a.out:	lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -ll -ly
	
y.tab.c: aug07_final.y
	yacc -d aug07_final.y

lex.yy.c: aug07_final.l
	lex aug07_final.l

