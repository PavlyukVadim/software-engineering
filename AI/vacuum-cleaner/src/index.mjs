import Environment from './Environment'
import VacuumCleanerWorld from './VacuumCleanerWorld'
import RandomReflexAgent from './agents/RandomReflexAgent'
import SimpleReflexAgent from './agents/SimpleReflexAgent'
import ModelBasedReflexAgent from './agents/ModelBasedReflexAgent'

const initialDirtAppearanceProbability = 0.01

const simpleReflexAgent = new SimpleReflexAgent()
const modelBasedReflexAgent = new ModelBasedReflexAgent()
const randomReflexAgent = new RandomReflexAgent()

const createWorld = (dirtAppearanceProbability, agent) => {
  const env = Environment({ dirtAppearanceProbability })
  return VacuumCleanerWorld(env, agent)
}

const output = (grid) => {
  grid.forEach((row) => {
    let str = ''
    row.forEach((cell) => {
      const { isWall, hasVacuumCleaner, isClean, isDirty } = cell
      let s = ''
      if (isWall) s = '█'
      else if (hasVacuumCleaner) s = '@'
      else if (isDirty) s = 'r'
      else if (isClean) s = ' '      

      str += s
    })
    console.log(str)
  }) 
}

const worlds = [
  createWorld(initialDirtAppearanceProbability, simpleReflexAgent),
  createWorld(initialDirtAppearanceProbability, modelBasedReflexAgent),
  createWorld(initialDirtAppearanceProbability, randomReflexAgent),
]

worlds.forEach(world => {
  world.trashCountOnEachStep = []
})

const dirtyCount = (grid) => {
  let count = 0
  grid.forEach(c => {
    c.forEach(cc => {
      if (cc.isDirty) {
        count++
      }
    })
  })
  return count
}

let i = 0
const N = 1000
while(i < N) {
  i++
  worlds.forEach(world => {
    world.performNextAction()
    world.trashCountOnEachStep.push(dirtyCount(world.environment.grid))
  })
}

console.log('simpleReflexAgent', simpleReflexAgent.energySpent)
console.log('modelBasedReflexAgent', modelBasedReflexAgent.energySpent)
console.log('randomReflexAgent', randomReflexAgent.energySpent)

console.log('--------')

worlds.forEach((world) => {
  const sum = world.trashCountOnEachStep.reduce((ac, el) => el + ac)
  console.log('trashCountOnEachStep', sum / N)
})
