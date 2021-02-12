import { getConnection } from "typeorm";
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
    let result = await getConnection().getRepository(User).insert(usr);
    let result_head = result.raw;
    let user_tmp = new User();

    if (result_head.affectedRows > 0) {
      user_tmp.Id = result_head.insertId;
      user_tmp = await this.getUserById(user_tmp);

      console.log(user_tmp);
    }

    return user_tmp;
  }
}
