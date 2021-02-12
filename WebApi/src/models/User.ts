import { type } from "os";
import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class User {
  @PrimaryGeneratedColumn()
  Id: Number;

  @Column({ length: 100 })
  userName: string;

  @Column({ length: 10 })
  password: string;

  @Column({ length: 250 })
  email: string;

  @Column({ nullable: true, type: "date" })
  ultimoLogin: Date;

  @Column({ nullable: true, type: "date" })
  dataCadastro: Date;

  @Column()
  habilitado: boolean;
}
