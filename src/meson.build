cxx = meson.get_compiler('cpp')

torch_sub_proj = subproject('libtorch', required : false)

if not torch_sub_proj.found()
    message('lib torch not founded, try found by handmade')
    LIB_TORCH_PATH = meson.project_source_root() / 'subprojects' / 'libtorch'
    LIB_TORCH_LIB_PATH = LIB_TORCH_PATH / 'lib'
    LIB_TORCH_INCL_PATH_ABSOLUTE = LIB_TORCH_PATH / 'include'
    LIB_TORCH_INCL_PATH = '..' / 'subprojects' / 'libtorch' / 'include'
    LIB_TORCH_INCL_PATH_API = LIB_TORCH_INCL_PATH / 'torch' / 'csrc' / 'api' / 'include'
    LIB_TORCH_INCL_PATH_ATEN = LIB_TORCH_INCL_PATH / 'ATen'
    LIB_TORCH_INCL_PATH_C10 = LIB_TORCH_INCL_PATH / 'c10'

########## prepare lib for torch ##########
    python_exe = find_program('python3', 'python')
    message('finded python')
    
    params = files(meson.project_source_root() / 'scripts' / 'torch_change_lib_name.py')

    r = run_command(python_exe, params, LIB_TORCH_LIB_PATH)
    if r.returncode() != 0
        error('Error change .so.1 name')
    endif


    LIB_TORCH_INCLUDE_LIST = [
            LIB_TORCH_INCL_PATH, LIB_TORCH_INCL_PATH_API, LIB_TORCH_INCL_PATH_ATEN, LIB_TORCH_INCL_PATH_C10
        ]

    lib_torch_list = [
        'asmjit',
        'backend_with_compiler',
        'benchmark',
        'benchmark_main',
        'c10',
        'caffe2_protos',
        'clog',
        'cpuinfo',
        'cpuinfo_internals',
        'dnnl',
        'fbgemm',
        'fmt',
        'foxi_loader',
        'gloo',
        'gmock',
        'gmock_main',
        'gomp-52f2fd74',
        'gtest',
        'gtest_main',
        'ittnotify',
        'jitbackend_test',
        'kineto',
        'nnapi_backend',
        'nnpack',
        'nnpack_reference_layers',
        'onnx',
        'onnx_proto',
        'protobuf',
        'protobuf-lite',
        'protoc',
        'pthreadpool',
        'pytorch_qnnpack',
        'qnnpack',
        'shm',
        'tensorpipe',
        'tensorpipe_uv',
        'torchbind_test',
        'torch_cpu',
        'torch_global_deps',
        'torch_python',
        'torch',
        'unbox_lib',
        'XNNPACK',
    ]
    deps = []
    foreach lib_name : lib_torch_list 
        deps += cxx.find_library(lib_name, dirs : [LIB_TORCH_LIB_PATH])
    endforeach

    torch_deps = declare_dependency(
        dependencies : deps,
        include_directories : include_directories(LIB_TORCH_INCLUDE_LIST),
    )
endif

fmt_deps = dependency('fmt', method: 'pkg-config')
boost_deps = dependency('boost', method: 'pkg-config')

qt_version = 'qt6'
qt = import(qt_version)
qt_deps = dependency(qt_version, modules : ['Core', 'Gui', 'Widgets'], static : true, required : true)


inc = include_directories('.')

subdir('hello')

cpp_nn_header_files = []
cpp_nn_files = [
    files('main.cpp')
]

cpp_nn_deps = [
    hello_dep,
    torch_deps,
    fmt_deps,
    boost_deps,
    qt_deps,
]

cpp_nn_files += qt.preprocess(
  moc_headers  : cpp_nn_header_files,
  dependencies : cpp_nn_deps,
)

cpp_nn_exe = executable(
    'cpp_nn',
    sources      : cpp_nn_files,
    dependencies : cpp_nn_deps,
)
