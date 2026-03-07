#ifndef MATRICE_H
#define MATRICE_H

/**
 * @brief Хоёр хэмжээст матрицыг илэрхийлэх класс.
 * * Энэ класс нь матрицын хэмжээс (мөр, багана) болон элементүүдийг хадгалж,
 * математик болон бусад үйлдлүүдийг хийнэ.
 */
class Matrix {
  private:
    int rows; // Матрицын мөрийн тоо (m)
    int cols; // Матрицын баганын тоо (n)
    float** values; // Матрицын элементүүдийг хадгалах хоёр хэмжээст массив
    /**
     * @brief Шинэ хэмжээстэй матриц үүсгэх, санах ойг хуваарилах туслах функц.
     * @param r Шинэ мөрийн тоо
     * @param c Шинэ баганын тоо
     */
    
    void allocate(int r, int c);
  public:
    // 1. БАЙГУУЛАГЧ ФУНКЦҮҮД (Constructors)
    /**
     * @brief Матрицын байгуулагч функц
     * @param r Мөрийн тоо
     * @param c Баганын тоо
     */
    Matrix(int r = 1, int c = 1);
    /**
     * @brief Матрицын хуулбар байгуулагч функц
     * @param other Хуулбарлах матриц
     */
    Matrix(const Matrix& other);
    /**
     * @brief Матрицын устгагч функц
     */
    ~Matrix();
    /**
     * @brief Матрицын утга оноох set
     * @param r Мөрийн тоо
     * @param c Баганын тоо
     * @param value Оноох утга
     */
    void setValue(int r, int c, float value);
    /**
     * @brief Матрицын мөр оноох set
     * @param r мөрийн тоо
     */
    void setR(int r);
    /**
     * @brief Матрицын багана оноох set
     * @param c баганы тоо
     */
    void setC(int c);
    /*
     * @brief Матрицын утга авах функц
     * @param r Мөрийн индекс. (0-ээс эхэлнэ)
     * @param c Баганын индекс. (0-ээс эхэлнэ)
     * @return Элементийн утга. Индекс буруу бол 0.0f буцаана
     */
    float getValue(int r, int c) const;
    /**
     * @brief Матрицын мөр авах функц
     */
    int getR() const;
    /**
     * @brief Матрицын багана авах функц
     */
    int getC() const;
    /*
     * @brief Матрицын хэвлэх функц
     */
    void print() const;
    /**
     * @brief Матрицын оноох оператор
     * @param other Оноох матриц
     * @return Өөрчлөгдсөн матриц(*this)
     */
    Matrix& operator=(const Matrix& other);
    /**
     * @brief Хоёр матрицыг нэмэх (R = R1 + R2)
     * @param other Нэмэх матриц
     * @return Үр дүнгийн шинэ матриц
     * * Матрицууд ижил хэмжээстэй байх ёстой
     */
    Matrix operator+(const Matrix& other) const;
    /**
     * @brief Матриц дээр float тоо нэмэх (R = R1 + 12.5)
     * @param scalar Нэмэх float тоо
     * @return Үр дүнгийн шинэ матриц
     */
    Matrix operator+(float scalar) const;
    /**
     * @brief Матрицын хасах оператор (R = R1 - R2)
     * @param other Хасах матриц
     * @return Үр дүнгийн шинэ матриц
     * * Матрицууд ижил хэмжээстэй байх ёстой
     */
    Matrix operator-(const Matrix& other) const;
    /**
     * @brief Матрицын үржих оператор (R = R1 * R2)
     * @param other Үржүүлэх матриц
     * @return Үр дүнгийн шинэ матриц
     * * R1-ийн баганын тоо нь R2-ийн мөрийн тоотой тэнцүү байх ёстой.
     */
    Matrix operator*(const Matrix& other) const;
    /**
     * @brief нэгээр нэмэгдүүлэх оператор
     * * Матрицын бүх элементийг 1-ээр нэмэгдүүлнэ
     * @return Нэмэгдсэн матриц
     */
    Matrix& operator++();
    /**
     * @brief нэгээр хорогдуулах оператор
     * * Матрицын бүх элементийг 1-ээр хорогдуулна
     * @return Хорогдсон матриц
     */
    Matrix& operator--();
    /**
     * @brief Үржих утга оноох оператор (*=)
     * @param other Үржүүлэх матриц
     * @return Өөрчлөгдсөн матриц
     * * Матрицын үржвэрийг тооцоолоод өөрт нь онооно
     */
    Matrix& operator*=(const Matrix& other);
    /**
     * @brief Хасах утга оноох оператор (-=)
     * @param other Хасах матриц
     * @return Өөрчлөгдсөн матриц
     * * Матрицын элементүүдийг хасаад өөрт нь онооно
     */
    Matrix& operator-=(const Matrix& other);
    /**
     * @brief Нэмэх утга оноох оператор (+=)
     * @param other Нэмэх матриц
     * @return Өөрчлөгдсөн матриц
     * * Матрицын элементүүдийг нэмээд өөрт нь онооно
     */
    Matrix& operator+=(const Matrix& other);
    /**
     * @brief Матрицыг хөрвүүлэх
     * @return Хөрвүүлсэн шинэ матриц
     * * Мөрийг багана, баганыг мөр болгон байрлуулах.
     */
    Matrix hurvuuleh()const;
};

#endif