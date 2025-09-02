# Permutation Shift

## 题目描述

一个长度为 $n$ 的初始排列为 $[1,2,3,4,\ldots,n]$ 。
对其进行下列操作：

* 首先，我们将其循环移动 $k$ 位， $k$ 为一个未知数 $(0 \leq k \leq n-1)$ 。

将一个长度为 $n$ 的数组循环移动k位就是将原数组最后 $k$ 位移动到第 $1 \sim k$ 位，并将其余 $n-k$ 位移动到第 $k+1 \sim n$ 位。比如说，我们将 $[1,2,3,4,5,6]$ 循环移动两位，就是 $[5,6,1,2,3,4]$ 。

* 然后，我们将数组中任意两个数交换，最多进行 $m$ 次。

给定 $n,m$ 和最后的结果，你需要找出所有可能的 $k$ 值。

## 样例 #1

### 输入

```
4
4 1
2 3 1 4
3 1
1 2 3
3 1
3 2 1
6 0
1 2 3 4 6 5```

### 输出

```
1 3
1 0
3 0 1 2
0```

# 题解

## 作者：TLE_Automat (赞：13)

## **题意：**

给定一个长度为 $n$ 的目标排列 $p$ 和一个整数 $m$ ，并且你有一个初始排列 $[1,2,...,n]$ 。

现在请你求出所有满足以下条件的整数 $k(0\le k\le n-1)$ ： 

将初始排列**向右**循环位移 $k$ 次后，得到排列 $a$ ，把 $a$ 的元素进行**不超过** $m$ 次交换，使得 $a = p$ 。

 ## **数据范围：**

- 本题有多组数据。
- 对于每组数据 $3\le n \le 3\times 10^5 , 0 \le m \le \frac{n}{3}$ 。
- 对于所有数据，保证每组数据的 $n$ 的和不超过 $3 \times 10^5$ 。

## **思路：**

首先，我们第一反应大概率是枚举每一个 $k$ ，然后快速判断行不行，我们先按照这个思路走下去。

如果我们确定一个 $k$ ，假设初始排列向右循环位移 $k$ 次后，与目标排列 $p$ 的**对应位置上**相同的数字的个数为 $cnt$ 个，因为我们最多交换 $m$ 次，所以我们最多改变 $2\cdot m$ 个位置，所以不难看出：若 $cnt<n-2\cdot m$ ，$k$ 肯定不满足。

所以如果 $k$  满足条件 ，那么 $cnt$ 必须大于等于 $n-2\cdot m$ ，又因为 $m\le \frac{n}{3}$ ，所以 $cnt \ge n - \frac{2\cdot n}{3} = \frac{n}{3}$ 恒成立，至此，我们得到一个显然的结论，满足条件的 $k$ 不会超过 $3$ 个，题目一下子就明朗了起来。

那这样，我们只需要考虑如何快速判断一个排列 $a$ 最少需要交换多少次换到目标排列 $p$ 。我们只需要把 $a_i$ 向 $p_i$ 连一条无向边，最后用 $n$ 减去联通块个数就是最小的交换次数。

至此，本题完结，时间复杂度 $O(n)$ 。





---

## 作者：cunzai_zsy0531 (赞：8)

## CF1553E题解-by cunzai_zsy0531

