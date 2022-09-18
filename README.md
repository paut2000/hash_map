# Hast table
## Project structure
Шаблонный класс AbstractHash является родителем CCHash (Collision Chains, цепочки коллизий) и OAHash (Open Addressing, открытая адресация).
Класс List реализует структуру данных список, чтобы хранить коллизии в CCHash.
Шаблонный класс HashTable служит обёрткой для абстрактного класса и его наследников.

## Графики средней трудоёмкости в хэш-таблице с цепочками коллизий
![изображение](https://user-images.githubusercontent.com/48650232/190893151-97d17873-f4f0-4d72-97a7-71972d47f982.png)

## Графики средней трудоёмкости в хэш-таблице с открытой адресацией
![изображение](https://user-images.githubusercontent.com/48650232/190893154-bef76096-bbd3-486f-91ce-dfc9b9ea14a7.png)
