import actions, { moveActionsList } from '../actions'
import { pickRandom } from './utils'

class Agent {
  constructor() {
    this.energySpent = 0
  }

  suck() {
    this.energySpent += 2
    return actions.suck
  }

  move() {
    this.energySpent++
    return pickRandom(moveActionsList)
  }

  perceive ({ isDirty }) {
    return isDirty
      ? this.suck()
      : this.move()
  }
}

export default Agent
