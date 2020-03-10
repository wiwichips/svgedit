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

/*
let libm = ffi.Library('libm', {
  'ceil': [ 'double', [ 'double' ] ]
});
console.log(libm.ceil(1.5)); // 2
 
// You can also access just functions in the current process by passing a null
let current = ffi.Library(null, {
  'atoi': [ 'int', [ 'string' ] ]
});
console.log(current.atoi('1234')); // 1234
*/

// functions from shared library to use
let libsvgparse = ffi.Library('parser/libsvgparse', {
	// test functions
	'floatToString': [ 'string', [ 'float' ] ],
	'printHelloWorld': [ 'string', [ 'int' ] ],
	'createValidSVGimage': ['Object', ['string', 'string']],
	// 
});



console.log(libsvgparse.floatToString(33.3));
console.log(libsvgparse.printHelloWorld(1));

console.log(libsvgparse.createValidSVGimage('uploads/rects.svg', 'parser/svg.xsd').description);



// simple example endpoint where server stores information
let testString = '';
app.get('/test', function(req , res){
	console.log(req.query.name1 + '   ' + testString);
	
	let retStr = req.query.name1 + " " + testString;
	testString = req.query.name1
	res.send({
		foo: retStr
	});
});


//Sample endpoint
app.get('/someendpoint', function(req , res){
  let retStr = req.query.name1 + " " + req.query.name2;
  
  console.log(req.query.name1 + '   ' + req.query.name2);
  
  res.send({
    foo: retStr
  });
});

app.listen(portNum);
console.log('Running app at localhost: ' + portNum + '!!');