## Piros-Fekete fa implementáció (csak beszúrás)

[Forrás](https://www.geeksforgeeks.org/red-black-tree-in-cpp/), de a hiba (az ismétlődő számok beszúrásánál) kijavítva, a törlés nem jó így kivettem.

Fa megjelenítése [GraphViz](http://graphviz.org/) segítségével:

```bash
g++ -std=c++11 rbtree.cpp -o rbtree && \
"/Users/tom/Dev/cpp/"rbtree && \
dot -Tsvg rbt.dot > rbt.svg    
```

##### Kimenet: [GraphViz dot-fájl](https://dreampuf.github.io/GraphvizOnline/?engine=dot), [SVG](rbt.svg)
