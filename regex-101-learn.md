# [`Regex`](https://regexlearn.com/learn)

- Regular Expression

## Range 

- The period `.` allows selecting any character, including special characters and spaces.
- Character Sets `[abc]`.
- Negated Character Sets `[^abc]`.
- Letter Range `[a-z]`
- Number Range `[0-9]`
 
## Repetition

- Asterisk `*`: We put an asterisk `*` after a character to indicate that the character may either **not match** at all or can **match many times**.
- Plus Sign `+`: To indicate that a character can occur **one or more times**, we put a plus sign `+` after a character.
- Question Mark `?`: To indicate that a character is **optional**, we put a `?` question mark after a character.
- To express a certain **number of occurrences** of a character, we write curly braces `{n}` along with how many times we want it to occur at the end. `{n,}` for **at least how many times** we want it to occur. `{x,y}` to express the occurrence of a character in a certain number range.

## Grouping

- We can **group** an expression and use these groups to **reference** or **enforce** some rules. To group an expression, we enclose `()` in parentheses.
- Referencing a Group: with text: `ha-ha,haa-haa` and pattern `(ha)-\1,(haa)-\2` - The first group is used by writing `\1` to **avoid rewriting**. Here 1 denotes the order of grouping. Type `\2` at the end of the expression to refer to the second group.
- Parentheses `(?: )`: Non-capturing Grouping - You **can group** an expression and ensure that it is **not captured by references**.
 
## Miscellaneous

- Pipe Character `|` : Alternation - It allows to specify that an expression can be in **different expressions**. Thus, all possible statements are written separated by the pipe sign `|`. This differs from charset `[abc]`, charsets operate at the character level. Alternatives are at the **expression level**.
- Escape Character `\`: There are special characters that we use when writing regex. `{}[]/\+*.$^|?` Before we can **select** these characters themselves, we need to use an escape character `\`.
- Caret Sign `^`: Selecting by Line Start.
- Dollar Sign `$`: Selecting by End of Line.
- Word Character `\w`: **Letter**, **Number** and **Underscore**.
- Except Word Character `\W`: is used to find characters **other than** letters, numbers, and underscores.
- Number Character `\d`: is used to find only **number characters**.
- Except Number Character `\D`: is used to find **non-numeric characters**.
- Space Character `\s`: is used to find **only space characters**.
- Except Space Character `\S`: is used to find **non-space characters**.
 
## Lookarounds

- Positive Lookahead `(?=)`: Example `\d+(?=PM)` - select the numberical values that **have** `PM` **after them**.
- Negative Lookahead `(?!)`: Example `\d+(?!PM)` - select only the numerical values that do **not have** `PM` **after them**.
- Positive Lookbehind `(?<=)`: Example `(?<=\$)\d+` - select only the number values that **preceded** by `$`.
- Negative Lookbehind `(?<!)`: Example `(?<!\$)\d+` - select only the number values that **not preceded** by `$`.

## Flags
Flags change the output of the expression. That's why flags are also called `modifiers`.

- Global Flag: The `global` flag causes the expression to **select all matches**. If **not used** it will only select the **first match**. *Example `/\w+\.com/g`*.
- Multiline Flag: Regex sees all text as one line. But we use the `multiline` flag to handle **each line separately**. In this way, the expressions we write according to the end of the linework separately for each line. *Example `/\w+\.com$/gm`*.
- Case-insensitive Flag: In order to **remove the case-sensitiveness** of the expression we have written, we must activate the case-insensitive flag. *Example `/\w+\.com$/gmi`*.
- Greedy Matching: Regex does a greedy match **by default**. This means that the matchmaking will be as long as possible. Check out the example below. It refers to any match that ends in `r` and can be any character preceded by it. But it does not stop at the first letter `r`. *Example: text `ber beer beeer beeeer` and pattern `/.*r/`*.
- Lazy Matching: Lazy matchmaking, unlike greedy matching, **stops at the first matching**. For example, in the example below, add a `?` after `*` to find the first match that ends with the letter `r` and is preceded by any character. It means that this match will stop at the first letter `r`. *Example: text `ber beer beeer beeeer` and pattern `/.*?r/`*.
