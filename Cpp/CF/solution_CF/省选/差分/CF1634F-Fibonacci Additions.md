# Fibonacci Additions

## 题目描述

对于一个数组 $X$，有如下操作：对于区间 $[l,r]$，给 $X_l$ 加上 $F_1$，给 $X_{l+1}$ 加上 $F_2$，以此类推，并且给 $X_r$ 加上 $F_{r-l+1}$。然后将区间 $[l,r]$ 内每个数对 $MOD$ 取模。$F$ 数组是这样一个数组：$F_1=1$，$F_2=1$，当 $i>2$ 时 $F_i=F_{i-1}+F_{i-2}$。

已知两个长度相同的数组 $A$，$B$，给出若干次操作，每次操作后你需要求出取模过后的数组 $A$，$B$ 是否相等。

## 样例 #1

### 输入

```
3 5 3
2 2 1
0 0 0
A 1 3
A 1 3
B 1 1
B 2 2
A 3 3```

### 输出

```
YES
NO
NO
NO
YES```

## 样例 #2

### 输入

```
5 3 10
2 5 0 3 5
3 5 8 2 5
B 2 3
B 3 4
A 1 2```

### 输出

```
NO
NO
YES```

# 题解

## 作者：_ajthreac_ (赞：28)

这道题目形式很新颖，但是解法很简单。

首先注意到我们只关心 $A,B$ 的差是否相等，那么可以定义一个 $C_i=A_i-B_i$，一切操作转化成在 $C$ 上进行区间加减。

区间加减？回想我们学过的算法，**差分**正是将区间加减的复杂度减小一维的方式。只是这个题形式特殊，我们要考虑差分的本质。

区间加同一个数可以差分是因为增量序列的递推式为 $a_i=a_{i-1}$，而后一个数减去前一个数正好抵消。带回此题，增量序列的递推式为 $a_i=a_{i-1}+a_{i-2}$，容易知道此时想要抵消需要减去前两个数。设操作区间为 $[l,r]$，差分数组为 $D_i=C_i-C_{i-1}-C_{i-2}$，那么就在 $D_l$ 上 $+1$，在 $D_{r+1},D_{r+2}$ 上分别减去 $F_{r-l+2},F_{r-l+1}$ 以抵消后面的。

判断答案可以通过判断 $D$ 是否全为 $0$ 实现，只需要加一个计数器记录非零的个数即可。

核心代码如下：
```cpp
const int N=300010;
int n,q,a[N],f[N],p,cnt;
il void M(int x,int v){
  if(x>n)return;
  cnt-=!!a[x],(a[x]+=v+p)%=p,cnt+=!!a[x];
}
signed main(){
  Read(n),Read(q),Read(p),f[1]=1;
  for(int i=2;i<=n;i++)f[i]=(f[i-1]+f[i-2])%p;
  for(int i=1;i<=n;i++)Read(a[i]);
  for(int i=1,x;i<=n;i++)Read(x),(a[i]-=x-p)%=p;
  for(int i=n;i>1;i--)a[i]=(a[i]-a[i-1]-a[i-2]+p+p)%p;
  for(int i=1;i<=n;i++)cnt+=!!a[i];
  for(int i=1,l,r;i<=q;i++){
    char s[5];scanf("%s",s),Read(l),Read(r);
    if(s[0]=='A')M(l,1),M(r+1,-f[r-l+2]),M(r+2,-f[r-l+1]);
    else M(l,-1),M(r+1,f[r-l+2]),M(r+2,f[r-l+1]);
    puts(cnt?"NO":"YES");
  }
  KafuuChino HotoKokoa
}
```

---

## 作者：EXODUS (赞：22)

# Part 1：前言
差分好题。~~但我差点码了区间加斐波那契数列上去。~~

# Part 2：正文
首先很套路的想到，判断两个数组是否相等可以直接维护这两个数组的差值。

~~因为大写不好打~~，接下来的数组全部用小写字母表示。$f_i$ 表示斐波那契数列的第 $i$ 项。

记录 $c_i=a_i-b_i$ ，那么 $\forall i\in[1,n],a_i=b_i$ 等价于 $\forall i\in[1,n],c_i=0$。

