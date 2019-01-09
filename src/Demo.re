/* https://github.com/jonlaing/rationale */
open Rationale.Function;

Js.log("\n\n--------------------------------------------------------------------");
Js.log("Hello, BuckleScript and Reason!");
let greeting = "foo";
Js.log({j|Hello $greeting from `console.log` using string templates|j});

let log = Js.log;

print_string("Hello, using OCaml `print_string`!\n");

let doubleInt = x => x * 2;
let doubleFloat = x => x *. 2.;

8 
|> doubleInt 
|> Js.log;

type doubleStringT = string => string;
let doubleString: doubleStringT =
  string_of_int <|| doubleInt <|| int_of_string;

(Js.log <|| doubleString)("5");

/**********************************************************
  Variants
  https://reasonml.github.io/docs/en/variant
*/
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

btc |> coinToString |> Js.log;

/**********************************************************
  Pattern Matching
  https://reasonml.github.io/docs/en/pattern-matching
*/
type eitherT = 
  | Left(string)
  | Right(int, int);

let eitherToString = (data) =>
  switch data {
  | Left(message) => {j|Left($message)|j}
  | Right(0, _) => {j|Right where the first was 0|j}
  | Right(x, y) => {j|Right($x, $y)|j}
  };

let eitherToStringLog = Js.log <|| eitherToString;
eitherToStringLog(Left("Danger Will Robinson"));
eitherToStringLog(Right(0, 7));
eitherToStringLog(Right(52, 104));

type person = {
  name: string,
  age: int,
};

let rob = {
  name: "Rob",
  age: 31,
}

let ally = {
  name: "Ally",
  age: 30,
}



let getPersonInfo = (data) =>
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