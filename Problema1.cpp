#include <stdio.h>

typedef struct{
    int nrMat; //CNP
    int grupa;
    int an;
    int absenteCurs[10];
    int absenteSeminar[10];
} Student;

void conversie(char s1[]){
    FILE* f, * g;
    Student s;
    int i;
    char s2[20] = {0};


    f=fopen(s1, "rb");

    if (f==NULL) {
        printf("Fisierul nu a putut fi gasit");
        return;
    }

    printf("\nFisier text: ");
    scanf("%s", s2);
    g=fopen(s2,"w+");

    if(g==NULL) {
        printf("Eroare la crearea fisierului");
        return;
    }

    fprintf(g,"NR MATRICOL \t|GRUPA \t|AN \t");
    for(i=0;i<10;i++){
        fprintf(g, "|ABSENTECURS%d \t", i+1);
        fprintf(g, "|ABSENTESEMINAR%d \t", i+1);
    }

    fread(&s, sizeof(Student), 1, f);

    while(!feof(f)){
        fprintf(g, "\n%d \t\t|%d \t|%d \t", s.nrMat, s.grupa, s.an);
        for(i=0;i<10;i++) {
            fprintf(g, "|%d \t\t", s.absenteCurs[i]);
            fprintf(g, "|%d \t\t\t", s.absenteSeminar[i]);
        }
        fread(&s, sizeof(Student), 1, f);

    }
    fclose(f);
    fclose(g);

}

int main()
{
    FILE *f;
    char s1[20];
    Student s;
    int i, j, cod, nrMat, totalAbsente, varLucru;

    printf("\nFisier: ");
    gets(s1);
    f=fopen(s1,"ab");

    if(f==NULL) {
        printf("Eroare la deschiderea/crearea fisierului");
        return 0;
    }

    printf("Nr.matricol: ");
    scanf("%d", &cod);

    while(cod<1) {
        printf("\nNr matricol nu poate fi negativ sau 0. Introduceti nr matricol sau -1 pt oprire: ");
        scanf("%d",&cod);
    }

    while(!feof(stdin) && cod!=-1) {

        s.nrMat = cod;

        printf("Grupa: ");
        scanf("%d",&varLucru);
        while (varLucru<1) {
            printf("Grupa trebuie sa fie mai mare decat 0. Introduceti grupa: ");
            scanf("%d", &varLucru);
        }
        s.grupa = varLucru;

        printf("An: ");
        scanf("%d",&varLucru);
        while (varLucru<1 || varLucru>5) {
            printf("Anul trebuie sa fie intre 1 si 5. Introduceti anul din nou: ");
            scanf("%d", &varLucru);
        }
        s.an = varLucru;


        for(i=0;i<10;i++){

            printf("Absente curs %d: ",i+1);
            scanf("%d", &varLucru);
            while (varLucru<0 || varLucru>10) {
                printf("Studentul poate avea min 0 si max 10 absente/semestru. Absente curs %d: ",i+1);
                scanf("%d", &varLucru);
            }
            s.absenteCurs[i] = varLucru;

            printf("Absente seminar %d: ",i+1);
            scanf("%d", &varLucru);
            while (varLucru<0 || varLucru>10) {
                printf("Studentul poate avea min 0 si max 10 absente/semestru. Absente seminar %d: ",i+1);
                scanf("%d", &varLucru);
            }
            s.absenteSeminar[i] = varLucru;
        }

        fwrite(&s,sizeof(Student),1,f);

        printf("\nNr.matricol sau -1 pentru a opri adaugarea de date: ");
        scanf("%d",&cod);
        while(cod<1 && cod!=-1) {
            printf("\nNr matricol nu poate fi negativ sau 0. Introduceti nr matricol sau -1 pt oprire: ");
            scanf("%d",&cod);
        }
    }

    fclose(f);

    conversie(s1);

    if(!(f=fopen(s1,"rb"))) {
        printf("\nFisierul %s nu poate fi deschis",s1);
        return 0;
    }


    printf("\nNr. matricol pentru care se calculeaza totalul absentelor: ");
    scanf("%d",&nrMat);
    if(nrMat==-1) {
        printf("\nCod invalid. Niciun student nu va fi adaugat");
    }

    while(nrMat!=-1){
        rewind(f);
        fread(&s, sizeof(Student), 1, f);
        i=0;
        totalAbsente = 0;
        while(!feof(f) && i==0) {
            if(nrMat==s.nrMat){
                i=1;
                for(j=0;j<10;j++){
                    totalAbsente+=s.absenteCurs[j];
                    totalAbsente+=s.absenteSeminar[j];
                }
            }
            fread(&s, sizeof(Student), 1, f);
        }
        if (i==0) {
            printf("Nu a fost gasit niciun student cu nr matricol %d", nrMat);
        } else {
            printf("Total absente %d", totalAbsente);
        }
        printf("\nNr. matricol pentru care se calculeaza totalul absentelor sau -1 pt oprire: ");
        scanf("%d",&nrMat);

    }
    fclose(f);
    return 0;
}

