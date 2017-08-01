var encoding = require('encoding');

let s = 'テスト';
let r = encoding.convert(s, "utf16le");


console.log(s);
console.log(s.charCodeAt(0));
console.log(s.charCodeAt(0) & 0x7f & 0x7f);
console.log(encoding.convert(s.substr(0, 1), "utf8")[0] & 0x7f);
console.log(encoding.convert(s.substr(0, 1), "utf8")[1]);
console.log(encoding.convert(s.substr(0, 1), "utf8")[2]);
console.log(r.toString("utf16le"));
