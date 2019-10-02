import { promisify } from "util";

import express from "express";
import compression from "compression";
import { ApolloServer } from "apollo-server-express";

import pg from "pg";
import { makePluginHook } from "postgraphile";
// @ts-ignore
import { makeSchemaAndPlugin } from "postgraphile-apollo-server";

const PORT = process.env.PORT ? parseInt(process.env.PORT, 10) : 3000;
const DB = process.env.DATABASE_URL || "postgres://postgres:postgres@localhost";

async function main() {
  const pool = new pg.Pool({ connectionString: DB });
  const { schema, plugin } = await makeSchemaAndPlugin(pool, "public", {
    pluginHook: makePluginHook([require("@graphile/pg-pubsub")]),
    subscriptions: true,
    simpleSubscriptions: true,
    appendPlugins: [
      require("@graphile-contrib/pg-many-to-many"),
      require("postgraphile-plugin-connection-filter"),
      require("postgraphile-plugin-nested-mutations")
    ]
  });
  const server = new ApolloServer({ schema, plugins: [plugin] });
  const app = express();
  app.disable("x-powered-by");
  app.use(compression());
  app.use(express.static("./dist/public"));
  server.applyMiddleware({ app });
  // @ts-ignore
  await promisify(app.listen).call(app, PORT);
  console.log(`> Started on port ${PORT}`);
}

main().catch(err => {
  console.error(err);
  process.exit(1);
});
