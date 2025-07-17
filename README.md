# Inofficial Xournalpp Plugin Hub

This is an Idea for the Plugin Hub Repository for Xournal++


## TODO

- [ ] Branch Protection rules for PRs
- [ ] PR Templates
- [ ] update and make the Readme
- [ ] make the python script to merge the json
- [ ] make the client software to read the json
- [ ] write an good instruction how to add a pluigin
- [ ] make ISSUE Templates

**Anyone who want to help is welcome!**


<!-- ------------------------------------------ ---

Other TODO

- rename the Folders (shorter folder names)

---- ------------------------------------------ -->


<!--

Ascii banner
https://manytools.org/hacker-tools/ascii-banner/

'##::::'##::'######::'########:'##:::::::'########::'######:::'######::
 ##:::: ##:'##... ##: ##.....:: ##::::::: ##.....::'##... ##:'##... ##:
 ##:::: ##: ##:::..:: ##::::::: ##::::::: ##::::::: ##:::..:: ##:::..::
 ##:::: ##:. ######:: ######::: ##::::::: ######:::. ######::. ######::
 ##:::: ##::..... ##: ##...:::: ##::::::: ##...:::::..... ##::..... ##:
 ##:::: ##:'##::: ##: ##::::::: ##::::::: ##:::::::'##::: ##:'##::: ##:
. #######::. ######:: ########: ########: ########:. ######::. ######::
:.......::::......:::........::........::........:::......::::......:::
'####:'########::'########::::'###:::::'######::                       
. ##:: ##.... ##: ##.....::::'## ##:::'##... ##:                       
: ##:: ##:::: ##: ##::::::::'##:. ##:: ##:::..::                       
: ##:: ##:::: ##: ######:::'##:::. ##:. ######::                       
: ##:: ##:::: ##: ##...:::: #########::..... ##:                       
: ##:: ##:::: ##: ##::::::: ##.... ##:'##::: ##:                       
'####: ########:: ########: ##:::: ##:. ######::                       
....::........:::........::..:::::..:::......:::                       

Add a statistics server which counts plugins etc
- Count

with workflow or free hosting like nextjs idk

-->


## Directories

```
plugin-data-pull
-> a python script which collects the plugin data to make it faster readable
   for a client software

plugin-registration
-> to registrate new plugins

plugins
-> to store code for xournalpp plugins
```


## Registration

How to registrate a plugin?

1. Your pluigin must have the files mentioned above

2. open the `plugin-registration` folder

3. create a new json file the name of your pluigin and paste this:

[example_registration](example/example_registration.json)

4. add the link


## Plugin Structure

Your plugin musst have a 
```
index.json
```
file in the root directory *(as well as the standard `plugin.ini` and lua files)*

**The Content of this file looks like this:**

[example](example/example.json)

**namespace** MUSST be same as your json file in `plugin-resgistration`,
else it does not work!

You can of course add multiple **other versions** and multiple versions
to **available_for**


---

See here [github.com/xournalpp/xournalpp/issues/3839](https://github.com/xournalpp/xournalpp/issues/3839)


## License

the license is MIT except for the directories where another license is located,
this license applies of course although for the subdirectories of directory.
