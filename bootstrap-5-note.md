# Bootstrap 5 Containers

<details>
  <summary>click to expand</summary>

## Bootstrap 5 Containers

- Containers are used to pad the content inside of them, and there are two container classes available:

1. The `.container` class provides a responsive fixed width container.
2. The `.container-fluid` class provides a full width container, spanning the entire width of the viewport.

    <img src="asset/container_container-fluid.png" width="800"/>

## Fixed Container

- Use the `.container` class to create a responsive, fixed-width container.

- Note that its width (max-width) will change on different screen sizes:

    ||Extra small< 576px|Small ≥ 576px|Medium ≥ 768px|Large ≥ 992px|Extra Large ≥ 1200px|XXL ≥ 1400px|
    |:---:|:---:|:---:|:---:|:---:|:---:|:---:|
    |max-width|100%|540px|720px|960px|1140px|1320px|

    ```html
    <div class="container">
        <h1>My First Bootstrap Page</h1>
        <p>This is some text.</p>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_gs_container&stacked=h)

## Fluid Container

- Use the `.container-fluid` class to create a full width container, that will always span the entire width of the screen (width is always 100%):

    ```html
    <div class="container-fluid">
        <h1>My First Bootstrap Page</h1>
        <p>This is some text.</p>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_gs_container-fluid&stacked=h)

## Container Padding

`p` | `px-[0-5]` | `px-[0-5]` | `pt-[0-5]` | `pb-[0-5]` | `ps-[0-5]` | `pe-[0-5]`

- Add a top padding

    ```html
    <div class="container pt-1"></div>
    <div class="container pt-2"></div>
    <div class="container pt-3"></div>
    <div class="container pt-4"></div>
    <div class="container pt-5"></div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_container_padding&stacked=h)

- Add a bottom padding

    ```html
    <div class="container pb-1"></div>
    ...
    ```

- Add a left padding

    ```html
    <div class="container ps-2"></div>
    ...
    ```

- Add a right padding

    ```html
    <div class="container pe-3"></div>
    ...
    ```

- Add 4 direct padding

    ```html
    <div class="container p-4"></div>
    ...
    ```

- Add horizontal padding (left-right)

    ```html
    <div class="container px-4"></div>
    ...
    ```

- Add vertical padding (up-down)

    ```html
    <div class="container py-4"></div>
    ...
    ```

## Container Margin

`m` | `mx-[0-5]` | `mx-[0-5]` | `mt-[0-5]` | `mb-[0-5]` | `ms-[0-5]` | `me-[0-5]`

- Add margin

    ```html
    <div class="container mt-5"></div> <!-- Add a top margin -->
    <div class="container mb-1"></div> <!-- Add a bottom margin -->
    <div class="container ms-2"></div> <!-- Add a left margin -->
    <div class="container me-3"></div> <!-- Add a right margin -->
    <div class="container m-4"></div> <!-- Add 4 direct margin -->
    <div class="container mx-4"></div> <!-- Add horizontal margin (left-right) -->
    <div class="container my-4"></div> <!-- Add vertical margin (up-down) -->
    ...
    ```

## Container Border and Color

- Other utilities, such as borders and colors, are also often used together with containers:

    ```html
    <div class="container p-5 my-5 border"></div>

    <div class="container p-5 my-5 bg-dark text-white"></div>

    <div class="container p-5 my-5 bg-primary text-white"></div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_container_color&stacked=h)

## Responsive Containers

- You can also use the `.container-sm|md|lg|xl|xxl` classes to determine when the container should be responsive.

