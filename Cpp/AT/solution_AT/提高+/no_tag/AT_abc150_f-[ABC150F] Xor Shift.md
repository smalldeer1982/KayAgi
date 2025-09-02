# [ABC150F] Xor Shift

## 题目描述

给定两个长度为 $n$ 的序列 $a=\{a_0,a_1,\cdots,a_{n-1}\}$ 和 $b=\{b_0,b_1,\cdots,b_{n-1}\}$，输出所有有序数对 $(k,x)$ ，满足：  
1. $0\leq k<n$ 且 $x\geq 0$。
2. 序列 $a'=b$，其中 $a'_i = a_{i+k\bmod n}\operatorname{xor} x\ (0\leq i<n)$，“$\operatorname{xor}$”表示按位异或。

## 说明/提示

$1\leq n\leq 2\times 10^5$，$0\leq a_i,b_i<2^{30}$。

## 样例 #1

### 输入

```
3
0 2 1
1 2 3```

### 输出

```
1 3```

## 样例 #2

### 输入

```
5
0 0 0 0 0
2 2 2 2 2```

### 输出

```
0 2
1 2
2 2
3 2
4 2```

## 样例 #3

### 输入

```
6
0 1 3 7 6 4
1 5 4 6 2 3```

### 输出

```
2 2
5 5```

## 样例 #4

### 输入

```
2
1 2
0 0```

### 输出

```
```

# 题解

## 作者：World_Creater (赞：4)

先考虑 $k=0$ 时怎么做。

考虑对原序列进行“差分”（即取相邻两个数的异或值），我们得到两个新的序列 $a1,b1$。

思考序列 $a1$ 的性质：我们发现，将序列 $a$ 整体异或上一个数，序列 $a1$ 始终不变！

因此当 $k=0$ 时，有解的情况**当且仅当**序列 $a1$ 和 $b1$ 是相同的，此时我们取的 $x$ 为 $a_0\operatorname{xor} b_0$。

推广到 $0\leq k<n$ 的情况。

考虑倍长 $a$ 数组，断环成链，继续取 $a1$ 为序列 $a$ 相邻两个数的异或值，取 $b1$ 为序列 $b$ 相邻两个数的异或值。如果存在一个 $i$ 使得 $k=i$ 有解，**当且仅当** $b1$ 是 $a1$ 从下标 $i$ 开始的一段**连续子串**，同样的，此时我们取的 $x$ 为 $a_i\operatorname{xor} b_0$。

那么问题就变成了一个字符串匹配问题，普通 $\rm KMP$ 匹配即可。

