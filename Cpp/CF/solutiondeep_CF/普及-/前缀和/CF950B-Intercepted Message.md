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



### 题目内容中文翻译
# 拦截的消息

## 题目描述

黑客Zhorik想破译他昨天拦截的两条秘密消息。每条消息由若干加密块组成，每个块包含若干字节信息。

Zhorik知道每条消息都是一个包含一个或多个文件的存档。当存档通过网络传输时，每个文件会被分割为若干块，块顺序传输。两个消息可能对同一文件的块分割方式不同。

给定两个消息的块长度序列，求存档最多可能包含的文件数。要求每个文件在两个消息中的块总长度相等，且文件顺序一致。

## 样例解释

样例1中，存在3个文件：7=2+5，15=3+1+11和8=4+4。对应的块总和在两个消息中分别为：
消息1：[2,5], [3,1,11], [4,4]  
消息2：[7], [8,2,4,1], [8]

---

### 题解分析与结论

#### 核心思路
使用**双指针+贪心策略**：  
1. 维护两个当前分段和`s1`, `s2`，初始为两个数组的首元素
2. 比较当前和：
   - 相等时：找到一个文件分割点，答案+1，并重置分段和
   - 不等时：移动较小和的指针，累加新元素
3. 时间复杂度O(n+m)，空间复杂度O(1)

#### 最优题解亮点

1. **信守天下（5星）**
   - 使用前缀和预处理，双指针同步扫描
   - 代码简洁，逻辑直观，易理解
   ```cpp
   for (int i = 1; i <= n; i++) {
     while (j <= m && a[i] > b[j]) j++;
     ans += (a[i] == b[j] && j <= m);
   }
   ```

2. **某某x（5星）**
   - 与前解思路一致，代码风格清晰
   - 循环结构优化，变量命名规范
   ```cpp
   _rep(1, n, i) {
     while(j <= m && a[i] > b[j]) j++;
     ans += (a[i]==b[j]&&j<=m);
   }
   ```

3. **Wi_Fi（5星）**
   - 动态维护当前和，无需前缀和数组
   - 边界处理严谨，空间效率更优
   ```cpp
   while(x<=n&&y<=m) {
     if(s1==s2) ans++,x++,y++,s1=a[x],s2=b[y];
     else if(s1<s2) s1+=a[++x];
     else s2+=b[++y];
   }
   ```

---

### 关键技巧总结
1. **双指针同步推进**：通过比较当前分段和，保证文件顺序一致
2. **贪心选择策略**：总是优先扩展较小和的分段，确保最早找到分割点
3. **边界处理**：循环终止条件需同时判断两个指针的越界情况

---

### 类似题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   - 考察前缀和与贪心思想
2. [CF978B File Name](https://codeforces.com/problemset/problem/978/B)  
   - 双指针处理连续子段
3. [P3143 钻石收集](https://www.luogu.com.cn/problem/P3143)  
   - 双指针求最大区间覆盖

---
处理用时：143.75秒