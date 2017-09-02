[%bs.raw {|require('./game.css')|}];

open Square;

type action =
  | HandleClick int
  | JumpToStep int;

type squares = array mark;

type state = {
  history: array squares,
  xIsNext: bool,
  stepNumber: int
};

let calculateWinner squares => {
  let lines = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6]
  ];
  let winningLine = {
    let winning =
      fun
      | [a, b, c] => squares.(a) == squares.(b) && squares.(b) == squares.(c)
      | _ => false;
    List.filter winning lines
  };
  switch winningLine {
  | [[a, ..._rest]] => squares.(a)
  | _ => None
  }
};

let handleClick i _event => HandleClick i;

let jumpToStep step _event => JumpToStep step;

let component = ReasonReact.reducerComponent "Game";

let make _children => {
  ...component,
  initialState: fun () => {history: [|Array.make 9 None|], xIsNext: true, stepNumber: 0},
  reducer: fun action state =>
    switch action {
    | HandleClick i =>
      let history = Array.sub state.history 0 (state.stepNumber + 1);
      let squares = Array.copy @@ history.(Array.length history - 1);
      if (calculateWinner squares != None || squares.(i) != None) {
        ReasonReact.NoUpdate
      } else {
        squares.(i) = state.xIsNext ? X : O;
        ReasonReact.Update {
          history: Array.append history [|squares|],
          xIsNext: not state.xIsNext,
          stepNumber: Array.length history
        }
      }
    | JumpToStep step => ReasonReact.Update {...state, stepNumber: step, xIsNext: step mod 2 == 0}
    },
  render: fun self => {
    let history = self.state.history;
    let current = history.(self.state.stepNumber);
    let winner = calculateWinner current;
    let moves =
      Array.mapi
        (
          fun move _step => {
            let desc = move > 0 ? "Move #" ^ string_of_int move : "Game start";
            <li key=(string_of_int move)>
              <a href="#" onClick=(self.ReasonReact.reduce (jumpToStep move))>
                (ReasonReact.stringToElement desc)
              </a>
            </li>
          }
        )
        history;
    let status =
      winner == None ?
        "Next player: " ^ (self.state.xIsNext ? "X" : "O") : "Winner: " ^ string_of_mark winner;
    <div className="game">
      <div className="game-board"> <Board owner=self squares=current handleClick /> </div>
      <div className="game-info">
        <div> (status |> ReasonReact.stringToElement) </div>
        <ol> (ReasonReact.arrayToElement moves) </ol>
      </div>
    </div>
  }
};
