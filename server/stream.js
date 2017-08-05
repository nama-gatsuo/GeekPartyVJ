'use strict';

var _fs = require('fs');

var _fs2 = _interopRequireDefault(_fs);

var _twitter = require('twitter');

var _twitter2 = _interopRequireDefault(_twitter);

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

var path = './src/client/oF/bin/data/json/';
var file = 'twi.json';

client.stream('statuses/filter', {
    track: 'Akiparty'
}, function (stream) {

    stream.on('data', function (data) {

        _fs2.default.writeFile(path + file, JSON.stringify(data), null, null);
        _fs2.default.readFile(path + file, 'utf8', function (err, tw) {
            console.log(JSON.stringify(tw));
        });
    });
});
//# sourceMappingURL=stream.js.map
