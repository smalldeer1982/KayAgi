# Lucky Country

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

## 样例 #1

### 输入

```
4 3
1 2
2 3
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 4
1 2
3 4
4 5
3 5
```

### 输出

```
-1
```

# 题解

## 作者：zac2010 (赞：7)

## 做法
首先，不难将题目转化为：给定一些物品（连通块），物品有体积（连通块大小），对于每个 $x$，求最少几件物品能恰好装满一个容积为 $x$ 背包。

体积相同的物品我们视其为同一种。所以这是一个多重背包问题。利用二进制分解可以做到 $O(n\sqrt n)$。

## 时间复杂度证明

假设第 $i$ 种物品选了 $c_i$ 次。时间复杂度 $O(n(\sum_{i=1}^{n}\log_{c_i}))$。

有：一种方案中，最多只有 $\sqrt n$ 个 $i$ 满足 $c_i=0$（可以分 $i\leq\sqrt n$ 与 $i>\sqrt n$ 分类讨论）。

考虑最坏情况，此时的时间复杂度为 $O(n(\sum_{i=1}^{\sqrt n}\log_{c_i}))$；同时满足 $\sum_{i=1}^{\sqrt n} i\times c_i=n$，且它和 $\sum_{i=1}^{\sqrt n}2^{\lfloor \log i \rfloor} c_i$ 是同个级别的。

所以现在就是要贪心地构造 $c$ 数组，使得复杂度花销最大。假设是 $n$ 为 $1$，必定是优先让 $c_1=1$。接着是第二次，我们会发现当前的最优方案有两个：把 $c_1$ 加上 $2$ 以及把 $2^1=2$ 个满足 $\lfloor \log i \rfloor=1$ 的点各自加上 $1$。假若这两种都选了，那么有 $c_1=2,c_2=1,c_3=1$。之后第 $3$ 次的最优方案中 $c_1$ 需要加上 $4$，所有 $\lfloor \log i \rfloor=1$ 的点都要加上 $2$，所有 $\lfloor \log i \rfloor=2$ 的点要加上 $1$……总之，决策次数增加就意味着上一层中 $\lfloor \log i \rfloor=j$ 的所有点在当前需要加上的数翻了倍（这样才能使得 $\log c_i$ 增加）。这样的过程不超过 $\sqrt n$ 次。

归纳一下，$c$ 数组在最坏情况下：$c_i=\frac{\sqrt n}{2^{\lfloor \log i\rfloor}}$。时间复杂度是 $O(n(\sum_{i=1}^{\log\sqrt n} 2^{i - 1}\times((\log {\sqrt n}) - i+1)))$，$n$ 后面（括号里）的部分展开一下就是 $1\times(\log\sqrt n-0)+2\times(\log\sqrt n-1)+4\times (\log\sqrt n - 2)+\cdots+\sqrt n\times (\log\sqrt n-\log\sqrt n+1)$。再拆系数，$(\log\sqrt n)+(\log\sqrt n-1)+(\log\sqrt n - 1)+\cdots+(\log\sqrt n-\log\sqrt n+1)+(\log\sqrt n-\log\sqrt n+1)+\cdots+(\log\sqrt n-\sqrt n+1)$。不妨把它写成一个三角形的形式（每一列的数相同）：
$$
 \begin{matrix}
   \sqrt n & \frac{\sqrt n}{2} & \cdots & 2 & 1\\
    & \frac{\sqrt n}{2} & \cdots & 2 & 1 \\
    &  & \cdots & 2 & 1 \\
    &  & \cdots & \vdots & \vdots \\
   	&  &  & 2 & 1 \\
   	&  &  &  & 1
  \end{matrix} 
$$

其中，第一行的总和约为 $2\sqrt n$，第二行的约为 $\sqrt n$，第三行的 $\frac{\sqrt n}{2}$……最后一行为 $1$。等比数列求和即可，会发现总和约是 $4\sqrt n$。

