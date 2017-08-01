import Twitter from 'twitter'
import { UdpSender } from 'omgosc'

import SETTINGS from './settings'

let t = SETTINGS.TWI, c = SETTINGS.CLIENT;

let client = new Twitter({
    consumer_key: t.CONSUMER_KEY,
    consumer_secret: t.CONSUMER_SECRET,
    access_token_key: t.ACCESS_TOKEN_KEY,
    access_token_secret: tI.SCCESS_TOKEN_KEY_SECRET
});

let sender = new UdpSender(c.HOST, c.PORT);

client.stream('statuses/filter', {
    track: 'Akiparty'
}, (stream) => {

    stream.on('data', (data) => {

        console.log('name: ' + data.user.screen_name);
        console.log('text: ' + data.text);

        sender.send(
            '/twi_osc', 'ss',
            [ data.user.screen_name, data.text ]
        );

    });

});
