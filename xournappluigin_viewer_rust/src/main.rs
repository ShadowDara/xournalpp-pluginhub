use serde_json::Value;

fn main() {
    match check_json() {
        Ok(_) => println!("Alles ok"),
        Err(e) => eprintln!("Fehler: {}", e),
    }
}

fn check_json() -> Result<(), Box<dyn std::error::Error>> {
    // file where the pluigin data is stored
    let url = "https://raw.githubusercontent.com/ShadowDara/xournalpp-pluigin-hub-idea/refs/heads/main/pluigins.json";

    let client = reqwest::blocking::Client::new();
    let response = client
        .get(url)
        .header("User-Agent", "RustClient/1.0")
        .send()?;

    let text = response.text()?;
    
    let json_result: serde_json::Result<Value> = serde_json::from_str(&text);

    match json_result {
        Ok(json) => {
            println!("Gültiges JSON empfangen!");
            println!("{json}")
        },
        Err(e) => {
            println!("Ungültiges JSON: {}", e);
        }
    }

    Ok(())
}
