# Reverse Card (Hard Version)

## 题目描述

The two versions are different problems. You may want to read both versions. You can make hacks only if both versions are solved.

You are given two positive integers $ n $ , $ m $ .

Calculate the number of ordered pairs $ (a, b) $ satisfying the following conditions:

- $ 1\le a\le n $ , $ 1\le b\le m $ ;
- $ b \cdot \gcd(a,b) $ is a multiple of $ a+b $ .

## 说明/提示

In the first test case, no pair satisfies the conditions.

In the fourth test case, $ (2,2),(3,6),(4,4),(6,3),(6,6),(8,8) $ satisfy the conditions.

## 样例 #1

### 输入

```
6
1 1
2 3
3 5
10 8
100 1233
1000000 1145141```

### 输出

```
0
1
1
6
423
5933961```

# 题解

## 作者：ShanQing (赞：13)

批：赛时没想到 $(p+q) \mid d $ 所以推复杂了还整出了奇怪的欧拉函数，喜提罚坐，快说我菜/kk。

首先经典套路，设 $d=\gcd(a,b)$，然后 $a=pd$，$b=qd$，显然有 $\gcd(p,q)=1$，原式变为 $(pd+qd) \mid (qd^2) $。

两边同除 $d$，原式变为 $(p+q) \mid (qd) $。

由 $\gcd(p,q)=1$ 得 $\gcd(p+q,q)=1$，所以只能有 $(p+q) \mid d $。

由于 $d=\frac{a}{p}$，又因为显然 $p<d$，所以有 $p<\frac{a}{p}<\frac{n}{p}$，即 $p^2<n$。同理，$q^2<m$。

于是就成功地缩小了 $p$ 和 $q$ 的范围。这时候就可以枚举所有满足 $\gcd(p,q)=1$ 的数对，对于每一对数对 $d$ 的取值范围显然为 $\min(\left\lfloor\frac{n}{p}\right\rfloor,\left\lfloor\frac{m}{q}\right\rfloor)$，然后又要满足 $(p+q) \mid d $，所以贡献即为 $\frac{\min(\left\lfloor\frac{n}{p}\right\rfloor,\left\lfloor\frac{m}{q}\right\rfloor)}{p+q}$。

## code

