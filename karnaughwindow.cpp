#include "karnaughwindow.h"
#include "ui_karnaughwindow.h"
#include "qlsolver.h"

KarnaughWindow::KarnaughWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KarnaughWindow)
{
    ui->setupUi(this);

    // Mặc định
    ui->tableKetQua->setVisible(false);

    // Khi đổi số biến
    connect(ui->cbbSoBien, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){
                int soBien = index + 2;

                // Ẩn bảng kết quả và xóa dòng chữ phương trình cũ
                ui->tableKetQua->setVisible(false);
                ui->txtKetQua->setText("");

                if (soBien <= 4) {
                    // Nếu <= 4 biến: Hiện K-Map, Ẩn khung nhập tay, MỞ KHÓA nút OK
                    ui->tableKMap->setVisible(true);
                    ui->grpNhapTay->setVisible(false);
                    ui->btnOK->setEnabled(true);

                    veBanDoKarnaugh(soBien);

                } else {
                    // Nếu > 4 biến: Ẩn K-Map, Hiện khung nhập tay, KHÓA nút OK
                    ui->tableKMap->setVisible(false);
                    ui->grpNhapTay->setVisible(true);
                    ui->btnOK->setEnabled(false);
                }
            });

    // Khi đổi SOP/POS
    connect(ui->cbbDangBieuThuc, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){
                if (index == 0) { // Đang chọn SOP
                    ui->txtMainTerms->setPlaceholderText("Nhập Minterms (vd: 1, 2, 5, 10)");
                } else {          // Đang chọn POS
                    ui->txtMainTerms->setPlaceholderText("Nhập Maxterms (vd: 0, 3, 7, 15)");
                }
            });

    // Kích hoạt giao diện lần đầu tiên
    ui->cbbDangBieuThuc->currentIndexChanged(0);
    ui->cbbSoBien->currentIndexChanged(ui->cbbSoBien->currentIndex());
}

KarnaughWindow::~KarnaughWindow()
{
    delete ui;
}

