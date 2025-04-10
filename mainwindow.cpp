#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "link_sequence.h"
#include "array_sequence.h"
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>
#include <QPushButton>
#include <QDialog>
#include <QRadioButton>
#include <QTimer>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QLineEdit>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), currentSequence(nullptr) {
    // Создание центрального виджета
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // Создание метки для отображения размера
    sizeLabel = new QLabel(this);
    mainLayout->addWidget(sizeLabel);
    
    // Создание списка для отображения элементов
    listWidget = new QListWidget(this);
    mainLayout->addWidget(listWidget);
    
    // Создание контейнера для кнопок
    QWidget* buttonContainer = new QWidget(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);
    
    // Создание кнопок для операций
    QPushButton* appendButton = new QPushButton("Append", this);
    QPushButton* prependButton = new QPushButton("Prepend", this);
    QPushButton* insertAtButton = new QPushButton("Insert At", this);
    QPushButton* getAtButton = new QPushButton("Get At", this);
    QPushButton* getFirstButton = new QPushButton("Get First", this);
    QPushButton* getLastButton = new QPushButton("Get Last", this);
    QPushButton* getSubsequenceButton = new QPushButton("Get Subsequence", this);
    QPushButton* concatenateButton = new QPushButton("Concatenate", this);

    // Добавление кнопок в layout
    buttonLayout->addWidget(appendButton);
    buttonLayout->addWidget(prependButton);
    buttonLayout->addWidget(insertAtButton);
    buttonLayout->addWidget(getAtButton);
    buttonLayout->addWidget(getFirstButton);
    buttonLayout->addWidget(getLastButton);
    buttonLayout->addWidget(getSubsequenceButton);
    buttonLayout->addWidget(concatenateButton);

    // Подключение сигналов кнопок к слотам
    connect(appendButton, &QPushButton::clicked, this, &MainWindow::appendItem);
    connect(prependButton, &QPushButton::clicked, this, &MainWindow::prependItem);
    connect(insertAtButton, &QPushButton::clicked, this, &MainWindow::insertAtIndex);
    connect(getAtButton, &QPushButton::clicked, this, &MainWindow::getAtIndex);
    connect(getFirstButton, &QPushButton::clicked, this, &MainWindow::getFirst);
    connect(getLastButton, &QPushButton::clicked, this, &MainWindow::getLast);
    connect(getSubsequenceButton, &QPushButton::clicked, this, &MainWindow::getSubsequence);
    connect(concatenateButton, &QPushButton::clicked, this, &MainWindow::concatenate);

    mainLayout->addWidget(buttonContainer);
    
    // Установка центрального виджета
    setCentralWidget(centralWidget);

    // Создание меню бара
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Создание меню "Файл"
    QMenu *fileMenu = menuBar->addMenu(tr("&Файл"));

    // Добавление действия "Создать последовательность" в меню "Файл"
    QAction *newSequenceAction = fileMenu->addAction(tr("Создать последовательность"));
    connect(newSequenceAction, &QAction::triggered, this, &MainWindow::createNewSequence);

    // Добавление действия "Выход" в меню "Файл"
    QAction *exitAction = fileMenu->addAction(tr("Выход"));
    connect(exitAction, &QAction::triggered, this, &QApplication::quit);

    // Автоматически открываем диалог создания последовательности при запуске
    QTimer::singleShot(0, this, &MainWindow::createNewSequence);

    // Создание меню "Правка"
    QMenu *editMenu = menuBar->addMenu(tr("&Правка"));
    // Здесь можно добавить действия для меню "Правка"

    // Создание меню "Справка"
    QMenu *helpMenu = menuBar->addMenu(tr("&Справка"));
    // Здесь можно добавить действия для меню "Справка"
}

void MainWindow::createNewSequence() {
    // Создание диалогового окна
    QDialog dialog(this);
    dialog.setWindowTitle("Создание новой последовательности");
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // Создание радио-кнопок для выбора типа последовательности
    QRadioButton* arrayButton = new QRadioButton("Array Sequence", &dialog);
    QRadioButton* linkedButton = new QRadioButton("Linked Sequence", &dialog);
    arrayButton->setChecked(true);  // По умолчанию выбран Array Sequence
    
    layout->addWidget(arrayButton);
    layout->addWidget(linkedButton);
    
    // Кнопки подтверждения
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    // Показываем диалог и ждем ответа
    if (dialog.exec() == QDialog::Accepted) {
        // Удаляем старую последовательность, если она существует
        if (currentSequence) {
            delete currentSequence;
        }
        
        // Создаем новую пустую последовательность выбранного типа
        if (arrayButton->isChecked()) {
            currentSequence = new ArraySequence<int>();
        } else {
            currentSequence = new LinkSequence<int>();
        }
        
        // Обновляем отображение пустой последовательности
        updateSequenceDisplay(currentSequence);
    }
}

