#include "matrice.h"
#include <iostream>

using namespace std;
/**
 * Хоёр хэмжээст матрицыг илэрхийлэх класс. 
 * Энэ класс нь матрицын хэмжээс (мөр, багана) болон элементүүдийг хадгалж, 
 * математик болон бусад үйлдлүүдийг хийнэ.
 */
void Matrix :: allocate(int r, int c){
  if (r <= 0 || c <= 0) {
    rows = 0; //Матрицын мөрийн тоо (m)
    cols = 0; // Матрицын баганын тоо (n)
    values = nullptr; //Матрицын элементүүдийг хадгалах хоёр хэмжээст массив
    return;
  }
  rows = r;
  cols = c;
  values = new float*[rows];  // Мөрүүдийн заагчийн массив үүсгэх
  for (int i = 0; i < rows; ++i){
    values[i] = new float[cols];  // Мөр тус бүрт багануудыг үүсгэх
    for(int j = 0; j < cols; ++j){
      values[i][j] = 0.0f; // Элементүүдийг 0-ээр эхлүүлэх
    }
  }
}
Matrix::Matrix(int r, int c){
  allocate(r, c);
}
Matrix::Matrix(const Matrix& other){ //Матрицын хуулбар байгуулагч функц
  allocate(other.rows, other.cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      setValue(i, j, other.getValue(i, j));
    }
  }
}
Matrix :: ~Matrix(){ //Матрицын устгагч функц
  if (values != nullptr) {
      for (int i = 0; i < rows; ++i) {
          delete[] values[i];
      }
      delete[] values;
      values = nullptr;
  }
}
void Matrix :: setValue(int r, int c, float value){ //Матрицын утга оноох set
  if (values == nullptr) {
    cerr << "Aldaa: Matrix sanakh oi noogdoogui\n";
    return;
  }
  if(r >= 0 && r < rows && c >= 0 && c < cols){
    values[r][c] = value;
  }else{
    cerr << "Aldaa index hetersen\n";
    return;
  }
}
void Matrix :: setR(int r) {
  if (r < 0) {
    cerr << "Aldaa: Muriin too 0-ees baga baina!\n";
    return;
  }
  if(values == nullptr){
    rows = r;
    if (cols == 0) cols = 1;
    values = new float*[rows];
    for(int i = 0; i < rows; i++){
      values[i] = new float[cols];
      for(int j = 0; j < cols; j++){
        values[i][j] = 0.0f;
      }
    }
    return;
  }
  float**newValues = new float*[r];
  for(int i = 0; i < r; i++){
    newValues[i] = new float [cols];
  }
  int minRows = (r > rows) ? rows : r;
  for(int i = 0; i < minRows; i++){
    for(int j = 0; j < cols; j++){
      newValues[i][j] = values[i][j];
    }
  }
  for (int i = rows; i < r; i++){
    for(int j = 0; j < cols; j++){
      newValues[i][j] = 0.0f;
    }
  }

  for(int i = 0; i < rows; i++){
    delete[] values[i];
  }
  delete[] values;

  values = newValues;
  rows = r;
}
void Matrix :: setC(int c){
  if(c < 0){
    cerr << "Aldaa: Baganii too 0-ees baga baina!\n";
  }
  if(values == nullptr){
    cols = c;
    if (rows == 0) rows = 1;
    values = new float*[rows];
    for(int i = 0; i < rows; i++){
      values[i] = new float[cols];
      for(int j = 0; j < cols; j++){
        values[i][j] = 0.0f;
      }
    }
    return;
  }
  float** newValues = new float*[rows];
  for (int i = 0; i < rows; i++){
    newValues[i] = new float[c];
  }
  int minCols = (c < cols) ? c : cols;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < minCols; j++){
      newValues[i][j] = values[i][j];
    }
  }
  for(int i = 0; i < rows; i++){
    for(int j = cols; j < c; j++){
      newValues[i][j] = 0.0f;
    }
  }
  for(int i = 0; i < rows; i++){
    delete[] values[i];
  }
  delete[] values;

  values = newValues;
  cols = c;
}
float Matrix :: getValue(int r, int c) const { // Матрицын утга авах
  if (values == nullptr) {
    cerr << "Aldaa: Matrix sanakh oi noogdoogui\n";
    return 0.0f;
  }
  if(r >= 0 && r < rows && c >= 0 && c < cols){
    return values[r][c];
  }else{
    cerr << "Aldaa index hetersen\n" << endl;
    return 0.0f;
  }
}
int Matrix :: getC() const{
  if (values == nullptr) {
    cerr << "Aldaa: Matrix sanakh oi noogdoogui\n";
    return 0;
  }
  return cols;
}
int Matrix :: getR() const{
  if (values == nullptr) {
    cerr << "Aldaa: Matrix sanakh oi noogdoogui\n";
    return 0;
  }
  return rows;
}
void Matrix :: print () const {
  cout << "Матриц (" << rows << "x" << cols << "):" << endl;
  if (rows == 0 || cols == 0) {
    cout << "[Хоосон]" << endl;
    return;
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cout << getValue(i, j) << " \t";
    }
    cout << endl;
  }
}

