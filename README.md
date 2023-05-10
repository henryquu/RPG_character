# Instrukca
Program do tworzenia postaci RPG oraz modyfikacji jej ekwipunku.

## Po uruchomieniu program pyta się o sposób inicjalizacji postaci
### Dostępne opcje
1. Tworzenie nowej postaci
    Następuje przekerowanie do menu tworzenia postaci:
    - Podanie nazwy postaci (wymagane)
    - Wybór za pomocą radio buttonu:
        - rasy: człowiek, elf, ork
        - klasy: mag, łucznik, wojownik 

2. Wczytanie postaci z pliku 
    - podanie nazwy postaci z dostępnej listy oraz jej wczytanie z ekwipunkiem
    
Następnie przechodzimy do menu postaci

___

## Menu postaci
Zarządzania aktualną postacią.
### Dostępne opcje:
1. Zapis aktualnej postaci oraz jej ekwipunku w pliku.
2. Przejście do menu ekwipunku.
3. Powrót do głównego menu.

Po prawej stronie dostępny jest podgląd statystyk aktualnej postaci.

___

## Menu ekwipunku
Zarządzania aktualnym przedmiotem oraz możliwością tworzenia nowego przedmiotu.
### Dostępne opcje
1. Założenie / sciągnięcie przedmiotu.
2. Usunięcie aktualnego przedmiotu.
3. Stworzenie nowego przedmiotu oraz dodanie go do ekwipunku:
    - Podanie nazwy przedmiotu
    - Wybór typu przedmioty za pomocą radio buttonu
4. Pzejście do następnego przedmiotu w ekwipunku.
5. Powrót do Menu Postaci.

___

# Moduły

## inventory
**stuktura Item**
Zarządzanie ekwipunkiem -> linked_list z funkcjami:
- sumowanie wagi
- dodawanie elementów z zabezpieczeniem totalnej wagi
- sumowanie otrzymywanych statystyk
- usuwanie ekwipunku / pojedyńczych elementów
- generowanie przedmiotów

___

## characters
**Klasa Character**
Statystyki:
- Siła -> hp
- Inteligencja -> mana
- Zręczność -> szybkość ataku
- obrażenia (broń)
- zasięg    (broń)

Postacie, zarządzanie i tworzenie, funkcje:
- statystyki w oparciu o klasę i rasę
- inicjalizacja ekwipunku
- podawanie statystyk *całość (baza)*
- zapis + odczyt postaci w pliku (usuwanie starego wpisu postaci)
- możliwy tylko 1 przedmiot danego typu założony

___

## mainwindow
Interfejs graficzny.

___

## utils
Dodatkowe funkcje.
