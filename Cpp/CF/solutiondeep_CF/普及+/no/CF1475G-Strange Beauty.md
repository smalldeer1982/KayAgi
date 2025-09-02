# 题目信息

# Strange Beauty

## 题目描述

Polycarp found on the street an array $ a $ of $ n $ elements.

Polycarp invented his criterion for the beauty of an array. He calls an array $ a $ beautiful if at least one of the following conditions must be met for each different pair of indices $ i \ne j $ :

- $ a_i $ is divisible by $ a_j $ ;
- or $ a_j $ is divisible by $ a_i $ .

For example, if:

- $ n=5 $ and $ a=[7, 9, 3, 14, 63] $ , then the $ a $ array is not beautiful (for $ i=4 $ and $ j=2 $ , none of the conditions above is met);
- $ n=3 $ and $ a=[2, 14, 42] $ , then the $ a $ array is beautiful;
- $ n=4 $ and $ a=[45, 9, 3, 18] $ , then the $ a $ array is not beautiful (for $ i=1 $ and $ j=4 $ none of the conditions above is met);

Ugly arrays upset Polycarp, so he wants to remove some elements from the array $ a $ so that it becomes beautiful. Help Polycarp determine the smallest number of elements to remove to make the array $ a $ beautiful.

## 说明/提示

In the first test case, removing $ 7 $ and $ 14 $ will make array $ a $ beautiful.

In the second test case, the array $ a $ is already beautiful.

In the third test case, removing one of the elements $ 45 $ or $ 18 $ will make the array $ a $ beautiful.

In the fourth test case, the array $ a $ is beautiful.

## 样例 #1

### 输入

```
4
5
7 9 3 14 63
3
2 14 42
4
45 9 3 18
3
2 2 8```

### 输出

```
2
0
1
0```

# AI分析结果

### 题目翻译
## 奇怪的美丽

### 题目描述
Polycarp 在街道上发现了一个包含 $n$ 个元素的数组 $a$。

Polycarp 为数组的美丽定义了一个标准。他称一个数组 $a$ 是美丽的，当且仅当对于每一对不同的索引 $i \ne j$，至少满足以下条件之一：
- $a_i$ 能被 $a_j$ 整除；
- 或者 $a_j$ 能被 $a_i$ 整除。

例如：
- 当 $n = 5$ 且 $a = [7, 9, 3, 14, 63]$ 时，数组 $a$ 不是美丽的（当 $i = 4$ 且 $j = 2$ 时，上述两个条件都不满足）；
- 当 $n = 3$ 且 $a = [2, 14, 42]$ 时，数组 $a$ 是美丽的；
- 当 $n = 4$ 且 $a = [45, 9, 3, 18]$ 时，数组 $a$ 不是美丽的（当 $i = 1$ 且 $j = 4$ 时，上述两个条件都不满足）。

丑陋的数组会让 Polycarp 心烦，所以他想从数组 $a$ 中移除一些元素，使其变得美丽。请帮助 Polycarp 确定最少需要移除多少个元素才能使数组 $a$ 变得美丽。

### 说明/提示
在第一个测试用例中，移除 $7$ 和 $14$ 会使数组 $a$ 变得美丽。
在第二个测试用例中，数组 $a$ 已经是美丽的。
在第三个测试用例中，移除元素 $45$ 或 $18$ 中的一个会使数组 $a$ 变得美丽。
在第四个测试用例中，数组 $a$ 是美丽的。

