#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct label
{
    char label[100];
    int addr;
};

int label_to_addr(struct label *labels, char *label)
{
    for (int l = 0; l < sizeof(labels); l++)
    {
        if (strstr(labels[l].label, label))
        {
            return labels[l].addr;
        }
    }
    printf("Label %s not found\n", label);
    return 0;
}
int is_decimal(char *string)
{
    int i = 0;
    while (string[i])
    {
        if (!isdigit(string[i]))
            return 0;
        i++;
    }
    return 1;
}
int to_decimal(char *string)
{
    int num = 0;
    int i = 0;
    while (string[i])
    {
        if (isdigit(string[i]))
        {
            num *= 10;
            num += (string[i] - '0');
        }
        i++;
    }
    return num;
}

int hex_dec_to_int(char *num)
{
    if (strncmp(num, "0x", 2) == 0)
        return strtol(num, NULL, 0);
    return to_decimal(num);
}

int inst_to_hex(char *inst)
{
    if (strstr(inst, "lda"))
        return 0x0;
    if (strstr(inst, "sto"))
        return 0x1;
    if (strstr(inst, "add"))
        return 0x2;
    if (strstr(inst, "sub"))
        return 0x3;
    if (strstr(inst, "jmp"))
        return 0x4;
    if (strstr(inst, "jne"))
        return 0x6;
    if (strstr(inst, "stp"))
        return 0x7;
    // extra
    if (strstr(inst, "sa"))
        return 0x5;
}

void do_pass(int pass, FILE *inFile, FILE *outFile, struct label *labels)
{
    char line[100];

    int line_num = 0;
    int label_c = 0;
    while (fgets(line, 100, inFile))
    {
        int is_asm_line = 0;

        line[strcspn(line, "\n")] = 0;
        if (line[0] == 0)
            continue;

        char *comment = strchr(line, ';'); // removing comments
        if (comment)
            *comment = '\0';

        char line_copy[100];
        strcpy(line_copy, line);

        char *inst = strtok(line, " ");
        char *parm = strtok(NULL, " ");
        parm = strtok(parm, "+");
        char *offset = strtok(NULL, "+");

        char line_lower[100];
        for (int i = 0; i < 100; i++)
        {
            line_lower[i] = tolower(line[i]);
        }

        if (line[0] == '.' && pass == 0)
        {
            struct label local;

            memcpy(line, line + 1, sizeof(line) - 1);

            strcpy(local.label, line);
            local.addr = line_num;

            labels[label_c++] = local;

            printf("Label: %s at: %u\n", local.label, local.addr);
        }
        else if (
            strstr(inst, "lda") || // normal insructions
            strstr(inst, "sto") ||
            strstr(inst, "add") ||
            strstr(inst, "sub") ||
            strstr(inst, "jmp") ||
            strstr(inst, "jne") ||
            strstr(inst, "stp") ||
            // extra
            strstr(inst, "sa"))
        {
            is_asm_line = 1;
            if (pass == 1)
            {
                int addr = 0;
                if (parm)
                {
                    if (
                        strncmp(parm, "0x", 2) == 0 ||
                        is_decimal(parm))
                    {
                        addr = hex_dec_to_int(parm);
                    }
                    else
                    {
                        addr = label_to_addr(labels, parm);
                    }
                }

                if (
                    addr > 0xFFF ||
                    (strstr(inst, "stp") && addr > 0x0))
                {
                    printf("WARNING line %d, instruction: %s, has a input that it is capable of %03X\n", line_num, inst, addr);
                }
                int off = 0;
                if (offset)
                    off = hex_dec_to_int(offset);
                printf("line: %d inst: %s, addr: %03X offset: %d\n", line_num, inst, addr, off);
                fprintf(outFile, "%x %03X\n", inst_to_hex(inst), addr + off);
            }
        }
        else if (
            strncmp(inst, "0x", 2) == 0 ||
            is_decimal(inst))
        {
            inst = strtok(line_copy, " ");
            while (inst != NULL)
            {
                int num = hex_dec_to_int(inst);

                if (pass == 1)
                {
                    fprintf(outFile, "%04X\n", num);
                }

                is_asm_line += 1;
                inst = strtok(NULL, " ");
            }
        }

        line_num += is_asm_line;
    }
    rewind(inFile);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("too few arguments");
        return 1;
    }

    FILE *inFile, *outFile;
    inFile = fopen(argv[1], "r");

    if (!inFile)
    {
        printf("invalid file");
        return 1;
    }
    outFile = fopen(argv[2], "w");
    if (!outFile)
    {
        outFile = fopen("./o.lst", "w");
    }

    struct label labels[4096];

    do_pass(0, inFile, outFile, labels);
    do_pass(1, inFile, outFile, labels);

    fclose(inFile);
    fclose(outFile);

    return 0;
}