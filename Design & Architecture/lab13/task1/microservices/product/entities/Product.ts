import { Entity, ObjectIdColumn, Column } from "typeorm";

@Entity()
export class Product {
    @ObjectIdColumn()
    id!: string;

    @Column()
    name!: string;

    @Column()
    price!: number;
}
