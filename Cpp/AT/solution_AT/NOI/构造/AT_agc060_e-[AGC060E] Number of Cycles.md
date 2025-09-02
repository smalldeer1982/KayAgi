# [AGC060E] Number of Cycles

## 题目描述

在本题中，提到“顺序”时，指的是 $ (1,2,\cdots,N) $ 的一个排列。

对于一个排列 $ a=(a_1,a_2,\cdots,a_N) $，定义 $ f(a) $ 为 $ a $ 的循环节（cycle）的个数。更准确地说，$ f(a) $ 的值定义如下：

- 考虑一个有 $ N $ 个顶点、编号为 $ 1 $ 到 $ N $ 的无向图。对于每个 $ 1\leq i\leq N $，在顶点 $ i $ 和顶点 $ a_i $ 之间连一条边。此时，该图的连通分量个数即为 $ f(a) $。

给定一个排列 $ P=(P_1,P_2,\cdots,P_N) $ 和一个整数 $ K $。判断是否存在一个排列 $ x $，使得下列条件成立，并在存在时构造出一个解：

- 令 $ y_i=P_{x_i} $，从而得到排列 $ y $。
- 满足 $ f(x)+f(y)=K $。

对于每个输入文件，需要解答 $ T $ 个测试用例。

## 说明/提示

### 数据范围

- $ 1\leq T\leq 10^5 $
- $ 2\leq N\leq 2\times 10^5 $
- $ 2\leq K\leq 2N $
- $ (P_1,P_2,\cdots,P_N) $ 是 $ (1,2,\cdots,N) $ 的一个排列
- 每个输入文件中所有 $ N $ 的总和不超过 $ 2\times 10^5 $
- 输入的所有数均为整数

### 样例解释 1

