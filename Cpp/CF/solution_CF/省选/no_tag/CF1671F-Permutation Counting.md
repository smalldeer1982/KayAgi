# Permutation Counting

## 题目描述

Calculate the number of permutations $ p $ of size $ n $ with exactly $ k $ inversions (pairs of indices $ (i, j) $ such that $ i < j $ and $ p_i > p_j $ ) and exactly $ x $ indices $ i $ such that $ p_i > p_{i+1} $ .

Yep, that's the whole problem. Good luck!

## 样例 #1

### 输入

```
5
10 6 4
7 3 1
163316 11 7
136373 11 1
325902 11 11```

### 输出

```
465
12
986128624
7636394
57118194```

# 题解

## 作者：Leasier (赞：7)

注意到 $n$ 很大但 $k, x$ 很小，感性理解可知此时 $p_i = i$ 的 $i$ 很多，而 $p_i \neq i$ 的 $i$ 很少。事实上，这样的 $i$ 不超过 $22$ 个。

于是我们考虑对所有满足如下条件的区间 $[l, r]$ 分开讨论（类似地，这样的区间不超过 $11$ 个）：

- $2 \leq r - l + 1 \leq 12$。
- $p_l, p_{l + 1}, \cdots, p_r \in [l, r]$。
- $\not\exists l \leq i < r$，$[l, i], (i, r]$ 也为符合上述条件的区间。

感性理解可知第三个条件等价于 $\not\exists l \leq i < r, \displaystyle\max_{j = l}^i p_j < \min_{j = i + 1}^r p_j$。

注意到将 $p_i$ 整体减去一个数是不影响上述条件成立与否，于是我们只需要讨论 $l = 1, 2 \leq r \leq 12$ 的情况。这可以 dfs + 剪枝在 $O(N^2 N!)$ 的时间复杂度内预处理出（事实上对逆序对个数剪枝后跑得飞快），其中 $N = 12$。

先考虑当 $n$ 比较小时如何应用上述区间的性质。

设 $dp_{i, j, k}$ 表示已经填好了 $1 \sim i$，当前逆序数为 $j$，下降数为 $k$ 的方案数。

初值：$dp_{0, 0, 0} = 1$。

转移分为如下两种：

- $dp_{i, j, k} \leftarrow dp_{i, j, k} + dp_{i - 1, j, k}$，表示填入一个不包含在一个满足条件的区间中的 $p_i = i$。
- $dp_{i, j, k} \leftarrow dp_{i, j, k} + dp_{l - 1, x, y} cnt_{i - l + 1, j - x, k - y}$，其中 $cnt_{i, j, k}$ 表示长为 $i$ 的符合条件的区间，逆序数为 $j$，下降数为 $k$ 的方案数，这可以预处理出，该转移表示附加一个 $l \sim i$ 的符合条件的区间。

答案：$dp_{n, k, x}$。

时间复杂度为 $O(N^2 N! + N^5 M + T)$，由于 $M$ 达到了 $10^9$ 级别，显然不能通过。

现在我们考虑应用符合条件的区间不超过 $11$ 个的性质。

考虑枚举我们往 $n$ 个数中填了 $i$ 个符合条件的区间，总长为 $j$，由插板法可知此时方案数为 $C_{n + i - j}^i$，我们只需要再乘上一共填 $i$ 个符合条件的区间，总长为 $j$，逆序数为 $k$，下降数为 $x$ 的方案数并对所有 $i, j$ 得到的答案求和即可。

考虑给前面的 dp 加一维表示填的 $i$ 个符合条件的区间的数量，设 $dp_{i, j, k, l}$ 表示已经填了 $i$ 个符合条件的区间，总长为 $j$，当前逆序数为 $k$，下降数为 $l$ 的方案数。

初值：$dp_{0, 0, 0, 0} = 1$。

转移：$dp_{i, j, k, l} \leftarrow dp_{i, j, k, l} + dp_{i - 1, x - 1, y, z} cnt_{j - x + 1, k - y, l - z}$。

~~u1s1，$O(N^7)$ 的 dp 预处理我个人认为有点离谱。~~

时间复杂度为 $O(N^2 N! + TN^3)$。

注意算组合数部分需要提前进行线性求逆的预处理。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 12, M = 11, K = 22, mod = 998244353;
int suf[N + 7], p[N + 7], pre[N + 7], cnt[N + 7][M + 7][M + 7];
ll inv[N + 7], dp[M + 7][K + 7][M + 7][M + 7];
vector<int> v{1};

inline void init(){
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= N; i++){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
}

void dfs(int cur, int n, int m, int k){
	if (m > M) return;
	if (cur > n){
		for (register int i = 1; i <= n; i++){
			pre[i] = max(pre[i - 1], p[i]);
		}
		for (register int i = n; i >= 1; i--){
			suf[i] = min(suf[i + 1], p[i]);
		}
		for (register int i = 1; i < n; i++){
			if (pre[i] < suf[i + 1]) return;
		}
		cnt[n][m][k]++;
		return;
	}
	int size = n - cur + 1, cur_i = cur + 1;
	for (register int i = 0; i < size; i++){
		int m_ = m;
		p[cur] = v[i];
		for (int j = 1; j < cur; j++){
			if (p[cur] < p[j]) m_++;
		}
		if (m_ <= M){
			v.erase(v.begin() + i);
			if (cur == 1 || p[cur] > p[cur - 1]){
				dfs(cur_i, n, m_, k);
			} else {
				dfs(cur_i, n, m_, k + 1);
			}
			v.insert(v.begin() + i, p[cur]);
		}
	}
}

inline ll comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	ll ans = 1;
	for (register int i = 1, j = n; i <= m; i++, j--){
		ans = ans * j % mod * inv[i] % mod;
	}
	return ans;
}

ll lucas(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	if (n == 0) return 1;
	return lucas(n / mod, m / mod) * comb(n % mod, m % mod) % mod;
}

