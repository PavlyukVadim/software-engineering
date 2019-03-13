class FunRand {
  /**
  * Generates a random value according to an exponential distribution
  *
  * @param timeMean mean value
  * @return a random value according to an exponential distribution
  */
  static Exp(timeMean) {
    let a = 0
    while (a === 0) {
      a = Math.random()
    }
    a = -timeMean * Math.log(a)
    return a
  }

  /**
  * Generates a random value according to a uniform distribution
  *
  * @param timeMin
  * @param timeMax
  * @return a random value according to a uniform distribution
  */
  static Unif(timeMin, timeMax) {
    let a = 0
    while (a === 0) {
      a = Math.random()
    }
    a = timeMin + a * (timeMax - timeMin)
    return a
  }

  /**
  * Generates a random value according to a normal (Gauss) distribution
  *
  * @param timeMean
  * @param timeDeviation
  * @return a random value according to a normal (Gauss) distribution
  */
  static Norm(timeMean, timeDeviation) {
    let a
    // Random r = new Random();
    // a = timeMean + timeDeviation * r.nextGaussian();
    a = timeMean + timeDeviation * Math.random()
    return a
  }
}

class Element {
  static nextId = 0

  constructor(nameOfElement, delay) {
    this.tNext = 0
    this.delayMean = 1
    this.distribution = 'exp'
    this.tCurr = this.tNext
    this.state = 0
    this.nextElement = null
    this.id = Element.nextId
    Element.nextId++
    this.name = `element${this.id}`
    this.quantity = 0

    if (delay) {
      // this.name = 'anonymus'
      this.delayMean = delay
      this.distribution = ''
    }

    if (nameOfElement) {
      this.name = nameOfElement
      this.distribution = 'exp'
    }
  }

  getDelay() {
    let delay = this.getDelayMean()

    const distribution = this.getDistribution()
    if (distribution === 'exp') {
      delay = FunRand.Exp(this.getDelayMean())
    } else {
      if (distribution === 'norm') {
        delay = FunRand.Norm(
          this.getDelayMean(),
          this.getDelayDev()
        )
      } else {
        if (distribution === 'unif') {
          delay = FunRand.Unif(
            this.getDelayMean(),
            this.getDelayDev()
          )
        } else {
          if (distribution === '') {
            delay = this.getDelayMean()
          }
        }
      }
    }
    return delay
  }

  getDelayDev = () => this.delayDev
  
  setDelayDev = (delayDev) => {
    this.delayDev = delayDev
  }

  getDistribution = () => this.distribution
  
  setDistribution = (distribution) => {
    this.distribution = distribution
  }

  getQuantity = () => this.quantity
  
  getTcurr = () => this.tCurr
    
  setTcurr = (tCurr) => {
    this.tCurr = tCurr
  }

  getState = () => this.state

  setState = (state) => {
    this.state = state
  }

  getNextElement = () => this.nextElement

  setNextElement = (nextElement) => {
    this.nextElement = nextElement
  }

  inAct() {

  }
    
  outAct() {
    this.quantity++
  }

  getTnext() {
    return this.tNext
  }
    
  setTnext(tNext) {
    this.tNext = tNext
  }
  
  getDelayMean() {
    return this.delayMean
  }

  setDelayMean(delayMean) {
    this.delayMean = delayMean
  }

  getId() {
    return this.id
  }

  setId(id) {
    this.id = id
  }

  printResult() {
    console.log(`${this.getName()} quantity = ${this.quantity}`)
  }

  printInfo() {
    const name = this.getName()
    console.log(`${name} state = ${this.state} quantity = ${this.quantity} tnext = ${this.tNext}`)
  }

  getName = () => this.name
  
  setName = (name) => {
    this.name = name
  }
  
  doStatistics(delta) {

  }
}

class Create extends Element {
  constructor(delay) {
    super(delay)
  }

  outAct() {
    super.outAct()
    // console.log('super', super)
    const tCurr = this.getTcurr()
    this.setTnext(tCurr + this.getDelay())
    // this.setTnext(Number.MAX_VALUE + 100)
    this.getNextElement().inAct()
  }
}

class Process extends Element {
  constructor(delay) {
    super(delay)
    this.queue = 0
    this.maxqueue = Number.MAX_SAFE_INTEGER
    this.meanQueue = 0
    this.failure = 0
  }

  inAct() {
    if (this.getState() == 0) {
      this.setState(1)
      this.setTnext(this.getTcurr() + this.getDelay())
    } else {
      if (this.getQueue() < this.getMaxqueue()) {
        this.setQueue(this.getQueue() + 1)
      } else {
        this.failure++
      }
    }
  }

