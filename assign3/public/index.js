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
	
	// set the file log table on page load
	//Pass data to the Ajax call, so it gets passed to the server
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
			
			// if there are no files, just append NO FILES
			$('#testTable').append('<p>NO FILES</p>');
			
		},
		fail: function(error) {
			console.log(error); 
		}
	});
	
	
	
	$('#someform').submit(function(e){
        e.preventDefault();
		
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/someendpoint',   //The server endpoint we are connecting to
			data: {
				name1: $('#entryBox').val(),
			},
			success: function (data) {
				console.log(data.boo);
				
			},
			fail: function(error) {
				console.log(error); 
			}
		});
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
	
	$('#viewPanelForm').submit(function(e) {
		e.preventDefault();
		let optionChosen = 'rect.svg';
		
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
	
});