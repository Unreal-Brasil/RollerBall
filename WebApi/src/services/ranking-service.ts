import { getConnection } from "typeorm";
import { Game } from "../models/Game";
import { PlayedGame } from "../models/PlayedGame";
import { User } from "../models/User";

export default class RankingService {

    async getGlobalRanking(game: Game) {
        const result = await getConnection()
            .getRepository(PlayedGame)
            .createQueryBuilder("played")
            .select("played.userId")
            .addSelect("MAX(played.score)", "maxScore")
            .addSelect("User.userName", "userName")
            .innerJoin("played.user", "User")
            .where("played.gameId = :gameId")
            .setParameters({ gameId: game.Id })
            .groupBy("played.userId")
            .orderBy("maxScore", "DESC")
            .getRawMany();

        return result;
    }
}