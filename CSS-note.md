# CSS 2D Transforms

<details>
  <summary>click to expand</summary>

## CSS 2D Transforms

- CSS transforms allow you to move, rotate, scale, and skew elements.

## CSS 2D Transforms Methods

- With the CSS transform property you can use the following 2D transformation methods:

  - `translate()`
  - `rotate()`
  - `scaleX()`
  - `scaleY()`
  - `scale()`
  - `skewX()`
  - `skewY()`
  - `skew()`
  - `matrix()`

## The `translate()` Method

- The `translate()` method moves an element from its current position (according to the parameters given for the `X-axis` and the `Y-axis`).

- The following example moves the `<div>` element 50 pixels to the right, and 100 pixels down from its current position:

    <img src="asset/css_transform_translate.gif"/>

    ```css
    div {
       transform: translate(50px, 100px);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_translate)

## The `rotate()` Method

- The `rotate()` method rotates an element clockwise or counter-clockwise according to a given degree.

- The following example rotates the `<div>` element clockwise with 20 degrees:

    <img src="asset/css_transform_rotate.gif"/>

    ```css
    div {
        transform: rotate(20deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_rotate)

- Using negative values will rotate the element counter-clockwise.

- The following example rotates the `<div>` element counter-clockwise with 20 degrees:

    ```css
    div {
        transform: rotate(-20deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_rotate2)

## The `scale()` Method

- The `scale()` method increases or decreases the size of an element (according to the parameters given for the width and height).

- The following example increases the `<div>` element to be two times of its original width, and three times of its original height:

    <img src="asset/css_transform_scale.gif"/>

    ```css
    div {
        transform: scale(2, 3);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_scale)

- The following example decreases the `<div>` element to be half of its original width and height:

    ```css
    div {
        transform: scale(0.5, 0.5);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_scale2)

## The `scaleX()` Method

- The `scaleX()` method increases or decreases the width of an element.

- The following example increases the `<div>` element to be two times of its original width:

    ```css
    div {
        transform: scaleX(2);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_scaleX)

- The following example decreases the `<div>` element to be half of its original width:

    ```css
    div {
        transform: scaleX(0.5);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_scaleX2)

## The `scaleY()` Method

- The `scaleY()` method increases or decreases the height of an element.

- The following example increases the `<div>` element to be three times of its original height:

    ```css
    div {
        transform: scaleY(3);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_scaleY)

- The following example decreases the `<div>` element to be half of its original height:

    ```css
    div {
        transform: scaleY(0.5);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_scaleY2)

## The `skewX()` Method

- The `skewX()` method skews an element along the X-axis by the given angle.

- The following example skews the `<div>` element 20 degrees along the X-axis:

    ```css
    div {
        transform: skewX(20deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_skewx)

## The `skewY()` Method

- The `skewY()` method skews an element along the Y-axis by the given angle.

- The following example skews the `<div>` element 20 degrees along the Y-axis:

    ```css
    div {
        transform: skewY(20deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_skewy)

## The `skew()` Method

- The `skew()` method skews an element along the X and Y-axis by the given angles.

- The following example skews the `<div>` element 20 degrees along the X-axis, and 10 degrees along the Y-axis:

    ```css
    div {
        transform: skew(20deg, 10deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_skew)

- If the second parameter is not specified, it has a zero value. So, the following example skews the `<div>` element 20 degrees along the X-axis:

    ```css
    div {
        transform: skew(20deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_skew2)

## The `matrix()` Method

- The `matrix()` method combines all the 2D transform methods into one.

- The `matrix()` method take six parameters, containing mathematic functions, which allows you to rotate, scale, move (translate), and skew elements.

- The parameters are as follow: `matrix(scaleX(), skewY(), skewX(), scaleY(), translateX(), translateY()`)

    <img src="asset/css_transform_rotate.gif"/>

    ```css
    div {
        transform: matrix(1, -0.3, 0, 1, 0, 0);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_matrix1)

## CSS 2D Transform Methods

- CSS 2D Transform Methods

    |Function|Description|
    |---|---|
    |`matrix(n,n,n,n,n,n)`|Defines a 2D transformation, using a matrix of six values|
    |`translate(x,y)`|Defines a 2D translation, moving the element along the X- and the Y-axis|
    |`translateX(n)`|Defines a 2D translation, moving the element along the X-axis|
    |`translateY(n)`|Defines a 2D translation, moving the element along the Y-axis|
    |`scale(x,y)`|Defines a 2D scale transformation, changing the elements width and height|
    |`scaleX(n)`|Defines a 2D scale transformation, changing the element's width|
    |`scaleY(n)`|Defines a 2D scale transformation, changing the element's height|
    |`rotate(angle)`|Defines a 2D rotation, the angle is specified in the parameter|
    |`skew(x-angle,y-angle)`|Defines a 2D skew transformation along the X- and the Y-axis|
    |`skewX(angle)`|Defines a 2D skew transformation along the X-axis|
    |`skewY(angle)`|Defines a 2D skew transformation along the Y-axis|

</details>

# CSS 3D Transforms

<details>
  <summary>click to expand</summary>

## CSS 3D Transforms

- CSS also supports 3D transformations.

## CSS 3D Transforms Methods

- With the CSS transform property you can use the following 3D transformation methods:

  - `rotateX()`
  - `rotateY()`
  - `rotateZ()`

## The `rotateX()` Method

- The `rotateX()` method rotates an element around its X-axis at a given degree:

    ```css
    # myDiv {
        transform: rotateX(150deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_rotateX)

## The rotateY() Method

- The rotateY() method rotates an element around its Y-axis at a given degree:

    ```css
    # myDiv {
        transform: rotateY(150deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_rotateY)

## The `rotateZ()` Method

- The `rotateZ()` method rotates an element around its Z-axis at a given degree:

    ```css
    # myDiv {
        transform: rotateZ(90deg);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transform_rotateZ)

## CSS 3D Transform Methods

- 3D Transform Methods

    |Function|Description|
    |---|---|
    |`matrix3d(n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n)`|Defines a 3D transformation, using a 4x4 matrix of 16 values|
    |`translate3d(x,y,z)`|Defines a 3D translation|
    |`translateX(x)`|Defines a 3D translation, using only the value for the X-axis|
    |`translateY(y)`|Defines a 3D translation, using only the value for the Y-axis|
    |`translateZ(z)`|Defines a 3D translation, using only the value for the Z-axis|
    |`scale3d(x,y,z)`|Defines a 3D scale transformation|
    |`scaleX(x)`|Defines a 3D scale transformation by giving a value for the X-axis|
    |`scaleY(y)`|Defines a 3D scale transformation by giving a value for the Y-axis|
    |`scaleZ(z)`|Defines a 3D scale transformation by giving a value for the Z-axis|
    |`rotate3d(x,y,z,angle)`|Defines a 3D rotation|
    |`rotateX(angle)`|Defines a 3D rotation along the X-axis|
    |`rotateY(angle)`|Defines a 3D rotation along the Y-axis|
    |`rotateZ(angle)`|Defines a 3D rotation along the Z-axis|
    |`perspective(n)`|Defines a perspective view for a 3D transformed element|

</details>

# CSS Transitions

<details>
  <summary>click to expand</summary>

## How to Use CSS Transitions?

- You will learn about the following properties:

  - `transition`
  - `transition-delay`
  - `transition-duration`
  - `transition-property`
  - `transition-timing-function`

- To create a transition effect, you must specify two things:

  - the CSS property you want to add an effect to
  - the duration of the effect

- **Note**: If the duration part is not specified, the transition will have no effect, because the default value is **0**.

- The following example shows a `100px * 100px` red `<div>` element. The `<div>` element has also specified a transition effect for the width property, with a duration of 2 seconds:

    ```css
    div {
        width: 100px;
        height: 100px;
        background: red;
        transition: width 2s;
    }
    ```

- The transition effect will start when the specified CSS property (width) changes value.

- Now, let us specify a new value for the width property when a user mouses over the `<div>` element:

    ```css
    div:hover {
        width: 300px;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition1)

- Notice that when the cursor mouses out of the element, it will gradually change back to its original style.

## Change Several Property Values

- The following example adds a transition effect for both the width and height property, with a duration of 2 seconds for the width and 4 seconds for the height:

    ```css
    div {
        transition: width 2s, height 4s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition2)

## Specify the Speed Curve of the Transition

- The `transition-timing-function` property specifies the speed curve of the transition effect.

- The `transition-timing-function` property can have the following values:

  - `ease` - specifies a transition effect with a slow start, then fast, then end slowly (this is default).
  - `linear` - specifies a transition effect with the same speed from start to end.
  - `ease-in` - specifies a transition effect with a slow start.
  - `ease-out` - specifies a transition effect with a slow end.
  - `ease-in-out` - specifies a transition effect with a slow start and end.
  - `cubic-bezier(n,n,n,n)` - lets you define your own values in a cubic-bezier function.

- The following example shows some of the different speed curves that can be used:

    ```css
    # div1 {transition-timing-function: linear;}
    # div2 {transition-timing-function: ease;}
    # div3 {transition-timing-function: ease-in;}
    # div4 {transition-timing-function: ease-out;}
    # div5 {transition-timing-function: ease-in-out;}
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition_speed)

## Delay the Transition Effect

- The transition-delay property specifies a delay (in seconds) for the transition effect.

- The following example has a 1 second delay before starting:

    ```css
    div {
        transition-delay: 1s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition_delay)

## Transition + Transformation

- The following example adds a transition effect to the transformation:

    ```css
    div {
        transition: width 2s, height 2s, transform 2s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition_transform)

## More Transition CSS

- The CSS transition properties can be specified one by one, like this:

    ```css
    div {
        transition-property: width;
        transition-duration: 2s;
        transition-timing-function: linear;
        transition-delay: 1s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition4)

- or by using the shorthand property transition:

    ```css
    div {
        transition: width 2s linear 1s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_transition5)

## CSS Transition Properties

- The following table lists all the CSS transition properties:

    |Property|Description|
    |---|---|
    |`transition`|A shorthand property for setting the four transition properties into a single property|
    |`transition-delay`|Specifies a delay (in seconds) for the transition effect|
    |`transition-duration`|Specifies how many seconds or milliseconds a transition effect takes to complete|
    |`transition-property`|Specifies the name of the CSS property the transition effect is for|
    |`transition-timing-function`|Specifies the speed curve of the transition effect|

</details>

# CSS Animations

<details>
  <summary>click to expand</summary>

## CSS Animations

- CSS allows animation of HTML elements without using JavaScript!

- In this chapter you will learn about the following properties:

  - `@keyframes`
  - `animation-name`
  - `animation-duration`
  - `animation-delay`
  - `animation-iteration-count`
  - `animation-direction`
  - `animation-timing-function`
  - `animation-fill-mode`
  - `animation`

## What are CSS Animations?

- An animation lets an element gradually change from one style to another.

- You can change as many CSS properties you want, as many times as you want.

- To use CSS animation, you must first specify some keyframes for the animation.

- Keyframes hold what styles the element will have at certain times.

## The `@keyframes` Rule

- When you specify CSS styles inside the `@keyframes` rule, the animation will gradually change from the current style to the new style at certain times.

- To get an animation to work, you must bind the animation to an element.

- The following example binds the "example" animation to the `<div>` element. The animation will last for 4 seconds, and it will gradually change the background-color of the `<div>` element from "red" to "yellow":

    ```css
    /*The animation code*/
    @keyframes example {
        from {background-color: red;}
        to {background-color: yellow;}
    }

    /*The element to apply the animation to*/
    div {
        width: 100px;
        height: 100px;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation1)

- **Note**: The `animation-duration` property defines how long an animation should take to complete. If the `animation-duration` property is not specified, no animation will occur, because the default value is 0s (0 seconds).

- In the example above we have specified when the style will change by using the keywords "from" and "to" (which represents `0%` (start) and `100%` (complete)).

- It is also possible to use percent. By using percent, you can add as many style changes as you like.

- The following example will change the background-color of the `<div>` element when the animation is 25% complete, 50% complete, and again when the animation is 100% complete:

    ```css
    /*The animation code*/
    @keyframes example {
        0%   {background-color: red;}
        25%  {background-color: yellow;}
        50%  {background-color: blue;}
        100% {background-color: green;}
    }

    /*The element to apply the animation to*/
    div {
        width: 100px;
        height: 100px;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation2)

- The following example will change both the background-color and the position of the `<div>` element when the animation is 25% complete, 50% complete, and again when the animation is 100% complete:

    ```css
    /*The animation code*/
    @keyframes example {
        0%   {background-color:red; left:0px; top:0px;}
        25%  {background-color:yellow; left:200px; top:0px;}
        50%  {background-color:blue; left:200px; top:200px;}
        75%  {background-color:green; left:0px; top:200px;}
        100% {background-color:red; left:0px; top:0px;}
    }

    /*The element to apply the animation to*/
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
    }
    ```

## Delay an Animation

- The `animation-delay` property specifies a delay for the start of an animation.

- The following example has a 2 seconds delay before starting the animation:

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-delay: 2s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_delay)

- **Negative values are also allowed**. If using negative values, the animation will start as if it had already been playing for N seconds.

- In the following example, the animation will start as if it had already been playing for 2 seconds:

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-delay: -2s;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_delay2)

## Set How Many Times an Animation Should Run

- The `animation-iteration-count` property specifies the number of times an animation should run.

- The following example will run the animation 3 times before it stops:

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-iteration-count: 3;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_count)

