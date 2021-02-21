import { type } from "os";
import { Column, Entity, ManyToOne, PrimaryGeneratedColumn, Unique } from "typeorm";
import { Game } from "./Game";
import { User } from "./User";


@Entity()
export class PlayedGame {

  @PrimaryGeneratedColumn()
  Id: number;

  @Column({ type: "numeric" })
  score: number;

  @Column({ type: "numeric" })
  time: number;

  @Column({ nullable: true, type: "datetime" })
  dataJogo: Date;

  @ManyToOne(type => User, user => user.playedGames)
  user: User;

  @ManyToOne(type => Game, game => game.playedGames)
  game: Game;

}
