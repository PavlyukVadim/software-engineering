const canvas1 = document.getElementById('generator1')
const ctx1 = canvas1.getContext('2d')

const N = 1000

// first generator

const generator = (a) => {
  const randomValue = Math.random()
  const x = - (1/a) * Math.log(randomValue)
  return x
}

const numbers = Array.from({length: N})
const a = 2
numbers.forEach((n, i, arr) => {
  arr[i] = generator(a)
})

histogram(ctx1, numbers)
// console.log(numbe/rs)