- The following example uses the value `infinite` to make the animation continue for ever:

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-iteration-count: infinite;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_count2)

## Run Animation in Reverse Direction or Alternate Cycles

- The `animation-direction` property specifies whether an animation should be played forwards, backwards or in alternate cycles.

- The `animation-direction` property can have the following values:

  - `normal` - The animation is played as normal (forwards). This is default
  - `reverse` - The animation is played in reverse direction (backwards)
  - `alternate` - The animation is played forwards first, then backwards
  - `alternate-reverse` - The animation is played backwards first, then forwards

- The following example will run the animation in reverse direction (backwards):

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-direction: reverse;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_direction)

- The following example uses the value `alternate` to make the animation run forwards first, then backwards:

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-iteration-count: 2;
        animation-direction: alternate;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_direction2)

- The following example uses the value `alternate-reverse` to make the animation run backwards first, then forwards:

    ```css
    div {
        width: 100px;
        height: 100px;
        position: relative;
        background-color: red;
        animation-name: example;
        animation-duration: 4s;
        animation-iteration-count: 2;
        animation-direction: alternate-reverse;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_direction3)

## Specify the Speed Curve of the Animation

- The `animation-timing-function` property specifies the speed curve of the animation.

- The `animation-timing-function` property can have the following values:

  - `ease` - Specifies an animation with a slow start, then fast, then end slowly (this is default).
  - `linear` - Specifies an animation with the same speed from start to end.
  - `ease-in` - Specifies an animation with a slow start.
  - `ease-out` - Specifies an animation with a slow end.
  - `ease-in-out` - Specifies an animation with a slow start and end.
  - `cubic-bezier(n,n,n,n)` - Lets you define your own values in a cubic-bezier function.

- The following example shows some of the different speed curves that can be used:

    ```css
    # div1 {animation-timing-function: linear;}
    # div2 {animation-timing-function: ease;}
    # div3 {animation-timing-function: ease-in;}
    # div4 {animation-timing-function: ease-out;}
    # div5 {animation-timing-function: ease-in-out;}
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_speed)