- The `max-width` of the container will change on different screen sizes/viewports:

    |Class|Extra small < 576px|Small ≥ 576px|Medium ≥ 768px|Large ≥ 992px|Extra large ≥ 1200px|XXL ≥ 1400px|
    |:---:|:---:|:---:|:---:|:---:|:---:|:---:|
    |`.container-sm`|100%|540px|720px|960px|1140px|1320px|
    |`.container-md`|100%|100%|720px|960px|1140px|1320px|
    |`.container-lg`|100%|100%|100%|960px|1140px|1320px|
    |`.container-xl`|100%|100%|100%|100%|1140px|1320px|
    |`.container-xxl`|100%|100%|100%|100%|100%|1320px|

    ```html
    <div class="container-sm">.container-sm</div>
    <div class="container-md">.container-md</div>
    <div class="container-lg">.container-lg</div>
    <div class="container-xl">.container-xl</div>
    <div class="container-xxl">.container-xxl</div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_container_resp&stacked=h)

# Bootstrap 5 Grids

## Bootstrap 5 Grid System

- Bootstrap's grid system is built with flexbox and allows up to 12 columns across the page.

- If you do not want to use all 12 columns individually, you can group the columns together to create wider columns:

- The grid system is responsive, and the columns will re-arrange automatically depending on the screen size.

- Make sure that the sum adds up to 12 or fewer (it is not required that you use all 12 available columns).

    <img src="asset/bootstrap_5_grids.png" width="800"/>

## Grid Classes

- The Bootstrap 5 grid system has six classes:

  - `.col-` (extra small devices - screen width less than 576px)
  - `.col-sm-` (small devices - screen width equal to or greater than 576px)
  - `.col-md-` (medium devices - screen width equal to or greater than 768px)
  - `.col-lg-` (large devices - screen width equal to or greater than 992px)
  - `.col-xl-` (xlarge devices - screen width equal to or greater than 1200px)
  - `.col-xxl-` (xxlarge devices - screen width equal to or greater than 1400px)

**Tip**: Each class scales up, so if you want to set the same widths for `sm` and `md`, you only need to specify `sm`.

## Basic Structure of a Bootstrap 5 Grid

- The following is a basic structure of a Bootstrap 5 grid:

    ```html
    <!-- Control the column width, and how they should appear on different devices -->
    <div class="row">
        <div class="col-*-*"></div>
        <div class="col-*-*"></div>
    </div>
    <div class="row">
        <div class="col-*-*"></div>
        <div class="col-*-*"></div>
        <div class="col-*-*"></div>
    </div>
    <!-- Or let Bootstrap automatically handle the layout -->
    <div class="row">
        <div class="col"></div>
        <div class="col"></div>
        <div class="col"></div>
    </div>
    ```

### Three Equal Columns

- The following example shows how to create three equal-width columns, on all devices and screen widths:

    ```html
    <div class="row">
        <div class="col">.col</div>
        <div class="col">.col</div>
        <div class="col">.col</div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_grid_ex&stacked=h)

### Responsive Columns

- The following example shows how to create four equal-width columns starting at tablets and scaling to extra large desktops. **On mobile phones or screens that are less than 576px wide, the columns will automatically stack on top of each other**:

    ```html
    <div class="row">
        <div class="col-sm-3">.col-sm-3</div>
        <div class="col-sm-3">.col-sm-3</div>
        <div class="col-sm-3">.col-sm-3</div>
        <div class="col-sm-3">.col-sm-3</div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_grid_ex1&stacked=h)

### Two Unequal Responsive Columns

- The following example shows how to get two various-width columns starting at tablets and scaling to large extra desktops:

    ```html
    <div class="row">
        <div class="col-sm-4">.col-sm-4</div>
        <div class="col-sm-8">.col-sm-8</div>
    </div>
    ```

    [Try It Yourself](<https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_grid_ex2&stacked=h>)

</details>

# Bootstrap 5 Text/Typography

<details>
  <summary>click to expand</summary>

## Bootstrap 5 Default Settings

- Bootstrap 5 uses a default `font-size` of `1rem` (`16px` by default), and its `line-height` is `1.5`.

- In addition, all `<p>` elements have `margin-top: 0` and `margin-bottom: 1rem` (`16px` by default).

## `<h1>` - `<h6>`

- Bootstrap 5 styles HTML headings (`<h1>` to `<h6>`)  with a bolder `font-weight` and a responsive `font-size`.

- You can also use .h1 to .h6 classes on other elements to make them behave as headings if you want:

    ```html
    <p class="h1">h1 Bootstrap heading</p>
    <p class="h2">h2 Bootstrap heading</p>
    <p class="h3">h3 Bootstrap heading</p>
    <p class="h4">h4 Bootstrap heading</p>
    <p class="h5">h5 Bootstrap heading</p>
    <p class="h6">h6 Bootstrap heading</p>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_hn2&stacked=h)

