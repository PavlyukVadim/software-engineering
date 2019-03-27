const config = {
  createDelayRange: [1, 3],
  createDistribution: 'exp',
  processDelayRange: [2, 5],
  processDistribution: 'exp',
  processWorkers: 1,
  processMaxqueueRange: [1, 5],
}

const getValueFromRange = (range) => {
  const [min, max] = range
  return Math.round(Math.random() * (max - min)) + min
}

const modelSimulateWrapper = (n, time) => {
  const cDelay = getValueFromRange(config.createDelayRange)
  const c = new Create(cDelay)
  c.setName('CREATOR')
  c.setDistribution(config.createDistribution)

  const processes = []
  let prevProcess = null
  let processesAmount = 0
  while(processes.length < n) {
    const pDelay = getValueFromRange(config.processDelayRange)
    const pMaxQueue = getValueFromRange(config.processMaxqueueRange)
    const p = new Process(pDelay, config.processWorkers)
    p.setName(`PROCESSOR ${processesAmount + 1}`)
    p.setDistribution(config.processDistribution)
    p.setMaxqueue(pMaxQueue)
    processesAmount = processes.push(p)

    if (processesAmount === 1) {
      c.setNextElement(p)
    }
    if (prevProcess) {
      prevProcess.setBranch([{ nextElement: p, probability: 1 }])
    }
    prevProcess = p
  }
  
  const list = [c, ...processes]
  const model = new Model(list)

  const startTime = new Date()
  model.simulate(time, true, true)
  const endTime = new Date()
  const workingTime = (endTime - startTime) / 1000
  console.log('N', n, ':', 'working time', workingTime)
}

modelSimulateWrapper(1, 1000)
modelSimulateWrapper(2, 1000)
modelSimulateWrapper(5, 1000)
modelSimulateWrapper(10, 1000)
modelSimulateWrapper(20, 1000)
modelSimulateWrapper(50, 1000)
modelSimulateWrapper(100, 1000)
modelSimulateWrapper(200, 1000)
modelSimulateWrapper(500, 1000)
