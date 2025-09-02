# Culture Code

## 题目描述

在附近的一家纪念品商店里，有著名的俄罗斯套娃（matryoshka）出售，你想买几个。商店里有 $n$ 个不同的套娃。每个套娃的体积为 $out_i$，内部空间体积为 $in_i$（当然，$out_i > in_i$）。

你的包里空间不多，但幸运的是，你知道套娃可以相互嵌套。形式化地说，如果我们可以重新排列一组套娃，使得第一个套娃可以嵌套进第二个，第二个可以嵌套进第三个，依此类推，则称这组套娃是嵌套的。如果 $out_i \le in_j$，则套娃 $i$ 可以嵌套进套娃 $j$。因此，只有最外层的套娃会占用你包里的空间。

我们定义一组嵌套套娃的“额外空间”为该结构内部所有空余空间的总体积。显然，这等于 $in_{i_1} + (in_{i_2} - out_{i_1}) + (in_{i_3} - out_{i_2}) + \dots + (in_{i_k} - out_{i_{k-1}})$，其中 $i_1, i_2, \ldots, i_k$ 是选中套娃按嵌套顺序的编号。

最后，我们称一个嵌套子集是“足够大”的，如果没有其它套娃可以加入该子集且不破坏其嵌套性质。

你想买尽可能多的套娃，所以你应该选择一个“足够大”的嵌套子集。但如果包里浪费太多空间你会失望，因此你希望选择一个“足够大”的子集，使其额外空间在所有“足够大”子集中最小。现在你想知道，有多少个不同的嵌套子集满足这些条件（即它们是“足够大”的，并且不存在额外空间更小的“足够大”子集）。如果存在至少一个编号 $i$，使得一个子集包含第 $i$ 个套娃而另一个不包含，则这两个子集被认为是不同的。

由于答案可能很大，请输出对 $10^9 + 7$ 取模后的结果。

## 说明/提示

在示例中，有 $6$ 个“足够大”的嵌套子集，其额外空间均为最小值：

- $\{1, 5\}$：无法再加入其他套娃且保持嵌套，额外空间为 $1$；
- $\{1, 6\}$；
- $\{2, 4, 5\}$；
- $\{2, 4, 6\}$；
- $\{3, 4, 5\}$；
- $\{3, 4, 6\}$。

