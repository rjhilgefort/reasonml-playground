/* Note To Self: 
  - Turn off ligatures.
  - Record macros for changing true to false and vice versa (for condLog).
  - Show code hints throughout.
*/
let setctionBreak = (log: 'a => unit, section: string): unit => {
  let decoratedSection = {j|--- $section ---|j};
  let border = decoratedSection |> String.length |> String.make(_, '-');

  log("\n\n\n");
  log(border);
  log(decoratedSection);
  log(border);
  ();
};





/**********************************************************
  * Loops: https://reasonml.github.io/docs/en/imperative-loops
    - A selling point of ReasonML is that it isn't dogmatic, yet prefers FP style.
  * Mutating: https://reasonml.github.io/docs/en/mutation
    - Everything is immutable by default and you have to say when you want to mutate with `ref`.
    - let === const
    - `ref` isn't a keyword- it's just a predefined record type that looks like this: `{ contents: 'foo }`
      The `:=` is a language feature that's just sugar for `bar.contents = "bar"`.
*/
let repeatFor = (times, toRepeat) => {
  let ret = ref("");
  for (_ in times downto 1) {
    ret := ret.contents ++ toRepeat;
  }
  ret.contents;
};
let repeat = repeatFor;

let repeatWhile = (times, toRepeat) => {
  let i = ref(times)
  let ret = ref("")
  while (i.contents > 0) {
    ret := ret.contents ++ toRepeat;
    i := i.contents - 1;
  }
  ret.contents;
};

Js.log(repeatFor(100, "\n"));
setctionBreak(Js.log, "Loops, Mutating")

Js.log(repeatFor(3, "for-"));
Js.log(repeatWhile(3, "while-"));






/**********************************************************
  * Currying
    - Everything is auto-curried by default.
  * Partial Applications
    - You can partially apply functions to get back a function wating for the remaining arguments.
  * Types
    - `'a` is a type variable. Here we're saying, we don't know what 'a is, but it must
    conform to the usage in the function. That means it must be compatible with `Js.log`.
    - `unit` is like `void`, but also not really. It's used to indicate that the
      function doesn't return anything.
    - Type inference is one of the best features of the language and this funcion doesn't
      require the explicit types.
*/
let condLog = (shouldLog: bool, message: 'a): unit => {
  if (shouldLog) {
    Js.log(message);
  };
};

let log = condLog(false);
log("This won't log because `log` is partially applied with `shouldLog = false`");

let log = condLog(false); // You can reassign let bindings but redefining them.
setctionBreak(log, "Currying, Partial Apps, Types");

log("Hello from Reason!");





/**********************************************************
  * Pervasives (Built-Ins)
    - This module is `open`ed in every file- which means you don't have to use the namespace.
  * Infix Operators
    - Just regular functions
  * Strings
    - Can do string templates like JS
  * Bucklescript / JS Functions
    - By using `JS.log` we're precluding ourselves from native compilation- must be 
      transpiled to JS with Bucklescript.
*/
let log = condLog(false);
setctionBreak(log, "Pervasives, Infix Operators");

log("foo" ++ "bar");
log((++)("foo", "bar"));
log(Pervasives.(++)("foo", "bar"))

let greeting = "foo";
log({j|Hello $greeting from `console.log` using string templates|j});
// Same as: `console.log(`Hello ${greeting} ...`)`

log @@ "You can use @@ when there is a function with a single argument";

// print_string("Hello, using OCaml `print_string`!\n");





/**********************************************************
  * Expressions, Blocks
    - Almost everything is an expression and returns a value. 
  * Implicit returns
    - The last expression is always returned, there is no `return` keyword.
  * Switch Expressions
    - We'll see more and more complicated use cases throughout the rest of this.
*/
let log = condLog(false);
setctionBreak(log, "Expressions, Blocks, Implicit Returns, Switches");

let ifElseLet = if (true) {
  "value is true";
} else {
  // This is an error, must have consistent return.
  // 5;
  "value is false";
};

log(ifElseLet);

let a = "I'll be unchanged";
let blockExpression = {
  let a = "a";
  let b = "b";
  {j|$a and $b|j};
};

log(a);
log(blockExpression);

let switchExpressionParam: string = "marco";
let switchExpression = switch switchExpressionParam {
  | "marco" => "polo"
  | _ => "Unnecessary catch all handler" /* You can use `_` when you don't care about a param- or `() =>` */
};

log(switchExpression);





/**********************************************************
  Pipe operator
*/
let log = condLog(false);
setctionBreak(log, "Expressions, Blocks, Implicit Returns, Switches");

let doubleInt = (x) => {
  x * 2;
};
let doubleFloat = x => x *. 2.;

5.2 |> doubleFloat |> string_of_float |> log;
// Same as: log(string_of_float(doubleFloat(5.2)))

8 
|> doubleInt 
|> float_of_int 
|> (x => x +. 1.7)
|> doubleFloat 
|> string_of_float
|> log;






/**********************************************************
  * Function Composition 
    - ... As opposed to value piping
    - Using Rationale: https://github.com/jonlaing/rationale
  * Modules
    - `open`ing module just removes the namespace
*/
let log = condLog(false);
setctionBreak(log, "Function Composition, Modules");

open Rationale.Function;

type doubleStringT = string => string;
let doubleString: doubleStringT = string_of_int <|| doubleInt <|| int_of_string;
// let doubleString: doubleStringT = x => x |> int_of_string |> doubleInt |> string_of_int;
// const doubleString = x => string_of_int(doubleInt(int_of_string(x)))
// const doubleString = R.compose(string_of_int, doubleInt, int_of_string)
// const doubleString = _.flowLeft(string_of_int, doubleInt, int_of_string)

