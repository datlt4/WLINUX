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

<details>
  <summary>click to expand</summary>

- Variables declared with let have Block Scope
- Variables declared with let must be Declared before use
- Variables declared with let cannot be Redeclared in the same scope
</details>

<details>
  <summary>click to expand</summary>

  Example:

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

- The for statement creates a loop with 3 optional expressions:

  ```javascript
  for (expression 1; expression 2; expression 3) {
      // code block to be executed
  }
  ```

  ```javascript
  for (let i = 0; i < 5; i++) {
    text += "The number is " + i + "<br>";
  }
  // The number is 0
  // The number is 1
  // The number is 2
  // The number is 3
  // The number is 4

  const cars = ["BMW", "Volvo", "Saab", "Ford"];
  let i, len, text;
  for (let i = 0, len = cars.length, text = ""; i < len; i++) {
      text += cars[i] + "<br>";
  }
  // BMW
  // Volvo
  // Saab
  // Ford
  ```

</details>

### The For In Loop

<details>
  <summary>click to expand</summary>

- The JavaScript `for in` statement loops through the properties of an Object:

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

<details>
  <summary>click to expand</summary>

- The JavaScript `for in` statement can also loop over the properties of an Array:

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
  // 45
  // 4
  // 9
  // 16
  // 25
  ```
</details>

### `Array.forEach()`

<details>
  <summary>click to expand</summary>

- The `forEach()` method calls a function (a callback function) once for each array element.

  ```javascript
  const numbers = [45, 4, 9, 16, 25];
  let txt = "";
  numbers.forEach(myFunction);
  function myFunction(value, index, array) {
      txt += value + "<br>"; 
  }
  ```
</details>

### The For Of Loop

<details>
  <summary>click to expand</summary>

- The JavaScript `for of` statement loops through the values of an iterable object.

  ```javascript
  const cars = ["BMW", "Volvo", "Mini"];

  let text = "";
  for (let x of cars) {
      text += x;
  }
  ```

  ```javascript
  let language = "JavaScript";
  
  let text = "";
  for (let x of language) {
      text += x;
  }
  ```
</details>

### The `While` Loop

<details>
  <summary>click to expand</summary>
  
- The `while` loop loops through a block of code as long as a specified condition is true.

  ```javascript
  while (i < 10) {
      text += "The number is " + i;
      i++;
  }
  ```
</details>

### The `Do While` Loop

<details>
  <summary>click to expand</summary>

- The `do while` loop is a variant of the while loop. This loop will execute the code block once, before checking if the condition is true, then it will repeat the loop as long as the condition is true.

  ```javascript
  do {
      text += "The number is " + i;
      i++;
  }
  while (i < 10);
  ```
</details>

# JavaScript Async

### JavaScript Promise Object

<details>
  <summary>click to expand</summary>

- `Producing code` is code that can take some time
- `Consuming code` is code that must wait for the result
- A Promise is an Object that links `Producing code` and `Consuming code`.

  ```javascript
  let myPromise = new Promise(function(myResolve, myReject) {
      // "Producing Code" (May take some time)
      myResolve(); // when successful
      myReject();  // when error
  });
  
  // "Consuming Code" (Must wait for a fulfilled Promise)
  myPromise.then(
      function(value) { /* code if successful */ },
      function(error) { /* code if some error */ }
  );
  ```

- When the producing code obtains the result, it should call one of the two callbacks:

  |When|Call|
  |---|---|
  |Success|`myResolve(result value)`|
  |Error|`myReject(error object)`|

  ```javascript
  function myDisplayer(some) {
      document.getElementById("demo").innerHTML = some;
  }
  
  let myPromise = new Promise(function(myResolve, myReject) {
      let x = 0;
    
      // The producing code (this may take some time)
      // some code (try to change x to 5)
    
      if (x == 0) {
          myResolve("OK");
      } else {
          myReject("Error");
      }
  });
  
  myPromise.then(
      function(value) {myDisplayer(value);},
      function(error) {myDisplayer(error);}
  );
  ```
</details>

### JavaScript Promise Examples - Waiting for a Timeout

<details>
  <summary>click to expand</summary>

- Example Using Callback

  ```javascript
  setTimeout(function() { myFunction("I love You !!!"); }, 3000);

  function myFunction(value) {
      document.getElementById("demo").innerHTML = value;
  }
  ```

- Example Using Promise

  ```javascript
  let myPromise = new Promise(function(myResolve, myReject) {
      setTimeout(function() { myResolve("I love You !!"); }, 3000);
  });

  myPromise.then(function(value) {
      document.getElementById("demo").innerHTML = value;
  });
  ```
</details>

### JavaScript Promise Examples - Waiting for a file

<details>
  <summary>click to expand</summary>

- Example Using Callback

  ```javascript
  function getFile(myCallback) {
      let req = new XMLHttpRequest();
      req.open('GET', "mycar.html");
      req.onload = function() {
          if (req.status == 200) {
              myCallback(req.responseText);
          } else {
              myCallback("Error: " + req.status);
          }
      }
      req.send();
  }

  getFile(myDisplayer);
  ```

- Example Using Promise

  ```javascript
  let myPromise = new Promise(function(myResolve, myReject) {
      let req = new XMLHttpRequest();
      req.open('GET', "mycar.html");
      req.onload = function() {
          if (req.status == 200) {
              myResolve(req.response);
          } else {
              myReject("File not Found");
          }
      };
      req.send();
  });

  myPromise.then(
      function(value) {myDisplayer(value);},
      function(error) {myDisplayer(error);}
  );
  ```
</details>

### Async Syntax

<details>
  <summary>click to expand</summary>

- The keyword `async` before a function makes the function return a `promise`:

  ```javascript
  async function myFunction() {
      return "Hello";
  }
  ```
  
  Is the same as:
  
  ```javascript
  async function myFunction() {
      return "Hello";
  }
  myFunction().then(
      function(value) {myDisplayer(value);},
      function(error) {myDisplayer(error);}
  );
  ```

  Or simpler, since you expect a normal value (a normal response, not an error):

  ```javascript
  async function myFunction() {
      return "Hello";
  }
  myFunction().then(
      function(value) {myDisplayer(value);}
  );
  ```
</details>

### Await Syntax

<details>
  <summary>click to expand</summary>

- The `await` keyword can only be used inside an `async` function.
- The `await` keyword makes the function pause the execution and wait for a resolved `promise` before it continues:

  ```javascript
  let value = await promise;
  ```

  Basic Syntax

  ```javascript
  async function myDisplay() {
      let myPromise = new Promise(function(resolve, reject) {
          resolve("I love You !!");
      });
      document.getElementById("demo").innerHTML = await myPromise;
  }
  myDisplay();
  ```

  Example without reject

  ```javascript
  async function myDisplay() {
      let myPromise = new Promise(function(resolve) {
          resolve("I love You !!");
      });
      document.getElementById("demo").innerHTML = await myPromise;
  }
  
  myDisplay();
  ```
</details>

### Example `async-await` - Waiting for a Timeout

<details>
  <summary>click to expand</summary>

  ```javascript
  async function myDisplay() {
      let myPromise = new Promise(function(resolve) {
          setTimeout(function() {resolve("I love You !!");}, 3000);
      });
      document.getElementById("demo").innerHTML = await myPromise;
  }
  
  myDisplay();
  ```
</details>

### Example `async-await` - Waiting for a File

<details>
  <summary>click to expand</summary>

  ```javascript
  async function getFile() {
      let myPromise = new Promise(function(resolve) {
          let req = new XMLHttpRequest();
          req.open('GET', "mycar.html");
          req.onload = function() {
              if (req.status == 200) {
                  resolve(req.response);
              } else {
                  resolve("File not Found");
              }
          };
          req.send();
      });
      document.getElementById("demo").innerHTML = await myPromise;
  }
  
  getFile();
  ```
</details>