## Specify the fill-mode For an Animation

- CSS animations do not affect an element before the first keyframe is played or after the last keyframe is played. The `animation-fill-mode` property can override this behavior.

- The `animation-fill-mode` property specifies a style for the target element when the animation is not playing (before it starts, after it ends, or both).

- The `animation-fill-mode` property can have the following values:

  - `none` - Default value. Animation will not apply any styles to the element before or after it is executing.
  - `forwards` - The element will retain the style values that is set by the last keyframe (depends on `animation-direction` and `animation-iteration-count`).
  - `backwards` - The element will get the style values that is set by the first keyframe (depends on `animation-direction`), and retain this during the `animation-delay` period.
  - `both` - The animation will follow the rules for both forwards and backwards, extending the animation properties in both directions.

- The following example lets the `<div>` element retain the style values from the last keyframe when the animation ends:

    ```css
    div {
        width: 100px;
        height: 100px;
        background: red;
        position: relative;
        animation-name: example;
        animation-duration: 3s;
        animation-fill-mode: forwards;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_fill-mode)

- The following example lets the `<div>` element get the style values set by the first keyframe before the animation starts (during the animation-delay period):

    ```css
    div {
        width: 100px;
        height: 100px;
        background: red;
        position: relative;
        animation-name: example;
        animation-duration: 3s;
        animation-delay: 2s;
        animation-fill-mode: backwards;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_fill-mode2)

