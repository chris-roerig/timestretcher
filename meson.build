project('timestretch', 'cpp',
    version: '0.1.0',
    default_options: ['cpp_std=c++17'])

soundtouch_dep = dependency('soundtouch')
sndfile_dep = dependency('sndfile')

executable('timestretch',
    sources: ['src/main.cpp', 'src/TimeStretcher.cpp'],
    include_directories: 'include',
    dependencies: [soundtouch_dep, sndfile_dep]
)

