# Books Exchange (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

There are $ n $ kids, each of them is reading a unique book. At the end of any day, the $ i $ -th kid will give his book to the $ p_i $ -th kid (in case of $ i = p_i $ the kid will give his book to himself). It is guaranteed that all values of $ p_i $ are distinct integers from $ 1 $ to $ n $ (i.e. $ p $ is a permutation). The sequence $ p $ doesn't change from day to day, it is fixed.

For example, if $ n=6 $ and $ p=[4, 6, 1, 3, 5, 2] $ then at the end of the first day the book of the $ 1 $ -st kid will belong to the $ 4 $ -th kid, the $ 2 $ -nd kid will belong to the $ 6 $ -th kid and so on. At the end of the second day the book of the $ 1 $ -st kid will belong to the $ 3 $ -th kid, the $ 2 $ -nd kid will belong to the $ 2 $ -th kid and so on.

Your task is to determine the number of the day the book of the $ i $ -th child is returned back to him for the first time for every $ i $ from $ 1 $ to $ n $ .

Consider the following example: $ p = [5, 1, 2, 4, 3] $ . The book of the $ 1 $ -st kid will be passed to the following kids:

- after the $ 1 $ -st day it will belong to the $ 5 $ -th kid,
- after the $ 2 $ -nd day it will belong to the $ 3 $ -rd kid,
- after the $ 3 $ -rd day it will belong to the $ 2 $ -nd kid,
- after the $ 4 $ -th day it will belong to the $ 1 $ -st kid.

So after the fourth day, the book of the first kid will return to its owner. The book of the fourth kid will return to him for the first time after exactly one day.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
3
2 3 1
6
4 6 2 1 5 3
1
1
4
3 4 1 2
5
5 1 2 4 3
```

### 输出

```
1 1 1 1 1 
3 3 3 
2 3 3 2 1 3 
1 
2 2 2 2 
4 4 4 1 4 
```

# 题解

## 作者：__O_v_O__ (赞：2)

首先我们注意到，从每一个点出发，走的路径都一定是勺型的，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/csfevdcm.png)

易知，$1$ 号点的答案是 $-1$，而其他点的答案都是 $5$（环的长度）。

于是可以得出这样一个结论：当找到“勺型”后，“勺柄”上点的答案都是 $-1$，“勺面”上点的答案都是环的长度。

得到结论后，后面的做法有很多，这里我只讲我的做法。

我开了三个数组，$vi$ 数组用来标记，$ord$ 数组用来记录点在“勺子”上的编号，$jg$ 数组记录“勺子”上依次经过的点的编号。

每次，往前走一步，这时有以下三种情况：
	
1. 没有走过当前点。这时将当前点的 $vi$ 值改为“勺尖”（上图的点 $1$）的值（每个“勺子”是不同的，不能混淆），再记录当前点的 $ord$ 和 $jg$ 值。

2. 走到了另一个“勺子”上。此时这个“勺子”上的点没有形成环，永远回不来，所以把这个“勺子”上的点的答案全部置为 $-1$。
	
3. 在同一个“勺子”上形成了环。这时用 $ord$ 数组求出这个点的编号，在它前面的点的答案全部置为 $-1$，在它后面的的的答案全部置为环的长度。
	
最后输出答案即可。注意多测清空。
	
**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int q,n,p[100001],vi[100001],jg[100001],a[100001],ord[100001];
void dfs(int x){
	int nu=1,st=x;ord[x]=1,vi[x]=st,jg[1]=x;
	while(1){
		int t=p[x];
		if(vi[t]!=st&&vi[t]){afor(i,1,nu,STB)a[jg[i]]=-1;return;}//第2种
		else if(vi[t]==st){//第3种
			int k=ord[t];
			afor(i,1,k-1,STB)a[jg[i]]=-1;
			afor(i,k,nu,STB)a[jg[i]]=nu-k+1;
			return;
		}else vi[t]=st,x=t,jg[++nu]=x,ord[x]=nu;//第1种
	}
}signed main(){
	ios::sync_with_stdio(0),cin>>q;
	afor(i,1,q,STB){
		cin>>n,memset(a,0,sizeof a),memset(vi,0,sizeof vi);
		afor(j,1,n,STB)cin>>p[j];
		afor(j,1,n,STB)if(!a[j])dfs(j);
		afor(j,1,n,STB)cout<<a[j]<<' ';
		cout<<endl;
	}return 0;
}
```

