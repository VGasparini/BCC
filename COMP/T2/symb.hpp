#ifndef SYMB_HPP
#define SYMB_HPP

#define NULO         0
#define NULO_STR     ""

#define TIPO_INT     1000
#define TIPO_FLOAT   1001
#define TIPO_STRING  1002
#define TIPO_VOID    1003

#define INST_IDIV            2000
#define INST_IMUL            2001
#define INST_IADD            2002
#define INST_ISUB            2003
#define INST_ICONST0         2004
#define INST_ICONST1         2005
#define INST_ICONST2         2006
#define INST_ICONST3         2007
#define INST_ICONST4         2008
#define INST_ICONST5         2009
#define INST_BIPUSH          2010
#define INST_ILOAD           2011
#define INST_ISTORE          2012
#define INST_GETPRINT        2013
#define INST_INVOKEPRINT_INT 2014
#define INST_INVOKEPRINT_STR 2015
#define INST_IF_ICMPEQ       2016
#define INST_IF_ICMPNE       2017
#define INST_IF_ICMPLT       2018
#define INST_IF_ICMPLE       2019
#define INST_IF_ICMPGT       2020
#define INST_IF_ICMPGE       2021
#define INST_GOTO            2022
#define INST_NEWLABEL        2023
#define INST_LDC             2024
#define INST_DUP             2025
#define INST_NEWSCANNER      2026
#define INST_GETINPUTSTREAM  2027
#define INST_INVOKEINPUTSTR  2028
#define INST_NEXTINT         2029
#define INST_LDCSTRING       2030
#define INST_ASTORE          2031
#define INST_ALOAD           2032
#define INST_NEXTLINE        2033
#define INST_DELIMITADORFUNC 2034
#define INST_INVOKESTATIC    2035
#define INST_IRETURN         2036
#define INST_ARETURN         2037
#define INST_RETURN          2038
#define INST_IINC            2039

#define CMP_EQUAL            3000
#define CMP_NEQUAL           3001
#define CMP_LTHAN            3002
#define CMP_LEQUAL           3003
#define CMP_GTHAN            3004
#define CMP_GEQUAL           3005
#define OP_MUL               3006
#define OP_ADD               3007
#define OP_DIV               3008
#define OP_SUB               3009
#define OP_IINC              3010

#endif