"5" |> doubleString |> log;
(log <|| doubleString)("5");






/**********************************************************
  * Variants
    - https://reasonml.github.io/docs/en/variant
*/
let log = condLog(false);
setctionBreak(log, "Variants");

type coinT = | BTC | ETH | LTC;

let string_of_coin = (x: coinT): string => 
  switch x {
  | BTC => "`x` was BTC"
  | ETH => "`x` was ETH"
  | LTC => "`x` was LTC"
  // Reason knows I've covered all the cases in the variant and doesn't require a default case
  };

// They aren't types, can be used as values like strings, booleans, etc
let btc = BTC;
let eth = ETH;
let ltc = LTC;

btc |> string_of_coin |> log;
eth |> string_of_coin |> log;






/**********************************************************
  * Pattern Matching
    - https://reasonml.github.io/docs/en/pattern-matching
  * Variant Constructor Args
*/
let log = condLog(false);
setctionBreak(log, "Pattern Matching, Variant Constructor Args");

type eitherT = 
  | Left(string)
  | Right(int, int);

let string_of_either = (data) =>
  switch data {
  | Left(message) => {j|Left($message)|j}
  | Right(0, _) => {j|Right where the first was 0|j}
  | Right(x, y) => {j|Right($x, $y)|j}
  };

let logEither = log <|| string_of_either;

logEither(Left("Danger Will Robinson"));
logEither(Right(0, 7));
Right(52, 104) |> logEither;








/**********************************************************
  * Record Type
    - Type inference knows `rob` and `ally` are a person by their shape.
*/
let log = condLog(false);
setctionBreak(log, "Record Type");

type person = {
  name: string,
  age: int,
};

let rob = {
  name: "Rob",
  age: 31,
};
let ally = {
  name: "Ally",
  age: 30,
};

let getPersonInfo = data =>
  switch data {
  | ({ name: "Rob" } | { name: "Ally" }) as x => {
    let { name, age } = x;
    {j|"$name" is $age years old|j}
  }
  | (x) => "Some other person with the name: \"" ++ x.name ++ "\" is " ++ string_of_int(x.age) ++ " years old.";
  };

rob |> getPersonInfo |> log;
ally |> getPersonInfo |> log;
{ name: "Jerry", age: 82 } |> getPersonInfo |> log;






/**********************************************************
  * Function/Switch shorthand
    - Function must be unary
*/
let log = condLog(false);
setctionBreak(log, "Function/Switch Shorthand");

let getNameVerbose = data =>
  switch data {
  | { name: "Rob" } => "What's up Rob"
  | x => {j|I don't know you $x.name|j}
  };

let getNameShort = fun
  | { name: "Rob" } => "What's up Rob"
  | _ => {j|I don't know you|j};

rob |> getNameVerbose |> log;
ally |> getNameShort |> log;







/**********************************************************
  * Labeled Arguments
    - Think of the way you do destructured objects in JS as a way to provide args in whatever
      order and just pass them by name- the usage is similar.
    - ReasonReact does this exclusively.
  * Option Variant
    - https://reasonml.github.io/docs/en/null-undefined-option
    - There are no nulls or undefineds in the language.
*/
let log = condLog(false);
setctionBreak(log, "Labled Arguments, Option Variant");

/** 
 * `option` is built in and looks like this:
 * type option = | None | Some('a) 
 */

let string_of_option_int = fun
  | Some(x) => string_of_int(x)
  | None => "[None]";

let logOptionInt = log <|| string_of_option_int;

let findIndexValue = (~needle, ~haystack): option(int) => {
  switch haystack {
  | [||] => None
  | x => Some(Js.Array.findIndex(x => x == needle, x))
  };
}

let someArray = [|"foo", "bar", "baz"|];

findIndexValue("foo", someArray) |> logOptionInt;

findIndexValue(
  ~needle="baz", 
  ~haystack=someArray,
) |> logOptionInt;

findIndexValue(
  ~haystack=someArray,
  ~needle="baz"
) |> logOptionInt;

someArray |> (x) => findIndexValue(~needle="bar", ~haystack=x) |> logOptionInt;
someArray |> findIndexValue(~haystack=_, ~needle="bar") |> logOptionInt;
someArray |> findIndexValue("bar", _) |> logOptionInt;












/**********************************************************
  * Fast Piping 
    - `|.` and `->`
*/
let log = condLog(false);
setctionBreak(log, "Fast Pipe");

type kind = | Cat | Dog;
type animal = {
  kind: kind,
  name: string,
};

let speak = (animal, extra) => {
  switch animal {
  | { kind: Cat } as x => {j|Hi, I'm a Cat by the name of $x.name and I want to tell you about $extra!!|j}
  | { kind: Dog } as x => {j|I'm a smelly dog, I go by $x.name. Here's a thought about $extra.|j};
  | x => {j|WHAT ARE YOU!? $x.kind|j} /* Note that Reason is telling me I don't need this case */
  }
  |> log;
  animal;
}

let someCat = {
  kind: Cat,
  name: "pet1",
}
let someDog = {
  kind: Dog,
  name: "pet2",
}

// As long as I return the subject (`animal`) in my function, I can chain these "methods"
someCat -> speak("my paws") -> speak("my tail");

// This can feel like OOO and that's the intent of fast pipes AFAICT
// This is also useful when you are wrapping and working with existing JS
someDog->speak("poop");