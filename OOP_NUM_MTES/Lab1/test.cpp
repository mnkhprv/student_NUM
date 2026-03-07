#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

// Regular function
float sondgoi_regular(int n, int a[]) {
    int s = 0;
    int k = 0;
    for (int i = 0; i < n; i++){
        if(a[i] % 2 == 1){
            s += a[i];
            k++;
        }
    }
    if (k == 0) return 0;
    return (float)s / k;
}

// Inline function
inline float sondgoi_inline(int n, int a[]) {
    int s = 0;
    int k = 0;
    for (int i = 0; i < n; i++){
        if(a[i] % 2 == 1){
            s += a[i];
            k++;
        }
    }
    if (k == 0) return 0;
    return (float)s / k;
}

int main() {
    // ugugdul testleh
    int a[] = {1, 2, 3, 4, 31, 2, 7, 15, 131, 1};
    int n = 10;
    const int iterations = 1000000;
    
    // engiin function testleh
    auto start = high_resolution_clock::now();
    float result1;
    for (int i = 0; i < iterations; i++) {
        result1 = sondgoi_regular(n, a);
    }
    auto end = high_resolution_clock::now();
    auto duration_regular = duration_cast<microseconds>(end - start);
    
    // inline function tesetleh
    start = high_resolution_clock::now();
    float result2;
    for (int i = 0; i < iterations; i++) {
        result2 = sondgoi_inline(n, a);
    }
    end = high_resolution_clock::now();
    auto duration_inline = duration_cast<microseconds>(end - start);
    
    // Results
    cout << "=== Performance Comparison ===" << endl;
    cout << "Regular function time: " << duration_regular.count() << " microseconds" << endl;
    cout << "Inline function time:  " << duration_inline.count() << " microseconds" << endl;
    cout << "Difference: " << (duration_regular.count() - duration_inline.count()) << " microseconds" << endl;
    
    if (duration_inline.count() < duration_regular.count()) {
        double speedup = (double)duration_regular.count() / duration_inline.count();
        cout << "Inline is " << speedup << "x faster" << endl;
    } else if (duration_regular.count() < duration_inline.count()) {
        double speedup = (double)duration_inline.count() / duration_regular.count();
        cout << "Regular is " << speedup << "x faster" << endl;
    } else {
        cout << "No significant difference" << endl;
    }
    
    cout << "\nResults verification:" << endl;
    cout << "Regular result: " << result1 << endl;
    cout << "Inline result:  " << result2 << endl;
    
    // Assembly inspection instructions
    cout << "\n=== How to inspect assembly code ===" << endl;
    cout << "Compile with: g++ -O2 -S filename.cpp" << endl;
    cout << "Then check the .s file to see if function calls are eliminated" << endl;
    
    return 0;
}