综上所述，最大的花销也是 $n\sqrt n$ 级别的。故而本题的时间复杂度为 $O(n\sqrt n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m, ans = INF, fa[N], cnt[N], c[N], dp[N];
int find(int x){return fa[x] == x? x : fa[x] = find(fa[x]);}
void Union(int x, int y){fa[find(x)] = find(y);}
int check(int x){
    while(x){
        if(x % 10 != 4 && x % 10 != 7) return 0;
        x /= 10;
    }
    return 1;
}
int main(){
    scanf("%d%d", &n, &m);
    FL(i, 1, n) fa[i] = i;
    FL(i, 1, m){
        int u, v; scanf("%d%d", &u, &v);
        Union(u, v);
    }
    FL(i, 1, n) cnt[find(i)]++;
    FL(i, 1, n) if(cnt[i]) c[cnt[i]]++;
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    FL(i, 1, n){
        int s = c[i], p = 1, t;
        while(s > 0){
            t = min(s, p), s -= p, p *= 2;
            FR(j, n - t * i, 0)
                dp[j + t * i] = min(dp[j + t * i], dp[j] + t);
        }
    }
    FL(i, 1, n) if(check(i)) ans = min(ans, dp[i]);
    printf("%d\n", ans < INF? ans - 1 : -1);
    return 0;
}
```


---

## 作者：Link_Cut_Y (赞：3)

## 题意

给定若干个物品，每个物品有重量，物品的重量和为 $n$。求 $[1, n]$ 中每个重量需要几个物品拼起来。

## 分析

 - 最多有 $O(\sqrt{n})$ 种不同的重量。因为 $1 + 2 + \cdots + k \ge n$ 时 $k$ 是 $O(\sqrt n)$ 级别的。
 
 - 因此可以把物品重量相同的归为一类，然后跑多重背包。多重背包常见的优化（比如二进制优化和单调队列优化）就不赘述了。
 
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

using PII = pair<int, int>;
const int N = 100010, M = N << 1;
const int INF = 0x3f3f3f3f;
int f[N], ans = INF;
PII vec[10000000];
int h[N], e[M], ne[M], idx;
int n, m, sz[N], cnt, bin[N];
vector<PII> bags;
bool vis[N];

void add(int a, int b) {
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}
void dfs(int u, int &cnt) {
	vis[u] = true; cnt ++ ;
	for (int i = h[u]; i; i = ne[i]) {
		int v = e[i];
		if (vis[v]) continue;
		dfs(v, cnt);
	}
}
void get(int now) {
	if (now > n) return;
	if (now != 0) ans = min(ans, f[now]);
	get(now * 10 + 4);
	get(now * 10 + 7);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++ ) {
		int a, b; scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	for (int i = 1; i <= n; i ++ )
		if (!vis[i]) dfs(i, sz[ ++ cnt]);
	for (int i = 1; i <= cnt; i ++ )
		bin[sz[i]] ++ ; cnt = 0;
	for (int i = 1; i <= n; i ++ )
		if (bin[i]) vec[ ++ cnt] = {i, bin[i]};
	bags.push_back({0, 0});
	for (int i = 1; i <= cnt; i ++ ) {
		int val = vec[i].first, t = vec[i].second;
		int tmp = 1;
		while (tmp <= t) bags.push_back({val, tmp}), t -= tmp, tmp <<= 1;
		if (t) bags.push_back({val, t});
	}
	memset(f, 0x3f, sizeof f); f[0] = 0;
	for (int i = 1; i < bags.size(); i ++ ) {
		int val = bags[i].first, t = bags[i].second;
		for (int j = n; j >= val * t; j -- ) {
			f[j] = min(f[j], f[j - val * t] + t);
		}
	} get(0);
	printf("%d\n", ans == INF ? -1 : ans - 1);
	return 0;
}
```

---

## 作者：minxu (赞：1)

[题目](https://www.luogu.com.cn/problem/CF95E)

将所有联通块找出来后 就是一个多重背包裸题了

这里提供一种单调队列的做法 

注意要初始化每次的队首为极大值 因为要求最小 然后就是枚举%$sz[i]$的余数 枚举个数 先把当前值压入队列 再从队列找最大值更新 

因为不同物品的个数只有$\sqrt{n}$个 

所以复杂度就是$O(n*\sqrt{n})$

不知道为什么竟然没有跑过二进制拆分 


```
#include <bits/stdc++.h>

using namespace std;
template <typename T>
inline void read(T &x)
{
    x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    if (f == -1)
        x = -x;
}
int n, m, tot;
const int N = 1e5 + 55;
int f[N];
int fa[N];
int stk[N], h, t = 1;
int sz[N], v[N], w[N], sum[N];
int g[N];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
inline bool check(int x)
{
    while (x)
    {
        if (x % 10 != 4 && x % 10 != 7)
            return false;
        x /= 10;
    }
    return true;
}
int vis[N];
int main()
{
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
        fa[i] = i, sz[i] = 1;
    for (int i = 1, x, y; i <= m; ++i)
    {
        read(x), read(y);
        int fx = find(x), fy = find(y);
        if (fx == fy)
            continue;
        if (sz[x] < sz[y])
            swap(x, y);
        sz[fx] += sz[fy];
        fa[fy] = fx;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (fa[i] == i)
        {
            if (!vis[sz[i]])
            {
                w[++tot] = sz[i];
                vis[sz[i]] = 1;
            }
            sum[sz[i]]++;
        }
    }
    memset(f, 0x3f3f3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= tot; ++i)
    {
        for (int r = 0; r < w[i]; ++r)//枚举余数
        {
            h = 0, t = 1;
            g[1] = 1 << 30;//初始化
            for (int k = 0; k * w[i] + r <= n; ++k)//枚举选几个
            {
                int tmp = f[k * w[i] + r] - k;//先压入$i-1$时的值
                while (h < t && k - stk[h + 1] > sum[w[i]])
                    h++;
                f[k * w[i] + r] = min(f[k * w[i] + r], g[h + 1] + k);
                while (h < t && g[t] >= tmp)
                    t--;
                stk[++t] = k;
                g[t] = tmp;
            }
        }
    }
    int ans = 1 << 30;
    for (int i = 1; i <= n; ++i)
        if (check(i) && f[i] <= n)
            ans = min(ans, f[i]);
    if (ans > n)
        cout << -1;
    else
        cout << ans - 1;
    return 0;
}
```



---

## 作者：NBest (赞：1)

# 思路
第一眼看以为是个图论，结果发现缩点之后就是个多重背包裸题。

我们把原连通块变成一个重量为连通块大小的物体，然后发现只需要找在容量为幸运数的情况下，放满容量所选物体数量的最小值。

考虑背包，但是复杂度为 $O(n^2)$，观察到这题有根号性质，也就是把重量相同的物体缩在一起后总数量不会超过 $\sqrt n$，然后做一个二进制优化对多重背包即可，总复杂度 $O(n\sqrt n \log n)$。

## $Code$
```cpp
unordered_map<int,int>M;
int n,m,fa[100005],siz[100005],w[100005],v[100005],tot,f[100005];
bool  pd[100005];
inline int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    int xx=find(x),yy=find(y);
    if(xx==yy)return;
    if(siz[xx]>siz[yy])xx^=yy^=xx^=yy;
    siz[yy]+=siz[xx],siz[xx]=0;
    fa[xx]=yy;
}
bool is(int x){
    while(x){
        if(x%10!=4&&x%10!=7)return 0;
        x/=10;
    }
    return 1;
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        merge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(pd[find(i)])continue;
        pd[fa[i]]=1;
        M[siz[fa[i]]]++;
    }
    for(auto PI:M){
        int W=PI.first,S=PI.second;
        for(int k=__lg(S)-1;S&&~k;--k){
            if(S>=(1<<k))w[++tot]=W*(1<<k),v[tot]=(1<<k),S-=(1<<k);
        }
        if(S)w[++tot]=W*S,v[tot]=S;
    }
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=tot;i++){
        for(int j=n;j>=w[i];--j){
            f[j]=min(f[j],f[j-w[i]]+v[i]);
        }
    }
    int ans=1e9;
    for(int i=4;i<=n;i++){
        if(is(i)){
            ans=min(ans,f[i]-1);
        }
    }
    if(ans>n)ans=-1;
    cout<<ans;
}
```
## 后话
所以为什么这题评紫，多重背包是绿题唉。一开始看到这题是紫都不敢用背包，看见背包才敢想背包正解。

---

## 作者：yeshubo_qwq (赞：1)

## Solution

紫题？

首先用并查集维护岛屿之间的连通关系。

然后将问题转化为有若干个联通块，选择其中一部分，使它们的和是幸运数。


转化后的问题就是多重背包的模版，记得加上优化（我同学没加优化疯狂 T）。

只需要二进制分组即可，还用不上单调队列。

注意答案是最少联通块数量减一，记得判无解。

## Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1e5+5;
int f[N],g[N],a[N],k,dp[N],x,y,n,m,i,j,sum;
void init(int n){
	for (int i=1;i<=n;i++) f[i]=i,g[i]=1;
}
int find(int x){
	return f[x]=(f[x]==x?x:find(f[x]));
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if (x!=y) g[x]+=g[y],f[y]=f[x];
}
bool lucky(int x){
	while (x!=0){
		if (x%10!=4 && x%10!=7) return false;
		x/=10;
	}
	return true;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	init(n);
	for (i=1;i<=m;i++) cin>>x>>y,merge(x,y);
	for (i=1;i<=n;i++)
		if (find(i)==i) a[g[i]]++;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for (i=1;i<=n;i++){
		if (a[i]==0) continue;
		sum=0;
		for (k=1;sum+k<=a[i];sum+=k,k<<=1){
			for (j=n;j>=0;j--)
				if (j-i*k>=0)
					dp[j]=min(dp[j],dp[j-i*k]+k);
				else
					break;
		}
		k=a[i]-sum;
		if (k==0) continue;
		for (j=n;j>=0;j--)
			if (j-i*k>=0)
				dp[j]=min(dp[j],dp[j-i*k]+k);
			else
				break;
	}
	int ans=dp[n+1];
	for (i=1;i<=n;i++)
		if (lucky(i))
			ans=min(ans,dp[i]);
	return cout<<(ans==dp[n+1]?-1:ans-1),0;
}
```


---

## 作者：intel_core (赞：1)

简要题意：有一张无向图，你需要加一些边使得图上出现一个大小为幸运数的连通块；一个数是幸运数当且仅当这个数的所有数码都是 `4` 或 `7`。

先用并查集跑出所有连通块的大小。

转化为若干个数，选一些让它们的和是幸运数。

直接背包做的话，复杂度 $O(n^3)$ ，需要优化。

观察到所有连通块大小最多只有 $O(\sqrt{n})$ 种，所以我们可以把大小相同的连通块一起考虑。

这样缩起来之后复杂度可以降到 $O(n^2)$。

这是一个很明显的完全背包模型，使用二进制优化解决。

复杂度不会分析，大概 $O(n \sqrt{n})$ 吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
int n,m,cnt[NR],fa[NR],size[NR];
int f[NR],tot,w[NR],v[NR];

void init(){
	for(int i=1;i<=n;i++)fa[i]=i,size[i]=1; 
}
int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	fa[x]=y;size[y]+=size[x];
}
bool check(int x){
	if(!x)return 1;
	if(x%10==4||x%10==7)return check(x/10);
	return 0;
}

int main(){
	cin>>n>>m;init(); 
	for(int i=1,x,y;i<=m;i++)
		scanf("%d%d",&x,&y),merge(x,y);
	for(int i=1;i<=n;i++)
		if(get(i)==i)cnt[size[i]]++;
	for(int i=1;i<=n;i++){
		int now=1;
		while(cnt[i]>0){
			w[++tot]=min(cnt[i],now)*i;v[tot]=min(cnt[i],now);
			cnt[i]-=now;now<<=1;
		}
	}
	memset(f,999999,sizeof(f));f[0]=0;
	for(int i=1;i<=tot;i++)
		for(int j=n-w[i];j>=0;j--)f[j+w[i]]=min(f[j+w[i]],f[j]+v[i]);
	int ans=1e9;
	for(int i=1;i<=n;i++)
		if(check(i))ans=min(ans,f[i]);
	if(ans<1e9)cout<<ans-1<<endl;
	else puts("-1");
	return 0;
}








```

---

## 作者：xixike (赞：1)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15738312.html)

## Desciption

[CF95E Lucky Country](https://www.luogu.com.cn/problem/CF95E)

## Solution

非常巧妙的 $dp$ 题，sto xy学长 orz

同一个区域的岛屿明显只能在一起，所以用并查集合并一下同一区域内的岛屿。

然后我们要找出用最少的边连出一个幸运地区。

那这不就是一个背包吗！

朴素的状态：$dp_{i, j}$ 表示考虑到前 $i$ 个区域，一共有 $j$ 个岛屿的最小连边数。

朴素的转移方程：
$$
dp_{i, j} = \min\{dp_{i - 1, j - a_i} + 1\}
$$

> $a_i$：表示区域 $i$ 中的岛屿个数。

显然会 T，考虑优化。

经典的**二进制拆分**就登场了，所以我们二进制拆一下跑个 01背包 即可。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 1e5 + 10;
int n, m, tot, cnt;
int f[N], siz[N];
int a[N], dp[N], w[N], v[N];

inline int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
}

inline void prework(){
    for(int i = 1; i <= n; ++i){
        if(!a[i]) continue;
        int tmp = 1;
        while(a[i]){
            w[++cnt] = i * tmp, v[cnt] = tmp;
            a[i] -= tmp, tmp <<= 1;
            if(a[i] < tmp && a[i]){
                w[++cnt] = i * a[i], v[cnt] = a[i];
                break;
            }
        }
    }
}

inline bool check(int x){
    while(x){
        if(x % 10 != 4 && x % 10 != 7) return 0;
        x /= 10;
    }
    return 1;
}

int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) f[i] = i, siz[i] = 1;
    for(int i = 1; i <= m; ++i){
        int fu = find(read()), fv = find(read());
        if(fu != fv){
            if(siz[fu] < siz[fv]) swap(fu, fv);
            f[fu] = fv, siz[fv] += siz[fu];
        }
    }
    for(int i = 1; i <= n; ++i)
        if(find(i) == i) a[siz[i]]++;
    memset(f, 0x3f, sizeof(f));
    prework();
    f[0] = 0;
    for(int i = 1; i <= cnt; ++i)
        for(int j = n; j >= w[i]; --j)
            f[j] = min(f[j], f[j - w[i]] + v[i]);
    int ans = 1e9;
    for(int i = 1; i <= n; ++i)
        if(check(i)) ans = min(ans, f[i]);
    write(ans > n ? -1 : ans - 1);
    puts("");
    return 0;
}
```

$$
\_EOF\_
$$



---

## 作者：45dino (赞：1)

一开始先用并查集处理出每个联通块的大小，发现每连一条边就是将两个联通合并在一起。

令 $f(i)$ 表示大小为 $i$ 的联通块最少需要 $f(i)$ 个初始联通块合并得到，则答案可以表示为 $\min \{f(x)\}$ ，其中 $x$ 是 $[1,n]$ 的 lucky number。

用多重背包计算即可。

时间复杂度：$\Theta(n\times \sqrt{n}\times \log_2 {n})$

参考代码
```cpp
#pragma GCC optimize("Ofast") 
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
int n,m,fa[100001],size[100001],cnt[100001],dp[100001];
int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
bool isl(int x)
{
	for(;x;x/=10)
		if(x%10!=4&&x%10!=7)
			return 0;
	return 1;
}
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		fa[i]=i;
	while(m--)
	{
		int x=read(),y=read();
		fa[find(x)]=find(y);	
	}	
	for(int i=1;i<=n;i++)
		size[find(i)]++;
	for(int i=1;i<=n;i++)
		cnt[size[i]]++;
	for(int i=1;i<=n;i++)
		dp[i]=114514114514114514;
	for(int i=1;i<=n;i++)
		if(cnt[i])
		{
			int num=cnt[i];
			for(int p=1;num;p<<=1)
			{
				p=min(p,num);
				num-=p;
				int w=p*i;
				for(int l=n-w;l>=0;l--)
					dp[l+w]=min(dp[l+w],dp[l]+p);
			}
		}
	int ans=114514114514114514;
	for(int i=1;i<=n;i++)
		if(isl(i))
			ans=min(ans,dp[i]);
	if(ans==114514114514114514)
		ans=-1;
	else
		ans--;
	cout<<ans;
	return 0;
}
```


~~搞不懂为啥是紫题\yun~~

---

## 作者：Cylete (赞：1)

首先我们并查集跑出每个块的大小size

题目就转化成给你一堆数，最少合并几次使这些数字只有4和7

就是一个经典的背包问题

注意要用二进制优化即可

```cpp
#define R register

