# AND, OR and square sum

## 题目描述

### 题面描述

给定 $n$ 个非负整数 $a_1,\cdots,a_n$。

你可以进行如下操作：选择两个不同的下标 $i,j$ 满足 $1\leq i,j\leq n$，并将 $a_i\gets a_i\ \mathsf{AND}\ a_j,\ a_j\gets a_i\ \mathsf{OR}\ a_j$，**两个赋值同时进行**。AND 是按位与，OR 是按位或。

你可以进行任意次操作。求操作后所有数的平方和的最大值，即 $\max \sum a_i^2$。

## 样例 #1

### 输入

```
1
123```

### 输出

```
15129```

## 样例 #2

### 输入

```
3
1 3 5```

### 输出

```
51```

## 样例 #3

### 输入

```
2
349525 699050```

### 输出

```
1099509530625```

# 题解

## 作者：Alex_Wei (赞：15)

> [题面传送门](https://www.luogu.com.cn/problem/CF1368D)。

> 题意简述：给定 $n$ 个非负整数 $a_1,\cdots,a_n$，每次操作中你可以选择一对 $i,j\ (i\neq j)$ 并将 $a_i\gets a_i\ \mathsf{AND}\ a_j,\ a_j\gets a_i\ \mathsf{OR}\ a_j$，**两个赋值同时进行**。你可以进行任意次操作。求操作后所有数的平方和的最大值，即 $\max \sum a_i$。

前置知识：位运算中的 AND（按位与）和 OR（按位或）。

一道有趣的贪心题。

---

熟悉位运算的同学应该能够一眼看出来 $x\ \mathsf{OR}\ y=x+y-(x\ \mathsf{AND}\ y)$。

也就是说，**每次操作并不改变 $a_i$ 与 $a_j$ 的和**。

所以我们应当让序列 $a$ 中大的尽量大，小的尽量小（感性理解一下）。

更进一步地分析，不难发现**在二进制下，每次操作不改变序列 $a$ 中每一位上 $1$ 的个数。**

这一点很好证明：

- 当 $a_i$ 第 $k$ 位和 $a_j$ 第 $k$ 位相同时，AND 和 OR 运算并不会改变它们第 $k$ 位上的值。

- 当 $a_i$ 第 $k$ 位和 $a_j$ 第 $k$ 位不同时，它们的按位与的第 $k$ 位为 $0$，按位或的第 $k$ 位为 $1$，也是不同的。

有了上面这个结论，我们统计出序列 $a$ 的第 $k$ 位上有多少个 $1$，再尽可能地贪心，构造出大的数，使得平方和最大。

如果还是不理解可以看代码：

```cpp
ll n,ans,buc[20]; // 记得开 long long 

int main(){
	cin>>n;
	for(int i=1,a;i<=n;i++)
		{cin>>a; for(int j=0;j<20;j++)buc[j]+=(a>>j)&1;}// 统计第 j 位上有多少个 1 
	for(ll i=1,tmp=0;i<=n;i++,ans+=tmp*tmp,tmp=0)
		for(int j=0;j<20;j++)if(buc[j])buc[j]--,tmp+=1<<j;// 每一位有剩下的 1 就选上 
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：xiaolilsq (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1368D)

## 题意简述

给定大小为 $n$ 的序列 $a$ ，定义一次操作为选择两个数 $i,j\in[1,n]$ ，设执行操作前 $a_i=x,a_j=y$ ，那么执行操作后 $a_i=x \operatorname{and} y,a_j=x \operatorname{or} y$ ，执行**若干次操作**后， $\sum_{i=1}^na_i^2$ 最大能为多少。

## 题目分析

其实给定序列是没有必要的，不妨将其描述成一个可重集，因为我们并不关心一个数的下标。

两个数 $x,y$ 在进行操作后变成了 $x \operatorname{and} y,x \operatorname{or} y$ ，容斥显然有 $x+y=(x \operatorname{and} y)+(x \operatorname{or} y)$ ，不妨设 $x \operatorname{or} y = y+z$ ，那么操作后的两个数就是 $x-z,y+z$ ，操作前后的变化量就是 $[(x-z)^2+(y+z)^2]-(x^2+y^2)=2z(z+y-x)=2[(x \operatorname{or} y)-y][(x \operatorname{or} y)-x]$ ，又 $(x \operatorname{or} y)-y\ge 0,(x \operatorname{or} y)-x\ge 0$ ，每次执行操作后**答案都不会更劣**。

既然如此，我们肯定会**尽可能多地执行操作直到答案没有变化为止**。

何时答案将不会改变？ $(x \operatorname{or} y)-y=0$ 或者 $(x \operatorname{or} y)-x=0$ 时，即 **$x$ 转化成二进制后所有位都被 $y$ 包含或者 $y$ 转化成二进制后所有位都被 $x$ 包含**时。

我们将会一直执行操作直到满足上述粗体字要求为止，那么不妨把所有二进制位的出现次数记录下来，包含所有二进制位的数的最终个数肯定是所有出现次数中的最小值，包含除出现次数最小的那位外的所有二进制位的数的最终个数肯定是所有出现次数中的次小值……，由此我们便得到了解决这题的方法。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
struct Node{
	int val,id;
	Node(int val=0,int id=0):
		val(val),id(id){}
	bool operator < (const Node o)const{
		return val>o.val;
	}
}sm[20];
int main(){
	int n;read(n);
	while(n--){
		int a,cn=0;read(a);
		while(a){
			sm[cn].val+=a&1;
			a>>=1;++cn;
		}
	}
	for(int i=0;i<20;++i)
		sm[i].id=i;
	sort(sm,sm+20);
	long long ans=0;
	for(int i=0,Imakf=0;i<20;++i){
		Imakf|=1<<sm[i].id;
		int nm=sm[i].val;
		if(i!=19)nm-=sm[i+1].val;
		ans+=1ll*Imakf*Imakf*nm;
	}
	write(ans),pc('\n');
	return 0;
}
```

---

## 作者：KellyFrog (赞：2)

众所周知，对于任意$x$和$y$，$x+y=x \space \text{or} \space y+x\space\text{and}\space y$，也就是说，前后操作的总和是不变的。

感性理解下，当$a$中较大的数越大时，$\Sigma a_i ^2$越大。

又因为我们可以操作任意次，为了让大的尽量大，所以我们每次在二进制上取最多的位数，对于答案的贡献一定是最大的。

于是做法就显然了，把所有二进制拆了扔进桶里，每次从取所有不为空的桶计入答案。

code:
```cpp
#include <iostream>

using namespace std;

typedef long long ll;

ll cnt[25], n, ans, x;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> x;
		for(int j = 0; j < 20; j++) {
			cnt[j] += (x >> j) & 1ll;
		}
	}
	for(int i = 1; i <= n; i++) {
		ll cur = 0;
		for(int j = 0; j < 20; j++) {
			if(cnt[j]) {
				cnt[j]--;
				cur += 1ll << j;
			}
		}
		ans += cur * cur;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Exiler (赞：1)

## 原题

[CF1368D AND, OR and square sum](https://www.luogu.com.cn/problem/CF1368D)

---

## 思路概述

### 题意分析

给定一个长度为 $n$ 的数列，对于其中两个数 $a_i,a_j(1≤i,j≤n)$ 每次可以执行操作 $a_i\text{ AND }a_j→a_i,a_i\text{ OR }a_j→a_j$ ，求不限次数的操作后能得到的最大数列平方和。

### 思路分析

首先对这两种运算方式进行分析。与运算等于对二进制下的两数求交集，或运算则等于对二进制下的两数求并集。根据简单的数学常识不难得出 $(a_i\text{ OR }a_j)+(a_i\text{ AND }a_j)=a_i+a_j$ ，也就是说每次操作并不改变两数的和。

一个常识：两个和为定值的正整数，差越大，平方和越大（篇幅原因，笔者不在此处证明）。

由上述内容就可以知道，对于本题的要求，只需要记录所有数各位上 $1$ 的数量，再尽量在数列两端分别构造最大最小的数即得到答案。

---

## 算法实现

### 关于最大（最小）数的构造

首先对输入的每个数进行二进制拆分和记录，可以得到二进制形式下 $0$ 到 $19$ 位的 $1$ 的数量。

对于最大数，尽量将所有位能加入的 $1$ 加上。构造完最大数，剩下的数自然是最小数。

### 注意事项

由于求平方和，而构造出的数 $a_i$ 处于区间 $[0,2^{20})$ ，所以在 `int` 范围内可能会溢出，需要开 `long long` 类型变量。

---

## AC code


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<set>
#include<ctime>
#define ll long long
#define RL register long long
using namespace std;
const ll maxs=30;
ll n,ans;
ll rec[maxs];
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n;
	for(RL i=1,inp;i<=n;++i)
	{
		cin >> inp;
		for(RL j=0;j<20;++j) 
			rec[j]+=((inp>>j)&1);
	}
	for(RL i=1,temp=0;i<=n;++i,temp=0)
	{
		for(RL j=0;j<20;++j) 
			if(rec[j])
			{
				temp+=1<<j;
				--rec[j];
			}
		ans+=temp*temp;
	}
	cout << ans;	
	return 0;
}

```

---

## 作者：hjqhs (赞：0)

简单二进制题，duel 打的第二场。   
二进制题先拆位。  
然后观察性质，$A \texttt{ or } B = A + B-A \texttt{ and } B$。所以总和不变。如果和不变，则显然让大的尽量大，小的尽量小，就可以是总平方和最大。   
所以每次尽量把可以选上的 $1$ 全部选上，然后平方后累加进答案即可。
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define fv(i,p) for(int i=0;i<p.size();++i)
#define all(x) x.begin(),x.end()
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
// #define mp make_pair
// #define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=100005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAx(int a,int b,int c){return Max(a,Max(b,c));}
int MAX(int a,int b,int c,int d){return Max(Max(a,b),Max(c,d));}
int Min(int a,int b){return a<b?a:b;}
int MIn(int a,int b,int c){return Min(a,Min(b,c));}
int MIN(int a,int b,int c,int d){return Min(Min(a,b),Min(c,d));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
void cmin(int&x,int y){if(x>y)x=y;}
void cmax(int&x,int y){if(x<y)x=y;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
  while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
  return x*f;
}
int T=1;
int n,cnt[22],ans;
void solve(){
  cin>>n;
  rep(i,1,n){
    int x;cin>>x;
    rep(j,0,20){
      if((x>>j)&1){
        ++cnt[j];
      }
    }
  }
  rep(i,1,n){
    int tmp=0;
    rep(j,0,20){
      if(cnt[j]){
        --cnt[j];
        tmp+=(1<<j);
      }
    }
    ans+=tmp*tmp;
  }
  cout<<ans;
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  // cin>>T;
  while(T--)solve();
  return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

贪心。

## 思路

首先有一个常用的 trick：$x + y = (x \text{ and } y) + (x \text{ or } y)$。

也就是说，对于 $a_i$ 与 $a_j$ 的一次变化，$(a_i + a_j)$ 始终不变。

于是我们可以直接拆式子了：

$\sum\limits_{i = 1}^n a_i^2 = (\sum\limits_{i=1}^n a_i)^2 + \sum\limits_{i=1}^n\sum\limits_{j=i+1}^n a_ia_j$。

根据上面的 trick，$(\sum\limits_{i=1}^n a_i)^2$ 永远不变。所以只需让 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n a_ia_j$ 最大即可。

继续推论。很显然，如果 $a_i + a_j$ 不变，等价于每一位 $a_{i, k} + a_{j, k}$ 也不变。

和一定，差小积大。对于每一位，只需要把全部数的 $1$ 堆在前面即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/42cj2fqe.png)

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[200005], cnt[25]; //cnt : 每个数位有多少个1
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if (n == 1) {cout << 1ll * a[1] * a[1]; return 0;} //这个特判不加也没事
	
	for (int i = 1; i <= n; i++)
		for (int k = 0; k < 20; k++)
			if (a[i] & (1 << k))
				cnt[k]++; //统计每一位的1个数
	
	memset(a, 0, sizeof a);
	for (int k = 0; k < 20; k++)
		for (int i = 1; i <= cnt[k]; i++)
			a[i] += (1 << k); //把1堆到前面
	
	long long ans = 0;
	for (int i = 1; i <= n; i++) ans += 1ll * a[i] * a[i]; //计算答案
	cout << ans;
	return 0;}
```

---

## 作者：封禁用户 (赞：0)

### 分析

可以发现，$x+y=x$ OR $y + x$ AND $y$。

因为就是把二进制位给移了一下位。

所以转换一下式子 

$\sum_{i=1}^{n} {{a_i}^{2}} = ({\sum_{i=1}^{n}}) ^ 2 - 2 \times \sum_{i=1}^{n} \times \sum_{j=i+1}^{n}$。

想让后式最大，那必须让前后的差值尽量地大，所以我们只需要重新分配二进制位，尽可能分配给前面即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define N 200010
int n,sum[20];
ll ans = 0;
int main()
{
	scanf("%d",&n);
	F(i,1,n) 
	{
		ll x;
		scanf("%lld",&x);
		F(j,0,19) 
		{
			sum[j] += x & 1;
			x >>= 1;	
		}		
	}
	F(i,1,n)
	{
		ll ret = 0;
		F(j,0,19)
			if(sum[j])
			{
				ret += 1<<j;
				--sum[j];	
			}
		ans += ret * ret;
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：亦闻楚歌起 (赞：0)

# 题意

给定$n$个非负整数 $a_1,\dots,a_n$ ，每次操作可以选定任意两个下标不同的非负整数 $a_i,a_j$ ，向序列中加入两个新的数 $a_i\text{ AND } a_j,a_i\text{ OR } a_j$ 并删除原来的两个数。其中 $\text{AND,OR}$ 分别是按位与，按位或操作。

求若干次操作后 $\sum_{i=1}^na_i^2$ 的最大值

# 思路

考虑二进制下任意两个数

$$
\begin{matrix}
a=(1010111)_2&a \text{ AND } b=(0000100)_2 \\
b=(0101100)_2&a \text{ OR }b=(1111111)_2
\end{matrix}
$$

可以发现，对于每次操作，相当于每一位上的$1$都“往下坠”落到了或的结果上。只有两个数那一位上都是$1$的那一位与的结果才会是$1$

~~（感觉在说废话）~~

记 $c=a\text{ AND } b,d=a\text{ OR } b$ ，那么操作一次之后平方和就会增加 $c^2+d^2-a^2-b^2=(d^2-b^2)-(a^2-c^2)=(d+b)(d-b)-(a+c)(a-c)$

观察，发现 $d-b=a-c$。因为 $d$ 拥有 $a,b$ 所有的 $1$ ，减去 $b$ 就剩下仅 $a$ 拥有的 $1$ 。同样 $c$ 拥有 $a,b$ 共有的 $1$ ，用 $a$ 减它就剩下仅 $a$ 拥有的 $1$ 。

因此记 $d-b=a-c=x$，显然或的结果不会小于原数，与的结果不会大于原数，因此 $x\geq 0$

那么平方和增量可以表示为 $(d+b-a-c)x$，只要 $b-a$ 非负那么这次操作就是不亏的。

同样，如果在拆平方和增量的时候我们写成 $(d^2-a^2)-(b^2-c^2)$，并记 $d-a=b-c=y$ 的话，我们可以得到 $y\geq 0$ ，并且平方和增量可以表示为 $(d+a-b-c)y$ 。只要 $a-b$ 非负那么这次操作也不亏。

所以说，每次操作都是不亏的，只要能操作就一直操作好了。

怎么样操作就是无效的呢？比如 $a,b$ 有其中一个是 $0$ 时，操作就没有必要了。或者按位或的结果等于原来某一个数时，无论哪一位上的 $1$ 都不能落下来，所以操作也是无效的。

那么当一个数拥有能拥有的所有的 $1$ 时，他就可以被宣判无效了。这个时候他已经做出了最大贡献。对于 $n$ 个数，都做它的最大贡献，得到的结果就是最大的。

这么说我们可以把 $n$ 个数的二进制位有多少个 $1$ 存下来，然后能取 $1$ 就取，最后得到的总和就是最大的。

期望时间复杂度 $\mathcal O(n\log_2n)$

```cpp
#include <cstdio>

int n,a[21],x;
long long int ans;

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&x);
		for(int j=0;x;++j) {
			a[j]+=x&1;
			x>>=1;
		}
	}
	for(int i=1;i<=n;++i) {
		x=0;
		for(int j=0;j<21;++j) if(a[j]) x|=1<<j,--a[j];
		ans+=1ll*x*x;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：lnwhl (赞：0)

## 题意简述
>给定 $n$ 个非负整数 $a_1,\cdots,a_n$，每次操作中你可以选择一对 $i,j(i\neq j)$  并将 $a_i\gets a_i\ \mathsf{AND}\ a_j,\ a_j\gets a_i\ \mathsf{OR}\ a_j$
 ，两个赋值同时进行。你可以进行任意次操作。求操作后所有数的平方和的最大值，即 $\max \sum a_i^2$。

## 思路
一道很不错的贪心题。

首先我们要知道 
$$x+y=x\ \mathsf{AND}\ y+x\ \mathsf{OR}\ y$$
也就是说每次操作后两个数的总和是不变的，为了使平方和最大，我们肯定是应该使**大的尽量大，小的尽量小**。

进一步分析一下上面的那个式子，可以发现**每次操作过后每一位上的 $1$ 的个数不改变（二进制中）**。

------------
证明：
- 如果两个数第 $k$ 的数相同，那么进行$\ \mathsf{AND}\ $和$\ \mathsf{OR}\ $操作之后不会改变该位置上的值。
- 如果两个数第 $k$ 的数不同，那么肯定就是一个 $1$，一个 $0$。$1\ \mathsf{AND}\ 0=0,1\ \mathsf{OR}\ 0=1$，操作之后仍旧是一个 $1$，一个 $0$。

------------
有了上面的结论，我们就可以用一个桶统计出每一位有几个 $1$，然后尽可能的**贪心**，有 $1$ 就放，从而使大数更大。然后就可以通过本题了。时间复杂度 $O(n\log n)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int hav[25],n,x;
long long ans=0;
int main() 
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>x;
		for(int j=0;j<20;j++) 
			hav[j]+=(x>>j)&1;//统计每一位1的个数 
	}
	for(int i=1;i<=n;i++) 
	{
		long long res=0;
		for(int j=0;j<20;j++) 
			if(hav[j])//因为贪心，有1就分配 
				hav[j]--,res+=1<<j;
		ans+=res*res;
	}
	cout<<ans;
	return 0;
}
```
完结散花~~~

---

