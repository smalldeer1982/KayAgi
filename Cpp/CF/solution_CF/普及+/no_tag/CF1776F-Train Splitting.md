# Train Splitting

## 题目描述

There are $ n $ big cities in Italy, and there are $ m $ train routes between pairs of cities. Each route connects two different cities bidirectionally. Moreover, using the trains one can reach every city starting from any other city.

Right now, all the routes are operated by the government-owned Italian Carriage Passenger Company, but the government wants to privatize the routes. The government does not want to give too much power to a single company, but it also does not want to make people buy a lot of different subscriptions. Also, it would like to give a fair chance to all companies. In order to formalize all these wishes, the following model was proposed.

There will be $ k \ge 2 $ private companies indexed by $ 1, \, 2, \, \dots, \, k $ . Each train route will be operated by exactly one of the $ k $ companies. Then:

- For any company, there should exist two cities such that it is impossible to reach one from the other using only routes operated by that company.
- On the other hand, for any two companies, it should be possible to reach every city from any other city using only routes operated by these two companies.

Find a plan satisfying all these criteria. It can be shown that a viable plan always exists. Please note that you can choose the number $ k $ and you do not have to minimize or maximize it.

## 说明/提示

In the first test case, the output is illustrated in the following picture, where different colors correspond to different companies (blue for $ 1 $ , red for $ 2 $ , green for $ 3 $ , and yellow for $ 4 $ ):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776F/1eaddc7b0f6d2a4f1f27940fa94f2aacb1f5a325.png)If we consider, for example, only companies $ 2 $ and $ 3 $ , we can see that from any city it is possible to reach every other city (picture on the left below). However, if we restrict to company $ 2 $ alone, it becomes impossible to reach city $ 5 $ from city $ 1 $ (picture on the right).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776F/31ecc8efdc21984e9ee7dfce5c89335fe0b0fc8e.png)In the second test case, the output is illustrated in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776F/168f9819a179018b8d7faca3d4c3b94ba0dba5d9.png)

## 样例 #1

### 输入

```
2
5 9
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
3 3
1 2
3 1
2 3```

### 输出

```
4
1 2 3 1 4 2 2 4 3
3
2 3 1```

# 题解

## 作者：rui_er (赞：3)

题意：有一个 $n$ 点 $m$ 边简单无向连通图，请用若干（至少为 $2$）种颜色对每条边染色，使得：

- 对于每种颜色，仅由该颜色的边组成的生成子图不连通。
- 对于每两种颜色，仅由该颜色的边组成的生成子图连通。

---

不难想到如下思路：

- 找出一个节点 $u$，将所有与 $u$ 相连的边分配颜色 $1$。
- 将其他边分配颜色 $2$。

此时，整张图只有两种颜色，因此第二个要求显然成立。同时，$u$ 必然不与其他点连通，颜色 $2$ 的第一个要求也成立。只需考虑颜色 $1$ 的第一个要求。

如果找到节点 $u$，使得 $d(u)<n$，此时至少一个节点不与 $u$ 连通，本题就做完了。

只有在原图是完全图的时候才找不到这样的节点 $u$，此时拿出一个颜色 $1$ 的边，将其改为颜色 $3$ 即可。显然这种构造符合要求。

```cpp
// Problem: F. Train Splitting
// Contest: Codeforces - SWERC 2022-2023 - Online Mirror (Unrated, ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/contest/1776/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;
const int N = 55;

int T, n, m, deg[N], ans[N*N];
vector<pair<int, int>> e[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	for(scanf("%d", &T); T; T--) {
		scanf("%d%d", &n, &m);
		rep(i, 1, m) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].emplace_back(v, i);
			e[v].emplace_back(u, i);
			++deg[u]; ++deg[v];
		}
		if(*min_element(deg+1, deg+1+n) < n - 1) {
			int u = min_element(deg+1, deg+1+n) - deg;
			puts("2");
			rep(i, 0, deg[u]-1) ans[e[u][i].second] = 1;
			rep(i, 1, m) if(!ans[i]) ans[i] = 2;
		}
		else {
			puts("3");
			ans[e[1][0].second] = 1;
			rep(i, 1, deg[1]-1) ans[e[1][i].second] = 2;
			rep(i, 1, m) if(!ans[i]) ans[i] = 3;
		}
		rep(i, 1, m) printf("%d%c", ans[i], " \n"[i==m]);
		rep(i, 1, n) e[i].clear();
		rep(i, 1, n) deg[i] = 0;
		rep(i, 1, m) ans[i] = 0;
	}
	return 0;
}
```

---

## 作者：DE_aemmprty (赞：2)

### 1 题目大意

