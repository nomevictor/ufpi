calculo(A, B, R):-
    A > B,
    R is A ^ 3 + (A ^ 2 / B),!.
calculo(A, B, R):-
    A < B,
    R is (B ^ 2) * (2 * B - A),!.
calculo(A, B, R):-
    A = B,
    R is 3 * A + 2 * (A * B).