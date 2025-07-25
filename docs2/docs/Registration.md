# Registrate

How to registrate a plugin?

1. Your pluigin must have the files mentioned above

2. open the `registration` folder

3. create a new json file the name of your pluigin and paste this:

[example_registration](example/registration.json)

4. add the link


## Plugin Structure

Your plugin musst have a 
```
index.json
```
file in the root directory *(as well as the standard `plugin.ini` and lua files)*

**The Content of this file looks like this:**

[example_index](example/index.json)

**namespace** MUSST be same as your json file in `registration`,
else it does not work!

You can of course add multiple **other versions** and multiple versions
to **available_for**

**Need an example?** Click [here](../example)