代码（注意代码里的下标从 $1$ 开始）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[400005],a1[400005],b[400005],b1[400005],kmp[400005];
vector<int> ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<2*n;i++)
	{
		a1[i]=a[i]^a[i+1];
		b1[i]=b[i]^b[i+1];
	}
	int j=0;
	b1[n]=-2;
	for(int i=2;i<n;i++)
	{
		while(j&&b1[i]!=b1[j+1]) j=kmp[j],cerr<<j<<"\n";
		if(b1[i]==b1[j+1]) j++;
		kmp[i]=j;
	}
	j=0;
	a1[2*n]=-1;
	for(int i=1;i<2*n;i++)
	{
		while(j&&b1[j+1]!=a1[i]) j=kmp[j];
		if(b1[j+1]==a1[i]) j++;
		if(j==n-1) ans.emplace_back(i-j+1);
	}
	for(auto i:ans)
	{
		if(i==n+1) break;
		cout<<i-1<<" "<<(a[i]^b[1])<<"\n";
	}
}
```

---

## 作者：Fairicle (赞：3)

由异或的性质可以得到 $x=a_{(k+i)\%n}\  \text{xor} \ b_i$

如果满足条件那么必然有 $a_{k\% n}\  \text{xor} \ b_0=a_{(k+1)\% n}\  \text{xor} \ b_1=...=a_{(k+n-1)\% n}\  \text{xor} \ b_{n-1}$

也就是 $a_{k\% n}\  \text{xor} \ a_{(k+1)\% n}=b_0\  \text{xor} \ b_1...$

于是记 $c_i=a_{i\%n}\  \text{xor} \ a_{(i+1)\% n},d_i=b_i\  \text{xor} \ b_{i+1}$

若对于一个 $k$ 有 $∀ i\in[0,n-1],c_{(i+k)\% n}=d_i$，则这个 $k$ 是合法答案，并且 $x=a_k\ \text{xor}\ b_0$。

问题转化为对于一个 $k$ 如果 $c[k...k+n-1]$ 与 $d[0...n-1]$ 相匹配，则 $k$ 可行。那么这里可以使用哈希算法。

首先将 $c,d$ 离散化，映射到 $4e5$ 级别的数，随后选取一个大于 $4e5$ 的整数作为 $bas$，再选取一个较大质数作为模数。

我的 $bas=1333331,mod=1000000000091$。

code：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
#define pb push_back
#define mp make_pair
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 200010
#define mod 1000000000091
int n,a[N],b[N],buc[N<<1],top;
ll c[N<<1],d[N];
ll bas=1333331;
inline int lowbit(int x){return x & ( - x ) ;}
int main()
{
	n=rd();
	for(ri i=0;i<n;++i) a[i]=rd();a[n]=a[0];
	for(ri i=0;i<n;++i) b[i]=rd();b[n]=b[0];
	for(ri i=0;i<n;++i) c[i]=a[i]^a[i+1],buc[++top]=c[i];
	for(ri i=0;i<n;++i) d[i]=b[i]^b[i+1],buc[++top]=d[i];
	sort(buc+1,buc+1+top);
	int len=unique(buc+1,buc+1+top)-buc-1;
	for(ri i=n;i<2*n;++i) c[i]=c[i-n];
	for(ri i=0;i<2*n;++i) c[i]=lower_bound(buc+1,buc+1+len,c[i])-buc;
	for(ri i=0;i<n;++i) d[i]=lower_bound(buc+1,buc+1+len,d[i])-buc;
	//for(ri i=0;i<2*n;++i) cout<<c[i]<<" ";cout<<endl;
	//for(ri i=0;i<n;++i) cout<<d[i]<<" ";cout<<endl;
	ll sta=0;
	int ans=0;
	for(ri i=0;i<n;++i) sta=(sta*bas+d[i])%mod;//cout<<sta<<endl;
	ll tmp=1,now=0;for(ri j=1;j<n;++j) tmp=tmp*bas%mod;
	for(ri i=0;i<n;++i) {now=(now*bas+c[i])%mod;if(now==sta) cout<<0<<" "<<(a[0]^b[0])<<endl;}
	for(ri i=n;i<2*n-1;++i) {now=((now-(c[i-n]*tmp%mod)+mod)*bas+c[i])%mod;if(now==sta) cout<<i+1-n<<" "<<(a[i+1-n]^b[0])<<endl;}
    return 0;
}

```


---

## 作者：_edge_ (赞：2)

来这里介绍乱搞做法。

我不会字符串呀，我不会 Z 函数呀，但是我会暴力！！！！

我们可以把 $k$ 视为向右循环位移 $k$ 位。

那么我们可以把 $a$ 数组复制一份，然后寻找他的头，进行匹配。

那么怎么匹配才比较优秀呢？

这个时候会有各种各样神奇的做法，但是我喜欢乱搞。

于是我们把头后面的 $1000$ 位给取出来，尾巴前面的 $1000$ 位给拿出来，然后暴力求一下异或值，这样对的概率非常的高，只有一个点 WA 了。

考虑优化这个过程，我们想寻找的就是一串子串异或某个 $x$ 之后和另一段子串的差别，这种可以直接上异或前缀和。

