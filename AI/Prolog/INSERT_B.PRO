domains
X=symbol*
Y=symbol
P=integer

predicates
insert_begin(X,X,Y)
insert_end(Y,X,X)
insert(Y,X,P,X)
reverse(X,X,X)

clauses
insert_begin([Y|X],X,Y).

insert_end(Y,[Z|X],[Z|N]):-insert_end(Y,X,N).
insert_end(Y,[],[Y]).

insert(V,[H|X],P,[H|G]):- P>1,C=P-1,
			  insert(V,X,C,G). 
insert(V,X,1,[V|X]).
reverse([],Z,Z).
reverse([H|X],Z,R):-reverse(X,Z,[H|R]).