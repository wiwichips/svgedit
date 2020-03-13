// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/someendpoint',   //The server endpoint we are connecting to
        data: {
            name1: "Value 1",
            name2: "Value 2"
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
			
            $('#blah').html("On page load, received string '"+data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            console.log('write object to screen on page load: ' + data); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error); 
        }
    });

    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
/*    $('#someform').submit(function(e){
		console.log('value in entry box = ' + $('#entryBox').val());
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/test',   //The server endpoint we are connecting to
			data: {
				name1: $('#entryBox').val(),
			},
			success: function (data) {
				console.log('write object to screen on page load: ' + data.foo); 

			},
			fail: function(error) {
				console.log(error); 
			}
		});
    });*/
	
	// set the file log table and select drop list on page load 
	$.ajax({
		type: 'get',            //Request type
		dataType: 'json',       //Data type - we will use JSON for almost everything 
		url: '/getSVGJSON',   //The server endpoint we are connecting to
		data: {
			name1: 'hen_and_chicks.svg'
		},
		success: function (data) {
			// console.log('write object to screen on page load: ' + data.foo); 
			// $('#imagePath').src = "hen_and_chicks.svg";
			
			/// add all the files into the file log
			for(let i = 0; i < data.foo.length; i++) {
			
				let imageFileName = data.foo[i].name;
			
				$('#testTable').append('<tbody>');
				$('#testTable').append('<tr>');
				$('#testTable').append('<th><img class="resize" src="' + imageFileName + '"></th>');
				$('#testTable').append('<th><a href="' + imageFileName + '">' + imageFileName + '</a></th>');
				$('#testTable').append('<th>' + data.foo[i].size + ' kb</th>');
				$('#testTable').append('<th>' + data.foo[i].numRect + '</th>');
				$('#testTable').append('<th>' + data.foo[i].numCirc + '</th>');
				$('#testTable').append('<th>' + data.foo[i].numPaths + '</th>');
				$('#testTable').append('<th>' + data.foo[i].numGroups + '</th>');
				$('#testTable').append('</tr>');
				$('#testTable').append('</tbody>');
				
			}
			
			// also add these to the svgDropDown list
			for(let i = 0; i < data.foo.length; i++) {
				
				let imageFileName = data.foo[i].name;
				
				$('#svgDropDown').append('<option>' + imageFileName + '</option>');
				
			}
			
			// if there are no files, just append NO FILES
			if(data.foo.length === 0) {
				$('#testTable').append('<p>NO FILES</p>');
			}
			
		},
		fail: function(error) {
			console.log(error); 
		}
	});
	
	$('#uploadForm').submit(function(e) {
		e.preventDefault();

		var form = document.getElementById('uploadForm');
		var formData = new FormData(form);
		
		$.ajax({
			type: "POST",
			url: '/validUpload',
			data: formData,
			contentType: false,
			processData: false,
			cache: false,
			
			beforeSend: function() {
				// 
			},
			success: function(msg) {
				console.log();
			},
			error: function() {
				// error
			}
		});
	});
	
	$('#createForm').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/createSVG',   //The server endpoint we are connecting to
			data: {
				filename: $('#fileName').val(),
				description: $('#description').val(),
				title: $('#title').val(),
			},
			success: function (data) {
				
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	let optionChosen = 'temp';
/*
	$('#viewPanelForm').submit(function(e) {
		e.preventDefault();
		optionChosen = 'rect.svg';
		
		
		// call the function that returns the informaton about the svg
		$.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/svgDetails',   //The server endpoint we are connecting to
			data: {
				filename: optionChosen,
			},
			success: function (data) {
				console.log('title = ' + data.foo.title);
				console.log('description = ' + data.foo.description);
				
				
				
				
			},
			fail: function(error) {
				
			}
		});
		  
		
		
	});
	*/
	
	$('#svgDropDown').change(function () {
		let str = "";
		$( "select option:selected" ).each(function() {
			str += $( this ).text();
		});
		
		// set option Chosen to the option the user clicked
		optionChosen = str;
console.log(optionChosen);

		// get the information about the svg from the backend
		$.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/svgDetails',   //The server endpoint we are connecting to
			data: {
				filename: optionChosen,
			},
			success: function (data) {
				htmlFormattingForViewPanel(data.foo, optionChosen);
			},
			fail: function(error) {
				
			}
		});

	}).change();
	
	$('#changeTitleForm').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/changeTitle',   //The server endpoint we are connecting to
			data: {
				newTitle: $('#titleBox').val(),
				filename: optionChosen,
			},
			success: function (data) {
				
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	$('#changeDescriptionForm').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/changeDescription',   //The server endpoint we are connecting to
			data: {
				newDescription: $('#descriptionBox').val(),
				filename: optionChosen,
			},
			success: function (data) {
				
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	$('#addCircle').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/addCircle',   //The server endpoint we are connecting to
			data: {
				cx: $('#cxBox').val(),
				cy: $('#cyBox').val(),
				r: $('#rBox').val(),
				units: $('#cunitsBox').val(),
				fill: $('#circleFillBox').val(),
				filename: optionChosen,
			},
			success: function (data) {
				
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	$('#addRectangle').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/addRectangle',   //The server endpoint we are connecting to
			data: {
				x: $('#xBox').val(),
				y: $('#yBox').val(),
				width: $('#widthBox').val(),
				height: $('#heightBox').val(),
				units: $('#unitsBox').val(),
				fill: $('#rectangleFillBox').val(),
				filename: optionChosen,
			},
			success: function (data) {
				
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	$('#scaleShape').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/scaleShape',   //The server endpoint we are connecting to
			data: {
				scaleFactor: $('#scaleFactorBox').val(),
				shapeType: $('#shapeType').val(),
				index: 0, // depricated
				fileName: optionChosen,
			},
			success: function (data) {
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	$('#chooseAttribute').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/chooseAttribute',   //The server endpoint we are connecting to
			data: {
				shapeType: $('#chooseShapeType').val(),
				shapeNumber: $('#chooseShapeNumber').val(),
				fileName: optionChosen,
			},
			success: function (data) {
				
				console.log("success");
				
				
				
				
			},
			fail: function(error) {
				
			}
		});
    });
	
	
	// adds table formatting for the svg view panel
	function htmlFormattingForViewPanel(svgObject, filename) {
		
		// dont do anything if the string is empty
		if(optionChosen === '') {
			return;
		}
		
		// kill the children to make room for the new table
		$('#SVGviewPanel').empty();
		
		// create table for image
		$('#SVGviewPanel').append('<table class="table table-fixed" border="2">');
			$('#SVGviewPanel').append('<th><img class="resize" src="' + filename + '"></th>');
		$('#SVGviewPanel').append('</table>');
		
		// create table for title and description
		$('#SVGviewPanel').append('<table class="table table-fixed" border="2">');
			$('#SVGviewPanel').append('<tr>');
				$('#SVGviewPanel').append('<th style="text-align:center">Title<th>');
				$('#SVGviewPanel').append('<th style="text-align:center">Description<th>');
			$('#SVGviewPanel').append('</tr>');
			$('#SVGviewPanel').append('<tr>');
				$('#SVGviewPanel').append('<td>' + svgObject.title + '<th>');
				$('#SVGviewPanel').append('<td>' + svgObject.description + '<th>');
			$('#SVGviewPanel').append('</tr>');
		$('#SVGviewPanel').append('</table>');
		
		// create tabe for components
		$('#SVGviewPanel').append('<table class="table table-fixed" border="2">');
			$('#SVGviewPanel').append('<tr>');
				$('#SVGviewPanel').append('<th style="text-align:center">Component</th>');
				$('#SVGviewPanel').append('<th style="text-align:center">Summary</th>');
				$('#SVGviewPanel').append('<th style="text-align:center">Other Attributes</th>');
			$('#SVGviewPanel').append('</tr>');
		$('#SVGviewPanel').append('</table>');
		
		// populate componenets table
		// circles
		for(let i = 1; i < svgObject.circles.length + 1; i++) {
			$('#SVGviewPanel').append('<tr>');
				// componenet number
				$('#SVGviewPanel').append('<td style="text-align:left">Circle ' + i + '</td>');
				
				// componenet summary
				$('#SVGviewPanel').append('<td style="text-align:center">x = ' 
				+ svgObject.circles[i - 1].cx
				+ ' y = ' + svgObject.circles[i - 1].cy 
				+ ' r = ' + svgObject.circles[i - 1].r
				+ ' units = ' + svgObject.circles[i - 1].units
				+ '</td>');
				
				// componenet other attributes
				$('#SVGviewPanel').append('<td style="text-align:right">' + svgObject.circles[i - 1].numAttr + '</td>');
			$('#SVGviewPanel').append('</tr>');
		}
		
		// rectangles
		for(let i = 1; i < svgObject.rectangles.length + 1; i++) {
			$('#SVGviewPanel').append('<tr>');
				// componenet number
				$('#SVGviewPanel').append('<td style="text-align:left">Rectangle ' + i + '</td>');
				
				// componenet summary
				$('#SVGviewPanel').append('<td style="text-align:center">x = ' 
				+ svgObject.rectangles[i - 1].x
				+ ' y = ' + svgObject.rectangles[i - 1].y 
				+ ' Width = ' + svgObject.rectangles[i - 1].w 
				+ ' Height = ' + svgObject.rectangles[i - 1].h 
				+ ' Units = ' + svgObject.rectangles[i - 1].units 
				+ '</td>');
				
				// componenet other attributes
				$('#SVGviewPanel').append('<td style="text-align:right">' + svgObject.rectangles[i - 1].numAttr + '</td>');
			$('#SVGviewPanel').append('</tr>');
		}
		
		// paths
		for(let i = 1; i < svgObject.paths.length + 1; i++) {
			$('#SVGviewPanel').append('<tr>');
				// componenet number
				$('#SVGviewPanel').append('<td style="text-align:left">Path ' + i + '</td>');
				
				// componenet summary
				$('#SVGviewPanel').append('<td style="text-align:center">x = ' 
				+ svgObject.paths[i - 1].d
				+ '</td>');
				
				// componenet other attributes
				$('#SVGviewPanel').append('<td style="text-align:right">' + svgObject.paths[i - 1].numAttr + '</td>');
				
			$('#SVGviewPanel').append('</tr>');
		}
		
		// groups
		for(let i = 1; i < svgObject.groups.length + 1; i++) {
			$('#SVGviewPanel').append('<tr>');
				
			$('#SVGviewPanel').append('</tr>');
		}
		
		return;
	}
	
	
	
	
	
	
});
