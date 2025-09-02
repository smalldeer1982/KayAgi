# [JOI Open 2021] 杂交 / Crossing

## 题目背景

**警告：滥用本题评测将被封号。**

## 题目描述

你的资源库里有 $3$ 个长度为 $N$ 的只由 `J`，`O`，`I` 组成的序列 $S_A,S_B,S_C$，你可以进行 C 操作（全名为 Cross 操作，简写为 C 操作），每一次 C 操作你可以在资源库里选择两个字符串 $C_1,C_2$，C 操作后产生的字符串为 $C_3$，则对于任意 $i \in [1,N]$，设这三个字符串第 $i$ 个位置上的字符分别为 $c_1,c_2,c_3$，有：

|$c_1$|$c_2$|$c_3$|
|:-:|:-:|:-:|
|J|J|J|
|J|O|I|
|J|I|O|
|O|J|I|
|O|O|O|
|O|I|J|
|I|J|O|
|I|O|J|
|I|I|I|

上面这个表格的意思是 $c_1,c_2$ 为对应字符时，$c_3$ 也应该是对应的字符。

进行 C 操作后将会把产生的字符串放入资源库。

你被给定了一个长度为 $N$ 的只由 `J`，`O`，`I` 组成的字符串 $T_0$，和 $Q$ 个整数 $L_j,R_j$ 和 $Q$ 个字符 $C_j$，由这些形成 $Q$ 个长度为 $N$ 的字符串 $T_j$，规则为：

> $T_j$ 是由 $T_{j-1}$ 的第 $L_j$ 个字符到第 $R_j$ 个字符都替换成 $C_j$ 得到的。

求对于每一个字符串（包括 $T_0$），是否能由给定的资源库进行一次或多次 C 操作得来。如果该字符串与资源库的其中一个字符串一模一样，也可以称“进行 C 操作得来”，详细内容请看样例 1 的 $T_2$。

第 $j$ 个字符串进行 C 操作时放入资源库的字符串将会在对第 $j+1$ 个字符串判断时清空。

## 说明/提示

#### 样例 1 解释

- $T_0$ 可以由 `JJOI` 和 `OJOO` 经过 C 操作而来；
- $T_1$ 为 `OOOO`，无法从资源库经过 C 操作而来；
- $T_2$ 为 `OJOO`，资源库中有 `OJOO`，故可以；
- $T_3$ 为 `OIII`：
	1. 由 `JJOI` 和 `OJOO` 经过 C 操作产生 `IJOJ`；
    2. 由 `JOJO` 和 `IJOJ` 经过 C 操作产生 `OIII`。
    
#### 样例 2 解释

- $T_0$ 无法从资源库经过 C 操作而来；
- $T_1$ 为 `OOI`，无法从资源库经过 C 操作而来；
- $T_2$ 为 `JOI`，资源库中有 `JOI`，故可以。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（3 pts）：$S_A=S_B=S_C$，$N \le 100$；
- Subtask 2（23 pts）：$S_A=S_B=S_C$；
- Subtask 3（23 pts）：$N \le 100$；
- Subtask 4（51 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $1 \le N \le 2 \times 10^5$；
- $S_A,S_B,S_C$ 是只包含 `J`，`O`，`I` 的长度为 $N$ 的字符串；
- $1 \le Q \le 2 \times 10^5$；
- $T_0$ 是只包含 `J`，`O`，`I` 的长度为 $N$ 的字符串；
- $1 \le L_j \le R_j \le N$；
- $C_j \in  \{$`J`，`O`，`I`$\}$。 

#### 说明

翻译自 [JOI 2020 / 2021 Open Contest A Crossing](http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2021/crossing/2021-open-crossing-statement-en.pdf)。

## 样例 #1

### 输入

```
4
JOJO
JJOI
OJOO
3
IJOJ
1 4 O
2 2 J
2 4 I```

### 输出

```
Yes
No
Yes
Yes```

## 样例 #2

### 输入

