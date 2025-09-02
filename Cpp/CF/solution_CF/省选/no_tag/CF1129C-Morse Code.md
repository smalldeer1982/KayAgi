# Morse Code

## 题目描述

在摩尔斯电码（以下简称“摩码”）中，字母表中的一个字母被表示为一个长度为$1$~$4$的01串。长度为$1$~$4$的01串共有$2^1+2^2+2^3+2^4=30$个，而字母只有$26$个，所以有$4$个01串不表示任何字母——"0011"、"0101"、"1110"、"1111"，其他$26$个01串表示互不相同的$26$个字母。
你有一个01串$S$，初始为空。现在有$m$次添加，每次往$S$的末尾添加一个字符（"0"或"1"）。对于每一次添加，你都要回答目前的$S$的所有非空子串用摩码所能表示的字母串的总数。由于答案可能巨大，你只需要输出答案模$10^9+7$的结果。

## 样例 #1

### 输入

```
3
1
1
1
```

### 输出

```
1
3
7
```

## 样例 #2

### 输入

```
5
1
0
1
0
1
```

### 输出

```
1
4
10
22
43
```

## 样例 #3

### 输入

```
9
1
1
0
0
0
1
1
0
1
```

### 输出

```
1
3
10
24
51
109
213
421
833
```

# 题解

## 作者：chenxia25 (赞：8)

>### [洛谷题目页面传送门](https://www.luogu.org/problemnew/show/CF1129C) & [CodeForces题目页面传送门](https://codeforces.com/contest/1129/problem/C)

>题意见洛谷里的翻译。

首先我们可以用区间DP算出对于每个子01串，能表示的字母串的个数。

设$dp_{i,j}$表示长度为$i$，起点为$j$（下标从$1$开始）的子01串能表示的字母串的个数（也许我设的DP状态有点奇怪）。显然，$dp_{0,i}=1$，因为空子01串能且仅能表示空字母串。

那么转移怎么转移呢？可以从串的首部转移，从首部挖出$1\sim4$个字符组成字母，累加上剩下的串的DP值。那么状态转移方程为$dp_{i,j}=\sum\limits_{k=1}^{\min(4,i)}dp_{i-k,j+k}$，其中$k=4$时还要考虑首部$4$个字符是否为不能表示字母的那可怜的$4$个01串，如果是的话，就不能累加上$dp_{i-4,j+4}$。同样的道理，从尾部转移也是可以的。转移的总时间复杂度是$\mathrm{O}\left(n^2\right)$，因为一共有$\mathrm{O}\left(n^2\right)$个子01串，而每次转移是$\mathrm{O}(1)$的。

接下来要算答案了。设到当前第$i$次的添加字符后，答案为$ans$，那么容易想到，下一次（第$i+1$次）添加字符后，增加了$[1,i+1],[2,i+1],\cdots,[i+1,i+1]$这$i+1$个子01串，答案变成了$ans+\sum\limits_{j=1}^{i+1}dp_{i+1-j+1,j}$，我们把$\sum\limits_{j=1}^{i+1}dp_{i+1-j+1,j}$累加到$ans$里。但是，在累加的过程中，可能对于有的$j$，$[j,i+1]$这段子01串和之前累加的有重复，也就是说这段子01串所能表示的所有字母串都被算过了，就不能再把$dp_{i+1-j+1,j}$累加上了。所以我们需要判重。

我们可以预处理出前缀哈希数组$Hsh$，这样可以在$\mathrm{O}(1)$时间内计算出任意一个子串的哈希值。然后怎么判重呢？用一个$vis$数组肯定不行，因为哈希值在$\left[0,2^{64}\right)$内，会MLE。用裸的`set`，要判$\mathrm{O}\left(n^2\right)$次，每次$\mathrm{O}\left(\log_2n^2\right)=\mathrm{O}(\log_2n)$，总共$\mathrm{O}\left(n^2\log_2n\right)$；将`set`按子01串长度分成$n$组，也还是$\mathrm{O}\left(n^2\log_2n\right)$。这复杂度配上STL的常数，会TLE。