  outAct() {
    super.outAct()
    this.setTnext(Number.MAX_VALUE)
    this.setState(0)
    if (this.getQueue() > 0) {
      this.setQueue(this.getQueue() - 1)
      this.setState(1)
      this.setTnext(this.getTcurr() + this.getDelay())
    }

    if (this.outActCallBack) {
      this.outActCallBack()
    }
  }

  doStatistics(delta) {
    super.doStatistics()
    this.meanQueue = this.getMeanQueue() + this.queue * delta
  }

  getFailure = () => this.failure
  
  getQueue = () => this.queue
    
  setQueue(queue) {
    this.queue = queue
  }
    
  getMaxqueue = () => this.maxqueue
    
  setMaxqueue(maxqueue) {
    this.maxqueue = maxqueue
  }

  printInfo() {
    super.printInfo()
    console.log(`queue = ${this.getQueue()}`)
    console.log(`failure = ${this.getFailure()}`)
  }

  getMeanQueue = () => this.meanQueue
}

class Model {
  // const list = []
  
  constructor(elements = []) {
    this.list = [...elements]
    this.tNext = 0
    this.event = 0
    this.tCurr = this.tNext
  }

  simulate(time, disableOutput) {
    while (this.tCurr < time) {
      this.tNext = Number.MAX_VALUE
      for (let e of this.list) {
        if (e.getTnext() < this.tNext) {
          this.tNext = e.getTnext()
          this.eventId = e.getId()
        }
      }

      const event = this.list[this.eventId] || {}
      const eventName = event.getName
        ? event.getName()
        : 'unknown'

      if (!disableOutput) {
        console.log(`It's time for event in ${eventName}, time = ${this.tNext}`)  
      }
      
      for (let e of this.list) {
        e.doStatistics(this.tNext - this.tCurr)
      }

      this.tCurr = this.tNext
      // console.log('this.tCurr', this.tCurr)

      for (let e of this.list) {
        e.setTcurr(this.tCurr)
      }

      event.outAct && event.outAct()
      for (let e of this.list) {
        if (e.getTnext() == this.tCurr) {
          e.outAct()
        }
      }

      if (!disableOutput) {
        this.printInfo()
      }
    }
    this.printResult()
  }

  printInfo() {
    for (let e of this.list) {
      e.printInfo()
    }
    console.log('---------------------------------')
  }

  printResult() {
    console.log('-------------RESULTS-------------')
    const { tCurr } = this
    for (let e of this.list) {
      e.printResult()
      if (e instanceof Process) {
        const meanQ = Number(e.getMeanQueue() / tCurr).toFixed(2)
        const failP = Number(e.getFailure() / e.getQuantity()).toFixed(2)
        console.log(`mean length of queue = ${meanQ}`)
        console.log(`failure probability = ${failP}`)

        switch(e.getName()) {
          case 'PROCESSOR 1': {
            result.p1Quant.push(e.quantity)
            result.p1MeanQ.push(meanQ)
            result.p1FailP.push(failP)
            break
          }
          case 'PROCESSOR 2': {
            result.p2Quant.push(e.quantity)
            result.p2MeanQ.push(meanQ)
            result.p2FailP.push(failP)
            break
          }
          case 'PROCESSOR 3': {
            result.p3Quant.push(e.quantity)
            result.p3MeanQ.push(meanQ)
            result.p3FailP.push(failP)
            break
          }
        }
      } else {
        result.cQuant.push(e.quantity)
      }
    }
  }
}

const modelRunner = (cConfig, p1Config, p2Config, p3Config) => {
  const c = new Create(cConfig.delay) // 2
  c.setName('CREATOR')
  c.setDistribution(cConfig.distr) // 'exp'
  result.cDelay.push(cConfig.delay)
  
  const p1 = new Process(p1Config.delay)
  p1.setName('PROCESSOR 1')
  p1.setDistribution(p1Config.distr)  // 'exp'
  p1.setMaxqueue(p1Config.maxq) // 5
  p1.outActCallBack = () => p2.inAct()
  result.p1Delay.push(p1Config.delay)
  result.p1Maxq.push(p1Config.maxq)
  
  const p2 = new Process(p2Config.delay)
  p2.setName('PROCESSOR 2')
  p2.setDistribution(p2Config.distr)
  p2.setMaxqueue(p2Config.maxq)
  p2.outActCallBack = () => p3.inAct()
  result.p2Delay.push(p2Config.delay)
  result.p2Maxq.push(p2Config.maxq)
  
  const p3 = new Process(p3Config.delay)
  p3.setName('PROCESSOR 3')
  p3.setDistribution(p3Config.distr)
  p3.setMaxqueue(p3Config.maxq)
  result.p3Delay.push(p3Config.delay)
  result.p3Maxq.push(p3Config.maxq)
  
  c.setNextElement(p1)

  const list = [c, p1, p2, p3]

  const model = new Model(list)
  model.simulate(1000, true)
}