```
3
JOI
JOI
JOI
2
OJI
1 2 O
1 1 J```

### 输出

```
No
No
Yes```

# 题解

## 作者：7KByte (赞：5)

有删减，原文见[**我的博客**](https://www.cnblogs.com/SharpnessV/p/15178088.html)。

很有意思的一道题。

不难发觉得关键还是在变化上。

我们用 $1,2,3$ 表示分别表示三个字母，那么如果 $c_1\neq c_2$，则 $c_3 = c_1 \oplus c_2$，直接异或就行。

但是如果 $c_1=c_2$ 根本表示不了，后面也没法做（罚坐了半个小时

考虑用 $0,1,2$ 分别表示三个字母，那么我们可以发现 $c_3\equiv-c_1-c_2\pmod{3}$。

所以杂交后得到的串 $S$ 一定可以表示为 $aS_A+bS_B+cS_C$，由于每一位都是模 $3$ 意义下的，所以杂交所得的串不会超过 $27$ 个。

我们直接写个程序爆算所有可能的 $(a,b,c)$，发现只有 $9$ 种可能。

那么我们只用预处理这 $9$ 个串的哈希值，然后用线段树维护 $T$ 的哈希值，这道题就做完了。

---

## 作者：EXODUS (赞：1)

# Part 1：前言
比较新颖的一个题。

# Part 2：正文

首先观察题目中操作的性质。设对于一对串 $(s,t)$，进行题目中所述操作为 $\text{cross}(s,t)$，那么对于两个串 $s,t$，有 $\text{cross}(\text{cross}(s,t),t)=s$，因此我们猜测能表示的串不会很多。但很不幸的是，$\text{cross}$ 不满足结合律，所以我们无法直接说明所得的串不多。

因此，我们考虑把 $\text{cross}$ 操作映射成一个熟悉的有结合律的操作。首先注意到 $\text{cross}$ 操作对位独立，所以我们考虑对每一个字符分别考虑。设将 $\texttt{J}$ 映射为 $x$，$\texttt{O}$ 映射为 $y$，$\texttt{I}$ 映射为 $z$，映射后的操作符为 $\circ$，那么题目中的要求可以被刻画为一下三个等式。
$$
\begin{cases}
x\circ x=y\circ z=z\circ y=x\\
y\circ y=x\circ z=z\circ x=x\\
z\circ z=x\circ y=y\circ x=x\\
\end{cases}
$$
首先注意到映射后的操作一定需要满足交换律。而另一个观察是出现了一个类似轮换式的等式关系，具有这种结构的二元运算在我们印象中只存在异或和模加，而异或是不满足 $x\circ x=x$ 的，故我们考虑模加。经过一些简单构造后，我们发现我们可以构造出如下映射。
$$
\begin{aligned}
&x=0,y=1,z=2\\
&x\circ y=(2x+2y)\bmod 3
\end{aligned}
$$
我们惊喜的发现，映射为如下操作后，我们可以说明经过 $\text{cross}$ 操作能生成的串不会很多了。

依然考虑每一位是独立的。那么对于一位 $i$，其一定可以表示为 $am_{A,i}+bm_{B,i}+cm_{C,i}$ 的形式，其中 $m_{c,i}$ 表示 $S_c$ 的第 $j$ 位按照上述规则映射后的结果。而运算是在模 $3$ 意义下进行的，故我们可以说明可以生成的串不会超过 $27$ 种，而实际上，串的种类数只有 $9$ 种，分别对应 $S_A,S_B,S_C,\text{cross}(A,B),\text{cross}(A,C),\text{cross}(B,C),\text{cross}(\text{cross}(A,B),C),\text{cross}((B,C),A),\text{cross}(\text{cross}(C,A),B)$。我们可以预处理出来以后把哈希值塞到一个集合里。

处理单次询问时直接处理出哈希值在集合里暴力查询，而修改相当于是修改串的哈希值，可以轻易的线段树维护。

时间复杂度 $O(Q(\log N+B))$，其中 $B=9$。



# Part 3：代码

~~出题人素质很差，卡了自然溢出哈希。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
typedef unsigned long long ull;
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}


