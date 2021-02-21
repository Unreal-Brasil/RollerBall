import { getConnection } from "typeorm";
import { Game } from "../models/Game";
import { User } from "../models/User";

export class UserService {
  async doLogin(usr: User) {
    let result = await getConnection()
      .getRepository(User)
      .createQueryBuilder("user")
      .where("user.userName = :usr_name")
      .andWhere("user.password = :pwd and user.habilitado=1")
      .setParameters({ usr_name: usr.userName, pwd: usr.password })
      .getOne();

    if (result !== undefined) {
      this.updateLoginDate(result);
    }

    console.log(result);

    return result;
  }

  async updateLoginDate(usr: User) {
    const result = await getConnection()
      .getRepository(User)
      .createQueryBuilder()
      .update(User)
      .set({ ultimoLogin: new Date() })
      .where("Id = :id")
      .setParameters({ id: usr.Id })
      .execute();

    console.log(result);
  }

  async getUserById(usr: User) {
    const result = await getConnection()
      .getRepository(User)
      .createQueryBuilder("user")
      .where("user.Id = :id")
      .setParameters({ id: usr.Id })
      .getOne();
    console.log(result);

    return result;
  }

  async doRegister(usr: User) {
    
    console.log(usr);

    const sel_game = await getConnection()
      .getRepository(Game)
      .createQueryBuilder("game")
      .where("game.Id = :id")
      .setParameters({ id: usr.games[0].Id })
      .getOne();

    usr.games = [sel_game];

    let result = await getConnection().getRepository(User).save(usr);

    return result;
  }
}
