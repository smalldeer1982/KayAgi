# 题目信息

# Mystic Permutation

## 题目描述

Monocarp is a little boy who lives in Byteland and he loves programming.

Recently, he found a permutation of length $ n $ . He has to come up with a mystic permutation. It has to be a new permutation such that it differs from the old one in each position.

More formally, if the old permutation is $ p_1,p_2,\ldots,p_n $ and the new one is $ q_1,q_2,\ldots,q_n $ it must hold that $ $$$p_1\neq q_1, p_2\neq q_2, \ldots ,p_n\neq q_n. $ $$$

Monocarp is afraid of lexicographically large permutations. Can you please help him to find the lexicographically minimal mystic permutation?

## 说明/提示

In the first test case possible permutations that are mystic are $ [2,3,1] $ and $ [3,1,2] $ . Lexicographically smaller of the two is $ [2,3,1] $ .

In the second test case, $ [1,2,3,4,5] $ is the lexicographically minimal permutation and it is also mystic.

In third test case possible mystic permutations are $ [1,2,4,3] $ , $ [1,4,2,3] $ , $ [1,4,3,2] $ , $ [3,1,4,2] $ , $ [3,2,4,1] $ , $ [3,4,2,1] $ , $ [4,1,2,3] $ , $ [4,1,3,2] $ and $ [4,3,2,1] $ . The smallest one is $ [1,2,4,3] $ .

## 样例 #1

### 输入

```
4
3
1 2 3
5
2 3 4 5 1
4
2 3 1 4
1
1```

### 输出

```
2 3 1
1 2 3 4 5
1 2 4 3
-1```

# AI分析结果

### 题目内容
# 神秘排列

## 题目描述
莫诺卡普是一个住在比特兰的小男孩，他热爱编程。
最近，他发现了一个长度为 $n$ 的排列。他必须想出一个神秘排列。这个新排列必须与原排列在每个位置上都不同。
更正式地说，如果原排列是 $p_1,p_2,\ldots,p_n$，新排列是 $q_1,q_2,\ldots,q_n$，那么必须满足 $p_1\neq q_1, p_2\neq q_2, \ldots, p_n\neq q_n$。
莫诺卡普害怕字典序较大的排列。你能帮他找到字典序最小的神秘排列吗？

## 说明/提示
在第一个测试用例中，可能的神秘排列是 $[2,3,1]$ 和 $[3,1,2]$。两者中字典序较小的是 $[2,3,1]$。
在第二个测试用例中，$[1,2,3,4,5]$ 是字典序最小的排列，并且它也是神秘排列。
在第三个测试用例中，可能的神秘排列是 $[1,2,4,3]$，$[1,4,2,3]$，$[1,4,3,2]$，$[3,1,4,2]$，$[3,2,4,1]$，$[3,4,2,1]$，$[4,1,2,3]$，$[4,1,3,2]$ 和 $[4,3,2,1]$。其中最小的是 $[1,2,4,3]$。

