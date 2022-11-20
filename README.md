# Ache

Run-of-the-mill brain fuck interpreter.

## Brain Fuck

Brainfuck is a minimalistic esoteric programming language created by Urban Müller in 1993.

[Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)

Consist of eight operators

```mermaid
graph LR
    OpenFile --> In
    subgraph repeat
    In{Read Char} --> |>|Advance[Advance to the next cell]
    In --> |<|Regress[Regress to the previous cell]
    In --> |+|Increment[Increment Cell By One]
    In --> |-|Decrement[Decrement Cell By One]
    In --> |.|Write[Write Cell to Stdout]
    In --> |,|Read[Read Stdin into Cell]
    In --> |"["|Open[Open Loop Block] --> Check{Cell Not Zero?}
    In --> |"]"|Close[Close Loop Block] --> Check
    Check --true--> Stay[Stay in Loop Block]
    Check --false--> Leave[Leave Loop Block]
    end
    In --> |eof|Exit
```

## Build

```bash
g++ -std=c++14 -o ache src/ache.cpp
```

## Run

```bash
./ache brainfuck_samples/hello.bf
```

## License

[MIT](LICENSE.md)