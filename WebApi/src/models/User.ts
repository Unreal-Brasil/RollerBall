import { type } from "os";
import { Column, Entity, PrimaryGeneratedColumn, Unique } from "typeorm";

@Entity()
@Unique("UNI-User", ["userName"])
@Unique("UNI-Email", ["email"])
export class User {
  @PrimaryGeneratedColumn()
  Id: Number;

  @Column({ length: 100 })
  userName: string;

  @Column({ length: 10 })
  password: string;

  @Column({ length: 250 })
  email: string;

  @Column({ nullable: true, type: "datetime" })
  ultimoLogin: Date;

  @Column({ nullable: true, type: "datetime" })
  dataCadastro: Date;

  @Column()
  habilitado: boolean;
}
