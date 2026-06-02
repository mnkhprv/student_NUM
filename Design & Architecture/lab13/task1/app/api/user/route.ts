import { NextRequest, NextResponse } from "next/server";
import { getUserDataSource } from "../../../microservices/user/user-connection";
import { User } from "../../../microservices/user/entities/User";

export async function POST(req: NextRequest) {
    const ds = await getUserDataSource();
    const { name, email, password } = await req.json();
    const userRepo = ds.getRepository(User);
    const user = userRepo.create({ name, email, password });
    await userRepo.save(user);
    return NextResponse.json(user, { status: 201 });
}
