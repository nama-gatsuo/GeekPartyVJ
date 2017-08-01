var twitter = require('twitter');
var Sender = require('omgosc').UdpSender;
const hosturl = '0.0.0.0';
const oscport = 4321;

var client = new twitter({

    consumer_key: 'emGIH5fTaWYpNU8ydhLUp4x7T',
    consumer_secret: 'me8Pz5t4LLRU5hHd1jIWrJ2hbGynSQbuaFVLFy7rxbX3nhRKoK',
    access_token_key: '157947766-V2w0vLmfbm3HShfuPvJ1LXY8rVqVfBRtoW9hyOKA',
    access_token_secret: 'JK6Ltw2n7uX0z3dUh0DY2uEYOatGfoSI2NySAWLMz0L64'

});

var sender = new Sender(hosturl, oscport);

client.stream('statuses/filter', {
    track: '#Akiparty'
}, (stream) => {

    stream.on('data', (data) => {

        // console.log(data);

        console.log('name: ' + data.user.screen_name);
        console.log('text: ' + data.text);

        let s1, s2, s3;

        if (data.text.length <= 50) {
            s1 = data.text.slice(0, 50);
            s2 = '';
            s3 = '';
        } else if (data.text.length > 50 || data.text.length <= 100) {
            s1 = data.text.slice(0, 50);
            s2 = data.text.slice(51, 100);
            s3 = '';
        } else if (data.text.length > 100) {
            s1 = data.text.slice(0, 50);
            s2 = data.text.slice(51, 100);
            s3 = data.text.slice(101, 140);
        }

        sender.send(
            '/twi_osc',
            'ssss',
            [
                data.user.screen_name,
                s1,
                s2,
                s3
            ]
        );

    });


});
