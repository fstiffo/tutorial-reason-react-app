[%bs.raw {|require('./game.css')|}];

external log : string => unit = "console.log" [@@bs.val];

let component = ReasonReact.statelessComponent "Game";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="game">
      <div className="game-board"> <Board /> </div>
      <div className="game-info"> <div /* TODO*/ /> <ol /* TODO */ /> </div>
    </div>
};
