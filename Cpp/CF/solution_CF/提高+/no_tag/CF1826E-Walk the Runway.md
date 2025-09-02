# Walk the Runway

## 题目描述

A fashion tour consists of $ m $ identical runway shows in different cities. There are $ n $ models willing to participate in the tour, numbered from $ 1 $ to $ n $ . People in different cities have different views on the fashion industry, so they rate each model differently. In particular, people in city $ i $ rate model $ j $ with rating $ r_{i, j} $ .

You are to choose some number of $ k $ models, and their order, let the chosen models have indices $ j_1, j_2, \dots, j_k $ in the chosen order. In each city, these $ k $ models will walk the runway one after another in this order. To make the show exciting, in each city, the ratings of models should be strictly increasing in the order of their performance. More formally, for any city $ i $ and index $ t $ ( $ 2 \leq t \leq k $ ), the ratings must satisfy $ r_{i,j_{t - 1}} < r_{i,j_t} $ .

After all, the fashion industry is all about money, so choosing model $ j $ to participate in the tour profits you $ p_j $ money. Compute the maximum total profit you can make by choosing the models and their order while satisfying all the requirements.

## 说明/提示

In the first example, there are $ 3 $ invited models. The show consists of models in the order $ [1, 3, 4] $ .

Then, the corresponding ratings in the cities are as follows:

- City $ 1 $ — $ [ 1, 3, 4 ] $ .
- City $ 2 $ — $ [ 1, 2, 3 ] $ .
- City $ 3 $ — $ [ 2, 4, 5 ] $ .

You can see that the ratings are increasing. So the total profit is $ 10 + 10 + 10 = 30 $ . It can be proven that we can't achieve a bigger profit.

In the second example, we can invite the fifth model to the tour, which would result in a total profit of $ 50 $ . It can be proven that we can't achieve a bigger profit.

In the third example, we invite the single model to the tour, which results in a total profit of $ 1\,000\,000\,000 $ .

In the fourth test case, we can invite all the models and make the show in the order $ [ 5, 4, 3, 2, 1 ] $ . The total profit is $ 5 \cdot 1\,000\,000\,000 = 5\,000\,000\,000 $ .

## 样例 #1

### 输入

```
3 5
10 10 10 10 10
1 2 3 4 5
1 5 2 3 4
2 3 4 5 1```

### 输出

```
30```

## 样例 #2

### 输入

```
3 5
10 10 10 10 50
1 2 3 4 5
1 5 2 3 4
2 3 4 5 1```

### 输出

```
50```

## 样例 #3

### 输入

```
1 1
1000000000
1```

### 输出

```
1000000000```

## 样例 #4

### 输入

```
5 5
1000000000 1000000000 1000000000 1000000000 1000000000
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1```

### 输出

```
5000000000```

## 样例 #5

### 输入

```
1 3
1 2 3
3 3 3```

### 输出

```
3```

# 题解

## 作者：zac2010 (赞：6)

题意：给定一个物品序列。每个物品有 $m$ 种属性和一个收益（第 $i$ 个物品的第 $j$ 种属性为 $r_{j,i}$）。你需要从原序列中取出几个物品（可以乱序取），并给这些取出的物品安排顺序，使得新的物品序列满足：对于任意 $i,j[i<j]$，都有 $i$ 的任意指标都比 $j$ 小。

$O(n^2m)$ 的朴素 $\text{DP}$ 比较简单，我们按照任意一个属性（指标）对序列进行排序。之后设 $f_i$ 为 $i$ 强制选时，$1\to i$ 这些物品能获得的最大价值。转移则是通过偏序关系转移——即 $j$ 能转移到 $i$ 当且仅当 $j<i$ 且 $\forall k,r_{j,k}<r_{i,k}$。

之后考虑优化转移时判断的过程。我们对 $j$ 能否转移到 $i$ 进行统一的预处理。具体的，我们对于每一个属性分别计算有哪些 $j$ 的当前属性比 $i$ 小，然后把多个属性的结果进行与运算，得到最终的结果。这一整个过程都可以用 $\text{bitset}$ 进行优化。

