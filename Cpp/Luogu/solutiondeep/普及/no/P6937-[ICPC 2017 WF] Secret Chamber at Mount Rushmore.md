# 题目信息

# [ICPC 2017 WF] Secret Chamber at Mount Rushmore

## 题目描述



![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14641/1.png)

By now you have probably heard that there is a spectacular stone sculp-ture featuring four famous U.S. presidents at Mount Rushmore.  How-ever, very few people know that this monument contains a secret cham-ber. This sounds like something out of a plot of a Hollywood movie, butthe chamber really exists.  It can be found behind the head of AbrahamLincoln and was designed to serve as a Hall of Records to store impor-tant historical U.S. documents and artifacts.  Historians claim that theconstruction of the hall was halted in 1939 and the uncompleted cham-ber was left untouched until the late 1990s,  but this is not the wholetruth.

In $1982$ , the famous archaeologist $S$ . Dakota Jones secretly visited the monument and found that the chamber actually was completed, but it was kept confidential. This seemed suspicious and after some poking around, she found a hidden vault and some documents inside. Unfortunately, these documents did not make any sense and were all gibberish. She suspected that they had been written in a code, but she could not decipher them despite all her efforts.

Earlier this week when she was in the area to follow the ACM-ICPC World Finals, Dr. Jones finally discovered the key to deciphering the documents, in Connolly Hall of $SDSM&T$ . She found a document that contains a list of translations of letters. Some letters may have more than one translation, and others may have no translation. By repeatedly applying some of these translations to individual letters in the gibberish documents, she might be able to decipher them to yield historical U.S . documents such as the Declaration of Independence and the Constitution. She needs your help.

You are given the possible translations of letters and a list of pairs of original and deciphered words. Your task is to verify whether the words in each pair match. Two words match if they have the same length and if each letter of the first word can be turned into the corresponding letter of the second word by using the available translations zero or more times.



## 说明/提示

Time limit: 1 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
9 5
c t
i r
k p
o c
r o
t e
t f
u h
w p
we we
can the
work people
it of
out the
```

### 输出

```
yes
no
no
yes
yes
```

## 样例 #2

### 输入

```
3 3
a c
b a
a b
aaa abc
abc aaa
acm bcm
```

### 输出

```
yes
no
yes
```

# AI分析结果



**算法分类**: 图论（传递闭包）

---

### 综合分析与结论
题目核心是判断字符间是否存在可达路径，使用**图论**中的传递闭包思想（Floyd算法）预处理所有字符对的可达性，使得查询时只需检查对应字符是否可达。DFS/BFS也可用于单次查询，但多次查询时效率低。Floyd算法在此场景下更优，时间复杂度为O(26³)，完全可接受。

---

### 高分题解推荐

1. **作者：ljh789789**（⭐⭐⭐⭐⭐）  
   **关键亮点**：  
   - 使用Floyd算法预处理所有字符对的可达性，代码简洁高效。  
   - 预处理时自动处理自环（`f[i][i]=1`），符合题意。  
   **核心代码**：  
   ```cpp
   for(int k=1;k<=26;k++)
   for(int i=1;i<=26;i++)
   for(int j=1;j<=26;j++)
       if(f[i][k]&&f[k][j]) f[i][j]=1;
   ```

2. **作者：char_phi**（⭐⭐⭐⭐）  
   **关键亮点**：  
   - 提供DFS和Floyd两种解法，思路全面。  
   - DFS中通过`vis`数组避免环路导致的死递归。  
   **核心代码（Floyd）**：  
   ```cpp
   for (re k = 1 ; k <= n ; ++ k)
       for (re i = 1 ; i <= n ; ++ i)
           for (re j = 1 ; j <= n ; ++ j)
               can[i][j] |= (can[i][k] & can[k][j]);
   ```

3. **作者：StarsIntoSea_SY**（⭐⭐⭐⭐）  
   **关键亮点**：  
   - 代码简洁，直接应用传递闭包。  
   - 正确处理字符到自身的转换。  
   **核心代码**：  
   ```cpp
   for(int t=1;t<=26;++t)
       for(int i=1;i<=26;++i)
           for(int j=1;j<=26;++j)
               if(f[i][t]&f[t][j]) f[i][j]=1;
   ```

---

### 最优关键思路
**传递闭包预处理**：将字符视为图的节点，转换规则视为有向边，通过Floyd算法预处理所有字符对的可达性矩阵，使得每次查询仅需检查对应位置是否可达。

---

### 拓展与举一反三
- **类似题目**：  
  1. [P1613 跑路](https://www.luogu.com.cn/problem/P1613)（传递闭包+最短路）  
  2. [P4306 连通数](https://www.luogu.com.cn/problem/P4306)（有向图可达性统计）  
  3. [P2881 排名的牛](https://www.luogu.com.cn/problem/P2881)（传递闭包应用）

- **心得总结**：  
  - **预处理优先**：当多次查询依赖同一组规则时，预处理（如Floyd）显著优于实时计算（如DFS）。  
  - **环路处理**：DFS必须用`vis`数组避免重复访问，否则会无限递归（如作者char_phi的调试经验）。

---
处理用时：54.74秒