const int N=2e5+7,base=13,mod=998244353;

struct Info{
	ull cur;
	Info(ull _cur=0):cur(_cur){}
	Info operator +(Info rhs){return Info((cur+rhs.cur)%mod);}
	Info operator *(Info rhs){return Info((cur*rhs.cur)%mod);}
	bool operator ==(Info rhs){return cur==rhs.cur;}
};

int n,Q;
char str[N];
vector<int>s[3];
vector<Info>bas,pwb,val[3];



vector<int> cross(vector<int> lhs,vector<int> rhs){
	vector<int>res(n+1);
	for(int i=1;i<=n;i++)res[i]=2*(lhs[i]+rhs[i])%3;
	return res;
}

Info calc(vector<int> cur){
	Info res=0;
	for(int i=1;i<=n;i++)res=res*base+cur[i];
	return res;
}

int key(char c){
	return (c!='J'?(c!='O'?2:1):0);
}

struct Sgt{
#define ls(k) ((k)<<1)
#define rs(k) (((k)<<1)|1)
	struct Tree{Info key;int len,tag;}t[N<<2];
	void pull(int k){
		t[k].key=t[ls(k)].key*pwb[t[rs(k)].len]+t[rs(k)].key;
	}
	void apply(int k,int v){
		t[k].key=val[v][t[k].len];
		t[k].tag=v;
	}
	void push(int k){
		if(t[k].tag!=-1)apply(ls(k),t[k].tag),apply(rs(k),t[k].tag),t[k].tag=-1;
	}
	void build(int l,int r,int k){
		t[k].len=r-l+1;t[k].tag=-1;
		if(l==r)return t[k].key=key(str[l]),void();
		int mid=(l+r)>>1;
		build(l,mid,ls(k));
		build(mid+1,r,rs(k));
		pull(k);
	}
	void modify(int l,int r,int k,int ql,int qr,int v){
		if(ql<=l&&r<=qr)return apply(k,v);
		int mid=(l+r)>>1;push(k);
		if(ql<=mid)modify(l,mid,ls(k),ql,qr,v);
		if(mid<qr)modify(mid+1,r,rs(k),ql,qr,v);
		pull(k);
	}
	Info query(){return t[1].key;}
#undef ls
#undef rs
}sgt;

bool solve(){
	Info res=sgt.query();
	// printf("%llu\n",res);
	if(find(bas.begin(),bas.end(),res)!=bas.end())return 1;
	return 0;
}

int main(){
	read(n);
	pwb.resize(n+1);
	pwb[0]=1;
	for(int i=1;i<=n;i++)pwb[i]=pwb[i-1]*base;
	for(int i=0;i<=2;i++){
		scanf("%s",str+1);
		s[i].resize(n+1);
		for(int j=1;j<=n;j++)s[i][j]=key(str[j]);
	}
	for(int i=0;i<=2;i++){
		val[i].resize(n+1);val[i][0]=0;
		for(int j=1;j<=n;j++)val[i][j]=val[i][j-1]*base+i;
	}
	bas.eb(calc(s[0]));
	bas.eb(calc(s[1]));
	bas.eb(calc(s[2]));
	bas.eb(calc(cross(s[0],s[1])));
	bas.eb(calc(cross(s[1],s[2])));
	bas.eb(calc(cross(s[0],s[2])));
	bas.eb(calc(cross(s[0],cross(s[1],s[2]))));
	bas.eb(calc(cross(s[1],cross(s[2],s[0]))));
	bas.eb(calc(cross(s[2],cross(s[0],s[1]))));
	
	// for(auto x:bas)printf("%llu\n",x);printf("\n");
	
	read(Q);
	scanf("%s",str+1);
	sgt.build(1,n,1);
	puts(solve()?"Yes":"No");
	for(int _=1,l,r;_<=Q;_++){
		char c;
		read(l,r),scanf("%c",&c);
		sgt.modify(1,n,1,l,r,key(c));
		puts(solve()?"Yes":"No");
	}
	return 0;
}

