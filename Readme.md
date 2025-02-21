## Piros-Fekete fa implementáció (csak beszúrás)

[Forrás](https://www.geeksforgeeks.org/red-black-tree-in-cpp/), de a hiba (az ismétlődő számok beszúrásánál) kijavítva, a törlés nem jó így kivettem.

Fa megjelenítése [GraphViz](http://graphviz.org/) segítségével:

```bash
g++ -std=c++11 rbtree.cpp -o rbtree && \
"/Users/tom/Dev/cpp/"rbtree && \
dot -Tsvg rbt.dot > rbt.svg    
```

##### Bemenet: [input.txt](input.txt) (a beszúrandó számok szóközzel elválasztva)

##### Kimenet: [rbt.dot](rbt.dot) [(GraphViz dot-fájl)](https://dreampuf.github.io/GraphvizOnline/?engine=dot), [rbt.svg (svg fájl)](rbt.svg)
