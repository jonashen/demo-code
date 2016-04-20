#include "main_window.h"

using namespace std;

// Facile
void parseProgram(istream &inf, vector<Statement *> & program, vector<string>& linesOfCode);
Statement * parseLine(string line);
void interpretProgram(istream& inf, vector<string>& linesOfCode, vector<Statement *>& program);

MainWindow::MainWindow()
{
    // Overall layout
    bool test = showPopup();

    exitButton = new QPushButton("Exit"); // create exit button first to press it
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
    
    if (!test)
    {
        exit(EXIT_FAILURE); // simulates pressing exit
    }
    
    ifstream infile(filename.c_str());
    
    interpretProgram(infile, linesOfCode, program); // has code lines and program itself
    
    // Create a program state with size of vector length - 1 (due to NULL)
    p_state = new ProgramState( program.size() - 1 );
    
    
    overallLayout = new QGridLayout();
    
    codeLines = new QListWidget(); // adding the lines of code
    for (unsigned int i = 0; i < linesOfCode.size(); i++)
        codeLines->addItem(QString::fromStdString(linesOfCode[i]) );
    
    currLine = new QListWidget(); // current line
    
    for (unsigned int i = 0; i < linesOfCode.size(); i++)
        currLine->addItem(QString::fromStdString(""));
    
    currLine->setMaximumWidth(50);
    
    overallLayout->addWidget(currLine, 0, 0, 6, 1);
    //connect(codeLines, SIGNAL(currentRowChanged(int)), this, SLOT() );
    overallLayout->addWidget(codeLines, 0, 1, 6, 3);
    // Adding all the buttons
    brkeButton = new QPushButton("Break");
    contButton = new QPushButton("Continue");
    stepButton = new QPushButton("Step");
    nextButton = new QPushButton("Next");
    inspButton = new QPushButton("Inspect");
    
    connect(codeLines, SIGNAL(currentRowChanged(int)), this, SLOT(lineSelect(int))); // saves selected line
    
    // Connecting the buttons
    connect(brkeButton, SIGNAL(clicked()), this, SLOT(programBrke()) );
    connect(contButton, SIGNAL(clicked()), this, SLOT(programCont()) );
    connect(stepButton, SIGNAL(clicked()), this, SLOT(programStep()) );
    connect(nextButton, SIGNAL(clicked()), this, SLOT(programNext()) );
    connect(inspButton, SIGNAL(clicked()), this, SLOT(programInsp()) );
    
    // row, col, rowSpan, colSpan
    overallLayout->addWidget(brkeButton, 0, 4, 1, 2);
    overallLayout->addWidget(contButton, 1, 4, 1, 2);
    overallLayout->addWidget(stepButton, 2, 4, 1, 2);
    overallLayout->addWidget(nextButton, 3, 4, 1, 2);
    overallLayout->addWidget(inspButton, 4, 4, 1, 2);
    overallLayout->addWidget(exitButton, 5, 4, 1, 2);
    
    
    
    // Set overall layout
    setLayout(overallLayout);
    
}

// Destructor
MainWindow::~MainWindow()
{
    // Delete Facile
    delete p_state;
    for (unsigned int i = 1; i < program.size(); i++) // 0th element is NULL
        delete program[i];
    
    // Delete Layout
    delete overallLayout;
    delete naList;
    delete ndList;
    delete vaList;
    delete vdList;
    delete promptLayout;
    delete inspectLayout;
    
    // Delete Widget
    delete codeLines;
    delete currLine;
    delete inspectList;
    
    delete naNameList;
    delete naValList;
    delete ndNameList;
    delete ndValList;
    delete vaNameList;
    delete vaValList;
    delete vdNameList;
    delete vdValList;
    
    // Delete Dialog
    delete dialog;
    delete iDialog;
    delete buttonBox;
    
    // Delete Label
    delete prompt;
    delete sortBy;
    
    // Delete QLineEdit
    delete fileInput;
    
    //Delete QComboBox
    delete updateCB;
    
    // Delete Buttons
    delete contButton;
    delete brkeButton;
    delete stepButton;
    delete nextButton;
    delete inspButton;
    delete exitButton;
    delete hideButton;
    delete updtButton;
}

// Initial Pop-up Window
bool MainWindow::showPopup() // Initial popup prompt to type in filename
{
    dialog = new QDialog;
    
    prompt = new QLabel("Please enter a filename: ");
    
    fileInput = new QLineEdit(this);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Cancel);
    
    // accepted from dialog box
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    
    // adding to prompt layout
    promptLayout = new QVBoxLayout;
    promptLayout->addWidget(prompt);
    promptLayout->addWidget(fileInput);
    promptLayout->addWidget(buttonBox);
    
    dialog->setLayout(promptLayout);
    dialog->exec();
    
    promptAnswer = dialog->result();
    
    // save filename
    filename = fileInput->text().toStdString();
    
    if(promptAnswer == 1)
    {
        fileIsValid(); return true;
    }
    
    else return false;
}