#define size dede//CF size 是关键字

const int N = 1e5 + 10;

int n, m, ans = 1234567890;
int f[N], size[N], a[N];
int w[N], v[N], tot;

inline int getf(int x)
{
	return f[x] == x ? x : f[x] = getf(f[x]);
}

inline bool check(int x)
{
	while(x)
	{
		if(x % 10 != 4 && x % 10 != 7) return false;
		x /= 10;
	}
	return true;
}

signed main()
{
	into();
	read(n); read(m);
    //初始化并查集
	for(R int i = 1; i <= n; i++) f[i] = i, size[i] = 1;
	for(R int i = 1, x, y; i <= m; i++)
	{
		read(x); read(y);
		int t1 = getf(x), t2 = getf(y);
		if(t1 != t2)
		{
			if(size[t1] < size[t2]) swap(t1, t2);//感觉是多余的，只是合并惯了小并到大
			f[t2] = t1;
			size[t1] += size[t2];
		}
	}
	for(R int i = 1; i <= n; i++)
		if(getf(i) == i)
			a[size[i]]++;
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
    //二进制优化
	for(R int i = 1; i <= n; i++)
	{
		int sum = 1, now = 1;
		if(!a[i]) continue;
		w[++tot] = i; v[tot] = 1;
		while(sum < a[i])
		{
			now <<= 1;
			sum += now;
			if(sum > a[i])
			{
				sum -= now;
				w[++tot] = i * (a[i] - sum);
				v[tot] = a[i] - sum;
				break;
			}
			w[++tot] = i * now;
			v[tot] = now;
		}
	}
	for(R int i = 1; i <= tot; i++)
		for(R int j = n; j >= 0; j--)
			if(j - w[i] >= 0)
				f[j] = min(f[j], f[j - w[i]] + v[i]);
	for(R int i = 1; i <= n; i++) if(check(i)) ans = min(ans, f[i]);
	if(ans > n) puts("-1");
	else writeln(ans - 1);//注意要-1，因为一开始自己是一块不需要
	return 0;
}
```

---

## 作者：liangzihao (赞：1)

首先跑出每个地区的大小，因为边是双向的，所以不用连通分量，直接上并查集去维护即可。假设每个连通块的大小为$x_i$， 现在问题就变成问最少要用多少个$x_i$可以组成一个幸运数字了。因为题目要求的是连接的次数，所以把这个答案减$1$即可。

我们发现所有数字的和是等于$n$的，所以可以用dp，设$f[i][j]$为前i个数，组成和为$j$的数，设第i个数为$a_i$，最小要用多少个数，有
$$f[i][j]=min(f[i-1][j-a_i]+1)$$
显然这会超时，但是我们发现不同的$a_i$顶多只有$\sqrt{n}$个，因为所有$a_i$的和为$n$，而$1$到$\sqrt{n}$的和就已经超过$n$了。所以可以变为一个多重背包，然后使用二进制优化多重背包可以做到$O(n*\sqrt{n}*logk)$，其中$k$为每种数字的个数。虽然$k$最大可以是$1e5$，但是这样$a_i$的总数就很小，一般的复杂度应该是$O(n*\sqrt{n})$的。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

const int maxn=1e5+7;

using namespace std;

int n,m,cnt,x,y;
int p[maxn],f[maxn],b[maxn],size[maxn],w[maxn],v[maxn];

int find(int x)
{
    int y=x,root;
    while (p[x]) x=p[x];
    root=x;
    x=y;
    while (p[x])
    {
        y=p[x];
        p[x]=root;
        x=y;
    }
    return root;
}

void uni(int x,int y)
{
    int u=find(x);
    int v=find(y);
    if (u==v) return;
    if (size[x]>size[y]) p[v]=u,size[u]+=size[v];
                    else p[u]=v,size[v]+=size[u];
}

bool check(int x)
{
    while (x>0)
    {
        if ((x%10!=4) && (x%10!=7)) return false;
        x/=10;
    }
    return true;
}

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) size[i]=1;	
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        uni(x,y);
    }	
    for (int i=1;i<=n;i++)
    {
        if (find(i)==i) b[size[i]]++;
    }		
    memset(f,0x3f3f3f3f,sizeof(f));
    f[0]=0;	
    for (int i=1;i<=n;i++)
    {
        if (!b[i]) continue;
        int sum=1,power=1,k=1;
        w[++cnt]=i;
        v[cnt]=1;
        while (sum<b[i])
        {
            power*=2;
            sum+=power;
            if (sum>=b[i])
            {
                sum-=power;
                w[++cnt]=i*(b[i]-sum);
                v[cnt]=b[i]-sum;
                break;
            }
            w[++cnt]=i*power;
            v[cnt]=power;
        }
    }	
    for (int i=1;i<=cnt;i++)
    {
        for (int j=n;j>=0;j--)
        {
            if (j-w[i]>=0)
            f[j]=min(f[j],f[j-w[i]]+v[i]);
        }
    }	
    int ans=0x3f3f3f3f;	
    for (int i=4;i<=n;i++)
    {
        if (check(i))
        {
            ans=min(ans,f[i]-1);
        }
    }
    if (ans>n) printf("-1");
          else printf("%d",ans);
}
```

