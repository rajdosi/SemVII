
domains
n=integer
li=integer*
Z=integer*

predicates
start(n,li)
find(n,li,n)
rev(li,li,n)

clauses

start(E,Y):-Z=[],rev(Y,Z,E).
rev([X|Y],Z,E):-rev(Y,[X|Z],E).
rev([],Z,E):-find(E,Z,0).
find(E,[X|_],N):-E=X,write(N).
find(E,[_|Y],N):-A=N+1,find(E,Y,A).
find(_,[_],_):-write("element not present").