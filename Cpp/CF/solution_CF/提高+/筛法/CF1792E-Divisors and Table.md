# Divisors and Table

## 题目描述

给定一张 $n \times n$ 的表格和一个正整数 $m = m_1 \times m_2$，表格第 $i$ 行第 $j$ 列的数 $a_{i, j} = i \times j$。

现在需要你求出 $m$ 的每个因子 $d$ 是否在表格中出现，若出现，则求出其出现在表格中的最小行号。

## 样例 #1

### 输入

```
3
3 72 1
10 10 15
6 1 210```

### 输出

```
6 2
10 0
8 5```

# 题解

## 作者：信息向阳花木 (赞：7)

这个方法可能比较好理解一些，但就是运行时间有点长（

我们先通过分解 $m1$，$m2$ 的因数来求出 $m$ 的所有因数。

对于 $m$ 的第 $i$ 个因数 $c_i$，$c_i$ 所在的行号一定是 $c_i$ 的因数。所以我们可以二分找到最小的 $k$，使得 $\lceil \frac{c_i}{c_k} \rceil ≤ n$，然后从 $k$ 开始枚举 $j$（$k≤j≤n$），直到 $\left. c_j \middle| c_i\right.$ 为止，那么 $c_i$ 所对应的最小行号就是 $c_j$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define int long long

int t, n, m1, m2;
vector<int> a, b, c;

