open Rationale.Function;

Js.log("\n\n--------------------------------------------------------------------");
Js.log("Hello, BuckleScript and Reason!");
let greeting = "foo";
Js.log({j|Hello $greeting from `console.log` using string templates|j});

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