### 样例 #1
#### 输入
```
4
5
7 9 3 14 63
3
2 14 42
4
45 9 3 18
3
2 2 8
```
#### 输出
```
2
0
1
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解大多围绕动态规划来解决问题，核心思路是通过状态定义和状态转移来找出满足条件的最大子集大小，再用原数组长度减去该大小得到最少移除元素的数量。不同题解的差异主要体现在状态定义、转移方式以及优化策略上。

### 所选题解
- **Cutest_Junior（5星）**
    - **关键亮点**：思路清晰，对不同复杂度的做法逐步分析和优化，从 $O(N^2)$ 的朴素 DP 到 $O(N\sqrt{N})$ 枚举因数的 DP，再到 $O(N\log N)$ 枚举倍数的 DP，最后通过桶计数优化避免重复计算，代码实现也较为简洁。
    - **个人心得**：在优化过程中，发现枚举倍数的做法在特殊数据下复杂度会退化为 $O(N^2)$，从而进一步思考并采用桶计数的方式优化，体现了对算法复杂度的深入理解和优化能力。
- **zjjws（4星）**
    - **关键亮点**：提出枚举质因子的优化思路，避免了枚举倍数时产生的大量无用计算，虽然复杂度同阶但能提高效率，并且详细阐述了正序和倒序 DP 的区别，有独特的思考角度。
    - **个人心得**：一开始想建图，但发现枚举倍数会有大量无用边，从而想到只连质因数次数减 1 的边，最后在实现时没有真的建图，体现了对问题的深入分析和灵活处理。
- **I_am_Accepted（4星）**
    - **关键亮点**：思路简洁明了，通过证明子集满足两两呈倍数关系等价于相邻两数呈倍数关系，简化了问题，代码实现也较为清晰。

### 重点代码
#### Cutest_Junior 最终优化代码
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int arr[N];
int dp[N];

void run() {
    int n;
    scanf("%d", &n);
    memset(arr, 0, sizeof arr);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        ++arr[x];
    }
    memset(dp, 0, sizeof dp);
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        dp[i] += arr[i];
        ans = max(ans, dp[i]);
        for (int j = i + i; j < N; j += i) {
            dp[j] = max(dp[j], dp[i]);
        }
    }
    printf("%d\n", n - ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        run();
    }
}
```
**核心实现思想**：使用桶计数统计每个数的出现次数，$dp[i]$ 表示以 $i$ 为最大数的最大集合大小，通过枚举 $i$ 的倍数更新 $dp$ 值，最后用数组长度减去最大集合大小得到最少移除元素的数量。

#### zjjws 代码
```cpp
const int N=2e5+3;

bool pri[N];
int prime[N];
int cutt;
inline void init()
{
    for(int i=2;i<N;i++)
    {
        if(!pri[i])prime[++cutt]=i;
        for(int j=1;j<=cutt;j++)
        {
            int now=i*prime[j];
            if(now>=N)break;
            pri[now]=true;
            if(i%prime[j]==0)break;
        }
    }
    return;
}

int a[N];
int b[N];
int f[N];
inline void work()
{
    int n=rin();
    memset(b,0,sizeof(b));
    memset(f,0,sizeof(f));
    int maxs=0;
    int ans=0;
    for(int i=1,x;i<=n;i++)b[(x=rin())]++,maxs=max(maxs,x);
    for(int i=1;i<=maxs;i++)
    {
        f[i]+=b[i];
        ans=max(ans,f[i]);
        if(f[i])
        {
            for(int j=1;j<=cutt;j++)
            {
                int now=i*prime[j];
                if(now>maxs)break;
                f[now]=max(f[now],f[i]);
            }
        }
    }
    printf("%d\n",n-ans);
    return;
}
```
**核心实现思想**：先预处理质数，使用桶计数统计每个数的出现次数，$f[i]$ 表示以 $i$ 为最大数的最大集合大小，通过枚举 $i$ 的质因子倍数更新 $f$ 值，最后用数组长度减去最大集合大小得到最少移除元素的数量。

#### I_am_Accepted 代码
```cpp
int n;
int a[N];
int pos[N];
int ans[N];
int out;
void work(){
    cin>>n;
    For(i,1,n) cin>>a[i];
    sort(a+1,a+1+n);
    For(i,0,N-1) pos[i]=0;
    For(i,1,n){
        ans[i]=0;
        for(int x=1,y;x*x<=a[i];x++){
            if(a[i]%x) continue;
            y=a[i]/x;
            ckmx(ans[i],ans[pos[x]]+1);
            ckmx(ans[i],ans[pos[y]]+1);
        }
        pos[a[i]]=i;
    }
    out=0;
    For(i,1,n) ckmx(out,ans[i]);
    cout<<n-out<<endl;
}
```
**核心实现思想**：对数组排序，记录每个数最后出现的位置，$ans[i]$ 表示以 $a[i]$ 为最大值的满足题意子集的最大大小，通过枚举 $a[i]$ 的因数更新 $ans$ 值，最后用数组长度减去最大子集大小得到最少移除元素的数量。

### 扩展思路
同类型题或类似算法套路：这类题目通常围绕整除关系和动态规划展开，可能会有不同的数据范围和条件变化。例如，可能会要求找出满足特定整除关系的最长上升子序列，或者在二维数组中寻找满足整除关系的路径等。解题的关键在于合理定义状态和状态转移方程，同时根据数据范围选择合适的优化策略。

### 推荐洛谷题目
1. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)：经典的 0 - 1 背包问题，与本题的动态规划思想类似，通过状态转移来求解最优解。
2. [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：简单的动态规划入门题，通过递推的方式求解从顶部到底部的最大路径和。
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，与本题的动态规划思想有一定关联，通过状态转移来求解最大价值。

---
处理用时：68.56秒