# 题目信息

# Maximum Product

## 题目描述

You are given an array of integers $ a_1,a_2,\ldots,a_n $ . Find the maximum possible value of $ a_ia_ja_ka_la_t $ among all five indices $ (i, j, k, l, t) $ ( $ i<j<k<l<t $ ).

## 说明/提示

In the first test case, choosing $ a_1,a_2,a_3,a_4,a_5 $ is a best choice: $ (-1)\cdot (-2) \cdot (-3)\cdot (-4)\cdot (-5)=-120 $ .

In the second test case, choosing $ a_1,a_2,a_3,a_5,a_6 $ is a best choice: $ (-1)\cdot (-2) \cdot (-3)\cdot 2\cdot (-1)=12 $ .

In the third test case, choosing $ a_1,a_2,a_3,a_4,a_5 $ is a best choice: $ (-1)\cdot 0\cdot 0\cdot 0\cdot (-1)=0 $ .

In the fourth test case, choosing $ a_1,a_2,a_3,a_4,a_6 $ is a best choice: $ (-9)\cdot (-7) \cdot (-5)\cdot (-3)\cdot 1=945 $ .

## 样例 #1

### 输入

```
4
5
-1 -2 -3 -4 -5
6
-1 -2 -3 1 2 -1
6
-1 0 0 0 -1 -1
6
-9 -7 -5 -3 -2 1```

### 输出

```
-120
12
0
945```

# AI分析结果

### 题目内容
# 最大乘积

## 题目描述
给定一个整数数组 $a_1, a_2, \ldots, a_n$ 。在所有满足 $i < j < k < l < t$ 的五个索引 $(i, j, k, l, t)$ 中，找出 $a_ia_ja_ka_la_t$ 可能的最大值。

## 说明/提示
在第一个测试用例中，选择 $a_1, a_2, a_3, a_4, a_5$ 是最佳选择：$(-1) \cdot (-2) \cdot (-3) \cdot (-4) \cdot (-5) = -120$ 。

在第二个测试用例中，选择 $a_1, a_2, a_3, a_5, a_6$ 是最佳选择：$(-1) \cdot (-2) \cdot (-3) \cdot 2 \cdot (-1) = 12$ 。

在第三个测试用例中，选择 $a_1, a_2, a_3, a_4, a_5$ 是最佳选择：$(-1) \cdot 0 \cdot 0 \cdot 0 \cdot (-1) = 0$ 。

在第四个测试用例中，选择 $a_1, a_2, a_3, a_4, a_6$ 是最佳选择：$(-9) \cdot (-7) \cdot (-5) \cdot (-3) \cdot 1 = 945$ 。

## 样例 #1
### 输入
```
4
5
-1 -2 -3 -4 -5
6
-1 -2 -3 1 2 -1
6
-1 0 0 0 -1 -1
6
-9 -7 -5 -3 -2 1
```
### 输出
```
-120
12
0
945
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何从给定数组中选取5个数使得乘积最大展开。由于数组中存在负数，所以不能简单选择最大的5个数，需考虑负数个数对乘积正负性的影响。多数题解利用排序后根据负数个数的不同情况进行分析，少数采用搜索的方式。各题解思路相近，但实现细节和优化程度有所差异。

### 所选的题解
- **作者：_Aoi_ (4星)**
    - **关键亮点**：思路清晰，简洁明了地指出考虑负数情况下使5个数乘积最大的几种情况，并通过排序快速得出结果，代码简洁高效。
    - **个人心得**：强调不开long long可能导致错误结果。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,a[100010],ans1,ans2,ans3,ans=-1e9;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+n+1);
        ans1=a[n]*a[n-1]*a[n-2]*a[n-3]*a[n-4];
        ans2=a[1]*a[2]*a[n]*a[n-1]*a[n-2];
        ans3=a[1]*a[2]*a[3]*a[4]*a[n];
        ans=max(ans1,max(ans2,ans3));
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：对输入数组排序后，分别计算最大的5个数、最小的2个负数和最大的3个数、最小的4个负数和最大的1个数这三种组合的乘积，取其最大值作为结果。

- **作者：Tenshi (4星)**
    - **关键亮点**：提出一种独特的搜索思路，根据n的大小进行不同处理，n≤10时直接搜索，n＞10时取数组最小和最大的各5个数组成新数组再搜索，并证明了该方法的正确性。
    - **重点代码**：
```cpp
void dfs(int st,ll res){
    if(st==5){
        ans=max(ans,res);
        return;
    }
    for(int i=1;i<=min(n,10);i++){
        if(vis[i]) continue;

        vis[i]=1;
        dfs(st+1,res*rec[i]);
        vis[i]=0;
    }
}
int main(){
    cin>>T;
    while (T--)
    {
        cin>>n;
        FOR(i,1,n) cin>>a[i];
        sort(a+1,a+1+n);

        if(n<=10){
            FOR(i,1,n) rec[i]=a[i];
            ans=LLONG_MIN;
            dfs(0,1);
            cout<<ans<<endl;
        }
        else{
            FOR(i,1,5) rec[i]=a[i];
            FOR(i,n-4,n) rec[i-n+10]=a[i];
            ans=LLONG_MIN;
            dfs(0,1);
            cout<<ans<<endl;
        }
    }
    return 0;
}
```
核心实现思想：通过深度优先搜索（DFS）遍历可能的5个数的组合，根据n的大小确定搜索范围，从而找到最大乘积。

### 最优关键思路或技巧
利用排序结合贪心思想，根据负数个数的奇偶性，考虑不同的数的组合方式（如最大的5个数、最小的2个负数和最大的3个数、最小的4个负数和最大的1个数等组合）来获取最大乘积。同时，在处理较大数据规模时，可通过合理缩小搜索范围（如只考虑最大和最小的部分数）来优化算法。

### 可拓展之处
同类型题可拓展到选择不同个数的数求最大乘积，类似算法套路是先对数组排序，再根据数的正负性和要选择的数的个数，分析不同组合情况，利用贪心思想选取合适组合。

### 洛谷相似题目推荐
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)
- [P1094 [NOIP2007 普及组] 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908) 

---
处理用时：42.85秒