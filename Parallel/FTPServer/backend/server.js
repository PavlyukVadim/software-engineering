const net = require('net')
const fs = require('fs')

const server = net.createServer((connection) => {
  console.log('client connected')
  connection.on('data', (data) => {
    const receivedData = data.toString()
    const receivedObj = JSON.parse(receivedData)
    const userName = receivedObj.payload
    console.log('received request from:', userName)
    getFilesList(userName, (err, files) => {
      const response = {
        type: 'filesList',
        payload: files,
      }
      const strResponse = JSON.stringify(response)
      connection.write(strResponse)
      console.log('sent response:', strResponse)
    })
  })

  connection.on('end', () => {
    console.log('client disconnected')
  })
})

server.listen(8080, function() {
  console.log('ftp server is listening at 8080')
})

const dataFolder = 'data'

const getFilesList = (userName, callback) => {
  fs.readdir(`./${dataFolder}/${userName}`, callback)
}
