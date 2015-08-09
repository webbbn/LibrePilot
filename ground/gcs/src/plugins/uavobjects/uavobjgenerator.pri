UAVOBJ_INIT_CPP = uavobjectsinit.cpp
UAVOBJ_INIT_CPP_TEMPLATE = $${UAVOBJ_INIT_CPP}.template

uavobjgenerator.input = UAVOBJS
uavobjgenerator.commands = $$shell_path($${UAVOBJGENERATOR}) -gcs $${UAVOBJ_XML_DIR} $${UAVOBJ_ROOT_DIR} ${QMAKE_FILE_BASE}
silent:uavobjgenerator.commands = @echo uavobjgenerator -gcs && $${uavobjgenerator.commands}
uavobjgenerator_header.depends = $${UAVOBJ_INIT_CPP_TEMPLATE}
uavobjgenerator.output = $${UAVOBJ_INIT_CPP}
uavobjgenerator.variable_out = SOURCES
uavobjgenerator.CONFIG += combine

QMAKE_EXTRA_COMPILERS += uavobjgenerator

uavobjgenerator_header.input = UAVOBJS
# We don't want any commands here because uavobjgenerator also creates .cpp, but if command is empty no rules are created
uavobjgenerator_header.commands = $$escape_expand(\\n)
uavobjgenerator_header.depends = $${UAVOBJ_INIT_CPP}
uavobjgenerator_header.output = ${QMAKE_FILE_BASE}.h # Actually generated by uavobjgenerator for this depends
uavobjgenerator_header.variable_out = UAVOBJS_HEADERS

QMAKE_EXTRA_COMPILERS += uavobjgenerator_header

uavobjgenerator_source.input = UAVOBJS
# We don't want any commands here because uavobjgenerator also creates .cpp, but if command is empty no rules are created
uavobjgenerator_source.commands = $$escape_expand(\\n)
uavobjgenerator_source.depends = $${UAVOBJ_INIT_CPP}
uavobjgenerator_source.output = ${QMAKE_FILE_BASE}.cpp # Actually generated by uavobjgenerator for this depends
uavobjgenerator_source.variable_out = SOURCES

QMAKE_EXTRA_COMPILERS += uavobjgenerator_source

# Do our own moc without moc_verify because the files aren't generated when verified
load(moc)
uavobjgenerator_moc.commands = $$moc_header.commands
uavobjgenerator_moc.output = $$moc_header.output
uavobjgenerator_moc.input = UAVOBJS_HEADERS
uavobjgenerator_moc.variable_out = GENERATED_SOURCES

QMAKE_EXTRA_COMPILERS += uavobjgenerator_moc