## Display Headings

- Display headings are used to stand out more than normal headings (larger `font-size` and lighter `font-weight`), and there are six classes to choose from: `.display-1` to `.display-6`:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_display&stacked=h)

## `<small>`

- In Bootstrap 5 the HTML `<small>` element (and the `.small` class) is used to create a smaller, secondary text in any heading:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_small&stacked=h)

## `<mark>`

- Bootstrap 5 will style `<mark>` and `.mark` with a yellow background color and some padding:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_mark&stacked=h)

## `<abbr>`

- Bootstrap 5 will style the HTML `<abbr>` element with a dotted border bottom and a cursor with question mark on hover:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_abbr&stacked=h)

## `<blockquote>`

- Add the `.blockquote` class to a `<blockquote>` when quoting blocks of content from another source. And when naming a source, like "from WWF's website", use the `.blockquote-footer` class:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_blockquote&stacked=h)

## `<dl>`

- Bootstrap 5 will style the HTML `<dl>` element in the following way:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_dl&stacked=h)

## `<code>`

- Bootstrap 5 will style the HTML `<code>` element in the following way:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_code&stacked=h)

## `<kbd>`

- Bootstrap 5 will style the HTML `<kbd>` element in the following way:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_kbd&stacked=h)

## `<pre>`

- Bootstrap 5 will style the HTML `<pre>` element in the following way:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_pre&stacked=h)

## More Typography Classes

- The Bootstrap 5 classes below can be added to style HTML elements further:

|Class|Description|Example|
|---|---|:---:|
|`.lead`|Makes a paragraph stand out|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_txt_lead&amp;stacked=h)|
|`.text-start`|Indicates left-aligned text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-left&amp;stacked=h)|
|`.text-break`|Prevents long text from breaking layout|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-break)|
|`.text-center`|Indicates center-aligned text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-left&amp;stacked=h)|
|`.text-decoration`|none Removes the underline from a link|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_txt_decoration&amp;stacked=h)|
|`.text-end`|Indicates right-aligned text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-left&amp;stacked=h)|
|`.text-nowrap`|Indicates no wrap text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-left&amp;stacked=h)|
|`.text-lowercase`|Indicates lowercased text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-lowercase&amp;stacked=h)|
|`.text-uppercase`|Indicates uppercased text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-lowercase&amp;stacked=h)|
|`.text-capitalize`|Indicates capitalized text|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_text-lowercase&amp;stacked=h)|
|`.initialism`|Displays the text inside an `<abbr>` element in a slightly smaller font size|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_txt_abbr2&amp;stacked=h)|
|`.list-unstyled`|Removes the default list-style and left margin on list items (works on both `<ul>` and `<ol>`). This class only applies to immediate children list items (to remove the default list-style from any nested lists, apply this class to any nested lists as well)|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_txt_list-unstyled&amp;stacked=h)|
|`.list-inline`|Places all list items on a single line (used together with .list-inline-item on each `<li>` elements)|[Try It](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_ref_txt_list-inline&amp;stacked=h)|

## Text Colors

- Bootstrap 5 has some contextual classes that can be used to provide "meaning through colors".

- The classes for text colors are: `.text-muted`, `.text-primary`, `.text-success`, `.text-info`, `.text-warning`, `.text-danger`, `.text-secondary`, `.text-white`, `.text-dark`, `.text-body` (default body color/often black) and `.text-light`:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_colors&stacked=h)

