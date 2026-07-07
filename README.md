# Zaawansowany-kalkulator-konsolowy
Konsolowy kalkulator napisany w C++, umożliwiający obliczanie wyrażeń matematycznych z obsługą nawiasów, priorytetów operatorów, potęgowania, pierwiastka kwadratowego oraz historii obliczeń zapisywanej do pliku. Program wykorzystuje stosy (`stack`) do analizy i wykonywania działań oraz obsługuje podstawowe błędy.
# Kalkulator Wyrażeń Matematycznych (C++)

## 📌 Opis projektu

Jest to prosty kalkulator konsolowy napisany w języku **C++**, umożliwiający obliczanie złożonych wyrażeń matematycznych z zachowaniem priorytetów operatorów oraz nawiasów. Program zapisuje historię wykonanych obliczeń do pliku tekstowego i pozwala na jej przeglądanie oraz usuwanie.

Projekt został wykonany z wykorzystaniem stosów (`stack`) do analizy i obliczania wyrażeń matematycznych.

---

## ✨ Funkcjonalności

* wykonywanie działań matematycznych:

  * dodawanie (`+`)
  * odejmowanie (`-`)
  * mnożenie (`*`)
  * dzielenie (`/`)
  * reszta z dzielenia (`%`)
  * potęgowanie (`^`)
  * pierwiastek kwadratowy (`sqrt()`)
* obsługa liczb ujemnych
* obsługa nawiasów okrągłych `()` oraz kwadratowych `[]`
* zachowanie priorytetów operatorów
* wykrywanie błędów składni wyrażeń
* zapisywanie historii obliczeń do pliku `historia.txt`
* przeglądanie historii obliczeń
* usuwanie historii obliczeń

---

## 🖥️ Menu programu

Po uruchomieniu użytkownik może wybrać jedną z opcji:

1. Obliczenie nowego wyrażenia
2. Wyświetlenie historii obliczeń
3. Usunięcie historii
4. Zakończenie programu

---

## 📖 Przykładowe działania

```text
2+5*4
```

Wynik:

```text
22
```

---

```text
(8+2)*5
```

Wynik:

```text
50
```

---

```text
sqrt(81)
```

Wynik:

```text
9
```

---

```text
2^5
```

Wynik:

```text
32
```

---

## ⚠️ Obsługiwane błędy

Program informuje użytkownika o niepoprawnych danych wejściowych, między innymi:

* dzielenie przez zero,
* pierwiastek z liczby ujemnej,
* nieznana funkcja,
* błędne nawiasy,
* brak operatora,
* zbyt mała liczba argumentów,
* niedozwolone znaki.

---

## 🛠️ Wykorzystane technologie

* C++
* Standard Template Library (STL)

  * `stack`
  * `vector`
  * `string`
  * `fstream`

---

## 📂 Struktura projektu

```text
├── main.cpp
├── historia.txt
└── README.md
```


