hello_headers = ['hello.hpp']
hello_sources = ['hello.cpp']

hello_lib = static_library('hello',
				include_directories : inc,
				install : true,
				sources: [hello_headers, hello_sources],
				dependencies: [
						torch_deps,
						fmt_deps,
						boost_deps,
					]
				)

hello_dep = declare_dependency(include_directories : inc,
					   link_with : hello_lib)

install_headers(hello_headers,
		 subdir : 'hello')

