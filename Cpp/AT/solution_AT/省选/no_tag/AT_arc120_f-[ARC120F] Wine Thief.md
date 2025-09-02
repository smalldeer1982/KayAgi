# [ARC120F] Wine Thief

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc120/tasks/arc120_f

**問題 F と問題 F2 は同じ問題ですが、制約と実行時間制限が異なります。**

高橋君の倉庫には $ N $ 本のワインがあり、左右方向 $ 1 $ 列に並んでいます。左から $ i $ 番目のワインの美味しさは $ A_i $ です。  
 青木君は今からこの $ N $ 本のうち、ちょうど $ K $ 本を選んで盗みます。しかし、高橋君は注意深いので、以下の条件が満たされると盗まれたことに気付いてしまいます。

- 連続で並ぶ $ D $ 本のワインであって、そのうち $ 2 $ 本以上盗まれているようなものが存在する (この問題では $ D\ =\ 2 $ です)

高橋君に気付かれないような全ての盗み方について、盗んだワインの美味しさの和を求め、それを足し合わせた値を求めてください。  
 なお、答えは非常に大きくなることがあるので、$ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ D\ =\ 2 $
- $ 2\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ K\ \le\ \left\lceil\ \frac{N}{D}\ \right\rceil $ （$ \left\lceil\ x\ \right\rceil $ は $ x $ 以上の最小の整数を表す）
- $ 1\ \le\ A_i\ \lt\ 998244353 $
- 入力に含まれる値は全て整数

### Sample Explanation 1

盗み方と盗んだワインの美味しさの和は以下の通りです。 - 左から $ 1 $ 本目のワインと $ 3 $ 本目のワインを盗んだ場合 : 美味しさの和は $ 1\ +\ 2\ =\ 3 $ - 左から $ 1 $ 本目のワインと $ 4 $ 本目のワインを盗んだ場合 : 美味しさの和は $ 1\ +\ 3\ =\ 4 $ - 左から $ 2 $ 本目のワインと $ 4 $ 本目のワインを盗んだ場合 : 美味しさの和は $ 4\ +\ 3\ =\ 7 $ よって答えは $ 3\ +\ 4\ +\ 7\ =\ 14 $ となります。

### Sample Explanation 2

左から $ 1,\ 3,\ 5 $ 本目のワインを盗むほかありません。

## 样例 #1

### 输入

```
4 2 2
1 4 2 3```

### 输出

```
14```

## 样例 #2

### 输入

```
5 3 2
4 7 5 3 8```

### 输出

```
17```

## 样例 #3

### 输入

```
12 4 2
107367523 266126484 149762920 57456082 857431610 400422663 768881284 494753774 152155823 740238343 871191740 450057094```

### 输出

```
136993014```

# 题解

## 作者：翼德天尊 (赞：7)

首先很容易想到 dp，但是复杂度卡在了 $O(nk)$ 下不去，只能另谋出路。

考虑将序列变成环，收缩题目限制，即多加入 $a_1$ 和 $a_n$ 也不能够同时选的限制。此时贡献是好计算的，具体来说，有两种方式可以计算一个环的贡献：

- 考虑整体方案数。设 $g(i,j)$ 表示长度为 $i$ 的环，最多选 $j$ 个数，且所选数两两不相邻的方案数；$f(i,j)$ 表示长度为 $i$ 的序列，最多选 $j$ 个数，且两两不相邻的方案数。则如果考虑环上第一个数是否选择，显然可以有：$g(i,j)=f(i-1,j)+f(i-3,j-1)$。而 $f$ 的求解则是隔板法的经典问题，考虑将 $j$ 个数插入剩下 $i-j$ 个数的 $i-j+1$ 个空隙里，则有 $f(i,j)=C_{i-j+1}^{j}$。而又由于一个环上每个数被选择的次数均等，故每个数都会被选择 $\frac{g(i,j)\times j}{i}$ 次，将其与环上 $a_i$ 之和相乘即可。

