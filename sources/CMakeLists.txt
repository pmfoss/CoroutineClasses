set( HEADER_FILES 
        CoAwaiter.h
		CoBasePromise.h
		CoGenerator.h
		CoTask.h
		CoUtility.h
		CoValueReturnPromise.h
		CoVoidReturnPromise.h
   )

install(FILES ${HEADER_FILES} DESTINATION ${INCLUDE_INSTALL_DIR})