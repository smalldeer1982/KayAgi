# Well played!

## 题目描述

Max 最近沉迷于一款打怪游戏《赛某号》。现在，他正在参加赛某号的春季联赛。

他有 $n$ 只精灵。每只精灵都有对应的生命值 $hp_i$ 和攻击值 $dmg_i$。在比赛过程中，Max 可以借助巴拉拉小魔仙之力，说出这两种咒语：

1. “乌卡拉！血量！加倍！“意即将当前精灵的生命值加倍。（使得 $hp_i \gets 2\times hp_i$）

2. “乌卡拉！生命之力！”意即将当前精灵的生命值赋给当前精灵的攻击值。（使得 $dmg_i\gets hp_i$）

Max 当然不能无限使用这两种咒语。在一局游戏中，他可以使用第一种咒语 $a$ 次，第二次咒语 $b$ 次。由于Max 购买了超级 Nono，所以这两种咒语都可以被多次用在同一精灵身上，且咒语的使用顺序没有限制。Max 可以不用完所有的咒语。

Max 非常希望通过使用这些咒语使得自己的精灵战斗群的攻击值达到最大。现在，Max 想知道这个最大值。


输入第 $2$ 行到第 $n+1$ 行，每行两个整数 $hp$，$dmg$。第 $i$ 行表示第 $i-1$ 个精灵的生命值和攻击值。

## 样例 #1

### 输入

```
2 1 1
10 15
6 1
```

### 输出

```
27
```

## 样例 #2

### 输入

```
3 0 3
10 8
7 11
5 2
```

### 输出

```
26
```

# 题解

## 作者：Echidna (赞：2)

首先，有一个很显然的结论：把所有的生命值乘二的机会都给一个人是最优的。

下面是证明：

我们考虑假如这里有两个人，他们的生命值分别为 $h_1,h_2$ ，他们的攻击值均小于他们自己的生命值。这里还有 $n$ 次生命乘二的机会和可以视为无限次的把生命值赋为攻击值的机会。

那么我们假设我们把 $x$ 次生命乘二的机会分给第一个人，那么它们的战斗力之和可以表示为 

$$f(x)=2^xh_1 + 2^{n-x}h_2$$

让我们假设存在一个 $a\in[1,n]$ ，使得 $f(a)>f(0)$ 且 $f(a)>f(n)$ ，那么则有 

$$
\begin{aligned}&
\begin{cases}
2^ah_1 + 2^{n-a}h_2 > h_1 +2^nh_2\\
2^ah_1 + 2^{n-a}h_2 > 2^nh_1 + h_2
\end{cases}
\\\\
\to&
\begin{cases}
(2^a-1)h_1 > (2^n-2^{n-a})h_2\\
(2^n-2^a)h_1 < (2^{n-a}-1)h_2
\end{cases}
\\\\
\to&
\begin{cases}
\dfrac{h1}{h2} > \dfrac{2^n-2^{n-a}}{2^a-1} = \dfrac{(2^a-1)\cdot2^{n-a}}{2^a-1}=2^{n-a}\\ \\
\dfrac{h1}{h2} < \dfrac{2^{n-a}-1}{2^n-2^a} = \dfrac{2^{n-a}-1}{(2^{n-a}-1)\cdot 2^a} = \dfrac{1}{2^a}
\end{cases}
\\\\
\to&
\begin{cases}
\dfrac{h1}{h2} > 2^{n-a}\\\\
\dfrac{h1}{h2} < \dfrac{1}{2^a}
\end{cases}
\end{aligned}
$$

因为 $2^{n-a} > \frac{1}{2^a}$ ，所以不可能找到一个 $a$ 满足 $f(a)>f(0)$ 且 $f(a)>f(n)$ ，所以在只有两个人并且两个人的初始攻击值都低于生命值的情况下，把机会都给一个人最优。

有一个人的初始攻击值 $d_i$ 高于他的初始生命值 $h_i$ 的情况是大同小异的，于是我们得到结论：

**两个人，无论他们的生命值和攻击值之间的关系是怎样的，把生命乘二给其中一个人总是会更优。**

对于第一次操作分布到了三个或者更多人的情况，同样适用本结论。对于任意两个被分布的人，必然把两个人的生命值乘二机会放到某一个人身上会比这个更优，于是没有一个分布到了三个或三个以上的人的方案是最优的。

于是我们扩展了结论：

**在多个人中，无论他们的生命值和攻击值之间的关系是怎样的，把生命乘二给其中一个人总是会更优。**

