BUILD = build

ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
else
CMAKE_G = -G "Unix Makefiles"
endif

all:$(BUILD)
	@cd $(BUILD) && cmake .. $(CMAKE_G) -DCMAKE_BUILD_TYPE="Release" && make -j

$(BUILD):
	@-mkdir $@

.PHONY: format clean
format: klib test
	@-find $^ -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
clean:
	@-git clean -f -d -X
