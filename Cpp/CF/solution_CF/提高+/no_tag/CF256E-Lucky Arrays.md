# Lucky Arrays

## 题目描述

Little Maxim loves interesting problems. He decided to share one such problem with you.

Initially there is an array $ a $ , consisting of $ n $ zeroes. The elements of the array are indexed, starting from 1. Then follow queries to change array $ a $ . Each query is characterized by two integers $ v_{i},t_{i} $ . In the answer to the query we should make the $ v_{i} $ -th array element equal $ t_{i} $ $ (a_{vi}=t_{i}; 1<=v_{i}<=n) $ .

Maxim thinks that some pairs of integers $ (x,y) $ are good and some are not. Maxim thinks that array $ a $ , consisting of $ n $ integers, is lucky, if for all integer $ i $ , $ (1<=i<=n-1) $ the pair of integers $ (a_{i},a_{i+1}) $ — is good. Note that the order of numbers in the pairs is important, that is, specifically, $ (1,2)≠(2,1) $ .

After each query to change array $ a $ Maxim wants to know, how many ways there are to replace all zeroes in array $ a $ with integers from one to three so as to make the resulting array (without zeroes) lucky. Of course, distinct zeroes can be replaced by distinct integers.

Maxim told you the sequence of queries and all pairs of integers he considers lucky. Help Maxim, solve this problem for him.

## 样例 #1

### 输入

```
3 10
1 1 0
1 0 0
1 1 1
1 1
1 3
2 2
3 0
2 1
3 0
3 1
2 0
3 1
1 0
```

### 输出

```
3
6
1
1
2
2
1
3
3
6
```

# 题解

## 作者：RedLycoris (赞：3)

这里是全网唯一一份分块的题解（也可能是唯一一份分块卡过去的做法）。

---

现将这 $n$ 个数分块。

令 $dp_{f,i,j}$ 表示考虑到某一块中，考虑到第 $i$ 个位置，上一个位置填的数是 $j$ 时，这一块的开头为 $f$ 的方案数对 $dp_{i,j}$ 的贡献的系数。注意，这里是系数，为了好带入到查询时的整合。可以发现，$f$ 对于转移无关。

处理更新的代码：

```cpp
	inline void go(){
		memset(dp,0,sizeof(dp));
		if(a[0]==0){
			for(ri f=1;f<=3;++f){   //不确定，枚举
				dp[f][0][f]=1;
				for(ri i=1;i<sz;++i){
					ri t=a[i];
					if(a[i]==0){    //分类转移
						for(t=1;t<=3;++t)
							for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
					}else{
						for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
					}
				}
			}			
		}else{     //已经确定块头必须是多少
				ri f=a[0];
				dp[f][0][f]=1;
				for(ri i=1;i<sz;++i){
					ri t=a[i];
					if(a[i]==0){
						for(t=1;t<=3;++t)
							for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
					}else
						for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
				}
		}
	}
```

然后，查询时有些复杂：

首先，单独处理好整个数列的第一个块（因为 $dp$ 存的是系数，不好接入）。

然后，对于接下来的每个块，考虑与上一个块的末尾相接。

先处理好每个块的块首的答案，然后利用 $dp$ 直接计算得到块尾的答案。

注意要时时刻刻取模。

这样，分块的做法就写好了。

**不过，如果你只做到了这儿，你只会想绝大多数分块一样TLE 11**

---

一些优化：

+ 对于查询时的处理，将 $dp[3]$ 展开成 $x,y,z$ 来节省常数

+ 尽量的去掉大括号

+ register inline

+ 快读快输，火车头

+ 快的大小是信仰数 ~~srand('xhztxdy')~~

+ 使用 C++14 来替代 C++11

---

痛苦的心路历程(在 mashups 不断测试)：

