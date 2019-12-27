$(document).on('scroll', function() {
    if ($(document).scrollTop() > 0) {
        $('.nav').addClass('nav--shrink');
    } else {
        $('.nav').removeClass('nav--shrink');
    }
});

var dataset = [-64,23];

var rssi;
var temperature;

function callServer() {
    var xmlHttp = new XMLHttpRequest()
    xmlHttp.onreadystatechange = function() {

         if (this.readyState == 4 && this.status == 200) {

           var jsonResponse = JSON.parse(this.responseText);

           dataset[0] = jsonResponse["rssi"];
           dataset[1] = jsonResponse["temperature"];
           console.log(dataset);
         }
    };
    xmlHttp.open("GET", "http://localhost:5000/data", true);
    xmlHttp.send( null );

}

setInterval(function(){
  callServer();
}, 10000);





//for 2nd:

  var l2 = d3.select('#l2')
  .attr("width", 960) //减是变窄了
  .attr("height", 500);

  //tooltip+circle
  l2.selectAll("circle")
     .data(dataset)
     .enter()
     .append("circle")
     .attr("cx", 140)
     .attr("cy", 400)
     .attr("r",8)
     .attr("fill", "#FF6347")
     .attr("fill-opacity", 0.7)
     .attr("stroke", "#FFB6C1")
     .attr("stroke-width", 12)
     .attr("stroke-opacity", 0.5)
     .on("click", openNav)
     .on("mouseover", function(d){
       d3.select(this).style("cursor", "pointer");
       tooltip.html("Status: Active" +"<br/>"+"Rssi: " + dataset[0] + "<br/>" + 'Temperature: '+ dataset[1]+ " °C")
       .style("left", d3.event.pageX - 70 + "px")
   .style("top", d3.event.pageY - 90 + "px")
   .style("opacity", 0.8)
   d3.select(this).transition()
         .duration(150)
  })
  .on("mouseout", function(){
  d3.select(this).transition()
           .duration(150)
  tooltip.style("opacity", 0)
  });


  var tooltip = d3.select("body")
                    .append("div")
                    .attr("class", "tooltip")
                    .style("opacity", 0)



/*navigation*/

  function openNav() {
    document.getElementById("mySidenav").style.width = "550px";
    document.getElementById("main").style.marginRight = "550px";
    document.body.style.backgroundColor = "rgba(0,0,0,0.4)";
}

function closeNav() {
    document.getElementById("mySidenav").style.width = "0";
    document.getElementById("main").style.marginRight= "0";
    document.body.style.backgroundColor = "white";
}

/*chart js*/
var testValueCount=10;
  function NewValue(){
       testValueCount++;
 // console.log(testValueCount);
        if(testValueCount==25 || testValueCount==28){
		    return 20;
		}

		if(testValueCount==100){
		  return 15;
		}
        if(Math.random() > .5){
            return Math.round(Math.random()*20);
        } else {
            return (Math.random()*20).toFixed(1);
        }



    }


	var el=d3.select("#use1");
	var min=el.attr("minvalue");
	var max=el.attr("maxvalue");
	var samprate=el.attr("samprate");
	var dataCount=el.attr("datacounts");



    var uadatas=[];
	var ubdatas=[];
	var uadatas2=[];
	var ubdatas2=[];

	var uadatas3=[];
	var ubdatas3=[];

	 var t=new Date();
    var timenow=t.getTime();

	var timeStart=timenow;

    uadatas.push([timeStart,22]);
    ubdatas.push([timeStart,20]);
	uadatas2.push([timeStart,160]);
    ubdatas2.push([timeStart,300]);
	uadatas3.push([timeStart,20]);
    ubdatas3.push([timeStart,80]);

	var lineInitdataset = [

	  {name:"UA",
	  alldatas:uadatas
	 }
    ];


	function addData(timeminInLine,dataCountInLine,timeStepInLine,updateData,useId){
	      var t = new Date();

		  var timenowToAdd = timeminInLine+dataCountInLine*timeStepInLine;

		 if(useId=="use1"){
		      for (var i = 0; i < updateData.length; i++) {
			  updateData[i].alldatas.push([timenowToAdd, NewValue()]);
		   }
		 }

		 if(useId=="use2"){
		   for (var i = 0; i < updateData.length; i++) {
			  updateData[i].alldatas.push([timenowToAdd, NewValue1()]);
		   }
		 }

		  if(useId=="use3"){
		   for (var i = 0; i < updateData.length; i++) {
			  updateData[i].alldatas.push([timenowToAdd, NewValue2()]);
		   }
		 }


		   return updateData;
	}

	function deleteData(updateData,useId){
	      for (var i = 0; i < updateData.length; i++) {
			       updateData[i].alldatas.shift();
	       }
		  return updateData;
	}


	var objLine=new LoadLineChart("realTimeLine_2",lineInitdataset,min,max,samprate,dataCount,"use1");
	objLine.updateLineChart();

	//var objLine2=new LoadLineChart("realTimeLine_3",lineInitdataset2,min2,max2,samprate2,dataCount2,"use2");
	//objLine2.updateLineChart();

	//var objLine3=new LoadLineChart("realTimeLine_4",lineInitdataset3,min3,max3,samprate3,dataCount3,"use3");
	//objLine3.updateLineChart();
