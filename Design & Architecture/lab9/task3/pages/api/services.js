import { connectToDatabase } from "@/lib/mongodb";
import { ServiceService } from "@/services/ServiceService";

export default async function handler(req, res) {
  await connectToDatabase();
  const service = new ServiceService();

  if (req.method === "GET") {
    const data = await service.getAll();
    return res.status(200).json(data);
  }

  if (req.method === "POST") {
    const created = await service.create(req.body);
    return res.status(201).json(created);
  }

  res.status(405).end(); // Method Not Allowed
}