```cpp
//writer:Oier_szc

#include <bits/stdc++.h>
//#include <windows.h>
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define pii pair<int,int>
#define fi first
#define se second
#define int long long
using namespace std;
const int N=2e3+5,INF=2e9,mod=1e9+7;
int t,n,m;
int bad[N][N];
int gcd(int a,int b) {return !b?a:gcd(b,a%b);}
signed main() {
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld%lld",&n,&m);
		int ans=0;
		for(int a=1;a<=n/a;++a) {
			for(int b=1;b<=m/b;++b) {
				if(gcd(a,b)==1) ans+=min(n/a,m/b)/(a+b);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：InQueue (赞：3)

### Update：

2024.5.28：复杂度应为 $O(\sqrt{nm} \log{nm})$ 而非 $O(\sqrt{nm})$。感谢 @[N_z_](https://www.luogu.com.cn/user/320087) 指出。

---

题意很简单：计算满足以下两个条件的有序数对 $(a,b)$ 的数量：

- $1\le a\le n$，$1\le b\le m$。

- $(a+b)\mid (b\times \gcd(a, b))$。

令 $g = \gcd(a, b)$，$a_0,b_0$ 满足 $a = a_0g,b = b_0g,\gcd(a_0, b_0)=1$。

由题，有：

$$(a_0g+b_0g)\mid (b_0g^2)$$

$$\iff (a_0+b_0)\mid (b_0g)$$

由[辗转相减法](https://baike.baidu.com/item/%E8%BE%97%E8%BD%AC%E7%9B%B8%E5%87%8F/7529647)，$\gcd(a_0+b_0, b_0) = \gcd(a_0, b_0) = 1$。

所以，

$$(a_0+b_0)\mid g$$

$$\because g\neq 0$$

$$\therefore a_0+b_0\le g$$

代回条件一：

$$n\ge a = a_0g\ge a_0^2+a_0b_0$$

$$m\ge b = b_0g\ge b_0^2+a_0b_0$$

注意到此时 $a_0,b_0$ 都是根号级别的，直接枚举 $a_0,b_0$，复杂度为 $O(\sqrt{nm} \log nm)$，可以通过。

结合 $(a_0+b_0)\mid g$，得到答案：

$$\sum_{a_0=1}^{a_0^2+a_0\le n}\sum_{b_0=1}^{b_0^2+a_0b_0\le m}[\gcd(a_0, b_0)=1]\left \lfloor \dfrac{\min\left(\left \lfloor \dfrac{n}{a_0} \right \rfloor, \left \lfloor \dfrac{m}{b_0} \right \rfloor\right)}{a_0 + b_0} \right \rfloor $$

[CF 提交记录。](https://codeforces.com/contest/1967/submission/259260045)

---

## 作者：mayike (赞：3)

很水的一道推式子题，打不起比赛，被机房同学嘲讽后做的。

### [题目传送门](https://codeforces.com/problemset/problem/1967/B2)

## 思路

既然 $b \cdot \gcd(a,b)$ 是 $a + b$ 的倍数，那不妨设 $b \cdot \gcd(a,b)=(a+b) \cdot x$，$x$ 为正整数。

想想如何消掉 $b \cdot \gcd(a,b)$ 中的 $\gcd(a,b)$，不妨设 $a=n \cdot \gcd(a,b),b=m \cdot \gcd(a,b),\gcd(n,m)=1$，此处 $n,m$ 与题目的 $n,m$ 无关。

那么原式变为 $b \cdot \gcd(a,b)=(n+m) \cdot \gcd(a,b) \cdot x$，得 $b=m \cdot \gcd(a,b)=(n+m) \cdot x$，因为 $\gcd(n,m)=1$，所以 $m$ 与 $n+m$ 互质或 $m=1$ 结果一样，则一定有 $\gcd(a,b)=(n+m) \cdot k$，进而 $b=(n+m) \cdot k \cdot m,a=(n+m) \cdot k \cdot n$。发现 $m^2 < b,n^2 < a$，暴力枚举 $n,m$ 即可。

```cpp
#include<bits/stdc++.h>
int T,a,b;
long long ans;
using namespace std;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>a>>b;
		for(int n=1;n*n<=a;n++)
			for(int m=1,s;m*m<=b;m++)
				if(__gcd(n,m)==1)ans+=min(a/(n+m)/n,b/(n+m)/m);
		cout<<ans<<"\n",ans=0;
	}
	return 0;
}
```

---

## 作者：Unordered_OIer (赞：2)

# CF1967B2


设 $a=pg,b=qg$，其中 $\gcd(p,q)=1,g=\gcd(a,b)$。

设 $bg=m(a+b)$。

由 $b \times \gcd(a,b)$ 为 $a+b$ 的倍数，得 $qg^2=m(p+q)g,m \in \mathbb{Z^+}$。

$qg=m(p+q)$。

易知 $\gcd(q,p+q)=1$。

则设 $g=(p+q)r,r \in \mathbb{Z^+}$。

带回最初的式子：

$a=p(p+q)r,b=q(p+q)r$，其中仅要求 $\gcd(p,q)=1$。

实际上并不关心 $r$，所以枚举 $p,q$，只要最后算出来的 $a,b$ 在范围内即可，复杂度 $O(\sqrt{nm})$（由最终的式子不难发现 $p,q$ 不能超过 $\sqrt n,\sqrt m$）。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,m;
ll gcd(ll x,ll y){
	return !y?x:gcd(y,x%y);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		ll ans=0;
		for(ll i=1;i*i<=n;i++){
			for(ll j=1;j*j<=m;j++)if(gcd(i,j)==1){
				ll a=i,b=j;
				if(a*(a+b)<=n&&b*(a+b)<=m){
					ans+=min(n/a/(a+b),m/b/(a+b));
				}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：1)

不一样的做法。

枚举 $k$，使得 $b\cdot \gcd(a,b)=k(a+b)$，令 $c=\frac{a}{\gcd(a,b)}$，$d=\frac{b}{\gcd(a,b)}$。

两边同时除以 $b$ 可得 $\gcd(a,b)=k\cdot\frac{a}{b} + k$，进而可得 $\gcd(a,b)=c\cdot\frac{k}{d} + k$，由于 $c$ 和 $d$ 互质，所以当 $d$ 无法整除 $k$ 时，$c\cdot\frac{k}{d}$ 也不是整数，所以 $d$ 必然是 $k$ 的因数。

枚举 $k$ 的因数作为 $d$，可以表示 $a=\frac{k}{d}\cdot c^2 + k\cdot c$，因为 $a\leq n$，所以 $\frac{k}{d}\cdot c^2 + k\cdot c\leq n$，同理可得 $k\cdot c+ k\cdot d \leq m$。解这两个不等式可得 $c$ 的最大值。则当 $k$ $d$ 为此值时，有 $\lfloor c\rfloor$ 种方案。

最终可得合法方案数，时间复杂度为 $O(\sum\limits_{i=1}^{\min(n,m)}d(i) )$，其中 $d(i)$ 为数字 $i$ 因数的个数，用计算机算了一下稍小于 $10^8$，卡常后能过。

---

## 作者：masonpop (赞：1)

感觉自己的做法比较神秘，因此写一下。

考虑原式等价于 $(a+b)|\gcd^2(a,b)$。因为 $\gcd(a,b)=\gcd(a+b,b)$，设 $T=a+b$，则等价于 $T|\gcd^2(T,b)$，筛素因子后可以求出 $b$ 为某个数 $d$ 的倍数（即 $d|\gcd(T,b)$），且上下界为 $[\max(1,T-n),\min(m,T)]$。直接算就行。[代码](https://codeforces.com/contest/1967/submission/259634731)。

P.S. 关于这个 $d$ 的详细定义如下：

设 $T=\prod\limits_{i=1}^kp_i^{\alpha_i}$（唯一分解），定义 $\beta_i=\lceil\frac{\alpha_i}{2}\rceil$，那么 $d=\prod\limits_{i=1}^kp_i^{\beta_i}$。

---

## 作者：Luzhuoyuan (赞：1)

Links: [[Codeforces]](https://codeforces.com/contest/1967/problem/B2) [[Luogu]](https://www.luogu.com.cn/problem/CF1967B2)

### 题意

给定两个正整数 $n,m$，求同时满足以下两个要求的有序正整数对 $(a,b)$ 的个数：

- $1\le a\le n,1\le b\le m$；
- $b\cdot\gcd(a,b)$ 是 $a+b$ 的倍数。

每个测试点 $t$ 组测试用例。

---

- $1\le t\le 10^4$；
- $1\le n,m\le 2\cdot 10^6$；
- $\sum n,\sum m\le 2\cdot 10^6$。

### 思路

题目的要求就是存在正整数 $k$，满足 $b\cdot\gcd(a,b)=k(a+b)$，转化一下得到 $b=\dfrac{k(a+b)}{\gcd(a,b)}$。我们令 $g=\gcd(a,b),x=\dfrac a g,y=\dfrac b g$，则上式转化为 $yg=kx+ky$，并且显然 $x,y$ 互质。

之后，我们得到 $y(g-k)=kx$，我们发现 $k$ 一定是 $y$ 的倍数。简单证明：若 $k$ 非 $y$ 的倍数，由于 $kx$ 是 $y$ 的倍数，$x,y$ 必然有非 $1$ 的公因数，与它们互质相矛盾。

令 $c=\dfrac k y$，则 $x=\dfrac{y(g-cy)}{cy}=\dfrac g c-y$，即 $x+y=\dfrac g c$。又因为 $\dfrac g c\le g\le \lfloor\min(\dfrac n x,\dfrac m y)\rfloor$，所以对答案有贡献的 $x,y$ 分别小于等于 $\sqrt n,\sqrt m$。所以我们在这个范围内枚举 $x,y$，若它们互质，则把合法的 $g$ 的种数加进答案。预处理 $\gcd$ 就可以做到 $O(\sqrt n\cdot \sqrt m)=O(n)$ 的复杂度。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,B=1505,b=1500;
int T,n,m,g[B][B],bn,bm,ans;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
signed main(){
	for(int i=1;i<=b;i++)g[i][0]=g[0][i]=i;
	for(int i=1;i<=b;i++)for(int j=1;j<=i;j++)g[i][j]=g[j][i]=g[j][i%j];
	T=read();
	while(T--){
		n=read(),m=read();bn=sqrt(n),bm=sqrt(m);ans=0;
		for(int i=1;i<=bn;i++)for(int j=1;j<=bm;j++)if(g[i][j]==1)ans+=min(n/i,m/j)/(i+j);
		printf("%d\n",ans);
	}
	return 0;
}
```

