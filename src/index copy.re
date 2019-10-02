
[@bs.module "./registerServiceWorker"]
external registerServiceWorker: unit => unit = "register";

registerServiceWorker();


ReactDOMRe.hydrateToElementWithId(<App />, "root");
// import React from "react";
// import { hydrate, render } from "react-dom";
// import { register } from "register-service-worker";

// import App from "./App";

// let root = document.getElementById("root");
// if (root) {
//   hydrate(<App />, root);
//   if (process.env.NODE_ENV === "production") register("./service-worker.js");
// } else {
//   root = document.createElement("div");
//   root.id = "root";
//   document.body.appendChild(root);
//   render(<App />, root);
// }

// export default () => render(<App />, root);
