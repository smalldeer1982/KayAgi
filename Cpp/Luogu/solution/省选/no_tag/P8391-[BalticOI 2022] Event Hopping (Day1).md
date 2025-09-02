# [BalticOI 2022] Event Hopping (Day1)

## 题目描述

有 $n$ 个区间，第 $i$ 个区间为 $[l_i,r_i]$。

你可以在区间之间跳跃。当你在第 $x$ 个区间上时，你可以跳到一个覆盖右端点 $r_x$ 的区间 $y$ 上，即从 $x$ 能跳到 $y$ 当且仅当 $[r_x \in [l_y,r_y]]$。

有 $q$ 次询问，每次你一开始在第 $s_i$ 个区间，你需要跳到第 $t_i$ 个区间。你需要输出你至少需要跳多少次。如果不能跳到，输出 `impossible`。

## 说明/提示

- 子任务 $1$ ($10$ 分)：每一个区间可以跳到至多一个其他区间。

- 子任务 $2$ ($10$ 分)：$n≤ 1000$，$q ≤100$。

- 子任务 $3$ ($15$ 分)：$n≤5000$。

- 子任务 $4$ ($15$ 分)：$q ≤100$。

- 子任务 $5$ ($20$ 分)：不存在两个区间 $i,j$ 满足 $[l_i, r_i] \subseteq [l_j,r_j]$。

- 子任务 $6$ ($30$ 分)：没有特殊限制。

对于所有数据，满足 $1≤n,q ≤100000$，$1≤l_i<r_i≤10^9$，$1≤s_i,t_i≤n$。

## 样例 #1

### 输入

```
5 2
1 3
2 4
4 7
7 9
3 7
1 4
3 2```

### 输出

```
2
impossible
```

## 样例 #2

### 输入

```
8 5
1 2
3 4
1 5
6 7
5 10
10 20
15 20
999999999 1000000000
1 6
1 7
2 4
3 3
5 8
```

### 输出

```
3
4
impossible
0
impossible```

# 题解

## 作者：Acee (赞：4)

暴力就是直接建出图来，跑最短路。

可以用线段树优化建图，但没有前途。

从前往后肯定不行，因为太多选择。

正难则反，反着来贪心发现 $l$ 越小越好。

这个可以用线段树来求。

接着，每一个点都只有一个选择，即一个父亲，所以变成了树。

然后，图就变成了树，然后树上倍增就可以求了。

