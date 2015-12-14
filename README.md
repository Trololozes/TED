# TED - Text EDitor

##Todo
- [x] Qt 5.5, lançado em 01/07
- [x] Criar projeto base
- [x] Planejar features
- [x] Parar de enrolar e começar a bombar código na parada
- [x] Arrumar estruturação do projeto
- [x] Remover arquivos desnecessarios
- [x] Criar branch develop (master deve ser sempre compilável e executável)
- [x] Criar lista de funcionalidades básicas
- [ ] NÃO começar o desenvolvimento de features adicionais antes de TODAS as features básicas estarem funcionais
- [x] Adicionar License (LGPL Obrigatória -> Qt Open Source)
- [x] Adicionar instruções de compilação nas plataformas alvo (win, linux, mac(?))


##Instruções de Compilação

####MinGW

Para compilar certifique-se de ter:
- Qt 5.5
- libgcrypt
- GNU make
- GCC (g++)

1. Gere um Makefile a partir do arquivo TED.pro
```
qmake TED.pro
```

2. Para compilar o programa é simples:
```
make
```

3. O executável está dentro da pasta `bin`.


###### Repositório apenas para o código do ted, nada mais!
