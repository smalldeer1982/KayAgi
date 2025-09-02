# Appleman and a Game

## 题目描述

Appleman and Toastman like games. Today they play a game with strings with the following rules. Firstly Toastman tells Appleman two strings $ s $ and $ t $ both consisting only of letters 'A', 'B', 'C', 'D'. Then Appleman must build string $ s $ as quickly as possible. Initially he has empty string, and in one second he can append to end of the current string any contiguous substring of $ t $ .

Now, Toastman and Appleman are beginning to play the game. Toastman has already told string $ t $ to Appleman, but he hasn't come up with string $ s $ yet. Toastman only thinks, that he should choose string $ s $ consisting of $ n $ characters. Of course, he wants to find the worst string for Appleman (such string, that Appleman will spend as much time as possible during the game). Tell Toastman, how much time will Appleman spend during the game if Toastman finds the worst string for him. You can assume that Appleman plays optimally, therefore he builds any string $ s $ in minimal possible time.

## 说明/提示

In the first example, Toastman can choose $ s $ equal to "AAAAA".

In the second example, Toastman can choose $ s $ equal to "DADDA".

## 样例 #1

### 输入

```
5
ABCCAD
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
AAABACADBABBBCBDCACBCCCDDDBDCDD
```

### 输出

```
4
```

# 题解

## 作者：YxYe (赞：8)

# [[CF461E] 苹果人和他的游戏 题解](https://www.luogu.com.cn/problem/CF461E)

题意稍微理解一下应该都能看懂叭——

一眼：最小值最大？可以二分答案耶！

然而本蒟蒻却用倍增做了~

## 思路

### Pre

我们先假设 $s$ 已知，那么对面的策略就是**贪心**，能匹配就继续匹配，直到不能再匹配了，然后再重新找一个子串开始匹配。

原因是如果对面现在不继续匹配，那么显然不会更优（毕竟你再拿一个就后面匹配是少拿一个，并不会影响匹配串数）

所以我们最终构造出来的字符串 $s$ 一定是一个由无数段 $t$ 中的子串构成的。

如果想让次数更多，那么尽可能使得每一个段最短。

### Solve

我会 dp！**动态规划**，设 $f[i][j]$ 表示以 $i$ 作为开头，在其结尾放 $j$，不会产生一个新的 $t$ 的子串，生成的段的最短长度（即当前串已经贪心到无法扩展）。

注意到 $n$ 的范围，显然会超时。

我会优化！考虑**倍增**，每次合并两个匹配好的串， $f[i][j][l]$ 记录合并了 $2^l$ 个串的结果。那么转移方程即为：

$$ f[i][j][l]=\min{(f[i][k][l-1]+f[k][j][l-1])} $$

统计答案就是倍增的套路了，逆序枚举 $l$，若当前答案小于 $n$ 就合并，否则继续。

### Code

我会实现！用 trie 维护原串的前缀，然后 dfs 预处理 $f$ 数组的 $l=2^0$ 这一维。你一定会问 trie 开这么大空间不会炸吗？注意到当字符串大于 $\log_4{|s|}$ 时不优，所以建树深度就可以优化到 $\log_4{|s|}$ 级别。

> Talk is cheap, show you my code.

## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#define ll long long
#define db double
#define fo(i,a,b) for(int i=(a);i<=(b);i++)
#define fp(i,a,b) for(int i=(a);i<(b);i++)
#define de(i,a,b) for(int i=(a);i>=(b);i--)
#define fs(e,i,u) for(int i=e.head[u];i;i=e.nxt[i])
#define pii pair<int, int>
#define pdd pair<db,db>
#define pb push_back
#define fir first
#define sec second
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
using namespace std;
const int maxn=1e7+7;
const ll inf=1e18+7;
ll n,m;
string s;
struct trie{
	int son[4];
}tr[maxn];int tot;
ll f[5][5][66],g[5][5],h[5][5];
void dfs(int x,int z,int y,int lth){//以x开头，放到x后的z，接下来放y，当前长度为lth 
	if(lth>=f[x][y][0])return;
	if(!tr[z].son[y]){
		f[x][y][0]=lth;
		return; 
	}
	fp(i,0,4){
		if(tr[z].son[i]){
			dfs(x,tr[z].son[i],y,lth+1);
		}
	}
}
int main(){
	cin>>n;
	cin>>s;
	m=s.size();
	ll lgn=log2(n),md=log2(sqrt(m))+1;
	fp(i,0,m){
		int now=0;
		fp(j,i,min(m,i+md)){
			int x=s[j]-'A';
			if(!tr[now].son[x])tr[now].son[x]=++tot;
			now=tr[now].son[x];
		}
	}
	fo(l,0,lgn){
		fp(i,0,4){
			fp(j,0,4){
				f[i][j][l]=inf;
			}
		}
	}
	fp(i,0,4){
		fp(j,0,4){
			if(tr[0].son[i]&&tr[0].son[j]){
				dfs(i,tr[0].son[i],j,1);
			}
		}
	}
	fo(l,1,lgn){
		fp(i,0,4){
			fp(j,0,4){
				fp(k,0,4){
					if(tr[0].son[i]&&tr[0].son[j]&&tr[0].son[k]){
						f[i][j][l]=min(f[i][j][l],f[i][k][l-1]+f[k][j][l-1]);
					}
				}
			}
		}
	}
	ll ans=1;
	de(l,lgn,0){
		ll minx=inf;
		fp(i,0,4){
			fp(j,0,4){
				h[i][j]=inf;
				if(tr[0].son[i]&&tr[0].son[j]){
					fp(k,0,4){
						if(tr[0].son[k]){
							h[i][j]=min(h[i][j],g[i][k]+f[k][j][l]);
						}
					}
					minx=min(minx,h[i][j]);
				}
			}
		}
		if(minx<n){
			ans+=1ll<<l;
			fp(i,0,4){
				fp(j,0,4){
					g[i][j]=h[i][j];
				}
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

完结 * ★,°*:.☆(￣▽￣)/$:*.°★ * 撒花 ♥。

---

## 作者：上天台 (赞：5)

orz原题解，看了很久才看懂。。。其实原题解的步骤很清晰，只是对于我这种弱菜而言还是有些地方要想很久才能想明白为什么。。。于是写了个（似乎）比较详细的题解。

考虑Appleman所采取的最优策略是什么样的。

假设当前已经填了i-1个字符，找到t中最长的满足s[i,i+len-1]=t[pos,pos+len-1]的子串填进去，其中pos是子串的左端点，len是子串的长度。

这是因为，如果一直填短串，相当于到了最后还要比填长串的多填几个才能填到n。
如果先填短串，然后在某一步填长串，最多也只能和之前的变成一样的长度，不可能比一直填长串的长。（可以画图理解一下）

然后就可以来做题了。

题目要求最小值最大，发现当可以用较小步数填时显然比它大的步数也都可以，满足二分性质，于是可以**二分答案**。

设dp[x][i][j]表示填x次，第x次填进去的子串开头的字母是i，第x+1次填进去的子串开头的字母是j，所能填出的最小长度。（j不被计算在长度中）

当dp[x][i][j]<n时，即采用这种t，即使Appleman用了最优填法也只能在还没到n的时候就用完了x次，剩下的长度需要的步数为正，即答案>x；反之，答案小于等于x。

**初始**：dp[1][i][j]相当于找到一个长度为L的子串，使得它在t中出现的长度是L-1，那么最小的L-1就是dp[1][i][j]。

然而这并不好找，于是我们思考一下，发现显然地，dp[1][i][j]其实就是**最小的以i开头，j结尾且不是t的子串的最短字符串**的长度。

于是我们可以从小到大枚举长度L，找出t中有多少种**（注意不是“个”）**不同的以i开头，j结尾且长度为L的子串（数量记为calc[i][j][L]），
假设字符集大小是C，如果calc[i][j][L]=C^(L-2)，就继续往下枚举，不然就让dp[1][i][j]=L-1并break。因为要求子串本质不同，那就用**字典树**统计。

然而这样还是不行，因为L<=|t|<=1e5，这样会T飞。

于是再仔细思考一下，显然我们只有当calc[i][j][L]>=pw(C,L-2)时才不合法，而calc[i][j][L]恒<=|t|，即|t|>=calc[i][j][L]>=pw(C,L-2)，即L<=logC_|t|+2时才不合法。

换而言之，**L最大不超过logC_|t|+3**。
这样一来，直接按照之前说的方法做就可以了。

**转移**：dp[x+1][i][j]=min(dp[x][i][k]+dp[1][k][j]) (0<=k<=C-1)

由于1<=x<=n而n<=1e18，可以**矩阵乘法+快速幂**。

问题解决辣，复杂度是O(|t|*logC_|t|+((C^3)*(log^2 n)))的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(register int x=y; x<=z; x++)
#define downrep(x,y,z) for(register int x=y; x>=z; x--)
#define LL long long
#define repedge(x,y) for(register int x=hed[y]; ~x; x=edge[x].nex)
#define ms(x,y,z) memset(x,y,sizeof(z))
inline int read(){
    int x=0; int w=0; char ch=0;
    while(ch<'0' || ch>'9') w|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w? (-x):x;
}
const int N=100005;
const int C=4;
const int L=15;
LL n;
int m,calc[C][C][L],DEP,tr[N*L][C],nw[N*L],cnt;
char s[N];
struct mat{ LL num[C][C]; }B;
LL PW(LL a,LL b){
    LL res=1;
    while(b){ if (b&1) res=res*a; a=a*a; b>>=1; }
    return res;
}
void insert(int x){
    int k=0; int u=s[x]-'A';
    rep(i,x,min(m-1,x+DEP-1)){
       int p=s[i]-'A';
       tr[k][p]=tr[k][p]? tr[k][p]:(tr[k][p]=++cnt);
       k=tr[k][p];
       if (!nw[k]){ nw[k]=1; ++calc[u][p][i-x+1]; }
    }
}
mat operator * (mat a,mat b){
    mat c; rep(i,0,C-1) rep(j,0,C-1) c.num[i][j]=n+1ll;
    rep(k,0,C-1) rep(i,0,C-1) rep(j,0,C-1)
    c.num[i][j]=min(c.num[i][j],a.num[i][k]+b.num[k][j]);
    return c;
}
mat pw(mat a,LL b){
    mat res=a; b-=1ll;
    while(b){ if (b&1) res=res*a; a=a*a; b>>=1; }
    return res;
}
int check(LL x){
    mat res=pw(B,x); int pd=0;
    rep(i,0,C-1) rep(j,0,C-1)
    pd|=(res.num[i][j]<n);
    return pd;
}
LL solve(){
    LL l=1; LL r=n;
    while(l<r){
       LL mid=((l+r)/2ll);
       if (check(mid)) l=mid+1;
       else r=mid;
    }
    return l;
}
int main(){
    scanf("%lld",&n); scanf("%s",&s);
    m=strlen(s); DEP=min(11,m+1);
    rep(i,0,m-1) insert(i);
    rep(i,0,C-1) rep(j,0,C-1) downrep(k,DEP,2)
    if (calc[i][j][k]!=PW(C,k-2)) B.num[i][j]=k-1;
    printf("%lld\n",solve());
    return 0;
}
```

---

## 作者：FZzzz (赞：4)

网上的题解一个都看不懂，可能是我过于傻逼。

首先有一个显然的结论：一个串的子串的操作次数不大于这个串自己。考虑如果已知 $s$ 如何求最小操作次数。建出 $t$ 的 SAM，把 $s$ 丢到上面贪心匹配，不能走了则回到起点然后答案加一。由上面的结论易证这样做的正确性。

上面那个结论的推论是，若长度为 $n$ 的所有串都能 $k$ 步以内构造，则长度不大于 $n$ 的所有串都能 $k$ 步以内构造。那么我们考虑二分转化为判定问题，求出最大的 $l$ 使得长度不大于 $l$ 的串都可以 $k$ 步以内构造。

考虑矩阵乘法，但是在矩阵乘法之前先要设计一个有理有据的 dp。令 $f_{i,c}$ 表示 $i$ 步不能构造出的以 $c$ 开头的最短的串长度为 $f_{i,c}+1$，那么我们考虑从 $f_{i-1}$ 转移到 $f_i$。考虑一个 $c$ 开头的串在 SAM 上走，走到某个地方走不动了，假设下一个字符是 $d$，那么后面接任意一个 $d$ 开头的可以以 $i-1$ 步构造出的字符串，则整个串都可以 $i$ 步构造出。

那么设 $g_{c,d}$ 为最短的以 $c$ 开头的子串，并且在后面加一个 $d$ 它就不是子串，这可以在 SAM 上 dp 出来。根据上面那个过程我们可以发现：$f_{i,c}=\min\limits_{d\in\Sigma}g_{c,d}+f_{i-1,d}$。如果还需要更加严谨的证明，那么考虑两步：
- 证明不大于这个值的 $c$ 开头的串必然可以 $i$ 步构造。这个串在 SAM 上走不下去的时候若下一个字符是 $d$，则已匹配长度必然不小于 $g_{c,d}$，那么后面的串的长度必然不大于 $f_{i-1,d}$，故后面可以 $i-1$ 步构造，整个串可以 $i$ 步构造。
- 构造一个长度为这个值加一的 $c$ 开头的串无法 $i$ 步构造。假设这个最小值在 $d$ 处取到，只需要构造一个串，前面 $g_{c,d}$ 个字符是满足 $g_{c,d}$ 定义的一个串，后面接一个 $d$ 开头的长度为 $f_{i-1,d}+1$ 的无法被 $i-1$ 步构造的一个串，那么这个串就无法 $i$ 步构造。

这个 dp 有另一种理解方式：两个子串拼在一起如果还是子串，那么必定不优。从这个意义出发的推导与上面这个是本质相同的，这里不再赘述。

现在的 dp 已经是 $\{\min,+\}$ 的矩乘形式，可以直接矩阵快速幂优化，外层套一个二分即可。你甚至可以把二分和快速幂合成一个倍增。我的实现时间复杂度是 $O(|t||\Sigma|^2+|\Sigma|^3\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxm=1e5+5;
ll n;
int m;
char t[maxm];
int sz=1,last=0,len[maxm*2],link[maxm*2],nxt[maxm*2][4];
void extend(int c){
	int cur=sz++;
	len[cur]=len[last]+1;
	int p=last;
	while(p>=0&&!nxt[p][c]){
		nxt[p][c]=cur;
		p=link[p];
	}
	if(p>=0){
		int q=nxt[p][c];
		if(len[q]==len[p]+1) link[cur]=q;
		else{
			int clone=sz++;
			link[clone]=link[q];
			memcpy(nxt[clone],nxt[q],sizeof(nxt[0]));
			len[clone]=len[p]+1;
			while(p>=0&&nxt[p][c]==q){
				nxt[p][c]=clone;
				p=link[p];
			}
			link[cur]=link[q]=clone;
		}
	}
	last=cur;
}
int f[4][maxm*2];
void dfs(int u){
	if(f[0][u]>=0) return;
	for(int i=0;i<4;i++) if(nxt[u][i]) dfs(nxt[u][i]);
	for(int i=0;i<4;i++){
		f[i][u]=nxt[u][i]?2e9:0;
		for(int j=0;j<4;j++) if(nxt[u][j])
			f[i][u]=min(f[i][u],f[i][nxt[u][j]]+1);
	}
}
struct matrix{
	ll a[4][4];
	matrix operator *(matrix B){
		matrix C;
		for(int i=0;i<4;i++) for(int j=0;j<4;j++){
			C.a[i][j]=n;
			for(int k=0;k<4;k++)
				C.a[i][j]=min(C.a[i][j],a[i][k]+B.a[k][j]);
		}
		return C;
	}
};
matrix ksm(matrix A,ll b){
	matrix ans;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++) ans.a[i][j]=i==j?0:n;
	while(b){
		if(b%2==1) ans=ans*A;
		A=A*A;
		b/=2;
	}
	return ans;
}
matrix A[60];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	scanf("%s",t+1);
	m=strlen(t+1);
	link[0]=-1;
	for(int i=1;i<=m;i++) extend(t[i]-'A');
	memset(f,-1,sizeof(f));
	dfs(0);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++) A[0].a[i][j]=f[i][nxt[0][j]]+1;
	for(int i=1;i<60;i++) A[i]=A[i-1]*A[i-1];
	ll ans=0;
	matrix B;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++) B.a[i][j]=i==j?0:n;
	for(int i=59;i>=0;i--){
		matrix C=A[i]*B;
		ll res=n+1;
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++) res=min(res,C.a[j][k]);
		if(res<n){
			ans+=1ll<<i;
			B=C;
		}
	}
	printf("%lld\n",ans+1);
	#ifdef LOCAL
	fprintf(stderr,"%d\n",(int)clock());
	#endif
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

[不知道会不会更好的阅读体验](https://www.cnblogs.com/tx-lcy/p/18228912#cf461e)

## 思路

不清楚字符集为啥要开这么小，开成 $100$ 同样能做。

考虑如何计算一个字符串被拼成的最小操作次数，从左往右扫一遍，如果上一个字符所在的连续段加上当前字符仍然是 $t$ 的一个子串，那就直接加入，否则新开一个连续段，不难证明这是正确的。

那么把 SAM 建出来之后我们可以据此设计一个 $\Theta(n|t|)$ 的 DP，具体地说就是设 $dp_{i,j}$ 表示前 $i$ 个字符，当前最后的连续段对应了 SAM 上的节点 $j$ 的最大操作次数。

这显然是过不去的，注意到对于固定的 $t$，$n=x+1$ 时的答案一定大于等于 $n=x$ 时的答案。

同样的，当答案为 $x$ 时对应的最小 $n$ 也一定小于等于答案为 $x+1$ 时对应的最小 $n$。

因此我们可以二分答案，现在问题变成计算答案为 $x$ 时的最小长度。

若 SAM 上节点 $x$ 没有连向字符 $c$ 的边，那么我们令 $x$ 连向字符 $c$ 的边到达的点为根节点连向字符 $c$ 的边到达的点，我们尝试把这个问题写得更清楚一点：

> 给你一张有向图，满足上面有 $4$ 个特殊点。
> 你有两个变量，$cnt1$ 和 $cnt2$。
> 你从根开始走，每经过一条边则 $cnt1$ 加一，每到达一个特殊点则 $cnt2$ 加一，当 $cnt2$ 为 $x$ 时过程终止。
> 你可以任意安排你走的路径，需要求出终止时 $cnt1$ 的最小值。

设 $cnt2$ 在点 $a_1,a_2,\dots,a_n$ 上加一，不难发现 $(a_i,a_{i+1})$ 的种类只有 $16$ 种。

因此暴力求出每种 $(a_i,a_{i+1})$ 经过的最少边数，然后矩阵快速幂转移即可。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define rep(i,j,k) for (int i=j;i<=k;++i)
#define per(i,j,k) for (int i=j;i>=k;--i)
int const N=1e6+10;
int n,m,ch[N][4],dis[N],cnt=1,la=1,len[N],fa[N];string s;
struct matrix{
    int c[4][4];
    inline void clear(){memset(c,0x3f,sizeof(c));}
}zhuan,cs;
inline matrix operator * (matrix a,matrix b){
    matrix c;c.clear();
    rep(i,0,3) rep(j,0,3) rep(k,0,3)
        c.c[i][j]=min(c.c[i][j],a.c[i][k]+b.c[k][j]);
    return c;
}
inline matrix qpow(matrix a,int b){
    matrix res=a;--b;
    while (b){
        if (b&1) res=res*a;
        a=a*a,b>>=1;
    }
    return res;
}
inline void insert(int x){
    int p=++cnt,q=la;len[p]=len[q]+1,la=p;
    for (;!ch[q][x] && q;q=fa[q]) ch[q][x]=p;
    if (!q) fa[p]=1;
    else{
        int v=ch[q][x];
        if (len[v]==len[q]+1) fa[p]=v;
        else{
            int nv=++cnt;
            fa[nv]=fa[v],len[nv]=len[q]+1;
            memcpy(ch[nv],ch[v],sizeof(ch[v]));
            fa[p]=fa[v]=nv;
            for (;ch[q][x]==v && q;q=fa[q]) ch[q][x]=nv;
        }
    }
}
inline bool check(int nx){
    cs.clear();
    rep(i,0,3) cs.c[1][i]=1;
    cs=cs*qpow(zhuan,nx-1);
    int mi=9e18;
    rep(i,0,3) mi=min(mi,cs.c[1][i]);
    return mi<=n;
}
void solve(){
    cin>>n>>s,m=s.size(),s=" "+s;
    if (n==1) return cout<<"1\n",void();
    rep(i,1,m) insert(s[i]-'A');
    rep(i,1,cnt) rep(j,0,3) if (!ch[i][j]) ch[i][j]=ch[1][j];
    zhuan.clear();
    rep(i,0,3){
        rep(j,1,cnt) dis[j]=-1;int Root=ch[1][i],id=i;
        queue<int>q;q.push(ch[1][i]),dis[ch[1][i]]=0;
        while (!q.empty()){
            int x=q.front();q.pop();
            rep(i,0,3)
                if (dis[ch[x][i]]==-1) dis[ch[x][i]]=dis[x]+1,q.push(ch[x][i]);
                else if (ch[x][i]==Root) zhuan.c[id][id]=min(zhuan.c[id][id],dis[x]+1);
        }
        rep(j,0,3) if (i^j) zhuan.c[i][j]=dis[ch[1][j]];
    }
    int l=1,r=n,ans=0;
    while (l<=r)
        if (check(mid)) l=(ans=mid)+1;
        else r=mid-1;
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    // cin>>t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：Lu_xZ (赞：1)

补充了部分细节问题。

如果 $s$ 确定，如何求出其最小操作数？

$g_i$ 表示前缀 $i$ 最少被分成多少段，$g_i$ 能从 $g_j + 1$ 转移当且仅当 $(j, i]$ 是 $t$ 的子串。

注意到 $g_{i} \ge g_{i - 1}$，因为任意 $i$ 的方案都能砍掉 $s_i$ 后变成 $i - 1$ 的方案。

因此 $i$ 的转移点为最小的 $j$ 满足 $(j, i]$ 是 $t$ 的子串。

有如下贪心：对于每一段，能延伸就延伸（在 $t$ 的 sam 上跑，有转移边就走，否则回到根）。

在段数相同的情况下要最小化总长度，这样才能在总长度确定时最大化段数。

设 $f(k, i, j)$ 表示已经拼了 $k$ 段，以字符 $i$ 开头且不能再往后延伸一个字符 $j$ 的最小总长度。

倍增优化：$f(2^k, i, j) \gets f(2^{k - 1}, i, x) + f(2^{k - 1}, x, j)$。

问题转化为求 $f(1, i, j)$。

其代表的子串在将来一定是接一个 $j$ 开头的段，并产生 $2$ 的贡献。

把以 $i$ 开头的字符串 $s$ 分成三类：

1. 是 $t$ 的子串且后面不能加 $j$，在后面接一个 $j$ 开头的段，恰好产生两个段。
2. 是 $t$ 的子串且后面能加 $j$，不一定能产生两个段。
3. 不是 $t$ 的子串，已经产生至少两个段了，哪怕新接的段不产生贡献，贡献仍然至少为二。

因此在相同长度下，一三比二更优。

固定长度为 $k$，第二类有 $x = O(n)$ 种，一三加起来有 $4^{k - 1} - x$。

存在一三串当且仅当 $4^{k - 1} - x > 0$，取 $k = 11$ 足矣。

对所有后缀建出树高为 $11$ 的字典树即可求出所有有用的 $f(1, i, j)$（可能存在大于 $11$，但是没用）。

统计答案：从高到低枚举 $2^k$，$h_{i, j}$ 表示 $i$ 开头，后面接不了 $j$，在当前答案下的最小长度。

由于有“不能接”这一限制，贪心的让 $h_{i, j} < n$，并在最后补一个 $j$（体现在答案上就是加 $1$）。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr int N = 1e5 + 5;

int m, t[N * 15][4], idx;
char s[N];

ll n, f[61][4][4], h[4][4], g[4][4];

void dfs(int u, int v, int d, ll& x) {
	if(!u) return;
	if(!t[u][v]) {
		x = min(x, (ll)d);
		return;
	}
	for(int i = 0; i < 4; ++ i) {
		dfs(t[u][i], v, d + 1, x);
	}
}
main() {
	scanf("%lld%s", &n, s);
	m = strlen(s);
	for(int i = 0; i < m; ++ i) s[i] -= 'A';
	for(int i = 0; i < m; ++ i) {
		for(int j = i, p = 0; j < m; ++ j) {
			if(j - i >= 11) break;
			if(!t[p][s[j]]) t[p][s[j]] = ++ idx;
			p = t[p][s[j]];
		}
	}
	memset(f, 0x3f, sizeof f);
	for(int i = 0; i < 4; ++ i) {
		for(int j = 0; j < 4; ++ j) {
			dfs(t[0][i], j, 1, f[0][i][j]);
		}
	}
	for(int k = 1; k <= 60; ++ k) {
		for(int i = 0; i < 4; ++ i) {
			for(int j = 0; j < 4; ++ j) {
				for(int x = 0; x < 4; ++ x) {
					f[k][i][j] = min(f[k][i][j], f[k - 1][i][x] + f[k - 1][x][j]);
				}
			}
		}
	}
	ll ans = 0;
	for(int k = 60; k >= 0; -- k) {
		ll mi = 1e18;
		for(int i = 0; i < 4; ++ i) {
			for(int j = 0; j < 4; ++ j) {
				h[i][j] = 1e18;
				for(int x = 0; x < 4; ++ x) {
					h[i][j] = min(h[i][j], g[i][x] + f[k][x][j]);
				}
				mi = min(mi, h[i][j]);
			}
		}
		if(mi < n) {
			ans |= 1ll << k;
			swap(g, h);
		}
	}
	printf("%lld", ans + 1);
}
```

---

## 作者：居然有个高手 (赞：1)

考虑 $s$ 已知时我们如何操作最优，答案十分显然：假设当前已经匹配了 $i-1$ 个字符，则我们找出最大的 $j$ 满足 $s_{i,j}$ 是 $t$ 的子串操作即可。这种操作方法对后面的影响最小，所以一定最优。

由此，我们可以将 $s$ 划分成若干段，每段都是 $t$ 的一个子串，且第 $i+1$ 段的开头不能被拼接在第 $i$ 段后。此刻，每一段的关键信息仅有开头字符与结尾能够拼接上哪些字符集合。我们可以记录一个状态 $f_{i,j,S}$ 表示目前已有 $i$ 段，开头字符为 $j$，下一段的开头字符可以是集合 $S$ 里面字符时，$s$ 的最小长度。考虑转移，首先我们需要求出满足 $j,S$ 两个限制的最短的 $t$ 的子串，发现其长度不超过 $\log_4 |s|$，可以暴力枚举 $j,S,len$ 算出。

随后，根据此状态 DP 可以做到 $O(2^{12}n)$。

发现 $n$ 非常大，且转移为线性转移，可以直接矩阵优化转移。判定答案过程中可以用二分转倍增的优化，最终复杂度即可做到 $O(2^{18} \log n)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
inline long long read(){
    long long x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
long long m;
int n;
char s[N];
unsigned long long ksm[N],base=13131,hsh[N];
struct matrix{
    __int128 f[75][75];
    inline matrix operator*(matrix b){
        matrix c;
        for(int i = 0;i<64;i++){
            for(int j = 0;j<64;j++){
                c.f[i][j]=1e30;
                for(int k = 0;k<64;k++)c.f[i][j]=min(c.f[i][j],f[i][k]+b.f[k][j]);
            }
        }
        return c;
    }
}ans,f[61];
vector<int>v[5];
inline int id(int x,int y){
    return x*16+y;
}
map<unsigned long long,int>mp;
int main(){
    m=read();scanf("%s",s+1),n=strlen(s+1);
    ksm[0]=1;
    for(int i = 1;i<=n;i++){
        ksm[i]=ksm[i-1]*base;hsh[i]=hsh[i-1]*base+s[i]-'A';
        v[s[i]-'A'].push_back(i);
    }
    for(int i = 0;i<16;i++){
        for(int j = 0;j<4;j++){
            int len = 1,now=1;
            while(1){
                mp.clear();
                for(int k = 0;k<4;k++){
                    if(!(i&(1<<k)))continue;
                    for(auto pos : v[k])if(pos>len && s[pos-len]==j+'A')mp[hsh[pos-1] - hsh[pos-len-1]*ksm[len]]++;
                }
                if(mp.size()<now)break;
                len++,now*=4;
            }
            for(int k = 0;k<4;k++){
                if(i&(1<<k)){
                    for(int o = 0;o<16;o++)f[0].f[id(j,i)][id(k,o)]=len;
                }
                else{
                    for(int o = 0;o<16;o++)f[0].f[id(j,i)][id(k,o)]=1e18;
                }
            }
        }
    }
    for(int i = 1;i<=60;i++){
        f[i]=f[i-1]*f[i-1];
    }
    long long res=1;
    for(int i = 60;i>=0;i--){
        auto now = ans*f[i];
        __int128 minn=1e30;
        for(int j = 0;j<64;j++)minn=min(minn,now.f[1][j]);
        if(minn>=m)goto fail;
        res+=(1ll<<i);ans=now;
        fail:;
    }
    cout<<res;
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

幽默 `*3000`，实际难度应该是 `*2300` 至 `*2400`。

考虑给你一个串，怎么算他的代价。

我们发现，“子串”这个性质有很好的单调性，因此每次删掉最长的后缀使得他是另一个串的子串即可。

考虑这个后缀形如 $\texttt {XXXXXXA}$，那么只有第一个 $\texttt X$ 那个字符是关键的，它又是下一个后缀的最后一个字母。所以我们只关心如果这个后缀最后一个字母是 $c_1$，下一个后缀的最后一个字母是 $c_2$，这样的后缀最长是多少。

因此按照最后一个字母进行转移可以写成矩阵的形式。二分答案 + 矩阵快速幂即可。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,INF=1e18+10,MOD=998244353;
int n,m,h[MAXN],pw[MAXN];
string T;
int calc(int l,int r) {return ((h[r]-h[l-1]*pw[r-l+1])%MOD+MOD)%MOD;}
struct Matrix {int v[4][4];}init;
Matrix operator *(Matrix A,Matrix B) {
	Matrix res;
	memset(res.v,0x3f,sizeof(res.v));
	ffor(i,0,3) ffor(j,0,3) ffor(k,0,3) res.v[i][k]=min(res.v[i][k],A.v[i][j]+B.v[j][k]);
	return res;	
}
Matrix operator ^(Matrix A,int p) {
	Matrix res;
	memset(res.v,0x3f,sizeof(res.v));
	ffor(i,0,3) res.v[i][i]=0;
	while(p) {
		if(p&1) res=res*A;
		A=A*A,p>>=1;
	}
	return res;
}
int check(int d) {
	Matrix INIT=init^(d-1);
	int mn=INF;
	ffor(i,0,3) ffor(j,0,3) mn=min(mn,INIT.v[i][j]);
	if(mn+1<=n) return 1;
	return 0;	
}
int bfind(int l,int r) {
	int ans=0,mid;
	while(l<=r) {
		mid=l+r>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
signed main() {
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>T,m=T.size(),T="&"+T;
	pw[0]=1; ffor(i,1,m) pw[i]=pw[i-1]*4%MOD;
	ffor(i,1,m) h[i]=(h[i-1]*4+T[i]-'A')%MOD;
	ffor(i,0,3) ffor(j,0,3) {
		ffor(len,1,12) {
			set<int> st;
			ffor(k,len,m) if(T[k]-'A'==i&&T[k-len]-'A'==j) st.insert(calc(k-len,k));
			if(st.size()!=(1<<(len*2-2))) {init.v[i][j]=len;break ;}
		}
	}
	cout<<bfind(1,n);
	return 0;
}
```

有人模拟赛没删调试获得了 $0$ 分，警钟长鸣。

---

## 作者：Jsxts_ (赞：0)

考虑知道了 $s$ 怎么求它的最小操作次数：设 $dp_i$ 表示前 $i$ 个的最小操作次数，然后找到以 $i$ 结尾在 $t$ 中出现过的最长串，设其长度为 $l$，从 $dp_{i-l-1}+1$ 转移过来。由于 dp 值随 $i$ 不降，所以只需找到最长串。

现在考虑使得每次这个 dp 的转移时的 $l$ 都尽量短（这样会使上面的 dp 值尽量大）。假设当前结尾处字母为 $c$，那么我们需要找到一个以 $c$ 结尾并在 $t$ 中没有出现的最短的串 $s$，贪心地填在这里，那么划分时考虑从后往前划分，肯定是将 $s$ 除去第一个字母的剩下部分划成一段，剩下再同样的继续贪心（举例，若以 $\texttt{A}$ 结尾时 $s=\texttt{ADA}$，则肯定是将 $\texttt{DA}$ 划做一段，$\texttt{A}$ 与剩下的串再继续划分）。

所以，这个串只和长度、开头、结尾有关。于是我们可以预处理出 $val_{i,j}$ 表示开头为 $i$，结尾为 $j$ 且没在 $t$ 中出现的最短串长度。之后考虑一个 dp：设 $f_{i,j}$ 表示当 $s$ 长度为 $i$，结尾为 $j$ 时的最小操作次数的最大值。转移就枚举开头的字母 $k$，从 $f_{i-val_{k,j}+1,k}+1$ 转移过来。

但是有可能最后一段不是由一个最短串组成，那么考虑在开头转移时可以只填最短串的一段前缀（即 $i<val_{k,j}$ 时将 $f_{i,j}$ 设为 $1$），这样就钦定最后答案一定是 $\max\{f_{n,0\sim 3}\}$。

然后发现这个 $val_{i,j}$ 长度是 $\log_4(|t|)$ 级别的，所以可以存下 $i$ 前 $\log_4(|t|)$ 个下标的所有状态共 $|\sum|\log_4(|t|)$ 个状态进行矩阵加速即可。

而对于前面的 $val_{i,j}$ 如何预处理，同样因为长度很短所以直接枚举长度然后判断是否每种这个长度的串都在 $t$ 中出现过。

总时间复杂度 $O((|\sum|\log_4(|t|))^3+|t|\log_4(|t|))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e5;
inline ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int f[N + 10][5],val[4][4],l;
ll n;
string s;
struct Matrix {
	ll w[45][45];
	ll* operator[] (const int x) {
		return w[x];
	}
	friend Matrix operator * (Matrix x,Matrix y) {
		Matrix z;
		memset(z.w,-0x3f,sizeof z.w);
		for (int i = 0;i < 40;i ++ )
			for (int k = 0;k < 40;k ++ )
				for (int j = 0;j < 40;j ++ )
					z[i][j] = max(z[i][j],x[i][k] + y[k][j]);
		return z;
	}
}A;
int id(int i,int j) {
	return (i - 1) * 4 + j;
}
Matrix qpow(Matrix a,ll b) {
	Matrix res;
	memset(res.w,0,sizeof res.w);
	while (b) {
		if (b & 1) res = res * a;
		b >>= 1, a = a * a;
	}
	return res;
}
map<string,int> mp;
int main() {
	n = read();
	cin >> s;
	l = s.size();s = '#' + s;
	for (int i = 2;i <= 10;i ++ ) {
		for (char a = 'A';a <= 'D';a ++ )
			for (char b = 'A';b <= 'D';b ++ ) {
				if (val[a - 'A'][b - 'A']) continue;
				int ct = 0;
				mp.clear();
				for (int j = 1;j <= l - i + 1;j ++ )
					if (s[j] == a && s[j + i - 1] == b) {
						string ss = s.substr(j,i);
						if (!mp[ss]) mp[ss] = 1, ct ++;
					}
				if (ct < pow(4,i - 2)) val[a - 'A'][b - 'A'] = i;
			}
	}
	memset(A.w,-0x3f,sizeof A.w);
	for (int i = 0;i < 36;i ++ ) A[i + 4][i] = 0;
	for (int j = 0;j < 4;j ++ )
		for (int k = 0;k < 4;k ++ ) {
			A[id(10 - val[k][j] + 2,k)][id(10,j)] = 1;
		}
	Matrix ans = qpow(A,n);
	ll Ans = max({ans[0][id(10,0)],ans[0][id(10,1)],ans[0][id(10,2)],ans[0][id(10,3)]});
	cout << Ans;
	return 0;
}
```

---

## 作者：SoyTony (赞：0)

在 $s$ 中添加一个字符串使得操作次数增加意味着添加的部分没有出现在 $t$ 中，使操作次数尽量多意味着这样的未出现子串是极短的，也就是删去最后一个字符后是出现 $t$ 中的。

构造的过程实际是在原串 $s$ 的基础上增加一个子串得到 $s'$，其中 $s$ 的末尾字符 $c_1$，$s'$ 的末尾字符 $c_2$，增加的部分是以 $c_1$ 开头 $c_2$ 结尾且最短的未在 $t$ 中出现的字符串（不包含 $c_1$），因此增加的部分按开头结尾分类取最短有关，也就是 $4\times 4=16$ 种。容易发现这些字符串长度是 $O(\log_4 |t|)$ 的。

这样得到一个 $O(|t|\log_4 |t|\log_2 |t|)$ 预处理（使用哈希以及 `map` 判断当前长度的所有字符串是否都已经出现），DP 复杂度 $O(n\log_4 |t|)$ 的做法。注意最后形成的 $s$ 的末尾未必是一个 $t$ 不包含子串的末尾，也可能是补齐了一个后缀，例如 $\texttt{AADACABBABDBCCACBCDDADBDC}$ 中所有长度为 $2$ 的字符串都已经出现，若构造出长度小于 $n=4$ 的 $\texttt{ABC}$，可以添加为 $\texttt{ABCD}$，而 $\texttt{CD}$ 在 $t$ 中是出现过的。

考虑优化，由于长度很小，直接拆成若干长度为 $1$ 的边，变成朴素的游走 $n$ 步问题，贡献只在最后一条边产生，矩阵快速幂即可解决。统计答案也要考虑上面的情况。

时间复杂度 $O(|t|\log_4 |t|\log_2 |t|+(|\Sigma|^2\log_4 |t|)^3\log_2 n)$。

提交记录：[Submission - CodeForces](https://codeforces.com/problemset/submission/461/226127991)

---

## 作者：JoaoFelix (赞：0)

很久没有写CF题的题解了...看在题解数量不多的情况下来写一下吧

首先有一种直观的思路就是我们考虑求出最短的没有在原串中出现的串然后将它反复重复构造一组解！

很显然这有诸多的边界条件我们无法保证其正确性，因为最短的实际上有很多种情况，但是针对这一个串的结尾（想想看，其实也就是下一个串的开头）也就有很多选择，然后有些选择会更优，可是有些选择不优，然后我们求出来的不一定能最优！
而且实际上我们最短的串是可以有两个及以上配对来完成构造出最优解的，因此我们可以记录第一个出现的字母和最后出现的字母来完成DP即可！

首先我们考虑这样最短的串不在字符串中出现的长度是不会超过10的，可以根据生日悖论，然后我们只需要把不超过10的字符串连续地建立在Trie上面，然后求出第一个字母和最后一个字母的最短的不在字符串出现的串的长度即可！

然后我们就可以DP了，但是由于规模达到1e18，因此我们考虑二分用时，然后求出在这样的用时情况下能构造出最短的字符串的长度是多少，然后check就行了，由于字符集很小，因此可以用矩乘维护DP（这个矩乘不应该完全叫做矩乘，是倍增Floyd，有两种写的姿势一种是直接类似矩乘维护，还可以用倍增维护，貌似多一维，可以看一下P1613跑路那一题）

由于建Trie的常数和矩乘的复杂度都很小，因此程序能飞快通过所有测试点！

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
	char c = getchar(); ll x = 0, f = 1;
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}

const int N = 100005;

ll n; char str[N]; int l; bool usd[N << 4];
int ch[N << 4][4], buc[4][4][15], tot;

struct matrix {
	ll a[4][4];
	void init(ll v) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) a[i][j] = v;
	}
} bse;
matrix operator * (matrix a, matrix b) {
	matrix c; c.init(n + 1);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++) c.a[i][j] = min(c.a[i][j], a.a[i][k] + b.a[k][j]);
	return c; 
}

int fpow(int x, int y) {
	int ret = 1; if (y < 1) return 1;
	for (; y; y >>= 1, x = x * x) if (y & 1) ret = ret * x;
	return ret;
}
bool check(ll mid) {
	if (!mid) return false; mid--;
	matrix res = bse, cp = bse;
	for (; mid; mid >>= 1, cp = cp * cp) if (mid & 1) res = res * cp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) if (res.a[i][j] < n) return true;
	return false;
}

int main() {
	n = read(); scanf("%s", str + 1); l = strlen(str + 1); 
	int lim = min(l, 10) + 1;
	for (int i = 1; i <= l; i++) {
		int now = 0, fir = str[i] - 'A';
		for (int j = i; j <= min(i + lim - 1, l); j++) {
			int c = str[j] - 'A';
			if (!ch[now][c]) ch[now][c] = ++tot;
			now = ch[now][c];
			if (!usd[now]) usd[now] = true, buc[fir][c][j - i + 1]++; 
		}
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = lim; k >= 2; k--) if (buc[i][j][k] != fpow(4, k - 2)) bse.a[i][j] = k - 1;
	ll l = 0, r = n + 1;
	while (l + 1 < r) {
		ll mid = (l + r) >> 1;
		if (check(mid)) l = mid; else r = mid;
	}
	printf("%lld\n", r); 
	return 0;
}

```


---

