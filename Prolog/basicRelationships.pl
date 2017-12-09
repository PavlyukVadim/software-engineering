male('Vasil').
male('Dmytro').
male('Kolya').
male('Igor').
male('Anatoly').
male('Alexey').
male('Yevgeny').
male('Roman').
male('Peter').

female('Anya').
female('Nadia').
female('Olya').
female('Natalia').
female('Marina').
female('Oksana').

father('Vasil', 'Igor').
father('Vasil', 'Anatoly').
father('Dmytro', 'Marina').
father('Dmytro', 'Natalia').
father('Kolya', 'Oksana').
father('Igor', 'Alexey').
father('Igor', 'Yevgeny').
father('Alexey', 'Roman').
father('Alexey', 'Peter').

mother('Anya', 'Igor').
mother('Anya', 'Anatoly').
mother('Nadia', 'Marina').
mother('Nadia', 'Natalia').
mother('Olya', 'Oksana').
mother('Natalia', 'Alexey').
mother('Natalia', 'Yevgeny').
mother('Oksana', 'Roman').
mother('Oksana', 'Peter').

parent(X, Y) :- father(X, Y); mother(X, Y).
child(X, Y) :- father(Y, X); mother(Y, X).

son(X, Y) :- parent(Y, X), male(X).

daughter(X, Y) :- parent(Y, X), female(X).

brother(X, Y) :- parent(Z, X), parent(Z, Y), male(X).
%% brother('Alexey', 'Yevgeny').

sister(X, Y) :- parent(Z, X), parent(Z, Y), female(X).
%% sister('Marina', 'Natalia').

uncle(X, Y) :- brother(X, Z), parent(Z, Y).

aunt(X, Y) :- sister(X, Z), parent(Z, Y).

nephew(X, Y) :- uncle(Y, X), male(X); aunt(Y, X), male(X).

niece(X, Y) :- uncle(Y, X), female(X); aunt(Y, X), female(X).

grandfather(X, Y) :- parent(X, Z), child(Y, Z), male(X).
%% grandfather('Kolya', 'Roman').

grandmother(X, Y) :- parent(X, Z), child(Y, Z), female(X).

grandson(X, Y) :- grandfather(Y, X), grandmother(Y, X), male(X).
%% grandson('Roman', 'Kolya').

granddaughter(X, Y) :- grandfather(Y, X), grandmother(Y, X), female(X).

married(X, Y) :- child(Z, X), child(Z, Y).

hismotherinlaw(X, Y) :- married(Z, Y), daughter(Z, X), mother(X, Z).

hisfatherinlaw(X, Y) :- married(Z, Y), daughter(Z,X), father(X, Z).

hermotherinlaw(X, Y) :- married(Z, Y), son(Z, X), mother(X, Z).

herfatherinlaw(X, Y) :- son(Z, X), married(Z,Y), father(X, Z).

soninlaw(X, Y) :- married(X, Z), father(Z,Y).

daughterinlaw(X, Y) :- married(X, Z), son(Z, Y).

brotherinlaw(X, Y) :- married(X, Z), sister(Z, D), married(D, Y).

sisterinlaw(X, Y) :- sister(X, Z), married(Z, Y), sister(Z, X).

diver(X, Y) :- married(Y, Z), brother(X, Z).

greatnephew(X, Y) :- grandson(X, Z), parent(Q, Z), parent(Q, Y).

greatniece(X, Y) :- granddaughter(X, Z), parent(Q, Z), parent(Q, Y).
