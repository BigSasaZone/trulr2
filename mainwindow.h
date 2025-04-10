#pragma once

// Qt заголовки
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialog>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QInputDialog>

// Пользовательские заголовки
#include "sequence.h"
#include "array_sequence.h"
#include "link_sequence.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Метод для обновления отображения sequence
    template<typename T>
    void updateSequenceDisplay(const Sequence<T>* sequence);

private slots:
    void createNewSequence();
    void appendItem();
    void prependItem();
    void insertAtIndex();
    void getAtIndex();
    void getFirst();
    void getLast();
    void getSubsequence();
    void concatenate();

private:
    Ui::MainWindow *ui;
    QListWidget* listWidget;
    QLabel* sizeLabel;
    Sequence<int>* currentSequence;  // Используем int для примера
    void createButtons();
};