- You can also add `50% opacity` for black or white text with the `.text-black-50` or `.text-white-50` classes:

    [Try It Yourself](<https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_colors_opacity&stacked=h>)

## Background Colors

- The classes for background colors are: `.bg-primary`, `.bg-success`, `.bg-info`, `.bg-warning`, `.bg-danger`, `.bg-secondary`, `.bg-dark` and `.bg-light`.

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_bgcolors&stacked=h)

- The `.bg-color` classes above does not work well with text, or at least then you have to specify a proper `.text-color` class to get the right text color for each background.

- However, you can use the `.text-bg-color` classes and Bootstrap will automatically handle the appropriate text color for each background color:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_txt_bgcolors2&stacked=h)

</details>

# Bootstrap 5 Tables

<details>
  <summary>click to expand</summary>

## Basic Table

- A basic Bootstrap 5 table has a light padding and horizontal dividers.

- The `.table` class adds basic styling to a table:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_basic&stacked=h)

## Striped Rows

- The `.table-striped` class adds zebra-stripes to a table:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_striped&stacked=h)

## Bordered Table

- The `.table-bordered` class adds borders on all sides of the table and cells:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_bordered&stacked=h)

## Hover Rows

- The `.table-hover` class adds a hover effect (grey background color) on table rows:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_hover&stacked=h)

## Black/Dark Table

- The `.table-dark` class adds a black background to the table:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_dark&stacked=h)

## Dark Striped Table

- Combine `.table-dark` and `.table-striped` to create a dark, striped table:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_dark_striped&stacked=h)

## Hoverable Dark Table

- The `.table-hover` class adds a hover effect (grey background color) on table rows:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_dark_hover&stacked=h)

## Borderless Table

- The `.table-borderless` class removes borders from the table:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_borderless&stacked=h)

## Contextual Classes

- Contextual classes can be used to color the whole table (`<table>`),  the table rows (`<tr>`) or table cells (`<td>`).

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_contextual&stacked=h)

- The contextual classes that can be used are:

    |Class|Description|
    |:---:|---|
    |`.table-primary`|Blue: Indicates an important action|
    |`.table-success`|Green: Indicates a successful or positive action|
    |`.table-danger`|Red: Indicates a dangerous or potentially negative action|
    |`.table-info`|Light blue: Indicates a neutral informative change or action|
    |`.table-warning`|Orange: Indicates a warning that might need attention|
    |`.table-active`|Grey: Applies the hover color to the table row or table cell|
    |`.table-secondary`|Grey: Indicates a slightly less important action|
    |`.table-light`|Light grey table or table row background|
    |`.table-dark`|Dark grey table or table row background|

## Table Head Colors

- You can also use any of the contextual classes to only add a background color to the table header:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_head&stacked=h)

## Small table

- The `.table-sm` class makes the table smaller by cutting cell padding in half:

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_sm&stacked=h)

## Responsive Tables

- The `.table-responsive` class adds a scrollbar to the table when needed (when it is too big horizontally):

    ```html
    <div class="table-responsive">
        <table class="table">
            ...
        </table>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_table_responsive)

- You can also decide when the table should get a scrollbar, depending on the screen width:

    |Class|Screen width|
    |:---:|:---:|
    |`.table-responsive-sm`|`< 576px`|
    |`.table-responsive-md`|`< 768px`|
    |`.table-responsive-lg`|`< 992px`|
    |`.table-responsive-xl`|`< 1200px`|
    |`.table-responsive-xxl`|`< 1400px`|

- Example

    ```html
    <div class="table-responsive-sm">
        <table class="table">
            ...
        </table>
    </div>
    ```

</details>

# Bootstrap 5 Images

<details>
  <summary>click to expand</summary>

## Image Shapes

### Rounded Corners

- The `.rounded` class adds rounded corners to an image:

    ```html
    <img src="cinqueterre.jpg" class="rounded" alt="Cinque Terre">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_img_rounded&stacked=h)

