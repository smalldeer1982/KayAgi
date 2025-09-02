# DIY Garland

## 题目描述

Polycarp has decided to decorate his room because the New Year is soon. One of the main decorations that Polycarp will install is the garland he is going to solder himself.

Simple garlands consisting of several lamps connected by one wire are too boring for Polycarp. He is going to solder a garland consisting of $ n $ lamps and $ n - 1 $ wires. Exactly one lamp will be connected to power grid, and power will be transmitted from it to other lamps by the wires. Each wire connectes exactly two lamps; one lamp is called the main lamp for this wire (the one that gets power from some other wire and transmits it to this wire), the other one is called the auxiliary lamp (the one that gets power from this wire). Obviously, each lamp has at most one wire that brings power to it (and this lamp is the auxiliary lamp for this wire, and the main lamp for all other wires connected directly to it).

Each lamp has a brightness value associated with it, the $ i $ -th lamp has brightness $ 2^i $ . We define the importance of the wire as the sum of brightness values over all lamps that become disconnected from the grid if the wire is cut (and all other wires are still working).

Polycarp has drawn the scheme of the garland he wants to make (the scheme depicts all $ n $ lamp and $ n - 1 $ wires, and the lamp that will be connected directly to the grid is marked; the wires are placed in such a way that the power can be transmitted to each lamp). After that, Polycarp calculated the importance of each wire, enumerated them from $ 1 $ to $ n - 1 $ in descending order of their importance, and then wrote the index of the main lamp for each wire (in the order from the first wire to the last one).

The following day Polycarp bought all required components of the garland and decided to solder it — but he could not find the scheme. Fortunately, Polycarp found the list of indices of main lamps for all wires. Can you help him restore the original scheme?

## 说明/提示

The scheme for the first example (R denotes the lamp connected to the grid, the numbers on wires are their importance values):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1283F/6254ca5cb4bc3113998afdb1162625eae0ea8d75.png)

## 样例 #1

### 输入

```
6
3 6 3 1 5
```

### 输出

```
3
6 3
6 5
1 3
1 4
5 2
```

# 题解

## 作者：Midoria7 (赞：15)

震惊，感觉题解里写的都挺多的，但是感觉这个方法就随随便便~~水~~过去了

首先，不可能去存 $2^i$，因为 $n\leq 2\times10^5$。实际上这个就是唬人的。但是贪心是错误的。

显然，第一个输入的一定是根节点。然后我们发现有一个性质是，越后第一次出现的点深度一定更深。而没有出现的点就一定是叶子节点了。所以我们读入时，记一下每一个点的出现个数，可以理解为入度。没有出现过的，即是叶子节点，我们把他们扔进一个小根堆里。

然后我们考虑配对。我们又发现，一个数的出现次数一定是他的儿子个数，那我们就好连边了。从后往前遍历 $a$ 数组，每一个数和堆顶连边，同时该点 $degin[a[i]]--$。如果 $degin[a[i]]$ 为零了，就加入堆里。这样循环 $n-1$ 次，即可构造出一组解。这样一定是从下到上连边的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,root;
int a[maxn],degin[maxn];

inline int read(){
	int x=0;bool fopt=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')fopt=0;
	for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+ch-48;
	return fopt?x:-x;
}

priority_queue<int,vector<int>,greater<int> > q;
int main(){
	n=read();
	for(int i=1;i<n;i++){
		a[i]=read();
		degin[a[i]]++;
	}
	printf("%d\n",a[1]);
	for(int i=1;i<=n;i++)
		if(!degin[i])q.push(i);
	for(int i=n-1;i>=1;i--){
		int v=q.top();q.pop();
		printf("%d %d\n",a[i],v);
		degin[a[i]]--;
		if(degin[a[i]]==0)q.push(a[i]);
	}
	return 0;
}
```

---

## 作者：Rhodoks (赞：4)

出题人题解咕掉了，照着代码理解了一下写写个人的看法。


$used[i]$代表目前$i$号节点的父亲是否确定，$a[i]$是第$i$条边的主灯（父亲节点）。

算法的思想大致是这样：按照给出边的顺序遍历，$i$为边序号。如果$i<n$且第$i+1$条边的父亲未定，则连接$a[i]$与$a[i+1]$。否则连接$a[i]$和$cur$，后者为当前未确定父亲的编号最大的节点。

这样，每次连接第$i$条边时，$a[i]$的父亲都是已经确定的（$a[1]$是根节点例外）。这意味着，满足$used[i]=1$的点$i$不可能对之后的边的重要性产生贡献。

设第$i$条边的重要性是$d_i$。

如果$a[i]$连接了$cur$，因为$cur$是当前$used[i]=0$的编号最大节点，之后的边的子树中的节点编号必然小于$cur$。$2^i>2^{i-1}+2^{i-2}+...+2^1+2^0$。所以$d_i>d_j (j>i)$，特殊地，$d_i>d_{i+1}$。

如果$a[i]$连接了$a[i+1]$,那么$a[i]$是$a[i+1]$的父亲，显然$d_i>d_{i+1}$。

综上所述$d_1>d_2>...>d_{n-1}>d_n$

对于所有合法数据均能构造出这样的解，不需要考虑无解情况。

code：
```cpp
#include <bits/stdc++.h>
#define MAXN 210000
#define _ 0
using namespace std;

