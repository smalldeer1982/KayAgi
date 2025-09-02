# Palindrome XOR

## 题目描述

给定一个由字符 “1”、“0” 和 “?” 组成的字符串 $s$。保证 $s$ 的第一个字符为 “1”。设 $m$ 为 $s$ 的长度。

请你统计有多少对整数 $a, b$ 满足以下条件：

- $1 \leq a < b < 2^m$；
- $a$ 和 $b$ 的二进制表示（不含前导零）都是回文串；
- $a$ 和 $b$ 按位异或后的二进制表示与 $s$ 匹配。这里称 $t$ 与 $s$ 匹配，指的是 $t$ 和 $s$ 长度相同，且对于每个 $i$，$t$ 的第 $i$ 个字符等于 $s$ 的第 $i$ 个字符，或者 $s$ 的第 $i$ 个字符为 “?”。

请你输出满足条件的对数，答案对 $998244353$ 取模。

## 说明/提示

对于第一个样例，满足条件的二进制对为 $(111, 10001), (11, 10101), (1001, 11111)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10110
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1?0???10
```

### 输出

```
44
```

## 样例 #3

### 输入

```
1?????????????????????????????????????
```

### 输出

```
519569202
```

## 样例 #4

### 输入

```
1
```

### 输出

```
0
```

# 题解

## 作者：duyi (赞：3)

## 题解 CF1147D Palindrome XOR

首先，因为保证了$s_1=1$，又要求$a<b$，所以显然可以确定$a_1=0,b_1=1$。

现在$b$的最高位已经确定了，而$a$的最高位还不知道。注意到数据范围只有$1000$，于是想到枚举$a$的最高位。

考虑枚举了$a$的最高位为$i$ ($2\leq i\leq n$)。则$a_{1\dots i-1}$都必须等于$0$，$a_i$必须等于$1$。

然后其他位怎么确定呢？如果你试图观察这个串的性质，找循环节之类的，会很麻烦。本题的难点就在这一步：要想到用**图论的模型**去解决。

问题相当于：有$2n$个点，点权为$\{0,1\}$。一些点的点权已经确定，其他点还未确定。有一些限制条件形如：点$u$和点$v$的权值必须相等，或点$u$和点$v$的权值必须不等。问有多少种满足条件的点权方案。

考虑建一张$2n+2$个点的图。其中两个点$0,1$，它们的权值就分别为$0,1$，已经确定。然后在其它点之间连边。有两种边：边权为$0$表示这两个点权值必须**相等**；边权为$1$表示这两个点权值必须**不等**。具体来说：

- 先在$0,1$两个点之间连一条边权为$1$的边（表示它们权值不等）。
- 对于点$u$，如果权值已经确定为$0$或$1$，则向$0$或$1$连边权为$0$的边。
- 对于一个位置$j$ ($1\leq j\leq n$)，如果$s_j=0$，则$a_j,b_j$之间连一条边权为$0$的边；如果$s_j=1$，则$a_j,b_j$之间连一条边权为$1$的边；如果$s_j=\text{?}$，则不连边（表示没有限制）。
- 对于一个位置$k$ ($1\leq k\leq n$)，在$b_k$和$b_{n-k+1}$之间连边权为$0$的边（这样能保证回文）。对$a$同理。

建好图后，我们先把由权值为$0$的边相连的点缩起来（可以用并查集实现）。然后图上就只剩权值为$1$的边了：每条边两端都必须不等。那么，显然，图上每个连通块，都必须是二分图，否则方案数为$0$。判断二分图可以用$\text{dfs}$染色实现，时间复杂度$O(n)$。

现在已经判断了每个连通块都是二分图。设有$c$个连通块，则合法的染色方案数就是$2^{c-1}$。因为每个连通块里，只要确定了其中任意一个点的权值，其他点的权值就都确定了。而减$1$是因为包含点$0,1$的这个连通块，$0$这个点权值天然就是$0$，所以这个连通块里所有值，一开始就都已经确定了。

总时间复杂度$O(n^2)$。

总结一下，本解法最妙的地方，还是在于用**图论**的模型，来刻画这些限制。这有点像$\text{2-SAT}$，但本题并不是$\text{2-SAT}$。因为本题里，我们连的都是**无向边**。这也使得我们可以计算出方案数。而经典的$\text{2-SAT}$是不能求方案数的（只能判断可行性、构造一组方案）。

参考代码：

```cpp
//problem:
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MOD=998244353;
const int MAXN=1000;
inline int mod1(int x){return x<MOD?x:x-MOD;}
inline int mod2(int x){return x<0?x+MOD:x;}
inline void add(int& x,int y){x=mod1(x+y);}
inline void sub(int& x,int y){x=mod2(x-y);}
inline int pow_mod(int x,int i){int y=1;while(i){if(i&1)y=(ll)y*x%MOD;x=(ll)x*x%MOD;i>>=1;}return y;}

