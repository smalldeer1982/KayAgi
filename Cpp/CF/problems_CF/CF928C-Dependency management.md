---
title: "Dependency management"
layout: "post"
diff: 普及+/提高
pid: CF928C
tag: []
---

# Dependency management

## 题目描述

Polycarp 正在开发一个使用 Vaja 语言编写的项目，依赖于著名的依赖管理系统 Vamen。为了简化处理，Vamen 将 Vaja 项目和库都视作项目。

每个 Vaja 项目都有一个由小写字母组成的独特名称，长度不超过 10 个字符，以及一个版本号，这是一个介于 1 和 $10^6$ 之间的正整数。每个项目（通过其名称和版本号确定）可能依赖于其他项目。确保不存在循环依赖。

你会得到一份项目的描述列表。其中，第一个项目是 Polycarp 当前正在开发的项目。请帮助 Polycarp 确定他的项目所直接或间接依赖的所有项目。

如果 Polycarp 的项目依赖于某个项目的两个不同版本，系统将选择离 Polycarp 项目最近的版本。如果多个版本距离相同，则选择版本号较大的那个版本。这个版本被视为有效版本，其他版本及其依赖都会被忽略。

在这个问题中，你需要选出一个最小的项目集，满足以下条件：

- 必须包含 Polycarp 的项目；
- Polycarp 的项目直接或间接依赖于这个集合中的所有其他项目；
- 集合中的项目没有重名；
- 对于集合中项目 $x$ 所依赖的每个项目 $y$，要么 $y$ 在集合中，要么存在一个不同版本且到 Polycarp 项目路径更短的项目取代了 $y$。在多种选择的情况下，选择最新的版本。

输出 Polycarp 项目的所有依赖项目的名称（不包括 Polycarp 的项目本身），按字典顺序排列。

## 输入格式

第一行包含一个整数 $n$，表示 Vaja 项目的数量（$1 \le n \le 1000$）。

接下来的描述中，每个项目有两行信息。第一行为项目名称和版本号，用空格分隔。第二行为直接依赖的项目数量（范围从 0 到 $n-1$），随后是一系列依赖项目，每行一个，顺序可随机。每个依赖项通过名称和版本号标识。所有项目按随机顺序给出，但第一个项目始终是 Polycarp 的项目。项目描述之间用空行隔开。请参考样例以帮助理解。

保证不存在循环依赖。

## 输出格式

按字典顺序输出 Polycarp 项目所有依赖项目的名称。

## 样例
第一个示例见下图。箭头从 $A$ 指向 $B$，表示 $B$ 直接依赖于 $A$。Polycarp 的项目「a」（版本 3）依赖的项目以黑色标注。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF928C/a371859be3b1d6095a64048886da3d40b8a64a5c.png)

第二个示例见下图。箭头从 $A$ 指向 $B$，表示 $B$ 直接依赖于 $A$。Polycarp 的项目「codehorses」（版本 5）依赖的项目以黑色标注。注意，由于存在「mashadb 2」，「extra 1」被选择，而不是「extra 3」；因此，「mashadb 1」及其所有依赖被忽略。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF928C/978730e491ec608e1064d6e22362aa73a87095d0.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
a 3
2
b 1
c 1
 
b 2
0
 
b 1
1
b 2
 
c 1
1
b 2

```

### 输出

```
2
b 1
c 1

```

## 样例 #2

### 输入

```
9
codehorses 5
3
webfrmk 6
mashadb 1
mashadb 2
 
commons 2
0
 
mashadb 3
0
 
webfrmk 6
2
mashadb 3
commons 2
 
extra 4
1
extra 3
 
extra 3
0
 
extra 1
0
 
mashadb 1
1
extra 3
 
mashadb 2
1
extra 1

```

### 输出

```
4
commons 2
extra 1
mashadb 2
webfrmk 6

```

## 样例 #3

### 输入

```
3
abc 1
2
abc 3
cba 2

abc 3
0

cba 2
0

```

### 输出

```
1
cba 2

```

