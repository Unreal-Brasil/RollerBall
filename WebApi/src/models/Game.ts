import { type } from "os";
import { Column, Entity, JoinTable, ManyToMany, ManyToOne, OneToMany, PrimaryGeneratedColumn, Unique } from "typeorm";
import { PlayedGame } from "./PlayedGame";
import { User } from "./User";


@Entity()
export class Game {

  @PrimaryGeneratedColumn()
  Id: number;

  @Column({ length: 250 })
  nome: string;
    
  @ManyToMany(type => User, usr=> usr.games)
  users: User[];

  @OneToMany(type => PlayedGame, pg => pg.game)
  playedGames: PlayedGame[];    
}
