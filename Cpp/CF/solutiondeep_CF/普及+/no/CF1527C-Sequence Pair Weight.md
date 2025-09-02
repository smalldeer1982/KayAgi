# 题目信息

# Sequence Pair Weight

## 题目描述

The weight of a sequence is defined as the number of unordered pairs of indexes $ (i,j) $ (here $ i \lt j $ ) with same value ( $ a_{i} = a_{j} $ ). For example, the weight of sequence $ a = [1, 1, 2, 2, 1] $ is $ 4 $ . The set of unordered pairs of indexes with same value are $ (1, 2) $ , $ (1, 5) $ , $ (2, 5) $ , and $ (3, 4) $ .

You are given a sequence $ a $ of $ n $ integers. Print the sum of the weight of all subsegments of $ a $ .

A sequence $ b $ is a subsegment of a sequence $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

- In test case $ 1 $ , all possible subsegments of sequence $ [1, 2, 1, 1] $ having size more than $ 1 $ are: 
  1. $ [1, 2] $ having $ 0 $ valid unordered pairs;
  2. $ [2, 1] $ having $ 0 $ valid unordered pairs;
  3. $ [1, 1] $ having $ 1 $ valid unordered pair;
  4. $ [1, 2, 1] $ having $ 1 $ valid unordered pairs;
  5. $ [2, 1, 1] $ having $ 1 $ valid unordered pair;
  6. $ [1, 2, 1, 1] $ having $ 3 $ valid unordered pairs.
  
   Answer is $ 6 $ .
- In test case $ 2 $ , all elements of the sequence are distinct. So, there is no valid unordered pair with the same value for any subarray. Answer is $ 0 $ .

## 样例 #1

### 输入

```
2
4
1 2 1 1
4
1 2 3 4```

### 输出

```
6
0```

# AI分析结果

### 题目内容翻译
# 序列对权重

## 题目描述
序列的权重定义为值相同的无序索引对 $(i, j)$（其中 $i < j$）的数量。例如，序列 $a = [1, 1, 2, 2, 1]$ 的权重是 $4$。值相同的无序索引对集合是 $(1, 2)$、$(1, 5)$、$(2, 5)$ 和 $(3, 4)$。

给定一个包含 $n$ 个整数的序列 $a$。请输出 $a$ 的所有子段的权重之和。

如果序列 $b$ 可以通过从序列 $a$ 的开头删除若干（可能为零个或全部）元素，以及从结尾删除若干（可能为零个或全部）元素得到，那么序列 $b$ 就是序列 $a$ 的一个子段。

## 说明/提示
- 在测试用例 1 中，序列 $[1, 2, 1, 1]$ 所有长度大于 1 的可能子段为：
  1. $[1, 2]$，有 $0$ 个有效的无序对；
  2. $[2, 1]$，有 $0$ 个有效的无序对；
  3. $[1, 1]$，有 $1$ 个有效的无序对；
  4. $[1, 2, 1]$，有 $1$ 个有效的无序对；
  5. $[2, 1, 1]$，有 $1$ 个有效的无序对；
  6. $[1, 2, 1, 1]$，有 $3$ 个有效的无序对。
  
  答案是 $6$。
- 在测试用例 2 中，序列的所有元素都是不同的。因此，对于任何子数组，都没有值相同的有效无序对。答案是 $0$。

## 样例 #1
### 输入
```
2
4
1 2 1 1
4
1 2 3 4
```

