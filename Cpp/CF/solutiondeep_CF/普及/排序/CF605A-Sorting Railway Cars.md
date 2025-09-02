# 题目信息

# Sorting Railway Cars

## 题目描述

An infinitely long railway has a train consisting of $ n $ cars, numbered from $ 1 $ to $ n $ (the numbers of all the cars are distinct) and positioned in arbitrary order. David Blaine wants to sort the railway cars in the order of increasing numbers. In one move he can make one of the cars disappear from its place and teleport it either to the beginning of the train, or to the end of the train, at his desire. What is the minimum number of actions David Blaine needs to perform in order to sort the train?

## 说明/提示

In the first sample you need first to teleport the $ 4 $ -th car, and then the $ 5 $ -th car to the end of the train.

## 样例 #1

### 输入

```
5
4 1 2 5 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
4 1 3 2
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
# 铁路车厢排序

## 题目描述
有一条无限长的铁路，上面有一列由 $n$ 节车厢组成的火车，车厢编号从 $1$ 到 $n$（所有车厢的编号都是不同的），且排列顺序是任意的。大卫·布莱恩（David Blaine）想将这些铁路车厢按编号递增的顺序排列。在一次操作中，他可以让其中一节车厢从其位置消失，并将其传送到火车的开头或结尾，具体由他决定。那么，大卫·布莱恩为了将火车排序，最少需要执行多少次操作呢？

## 说明/提示
在第一个样例中，你需要先将第 $4$ 节车厢，然后将第 $5$ 节车厢传送到火车的末尾。

## 样例 #1
### 输入
```
5
4 1 2 5 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
4
4 1 3 2
```
### 输出
```
2
```

### 综合分析与结论
这些题解的核心思路都是将问题转化为求最长上升子序列（这里的上升子序列要求相邻元素差为 1）的问题，通过求出最长上升子序列的长度，用总长度减去该长度得到最少的移动次数。

- **思路**：为了使移动次数最少，就要让不需要移动的车厢尽可能多，而不需要移动的车厢组成的就是原序列中相邻元素差为 1 的最长上升子序列。
- **算法要点**：使用动态规划的思想，定义状态 $dp_i$ 表示以 $i$ 为结尾的最长上升子序列的长度，状态转移方程为 $dp_{a_i}=dp_{a_i - 1}+1$，其中 $a_i$ 是输入的车厢编号。
- **解决难点**：原问题看似复杂，但通过分析发现不需要移动的车厢的特征，将其转化为求最长上升子序列问题，避免了 $O(n^2)$ 的时间复杂度，利用桶标记的方法，将时间复杂度优化到 $O(n)$。

### 所选题解
- **作者：sxyugao (赞：18)，4星**
    - **关键亮点**：思路清晰，代码简洁，直接点明了问题的本质是求最长上升子序列，并通过桶标记的方法优化了时间复杂度。
```cpp
#include<cstdio>
int n,a,ans,f[500001];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a);
        f[a]=f[a-1]+1;
        if(f[a]>ans)ans=f[a];
    }
    printf("%d",n-ans);
}
```
核心实现思想：通过循环读取车厢编号，利用桶标记数组 $f$ 记录以每个编号为结尾的最长上升子序列的长度，不断更新最长上升子序列的长度 $ans$，最后用总长度 $n$ 减去 $ans$ 得到最少移动次数。

- **作者：_32bit_Silentnight (赞：7)，4星**
    - **关键亮点**：通过极端样例和特殊样例的分析，直观地展示了问题的规律，帮助理解思路。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b[200001]={0},i,m=-1,k=0,x;scanf("%d",&a);
    for(i=1;i<=a;i++){
        cin>>x;
        b[x]=b[x-1]+1;
        m=max(m,b[x]);
    }
    cout<<a-m;
}
```
核心实现思想：与上一题解类似，使用数组 $b$ 记录以每个编号为结尾的最长上升子序列的长度，更新最大值 $m$，最后输出 $a - m$。

- **作者：1qaz234Q (赞：2)，4星**
    - **关键亮点**：详细说明了动态规划的状态转移方程和边界条件，逻辑严谨。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int f[N];
int main(){
    int n;
    int maxn=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        int p;
        cin>>p;
        if(p==1){
            f[1]=1; 
        }
        else{
            f[p]=f[p-1]+1;
        }
        maxn=max(maxn,f[p]);
    }
    int ans=n-maxn; 
    cout<<ans;
}
```
核心实现思想：通过循环读取车厢编号，根据边界条件和状态转移方程更新数组 $f$，记录以每个编号为结尾的最长上升子序列的长度，更新最大值 $maxn$，最后输出 $n - maxn$。

### 最优关键思路或技巧
- **思维方式**：将排序问题转化为求最长上升子序列问题，通过分析不需要移动的元素的特征，简化问题。
- **算法优化**：利用桶标记的方法，避免了 $O(n^2)$ 的时间复杂度，将时间复杂度优化到 $O(n)$。

### 可拓展之处
同类型题可以是对其他序列进行排序，操作可能有所不同，但核心思路都是找出不需要移动的元素组成的子序列，通过减少移动次数来达到排序的目的。类似算法套路可以应用于其他动态规划问题，通过分析问题的特征，找到状态转移方程，从而解决问题。

### 推荐洛谷题目
- [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：求最长不上升子序列和最少拦截系统数。
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：求两个序列的最长公共子序列。
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：环形石子合并问题，涉及动态规划的应用。

### 个人心得
题解中未包含个人心得。

---
处理用时：40.74秒