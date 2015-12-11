domains
str=string
n=integer

predicates
compare(str,n)
pas(str)

clauses
pas(A):-compare(A,2).
compare(_,0):-write("You get Blocked").
compare(A,_):-A="password",write("Correct Password").
compare(_,N):-B=N-1,write("Incorrect Password"),readln(S),compare(S,B).

