quadruplo(Valor, I, Resultado):-
    I < 2,
    Valor2 is Valor + Valor,
    I2 is I + 1,
    quadruplo(Valor2, I2, Resultado),!.
quadruplo(Valor,_, Valor).

multiplo(Valor, Resultado):-
    Valor >= 5,
    Valor2 is Valor - 5,
    multiplo(Valor2, Resultado2),
    Resultado is Resultado2,!.
multiplo(Valor, Valor).

principal(Valor, Quadruplo, Multiplo):-
    quadruplo(Valor, 0, Quadruplo),
    multiplo(Quadruplo, ResultMultiplo),
    ResultMultiplo == 0,
    Multiplo = "Eh multiplo",!.
principal(_, _, Multiplo):-
    Multiplo = "Nao eh multiplo".