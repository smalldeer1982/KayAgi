# 题目信息

# Maximum Sum

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , where all elements are different.

You have to perform exactly $ k $ operations with it. During each operation, you do exactly one of the following two actions (you choose which to do yourself):

- find two minimum elements in the array, and delete them;
- find the maximum element in the array, and delete it.

You have to calculate the maximum possible sum of elements in the resulting array.

## 说明/提示

In the first testcase, applying the first operation produces the following outcome:

- two minimums are $ 1 $ and $ 2 $ ; removing them leaves the array as $ [5, 10, 6] $ , with sum $ 21 $ ;
- a maximum is $ 10 $ ; removing it leaves the array as $ [2, 5, 1, 6] $ , with sum $ 14 $ .

 $ 21 $ is the best answer.

In the second testcase, it's optimal to first erase two minimums, then a maximum.

## 样例 #1

### 输入

```
6
5 1
2 5 1 10 6
5 2
2 5 1 10 6
3 1
1 2 3
6 1
15 22 12 10 13 11
6 2
15 22 12 10 13 11
5 1
999999996 999999999 999999997 999999998 999999995```

### 输出

```
21
11
3
62
46
3999999986```

# AI分析结果

### 题目中文重写
# 最大和

## 题目描述
给定一个数组 $ a_1, a_2, \dots, a_n $，其中所有元素都不同。

你必须对其恰好执行 $ k $ 次操作。在每次操作中，你只需执行以下两个操作之一（你自己选择执行哪一个）：
- 找到数组中的两个最小元素，并删除它们；
- 找到数组中的最大元素，并删除它。

你需要计算结果数组中元素的最大可能和。

## 说明/提示
在第一个测试用例中，执行第一个操作会产生以下结果：
- 两个最小值是 $ 1 $ 和 $ 2 $；删除它们后，数组变为 $ [5, 10, 6] $，和为 $ 21 $；
- 最大值是 $ 10 $；删除它后，数组变为 $ [2, 5, 1, 6] $，和为 $ 14 $。

$ 21 $ 是最佳答案。

在第二个测试用例中，最优的做法是先删除两个最小值，然后删除一个最大值。

## 样例 #1
### 输入
```
6
5 1
2 5 1 10 6
5 2
2 5 1 10 6
3 1
1 2 3
6 1
15 22 12 10 13 11
6 2
15 22 12 10 13 11
5 1
999999996 999999999 999999997 999999998 999999995
```

### 输出
```
21
11
3
62
46
3999999986
```

### 算法分类
前缀和

### 综合分析与结论
这些题解主要围绕排序和前缀和来解决问题。整体思路是先对数组排序，然后通过枚举删除最小两个数和最大一个数的不同次数组合，利用前缀和快速计算剩余元素的和，从而找出最大和。部分题解使用双端队列来模拟操作过程。

各题解的算法要点在于排序保证数组有序，方便确定最小和最大元素，前缀和则优化了求和的时间复杂度。解决的难点在于如何合理枚举不同的操作组合，以及正确使用前缀和计算剩余元素的和。

### 所选题解
- **作者：LEle0309（4星）**
  - **关键亮点**：思路清晰，详细解释了前缀和的概念和使用方法，代码简洁易懂，注释丰富。
  - **核心实现思想**：先对数组排序，然后计算前缀和数组。通过枚举删除最小两数的次数 $i$，计算出删除最大数的次数 $k - i$，利用前缀和公式 $sum_{n-(k-i)}-sum_{2 \times i}$ 计算剩余元素的和，打擂台求最大值。
  - **核心代码**：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long//防见祖宗神器
using namespace std;
int a[200005],sum[200005],t,n,k,i;//俩数组
signed main()
{
    cin>>t;//t组数据
    while(t--)
    {
        int ans=0;
        memset(a,0,sizeof(a));//多测不清空，提交两行泪
        cin>>n>>k;
        for(i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+n+1);
        for(i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];//求前缀和
        for(i=0;i<=k;i++)ans=max(ans,sum[n-(k-i)]-sum[2*i]);//暴力枚举所有i，套公式，打擂台求最大值
        cout<<ans<<endl;//输出，注意换行
    }
    return 0;//养成好习惯
}
```
- **作者：FinderHT（4星）**
  - **关键亮点**：详细分析了朴素想法的时间复杂度问题，引出前缀和的优化方法，思路连贯，代码规范。
  - **核心实现思想**：先对数组排序，计算前缀和数组。枚举删除两个最小值的操作次数 $x$，得出删除最大值的次数 $k - x$，根据公式 $h_{n-(k-x)}-h_{2 \times x}$ 维护答案。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+10;
int a[MAXN];
ll h[MAXN];//由于前缀和增长速度快，所以用long long
inline void solve(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);//排序，数组保持有序是使所推出式子成立的条件
    for(int i=1;i<=n;i++)h[i]=h[i-1]+a[i];//前缀和
    ll maxa=0;
    for(int x=0;x<=k;x++)
        maxa=max(maxa,h[n-(k-x)]-h[2*x]);//排序后就可根据式子维护答案
    printf("%lld\n",maxa);
}
signed main(){
    int T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
```
- **作者：__Dist__（4星）**
  - **关键亮点**：明确指出多测要清空数组，提醒了可能出现的错误，代码简洁，逻辑清晰。
  - **核心实现思想**：排序数组，计算前缀和数组，枚举操作次数，利用前缀和公式维护最大值。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long//由于前缀和增长地很快，保险用long long
using namespace std;
const int MAXN=2e5+5;
int T;
int qzh[MAXN],a[MAXN],k,n;
signed main(){
    cin>>T;
    while(T--){
        memset(qzh,0,sizeof qzh);
        memset(a,0,sizeof a);//多测不清空，爆零两行泪
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+n+1);//排序
        for(int i=1;i<=n;i++){
            qzh[i]=qzh[i-1]+a[i];//求前缀和
        }
        int ans=0;
        for(int i=0;i<=k;i++)//别忘了是从0开始 
            ans=max(ans,qzh[n-(k-i)]-qzh[2*i]);//维护ans 
        cout<<ans<<endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
- 排序：将数组排序后，能方便地确定最小和最大元素，为后续操作提供基础。
- 前缀和：通过预处理前缀和数组，能在 $O(1)$ 时间内计算出任意区间的和，优化了求和的时间复杂度。
- 枚举：枚举删除最小两个数和最大一个数的不同次数组合，找出最大和。

### 可拓展之处
同类型题可能会有更多复杂的操作或条件，例如操作次数有限制、元素有重复等。类似算法套路可以应用在需要频繁计算区间和的题目中，通过前缀和优化时间复杂度。

### 推荐洛谷题目
- P1115 最大子段和
- P2671 [NOIP2015 普及组] 求和
- P3131 [USACO16JAN]Subsequences Summing to Sevens S

### 个人心得摘录与总结
- **WA_sir**：在语文课刚下课时突然想出解法，强调了排序和多组数据清空数组的重要性。总结是在日常学习中随时可能有解题灵感，同时要注意多测数据的处理，避免出错。

---
处理用时：49.60秒