const net = require('net')
const express = require('express')
const path = require('path')

const app = express()

app.get('/', function (req, res) {
  console.log('req', req.url)
  const indexPath = path.join(__dirname, '../frontend/index.html')
  res.sendFile(indexPath)
})

app.get('/user/:id', function (req, res) {
  const userName = req.params.id
  createConnectionToFtp(userName, res)
  console.log('params', req.params.id)
})

const publicPath = path.join(__dirname, '../frontend/public')
app.use('/public', express.static(publicPath))

app.listen(3000, () => {
  console.log('App listening on port 3000!')
})


const createConnectionToFtp = (userName, res) => {
  var client = net.connect({port: 8080}, () => {
    console.log(`connected ${userName} to server!`)
    client.write({
      type: 'userName',
      payload: userName,
    })
  })

  client.on('data', function(data) {
    console.log(data.toString())
    res.send(data.toString())
    // client.end()
  })
   
  client.on('end', function() { 
    console.log('disconnected from server');
  })
}