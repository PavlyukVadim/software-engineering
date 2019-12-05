import clone from 'ramda/src/clone'
import prop from 'ramda/src/prop'
import actions, { isMove } from './actions'
import { getPositionAfterMove } from './util'

export default ({ dirtAppearanceProbability }) => {
  const grid = clone(defaultEnvironmentGrid)
  return {
    grid,
    acceptAction: (action) => {
      const { bumpOccurred = false } = isMove(action) ? applyMove(grid, action) : {}
      if (action === actions.suck) applySoak(grid)
      dirtyWorld(grid, dirtAppearanceProbability)
      return { bumpOccurred, isDirty: getVacuumCleanerCell(grid).isDirty }
    },
    get percept () {
      return {
        bumpOccurred: false,
        isDirty: getVacuumCleanerCell(grid).isDirty
      }
    },
  }
}

const createCell = ({ isDirty = false, isClean = !isDirty, isWall = false, hasVacuumCleaner = false }) => {
  if (isClean && isDirty) {
    throw Error("Cell can't be both clean and dirty")
  } if (isWall && isDirty) {
    throw Error("Walls can't be dirty")
  } else if (isWall && hasVacuumCleaner) {
    throw Error("Vacuum cleaner can't be placed in the wall")
  }
  return {
    isWall,
    hasVacuumCleaner,
    get isClean () {
      return isClean
    },
    set isClean (clean) {
      isClean = clean
      isDirty = !clean
    },
    get isDirty () {
      return isDirty
    },
    set isDirty (dirty) {
      isClean = !dirty
      isDirty = dirty
    }
  }
}

const defaultEnvironmentSchema = `
██████████
█        █
█ ██████ █
█ █      █
█ █    █ █
█ █  @ █ █
█ █    █ █
█ ██ ███ █
█        █
██████████
`

const symbolMap = {
  ' ': createCell({ isClean: true }),
  '█': createCell({ isWall: true }),
  '@': createCell({ hasVacuumCleaner: true })
}

const defaultEnvironmentGrid = defaultEnvironmentSchema
  .trim()
  .split('\n')
  .map(line =>
    [...line.trim()]
      .map(c => ({
        ' ': createCell({ isClean: true }),
        '█': createCell({ isWall: true }),
        '@': createCell({ hasVacuumCleaner: true })
      }[c]))
  )

const applyMove = (grid, action) => {
  const oldPosition = getVacuumCleanerPosition(grid)
  const newPosition = getPositionAfterMove(action, oldPosition)
  const [newX, newY] = newPosition
  const newCell = grid[newX][newY]

  if (newCell.isWall) {
    return { bumpOccurred: true }
  } else {
    getVacuumCleanerCell(grid).hasVacuumCleaner = false
    newCell.hasVacuumCleaner = true
    return { bumpOccurred: false }
  }
}

const applySoak = (grid) => {
  getVacuumCleanerCell(grid).isDirty = false
}

const getVacuumCleanerPosition = grid => grid.reduce(
  (result, row, i) => {
    const j = row.findIndex(prop('hasVacuumCleaner'))
    return j !== -1 ? [i, j] : result
  }
)

const getVacuumCleanerCell = (grid) => {
  const [x, y] = getVacuumCleanerPosition(grid)
  return grid[x][y]
}

const dirtyWorld = (grid, dirtAppearanceProbability) => {
  for (const row of grid) {
    for (const cell of row) {
      if (Math.random() < dirtAppearanceProbability) {
        cell.isDirty = true
      }
    }
  }
}
