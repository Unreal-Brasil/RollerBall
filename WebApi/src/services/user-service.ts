import { getConnection } from "typeorm";
import { User } from "../models/User";

export class UserService {
  async doLogin(usr: User) {
    let result = await getConnection()
      .getRepository(User)
      .createQueryBuilder("user")
      .where("user.userName = :usr_name")
      .andWhere("user.password = :pwd")
      .setParameters({ usr_name: usr.userName, pwd: usr.password })
      .getOne();
    console.log(result);

    return result;
  }
}
