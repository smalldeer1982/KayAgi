# 2+ doors

## 题目描述

Narrator 有一个长度为 $n$ 的数组 $a$，但是他会仅告诉你 $n$ 和 $q$ 条信息，每条信息都包含三个数字 $i,j,x$，代表 $a_i \mid a_j = x$，其中 $|$ 是[二进制按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

请找出字典序最小的数组 $a$ 满足这些条件。

一个数组 $a$ 在字典序意义下比一个数组 $b$ 小，当且仅当满足如下条件：

- 在 $a$ 中第一个和 $b$ 元素不同的位置中，$a$ 的元素比 $b$ 中对应位置的元素小。

## 说明/提示

在样例 $1$ 中，以下这些数组满足所有条件：

- $ [0, 3, 2, 2] $，
- $ [2, 1, 0, 0] $，
- $ [2, 1, 0, 2] $，
- $ [2, 1, 2, 0] $，
- $ [2, 1, 2, 2] $，
- $ [2, 3, 0, 0] $，
- $ [2, 3, 0, 2] $，
- $ [2, 3, 2, 0] $，
- $ [2, 3, 2, 2] $。

## 样例 #1

### 输入

```
4 3
1 2 3
1 3 2
4 1 2```

### 输出

```
0 3 2 2```

## 样例 #2

### 输入

```
1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
2 1
1 1 1073741823```

### 输出

```
1073741823 0```

# 题解

## 作者：liangbowen (赞：30)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1715D)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1715d)

感觉挺不错的一道图论转化题。（其实也和图论关系不大。）

## 思路

对于每个条件 $a_u \mid a_v = x$，二进制拆掉 $x$。如果 $x$ 的二进制位 $j$ 是 $1$，说明 $a_u$ 和 $a_v$ 中，当前位也肯定有至少一个为 $1$。标记一下 $f_{u, j} = f_{v, j} = 1$。

由于字典序最小，所以我们尽量只让 $a_{\max(u, v)}$ 的对应二进制位为 $1$，这样可以使得 $a_{\min(u, v)}$ 小一些。

由于要表示出点与点之间的关系，我们尝试**建图**。对每一个条件建图：连一条 $u$ 与 $v$ 间，边权为 $x$ 的双向边。

然后，枚举每一位二进制位 $j$，以及每一个点。对于每一个点，看与之相连的其他所有点（仍然是记为 $u$, $v$, $x$）。

我们现在是看 $a_u$ 的第 $j$ 位（指的是二进制下。之后同理），要不要变成 $1$。

如果 $x$ 的第 $j$ 位是 $0$，就跳过。否则，看 $u$ 与 $v$ 的大小关系。

+ 如果 $u < v$，那么如果 $f_v$ 的第 $j$ 位没有被标记过，$a_u$ 的第 $j$ 位才必须为 $1$。否则应该让 $a_v$ 为 $1$，这样 $u$ 就能小一些了。
+ 如果 $u > v$，那么看当前 $a_v$ 的结果。如果 $a_v$ 的第 $j$ 位为 $0$，那 $a_u$ 的第 $j$ 位才必须为 $1$。

你可能会问，$u = v$ 怎么办？显然 $a_u \mid a_u = x$，直接表明了 $a_u = x$。因此在第一步时，就能特判掉 $u = v$ 的情况，避免自环。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#define space putchar(' ')
#define endl putchar('\n')
using namespace std;
int read()
{
	char op = getchar(); int x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(LL x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
const int N = 1e5 + 5, M = 2e5 + 5;
struct Edge
{
	int now, nxt, w;
}e[M << 1]; //这里空间要开足！赛时调了好久。 
int head[N], cur;
void add(int u, int v, int w)
{
	e[++cur].now = v;
	e[cur].nxt = head[u];
	e[cur].w = w;
	head[u] = cur;
}
bool bit(int x, int j) {return x & (1 << (j - 1));} //x 的第 j 位 
bool flag[N][35]; //flag[i][j]表示a[i]的第j位是否有可能为1
int a[N];
bool calc(int u, int j)
{
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now, x = e[i].w;
		if (!bit(x, j)) continue;
		if (u < v) {if (flag[v][j]) return true;}
		else {if (!bit(a[v], j)) return true;}
	}
	return false;
}
int main()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int u = read(), v = read(), x = read();
		for (int j = 1; j <= 30; j++)
			if (!bit(x, j))
				flag[u][j] = flag[v][j] = true;
		if (u == v) {a[u] = x; continue;} //特判，避免加边时造成自环 
		add(u, v, x), add(v, u, x);
	}
	for (int j = 1; j <= 30; j++)
		for (int i = 1; i <= n; i++)
			if (calc(i, j))
				a[i] |= (1 << (j-1));
	for (int i = 1; i <= n; i++) write(a[i]), space;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：幸存者 (赞：12)

首次场切 CF Div.2 D，来提供一种比较好写的做法。
## 思路
先求出数组 $a$ 中每个数的最大可能值存入数组 $a$，再通过每个数的最大可能值计算出字典序最小的数组 $a$。

显然第 $i$ 个数的最大可能值就是所有与 $i$ 有关的要求中的 $x$ 之间按位与得到的结果。

更简洁的表述方式：若要求 $a_i\mid a_j=x$，只需要令 $a_i=a_i\ \&\ x,a_j=a_j\ \&\ x$ 即可。

需要注意的是，数组 $a$ 的初值应设为 $2^{30}-1$。

那么如何求出字典序最小的数组 $a$ 呢？我们根据按位或运算的性质（在已知 $x,z$ 的条件下，若 $x\mid y=z$，则 $y$ 的最小值为 $z-x$），通过最大推导最小即可。

算的时候从 $i=1$ 开始在 $a_1,a_2,\cdots,a_{i-1}$ 都已经确定的情况下，先令 $a_i=0$。若要求 $a_i\mid a_j=x$，则将 $a_i$ 的值修改为 $a_i\mid(x-a_j)$ 即可。

需要注意的是，有可能存在 $i=j$ 的情况，此时直接将 $a_i$ 的值修改为 $a_i\mid x$ 即可。
## $\text{AC Code}$ 
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010];
vector<int> v[100010], w[100010];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) a[i] = (1 << 30) - 1;
    while (m--)
    {
        int i, j, x;
        cin >> i >> j >> x;
        a[i] &= x;
        a[j] &= x;
        v[i].push_back(j);
        v[j].push_back(i);
        w[i].push_back(x);
        w[j].push_back(x);
    }
    for (int i = 1; i <= n; i++)
    {
        a[i] = 0;
        for (int j = 0; j < v[i].size(); j++) 
        {
            if (i != v[i][j]) a[i] |= w[i][j] - a[v[i][j]];
            else a[i] |= w[i][j];
        }
        cout << a[i] << " ";
    }
    return 0;
}
```

---

## 作者：Qzong (赞：6)

# 简要题意
对于一个数组 $a$，给定 $Q$ 个限制条件，每个条件给出 $i,j,x$ 使得 $a_i|a_j=x$。

构造数组使其字典序最小。

# Solution
以下 $ans_i$ 表示最后我们构造出来的答案数组。

考虑一个最宽松的限制条件，我们有一个 $b$ 数组，在最开始，$b$ 在二进制意义下全是 $1$。


对于每个条件，我们令 $b_i=b_i\&x,b_j=b_j\&x$。

显然，$b$ 数组是答案最宽松的条件，即 $ans_i\subseteq b_i$。

也就是说，若一定存在解，则 $b_i$ 必然是一组合法解。

现在要求字典序最小，我们从前往后构造答案。

考虑当前构造位 $i$。

为了让字典序最小，对于一个限制 $\{a_i|a_j=x,(i<j)\}$，我们应尽可能的让 $ans_j$ 完成要求，$ans_j$ 能完成的部分即为 $x\&b_j$。

剩余的部分，即 $(x$ $^$ $(x\&b_j))$，则不得不让 $ans_i$ 来完成，于是 $ans_i$ 必须或上这一部分。

但是注意，$ans_j$ 并不是一定要完成 $x\&b_j$。

因为 $ans_i$ 也有可能在其他条件的~~迫害~~下不得不完成了一部分 $x$。

于是我们对于 $\{a_i|a_j=x,(i>j)\}$，再让 $ans_i|=(x\&ans_i)$ 来完成剩余的限制即可。

~~由于每一步都是必要的，所以他是最小的。~~

至于 $\{a_i|a_j=x,(i=j)\}$，则 $ans_i=x$ 是必然的。

复杂度 $O(n+q)$。

```cpp
#include<bits/stdc++.h>
#include<vector>
const int N=200010;
int a[N],b[N],ans[N];
struct node{
	int to,val;
};
std::vector<node>p[N];
signed main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)a[i]=(1<<30)-1;
	int x,y,z;
	for(int i=1;i<=q;i++){	
		scanf("%d%d%d",&x,&y,&z);
		a[x]=z&a[x],a[y]=z&a[y];
		p[x].push_back(node{y,z}),p[y].push_back(node{x,z});
	}
	for(int i=1;i<=n;i++){
		for(node j:p[i]){
			if(i==j.to)ans[i]|=j.val;
			else if(j.to>=i){
				ans[i]|=((j.val^(j.val&a[j.to]))&a[i]);
			}
			else {
				ans[i]|=((j.val^(j.val&ans[j.to]))&a[i]);
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Dregen_Yor (赞：5)

[博客食用效果更佳](https://www.cnblogs.com/Dregen-Yor/p/16613000.html)。

~~个人认为这道 D 比 C 要简单~~。

# 思路

~~位运算的知识太简单这里就不提了。~~

因为题目中每个条件限制为 $ a_i \mid a_j = x $，并且题目中还提到 $x<2^{30}$，我们考虑将 $x$ 转换成二进制的方式表示，枚举 $x$ 的每一位，若枚举到的当前位置上为 $0$，则 $a_i$ 和 $a_j$ 上的该位不能赋值成 $1$，用数组标记一下。

对于每一个关系，我们可以以图的形式来表示，每一个 $ a_i \mid a_j = x $ 的关系，可以在 $i$ 和 $j$ 中间连一条权值为 $x$ 的边。在遍历的时候，对于每一条边，为了保证字典序最小，我们可以尽可能地让 $i$ 和 $j$ 中较大的一位尽可能地和 $x$ 的每一位相等，同时只让 $a_i$ 和 $a_j$ 其中一个满足当前位上为 $1$ 即可。

我们可以枚举二进制的每一位，枚举每一位时，枚举每个点和当前的点相连的边，若相连的点的下标比当前的小且边权中包含这一位，同时相连的点的答案中不包含这一位，就将当前点的答案的这一位变成 $1$，如果相连的点的下标比当前的大且边权中包含这一位，若相连的点的**这一位被标记**，将当前点的答案的这一位变为 $1$。

最终输出答案即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
	int to, k;
};
vector <node> G[100010];
int n, m, v[100010][31], ans[100010];

int main() {
	scanf("%d%d", &n, &m);
	memset(ans, 0, sizeof(ans));

	for (int i = 1; i <= m; i++) {

		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);

		for (int j = 0; j < 30; j++) {

			if (k & (1 << j)) {
				continue;
			}

			v[x][j] = v[y][j] = 1;
		}

		if (x == y) {
			ans[x] |= k;
			continue;
		}

		G[x].push_back(node{y, k});
		G[y].push_back(node{x, k});
	}

	for (int x = 29; x >= 0; x--) {

		for (int i = 1; i <= n; ++i) {

			bool f = 0;

			for (int j = 0; j < G[i].size(); j++) {

				int to = G[i][j].to, k = G[i][j].k;

				if (to < i) {
					if (k & (1 << x)) {
						if (ans[to] & (1 << x)) {
							continue;
						}

						f = 1;
						break;
					}
				} else {
					if (k & (1 << x)) {
						if (v[to][x]) {
							f = 1;
							break;
						}
					}
				}
			}

			if (f)
				ans[i] |= (1 << x);
		}
	}

	for (int i = 1; i <= n; i++) {

		printf("%d ", ans[i]);
	}

	return 0;
}


```


---

## 作者：ExplodingKonjac (赞：3)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1715D)**

最开始以为 2-Sat 板子，但是后来发现甚至不用 2-Sat，而且用了似乎还不太方便处理最小化字典序（

## 题目分析

位运算不同位互不干扰，那么就先拆位，这样只用处理 $0$ 和 $1$。

对于一些限制，我们可以判断出某些位置的值是确定的：$a_x\operatorname{or}a_x=y$、$a_x\operatorname{or}a_y=0$。给确定的位置打上标记。去掉这些限制后，剩下的限制就是说“$x$ 和 $y$ 中至少一个 $1$”，且有 $x\neq y$。对于一个限制 $x,y$，不妨设 $x<y$，把 $y$ 挂在 $x$ 上。

因为要字典序最小化，所以我们从左往右贪心。如果当前位置有标记了，直接跳过。否则，如果挂在这里的位置中存在已经确定为 $0$ 的，那么这里非选 $1$ 不可。再不然，当前位置可以随便定，那么就选 $0$，并且把挂在这里的位置修改为 $1$ 并打上标记。

题目保证一定有解，不难发现这样必然能够构造出来。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int n,m,a[100005];
vector<int> g[100005];
bool chk[100005];
struct Limit{ int x,y,z; }q[200005];
int main()
{
	qin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		qin>>q[i].x>>q[i].y>>q[i].z;
		if(q[i].x>q[i].y) swap(q[i].x,q[i].y);
	}
	for(int j=0;j<30;j++)
	{
		for(int i=1;i<=n;i++)
			chk[i]=false,g[i].clear();
		for(int i=1;i<=m;i++)
		{
			int x=q[i].x,y=q[i].y;
			bool v=q[i].z&(1<<j);
			if(x==y) a[x]|=v<<j,chk[x]=true;
			else if(v) g[x].push_back(y);
			else chk[x]=chk[y]=true;
		}
		for(int i=1;i<=n;i++)
		{
			bool fl=false;
			for(auto &k: g[i]) fl|=(!(a[k]&(1<<j)) && chk[k]);
			if(fl || (a[i]&(1<<j))) a[i]|=1<<j;
			else for(auto &k: g[i]) a[k]|=1<<j,chk[k]=true;
		}
	}
	for(int i=1;i<=n;i++)
		qout.writesp(a[i]);
	return 0;
}
```


---

## 作者：__qhd (赞：1)

#### 简要题意
构造长度为$n$的数组满足$q$个形如$a_i|a_j=x$的条件,要求字典序最小,保证有解。
#### 思路
按位或操作 $1|1=1 , 0|1=1 , 1|0=0 , 0|0=0$，即一个数二进制存在一位是$1$后，无论如何按位或，该$1$无法消失。

所以我们考虑与$a_i$有关的每个数二进制位上哪一位是$1$，当且仅当所有与$a_i$有关的$x$该位都为$1$时,$a_i$该位才能取$1$。即将所有与$a_i$有关的$x$按位与,得到 $t$ , $ t = x_1 $&$ x_2$&$x_3··· $（这里$x$指与$a_i$相关的所有$x$）。当$t|a_i=t$时$a_i$取值合法。因为保证有解，所以当每个$a_i$都取得和他相关的$t$时，序列合法。将此序列记录下来为$a$序列。在操作同时，开一个vector记录一下与$a_i$有关的所有位置(当i=j时不记录并进行一个特判)。

现在我们考虑如何求字典序最小的序列，从左向右遍历序列，当遍历到第$i$个时，遍历与该位置有关的其他位置，并将这些位置上的数$a_j$与起来，将最终的结果$p$与$a_i$与一下，若$p\neq0$则 $a_i = a_i-p$ 。当遇到条件为$a_i|a_i=x$的位置时，直接跳过。显然，在此操作后得到的序列字典序最小。

复杂度$O(n+q)$.

#### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template<class T>
void read(T &x){
	x = 0;
	char c=getchar();
	bool t=false;
	while(c<'0'||c>'9'){if(c=='-')t=true;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x = x*(t?-1:1);
}
const int N = 2e5+10;
int l,r;
ll x;
int n,q;
vector<int> str[N];
ll t[N],vis[N],a[N];
bool flg[N];
int main(){
	read(n);read(q);
	for(int i=1;i<=q;i++){
		read(l);read(r);read(x);
		if(l==r){
			t[l] = x;
			flg[l] = 1;
			a[l] = x;
			continue;
		}
		str[l].push_back(r);
		str[r].push_back(l);
		if(!vis[l]){
			t[l] = x;
			vis[l] = 1;
		}
		else{
			t[l] = t[l]&x;	
		}
		if(!vis[r]){
			t[r] = x;
			vis[r] = 1;
		}
		else{
			t[r] = t[r]&x;	
		} 		
	} //满足(a[i]|t[i])==t[i] 
	//t[i]二进制为1的位置能放 
	for(int i=1;i<=n;i++){
		if(flg[i])t[i] = a[i];
	}
//	if(n>10000)cout<<t[43952]<<" "<<t[35625]<<" ";
	for(int i=1;i<=n;i++){
		ll p = t[i];
		if(flg[i])continue;
		for(int j=0;j<str[i].size();j++){
			int dis = str[i][j];
			p = p&t[dis];
		}
		if(str[i].size())t[i]-=p;
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",t[i]);
	}
	return 0;
}
```



---

## 作者：Zigh_Wang (赞：1)

# 题面
[CF原版](https://codeforces.com/contest/1715/problem/D)
[洛谷中文题面](https://www.luogu.com.cn/problem/CF1715D)

# 分析
通过观察我们可以发现，这是一道 2−SAT 问题，因为我们有 $q$ 个两两相关的限制条件，于是我们可以考虑建图来跑 (~~于是建图这一步这么快就出来了~~)。

因为我们的限制条件是**按位或**，因此我们可知在二进制下各个位是相互独立的，于是我们可以分开讨论，并且我们发现我们只需要对每个位上都求出字典序最小的情况，我们就得到了整个的字典序最小。

### 建图
我们考虑怎么建图：由于是 2-SAT 问题，假定每个数的**当前位**为点，那么每一对限制条件就是一条无向边（因为他们的限制是**相互**的）。

我们分 3 种情况讨论：

1. **已经确定**：通过观察我们可以发现，如果给定的 $a = b$ 那么我们就已经可以**确定** $ans[a] = x$（$ans$即为最终输出结果），注意 $a$ 是下标（注意看题）。那么我们在分位讨论的时候只需要给他所对应的点上一个特殊标记，告诉程序我们将**不再动他**即可（比如为 $1$ 就给他赋值为 $2$，为 $0$ 就直接赋值为 $0$，因为我们后面将只处理权值为 $1$ 的节点）。

2. **限制为0**：在一对限制条件中，我们不难发现，如果 $x$ 在这一位是 $0$，那么我们就可以断定 $ans[a]$ 和 $ans[b]$ 的这一位都是 $0$（由按位或的性质）。那么我们可以在建图的时候就直接让这两个点的权值赋为 $0$，然后再也**不动他**即可。（由于要求字典序最小，于是已经被赋为 $0$ 的位我们将不会再动）。

3. **限制为1**：再考虑 $x$ 这一位是 $1$ 的情况，我们先假定除了以上两种特殊处理的点以外的点的权值**都为 1**，然后将每一对这样的限制连上边（上面两种已经确定的情况可以不建）。我们**从节点 1 开始**（也就是对应原序列的第一个数）遍历**所有**他所连向的点，如果其中由**任何一个**权值为 $0$（前面赋的初值，或者后面处理的），那么我们可以确定这个点**只能**为 $1$。否则我们就把它赋为 $0$（为了保证字典序最小）。最后所有点更新完之后更新答案即可。（**注意**：已经赋值为 $0$ 或 $2$ 的点我们将不会再动，因为他们已经确定了）。

当所有位都跑完我们就得到了最终答案。

**注意**：如果某个点被孤立了（没有连边），那么他直接为 $0$ 是最优的。

eg. 我们以原题中的样例一为例：
![在这里插入图片描述](https://img-blog.csdnimg.cn/60e309f2a92e4153b8dd2521009fbb58.png)
上图中边上的权值表示限制中的 $x$ 这一位是什么。

# 代码实现
```cpp
//省略快读和头文件
#define Ql Qualifications//为了简写用
int T;

struct Edge {
	int hd[MAXN];
	int nxt[MAXN << 2], to[MAXN << 2];
	int tot = 0;
	
	void Add(int x, int y) {
		nxt[++tot] = hd[x];
		hd[x] = tot;
		to[tot] = y;
	}
}e;

int n, q;
int ans[MAXN];

struct Qualifications {
	int a, b, x;
}p[MAXN << 1];

int dig[MAXN];
void Solve(int pos)
{
	memset(e.hd, 0, sizeof(e.hd));//记得清空
	e.tot = 0;
	for(int i = 1; i <= n; i++)
		dig[i] = 1;
	for(int i = 1; i <= q; i++) {
		if(p[i].a == p[i].b) {
			if((p[i].x >> pos) & 1)
				dig[p[i].a] = 2;//表示为 1，且固定不再修改
			else
				dig[p[i].a] = 0;//如果是 0，直接为 0 即可，因为我们本来就不动他 
			continue;
		}
		
		if((p[i].x >> pos) & 1) {//如果是 1 就说明需要连边来判断如何填 
			e.Add(p[i].a, p[i].b);
			e.Add(p[i].b, p[i].a);
		}else {
			dig[p[i].a] = dig[p[i].b] = 0;//如果是 0 那么直接赋值为 0 即可，由按位或的性质 
		}
	}
	for(int x = 1; x <= n; x++) {
		if(dig[x] == 0 || dig[x] == 2)
			continue;//这两种都是已经固定的
		
		bool flag = true;//表示可以更改为 0 
		for(int i = e.hd[x]; i; i = e.nxt[i]) {
			int y = e.to[i];
			if(dig[y] == 0) {//只要连向的点有一个是 0 就说明他一定是 1 
				flag = false;
				break;
			}
		}
		
		if(flag || !e.hd[x])//否则将他赋值为 0 一定更优(字典序最小) 
			dig[x] = 0;//同样如果这个点是独点，那么他一定为 0 更优 
	}
	
	for(int i = 1; i <= n; i++)
		ans[i] |= (dig[i] > 0) * (1 << pos);
}

int main()
{
	n = inpt(), q = inpt();
	
	for(int i = 1; i <= q; i++) {
		int a = inpt(), b = inpt(), x = inpt();
		
		if(a == b)//表示这一个已经确定了 
			ans[a] = x;
		p[i] = Ql{a, b, x};//看不懂就看第1行和第19行
	}
	
	for(int i = 0; i < 31; i++)//分位做 
		Solve(i);
	
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	
	return 0;
}
```

---

## 作者：y_kx_b (赞：1)

神 $\texttt j\color{red}\texttt{iangly}$ 做法，想了半天才看懂 /kk

考场上一直在淦 B，然后一直没淦过，错过了一道好题（至少我这么觉得）。

Sol.
---
涉及到两点之间的关系，考虑建图。因为 $i$ 和 $j$ 没有顺序关系，故建无向图。（当然因写法而异，建有向图应该也是可以的：$i$ 到 $j$ 有边仅当 $i<j$ 成立。当然我没试过）

首先，边读入边建图，边预处理出每个节点最大的可能值 $f$（每次位与上边权）。

比如下图：（为了方便，边权已用二进制位表示。）

![](https://cdn.luogu.com.cn/upload/image_hosting/cxr15upq.png)

$1$ 号点的最大值为 $\texttt{101}$，$2$ 号点的最大值为 $\texttt{110}$，$3$ 号点的最大值为 $\texttt{100}$。

然后，因为答案需要字典序最小，我们贪心地让靠前的点的值最小。那么遍历一遍和这个点相连的边，每次计算出这个点至少要做出多少贡献。即：`res|=w&~f[j]`：$w$ 是边权，$j$ 是另一节点。这句话的意思是：$f_j$ 是另一节点最大做出的贡献，取反再位与边权就是该节点最少还需要对该边做出多少贡献。然后把每条边的贡献全部位或起来就是这个点最小的权值。最后 $f_i\gets res$，因为这个点点权已经确定了。

继续用上面的例子。因为 $3$ 号点最多只能贡献 $\texttt{100}$，所以 $1$ 号点必须贡献一个 $\texttt{001}$。而到 $3$ 号点时 $f_1=\texttt{001},f_2=\texttt{010}$，所以 $f_3=\texttt{100}$。

然后发现样例 \#3 过不了，~~被迫~~考虑自环的情况。

如果出现自环说明 $f_i\operatorname{or}f_i=x$，意味着 $f_i$ 必须等于 $x$。所以直接 `if(j==i)res=w;` 易证其他情况下 $res$ 不会超过自环的 $w$。

为什么要特判自环？因为如果不特判的情况下程序会认为 $j(=i)$ 已经为这条边做出了所有贡献，那么它会认定 $i$ 不需要做出贡献。实际上这是错误的。

至于样例 \#2，因为一开始 $res$ 初始化为 $0$，所以没有影响。

Extended Part：无解？
---
（注：原题保证数据有解。）

我们现在考虑什么情况会无解。先给出结论：如果在给 $f_i$ 赋值为 $res$ 前发现 $res\operatorname{or}f_i\not=f_i$，那么无解。

### 1.自环。
>易证其他情况下 $res$ 不会超过自环的 $w$。

易证如果 $res$ 超过了自环的 $w$（$\Leftarrow res\operatorname{or}w\not=w$），那么无解。

显然自环代表这个点权值只能为 $w$。如果这个点必须为其他点做出额外的贡献，那么无解。

![](https://cdn.luogu.com.cn/upload/image_hosting/ixjwffqx.png)

这个例子中，$1$ 号节点的自环意味着它的权值只能为 $\texttt{010}$，但它要为 $1\ 2\ \texttt{111}$ 这条边贡献出 $\texttt{011}$，所以无解。

### 2.重边（权值不同）。
![](https://cdn.luogu.com.cn/upload/image_hosting/kz8dui0u.png)

这里两个节点都不能贡献 $\texttt{100}$，所以程序认为 $1$ 号点需要贡献 $\texttt{100}$，但 $1$ 号点无法贡献，无解。

其实和下面没有区别。
### 3.其他情况
![](https://cdn.luogu.com.cn/upload/image_hosting/83ei7dkt.png)

这里三个节点都不能贡献，所以程序认为 $1$ 号点需要贡献 $\texttt{101}$，但 $1$ 号点无法贡献，无解。

### 4.树（森林）
前面三个都是带环的，但别以为树（森林）就不存在无解情况了。

![](https://cdn.luogu.com.cn/upload/image_hosting/4wpdfjsk.png)

这里 $1$ 号和 $2$ 号都被限制死了，所以无法贡献边 $1\ 2\ \texttt{010}$。

---
一开始忘放 code 了，补上。
```cpp
int n,m;
int f[N];
bool major(){
	n=read();
	fill(f+1,f+n+1,0x7fffffff);
	m=read();
	while(m--){
		int a=read(),b=read(),c=read();
		addd(a,b,c);
		f[a]&=c,f[b]&=c;
	}
	for(int i=1;i<=n;i++)
	{
		int res=0;
		for(int k=head[i];k;k=ne[k])
			if(to[k]!=i)res|=w[k]&~f[to[k]];
			else res=w[k];//这里写res|=w[k];也刑
		if((res|f[i])!=f[i])return puts("FaQ");//无解
		printf("%d ",f[i]=res);
	}
	return 114514;
}
```

---
~~瞎写的，连自己都看不懂/kk~~

所以如果有内容错误请在评论区指出，谢谢！

---

## 作者：tangtangpeng (赞：1)

## 题意

给定有 $q$ 个方程的方程组，方程都如 $a_i \mid a_j = x$ 的形式，$|$ 表示按位或，求出字典序最小的一组解。

## 思路

按位或运算每一位之间互不干扰，所以我们把方程组二进制化后一位一位地考虑。

对于每一位，我们可以建图处理，如果有方程 $a_i \mid a_j = x$，那么就从 $i$ 到 $j$ 连一条权值为 $x$ 对应的这一位的边。

问题转化为：有一张 $n$ 个节点，$m$ 条边的无向图，点有点权边有边权，给定边权，求使得对于每一条边，两端的点权的按位或等于边权的字典序最小的点权。

最开始所有点都赋值为 $1$，然后扫一遍整张图，如果发现有一条边的边权为 $0$
，那么这条边两端的点权就必须都为 $0$。

现在我们已经将所有点权必须为 $0$ 的点赋好了值，我们再扫一遍整张图，如果发现有一个点的点权仍为 $1$，那么使用贪心思想，判断一下如果存在这个点的出边的边权为 $1$ 且这条边上的儿子的点权为 $0$，那么这个点就必须为 $1$，否则这个点的点权就可以赋值为 $0$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2E5 + 10;
int n, m;
int a[N];
vector< pair<int, int> > G[N];

bool get_bit(int x, int bit){return (x >> bit) & 1;}
void trans1(int &x, int bit){x |= (1 << bit);}
void trans0(int &x, int bit){x &= ~(1 << bit);}

bool solve(int bit)
{
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < G[i].size(); j++)
		{
			if(!get_bit(G[i][j].second, bit))
				trans0(a[i], bit);
			else if(!get_bit(a[i], bit) && !get_bit(a[G[i][j].first], bit))
				return 0;
		}
	for(int i = 1; i <= n; i++)
		if(get_bit(a[i], bit))
		{
			trans0(a[i], bit);
			for(int j = 0; j < G[i].size(); j++)
				if(!get_bit(a[G[i][j].first], bit) && get_bit(G[i][j].second, bit))
				{
					trans1(a[i], bit);
					break;
				}
		}
	return 1;
}

int main()
{
	cin >> n >> m;
	while(m--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		G[a].push_back(make_pair(b, c));
		G[b].push_back(make_pair(a, c));
	}
	for(int i = 1; i <= n; i++)
		a[i] = (1 << 31) - 1;
	for(int i = 0; i <= 30; i++)
		if(!solve(i))
		{
			cout << -1;
			return 0;
		}
	for(int i = 1; i <= n; i++)
		cout << a[i] << " ";
	return 0;
}
```


---

## 作者：Kidding_Ma (赞：1)

要让字典序最小就要让每个数字在满足条件的同时都尽可能的小并且排在前面的数字变小的优先级要比排在后面的数字的优先级更大。
$$
\begin{aligned}
1\operatorname|1 &= 1\\
0\operatorname|1 &= 1\\
1\operatorname|0 &= 1\\
0\operatorname|0 &= 0\\
\end{aligned}
$$
先排序，让下标小的限定条件排在前面，等下才方便贪心。  
如果 $i\operatorname|j = x$ 那么当 $x$ 二进制下某位为 $0$ 时，$i$ 和 $j$ 对应的那位也必须是 $0$ 我们用一个二维数组 $a$ 来标记这些必须为 $0$ 的位，标记为 $2$。  
全部标记完以后再遍历一次，如果 $x$ 二进制下某位为 $1$，若 $i = j$，那 $i$ 对应的那位肯定是 $1$；如果 $i$ 和 $j$ 不相等，那么 $i$ 对应的那位为 $1$ 或 $j$ 对应的那位为 $1$；如果 $i$ 对应的那位已经被标记为 $2$ 了，那么肯定是 $j$ 对应的那位为 $1$，否则反之；如果是 $1$ 那么标记为 $1$。 
最后只剩一种情况，如果 $x$ 二进制下某位为 $1$ 且 $i$ 和 $
j$ 对应的那位既没有被标记为 $2$ 也没有被标记为 $1$, 这种情况肯定是 $j$ 对应的那位标记为 $1$。

C++ Code

```cpp
#include "bits/stdc++.h"

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<array<int, 3>> q(m);

  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    x--;
    y--;
    if (x > y) {
      swap(x, y);
    }
    q[i] = {x, y, w};
  }

  sort(q.begin(), q.end());

  vector<array<int, 30>> a(n);

  for (int i = 0; i < m; i++) {
    auto [x, y, w] = q[i];
    for (int j = 0; j < 30; j++) {
      if ((w >> j & 1) == 0) {
        a[x][j] = 2;
        a[y][j] = 2;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    auto [x, y, w] = q[i];
    for (int j = 0; j < 30; j++) {
      if (w >> j & 1) {
        if (x == y) {
          a[x][j] = 1;
          a[y][j] = 1;
        } else if (a[x][j] == 2) {
          a[y][j] = 1;
        } else if (a[y][j] == 2) {
          a[x][j] = 1;
        }
      }
    }
  }

  for (int i = 0; i < m; i++) {
    auto [x, y, w] = q[i];
    for (int j = 0; j < 30; j++) {
      if (w >> j & 1) {
        if (a[x][j] == 0 && a[y][j] == 0) {
          a[y][j] = 1;
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    int res = 0;
    for (int j = 29; j >= 0; j--) {
      res *= 2;
      if (a[i][j] == 2) {
        a[i][j] = 0;
      }
      res += a[i][j];
    }
    cout << res << " \n"[i == n - 1];
  }

  return 0;
}
```

---

## 作者：LYY_yyyy (赞：0)

首先显然要拆位。由于字典序最小，我们贪心地希望当这一位 $x$ 为 $1$ 时，将 $1$ 挂在较大的位置上。但是直接贪心可能会出现矛盾。我们记 $g_{i,k}$ 表示在第 $k$ 位上，$i$是否一定要填 $0$。考虑将每个条件转化为一条 $i,j$ 之间的，权值为 $x$ 的双向边。当 $x$ 的第 $k$ 位为 $0$ 时，我们将 $g_{i,k}$ 和 $g_{j,k}$ 置为 $1$。之后从前向后考虑每个点，枚举出边，设这个点为 $u$，连向 $v$。记 $ans_{i,k}$ 为 $i$ 每一位的答案，初始全是 $0$。分类：

若 $u<v$，如果 $x$ 的第 $k$ 位为 $1$ 并且 $g_{v,k}=1$，则 $ans_{u,k}=1$，否则忽略。

若 $u>v$，如果 $x$ 的第 $k$ 位为 $1$ 并且 $u$ 未被确定（见后文），则 $ans_{u,k}=ans_{v,k}\oplus1$，否则忽略。

以上就是核心思路。还有一个细节，就是重边的处理，此时我们发现 $u$ 的答案就是 $x$ ，开一个数组记一下它已经被确定即可，不用建边。

最终 $i$ 的答案就是 $\sum_{k=0}^{29}2^kans_{i,k}$，时间复杂度 $O(m\log V)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int head[100010];int tot;
bool g[100010][30];
int ans[100010][30];
struct node
{
	int to,next,w;
}q[400010];
void build(int u,int v,int w)
{
	q[++tot].to=v;
	q[tot].w=w;
	q[tot].next=head[u];
	head[u]=tot;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	while(m--)
	{
		int u,v,w;
		cin>>u>>v>>w;
		if(u==v)
		{
			for(int i=0;i<=29;i++) 
			{
				ans[u][i]=(w>>i)&1;
				if(!((w>>i)&1)) g[u][i]=1;
			}
		}
		else
		{
			build(u,v,w);build(v,u,w);
			for(int i=0;i<=29;i++){
				if(!((w>>i)&1)) g[u][i]=g[v][i]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=q[j].next)
		{
			int to=q[j].to,x=q[j].w;
			if(to<i)
			{
				for(int z=0;z<=29;z++)
				{
					if(!((x>>z)&1)) continue;
					if(ans[i][z]) continue;
					ans[i][z]=ans[to][z]^1;
				}
			}
			else
			{
				for(int z=0;z<=29;z++)
				{
					if(!((x>>z)&1)) continue;
					if(g[to][z]) ans[i][z]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=0;j<=29;j++) sum+=ans[i][j]*(1<<j);
		cout<<sum<<' ';
	}
	return 0;
}
```

---

## 作者：zhaoyp (赞：0)

# Solution
[CF1715D](https://codeforces.com/contest/1715/problem/D)
$\text{Difficulty : 1900}$。

------------

题意：长度为 $n$ 的整数数组 $a$，$q$ 个限制，每个限制包括三个整数 $i,j,x$，要求满足 $a_i\mid a_j$，其中 $\mid$ 表示按位或运算。

首先自己或自己的数是确定的。

其次把某位或起来为 $0$ 的两数的该位填上 $0$。

然后考虑现在必须填 $1$ 的数位，也就是或起来为 $1$，但是其中一个数位已经填了 $0$。

然后剩下的就可以贪心选字典序最小的，从 $1$ 到 $n$，从高位到低位，如果还没有填过就在这个位置上填上 $0$，然后把填上这个 $0$ 之后必须填 $1$ 的数位填上 $1$。

在实现上可以把或起来为 $1$ 的两位之间连边。

[my code](https://codeforces.com/contest/1715/submission/169134205)

---

