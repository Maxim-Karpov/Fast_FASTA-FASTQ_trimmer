# Overview
Quickly trim your FASTA/FASTQ sequences a set number of basepairs from left, right, or both ends of the sequence.

## Manual
```
Input requires all 4 arguments:
  -i    input file
  -t    trim mode (both|left|right)
  -tl   trim length - number of basepairs to trim from both, left, or right sides of the sequences
  -ft   file type (fasta|fastq)
  ```

## Notes
- For FASTQ files, the software won't work if the sequences are shorter than 60bp or if the sequence names are longer than 60 characters. You can manually edit this quantity and rebuild the binary with g++ if required.
