a.out: lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -ll

y.tab.c: prac2.y
	yacc -d prac2.y

lex.yy.c: prac2.l
	lex prac2.l
