# gtav-cpp-utils
Useful classes for developing ASI plugins using Script Hook V

## MenuV
A small library to create simple menus. It supports various item types:
- Simple text
- Configurable key (once the item is selected, user can set a different key for this item)
- Configurable value (user can enter a custom value on select)
- Options set (user can scroll through defined options)

Example usage can be found in `menuv/example/script.cpp`

## INI Settings
This simple class is using boost library (http://www.boost.org/) for parsing .ini configuration files.

Example usage:
```cpp
Settings settings;
settings.load("MarkExecute.ini");

// If the file doesn't exist or is empty, we can set default options.
// Jeżeli plik nie istnieje lub jest pusty, możemy zapisać domyślne ustawienia.
if(settings.getOptions().size() == 0)
{
  settings.setOption("MarkExecute", "menuKey", "F3");
  settings.setOption("MarkExecute", "markKey", "X");
  settings.setOption("MarkExecute", "executeKey", "E");
  settings.setOption("MarkExecute", "markAllOnHold", "true");
  settings.setOption("MarkExecute", "targetsLimit", "5");
  settings.setOption("MarkExecute", "killCam", "Random");
  
  settings.save();
}

string menuKey = settings.getOption("menuKey");
bool markAllOnHold = settings.getOptionBool("markAllOnHold");
```
