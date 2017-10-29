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

const inputNumberOfClients = $('#input-number-of-clients');
const numberOfClients = $('#number-of-clients');
const addClientsBtn = $('#add-row-clients');

addClientsBtn.on('click', () => {
  showLoader();
  const numberOfRows = Number(inputNumberOfClients.val());
  const data = {
    numberOfRows
  };

  $.ajax({
    type: 'POST',
    data: JSON.stringify(data),
    contentType: 'application/json',
    url: 'http://localhost:3000/addClients',            
    success: (data) => {
      hideLoader();
      numberOfClients.text(data.fill_clients_table);
    }
   }
  );
});

const inputNumberOfContracts = $('#input-number-of-contracts');
const numberOfContracts = $('#number-of-contracts');
const addContractsBtn = $('#add-row-contracts');

addContractsBtn.on('click', () => {
  showLoader();
  const numberOfRows = Number(inputNumberOfContracts.val());
  const data = {
    numberOfRows
  };

  $.ajax({
    type: 'POST',
    data: JSON.stringify(data),
    contentType: 'application/json',
    url: 'http://localhost:3000/addContracts',            
    success: (data) => {
      hideLoader();
      numberOfContracts.text(data.fill_contracts_wo_programs_table);
    }
   }
  );
});


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
      hideLoader();
      numberOfClients.text('0');
      numberOfContracts.text('0');
    }
   }
  );
};