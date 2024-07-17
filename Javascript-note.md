# JavaScript Date and Time

<details>
  <summary>click to expand</summary>

```javascript
const currentDate = new Date();
console.log(currentDate);
// Output: "Thu May 30 2024 09:15:36 GMT+0700 (Indochina Time)"

const specificDate = new Date(2024, 5, 14, 12, 0, 0);
console.log(specificDate);
// Output: "Fri Jun 14 2024 12:00:00 GMT+0700 (Indochina Time)"

const nextYear = new Date();
nextYear.setFullYear(nextYear.getFullYear() + 1);
console.log(nextYear);
// Output: date and time one year later

const formattedDate = currentDate.toLocaleDateString("en-US",
    { weekend: 'long', year: 'numeric', month: 'long', day: 'numeric' });
console.log(formattedDate);
// Output: "May 30, 2024"

// Install moment.js in here (https://momentjs.com/)
const momentDate = moment();
console.log(momentDate.format('MMMM Do YYYY, h:mm:ss a'));
// Output: "May 30th 2024, 9:48:48 am"
console.log(moment("20111031", "YYYYMMDD").fromNow());
// Output: "13 years ago"
console.log(moment("20111031").format('MMMM Do YYYY, h:mm:ss a'));
// Output: "October 31st 2011, 12:00:00 am"
```

</details>

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

## [async/await JS in-depth](https://medium.com/@ktan2050/async-await-in-depth-part-1-52ea6db38527)

- In nativePromise, a nested promise chain is used to fetch user info first and after getting the user info, fetching comments given by that user.It looks clumsy from a reading standpoint.The same thing can be achieved using async/await in a cleaner way as mentioned in asyncAwait method.

    ```javascript
    function nativePromise() {
        fetch("https://jsonplaceholder.typicode.com/todos/1")
            .then(response => response.json())
            .catch(error => console.log(error))
            .then(user => {
                fetch(`https://jsonplaceholder.typicode.com/posts/${user.userId}/comments`)
                    .then(response => response.json())
                    .catch(error => console.log(error))
                    .then(comments => {
                        console.log("user: ", user);
                        console.log("comments: ", comments);
                    })
                    .catch(error => console.log(error))
            })
            .catch(error => console.log(error))
    }
    ```

    ```javascript
    async function asyncAwait(id = 1) {
        try {
            let response = await fetch(`https://jsonplaceholder.typicode.com/todos/${id}`);
            const user = await response.json();
            response = await fetch(`https://jsonplaceholder.typicode.com/posts/${user.userId}/comments`);
            const comments = await response.json();
            console.log("user: ", user);
            console.log("comments: ", comments);
        } catch (error) {
            console.log(error);
        }
    }
    ```

## `Async`


- If a function is defined as `async`, then it implies that a promise will be returned.

- If `async` function returns a value instead of a promise then JavaScript will automatically warp the returned value in a resolved promise.

- If `async` function returns nothing then JavaScript will automatically warp `undefined` in a resolved promise.

    ```javascript
    async function foo1() {
        // JS will wrap 1 in a resolved primise i.e. equivalent to Promise.resolve(1)
        return 1;
    }

    async function foo2() {
        // JS will warp `undefined` in a resolved promise
        // As nothitng is being returned by this method
    }

    await foo1().then(result => result);
    // 1
    await foo3().then(result => result);
    // undefined
    ```

## `Await`

- The keyword `await` make sure JavaScript will wait for a promise until and unless the promise has been either resolved or rejected

- It can be used inside an `async` block only.

- If `await` is used in regular function then JavaScript will throw an error.

    ```javascript
    async function foo3() {
        const response = await fetch("https://jsonplaceholder.typicode.com/todos/1");
        // As await has been used, JS will wait until promise won't resolved
        const user = await response.json();
        console.log(user);
    }

    function syncFunction() {
        console.log("Before asyncAwait is called");
        foo3().then(result => result);
        console.log("After asyncAwait is called");
        // As JS is a single threaded, execution will continue in syncFunction
        // It won't wait for completion of foo3 method as syncFunction is a regular method
    }

    async function asyncFunction() {
        console.log("Before asyncAwait is called");
        await foo3().then(result => result);
        // As await is used for foo3, JS will wait to completes foo3 execution first
        // Then it will resume further execution
        console.log("After asyncAwait is called");
    }

    syncFunction();
    // Before asyncAwait is called
    // After asyncAwait is called
    // {userId: 1, id: 1, title: 'delectus aut autem', completed: false}
    asyncFunction();
    // Before asyncAwait is called
    // {userId: 1, id: 1, title: 'delectus aut autem', completed: false}
    // After asyncAwait is called
    ```

- The main task of await is to wait for a Promise.

- The await expression causes async function execution to pause until a Promise is settled (that is, fulfilled or rejected),

```javascript
async function foo() {
    console.log("foo execution started");
    let response = await fetch(`https://jsonplaceholder.typicode.com/todos/1`);
    const user = await response.json();
    console.log("user:", user);
    console.log("foo execution completed");
    return user;
}

