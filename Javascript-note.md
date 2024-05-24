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

### Promise - ChatGPT's Lecture

1. **About**

<details>
  <summary>click to expand</summary>

   - Promises in JavaScript are objects representing the eventual completion or failure of an asynchronous operation. They are used to handle asynchronous operations such as fetching data from a server, reading files, or any other operations that take time to complete.

   - States of a Promise:
     - Pending: Initial state. The promise's outcome hasn't been determined yet.
     - Fulfilled (Resolved): The operation completed successfully.
     - Rejected: The operation failed.
</details>

2. **Creating a Promise**

<details>
  <summary>click to expand</summary>

  - You create a new promise using the `Promise` constructor, which takes a function as an argument. This function, known as the executor function, is called immediately with two arguments: `resolve` and `reject`. Inside this function, you perform the asynchronous operation. You call `resolve(value)` when the operation is successful and `reject(reason)` if it fails.
  - Let's say you want to simulate fetching data from a server asynchronously using a promise:

    ```javascript
    const fetchData = new Promise((resolve, reject) => {
        setTimeout(() => {
            const data = { id: 1, name: 'John Doe' };
            resolve(data); // Simulate successful data fetch
            // If there's an error, you can reject the promise:
            // reject('Failed to fetch data');
        }, 2000); // Simulate 2 seconds delay
    });
    ```
</details>

3. **Consuming a Promise**

<details>
  <summary>click to expand</summary>

  - You consume a promise using its `then` and `catch` methods. then is called when the promise is fulfilled, and `catch` is called when the promise is rejected.
  - Now let's consume the promise we created and log the result to the console:
    ```javascript
    fetchData
        .then((data) => {
            console.log('Data:', data);
        })
        .catch((error) => {
            console.error('Error:', error);
        });
    ```
</details>

4. **Chaining Promises**

<details>
  <summary>click to expand</summary>

  - Promises can be chained using the `then` method. This allows you to execute multiple asynchronous operations sequentially.
  - Suppose you want to fetch user data and then fetch additional information based on the user's ID:

    ```javascript
    fetchUserData()
    .then((user) => {
        return fetchAdditionalInfo(user.id);
    })
    .then((additionalInfo) => {
        console.log('Additional info:', additionalInfo);
    })
    .catch((error) => {
        console.error('Error:', error);
    });
    ```
</details>

5. Promise.all

<details>
  <summary>click to expand</summary>

  - The `Promise.all` method takes an iterable of promises and returns a single promise that resolves when all of the promises in the iterable have resolved, or rejects with the reason of the first promise that rejects.
  - Let's say you have multiple promises for fetching data from different endpoints, and you want to wait for all of them to resolve before proceeding:

    ```javascript
    const promise1 = fetchDataFromEndpoint1();
    const promise2 = fetchDataFromEndpoint2();
    const promise3 = fetchDataFromEndpoint3();
    
    Promise.all([promise1, promise2, promise3])
        .then((results) => {
            console.log('All data fetched:', results);
        })
        .catch((error) => {
            console.error('Error:', error);
        });
    
    ```
</details>

6. Promise.race

<details>
  <summary>click to expand</summary>

  - The `Promise.race` method returns a promise that resolves or rejects as soon as one of the promises in the iterable resolves or rejects.
  - Suppose you have two promises for fetching data from different sources, and you want to use the one that resolves first:

    ```javascript
    const promise1 = fetchDataFromSource1();
    const promise2 = fetchDataFromSource2();
    
    Promise.race([promise1, promise2])
        .then((result) => {
            console.log('First data fetched:', result);
        })
        .catch((error) => {
            console.error('Error:', error);
        });

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

# HTML + Javascript

## HTML `<div> data-*` Attribute

<details>
  <summary>click to expand</summary>

### Using `data-*`

- A `data-*` attribute on a `<div>` tag attaches additional data to the `div` element.

- To create a custom attribute, replace `*` with a `lowercase string`, such as `data-id`, `data-status`, or `data-location`.

- An `<div>` element can have any number of `data-*` attributes, each with their own name.

- Using `data-*` attributes reduces the need for requests to the server.

- **Note:** The `data-*` attribute is not visible and does not change the appearance of the `div` element.

- Example:

    ```html
    <div data-registration-number="40039" style="background-color:aliceblue;padding:25px;">
        <b>Registration Successful!</b>
        <p>We will email your entry passes to the Louvre Museum in Paris.</p>
    </div>
    ```

### Syntax

- **Note:** The `*` can be any string, such as `data-id`,  `data-cost`,  `data-supplier`, etc.

    ```html
    <div data-*="value" >
    ```
    
    |VALUE|DESCRIPTION|
    |:---:|---|
    |`value`|A string value. Can be numeric, alphanumeric, JSON, etc.|
  
    ```html
    <div data-ticket="1223887" id="mydiv" style="background-color:aliceblue;padding:25px;">
        <b>Registration Successful!</b>
        <p>We will email your entry passes to the Louvre Museum in Paris.</p>
    </div>
    
    <br/>
    <button onclick="show1();">Show data with getAttribute</button>
    <button onclick="show2();">Show data with dataset.*</button>
    
    <script>
        let show1 = () => {
            let element = document.getElementById("mydiv");
            alert("Ticket # = " + element.getAttribute('data-ticket'));
        };

        let show2 = () => {
            let element = document.getElementById("mydiv");
            alert("Dataset.Ticket # = " + element.dataset.ticket);
        };
    </script>
    ```

</details>

## Memoization

<details>
  <summary>click to expand</summary>

- Memoization is an optimization technique that is used to improve the performance of a function by caching its return values so that it does not need to redo the potentially heavy computations next time it is called.

    ```javascript
    function carCount() {
        var count = 0;
        var increment = function () {
            return ++count;
        }
        return increment;
    }
    
    console.log(carCount());    // => 1
    console.log(carCount());    // => 2
    console.log(carCount());    // => 3
    console.log(carCount());    // => 4
    ```

- Let's look at how memoization can be used to improve computing the Fibonacci numbers. The recursive approach to generating these numbers does not scale very well. In the example below the getFibonacci function is recursively called 177 times to generate the sum of the first 10 Fibonacci numbers:

    ```javascript
    function getFibonacci(num) {
        if (num < 2) {
            return num;
        }
        return getFibonacci(num - 1) + getFibonacci(num - 2);
    }
    
    console.log(getFibonacci(10));     // => 55   (with 177 iterations)
    ```

- The program does a lot of extra work by not keeping track of previously calculated values. This is where memoization comes in. First, declare a cache array where you can store the already-calculated function values that were returned in previous calls. Then, instead of invoking the function, return these values in subsequent calls to the function, like so:

    ```javascript
    function getFibonacci(num) {
        var cache = [];
        var fib = function (value) {
            if (value < 2) return value;
            if (cache[value]) return cache[value];
    
            cache[value] = (fib(value - 1)) + (fib(value - 2));
            return cache[value];
        };
        return fib(num);
    }
    
    console.log(getFibonacci(10));     // => 55   (with 20 iterations)
    ```

- To generate the first 10 Fibonacci numbers, this function is recursively executed 20 times only. A significant improvement.

</details>
