/*
var sendStruct = function()
{
		//Get question info
	var response = HTTPGET("https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");	
	//Convert to JSON
	var json = JSON.parse(response);

	var questionarr = [];
	var temp; 
	//Construct a key-value dictionary
	var qs = [];
	var questionname = "";// = json[4].name;
  var questiondesc = "";// = json[4].desc;
	var dict = {};// = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondes};
	var count = 0;
	
	json.forEach(function(entry)
								{
									questionname = entry.name;
									questiondesc = entry.desc;
									dict = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondesc};
									qs[count] = (dict);
									temp = new ques(questionname, questiondesc, "", "");
									questionarr[count] = temp;
									count++;
								});
                   
	response = HTTPGET("https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");
	json = JSON.parse(response);
	var correctA = "";// = json[4].name;
  var wrongBCD = "";// = json[4].desc;
	count = 0;
	json.forEach(function(entry)
								{
									correctA = entry.Answer1;
									wrongBCD = [entry.Answer2, '/', entry.Answer3, '/', entry.Answer4];
									dict = {"KEY_CANSA" : correctA, "KEY_WANS": wrongBCD};
									qs[count] = (dict);
									questionarr[count].correct = correctA;
									questionarr[count].wrong = wrongBCD;
									count++;
								});


	
	//Send data to watch for display	
	//Pebble.sendAppMessage(questionarr);

	Pebble.sendAppMessage(questionarr);
};

var getQuestion = function() {
	//Get question info
	var response = HTTPGET("https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");
		
	//Convert to JSON
	var json = JSON.parse(response);
	
	//Construct a key-value dictionary
	var qs = [];
	var questionname = "";// = json[4].name;
  var questiondesc = "";// = json[4].desc;
	var dict = {};// = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondes};
	var count = 0;
	
	json.forEach(function(entry)
								{
									questionname = entry.name;
									questiondesc = entry.desc;
									dict = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondesc};
									qs[count] = (dict);
									count++;
									console.log(entry.id);
									Pebble.sendAppMessage(dict); // handlers needed
								});
                   
	
	//Send data to watch for display
	//Pebble.sendAppMessage(qs);
//	Pebble.sendAppMessage(dict);

};

var getAnswer = function() {
	//Get answer info
	var response = HTTPGET("https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");
		
	//Convert to JSON
	var json = JSON.parse(response);
	
	//Construct a key-value dictionary
	var qs = [];
	var correctA = "";// = json[4].name;
  var wrongBCD = "";// = json[4].desc;
	var dict = {};// = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondes};
	var count = 0;
	
	json.forEach(function(entry)
								{
									correctA = entry.Answer1;
									wrongBCD = [entry.Answer2, '/', entry.Answer3, '/', entry.Answer4];
									dict = {"KEY_CANSA" : correctA, "KEY_WANS": wrongBCD};
									qs[count] = (dict);
									count++;
								});
	
	//Send data to watch for display
	Pebble.sendAppMessage(qs);
};

Pebble.addEventListener("ready",
  function(e) {
	//App is ready to receive JS messages
		getQuestion();
    getAnswer();
		//sendStruct();
  }
);

*/



var url_array = new Array("https://raw.githubusercontent.com/chrzhang/json_fodder/master/capitalsnew.json",
                           "https://raw.githubusercontent.com/chrzhang/json_fodder/master/celebritiesnew.json",
                           "https://raw.githubusercontent.com/chrzhang/json_fodder/master/baseballnew.json");
var payload_value = 0;
function HTTPGET(url) {
	var req = new XMLHttpRequest();
	req.open("GET", url, false);
	req.send(null);
	return req.responseText;
}


var getQuestion = function() {
	//Get question info
    var response = HTTPGET(url_array[payload_value]);
    //"https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");
		console.log("payload value",payload_value);
	//Convert to JSON
	var json = JSON.parse(response);
	
	var questionname = json[4].name;
    var questiondes = json[4].desc;
    console.log(questionname);
    console.log(questiondes);
	//Console output to check all is working.
	//console.log("It is " + temperature + " degrees in " + location + " today!");

                   
	//Construct a key-value dictionary	
	var dict = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondes};
	
	//Send data to watch for display
	Pebble.sendAppMessage(dict);
};

var getAnswer = function() {
	//Get answer info
	var response = HTTPGET(url_array[payload_value]);
		
	//Convert to JSON
	var json = JSON.parse(response);
	
	var correctA = json[4].Answer1;
    var wrongBCD = [json[4].Answer2, '/', json[4].Answer3, '/', json[4].Answer4];
                   
	//Construct a key-value dictionary	
	var dict = {"KEY_CANSA" : correctA, "KEY_WANS": wrongBCD};
	
	//Send data to watch for display
	Pebble.sendAppMessage(dict);
};
/*
Pebble.addEventListener("ready",
  function(e) {
	//App is ready to receive JS messages
	getQuestion();
    getAnswer();
  }
);*/

Pebble.addEventListener("ready",//"appmessage",
                         function(e) {
                             console.log("digger");
                             for(var key in e.payload){
                                 console.log(key);
                                 console.log(e.payload[key]);
                                 payload_value = e.payload[key];
                             }
                            //console.log((e.payload);
                             console.log(JSON.stringify(e.payload));
                             //App is ready to receive JS messages
	getQuestion();
    getAnswer();
                        });
