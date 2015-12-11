domains
	A=Integer
	B=Integer
	C=Symbol
	D=Real
predicates 
	Go
	Calc(Integer,Integer,Symbol)	
clauses
	Go:-
	Readint(A),
	Readint(B),
	Readln(C),
	Calc(A, B, C).
	Calc(A,B,"+") :- D=A+B, Write(D).
	Calc(A,B,"-") :- D=A-B, Write(D).
	Calc(A,B,"*") :- D=A*B, Write(D).
	Calc(A,B,"/") :- D=A/B, Write(D).