int pw[MAXN*2+5];

int n;
char s[MAXN+5];

int id_a[MAXN+5],id_b[MAXN+5],id[2],cnt_id;
int fa[MAXN*2+5],sz[MAXN*2+5];
int get_fa(int x) { return (fa[x]==x) ? x : (fa[x]=get_fa(fa[x])); }
void unite(int u,int v){
	u=get_fa(u);v=get_fa(v);
	if(u!=v){
		if(sz[u]>sz[v]) swap(u,v);
		fa[u]=v;
		sz[v]+=sz[u];
	}
}

struct EDGE{int nxt,to;}edge[MAXN*2+100];
int head[MAXN*2+5],tot;
inline void add_edge(int u,int v) { edge[++tot].nxt=head[u];edge[tot].to=v;head[u]=tot; }

int col[MAXN*2+5];
bool fail;
void dfs(int u){
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(col[v]){
			if(col[v]==col[u]){
				fail=true;
				return;
			}
			continue;
		}
		col[v]=3-col[u];
		dfs(v);
		if(fail) return;
	}
}

int main() {
	cin>>(s+1); n=strlen(s+1);
	cnt_id=0;
	id[0]=++cnt_id;
	id[1]=++cnt_id;
	for(int i=1;i<=n;++i){
		id_a[i]=++cnt_id;
		id_b[i]=++cnt_id;
	}
	pw[0]=1;
	for(int i=1;i<=cnt_id;++i)
		pw[i]=mod1(pw[i-1]<<1);
	int ans=0;
	for(int st=2;st<=n;++st){
		for(int i=1;i<=cnt_id;++i){
			fa[i]=i;
			sz[i]=1;
			head[i]=0;
			col[i]=0;
		}
		tot=0;
		unite(id_a[st],id[1]);
		unite(id_b[1],id[1]);
		for(int i=1;i<st;++i){
			unite(id_a[i],id[0]);
		}
		for(int i=st;i<=n;++i){
			int l=i-st+1;
			unite(id_a[i],id_a[n-l+1]);
		}
		for(int i=1;i<=n;++i){
			unite(id_b[i],id_b[n-i+1]);
			if(s[i]=='0'){
				unite(id_a[i],id_b[i]);
			}
		}
		add_edge(get_fa(id[0]),get_fa(id[1]));
		add_edge(get_fa(id[1]),get_fa(id[0]));
		for(int i=1;i<=n;++i){
			
			if(s[i]=='1'){
				add_edge(get_fa(id_a[i]),get_fa(id_b[i]));
				add_edge(get_fa(id_b[i]),get_fa(id_a[i]));
			}
		}
		fail=false;
		int cnt_cc=0;//connected componet
		for(int i=1;i<=cnt_id;++i){
			if(get_fa(i) == i && !col[i]){
				col[i]=1;
				dfs(i);
				if(fail) break;
				cnt_cc++;
			}
		}
		if(fail) continue;
		add(ans,pw[cnt_cc-1]);
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Hydroxythio (赞：1)

看见这道题的题解都是 $dfs$ 染色，那我来一发带权并查集。

如果没有特殊说明，下文的 $a,b$ 都是二进制。

因为有 $1 \leq a < b < 2^m$ 的限制存在，同时 $a \ XOR \ b = s,s_1=0$，不难发现 $a$，$b$ 的位数一定不同，而且 $b$ 的位数为 $m$，最高位为 $1$，否则无法满足 $a \ XOR \ b = s$。

但是 $a$ 的位数是未知的，由于 $1 \leq m \leq 1000$，考虑枚举 $a$ 的位数。设 $a$ 的位数为 $n$。

题目要求 $a,b$ 回文，也就是 $\forall \ m-n+1 \leq i \leq m,1 \leq j \leq m$，有 $a_i=a_{n-i+1},b_j=b_{m-j+1}$。而 $a \ XOR \ b = s$，就是 $\forall 1 \leq i \leq m$，有 $a_i=b_i (s_i=0),a_i \neq b_i (s_i = 1)$，特别地，如果 $s_i= \ ?$，那么 $a_i,b_i$ 之间没有限制，对于 $\forall i \leq m-n$，有 $a_i=0$。此外，显然有 $a_{m-n+1}=b_1=1$。

简单地说，回文的限制和异或 $=s$ 的限制告诉了我们 $a,b$ 中哪些位是相等或者不等的。因此我们把这些相关的位分到一组里面，可以得到若干组，对于一组中的一些位，任意一位确定了值是 $0,1$，那么整组的值都唯一确定。但是注意由于 $a_{m-n+1}=b_1=1$，一定有一组只有一种取值，其他组的值都有两种，那么 $a$ 的位数为 $n$ 的答案就是 $2^{cnt-1}$，其中 $cnt$ 表示组数。特别地，如果某组中存在相互矛盾的关系，那么 $a$ 的位数为 $n$ 的答案为 $0$。

分组显然可以用带权并查集来维护。我们把 $b$ 的每一位标记为 $1,2,\cdots ,m$，把 $a$ 的每一位标记为 $m+1,m+2 \cdots ,m+m$，如果确定某两位相同或者不同，就用带权并查集合并起来，同时标记这两位相同或不同。合并的时候顺便判断是否矛盾。总时间复杂度 $O(m^2)$。

参考代码如下：
```c++
#include <bits/stdc++.h>

using namespace std;

const int mod=998244353;
const int Maxn=2005;
int n;
char str[1005];
int fath[Maxn],dis[Maxn];

inline int& md(int &a) {return a<mod?a:(a-=mod);}

int power(int a,int n,int p)
{
	//UOIAKer的快速幂
	int ans=1;a%=p;
	for (;n;n>>=1,a=1ll*a*a%p) if (n&1) ans=1ll*ans*a%p;
	return ans;
}

int Find(int x)
{
	if (fath[x]==x) return x;
	int rt=Find(fath[x]);
	dis[x]^=dis[fath[x]];
	return fath[x]=rt;
}

bool Merge(int a,int b,int c)
{
	int x=Find(a),y=Find(b);
	if (x==y) return dis[a]^dis[b]^c^1;
	fath[x]=y;
	dis[x]=dis[a]^dis[b]^c;
	return true;
}

int solve(int la)
{
	for (int i=1;i<=n+n;++i) {
		fath[i]=i;dis[i]=0;
	}
	for (int i=1;i<=n/2;++i) Merge(i,n-i+1,0);
	for (int i=1;i<=la/2;++i) Merge(n+i,n+la-i+1,0);
	for (int i=la+1;i<n;++i) Merge(n+i,n+n,0);
	Merge(1,n+1,0);
	for (int i=1;i<=n;++i) {
		if (str[n-i+1]=='?') continue;
		if (!Merge(n+i,i,str[n-i+1]-48)) return 0;
	}
	int cnt=0;
	for (int i=1;i<=n+n;++i) cnt+=fath[i]==i;
	return power(2,cnt-1,mod);
}

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);int ans=0;
	for (int i=1;i<n;++i) md(ans+=solve(i));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：SkyRainWind (赞：1)

因为 s 首位为 1，所以 a<2^(m-1) 2^(m-1)<=b<2^m，确定了 b 的位数

建图，边分 0/1 两种，0代表两端数的对应二进制位相等，1代表不等

将 a[i] a[n-1-i] 连 0边（回文） b 同理
建两个虚点 0 1 （2*n 、2*n+1）虚点见连 1 边

如果 s[i] 对应的位为 1，则 a b 间连 1 边，否则若为 0，连 0 边，'?' 不操作
b 比 a 多的那些位 a 与 0 点连 0 边 （因为这一位必须没有）

注意 a b 不能有前导 0，直接 与 2*n 连 1 边即可 

代码：


```cpp
// by Balloons
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#define mpr make_pair
#define debug() puts("okkkkkkkk")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)

using namespace std;

typedef long long LL;

const int inf = 1 << 30;
const int mod=998244353;
const int maxn=2005;

string s;
LL ans=0;
int n;
vector<pair<int,int> >edges[maxn];
int col[maxn],vis[maxn];
int isbi=1;

void flood(int x,int curcol){
	if(vis[x]){
		if(col[x]!=curcol){
			isbi=0;
		}
		return ;
	}
	vis[x]=1;
	col[x]=curcol;
	for(int i=0;i<edges[x].size();i++){
		int u=edges[x][i].first,v=edges[x][i].second;
		flood(u,curcol ^ v);
	}
}

int pw(int x,int y){
	if(!y)return 1;
	if(y==1)return x;
	int mid=pw(x,y>>1);
	if(y&1)return 1ll*mid*mid%mod*x%mod;
	return 1ll*mid*mid%mod; 
}

int sear(){
	isbi=1;
	int con=0;
	for(int i=0;i<=2*n+1;i++){
		if(!vis[i]){
			flood(i,0);
			++ con;
		}
	}
	if(!isbi)return 0;
	return pw(2,con-1);
}

int solve(int m){
	memset(vis,0,sizeof vis);
	memset(col,-1,sizeof col);
	for(int i=0;i<=maxn-1;i++)edges[i].clear();
	for(int i=0;i<n;i++){	// b
		edges[i].push_back(mpr(n-1-i,0));
	}
	for(int i=0;i<m;i++){	// a
		edges[i+n].push_back(mpr(n+(m-1-i),0));
	}
	for(int i=m;i<n;i++){
		edges[i+n].push_back(mpr(2*n,0));	// 2*n --> 0
		edges[2*n].push_back(mpr(i+n,0));
	}
	for(int i=0;i<n;i++){
		if(s[n-1-i]=='0'){
			edges[i].push_back(mpr(i+n,0));
			edges[i+n].push_back(mpr(i,0));
		}else if(s[n-1-i]=='1'){
			edges[i].push_back(mpr(i+n,1));
			edges[i+n].push_back(mpr(i,1));
		}
	}
	edges[2*n].push_back(mpr(2*n+1,1));
	edges[2*n+1].push_back(mpr(2*n,1));
	
	edges[n].push_back(mpr(2*n,1));
	edges[2*n].push_back(mpr(n,1));
	edges[0].push_back(mpr(2*n,1));
	edges[2*n].push_back(mpr(0,1));
//	cout<<"ed   "<<edges[2*n+1].size()<<endl;
	
	return sear();
}

int main(){
	ios::sync_with_stdio(false);
	cin>>s;
	n=s.size();
	for(int i=1;i<n;i++){
		ans = (ans+solve(i))%mod;
//		printf("%d\n",ans);
	}
	cout<<ans<<endl;

	return 0;
}

```


---

## 作者：Sharpsmile (赞：0)

# Palindrome XOR

一个非常好玩的题目。

看到题解里都是高深的 dfs 做法，感觉好难。需要进行建图 dfs，好像还需要缩点？感觉有点复杂。

这里写一个比较无脑的做法，有可能本质上是和另外几位佬的做法一致的，但是个人感觉简单好想。

前面的步骤与另外几位大体一致，枚举 $a$ 的最高位是哪一位。然后大概搞一个图状物。但是我们并没有必要把他建出来。

我们观察一下这两个串的性质，一个相当好的性质是他们是回文的。这个时候我们发现：通过两个回文中心相互捯饬，对于每一个位置，他一步可以到达至多两个点。也就是说感觉上这个东西会变成一个链状物或环状物。

稍微手玩一下，你会发现只有链，我们用这些“边”一定可以将原来的两个串划分为以下形式：由若干条互不相交的链组成，且每一条链都有至少一个端点在裸露部分。这里裸露部分的定义是那些 $b$ 有 $a$ 没有的位。

我们对链稍加整理，大致得到了这样一种东西：![](https://cdn.luogu.com.cn/upload/image_hosting/lvvp0ldb.png)

其中每一个拐点都是一个原序列的位。

有了这种之后，我们就可以继续无脑的上一个 $dp$。

这张图求解方案数等价于：将每一个横线设定一个权值，竖线的权值为与其相接的横线权值异或和，且应等于题目中所给的参数。

对于这个东西，我们只需要定义 $dp_{i,1/0}$ 表示当前考虑到了第 $i$ 条横线，且这条横线的权值为 $0/1$ 的方案数即可。转移是朴素的。 然后需要注意的是 $a$ 的最高位应该为 $1$，需要在对应位置清除 $0$ 的方案。在实际操作过程中，你甚至不需要把数组建出来，直接从上一个向下一个推即可。

最后我们把所有链的方案数相乘得到对于固定 $a$ 最高位的方案数，然后相加得解。

感觉这个做法和其他题解很像但是相对无脑了一点（只是可能实际写的时候有点麻烦，边界可能有点多。下方挂出主题代码以供参考。


```cpp
inline int OP(int x,int l,int r){
    if(x<l||x>r)exit(0);
    int d=x-l;
    return r-d;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>s;
    n=s.size();
    s=" "+s;
    int ans=0;
    for(int i=1;i<n;i++){
        memset(vis,0,sizeof(vis));
        int res=1;
        for(int j=1;j<=n;j++)
            if(!vis[j]){
                int x=j;bool p=1;
                vector<int>T;vis[j]=1;
                while(1){int pt=x;
                    if(p)x=OP(x,1,n);
                    else x=OP(x,n-i+1,n);
                    vis[x]=1;
                    if(x==pt)break;T.push_back(x);
                    if(x<n-i+1)break;p^=1;
                }
                int X=x,d1=0,d0=0;bool fl=0;
                if(s[j]=='1'||s[j]=='?')d1++;
                if(s[j]=='0'||s[j]=='?')d0++;
                for(int x:T)if(x!=X||x>=n-i+1){
                    if(fl==1&&x==n-i+1)d0=0;
                    int t1=0,t0=0;
                    if(s[x]=='1') t0=d1,t1=d0;
                    else if(s[x]=='0') t0=d0,t1=d1;
                    else t0=(d1+d0)%M,t1=(d1+d0)%M;
                    fl^=1;
                    if(fl==1&&x==n-i+1)t0=0;
                    d1=t1,d0=t0;
                }
                if(X<n-i+1){
                    if(s[X]=='1')res=(res*d1)%M;
                    else if(s[X]=='0')res=(res*d0)%M;
                    else res=(res*(d1+d0))%M;
                }
                else res=(res*(d1+d0))%M;
            }
        ans=(ans+res)%M;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

