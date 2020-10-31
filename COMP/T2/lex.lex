%{
    #include "bib.hpp"
    #include "syntax.tab.hpp"
%}
%option noyywrap 

NUMERO		[0-9]+
IDENT     [A-Za-z]+[a-zA-Z0-9]*
LITERAL     \".*\"

%%
[ \n\t]                 {}
{NUMERO}+				{yylval.constante = atoi(yytext); return INT;}
{NUMERO}+\.{NUMERO}      {yylval.fconstante = atof(yytext); return FLOAT;}
";"                     {return SEMICOLON;}
"+"						{return PLUS;}
"-"						{return MINUS;}
"*"                     {return MULTIPLY;}
"/"					    {return DIVIDE;}
"read"			        {return READ;}
"print"				    {return WRITE;}
"="						{return RECEIVE;}
"=="                    {return EQUALS;}
"!="                    {return DIFFERENT;}
">"						{return BIGGER;}
"<"						{return LESS;}
">="					{return EQBIGGER;}
"<="					{return EQLESS;}
"("						{return LPARENTHESES;}
")"						{return RPARENTHESES;}
"{"						{return LBRACKET;}
"}"						{return RBRACKET;}
","					    {return COMA;}
"&&"					{return AND;}
"||"					{return OR;}
"!"					    {return NOT;}
"if"				    {return IF;}
"else"				    {return ELSE;}
"while"		            {return WHILE;}
"do"                    {return DO;}
"return"                {return RETURN;}
"int"                   {return INT_T;}
"float"                 {return FLOAT_T;}
"string"                {return STRING_T;}
{IDENT}				    {yylval.id = yytext; return ID;}
{LITERAL}				{yylval.literal = yytext; return LITERAL;}
.						{return INVALID_CHAR;}
%%