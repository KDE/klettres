/*
    Copyright (C) SPDX-FileCopyrightText: 2007 Pino Toscano <pino@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KLTHEME_H
#define KLTHEME_H
#include <QSize>
#include <QColor>
#include <QRect>

class KLTheme
{
public:
    KLTheme();
    virtual ~KLTheme();


    virtual QString name() const = 0;
    virtual QString uiName() const = 0;
    virtual QString svgFileName() const = 0;
    ///returns the color for displaying the letter/syllable
    virtual QColor letterColor() const = 0;
    ///returns the color for the background of the LineEdit box
    virtual QColor backgroundInputColor() const = 0;
    ///returns the color for the letter in the LineEdit box
    virtual QColor letterInputColor() const = 0;
    virtual QRect wordRect(const QSize& windowsize) const = 0;
    virtual QRect inputRect(const QSize& windowsize) const = 0;
};

class KLThemeFactory
{
public:
    static KLThemeFactory* instance();
    ~KLThemeFactory();

    KLTheme* buildTheme(int id) const;
    QStringList themeList() const;

private:
    KLThemeFactory();
};

#endif
