import { getConnection } from "typeorm";
import { PlayedGame } from "../models/PlayedGame";
import { User } from "../models/User";

export default class GameService {

    async doRegister(playedGame: PlayedGame) {

        let result = await getConnection().getRepository(PlayedGame).insert(playedGame);
        let result_head = result.raw;
        let pg_tmp = new PlayedGame();

        if (result_head.affectedRows > 0) {
            pg_tmp.Id = result_head.insertId;
            pg_tmp = await this.getById(pg_tmp);
            console.log(pg_tmp);
        }

        return pg_tmp;
    }


    async getById(played: PlayedGame) {
        const result = await getConnection()
            .getRepository(PlayedGame)
            .createQueryBuilder("played")
            .leftJoinAndSelect("played.user", "User")
            .where("played.Id = :id")
            .setParameters({ id: played.Id })
            .getOne();

        return result;
    }
}