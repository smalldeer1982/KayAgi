# 题目信息

# K-Periodic Array

## 题目描述

This task will exclusively concentrate only on the arrays where all elements equal 1 and/or 2.

Array $ a $ is $ k $ -period if its length is divisible by $ k $ and there is such array $ b $ of length $ k $ , that $ a $ is represented by array $ b $ written exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371A/53488bbee46df1b241cbadadd932aea80891152b.png) times consecutively. In other words, array $ a $ is $ k $ -periodic, if it has period of length $ k $ .

For example, any array is $ n $ -periodic, where $ n $ is the array length. Array $ [2,1,2,1,2,1] $ is at the same time 2-periodic and 6-periodic and array $ [1,2,1,1,2,1,1,2,1] $ is at the same time 3-periodic and 9-periodic.

For the given array $ a $ , consisting only of numbers one and two, find the minimum number of elements to change to make the array $ k $ -periodic. If the array already is $ k $ -periodic, then the required value equals $ 0 $ .

## 说明/提示

In the first sample it is enough to change the fourth element from 2 to 1, then the array changes to $ [2,1,2,1,2,1] $ .

In the second sample, the given array already is 4-periodic.

In the third sample it is enough to replace each occurrence of number two by number one. In this case the array will look as $ [1,1,1,1,1,1,1,1,1] $ — this array is simultaneously 1-, 3- and 9-periodic.

## 样例 #1

### 输入

```
6 2
2 1 2 2 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8 4
1 1 2 1 1 1 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
9 3
2 1 1 1 2 1 1 1 2
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# K-周期数组

## 题目描述
本任务仅关注所有元素均为1和/或2的数组。

数组 $a$ 是 $k$ -周期的，如果其长度能被 $k$ 整除，并且存在一个长度为 $k$ 的数组 $b$，使得数组 $a$ 由数组 $b$ 连续重复 $\frac{|a|}{k}$ 次构成。换句话说，数组 $a$ 是 $k$ -周期的，如果它有长度为 $k$ 的周期。

例如，任何数组对于其自身长度 $n$ 来说都是 $n$ -周期的。数组 $[2,1,2,1,2,1]$ 同时是2 -周期和6 -周期的，数组 $[1,2,1,1,2,1,1,2,1]$ 同时是3 -周期和9 -周期的。

对于给定的仅由1和2组成的数组 $a$，找出使其成为 $k$ -周期数组所需更改的最小元素数量。如果数组已经是 $k$ -周期的，那么所需值为0。

## 说明/提示
在第一个样例中，只需将第四个元素从2改为1，数组就变为 $[2,1,2,1,2,1]$ 。

在第二个样例中，给定的数组已经是4 -周期的。

在第三个样例中，只需将每个2替换为1。在这种情况下，数组将变为 $[1,1,1,1,1,1,1,1,1]$ ，这个数组同时是1 -周期、3 -周期和9 -周期的。

## 样例 #1
### 输入
```
6 2
2 1 2 2 2 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
8 4
1 1 2 1 1 1 2 1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
9 3
2 1 1 1 2 1 1 1 2
```
### 输出
```
3
```

### 算法分类
贪心

### 综合分析与结论
三道题解思路本质相同，均基于贪心策略。核心思路是对于每个周期位置，统计1和2出现的次数，将出现次数少的元素全部改为出现次数多的元素，累加这些更改次数即得到使数组成为k -周期数组所需更改的最小元素数量。不同点在于代码实现细节，如变量命名、输入输出方式、函数封装等。

### 所选的题解
 - **作者：Light_Star_RPmax_AFO (星级：4星)**
   - **关键亮点**：思路清晰，代码简洁明了，直接在循环中统计每个周期位置1和2出现次数，利用宏定义的取最小值函数计算结果。
   - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define mi(a,b) a<b?a:b
int n,k,b[110],a[10010],c[110],ans;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)if(a[i]==1)b[i%k]++;else c[i%k]++;
    for(int i=0;i<k;i++)ans+=mi(b[i],c[i]);
    printf("%d\n",ans);
    return 0;
}
```
核心实现思想：先输入数组长度n和周期k以及数组元素，然后遍历数组统计每个周期位置1和2出现的次数，最后累加每个周期位置出现次数少的元素个数得到结果。
 - **作者：Noby_Glds (星级：4星)**
   - **关键亮点**：代码简洁，通过巧妙的数组下标运算和简洁的代码逻辑实现需求。
   - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define N 110
using namespace std;
int n,k,a[N],s[N],ans;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i],s[i%k]+=(a[i]==1);
    for(int i=0;i<k;i++) ans+=min(s[i],n/k-s[i]);
    cout<<ans;
    return 0;
}
```
核心实现思想：输入n和k以及数组元素，在输入时统计每个周期位置1出现的次数，利用总个数与1出现次数差值得到2出现次数，累加每个周期位置出现次数少的元素个数得到结果。

### 最优关键思路或技巧
利用贪心策略，针对每个周期位置分别统计1和2的出现次数，将出现次数少的元素改为出现次数多的元素，从而保证更改次数最少。在代码实现上，通过巧妙利用数组下标取模运算来统计每个周期位置的元素出现情况，简化代码逻辑。

### 可拓展之处
同类型题可拓展到具有周期性规律且元素种类有限的数组问题，类似算法套路是针对周期内各位置元素情况进行统计分析，利用贪心策略做出最优选择。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：43.72秒