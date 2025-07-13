-- This is an example Xournal++ Plugin - copy this to get started

-- Register all Toolbar actions and intialize all UI stuff
function initUi()
  ref = app.registerUi({
    ["menu"] = "Open Pluigin Istaller",
    ["callback"] = "openMenu",
    ["accelerator"] = "<Control>t"
  });
end

-- Callback Menu for the pluigin installer
function openMenu()
  result = app.msgbox(
    "Inofficial Xournalpp Pluigin Installer",
    {
      [1] = "Yes",
      [2] = "No"
    }
  );

  if result == 1 then
    print("Benutzer hat 'Yes' gewählt.")
    show_window()
    -- Hier dein Code für Yes-Aktion
  elseif result == 2 then
    print("Benutzer hat 'No' gewählt.")
    -- Hier dein Code für No-Aktion
  else
    print("Unbekannte Auswahl: " .. tostring(result))
  end
end