[题面](https://www.luogu.com.cn/problem/CF1553E)

一道心理阴影题。

题意已经很明显了，$O(n^2)$ 做法就是，对于每个 $k$，求最少多少次交换可以使一个排列变为另一个排列。做法是说，对于同一个数，若它在两个排列中的位置不同（记这样的数的总数为 $s$），就建一条连接这两个位置的边，求得图的连通分量数 $c$，答案就是 $s-c$。

考场上想到这个，但是无论如何都不会优化了。不会优化就直接做啊！

考虑到这个题给了一个限制 $m$，最理想的情况下，可以做有 $2m$ 个数位置不对的两个排列。那么 $s>2m$ 的肯定都不可以。题目中给了一个 $m\leq \frac{n}{3}$，这时候就派上用场了：设旋转参数为 $k$ 的时候，两个排列位置一样的个数为 $cnt_k$，那么 $\sum_{i=0}^{n-1}cnt_i=n$。所以，满足 $s\leq 2m$ 的 $k$ 的数量最多不超过 $3$！直接 $O(3n)$ 做完了。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define pb push_back
using namespace std;
const int N=3e5+13;
int n,m,cnt[N],p[N],ans[N];
vector<int> g[N];
bool vis[N];
inline void add_edge(int u,int v){g[u].pb(v);}
void dfs(int u){
	vis[u]=1;
	for(auto v:g[u])
		if(!vis[v]) dfs(v);
}
inline void solve(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) cnt[i]=0;
	for(int i=1;i<=n;++i){
		int x;scanf("%d",&x);
		p[x]=i;
		cnt[(i-x+n)%n]++;//这种情况下，x这个数的位置不需要动
	}
	int t=0;
	for(int k=0;k<n;++k){
		if(cnt[k]<n-2*m) continue;//不可能成功了，直接特判掉，能往下走的k最多3个
		for(int i=1;i<=n;++i) vis[i]=0,g[i].clear();
		for(int i=1;i<=n;++i){
			int pos=(i+k-1)%n+1;
			if(pos!=p[i]) add_edge(pos,p[i]);//加边
		}
		int c=0;
		for(int i=1;i<=n;++i){
			int pos=(i+k-1)%n+1;
			if(pos!=p[i]&&!vis[pos]) dfs(pos),++c;//求连通分量个数
		}
		if(n-cnt[k]-c<=m) ans[++t]=k;//最后判断是否可行
	}
	printf("%d ",t);for(int i=1;i<=t;++i) printf("%d ",ans[i]);putchar('\n');
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
//E
```


---

## 作者：5ab_juruo (赞：3)

观察到操作的顺序对题目答案没有本质影响，所以我们可以枚举 $k$，即将新的数组向左移位来抵消影响。

我们观察到 $m\le \dfrac{n}{3}$，即会有至少 $\dfrac{1}{3}$ 的数没有被交换。同时，一个数没有被交换而这个序列满足条件当且仅当这个数在原位置上。同时，易得对于每个数，有且仅有一个 $k$ 使这个数在原位置上。所以，这样的 $k$ 最多只有 $3$ 个。

所以，我们记录 $k$ 使数在原位置上的个数 $cnt_k$，如果 $cnt_k\ge n-2m$ 就暴力计算需要多少次交换。显然，如果从 $i$ 向 $a_i$ 连边，则答案就是 $n-\text{环数}$，复杂度 $\mathcal{O}(n)$。

Code：
```cpp
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int max_n = 300000;

int cnt[max_n], a[max_n], k[3];
bool vis[max_n];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int cas, n, m, kc, lc, ptr;
	
	cin >> cas;
	while (cas--)
	{
		kc = 0;
		
		cin >> n >> m;
		
		for (int i = 0; i < n; i++)
			cnt[i] = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i], a[i]--;
			cnt[(i+n-a[i])%n]++; // 统计个数
		}
		
		for (int i = 0; i < n; i++)
			if (cnt[i] >= n - 2 * m) // 是可能的 k
			{
				for (int j = 0; j < n; j++)
					vis[j] = false;
				lc = 0;
				for (int j = 0; j < n; j++) // 数环数
					if (!vis[j])
					{
						ptr = j;
						while (!vis[ptr]) // 遍历环
						{
							vis[ptr] = true;
							ptr = (a[ptr] + i) % n;
						}
						lc++;
					}
				
				if (n - lc <= m) // 满足就算上
					k[kc++] = i;
			}
		
		cout << kc;
		for (int i = 0; i < kc; i++)
			cout << " " << k[i];
		cout << endl;
	}
	
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：2)

很久很久之前做的题，怀念一下那段美好时光顺带写个题解。\
给了一个 $m\le \frac{n}{3}$，不觉得很神秘吗，来研究一下这里，首先有经典东西：每次交换最多可以改变两个数的位置。也就是说，有至多 $2m$ 的数匹配不上移位，剩下至少 $\frac{n}{3}$ 个数一定可以与移位匹配上，考虑找出这样的匹配位置来。\
对于每一个位置都求出他需要的 $k$，只有个数大于等于 $\frac{n}{3}$ 的 $k$ 值才有可能是答案，换句话说，合法的 $k$ 最多有 $3$ 个，枚举并直接暴力检查交换次数是否不超过 $m$ 就行了。\
当然，最后的检验也可以不那么简单粗暴，一个排列到另一个排列的最小交换次数就等于 $n$ 减去相应位置连边后的图的环数。证明就是最后一定全是自环，而每次交换可以把一个环变成两个，增加了一个环。

---

## 作者：Madefaker (赞：2)

