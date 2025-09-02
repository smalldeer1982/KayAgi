# 「dWoi R2」Elevator / 电梯

## 题目背景

zszz，主角总会在学级裁判前乘电梯下去的过程中在内心写小作文。

但万一写不出来怎么办 Zzz ……

于是最原开始想数学题了 ……

## 题目描述

现有正整数 $a,b,c$ 满足 $\alpha$ 式：$\dfrac{1}{a}-\dfrac{1}{b}=\dfrac{1}{c}$，且 $\gcd (a,b,c)=1$。

现给定正整数 $N$，请编程求出满足 $c \leq N$ 的 $\alpha$ 式的个数以及满足以下条件的一个 $b$：

对所有 $c=N$ 得到的 $\alpha$ 式中使得 $a$ 最小。

## 说明/提示

#### 样例 #2 解释

第一个询问中对应的式子为：$\dfrac{1}{232} - \dfrac{1}{54056} = \dfrac{1}{233}$，故后一个输出为 $54056$。

第二个询问中对应的式子为：$\dfrac{1}{1620} - \dfrac{1}{8181} = \dfrac{1}{2020}$，故后一个输出为 $8181$。

而这两个 $\alpha$ 式的 $a$ 在所有 $c=N$ 的情况中是最小的。
- - -
#### 数据规模与约定

对于 $10\%$ 的数据，有 $N\leq 100$，$T\leq 10$。

对于 $30\%$ 的数据，有 $N\leq 10^3$，$T\leq 100$。

对于 $70\%$ 的数据，有 $N\leq 10^5$，$T\leq 10^4$。

对于 $100\%$ 的数据，有 $N\leq 2\times 10^6$，$T\leq 10^5$。
- - -
#### 关于 Special Judge

**本题采用 Special Judge。**

