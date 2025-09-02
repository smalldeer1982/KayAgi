# Railway System

## 题目描述

As for the technology in the outside world, it is really too advanced for Gensokyo to even look up to.

—Yasaka Kanako, Symposium of Post-mysticism



This is an interactive problem.

Under the direct supervision of Kanako and the Moriya Shrine, the railway system of Gensokyo is finally finished. GSKR (Gensokyo Railways) consists of $ n $ stations with $ m $ bidirectional tracks connecting them. The $ i $ -th track has length $ l_i $ ( $ 1\le l_i\le 10^6 $ ). Due to budget limits, the railway system may not be connected, though there may be more than one track between two stations.

The value of a railway system is defined as the total length of its all tracks. The maximum (or minimum) capacity of a railway system is defined as the maximum (or minimum) value among all of the currently functional system's [full spanning forest](https://en.wikipedia.org/wiki/Spanning_tree#Spanning_forests).

In brief, full spanning forest of a graph is a spanning forest with the same connectivity as the given graph.

Kanako has a simulator only able to process no more than $ 2m $ queries. The input of the simulator is a string $ s $ of length $ m $ , consisting of characters 0 and/or 1. The simulator will assume the $ i $ -th track functional if $ s_i= $ 1. The device will then tell Kanako the maximum capacity of the system in the simulated state.

Kanako wants to know the the minimum capacity of the system with all tracks functional with the help of the simulator.

The structure of the railway system is fixed in advance. In other words, the interactor is not adaptive.

## 说明/提示

Here is the graph of the example, satisfying $ l_i=i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1687B/91ed2595ccd5b28c792f8d64dc85c03cf1c73365.png)

## 样例 #1

### 输入

```
5 4

0

5

9

7```

### 输出

```
? 0000

? 1110

? 1111

? 1101

! 7```

# 题解

## 作者：GaryH (赞：6)

考虑模拟 `kruskal` 的过程来求最小生成树，即：

首先我们可以用 $m$ 次询问求出每条边的边权，
再按边权从小到大的顺序尝试加入每条边。

对于当前考虑的边，设其权为 $w$ 且连接了 $u,v$，
则我们需要判断，

是否存在一条左右端点分别为 $u,v$ 的链，满足这条链上所有边的权值都小于 $w$，

如果不存在，则等价于当前边不在最小生成树中，
而这个条件的判定，我们可以用两次询问做到。

具体的，我们先查询出：保留所有边权**不超过** $w$ 的边的最大生成树的边权和 $x$，

我们再查询出：保留所有边权**小于** $w$ 的边并查询出最大生成树的边权和 $x'$，

那么 $x-x'=w$ 就等价于不存在一条满足上面要求的链，
原因是所有边的权值都是正的。

注意到某次查询出的 $x'$ 实际上就是上一次查询出的 $x$，
所以一共用 $2m$ 次查询，就能求出最小生成树的权值和。

**code** :
```
#include <bits/stdc++.h>

#define fi first
#define se second
#define vi vector
#define db double
#define ep emplace
#define mp make_pair
#define pb push_back
#define LL long long
#define emp emplace_back
#define pii pair < int , int >
#define SZ(x) ((int)(x.size()))
#define all(x) x.begin(), x.end()
#define ckmax(a, b) ((a) = max((a), (b)))
#define ckmin(a, b) ((a) = min((a), (b)))
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define edg(i, v, u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

using namespace std;

int read (char ch = 0, int x = 0, int f = 1) {
	while (ch < '0' || ch > '9') f = ch == '-' ? -1 : 1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
void write (int x) {
	if (x < 0) putchar ('-'), x = -x;
	static int stk[45], top = 0;
	do stk[++top] = x % 10, x /= 10; while (x);
	while (top) putchar (stk[top] + '0'), top--;
}

const int N (505);

int n, m;
string s;
pii e[N];
int rk[N];

int qry() {
	cout << "? " << s << endl, cout.flush();
	int x; cin >> x; return x;
}

int main() {
	cin >> n >> m;
	rep (i, 0, m - 1) s.pb ('0');
	rep (i, 1, m) {
		s[i - 1] = '1';
		e[i].fi = qry(), e[i].se = i;
		s[i - 1] = '0';
	}
	sort (e + 1, e + m + 1);
	int mst = 0, lst = 0;
	rep (i, 1, m) {
		s[e[i].se - 1] = '1';
		int x = qry();
		if (x == lst + e[i].fi) {
			mst += e[i].fi;
		}
		lst = x;
	}
	cout << "! " << mst << endl, cout.flush();
	return 0;
}
```