function asyncAndSync() {
    console.log("Calling foo method");
    foo().then(user => console.log(`USER:`, JSON.stringify(user)));
    console.log("Called foo method");
    console.log("Normal execution continues add foo execution resumed once promise is settled");
}

asyncAndSync();
// Calling foo method
// foo execution started
// Called foo method
// Normal execution continues add foo execution resumed once promise is settled
// user: {userId: 1, id: 1, title: 'delectus aut autem', completed: false}
// foo execution completed
// USER: {"userId":1,"id":1,"title":"delectus aut autem","completed":false}
```

- `asyncAndSync` is a regular function which will execute in synchronous fashion.

- `foo` is an `async` function will execute in asynchronous fashion.

## Different way of using async/await with try, catch, then and throw

- There are many ways to handle a promise using `async/await`. It can be handled in a native way i.e. by using `.then` and `.catch`.

- When a promise gets `resolved`, the `resolved` value will get handled by `then` block.

- When a promise gets `rejected` then the `rejected` value will get handled by `catch` block.

- It can be handled using `try` and `catch` block.

- If a promise gets rejected then that rejected value will be caught in a `try` block and throw the same to `catch` block for error handling of rejected value.

```javascript
/**
 * Using async/await with then
 */
async function foo4() {
    let promise = new Promise(function(resolved, rejected) {
        setTimeout(() => resolved("Promise has been resolved"), 1000);
        // Promise will be resolved after 1 second
    });
    return promise;
}

funtion foo5() {
    foo4().then((message) => console.log(message));
}
```

```javascript
/**
 * Using async/await with catch
 */
async function foo6() {
    let promise = new Promise(function(resolve, reject) {
        setTimeout(function() {
            reject("Promise has been rejected")
            // Promise will get reject after 1 second
        }, 1000);
    });
    return promise;
}

function foo7() {
    foo6().catch(err => console.error(err));
}

foo7();
```

asyncAndSync();


asyncAndSync(10);
asyncAndSync(11);
asyncAndSync(12);


asyncAndSync(13);
asyncAndSync(14);
asyncAndSync(15);



function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}

async function foo8() {
    let promise = new Promise((resolve, reject) => {
        setTimeout(() => {
            if (getRandomInt(100) % 2 === 0) {
                resolve("Even number");
            }
            else {
                reject("Odd number");
            }
        }, 1000);
    });

    return promise;
}

function foo9() {
    console.log("Before foo8 is called");
    foo8()
        .then(result => result)
        .catch(error => error)
        .finally(() => console.log("foo8 execution finished"));
    console.log("After foo8 is called");
}

async function foo11() {
    try {
        const result = await foo8();
        console.log(result);
    } catch (e) {
        console.log(`Inside foo11 try-catch block ${e}`);
    }
}


foo9();



async function foo13() {
    const result = await foo8()
        .then(result => console.log(result))
        .catch(error => {
            console.log(`Inside foo13 try-catch block ${error}`);
            throw error;
        });