## 样例 #1
### 输入
```
4
3
1 2 3
5
2 3 4 5 1
4
2 3 1 4
1
1
```
### 输出
```
2 3 1
1 2 3 4 5
1 2 4 3
-1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路大多基于贪心策略，旨在构造字典序最小的神秘排列。各题解都先对 $n = 1$ 的无解情况进行特判。主要难点在于处理当原排列的第 $n$ 位为 $n$ 时，如何调整以满足条件且保证字典序最小。多数题解采用在遍历到第 $n - 1$ 位时，若第 $n$ 个数未被使用，则先输出第 $n$ 个数并标记，然后继续遍历的方法；部分题解采用交换第 $n$ 位和第 $n - 1$ 位数字的方式。部分题解还使用标记数组记录数字是否已被使用，以避免重复。

### 所选的题解
- **作者：qW__Wp (5星)**
    - **关键亮点**：思路清晰，先对 $n = 1$ 特判，贪心策略明确，先排序原数组，从最小数开始选，利用标记数组判断数字是否可用，最后针对最后一位的特殊情况进行交换处理，代码实现简洁明了。
    - **重点代码**：
```cpp
if(n==1){
    cout<<"-1\n";
    continue;
}
sort(a1+1,a1+n+1);
for(int i=1;i<=n;i++){
    if(vis[i]){
        continue;
    }
    for(int j=1;j<=n;j++){
        if(a1[j]!=a[i]&&!visj[j]){
            a[i]=a1[j];
            vis[i]=1;
            visj[j]=1;
            break;
        }
    }
}
if(!vis[n]){
    a[n]=a[n-1];
    a[n-1]=a1[n];
}
```
核心实现思想：对原数组排序后，从前往后遍历原排列，为每个位置选择未使用且与原位置数字不同的最小数字，若最后一位无法满足条件则与倒数第二位交换。
- **作者：KidzzZip (4星)**
    - **关键亮点**：解题思路简洁易懂，直接暴力枚举，从 $1$ 到 $n$ 为每个位置选择数字，同样对 $n = 1$ 特判，在处理最后一位数字时考虑了与倒数第二位数字交换的情况，代码可读性较好。
    - **重点代码**：
```cpp
if(m==1){
    cin>>a[1];
    cout<<"-1\n";
    continue;
}
for(int i=1;i<=m;i++){
    if(i==m-1&&!flag[a[m]]){
        cout<<a[m]<<' ';
        flag[a[m]]=true;
    }
    for(int j=1;j<=m;j++){
        if(!flag[j]&&j!=a[i]){
            cout<<j<<' ';
            flag[j]=true;
            break;
        }
    }
}
```
核心实现思想：从前往后遍历原排列，为每个位置在未使用且与原位置数字不同的数字中选择最小的，当遍历到倒数第二位且最后一位数字未被使用时，先输出最后一位数字。
- **作者：skyskyCCC (4星)**
    - **关键亮点**：详细分析了暴力枚举过程中可能出现的漏洞，即原排列最后一位为 $n$ 时的特殊情况，并提出将 $n$ 与第 $n - 1$ 个位置元素交换的解决方法，代码注释详细，便于理解。
    - **重点代码**：
```cpp
if(n==1){
    cin>>p[1];
    cout<<"-1\n";
    continue;
}
for(int i=1;i<=n;i++){
    if(i==n-1&&pd[p[n]]==0){
        cout<<p[n]<<" ";
        pd[p[n]]=1;
    }
    for(int j=1;j<=n;j++){
        if(j!=p[i]&&pd[j]==0){
            cout<<j<<" ";
            pd[j]=1;
            break;
        }
    }
}
```
核心实现思想：从前往后遍历原排列，为每个位置选择合适数字，当遍历到倒数第二位且最后一位数字未被使用时，先输出最后一位数字，保证前 $n - 2$ 位字典序最小。

### 最优关键思路或技巧
在构造字典序最小的排列时，采用贪心策略，从最小数字开始尝试放置在当前位置，同时利用标记数组记录数字使用情况以避免重复。针对原排列最后一位为 $n$ 这种特殊情况，通过将 $n$ 与第 $n - 1$ 位数字交换的方式保证满足条件且字典序相对较小。

### 拓展
此类题目属于构造类问题，通常需根据给定条件构造出符合要求的数据排列。类似套路包括先确定特殊情况（如本题 $n = 1$），再采用贪心等策略处理一般情况，过程中常借助标记数组辅助判断。

### 推荐题目
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：通过二分查找和贪心策略解决数列分段问题，与本题类似，需在满足一定条件下构造最优解。
- [P2871 [USACO07DEC]手链Charm Bracelet](https://www.luogu.com.cn/problem/P2871)：典型的背包问题，利用动态规划和贪心思想，在有限容量下选择物品以达到最优价值，可锻炼贪心和动态规划结合的思维。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据贪心策略对数据进行排序，以解决排队接水时间最短的问题，与本题同样是通过合理排序和贪心选择构造最优方案。 

---
处理用时：63.56秒