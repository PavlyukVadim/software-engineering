const net = require('net')

const server = net.createServer((connection) => { 
  console.log('client connected')
   
  connection.write('Hello World!\r\n')

  connection.on('data', (data) => {
    console.log('data', data)
    console.log('received', data.toString())
  })

  connection.on('end', () => {
    console.log('client disconnected')
  })
})

server.listen(8080, function() { 
  console.log('ftp server is listening at 8080')
})
