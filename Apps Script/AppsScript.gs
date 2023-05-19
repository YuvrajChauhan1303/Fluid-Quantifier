var ss = SpreadsheetApp.openById('your spreadsheets s\Script ID '); //Add Script Id

//Full Link: https://docs.google.com/spreadsheets/d/1DWYqfMzsWD5lPN-lNAc3c4Sbrrthnf6OT7AmEAp_csTeyXDA/edit#gid=0
//Script ID : 1DWYqfMzsWD5lPN-lNAc3c4Snf6OT7AmEAp_csTeyXfgDA
//Hint: After '/d/' and before /edit#gid=0

var sheet = ss.getSheetByName('Sheet1'); // Add Sheet Name
var timezone = "Mumbai" 
var final_time = 5*60 + 30;

function doGet(e){
  Logger.log( JSON.stringify(e) );
  if (e.parameter == 'undefined') {
    return ContentService.createTextOutput("Received data is undefined");
  }
  var Curr_Date =new Date(new Date().setMinutes(new Date().getMinutes() + final_time));
  var Curr_Time     = Utilities.formatDate(Curr_Date, timezone, 'HH:mm:ss');
  var student_id    = stripQuotes(e.parameters.data1);
  var first_name    = stripQuotes(e.parameters.data2);
  var last_name     = stripQuotes(e.parameters.data3);
  var curent_session = stripQuotes(e.parameter.data4);
  //Add functions if you want more sections on this projectin this spreadsheet 
  var nextRow = sheet.getLastRow() + 1;
  sheet.getRange("A" + nextRow).setValue(Curr_Date);
  sheet.getRange("B" + nextRow).setValue(Curr_Time);
  sheet.getRange("C" + nextRow).setValue(student_id);
  sheet.getRange("D" + nextRow).setValue(first_name);
  sheet.getRange("E" + nextRow).setValue(last_name);
  sheet.getRange("F" + nextRow).setValue(curent_session) //DO NOT ADD SEMI COLON
  //Add more Sections using above syntax, but DO NOT ADD SEMI COLON to the last statement.
  return ContentService.createTextOutput("Data is stored in Google Sheet.");
  
}

function stripQuotes( value ) {
  return value.toString().replace(/^["']|['"]$/g, "");
}
}
