# [AGC020F] Arcs on a Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc020/tasks/agc020_f

長さ $ C $ の円周があり、この上に $ N $ 本の円弧を配置します。円弧 $ i $ の長さは $ L_i $ です。

それぞれの円弧 $ i $ は、円周上の一様ランダムな位置に配置されます。 すなわち、円周上のランダムな点が選ばれ、その点を中心とした長さ $ L_i $ の円弧が出現します。

これらの円弧は、それぞれ独立に配置されます。例えば、円弧が交差したり、ある円弧が別の円弧を含むことがあります。

円周上のすべての点が少なくとも一本の円弧で覆われる確率はいくらでしょうか？ 円弧はその両端も覆うものとします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 6 $
- $ 2\ \leq\ C\ \leq\ 50 $
- $ 1\ \leq\ L_i\ <\ C $
- 入力値はすべて整数である。

### Sample Explanation 1

二本の円弧の中心間の距離が $ 1 $ 以上でなければなりません。長さ $ 3 $ の円周上でそのようになる確率は $ 1\ /\ 3 $ です。

### Sample Explanation 2

円弧の長さの合計がちょうど $ C $ であり、円周上のすべての点が少なくとも一本の円弧に覆われることはありえますが、この事象の発生確率は $ 0 $ です。

## 样例 #1

### 输入

```
2 3
2 2```

### 输出

```
0.3333333333333333```

## 样例 #2

### 输入

```
4 10
1 2 3 4```

### 输出

```
0.0000000000000000```

## 样例 #3

### 输入

```
4 2
1 1 1 1```

### 输出

```
0.5000000000000000```

## 样例 #4

### 输入

```
3 5
2 2 4```

### 输出

```
0.4000000000000000```

## 样例 #5

### 输入

```
4 6
4 1 3 2```

### 输出

```
0.3148148148148148```

## 样例 #6

### 输入

```
6 49
22 13 27 8 2 19```

### 输出

```
0.2832340720702695```

# 题解

## 作者：Kinandra (赞：29)

标签: 状压DP, 神奇套路.

这道题的做法感觉很经典, 又或者说很套路, 然而我只做过一道这种套路的题;)

首先**断环为链**, 以最长的弧的起点作为链的起点(同时也是链的终点), 由于将环的的问题转化为了线段的问题, 下面将**弧**描述为**线段**.

然后由于坐标的连续性为求解带来的困难, 我们需要将坐标**离散化**, 套路化的方法是将坐标 $x$ 分为整数部分 $a$ 和小数部分 $b$ , 对小数部分进行离散化(不知道这么表述是否准确). 

试图揣摩一下这么离散化的思路: 本题研究的是线段相交的问题, 这个涉及到这两弧端点之间的坐标差. 更深入地, 由于**线段的长度为整数**, 两线段相交只与坐标整数部分的**数值**和小数部分的**相对大小**有关, 即我们不在乎小数部分的具体数值, 故将其离散化(整数部分本身具有离散性, 不需要特别处理).

也就是说, 如果线段的长度是没有特殊性质的实数这么离散化就不行了.

离散化之后, 坐标变为 $nc$ 个, 这个问题就可以比较容易的解决了. $\mathcal O(n!)$ 地枚举各个线段**小数部分的相对大小**, 然后状压Dp一下就好了. 

具体的, 设 $f[i][j][s]$ 表示左端点坐标(离散化后的, 下同)不大于 $i$ 的线段已经放置完毕, 覆盖到的最大的坐标为 $j$ , 线段的是否放置的状态为 $s$ 的方案数. 转移就枚举是否以 $i$ 为左端点放置线段 $x$ , 这样分别转移到 $f[i+1][j][s]$ 和 $f[i+1][max(j,to[x][i])][s\cup\{x\}]$ , 其中 $to[x][i]$ 表示在以 $i$ 为左端点放置 $x$ , $x$ 右端点的坐标. 注意由于我们限定了小数部分的相对大小, 每一处可以放置的线段 $x$ 只有一条, 所以转移是 $\mathcal O(1)$ 的.

