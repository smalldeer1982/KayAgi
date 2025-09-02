# Preorder

## 题目描述

给你一颗 $2^n-1$ 个节点的完美二叉树，按照以下顺序编号：  
 - 根节点编号为 $1$;
 - 编号为 $x$ 的节点左儿子为 $2x$，右儿子为 $2x+1$。
 
 每个顶点上有一个字母 `A` 或 `B`，在节点 $x$ 上的字母为 $s_x$。  
 顶点 $x$ 的先序串 $f(x)$ 定义如下：  
 - 如果 $x$ 是叶子，那么 $x$ 的先序串是 $s_x$；  
 - 否则 $x$ 的先序串是 $s_x+f(l_x)+f(r_x)$，其中 $+$ 表示连接两个字符串，$l_x,r_x$ 代表 $x$ 的左右儿子。
 
一棵树的先序串是根节点的先序串。  
允许执行交换任意一个非叶子节点的左右儿子任意次，求树可能的所有不同先序串的个数，
答案模 $998244353$ 。

## 样例 #1

### 输入

```
4
BAAAAAAAABBABAB```

### 输出

```
16```

## 样例 #2

### 输入

```
2
BAA```

### 输出

```
1```

## 样例 #3

### 输入

```
2
ABA```

### 输出

```
2```

## 样例 #4

### 输入

```
2
AAB```

### 输出

```
2```

## 样例 #5

### 输入

```
2
AAA```

### 输出

```
1```

# 题解

## 作者：zsq147258369 (赞：12)

题意：

给你一棵以BFS序排列的深度为 $n$ 的满二叉树，每个节点有一个字符 $A$ 或 $B$。

现有一操作：把某一个节点的左右子树调换。

问：经过若干次操作，总共可以得到多少种不同的前序遍历。

我们可以先把树脑补出来。

令 $f_u$ 表示 $u$ 的子树共有 $f_u$ 种前序遍历。那么叶子节点的值显然是 $1$。

有考虑 $u$ 有左儿子 $a$ 和右儿子 $b$。

由乘法原理得知 $f_u=f_a*f_b$。

但我们还可以交换 $a$ 和 $b$，那么 $f_u=2*f_a*f_b$。

~~万事大吉！写代码去了！~~

不急，还有一种情况。就是如果 $a$ 和 $b$ 通过某一种方式同构的话，交换 $a$ 和 $b$ 其实是一样的情况。

那么如何判断同构？有一种方式是通过记录其子树的字典序最小的前序遍历 $s_u$。如果  $s_a=s_b$，那么他们可以同构。

代码 ~~勿喷~~

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=9e5,mod=998244353;

int n,a[N],f[N],m,g[N],dep[N];

string s[N];

#define ls (x<<1)
#define rs (x<<1|1)

void dfs(int x)
{
	if(ls>m){s[x]=a[x]+'0';f[x]=1;return;}
	dep[ls]=dep[rs]=dep[x]+1;
	dfs(ls),dfs(rs);
	if(s[ls]==s[rs])f[x]=f[ls]*f[rs]%mod;
	else f[x]=f[ls]*f[rs]%mod*2%mod;
	s[x]=a[x]+'0';
	if(s[ls]<s[rs])s[x]+=s[ls]+s[rs];
	else s[x]+=s[rs]+s[ls];
}