### Circle

- The `.rounded-circle` class shapes the image to a circle:

    ```html
    <img src="cinqueterre.jpg" class="rounded-circle" alt="Cinque Terre">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_img_circle&stacked=h)

### Thumbnail

- The `.img-thumbnail` class shapes the image to a thumbnail (bordered):

    ```html
    <img src="cinqueterre.jpg" class="img-thumbnail" alt="Cinque Terre">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_img_thumbnail&stacked=h)

## Aligning Images

- Float an image to the left with the `.float-start` class or to the right with `.float-end`:

    ```html
    <img src="paris.jpg" class="float-start">
    <img src="paris.jpg" class="float-end">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_img_align&stacked=h)

## Centered Image

- Center an image by adding the utility classes `.mx-auto` (margin:auto) and `.d-block` (display:block) to the image:

    ```html
    <img src="paris.jpg" class="mx-auto d-block">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_img_centered&stacked=h)

## Responsive Images

- Images come in all sizes. So do screens. Responsive images automatically adjust to fit the size of the screen.

- Create responsive images by adding an `.img-fluid` class to the `<img>` tag. The image will then scale nicely to the parent element.

- The `.img-fluid` class applies `max-width: 100%;` and `height: auto;` to the image:

    ```html
    <img class="img-fluid" src="ny.jpg" alt="New York">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_img_responsive&stacked=h)

</details>

# Bootstrap 5 Jumbotron

<details>
  <summary>click to expand</summary>

## Jumbotron

    ```html
    <div class="mt-4 p-5 bg-primary text-white rounded">
        <h1>Jumbotron Example</h1>
        <p>Lorem ipsum...</p>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_jumbotron&stacked=h)

</details>

# Bootstrap 5 Alerts

<details>
  <summary>click to expand</summary>

## Alerts

- Bootstrap 5 provides an easy way to create predefined alert messages:

    <img src="asset/bootstrap-5-alert.png" width="700"/>

- Alerts are created with the `.alert` class, followed by one of the contextual classes `.alert-success`, `.alert-info`, `.alert-warning`, `.alert-danger`, `.alert-primary`, `.alert-secondary`, `.alert-light` or `.alert-dark`.

    ```html
    <div class="alert alert-success">
        <strong>Success!</strong> Indicates a successful or positive action.
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_alerts&stacked=h)

## Alert Links

- Add the `.alert-link` class to any links inside the alert box to create "matching colored links":

    ```html
    <div class="alert alert-success">
        <strong>Success!</strong> You should <a href="#" class="alert-link">read this message</a>.
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_alerts_link&stacked=h)

## Closing Alerts

- To close the alert message, add a `.alert-dismissible` class to the alert container. Then add `class="btn-close"` and `data-bs-dismiss="alert"` to a link or a button element (when you click on this the alert box will disappear).

    ```html
    <div class="alert alert-success alert-dismissible">
        <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
        <strong>Success!</strong> This alert box could indicate a successful or positive action.
    </div>
    ```

## Animated Alerts

- The `.fade` and `.show` classes adds a fading effect when closing the alert message:

    ```html
    <div class="alert alert-danger alert-dismissible fade show">
    ```

</details>

# Bootstrap 5 Buttons

<details>
  <summary>click to expand</summary>

## Button Styles

