# Facer爱游泳

## 题目背景

Facer 是一个爱游泳的孩子。

## 题目描述

一天他来到了一个 $n \times m$ 的游泳池中，其中第一行是水面，第 $n$ 行是游泳池底。

![](https://cdn.luogu.com.cn/upload/image_hosting/ggncnjpk.png)

Facer 想要从 $(1,1)$ 游到 $(1,m)$。他初始速度为 $0$ m/s。

Facer 可以按照以下方式游泳：假设当前 Facer 位于 $(x,y)$，速度为 $v$，那么它可以游到 $(x+v,y+1)$，如果 $x+v>n$，那么就会游到 $(n,y+1)$。

到了每一个格子，Facer 可以选择将自己的速度 $+1$，$-1$ 或者不变，也就是说每次 Facer 有三种选择：

- 游到 $(x+v-1,y+1)$，速度变为 $v-1$。
- 游到 $(x+v,y+1)$，速度变为 $v$。
- 游到 $(x+v+1,y+1)$，速度变为 $v+1$。

游泳池的每个格子上会放有以下两种物品中的一种：

- 变速器，每个变速器有一个属性 $w$，到了这个格子速度会变为 $v+w$（当然原来的 $+1$，$-1$，不变照样存在）。
- 金币盒，每个金币盒中有一定数量的钱 $a$，到了这个位置你可以得到 $a$ 个金币。

除此之外，有以下两点需要注意的：

1. 当 Facer 到达水面，即位于 $(1,x)$ 时，Facer的速度会变成 $0$（当然他仍然可以选择将速度 $+1$，$-1$ 或不变）。
2. Facer 不能在水下待太长时间，相邻两次到水面换气的时间不能超过 $k$ 秒。

求 Facer 能够得到最大金币的数量。

## 说明/提示

#### 数据规模与约定

- 对于 $10\%$ 的数据，$1 \leq n,m \leq 5$。
- 对于 $40\%$ 的数据，$1 \leq n,m \leq 100$。
- 对于 $100\%$ 的数据，$1 \leq n \leq 100$，$1 \leq m \leq 1000$，$1 \leq k \leq 10$，$-20 \leq w \leq 20$，$-1000 \leq a \leq 1000$。

## 样例 #1

### 输入

```
3 3 3
s1 v1 s1
s3 s19 v2
v3 s-1 v-1
```

### 输出

```
2```

## 样例 #2

### 输入

```
5 10 3
s81 s47 s3 s0 s82 s31 s89 v0 s97 v-1
s14 s94 v1 v-1 v1 s106 v1 v0 v-1 v0
s93 s105 v-1 s219 v0 v0 v-1 v1 s225 v1
v0 s160 v1 v1 s348 s120 s240 s392 s280 s172
s305 s455 s140 v-1 s455 v0 v-1 v0 v1 s410
```

### 输出

```
430```

# 题解

## 作者：baiABC (赞：3)

这题网上都是清一色的 dfs，但是其实直接 dp 也可以。

设 $f(j,i,v,x)$ 表示 $(i,j)$ 位置当前速度为 $v$，潜水时间为 $x$ 的最大答案（本格得到的钱不计），则容易递推更新后继状态，$f(m,1,0,0)$ 即为答案。

先解决空间问题。首先 $j$ 一维可以用滚动数组，然后由于 $k\leq 10$，所以 $-21\times 10\leq v\leq21\times 10$，可以开下。$v$ 可能是负数，给 $v$ 加上 $300$ 变成正数。

再考虑时间，可以限制下一个阶段枚举的 $v$ 的范围。时间复杂度 $O(mnk^2\cdot\max w)$，可以过。

DP 注意细节。
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[2][105][605][15], a[105][1005][2];
void upd(int &x, int y)
{
   x = max(x, y);
}
int main()
{
   ios::sync_with_stdio(0);
   int n, m, k; cin >> n >> m >> k;
   for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= m; ++j)
      {
         char c; cin >> c;
         a[i][j][0] = c=='v';
         cin >> a[i][j][1];
      }
   memset(***dp, 0x80, sizeof dp); // -INF
   dp[1][1][300][0] = 0; // 下面 v 都加了 300
   int lalv = 0, larv = 0, lv = 300, rv = -300;
   for(int i = 1; i < m; ++i)
   {
      int r = i & 1, tr = r^1;
      for(int j = 1; j <= n; ++j)
      {
         if(j == 1)
         {
            int ts = dp[r][1][300][0];
            if(ts == 0x80808080) continue;
            if(!a[1][i][0]) ts += a[1][i][1];
            lv = rv = 0;
            upd(dp[tr][1][300][0], ts);
            if(n > 1) upd(dp[tr][2][301][1], ts), rv = 1;
            continue;
         }
         for(int v = lalv; v <= larv; ++v)
         {
            int tv = v;
            if(a[j][i][0]) tv += a[j][i][1];
            for(int x = 1; x < k; ++x)
            {
               int ts = dp[r][j][v+300][x];
               if(ts == 0x80808080) continue;
               if(!a[j][i][0]) ts += a[j][i][1];
               int tj = j+tv;
               tj = min(tj, n);
               if(tj <= 2)
               {
                  lv = min(lv, 0);
                  rv = max(rv, 0);
                  upd(dp[tr][1][300][0], ts);
                  if(tj < 1) continue;
               }
               if(x == k-1) continue;
               if(tj > 1)
               {
                  lv = min(lv, tv); rv = max(rv, tv);
                  upd(dp[tr][tj][tv+300][x+1], ts);
               }
               if(tj > 2)
               {
                  lv = min(lv, tv-1); rv = max(rv, tv-1);
                  upd(dp[tr][min(n,j+tv-1)][tv-1+300][x+1], ts);
               }
               if(n > 1)
               {
                  lv = min(lv, tv+1); rv = max(rv, tv+1);
                  upd(dp[tr][min(n,tj+1)][tv+1+300][x+1], ts);
               }
            }
         }
      }
      lalv = lv; larv = rv;
      lv = 300; rv = -300;
      memset(dp[r][0][0], 0x80, sizeof dp[r]);
      // 滚动数组要清空！
   }
   cout << dp[m&1][1][300][0]+(a[1][m][0]?0:a[1][m][1]) << '\n';
   return 0;
}
```

---