```

# Part 4：后文
最后稍微魔怔一下。

怎么高铁上网这么差/oh。怎么高铁上网这么差/oh。怎么高铁上网这么差/oh。怎么高铁上网这么差/oh。怎么高铁上网这么差/oh。怎么高铁上网这么差/oh。


---

## 作者：沉石鱼惊旋 (赞：0)

# 题目思路

题目这个变化看上去是判断两个字符是否相同，相同选他否则选剩下的一个。但有个很深刻的事情是把字符分别设为 $1,2,3$。那么 $a \operatorname{cross} b$ 运算结果就是 $c\equiv 2a+2b\pmod 3$。模拟赛时一点没想到还可以这样变换。

交换律不难看出。设 $A$ 是一个运算过程，这个事情也告诉我们 $(a \operatorname{cross} A) \operatorname{cross} a=a \operatorname{cross} (A \operatorname{cross} a)=A$。因此在一个最后的表达式中，$S_A,S_B,S_C$ 不可能出现超过一次参与运算。

那么总状态只有 $9$ 类：

1. $S_A$；
1. $S_B$；
1. $S_C$；
1. $S_A\operatorname{cross} S_B$；
1. $S_A\operatorname{cross} S_C$；
1. $S_B\operatorname{cross} S_C$；
1. $(S_A \operatorname{cross} S_B)\operatorname{cross} S_C$；
1. $(S_B \operatorname{cross} S_C)\operatorname{cross} S_A$；
1. $(S_C \operatorname{cross} S_A)\operatorname{cross} S_B$。

我们要做的就是判断给定字符串有没有在这里出现过。可以直接存下这九种字符串的哈希值。再加一棵维护哈希值的线段树，支持区间推平和查询全局哈希。线段树维护一下当前覆盖的颜色，预处理出颜色连续段的哈希值。全局查询就是根节点的哈希值。

代码实现写的是单模随机 base。另外我在 Baekjoon 交这题交了三发改了两次模数才过？？？

# 代码链接

[洛谷 record 198170123](https://www.luogu.com.cn/record/198170123)

代码有 modint 有点长，附一份 qoj 链接。

<https://qoj.ac/submission/856620>

---

## 作者：ty_mxzhn (赞：0)

这个运算见过好多遍了。设 $J,O,I=0,1,2$ 则有 $c_3\equiv -c_1-c_2 \pmod{3}$。

因为我们是对这个序列做整体操作，则最终序列只能是 $T\equiv xS_A+yS_B+zS_C\pmod{3}$。其中 $-1\le x,y,z\le 1$。

考虑爆搜出所有情况（实际上只有 $9$ 种）然后哈希。

区间修改时用线段树维护 $T$ 的哈希值再比对即可，时间复杂度 $O(n\log n)$。

代码比较好写就不贴了。给大家推荐一下这个运算的[另一个题](https://www.luogu.com.cn/problem/AT_arc117_c)。

---

## 作者：wwwwwza (赞：0)

挺有意思的一道题。

相当于找到三个数分别表示 $J,O,I$，通过一种运算，让他们可以互相表示。

可以发现，让其分别表示 $0,1,2$，可以做到 $c_3 \equiv -c_1-c_2 \pmod 3$。

所以杂交后的 $Sa,Sb,Sc$ 只有可能被用 $0,1,2$ 次，暴搜有 $27$ 种 $S$，哈希储存。

$T$ 用线段树维护哈希值。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int p1=31,p2=73;
const int dx[9]={0,0,0,1,1,1,2,2,2};
const int dy[9]={0,1,2,0,1,2,0,1,2};
const int dz[9]={1,0,2,0,2,1,2,1,0};
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,q,l,r;
int mod1[N],mod2[N],A[N][2],B[N][2],C[N][2];
char a[N],b[N],c[N],ch;
string s;
int t(char ch){
	if(ch=='J')return 0;
	if(ch=='O')return 1;
	if(ch=='I')return 2;
}
map<pair<int,int>,bool>mp;
struct node{
	int x,y,tag;
}tree[N<<2];
void build(int rt,int l,int r){
	if(l==r){
		tree[rt].x=tree[rt].y=t(s[l]);
		return;
	}
	int mid=l+r>>1;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	tree[rt].x=tree[rt*2].x*mod1[r-mid]+tree[rt*2+1].x;
	tree[rt].y=tree[rt*2].y*mod2[r-mid]+tree[rt*2+1].y;
	tree[rt].x%=mod;tree[rt].y%=mod;
}
void work(int rt,int len,int d){
	if(d==0){
		tree[rt].x=A[len][0];
		tree[rt].y=A[len][1];
	}else if(d==1){
		tree[rt].x=B[len][0];
		tree[rt].y=B[len][1];
	}else{
		tree[rt].x=C[len][0];
		tree[rt].y=C[len][1];
	}
}
void pushdown(int rt,int l,int r){
	if(tree[rt].tag){
		tree[rt*2].tag=tree[rt].tag;
		tree[rt*2+1].tag=tree[rt].tag;
		tree[rt].tag--;
		int mid=l+r>>1;
		work(rt*2,mid-l+1,tree[rt].tag);
		work(rt*2+1,r-mid,tree[rt].tag);
		tree[rt].tag=0;
	}
}
void update(int rt,int l,int r,int x,int y,int d){
	if(x<=l&&r<=y){
		work(rt,r-l+1,d);
		tree[rt].tag=d+1;
		return;
	}
	pushdown(rt,l,r);
	int mid=l+r>>1;
	if(x<=mid)update(rt*2,l,mid,x,y,d);
	if(y>mid)update(rt*2+1,mid+1,r,x,y,d);
	tree[rt].x=tree[rt*2].x*mod1[r-mid]+tree[rt*2+1].x;
	tree[rt].y=tree[rt*2].y*mod2[r-mid]+tree[rt*2+1].y;
	tree[rt].x%=mod;tree[rt].y%=mod;
}
void print(){
	if(mp[make_pair(tree[1].x,tree[1].y)])cout <<"Yes"<<endl;
	else cout <<"No"<<endl;
}
signed main(){
	cin >>n>>a>>b>>c;
	mod1[0]=mod2[0]=1;
	for(int i=1;i<=n;i++){
		mod1[i]=mod1[i-1]*p1%mod;
		mod2[i]=mod2[i-1]*p2%mod;
		
		A[i][0]=(A[i-1][0]*p1+0)%mod;
		A[i][1]=(A[i-1][1]*p2+0)%mod;
		
		B[i][0]=(B[i-1][0]*p1+1)%mod;
		B[i][1]=(B[i-1][1]*p2+1)%mod;
		
		C[i][0]=(C[i-1][0]*p1+2)%mod;
		C[i][1]=(C[i-1][1]*p2+2)%mod;
	}
	for(int i=0;i<9;i++){
		int h1=0,h2=0;
		for(int j=0;j<n;j++){
			h1=h1*p1+(dx[i]*t(a[j])+dy[i]*t(b[j])+dz[i]*t(c[j]))%3;
			h2=h2*p2+(dx[i]*t(a[j])+dy[i]*t(b[j])+dz[i]*t(c[j]))%3;
			h1%=mod;h2%=mod;
		}
		mp[make_pair(h1,h2)]=1;
	}
	cin >>q>>s;
	s=" "+s;
	build(1,1,n);
	print();
	while(q--){
		cin >>l>>r>>ch;
		update(1,1,n,l,r,t(ch));
		print();
	}
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

看题面吧，我也不知道怎么总结。

## 题目分析

对于每个位置，只有 $3^3=27$ 种本质不同的搭配，所以只需要把这 $27$ 种搭配放在一起暴力跑出来就可以得到种类的上界：$9$。

所以直接爆搜，线段树维护哈希即可，复杂度 $O(n\log n)$。

卡自然溢出哈哈幽默。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=2e5+5,M=1e5+5,inf=(1LL<<31)-1,mod=998244853;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
const int base=13331;
int n,m,tp;
string s[4],t,ss[100];
map<int,bool>P;
char C[4];
map<char,int>A;
inline string mult(string a,string b){
	repn(i)if(a[i]!=b[i]){
		rep(j,1,3)if(a[i]!=C[j]&&b[i]!=C[j]){
			a[i]=C[j];
			break;
		}
	}
	return a;
}
inline void dfs(string S){
	ui H=0;
	repn(i)H=(1LL*H*base+S[i])%mod;
	if(P[H])return;
	P[H]=1,ss[++tp]=S;
	int nw=tp-1;
	rep(i,1,nw)dfs(mult(S,ss[i]));
}
ui p[N],H[N][4];
struct seg{
	int lazc;
	ui H;
}xd[N<<2];
inline void build(int x,int l,int r){
	if(l==r)return xd[x].H=t[l],void();
	build(lc),build(rc),xd[x].H=(1LL*xd[L].H*p[r-mid]+xd[R].H)%mod;
}
inline void cover(int x,int l,int r,int k){
	xd[x].lazc=k,xd[x].H=H[r-l+1][k];
}
inline void pushdown(int x,int l,int r){
	if(xd[x].lazc)cover(lc,xd[x].lazc),cover(rc,xd[x].lazc),xd[x].lazc=0;
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k){
	if(OK)return cover(x,l,r,k),void();
	pushdown(x,l,r);
	if(Ll<=mid)modify(lc,Ll,Rr,k);
	if(Rr>mid)modify(rc,Ll,Rr,k);
	xd[x].H=(1LL*xd[L].H*p[r-mid]+xd[R].H)%mod;
}
inline void Main(){
	n=read(),tp=0;
	rep(i,1,3)cin>>s[i],s[i]='#'+s[i];
	m=read(),cin>>t,t='#'+t;
	C[1]='J',C[2]='O',C[3]='I';A['J']=1,A['O']=2,A['I']=3;
	rep(i,1,3)dfs(s[i]);
	p[0]=1;
	repn(i)rep(j,1,3)H[i][j]=(1LL*H[i-1][j]*base+C[j])%mod,p[i]=1LL*p[i-1]*base%mod;
	build(Root);
	puts(P.find(xd[1].H)!=P.end()?"Yes":"No");
	while(m--){
		int l=read(),r=read(),k;char c;cin>>c,k=A[c];
		modify(Root,l,r,k);
		puts(P.find(xd[1].H)!=P.end()?"Yes":"No");
	}
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}	
```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7803)。

