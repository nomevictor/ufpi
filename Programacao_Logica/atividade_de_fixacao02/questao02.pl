multiplos3e7(I, F, M, R):-
    I =< F,
    R1 is I mod 3,
    R1 = 0,
    R2 is I mod 7,
    R2 = 0,
    M1 is M + 1,
    I2 is I + 1,
    multiplos3e7(I2, F, M1, R),!.
multiplos3e7(I, F, M, R):-
    I =< F,
    I2 is I + 1,
    multiplos3e7(I2, F, M, R),!.
multiplos3e7(_, _, M, R):-
    R is M.

somaMultiplos7(I, F, A, R):-
    I =< F,
    R1 is I mod 7,
    R1 = 0,
    I2 is I + 1,
    A2 is A + I,
    somaMultiplos7(I2, F, A2, R),!.
somaMultiplos7(I, F, A, R):-
    I =< F,
    I2 is I + 1,
    somaMultiplos7(I2, F, A, R),!.
somaMultiplos7(_, _, A, R):-
    R is A.

prod5Menores500(I, F, A, R):-
    I =< 500,
    I =< F,
    R1 is I mod 5,
    R1 = 0,
    A2 is A * I,
    I2 is I + 1,
    prod5Menores500(I2, F, A2, R),!.
prod5Menores500(I, F, A, R):-
    I =< 500,
    I =< F,
    I2 is I + 1,
    prod5Menores500(I2, F, A, R),!.
prod5Menores500(_, _, A, R):-
    R is A.

diferencaParesImpares(I, F, AP, AI, R):-
    I =< F,
    R1 is I mod 2,
    R1 = 0,
    AP2 is AP + I,
    I2 is I + 1,
    nl,
    diferencaParesImpares(I2, F, AP2, AI, R),!.
diferencaParesImpares(I, F, AP, AI, R):-
    I =< F,
    R1 is I mod 2,
    R1 =\= 0,
    nl,
    AI2 is AI * I,
    I2 is I + 1,
    diferencaParesImpares(I2, F, AP, AI2, R),!.
diferencaParesImpares(_, _, AP, AI, R):-
    R is AP - AI.
