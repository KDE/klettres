public:
  static QString defaultLanguage();
  static void setLanguages(const QStringList &languages) 
  {
    Prefs::self()->m_languages = languages;
  }

  static void setLanguageNumber(int i)
  {
    setLanguage(Prefs::self()->m_languages[i]);
  }
  static int languageNumber()
  {
    int i = Prefs::self()->m_languages.findIndex(language());
    if (i != -1)
      return i;
    i = Prefs::self()->m_languages.findIndex(defaultLanguage());
    if (i != -1)
      return i;
    i = Prefs::self()->m_languages.findIndex("en");
    if (i != -1)
      return i;

    return 0; 
  }
  QStringList m_languages;