贪心证明完成之后我们就可以用简单的方法来把答案求出来啦

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e6;
#define ll long long
#define PII pair<int,int>
PII s[N];
int delta[N];
int n,a,b;
signed main(){
    cin>>n>>a>>b;
    int sum=0;
    for(int i=1;i<=n;i++)
        cin>>s[i].first>>s[i].second,sum+=s[i].second;
    if(b==0){
        cout<<sum<<endl;
        return 0;
    }
    sort(s+1,s+1+n,[](PII a,PII b){
        return a.first-a.second>b.first-b.second;
    });
    int cont=0;
    int lst=0;
    for(int now=1;now<=min(b,n);now++){
        if(s[now].first>s[now].second){
            cont+=s[now].first-s[now].second;
            lst=now;
        }else break;
    }
    for(int i=1;i<=n;i++)
        if(i<=lst)
            delta[i]=cont-(s[i].first-s[i].second);
        else delta[i]=(lst==b)?(cont-(s[lst].first-s[lst].second)):cont;
    int ans=0;
    for(int i=1;i<=n;i++)
        delta[i]=delta[i]+(1ll<<a)*s[i].first-s[i].second,ans=max(ans,delta[i]);
    cout<<max(ans+sum,sum)<<endl;
}
```

---

## 作者：UncleSam_Died (赞：1)

### 解题思路

两个显然的结论：

- 将所有生物 $hp_i-dmg_i$ 的值按照从大到小的顺序排序后，将正值部分全部进行 $b$ 操作（如果可以的话），这样是最优的；
- 将所有的 $a$ 操作全部在同一生物上进行是最优的，证明如下（假设只有两个，多个同样成立）：
  - 令 $f(i,x)=hp_i\times 2^x$，则 $f(j,y)=hp_j\times 2^y$，由此可得分开的值 $sum=f(i,x)+f(j,y)-dmg_i-dmg_j$，在一个生物上进行的值为 $f(i,x+y)+f(j,0)-dmg_i-dmg_j$，不妨设 $hp_i>hp_j$；
  - 假设 $f(i,x+y)+f(j,0)-dmg_i-dmg_j<sum$，则 $f(i,x+y)+f(j,0)<f(i,x)+f(j,y)$，移项可得 $f(i,x+y)-f(i,x)<f(j,y)-f(j,0)$，带入得到 $hp_i\times(2^y-1)\times 2^x<hp_j\times (2^y-1)$，不等式两边同时除以 $2^y-1$ 可得 $hp_i\times 2^x<hp_j$ ，又因为 $hp_i>hp_j$，故等式不成立，$f(i,x+y)+f(j,0)-dmg_i-dmg_j\ge sum$；
  - 综上，将 $a$ 全部赋为一个生物最优。

接下来只需要简单的贪心就可以了，但是有些细节需要注意一下。



### AC 代码

```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 200005
#define int ll
int n,a,b,d[N];
struct QWQ{int hp;int dmg;}s[N];
inline bool cmp(QWQ A,QWQ B){
	if(A.hp-A.dmg==B.hp-B.dmg)
		return A.hp>B.hp;
	return A.hp-A.dmg>B.hp-B.dmg;
}
signed main(){
	scanf("%lld%lld%lld",&n,&a,&b);
	for(register int i=1;i<=n;++i){
		scanf("%lld",&s[i].hp),
		scanf("%lld",&s[i].dmg);
	}std::sort(s+1,s+n+1,cmp);
	int replace=0,maxt1=-1,res=0;
	for(register int i=1;i<=n;++i)
		res+=s[i].dmg,d[i]=s[i].dmg;
	if(b==0){printf("%lld",res);return 0;}
	if(b){for(register int i=1;i<=n;++i){
			int sub=s[i].dmg;
			int now=(1ll<<a)*s[i].hp-sub;
			maxt1=std::max(maxt1,now);
		}res=res+maxt1;
	}for(register int i=1;i<=n;++i){
		if(s[i].hp<=s[i].dmg||!b) break;
		s[i].dmg=s[i].hp;--b;++replace;
	}int ans=0;
	for(register int i=1;i<=n;++i)
		ans+=s[i].dmg;
	int Maxt=-1,Mint=s[replace].dmg,Mini=replace;
	for(register int i=1;i<=replace;++i){
		if(s[i].hp>Maxt) Maxt=s[i].hp;
	}int maxt=((1ll<<a)-1)*Maxt;
	if(b>0){for(register int i=replace+1;i<=n;++i){
			int sub=s[i].dmg;
			int now=(1ll<<a)*s[i].hp-sub;
			maxt=std::max(maxt,now);
		}
	}else{for(register int i=replace+1;i<=n;++i){
			int sub=s[i].dmg;
			int now=(1ll<<a)*s[i].hp-sub;
			maxt=std::max(maxt,now-Mint+d[Mini]);
		}
	}printf("%lld",maxt+ans>res?maxt+ans:res);
}



