import { Router } from "express";

import { UserService } from "../services/user-service";

const router = Router();

router.post("/user", async (req, res) => {
  let x = new UserService();
  console.log(req.body);

  const usr = await x.doLogin(req.body);

  let ret_val = {};

  if (usr !== undefined) {
    ret_val = {
      status: "OK",
      mensagem: "Login com sucesso!",
      id: usr.Id,
      username: usr.userName,
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

router.post("/new_user", (req, res) => {
  res.json({});
});

export default router;