## 思路

对于三个字符 $c_1,c_2,c_3$（字符集为 $\{\mathtt{J,O,I}\}$），若 $c_3$ 是由 $c_1,c_2$ 组合而成，钦定 $\mathtt{J}$ 的值为 $1$，$\mathtt{O}$ 的值为 $2$，$\mathtt{I}$ 的值为 $3$，容易发现 $c_1+c_2+c_3\equiv 0\pmod 3$。

最终得到的串一定能被 $a$ 个 $S_1$，$b$ 个 $S_2$，$c$ 个 $S_3$ 组成，而我们知道 $3a\equiv 0\pmod 3$，那么 $a,b,c$ 的取值范围仅在 $\{0,1,2\}$ 之间，也就是最多能产生的 $27$ 个不同的串。

那么我们直接暴力生成串，求出每个串的哈希值，然后用线段树维护 $T$ 的哈希值即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=2e5+7;

const int Mod=998244353;
const int bas=23;

int n,Q;
string S1,S2,S3,T;
ll Sm[Maxn];
ll pw[Maxn];
ll hsS[Maxn];

inline char Getth(char x,char y){
    if(x==y) return x;
    return 'J'+'O'+'I'-x-y;
}
inline string Turn(string a,string b){
    string z;
    for(int i=0;i<n;i++)
        z+=Getth(a[i],b[i]);
    return z;
}
map<string,bool>mp;

