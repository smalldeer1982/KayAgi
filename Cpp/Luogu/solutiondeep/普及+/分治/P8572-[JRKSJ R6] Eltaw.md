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

• 综合分析与结论：
    - 所有题解都基于前缀和思想，通过预处理前缀和数组，快速计算区间和。针对数据范围 \(1\le n,k,q\le5\times 10^5\)，\(1\le n\times k\le 5\times10^5\)，采用了不同优化策略。
    - 多数题解利用 \(n\) 和 \(k\) 的制约关系，根据 \(n\) 与 \(\sqrt{nk}\) 或 \(k\) 与 \(\sqrt{nk}\) 的大小比较，选择不同复杂度的算法：
        - 当 \(n\leq\sqrt{nk}\) 时，预处理所有 \(O(n^2)\) 种区间的答案，时间复杂度 \(O(n^2k)\)，查询 \(O(1)\)。
        - 当 \(k\leq\sqrt{nk}\) 时，直接暴力查询，每次查询 \(O(k)\)，总时间复杂度 \(O(qk)\)。
    - 部分题解还使用 `map` 进行记忆化，避免重复计算已查询区间，降低时间复杂度。

• 所选的题解：
  - 作者：cyffff (5星)
    - 关键亮点：思路清晰，详细分析复杂度，根据 \(n\) 和 \(k\) 大小关系分类讨论，提出 \(O(s\sqrt s + q)\) 或 \(O(s + q\sqrt s)\) 时间复杂度解法，代码简洁明了。
    - 重点代码及核心思想：
```cpp
map<ll,ll>ans; 
//...
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
```
核心思想是利用 `map` 记忆化已查询区间，若未查询过则 \(O(k)\) 计算区间和最大值。

  - 作者：Jerrlee✅ (4星)
    - 关键亮点：分析数据范围，指出 \(O(q \times k)\) 询问复杂度不足，通过预处理优化，代码注释详细，对不同情况分类处理思路清晰。
    - 重点代码及核心思想：
```cpp
if(k>sqrt(500000)){
    memset(ans,0,sizeof ans);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            for(int z=1;z<=k;z++)
                ans[i][j]=max(ans[i][j],qzh[z][j]-qzh[z][i-1]);
}//O(n^2 k)预处理
while(q--){
    int x,y;
    cin>>x>>y;
    if(x==1){cout<<jrl[y]-jrl[x-1]<<endl;continue;}
    int cnt=LLONG_MIN;
    if(k>sqrt(500000)){
        cout<<ans[x][y]<<endl;
    }
    else{
        for(int i=1;i<=k;i++) cnt=max(cnt,qzh[i][y]-qzh[i][x-1]);
        cout<<cnt<<endl;
    }
}
```
根据 \(k\) 与 \(\sqrt{500000}\) 大小关系，\(k\) 大时预处理所有区间答案，\(k\) 小时暴力查询。

  - 作者：Engulf (4星)
    - 关键亮点：明确指出根号分治思想，根据 \(k\) 与 \(\sqrt{5 \cdot 10 ^ 5}\) 的大小关系，分别采用不同预处理和查询策略，代码简洁易懂。
    - 重点代码及核心思想：
```cpp
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
```
当 \(k > \sqrt{5 \cdot 10 ^ 5}\) 时预处理所有区间答案，\(k \leq \sqrt{5 \cdot 10 ^ 5}\) 时暴力查询。

• 最优关键思路或技巧：
    - **根号分治**：利用 \(n\) 和 \(k\) 的乘积上限，根据 \(n\) 或 \(k\) 与 \(\sqrt{nk}\) 的大小关系，选择不同复杂度算法，平衡预处理和查询时间。
    - **前缀和优化**：预处理前缀和数组，将区间和计算优化到 \(O(1)\)。
    - **记忆化**：使用 `map` 存储已查询区间答案，避免重复计算，降低时间复杂度。

• 可拓展之处：
    - 同类型题或类似算法套路：此类题目通常给出多个序列，进行区间查询，可拓展到二维或多维序列，以及更复杂的区间操作（如区间最值、区间异或等）。类似算法套路为利用数据范围关系，通过预处理、分治、记忆化等优化暴力解法。

• 推荐题目：
    - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：单序列求最大子段和，可拓展到多序列。
    - [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：二维区间操作，可类比本题前缀和优化思路。
    - [P2212 [USACO14MAR]Flowerpot S](https://www.luogu.com.cn/problem/P2212)：多序列区间最值问题，类似本题查询思路。

• 个人心得摘录：
    - 作者Jerrlee✅：这次比赛蛮不错的，赛时好好写了几题，310分跑路。总结：分享参赛体验，未涉及具体解题心得。 

---
处理用时：40.12秒