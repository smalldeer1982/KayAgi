# Knapsack

## 题目描述

你有一个容量为$W$的背包，和$8$种物品，重量分别为$1$~$8$的整数，分别有$cnt_1,cnt_2...cnt_8$个。  
求背包中最多能装上多大的重量。

## 说明/提示

$0\le W \le10^{18}$  
$0 \le cnt_i \le 10^{16}$

## 样例 #1

### 输入

```
10
1 2 3 4 5 6 7 8
```

### 输出

```
10
```

## 样例 #2

### 输入

```
0
0 0 0 0 0 0 0 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
0 4 1 0 0 9 8 3
```

### 输出

```
3
```

# 题解

## 作者：Acfboy (赞：13)

这题明明是个很妙的背包，为什么没有个正常点的做法啊……

题目要求的是物品个数很多，背包容量很大但每件物品重量很小，且物品种类也很少时的背包问题。

因为背包的容量实在是太大了，所以不能直接做，我们考虑将物品都尽量打包成一些组，以便组内能够快速地取到最优，同时得满足组外的物品少一点，这样就可以直接对它们做 dp 了。

可以发现，一个组的大小是所有物品的重量的最小公倍数（$840$）的时候非常合适。因为是最小公倍数，所以这一个组一定可以去满，几个组拼接起来是无缝的，那么取这些组拼满整个大背包就有贪心的最优策略：尽可能多取。  
而对于剩下的，每一种物品剩余个数都不可能超过组的大小，即剩下的每种最多 $840$ 个，加起来不超过 $840\times 8$, 直接做 dp 就可以了。

令 $f_{i, j}$ 表示前 $i$ 种物品剩余的总价值为 $j$ 的时候能拼成的最多组数。那么枚举每一个剩下 $k$ 件，设当前的物品拼成 $840$ 的价值需要的个数是 $d$, 可以得到转移方程 $f_{i, j} = \max\{f_{i-1, j-i\times k} + \frac{cnt_{i-1}-k}{d} \}$。

最后统计答案的时候枚举一个 $j$ 在加上这最大的个数乘上 $840$ 即可。

