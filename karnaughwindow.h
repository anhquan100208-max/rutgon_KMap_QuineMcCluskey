#ifndef KARNAUGHWINDOW_H
#define KARNAUGHWINDOW_H


#include <QMainWindow>
#include <QPainter>

class O_Goc : public QWidget {
public:
    QString textTren, textDuoi;
    O_Goc(QString tren, QString duoi, QWidget *parent = nullptr)
        : QWidget(parent), textTren(tren), textDuoi(duoi) {}
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing); // Giúp nét vẽ mịn

        // Vẽ đường chéo từ góc trên-trái xuống dưới-phải
        painter.drawLine(0, 0, width(), height());

        // Viết chữ AB ở nửa trên bên phải, CD ở nửa dưới bên trái
        painter.drawText(QRect(0, 0, width(), height()/2), Qt::AlignRight | Qt::AlignBottom, textTren + "  ");
        painter.drawText(QRect(0, height()/2, width(), height()/2), Qt::AlignLeft | Qt::AlignTop, "  " + textDuoi);
    }
};

class O_KetQua : public QWidget {
public:
    QString textGiaTri;
    QList<QColor> danhSachMauNhom;
    O_KetQua(QString text, QList<QColor> mauNhom, QWidget *parent = nullptr)
        : QWidget(parent), textGiaTri(text), danhSachMauNhom(mauNhom) {}
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(), Qt::white); // Nền mặc định trắng

        int padding = 2;
        QRect khungVien = rect();


        for (int i = 0; i < danhSachMauNhom.size(); ++i) {
            QColor mau = danhSachMauNhom.at(i);

            painter.setPen(QPen(mau, 3)); // Viền dày 3px
            khungVien.adjust(padding, padding, -padding, -padding);
            painter.drawRect(khungVien);
            padding += 3; // Lùi viền tiếp theo vào trong
        }

        painter.setPen(Qt::black);
        QFont font = painter.font(); font.setBold(true); font.setPointSize(14);
        painter.setFont(font);
        painter.drawText(rect(), Qt::AlignCenter, textGiaTri); // In số 1/0/X ra giữa
    }
};

namespace Ui {

class KarnaughWindow;
}

class KarnaughWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KarnaughWindow(QWidget *parent = nullptr);
    ~KarnaughWindow();

private:
    Ui::KarnaughWindow *ui;
    void veBanDoKarnaugh(int soBien);

private slots:
// Tự động chạy khi click vào 1 ô trong bảng
void on_tableKMap_cellClicked(int row, int column);
    void on_btnOK_clicked();
void on_btnBangTrangThai_clicked();
};

#endif // KARNAUGHWINDOW_H
