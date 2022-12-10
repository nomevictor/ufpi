cinema(CustoFilme, CustoSecao, ValorIngresso, QtdPessoasSecao, QtdSecao, QtdIngressos):-
    ValorBrutoSecao is QtdPessoasSecao * ValorIngresso * QtdSecao,
    CustoTotal is CustoFilme + (CustoSecao * QtdSecao),
    Lucro is ValorBrutoSecao - CustoTotal,
    Lucro =< 0,
    QtdSecao2 is QtdSecao + 1,
    cinema(CustoFilme, CustoSecao, ValorIngresso, QtdPessoasSecao, QtdSecao2, QtdIngressos),!.
cinema(_, _, _, QtdPessoasSecao, QtdSecao, QtdIngressos):-
    QtdIngressos is QtdSecao * QtdPessoasSecao.