---

## 作者：StayAlone (赞：4)

### 题意

交互题。

给定一个 $n$ 个点，$m$ 条边的图。你可以询问 $2m$ 次：选取原图中的某些边之后，在这些边中找到的最大生成森林的边权之和。你需要回答整个图的最小生成森林的边权和。

$n\leq 200,m\leq 500$


### 思路

考虑 kruskal 的过程，需要知道：

- 每条边的边权；
- 每条边的两个端点目前是否在一个连通块中。

可以通过询问完成以上的操作，完全就是模拟一遍 kruskal。

先通过前 $m$ 次询问轻松获得所有边的边权，将其从小到大排序。设当前的边权和为 $w_1$，加入这条边之后的最大生成森林边权和为 $w_2$，这条边的边权为 $w$，则两个点 $u,v$ 不在同一个连通块中，当且仅当 $w_1 + w = w_2$。证明其实比较显然：

1. 充分性

考虑反证：若 $w_1+w=w_2$ 但 $u,v$ 在同一个连通块中，得到的不是一个森林（有环）。

2. 必要性

由于 $u,v$ 不在同一个连通块中，按照 kruskal 的贪心，显然要将其加入生成森林。

稍微实现一下就可以通过 $2m-1$ 次询问回答出答案。

模拟 kruskal！模拟 kruskal！模拟 kruskal！与 kruskal 的唯一区别就在于原本并查集的操作用查询来完成。

时间复杂度 $\mathcal O(m^2)$。

