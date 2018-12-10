window.onload = () => {
  const btnGetFilesList = document.getElementById('btn-get-files-lst')
  const userNameInput = document.getElementById('user-name')
  
  btnGetFilesList.onclick = async (e) => {
    e.preventDefault()
    e.stopPropagation()
    const userName = userNameInput.value
    const list = await getFilesListByUserName(userName)
    alert(userNameInput.value)
  }
}

const getFilesListByUserName = function (userName) {
  const url = `/user/${userName}`
  return fetch(url)
}
