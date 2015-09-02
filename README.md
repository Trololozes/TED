# TED - Text EDitor

##Todo
- [x] Qt 5.5, lançado em 01/07
- [ ] Criar projeto base
- [ ] Planejar features
- [ ] Parar de enrolar e começar a bombar código na parada
- [ ] Arrumar estruturação do projeto
- [x] Remover arquivos desnecessarios
- [x] Criar branch develop (master deve ser sempre compilável e executável)
- [ ] Criar lista de funcionalidades básicas
- [ ] NÃO começar o desenvolvimento de features adicionais antes de TODAS as features básicas estarem funcionais
- [x] Adicionar License (LGPL Obrigatória -> Qt Open Source)
- [ ] Adicionar instruções de compilação nas plataformas alvo (win, linux, mac(?))


##Instruções de Compilação

Para compilar certifique-se de ter:
- Qt 5.5
- GNU make

1. Deve-se criar um arquivo .pro com as configurações do projeto (será feito enquanto é desenvolvido), exempplo de arquivo .pro:

```
QT += widgets
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = textedit

HEADERS         = textedit.h
SOURCES         = textedit.cpp \
                  main.cpp

RESOURCES += textedit.qrc
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

EXAMPLE_FILES = textedit.qdoc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/textedit
INSTALLS += target
```

Na linha de comando digite:
```
qmake <nome_do_arquivo.pro>
make
```

###### Repositório apenas para o código do ted, nada mais!
