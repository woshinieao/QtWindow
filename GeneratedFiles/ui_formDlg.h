/********************************************************************************
** Form generated from reading UI file 'formDlg.ui'
**
** Created: Wed Oct 5 15:43:07 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDLG_H
#define UI_FORMDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FormDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *leId;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *leName;
    QLabel *label_4;
    QLineEdit *lePhone;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FormDlg)
    {
        if (FormDlg->objectName().isEmpty())
            FormDlg->setObjectName(QString::fromUtf8("FormDlg"));
        FormDlg->resize(491, 378);
        verticalLayout_2 = new QVBoxLayout(FormDlg);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(FormDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        leId = new QLineEdit(FormDlg);
        leId->setObjectName(QString::fromUtf8("leId"));
        leId->setMinimumSize(QSize(0, 40));
        leId->setMaximumSize(QSize(16777215, 16777215));
        leId->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\226\260\345\256\213\344\275\223\";"));

        horizontalLayout->addWidget(leId);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(FormDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        leName = new QLineEdit(FormDlg);
        leName->setObjectName(QString::fromUtf8("leName"));
        leName->setMinimumSize(QSize(0, 40));
        leName->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(leName);

        label_4 = new QLabel(FormDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lePhone = new QLineEdit(FormDlg);
        lePhone->setObjectName(QString::fromUtf8("lePhone"));
        lePhone->setMinimumSize(QSize(0, 40));
        lePhone->setMaximumSize(QSize(16777215, 16777215));
        lePhone->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\226\260\345\256\213\344\275\223\";"));

        horizontalLayout_2->addWidget(lePhone);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(FormDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(FormDlg);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(lineEdit);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 4);

        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(FormDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        verticalLayout_2->addWidget(buttonBox);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 5);

        retranslateUi(FormDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), FormDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FormDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(FormDlg);
    } // setupUi

    void retranslateUi(QDialog *FormDlg)
    {
        FormDlg->setWindowTitle(QApplication::translate("FormDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormDlg", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt;\">\345\215\225\345\217\267\357\274\232</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        leId->setText(QString());
        label_3->setText(QApplication::translate("FormDlg", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt;\">\350\201\224\347\263\273\344\272\272\357\274\232</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        leName->setText(QString());
        label_4->setText(QApplication::translate("FormDlg", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt;\">\347\224\265\350\257\235\357\274\232</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormDlg", "<html><head/><body><p><span style=\" font-size:12pt;\">\346\217\217\350\277\260:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormDlg: public Ui_FormDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDLG_H
