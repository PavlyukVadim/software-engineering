import actions from './actions'

export const getPositionAfterMove = (move, [prevX, prevY]) => {
  switch(move) {
    case actions.moveUp: return [prevX - 1, prevY]
    case actions.moveDown: return [prevX + 1, prevY]
    case actions.moveLeft: return [prevX, prevY - 1]
    case actions.moveRight: return [prevX, prevY + 1]
  }
}