那该怎么办呢？事实上，`set`的组数其实应该尽可能多，那样每个`set`的元素个数就尽可能少，复杂度就尽可能小。不妨按哈希值模$10^7$的值分为$10^7$组。这样分，平均每组只有一两个元素，用`set`还亏了，直接用链式前向星装即可。

以下是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 3000
#define hshmod 10000000//将哈希分为的组数
#define mod 1000000007
#define ull unsigned long long
bitset<N+1> a;//01串
int dp[N+1][N+2];//dp[i][j]表示长度为i，起点为j的子01串能表示的字母串数
inline bool ok(bool a,bool b,bool c,bool d){//是否能表示字母
	return !(!a&&!b&&c&&d||!a&&b&&!c&&d||a&&b&&c&&!d||a&&b&&c&&d);//不是那可怜的4个串就OK
}
ull Hsh[N+1]/*前缀哈希值*/,power[N+1]/*power[i]为哈希base（131）的i次方*/;
ull hsh(int l,int r){//[l,r]这段子01串的哈希值
	return Hsh[r]-Hsh[l-1]*power[r-l+1];
}
int head[hshmod],nxt[N*N],tot;ull data[N*N];//链式前向星
void add(int x,ull y){//往第x组里添加哈希值y
	data[++tot]=y;nxt[tot]=head[x];head[x]=tot;
}
int main(){
	int n/*添加字符的次数，即最终01串的长度*/,ans=0/*目前的答案*/,i,j;scanf("%d",&n);
	for(i=1;i<=n;i++){int x;scanf("%d",&x);a[i]=x;}
	power[0]=1;//131^0=1
	for(i=1;i<=n;i++)Hsh[i]=Hsh[i-1]*131ull+a[i]+1,power[i]=power[i-1]*131ull;//预处理
	fill(dp[0]+1,dp[0]+n+2,1);//DP边界：dp[i][0]=1
	for(i=1;i<=n;i++)for(j=1;j+i-1<=n;j++)//状态转移
		dp[i][j]=dp[i-1][j+1],
		dp[i][j]+=i>=2?dp[i-2][j+2]:0,dp[i][j]%=mod,
		dp[i][j]+=i>=3?dp[i-3][j+3]:0,dp[i][j]%=mod,
		dp[i][j]+=i>=4&&ok(a[j],a[j+1],a[j+2],a[j+3])?dp[i-4][j+4]:0,dp[i][j]%=mod;
//	for(i=1;i<=n;i++)for(j=1;j+i-1<=n;j++)
//		printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
	for(i=1;i<=n;i++){//第i次添加字符
		for(j=1;j<=i;j++){//枚举新增子01串的左端点，右端点是i
			ull h=hsh(j,i);//此新子01串的哈希值
			int hmod=h%hshmod;//它的类别
//			cout<<h<<" "<<hmod<<" "<<dp[i-j+1][j]<<"\n";
			bool mar=false;//是否和之前的某一个串重复
			for(int k=head[hmod];k;k=nxt[k])//枚举此组里的元素
				if(data[k]==h)//有和它的哈希值相同的？
					{mar=true;/*重复*/break;/*不必再找，退出*/}
			if(!mar)//如果无重复，照样累加
				ans+=dp[i-j+1][j],ans%=mod,add(hmod,h)/*扔进链表*/;
		}
		printf("%d\n",ans);//输出目前的答案
//		puts("");
	}
	return 0;
}
```

---

## 作者：夜猫子驱蚊器 (赞：3)

[官方题解](https://codeforces.com/blog/entry/65520)给了一个离线做法，而且是$O(m^2+m^2logm)$的，我的做法是在线的$O(m^2)$。我是用Trie树做哒，碰到子序列子串之类的问题有时候想想Trie树会有奇效喔QAQ

我们可以发现，不同的0/1子序列答案不会重复，那么就可以对所有不同的的0/1子序列计算有多少种英文刚好构成这个子序列。而Trie树上不会有相同的两个字符串，于是自然想到了对当前的$i$位0/1串的所有子序列一起建一棵Trie树。每次新增一位时，只需要在之前的答案上再加上所有后缀的答案就行了。这些新后缀都要被加入Trie树。

用$anc[x]$表示结点的父亲结点，$f[x]$表示从根到结点$x$的这个0/1串有多少种英文构成。假设当前要在Trie树上加入原串中第$i$个0/1，a数组中记录的就是Trie树中表示原串第$i-1$位的那些点。我们只需要在这些点的儿子加上第$i$位，就可以构成所有后缀了。每次在Trie树上新加一个点$x$，可以用DP的方法$O(1)$计算$f[x]$，再$ans+=f[x]$就行了

还有一种更方便的方法是直接把当前串反向再插入Trie树，不过当时本蒟蒻并没有想到。。

博主语文太烂了，感觉讲得可能不太清楚，具体有什么不懂的可以留言～[CSDN](https://blog.csdn.net/ymzqwq/article/details/88311549)上回复可能会比较及时，大家多多包涵QAQ


```cpp
#include<bits/stdc++.h>
#define ll long long
#define fr(i,x,y) for(int i=(x);i<=(y);i++)
#define rf(i,x,y) for(int i=(x);i>=(y);i--)
#define frl(i,x,y) for(int i=(x);i<(y);i++)
#define do_nothing 233
using namespace std;
const int N=3005;
const int p=1e9+7;
int n;
int trie[N*N][2],cnt,anc[N*N],f[N*N];
int ans;
int a[N],m;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}