void KarnaughWindow::veBanDoKarnaugh(int soBien)
{
    ui->tableKMap->clear();
    ui->tableKetQua->clear();
    ui->tableKetQua->setRowCount(0); ui->tableKetQua->setColumnCount(0);

    // Ẩn tiêu đề mặc định của Qt
    ui->tableKMap->horizontalHeader()->setVisible(false);
    ui->tableKMap->verticalHeader()->setVisible(false);

    int grayToDec[] = {0, 1, 3, 2};
    QStringList cot, hang;
    QString textTren, textDuoi;
    int soHangKMap, soCotKMap;

    // Cài đặt thông số theo số biến
    if (soBien == 2) {
        soHangKMap = 2; soCotKMap = 2;
        cot << "0" << "1"; hang << "0" << "1";
        textTren = "A"; textDuoi = "B";
    } else if (soBien == 3) {
        soHangKMap = 2; soCotKMap = 4;
        cot << "00" << "01" << "11" << "10"; hang << "0" << "1";
        textTren = "AB"; textDuoi = "C";
    } else {
        soHangKMap = 4; soCotKMap = 4;
        cot << "00" << "01" << "11" << "10"; hang << "00" << "01" << "11" << "10";
        textTren = "AB"; textDuoi = "CD";
    }

    // Tăng thêm 1 hàng & 1 cột để làm tiêu đề giả
    ui->tableKMap->setRowCount(soHangKMap + 1);
    ui->tableKMap->setColumnCount(soCotKMap + 1);

    // -- Vẽ ô góc (0,0) có đường chéo --
    ui->tableKMap->setCellWidget(0, 0, new O_Goc(textTren, textDuoi));

    // -- Vẽ hàng tiêu đề (Cột) --
    for(int i = 0; i < soCotKMap; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(cot[i]);
        item->setBackground(QBrush(QColor(210, 210, 210))); // Tô màu xám
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled); // Khóa lại, không cho click
        ui->tableKMap->setItem(0, i + 1, item);
    }

    // -- Vẽ cột tiêu đề (Hàng) --
    for(int i = 0; i < soHangKMap; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(hang[i]);
        item->setBackground(QBrush(QColor(210, 210, 210)));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableKMap->setItem(i + 1, 0, item);
    }

    // -- Điền các ô Minterm (Số vị trí) --
    for(int r = 0; r < soHangKMap; ++r) {
        for(int c = 0; c < soCotKMap; ++c) {
            int minterm;
            if (soBien == 2) minterm = c * 2 + r;
            else if (soBien == 3) minterm = grayToDec[c] * 2 + r;
            else minterm = grayToDec[c] * 4 + grayToDec[r];

            QTableWidgetItem *item = new QTableWidgetItem(QString::number(minterm));
            item->setTextAlignment(Qt::AlignCenter);
            item->setBackground(QBrush(Qt::white));
            item->setData(Qt::UserRole, 0);

            // Lùi tọa độ lại 1 ô vì đã chèn tiêu đề
            ui->tableKMap->setItem(r + 1, c + 1, item);
        }
    }

    ui->tableKMap->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableKMap->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void KarnaughWindow::on_tableKMap_cellClicked(int row, int column)
{
    if (row == 0 || column == 0) {
        return;
    }

    // Lấy ô hiện tại đang được click (chắc chắn lúc này là ô dữ liệu hợp lệ)
    QTableWidgetItem *item = ui->tableKMap->item(row, column);
    if (!item) return;

    // Kiểm tra xem chế độ Don't Care có đang được tích hay không
    bool isDontCareMode = ui->chkDontCare->isChecked();

    // Lấy trạng thái hiện tại của ô được lưu ngầm (0: trống, 1: chọn, 2: don't care)
    int trangThai = item->data(Qt::UserRole).toInt();

    // NẾU ĐANG BẬT CHẾ ĐỘ DON'T CARE (Click để chọn X)
    if (isDontCareMode) {
        if (trangThai == 2) {
            // Đang là Don't care (X) rồi, click phát nữa thì bỏ chọn (trả về 0)
            item->setData(Qt::UserRole, 0);
            item->setBackground(QBrush(Qt::white));
        } else {
            // Nếu chưa phải X, đổi trạng thái thành 2 và tô nền màu Vàng
            item->setData(Qt::UserRole, 2);
            item->setBackground(QBrush(Qt::yellow));
        }
    }
    // NẾU KHÔNG BẬT CHẾ ĐỘ DON'T CARE (Click để chọn biến bình thường)
    else {
        if (trangThai == 1) {
            // Đang được chọn rồi, click phát nữa thì bỏ chọn (trả về 0)
            item->setData(Qt::UserRole, 0);
            item->setBackground(QBrush(Qt::white));
        } else {
            // Nếu chưa chọn, đổi trạng thái thành 1 và tô nền màu Xanh lá
            item->setData(Qt::UserRole, 1);
            item->setBackground(QBrush(Qt::green));
        }
    }
}
void KarnaughWindow::on_btnOK_clicked()
{
    int soBien = ui->cbbSoBien->currentIndex() + 2;
    bool isSOP = (ui->cbbDangBieuThuc->currentIndex() == 0);

    std::vector<int> listMainTerms;
    std::vector<int> listDontCares;

    // Kiểm tra dữ liệu
    if (soBien <= 4) {
        // Nếu <= 4 biến: Lấy dữ liệu từ việc quét Bảng 1
        int soHang = ui->tableKMap->rowCount();
        int soCot = ui->tableKMap->columnCount();
        for(int r = 1; r < soHang; ++r) {
            for(int c = 1; c < soCot; ++c) {
                QTableWidgetItem *item = ui->tableKMap->item(r, c);
                if (!item) continue;
                int trangThai = item->data(Qt::UserRole).toInt();
                int giatri = item->text().toInt();

                if (trangThai == 1) listMainTerms.push_back(giatri);
                else if (trangThai == 2) listDontCares.push_back(giatri);
            }
        }
    } else {
        // Nếu > 4 biến: Lấy dữ liệu từ chuỗi nhập tay
        const QStringList listMin = ui->txtMainTerms->text().split(",", Qt::SkipEmptyParts);
        for (const QString &s : listMin) {
            listMainTerms.push_back(s.trimmed().toInt());
        }

        const QStringList listDC = ui->txtDontCares->text().split(",", Qt::SkipEmptyParts);
        for (const QString &s : listDC) {
            listDontCares.push_back(s.trimmed().toInt());
        }
    }

    // Gọi thuật toán + in kq chữ
    QLSolver solver;
    solver.solve(soBien, isSOP, listMainTerms, listDontCares);

    QString bieuThuc = solver.getBieuThucRutGon();
    ui->txtKetQua->setText("F = " + bieuThuc);

    // Vẽ bảng kết quả (<4)
    if (soBien <= 4) {
        ui->tableKetQua->setVisible(true); // Hiện bảng lên

        int soHang = ui->tableKMap->rowCount();
        int soCot = ui->tableKMap->columnCount();

        ui->tableKetQua->setRowCount(soHang);
        ui->tableKetQua->setColumnCount(soCot);
        ui->tableKetQua->horizontalHeader()->setVisible(false);
        ui->tableKetQua->verticalHeader()->setVisible(false);

        std::vector<std::vector<int>> danhSachNhom = solver.getCacNhomDaGom();
        QList<QColor> bangMau = {Qt::red, Qt::green, Qt::blue, Qt::magenta, QColor(255, 165, 0)};

        for(int r = 0; r < soHang; ++r) {
            for(int c = 0; c < soCot; ++c) {

                // Xử lý ô góc (0,0)
                if (r == 0 && c == 0) {
                    QString tTren, tDuoi;
                    if (soBien == 2) { tTren = "A"; tDuoi = "B"; }
                    else if (soBien == 3) { tTren = "AB"; tDuoi = "C"; }
                    else { tTren = "AB"; tDuoi = "CD"; }
                    ui->tableKetQua->setCellWidget(0, 0, new O_Goc(tTren, tDuoi));
                    continue;
                }

                // Xử lý tiêu đề
                if (r == 0 || c == 0) {
                    QTableWidgetItem *itemGoc = ui->tableKMap->item(r, c);
                    if (itemGoc) {
                        QTableWidgetItem *itemTieuDe = new QTableWidgetItem(itemGoc->text());
                        itemTieuDe->setBackground(QBrush(QColor(210, 210, 210)));
                        itemTieuDe->setTextAlignment(Qt::AlignCenter);
                        ui->tableKetQua->setItem(r, c, itemTieuDe);
                    }
                    continue;
                }

                // Xử lý ô dữ liệu lồng viền màu
                QTableWidgetItem *itemGoc = ui->tableKMap->item(r, c);
                if (!itemGoc) continue;

                int minterm = itemGoc->text().toInt();
                int trangThai = itemGoc->data(Qt::UserRole).toInt();

                QString textKetQua = "0";
                if (trangThai == 2) textKetQua = "X";
                else if (trangThai == 1) textKetQua = isSOP ? "1" : "0";
                else textKetQua = isSOP ? "0" : "1";

                QList<QColor> mauCuaO;
                for (size_t i = 0; i < danhSachNhom.size(); ++i) {
                    if (std::find(danhSachNhom[i].begin(), danhSachNhom[i].end(), minterm) != danhSachNhom[i].end()) {
                        mauCuaO.append(bangMau[i % bangMau.size()]);
                    }
                }
                ui->tableKetQua->setCellWidget(r, c, new O_KetQua(textKetQua, mauCuaO));
            }
        }
        ui->tableKetQua->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableKetQua->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    } else {
        // Nếu > 4 biến thì ẩn cái bảng kết quả đi luôn cho gọn
        ui->tableKetQua->setVisible(false);
    }
}


