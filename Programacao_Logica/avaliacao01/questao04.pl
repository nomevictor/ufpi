equacao(N, M, Resultado):-
    binarioToDecimal(M, 0, 0, MDecimal),
    Calculo is N ^ 2 * (3 * MDecimal),
    decimalToBinario(Calculo, Resultado).
    
binarioToDecimal(Binario, I, Acumulator, Decimal):-
    Binario >= 1,
    Resto is Binario mod 10,
    Binario2 is Binario // 10,
    I2 is I + 1,
    Acumulator2 is Acumulator + Resto * 2 ^ I,
    binarioToDecimal(Binario2, I2, Acumulator2, Decimal),!.
binarioToDecimal(_, _, Acumulator, Acumulator).

decimalToBinario(Decimal, Binario):-
    Decimal >= 2,
    Resto is Decimal mod 2,
    Decimal2 is Decimal // 2,
    decimalToBinario(Decimal2, Binario2),
    Binario is Binario2 * 10 + Resto,!.
decimalToBinario(Decimal, Decimal).