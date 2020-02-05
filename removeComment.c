void removeComment(char *c){
       int a, b;

       for(a=b=0; c[b] ;){
              if(c[b]=='/' && c[b+1] == '/') {for(b= b+2; c[b] && c[b++]!= '\n';) ; }
              else if (c[b] == '/' && c[b+1] == '*'){
                     for(b=b+2; c[b] && c[++b] && (c[b-1]!='*' || c[b]!='/' || !b++); );
              }
              else {c[a++] = c[b++];}
       }
       c[a]='\0';
}

int main(int argc, const char * argv[]) {
FILE* fin;
FILE* fout;
int i = 0;
int c = 0;
char file[MAX];

while((c = fgetc(fin))!=EOF && i < MAX){
file[i] = fgetc(fin);
++i;
}
removeComment(file);
fputs(file, fout);
closefiles(2, fin, fout);
return 0;
}