然后每次相当于对 $c$ 数组的一个区间加/减一个等差数列，直接转化为 [CF446C](https://www.luogu.com.cn/problem/CF446C)。

~~然后就做完了ヽ(✿ﾟ▽ﾟ)ノ~~ 常数偏大，很可能寄掉。

然后看了一眼标签，差分？

考虑差分为什么可以优化区间加的时间复杂度，把区间加转化为单点加。（即答

那么如何把斐波那契数列加转化为单点加呢？

设计一个数组 $d$，使得 $d_i=c_i-c_{i-1}-c_{i-2}$。此时区间加斐波那契数列时，设 $j$ 为不在边界上的点，那么 $d_j=c_j+f_j-c_{j-1}-f_{j-1}-c_{j-2}-f_{j-2}=c_j-c_{j-1}-c_{j-2}$，发现满足中间不变，直接转化为单点加，这里实现见代码。

~~什么你问我怎么想到的？看看斐波那契递推公式啦~~

同时维护一下 $d$ 数组中 $0$ 的个数 $cnt$，如果 $cnt=n$ 说明 $d$ 全 $0$，则 $c$ 全 $0$，即 $a=b$。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int res=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){res=res*10+c-'0';c=getchar();}
    return res*f;
}
inline char readc(){
    char c=getchar();
    while(!isalpha(c)){c=getchar();}
    return c;
}
const int N=3e5+7;
int a[N],f[N],x,cnt;
int n,q,mod;
void add(int x,int val){
	if(x>n)return;
	cnt-=(a[x]==0);
	a[x]=((a[x]+val)%mod+mod)%mod;
	cnt+=(a[x]==0);
}
char c[2];
int l,r;
signed main(){
	scanf("%lld%lld%lld",&n,&q,&mod);
	f[1]=f[2]=1;
	for(int i=3;i<=n+1;i++)f[i]=(f[i-1]+f[i-2])%mod;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&x),a[i]=(a[i]-x+mod)%mod;
	for(int i=n;i>=1;i--){
		if(i==1)continue;
		a[i]=(a[i]-a[i-1]-a[i-2]+mod+mod)%mod;
		cnt+=(a[i]==0);
	}
	cnt+=(a[1]==0);
	//for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	//cout<<endl;
	while(q--){
		scanf("%s%lld%lld",c,&l,&r);
		if(c[0]=='A'){
			add(l,1);
			add(r+1,-f[r-l+2]);
			add(r+2,-f[r-l+1]);
		}
		else{
			add(l,-1);
			add(r+1,f[r-l+2]);
			add(r+2,f[r-l+1]);
		}
		if(cnt==n)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```
# Part 4：后文
点赞再走吧（可怜

---

## 作者：小木虫 (赞：5)

### Preface  
初学差分，我对很多差分性质都不太熟，有一些比较弱智的困惑，我会把这些困惑都写到题解里，这是一道比较难的思维题，看到好多大佬都没有结论上的证明，本蒟蒻来一发。  
### Problem  
给你两个序列，它们可以区间加斐波那契数列，求每次区间加后它俩是否在模意义下相等。  
### Problem  
我们先搞出 $a$ 与 $b$ 的差 $c$ 存起来，这样就仅仅是要求 $c$ 全部为 0，简化问题。  

众所周知，差分可以用来解决区间加，只需要头尾更改就可以，然而这道题我们需要给它一点小魔改，使差分不仅仅是现在的数减去上一个数，而是要再减去上上个数，这样就很契合斐波那契数列，中间抵消了，可以做到头尾更改了。  

我们现在拿到了一个差分数组，但是不能停下来啊！！！如果这道题只有最后一个询问的话直接还原出来原数组就可以了，但是这题每更改一次就询问，非常的吃不消，那么我们想着能不能找出差分数组的一些小性质。  

回头看看我们的要求是 $c$ 全体为 0。那么我们只要证明只要差分数组全部为 0，那么 $c$ 也全体为 0 就可以了。  

我们利用数学归纳法证明，差分数组 $d_i=c_i-c_{i-1}-c_{i-2}$，若 $c_{i-1},c_{i-2}$ 都为 0，此时 $d_i$ 也为 0，那么 $c_i$ 一定为 0。  
观察 $d$ 的第一项与第二项，第一项的 $d$ 就等于 $c$，于是第一个 $c$ 就等于 0，第二项的 $d$ 只等于前面两个玩意的和，那么第二项的 $c$ 也等于 0。于是后面根据数学归纳法全部成立，命题得证。  
最后贴一下代码：  
```cpp
#pragma GCC optimize(2,3)
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
ll fib[N];int n,q,l,r;char opt[2];
ll a[N],b[N],c[N],d[N];int mod;
int zero;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q>>mod;
	fib[1]=1;fib[2]=1;
	for(int i=3;i<=n+5;i++)
		fib[i]=fib[i-1]+fib[i-2],fib[i]%=mod;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)c[i]=a[i]-b[i];
	d[1]=c[1];d[2]=c[2]-c[1];
	for(int i=3;i<=n;i++)d[i]=c[i]-c[i-1]-c[i-2];
	for(int i=1;i<=n;i++)d[i]=(d[i]%mod+mod)%mod;
	for(int i=1;i<=n;i++)zero+=(d[i]!=0);
	while(q--){
		cin>>opt;cin>>l>>r;
		int neg=0;
		if(opt[0]=='A')neg=1;
		else neg=-1;
		if(d[l]==0)zero++;
		d[l]=(d[l]+(neg+mod)%mod)%mod;
		if(d[l]==0)zero--;
		if(r!=n){
			if(d[r+1]==0)zero++;
			d[r+1]=(d[r+1]+(-neg*fib[r-l+2]%mod+mod)%mod)%mod;
			if(d[r+1]==0)zero--;
		}
		if(r+1<n){
			if(d[r+2]==0)zero++;
			d[r+2]=(d[r+2]+(-neg*fib[r-l+1]%mod+mod)%mod)%mod;
			if(d[r+2]==0)zero--;
		}
		if(zero==0)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：4)

