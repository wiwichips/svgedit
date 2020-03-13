'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {	
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
 
  let uploadFile = req.files.uploadFile;
 
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 


/// functions from shared library to use
let libsvgparse = ffi.Library('parser/libsvgparse', {
	// test functions
	'floatToString': [ 'string', [ 'float' ] ],
	'printHelloWorld': [ 'string', [ 'int' ] ],
	'JSONcreateValidSVG': ['string', ['string', 'string']],
	'validateSVGfile': ['int', ['string', 'string']],
	'createNewSVGimageAndWriteToFile': ['int', ['string', 'string', 'string', 'string']],
	'circleToJSONfromValidFile': ['string', ['string', 'string']],
	'rectToJSONfromValidFile': ['string', ['string', 'string']],
	'pathToJSONfromValidFile': ['string', ['string', 'string']],
	'groupToJSONfromValidFile': ['string', ['string', 'string']],
	'getTitle': ['string', ['string', 'string']],
	'getDescription': ['string', ['string', 'string']],
	'changeTitleFromFile': ['void', ['string', 'string', 'string']],
	'changeDescriptionFromFile': ['void', ['string', 'string', 'string']],
	'addCircleFromFile': ['int', ['string', 'string', 'float', 'float', 'float', 'string', 'string']],
	'addRectangleFromFile': ['int', ['string', 'string', 'float', 'float', 'float', 'float', 'string', 'string']],
	'scaleShapeFromFile': ['int', ['string', 'string', 'float', 'string']],
	'updateAttributeFromFile': ['int', ['string', 'string', 'string', 'int', 'string', 'string']],
	'returnInformationAboutShape': ['string', ['string', 'string', 'string', 'int']],
});

/// end points

// getSVGJSON - returns an array of SVG objects with a filename 
app.get('/getSVGJSON', function(req , res){
	// create array
	let img = [];
	let totalFiles = 0;
	let fileNames = fs.readdirSync('uploads'); // get files

	// loop through each file
	for(let i = 0; i < fileNames.length; i++) {
		img.push(JSON.parse(libsvgparse.JSONcreateValidSVG('uploads/'+ fileNames[i] +'', 'parser/svg.xsd')));
		img[i].name = fileNames[i];
		img[i].size = Math.round((fs.statSync('uploads/' + fileNames[i])["size"]) / 1000);
	}
	
	// send the thing
	res.send({
		foo: img
	});
});


// validUpload - same as /upload except it checks if the svg passed is valid and deletes invalid svgs
app.post('/validUpload', function(req, res) {

	console.log('upload called on ' + req);

	if(!req.files) {
		return res.status(400).send('No files were uploaded.');
	}

	let uploadFile = req.files.uploadFile;

	// Use the mv() method to place the file somewhere on your server
	uploadFile.mv('uploads/' + uploadFile.name, function(err) {
	if(err) {
		return res.status(500).send(err);
	}
	
	// check if the file is valid
	if(libsvgparse.validateSVGfile('uploads/' + uploadFile.name,'parser/svg.xsd') == 0) {
		// if the file is invalid, delete it
		fs.unlinkSync('uploads/' + uploadFile.name)
		// console.log('deleted ' + uploadFile.name);
	}

	res.redirect('/');
	});
});

// createSVG - creates an svg from the client
app.get('/createSVG', function(req, res) {
	
	// console.log('filename = ' + req.query.filename);
	// console.log('title = ' + req.query.title);
	// console.log('description = ' + req.query.description);
	
	// create svgImage with filename titlt description and write to file
	console.log('createSVG = ' + libsvgparse.createNewSVGimageAndWriteToFile('parser/svg.xsd', 'uploads/' + req.query.filename, req.query.title, req.query.description));

	res.send({
		foo: 'worked'
	});
});

// svgDetails - returns all details for an SVG needed by View SVG
app.get('/svgDetails', function(req, res) {
	
	console.log(req.query.filename);
	if(req.query.filename === '') {
		
	}
		
	
	var details = new Object();
	
	// get title and description
	details.description = libsvgparse.getDescription('uploads/'+ req.query.filename +'', 'parser/svg.xsd');
	details.title = libsvgparse.getTitle('uploads/'+ req.query.filename +'', 'parser/svg.xsd');
	
	// get the lists of shapes
	details.circles = JSON.parse(libsvgparse.circleToJSONfromValidFile('uploads/'+ req.query.filename +'', 'parser/svg.xsd'));
	details.rectangles = JSON.parse(libsvgparse.rectToJSONfromValidFile('uploads/'+ req.query.filename +'', 'parser/svg.xsd'));
	details.paths = JSON.parse(libsvgparse.pathToJSONfromValidFile('uploads/'+ req.query.filename +'', 'parser/svg.xsd'));
	details.groups = JSON.parse(libsvgparse.groupToJSONfromValidFile('uploads/'+ req.query.filename +'', 'parser/svg.xsd'));
	
	res.send({
		foo: details
	});
});