main()
{
	cin>>n;m=pow(2,n)-1;
	for(int i=1;i<=m;i++)
	{
		char z;
		cin>>z;
		if(z=='A')a[i]=1;
	}
	dfs(1);
	cout<<f[1];
}
```


---

## 作者：听取MLE声一片 (赞：4)

题意：

给你一棵深度为 $n$ 的满二叉树，每个节点有一个字符 A 或 B。

操作为：把某一个节点的左右子树调换。

询问：经过若干次操作，总共可以得到多少种不同的中序遍历。

很明显，对于每个节点来说，只有两种可能：操作和不操作。

进一步的，如果一个点的左右子树不是同构，那么操作之后必定会产生新的情况；如果是同构，则操作跟不操作没有区别。

同构我这里用了一个字符串来存储，具体来说是该节点 + 左右子树字符串字典序小的 + 左右子树字符串字典序大的，这样就可以判断是不是同构，直接比较即可。

如果左右子树不为同构的点的个数为 $m$，那么答案显然是 $2^m$，因为每个符合要求的点都有操作和不操作两种情况。




```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int mod=998244353;
const int N=3e5+10;
int n,m,ls[N],rs[N],ans;
string s,b[N];
char a[N];
void dfs(int x){
	if(x*2+1>m){
		b[x]=a[x];
		return;
	}
	dfs(x*2);
	dfs(x*2+1);
	int ls=x*2,rs=x*2+1;
	if(b[ls]!=b[rs])
		ans++;
	if(b[rs]>b[ls])
		b[x]=a[x]+b[rs]+b[ls];
	else b[x]=a[x]+b[ls]+b[rs];
}
int ksm(int x,int y){
	int s=1;
	while(y>0){
        if(y%2==1)
            s=s*x%mod;
        x=x*x%mod;
        y=y/2;
    }
    return s;
}
signed main()
{
	n=read();
	cin>>s;
	m=s.length();
	s=' '+s;
	for(int i=1;i<=m;i++)
		a[i]=s[i];
	dfs(1);
	cout<<ksm(2,ans);
	return 0;
}

```

---

## 作者：naroto2022 (赞：1)

# CF1671E 题解

[博客园里看更佳](https://www.cnblogs.com/naroto2022/p/18717823)

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1671E)

[原题传送门](https://codeforces.com/problemset/problem/1671/E)

### 思路

随便思考下发现是树形 dp，考虑 $dp_u$ 是以 $u$ 为子树的答案。

于是就有两种情况。

$dp_u=\left\{\begin{array}{l}dp_{ls}\times dp_{rs}\\2\times dp_{ls}\times dp_{rs}\end{array}\right.$

然后讨论两种转移情况下的前提，要是左右子树的字符串不一样，那就可以交换左右子树，成为第二种情况。

接下来考虑左右子树的字符串是否会一样，由于操作可逆，所以只要两个集合中有一个字符串是相同的，两个集合就是可以互相转换的。

于是考虑把字典序最小的当做代表，在 dp 转移的时候顺带统计。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define gc()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define ll long long
#define ls u<<1
#define rs u<<1|1
using namespace std;
const int MN=(1<<18)+5,mod=998244353;
ll n,dp[MN];
char buf[1<<23],*p1=buf,*p2=buf,s[MN];
string str[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}return x*f;}
char getc(){char ch=gc();while(ch!='A'&&ch!='B')ch=gc();return ch;}
void dfs(ll u){
    if(u>=(1<<(n-1))){
        dp[u]=1;str[u]=s[u];
        return;
    }
    dfs(ls);dfs(rs);
    if(str[ls]==str[rs]) dp[u]=dp[ls]*dp[rs]%mod;
    else dp[u]=2*dp[ls]*dp[rs]%mod;
    str[u]=s[u];
    if(str[ls]<str[rs]) str[u]+=str[ls]+str[rs];
    else str[u]+=str[rs]+str[ls];
}
int main(){
    n=read();
    for(int i=1; i<(1<<n); i++) s[i]=getc();
    dfs(1);write(dp[1]);putchar('\n');
    return 0;
}//250216
```

---

## 作者：fishing_cat (赞：1)

### 题意

一棵完全二叉树，有点权 $1$ 和 $0$，可以交换任意点的左右子树，问有多少种前序遍历。

### 思路

可以记 $dp_i$ 为以点 $i$ 为根的子树的前序遍历数。在点 $i$ 的左右子树没有相同的前序遍历时，按照乘法原理，可以得
$$dp_i = 2 \times dp_{ls} \times dp_{rs}$$

在点 $i$ 的左右子树有相同的前序遍历时，会发现交换左右儿子不会使前序遍历改变，此时转移为
$$dp_i = dp_{ls} \times dp_{rs}$$

那如何判断是否是情况二？在点 $i$ 的左右子树有相同的前序遍历时，会发现左右子树的所有前序遍历种类一定相同，所以只需比较其一。那我们就可以记录每个点为根时可以交换出的字典序最小的前序遍历，来判断是否是情况二。

具体细节可以见代码。

### code 

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline

using namespace std;

const ll mod = 998244353;
const ll M = 3e5;

ll n, len, tr[M], dp[M];
string vel[M];
char s;

