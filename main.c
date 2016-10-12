#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_LENTH 1024

typedef unsigned int uint32_t;
typedef unsigned long size_t;
typedef unsigned long long uint64_t;


void printLine(char *path, char *dest, char *addition);

int main(int argc,char **argv) {
    char *memdata = "/home/alpha/Desktop/handleflow/oracle_memdata.conf";
    char *mempage = "/home/alpha/Desktop/handleflow/oracle_mempage.conf";
    char *dest = "/home/alpha/Desktop/handleflow/test.bin";

    printLine(mempage, dest, memdata);
    return 0;
}

void printLine(char *path, char *dest, char *addition){
    char buffer[MAX_LENTH];
    char buffer1[MAX_LENTH];
    size_t len;
    uint32_t *data, linenum=0;
    uint64_t *stream1, ret1=0;
    uint32_t *stream2, ret2=0;
    int count=0;
    char *buf1;
    char *ptr;

    buf1=(char *) malloc(sizeof(char) *124);
    data = &linenum;
    stream1 = &ret1;
    stream2 = &ret2;
    FILE *pf = fopen(path, "rt");
    FILE *df = fopen(dest, "w");

    if(pf == NULL || df== NULL){
        printf("file is not open");
    }

    fseek(df, 4L, SEEK_SET);
    while(fgets(buffer, MAX_LENTH, pf) != NULL){
        strcpy(buf1, buffer);
        char *token = strtok(buf1, ",");
        while (token != NULL){
            count++;
            if(count==1){
                ret1 = strtoull(token, &ptr, 16);
                fwrite(stream1, sizeof(ret1), 1, df);
                fflush(df);
            }
            if(count==3){
                ret2 = strtoul(token, &ptr, 16);
                fwrite(stream2, sizeof(ret2), 1, df);
                fflush(df);
            }
            token = strtok(NULL, ",");
        }
        linenum++;
        count = 0;
    }
    rewind(df);
    fwrite(data, sizeof(linenum), 1, df);
    fflush(df);

    FILE *spf = fopen(addition,"r");
    if(spf == NULL){
        printf("open source stream fail!");
    }
    fseek(df, 0 ,SEEK_END);
    while((len = fread(buffer1, sizeof(char), MAX_LENTH, spf)) > 0){
        fwrite(buffer1, sizeof(char), len, df);
        fflush(df);
    }
    fclose(spf);

    fclose(pf);
    fclose(df);

}