const express = require('express'); //Import the express dependency
const cors = require('cors');
const path = require('path');
const bodyParser = require('body-parser')

const app = express();              //Instantiate an express app, the main work horse of this server
const port = 5000;                  //Save the port number where your server will be listening

var urlencodedParser = bodyParser.urlencoded({ extended: false })

app.use(cors());
app.use('/', express.static('.'))

app.get('/', (req, res) => {        //get requests to the root ("/") will route here
    res.sendFile(path.join(__dirname, '/index.html'));    //server responds by sending the index.html file to the client's browser
                                                
});

// app.post('/', urlencodedParser, (req, res) => {
//     console.log('Got body:', req.body);
//     res.sendStatus(200);
// });

app.listen(port, () => {            //server starts listening for any attempts from a client to connect at port: {port}
    console.log(`Now listening on port ${port}`); 
});