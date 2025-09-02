# [ABC318E] Sandwiches

## 题目描述

**题意简述**

给定一个长度为 $N$ 的序列 $A$。求满足以下条件的三元组 $(i,j,k)$ 的个数。

- $1 \le i < j < k \le N$
- $A_i = A_k$
- $A_i \ne A_j$

## 说明/提示

- $3 \le N \le 3 \times 10^5$
- $1 \le A_i \le N$

**样例一解释**

有 $3$ 个，分别为 $(1,2,1),(2,1,2),(2,3,2)$。

## 样例 #1

### 输入

```
5
1 2 1 3 2```

### 输出

```
3```

## 样例 #2

### 输入

```
7
1 2 3 4 5 6 7```

### 输出

```
0```

## 样例 #3

### 输入

```
13
9 7 11 7 3 8 1 13 11 11 11 6 13```

### 输出

```
20```

# 题解

## 作者：Zi_Gao (赞：7)

## 前言

我去，以为多难呢，搞了个三元环出来，结果根本不用。但是这样优势就是代码好写。

## 正文

### 0x00 分析题目

看到三元组的条件，首先想到可以建图跑一个三元环计数。那么考虑怎么建立图论模型。

由于 $A_i=A_k,A_i\not=A_j,i\lt j\lt k$ 那么则有 $A_j\not=A_k$。这样考虑当 $A_i\not=A_j,i\lt j$ 时建立 $i\rightarrow j$ 的有向边；当 $A_i=A_j,i\lt j$ 时建立 $i\leftarrow j$ 的有向边。这样建立出一个竞赛图即可计数三元环。设点 $u$ 的入度为 $out_u$ 有结论三元环个数为 $\left(\begin{matrix}n\\3\end{matrix}\right)-\sum_{i=1}^{n}\left(\begin{matrix}out_i\\2\end{matrix}\right)$。实际上就是容斥一下，用最多的个数减去不合法的个数。

### 0x01 代码实现

正反扫两次数组，开个桶记录一下数字出现个数，计算好入度即可。

AC CODE

```cpp
#include<bits/stdc++.h>
#define int long long
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

long long out[300010];

int a[300010],buc[300010];

signed main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i;
    register long long res=0;
    int n=read();
    for(i=1;i<=n;++i) a[i]=read();

    for(i=1;i<=n;++i)
        out[i]+=(buc[a[i]]++);

    for(i=1;i<=n;++i) buc[i]=0;

    for(i=n;i;--i)
        out[i]+=(n-i-(buc[a[i]]++));

    res=n*(n-1)*(n-2)/6;

    for(i=1;i<=n;++i) res-=out[i]*(out[i]-1)/2;

    print(res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

这样的题需要我们善于观察，训练转换问题的能力。

---

## 作者：lrx___ (赞：6)

**题意简述**

有一个长度为 $N$ 数列 $A$，求 $A$ 中满足以下的三元组 $(i,j,k)$ 的个数。

- $1 \le i < j < k \le N$
- $A_i = A_k$
- $A_i \neq A_j$

**思路**

当看到这个题的时候，我想到了[这个题](https://www.luogu.com.cn/problem/CF894A)。原题的思路是答案等于每个 `A` 左边的 `Q` 的数量乘上右边的 `Q` 的数量。在这道题中，`Q` 相当于题目中的 $A_i$，`A` 相当于题目中的 $A_j$。设 $b_{i,j}$ 为每个 $i$ 在序列 $A$ 中的下标，$c_i$ 为序列 $A$ 中 $i$ 的个数，$l$ 为则所有满足条件的 $A_i=x$ 的三元组的数量就是 $\sum\limits_{j=2}^{c_i}(b_{i,j}-b_{i,j-1}-1) \times i \times (c_i-i)$，就是每个不是 $i$ 的区间长度乘上它左边 $i$ 的个数再乘上它右边 $i$ 的个数。

要注意的是，计算时会爆 `int`。

**代码**

```cpp
#include<cstdio>
#include<vector>
using namespace std;
typedef unsigned long long ll;
const int N=3e5+5;
vector<int>a[N];
/* a[i]存的是每个i的下标 */
int main(){
	int n,i,j,l,x;
	ll s=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		a[x].push_back(i);
		/* 记录x的下标 */
	}
	for(i=1;i<=n;i++){
		l=a[i].size();
		for(j=1;j<l;j++){
			s+=(ll)(a[i][j]-a[i][j-1]-1)*j*(l-j);
			/* 解释：a[i][j]-a[i][j-1]-1为每个不是i的区间长度，j是它左边的i的个数，l-j是它右边的i的个数。 
			要注意计算时会爆int，这里要进行转换 */
		}
	}
	printf("%llu\n",s);
	return 0;
}
```

---

## 作者：DerrickLo (赞：3)

我们用 vector 将每个数出现的位置存起来。

然后对于每一种数，设这个数出现了 $k$ 次，相邻的两个数 $i$ 和 $i+1$ 中间的区域的长度设为 $l$，而这对于整体答案的贡献是 $l\times i\times(k-i)$，意思就是左端点和右端点都分别可以取 $i$ 种和 $k-i$ 种。

具体看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[300005],ans;
vector<int> ve[300005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ve[a[i]].emplace_back(i);
	for(int i=1;i<=n;i++)if(ve[i].size()){
		for(int j=1;j<ve[i].size();j++){
			ans+=(ve[i][j]-ve[i][j-1]-1)*j*(ve[i].size()-j);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Shameimaru_Aya (赞：2)

一种不依赖 vector 的更为优雅的做法。拒绝 STL 从你做起！

考虑每个位置 $i$，设 $last$ 是满足 $A_i=A_{last}$ 的上一个位置，然后计算当 $i$ 作为最后一个元素时满足条件的三元组的数量。delightful 地发现它只由两部分组成：

- 由两个 $last$ 及之前的位置和 $i$ 组成满足条件的三元组的数量。

- 由一个 $last$ 之前的位置（满足对应值等于 $A_i$），$last$ 和 $i$ 之间的位置和 $i$ 组成三元组的数量。

对于第一部分，数量等于位置 $last$ 对答案的贡献。可以简单地理解为将三元组的最后一个元素由 $last$ 变成 $i$。于是开始了递推。

对于第二部分，数量等于 $(last-i-1) \times cnt_{A_i}$。$cnt$ 记录 $A_i$ 此前出现的次数。

最终统计所有位置的贡献即为答案。这样子。

```cpp
#include<iostream>
using namespace std;
#define ll long long
const int maxn=3e5+50;
ll a[maxn],last[maxn],cnt[maxn],num[maxn],ans=0;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		num[i]=num[last[a[i]]]+(i-last[a[i]]-1)*cnt[a[i]];
		cnt[a[i]]++;
		last[a[i]]=i;
	}
	for(int i=1;i<=n;i++)ans+=num[i];
	cout<<ans;
	return 0;
}