int main(){
	int t;
	cin >> t;
	init();
	for (register int i = 2; i <= N; i++){
		suf[i + 1] = 0x7fffffff;
		v.push_back(i);
		dfs(1, i, 0, 0);
	}
	dp[0][0][0][0] = 1;
	for (register int i = 1; i <= M; i++){
		for (register int j = 1; j <= K; j++){
			int t1 = min(j * (j - 1) / 2, M), t2 = min(j - 1, M);
			for (register int k = 1; k <= t1; k++){
				for (register int l = 1; l <= t2; l++){
					for (register int x = max(j - N + 1, 1); x < j; x++){
						for (register int y = 0; y < k; y++){
							for (register int z = 0; z < l; z++){
								dp[i][j][k][l] = (dp[i][j][k][l] + dp[i - 1][x - 1][y][z] * cnt[j - x + 1][k - y][l - z] % mod) % mod;
							}
						}
					}
				}
			}
		}
	}
	for (register int i = 1; i <= t; i++){
		int n, k, x;
		ll ans = 0;
		cin >> n >> k >> x;
		for (register int j = 0; j <= M; j++){
			for (register int y = 0; y <= K; y++){
				ans = (ans + dp[j][y][k][x] * lucas(n + j - y, j) % mod) % mod;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：myee (赞：5)

### 前言

有没有一种可能，就是说，出题人打着 dp 的名号，考你生成函数？

### 思路

我们称一个范围是 $[l,r]$ 的段是**置换**的，当且仅当其值域也恰**遍取** $[l,r]$。

我们称一个置换段是**本原**的，当且仅当其**不能**由其余置换段简单**拼接**而成。

我们称一个本原段是**平凡**的，当且仅当其**长度为 $1$**；反之，则是**不平凡**的。

有结论：
* 值域为 $[l,r]$ 的置换段 $a_{l\sim r}$ 与长度为 $r-l+1$ 的排列 $p_{1\sim r-l+1}$ 构成**一一映射** $p_k=a_{k+l-1}-l+1$，且**保持逆序数、下降数不变**。
* 任何一个长度为 $l$ 的本原段其**逆序数** $k\ge l-1$。
* 任何一个排列可以由若干本原段拼接而成，其中**不平凡的段数量不会超过原排列的逆序数**。

证明显然，略去。

注意到本题 $k,x$ 很小，我们不妨**预处理**时**暴力枚举所有排列**，即枚举**每一类置换段的形式**，记录有**非平凡本原**性、**长度**为 $l(l\le12)$、**逆序数**为 $k(k\le11)$、**下降数**为 $x(x\le11)$ 的排列数量 `CNT[l][k][x]`。

这部分复杂度是 $O(k!)$ 级别的，实际在 $l=12$ 时要跑得巨慢，建议**打表**。（似乎可用多项式 $\ln$ 来解决而不用暴力？）

记生成函数 $F(z)=\sum_{a,b,c}(Cnt_{a,b,c}u^bt^c)z^a$（注意这里认为 $u,t$ 都是常数），则答案的生成函数为：

$${1\over1-z-F}$$

答案为

$$\\
[z^nu^kt^x]{1\over1-z-F}
\\=[z^nu^kt^x]\sum_a\sum_p\binom{a+p}pz^aF^p\quad({\tt 这步用组合意义解释更简单})
\\=\sum_a[z^{n-a}u^kt^x]\sum_p\binom{a+p}pF^p
\\=\sum_a\sum_p\binom{n-a+p}p[z^au^kt^x]F^p
\\$$

（其实用组合意义解释更简单，可以避免生成函数）

由于 $k,x$ 的限制，暴力预处理 $F^1,F^2,\dots,F^{11}$ 即可，于是 $a\le22$ 也是显然的，从而这个柿子可以暴力求。

综上，本题解完。

### Code

如果常数实现不优秀，可能要考虑加一个火车头。

注释里的代码用于 `CNT[12][][]` 的打表卡常。

```cpp
#include <algorithm>
#include <stdio.h>
#include <vector>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T>T exgcd(T a,T b,T&x,T&y){if(b!=0){T ans=exgcd(b,a%b,y,x);y-=a/b*x;return ans;}else return y=0,x=1,a;}
template<typename T>T power(T base,T index,T mod)
{
    T ans=1%mod;
    while(index)
    {
        if(index&1)ans=ans*base%mod;
        base=base*base%mod,index>>=1;
    }
    return ans;
}
namespace ConstMod
{
    template<const ullt p>
    class mod_ullt
    {
        private:
            ullt v;
            inline ullt chg(ullt w){return(w<p)?w:w-p;}
            inline mod_ullt _chg(ullt w){mod_ullt ans;ans.v=(w<p)?w:w-p;return ans;}
        public:
            mod_ullt():v(0){}
            mod_ullt(ullt v):v(v%p){}
            bol empty(){return!v;}
            inline ullt val(){return v;}
            friend bol operator<(mod_ullt a,mod_ullt b){return a.v<b.v;}
            friend bol operator>(mod_ullt a,mod_ullt b){return a.v>b.v;}
            friend bol operator<=(mod_ullt a,mod_ullt b){return a.v<=b.v;}
            friend bol operator>=(mod_ullt a,mod_ullt b){return a.v>=b.v;}
            friend bol operator==(mod_ullt a,mod_ullt b){return a.v==b.v;}
            friend bol operator!=(mod_ullt a,mod_ullt b){return a.v!=b.v;}
            inline friend mod_ullt operator+(mod_ullt a,mod_ullt b){return a._chg(a.v+b.v);}
            inline friend mod_ullt operator-(mod_ullt a,mod_ullt b){return a._chg(a.v+a.chg(p-b.v));}
            inline friend mod_ullt operator*(mod_ullt a,mod_ullt b){return a.v*b.v;}
            friend mod_ullt operator/(mod_ullt a,mod_ullt b){return b._power(p-2)*a.v;}
            friend mod_ullt operator^(mod_ullt a,ullt b){return a._power(b);}
            inline mod_ullt operator-(){return _chg(p-v);}
            mod_ullt sqrt()
            {
                if(power(v,(p-1)>>1,p)!=1)return 0;
                mod_ullt b=1;do b++;while(b._power((p-1)>>1)==1);
                ullt t=p-1,s=0,k=1;while(!(t&1))s++,t>>=1;
                mod_ullt x=_power((t+1)>>1),e=_power(t);
                while(k<s)
                {
                    if(e._power(1llu<<(s-k-1))!=1)x*=b._power((1llu<<(k-1))*t);
                    e=_power(p-2)*x*x,k++;
                }
                return _min(x,-x),x;
            }
            mod_ullt inv(){return _power(p-2);}
            mod_ullt _power(ullt index){mod_ullt ans(1),w(v);while(index){if(index&1)ans*=w;w*=w,index>>=1;}return ans;}
            voi read(){v=0;chr c;do c=getchar();while(c>'9'||c<'0');do v=(c-'0'+v*10)%p,c=getchar();while(c>='0'&&c<='9');v%=p;}
            voi print()
            {
                static chr C[20];uint tp=0;
                ullt w=v;do C[tp++]=w%10+'0',w/=10;while(w);
                while(tp--)putchar(C[tp]);
            }
            voi println(){print(),putchar('\n');}
            mod_ullt operator++(int){mod_ullt ans=*this;return v=chg(v+1),ans;}
        public:
            inline ullt&operator()(){return v;}
            inline mod_ullt&operator+=(mod_ullt b){return*this=_chg(v+b.v);}
            inline mod_ullt&operator-=(mod_ullt b){return*this=_chg(v+chg(p-b.v));}
            inline mod_ullt&operator*=(mod_ullt b){return*this=v*b.v;}
            mod_ullt&operator^=(ullt b){return*this=_power(b);}
            mod_ullt&operator/=(mod_ullt b){return*this=b._power(p-2)*v;}
            mod_ullt&operator++(){return v=chg(v+1),*this;}
    };
}
const ullt Mod=998244353;
typedef ConstMod::mod_ullt<Mod>modint;
modint A[100005],B[100005];
modint CNT[13][12][12],User[12][27][12][12];
uint V[13],QAQ[13];
int main() // 总不会手写 ln 吧？？？
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
#endif
	A[0]=1;for(uint i=1;i<=100000;i++)A[i]=A[i-1]*i;
	B[100000]=A[100000].inv();for(uint i=100000;i;i--)B[i-1]=B[i]*i;
	for(uint i=2;i<=11;i++)
	{
		for(uint j=0;j<i;j++)V[j]=j+1;
        V[i-1]=0;
		do
		{
            if(V[i-1]==i-1)continue;
            uint p=0;
            for(uint j=0;j<i;j++){_max(p,V[j]);if(p==j)break;}
            if(++p!=i)
            {
                for(uint j=p;j<i;j++)V[j]=i+p-1-j;
                continue;
            }
            for(uint j=0;j<i;j++)QAQ[j]=0;
			uint x=0,y=0;
			for(uint j=i-1;~j;j--)
            {
                for(uint k=V[j];k;k-=lowbit(k))x+=QAQ[k];
                for(uint k=V[j]+1;k<=i;k+=lowbit(k))QAQ[k]++;
            }
			for(uint j=1;j<i;j++)y+=V[j-1]>V[j];
			if(x<=11&&y<=11)CNT[i][x][y]++;
		}
		while(std::next_permutation(V,V+i));
        // puts("qwq");
	}
    // for(uint i=1;i<=11;i++)for(uint j=1;j<=11;j++)
        // CNT[12][i][j].print(),putchar(" \n"[j==11]);
    CNT[12][11][1]=11;CNT[12][11][2]=165;CNT[12][11][3]=462;CNT[12][11][4]=330;CNT[12][11][5]=55;CNT[12][11][6]=1;
    // for(uint i=1;i<=5;i++)for(uint j=1;j<=5;j++)for(uint k=1;k<=5;k++)
    //     CNT[i][j][k].print(),putchar(" \n"[k==5]);
	User[0][0][0][0]=1;
	for(uint p=1;p<=11;p++)for(uint i=1;i<=12;i++)for(uint j=1;j<=11;j++)for(uint k=1;k<=11;k++)
        for(uint q=24;q>=i;q--)for(uint u=11;u>=j;u--)for(uint v=11;v>=k;v--)
            User[p][q][u][v]+=User[p-1][q-i][u-j][v-k]*CNT[i][j][k];
    uint t;scanf("%u",&t);
    while(t--)
    {
    	uint n,k,t;
    	scanf("%u%u%u",&n,&k,&t);
    	auto binom=[&](uint n,uint k)->modint
    	{
    		if(n<k||n>Mod||k>Mod)return 0;
    		modint ans=B[k];
    		for(uint i=n-k+1;i<=n;i++)ans*=i;
    		return ans;
    	};
    	modint ans;
    	for(uint i=1;i<=22&&i<=n;i++)for(uint j=1;j<=11;j++)ans+=binom(n-i+j,j)*User[j][i][k][t];
	    ans.println();
    }
    return 0; 
}
```

再来放张表（可以通过在上面代码基础上修改得到）：

```cpp
CNT[2][1][1]=1;
CNT[3][2][1]=2;
CNT[3][3][2]=1;
CNT[4][3][1]=3;CNT[4][3][2]=1;
CNT[4][4][1]=1;CNT[4][4][2]=4;
CNT[4][5][2]=3;
CNT[4][6][3]=1;
CNT[5][4][1]=4;CNT[5][4][2]=4;
CNT[5][5][1]=2;CNT[5][5][2]=12;CNT[5][5][3]=2;
CNT[5][6][1]=2;CNT[5][6][2]=12;CNT[5][6][3]=4;
CNT[5][7][2]=9;CNT[5][7][3]=6;
CNT[5][8][2]=3;CNT[5][8][3]=6;
CNT[5][9][3]=4;
CNT[5][10][4]=1;
CNT[6][5][1]=5;CNT[6][5][2]=10;CNT[6][5][3]=1;
CNT[6][6][1]=3;CNT[6][6][2]=28;CNT[6][6][3]=13;
CNT[6][7][1]=4;CNT[6][7][2]=35;CNT[6][7][3]=29;CNT[6][7][4]=1;
CNT[6][8][1]=3;CNT[6][8][2]=35;CNT[6][8][3]=41;CNT[6][8][4]=4;
CNT[6][9][1]=1;CNT[6][9][2]=30;CNT[6][9][3]=44;CNT[6][9][4]=7;
CNT[6][10][2]=17;CNT[6][10][3]=45;CNT[6][10][4]=7;
CNT[6][11][2]=8;CNT[6][11][3]=30;CNT[6][11][4]=11;
CNT[7][6][1]=6;CNT[7][6][2]=20;CNT[7][6][3]=6;
CNT[7][7][1]=4;CNT[7][7][2]=55;CNT[7][7][3]=50;CNT[7][7][4]=3;
CNT[7][8][1]=6;CNT[7][8][2]=80;CNT[7][8][3]=118;CNT[7][8][4]=18;
CNT[7][9][1]=6;CNT[7][9][2]=95;CNT[7][9][3]=186;CNT[7][9][4]=48;
CNT[7][10][1]=6;CNT[7][10][2]=101;CNT[7][10][3]=230;CNT[7][10][4]=85;CNT[7][10][5]=2;
CNT[7][11][1]=2;CNT[7][11][2]=94;CNT[7][11][3]=260;CNT[7][11][4]=113;CNT[7][11][5]=4;
CNT[8][7][1]=7;CNT[8][7][2]=35;CNT[8][7][3]=21;CNT[8][7][4]=1;
CNT[8][8][1]=5;CNT[8][8][2]=96;CNT[8][8][3]=145;CNT[8][8][4]=26;
CNT[8][9][1]=8;CNT[8][9][2]=155;CNT[8][9][3]=358;CNT[8][9][4]=124;CNT[8][9][5]=3;
CNT[8][10][1]=9;CNT[8][10][2]=207;CNT[8][10][3]=616;CNT[8][10][4]=313;CNT[8][10][5]=16;
CNT[8][11][1]=11;CNT[8][11][2]=250;CNT[8][11][3]=859;CNT[8][11][4]=567;CNT[8][11][5]=53;
CNT[9][8][1]=8;CNT[9][8][2]=56;CNT[9][8][3]=56;CNT[9][8][4]=8;
CNT[9][9][1]=6;CNT[9][9][2]=154;CNT[9][9][3]=350;CNT[9][9][4]=126;CNT[9][9][5]=4;
CNT[9][10][1]=10;CNT[9][10][2]=268;CNT[9][10][3]=898;CNT[9][10][4]=552;CNT[9][10][5]=48;
CNT[9][11][1]=12;CNT[9][11][2]=389;CNT[9][11][3]=1654;CNT[9][11][4]=1404;CNT[9][11][5]=204;CNT[9][11][6]=1;
CNT[10][9][1]=9;CNT[10][9][2]=84;CNT[10][9][3]=126;CNT[10][9][4]=36;CNT[10][9][5]=1;
CNT[10][10][1]=7;CNT[10][10][2]=232;CNT[10][10][3]=742;CNT[10][10][4]=448;CNT[10][10][5]=43;
CNT[10][11][1]=12;CNT[10][11][2]=427;CNT[10][11][3]=1967;CNT[10][11][4]=1887;CNT[10][11][5]=357;CNT[10][11][6]=6;
CNT[11][10][1]=10;CNT[11][10][2]=120;CNT[11][10][3]=252;CNT[11][10][4]=120;CNT[11][10][5]=10;
CNT[11][11][1]=8;CNT[11][11][2]=333;CNT[11][11][3]=1428;CNT[11][11][4]=1302;CNT[11][11][5]=252;CNT[11][11][6]=5;
CNT[12][11][1]=11;CNT[12][11][2]=165;CNT[12][11][3]=462;CNT[12][11][4]=330;CNT[12][11][5]=55;CNT[12][11][6]=1;
```






---

## 作者：Presentation_Emitter (赞：5)

~~邪道解法~~。

观察样例，猜想答案是关于 $k,x$ 其中一个的多项式。打表可得 $\forall n \ge k \ge x,f(n)$ 是一个 $x$ 次的多项式。于是下面只需要考虑 $n \le k+x \le 22$ 的情况即可。

设 $f_{n,i,S}$ 表示当前放到 $n$，逆序数为 $i$，所有 $p_r \gt p_{r+1}$ 的 $r$ 的集合为 $S$。转移即为 $\forall i \le i+n-j \lt 11,f_{n-1,i,S} \to f_{n,i+n-j,I(S,j)}$。其中 $I(S,j)$ 表示在第 $j$ 个位置后插入 $n$ 的 $S$，即：

$$
[x \in I(S,j)]=
\begin{cases}
 0 & \text{ if } x=j-1 \\
 1 & \text{ if } x=j \\
 [x \in S] & \text{ if } x\lt j-1 \\
 [x-1 \in S] & \text{ if } x\gt j
\end{cases}
$$

上述 DP 的时间复杂度为 $\Theta(n^22^n)$。用这个 DP 打一个表即可。

之后对于 $n \le 22$ 输出表中值，$n \gt 22$ 部分直接取 $k,k+1,\cdots,k+x$ 插值即可。

Code:

```cpp
cst int tb[12][12][24]={/*打的表*/};
ll T;
int main()
{
	//file(permutation);
	T=rd();
	while(T --> 0)
	{
		ll n=rd(),k=rd(),x=rd();
		if(n<=x||k<x){puts("0");continue;}
		if(n<=25){prt(tb[x][k-x][n-x-1]);continue;}
		int res=0;
		for(int i=k;i<=25;++i)
		{
			int p1=tb[x][k-x][i-x-1],p2=1;
			for(int j=k;j<=25;++j)
				if(i^j)p1=1ll*p1*(n-j)%HgS,p2=1ll*p2*(i-j)%HgS;
			p1=1ll*(HgS+p1)*qpow(HgS+p2)%HgS;pls(res,p1);
		}
		prt(res);
	}
	ret 0;
}
```

打表程序：

```cpp
int*f[25][12],ans[25][12][55];
int main()
{
	freopen("tb.out","w",stdout);
	for(int i=0;i<25;++i)for(int j=0;j<12;++j){f[i][j]=new int[1<<i];for(int s=0;s<(1<<i);++s)f[i][j][s]=0;}
	f[0][0][0]=1;
	for(int n=1;n<25;++n)
	{
		for(int i=0;i<12;++i)
		{
			for(int j=0;j<=n;++j)
			{
				if(i+n-j>11)continue;
				for(int s=0;s<(1<<(n-1));++s)
				{
					int ss=s>>j,s2=(ss<<(j+1))|(1<<j);if(j)s2|=(s-(ss<<j))&((1<<(j-1))-1);
					pls(f[n][i+n-j][s2&((1<<n)-1)],f[n-1][i][s]);
				}
			}
		}
	}
	for(int n=0;n<25;++n)for(int i=0;i<12;++i)for(int s=0;s<(1<<n);++s)pls(ans[n][i][__builtin_popcount(s)],f[n][i][s]);
	puts("cst int tb[12][12][24]={\n{{}},");
	for(int j=1;j<12&&(puts("{"),1);puts("},"),++j)for(int i=j;i<12&&(pc('{'),1);puts("},"),++i)for(int n=j+1;n<=25;++n)prt(ans[n-1][i][j],",\0"[n==25]);
	ret 0;
}
```

切完这题可以去做一下 AGC020F。

---

## 作者：do_while_true (赞：5)

> 计算长度为 $n$ 的排列数，使得有 $k$ 个逆序对，$x$ 个下降对（对于一个 $i$ 如果满足 $p_i>p_{i+1}$ 则为一个下降对）。对 $998244353$ 取模。
>
> $1 \le n \le 998244352,1 \le k \le 11,1 \le x \le 11$．

因为觉得特别有拓展意义，于是写的稍微意识流了一点！

计数问题的常见想法是，现在有很多方案，要以某种方式划分等价类，对于每个等价类先计算单独一个的方案数是多少，然后再计算这个等价类有多少种情况。

即，通过划分等价类的方式，把一个计数问题变成了对于每个等价类的计数问题。

对于这个题而言，观察一个排列的逆序对以及下降对，如果对于一个位置 $i$ 满足其前缀 $\max$ $mx_i=i$，也就是前 $i$ 个位置填着 $1\sim i$ 这些数，从这个地方划分，前半部分和后半部分之间不会产生逆序对和下降对。例如 `2 1 4 3`，可以分成前面的 `2 1` 和后面的 `4 3`，考虑每个段的相对大小关系，`2 1 4 3` 的逆序对/下降对数相当于两个 `2 1` 的逆序对/下降对数的和。

这里的启发是，按照前缀 $mx_i>i$ 来划分等价类，称之为“极长非降序段”。例如：`2 1 4 3` 不是，因为可以分成 `2 1` 和 `4 3`；而 `2 4 3 1` 是，除了最后一个位置以外其他所有位置都满足 $mx_i>i$．

并且注意到，有些连续的 $a_i=mx_i=i$ 的位置可以不用考虑，只考虑 $mx_i>i$ 的那些极长连续段，它们的相对大小关系的不同会产生逆序对以及下降对的贡献，最后的方案数就是有一些小球放进一些盒子里面的方案数了。例如：`2 1 3 4 6 5` 和 `1 3 2 4 6 5` 是等价的，前者会产生贡献的是 `2 1` 和 `6 5`，后者会产生贡献的是 `3 2` 和 `6 5`，都是两个相对大小关系为 `2 1` 的段，他们是一个等价类，对于这个等价类的方案相当于在两个捆绑在一起的组之间以及两边的 $3$ 个空隙里面放入 $6-4=2$ 个不会产生贡献的 $a_i=i$ 的数。

那么做法就很明朗了。

首先对极长非降序段的相对大小关系来 dp，注意之类要算上最后结尾的位置会 $mx_{end}=end$，经过打表发现这样的段最长超过 $12$ 就会爆掉 $k\leq 11$ 的限制，那么只对长度 $\leq 12$ 的 dp 即可。

对于每个长度 $n$ 来说，$f_{S,t1,t2,i}$ 表示已经选的集合为 $S$，有 $t1$ 个逆序对，有 $t2$ 个下降对，最后结尾为 $i$，每次找一个合法的可填的转移即可，时间复杂度是 $\mathcal{O}(2^{12}\times 11^2\times 12^3)$．

```cpp
for(n=2;n<=12;n++){
	for(int i=0;i<=all(n);i++)
		for(int j=0;j<=11;j++)
			for(int k=0;k<=11;k++)
				for(int l=0;l<=n;l++)
					f[i][j][k][l]=0;
	f[0][0][0][0]=1;
	for(int o=1;o<=n;o++){
		for(int S=0;S<=all(n);S++)
		for(int c1=0;c1<=11;c1++)
		for(int c2=0;c2<=11;c2++)
		for(int lst=0;lst<=n;lst++)
		if(f[S][c1][c2][lst]&&__builtin_popcount(S)+1==o){
			int mx=0;
			for(int i=1;i<=n;i++)
				if((S>>(i-1))&1)
					mx=i;
			for(int j=1;j<=n;j++)
				if(!((S>>(j-1))&1)){
					if(max(mx,j)>o||o==n){
						int t1=c1+__builtin_popcount(S&(all(n)-all(j)));
						int t2=c2+(lst>j);
						if(t1<=11&&t2<=11)cadd(f[S|(1<<(j-1))][t1][t2][j],f[S][c1][c2][lst]);
					}
				}
		}
	}
	for(int i=1;i<=11;i++)
		for(int j=1;j<=11;j++)
			for(int k=1;k<=n;k++)
				cadd(s[n][i][j],f[all(n)][i][j][k]);
}
```

然后将这些极长非降序段组合起来即可，由于最后算插入 $a_i=i$ 的不会产生影响的数的时候，要知道有几个空隙可以插，要插几个数，所以将这些段组合起来的过程中需要记录用了几个段，用了几个数（这里实际上也在划分等价类，然后最后算每个等价类的方案数）。这里的 $F_{a,b,c,d}$ 代表选了 $a$ 个段，用了 $b$ 个数，有 $c$ 个逆序对，$d$ 个下降对，组合起来的过程实际上是一个多维的背包。由于一个段可以在一个等价类中出现多次，所以这里先循环背包容量，再循环物品种类。这里 $b$ 的上限都是 $22$，$a$ 则是 $11$（最坏情况是 $11$ 个 `2 1`）


复杂度是 $\mathcal{O}(22\times 11^5\times 12)$

```cpp
F[0][0][0][0]=1;
for(int a=0;a<=11;a++)
	for(int b=0;b<=22;b++)
		for(int c=0;c<=11;c++)
			for(int d=0;d<=11;d++)
				if(F[a][b][c][d])
					for(n=2;n<=12;n++)
						for(int i=1;i<=11;i++)
							for(int j=1;j<=11;j++)
								if(c+i<=11&&d+j<=11)
									cadd(F[a+1][b+n][c+i][d+j],1ll*F[a][b][c][d]*s[n][i][j]%mod);
```

最后每次处理询问的时候枚举用几个段，用了几个数，然后乘上一个组合数即可。

完整代码：

```cpp
//orz meyi
#include<cstdio>
#include<vector>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<map>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x, T2& ...y){ read(x); read(y...); }
const int N=100010;
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
int n=12,f[(1<<12)+10][12][12][13];
int s[13][12][12],F[13][23][12][12];
int inv[23];
int all(int x){
	return (1<<x)-1;
}
ll qpow(ll x,ll y){
	ll s=1;
	while(y){
		if(y&1)s=s*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return s;
} 
int C(int x,int y){
	ll s=1;
	for(int i=1;i<=y;i++){
		s=1ll*s*(x-i+1)%mod*inv[i]%mod;
	}
	return s;
}
void solve(){
	int x,y,z;read(x,y,z);
	int ans=0;
	for(int i=2;i<=min(22,x);i++){
		ll tmp=x-i+1;
		for(int j=1;j<=11;j++){
			cadd(ans,1ll*F[j][i][y][z]*tmp%mod);
			tmp=1ll*tmp*(x-i+j+1)%mod*inv[j+1]%mod;
		}
	}
	cout << ans << '\n';
}
signed main(){
	inv[0]=inv[1]=1;
	for(int i=2;i<=22;i++)inv[i]=qpow(i,mod-2);
	for(n=2;n<=12;n++){
		for(int i=0;i<=all(n);i++)
			for(int j=0;j<=11;j++)
				for(int k=0;k<=11;k++)
					for(int l=0;l<=n;l++)
						f[i][j][k][l]=0;
		f[0][0][0][0]=1;
		for(int o=1;o<=n;o++){
			for(int S=0;S<=all(n);S++)
			for(int c1=0;c1<=11;c1++)
			for(int c2=0;c2<=11;c2++)
			for(int lst=0;lst<=n;lst++)
			if(f[S][c1][c2][lst]&&__builtin_popcount(S)+1==o){
				int mx=0;
				for(int i=1;i<=n;i++)
					if((S>>(i-1))&1)
						mx=i;
				for(int j=1;j<=n;j++)
					if(!((S>>(j-1))&1)){
						if(max(mx,j)>o||o==n){
							int t1=c1+__builtin_popcount(S&(all(n)-all(j)));
							int t2=c2+(lst>j);
							if(t1<=11&&t2<=11)cadd(f[S|(1<<(j-1))][t1][t2][j],f[S][c1][c2][lst]);
						}
					}
			}
		}
		for(int i=1;i<=11;i++)
			for(int j=1;j<=11;j++)
				for(int k=1;k<=n;k++)
					cadd(s[n][i][j],f[all(n)][i][j][k]);
	}
	F[0][0][0][0]=1;
	for(int a=0;a<=11;a++)
		for(int b=0;b<=22;b++)
			for(int c=0;c<=11;c++)
				for(int d=0;d<=11;d++)
					if(F[a][b][c][d])
						for(n=2;n<=12;n++)
							for(int i=1;i<=11;i++)
								for(int j=1;j<=11;j++)
									if(c+i<=11&&d+j<=11)
										cadd(F[a+1][b+n][c+i][d+j],1ll*F[a][b][c][d]*s[n][i][j]%mod);
	int T;read(T);while(T--)solve();
	return 0;
}
```

---

## 作者：Nanarikom (赞：4)

这真是一个[友善度]题啊！一句话题意是给定 $n, k, x$ 求模 $998244353$ 意义下有多少个长度为 $n$ 的 permutation $p$ 满足逆序对数为 $k$ 且有 $x$ 个 $i$ 满足 $p_i > p_{i+1}$，数据范围 $1 \leq n \leq 998244352, 1 \leq k, x \leq 11$。以下表记默认 $N=11$。首先注意到 $n$ 和 $k, x$ 的数据范围相差巨大，可以发现答案的形式是大部分位置保持 $p_i = i$，少部分位置有一些段是置换。考虑预处理 $cnt_{len, k, x}$ 表示有多少长度为 $len$ 的 permutation $p$ 满足逆序对数为 $k$ 且有 $x$ 个 $i$ 满足 $p_i > p_{i+1}$，且不存在分界点 $k$ 使得 $\max_{i=1}^{k} p_i < \min_{i=k+1}^{len} p_i$（否则应该拆分为两段）。其中 $1 \leq len \leq N + 1, 1 \leq k, x \leq N$，故这一步直接爆搜所有排列的时间复杂度是 $O(N \log N \cdot N!)$。这里看上去很难接受，但实际上 $k > N$ 的时候可以直接剪枝，非常快，最后实际上只有大约 $2 \times 10^4$ 个 permutation 合法。则以下我们考虑一个 DP：令 $dp_{siz, len, k, x}$ 表示有 $siz$ 个不满足 $p_i = i$ 的连续段，这些段的长度之和是 $len$，且一共产生 $k$ 个逆序对，一共有 $x$ 个 $i$ 满足 $p_i > p_{i+1}$ 的方案数。不难看出转移如下：
$$
dp_{siz, len, k, x} \times cnt_{\Delta len, \Delta k, \Delta x} \rightarrow dp_{siz + 1, len + \Delta len, k + \Delta k, x + \Delta x}
$$
虽然光看变量数这个 DP 看上去是 $O(N^7)$ 的有点悬，不过实际上搜出来 $cnt$ 里不为 $0$ 的位置只占大概十分之一，可以扔进 map 之类的里面跳过空白的位置，实际复杂度大概是 $O(N^4 |cnt|)$，这样就稳多了。到这里就预处理完了，最终每组的答案的计算方式就是考虑枚举 $siz$ 和 $len$，则此时你要把 $n - len$ 个 $p_i=i$ 的位置用插板法插到 $siz$ 个段之间，此时的方案数是 $\binom{n - len + siz}{n - len} \cdot dp_{siz, len, k, x}$。此处组合数因为 $n$ 很大没法预处理但是可以 $O(siz)$ 暴力计算。时间复杂度 $O(TN^3)$。

虽然如果你对背包的理解很好的话就不用我强调了，不过还是提示一下注意这个类背包的 DP 里枚举的顺序——它是完全背包而非 01 背包，而且物品之间是有顺序的所以物品应该在最内层而非最外层枚举。

代码意外得不太慢，跑了 400 多 ms。虽然不觉得自己的代码好看的还是给万一需要的人贴一下好了。

```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
#define MULTI int _T; cin >> _T; while(_T--)
using namespace std;

typedef long long ll;

const int N = 13;
const int INF = 0x3f3f3f3f;
const ll INFF = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
template <typename T> bool chkmin (T &x, T y) {return y < x ? x = y, 1 : 0;}
template <typename T> bool chkmax (T &x, T y) {return y > x ? x = y, 1 : 0;}

ll qpow (ll n, ll m) {
	ll ret = 1;
	while (m) {
		if (m & 1) ret = ret * n % mod;
		n = n * n % mod;
		m >>= 1;
	}
	return ret;
}
ll getinv (ll a) {
	return qpow(a, mod - 2);
}

struct BIT {
	int n, c[N];
	void init (int _n) {n = _n; for (int i = 0;i <= n;++i) c[i] = 0;}
	int lowbit (int x) {return x & (-x);}
	void update (int i, int x) {while (i <= n) {c[i] += x; i += lowbit(i);}}
	int query (int i) {int ret = 0; while (i) {ret += c[i]; i -= lowbit(i);} return ret;}
} bit;

int len;
int p[N], vis[N];
int premax[N], sufmin[N];
map <tuple <int, int, int>, int> cnt;
void dfs (int u, int curk, int curx) {
	if ((curk > 11) || (curx > 11)) return;
	if (u == len + 1) {
		premax[0] = 0;
		sufmin[len + 1] = INF;
		for (int i = 1;i <= len;++i) premax[i] = max(premax[i - 1], p[i]);
		for (int i = len;i >= 1;--i) sufmin[i] = min(sufmin[i + 1], p[i]);
		for (int i = 1;i <= len - 1;++i) if (premax[i] < sufmin[i + 1]) return;
		// for (int i = 1;i <= len;++i) cout << p[i] << " "; cout << ": " << curk << ' ' << curx << endl;
		cnt[make_tuple(len, curk, curx)]++;
		return;
	}
	
	for (int i = 1;i <= len;++i) if (vis[i] == 0) {
		if ((u == 1) && (i == 1)) continue;
		if ((u == len) && (i == len)) continue;
		vis[i] = 1;
		bit.update(i, 1);
		
		p[u] = i;
		dfs(u + 1, curk + (i - bit.query(i)), curx + ((u >= 2) && (p[u - 1] > p[u])));
		
		vis[i] = 0;
		bit.update(i, -1);
	}
}
ll dp[N][N * 2][N][N];
void init () {
	for (len = 1;len <= 12;++len) {
		bit.init(len);
		memset(p, 0, sizeof p);
		dfs(1, 0, 0);
	}
	
	dp[0][0][0][0] = 1;
	for (int siz = 0;siz <= 11;++siz) {
		for (int len = 0;len <= 22;++len) {
			for (int k = 0;k <= 11;++k) {
				for (int x = 0;x <= 11;++x) if (dp[siz][len][k][x]) {
					for (auto [d, times] : cnt) {
						auto [dlen, dk, dx] = d;
						if (siz + 1 > 11) continue;
						if (len + dlen > 22) continue;
						if (k + dk > 11) continue;
						if (x + dx > 11) continue;
						(dp[siz + 1][len + dlen][k + dk][x + dx] += dp[siz][len][k][x] * times) %= mod;
					}
				}
			}
		}
	}
}

int n, k, x;
ll cmn (ll m, ll n) {
	n = min(n, m - n);
	ll ret = 1;
	for (int i = m;i >= m - n + 1;--i) {
		ret = ret * i % mod;
	}
	for (int i = 1;i <= n;++i) {
		ret = ret * getinv(i) % mod;
	}
	return ret;
}

int main () {
	init();
	
	MULTI {
		cin >> n >> k >> x;
		
		ll ans = 0;
		for (int siz = 1;siz <= 11;++siz) for (int len = 1;len <= min(n, 22);++len) if (dp[siz][len][k][x]) {
			// cout << siz << ' ' << len << ' ' << k << ' ' << x << ':' << cmn(n - len + siz, n - len) << ' ' << dp[siz][len][k][x] << endl;
			ans += cmn(n - len + siz, n - len) * dp[siz][len][k][x];
			ans %= mod;
		}
		cout << ans << endl;
	}
}
```


---

## 作者：Moeebius (赞：2)

> 定义一个子段 $\{p_l,p_{l+1},\dots,p_r\}$ 是**置换**的，当且仅当其值域也为 $[l,r]$。
>
> 定义一个置换子段是**本原**的，当且仅当其无法通过若干置换子段拼接得到。
>
> 定义一个本原置换子段是**非平凡**的，当且仅当其长度大于 $1$。

则有以下结论：

- 总是可以将一个排列划分为若干本原置换子段，且划分方法唯一。

略。

- 划分出的本原置换子段，两两之间不存在逆序对和下降。

由置换性，可得任意两段间值域不交，即得。$\square$

- 满足题意的排列，其划分出的非平凡本原置换子段**数量**不超过 $11$。

每个非平凡的本原置换子段一定不可能单调递增（否则一定可以通过若干个平凡子段拼接得到），即至少有一个下降位置，而本题中要求下降数不超过 11。$\square$

- 满足题意的排列，其划分出的非平凡本原置换子段**长度和**不超过 $22$。

> @[蒟蒻君HJT](https://www.luogu.com.cn/user/131591) 对这个结论的证明是错误的，详见[这个讨论](https://www.luogu.com.cn/discuss/962167)。

考虑一个长度为 $l(l>1)$ 的非平凡本原置换子段 $\{a\}$。

我们维护一个指针 $p$，初始时 $p=1$。接下来我们找到 $p$ 右边第一个比 $a_p$ 小的数 $a_q$。（由于本原性，我们一定能找到这样的一个 $q$。）

此时，$a_p,a_{p+1},\dots,a_{q-1}$ 这 $q-p$ 个数都能与 $a_q$ 形成逆序对。接下来，我们让 $p\gets q$。也就是说，我们让 $p$ 增大 $q-p$ 的时候，也同时获得了 $q-p$ 个逆序对。当 $p=l$ 时我们终止流程，此时 $p$ 增大了 $l-1$，因此该子段至少存在 $l-1$ 个逆序对。

而序列总逆序对数不超过 11，故序列总长度不超过 $(1+1)\times11=22$。$\square$

下记 $m$ 为逆序对数和下降数的上界。

---

有了上述结论后，考虑 DP 计数非平凡本原置换子段，之后背包合并。

记 $f_{i,j,k,o,p}$ 表示长度为 $i$，逆序对数为 $j$，下降数为 $k$，最后一个位置为 $o$，还需要一个 $\le p$ 的数才能使其具有本原性的排列个数。特别地，$p=0$ 表示没有限制。

转移时考虑填在末尾的数 $x(1 \le x \le i)$（将之前填写的 $[x,i)$ 内的数均加上 $1$）。

- 若 $x \le p$，则限制得到满足，$p \gets 0$。
- 若 $x = i$，则增加一条限制 $i-1$，注意到这条限制只有当 $p=0$ 时才有影响。

其余变量的更新是简单的。

这部分复杂度 $O(m^6)$。

---

记 $g_{i,j,k,p}$ 表示总长为 $i$，由 $j$ 个非平凡本原置换段拼接得到，逆序对数、下降数分别为 $k,p$ 的序列个数。可以在 $O(m^7)$ 的复杂度内完成转移。

---

最后需要统计答案，假设要求的长度、逆序对数和下降数分别为 $n,x,y$。考虑枚举非平凡位置数量 $i$、段数 $j$。则相当于将剩下 $n-i$ 个数分成 $j+1$ 段（可空），贡献为 $\binom{n-i+j}{j}\cdot g_{i,j,x,y}$。其中组合数直接按定义计算，需要预处理阶乘逆元，单次复杂度 $O(m^3)$。

---

## 作者：kyEEcccccc (赞：2)

有趣的题。

我们要求逆序对小于 $11$，考虑计算逆序对时在两个位置都计算一遍，则总个数不超过 $22$。如果一个位置不是任何逆序对端点，那么它满足 $a_i = i$，且左右两边互不影响。这样我们只需要考虑最多 $22$ 个位置，它们会构成一些连续段，显然一个数所有的逆序对都来自它所属的连续段内部，于是我们考虑对连续段 DP，具体地求出长度为 $i$ 的排列，有 $k$ 个逆序对和 $l$ 个下降位置的方案数 $g_{i,k,l}$。这个可以用状压 DP。设 $f_{S, k, l, t}$ 表示已经填了 $S$ 中数，最后一个填 $t$，随便做即可，但复杂度里面算出来是 $22^2\times11^2\times2^{22}$，有点小/xia。考虑当前已经填的数集合 $S$，显然所有其中元素对不在其中的元素会构成一些必然存在的逆序对，假如这些逆序对已经超过 $11$ 个，这个状态就废了。搜一下发现有效的 $S$ 只有 $2861$ 个。接下来求出 $h_{i, j, k, l}$ 表示共 $i$ 个有效数形成 $j$ 段，回答询问时枚举 $i, j$，将这一状态放进长为 $n$ 的序列中方案数就是 $\binom{n-i+1}{j}$。求这个东西的时间大概是 $22^2\times11^5$ 且远远跑不满。

代码

```cpp
// Author: kyEEcccccc

#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using ULL = unsigned long long;

#define F(i, l, r) for (int i = (l); i <= (r); ++i)
#define FF(i, r, l) for (int i = (r); i >= (l); --i)
#define MAX(a, b) ((a) = max(a, b))
#define MIN(a, b) ((a) = min(a, b))
#define SZ(a) ((int)((a).size()) - 1)

constexpr int MOD = 998244353;

LL kpow(LL x, LL k = MOD - 2)
{
	LL r = 1;
	x = x % MOD;
	while (k)
	{
		if (k & 1) r = r * x % MOD;
		x = x * x % MOD;
		k >>= 1;
	}
	return r;
}

int id[1 << 22];
vector<int> stts;
int f[3000][22][12][12];
int g[23][12][12], h[23][12][12][12];
int ifac[12];

signed main(void)
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr);

	F(w, 0, (1 << 22) - 1)
	{
		int tot = 0, t = 0;
		F(i, 0, 22 - 1)
		{
			if (w >> i & 1) tot += t;
			else ++t;
		}
		if (tot > 11) id[w] = -1;
		else
		{
			id[w] = stts.size();
			stts.push_back(w);
		}
	}
	ifac[0] = 1;
	F(i, 1, 11) ifac[i] = ifac[i - 1] * kpow(i) % MOD;

	f[0][0][0][0] = 1;
	F(i, 1, SZ(stts))
	{
		int w = stts[i];
		F(j, 0, 22 - 1)
		{
			if (!(w >> j & 1)) continue;
			if (w == (1 << (j + 1)) - 1) continue;
			if (id[w ^ 1 << j] == -1) continue;
			F(t, 0, 22 - 1)
			{
				if ((t != 0 || (w ^ 1 << j) != 0) && (t == j || !(w >> t & 1))) continue;
				int dk = __builtin_popcount(w >> (j + 1)), dl = j < t ? 1 : 0;
				F(k, 0, 11 - dk) F(l, 0, k)
					(f[i][j][k + dk][l + dl] += f[id[w ^ 1 << j]][t][k][l]) %= MOD;
			}
		}
	}
	F(i, 1, 22) F(t, 0, i - 1) F(j, 0, 11) F(l, 0, j)
		(g[i][j][l] += f[id[(1 << i) - 1]][t][j][l]) %= MOD;
	h[0][0][0][0] = 1;
	F(i, 1, 22) F(j, 1, i / 2) F(k, 1, 11) F(l, 1, k)
	{
		F(di, 2, i - (j - 1) * 2) F(dk, 1, k) F(dl, 1, min(dk, l))
		{
			h[i][j][k][l] = (h[i][j][k][l] + (LL)h[i - di][j - 1][k - dk][l - dl] * g[di][dk][dl]) % MOD;
		}
	}

	int _;
	cin >> _;
	while (_--)
	{
		int n, a, b;
		cin >> n >> a >> b;
		LL ans = 0;
		F(i, 1, 22)
		{
			if (i > n) break;
			LL x = 1;
			F(j, 1, i / 2)
			{
				if (j > n - i + 1) break;
				(x *= (n - i + 1) - j + 1) %= MOD;
				(ans += h[i][j][a][b] * x % MOD * ifac[j]) %= MOD;
			}
		}
		cout << ans << '\n';
	}
	
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

记 $\max(k,x)=N$。

我想来讲一下正经一点的，不搜索不打表的 $\mathcal{O}(N^7)$ dp 的做法。

考虑将排列划分为极小的若干个区间 $[l_i,r_i]$ 使得 $p_{l_i}\sim p_{r_i}$ 恰好为数字 $l_i\sim r_i$ 的排列（本原连续段）。这样做的好处是，两段之间绝对不可能存在逆序和下降，且这种划分方式一定是唯一的。

下证：

1. 非严格递增的 $[l_i,r_i]$ 至多有 $11$ 个。

原因：每个非严格递增的区间必存在下降。

2. 非严格递增的 $[l_i,r_i]$ 区间长度总和不超过 $22$。

原因：假定 $[l_i,r_i]$ 长度为 $len\geq 2$，对于所有 $i\in[l_i,r_i-1]$，$[l_i,i]$ 与 $[i+1,r_i]$ 这两个区间之间必然存在逆序对，否则 $\max([l_i,i])<\min([i+1,r_i])$，这个区间就不是本原连续段了。

因此长度为 $len$ 的区间至少存在 $len-1$ 个逆序对，也即区间长度总和不超过 $2\times 11=22$。

由此可以发现 $p_i=i$ 对绝大多数 $i$ 成立，那么我们只需要考虑那些非递增的 $[l_i,r_i]$，最后插板把 $n-c(c\leq22)$ 个数插进去就可以。

考虑先对每段 dp。

容易想到设 dp 状态 $f_{i,x,y,j}$ 表示长度为 $i$ 的排列，逆序数为 $x$，下降数为 $y$，最后一个数是 $j$ 的方案数。转移即枚举 $p_i=k$。

但这样是错的，因为没有保证其是本原连续段。

问题出在哪里？

举个例子，$i=4$ 时，若枚举 $p_i=p_4=4$，那么其实当前状态下 $p_1\sim p_3$ 可以被划分出去。为了保证本原性，一定要在之后的某个 $p_z$ 处，令 $p_z=1/2/3$，把 $3$ “抬升”上去才可以。

由此可以看出我们还需要记一维状态 $u$ 表示要求之后的某一个 $p_z$ 必须 $\leq u$，$u=0$ 表示无要求。

初始化 $dp_{1,0,0,1,1}=1$，之后每次取 $p_i=i(i\geq 2)$ 时，将 $u$ 更新为 $\min(u,i-1)$，而取 $p_i\leq u$ 时，将 $u$ 更新为 $0$ 即可。 

转移的总复杂度为 $\mathcal{O}(N^6)$。

然后求出 $g_{i,j,x,y}$ 表示 $j$ 个长度和为 $i$ 的区间，共有 $x$ 个逆序数和 $y$ 个下降数的方案数，简单背包合并即可，复杂度 $\mathcal{O}(N^7)$。

对每组询问 $(n,k,m)$，枚举非严格递增的区间个数为 $j$，长度总和为 $i$，余下 $n-i$ 个数插进 $j+1$ 个空隙里，空隙可空，方案数 $g_{i,j,k,m}\times \begin{pmatrix} n-i \\ j \end{pmatrix}$，组合数下指标较小，用定义求，然后累和即可。最后一部分复杂度 $\mathcal{O}(TN^3)$。

code

```cpp
#include <bits/stdc++.h>
const int mod = 998244353;
inline int mul(int x, int y){
  return (int)(1ll * x * y % (1ll * mod));
}
inline int add(int x, int y){
  return x + y >= mod ? x + y - mod : x + y;
}
inline int minus(int x, int y){
  return x < y ? x - y + mod : x - y;
}
inline int Qpow(int x, int y){
  int r = 1;
  while(y){
    if(y & 1) r = mul(r, x);
    x = mul(x, x);
    y >>= 1;
  }
  return r;
}
int f[13][12][12], g[23][12][12][12], ifac[12];
inline int C(int x, int y){
  int r = 1;
  for(int i = x; i >= x - y + 1; --i) r = mul(r, i);
  for(int i = 1; i <= y; ++i) r = mul(r, ifac[i]);
  return r;
}
void solve(){
  int n, k, m; int ans = 0;
  scanf("%d%d%d", &n, &k, &m);
  for(int i = 1; i <= 22 && i <= n; ++i)
    for(int j = 1; j <= 11; ++j)
       ans = add(ans, mul(g[i][j][k][m], C(n - i + j, j)));
  printf("%d\n", ans);
  return ;
}
int dp[13][12][12][13][13];
int main(){
  int T = 1;
  scanf("%d", &T);
  ifac[0] = 1;
  for(int i = 1; i <= 11; ++i) ifac[i] = Qpow(i, mod - 2);
  dp[1][0][0][1][1] = 1;
  for(int i = 2; i <= 12; ++i)
    for(int x = 0; x <= std::min(11, (i - 2) * (i - 1) / 2); ++x)
      for(int y = 0; y <= i - 2; ++y)
        for(int j = 1; j <= i - 1; ++j)
          for(int u = 0; u <= i - 1; ++u){
            if(!dp[i - 1][x][y][j][u]) continue;
            for(int k = 1; k <= i; ++k){
              int rj, nx, ny, nu;
              if(j >= k) rj = j + 1;
              else rj = j;
              if(rj > k) ny = y + 1;
              else ny = y;
              nx = x + i - k;
              if(nx > 11 || ny > 11) continue;
              if(k <= u) nu = 0;
              else nu = u;
              if(k == i && u == 0) nu = k - 1;
              dp[i][nx][ny][k][nu] = add(dp[i][nx][ny][k][nu], dp[i - 1][x][y][j][u]);
            }
          }
  for(int i = 1; i <= 12; ++i)
    for(int x = 0; x <= 11; ++x)
      for(int y = 0; y <= 11; ++y)
        for(int j = 1; j <= i; ++j)
          f[i][x][y] = add(f[i][x][y], dp[i][x][y][j][0]);
  g[0][0][0][0] = 1;
  for(int j = 1; j <= 11; ++j)
    for(int i = 1; i <= 22; ++i)
      for(int x = 0; x <= 11; ++x)
        for(int y = 0; y <= 11; ++y)
          for(int oi = 2; oi <= i && oi <= 12; ++oi)
            for(int ox = 0; ox <= x; ++ox)
              for(int oy = 0; oy <= y; ++oy)
                g[i][j][x][y] = add(g[i][j][x][y], mul(g[i - oi][j - 1][x - ox][y - oy], f[oi][ox][oy]));
  while(T--) solve();
  return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

# 一、性质
对于一个区间如果无法划分成两半使得前一半全部小于后一半，并且是区间中的值域是连续的，则这个区间至少可以提供 $1$ 个下降数，和 $len-1$ 个逆序对，因此这样的区间最多有 $11$ 个，且总长度最多为 $22$。
### 证明：
下降数：若没有 $1$ 个下降数，则序列上升，不满足定义。

逆序对：考虑使用数学归纳法，对于长度小于等于 $2$ 的区间显然成立，对于更大的区间，将其分成两半后，前一半和后一半至少有一对逆序对，所以成立。
# 二、解法
对于一个满足上述条件的区间可以将所有数减小，变成一个排列。

设 $f_{i,j,k,w}$ 表示区间总长度为 $i$，区间个数为 $j$，逆序对数量为 $k$，下降数为 $w$ 的方案数。

那么答案就是 $\sum\limits_{i-1}^{\min(n,22)}\sum\limits_{j=1}^{min(11,\lfloor\frac{i}{2}\rfloor)}f_{i,j,k,x}\times C_{n-i+j}^{j}$

考虑 $f$ 的求法，设 $g_{i,j,k}$ 表示一个区间长度为 $i$，逆序对数量为 $j$，下降数为 $k$ 的方案数。

那么就可以轻松的从 $g$ 转移到 $f$。

考虑 $g$ 的求法，考虑状压，设 $h_{i,j,k,w}$，表示一个区间每个数的选择情况为 $i$，逆序对数量为 $j$，下降数为 $k$，以 $w$ 结尾的方案数，这个区间可以不完整。

$h$ 可以直接转移，$g$ 可以由 $h$ 转移。

综上，设 $N=11$，则时间复杂度为 $O(2^N\times N^4+N^7+T\times N^2)$
# 三、代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,l,g[4101],f[4101][13][13][13],cn[13][13][13],cq[23][13][13][13],ny[13],ans,C;
const int mo=998244353;
int mi(int x,int y){
	int re=1;
	while(y>0){
		if(y&1)
			re=1ll*re*x%mo;
		y>>=1;
		x=1ll*x*x%mo;
	}
	return re;
}
int main(){
	for(int i=1;i<=12;i++)
		f[(1<<i-1)][0][0][i]=1;
	for(int i=1,ii;i<(1<<12);i++)
		g[i]=g[i^(i&-i)]+1;
	for(int i=1,ii;i<(1<<12);i++)
		for(int j=0,jj;j<=11&&j*2<=g[i]*(g[i]-1);j++)
			for(int w=0;w<=11&&w<g[i];w++){
				jj=j-g[i]+1;
				for(int k=g[(i&-i)-1]+1;;k=g[((i>>k)&-(i>>k))-1]+k+1){
					ii=(i^(1<<k-1));
					if(jj>=0&&ii+1!=(1<<g[ii])){
						for(int kk=g[(ii&-ii)-1]+1;;kk=g[((ii>>kk)&-(ii>>kk))-1]+kk+1){
							if(w-(kk>k)>=0){
								f[i][j][w][k]+=f[ii][jj][w-(kk>k)][kk];
								f[i][j][w][k]>=mo?f[i][j][w][k]+=mo:0;
							}
							if((ii>>kk)==0)
								break;
						}
					}
					if(i+1==(1<<g[i])){
						cn[g[i]][j][w]+=f[i][j][w][k];
						cn[g[i]][j][w]>=mo?cn[g[i]][j][w]-=mo:0;
					}
					if((i>>k)==0)
						break;
					jj++;
				}
			}
	cq[0][0][0][0]=1;
	for(int i=1;i<=22;i++)
		for(int j=1;j<=11&&j*2<=i;j++)
			for(int k=0;k<=11&&k*2<=(i-1)*i;k++)
				for(int w=0;w<=11&&w<=i-j;w++)
					for(int ii=2;ii<=12&&ii<=i;ii++)
						for(int kk=0;kk<=k;kk++)
							for(int ww=0;ww<=w;ww++){
								cq[i][j][k][w]+=1ll*cq[i-ii][j-1][k-kk][w-ww]*cn[ii][kk][ww]%mo;
								cq[i][j][k][w]>=mo?cq[i][j][k][w]-=mo:0;
							}
	for(int i=1;i<=11;i++)
		ny[i]=mi(i,mo-2);
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&l);
		ans=0;
		for(int i=1;i<=22&&i<=n;i++){
			C=1;
			for(int j=1;j<=11&&j*2<=i;j++){
				C=1ll*C*(n-i+j)%mo*ny[j]%mo;
				ans+=1ll*cq[i][j][m][l]*C%mo;
				ans>=mo?ans-=mo:0;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

