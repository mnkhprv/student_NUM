import { Member } from "../entity/Member";

export interface MemberRepo {
  findById(id: string): Promise<Member | null>;
}