![](https://cdn.luogu.com.cn/upload/image_hosting/xaysi6hy.png)

---

整体代码：

```cpp

#include<bits/stdc++.h>
#define ll long long
#define reg register
#define mp make_pair
#define ri register int
#define ld long double
using namespace std;
const int maxn=70007;
char buffer[maxn],*S,*T;
inline char Get_Char(){
    if(S==T){
        T=(S=buffer)+fread(buffer,1,maxn,stdin);
        if(S==T)return EOF;
    }
    return *S++;
}

inline int read(){
    char c;
    int re=0,f=0;
    for(c=Get_Char();c<'0' or c>'9';c=Get_Char())if(c=='-')f=1;
    for(;c>='0' and c<='9';)re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();
    if(f)return -re;
    return re;
}

inline void read(int&x){
    char c;
    int re=0,f=0;
    for(c=Get_Char();c<'0' or c>'9';c=Get_Char())if(c=='-')f=1;
    for(;c>='0' and c<='9';)re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();
    if(f)x=-re;
    else x=re;
}
const int mxn=78787;
vector<int>g[mxn];
int n,q;
int a[mxn];
int c[4][4];
const int siz=225;
const int md=777777777;
inline void add(int&x,int y){
	x+=y;
	if(x>=md)x-=md;
}
struct tmp{
	ll x,y,z;
	inline void G(){
		x%=md;
		y%=md;
		z%=md;
	}
};
struct ttmp{tmp x,y,z;};
struct kuai{
	int dp[4][siz][4],a[siz],sz;
	inline void init(){
		sz=0;memset(a,0,sizeof(a));
	}
	inline void go(){                //更新
    memset(dp,0,sizeof(dp)); 
		if(a[0]==0){
			for(ri f=1;f<=3;++f){
				dp[f][0][f]=1;
				for(ri i=1;i<sz;++i){
					ri t=a[i];
					if(a[i]==0){
						for(t=1;t<=3;++t)
							for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
					}else{
						for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
					}
				}
			}			
		}else{
				ri f=a[0];
				dp[f][0][f]=1;
				for(ri i=1;i<sz;++i){
					ri t=a[i];
					if(a[i]==0){
						for(t=1;t<=3;++t)
							for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
					}else
						for(ri p=1;p<=3;++p)if(c[p][t]==1)add(dp[f][i][t],dp[f][i-1][p]);
				}
		}
	}
	inline ttmp ret(){return (ttmp){(tmp){dp[1][sz-1][1],dp[1][sz-1][2],dp[1][sz-1][3]},(tmp){dp[2][sz-1][1],dp[2][sz-1][2],dp[2][sz-1][3]},(tmp){dp[3][sz-1][1],dp[3][sz-1][2],dp[3][sz-1][3]}};}
}k[mxn/siz+3];
inline void solve(){
	read(n),read(q);
	for(ri i=1;i<=3;++i)for(int j=1;j<=3;++j)read(c[i][j]);
	for(ri i=0;i<mxn/siz+3;++i)k[i].init();
	for(ri i=0;i<n;++i)++k[i/siz].sz;
	int num=(n+siz-1)/siz;
	for(ri i=0;i<=num;++i)k[i].go();
	for(;q--;){
		ri x,t;read(x),read(t);--x;
		k[x/siz].a[x%siz]=t;
		k[x/siz].go();
		reg tmp cur;
		ri ta=k[0].a[0];
		if(!ta)cur.x=1,cur.y=1,cur.z=1;    //处理第一块
		else{
			cur.x=0,cur.y=0,cur.z=0;
			if(ta==1)cur.x=1;
			if(ta==2)cur.y=1;
			if(ta==3)cur.z=1;
		}
		{
			ttmp tt=k[0].ret();
			reg tmp x=tt.x,y=tt.y,z=tt.z;
			tmp nw;
				nw.x=x.x*cur.x+y.x*cur.y+z.x*cur.z;
				nw.y=x.y*cur.x+y.y*cur.y+z.y*cur.z;
				nw.z=x.z*cur.x+y.z*cur.y+z.z*cur.z;
			nw.G();
			cur=nw;
		}
		for(ri i=1;i<num;++i){
			ri ta=k[i].a[0];
			reg tmp ne;ne.x=0,ne.y=0,ne.z=0;
			if(ta==0){                   //处理块首
					if(c[1][1])ne.x+=cur.x;
					if(c[2][1])ne.x+=cur.y;
					if(c[3][1])ne.x+=cur.z;
					if(c[1][2])ne.y+=cur.x;
					if(c[2][2])ne.y+=cur.y;
					if(c[3][2])ne.y+=cur.z;
					if(c[1][3])ne.z+=cur.x;
					if(c[2][3])ne.z+=cur.y;
					if(c[3][3])ne.z+=cur.z;
			}
			if(ta==1){
					if(c[1][1])ne.x+=cur.x;
					if(c[2][1])ne.x+=cur.y;
					if(c[3][1])ne.x+=cur.z;
			}
			if(ta==2){
					if(c[1][2])ne.y+=cur.x;
					if(c[2][2])ne.y+=cur.y;
					if(c[3][2])ne.y+=cur.z;
			}
			if(ta==3){
					if(c[1][3])ne.z+=cur.x;
					if(c[2][3])ne.z+=cur.y;
					if(c[3][3])ne.z+=cur.z;
			}
			cur=ne;                       //得到块尾
			reg ttmp tt=k[i].ret();
			reg tmp x=tt.x,y=tt.y,z=tt.z;
			reg tmp nw;
				nw.x=x.x*cur.x+y.x*cur.y+z.x*cur.z;
				nw.y=x.y*cur.x+y.y*cur.y+z.y*cur.z;
				nw.z=x.z*cur.x+y.z*cur.y+z.z*cur.z;
				nw.G();
			cur=nw;
			cur.G();
		}
		ri ans=cur.x;add(ans,cur.y);add(ans,cur.z);
		printf("%d\n",ans);
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;//cin>>T;
	for(;T--;)solve();
}
```

---

加上信仰火车头是6kb

~~所以6kb干了2kb的活~~

---

## 作者：Islauso (赞：2)

这道题个人觉得理论上来说分块是可以做的，但不知道为什么一直会 T 在第 11 个点，改成线段树后惊奇的发现居然是目前洛谷上的最优解，写篇题解纪念一下。

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20210104191646.png)

