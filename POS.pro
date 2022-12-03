QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DB/ADatabase.cpp \
    DB/Cart.cpp \
    DB/Products.cpp \
    POS/Product.cpp \
    POS/UI/Box/ATextBox.cpp \
    POS/UI/Button/AImageButton.cpp \
    POS/UI/Button/ATextButton.cpp \
    POS/UI/Button/CustomImage.cpp \
    POS/UI/Button/CustomText.cpp \
    POS/UI/ErrorNotification.cpp \
    POS/UI/ProductContainer.cpp \
    POS/UI/Screen/Home.cpp \
    POS/UI/VirtualKeyPad.cpp \
    POS/UI/Window.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    DB/ADatabase.hpp \
    DB/Cart.hpp \
    DB/Products.hpp \
    POS/Product.hpp \
    POS/UI/Box/ATextBox.hpp \
    POS/UI/Button/AImageButton.hpp \
    POS/UI/Button/ATextButton.hpp \
    POS/UI/Button/CustomImage.hpp \
    POS/UI/Button/CustomText.hpp \
    POS/UI/ErrorNotification.hpp \
    POS/UI/ProductContainer.hpp \
    POS/UI/ProductContainer.impl.hpp \
    POS/UI/Screen/Home.hpp \
    POS/UI/VirtualKeyPad.hpp \
    POS/UI/Window.hpp \
    pch.hpp \
    widget.h

FORMS += \
    widget.ui

TRANSLATIONS += \
    POS_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    assets/icon/add.png \
    assets/icon/addFunds.png \
    assets/icon/clear.png \
    assets/icon/create.png \
    assets/icon/exit.png \
    assets/icon/load.png \
    assets/icon/old/add.png \
    assets/icon/old/addFunds.png \
    assets/icon/old/clear.png \
    assets/icon/old/create.png \
    assets/icon/old/exit.png \
    assets/icon/old/load.png \
    assets/icon/old/pay.png \
    assets/icon/old/remove.png \
    assets/icon/old/removeFromDB.png \
    assets/icon/old/save.png \
    assets/icon/old/search.png \
    assets/icon/pay.png \
    assets/icon/remove.png \
    assets/icon/removeFromDB.png \
    assets/icon/save.png \
    assets/icon/search.png \
    database/Products.csv \
    database/cart/Cart1.csv \
    database/cart/Cart2.csv \
    database/cart/Cart3.csv
