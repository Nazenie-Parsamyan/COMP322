#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


char ascii[34][6] = {"NULL", "SOH", "STX", "ETX",  
                    "EOT", "ENQ", "ACK", "BEL", "BS", 
                    "TAB", "LF", "VT", "FF", "CR", "SO", 
                    "SI", "DLE", "DC1", "DC2", "DC3", "DC4",
                    "NAK", "SYN", "ETB", "CAN", "EM", "SUB",
                    "ESC", "FS", "GS", "RS", "US", "Space", "DEL"};
char binary[200][9];
int binarySize = 0;

void BUFFER(){
    int i;
    int j;
    for(i=0;i<=7;i++){
        for(j=0;j<=7;j++){
            if (binary[i][j]!='1' && binary[i][j]!='0'){
                int k = j;
                while(k<=7){
                    binary[i][k]='0';
                    k++;
                }
            }

        }
        binary[i][8]= '\0';
    }

}

int Decimal(char* bin){
    
    
    
    int i;
    int dec =0;
    for(i=1;i<=7;i++){

        dec+=((int)(bin[i])-48)*pow(2,7-i);

      
        
    }

    return dec;

}

void Ascii(int dec, char* c){
    if(dec<=32){
        c = ascii[dec];
    } 
    else if(dec==127){
        c = ascii[33];
    }
    else{
        c[0] = (char)(dec);
        c[1] = '\n';
    }
}

char* Parity(char* bin){
   
    int numOnes =0;
    int i;
    for(i=0;i<=7;i++){
        numOnes += ((int)(bin[i]-48));
        
    }
    if(numOnes % 2 == 0){
            return "EVEN";

        }
        else{
            return "ODD";
        }

}

void PRINT(char* bin){
    int dec;
    char* parity;
    char ascii[6];
    dec = Decimal(bin);
    parity =Parity(bin);
    Ascii(dec, ascii);
    printf("%8s %8c %8d %s\n", bin, ascii[0], dec, parity);
}

 void readFile(int fd){
    char buf;
    int x=1;
    int i=0;
    int j=0;
    while(x){
        x = read(fd,&buf,1);
        printf("%c", buf);
        if(buf==' '){
            i++;
            binarySize++;
            binary[i][j] = '\0';
            j=0;
        }
        else if(x==0){
             continue;
        }
        else{
            binary[i][j] = buf;
            j++;
            if(j==8){
                binary[i][j] = '\0';
                j=0;
                i++;
            }
        }
    }
    binarySize+=1;
    close(fd);
}

int main(int argc, char** argv)
{
    int i;
    if (argc<=1){
        printf("Error: File Not Found.");
        exit(1);
    }
     else if (argv[1][0]=='-'){
         for (i=2; i<argc; i++){
            strcpy(binary[i-2], argv[i]);
         }
         binarySize =argc-2;
    }
    else if (argv[1][0]=='1'||argv[1][0]=='0'){
        for (i=1; i<argc;i++){
            strcpy(binary[i-1], argv[i]);
        }
        binarySize= argc -1;
    }
    else{
        
        int fd = open(argv[1], O_RDONLY);
        if(fd==-1){
            printf("Error: File Not Found");
            exit(1);
        }
        readFile(fd);

    }
    printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");
    BUFFER();
    for(i=0;i<binarySize;i++){
     
        PRINT(binary[i]);

    }
   
return(0);

	

}