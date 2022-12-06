produto(A, B, AC, I, R):-
    I < B,
    AC2 is AC + A,
    I2 is I + 1,
    produto(A, B, AC2, I2, R),!.
produto(_, _, AC, _, R):-
    R is AC.