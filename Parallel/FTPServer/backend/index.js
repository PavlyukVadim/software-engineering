const net = require('net')
const express = require('express')
const path = require('path')

const app = express()

app.get('/', function (req, res) {
  const indexPath = path.join(__dirname, '../frontend/index.html')
  res.sendFile(indexPath)
})

app.get('/user/:id', function (req, res) {
  const userName = req.params.id
  createConnectionToFtp(userName, res)
  console.log('input params:', req.params.id)
})

const publicPath = path.join(__dirname, '../frontend/public')
app.use('/public', express.static(publicPath))

const dataPath = path.join(__dirname, '/data')
app.use('/data', express.static(dataPath))

app.listen(3000, () => {
  console.log('App listening on port 3000!')
})


const createConnectionToFtp = (userName, res) => {
  var client = net.connect({port: 8080}, () => {
    console.log(`connected ${userName} to server!`)
    const obj = {
      type: 'userName',
      payload: userName,
    }

    client.write(JSON.stringify(obj))
  })

  client.on('data', function(data) {
    const receivedData = data.toString()
    console.log('received response from FTP server:', receivedData)
    const obj = JSON.parse(receivedData)
    const { type } = obj
    res.send(data.toString())
    // client.end()
  })

  client.on('end', function() {
    console.log('disconnected from server');
  })
}
