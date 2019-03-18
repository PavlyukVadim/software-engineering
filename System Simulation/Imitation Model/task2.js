const iterations = 5
const simulationTime = 100000

let p1QueueSum = 0
let p2QueueSum = 0
let p3QueueSum = 0
let p4QueueSum = 0

let p1LoadSum = 0
let p2LoadSum = 0
let p3LoadSum = 0
let p4LoadSum = 0

for(let i = 0; i < iterations; i++) {
  const c = new Create(2)
  const p1 = new Process(0.6, 1)
  const p2 = new Process(0.3, 1)
  const p3 = new Process(0.4, 1)
  const p4 = new Process(0.1, 2)
  const d = new Process(0, 1)

  c.setName('CREATOR')
  p1.setName('PROCESSOR 1')
  p2.setName('PROCESSOR 2')
  p3.setName('PROCESSOR 3')
  p4.setName('PROCESSOR 4')
  d.setName('DISPOSE')

  p1.setMaxqueue(Number.MAX_VALUE)
  p2.setMaxqueue(Number.MAX_VALUE)
  p3.setMaxqueue(Number.MAX_VALUE)
  p4.setMaxqueue(Number.MAX_VALUE)

  const branch_P2_P3_P4_D = [
    // routes for p1 -> p2
    {
      nextElement: p2,
      probability: 0.15,
    },
    // routes for p1 -> p3
    {
      nextElement: p3,
      probability: 0.13,
    },
    // routes for p1 -> p4
    {
      nextElement: p4,
      probability: 0.3,
    },
    // routes for p1 -> d
    {
      nextElement: d,
      probability: 0.42,
    },
  ]

  const branch_P2_P1 = [
    {
      nextElement: p1,
      probability: 1,
    }
  ]

  const branch_P3_P1 = [
    {
      nextElement: p1,
      probability: 1,
    }
  ]

  const branch_P4_P1 = [
    {
      nextElement: p1,
      probability: 1,
    }
  ]

  c.setNextElement(p1)
  p1.setBranch(branch_P2_P3_P4_D)
  p2.setBranch(branch_P2_P1)
  p3.setBranch(branch_P3_P1)
  p4.setBranch(branch_P4_P1)

  const list = [c, p1, p2, p3, p4, d]

  const model = new Model(list)
  model.simulate(simulationTime, true)

  const p1MeanQueue = (p1.getMeanQueue() / simulationTime)
  const p2MeanQueue = (p2.getMeanQueue() / simulationTime)
  const p3MeanQueue = (p3.getMeanQueue() / simulationTime)
  const p4MeanQueue = (p4.getMeanQueue() / simulationTime)

  p1QueueSum += p1MeanQueue
  p2QueueSum += p2MeanQueue
  p3QueueSum += p3MeanQueue
  p4QueueSum += p4MeanQueue

  const p1MeanLoad = (p1.getMeanLoad() / simulationTime)
  const p2MeanLoad = (p2.getMeanLoad() / simulationTime)
  const p3MeanLoad = (p3.getMeanLoad() / simulationTime)
  const p4MeanLoad = (p4.getMeanLoad() / simulationTime)

  p1LoadSum += p1MeanLoad
  p2LoadSum += p2MeanLoad
  p3LoadSum += p3MeanLoad
  p4LoadSum += p4MeanLoad
}

p1QueueSum /= iterations
p2QueueSum /= iterations
p3QueueSum /= iterations
p4QueueSum /= iterations

p1LoadSum /= iterations
p2LoadSum /= iterations
p3LoadSum /= iterations
p4LoadSum /= iterations

const p1QueueSumT = 1.786
const p2QueueSumT = 0.003
const p3QueueSumT = 0.004
const p4QueueSumT = 0.00001

const p1LoadSumT = 0.714
const p2LoadSumT = 0.054
const p3LoadSumT = 0.062
const p4LoadSumT = 0.036

p1QueueSum = Number(p1QueueSum).toFixed(8)
p2QueueSum = Number(p2QueueSum).toFixed(8)
p3QueueSum = Number(p3QueueSum).toFixed(8)
p4QueueSum = Number(p4QueueSum).toFixed(8)

p1LoadSum = Number(p1LoadSum).toFixed(8)
p2LoadSum = Number(p2LoadSum).toFixed(8)
p3LoadSum = Number(p3LoadSum).toFixed(8)
p4LoadSum = Number(p4LoadSum).toFixed(8)

console.log('p1QueueSum', p1QueueSum)
console.log('p2QueueSum', p2QueueSum)
console.log('p3QueueSum', p3QueueSum)
console.log('p4QueueSum', p4QueueSum)

console.log('p1LoadSum', p1LoadSum)
console.log('p2LoadSum', p2LoadSum)
console.log('p3LoadSum', p3LoadSum)
console.log('p4LoadSum', p4LoadSum)

console.log('p1QueueSum %', (p1QueueSumT - p1QueueSum) * 100)
console.log('p2QueueSum %', (p2QueueSumT - p2QueueSum) * 100)
console.log('p3QueueSum %', (p3QueueSumT - p3QueueSum) * 100)
console.log('p4QueueSum %', (p4QueueSumT - p4QueueSum) * 100)
