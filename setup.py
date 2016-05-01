from distutils.core import setup, Extension

ext = Extension('jade',
    sources=['python.c', 'src/jade.c'],
    extra_compile_args=['-O3', '-std=c99', '-Ofast'],
    extra_link_args=["-s"],
    language="c",
)

setup(
    name='jade',
    author='S-YOU', author_email='S-YOU@users.noreply.github.com',
    version='0.0.5',
    url='https://github.com/S-YOU/jade',
    download_url='https://github.com/S-YOU/jade/tarball/master',
    ext_modules=[ext]
)