void KarnaughWindow::on_btnBangTrangThai_clicked()
{
    int soBien = ui->cbbSoBien->currentIndex() + 2;
    bool isSOP = (ui->cbbDangBieuThuc->currentIndex() == 0);

    std::vector<int> listMainTerms;
    std::vector<int> listDontCares;

    // Kiểm tra dữ liệu
    if (soBien <= 4) {
        int soHang = ui->tableKMap->rowCount();
        int soCot = ui->tableKMap->columnCount();
        for(int r = 1; r < soHang; ++r) {
            for(int c = 1; c < soCot; ++c) {
                QTableWidgetItem *item = ui->tableKMap->item(r, c);
                if (!item) continue;
                int trangThai = item->data(Qt::UserRole).toInt();
                int giatri = item->text().toInt();

                if (trangThai == 1) listMainTerms.push_back(giatri);
                else if (trangThai == 2) listDontCares.push_back(giatri);
            }
        }
    } else {
        const QStringList listMin = ui->txtMainTerms->text().split(",", Qt::SkipEmptyParts);
        for (const QString &s : listMin) listMainTerms.push_back(s.trimmed().toInt());

        const QStringList listDC = ui->txtDontCares->text().split(",", Qt::SkipEmptyParts);
        for (const QString &s : listDC) listDontCares.push_back(s.trimmed().toInt());
    }

    // Gọi thuật toán và in kq chữ
    QLSolver solver;
    solver.solve(soBien, isSOP, listMainTerms, listDontCares);

    QString bieuThuc = solver.getBieuThucRutGon();
    ui->txtKetQua->setText("F = " + bieuThuc);

    // Bảng kq --> Bảng trạng thái
    ui->tableKetQua->setVisible(true); // Đảm bảo bảng hiện lên

    int soHang = (1 << soBien); // 2^soBien (vd: 3 biến = 8 hàng, 4 biến = 16 hàng)
    int soCot = soBien + 1;     // Số cột = Số biến (A,B,C...) + 1 cột kết quả (F)

    ui->tableKetQua->clear();
    ui->tableKetQua->setRowCount(soHang);
    ui->tableKetQua->setColumnCount(soCot);

    // Bật lại thanh tiêu đề ngang (vì nút OK đã ẩn nó đi)
    ui->tableKetQua->horizontalHeader()->setVisible(true);
    ui->tableKetQua->verticalHeader()->setVisible(false);

    // Tạo danh sách tên cột (A, B, C, D,... và Y)
    QStringList headers;
    QString vars[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    for (int i = 0; i < soBien; ++i) {
        headers << ((i < 8) ? vars[i] : "X" + QString::number(i));
    }
    headers << "Y"; // Cột kết quả cuối cùng
    ui->tableKetQua->setHorizontalHeaderLabels(headers);

    // Đổ dữ liệu 0/1 vào bảng trạng thái
    for (int i = 0; i < soHang; ++i) {

        // Điền các bit 0/1 của biến đầu vào (Các cột A, B, C...)
        for (int bit = 0; bit < soBien; ++bit) {
            // Phép dịch bit để lấy số 0 hoặc 1
            int val = (i >> (soBien - 1 - bit)) & 1;
            QTableWidgetItem *itemBit = new QTableWidgetItem(QString::number(val));
            itemBit->setTextAlignment(Qt::AlignCenter);
            ui->tableKetQua->setItem(i, bit, itemBit);
        }

        // Điền kết quả cột F
        QString textF;
        if (std::find(listMainTerms.begin(), listMainTerms.end(), i) != listMainTerms.end()) {
            textF = isSOP ? "1" : "0";
        } else if (std::find(listDontCares.begin(), listDontCares.end(), i) != listDontCares.end()) {
            textF = "X";
        } else {
            textF = isSOP ? "0" : "1";
        }

        QTableWidgetItem *itemF = new QTableWidgetItem(textF);
        itemF->setTextAlignment(Qt::AlignCenter);

        // Tô nền xanh nhạt, chữ in đậm và màu đỏ/xanh cho cột F dễ nhìn
        itemF->setBackground(QBrush(QColor(240, 248, 255)));
        QFont font = itemF->font();
        font.setBold(true);
        itemF->setFont(font);
        if (textF == "1") itemF->setForeground(QBrush(Qt::blue));
        else if (textF == "0") itemF->setForeground(QBrush(Qt::red));

        ui->tableKetQua->setItem(i, soBien, itemF);
    }

    // Kéo giãn các cột cho đẹp
    ui->tableKetQua->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