##### E

题目大意：给定一个长度为 $n$ 数组 $p$，求可以将数组 $id = [1,2,3,...,n]$ 通过循环右移 $k(0 \le k \le n - 1)$ 次之后，交换**不小于** $m(0 \le m \le \frac{n}{3})$ 个数字，得到数组 $p$ 的 $k$ 的个数。

如果把数组中的所有元素减一，那么数组变成 $[0,1,2,..,n-1]$，右移 $k$ 位之后第 $i$ 位（从 $0$ 开始）原本是 $i$，变成 $(i-k) \operatorname{mod} n$，表示比较方便。

可以想到遍历每一个 $k$，判断 $id >> k$（即 $(id>>k)_i = (i - k) \operatorname{mod} n$ 要变成 $p$ 的最小次数是否小于等于 $m$。要如何判断呢？以下是经典模型：

$a$ 数组和 $b$ 数组都有 $n$ 个数，并且它们都是 $n$ 的排列。若每次可以交换 $a$ 中任意的两个数，求将 $a$ 变成 $b$ 的最小交换次数。

例如 $a = [4,2,3,1],b = [1,2,3,4]$，将 $a_0=4$ 与 $a_3 = 1$ 交换，得到 $b$ 数组。于是最小交换次数为 $1$。

这个基本模型的一个通用解法是：建立一张 $n$ 个点的图，对于 $0 \le i \le n - 1$，建立无向边 $a_i,b_i$。那么最小交换次数就是 $n-c$，其中 $c$ 表示这个图中连通块的个数。