[代码](https://loj.ac/s/1984789)

---

## 作者：一只绝帆 (赞：2)

这题似乎曾经在 2023 的 SD 三轮省集被加强到了空间 $\mathcal O(n)$，不过被我用 `int24` 卡过去了。

每个点往右跳没什么规律，但是能跳到一条线段的线段们的右端点一定是连续的一段区间，因为每新扩展一个区间，新的候选右端点跟原来的候选右端点们一定是连着的（可以自己画个图理解）。

于是就变成了一棵树，每条线段都想往左跳到尽量左的左端点，值得注意的是你不仅可以使用倍增，你还可以建出树来使用树剖完成这个跳的操作，即链顶合法就跳链顶，否则在最上面一段进行二分，这样空间是线性的。

代码其他题解比较完备，不放了。

---

## 作者：cike_bilibili (赞：2)

# 思路
正难则反，从前跳到后显然是不好实现的，所以可以考虑从后跳到前。问题转化为在一个区间内挑选一个右端点对应的区间跳过去。

显然，选到的区间对应的左端点越靠左，能够在新区间选择的区间就越多，所以在区间内贪心选择左端点最靠左的区间即可，可以用 ST 表维护。

容易看出，每一个区间所对应的下一个区间都是固定的，所以可以使用倍增加速。

# AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,m;
struct node{
	int l;
	int r;
	int id;
}a[100005],b[100005];
bool cmp(node a,node b){
	if(a.r==b.r)return a.l<b.l;
	return a.r<b.r;
}
int st[100005][25];
int belong[100005];
int ge[100005][25];
void init(){
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			(st[i][j-1]>st[i+(1<<(j-1))][j-1])?ge[i][j]=ge[i+(1<<(j-1))][j-1]:ge[i][j]=ge[i][j-1];
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int l,int r){
	int p=log2(r-l+1);
	return (st[l][p]>st[r-(1<<p)+1][p])?ge[r-(1<<p)+1][p]:ge[l][p] ;
}
int ne[100005][25];
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		a[i]={x,y,i};
		b[i]={x,y,i};
	}
	stable_sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		st[i][0]=a[i].l;
		ge[i][0]=a[i].id;
	}
	init();
	for(int i=1;i<=n;i++){
		int L=1,R=i;
		while(L<R){
			int mid=(L+R)>>1;
			if(a[mid].r<a[i].l)L=mid+1;
			else R=mid;
		}
		if(L!=i) ne[a[i].id][0]=query(L,i);
		else ne[a[i].id][0]=0;
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n;i++){
			ne[i][j]=ne[ne[i][j-1]][j-1];
		}
	}
	while(m--){
		int ans=0;
		int x=read(),y=read();
		if(b[x].r>b[y].r){
			printf("impossible\n");
			continue;
		}
		if(x==y){
			printf("0\n");
			continue;
		}
		if(b[y].r>=b[x].r&&b[y].l<=b[x].r){
			printf("1\n");
			continue;
		}
		for(int i=24;i>=0;i--){
			if(ne[y][i]&&b[ne[y][i]].l>b[x].r)y=ne[y][i],ans+=(1<<i);
		}
		if(ne[y][0]==0){
			printf("impossible\n");
		}
		else{
			printf("%d\n",ans+2);
		}
	}
}
```


---

## 作者：7KByte (赞：2)

如果按照给定的题意直接模拟，就会发现每次向右边跳会有多种选择，而我们无法在这多种选择中做出决策。

所以我们选择倒着做，从 $t$ 跳回到 $s$，那么这个过程中区间的 $l,r$ 都不增，那么我们每次选择能跳到的区间中 $l$ 最小即可。预处理后直接倍增即可，时间复杂度 $\mathcal{O}((n + q)\log n)$。

```cpp
#define N 100005
#define M 200005
int n, q, l[N], r[N], f[N][17], w, c[M], u[M], m; vector<int>a[M], b[M];
int ck(int x,int y){return l[x] < l[y] ? x : y;}
inline void ins(int x,int w){for(; x <= m; x += x & -x)c[x] = ck(c[x], w);}
inline int ask(int x){int w = 0; for(; x; x -= x & -x)w = ck(c[x], w); return w;}
int main() {
	read(n, q), w = log2(n);
	rp(i, n)read(l[i], r[i]), u[++m] = l[i], u[++m] = r[i];
	sort(u + 1, u + m + 1), m = unique(u + 1, u + m + 1) - u - 1;
	rp(i, n){
		l[i] = lower_bound(u + 1, u + m + 1, l[i]) - u, r[i] = lower_bound(u + 1, u + m + 1, r[i]) - u;
		a[l[i]].pb(i), b[r[i]].pb(i);
	}
	l[0] = inf;
	pr(i, m){
		go(x, b[i])ins(i, x);
		go(x, a[i])f[x][0] = ask(r[x]);
	}
	rp(j, w)rp(i, n)f[i][j] = f[f[i][j - 1]][j - 1];
	while(q--){
		int s, t;
		read(s, t);
		if(r[s] > r[t])puts("impossible");
		else if(s == t)puts("0");
		else{
			int ans = 1;
			pre(i, w, 0)if(l[f[t][i]] > r[s])ans += 1 << i, t = f[t][i];
			if(l[f[t][0]] > r[s]){puts("impossible"); continue;}
			if(l[t] > r[s])ans++;
			printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

