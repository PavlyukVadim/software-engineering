import minBy from 'ramda/src/minBy'
import actions, { moveActionsList } from '../actions'
import { isMove } from '../actions'
import { getPositionAfterMove } from './../util'

const initialPosition = Object.freeze([9, 9])

const createCell = () => ({ lastVisited: -Infinity })
const createRow = () => Array(19).fill(null).map(createCell)
const createGrid = () => {
  const grid = Array(19).fill(null).map(createRow)
  const [x, y] = initialPosition
  grid[x][y].isWall = false
  return grid
}

class Agent {
  constructor() {
    this.exploredGrid = createGrid()
    this.position = initialPosition
    this.iterationNum = 0
    this.prevAction = null
    this.energySpent = 0
  }

  getDestination(action) {
    const [x, y] = getPositionAfterMove(action, this.position)
    return this.exploredGrid[x][y]
  }

  suck() {
    this.energySpent += 2
    return actions.suck
  }

  moveOrIdle() {
    const possibleMoves = moveActionsList
      .map(action => ({ action, destination: this.getDestination(action) }))
      .filter(({ destination: { isWall = false } }) => !isWall)
    if (possibleMoves.length) {
      this.energySpent++
      return possibleMoves
        .reduce(minBy(({ destination: { lastVisited } }) => lastVisited))
        .action
    } else {
      return actions.idle
    }
  }

  perceiveMove(bumpOccurred) {
    const [newX, newY] = getPositionAfterMove(this.prevAction, this.position)
    if (bumpOccurred) {
      this.exploredGrid[newX][newY].isWall = true
    } else {
      this.exploredGrid[newX][newY].isWall = false
      const [oldX, oldY] = this.position
      this.exploredGrid[oldX][oldY].lastVisited = this.iterationNum
      this.position = [newX, newY]
    }
  }

  perceive({ bumpOccurred, isDirty }) {
    if (isMove(this.prevAction)) this.perceiveMove(bumpOccurred)
    this.prevAction = isDirty
      ? this.suck()
      : this.moveOrIdle()

    this.iterationNum++
    return this.prevAction
  }
}

export default Agent
