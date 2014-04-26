function HTTPGET(url) {
	var req = new XMLHttpRequest();
	req.open("GET", url, false);
	req.send(null);
	return req.responseText;
}


var getQuestion = function() {
	//Get question info
	var response = HTTPGET("https://raw.githubusercontent.com/chrzhang/json_fodder/master/jsontest.json");
		
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

Pebble.addEventListener("ready",
  function(e) {
	//App is ready to receive JS messages
	getQuestion();
    getAnswer();
  }
);