## 题目大意

给出一个长度为 $n$ 的数列 $a$，初始时所有元素都为 $0$，有 $m$ 次修改，每次把 $a_{v}$ 的值改成 $t$，且 $t\in[0,3]$，修改完之后，询问如果把这个数列中所有的 $0$ 都改成 $1$ 到 $3$ 中的某个整数（两个 $0$ 可以改为不同的值），有多少种方案使这个数列是一个幸运的数列。

定义一个数列为幸运的数列，当且仅当对于所有 $1\le i\le n-1$，数对 $(a_i,a_{i+1})$ 是幸运的，用一个 $3\times 3$ 的矩阵 $w$ 来表示幸运的数对，当 $w_{i,j}=1$ 时，表示数对 $(i,j)$ 是幸运的，反之则表示它不是幸运的。

答案对 $777777777$ 取模。

## 思路

这道题其实就是大力线段树乱搞就行了，毕竟 $n$ 才到 $77777$（~~那为什么分块会 T 啊喂~~）。

显然，我们只关心那些所有元素都为 $0$ 的区间（为了方便，下面都称之为 $0$ 区间），而这些区间彼此又是无关的，也就是说，这个 $0$ 区间选的变换方案是什么，跟那个 $0$ 区间选的变换方案是什么并没有什么卵关系，因此在询问时，我们只需要将每个 $0$ 区间的方案总数乘起来就行了，这一部分可以直接 DP 预处理，用 $f_{i,j,len}$ 表示一段长度为 $len$，开头选择数字 $i$，结尾选择数字 $j$ 的 $0$ 区间的方案总数，那么状态转移方程显然如下：
$$
f_{i,j,len}=\sum\limits^3_{k=1} f_{i,k,len-1} (a_{k,j}=1)
$$
这个状态转移方程可以视为是在 $f_{i,k,len-1}$ 的结尾再加上一个数 $j$，由于必须满足 $a_{k,j}=1$，那么显然加上 $j$ 之后的数列仍是一个幸运的数列。

显然如果每次都暴力把所有 $0$ 区间扫一遍，复杂度为 $O(nm)$，略微用脚趾一算就知道过不了，所以我们考虑用数据结构去维护。

那么什么数据结构能维护这样一种东西，同时时间复杂度还很优秀呢。

肯定是万能的线段树啊。

我们用每个节点表示这个区间内的答案是多少，然后在 pushup 的时候将两个儿子的答案乘起来，但由于每个区间两端的 $0$ 区间的长度并不明确，所以我们在计算这个节点的答案时并不能把这部分算进去，而应该在 pushup 时进行合并。

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20210104195117.png)

