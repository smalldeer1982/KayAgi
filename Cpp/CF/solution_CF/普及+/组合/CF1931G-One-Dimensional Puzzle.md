# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 样例 #1

### 输入

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5```

### 输出

```
4
66
0
794100779
1
0
1
0
1
36
126```

# 题解

## 作者：快斗游鹿 (赞：15)

观察拼图形状。可以发现如果不考虑第三块和第四块拼图，第一块拼图和第二块拼图一定是交替出现的。也就意味着如果 $ \lvert c_1-c_2 \rvert>1$，一定无解。

然后分类讨论：

如果 $c_1=c_2$：

以第一块拼图打头，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/axpl313m.png)

可以发现第三块拼图有 $c_1$ 个空位可填，第四块拼图有 $c_2+1$ 个空位可填。

可以发现这个问题就相当于有 $y$ 个盒子，要放入 $x$ 个球，可以为空的方案数，由插板法易知答案为 $\tbinom{x+y-1}{y-1}$，记 $g(x,y)=\tbinom{x+y-1}{y-1}$。那么该情况的答案就是 $g(c_3,c_1)\times g(c_4,c_2+1)$。

同理，如果以第二块拼图打头，那么第三块拼图有 $c_1+1$ 个空位可填，第四块拼图有 $c_2$ 个空位可填，答案就是 $g(c_3,c_1+1)\times g(c_4,c_2)$。

如果 $\lvert c_1-c_2 \rvert=1$：

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s8m488mq.png)

可以发现第三块和第四块拼图都有 $\max(c_1,c_2)$ 个空位可填，设 $a=\max(c_1,c_2)$。

那么方案数就是 $g(c_3,a)\times g(c_4,a)$。然后就做完了。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=8e6+5;
const int mod=998244353;
int T,a,b,c,d;
int fac[N],inv[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int C(int nn,int mm){
	if(!mm)return 1;
	if(nn<mm)return 0;
	return fac[nn]%mod*inv[mm]%mod*inv[nn-mm]%mod;
}
signed main(){
	//freopen("std.in","r",stdin);
	T=read();
	inv[0]=1;inv[1]=1;fac[0]=1;fac[1]=1;
	for(int i=2;i<=8e6;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=8e6;i++)inv[i]=inv[i-1]*inv[i]%mod;
	for(int i=2;i<=8e6;i++)fac[i]=fac[i-1]*i%mod;
	while(T--){
		a=read();b=read();c=read();d=read();
		if(a==b){
			//a个c,b+1个d
			//a+1个c,b个d 
			if(!a)puts(c&&d?"0":"1");
			else printf("%lld\n",(C(a+c-1,a-1)*C(b+d,b)%mod+C(b+d-1,b-1)*C(a+c,a))%mod); 
		}
		else if(abs(a-b)==1){
			if(a<b)swap(a,b);
			printf("%lld\n",C(a+c-1,a-1)*C(a+d-1,a-1)%mod);
		}
		else puts("0");
	}
	return 0;
}

```


---

## 作者：ganpig (赞：2)

我们用图来表示四块拼图之间的连接关系

