const canvas1 = document.getElementById('generator1')
const canvas2 = document.getElementById('generator2')

const ctx1 = canvas1.getContext('2d')
const ctx2 = canvas2.getContext('2d')

const N = 1000

// exponential generator

const exponentialGenerator = (a) => {
  const randomValue = Math.random()
  const x = - (1/a) * Math.log(randomValue)
  return x
}

const researchGenerator = (numbers) => {
  const averageRandomVariable = (
    numbers.reduce((sum, value) => sum + value, 0) / N
  ).toFixed(2)
  
  const dispersion = numbers.reduce((sum, value) => {
    const diff = (value - averageRandomVariable) ** 2
    return sum + diff
  }, 0) / (N - 1)
  
  console.log('averageRandomVariable', averageRandomVariable)
  console.log('dispersion', Math.sqrt(dispersion))
}

const generateNumbersWithExponentialGenerator = () => {
  const numbers = Array.from({length: N})
  const a = 3
  numbers.forEach((n, i, arr) => {
    arr[i] = exponentialGenerator(a)
  })
  
  researchGenerator(numbers)
  histogram(ctx1, numbers)
}

const normalGenerator = (o, a) => {
  const u = Array.from({length: 12})
    .map(() => Math.random())
    .reduce((sum, value) => sum + value, 0)
    .toFixed(2)

  const x = o * u + a
  return x
}

const generateNumbersWithNormalGenerator = () => {
  const numbers = Array.from({length: N})
  const o = 1
  const a = 2
  numbers.forEach((n, i, arr) => {
    arr[i] = normalGenerator(o, a)
  })
  
  researchGenerator(numbers)
  histogram(ctx2, numbers)
}


generateNumbersWithExponentialGenerator()
generateNumbersWithNormalGenerator()

// console.log(numbe/rs)