template<typename T>
void MainWindow::updateSequenceDisplay(const Sequence<T>* sequence) {
    if (!sequence) return;
    
    // Очистка списка
    listWidget->clear();
    
    // Обновление метки с размером
    sizeLabel->setText(QString("Размер последовательности: %1").arg(sequence->GetLenght()));
    
    // Добавление элементов в список
    for(size_t i = 0; i < sequence->GetLenght(); i++) {
        QString itemText = QString("Элемент %1: %2").arg(i).arg(sequence->Get(i));
        listWidget->addItem(itemText);
    }
}

// Реализация слотов для кнопок
void MainWindow::appendItem() {
    if (!currentSequence) return;
    
    bool ok;
    int value = QInputDialog::getInt(this, "Append Item", 
                                   "Enter value to append:", 0, 
                                   INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        currentSequence->Append(value);
        updateSequenceDisplay(currentSequence);
    }
}

void MainWindow::prependItem() {
    if (!currentSequence) return;
    
    bool ok;
    int value = QInputDialog::getInt(this, "Prepend Item", 
                                   "Enter value to prepend:", 0, 
                                   INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        currentSequence->Prepend(value);
        updateSequenceDisplay(currentSequence);
    }
}

void MainWindow::insertAtIndex() {
    if (!currentSequence) return;
    
    bool ok;
    int index = QInputDialog::getInt(this, "Insert At Index", 
                                   "Enter index:", 0, 
                                   0, currentSequence->GetLenght(), 1, &ok);
    if (!ok) return;
    
    int value = QInputDialog::getInt(this, "Insert Value", 
                                   "Enter value:", 0, 
                                   INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        currentSequence->InsertAt(value, index);
        updateSequenceDisplay(currentSequence);
    }
}

void MainWindow::getAtIndex() {
    if (!currentSequence) return;
    
    bool ok;
    int index = QInputDialog::getInt(this, "Get At Index", 
                                   "Enter index:", 0, 
                                   0, currentSequence->GetLenght() - 1, 1, &ok);
    if (ok) {
        int value = currentSequence->Get(index);
        QMessageBox::information(this, "Value at Index", 
                               QString("Value at index %1: %2").arg(index).arg(value));
    }
}

void MainWindow::getFirst() {
    if (!currentSequence || currentSequence->GetLenght() == 0) return;
    
    int value = currentSequence->GetFirst();
    QMessageBox::information(this, "First Element", 
                           QString("First element: %1").arg(value));
}

void MainWindow::getLast() {
    if (!currentSequence || currentSequence->GetLenght() == 0) return;
    
    int value = currentSequence->GetLast();
    QMessageBox::information(this, "Last Element", 
                           QString("Last element: %1").arg(value));
}

void MainWindow::getSubsequence() {
    if (!currentSequence) return;
    
    bool ok;
    int startIndex = QInputDialog::getInt(this, "Get Subsequence", 
                                        "Enter start index:", 0, 
                                        0, currentSequence->GetLenght() - 1, 1, &ok);
    if (!ok) return;
    
    int endIndex = QInputDialog::getInt(this, "Get Subsequence", 
                                      "Enter end index:", startIndex, 
                                      startIndex, currentSequence->GetLenght() - 1, 1, &ok);
    if (ok) {
        // Получаем новую подпоследовательность
        Sequence<int>* subsequence = currentSequence->GetSubsequence(startIndex, endIndex);
        
        // Удаляем старую последовательность
        delete currentSequence;
        
        // Заменяем указатель на новую последовательность
        currentSequence = subsequence;
        
        // Обновляем отображение
        updateSequenceDisplay(currentSequence);
    }
}

void MainWindow::concatenate() {
    if (!currentSequence) return;
    
    QDialog dialog(this);
    dialog.setWindowTitle("Create sequence to concatenate");
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    QLineEdit* input = new QLineEdit(&dialog);
    layout->addWidget(new QLabel("Enter numbers separated by spaces:"));
    layout->addWidget(input);
    
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    layout->addWidget(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        QStringList numbers = input->text().split(" ", Qt::SkipEmptyParts);
        Sequence<int>* secondSequence;
        
        if (dynamic_cast<ArraySequence<int>*>(currentSequence)) {
            secondSequence = new ArraySequence<int>();
        } else {
            secondSequence = new LinkSequence<int>();
        }
        
        for (const QString& num : numbers) {
            secondSequence->Append(num.toInt());
        }
        
        Sequence<int>* result = currentSequence->Concat(*currentSequence, *secondSequence);
        delete currentSequence;
        delete secondSequence;
        currentSequence = result;
        updateSequenceDisplay(currentSequence);
    }
}

MainWindow::~MainWindow() {
    if (currentSequence) {
        delete currentSequence;
    }
}