---

## 作者：Karry5307 (赞：2)

### 题意

一共有$q$组询问，每组询问给定一个长度为$n$的排列$p$，节点$i$向$p_i$连边，求每个点所属的最小环的长度。

$\texttt{Data Range:}1\leq q\leq 10^3,1\leq n\leq 2\times 10^5$

### 题解

有一道与之类似的题，叫做[$\texttt{Fixed Point Theorem}$](https://www.luogu.org/problem/UVA13074)（话说这是在我板刷$\texttt{UVa}$时偶然碰到的）

首先我们把排列写成置换的形式，有

$$\begin{pmatrix}1&2&3&\cdots&n\\p_1&p_2&p_3&\cdots&p_n\end{pmatrix}$$

然后可以把置换拆解成循环，然后记录一下每个位置所在循环的大小即可。

时间复杂度$O(qn)$，比$\texttt{Tarjan}$常数小。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=1e6+51;
ll test,cnt,tot;
ll vis[MAXN],perm[MAXN],bel[MAXN],size[MAXN];
inline ll read() 
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll dfs(ll cur,ll cnt,ll tot)
{
	if(vis[cur])
	{
		return cnt;
	}
	vis[cur]=1,size[tot]++,bel[cur]=tot;
	return dfs(perm[cur],cnt+1,tot);
}
inline void solve()
{
	for(register int i=1;i<=cnt;i++)
	{
		if(!vis[i])
		{
			dfs(i,0,++tot);
		}
	}
	for(register int i=1;i<=cnt;i++)
	{
		printf("%d ",size[bel[i]]);
	}
	puts("");
}
int main()
{
	test=read();
	for(register int t=0;t<test;t++)
	{
		cnt=read();
		for(register int i=1;i<=cnt;i++)
		{
			perm[i]=read();
		}
		solve();
		tot=0,
		memset(vis,0,sizeof(vis)),memset(bel,0,sizeof(bel));
		memset(size,0,sizeof(size));
	}
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1249/B2)
我们需要为每个查询计算每个孩子的书第一次回到自己手中的天数。由于 $p$ 是一个排列，每个孩子最终都会回到自己手中，且这个过程会形成一个或多个循环。

## 思路
用类似图论的方式解决：**对于每一个人，直接遍历一圈。**

但这样单次时间复杂度为 $\mathcal{O}(n^2)$，显然超时。

可以利用记忆化的思想，将这个环上的每一个人都记录下来，后面统一赋值。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[200005],p[200005];
bool vis[200005];
void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
		p[i]--; // 转换为0-based
	}
	memset(ans,0,sizeof(ans));
	memset(vis,false,sizeof(vis));
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			vector<int> cyc;
			int cur = i;
			while (!vis[cur]) {
				vis[cur] = true;
				cyc.push_back(cur);
				cur = p[cur];
			}
			int len = cyc.size();
			for (int k : cyc) {
				ans[k] = len;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
}
int main() {
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(nq) $，本题中 $\sum n \leq 2 \times 10^5$，可以通过本题。

---

## 作者：minVan (赞：1)

**题目大意**

有 $n$ 个小朋友每人手里有一本书，给定一个排列 $a$，表示每一轮第 $i$ 个小朋友会把书给 $a_i$。求每个小朋友的书会在几轮后回到自己手里。

**解题思路一**

很简单，实现一个简易的 $\texttt{DFS}$，就可以找出每个小朋友在第几轮可以拿回自己的书。

虽然这种方法看上去很简单，但实际上会 $\texttt{TLE}$，所以建议使用思路二。

**解题思路二**

递归、并查集。由于每个数字只出现一次，自己多画几个样例，可以发现要么会形成环，要么就单独一个点（或者叫自环），我们只需要从每个没有遍历过的点都进行一次递归搜索即可，最后这个环里面有几个点，那么就要传递几个人。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n, a[N], ans[N];
bool vis[N];
int dfs(int x, int d) {
	if(vis[x]) {
		return d - 1;
	}
	vis[x] = 1;
	return ans[x] = dfs(a[x], d + 1);
}
int main() {
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		fill(vis, vis + n + 1, 0);
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int i = 1; i <= n; i++) {
			if(vis[i]) {
				continue;
			}
			dfs(i, 1);
		}
		for(int i = 1; i <= n; i++) {
			cout << ans[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：thjkhdf12 (赞：1)

本题的标准做法是$Tarjan$或者$Kosarajo$缩点，但是瞎搜一下也是可以过的。$dfs$寻找如果下一个就是要找的目标那就返回$cnt$的值，$cnt$为当前进行了几次交换
```cpp
#include<iostream>
#include<cstring>
using namespace std;

#define mfor(i,a,b) for(register int i=(a);i<=(b);i++)
#define mem(a,b) memset(a,(b),sizeof(a))

int T;
int n;
int tu[1000010];
bool vis[1000010];
int ans[1000010];

int dfs(int x, int t, int cnt)
{
//t表示搜索目标，x表示当前搜索的是哪个，cnt表示当前深度
    vis[x] = true;
    if (t == tu[x]) return ans[x] = cnt + 1;
    return ans[x] = dfs(tu[x], t, cnt + 1);
}

int main()
{
    cin >> T;
    mfor(p, 1, T)
    {
        cin >> n;
        mem(vis, false);
        //多组样例一定要注意初始化问题
        mfor(i, 1, n) cin >> tu[i];
        mfor(i, 1, n)
        {
            if (!vis[i])
            {
                dfs(i, i, 0);
            }
        }
        mfor(i, 1, n)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}
```


-------------------------
### 更新
奉上$Tarjan$算法缩点正解（比瞎搜写起来麻烦很多，而且因为多种原因比如初始化麻烦，常数更大等等比瞎搜还慢一点）

根据题意，每次传书最终都能传回自己，所以这个传书的循环构成一个强连通分量，而每个点所在强连通分量中的点数就是传回自己所需要的传书次数
```cpp
#include<iostream>
#include<stack>
#include<algorithm>
#include<cstring>
using namespace std;

int T, n;
const int maxn = 200010;
int dfn[maxn]; //第i个点被dfs到的次序
int low[maxn];    //二叉搜索树上i所在子树上仍在栈中的最小dfn，low[i]相等的点在一个强连通分量中
bool vis[maxn];	//是否在栈中
stack<int>s;
int turn[maxn];
int tot;
int num[maxn];    //第i个强连通分量的点数
int res[maxn];	//res[i]表示i在第几个强连通分量中
int cnt;

void tarjan(int x)
{
	dfn[x] = low[x] = ++cnt;
	s.push(x);
	vis[x] = true;
	if (!dfn[turn[x]])
	{
		tarjan(turn[x]);
		low[x] = min(low[x], low[turn[x]]);
	}
	else if (vis[turn[x]])
	{
		low[x] = min(low[x], dfn[turn[x]]);
	}
	if (low[x] == dfn[x])
	{
		tot++;
		while (!s.empty() && s.top() != x)
		{
			int t = s.top();
			num[tot]++;
			res[t] = tot;
			vis[t] = false;
			s.pop();
		};
		s.pop();
		num[tot]++;
		res[x] = tot;
		vis[x] = false;
	}
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> turn[i];
		}
		for (int i = 1; i <= n; i++)
		{
			if (!dfn[i])
			{
				tarjan(i);
			}
		}
		for (int i = 1; i <= n; i++)
		{
			cout << num[res[i]] << " ";
		}
		cout << endl;
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(num, 0, sizeof(num));
		memset(res, 0, sizeof(res));
		tot = 0;
		cnt = 0;
	}
}
```

---

## 作者：QCurium (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1249B2)

[视频讲解（顺便点个赞吧](https://www.bilibili.com/video/BV1Lu4y147c3/?vd_source=a8f2ca9bd086cb49d933fb93cb7409c0)

## 题意

给你 $n$ 个数，让你求出每个数所在的环的长度是多少。

## 题目分析

我们可以记录第一个没被遍历过的点，从这个点开始找环，并将找到的换上数字的下标存在队列里，更新环的长度。这样，每找到一个新元素是，我们判断它和队首是否相同，如果相同，证明这个环找完了。

环找完了后，我们依次将队列中的元素弹出，并赋上值。当没有没被遍历过的点时，所有环就找完了。

因为 $\sum n \le 2 \times 10^5$，所以我们的做法是不会超时的。

## 题目推荐

[P2127 序列排序](https://www.luogu.com.cn/problem/P2127)，思想和此题很相似。

## Code

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define pdd pair<double,double>
#define int long long
#define base 200807
#define mod 212370440130137903
using namespace std;
const int N=2e5+5;
int t,n,nw=1,a[N],b[N];
bool bj[N]={0};
queue<int> q;
bool solve(){
	for(int i=nw;i<=n;i++){
		if(bj[i])
			nw++;
		else
			break;
	}
	if(nw>n)
		return 0;
	int asd=nw,cnt=0;
	if(a[asd]==asd){
		q.push(asd);
		cnt++;
	}
	else{
		while(a[asd]!=q.front()){
			q.push(asd);
			asd=a[asd];
			cnt++;
		}
		q.push(asd);
		cnt++;
	}
	while(!q.empty()){
		int c=q.front();
		q.pop();
		bj[c]=1;
		b[c]=cnt;
	}
	return 1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		nw=1;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		while(solve()){
			;
		}
		for(int i=1;i<=n;i++){
			cout<<b[i]<<" ";
			a[i]=0;
			b[i]=0;
			bj[i]=0;
		}
		cout<<'\n';
	}
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/126034989)

---

## 作者：JWRuixi (赞：0)

~~好像在考场上看见这种题~~

- 题意

来提供一波翻译：

给定长度为 $n$ 的排列 $p$，表示 $i$ 指向 $p_i$，求每个点所在环的长度，多组测试，$\sum n \le 2 \times 10^5$。

- 分析

我觉得没什么好说的，既然是排列，就直接暴力跳、打标记，复杂度 $O(n)$。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 2e5 + 500;
int T, n, p[maxn], ans[maxn];
bool vis[maxn];

int main () {
	T = read();
	while (T--) {
		n = read();
		for (int i = 1; i <= n; i++) p[i] = read(), vis[i] = 0; 
		for (int i = 1; i <= n; i++) {
			if (vis[i]) continue;
			int len = 0, x = i;
			while (p[x] != i) vis[x] = 1, len++, x = p[x];
			vis[x] = 1, len++, x = i;
			while (p[x] != i) ans[x] = len, x = p[x];
			ans[x] = len;
		}
		for (int i = 1; i <= n; i++) write(ans[i]), putchar(' ');
		puts("");
	}
}
```

---

## 作者：scp020 (赞：0)

### 题目大意

共 $q$ 组询问，对于每一组询问有长度为 $n$ 的序列 $p$，$p_i$ 表示第 $i$ 个人的下一位是 $p_i$。

求每一个点所在环的长度。

### 关于解法

本题是一道记忆化搜索题（我不会 Tarjan 缩点），从而减少时间复杂度。题目大意请参考 [CF1249B1](https://www.luogu.com.cn/problem/CF1249B1)。

我们发现如果暴力搜索的话对于每一个点我们都会一直搜索直到环，而这个算法会让有许多点重复走过多次，是没有意义的，所以我们想到了记忆化搜索。

暴力搜索时间复杂度是 $O(\sum n^2)$，记忆化搜索的时间复杂度是 $O(\sum n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int e[200010],q,n,cnt,t,f[200010],ans[200010];//记忆化搜索 
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
inline int search(int pos,int t,int cnt)
{
	f[pos]=1;
	if(t==e[pos]) return ans[pos]=cnt+1;
	else return ans[pos]=search(e[pos],t,cnt+1);
}
int main()
{
    q=read();
    while(q--)
    {
        n=read();
        memset(e,0,sizeof(e)),memset(f,0,sizeof(f));
        for(int i=1;i<=n;i++) e[i]=read();
        for(int i=1;i<=n;i++) if(!f[i]) search(i,i,0);
        for(int i=1;i<=n;i++) write(ans[i]),printf(" ");
        printf("\n");
    }
    return 0;
}
```


---

## 作者：lengxinjy (赞：0)

看到大佬们各种$Tarjan$缩点，蒟蒻瑟瑟发抖……

当时现场比赛的时候就看到它和[这个题](https://www.luogu.org/problem/P2661)有诸多相似之处。

在这道$NOIP$原题中，我们使用并查集维护每个点到对应根的距离以及最小环的大小。类似地，此题也可以使用并查集解决。维护距离操作完全相同，维护环时开一个$ans$数组记录每个点所在环的大小，每次$find$时更新距离，合并时更新换的大小即可。

这里还有一点小问题，对于每个环中不在最后一条边上的点（即不是“封口”的点），更新$ans$数组时，这些点并不会被更新到。所以我们在输出时，将$ans[i]$改为$ans[find(i)]$即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ff first
#define ss second
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int INF=2147483647;
inline int read()
{
	int x=0,k=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')k=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*k;
}
int f[200086],n,q,ans[200086],d[200086];
int find(int x)
{
	if(x!=f[x])
	{
		int last=f[x];
		f[x]=find(f[x]);
		d[x]+=d[last];
	}
	return f[x];
}
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy)f[fx]=fy,d[x]=d[y]+1;
	else
	{
		ans[x]=min(ans[x],d[x]+d[y]+1);
		ans[y]=min(ans[x],d[x]+d[y]+1);
	}
}
int main()
{
	q=read();
	while(q--)
	{
		memset(f,0,sizeof(f));
		memset(ans,0x7f,sizeof(ans));
		memset(d,0,sizeof(d));
		n=read();
		rep(i,1,n)f[i]=i;
		rep(i,1,n)
		{
			int p=read();
			merge(i,p);
		}
		rep(i,1,n)printf("%d ",ans[find(i)]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：B_Qu1e7 (赞：0)

暴力模拟即可。

每次搜索第一个还没加入到环中的点$i$，在路径中把途中经过的点的$step$标记为$i$。最后将环的长度赋给$i$即可。

```cpp
#include<cctype> 
#include<cstdio>
#define R register
int Q,N,A[200005],f[200005],p[200005];
template<class T>inline void read(R T &m)
{
	m=0;
	R char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(Q);
	while(Q--)
	{
		read(N);
		for(R int i=1;i<=N;++i)
		{
			read(A[i]);
			f[i]=0; //当前点开始的环长度
				//注意，只有第一个搜到的点标记环长度，其他点通过 标记在某个点开始的环中 的方式来找环长
			p[i]=i;//这个点在以哪个点开始的环中
		}
		for(R int i=1;i<=N;++i)
		{
			if(!f[p[i]])//注意这里是f[p[i]]，不是f[i]
			{
				R int tmp=A[i],step=1;
				p[i]=i;
				while(tmp!=i)//不成环
				{
					++step;//环长增加
					p[tmp]=i;//标记是以i开始的环
					tmp=A[tmp];//找下一个点
				}
				f[i]=step;
			}
		}
		for(R int i=1;i<=N;++i)
		{
			printf("%d ",f[p[i]]);
		}
		puts("");
	}
}
```

---

