import { Router } from "express";
import { User } from "../models/User";
import { UserService } from "../services/user-service";
import * as jwt from "jsonwebtoken";
import { getTokenKey } from "../global";
import GameService from "../services/game-service";
import { PlayedGame } from "../models/PlayedGame";
import RankingService from "../services/ranking-service";

const router = Router();

function checkToken(tk: string): any {
  let decoded = undefined;
  try {
    decoded = jwt.verify(tk, getTokenKey());
  } catch (error) {
    console.log(error);
  }

  return decoded;
}

router.post("/dologin", async (req, res) => {
  let x = new UserService();
  console.log(req.body);

  const usr = await x.doLogin(req.body);

  let ret_val = {};

  if (usr !== undefined) {
    var mytoken = jwt.sign({ Id: usr.Id, userName: usr.userName }, getTokenKey());

    ret_val = {
      status: "OK",
      mensagem: "Login com sucesso!",
      id: usr.Id,
      username: usr.userName,
      token: mytoken,
    };
  } else {
    ret_val = {
      status: "ERROR",
      mensagem: "Login Inválido!",
    };
  }
  console.log(ret_val);
  res.json(ret_val);
});

router.post("/doregister", async (req, res) => {
  let x = new UserService();

  let u = req.body as User;

  u.dataCadastro = new Date();

  const usr = await x.doRegister(u);

  let ret_val = {};

  if (usr !== undefined) {
    ret_val = {
      status: "OK",
      mensagem: "USUARIO REGISTADO COM SUCESSO!",
      id: usr.Id,
      username: usr.userName,
    };
  } else {
    ret_val = {
      status: "ERROR",
      mensagem: "Não foi possível efetuar o cadastro!",
    };
  }
  console.log(ret_val);
  res.json(ret_val);
});

router.post("/doregistergame", async (req, res) => {
  let x = new GameService();
  let userInfo = checkToken(req.body.token);
  let ret_val = {};

  if (userInfo === undefined) {
    ret_val = {
      status: "ERROR",
      mensagem: "Não foi possível computar os dados!",
    };
  } else {
    let tmp_user = new User();

    let u = req.body as PlayedGame;
    u.dataJogo = new Date();
    tmp_user.Id = userInfo.Id;

    u.user = tmp_user;
    const game = await x.doRegister(u);
    if (game !== undefined) {
      ret_val = {
        status: "OK",
        mensagem: "JOGO REGISTADO COM SUCESSO!",
        id: game.Id
      };
    } else {
      ret_val = {
        status: "ERROR",
        mensagem: "Não foi possível gravar os dados!",
      };
    }

    console.log(ret_val);
  }

  res.json(ret_val);
});

router.post("/getrankingglobal", async (req, res) => {
  let x = new RankingService()
  const ranking = await x.getGlobalRanking();

  let ret_val = {
    status: "OK",
    ranking: ranking,
  };



  res.json(ret_val);
});



export default router;
