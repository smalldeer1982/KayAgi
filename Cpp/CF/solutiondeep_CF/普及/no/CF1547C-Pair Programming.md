# 题目信息

# Pair Programming

## 题目描述

Monocarp and Polycarp are learning new programming techniques. Now they decided to try pair programming.

It's known that they have worked together on the same file for $ n + m $ minutes. Every minute exactly one of them made one change to the file. Before they started, there were already $ k $ lines written in the file.

Every minute exactly one of them does one of two actions: adds a new line to the end of the file or changes one of its lines.

Monocarp worked in total for $ n $ minutes and performed the sequence of actions $ [a_1, a_2, \dots, a_n] $ . If $ a_i = 0 $ , then he adds a new line to the end of the file. If $ a_i > 0 $ , then he changes the line with the number $ a_i $ . Monocarp performed actions strictly in this order: $ a_1 $ , then $ a_2 $ , ..., $ a_n $ .

Polycarp worked in total for $ m $ minutes and performed the sequence of actions $ [b_1, b_2, \dots, b_m] $ . If $ b_j = 0 $ , then he adds a new line to the end of the file. If $ b_j > 0 $ , then he changes the line with the number $ b_j $ . Polycarp performed actions strictly in this order: $ b_1 $ , then $ b_2 $ , ..., $ b_m $ .

Restore their common sequence of actions of length $ n + m $ such that all actions would be correct — there should be no changes to lines that do not yet exist. Keep in mind that in the common sequence Monocarp's actions should form the subsequence $ [a_1, a_2, \dots, a_n] $ and Polycarp's — subsequence $ [b_1, b_2, \dots, b_m] $ . They can replace each other at the computer any number of times.

Let's look at an example. Suppose $ k = 3 $ . Monocarp first changed the line with the number $ 2 $ and then added a new line (thus, $ n = 2, \: a = [2, 0] $ ). Polycarp first added a new line and then changed the line with the number $ 5 $ (thus, $ m = 2, \: b = [0, 5] $ ).

Since the initial length of the file was $ 3 $ , in order for Polycarp to change line number $ 5 $ two new lines must be added beforehand. Examples of correct sequences of changes, in this case, would be $ [0, 2, 0, 5] $ and $ [2, 0, 0, 5] $ . Changes $ [0, 0, 5, 2] $ (wrong order of actions) and $ [0, 5, 2, 0] $ (line $ 5 $ cannot be edited yet) are not correct.

## 样例 #1

### 输入

```
5

3 2 2
2 0
0 5

4 3 2
2 0 5
0 6

0 2 2
1 0
2 3

5 4 4
6 0 8 0
0 7 0 9

5 4 1
8 7 8 0
0```

### 输出

```
2 0 0 5 
0 2 0 6 5 
-1
0 6 0 7 0 8 0 9
-1```

# AI分析结果

### 题目内容重写
Monocarp和Polycarp正在学习新的编程技术。现在他们决定尝试结对编程。

已知他们一起在同一个文件上工作了$n + m$分钟。每分钟他们中的一个人会对文件进行一次修改。在他们开始之前，文件中已经有$k$行。

每分钟，他们中的一个人会执行以下两种操作之一：在文件末尾添加一行，或者修改文件的某一行。

Monocarp总共工作了$n$分钟，执行的操作序列为$[a_1, a_2, \dots, a_n]$。如果$a_i = 0$，则他在文件末尾添加一行；如果$a_i > 0$，则他修改第$a_i$行。Monocarp严格按照这个顺序执行操作：$a_1$，然后$a_2$，……，$a_n$。

Polycarp总共工作了$m$分钟，执行的操作序列为$[b_1, b_2, \dots, b_m]$。如果$b_j = 0$，则他在文件末尾添加一行；如果$b_j > 0$，则他修改第$b_j$行。Polycarp严格按照这个顺序执行操作：$b_1$，然后$b_2$，……，$b_m$。

请恢复他们共同的操作序列，长度为$n + m$，并确保所有操作都是合法的——不能修改尚未存在的行。注意，在共同序列中，Monocarp的操作必须形成子序列$[a_1, a_2, \dots, a_n]$，Polycarp的操作必须形成子序列$[b_1, b_2, \dots, b_m]$。他们可以随时交换使用电脑。

### 算法分类
贪心

### 题解分析与结论
所有题解都采用了贪心策略，核心思想是优先选择增加行数的操作（即操作值为0），以最大化当前的行数$k$，从而为后续的修改操作提供更大的灵活性。如果两个序列的当前操作都无法执行（即操作值大于$k$），则输出`-1`。

### 所选高星题解
1. **作者：SunsetLake (赞：3)**  
   - **星级：4**  
   - **关键亮点**：  
     - 使用贪心策略，优先选择0操作，确保$k$最大化。  
     - 通过设置极大值防止多余的0操作被加入序列，代码简洁且高效。  
   - **核心代码**：
     ```cpp
     while(l<=n||r<=m){
         if(a[l]==0){
             c[++cnt]=0;
             l++;
             k++;
         }
         else if(b[r]==0){
             c[++cnt]=0;
             r++;
             k++;
         }
         else{
             if(k<a[l]&&k<b[r]){
                 puts("-1");
                 ok=1;
                 break;
             }
             if(k>=a[l])c[++cnt]=a[l],l++;
             else if(k>=b[r])c[++cnt]=b[r],r++;
         }
     }
     ```

2. **作者：xuanyuan_Niubi (赞：2)**  
   - **星级：4**  
   - **关键亮点**：  
     - 使用队列模拟操作序列，代码结构清晰，易于理解。  
     - 通过优先处理一个序列，确保$k$的最大化，减少无解情况的发生。  
   - **核心代码**：
     ```cpp
     while(!a.empty()||!b.empty()){
         if((a.front()>k&&b.front()>k)||(b.empty()&&a.front()>k)||(a.empty()&&b.front()>k)){
             fl=0;break;
         }
         int x=a.front();
         while(x<=k&&!a.empty()){
             if(x==0)k++;
             c.push(x);a.pop();x=a.front(); 
         }
         x=b.front();
         while(x<=k&&!b.empty()){
             if(x==0)k++;
             c.push(x);b.pop();x=b.front();
         }
     }
     ```

3. **作者：dalao_see_me (赞：1)**  
   - **星级：4**  
   - **关键亮点**：  
     - 使用双指针遍历两个序列，确保操作的顺序性。  
     - 通过优先选择0操作，确保$k$的最大化，代码简洁且高效。  
   - **核心代码**：
     ```cpp
     while(i<=n&&j<=m&&f){
         if(a[i]==0){
             c[++tot]=0;
             i++; len++;
             continue;
         }
         if(b[j]==0){
             c[++tot]=0;
             j++; len++;
             continue;
         }
         if(a[i]<=len){
             c[++tot]=a[i];
             i++;
             continue;
         }
         if(b[j]<=len){
             c[++tot]=b[j];
             j++;
             continue;
         }
         f=0;
     }
     ```

### 最优关键思路
- **优先选择0操作**：通过优先选择增加行数的操作，确保$k$最大化，从而为后续的修改操作提供更大的灵活性。
- **双指针或队列模拟**：使用双指针或队列模拟操作序列的合并过程，确保操作的顺序性。

### 可拓展之处
- **类似问题**：类似的问题可以出现在需要合并两个序列并确保某些条件的情况下，例如合并两个有序数组并保持有序性。
- **算法套路**：贪心算法在需要最大化或最小化某些条件时非常有用，尤其是在操作顺序固定的情况下。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：39.95秒