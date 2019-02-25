// number of intervals
const k = 20

const histogram = (ctx, array) => {
  const min = Math.min(...array)
  const max = Math.max(...array)

  const intervalSize = (max - min) / k

  const intervals = Array.from({length: k})

  intervals.reduce((prevInterval, el, index, array) => {
    array[index] = prevInterval + intervalSize
    return array[index]
  }, min)

  intervals.forEach((interval, i, arr) => {
    arr[i] = (interval).toFixed(2)
  })

  array.sort((a, b) => a - b)
  
  const numbersBeforeInterval = Array.from({length: k})
  for (let i = 0; i < numbersBeforeInterval.length; i++) {
    const intervalRightBorder = intervals[i + 1] || max
    const lastIndex = array.findIndex((number) => (number >= intervalRightBorder))
    const numbersLessThanRightBorder = (lastIndex !== -1)
      ? lastIndex
      : numbersBeforeInterval[i - 1]
    
      numbersBeforeInterval[i] = numbersLessThanRightBorder
  }

  const frequencies = numbersBeforeInterval.map((lastIndex, i, array) => {
    const prevNumbersInInterval = (array[i - 1] || 0)
    const numbersInInterval = lastIndex - prevNumbersInInterval
    return numbersInInterval
  })

  // console.log('frequencies', frequencies)    
  // console.log('intervals', intervals)

  const backgroundColors = [
    'rgba(255, 99, 132, 0.2)',
    'rgba(54, 162, 235, 0.2)',
    'rgba(255, 206, 86, 0.2)',
    'rgba(75, 192, 192, 0.2)',
    'rgba(153, 102, 255, 0.2)',
    'rgba(255, 159, 64, 0.2)'
  ]

  const borderColor = [
    'rgba(255,99,132,1)',
    'rgba(54, 162, 235, 1)',
    'rgba(255, 206, 86, 1)',
    'rgba(75, 192, 192, 1)',
    'rgba(153, 102, 255, 1)',
    'rgba(255, 159, 64, 1)',
  ]

  new Chart(ctx, {
    type: 'bar',
    data: {
      labels: intervals,
      datasets: [{
        label: '# of Votes',
        data: frequencies,
        backgroundColor: [
          ...backgroundColors,
          ...backgroundColors,
          ...backgroundColors,
          ...backgroundColors,
        ],
        borderColor: [
          ...borderColor,
          ...borderColor,
          ...borderColor,
          ...borderColor,
        ],
        borderWidth: 1
      }]
    },
    options: {
      scales: {
        yAxes: [{
          ticks: {
            beginAtZero:true,
          }
        }]
      },
      maintainAspectRatio: false,
    }
  })
}