void dfs(ll u) {
	if (u*2 > len) return ; // 叶子节点跳出
	ll ls = u*2, rs = u*2 + 1;
	dfs(ls);
	dfs(rs);
	if (vel[ls] != vel[rs]) dp[u] = 2*dp[ls]*dp[rs] % mod; // 情况一转移
	else dp[u] = dp[ls]*dp[rs] % mod; // 情况二转移
	if (vel[ls] < vel[rs]) vel[u] += vel[ls] + vel[rs];
	else vel[u] += vel[rs] + vel[ls]; // 合并字典序最小的前序遍历
}

int main() {
	read(n); len = (1 << n) - 1;
	for (int i = 1; i <= len; i ++) {
		cin >> s;
		tr[i] = s - 'A', vel[i] = s, dp[i] = 1;
	}
	dfs(1);
	cout << dp[1] << '\n';
	return 0;
}
```

---

## 作者：yuruilin2026 (赞：0)

一道基本上不知道怎么做的题目。\
当做完我还不知道为什么过的。\
感谢神犇 [Hootime](https://www.luogu.com.cn/user/1275540) 看到题目之后再旁边说了一句思路，然后给了我这个蒟蒻一点启发。
### 解题思路：
这道题很明显是一个树形 DP 吧（不然呢？）。\
对于第 $i$ 个点的方案数 $dp_i$：
- 如果任意交换后 $i \times 2$ 的前序排列也不可能与 $i \times 2$ 的前序排列重合，那么根据乘法原理 $dp_i = 2 \times dp_{2i} \times dp_{2i+1}$。
- 如果任意交换后 $i \times 2$ 的前序排列也可能与 $i \times 2$ 的前序排列重合，所以说有一些情况重复，$dp_i = dp_{2i} \times dp_{2i+1}$。

Q：那如何求出是否重复呢？\
A：我们在学 Floyd 时知道了一些东西：\
若 $i$ 与 $k$ 可达，$k$ 与 $j$ 可达，则 $i$ 与 $j$ 可达。\
所以说可以找到一个代表，然后判断代表是否相同。\
这里使用字典序。\
我们可以对每个点 $i$ 求出以 $i$ 为根节点的字典序最小的排列（对于第 $i$ 个点可以用 $i \times 2$ 点的排列和 $i \times 2 + 1$ 点的排列组合而来）。\
基本就完了，直接看代码：
### AC 代码（洛谷上交不了，只能去 CF 上交）：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,dp[514514],m,mod = 998244353;
char a[514514];
string b[514514];
string minn(string xx,string yy){
	return xx<yy?xx:yy;
}
void sou(long long x){
	if(x * 2 >= n+1){
		b[x] = a[x];
		return;
	}
	sou(x*2);
	sou(x*2+1);
	b[x] = minn(a[x] + b[x*2] + b[x*2+1],a[x] + b[x*2+1] + b[x*2]);
}
void DP(long long x){
	if(x * 2 >= n+1) return;
	DP(x*2);
	DP(x*2+1);
	if(b[x*2] == b[x*2+1]) dp[x] = dp[2*x] * dp[x*2+1];
	else dp[x] = dp[x*2] * dp[x*2+1] * 2;
	dp[x] %= mod;
}
int main(){
	cin >> n;
	m = n,n = pow(2,n)-1;
	for(long long i = 1;i <= n;++i){
		cin >> a[i];
		dp[i] = 1;
	}
	sou(1);//求出字典序最小的遍历排列 
	DP(1);//DP
	cout << dp[1]; 
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

[题目链接](https://codeforces.com/problemset/problem/1671/E)

考虑 dp，设 $f_u$ 表示以 $u$ 为根的子树内能得到多少种不同的先序序列。

直接的想法是根据乘法原理 $f_u=f_{ls}\times f_{rs}$ 转移，然后考虑交换操作产生的影响：如果左右两棵子树不同构（注意这里同构的定义为：存在一种交换方式，使得两棵树结构相同），那么交换两棵子树也会产生相同的贡献，此时就有 $f_u=2\times f_{ls}\times f_{rs}$。

现在的问题就是判断子树同构，因为是个满二叉树，你可以考虑胡编一个哈希解决，时间复杂度 $O(2^n)$。

但其实没必要，子树同构等价于它们字典序最小的先序串相同，直接暴力维护这个东西即可，上界大概是 $O(n2^n)$，因为 $2^n$ 个 $s_i$ 都会出现在最多 $O(n)$ 个字符串内。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+5;
const int mod=998244353;
int n,ls[N],rs[N],f[N];
string hsh[N];
char s[N];
void dfs(int now){
    if(!ls[now]||!rs[now]){
        hsh[now]=s[now];f[now]=1;
        return;
    }
    dfs(ls[now]);dfs(rs[now]);
    hsh[now]=s[now];
    f[now]=f[ls[now]]*f[rs[now]]%mod;
    if(hsh[ls[now]]!=hsh[rs[now]]) f[now]=f[now]*2%mod;
    if(hsh[ls[now]]<hsh[rs[now]]) hsh[now]+=hsh[ls[now]]+hsh[rs[now]];
    else hsh[now]+=hsh[rs[now]]+hsh[ls[now]];
}
void Main(){
    cin>>n>>(s+1);n=(1ll<<n)-1;
    For(i,1,n){
        if((i<<1)<=n) ls[i]=i<<1;
        if((i<<1|1)<=n) rs[i]=i<<1|1;
    }
    dfs(1);cout<<f[1]<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T=1;//cin>>T;
    while(T--) Main();
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Analysis

普通的先序遍历：

1. 存入本节点。

2. 先序遍历左儿子。

3. 先序遍历右儿子。

由于本题中任意次 swap 左右儿子的操作等价于先序遍历时变为：

1. 存入本节点。

2. 任意选择左右儿子中的一个遍历

3. 选择另一个儿子遍历

我们命名这样的遍历为「新遍历」。

我们设 $b_i$ 表示 $i$ 节点子树能有几种不同的「新遍历」序列。显然对于叶子 $x$，$b_x=1$。

我们考虑如何将儿子的 $b$ 推到父亲的 $b$。

------------

**引理：** 如果两棵子树所有可能的「新遍历」序列中字典序最小的不同，则这两个子树的所有可能的「新遍历」序列均不相同。

**证明：** 反证法。假设有一对子树 $x,y$ 不满足引理。

我们可以知道 $x,y$ 取到相同的「新遍历」序列时每个节点先遍历左儿子还是右儿子。我们把 $x,y$ 某些子树交换左右儿子使得每个节点均先遍历左儿子。我们发现此时 $x,y$ 两棵树是一模一样的，这样所有可能的「新遍历」序列中字典序最小的一定相同。矛盾，原命题成立。

------------

所以，我们从下至上处理这棵树。每处理完一个节点就把这个子树调成「新遍历」序列字典序最小的样子。

当现在到了节点 $x$，两个儿子分别是 $ls,rs$，那我们可以在 $size(ls)+size(rs)$ 的时间里判断两个树是否相等，或是判断「新遍历」序列字典序大小。

* 若两个子树相同，则 $b_x=b_{ls}\times b_{rs}$。

* 否则，$b_x=2\times b_{ls}\times b_{rs}$。

然后将两个子树调成「新遍历」序列字典序最小的样子。

时间复杂度 $O(n2^n)$。

### Code

[Link](https://codeforces.com/contest/1671/submission/154728988)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
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
const ll mod=998244353;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N (1<<18)+10
#define ls (rt<<1)
#define rs (rt<<1|1) 
int m,n;
bool a[N];
char ch;
int b[N];
int cmp(int x,int y){
	if(a[x]>a[y]) return 1;
	if(a[x]<a[y]) return -1;
	if((x<<1)>n) return 0;
	int res=cmp(x<<1,y<<1);
	if(res!=0) return res;
	else return cmp(x<<1|1,y<<1|1);
}
void sw(int x,int y){
	swap(a[x],a[y]);
	if((x<<1)>n) return ;
	sw(x<<1,y<<1);
	sw(x<<1|1,y<<1|1);
}
inline int dfs(int rt){
	if(ls>n) return 1;
	int r1=dfs(ls);
	int r2=dfs(rs);
	int res=cmp(ls,rs);
	if(res==1) sw(ls,rs);
	if(res!=0) return r1*r2*2%mod;
	else return r1*r2%mod;
}
signed main(){IOS;
	cin>>m;
	n=(1<<m)-1;
	For(i,1,n){
		cin>>ch;
		a[i]=(ch=='B');
	}
	cout<<dfs(1)<<endl;
return 0;}
```

---