如上图，我们在计算左儿子的答案时，只计算前两个 $0$ 区间，也就是 $[2,2]$ 和 $[5,6]$ 的答案，而右儿子则直接不计算，因为它并没有一个完整的 $0$ 区间。

在 pushup 时，我们先把左儿子的答案乘上右儿子的答案，然后再计算它们中间夹的那个 $0$ 区间的答案，这样上面那个节点的答案就是 $[2,2]$，$[5,6]$ 和 $[8,13]$ 三个 $0$ 区间的答案的乘积。

还有一点需要注意，如果这个数列中本来就有不幸运的数对，比如说我们定义幸运的数对有 $(1,2)$，$(2,3)$，但我们却把一个数列修改成了 $1,3,0,0,2$ 这样，那么不论那些 $0$ 怎么变，都不会有幸运的数列产生，此时则应输出 $0$，对应到线段树上，我们发现其实只需要在 pushup 的时候，判断左右儿子最边上的两个数（设为 $x$ 和 $y$）是否非零，且 $(x,y)$ 不是一个幸运的数对就行了，如果出现这种情况，就直接把这个节点的答案变成 $0$（其他时候默认都为 $1$），这样在算的时候答案就一定为 $0$ 了。

在查询的时候，我们只需要对根节点进行计算，先找到它记录的答案，再统计它左右两边没有被算进这个节点的答案的 $0$ 区间的方案数，最后乘起来就行了，不过这里还要特判，如果整个序列都为 $0$ 的话，就需要特殊计算。

具体的看一下代码吧。

## 参考代码