```

---

## 作者：Register_int (赞：2)

先记录下每个位置上数的下一次出现位置，从左往右扫。设当前扫到 $a_i$，下一个相同的为 $a_j$，那么方案数是左边的 $a_i$ 个数乘右边的 $a_i$ 个数再乘上 $j-i-1$。直接维护即可，时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;

int n, a[MAXN], p[MAXN], nxt[MAXN];

ll x[MAXN], y[MAXN], ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), x[a[i]]++;
	nxt[n] = n + 1, p[a[n]] = n;
	for (int i = n - 1; i; i--) nxt[i] = p[a[i]], p[a[i]] = i;
	for (int i = 1; i <= n; i++) {
		if (nxt[i] > n) continue;
		x[a[i]]--, y[a[i]]++;
		ans += x[a[i]] * y[a[i]] * (nxt[i] - i - 1);
	}
	printf("%lld", ans);
}
```

---

## 作者：Light_az (赞：1)

提供一个好玩的思路。

枚举每一种颜色，对于其中一种颜色，我们将其中的点取出来会出现多个线段，下图以 $1$ 为例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/low6tulh.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

我们考虑先选定 $a_i,a_k$，然后选择 $a_j$。

对于其中一组 $a_i,a_k$，它对答案的贡献就是它们之间不相同元素的个数，也就是说某一个不等于 $1$ 的 $a_j$ 对答案的贡献其实就是有多少个线段会经过它，如上图为例子： 对于 $4$ 来说，它对上图 $a_i=a_k=1$ 时的贡献是 $3$，因为它被 $[1,5],[1,7],[1,11]$ 这几个线段所包含，当然对于 $[1,5]$ 范围内剩下的 $2,3$ 对答案的贡献与 $4$ 一样，因为他们都在同一个区间内。

