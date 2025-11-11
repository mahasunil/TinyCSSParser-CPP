# TinyCSSParser-CPP
A minimal CSS parser in C++ for learning purpose. Parses CSS into structured objects (Rules and Declarations) with modern C++ practices.

## Overview
This project is tiny css parser written in C++. It parses CSS strings into structured objects.
 - 'Rule': Repersents a CSS selector and its declarations.
 - 'Declaration': Represents a single CSS property and value pair.

The main goal is educational:
- Learn how to parse text using C++.
- Understand object-oriented modeling for CSS structures.
- Practice C++ features like 'std::vector', 'std::move', and 'stringstream'.

## Features
- Parse CSS selectors and their declarations.
- Handle simple CSS syntax with one declaration per line.
- Store parsed data in C++ objects ('Rule' and 'Declaration').
- Print the parsed structure in a human-readable format.
- Uses modern C++ 'move semantics' for efficiency.

## Planned Features
- Support for CSS comments and ignoring them during parsing.
- Support for nested rules and media queries.
- Error handling for malformed CSS.
- Extend parser to handle pseudo-classes and pseudo-elements.

### Sample CSS Input
   body{
            background:gray;
            padding:10px;
        }
        h1{
            font-size:30px;
            color:gray;
        }
        p{
            color:black;
            font-size:20px;
        }
        h2.highlight{
            background:yellow;
            padding:10px;
            border-radius:10px;
        }
        div.note{
            height:150px;
            padding:10px;
            background:blue;
        }

### Parser Output:
Selector: body
  background: gray
  padding: 10px

Selector: h1
  font-size: 30px
  color: gray

Selector: p
  color: black
  font-size: 20px

Selector: h2.highlight
  background: yellow
  padding: 10px
  border-radius: 10px

Selector: div.note
  height: 150px
  padding: 10px
  background: blue