signed main()
{
	scanf("%lld", &t);
	while (t -- )
	{
		int cnt = 0, ans = 0;
		a.clear();
		b.clear();
		c.clear();
		
		scanf("%lld%lld%lld", &n, &m1, &m2);
		for (int i = 1; i <= m1 / i; i ++ )
		{
			if(m1 % i == 0)
			{
				a.push_back(i);
				if(m1 / i != i) a.push_back(m1 / i); 
			}
		}
		for (int i = 1; i <= m2 / i; i ++ )
		{
			if(m2 % i == 0)
			{
				b.push_back(i);
				if(m2 / i != i) b.push_back(m2 / i);
			}
		}
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		
		for (int i = 0; i < a.size(); i ++ )
			for (int j = 0; j < b.size(); j ++ )
				c.push_back(a[i] * b[j]);
				
		sort(c.begin(), c.end());
		c.erase(unique(c.begin(), c.end()), c.end());
		
		for (int i = 0; i < c.size(); i ++ )
		{
			int l = 0, r = i;
			while (l <= r)
			{
				int mid = l + r >> 1;
				if ((c[i] + c[mid] - 1) / c[mid] <= n) r = mid - 1;
				else l = mid + 1;
			}
			for (int j = l; j < c.size(); j ++ )
			{
				if(c[j] > n) break;
				if(c[i] % c[j] == 0)
				{
					ans ^= c[j];
					cnt ++;
					break;
				}
			}
		}
		printf("%lld %lld\n", cnt, ans);
	}
}
```

---

## 作者：Leasier (赞：6)

首先可以对 $m_1 m_2$ 分解质因数，进而抓出其所有因数。

接下来直接考虑 $\min$ 比较麻烦，我赛时的思路是用可持久化可并堆维护一个数在这张表上的所有出现位置的列，从小到大处理，每次在合并完成后弹出所有已经不满足条件的那些过小的数——显然它们对于更大的数也不合法，判断时看看堆顶是否 $\leq n$ 即可。

但这样的时间复杂度是伪的……沿着直接求 $\min$ 这条路已经很难走下去了。

考虑反过来，尝试求出最大的行，进而可以得知最小的列。

考虑 dp。设 $dp_x$ 表示 $x$ 的因数中最大且不大于 $n$ 者。

初值：$dp_x = [x \leq n] x$。

转移：$dp_x \leftarrow \max(dp_x, dp_{\frac{x}{p}})$，其中 $p$ 为 $x$ 的一个质因数。

答案：$\displaystyle\sum_{x \mid m_1 m_2} [dp_x \neq 0 \operatorname{and} \frac{x}{dp_x} \leq n]$ 和 $\operatorname{xor}_{x \mid m_1 m_2} [dp_x \neq 0 \operatorname{and} \frac{x}{dp_x} \leq n] \frac{x}{dp_x}$。

时间复杂度为 $O(t(\sqrt{m_1} + \sqrt{m_2} + \tau(m_1 m_2) \omega(m_1 m_2) \log \tau(m_1 m_2)))$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

int prime[17], power[17];
ll bucket[103687], dp[103687];
map<int, int> mp;

inline void decompound(int n){
	for (int i = 2; i * i <= n; i++){
		while (n % i == 0){
			n /= i;
			mp[i]++;
		}
	}
	if (n > 1) mp[n]++;
}

void dfs(int cur, ll val, int cnt1, int &cnt2){
	if (cur > cnt1){
		bucket[++cnt2] = val;
		return;
	}
	for (int i = 0; i <= power[cur]; i++){
		dfs(cur + 1, val, cnt1, cnt2);
		val *= prime[cur];
	}
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, m1, m2, cnt1 = 0, cnt2 = 0, ansa = 0;
		ll ansb = 0;
		cin >> n >> m1 >> m2;
		mp.clear();
		decompound(m1);
		decompound(m2);
		for (map<int, int>::iterator j = mp.begin(); j != mp.end(); j++){
			cnt1++;
			prime[cnt1] = j->first;
			power[cnt1] = j->second;
		}
		dfs(1, 1, cnt1, cnt2);
		sort(bucket + 1, bucket + cnt2 + 1);
		for (int j = 1; j <= cnt2; j++){
			ll t;
			if (bucket[j] <= n){
				dp[j] = bucket[j];
			} else {
				dp[j] = 0;
			}
			for (int k = 1; k <= cnt1; k++){
				if (bucket[j] % prime[k] == 0) dp[j] = max(dp[j], dp[lower_bound(bucket + 1, bucket + cnt2 + 1, bucket[j] / prime[k]) - bucket]);
			}
			t = bucket[j] / dp[j];
			if (dp[j] != 0 && t <= n){
				ansa++;
				ansb ^= t;
			}
		}
		cout << ansa << " " << ansb << endl;
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：2)

实际上我们可以用 Pollard-rho 直接暴力分解出 $ m $ 的因数，而不需要分别分解两个因子之后再合并。

然后我们得到质因子分解后 dfs 枚举每个质因子的出现次数，不难发现这样做由唯一分解定理所以每个因子只会被枚举一次。

得到所有因子后发现行号必须要是其约数，可以二分出最小的令其在表格范围内的数，然后从这个数往上暴力跳得到能整除这个因子的最小约数即可。

时间复杂度不会算，但是跑不满可以过。实现部分参照了第一篇题解。

注意计算过程中可能会出现的溢出问题。

代码：（模板过长贴云剪贴板）

[模板](https://www.luogu.com.cn/paste/cpc2see7)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
/*模板*/
vector<pair<int,int> >p;
vector<uint64_t>tmp,c;
int ksm(int a,int b) 
{
	int res=1;
	while(b) 
    {
		if(b&1)
		res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
void dfs1(int step,int now) 
{
	if(step==p.size()) 
    {
		tmp.push_back(now);
		return;
	}
	for (int i=0;i<=p[step].second;i++)
	dfs1(step+1,now*ksm(p[step].first,i));
}
main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		uint64_t n,a,b,res;
		cin>>n>>a>>b;
		res=a*b;
		auto map1=OY::Pollard_Rho::decomposite(res);
		p.clear();
		for (auto x:map1) 
        {
			pair<int,int> a= {x.prime,x.count};
			p.push_back(a);
		}
		tmp.clear();
		dfs1(0,1);
		int cnt=0,ans=0;
		c=tmp;
		sort(c.begin(),c.end());
		for (int i = 0; i < c.size(); i ++ ) 
        {
			int l = 0, r = i;
			while (l <= r) 
            {
				int mid = l + r >> 1;
				if ((c[i] + c[mid] - 1) / c[mid] <= n) 
				        r = mid - 1; 
                        else 
				        l = mid + 1;
			}
			for (int j = l; j < c.size(); j ++ ) 
            {
				if(c[j] > n) 
				        break;
				if(c[i] % c[j] == 0) 
                {
					ans ^= c[j];
					cnt ++;
					break;
				}
			}
		}
		cout<<cnt<<' '<<ans<<'\n';
	}
}
```


---

## 作者：Hoks (赞：1)