总时间复杂度为 $O(\frac{mn^2}{w}+nm\log n)$，$w$ 取 $32$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 5010, M = 510;
int m, n, c, r[N][M], id[N];
ll ans, f[N];
bitset<N> now, b[N];
int cmp(int i, int j){return r[i][c] < r[j][c];}
int main(){
	scanf("%d%d", &m, &n);
	FL(i, 1, n) id[i] = i, b[i].set();
	FL(j, 0, m) FL(i, 1, n) scanf("%d", &r[i][j]);
	FL(k, 1, m){
		now.reset(), now[0] = 1, c = k;
		sort(id + 1, id + n + 1, cmp);
		FL(i, 1, n){
			int j = i;
			while(j < n && r[id[j + 1]][k] == r[id[i]][k]) j++;
			FL(l, i, j) b[id[l]] &= now;
			FL(l, i, j) now[id[l]] = 1; i = j;
		}
	}
	sort(id + 1, id + n + 1, cmp);
	FL(i, 1, n) FL(j, 0, i - 1) if(b[id[i]][id[j]])
		f[i] = max(f[i], f[j] + r[id[i]][0]);
	FL(i, 1, n) ans = max(ans, f[i]); 
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Gao_l (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1826E)

很容易想到 $O(n^2m)$ 的 dp 做法。

$dp_i$ 表示最后一个选的是 $i$ 时的最大价值。

转移方程为：$dp_i=dp_j+p_i$（如果可以转移）。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
int p[N],r[N][N];
bool can[N][N];
int dp[N];
int cnt[N];//储存映射关系
int n,m;
bool cmp(int x,int y){
    return r[1][x]<r[1][y];
}
signed main(){
    cin >> m >> n;
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin >> r[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            can[i][j]=true;
            for(int k=1;k<=m;k++){
                if(r[k][i]<=r[k][j]){
                    can[i][j]=false;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        cnt[i]=i;
        dp[i]=p[i];//自己
    }
    sort(cnt+1,cnt+1+n,cmp);//将一维单调 可以证明 i 只能从 1~i-1转移
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(can[cnt[i]][cnt[j]]){//如果可以转移
                dp[cnt[i]]=max(dp[cnt[i]],dp[cnt[j]]+p[cnt[i]]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout << ans << "\n";
    return 0;
}
```
![](https://s21.ax1x.com/2024/12/07/pA78qhR.png)
但是很明显过不了。

考虑 bitset 优化，开 $n$ 个长度为 $n$ 的 bitset 数组 $b$。

$b_{i,j}=1$ 时表示可以从 $j$ 转移到 $i$。

然后，考虑每一维的预处理将逐位枚举变成 $\&$ 操作，此时时间复杂度从 $O(m)$ 降为 $O(\frac{m}{w})$（此时 $w=32$）。

这时，我们就可以用 $O(\frac{n^2m}{w})$（此时 $w=32$）的时间复杂度预处理出 $b$。

然后通过 dp 以 $O(nm\log_n)$ 的时间复杂度求出答案。

总时间复杂度：
$$O(\frac{n^2m}{w}+nm\log_2n)$$

AC code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
int n,m;
int p[N];
int a[N][N];
int cnt[N];
int nid;
bool cmp(int x,int y){
    return a[nid][x]<a[nid][y];
}
bitset<5005>b[N],now;
int dp[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> m >> n;
    for(int i=1;i<=n;i++){
        cin >> p[i];
        cnt[i]=i;
        b[i].set();//初始为全1
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
        }
    }
    for(int k=1;k<=m;k++){
        nid=k;
        now.reset();
        sort(cnt+1,cnt+1+n,cmp);//对第k维排序
        for(int i=1,j;i<=n;i++){
            j=i;
            while(j<n&&a[k][cnt[j]]==a[k][cnt[j+1]])j++;//特判相等的情况
            for(int l=i;l<=j;l++){
                b[cnt[l]]&=now;
            }
            for(int l=i;l<=j;l++){
                now[cnt[l]]=1;
            }
            i=j;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        dp[cnt[i]]=p[cnt[i]];
        ans=max(ans,dp[cnt[i]]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(b[cnt[i]][cnt[j]]){
                dp[cnt[i]]=max(dp[cnt[i]],dp[cnt[j]]+p[cnt[i]]);
                ans=max(ans,dp[cnt[i]]);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Ruan_ji (赞：3)

# CF1826E题解

## 思路
题面很清楚，我们注意到几个坑点：

1. $r_{i,j}$ 是竖着输入的，这个需要特别注意，翻译里没有说。

2. 如果已经有了一个集合 $S$，假如我们现在要加入元素 $x$，我们不可以钦定 $x$ 和 $S$ 中元素的偏序关系，也就是说，加进来的元素必须比集合 $S$ 内的所有元素要大（这里的大是指题目中描述的大于）。

接下来我们说一说思路。在此，我会尽量清除说明每一步干什么，不像其他题解那样云里雾里。

首先，我们先写暴力 dp。每个人的朴素 dp 都十分不同，虽然时间复杂度都是一样的，但是有的 dp 是优化不到满分的。

为了节省时间我就只说正确的 dp 了，可以对照自己的 dp 理解一下为什么这个更有前途。

我们先预处理出 $i$ 比哪些数字要大，然后我们直接最长上升子序列 dp 就行。

### 预处理
首先我们有一个 $k$ 表示枚举到了这 $m$ 维度中的第 $k$ 维。然后我们按这一维度下的 $r_{1\sim n,k}$ 排序。我们现在是不是获得了一个数组？然后我们枚举这个数组，$i$ 表示枚举到了第几个数字。现在你要想象每个数字有一个自己的 ```bitset[i]```，用来表示是否比一个数字大。具体来说如果```bitset[i][x]==1``` 表示 $i$ 比 $x$ 大（目前），为什么说是目前，因为我们现在只枚举到了前 $k$ 位，有可能在后面的位中不满足大于了，然后 ```bitset[i][x]``` 就会等于 $0$。那么具体怎么实现呢？排了序之后在 $i$ 之前的一定在这一位比 $i$ 小。我们新开一个临时 bitset，叫做 $A$。$A$ 的构造大概就是这样的 ```111100000000```。$1$ 就表示比 $i$ 小，然后我们直接 $A \And bit_i$ 即可，这样就完成了这一位的更新。

有一个细节需要注意，题目中的偏序关系是严格的小于，所以对于排序过后一堆连着的相同的要特殊处理，具体来说就是在这一段不要更新 $A$，然后到下种数字的时候再更新。

最后我们的时间复杂度是 $O(\frac{n^2m}{w})$。$\frac{1}{w}$ 的常数优化是 bitset 位运算给的。

## 实现
```cpp
#include <bits/stdc++.h>
#define N 5005
#define M 505
using namespace std;

//输入
int m,n;
int p[N];
int r[N][M]; 

//排序用
int wich; //当前正在枚举哪位，方便cmp使用
int vis[N]; //排序之后要知道i在原序列中是哪个

//统计答案用
long long ans, dp[N];

//预处理用
bitset<N> b[N]; //这是每个数字可以比哪些数字大

int cmp(int x, int y){
    return r[x][wich] < r[y][wich];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>m>>n;
    for(int i=1;i<=n;++i){
        cin>>p[i];
    }
    for(int i=1;i<=n;++i){
        vis[i]=i; //现在不理解，接着看
        b[i].set(); //初始化为1，很好理解
    }
    for(int j=1;j<=m;++j){
        for(int i=1;i<=n;++i){
            cin>>r[i][j]; //注意竖着输入
        }
    }
    //预处理
    for(int k=1;k<=m;++k){
        bitset<N> a;
        a.reset(); 
        a[0]=1;
        wich=k;
        sort(vis+1,vis+n+1,cmp);
        for(int i=1;i<=n;++i){
            int j=i;
            while(j<n && r[vis[j+1]][k] == r[vis[i]][k]) j++;//特判一堆一样的的情况

            for(int x=i;x<=j;++x) b[vis[x]] &= a; //特判一堆一样的的情况
            for(int x=i;x<=j;++x){//特判一堆一样的的情况
                a[vis[x]]=1;
            }
            i=j;
        }
    }

    //dp
    wich=1;
	sort(vis + 1, vis + n + 1, cmp); //必须保证一维偏序的满足才能dp
    for(int i=1;i<=n;++i){ //简单最长上升子序列
        for(int j=0;j<i;++j){
            if(b[vis[i]][vis[j]]){ //预处理的可不可以转移
                dp[i]=max(dp[i],dp[j]+p[vis[i]]);
            }
        }
    }
    for(int i=1;i<=n;++i){
        ans=max(ans,dp[i]);
    }
	cout<<ans<<'\n';
	return 0;
}
```

看的这么认真，用一个赞来结束这道题目的学习吧！

---

## 作者：541forever (赞：2)

初看此题，可以发现题目的限制是个类似 $n$ 维偏序，因为 $m$ 不大，不难想到预处理出他们两两之间是否存在偏序关系，然后形似记忆化搜索地做个 dp，但直接暴力预处理的复杂度是 $O(n^2m)$ 的，考虑用 `bitset` 维护两两之间是否存在偏序关系，我们可以每次选择一维进行排序，那么排完序后的每个数的前面的数不可能比该数优，每次用 `bitset` 进行一次 `&` 操作即可，`bitset` 的 `&` 的复杂度为 $m \over w$，因此总时间复杂度为 $O(nm log n+ {{n^2m} \over w})$，其中 $w$ 等于 $64$。

[Code](https://www.luogu.com.cn/paste/v61u3fo8)

---

## 作者：nullqtr_pwp (赞：1)

## Solution
对任意的 $t$ 和 $i$ 都有 $ r_{i,j_{t - 1}} < r_{i,j_t} $，这启示我们去找 $j_t,j_{t+1}$ 的关系。令一个有序的二元组 $(u,v)$ 合法当且仅当 $u$ 是 $j_1$ 时 $v$ 可以是 $j_2$。

现在考虑找出所有合法的 $(u,v)$ 后怎么做。我们可以考虑建图。

对于所有合法对，从 $u$ 到 $v$ 连一条有向边。这样一来，我们得到了一张有向无环图，原因是 $(u,v)$ 合法时，根据题目的限制，$(v,u)$ 一定不合法。

对于这张有向无环图，我们从某个点开始找一条链，记节点编号依次是 $p_1,p_2,\cdots,p_k$，其实就意味着我们选出了编号为 $p_1,p_2,\cdots,p_k$ 的模特。题目要求我们去找总和最大值，到这张有向无环图上就是去找**一条链，点权总和最大**，直接 dfs 即可。

dfs 复杂度最劣为 $O(n^2)$。

找出所有合法对，这是一个**高维偏序**板子。不会的可以自行搜索，使用 ```bitset``` 优化。暴力是 $O(n^2m)$，用 ```bitset``` 是 $O(\dfrac{n^2m}{w})$ 的。

总时间复杂度 $O(n^2+\dfrac{n^2m}{w})$。

## Code
```cpp
int p[509][5009],a[maxn],vis[maxn];
vi g[maxn];
int dfs(int u){
	if(vis[u]) return vis[u];
	int rt=a[u],tot=0;
	for(int v:g[u]) tot=max(tot,dfs(v));
	return vis[u]=rt+tot;
}
pii b[maxn];
int m,n,ans;
bitset<5010>c[5010];
void solve(){
	m=read(),n=read(),ans=0;
	F(i,1,n) a[i]=read(),c[i].set();
	F(i,1,m){
		F(j,1,n) b[j]={read(),j};
		sort(b+1,b+n+1);
        bitset<5010>cur;
		for(int j=1;j<=n;){
			int p=j;
			for(;p<=n&&b[p].fi==b[j].fi;) c[b[j++].se]&=cur;
			for(;p<j;) cur[b[p++].se]=1;
		}
	}
	F(i,1,n) F(j,1,n) if(i!=j&&c[i][j]==0&&c[j][i]==1) g[i].pb(j); 
	F(i,1,n) ans=max(ans,dfs(i));
	printf("%lld",ans);
}
```


---

## 作者：船酱魔王 (赞：0)

# Walk the Runway 题解

## 题意回顾

$ n $ 个带权有序 $ m $ 元组，求最长严格偏序链长度。

$ 1 \le m \le 500 $，$ 1 \le n \le 5000 $。

## 分析

暴力时间复杂度为 $ O(n^2m) $，不可过。

基于 cdq 分治或 KDT 等高维数点数据结构的传统算法复杂度飙升到 $ O(n \log^{m-1}n) $，感觉不如暴力。

考虑优化暴力 DP，如果我们能快速判断两个元组的偏序的话，$ O(n^2) $ DP 可过。

考虑每一元素的限制条件得到每个元组对于这个元素所有更小的元组集合，再取交集即可。

可以排序后在集合内依次加入元素，再分别取交集，注意正确处理同一维度上相等的值。可以用 `bitset` 维护集合，操作即为位赋值、与运算。

算法时间复杂度为 $ O(\frac{n^2m}{w}+nm \log n+n^2) $。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;
const int N = 5005;
int m, n;
bitset<5001> bt;
bitset<5001> bs[5001];
struct node {
	int id;
	int p;
} r[N];
int a[N][505];
int wd = 0;
bool operator<(node p1, node p2) {
	return a[p1.id][wd] < a[p2.id][wd];
}
long long dp[N];
vector<int> v; 
int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i++) scanf("%d", &r[i].p), r[i].id = i;
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) scanf("%d", &a[j][i]);
	}
	for(int i = 1; i <= n; i++) bs[i].set();
	for(int pi = 1; pi < m; pi++) {
		wd = pi;
		sort(r + 1, r + n + 1);
		bt.reset();
		for(int i = 1; i <= n; i++) {
			bs[r[i].id] &= bt;
			v.push_back(r[i].id);
			if(a[r[i].id][pi] < a[r[i + 1].id][pi]) {
				for(int j = 0; j < v.size(); j++) bt[v[j]] = 1;
				v.clear();
			}
		}
	}
	wd = m;
	sort(r + 1, r + n + 1);
	long long pts = 0;
	for(int i = 1; i <= n; i++) {
		dp[r[i].id] = r[i].p;
		for(int j = 1; j < i; j++) {
			if(bs[r[i].id][r[j].id] && a[r[i].id][m] > a[r[j].id][m]) dp[r[i].id] = max(dp[r[i].id], dp[r[j].id] + r[i].p);
		}
		pts = max(pts, dp[r[i].id]);
	}
	printf("%lld\n", pts);
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

高维偏序。直接套 $m-1$ 层 CDQ。复杂度 $O(n\log^{m-1}n)$ 解决。

很明显不行。

但是解决高维偏序还有一种常见的 trick：把每一维拆开，用二进制表示出偏序关系，最后全部按位与起来合并。

具体说，就是将每一维先按照 $r$ 值排序。陆续加入每个数，用一个 bitset 记录加入了哪些数。在所有 $r_j<r_i$ 的 $j$ 都加入后，当前 bitset 表示的就是这一维和 $i$ 满足对应偏序关系的集合了。

对每一维都如此处理。最后所有 bitset 与起来就是满足所有偏序关系的集合了。上面部分 $O(\frac{n^2m}{w})$ 解决。最后 $O(n^2)$ dp 即可。

code：

```cpp
int n,m,c[N],id[N];
pii e[N],f[N];
ll dp[N];
bitset<N> d[N];
void Yorushika(){
	scanf("%d%d",&m,&n);
	rep(i,1,n){
		scanf("%d",&c[i]);
		d[i].set();
	}
	rep(i,1,n){
		scanf("%d",&f[i].fi);
		f[i].se=i;
	}
	sort(f+1,f+n+1);
	rep(i,1,n){
		id[f[i].se]=i;
	}
	rep(j,1,m-1){
		rep(i,1,n){
			scanf("%d",&e[i].fi);
			e[i].se=id[i];
		}
		sort(e+1,e+n+1);
		int p=0;
		bitset<N> s;
		s.reset();
		rep(i,1,n){
			while(p<n&&e[p+1].fi<e[i].fi)
				s.set(e[++p].se);
			d[e[i].se]&=s;
		}
	}
	ll ans=0;
	rep(i,1,n){
		dp[i]=c[f[i].se];
		rep(j,1,i-1){
			if(d[i].test(j)&&f[i].fi>f[j].fi)
				dp[i]=max(dp[i],dp[j]+c[f[i].se]);
		}
		ans=max(ans,dp[i]);
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：LinkZelda (赞：0)

首先考虑一个暴力 dp，设 $dp_{i,j}$ 表示选了 $i$ 个 model，上一个选的编号为 $j$，那么枚举状态并转移是 $O(n^2m^2)$ 的。

我们从这个暴力中得到启发，能转移到某个 $j$ 的所有点 $x$ 必须满足的是所有城市中，$x$ 的 rating 都小于 $j$，也就是构成了偏序关系。如果我们以这些偏序关系建图，会得到一个 DAG，直接在这上面跑 dp 的话，时间复杂度就降为 $O(n^2)$。

那么剩下的问题是如何求出所有偏序关系。我们对每个城市的 rating 排序，从后往前扫一次并维护一下每个点能到哪些点，这样做是 $O(n^2m)$ 的，使用 bitset 优化这个维护的过程就能做到 $O\left(\dfrac{n^2m}{w}\right)$ 了。

[代码](https://codeforces.com/contest/1826/submission/204619145)。

---

## 作者：Unnamed114514 (赞：0)

**引理**：如果我们把可达关系带入图论，那么该图为 DAG。

证明：若存在边 $i\to j,j\to i$，那么则有 $r_{k,i}>r_{k,j},r_{k,j}>r_{k,i}$，显然不可能，于是原命题成立。

***

由于建图后显然可以拓扑（当然也可以记忆化搜索），定义 $f_u$ 表示到达 $u$ 的最大值，状态转移方程式显然：$f_u\gets\max\{f_v,p_u\}(v\to u)$。

那么问题就转化成了怎么快速建图。

***

首先容易想到我们可以 $O(n^2m)$ 暴力枚举 $(i,j)$ 建图，但是这样运算次数是 $1.25\times 10^{10}$，是会 TLE 的。

然后我们就可以想到，既然这个玩意是 $10^{10}$ 级别的，从某种意义上的套路来讲，我们可以考虑用一个 `bitset` 做到 $O(\dfrac{n^2m}{w})$。

然后我们想到如果我们对 $i\to j$ 拆成 $m$ 个状态，每个状态用 `bool` 表示，那么显然只有这 $m$ 个状态中 $r_{k,i}<r_{k,j}$ 均成立，那么 $i$ 才有边连向 $j$。那么就等价于这 $m$ 个状态进行与（`&`）运算。那么 $i$ 到 $j$ 有边的充要条件就是这个运算与起来结果为 $1$。

那么现在我们相当于要维护 $r_{k,i}<r_{k,j}$ ，于是就自然地想到对于每一个 $m$，将 $r$ 进行排序，那么我们现在只需要求出 $r$ 相等的区间 $[l,r]$，然后 $[l,r]$ 显然就是当前的状态，然后我们在在状态里把 $[l,r]$ 的状态更新即可。

---

