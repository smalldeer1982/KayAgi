# Gold Transfer

## 题目描述

You are given a rooted tree. Each vertex contains $ a_i $ tons of gold, which costs $ c_i $ per one ton. Initially, the tree consists only a root numbered $ 0 $ with $ a_0 $ tons of gold and price $ c_0 $ per ton.

There are $ q $ queries. Each query has one of two types:

1. Add vertex $ i $ (where $ i $ is an index of query) as a son to some vertex $ p_i $ ; vertex $ i $ will have $ a_i $ tons of gold with $ c_i $ per ton. It's guaranteed that $ c_i > c_{p_i} $ .
2. For a given vertex $ v_i $ consider the simple path from $ v_i $ to the root. We need to purchase $ w_i $ tons of gold from vertices on this path, spending the minimum amount of money. If there isn't enough gold on the path, we buy all we can.

If we buy $ x $ tons of gold in some vertex $ v $ the remaining amount of gold in it decreases by $ x $ (of course, we can't buy more gold that vertex has at the moment). For each query of the second type, calculate the resulting amount of gold we bought and the amount of money we should spend.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query, so don't forget to flush output after printing answers. You can use functions like fflush(stdout) in C++ and BufferedWriter.flush in Java or similar after each writing in your program. In standard (if you don't tweak I/O), endl flushes cout in C++ and System.out.println in Java (or println in Kotlin) makes automatic flush as well.

## 说明/提示

Explanation of the sample:

At the first query, the tree consist of root, so we purchase $ 2 $ tons of gold and pay $ 2 \cdot 2 = 4 $ . $ 3 $ tons remain in the root.

At the second query, we add vertex $ 2 $ as a son of vertex $ 0 $ . Vertex $ 2 $ now has $ 3 $ tons of gold with price $ 4 $ per one ton.

At the third query, a path from $ 2 $ to $ 0 $ consists of only vertices $ 0 $ and $ 2 $ and since $ c_0 < c_2 $ we buy $ 3 $ remaining tons of gold in vertex $ 0 $ and $ 1 $ ton in vertex $ 2 $ . So we bought $ 3 + 1 = 4 $ tons and paid $ 3 \cdot 2 + 1 \cdot 4 = 10 $ . Now, in vertex $ 0 $ no gold left and $ 2 $ tons of gold remain in vertex $ 2 $ .

At the fourth query, we add vertex $ 4 $ as a son of vertex $ 0 $ . Vertex $ 4 $ now has $ 1 $ ton of gold with price $ 3 $ .

At the fifth query, a path from $ 4 $ to $ 0 $ consists of only vertices $ 0 $ and $ 4 $ . But since no gold left in vertex $ 0 $ and only $ 1 $ ton is in vertex $ 4 $ , we buy $ 1 $ ton of gold in vertex $ 4 $ and spend $ 1 \cdot 3 = 3 $ . Now, in vertex $ 4 $ no gold left.

## 样例 #1

### 输入

```
5 5 2
2 0 2
1 0 3 4
2 2 4
1 0 1 3
2 4 2```

### 输出

```
2 4
4 10
1 3```

# 题解

## 作者：忘怀星 (赞：7)

>比较简单的一道题，如果发现了特点的话……

特点是什么？就是 **It's guaranteed that  $p_i$  exists and  $c_i > c_{p_i}$** 。也就是说我们可以贪心的认为取越靠近根的越好。

那么就简单了，可以考虑当前到根的链上最靠上的非空节点是哪一个，然后去处理该节点。要是把它掏空了，则再找下一个非空节点，否则的话询问结束。

如何找最靠上的非空节点呢？我们可以使用倍增，理由很简单，因为使用倍增的话在线加入新节点会很方便。

那么复杂度呢？看起来这么暴力的算法如何保证复杂度呢？

考虑每一次处理节点。要不就是把节点掏空，要不就是结束了一次询问。而我们知道询问与节点数量之和为 $n$ 。每次找非空节点复杂度为 $logn$ ，所以可以证明总复杂度为 $nlogn$ 。

code：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <unordered_map>

#define int long long
using namespace std;

int read()
{
	int a = 0,x = 1;char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9') {a = a*10 + ch-'0';ch = getchar();}
	return a*x;
}
const int N=1e6+7,P=1e9+7,M=1e6+7;
int fpow(int a,int x)
{
	if(x == 1) return a;
	if(x == 0) return 1;
	int t = fpow(a,x/2);
	if(x&1) return t*t%P*a%P;
	else return t*t%P;
}

int n,a[N],c[N],fa[N][20];
int get(int u)
{
	for(int i = 19;i >= 0;i --) if(a[fa[u][i]]) u = fa[u][i];
	return u;
}
signed main()
{
	n = read(),a[1] = read(),c[1] = read();
	for(int i = 2;i <= 1+n;i ++) {
		int op = read();
		if(op == 1) {
			fa[i][0] = read()+1,a[i] = read(),c[i] = read();
			for(int j = 1;j < 20;j ++) fa[i][j] = fa[fa[i][j-1]][j-1];
		} else {
			int v = read()+1,tmp , w = read(),ans = 0;
			tmp = w;while(a[v] && w) {
				int x = get(v);
				if(w > a[x]) {
					w -= a[x],ans += a[x]*c[x];
					a[x] = 0;
				} else {
					a[x] -= w,ans += w*c[x];
					w = 0;
				}
			}
			printf("%lld %lld\n",tmp-w,ans);
		}
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：wfc284 (赞：1)

$3 \times 10 ^ 5 $ 的数据，多半是 $O(n \log n)$ 了。  
问题来了：那个 log 怎么来的？  
于是想到了倍增。  
他有一个很好的性质：后代的单价永远大于祖先。据此直接贪心。  
每加一个点，就处理出它的 $2^c$ 级祖先。  
对于每一个询问，直接往最上面跳，直到遇到一个被买完的。直接加上对应的价钱即可。  
时间复杂度分析：每个结点最多被买完一次。每次找结点复杂度为 $O(\log n)$。总复杂度 $O(n \log n)$。
### Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
#define int long long
using namespace std;
const int N = 3e5+2;

int q, a[N], c[N];
int anc[N][20];

int get(int u) {
	for(re int k = 19; k >= 0; --k)
		if(a[anc[u][k]]) u = anc[u][k];
	return u;
}

signed main() {
	cin >> q >> a[1] >> c[1];
	for(re int i = 2, opt, p, u, w; i <= q+1; ++i) {
		scanf("%lld", &opt);
		if(opt == 1) {
			scanf("%lld%lld%lld", &p, &a[i], &c[i]), ++p;
			anc[i][0] = p;
			for(re int c = 1; c <= 19; ++c) anc[i][c] = anc[anc[i][c-1]][c-1];
		}
		else {
			scanf("%lld%lld", &u, &w), ++u;
			int tot = 0. tot_price = 0;
			while(a[u] && w) {
				int x = get(u);
				if(a[x] < w) {
					tot += a[x], tot_price += a[x] * c[x];
					w -= a[x], a[x] = 0;
				}
				else {
					tot += w, tot_price += w * c[x];
					a[x] -= w;
					break;
				}
			}
			printf("%lld %lld\n", tot, tot_price);
			fflush(stdout);
		}
	}
	return 0;
}
```

---

## 作者：wrzSama (赞：1)

## 题意

本题强制在线，请在**处理完每次询问之后**再继续读入数据，同时也请注意刷新缓冲区。
给定一个初始只有一个根节点（编号为 $0$）的有根树，第 $i$ 个节点有 $a_i$ 块金子，在该节点上每块金子价格均为 $c_i$。
你需要维护这棵树，处理 $q$ 次操作，操作有两种，具体的：

1. 假设这是第 $i$ 次操作，给定整数 $p_i,a_i,c_i$。你需要创建一个节点 $i$ 使得节点 $p_i$ 是节点 $i$ 的父节点，且拥有 $a_i$ 块金子，每块有价格 $c_i$。**我们保证 $c_i\gt c_{p_i}$ 成立。**
2. 给定整数 $v_i,w_i$，你需要从节点 $v_i$ 到节点 $0$ 的所有节点上买正好 $w_i$ 块金子，且总价格最小。输出买到的金子数和最小总价格。**注意，如果路径中没有足够金子的话，你需要买下路径上的所有金子。**
   $1\leq q\leq3\times10^5;1\leq a_0,c_0\lt10^6;$
   对于操作一：$0\leq p_i\lt i;1\leq a_i,c_i\lt10^6;c_i\gt c_{p_i};$
   对于操作二：$0\leq v_i\lt i;1\leq w_i\lt10^6;$ 且节点 $v_i$ 一定存在。
   我们还保证，一定至少有一次操作二。

## 思路

我们发现每一次购买黄金都会将这条链上的一些节点（可能为 $0$ 个节点)上的所有黄金全部买走，并买走一个节点上的部分黄金（可能为 $0$ 块）。每个节点只会被 $1$ 次购买买走剩余的全部黄金，而买走一个节点的部分黄金的情况每次购买只会出现 $1$ 次，所以我们完全可以在 $O(q)$ 的时间复杂度内买走每次购买需要买的黄金。下面，我们考虑每次购买应该买哪些节点上的黄金。因为子节点的黄金价格严格贵于父节点的黄金价格，所以我们可以倍增找到这条链上根节点下第 $1$ 个黄金数量不为 $0$ 的节点开始买，如果数量不够就继续找它下面的第一个节点开始买。因为每次购买都是从上往下买的，所以如果一个节点的父节点的黄金数量不为 $0$，那么它的黄金数量一定不为 $0$。所以我们找到第 $1$ 个黄金数量不为 $0$ 的后访问到的每一个节点都是会被买黄金的节点，这样令时间复杂度得以保证。总时间复杂度 $O(n \log_n)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int q,d[300005],a[300005],fa[300005][20];
ll c[300005];
inline int find(int x,int len)
{
	for(int i=19;i>=0;--i)
	{
		if(len&(1<<i))
		{
			len^=(1<<i);
			x=fa[x][i];
		}
	}
	return x;
}
int main()
{
	q=read();
	a[1]=read();
	c[1]=read();
	for(int i=2;i<=q+1;++i)
	{
		int op=read();
		if(op==1)
		{
			fa[i][0]=read()+1;
			d[i]=d[fa[i][0]]+1;
			for(int j=1;j<20;++j) fa[i][j]=fa[fa[i][j-1]][j-1];
			a[i]=read();
			c[i]=read();
		}
		else
		{
			int v=read()+1,w=read(),x=v,y=w;
			for(int j=19;j>=0;--j) if(a[fa[x][j]]) x=fa[x][j];
			int tmp=min(w,a[x]);
			ll ans=tmp*c[x];
			w-=tmp;
			a[x]-=tmp;
			while(w&&x!=v)
			{
				x=find(v,d[v]-d[x]-1);
				tmp=min(w,a[x]);
				w-=tmp;
				a[x]-=tmp;
				ans+=tmp*c[x]; 
			}
			write(y-w);
			putchar(' ');
			write(ans);
			cout<<'\n';
			fflush(stdout);
		}
	}
	return 0;
}
```


---

## 作者：wheneveright (赞：1)

## 分析

看到条件 $c_i>c_{p_i}$ ,可以直接贪心，尽量买靠近根节点的金子就好了

操作一：
		添加一个节点 $i$,注意 $i=$ 总操作数，还包括操作 $2$ 的个数。

对于每一个节点，开三个数组分别存它的父亲，剩余金子个数与金子单价

```cpp
void add_node(int fi,int ai,int vi)
{
	val[cnt]=vi;
	fa[cnt]=fi;
	a[cnt]=ai;
	cnt++;	
}
```

操作二：

在存入时建一个临时变量，存下 $need=w_i$

从 $p=v_i$ 开始：

对于一个非根节点，首先先递归调用父节点，这样首先选择的就是根节点,

然后对当前节点进行处理，分两种情况：

1. $a_i>need$
   1. $ans+=need \times val_p$
   2. $a_i-=need$
   3. $need=0$
2. $a_i\le need$ 
   1. $ans+=a_i\times v_i$
   2. $need-=a_i$
   3. $a_i=0$

最后买下的就是 $w_i-need$,花的钱就是 $ans$。

核心代码：

```cpp
void update_buy(int p)
{ 
	if(fa[p]!=p) update_buy(fa[p]);//不是根,优买父节点 
	if(need) //还需要买的数量
	{
		if(a[p]>need)
		{
			a[p]-=need;
			ans+=v[p]*need;
			need=0;
		}//case 1
		else
		{
			need-=a[p];
			ans+=a[p]*v[p];
			a[p]=0;
		}//case 2
	}
}
```

---

## 作者：Little09 (赞：0)

普及组难度树上倍增题。

我们只需要做到以下内容（在线），就能完成本题：

1. 添加一个点 $x$；
2. 查询一个点 $x$ 所在树的根；
3. 删除一个点 $x$，$x$ 是一棵树的根。

如果能做到以上三点，那么对于操作 $1$ 就添加，对于操作 $2$ 就不停地查询根，如果能买黄金就买，买完以后删除，然后计算即可。

删除很难，考虑给已删除的点打一个标记。于是查询的时候，倍增往上跳到第一个没有打标记的点，它一定就是要查询的根。所以在添加点的时候就可以把倍增预处理好。

记得 `fflush(stdout)`。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x) memset(x,0,sizeof(x))
//const ll inf=1000000000000000000; 

const int N=300005;
int q;
ll a[N],c[N];
int lg[N];
bool used[N];
int fath[N][21],depth[N];
void dfs(int u,int fa)
{
	depth[u]=depth[fa]+1;
	fath[u][0]=fa;
	for (int i=1;i<=lg[depth[u]];i++)
	{
		fath[u][i]=fath[fath[u][i-1]][i-1];
	}
}

inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 

int ask(int x)
{
	for (int i=lg[depth[x]];i>=0;i--)
    {
    	if (used[fath[x][i]]==0) 
    	{
    		x=fath[x][i];
    	}
    }
    return x;
}

int main()
{
	q=read(),a[0]=read(),c[0]=read();
	for (int i=1;i<=300000;i++) 
	{
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	}
	for (int i=1;i<=300000;i++) 
	{
		lg[i]--;
	}
	for (int i=1;i<=q;i++)
	{
		int tp=read();
		if (tp==1)
		{
			int p=read();
			a[i]=read(),c[i]=read();
			dfs(i,p);
		}
		else
		{
			ll v=read(),w=read();
			ll ans=0;
			ll ww=w;
			while (1)
			{
				int r=ask(v);
				if (used[r]) break;
				if (w>=a[r])
				{
					used[r]=1;
					w-=a[r];
					ans+=a[r]*c[r];
					a[r]=0;
				}
				else
				{
					a[r]-=w;
					ans+=w*c[r];
					w=0;
					break;
				}
			}
			printf("%lld %lld\n",ww-w,ans);
			fflush(stdout);
		}
	}
	return 0;
}

```


---

