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
  var response = HTTPGET(url_array[payload_value]);
		
	//Convert to JSON
	var json = JSON.parse(response);
	
	var questionname = json[4].name;
  var questiondes = json[4].desc;
    
	//Console output to check all is working.
	//console.log("It is " + temperature + " degrees in " + location + " today!");

                   
	//Construct a key-value dictionary	
	var dict = {"KEY_QNAME" : questionname, "KEY_QDESCRIPTION": questiondes};
	
	//Send data to watch for display
	Pebble.sendAppMessage(dict);
};

var getAnswer = function() {
	//Get answer info
	var response = HTTPGET("https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");
		
	//Convert to JSON
	var json = JSON.parse(response);
	
	var correctA = json[4].Answer1;
  var wrongBCD = [json[4].Answer2, '/', json[4].Answer3, '/', json[4].Answer4];
                   
	//Construct a key-value dictionary	
	var dict = {"KEY_CANSA" : correctA, "KEY_WANS": wrongBCD};
	
	//Send data to watch for display
	Pebble.sendAppMessage(dict);
};

Pebble.addEventListener("appmessage",
        function(e) {
                console.log("digger");
                 for(var key in e.payload){
                         console.log(key);
                         console.log(e.payload[key]);
                          payload_value = e.payload[key];
                          }
                           getQuestion();
                           getAnswer();
  });