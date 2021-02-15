import { type } from "os";
import { Column, Entity, OneToMany, PrimaryGeneratedColumn, Unique } from "typeorm";
import { PlayedGame } from "./PlayedGame";

@Entity()
@Unique("UNI-User", ["userName"])
@Unique("UNI-Email", ["email"])
export class User {

  @PrimaryGeneratedColumn()
  Id: Number;

  @Column({ length: 100 })
  userName: string;

  @Column({ select: false, length: 10 })
  password: string;

  @Column({ length: 250 })
  email: string;

  @Column({ nullable: true, type: "datetime" })
  ultimoLogin: Date;

  @Column({ nullable: true, type: "datetime" })
  dataCadastro: Date;

  @Column()
  habilitado: boolean;

  @OneToMany(type => PlayedGame, pg => pg.user)
  playedGames: PlayedGame[];
}
