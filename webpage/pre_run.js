/* Pre Run script */

import { readFileSync, writeFileSync } from 'fs';

console.log("");

console.log("*****************************");
console.log("*                           *");
console.log("*     Run Pre Run Script    *");
console.log("*                           *");
console.log("*****************************");

console.log("");

/* creating src/components/plugins.js */
let content = await readFileSync('../data/plugins.json', 'utf-8');

writeFileSync('src/components/plugins.js', `// All registered plugins\n// This file is auto-generated from root/plugins.json,\n// do not edit manually !!!\n\nexport const plugin_data = ${content}\n`);

console.log("");

console.log("*****************************");
console.log("*                           *");
console.log("*  Finished Pre Run Script  *");
console.log("*                           *");
console.log("*****************************");

console.log("");
