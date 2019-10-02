
[@bs.module "./serviceWorker"]
external register_service_worker: unit => unit = "register";
[@bs.module "./serviceWorker"]
external unregister_service_worker: unit => unit = "unregister";
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:3000/graphql", ());

let client =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
let app =
 <ReasonApolloHooks.ApolloProvider client>
   <App />
 </ReasonApolloHooks.ApolloProvider>;

ReactDOMRe.hydrateToElementWithId(app, "root");
unregister_service_worker();
// ReactDOMRe.renderToElementWithId(<Component1 message="Hello! Click this text." />, "index1");

// ReactDOMRe.renderToElementWithId(<Component2 greeting="Hello!" />, "index2");
