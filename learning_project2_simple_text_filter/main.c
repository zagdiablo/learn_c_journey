#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void string_analyzer(char *input_string, int *string_size, int *vowels, int *consonants, int *digits);

int main(void)
{
    char input_string[] = "C is Fun 101!";
    char *pInput_string = &input_string[0];
    int string_size = (sizeof(input_string) / sizeof(char)) - 1;
    int vowels = 0;
    int consonants = 0;
    int digits = 0;

    string_analyzer(pInput_string, &string_size, &vowels, &consonants, &digits);

    printf("String analyzer result: vowels = %d, consonant = %d, digits = %d", vowels, consonants, digits);

    return 0;
}

void string_analyzer(char *input_string, int *string_size, int *vowels, int *consonants, int *digits){
    const char vowels_char[] = "aiueo";
    const char consonants_char[] = "bcdfghjklmnpqrstvwxyz";
    const char digits_char[] = "1234567890";

    for(int i=0; i<(*string_size); i++){
        for(unsigned long int j=0; j<(sizeof(vowels_char)/sizeof(char))-1; j++){
            if(tolower(input_string[i]) == vowels_char[j]){
                (*vowels) += 1;
            }
        }
        for(unsigned long int j=0; j<(sizeof(consonants_char)/sizeof(char))-1; j++){
            if(tolower(input_string[i]) == consonants_char[j]){
                (*consonants) += 1;
            }
        }
        for(unsigned long int j=0; j<(sizeof(digits_char)/sizeof(char))-1; j++){
            if(tolower(input_string[i]) == digits_char[j]){
                (*digits) += 1;
            }
        }
    }
}