在第 $ 1 $ 个测试用例中，取 $ x=(2,1,3) $，则 $ y=(3,1,2) $，此时 $ f(x)+f(y)=2+1=3 $。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 3
1 3 2
2 2
2 1
4 8
1 2 3 4```

### 输出

```
Yes
2 1 3
No
Yes
1 2 3 4```

# 题解

## 作者：yszs (赞：5)


[传送门](https://www.luogu.com.cn/problem/AT_agc060_e)

## 非常非常非常详细的题解

发现题解区的题解不是很详细啊，所以就自己写了一篇。

里面包含所有结论的详细证明图解，如果哪个地方有问题欢迎指出来。

求过 $\texttt{QwQ}$。

### $\texttt{Description}$

对于一个 $1$ ~ $n$ 的排列 $a$，设 $f(a)$ 表示排列 $a$ 的环数。

给定 $n$,$m$ 和一个排列 $a$，称一个排列 $b$ 是好的当且仅当它满足下列条件：

- 设排列 $c$ 满足 $c_{i}=a_{b_{i}}$，那么 $f(b)+f(c)=m$。

你需要构造一个好的排列 $b$ 或输出无解。

$n\leq 2\times 10^{5}$。

### $\texttt{Solution}$

考虑调整法。

每次交换一个排列的两个元素可以使答案 $\pm 1$。

一种情况是大环分裂成两个小环，答案 $+1$。

另一种情况是两个环合并成一个大环，答案 $-1$。

因为交换 $b$ 的两个元素会交换 $c$ 的两个元素。

所以交换一次答案的变化只有 $2,0,-2$。

那么显然如果 $k$ 与 $f(b)+f(c)$ 奇偶性不同，一定无解。

那考虑构造出最大值，最小值。

然后通过最小值调整到最大值，或者最大值调整到最小值。

所以如果 $k$ 在最大值最小值之中，且奇偶性相同，那么有解。

---

>结论 $1$:最大值是 $f(p)+n$，当 $x_i=i$ 时取到。

反证法证明:

- 如果存在 $f(x)<n$ 并且 $f(x)+f(y)> f(p)+n $。

- 那么 $x$ 一定可以通过交换两个元素使 $f(x) +1$，所以 $f(x)+f(y)$ 不降。

- 当调整到 $f(x)$ 等于 $n$ 时，$y=p$，与 $f(x)+f(y)>f(p)+n$ 矛盾。

---

>结论 $2$：最小值要么是2要么是3。

>x首先 $f(b)+f(c)\ge 2$ 不能再小了。

证明:

- 考虑这么一个构造方法:

- 不要忘了排列对应的图上每个点的入度为 $1$，出度为 $1$。

- 因为我们有两个排列，所以我们想象两个图，一个代表 $b$，一个代表 $c$，初始无边。

- 我们一个一个给每个点连出边，最后一个点确定且会形成环。

	- 怎么连？

- 考虑贪心，如果一个点的出边**连向自己所在联通块**，那么会**使 $f(x)$ 值变大**，所以我们每次都连与自己不相连的连通块，直到不管怎么连都会使 $f(b)$ 增大:

- 首先要注意每个点入度为 $1$，所以一个点所在的连通块，只有一个点可以接收边。

- 假如当前正在给第 $i$ 个点分配出边，那么每个图上都有 $n-i+1$ 个连通块，对于 $i$ 的连边小小分讨一下。

上图！

![](https://cdn.luogu.com.cn/upload/image_hosting/yextseny.png)

一共有两种决策：

![](https://cdn.luogu.com.cn/upload/image_hosting/z008mdqz.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/86xp8suz.png)

聪明的你一定发现了什么时候会出现问题了。

没错！

>当只有两个连通块时，出现 $(1)$ 情况时一定会形成一个环。

>出现 $(2)$ 情况则不会有环。

这时 $i=n-1$。

$i=n$ 的时候连边确定，一定都会形成环。

>所以情况 $(1)$ 就对应了 $f(b)+f(c)=3$。

>情况 $(2)$ 对应了 $f(b)+f(c)=2$。

因为不可能出现答案小于 $2$ 的情况。

自然最小奇数值就是 $3$ 了。

---

然后你通过上述方法构造出了一个下界。

发现其中一定有一个排列是只有一个环的。

先不管另一个排列。

我们对这个环动手脚。

每次通过交换**一步**把他的大环分裂成一个自环和一个大环答案 $+1$，所以这时 $f(b)+f(c)$ 不降。

如果枚举对应变化然后求 $f(x)+f(y)$ 复杂度是 $O(n^2)$ 的。

但是这个东西不降，所以考虑二分自环个数，然后 $O(n) \ \text{check}$。

复杂度 $O(n\log n)$。

代码为了实现方便用了并查集。

[code](https://www.luogu.com.cn/paste/n5un5ld7)

---

## 作者：xkai (赞：3)

来一个 $O(n)$ 的打表+构造的做法。其中打表主要是打一些结论，这部分其他题解已有证明。

首先去打表 $p$ 为单独一个环的情况，容易发现当 $p$ 的长度为偶数时，$k$ 取 $[3,n+1]$ 之间所有的奇数；$p$ 的长度为奇数时，$k$ 取 $[2,n+1]$ 之间所有的偶数。

这时候再去打 $p$ 有多个环的情况，会发现答案的规律是相同的。而且还有这样的规律，每个偶环会改变答案的奇偶性，奇环不会。

然后就开构了。以下只用文字说明构造方法，建议配合手玩理解。

对于单个环的情况，选择环上连续的一段成为自环，剩下的一段连成一个环。可以发现在枚举自环数量的过程中可以取到所有的答案。

对于多个环，首先要把所有环的最小值相加，如果询问的 $k$ 大于等于这个最小值，那么每个环就可以独立开做了。否则我们就要考虑去合并一些环。

容易发现我们只需要做这样的问题：有多个环，要让答案为 $2,3,4$ 中的某个数。其中答案为 $2,4$，则偶环必定存在偶数个；答案为 $3$ 偶环存在奇数个。

我们考虑把每个偶环拆成一个单点加一条奇链。对于多个偶环，我们把它们的单点顺次连接，奇链顺次连接。这样就得到两条链了，称为点链和链链。然后如果要求答案 $2$ 则将点链尾连向链链首，链链尾连向点链首（交错连接）；要求答案为 $4$ 将点链尾连向点链首，链链尾连向链链首（同向连接）；要求答案为 $3$ 可以上述两种方法任意。

然后再来考虑奇环，可以把它断成一条链，插入上述得到的环上的任意一个位置。

时间复杂度 $O(n)$。代码比较丑。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=200010;
int n,k,p[N],b[N];bool vis[N];

vector<int>oo[N];int tot;
void GG(int t){
	sort(oo+1,oo+1+tot,[&](vector<int>&a,vector<int>&b){
		return (a.size()&1)<(b.size()&1);
	});
	if(oo[1].size()&1){
		assert(t==2);
		int x=0,y=0;
		for(int i=1;i<=tot;i++){
			auto&pt=oo[i];
			int sz=pt.size();
			for(int j=0;j<sz-1;j++)b[pt[j]]=pt[j+1];
			if(!x){
				x=pt[0],y=pt[sz-1];
			}
			else{
				b[y]=pt[0];
				y=pt[sz-1];
			}
		}
		b[y]=x;
	}
	else{
		auto&pt=oo[1];int sz=pt.size();
		int xx=pt.back(),yy=pt.back(),x=pt[0],y=pt[sz-2];
		for(int i=0;i<sz-2;i++)b[pt[i]]=pt[i+1];
		for(int i=tot;oo[i].size()&1;i--){
			auto&pt=oo[i];
			int sz=pt.size();
			for(int j=0;j<sz-1;j++)b[pt[j]]=pt[j+1];
			b[y]=pt[0];
			y=pt[sz-1];
		}
		for(int i=2;i<=tot&&oo[i].size()%2==0;i++){
			auto&pt=oo[i];
			int sz=pt.size();
			for(int j=0;j<sz-2;j++)b[pt[j]]=pt[j+1];
			b[y]=pt[0],y=pt[sz-2];
			b[yy]=pt.back(),yy=pt.back();
		}
		if(t<=3){
			b[y]=xx,b[yy]=x;
		}
		else{
			assert(t==3||t==4);
			b[y]=x,b[yy]=xx;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int T;cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>p[i];

		for(int i=1;i<=n;i++)vis[i]=0;
		int mi=0,mx=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]){
				int cc=0;
				int j=i;
				while(!vis[j]){
					vis[j]=1;
					cc++;
					j=p[j];
				}
				if(cc&1){
					mi+=2;
					mx+=cc+1;
				}
				else{
					mi+=3;
					mx+=cc+1;
				}
			}

		if(k>mx||((abs(k-mi))&1)){
			cout<<"No\n";
			continue;
		}
		if(k==1){
			cout<<"No\n";
			continue;
		}
		if(k<mi){
			cout<<"Yes\n";
			for(int i=1;i<=n;i++)vis[i]=0;

			int now=0;tot=0;bool ok=0;
			for(int i=1;i<=n;i++)
				if(!vis[i]){
					vector<int>pt;
					int x=i;
					while(!vis[x]){
						pt.push_back(x);
						vis[x]=1;
						x=p[x];
					}
					if(!ok){
						++tot;
						oo[tot]=pt;
						now+=(pt.size()&1)?2:3;
						if(now-((now&1)?3:2)>=mi-k){
							ok=1;
							GG(now-(mi-k));
						}
					}
					else{
						int sz=pt.size();
						if(sz&1){
							for(int j=0;j<sz;j++){
								b[pt[j]]=pt[(j+1)%sz];
							}
						}
						else{
							for(int j=0;j<sz-1;j++){
								b[pt[j]]=pt[(j+1)%(sz-1)];
							}
							b[pt[sz-1]]=pt[sz-1];
						}
					}
				}
			assert(ok);
			for(int i=1;i<=n;i++)cout<<b[i]<<' ';cout<<'\n';
			continue;
		}
		int rest=k-mi;
		for(int i=1;i<=n;i++)vis[i]=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]){
				vector<int>pt;
				int j=i;
				while(!vis[j]){
					vis[j]=1;
					pt.push_back(j);
					j=p[j];
				}
				for(int z=pt.size();;z--){
					assert(z>=0);
					int v=0;
					if((int)pt.size()>z){
						int zz=(int)pt.size()-z;
						v=z+1+((zz&1)?1:2);
					}
					else{
						v=z+1;
					}
					v-=((pt.size()&1)?2:3);
					if(v<=rest){
						rest-=v;
						int t=pt.size()-z;
						for(int k=0;k<t;k++){
							b[pt[k]]=pt[(k+1)%t];
						}
						for(int k=t;k<(int)pt.size();k++)b[pt[k]]=pt[k];
						break;
					}
				}
			}
		cout<<"Yes\n";
		for(int i=1;i<=n;i++)cout<<b[i]<<' ';cout<<'\n';
	}
	return 0;
}
```


