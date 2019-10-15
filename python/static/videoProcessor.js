var video = document.getElementById("video");
var c1 = document.getElementById("c1");
var ctx1 = c1.getContext("2d");
var c2 = document.getElementById("c2");
var ctx2 = c2.getContext("2d");

var source = document.createElement('source');
const BASE_URL = 'http://localhost:5000/'
const fps = 43

function timerCallback() {
  if (this.video.paused || video.ended) {
    return;
  }
  computeFrame();

  setTimeout(function () {
    timerCallback();
  }, 1000 / fps);
}

function upLoadVideo(file){
  const formData = new FormData();
  formData.append("videoFile", file);

  const UPLOAD_URL = `${BASE_URL}upload_video`

  return fetch(UPLOAD_URL, {
      method: 'POST',
      headers:{
        'Content-Length': file.length,
        'Access-Control-Allow-Orgin': 'https://localhost:5000'
      },
      body: formData,
    })
    .then(response => {
     return response.json();
    })
    .then(json => {
      console.log("json", json);
      return json;
    })
  
}

async function doLoad(event) {
  console.log("DoLoad", event)
  
  //Get video from user
  var URL = window.URL || window.webkitURL
  var file  = document.getElementById("video_file_input").files[0]; 
  
  //Upload the video to server
  await upLoadVideo(file)
    .catch(e => console.log("Fetch error:", e));
  
  var videoURL = URL.createObjectURL(file);

  // set the new video source on the html
  // video.src = videoURL 

  video.addEventListener("play", () => {
    width = video.videoWidth / 2;
    height = video.videoHeight / 2;
    timerCallback();
  }, false);
}

function computeFrame() {
  ctx1.drawImage(video, 0, 0, width, height);
  let frame = ctx1.getImageData(0, 0, width, height);
  let l = frame.data.length / 4;

  for (let i = 0; i < l; i++) {
    let r = frame.data[i * 4 + 0];
    let g = frame.data[i * 4 + 1];
    let b = frame.data[i * 4 + 2];
    if (g > 100 && r > 100 && b < 43)
      frame.data[i * 4 + 3] = 0;
  }
  ctx2.putImageData(frame, 0, 0);
  return;
}

window.onload = () => {
  console.log("on video load")

  document.getElementById("video_file_input")
    .addEventListener('change', (event) => {
      doLoad(event);
    })
}

document.addEventListener("DOMContentLoaded", () => {
  console.log("DOMContentLoaded")
});