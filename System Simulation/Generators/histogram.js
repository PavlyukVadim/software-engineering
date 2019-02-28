// number of intervals
const k = 20

const histogram = (ctx, intervals, frequencies) => {
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