- Bootstrap 5 provides different styles of buttons:

    ```html
    <button type="button" class="btn">Basic</button>
    <button type="button" class="btn btn-primary">Primary</button>
    <button type="button" class="btn btn-secondary">Secondary</button>
    <button type="button" class="btn btn-success">Success</button>
    <button type="button" class="btn btn-info">Info</button>
    <button type="button" class="btn btn-warning">Warning</button>
    <button type="button" class="btn btn-danger">Danger</button>
    <button type="button" class="btn btn-dark">Dark</button>
    <button type="button" class="btn btn-light">Light</button>
    <button type="button" class="btn btn-link">Link</button>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_styles&stacked=h)

- The button classes can be used on `<a>`, `<button>`, or `<input>` elements:

    ```html
    <a href="#" class="btn btn-success">Link Button</a>
    <button type="button" class="btn btn-success">Button</button>
    <input type="button" class="btn btn-success" value="Input Button">
    <input type="submit" class="btn btn-success" value="Submit Button">
    <input type="reset" class="btn btn-success" value="Reset Button">
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_elements&stacked=h)

## Button Outline

- Bootstrap 5 also provides eight outline/bordered buttons.

- Move the mouse over them to see an additional `hover` effect:

    ```html
    <button type="button" class="btn btn-outline-primary">Primary</button>
    <button type="button" class="btn btn-outline-secondary">Secondary</button>
    <button type="button" class="btn btn-outline-success">Success</button>
    <button type="button" class="btn btn-outline-info">Info</button>
    <button type="button" class="btn btn-outline-warning">Warning</button>
    <button type="button" class="btn btn-outline-danger">Danger</button>
    <button type="button" class="btn btn-outline-dark">Dark</button>
    <button type="button" class="btn btn-outline-light text-dark">Light</button>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_outline&stacked=h)

## Button Sizes

- Use the `.btn-lg` class for large buttons or `.btn-sm` class for small buttons:

    ```html
    <button type="button" class="btn btn-primary btn-lg">Large</button>
    <button type="button" class="btn btn-primary">Default</button>
    <button type="button" class="btn btn-primary btn-sm">Small</button>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_sizes&stacked=h)

## Block Level Buttons

- To create a block level button that spans the entire width of the parent element, use the .d-grid "helper" class on the parent element:

    ```html
    <div class="d-grid">
        <button type="button" class="btn btn-primary btn-block">Full-Width Button</button>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_block&stacked=h)

- If you have many block-level buttons, you can control the space between them with the `.gap-*` class:

    ```html
    <div class="d-grid gap-3">
        <button type="button" class="btn btn-primary btn-block">Full-Width Button</button>
        <button type="button" class="btn btn-primary btn-block">Full-Width Button</button>
        <button type="button" class="btn btn-primary btn-block">Full-Width Button</button>
    </div>
    ```

## Active/Disabled Buttons

- A button can be set to an active (appear pressed) or a disabled (unclickable) state:

- The class `.active` makes a button appear pressed, and the `disabled` attribute makes a button unclickable. Note that `<a>` elements do not support the disabled attribute and must therefore use the `.disabled` class to make it visually appear disabled.

    ```html
    <button type="button" class="btn btn-primary active">Active Primary</button>
    <button type="button" class="btn btn-primary" disabled>Disabled Primary</button>
    <a href="#" class="btn btn-primary disabled">Disabled Link</a>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_active&stacked=h)

## Spinner Buttons

- You can also add `spinners` to a button, which you will learn more about in our [BS5 Spinners Tutorial](https://www.w3schools.com/bootstrap5/bootstrap_spinners.php):

    ```html
    <button class="btn btn-primary">
        <span class="spinner-border spinner-border-sm"></span>
    </button>

    <button class="btn btn-primary">
        <span class="spinner-border spinner-border-sm"></span>
        Loading..
    </button>

    <button class="btn btn-primary" disabled>
        <span class="spinner-border spinner-border-sm"></span>
        Loading..
    </button>

    <button class="btn btn-primary" disabled>
        <span class="spinner-grow spinner-grow-sm"></span>
        Loading..
    </button>
    ```

</details>

# Bootstrap 5 Button Groups

<details>
  <summary>click to expand</summary>

## Button Groups

- Bootstrap 5 allows you to group a series of buttons together (on a single line) in a button group:

- Use a `<div>` element with class `.btn-group` to create a button group:

    ```html
    <div class="btn-group">
        <button type="button" class="btn btn-primary">Apple</button>
        <button type="button" class="btn btn-primary">Samsung</button>
        <button type="button" class="btn btn-primary">Sony</button>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_group&stacked=h)

- Tip: Instead of applying button sizes to every button in a group, use class `.btn-group-lg` for a large button group or the `.btn-group-sm` for a small button group:

    ```html
    <div class="btn-group btn-group-lg">
        <button type="button" class="btn btn-primary">Apple</button>
        <button type="button" class="btn btn-primary">Samsung</button>
        <button type="button" class="btn btn-primary">Sony</button>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_group_size&stacked=h)