```cpp
#include <bits/stdc++.h>
#define judge(x) (tree[x].lz == tree[x].r-tree[x].l+1)//拿来判断这个节点的区间里的数是否全为 0
using namespace std;
namespace IO
{
	char buf[1<<23],*p1=buf,*p2=buf;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
	#define isdigit(c) (c>=48&&c<=57)
	#define isalpha(c) ((c>=65&&c<=90)||(c>=97&&c<=122))
	template<typename T> inline void read(T &x)
	{
		x=0;
		register char ch=getchar();
		while(!isdigit(ch))
			ch=getchar();
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^48);
			ch=getchar();
		}
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args)
	{
		read(t);read(args...);
	}
}
using namespace IO;
typedef long long ll;
const int N = 8e4+10, inf = 0x3f3f3f3f, mod = 777777777;
struct SegTree
{
	int l;//表示区间的左端点
	int r;//表示区间的右端点
	int lz;//靠着左边的 0 区间的长度
	int rz;//靠着右边的 0 区间的长度
	int ln;//左边第一个不为 0 的数
	int rn;//右边第一个不为 0 的数
	ll dat;//这个区间里除开左右两端其他 0 区间的答案乘积（也就是这个区间的答案）
};
SegTree tree[N<<2];
int n, m, a[10][10];
ll f[N][10][10];
inline void push_up(int i)
{
	tree[i].lz = tree[i<<1].lz;
	tree[i].rz = tree[i<<1|1].rz;
	tree[i].ln = tree[i<<1].ln;
	tree[i].rn = tree[i<<1|1].rn;//这四句显然，不再解释
	if(judge(i<<1) && judge(i<<1|1))//如果左右儿子的区间都是 0 区间
	{
		tree[i].lz = tree[i].rz = tree[i].r-tree[i].l+1;
		tree[i].dat = 1;
	}
	if(judge(i<<1) && !judge(i<<1|1))//如果左儿子的区间是 0 区间，右儿子的不是
	{
		tree[i].lz += tree[i<<1|1].lz;
		tree[i].ln = tree[i<<1|1].ln;
		tree[i].dat = tree[i<<1|1].dat;
	}
	if(!judge(i<<1) && judge(i<<1|1))//如果左儿子的区间不是 0 区间，右儿子的是
	{
		tree[i].rz += tree[i<<1].rz;
		tree[i].rn = tree[i<<1].rn;
		tree[i].dat = tree[i<<1].dat;
	}
	if(!judge(i<<1) && !judge(i<<1|1))//如果两个儿子的区间都不是 0 区间
	{
		tree[i].dat = tree[i<<1].dat*tree[i<<1|1].dat%mod;
		if(tree[i<<1].rz || tree[i<<1|1].lz)//单独统计两个儿子中间夹的那个 0 区间
		{
			ll t = 0;
			for(int j = 1; j <= 3; j++)
				for(int k = 1; k <= 3; k++)
					if(a[tree[i<<1].rn][j] && a[k][tree[i<<1|1].ln])
						t = (t+f[tree[i<<1].rz+tree[i<<1|1].lz][j][k])%mod;
			tree[i].dat = tree[i].dat*t%mod;
		}
	}
	if(!tree[i<<1].rz && !tree[i<<1|1].lz && !a[tree[i<<1].rn][tree[i<<1|1].ln])//判断是否有不合法的数对
		tree[i].dat = 0;
}
void build(int i, int l, int r)
{
	tree[i].l = l;
	tree[i].r = r;
	tree[i].lz = tree[i].rz = r-l+1;
	tree[i].dat = 1;
	if(l == r)
		return;
	int mid = (l+r)>>1;
	build(i<<1, l, mid);
	build(i<<1|1, mid+1, r);
}
void update(int i, int x, int k)
{
	if(tree[i].l == tree[i].r)//显然，不做解释
	{
		if(k)
			tree[i].lz = tree[i].rz = 0;
		else
			tree[i].lz = tree[i].rz = 1;
		tree[i].ln = tree[i].rn = k;
		return;
	}
	if(tree[i<<1].r >= x)
		update(i<<1, x, k);
	else
		update(i<<1|1, x, k);
	push_up(i);
}
ll query()
{
	if(tree[1].lz == n)//判断是否整个数列的数都为 0
	{
		ll t = 0;
		for(int i = 1; i <= 3; i++)
			for(int j = 1; j <= 3; j++)
				t = (t+f[n][i][j])%mod;
		return t;
	}
	ll ans = tree[1].dat;
	if(tree[1].lz)//左边的 0 区间
	{
		ll t = 0;
		for(int i = 1; i <= 3; i++)
			for(int j = 1; j <= 3; j++)
				if(a[j][tree[1].ln])
					t = (t+f[tree[1].lz][i][j])%mod;
		ans = ans*t%mod;
	}
	if(tree[1].rz)//右边的 0 区间
	{
		ll t = 0;
		for(int i = 1; i <= 3; i++)
			for(int j = 1; j <= 3; j++)
				if(a[tree[1].rn][i])
					t = (t+f[tree[1].rz][i][j])%mod;
		ans = ans*t%mod;
	}
	return ans;
}
signed main()
{
	read(n, m);
	for(int i = 1; i <= 3; i++)
		for(int j = 1; j <= 3; j++)
			read(a[i][j]);
	f[1][1][1] = f[1][2][2] = f[1][3][3] = 1;
	for(int i = 2; i <= n; i++)//DP 预处理，上面解释过了
		for(int j = 1; j <= 3; j++)
			for(int k = 1; k <= 3; k++)
				for(int l = 1; l <= 3; l++)
					if(a[l][k])
						f[i][j][k] = (f[i][j][k]+f[i-1][j][l])%mod;
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		int v;
		ll t;
		read(v, t);
		update(1, v, t);
		printf("%lld\n", query());
	}
	return 0;
}
```

~~所以为什么分块过不了啊喂。~~

---

## 作者：WeLikeStudying (赞：1)

**题意**
- [题目链接](https://www.luogu.com.cn/problem/CF256E)。
- 一个 $n$ 行 $m$ 列的矩阵，给出一个 $m\times m$ 的转移方阵，表示第 $i$ 行某一列可以走到第 $i+1$ 行的哪一列。
- 一开始规定某行只能走哪一列（或者都能走），支持 $q$ 次单点修改，问从第一行走到最后一行的方案数。
- $n\le 77777,q\le77777,m=3$。

**分析**
- 由于 $m$ 较小，考虑线段树维护从左端点 $i$ 走到右端点 $j$ 的方案数，发现区间信息合并相当于做矩阵乘法，用普通的线段树维护即可，十分简单。
- 维护的转移类似于矩阵的转移，详细见代码。
- 由于我们路径之间还有一个转移序列，所以合并信息时需要乘上那个矩阵。
- 说句实话，作者不习惯写这么短的博文，不过这个确实没啥思维，思想和动态动态规划（$\text{DDP}$）类似，可以作为基础入手的模板题？
- [代码实现](https://www.luogu.com.cn/paste/5ph84j9a)。

---