---

## 作者：苹果蓝17 (赞：3)

设 $k=f(x)+f(y)$。

关键性质：交换 $x_i,x_j$，也会交换 $y_i,y_j$，故 $k$ 的变化量必为 $-2,0,2$ 中的某个。

那么若 $K$ 与 $k$ 的奇偶性不同就已经无解。考虑求出 $k$ 的最大值 $mx$ 与最小值 $mn$，只要 $mn \leq K \leq mx$ 就一定有解。

> 结论：$mx=f(P)+n$，当 $x_i=i$ 时取到。  
> 证明：假设存在 $f(x)<n$ 时 $f(x)+f(y)>f(P)+n$。一定存在 $i,j$ 使得交换 $x_i,x_j$ 后 $f(x)$ 增加 $1$，那么 $f(x)+f(y)$ 单调不降。有限次调整后 $f(x)=n$，而此时 $f(x)+f(y)>f(P)+n$，矛盾。证毕。

> 结论：$mn=2$ 或 $mn=3$。 

$f(x)+f(y) \geq 2$，故显然不能更小了。下面给出一组构造算法：

- 构造两个 $n$ 个点的图，初始无边。

- 枚举每个点 $1,2,\cdots,n-2$，找一个点 $v$ 使得 $i$ 与 $v$ 在 $G$ 中不连通且 $i$ 与 $P_v$ 在 $H$ 中不连通。

    + 这样的 $v$ 一定存在。由于每个点度数不超过 $1$，故 $G$ 与 $H$ 中不能选的点都至多只有一个，那么不能选的点至多只有两个，而剩下的点至少有三个。