具体的我们可以变成 $a_l \oplus a_{l+1} \oplus a_{l+2} \oplus \cdots \oplus a_r=b_1 \oplus x \oplus b_2 \oplus x \oplus \cdots \oplus b_n$，然后这东西异或前缀和一下就可以了！

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=5e5+5;
int a[INF],b[INF],n,sum1[INF],sum[INF];
signed main()
{
	srand(time(0));
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=n+1;i<=n*2;i++) a[i]=a[i-n];
	for (int i=1;i<=n;i++) cin>>b[i];
	
	for (int i=1;i<=n*2;i++) sum[i]=sum[i-1]^a[i];
	for (int i=1;i<=n;i++) sum1[i]=sum1[i-1]^b[i];
	
	for (int l=1;l<=n;l++) {
		int fl=0,la=-1;
		for (int r=l;r<=min(l+n-1,l+1);r++) {
			if (la==-1) la=b[r-l+1]^a[r];
			else if (la!=(b[r-l+1]^a[r])) fl=1;
			if (fl) break;
		}
		
//		cout<<(la^sum1[n])<<" "<<(sum[l+n-1]^sum[l-1])<<" fad?\n"; 
		int K=la;
		if (n&1) ;
		else K=0;
		if ((K^sum1[n])!=(sum[l+n-1]^sum[l-1])) continue;
		
		for (int r=l+n-1;r>=max(l+n-1-1,l);r--) {
			if (la==-1) la=b[r-l+1]^a[r];
			else if (la!=(b[r-l+1]^a[r])) fl=1;
			if (fl) break;
		}
		
		if ((K^sum1[n])!=(sum[l+n-1]^sum[l-1])) continue;
		for (int T=1;T<=1;T++) {
			int r=rand()%n+l;
			if (la==-1) la=b[r-l+1]^a[r];
			else if (la!=(b[r-l+1]^a[r])) fl=1;
			if (fl) break;
		}
		if ((K^sum1[n])!=(sum[l+n-1]^sum[l-1])) continue;
		if (!fl) cout<<l-1<<" "<<la<<"\n";
	}
	return 0;
}
```


---

## 作者：Rushroom (赞：2)

稍微有一点点改动的 **Z 函数**。

（KMP 应该也可以做，但是个人感觉 Z 函数好理解。

## 做法

### 前置芝士

[Z 函数](https://oi-wiki.org/string/z-func/)

### 思路

看到 **Shift**，首先想到把 $a$ 复制一遍。

总所周知，做 Z 函数时，需要把文本串和匹配串拼在一起，中间加一个奇怪的字符，所以，我们拼成了这样一个串：

$b+(-1)+a+a$（ $+$ 表示拼接）

在这个题目中，是否也满足 Z 函数的性质呢？

我们再回顾一遍 Z 函数的扩展过程。

如果已知：对于任何 $l \le i \le r$，$a_i \oplus b_i=x$。

- 扩展到 $i=r+1$：如果 $a_{r+1} \oplus b_{r+1}$，那么显然，$z_i$ 可以 $+1$。

- 扩展到 $j(j\le r)$：同理，也是可以拓展的。不懂得左转[这里](https://oi-wiki.org/string/z-func/#_3)。

所以，这道题里 $XOR$ 的性质是完全满足 Z 函数的。 

然后就可以愉快地跑一遍 Z 函数了。

### Code

```cpp
/*
 * @Description: I want to be the weakest vegetable in the world!
 * @Author: CGBoy
 * @Date: 2022-03-06 09:52:33
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T_, case_;
int n, a[200005], b[200005], s[700005];
int z[700005];
void Z() {
    int l = 0, r = -1;
    int siz = n + n + n + 1;
    forr(i, 1, siz - 1) {
        if (i <= r) {
            if (i + z[i - l] - 1 < r)z[i] = z[i - l];
            else {
                z[i] = r - i + 1;
                while (i + z[i] < siz && (s[i + z[i]] ^ s[z[i]]) == (s[i + z[i] - 1] ^ s[z[i] - 1]))z[i]++;
            }
        }
        else {
            z[i] = 1;
            while (i + z[i] < siz && (s[i + z[i]] ^ s[z[i]]) == (s[i + z[i] - 1] ^ s[z[i] - 1]))z[i]++;
        }
        if (i + z[i] - 1 > r)l = i, r = i + z[i] - 1;
    }
}
void solve() {
    cin >> n;
    rep(i, n)cin >> a[i];
    rep(i, n)cin >> b[i];
    rep(i, n)s[i] = b[i];
    s[n] = -1;
    rep(i, n)s[n + 1 + i] = s[n + n + 1 + i] = a[i];
    Z();
    forr(i, n + 1, n + n) {
        if (z[i] == n) {
            cout << i - n - 1 << ' ' << (a[i - n - 1] ^ b[0]) << endl;
        }
    }
}
int main() {
    T_ = 1;

    for (case_ = 1;case_ <= T_;case_++)solve();
    return 0;
}
```


---

## 作者：mcqueen (赞：1)

首先是一个很显然的观察：

如果$b_i=a_{(i+k)\bmod n}\ \text{xor}\ x$，那么$a_{(i+k)\bmod n}\ \text{xor}\ b_i=x$。

所以，如果两个序列对应的每一位的异或值都相等，那么它就符合题意。

现在我们考虑如何判断两个序列每一位的异或值都相等。

因为这个$a_{(i+k)\bmod n}$就相当于把$a$序列“轮换”着变化，所以考虑序列上相邻两位的某种关系是否能快速判断两个序列的每一位的异或值都相等。

思考一下，当我们把$a_i$变成$a_{(i+1)\bmod n}$时，对应的$b_i$要怎么样变才能使得它与$a_{(i+1)\bmod n}$的异或值等于$a_i$与$b_i$的异或值？

当$a_i$变成$a_{(i+1)\bmod n}$时，如果$a_i$的某一个二进制位改变了，那么$b_i$的这个二进制位也要改变。

举个例子：若$a_1=3,a_2=5$，他们对应的二进制表示分别为：$011$，$101$。在$a_1$变为$a_2$的过程中，第$1$位，第$2$位（从第$0$位开始数）二进制位改变了。

那如果$b_1=1$，那么$b_1$将要变成的$b_2$就是$b_1$的二进制位中的第$1$位，第$2$位改变的结果，那么$(b_1)_2=001\rightarrow(b_2)_2=111$，$b_2$必须为$7$。

$a_1$变为$a_2$，$b_1$变为$b_2$所需要变的二进制位是对应相同的，其实就意味着，$a_1\ \text{xor}\ a_2=b_1\ \text{xor}\  b_2$。

于是我们有$a_1\ \text{xor}\ a_2=b_1\ \text{xor}\ b_2\Rightarrow a_1\ \text{xor}\ b_1=a_2\ \text{xor}\ b_2$。

上面那个式子用异或的性质也可以显然得到。

而如果对应多个数，根据等式的传递性，我们显然可以推广得：

$$
\forall i\in[0,n-1],a_i\ \text{xor} \ a_{(i+1)\bmod n}=b_i\ \text{xor} \ b_{(i+1)\bmod n}\Rightarrow a_1\ \text{xor}\ b_1=a_2\ \text{xor}\ b_2=...=a_{n-1}\ \text{xor}\ b_{n-1}
$$

那么我们可以记$c_i=a_i\ \text{xor}\ a_{(i+1)\bmod n},d_i=b_i\ \text{xor}\ b_{(i+1)\bmod n}$。

然后如果存在某个$k,0\le k <n $，使得$c_{(i+k)\bmod n}=d_i$，那么这个$k$就是合法的。如何快速的求解呢？

这玩意其实就比较套路了。首先$c_{(i+k)\bmod n}$这种有点像环的东西把它复制一下就行了。然后把$d$序列放前面，复制之后的$c$放后面，跑一下 Z 算法（扩展 KMP ）。然后通过 lcp 是否等于$n$来判断对应的$k$是否可以就行了。

没有学过 Z 算法可以去[OI-wiki](https://oi-wiki.org/string/z-func/)，或者[我的博文](https://www.luogu.com.cn/blog/mcqueen/z-algorithm)。个人建议初学者去看 OI-wiki 上的，OI-wiki 写的比较详细，我的写的相对简略一点。（不过我的博客里有我在CF上看到的并整理下来的比较优美的 Z 算法的写法，值得学习）。

**题外话：**
当然这玩意应该也可以直接 KMP ~~（但其实我不会（是的没错我不会 KMP 但我会扩展 KMP ））~~，应该也可以哈希，~~（但我**个人**总感觉这种不是真正的字符串匹配可能会被卡（不过我好像看到有人用单哈希过了），而且Z算法比起哈希来码量小不少）（这不是说我不喜欢哈希，哈希大发好）~~。

**code：**
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
template<typename T>
inline void in(T &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
int n,A[N],B[N],a[N],b[N],Z[N*3],s[N*3];
void calc_z(int n)
{
	Z[0]=n;
	int l=0,r=0;
	for(int i=1;i<n;++i)
	{
		if(i>r)l=r=i;
		Z[i]=min(r-i,Z[i-l]);
		while(s[Z[i]]==s[i+Z[i]])++Z[i];
		if(i+Z[i]>r)r=i+Z[i],l=i;
	}
}
int main()
{
	in(n);
	for(int i=0;i<n;++i)in(A[i]);
	for(int i=0;i<n;++i)in(B[i]);
	for(int i=0;i<n;++i)
	a[i]=(A[i]^A[(i+1)%n]),b[i]=B[i]^B[(i+1)%n];
	for(int i=0;i<n;++i)
	s[i]=b[i];
	s[n]=-1;
	for(int i=n+1;i-n-1<n;++i)
	s[i]=a[i-n-1];
	for(int i=n+n+1;i-n-n-1<n;++i)
	s[i]=a[i-n-n-1];
	calc_z(n+n+n+1);
	for(int i=n+1;i-n-1<n;++i)
	if(Z[i]==n)
		printf("%d %d\n",i-n-1,A[i-n-1]^B[0]);
	return 0;
}
```




---

## 作者：ix35 (赞：1)

好题！

首先是按位确定，令 $t(i,j)$ 表示 $A$ 序列向右移动 $j$ 位后异或某一个数能否等于 $B$ 序列，则如果所有 $t(i,q)\ \ (i\in [1,30])$ 都是 $1$，移动 $q$ 位才是一个可行的答案。

然后就将原问题转化成了一个全是 $0,1$ 的问题，这样异或处理起来就简单得多，异或一下就相当于是全体取反，所以设 $cntA,cntB$ 分别是 $A,B$ 中 $1$ 的个数，如果 $cntA=cntB$，那么可以不异或任何数，如果恰好 $cntA+cntB=n$，那么可以 $A$ 序列全部取反再与 $B$ 匹配。

然后就是一个普通的字符串匹配问题，将 $A$ 做循环位移使得和 $B$ 完全相等，我们只需要将 $B$ 复制两倍（或者复制 $A$ 也是一样的），做一次 KMP 即可提取出所有匹配位置，于是 $t(i,j)$ 就计算出来了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m,a[2*MAXN],b[MAXN],c[2*MAXN],d[MAXN],nx[MAXN],bl[MAXN],ans[MAXN];
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {scanf("%d",&a[i]);}
	for (int i=1;i<=n;i++) {scanf("%d",&b[i]);}
	for (int i=n+1;i<=n+n;i++) {a[i]=a[i-n];}
	m=n;
	n=m+m; 
	for (int ii=0;ii<30;ii++) {
		memset(bl,0,sizeof(bl));
		int tmp1=0,tmp2=0,flg=0;
		for (int j=1;j<=n;j++) {c[j]=((a[j]>>ii)&1);tmp1+=c[j]*(j<=m);}
		for (int j=1;j<=m;j++) {d[j]=((b[j]>>ii)&1);tmp2+=d[j];}
		if (tmp1==tmp2) {
			nx[1]=0;
		    for (int i=2,j=0;i<=m;i++) {
    		    while (j>0&&d[i]!=d[j+1]) {j=nx[j];}
        		if (d[i]==d[j+1]) {j++;}
        		nx[i]=j;
    		}
    		for (int i=1,j=0;i<=n;i++) {
	        	if (j==m) {j=nx[j];}
		        while (j>0&&c[i]!=d[j+1]) {j=nx[j];}
    		    if (c[i]==d[j+1]) {j++;}
        		if (i>=m&&j!=m) {bl[i-m]++;}
    		}
    		flg=1;
		}
		if (m-tmp1==tmp2) {
			for (int j=1;j<=m;j++) {d[j]^=1;}
			nx[1]=0;
		    for (int i=2,j=0;i<=m;i++) {
    		    while (j>0&&d[i]!=d[j+1]) {j=nx[j];}
        		if (d[i]==d[j+1]) {j++;}
        		nx[i]=j;
    		}
    		for (int i=1,j=0;i<=n;i++) {
	        	if (j==m) {j=nx[j];}
		        while (j>0&&c[i]!=d[j+1]) {j=nx[j];}
    		    if (c[i]==d[j+1]) {j++;}
        		if (i>=m&&j!=m) {bl[i-m]++;}
    		}
    		flg=1;
		}
		if (!flg) {
			return 0;
		}
		if (tmp1==tmp2&&m-tmp1==tmp2) {
			for (int j=0;j<=m;j++) {
				if (bl[j]==2) {ans[j]=1;}
			}
		} else {
			for (int j=0;j<=m;j++) {
				if (bl[j]==1) {ans[j]=1;}
			}
		}
	}
	for (int i=0;i<m;i++) {
		if (!ans[i]) {printf("%d %d\n",i,a[i+1]^b[1]);}
	}
	return 0;
}
```


---

## 作者：lilong (赞：0)

读题可以发现一个事实，即如果已求得一个合法的 $k$，则 $x$ 也唯一确定了。因为 $a_{(i+k)\bmod n} \operatorname{xor}x=b_i$，根据异或的可逆性可得 $x=a_{(i+k)\bmod n} \operatorname{xor} b_i$。那么问题转化为判断每个 $0\le k <n$ 是否合法。

不难想到暴力的做法，每次令 $x=a_k \operatorname{xor}b_0(0\le k <n)$，判断其它位置是否相等，时间复杂度 $O(n^2)$，不够优秀，瓶颈在于判断是否相等这个过程。考虑异或的本质是二进制的运算，且在某一二进制位上 $a_i$ **要么全部不变**，**要么全部取反**（取决于 $x$ 二进制在该位上的数值）。又由于不同的 $x$ 可能在某些二进制位上相同，因此每次都重新判断会出现大量冗余。

我们换个角度考虑，枚举 $x$ 二进制下的每一位，并令该位分别等于 $0$ 和 $1$，保留 $a_i$ 当前位和 $x$ 当前位的异或值，同时令 $b'$ 为 $b$ 二进制当前位的值。这样做，相当于 $a'$ 在当前位确定下来了，直接枚举 $k$ 判断和 $b'$ 是否相等即可，用 Hash 即可做到 $O(n)$。如果某一位的 $x$ 为 $0$ 或 $1$ 时均不合法，则对应 $k$ 不合法，否则合法。

总时间复杂度 $O(n\log A)$，其中 $A$ 为值域上限。


```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define MOD 998244853
#define base 233

using namespace std;

int n,A[1000001],B[1000001],a[1000001],b[1000001],c[1000001],d[1000001],sum[1000001],p[1000001],ha[1000001],hb[1000001],f[1000001],vis1[1000001],vis2[1000001];

int h1( int l , int r )
{
	if( l > r ) return 0;
	return ( ( ha[r] - ha[l - 1] * p[r - l + 1] % MOD ) % MOD + MOD ) % MOD;
} 

int h2( int l , int r )
{
	if( l > r ) return 0;
	return ( ( hb[r] - hb[l - 1] * p[r - l + 1] % MOD ) % MOD + MOD ) % MOD;
} 

void js1( )
{
	for( int i = 1 ; i <= n ; i ++ )
	{
		ha[i] = ( ha[i - 1] * base % MOD + c[i] ) % MOD;
		hb[i] = ( hb[i - 1] * base % MOD + d[i] ) % MOD;
	}
	int l1,r1,l2,r2;
	for( int i = 0 ; i < n ; i ++ )
	{
		l2 = 1,r2 = n - i;
		l1 = l2 + i,r1 = n;
//		cout << i << ' ' << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
		if( h1( l1 , r1 ) != h2( l2 , r2 ) ) continue;
		l2 = r2 + 1,r2 = n;
		r1 = l1 - 1,l1 = 1;
//		cout << i << ' ' << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
		if( h1( l1 , r1 ) != h2( l2 , r2 ) ) continue;
		vis1[i] = 1;
	}
	return;
}

void js2( )
{
	for( int i = 1 ; i <= n ; i ++ )
	{
		c[i] ^= 1;
		ha[i] = ( ha[i - 1] * base % MOD + c[i] ) % MOD;
		hb[i] = ( hb[i - 1] * base % MOD + d[i] ) % MOD;
	}
	int l1,r1,l2,r2;
	for( int i = 0 ; i < n ; i ++ )
	{
		l2 = 1,r2 = n - i;
		l1 = l2 + i,r1 = n;
//		cout << i << ' ' << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
		if( h1( l1 , r1 ) != h2( l2 , r2 ) ) continue;
		l2 = r2 + 1,r2 = n;
		r1 = l1 - 1,l1 = 1;
//		cout << i << ' ' << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
		if( h1( l1 , r1 ) != h2( l2 , r2 ) ) continue;
		vis2[i] = 1;
	}
	return;
}

signed main()
{
	cin >> n;
	p[0] = 1;
	f[0] = 1;
	for( int i = 1 ; i <= n ; i ++ )
		p[i] = p[i - 1] * base % MOD,f[i] = 1;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i],A[i] = a[i];
	for( int i = 1 ; i <= n ; i ++ )	
		cin >> b[i],B[i] = b[i];
	for( int j = 0 ; j <= 31 ; j ++ )
	{
		vis1[0] = vis2[0];
		for( int i = 1 ; i <= n ; i ++ )	
		{
			c[i] = a[i] % 2;
			d[i] = b[i] % 2;
			vis1[i] = vis2[i] = 0;
		}
		js1();
		js2();
		for( int i = 0 ; i < n ; i ++ )
			if( !vis1[i] && !vis2[i] )
				f[i] = 0;
		for( int i = 1 ; i <= n ; i ++ )
			a[i] /= 2,b[i] /= 2;
	}
	for( int i = 0 ; i < n ; i ++ )
		if( f[i] )
			cout << i << ' ' << ( A[i + 1] ^ B[1] ) << '\n';
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

好题啊。

## 解题思路

以下记 $\operatorname{xor} $ 为 $\oplus$。

注意到当循环移位系数 $k$ 一定时，若有解，则 $x$ 是一定的，即为 $x=a_{k+1} \oplus b_1$，故我们只需要判定某个循环移位是否有解即可。

根据 $\oplus$ 的性质可以得知：若某个循环移位有解，则对于每一个二进制位都有 $a$ 中该二进制位异或 $x$ 的该二进制位的值后左循环移位 $k$ 位之后与 $b$ 相同。

假定我们在这一位不进行异或，考虑这一个问题，我们发现可以用 Hash 做：具体的，计算区间 Hash 值，在循环移位 $k$ 位之后 $a_{1,\cdots,k-1}$ 会对应到 $a'_{n-k+1,\cdots,n}$，以及 $a_{k,\cdots,n}$ 会对应到 $a'_{1,\cdots,n-k}$。考虑使用区间哈希值判断两段是否相等即可。

注意到在非异或的情况下判断是 $O(n)$ 的，异或一边再判也一样，故对于每一位判断异或和非异或的情况总时间复杂度是 $O(n\log n)$ 的。

某一个循环移位有解，当且仅当其每一位都有解，若有解则 $x=a_{k+1} \oplus b_1$，输出即可。

---

