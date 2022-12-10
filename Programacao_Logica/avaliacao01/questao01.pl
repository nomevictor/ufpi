impostoDevido(SalarioBrutoMensal, ImpostoPagoMensal, Imposto, Restituicao):-
    SalarioBrutoAnual is SalarioBrutoMensal * 12,
    ImpostoPagoAnual is ImpostoPagoMensal * 12,
    BaseCalculo is SalarioBrutoAnual - (SalarioBrutoAnual * 0.2),
    aliquota(BaseCalculo, Aliquota),
    Aliquota =\= 0,
    Imposto is BaseCalculo * Aliquota,
    Restituicao is Imposto - ImpostoPagoAnual,!.
impostoDevido(SalarioBrutoMensal, _, Imposto, Restituicao):-
    write('Isento de impostos!'), nl,
    Restituicao is SalarioBrutoMensal * 12,
    Imposto is 0.


aliquota(BaseDeCalculo, Aliquota):-
    BaseDeCalculo > 65000,
    Aliquota is 0.295,!.
aliquota(BaseDeCalculo, Aliquota):-
    BaseDeCalculo >= 55000, BaseDeCalculo =< 65000,
    Aliquota is 0.295,!.
aliquota(BaseDeCalculo, Aliquota):-
    BaseDeCalculo >= 45000, BaseDeCalculo =< 55000,
    Aliquota is 0.295,!.
aliquota(BaseDeCalculo, Aliquota):-
    BaseDeCalculo >= 35000, BaseDeCalculo =< 45000,
    Aliquota is 0.295,!.
aliquota(BaseDeCalculo, Aliquota):-
    BaseDeCalculo =< 35000,
    Aliquota is 0.