// changeTitle - changes the title of a specified image. Does not copy if exceeds 255
app.get('/changeTitle', function(req , res){
	console.log(req.query.newTitle);
	
	libsvgparse.changeTitleFromFile('uploads/'+ req.query.filename +'', 'parser/svg.xsd', req.query.newTitle);

	res.send({
		foo: req.query.newTitle
	});
});

// changeDescription - changes the description of a specified image. Does not copy if exceeds 255
app.get('/changeDescription', function(req , res){
	console.log(req.query.newDescription);
	
	libsvgparse.changeDescriptionFromFile('uploads/'+ req.query.filename +'', 'parser/svg.xsd', req.query.newDescription);

	res.send({
		foo: req.query.newDescription
	});
});

// addCircle - adds a circle to an image
app.get('/addCircle', function(req , res){	
	libsvgparse.addCircleFromFile('uploads/'+ req.query.filename, 'parser/svg.xsd', req.query.cx, req.query.cy, req.query.r, req.query.units, req.query.fill);

	res.send({
		foo: 'worked'
	});
});

// addRectangle - changes the description of a specified image. Does not copy if exceeds 255
app.get('/addRectangle', function(req , res){	

	libsvgparse.addRectangleFromFile('uploads/'+ req.query.filename, 'parser/svg.xsd', req.query.x, req.query.y, req.query.width, req.query.height, req.query.units, req.query.fill);

	res.send({
		foo: 'worked'
	});
});

// scaleShape - scales a shape in an image by a scaleFactor
app.get('/scaleShape', function(req , res){

	console.log(req.query.scaleFactor);
	console.log(req.query.shapeType);
	console.log(req.query.index);
	
	// bool scaleShapeFromFile(char* fileName, char* schemaFile, float scaleFactor, int index, char* shapeType) {

	libsvgparse.scaleShapeFromFile('uploads/'+ req.query.fileName, 'parser/svg.xsd', req.query.scaleFactor, req.query.shapeType);

	res.send({
		foo: 'worked'
	});
});

// chooseAttribute - chooses a shape to display information for
app.get('/chooseAttribute', function(req , res){

	let erin = new Object();
	
	// console.log("shooting star: --->" + libsvgparse.returnInformationAboutShape('uploads/'+ req.query.fileName, 'parser/svg.xsd', req.query.shapeType, req.query.shapeNumber - 1));
	
	if(libsvgparse.returnInformationAboutShape('uploads/'+ req.query.fileName, 'parser/svg.xsd', req.query.shapeType, req.query.shapeNumber - 1) != "bad" && libsvgparse.returnInformationAboutShape('uploads/'+ req.query.fileName, 'parser/svg.xsd', req.query.shapeType, req.query.shapeNumber - 1) != "[]") {
		erin.otherAttributes = JSON.parse(libsvgparse.returnInformationAboutShape('uploads/'+ req.query.fileName, 'parser/svg.xsd', req.query.shapeType, req.query.shapeNumber - 1));
		
		// remember to add other details
		
		erin.bad = false;
	}
	
	else {
		erin.bad = true;
	}

	res.send({
		foo: erin
	});
});

// changeAttribute - chnages an attribute for a shape
app.get('/changeAttribute', function(req , res){
	
	// call function in c
	let yes = libsvgparse.updateAttributeFromFile('uploads/'+ req.query.fileName, 'parser/svg.xsd', req.query.shapeType, req.query.shapeNumber - 1, req.query.name, req.query.value);
	
	console.log('yes = ' + yes);
	
	res.send({
		foo: 'worked'
	});
});




/// test endpoints
// test end point
app.get('/get', function(req , res){
	console.log(req.query.name1 + '   ' + testString);
	
	let retStr = req.query.name1 + " " + testString;
	testString = req.query.name1
	res.send({
		foo: retStr
	});
});


let holder = 'hello';
//Sample endpoint
app.get('/someendpoint', function(req , res){
  let retStr = req.query.name1 + " " + holder;
  
  console.log(req.query.name1 + '   ' + holder);
  
  holder = req.query.name1;
  
  res.send({
    boo: retStr
  });
});


app.listen(portNum);
console.log('Running app at localhost: ' + portNum + '!!');