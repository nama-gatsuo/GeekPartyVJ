import jschardet from 'jschardet'
import { Iconv } from 'iconv'

import Twitter from 'twitter'
import { UdpSender } from 'omgosc'

import SETTINGS from './settings'

let t = SETTINGS.TWI, c = SETTINGS.CLIENT;

let client = new Twitter({
    consumer_key: t.CONSUMER_KEY,
    consumer_secret: t.CONSUMER_SECRET,
    access_token_key: t.ACCESS_TOKEN_KEY,
    access_token_secret: t.ACCESS_TOKEN_KEY_SECRET
});

let sender = new UdpSender(c.HOST, c.PORT);

let notUtf8String = 'ほげ感mga永松じ';
let detectResult = jschardet.detect(notUtf8String);
console.log(notUtf8String); // -> { encoding: 'ascii', confidence: 1 }
console.log(detectResult);
let iconv = new Iconv('utf-8', 'utf-8');
let convertedString = iconv.convert(new Buffer(notUtf8String)).toString();

console.log(convertedString);
sender.send('/twi_osc', 'ss', [notUtf8String, convertedString]);

// client.stream('statuses/filter', {
//     track: 'Akiparty'
// }, (stream) => {
//
//     stream.on('data', (data) => {
//         //console.log(data);
//         let name = data.user.name + ' @' + data.user.screen_name;
//
//         console.log('name: ' + name);
//         console.log('text: ' + data.text);
//
//         let enc = jschardet.detect(name).encoding;
//         let iconv = new Iconv(enc, 'UTF-8//TRANSLIT//IGNORE');
//         name = iconv.convert(name).toString();
//
//         enc = jschardet.detect(data.text).encoding;
//         iconv = new Iconv(enc, 'UTF-8//TRANSLIT//IGNORE');
//         let txt = iconv.convert(data.text).toString();
//
//         sender.send(
//             '/twi_osc', 'ss',
//             [ name, txt ]
//         );
//
//     });
//
// });
