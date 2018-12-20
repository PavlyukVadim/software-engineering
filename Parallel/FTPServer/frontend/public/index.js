window.onload = () => {
  const btnGetFilesList = document.getElementById('btn-get-files-lst')
  const userNameInput = document.getElementById('user-name')
  const filesDropDown = document.getElementById('files-list-DropDown')


  btnGetFilesList.onclick = async (e) => {
    e.preventDefault()
    e.stopPropagation()
    const userName = userNameInput.value
    const response = await getFilesListByUserName(userName)
    const data = await response.json()
    if (data.type === 'filesList') {
      const files = data.payload
      filesDropDown.innerHTML = ''
      files.forEach((fileName) => {
        const a = document.createElement('a')
        a.innerHTML = fileName
        a.className = 'dropdown-item'
        a.setAttribute('target', '_blank')
        a.setAttribute('href', `data/${userName}/${fileName}`)
        filesDropDown.appendChild(a)
      })
    }
    console.log('data', data)
  }
}

const getFilesListByUserName = function (userName) {
  const url = `/user/${userName}`
  return fetch(url)
}
