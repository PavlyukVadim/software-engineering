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

  printInfo = () => {
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

  simulate(time) {
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
      console.log(`It's time for event in ${eventName}, time = ${this.tNext}`)
      
      for (let e of this.list) {
        e.doStatistics(this.tNext - this.tCurr)
      }

      this.tCurr = this.tNext
      // console.log('this.tCurr', this.tCurr)

      for (let e of this.list) {
        e.setTcurr(this.tCurr)
      }

      event.outAct()
      for (let e of this.list) {
        if (e.getTnext() == this.tCurr) {
          e.outAct()
        }
      }

      this.printInfo()
    }
    this.printResult()
  }

  printInfo() {
    for (let e of this.list) {
      e.printInfo()
    }
  }

  printResult() {
    console.log('-------------RESULTS-------------')
    const { tCurr } = this
    for (let e of this.list) {
      e.printResult()
      if (e instanceof Process) {
        // console.log('e.getMeanQueue()', e.getMeanQueue())
        // console.log('this.tCurr', tCurr)
        // console.log('e.getFailure()', e.getFailure())
        console.log(`mean length of queue = ${e.getMeanQueue() / tCurr}`)
        console.log(`failure probability = ${e.getFailure() / e.getQuantity()}`)
      }
    }
  }
}


const c = new Create(2)
const p = new Process(1)

console.log(`id0 = ${c.getId()} id1 = ${p.getId()}`)

c.setNextElement(p)
p.setMaxqueue(5)
c.setName('CREATOR')
p.setName('PROCESSOR')
c.setDistribution('exp')
p.setDistribution('exp')

console.log('c', c)
console.log('p', p)

const list = [c, p]

const model = new Model(list)
model.simulate(100)
