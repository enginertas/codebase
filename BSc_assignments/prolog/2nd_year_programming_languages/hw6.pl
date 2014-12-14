/******Helper for inverting predicates*******/
not(P).
not(P):-call(P),!,fail.

/******msequal****Equaliy for multitrees*********/
search([X|T], [], [Y|J]):-			
	(msequal(X,Y), msequal(T,J); 
	not(msequal(X,Y)), search([X|T],[Y],J)),!.		
							
search([X|T], [A|B], [Y|J]):-
	(msequal(X,Y), append([A|B] , J, R), msequal(T,R); 
	not(msequal(X,Y)), append([A|B] , [Y], R), search([X|T],R,J)),!.

msequal([],[]).
msequal(X,X):-!.
msequal([X|T], [Y|J]):-search([X|T], [], [Y|J]).
/*************Union of multitrees*************/

search2(X, [Y|J], [], D, Diff, NewList):-			
	(msequal(X,Y), search2(X, [], J, [], [], []);
	not(msequal(X,Y)), search2(X,J,[Y], D, Diff,NewList)), !.

search2(X, [Y|J], [A|B], D, Diff, NewList):-
	(msequal(X,Y), append(J, [A|B], N), search2(X, [], N, [], [], []);		
	not(msequal(X,Y)), append([Y], [A|B], N), search2(X, J, N, D,Diff, NewList)),!.

search2(X, [], [A|B], D, Diff, NewList):-		
	Diff=D, NewList=[A|B].

findDiff([X|T], [Y|J], [], I):-				
	(msequal(X,Y), findDiff(T, J, [], I);
	not(msequal(X,Y)), search2(X, [Y|J], [], [X], Diff , NewList), findDiff(T, NewList, Diff, I)), !.

findDiff([X|T], [Y|J], D, I):-
	(msequal(X,Y), findDiff(T, J, D, I);
	not(msequal(X,Y)), search2(X, [Y|J], [], [X], Diff , NewList), append(Diff, D, R), findDiff(T, NewList, R, I)), !.

findDiff([],_,D,I):-
	I=D.

msunion([X|T], [Y|J], R):-			
	findDiff([Y|J], [X|T], [] , I) , append([X|T], I, R).