string lst[Maxn];

struct TREE{
    int l,r,len;
    ll hsh;
    char tag;
}tree[Maxn<<2];

inline void pushup(int node){
    tree[node].hsh=(tree[node<<1].hsh+tree[node<<1|1].hsh*pw[tree[node<<1].len]%Mod)%Mod;
}
void buildtree(int node,int l,int r){
    tree[node].l=l;
    tree[node].r=r;
    tree[node].len=r-l+1;
    tree[node].tag=0;
    if(l==r){
        tree[node].hsh=T[l-1];
        return ;
    }
    int mid=l+r>>1;
    buildtree(node<<1,l,mid);
    buildtree(node<<1|1,mid+1,r);
    pushup(node);
} 

inline void spread(int node,char c){
    tree[node].hsh=Sm[tree[node].len-1]*(ll)c%Mod;
    tree[node].tag=c;
}
inline void pushdown(int node){
    if(tree[node].tag==0) return ;
    spread(node<<1,tree[node].tag);
    spread(node<<1|1,tree[node].tag);
    tree[node].tag=0;
}
void modify(int node,int l,int r,char c){
    if(tree[node].l>=l and tree[node].r<=r){
        spread(node,c);
        return ;
    }
    pushdown(node);
    int mid=tree[node].l+tree[node].r>>1;
    if(l<=mid) modify(node<<1,l,r,c);
    if(r>mid) modify(node<<1|1,l,r,c);
    pushup(node);
}
ll query(int node,int l,int r){
    if(tree[node].l>=l and tree[node].r<=r) return tree[node].hsh;
    pushdown(node);
    int mid=tree[node].l+tree[node].r>>1;
    ll hs=0;
    if(r>mid) hs=query(node<<1|1,l,r);
    if(l<=mid) hs=(hs*pw[tree[node<<1].len]%Mod+query(node<<1,l,r));
    return hs; 
}
inline ll geths(string s){
    ll hs=0;
    for(int i=n-1;~i;i--) hs=(hs*bas%Mod+s[i])%Mod;
    return hs;
}

