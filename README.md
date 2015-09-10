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
- [x] Adicionar instruções de compilação nas plataformas alvo (win, linux, mac(?))


##Instruções de Compilação

####MinGW

Para compilar certifique-se de ter:
- Qt 5.5
- GNU make
- GCC (g++)

1. Deve-se criar um arquivo .pro com as configurações do projeto com o comando ``` qmake -project ```

2. Na linha de comando digite ``` qmake <nome_do_arquivo.pro> ``` para criar o makefile para a plataforma

3. Para compilar o programa é simples:
```
make
```

###### Repositório apenas para o código do ted, nada mais!
