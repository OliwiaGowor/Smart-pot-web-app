# Smart pot

## Cel projektu
  Celem projektu jest stworzenie systemu umożliwiającego automatyzację nawadniania kwiatów. Będzie on kontrolowany przez czujniki wilgotności gleby oraz natężenia światła. W określonych warunkach ma uruchamiać się moduł nawadniający. Parametry systemu oraz komunikaty o warunkach panujących w pobliżu rośliny będą pokazywane za pomocą aplikacji Webowej, wysyłane w formie powiadomienia na pocztę e-mail oraz wyświetlane na wyświetlaczu dołączonym do układu. Jedyna wymagana ingerencja użytkownika ma polegać na uzupełnianiu zbiornika z wodą oraz ewentualnej zmianie domyślnych ustawień.



## Wymagania funkcjonalne
  Celem układu jest kontrolowanie wilgotności gleby w doniczce oraz natężenia światła w pobliżu rośliny za pomocą odpowiednich czujników. W przypadku, gdy wilgotność gleby spadnie poniżej określonego poziomu, uruchomiona zostanie mała pompka wodna. System zawiera także czujnik odległości. Umieszczony powinien być on nad zbiornikiem z wodą w celu określenia poziomu wody. Aktualne parametry oraz informacje o podlaniu rośliny wyświetlane są w aplikacji Webowej, na wyświetlaczu oraz wysyłane do użytkownika w postaci powiadomienia na skrzynkę mailową. Układ zbudowany jest na bazie mikroprocesora ESP32. Zasilany jest sieciowo, a w przypadku braku prądu, bateryjnie.



## Wykorzystane elementy
* Mikrokontroler FireBeetle ESP32-E
* Wyświetlacz Philips PCF8574 LCD 2x16 z konwerterem I2C LCM1602
* Ogniwo 18650 Li-Ion XTAR o pojemności 2200 mAh i napięciu nominalnym 3,7V
* Czujnik wilgotności gleby MOD-01588
* Czujnik natężenia światła LDR rezystancyjny – Okystar
* Czujnik odległości ultradźwiękowy HC-SR04
* Pompa wodna - mała, zanurzalna pompka wodną zasilana napięciem 3V – 6V
* Tranzystor bipolarny NPN 2N2222A
* Rezystor 2.2k Ohm



## Obsługa
### Urządzenie
  System jest prosty w obsłudze i może pracować bez większej ingerencji ze strony użytkownika przez okres czasu ograniczony przez pojemność używanego naczynia z wodą oraz, w przypadku braku prądu, pojemność i poziom naładowania ogniwa. 
Aby układ działał prawidłowo, należy upewnić się czy wszystkie części są podłączone prawidłowo. Następnie czujnik wilgotności oraz silikonową rurkę od pompki należy wbić do gleby w doniczce z rośliną, a samą pompkę zanurzyć w naczyniu z wodą do podlewania kwiatów. Bezpośrednio nad naczyniem z wodą należy zamontować czujnik odległości. Czujnik natężenia światła ułożyć w takiej pozycji, aby bez zakłóceń monitorował stopień nasłonecznienia rośliny (nie układać pod przedmiotami, które zaburzają dostęp światła do czujnika np. pod parapetem). W celu uzyskania dostępu do aplikacji webowej, pozwalającej zdalnie sterować urządzeniem oraz w celu otrzymywania powiadomień e-mail niezbędne jest także przygotowanie urządzenia zapewniającego połączenie internetowe poprzez Wi-Fi. Nazwę sieci, hasło oraz dane skrzynki mailowej należy uzupełnić w kodzie programu Następnie należy podłączyć urządzenie do prądu oraz koszyka z ogniwem. Jeśli wszystko zostało podłączone prawidłowo zaświeci się wyświetlacz LCD, pokazujący najpierw stan połączenia z internetem oraz adres IP, który należy wpisać w przeglądarce internetowej, a następnie aktualne parametry. Na e-mail zostanie wysłane powiadomienie o uruchomieniu urządzenia, a następnie co ustalony czas wysyłane będą powiadomienia z aktualnymi parametrami lub powiadomienia o włączeniu pompy wodnej.

### Aplikacja Webowa
  Aplikacja Webowa umożliwia sterowanie urządzeniem oraz monitorowanie jego aktualnego stanu z dowolnej przeglądarki internetowej. Warunkiem działania tej funkcji jest podłączenie urządzenia do tej samej sieci Wi-Fi co mikroprocesor. Adresem storny jest IP urządzenia, wyświetlane na ekranie LCD podczas jego uruchamiania. 
