# 题目信息

# [ABC342C] Many Replacement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc342/tasks/abc342_c

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます。

文字列 $ S $ に対して操作を $ Q $ 回行います。 $ i $ 回目 $ (1\leq\ i\leq\ Q) $ の操作は文字の組 $ (c\ _\ i,d\ _\ i) $ で表され、次のような操作に対応します。

- $ S $ に含まれる文字 $ c\ _\ i $ をすべて文字 $ d\ _\ i $ で置き換える。
 
すべての操作が終わったあとの文字列 $ S $ を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10^5 $
- $ S $ は英小文字からなる長さ $ N $ の文字列
- $ 1\leq\ Q\leq2\times10^5 $
- $ c\ _\ i,d\ _\ i $ は英小文字 $ (1\leq\ i\leq\ Q) $
- $ N,Q $ は整数
 
### Sample Explanation 1

$ S $ は `atcoder` → `atcodea` → `aecodea` → `aecovea` → `recover` と変化します。 たとえば、$ 4 $ 番目の操作では $ S={} $`aecovea` に含まれる `a` （$ 1 $ 文字目と $ 7 $ 文字目）をすべて `r` に置き換えるので $ S={} $`recover` となります。 すべての操作が終わったときには $ S={} $`recover` となっているため、`recover` を出力してください。

### Sample Explanation 2

$ c\ _\ i=d\ _\ i $ であるような操作や $ S $ に $ c\ _\ i $ が含まれないような操作もあります。

## 样例 #1

### 输入

```
7

atcoder

4

r a

t e

d v

a r```

### 输出

```
recover```

## 样例 #2

### 输入

```
3

abc

4

a a

s k

n n

z b```

### 输出

```
abc```

## 样例 #3

### 输入

```
34

supercalifragilisticexpialidocious

20

g c

l g

g m

c m

r o

s e

a a

o f

f s

e t

t l

d v

p k

v h

x i

h n

n j

i r

s i

u a```

### 输出

```
laklimamriiamrmrllrmlrkramrjimrial```

# AI分析结果

### 题目翻译
## [ABC342C] 多次替换

### 题目描述
给定一个由小写英文字母组成的长度为 $N$ 的字符串 $S$。

对字符串 $S$ 进行 $Q$ 次操作。第 $i$ 次（$1\leq i\leq Q$）操作由字符对 $(c_i, d_i)$ 表示，对应以下操作：
- 将 $S$ 中包含的所有字符 $c_i$ 替换为字符 $d_i$。

请输出所有操作完成后的字符串 $S$。

### 说明/提示
#### 约束条件
- $1\leq N\leq2\times10^5$
- $S$ 是由小写英文字母组成的长度为 $N$ 的字符串
- $1\leq Q\leq2\times10^5$
- $c_i, d_i$ 是小写英文字母（$1\leq i\leq Q$）
- $N, Q$ 是整数

#### 样例解释 1
$S$ 按以下方式变化：`atcoder` → `atcodea` → `aecodea` → `aecovea` → `recover`。例如，在第 4 次操作中，将 $S =$ `aecovea` 中包含的 `a`（第 1 个和第 7 个字符）全部替换为 `r`，因此 $S =$ `recover`。由于所有操作完成后 $S =$ `recover`，所以请输出 `recover`。

#### 样例解释 2
也存在 $c_i = d_i$ 的操作，或者 $S$ 中不包含 $c_i$ 的操作。

### 样例 #1
#### 输入
```
7
atcoder
4
r a
t e
d v
a r
```
#### 输出
```
recover
```

### 样例 #2
#### 输入
```
3
abc
4
a a
s k
n n
z b
```
#### 输出
```
abc
```

### 样例 #3
#### 输入
```
34
supercalifragilisticexpialidocious
20
g c
l g
g m
c m
r o
s e
a a
o f
f s
e t
t l
d v
p k
v h
x i
h n
n j
i r
s i
u a
```
#### 输出
```
laklimamriiamrmrllrmlrkramrjimrial
```

### 题解综合分析与结论
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|Programming_Konjac|创建字符映射数组，先初始化，再存储操作，用倒推法更新映射，最后输出结果|使用 `map` 存储字符映射，倒推更新映射|处理间接替换问题，避免重复遍历字符串|4星|
|_smart_stupid_|记录字母替换关系，每次出现替换关系时更新所有要替换成该字母的字母|使用数组 `f` 记录替换关系，遍历 26 个字母更新替换关系|正确处理字母替换的传递性|3星|
|LaoXu666|存储每个字母的变换结果，倒着操作解决间接变换问题|使用数组 `Replace` 存储变换结果，倒序处理操作|解决间接变换和环的问题|4星|
|LittleDrinks|通过修改标记实现批量修改，用 `x` 数组存储字符出现下标|使用 `vector` 存储字符出现下标，根据字符存在情况修改标记|减少修改时间，避免直接枚举超时|3星|
|HappyJaPhy|开 `fa` 数组记录字母替换关系，每次操作遍历 26 个字母更新|使用数组 `fa` 记录替换关系，遍历 26 个字母更新替换关系|处理字母替换的传递性|3星|

### 所选题解
- **Programming_Konjac（4星）**
    - **关键亮点**：思路清晰，使用 `map` 存储字符映射，通过倒推法避免了重复遍历字符串，有效处理了间接替换问题。
    - **核心代码**：
```cpp
map<char,char> m;
for(int i='a'; i<='z'; i++){
    m[(char)i]=(char)i;
}
char c[200005],d[200005];
for(int i=1; i<=q; i++) cin>>c[i]>>d[i];
for(int i=q; i>=1; i--){
    m[c[i]]=m[d[i]];
}
for(int i=0;i<n;i++){
    cout<<m[s[i]];
}
```
- **LaoXu666（4星）**
    - **关键亮点**：详细分析了间接变换和环的问题，通过倒着操作解决了这些问题，代码简洁易懂。
    - **核心代码**：
```cpp
char Replace[128];
for (int i = 0; i < 128; i++) {
    Replace[i] = char(i);
}
for (int i = 1; i <= K; i++) {
    std::cin >> Replace1[i] >> Replace2[i];
}
for (int i = K; i >= 1; i--) {
    Replace[Replace1[i]] = Replace[Replace2[i]];
}
for (char i: Str) {
    std::cout << Replace[i];
}
```

### 最优关键思路或技巧
- 使用映射数组（如 `map` 或普通数组）存储字母的替换关系，避免直接对字符串进行频繁替换操作，减少时间复杂度。
- 采用倒推法处理操作，解决间接替换和环的问题，确保最终结果的正确性。

### 拓展思路
同类型题目可能会增加操作的复杂性，如增加操作的类型（如删除、插入字符等），或者改变字符串的组成（如包含大写字母、数字等）。类似的算法套路包括使用映射或并查集来处理元素之间的关系。

### 推荐题目
- [P1955 [NOI2015] 程序自动分析](https://www.luogu.com.cn/problem/P1955)
- [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)
- [P3367 [模板] 并查集](https://www.luogu.com.cn/problem/P3367)

### 个人心得摘录与总结
- **Programming_Konjac**：提到使用倒推法是因为后面的操作会影响一开始的操作，通过赋值为 $m_{d_i}$ 避免了重复遍历字符串，解决了间接替换的问题。
总结：在处理有顺序影响的操作时，可以考虑倒推法，同时合理利用映射数组避免重复计算。 

---
处理用时：43.59秒