- The following example lets the `<div>` element get the style values set by the first keyframe before the animation starts, and retain the style values from the last keyframe when the animation ends:

    ```css
    div {
        width: 100px;
        height: 100px;
        background: red;
        position: relative;
        animation-name: example;
        animation-duration: 3s;
        animation-delay: 2s;
        animation-fill-mode: both;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation_fill-mode3)

## Animation Shorthand Property

- The example below uses six of the animation properties:

    ```css
    div {
        animation-name: example;
        animation-duration: 5s;
        animation-timing-function: linear;
        animation-delay: 2s;
        animation-iteration-count: infinite;
        animation-direction: alternate;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation4)

- The same animation effect as above can be achieved by using the shorthand animation property:

    ```css
    div {
        animation: example 5s linear 2s infinite alternate;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_animation5)

## CSS Animation Properties

- The following table lists the `@keyframes` rule and all the CSS animation properties:

    |Property|Description|
    |---|---|
    |`@keyframes`|Specifies the animation code|
    |`animation`|A shorthand property for setting all the animation properties|
    |`animation-delay`|Specifies a delay for the start of an animation|
    |`animation-direction`|Specifies whether an animation should be played forwards, backwards or in alternate cycles|
    |`animation-duration`|Specifies how long time an animation should take to complete one cycle|
    |`animation-fill-mode`|Specifies a style for the element when the animation is not playing (before it starts, after it ends, or both)|
    |`animation-iteration-count`|Specifies the number of times an animation should be played|
    |`animation-name`|Specifies the name of the @keyframes animation|
    |`animation-play-state`|Specifies whether the animation is running or paused|
    |`animation-timing-function`|Specifies the speed curve of the animation|

</details>


# CSS Pseudo-classes

<details>
  <summary>click to expand</summary>

## What are Pseudo-classes?

- A pseudo-class is used to define a special state of an element.

## Syntax

- The syntax of pseudo-classes:

    ```css
    selector:pseudo-class {
        property: value;
    }
    ```

## Anchor Pseudo-classes

- Links can be displayed in different ways:

    ```css
    /*unvisited link*/
    a:link {
        color: #FF0000;
    }

    /*visited link*/
    a:visited {
        color: #00FF00;
    }

    /*mouse over link*/
    a:hover {
        color: #FF00FF;
    }

    /*selected link*/
    a:active {
        color: #0000FF;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_pseudo-class_links)

## Pseudo-classes and HTML Classes

- Pseudo-classes can be combined with HTML classes:

- When you hover over the link in the example, it will change color:

    ```css
    a.highlight:hover {
        color: #ff0000;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_pseudo-class)

## Hover on `<div>`

- An example of using the `:hover` pseudo-class on a `<div>` element:

    ```css
    div:hover {
        background-color: blue;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_pseudo-class_hover_div)

## Simple Tooltip Hover

- Hover over a `<div>` element to show a `<p>` element (like a tooltip):

    ```css
    p {
        display: none;
        background-color: yellow;
        padding: 20px;
    }

    div:hover p {
        display: block;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_pseudo-class_hover_tooltip)

## CSS - The `:first-child` Pseudo-class

- The `:first-child` pseudo-class matches a specified element that is the first child of another element.

### Match the first `<p>` element

- In the following example, the selector matches any `<p>` element that is the first child of any element:

    ```css
    p:first-child {
        color: blue;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_first-child1)

### Match the first `<i>` element in all `<p>` elements

- In the following example, the selector matches the first `<i>` element in all `<p>` elements:

    ```css
    p i:first-child {
        color: blue;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_first-child2)

### Match all `<i>` elements in all first child `<p>` elements

- In the following example, the selector matches all `<i>` elements in `<p>` elements that are the first child of another element:

    ```css
    p:first-child i {
        color: blue;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_first-child3)

## All CSS Pseudo Classes

- All CSS Pseudo Classes

    |Selector|Example|Example description|
    |---|---|---|
    |[`:active`](https://www.w3schools.com/cssref/sel_active.asp)|`a:active`|Selects the active link|
    |[`:checked`](https://www.w3schools.com/cssref/sel_checked.asp)|`input:checked`|Selects every checked `<input>`; element|
    |[`:disabled`](https://www.w3schools.com/cssref/sel_disabled.asp)|`input:disabled`|Selects every disabled `<input>`; element|
    |[`:empty`](https://www.w3schools.com/cssref/sel_empty.asp)|`p:empty`|Selects every `<p>`; element that has no childre>|
    |[`:enabled`](https://www.w3schools.com/cssref/sel_enabled.asp)|`input:enabled`|Selects every enabled `<input>`; element|
    |[`:first-child`](https://www.w3schools.com/cssref/sel_firstchild.asp)|`p:first-child`|Selects every `<p>`; elements that is the first child of itent|
    |[`:first-of-type`](https://www.w3schools.com/cssref/sel_first-of)|`p:first-of-type`|Selects every `<p>`; element that is the first `<p>`ment of its parent|
    |[`:focus`](https://www.w3schools.com/cssref/sel_focus.asp)|`input:focus`|Selects the `<input>`; element that has focus|
    |[`:hover`](https://www.w3schools.com/cssref/sel_hover.asp)|`a:hover`|Selects links on mouse over|
    |[`:in-range`](https://www.w3schools.com/cssref/sel_in-range)|`input:in-range`|Selects `<input>`; elements with a value within a fied range|
    |[`:invalid`](https://www.w3schools.com/cssref/sel_invalid.asp)|`input:invalid`|Selects all `<input>`; elements with an invalid value|
    |[`:lang(<i>language</i>)`](https://www.w3schools.com/cssref/sel_lang.asp)|`p:lang(it)`|Selects every `<p>`; element with a lang attribute value startith "it"|
    |[`:last-child`](https://www.w3schools.com/cssref/sel_last-child)|`p:last-child`|Selects every `<p>`; elements that is the last child o parent|
    |[`:last-of-type`](https://www.w3schools.com/cssref/sel_last-of)|`p:last-of-type`|Selects every `<p>`; element that is the last element of its parent|
    |[`:link`](https://www.w3schools.com/cssref/sel_link.asp)|`a:link`|Selects all unvisited links|
    |[`:not(selector)`](https://www.w3schools.com/cssref/sel_not.asp)|`:not(p)`|Selects every element that is not a `<p>`; element|
    |[`:nth-child(n)`](https://www.w3schools.com/cssref/sel_nth-child)|`p:nth-child(2)`|Selects every `<p>`; element that is the second child of parent|
    |[`:nth-last-child(n)`](https://www.w3schools.com/cssref/sel_nth-last)|`p:nth-last-child(2)`|Selects every `<p>`; element that is the second child of itent, counting from the last child|
    |[`:nth-last-of-type(n)`](https://www.w3schools.com/cssref/sel_nth-last)|`p:nth-last-of-type(2)`|Selects every `<p>`; element that is the second `<p>`; eleof its parent, counting from the last child|
    |[`:nth-of-type(n)`](https://www.w3schools.com/cssref/sel_nth-of)|`p:nth-of-type(2)`|Selects every `<p>`; element that is the second `<p&lement of its parent|
    |[`:only-of-type`](https://www.w3schools.com/cssref/sel_only-of)|`p:only-of-type`|Selects every `<p>`; element that is the only `<p&gement of its parent|
    |[`:only-child`](https://www.w3schools.com/cssref/sel_only-child)|`p:only-child`|Selects every `<p>`; element that is the only child ofparent|
    |[`:optional`](https://www.w3schools.com/cssref/sel_optional.asp)|`input:optional`|Selects `<input>`; elements with no "required" attribud>|
    |[`:out-of-range`](https://www.w3schools.com/cssref/sel_out-of)|`input:out-of-range`|Selects `<input>`; elements with a value outside a sied range|
    |[`:read-only`](https://www.w3schools.com/cssref/sel_read-only)|`input:read-only`|Selects `<input>`; elements with a "readonly" attribpecified|
    |[`:read-write`](https://www.w3schools.com/cssref/sel_read-write)|`input:read-write`|Selects `<input>`; elements with no "readonly" attribute|
    |[`:required`](https://www.w3schools.com/cssref/sel_required.asp)|`input:required`|Selects `<input>`; elements with a "required" attributcified|
    |[`:root`](https://www.w3schools.com/cssref/sel_root.asp)|`root`|Selects the document's root element|
    |[`:target`](https://www.w3schools.com/cssref/sel_target.asp)|`#news:target`|Selects the current active #news element (clicked on  containing that anchor name)|
    |[`:valid`](https://www.w3schools.com/cssref/sel_valid.asp)|`input:valid`|Selects all `<input>`; elements with a valid value|
    |[`:visited`](https://www.w3schools.com/cssref/sel_visited.asp)|`a:visited`|Selects all visited links|

</details>

# CSS Pseudo-elements

<details>
  <summary>click to expand</summary>

## What are Pseudo-Elements?

- A CSS pseudo-element is used to style specified parts of an element.

## Syntax

- The syntax of pseudo-elements:

    ```css
    selector::pseudo-element {
        property: value;
    }
    ```

## The `::first-line` Pseudo-element

- The `::first-line` pseudo-element is used to add a special style to the first line of a text.

- The following example formats the first line of the text in all `<p>` elements:

    ```css
    p::first-line {
        color: #ff0000;
        font-variant: small-caps;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_firstline)

- **Note**: The `::first-line` pseudo-element can only be applied to block-level elements.

- The following properties apply to the `::first-line` pseudo-element:

    - font properties
    - color properties
    - background properties
    - word-spacing
    - letter-spacing
    - text-decoration
    - vertical-align
    - text-transform
    - line-height
    - clear

## The `::first-letter` Pseudo-element

- The `::first-letter` pseudo-element is used to add a special style to the first letter of a text.

- The following example formats the first letter of the text in all `<p>` elements:

    ```css
    p::first-letter {
        color: #ff0000;
        font-size: xx-large;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_firstletter)

- Note: The `::first-letter` pseudo-element can only be applied to block-level elements.

- The following properties apply to the `::first-letter` pseudo- element:

    - font properties
    - color properties
    - background properties
    - margin properties
    - padding properties
    - border properties
    - text-decoration
    - vertical-align (only if `float` is `none`)
    - text-transform
    - line-height
    - float
    - clear

## Pseudo-elements and HTML Classes

- Pseudo-elements can be combined with HTML classes:

    ```css
    p.intro::first-letter {
        color: #ff0000;
        font-size: 200%;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_pseudo-element)

- The example above will display the first letter of paragraphs with `class="intro"`, in red and in a larger size.

## Pseudo-elements and HTML Classes

- Pseudo-elements can be combined with HTML classes:

    ```css
    p.intro::first-letter {
        color: #ff0000;
        font-size: 200%;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_pseudo-element)

- The example above will display the first letter of paragraphs with class="intro", in red and in a larger size.

## Multiple Pseudo-elements

- Several pseudo-elements can also be combined.

- In the following example, the first letter of a paragraph will be red, in an `xx-large` font size. The rest of the first line will be blue, and in small-caps. The rest of the paragraph will be the default font size and color:

    ```css
    p::first-letter {
        color: #ff0000;
        font-size: xx-large;
    }

    p::first-line {
        color: #0000ff;
        font-variant: small-caps;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_firstline_letter)

## CSS - The `::before` Pseudo-element

- The `::before` pseudo-element can be used to insert some content before the content of an element.

- The following example inserts an image before the content of each `<h1>` element:

    ```css
    h1::before {
        content: url(smiley.gif);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_before)

## CSS - The `::after` Pseudo-element

- The `::after` pseudo-element can be used to insert some content after the content of an element.

- The following example inserts an image after the content of each `<h1>` element:

    ```css
    h1::after {
        content: url(smiley.gif);
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_after)

## CSS - The `::marker` Pseudo-element

- The `::marker` pseudo-element selects the markers of list items.

- The following example styles the markers of list items:

    ```css
    ::marker {
        color: red;
        font-size: 23px;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss_marker)

## CSS - The `::selection` Pseudo-element

- The `::selection` pseudo-element matches the portion of an element that is selected by a user.

- The following CSS properties can be applied to `::selection`: color, background, cursor, and outline.

- The following example makes the selected text red on a yellow background:

    ```css
    ::selection {
        color: red;
        background: yellow;
    }
    ```

    [Try It Yourself](https://www.w3schools.com/css/tryit.asp?filename=trycss3_selection)

</details>
