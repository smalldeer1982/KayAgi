# 天下一芸術

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2014-qualb/tasks/tenka1_2014_qualB_d



## 说明/提示

### 部分点

- $ 1\ \leq{}\ N\ \leq{}\ 5 $ かつ $ 1\ \leq{}\ H,\ W\ \leq{}\ 5 $のすべてのテストケースに正解した場合、部分点として35点を与える
- $ 1\ \leq{}\ N\ \leq{}\ 9 $ のすべてのテストケースに正解した場合、部分点としてさらに40点を与える

### Sample Explanation 1

\### 出力例1 ```

```
<pre class="prettyprint linenums">1
```

与えられたペンキを上から順にA, B, C, D, Eとすると以下の順番で塗りわけることが可能です。

 ```
BBB
BBB
```

 ```
BBB
AAA
```

 ```
BCB
AAA
```

 ```
BCB
ADA
```

今回の塗り方ではEは使用しませんでした。<h3>Sample Explanation 2</h3><p>### 出力例2

 ```
</p><pre class="prettyprint linenums">0
```

与えられたペンキで塗ることはできません。<h3>Sample Explanation 3</h3><p>### 出力例3

 ```
</p><pre class="prettyprint linenums">0
```

与えられたペンキで塗ることはできません。<h3>Sample Explanation 4</h3><p>### 出力例4

 ```
</p><pre class="prettyprint linenums">1
```

与えられたペンキを上から順にA, B, C, D, Eとすると以下の順番で塗りわけることが可能です。

 ```
A A # # #
A A # # #
A A # # #
A A # # #
A A # # #
```

 ```
A A B B #
A A B B #
A A B B #
A A B B #
A A B B #
```

 ```
A A B B E
A A B B E
A A B B E
A A B B E
A A B B E
```

 ```
A D D D E
A D D D E
A D D D E
A A B B E
A A B B E
```

 ```
A D D D E
A D D C C
A D D C C
A A B C C
A A B B E
```
```

## 样例 #1

### 输入

```
5
4
0
4
10
4
2 3
3 1 3
0 2 0```

### 输出

```
None```

## 样例 #2

### 输入

```
5
4
0
4
10
4
2 4
3 1 2 3
0 1 2 0```

### 输出

```
None```

## 样例 #3

### 输入

```
2
1
2
2 2
0 1
1 0```

### 输出

```
None```

## 样例 #4

### 输入

```
5
1
1
66
30
1
5 5
3 4 4 4 2
3 4 4 0 0
3 4 4 0 0
3 3 1 0 0
3 3 1 1 2```

### 输出

```
None```