### Preface

比赛时还没写 D，瞄了一眼 F。“这不是[原题](https://www.luogu.com.cn/problem/CF446C)吗？”我想。然后花了 $10^9+7$ 年发现根本不是这样做的（甚至 $O(n)$）。

### Analysis

首先可以预处理出 Fib（斐波那契数列），记为 $F$。

我们记 $P_i=A_i-B_i$。题目要 $P$ 每次区间加（或减） Fib 后询问是否全为 $0$。

发现区间加 Fib 非常头痛。

由于 Fib 的递推式为 $F_n-F_{n-1}-F_{n-2}=0$，我们考虑以下不常规的差分（无意义的下标取值为 $0$）：

$$Q_i=P_i-P_{i-1}-P_{i-2}\quad(1\le i\le n)$$

这样 $P$ 区间加 Fib 相当于 $Q$ 的区间两端做少量加减。（区间中间部分满足：每一项 与 前两项和 的差保持不变）

具体地，若 $P$ 中 $[L,R]$ 加 Fib，则“少量加减”指：

$$\begin{aligned}
Q_L&+=F_1(=1)
\\
Q_{R+1}&-=F_{R-L}+F_{R-L+1}(=F_{R-L+2})
\\
Q_{R+2}&-=F_{R-L+1}
\end{aligned}$$

而

$$\forall i\in[1,n],P_i=0\iff\forall i\in[1,n],Q_i=0$$

所以每次记录 $Q$ 中 $0$ 的个数即可。

### Detail

别忘了取模。

输出居然卡 `endl`，不可思议。

### Code

[Link](https://codeforces.com/contest/1634/submission/145814935)

---

## 作者：Hisaishi_Kanade (赞：2)

设 $p_i=a_i-b_i$，那么查询 $a,b$ 是否相等就是问是否有 $p_i=0$。

这个题在区间上加一个斐波那契数列，貌似处理有点棘手。

我们考虑更简单的做法？区间操作？差分！

但是如果是 $d_i=p_i-p_{i-1}$ 这种，没办法 $O(1)$ 的操作斐波那契数列。

我们观察 $f_{i}=f_{i-1}+f_{i-2}$，如果我们改令 $d_{i}=p_{i}-p_{i-1}-p_{i-2}$？

再进行题目中的操作呢？

$d_{i}=p_{i}+f_{j}-p_{j-1}-f_{j-1}-p_{j-2}-f_{j-2}=p_{i}-p_{i-1}-p_{i-2}=d_i$。

那么这样，非边界的点就完全不会变化。

再考虑怎么改两边，设要改的是 $[l,r]$。

因为 $q_{l}\gets q_{l}+f_1=q_{l}+1$，所以 $d_{l}\gets d_{l}+1$。

带入几项，可以发现这样 $d_{l+k} \gets d_{l}+f_{k+1}$。

但是在 $d_{r}$ 后方的变化我们是不希望看到的，所以要 $d_{r+1}\gets d_{r+1}-f_{r-l+2}$ 和 $d_{r+2}\gets d_{r+2}-f_{r-l+1}$。

```cpp
int n,p,q,cnt;
const int maxn=300005;
int a[maxn],b[maxn];
long long f[maxn],d[maxn];
inline void add(int pos,int ad)
{
	if(pos>n)
		return ;
	else
	{
		cnt-=d[pos]!=0;
		d[pos]=(d[pos]+ad+p)%p;
		cnt+=d[pos]!=0;
		return ;
	}
}
char opt[3];
int main()
{
	int i,j,l,r;
	n=read();
	q=read();
	p=read();
	f[1]=f[2]=1;
	rep(i,3,n)
		f[i]=(f[i-1]+f[i-2])%p;
	rep(i,1,n)
		a[i]=read();
	rep(i,1,n)
	{
		b[i]=read();
		a[i]=(a[i]-b[i]+p)%p;
//		printf("%d\n",a[i]);
	}
	d[1]=a[1];cnt=d[1]!=0;
	req(i,n,2)
	{
		d[i]=a[i]-a[i-1]-a[i-2];
		d[i]=(d[i]%p+p)%p;
		cnt+=d[i]!=0;
	}
//	rep(i,1,n)
//		printf("%d\n",d[i]);
	rep(i,1,q)
	{
		while( (opt[0]=getchar()) && (opt[0]!='A') && opt[0]!='B');
		l=read();r=read();
		if(opt[0]=='A')
		{
			add(l,1);
			add(r+1,-f[r-l+2]);
			add(r+2,-f[r-l+1]);
		}else
		{
			add(l,-1);
			add(r+1,f[r-l+2]);
			add(r+2,f[r-l+1]);
		}
		puts(cnt?"NO":"YES");
	}
	return 0;
}
```

---

## 作者：hyman00 (赞：1)

## 001

一看到这个题目，第一想法是用一个线段树之类的强大的数据结构维护数组，但是这道题的正解不是这样的！

## 002

我们可以先来考虑一个简单一点的问题：

维护一个长度为 $n$ 数组 $a$，每次操作给定 $l,r,c$，对于所有 $l\le i\le r$，$a_i=a_i+c$，每次操作后输出 $a$ 是不是全是 0。

-------------

这里我们暂且称 $a_n=0$，那么设 $b_i=a_{i+1}-a_i(0\le i<n)$。

这时，一次操作就变成了：

- 如果 $l\ne0$，$b_{l-1}=b_{l-1}+c$
- $b_r=b_r-c$

这也就是维护差分数组的思路。

但是，怎么判断是不是全是 0 呢？

-------------

观察发现，$a$ 数组全是 0, 和 $b$ 数组全是 0 是等价的，于是就可以维护一个 $cnt$ 是 $b$ 数组中目前有多少非零的值，每次操作更新即可

## 003

回归正题，这道题也用了这么一个方法。

这里的 $a$ 和 $b$ 完全相同可以转化为 $c_i=a_i-b_i=0$。

因为 $fib_i+fib_{i+1}=fib_{i+2}$，所以 $fib_{i+2}-fib_{i+1}-fib_i=0$。

这时维护一个 $d$ 数组 $d_i=c_{i+2}-c_{i+1}-c_i$

每次操作就可以是常数复杂度了！

A 操作：

- 如果 $l>1$，$d_{l-2}=d_{l-2}+1$
- 如果 $r>0$，$d_{r-1}=d_{r-1}-fib_{r-l+1}$
- $d_r=d_r-fib_{r-l}$

B 操作：

- 如果 $l>1$，$d_{l-2}=d_{l-2}-1$
- 如果 $r>0$，$d_{r-1}=d_{r-1}+fib_{r-l+1}$
- $d_r=d_r+fib_{r-l}$

## 004

附上 $27$ 行AC代码：
```c++
#include<bits/stdc++.h>
using namespace std;
long long a[300009],b[300009],c[300009],f[300009],kk;
long long fib[300009];
long long n,m,mod,x,y;
inline void upd(int x,int num){
	if(f[x])kk--;
	f[x]=(f[x]+num+mod)%mod;
	if(f[x])kk++;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>mod;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++)cin>>b[i],c[i]=(a[i]%mod-b[i]%mod+mod)%mod;
	c[n]=c[n+1]=0;fib[0]=fib[1]=1;
	for(int i=2;i<n+4;i++)fib[i]=(fib[i-1]+fib[i-2])%mod;
	for(int i=0;i<n;i++)f[i]=(c[i+2]-c[i+1]-c[i]+mod+mod)%mod,kk+=(f[i]!=0);
	for(int i=0;i<m;i++){
		char cc;
		cin>>cc>>x>>y;
		x--,y--;
		int ss=((cc=='A')?1:-1);
		if(x>1)upd(x-2,ss);
		if(y)upd(y-1,-ss*fib[y-x+1]);
		upd(y,-ss*fib[y-x]);
		cout<<(kk?"NO":"YES")<<"\n";
	}
}
```

## 005

~~不得不说，难得有只要27行程序的F题~~

---

## 作者：wosile (赞：1)

这题在 Div.2 的 F 中算比较简单的。

----
题意比较简单，略过。

我们发现答案只与 $A,B$ 是否相同有关，也就是只与 $A_i-B_i$ 有关
。所以我们定义 $C_i=A_i-B_i$。

如果这题的操作是给一个区间加上相同的数，只需要简单的维护差分就可以了。定义 $D_i=C_i-C_{i-1}(D_1=C_1)$，则每次对于 $[l,r]$ 的操作只需要改变 $D_l$ 和 $D_{r+1}$。$C_i$ 全为 $0$ 当且仅当 $D_i$ 全为 $0$。

现在，操作变成了给一个区间加上一段斐波那契数列，我们还是要找到一个与 $C$ 有关的数列 $D$，使得每次操作只改变少数几个 $D_i$ 的值。

因为 $F_i=F_{i-1}+F_{i-2}$，所以我们定义 $D_i=C_i-C_{i-1}-C_{i-2}(D_2=C_2-C_1, D_1=C_1)$。对区间 $[l,r]$ 操作的时候，对于 $l+1\leq i\leq r$，$D_i$ 的值都无需改变。只有 $D_l,D_{r+1},D_{r+2}$ 的值会受到影响，其他都抵消了。

同样的，$C_i$ 全为 $0$ 当且仅当 $D_i$ 全为 $0$。

时间复杂度：$O(n+q)$

空间复杂度：$O(n)$

----
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int mod,n,q,zs;
int a[300005],b[300005],c[300005],d[300005],f[300005];
void add(int x,int val){
	if(val==0 || x>n)return;
	if(d[x]==0)zs--;
	d[x]=((d[x]+val)%mod+mod)%mod;
	if(d[x]==0)zs++;
}
int main(){
	scanf("%d%d%d",&n,&q,&mod);
	f[1]=f[2]=1;
	for(int i=3;i<=n+1;i++)f[i]=(f[i-1]+f[i-2])%mod;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)c[i]=(a[i]-b[i]+mod)%mod;
	for(int i=1;i<=n;i++){
		if(i==1)d[i]=c[i];
		else d[i]=((c[i]-c[i-1]-c[i-2])%mod+mod)%mod;
	}
	for(int i=1;i<=n;i++)zs+=(d[i]==0?1:0);
	while(q--){
		char c[2];
		int l,r;
		scanf("%s%d%d",c,&l,&r);
		if(c[0]=='A'){
			add(l,1);
			add(r+1,-f[r-l+2]);
			add(r+2,-f[r-l+1]);
		}
		else{
			add(l,-1);
			add(r+1,f[r-l+2]);
			add(r+2,f[r-l+1]);
		}
		if(zs==n)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：给定两个序列 $a,b$，每次将其中一个序列的一个区间进行一次“加”操作，求进行 $1\sim q$ 次操作后两序列是否相等。

核心思想：差分

解：
问题容易转化为求序列 $c_i=a_i-b_i$ 经过 $q$ 次操作后是否全为 $0$。考虑如何降低总复杂度：注意到 $\forall\:l\le c_i,c_{i+1},c_{i+2}\le r$，操作前后 $c_{i+2}-c_{i-1}-c_{i}$ 不变。定义 $d_1=c_1,d_2=c_2$ 且对于其余项有 $d_i=c_i-c_{i-1}-c_{i-2}$。则对于每一项操作，$d_l$ 会增加 $1$，$d_{r+1}$ 会减少 $F_{r-l}+F_{r-l+1}=F_{r-l+2}$，$d_{r+2}$ 会增加 $F{r-l+1}$。每次操作后统计 $d_i$ 是否全 $0$ 即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long n, q, m, l, r, a[300001], b[300001], d[300001], f[300002], cnt, t;
char c;
inline long long read()
{
	long long t=0;
	char ch=getchar();
	while(ch>='0' && ch<='9')
	{
		t=10*t+ch-48;
		ch=getchar();
	}
	return t;
}
int main()
{
	n=read();
	q=read();
	m=read();
	f[1]=1;
	for(int i=2; i<=n+1; i++)
		f[i]=(f[i-1]+f[i-2])%m;//预处理
	for(int i=1; i<=n; i++)
		a[i]=read();
	for(int i=1; i<=n; i++)
		b[i]=read();
	for(int i=1; i<=n; i++)
		d[i]=(a[i]-b[i]+m)%m;//构造d
	for(int i=n; i>=3; i--)
	{
		d[i]=(d[i]-d[i-1]-d[i-2]+m+m)%m;
		if(d[i]==0)
			cnt++;
	}
	d[2]=(d[2]-d[1]+m)%m;
	if(d[2]==0)
		cnt++;
	if(d[1]==0)
		cnt++;
	for(int i=1; i<=q; i++)
	{
//		for(int j=1; j<=n; j++)
//			cout<<d[j]<<" ";
//		cout<<endl;
		c=getchar();
		t=getchar();
		l=read();
		r=read();
		if(d[l]==0)
			cnt--;
		if(d[r+2]==0)
			cnt--;
		if(d[r+1]==0)
			cnt--;
//		cout<<c<<" "<<l<<" "<<r<<endl;
		if(c=='A')
		{
			d[l]=(d[l]+1)%m;
			if(r+1<=n)
				d[r+1]=(d[r+1]-f[r-l+2]+m)%m;
			if(r+2<=n)
				d[r+2]=(d[r+2]-f[r-l+1]+m)%m;
		}
		else
		{
			d[l]=(d[l]-1+m)%m;
			if(r+1<=n)
				d[r+1]=(d[r+1]+f[r-l+2])%m;
			if(r+2<=n)
				d[r+2]=(d[r+2]+f[r-l+1])%m;
		}//操作
		if(d[l]==0)
			cnt++;
		if(d[r+2]==0)
			cnt++;
		if(d[r+1]==0)
			cnt++;//统计是否全0
//		cout<<cnt<<" ";
		if(cnt==n)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}

```

---

## 作者：mango09 (赞：0)

[F. Fibonacci Additions](https://codeforces.com/problemset/problem/1634/F)

维护 $A$ 和 $B$ 的差数组 $D$，$D_i = 0$ 意味着 $A_i = B_i$，所以问题转化为求 $D$ 中是否全为 $0$。

动态统计 $D$ 中元素 $0$ 的个数。用线段树是不好统计的，我们可以使用差分。

根据斐波那契数列的特点 $f_n = f_{n - 1} + f_{n - 2}$，令差分数组 $c_n = D_n - D_{n - 1} - D_{n - 2}$，这样在对 $D$ 区间加或减斐波那契数列时，只有 $c_l, c_{r + 1}, c_{r + 2}$ 会发生变化，变化量也是非常好算的，不在正文中赘述。

观察到只有当 $c$ 中全为 $0$ 时，$D$ 中才能全为 $0$，于是只需要暴力维护 $c$ 中 $0$ 的个数 $cnt$，询问时判断 $cnt$ 是否等于 $n$ 即可。

[Code](https://codeforces.com/contest/1634/submission/170557603)

---

