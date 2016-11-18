# basic source code CMakeLists.txt

art_make_library( LIBRARY_NAME  ub_PMTAna
                  SOURCE        PMTAna.cxx
                  LIBRARIES
                             ${ROOT_BASIC_LIB_LIST}
                             lardataobj_RawData
)


install_headers()
install_source()