const test1 = [
  { delay: 2, distr: 'exp' },
  { delay: 1, distr: 'exp', maxq: 5 },
  { delay: 2, distr: 'exp', maxq: 5 },
  { delay: 3, distr: 'exp', maxq: 5 },
]

const test2 = [
  { delay: 3, distr: 'exp' },
  { delay: 3, distr: 'exp', maxq: 5 },
  { delay: 3, distr: 'exp', maxq: 5 },
  { delay: 3, distr: 'exp', maxq: 5 },
]

const test3 = [
  { delay: 2, distr: 'exp' },
  { delay: 1, distr: 'exp', maxq: 5 },
  { delay: 1, distr: 'exp', maxq: 5 },
  { delay: 1, distr: 'exp', maxq: 5 },
]

const test4 = [
  { delay: 3, distr: 'exp' },
  { delay: 1, distr: 'exp', maxq: 3 },
  { delay: 1, distr: 'exp', maxq: 3 },
  { delay: 1, distr: 'exp', maxq: 3 },
]

const test5 = [
  { delay: 2, distr: 'exp' },
  { delay: 2, distr: 'exp', maxq: 1 },
  { delay: 2, distr: 'exp', maxq: 1 },
  { delay: 2, distr: 'exp', maxq: 1 },
]

const test6 = [
  { delay: 2, distr: 'exp' },
  { delay: 3, distr: 'exp', maxq: 5 },
  { delay: 3, distr: 'exp', maxq: 5 },
  { delay: 3, distr: 'exp', maxq: 5 },
]

const test7 = [
  { delay: 5, distr: 'exp' },
  { delay: 2, distr: 'exp', maxq: 5 },
  { delay: 2, distr: 'exp', maxq: 5 },
  { delay: 2, distr: 'exp', maxq: 5 },
]

const test8 = [
  { delay: 5, distr: 'exp' },
  { delay: 2, distr: 'exp', maxq: 5 },
  { delay: 3, distr: 'exp', maxq: 5 },
  { delay: 4, distr: 'exp', maxq: 5 },
]

const test9 = [
  { delay: 5, distr: 'exp' },
  { delay: 4, distr: 'exp', maxq: 10 },
  { delay: 3, distr: 'exp', maxq: 8 },
  { delay: 2, distr: 'exp', maxq: 6 },
]

const test10 = [
  { delay: 3, distr: 'exp' },
  { delay: 3, distr: 'exp', maxq: 3 },
  { delay: 3, distr: 'exp', maxq: 3 },
  { delay: 3, distr: 'exp', maxq: 3 },
]

const test11 = [
  { delay: 10, distr: 'exp' },
  { delay: 2, distr: 'exp', maxq: 5 },
  { delay: 2, distr: 'exp', maxq: 5 },
  { delay: 2, distr: 'exp', maxq: 5 },
]

const test12 = [
  { delay: 10, distr: 'exp' },
  { delay: 50, distr: 'exp', maxq: 3 },
  { delay: 40, distr: 'exp', maxq: 3 },
  { delay: 30, distr: 'exp', maxq: 3 },
]

const tests = [
  test1,
  test2,
  test3,
  test4,
  test5,
  test6,
  test7,
  test8,
  test9,
  test10,
  test11,
  test12,
]

const result = {
  cDelay: [],
  // p1
  p1Delay: [],
  p1Maxq: [],
  // p2
  p2Delay: [],
  p2Maxq: [],
  // p3
  p3Delay: [],
  p3Maxq: [],
  // c
  cQuant: [],
  // p1
  p1Quant: [],
  p1MeanQ: [],
  p1FailP: [],
  // p2
  p2Quant: [],
  p2MeanQ: [],
  p2FailP: [],
  // p3
  p3Quant: [],
  p3MeanQ: [],
  p3FailP: [],
}

tests.forEach((test) => {
  modelRunner(...test)
})

buildTable(result)