// Checks the file until it is valid
void MainWindow::fileIsValid()
{
    ifstream infileTest(filename.c_str());
    if(!infileTest)
    {
        Error(); showPopup();
    }
}

// Error message
void MainWindow::Error()
{
    QMessageBox messageBox;
    messageBox.setFixedSize(500,200);
    messageBox.critical(0,"Error","An error has occured!");
}

// Step Button
void MainWindow::programStep()
{
    int lastLine = p_state->currLine() - 1; // saves current line
    
    // If divide by zero occurs
    if(p_state->get_zero()) // tried to divide by zero
    {
        Error(); // Error window
        p_state->set_zero(false); // sets back to false
        p_state->nextLine(); // Skips to next line
    }
    
    else if(lastLine == 0)
    {
        currLine->item(0)->setText(QString::fromStdString("*")); // first line only
        program[p_state->currLine()]->execute(p_state, cout);
        
    }
    
    else if ( p_state->currLine() == p_state->numLines() ) // we are at the last line
    {
        currLine->item(lastLine)->setText(QString::fromStdString(""));
        p_state->set_line(1);
    }
    
    else
    {
        for (unsigned int i = 0; i < linesOfCode.size(); i++)
        {
            if(currLine->item(i)->text().QString::toStdString() == "*" )
                currLine->item(i)->setText(QString::fromStdString(""));
        }
        
        currLine->item(p_state->currLine() - 1)->setText(QString::fromStdString("*")); // currline starts at 1
        program[p_state->currLine()]->execute(p_state, cout);
    }
}

// Continue Button
void MainWindow::programCont()
{
    int lastLine = p_state->currLine() - 1;
    bool breakFound = false;
    while ( !breakFound )
    {
        lastLine = p_state->currLine() - 1; // saves current line
        
        // If divide by zero occurs
        if(p_state->get_zero()) // tried to divide by zero
        {
            Error(); // Error window
            p_state->set_zero(false); // sets back to false
            p_state->nextLine(); // Skips to next line
        }
        
        else if(lastLine == 0)
        {
            currLine->item(0)->setText(QString::fromStdString("*")); // first line only
            program[p_state->currLine()]->execute(p_state, cout);
            
        }
        
        else if ( p_state->currLine() == p_state->numLines() ) // we are at the last line
        {
            currLine->item(lastLine)->setText(QString::fromStdString(""));
            p_state->set_line(1);
            break;
        }
        
        else
        {
            for (unsigned int i = 0; i < linesOfCode.size(); i++){
                if(currLine->item(i)->text().QString::toStdString() == "*" )
                    currLine->item(i)->setText(QString::fromStdString(""));
            }
            if(currLine->item(p_state->currLine() - 1)->text().QString::toStdString() == "#" ) breakFound = true;
            currLine->item(p_state->currLine() - 1)->setText(QString::fromStdString("*")); // currline starts at 1
            program[p_state->currLine()]->execute(p_state, cout);
        }
    }
}



// Next Button
void MainWindow::programNext()
{
    stringstream ss;
    string temp;
    int nextLine;
    
    ss << linesOfCode[p_state->currLine() - 1];
    ss >> temp;
    if(temp == "GOSUB")
    {
        nextLine = p_state->currLine();
        currLine->item(nextLine)->setText(QString::fromStdString("#"));
        programCont(); // acts as continue function
    }
    else
        programStep(); // acts as step function
}


 // Break Button
void MainWindow::programBrke()
{
        if(lineSelected < 0 || lineSelected >= p_state->numLines())
            Error();
        else
            currLine->item(lineSelected)->setText(QString::fromStdString("#"));
}



