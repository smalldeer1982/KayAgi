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
有一次，鲍勃拿了一条由 $n$ 个方格组成的纸条（纸条的高度为 1 个方格）。他在每个方格中写了一个整数，这个整数可能是负数。他想知道有多少种方法可以将这条纸条剪成两段，使得其中一段上数字的和等于另一段上数字的和，并且每一段都包含正整数个方格。你能帮鲍勃解决这个问题吗？

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
这些题解主要围绕如何计算将纸条剪成两段且两段数字和相等的方案数展开，核心在于高效计算两段的和。不同题解采用了不同的方法，复杂度有所差异。
|作者|思路|算法要点|解决难点|复杂度|评分|
| ---- | ---- | ---- | ---- | ---- | ---- |
|zhangyuhan|枚举切割点，用前缀和计算两段和并比较|前缀和：i到j区间的和为s[j]-s[i]|高效计算区间和|$O(n)$|5星|
|_FILARET_|先求总和，通过前缀和s数组确定切割点|前缀和预处理，判断s[i]*2是否等于总和|避免用除法判断导致错误|$O(n)$|4星|
|lxzy_（方法1）|暴力求和，枚举切割点并分别计算两段和|双重循环分别计算两段和|无优化，复杂度高|$O(n^2)$|1星|
|lxzy_（方法2）|动态求和，初始计算两段和，循环更新|初始计算两段和，每次循环更新|避免重复计算|$O(n)$|4星|
|lxzy_（方法3）|前缀和，枚举切割点，用前缀和计算两段和|前缀和：前段和为s[i]，后段和为s[n]-s[i]|高效计算区间和|$O(n)$|4星|
|06ray|前缀和模拟，枚举切割点，比较两段和|前缀和：第i项后面数字之和为s[n]-s[i]|高效计算区间和|$O(n)$|4星|
|fls233666|枚举切割点，预处理前缀和数组判断合法性|预处理前缀和数组s，s[i][0]表示[1,i]和，s[i][1]表示[i,n]和|高效判断切割点合法性|$O(n)$|4星|
|loi_hjh|枚举切割点，动态更新左右和|动态更新左右和，判断左右和是否相等|避免重复计算|$O(n)$|4星|

### 所选题解
- **zhangyuhan（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了前缀和的应用，时间复杂度低。
    - **核心代码**：
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
核心思想：先读入数据并计算前缀和，然后枚举切割点，比较两段的和是否相等。

- **_FILARET_（4星）**
    - **关键亮点**：详细解释了前缀和的概念和应用，给出了后续练习题目。
    - **核心代码**：
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
    for(int i=1;i<=N;i++) {
        cin>>a[i];
        s[i]=s[i-1]+a[i];
        sum+=a[i];
    }
    for(int i=1;i<N;i++){
        if(s[i]*2==sum){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
```
核心思想：先读入数据，计算前缀和与总和，然后枚举切割点，判断s[i]*2是否等于总和。

- **lxzy_（方法3，4星）**
    - **关键亮点**：详细介绍了多种解题方法，对前缀和方法进行了清晰解释。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
const int N=1e5+50;
int a[N];
int s[N];
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];
    }

    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(s[i]==s[n]-s[i])
        {
            ans++;
        }
    }

    printf("%d",ans);
    return 0;
}
```
核心思想：先读入数据并计算前缀和，然后枚举切割点，比较前段和与后段和是否相等。

### 最优关键思路或技巧
使用前缀和预处理数组，将计算区间和的复杂度从 $O(n)$ 降至 $O(1)$，避免重复计算，从而将整体时间复杂度优化到 $O(n)$。

### 拓展思路
同类型题目通常涉及区间和的计算与比较，可使用前缀和、动态求和等方法优化。例如在求子数组和满足特定条件的问题中，都可以考虑前缀和的应用。

### 洛谷题目推荐
1. P3131 [USACO16JAN]子共七Subsequences Summing to Sevens
2. P2280 [HNOI2003]激光炸弹
3. P3406 海底高铁

### 个人心得摘录与总结
- **lxzy_**：尝试暴力求和方法时，因复杂度高导致超时，后通过优化求和操作，将复杂度降至 $O(n)$ 成功AC，说明在处理数据范围较大的题目时，要注意算法复杂度的优化。 

---
处理用时：39.47秒