int n;
int a[MAXN];
int used[MAXN];

int main()
{
	int n;
	cin>>n;
	int cur=n;
	n--;
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	cout<<a[1]<<endl;
	used[a[1]]=1;
	for (int i=1;i<=n;i++)
	{
		while (used[cur])
			cur--;
		if (used[a[i+1]] || i==n)
		{
			cout<<a[i]<<' '<<cur<<endl;
			used[cur]=1;
		}
		else
		{
			cout<<a[i]<<' '<<a[i+1]<<endl;
			used[a[i+1]]=1;
		}
	}
	return ~~(0^_^0);
}


```

---

## 作者：Corzica (赞：2)

观察样例，因为幂次的特殊性质，打印边的顺序是根到 $n,n-1,n-2,\dots$ 的链。

显然，第一个数一定是根。

依次扫描这个序列，并同时记录当前的目标的点，当前打印的就是根到目标的链。考虑什么时候会更改目标，一是目标已经出现了，自然要更改。二是突然跳到了一个已经确定了父亲的点，说明目标点的链打印完毕，直接把目标点和上一个序列中点连起来就行。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[200005], m, vis[200005], fa[200005], now;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> a[i];
	}
	m = a[1];
	now = n;
	vis[m] = 1;
	if (m == n) now--;
	for (int i = 2; i < n; i++) {
		if (vis[a[i]]) {
			fa[now] = a[i - 1];
			vis[now] = 1;
			now--;
			while (vis[now]) now--;
		} else {
			vis[a[i]] = 1;
			fa[a[i]] = a[i - 1];
			while (vis[now]) now--;
		}
		if (i == n - 1) {
			fa[now] = a[i];
		}
	}
	cout << m << "\n";
	for (int i = 1; i <= n; i++) {
		if (fa[i]) cout << i << " " << fa[i] << "\n";
	}
}
```

---

## 作者：ChrysanthBlossom (赞：2)

提供一个似乎题解区里面没有的思路（但是代码实现和第二篇差距不太大）。

首先思考一下为什么是 $2^i$，为什么不是类似 $val_i$ 或 $2^{val_i}$ 的东西。显然 $\sum2^i$ 就相当于把子树内的点进行状压，而如果一个子树的最大值比另一个子树的最大值大，那么他的权值必然比另一个子树的权值大；如果这两棵子树最大值相同，由于能被一个最大值作用到的点会构成一条到根的链，因此此时两棵子树必然构成祖先关系，深度越小的显然权值就更大了。由此，按权值和排序显然等价于以最大值为第一关键字以深度的相反数为第二关键字从大到小排序。

于是，$a$ 数组一定是若干个最大值为 $n$ 的子树的父亲，接上若干个最大值为 $n-1$ 的子树的父亲，再接上若干个最大值为 $n-2$ 的子树的父亲……不断接下去。并且最大值相同的子树一定构成一条从根开始的链。于是可以设一个虚拟的根 0 号点，然后给他挂上个初始的最大值 $n$，接着不断地往当前点与最大值之间插点，就可以求完一个最大值的所有祖先。

考虑什么时候需要更换最大值，显然当你换子树的时候最大值会发生变化，当前子树的父亲是当前最大值时最大值也会变化，这两种情况下 $a_i$ 都被访问过了，处理的话跳过去换最大值就行了（如果不太能看懂的话可以看代码）。

