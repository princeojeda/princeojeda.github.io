window.onload = () => {
    var num1 = Number(prompt("Enter the first number to add: "));
    var num2 = Number(prompt("Enter the second number to add: "));

    function add(num1, num2) {
        var sum = num1 + num2;
        return sum;
    }

    alert("The sum is: " + add(num1, num2));
}