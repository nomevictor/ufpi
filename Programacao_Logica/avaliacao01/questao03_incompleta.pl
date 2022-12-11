principal(Valor, Quadruplo, Multiplo):-
    quadruplo(Valor, 0, Quadruplo),
    multiplo(Quadruplo, 0, Multiplo).


quadruplo(Valor, I, Resultado):-
    I < 2,
    Valor2 is Valor + Valor,
    I2 is I + 1,
    quadruplo(Valor2, I2, Resultado),!.
quadruplo(Valor,_, Valor).


multiplo(Valor, I, Resultado):-
    Valor > 5,
    Valor > 0,
    Valor2 is Valor - 5,
    