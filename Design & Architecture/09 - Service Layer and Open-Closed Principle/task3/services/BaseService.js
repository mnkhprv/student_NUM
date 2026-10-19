export class BaseService {
  constructor(model) {
    this.model = model;
  }

  async getAll() {
    return this.model.find({});
  }

  async create(data) {
    return this.model.create(data);
  }
}