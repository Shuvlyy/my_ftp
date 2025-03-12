# YML Parser

Basic YAML parser written in C.

## Usage

> [!WARNING]
> Every function not shown in this README is not for use.

### Creation

```c
char filepath[] = "file.yml";
yml_t *yml = yml_create_from_file(filepath);

/* Or... */

char yml_content[] = "name: Lysandre\n"
                     "age: 18\n"
                     "birth:\n"
                     "  year: 2006\n"
                     "  month:\n"
                     "    index: 7\n"
                     "    name: July"
                     "  day: 3\n"
                     "gpa: 3.20\n"
                     "hasCramptes: false\n";

yml_t *yml = yml_create_from_string(yml_content);
```

### 📰 Reading content (getters)

For now, only `int`, `float`, `bool` and strings (`char *`) are supported.

> [!TIP]
> Every value is de facto stored as a string (`char *`).

```c
yml *yml = ...; // Initialize your YML here

int birth_year = yml_get_int(yml, "birth.year"); // 2006
float gpa = yml_get_float(yml, "gpa"); // 3.20
char *name = yml_get_str(yml, "name"); // "Lysandre"
char *name = yml_get_str(yml, "hasCramptes"); // false

/* Error demonstration */
int month_name = yml_get_int(yml, "birth.month.name"); // "Error: "birth.month.name": Node type isn't valid"
float height = yml_get_float(yml, "height"); // "Error: "height": Node not found."
char *birth = yml_get_str(yml, "birth"); // "Error: "birth": Empty value"
```

> [!WARNING]
> If an error is encountered during reading, `0` (or `NULL`) is returned and an
> error is thrown in the `STDERR`.

### ✏️ Writing content (setters)

As for getters, only `int`, `float`, `bool` and strings (`char *`) are supported.

> [!TIP]
> A field type can change. If you set a float where a string was, it will now
> be a float!\
> Just be careful about your YML cohesion!

```c
yml *yml = ...; // Initialize your YML here

yml_set_int(yml, "age", 19); // Soon!!
yml_set_float(yml, "gpa", 4.0f);
yml_set_str(yml, "name", "Jolina");
yml_set_bool(yml, "hasCramptes", true); // 😊
```

### 💾 Saving your modifications

Just call the `yml_save(yml, filepath)` function, where `yml` is your yml
instance, and `filepath` the path where you want to save the file
(with the right extension: `.yml`!).

> [!CAUTION]
> Comments aren't kept.

### And finally...

Don't forget to destroy your YML instance when you are done with it!\
Just call the `yml_destroy(yml)` function, where `yml` is your yml instance.

## Time spent

Around 29 hours.\
My wakatime statistics aren't representative of my real time
spent, as it also counted my time spent on the MyRPG project in general.

### Made with 💜 by [Lysandre B.](https://www.github.com/shuvlyy)
