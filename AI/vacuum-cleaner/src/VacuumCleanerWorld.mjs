export default (environment, agent, debug) => {
  let lastPercept = environment.percept
  return {
    environment,
    agent,
    performNextAction: () => {
      const action = agent.perceive(lastPercept)
      lastPercept = environment.acceptAction(action)
      if (debug) {
        console.log(`Action: ${action}. Percept: ${JSON.stringify(lastPercept)}`)
      }
    }
  }
}
