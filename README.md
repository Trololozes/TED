## TED - Text EDitor

__Um software de edição de texto com segurança criptográfica.__

Repositório apenas para o código do ted, nada mais!


## Instruções de Compilação
### Windows
#### MinGW

Para compilar certifique-se de ter:
- Qt 5.5 (versão com MinGW)
- libgcrypt

1. Gere um Makefile a partir do arquivo TED.pro
```
qmake TED.pro
```

2. Para compilar o programa é simples:
```
mingw32-make
```

3. O executável está dentro da pasta `bin`.
```
bin\TED.exe
```


Para evitar o trabalho de compilar das fontes, disponibilizamos as bibliotecas
criptográficas pré-compiladas aqui:  
[libgcrypt-libgpg-error.zip](https://www.dropbox.com/s/2nw0vdtcc5vd3mq/libgcrypt-libgpg-error.zip?dl=0)  
(md5sum: 0b416c02e9e293caa1dc4ca99a4210f0)

Descompacte o zip e coloque os arquivos nas respectivas pastas da sua versão do
MinGW.


---
### Linux

Pelo gerenciador de pacotes da sua distro, instale os pacotes `-dev` de:
- Qt 5.5
- libgcrypt
- libgpg-error

Tenha instalado também:
- Qt qmake
- GNU make
- GCC (g++)

1. Gere o Makefile
```
qmake TED.pro
```

2. Compile o programa
```
make
```

3. Executável pode ser encontrado na pasta `bin`
```
bin/TED
```
