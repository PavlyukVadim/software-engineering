const moveActions = {
  moveUp: 'move Up',
  moveDown: 'move Down',
  moveRight: 'move Right',
  moveLeft: 'move Left'
}

export const moveActionsList = Object.values(moveActions)

export const isMove = action => moveActionsList.includes(action)

const actions = {
  ...moveActions,
  suck: 'suck',
  idle: 'idle',  
}

export const actionsList = Object.values(actions)

export default actions