没有更多“好”的子集，例如，子集 $\{6, 7\}$ 不是“足够大”的（可以加入第 $4$ 个套娃），而子集 $\{4, 6, 7\}$ 的额外空间为 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
4 1
4 2
4 2
2 1
5 4
6 4
3 2
```

### 输出

```
6
```

# 题解

## 作者：wlzhouzhuan (赞：27)

- 前言

比赛的时候做不出来，哭死在厕所。

赛后听大家说是$DP$，听了下思路，觉得还蛮有道理的。

但后来听 $\color{red}{Sooke}$ 口胡的思想，觉得十分的优美，连我的老师   $xkchen$ 都赞不绝口。

由于我比较菜，所以这个口胡的思想由我来详细说明和实现。

- 题解

我们先将式子给拆解：

$in_{i_1}+(in_{i_2}-out_{i_1})+...+(in_{i_k}-out_{i_{k-1}})$

$=in_{i_k}+\sum_{p=1}^{k-1}(in_{i_p}-out_{i_p})$


题目要求这个式子尽可能小，也就是在$in_{i_k}$一定的时候，满足$\sum_{p=1}^{k-1}(in_{i_p}-out_{i_p})$尽可能小。

下面进入精彩的构造部分：

我们先加一个超级源点$S$，并且将这$n$个俄罗斯套娃按照 $in_i$ 从小到大排序。

此时我们可以将这些套娃以及该超级源放置在一个数轴上：

![](https://i.loli.net/2019/07/26/5d3b1022bd6da97415.png)

（不妨设$S$为0号点）
此时这些点满足性质 $0 = in_0 < in_1\le in_2 \le in_3 \le ... \le in_n$

然后，我们建立$n$条有向边，从节点 $i$ 到节点 $i+1$ 的边，权值为 $in_{i+1}-in_i$。

接着，我们设$up_i$表示第一个满足 $in_j$ 大于 $out_i$ 的 $j$，如果不存在$j$，就跳过。

建立一条从节点 $i$ 到节点 $up_i$ 的边，权值为$in_{jump_i}-out_i$。

![](https://i.loli.net/2019/07/26/5d3b11edade2c19071.png)

例如此图，$val_1=in_1-in_0,val_2=in_2-in_1,...,val_5=in_3-out_1,val6=in_4-out_2$

接下来，我们跑一遍以$S$为起点的最短路，维护到每个点的最短路条数即为答案。

为啥呢？

读者可以想象，如果这条路中，走了一些诸如图解中$1 - 4$的边，则代价为$\sum_{i=1}^{k}(in_i-in_{i-1})=in_k-in_0=in_k$，也就是表达式中孤零零提出来的$in_{k}$，

同时，我们走的路中，走了一些诸如图解中$5 - 6$的边，则代价为$\sum_{p=1}^{k-1}(in_{i_p}-out_{i_p})$

所以跑最短路是正确的！

我们记$dis_i$为从$S$点出发，到$i$的最短路，$cnt_i$为最短路条数，$min\_ dis = min \{dis_i \}, 1\le i\le n$

则答案为$\sum_{i=1}^{n} [dis_i = min\_ dis, out_i>in_n]\times cnt_i $

其中$in_n$表示最大套娃的$in$,加入布尔运算，是因为如果$out_i\le in_n$，则可以继续往外套娃，不符合题目要求。

同时，个人认为该方式求最短路条数不能用 $dijkstra$ 计算，因为边权可能为$0$，$dijkstra$遇到零权边，$dis_i$虽说不受影响，但$cnt_i$会出问题，
导致答案错误，不难构造出反例卡掉$dijkstra$。若读者有办法规避此类问题，欢迎在讨论版里指出做法。

考虑到每条边$(i,j)$满足性质$i<j$，所以该图为$DAG$，则考虑用拓扑，从节点 $i$ 尝试大于$i$的节点进行拓展延伸即可计数。

复杂度集中在排序的地方，之后的操作为$O(n)$。

总复杂度$O(nlogn)$，是个非常优秀，也非常妙的做法。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 200005;
struct Doll {
  int out, in;
  bool operator < (const Doll& b) const {
    return in < b.in;
  }
} a[N];

struct Edge {
  int to, nxt, val;
  Edge(int to = 0, int nxt = 0, int val = 0):
    to(to), nxt(nxt), val(val) {}
} edge[N << 1];
int head[N], tot;

void add(int u, int v, int val) {
  /*
  printf("*** new Edge!\n");
  printf("(%d -> %d, val = %d)\n", u, v, val);
  putchar('\n');
  */
  edge[++tot] = (Edge){v, head[u], val};
  head[u] = tot;
}

int n;

int Erfen(int x) {
  int l = 1, r = n;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (a[mid].in >= x) r = mid;
    else l = mid + 1;
  }
  if (a[l].in >= x) return l;
  else return -1;
}

const int mod = 1e9 + 7;
ll dis[N], cnt[N];
bool vis[N];

void topo() {
  memset(dis, 0x7f7f7f, sizeof(dis));
  memset(cnt, 0, sizeof(cnt));
  memset(vis, 0, sizeof(vis));
  cnt[0] = 1LL, dis[0] = 0LL;
  
  for (int i = 0; i <= n; i++) {
    for (int j = head[i]; j != -1; j = edge[j].nxt) {
      int v = edge[j].to;
      if (dis[v] > dis[i] + edge[j].val) {
        dis[v] = dis[i] + edge[j].val;
        cnt[v] = cnt[i];
      } else if (dis[v] == dis[i] + edge[j].val) {
        (cnt[v] += cnt[i]) %= mod;
      }
    }
  }
}

int main() {
  memset(head, -1, sizeof(head));
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].out, &a[i].in);
  }
  sort(a + 1, a + n + 1);
  /*
  printf("*** debug sort\n");
  for (int i = 1; i <= n; i++) {
    printf("%d-> (%d, %d)\n", i, a[i].out, a[i].in);
  } 
  printf("*** end, sort\n");
  */
  for (int i = 0; i < n; i++) {
    add(i, i + 1, a[i + 1].in - a[i].in);
  }
  for (int i = 1; i <= n; i++) {
    int up = Erfen(a[i].out);
    if (up == -1) continue;
    add(i, up, a[up].in - a[i].out);
  }
  topo();

  ll ans = 0LL, mindis = 1e15;
  for (int i = 1; i <= n; i++) {
    if (a[i].out > a[n].in)
      mindis = min(mindis, dis[i]);
  }
  
  for (int i = 1; i <= n; i++) {
    //printf("cnt[%d] = %lld\n", i, cnt[i]);
    //printf("dis[%d] = %lld\n", i, dis[i]);
    if (a[i].out > a[n].in && mindis == dis[i])
      (ans += cnt[i]) %= mod;
  }
  printf("%lld\n", ans);
  
  return 0;
}
```

