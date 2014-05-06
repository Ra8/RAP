CONFIGDIR=config/
DOTPROFILE=RAP.pro
PROJECTMAKEFILE=.projectMakefile
DOXYFILE=Doxyfile
EXECUTABLE=RAP
SOURCEFILES=$(shell find src -name *.cpp -printf '%p ')
HEADERFILES=$(shell find src -name *.h -printf '%p ')
all:$(PROJECTMAKEFILE)
	@make -f $^ -s

$(PROJECTMAKEFILE):$(DOTPROFILE) $(SOURCEFILES) $(HEADERFILES)
	@qmake-qt4 -o $@ $<

run:all
	@./$(EXECUTABLE)
doc:
	@doxygen $(DOXYFILE) 2>0 >0
	@rm 0
print:
	@echo $(CONFIGDIR)
	@echo $(DOTPROFILE)
	@echo $(PROJECTMAKEFILE)
zip:
	@rm ../project-assigment.zip -f
	@7z a -tzip ../project-assigment.zip Doxyfile RAP.pro img makefile maps src
	@echo
	@echo
	@echo "project-assigment.zip created on parent folder"
	@echo
clean:
	@rm moc* -f -r
	@rm *.o -f -r
	@rm $(PROJECTMAKEFILE) -f
	@rm $(EXECUTABLE) -f
	@rm doc -f -r
	@rm .obj -f -r
	@rm .qrc -f -r
	@rm .moc -f -r
	@rm .ui -f -r
	@rm .cpps -f
	@rm .hs -f
	@rm .dirs -f
