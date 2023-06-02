# 1c-2023-metodos-tp2
Repo para el tp2 de métodos

## Instrucciones

### Crear el entorno e instalar dependencias.

0. Install conda: https://docs.conda.io/en/latest/miniconda.html
1. conda create -n metodos-tp2-env python=3.7
2. conda activate metodos-tp2-env
3. pip install -r requirements.txt

## Compilación

1. Ir al src 

```
cd 1c-2023-metodos-tp2/src
```

2. Compilar el programa

```
sh compile
``` 

## Correr el programa

```
./main (nombre_archivo_test) (niter) (eps)
```

## Ejemplo:

##### Entrada:
```
./main prueba_txt 100000 0.000001
```
##### Salida:
```
tests/prueba.txt_autovalores.out
tests/prueba.txt_autovectores.out
```


DUDAS:

- Eigenfaces de 2DPCA?
