const store = {
  successClients: [],
  disposedClients: [],
  outedClients: [],
  returnedToDoctors: 0,
  c1SumCreation: 0,
  c2SumCreation: 0,
  c3SumCreation: 0,
  outSumCreation: 0,
  desposeSumCreation: 0,
}
const simulationTime = 10000

// deley = time / frequencу
const c1 = new Create(30)
const c2 = new Create(150)
const c3 = new Create(37.5)

c1.setName('Pation1 Creator')
c2.setName('Pation2 Creator')
c3.setName('Pation3 Creator')

// 2 doctors for c1, c2, c3
const p1 = new Process(15, 2)
p1.setMaxqueue(Number.MAX_VALUE)


// 3 chambers for c1
const p2 = new Process(5.5, 3, 2.5)

// 1 registry
const p3 = new Process(4.5, 1)

// 2 laborants for c2, c3
const p4 = new Process(4, 2)

const d = new Process(0, 1)
d.setName('DISPOSE')

const o = new Process(0, 1)
o.setName('OUT')

// const p5 = new Process(0.3, 1)
// const p6 = new Process(0.3, 1)

p1.setName('Doctors')
p2.setName('Chambers')
p3.setName('Registry')
p4.setName('Laborants')
// p5.setName('Doctors - Registry')
// p6.setName('Lab - Doctors')

// const p2 = new Process(0.3, 1)
// const d = new Process(0, 1)


c1.setNextElement(p1)
c2.setNextElement(p1)
c3.setNextElement(p1)

p1.setPriorityQueueTarget(c1)

const typeBranch = [
  // (c1) p1 => p2
  {
    type: c1,
    nextElement: p2,
  },
  // (c2) p1 => p3
  {
    type: c2,
    nextElement: p3,
  },
  // (c3) p1 => p3
  {
    type: c3,
    nextElement: p3,
  }
]

p1.setTypeBranch(typeBranch)
// after Chamber -> Dispose
p2.setBranch([{ nextElement: d, probability: 1 }])

// after Registry -> Laborants
p3.setBranch([{ nextElement: p4, probability: 1 }])


const typeBranchForOut = [
  // (c2) p4 => p3
  {
    type: c2,
    nextElement: p3,
    itemCreator: c1,
  },
  // (c3) p4 => o
  {
    type: c3,
    nextElement: o,
  }
]

p4.setTypeBranch(typeBranchForOut)

const list = [
  c1, c2, c3,
  p1,
  p2, p3,
  p4,
  d, o,
]

const model = new Model(list)
model.simulate(simulationTime, true)

console.log('store.returnedToDoctors', store.returnedToDoctors)
console.log('store', store)

const p12avarage = store.disposedClients.reduce((s, item) => {
  return s + ((item.deletionTime - item.creationTime) * 1000)
}, 0) / store.disposedClients.length

const p3avarage = store.outedClients.reduce((s, item) => {
  return s + ((item.deletionTime - item.creationTime) * 1000)
}, 0) / store.outedClients.length

console.log('p12avarage', p12avarage)
console.log('p3avarage', p3avarage)
// console.log('P3 avarage time', (Math.abs(store.outSumCreation - store.c3SumCreation)))