const express = require('express');
 const app = express();
//const cors = require('cors');
const PORT = 3000;

  //app.use(cors());

   // API endpoint
   app.get('/api', (req, res) => {
                                  res.send('Server time : ' + Date.now() + ' ms  Hello World from Server!');
                                 });
   
        // Factorial calculation function
        const factorial =  (n) => {
                                   if(isNaN(n))return NaN;
                                   if (n < 0) return NaN;
                                   if (n === 0 || n === 1) return 1;
                                    return n * factorial(n - 1);
                                  }
   // Route with parameter validation
   app.get('/factorial/:n', (req, res) => {
                                            const n = parseInt(req.params.n);
                                            console.log("request from client /factorial/"+n)
                                             const result = "(from server) " + factorial(n);
                                              res.send(result);
                                          });

   // Serve client page
   app.get('/', (req, res) => {
                               res.sendFile(__dirname + '/index.html');
                              });

    app.listen(PORT, '0.0.0.0', () => {
                                      console.log(`Server running at ${PORT}`);
                                     });