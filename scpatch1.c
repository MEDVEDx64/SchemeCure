/// medvedx64, 2013-03-26

#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc < 2)
        return 1;

    int i;
    unsigned char destv = 0;

    FILE *log = fopen("scpatch.log", "w");
    fprintf(log, "scpatch argc=%d\n", argc);

    for(i = 1; i < argc; i++)
    {
        FILE *f = NULL;
        if(!(f = fopen(argv[i], "r+")))
        {
            fprintf(log, "%d: %s: fail (can't open)\n", i, argv[i]);
            continue;
        }

        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        rewind(f);

        if(len != 297){
            fprintf(log, "%d: %s: fail (length mismatch)\n", i, argv[i]);
            continue;
        }

        fseek(f, 0xe0, SEEK_SET);
        fwrite(&destv, 1, 1, f);
        fclose(f);
        fprintf(log, "%d: %s: success\n", i, argv[i]);
    }

    fclose(log);
    return 0;
}
