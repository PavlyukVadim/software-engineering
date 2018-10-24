const fs = require('fs')
const path = require('path')

const AVARAGE_WORD_LENGTH = 5
const ALLOWED_SPACE_DELTA = 15
const ALLOWED_LETTER_DELTA = 30

const POWER = 26

fs.readFile(path.resolve(__dirname, 'file'), 'utf8', (err, input) => {
  let currentShift = 0
  let found = false

  while((currentShift <= POWER) && !found) {
    const caesarDecrypted = caesarDecrypt(input, currentShift)
    let xorKey = 0
    while(xorKey <= 256) {
      const xorDecrypted = xorDecrypt(caesarDecrypted, xorKey)
      const isReal = checkProbability(xorDecrypted)
      if (isReal) {
        found = true
        console.log('xorDecrypted', xorDecrypted)
      }
      xorKey++
    }
    currentShift++
  }
})

const caesarDecrypt = (text = '', key = 0) => {
  const letters = text.split('')
  const decryptedText = letters.map((letter) => {
    if (!letter.match(/[a-z]/i)) return letter
    const code = letter.charCodeAt()
    const koef = (code >= 97 && code <= 122) ? 97 : 65
    const decryptedLetter = String.fromCharCode(((code - koef + key) % POWER) + koef)
    return decryptedLetter
  }).join('')

  return decryptedText
}

const xorDecrypt = (text = '', key = 0) => {
  const letters = text.split('')
  const decryptedText = letters.map((letter) => {
    const decryptedLetter = String.fromCharCode(letter.charCodeAt() ^ key)
    return decryptedLetter
  }).join('')

  return decryptedText
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
