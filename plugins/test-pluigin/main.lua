-- @Author Shadowdara
-- Example Plugin for the Plugin Hub
-- Does absolutly nothing

function initUi()
  ref = app.registerUi({
    ["menu"] = "Plugin Hub Example Plugin",
    ["callback"] = "popupmenu",
    ["accelerator"] = ""
  });
end

function popupmenu()
  result = app.msgbox(
    "Plugin Hub Example Plugin",
    {
      [1] = "Plugin Worked!",
    }
  );
end
