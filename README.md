# Package Comparison

The program receives 2 branch names as input, receives a list of their packages and generates a JSON file:
```json
{
    "branch1_except_branch2": [
        {   },
    ],
    "branch2_except_branch1": [
        {   },
    ],
    "branch1_newer_branch2": [
        {   },
    ]
}
```

## Installation
```bash
su -
apt-get update
apt-get install git
apt-get install gcc-c++
apt-get install rapidjson
apt-get install curl-devel
```

```bash
git clone https://github.com/42ghost/test_alt.git
cd test_alt
make
```

installing a shared library
```bash
su
make install
su -
ldconfig
```

## Usage

```bash
./main branchname1 branchname2
```

## Notes
1. The program performs 2 a GET request to the https://rdb.altlinux.org/api/export/branch_binary_packages/{branchname_N}.
2. Compares packages of branches and generates the final file {branchname1}_{branchname2}.json
