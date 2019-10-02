[%bs.raw {|require('./App.scss')|}];

module QueryConfig = [%graphql {|
  query
    {
      nodeId
    },
|}];
module ClickQuery = ReasonApolloHooks.Query.Make(QueryConfig);

[@react.component]
let make = () => {
  let (numClicks, setNumClicks) = React.useState(() => 0);
  let (_simple, full) = ClickQuery.use();
  <div>
    {switch (full) {
     | {loading: true, data: None} => <p> {React.string("Loading...")} </p>
     | {data: Some(data)} =>
       <div>
         <button onClick={_ => setNumClicks(_ => numClicks + 1)}>
           {numClicks->string_of_int |> React.string}
           " clicks"->React.string
         </button>
         {switch (Js.Json.stringifyAny(data)) {
          | Some(s) => s->React.string
          | None => ""->React.string
          }}
       </div>
     | {error: Some(_)} => <p> {React.string("Error")} </p>
     | {error: None, data: None, loading: false} =>
       <p> {React.string("error")} </p>
     }}
  </div>;
};