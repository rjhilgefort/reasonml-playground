/* Note To Self: Turn off ligatures */

let condLog = (shouldLog: bool, message: 'a): unit => {
  if (shouldLog) {
    Js.log(message);
  };
};

/**********************************************************
  Strings, Logging
*/
let log = condLog(false);

/* let === const */
let greeting = "foo";

Js.log("\n\n\n\n\n--------------------------------------------------------------------");
log("Hello, BuckleScript and Reason!");

log("foo" ++ "bar");
log((++)("foo", "bar"));
log(Pervasives.(++)("foo", "bar"))

log({j|Hello $greeting from `console.log` using string templates|j});

log @@ "You can use @@ when there is a function with a single argument";

/* print_string("Hello, using OCaml `print_string`!\n"); */

/**********************************************************
  Expressions, Implicit Returns, Blocks
*/
let log = condLog(false);

let ifElseLet = if (true) {
  "value is true";
} else {
  /* This is an error, must have consistent return. */
  /* 5; */
  "value is false";
};

log(ifElseLet);

let a = "file scope 'a'";
let blockExpression = {
  let a = "a";
  let b = "b";
  {j|$a and $b|j}
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
  Functionas and Piping
*/
let log = condLog(false);

let doubleInt = (x) => {
  x * 2
};
let doubleFloat = x => x *. 2.;

5.2 |> doubleFloat |> log;

8 
|> doubleInt 
|> float_of_int 
|> (x => x +. 1.7)
|> doubleFloat 
|> log;

/**********************************************************
  Function Composition (As opposed to value piping)
  https://github.com/jonlaing/rationale
*/
let log = condLog(false);

open Rationale.Function;
type doubleStringT = string => string;
let doubleString: doubleStringT = string_of_int <|| doubleInt <|| int_of_string;
/* const doubleString = R.compose(string_of_int, doubleInt, int_of_string) */
/* const doubleString = _.flowLeft(string_of_int, doubleInt, int_of_string) */

(log <|| doubleString)("5");

/**********************************************************
  Variants
  https://reasonml.github.io/docs/en/variant
*/
let log = condLog(false);
type coinT = | BTC | ETH | LTC;

let btc = BTC;
let eth = ETH;
let ltc = LTC;

let coinToString = (x: coinT): string => 
  switch x {
  | BTC => "`x` was BTC"
  | ETH => "`x` was ETH"
  | LTC => "`x` was LTC"
  };

btc |> coinToString |> log;
eth |> coinToString |> log;

/**********************************************************
  Pattern Matching
  https://reasonml.github.io/docs/en/pattern-matching
*/
let log = condLog(false);

type eitherT = 
  | Left(string)
  | Right(int, int);

let eitherToString = (data) =>
  switch data {
  | Left(message) => {j|Left($message)|j}
  | Right(0, _) => {j|Right where the first was 0|j}
  | Right(x, y) => {j|Right($x, $y)|j}
  };

let eitherToStringLog = log <|| eitherToString;
eitherToStringLog(Left("Danger Will Robinson"));
eitherToStringLog(Right(0, 7));
Right(52, 104) |> eitherToStringLog;

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
  Function/Switch shorthand
*/
let log = condLog(false);

let getNameVerbose = data =>
  switch data {
  | { name: "Rob" } => "What's up Rob"
  | x => {j|I don't know you $x.name|j}
  };

let getNameShort = fun
  | { name: "Rob" } => "What's up Rob"
  | x => {j|I don't know you $x.name|j};

rob |> getNameVerbose |> log;
ally |> getNameShort |> log;

/**********************************************************
  Labled Arguments
*/
let log = condLog(false);

/* type option = | None | Some('a) */

let findIndexValue = (~needle, ~haystack): option(int) => {
  switch haystack {
  | [||] => None
  | x => Some(Js.Array.findIndex(x => x == needle, x))
  };
}

let someArray = [|"foo", "bar", "baz"|];

findIndexValue("foo", someArray) |> log;

findIndexValue(
  ~needle="baz", 
  ~haystack=someArray,
) |> log;

findIndexValue(
  ~haystack=someArray,
  ~needle="baz"
) |> log;

someArray |> (x) => findIndexValue(~needle="bar", ~haystack=x) |> log;
someArray |> findIndexValue(~haystack=_, ~needle="bar") |> log;
someArray |> findIndexValue("bar", _) |> log;

/**********************************************************
  Fast Piping (`|.` and `->`)
*/
let log = condLog(false);

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

/* As long as I return the subject (`animal`) in my function, I can chain these "methods" */
someCat -> speak("my paws") -> speak("my tail");

/* This can feel like OOO and that's the intent of fast pipes AFAIK */
/* This is also useful when you are wrapping and working with existing JS */
someDog->speak("poop");