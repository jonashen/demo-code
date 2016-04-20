#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QWidget>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "../lib/all.h"

class OutOfBounds : public std::exception {
private:
    int index;
public:
    OutOfBounds(int i) {
        index = i;
    }
    std::string what() {
        std::string message = "OutOfBounds";
        return message;
    }
};

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

private slots:
	bool showPopup();
    void Error();
    void programStep();
    void programCont();
    void programNext();
    void programInsp();
    void programBrke();
    void lineSelect(int ls);
    void fileIsValid();
    void updateInspect();

private:
	// Layout
	QGridLayout* overallLayout;
    QHBoxLayout* naList;
    QHBoxLayout* ndList;
    QHBoxLayout* vaList;
    QHBoxLayout* vdList;
    QVBoxLayout* promptLayout;
    QVBoxLayout* inspectLayout;
    
    // Widget
    QListWidget* codeLines;
    QListWidget* currLine;
    QListWidget* inspectList;
    
    QListWidget* naNameList;
    QListWidget* naValList;
    QListWidget* ndNameList;
    QListWidget* ndValList;
    QListWidget* vaNameList;
    QListWidget* vaValList;
    QListWidget* vdNameList;
    QListWidget* vdValList;
    
    // Dialog
    QDialog* dialog;
    QDialog* iDialog;
    QDialogButtonBox* buttonBox;

	// Result label
	QLabel* prompt;
    QLabel* sortBy;
    
    // QLineEdit
    QLineEdit* fileInput;
    
    //QComboBox
    QComboBox* updateCB;

	// Buttons
	QPushButton* contButton;
    QPushButton* brkeButton;
    QPushButton* stepButton;
    QPushButton* nextButton;
    QPushButton* inspButton;
    QPushButton* exitButton;
    QPushButton* hideButton;
    QPushButton* updtButton;

    
    int promptAnswer; // value from closing filename popup
    int errorVal; // value from closing error popup
    std::string filename; // filename input from user
    int lineSelected; // used to determine breakpoints
    
    std::vector<std::string> linesOfCode; // lines of code
    ProgramState * p_state; // state of the program
    std::vector<Statement *> program; // program itself
    
};
