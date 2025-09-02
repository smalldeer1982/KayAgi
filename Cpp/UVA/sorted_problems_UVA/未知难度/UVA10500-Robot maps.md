---
title: "Robot maps"
layout: "post"
diff: 难度0
pid: UVA10500
tag: []
---

# Robot maps

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1441

[PDF](https://uva.onlinejudge.org/external/105/p10500.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10500/566d25eb37e98567b749b441a36264042541e890.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10500/cff82855019ee931398c29757de7102b8e240d9b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10500/23cfd2af0e353ef46c3c7eda6e99488cac4d8e57.png)

## 样例 #1

### 输入

```
5 5
1 3
X X 0 0 X
X X 0 0 X
X 0 X 0 X
X 0 0 0 X
X X X X X
5 5
1 1
0 0 X X X
X X 0 0 X
X 0 0 0 X
X 0 0 0 X
X X X X X
0 0
```

### 输出

```
|---|---|---|---|---|
| ? | X | 0 | 0 | X |
|---|---|---|---|---|
| ? | X | 0 | 0 | X |
|---|---|---|---|---|
| X | 0 | X | 0 | X |
|---|---|---|---|---|
| X | 0 | 0 | 0 | X |
|---|---|---|---|---|
| ? | X | X | X | ? |
|---|---|---|---|---|
NUMBER OF MOVEMENTS: 7
|---|---|---|---|---|
| 0 | 0 | X | ? | ? |
|---|---|---|---|---|
| X | X | ? | ? | ? |
|---|---|---|---|---|
| ? | ? | ? | ? | ? |
|---|---|---|---|---|
| ? | ? | ? | ? | ? |
|---|---|---|---|---|
| ? | ? | ? | ? | ? |
|---|---|---|---|---|
NUMBER OF MOVEMENTS: 1
```