（逃

---

## 作者：N1K_J (赞：1)

赛时非常唐，没有注意到 $a,b$ 范围。

题目大意：给定 $n,m$，求满足 $1 \le a \le n,1 \le b \le m,a+b | b \cdot \gcd(a,b)$ 的 $(a,b)$ 组数。

同 easy version，尝试令 $\gcd(a,b) = x,a = px,b = qx,\gcd(p,q) = 1$。

那么 $(p+q)x|qx^2$。

有 $p+q|qx$。

由于 $\gcd(p,q) = 1$，有 $\gcd(p+q,q) = 1$。

因此 $p+q|x$。

又 $a = px,b = qx$，得 $p \le \sqrt a,q \le \sqrt b$。

因此 $O(\sqrt n ^2)$ 的枚举 $p,q$ 就可以了。

[Code](https://codeforces.com/contest/1972/submission/258987026)

---

## 作者：NATO (赞：1)

##### 写在前面：

乱搞做法，谨慎观看。

不过既然能过极限数据，那就也没法卡掉是吧，也许能称之为正解？

#### 思路浅析：

考虑列出计数柿子：

$\sum\limits_{i=1}^n\sum\limits_{j=1}^m[(i+j)|j\cdot\gcd(i,j)]$

套路地，我们考虑枚举 $i,j$ 的最大公约数 $d$，并将枚举的 $i,j$ 变为 $\frac{i}{d},\frac{j}{d}$：

$\sum\limits_{d=1}^{\min(n,m)}\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}[(i+j)d|jd^2][\gcd(i,j)=1]$