void Add(int &x,int y){  //手动取模
	x+=y;
	while(x>=p) x-=p;
}

void add(int x,int d){  //在trie树上新增一个结点
	trie[x][d]=++cnt;
	anc[cnt]=x;
	int tmp=cnt,s=0,ss=0;
	fr(i,1,4){  //DP，枚举最后一个英文字母占几个0/1
		int ff=anc[tmp];
		if (trie[ff][0]==tmp) s=0;else s=1;
		ss+=s<<(i-1);
		tmp=ff;
		if (i==4&&(ss==3||ss==5||ss==14||ss==15)) do_nothing;
		 else Add(f[cnt],f[tmp]);
		if (tmp==0) break;
	}
	Add(ans,f[cnt]);
}

void ins(int x){  //在trie树上加入所有后缀
	a[++m]=0;
	fr(i,1,m){
		int tmp=a[i];
		if (!trie[tmp][x]) add(tmp,x);
		a[i]=trie[tmp][x];
	}
}

int main(){
	read(n);
	int x;
	f[0]=1;
	fr(i,1,n){
		read(x);
		ins(x);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：wucstdio (赞：2)

首先我们考虑怎么求一个串可行的字母串的总数。

考虑用DP来求。设$f_i$表示$1$到$i$这个子串的可行方案，转移的时候令$f_i=f_{i-1}+f_{i-2}+f_{i-3}+f_{i-4}$，然后再看长度为$4$是否合法，不合法减掉就行了。

接下来我们考虑怎样求所有子串的。由于这道题只支持插入，所以我们可以在每次插入后用上面那个DP求出所有后缀的可行方案，倒过来DP即可。

接下来考虑如何判断一个后缀是否出现过，如果没有出现过就加入。

我考场写了一个set，然后时间复杂度$O(n^2\log n)$光荣TLE了……

我们考虑建后缀自动机。由于后缀自动机对应反串后缀树，而所有新加入的后缀就对应了当前节点到根的路径上的点，所以要想使得这个后缀之前没有出现过，只需要查看它的子树中是否有除了新加入的点之外的其它点。比如$11000$这个字符串，建出来的反串后缀树是这样的：

![](https://cdn.luogu.com.cn/upload/pic/61522.png)

容易发现，$000,0001,00011$这三个字符串后面没有分叉，而$0,00$这两个字符串后面有分叉。

把字符串反过来我们可以发现，$0,00$这两个字符串之前出现过，而$000,0001,00011$这三个字符串之前没有出现过。

于是做法就出来了：对于一个新加入的字符，我们记录一下它所在的节点的父节点$node$，然后所有长度大于$len[node]$的都要加入答案，其余的都不能加入答案。

时间复杂度是$O(n^2)$，然而如果你提前注意到能加入的字符串长度一定连续的话就可以把前面会TLE的算法用个二分一优化就行了。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=1e9+7;
int m,a[3005];
ll f[3050];
struct Tree
{
	int child[2];
	int len;
	int fail;
}tree[6005];
int n,tot,last,p[30005];
void insert(int c)
{
	int now=++tot,node=last;
	tree[now].len=tree[node].len+1;
	while(node!=-1&&!tree[node].child[c])
	{
		tree[node].child[c]=now;
		node=tree[node].fail;
	}
	if(node==-1)tree[now].fail=0;
	else
	{
		int cur=tree[node].child[c];
		if(tree[cur].len==tree[node].len+1)tree[now].fail=cur;
		else
		{
			int clone=++tot;
			tree[clone]=tree[cur];
			p[clone]=p[cur];
			tree[clone].len=tree[node].len+1;
			while(node!=-1&&tree[node].child[c]==cur)
			{
				tree[node].child[c]=clone;
				node=tree[node].fail;
			}
			tree[cur].fail=tree[now].fail=clone;
		}
	}
	last=now;
}
int main()
{
	tree[0].fail=-1;
	scanf("%d",&m);
	ll ans=0;
	for(int n=1;n<=m;n++)
	{
		scanf("%d",&a[n]);
		insert(a[n]);
		p[last]=n;
		memset(f,0,sizeof(f));
		f[n+1]=1;
		for(int i=n;i>=1;i--)
		{
			f[i]=f[i+1]+f[i+2]+f[i+3]+f[i+4];
			if(!a[i]&&!a[i+1]&&a[i+2]&&a[i+3])f[i]-=f[i+4];
			if(!a[i]&&a[i+1]&&!a[i+2]&&a[i+3])f[i]-=f[i+4];
			if(a[i]&&a[i+1]&&a[i+2]&&!a[i+3])f[i]-=f[i+4];
			if(a[i]&&a[i+1]&&a[i+2]&&a[i+3])f[i]-=f[i+4];
			f[i]%=MOD;
			ans+=f[i];
		}
		int node=tree[last].fail;
		for(int i=tree[node].len;i>=1;i--)
		  ans-=f[n-i+1];
		ans%=MOD;
		printf("%I64d\n",ans);
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

设 $dp_{i,j}$ 表示 $j\sim i$ 能表示出的方案数，可以从 $dp_{i-1,j},dp_{i-2,j},dp_{i-3,j}$ 直接转移而来，因为 $[i,i],[i-1,i],[i-2,i]$ 组成的电码无限制，而 $dp_{i-4,j}$ 需要稍微判断下 $[i-3,i]$ 是否为无意义电码才能进行转移。最后答案为 $\forall l,r\in[1,i],\sum dp_{l,r}$，不过要去重，就是存在多个 $[l,r]$ 子串相同时只累加一次。

判重部分用字符串哈希加上手写哈希表。

---

## 作者：_edge_ (赞：1)

怎么题解区全是手写哈希表，或者 SA 和 SAM 这么抽象的做法。

容易设计一个 dp，做 $j \sim i$ 的有多少划分方式。

因此把问题转化为求某一段子串是否在之前出现过。

首先对于 $i$ 这个结尾来说，合法的子串一定是一段前缀，因此我们只需要求一下 $i$ 结尾和前面的 lcp 就可以了，这个可以递推。

总时间复杂度 $O(m^2)$ 常数非常小。


```cpp
#include <bits/stdc++.h>
#define int long long 
#define ull unsigned long long 
using namespace std;
const int INF=5e5+5;
const int base=233;
const int Mod=1e9+7;
const int INFN=5e6+5;
const int INFM=3e3+5;
int m,f[INF],tot;
int lcp[INFM][INFM];
string s1;
ull hash1[INF],cnt[INFN],ba[INF];
ull Get(int l,int r) {return hash1[r]-hash1[l-1]*ba[r-l+1];}
int Get2(ull x) {return lower_bound(cnt+1,cnt+1+tot,x)-cnt;}
signed main()
{
//	freopen("data.in","r",stdin);
//	freopen("test.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>m;s1=" "+s1;ba[0]=1;
	for (int i=1;i<=m;i++) ba[i]=ba[i-1]*233;
	for (int i=1;i<=m;i++) {char c;cin>>c;s1+=c;}
	for (int i=1;i<=m;i++) 
		for (int j=1;j<=m;j++)
			if (s1[i]==s1[j]) lcp[i][j]=lcp[i-1][j-1]+1;
			else lcp[i][j]=0;	
	int res=0;
	for (int i=1;i<=m;i++) {
		for (int j=1;j<=i+1;j++) f[j]=0;
		f[i+1]=1;int Max=0;
		for (int p=1;p<i;p++) Max=max(Max,lcp[i][p]);
		for (int j=i+1;j;j--) {
			for (int k=j-1;k;k--) {
				if (j-k>4) break;
				if (j-k==4) {
					if (s1[k]=='0' && s1[k+1]=='0' && s1[k+2]=='1' && s1[k+3]=='1') continue;
					if (s1[k]=='0' && s1[k+1]=='1' && s1[k+2]=='0' && s1[k+3]=='1') continue;
					if (s1[k]=='1' && s1[k+1]=='1' && s1[k+2]=='1' && s1[k+3]=='0') continue;
					if (s1[k]=='1' && s1[k+1]=='1' && s1[k+2]=='1' && s1[k+3]=='1') continue;
					f[k]+=f[j];
					if (f[k]>=Mod) f[k]-=Mod;
				} else {
					f[k]+=f[j];
					if (f[k]>=Mod) f[k]-=Mod;
				}
			}
			if (j==i+1) continue;
			if (i-j+1<=Max) continue; 
			res+=f[j];
			if (res>=Mod) res-=Mod;
		}
		cout<<res<<"\n";
	}
	return 0;
}
```

---

## 作者：qiyue7 (赞：1)

放个SAM版的 || 可以强制在线做 模仿求不同子串的做法 直接从border的前一位开始枚举dp到开头 枚举时状态不清空即可得到所有新增加后缀对答案的贡献，累加即可
（难点在于在线写的话 ，深搜的细节非常多，细节不好处理，但是思路是十分显然的）

```cpp
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
#include<cstdio>
using namespace std;
const int N = 10000;
struct SAM_node
{
	SAM_node *pre, *next[5];
	int step;
	void clear()
	{
		pre = 0;
		step = 0;
		memset(next, 0, sizeof(next));
	}
};
long d[N * 2];
SAM_node *pool[N * 2];
SAM_node SAM_Pool[N * 2];
struct SAM 
{
	SAM_node *root, *last;
	SAM_node  *cur;
	long tot2;
	long k;
	void init()
	{
		cur = SAM_Pool;
		root = last = cur++;
		root->clear();
	}
	void Insert(int w)
	{
		SAM_node *p = last;
		SAM_node *np = cur++;
		np->clear();
		np->step = p->step + 1;
		while (p && !p->next[w])
		{
			p->next[w] = np, p = p->pre;
		}
		if (p == 0)
			np->pre = root;
		else
		{
			SAM_node *q = p->next[w];
			if (p->step + 1 == q->step)
				np->pre = q;
			else
			{
				SAM_node *nq = cur++;
				nq->clear();
				memcpy(nq->next, q->next, sizeof(q->next));
				nq->step = p->step + 1;
				nq->pre = q->pre;
				q->pre = nq;
				np->pre = nq;
				while (p&&p->next[w] == q)
				{
					p->next[w] = nq, p = p->pre;
				}
			}
		}
		last = np;
	}
}part;
long long dp[10000];
int str[10000];
vector<int> anti[4];
const int mod = 1000000007;
long long dfs(int a,int end)
{
	if (dp[a] != -1)
		return dp[a];
	if (a == end)
		return 1;
	dp[a] = 0;
	vector<int> p;
	p.push_back(str[a]);
	int k = min(a + 3, end);
	for (int i = a + 1; i <= k; ++i)
	{
		dp[a] += dfs(i, end), p.push_back(str[i]);
		dp[a] = dp[a] % mod;
	}
	if (a + 3 >= end&&(p != anti[0] && p != anti[1] && p != anti[2] && p != anti[3]))
		dp[a]++;
	if ((p != anti[0] && p != anti[1] && p != anti[2] && p != anti[3]))
	{
		if (a + 4 <= end)
		{
			dp[a] += dfs(a + 4, end);
			dp[a] = dp[a] % mod;
		}
	}
	return dp[a];
}
long long ans1[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	memset(dp, -1, sizeof(dp));
	memset(str, 0, sizeof(str));
	anti[0].push_back(1);
	anti[0].push_back(1);
	anti[0].push_back(1);
	anti[0].push_back(1);
	anti[1].push_back(0);
	anti[1].push_back(0);
	anti[1].push_back(1);
	anti[1].push_back(1);
	anti[2].push_back(1);
	anti[2].push_back(1);
	anti[2].push_back(1);
	anti[2].push_back(0);
	anti[3].push_back(0);
	anti[3].push_back(1);
	anti[3].push_back(0);
	anti[3].push_back(1);
	int n,a;
	cin >> n;
	long long ans = 0;
	part.init();
	ans1[0] = 0;
	memset(ans1, 0, sizeof(ans1));
	for (int i = 1; i <= n; ++i)
	{
		memset(dp, -1, sizeof(dp));
		cin >> a;
		str[i] = a;
		part.Insert(a);
		for (int j = i - part.last->pre->step; j >= 1; --j)
		{
			//memset(dp, -1, sizeof(dp));
			ans1[i] += dfs(j, i);
			ans1[i] = ans1[i] % mod;
		}
		ans += ans1[i];
		ans = ans % mod;
		cout << ans << '\n';
	}
	return 0;
}
```


---

## 作者：hsfzLZH1 (赞：1)

## 题目大意

给定一个长度为 $n$ 的 01 字符串 $s$ ，求其所有前缀中所有本质不同的子串可以解码成合法的 **字母** 串，按照前缀的长度从 $1$ 到 $n$ 输出答案。

答案取模 $10^9+7$ 。

一个字符串 $p$ 可以被译为一个 **字母** 当且仅当 $1\le |s|\le 4$ 且 $p$ 不等于 $0011,0101,1110$ 或 $1111$ 。

一个字符串可以被译为一个 **字母** 串当且仅当其可以被分为若干个部分，这些部分都可以被译为一个 **字母** ；对于一个字符串，不同的分解方式被定义为分解方式不同。

$1\le n\le 3000$

## 解题思路

### 这是一个拼题

简单 DP $+($ 后缀数组 $+$ 链表 $)$

### 简单 DP

假如我们不要求本质不同的字符串的答案，而是求所有子串的答案。我们枚举一个起点位置 $x$ ，记 $f(x,i)$ 为从起点位置 $x$ 到位置 $i$ 所形成的字符串的不同分解方式个数，那么我们可以枚举合法的字母对应的 01 串 $p$ ，有 $f(x,i)=\sum f(x,i-|p|)$ ，可以通过一个 DP ，求出所有 $f$ 的值。

这部分的时间复杂度是 $O(n^2)$ 。

### 后缀数组

但是考虑到我们要求的是本质不同的字符串的答案，我们对字符串 $s$ 进行后缀排序，从当前位置开始本质不同的字符串就是和后缀排序位置上一个位置的 $LCP$ 之后的不同前缀。那么我们在统计的时候只需计算 $\sum_{i=sa_x+h_x}^n f(sa_x,i)$ 的值即可。

这部分的时间复杂度是 $O(n\log_2 n+n^2)$

### 链表

我们发现我们要求的值是给定字符串前缀的答案。我们翻转原字符串 $s$ ，将其后缀（即原串的前缀）从后缀数组中删除，并维护相邻的 $LCP$ 值，重新计算增加值。

我们用链表维护这个操作。首先记录每个位置在后缀排序中的位置，然后删除该位置时，合并其向左和向右的两个 $LCP$ 值，即取最小值，然后加上一些之前没有计算过的值。由于每个值只会被加上或减去都最多一次，所以这一部分的复杂度为 $O(n^2)$

总的时间复杂度为 $O(n^2)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=3010;
const int mod=1000000007;
int n,m,sa[maxn],x[maxn],y[maxn],c[maxn],rnk[maxn],h[maxn];
int s[maxn],f[maxn][maxn],ans[maxn],tot[maxn],r[maxn];
struct node
{
	int lft,rgt,lv,rv;
}ss[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=n;i>=1;i--)scanf("%d",s+i);
	m=2;
	for(int i=1;i<=n;i++)x[i]=s[i];
	for(int i=0;i<=m;i++)c[i]=0;
	for(int i=1;i<=n;i++)c[x[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
	for(int k=1,cur;k<=n;k<<=1)
	{
		cur=0;
		for(int i=n;i>n-k;i--)y[++cur]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)y[++cur]=sa[i]-k;
		for(int i=0;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
		cur=y[sa[1]]=1;
		for(int i=2;i<=n;i++)
		{
			int a,b;
			a=sa[i]+k>n?-1:x[sa[i]+k];
			b=sa[i-1]+k>n?-1:x[sa[i-1]+k];
			y[sa[i]]=(x[sa[i]]==x[sa[i-1]])&&(a==b)?cur:(++cur);
		}
		swap(x,y);
		if(cur>=n)break;
		m=cur;
	}
	for(int i=1;i<=n;i++)rnk[sa[i]]=i;
	int nww=0;
	for(int i=1;i<=n;i++)
	{
		if(rnk[i]==1)continue;
		if(nww)nww--;
		while(i+nww<=n&&sa[rnk[i]-1]+nww<=n&&s[i+nww]==s[sa[rnk[i]-1]+nww])nww++;
		h[rnk[i]]=nww;
	}
	for(int i=1;i<=n;i++)
	{
		f[i][i]=1;
		for(int j=i+1;j<=n;j++)
		{
			for(int k=max(i,j-3);k<=j;k++)//[k,j]
			{
				bool tf=true;
				if(k==j-3)
				{
					if(s[j-3]==1&&s[j-2]==1&&s[j-1]==1&&s[j]==1)tf=false;
					if(s[j-3]==1&&s[j-2]==1&&s[j-1]==0&&s[j]==0)tf=false;
					if(s[j-3]==1&&s[j-2]==0&&s[j-1]==1&&s[j]==0)tf=false;
					if(s[j-3]==0&&s[j-2]==1&&s[j-1]==1&&s[j]==1)tf=false;
				}
				if(tf)
				{
					f[i][j]+=(k==i?1:f[i][k-1]);
					f[i][j]%=mod;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)for(int j=sa[i]+h[i];j<=n;j++)
	ans[1]+=f[sa[i]][j],ans[1]%=mod,tot[sa[i]]+=f[sa[i]][j],tot[sa[i]]%=mod;
	for(int i=1;i<=n;i++)r[sa[i]]=sa[i]+h[i];
	sa[n+1]=n+1;
	for(int i=1;i<=n;i++)ss[sa[i]].lft=sa[i-1],ss[sa[i]].lv=h[i],ss[sa[i]].rgt=sa[i+1],ss[sa[i]].rv=h[i+1];
	for(int i=2;i<=n;i++)
	{
		ans[i]=(ans[i-1]-tot[i-1]+mod)%mod;
		ss[ss[i-1].lft].rgt=ss[i-1].rgt;
		ss[ss[i-1].rgt].lft=ss[i-1].lft;
		int minn=min(ss[i-1].rv,ss[i-1].lv);
		if(ss[i-1].rv!=minn)
		{
			for(int j=ss[i-1].rgt+minn;j<r[ss[i-1].rgt];j++)
			ans[i]+=f[ss[i-1].rgt][j],ans[i]%=mod,
			tot[ss[i-1].rgt]+=f[ss[i-1].rgt][j],tot[ss[i-1].rgt]%=mod;
			r[ss[i-1].rgt]=ss[i-1].rgt+minn;
		}
		ss[ss[i-1].lft].rv=minn;
		ss[ss[i-1].rgt].lv=minn;
	}
	for(int i=n;i>=1;i--)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：happybob (赞：0)

在序列末尾加一个数时，直接 DP 算新的贡献。$f_i$ 表示 $i$ 到末尾这一段能被视作多少个。由于摩斯密码长度很短，直接枚举 $i$ 被分在哪里即可。

但是考虑到有子串相同，我们对于每个后缀 $[i,n]$，判断加入 $s_n$ 前是否存在相同的子串。如果不存在则加上贡献。直接做是 $O(m^3)$ 的，考虑二分一下变成 $O(m^2 \log m)$ 即可通过。

---

## 作者：shinkuu (赞：0)

没有理解哪里有 *2400。

设 $dp_{i,j}$ 为区间 $[i,j]$ 的子串能表示多少种字符串。则有 $dp_{i,j}=\sum_{k\le 4} dp_{i,j-k}$ 并要求 $[j-k+1,j]$ 组成的子串不为题面给出的四个中的任意一个。容易发现这个 dp 本身就是增量的，所以题目中的“以此加入”对 dp 没有影响。

但是要去重，不过只用在统计答案的时候去除多余贡献。设当前加入的是第 $j$ 个，将 $[i,j]$ 这一段贡献加入答案前，先检查和 $[i,j]$ 相同的字符串是否之前就出现过。字符串哈希即可。

用一个 set 可以 $O(n^2\log n)$，TLE on 11，于是手写哈希表，过了。

code：

```cpp
int n,m,a[N],dp[N][N];
ull c[2],f[N],pw[N];
const ull base=19589103893ull;
mt19937 rnd(time(0));
const int d[4][4]={{0,0,1,1},{0,1,0,1},{1,1,1,0},{1,1,1,1}};
struct HashTable{
	const int mod=1e7+7;
	struct node{
		ull k;int nxt;
	}e[N*N];
	int tot,head[M];
	il void add(int u,ull x){
		e[++tot]={x,head[u]},head[u]=tot;
	}
	bool find(ull x){
		int p=x%mod;
		go(i,p){
			if(e[i].k==x){
				return 1;
			}
		}
		add(p,x);
		return 0;
	}
}H;
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il bool check(int l,int r){
	if(r-l<3){
		return 1;
	}
	rep(i,0,3){
		if(a[l]==d[i][0]&&a[l+1]==d[i][1]&&a[r-1]==d[i][2]&&a[r]==d[i][3]){
			return 0;
		}
	}
	return 1;
}
il ull getHash(int l,int r){
	return f[r]-f[l-1]*pw[r-l+1];
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,0,1){
		c[i]=1ull*rnd()*rnd()*rnd()*rnd();
	}
	pw[0]=1;
	int ans=0;
	rep(i,1,n){
		scanf("%d",&a[i]);
		f[i]=f[i-1]*base+c[a[i]];
		pw[i]=pw[i-1]*base;
		dp[i][i-1]=1;
		rep(j,1,i){
			rep(k,0,3){
				if(i-k>=j&&check(i-k,i)){
					dp[j][i]=Mod(dp[j][i],dp[j][i-k-1]);
				}
			}
			ull tmp=getHash(j,i);
			if(!H.find(tmp)){
				ans=Mod(ans,dp[j][i]);
			}
		}
		printf("%d\n",ans);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

