use reqwest::blocking::Client;
use serde_json::Value;

fn main() {
    match check_json() {
        Ok(json) => println!("Alles ok : {}", json),
        Err(e) => eprintln!("Fehler: {}", e),
    }

    // then need to parse the json file
}

fn check_json() -> Result<Value, Box<dyn std::error::Error>> {
    // Datei, wo die Plugin-Daten liegen
    let url = "https://raw.githubusercontent.com/ShadowDara/xournalpp-plugin-hub-idea/refs/heads/main/plugins.json";

    let client = Client::new();
    let response = client
        .get(url)
        .header("User-Agent", "RustClient/1.0")
        .send()?;

    let text = response.text()?; // ✅ hier: ? entpackt das Result<String, _>

    let json: Value = serde_json::from_str(&text)?; // ✅ entpackt Result<Value, _>

    Ok(json)
}
