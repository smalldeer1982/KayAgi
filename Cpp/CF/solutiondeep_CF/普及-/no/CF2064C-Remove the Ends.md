# 题目信息

# Remove the Ends

## 题目描述

你有一个长度为 $n$ 的数组 $a$，其中元素均为非零整数。初始时你有 $0$ 枚硬币，你将重复以下操作直到 $a$ 变为空：
- 设当前数组 $a$ 的大小为 $m$。选择一个整数 $i$（$1 \le i \le m$），获得 $|a_i|$ $^{\text{∗}}$ 枚硬币，然后：
  - 如果 $a_i < 0$，则将 $a$ 替换为 $[a_1,a_2,\ldots,a_{i - 1}]$（即删除从 $a_i$ 开始的后缀）；
  - 否则，将 $a$ 替换为 $[a_{i + 1},a_{i + 2},\ldots,a_m]$（即删除以 $a_i$ 结尾的前缀）。

请计算最终你能获得的最大硬币数量。

 $^{\text{∗}}$ 此处 $|a_i|$ 表示 $a_i$ 的绝对值：当 $a_i > 0$ 时等于 $a_i$，当 $a_i < 0$ 时等于 $-a_i$。

## 说明/提示

第一个测试用例中获得 $23$ 枚硬币的操作示例：
- $a = [3, 1, 4, -1, -5, \text{\color{red}{-9}}] \xrightarrow{i = 6} a = [3, 1, 4, -1, -5]$，获得 $9$ 枚硬币。
- $a = [\text{\color{red}{3}}, 1, 4, -1, -5] \xrightarrow{i = 1} a = [1, 4, -1, -5]$，获得 $3$ 枚硬币。
- $a = [\text{\color{red}{1}}, 4, -1, -5] \xrightarrow{i = 1} a = [4, -1, -5]$，获得 $1$ 枚硬币。
- $a = [4, -1, \text{\color{red}{-5}}] \xrightarrow{i = 3} a = [4, -1]$，获得 $5$ 枚硬币。
- $a = [4, \text{\color{red}{-1}}] \xrightarrow{i = 2} a = [4]$，获得 $1$ 枚硬币。
- $a = [\text{\color{red}{4}}] \xrightarrow{i = 1} a = []$，获得 $4$ 枚硬币。

最终共获得 $23$ 枚硬币。

第二个测试用例中获得 $40$ 枚硬币的操作示例：
- $a = [-10, -3, -17, \text{\color{red}{1}}, 19, 20] \xrightarrow{i = 4} a = [19, 20]$，获得 $1$ 枚硬币。
- $a = [\text{\color{red}{19}}, 20] \xrightarrow{i = 1} a = [20]$，获得 $19$ 枚硬币。
- $a = [\text{\color{red}{20}}] \xrightarrow{i = 1} a = []$，获得 $20$ 枚硬币。

最终共获得 $40$ 枚硬币。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
6
3 1 4 -1 -5 -9
6
-10 -3 -17 1 19 20
1
1```

### 输出

```
23
40
1```

# AI分析结果

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路大多围绕着发现每次操作只会选择最左边的正数或者最右边的负数这一重要性质展开。通过预处理前缀正和以及后缀负和，再枚举正负分界点来找到能获得的最大硬币数量。
- **思路对比**：大部分题解思路相近，都是利用前缀和与后缀和的思想，如 nochiras、zzldd、Redshift_Shine 等。而 thedyingkai 是逐个加入元素考虑，hbhz_zcy 则是从操作序列的变化来推导。
- **算法要点**：主要是计算前缀正和与后缀负和，然后通过枚举分界点取最大值。部分题解使用了前缀和数组，部分题解则使用变量动态更新。
- **解决难点**：关键在于发现操作的最优策略，即每次选择最左边的正数或最右边的负数，然后合理地计算和统计结果。

### 所选题解
- **zzldd（4星）**：
  - **关键亮点**：思路清晰，代码简洁明了，注释详细，使用前缀和与后缀和数组，通过枚举位置计算最大硬币数。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long //一定要开long long,否则会挂
using namespace std;
int T,n,a[200005],qz[200005],hz[200005];
signed main(){
    cin>>T;
    while(T--){
        cin>>n;int ans=0;
        qz[0]=0,hz[n+1]=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            qz[i]=(a[i]>=0?qz[i-1]+a[i]:qz[i-1]); //前缀和
        }for(int i=n;i>=1;i--) hz[i]=(a[i]<0?hz[i+1]+abs(a[i]):hz[i+1]);  //后缀和
        for(int i=1;i<=n;i++) ans=max(qz[i]+hz[i],ans);
        cout<<ans<<"\n";
    }
}
```
核心实现思想：先计算前缀和数组 `qz` 记录前 `i` 个元素中正数的和，后缀和数组 `hz` 记录从 `i` 到 `n` 中负数的绝对值之和，然后枚举每个位置，取 `qz[i] + hz[i]` 的最大值作为结果。

- **Redshift_Shine（4星）**：
  - **关键亮点**：代码结构清晰，有调试信息，同样使用前缀和思想，通过枚举分界点计算最大硬币数。
  - **核心代码**：
```c++
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
using ll = long long;
ll a[N], pfp[N], pfn[N], res;
int n;
void init_local()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    for (int i = 1; i <= n; i++)
    {
        pfp[i] = pfp[i - 1];
        pfn[i] = pfn[i - 1];
        if (a[i] > 0)
            pfp[i] += a[i];
        if (a[i] < 0)
            pfn[i] -= a[i];
    }
}
void run()
{
    res = 0;
    for (int i = 0; i <= n; i++)
    {
        res = max(res, pfp[i] + pfn[n] - pfn[i]);
    }
    printf("%lld\n", res);
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
    {
        init_local();
        run();
    }
}
```
核心实现思想：`init_local` 函数中计算前缀正和 `pfp` 与前缀负和 `pfn`，`run` 函数中枚举分界点 `i`，计算 `pfp[i] + pfn[n] - pfn[i]` 的最大值作为结果。

### 最优关键思路或技巧
- **贪心策略**：发现每次操作选择最左边的正数或最右边的负数更优。
- **前缀和与后缀和**：通过预处理前缀正和与后缀负和，将问题转化为枚举分界点取最大值，降低时间复杂度。

### 拓展思路
同类型题可能会有不同的操作规则和条件，但核心思想可能还是围绕着贪心策略和前缀和、后缀和的运用。例如，改变操作的删除规则，或者增加更多的限制条件，都可以用类似的思路去分析和解决。

### 推荐洛谷题目
- P1169 [ZJOI2007] 棋盘制作
- P1719 最大加权矩形
- P2671 [NOIP2015 普及组] 求和

---
处理用时：29.62秒