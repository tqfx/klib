BUILD = build

ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
else
CMAKE_G = -G "Unix Makefiles"
endif

.PHONY: $(BUILD) format clean

$(BUILD):
	@cmake -S . -B $@ $(CMAKE_G) -DCMAKE_BUILD_TYPE="Release" && cd $@ && make -j

clean:
	@-git clean -f -d -X

format: klib test
	@-find $^ -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