如果你第一问都答对了而第二问有答错的，那么你将得到 $30\%$ 的分数，如果你第一问有答错的而第二问都答对了，那么你将得到 $70\%$ 的分数，但是如果你第一问和第二问都有部分或者全部错误，那么你将被判作 WA；此外，如果你输出残缺或者过多，例如只回答第一问却不输出第二问的答案（$N=1$ 除外）或者 $N=1$ 后多输出了一个数，那么你将同样不会得到分数。

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
0
1 2```

## 样例 #2

### 输入

```
2
233
2020```

### 输出

```
479 54056
5470 8181```

# 题解

## 作者：Prean (赞：7)

题意：给定 $ n $，求方程 $ \frac 1 a - \frac 1 b=\frac 1 n $ 的所有解，且解必须满足 $ \gcd(a,b,n)=1 $。

以下内容搬运自官方题解：

转化一下：
$$ bn=a(b+n) $$
$$ a=\frac {bn} {b+n} $$
根据 $ \gcd(a,b,n)=1 $，有：
$$ \gcd(\frac {bn} {b+n},b,n)=\gcd(\frac {bn} {b+n},\gcd(b,n))=1 $$
接下来设 $ b=x \times \gcd(b,n),n=y \times \gcd(b,n) $，那么一定有 $ \gcd(x,y)=1 $。

于是：
$$ \gcd(\frac {xy} {x+y} \times \gcd(b,n),\gcd(b,n))=1 $$
$$ \gcd(b,n)|(x+y) $$
而 $ \gcd(xy,x+y)=1,\frac {xy} {x+y} \times \gcd(b,n) $ 是整数，所以有 $ (x+y)|\gcd(b,n) $。

于是 $ x+y=\gcd(b,n),b+n=\gcd(b,n) \times (x+y) = \gcd(b,n)^2 $。

相当于求方程 $ x+n=\gcd(x,n) $。（这里的 $ x $ 在上面是 $ b $）

下面为了方便，设 $ \gcd(x,n)=d,c=dk $。
$$ d^2=dk+x $$
$$ x=d \times (d-k) $$
然后对于 $ d $，枚举可行的 $ k $，最后检查一下是否合法就行。

检查是否合法的瓶颈在于，计算 $ \gcd(x,c)=\gcd(d(d-k),c)=\gcd(d(d-k),dk)=d \times \gcd(d-k,k) $。

这里的 $ d-k $ 和 $ k $ 一定有一个数不大于 $ \sqrt n $，所以根据 $ \gcd(a,b)=\gcd(a \bmod b,b) $，可以直接预处理一个 $ \sqrt n \times \sqrt n $ 的表。

再往下推，发现实际上是判断 $ d \times \gcd(d-k,k)=d $，也就是判断 $ d $ 和 $ k $ 是否互质，所以打表可以使用一个 bool 类型的数组来降低常数。

到这里，复杂度已经变成 $ O(n\log n+T) $ 的了。在[加强版](https://www.luogu.com.cn/problem/U175972)中，这个做法只跑了 1s，并且卡掉了 $ O(n+T\sqrt n) $ 的暴力，还在原版跑到了[300ms](https://www.luogu.com.cn/record/56864840)。
```cpp
#include<cstdio>
#include<vector>
typedef unsigned uint;
typedef unsigned long long ull;
const uint M=2e6;
uint T,mx,n[100005],ans1[M+5];bool _check[1420][1420];
ull ans[M+5],ans2[M+5];
inline ull min(const ull&a,const ull&b){
	return a>b?b:a;
}
signed main(){
	register uint i,j,x;
	scanf("%u",&T);_check[0][1]=true;
	for(i=1;i<=1415;++i)_check[1][i]=true;
	for(i=2;i<=1415;++i){
		for(x=0,j=i;j<=1415;++j){
			_check[i][j]=_check[x][i];
			if(++x==i)x=0;
		}
	}
	for(i=1;i<=T;++i)scanf("%u",n+i),mx=n[i]>mx?n[i]:mx;
	for(i=1;i<=mx;++i)ans2[i]=0x7f7f7f7f7f7f7f7f;
	for(i=1;i<=mx;++i){
		for(j=1,x=i;j<=i&&x<=mx;++j,x+=i){
			if(_check[i%j][j])ans2[x]=min(ans2[x],1ull*i*(i-j)),++ans1[x];
		}
	}
	for(ans1[i=1]=0;i<=mx;++i)ans1[i]+=ans1[i-1];
	for(i=1;i<=T;++i)printf(n[i]==1?"0\n":"%u %llu\n",ans1[n[i]],ans2[n[i]]);
}
```

---

## 作者：djwj233 (赞：3)

先把 $N=1$ 的情况特判掉，再进行讨论。

不难想到一个预处理前缀和的思路：我们对每个 $c$ 都算出其对应的方案数、答案，然后在方案数中累加上之前的所有方案数。

题目中那个式子可推得：
$$
ab+ac=bc
$$
由于 $ac>0$，因此 $ab<bc$，有 $a<c$。

考虑一种暴力：我们对每个 $c$，暴力地枚举 $a\in [1,c)$，每次判断
$$
b=\frac{ca}{c-a}
$$
是否为整数且是否有 $\gcd(a,b,c)=1$ 即可。复杂度 $\Theta(n^2)$。

问题在于如何优化这个枚举 $a$ 的过程。我们发现式子中的分母不太好处理，于是我们令 $c-a=x$，有
$$
x\mid ca \Leftrightarrow x\mid c(c-x)\Leftrightarrow x\mid c^2-xc \Leftrightarrow x\mid c^2 
$$
又因为 $x\in [1,c)$，因此 $x$ 是 $c^2$ 的较小的因数，有 $x<\dfrac{c^2}{x}$。

那么由于 $\gcd(a,c)=\gcd(c-a,c)=\gcd(x,c)$，因此 $\gcd(a,b,c)=\gcd(\gcd(x,c),b)$。

又因为
$$
b=\frac{c^2-xc}{x}=\frac{c^2}{x}-c
$$
因此设 $\gcd(x,c)=k$，则 $\gcd(k,b)=\gcd(k,\dfrac{c^2}{x})$。

再设 $\dfrac{x}{k}=\alpha,\dfrac{c}{k}=\beta$，有 $\gcd(\alpha,\beta)=1$，且
$$
\gcd(k,\frac{k^2\beta^2}{k\alpha})=1\Rightarrow\gcd(k,\frac{k\beta^2}{\alpha})=1
$$
由于 $\gcd(\alpha,\beta)=1$，所以 $\gcd(\alpha,\beta^2)=1$，有 $\alpha\mid k$。

若 $\alpha<k$，则 $\gcd(k,\dfrac{k}{\alpha})>1$，矛盾，因此有 $\alpha=k$，故 $x=\gcd(x,c)^2$。

另一方面，可以证明取任意 $x$ 使 $x=\gcd(x,c)^2$ 时，所得的 $b$ 都是整数且有 $\gcd(a,b,c)=1$。

那么现在的问题变得简单多了。由算术基本定理，我们对 $c$ 进行标准分解：（这可以通过素数筛实现）
$$
c=\prod_{i=1}^{cnt} p_i^{a_i}\quad(p_i\in \mathbb P,a_i\ge1)
$$
那么我们取的 $\gcd(x,c)$ 质因数分解后第 $i$ 项的次幂**要么是 $0$，要么是 $a_i$**。

对于第一问，看上去答案为 $2^{cnt}$，但这是不正确的。我们注意到有一个 $x<c$ 的要求，因此需要 $\gcd(x,c)^2<c$。

易知 $2^{cnt}$ 种答案一一对应地有 $>\sqrt{c}$ 和 $<\sqrt{c}$ 两种情况，且不可能有 $=\sqrt{n}$ 的情况出现。

因此答案就是 $2^{cnt-1}$。

对于第二问，让 $a$ 最小其实就是让 $x$ 最大。

那么我们反着来，枚举一个 $d=\gcd(x,c)$，枚举所有是 $d$ 的倍数且 $>d^2$ 的 $c$，逐一判断是否有 $\gcd(d^2,c)=1$ 并更新答案即可。

代码：
```c++
#include <bits/stdc++.h>
using namespace std;
#define fo(v,a,b) for(int v=a;v<=b;v++)
#define fr(v,a,b) for(int v=a;v>=b;v--)
#define il inline

typedef long long ll;

const int N=2000010;

int n;
int cnt[N]; ll f[N],ans[N];

void prework()
{
	for(int i=2;i<=n;i++) if(cnt[i]==0)
		for(int j=i;j<=n;j+=i)
			cnt[j]++;
	for(int i=2;i<=n;i++)
		f[i]=f[i-1]+(1LL<<(cnt[i]-1));

	for(int d=1;d*d<=n;d++)
		for(int c=d*(d+1);c<=n;c+=d)
			if(__gcd(c,d*d)==d)
				ans[c]=max(ans[c],(ll)d*d);
	for(int i=2;i<=n;i++) {
		ans[i]=i-ans[i]; // calculate a
		ans[i]=(ll)i*ans[i]/(i-ans[i]); // calculate b
	}
}

void solve()
{
	scanf("%d",&n);
	if(n==1) {
		puts("0");
	} else {
		printf("%lld %lld\n",f[n],ans[n]);
	}
}

int main()
{
	n = N-10;
	prework();
	
    int T; cin>>T;
    while(T--) solve();
    
    return 0;
}
```

---

