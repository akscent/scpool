# Инструкция по тестированию.

  Чтобы запустить проверку на стиль, выполните следующую команду: \
  ```clang-format -n src/sourcefile_name.c``` \
  \
  Чтобы скачать clang-format, введите в терминал одну из следующих команд: \
  ```brew install clang-format``` \
  или, если у вас есть root-права (для Ubuntu / Linux Mint / Debian) \
  ```sudo apt install clang-format```


 * **Статический анализ кода.** 
 Чтобы установить утилиту, введите в терминал одну из следующих команд: \
   ```brew install cppcheck``` \
   или, если у вас есть root-права (для Ubuntu / Linux Mint / Debian) \
   ```sudo apt install cppcheck``` \
   \
   Установив cppcheck, вы можете протестировать ваш исходный код: \
   ```cppcheck --enable=all --suppress=missingIncludeSystem soursefile_name.c``` \
   Также можно проверить сразу все файлы с исходным кодом в директории: \
   ```cppcheck --enable=all --suppress=missingIncludeSystem *.c *```
