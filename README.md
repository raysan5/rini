<img align="left" src="https://github.com/raysan5/rini/blob/main/logo/rini_256x256.png" width=256>

**rini is a simple and easy-to-use config init files reader and writer**

`rini` is provided as a self-contained portable single-file header-only library with no external dependencies. 
Its only dependency, the standard C library, can also be replaced with a custom implementation if required.

Multiple configuration options are available through `#define` values.

<br>
<br>
<br>

## features

 - Config files reading and writing
 - Supported value types: int, string
 - Support comment lines and empty lines
 - Support custom line comment delimiter
 - Support custom value delimiters
 - Support value description comments
 - Support custom description custom delimiter
 - Support multi-word text values w/o quote delimiters
 - Minimal C standard lib dependency (optional)
 - Customizable maximum config values capacity

## configuration

`#define RINI_IMPLEMENTATION`

Generates the implementation of the library into the included file.
If not defined, the library is in header only mode and can be included in other headers
or source files without problems. But only ONE file should hold the implementation.

`#define RINI_MAX_CONFIG_CAPACITY`

Define the maximum capacity of config data structure, customizable by user.
Default value: 32 entries support

`#define RINI_LINE_COMMENT_DELIMITER`

Define character used to comment lines, placed at beginning of line
Most .ini files use semicolon ';' but '#' is also used
Default value: '#'

`#define RINI_LINE_SECTION_DELIMITER`

Defines section lines start character
Sections loading is not supported, lines are just skipped for now

`#define RINI_VALUE_COMMENTS_DELIMITER`

Defines a property line-end comment delimiter
This implementation allows adding inline comments after the value.
Default value: '#'

`#define RINI_VALUE_DELIMITER`

Defines a key value delimiter, in case it is defined.
Most .ini files use '=' as value delimiter but ':' is also used or just whitespace
Default value: ' '

`#define RINI_VALUE_QUOTATION_MARKS`

Defines quotation marks to be used around text values 
Text values are determined checking text with atoi(), only for integer values,
in case of float values they are always considered as text
Default value: '\"'

`#define RINI_DESCRIPTION_DELIMITER`

Defines a property line-end comment delimiter
This implementation allows adding inline comments after the value.
Default value: '#'
 
## basic functions

```c
// Load/unload config from file (*.ini) or create a new config object (pass NULL)
rini_config rini_load_config(const char *file_name);            
void rini_unload_config(rini_config *config);

// Save config to file, with custom header (if provided)
// NOTE: Only full config file rewrite supported, no partial updates
void rini_save_config(rini_config config, const char *file_name);

// Get config value int/text/description for provided key, returns -1 or NULL if not found
int rini_get_config_value(rini_config config, const char *key);
const char *rini_get_config_value_text(rini_config config, const char *key); 
const char *rini_get_config_value_description(rini_config config, const char *key);

// Set config value int/text and description for existing key or create a new entry
// NOTE: When setting a text value, if id does not exist, a new entry is automatically created
int rini_set_config_value(rini_config *config, const char *key, int value, const char *desc);
int rini_set_config_value_text(rini_config *config, const char *key, const char *text, const char *desc); 

// Set config value description for existing key
// WARNING: Key must exist to add description, if a description exists, it is updated
int rini_set_config_value_description(rini_config *config, const char *key, const char *desc); 
```

## limitations

 - Config `[sections]` not supported
 - Saving config file requires complete rewrite

## usage example

Load an existing config file
```c
#define RINI_IMPLEMENTATION
#include "rini.h"

int main()
{
    rini_config config = rini_load_config("config.ini");

    int show_window_sponsors_value = rini_get_config_value(config, "SHOW_WINDOW_SPONSORS");
    int show_window_info_value = rini_get_config_value(config, "SHOW_WINDOW_INFO");
    int show_window_edit_value = rini_get_config_value(config, "SHOW_WINDOW_EDIT");
    int image_scale_filter_value = rini_get_config_value(config, "IMAGE_SCALE_FILTER");
    int image_background_value = rini_get_config_value(config, "IMAGE_BACKGROUND");
    int visual_style_value = rini_get_config_value(config, "VISUAL_STYLE");
    int clean_window_mode_value = rini_get_config_value(config, "CLEAN_WINDOW_MODE");

    rini_unload_config(&config);

    return 0;
}
```

Save a custom config file:
```c
#define RINI_IMPLEMENTATION
#include "rini.h"

int main()
{
    // Create empty config with 32 entries (RINI_MAX_CONFIG_CAPACITY)
    rini_config config = rini_load_config(NULL);

    // Define header comment lines
    rini_set_config_text(&config, NULL, RINI_LINE_COMMENT_DELIMITER, "Initialization configuration options");
    rini_set_config_text(&config, NULL, RINI_LINE_COMMENT_DELIMITER, NULL);
    rini_set_config_text(&config, NULL, RINI_LINE_COMMENT_DELIMITER, "NOTE: This file is loaded at application startup,");
    rini_set_config_text(&config, NULL, RINI_LINE_COMMENT_DELIMITER, "if file is not found, default values are applied");
    rini_set_config_text(&config, NULL, RINI_LINE_COMMENT_DELIMITER, NULL);

    // Define config values
    rini_set_config_value(&config, "SHOW_WINDOW_SPONSORS", 1, "Show sponsors window at initialization");
    rini_set_config_value(&config, "SHOW_WINDOW_INFO", 0, "Show image info window");
    rini_set_config_value(&config, "SHOW_WINDOW_EDIT", 0, "Show image edit window");
    rini_set_config_value(&config, "IMAGE_SCALE_FILTER", 1, "Image scale filter enabled: 0-Point, 1-Bilinear");
    rini_set_config_value(&config, "IMAGE_BACKGROUND", 0, "Image background style: 0-None, 1-Checked, 2-Black, 3-Magenta");
    rini_set_config_value(&config, "VISUAL_STYLE", 2, "UI visual style selected: 0-9");
    rini_set_config_value(&config, "CLEAN_WINDOW_MODE", 0, "Clean window mode enabled");

    rini_save_config(config, "config.ini", ini_header);

    rini_unload_config(&config);
    
    return 0;
}
```

## license

rini is licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