---

## 作者：__Hacheylight__ (赞：0)

Codeforces 95E Lucky Country

如果一个数中不包含除4和7之外的数字则是幸运数。

有n个岛屿，通过双向道路连接。这些岛屿被分为几个地区。

每个岛属于恰好一个区域，同一区域中的任何两个岛之间存在道路，不同区域的任何两个岛之间没有路径。

如果一个地区的岛屿数量是一个幸运数字，则这个地区是幸运的。

问最少增加几条道路能创建一个幸运地区。

解析：

可以通过SCC处理强连通，但是我选择了并查集

dp通过二进制提速 $O( a^2 )->O(nlogn)$

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <functional>

using namespace std ;

const int eps=1e-6 ;
const int inf=(1<<29);

#define pb push_back
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define Rep(i,a,b) for(int (i)=(a);(i)< (b);(i)++) 
#define REP(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)

typedef unsigned long long ull ;
typedef long long ll ;

inline int read(){
	char c ;
	int f=1 ;
	while((c=getchar())<'0' || c>'9') if (c=='-') f=-1 ;
	int res=c-'0' ;
	while((c=getchar())>='0' && c<='9') res=res*10+c-'0' ;
	return res*f ;
}

const int N = 100010 ;

map <int,int> mp ;
int f[N],rank[N],dp[N] ;
int n,m ;