Za pomocą aplikacji użytkownik może włączyć lub wyłączyć “tryb wyjazdowy (“away mode”), który odpowiada za wysyłanie powiadomień o aktualnym stanie rośliny za pomocą wiadomości e-mail. Istnieje możliwość ustawienia ich częstotliwości. Kolejną funkcją jest możliwość manualnego włączania oraz wyłączania pompki wodnej. Aby przełączyć się na manualne sterowanie pompką wodna należy ustawić minimalny pozom wilgotności na 0. W aplikacji wyświetlane parametry czujników w czasie rzeczywistym. Został zaimplementowany suwak do ustawiania minimalnego poziomu wilgotności gleby w doniczce, przy którym uruchamia się moduł nawadniający.


## Oprogramowanie
Kod programu napisano w języku C++ oraz przy pomocy HTML, CSS i Javascript w przypadku części Webowej i  podzielony jest na 6 plików:

### Gsender.h
  Jest to plik nagłówkowy, który zawiera deklarację klasy Gsender.


### Gsender.cpp
  Ten kod definiuje klasę Gsender, która umożliwia wysyłanie wiadomości e-mail za pomocą protokołu SMTP. Oto najważniejsze fragmenty kodu:
* Metoda statyczna ```Instance()``` tworzy instancję klasy Gsender i zwraca wskaźnik do niej. Wykorzystuje wzorzec Singleton, aby upewnić się, że istnieje tylko jedna instancja klasy Gsender.
* Metoda ```Subject(const char* subject)``` ustawia temat wiadomości. Usuwa poprzedni temat (jeśli istniał) i alokuje pamięć dla nowego tematu.
* Metoda ```AwaitSMTPResponse(WiFiClientSecure &client, const String &resp, uint16_t timeOut)``` oczekuje na odpowiedź serwera SMTP. Sprawdza, czy klient otrzymuje odpowiedź od serwera w określonym czasie. Jeśli czas przekroczy limit, zwraca wartość false.
* Metoda ```getLastResponce()``` zwraca ostatnią otrzymaną odpowiedź serwera SMTP.
* Metoda ```getError()``` zwraca bieżący błąd (jeśli wystąpił) jako wskaźnik na stałą tablicę znaków.
* Metoda ```Send(const String &to, const String &message)``` jest główną metodą do wysyłania wiadomości e-mail. Tworzy połączenie z serwerem SMTP, autoryzuje się, ustawia nagłówki wiadomości, wysyła treść wiadomości i zamyka połączenie.


### Message.h
  Jest to plik nagłówkowy, który zawiera deklaracje funkcji sendInfo() i sendInfoPump().


### Message.cpp
  Ten kod zawiera dwie funkcje, ```sendInfo()``` i ```sendInfoPump()```, które wysyłają informacje przez e-mail. Oto opis najważniejszych fragmentów kodu:
* Funkcja ```sendInfo()``` przyjmuje jako parametry adres e-mail, wilgotność, poziom oświetlenia i odległość od czujnika. Tworzony jest ciąg znaków message, do którego dodawane są informacje o wilgotności, poziomie oświetlenia i odległości. Następnie tworzony jest obiekt klasy Gsender i wywoływana jest funkcja ```Send()```, która wysyła wiadomość e-mail z danymi.
* Funkcja ```sendInfoPump()``` przyjmuje jako parametry adres e-mail, stan pompy wodnej (włączona/wyłączona) i wilgotność. Podobnie jak w funkcji ```sendInfo()```, tworzony jest ciąg znaków message, do którego dodawane są informacje o stanie pompy wodnej i wilgotności. Następnie tworzony jest obiekt klasy Gsender i wywoływana jest funkcja ```Send()```, która wysyła wiadomość e-mail z danymi.

Obie funkcje korzystają z klasy Gsender, której instancja jest pobierana za pomocą metody ```Instance()```. Klasa Gsender prawdopodobnie implementuje funkcjonalność wysyłania wiadomości e-mail.

### index.h
  Jest to plik nagłówkowy zawierający deklarację strony internetowej, napisanej przy pomocy HTML, CSS oraz JavaScript jako tablica znaków typu char. Zawiera treść strony internetowej w formie tzw. "raw literal" (znak R"rawliteral(' na początku i ')rawliteral" na końcu). Dzięki temu wszystkie znaki wewnątrz ciągu są traktowane dosłownie, bez potrzeby ucieczek (backslashes) dla znaków specjalnych.
