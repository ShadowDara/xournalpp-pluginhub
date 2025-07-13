-- @Author Shadowdara
-- Example Pluigin for the Pluigin Hub
-- Does absolutly nothing

function initUi()
  ref = app.registerUi({
    ["menu"] = "Pluigin Hub Example Pluigin",
    ["callback"] = "popupmenu",
    ["accelerator"] = ""
  });
end

function popupmenu()
  result = app.msgbox(
    "Pluigin Hub Example Pluigin",
    {
      [1] = "Pluigin Worked!",
    }
  );
end