![](https://cdn.luogu.com.cn/upload/image_hosting/s5unydep.png)

于是问题就转化成了求这张有向图上经过结点 $i$ 恰好 $c_i$ 次的路径数量

注意到，从 $1$ 出发，无论如何回到 $1$，总要经过 $2$，于是合法路径中两个 $1$ 间必有 $2$，同理两个 $2$ 间必有 $1$，因此除去路径中的 $3$ 和 $4$ 以后，剩下的一定是形如 $1-2-1-\cdots$ 这样的循环，具体形式由 $c_1$ 与 $c_2$ 的关系决定：

- $c_1=c_2+1$ 时，一定是 $1-2-\cdots-2-1$；
- $c_2=c_1+1$ 时，一定是 $2-1-\cdots-1-2$；
- $c_1=c_2$ 时，可以是 $1-2-\cdots-1-2$ 也可以是 $2-1-\cdots-2-1$；
- $|c_1-c_2|>1$ 时，不存在合法路径。

接着我们考虑如何把 $3$ 和 $4$ 插进去，容易发现 $3$ 可以任意插在 $1$ 之后 $2$ 之前，$4$ 可以任意插在 $2$ 之后 $1$ 之前

考虑前面提到的循环由 $1$ 开始，即 $c_1 \ge c_2$ 的情况，$3$ 有 $\lfloor \frac{c_1+c_2+1}{2} \rfloor$ 个位置可以插，$4$ 有 $\lfloor \frac{c_1+c_2+2}{2} \rfloor$ 个位置可以插；而从 $2$ 开始则反之。注意 $c_1=c_2$ 时要把两种情况的答案相加！

注：把 $n$ 个东西插进 $m$ 个位置的方法数，用隔板法易得共有 $\tbinom {n+m-1}{n}$ 种

记得特判 $c_1=c_2=0$ 的情况~

## $\text{Code}$

```cpp
#include <bits/stdc++.h>

constexpr int mod = 998244353, N = 2e6 + 10;
int fac[N]{1};
inline int inv(long long x) {
    long long res = 1;
    for (int b = mod - 2; b; b >>= 1, x = x * x % mod)
        if (b & 1)
            res = res * x % mod;
    return res;
}
inline int C(int n, int m) {
    return 1ll * fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
}

int main() {
    for (int i = 1; i < N; i++)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    int T;
    std::cin >> T;
    while (T--) {
        int c1, c2, c3, c4;
        std::cin >> c1 >> c2 >> c3 >> c4;
        if (std::abs(c1 - c2) >= 2)
            puts("0");
        else if (!c1 && !c2)
            puts(c3 && c4 ? "0" : "1");
        else {
            long long ans = 0;
            if (c1 >= c2)
                ans += 1ll * C(c3 + (c1 + c2 - 1) / 2, c3) * C(c4 + (c1 + c2) / 2, c4) % mod;
            if (c2 >= c1)
                ans += 1ll * C(c3 + (c1 + c2) / 2, c3) * C(c4 + (c1 + c2 - 1) / 2, c4) % mod;
            printf("%lld\n", ans % mod);
        }
    }
}
```

---

## 作者：Register_int (赞：2)

[Overall](https://www.luogu.com.cn/blog/const1e7/CF1931-solution)  
[更好的阅读体验](https://zhuanlan.zhihu.com/p/682231073)  

题意：给定如图的四个拼图块：

![](https://espresso.codeforces.com/d862915ed3dc627101b0e632c1c778b818648879.png)

数量为 $c_1,c_2,c_3,c_4$。这些拼图块不能旋转、翻转，问将它们拼成一列直线的方案数。

有一个简单的观察：只有 $1,2$ 拼块能改变凹凸，并且拼好 $1,2$ 的方法只有两者交替拼一种。$3,4$ 可以任意拼到 $1,2$ 的左右侧而不会影响其他拼块。

首先，有个前置知识：

- 将 $x$ 个相同的物品放进 $y$ 个盒子（允许不放）的方案数是 $\binom{x+y-1}{y-1}$。

第一句告诉我们，如果 $|c_1-c_2|>1$，那么必定无法拼好。第二条结论则告诉我们 $3,4$ 不会相互影响，可以拆开后用乘法原理合并。此时分类讨论：

- 若没有 $1,2$ 块，则在 $3,4$ 块都有的情况下无解，否则有方案数为 $1$，即全拼起来。
- 若 $c_1=c_2$，拼好 $1,2$ 块有两种方案：
	- 若 $1$ 开头，则 $3$ 有 $c_1$ 个空位，$4$ 有 $c_1+1$ 个空位，方案数为 $\binom{c_3+c_1-1}{c_1-1}\binom{c_4+c_1}{c_1}$。
   - 若 $2$ 开头，则 $3$ 有 $c_1+1$ 个空位，$4$ 有 $c_1$ 个空位，方案数为 $\binom{c_3+c_1}{c_1}\binom{c_4+c_1-1}{c_1-1}$。
   
   总方案数为 $\binom{c_3+c_1-1}{c_1-1}\binom{c_4+c_1}{c_1}+\binom{c_3+c_1}{c_1}\binom{c_4+c_1-1}{c_1-1}$。

- 若 $c_1=c_2+1$，拼好 $1,2$ 块仅有一种方案：以 $1$ 开头。此时 $3,4$ 均有 $c_1$ 个空位，方案数为 $\binom{c_3+c_1-1}{c_1-1}\binom{c_4+c_1-1}{c_1-1}$。
- 若 $c_1=c_2-1$，拼好 $1,2$ 块仅有一种方案：以 $2$ 开头。此时 $3,4$ 均有 $c_1+1$ 个空位，方案数为 $\binom{c_3+c_1}{c_1}\binom{c_4+c_1}{c_1}$。

预处理阶乘、阶乘逆元即可做到 $O(1)$ 组合数，按公式计算即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e6 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll C(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int t, a, b, c, d;

int main() {
	for (scanf("%d", &t), init(2e6); t--;) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (abs(a - b) > 1) { puts("0"); continue; }
		if (a == b) {
			if (!a) puts(c && d ? "0" : "1"); 
			else printf("%lld\n", (C(c + a, a) * C(d + a - 1, a - 1) + C(c + a - 1, a - 1) * C(d + a, a)) % mod);
		} else if (a == b + 1) printf("%lld\n", C(c + a - 1, a - 1) * C(d + a - 1, a - 1) % mod);
		else  printf("%lld\n", C(c + a, a) * C(d + a, a) % mod);
	}
}
```

---

## 作者：rainygame (赞：1)

第一次 AK CF 的比赛，写篇题解纪念一下。

对于这四个拼图，可以通过对两边的凹凸进行区分。第一种是 $\texttt{11}$、第二种是 $\texttt{00}$、第三种是 $\texttt{01}$、第四种是 $\texttt{10}$。

然后对于一个合法的拼图序列，设第 $i$ 个的拼图右边的凹凸性是 $a_i$，$a_i$ 为 $\texttt{0}$ 表示这是凹的，$\texttt{1}$ 同理。那么最后得到的就是一个长度为 $c_1+c_2+c_3+c_4$ 的 01 串。显然地，01 串是类似“$\texttt{0}$ 段”“$\texttt{1}$ 段”“$\texttt{0}$ 段”“$\texttt{1}$ 段”这样交替的。

考虑拼图在这个 01 串里的地位。可以发现第三种是在 01 串里面是从一个“$\texttt{0}$ 段”到一个“$\texttt{1}$ 段”的“过渡”，而第四种则恰好相反。由此我们可以推出“$\texttt{0}$ 段”和“$\texttt{1}$ 段”的数量：

1. $c_3=c_4+1$，这个时候 01 串是从 $\texttt{0}$ 开始，到 $\texttt{0}$ 结束的。因为“$\texttt{0}$ 段”比“$\texttt{1}$ 段”多 $1$。
2. $c_4=c_3+1$，和 1 同理。
3. $c_3=c_4$，这个时候 01 串可以从 $\texttt{1}$ 开始，到 $\texttt{0}$ 结束；也可以从 $\texttt{0}$ 开始，到 $\texttt{1}$ 结束。两种情况的方案数要分别统计。
4. $\lvert c_3-c_4\rvert > 1$，没有合法的 01 串。

现在知道了 01 串的构成了，考虑 $c_1$ 和 $c_2$ 对答案的影响。以 $c_1$ （两边都是凸）为例：

假设一个“$\texttt{1}$ 段”的长度为 $l$，那么它对 $c_1$ 的贡献为 $l-1$。

所以考虑所有的“$\texttt{1}$ 段”，它们满足这个式子：

$$
\sum (l_i-1)=c_1
$$

只需要找到满足这个式子的 $l_i$ 的正整数解即可，根据组合计数的知识，$l_i$ 的解共有 $C_{k+c_1-1}^{k-1}$ 组，其中 $k$ 为“$\texttt{1}$ 段”的数量。

$c_2$ 对答案的影响就是把上面的“$\texttt{1}$ 段”全部改成了“$\texttt{0}$ 段”而已，因为两者互不影响，所以取两者解组数之积即可。

注意 $c_1,c_2$ 为 $0$ 的情况。以及 $c_1=c_3=0$ 或 $c_2=c_4=0$ 的情况。

赛时通过代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD(998244353);
#define MAXN 5000001
#define inv(x) (qpow(x, MOD-2))

int t, c_1, c_2, c_3, c_4;
int f[MAXN];

int qpow(int a, int k){
    int res(1);
    while (k){
        if (k & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        k >>= 1;
    }
    return res;
}

int C(int n, int m){
    if (n < m || n < 0 || m < 0) return 0;
    if (!m) return 1;
    return (f[n]*inv(f[m]) % MOD) * inv(f[n-m]) % MOD;
}
#define solve(n, m) (!(n) && !(m) ? 1 : C((n)+(m)-1, (n)-1))

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    f[0] = 1;
    for (int i(1); i<MAXN; ++i) f[i] = (f[i-1] * i) % MOD;
    // cout << solve(1, 4) << ' ' << solve(0, 0) << '\n';

    cin >> t;
    while (t--){
        cin >> c_1 >> c_2 >> c_3 >> c_4;
        if (!c_1 && !c_2 && !c_3 && !c_4){
            cout << "1\n";
            continue;
        }
        if (c_1 == c_2) cout << (solve(c_1+1, c_4)*solve(c_2, c_3)+solve(c_1, c_4)*solve(c_2+1, c_3)) % MOD;
        else if (c_1-c_2 == 1) cout << (solve(c_1, c_4)*solve(c_2+1, c_3)) % MOD;
        else if (c_2-c_1 == 1) cout << (solve(c_1+1, c_4)*solve(c_2, c_3)) % MOD;
        else cout << "0";
        cout << '\n';
    }

    return 0;
}
```


---

## 作者：MaxBlazeResFire (赞：1)

出题人玩[原](https://www.luogu.com.cn/problem/CF1608D)神玩的吧？

把 $4$ 种拼图看成 $11,00,01,10$，问能不能全拼在一起。

$\rm Observation1:$ $1$ 与 $0$ 的总数差不能超过 $2$；

$\rm Observation2:$ 两个 $00$ 之间必然恰好有一个 $11$；两个 $11$ 之间必然恰好有一个 $00$；

$\rm Observation3:$ 用 $00,11$ 将整个序列分成若干段（包括首尾），每一段内部必然都只放 $01$ 或只放 $10$，且二者不占用同一个缝隙，贡献可以独立计算。

分情况讨论，插板即可。复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 4000005
#define mod 998244353

int fac[MAXN],inv[MAXN],ifac[MAXN],c[5];

inline int C( int n , int m ){ return n >= m ? 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod : 0; }
inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }

inline void solve(){
	scanf("%d%d%d%d",&c[1],&c[2],&c[3],&c[4]);
	int C0 = c[2] * 2 + c[3] + c[4],C1 = c[1] * 2 + c[3] + c[4];
	if( abs( C0 - C1 ) > 2 ){ puts("0"); return; }
	if( c[2] > c[1] ) printf("%lld\n",1ll * C( c[1] + c[3] , c[1] ) * C( c[1] + c[4] , c[1] ) % mod);
	else if( c[1] > c[2] ) printf("%lld\n",1ll * C( c[2] + c[3] , c[2] ) * C( c[2] + c[4] , c[2] ) % mod);
	else{
		if( !c[1] && !c[2] ){
			if( !c[3] || !c[4] ) puts("1");
			else puts("0");
			return;
		}
		int Ans = 1ll * C( c[1] + c[3] , c[1] ) * C( c[2] + c[4] - 1 , c[2] - 1 ) % mod;
		chkadd( Ans , 1ll * C( c[2] + c[4] , c[2] ) * C( c[1] + c[3] - 1 , c[1] - 1 ) % mod );
		printf("%d\n",Ans);
	}
}

signed main(){
	fac[0] = inv[1] = ifac[0] = 1;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) fac[i] = 1ll * fac[i - 1] * i % mod;
	for( int i = 2 ; i <= MAXN - 5 ; i ++ ) inv[i] = 1ll * ( mod - mod / i ) * inv[mod % i] % mod;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

什么 [[ABC336G] 16 Integers](https://www.luogu.com.cn/problem/AT_abc336_g) 究极弱化版。

把元素 $1$ 看成 $01$，元素 $2$ 看成 $10$，元素 $3$ 看成 $11$，元素 $4$ 看成 $00$。则转化为统计长度为 $2$ 的子串 $xy$ 出现次数为 $c_{xy}$ 的 $01$ 串个数。

把子串 $xy$ 看成 $x \to y$ 的一条有向边，那么这是一个**点数为 $2$ 的**欧拉路径计数问题，可以 BEST 定理解决，但是不需要。

有解的必要条件是 $|c_{01} - c_{10}| \le 1$。若 $c_{01} = c_{10}$ 那么 $01$ 串开头和结尾的字符相同。若以 $0$ 开头和结尾，相当于把 $c_{00} + c_{01} + 1$ 个 $0$ 分成 $c_{01} + 1$ 份，$c_{10} + c_{11}$ 个 $1$ 分成 $c_{10}$ 份，每份非空，根据插板法可得方案数为 $\binom{c_{00} + c_{01}}{c_{01}} \binom{c_{10} + c_{11} - 1}{c_{10} - 1}$。以 $1$ 开头和结尾类似。

若 $c_{01} = c_{10} + 1$，那么以 $0$ 开头，以 $1$ 结尾。相当于把 $c_{00} + c_{01}$ 个 $0$ 分成 $c_{01}$ 份，$c_{11} + c_{01}$ 个 $1$ 分成 $c_{01}$ 份，方案数为 $\binom{c_{00} + c_{01} - 1}{c_{01} - 1} \binom{c_{11} + c_{01} - 1}{c_{01} - 1}$。

$c_{10} = c_{01} + 1$ 的情况是类似的。注意特判 $c_{10} = c_{01} = 0$，这种情况只能是全 $0$ 或全 $1$，所以 $c_{00}$ 和 $c_{11}$ 不能都非 $0$。

时间复杂度 $O(T + \sum c_i)$。

[code](https://codeforces.com/problemset/submission/1931/246301851)

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

第一眼看到这题可能会想 dp 或者矩阵加速之类的，但是这些都不好做。

我们定义向右凸出或向左凹陷为状态 1，反之为状态 0，那么这四种拼图相当于一条从某个点连向另一个点的边，这样我们需要求的就是这个只有两个点的图的欧拉路径。

实际上思考的时候也可以不带上面这一步，这里只是进行一个更直观的转化，这样后面的内容也更容易理解。

既然是欧拉路径，那么一定是形如 $0\rightarrow \cdots \rightarrow 0\rightarrow 1\rightarrow 1\rightarrow \cdots \rightarrow 1\rightarrow 0\rightarrow \cdots$ 这样的，也有可能起点是 $1$。

容易发现 $0\rightarrow 1$ 的数量一定与 $1\rightarrow 0$ 的数量相差最多 $1$，因为忽略自环就一定要交替走这两种边。

之后对于差为 $-1$、$0$ 和 $1$ 的情况分别讨论，剩下的自环就用插板法即可解决，这里就不再赘述，可以参考其它题解。

---

## 作者：int08 (赞：0)

## 前言

这个是水 Div.3 G，不过隔壁还有更水的 [Div.2 F](https://www.luogu.com.cn/problem/CF1929F)，还是同一个知识点，我也写了题解的。
## 题意

给出如图中四种形状零件的数量，问有多少种将它们连为一线的方式。

# Solution

一眼思维题，先观察。

发现零件 C 和 D 的插入不影响原有形状，只要有 A 或者 B，C 和 D 想插多少插多少。

先特判掉没有 A 和 B 的，此时如同时有 C 和 D 则无解，否则则有唯一解。

如果有 A 或者 B，C 和 D 并不影响可解性，只影响解的数量。

那么抛开 C、D 不管，只有 A，B 的话，只有一个 A 一个 B 交错放才合法，即 A 和 B 数量差不超过 $1$。

解决完 A 和 B，就是 C 和 D 咋插进去的问题了。

以 $x$ 个 A，$x-1$ 个 B 为例。

显然有 $2 \times x$ 个位置，其中 $x$ 个可放 C，另 $x$ 个可放 D。

每个位置可放任意个，也可不放，经典[插板法](https://oi-wiki.org/math/combinatorics/combination/#%E6%8F%92%E6%9D%BF%E6%B3%95)得出放法数为（设有 $y$ 个 C，D 同理）：

$$\binom{x-1+y}{x-1}$$

如果 A，B 数量相等，则要考虑哪个在前哪个在后，但是式子差不多，建议自己推推，也可以看我的代码。

## AC Code
```cpp
#include<bits/stdc++.h> 
#define int long long
#define mod 998244353
using namespace std;
int qp(int x,int y)
{
	int ans=1;
	for(int i=1,j=x;i<=y;i*=2,j=(j*j)%mod) if(i&y) ans=(ans*j)%mod;
	return ans;
}
int C(int x,int y)
{
	int ans=1;
	for(int i=1;i<=y;i++) ans=(ans*(x+1-i))%mod,ans=(ans*qp(i,mod-2))%mod;
	return ans;
 } 
int a,b,c,d,t;
signed main()
{
	cin>>t;
	for(int ac=1;ac<=t;ac++)
	{
		cin>>a>>b>>c>>d;
		if(a+b==0&&c*d==0)
		{
			puts("1");
			continue;
		}
		if(a+b==0||abs(a-b)>1)
		{
			puts("0");
			continue;
		}
		if(a-b)
		cout<<(C(c+min(a,b),min(a,b))*C(d+min(a,b),min(a,b)))%mod<<endl;
		else
		cout<<(C(c+min(a,b),min(a,b))*C(d+min(a,b)-1,min(a,b)-1)+C(c+min(a,b)-1,min(a,b)-1)*C(d+min(a,b),min(a,b)))%mod<<endl;
	}
	return 0;
}
```
## 后记

人生第一场 CF Div.3 就碰见了难得一遇的超水 3G，然后啥准备没做呢就 AK 了。

有一种 "It brought me 'the END' before 'the BEGINNING'" 的美。

可能以后就没法 AK Div.3 了。

无所谓啦。

"Every 'END' is a new 'BEGINNING'"

---

## 作者：sjr3065335594 (赞：0)

## 题意简述

有 $4$ 种拼图，其中第 $i$ 种拼图有 $c_i$ 张。将所有的拼图从左往右拼起来，求总方案数。

## 思路

显然容易发现，每个 $1$ 号拼图和若干个 $3$ 号拼图拼起来得到的图形仍是一个 $1$ 号拼图，$1$ 号与 $4$ 号同理，所以实际上 $3$ 和 $4$ 号拼图对最终的拼图形状没有实际影响，只与 $1$ 号与 $2$ 号有关，由于 $1$ 和 $2$ 号拼图只能够交替拼接，所以如果 $|c_1-c_2|>1$，说明无法交替拼接，即一定无解，还有一种无解的情况，即 $c_1=c_2=0$ 且 $c_3\neq0,c_4\neq0$，意思就是 $3$ 和 $4$ 号拼图没办法单独拼接。现在我们就将问题转化成了对于由 $1$ 和 $2$ 号拼起来的拼图，将 $3$ 和 $4$ 号插进去的方案数。下面分三种情况进行讨论。

1. $c_1=c_2+1$

此时拼图应该是 `1 2 ... 2 1` 这样的排列，由于每个 $1$ 号拼图都可以拼若干个 $3$ 号拼图，即 $3$ 号拼图有 $c_1$ 个位置可以放入，要将 $c_3$ 个 $3$ 号拼图放进 $c_1$ 个位置里，可以有位置不妨，根据隔板法，总方案数为 $C_{c_1+c_3-1}^{c_1}$，$4$ 号拼图同理。所以总方案数为 $C_{c_1+c_3-1}^{c_1}+C_{c_1+c_4-1}^{c_1}$。

2. $c_2=c_1+1$

这种与上边的同理，总方案数为 $C_{c_2+c_3-1}^{c_2}+C_{c_2+c_4-1}^{c_2}$。

3. $c_1=c_2$

这时就有两种情况，第一种是前两种拼图拼成 `1 2 ... 1 2` 的情况，可以发现 $3$ 号拼图有 $c_1$ 个位置可以放，$4$ 号拼图有 $c_1+1$ 个位置可以放；第二种是 `2 1 ... 2 1` 的情况，可以发现 $3$ 号拼图有 $c_1+1$ 个位置可以放，$4$ 号拼图有 $c_1$ 个位置可以放。

所以此时总方案数为 $C_{c_1+c_3-1}^{c_1}\times C_{c_1+c_4}^{c_1+1}+C_{c_1+c_3}^{c_1+1}\times C_{c_1+c_4-1}^{c_1}$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
//#define int long long
//#define int __int128
using namespace std;
const int N=1e6+5;
const int M=1e6+5;
const int INF=2e9+5;
const int mod=998244353;
ll qpow(ll a,ll b) {
	ll res=1;
	while(b) {
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll fac[N<<1],inv[N<<1];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N*2;i++) {
		fac[i]=fac[i-1]*i%mod;
		inv[i]=qpow(fac[i],mod-2);
	}
}
ll C(int n,int m) {
	int w=n;n=n+m-1;m=w;//由于组合数写起来麻烦在这里更改
	return (fac[n]*inv[m]%mod*inv[n-m]%mod)%mod;
}
int t,c1,c2,c3,c4;
void solve() {
	scanf("%d%d%d%d",&c1,&c2,&c3,&c4);
	if(abs(c1-c2)>1) {
		printf("0\n");
		return;
	}
	ll ans;
	if(c1==c2) {
		ans=((C(c3,c1)*C(c4,c1+1))%mod+(C(c3,c1+1)*C(c4,c1))%mod)%mod;
	} else {
		int c=max(c1,c2);
		ans=(C(c3,c)*C(c4,c))%mod;
	}
	if(c1==c2&&c1==0&&(c3==0||c4==0))ans=1;
	printf("%lld\n",ans);
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&t);
	init();
	while(t--)solve();
	return 0;
}

```


---

## 作者：SamHJD (赞：0)

## One-Dimensional Puzzle

### Description

有四种拼图：两边凸，两边凹，左凹右凸，左凸右凹。给出每种拼图的个数 $c_1,c_2,c_3,c_4$，问有多少种方案能使这些拼图拼成一行。 

### Solution

将四种拼图编号为 $1,2,3,4$。我们发现 $1$ 和 $3,4$ 拼完后的形状仍为两边凸，$2$ 和 $3,4$ 拼完后的形状仍为两边凹。

因此暂时不考虑 $3,4$，若只有 $1,2$，则能拼成一行仅当这两种拼图的个数差不超过 $1$，因为 $1$ 的两边只能放 $2$，$2$ 的两边只能放 $1$，此时可以判无解。

接下来往里面插入 $3,4$：

* 若 $c_1=c_2$，则需分类讨论 $1$ 在第一个和 $2$ 在第一个的情况。若 $1$ 在第一个，则 $3$ 能放的位置个数为 $c_1$，$4$ 能放的位置个数为 $c_2+1$；若 $2$ 在第一个，则 $3$ 能放的位置个数为 $c_1+1$，$4$ 能放的位置个数为 $c_2$。

* 否则 $3,4$ 能放的位置个数均为 $\max(c_1,c_2)$。

计算将 $x$ 个数放入 $y$ 个位置（允许有空）的方案数，可转换为每个位置至少有一个的情况，只需将 $x$ 变为 $x+y$，用插板法计算：

$$ans=\dfrac{(x+y-1)!}{x!(y-1)!}=C_{x+y-1}^{y-1}$$

---

## 作者：Lily_White (赞：0)

## 思路分析
题中所给 4 种块的兼容性（也就是可以拼接的关系）可以用下表表示。

| 左侧可以拼接 | 当前块 | 右侧可以拼接 |
| :----------: | :----------: | :----------: |
| 2/4 | 1 |  2/3|
| 1/3 | 2 |  1/4|
| 1/3 | 3 |  2/3|
| 2/4 | 4 | 1/4 |

这些规则总结如下

- `1` 块和 `2` 块必须交替出现，不能出现连续的 `11` 或 `22` 等排列
- `3` 块和 `4` 块可以连续任意多个地出现
- `3` 块可以被插在 `12` 段中间，也就是可以出现 `133...32` 这种结构，也可以被放在第一个 `2` 的左侧、或者最后一个 `1` 的右侧，为方便起见，称这样的位置为甲类空隙
- `4` 块可以被插在 `21` 段中间，也就是可以出现 `244...41` 这种结构，也可以被放在第一个 `1` 的左侧、或者最后一个 `2` 的右侧，为方便起见，称这样的位置为乙类空隙

我们在计数时，首先将 `1` 和 `2` 块摆好位置，也就是摆成 `...121212...` 的序列，这就要求**它们的个数差不能大于 1**，否则，就会出现连续的 `11` 或 `22` 等排列，这是不符合要求的。

摆好位置之后，数一数有多少个可以插连续 `3` 或 `4` 段的空间。这就需要分类讨论。

- 如果 $a=b$，此时，若从 `1` 开始，也就是摆放成 `121212...1212` 的样子，这时甲类空隙为 $a-1$ 个，乙类空隙为 $b$ 个；另一种情况：若摆放成 `2121212...121` 的样子，这时甲类空隙为 $a$ 个，乙类空隙为 $b-1$ 个；
- 否则，甲类空隙和乙类空隙分别为 $\lfloor\dfrac{(a+b)}2\rfloor+1$ 个。

接着，我们需要将 `34` 两种拼图放到对应类别的空隙中，这是**允许出现空组且元素相同的分组计数问题**，可以用隔板法解决。具体推导可以参考 [OI Wiki](https://oi-wiki.org/math/combinatorics/combination/#%E9%9D%9E%E8%B4%9F%E6%95%B4%E6%95%B0%E5%92%8C%E7%9A%84%E6%95%B0%E7%9B%AE) 的条目。最终结果为 $\displaystyle \binom{n+k-1}{n}$，这里 $k$ 为空数，$n$ 为物体数。

最后还需要注意 $a=b=0$ 的情况，这时，若 $c$ 或 $d$ 均非 $0$，则答案为 $0$，否则答案为 $1$。
## 参考代码
```cpp
const int MOD = 998244353;
const int N = 2000000;
ll fact[N + 20];
void init() {
    fact[0] = 1;
    repn(i, N) fact[i] = fact[i - 1] * i % MOD;
}
ll qpow(ll a, ll b = MOD - 2, ll p = MOD) {
    ll ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = ans * a % p;
        a = a * a % p;
    }
    return ans;
}
ll nCr(ll n, ll r) {
    if (n < r)
        return 0;
    else
        return fact[n] * qpow(fact[r]) % MOD * qpow(fact[n - r]) % MOD;
}
void inc(ll &x, ll d) { x = (x + d) % MOD; }
void Main() {
    ll a, b, c, d;
    rd(a, b, c, d);
    ll ans = 0;
    if (a == b) {
        if (a == 0) {
            if (c == 0 && d != 0)
                cout << 1 << endl;
            else if (c != 0 && d == 0)
                cout << 1 << endl;
            else if (c == 0 && d == 0) {
                cout << 1 << endl;
            } else
                cout << 0 << endl;
        } else {
            // type 3
            ll space = (a + b) / 2 + 1;
            // cerr << space3 << ' ' << nCr(space3 + c - 1, c) << endl;
            inc(ans, nCr(space + c - 1, c) * nCr(space + d - 1 - 1, d) % MOD);
            inc(ans, nCr(space + d - 1, d) * nCr(space + c - 1 - 1, c) % MOD);
            cout << ans << endl;
        }
    } else if (a == b - 1) {
        ll space = (a + b) / 2 + 1;
        inc(ans, nCr(space + c - 1, c) * nCr(space + d - 1, d) % MOD);
        cout << ans << endl;
    } else if (a == b + 1) {
        ll space = (a + b) / 2 + 1;
        inc(ans, nCr(space + c - 1, c) * nCr(space + d - 1, d) % MOD);
        cout << ans << endl;
    } else {
        cout << 0 << endl;
    }
}
```

---

## 作者：arrow_king (赞：0)

# G. One-Dimensional Puzzle

记 `|` 为第一种拼图，`-` 为第二种拼图，`>` 为第三种拼图，`<` 为第四种拼图。

观察到最终合法的组合是有一定规律的，最后的情况一定是：

$$\underbrace{\texttt{<...<}}_{\tiny\text{若干个}}\texttt |\underbrace{\texttt{>...>}}_{\tiny\text{若干个}}\texttt -\underbrace{\texttt{<...<}}_{\tiny\text{若干个}}\texttt |\underbrace{\texttt{>...>}}_{\tiny\text{若干个}}\texttt -\cdots$$

或者是

$$\underbrace{\texttt{>...>}}_{\tiny\text{若干个}}\texttt -\underbrace{\texttt{<...<}}_{\tiny\text{若干个}}\texttt |\underbrace{\texttt{>...>}}_{\tiny\text{若干个}}\texttt -\underbrace{\texttt{<...<}}_{\tiny\text{若干个}}\texttt |\cdots$$

此处“若干个”均可以为 $0$。

直接进行分类讨论：

1. `|` 与 `-` 数量相同，则有两种情况，一种是 `|` 在前，一种是 `-` 在前。前一种情况里有 $c_1$ 个位置放置 `>` 段而有 $c_1+1$ 个位置放置 `<` 段，前一种情况里有 $c_1$ 个位置放置 `<` 段而有 $c_1+1$ 个位置放置 `>` 段，两类结果相加即可。
2. `|` 比 `-` 多一个，则放置 `<` 与 `>` 段的位置数相同，均为 $c_1$。
3. `|` 比 `-` 少一个，则放置 `<` 与 `>` 段的位置数相同，均为 $c_2$。
4. $|c_1-c_2|>1$，则不存在对应的解。
5. $c_1=0,c_2=0$，没有放置 `<` 与 `>` 段的位置，则两种积木不能都有，否则不存在解。如果 $c_3\cdot c_4=0$，那么解数是 $1$。

这样就讨论完了。将相同积木放入对应位置（可以放 $0$ 个）的方案数是经典的插板法，套用公式并预处理组合数即可。

时间复杂度 $O(t+V)$，其中 $V=\max\left\{\sum\limits_{i=1}^4c_i\right\}$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 10000000
#define mod 998244353
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll t,c[4];
ll fac[N+5],inv[N+5];
il ll Abs(ll x) {
	return x>=0?x:-x;
}
il ll qpow(ll a,ll b) {
	ll ans=1;
	while(b) {
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
il ll C(ll x,ll y) {
	if(x<y) return 0;
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main() {
	t=read(),fac[0]=1;
	for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	while(t--) {
		for(int i=0;i<4;i++) c[i]=read();
		if(Abs(c[1]-c[0])>1) {
			printf("0\n");
			continue;
		}
		if(c[0]==0&&c[1]==0) {
			if(c[2]*c[3]==0) printf("1\n");
			else printf("0\n");
			continue;
		}
		if(c[0]==c[1]) {
			ll ans=C(c[3]+c[0],c[0])*C(c[2]+c[0]-1,c[0]-1)%mod;
			ans=(ans+C(c[2]+c[0],c[0])*C(c[3]+c[0]-1,c[0]-1)%mod)%mod;
			printf("%lld\n",ans);
		}
		else if(c[0]<c[1]) {
			ll ans=C(c[3]+c[1]-1,c[1]-1)*C(c[2]+c[1]-1,c[1]-1)%mod;
			printf("%lld\n",ans);
		}
		else {
			ll ans=C(c[3]+c[0]-1,c[0]-1)*C(c[2]+c[0]-1,c[0]-1)%mod;
			printf("%lld\n",ans);
		}
	}
	return 0;
}

```

---

## 作者：MarSer020 (赞：0)

怎么有菜狗 30min 才会 div3 G 啊/lh

$\Large\text{Solution}$

考虑 $1$ 可以把末端的凹陷变为凸起，$2$ 可以把末端的凸起变为凹陷，而 $3$ 和 $4$ 不变，所以当且仅当 $1$ 和 $2$ 个数的绝对值之差 $\le 1$ 时才有解，否则多出的 $1$ 或 $2$ 无法放入。

有解时大致形态是首先 $1$ 和 $2$ 交替放，然后中间的空隙放若干个 $3$ 或 $4$。

用 $\text{calc}(x,y)$ 表示将 $x$ 个元素分成互不相同且可以为空的 $y$ 份，分别插入 $y$ 个空中的方案数，则有 $\text{calc}(x,y)=\binom{x+y-1}{x}$。

分 $3$ 种情况：

- $c_1=c_2=0$，此时若 $c_3\ne 0$ 且 $c_4\ne 0$ 则无解，否则为 $1$。
- $c_1=c_2\ne 0$，此时方案数为 $\text{calc}(c_3,c_1)\times\text{calc}(c_4,c_2+1)+\text{calc}(c_3,c_1+1)\times\text{calc}(c_4,c_2)$。
- $c_1\ne c_2$，此时令 $m=\max(c_1,c_2)$，则方案数为 $\text{calc}(c_3,m)\times\text{calc}(c_4,m)$。

可以自己画图帮助理解。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int int64_t
using namespace std;
const int mod=998244353;
int t,a,b,c,d,m=2e6,fac[2000005],inv[2000005];
int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=ret*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ret;
}
int calc(int x,int y){
	return fac[x+y-1]*inv[x]%mod*inv[y-1]%mod;
}
int32_t main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>t,fac[0]=inv[0]=1;
	for(int i=1;i<=m;i++)
		fac[i]=fac[i-1]*i%mod;
	inv[m]=qpow(fac[m],mod-2);
	for(int i=m-1;i>=1;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	while(t--){
		cin>>a>>b>>c>>d;
		if(abs(a-b)>1){
			cout<<"0\n";
			continue;
		}
		if(!a&&!b){
			if(c&&d)
				cout<<"0\n";
			else
				cout<<"1\n";
			continue;
		}
		if(a==b)
			cout<<(calc(c,a)*calc(d,b+1)+calc(c,a+1)*calc(d,b))%mod<<'\n';
		else
			cout<<calc(c,max(a,b))*calc(d,max(a,b))%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

降智环节，赛时一直对着拼图 $34$ 找性质，然后就愉快罚坐。

不难发现拼图 $12$ 肯定是交错分布的，然后讨论一下，假若 $c_1 = c_2$ 那么需要枚举第一个放拼图 $1$ 还是拼图 $2$，然后发现拼图 $1$ 后面可以摆任意多个拼图 $3$，拼图 $2$ 后面可以摆任意多个拼图 $4$，等于把这个问题转化为 $n$ 个相同的拼图 $3$ 放入 $m$ 个不同的间隙以及 $n$ 个相同的拼图 $4$ 放入 $m$ 个不同的间隙，直接预处理组合数计算 ${n + m - 1 \choose m - 1}$ 即可。

假若 $c_1 \not = c_2$，那么情况类似，甚至确定了开头到底是哪个拼图减少了讨论。

时间复杂度 $O(\sum c_i + T \log mod)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
const int maxn = 4e6+114;
int c1,c2,c3,c4;
int fac[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int C(int n,int m){
    if(n==m) return 1;
    if(m>n||m<0) return 0;
    return (fac[n]*qpow(fac[m],mod-2))%mod*qpow(fac[n-m],mod-2)%mod;
}
//
void work(){
    cin>>c1>>c2>>c3>>c4;
    if(c1==c2){
        if(c1==0){
            if(c3!=0&&c4!=0) cout<<0<<'\n';
            else{
                cout<<1<<'\n';
            }
        }else{
            //1 开头
            int d3=c1;
            int d4=(c1+c2+1)-d3;
            int ans=C(c3+d3-1,d3-1)*C(c4+d4-1,d4-1)%mod;
            //d4=2
            //d3=1
            //4 开头
            d4=c2;
            d3=(c1+c2+1)-d4;
            ans=(ans+C(c3+d3-1,d3-1)*C(c4+d4-1,d4-1)%mod)%mod;
            cout<<ans<<'\n';
        }
 
    }else{
        if(c1>c2){
            if(c1-c2>1) cout<<0<<'\n';
            else{
                //1 2 1 2 1 2 1 2 1
                int d4=c1;
                int d3=(c1+c2+1)-d4;
                cout<<C(c3+d3-1,d3-1)*C(c4+d4-1,d4-1)%mod<<'\n';
            }
        }else{
            if(c2-c1>1) cout<<0<<'\n';
            else{
                //2 1 2 1 2 1 2 1 2
                int d3=c2;
                int d4=(c1+c2+1)-d3;
                cout<<C(c3+d3-1,d3-1)*C(c4+d4-1,d4-1)%mod<<'\n';
            }
        }
 
    }
}
//1 2 1 2
void init(){
    fac[0]=1;
    for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    init();
    while(t--) work();
    return 0;
}
```


---

