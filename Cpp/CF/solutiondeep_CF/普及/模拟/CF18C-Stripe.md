# 题目信息

# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
0 0
```

### 输出

```
1
```

# AI分析结果

### 题目中文重写
# 条纹

## 题目描述
有一次，鲍勃拿了一条由 $n$ 个方格组成的纸条（纸条的高度为 1 个方格）。他在每个方格中都写了一个整数，这个整数可能是负数。他想知道有多少种方法可以将这条纸条剪成两段，使得其中一段上数字的和等于另一段上数字的和，并且每一段都包含正整数个方格。你能帮鲍勃解决这个问题吗？

## 样例 #1
### 输入
```
9
1 5 -6 7 9 -16 0 -2 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3
1 1 1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
2
0 0
```
### 输出
```
1
```

### 综合分析与结论
这些题解主要围绕如何计算将纸条剪成两段且两段数字和相等的方法数展开，核心在于高效计算不同区间的数字和。不同题解采用了不同的方法，各有优劣。
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|zhangyuhan|枚举切割点，用前缀和比较两段区间和|前缀和计算区间和，枚举切割点|避免重复计算区间和，将计算复杂度降为 $O(1)$|5星|
|_FILARET_|先求总和，通过前缀和数组确定切割点|前缀和预处理，判断切割点是否满足条件|避免嵌套循环导致的超时问题|4星|
|lxzy_（方法1）|暴力求和，枚举切割点并分别计算两段和|嵌套循环计算两段和|数据规模大时超时，时间复杂度 $O(N^2)$|1星|
|lxzy_（方法2）|动态求和，通过更新前后段和减少重复计算|初始化前后段和，循环更新和值|去除重复计算，将求和复杂度降为 $O(1)$|4星|
|lxzy_（方法3）|使用前缀和，通过前缀和数组计算两段和|前缀和预处理，比较前后段和|高效计算区间和|4星|
|06ray|用前缀和模拟，枚举切割点比较两段和|前缀和计算区间和，枚举切割点|避免暴力求和的高复杂度|4星|
|fls233666|预处理前缀和，枚举切割点判断合法性|预处理前后缀和，枚举切割点判断合法性|避免枚举后逐个求和的高复杂度|4星|
|loi_hjh|枚举切割点，动态更新左右段和|动态更新左右段和，判断是否相等|避免重复计算，降低复杂度|4星|

### 所选题解
- **zhangyuhan（5星）**
    - 关键亮点：思路清晰，代码简洁，利用前缀和高效解决问题，时间复杂度为 $O(n)$。
    - 核心代码：
```cpp
#include<iostream>
using namespace std;

int n,a[100010],s[100010];
int ans;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }
    for(int i=1;i<=n-1;i++){
        if(s[i]==s[n]-s[i])
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```
核心实现思想：先读入数据并计算前缀和数组 $s$，然后枚举切割点 $i$，比较 $s[i]$ 和 $s[n] - s[i]$ 是否相等，相等则方案数加 1。

- **_FILARET_（4星）**
    - 关键亮点：详细介绍了前缀和的概念和用途，代码注释清晰，还给出了相关练习题目。
    - 核心代码：
```cpp
#include <iostream>
using namespace std;
const int MAXN=100005;
int N;
long long a[MAXN]={0};
long long s[MAXN]={0};
long long sum=0;
int ans=0;

int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i];
        s[i]=s[i-1]+a[i];
        sum+=a[i];
    }
    for(int i=1;i<N;i++)
    {
        if(s[i]*2==sum)
        {
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：读入数据时计算前缀和数组 $s$ 以及总和 $sum$，然后枚举切割点 $i$，判断 $s[i] * 2$ 是否等于 $sum$，相等则方案数加 1。

- **lxzy_（方法2，4星）**
    - 关键亮点：针对暴力求和的重复计算问题进行优化，将求和复杂度降为 $O(1)$。
    - 核心代码：
```cpp
#include<cstdio>
using namespace std;
const int N=1e5+50;
int a[N];
int tot2;
int tot1;
int ans=0;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(i>1)
        {
           tot2+=a[i];
        }
    }
    if(n==1)
    {
        printf("0");
        return 0;
    }
    tot1+=a[1];
    if(tot1==tot2)
    {
        ans++;
    }
    for(int i=2;i<=n-1;i++)
    {
        tot1+=a[i];
        tot2-=a[i];
        if(tot1==tot2)
        {
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```
核心实现思想：初始化前段和 $tot1$ 为 $a[1]$，后段和 $tot2$ 为 $a[2]$ 到 $a[n]$ 的和，然后从 2 到 $n - 1$ 循环，每次更新 $tot1$ 和 $tot2$，并判断是否相等，相等则方案数加 1。

### 最优关键思路或技巧
使用前缀和预处理数组，将计算区间和的复杂度从 $O(n)$ 降为 $O(1)$，避免了重复计算，从而将整体时间复杂度降为 $O(n)$。

### 可拓展之处
同类型题或类似算法套路：可以拓展到二维前缀和问题，用于计算矩阵中某一区域的元素和；也可应用于区间查询问题，如查询数组中某一区间的和、最大值、最小值等。

### 推荐洛谷题目
1. P3131 [USACO16JAN]子共七Subsequences Summing to Sevens
2. P2280 [HNOI2003]激光炸弹
3. P3406 海底高铁

### 个人心得摘录与总结
- **lxzy_**：尝试暴力求和方法时，提交代码后发现超时，分析得出时间复杂度为 $O(N^2)$，数据范围大时无法通过，进而思考优化方法，采用动态求和和前缀和方法解决问题，最终成功 AC。总结是在面对算法问题时，要注意时间复杂度，避免暴力解法，可通过去除重复计算等方式进行优化。 

---
处理用时：41.18秒