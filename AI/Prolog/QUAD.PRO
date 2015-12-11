domains
	A=Integer
	B=Integer
	C=Integer
	D=Real
	R1=Real
	R2=Real
predicates
	Go
	Delta(Integer, Integer, Integer)
	Calc(Real, Integer, Integer)
clauses
	Go:-
	Readint(A),
	Readint(B),
	Readint(C),
	Delta(A,B,C).
	Delta(A,B,C):-
	D=(B*B)-(4*A*C),
	Write("Value of D: "),
	Write(D, "\n"),
	Calc(D,B,A).
	Calc(D,B,A):-
	R1=((-1*B)+sqrt(D))/(2*A),
	R2=((-1*B)-sqrt(D))/(2*A),
	Write("Root 1 : ", R1, "\n"), 
	Write("Root 2 : ", R2, "\n").