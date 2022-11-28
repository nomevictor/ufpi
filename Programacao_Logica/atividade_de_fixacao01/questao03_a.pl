mediaPonderada(X1, X2, X3, X4, P1, P2, P3, P4, M):-
    M is (X1 * P1 + X2 * P2 + X3 * P3 + X4 * P4) / (P1 + P2 + P3 + P4).