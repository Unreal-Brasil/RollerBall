import "reflect-metadata";
import * as express from "express";
import indexRoutes from "./routes/index";
import * as bodyParser from "body-parser";
import { createConnection, getConnection } from "typeorm";
import { User } from "./models/User";
import { PlayedGame } from "./models/PlayedGame";
import { Game } from "./models/Game";

(async () => {
  const cnn = await createConnection({
    type: "mysql",
    host: "localhost",
    port: 3306,
    username: "root",
    password: "senha@1010",
    database: "db_roller_ball",
    entities: [
      __dirname + "/models/*.ts",
      User,
      Game,
      PlayedGame
    ],
    synchronize: true,
    logging: true,
  });
})();

const app = express();

app.use(express.json());
app.use(indexRoutes);

app.listen(3000);