时间复杂度 $O(n)$，代码实现感觉也不错（

```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
#define mkp make_pair
using namespace std;
const int maxn=2e5+7;
int n;
int a[maxn];
bool vis[maxn];
vector<pair<int,int> >edge;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(ri i=1;i<n;i++)cin>>a[i];
	vis[n]=1;
	int now_cur=n;
	int now_point=0;
	edge.emplace_back(mkp(now_point,n));
	for(ri i=1;i<n;i++){
		edge.pop_back();
		edge.emplace_back(mkp(now_point,a[i]));
		if(vis[a[i]]){
			edge.pop_back();
			edge.emplace_back(mkp(now_point,now_cur));
			while(vis[now_cur])now_cur--;
			vis[now_cur]=1;
		}
		now_point=a[i];
		vis[a[i]]=1;
		edge.emplace_back(mkp(a[i],now_cur));
	}
	cout<<edge[0].second<<endl;
	for(ri i=1;i<edge.size();i++){
		cout<<edge[i].first<<' '<<edge[i].second<<endl;
	}
	return 0;
}
```

---

## 作者：caidzh (赞：2)

## 吐槽一下

$2400$难度的傻逼题

~~思考时间远短于这场的E，学傻了学傻了~~

## $\text{Solution}$

首先我们发现一条边的权值就是其连接的子节点的子树内节点的权值和

不妨直接用子树根来表示子树权值和，注意到一个优秀的性质：子树根的权一定大于子树内任意节点的权，因此根向上连的边一定比子树内的边排名靠前

顺着思考，排名最靠后的边一定使得一个叶子节点被连上，如果一个子树被完全确定，那么这个子树的根相当于一个叶子结点

因此解法便呼之欲出了：我们记录一个点有几个直接相连的儿子，如果这个点没有儿子，则将其扔进小根堆（存点的编号+权）里，每次连边的时候，取出堆顶，然后连向其父亲，用类似拓扑排序的方式更新父亲有几个儿子即可

问题在于：点的权怎么维护，因为这个权非常大，不容易维护

注意到所有点的权都不同，且都是$2^i$，由于二进制中高位决定一切，我们直接记录子树中最大的点的编号就可以完美解决这个问题

无解情况乱判即可
```cpp
#include<bits/stdc++.h>
const int maxn=200010;
int n,a[maxn],deg[maxn],pos[maxn],to[maxn],val[maxn];
struct Node{
	int x,val;
	bool operator <(const Node x)const{return x.val<val;}
};priority_queue<Node>que;
int main()
{
	scanf("%d",&n);for(int i=1;i<n;i++)scanf("%d",&a[i]),deg[a[i]]++;for(int i=1;i<=n;i++)val[i]=i;
	for(int i=1;i<=n;i++)if(!deg[i]){Node x;x.x=i;x.val=val[i];que.push(x);}
	for(int i=n-1;i>=1;i--){
		if(que.size()==0){cout<<-1;return 0;}
		Node x=que.top();int u=x.x;val[a[i]]=max(val[a[i]],val[u]);
		que.pop();pos[i]=u;to[i]=a[i];deg[a[i]]--;
		if(!deg[a[i]]){Node v;v.val=val[a[i]];v.x=a[i];que.push(v);}
	}if(que.size()>1){cout<<-1;return 0;}
    cout<<a[1]<<endl;
    for(int i=1;i<n;i++)cout<<pos[i]<<" "<<to[i]<<endl;return 0;
}
```


---

## 作者：cmll02 (赞：0)

考虑每次选的点，必然包含了没选的点中最大的那个。

并且它的父节点已经被选了。

根节点显然是 $a_1$。

那么你考虑依次加点。

如果当前点是

- 新出现的点，且不等于最大值，那么最大值仍然在它的子树中，从而它是上一个点的子节点。

- 新出现的点，且等于最大值，那么它是上一个点的子节点，同时更新剩下的最大值，这个新的最大值在其子树内。

- 出现过的点。这说明最大值是上一个点的子节点，新的最大值在新的节点的子树内。

按照这个东西模拟即可。

