open Square;

type state = {
  squares: array mark,
  xIsNext: bool
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

let component = ReasonReact.statefulComponent "Board";

let make _children => {
  let handleClick i _event {ReasonReact.state: state} => {
    let squares = state.squares;
    Js.log "Handle Started";
    if (calculateWinner squares != None || squares.(i) != None) {
      let r = ReasonReact.NoUpdate;
      Js.log "No update..";
      r
    } else {
      Js.log "Updating...";
      squares.(i) = state.xIsNext ? X : O;
      let r = ReasonReact.Update {squares, xIsNext: not state.xIsNext};
      Js.log "Updated";
      r
    }
  };
  let renderSquare self i => {
    let f = self.ReasonReact.update (handleClick i);
    let g = ();
    <Square value=self.ReasonReact.state.squares.(i) handleClick=f />
  };
  {
    ...component,
    initialState: fun () => {squares: Array.make 9 None, xIsNext: true},
    render: fun self => {
      let winner = calculateWinner self.state.squares;
      let status =
        winner == None ?
          "Next player: " ^ (self.state.xIsNext ? "X" : "O") : "Winner: " ^ string_of_mark winner;
      <div>
        <div> (status |> ReasonReact.stringToElement) </div>
        <div className="board-row">
          (renderSquare self 0)
          (renderSquare self 1)
          (renderSquare self 2)
        </div>
        <div className="board-row">
          (renderSquare self 3)
          (renderSquare self 4)
          (renderSquare self 5)
        </div>
        <div className="board-row">
          (renderSquare self 6)
          (renderSquare self 7)
          (renderSquare self 8)
        </div>
      </div>
    }
  }
};