- 找一个点 $v$ 使得 $n-1$ 与 $v$ 在 $G$ 中不连通。能找到的原因同上。

- $x_n$ 被唯一确定。

注意到上述算法中只有 $3$ 处会增加环数，故 $f(x)+f(y) \leq 3$。

接下来考虑构造方案。

将取到 $mn$ 的 $x$ 记作 $A$，取到 $mx$ 的 $x$ 记作 $B$。

将 $A$ 通过不超过 $n-1$ 次交换变为 $B$，记这个过程中的 $x$ 分别为 $A=C_0,C_1,C_2,\cdots,C_{t-1},C_t=B$。

显然序列中任意两个相邻的 $x$ 对应的 $k$ 差不超过 $1$，于是可以类似二分求函数零点的方式找到满足条件的 $C_p$。

总时间复杂度 $O(\sum n \log n)$。

[**Code**](https://atcoder.jp/contests/agc060/submissions/37777088)



---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc060_e)

**题目大意**

> 记 $f(p)$ 表示排列 $\{p_i\}$ 形成的环数。
>
> 给定 $n$ 阶排列 $a$，构造排列 $b$ 使得 $f(b)+f(b\circ a)=k$。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

设 $c=b\circ a$，观察到交换 $b_i,b_j$ 同时也会交换 $c_i,c_j$。

因此 $f(b)+f(c)$ 的单次变化量一定是偶数（$\pm 2$ 或 $0$）。

先考虑 $f(b)+f(c)$ 的最大值：猜测在 $b_i=i$ 时取得，此时最值为 $n+f(a)$，事实上这是可以证明的：

> 假设最大值在 $f(b)<n$ 时取得，那么每次交换 $b_i,b_j$ 使得 $f(b)$ 变大，$f(b)+f(c)$ 一定不降，那么一定有一组最大值在 $b_i=i$ 时取得。

因此 $k$ 的奇偶性不同于 $n+f(a)$ 或者 $>n+f(a)$ 一定无解。

接下来考虑 $f(b)+f(c)$ 的最小值，显然理论最小值是 $2$，尝试构造：

- 对于每个 $i$，选择一个没有入度的 $j$ 使得当前 $j,i$ 在当前 $b$ 中不连通，且 $p_j,i$ 在当前 $c$ 中不连通。
- 注意到这样的操作至多导致两个 $j$ 不能选，因此对于 $1\le i\le n-2$，这样的 $j$ 总是存在。
- 对于 $i=n-1$，我们至少可以选一个 $j$ 使得 $j,i$ 在当前 $b$ 中不连通，这一步至多导致 $+1$ 个环。
- 对于 $i=n$ 至多导致 $+2$ 个环。

因此 $f(b)+f(c)$ 的最小值 $\le 3$，那么最小值为 $2/3$，根据 $n+f(a)$ 的奇偶性可以决定。