现在问题转化为:求 $n$ 个小线段中，每个小线段分别会被其他线段覆盖多少次，我们先考虑 $n$ 个小线段一共可以组成多少个线段，简单组合数学得出有 $\sum_{i=1}^{n} i$ 个线段，即 $ \frac{(1+n) \times n}{2}$，然后考虑没有覆盖这个小区间的线段有多少，分别是左边的小线段和右边的小线段能够组成的线段数量，最后相减即可算出该小线段会被覆盖多少次，然后再乘上该小线段内不同元素数量即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T;
ll mn=INT_MAX,mx=0,p,opt;
ll a[N],b[N];
vector<ll> id[N];
ll f(ll n){
	return (1+n)*n/2;
}
int main(){
	cin>>n;
	F(i,1,n){
		cin>>a[i];
		id[a[i]].push_back(i);//记录颜色下标位置
	}
	F(i,1,n){
		if(b[a[i]]) continue;//枚举颜色
		b[a[i]]=1;
		for(ll num=1;num<id[a[i]].size();num++){
			ans+=(id[a[i]][num]-id[a[i]][num-1]-1)*(f(id[a[i]].size()-1)-f(num-1)-f(id[a[i]].size()-num-1));
            //区间不同元素个数*该区间会被覆盖多少次
     		//f(n)求n个小线段组成多少大线段                                         
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Scorilon (赞：1)

一开始考虑枚举 $i$ 或 $k$ 来统计，发现需要 $O(n^2)$ 的时间复杂度。

因此考虑枚举 $j$，我们可以用 $l_x$ 表示满足 $i<j,a_i=x$ 的数量，用 $r_x$ 表示满足 $j<k,a_k=x$ 的数量。

那么会发现对于每一个 $j$，它的贡献应为 $\sum_{x=1,x \not = a_j}^n l_xr_x$，注意到 $a_j$ 只有一项，所以考虑容斥，将这一项单独提出来，那么贡献就变成了 $(\sum_{x=1}^n l_xr_x)-l_{a_j}r_{a_j}$，因此我们可以先处理出 $\sum_{x=1}^n l_xr_x$，在每次 $j$ 移动的时候修改贡献即可。预处理时间复杂度 $O(n)$，修改为 $O(1)$，每次统计答案为 $O(1)$，总时间复杂度 $O(n)$，足以通过本题。

```cpp
#include <cstdio>

const int N=3e5+5;

int n;
int a[N];
int l[N],r[N];
long long ans,sum;

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(i==1) l[a[i]]++;//初始化l和r
		else if(i!=2) r[a[i]]++;
	}
	for(int i=1;i<=n;i++) sum+=(1ll*l[i]*r[i]);//预处理
	for(int j=2;j<n;j++) {
		ans+=(sum-1ll*l[a[j]]*r[a[j]]);//统计答案
		++l[a[j]];sum+=r[a[j]];//修改
		--r[a[j+1]];sum-=l[a[j+1]];
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：robertuu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc318_e)

没有 C 和 D 简单。

暴力：$O(n^3)$，显然会 TLE。

由于限制中出现了 $i < k$ 且 $A_i = A_k$，很显然可以想到排序，为了方便计算答案，排序时需要维护 `id`。

扫描排序后数组，每扫描到一个新的数字就记录这个新数字的第一个出现位置，不是新的数字则累加这个位置和这个数字第一个出现的位置之间有几个值不同的数字，记录为 $s[i]$，相当于固定选择第一个位置和这个位置下 $j$ 的取值情况，轻松去掉一重循环。

每一个数字扫描完成后，会发现固定选择第一个数字的对答案的贡献就是这一段的 $s$ 之和。固定选择第二个数字的贡献则是这一段的 $s$ 之和去掉前两个数字位置间隔乘以后面的数字个数，这时是 $num - 1$，$num$ 为这个数值的出现次数（因为 $k$ 取后面每一个值时都少了这些 $j$ 的取值）。每向后拓展一个都进行相同的操作。

复杂度：虽然有两重循环，但是第二重循环只会执行 $n$ 次，所以复杂度仍为 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300002],fst[300002];
long long s[300002];
struct node
{
	int x,id;
} b[300002];
bool cmp(node x,node y)
{
	if(x.x != y.x) return x.x < y.x;
	return x.id < y.id;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
		b[i].x = a[i];
		b[i].id = i;
	}
	sort(b+1,b+1+n,cmp);
	fst[b[1].x] = 1;
	int cnt = 0;
	long long SUM,ans = 0,tmp;
	for(int i = 1;i <= n+1;i++)
	{
		if(i > 1 && b[i].x != b[i-1].x) 
		{
			SUM = 0; tmp = i-fst[b[i-1].x];
			for(int j = fst[b[i-1].x];j < i;j++) SUM += s[j];
			for(int j = fst[b[i-1].x];j < i;j++)
			{
				ans += SUM; tmp--;
				if(j != i-1) SUM -= tmp*(b[j+1].id-b[j].id-1);
			}
			fst[b[i].x] = i;
			cnt = 0;
		}
		cnt++;
		s[i] = (b[i].id-b[fst[b[i].x]].id+1) - cnt;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Failure_Terminator (赞：0)

## Solution

考虑枚举 $j$。

使 $pre_i$ 表示当前时刻 $i$ 在选定 $j$ 前面出现的次数，$suf_i$ 表示当前时刻 $i$ 在选定 $j$ 后面出现的次数。

用一个变量 $p$ 记录当前 $\sum_{i = 1}^{n} pre_i \times suf_i$ 的值。

对于 $j \in [2, n - 1]$，累加 $p$ 减去 $pre_{a_j} - suf_{a_j}$ （即 $a_i = a_j$）的情况数。

后面处理 $suf$ 与 $pre$ 的变化，由于这个变化为 $1$，很好处理。

处理时更新 $p$ 的值。

建议和代码结合食用。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}
void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

const int N = 3e5 + 5;
int pre[N], suf[N], p = 0;
int n, a[N], ans = 0;

signed main()
{
	n = read();
	for (int i = 1; i <= n; i ++) a[i] = read();
	for (int i = 3; i <= n; i ++) suf[a[i]] ++;
	pre[a[1]] ++, p = pre[a[1]] * suf[a[1]];
	for (int i = 2; i < n; i ++){
		ans += p - pre[a[i]] * suf[a[i]];
		p -= suf[a[i + 1]] * pre[a[i + 1]];
		suf[a[i + 1]] --;
		p += suf[a[i + 1]] * pre[a[i + 1]];
		p += suf[a[i]];
		pre[a[i]] ++;
	} 
	cout << ans;
    return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc318_e)

开场 $11$ 分钟切，但是手贱点了 Unrated。

## $\mathtt{Solution}$

一个还算可以的题目。

因为 $i,k$ 是等价的，所以容易想到枚举 $j$。

定义两个数组 $cnt_i,cnt2_i$，分别表示当前枚举的 $j$ 的前面有多少个 $i$，以及当前枚举的 $j$ 的后面有多少个 $i$。

不难得到每一次的答案是 $\sum\limits^n_{i=1,i\ne a_j}cnt_i\times cnt2_i$，可以先把一开始的答案预处理出来（其实就是 $0$），然后每次更新即可。

因为这次 $a_j$ 是“右边的”，下一次它就是“左边的”了，于是计算完答案之后 $cnt2_{a_j}-1,cnt_{a_j}+1$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
const int MAXN = 3e5 + 5; 
int n, ans, res, a[MAXN], cnt[MAXN], cnt2[MAXN];
signed main(){
	n = read();
	for(int i = 1;i <= n;i ++)a[i] = read(), cnt2[a[i]] ++;
	for(int i = 1;i <= n;i ++){
		res += ans - cnt[a[i]] * cnt2[a[i]];
		ans -= cnt[a[i]] * cnt2[a[i]];
		ans += (cnt[a[i]] + 1) * (cnt2[a[i]] - 1);
		cnt[a[i]] ++, cnt2[a[i]] --; 
//		printf("%lld %lld\n", i, ans);
	}
	printf("%lld", res);
	return 0;
}

```


---

## 作者：happybob (赞：0)

没啥困难的。

枚举 $i$，然后找出所有在 $i$ 后面可以出现的 $k$。对于某个 $k$，设 $(i,k)$ 中有 $x$ 个 $a_j = a_i$，那么 $k$ 的贡献是 $k-1-i-x$。

发现后面 $x$ 是一个等差数列，前面可以把 $i$ 提出来，$k-1$ 可以动态维护和，就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

const int N = 3e5 + 5, MOD = 1e9 + 7; // Remember to change

int n, m, q, t, a[N];
set<int> st[N];
long long nowsum[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],st[a[i]].insert(i),nowsum[a[i]]+=(i-1);
	long long ans=0LL;
	for(int i=1;i<=n;i++)
	{
		nowsum[a[i]]-=(i-1);
		st[a[i]].erase(st[a[i]].begin());
		long long l=1,r=st[a[i]].size()-1;
		long long ss=(l>r?0LL:(l+r)*(r-l+1)/2);
		ans+=nowsum[a[i]]-(long long)st[a[i]].size()*(i)-ss;
	}
	cout<<ans<<"\n";
	return 0;
}

```


---

## 作者：_7Mr (赞：0)

# 翻译

给你一个长度为 $N$ 的正整数数组。求满足下列所有条件的正整数三元组 $(i,j,k)$ 的个数。

- $1 \le i < j < k \le N$。
- $A_i = A_k$。
- $A_i \ne A_j$。

# 思路

看到这个题不要慌，肯定是推结论，那么我们来找找规律。

比如说 `12121` 我们可以发现答案为 $5$。我们可以将这个样例分成 $2$ 类。

- 第一类，形如 `1 x 1`。
- 第二类，形如 `2 x 2`。

现在有个很重要的东西出现了，可以发现每一类之间**互不影响**也就是说我们可以分开单独来算。

我们继续分析，可以分析出，对于每一类的答案，只和中间的数的个数有关。那么我们就可以将相同两个数中间的个数算出来，然后用 map 存一下就行了。

接下来我们只需要统计答案就行了，继续分析下去，发现每一段中间的个数和他是第几个中间的个数有关，就比如我现在有一个数，他每两个中间的间隔数为 `1 2 3` 那么我们的答案就为 $1+2+3+2+3+3$ 发现没有，我们算出来的间隔数要乘以他是第几个，最后算出答案就行了。

# ACcode

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
const int maxn=3e6+5;
int n,ans;
int a[maxn],last[maxn],now[maxn];
map<int,map<int,int> >sum;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		if(last[a[i]]==0) last[a[i]]=i;//第一次出现特殊处理
		else {
			sum[a[i]][++now[a[i]]]=i-last[a[i]]-1;//算间隔数
			last[a[i]]=i;
		}
	}
	for(int i=1; i<=n; i++) {//算出答案
		int wh=0,p=1;
		for(int j=1; j<=now[i]; j++) {
			wh+=sum[i][j]*p;
			ans+=wh;
			p++;//第几个
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ldj2006 (赞：0)

# [ABC318E] Sandwiches 题解

## 题意简述

&emsp; &emsp;给定包含 $n$ 个整数的序列 $a$，其中任意元素的值 $a_i \in [1,n]$，统计包含三个元素的满足以下条件有序三元组数量：满足下标严格递增；满足第一个和最后一个元素相等，而中间的元素和两端的元素不相等。

&emsp; &emsp;记录三元组 $(a_i,a_j,a_k)$，即 $1 \le i < j < k \le n , a_i = a_k \ne a_j$。

## 思路分析

&emsp; &emsp;看到统计三元组就想到了扫描线。我们以 $k$ 为扫描线，统计在 $k$ 左侧的满足条件的三元组。

&emsp; &emsp;我们先观察到 $a_i = a_k$ 是个比较严格的条件限制，于是我们可以 $n$ 个 vector 维护每种数组的对应下标。现在我们画一张图：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/m8hoxca8.png)

&emsp; &emsp;我们令当前扫描线位置为 $t$，**所有** 和 $a_t$ 数字相同的，在 $t$ 左侧的元素，下标为 ${idx}_i$。那么除了这些元素，剩下的元素数字一定和 $a_t$ 不同。我们统计每对 ${idx}_i$ 到 $t$ 之间（假设之前共有 $m$ 个，$i \in [1,m]$），和 $a_t$ 数字不同的元素个数，在加和即可。注意要减掉区间中间，包含的数字等于 $a_t$ 的元素数量，当然这个可以通过 $i$ 算出来。

&emsp; &emsp;我们可以发现：

$$
{idx}_1\text{的贡献：} t - {idx_1} - 2 - 1 \\
{idx}_2\text{的贡献：} t - {idx_2} - 1 - 1 \\
{idx}_3\text{的贡献：} t - {idx_3} - 0 - 1 \\
\dots\\
{idx}_i\text{的贡献：} t - {idx_i} - (m-i) - 1 \\
$$

&emsp; &emsp;根据等差数列等相关知识，不难得出：

$$
$$

$$
\begin{aligned}
\text{总贡献} & = m \times t - \sum_i{{idx}_i} - m \times 1 - \frac{(m-1)m}{2} \\
& = m(t-1) - \frac{(m-1)m}{2} - \sum_i{{idx}_i}
\end{aligned}
$$

&emsp; &emsp;于是，我们甚至不用维护下标具体在哪里。我们只需要维护对于当前，之前下标的总和，和之前的下标总个数。计算完答案，在把当前的加入更新即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 3e5 + 5;

LL sumidx[N];
LL cntidx[N];

LL a[N];
LL n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	LL ans = 0;
	for(LL i = 1;i <= n;i++)
	{
		ans += cntidx[a[i]]*(i-1ll) - sumidx[a[i]] - (cntidx[a[i]]-1)*cntidx[a[i]]/2ll;
		cntidx[a[i]]++;
		sumidx[a[i]] += i;
	}
	cout << ans << "\n";
	return 0;
}
```

---

