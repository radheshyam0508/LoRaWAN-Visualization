$(document).on('scroll', function() {
    if ($(document).scrollTop() > 0) {
        $('.nav').addClass('nav--shrink');
    } else {
        $('.nav').removeClass('nav--shrink');
    }
});


$('.btn').on('click', function(e) {
    runStack();
});
$(document).ready(runStack());

function runStack() {
    if ($('.btn').hasClass('active')) {
        unstack();
    } else {
        stack()
    }
    $('.btn').toggleClass('active');
}

function stack() {
    var boxes = $('.paper');
    $.each(boxes, function(i, v) {
        var self = this;
        setTimeout(function() {
            $(self).addClass('stacked');
        }, i * 300);
    });
    setTimeout(function() {
        $('.btn').text('Floor plan');
    }, 900);
}

function unstack() {
    var boxes = $('.paper').get().reverse();
    $.each(boxes, function(i, v) {
        var self = this;
        setTimeout(function() {
            $(self).removeClass('stacked');
        }, i * 300);
    });
    setTimeout(function() {
        $('.btn').text('View');
    }, 900);
}
