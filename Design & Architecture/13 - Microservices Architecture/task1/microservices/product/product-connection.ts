import "reflect-metadata";
import { DataSource } from "typeorm";
import { Product } from "./entities/Product";

const productDataSource = new DataSource({
    type: "mongodb",
    url: process.env.PRODUCT_DB_URI,
    entities: [Product],
});

export async function getProductDataSource() {
    if (!productDataSource.isInitialized) {
        await productDataSource.initialize();
    }
    return productDataSource;
}
