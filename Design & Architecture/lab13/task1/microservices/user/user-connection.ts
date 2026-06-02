import "reflect-metadata";
import { DataSource } from "typeorm";
import { User } from "./entities/User";

const userDataSource = new DataSource({
    type: "mongodb",
    url: process.env.USER_DB_URI,
    entities: [User],
});

export async function getUserDataSource() {
    if (!userDataSource.isInitialized) {
        await userDataSource.initialize();
    }
    return userDataSource;
}
