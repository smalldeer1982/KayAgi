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

• 综合分析与结论：这些题解都基于对题目数据范围 \(1\le n,k,q\le5\times 10^5\)，\(1\le n\times k\le 5\times10^5\) 的分析，发现 \(n\) 和 \(k\) 相互制约关系，进而采用不同策略解题。主要思路有两种暴力方法结合或利用记忆化优化暴力。一种暴力是 \(O(n^2k)\) 预处理所有区间答案，\(O(1)\) 查询；另一种是 \(O(qk)\) 每次询问时计算答案。根据 \(n\) 和 \(k\) 相对大小选择不同策略，本质是根号分治思想。

所选的题解：
  - **作者：cyffff (5星)**
    - **关键亮点**：思路清晰，详细分析复杂度，通过分类讨论 \(n\) 和 \(k\) 大小关系，得出整体复杂度为 \(O(s\sqrt s+q)\) 或 \(O(s+q\sqrt s)\)（\(s = nk\)），并利用 `map` 记忆化询问区间答案。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff

}
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
    - **核心思想**：先将 \(k\) 个长度为 \(n\) 的序列按一维存储并计算前缀和。每次询问时，若该区间答案已在 `map` 中记录则直接输出，否则遍历 \(k\) 个序列计算区间和取最大值并记录到 `map` 中。

  - **作者：Jerrlee✅ (4星)**
    - **关键亮点**：清晰阐述题意和思路，通过观察数据范围发现复杂度可能含根号，根据 \(k\) 与 \(\sqrt{5 \times 10^5}\) 的大小关系分类处理，分别给出不同预处理和查询方式。
    - **个人心得**：这次比赛不错，赛时写了几题拿了310分。
    - **核心代码**：
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
    - **核心思想**：先计算所有序列前缀和。当 \(k > \sqrt{5 \times 10^5}\) 时，预处理所有区间 \([l,r]\) 的最大值；当 \(k \leq \sqrt{5 \times 10^5}\) 时，每次询问遍历 \(k\) 个序列计算区间和取最大值。对于 \(l = 1\) 的特殊情况提前处理优化。

  - **作者：Engulf (4星)**
    - **关键亮点**：明确指出利用根号分治，根据 \(k\) 与 \(\sqrt{5 \cdot 10 ^ 5}\) 的大小关系，分别采用不同策略，代码简洁明了。
    - **个人心得**：无
    - **核心代码**：
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
    - **核心思想**：先计算所有序列前缀和。当 \(k > \sqrt{5 \cdot 10 ^ 5}\)（约为707）时，预处理所有区间 \([l,r]\) 的最大值；当 \(k \leq \sqrt{5 \cdot 10 ^ 5}\) 时，每次询问遍历 \(k\) 个序列计算区间和取最大值。

• 最优关键思路或技巧：利用根号分治思想，根据 \(n\) 和 \(k\) 的相对大小关系，选择不同的预处理和查询策略。当 \(n\) 较小时，预处理所有区间答案；当 \(k\) 较小时，每次询问暴力计算答案，同时可利用记忆化减少重复计算。

• 可拓展之处：同类型题通常会给出类似相互制约的数据范围，可采用根号分治，根据不同条件选择不同算法策略。类似算法套路如根据数据范围特点，将暴力算法在不同情况下进行组合优化。

• 推荐题目：
  - [P3959 宝藏](https://www.luogu.com.cn/problem/P3959)：涉及状态压缩与暴力搜索结合，类似本题根据数据范围选择合适算法策略。
  - [P2671 求和](https://www.luogu.com.cn/problem/P2671)：需要利用前缀和优化，同时结合数据范围进行复杂度分析，与本题前缀和及复杂度分析思路相似。
  - [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)：通过对数据范围分析，采用合适的暴力枚举策略解题，类似本题根据条件选择暴力方式。 

---
处理用时：56.80秒