### 输出
```
6
0
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是计算每个相等元素对在所有子段中产生的贡献，再将所有贡献累加得到最终结果。不同题解在实现细节和优化方式上有所不同。
- **思路对比**：多数题解通过计算包含相等元素对的子段数量来确定贡献，部分题解采用离散化处理大值域问题，还有题解使用动态规划的思想。
- **算法要点**：计算包含相等元素对 $[i, j]$ 的子段数量为 $i\times(n - j + 1)$；使用 map 或离散化处理元素值；部分题解使用前缀和优化计算。
- **解决难点**：处理大值域时，部分题解采用离散化；避免超时，部分题解使用前缀和优化时间复杂度。

### 所选题解
- **作者：npqenqpve（5星）**
  - **关键亮点**：思路清晰，代码简洁，直接使用 map 统计每个元素的下标和，计算贡献，时间复杂度低。
- **作者：ZCETHAN（4星）**
  - **关键亮点**：详细解释了计算贡献的原理，使用离散化处理大值域问题，避免了使用 map 带来的额外开销。
- **作者：_xbn（4星）**
  - **关键亮点**：采用动态规划的思想，设 $f(i)$ 表示所有以 $i$ 结尾的子段的权重和，通过 map 记录之前相等元素的下标，实现转移。

### 重点代码
#### npqenqpve 的代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long 
#define ld long double
using namespace std;
int t,a[100005],b[100005];
map<int,int>num;
signed main()
{
    cin>>t;
    while(t--)
    {
        int n;cin>>n;
        for(int i=1;i<=n+1;i++) a[i]=0;
        num.clear();
        for(int i=1;i<=n;i++) 
        {
            cin>>a[i];
        }
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            ans+=num[a[i]]*(n-i+1);
            num[a[i]]+=i;
        }
        cout<<ans<<"\n";
    }
    system("pause");
}
```
**核心实现思想**：使用 map 记录每个元素之前出现的下标和，对于每个元素，计算其与之前相同元素对答案的贡献，即 `num[a[i]]*(n - i + 1)`，然后更新 map 中该元素的下标和。

#### ZCETHAN 的代码
```cpp
#include<bits/stdc++.h>
#define inf 1<<30
#define INF 1ll<<60
#define ll long long
using namespace std;
const int MAXN=1e5+10;
int a[MAXN],b[MAXN];
ll sum[MAXN];
void solve(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    int cnt=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
    //离散化
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(!sum[a[i]]) sum[a[i]]+=i;
        else{
            ans+=sum[a[i]]*(n-i+1);
            sum[a[i]]+=i;
        }
    }printf("%lld\n",ans);
    for(int i=1;i<=cnt;i++) sum[i]=0;
}
int main()
{
    int T;
    for(scanf("%d",&T);T--;)
        solve();
}
```
**核心实现思想**：先对元素进行离散化，将大值域映射到小范围。然后使用数组 `sum` 记录每个离散化后元素的下标和，对于每个元素，计算其与之前相同元素对答案的贡献，即 `sum[a[i]]*(n - i + 1)`，然后更新 `sum` 数组。

#### _xbn 的代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 600002;
int n, m, k, p, ans, sum, t, tot, cnt, a[N], b[N], c[N], d[N], f[N];
map<int,int> mp;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch))
    {
        if(ch == '-') f=-1;
        ch = getchar();
    }
    while(isdigit(ch))
    {
        x=(x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
signed main()
{
    int T = read();
    while(T--)
    {
        n = read();
        mp.clear();
        ans = 0;
        for(int i = 1; i <= n; i++)
        {
            a[i] = read();
            f[i] = 0;
        }
        for(int i = 1; i <= n; i++)
        {
            if(i > 1) f[i] = f[i - 1];
            if(mp.count(a[i]))
            {
                f[i] += mp[a[i]];
            }
            mp[a[i]] += (i);
            ans += f[i];
        }
        cout << ans << endl;
    }
    return 0;
}
```
**核心实现思想**：设 $f(i)$ 表示所有以 $i$ 结尾的子段的权重和，使用 map 记录之前相等元素的下标和。对于每个元素，若之前有相同元素，则更新 $f(i)$，并将 $f(i)$ 累加到答案中，同时更新 map 中该元素的下标和。

### 最优关键思路或技巧
- 计算包含相等元素对 $[i, j]$ 的子段数量为 $i\times(n - j + 1)$，以此计算每个相等元素对的贡献。
- 使用 map 或离散化处理元素值，避免大值域带来的问题。
- 部分题解使用前缀和优化计算，降低时间复杂度。

### 可拓展之处
同类型题目可能会改变序列的定义或权重的计算方式，但核心思路仍然是计算每个元素对的贡献。类似算法套路包括计算子数组的相关问题，如子数组的和、子数组的最大值等，都可以通过计算每个元素的贡献来解决。

### 推荐洛谷题目
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
2. [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)

### 个人心得
- ZCETHAN 提到注意不要用 memset 全部更新，这题能卡掉（亲测），提醒我们在处理数据时要注意细节，避免不必要的时间开销。

---
处理用时：59.66秒