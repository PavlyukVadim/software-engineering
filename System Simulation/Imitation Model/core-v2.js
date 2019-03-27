// core based on a real queue (from array)

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
      this.distribution = 'exp'
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
    super('', delay)
  }

  setPriorityBranch(routes) {
    this.priorityBranch = routes
  }

  outAct() {
    super.outAct()
    const tCurr = this.getTcurr()
    this.setTnext(tCurr + this.getDelay())

    if (this.name === 'Pation1 Creator') {
      store.c1SumCreation += +new Date()
    } else if (this.name === 'Pation2 Creator') {
      store.c2SumCreation += +new Date()
    } else if (this.name === 'Pation3 Creator') {
      store.c3SumCreation += +new Date()
    }
    // this.getNextElement().inAct()

    if (this.priorityBranch) {
      let nextElement = this.priorityBranch.priority

      this.priorityBranch.forEach((process) => {
        if(process.getQueueSize() < nextElement.getQueueSize()) {
          nextElement = process
        }
      })
      nextElement.inAct(this)
    } else {
      this.getNextElement().inAct(this)
    }
  }
}

class Process extends Element {
  constructor(delay, workersNumber = 1) {
    super('', delay)
    this.queue = []
    this.maxqueue = Number.MAX_SAFE_INTEGER
    this.meanQueue = 0
    this.meanLoad = 0
    this.failure = 0
    this.workers = Array
      .from({length: workersNumber})
      .map(() => ({
        state: 0,
        nextTime: Number.MAX_VALUE,
        done: 0,
        meanLoad: 0,
      }))
  }

  getFreeWorker() {
    const freeWorker = this.workers.find((worker) => {
      return (worker.state === 0)
    })
    return freeWorker
  }

  getLastActiveWorker() {
    const minNextTime = this.getWorkersMinNextTime()

    const lastActiveWorker = this.workers.find((worker) => {
      return (worker.nextTime === minNextTime)
    })
    return lastActiveWorker
  }

  getWorkersMinNextTime() {
    const nextTimes = this.workers
      .map((worker) => worker.nextTime)
  
    const minNextTime = Math.min(...nextTimes)
    return minNextTime
  }

  activateWorker(worker, creatorItem) {
    worker.state = 1
    worker.nextTime = this.getTcurr() + this.getDelay()
    this.lastWorkedCreatorItem = creatorItem

    const queueItem = {
      creationTime: new Date(),
      creatorItem,
    }

    worker.item = queueItem

    if (this.name === 'DISPOSE') {
      store.disposedClients.push(queueItem)
    }
  }

  getTnext() {
    const minNextTime = this.getWorkersMinNextTime()
    return minNextTime
  }

  setBranch(branch) {
    this.branch = branch
  }

  setTypeBranch(typeBranch) {
    this.typeBranch = typeBranch
  }

  setPriorityQueueTarget(priorityQueueTarget) {
    this.priorityQueueTarget = priorityQueueTarget
  }

  inAct(creatorItem) {
    const freeWorker = this.getFreeWorker()
    if (freeWorker) {
      this.activateWorker(freeWorker, creatorItem)
    } else {
      const queueSize = this.getQueueSize()
      const maxQueueSize = this.getMaxQueueSize()
      if (queueSize < maxQueueSize) {
        const queueItem = {
          creationTime: new Date(),
          creatorItem,
        }
        this.addQueueItem(queueItem)
      } else {
        this.failure++
      }
    }
  }

