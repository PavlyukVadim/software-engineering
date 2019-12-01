import { pickRandom } from './utils'
import { actionsList } from '../actions'

class Agent {
  constructor() {
    this.energySpent = 0
  }

  perceive ({ isDirty }) {
    const action = pickRandom(actionsList)
    if (action === 'suck') {
      this.energySpent += 2
    }
    if (action !== 'idle') {
      this.energySpent++
    }
    return action
  }
}

export default Agent
