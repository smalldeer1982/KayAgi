# 题目信息

# Intercepted Message

## 题目描述

Hacker Zhorik wants to decipher two secret messages he intercepted yesterday. Yeah message is a sequence of encrypted blocks, each of them consists of several bytes of information.

Zhorik knows that each of the messages is an archive containing one or more files. Zhorik knows how each of these archives was transferred through the network: if an archive consists of $ k $ files of sizes $ l_{1},l_{2},...,l_{k} $ bytes, then the $ i $ -th file is split to one or more blocks $ b_{i,1},b_{i,2},...,b_{i,mi} $ (here the total length of the blocks $ b_{i,1}+b_{i,2}+...+b_{i,mi} $ is equal to the length of the file $ l_{i} $ ), and after that all blocks are transferred through the network, maintaining the order of files in the archive.

Zhorik thinks that the two messages contain the same archive, because their total lengths are equal. However, each file can be split in blocks in different ways in the two messages.

You are given the lengths of blocks in each of the two messages. Help Zhorik to determine what is the maximum number of files could be in the archive, if the Zhorik's assumption is correct.

## 说明/提示

In the first example the maximum number of files in the archive is 3. For example, it is possible that in the archive are three files of sizes $ 2+5=7 $ , $ 15=3+1+11=8+2+4+1 $ and $ 4+4=8 $ .

In the second example it is possible that the archive contains two files of sizes $ 1 $ and $ 110=10+100=100+10 $ . Note that the order of files is kept while transferring archives through the network, so we can't say that there are three files of sizes $ 1 $ , $ 10 $ and $ 100 $ .

In the third example the only possibility is that the archive contains a single file of size $ 4 $ .

## 样例 #1

### 输入

```
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
1 10 100
1 100 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 4
4
1 1 1 1
```

### 输出

```
1
```

# AI分析结果



### 题目内容
# 拦截的消息

## 题目描述

黑客Zhorik想破译他昨天拦截的两条秘密消息。每条消息由若干加密块组成，每个块包含若干字节的信息。

Zhorik知道每条消息都是一个包含一个或多个文件的存档。存档通过网络传输时，若包含k个文件（大小分别为l₁,l₂,...,l₋），则每个文件会被拆分为若干个块（保持文件顺序），所有块按文件顺序传输。

已知两条消息总长度相等，但文件拆分方式可能不同。请确定存档最多可能包含多少个文件。

## 输入输出样例

样例1：  
输入：  
7 6  
2 5 3 1 11 4 4  
7 8 2 4 1 8  
输出：  
3  

样例2：  
输入：  
3 3  
1 10 100  
1 100 10  
输出：  
2  

样例3：  
输入：  
1 4  
4  
1 1 1 1  
输出：  
1  

---

### 题解分析与结论
需要找到两个数组中的最大分段次数，使得每次分段后的和相等且顺序一致。核心思路是使用前缀和与双指针贪心匹配。

---

### 精选题解

#### 题解1（作者：信守天下）  ★★★★★
**关键思路**：预处理前缀和数组，用双指针同步扫描两个数组，当发现相等的前缀和时立即分割。  
**代码亮点**：  
- 使用前缀和数组避免重复计算  
- 单次线性扫描，时间复杂度O(n+m)  
- 代码简洁直观，可读性强  

```cpp
for (int i = 1; i <= n; i++) {     
    while (j <= m && a[i] > b[j]) {  
        j++;                           
    }
    ans += (a[i] == b[j] && j <= m);
}
```

#### 题解2（作者：某某x）  ★★★★☆  
**关键思路**：动态维护当前分段和，通过比较大小移动指针，相等时立即分割。  
**实现技巧**：  
- 直接在输入时计算前缀和  
- 用while循环处理不等情况  
- 逻辑清晰，空间优化  

```cpp
_rep(1, n, i) {
    while(j <= m && a[i] > b[j]) j++;
    ans += (a[i]==b[j]&&j<=m);
}
```

---

### 关键技巧总结
1. **前缀和预处理**：将分段和转换为前缀和差值比较问题  
2. **双指针贪心**：保持两个指针同步推进，及时处理较小值以寻找匹配  
3. **边界处理**：通过指针范围检查避免数组越界  

---

### 推荐练习
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [CF1005C 相同元素对](https://codeforces.com/problemset/problem/1005/C)  
3. [P3143 钻石收集](https://www.luogu.com.cn/problem/P3143)  

---

### 调试心得摘录
> "移动指针后未及时检查越界导致WA，后来发现应在循环条件中增加指针范围判断"  
> —— 调试中发现边界处理的重要性，尤其在指针操作时需始终保证数组访问合法。

---
处理用时：164.90秒