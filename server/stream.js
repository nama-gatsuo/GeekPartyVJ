'use strict';

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
    access_token_secret: tI.SCCESS_TOKEN_KEY_SECRET
});

var sender = new _omgosc.UdpSender(c.HOST, c.PORT);

client.stream('statuses/filter', {
    track: 'Akiparty'
}, function (stream) {

    stream.on('data', function (data) {

        console.log('name: ' + data.user.screen_name);
        console.log('text: ' + data.text);

        sender.send('/twi_osc', 'ss', [data.user.screen_name, data.text]);
    });
});
//# sourceMappingURL=stream.js.map