// Inspect Window
void MainWindow::programInsp()
{
    iDialog = new QDialog;
    
    // add the buttons
    updtButton = new QPushButton("Update");
    hideButton = new QPushButton("Hide");
    connect(updtButton, SIGNAL(clicked()), this, SLOT(updateInspect()) );
    connect(hideButton, SIGNAL(clicked()), iDialog, SLOT(hide()) );

    // vectors holding the values
    vector< pair<string, int> > nameAscend;
    vector< pair<string, int> > nameDescend;
    vector< pair<int, string> > valueAscend;
    vector< pair<int, string> > valueDescend;
    
    // pushing back into the vectors
    for (map<string,int>::iterator it = p_state->var_map()->begin(); it != p_state->var_map()->end(); ++it)
    {
        nameAscend.push_back(*it);
        nameDescend.push_back(*it);
        valueAscend.push_back(make_pair(it->second, it->first));
        valueDescend.push_back(make_pair(it->second, it->first));
    }

    // Merge sort
    AscendSort< pair<string, int> > nA; mergeSort(nameAscend, nA); // merge sort names a-z
    DescendSort< pair<string, int> > nD; mergeSort(nameDescend, nD); // merge sort names z-a
    
    AscendSort<pair<int, string> > vA; mergeSort(valueAscend, vA); // merge sort val 0-9
    DescendSort<pair<int, string> > vD; mergeSort(valueDescend, vD); // merge sort val 9-0
    
    sortBy = new QLabel("Sort by: ");
    
    // Combo Box
    updateCB = new QComboBox;
    QStringList updateList; // make a list of strings
    updateList << "Name (Ascending)" << "Name (Descending)" << "Value (Ascending)" << "Value (Descending)";
    updateCB->insertItems(0, updateList); // insert strings into combobox
    
    
    // Name Ascend
    naList = new QHBoxLayout; // horizontal layout for table
    naNameList = new QListWidget; // name of ascend sort
    naValList = new QListWidget; // values of ascend sort
    naList->addWidget(naNameList); naList->addWidget(naValList); // add tables to layout
    
    for (vector<pair<string, int> >::iterator it = nameAscend.begin(); it != nameAscend.end(); ++it)
    {
        naNameList->addItem(QString::fromStdString(it->first));
        naValList->addItem(QString::number(it->second));
    }
    
    
    // Name Descend
    ndList = new QHBoxLayout;
    ndNameList = new QListWidget;
    ndValList = new QListWidget;
    ndList->addWidget(ndNameList); ndList->addWidget(ndValList);
    
    for (vector<pair<string, int> >::iterator it = nameDescend.begin(); it != nameDescend.end(); ++it)
    {
        ndNameList->addItem(QString::fromStdString(it->first));
        ndValList->addItem(QString::number(it->second));
    }
    
    
    // Value Ascend
    vaList = new QHBoxLayout;
    vaNameList = new QListWidget;
    vaValList = new QListWidget;
    vaList->addWidget(vaNameList); vaList->addWidget(vaValList);
    
    for (vector<pair<int, string> >::iterator it = valueAscend.begin(); it != valueAscend.end(); ++it)
    {
        vaNameList->addItem(QString::fromStdString(it->second));
        vaValList->addItem(QString::number(it->first));
    }
    
    
    // Value Descend
    vdList = new QHBoxLayout;
    vdNameList = new QListWidget;
    vdValList = new QListWidget;
    vdList->addWidget(vdNameList); vdList->addWidget(vdValList);
    
    for (vector<pair<int, string> >::iterator it = valueDescend.begin(); it != valueDescend.end(); ++it)
    {
        vdNameList->addItem(QString::fromStdString(it->second));
        vdValList->addItem(QString::number(it->first));
    }
    
    // Add to Inspect layout
    inspectLayout = new QVBoxLayout;
    inspectLayout->addWidget(sortBy);
    inspectLayout->addWidget(updateCB);
    
    inspectLayout->addLayout(ndList); ndNameList->hide(); ndValList->hide();
    inspectLayout->addLayout(vaList); vaNameList->hide(); vaValList->hide();
    inspectLayout->addLayout(vdList); vdNameList->hide(); vdValList->hide();
    inspectLayout->addLayout(naList);
    
    inspectLayout->addWidget(updtButton);
    inspectLayout->addWidget(hideButton);
    
    iDialog->setLayout(inspectLayout);
    iDialog->exec();
}

// Inspect helper function
void MainWindow::updateInspect()
{
    // hide everything first
    naNameList->hide(); naValList->hide();
    ndNameList->hide(); ndValList->hide();
    vaNameList->hide(); vaValList->hide();
    vdNameList->hide(); vdValList->hide();
    
    if(updateCB->currentIndex() == 0) // Name (Ascending)
    {
        naNameList->show(); naValList->show();
    }
    
    else if(updateCB->currentIndex() == 1) // Name (Descending)
    {
        ndNameList->show(); ndValList->show();
    }
    
    else if(updateCB->currentIndex() == 2) // Value (Ascending)
    {
        vaNameList->show(); vaValList->show();
    }
    
    else if(updateCB->currentIndex() == 3) // Value (Descending)
    {
        vdNameList->show(); vdValList->show();
    }
}