[AC code record](https://www.luogu.com.cn/record/101883414)

```cpp
int n, m, sum; string s;
pii ans[510];

int main() {
	read(n, m);
	rep1(i, 0, m - 1) s += '0'; s[0] = '1';
	rep1(i, 0, m - 1) {
		cout << "? " + s << endl;
		read(ans[i].fst); s[i] = '0';
		if (i ^ m - 1) s[i + 1] = '1';
		ans[i].snd = i;
	} sort(ans, ans + m); sum = ans[0].fst;
	rep1(i, 0, m - 1) s[i] = '0'; s[ans[0].snd] = '1';
	rep1(i, 1, m - 1) {
		s[ans[i].snd] = '1';
		cout << "? " + s << endl;
		int x = read();
		if (x == sum + ans[i].fst) sum += ans[i].fst;
		else s[ans[i].snd] = '0';
	} printf("! %d", sum);
	rout; 
}
```

---

## 作者：ncwzdlsd (赞：2)

简化一下题意，给定一个 $n$ 个点 $m$ 条边的无向带权图，不超过 $2m$ 次询问，每次可以询问一个边集，交互器返回由这些边构成的最大生成森林的边权和，要求求出最小生成森林的权值和。

蒟蒻的第一道交互题诶 qwq。

我们考虑模拟一下 Kruskal 求最小生成树的过程。为了用 Kruskal 求出最小生成树，我们需要知道每一条边的边权和边是否在一个连通块内。

对于边权，我们可以采用 $m$ 次询问得到所有边权，这是好的。

对于连通块的维护，我们考虑这样询问：如果最大生成森林的边权和的减小值不等于删掉的这条边的权值，那么说明为了连通性用一条边权更小的边进行替换；如果减小值等于删掉的边的边权，证明连通性被破坏了，显然，这条边是一个重要角色，因为它是连通两个点的最小边，于是乎在 Kruskal 的过程中，我们加入这条边的时候显然两端一定没有相连，于是乎它一定在最小生成森林中。

然后模拟 Kruskal 的过程，直接统计答案就可以了 qwq。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;

struct node
{
	int v,id;
}gg[505];

bool cmp(node a,node b)
{
	return a.v<b.v;
}

int query(string s)
{
	cout<<"? "<<s<<endl;
	cout.flush();
	int tmp;cin>>tmp;
	return tmp;
}

int main()
{
	int n,m;cin>>n>>m;
	for(int i=1;i<=m;i++) s+='0';
	for(int i=1;i<=m;i++)
		s[i-1]='1',gg[i].v=query(s),s[i-1]='0';//查询边权，注意字符串下标从1开始 
	for(int i=1;i<=m;i++) gg[i].id=i;
	sort(gg+1,gg+m+1,cmp);
	int ans=0,tmp1=0,tmp2=0;
	for(int i=1;i<=m;i++)
	{
		s[gg[i].id-1]='1',tmp1=query(s);
		if(tmp1!=gg[i].v+tmp2) s[gg[i].id-1]='0';
		else tmp2=tmp1,ans+=gg[i].v;
	}
	cout<<"! "<<ans;
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

首先我们可以 $m$ 次询问得到 $m$ 条边权。

然后参照 Kruskal 算法流程。

我们将边按照边权升序排序，依次判断两端点是否已经在同一并查集里。

具体地，假设当前枚举到边 $e$，边权为 $x$，前面已经确认在最小生成树（或森林）的边集为 $E$，$E$ 中的边权和为 $y$。

询问一下 $E\cup e$ 的最大生成树（森林），设为 $z$。若 $z=x+y$，则说明 $e$ 的两端不在同一个并查集内，此时我们将 $e$ 加入 $E$ 即可。

* * *

若 $e$ 的两端不在同一个并查集内，则树上的某条路径和 $e$ 组成了一个环，我们必然在环上删掉一条边，由于边权为正，$z<x+y$，矛盾。

* * *

否则，不将 $e$ 加入 $E$。

这样我们不超过 $m+m=2m$ 次求出了答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 502

struct node{
	int val,id;
	friend bool operator<(node x,node y){
		return x.val<y.val;
	}
}a[N];
int n,m;
int que(string s){
	cout<<"? "<<s<<endl;
	cout.flush();
	static int x;
	cin>>x;
	return x;
}
signed main(){IOS;
	cin>>n>>m;
	string s;
	For(i,1,m) s=s+'0';
	For(i,1,m){
		s[i-1]='1';
		a[i].val=que(s);
		s[i-1]='0';
	}
	For(i,1,m) a[i].id=i;
	sort(a+1,a+1+m);
	int ans=0,res,lst=0;
	For(i,1,m){
		s[a[i].id-1]='1';
		res=que(s);
		if(res!=lst+a[i].val){
			s[a[i].id-1]='0';
		}else{
			lst=res;
			ans+=a[i].val;
		}
	}
	cout<<"! "<<ans<<endl;
return 0;}
```

---

## 作者：听取MLE声一片 (赞：2)

Update：修改部分词汇。

人话题面：给定一个图，你每次询问可以控制每条边通断，并获得最大生成森林答案，不超过 $2m$ 次询问，需要求全图的最小生成森林。

最小生成森林自然想到 kruskal，首先是将所有边排序，即把每条边都设成一个单独的 1，来求出每条边的长度。

kruskal 的思想是边从小到大排序，如果当前加的这条边并不真正连边，就不加，这个过程用并查集表示，我们可以将询问转化为一个并查集。

不难看出，如果现在连的是一个森林，最大生成森林显然就是所有边长度之和，换句话说，如果最大生成森林小于所有边的和，那么最后一条边是不需要加的。

由此便得出代码。

---

## 作者：dd_d (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16342541.html)
### Sol  
首先先用 $m$ 次查询把每条边的权值弄出来。  
然后把边按照权值排序。从小到大依次加入每条边。  
当一条边在最后的答案中那么当且仅当 $x-last=a_i$，其中 $x$ 为当前询问的答案，$last$ 为前 $i-1$ 条边组成的最优答案，$a_i$ 表示第 $i$ 条边的权值。  
正确性可以考虑 kruskal 的过程。  
### Code
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e5+10;
int n,m,bel[N],a[N],ans,p[N],last;
int query()
{
	cout<<"? ";
	for (int i=1;i<=m;i++)
		cout<<bel[i]; cout<<'\n';
	int now; cin>>now; return now;
}
signed main()
{
	n=read(); m=read();
	for (int i=1;i<=m;i++)
		bel[i]=1,a[i]=query(),bel[i]=0,p[i]=i;
	sort(p+1,p+m+1,[](int x,int y)
	{
		return a[x]<a[y];
	});
	for (int i=1;i<=m;i++)
	{
		bel[p[i]]=1;
		int x=query();
		if (x-last==a[p[i]]) last=x;
		else bel[p[i]]=0;
	}
	for (int i=1;i<=m;i++)
		if (bel[p[i]]) ans+=a[p[i]];
	cout<<"! "<<ans<<'\n';
}





```

---

## 作者：12345678hzx (赞：1)

## 题目大意
这是一道交互题。

有一个 $n$ 个点，$m$ 条边的图。你最多可以询问 $2m$ 次，每次长度为 $m$ 的询问形如 `? 1111`，回答为选取图中的若干条边的最大生成森林的边权之和。

当你知道了整张图的最小生成森林的边权和，你需要输出它。
## 思路
当我们需要知道一张图的最小生成森林的边权和，显然我们需要知道每条边的边权。所以可以做 `? 1000...000` 的询问来获得每条边的边权。然后我们就可以模拟最小生成树的加边过程，每次加入一条边，询问最大生成森林的边权和，如果这一次询问的答案减去上一次答案的值等于这条边的边权，则这条边一定在最小生成森林中。

我们考虑来证明这个结论。整个程序进行的过程就像 `kruskal` 算法的过程，所以可以证明这个结论。

---

## 作者：Shunpower (赞：1)

诈骗题。$n$ 是无用的，复杂度瓶颈在于输出。

此外 $n,m$ 开这么小其实是为了交互器的复杂度正确，与正解关联不大。

## 思路

首先考虑用 $m$ 次询问来得到每一条边的边权。

首先我们考虑对边权从大到小排序，然后从大到小删边。

注意到当我减少一条边，假如最大生成森林的总权值并没有减少这条边的边权，那么相当于是原图为了保持连通性不变换上了一条更小的边。

那么类似的我们可以想到当减少一条边，最大生成森林的总权值减少了这条边的边权，说明原图不得不放弃维持连通性，那么这条边是为了连通某两个“砍掉这条边就不连通了的”点所需要的最小的边。

然后想一想 Kruskal 的行为，当我选到这样的一条边时这一条边的两端一定没有被连过，那么这条边一定会被加入。所以这就说明这条边一定在最小生成森林上。

因此实现时先用 `000100` 这样的询问 $m$ 次得到边权。

然后按照从大到小边权排序，一开始放满 `111111`，然后抠掉最大的边，得到 `111011`，将两次的答案作差得到最大生成森林的总权值减少量，和这条边的边权比较并且处理就好了。然后继续抠成 `110011`，以此类推。

## 代码

$n$ 是没有作用的。复杂度 $\mathcal O(m^2)$，瓶颈在于输出。

```cpp
int n,m;
string s;
pii a[N];
bool cmp(pii x,pii y){
	return x.fi>y.fi;
}
int main(){
	cin>>n>>m;
	fr1(i,1,m){
		string s="";
		fr1(j,1,m){
			s+='0';//这里写的比较 naive
		}
		s[i-1]='1';
		cout<<"? "<<s<<endl;
		int x;
		cin>>x;
		a[i].fi=x;
		a[i].se=i;
	}//查询边权
	sort(a+1,a+m+1,cmp);//按边权排序
	fr1(i,1,m){
		s+='1';
	}
	int ans=0;
	int x=0,res=0;
	fr1(i,1,m){
		cout<<"? "<<s<<endl;
		cin>>x;
		if(!res){//第一次没有res要特判
			s[a[i].se-1]='0';
			res=x;
			continue;
		}
		if(res-x==a[i-1].fi){//砍掉上一条边影响连通性
			ans+=a[i-1].fi;//一定在最小森林上
		}
		s[a[i].se-1]='0';//抠掉边权最大的边
		res=x;
	}
	cout<<"! "<<ans+x<<endl;//最后一条边一定是影响连通性的边，因此在最小森林上
	ET;
}
```

[AC 记录](https://www.luogu.com.cn/record/101876109)

---

## 作者：JS_TZ_ZHR (赞：1)

## 题意：

有一个 $n$ 个点，$m$ 条边的图，现在你可以查询至多 $2m$ 次，每次查询可以得到对于你选定的边集的最大生成森林。求图的最小生成森林。

## 题解：

先得到所有边的长度。

考虑 Kruskal 算法的过程。从最小的边开始考虑。如果加入后新的最大生成树边权的增加值正好是这条边的权值，那么说明这条边连接了原来两个不同的连通块，应该加入最小生成树。将所有这样的边边权加起来即可。

```cpp
#include<bits/stdc++.h>
#define N 2000005
#define int long long
using namespace std;
int n,m,ans,sum;
string s1,s2;
struct node{
	int w,p;
}a[N];
bool cmp(node u,node v){
	return u.w<v.w;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)s1+="1",s2+="0";
	for(int i=1;i<=m;i++){
		s2[i-1]='1';
		cout<<"? "<<s2<<endl;
		cin>>a[i].w;
		a[i].p=i;
		s1[i-1]='1',s2[i-1]='0';
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		s2[a[i].p-1]='1';
		cout<<"? "<<s2<<endl;
		cin>>sum;
		if(sum==ans+a[i].w){
			ans=sum;
			continue;
		}
		else{
			s2[a[i].p-1]='0';
		}
	}
	cout<<"! "<<ans<<endl;
} 
```


---

## 作者：Cocoly1990 (赞：1)

显然的，边权是必然需要知道的，每次做形如 `0000...0100...000` 的询问可以在 $m$ 次询问内得到所有的边权。

模拟最小生成树的加边过程，从小到大加边，记第 $i$ 次询问的结果为 $a_i$,边权从小到大排序的集合为 $w_i$,则如果 $a_i-a_{i-1}=w_i$,那么 $w_i$ 就会是最后最小生成森林的其中一条边。

考虑证明，如果 $a_i-a_{i-1}=w_i$,就说明 $w_i$ 连接的两个顶点中不存在比 $w_i$ 还小的边，所以 $w_i$ 会在最小生成树中。

---

## 作者：Cells (赞：0)

##  思路

首先根据经验来说 CF 的交互题卡询问次数都比较死，所以说询问次数太离谱一般都是不正确的。

vp 时是这样想的，可以构造 $m$ 条只有一个 $1$ 的询问知道每条边的边权，还剩下了 $m$ 次询问机会。此时我们情不自禁的想起了 kruskal，基于贪心，每次加入最小边权的边。

所以我们存储每条边的边权和编号，排序。然后呢，我们每次都加入当前最短的边，让当前已选边权和更新，并且询问已选边的最大生成树的边权和，如果最大生成树的边权和不等于当前已选的边权之和，说明当前边已经在某个环中，代替了某个边权更小的边，所以最小生成树不能要这条边，更新已选边边权和还有已选边状态。其实质就是用询问充当了并查集。

不多不少 $2m$ 次，具体看代码会更清楚。

## Code

```c++
//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define fr front
# define il inline
# define fir first
# define sec second
# define vec vector
# define it iterator
# define pb push_back
# define lb lower_bound
# define ub upper_bound
# define all(x) x.begin(), x.end()
# define mem(a, b) memset(a, b, sizeof(a))

# define lc (t[p].l)
# define rc (t[p].r)
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r

# define sqr(x) ((x) * (x))
# define bpc __builtin_popcount
# define lowbit(x) ((x) & (-(x)))
# define geti(x, i) (((x) >> (i)) & 1)
# define set1(x, i) ((x) | (1 << (i)))
# define set0(x, i) ((x) & (~(1 << (i))))

# define debug1(x) cerr << #x << " = " << x << " "
# define debug2(x) cerr << #x << " = " << x << "\n"
# define bug cerr << "--------------------------\n"

# define each1(i, x) for(auto (i) : (x))
# define each2(i, x) for(auto (&i) : (x))
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
# define G(i, h, u, ne) for(int i = (h[(u)]); i; i = (ne[(i)]))
# define reps(i, a, b, c) for(int i = (a); i <= (b); i += (c))
# define pres(i, a, b, c) for(int i = (a); i >= (b); i -= (c))
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int M = 5e2 + 10;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int n, m, ans;

PII e[M];

bitset<M> have;//已选边 

signed main(){
	cin >> n >> m;
	
	rep(i, 1, m){
		cout << "? ";
		rep(j, 1, i - 1) cout << 0;
		cout << 1;
		rep(j, i + 1, m) cout << 0;
		cout << endl;
		cin >> e[i].fir;//边权 
		e[i].sec = i;//编号 
	}
	
	sort(e + 1, e + 1 + m, less<PII>());//排序 
	
	int sum = 0;
	rep(i, 1, m){
		sum += e[i].fir;//更新已选边边权和 
		have[e[i].sec] = true;//加入选的边 
		cout << "? ";
		rep(j, 1, m) cout << have[j];
		cout << endl;
		int v;
		cin >> v;
		if(v != sum){//在环中 
			have[e[i].sec] = false;//更新 
			sum -= e[i].fir;
		}
		
		else ans += e[i].fir;//不在环中，必定选
	}
	
	cout << "! " << ans << endl;
	
	return 0;
}
```

**感谢观看！！！**

---

## 作者：FiraCode (赞：0)

看到 $2m$ 次询问，考虑先把所有边的权值从小到大排序。

然后，考虑模拟 Kruskal，那么难点在判断当前边是否是链接了已联通的连通块。

那么我们可以考虑询问当前最小生成森林上的边加上当前边。

如果相比之前（设此时最大生成森林权为 $w$），加上边后的值若是 $w+v_i$，那么这条边就可以加到最大生成森林中。

询问次数为 $2m-1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
pair<int, int> v[100010];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        string s;
        for (int j = 1; j <= m; ++j)
            if (j != i) s += '0';
            else s += '1';
        
        cout << "? " << s << endl;
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v + 1, v + 1 + m);
    int la = v[1].first, sum = v[1].first;
    string s;
    for (int i = 1; i <= m; ++i) 
        if (i != v[1].second) s += '0';
        else s += '1';

    for (int i = 2; i <= m; ++i) {
        string t = s;
        t[v[i].second - 1] = '1';
        cout << "? " << t << endl;
        int val; cin >> val;
        if (val - la != v[i].first) ;
        else la = val, s = t, sum += v[i].first;
    }

    cout << "! " << la << endl;

    return 0;
}
```

---

## 作者：西瓜nd (赞：0)

蒟蒻的第一道交互题，第二篇题解，可能写的不好，轻喷。

[题目传送门](https://www.luogu.com.cn/problem/CF1687B)

## 题意简述
交互题，一个 $n$ 个点 $m$ 条边的无向带权图。初始给定 $n$，$m$，每次可以询问一个边集，返回由这些边组成的最大生成森林的边权和。要求在 $2m$ 次询问内求出最小生成森林的权值和。

（$2 \leq n \leq 200$，$1 \leq m \leq 500$）


## 题目分析

一个显然的想法，前 $m$ 次询问每次只询问一条边，知道每条边的边权，但还不知道图的形态。

考虑一下 Kruskal 的过程：

- 按边权从小到大排序

- 依次尝试加边，并查集判断是否会成环

我们可以发现，问题就在能否判断环，于是可以考虑能不能通过询问代替并查集的过程。

考虑将新加的边与原来已知的最小生成树（或森林）的边集进行一次询问，其最大生成树（或森林）可能发生了以下几种情况：

- 新加的边与原最大生成树（或森林）构成了环，为了保持连通性，从环上踢掉了一条边权更小的边，**边权和变化量小于新加边的边权**。
- 新加的边直接加入原最大生成树（或森林），**边权和变化量等于新加边的边权**。

显然，第一种情况的边是不能选的，因为新加这条边会使得最小生成树（或森林）有环。只有第二种情况满足。

同时不难发现，每次询问后最大生成树（或森林）的形态与最小生成树（或森林）的形态（边和点）都是一致的。这也是能这么做的一个依据。

综上，前 $m$ 次询问得到每条边边权。后 $m-1$ 次询问，每次我们用新加的边与原来已知的最小生成树（或森林）的边集进行一次询问，若边权和变化量小于新加边的边权，则这条边不可选；若边权和变化量等于新加边的边权，则选。这样就能在 $2m$ 次询问内得出答案。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=505;
int n,m;
bool bj[maxn];  //记录已知最小生成树（或森林）的边

struct edge{
    int p,v;
}c[maxn];

bool cmp(edge x,edge y){
    return x.v<y.v;
}

int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cout<<"? ";
        for(int j=1;j<=m;j++){
            if(j!=i)cout<<bj[i];
            else cout<<1;
        }
        cout<<endl;
        fflush(stdout);
        c[i].p=i;
        cin>>c[i].v;
    }

    sort(c+1,c+1+m,cmp);

    int cnt=0;
    ll ans=0;
    int x=c[1].v,y;
    bj[c[1].p]=1;
    ans+=c[1].v;

    for(int i=2;i<=m;i++){
        cout<<"? ";
        bj[c[i].p]=1;
        for(int j=1;j<=m;j++){
            cout<<bj[j];
        }
        cout<<endl;
        fflush(stdout);

        cin>>y;
        int d=y-x;
        if(d<c[i].v){   //若边权和变化量小于新加边的边权，不选
            bj[c[i].p]=0;
        }
        else{
            ans+=c[i].v;
            x=y;
            if(++cnt==n-1)break;
        }
    }
    cout<<"! "<<ans;

    return 0;
}

```

---

## 作者：jiangtaizhe001 (赞：0)

[题目传送门](http://codeforces.com/problemset/problem/1687/B)  
[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16379995.html)
### 题目大意
交互题，给定 $n,m$，代表有一张 $n$ 个点 $m$ 条边的带权无向图。  
每次询问，可以删除一些边（询问独立），得删掉这些边的最大生成森林。  
现在 $2m$ 次询问内求整张图片的最小生成森林。（最后输出答案不算询问）  
$n,m\le 500$   
生成森林的定义是选择图中的一些边，使得图的连通性不变，并且每个连通块都是树。  
### 题目解析
首先我们可以通过询问得到每一条边的边权，总共查询 $m$ 次，每次只需要保留一条边。  
我们可以考虑 Kruskal 的方法。  
注意到 Kruskal 的做法是将边权从小到大排序，然后判断每一条边是否可以加入到生成树（这题是生成森林）里面。重点在于加入这条边Hi好是否改变图的连通性。  
所以我们考虑使用询问操作来判断连通性。  
记上一次操作得到的最大生成森林为 $las$，新加进去的边的边权为 $c$，那么如果加进去后的边得到的最大生成森林是 $las+c$，代表这条边加进去后图的连通性改变了，那么就把这条边的边权计入答案。这样需要询问 $m$ 次。  
所以总共 $2m$ 次刚刚好。  

核心代码：
```cpp
struct JTZ{
	int c,num;
	bool operator < (const JTZ x) const {
		return this->c < x.c;
	}
}edge[maxn]; int n,m; char ask[maxn];
int main(){
	n=read(); m=read(); int i,j,now,las,ans; las=ans=0;
	for(i=1;i<=m;i++){
		pc('?'),pc(' '); for(j=1;j<=m;j++) pc(i==j?'1':'0'); pc('\n'); fflush(stdout);
		edge[i].c=read(); edge[i].num=i; ask[i]='0';
	} sort(edge+1,edge+m+1);
	for(i=1;i<=m;i++){
		ask[edge[i].num]='1'; printf("? %s\n",ask+1); fflush(stdout);
		now=read(); if(now==las+edge[i].c) ans+=edge[i].c; las=now; 
	} pc('!'),pc(' '),print(ans);
	return 0;
}
```

---

