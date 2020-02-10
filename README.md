# Mathematics

Tasks solved during my degree numerical and maybe analytical at some point. 

We mainly use matlab but I want to get better at C, I've therefore started to implement
the tasks I've gotten using C. 

### Complex Number

z^n = a + ib

```
gcc -o complex -lm main.c
```

to run the program use the following

```
./complex n a b // Where n is the power, a is the real number and b is the imaginary part
```

### Hanoi

Calculates the amount of moves needed to complete the game.

```
gcc -o hanoi main.c
```

to run the program use the following

```
./hanoi n // Where n is the number of blocks in the hanoi tower. 
```

### RREF (Reduced Row Echelon Form)

Calucluates the reduced row echelon form
```
gcc -o rref -lm main.c
```

to run the program use the following
```
./rref file.extension row col // where row is the number of rows and col is the number of cols
```
