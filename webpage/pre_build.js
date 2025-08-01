/* Pre Build Script */

/* Docs Site must be BUILD BEFORE !!! */

import { writeFileSync } from 'fs';
import { cp } from 'fs/promises';
import { mkdir } from 'fs/promises';
import { exec } from "child_process";

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
console.log("*   Run Pre Build Script    *");
console.log("*                           *");
console.log("*****************************");

console.log("");

await createFolder('dist');
writeFileSync('dist/.nojekyll', '');

/* Docs Site adding to the Astro Export */

try {
  await cp('../docs2/site', 'public/docs', { recursive: true });
  console.log('copied Folder successfully');
} catch (err) {
  console.error('Error while copying:', err);
}

console.log("");

console.log("*****************************");
console.log("*                           *");
console.log("* Finished Pre Build Script *");
console.log("*                           *");
console.log("*****************************");

console.log("");
