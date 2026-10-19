import { NextRequest, NextResponse } from "next/server";
import { getProductDataSource } from "../../../microservices/product/product-connection";
import { Product } from "../../../microservices/product/entities/Product";

export async function POST(req: NextRequest) {
    const ds = await getProductDataSource();
    const { name, price } = await req.json();
    const productRepo = ds.getRepository(Product);
    const product = productRepo.create({ name, price });
    await productRepo.save(product);
    return NextResponse.json(product, { status: 201 });
}