时间复杂度 $\mathcal O(2^n\times n!\times(nc)^2)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, c, l[51];
double f[502][102], res, cnt;
int main() {
    n = read(), c = read();
    for (int i = 0; i < n; ++i) l[i] = read();
    sort(l, l + n);
    while (1) {
        for (int i = 0; i <= c * n; ++i)
            for (int s = 0; s < (1 << n - 1); ++s) f[i][s] = 0;
        f[l[n - 1] * n][0] = 1;
        for (int i = 1, p; i <= c * n; ++i) {
            if ((p = i % n - 1) < 0) continue;
            for (int j = i; j <= c * n; ++j)
                for (int s = 0; s < (1 << n - 1); ++s)
                    if (~s >> p & 1)
                        f[min(c * n, max(j, i + l[p] * n))][s | (1 << p)] +=
                            f[j][s];
        }
        res += f[c * n][(1 << n - 1) - 1], ++cnt;
        if (!next_permutation(l, l + n - 1)) break;
    }
    printf("%.13lf\n", (double)res / cnt / pow(c, n - 1));
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```


---

## 作者：skydogli (赞：24)

WC的时候lyx大神优化的一道题……不过讲得比较粗枝大叶，于是小蒟蒻来补一点细节。

首先，我们钦定边长最大的边的左端点为起点，这样我们就可以断环为链了。

然后，假设精度要求极低，我们尝试用离散的DP解决此题（也就是线段只能在端点上）。令 $f_{st,i}$ 表示用了哪些线段，目前覆盖了 $[0,i]$ 这段区间，从小到大枚举起点后先枚举线段再枚举集合（也就是子集前缀和的顺序）帮助转移即可。

不难发现，只要我们不断将线段细分，就能得到更高的精度，当段数为无穷大时，可以认为是没有精度误差的。

接下来是一个很重要的结论：令分段数为 $m$ ，自主放置的线段数为 $n$，合法的放置线段的方案数是一个关于 $m$ 的 $n$ 次多项式，因为线段总数才 $n$ 条，不可能存在更高次的系数。

~~如果有更加理性、直观的证明，请您不吝赐教。~~

也就是我们现在想求出一个 $n$ 次多项式，只要代入 $n+1$ 个值，就能拉格朗日插值插出这个多项式了，将 $m=c\dots (n+1)c$ 代入即可。

接下来，我们看看我们要求的答案是什么

$$ans=\lim_{m\to \infty} \frac{f(m)}{m^n}$$

不难发现，这其实就是第 $n$ 次项的系数。

$n$ 这么小，直接 $O(n^2)$ 插值求单项即可，插值时注意次数和点值的细节。总体时间复杂度$O(2^nn^4L^2)$ 。

好像复杂度能更优……先去试试

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int a=0,fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a*fh;
}
const int MN=505;
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define vc vector
int n,c,l[11];
int f[1<<5][MN],tot[1<<5];
double y[11];
signed main(){
	n=read();c=read();
	for(int i=0;i<n;++i)l[i]=read();
	sort(l,l+n);
	for(int i=0;i<(1<<n-1);++i){
		for(int j=0;j<n-1;++j)
			if((i>>j)&1)tot[i]+=l[j];		
	}
	for(int m=1;m<=n;++m){
		for(int i=0;i<(1<<n-1);++i)
			for(int j=0;j<=c*m;++j)
				f[i][j]=0;
		f[0][l[n-1]*m]=1;
		for(int i=0;i<m*c;++i){
			for(int p=0;p<n-1;++p)
				for(int st=0;st<(1<<n-1);++st){
					if(!((st>>p)&1)){
						int N=max(i+l[n-2]*m,l[n-1]*m);
						for(int j=max(i,l[n-1]*m);j<=c*m&&j<=N;++j)if(f[st][j]){
							int to=min(c*m,max(j,i+l[p]*m));
							f[st|(1<<p)][to]+=f[st][j];
						}
					}
			}
		}
		y[m]=f[(1<<n-1)-1][c*m];
	}
	double s=0;
	for(int i=1;i<=n;++i){//注意有1个线段固定了
		double C=1;
		for(int j=1;j<=n;++j){
			if(i==j)continue;
			C*=(i*c-j*c);//注意，我们代入的点值是c...(n+1)*c，而不是1...n+1
		}
		s+=y[i]/C;
	}
	printf("%.12lf",s);
	return 0;
}
```


---

## 作者：zhouhuanyi (赞：9)

一个和值域无关的算法，复杂度 $O(4^nn^2)$，不过好像可以用子集卷积和拉格朗日插值优化至 $O(3^nn^3)$。

如果说原问题在整数上做，我们通常可以用生成函数来刻画容斥的式子，求个二维 $\exp$ 状物就可以了，但是在实数域似乎不太好扩展，但实际上是可以扩展的。

原问题实际上可以抽象为类似连通子图计数的东西，因为环计数实际上就是链计数乘上第一段的长度，而要求第一段为连通块，而连通块具有和连通子图相似的性质，求个类似 $\ln$ (其实并不是 $\ln$)，就可以了。特别的，如果不存在一个弧跨过 $C$ 到 $0$ 这部分时是数不到的，但这部分是平凡的，就是 $\prod_{i=1}^{n}\frac{C-l_{i}}{C}$。而能通过我们以如上方式数到的都是不合法的方案，因为合法的方案不存在任何一个断开位置。

现在我们只需要求连通块的 $\text{GF}$ 点乘上 $\frac{x}{C}$，再与原来的相乘即可就行了，但卷积如何刻画呢？由于直接用概率来描述似乎比较奇怪，我们采用几何概型的思想，将其视为求体积，虽然是高维的。

一个平凡的想法是令 $F_{S}(x)$ 表示 $S$ 集合的长度为 $x$ 内选择的体积和，令 $G_{S}(x)$ 表示 $S$ 集合的长度为 $x$ 内选择的并要求构成一个连通块的体积和，那么有 $G_{S}(x)=F_{S}(x)-\sum_{T\subsetneqq S,T\not=\emptyset} F_{T}(x)*G_{\complement_ST}(x)$，其中 $F(x)*G(x)=\int_{0}^{x}F'(y)G(x-y)dy$(注意其中求导所丢失的常数项要特殊处理)。一开始 $F_{S}(x)$ 其实是一个分段多项式，因为有要求 $x\geqslant \max_{i\in S}l_{i}$，不难发现进行运算后 $F_{S}(x)$ 的段数最多是 $2^{|S|}-1$ 的，因为每一个段的界点其实都形如 $T\subset S,T\not=\emptyset$ 的一个集合 $T$ 的和 $W(T)$ (即 $\sum_{x\in T}l_{x}$)，那么实际上我们可以令 $F_{S}(x)=\sum_{T\subset S,W(T)\leqslant C}f_{S,T}(\frac{C-W(T)}{C})$，则 $f$ 就是一个多项式了。

现在我们只需要能求两个多项式的 $*$，就可以求解两个函数的 $*$ 了，我们要快速计算 $h=f*g$ 即 $h(x)=\int_{0}^{x}f'(y)g(x-y)dy$，如果直接使用暴力二项式定理展开对展开的分别积分可以算出 $R(a,b)$ 表示 $x^a$ 与 $x^b$ 贡献到 $x^{a+b}$ 的贡献，将 $R$ 打表之后会发现一个神奇的事情，$R(x,y)=\frac{1}{\binom{x+y}{x}}$，这是为什么呢？实际上我们发现我们的 $*$ 运算其实和第一类欧拉积分非常的相似，而贝塔函数在非负整数部分的取值和组合数倒数有一定关联，对 $f$ 的导将其变成了一个更加优美的形式:$\frac{1}{\binom{x+y}{x}}$。

像定义 $\text{EGF}$ 一样，我们可以定义一个和积分有关的生成函数 $\text{IGF}$，满足 $f(x)=\sum_{i=0}^{\infty}a_{i}i!x^i$，这样就可以把多项式的四则运算以及开根求导积分 $\ln,\exp$ 等东西全部放上去。

现在将 $G$ 求好了，但如何将其点乘上 $x$ 本身呢，注意到令 $H$ 为 $G$ 的两侧都被覆盖的面积，那么 $G(x)=\int_{}\int_{}H(x)d^2x$，而我们最终要其实就是 $\int_{}H(x)xdx$，所以我们求 $\int_{}G''(x)xdx$ 即可 (这里一次项需要修正，常数项不用是因为在本题限制下常数项一定为 $0$)，由于这个算的是第一段，可能还有后面的，令 $T(x)=\int_{}G''(x)xdx$，我们算出 $T+T*F$ 就是最终的 $\text{GF}$ 形式了。

由于 $F$ 只有一段，枚举子集与其中一个子集构成的段的复杂度是 $O(4^n)$，暴力卷积是 $O(n^2)$ 的，所以是 $O(4^nn^2)$ 的。但似乎子集部分可以子集卷积，拉格朗日插值可以优化掉暴力卷积，于是可以 $O(3^nn^3)$，用 $\text{poly}$ 优化掉子集卷积的暴力卷积可以 $O(3^nn^2\log n)$，但是由于 $n$ 不得不比较小，可能不如暴力卷积。

特别的，该做法在值域非常小的时候可以将段给换成值域，这样里面的枚举子集可以优化掉。另外 $\text{PKUSC2021 D2T3}$ 招新也可以用同样的方法不带值域，做到暴力卷积 $O(n^6)$，三维 $NTT$ 优化可以 $O(n^3 \log n)$，实际上就是把这个东西拼上一个有标号二分图计数的 $\text{trick}$。

---

## 作者：tzc_wk (赞：8)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Atcoder 题面传送门](https://atcoder.jp/contests/agc020/tasks/agc020_f) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT3860)

~~一道难度 unavailable 的 AGC F 哦~~

首先此题最棘手的地方显然在于此题的坐标可以为任意实数，无法放入 DP 的状态，也无法直接计算概率。我们考虑是否能将实数坐标转化为我们熟知的整数坐标。这里有一个套路，注意到**每条弧的长度都是整数**这个条件，考虑两个坐标 $A,B$，显然以 $A$ 开始的长度为 $l$ 的弧能覆盖到 $B$ 当且仅当 $\lfloor B\rfloor-\lfloor A\rfloor<l$，或者 $\lfloor B\rfloor-\lfloor A\rfloor=l$ 且 $(B-\lfloor B\rfloor)<(A-\lfloor A\rfloor)$。这就告诉我们，坐标的小数部分具体是什么并不重要，我们只关心它们的**相对大小**。又因为小数部分为取值范围为 $[0,1)$ 的连续性变量，因此出现两点小数部分相同的概率可以视作 $0$，因此我们**暴力枚举这 $n$ 条线段小数部分的相对大小**——共有 $n!$ 种可能的情况，它们是等可能的（yyq 既视感），计算出它们覆盖整个圆周的概率后除以 $n!$ 即可。

接下来考虑给定这 $n$ 条线段小数部分的相对大小后怎样计算概率，首先我们固定住一条线段的位置，这样即可实现**断环成链**，其次由于我们已经知道了它们的相对大小了，所以最多只可能有 $nc$ 个起点位置，故可将 $c$ 个坐标拆成 $nc$ 个并将线段覆盖转化为点覆盖——这个异常容易理解。我们强制要求小数部分相对大小排名为 $k$ 的线段只能在 $tn+k(t\in\mathbb{Z})$ 的位置作为起始位置。这样就可以 $dp$ 了，设 $dp_{i,j,k}$ 表示现在覆盖了起点坐标 $\leq i$ 的线段，当前覆盖到的右端点的最大值为 $j$，当前使用的线段集合为 $k$（这个状态设计感觉有点像[此题](https://www.luogu.com.cn/problem/CF559E)），转移就分 $i$ 处不放线段和放线段两种情况转移即可，显然如果 $i$ 处放线段，那放置的线段是唯一的（$i\bmod n$），因此总复杂度 $n!\times 2^n\times n\times c$，由于此题 $n$ 数据范围极小，可通过此题。

最后值得一提的是不少题解都没有提到一点，就是为什么一定要强制令**长度最大的线段**的起点为圆周的起始位置，这里稍微讲下，因为假设我们用一个长度较小的线段作为圆周的起始位置，根据我们的 DP 过程可知对于线段超过断成的链的部分我们会直接忽略，但有可能会出现长度较大的线段从链的末尾开始覆盖，由于这是一个圆周，因此多出的部分又绕回链的开头，补上链开头线段覆盖的空隙的情况，这种情况是不会被我们纳入总方案的，不过 in fact 这种方案也是合法的。而使用长度最大的线段作为开头就恰好避免的这种情况，因此需要强制令长度最大的线段的起点为圆周的起始位置。

~~似乎 WC2021 的时候 lyx 神仙给出了一个更优秀的解法，要什么高级插值技巧什么的，not for me，thx~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=6;
const int MAXC=50;
int n,l[MAXN+2],c,p[MAXN+2];
ll dp[MAXN*MAXC+5][(1<<MAXN)+5];
int main(){
	scanf("%d%d",&n,&c);ll ret=0;
	for(int i=0;i<n;i++) scanf("%d",&l[i]),p[i]=i;
	sort(l,l+n);reverse(l,l+n);
	do {
		memset(dp,0,sizeof(dp));dp[l[p[0]]*n][1]=1;
		for(int i=1;i<n*c;i++) for(int j=i;j<=n*c;j++){
			int t=i%n;
			for(int k=0;k<(1<<n);k++) if(~k>>t&1)
				dp[min(n*c,max(j,i+l[p[t]]*n))][k|(1<<t)]+=dp[j][k];
		} ret+=dp[n*c][(1<<n)-1];
	} while(next_permutation(p+1,p+n));
	double ans=ret;//printf("%lld\n",ret);
	for(int i=1;i<=n-1;i++) ans=1.*ans/i;
	for(int i=2;i<=n;i++) ans=1.*ans/c;
	printf("%.17lf\n",ans);
	return 0;
}
```



---

## 作者：樱雪喵 (赞：7)

Tags: 状压，离散化，期望

从不知道多长时间以前的杂题选讲翻出来的。当时貌似没看懂题解在讲什么。

先断环为链，并以**最长线段的起点**作为整条链的起点。那么我们只需要让这条链上 $[0,n)$ 的位置都被覆盖就行了。

>如果没有选最长线段做起点，可能出现一条线段把起点线段覆盖住的情况，这样也是合法的，但并没有按上述条件覆盖 $[0,n)$ 的位置。下图是一个例子。  
![](https://cdn.luogu.com.cn/upload/image_hosting/o551b4sw.png)

然后这个问题的瓶颈在于坐标可以是实数。  
但因为长度都是整数，我们只需要知道两条线段起点的**整数部分**和**小数部分的相对大小关系**就可以判断它们是否相交。

这启发我们枚举每条线段之间小数部分的大小关系，并将其离散化。那么我们拥有了 $nc$ 个整数坐标，线段只能分布在其小数部分对应的整数坐标上。

这样就可以把坐标塞进 dp 状态了：设 $f_{i,j,s}$ 表示考虑了左端点坐标不超过 $i$ 的线段，覆盖了 $[0,j]$ 的所有位置，使用过的线段集合为 $s$ 的方案数。

因为放线段随机，所以每种小数部分大小关系概率相等，可以计算出对应的期望贡献。

时间复杂度 $O(n!2^n(nc)^2)$，不过 $n$ 只有 $6$，能过。

```cpp
const int N=55;
int n,c,a[N],vis[N],jc[N],tot;
int f[N*6][(1<<6)+5];
double ans;
il double qpow(double n,int k)
{
    double res=1;
    for(;k;n=n*n,k>>=1) if(k&1) res=res*n;
    return res;
}
int main()
{
    n=read(),c=read();
    for(int i=0;i<n;i++) a[i]=read();
    sort(a,a+n);
    do
    {
        tot++;
        memset(f,0,sizeof(f));
        f[a[n-1]*n][0]=1;
        for(int i=1;i<=c*n;i++)
        {
            if(i%n==0) continue;
            for(int j=i;j<=c*n;j++)
            {
                for(int s=0;s<(1<<n-1);s++)
                {
                    int x=i%n-1;
                    if(s>>x&1) continue;
                    f[min(c*n,max(j,i+a[x]*n))][s^(1<<x)]+=f[j][s];
                }
            }
        }
        ans+=f[c*n][(1<<n-1)-1];
    }while(next_permutation(a,a+n-1));
    printf("%.12lf\n",1.0*ans/tot/qpow(c,n-1));
    return 0;
}
```

---

## 作者：Illusory_dimes (赞：5)

~~范围越小题越神，这是一道难度问号题哦。~~

复盘 $\color{black}{\text{n}}\color{red}{\text{ealchen}}$ 神仙讲的题。

## Description

你有一个长度为 $C$ 的圆，你在上面画了 $n$ 个弧，长度为 $l_i$ 。

现在所有弧随机分布在圆上（坐标集为实数），求圆的每一个实点被至少一个弧覆盖的概率是多少？

$2 \leq n \leq 6,\ 2 \leq C \leq 50,\ l_i < C$

## Analysis

这个范围有点让我们不知所措呵。

注意到坐标可以是实数，我们是肯定不能做到把所有实数拿来当候选坐标的。

然后有个 trick （？）大概就是对于每个整数 $k$ ，分成 $n$ 份，可以理解为把所有 $n$ 个点坐标的小数部分拎出来离散化。

（因为弧长是整数所以两端小数部分相等所以才可以这样做）

所以我们直接把原来的长度 $C$ 变成了 $nC$ 个点。

还注意到这是一个圆，开始和结尾交合的地方比较麻烦，有注意到这个和顺序没有关系，所以我们可以直接先摁上去一个弧，这样就可以断链为环了。

剩下看起来就比较好处理了（

## Sol1

其实局面已经比较明显了，我们可以通过枚举每个弧小数部分相对大小，然后用状压 $\text{DP}$ 解决剩下的问题。

我们设 $f_{i, S, j}$ 表示在长度不超过 $i$ 的弧放置完毕，弧的选择状态集合为 $S$ ，覆盖到的最远坐标在 $j$ 的方案数。

转移从 $i$ 到 $i + 1$ 需要放置新的弧，枚举放置的起始点，更新一下最远距离就可以转移了。

大概就是：

$$f_{i, S, j} \rightarrow f_{i + 1, S \cup \{x\}, \max(j,\ k + len \cdot n)}$$

算好了方案数，除以总方案数就行了： $(n - 1)! \cdot c ^ {n - 1}$ （主要我们一开始定了一个点）。

时间复杂度 $O(2 ^ {n - 1} \cdot (nC) ^ 2 \cdot (n - 1)!)$ 。

## Sol2

据说来自 $\color{black}{\text{E}}\color{red}{\text{I}}$ ，反正很神仙就是了。

我们发现枚举小数部分相对大小有点浪费，考虑直接把小数部分排名也压进 $f$ 里面，形如 $f_{i, S, j, p}$ 表示在长度不超过 $i$ 的弧放置完毕，弧的选择状态集合为 $S$ ，覆盖到的最远坐标在 $j$ ，最远弧小数部分大小排名 $p$ 的方案数。

这样的话，更新最远距离的同时，要同时更新对应的排名，大概就是：

$$f_{i, S, j, p} \rightarrow f_{i + 1, S \cup \{x\}, \max(\{j,\ p + [q \leq p] \},\ \{k + len \cdot n,\ q\})}$$

中括号就是插进来新的大小比自己小的小数排名的更新。

但是还有一个细节，我们需要的是整个都被覆盖，但是如果在同一个“1”内，前面的结束端点小数部分比后面开始端点的小数部分小，实际上是并没有覆盖完全的，需要排除掉。

大概就是 i - 1 的结束端点等于 i 的起始端点，且前者小数部分大小排名小于后者的，直接跳过。

时间复杂度精细实现可以做到 $O(2 ^ {n - 1} \cdot C ^ 2 n ^ 3)$ 。

## ~~Sol3~~

插值做法？不会。但是理想时间复杂度似乎比 Sol2 高点。

## Code

### Sol1

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;

#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout);
#define Check(a) freopen(a".in", "r", stdin), freopen(a".ans", "w", stdout);

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
#define fi first
#define se second
#define mp std::make_pair

const int mod = 1e9 + 7, i2 = 5e8 + 4;
template <typename A>
inline int M(A x) {return x;}
template <typename A, typename ...B>
inline int M(A x, B ... args) {return 1ll * x * M(args...) % mod;}

#define mi(x) (x >= mod) && (x -= mod)
#define ad(x) (x < 0) && (x += mod)

int n, c, m, le[7];
double f[306][36], ans, cnt;

inline int ksm(int a, int b) {
	int tm = 1;
	for (; b; b >>= 1, a = M(a, a)) b & 1 && (tm = M(a, tm));
	return tm;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> c; m = 1 << n - 1;
	for (int i = 0; i < n; ++i) std::cin >> le[i];
	sort(le, le + n);

	do {
		for (int i = 0; i <= c * n; ++i) {
			for (int s = 0; s < m; ++s) f[i][s] = 0;
		}
		f[le[n - 1] * n][0] = 1;//先把最后一个放上去

		for (int i = 1; i <= c * n; ++i) {
			if (!(i % n)) continue;

			int p = i % n - 1;
			for (int j = i; j <= c * n; ++j) {
				for (int s = 0; s < m; ++s) ~s >> p & 1 && (
					f[min(c * n, max(j, i + le[p] * n))][s | (1 << p)] += f[j][s]
				);
			}
		}

		ans += f[c * n][m - 1]; ++cnt;
	} while (next_permutation(le, le + n - 1));

	std::cout << fixed << setprecision(12) << ans / cnt / ksm(c, n - 1);

	return 0;
}
```
### Sol2

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;

#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout);
#define Check(a) freopen(a".in", "r", stdin), freopen(a".ans", "w", stdout);

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
#define fi first
#define se second
#define mp std::make_pair

const int mod = 1e9 + 7, i2 = 5e8 + 4;
template <typename A>
inline int M(A x) {return x;}
template <typename A, typename ...B>
inline int M(A x, B ... args) {return 1ll * x * M(args...) % mod;}

#define mi(x) (x >= mod) && (x -= mod)
#define ad(x) (x < 0) && (x += mod)

int n, c, m, le[7], I[32];
ll f[32][52][7];

inline int ksm(int a, int b) {
	int tm = 1;
	for (; b; b >>= 1, a = M(a, a)) b & 1 && (tm = M(a, tm));
	return tm;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> c; m = 1 << n - 1;
	for (int i = 0; i < n; ++i) std::cin >> le[i];
	sort(le, le + n);
	f[0][le[n - 1]][0] = 1;

	for (int i = 1; i < m; ++i) I[i] = I[i >> 1] + (i & 1);

	for (int i = 0; i < c; ++i) {
		for (int j = 1; j < n; ++j) {
			for (int k = m - 1; ~k; --k) {
				if (j > I[k] + 1) continue;

				for (int l = i; l <= c; ++l) {
					for (int p = 0; p <= I[k]; ++p) {
						if (l == i && p < j) continue;

						int po = p + (p >= j);
						for (int q = 0; q < n - 1; ++q) if (~k >> q & 1) {
							int len = std::min(i + le[q], c);

							if (len > l || (len == l && j > po)) {
								f[k | (1 << q)][len][j] += f[k][l][p];
							}
							else f[k | (1 << q)][l][po] += f[k][l][p];
						}
					}
				}
			}
		}
	}

	double ans = 0;
	for (int i = 0; i < n; ++i) ans += f[m - 1][c][i];
	for (int i = 1; i < n; ++i) ans /= c * i;

	std::cout << fixed << setprecision(12) << ans << "\n";

	return 0;
}
```

---

## 作者：Arghariza (赞：4)

先考虑只能放**整点**的情况，不难想到考虑 dp。

对于环上的 dp，考虑**断环成链**，即钦定一条线段的左端点为**起点**。这里我们令长度**最长**的线段的左端点为环的起点。

这样做有一个好处：我们不用考虑**一条线段把环末尾覆盖再覆盖开头的空**的情况，而当我们钦定一个长度较小的线段作为起点时，在环的末尾放一个长度较长的线段有可能覆盖到环开头的空隙中，这样是合法的，但判不到。

然后就相当于固定了一个前缀被覆盖，剩下 $n-1$ 条线段，由于 $n$ 的范围较小，不难想到**状压**。同时我们考虑从前往后枚举线段**起点**，这样任意时刻覆盖的都是一段**前缀**。具体来讲，我们设 $f_{i,S}$ 表示覆盖了 $[0,i]$ 这段**极长**前缀，用了 **$S$ 集合中线段**的方案数（最长线段，即我们已经钦定位置的线段不算）。

转移时枚举线段起点 $i$、要填的线段 $j$、上一刻 $S$ 集合的状态 $T$ 以及上一刻覆盖到的前缀 $[0,w]$ 即可。由于我们钦定了最长线段为起点，中途我们一旦留下了空隙以后就无法弥补了，所以 $w\ge i$。我们用 $w$ 和 $i+l_j$ 去更新现在的极长前缀，那么有：

$$f_{\min(c,\max(w,i+l_j)),T\cup\{ j\}}\gets f_{w,T}$$

然后这是只能放**整点**的情况，现在考虑**任意实点**的情况。

考虑刚才的 dp 时间复杂度 $O(c^2n2^n)$，发现这个时间限制相当富余，我们考虑乱搞。

具体来讲，我们将圆和弧细分成 $m$ 段，满足 $c\mid m$。我们再给 $l_i$ 和 $c$ 乘上 $\frac{m}{c}$，做刚才的 dp。显然，当 $m$ **越大**时，可以取的整点就**越多**。当 $m\to +∞$ 时，我们可以认为圆环上所有**实点**都可以取到。

于是我们又有一个 $O(m^2n2^n)$ 的 dp 了，其中 $m\to +∞$。考虑优化复杂度。

我们想起一种 dp 优化方法，在值域很大，另一维很小，答案满足为关于值域的较小次数多项式时，可以用**拉格朗日插值**优化。例如[这题](https://www.luogu.com.cn/problem/CF995F)。

类似地，这题我们放大眼睛观察，我们发现**任意摆放线段**时，合法的方案数是一个关于 $m$ 的 $n$ 次多项式。当我们**钦定最长线段起点**时，方案数就是一个关于 $m$ 的 $n-1$ 次多项式~~但我不会证~~。感性理解一下，每次插入一条线段最多使次数增加 $1$，而一共 $n-1$ 条线段，所以多项式次数不超过 $n-1$。

于是我们取 $m=c,2c,\cdots,nc$ 即可得到这个多项式的 $n$ 个点值，而我们要求：

$$\lim\limits_{m\to +∞}\frac{f(m)}{m^{n-1}}$$

上面是合法的方案数，下面是总方案数，除一下就是概率。同时不难发现这东西就是 $[m^{n-1}]f(m)$，即求**最高次数项的系数**。

回忆拉格朗日插值公式：

$$f(x)=\sum\limits_{i=1}^ny_i\prod\limits_{j\neq i}\frac{x-x_j}{x_i-x_j}$$

相当于若干个一次式相乘，每个一次式里面取一次项或常数项。但是由于我们要求最高次数项，我们只能取一次项，所以：

$$[x^{n-1}]f(x)=\sum\limits_{i=1}^ny_i\prod\limits_{j\neq i}\frac{1}{x_i-x_j}$$

代入 $y_i=f_{ic,U}$ 就做完了。复杂度 $O(c^2n^42^n)$，其实由于钦定的最长线段，应该是 $2^{n-1}$，所以常数很小。

其实不会拉插的话可以高斯消元。复杂度不变。

```cpp
const int N = 10;
const int M = 55;
const int T = (1 << 5) + 10;
int n, c, tc, S, l[N], tl[N], f[N * M][T], y[N];

signed main() {
    n = rd(), tc = rd(), S = (1 << (n - 1)) - 1;
    for (int i = 0; i < n; i++) tl[i] = rd();
    sort(tl, tl + n);
    for (int _ = 1; _ <= n; _++) {
        for (int i = 0; i < n; i++) l[i] = tl[i] * _;
        c = tc * _;
        for (int i = 0; i <= c; i++)
            memset(f[i], 0, sizeof(int) * (S + 5));
        f[l[n - 1]][0] = 1;
        for (int i = 0; i <= c; i++) 
            for (int j = 0; j < n - 1; j++) 
                for (int k = 0; k < S; k++) 
                    if ((k >> j) & 1 ^ 1) 
                        for (int w = max(i, l[n - 1]); w <= c; w++) 
                            f[min(max(w, i + l[j]), c)][k | (1 << j)] += f[w][k];
        y[_] = f[c][S];
    }
    double res = 0;
    for (int i = 1; i <= n; i++) {
        int p = y[i], q = 1;
        for (int j = 1; j <= n; j++) 
            if (j ^ i) q *= (i - j) * tc;
        res += 1. * p / q;
    }
    printf("%.12lf", res);
    return 0;
}
```

---

## 作者：wind_boy (赞：3)

第一道独立切掉的问号题。写篇题解纪念一下。

一个显然的观察就是一个方案是否合法只和这 $2n$ 个点的相对位置关系有关。

考虑容斥，钦定有 $m$ 段没被覆盖，现在整个环被划分为了 $2m$ 段，分界点为 $l_1,r_1,l_2,r_1,\cdots,l_m,r_m$，其中 $(r_i,l_{i\bmod m+1})$ 没被覆盖，$[l_i,r_i]$ 可以被覆盖，且 $l_i$ 和 $r_i$ 必须被覆盖，考虑计算概率。

爆搜出每个弧在哪个区间，爆搜出 $l_i,r_i$ 被哪个弧覆盖，设 $x_{2i-1}=r_i-l_i,x_{2i}=l_{i\bmod m+1}-r_i$，那么会有若干条形如 $x_i\geq c_i$ 的限制，以及 $\sum x_i=C$ 的限制，并且概率为 $\prod f_i(x_i)$，其中 $f_i$ 是一个 $n$ 次多项式。由于 $x_i\geq c_i$ 看起来很不爽，因此让 $x_i$ 减掉 $c_i$，让 $f_i(x_i)$ 变成 $f_i(x_i+c_i)$，那么限制就变成了 $x_i\geq 0$。现在我们需要计算的就是形如 $\int_0^t\int_0^t\cdots\int_0^tf_1(x_1)f_2(x_2)\cdots f_{m}(t-\sum_{i=1}^{m-1} x_i)dx_1dx_2\cdots dx_{m-1}$ 的式子。

有结论：上式为关于 $t$ 的多项式。考虑归纳。假设 $f_1,f_2$ 为多项式，则 $\int_0^tf_1(x)f_2(t-x)dx=\sum_{i=0}\sum_{j=0}u_iv_j\int_0^t x^i(t-x)^j dx$。显然 $\int_0^t x^i(t-x)^j dx$ 是关于 $t$ 的多项式，证毕。

复杂度 $O(\sum_in^{\underline i}i^{n-i}f_i\times \text{poly}(n))$，其中 $f_n$ 为斐波那契数列第 $n$ 项。

[code](https://atcoder.jp/contests/agc020/submissions/63720499)

由于笔者数学水平不高，如有错漏欢迎指出。

---

## 作者：关怀他人 (赞：3)

### AGC 020F
#### Solution
首先默认长度最长的那一条弧放在$[0,x]$的位置上，然后考虑其它弧的左端点的位置。

有一个套路，考虑把左端点位置的整数部分和小数部分分开考虑，那么整数部分只有$n$种可能，而小数部分虽然可能性有无数种，但是它们之间的相对顺序只有$n!$种（默认互不相同，因为连续型随机变量取值相同的概率可以视为$0$），而且只有这个相对顺序会对答案有影响。

于是我们可以$n!$枚举小数部分的相对顺序，把圆上给拆成$N\times C$个点，其中第$i \times N + C$个点表示整数部分为$i$，小数部分的相对顺序为$j$，然后设$f[i][j][S]$表示现在考虑到点$i$，当前最远能覆盖到点$j$，已经选了的点的集合为$S$的方案数，转移有两种，一种是直接转移到$f[i+1][j][S]$，还有一种是转移到$f[i+1][max(j,pos)][S\cup \{x\}]$，其中$pos$为以$i$左端点放置第$x$条弧后能覆盖到的最远位置。
#### Code
```cpp
int n,C;
int a[MAXN],len[MAXN];
ll facn,p,ans;
ll f[2][MAXL][MAXM]; 

int main(){
    scanf("%d%d",&n,&C);
    for(int i = 1;i <= n;i++){
        scanf("%d",&len[i]);
        a[i] = i;
    }
    sort(len + 1,len + 1 + n);
    do{
        memset(f,0,sizeof(f));
        int cur = 0,maxState = (1 << (n - 1)) - 1;
        f[cur][len[n] * n][0] = 1;
        for(int i = 1;i < C * n;i++){
            if(i % n == 0) continue;
            memset(f[cur ^ 1],0,sizeof(f[cur ^ 1]));
            int x = i % n - 1;
            for(int j = i;j <= C * n;j++){
                for(int S = 0;S <= maxState;S++){
                    f[cur ^ 1][j][S] += f[cur][j][S];
                    if(!(S >> x & 1))
                        f[cur ^ 1][min(C * n,max(j,i + len[a[x + 1]] * n))][S | (1 << x)] += f[cur][j][S];
                }
            }
            cur ^= 1;
        }
        ans += f[cur][C * n][maxState];
    }while(next_permutation(a + 1,a + n));
    facn = p = 1;
    for(int i = 1;i < n;i++)
        facn *= i, p *= C;
    printf("%.12Lf\n",(long double)ans / facn / p);
    return 0;
}
```

---

## 作者：xht (赞：1)

## [Arcs on a Circle](https://atcoder.jp/contests/agc020/tasks/agc020_f)

### 题意

- 有一个周长为 $c$ 的圆。
- 你有 $n$ 条弧，第 $i$ 条弧的弧长为 $l_i$。
- 对于每条弧，你会在圆上随机一个位置作为它的中点放置。
- 求圆上每个点都被至少一条弧覆盖的概率。
- $n \le 6$，$c \le 50$。

### 题解

考虑断环为链，以最长弧的一端为端点断开这个环。

**由于所有的弧长都是整数，所以我们不关心所有弧起始点的小数部分，我们只关心小数部分之间的大小关系。**

我们可以暴力枚举这个大小关系，于是问题变成：在区间 $[0,nc)$ 上，有一条已知长度的从 $0$ 开始的线段，另外还有 $n-1$ 条已知长度，且起点 $\bmod n$ 确定的线段，要求这些线段覆盖整个区间的方案数。

考虑状压 DP，设 $f_{i,j,s}$ 表示当前在点 $i$，已经覆盖到了点 $j$，使用的线段集合为 $s$ 的方案数，转移时考虑 $i+1$ 是否为某个线段的起点即可。

由于我们一开始选择的是最长的线段，因此因为断开了环而断开的线段在开头处不会有贡献，可以直接忽略掉。

时间复杂度 $\mathcal O((n-1)!n^2c^22^{n-1})$。

### 代码

```cpp
int n, m, k, l[7], p[7], f[307][307][135];

inline int work() {
	memset(f, 0, sizeof(f));
	f[0][l[n]*n][0] = 1;
	for (int i = 1; i < n * m; i++)
		for (int j = i; j <= n * m; j++)
			for (int s = 0; s <= k; s++)
				if (f[i-1][j][s]) {
					f[i][j][s] += f[i-1][j][s];
					int x = i % n;
					if (!x || s >> (x - 1) & 1) continue;
					f[i][min(n*m,max(j,i+l[p[x]]*n))][s|1<<(x-1)] += f[i-1][j][s];
				}
	return f[n*m-1][n*m][k];
}

int main() {
	rd(n, m), rda(l, n), k = (1 << (n - 1)) - 1;
	sort(l + 1, l + 1 + n), iota(p + 1, p + n, 1);
	ll ans = 0, cnt = 1;
	for (int i = 1; i < n; i++) cnt *= i * m;
	do ans += work();
	while (next_permutation(p + 1, p + n));
	printf("%.20Lf\n", 1.0L * ans / cnt);
	return 0;
}
```

---

## 作者：sky_of_war (赞：1)

同步发布于我的博客：[Arcs on a Circle](https://www.skyofwar.net/2019/05/22/156.html)

不失一般性，假设最长的弧的长度为$L_N$。我们可以任意地将这个弧的固定在圆的任意一个位置上，因为圆是循环同构的。考虑在圆上引入坐标系，使得第$N$个圆弧的始末坐标分别为$0$和$L_N$，同时圆上的所有其他点的坐标都在$[0, C)$范围内。

令$X_i$为弧的左端坐标，那么它的右端坐标为$(X_i+L_i)\bmod C$。由于$X_i$是随机地从$[0, C)$中选择的，于是我们尝试重新表示$X_i$为$P_i+F_i$，其中$P_{i}=\left\lfloor X_{i}\right\rfloor$，$F_{i}=X_{i}-P_{i}$，这可以将问题转化为从$[0 ,C-1]$中取一个整数$P_{i}$和从$[0,1)$中随机取一个实数$F_{i}$，并且有$X_{N}=P_{N}=F_{N}=0$。
我们可以得出$F_i$是互不相同的，因为对于$i \neq j$，$F_{i}=F_{j}$的概率为$0$。

考虑一个排列$A_{1}, A_{2}, \dots, A_{N-1}$，满足
$$F_{A_{1}}<F_{A_{2}}<\ldots<F_{A_{N-1}}$$
由于$F_{N}$已经被固定在了$0$处，一共有$(N-1) !$种不同的排列。于是一个朴素做法就显而易见了：枚举这个排列，再枚举$P_i$，再检查每种情况是否满足题目条件，时间复杂度为十分~~优秀~~的$\mathcal O\left((N-1) ! \cdot C^{N-1} \cdot N \log N\right)$，可以获得$0$分的好成绩。

上面的算法慢在哪里呢？我们发现暴力枚举$P_i$太慢了！考虑$\text{dp}$，注意到所有可能成为弧末端的坐标值，按递增顺序依次为：
$$\begin{array}{c}{0 ; 0+F_{A_{1}} ; 0+F_{A_{2}} ; \ldots ; 0+F_{A_{N-1}}} \\ {1 ; 1+F_{A_{1}} ; 1+F_{A_{2}} ; \ldots ; 1+F_{A_{N-1}}} \\ {\cdots} \\ {C-1 ; C-1+F_{A_{1}} ; C-1+F_{A_{2}} ; \ldots ; C-1+F_{A_{N-1}}}\end{array}$$
一共有$CN$个这样的坐标。用$x_{0}, x_{1}, \dots, x_{C N-1}$对它们进行编号，设$f_{i,j,S}$表示，从$0$覆盖到了$j$，其中起点最靠右的在$i$点，已经出现的线段集合是$S$的方案数。初始值$f_{0, L_{N} \cdot N, \{N\}}=1$，最终答案为$f_{C N,CN,\{1,2, \ldots, N\}}$。然后分两种情况考虑：
 - 没有弧的起点在$x_i$，那么$f_{i, j, s} \to f_{i+1, j, s}$
 - 有弧的起点在$x_i$，显然这条弧只能是$A_{i \bmod n}$，并且还要满足$i \bmod n \neq 0$且$A_{i \bmod n} \notin s$。那么$f_{i, j, s} \to f_{i+1, \min \left(C N, \max \left(j, i+L_{A_{i \bmod n}} \cdot N\right) \right),s \cup\left\{A_{i \bmod n}\right\} }$

时间复杂度$\mathcal O(N! 2^{N}(C N)^{2})$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, c, A[10];
double f[500][(1 << 7)], ans, t;
inline double fact(int k)
{
    if (!k) return 1;
    if (k == 1) return 1;
    if (k == 2) return 2;
    if (k == 3) return 6;
    if (k == 4) return 24;
    if (k == 5) return 120;
    return 0; 
}
int main()
{
    scanf("%d%d", &n, &c);
    for(int i = 0; i < n; ++i) scanf("%d", &A[i]);
    sort(A, A + n);
    do
    {
        memset(f, 0, sizeof f);
        f[A[n - 1] * n][0] = 1;
        for(int i = 0; i <= n * c; ++i)
            for(int j = i; j <= n * c; ++j)
                for(int S = 0; S < (1 << n - 1); ++S)
                    if(i % n && !((S >> (i % n - 1)) & 1))
                        f[min(n * c, max(j, i + A[i % n - 1] * n))][S | (1 << (i % n - 1))] += f[j][S];
        ans += f[n * c][(1 << n - 1) - 1];
        ++t;
    }
    while(next_permutation(A, A + n - 1));
    printf("%.15lf", (double)ans / t / pow(c, n - 1));
    return 0;
}
```

---

## 作者：heyongxin (赞：1)

**16.2 题目大意**

一个长度为 C 的圆周，上面随机放 N 个线段，第 i 个长度为 Li，问恰好覆盖整个圆周的概率。

C, Li 都是整数。
数据范围很小，n<=6。


------------
**16.3 题目解法**

首先固定 Li 最长的，这个不影响答案。

我们并不关心随机的小数部分，我们只关心小数部分的相对大小，所以我们可以暴力枚举N个排列。

这样整个圆周相当于离散化成了 N*C 个点，然后我们DP有多少种方案可以用这 N 个线段覆盖这个圆周。
暴力的话是 $C^N$ 的太慢了。

用f[i][j][S] 表示，从0覆盖到了j，其中起点最靠右的在i点，已经出现的线段集合是S。

注意因为上面枚举排列的关系，确定了起点，必然可以知道是哪条线段。状态数优化为$2^N$ $(CN)^2$，转移是 O(1)的。

不选弧的话，从f[i][j][S] 转移到 f[i+1][j][S]。

选弧的话，从f[i][j][S]转移到f[i+1][min(C*N,max(j,i+$L_{(Aimodn)}$× N))][S∪{$A_i$ mod n}]。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,l[10];
double dp[500][(1<<7)],t,ans;
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;++i)
	scanf("%d",&l[i]);
	sort(l,l+n);
	do
	{
		memset(dp,0,sizeof(dp));
		dp[l[n-1]*n][0]=1;
		for(int i=0;i<=n*c;++i)
		for(int j=i;j<=n*c;++j)
		for(int S=0;S<(1<<n-1);++S)
			if(i%n and !((S>>(i%n-1))&1))
				dp[min(n*c,max(j,i+l[i%n-1]*n))][S|(1<<(i%n-1))]+=dp[j][S];
		ans+=dp[n*c][(1<<n-1)-1];
		t++;
	}
	while(next_permutation(l,l+n-1));
	printf("%.15lf",(double)ans/t/pow(c,n-1));
	return 0;
}
```

---

## 作者：dontwannacry (赞：0)

# AT_agc020_f 题解
## 前言
虽然这题是 7 年前的题，但是蒟蒻在做到这个题时还是大大的被震撼到，于是写一篇题解纪念一下。
## 题目大意
[原题链接](https://atcoder.jp/contests/agc020/tasks/agc020_f)

你有一个长度为 $C$ 的圆，你在上面画了 $N$ 个弧。弧 $i$ 有长度 $l_i$。

每一条弧 $i$ 随机均匀地放置在圆上：选择圆上的一个随机实点，然后出现一条以该点为中心的长度为 $l_i$ 的弧。弧是独立放置的。例如，它们可以相互交叉或包含。

现在问你圆的每一个实点被至少一个弧覆盖的概率是多少？注意一条弧覆盖了它的两个端点。
### 约束条件
- $ 2\ \leq\ N\ \leq\ 6 $
- $ 2\ \leq\ C\ \leq\ 50 $
- $ 1\ \leq\ L_i\ <\ C $
- 输入值全为整数。
## 解题思路
### 关键点：
将线段位置的小数部分离散化后按照钦定的大小顺序进行状压dp。
### 分析
首先，我们不妨使用弧的端点来代表这个弧。因为用弧的中点来代表弧的话要考虑弧对左右两个方向的覆盖情况。

由于弧可以落在圆上的任意位置，覆盖的情况是无穷的。这样的问题显然是计算机无法直接处理的。我们先尝试让它变成一个有穷的问题。

我们考虑把圆看作**无数个连续的点**的集合，再对点集进行取样，把这个点集变成一个**有限个离散的点**的集合，比如说在圆上等距地取 $M$ 个点。显然，我们取的点越多，答案就越接近准确值。当然由于这个题的精度要求比较高（误差小于 $ 10^{-11} $），这个办法在这个题中是不可行的。

不过这个思路给了我们启发：我们先假装弧的位置就只能在这样的 $M$ 个编号为 $0$ 到 $M-1$ 散点中，由于 $N$ 比较小，问题就可以用**状压dp**来做了：我们设 $f_{S,i}$ 为取了集合 $S$ 中的弧，让他们覆盖从 $0$ 号点到 $i$ 号点中的所有点的概率。令点 $M$ 为点 $0$，答案即为 $f_{U,M}$（$U$ 为全集）。

当然，较高的精度要求限制了这个做法的前途，我们还需要去题目中挖掘更多的性质。

在状压的做法中，我们希望每次加入弧时，它都是能和前面的弧相交的。由于弧长度必定是整数这一约束，我们考虑弧位置的小数部分造成的影响：

记弧 $i$ 开始位置为 $p_i = z_i+q_i$，$z_i = \lfloor p_i \rfloor$。那么弧的结束位置为 $p_i' = (z_i+l_i)+q_i$ 也就是说，我们可以用 $\{z_i,q_i,l_i\}$ 来描述弧 $i$。为什么不用 $\{p_i,l_i \}$ 来描述呢？因为我们如果直接用 $p_i$ 来描述的话，就又要向之前那样枚举无穷多的状况。而记成 $z_i+q_i$ 的话，我们就可以把 $q_i$ 看作位置的第二关键字，进而可以想到将数列 $\{q\}$ 排序，用排序后的结果来代替 $\{q\}$，**把一个小数的东西变成全排列**。于是我们又完成了从无穷到有穷的过程。

从点集的角度来再看一遍这个过程，其实相当于我们在无限的点的集合中取出 $N \times C$ 个点（$N$ 组点，每组 $C$ 个，每组的点为 $U_i = \{p_i|p_i = z+q_i\}$）来做状压。

于是我们先枚举全排列，按照钦定的 $q$ 的大小顺序做状压就行了。
## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double lld;
int N,R,C,L[8],order[8],sum;
lld dp[32][310],ans = 0,tim;
void dpcase(){
	for(int re = 0;re < (1<<N);++re){
		for(int now = 0;now <= (N+1)*C;++now){
			dp[re][now] = 0;
		}
	}	
	dp[0][L[N]*(N+1)] = 1;
	for(int now = 1;now <= (N+1)*C;++now){
		if(now%(N+1) == 0){continue;}
		for(int ne = now+1;ne <= (N+1)*C;++ne){
			for(int re = 0;re < (1<<N);++re){
				for(int i = 0;i < N;++i){
					if(re&(1<<i)){continue;}
					if(now%(N+1) != order[i]){continue;}
					dp[re+(1<<i)][min(max(now+L[i]*(N+1),ne),(N+1)*C)] += dp[re][ne]/C;
				}
			}
		}
	}
}
void dfs(int T){
	if(T == 0){
		dpcase();
		ans += dp[(1<<N)-1][(N+1)*C]*tim;
		return;
	}
	for(int i = 0;i < N;++i){
		if(!order[i]){
			order[i] = T;
			dfs(T-1);
			order[i] = 0;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> C;
	for(int i = 0;i < N;++i){cin >> L[i];sum += L[i];}
	if(sum <= C){printf("%.16Lf\n",ans);return 0;}
	sort(L,L+N);--N;
	tim = 1.0;for(int i = 2;i <= N;++i){tim /= i;}
	dfs(N);
	printf("%.16Lf\n",ans);
	return 0;
}
```
## 后话
其实离散化这种东西挺基础的，看到小数这样的东西应该不难往这方面想。但是只对小数部分进行离散化这点不知道算不算好想？

