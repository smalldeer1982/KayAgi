---
title: "Treblecross"
layout: "post"
diff: 提高+/省选-
pid: UVA10561
tag: ['字符串', '搜索']
---

# Treblecross

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1502

[PDF](https://uva.onlinejudge.org/external/105/p10561.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/31bc60cd2679d5a858bab6338b6a91a761cb246d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/f3a035fa62c3266f7235864450f9f70c79fb3298.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/9aa18e2eb8be86e1d3e3cb2e789c20ffbc1a2cbf.png)

## 样例 #1

### 输入

```
4
.....
X.....X..X.............X....X..X
.X.X...X
...............................................
```

### 输出

```
WINNING
3
LOSING
WINNING
3
WINNING
1 12 15 17 20 24 28 31 33 36 47
```



---

---
title: "Hyper Prefix Sets"
layout: "post"
diff: 提高+/省选-
pid: UVA11488
tag: ['字符串']
---

# Hyper Prefix Sets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2483

[PDF](https://uva.onlinejudge.org/external/114/p11488.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/b054540c80bd466e35ea7b5ef13a250519cecff4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/fc8e7263656e721ab7ea67390fda22bec8d391d1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/144ebe3d0def2038245a39df7775b227fb650280.png)

## 样例 #1

### 输入

```
4
4
0000
0001
10101
010
2
01010010101010101010
11010010101010101010
3
010101010101000010001010
010101010101000010001000
010101010101000010001010
5
01010101010100001010010010100101
01010101010100001010011010101010
00001010101010110101
0001010101011010101
00010101010101001
```

### 输出

```
6
20
66
44
```



---

---
title: "生成排列 Generating Permutations"
layout: "post"
diff: 提高+/省选-
pid: UVA11925
tag: ['字符串', '构造']
---

# 生成排列 Generating Permutations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3076

[PDF](https://uva.onlinejudge.org/external/119/p11925.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/4ae01d3bad0e00d10dd54ea1a36732d8994153c9.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/39a915f8fa7c330f6d88d2084592f1cdbcc50f29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/b09493d267f3d2d325027cbace89abb524055c4a.png)

## 样例 #1

### 输入

```
3 2 1 3
3 2 3 1
4 4 2 3 1
0
```

### 输出

```
1
2
12122
```



---

---
title: "Bribing FIPA"
layout: "post"
diff: 提高+/省选-
pid: UVA1222
tag: ['字符串', '离散化', '背包 DP']
---

# Bribing FIPA

## 题目描述

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。

## 输入格式

多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。


多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。

## 输出格式

对于每组输入数据，输出一行表示答案。
```
UVA1222

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。


对于每组输入数据，输出一行表示答案。
样例输入：
3 2
Aland 10
Boland 20 Aland
Coland 15
#

样例输出：
20



---

---
title: "Jurassic Remains"
layout: "post"
diff: 提高+/省选-
pid: UVA1326
tag: ['字符串', '搜索', '枚举']
---

# Jurassic Remains

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4072

[PDF](https://uva.onlinejudge.org/external/13/p1326.pdf)



---

---
title: "Falling Leaves"
layout: "post"
diff: 提高+/省选-
pid: UVA1525
tag: ['字符串', '搜索', '平衡树', '图论建模']
---

# Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4300

[PDF](https://uva.onlinejudge.org/external/15/p1525.pdf)



---