- 考虑单独方案数。当 $a_i$ 被选择时，其在环上所在位置与相邻位置都无法再被选择，剩下的数可以随意选取，故此时有 $f(i-3,j-1)$ 种方案数包含 $a_i$。

于是我们便可以 $O(1)$ 快速求解一个环上所有方案的权值和了。

但显然此时我们还漏算了一部分贡献，即 $a_1$ 和 $a_n$ 同时被选择的所有方案的贡献。于是我们可以再将这一部分贡献加上：

- 这些方案中，$a_1$ 和 $a_n$ 会共同出现 $f(n-4,k-2)$ 次，计入贡献。

- 剩下的贡献便为序列 $[3,n-2]$ 中选择 $k-2$ 个数，且两两不相邻的子问题所造成的贡献，递归求解该子问题即可。

不难发现子问题的量级为 $O(n)$，故总时间复杂度为 $O(n)$。

注意一些边界情况即可。细节见代码。

**本题启发我们在求解问题时，可以考虑增强/减弱约束，使问题具有一些很好的性质而便于求解，再从两个问题的不同角度考虑修改解法以适应原问题。**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5;
const int mod=998244353;
int n,k,d;
ll a[N],s[N],sum,jc[N],inv[N];
int read(){
	int w=0,fh=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') fh=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*fh;
}
ll C(int x,int y){
    if (x<y) return 0;
    assert(x<=n&&y<=n);
    return jc[x]*inv[y]%mod*inv[x-y]%mod;
}
ll lin(int x,int y){
    return C(x-y+1,y);
}
ll cir(int x,int y){
    return (lin(x-1,y)+lin(x-3,y-1))%mod;
}
ll ksm(ll x,ll y){
    ll ans=1;
    while (y){
        if (y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
void init(){//预处理阶乘及逆元
    jc[0]=inv[0]=1;
    for (int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    inv[n]=ksm(jc[n],mod-2);
    for (int i=n-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
ll work(int x,int y,int l,int r){
    if (y<=0) return 0;
    int len=x;
    if (len==0) return 0;
    if (len==1) return a[l];
    if (len==2) return (a[l]+a[r])%mod;
    if (len==3) return (y==2)?(a[l]+a[r])%mod:(a[l]+a[l+1]+a[l+2])%mod;//一些边界情况
    ll ans=((s[r]-s[l-1]+mod)%mod*lin(x-3,y-1)%mod+work(x-4,y-2,l+2,r-2)+(a[l]+a[r])%mod*lin(x-4,y-2)%mod)%mod;
    return ans;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
#endif
    n=read(),k=read(),d=read();
    init();
    for (int i=1;i<=n;i++) a[i]=read(),s[i]=(s[i-1]+a[i])%mod;
    cout<<work(n,k,1,n)<<'\n';
    return 0;
}
```

---

## 作者：Caiest_Oier (赞：7)

# [AT_arc120_f](https://www.luogu.com.cn/problem/AT_arc120_f)    

枚举 $i$，强制钦定 $i$ 被选中，则贡献为 $A_i\times F_i$，$F_i$ 为强制选中 $i$ 的方案数。      

首先考虑如何计算 $f(i,j)$，即在 $i$ 个数中选不相邻的 $j$ 个的方案数。考虑在 $1$ 左边和 $i$ 右边补充两个格子，则选 $j$ 个不相邻的数将 $i+2-j$ 个格子划分为了 $j+1$ 段，使用插板法，得出 $f(i,j)=C_{i-j+1}^{j}$。       

再考虑如何计算 $F_i$。如果强制选中了 $i$，那么 $i-1$ 与 $i+1$ 都一定不被选中，将其从 $n$ 个数中删去，剩下 $n-3$ 个数中需要选 $k-1$ 个，方案就是 $f(n-3,k-1)$。但是这样会导致 $i-2$ 与 $i+2$ 不能同时选。于是再强制钦定 $i-2$，$i$，$i+2$ 都被强制选中，将 $[i-3,i+3]$ 全部删除，方案数加上 $f(n-7,k-3)$，这样直到左右两边扩展到边界为止。于是 $F_i$ 可以表示成 $\sum_{i=1}^{lim}f(n-i\times4+1,k-i\times2+1)$，这个可以前缀和预处理，于是就算完了，复杂度 $O(n+\log MOD)$。    

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,k,D,A[500003],ans,jc[600003],njc[600003],v[600003],k1,k2,k3,k4,k5,k6,k7;
int C(int X,int Y){
	if(X<0||Y<0||X<Y)return 0;
	return jc[X]*(njc[X-Y]*njc[Y]%MOD)%MOD;
}
int fstp(int X,int Y){
	int ret=1,bse=X;
	while(Y){
		if(Y&1)ret*=bse;
		bse*=bse;
		ret%=MOD;
		bse%=MOD;
		Y>>=1;
	}
	return ret;
}
int f(int X,int Y){return C(X+1-Y,Y);}
signed main(){
	ios::sync_with_stdio(false);
	jc[0]=1;
	for(int i=1;i<=600000;i++)jc[i]=jc[i-1]*i%MOD;
	njc[600000]=fstp(jc[600000],MOD-2);
	for(int i=599999;i>=0;i--)njc[i]=njc[i+1]*(i+1)%MOD;
	cin>>n>>k>>D;
	for(int i=1;i<=n;i++)cin>>A[i];
	for(int i=1;i<=n;i++)v[i]=(v[i-1]+f(n-4*i+1,k-(2*i-1)))%MOD;
	for(int i=1;i<=n;i++){
		k2=min(i/2,(n-i+1)/2);
		k1=v[k2];
		k3=i-(k2*2)+1;
		k4=i+(k2*2)-1;
		if(k2!=0&&k3!=1&&k4!=n)k1=(k1+f(n-(k4-k3+1)-2-(k4<(n-1))-(k3>2),k-(k2*2+1)))%MOD;
		if(k2==0)k1=(k1+f(n-2,k-1))%MOD;
		ans=(ans+A[i]*k1)%MOD;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Inui_Sana (赞：2)

感觉这题实际难度没有 at 评分那么高，给一个不从环的角度考虑的做法。

下文 $m$ 为题面中 $k$。

考虑固定一个 $i$ 算 $a_i$ 的贡献。如果直接枚举一边的个数就得到了讨论区里的式子，比较难做。于是就需要把两边**放在一起考虑**。

具体地，考虑当前既然钦定 $i$ 选了，那 $i+1$ 和 $i-1$ 都不能选，于是把 $[1,i-2]$ 和 $[i+2,n]$ 拼起来算选 $k-1$ 个的方案数。但是同时又发现，$i-2$ 和 $i+2$ 可以同时选。于是考虑在中间新插入一个元素，值为 $0$，再去算方案数。

此时又有一个问题：如果选了那个新插入的元素，那么实际上在原序列中就只选了 $m-2$ 个元素。于是考虑再容斥掉，减去一定选了这个元素，其他位置一共选了 $m-2$ 个的方案数。不难发现这是一个子问题。

于是考虑设 $Solve(x,y,k)$ 表示当前钦定要选的点左边（也就是类似上文的 $[1,i-2]$）还有 $x$ 个元素，右边有 $y$ 个，还要从中选 $k$ 个。则选中 $i$ 的方案数为 $Solve(i-2,n-i-1,m-1)$。$Solve$ 大概长这样：

```cpp
int solve(int x,int y,int k){
	if(x>y){
		return solve(y,x,k);
	}
	if(!x){
		return binom(y-k+1,k);
	}
	return Mod(binom(x+y-k+2,k),mod-solve(x-1,y-1,k-1));
}
```

其中显然有无用信息，注意到每次组合数的值只和 $x+y$ 和 $k$ 有关，只有迭代次数和 $\min(i-2,n-i-1)$ 有关。于是简化一下，变成循环的形式就是：

```cpp
int j=m-1,k=n-3,p=1;
for(j=m-1,k=n-3,p=1;j>=m-x+1;j--,p^=1,k-=2){
  if(p){
    sum=Mod(sum,binom(k-j+2,j));
  }else{
    sum=Mod(sum,mod-binom(k-j+2,j));
  }
}
if(p){
  sum=Mod(sum,binom(k-j+1,j));
}else{
  sum=Mod(sum,mod-binom(k-j+1,j));
}
```
其中 $j$ 为还要选的个数，$k$ 为当前序列长度，$p$ 表示正负性。

再发现 $i$ 只会限制代码中 $j$ 的范围。于是预处理 $f_i=\sum_{i\le j\le m-1}(-1)^{m-j+1}\binom{k-j+1}{j}$ 就可以把循环部分干掉了。

总复杂度 $O(n)$。

code：

```cpp
int n,m,k,a[N],f[N];
int fac[N],ifac[N];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int binom(int x,int y){
	if(x<0||y<0||x<y){
		return 0;
	}
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void init(int n){
	fac[0]=1;
	rep(i,1,n){
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	ifac[n]=qpow(fac[n],mod-2);
	drep(i,n-1,0){
		ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	}
}
void Yorushika(){
	read(n,m,k);
	init(n);
	int ans=0;
	for(int j=m-1,k=n-3,p=1;j>=m-n+1;j--,p^=1,k-=2){
		if(p){
			f[j+n]=Mod(f[j+n+1],binom(k-j+2,j));
		}else{
			f[j+n]=Mod(f[j+n+1],mod-binom(k-j+2,j));
		}
	}
	rep(i,1,n){
		read(a[i]);
		if(i==1||i==n){
			ans=Mod(ans,1ll*a[i]*binom(n-m,m-1)%mod);
		}else{
			int x=i-1,y=n-i;
			if(x>y){
				swap(x,y);
			}
			int sum=f[m-x+n+1],j=m-1,k=n-3,p=1;
			j-=x-1,p^=(x-1)&1,k-=2*(x-1);
			if(p){
				sum=Mod(sum,binom(k-j+1,j));
			}else{
				sum=Mod(sum,mod-binom(k-j+1,j));
			}
			ans=Mod(ans,1ll*a[i]*sum%mod);
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：EuphoricStar (赞：2)

Hint：如果是一个环怎么做？

Answer：由于是一个环，因此环上每个点对最终答案造成的贡献都相同。设 $f_{i,j}$ 为长度为 $i$ 的序列选 $j$ 个不相邻的点的方案数，则 $f_{i,j} = \binom{i-j+1}{j}$。应该很好理解，考虑一个长度为 $i-j$ 的链，链头、链尾和两个数之间都可以插入一个元素，总共需要插入 $j$ 个，因此方案数是 $\binom{i-j+1}{j}$。每个点对答案的贡献为 $a_i \times f_{n-3,k-1}$（就是钦定这个点不选，断环为链）。

这启发我们在环的基础上考虑。发现除了环的答案，链的要多考虑两端都选的方案。设 $g_{i,j,k}$ 为在 $[i,j]$ 的链选 $k$ 个不相邻的点的答案。令 $len = j - i + 1$，那么：

$$g_{i,j,k} = f_{len-3,k-1} \times (\sum\limits_{p=i}^j a_p) + f_{len-4,k-2} \times (a_i + a_j) + g_{i+2,j-2,k-2}$$

第一部分是环的答案，后面是钦定选 $a_i,a_j$，$[i+2,j-2]$ 选点的方案为 $f_{len-4,k-2}$，作为系数乘上 $a_i + a_j$，最后再递归下去。

时间复杂度 $O(n)$。

[code](https://atcoder.jp/contests/arc120/submissions/40962161)

---

## 作者：Otue (赞：1)

## [[ARC120F] Wine Thief](https://www.luogu.com.cn/problem/AT_arc120_f)

### 题目大意

给定含有 $n$ 个元素的序列 $A$，现在要求选出含有 $k$ 个元素的子序列，满足不能存在在原序列 $A$ 中相邻的元素。问所有可能的子序列的权值和。

### 题目思路

这道题非常妙。首先我们把序列限制强化成环形限制，即要求 $a_1$ 和 $a_n$ 也不能相同。强化限制做更简单，其实数学中也有很多这样的思维。

定义 $f(i,j)$ 表示前 $i$ 个数中选择 $j$ 个数的方案数，同时定义 $g(i,j)$ 表示前 $i$ 个环形数中选择 $j$ 个数的方案数（即要求 $a_1$ 和 $a_i$ 不相同）。容易发现 $g(i,j)<f(i,j)$ 因为限制更强。同时我们根据组合数学得到 $f(i,j)=\binom{i-j+1}{j}$。转移 $g$ 数组有 $g(i,j)=f(i-1,j)+f(i-3,j-1)$。

可以知道，在环形序列上，每一个 $a_i$ 被选择的频率是相同的，那么可以得到每个 $a_i$ 都被选择了 $\dfrac{k\times g(i,j)}{n}$ 次。那么先把答案累计上 $(\sum \limits _{i=1}^{n} a_i)\times (\dfrac{k\times g(i,j)}{n})$。

因为环形序列少计算了两端同时选择的贡献，则还需要计算选了 $1$ 和 $n$ 的情况，那么此时先将 $1$ 和 $n$ 对答案造成的贡献提前计算出来，然后就可以再规约成 $[3,n-2]$ 中选择 $k-2$ 个的子问题答案，递归处理。可以得知复杂度 $O(n)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc120_f)

**题目大意**

> 给定 $a_1\sim a_n$，求所有大小为 $k$ 的链上独立集的 $a$ 元素之和。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

设独立集个数为 $f(n,k)=\binom{n-k+1}k$

注意到链上独立集并不具有对称性，而环上独立集有较好的性质，每个点被选入独立集的方案都相同，都是 $f(n-2,k-1)$。

回到原问题，未计算的情况一定同时选择了 $a_1,a_n$。

这种独立集一共有 $f(n-4,k-2)$ 个，$a_1,a_n$ 的系数也是这个。

我们只要考虑这种独立集中 $a_3\sim a_{n-2}$ 中的 $a_i$ 贡献，容易发现所有选择 $a_1,a_n$ 的 $k$ 元独立集和 $a_3\sim a_{n-2}$ 中的 $k-2$ 元独立集一一对应。

因此我们只要递归 $a_3\sim a_{n-2},k-2$ 递归算一遍原问题答案即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5,MOD=998244353;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll a[MAXN],s[MAXN],fac[MAXN],ifac[MAXN];
ll g(int n,int m) {
	if(m<0||n<2*m-1) return 0;
	return fac[n+1-m]*ifac[m]%MOD*ifac[n+1-2*m]%MOD;
}
ll f(int l,int r,int k) {
	if(k<=1) return k*(s[r]+MOD-s[l-1])%MOD;
	return ((s[r]-s[l-1])*g(r-l-2,k-1)+(a[l]+a[r])*g(r-l-3,k-2)+f(l+2,r-2,k-2))%MOD;
}
signed main() {
	for(int i=fac[0]=ifac[0]=1;i<MAXN;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	int n,k,d;
	scanf("%d%d%d",&n,&k,&d);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),s[i]=(s[i-1]+a[i])%MOD;
	printf("%lld\n",f(1,n,k));
	return 0;
}
```

---

## 作者：naught (赞：0)

# [ARC120F] Wine Thief

## 题外话

“求和”看成“求有多少个不同值”，卡了许久，收获良多。

## 题面翻译

给定含有 $n$ 个元素的序列 $\{A\}$，从中选出 $k$ 个不相邻的数，求所有可能的和。

## Solution

直接做还是太难了，于是考虑先做简单版：如果是在环上选的呢？

定义 $f_{i,j}$ 为选到第 $i$ 个点，选择了 $j$ 个点的和，值为 $\binom{i-j+1}{j}$。

因为是在环上，所以每个点对答案的贡献都是一样的，值为 $a_i \times f_{n-3, k-1}$，进行递推即可。

这时候再转回来思考对于序列的操作，发现除了两端都选之外，情况与环上无异。

令 $F_{l, r, k}$ 为在区间 $[l, r]$ 中选 $k$ 个数字的价值，令 $len = r-l+1$，则：

$$

F_{l, r, k} = f_{len-3, k-1} \times (sum_r-sum_{l-1}) + f_{len-4, k-2} \times (a_l+a_r) + F(l+2, r-2, k-2)。

$$

时间复杂度为 $O(n)$ 的 dp。

## 代码
```cpp
// written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 300005
#define Mod 998244353
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

ll hts(ll a, ll b)
{
    ll res = 1;
    while(b)
    {
        if(b&1) (res *= a) %= Mod;
        (a *= a) %= Mod, b >>= 1;
    }
    return res;
}

int n, k, a[Maxn];
ll fac[Maxn], inv[Maxn], sum[Maxn];

void Init(ll n)
{
    fac[0] = 1;
    fo(i, 1, n) fac[i] = fac[i-1]*i%Mod;
    inv[n] = hts(fac[n], Mod-2);
    fr(i, 0, n-1) inv[i] = inv[i+1]*(i+1)%Mod;
}

ll C(ll i, ll j) {return fac[i]*inv[j] %Mod * inv[i-j] %Mod;}

ll F(ll l, ll r, ll k)
{
    if(k == 0) return 0;
    if(k == 1) return (sum[r]-sum[l-1]+Mod) % Mod;
    ll len = r - l + 1;
    return (C(len-1-k, k-1) * (sum[r]-sum[l-1]+Mod) % Mod + C(len-1-k, k-2) * (a[l]+a[r]) % Mod + F(l+2, r-2, k-2)) % Mod;
}

int main()
{
    Init(Maxn-5);
    n = read(), k = read(), a[1] = read();;
    fo(i, 1, n) a[i] = read(), sum[i] = (sum[i-1]+a[i]) % Mod;
    printf("%lld", F(1, n, k));
    return 0;
}
```

## Tips

记得考虑边界。

---

## 作者：gan1234 (赞：0)

### ARC120F Wine Thief

首先我们要知道 $n$ 个点选 $k$ 个不相邻点的方案数 $f_{n,k}$，插板法可求出为 $f_{n,k}=\binom{n-k+1}{k}$。

考虑枚举 $a_i$，然后乘上它两边选的方案数就是 $a_i$ 的贡献。

选了 $a_i$ 后两边有两种选法：

- 不同时选 $a_{i-2},a_{i+2}$，此时方案数等价于直接将两边拼起来，再去选，为 $f_{n-3,k-1}$。

- 钦定同时选 $a_{i-2},a_{i+2}$，此时需要删去 $a_{i-2},a_{i-3},a_{i+2},a_{i+3}$ 四个点，然后递归子问题。

我们定义像上面每删去四个点为扩张一次。

令 $g_i$ 表示像这样向外扩张 $i$ 次的方案数，此时还剩 $n-4i+1$ 个点和 $k-2i+1$ 个要选的点，我们有： 

$$g_i=f_{n-4i+1,k-2i+1}+g_{i+1}$$

其中 $g_i=0,i>n$。

考虑如何处理扩张到边界后的边界问题。

令 $j$ 为点 $i$ 最多能向外扩张的次数，显然 $j=\min(\lfloor\frac{\min(i-1,n-i)}{2}\rfloor,\lfloor\frac{k-1}{2}\rfloor)$。

进行过 $j$ 轮后，我们应当停止扩张，因为此时已经无法再两边各删去四个点了，此时两段区间一定有一边少于两个点。

令 $t1=\max(\min(i-2j-1,n-i-2j)-1,0),t2=\max(\max(i-2j-1,n-i-2j)-1,0)$ 表示较少的一段区间点数和较多的一段区间点数。

将 $t1$ 分 $0,1$ 两种情况分类讨论，我们可以得到：

$$g_1-g_{j+1}+f_{t2,k-2j-1}+t1f_{t2,k-2j-2}$$

所以答案就是：

$$\sum^n_{i=1}(g_1-g_{j+1}+f_{t2,k-2j-1}+t1f_{t2,k-2j-2})a_i$$

---

