# htslib-experiments
Strictly experimental code

On MacOS

1. Build htslib/bcftools from master
```
brew install xz gsl
git clone https://github.com/samtools/htslib.git
git clone https://github.com/samtools/bcftools.git # Optional, but nice to have
./configure
make
```

2. clang++ -I/path/to/htslib -L/path/to/htslib -lhts -lbz2 -llzma -lcurl -lz -g read_from_bam.cc