  outAct() {
    super.outAct()
    const worker = this.getLastActiveWorker()
    worker.nextTime = Number.MAX_VALUE
    worker.state = 0
    worker.item.deletionTime = new Date()
    worker.done++

    if (this.name === 'OUT') {
      store.outedClients.push(worker.item)
      store.outSumCreation += +new Date()
    } else if (this.name === 'DISPOSE') {
      store.desposeSumCreation += +new Date()
    }
    

    let lastQueueItem = {}
    const queueSize = this.getQueueSize()
    if (queueSize > 0) {
      lastQueueItem = this.removeQueueItem()
      lastQueueItem.deletionTime = new Date()
      lastQueueItem.worker = worker
      worker.state = 1
      worker.nextTime = this.getTcurr() + this.getDelay()
    }

     if (this.typeBranch) {
      const route = this.typeBranch.find((typeRoute) => {
        return (typeRoute.type === this.lastWorkedCreatorItem)
      })

      if (route) {
        const routeItemCreator = route.itemCreator
        // console.log('routeItemCreator', routeItemCreator)
        if (routeItemCreator) {
          store.returnedToDoctors++
          this.lastWorkedCreatorItem = routeItemCreator
        }
        route.nextElement.inAct(routeItemCreator || this.lastWorkedCreatorItem)
      }
    }

    if (this.branch) {
      const probability = Math.random()

      // transforms [0.3, 0.3, 0.4] into [0.3, 0.6, 1]
      const routesProbabilitiesMaxValues = []
      this.branch.forEach((route, i) => {
        routesProbabilitiesMaxValues[i] =
          route.probability + (routesProbabilitiesMaxValues[i - 1] || 0)
      })

      const routeIndex = routesProbabilitiesMaxValues
        .findIndex((value) => value >= probability)

      const route = this.branch[routeIndex]
      route.nextElement.inAct(this.lastWorkedCreatorItem)
    }
    
    if (this.outActCallback) {
      this.outActCallback()
    }
  }

  doStatistics(delta) {
    super.doStatistics()
    const queueSize = this.getQueueSize()
    this.meanQueue = this.getMeanQueue() + queueSize * delta
    this.workers.forEach((worker) => {
      worker.meanLoad += worker.state * delta
    })
  }

  getFailure = () => this.failure

  getQueueSize = () => this.queue.length

  addQueueItem(queueItem) {
    this.queue.push(queueItem)
  }

  removeQueueItem() {
    // implement priority queue
    this.queue.sort((item) => {
      return (item.creatorItem === this.priorityQueueTarget)
        ? -1
        : 1
    })
    
    const firstItem = this.queue.shift()
    return firstItem
  }

  getMaxQueueSize = () => this.maxqueue
    
  setMaxqueue(maxqueue) {
    this.maxqueue = maxqueue
  }

  printInfo() {
    super.printInfo()
    console.log(`queue = ${this.getQueueSize()}`)
    console.log(`failure = ${this.getFailure()}`)
  }

  getMeanQueue = () => this.meanQueue

  getMeanLoad = () => {
    let load = 0
    this.workers.forEach((worker) => {
      load += worker.meanLoad
    })
    return load
  }
}

class Model {
  constructor(elements = []) {
    this.list = [...elements]
    this.tNext = 0
    this.event = 0
    this.tCurr = this.tNext
  }

  simulate(time, hideOutput) {
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
      
      if (!hideOutput) {
        console.log(`It's time for event in ${eventName}, time = ${this.tNext}`)
      }

      for (let e of this.list) {
        e.doStatistics(this.tNext - this.tCurr)
      }

      this.tCurr = this.tNext

      for (let e of this.list) {
        e.setTcurr(this.tCurr)
      }

      if (typeof event.outAct === 'function') {
        event.outAct()
      }
      for (let e of this.list) {
        if (e.getTnext() == this.tCurr) {
          e.outAct()
        }
      }

      if (!hideOutput) {
        this.printInfo()  
      }
    }
    this.printResult(time)
  }

  printInfo() {
    for (let e of this.list) {
      e.printInfo()
    }
    console.log('---------------------------------')
  }

  printResult(time) {
    console.log('-------------RESULTS-------------')
    console.log('TIME: ', time)
    const { tCurr } = this
    for (let e of this.list) {
      e.printResult()
      if (e instanceof Process) {
        const meanQueue = Number(e.getMeanQueue() / tCurr).toFixed(2)
        const failureProb = Number(e.getFailure() / e.getQuantity()).toFixed(2)
        console.log('mean length of queue:', meanQueue)
        console.log('failure probability:', failureProb)
        console.log('workers:')
        e.workers.forEach((worker, index) => {
          const { done, meanLoad } = worker
          console.log('  worker#', index + 1)
          console.log('    done:', done)
          console.log('    meanLoad:', Number(meanLoad / tCurr).toFixed(2))
        })
        console.log('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
      }
    }
  }
}
