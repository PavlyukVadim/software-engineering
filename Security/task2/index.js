const fs = require('fs')
const path = require('path')

const AVARAGE_WORD_LENGTH = 5
const ALLOWED_SPACE_DELTA = 15
const ALLOWED_LETTER_DELTA = 30

const POWER = 26

const hex2a = (hexx) => {
  const hex = hexx.toString();//force conversion
  let str = '';
  for (let i = 0; (i < hex.length && hex.substr(i, 2) !== '00'); i += 2)
    str += String.fromCharCode(parseInt(hex.substr(i, 2), 16));
  return str;
}

fs.readFile(path.resolve(__dirname, 'encoded'), 'utf8', (err, input) => {
  let currentShift = 0
  let found = false

  const str = hex2a(input)
  const symbols = str.split('')
  const arr = []

  console.log(str)

  symbols.forEach((symbol, i) => {
    arr[i] = indexOfCoincidence(str, i, arr)
  })

  console.log(arr)
})

const getFreqObj = (letters) => {
  const currentLetterFrequencies = {}
  const numberOfLetters = letters.length

  letters.split('').forEach((letter) => {
    if (currentLetterFrequencies[letter]) {
      currentLetterFrequencies[letter] = currentLetterFrequencies[letter] + 1
    } else {
      currentLetterFrequencies[letter] = 1
    }
  })

  return currentLetterFrequencies
}


const indexOfCoincidence = (text = '', shift = 0, arr) => {
  const symbol = text[shift]
  const n = text.length

  const obj = getFreqObj(text)

  const b = (n * n - 1)

  let i = 0
  let result = 0
  while(i <= shift) {
    const fi = obj[symbol] * (obj[symbol] - 1)
    result += fi / b
    i++
  }
  return result
}
