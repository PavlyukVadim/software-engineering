const store = {
  successClients: [],
}
const simulationTime = 10000

// deley = time / frequencу
const c1 = new Create(30)
const c2 = new Create(150)
const c3 = new Create(37.5)

c1.setName('Pation1 Creator')
c2.setName('Pation2 Creator')
c3.setName('Pation3 Creator')

const p1 = new Process(0.3, 1)
const p2 = new Process(0.3, 1)
const p3 = new Process(0.3, 1)
const p4 = new Process(0.3, 1)
const p5 = new Process(0.3, 1)
const p6 = new Process(0.3, 1)

p1.setName('Doctors')
p2.setName('Chamber')
p3.setName('Registry')
p4.setName('Lab')
p5.setName('Doctors - Registry')
p6.setName('Lab - Doctors')

// const p2 = new Process(0.3, 1)
// const d = new Process(0, 1)