## 前言
求证明复杂度。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
肯定要先求 $m1\cdot m2$ 的所有因子。

直接求会爆，所以我们分开求出所有因子然后合并。

有关这个因子的数量我们可以查表：
![](https://cdn.luogu.com.cn/upload/image_hosting/vu8s20ty.png)
其中 $\max d(n)$ 这一行就是在这个数据范围下的最多因子个数。

发现 $10^9$ 内最多 $1344$ 个因子，所以数组开 $2\times10^6$ 就够用了。

然后考虑怎么求最小出现行数。

假设我们已经求完了所有因子扔在了 $c$ 里，$c_i$ 表示第 $i$ 个因子。

那么我们不难发现，$c_i$ 的所有因子肯定会在 $c_j,j\in[1,i]$ 出现。

这点证明也很容易，$c_i$ 都已经是因子了，因子的因子肯定是因子。

那么我们现在要求的就是：
$$\min(c_j),(c_i=x\cdot c_j,j\in[1,i],x\in[1,n],c_j\in[1,n])$$
前面是要求的，后面的是判断条件。

这样我们不难想到，先把最前面一段 $\frac{c_i}{c_j}>n$ 的部分先跳掉。

这样就搞出来了一种很优秀的暴力，直接提交发现可过。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e6+10,V=1e6,M=35,INF=1e9+10,mod=1e9+7;
int n,m1,m2,tot,cnt,cur,a[N],b[N],c[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void solve()
{
	n=read(),m1=read(),m2=read();tot=cnt=cur=0;
	for(int i=1;i*i<=m1;i++) if(m1%i==0) a[++tot]=i,a[++tot]=m1/i;
	for(int i=1;i*i<=m2;i++) if(m2%i==0) b[++cnt]=i,b[++cnt]=m2/i;
	for(int i=1;i<=tot;i++) for(int j=1;j<=cnt;j++) c[++cur]=a[i]*b[j];
	sort(c+1,c+1+cur);cur=unique(c+1,c+1+cur)-c-1;tot=cnt=0;
	for(int i=1;i<=cur;i++)
	{
		int l=1,r=i,res=1;
		while(l<=r)
			if((c[i]+c[mid]-1)/c[mid]<=n) res=mid,r=mid-1;
			else l=mid+1;
		for(int j=res;j<=i&&c[j]<=n;j++)
			if(c[i]%c[j]==0){tot++;cnt^=c[j];break;}
	}print(tot),put(' '),print(cnt);put('\n');
}
signed main()
{
	int T=1;
	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：2018ljw (赞：1)

首先分解出 $m$ 的质因子。我们相当于要对每个 $d$ 求满足 $x\mid d$，$\frac dx\le n$ 最小的 $x$。

以下用 $d(x)$ 表示 $x$ 的因数个数。

最小化 $x$ 时会受到 $\frac dx$ 的限制，因此不妨最大化 $\frac dx$，然后看 $x$ 合不合法。$x$ 只要不合法那么更小的 $\frac dx$ 也一定会不合法。这种做法题解区已经有了故不赘述，我们来些~~靠谱的~~乱搞。

关注到有用的 $x$ 一定是 $m$ 中 $\le n$ 的因数，大约是 $5\times 10^4$ 级别，考虑在这上搞些操作。从小到大枚举 $x$，我们可以得到以 $x$ 为最小质因子时，$d$ 的一个可行区间 $[l,r]$。

$r$ 好求，对于 $l$，我们需要保证 $d$ 超出 $x$ 的任意真因子的合法范围。从 $x$ 中扣掉最小质因子算上界即可。因此维护一个 `set`，每次删去合法的 $d$ 并统计贡献，完事。

接下来是粗略估计复杂度。

假设 $k$ 为 $x$ 的最小质因子。首先 $d(m)=\prod c_i+1$，而 $\lfloor\log_{3}10^{18}\rfloor=37,\lfloor\log_{3}10^9\rfloor=18$。因此 $k\ge 3$ 时，合法的 $x$ 很少。

$n^2<m$ 时会出现较多 $d$ 不合法，因此假定 $m=n^2$。$d$ 的范围为 $(\frac 12nx,nx]$，对应过来即为 $[\frac nx,2\frac nx)$，因此因数个数上界为 $\frac nx$。

$x\ge \sqrt n$ 时因数个数 $\le \sqrt n$，而合法的 $x$ 为 $d(m)$ 级别；$x\le \sqrt n$ 时 $x$ 个数 $\le \sqrt n$，因数个数 $\le d(m)$。

因此一个粗略的上界是 $O(d(m)\sqrt n)$。由于带删、区间枚举、$x$ 个数限制等因素，这个 $d(m)$ 是远跑不满的。[record](https://codeforces.com/contest/1792/submission/211224981)。





---

## 作者：lightup37 (赞：1)

不会证复杂度。CF [1653ms](https://codeforces.com/contest/1792/submission/190984079) 求叉/证。

---

## 题意

给定 $m = m1\times m2$ 和 $n$。定义 $g(x, n)$ 为是否存在一个 $x$ 的因子 $t$ 使得 $t\leq n, \frac{x}{t}\leq n$，$f(x, n)$ 是最小的 $x$ 因子 $t$，使得 $t\leq n, \frac{x}{t}\leq n$。

求 $\sum\limits_{d|m} g(d, n)$ 和 $\oplus_{d|m, g(d, n)= 1} f(d, n)$。

$n, m1, m2\leq 10^9$.

## 解法

$m$ 的因子一定是一个 $m1$ 的因子 $x$ 和一个 $m2$ 的因子 $y$ 的乘积。这不能让我们避免重复计数，因而我们要求 $x$ 是所有满足 $x_0y_0 = m, x_0 | m1, y_0|m2$ 中 $x_0$ 最小的那个 $x_0$。这也就是在说，不存在 $t | y, tx | m1$，也即 $\gcd(y, \frac{m1}{x}) = 1$。称这样的二元组为可爱的。

[oeis](http://oeis.org/A066150) 得到 $m1, m2$ 在 1e9 级别时，可爱的二元组 $(x, y)$ 的级别在 1e5 左右。

要判断一个二元组 $(x, y)$ 是否合法并求出其 $f(xy, n)$，最直观的想法就是枚举 $i|x, j|y$，判断是否有 $ij\leq n, \frac{x}{i}\frac{y}{j}\leq n$，但是这样显然是不行的。我们考虑只枚举 $i$，那么要求就是 $\frac{ni}{xy}\leq j \leq \frac{n}{i}, j|y$。大于号那边有 $y$ 不好处理，但是小于号没有。不妨改为求 $h(xy, n)$ 为**最大的** $xy$ 的因子 $t$，使得 $t\leq n, \frac{xy}{t}\leq n$。那么我们只需要求出最大的 $j|y$ 且 $j\leq \frac{n}{i}$，然后简单的判定是否有 $j\ge \frac{ni}{xy}$ 即可。

枚举所有可爱的二元组 $(x, y)$ 和 $x$ 的因子 $i$，将其抽象为一个询问三元组 $(y, \frac{n}{i}, x)$ 存储下来。然后对于每个 $y$ 依据 $\frac{n}{i}$ 上升依次处理询问。$\frac{n}{i}$ 相同的询问，要求出的 $j$ 是相同的。

爆搜得到，对于一个 $m1$，二元组 $(i, x)$ 满足 $i|x, x|m1$ 的数量，在 $m1\leq 10^9$ 的时候为 136080。

整体复杂度为 $\sum\limits_{y|m2} \sum\limits_{x|m1} [(\frac{m1}{x}, y) = 1] d(x)$，我不会算但是跑的飞快。

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define uf(i,x,y) for(int i=x, i##end=y; i<i##end; ++i)
#define ll long long
#define pir pair<int, int>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back 
char ch;
int rd() {
	int f=1, x=0; ch=getchar();
	while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
	while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
const int _ = 2000, inf = -1;
int fac[2][_], tot[2];
int okf[_][_], okc[_];
int facf[_][_], ffc[_];
int facy[_][_], fyc[_];
int qat[_][_], qc[_];
int ans[_][_];
void upd(int a, int b, int c) {
	ans[a][b] = max(ans[a][b], c);
}
void solve() {
	int aal = 0, s = 0;
	int C = rd(); int m[2]; m[0] = rd(), m[1] = rd(); tot[0] = tot[1] = 0;
	f(t,0,1) {
		for(int i=1; i*i <= m[t]; ++i) {
			if(m[t] % i) continue ;
			fac[t][++tot[t]] = i;
			if(i*i != m[t]) fac[t][++tot[t]] = m[t]/i;
		}
	}
	f(t,0,1) sort(fac[t] + 1, fac[t] + tot[t] + 1);
	f(j,1,tot[1]) {
		int y = fac[1][j]; okc[j] = 0;
		f(i,1,tot[0]) {
			int X = m[0] / fac[0][i];
			if(gcd(X, y) == 1) {
				okf[j][++okc[j]] = i, ans[j][i] = inf;
			}
		}
	}
	f(i,1,tot[0]) {
		ffc[i] = 0;
		f(j,1,i) {
			if(fac[0][i] % fac[0][j] == 0) {
				facf[i][++ffc[i]] = j;
			}
		}
	}
	f(i,1,tot[1]) {
		fyc[i] = 0;
		f(j,1,i) {
			if(fac[1][i] % fac[1][j] == 0) facy[i][++fyc[i]] = j;
		}
	}
	f(j,1,tot[1]) {
		int y = fac[1][j];
		f(i,1,okc[j]) {
			int x = fac[0][okf[j][i]], I = okf[j][i];
			f(k,1,ffc[I]) {
				int t = facf[I][k];
				qat[t][++qc[t]] = I;
			}
		}
		int nowp = 0;
		d(i,1,tot[0]) {
			int nl = C/fac[0][i];
			while(nowp + 1 <= fyc[j] && fac[1][facy[j][nowp + 1]] <= nl) ++nowp;
			if(!nowp) { qc[i] = 0; continue ; }
			f(q,1,qc[i]) {
				int Qxid = qat[i][q], Qx = fac[0][Qxid];
				if(1LL * (Qx/fac[0][i]) * (y/fac[1][facy[j][nowp]]) <= C) upd(j, Qxid, fac[0][i] * fac[1][facy[j][nowp]]);
			}
			qc[i] = 0;
		}
		f(i,1,okc[j]) {
			if(ans[j][okf[j][i]] == inf) continue;
			int rans = 1LL * fac[1][j] * fac[0][okf[j][i]] / ans[j][okf[j][i]];
			aal ^= rans;
			++s;
		}
	}
	cout << s << ' ' << aal << endl;
}
int main() {
	int T=rd(); while(T--) solve();
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

VP 切，感觉很水。为什么能评到 $2400$ 啊。

首先考虑一个很简单的暴力。对于 $m_1$，$m_2$ 分别分解出其的因数 **（不需要伟大的 `Pollard-Rho`）**，然后因数两两相乘再去重即为 $m$ 的所有因数。

然后枚举 $m$ 的每一个因数 $v$。若 $v>n^2$ 则显然无解。否则若 $v$ 存在于 $n\times n$ 的乘法表中，则**必然有其所在的行 $i$ 满足 $i\mid v$。** 因此直接暴力枚举出 $v$ 的所有因子然后挨个判断。然后光荣 TLE。

然后可以发现这个东西可以二分一下，找到第一个可能满足条件的行，然后从这个行开始枚举。然后就能过了，喜提最劣解。upd：并不是

```cpp
/*v是m=m1*m2的所有因数
  已经去重并从小到大排序*/
int cx=0,cnt=0;
for(int i=0;i<v.size();++i)
    if(v[i]<=n*n){
        int l=0,r=i,best=0;
        while(l<=r){
            int mid=l+r>>1;
            if((v[i]+v[mid]-1)/v[mid]>n)
                l=mid+1;
            else
                r=mid-1,best=mid;
        }
        for(int j=best;j<v.size()&&v[j]<=n;++j)
            if(v[i]%v[j]==0){
                ++cnt;
                cx^=v[j];
                break;
            }
    }
```

---

## 作者：Mikefeng (赞：0)

## 做法

首先筛出 $m1,m2$ 的因数，交叉相乘得到 $m$ 的因数。

然后考虑能整除 $m$ 因数的数一定还是 $m$ 因数，因此我们可以枚举 $m$ 的因数进行筛除。

设枚举到当前行是 $x$ ,当前因数是 $y$，当 $x\times n<y$ 时就可以退出循环了。

多次筛除已经被筛除过的数是很浪费时间的，因此用用链表维护还没有被筛除的因数，删除是 $O(1)$ 的。

时间复杂度是 $O(d(k)^2)$ 的，其中 $d(k)$ 指的是 $k$ 的因数个数。

$10^{18}$ 以内的数 $d(k)$ 最多为 103680。但是由于每次从小到大枚举行数时会快速筛掉大量的数，并且大于 $10^9$ 的因数不会被用作除数，因此时间是完全可以通过的。

## 代码


```cpp
using namespace std;
inline ll read(){
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const ll N=1e7+5;
ll t,n,m1,m2,k,num,ans;
vector<ll> v,v1,v2;
inline void get_p(ll x,vector<ll> &v){
	v.clear();
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			v.push_back(i);
			if(i*i!=x) v.push_back(x/i);
		}
	}
}
ll pre[N],nxt[N],val[N];
inline void get_ans(){
	for(ll x:v){
		if(x>k) break;
		for(ll i=nxt[0];i!=n+1;i=nxt[i]){
			if(val[i]%x==0&&val[i]/x<=k){
				num++;ans^=x;
				pre[nxt[i]]=pre[i];
				nxt[pre[i]]=nxt[i];
			}else if(val[i]%x==0) break;
		}
	}
}
int main(){
	t=read();
	while(t--){
		k=read();m1=read();m2=read();
		num=0;ans=0;
		get_p(m1,v1);get_p(m2,v2);
		for(ll x:v1) for(ll y:v2) v.push_back(x*y);
		sort(v.begin(),v.end());
		v.resize(unique(v.begin(),v.end())-v.begin());
		n=v.size();
		nxt[0]=1;
		for(ll i=1;i<=n;i++){
			pre[i]=i-1;nxt[i]=i+1;
			val[i]=v[i-1];
		}
		get_ans();
		printf("%lld %lld\n",num,ans);
		v.clear();
	}
	return 0;
}
```


---

## 作者：yimuhua (赞：0)

首先对 $m_1,m_2$ 分解质因数，然后组合起来暴力搜出 $m$ 的所有因数，因数数量大约是 $O(m^{\frac{1}{3}})$，对于 $m\le 10^8$ 最多为 $105000$ 个。

将 $m$ 的因数按从小到大存在 $d_1,d_2,\dots,d_l$ 中，对于每一个 $d_i$，我们要求一个最小的 $x$ 满足 $x$ 是 $d_i$ 的因数且 $\dfrac{d_i}{x}\le n$。

$\therefore x\ge \left\lceil\dfrac{d_i}{n}\right\rceil$

于是先二分出一个 $d_j$ 满足 $d_j\ge \left\lceil\dfrac{d_i}{n}\right\rceil$ 然后向后遍历直到 $d_j$ 为 $d_i$ 的一个因数或 $d_j>\min(n,d_i)$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<long long> a;
map<long long, long long> mp;
long long t, n, m, m2, cnt, ans;
vector<pair<long long, long long> > v;
void dfs(long long x, long long s) {
    if(x == v.size()) {
        a.push_back(s);
        return;
    }
    auto j = v[x];
    for(long long i = 0; i <= j.second; i++) {
        dfs(x + 1, s);
        if(i != j.second)
            s *= j.first;
    }
    return;
}
void init() {
    v.clear();
    for(long long i = 2; i < 100001; i++)
        if(!(m % i))
            while(!(m % i))
                mp[i]++, m /= i;
    if(m > 1)
        mp[m]++;
    for(long long i = 2; i < 100001; i++)
        if(!(m2 % i))
        while(!(m2 % i))
            mp[i]++, m2 /= i;
    if(m2 > 1)
        mp[m2]++;
    for(auto i : mp)
        v.push_back(i);
    dfs(0, 1);
    return;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> m >> m2, mp.clear(), a.clear(), init(), sort(a.begin(), a.end()), ans = cnt = 0;
        for(long long i : a) {
            auto it = lower_bound(a.begin(), a.end(), (i - 1) / n + 1);
            if(*it <= n) {
                while(it != a.end() && i % *it) {
                    it++;
                    if(it != a.end() && *it > n)
                        break;
                }
                if(it != a.end() && *it <= n)
                    cnt++, ans ^= *it;
            }
        }
        cout << cnt << ' ' << ans << '\n';
    }
    return 0;
}

```

---

