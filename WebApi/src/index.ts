import "reflect-metadata";
import * as express from "express";
import indexRoutes from "./routes/index";
import * as bodyParser from "body-parser";
import { createConnection, getConnection } from "typeorm";
import { User } from "./models/User";

(async () => {
  const cnn = await createConnection({
    type: "mysql",
    host: "localhost",
    port: 3306,
    username: "root",
    password: "senha@1010",
    database: "db_roller_ball",
    entities: [User],
    synchronize: true,
    logging: false,
  });
})();

const app = express();

app.use(express.json());
app.use(indexRoutes);

app.listen(3000);
