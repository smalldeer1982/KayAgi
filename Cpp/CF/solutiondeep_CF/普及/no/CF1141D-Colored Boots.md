# 题目信息

# Colored Boots

## 题目描述

There are $ n $ left boots and $ n $ right boots. Each boot has a color which is denoted as a lowercase Latin letter or a question mark ('?'). Thus, you are given two strings $ l $ and $ r $ , both of length $ n $ . The character $ l_i $ stands for the color of the $ i $ -th left boot and the character $ r_i $ stands for the color of the $ i $ -th right boot.

A lowercase Latin letter denotes a specific color, but the question mark ('?') denotes an indefinite color. Two specific colors are compatible if they are exactly the same. An indefinite color is compatible with any (specific or indefinite) color.

For example, the following pairs of colors are compatible: ('f', 'f'), ('?', 'z'), ('a', '?') and ('?', '?'). The following pairs of colors are not compatible: ('f', 'g') and ('a', 'z').

Compute the maximum number of pairs of boots such that there is one left and one right boot in a pair and their colors are compatible.

Print the maximum number of such pairs and the pairs themselves. A boot can be part of at most one pair.

## 样例 #1

### 输入

```
10
codeforces
dodivthree
```

### 输出

```
5
7 8
4 9
2 2
9 10
3 1
```

## 样例 #2

### 输入

```
7
abaca?b
zabbbcc
```

### 输出

```
5
6 5
2 3
4 6
7 4
1 2
```

## 样例 #3

### 输入

```
9
bambarbia
hellocode
```

### 输出

```
0
```

## 样例 #4

### 输入

```
10
code??????
??????test
```

### 输出

```
10
6 2
1 6
7 3
3 5
4 8
9 7
5 1
2 4
10 9
8 10
```

# AI分析结果

### 题目内容重写
# 彩色靴子

## 题目描述

有 $n$ 只左靴和 $n$ 只右靴。每只靴子都有一个颜色，用一个小写拉丁字母或问号（'?'）表示。因此，你被给出两个字符串 $l$ 和 $r$，长度均为 $n$。字符 $l_i$ 表示第 $i$ 只左靴的颜色，字符 $r_i$ 表示第 $i$ 只右靴的颜色。

一个小写拉丁字母表示一种特定颜色，但问号（'?'）表示不确定的颜色。两种特定颜色如果完全相同则是兼容的。不确定的颜色与任何（特定或不确定的）颜色都是兼容的。

例如，以下颜色对是兼容的：('f', 'f'), ('?', 'z'), ('a', '?') 和 ('?', '?')。以下颜色对是不兼容的：('f', 'g') 和 ('a', 'z')。

计算最大数量的靴子对，使得每对中有一只左靴和一只右靴，并且它们的颜色是兼容的。

输出最大数量的靴子对以及这些对本身。每只靴子最多只能属于一对。

## 样例 #1

### 输入

```
10
codeforces
dodivthree
```

### 输出

```
5
7 8
4 9
2 2
9 10
3 1
```

## 样例 #2

### 输入

```
7
abaca?b
zabbbcc
```

### 输出

```
5
6 5
2 3
4 6
7 4
1 2
```

## 样例 #3

### 输入

```
9
bambarbia
hellocode
```

### 输出

```
0
```

## 样例 #4

### 输入

```
10
code??????
??????test
```

### 输出

```
10
6 2
1 6
7 3
3 5
4 8
9 7
5 1
2 4
10 9
8 10
```

### 算法分类
贪心

### 题解分析与结论
这道题的核心是通过贪心策略最大化匹配靴子的数量。所有题解都采用了类似的思路：首先匹配相同颜色的靴子，然后利用问号（'?'）来匹配剩余的不匹配的靴子。具体来说，题解通常分为以下几个步骤：
1. 统计每个颜色和问号的出现次数。
2. 优先匹配相同颜色的靴子。
3. 用左靴的问号匹配右靴的剩余颜色，反之亦然。
4. 最后匹配左右靴的问号。

### 评分较高的题解

#### 作者：Ousmane_Dembele (4星)
**关键亮点**：
- 代码结构清晰，逻辑简单明了。
- 使用数组记录每种颜色和问号的位置，便于后续匹配。

**核心代码**：
```cpp
for(int i=1;i<=26;i++){//挨个匹配非？
    while(a[i].cnt&&b[i].cnt){
        answ++;
        ans[answ][1]=a[i].d[a[i].cnt];
        ans[answ][2]=b[i].d[b[i].cnt];
        a[i].cnt--;
        b[i].cnt--;
    }
}
```

#### 作者：little_sun (4星)
**关键亮点**：
- 使用队列记录每种颜色和问号的位置，代码简洁。
- 通过贪心策略逐步匹配，逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<=26;i++){
    while(a[i] && b[i]){
        --a[i], --b[i];
        ans[0].push_back(vec[i][0].front()), vec[i][0].pop();
        ans[1].push_back(vec[i][1].front()), vec[i][1].pop();
    }
}
```

#### 作者：Pretharp (4星)
**关键亮点**：
- 代码注释详细，便于理解。
- 使用队列数组记录位置，匹配逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<=26;i++){
    while(a[i] && b[i]){
        a[i]--,b[i]--;
        ans1.push(aw[i].front());
        aw[i].pop();
        ans2.push(bw[i].front());
        bw[i].pop();
        idx++;
    }
}
```

### 最优关键思路或技巧
- **贪心策略**：优先匹配相同颜色的靴子，然后再利用问号匹配剩余的靴子。
- **数据结构**：使用数组或队列记录每种颜色和问号的位置，便于后续匹配。

### 可拓展之处
- 类似的问题可以扩展到其他匹配问题，如字符串匹配、图论中的匹配问题等。
- 可以进一步优化匹配顺序，或者考虑更复杂的情况，如多颜色的匹配。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录
- **Ousmane_Dembele**：题目本身不难，但要注意匹配顺序，先匹配非问号，再匹配问号。
- **little_sun**：贪心策略是关键，问号不能浪费，要优先匹配无法匹配的颜色。
- **Pretharp**：代码注释很重要，尤其是对于复杂的匹配逻辑，注释可以帮助理解和调试。

---
处理用时：40.71秒