# Junqi AI

## Table of Contents
- [Background](#background)
- [Usage](#usage)
- [Status](#status)
- [Contributors](#contributors)
- [License](#license)

## Background
同济大学2020年春季人工智能的课程军旗AI的第二组(~~冠军~~)代码，使用Alpha-Beta剪枝，启发式搜索来完成，~~还有很多底层的优化~~。

## Usage
```
Game Junqi;
Junqi.Arg_Init(argc, argv); 
Chess Board;
Con.Get_Board(Board);
Movement Move =  Junqi.Search(Board, SEARCH_DEPTH);
```

## Status
目前搜索深度为8层，宽度为{45,35,20,10}迭代递减，最慢情况基本能在60s完成搜索，实际上大部分时间都在10s之内

## Contributors

[@yyjxx2010xyu](https://github.com/yyjxx2010xyu).
[@Lionel-Peiran](https://github.com/Lionel-Peiran).
[@william-wang-stu](https://github.com/william-wang-stu).
## License
MIT License