考虑对 $[(i+j)d|jd^2]$ 下手，考虑它即为 $[(i+j)|jd]$，由于我们要求此时 $i,j$ 互质（这样 $d$ 才是枚举的最大公约数），所以该条件成立只可能是 $(i+j)|d$（因为显然 $\gcd(i+j,j)=1$），那么我们就可以不去枚举 $i$，转而去枚举 $d$ 的因数，根据因数反过来推得 $i$ 并验证条件（$i\cdot d\le n$ 和 $\gcd(i,j)=1$），如果可行则计数。

这样的代码是好写的，预处理每个数的因数，然后枚举 $d$ 和它的因数，再枚举一个 $j$ 即可，这样的复杂度理论上是 $O(n\log^3n)$ 的（当然远远跑不满，可能复杂度能有更严的下限？~~反正笔者证不来~~），看起来是过不去的，但是，当我们写出来后发现极限数据 $2000000\;2000000$ 是只跑了不到 $10$ 秒的，尝试卡常：

1. 将存放每个数因数的部分改为手写链表存储。

2. 发现答案不会超过 `int` 的范围，于是全部使用 `int`。

于是，我们的程序在本机上就可以以约 $1.5$ 秒跑完极限数据，CF 上以 [$1.9$](https://codeforces.com/contest/1972/submission/258950475) 秒的优异成绩通过本题，顺便还有可能喜提[最劣解](https://codeforces.com/contest/1972/submission/259128386)。

#### 参考代码：

就在上面的链接里，有需要自取罢。

---

## 作者：DerrickLo (赞：1)

设 $\gcd(a,b)=d,a=dx,b=dy$，则 $(x,y)=1$。

那么 $(a,b)$ 就满足 $d^2y$ 被 $d(x+y)$ 整除，也就是说 $dy$ 被 $x+y$ 整除。又因为 $(y,x+y)=1$，所以 $d$ 被 $x+y$ 整除。

那么 $x$ 与 $y$ 都是根号级别的。考虑枚举 $x$ 与 $y$，则 $d$ 需要满足 $dx\le n,dy\le m,(x+y)|d$ 这三个条件，这样的 $d$ 的个数很好计算。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t,n,m;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int ans=0;
		for(int i=1;i*i<=n;i++)for(int j=1;j*j<=m;j++)if(__gcd(i,j)==1){
			ans+=min(n/i/(i+j),m/j/(i+j));
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：快斗游鹿 (赞：0)

题目所给的条件是 $(a+b)\mid b\gcd(a,b)$ 设 $g=\gcd(a,b),a=gx,b=gy$，则条件转化为 $(gx+gy) \mid g^2y$，约掉 $g$，得到 $(x+y)\mid gy$。显然 $\gcd(x,y)=1$。

这时有个很重要的性质，因为 $\gcd(x,y)=1$，所以 $\gcd(x+y,y)=1$，那么题目实际上就是要满足 $(x+y)\mid g$。而 $g\le\min(\lfloor\dfrac{n}{x}\rfloor,\lfloor\dfrac{m}{y}\rfloor)$，也就意味着 $x\le \lfloor\dfrac{n}{x}\rfloor$，那么 $x$ 数量就是 $\sqrt{n}$ 级别的，$y$ 同理，是 $\sqrt{m}$ 级别的。所以可以直接枚举 $x,y$，若 $\gcd(x,y)=1$，那么答案就加上 $\dfrac{g}{x+y}$。这里 $g$ 应当取到上界 $\min(\lfloor\dfrac{n}{x}\rfloor,\lfloor\dfrac{m}{y}\rfloor)$。

---

## 作者：可爱的小棉羊 (赞：0)

这个思路很有意思！

老样子，设 $a=pd,b=qd,d=\gcd(a,b)$，那么有 $\gcd(p,q)=1$。

那么我们得到 $d(p+q)\mid qd^2$，接着除掉一个 $d$。

所以 $(p+q)\mid qd$，我们知道 $\gcd(p+q,q)=1$ 那么 $(p+q)\mid d$。

到了这里我们似乎不知道咋搞了。

那我们开始枚举呗！

枚举每对互质的 $p,q$，令 $d=k(p+q)$，

那么 $a= k(p+q)p\le n,b=k(p+q)q\le m$。

我们就发现 $p,q$ 只用枚举到根号级别，每一对的贡献为 $\left\lfloor\dfrac{\min(\left\lfloor\frac{n}{p}\right\rfloor,\left\lfloor\frac{m}{q}\right\rfloor)}{a+b}\right\rfloor$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
	return b? gcd(b,a%b):a;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		long long ans=0;
		cin>>n>>m;
		for(int i=1;i<=n/i;i++){
			for(int j=1;j<=m/j;j++){
				//d%i+j==0
				//d<=n
				//m<=n/i/(i+j))
				//m<=n/j/(i+j)
				if(gcd(i,j)==1){
					ans+=(min(n/i,m/j)/(i+j));
				}
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：WRuperD (赞：0)

写发题解记录一下这道本来送我上 CM 的题。
![](https://cdn.luogu.com.cn/upload/image_hosting/dlckkk82.png)

不妨设题目中数对为 $(A,B)$。设 $\gcd(A,B)$ 为 $g$，$A = ag$，$B=bg$。

题目条件相当于 $bg^2=kg(a+b)$。

两边除以 $g$ 然后移项得到 ${b\over a} = {k\over g-k}$。

注意到 $a,b$ 互质。因此左式子是一个最简分数的形式。因从我们不妨设 ${b\over a} = {pk'\over p(g'-k')}$ 其中 ${k'\over (g'-k')}$ 也为最简分数。则有 $B=bpk',A=pa(g'-k')$。

有 $bg \leq m,ag\leq n$。则有 $gk' \leq m$, $g'^2-gk' \leq n$。所以有 $g'^2 \leq n + m$。所以有 $g'$ 和 $k'$ 是 $\sqrt {n + m}$ 级别的。忘记赛时是怎么做的了，反正可以得到其实 $g'$ 和 $k'$ 是 $\sqrt{\max(n,m)}$ 的。但是无伤大雅。

因此，我们可以考虑直接枚举所有的最简分数对 ${k'\over g'-k'}$。这样子是 $O(\sqrt {\max(n,m)} * \sqrt {\max(n,m)}) = O({\max(n,m)})$ 的。然后我们就由 $pg'a \leq n$，$pg'b \leq m$ 可以 $O(1)$ 计算出有多少种 $p$ 满足条件。

总的复杂度就是 $O(\max(n,m))$ 的了。

```cpp
// Problem: D2. Reverse Card (Hard Version)
// URL: https://codeforces.com/contest/1972/problem/D1
// Writer:WRuperD
// Powered by CP Editor (https://cpeditor.org)
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 1e6 + 10;

void solve(){
	int n = read(), m = read();
	int ans = 0;
	for(int i = 1; i * i <= n + m; i++){
		for(int j = 1; j * j <= n + m; j++){
			if(__gcd(i, j) != 1){
				continue;
			}
			int k = i, p = j + k;
			int b = k, a = p - k;
			if(a * p <= n and b * p <= m){
				ans += min(n / a / p, m / b / p);
			}
		}
	}
	write(ans), endl; 
	return ;
}

signed main(){
	int t = read();
	while(t--)	solve();
	return 0;
}
```

---

## 作者：robinyqc (赞：0)

一个另解，且复杂度较优异，代码也好写。

令 $c = a + b$，原式变为 $c\mid b\gcd(c - b, b)$，也即 $c\mid b\gcd(b, c)$。

质因数分解，设 $c = \prod p_i^{k_i}, b = \prod p_i^{r_i}$，那么 $\gcd(b, c) = \prod p_i^{\min(k_i, r_i)}$，那么 $b\gcd(b, c) = \prod p_i^{\min(k_i, r_i) + r_i}$。

由于 $c\mid b\gcd(b, c)$，由质因数分解相关性质，这个式子等价于 $\forall p_i, \min(k_i, r_i) + r_i \geq k_i$。

当 $r_i > k_i$ 时，式子恒成立；当 $r_i \leq k_i$ 时，式子等价于 $2r_i\geq k_i$。综上，$\min(k_i, r_i) + r_i\geq k_i\Leftrightarrow 2r_i\geq k_i$。

又，$r_i, k_i$ 都是整数，则 $2r_i\geq k_i\Leftrightarrow r_i\geq \left\lceil\frac {k_i}2\right\rceil$。

转化回整数形式，令 $v_c = \prod p_i^{\left\lceil\frac {k_i}2\right\rceil}$，那么 $v_c\mid b$。

也即，若钦定 $c$，就是要求 $[1, m]$ 中 $v_c$ 的倍数。这个是容易 $O(1)$ 求出的。

所以先对每个 $c\in [2, n + m]$ 求出 $v_c$，然后枚举 $c$ 计算即可。

预处理部分复杂度为 $1\sim n + m$ 所有数质因子个数和，也即 $O((n + m)\log \log (n + m))$ 的。回答询问是 $O(n + m)$ 的。

注意要保证 $1\leq a \leq n, 1\leq b\leq m$。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

using i64 = long long;

const int V = 4000000;

struct D2
{

vector<int> val;

D2(): val(V + 1, 1)
{
    vector<int> prime;
    vector<char> is_p(V + 1, true);
    for (int i = 2; i <= V; i++) {
        if (is_p[i]) prime.emplace_back(i);
        for (i64 j: prime) {
            if (i * j > V) break;
            is_p[i * j] = false;
            if (i % j == 0) break;
        }
    }
    for (int p: prime) {
        for (int i = p; i <= V; i += p) {
            int j = i, cnt = 0, v = 1;
            while (j % p == 0) {
                cnt++;
                j /= p;
                if (cnt & 1) v *= p;
            }
            val[i] *= v;
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    long long ans = 0;
    for (int c = 2; c <= n + m; c++) {
        ans += min(m, (c - 1)) / val[c] - max(c - n - 1, 0) / val[c];
    }
    cout << ans << '\n';
}

};

signed main()
{
    int t;
    cin >> t;
    D2 d2;
    while (t--) d2.solve();
    return 0;
}
```

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1967B2)/[Codeforces 1967B2](https://codeforces.com/contest/1967/problem/B2)/[Codeforces 1972D2](https://codeforces.com/contest/1972/problem/D2)

## 题意简述

给出两个数 $n,m$，求满足 $1\leq a\leq n,1\leq b\leq m,a+b|b\cdot\gcd(a,b)$ 的数对 $(a,b)$ 的数量。

## 解题思路

设 $a=x\cdot\gcd(a,b),b=y\cdot\gcd(a,b),x\perp y$，则 $(x+y)\gcd(a,b)|b\cdot\gcd(a,b)$，则 $x+y|y\cdot\gcd(a,b)$，又因为 $x\perp y$，可以得到 $\gcd(x+y,y)=\gcd(x,y)=1$，即 $x+y\perp y$，故 $x+y|\gcd(a,b)$。

由此可知，$\gcd(a,b)\geq x+y,x(x+y)\leq x\cdot\gcd(a,b)=a\leq n,y(x+y)\leq y\cdot\gcd(a,b)=b\leq m$，所以在 $\left[1,\lfloor\sqrt n\rfloor\right]$ 内枚举 $x$，在 $\left[1,\lfloor\sqrt m\rfloor\right]$ 内枚举 $y$，所有满足 $g\in\N^+,x+y|g,g\in\left[1,\min\left(\frac nx,\frac my\right)\right]$ 的 $g$ 都能作为 $\gcd(a,b)$，累积 $ans$ 输出即可。考虑到辗转相除法的时间复杂度，代码时间复杂度严格小于 $O(\sqrt{nm}\log m)$。

## AC 代码
### C++
```cpp
#include<stdio.h>
int min(int x,int y){return x<y?x:y;}
int gcd(int x,int y){return x?gcd(y%x,x):y;}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        long long ans=0;
        for(int x=1;x*x<=n;x++)
            for(int y=1;y*(y+x)<=m;y++)
                if(gcd(x,y)==1)ans+=min(n/x,m/y)/(x+y);
        printf("%lld\n",ans);
    }
    return 0;
}
```
### Python
```python
import sys
sys.setrecursionlimit(2000000)
from math import sqrt

def gcd(x,y):
    if x!=0:
        return gcd(y%x,x)
    return y

t=int(input())
for T in range(t):
    [n,m]=input().split()
    [n,m]=[int(n),int(m)]
    ans=0
    for i in range(1,int(sqrt(n))+1):
        for j in range(1,int(sqrt(m))+1):
            if gcd(i,j)==1:
                ans=ans+(min(n//i,m//j)//(i+j))
    print(ans)
```

---

## 作者：MarSer020 (赞：0)

场上卡了 1.5h，感觉像个 shaber。

但是显然不止绿吧，场上 zdc 和 zyf 都卡了 0.5h（

和 CF1956D 相比，建议这道题评蓝，那道题评绿。

感觉我的做法好唐。

$\Large\text{Solution}$

设 $\gcd(a,b)=g,a=xg,b=yg$，显然的，$x,y,g$ 均为整数，且 $\gcd(x,y)=1$。

考虑有如下转化：
$$
\begin{aligned}
&a+b\mid bg\\
\Leftrightarrow \ &x+y\mid yg\\
\because \ &\gcd(x,y)=1,\gcd(x+y,y)=1\\
\therefore \ &x+y\mid g
\end{aligned}
$$

所以枚举 $x+y$，再枚举 $g=k(x+y)$，再枚举 $x$ 即可。

考虑枚举 $x$ 的范围是 $[1,s]\bigcap[s-\frac{m}{g},\frac{n}{g}]$，总之是能过的，时间复杂度[听说](https://codeforces.com/blog/entry/129027?#comment-1145067)是 $O(ans\log n)$ 的。

$\Large\text{Code}$

很好理解，很短。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,m,ans;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>T;
	while(T--){
		cin>>n>>m,ans=0;
		for(int s=2;s<=n;s++)
			for(int g=s;g<=n;g+=s)
				for(int x=max(1,s-m/g);x<=s&&x<=n/g;x++)
					if(__gcd(x,s-x)==1)
						ans++;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