Matrix& Matrix :: operator=(const Matrix& other){
  if(this != &other){ // Өөрийгөө өөртөө оноохоос сэргийлэх
    if (values != nullptr) {  // Хуучин санах ойг суллах
    for (int i = 0; i < rows; ++i) {
        delete[] values[i];
    }
    delete[] values;
    values = nullptr;
    }
    allocate(other.rows, other.cols);// Шинэ санах ойг хуваарилах
    for(int i = 0; i < rows; i++){ //other матрицын утгыг set-ээр оноох
      for(int j = 0; j < cols; j++){
        setValue(i, j, other.values[i][j]);
      }
    }
  }
  return *this; 
};

Matrix Matrix :: operator+(const Matrix& other) const {
  if(other.cols != cols || other.rows != rows){
    cerr << "matrix hemjee adilhan baih ystoi!\n" << endl;
    return Matrix(0, 0);
  }else{
    Matrix re(rows, cols);
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        re.setValue(i, j, getValue(i, j) + other.getValue(i, j));
      }
    }
    return re;
  }
}
Matrix Matrix :: operator+(float scalar) const {
  Matrix re(rows, cols);
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      re.setValue(i, j, getValue(i, j) + scalar);
    }
  }
  return re;
}
Matrix Matrix :: operator-(const Matrix &other) const { //Матрицын хасах оператор (R = R1 - R2)
    if(other.cols != cols || other.rows != rows){
    cerr << "matrix hemjee adilhan baih ystoi!\n" << endl;
    return Matrix(0, 0); // Хоосон матриц буцаах
  }else{
    Matrix result(rows, cols);
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        result.setValue(i, j, getValue(i , j) - other.getValue(i, j));
      }
    }
    return result;
  }
}

Matrix Matrix :: operator*(const Matrix& other) const{//Матрицын үржих оператор (R = R1 * R2)
  if(cols != other.rows){
    cerr << "Error bagana ni muiin hemjetei adilhan baih ystoi!\n" << endl;
    return Matrix(0, 0); // Хоосон матриц буцаах
  }
  Matrix re(rows, other.cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < other.cols; j++){
      float sum = 0;
      for(int k = 0; k < cols; k++){
        sum += values[i][k] * other.values[k][j];
      }
      re.setValue(i, j, sum);
    }
  }
  return re;
}
Matrix& Matrix :: operator++(){//нэгээр нэмэгдүүлэх оператор
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      setValue(i, j, getValue(i, j) + 1.0f);
    }
  }
  return *this;
};
Matrix& Matrix :: operator--(){ //нэгээр хорогдуулах оператор
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      setValue(i, j, getValue(i, j) - 1.0f);
    }
  }
  return *this;
}
Matrix&Matrix ::operator*=(const Matrix& other){//Үржих утга оноох оператор (*=)
  if(cols != other.rows){
    cerr << "Error bagana ni muiin hemjetei adilhan baih ystoi!\n" << endl;
    return *this;
  }
  *this = (*this) * other;
  return *this;
}
Matrix& Matrix:: operator-=(const Matrix& other){//Хасах утга оноох оператор (-=)
  if(cols != other.cols || rows != other.rows){
    cerr << "Error mur bagana zurj baina!" << endl;
    return *this;
  }
  *this = (*this) - other;
  return *this;
}
Matrix& Matrix:: operator+=(const Matrix& other){//Нэмэх утга оноох оператор (+=)
  if(cols != other.cols || rows != other.rows){
    cerr << "Error mur bagana zurj baina!" << endl;
    return *this;
  }
  *this = (*this) + other; //*this д дамжуулж буй матрицаа 
  return *this;            // дахин тодорхойлсон + оператороор нэмэж хадгалаад буцаана
}
Matrix Matrix:: hurvuuleh() const{
  if (rows == 0 || cols == 0) return Matrix();
  Matrix A(cols, rows); // Шинэ матриц нь cols x rows хэмжээстэй байна
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      A.setValue(j, i, getValue(i, j)); // [i][j] элементийг [j][i] байрлалд хуулах
    }
  }
  return A;
}
