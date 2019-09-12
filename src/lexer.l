%option noyywrap

%{
#include <stdio.h>
#include <string.h>

enum class Token {
    TK_WHITESPACE,
    TK_INT,
    TK_REAL,
    TK_ID,
    TK_ADDOPR,
    TK_MULTOPR,
    TK_LOGOPR,
    TK_RELOPR,
    TK_ERROR,
    TK_ASIG,
    TK_PERIOD,
    TK_DDPER,
    TK_INCR,
    TK_FALSELIT,
    TK_TRUELIT,
    TK_STRLIT,
    TK_DATELIT,
    TK_WHILELIT,
    TK_IFLIT,
    TK_ELSELIT,
    TK_RETURNLIT,
    TK_INICIOLIT,
    TK_IFTHENLIT,
    TK_DOLIT,
    TK_ENDLIT,
    TK_STATIC,
    TK_INTTYPE,
    TK_ANYTYPE,
    TK_BOOLEAN,
    TK_VOID,
    TK_REALTYPE,
    TK_STRING,
    TK_DATE,
    TK_FRAGDIG,
    TK_FRAGLETTER,
    TK_COMMENT,
    TK_LEFTPAR,
    TK_RIGHTPAR,
    TK_LEFTBRACE,
    TK_RIGHTBRACE,
    TK_COMMA,
    TK_SEMICOLON,
    TK_EOF
};

#define YY_DECL Token getNextToken()

%}

%%

(\t|\r|\n|\ ) { return Token::TK_WHITESPACE; }
[0-9] { return Token::TK_FRAGDIG; }
[0-9]+ { return Token::TK_INT; }
[0-9]+(\.[0-9]+) { return Token::TK_REAL; }
"false" {  return Token::TK_FALSELIT; }
"true" { return Token::TK_TRUELIT; }
"while" { return Token::TK_WHILELIT; }
"if" { return Token::TK_IFLIT; }
"else" { return Token::TK_ELSELIT; }
"EXIT" { return Token::TK_RETURNLIT; }
"BEGIN" { return Token::TK_INICIOLIT; }
"THEN" { return Token::TK_IFTHENLIT; }
"DO" { return Token::TK_DOLIT; }
"END" { return Token::TK_ENDLIT; }
"static" { return Token::TK_STATIC; }
"int" { return Token::TK_INTTYPE; }
"anytype" { return Token::TK_ANYTYPE; }
"boolean" { return Token::TK_BOOLEAN; }
"void" { return Token::TK_VOID; }
"real" { return Token::TK_REALTYPE; }
"String" { return Token::TK_STRING; }
"date" { return Token::TK_DATE; }
\( { return Token::TK_LEFTPAR; }
\) { return Token::TK_RIGHTPAR; }
\} { return Token::TK_LEFTBRACE; }
\{ { return Token::TK_RIGHTBRACE; }
\, { return Token::TK_COMMA; }
\; { return Token::TK_SEMICOLON; }
\"([a-zA-Z]|[0-9]|\ |%|@|,|-|=|\(|\)|_)*\" { return Token::TK_STRLIT; }
[a-zA-Z] { return Token::TK_FRAGLETTER; }
(\/\/).* { return Token::TK_COMMENT; }
([0-9][0-9]\/[0-9][0-9]\/[0-9][0-9][0-9][0-9]) { return Token::TK_DATELIT; }
([a-zA-Z_]([a-zA-Z]|[0-9])*) { return Token::TK_ID; }
[+|\-] { return Token::TK_ADDOPR; }
[\*|\/] { return Token::TK_MULTOPR; }
(\|{2}|\&{2}) { return Token::TK_LOGOPR; }
(<=|>=|<|>|==) { return Token::TK_RELOPR; }
(:=) {  return Token::TK_ASIG; }
(\.) {  return Token::TK_PERIOD; }
(::) {  return Token::TK_DDPER; }
(\+\+) {  return Token::TK_INCR; }
<INITIAL><<EOF>> { return Token::TK_EOF; }
. { return Token::TK_ERROR; }


%%

int main(int argc, char* argv[]) {
    if(argc != 2){
        fprintf(stderr,"Wrong args");
        return 1;
    }

    yyin = fopen(argv[1],"r");

    FILE *file ;
    file = fopen("tokens.txt", "a");

    Token t;

    while (t != Token::TK_EOF)
    {
        t = getNextToken();
        if(t == Token::TK_ERROR ){
            printf("error\n");
            return 1;
        }
        
        printf("lexema: %s\n",yytext);
        if (t != Token::TK_WHITESPACE && t != Token::TK_COMMENT && t != Token::TK_EOF)
        {
            char text[3000];
            strcpy(text, yytext);
            strcat(text, "\n");
            fputs(text, file);
        }
    }

    fclose(file);

    // Runs the main flex function
    

    return 0;
}