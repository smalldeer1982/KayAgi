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
这些题解的核心思路都是基于前缀和优化，并利用根号分治思想，根据\(n\)和\(k\)的大小关系选择不同策略。
 - **思路方面**：基本思路是先预处理前缀和，对于询问，一种是直接暴力遍历\(k\)个序列求区间和最大值，时间复杂度\(O(qk)\)；另一种是预处理所有区间的答案，实现\(O(1)\)查询，时间复杂度\(O(n^2k)\)。根据\(n\)和\(k\)的大小关系选择不同做法，因为\(n\times k\leq5\times10^5\)，当\(n\leq\sqrt{5\times10^5}\)时适合预处理，当\(k\leq\sqrt{5\times10^5}\)时适合暴力查询。
 - **算法要点**：都利用前缀和优化区间和的计算，将\(O(n)\)的区间和计算优化为\(O(1)\)。同时，根据数据范围\(n\times k\)的限制，通过分类讨论\(n\)和\(k\)的大小关系来选择更优的算法策略。
 - **解决难点**：难点在于如何优化时间复杂度以满足数据范围要求。通过分析数据范围特点，发现\(n\)和\(k\)相互制约关系，采用根号分治思想，结合两种暴力解法的优势，有效降低时间复杂度。

综合来看，各题解思路相近，质量主要体现在思路清晰度、代码可读性和优化程度上。

### 所选的题解
1. **作者：cyffff (5星)**
    - **关键亮点**：思路清晰，详细分析复杂度。通过分类讨论\(n\)和\(k\)大小关系，得出时间复杂度为\(O(s\sqrt{s}+q)\)或\(O(s + q\sqrt{s})\)（\(s = nk\)），并使用`map`记录询问答案，避免重复计算。
    - **重点代码**：
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
        int p=(i - 1)*n;
        for(int j=1;j<=n;j++)
            a[++p]=read();
        p=(i - 1)*n+1;
        pr[p]=a[p];
        for(int j=2;j<=n;j++)
            p++,pr[p]=pr[p - 1]+a[p];
    }
    while(q--){
        ll l=read(),r=read();
        if(ans.find(l*n+r)!=ans.end()) write(ans[l*n+r]),putc('\n');
        else{
            ll tmp=0;
            for(int i=1;i<=k;i++){
                int p=(i - 1)*n;
                if(l!=1) tmp=max(tmp,pr[p+r]-pr[p+l - 1]);
                else tmp=max(tmp,pr[p+r]);
            }
            write(ans[l*n+r]=tmp),putc('\n');
        }
    }
    flush();
}
```
    - **核心实现思想**：先预处理前缀和数组`pr`，对于每次询问，检查`map`中是否已有答案，有则直接输出；否则遍历\(k\)个序列求区间和最大值，并记录到`map`中。
2. **作者：Jerrlee✅ (4星)**
    - **关键亮点**：清晰阐述思路，提到对特殊情况\(l = 1\)的优化，代码实现较简洁。通过分析数据范围得出复杂度可能含根号，分类讨论并结合两种暴力解法。
    - **重点代码**：
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
            qzh[i][j]=qzh[i][j - 1]+a[i][j];//前缀和
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
                    ans[i][j]=max(ans[i][j],qzh[z][j]-qzh[z][i - 1]);//这是前文所说第二种方法的预处理
    }//O(n^2 k)
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x==1){cout<<jrl[y]-jrl[x - 1]<<endl;continue;}//O(n k) in total
        int cnt=LLONG_MIN;
        if(k>sqrt(500000)){
            cout<<ans[x][y]<<endl;
        }//O(1)
        else{
            for(int i=1;i<=k;i++) cnt=max(cnt,qzh[i][y]-qzh[i][x - 1]);
            cout<<cnt<<endl;
        }//O(q k)
    }
}
```
    - **核心实现思想**：先预处理前缀和数组`qzh`，对于特殊情况\(l = 1\)，提前计算并保存答案到`jrl`数组。根据\(k\)与\(\sqrt{5\times10^5}\)的大小关系，选择预处理所有区间答案或暴力查询。
3. **作者：Engulf (4星)**
    - **关键亮点**：简洁明了地阐述根号分治思路，代码逻辑清晰。根据\(k\)与\(\sqrt{5\times10^5}\)的大小关系，分别采用不同策略，代码实现简洁高效。
    - **重点代码**：
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
    - **核心实现思想**：预处理前缀和后，当\(k > \sqrt{5\times10^5}\)（约为707）时，预处理所有区间的最大值到`f`数组；当\(k \leq 707\)时，暴力遍历\(k\)个序列求区间和最大值。

### 最优关键思路或技巧
 - **根号分治思想**：根据数据范围\(n\times k\leq5\times10^5\)，分析出\(n\)和\(k\)的反比例关系，当\(n\)较小时预处理所有区间答案，当\(k\)较小时采用暴力查询，有效平衡时间复杂度。
 - **前缀和优化**：通过预处理前缀和，将区间和的计算复杂度从\(O(n)\)降低到\(O(1)\)，提高计算效率。
 - **记忆化**：部分题解使用`map`或数组记录已查询区间的答案，避免重复计算，进一步优化时间复杂度。

### 可拓展之处
同类型题或类似算法套路：此类题目通常给出多个序列及区间查询要求，关键在于利用数据范围特点，采用分治、前缀和、记忆化等优化手段。常见类似套路如根据不同条件选择不同预处理或查询策略，以平衡时间复杂度。

### 推荐题目
 - **P3379 【模板】最近公共祖先（LCA）**：考察树结构上的区间查询，可通过预处理和特定算法优化查询复杂度，与本题利用预处理优化查询思路类似。
 - **P1115 最大子段和**：涉及序列上的区间和问题，可通过动态规划或前缀和思想解决，与本题对区间和的处理有相似之处。
 - **P2824 [HEOI2016/TJOI2016]排序**：同样是根据数据范围选择合适算法策略，通过分析数据特点优化时间复杂度，类似本题根号分治思路。

### 个人心得摘录与总结
 - **作者Jerrlee✅**：提到比赛中做题情况，通过分析数据范围和复杂度，结合两种暴力解法通过本题。总结出做题时要善于观察数据范围特点，合理运用算法优化手段。 

---
处理用时：90.53秒