external alert : string => unit = "alert" [@@bs.val];

type mark =
  | None
  | X
  | O;

let string_of_mark =
  fun
  | None => ""
  | X => "X"
  | O => "O";

let component = ReasonReact.statelessComponent "Square";

let make ::value ::handleClick _children => {
  ...component,
  render: fun _self =>
    <button className="square" onClick=handleClick>
      (string_of_mark value |> ReasonReact.stringToElement)
    </button>
};
