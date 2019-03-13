const thead = document.getElementById('thead')
const tbody = document.getElementById('tbody')

// const results = {
//   a: [1, 2, 3],
//   b: [0, 0, 0],
//   c: [3, 3, 3],
// }

function buildTable(results) {
  const buildHead = () => {
    const headTitles = Object.keys(results)
    const tr = document.createElement('tr')
    headTitles.forEach((headTitle) => {
      const th = document.createElement('th')
      th.innerHTML = headTitle
      tr.appendChild(th)
    })
    thead.appendChild(tr)
  }

  const buildBody = () => {
    const values = Object.values(results)
    const { length } = values[0]
    for (let i = 0; i < length; i++) {
      const tr = document.createElement('tr')
      values.forEach((data) => {
        const td = document.createElement('td')
        td.innerHTML = data[i]
        tr.appendChild(td)
      })
      tbody.appendChild(tr)
    }
  }

  buildHead()
  buildBody()
}

// buildTable(results)
