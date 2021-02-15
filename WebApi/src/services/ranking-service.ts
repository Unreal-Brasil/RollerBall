import { getConnection } from "typeorm";
import { PlayedGame } from "../models/PlayedGame";
import { User } from "../models/User";

export default class RankingService {

    async getGlobalRanking() {
        const result = await getConnection()
            .getRepository(PlayedGame)
            .createQueryBuilder("played")
            .select("played.userId")
            .addSelect("MAX(played.score)", "maxScore")
            .addSelect("User.userName", "userName")
            .innerJoin("played.user", "User")
            .groupBy("played.userId")
            .orderBy("maxScore", "DESC")
            .getRawMany();

        return result;
    }
}