Istnieje kilka funkcji JavaScript zdefiniowanych w tagu <script>, które wykonują się po stronie przeglądarki:
* ```togglePump(element)``` oraz ```toggleAwayMode(element)``` to funkcje, które wykorzystują obiekt XMLHttpRequest do wysłania żądania HTTP GET na odpowiednie ścieżki (/pump?state=1 lub /pump?state=0, /awayMode?state=1 lub /awayMode?state=0) w zależności od stanu przekazanego elementu (np. checkboxa). Wysyłając takie żądania, można włączać i wyłączać pompę lub tryb "away mode".
* ```setAwayModeInterval()``` oraz ```setMinHumidity()``` funkcje te wykorzystują XMLHttpRequest do wysłania żądania HTTP GET na odpowiednią ścieżkę (/setHumidity?value=<wartość>) z wartością odczytaną z pewnych elementów na stronie. W ten sposób można ustawić pewne parametry, takie jak interwał trybu "away mode" czy minimalną wilgotność.
* Trzy interwały (```setInterval(...)```) to fragmenty kodu JavaScript, które regularnie (co 2000 ms) wykonują żądania HTTP GET na różne ścieżki (/lightLvl, /humidity, /distance) i aktualizują zawartość odpowiednich elementów na stronie, takich jak poziom światła, wilgotność czy odległość.

### smartPot.ino
  Ten kod jest głównym programem dla mikrokontrolera ESP. Oto najważniejsze fragmenty kodu:
* Zdefiniowana stała ```SOUND_SPEED``` reprezentuje prędkość dźwięku w centymetrach na mikrosekundę.
* Zdefiniowane zmienne globalne, takie jak ```ssid``` i ```password```, które przechowują nazwę sieci WiFi i hasło, ```connection_state``` przechowuje stan połączenia, a ```reconnect_interval``` określa czas oczekiwania przed kolejną próbą połączenia z siecią WiFi. Innymi zmiennymi globalnymi są prędkość dźwięku (```SOUND_SPEED```), parametry wejściowe (```PARAM_INPUT_VALUE```, ```PARAM_INPUT_STATE```), minimalna wilgotność (```minHumidity```), czas trwania (w mikrosekundach) sygnału ultradźwiękowego w czujniku odległości (```duration```), interwały czasowe w programie (```counter```) zmienna (```awayMode```), która określa, czy tryb "away mode" jest aktywowany, interwał (w milisekundach) dla trybu "away mode" (```awayModeInterval```)
* Zainicjalizowany obiekt klasy ```LiquidCrystal_I2C``` do obsługi wyświetlacza LCD.
* Zainicjalizowany obiekt klasy ```AsyncWebServer``` o nazwie server nasłuchujący na porcie 80, co umożliwia obsługę żądań HTTP od przeglądarek internetowych.
* Funkcja ```checkHumidity()``` sprawdza poziom wilgotności. Jeśli jest zbyt niski, włącza pompę wodną i wyświetla informacje na wyświetlaczu LCD. Co jakiś czas wysyła również informację o pompie wodnej.
* Funkcja ```getLight()``` odczytuje poziom oświetlenia i zwraca odpowiednią wartość (ciemno, średnio, jasno).
* Funkcja ```getDistance()``` mierzy odległość przy użyciu czujników ultradźwiękowych i zwraca wynik w centymetrach.
* Funkcja ``````displayLight() wyświetla poziom oświetlenia na wyświetlaczu LCD i zwraca wartość jako ciąg znaków.
* Funkcja ```processor()``` zastępuje miejsca zastępcze w kodzie HTML strony internetowej. Wstawia dane dynamiczne, takie jak stan trybu "away mode", poziom światła, wilgotność, odległość, stan pompki wodnej czy aktualny minimalny poziom wilgotności.
* Funkcja ```handleAwayMode()``` obsługuje tryb "away mode" poprzez wysyłanie powiadomień na podstawie ustawionego interwału.
* Funkcja ```WiFiConnect()``` nawiązuje połączenie z siecią WiFi na podstawie podanych nazwy SSID i hasła. Jeśli nie zostaną podane, używa domyślnych wartości.
* Funkcja ```Awaits()``` oczekuje na połączenie z siecią WiFi, jeśli nie jest już nawiązane, w pętli próbuje ponownie połączyć się co pewien czas.
* W funkcji ```setup()``` inicjalizowane są różne ustawienia, takie jak komunikacja szeregowa, piny wejściowe/wyjściowe, połączenie WiFi. Następnie tworzony jest obiekt Gsender (klasy do wysyłania wiadomości e-mail) i wysyłana jest wiadomość testowa. Konfiguruje ona także endpointy obsługujące różne żądania HTTP.
* W funkcji ```loop()``` odbywa się główna pętla programu. Sprawdzane są parametry roślin (wilgotność, poziom oświetlenia, odległość od czujnika) i wyświetlane na wyświetlaczu LCD. Odbywa się także obsługa trybu “away mode”.

Kod korzysta również z funkcji pomocniczych, takich jak sendInfoPump() i sendInfo(), które wysyłają wiadomości e-mail z informacjami o pompie wodnej oraz parametrach roślin.