```



---

## 作者：JWRuixi (赞：1)

~~这题竟然有 $2100$！~~

- 题意

给定 $n$ 只精灵，包含两个参数 $hp$ 和 $d$。能对其进行两种操作：

1. $hp \leftarrow hp \times 2$，可以进行 $a$ 次。
2. $d \leftarrow hp$，可以进行 $b$ 次。

求 $\sum\limits_{i=1}^n d_i$ 的最大值。

- 分析

虽然显然可以看出一操作全用在一个精灵身上最优，但还是证一下：

令 $hp^\prime_{i,x} = hp_i \times 2^x$，不妨假设 $hp^\prime_{i,x} \ge hp^\prime_{j,y}$ 则 $hp^\prime_{i,x} + hp^\prime_{j,y} \le hp^\prime_{i,x+1} + hp^\prime_{j,y-1}$，移项即可。

考虑每次使用二操作能使答案的贡献增加 $hp-d$ 所以可以按其为关键字降序排序，取前 $b$ 个。

让后对于每一个书考虑如果将其 $hp \leftarrow hp\times2^a$ 之后的答案，注意对于后 $n-b$ 个数，要从前面减掉第 $b$ 个数的贡献才能多出一个二操作。

- code

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500);
int n, a, b, ans;

struct Node {
	int hp, d;
	inline int mx () {
		return max(hp, d);
	}
	inline bool operator < (const Node &rhs) const {
		return hp - d > rhs.hp - rhs.d;
	}
} q[maxn];

signed main () {
	n = read(), a = read(), b = min(read(), n);
	for (int i = 1; i <= n; i++) q[i] = {read(), read()};
	sort(q + 1, q + n + 1);
	for (int i = 1; i <= n; i++) {
		if (i <= b) ans += q[i].mx();
		else ans += q[i].d;
	}
	if (!b) return write(ans), 0;
	const int x = (1 << a), sum = q[b].d - q[b].mx(), tmp = ans;
	for (int i = 1; i <= n; i++) {
		if (i <= b) {
			int res = tmp - q[i].mx() + q[i].hp * x;
			ans = max(ans, res);
		} else {
			int res = tmp - q[i].d + q[i].hp * x + sum;
			ans = max(ans, res);
		}
	}
	write(ans);
}
```

---

## 作者：kkio (赞：1)

显然的贪心结论：如果要乘的话，那么乘到一个数上是最好的。

用数学方式推式子肯定能出，但是这里给个口胡证明：

假设你现在枚举了乘两个数，那么你总得先将这个两个数乘过他的 $ dmg $ 。所以现在再乘的话，你会发现，始终乘那个 $ hp $ 大的一定好，那么对于另一个数，我们还将他乘过 $ dmg $ 干什么?

所以枚举乘哪个数，注意一些边界情况就好了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int sum,n,a,b,maxx,pw=1,trm=0;
struct wwh
{
	int hp,dp,id;
	bool operator < (wwh r)
	{return hp-dp>r.hp-r.dp;}
}w[maxn];
signed main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	for(int i=1;i<=a;i++)pw*=2;
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&w[i].hp,&w[i].dp);
	sort(w+1,w+1+n);
	for(int i=1;i<=n;i++)
		if(w[i].hp-w[i].dp>0&&i<=b)
		{ 
			sum+=w[i].hp;
			if(i==b)trm=-w[i].hp+w[i].dp;
		} 
		else 
			sum+=w[i].dp;
	maxx=sum;
	for(int i=1;i<=n;i++)
	{
		int thp=w[i].hp*pw;
		if(w[i].hp-w[i].dp>0&&i<=b)maxx=max(sum-w[i].hp+thp,maxx);
		else if(b)maxx=max(maxx,sum-w[i].dp+thp+trm);//如果前面把次数用完了，那么你就得牺牲一个
	}
	printf("%lld\n",maxx);
}
```


---

## 作者：大菜鸡fks (赞：1)

a操作显然加到一个人身上最优。 枚举a操作

b操作显而易见，改变量越大越优

细节注意一下就可以了

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+5;
struct node{
	ll x,y;
}A[N];
int n,a,b;
ll sum;
inline void init(){
	scanf("%d%d%d",&n,&a,&b);
	for (int i=1;i<=n;i++) {
		scanf("%I64d%I64d",&A[i].x,&A[i].y);
	}
}
inline bool cmp(node A,node B){
	return A.x-A.y>B.x-B.y;
}
inline void solve(){
	sort(A+1,A+1+n,cmp);
	for (int i=1;i<=b;i++) sum+=max(A[i].x,A[i].y);
	for (int i=b+1;i<=n;i++) sum+=A[i].y;
	ll ans=sum;
	for (int i=1;i<=b;i++) ans=max(ans,sum-max(A[i].x,A[i].y)+(A[i].x<<a));
	sum=sum-max(A[b].x,A[b].y)+A[b].y;
	for (int i=b+1;i<=n&&b;i++) ans=max(ans,sum-A[i].y+(A[i].x<<a));
	printf("%I64d\n",ans); 
}
int main(){
	init();
	solve();
	return 0;
}
```

---

