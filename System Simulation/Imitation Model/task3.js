const store = {
  successClients: [],
}
const simulationTime = 10000

const c = new Create(0.5)
const p1 = new Process(0.3, 1)
const p2 = new Process(0.3, 1)
const d = new Process(0, 1)

let changes = 0

c.setName('CREATE')
p1.setName('PROCESS 1')
p2.setName('PROCESS 2')
d.setName('DISPOSE')

p1.setMaxqueue(3)
p2.setMaxqueue(3)
d.setMaxqueue(Number.MAX_VALUE)

p1.setBranch([{ nextElement: d, probability: 1 }])
p2.setBranch([{ nextElement: d, probability: 1 }])

p1.outActCallback = () => {
  const p1Queue = p1.getQueueSize()
  const p2Queue = p2.getQueueSize()

  if (p2Queue - p1Queue >= 2) {
    const item = p2.removeQueueItem()
    p1.addQueueItem(item)
    changes++
  }
}

p2.outActCallback = () => {
  const p1Queue = p1.getQueueSize()
  const p2Queue = p2.getQueueSize()

  if (p1Queue - p2Queue >= 2) {
    const item = p1.removeQueueItem()
    p2.addQueueItem(item)
    changes++
  }
}

const routes_C_P1_P2 = [p1, p2]
routes_C_P1_P2.priority = p1

c.setPriorityBranch(routes_C_P1_P2)

const list = [c, p1, p2, d]
const model = new Model(list)
model.simulate(simulationTime, true)

const p1MeanLoad = (p1.getMeanLoad() / simulationTime)
const p2MeanLoad = (p2.getMeanLoad() / simulationTime)

const p1MeanQueue = (p1.getMeanQueue() / simulationTime)
const p2MeanQueue = (p2.getMeanQueue() / simulationTime)

const averageClients = p1MeanLoad + p1MeanQueue + p2MeanLoad + p2MeanQueue

const averageTime = Number(store.successClients.reduce((sum, item) => {
  return sum + ((item.deletionTime - item.creationTime) / 1000)
}, 0) / store.successClients.length).toFixed(4)

console.log('Average clients', averageClients)
console.log('Average time', averageTime)
console.log('Changes', changes)
