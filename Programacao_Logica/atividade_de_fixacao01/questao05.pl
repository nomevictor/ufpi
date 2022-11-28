conversao(V, UI, UF, R):-
    UI = kg, UF = mg,
    R is V * 1000000,!.
conversao(V, UI, UF, R):-
    UI = mg, UF = kg,
    R is V / 1000000,!.
conversao(V, UI, UF, R):-
    UI = kg, UF = cg,
    R is V * 100000,!.
conversao(V, UI, UF, R):-
    UI = cg, UF = kg,
    R is V / 100000,!.
conversao(V, UI, UF, R):-
    UI = cg, UF = mg,
    R is V * 10,!.
conversao(V, UI, UF, R):-
    UI = mg, UF = cg,
    R is V / 10.
    