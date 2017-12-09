%% sum with step in d
sum(D, N, S) :- N =< D, S = N, !.
sum(D, N, S) :- Rest is N - D, sum(D, Rest, Sum), S is N + Sum.

executeSum :- sum(5, 200, S), write(S).


degree(A, 0, 1) :- !.
degree(A, 1, A) :- !.
degree(A, M, Res) :- M =< 0, OpM is (-M), degree(A, OpM, NewRes), Res is 1 / NewRes, !.
degree(A, M, Res):- (M mod 2) =:= 0, NewM is M / 2, degree(A, NewM, NewRes), Res is (NewRes * NewRes),!.
degree(A, M, Res) :- NewM is M - 1, degree(A, NewM, NewRes), Res is A * NewRes.

executeDegree :- degree(0.8551, -5, Res), write(Res).


%% sum of consecutive numbers from 0 to N
sumOfCon(S, E, 0) :- S is E, !.
sumOfCon(S, E, 0) :- S is E - 1, !.
sumOfCon(S, E, Sum) :- E >= S,
                     NewS is S + 1,
                     sumOfCon(NewS, E, NewSum),
                     Sum is NewS + NewSum.

executeSumOfCon :- sumOfCon(0, 40, Res), write(Res).
