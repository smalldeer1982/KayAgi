# 题目信息

# Dreamoon Likes Coloring

## 题目描述

Dreamoon likes coloring cells very much.

There is a row of $ n $ cells. Initially, all cells are empty (don't contain any color). Cells are numbered from $ 1 $ to $ n $ .

You are given an integer $ m $ and $ m $ integers $ l_1, l_2, \ldots, l_m $ ( $ 1 \le l_i \le n $ )

Dreamoon will perform $ m $ operations.

In $ i $ -th operation, Dreamoon will choose a number $ p_i $ from range $ [1, n-l_i+1] $ (inclusive) and will paint all cells from $ p_i $ to $ p_i+l_i-1 $ (inclusive) in $ i $ -th color. Note that cells may be colored more one than once, in this case, cell will have the color from the latest operation.

Dreamoon hopes that after these $ m $ operations, all colors will appear at least once and all cells will be colored. Please help Dreamoon to choose $ p_i $ in each operation to satisfy all constraints.

## 样例 #1

### 输入

```
5 3
3 2 2```

### 输出

```
2 4 1```

## 样例 #2

### 输入

```
10 1
1```

### 输出

```
-1```

# AI分析结果

### 题目翻译
Dreamoon非常喜欢给格子染色。

有一排 $n$ 个格子。最初，所有格子都是空的（不包含任何颜色）。格子从 $1$ 到 $n$ 编号。

给定一个整数 $m$ 和 $m$ 个整数 $l_1, l_2, \ldots, l_m$（$1 \le l_i \le n$）。

Dreamoon将执行 $m$ 次操作。

在第 $i$ 次操作中，Dreamoon将从范围 $[1, n - l_i + 1]$（包含端点）中选择一个数字 $p_i$，并将从 $p_i$ 到 $p_i + l_i - 1$（包含端点）的所有格子染成第 $i$ 种颜色。请注意，格子可能会被染色多次，在这种情况下，格子将显示最后一次操作的颜色。

Dreamoon希望在这 $m$ 次操作之后，所有颜色至少出现一次，并且所有格子都被染色。请帮助Dreamoon选择每次操作中的 $p_i$ 以满足所有约束条件。

### 算法分类
构造

### 综合分析与结论
这些题解大多先判断无解情况，主要有两种：一是所有 $l_i$ 之和小于 $n$；二是存在 $l_i + i - 1 > n$。对于有解情况，不同题解采用了不同的构造方法：
- 部分题解采用贪心策略，如让颜色尽可能靠右放置，再对左侧未染色部分进行调整。
- 部分题解通过记录后缀和，根据后缀和与 $n$ 的关系确定每个颜色的起始位置。
- 还有题解使用动态规划的思想，记录每个区间可能的覆盖位置，从结果往回推得到答案。

### 所选题解
- **奇米（4星）**
    - **关键亮点**：思路清晰，先明确无解情况，再通过记录后缀和，根据后缀和与 $n$ 的关系贪心确定每个颜色的起始位置，代码简洁易懂。
    - **个人心得**：考场 $FST$，现在发现一种更为简单的做法。
- **一扶苏一（4星）**
    - **关键亮点**：详细分析了构造过程，先让每种颜色尽可能靠右放置，再处理左侧未染色部分，逻辑严谨，时间复杂度为 $O(n)$。
    - **个人心得**：减号写成加号导致 $fst$。
- **蒟酱（4星）**
    - **关键亮点**：题解简短，直接贪心将第 $i$ 条线段的右端点放在 $n - i + 1$ 位置，再对左侧未染色部分进行处理，代码实现简洁。

### 重点代码
#### 奇米的代码
```cpp
const int N=1e5+5;
int n,m,a[N],b[N],sum[N],suf[N],ans;
signed main()
{
    n=read();
    m=read();
    int all=0;
    for ( int i=1;i<=m;i++ ) 
    {
        a[i]=read(); 
        all+=a[i];
        if(i+a[i]-1>n) 
            return printf("-1\n"),0;
    }
    for ( int i=n;i>=1;i-- ) 
        suf[i]=suf[i+1]+a[i];
    if(all<n) return printf("-1\n"),0;
    b[1]=1;
    for ( int i=2;i<=m;i++ )
    {
        if(i+suf[i]-1>=n) b[i]=i;
        else b[i]=n-suf[i]+1;
    }
    for ( int i=1;i<=m;i++ ) printf("%lld ",b[i]);
    return 0;
}
```
**核心实现思想**：先判断无解情况，然后计算后缀和，根据后缀和与 $n$ 的关系确定每个颜色的起始位置。

#### 一扶苏一的代码
```cpp
const int maxn = 100005;
int n, m;
int a[maxn], l[maxn], r[maxn], pl[maxn];
int main() {
    qr(n); qr(m);
    qra(a + 1, m);
    ll sum = 0;
    pl[0] = n;
    for (int i = 1; i <= m; ++i) {
        sum += a[i];
        r[i] = n - i + 1;
        l[i] = r[i] - a[i] + 1;
        if (l[i] <= 0) return puts("-1") & 0;
        pl[i] = std::min(l[i], pl[i - 1]);
    }
    if (sum < n) return puts("-1") & 0;
    if (pl[m] != 1) {
        sum = 0;
        for (int i = m; i; --i) {
            l[i] = sum + 1;
            sum += a[i];
            if (sum >= pl[i - 1]) {
                break;
            }
        }
    }
    qwa(l + 1, m, ' ', '\n');
    return 0;
}
```
**核心实现思想**：先判断无解情况，然后让每种颜色尽可能靠右放置，记录前 $i$ 个颜色左端点的最小值，若左侧有空余位置，从后往前用颜色铺满。

#### 蒟酱的代码
```cpp
constexpr int N=1e5+1,inf=0x3f3f3f3f;
int n,m,p1=1,p2=inf,l[N],p[N];
signed main(){
    std::ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;for(int i=1;i<=m;i++)cin>>l[i];
    if(std::accumulate(l+1,l+1+m,0ll)<n)return cout<<"-1",0;
    for(int i=1;i<=m;i++)if(cmin(p2,p[i]=n-i+2-l[i]),p2<=0)return cout<<"-1",0;
    for(int i=m;p1<=p2;i--)p[i]=p1,p1+=l[i];
    for(int i=1;i<=m;i++)cout<<p[i]<<' ';
    return 0;
}
```
**核心实现思想**：先判断无解情况，然后将第 $i$ 条线段的右端点放在 $n - i + 1$ 位置，若左端点小于 $1$ 则无解，最后处理左侧未染色部分。

### 最优关键思路或技巧
- 先判断无解情况，避免无效计算。
- 采用贪心策略，让颜色尽可能靠右放置，保证每种颜色至少出现一次，再对左侧未染色部分进行调整，使所有格子都被染色。
- 记录后缀和或前 $i$ 个颜色左端点的最小值，方便后续处理。

### 可拓展之处
同类型题或类似算法套路：其他构造类题目，如区间覆盖问题、排列构造问题等。解题时可先分析无解情况，再根据题目要求采用贪心、动态规划等策略进行构造。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心算法的经典应用，与本题的贪心思想有相似之处。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分答案与贪心结合的题目，可锻炼构造和贪心的思维。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分答案的题目，与本题的构造思路有一定的相似性。

### 个人心得总结
- 奇米：考场 $FST$，后续发现更简单的做法，提醒我们在考试时要仔细思考，考后要总结反思。
- 一扶苏一：减号写成加号导致 $fst$，强调了在编程时要注意细节，避免低级错误。

---
处理用时：56.89秒