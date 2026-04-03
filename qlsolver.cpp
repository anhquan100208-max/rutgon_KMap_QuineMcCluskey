#include "qlsolver.h"
#include <algorithm>
#include <QDebug>    // Thư viện này để in kết quả test ra màn hình dưới cùng

using namespace std;

QLSolver::QLSolver() {}
QString QLSolver::getBieuThucRutGon() {
    return m_ketQua;
}

vector<vector<int>> QLSolver::getCacNhomDaGom() {
    return m_cacNhom;
}

// Hàm công cụ 1: Chuyển số thập phân sang chuỗi nhị phân có độ dài cố định
string QLSolver::decToBin(int n, int soBien) {
    string result = "";
    // Chia liên tục cho 2 để lấy phần dư
    for (int i = 0; i < soBien; ++i) {
        result = to_string(n % 2) + result;
        n /= 2;
    }
    return result;
}

// Hàm công cụ 2: Đếm số lượng bit '1' trong chuỗi
int QLSolver::countOnes(const string& s) {
    int count = 0;
    for (char c : s) {
        if (c == '1') count++;
    }
    return count;
}

// Hàm xử lý chính: Chạy khi bấm nút OK
void QLSolver::solve(int soBien, bool isSOP, const vector<int>& minterms, const vector<int>& dontCares) {
    m_soBien = soBien; m_isSOP = isSOP; m_ketQua = ""; m_cacNhom.clear();
    if (minterms.empty()) { m_ketQua = m_isSOP ? "0" : "1"; return; }

    vector<int> allTerms = minterms;
    allTerms.insert(allTerms.end(), dontCares.begin(), dontCares.end());
    sort(allTerms.begin(), allTerms.end());
    allTerms.erase(unique(allTerms.begin(), allTerms.end()), allTerms.end());

    vector<Implicant> currentTable;
    for (int m : allTerms) {
        currentTable.push_back(Implicant(decToBin(m, soBien), {m}));
    }

    vector<Implicant> primeImplicants;

    // QUINE-MCCLUSKEY BƯỚC 1: GỘP NHÓM LIÊN TỤC
    while (!currentTable.empty()) {
        vector<Implicant> nextTable;
        for (size_t i = 0; i < currentTable.size(); ++i) {
            for (size_t j = i + 1; j < currentTable.size(); ++j) {
                if (differsByOne(currentTable[i].binaryStr, currentTable[j].binaryStr)) {
                    currentTable[i].isMerged = true;
                    currentTable[j].isMerged = true;

                    vector<int> mergedMinterms = currentTable[i].minterms;
                    mergedMinterms.insert(mergedMinterms.end(), currentTable[j].minterms.begin(), currentTable[j].minterms.end());
                    sort(mergedMinterms.begin(), mergedMinterms.end());
                    mergedMinterms.erase(unique(mergedMinterms.begin(), mergedMinterms.end()), mergedMinterms.end());

                    string newBin = mergeStrings(currentTable[i].binaryStr, currentTable[j].binaryStr);

                    bool exists = false;
                    for (const auto& imp : nextTable) {
                        if (imp.binaryStr == newBin) { exists = true; break; }
                    }
                    if (!exists) nextTable.push_back(Implicant(newBin, mergedMinterms));
                }
            }
        }

        // Lưu lại các nhóm không gộp được nữa
        for (const auto& imp : currentTable) {
            if (!imp.isMerged) {
                bool exists = false;
                for (const auto& pi : primeImplicants) {
                    if (pi.binaryStr == imp.binaryStr) { exists = true; break; }
                }
                if (!exists) primeImplicants.push_back(imp);
            }
        }
        currentTable = nextTable;
    }

    // QUINE-MCCLUSKEY BƯỚC 2: TÌM BẢNG PHỦ (Tham lam)
    vector<int> termsToCover = minterms;
    while (!termsToCover.empty()) {
        int bestPI_idx = -1;
        int maxCovered = 0;

        for (size_t i = 0; i < primeImplicants.size(); ++i) {
            int coverCount = 0;
            for (int m : primeImplicants[i].minterms) {
                if (find(termsToCover.begin(), termsToCover.end(), m) != termsToCover.end()) coverCount++;
            }
            if (coverCount > maxCovered) {
                maxCovered = coverCount;
                bestPI_idx = i;
            }
        }

        if (bestPI_idx == -1) break; // Lỗi an toàn

        m_cacNhom.push_back(primeImplicants[bestPI_idx].minterms);
        QString bieuThucPI = binToExpression(primeImplicants[bestPI_idx].binaryStr);
        m_ketQua += bieuThucPI + (m_isSOP ? " + " : " . ");

        for (int m : primeImplicants[bestPI_idx].minterms) {
            termsToCover.erase(remove(termsToCover.begin(), termsToCover.end(), m), termsToCover.end());
        }
    }

    if (m_ketQua.endsWith(" + ")) m_ketQua.chop(3);
    if (m_ketQua.endsWith(" . ")) m_ketQua.chop(3);
}

bool QLSolver::differsByOne(const string& a, const string& b) {
    int diff = 0;
    for (size_t i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) diff++;
    }
    return diff == 1;
}

// Hàm gộp 2 chuỗi (Thay bit khác nhau bằng dấu '-')
string QLSolver::mergeStrings(const string& a, const string& b) {
    string res = a;
    for (size_t i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) res[i] = '-';
    }
    return res;
}

// Hàm dịch chuỗi (vd: "10-1") sang biểu thức (vd: "AB'D")
QString QLSolver::binToExpression(const string& bin) {
    QString expr = "";
    QString vars[] = {"A", "B", "C", "D", "E", "F", "G", "H"};

    bool hasTerm = false;

    for(size_t i = 0; i < bin.length(); ++i) {
        if (bin[i] == '-') continue;

        // Cú pháp an toàn: Nếu lỡ số biến vượt quá 8 thì mượn tạm chữ X
        QString tenBien = (i < 8) ? vars[i] : "X" + QString::number(i);

        hasTerm = true;
        if (m_isSOP) { // Tổng các tích
            expr += (bin[i] == '1') ? tenBien : tenBien + "'";
        } else { // Tích các tổng
            expr += (bin[i] == '1') ? tenBien + "' + " : tenBien + " + ";
        }
    }

    if (!hasTerm) return m_isSOP ? "1" : "0"; // Rút gọn hết

    if (!m_isSOP) {
        expr.chop(3); // Cắt bỏ chữ " + " bị dư ở cuối
        expr = "(" + expr + ")";
    }
    return expr;
}