代码（注意其中的 dp 转移方式和说明里的略有不同）。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
const int N = 10, L = 900;
int f[N][L*N], w, cnt[N];
signed main() {
	scanf("%lld", &w);
	for (int i = 1; i <= 8; i++)
		scanf("%lld", &cnt[i]);
	memset(f, -1, sizeof f);
	f[1][0] = 0;
	for (int i = 1; i <= 8; i++) 
		for (int j = 0; j <= 840*8; j++) {
			if (f[i][j] == -1) continue;
			int r = 840 / i;
			if (cnt[i] < r) r = cnt[i];
			for (int k = 0; k <= r; k++) 
				f[i+1][j+k*i] = std::max(f[i+1][j+k*i],
						        f[i][j] + (cnt[i]-k) / (840 / i));
		}
	int ans = 0;
	for (int j = 0; j <= 840*8; j++) {
		if (j > w || f[9][j] == -1) continue;
		ans = std::max(ans, j + 840*(std::min(f[9][j], (w-j)/840)));
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：cjZYZtcl (赞：9)

## 来一发乱搞题解（

首先当物品总重小于背包容量可以全部放进去。

然后不难发现对于一个容量极大的背包首先可以乱放，当剩下的容量小到一定程度之后再考虑用背包算法去放物品。

那么我们考虑当一些物品剩余数量很多并且背包容量还很大的时候，先从这些物品中随机选择一种，然后随机地放入一部分该物品。

这样的操作只要你每次放入背包的部分足够小（代码中取的是 $\dfrac{1}{7}$），正确性是很高的。

当背包容量小到一定值（代码中取了 `3000`）之后直接跑背包即可。

### AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define UP(i, l, r) for(int i = l; i <= r; i++)
#define DOWN(i, r, l) for(int i = r; i >= l; i--)
#define pr pair<int, int>
#define mp make_pair
const int V = 3e3 + 5;//这是做背包的下限，当背包容量小于这个值就做背包
int M, n = 8, m, sum = 0;
int s[10];
bitset<V << 1> f;
inline int read(){
	int x = 0, mm = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') mm = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * mm;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
void init(){
	M = m = read();
	UP(i, 1, n){
		s[i] = read();
		sum += s[i] * i;
	}
}
void work(){
	if(sum <= m){
		write(sum);
		putchar('\n');
		return;
	}
	while(m > V){
		int z = rand() % n + 1;
		if(s[z] < sqrt(V)) continue;//当当前物品的数量过少就跳过
		int x = min((m - V) / z + 1, s[z]);
		int y = rand() % (x - x / 7 + 1) + (x / 7);//否则随机放入一部分，但至少放入1/7
		m -= y * z;
		s[z] -= y;
	}
	f.reset();
	f[0] = 1;
	UP(i, 1, n){//当背包容量小于V就直接bitset优化的背包跑一遍即可
		UP(j, 1, min(s[i], m / i)){
			f |= (f << i);
		}
	}
	DOWN(i, m, 0){
		if(f[i]){
			write(M - (m - i));
			putchar('\n');
			return;
		}
	}
}
signed main(){
	srand(time(NULL));
	srand(rand());
	srand(rand());
	init();
	work();
}
```

---

## 作者：NaCly_Fish (赞：5)

一种比较清新的做法qwq  

由于背包很大，物品很多，所以一开始可以先取走一部分。  
肯定不能全部取走，背包要剩下一些空间，具体是多少我并没有算，但是剩$850$可过。   
注意这里要加个特判：如果取走全部物品仍然不超过背包容量，直接输出答案。

这时背包容量就很小了，随便用背包dp一下就行了。。  
这里我比较懒，把每个物品倍增地拆开，然后跑01背包。

献上丑陋的代码：  
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define int long long
#define reg register
#define N 3003
using namespace std;

int w,tw,ans,t,n,cur,sum;
int cnt[9],v[N],f[N];

inline void read(int &x);
void print(int x);
inline int max(int x,int y);
inline int min(int x,int y);

signed main(){
    read(w);
    tw = max(0,w-850);
    for(int i=1;i<=8;++i){
        read(cnt[i]);
        sum += cnt[i]*i;
    }
    if(sum<=w){
        print(sum);
        return 0;
    }
    w -= tw;
    for(int i=1;i<=8;++i){
        t = min(cnt[i],tw/i);
        if(cnt[i]-t<10) t = max(0,cnt[i]-10);
        ans += t*i;
        tw -= t*i;
        cnt[i] -= t;
    }
    w += tw;
    for(reg int i=1;i<=8;++i){
        t = 1;
        for(reg int j=0;cnt[i]>0;++j){
            cur = min(t,cnt[i]);
            cnt[i] -= cur;
            v[++n] = cur*i;
            t <<= 1;
        }
    }
    for(reg int i=1;i<=n;++i)
        for(reg int j=w;j>=v[i];--j)
            f[j] = max(f[j],f[j-v[i]]+v[i]);
    print(ans+f[w]);
    return 0;
}

inline int max(int x,int y){
    return x>y?x:y;
}

inline int min(int x,int y){
    return x<y?x:y;
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
```

---

## 作者：xukuan (赞：5)

题目大意（不能作为正式的翻译，请注意！）

第一行输入w，第二行输入cnt[1],cnt[2],...,cnt[8],在保证1\*cnt[1]+2\*cnt[2]+...+8\*cnt[8]<=w时，求原式的最大值

算法：搜索剪枝

一开时直接穷举，i从0到cnt[x]，TLE#6：

CF评测id：50922218
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll w,Max,a[10];

void dfs(ll m,ll sum){
    if(m==9){
        Max=max(Max,sum);
        return;
    }
    for(ll i=0; i<=a[m]&&sum+m*i<=w;/*确保进入下一层搜索时总和不大于w*/ i++) dfs(m+1,sum+m*i);
}

int main(){
    cin>>w;
    for(ll i=1; i<=8; i++) scanf("%I64d",&a[i]);
    dfs(1,0);
    cout<<Max<<endl;
    return 0;
}
```

后来想到了一个至关重要的地方（有参考https://www.cnblogs.com/zwfymqz/p/10481631.html）：

穷举时从大到小，最多向下穷举9次！

证明：当超过9次时，可以通过别的数字补回来，重复搜索，砍掉

LG提交id：16972610

CF评测id：50922948
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll w,Max,a[10];

void dfs(ll m,ll sum){
    if(m==9){
        Max=max(Max,sum);
        return;
    }
    for(ll k=9,i=min((w-sum)/m,a[m]); k; k--,i--)
        dfs(m+1,sum+max((ll)0,i*m));
}

int main(){
    cin>>w;
    for(ll i=1; i<=8; i++) scanf("%lld",&a[i]);
    dfs(1,0);
    cout<<Max<<endl;
    return 0;
}
```


---

## 作者：zhangxiao666 (赞：1)

## 题意：
传统的背包，物品极小背包容量极大。

## 思路：

考虑正常背包用搜索怎么打的，大概是枚举区与不取（多件物品枚举取多少），但这样是 $O(2^n)$ 的。

但由于这题物品种类只有 $8$ 件，考虑剪枝，假设每件物品最多取 $x$，那么最少要取到到 $x\sim 9$（向下穷举 $9$ 次后所空出的空间中一定有与 $1\sim 8$ 的公倍数，会重复搜索），这样复杂度就很小了。

~~（其实还是爆搜乱搞）~~


## 代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10;
ll W, ans = 0;
array<ll, N> cnt;

ll read()
{
    int f = 1; ll s = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {s = s * 10 + ch - '0'; ch = getchar();}
    return f * s;
}

void Dfs(int now, ll sum)
{
    if (now > 8) 
    {
        ans = max(ans, sum);
        return;
    }
    ll cntnow = min(cnt[now], (W - sum) / now);
    for (int i = 0; i < 10; i++)
    {
        Dfs(now + 1, sum + max(0ll, now * (cntnow - i)));
    }
}

void work()
{
    W = read(); 
    for (int i = 1; i <= 8; i++) cnt[i] = read();
    Dfs(1, 0);
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1, opinput = 0;
    if (opinput) cin >> T;
    while (T--) work();
    return 0;
}
```

---

## 作者：revolutionary_oier (赞：1)


# 题目传送门
[传送门](https://www.luogu.com.cn/problem/CF1132E)

# 题目剖析

## 条件分析
初看一眼感觉是一道**多重背包**，但仔细观察，背包容量你就会开心地否认自己的思路，$0 \leq W \leq 10^{18}$，背包根本开不下；

所以要转换思路。

## 思维迸射
经过他人的提醒，因为背包容量只分 $x∈Z. x∈[1,8]$，不妨我们可以学习秦始皇——统一度量衡。

$\because \operatorname{lcm}([1,8])=840$

$\therefore$ 只需要将每种物品的重量均统一为 $840$，打包为一组，先从重量大的开始取 $840$ 打包组。

从这里开始将会分为 $2$ 种情况：

- 取尽 $840$，还剩一些；

我们只需要对剩余的物品搞一遍 01 背包加上 $840$ 打包组取得情况得到最终得结果（因为最后剩余的物品数绝对没有超过 $\sum_{i=1}^{8}\frac{840}{i}$，背包容量受到限制，可以进行 01 背包）。

- 未取尽 $840$，但无法再填充 $840$；

将剩余未取尽的 $840$ ,补齐到对应第 $i$ 种物品，剩余数量为 $\frac{840}{i}$ 进行 01 背包即可，可行性同上所述。

# 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int maxn=20+10;
const int maxm=1e4+10;
const int maxk=1e3+10;
int w,s,cnt,tot;
int a[maxn],b[maxn],v[maxm],f[maxk];
signed main(){
	scanf("%lld",&w);
	s=w/840;
   //打包
	for(int i=1;i<=8;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i]/(840/i);
		a[i]=a[i]%(840/i);
		if(s>=b[i]){
			s-=b[i];
			b[i]=0;
		}
		else {
			b[i]-=s;
			s=0;
		}
	}
   //处理剩余840
	for(int i=1;i<=8;i++){
		if(b[i]>0)a[i]=840/i;
		tot=tot+i*a[i];
		for(int j=1;j<=a[i];j++)v[++cnt]=i;
	}
	int p=w%840;
   //01背包
	if(s==0){
		for(int i=1;i<=cnt;i++){
			for(int j=p;j>=v[i];j--)f[j]=max(f[j],f[j-v[i]]+v[i]);
		}
		printf("%lld\n",w-(p-f[p]));
	}
	else {
		p=p+s*840;
		if(p>=tot)printf("%lld\n",w-(p-tot));
		else {
			for(int i=1;i<=cnt;i++){
				for(int j=p;j>=v[i];j--)f[j]=max(f[j],f[j-v[i]]+v[i]);
			}
			printf("%lld\n",w-(p-f[p]));
		}
	}
	return 0;
} 
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16063694.html)

# 题目大意

你有一个容量为 $n$ 的背包，和 $8$ 种物品，体积分别为 $1\sim 8$ 的整数，分别有 $a_1,a_2,\cdots,a_8$ 个。

求背包中最多能利用的体积。

$0\le n\le 10^{18},0\le a_i\le 10^{16}$。

# 题目分析

注意到背包容量 $n$ 很大，但是物品数量很小且物品体积很小。所以可以考虑将一些物品分成一组考虑，这里可以取 $\operatorname{lcm}(1,2,\cdots,8)=840$。我们尽量多地分组，剩下的部分，每一种物品的数量小于 $840$（否则可以再分一组），总共不超过 $840\times 4$。

令 $dp_{i,j}$ 表示考虑前 $i$ 种物品，剩余总体积为 $j$ 时能拼出的最大组数。

状态转移方程为：$dp_{i,j}=\max\{dp_{i-1,j-i\times k}+\dfrac{a_{i-1}-k}{\frac{840}{i}}\}$。

# 代码

```cpp
//2022/3/27
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define int long long
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;
const int N1 = 15,N2 = 855;
int a[N1],dp[N1][N1 * N2];
//dp[i][j]:前 i 种物品剩余的总价值为 j 的时候能拼成的最多组数
int n,ans;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	n = read();
	for (register int i = 1;i <= 8; ++ i) a[i] = read();
	mst(dp,-0x3f);
	dp[1][0] = 0;
	for (register int i = 1;i <= 8; ++ i) {
		for (register int j = 0;j <= 840 * 8; ++ j) {
			if (dp[i][j] != INF) {
				for (register int k = 0;k <= min(840 / i,a[i]); ++ k) {
					dp[i + 1][j + k * i] = max(dp[i + 1][j + k * i],dp[i][j] + (a[i] - k) / (840 / i));
				}
			}
		}
	}
	int ans = 0;
	for (register int i = 0;i <= 840 * 8; ++ i) {
		if (i <= n) ans = max(ans,i + 840 * (min(dp[9][i],(n - i) / 840)));
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：mulberror (赞：1)

~~首杀：提供一波非正常解法~~  
丢一波自己博客的链接：[传送门](http://chhokmah.top/2019/03/11/codeforces1132E%20Knapsack/)
# 题目描述
你有一个容量为$w$的背包，和$8$件物品，重量分别为$1~8$的整数，分别有$cnt_1 ... cnt_8$，求最大容量。

---
# 解法
笨蛋chh一开始打了一个背包模板乱搞压缩容量$j$状态，结果搞爆炸了。  
但是无意之间把对拍暴力交上去之后，$a$掉了。
冷静分析题目，数据范围容量$w$非常的大，那么我们就从数据规模小的$8$入手。  
每次枚举有当前物品放几个，然后暴力乱搞就过掉了。  
~~事实证明：暴力出奇迹~~  

----
# 瞎讲
我们其实做过$01$背包的容量压缩版，但是笨蛋$chh$就是调不对$QwQ$（蒟蒻太菜了），好像在洛谷比赛某一次出现过。

---
# ac代码
$邪教宣传一波：没有快读的代码是没有灵魂的$
```cpp
#include <bits/stdc++.h>
#define ms(a, b) memset(a, b, sizeof(a))
#define LL long long
using namespace std;
inline LL gll() {
    LL w = 0, x = 0;
    char ch = 0;
    while (!isdigit(ch)) w |= ch == '-', ch = getchar();
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return w ? -x : x;
}
LL ans=0, w, a[15]
inline void dfs(int x, LL sum) {
    if (x == 9) {
        ans = max(ans, sum);
        return;
    }
    LL v = min((w - sum) / x, a[x]);
    for (int i = 1; i <= 9; i ++) //枚举当前物品放几件
        dfs(x + 1, sum + max((LL)0, (v--) * x));
}
int main() {
    w = gll();
    for (int i = 1; i <= 8; i ++) a[i] = gll();
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}

```

---