- 尾记

这道题很神奇的被转化成了一道最短路计数题，相信都吓大家一跳。

没错，这种思路的确非常新颖独特，所以说 $\color{red}{Sooke}$ 实在是太强啦~

请读者认真思考，想想该方法的正确性。

烦请给该题解点个赞，举手之劳哈~

---

## 作者：Ynoi (赞：11)

比赛的时候想出了正解，没有调出来qwq

这是一个dp题

先将所有的matryoshkas 按照$out_i$排序

然后，定义$f_i$表示最外面用第$i$个matryoshkas，剩余的最小空间，$g_i$表示最小空间的方案数

则

$ f[i] = min(f[j] +in[i]- out[j]) (in[i] >= out[j])$

$ g[i] = \sum g[j] (in[i] >= out[j],f[i] = f[j] + in[i] - out[j])$

//$minout$表示所有out里面的最小值

//$maxin$表示所有in里面的最大值

$g[in[i] < minout] = 1$//因为要保证最里面不能再放下任何一个matryoshkas

设Anf为满足条件的最少剩余空间

$Anf = min(f[i])(out_i >= max in)$

Ans = $\sum_{out_i >= max in,Ans = Anf}{g_i}$//同理，要保证$i$外面不能放下任何一个matryoshkas

但是这样是$n^2$的，我们需要优化

$ f[i] = min(f[j] +in[i]- out[j]) $
 $= min(in[i] + f[j]-out[j])(in[i] >= out[j]) $

我们会发现，按照$out$排序后，满足条件$in[i] >= out[k]$的$j$肯定是$1$~$x$中（这个$x$可以二分答案）

而转移的时候一定是从最小的$f[j] - out[j]$转移来的

那么我们可以维护前缀$f[j] - out[j]$最小值

以及最小值的方案数之和


具体见代码
```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define pb push_back
#define int long long
#define pii pair<int,int>
#define fs first
#define it iterator
#define sd second
#define int long long 
#define INF (int)0x3f3f3f3f*(int)0x3f3f3f3f
#define mod 1000000007

int n,m,mo = INF,mi = 0;//mo ： minout ,mi maxin 
int f[MAXN],g[MAXN],s[MAXN],r[MAXN];
//s表示f[i] - out[i]的前缀最小值 
//r表示前缀最小值的方案数 （r[i] = Σg[j] (f[j] - out[j] == s[i])） 

struct aa {
	int i,o;//i:in o:out 
 } c[MAXN];
 int _o[MAXN];

bool cmp(aa a,aa b) { 
	return a.o < b.o || a.o == b.o && a.i < b.i;
}

void print(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}

void rd()
{
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> c[i].o >> c[i].i;
		mo = min(mo,c[i].o);
		mi = max(mi,c[i].i);
	}
	sort(c+1,c+n+1,cmp);
	for(int i = 1; i <= n; i ++)//o单独拿出来存储，便于二分 
		_o[i] = c[i].o;
}

signed main()
{
	rd();
	for(int i = 1; i <= n; i ++)  {
		if(c[i].i < mo)  g[i] = 1;
	}
	int anf = INF;
	for(int i = 1; i <= n; i ++) {
		
		int x = (int)(upper_bound(_o+1,_o+n+1,c[i].i) - 1- _o);
	 
		f[i] = s[x] + c[i].i;
		if(!g[i]) g[i] = r[x];
		
		
		int t = f[i] - c[i].o;
		if(t == s[i-1] && i != 1) {
			r[i] = g[i] + r[i-1];
			r[i] %= mod;
		} 
		else if(t < s[i-1] || i == 1) {
			r[i] = g[i]; 
		} else r[i] = r[i-1];
		
		s[i] = min(s[i-1],t);
		
		if(c[i].o > mi) anf = min(anf,f[i]);
		
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		if(c[i].o > mi && f[i] == anf) {
			ans += g[i];
		}
		ans %= mod;
	}
	cout<<ans<<"\n";
	return 0;
 } 
```




---

## 作者：_edge_ (赞：6)

现在是深夜 $21:52$，后天就是 NOIP 了，然而我是 ZJ 的初中生去不了，愿所有去 NOIP 的都能取的自己理想的成绩。

