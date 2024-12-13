var slidescroll = document.getElementById("slide-scroll");
var cardcontainer = document.querySelector(".highlight-card-container");
var highlightcards = document.getElementsByClassName("highlight-card");

var startX = 0,
    startY = 0;

var moveX = 0,
    moveY = 0;

var pleaseWait = false

var centeredHighlightCard = 0;

try {
    slidescroll.addEventListener("touchstart", touchStart);
    slidescroll.addEventListener("touchmove", touchMove);
    slidescroll.addEventListener("touchend", touchend);
    slidescroll.addEventListener("wheel", (e) => {
        if (e.shiftKey) {
            e.preventDefault()
            var delY = e.deltaY;
            var delX = e.deltaX;
            if (delY > 0) {
                if (!pleaseWait) {
                    if (centeredHighlightCard == highlightcards.length - 1) {
                        return
                    }
                    if (scrollTo(highlightcards[centeredHighlightCard + 1])) {
                        centeredHighlightCard += 1
                    }
                }
            } else {
                if (!pleaseWait) {
                    if (centeredHighlightCard == 0) {
                        return
                    }
                    if (scrollTo(highlightcards[centeredHighlightCard - 1])) {
                        centeredHighlightCard -= 1
                    }
                }
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
        if (Math.abs(moveX) > Math.abs(moveY)) {
            if (moveX > 0) {
                if (!pleaseWait) {
                    if (centeredHighlightCard == highlightcards.length - 1) {
                        return
                    }
                    if (scrollTo(highlightcards[centeredHighlightCard + 1])) {
                        centeredHighlightCard += 1
                    }
                }
            } else {
                if (!pleaseWait) {
                    if (centeredHighlightCard == 0) {
                        return
                    }
                    if (scrollTo(highlightcards[centeredHighlightCard - 1])) {
                        centeredHighlightCard -= 1
                    }
                }
            }
        } else {

        }
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
        if (Math.abs(moveX) < Math.abs(moveY)) {

        } else {
            e.preventDefault()
        }
    }
} catch (error) {
    console.log(error)
}


async function scrollTo(element) {
    // if (centeredHighlightCard === 0) {
    //     return false
    // }
    // if (!pleaseWait) {
    element.scrollIntoView({
        behavior: "smooth",
        block: "center",
        inline: "center"
    })
    pleaseWait = true
    setTimeout(() => {
        pleaseWait = false
        return true
    }, 600);
    // } else {
    //     return false
    // }
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

var educationCarousel = document.querySelector(".education-carousel"),
    educationCarouselCard = document.querySelectorAll(".education-carousel-card"),
    dotIndicator = document.querySelectorAll(".dot-indicator"),
    educationLeftBTN = document.getElementById("educationLeftBTN"),
    educationRightBTN = document.getElementById("educationRightBTN"),
    educationIndicator = document.getElementsByClassName("indicator-container")[0];

try {
    educationIndicator.addEventListener("touchmove", (e) => {
        e.preventDefault()
    })
    educationIndicator.addEventListener("wheel", (e) => {
        if (e.shiftKey) {
            e.preventDefault()
        }
    })
    educationCarousel.addEventListener("touchstart", (e) => {
        const firstTouch = e.touches[0];
        startX = firstTouch.clientX;
        startY = firstTouch.clientY;
    })
    educationCarousel.addEventListener("touchmove", (e) => {
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
        if (Math.abs(moveX) < Math.abs(moveY)) {
        } else {
            e.preventDefault()
        }
    })
    educationCarousel.addEventListener("wheel", (e) => {
        if (e.shiftKey) {
            e.preventDefault()
            var delY = e.deltaY;
            var delX = e.deltaX;
            if (delY > 0) {
                if (!pleaseWait) {
                    if (centeredHighlightCard == educationCarouselCard.length - 1) {
                        return
                    }
                    scrollTo(dotIndicator[centeredHighlightCard + 1])
                    if (scrollTo(educationCarouselCard[centeredHighlightCard + 1])) {
                        centeredHighlightCard += 1
                    }
                }
            } else {
                if (!pleaseWait) {
                    if (centeredHighlightCard == 0) {
                        return
                    }
                    scrollTo(dotIndicator[centeredHighlightCard - 1])
                    if (scrollTo(educationCarouselCard[centeredHighlightCard - 1])) {
                        centeredHighlightCard -= 1
                    }
                }
            }
        } else {
            console.log(e.deltaY, e.deltaX)
        }
    })


    educationLeftBTN.addEventListener("click", () => {
        if (!pleaseWait) {
            if (centeredHighlightCard == 0) {
                return
            }
            scrollTo(dotIndicator[centeredHighlightCard - 1])
            if (scrollTo(educationCarouselCard[centeredHighlightCard - 1])) {
                centeredHighlightCard -= 1
            }
        }
    })
    educationRightBTN.addEventListener("click", () => {
        if (!pleaseWait) {
            if (centeredHighlightCard == educationCarouselCard.length - 1) {
                return
            }
            scrollTo(dotIndicator[centeredHighlightCard + 1])
            if (scrollTo(educationCarouselCard[centeredHighlightCard + 1])) {
                centeredHighlightCard += 1
            }
        }
    })
} catch (error) {

}

const galleryMe = document.querySelector(".galleryMe"),
galleryFamily = document.querySelector(".galleryFamily"),
galleryFriends = document.querySelector(".galleryFriends"),
galleryHobbies = document.querySelector(".galleryHobbies"),
galleryClose = document.querySelector(".galleryClose");

const galleryContainer = document.querySelector(".gallery-container");

function closeGallery () {
    console.log("Close")
    galleryContainer.classList.remove("show")
    galleryMe.classList.add("hidden")
    galleryFamily.classList.add("hidden")
    galleryFriends.classList.add("hidden")
    galleryHobbies.classList.add("hidden")
}
function openMe() {
    galleryContainer.classList.add("show")
    galleryMe.classList.remove("hidden")
}

function openFamily() {
    galleryContainer.classList.add("show")
    galleryFamily.classList.remove("hidden")
}

function openFriends() {
    galleryContainer.classList.add("show")
    galleryFriends.classList.remove("hidden")
}

function openHobbies() {
    galleryContainer.classList.add("show")
    galleryHobbies.classList.remove("hidden")
}