void MainWindow::lineSelect(int ls) // Selected line
{
    lineSelected = ls;
}

void parseProgram(istream &inf, vector<Statement *> & program, vector<string>& linesOfCode)
{
    program.push_back(NULL);
    
    string line;
    while( ! inf.eof() )
    {
        getline(inf, line);
        linesOfCode.push_back( line );
        program.push_back( parseLine( line ) );
    }
}





Statement * parseLine(string line)
{
    Statement * statement;
    stringstream ss;
    string type;
    string var;
    int val = 0;
    
    ss << line;
    ss >> type;
    
    if ( type == "LET" ) // LET *var* *int*
    {
        ss >> var;
        ss >> val;
        // Note:  Because the project spec states that we can assume the file
        //	  contains a syntactically legal Facile program, we know that
        //	  any line that begins with "LET" will be followed by a space
        //	  and then a variable (single character) and then an integer value.
        statement = new LetStatement(var, val);
        return statement;
    }
    
    
    else if ( type == "PRINT" ) // PRINT *var*
    {
        ss >> var;
        statement = new PrintStatement(var);
        return statement;
    } // PRINT
    
    
    else if ( type == "PRINTALL" ) // PRINTALL
    {
        statement = new PrintStatement("ALL");
        return statement;
    }
    
    
    else if ( type == "ADD" ) // ADD *var* *p*
    {
        string str;
        ss >> var;
        ss >> std::ws; // eating up white space
        char c = ss.peek();
        
        if ( (c >= '0') && (c <= '9') ) // if p is an int
        {
            ss >> val;
            statement = new OperatorStatement(var, val, "ADD");
            return statement;
        }
        
        else // p is a variable
        {
            statement = new OperatorStatement(var, str, "ADD");
            return statement;
        }
        
    } // ADD
    
    
    else if ( type == "SUB" ) // SUB *var* *p*
    {
        string str;
        ss >> var;
        ss >> std::ws; // eating up white space
        char c = ss.peek();
        
        if ( (c >= '0') && (c <= '9') ) // if p is an int
        {
            ss >> val;
            statement = new OperatorStatement(var, val, "SUB");
            return statement;
        }
        
        else // p is a variable
        {
            statement = new OperatorStatement(var, str, "SUB");
            return statement;
        }
    } // SUB
    
    
    else if ( type == "MULT" ) // MULT *var* *p*
    {
        string str;
        ss >> var;
        ss >> std::ws; // eating up white space
        char c = ss.peek();
        
        if ( (c >= '0') && (c <= '9') ) // if p is an int
        {
            ss >> val;
            statement = new OperatorStatement(var, val, "MULT");
            return statement;
        }
        
        else // p is a variable
        {
            ss >> str;
            statement = new OperatorStatement(var, str, "MULT");
            return statement;
        }
    } // MULT
    
    
    else if ( type == "DIV" ) // DIV *var* *p*
    {
        string str;
        ss >> var;
        ss >> std::ws; // eating up white space
        char c = ss.peek();
        
        if ( (c >= '0') && (c <= '9') ) // if p is an int
        {
            ss >> val;
            statement = new OperatorStatement(var, val, "DIV");
            return statement;
        }
        
        else // p is a variable
        {
            statement = new OperatorStatement(var, str, "DIV");
            return statement;
        }
    } // DIV
    
    
    else if ( type == "GOTO" || type == "GOSUB") // GOTO/GOSUB *linenum*
    {
        ss >> val;
        statement = new GoStatement(val, type);
        return statement;
    }
    
    
    else if ( type == "RETURN") // RETURN
    {
        statement = new GoStatement(val, type);
        return statement;
    }
    
    
    else if ( type == "IF") // IF *var* *op* *int*/*o_var* THEN *linenum*
    {
        string op, then, o_var;
        int line;
        
        ss >> var >> op;
        ss >> std::ws; // eating up white space
        char c = ss.peek();
        
        if ( (c >= '0') && (c <= '9') ) // comparing to an int
        {
            ss >> val >> then >> line;
            statement = new IfStatement(var, op, val, line);
            return statement;
        }
        
        else // comparing to a variable
        {
            ss >> o_var >> then >> line;
            statement = new IfStatement(var, op, o_var, line);
            return statement;
        }
    }
    
    else // END or .
    {
        statement = new EndStatement();
        return statement;
    }
    
}

void interpretProgram(istream& inf, vector<string>& linesOfCode, vector<Statement *>& program)
{
    parseProgram( inf, program, linesOfCode ); // parse program, saves each line of code as well
}
