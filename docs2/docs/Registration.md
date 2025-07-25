# Registrate

How to registrate a plugin?

1. Your pluigin must have the files mentioned above

2. open the `registration` folder

3. create a new json file the name of your pluigin and paste this:

```json
{
    "main_link": "example_file"
}
```

4. add the link


## Plugin Structure

Your plugin musst have a 
```
index.json
```
file in the root directory *(as well as the standard `plugin.ini` and lua files)*

**The Content of this file looks like this:**

```json
{
    "name": "noname_plugin",
    "namespace": "noname",
    "author": "Shadowdara",
    "description": "example file",
    "license": "MIT",
    "version": "1.0.1",
    "link": "",
    "available_for": [
        "1.2.7"
    ],
    "other_versions": [
        {
            "version": "1.0.0",
            "available_for": [
                "1.2.6"
            ],
            "link": "source code link"
        }
    ]
}
```

**namespace** MUSST be same as your json file in `registration`,
else it does not work!

You can of course add multiple **other versions** and multiple versions
to **available_for**

**Need an example?** Click [here](../example)
