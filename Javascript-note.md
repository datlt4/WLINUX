# JavaScript Variables

### JavaScript Variables can be declared in 4 ways

<details>
  <summary>click to expand</summary>

- Automatically
- Using var
- Using let
- Using const
</details>

### When to Use var, let, or const?

<details>
  <summary>click to expand</summary>

- Always declare variables
- Always use const if the value should not be changed
- Always use const if the type should not be changed (Arrays and Objects)
- Only use let if you can't use const
- Only use var if you MUST support old browsers.
</details>

### Javascript Let

- Variables declared with let have Block Scope
- Variables declared with let must be Declared before use
- Variables declared with let cannot be Redeclared in the same scope

Example:

<details>
  <summary>click to expand</summary>

  ```javascript
  {
    let x = 2;
  }
  // x can NOT be used here
  ```

  ```javascript
  {
    var x = 2;
  }
  // x CAN be used here
  ```

  ```javascript
  // You can not accidentally redeclare a variable declared with let.
  let x = "John Doe";
  let x = 0; // [X]
  ```

  ```javascript
  // Variables defined with var can be redeclared.
  var x = "John Doe";
  var x = 0; // [V]
  ```
</details>

### JavaScript Const

<details>
  <summary>click to expand</summary>

- Variables defined with const cannot be Redeclared
- Variables defined with const cannot be Reassigned
- Variables defined with const have Block Scope
</details>

# Javascript Loop

### JavaScript supports different kinds of loops

<details>
  <summary>click to expand</summary>

- `for` - loops through a block of code a number of times
- `for/in` - loops through the properties of an object
- `for/of` - loops through the values of an iterable object
- `while` - loops through a block of code while a specified condition is true
- `do/while` - also loops through a block of code while a specified condition is true

</details>

### The For Loop

<details>
  <summary>click to expand</summary>

The for statement creates a loop with 3 optional expressions:

  ```javascript
  for (expression 1; expression 2; expression 3) {
    // code block to be executed
  }
  ```

  ```javascript
  for (let i = 0; i < 5; i++) {
    text += "The number is " + i + "<br>";
  }
  //The number is 0
  //The number is 1
  //The number is 2
  //The number is 3
  //The number is 4

  const cars = ["BMW", "Volvo", "Saab", "Ford"];
  let i, len, text;
  for (let i = 0, len = cars.length, text = ""; i < len; i++) {
    text += cars[i] + "<br>";
  }
  //BMW
  //Volvo
  //Saab
  //Ford
  ```

</details>

### The For In Loop

The JavaScript `for in` statement loops through the properties of an Object:

<details>
  <summary>click to expand</summary>

  ```javascript
  for (key in object) {
    // code block to be executed
  }
  ```

  ```javascript
  const person = {fname:"John", lname:"Doe", age:25};
  
  let text = "";
  for (let x in person) {
    text += person[x] + " ";
  }
  //John Doe 25
  ```
</details>

The JavaScript `for in` statement can also loop over the properties of an Array:

<details>
  <summary>click to expand</summary>

  ```javascript
  for (variable in array) {
    // code block to be executed
  }
  ```

  ```javascript
  const numbers = [45, 4, 9, 16, 25];
  let txt = "";
  for (let x in numbers) {
    txt += numbers[x] + "<br>"; 
  }
  //45
  //4
  //9
  //16
  //25
  ```
</details>

### `Array.forEach()`

The `forEach()` method calls a function (a callback function) once for each array element.

<details>
  <summary>click to expand</summary>

  ```javascript
  const numbers = [45, 4, 9, 16, 25];
  let txt = "";
  numbers.forEach(myFunction);
  function myFunction(value, index, array) {
    txt += value + "<br>"; 
  }
  ```
</details>

The For Of Loop
The JavaScript for of statement loops through the values of an iterable object.
