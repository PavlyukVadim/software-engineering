const canvas1 = document.getElementById('generator1')
const canvas2 = document.getElementById('generator2')
const canvas3 = document.getElementById('generator3')

const ctx1 = canvas1.getContext('2d')
const ctx2 = canvas2.getContext('2d')
const ctx3 = canvas3.getContext('2d')

const N = 10000

const eGA = Math.pow(5, 13)
const eGC = Math.pow(2, 31)

const generators = {
  exponential: (a) => {
    const randomValue = Math.random()
    const x = - (1/a) * Math.log(randomValue)
    return x
  },
  normal: (o, a) => {
    const u = Array.from({length: 12})
      .map(() => Math.random())
      .reduce((sum, value) => sum + value, -6)
      .toFixed(2)
  
    const x = o * u + a
    return x
  },
  even: (arrOfZ, prevZ) => {
    const z = (eGA * prevZ) % eGC
    arrOfZ.push(z)
    const x = z / eGC
    return x
  }
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
  const { exponential: exponentialGenerator } = generators
  
  const numbers = Array.from({length: N})
  const a = 3
  numbers.forEach((n, i, arr) => {
    arr[i] = exponentialGenerator(a)
  })
  
  researchGenerator(numbers)

  const [
    min,
    max,
    intervalSize,
    intervals,
    frequencies,
  ] = analyze(numbers)

  countKsiExponential(min, max, intervalSize, frequencies, a)
  histogram(ctx1, intervals, frequencies)
}

const generateNumbersWithNormalGenerator = () => {
  const { normal: normalGenerator } = generators
  const numbers = Array.from({length: N})
  const o = 4
  const a = 7
  numbers.forEach((n, i, arr) => {
    arr[i] = normalGenerator(o, a)
  })
  
  researchGenerator(numbers)

  const [
    min,
    max,
    intervalSize,
    intervals,
    frequencies,
  ] = analyze(numbers)

  countKsiNormal(min, max, intervalSize, frequencies, o, a)
  histogram(ctx2, intervals, frequencies)
}

const generateNumbersWithEvenGenerator = () => {
  const { even: evenGenerator } = generators
  const numbers = Array.from({length: N})
  const arrOfZ = []
  arrOfZ[0] = 3
  numbers.forEach((n, i, arr) => {
    arr[i] = evenGenerator(arrOfZ, arrOfZ[i])
  })
  
  researchGenerator(numbers)

  const [
    min,
    max,
    intervalSize,
    intervals,
    frequencies,
  ] = analyze(numbers)

  countKsiEven(min, max, intervalSize, frequencies)
  histogram(ctx3, intervals, frequencies)
}

generateNumbersWithExponentialGenerator()
generateNumbersWithNormalGenerator()
generateNumbersWithEvenGenerator()


/* array of generated N numbers */
function analyze(array) {
  const min = Math.min(...array)
  const max = Math.max(...array)

  const intervalSize = (max - min) / k

  const intervals = Array.from({length: k})

  intervals.reduce((prevInterval, el, index, array) => {
    array[index] = prevInterval + intervalSize
    return array[index]
  }, min)

  intervals.forEach((interval, i, arr) => {
    arr[i] = (interval).toFixed(2)
  })

  array.sort((a, b) => a - b)
  
  const numbersBeforeInterval = Array.from({length: k})
  for (let i = 0; i < numbersBeforeInterval.length; i++) {
    const intervalRightBorder = intervals[i] || max
    const lastIndex = array.findIndex((number) => (number >= intervalRightBorder))
    const numbersLessThanRightBorder = (lastIndex !== -1)
      ? lastIndex
      : numbersBeforeInterval[i - 1]
    
      numbersBeforeInterval[i] = numbersLessThanRightBorder
  }

  const frequencies = numbersBeforeInterval.map((lastIndex, i, array) => {
    const prevNumbersInInterval = (array[i - 1] || 0)
    const numbersInInterval = lastIndex - prevNumbersInInterval
    return numbersInInterval
  })

  return [
    min,
    max,
    intervalSize,
    intervals,
    frequencies
  ]
}

function countKsiExponential(min, max, intervalSize, frequencies, lambda = 3) {
  const statisticCount = (x0, x1, lambda = 3) => {
    const checkRand = (lambda, x) => {
      return lambda * Math.pow(Math.E, -lambda * x)
    }
  
    const step = (x1 - x0) / 100
    const result = Array.from({length: 100})
      .reduce((sum, el, i) => sum + checkRand(lambda, x0 + step * i) * step, 0)
    
    return result
  }

  let ksi = 0
  for (let i = 0; i < k; ++i) {
    const x0 = min + i * intervalSize
    const x1 = min + (i + 1) * intervalSize
    const np = statisticCount(x0, x1, lambda) * 10000
    if (frequencies[i] > 5) {
      ksi += Math.pow(frequencies[i] - np, 2) / np
    }
  }
  console.log('ksi^2 exponential', ksi)
}

function countKsiNormal(min, max, intervalSize, frequencies, o = 4, a = 7) {
  const statisticCount = (x0, x1, m, a) => {
    const checkRand = (d, a, x) => {
      return (1 / (d * Math.sqrt(2 * Math.PI))) * Math.exp(
        -(Math.pow(x - a, 2) / (2 * Math.pow(d, 2)))
      )
    }

    const step = (x1 - x0) / 100
    let result = 0
    for (let i = 0; i < 100; ++i) {
      result += checkRand(m, a, (x0 + step * i)) * step
    }
    return result
  }

  let ksi = 0
  for (let i = 0; i < k; ++i) {
    const x0 = min + i * intervalSize
    const x1 = min + (i + 1) * intervalSize
    const np = statisticCount(x0, x1, o, a) * 10000
    if (frequencies[i] > 5) {
      ksi += Math.pow(frequencies[i] - np, 2) / np
    }
  }

  console.log('ksi^2 normal', ksi)
}

function countKsiEven(min, max, intervalSize, frequencies, a, b) {
  const statisticCount = (x0, x1, a, b) => {
    const checkRand = (a, b, x) => {
      return (
        (x >= a && x <= b)
          ? 1 / (b - a)
          : 0
      )
    }

    const step = (x1 - x0) / 100
    let result = 0
    for (let i = 0; i < 100; ++i) {
      result += checkRand(a, b, (x0 + step * i)) * step
    }
    return result
  }

  let ksi = 0
  for (let i = 0; i < k; ++i) {
    const x0 = min + i * intervalSize
    const x1 = min + (i + 1) * intervalSize
    const np = statisticCount(x0, x1, 0, 1) * 10000

    if (frequencies[i] > 5) {
      ksi += Math.pow(frequencies[i] - np, 2) / np
    }
  }

  console.log('ksi^2 even', ksi)
}