![](![](https://cdn.luogu.com.cn/upload/image_hosting/wafbjgji.png))

原理：交换 $(a[i],a[j])$ 相当于断开边 $(a[i],b[i]),(a[j],b[j])$，并加边 $(a[i],b[j]),(a[j],b[i])$。 因为一个环（没有其他多余的边）删去两条边一定能够将其断成两个环，那么交换一次环内的边就可以把一个环断成两个环，即环数 $+1$。

注意到，如果超过 $2 \times m$ 个数字是不在位置上的，那么需要的交换次数超过 $m$。所以在位置上的数字数必须大于 $n - 2 \times m$。于是我们只需要判断在位置上的数字数 $cnt_k$ 大于 $n - 2 \times m$ 的 $k$。因为对于每一个 $p_i$，只有一个 $k$ 满足 $(i-k) \operatorname{mod} n = p_i$。所以在位置上的数之和为 $n$。由于 $m \le \frac{n}{3}$，所以满足 $cnt_k \ge n - 2 \times \frac{n}{3} = \frac{n}{3}$ 的 $k$ 最多有 $n \div \frac{n}{3} = 3$ 个取值。

因此对于每一个测试点，最多用以上模型检验 $3$ 次，故时间复杂度 $O(n)$。



---

## 作者：mango2011 (赞：0)

为什么大家都这么强悍？其实不用任何图论知识，也可以过掉这题的！

首先，我们观察一下 $i$ 在 $k$ 次循环位移之后到了哪里。然后就很容易地发现如果 $i$ 在结果中的位置为 $j$，则 $k=(n-i+j)\bmod n$ 的时候 $i$ 恰好与结果匹配，于是可以在 $O(n)$ 的时间复杂度内得到每个 $k$，有多少个元素可以匹配。

显然，如果当前有 $t$ 个与结果不匹配，那么至少需要 $\lceil\frac{t}{2}\rceil$ 次操作。结合题目限制中的 $m$，我们发现可能的 $k$ 的数量可以控制在一个很小的常数。

接下来就是有趣的贪心环节：

假设我们的 $k$ 有可能是答案（由于这样的 $k$ 极少，所以可以暴力检查），设 $[1,2,3,\dots,n]$ 循环位移 $k$ 次之后得到了 $b_1,b_2,b_3,\dots,b_n$。那么我们从首位开始往下寻找，一遇到不同的，就把后面的拿过来，与之交换，统计次数并与 $m$ 比较即可。正确性显然。

于是我们就做完了这题（大佬们的图论方法我是真没看懂啊）。

---

## 作者：5k_sync_closer (赞：0)

首先枚举 $k$，然后问题变为，求给定排列 $p'$ 能否在 $m$ 次交换内排好序（P1327），

考虑形式比较良好的做法：由 $i$ 向 $p'_i$ 连边，形成 $x$ 个环，则至少需要交换 $n-x$ 次才能排好序。

可以得到 $O(n^2)$ 的做法。

要求 $x\ge n-m$，注意到 $n-m$ 不会很小，即环必须较多，

则合法情形下自环数目也较多（不少于 $n-2m$ 个），

而 $n-2m\ge\dfrac n3$，即形成不少于 $n-2m$ 个自环的，有可能合法的 $k$ 不超过 $3$ 个，

统计每个 $k$ 形成多少个自环是容易的，取出可能合法的不超过 $3$ 个 $k$ 依次用 P1327 的方法检查即可。

```cpp
#include <cstdio>
int T, n, m, o, a[300050], c[300050], f[300050], z[300050];
int F(int x) { return x == f[x] ? x : f[x] = F(f[x]); }
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (int i = 1; i <= n; ++i)
            ++c[(i - a[i] + n) % n];
        for (int k = 0; k < n; ++k)
            if (c[k] >= n - 2 * m)
            {
                for (int i = 1; i <= n; ++i)
                    f[i] = i;
                for (int i = 1; i <= n; ++i)
                    f[F(a[i])] = F((i - k + n - 1) % n + 1);
                int q = n;
                for (int i = 1; i <= n; ++i)
                    if (i == F(i))
                        --q;
                if (q <= m)
                    z[++o] = k;
            }
        printf("%d ", o);
        for (int i = 1; i <= o; ++i)
            printf("%d ", z[i]);
        puts("");
        o = 0;
        for (int i = 0; i <= n; ++i)
            a[i] = c[i] = f[i] = z[i] = 0;
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1553E 题解



## 思路分析

通过交换元素使一个排列 $\{p_i\}$ 复原是一个十分经典的问题，只需要对所有的 $i$ 向 $p_i$ 连边得到一张有向图 $\mathbf G$，记 $\operatorname{cyc}(\mathbf G)$ 表示 $\mathbf G$ 中环的个数，那么复原 $\{p_i\}$ 的代价为 $n-\operatorname{cyc}(\mathbf G)$。

由于我们发现对 $1\sim n$ 右移 $k$ 位后匹配等价于使 $\{p_i\}$ 左移 $k$ 位后匹配，因此我们只需要对于每个 $k$ 验证一下 $\{p_i\}$ 左移 $k$ 位后能否在 $m$ 的代价以内复原为 $1\sim n$。

注意到每次检查一个 $k$ 的复杂度是 $\Theta(n)$，如果检查每一个 $k$ 一定会超时，不过我们注意到如下的观察：

> 观察：
>
> 对于任意的 $n,m$，合法的 $k$ 的数量不超过 $\left\lfloor\dfrac{n}{n-2\times m}\right\rfloor$ 个。
>
> 对于一个排列 $\{p_i\}$，每次操作至多使 $2$ 个 $p_i,p_j$ 复位，因此在原本的 $\{p_i\}$ 中至多只有 $2\times m$ 个 $i$ 失配，所以满足 $p_i=i$ 的至少 $n-2\times m$ 个。
>
> 回到原问题上，对于某个位置 $i$，有且仅有一个 $k$ 使得 $\{p_i\}$ 左移 $k$ 位后得到 $p_i=i$，因此对于所有 $k$，匹配的 $p_i$ 的数量总和为 $n$。
>
> 通过抽屉原理，我们得到：合法的 $k$ 的数量不超过 $\left\lfloor\dfrac{n}{n-2\times m}\right\rfloor$。

根据观察，又因为数据范围中保证 $m\le\tfrac13n$，因此合法 $k$ 的个数不超过 $3$。

所以我们只需要对于每个 $k$ 计算已经有多少个 $i$ 匹配成功，然后对于匹配成功的超过 $n-2\times m$ 的 $k$ 暴力验证即可。

时间复杂度 $\Theta(n)$。


## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=3e5+1;
int n,m,a[MAXN],cnt[MAXN];
bool vis[MAXN];
vector <int> G[MAXN];
inline void dfs(int p) {
	vis[p]=true;
	for(int v:G[p]) if(!vis[v]) dfs(v);
}
inline bool check(int k) {
	for(int i=1;i<=n;++i) G[i].clear(),vis[i]=false;
	for(int i=1;i<=n;++i) {
		G[(i+n-k)%n==0?n:(i+n-k)%n].push_back(a[i]);
	}
	int cnt=0;
	for(int i=1;i<=n;++i) {
		if(!vis[i]) ++cnt,dfs(i);
	}
	return (n-cnt)<=m;
}
inline void solve() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		++cnt[(i+n-a[i])%n];
	}
	vector <int> ans;
	for(int i=0;i<n;++i) {
		if(cnt[i]>=n-2*m&&check(i)) ans.push_back(i);
	}
	printf("%d ",(int)ans.size());
	for(int i:ans) printf("%d ",i);
	puts("");
} 
signed main() {
	int T;
	scanf("%d",&T) ;
	while(T--) solve();
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2100}$
---

看到有人说不好优化，于是我就来优化了。

---
### 解题思路：

首先初步转化问题，先写出一个顺序移动过若干位的，也就是形如：$5,6,7,8,1,2,3,4$ 的序列，然后用这个序列和给出的 $p$ 进行比较。观察到，只要这个序列和原序列不同的地方不超过 $2m$ 个，就一定能够完成最终的交换。

但是暴力是不行的，考虑优化。

考虑到两个序列中一个和 $a_i=i$ 的形式有相似之处，而且每一次的变化似乎也比较相似，考虑将 $b_i=p_i-i$，这样对于一开始的序列而言，$0$ 的位置就是匹配成功地位置。

然后考虑每一次循环移动，将两个连续的变化后的数组做差，将其加到 $b$ 上其实也就完成了一次变换。然后具体研究这个用来做差的数组，可以发现，这个数组是形如 $1,1,1,\cdots,n-1,\cdots ,1,1,1$ 的，也就是除了当前变化的位置其它都是 $1$。

然后就随便做了，直接分开计算前面的贡献，开个桶记录一下每一个值有多少个，顺序扫描一遍，然后反过来再做一遍就行了。最后需要再验证一遍，由于 $m\le \dfrac{n}{3}$，最多只会验证三次，总复杂度还是 $O(n)$ 的。

---
### 代码：
```cpp
#include<cstdio>
#include<map>
using namespace std;
int T,n,m,p[300005],rt[300005],ans[300005],cnt,x[300005],c[300005],px[300005];
map <int,int> mp;
void init(){
	mp.clear();cnt=0;
	for(int i=1;i<=n;i++)rt[i]=0,p[i]=0,ans[i]=0;;
}
bool check(int now){
	int cnt=0;
	for(int i=1;i<=now;i++)x[i]=n-now+i;
	for(int i=now+1;i<=n;i++)x[i]=i-now;
	for(int i=1;i<=n;i++)px[x[i]]=i;
	for(int i=1;i<=n;i++)c[i]=p[i];
	for(int i=1;i<=n;i++){ 
		while(c[i]!=x[i]){
			swap(c[i],c[px[c[i]]]);
			cnt++;
		}
	}
	return cnt<=m;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&p[i]);
		for(int i=1;i<=n;i++){
			mp[p[i]-n-i+1]++;
			rt[i]+=mp[1-i];
		}
		mp.clear();
		for(int i=1;i<=n;i++)mp[p[i]-i]++;
		for(int i=1;i<=n;i++){
			rt[i]+=mp[-i];
			mp[p[i]-i]--;
		}
		
		for(int i=1;i<=n;i++)
		if(n-rt[i]<=2*m)
		if(check(i%n))
		ans[++cnt]=i;
		
		printf("%d ",cnt);
		if(ans[cnt]==n){printf("0 ");cnt--;}
		for(int i=1;i<=cnt;i++)
		printf("%d ",ans[i]);
		printf("\n");
		init();
	}
	return 0;
}
```


---

## 作者：Little09 (赞：0)

如果一个排列 $p$ 经过至多 $m$ 次交换能变成 $p'$，那么它们元素不同的位置 $i$ （即不满足 $p_i=p'_i$）至多能有 $2\times m$ 个。也就是说，至少要有 $n-2\times m$ 个位置，两个排列上的数相同。

注意到 $m\le \frac{n}{3}$，也就是 $n-2\times m\ge  \frac{n}{3}$。所以每次可能的情况，至少要有 $\frac{n}{3}$ 的位置两个排列相同。

考虑循环移位的操作，经过 $n-1$ 次移位形成的 $n$ 个排列，每个元素只能在其中 $1$ 次，满足 $p_i=p'_i$。

所以至多只有 $3$ 个排列满足要求，判断一下这 $3$ 个即可。

代码：[link](https://codeforces.ml/contest/1553/submission/123324325)。

---

