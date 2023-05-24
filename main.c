#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

int generate_random_base() {
    srand(time(0));   
    int base = (rand() % (10 - 2 + 1)) + 2;   
    return base;
} 

int BaseToAscii (long int number, int base) {
    long int temp = number;
    int ascii_value = 0;
    int temp_count = 0;
    while (temp!=0) {
        int last_digit = temp%10 ;
        ascii_value += (last_digit * pow(base,temp_count));
        ++temp_count;
        temp = temp/10;
    }
    return ascii_value;
}

void delay(int number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

int main() {

    char test_string [256];            
    printf("\nEnter the string to be encrypted: ");
    fgets(test_string, 255, stdin);          
    int n = strlen(test_string);
    int encryption_base = generate_random_base() ;

    printf("\nYour Key is %d. Please remember it otherwise you can't decrypt your message.\n", encryption_base);
    printf("\nEncrypting..\n");
    delay(3);

    int final_length = n*16;
    int encrypted_msg [final_length] ;            
    int pos=0;      

    for (int i=0; i<n; ++i) {
        char c = test_string[i]; 
        int c_ascii = (int)c;    
        int reverse_converted [16];           
        int temp = c_ascii;                       
        int n2=0;
        int subscript = 0;
        while (temp>0) {   
            reverse_converted[subscript] = (temp%encryption_base);      
            temp = temp/encryption_base;
            n2++;  
            ++subscript;  
        }

        int final_converted [n2];            
        int k=0;

        for (int j = n2 - 1; j >= 0; --j) {
            final_converted[k] = reverse_converted[j];
            ++k;
        }
        for (int l=0; l<n2; ++l) {
            encrypted_msg[pos+l]=final_converted[l];         
        }

        pos+=n2;          
        encrypted_msg[pos] = 9999;
        pos+=1;            
    }

    char super_encrypted_msg [pos];

    for (int g=0; g<pos; ++g) {
        
        if (encrypted_msg[g] == 0)
            super_encrypted_msg[g] = ')' ;
        else if (encrypted_msg[g] == 1)
            super_encrypted_msg[g] = '!' ;
        else if (encrypted_msg[g] == 2)
            super_encrypted_msg[g] = '@' ;
        else if (encrypted_msg[g] == 3)
            super_encrypted_msg[g] = '#' ;
        else if (encrypted_msg[g] == 4)
            super_encrypted_msg[g] = '$' ;
        else if (encrypted_msg[g] == 5)
            super_encrypted_msg[g] = '%' ;
        else if (encrypted_msg[g] == 6)
            super_encrypted_msg[g] = '^' ;
        else if (encrypted_msg[g] == 7)
            super_encrypted_msg[g] = '&' ;
        else if (encrypted_msg[g] == 8)
            super_encrypted_msg[g] = '*' ;
        else if (encrypted_msg[g] == 9)
            super_encrypted_msg[g] = '(' ;
        else if (encrypted_msg[g] == 9999)
            super_encrypted_msg[g] = '~' ;           
    }

    printf("\nYour encrypted message is:\n");
    for (int m=0; m<pos; ++m)  {          
        printf("%c ",super_encrypted_msg[m]);
    }


    
    printf("\n\nPress Enter to continue with decryption ");
    char temp_choice;
    scanf("%c",&temp_choice);

    int key ;
    printf("\n\nEnter your Decryption Key: ");
    scanf("%d",&key);
    if (key !=  encryption_base) {
        printf("\nYou entered the wrong Key. You have only one chance left. Enter Again: ");
        scanf("%d",&key);
        if (key !=  encryption_base) {
            printf("\nSorry you again entered the wrong key. You can't decrypt your message.");
            exit(1);             
        }
    }



    // DECRYPTION :

    char temp_encrypted [final_length];            
    for (int p=0; p<pos; ++p) {
        temp_encrypted[p] = super_encrypted_msg[p];
    }
    printf("\n\n\nDecrypting...");
    delay(3);

    int first_decrypted [pos];
    for (int q=0; q<pos; ++q)  {
        if (temp_encrypted[q] == ')')
            first_decrypted[q] = 0;
        else if (temp_encrypted[q] == '!')
            first_decrypted[q] = 1;
        else if (temp_encrypted[q] == '@')
            first_decrypted[q] = 2;
        else if (temp_encrypted[q] == '#')
            first_decrypted[q] = 3;
        else if (temp_encrypted[q] == '$')
            first_decrypted[q] = 4;
        else if (temp_encrypted[q] == '%')
            first_decrypted[q] = 5;
        else if (temp_encrypted[q] == '^')
            first_decrypted[q] = 6;
        else if (temp_encrypted[q] == '&')
            first_decrypted[q] = 7;
        else if (temp_encrypted[q] == '*')
            first_decrypted[q] = 8;
        else if (temp_encrypted[q] == '(')
            first_decrypted[q] = 9;
        else if (temp_encrypted[q] == '~')                 
            first_decrypted[q] = 9999;
    }

    printf("\n\n");
    for (int r=0; r<pos; ++r) {
        printf("%d ",first_decrypted[r]);
    }
    delay(1);

    int second_decrypted [n];   
    int second_decrypted_index = 0;    
    int previous_9999_index = -1;          
    for (int s=0; s<pos; ++s) {
        if (first_decrypted[s] == 9999) {
            int current_9999_index = s;         
            int len_of_s;
            if (previous_9999_index != -1) {
                len_of_s = current_9999_index - previous_9999_index - 1;              
            } else {
                len_of_s = current_9999_index;                       
            }
            char temp_str [len_of_s];       
            int temp_i=0; 
            for (int t=previous_9999_index+1; t<current_9999_index; ++t) {
                char temp_char = first_decrypted[t]+'0';                      
                temp_str[temp_i] = temp_char;
                ++temp_i;
            }
            int base_int_value = atoi(temp_str);          
            second_decrypted[second_decrypted_index] = base_int_value;
            ++second_decrypted_index;           
            previous_9999_index = current_9999_index;  
        }

    }

    printf("\n");
    for (int u=0; u<n; ++u) {
        printf("%d ",second_decrypted[u]);
    }
    delay(1);

    int third_decrypted [n];
    for (int v=0; v<n; ++v) {
        third_decrypted[v] = BaseToAscii(second_decrypted[v],encryption_base);
    }
    printf("\n");
    for (int w=0; w<n; ++w) {
        printf("%d ",third_decrypted[w]);
    }
    delay(1);

    char final_decrypted [n-1];
    for (int z=0; z<n-1; ++z) {
        char temp_c = third_decrypted[z];
        final_decrypted[z] = temp_c;
    }

    printf("\n\nYour DECRYPTED message is : ");
    for (int y=0; y<n-1; ++y) {
        printf("%c",final_decrypted[y]);
    }
    printf("\n\n");
    
    return 0; 
}