int find(int x){
	return (f[x]==x)?x:f[x]=find(f[x]) ;
}

void merge(int x,int y){
	int X=find(x),Y=find(y) ;
	if (X==Y) return ; //现在已经是同一个集合 
	if (rank[X]<=rank[Y]){
		f[X]=Y;
		rank[Y]+=rank[X] ;
	}
	else {
		f[Y]=X ;
		rank[X]+=rank[Y] ;
	}
}

void F(int V,int C,int K){
	REP(i,V,C*K) dp[i]=min(dp[i],dp[i-C*K]+K) ;
}

bool lucky(int x){
	if (x%10!=4 && x%10!=7) return false ;
	if (x<10) return true ;
	return lucky(x/10) ;
}

int main(){
	n=read();m=read();
	Rep(i,0,n){
		f[i]=i;
		rank[i]=1;
	}
	Rep(i,0,m) {
		int x=read(),y=read();
		merge(x-1,y-1) ;
	} 
	Rep(i,0,n) if (find(i)==i) mp[rank[i]]++;
	
	Rep(i,0,n+1) dp[i]=inf ;
	
	dp[0]=0;
	for (map<int,int> ::iterator it=mp.begin();it!=mp.end();it++){
		int sz=(it->first),sum=(it->second) ;
		while (sum>0){
			F(n,sz,(sum+1)/2) ;
			sum/=2 ;
		} 
	} 
	int ans=inf ;
	Rep(i,0,n+1) if (lucky(i)) ans=min(ans,dp[i]) ;
	printf("%d\n",ans==inf?-1:ans-1) ;
	 
	return 0 ;
}

