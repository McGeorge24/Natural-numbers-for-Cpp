# Implementacija neskončno velikih števil v C++

## 1. Teoretične osnove

Pred začetkom je potrebno razumeti nekaj funkcionalnosti programskega jezika C++.
### 1.1. Objekti / razred / class
#### Deklaracija razreda izgleda tako:
```
class ImeRazreda {  
public:             
	int stevilka;
	string beseda;
	int Funkcija(int parameter);
};
```
`public:` nam pove kdo lahko dostopa, do sledeče kode. Pomeni da lahko do nje dostopajo vsi ostali razredi in funkcije.
Kot privzeto je `private:`, kar pomeni, da lahko sledečo kodo uporabljajo samo člani istega classa.
#### Definicija funkcij v razredu:
To lahko naredimo posebej ali pa skupaj z deklaracijo.

Posebej: 
```
int ImeRazreda::Funkcija(int parameter) {
	// program
}
```

Skupaj z deklaracijo:
```
class ImeRazreda {  
public:             
	int Funkcija(int parameter) {
	// program
	}
};
```
#### Operator overloading
To je funkcija v C++, ki omogoča, da lahko navadne operatorje uporabimo s svojimi razredi. Seveda se definicija drugačna za določene operatorje, v glavnem pa izgleda tako (za operator =):
```
InfiniteInt& operator=(const std::string& other) {
	// program
	return *this; // Return a reference to the current object
}
```
Ker operatorje obravnavamo kot funkcije, lahko tudi te 'overloadamo', tako kot funkcije. 'Function overloading' pa je možnost, da za funkcijo z istim imenom napišemo več definicij.
#### Konstruktorji in destruktorji
So funkcije, ki dejansko naredijo en primer tega razreda, torej novo spremenljivko. Definicija konstruktorja je drugačna od navadne funkcije, saj nimajo svojega tipa, ki stoji pred vsako funkcijo (int, string, void...):
```
InfiniteInt::InfiniteInt(const char *stevilo) {
	int i = 0;
	int length = strlen(stevilo);
	integer.reserve(length); // for better performance
	for (i = 0; i < length; i++) {
		integer.push_back(stevilo[length - 1 - i] - 48);
	}
};
```
Obstaja več vrst konstruktorjev, za ta projekt sta pomembna samo dva:
- navaden, ki inicializira (primer zgoraj),
- in Copy constructor, ki kopira podatke iz enega primera tega razreda v drugega.

Copy constructor je pomemben, če je med člani razreda kazalec na drug kos spomina. Ne želimo, da si dva primera istega objekta delita isti kos spomina. S Copy konstruktorjem lahko kopiramo računalniku povemo, da prekopira še ta kos spomina. Copy constructor izgleda tako:
```
InfiniteInt(InfiniteInt &ref) 
{
	integer = ref.integer;
}
```
V tem primeru se moj program zanaša na to, da ima razred `vector` že svoj copy konstruktor.

Destruktor pa poskrbi da se spomin pravilno sprosti. Spet je to pomembno, če je ena od spremenljivk samo kazalec. Moramo poskrbeti da se sprosti tudi ta spomin. Destruktor se zapiše enako kot konstruktor, vendar z '~' pred njim: `~InfiniteInt();`.

### 1.2. Simboli uporabljeni v C++
#### Simbol & in *
`Simbol &` lahko pomeni naslov določene spremenljivke. Uporabi se ga pred imenom spremenljivke:
```
int spremenljivka;
int* naslov_spremenljivke = &spremenljivka
```
Lahko pa pomeni samo referenco, (ki je tudi naslov spremenljivke v resnici), če ga uporabimo v tipu spremenljivke. Referenca ni svoja kopija spremenljivke. Če spreminjamo referenco spreminjamo tudi originalno spremenljivko.
```
int spremenljivka;
int& referenca_na_spremenljivko = spremenljivka;
```

`Simbol *` lahko pomeni množenje, lahko pa je tudi v zvezi s kazalci. Če zvezdico uporabimo v tipu, pomeni, da je to kazalec do tega tipa.
```
int* naslov_spremenljivke = &spremenljivka
```
Če pa zvezdico uporabimo pred tipom spremenljivke pa pomeni obratno operacijo od sklicevanja (reference) spremenljivke. Z to operacijo dobimo vrednost spremenljivke iz naslova
```
int spremenljivka = 123;
int * naslov_spemenljivke = &spremenljivka;
int kopija_spremenljivke = *naslov_spremenljivke; // kopija_spremenljivke = 123
```
#### Simbol ->
`Simbol ->` pomeni enako kot `. (pika`) pri klicanju funkcij objekta, vendar ga uporabljamo na kazalcih in ne na samih spremenljivkah. 
```
std::vector<int> seznam;
std::vector<int>* naslov_seznama = &seznam;

//Naslednji 2 vrstici kode sta ekvivalentni:
seznam.push_back(123);
naslov_seznama->push_back(123);
```
## 2. Upeljava
### 2.1 Shranjevanje števila
Odločil sem se, da bo število shranjeno v std::vector, iz 2 razlogov. Poiščem lahko vsako števko ter std::vector je seznam, ki se ga da povečati.
Števke so v v seznamu shranjene v obratnem vrstnem redu, saj je za seštevanje pomembno da so poravnane enice in ne števka, ki predstavlja največjo stopnjo.


## 3. Napredek
Kot mejo za dokončan projekt sem določil spodnje funkcije:
- [x] Inicializacija objekta s stringom,
- [ ] Inicializacija objekta z integerjem,
- [ ] Inicializacija objekta z operatorjem= (s stringom in integerjem),
- [x] Seštevanje dveh števil,
- [ ] Negativna števila,
- [ ] Odštevanje dveh števil,
- [ ] Množenje dveh števil (potencialno).


