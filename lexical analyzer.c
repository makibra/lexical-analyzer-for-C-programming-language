/*
Authors      :  MAKHLOUF Ibrahim & SEKAL oussama amir
Date        :  10-11-2023
Program     :   The code We’ve provided is a simple lexical analyzer for C programming language.
				The program reads the source file character by character and checks whether each character is a
				separator, operator, digit, part of an identifier or keyword, or part of a string. It then prints out
				the type of each token it encounters.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

char str[20];

void vider_tableau(char* ch) {
    int i = 0;
    for (i = 0; i < 20; i++) {
        *(ch + i) = '\0';
    }
}

const char* motsCles[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

bool mot_cle(const char* mot) {
    int nbMotsCles = sizeof(motsCles) / sizeof(motsCles[0]);
    for (int i = 0; i < nbMotsCles; i++) {
        if (strcmp(mot, motsCles[i]) == 0) {
            return true;
        }
    }
    return false;
}

// separateur
bool separateur(char ch) {
    if (ch == ',' || ch == ':' || ch == ';' ||
        ch == '(' || ch == ')' || ch == '{' ||
        ch == '}')
        return true;

    return false;
}

// operateur
bool operateur(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return true;
    return false;
}

// digit
bool digit(char ch) {
    if (ch == '0' || ch == '1' || ch == '2' ||
        ch == '3' || ch == '4' || ch == '5' ||
        ch == '6' || ch == '7' || ch == '8' ||
        ch == '9')
        return true;
    return false;
}

int main() {
    FILE* source, * dist;
    int i, caracere_actuel;
    source = fopen("source.txt", "r");
    dist = fopen("dist.txt", "w");
    if (source != NULL) {
        while (caracere_actuel != EOF) {
            caracere_actuel = fgetc(source);
            if (separateur(caracere_actuel)) printf("%c separateur \n", caracere_actuel);
            else if (operateur(caracere_actuel)) printf("%c operateur \n", caracere_actuel);
            else if (isdigit(caracere_actuel)) {
                i = 0;
                str[i] = caracere_actuel;
                i++;
                caracere_actuel = fgetc(source);
                while (isdigit(caracere_actuel)) {
                    str[i] = caracere_actuel;
                    i++;
                    caracere_actuel = fgetc(source);               }
                if (isalpha(caracere_actuel) || (caracere_actuel == '_')) {
                    while ((!separateur(caracere_actuel)) && (caracere_actuel != ' ') && !operateur(caracere_actuel)) {
                        str[i] = caracere_actuel;
                        i++;
                        caracere_actuel = fgetc(source);
                    }
                    printf("%s n'est pas un identifiant correct !\n", str);
                }
                else printf("%s nombre\n", str);
                vider_tableau(str);
            }
            else if (isalpha(caracere_actuel)) {
                i = 0;
                while ((!separateur(caracere_actuel)) && (caracere_actuel != ' ') && !operateur(caracere_actuel)) {
                    str[i] = caracere_actuel;
                    i++;
                    caracere_actuel = fgetc(source);
                }
                if (mot_cle(str)) printf("%s mot clef\n", str);
                else printf("%s identifiant\n", str);
                if (operateur(caracere_actuel)) printf("%c operateur \n", caracere_actuel);
                if (separateur(caracere_actuel)) printf("%c separateur \n", caracere_actuel);
                vider_tableau(str);
            }
            else if (caracere_actuel == '"') {  
                i = 0;
                str[i] = caracere_actuel;
                i++;
              
                caracere_actuel = fgetc(source);
                while (caracere_actuel != '"' && caracere_actuel != EOF) {
                    str[i] = caracere_actuel;
                    i++;
                    caracere_actuel = fgetc(source);
                }
                if (caracere_actuel == '"') {
                       str[i] = caracere_actuel;
                        i++;
                    str[i] = '\0';
                    printf("%s string \n", str);
                }
                
                vider_tableau(str);
            }
        }
    }

    fclose(source);
    fclose(dist);
    return 0;
}
