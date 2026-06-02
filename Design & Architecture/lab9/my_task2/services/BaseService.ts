export abstract class BaseService<T> {
  protected items: T[];

  constructor(items: T[]) {
    this.items = items;
  }

  getAll(): T[] {
    return this.items;
  }

  getById(id: number): T | undefined {
    return this.items.find((item) => (item as any).id === id);
  }
}