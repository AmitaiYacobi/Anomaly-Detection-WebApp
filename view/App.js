
const dropZone = document.querySelector('.drop-zone');
button = dropZone.querySelector('button');
input = dropZone.querySelector('input');

let file;
let csvToJson;

button.onclick = () => {
  input.click();
};

input.addEventListener('change', function() {
  file = this.files[0];
  showFile();
});


// If user draggs file over drag-zone
dropZone.addEventListener('dragover', (event) => {
  event.preventDefault();
  console.log('File is over DragZone');
  dropZone.classList.add('active')
});

// If user leave dragged file from drag-zone
dropZone.addEventListener('dragleave', () => {
  console.log('File is outside DragZone');
  dropZone.classList.remove('active')
});

// If user drop file on drag-zone
dropZone.addEventListener('drop', (event) => {
  event.preventDefault();
  file = event.dataTransfer.files[0];
  updateThumbnail(dropZone, file);
  showFile();
});


function showFile() {
  let fileType = file.type;
  let validExtensions = ['text/csv', 'text/csv', 'text/csv'];
  if (validExtensions.includes(fileType)) {
    const reader = new FileReader();
    reader.readAsText(file);
    reader.onload = () => {
      const text = reader.result;
      csvToJson = this.csvJSON(text);
      const options = {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: csvToJson
      };
      fetch('/api/model?model_type=', options);
      console.log(csvToJson);
    };
  } else {
    alert('This is not a csv file!');
  }
}

// Convert csv file into JSON
function csvJSON(csv) {
  var data = d3.csvParse(csv);
  var headers = Object.keys(data[0]);
  var myObject = {};

  headers.forEach(function(d) {
    myObject[d] = [];
  });

  data.forEach(function(d) {
    for (var key in d) {
      myObject[key].push(d[key]);
    }
  });
  return JSON.stringify(myObject);
}

function updateThumbnail(dropZoneElement, file) {
  let thumbnailElement = dropZone.querySelector('.drop-zone__thumb');

  if (dropZoneElement.querySelector('header')) {
    dropZoneElement.querySelector('header').remove();
  }
  if (dropZoneElement.querySelector('button')) {
    dropZoneElement.querySelector('button').remove();
  }

  if (!thumbnailElement) {
    thumbnailElement = document.createElement('div');
    thumbnailElement.classList.add('drop-zone__thumb');
    dropZoneElement.appendChild(thumbnailElement);
  }
  thumbnailElement.dataset.label = file.name;
}
