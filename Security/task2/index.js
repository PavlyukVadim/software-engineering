const fs = require('fs')
const path = require('path')

const AVARAGE_WORD_LENGTH = 5
const ALLOWED_SPACE_DELTA = 15
const ALLOWED_LETTER_DELTA = 30

const POWER = 26

const hex2a = (hexx) => {
  const hex = hexx.toString(); // force conversion
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
  const numberOfUniqueSymbols = getNumberOfUniqueSymbols(str)

  const arr = indexOfCoincidence(currentLetterFrequencies, numberOfUniqueSymbols)

  let counter = 0

  for(let i = 0; i < 256; i++)
    for(let j = 0; j < 256; j++) {
      for(let k = 0; k < 256; k++) {
        const key = [i, j, k]
        const newStr = symbols.map((symbol) => {
          if(counter === 3) counter = 0
          return xorDecrypt(symbol, key[counter++])
        }).join('')

        const found = checkProbability(newStr)
        if(found) {
          console.log('key', key.map((e) => String.fromCharCode(e)).join(''))
          console.log(newStr)
          return newStr
        }
      }
    }

})

const currentLetterFrequencies = {}
const getNumberOfUniqueSymbols = (text = '') => {
  // const currentLetterFrequencies = {}
  const symbols = text.split('')
  symbols.forEach((symbol) => {
    if (symbol in currentLetterFrequencies) {
      currentLetterFrequencies[symbol]++
    } else {
      currentLetterFrequencies[symbol] = 1
    }
  })
  const numberOfUniqueSymbols = Object.keys(currentLetterFrequencies).length
  return numberOfUniqueSymbols
}

const indexOfCoincidence = (currentLetterFrequencies, power) => {
  const b = (power * (power - 1))
  const arr = Object.keys(currentLetterFrequencies).map((letter) => {
    const fi = currentLetterFrequencies[letter] * (currentLetterFrequencies[letter] - 1)
    return fi / b
  })
  return arr
}

const checkProbability = (text = '') => {
  const expectedNumberOfSpaces = text.length / (AVARAGE_WORD_LENGTH + 1)
  const words = text.split(' ')
  const numberOfSpaces = words.length
  const currentDelta = (Math.abs(expectedNumberOfSpaces - numberOfSpaces) / expectedNumberOfSpaces) * 100

  if (currentDelta > ALLOWED_SPACE_DELTA) return false

  const currentLetterFrequencies = {}
  const letters = words.join('').toLowerCase().match(/[a-z]/ig) || []
  const numberOfLetters = letters.length

  letters.forEach((letter) => {
    if (currentLetterFrequencies[letter]) {
      currentLetterFrequencies[letter] = currentLetterFrequencies[letter] + 1
    } else {
      currentLetterFrequencies[letter] = 1
    }
  })

  Object.keys(currentLetterFrequencies).forEach((letter) => {
    currentLetterFrequencies[letter] = (currentLetterFrequencies[letter] / numberOfLetters) * 100
  })

  const totalProbability = Object.keys(currentLetterFrequencies).reduce((sum, letter) => {
    const expectedFrequency = frequencyMap.get(letter)
    if (!expectedFrequency) return sum
    const currentFrequency = currentLetterFrequencies[letter]
    const currentDelta = Math.abs(expectedFrequency - currentFrequency)
    return sum + currentDelta
  }, 0)

  return totalProbability <= ALLOWED_LETTER_DELTA
}

const xorDecrypt = (symbol, key) => {
  return String.fromCharCode(symbol.charCodeAt() ^ key)
}

const frequencyMap = new Map([
  ['e', 12.702],
  ['t',	9.056],
  ['a',	8.167],
  ['o',	7.507],
  ['i',	6.966],
  ['n',	6.749],
  ['s',	6.327],
  ['h',	6.094],
  ['r',	5.987],
  ['d',	4.253],
  ['l',	4.025],
  ['c',	2.782],
  ['u',	2.758],
  ['m',	2.406],
  ['w',	2.360],
  ['f',	2.228],
  ['g',	2.015],
  ['y',	1.974],
  ['p',	1.929],
  ['b',	1.492],
  ['v',	0.978],
  ['k',	0.772],
  ['j',	0.153],
  ['x',	0.150],
  ['q',	0.095],
  ['z',	0.074],
])
