public:
  QStringList languages();
  static void setLanguageNumber(int i)
  {
    setLanguage(Prefs::self()->m_languages[i]);
  }
  static int languageNumber()
  {
qWarning("Lnaguages: %s", Prefs::self()->m_languages.join(":").latin1());
    int i = Prefs::self()->m_languages.findIndex(language());
    if (i == -1)
      return 0;
    return i;
  }

private: 
  QStringList m_languages;
  QString m_defaultLanguage;
