#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkCode(char * tmp){
    char * a = "#include";
    int true = 0;
    if(strstr(tmp, a)!=0) {
        true = 1;
    }
    return true;
}

int count(char *code,char * a, int *val, int *ary, int *mat){
    char * try = strstr(code, a);
    int index=0, boyut;
    int inx, ini;
    char * tmp;
    char * find;
    char * search;
    char * x="(";
    char * y=";";
    char * z=",";
    char * v="[";
    int ind1=0, ind2=0;
    while (try != NULL) {
        boyut=0;
        index = try-code;
        ind1 = strstr(try,x) - code;
        ind2 = strstr(try,y) - code;
        if(ind2 > index && ind2 < ind1){
            search = strstr(try, v);
            if(search != NULL){
                inx = strstr(search,v) - code;
            }
            while(search != NULL && inx > index && inx < ind2){
                inx = strstr(search,v) - code;
                if(inx < ind2){
                    boyut++;
                }
                search = strstr(search + 1, v);
            }
            switch(boyut){
                case 0:
                *val+=1;
                find = strstr(try,z);
                if(find != NULL){
                    ini=strstr(find,z) - code;
                }
                while(find != NULL && ini > index && ini < ind2){
                    ini = strstr(find,z) - code;
                    if(ini < ind2){
                        *val+=1;
                    }
                    find = strstr(find + 1, z);
                }
                break;

                case 1:
                *ary+=1;
                boyut=0;
                break;

                case 2:
                *mat+=1;
                boyut=0;
                break;
            }
        }
        try = strstr(try + 1, a);
    }
    return 0;
}

int countLoop(char *code,char *a, int *loop){
    int index=0;
    char * try = strstr(code, a);
    char * x = "}";
    char * search;
    int ind1, ind2;
    int max=0, found=0;
    while (try != NULL){
        index = try-code;
        ind1 = strstr(try,x) - code;
        search = strstr(try + 1, a);
        if(search != NULL){
            ind2 = strstr(try + 1,a) - code;
        }
        found++;
        while(search != NULL && ind2 > index && ind2 < ind1){
            ind2 = strstr(search,a) - code;
            if(ind2 < ind1){
                found++;
            }
            search = strstr(search + 1, a);
        }
        if(found>max){
            max = found;
        }
        found=0;
        *loop = max;
        try = strstr(try + 1, a);
    }
    return 0;
}

int main(){
    FILE *f = fopen("files/deneme.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *code = malloc(fsize + 1);
    fread(code, fsize, 1, f);
    fclose(f);

    code[fsize] = 0;

    int check = 0;
    int a = checkCode(code);
    if (a == 1)
    {
       check = 1;
    }
    else{
        printf("Girilen metin bir kod parçacığı değil.");
    }
    
    if(check == 1){
        int bolval=0, bolary=0, bolmat=0;
        int charval=0, charary=0, charmat=0;
        int unscval=0, unscary=0, unscmat=0;
        int int8val=0, int8ary=0, int8mat=0;
        int int16val=0, int16ary=0, int16mat=0;
        int shrtval=0, shrtary=0, shrtmat=0;
        int unssval=0, unssary=0, unssmat=0;
        int fltval=0, fltary=0, fltmat=0;
        int intval=0, intary=0, intmat=0;
        int lngval=0, lngary=0, lngmat=0;
        int unsival=0, unsiary=0, unsimat=0;
        int int32val=0, int32ary=0, int32mat=0;
        int dblval=0, dblary=0, dblmat=0;
        int int64val=0, int64ary=0, int64mat=0;
        int lndval=0, lndary=0, lndmat=0;
        int topval=0, topary=0, topmat=0;
        int loopFor=0, loopDo=0, loopWhile=0, loop=0;
        int checkIf=0;
        char * a = "bool ";
        count(code,a,&bolval,&bolary,&bolmat);
        a = "char ";
        count(code,a,&charval,&charary,&charmat);
        a = "unsigned char ";
        count(code,a,&unscval,&unscary,&unscmat);
        a = "__int8 ";
        count(code,a,&int8val,&int8ary,&int8mat);
        a = "__int16 ";
        count(code,a,&int16val,&int16ary,&int16mat);
        a = "short ";
        count(code,a,&shrtval,&shrtary,&shrtmat);
        a = "unsigned short ";
        count(code,a,&unssval,&unssary,&unssmat);
        a = "float ";
        count(code,a,&fltval,&fltary,&fltmat);
        a = "int "; 
        count(code,a,&intval,&intary,&intmat);
        a = "long ";
        count(code,a,&lngval,&lngary,&lngmat);
        a = "unsigned int ";
        count(code,a,&unsival,&unsiary,&unsimat);
        a = "__int32 ";
        count(code,a,&int32val,&int32ary,&int32mat);
        a = "double ";
        count(code,a,&dblval,&dblary,&dblmat);
        a = "__int64 ";
        count(code,a,&int64val,&int64ary,&int64mat);
        a = "_LONGDOUBLE ";
        count(code,a,&lndval,&lndary,&lndmat);

        topmat = 1*(bolmat + charmat + unscmat + int8mat) + 2*(int16mat + shrtmat + unssmat) + 4*(fltmat + intmat + unsimat + int32mat) + 8*(dblmat + int64mat + lndmat);
        topary = 1*(bolary + charary + unscary + int8ary) + 2*(int16ary + shrtary + unssary) + 4*(fltary + intary + unsiary + int32ary) + 8*(dblary + int64ary + lndary);
        topval = 1*(bolval + charval + unscval + int8val) + 2*(int16val + shrtval + unssval) + 4*(fltval + intval + unsival + int32val) + 8*(dblval + int64val + lndval);
        
        char * b = "for(";
        countLoop(code, b, &loopFor);
        b = "while(";
        countLoop(code, b, &loopWhile);
        b = "do{";
        countLoop(code, b, &loopDo);
        if(loopFor > loop) loop = loopFor;
        if(loopWhile > loop) loop = loopWhile;
        if(loopDo > loop) loop = loopDo;
        b = "if(";
        countLoop(code, b, &checkIf);

        if(loop > 0){
            printf("Zaman karmaşıklığı=O(n^%d)\n", loop);
            printf("Yer karmaşıklığı=");
            if(topmat != 0){
                printf("%dn^2 + ",topmat);
            }
            if(topary != 0){
                printf("%dn + ",topary);
            }
            printf("%d O(n^%d)",topval, loop);
        }
        else if(loop == 0 && checkIf > 0){
            printf("Zaman karmaşıklığı=O(1)\n");
            printf("Yer karmaşıklığı=");
            if(topmat != 0){
                printf("%dn^2 + ",topmat);
            }
            if(topary != 0){
                printf("%dn + ",topary);
            }
            printf("%d O(1)",topval);
        }
        else if(loop == 0 && checkIf == 0){
            printf("Zaman karmaşıklığı=0\n");
            printf("Yer karmaşıklığı=");
            if(topmat != 0){
                printf("%dn^2 + ",topmat);
            }
            if(topary != 0){
                printf("%dn + ",topary);
            }
            printf("%d",topval);
        }   
    }
}