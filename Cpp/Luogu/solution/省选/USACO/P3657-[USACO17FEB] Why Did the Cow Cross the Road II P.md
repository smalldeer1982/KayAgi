# [USACO17FEB] Why Did the Cow Cross the Road II P

## 题目背景

*本题与 [金组同名题目](/problem/P6119) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 饲养了 $N$ 种奶牛，编号从 $1$ 到 $N$。一些品种的奶牛和其他奶牛间相处良好，事实证明，如果两个品种的奶牛编号分别为 $a,b$，当 $|a-b| \leq 4$ 时，这两个品种的奶牛能友好相处，否则不能友好相处。

一条长长的道路贯穿整个农场，道路的左侧有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场），道路的右侧也有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场）。为了让奶牛们安全穿过马路，Farmer John 希望能在马路上画出一些人行道（牛行道？），要求这些人行道满足如下条件：

1. 人行道从左侧的某个牧场出发，连接到右侧的某个牧场；
2. 人行道连接的两个牧场的奶牛要能友好相处；
3. 人行道不能在道路中间相交；
4. 每个牧场只能与一条人行道相连。

你需要帮 FJ 求出最多能有多少条人行道。

## 样例 #1

### 输入

```
6
1
2
3
4
5
6
6
5
4
3
2
1```

### 输出

```
5
```

# 题解

## 作者：kczno1 (赞：16)

题意(我没读懂，感谢\_\_stdcall):

让你把两组数字做匹配，连线不相交，并且匹配的每组数字相差<=4。

求最大匹配数。

题解:

从左到右枚举第一行的数，维护第二行每个位置结尾的最大匹配值的前缀max。

就是枚举他能匹配的位置并修改，用树状数组维护。

时间O(nlogn)

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=1;i<=n;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}

const int N=1e5+5;
int n,a[N],dy[N],now[N];

int c[N];
int qiu(int i)
{
    int ans=0;
    for(;i;i-=i&-i)if(c[i]>ans)ans=c[i];
    return ans;
}
void add(int i,int x)
{
    for(;i<=n;i+=i&-i)
    {
        if(c[i]>=x)return ;
        c[i]=x;
    }
}

