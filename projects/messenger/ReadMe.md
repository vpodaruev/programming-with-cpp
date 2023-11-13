## Notes for Windows user

### Download Boost libraries

- use [direct link](https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.7z)
- or get latest version from the official [web-site](https://www.boost.org)


### Unpack and install

`Boost.Asio` is a header-only library. So, just unpack archive and install headers without building anything else.
```sh
$ cd /path/to/boost_1_83_0
$ ./bootstrap.sh
$ ./b2 --prefix=/absolute/path/to/boost-1.83.0 --with-headers variant=release -j4 install
```


### Configure VS Code

Add to your workspace `settings.json` a hint where `CMake` should find Boost libraries.
```json
{
    "cmake.environment": {
        ...
        "BOOST_ROOT": "/absolute/path/to/boost-1.83.0"
    }
}
```
