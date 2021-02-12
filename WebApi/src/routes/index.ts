import { Router } from "express";
import { User } from "../models/User";
import { UserService } from "../services/user-service";
import * as jwt from "jsonwebtoken";
import { getTokenKey } from "../global";

const router = Router();

router.post("/dologin", async (req, res) => {
  let x = new UserService();
  console.log(req.body);

  const usr = await x.doLogin(req.body);

  let ret_val = {};

  if (usr !== undefined) {
    var mytoken = jwt.sign({ internal: usr.userName }, getTokenKey());

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

export default router;
