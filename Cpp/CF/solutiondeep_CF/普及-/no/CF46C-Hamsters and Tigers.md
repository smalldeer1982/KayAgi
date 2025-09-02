# 题目信息

# Hamsters and Tigers

## 题目描述

**题目大意：**

给你个**环**，环上有$n(2<=n<=1000)$个点，每个点为黑色（题目中的仓鼠）或白色（题目中的老虎），你每次可以交换两个点的位置，求最少交换次数使得黑点白点分离（即黑点连续，中间没有白点）

## 样例 #1

### 输入

```
3
HTH
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9
HTHTHTHHT
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
本题内容为中文，无需翻译。

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路基本一致，都是先统计 `H` 的数量，将环转化为链，再利用前缀和来计算长度为 `H` 总数量的连续序列中 `H` 最多的情况，最后用 `H` 的总数量减去这个最大值得到最少交换次数。部分题解将部分功能封装成函数，提高了代码的可读性和可维护性；部分题解考虑了小数据的特判。不同题解在代码实现细节和变量命名上有所差异，但整体思路相同。

### 所选题解
- **作者：lsy_41 (赞：9)，4星**
    - **关键亮点**：思路清晰，代码简洁，对关键步骤有注释。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define maxn 1000005
using namespace std;
int n, sum[maxn << 1], cnt, ans;
char A[maxn << 1]; 
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        if (A[i] == 'H') cnt++; 
    }
    for (int i = n + 1; i < n + cnt; i++)
        A[i] = A[(i - 1) % n + 1];
    for (int i = 1; i < n + cnt; i++)
        sum[i] = sum[i - 1] + (A[i] == 'H'); 
    for (int i = 1; i <= n; i++) {
        ans = max(ans, sum[i + cnt - 1] - sum[i - 1]); 
    }
    cout << cnt - ans;
    return 0;
}
```
    - **核心实现思想**：先统计 `H` 的数量 `cnt`，将环转化为链，计算前缀和 `sum`，然后遍历找出长度为 `cnt` 的连续序列中 `H` 最多的情况，用 `cnt` 减去这个最大值得到答案。

- **作者：分离性漫游 (赞：3)，4星**
    - **关键亮点**：思路简洁明了，代码实现直接。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,h,ans,sum[10005];
char a[100005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]=='H') h++;
    }
    for(int i=n+1;i<n+h;i++) a[i]=a[(i-1)%n+1];
    for(int i=1;i<n+h;i++) sum[i]=sum[i-1]+(a[i]=='H');
    for(int i=1;i<=n;i++) ans=max(ans,sum[i+h-1]-sum[i-1]);
    cout<<h-ans;
    return 0;
}
```
    - **核心实现思想**：与 lsy_41 的题解思路一致，先统计 `H` 的数量，将环转化为链，计算前缀和，找出最长连续 `H` 的数量，用 `H` 的总数减去该数量得到最少交换次数。

- **作者：togeth1 (赞：1)，4星**
    - **关键亮点**：对思路有详细的文字解释，代码注释清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[100010];
int n,k,ans,s[10010];
int main()
{
    cin>>n>>(a+1);
    for(int i=1; i<=n; i++)
        k+=(a[i]=='H');
    for(int i=n+1; i<n+k; i++)
        a[i]=a[(i-1)%n+1];
    for(int i=1; i<n+k; i++)
        s[i]=s[i-1]+(a[i]=='H');
    for(int i=1; i<=n; i++)
        ans=max(ans,s[i+k-1]-s[i-1]);
    cout<<k-ans;
    return 0;
}
```
    - **核心实现思想**：同样是先统计 `H` 的数量，破环为链，计算前缀和，找出最长连续 `H` 的数量，用总数减去该数量得到答案。

### 最优关键思路或技巧
- **破环为链**：将环形问题转化为链形问题，方便处理。
- **前缀和**：利用前缀和可以快速计算出任意区间内 `H` 的数量，时间复杂度为 $O(1)$。

### 拓展思路
同类型题或类似算法套路：涉及环形数据处理的问题，通常可以采用破环为链的方法；对于需要频繁查询区间和的问题，可以使用前缀和优化。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察前缀和与最大子段和的计算。
2. [P3131 [USACO16JAN]Subsequences Summing to Sevens S](https://www.luogu.com.cn/problem/P3131)：涉及前缀和与取模运算。
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：需要运用前缀和来优化计算。

### 个人心得
- **作者：Szr__QAQ**：提到将部分内容封装成函数，养成这类习惯有助于在调试时修改代码。这体现了良好的代码编写习惯，将功能模块化可以提高代码的可读性和可维护性。

---
处理用时：33.91秒