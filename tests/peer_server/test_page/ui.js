
function openTab(evt, tabName) {
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablinks");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" active", "");
  }
  document.getElementById(tabName).style.display = "block";
  evt.currentTarget.className += " active";
}

function initUi() {
  // select the first tab
  document.getElementById("tab1").style.display = "block";
  document.getElementById("button_tab1").className += " active";
  document.getElementById("server").value = config.URL_SERVER_HTTPS;
}

function showMessage(message) {
  document.getElementById("cmdResult").value = message;
}