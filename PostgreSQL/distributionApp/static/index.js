// var data = {};
// data.title = "title";
// data.message = "message";

// $.ajax({
//   type: 'POST',
//   data: JSON.stringify(data),
//   contentType: 'application/json',
//   url: 'http://localhost:3000/',            
//   success: function(data) {
//     console.log('success');
//     console.log(JSON.stringify(data));
//   }
//  }
// );

const loader = $('.loader');

const hideLoader = () => {
  loader.css('display', 'none');  
};
hideLoader();

const showLoader = () => {
  loader.css('display', 'block');  
};

const clearTablesBtn = $('.clear-tables');
clearTablesBtn.on('click', () => {
  clearAllTables();
});

const clearAllTables = () => {
  showLoader();
  const data = {
    target: 'tables'
  };

  $.ajax({
    type: 'DELETE',
    data: JSON.stringify(data),
    contentType: 'application/json',
    url: 'http://localhost:3000/',            
    success: (data) => {
      console.log('deleted');
      hideLoader();
    }
   }
  );
};