```

---

## 作者：封禁用户 (赞：0)

这是一道水题，先通过dfs求出所以连通块的大小，然后dp即可
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const int INF=0x3f3f3f3f;
int n,m,x,y,sum;
int vis[N],dp[N];
vector<int>e[N],v;
map<int,int>mp;
void dfs(int x)
{
	vis[x]=1;
	for(int i=0;i<e[x].size();i++)
		if(!vis[e[x][i]])
			dfs(e[x][i]);
	sum++;
}
bool lucky(int x)
{
	while(x)
	{
		if(x%10!=4&&x%10!=7)
			return false;
		x/=10;
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			sum=0;
			dfs(i);
			mp[sum]++;
		}
	}
	for(int i=1;i<=n;i++)
		dp[i]=INF;
	for(auto itr=mp.begin();itr!=mp.end();itr++)
	{
		int c=itr->first,k=itr->second;
		while(k>0)
		{
			for(int i=n;i>=c*((k+1)/2);i--)
				dp[i]=min(dp[i],dp[i-c*((k+1)/2)]+(k+1)/2);
			k/=2;
		}
	}
	int ans=INF;
	for(int i=1;i<=n;i++)
		if(lucky(i))
			ans=min(ans,dp[i]);
	if(ans==INF)
		printf("-1\n");
	else
		printf("%d\n",ans-1);
	return 0;
}

```

---

