bhaskara(A, B, C, [X1, X2]):-
    D is B ^ 2 - 4 * A * C,
    D > 0,
    X1 is ((- B + D ^ (1/2)) / (2 * A)),
    X2 is ((- B - D ^ (1/2)) / (2 * A)),!.
bhaskara(A, B, C, [X1, X2]):-
    D is B ^ 2 - 4 * A * C,
    D = 0,
    X1 is ((- B + D ^ (1/2)) / (2 * A)),
    X2 is ((- B + D ^ (1/2)) / (2 * A)),!.
bhaskara(_, _, _, _):-
    write("Nao possui raizes reais").