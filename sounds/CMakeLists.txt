set(langdir fr en ar cs da de en_GB es he hu id it lt ml nb nds nl nn pt_BR ru tn uk)
set(sublangdir alpha syllab )
foreach (_langcurrentdir ${langdir})
    file(GLOB _xmlfile "${_langcurrentdir}/*.xml" )
    install(FILES ${_xmlfile} DESTINATION ${KDE_INSTALL_DATADIR}/klettres/${_langcurrentdir})
    foreach(_sublangcurrentdir ${sublangdir})
        file(GLOB _oggfile "${_langcurrentdir}/${_sublangcurrentdir}/*.ogg" )
        install(FILES ${_oggfile} DESTINATION ${KDE_INSTALL_DATADIR}/klettres/${_langcurrentdir}/${_sublangcurrentdir})
    endforeach(_sublangcurrentdir ${sublangdir} )
endforeach(_langcurrentdir ${langdir})

