# 题目信息

# [JRKSJ R6] Eltaw

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/at23jtmh.png?x-oss-process=image)

你在月下独自行走，不禁想起了一道简单题。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

给你 $k$ 个长为 $n$ 的序列 $a_{1\dots k,1\dots n}$，有 $q$ 次询问，每次询问给出一个区间 $[l,r]$，要求出 $\displaystyle\max_{i=1}^k\sum_{j=l}^ra_{i,j}$，即求出所有序列中区间 $[l,r]$ 的和的最大值。

## 说明/提示

Idea：cyffff，Solution：cyffff，Code：cyffff，Data：cyffff

**Eltaw - Fl00t (Insane14.4)**

**本题输入输出文件较大，请使用恰当的输入输出方式。**
### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊限制 | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5\times10^3$ | $k\le 100$ | $20$ |
| $2$ | $5\times10^5$ | 保证 $l=1$ | $30$ |
| $3$ | $5\times10^5$ | 无 | $50$ |

对于 $100\%$ 的数据，$1\le n,k,q\le5\times 10^5$，$1\le n\times k\le 5\times10^5$，$1\le l\le r\le n$，$0\le a_{i,j}\le 10^9$。
### 数据更新记录
$\text{upd 2022.10.05}$：更新了两组数据，分别卡掉了两种时间复杂度错误的做法。感谢 @[二叉苹果树](https://www.luogu.com.cn/user/270854) 指出。


$\text{upd 2022.10.08}$：更新了一组数据，卡掉了记忆化不正确的做法。感谢 @[SweetOrangeOvO](https://www.luogu.com.cn/user/236862) 指出。

如果你能通过现在的所有测试点，说明你的代码复杂度极可能是正确的。如果你仍认为你的复杂度是错误的，请联系出题人。

## 样例 #1

### 输入

```
7 2 3
1 1 4 5 1 4 0
1 9 1 9 8 1 0
6 7
5 7
1 3```

### 输出

```
4
9
11```

# AI分析结果

### 综合分析与结论
这些题解大多围绕前缀和与根号分治的思想来解决问题。核心思路是先利用前缀和快速计算区间和，再根据数据范围 $n\times k\leq5\times10^5$ 进行分类讨论，当 $n$ 较小时预处理所有区间答案以实现 $O(1)$ 查询，当 $k$ 较小时每次询问直接遍历 $k$ 个序列计算最大值。部分题解还使用了记忆化的方法避免重复计算。

### 所选题解
- **作者：cyffff (赞：10)，4星**
    - **关键亮点**：思路清晰，对复杂度进行了详细分析，通过分类讨论 $n$ 和 $k$ 的大小关系，结合记忆化优化，给出了明确的复杂度结论。
- **作者：Engulf (赞：2)，4星**
    - **关键亮点**：简洁明了地阐述了根号分治的思想，根据 $k$ 与 $\sqrt{5\times10^5}$ 的大小关系进行分类处理，代码实现简洁。
- **作者：Jerrlee✅ (赞：3)，4星**
    - **关键亮点**：详细分析了复杂度，结合前缀和与分类讨论的思想，对特殊情况（$l = 1$）进行了优化，代码注释清晰。

### 重点代码及核心思想
#### cyffff 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+10;
int n,k,q,a[N];
ll pr[N];
map<ll,ll>ans; 
int main(){
    n=read(),k=read(),q=read();
    for(int i=1;i<=k;i++){
        int p=(i-1)*n;
        for(int j=1;j<=n;j++)
            a[++p]=read();
        p=(i-1)*n+1;
        pr[p]=a[p];
        for(int j=2;j<=n;j++)
            p++,pr[p]=pr[p-1]+a[p];
    }
    while(q--){
        ll l=read(),r=read();
        if(ans.find(l*n+r)!=ans.end()) write(ans[l*n+r]),putc('\n');
        else{
            ll tmp=0;
            for(int i=1;i<=k;i++){
                int p=(i-1)*n;
                if(l!=1) tmp=max(tmp,pr[p+r]-pr[p+l-1]);
                else tmp=max(tmp,pr[p+r]);
            }
            write(ans[l*n+r]=tmp),putc('\n');
        }
    }
    flush();
}
```
**核心思想**：先预处理每个序列的前缀和，对于每次询问，若之前询问过则直接输出答案，否则遍历 $k$ 个序列计算区间和的最大值并记录。

#### Engulf 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int M = 707;
int n, k, q;
int f[M][M];

signed main()
{
    cin.tie(nullptr) -> sync_with_stdio(false);
    cin >> n >> k >> q;
    vector<vector<int>> a(k + 1, vector<int>(n + 1));
    for (int i = 1; i <= k; i ++ )
        for (int j = 1; j <= n; j ++ )
            cin >> a[i][j], a[i][j] += a[i][j - 1];
    if (k > M)
    {
        for (int i = 1; i <= n; i ++ )
        {
            for (int j = i; j <= n; j ++ )
            {
                for (int id = 1; id <= k; id ++ )
                {
                    f[i][j] = max(f[i][j], a[id][j] - a[id][i - 1]);
                }
            }
        }
    }
    while (q -- )
    {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        if (k <= M)
        {
            for (int i = 1; i <= k; i ++ )
                ans = max(ans, a[i][r] - a[i][l - 1]);
            cout << ans << '\n';
        }
        else
        {
            cout << f[l][r] << '\n';
        }
    }
    return 0;
}
```
**核心思想**：先预处理每个序列的前缀和，根据 $k$ 与 $\sqrt{5\times10^5}$ 的大小关系分类处理。当 $k$ 较大时，预处理所有区间的最大值；当 $k$ 较小时，每次询问直接遍历 $k$ 个序列计算最大值。

#### Jerrlee✅ 的代码
```cpp
#define int long long//__int128
int jrl[500009];
signed main(){
    int n,k,q;
    cin>>n>>k>>q;
    int a[k+1][n+1];
    int qzh[k+9][n+9];
    int Jerrlee=sqrt(500000);
    int ans[Jerrlee+9][Jerrlee+9];//这边要注意，数组开大会 MLE
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            qzh[i][j]=qzh[i][j-1]+a[i][j];//前缀和
        }
    }
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            jrl[j]=max(jrl[j],qzh[i][j]);//这段是专为 sub2 写的，同时能有效缩短一内内时间，但是不加也能过
    if(k>sqrt(500000)){
        memset(ans,0,sizeof ans);
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                for(int z=1;z<=k;z++)
                    ans[i][j]=max(ans[i][j],qzh[z][j]-qzh[z][i-1]);//这是前文所说第二种方法的预处理
    }//O(n^2 k)
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x==1){cout<<jrl[y]-jrl[x-1]<<endl;continue;}//O(n k) in total
        int cnt=LLONG_MIN;
        if(k>sqrt(500000)){
            cout<<ans[x][y]<<endl;
        }//O(1)
        else{
            for(int i=1;i<=k;i++) cnt=max(cnt,qzh[i][y]-qzh[i][x-1]);
            cout<<cnt<<endl;
        }//O(q k)
    }
}
```
**核心思想**：先预处理每个序列的前缀和，对 $l = 1$ 的情况进行特殊处理，根据 $k$ 与 $\sqrt{5\times10^5}$ 的大小关系分类处理。当 $k$ 较大时，预处理所有区间的最大值；当 $k$ 较小时，每次询问直接遍历 $k$ 个序列计算最大值。

### 最优关键思路或技巧
- **前缀和**：利用前缀和可以在 $O(1)$ 时间内计算区间和，大大提高了计算效率。
- **根号分治**：根据 $n$ 和 $k$ 的大小关系进行分类讨论，选择合适的算法，降低了整体复杂度。
- **记忆化**：使用 `map` 等数据结构记录已经计算过的答案，避免重复计算。

### 拓展思路
同类型题或类似算法套路：
- 对于涉及区间查询的问题，前缀和是常用的预处理方法。
- 当数据范围存在制约关系时，根号分治是一种有效的优化策略。
- 记忆化可以应用于许多需要重复计算的场景，提高效率。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察前缀和与动态规划的结合。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：涉及前缀和与数学推导。
- [P3131 [USACO16JAN]Subsequences Summing to Sevens S](https://www.luogu.com.cn/problem/P3131)：需要利用前缀和与余数的性质。

### 个人心得摘录与总结
- **Jerrlee✅**：赛时好好写了几题，$310$ 分跑路。总结：认真对待比赛，积极解题能取得不错的成绩。
- **OoXiao_QioO**：认为这道题难度合适，作为备用题给了自己上大分的机会。总结：合适难度的题目能让不同水平的选手都有发挥的空间。 

---
处理用时：64.04秒