int main()
{
    freopen("1.in","r",stdin);
    n=read();
    rep(i,n)a[i]=read();
    rep(i,n)dy[read()]=i;
    rep(i,n)
    {
        int x=a[i];
        for(int j=max(1,x-4);j<=min(n,x+4);++j)now[j]=qiu(dy[j]-1);
        for(int j=max(1,x-4);j<=min(n,x+4);++j)add(dy[j],now[j]+1);
    }
    printf("%d\n",qiu(n));
}
```

---

## 作者：junxis (赞：10)

分析 “人行道不能在道路中间相交” 这一条件的本质，我们考虑匹配 $(i,j)$ 与 $(k,l)$，容易发现其不相交的条件为 $i<j$ 且 $k < l$。

我们发现，原问题等价于一个匹配条件更为宽松的最长公共子序列问题。

类似地，我们设计 dp。

记 $dp(i,j)$ 为考虑 $a$ 的前 $i$ 个元素与 $b$ 的前 $j$ 个元素，且 $a_i,b_j$ 必须匹配的最大匹配数。

则 $dp(i,j)=\max_{k<i,l<j}dp(k,l)+1$。

我们考虑优化这一过程。

从小到大枚举 $i$。

记 $c_j=\max_{k<i} dp(k,j)$。

则 $dp(i,j)=\max_{l<j}c_l+1$。

注意 $j$ 需满足与 $i$ 匹配，故 $j$ 只有 $O(1)$ 个。

再令 $c_j\leftarrow \max(c_j,dp(i,j))$。

则完成了一次转移。

用树状数组维护以上过程，为省去 $dp$ 数组并保证正确性，应从后到前更新 $c$。

答案为最终 $c$ 中最大值。

时间复杂度 $O(n \log n)$。

---

## 作者：BriMon (赞：9)

更好的阅读体验[戳这里](https://www.cnblogs.com/BriMon/p/9762659.html)。

如果一边只可以匹配另一边的一个位置，那么这个问题就是简单的最长上升子序列问题了。

但是这题不同，一个点可以匹配多个点，但是点数不多，于是也可以转化成上面的问题。

但是问题就是，如何保证一个点只被匹配一次，其实简单，我们把一边的一个点可以匹配的点的位置从大到小排序，这样就可以保证这些数里在最长上升子序列中最多只有一个出现。

转化甚是巧妙。

```cpp
#include <iostream>
#include <cstdio> 
#include <algorithm>
#include <cstring>
using namespace std;
#define reg register
inline char gc() {
    static const int bs = 1 << 22;
    static unsigned char buf[bs], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, bs, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
inline int read() {
    int res=0;char ch=gc();bool fu=0;
    while(!isdigit(ch))fu|=(ch=='-'), ch=gc();
    while(isdigit(ch))res=(res<<3)+(res<<1)+(ch^48), ch=gc();
    return fu?-res:res;
}
#define N 100005
int n;
int a[N], b[N];
int pos[N];
int c[N*9], cnt, tmp[10];
int low[N*9], ans;

int main()
{
	n = read();
	for (reg int i = 1 ; i <= n ; i ++) a[i] = read();
	for (reg int i = 1 ; i <= n ; i ++) pos[b[i] = read()] = i;
	for (reg int i = 1 ; i <= n ; i ++)
	{
		int top = 0;
		for (reg int j = max(1, a[i] - 4) ; j <= min(n, a[i] + 4) ; j ++)
			tmp[++top] = pos[j];
		sort(tmp + 1, tmp + 1 + top);
		for (reg int j = top ; j >= 1 ; j --) c[++cnt] = tmp[j];
	}
	low[++ans] = c[1];
	for (reg int i = 2 ; i <= cnt ; i ++)
	{
		if (c[i] > low[ans]) low[++ans] = c[i];
		else {
			int t = lower_bound(low + 1, low + 1 + ans, c[i]) - low;
			low[t] = c[i];
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：冷月冰瞳 (赞：7)

一个比较直接的DP就是 F[i, j] 表示第一条链的前 i 个和第二条链的前 j 个最大可能的连线数，那么

- F[i, j] = max(F[i-1, j], F[i, j-1], F[i-1, j-1]+1(if |a\_i-b\_j| <= 4))
但是这样状态个数就是 N^2，我们需要减少状态数。改变一个状态表示，对 F[i, j] 这个状态新增一个条件，就是 a\_i 和 b\_j 是连线的，即 |a\_i-b\_j| <= 4，这样 j 的取值个数就只有 9 个了，然后状态转移就是
- F[i, j] = max(F[x, y]+1),  x < i, y < j

这个转移就是一个前缀最大值，可以用树状数组优化。


---

## 作者：lg_zhou (赞：6)

一开始没想明白这道题，所以力求让大家看明白这篇题解。

如果暴力的 $dp$ 转移，相信大家都早已会求， 设 $dp[i][j]$ 为 $i$ 和 $j$ 是最后一组相连的情况下，最多的牛行道条数。

但我们为什么要这么设，为什么不能设  $dp[i][j]$ 为左边到 $i$ 为止，右边到 $j$ 为止，最多的牛行道条数呢？

我们都知道，一般状态有两种设法：以 $i$ 为止和必选 $i$。一般必选 $i$ 中后面的转移都要需要上一个的状态。比如最长上升子序列转移的时候每个数都要比前面大，想要知道上个数是什么，就以必选 $i$ 为状态设计。而如背包问题等，选不选当前的并不需要上一个物品状态，就设以什么为止。

但以 $i$ 为止虽然可以做这道题，但无法再优化下去了，因为我们只能从相邻状态 $i-1$ 或 $j-1$ 转移来。复杂度会爆炸。

所以设 $dp[i][j]$ 为 $i$ 和 $j$ 是最后一组相连的情况下，最多的牛行道条数。则 $dp[i][j] = max(dp[x][y]+1)(x < i, y < j) $ 并且 $i,j$ 的编号相差不过 $4$ 。

这时候我们要快速求出所有 $(x < i, y < j)$ 中 $dp[x][y]$ 的最大值。可以用树状数组的维护。我们用 $getmax(j-1)$ 这个前缀最大来维护所有 $y < j$ 的最大 $dp[i][j]$ 值。对于每一个新求出来的 $dp[i][j]$ 值，只需要 $modify(j,dp[i][j])$ ， 将 $j$ 这个位置的值更新一遍取个大即可。

那如何保证 $x < i$ 呢？很简单：我们第一层循环按 $i$ 来枚举，那我们已经 $modify$ 过的 $dp$ 值就只有可能是小于当前 $i$ 值的。所以直接按上面一段操作即可。

---

## 作者：yuzhechuan (赞：3)

LCS是本题比较直观的一种思路，即将普通LCS（最长公共子序列）的相等的条件改为差的绝对值<=4

众所周知，求LCS有两种$O(nlogn)$方法

一种是映射，另一种是DP优化

因为差的绝对值<=4的条件会使映射变得复杂，我们这里采用DP优化的方法

该方法具体可以见[[noip科普]关于LIS和一类可以用树状数组优化的DP](https://www.cnblogs.com/liu-runda/p/6193690.html)

要注意的是，该方法中要记录b[]中各值可合法对应的值在a[]的位置，这个位置是需要通过排序来保证有序的

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}
const int N=1e5+5;
int a[N],b[N],n,f[N],ans,pos[N];
vector<int> p[N];
struct BIT{ //树状数组模板
	#define lowbit(x) (x&(-x))
	int a[N];
	void up(int x,int v){
		while(x<=n){
			a[x]=max(a[x],v);
			x+=lowbit(x);
		}
	}
	int que(int x){
		int res=0;
		while(x){
			res=max(res,a[x]);
			x-=lowbit(x);
		}
		return res;
	}
}ma;
signed main(){
	read(n);
	for(int i=1,x;i<=n;i++){
		read(x);
		pos[x]=i; //记录某值的位置
	}
	for(int i=1;i<=n;i++){
		read(b[i]);
		for(int j=max(1,b[i]-4);j<=min(n,b[i]+4);j++)
			p[i].push_back(pos[j]); //记录b[]值合法对应值的位置
		sort(p[i].begin(),p[i].end()); //排序使之保证有序
	}
	for(int i=1;i<=n;i++)
		for(int j=p[i].size()-1;j>=0;j--){ //按位置搞LCS
			int pos=p[i][j];
			f[pos]=ma.que(pos-1)+1;
			ma.up(pos,f[pos]);
		}
	for(int i=1;i<=n;i++) ans=max(ans,f[i]); //得到答案
	write(ans);
}
```

---

## 作者：罪将于禁 (赞：3)

**\_这题又没有pascal题解。。\_>- - - 0. ###**

//n2暴力lcs20分

其实可以参考一下lcs模板。。这题差不多的。只是判断条件变为绝对值小于4

可以先将数据离散化。。虽然样例水的不需要离散化

然后用树状数组就行维护就行//一直觉得树状数组是玄学操作









```cpp
var
i,j,n,shu,qu:longint;
a,b,tree,now:array[0..100000]of longint;
function max(x,y:longint):longint;
begin
if x>y then exit(x) else exit(y);
end;
function min(x,y:longint):longint;
begin
if x>y then exit(y) else exit(x);
end;
function lowbit(x:longint):longint;//树状数组不解释。。。不会自己百度
begin
 lowbit:=x and -x;
end;
procedure add(x,y:longint);//建树，添加过程
begin
  while x<=n do
   begin
   tree[x]:=max(tree[x],y);
   x:=x+lowbit(x);
   end;
end;
function sum(x:longint):longint;//求1-x区间最大值
begin
 sum:=0;
 while x>0 do begin
 sum:=max(sum,tree[x]); 
 x:=x-lowbit(x);
 end;
end;
begin
  readln(n);
  for i:=1 to n do readln(a[i]);
  for j:=1 to n do begin readln(shu);  b[shu]:=j; end;//离散化一下
  for i:=1 to n do//对a就行枚举，复杂度n
    begin
    qu:=a[i];
    for j:=max(1,qu-4) to min(n,qu+4) do  now[j]:=sum(b[j]-1)+1;//树状数组维护logn
    for j:=max(1,qu-4) to min(n,qu+4) do  add(b[j],now[j]);
    end;
  writeln(sum(n));
end.//成功复杂度nlogn
```

---

## 作者：cirnovsky (赞：2)

## 题意简述

~~题面好长~~

大概意思就是说给你两个长度均为 $n$ 的整数序列，然后如果两个位置的值的差的绝对值小于4那么这两个位置就可以连一条边。要求边不交叉，求最多能连多少条。

## 题解

提供一种纯树状数组的做法。（去他的dp）

选取一行作为“参考行”，然后维护能与其匹配的位置，然后树状数组修改。

树状数组的思路要比dp的LCS简洁很多。

~~所以我们一起放弃dp罢~~

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define one max(1, a[i] - 4)
#define two min(n, a[i] + 4)

using namespace std;

const int MAXN = 1e5 + 5;
int bit[MAXN], a[MAXN], t[MAXN];
int n, rnk[MAXN];

void modify(int x, int y) {
	for (; x <= n; x += x & -x)
		if (y < bit[x]) return ;
		else bit[x] = y;
}

int queryf(int x) {
	int res = 0;
	for (; x; x -= x & -x)
		res = max(res, bit[x]);
	return res;
}

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1, x; i <= n; ++i) scanf("%d", &x), rnk[x] = i;
	for (int i = 1; i <= n; ++i) {
		for (int j = one; j <= two; ++j) t[j] = queryf(rnk[j] - 1);
		for (int j = one; j <= two; ++j) modify(rnk[j], t[j] + 1);
	}
	printf("%d\n", queryf(n));
}
```

---

## 作者：两年打铁 (赞：2)

一步步讲起。

首先由线段不相交，我们可以得到一个$O(n^2)$的做法，设$f_{i,j}$表示一行到i，一行到j的最大线段。

发现这个转移只跟枚举的前一个有关，而且每次只会从改的标号之前转移，那么我们就可以去掉枚举的那一维。

然后着眼题目中差值小于等于4，这意味着每个枚举的点对应可以改变dp数组的位置最多只有9个。

所以我们只要记下另一行的对应权值的标号即可。

上面讲到，由于转移是找到前缀最大值，那么就可以直接线段树或者树状数组维护了。

代码中有50分和100分做法。

```cpp
#include<bits/stdc++.h>
#define huan putchar('\n')
#define kong putchar(' ')
#define bug puts("QWQ")
#define swap mswap
using namespace std;

const int big=0x7fffffff;

inline void mswap(int &x,int &y)
{
    x^=y^=x^=y;
}

inline void read(int &x)
{
    x=0;register char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}

void write(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else write(x/10),putchar(x%10+'0');
}

inline void wrl(int x)
{
    write(x);
    huan;
}

inline void wrs(int x)
{
    write(x);
    kong;
}
const int N=2e5+233;

int f[N<<3];

int a[N],b[N],pos[N],s[2333];
int n;
namespace sub1
{
	int main()
	{
		for(register int i=1;i<=n;++i)
		{
			read(a[i]);
		}
		for(register int i=1;i<=n;++i)
		{
			read(b[i]);
		}
		int ans=0;
		for(register  int i=1;i<=n;++i)
		{
			for(register int j=n;j;--j)
			{
				if(abs(b[i]-a[j])<=4)
				{
					f[j]=max(f[j-1]+1,f[j]);
				}
				f[j]=max(f[j-1],f[j]);
				ans=max(ans,f[j]);
			}
			for(register int j=1;j<=n;++j)f[j]=max(f[j],f[j-1]);
		}
		cout<<ans<<endl;
		return 0;
	}
}

namespace sub2
{
	void change(int k,int l,int r,int pos,int v)
	{
		if(l==r)
		{
			f[k]=max(f[k],v);
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			change(k<<1,l,mid,pos,v);
		}
		else change(k<<1|1,mid+1,r,pos,v);
		f[k]=max(f[k<<1],f[k<<1|1]);
	}
	
	int query(int k,int l,int r,int p,int q)
	{
		if(l>=p&&r<=q)return f[k];
		int mid=(l+r)>>1;
		int ans=0;
		if(p<=mid)
		{
			ans=max(ans,query(k<<1,l,mid,p,q));
		}
		if(q>mid)
		{
			ans=max(ans,query(k<<1|1,mid+1,r,p,q));
		}
		return ans;
	}
	
	int main()
	{
		for(register int i=1;i<=n;++i)
		{
			read(a[i]);
			pos[a[i]]=i;
		}
		for(register int i=1;i<=n;++i)
		{
			read(b[i]);
		}
		
		for(register int i=1;i<=n;++i)
		{
			for(register int j=-4;j<=4;++j)
			{
				s[j+4]=0;
				if(b[i]+j<1||b[i]+j>n)continue;
				
				int now=0;
				if(pos[b[i]+j]-1>0)
				now=query(1,1,n,1,pos[b[i]+j]-1);
				
				s[j+4]=now+1;
			}
			for(register int j=-4;j<=4;++j)
			{
				if(b[i]+j<1||b[i]+j>n)continue;
				change(1,1,n,pos[b[i]+j],s[j+4]);
			}
		}
		cout<<query(1,1,n,1,n);
		return 0;
	}
}


int main()
{
	read(n);
	if(n<=5000)return sub1::main();
	else
	{
		return sub2::main();
	}
}

/*
6
1 2 3 4 5 6
6 5 4 3 2 1

6
1 2 3 4 5 6
2 5 3 4 6 1

6
4 5 3 6 2 1
2 5 3 4 6 1
*/
```


---

## 作者：__LYC__qwq (赞：1)

## 题意描述

左右两边有农场, 如果左右两边的品种绝对值相差 $\le 4$ 才可以建一条道路, 道路建好后道路要互不相交, 求出最大的修建道路数量。

## 思路

令某两条道路的左边农场从上到下的坐标分别为 $x_1, x_2$, 右边的坐标分别为 $y_1, y_2$, 如果不相交, 当且仅当 $x_1 < x_2$ 且 $y_1 < y_2$。

如果先对 $x_1$ 排序, 然后的选出的道路的 $y$ 就是在 $x_i \le x_{i + 1}$ 上的一段严格上升子序列, 由于题目要求最长, 就是求最长严格上升子序列。

首先, 对先把可以建的道路准备好, 因为题目中是 $|a - b| \le 4$, 左右两边的品种分别互不相同, 固然最多只有 $9N$ 个可行的道路。

状态 $(i, sum)$ 表示考虑排序后前 $i$ 个道路, 第 $i$ 个道路选的最大值为 $sum$。

推出转移式 $(j, sum') \to (i, sum)$ 其中, $x_j < x_i, y_j < y_i$。

显然, 是一个区间最大值问题, 用线段树维护即可。

时间复杂度 $:O(N \log N)$。

空间复杂度 $:O(N)$。

## 细节

注意有些道路的 $x_i$ 相等。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, M = 9 * N;

struct Node{
  int x, y;
}a[M];

int n, id, m, b[N], x, u[N], tot, v[N], flag, ans, dp[M], cnt[N];

struct TREE{
  struct Node{
    int l, r, maxx = 0;
  }t[4 * N];
  void build(int p, int l, int r){
    t[p].l = l, t[p].r = r;
    if(l == r){
      return;
    }
    int mid = (l + r) >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
  }
  void renew(int p){
    t[p].maxx = max(t[p * 2].maxx, t[p * 2 + 1].maxx);
  }
  void updata(int p, int l, int x){
    if(t[p].l == t[p].r){
      t[p].maxx = max(t[p].maxx, x);
      return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if(l <= mid){
      updata(p * 2, l, x);
    }
    else{
      updata(p * 2 + 1, l, x);
    }
    renew(p);
  }
  int getmax(int p, int l, int r){
    if(r < l){
      return 0;
    }
    if(t[p].l >= l && t[p].r <= r){
      return t[p].maxx;
    }
    int sum = 0;
    int mid = (t[p].l + t[p].r) >> 1;
    if(l <= mid){
      sum = max(sum, getmax(p * 2, l, r));
    }
    if(r > mid){
      sum = max(sum, getmax(p * 2 + 1, l, r));
    }
    renew(p);
    return sum;
  }
}tree;

int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> u[i];
    cnt[u[i]] = i;
  }
  for(int i = 1, x; i <= n; ++i){
    cin >> v[i];
    for(int j = max(1, v[i] - 4); j <= min(n, v[i] + 4); j++){
      if(cnt[j]){
        a[++tot] = {i, cnt[j]};
      }
    }
  }
  tree.build(1, 1, n);
  sort(a + 1, a + tot + 1, [](const Node &i, const Node &j){  return i.x < j.x || i.x == j.x && i.y < j.y;});
  for(int i = 1, j = 1; i <= tot;){
    for(; a[i].x == a[j].x; j++){
      dp[j] = tree.getmax(1, 1, a[j].y - 1) + 1;
      ans = max(ans, dp[j]);
    }
    for(; i < j; ++i){
      tree.updata(1, a[i].y, dp[i]);
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：xuzz (赞：1)

##### 很巧妙的一道题

题解区中的大佬都 **太 巨 辣**，蒟蒻实在看不懂，只能说一下自己的理解。

### 题意

两组数字上下匹配，每个数可匹配多次，要求连线的两数差的绝对值小于等于4，且线不能相交。

### 题解：

朴素的DP很好想，不会的可以先做弱化版。

设 $f_{i,j}$ 表示在第一行前 $i$ 个数，后 $j$ 个数之间连线，所获得的最大匹配数。

于是有转移方程：

$$f_{i,j}=\max(f_{i,j-1},f_{i-1,j},f_{i-1,j-1}+(|a_i-b_j|\leq4))$$

考虑优化，枚举第一行， $a_i$ 只会对值在 $a_i\pm4$ 以内的 $b_j$ 产生贡献，所以只要枚举会对 $a_i$ 产生贡献的  $b_j$ ，再求出前面最大的匹配数，加上新产生的匹配就是当前的最大匹配数，转移方程式就转化为：

$$f_{i,j}=\max(f_{i^{\prime},j^{\prime}})+1,i^{\prime}<i,j^{\prime}<j$$

也就是求前缀最大值，可以用树状数组维护。
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
inline int Max(const int x,const int y){return x>y?x:y;}
inline int Min(const int x,const int y){return x<y?x:y;}
const int N=100005;
int c[N],a[N],b[N],n,d[N];
int ask(int x){int s=0;while(x){s=Max(s,c[x]),x-=x&-x;} return s;}
void add(int x,const int k){for(;x<=n;x+=x&-x) if(c[x]>=k) return;else c[x]=k;}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[read()]=i;
	for(int i=1;i<=n;i++)
	{
		const int MI=Max(1,a[i]-4),MA=Min(n,a[i]+4);
		for(int j=MI;j<=MA;j++) d[j]=ask(b[j]-1);
		for(int j=MI;j<=MA;j++) add(b[j],d[j]+1);
	}
	printf("%d\n",ask(n));
	return 0;
}
```


---

## 作者：2023lpx (赞：0)

## 思路

~~无论如何，总得先把可以连的边先建出来吧？~~

设 $dp_{i}$ 表示考虑到第 $i$ 条可以连接的边，且这条边必须连，可以连边的最大值。

显然有 $dp_i=\max(dp_j|x_j<x_i,y_j<y_i)+1$。

显然，区间最大值可以用线段树维护。

因为总共只有 $9n$ 条可以连的边，故时间复杂度为 $O(n \log n)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int const maxn=500000;
int a[maxn+1];
int b[maxn+1];
struct To{
	int from,to;
}to[maxn*11+1];
int cnt;
int ca[maxn+1];
int f[maxn+1];
int tree[maxn*6+1];
void change(int p,int l,int r,int x,int c){
	if(l==r){
		tree[p]=max(tree[p],c);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		change(p*2,l,mid,x,c);
	}
	else{
		change(p*2+1,mid+1,r,x,c);
	}
	tree[p]=max(tree[p*2],tree[p*2+1]);
	return;
}
int find(int p,int l,int r,int L,int R){
	if(L>R){
		return 0;
	}
	if(l>=L&&r<=R){
		return tree[p];
	}
	int mid=(l+r)>>1;
	int sum=0;
	if(L<=mid){
		sum=max(sum,find(p*2,l,mid,L,R));
	}
	if(R>mid){
		sum=max(sum,find(p*2+1,mid+1,r,L,R));
	}
	return sum;
}
int ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		ca[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		for(int j=max(1,b[i]-4);j<=min(n,b[i]+4);j++){
			if(ca[j]!=0){
				cnt++;
				to[cnt].from=i;
				to[cnt].to=ca[j];
			}
		}
	}
	sort(to+1,to+cnt+1,[](To a,To b){return a.from==b.from?a.to<b.to:a.from<b.from;});
	int j=1;
	for(int i=1;i<=cnt;){
		while(to[i].from==to[j].from){
			f[j]=find(1,1,n,1,to[j].to-1)+1;
			ans=max(ans,f[j]);
			j++;
		}
		while(i<j){
			change(1,1,n,to[i].to,f[i]);
			i++;
		}
//		printf("%d===%d===\n",i,j);
	}
	printf("%d",ans);
	
	return 0;
}
```

---

## 作者：Fzrcy (赞：0)

> 题意简述：求出最大的 $m$，满足存在两个长度为 $m$ 的数组 $A$、$B$，使得 $A_i<A_{i+1}$，$B_i<B_{i+1}$，$|a_{A_i}-b_{B_i}|\le 4$，**一个数列中不会出现重复的数字**。

设 $f_{i,j}$ 表示考虑了 $a$ 数组中的前 $i$ 个元素、 $b$ 数组中的前 $j$ 个元素的最大匹配数。

可以像求最长公共子序列一样转移，时间复杂度为 $O(n^2)$。

观察转移条件 $|a_i-b_j|\le 4$，可以发现从 $f_{i,j}$ 转移到 $f_{i+1,k}$ 时，最多只有 $9$ 个 $f_{i+1,j}$ 和 $f_{i,j}$ 不同，直接用树状数组动态维护即可，时间复杂度为 $O(n\log n)$。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
constexpr int N=1e6+7;
int c[N],n,m,p[N];
void add(int x,int v){for(;x<=n;x+=x&-x)c[x]=max(c[x],v);}
int Q(int x){int r=0;for(;x;x-=x&-x)r=max(r,c[x]);return r;}
int main(){
	cin>>n;
	for(int i=1,x;i<=n;i++)
		cin>>x,p[x]=i;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		vector<pair<int,int>>S;
		for(int j=max(x-4,1);j<=min(x+4,n);j++)
			S.push_back({p[j],Q(p[j]-1)+1});
		for(auto j:S)add(j.first,j.second);
	}
	cout<<Q(n)<<'\n';
	return 0;
}
```



---

## 作者：Purslane (赞：0)

## Solution

>  Why did the chicken cross the road ? 

> To get the other side . ( 真不知道这有啥好笑的 )

最长上升子序列问题 . 两年前我竟然自创了这个 trick . 小学的我碾压现在的我 ......

考虑如果是一一配对的 , 那么显然的最长上升子序列问题 .

> $dp_i = \text{max} \{ dp_j \}+1 , f_j<f_i$ . 这么搞是 $\text{O(n} ^\text{2} \text{)}$ 的 . 有一种转换 $dp$ 方程的 , 但是这改变了它的本质 , 不好 . 考虑使用树状数组加速 , 即用树状数组找到所有 $f_j<f_i$ 的 $dp_j$ .

考虑这道题 . 奇奇怪怪 , 怎么有 $9$ 种配对方案啊 ! 咱不怕方案多 , 再开一维 : $dp_{i,j}$ , 这个 $j$ 维护的是哪一种配对方案 . 所以我们转移的时候要找到所有 $p_k < p_j$ 的 $k$ , 而 $i$ 没有什么关系 .

所以我们甚至可以从大到小枚举配对 , 连 $dp$ 数组都不用 ! ( 所以当年我是怎么想出来的 )

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
struct BIT {
	int n;
	vector<int> tr;
	void init(int N) {return tr.resize(N+1),n=N,void();}
	int lowbit(int k) {return k&-k;}
	void update(int pos,int val) {while(pos<=n) tr[pos]=max(tr[pos],val),pos+=lowbit(pos);return;}
	int Query(int pos) {int ans=0;while(pos) ans=max(ans,tr[pos]),pos-=lowbit(pos);return ans;}
	int query(int l,int r) {return Query(r)-Query(l-1);}
}bit;
int n,a[MAXN],b[MAXN],pos[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;ffor(i,1,n) cin>>a[i];ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) pos[a[i]]=i;
	bit.init(n);
	ffor(i,1,n) {
		vector<int> Pos;
		ffor(j,max(1,b[i]-4),min(n,b[i]+4)) Pos.push_back(pos[j]);
		sort(Pos.begin(),Pos.end(),[](int A,int B){return A>B;});
		for(auto idx:Pos) bit.update(idx,bit.Query(idx-1)+1);
	}
	cout<<bit.Query(n);
	return 0;
}
```

---

## 作者：lytqwq (赞：0)

两排农场，可以连接左右的两个农场 $i,j $ $ (|a_i-b_j|\le4) $ 来产生 $1$ 的贡献，连接不能相交，求最大贡献。

设 $f_{i,j}$ 为第一排看了前 $i$ 个农村，第二排看了前 $j$ 个农村的最大贡献。

有状态转移方程：

$$
f_{i,j}=\max( f_{i-1,j},f_{i,j-1},f_{i-1,j-1}+[ |a_i-b_j|\le4 ] )
$$


直接递推 $O(n^2)$

发现这个 连接左右的两个农场的条件 比较牛 ，对于一个 $i$ ，最多只有 $9$ 个 $j$ 才能行，而其他的项都是取前面的值，我们可以只对于每个 **可行的连接** 求它的 $f$ ，然后就成了个二维数点的问题，树状数组维护最大值即可

时间复杂度 $O(nlogn)$

这里直接给一个~~简洁的~~ $O(nlogn)$ 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100100;
int n,a[N],b[N],wz[N],c[N],fans[N],maxn;
vector<int> to[N];
int lowbit(int x){return x&(-x);}
void update(int x,int y){for(int i=x;i<=n;i+=lowbit(i))c[i]=max(c[i],y);}
int query(int x){int ans=0;for(int i=x;i>=1;i-=lowbit(i))ans=max(ans,c[i]);return ans;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),wz[a[i]]=i;
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		for(int v=-4;v<=4;v++)if(b[i]+v>=1&&b[i]+v<=n)to[i].push_back(wz[b[i]+v]);
		sort(to[i].begin(),to[i].end());
		int len=to[i].size();
		for(int o=0;o<len;o++)fans[o]=query(to[i][o]-1)+1,maxn=max(maxn,fans[o]);
		for(int o=0;o<len;o++)update(to[i][o],fans[o]);
	}
	printf("%d\n",maxn);
}
```



---

## 作者：andychen_2012 (赞：0)

#### 本题解对初学者较不友好

一个比较直接的DP就是 $f_{i,j}$ 表示第一条链的前 $i$ 个和第二条链的前 $j$ 个最大可能的连线数，那么

$$f_{i,j} = \max( f_{i-1,j}, f_{i,j-1}, f_{i-1,j-1}+1(|a_i-b_j|<= 4))$$

但是这样状态个数就是 $N^2$，我们需要减少状态数。

改变一个状态表示，对 $f_{i,j}$ 这个状态新增一个条件，
    
就是 $a_i$ 和 $b_j$ 是连线的，即 $|a_i-b_j|<=4$，
    
这样 $j$ 的取值个数就只有 $9$ 个了，然后状态转移就是
    
$$f_{i,j} = max(f_{x,y}+1),x<i,y<j$$

这个转移就是一个前缀最大值，可以用树状数组优化。
                                      
代码如下：

```cpp
#include<cstdio>
#define gc (ch=getchar())
inline int read(){
	char ch;
	while(gc<'0');
	int x=ch-'0';
	while(gc>='0')
		x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
int n,a[100005],d[100005],now[100005],tr[100005];
inline int sum(int x){
	int ans=0;
	while(x){
		if(tr[x]>ans)
			ans=tr[x];
		x-=x&(-x);
	}
	return ans;
}
inline void add(int x,int k){
	while(x<=n){
		if(tr[x]>=k)
			return;
		tr[x]=k;
		x+=x&(-x);
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		d[read()]=i;
	int x,be,la;
	for(int i=1;i<=n;i++){
		x=a[i];
		be=x-4<1?1:x-4;
		la=n<x+4?n:x+4;
		for(int j=be;j<=la;j++)
			now[j]=sum(d[j]-1);
		for(int j=be;j<=la;j++)
			add(d[j],now[j]+1);
	}
	printf("%d\n",sum(n));
	return 0;
}
```

---