此时 $f(b)=1$，考虑每次操作令 $f(b)\gets f(b)+1$，那么 $n-1$ 步之后 $f(b)+f(c)$ 会取到最大值，且每次变化量 $\in\{0,2\}$。

设 $2\mid n+f(a)$，那么这个过程中的 $f(b)+f(c)$ 会取遍 $[2,n+f(a)]$ 中所有偶数，即 $k$ 的所有可能值。

那么我们只要在这 $n-1$ 个排列中找到一个 $b$ 满足 $f(b)+f(c)=k$。

注意到每次 $f(b)+f(c)$ 单调不降，二分操作次数判断 $f(b)+f(c)$ 与 $k$ 的关系即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,k,p[MAXN],f[MAXN],g[MAXN],tf[MAXN],tg[MAXN],q[MAXN],df[MAXN],dg[MAXN];
bool vis[MAXN];
int find(int *dsu,int x) { return x^dsu[x]?dsu[x]=find(dsu,dsu[x]):x; }
bool diff(int *dsu,int x,int y) { return find(dsu,x)^find(dsu,y); }
void merge(int *dsu,int x,int y) { dsu[find(dsu,x)]=find(dsu,y); }
int count(int *arr) {
	fill(vis+1,vis+n+1,0);
	int ans=0;
	for(int i=1;i<=n;++i) if(!vis[i]) {
		++ans;
		for(int x=i;!vis[x];x=arr[x]) vis[x]=true;
	}
	return ans;
}
void solve() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) scanf("%d",&p[i]);
	int mx=n+count(p);
	if(k>mx||k%2!=mx%2) return puts("No"),void();
	puts("Yes");
	queue <int> Q;
	for(int i=1;i<=n;++i) df[i]=i,dg[i]=i,Q.push(i);
	for(int i=1;i<n;++i) {
		while(true) {
			int x=Q.front(); Q.pop();
			if(diff(df,x,i)&&(i==n-1||diff(dg,p[x],i))) {
				f[i]=x,g[i]=p[x],merge(df,i,f[i]),merge(dg,i,g[i]); break;
			} else Q.push(x);
		}
	}
	f[n]=Q.front(),g[n]=p[f[n]];
	int l=0,r=n;
	while(l<=r) {
		int mid=(l+r)>>1;
		copy(f+1,f+n+1,tf+1),copy(g+1,g+n+1,tg+1);
		for(int i=1;i<=n;++i) q[tf[i]]=i;
		for(int i=1;i<=mid;++i) {
			tf[q[i]]=tf[i],q[tf[i]]=q[i];
			tf[i]=q[i]=i;
		}
		for(int i=1;i<=n;++i) tg[i]=p[tf[i]];
		int t=count(tf)+count(tg);
		if(t==k) {
			for(int i=1;i<=n;++i) printf("%d ",tf[i]); puts("");
			return ;
		}
		if(t>k) r=mid-1;
		else l=mid+1;
	}
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：JWRuixi (赞：1)

~~/bx/bx/bx zltqwq~~

### 题意

对于一个排列 $p$，定义 $f(p)$ 为 $p$ 的环长。给定 $n, m, \{p_n\}$：请构造排列 $\{a_n\}, \{b_n\}$ 满足 $a_i = p_{b_i}$ 且 $f(a) + f(b) = m$，或报告无解。

### 分析

首先考虑分析有解的条件。观察后注意到一个性质：交换 $a_i, a_j$，会导致交换 $b_i, b_j$，$a, b$ 中的环数 $\pm 1$。也就是说：**一次交换操作对总环数的贡献为 $+2, -2, 0$**。

由此我们断言，环数最大为 $n + f(p)$。证明：假设 $a$ 中存在环长大于 $1$ 的环，那么把它拆开一定不劣，所以可以归纳出 $a_i = i$ 一定是一个最优解，此时环数为 $n + p(n)$。

有解的充要条件就是 $m \le n + p(n)$ 且 $n + p(n) \equiv m \pmod 2$，用构造证明。

我们考虑两种减少环数的思路：

1. 通过一次交换操作使 $a, b$ 中的环数都 $-1$；
2. 通过若干次操作使得在 $a/b$ 不变的前提下 $b/a$ 的环数 $-2$。

对于思路一，因为 $a_i = i$，所以可以将 $b$ 中的环依次合并，显然符合条件。我们最终可以将 $b$ 合并为一个环，而 $a$ 组成若干个环。