有一个 $n$ 点 $m$ 边简单无向连通图，请用若干（至少为 $2$）种颜色对每条边染色，使得：

* 对于每种颜色，仅由该颜色的边组成的生成子图不连通。

* 对于每两种颜色，仅由该颜色的边组成的生成子图连通。

**注意：**

* $\sum{n} \leq 5000$

* $3 \leq n \leq 50$

* $n - 1 \leq m \leq \frac{n(n-1)}{2}$

### 2 解题分析

纯纯诈骗题。

显然，我们发现 $k$ 越大，答案越难构造。所以，我们考虑最简单的情况：$k = 2$。

当 $k = 2$ 时，不难想到让一种颜色构成的子图连接不上其中一个点。这样，我们就可以选择一个度数最小的点，把不与这个点相连的所有边染颜色 $1$，再把与这个点相连的边染颜色 $2$。

兴高采烈的写完代码后一测样例：WA 了！于是，我们发现又一种特殊情况：当我们选择的结点度数为 $n - 1$ 时，颜色 $2$ 构成的生成子图是连通的！所以我们可以任意选择一条颜色为 $2$ 的边，把它改成颜色 $3$ 即可。

于是，这道题就完成了。十分诈骗。

### 3 AC Code

细节很少，这里只放核心代码。

```cpp
void solve() {
    cin >> n >> m;
    f (i, 1, n)
        deg[i] = 0;
    f (i, 1, m) {
        scanf("%lld %lld", &u[i], &v[i]);
        deg[u[i]] ++;
        deg[v[i]] ++;
    }
    int mndeg = 2e18, col = -1;
    /*找点*/
    f (i, 1, n)
        if (mndeg > deg[i]) {
            mndeg = deg[i];
            col = i;
        }
    /*染色 1*/
    f (i, 1, m)
        if (u[i] != col && v[i] != col)
            c[i] = 1;
    /*染色 2*/
    f (i, 1, m)
        if (u[i] == col || v[i] == col)
            c[i] = 2; 
    /*特殊情况：完全图*/
    f (i, 1, m)
        if (n * (n - 1) / 2 == m && c[i] == 2) {
            c[i] = 3;
            break;
        }
    /*输出时也要注意特殊情况*/
    printf("%lld\n", 2ll + (n * (n - 1) / 2 == m));
    f (i, 1, m)
        printf("%lld ", c[i]);
    printf("\n");
}
```

---

## 作者：KυρωVixen (赞：0)

## CF1776F 题解
这题是与 Saint_ying_xtf 打 duel 的时候做到的，和 CSP 的题目比起来很有趣，并且不难想。

### 题面：
有一个 $n$ 点 $m$ 边简单无向连通图，请用若干（至少为 $2$）种颜色对每条边染色，使得：

- 对于每种颜色，仅由该颜色的边组成的生成子图不连通。
- 对于每两种颜色，仅由该颜色的边组成的生成子图连通。

### 解法：
考虑贪心。

对于一个点 $i$，显而易见的是只要 $deg_i<n-1$，也就是说包含点 $i$ 的生成子图不连通，那么我们将这个点所连的所有边染成颜色 $1$，随后将其他边染成颜色 $2$，就一定是合法的。贪心找第一个这样的 $i$ 即可。

有一个边界情况：原图是完全图。

这种情况下只需要把边 $(1,2)$ 染成颜色 $3$，然后再把和点 $1$ 相连的其他边染成颜色 $2$，剩下的染成颜色 $1$ 即可。简单模拟即可得知这样做是对的。

## 代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define fi first
#define sc second
#define endl '\n'
using namespace std;
int n,m;
int a[1255],d[55];
vector<pair<int,int>>e;
void exec(){
    e.clear();
    cin>>n>>m;
    memset(d,0,sizeof(d));
    rep(i,1,m){
        int u,v; cin>>u>>v;
        if(u>v) swap(u,v);
        d[u]++; d[v]++;
        e.push_back({u,v});
    }
    if(m==(n-1)*n/2){
        cout<<3<<endl;
        rep(i,0,m-1){
            if(e[i].fi==1){
                if(e[i].sc==2) a[i]=3;
                else a[i]=2;
            }
            else a[i]=1;
            cout<<a[i]<<" ";
        }
        cout<<endl;
        return;
    }
    cout<<2<<endl;
    rep(i,1,n){
        if(d[i]<n-1){
            rep(j,0,m-1){
                if(e[j].fi==i||e[j].sc==i) a[j]=1;
                else a[j]=2;
                cout<<a[j]<<" ";
            }
            cout<<endl;
            break;
         }
    }
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin>>t;
    while(t--) exec();
}
```

---

