open Square;

let component = ReasonReact.statelessComponent "Board";

let make ::owner ::squares ::handleClick _children => {
  let renderSquare owner i =>
    <Square value=squares.(i) handleClick=(owner.ReasonReact.update (handleClick i)) />;
  {
    ...component,
    render: fun _self =>
      <div>
        <div className="board-row">
          (renderSquare owner 0)
          (renderSquare owner 1)
          (renderSquare owner 2)
        </div>
        <div className="board-row">
          (renderSquare owner 3)
          (renderSquare owner 4)
          (renderSquare owner 5)
        </div>
        <div className="board-row">
          (renderSquare owner 6)
          (renderSquare owner 7)
          (renderSquare owner 8)
        </div>
      </div>
  }
};
