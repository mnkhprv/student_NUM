// Үндсэн класс
class Mal {
  constructor(name) {
    this.name = name;
  }

  getSound() {
    return "Дуугүй";
  }

  getColor() {
    return "lightgray";
  }

  getEmoji() {
    return "❓";
  }
}

// Адуу
export class Hourse extends Mal {
  getSound() {
    return "Янцгаана";
  }

  getColor() {
    return "khaki";
  }

  getEmoji() {
    return "🐴";
  }
}

// Тэмээ
export class Camel extends Mal {
  getSound() {
    return "Буйлна";
  }

  getColor() {
    return "burlywood";
  }

  getEmoji() {
    return "🐫";
  }
}

// Үхэр
export class Cow extends Mal {
  getSound() {
    return "Мөөрнө";
  }

  getColor() {
    return "lightcoral";
  }

  getEmoji() {
    return "🐄";
  }
}

// Хонь
export class Sheep extends Mal {
  getSound() {
    return "Майлна";
  }

  getColor() {
    return "white";
  }

  getEmoji() {
    return "🐑";
  }
}

// Ямаа
export class Coat extends Mal {
  getSound() {
    return "Майлна";
  }

  getColor() {
    return "lightblue";
  }

  getEmoji() {
    return "🐐";
  }
}

export default Mal;