## Vertical Button Groups

- Bootstrap 5 also supports vertical button groups:

- Use the class `.btn-group-vertical` to create a vertical button group:

    ```html
    <div class="btn-group-vertical">
        <button type="button" class="btn btn-primary">Apple</button>
        <button type="button" class="btn btn-primary">Samsung</button>
        <button type="button" class="btn btn-primary">Sony</button>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_group_v&stacked=h)

## Button Groups Side by Side

- Button groups are `inline` by default, which makes them appear side by side when you have multiple groups:

    ```html
    <div class="btn-group">
        <button type="button" class="btn btn-primary">Apple</button>
        <button type="button" class="btn btn-primary">Samsung</button>
        <button type="button" class="btn btn-primary">Sony</button>
    </div>

    <div class="btn-group">
        <button type="button" class="btn btn-primary">BMW</button>
        <button type="button" class="btn btn-primary">Mercedes</button>
        <button type="button" class="btn btn-primary">Volvo</button>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_group_inline&stacked=h)

## Nesting Button Groups & Dropdown Menus

- Nest button groups to create dropdown menus (you will learn more about dropdowns in a later chapter):

    ```html
    <div class="btn-group">
        <button type="button" class="btn btn-primary">Apple</button>
        <button type="button" class="btn btn-primary">Samsung</button>
        <div class="btn-group">
            <button type="button" class="btn btn-primary dropdown-toggle" data-bs-toggle="dropdown">Sony</button>
            <div class="dropdown-menu">
                <a class="dropdown-item" href="#">Tablet</a>
                <a class="dropdown-item" href="#">Smartphone</a>
            </div>
        </div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_button_group_dropdown&stacked=h)

</details>

# Bootstrap 5 Badges

<details>
  <summary>click to expand</summary>

## Badges

- Badges are used to add additional information to any content:

- Use the `.badge` class together with a contextual class (like `.bg-secondary`) within `<span>` elements to create rectangular badges. Note that badges scale to match the size of the parent element (if any):

    ```html
    <h1>Example heading <span class="badge bg-secondary">New</span></h1>
    <h2>Example heading <span class="badge bg-secondary">New</span></h2>
    <h3>Example heading <span class="badge bg-secondary">New</span></h3>
    <h4>Example heading <span class="badge bg-secondary">New</span></h4>
    <h5>Example heading <span class="badge bg-secondary">New</span></h5>
    <h6>Example heading <span class="badge bg-secondary">New</span></h6>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_badges&stacked=h)

## Contextual Badges

- Use any of the contextual classes (`.bg-*`) to change the color of a badge:

    ```html
    <span class="badge bg-primary">Primary</span>
    <span class="badge bg-secondary">Secondary</span>
    <span class="badge bg-success">Success</span>
    <span class="badge bg-danger">Danger</span>
    <span class="badge bg-warning">Warning</span>
    <span class="badge bg-info">Info</span>
    <span class="badge bg-light">Light</span>
    <span class="badge bg-dark">Dark</span>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_badges2&stacked=h)

## Pill Badges

- Use the `.rounded-pill` class to make the badges more round:

    ```html
    <span class="badge rounded-pill bg-primary">Primary</span>
    <span class="badge rounded-pill bg-secondary">Secondary</span>
    <span class="badge rounded-pill bg-success">Success</span>
    <span class="badge rounded-pill bg-danger">Danger</span>
    <span class="badge rounded-pill bg-warning">Warning</span>
    <span class="badge rounded-pill bg-info">Info</span>
    <span class="badge rounded-pill bg-light">Light</span>
    <span class="badge rounded-pill bg-dark">Dark</span>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_badges_pills&stacked=h)

