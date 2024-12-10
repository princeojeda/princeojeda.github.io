var slidescroll = document.getElementById("slide-scroll");
var cardcontainer = document.querySelector(".highlight-card-container");
var highlightcards = document.getElementsByClassName("highlight-card");

var startX = 0,
    startY = 0;

var moveX = 0,
    moveY = 0;

var pleaseWait = false

var centeredHighlightCard = 0;

slidescroll.addEventListener("touchstart", touchStart);
slidescroll.addEventListener("touchmove", touchMove);
slidescroll.addEventListener("touchend", touchend);
slidescroll.addEventListener("wheel", (e) => {
    if (e.shiftKey) {
        e.preventDefault()
        var delY = e.deltaY;
        var delX = e.deltaX;
        console.log(centeredHighlightCard)
        if (delY > 0) {
            scrollToRight()
        } else {
            scrollToLeft()
        }
    } else {
        console.log(e.deltaY, e.deltaX)
    }
})

function touchStart(e) {
    const firstTouch = e.touches[0];
    startX = firstTouch.clientX;
    startY = firstTouch.clientY;
}

function touchend(e) {
    // alert("KJH")
    // e.preventDefault()
    if (Math.abs(moveX) > Math.abs(moveY)) {
        e.preventDefault()
        if (moveX > 0) {
            if (!pleaseWait) {
                scrollToRight()
            }
        } else {
            if (!pleaseWait) {
                scrollToLeft()
            }
        }
    }
    // var xUp = touchMove(e).touches[0].clientX;
    // var yUp = touchMove(e).touches[0].clientY;

    // var xDiff = startX - xUp;
    // var yDiff = startY - yUp;

    // if (xDiff > 0) {
    //     if (yDiff > xDiff) {
    //         return
    //     }
    //     scrollToRight()
    // } else {
    //     // if (yDiff > xDiff) {
    //     //     return
    //     // }
    //     e.preventDefault()
    //     scrollToLeft()
    // }
}

function touchMove(e) {
    if (!startX || !startY) {
        return
    }
    var xUp = e.touches[0].clientX;
    var yUp = e.touches[0].clientY;

    var xDiff = startX - xUp;
    var yDiff = startY - yUp;

    // return xDiff, yDiff
    moveX = xDiff;
    moveY = yDiff;

}

function scrollToRight() {
    if (centeredHighlightCard === highlightcards.length) {
        return
    }
    if (!pleaseWait) {
        highlightcards[centeredHighlightCard + 1].scrollIntoView({
            behavior: "smooth",
            block: "center",
            inline: "center"
        })
        pleaseWait = true
        setTimeout(() => {
            centeredHighlightCard += 1
            pleaseWait = false
        }, 600);
    }

}
function scrollToLeft() {
    if (centeredHighlightCard === 0) {
        return
    }
    if (!pleaseWait) {
        highlightcards[centeredHighlightCard - 1].scrollIntoView({
            behavior: "smooth",
            block: "center",
            inline: "center"
        })
        pleaseWait = true
        setTimeout(() => {
            centeredHighlightCard -= 1
            pleaseWait = false
        }, 600);
    }
}


var opennav = document.getElementById("openNav"),
closenav = document.getElementById("closeNav"),
navul = document.querySelector("header nav ul");

opennav.addEventListener("click", () => {
    navul.className = "show"
})
closenav.addEventListener("click", () => {
    navul.className = "hidden"
})