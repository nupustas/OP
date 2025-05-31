### Žodžių skaičiuoklė, ir nuorodų išrinkėjas
#### Ši programa suskaičiuoja pasikartojančių žodžių skaičių, bei išrenka nuorodas iš jūsų įvesto teksto.

## Projekto instrukcija
* Nukopijuokite norimą tekstą į **tekstas.txt** failą
* Paleiskite programą, naudojant **cmake**
* Programa suras pasikartojančiu žodžius bei nuorodas ir atspausdins **zodziai.txt** ir **nuorodos.txt** failuose, kurie yra **../op/build/release** kataloge.

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

##### 3. Projekto kompiliavimas:
```
mkdir build
cd build
cmake ..
```
```
cmake --build . --config Release
```
##### 4. Projekto paleidimas:
```
cd release
main.exe
```

## Paleidimas naudojant setup.exe
* Parsisiųskite **setup.exe** failą iš github repozitorijos
* Paleiskite **setup.exe** failą
* Sekite ekrane rodomas diegimo instrukcijas
* Įdiegę **setup.exe** darbalaukyje atsiras nuoroda paleisti programą
* Programą paleidinėkite administratoriaus būdu
* Projektas bus įdiegtas čia: C:\Program Files (x86)\VU\Zodziai

