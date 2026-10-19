import { BaseService } from "./BaseService";
import ServiceModel from "../models/ServiceModel";

export class ServiceService extends BaseService {
  constructor() {
    super(ServiceModel);
  }

  // BaseService-г өөрчлөхгүйгээр шинэ функц нэмэв → Open/Closed Principle
  async getByTitle(title) {
    return this.model.findOne({ title });
  }
}