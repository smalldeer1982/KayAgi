# 题目信息

# Intense Heat

## 题目描述

给定一个含有 $n$ 个数的数组，以及 $k$，求所有长度大于等于 $k$ 的子串的平均数最大值。

## 样例 #1

### 输入

```
4 3
3 4 1 2
```

### 输出

```
2.666666666666667
```

# AI分析结果

【题目内容】
# 酷热

## 题目描述

给定一个含有 $n$ 个数的数组，以及 $k$，求所有长度大于等于 $k$ 的子串的平均数最大值。

## 样例 #1

### 输入

```
4 3
3 4 1 2
```

### 输出

```
2.666666666666667
```

【综合分析与结论】
这些题解的核心思路都是利用前缀和来优化子串和的计算，进而求解长度大于等于 $k$ 的子串的平均数最大值。具体实现上，大部分题解通过两层循环枚举子串的起点和终点，利用前缀和在 $O(1)$ 时间内计算子串和，再计算平均数并更新最大值。

算法要点：
1. **前缀和计算**：通过前缀和数组 $sum$ 记录前 $i$ 个数的和，即 $sum[i] = sum[i - 1] + a[i]$。
2. **子串枚举**：使用两层循环枚举所有长度大于等于 $k$ 的子串，计算其平均数并更新最大值。

解决难点：
1. **前缀和的理解与运用**：理解前缀和的概念，以及如何利用前缀和在 $O(1)$ 时间内计算子串和。
2. **子串枚举的边界处理**：确保枚举的子串长度大于等于 $k$，避免越界。

【所选的题解】
- **Huhu12346（4星）**
  - 关键亮点：思路清晰，代码简洁，直接利用前缀和和两层循环求解问题。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double sum[5001],a[5001];
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        double dt=0;
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++)
        {            
            scanf("%lf",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        for(int i=m;i<=n;i++)
        {
            for(int j=1;j+i-1<=n;j++)
            {
                dt=max(dt,(sum[i+j-1]-sum[j-1])*1.0/i);
            }
        }
        printf("%.10f\n",dt);
    }
}
```
核心实现思想：先计算前缀和数组 $sum$，然后两层循环枚举子串长度 $i$ 和子串起点 $j$，计算子串和并更新最大值。

- **GossWandering（4星）**
  - 关键亮点：详细解释了前缀和的概念、作用和计算方法，代码中使用了快读优化。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define landingyu work();
#define AK return
#define IOI 0;
#define inf 0x3f3f3f3f
#define eps 0.00001
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
using namespace std;
double a[5010],sum[5010];
double maxx=-0x3f3f3f3f;
void work(){
    int n=read(),k=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++)
        for(int j=i+k-1;j<=n;j++)
            maxx=max(maxx,(sum[j]-sum[i-1])/(j-i+1));
    printf("%.8lf",maxx);
}
int main(){landingyu AK IOI}
```
核心实现思想：先通过快读读取输入，计算前缀和数组 $sum$，然后两层循环枚举子串起点 $i$ 和终点 $j$，计算子串和并更新最大值。

- **kimidonatsu（4星）**
  - 关键亮点：对前缀和的概念解释清晰，代码规范，注释详细。
  - 核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 50;
int n, k;
double ans;
double a[N], p[N];
int main() {
    scanf("%d %d", &n, &k);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &a[i]);
        p[i] = p[i - 1] + a[i];
    }
    for (int i = 1; i <= n - k + 1; i++) {
        for (int j = i + k - 1; j <= n; j++)
            ans = max(ans, ((p[j] - p[i - 1]) * 1.0 / (j - i + 1)));
    }
    printf("%.15lf\n", ans);
    return 0;
}
```
核心实现思想：先读取输入，计算前缀和数组 $p$，然后两层循环枚举子串起点 $i$ 和终点 $j$，计算子串和并更新最大值。

【最优的关键思路或技巧】
- **前缀和优化**：利用前缀和数组可以在 $O(1)$ 时间内计算任意子串的和，避免了每次都重新计算子串和的 $O(n)$ 复杂度，将整体复杂度从 $O(n^3)$ 降低到 $O(n^2)$。

【可拓展之处】
同类型题或类似算法套路：
1. 求数组中长度在一定范围内的子串的和的最大值或最小值。
2. 求数组中满足某些条件的子串的相关问题，如子串的乘积、异或和等。

【推荐题目】
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)
3. [P3131 [USACO16JAN]Subsequences Summing to Sevens S](https://www.luogu.com.cn/problem/P3131)

【个人心得】
- **kimidonatsu**：提到格式转换有坑，精度保留 $6$ 位即可，也可使用 `iomanip` 库中的 `setprecision`。总结：在处理浮点数输出时，要注意格式转换和精度问题。

---
处理用时：50.79秒