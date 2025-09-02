# Sherlock and the Encrypted Data

## 题目描述

Sherlock found a piece of encrypted data which he thinks will be useful to catch Moriarty. The encrypted data consists of two integer $ l $ and $ r $ . He noticed that these integers were in hexadecimal form.

He takes each of the integers from $ l $ to $ r $ , and performs the following operations:

1. He lists the distinct digits present in the given number. For example: for $ 1014_{16} $ , he lists the digits as $ 1,0,4 $ .
2. Then he sums respective powers of two for each digit listed in the step above. Like in the above example $ sum=2^{1}+2^{0}+2^{4}=19_{10} $ .
3. He changes the initial number by applying bitwise xor of the initial number and the sum. Example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF776G/959289a189ff1fca05b0806d5e720756eddc35a9.png). Note that xor is done in binary notation.

One more example: for integer 1e the sum is $ sum=2^{1}+2^{14} $ . Letters a, b, c, d, e, f denote hexadecimal digits $ 10 $ , $ 11 $ , $ 12 $ , $ 13 $ , $ 14 $ , $ 15 $ , respertively.

Sherlock wants to count the numbers in the range from $ l $ to $ r $ (both inclusive) which decrease on application of the above four steps. He wants you to answer his $ q $ queries for different $ l $ and $ r $ .

## 说明/提示

For the second input,

 $ 14_{16}=20_{10} $

 $ sum=2^{1}+2^{4}=18 $

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF776G/9208143c550bbdde0f9599d03b249de570f4e364.png)

Thus, it reduces. And, we can verify that it is the only number in range $ 1 $ to $ 1e $ that reduces.

## 样例 #1

### 输入

```
1
1014 1014
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 1e
1 f
```

### 输出

```
1
0
```

## 样例 #3

### 输入

```
2
1 abc
d0e fe23
```

### 输出

```
412
28464
```

# 题解

## 作者：Alex_Wei (赞：3)

