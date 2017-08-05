import fs from 'fs'
import Twitter from 'twitter'
import SETTINGS from './settings'

let t = SETTINGS.TWI, c = SETTINGS.CLIENT;

let client = new Twitter({
    consumer_key: t.CONSUMER_KEY,
    consumer_secret: t.CONSUMER_SECRET,
    access_token_key: t.ACCESS_TOKEN_KEY,
    access_token_secret: t.ACCESS_TOKEN_KEY_SECRET
});

const path = './src/client/oF/bin/data/json/';
const file = 'twi.json'

client.stream('statuses/filter', {
    track: 'Akiparty'
}, (stream) => {

    stream.on('data', (data) => {

        fs.writeFile(path + file, JSON.stringify(data), null, null);
        fs.readFile(path + file, 'utf8', function (err, tw) {
            console.log(JSON.stringify(tw));
        });

    });

});
