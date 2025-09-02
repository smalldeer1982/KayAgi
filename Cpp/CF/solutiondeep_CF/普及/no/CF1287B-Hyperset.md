# 题目信息

# Hyperset

## 题目描述

Bees Alice and Alesya gave beekeeper Polina famous card game "Set" as a Christmas present. The deck consists of cards that vary in four features across three options for each kind of feature: number of shapes, shape, shading, and color. In this game, some combinations of three cards are said to make up a set. For every feature — color, number, shape, and shading — the three cards must display that feature as either all the same, or pairwise different. The picture below shows how sets look.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1287B/2d643729d5939800827cb912354d70a177513bf3.png)

Polina came up with a new game called "Hyperset". In her game, there are $ n $ cards with $ k $ features, each feature has three possible values: "S", "E", or "T". The original "Set" game can be viewed as "Hyperset" with $ k = 4 $ .

Similarly to the original game, three cards form a set, if all features are the same for all cards or are pairwise different. The goal of the game is to compute the number of ways to choose three cards that form a set.

Unfortunately, winter holidays have come to an end, and it's time for Polina to go to school. Help Polina find the number of sets among the cards lying on the table.

## 说明/提示

In the third example test, these two triples of cards are sets:

1. "SETT", "TEST", "EEET"
2. "TEST", "ESTE", "STES"

## 样例 #1

### 输入

```
3 3
SET
ETS
TSE```

### 输出

```
1```

## 样例 #2

### 输入

```
3 4
SETE
ETSE
TSES```

### 输出

```
0```

## 样例 #3

### 输入

```
5 4
SETT
TEST
EEET
ESTE
STES```

### 输出

```
2```

# AI分析结果

### 题目内容重写

**题目名称：Hyperset**

**题目描述：**

蜜蜂Alice和Alesya给养蜂人Polina送了一款著名的卡片游戏“Set”作为圣诞礼物。这套卡片由若干张卡片组成，每张卡片有四个特征，每个特征有三种可能的取值：形状的数量、形状、阴影和颜色。在这个游戏中，某些三张卡片的组合被称为一个“set”。对于每一个特征——颜色、数量、形状和阴影——这三张卡片在该特征上的取值必须要么全部相同，要么全部不同。下图展示了“set”的样子。

Polina发明了一个新游戏，叫做“Hyperset”。在她的游戏中，有$n$张卡片，每张卡片有$k$个特征，每个特征有三种可能的取值：“S”、“E”或“T”。原始的“Set”游戏可以看作是$k=4$的“Hyperset”。

与原始游戏类似，三张卡片形成一个“set”，当且仅当所有特征在三张卡片上要么全部相同，要么全部不同。游戏的目标是计算有多少种选择三张卡片的方式可以形成一个“set”。

不幸的是，寒假结束了，Polina该去上学了。请你帮助Polina计算桌子上卡片中有多少个“set”。

**说明/提示：**

在第三个样例中，以下两组三张卡片是“set”：

1. "SETT", "TEST", "EEET"
2. "TEST", "ESTE", "STES"

**样例 #1：**

**输入：**

```
3 3
SET
ETS
TSE
```

**输出：**

```
1
```

**样例 #2：**

**输入：**

```
3 4
SETE
ETSE
TSES
```

**输出：**

```
0
```

**样例 #3：**

**输入：**

```
5 4
SETT
TEST
EEET
ESTE
STES
```

**输出：**

```
2
```

### 算法分类

枚举

### 题解分析与结论

该题的核心思路是通过枚举两张卡片，推导出第三张卡片应该满足的特征，然后检查是否存在这样的卡片。这种方法的时间复杂度为$O(n^2k)$，在给定的数据范围内是可行的。

#### 题解对比

1. **yuzhechuan的题解**：使用`map`来记录已经出现过的卡片，枚举两张卡片后推导第三张卡片，并检查`map`中是否存在该卡片。代码简洁，思路清晰，时间复杂度为$O(n^2k)$。
   
2. **ix35的题解**：使用Trie树来存储卡片信息，枚举两张卡片后推导第三张卡片，并在Trie树中查找。虽然时间复杂度与`map`方法相同，但常数可能更小，代码实现较为复杂。

3. **liuyz11的题解**：将卡片特征转换为三进制数，使用离散化和`map`进行计数。虽然思路正确，但代码实现较为复杂，且时间复杂度与`map`方法相同。

4. **_weishiqi66_的题解**：直接枚举两张卡片，推导第三张卡片，并使用`unordered_map`进行查找。代码简洁，但未处理重复计数问题，导致答案需要除以6。

5. **Maysoul的题解**：使用`map`和`set`来记录已经统计过的三元组，避免重复计数。代码实现较为复杂，但思路清晰。

6. **gyh20的题解**：使用`map`进行查找，枚举两张卡片后推导第三张卡片。代码简洁，但未处理重复计数问题，导致答案需要除以3。

#### 最优题解

**yuzhechuan的题解**（评分：5星）

- **关键亮点**：代码简洁，思路清晰，使用`map`进行查找，时间复杂度为$O(n^2k)$，适合本题的数据范围。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++){
      for(int j=i+1;j<=n;j++){
          string aim="";
          for(int k=0;k<m;k++){
              if(s[i][k]==s[j][k]) aim+=s[i][k];
              else{
                  if(s[i][k]!='S'&&s[j][k]!='S') aim+='S';
                  if(s[i][k]!='E'&&s[j][k]!='E') aim+='E';
                  if(s[i][k]!='T'&&s[j][k]!='T') aim+='T';
              }
          }
          ans+=mp[aim];
      }
      mp[s[i]]++;
  }
  ```

### 关键思路与技巧

1. **枚举两张卡片推导第三张卡片**：通过枚举两张卡片，可以唯一确定第三张卡片应该满足的特征，从而减少枚举次数。
2. **使用`map`进行快速查找**：`map`可以快速查找是否存在满足条件的第三张卡片，时间复杂度为$O(\log n)$。
3. **避免重复计数**：在枚举时，可以通过只统计$i$之前的卡片来避免重复计数。

### 拓展思路

类似的问题可以通过枚举部分元素，推导出剩余元素的条件，然后使用数据结构进行快速查找。例如，在组合数学中，常常需要枚举部分元素，推导出剩余元素的组合条件。

### 推荐题目

1. [P1219 八皇后问题](https://www.luogu.com.cn/problem/P1219)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)

### 个人心得

在调试过程中，发现重复计数是一个常见的问题，尤其是在枚举多个元素时。通过限制枚举范围或使用数据结构记录已经统计过的组合，可以有效避免重复计数。

---
处理用时：42.35秒