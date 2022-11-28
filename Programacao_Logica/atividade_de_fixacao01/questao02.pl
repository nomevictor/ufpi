mult(X, 1):-
    R1 is X mod 2,
    R1 = 0,
    R2 is X mod 7,
    R2 = 0,!.
mult(_,0).