不是很难的一个题。

看到这种 $out_i \le in_j$ 这种偏序关系，基本可以确定它大概是 DP。

我们需要从中找出一个比较好的结构来 DP，这样我们处理起来会没有后效性。

然后我们就尝试按 $in$ 进行排序，发现排序过后，对于一个 $i$ 而言，如果 $in_i<in_j$ 那么必然有 $in_i<out_j$，也就是说，$j$ 在 $i$ 后面必定不会有 $j$ 到 $i$ 的这种转移了！

我们很好的找到了一个最优子结构，然后的事情就是非常非常简单的 DP。

~~各位都来做 $2300$ 了，那这种 DP 应该就不用我说了吧。~~

还是提一下，就是 $f_i=\min \limits _{1\le j <i} f_j-out_i+in_j$。

然后大力转移即可，于是我们得到了下面这个 $O(n^2)$ 的代码。

```cpp
// LUOGU_RID: 95327039
#include <bits/stdc++.h>
#define int long long
#define pb push_back 
using namespace std;
const int Mod=1e9+7;
const int INF=1e5+5;
struct _node_data{
	int in,out;
}aa[INF];
int n,f[INF],f1[INF];
void solve() {
	cin>>n;int Max=0;
	for (int i=1;i<=n;i++)
		cin>>aa[i].out>>aa[i].in,Max=max(Max,aa[i].in);
	
	sort(aa+1,aa+1+n,[](_node_data xx,_node_data yy){return xx.in<yy.in;});
	for (int i=1;i<=n;i++) f[i]=aa[i].in,f1[i]=1;
	
//	for (int i=1;i<=n;i++)
//		cout<<aa[i].in<<" "<<aa[i].out<<" end\n";
	
	for (int j=1;j<=n;j++) {
		for (int i=1;i<j;i++)
			if (aa[i].out<=aa[j].in) {
				
				if (f[j]>f[i]-aa[i].out+aa[j].in) {
//					cout<<i<<" -> "<<j<<" this?\n";
					f[j]=f[i]-aa[i].out+aa[j].in;
					f1[j]=f1[i];
				}
				else if (f[j]==f[i]-aa[i].out+aa[j].in) {
					f1[j]+=f1[i],f1[j]%=Mod;
//					cout<<i<<" -> "<<j<<" this two?\n";
				}
			}
	}
	
	int ans=1e18,ans1=0;
	for (int i=1;i<=n;i++) {
		if (aa[i].out>Max) ;
		else continue;
//		cout<<i<<" "<<f[i]<<" "<<f1[i]<<" "<<aa[i].in<<" "<<aa[i].out<<" wemhao?\n";
		if (f[i]<ans) ans=f[i],ans1=f1[i];
		else if (ans==f[i]) ans1+=f1[i];
		ans1%=Mod;
	}
	cout<<ans1<<"\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	int t=1;
	while (t--) solve();
	return 0;
}
```

然后这种 DP 转移的地方大部分都可以优化。

对于这一类，相当于是数它前面比它小的数，数最小值。

如果碰到过类似偏序问题，应该都知道这是一道二维偏序问题。

于是我们随手扔上去一个树状数组就做完了。

时间复杂度 $O(n \log n)$。

