# Smart-pot-Web-app

## Cel projektu
  Celem projektu jest stworzenie systemu umożliwiającego automatyzację nawadniania kwiatów. Będzie on kontrolowany przez czujniki wilgotności gleby oraz natężenia światła. W określonych warunkach ma uruchamiać się moduł nawadniający. Parametry systemu oraz komunikaty o warunkach panujących w pobliżu rośliny będą pokazywane za pomocą aplikacji Webowej, wysyłane w formie powiadomienia na pocztę e-mail oraz wyświetlane na wyświetlaczu dołączonym do układu. Jedyna wymagana ingerencja użytkownika ma polegać na uzupełnianiu zbiornika z wodą oraz ewentualnej zmianie domyślnych ustawień.



## Wymagania funkcjonalne
  Celem układu jest kontrolowanie wilgotności gleby w doniczce oraz natężenia światła w pobliżu rośliny za pomocą odpowiednich czujników. W przypadku, gdy wilgotność gleby spadnie poniżej określonego poziomu, uruchomiona zostanie mała pompka wodna. System zawiera także czujnik odległości. Umieszczony powinien być on nad zbiornikiem z wodą w celu określenia poziomu wody. Aktualne parametry oraz informacje o podlaniu rośliny wyświetlane są w aplikacji Webowej, na wyświetlaczu oraz wysyłane do użytkownika w postaci powiadomienia na skrzynkę mailową. Układ zbudowany jest na bazie mikroprocesora ESP32. Zasilany jest sieciowo, a w przypadku braku prądu, bateryjnie.



## Obsługa
### Urządzenie
  System jest prosty w obsłudze i może pracować bez większej ingerencji ze strony użytkownika przez okres czasu ograniczony przez pojemność używanego naczynia z wodą oraz, w przypadku braku prądu, pojemność i poziom naładowania ogniwa. 
Aby układ działał prawidłowo, należy upewnić się czy wszystkie części są podłączone prawidłowo. Następnie czujnik wilgotności oraz silikonową rurkę od pompki należy wbić do gleby w doniczce z rośliną, a samą pompkę zanurzyć w naczyniu z wodą do podlewania kwiatów. Bezpośrednio nad naczyniem z wodą należy zamontować czujnik odległości. Czujnik natężenia światła ułożyć w takiej pozycji, aby bez zakłóceń monitorował stopień nasłonecznienia rośliny (nie układać pod przedmiotami, które zaburzają dostęp światła do czujnika np. pod parapetem). W celu uzyskania dostępu do aplikacji webowej, pozwalającej zdalnie sterować urządzeniem oraz w celu otrzymywania powiadomień e-mail niezbędne jest także przygotowanie urządzenia zapewniającego połączenie internetowe poprzez Wi-Fi. Następnie należy podłączyć urządzenie do prądu oraz koszyka z ogniwem. Jeśli wszystko zostało podłączone prawidłowo zaświeci się wyświetlacz LCD, pokazujący najpierw stan połączenia z internetem oraz adres IP, który należy wpisać w przeglądarce internetowej, a następnie aktualne parametry. Na e-mail zostanie wysłane powiadomienie o uruchomieniu urządzenia, a następnie co ustalony czas wysyłane będą powiadomienia z aktualnymi parametrami lub powiadomienia o włączeniu pompy wodnej.

### Aplikacja Webowa
  Aplikacja Webowa umożliwia sterowanie urządzeniem oraz monitorowanie jego aktualnego stanu z dowolnej przeglądarki internetowej. Warunkiem działania tej funkcji jest podłączenie urządzenia do tej samej sieci Wi-Fi co mikroprocesor. Adresem storny jest IP urządzenia, wyświetlane na ekranie LCD podczas jego uruchamiania. 
Za pomocą aplikacji użytkownik może włączyć lub wyłączyć “tryb wyjazdowy (“away mode”), który odpowiada za wysyłanie powiadomień o aktualnym stanie rośliny za pomocą wiadomości e-mail. Istnieje możliwość ustawienia ich częstotliwości. Kolejną funkcją jest możliwość manualnego włączania oraz wyłączania pompki wodnej. Aby przełączyć się na manualne sterowanie pompką wodna należy ustawić minimalny pozom wilgotności na 0. W aplikacji wyświetlane parametry czujników w czasie rzeczywistym. Został zaimplementowany suwak do ustawiania minimalnego poziomu wilgotności gleby w doniczce, przy którym uruchamia się moduł nawadniający.