## Badge inside an Element

- An example of using a badge inside a button:

    ```html
    <button type="button" class="btn btn-primary">
        Messages <span class="badge bg-danger">4</span>
    </button>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_badges_button&stacked=h)

</details>

# Bootstrap 5 Progress Bars

<details>
  <summary>click to expand</summary>

## Basic Progress Bar

- A progress bar can be used to show how far a user is in a process.

- To create a default progress bar, add a `.progress` class to a container element and add the `.progress-bar` class to its child element. Use the CSS width property to set the width of the progress bar:

    ```html
    <div class="progress">
        <div class="progress-bar" style="width:70%"></div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar1&stacked=h)

## Progress Bar Height

- The height of the progress bar is `1rem` (usually `16px`) by default. Use the CSS height property to change it:

    ```html
    <div class="progress" style="height:20px">
        <div class="progress-bar" style="width:40%;"></div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar7&stacked=h)

## Progress Bar Labels

- Add text inside the progress bar to show the visible percentage:

    ```html
    <div class="progress">
        <div class="progress-bar" style="width:70%">70%</div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar2&stacked=h)

## Colored Progress Bars

- By default, the progress bar is blue (primary). Use any of the contextual background classes to change its color:

    ```html
    <!-- Blue -->
    <div class="progress">
        <div class="progress-bar" style="width:10%"></div>
    </div>

    <!-- Green -->
    <div class="progress">
        <div class="progress-bar bg-success" style="width:20%"></div>
    </div>

    <!-- Turquoise -->
    <div class="progress">
        <div class="progress-bar bg-info" style="width:30%"></div>
    </div>

    <!-- Orange -->
    <div class="progress">
        <div class="progress-bar bg-warning" style="width:40%"></div>
    </div>

    <!-- Red -->
    <div class="progress">
        <div class="progress-bar bg-danger" style="width:50%"></div>
    </div>

    <!-- White -->
    <div class="progress border">
        <div class="progress-bar bg-white" style="width:60%"></div>
    </div>

    <!-- Grey -->
    <div class="progress">
        <div class="progress-bar bg-secondary" style="width:70%"></div>
    </div>

    <!-- Light Grey -->
    <div class="progress border">
        <div class="progress-bar bg-light" style="width:80%"></div>
    </div>

    <!-- Dark Grey -->
    <div class="progress">
        <div class="progress-bar bg-dark" style="width:90%"></div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar3&stacked=h)

## Striped Progress Bars

- Use the `.progress-bar-striped` class to add stripes to the progress bars:

    ```html
    <div class="progress">
        <div class="progress-bar progress-bar-striped" style="width:40%"></div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar4&stacked=h)

## Animated Progress Bar

- Add the `.progress-bar-animated` class to animate the progress bar:

    ```html
    <div class="progress">
        <div class="progress-bar progress-bar-striped progress-bar-animated" style="width:40%"></div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar5&stacked=h)

## Multiple Progress Bars

- Progress bars can also be stacked:

    ```html
    <div class="progress">
        <div class="progress-bar bg-success" style="width:40%">
            Free Space
        </div>
        <div class="progress-bar bg-warning" style="width:10%">
            Warning
        </div>
        <div class="progress-bar bg-danger" style="width:20%">
            Danger
        </div>
    </div>
    ```

    [Try It Yourself](https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_progressbar6&stacked=h)

</details>

<!--
# Bootstrap 5 Items

<details>
  <summary>click to expand</summary>

</details>
-->