有不懂可以私信我。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back 
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int Mod=1e9+7;
const int INF=5e5+5;
struct _node_data{
	int in,out;
}aa[INF];
int n,f[INF],f1[INF],tree[INF],tree1[INF];
vector <int> cnt;
int Get(int x) {return lower_bound(cnt.begin(),cnt.end(),x)-cnt.begin()+1;}
void add(int x,int y,int z) {
	for (int i=x;i<=5e5;i+=i&-i) 
		if (tree[i]>y) {tree[i]=y;tree1[i]=z,tree1[i]%=Mod;}
		else if (tree[i]==y) tree1[i]+=z,tree1[i]%=Mod;
	return ;
}
pii query(int x) {
	pii it={1e18,0};
	for (int i=x;i;i-=i&-i) {
		if (tree[i]<it.fi) it.fi=tree[i],it.se=tree1[i];
		else if (tree[i]==it.fi) it.se+=tree1[i],it.se%=Mod;
	}
	return it;
}
void solve() {
	memset(tree,63,sizeof tree);
	cin>>n;int Max=0;
	for (int i=1;i<=n;i++)
		cin>>aa[i].out>>aa[i].in,
		Max=max(Max,aa[i].in),cnt.pb(aa[i].out),cnt.pb(aa[i].in);
	
	sort(aa+1,aa+1+n,[](_node_data xx,_node_data yy){return xx.in<yy.in;});
	for (int i=1;i<=n;i++) f[i]=aa[i].in,f1[i]=1;
	sort(cnt.begin(),cnt.end());
	cnt.erase(unique(cnt.begin(),cnt.end()),cnt.end());
	
	for (int j=1;j<=n;j++) {
//		for (int i=1;i<j;i++)
//			if (aa[i].out<=aa[j].in) {
//				
//				if (f[j]>f[i]-aa[i].out+aa[j].in) {
//					f[j]=f[i]-aa[i].out+aa[j].in;
//					f1[j]=f1[i];
//				}
//				else if (f[j]==f[i]-aa[i].out+aa[j].in) {
//					f1[j]+=f1[i],f1[j]%=Mod;
//				}
//			}
		pii i=query(Get(aa[j].in));
//		cout<<i.fi<<" "<<i.se<<" fad?\n";
		if (f[j]>i.fi+aa[j].in) 
			f[j]=i.fi+aa[j].in,f1[j]=i.se;
		else if (f[j]==i.fi+aa[j].in)
			f1[j]+=i.se,f1[j]%=Mod;
		add(Get(aa[j].out),f[j]-aa[j].out,f1[j]);
		
	}
	
	int ans=1e18,ans1=0;
	for (int i=1;i<=n;i++) {
		if (aa[i].out>Max) ;
		else continue;
		if (f[i]<ans) ans=f[i],ans1=f1[i];
		else if (ans==f[i]) ans1+=f1[i];
		ans1%=Mod;
	}
	cout<<ans1<<"\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	int t=1;
	while (t--) solve();
	return 0;
}
```


---

## 作者：renhr2002 (赞：4)

实际上，这篇题解的建图方式和其他题解没有什么区别，就是对建图的理解有所不同，就来HFO一发吧。

建图方式为：

1. 加上超级源点0；
2. 将套娃按照内径从小到大排序，对于套娃0~n-1，建边i->i+1，权值为两个套娃的内径差；
3. 对于1~n-1，找到排序后编号最小的套娃j（如果不存在，则跳过），建边i->j，权值为j的内径减去i的内径。

但明显这样建图会T。这时，我们发现，第3部建图时，就是在一个序列中每次插入一个元素，再查找满足条件的第一个点，加上个SGT优化建图，再跑一遍最短路计数即可。

我对建图方式的理解：

1. 在最短路中跑了一些i->j的边，表示把j套在i的外面；
2. 最短路中跑了一些i->i+1的边，表示用i+1去替换i。

std如下：

```cpp
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
#define mod 1000000007
#define maxn 204800
char str;
int n;
struct point
{
	int a,b;
	friend bool operator < (point A,point B)
	{
		return A.b<B.b;
	}
}p[maxn];
ll tr[4*maxn];
struct edge
{
	int to;
	int nxt;
	ll val;
}nd[2*maxn];
int head[maxn],cnt;
int inval[maxn];
ll dist[maxn],num[maxn];
queue<int>q;
template<class X> inline void read(X &x)
{
	x=0;
	X f=1;
	while(!isdigit(str))
	{
		if(str=='-')
		{
			f=-1;
		}
		str=getchar();
	}
	while(isdigit(str))
	{
		x*=10;
		x+=str-'0';
		str=getchar();
	}
	x*=f;
	return;
}
void init()
{
	memset(head,-1,sizeof(head));
	memset(dist,0x3f,sizeof(dist));
	cnt=1;
	return;
}
void pushup(int x)
{
	tr[x]=max(tr[x<<1],tr[x<<1|1]);
	return;
}
void addt(int x,int l,int r,int rt,ll z)
{
	if(l==r)
	{
		tr[rt]=z;
		return;
	}else
	{
		int mid=(l+r)>>1;
		if(x<=mid)
		{
			addt(x,l,mid,rt<<1,z);
		}else
		{
			addt(x,mid+1,r,rt<<1|1,z);
		}
		pushup(rt);
	}
	return;
}
int query(int l,int r,int rt,ll z)
{
	if(l==r)
	{
		return l;
	}else
	{
		int mid=(l+r)>>1;
		if(tr[rt<<1]>=z)
		{
			return query(l,mid,rt<<1,z);
		}else
		{
			return query(mid+1,r,rt<<1|1,z);
		}
	}
}
void add(int x,int y,ll z)
{
	nd[cnt].to=y;
	nd[cnt].nxt=head[x];
	nd[cnt].val=z;
	head[x]=cnt++;
	inval[y]++;
	return;
}
void bfs()
{
	for(int i=0;i<=n;i++)
	{
		if(!inval[i])
		{
			q.push(i);
			dist[i]=0;
			num[i]=1;
		}
	}
	while(q.size())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i!=-1;i=nd[i].nxt)
		{
			int t=nd[i].to;
			inval[t]--;
			if(!inval[t])
			{
				q.push(t);
			}
			if(dist[t]>dist[x]+nd[i].val)
			{
				dist[t]=dist[x]+nd[i].val;
				num[t]=num[x];
			}else if(dist[t]==dist[x]+nd[i].val)
			{
				num[t]+=num[x];
				num[t]%=mod;
			}
		}
	}
	return;
}
int main()
{
	init();
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(p[i].a),read(p[i].b);
	}
	sort(p+1,p+n+1);
	addt(n,1,n,1,p[n].b);
	for(int i=n-1;i;i--)
	{
		add(i,i+1,p[i+1].b-p[i].b);
		if(tr[1]>=p[i].a)
		{
			int t=query(1,n,1,p[i].a);
			add(i,t,p[t].b-p[i].a);
		}
		addt(i,1,n,1,p[i].b);
	}
	add(0,1,p[1].b);
	bfs();
	ll ans=0,mi=0x3f3f3f3f3f3f3f3fll;
	for(int i=1;i<=n;i++)
	{
		if(p[i].a>p[n].b)
		{
			mi=min(mi,dist[i]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(p[i].a>p[n].b&&dist[i]==mi)
		{
			ans+=num[i];
			ans%=mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

一遍过编过样例 AC，爽。
### 题意
给定 $n$ 个套娃，有内部体积和外部体积，求**极长**套娃链的剩余空间取到 $\min$ 的方案数。
### 分析
容易发现套娃之间形成一个 DAG。

于是考虑直接按照外部体积排序，相当于在拓扑序上转移一个 DP 求方案数，容易发现最小值和方案数组成的 pair 是半群，是可以平凡合并的。

然后一个套娃能包含的所有套娃在排完序以后是个前缀，二分出这个前缀的位置，查询前缀合并出来的信息可以上个 sgt。注意我们在把信息插入 sgt 时要把外部体积减掉，这样查询的时候真实的剩余空间就只需要加上当前套娃的内部体积，可以最后再加不改变序关系。然后一种特殊的转移是单独成一种方案，因为要求方案极长，所以只能在当前套娃无法包含任何一个时才加入这种转移。

最后答案只需要把所有不能被别人包含的（因为要求极长）套娃 DP 出来的信息合并就可以了，时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int> 
#define fir first
#define sec second
#define mkpr make_pair
#define arr(x) array<int,x>
inline int read(){
	int x=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
bool getmn(int &x,int y){if(x>y)return x=y,1;return 0;}
bool getmx(int &x,int y){if(x<y)return x=y,1;return 0;}
mt19937 rnd(time(NULL));
const int maxn=2e5+5;
const int mod=1e9+7;
void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int n;
int _a[maxn],_b[maxn];
int p[maxn];
int a[maxn],b[maxn];
struct Data{
	int mn,val;
	Data(int m=0,int v=0){mn=m,val=v;}
	Data operator + (const Data &b) const{
		Data z;
		z.mn=min(mn,b.mn);
		if(z.mn==mn) add(z.val,val);
		if(z.mn==b.mn) add(z.val,b.val);
		return z;
	}
}dp[maxn];
class Segment_Tree{
#define ls (o<<1)
#define rs (o<<1|1)
private:
	Data tr[maxn<<2];
	void pushup(int o){tr[o]=tr[ls]+tr[rs];}
public:
	void update(int o,int l,int r,int x,Data k){
		if(l==r) return tr[o]=k,void();
		int m=(l+r)>>1;
		if(x<=m) update(ls,l,m,x,k);
		else update(rs,m+1,r,x,k);
		pushup(o);
	}
	Data query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return tr[o];
		int m=(l+r)>>1;
		if(x<=m&&y>m) return query(ls,l,m,x,y)+query(rs,m+1,r,x,y);
		if(x<=m) return query(ls,l,m,x,y);
		return query(rs,m+1,r,x,y);
	}
}sgt;
signed main(){	
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++) _a[i]=read(),_b[i]=read(),p[i]=i;
	sort(p+1,p+n+1,[&](int x,int y){return _a[x]<_a[y];});
	for(int i=1;i<=n;i++) a[i]=_a[p[i]],b[i]=_b[p[i]];
	for(int i=1;i<=n;i++){
		int pos=upper_bound(a+1,a+n+1,b[i])-a-1;
		if(pos>=1) dp[i]=sgt.query(1,1,n,1,pos),dp[i].mn+=b[i];
		else dp[i]=Data(b[i],1);
		dp[i].mn-=a[i];sgt.update(1,1,n,i,dp[i]);dp[i].mn+=a[i];
	}
	int mx=0;
	for(int i=1;i<=n;i++) getmx(mx,b[i]);
	Data ans(inf,0);
	for(int i=1;i<=n;i++) if(a[i]>mx) ans=ans+dp[i];
	cout<<ans.val<<'\n';
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

## 作者：TheShadow (赞：0)

# CF1197E Culture Code

## Solution

假如我们将套娃 $a$ 套进套娃 $b$ 中，那么我们得到的空气的体积（？？？）即为 $in_b-out_a$ 。

$a$ 能作为最外层的条件是 $\forall i\in [1,n],out_a>in_i$ 。

$a$ 能作为最内层的条件是 $\forall i\in [1,n],in_a<out_i$ 。（否则将满足条件的 $i$ 加入一定会使答案更优）

将每一个 $a$ 能包含 $b$ ，我们可以将其看做一条由 $a$ 连向 $b$ 的边权为 $in_a-out_b$ 的边。

又因为要空气的体积之和最小，那么我们就相当于是要求我们得到的图的最短路的数量。

但是我们直接连边的话，需要 $n^2$ 扫描一遍，时间上无法接受，所以我们需要优化。

### 方法一：线段树优化连边

我们先按照 $out$ 排序，那么每一个点都会向一段区间连边。这是我们可以像线段树一样，将这一个区间分为 $\log$ 段，然后再连边。这样我们就可以做到 $O(n\log n)$ 连边了。

### 方法二：DP

考虑我们最短路的松弛操作： $dis_u=min(dis_v+in_u-out_v)$ 。

将 $in_u$ 提出，那么我们需要维护的就是所有满足条件的点中， $dis_v-out_v$ 的最小值。

我们先将所有点按照 $out$ 从小到大排序，那么我们对每一个点，我们需要查询的都是一个前缀。

我们注意到一个事实，对于任意一个点 ，满足 $out>in$ 。

那么我们按照 $in$ 从小到大的顺序来处理，合法的，可以用来更新的区间，一定是不会变短的，这样我们就只需要维护一个最小值即可。

至于最短路计数问题，大家应该都会，就不再多说了。（不会的同学可以自行百度搜索）。

## Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class cnt>il read(cnt &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 2e5+5,mod = 1e9+7;
int n,mx,ans,a[MAXN],b[MAXN],cnt[MAXN],dis[MAXN],mn=INT_MAX;
struct Node{
	int x,y;
}node[MAXN];
it max(int x,int y){return x>y?x:y;}
it add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inl bool cmp1(int i,int j){return node[i].x<node[j].x;}
inl bool cmp2(int i,int j){return node[i].y<node[j].y;}
int main(){
//	freopen("easy.in","r",stdin);
//	freopen("easy.out","w",stdout);
	read(n);
	for(ri i=1;i<=n;++i) read(node[i].x),read(node[i].y),mx=max(mx,node[i].y),a[i]=b[i]=i;
	sort(a+1,a+1+n,cmp1); // 按照外层排序
	sort(b+1,b+1+n,cmp2); // 按照内层排序
	// DP方程：dis[x]=min(dis[y]-out[y])+in[x] 
	for(ri i=1,j=1,tt=1;i<=n;++i){
        // i 表示更新到了第几个， j 表示用来更新的区域已经拓展到了哪儿， tt 表示当前最小值对应的最短路数目
		ri id1=b[i];cnt[id1]=1;
		while(j<=n&&node[a[j]].x<=node[id1].y){ // 找到所有能更新 i 的 y
			ri id2=a[j++],x=node[id2].x;
			if(dis[id2]-x<mn) mn=dis[id2]-x,tt=cnt[id2];
			else if(dis[id2]-x==mn) tt=add(tt,cnt[id2]);
		}
		dis[id1]=node[id1].y+mn;
		cnt[id1]=tt;
	}
	// 最后统计答案
	mn=INT_MAX;
	for(ri i=n;i;--i){
		if(node[a[i]].x<=mx) break;
		if(dis[a[i]]<mn) mn=dis[a[i]],ans=cnt[a[i]];
		else if(dis[a[i]]==mn) ans=add(ans,cnt[a[i]]);
	}
	print(ans);
	return 0;
}
```

# 总结

还是太菜了~~特别是语文~~，甚至没想到最短路计数~~虽然最开始想到最那么一下~~，线段树连边这些操作也都还没学过，要更加努力才行。

---

## 作者：redegg (赞：0)

自己瞎想的$O(NlogN)$做法。（为什么那种难度提高-或者提高的一定要变成省选++？）

是这样的，假定我们现在有一个套娃在手上，桌子上有一堆套娃，并且我们都可以把这些套娃装进手里的这个套娃里，我们该怎么选择？

肯定是选择实心体积最大的那个对吧！

所以我瞎想到，把内径和外径同时在同一个序列里面排序，但是要标注这个是内径还是外径，并且满足一下三个规则：

1. 数值小的在前，大的在后。
2. 数值相同但是不是同一个套娃的情况下，外径排在内径前。
3. 数值相同且是同一个套娃，内径排在外径前。

这样可以保证一点，在前面的外径所属的套娃是一定可以被套到在后面的内径所属的套娃里面的。

剩下的，我们记录一个$maxn$表示现在最大的实心体积套娃组的实心体积。记录一个$maxa$表示现在组成这个实心体积套娃组的方案数。

除此之外，我们还要对每个套娃记录一个实心体积$v[i]$，初始值$v[i]=out[i]-in[i]$，后面$v[i]$会被计算成以$i$号套娃为最外层的最大实心体积。以及对每个套娃记录一个方案量$g[i]$，表示以$i$号套娃为最外层时实心体积最大时的方案数。

那么我们从$1$做到$2\times n$（内径与外径的个数之和），如果第$i$个数是内径，我们就把$maxn$加到这个内径所对应的套娃的$v$里面，同时把$maxa$乘到$g$里面。如果第$i$个数是外径，那么我们就把外径相应的套娃的$v$和$maxn$做对比，相等就把$g$加入$maxa$，大于的话就直接用$v$和$g$替换$maxn$和$maxa$。

最后计算答案很简单，我们倒着枚举这$2n$个内外径，到第一个内径时退出，为什么？因为要保证最外层的外径不会小于任何一个内径不然的话不符合题意。

答案计算详细见代码最后。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int mod=1e9+7;

int n;

int a[400005];
int b[400005];
int v[400005];
long long g[400005];

int cnt;
struct ha
{
    int h,c,id;
}q[400005];

bool cmp(const ha &aa,const ha &bb)
{
    if(aa.h!=bb.h)return aa.h<bb.h;
    if(aa.id!=bb.id)return aa.c<bb.c;
    return aa.c>bb.c;
}
int maxn;
int maxa;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&b[i],&a[i]);

    for(int i=1;i<=n;i++)
    {
        v[i]=b[i]-a[i];
        g[i]=1;
        cnt++;
        q[cnt].h=b[i];
        q[cnt].c=1;
        q[cnt].id=i;
        cnt++;
        q[cnt].h=a[i];
        q[cnt].c=2;
        q[cnt].id=i;
    }

    sort(q+1,q+1+cnt,cmp);
    maxa=1;
    for(int i=1;i<=cnt;i++)
    {
        if(q[i].c==1)
        {
            if(maxn==v[q[i].id])maxa=(maxa+g[q[i].id])%mod;
            if(maxn<v[q[i].id])
            {
                maxa=g[q[i].id];
                maxn=v[q[i].id];
            }
        }
        else{
            g[q[i].id]=(g[q[i].id]*maxa)%mod;
            v[q[i].id]+=maxn;
        }
    }
    long long ans=0;
    int minn=1e9;
    for(int i=cnt;i>=1;i--)
    {
        if(q[i].c==2)break;
        if(minn>b[q[i].id]-v[q[i].id])
            minn=b[q[i].id]-v[q[i].id],ans=0;
        if(minn==b[q[i].id]-v[q[i].id])
            ans=(ans+g[q[i].id])%mod;

    }
    printf("%lld\n",ans);
    return 0;
}

```


---