[code link](https://codeforces.com/contest/1283/submission/135730730)

---

## 作者：Vector_Mingfan (赞：0)

[**题目由此去-luogu**](https://www.luogu.com.cn/problem/CF1283F)

[**题目由此去2-CF**](https://codeforces.com/problemset/problem/1283/F)

[**博客园食用更加**](https://www.cnblogs.com/VectorCy/p/15377739.html)


------------
**题目大意**：有 $ n $ 个点，第 $ i $ 个点的权值为 $ i^2 $ ，现在有 $ n-1 $ 条边使得这些点组成一棵树，边的权值是它连接的子树的权值和。现在按照边的权值从大到小给你每条边的父节点，让你输出根节点的下标以及输出输入顺序每条边所连接的两个点。

**思路**：

- 自底向上很简单，首先我们处理出所有未出现过的点是什么，然后最后一条边连接的一定是最小的那个点。

- 有了这个思路我们就可以很容易的想到如果我们从后往前做，那么当前的点连接的一定是可供选择的点中的子树的值最小的那个。

- 由于每个点的值是 $ 2 $ 的幂次，于是我们只需要记录当前点子树中最大的点的值是什么即可。

- 那么什么是可供选择的点？首先可供选择的点一定是未在输入中出现过的点，然后如果当前点还在前面的输入中出现过，那么就证明这个点还连着值更大的儿子，那么这个点就不能被判为可供选择的点。

------------
**code**：

```cpp
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define fst first
#define snd second
using namespace std; 
const int N = 2e5 + 5;
struct node {
	int id, mx;
	bool operator< (const node& a)const {return mx > a.mx;}
};
priority_queue<node> q;
int n, a[N], vis[N];
pii  ans[N];

int main() {
	scanf("%d", &n);
	for (int i=1; i<n; i++) {
		scanf("%d", &a[i]);
		vis[a[i]]++ ;
	}
	for (int i=1; i<=n; i++) {
		if (!vis[i]) q.push({i, i});
	}
	for (int i=n-1; i; i--) {
		node now = q.top();
		q.pop();
		ans[i] = {a[i], now.id};
		vis[a[i]]-- ;
		if (a[i] != a[1] && !vis[a[i]]) q.push({a[i], max(now.mx, a[i])});
	}
	printf("%d\n", a[1]);
	for (int i=1; i<n; i++) {
		printf("%d %d\n", ans[i].fst, ans[i].snd);
	}
	return 0;
}
```


---

## 作者：demonlover923 (赞：0)

一开始想歪来了,想着每次找到一条边，然后在总量里面删去它的贡献，后来发现数据范围不对劲$n \in [1,200000]$，极限的时候$2^n$啥玩意都存不下.

换个方向，先确定根，很显然，根据题意，是$a_1$.

接着我们发现，他给的$a$是一条边中的父亲节点，也就是说会有一些点的编号不会在$a$中出现，接着考虑是什么点不会出现，冷静思考发现是叶子节点.

然后我们就顺着这个思路，找到叶子节点，输出边，再删掉这条边，类似一个拓扑的过程.

考虑什么样的删除顺序会好处理，边权和点权的定义启发了我们，点编号最小的叶子节点对应的边，是最小的.

接下来模拟过程就好了，倒序处理很是方便.


```cpp
/***************************************
*Author        :  demonlover
*Created Time  :  2020.11.28.10:09
*Problem       :  CF1283F
************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair <int,int> pii;
template <typename T>
inline void read(T &x) {
	int f = 0,c = getchar();x = 0;
	while (!isdigit(c))f |= c == 45,c = getchar();
	while (isdigit(c))x = (x<<3)+(x<<1)+(c^48),c = getchar();
	if (f)x = -x;
}
template <typename T,typename... Args>
	inline void read(T &x,Args &...args) {
	read(x);read(args...);
}

namespace run {
	const int maxn = 2e5+10;
	priority_queue< int > q;
	int a[maxn],ind[maxn];
	int n;
	inline int main() {
		read(n);
		for (register int i = 1;i < n;++i)
			read(a[i]),++ind[a[i]];
		printf("%d\n",a[1]);
		for (register int i = 1;i <= n;++i)
			if (!ind[i])
				q.push(-i);
		for (register int i = n-1;i >= 1;--i) {
			int x = -q.top();q.pop();
			printf("%d %d\n",a[i],x);
			--ind[a[i]];
			if (!ind[a[i]])q.push(-a[i]);
		}
		cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
		return 0;
	}
}
int main() {
	freopen("CF1283F.in","r",stdin);
	freopen("CF1283F.out","w",stdout);
	return run :: main();
}
```

---