> G. [CF776G Sherlock and the Encrypted Data](https://www.luogu.com.cn/problem/CF776G) *2900

> $q$ 组询问，以 16 进制的形式给出 $L, R$，求出满足以下条件的整数 $x$ 的个数。
>
> 1. $L\leq x \leq R$。
> 2. $f(x) < x$。其中 $f(x)$ 定义如下：
>
> 设 $x$ 在 16 进制下的数位分别为 $\overline{d_k d_{k - 1} d_{k - 2} \cdots d_0}$，令 $y = \sum\limits_{i = 0} ^ {15} 2 ^ i[i\in d]$，则 $f(x) = x \oplus y$。换句话说，$f(x)$ 等于 $x$ 异或上 “$2$ 的 “所有在 $x$ 的 16 进制下出现的数码” 次幂之和”。
>
> $1\leq q\leq 10 ^ 4$，$0\leq L\leq R < 16 ^ {15}$。

考虑数位 DP，用 $\leq R$ 的符合条件 2 的数的个数减去 $< L$​ 的符合条件 2 的数的个数。

令 $D = \max d$。我们只关心 $x$ 在二进制下第 $D$ 位的取值。因为若为 $1$，则 $f(x)$ 的第 $D$ 位为 $0$（而高位不变因为 $D$ 已经是最高位了），$f(x) < x$；否则 $f(x)$ 的第 $D$ 位为 $1$，$f(x) > x$​。

因此，直接枚举 $D$，套路地设 $f_{i, j, k}$ 表示当前考虑了高 $i$ 位（16 进制下），是否已经存在一位满足 $d_p = D$ 以及是否顶到上界。根据实际意义枚举下一位转移即可，注意考虑 $D$，顶到上界的 $d_{p - 1}(R)$ 以及 **二进制下** 第 $D$ 位为 $0$ 的限制。

答案即对 $R$ 求的 $\sum\limits_{D = 0} ^ {15} f_{0, 1, 0} + f_{0, 1, 1}$ 减去对 $L$ 求的 $\sum\limits_{D = 0} ^ {15} f_{0, 1, 0}$，因为前者是 $\leq$，后者是 $<$。

时间复杂度 $\mathcal{O}(qw ^ 3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 16;
long long q, ans, f[N][2][2];
long long calc(char *s, bool type) {
	long long n = strlen(s), d[N], ans = 0;
	reverse(s, s + n); // ADD THIS LINE
	for(int i = 0; i < n; i++) d[i] = isdigit(s[i]) ? s[i] - '0' : s[i] + 10 - 'a';
	for(int mxd = 0; mxd < N; mxd++) {
		memset(f, 0, sizeof(f)), f[n][0][1] = 1;
		if(mxd >= n << 2) continue;
		for(int p = n; p; p--) {
			for(int x : {0, 1}) {
				for(int y : {0, 1}) {
					if(!f[p][x][y]) continue;
					for(int dig = 0; dig <= mxd; dig++) {
						if((mxd >> 2) == p - 1 && dig >> mxd - (p - 1 << 2) & 1 ^ 1) continue;
						if(y && dig > d[p - 1]) continue;
						f[p - 1][x | (dig == mxd)][y & (dig == d[p - 1])] += f[p][x][y];
					}
				}
			}
		}
		ans += f[0][1][0] + type * f[0][1][1];
	}
	return ans;
}
int main() {
	// freopen("1.in", "r", stdin);
	cin >> q;
	for(int i = 1; i <= q; i++) {
		char s[N];
		scanf("%s", s), ans = -calc(s, 0);
		scanf("%s", s), cout << ans + calc(s, 1) << endl;
	}
	return 0;
}

/*
2022/4/28
start thinking at ??:??

回家路上想的.
注意到只和 maxdigit 有关, maxdigit 的位置决定了其大小.
直接枚举 maxdigit DP 即可.
f_{i, j, k} 表示考虑高 i 位, 是否出现 maxdigit, 是否顶到上界
时间复杂度 q * base ^ 2 * log_{base} n 


start coding at 21:13
finish debugging at 21:37
*/
```

---

## 作者：aison (赞：1)

题意：问$[L,R]$区间里有多少个数在进行下列三次操作后变小：

1. 写成$16$进制，把每个不同数位列出来. 

1. 对于每个数位，计算$2$的对应次幂，求和得到$sum$. 

1. 将原数与$sum$异或. $L,R\le 16^{15}$

解：很容易想到数位$dp$。不难发现第$2$步算出的和最多只能有$2^{16}-1$，也就是只影响原数十六进制下的最后$4$位。那么怎么设计状态呢？如果将这个和直接加入状态，那么总状态数至少是（位数×状态数=$16 * 2^{16} $），乘上数据组数的话显然会超时。那么怎么简化状态呢？其实我们可以不用存储整个$sum$。“异或后减小”这个条件可以转化成：原数中$sum$的最高位的那一位也是$1$，因为比这一位更高的位异或后不会变化，这一位异或后从$1$变为$0$，那么根据二进制数的性质原数一定会减小。所以我们只需要存储$sum$的最高位就可以了。

在代码实现的过程中，我们不必将$sum$的最高位保存在真正的状态中，可以枚举$sum$的最高位，设为第$high$位，将它保存在全局变量中然后直接做16进制的数位dp。枚举的时候每一位最多枚举到$high$，注意在枚举$high$所在的那个16进制数位的时候，要保证这一位上的数满足“原数中$sum$的最高位的那一位也是$1$”这个条件。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll dp[2][16];
int a[20];
int high;
ll dfs(int pos,int state,bool lead,bool limit)
/*pos表示枚举到第pos位，state表示当前枚举的数位中是否存在某一位的值为high*/
{
    if(pos==-1)return state;
    if(!limit&&!lead&&dp[state][pos]!=-1)return dp[state][pos];
    int up=limit?a[pos]:15;
    up=min(up,high);
    ll ans=0;
    for(int i=0;i<=up;i++)
    {
    	if((pos<<2)==((high>>2)<<2)&&!(i>>(high%4)&1))continue;
        /*如果枚举到high所在的16进制位要特判*/
    	int nstate=state;
    	if((lead&&i==0)==0)/*无前导0*/
    	{
    		if(i==high)nstate=1;
    	}
    	ans+=dfs(pos-1,nstate,lead&&i==0,limit&&i==a[pos]);
    }
    if(!limit&&!lead) dp[state][pos]=ans;
    return ans;

}
ll work(ll t)
{
	if(t<=0)return 0;
	int cnt=0;
	while(t)
	{
		a[cnt++]=t%16;
		t>>=4;
	}
	ll ans=0;
	for(high=4;high<min(16,cnt*4);high++)/*这里偷了个懒，high=0-3是不可能的*/
	{
		memset(dp,-1,sizeof(dp));
		ans+=dfs(cnt-1,0,1,1);
	}
	return ans;
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		ll l,r;
		scanf("%llx%llx",&l,&r);	
		printf("%lld\n",work(r)-work(l-1));
	}
	return 0;
}

```


---

## 作者：happybob (赞：0)

显然 $x \oplus y<x$ 等价于 $y$ 的最靠左的 $1$ 的位在 $x$ 中也为 $1$。

枚举 $k$ 为 $x$ 在 $16$ 进制表达下的最大数码，则可以直接从后往前做数位 DP，记 $f_{i,0/1,0/1}$ 表示到了第 $i$ 位，是否有最高位顶满的限制，后面是否存在某一位为 $k$，复杂度 $O(q \log^3 V)$。

---

## 作者：Vidoliga (赞：0)

提供 2log 做法。

典题数位 dp，考虑找 $f(x)<x$ 充要条件。

显然的设 $k= \max d$，不难发现当且仅当，$x$ 在二进制第 $k$ 位为 $1$ 时满足。

恰好等于 $k$ 不好算，容斥一下算 $\leq k$ 减去 $<k$。

设 $f_{i,0/1}$ 表示前 $i$ 位是否打破上界限制，每个 $16$ 进制位 $\leq k$ 且在二进制第 $k$ 位为 $1$ 时的方案数，$g_{i,0/1}$ 表示前 $i$ 位是否打破上界限制，每个 $16$ 进制位 $< k$ 且在二进制第 $k$ 位为 $1$ 时的方案数。

复杂度 $O(n \log^2 n)$。

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast","unroll-loops","inline")
#include<bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
const int LGN=16;
char L[LGN+10],R[LGN+10];int f[LGN+10][2],g[LGN+10][2],mx[LGN+10],v[LGN+10][4];
int calc(int x){
	if(!~x) return 0;
	for(int i=0;i<LGN;i++) mx[i]=x&15,x>>=4;
	int res=0;
	for(int d=0;d<LGN;d++){
		int p=d/4,q=d&3;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[16][1]=1;g[16][1]=1;
		for(int i=LGN-1;~i;i--){
			for(int s=0;s<2;s++){
				int lim=s?min(d,mx[i]):d;
				if(i==p){
					if((lim>>q&1)&&s){
						f[i][0]=f[i][0]+f[i+1][s]*(v[lim][q]-1),f[i][mx[i]==lim]=f[i][mx[i]==lim]+f[i+1][s];
					}
					else f[i][0]=f[i][0]+f[i+1][s]*v[lim][q];
				}
				else{
					if(s) f[i][0]=f[i][0]+f[i+1][s]*lim,f[i][mx[i]==lim]=f[i][mx[i]==lim]+f[i+1][s];
					else f[i][0]=f[i][0]+f[i+1][s]*(lim+1);
				}
			}
		}
		if(d) for(int i=LGN-1;~i;i--){
			for(int s=0;s<2;s++){
				int lim=s?min(d-1,mx[i]):d-1;
				if(i==p){
					if((lim>>q&1)&&s){
						g[i][0]=g[i][0]+g[i+1][s]*(v[lim][q]-1),g[i][mx[i]==lim]=g[i][mx[i]==lim]+g[i+1][s];
					}
					else g[i][0]=g[i][0]+g[i+1][s]*v[lim][q];
				}
				else{
					if(s) g[i][0]=g[i][0]+g[i+1][s]*lim,g[i][mx[i]==lim]=g[i][mx[i]==lim]+g[i+1][s];
					else g[i][0]=g[i][0]+g[i+1][s]*(lim+1);
				}
			}
		}
		res+=(f[0][0]+f[0][1])-(!d?0:g[0][0]+g[0][1]);
	}
	return res;
}
void solve(){
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
	cin>>L>>R;
	int n=strlen(L),m=strlen(R);
	reverse(L,L+n);reverse(R,R+m);
	int l=0,r=0;
	for(int i=LGN-1;~i;i--) if(L[i]) l=(l<<4)+(L[i]<='9'?L[i]-'0':L[i]-'a'+10);
	for(int i=LGN-1;~i;i--) if(R[i]) r=(r<<4)+(R[i]<='9'?R[i]-'0':R[i]-'a'+10);
	int tot=calc(r)-calc(l-1);
	return cout<<tot<<'\n',void();
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	for(int p=0;p<4;p++) for(int i=1;i<LGN;i++) v[i][p]=v[i-1][p]+(i>>p&1);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```


---

## 作者：chenxia25 (赞：0)

挺自然的一个题吧。

设满足条件的数为 khx 数。

首先差分转化。变成若干个求小于某个数的 khx 数的数量。

然后枚举第一位不同的，以及这一位是多少，变成 $\mathrm O\left(16^2q\right)$ 个「固定前缀 $pre$，后缀 $suf$ 个位置随便取，得到的 khx 数的数量」问题。

khx 数其实就是找到该数最大的 digit $d$，满足该数的二进制第 $d$ 位为 $1$。那就枚举 $d$ 呗。分两种情况：

1. $d$ 在 $pre$ 里。那么「二进制该位为 $1$」已经可以判断。接下来要做的是计算剩下 $suf$ 位的取值方案数，使得与 $pre$ 一并的最大 digit 为 $d$。如果 $pre$ 里有 $>d$ 那直接 skip；否则如果有等于 $d$，那只要满足后面全部不超过 $d$；否则不仅全部不超过 $d$，还要有一个等于 $d$。

   记录 $f_{t,x}$ 表示 $x$ 个 16 进制位，mask 为 $t$ 的方案数。如果求出了这个数组，预处理个前缀和显然可以 $\mathrm O(1)$ 回答上述内容。

2. $d$ 在 $suf$ 里。那么关于最大 digit 为 $d$，跟上面一样。此外还要满足第 `d >> 2` 位的二进制四位中第 `d & 3` 位必须为 $1$。容易发现，`d >> 2` 不管是多少都本质相同，所以我们只给 $f$ 加一维表示 `d & 3`。现在 $f_{t,x,i}$ 表示 `d & 3` 等于 $i$，如果无限制则 $i=4$。

如果求出了 $f$，则复杂度 $\mathrm O\!\left(16^3q\right)$。现在考虑怎么求 $f$。$x\leq 1$ 随便搞吧，否则用刷表法决策某个无限制的位，容易发现此时 $i$ 是多少不影响转移的过程。状态数 $\mathrm O\!\left(5\times 16\times 2^{16}\right)$，转移 $\mathrm O(16)$，复杂度 $\mathrm O\!\left(5\times16^2\times 2^{16}\right)$。

讲个笑话，一开始急忙跟 tzc 抢一血，读错题了，以为 digit 不去重。那其实几乎一样，只不过 $f$ 数组的 $t$ 的值域变成了 $16\times 2^{15}$，复杂度就变成了 $\mathrm O\!\left(5\times 16^3\times 2^{15}\right)$。读错题，你该反思！

```cpp
int toint(char c) { return isdigit(c) ? c ^ 48 : c - 'a' + 10; }
char tochar(int x) { return x < 10 ? x ^ 48 : 'a' + (x - 10); }

int f[1 << 16 | 10][16][5];
void solve() {
    f[0][0][4] = 1;
    REP(v, 0, 15) REP(d, 0, 4) {
        if(d == 4 || v >> d & 1) ++f[1 << v][1][d];
    }
    REP(x, 1, 14) REP(d, 0, 4) REP(t, 0, (1 << 16) - 1) if(f[t][x][d]) {
        REP(v, 0, 15) f[t | 1 << v][x + 1][d] += f[t][x][d];
    }
    REP(t, 1, (1 << 16) - 1) REP(x, 0, 15) REP(d, 0, 4) f[t][x][d] += f[t - 1][x][d];
}

void mian() {
    solve();
    auto ask = [&](string pre, int suf) {
        auto F = [&](int x, int y, int z) {
            // cout << x << " " << y << " " << z << "!!!\n";
            if(x < 0) return 0ll;
            else return f[x][y][z];
        };
        int ans = 0, alr = 0;
        for(char c : pre) alr |= 1 << toint(c);
        REP(d, 0, 15) {
            int bit = d >> 2, mod = d & 3, cnt = 0;
            if(alr >= (1 << d + 1)) continue;
            if(bit >= suf) {
                int shd = SZ(pre) - (bit - suf + 1);
                if(shd >= 0 && toint(pre[shd]) >> mod & 1) {
                    cnt += F((1 << d + 1) - 1, suf, 4);
                    if(~alr >> d & 1) cnt -= F((1 << d) - 1, suf, 4);
                }
            } else {
                cnt += F((1 << d + 1) - 1, suf, mod);
                if(~alr >> d & 1) cnt -= F((1 << d) - 1, suf, mod);
            }
            ans += cnt;
        }
        return ans;
    };
    auto deal = [&](string s) {
        int ans = 0;
        REP(i, 0, SZ(s) - 1) {
            int x = toint(s[i]);
            REP(y, 0, x - 1) {
                ans += ask(s.substr(0, i) + tochar(y), SZ(s) - 1 - i);
            }
        }
        return ans;
    };
    auto ok = [&](string s) {
        int S = 0, sum = 0, now = 1;
        reverse(ALL(s));
        for(char c : s) {
            S += now * toint(c);
            sum |= 1 << toint(c);
            now *= 16;
        }
        return (S ^ sum) < S;
    };
    // int ans = 0;
    // REP(a, 0, 1) REP(b, 0, 15) REP(c, 0, 15) {
    //     string s = string() + tochar(a) + tochar(b) + tochar(c);
    //     if(ans != deal(s)) cout << s << " is bad\n";
    //     if(ok(s)) ++ans;
    // }
    int qu = read();
    while(qu--) {
        string s, t; cin >> s >> t;
        int ans = 0;
        ans += deal(t);
        ans -= deal(s);
        ans += ok(t);
        prt(ans), pc('\n');
    }
}
```

---