这道题确乎是一道富有启发性的好题。

---

## 作者：UKE_Automation (赞：0)

### H AGC020F Arcs on a Circle

[$\text{Link}$](https://atcoder.jp/contests/agc020/tasks/agc020_f)

首先第一步我们考虑断环为链，我们把最长的一条弧任意放在圆上，然后不可能再有弧跨过这条弧，所以我们就可以变成一条链了。

然后现在的难点在于我们的坐标有可能是小数，比较难处理。我们考虑这样一个思路：题目中的 $C$ 比较小，所以我们可以尝试将它再次细分，然后每条线段依然只能放在整点上。我们令将这个环分成了 $m$ 份后合法的方案数为 $f(m)$，先考虑如何求 $f(m)$。

显然由于 $n$ 较小，所以可以状压 dp。设 $dp_{i,S,j}$ 表示当前枚举了起点在 $i$ 及以前的线段，当前已用线段集合为 $S$，覆盖到的最右端点为 $j$。转移时保证 $i\le j$，每次从小到大枚举一下当前要填的线段，转移是比较容易的。这一部分的复杂度是 $O(m^2n2^n)$。

不过现在的问题是 $m$ 取多少，实际上 $m$ 取到多少都不能在合理的时间复杂度内得到正确的答案，所以我们要换一个角度考虑。我们发现，当 $m\to +\infty$ 时，$f(m)$ 就是正确的方案数，而我们要求的是概率，于是答案就是：
$$
\lim_{m\to +\infty} \frac{f(m)}{m^{n-1}}
$$
此时我们观察可以发现，$f(m)$ 本身就是一个关于 $m$ 的 $n-1$ 次多项式，原因在于我们每增加一条线段就会使得次数至多加一。那么上面这个式子的值实际上就是 $f(m)$ 中 $n-1$ 次项的系数。求这个就是比较简单的了，直接代入 $n$ 个点值然后拉格朗日插值求出最后答案即可。最后复杂度是 $O(\sum(ic)^2\times n2^n)=O(c^2n^42^n)$。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

typedef long long ll;
typedef long double db;
const int Maxn = 2e5 + 5;
const int Inf = 2e9;
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
bool Beg;

int n, m, c, l[Maxn];
ll dp[1 << 5][305];
ll y[305];

void work(int x) {
	for(int i = 0; i < (1 << m); i++) for(int j = 0; j < x * c; j++) dp[i][j] = 0;
	dp[0][l[n] * x] = 1;
	for(int j = 1; j <= x * c; j++) {
		for(int p = 1; p <= m; p++) {
			int len = l[p] * x;
			for(int S = 0; S < (1 << m); S++) {
				if((S >> p - 1) & 1) continue;
				for(int i = j - 1; i <= x * c; i++) {
					if(!dp[S][i]) continue;
					dp[S | (1 << p - 1)][min(max(j + len - 1, i), c * x)] += dp[S][i];
				}
			}
		}	
	}
	y[x] = dp[(1 << m) - 1][c * x];
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	IOS();
	cin >> n >> c; m = n - 1;
	for(int i = 1; i <= n; i++) cin >> l[i];
	sort(l + 1, l + n + 1);
	for(int x = 1; x <= n; x++) work(x);
    db ans = 0;
    for(int i = 1; i <= n; i++) {
    	db mul = 1.0;
    	for(int j = 1; j <= n; j++) {
    		if(i != j) mul *= ((i - j) * c);
		}
		ans += y[i] / mul;
	}
	cout << fixed << setprecision(16) << ans << '\n';
	Usd();
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：0)

[aProblem Link](https://www.luogu.com.cn/problem/AT_agc020_f)

**题目大意**

> 给定一个周长为 $C$ 的环，有 $n$ 条长度为 $a_1\sim a_n$ 的弧，每条弧均匀随机一个实数位置放置，求所有弧覆盖整个环至少一次的概率。
>
> 数据范围：$C\le 50,n\le 6$。

**思路分析**

先从弧的位置是整点的情况入手：我们需要从一个合适的位置进行破环为链。

破环为链的一个缺陷是如果某个弧的起点 $x_i$ 满足 $x_i+a_i>C$，那么会对这条链的一段前缀 $[1,x+a_i-C]$ 产生覆盖。

但我们可以从最长链 $a_p$ 的起点开始破环为链，那么 $[1,a_p]$ 已经被覆盖，其他链覆盖的范围 $x+a_i-C$ 一定不超过 $a_p$。

因此对于这种弧我们就不需要考虑越过 $C$ 的贡献，只考虑对后缀的覆盖。

$f_{i,j,s}$ 表示将 $s$ 中的线段左端点放到 $[1,i]$ 中，覆盖范围 $[1,j]$ 的方案数，然后 dp 即可。

然后考虑取的是实数的情况。

事实上我们只关心 $x_i,a_i+x_i$ 的相对大小关系，我们发现比较他们的大小关系只需要比较整数部分，以及小数部分的相对顺序。

因此我们可以直接枚举 $\{x_i\}$（小数部分）的相对顺序，由于 $x_i$ 在实数范围内均匀随机，因此两个 $x_i$ 小数部分相等的概率为 $0$，$n!$ 枚举 $\{x_i\}$ 的顺序，然后做上面的 dp 即可。

时间复杂度 $\mathcal O(n!\times 2^nn^2C^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll dp[305][64],ans=0;
int n,m,a[10],p[10];
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%d",&a[i]),p[i]=i;
	sort(a,a+n);
	do {
		memset(dp,0,sizeof(dp));
		dp[a[n-1]*n][0]=1;
		for(int i=1;i<=n*m;++i) if(i%n) {
			int x=p[i%n-1];
			for(int j=i;j<=n*m;++j) for(int s=0;s<(1<<(n-1));++s) if(!(s>>x&1)) {
				dp[min(n*m,max(j,i+a[x]*n))][s|1<<x]+=dp[j][s];
			}
		}
		ans+=dp[n*m][(1<<(n-1))-1];
	} while(next_permutation(p,p+n-1));
	long double z=ans;
	for(int i=1;i<n;++i) z/=i;
	for(int i=1;i<n;++i) z/=m;
	printf("%.20Lf\n",z);
	return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [Arcs on a Circle](https://www.luogu.com.cn/problem/AT_agc020_f)

首先，一个非常自然的想法是尝试断环成链。怎么断呢？我们发现，选择最长线段的起点处截断是个非常好的选择，因为不可能有一个线段完全覆盖它。这之后，一个紧接着的想法就是 DP。

假如把描述中的全部“实点”改成“整点”的话，那么这题是比较 trivial 的，可以通过随便状压就出来了。

但是现在是实点。怎么办？

DP 状态里必然涉及到记录当前所有线段最远覆盖的位置，但这是个实数，不好记录。

这时候，一个不知道咋想出来的主意便产生了——我们考虑比较两个实数时的步骤，肯定是先比较整数，再比较小数。而因为所有线段长度都是整数，整数部分的大小关系是容易比较的，而小数部分可以选择离散化。具体而言，我们枚举它们小数部分的大小关系构成一个排列，然后将整个长度为 $c$ 的环变作 $n\times c$ 个点表示大小关系。我们枚举的排列的实际意义是，限制第一条线段的起始位置只能是 $1,n+1,2n+1,\dots,(c-1) \times n+1$ 这些位置，再限制第二条线段的位置只能是 $2,n+2,2n+2,\dots,(c-1) \times n+2$ 这样，大小关系确定，就可以 DP 了，只需要记得枚举完全排列后除以排列数即可。

时间复杂度 $n!\times 2^n\times(nc)^2$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=310;
int n,c,a[6],p[6];
double f[N][1<<5][N<<1],res;
int main(){
    scanf("%d%d",&n,&c);
    for(int i=0;i<n;i++) scanf("%d",&a[i]),p[i]=i;
    sort(a,a+n);
    do{
        f[0][0][a[n-1]*n]=1;
        for(int i=0;i<c*n;i++){
			for(int j=0;j<(1<<(n-1));j++){
				for(int k=i;k<2*c*n;k++){
					f[i+1][j][k]+=f[i][j][k];
					if(i%n&&!(j&(1<<p[i%n-1]))){
						f[i+1][j|(1<<p[i%n-1])][max(k,i+a[p[i%n-1]]*n)]+=f[i][j][k]/c;
					}
					f[i][j][k]=0;
				}
			}
		}
        for(int i=c*n;i<2*c*n;i++){
			res+=f[c*n][(1<<(n-1))-1][i];
			f[c*n][(1<<(n-1))-1][i]=0;
		}
    }while(next_permutation(p,p+n-1));
    for(int i=1;i<n;i++) res/=i;
    printf("%.11lf\n",res);
    return 0;
}
```

---

