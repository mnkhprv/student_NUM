export class Material {
  constructor(
    public name: string,
    public pricePerUnit: number, // 1 нэгж материалын үнэ
    public width: number, // Материалын өргөн
    public height: number // Материалын өндөр
  ) {}

  getTotalArea(): number {
    return this.width * this.height;
  }

  getRemainingArea(usedArea: number): number {
    return Math.max(0, this.getTotalArea() - usedArea);
  }
}
