### Žodžių skaičiuoklė, ir nuorodų išrinkėjas
#### Ši programa suskaičiuoja pasikartojančių žodžių skaičių, bei išrenka nuorodas iš jūsų įvesto teksto.

## Projekto paleidimas naudojant CMake
#### 1. Reikalingi įrankiai
Prieš paleidžiant projektą, įsitikinkite, kad turite šiuos įrankius:

- **CMake**: [Atsisiųsti CMake](https://cmake.org/download/) (minimum v3.10)
- **C++ kompiliatorius** (GCC, CLANG, MSVC)

#### 2. Parsisiųskite projektą, jei jo dar neturite
##### Projekto klonavimas iš git:
```bash
git clone https://github.com/nupustas/OP
```
Paklonave projektą, atidarykite jo aplanką.

##### Projekto kompiliavimas:
```
mkdir build
cd build
cmake ..
```
```
cmake --build . --config Release
```
##### Projekto paleidimas:
```
cd release
main.exe
```

## Projekto instrukcija
* Nukopijuokite norimą tekstą į **tekstas.txt** failą
* Paleiskite programą, naudojant **cmake ..**
* Programa suras pasikartojančiu žodžius bei nuorodas ir atspausdins **zodziai.txt** faile, kuris yra **../op/build/release** kataloge.
