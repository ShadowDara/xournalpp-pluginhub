import { readFileSync, writeFileSync } from 'fs';
import { mkdir } from 'fs/promises';

async function createFolder(ordner) {
  try {
    await mkdir(ordner);
    console.log('Ordner wurde erstellt!');
  } catch (err) {
    console.error('Fehler beim Erstellen des Ordners:', err);
  }
}

console.log("");

console.log("*****************************");
console.log("*                           *");
console.log("*     Run Pre Run Script    *");
console.log("*                           *");
console.log("*****************************");

console.log("");

await createFolder('build');
writeFileSync('build/.nojekyll', '');

// src/components/plugins.js erstellen
let content = await readFileSync('../plugins.json', 'utf-8');
writeFileSync('src/components/plugins.js', `// All registered plugins\n// This file is auto-generated, do not edit manually\n\nexport const plugin_data = ${content}\n`);

console.log("");

console.log("*****************************");
console.log("*                           *");
console.log("*  Finished Pre Run Script  *");
console.log("*                           *");
console.log("*****************************");

console.log("");
