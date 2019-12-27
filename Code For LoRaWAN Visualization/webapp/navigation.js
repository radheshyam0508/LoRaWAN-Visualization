$(document).on('scroll', function() {
    if ($(document).scrollTop() > 0) {
        $('.nav').addClass('nav--shrink');
    } else {
        $('.nav').removeClass('nav--shrink');
    }
});

dataset=[22,11];

var mark = d3.select('#mark')
.attr("width", 1200) //减是变窄了
.attr("height", 1500);

//tooltip+circle
mark.selectAll("circle")
   .data(dataset)
   .enter()
   .append("circle")
   .attr("cx", 680)
   .attr("cy", 1090)
   .attr("r",13)
   .attr("fill", "red")
   .attr("fill-opacity", 0.5)
   .attr("stroke", "#FF5733")
   .attr("stroke-width", 32)
   .attr("stroke-opacity", 0.3)
   .on("mouseover", function(d){
     tooltip1.html("<a href='main.html'>Click to check!</a>")
     .style("left", d3.event.pageX - 80 + "px")
 .style("top", d3.event.pageY - 80 + "px")
 .style("opacity", 0.8)
 d3.select(this).transition()
       .duration(150)
});

/*.on("mouseout", function(){
d3.select(this).transition()
         .duration(150)
tooltip.style("opacity", 0)
});*/


    var tooltip1 = d3.select("body")
                      .append("div")
                      .attr("class", "tooltip1")
                      .style("opacity", 0)
