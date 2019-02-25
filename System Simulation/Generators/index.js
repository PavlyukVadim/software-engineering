const canvas1 = document.getElementById('generator1')
const canvas2 = document.getElementById('generator2')
const canvas3 = document.getElementById('generator3')

const ctx1 = canvas1.getContext('2d')
const ctx2 = canvas2.getContext('2d')
const ctx3 = canvas3.getContext('2d')

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

// uniform generator
const eGA = Math.pow(5, 13)
const eGC = Math.pow(2, 31)
const evenGenerator = (arrOfZ, prevZ) => {
  const z = (eGA * prevZ) % eGC
  arrOfZ.push(z)
  const x = z / eGC
  return x
}

const generateNumbersWithEvenGenerator = () => {
  const numbers = Array.from({length: N})
  const arrOfZ = []
  arrOfZ[0] = 3
  numbers.forEach((n, i, arr) => {
    arr[i] = evenGenerator(arrOfZ, arrOfZ[i])
  })
  
  researchGenerator(numbers)
  histogram(ctx3, numbers)
}

generateNumbersWithExponentialGenerator()
generateNumbersWithNormalGenerator()
generateNumbersWithEvenGenerator()
