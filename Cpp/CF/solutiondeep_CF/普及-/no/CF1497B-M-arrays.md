# 题目信息

# M-arrays

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ consisting of $ n $ positive integers and a positive integer $ m $ .

You should divide elements of this array into some arrays. You can order the elements in the new arrays as you want.

Let's call an array $ m $ -divisible if for each two adjacent numbers in the array (two numbers on the positions $ i $ and $ i+1 $ are called adjacent for each $ i $ ) their sum is divisible by $ m $ . An array of one element is $ m $ -divisible.

Find the smallest number of $ m $ -divisible arrays that $ a_1, a_2, \ldots, a_n $ is possible to divide into.

## 说明/提示

In the first test case we can divide the elements as follows:

- $ [4, 8] $ . It is a $ 4 $ -divisible array because $ 4+8 $ is divisible by $ 4 $ .
- $ [2, 6, 2] $ . It is a $ 4 $ -divisible array because $ 2+6 $ and $ 6+2 $ are divisible by $ 4 $ .
- $ [9] $ . It is a $ 4 $ -divisible array because it consists of one element.

## 样例 #1

### 输入

```
4
6 4
2 2 8 6 9 4
10 8
1 1 1 5 2 4 4 8 6 7
1 1
666
2 2
2 4```

### 输出

```
3
6
1
1```

# AI分析结果

### 题目内容
# M-数组

## 题目描述
给定一个由 $n$ 个正整数组成的数组 $a_1, a_2, \ldots, a_n$ 以及一个正整数 $m$。

你需要将该数组的元素划分到一些数组中。你可以按照自己的意愿对新数组中的元素进行排序。

如果对于数组中任意两个相邻的数（对于每个 $i$，位置 $i$ 和 $i + 1$ 上的两个数称为相邻数），它们的和都能被 $m$ 整除，那么这个数组就称为 $m$ 可整除数组。只有一个元素的数组也是 $m$ 可整除数组。

求将 $a_1, a_2, \ldots, a_n$ 划分成 $m$ 可整除数组的最小数量。

## 说明/提示
在第一个测试用例中，我们可以按如下方式划分元素：
- $[4, 8]$。这是一个 $4$ 可整除数组，因为 $4 + 8$ 能被 $4$ 整除。
- $[2, 6, 2]$。这是一个 $4$ 可整除数组，因为 $2 + 6$ 和 $6 + 2$ 都能被 $4$ 整除。
- $[9]$。这是一个 $4$ 可整除数组，因为它只包含一个元素。

## 样例 #1
### 输入
```
4
6 4
2 2 8 6 9 4
10 8
1 1 1 5 2 4 4 8 6 7
1 1
666
2 2
2 4
```
### 输出
```
3
6
1
1
```

### 算法分类
数学

### 题解综合分析与结论
所有题解的核心思路均是利用数论知识，先将每个数对 $m$ 取模，不影响结果，之后通过“桶”记录取模后各余数的个数，再对不同余数情况进行分类讨论以确定最少分组数。各题解在具体分类讨论细节上略有差异，但本质相同。

### 所选的题解
 - **作者：江户川·萝卜 (5星)**
    - **关键亮点**：思路阐述清晰，对每种情况的分析详细，代码简洁明了，对边界情况考虑全面。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int c[100005];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        memset(c,0,sizeof(c));
        int n,m,val;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&val);
            c[val%m]++;
        }
        int ans=!!(c[0]);
        for(int i=1;i<=m/2;i++){
            int a=max(c[i],c[m-i]),b=min(c[i],c[m-i]);
            if(c[i]==0&&c[m-i]==0) continue;
            if(a==b||a==b+1) ans+=1;
            else ans+=1+(a-b-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：先统计每个数模 $m$ 后余数的个数，对于余数为 $0$ 的情况，只要存在就需单独一组；对于其他余数 $i$ 及其互补余数 $m - i$，根据它们出现次数的关系进行分类讨论，确定分组数。

### 最优关键思路或技巧
利用取模的性质简化问题，通过“桶”记录余数出现次数，对不同余数情况进行细致分类讨论来确定最少分组数。

### 可拓展思路
此类题目通常围绕数论性质展开，类似套路是先分析题目条件对应的数论规律，利用取模等操作简化问题，再通过合适的数据结构（如本题的“桶”）统计相关信息，最后分类讨论得出结果。

### 洛谷相似题目推荐
 - [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)
 - [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)
 - [P1572 计算分数](https://www.luogu.com.cn/problem/P1572)

---
处理用时：55.33秒