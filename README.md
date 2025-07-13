# Inofficial Xournalpp Pluigin Hub

This is an Idea for the Pluigin Hub Repository for Xournal++


## Directories

```
pluigin-data-pull
-> a python script which collects the pluigin data to make it faster readable
   for a client software

pluigin-registration
-> to registrate new pluigins

pluigins
-> to store code for xournalpp pluigins
```

## Pluigin Structure

Your pluigin musst have a 
```
index.json
```
file in the root directory *(as well as the standard `pluigin.ini` and lua files)*

**The Content of this file looks like this:**

```json
{
    "name": "",
    "namespace": "",
    "author": "",
    "description": "",
    "available_for": [
        "1.2.7"
    ],
    "other_versions": [
        {
            "available_for": [
                "1.2.6"
            ],
            "link": "source code link"
        }
    ]
}
```

**namespace** MUSST be same as your json file in `pluigin-resgistration`,
else it does not work!

You can of course add multiple **other versions** and multiple versions
to **available_for**


## Registration

How to registrate a pluigin?

1. Your pluigin must have the files mentioned above

2. open the `pluigin-registration` folder

3. create a new json file the name of your pluigin and paste this:

```json
{
    "main_link": ""
}
```

4. add the link

---

See here [github.com/xournalpp/xournalpp/issues/3839](https://github.com/xournalpp/xournalpp/issues/3839)


## License

the license is MIT except for the directories where another license is located,
this license applies of course although for the subdirectories of directory.
