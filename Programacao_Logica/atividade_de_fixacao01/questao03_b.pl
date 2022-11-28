maioresMP(X1, X2, X3, X4, M, 3):-
    (X1 > M, X2 > M, X3 > M);
    (X1 > M, X2 > M, X4 > M);
    (X2 > M, X3 > M, X4 > M);
    (X2 > M, X3 > M, X4 > M),!.
maioresMP(X1, X2, X3, X4, M, 2):-
    (X1 > M, X2 > M);
    (X1 > M, X3 > M);
    (X1 > M, X4 > M);
    (X2 > M, X1 > M);
    (X2 > M, X3 > M);
    (X2 > M, X3 > M);
    (X3 > M, X1 > M);
    (X3 > M, X2 > M);
    (X3 > M, X4 > M);
    (X4 > M, X1 > M);
    (X4 > M, X2 > M);
    (X4 > M, X3 > M),!.
maioresMP(X1, X2, X3, X4, M, 1):-
    (X1 > M);
    (X2 > M);
    (X3 > M);
    (X4 > M).