#ifndef QLSOLVER_H
#define QLSOLVER_H

#include <vector>
#include <string>
#include <QString>


using namespace std;


struct Implicant {
    string binaryStr;       // Dạng nhị phân, vd: "10-1"
    vector<int> minterms;   // Các ô mà nó đang bao phủ, vd: {9, 11}
    bool isMerged;          // Đánh dấu xem nó đã được gộp với ai chưa

    // Constructor để tạo dữ liệu cho nhanh
    Implicant(string b, vector<int> m) : binaryStr(b), minterms(m), isMerged(false) {}
};

class QLSolver
{
public:
    QLSolver();
    void solve(int soBien, bool isSOP, const vector<int>& minterms, const vector<int>& dontCares);

    // Lấy chuỗi phương trình cuối cùng
    QString getBieuThucRutGon();

    // Lấy danh sách các nhóm đã gom (Mỗi nhóm chứa các ô minterm để GUI tô viền)
    vector<vector<int>> getCacNhomDaGom();

private:
    int m_soBien;
    bool m_isSOP;

    QString m_ketQua;
    vector<vector<int>> m_cacNhom; // Chứa danh sách các ô của từng nhóm kết quả

    // Xử lý nhị phân
    string decToBin(int n, int soBien);

    // 2. Đếm số lượng bit '1' trong chuỗi nhị phân
    int countOnes(const string& s);
    bool differsByOne(const string& a, const string& b);
    string mergeStrings(const string& a, const string& b);
    QString binToExpression(const string& bin);
};

#endif // QLSOLVER_H
