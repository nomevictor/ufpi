formaTriangulo(A, B, C, 0):-
    (C > (B + A));
    (B > (A + C));
    (A > (B + C)),!.
formaTriangulo(_, _, _, 1).
