domains
	A=Symbol*
	B=Symbol
predicates
	chhe(A,B)
	check(A,B)
clauses
	check([X|_],X):-write("Found!!").
	check([_|A],B):-check(A,B).
	check([_|_],_):-write("Not Found!").
	chhe(A,B):-check(A,B).