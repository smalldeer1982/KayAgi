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