考虑思路二，我们考虑分为两步，先破坏 $b$ 形成的环，再重新连接上，每一次操作都合并一个 $a$ 中的环。

具体的：我们希望找到 $i \to b_i$，且 $i$ 和 $b_i$ 在 $a$ 中属于不同的环。交换 $i, b_i$ 会在 $b_i$ 处形成一个自环，于是我们希望找到 $k$ 满足 $b_i$ 和 $k$ 在 $a$ 中属于不同的环，在交换 $b_i$ 和 $k$。

实现使用并查集，维护每一个 $a$ 中的环，在维护一个集合 $S$ 记录可能满足 $i$ 和 $b_i$ 属于不同环的 $i$。每次操作后将 $b_i$ 和 $k$ 都加入 $S$，实际上我们只需要考虑两个环就一定能找到一个 $k$，所以两者均可以栈或队列维护。

复杂度 $\mathcal O(n \alpha(n))$。

### Code

提交记录：<https://atcoder.jp/contests/agc060/submissions/50720000>。

---

## 作者：EuphoricStar (赞：0)

讲个笑话，一年前做过，今天模拟赛出了，但是完全不记得，然后想了一种完全不同的方法，我真抽象。

首先考虑什么时候有解。显然 $m = n + f(a)$ 的时候有解，令 $b_i = i, c_i = a_i$ 即可。然后考虑任意交换一对 $(i, j)$，此时 $(b_i, b_j), (c_i, c_j)$ 都会被交换。所以 $f(b), f(c)$ 的变化量均为 $\pm 1$。所以 $f(b) + f(c)$ 的奇偶性确定，若 $m$ 和 $n + f(a)$ 的奇偶性不同就无解。

然后发现 $m \le n + f(a)$ 时才可能有解。考虑 $b_i = i, c_i = a_i$ 的情形，显然交换任意一对后 $f(b)$ 都会 $-1$，所以交换后一定不优。

然后发现这两个条件是充要条件，下面考虑构造性证明。

先构造出 $f(b) + f(c) = n + f(a)$ 的方案，也就是 $b_i = i, c_i = a_i$。考虑先从 $c$ 入手，以任意顺序扫 $c$ 的连通块，并且与上一个连通块合并，也就是任意交换这个连通块和上一个连通块的一对元素即可。显然它们在 $b$ 中属于的连通块也不同。所以 $f(b), f(c)$ 经过这样的一次操作后都会 $-1$，所以 $f(b) + f(c)$ 经过这样一次操作后会 $-2$。

扫完之后 $f(c) = 1$，但是 $f(b)$ 可能 $> 1$。我们希望当 $f(b) > 2$ 时让 $f(b)$ 减小 $2$，同时保持 $f(c) = 1$。

不妨考虑找到一个 $i$ 使得 $(i, c_i)$ 在 $b$ 中不在同一个连通块（容易发现一定能找到，因为不能找到就说明 $f(b) = 1$，可以直接退出）。此时可以直接交换 $(i, c_i)$，这样 $f(b)$ 会 $-1$，但是 $f(c)$ 会 $+1$。

我们发现一个非常好的事情，就是 $c_i$ 在 $c$ 中变成了一个自环，同时所有其他的点组成了一个环。也就是说我们让 $c_i$ 和任意一个其他点交换，$f(c)$ 都会变回 $1$。那么就让 $c_i$ 和任意一个在 $b$ 中和它不在同一个连通块的点 $j$ 交换，这样 $f(b)$ 会 $-1$。

所以经过上面的过程，$f(b) + f(c)$ 会 $-2$。

考虑快速维护这个构造的过程。可以使用一个类似栈的东西维护全部 $(i, c_i)$ **可能**在 $b$ 中在同一个连通块的点 $i$。找的时候直接取栈顶，在一个连通块就弹出。交换一对 $(i, j)$ 就把 $i, j$ 都加入栈即可。

然后对一个点 $x$ 找在 $b$ 中和它不在一个连通块的任意一个点，可以维护任意两个连通块的祖先，其中必然有一个不是 $x$ 的祖先。

所以时间复杂度就是 $O(n \log n)$，$\log n$ 是并查集复杂度，可以粗略地看成线性。实际跑得很快。

[code](https://atcoder.jp/contests/agc060/submissions/50720032)

---

