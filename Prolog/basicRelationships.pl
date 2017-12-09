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

son(X, Y) :- parent(Y, X), male(X).

daughter(X, Y) :- parent(Y, X), female(X).
