const cycledIterator = (iterable) => {
  let iterator = iterable[Symbol.iterator]()
  return {
    next: () => {
      const { done, value } = iterator.next()
      if (done) {
        iterator = iterable[Symbol.iterator]()
        return iterator.next()
      } else {
        return { done, value }
      }
    }
  }
}

export const pickRandom = (elements, probabilities) => {
  const elementsArr = [...elements]
  if (!elementsArr.length) {
    throw Error('Empty input not allowed')
  }
  if (probabilities) {
    const probabilitiesIterator = cycledIterator(probabilities)
    const randomValue = Math.random() * probabilities.reduce((acc, el) => acc + el)
    let probabilitiesSum = 0
    for (const elem of elements) {
      probabilitiesSum += probabilitiesIterator.next().value
      if (randomValue < probabilitiesSum) {
        return elem
      }
    }
  } else {
    return elementsArr[Math.floor(Math.random() * elementsArr.length)]
  }
}