int main(){
    scanf("%d",&n);
    cin>>S1>>S2>>S3;

    lst[0]=S1,lst[1]=S2,lst[2]=S3;
    mp[S1]=mp[S2]=mp[S3]=1;
    int l=2;
    for(int i=1;i<=l;i++){
    	cout<<lst[i]<<endl;
        for(int j=0;j<i;j++){
            string pp=Turn(lst[i],lst[j]);
            if(!mp.count(pp)) mp[pp]=1,lst[++l]=pp;
        }
    }
    int cp=0;
    for(auto i:mp){
        string s=i.first;
        hsS[++cp]=geths(s);
    }
    ll prd=1;
    for(int i=0;i<=n;i++){
        Sm[i]=((i-1>=0?Sm[i-1]:0)+prd)%Mod;
        pw[i]=prd;
        prd=prd*bas%Mod;
    }
    

    scanf("%d",&Q);
    cin>>T;
    buildtree(1,1,n);
    ll hs=geths(T);

    bool flg=0;
    for(int i=1;i<=cp;i++){
        if(hsS[i]==hs) flg=1;
    }
    if(flg) puts("Yes");
    else puts("No");

    while(Q--){
        int l,r;char c;
        scanf("%d%d",&l,&r);
        cin>>c;
        modify(1,l,r,c);
        hs=query(1,1,n);
        bool tag=0;
        for(int i=1;i<=cp;i++) if(hs==hsS[i]) tag=1;
        if(tag) puts("Yes");
        else puts("No");
    }    
    return 0;
}
```

---

