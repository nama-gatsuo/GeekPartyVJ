'use strict';

var _jschardet = require('jschardet');

var _jschardet2 = _interopRequireDefault(_jschardet);

var _iconv = require('iconv');

var _twitter = require('twitter');

var _twitter2 = _interopRequireDefault(_twitter);

var _omgosc = require('omgosc');

var _settings = require('./settings');

var _settings2 = _interopRequireDefault(_settings);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var t = _settings2.default.TWI,
    c = _settings2.default.CLIENT;

var client = new _twitter2.default({
    consumer_key: t.CONSUMER_KEY,
    consumer_secret: t.CONSUMER_SECRET,
    access_token_key: t.ACCESS_TOKEN_KEY,
    access_token_secret: t.ACCESS_TOKEN_KEY_SECRET
});

var sender = new _omgosc.UdpSender(c.HOST, c.PORT);

var notUtf8String = 'ほげ感mga永松じ';
var detectResult = _jschardet2.default.detect(notUtf8String);
console.log(notUtf8String); // -> { encoding: 'ascii', confidence: 1 }
console.log(detectResult);
var iconv = new _iconv.Iconv('utf-8', 'utf-8');
var convertedString = iconv.convert(new Buffer(notUtf8String)).toString();

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
//# sourceMappingURL=stream.js.map
