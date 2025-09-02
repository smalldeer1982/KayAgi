# Decryption

## 题目描述

An agent called Cypher is decrypting a message, that contains a [composite number](https://en.wikipedia.org/wiki/Composite_number) $ n $ . All divisors of $ n $ , which are greater than $ 1 $ , are placed in a circle. Cypher can choose the initial order of numbers in the circle.

In one move Cypher can choose two adjacent numbers in a circle and insert their [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) between them. He can do that move as many times as needed.

A message is decrypted, if every two adjacent numbers are not coprime. Note that for such constraints it's always possible to decrypt the message.

Find the minimal number of moves that Cypher should do to decrypt the message, and show the initial order of numbers in the circle for that.

## 说明/提示

In the first test case $ 6 $ has three divisors, which are greater than $ 1 $ : $ 2, 3, 6 $ . Regardless of the initial order, numbers $ 2 $ and $ 3 $ are adjacent, so it's needed to place their least common multiple between them. After that the circle becomes $ 2, 6, 3, 6 $ , and every two adjacent numbers are not coprime.

In the second test case $ 4 $ has two divisors greater than $ 1 $ : $ 2, 4 $ , and they are not coprime, so any initial order is correct, and it's not needed to place any least common multiples.

In the third test case all divisors of $ 30 $ greater than $ 1 $ can be placed in some order so that there are no two adjacent numbers that are coprime.

## 样例 #1

### 输入

```
3
6
4
30```

### 输出

```
2 3 6 
1
2 4 
0
2 30 6 3 15 5 10 
0```

# 题解

## 作者：灵茶山艾府 (赞：4)

有一个巧妙的解法：格雷码。

这里不介绍格雷码，不了解的可以看 [P5657](https://www.luogu.com.cn/problem/P5657)。

把 $n$ 质因数分解为 $p_1^{e_1}p_2^{e_2}\dots p_k^{e_k}$。对于 $n$ 的每个因数 $d$，可以用 $0$ 或 $1$ 表示其能否被某个质数 $p_i$ 整除，这可以压缩成一个数，记作 $mask$。例如 $n=30$，因数 $10$ 对应的 $mask=101_{(2)}$。

显然，每个 $[1,2^k-1]$ 中的 $mask$ 都至少有一个对应的因数。

题目要求不存在两个相邻且互质的因数，格雷码看上去恰好可以满足这个要求，但是需要做一些修改。

由于 $mask\neq 0$，我们需要找一个数来替代格雷码上的 $0$。例如 $k=3$ 时，格雷码为

```
001
011
010
110
111
101
100
```

由于是环形的，首尾并不满足要求，我们不妨将 `111` 移至末尾，这样就可以构造出满足题目要求的排列了。打印的时候，先打印所有 $mask$ 为 `001` 的因数，然后打印为 `011` 的，……，最后打印为 `111` 的。

$k>3$ 的构造方法也是类似的。

那么 $k=2$ 时呢？此时格雷码为 

```
01
11
10
```

若所有 $e_i$ 均为 $1$ ，无论怎么摆放必然会存在相邻互质的因数。反之，`11` 对应的因数不止一个，可以按 `01->11->10->11` 的顺序打印，即留一个 $mask$ 为 `11` 的因数放中间打印，剩余的在最后打印。


$k=1$ 的情况可以直接打印所有因数。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> fs;
vector<int> ans;

void f(int mask, int d) {
	if (mask == 0) {
		ans.push_back(d);
		return;
	}
	auto p = fs[__builtin_ctz(mask)];
	mask &= mask - 1;
	for (int i = 0; i < p.second; i++) {
		d *= p.first;
		f(mask, d);
	}
}

void run() {
	int n; cin >> n;
	int insert = 1;
	fs.resize(0);
	for (int i = 2; i * i <= n; i++) {
		int e = 0;
		for (; n % i == 0; n /= i) e++;
		if (e) {
			fs.emplace_back(i, e);
			if (e > 1) insert = 0;
		}
	}
	if (n > 1) fs.emplace_back(n, 1);

	ans.resize(0);
	int k = fs.size(), l, r;
	for (int i = 1; i < 1 << k; i++) {
		int mask = i ^ (i >> 1);
		if (mask + 1 == 1 << k) {
			l = ans.size();
			f(mask, 1);
			r = ans.size();
		} else f(mask, 1);
	}
	if (k == 2) l++;
	else insert = 0;

	int m = ans.size();
	for (int i = 0; i < l; i++) cout << ans[i] << ' ';
	for (int i = r; i < m; i++) cout << ans[i] << ' ';
	for (int i = l; i < r; i++) cout << ans[i] << ' ';
	cout << '\n' << insert << '\n';
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int t;
	for (cin >> t; t--; run());
	return 0;
}
```






---

## 作者：Lily_White (赞：3)

吐槽：我真的很佩服自己的乱序做题技能。VP 结果如下：
![VP Standings](https://cdn.luogu.com.cn/upload/image_hosting/q6gojen4.png)

好，进入正题。

这是一道数论题。我们首先手玩几组数据。下面，我们使用 $[a_1, a_2, \ldots, a_n, (a_1)]$ 的格式表示一个环。

- $6$

	注意到 $6 = 2 \times 3$。 因此一种构造方法是 $[2, 3, 6, (2)]$。需要一次操作把它变成 $[2, \text{\color{green}6}, 3, 6, (2)]$。容易知道这是最好的方法。
    
- $18$

	构造为 $[2, 4, 6, 3, 9, 18, (2)]$。不需要任何操作。
    
- $22$

	构造为 $[2, 11, 22, (2)]$。需要一次操作变成 $[2, \text{\color{green}22}, 11, 22, (2)]$。
    
- $24$

	构造为 $[2, 4, 8, 12, 6, 3, 24, (2)]$，不需要操作。
    
…………

我们可以发现这样的规律：

**猜想：** 如果一个合数可以写成 $p_1p_2$ 的形式，其中 $p_1, p_2$ 是素数（下同），那么我们就需要一次操作。否则，我们不需要操作。

下面，我们构造地证明这个猜想：

**证明：** 

首先定义大于 $1$ 的因数为*非平凡的*，令 $n$ 的非平凡因数集为 $S$。令 $P$ 为素数集。先考虑 $n = p_1p_2$ 的情况。

此时，$n$ 恰有三个非平凡的因数，它们是 $p_1, p_2, n$。

又因为 $p_1, p_2 \in P$，因此必然有 $\gcd(p_1, p_2)=1$。

注意到无论如何排列这三个因数，$p_1,p_2$ 必定是相邻的。因此，我们必须使用恰好一次操作，在 $p_1, p_2$ 之间插入 $\operatorname{lcm}(p_1, p_2)$ 来满足题意。

猜想的第一部分得证。

再考虑另外一种情况，利用算术基本定理我们有

$$n=\prod^{k}_{i=1}p_i^{\alpha_i},\qquad\forall 1\le i \le n, p_i \le p_{i+1}$$

此时，不难得到
$$\forall x,y \in S, \gcd(x, y)=1 \Leftrightarrow x, y \in P$$

进而，我们可以按照如下方法得到一个符合要求的构造：首先，写下 $n$ 的所有的素因子 $p_{1 \ldots k}$。接着，$\forall 1 \le i \le k$，在 $p_i, p_{(i+1) \operatorname{mod} k}$ 间插入 $p_ip_{i+1}$。最后，对于其他未使用过的数 $x$，我们将其插在 $p_i$ 和 $p_ip_{(i+1) \operatorname{mod} k}$ 之间，其中 $i$ 为满足 $1 \le i \le k, p_i \mid x$ 的最小 $i$。

不难知道，这样的构造符合题目的要求，因此，此时不需要任何操作。

至此，猜想得证。证完。

利用上面的推导，不难写出[代码](https://codeforces.com/contest/1419/submission/93407171)。

---

## 作者：tommymio (赞：3)

后排占坑，赛时没写出这题，赛后突然发现是个傻逼题，来写篇题解。

根据唯一分解定理，一个数 $n$ 可以被分解成 $\prod_{i=1}^{m} p_i^{b_i}$ 的形式，那么根据不同情况讨论即可，不难发现对于 $m>2$ 的情况，一定能够构造出一组解使得一次操作也不用进行。因为如果将这题看成一个图论问题，具有相同质因子的 $n$ 的因数连一条边，易证这个图上一定存在一个覆盖所有点的环。

那么对于 $m\leq 2$ 的情况呢？如果有两个以上的质因子相乘，本质和 $m>2$ 是相同的。也不会存在只有一个质因子的情况，因为 **$n$ 是合数**。那么对于只有两个质因数相乘的情况，在任何情况下都必须操作一次。

可能对于 $r$ 个质因子相乘 $(r>2)$ 的情况比较难以构造方案。我们可以将含有相同质因子的归为一类，在每两类之间插入一个含有两类质因子的数，不妨选为 $p_ip_{i-1}$。为了方便转移，我们可以先质因数分解，枚举每个质因子，将第 $i$ 个质因子之前的质因子所能构成的因子乘上第 $i$ 个质因子的幂，每次输出含有第 $i$ 个质因子的因子即可。

由于最多不会超过 $31$ 个质因子，这些质因子能够构成的因子不超过 $2\sqrt n$ 个，因此时间复杂度还是有保证的，理论最劣复杂度大概为 $O(62\sqrt n)$，但是在 $\text{Codeforces}$ 的神仙姬上跑的飞快，还进入了你谷最优解 $\text{rk} 4$（雾

**Show the Code**

```cpp
#include<cstdio>
#include<vector>
int num,tot,hd,top=0;
std::vector<int> vec;
int p[35],cnt[35],st[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void DivideByPrime(int n) {
	num=0;
	for(register int i=2;i*i<=n;++i) {
		if(n%i==0) {
			p[++num]=i;cnt[num]=0;
			while(n%i==0) {++cnt[num];n/=i;}
		}
	}
	if(n>1) {p[++num]=n; cnt[num]=1;}
}
int main() {
	int T=read();
	while(T--) {
		int n=read();
		DivideByPrime(n); 
		if(num==2&&cnt[1]==1&&cnt[2]==1) {printf("%d %d %d\n",n,p[1],p[2]);printf("1\n");}
		else {
			vec.clear();
			for(register int i=num;i>=1;--i) {
				for(register int j=0;j<vec.size();++j) {
					int cur=vec[j];
					for(register int k=1,x=p[i];k<=cnt[i];++k,x*=p[i]) {st[++top]=cur*x;}
				}
				int pos=(vec.size()>=1? vec.size():0);
				for(register int k=1,x=p[i];k<=cnt[i];++k,x*=p[i]) vec.push_back(x);
				while(top) {vec.push_back(st[top--]);}
				for(register int j=pos;j<vec.size();++j) {
					if((vec[j]%p[i]==0&&(vec[j]/p[i]==p[i-1]||vec[j]/p[i]==p[i+1]))||vec[j]==n) continue;
					printf("%d ",vec[j]);
				}
				if(i!=1) printf("%d ",p[i]*p[i-1]);
			}
			printf("%d\n0\n",n);
		}
	}
	return 0;
}
```



---

## 作者：jun头吉吉 (赞：3)

# 题解 CF1419E 【Decryption】

[$\color{skyblue}{\text{更好的阅读体验}}$](https://chen-jia-liang.gitee.io/blog/2020/09/20/%E9%A2%98%E8%A7%A3-CF1419E-%E3%80%90Decryption%E3%80%91/)
## 题意

设$p_1,p_2,\ldots,p_n$为$x$的所有非一因数，把它们重新排列在一个环上$a_1,a_2,\ldots,a_n$，第$1$个与第$n$个相邻。你每次可以选择$a_i$与$a_{i+1}$(或$a_1$)，在它们中间插入$\operatorname{lcm}(a_i,a_i+1)$，请求出最少的操作次数。

## 题解

听神仙说最多操作一次，可小蒟蒻太弱了，只会从样例找规律。

```
30
2 30 6 3 15 5 10 
```

然后从`30`开始反着看：

```
30 2 10 5 15 3 6
```
似乎有什么规律。再仔细观察一下，我们发现：

这不就是先选$n$，然后每次找一个与最后一个数不互质的最小的数，在统计次数就行了

正确性未知，但能在~~CF那群毒瘤~~的hack下活下来，应该是对的吧。

代码很好写。首先从$2\to\sqrt{x}$枚举$x$的因数，用一个`vector`存下来，然后不停地找就行了。

这里使用c++内置的`__gcd`来判断互质（主要是我不会辗转相除法

## 代码
```cpp
int t,n;vector<int>pr; 
int ans[100000];int len=0;
signed main(){
	in::read(t);;
	while(t--){
		in::read(n);pr.clear();
		for(int i=2;i<=sqrt(n);i++)
			if(n%i==0){
				pr.push_back(i);
				if(n!=i*i)pr.push_back(n/i);
			}
		sort(pr.begin(),pr.end());
		ans[len=1]=n;int ci=0;
		for(int i=2;pr.size();i++){
			//cout<<pr.size()<<endl;
			int tmp=-1;
			for(vector<int>::iterator it=pr.begin();it!=pr.end();it++)
				if(__gcd(*it,ans[len])!=1){
					tmp=*it;
					pr.erase(it);
					break;
				}
			if(tmp==-1){
				tmp=*pr.begin();
				pr.erase(pr.begin());
			}
			ci+=__gcd(tmp,ans[len])==1;
			ans[++len]=tmp;
		}
		ci+=__gcd(ans[len],ans[1])==1;
		for(int i=1;i<=len;i++)
			out::write(ans[i]),out::putc(' ');
		out::putc('\n');out::write(ci);out::putc('\n');
	}
	out::flush();
	return 0;
}
```

---

## 作者：SSerxhs (赞：2)

答案只可能是 $0,1$，且当且仅当 $n=pq(p,q\in prime,p\ne q)$ 时答案为 $1$

首先考虑答案为 $1$ 的情况。此时只有三个数 $p,q,pq$，只有 $(p,q)=1$，正确性和构造方法显然

接着考虑其他情况。设 $n$ 有 $m$ 个不同的素因子，并按幂次大小从大到小排列记为 $p_i$，幂次记为 $a_i$

若 $m=1$，则按大小排序即可（其实随便排都可以）

若 $m=2$，由于不满足上一个情况所以 $a_1\ge 2$，构造方法： $p_1\times p_2$，所有 $p_1$ 的其他倍数（前面未提及的且不是 $p_1,p_1^2\times 2$），$p_1$，$p_1^2\times p_2$,所有 $p_2$ 的其他倍数（前面未提及的且不是 $p_2$），$p_2$

正确性显然

若 $m\ge3$，先给所有的 $p_i\times p_{i+1},p_1\times p_m,p_i$ 都打上标记，（其余的都可以作为下文的倍数被填充）

构造方法： $p_1\times p_m$，$p_1$ 未填充倍数，$p_1$，$p_1\times p_2$，$p_2$ 未填充倍数，$p_2$，$p_2\times p_3$，以此类推。

正确性显然

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int ss[200002][2],ys[200002];
int n,c,fh,i,gs,gss,t,m,j,k;
bool ed[200002];
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
inline int fd(int x)
{
	return lower_bound(ys+1,ys+gss+1,x)-ys;
}
int main()
{
	read(t);
	while (t--)
	{
		memset(ed+1,0,gss);
		gs=gss=0;
		read(n);m=sqrt(n);while ((m+1)*(m+1)<=n) ++m;
		for (i=2;i<=m;i++) if (n%i==0)
		{
			ys[++gss]=i;
			if (i*i!=n) ys[++gss]=n/i;
		}ys[++gss]=n;
		sort(ys+1,ys+gss+1);
		for (i=2;i<=m;i++) if (n%i==0)
		{
			ss[++gs][0]=i;ss[gs][1]=1;
			while ((n=n/i)%i==0) ++ss[gs][1];
		}
		if (n!=1) {ss[++gs][0]=n;ss[gs][1]=1;}
		if (gs<=1)
		{
			for (i=1,j=ss[gs][0];i<=ss[gs][1];i++,j*=ss[gs][0]) printf("%d ",j);puts("\n0");
			continue;
		}
		if ((gs==2))
		{
			if ((ss[1][1]==1)&&(ss[2][1]==1)) printf("%d %d %d\n1\n",ss[1][0],ss[1][0]*ss[2][0],ss[2][0]);
			else
			{
				if (ss[1][1]==1) {swap(ss[1][1],ss[2][1]);swap(ss[1][0],ss[2][0]);}
				ed[fd(ss[1][0]*ss[2][0])]=ed[fd(ss[1][0]*ss[1][0]*ss[2][0])]=ed[fd(ss[1][0])]=ed[fd(ss[2][0])]=1;
				printf("%d ",ss[1][0]*ss[2][0]);
				for (i=1;i<=gss;i++) if ((!ed[i])&&(ys[i]%ss[1][0]==0))
				{
					ed[i]=1;
					printf("%d ",ys[i]);
				}
				printf("%d %d ",ss[1][0],ss[1][0]*ss[1][0]*ss[2][0]);
				for (i=1;i<=gss;i++) if (!ed[i]) printf("%d ",ys[i]);printf("%d\n",ss[2][0]);
				puts("0");
			}
			continue;
		}ss[0][0]=ss[gs][0];
		for (i=1;i<=gs;i++) ed[fd(ss[i][0])]=ed[fd(ss[i][0]*ss[i-1][0])]=1;
		for (i=1;i<=gs;i++)
		{
			printf("%d ",ss[i][0]*ss[i-1][0]);
			for (j=1;j<=gss;j++) if ((!ed[j])&&(ys[j]%ss[i][0]==0)) {printf("%d ",ys[j]);ed[j]=1;}
			printf("%d ",ss[i][0]);
		}puts("\n0");
	}
}
```

---

## 作者：Demoe (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1419E)

## 题意

- 给定一个**合数**，对于它大于 $1$ 的所有因数，找到一个排列，使得相邻两个数互质的数量尽可能小，输出方案及这个数量。

## Sol

先考虑求那个数量。

先考虑 $x=p^k$，显然为 $0$，且以任意顺序输出皆可。

再考虑 $x=p_1p_2$，存在三个因数，且有两个互质，所以答案为 $1$，任意顺序输出即可。

再考虑 $x=p_1^{k_1}p_2$，可以构造成 $p_1,p_1p_2,p_2,p_1^2p2$，其余填进去即可。

接下来再考虑 $x=\prod^n_{i=1}p_i^{k_i}$，可以构造成 $p_1,p_1p_2,p_2,p_2p_3...p_n,p_np_1$，再将其余数填进去。

所以可得仅有 $x=p_1p_2$ 时答案为 $1$ 其余时候为 $0$。

我们考虑对 $x=\prod^n_{i=1}p_i^{k_i}$ 构造方案。

因为我的写法比较烂，所以 $n=2$ 时要特判输出。

下面仅考虑 $n>2$ 时。

考虑将 $p_1p_n$ 最后输出，保证 $p_1$ 和 $p_n$ 连通。

对于每个 $p_i$，我们考虑 $\text{DFS}$ 输出。

考虑将 $p_ip_{i+1}$ 最后一个输出保证与 $p_{i+1}$ 连通。

其余可枚举后面每个质因数出现个数输出积即可。

```cpp
// wish to get better qwq
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e6+5;
ll t,n,p[N],cnt,sum,a[(N<<1)],qaq[N],qwq[N],cc,maxn;
bool pri[N];
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
void prime(ll x){
	pri[1]=1;
	for(ll i=2;i<=x;i++){
		if(!pri[i]) p[cnt++]=i;
		for(ll j=0;j<cnt&&i*p[j]<=x;j++){
			pri[i*p[j]]=1;
			if(!(i%p[j])) break;
		}
	}
}
void dfs(ll nw,ll x,ll sum){
	if(x==cc){
//		cout<<endl;
//		cout<<sum<<' '<<p[qwq[0]]<<' '<<maxn<<' '<<p[qwq[nw]]<<' '<<p[qwq[nw+1]]<<endl;
		if(sum!=p[qwq[0]]*maxn&&sum!=p[qwq[nw]]*p[qwq[nw+1]]) wr(sum),putchar(' ');
		return ;
	}
	ll awa=1;
	for(ll i=0;i<=qaq[qwq[x]];i++) dfs(nw,x+1,sum*awa),awa*=p[qwq[x]];
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(t);
	prime(N-5);
	while(t--){
		rd(n);sum=cc=maxn=0;
		a[sum++]=n;ll i=2;
		for(i=2;i*i<n;i++) if(n%i==0) a[sum++]=i,a[sum++]=n/i;
		if(i*i==n) a[sum++]=i;
		for(i=0;i<cnt;i++){
			qaq[i]=0;
			if(n%p[i]==0) qwq[cc++]=i,maxn=max(maxn,p[i]);
			while(n%p[i]==0) qaq[i]++,n/=p[i];
			if(n==1||p[i]*p[i]>n) break;
		}
		qaq[cnt]=0;
		if(n>1) qwq[cc++]=cnt,qaq[cnt]++,p[cnt]=n,maxn=max(maxn,n);
		if(sum==2){
			wr(a[0]),putchar(' '),wr(a[1]),puts("");
			wr(0);puts("");
			continue;
		}
		if(sum==3){
			if(a[1]*a[1]*a[1]==a[0]){
				wr(a[1]),putchar(' '),wr(a[2]),putchar(' '),wr(a[0]),puts("");
				wr(0);puts("");
			}
			else{
				wr(a[0]),putchar(' '),wr(a[1]),putchar(' '),wr(a[2]),puts("");
				wr(1);puts("");
			}
			continue;
		}
		if(cc==1){
			ll awa=1;
			for(ll i=1;i<=qaq[qwq[0]];i++) awa*=p[qwq[0]],wr(awa),putchar(' ');puts("");
			wr(0);puts("");
			continue;
		}
		ll awa=1;
		for(i=0;i<cc-1;i++){
			awa=1;
			for(ll j=1;j<=qaq[qwq[i]];j++) awa*=p[qwq[i]],dfs(i,i+1,awa);
			if(cc!=2) wr(p[qwq[i]]*p[qwq[i+1]]),putchar(' ');
		}
	//	cout<<"qwq"<<endl;
		for(i=1,awa=1;i<=qaq[qwq[cc-1]];i++) awa*=p[qwq[cc-1]],wr(awa),putchar(' ');
		wr(p[qwq[cc-1]]*p[qwq[0]]);puts("");
		wr(0);puts("");
	}
	return 0;
}
```

~~嘤嘤嘤没上 CM/kk~~

---

## 作者：lfxxx (赞：1)

首先直觉上答案非常小，于是考虑直接开始构造。

首先列出 $n$ 的所有质因子 $p_1 \sim p_k$，我们考虑构造 $k$ 段，第 $i$ 段间通过质因子 $p_i$ 保证不互质，段 $i$ 与段 $i+1$ 的交界处放 $p_i \times p_{i+1}$。剩余的有多个质因子的因数具体放哪段是无关紧要的，随便放下即可。

不难发现，当 $k \not = 2$ 时这个构造是最优的，可以取到 $0$ 次操作。

当 $k = 2$ 时，需要放两个 $p_1 \times p_2$ 的倍数，当 $n \not = p_1 \times p_2$ 时另一个就放 $n$，否则一定有 $n = p_1 \times p_2$，这种情况直接通过样例可得最优放法是 $p_1,p_2,n$，操作次数至少为 $1$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int warma = 1e5+114;
int t,n;
void solve(){
    cin>>n;
    set<int> S;
    for(int i=1;i<=min(n,warma);i++){
        if(n%i==0) S.insert(i);
        if(n%(n/i)==0) S.insert(n/i);
    }
    S.erase(1);
    vector<int> p;
    vector<int> end;
    int N=n;
    for(int x:S){
        if(N%x==0){
            p.push_back(x);
            while(N%x==0) N/=x;
        }
    }
    if(p.size()==2&&p[0]*p[1]==n){
        cout<<p[0]<<' '<<p[1]<<' '<<n<<'\n';
        cout<<1<<'\n';
        return ;
    }
    for(int i=0;i<p.size();i++){
        int u=p[i]*p[(i+1)%p.size()];
        if(S.find(u)==S.end()) u=n;
        end.push_back(u);
        S.erase(u);
    }
    vector< vector<int> > d;
    d.resize(p.size());
    for(int x:S){
        for(int i=0;i<p.size();i++){
            if(x%p[i]==0){
                d[i].push_back(x);
                break;
            }
        }
    }
    for(int i=0;i<p.size();i++){
        for(int x:d[i]) cout<<x<<' ';
        cout<<end[i]<<' ';
    }
    cout<<'\n';
    cout<<0<<'\n';
    return ;
}
int main(){
    cin>>t;
    while(t--) solve();
    return 0;
}
//by ChiFAN
```

---

## 作者：_Day_Tao_ (赞：1)

妙妙构造题。

首先比较显然的一点是，操作一次过后，新加入的数肯定不会有新的操作了，所以问题就转化为了构造一个数列，使得相邻两个数互质的数量尽可能少。

根据唯一分解定理，$n=\prod\limits_{i=1}^m p_i^{k_i}$，考虑如何才能让操作次数尽可能小。当相邻两个数不互质的时候，两个数存在至少一个公共的质因子，我们称这样的质因子为两数的“桥”。

有个结论：操作次数有且仅有 $0,1$ 两种情况，且操作次数为 $0$ 当且仅当 $n=a\times b\wedge a,b\in \mathbb{P}$。要使操作次数为 $0$，那么每两个数之间都要有一道桥，显然对于上面这种情况只能找到两个桥。接下来考虑这种情况之外的情况。

我们考虑把质因子从小到大排序，将含有至少一个质因子 $p_i$、不含有质因子 $p_1\cdots p_{i-1}$，$p_{i+1}\cdots p_n$ 任选的那些因数归为一块。容易发现，对于同一块之间肯定都是两两有桥的，也就是 $p_i$，接下来我们只需要考虑块与块之间的桥如何构建。又容易发现，$\prod\limits_{j=i}^m p_j^{k_j}$ 与下一块也一定存在一个桥，就是 $p_{i+1}$。再考虑 $p_1$ 和 $p_m$ 之间如何建桥。显然的，可以直接用 $n$ 去连接这两个质因子，只要把 $n$ 从 $p_1$ 的块中拿出来就行了。这样我们就构造好了。

注意有一种情况，就是 $m=2\wedge k_2=1$，我这种写法第一次连接两数的时候只能用 $n$，可以交换一下 $p_1,p_2$ 以及对应的 $k_1,k_2$ 来解决。

只有 831B 的小清新代码：

```
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
int n,nn,m;
vector<pii>v;
void print(int prod,int l,int r)
{
	if(prod==n)return; if(l>r)return printf("%d ",prod),void();
	if(prod!=1)print(prod,l+1,r);
	for(int i=1;i<=v[l].se;i++)prod*=v[l].fi,print(prod,l+1,r);
}
inline void solve()
{
	scanf("%d",&n),v.clear(),nn=n;
	for(int i=2,cnt;i*i<=n;i++)
	{
		cnt=0;while(nn%i==0)++cnt,nn/=i;
		if(cnt)v.push_back({i,cnt});
	}
	if(nn>1)v.push_back({nn,1});
	int m=(int)v.size()-1;
	if(m==1)if(v[0].se==1&&v[1].se==1)
		return printf("%d %d %d\n1\n",v[0].fi,n,v[1].fi),void();
	else if(v[1].se==1) swap(v[0],v[1]);
	for(int i=0;i<=m;i++) print(1,i,m);
	printf("%d\n0\n",n);
	return ;
}
signed main(){int T;scanf("%d",&T);while(T--) solve();return 0;}
```

---

## 作者：RedLycoris (赞：1)

人菜，只会打暴力

~~虽然是用小号，~~ 但还是div2里第一个AC的

由于每操作一次就相当于将两个不互质的数变得互质，所以我们的目标是找到一种排列使得相邻两个数不互质的数量尽可能的少。

考虑分解质因数。将由相同质因数的放在一起，留下一个做为连接这个质因数与下一个质因数的桥梁。

暴力即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define mp make_pair
#define ri register int
#define ld long double
using namespace std;
const int mxn=2e5+5;
vector<int>g[mxn];
int n,m;
int a[mxn];
vector<int>ps;
inline void solve(){
	cin>>n;ps.clear();int tn=n;
	vector<int>v;v.clear();
	for(int i=2;i*i<=n;++i){
		if(n%i==0){
			v.push_back(i);
			if(i!=n/i)v.push_back(n/i);
		}
	}
	v.push_back(n);
	sort(v.begin(),v.end());
	for(int i=2;i*i<=tn;++i){
		if(tn%i==0){
			ps.push_back(i);
			for(;tn%i==0;)tn/=i;
		}
	}
	if(tn!=1)ps.push_back(tn);
	if(ps.size()==1){
		for(int i:v)cout<<i<<' ';
		cout<<'\n'<<0<<'\n';
		return;
	}
	if(ps.size()==2 and v.size()==3){
		cout<<v[0]<<' '<<v[1]<<' '<<v[2]<<'\n';
		cout<<1<<'\n';
		return;
	}
	if(ps.size()>2){
		for(int i=0;i<ps.size()-1;++i){
			if(i){
				for(int j=0;j<v.size();++j){
					if(v[j]%ps[i]==0 ){
						if(v[j]!=ps[i]*ps[i+1])cout<<v[j]<<' ';
						v.erase(v.begin()+j);
						--j;		
					}
				}
				cout<<ps[i]*ps[i+1]<<' ';
			}else{
				cout<<ps[i]*ps[ps.size()-1]<<' ';
				for(int j=0;j<v.size();++j){
					if(v[j]%ps[i]==0 ){
						if(v[j]!=ps[i]*ps[i+1] and v[j]!=ps[i]*ps[ps.size()-1])cout<<v[j]<<' ';
						v.erase(v.begin()+j);
						--j;
					}
				}
				cout<<ps[i]*ps[i+1]<<' ';
			}
		}
		for(int i:v)cout<<i<<' ';cout<<"\n0\n";	
	}else{//只有两个质因数的时候不用留桥梁，需要特判
		for(int i=0;i<ps.size()-1;++i){
			if(i){
				for(int j=0;j<v.size();++j){
					if(v[j]%ps[i]==0 ){
						if(v[j]!=ps[i]*ps[i+1])cout<<v[j]<<' ';
						v.erase(v.begin()+j);
						--j;		
					}
				}
				cout<<ps[i]*ps[i+1]<<' ';
			}else{
				cout<<ps[i]*ps[ps.size()-1]<<' ';
				for(int j=0;j<v.size();++j){
					if(v[j]%ps[i]==0 ){
						if(v[j]!=ps[i]*ps[i+1] and v[j]!=ps[i]*ps[ps.size()-1])cout<<v[j]<<' ';
						v.erase(v.begin()+j);
						--j;
					}
				}
			}
		}
		for(int i:v)cout<<i<<' ';cout<<"\n0\n";	
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;cin>>T;
	for(;T--;)solve();
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

给定一个正整数 $n$，将它的所有大于一的因数按照任意顺序排列在一个环上，你每次可以选择圈上相邻的两个数，在它们中间插入他们的最小公倍数，使得最后的环上不存在两个相邻且互质的数。你需要找到一个需要进行操作次数最少的排列。

好像是某个数学竞赛的题目……

造几个数据发现答案不是 $0$ 就一定是 $1$。

考虑什么时候是 $1$。发现只有形如 $n = pq$ 的情况（$p,q$ 是质数）是 $1$。我们直接第一个放 $p$，第二个放 $q$，第三个放 $pq$ 就好。

接着考虑是 $0$ 的情况。

发现此时一定是两个数之间有一个和两个数都有相同质因子的数。

发现质因子最多不到 $20$ 个。考虑对于每种状态压缩，存储每一个数都可以被 $n$ 的哪些质因子整除。

那么，怎么保证相邻两项一定有相同的点呢？

我们拍拍脑袋——

**格雷码**！相邻两项只有一个位置不同。

但是这里状态序列不是序列，是个环，直接使用格雷码很有可能首尾不合法。

考虑把 `111...1` 这个状态串给放到最后。

这样的话，如果长度比 $2$ 大，这个串前后必有数相同。

那么，如果长度只有 $2$ 呢？（长度为 $1$ 只有一个数就不用考虑了）

此时序列一定是 `01 11 10`，不能直接把 `11` 放在最后。

如果 `11`，即 $p^mq^n$ 的数量比 $1$ 大，我们可以只放一个这样的数在末尾。

如果数量只有 $1$ 就没法放了，答案就是 $1$。这也证明了前面的情况。

然后就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int cnt=0,p[N],k[N];
int n;
int Gay(int x){return x^(x>>1);}
int g[1500010];
vector<int> mp[1500010];
void solve(){
    cin>>n;int z=n;
    for(int i=1;i<=20;++i)p[i]=k[i]=0;
    cnt=0;
    for(int i=2;i*i<=n;++i)if(n%i==0){
        p[++cnt]=i;
        while(n%i==0)n/=i,++k[cnt];
    }
    if(n>1){
        p[++cnt]=n;
        k[cnt]=1;
    }
    if(cnt==2 && k[1]==1 && k[2]==1){
        cout<<p[1]<<' '<<p[2]<<' '<<p[1]*p[2]<<'\n'<<1<<'\n';
        return;
    }
    for(int i=1;i<(1<<cnt);++i)mp[i].clear();
    n=z;
    for(int i=2;i*i<=n;++i)if(n%i==0){
        if(i*i==n){
            int sit=0;
            for(int j=1;j<=cnt;++j)if(i % p[j] == 0)sit+=(1<<(j-1));
            mp[sit].push_back(i);
        }
        else{
            int sit=0;
            for(int j=1;j<=cnt;++j)if(i % p[j] == 0)sit+=(1<<(j-1));
            mp[sit].push_back(i);
            sit=0;
            for(int j=1;j<=cnt;++j)if((n/i) % p[j] == 0)sit+=(1<<(j-1));
            mp[sit].push_back(n/i);
        }
    }
    mp[(1<<cnt)-1].push_back(n);
    if(cnt!=2){
        int pos=0;
        for(int i=1;i<(1<<cnt);++i)if(g[i]==((1<<cnt)-1)){pos=i;break;}
        swap(g[pos],g[(1<<cnt)-1]);
        for(int i=1;i<(1<<cnt);++i){
            if(!mp[g[i]].size())continue;
            for(auto k:mp[g[i]])cout<<k<<' ';
        }
        cout<<'\n'<<0<<'\n';
        swap(g[pos],g[(1<<cnt)-1]);
    }
    else{
        for(auto k:mp[1])cout<<k<<' ';
        int r=mp[3].size();--r;
        for(int i=0;i<r;++i)cout<<mp[3][i]<<' ';
        for(auto k:mp[2])cout<<k<<' ';
        cout<<mp[3][r]<<'\n';
        cout<<0<<'\n';
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    for(int i=1;i<=(1<<20);++i)g[i]=Gay(i);
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF1419E)

[CF's link](http://codeforces.com/problemset/problem/1419/E)

#### 题意：

给定一个正整数 $n$，将它的所有大于 $1$ 的因数按照任意顺序排列在一个环上，你每次可以选择圈上相邻的两个数，在它们中间插入他们的最小公倍数，使得最后的环上不存在两个相邻且互质的数。你需要找到一个需要进行操作次数最少的排列。 

#### Solution：

根据「唯一分解定理」，$n=p_{1}^{q1}\times p_{2}^{q2}\times\dots p_{k}^{qk}$。

1. $n$ 是质数，那么最少操作 $1$ 次。
2.  我们可以把 $n$ 的所有因数中被 $p_1$ 整除的分为一组，再把剩下的中被 $p_2$ 整除的分为一组，一直这样下去，在每组的边界上放能同时被两组的质因数整除的数。这样在 $n$ 不是两个不同的质数的乘积时结果一定是 $0$，否则是 $1$。 

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-26 08:21:28 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-26 10:31:25
 */
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=2e5+5;
int n,prime_tot,prime_ans[N],tong[N],note[N];
bool prime_pd[N];
bool check(int x){
    FOR(i,2,sqrt(x))
        if(x%i==0) return 0;
    return 1;
}
void prime(int x){
    memset(prime_pd,1,sizeof prime_pd);
    prime_pd[1]=0;
    FOR(i,2,x){
        if(prime_pd[i]) prime_ans[++prime_tot]=i;
        FOR(j,1,prime_tot){
            int y=i*prime_ans[j];
            if(y>x) break;
            prime_pd[y]=0;
            if(i%prime_ans[j]==0) break;
        }
    }
}
vector<int>a;
map<int,bool>mp;
int main(){
    prime(200000);
    int T=read();
    while(T--){
        a.clear();
        mp.clear();
        n=read();
        if(check(n)){
            write(1);putchar(' ');
            write(n);putchar(' ');
            puts("");
            puts("1");
            continue;
        }
        int m=n,sum=0;
        FOR(i,2,sqrt(n)){
            if(n%i==0){
                sum++;
                note[sum]=i;
                tong[sum]=1;
                while(n%i==0){
                    tong[sum]++;
                    n=n/i;
                }
            }
        }
        if(n!=1){
            sum++;
            note[sum]=n;
            tong[sum]=1;
        }
        n=m;
        FOR(i,2,sqrt(n)){
            if(n%i==0){
                a.push_back(i);
                if(i*i!=n) a.push_back(n/i);
            }
        }
        a.push_back(n);
        if(sum==1){
            for(auto it=a.begin();it<a.end();it++) write(*it),putchar(' ');
            puts("");
            write(0);
            puts("");
            continue;
        }
        if(sum==2&&note[1]*note[2]==n){
            write(note[1]),putchar(' ');
            write(note[2]),putchar(' ');
            write(n);
            puts("");
            puts("1");
            continue;
        }
        mp[n]=1;
        FOR(i,2,sum) mp[note[i-1]*note[i]]=1;
        FOR(i,1,sum){
            for(auto it=a.begin();it<a.end();it++) if(*it%note[i]==0&&!mp[*it]) write(*it),putchar(' '),mp[*it]=1;
            if(i<sum) write(note[i+1]*note[i]),putchar(' ');
            else write(n),putchar(' ');
        }
        puts("");
        write(0);
        puts("");
    }
    return 0;
}
```



---

## 作者：Pbri (赞：0)

写了份很丑的代码，赛时写的因为中间出去干了点事所以没有rush完，回来接着写了会调了调就出来了，因为当时很困所以写的很暴力很随意，开了好几个map。

先判一些特殊情况：

n是个质数，n是个质数的k次方，n除了自己只有两个因数且全部都是质数

然后就开始正常的过程了

先把所有的质因子拿出来变成链，然后往上面添加相邻两个质因数的乘积，最后的和一开始的可以不用管只要最后往里面加个n就可以了

处理质因子的时候因为有可能有质因子大于$\sqrt n$，比如$43=2\times3\times7$，但这样的质因子最多有一个（如果有两个乘积就大于n了），如果存在则一定是最小的大于根号n的因数，道理同上，所以只需要判断最小的大于根号n的因数是不是质数就可以了

然后把所有因数的最小质因子搞出来，因为因数不超过$\log(n)$所以时间复杂度可以保证，可以用类似于埃氏筛的方法做，然后往链里面添加，最后输出链就可以了

code：

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#define FUP(i,x,y) for(ll i=(x);i<=(y);i++)
#define FDW(i,x,y) for(ll i=(x);i>=(y);i--)
#define MAXN 200010
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define ll long long
#define db double
using namespace std;
ll read(){
    ll w=0,flg=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')flg=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){w=w*10-'0'+ch,ch=getchar();}
    return w*flg;
}
bool vis[50010];
ll prime[50010],x;
void oulasai()
{
    for(ll i=2;i<=50000;i++)
    {
        if(!vis[i]) prime[x++]=i;
        for(ll j=0;j<x;j++)
        {
            if(i*prime[j]>50000) break;
            vis[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
ll t;
map<ll,ll>mp1,mp2,mp3,mp4;
ll n,cnt,nxt[MAXN],ro[MAXN];
bool pdpri(ll x)
{
	for(ll i=2;i*i<=x;i++)
	{
		if(x%i==0) return false;
	}
	return true;
}
int main(){
	oulasai();
	t=read();
	while(t--)
	{
		mp1.clear(),mp2.clear(),mp3.clear(),mp4.clear();
		memset(nxt,0,sizeof(nxt));
		memset(ro,0,sizeof(ro));
		cnt=0;
		n=read();
		if(pdpri(n))
		{
			printf("%lld\n0\n",n);
			continue;
		}
		for(ll i=2;i*i<=n;i++)
		{
			if(n%i==0)
			{
				ro[++cnt]=i;
				if(i*i!=n) ro[++cnt]=n/i;
			}
		}
		ll tmp=n;
		while(tmp%ro[1]==0)
		{
			tmp/=ro[1];
		}
		if(tmp==1)
		{
			FUP(i,1,cnt) printf("%lld ",ro[i]);
			printf("%lld\n0\n",n);
			continue;
		}
		//cout<<ro[cnt]<<endl;
		if(cnt==2)
		{
			FUP(i,1,cnt) printf("%lld ",ro[i]);
			printf("%lld\n1\n",n);
			continue;
		}
		sort(ro+1,ro+cnt+1);
		FUP(i,1,cnt)
		{
			if(ro[i]*ro[i]>n&&ro[i-1]*ro[i-1]<=n)
			{
			//prllf("##%lld\n",pdpri(ro[i]));
				if(pdpri(ro[i]))
				{
					mp4[ro[i]]=1;
				}
			}
			//prllf("%lld\n",ro[i]);
			mp1[ro[i]]=i;
			if(ro[i]<=(ll)(sqrt(n)))
			{
				if(!vis[ro[i]])
				{
					mp4[ro[i]]=1;
				//cout<<ro[i]<<endl;
					FUP(j,i,cnt-1) mp2[ro[i]*ro[j]]=ro[i];
				}
			}
			
		}
		ll lst=1;
		mp3[ro[1]]=1;
		FUP(i,2,cnt)
		{
		//	prllf("%lld :%lld\n",ro[i],mp2[ro[i]]);
		//puts("11111");
			if(mp4[ro[i]])
			{
				mp3[ro[i]]=1;
				mp3[ro[i]*ro[lst]]=1;
				ll num=mp1[ro[lst]*ro[i]];
				nxt[lst]=num;
				nxt[num]=i;
				lst=i;
			}
		}
		FUP(i,1,cnt)
		{
			if(!mp3[ro[i]])
			{
				ll num=mp1[mp2[ro[i]]];
				nxt[i]=nxt[num];
				nxt[num]=i;
			}
		}
		ll now=1;
		while(now)
		{
			printf("%lld ",ro[now]);
			now=nxt[now];
		}
		printf("%lld\n0\n",n);
	}
	
    return 0;
}
```


---

## 作者：onglu (赞：0)

## E.Decryption  
### 题意  
给定一个数$n$，要求排列$n$的所有约数为一个环，然后如果相邻两个数互质就有一个贡献。  
要求贡献最少。  
### 思路  
第一步肯定是分解质因数。  
有一种构造方法，就是首先把$p_1,p_2,...,p_n$排成环，然后在每两个中间插入$p_i * p_{i - 1}$，剩下的能被$p_1$整除的数插在$p_1$后面，以此类推即可，这样的贡献都是0。  
接下来就考虑$corncase$：  
首先有单个质因子的情况，这个就直接输出所有约数就行，然后代价是$0$。  
然后只有两个质因子的情况：  
第一种是只有两个质因子且幂次为$1$也就是$p * q$的形式。这样子随意排约数就行，但是代价是$1$。  
第二种是两个质因子存在幂次不为$1$，这样的话按照上面的算法就会插入两个$p_1*p_2$显然不成立，解决方法是预先拿出一个$p_1 * p_2 * k$然后最后插在后面就可以了。  
具体实现看代码吧。  
还是有一点复杂的。  

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define Mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define ll long long
#define ull unsigned long long
#define FILL ""
using namespace std;
const int N = 1e6 + 1009, M = 0;
int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, pri[N], tot[N], dv[N], vis[N], cnt1, cnt2;
void dfs(int x,int now){
	if(x > cnt1){
		dv[++cnt2] = now;
		return ;
	}
	int t = now;
	dfs(x + 1, now);
	for(int i = 1; i <= tot[x]; i++){
		t *= pri[x];
		dfs(x + 1, t);
	}
}
void work(){
	memset(tot, 0, sizeof(tot));
	memset(vis, 0, sizeof(vis));
	n = read();cnt1 = cnt2 = 0;
	for(int i = 2; i * i <= n; i++)if(n % i == 0){
		pri[++cnt1] = i;
		while(n % i == 0){
			n /= i;
			tot[cnt1]++;
		}
	}
	if(n > 1){
		tot[++cnt1] = 1;
		pri[cnt1] = n;
	}
	dfs(1, 1);
	if(cnt1 == 2 && tot[1] == 1 && tot[2] == 1){
		printf("%lld %lld %lld\n1\n",pri[1], pri[2], pri[1] * pri[2]);
		return ;
	}
	int fin;
	pri[cnt1 + 1] = pri[1];
	tot[cnt1 + 1] = tot[1];
	if(cnt1 == 1){
		int t = pri[1];
		for(int i = 1; i <= tot[1]; i++){
			printf("%lld ",t);
			t *= pri[1];
		}
		printf("\n0\n");
		return ;
	}
//	cout<<dv[6]<<endl;
	if(cnt1 > 2)fin = pri[cnt1] * pri[1];
	else {
		for(int i = 2; i <= cnt2; i++){
//			cout<<i<<endl;
			if(dv[i] % (pri[cnt1] * pri[1]) == 0 && dv[i] / (pri[cnt1] * pri[1]) > 1){
				fin = dv[i];
				vis[i] = 1;
				break;
			}
//			cout<<i<<endl;
		}
	}
//	cout<<11111<<endl;
	for(int i = 1; i <= cnt1; i++){
		printf("%lld ",pri[i]);
		for(int j = 2; j <= cnt2; j++)if(!vis[j] && dv[j] % pri[i] == 0){
			if(dv[j] == pri[i] || dv[j] == pri[i] * pri[i + 1] || dv[j] == pri[1] * pri[cnt1]){
				vis[j] = 1;
				continue;
			}
			vis[j] = 1;
			printf("%lld ",dv[j]);
		}
		if(i != cnt1)printf("%lld ", pri[i] * pri[i + 1]);
		else printf("%lld ",fin);
	}
	printf("\n0\n");
}
main()
{
	//freopen(FILL".in", "r", stdin);
	//freopen(FILL".out", "w", stdout);
	int Case = read();
	while(Case--)work();
	return 0;
}

```

---

## 作者：feecle6418 (赞：0)

先将 $n$ 分解质因数。设为 $p_1^{k_1}p_2^{k_2}\dots$

假如 $n=p_1p_2$，那么答案一定是 1，直接输出 $p_1,p_2,n$。

否则，需要一个观察：当 $k_1>1$ 或 $k_2>1$ 时，将 $p$ 的所有因数按照下列方式排列，答案一定为 0：

- 最小质因子为 $p_1$ 的约数从小到大（不包括 $n$）。
- 最小质因子为 $p_2$ 的约数从小到大（不包括 $n$）。
- $\dots$
- $n$

证明较繁， ~~留作读者练习~~ 这里略去。

为什么 $k_1=1$ 且 $k_2=1$ 不对？因为这时最小质因子为 $p_1$ 的最大约数等于 $\dfrac{n}{p_2}$，假如 $p_2^2$ 不整除 $n$，则 $\gcd(p_2,\dfrac{n}{p_2})=1$。

先特判掉 $n=p_1p_2p_3$，因为因数个数太少。照着样例 `30` 的输出来排列即可。

否则：最小质因子为 $p_1$ 的约数中一定有两个是 $p_2$ 的倍数，把 $p_2$ 插入他们中间即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,p[10005],pk[10005];
vector<int> vec[105];
int main(){
	int t;
	cin>>t;
	while(t--){
		int tn,mxk=0;
		memset(pk,0,sizeof(pk));
		cin>>n,p[0]=0,tn=n;
		for(int i=2;i*i<=tn;i++){
			if(tn%i==0){
				p[++p[0]]=i;
				while(tn%i==0)tn/=i,mxk=max(mxk,++pk[p[0]]);
			}
		}
		if(tn>1)p[++p[0]]=tn,pk[p[0]]=1;
		if(p[0]==2&&pk[1]==1&&pk[2]==1){
			printf("%d %d %d\n%d\n",p[1],p[2],n,1);
			continue;
		}
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				for(int j=1;j<=p[0];j++){
					if(i%p[j]==0){
						vec[j].push_back(i);
						break;
					}
				}
				if(i*i!=n){
					for(int j=1;j<=p[0];j++){
						if((n/i)%p[j]==0){
							vec[j].push_back(n/i);
							break;
						}
					}
				}
			}
		}
		for(int i=1;i<=p[0];i++)sort(vec[i].begin(),vec[i].end());
		if(pk[1]>1||pk[2]>1){
			for(int i=1;i<=p[0];i++)for(int j:vec[i])cout<<j<<' ';
			printf("%d\n0\n",n);
			for(int i=1;i<=p[0];i++)vec[i].clear();
		}
		else if(p[0]==3&&mxk==1){
			printf("%d %d %d %d %d %d %d\n0\n",p[1],n,p[1]*p[2],p[2],p[2]*p[3],p[3],p[3]*p[1]);
			for(int i=1;i<=p[0];i++)vec[i].clear();
		}
		else {
			int p1=0,p2=0;
			for(int j:vec[1])if(j%p[2]==0&&!p1)p1=j;else if(j%p[2]==0&&!p2)p2=j;
			printf("%d %d %d %d ",p[1],p1,p[2],p2);
			for(int j:vec[1])if(j!=p1&&j!=p2&&j!=p[1])printf("%d ",j);
			for(int i=2;i<=p[0];i++)for(int j:vec[i])if(j!=p[2])cout<<j<<' ';
			printf("%d\n0\n",n);
			for(int i=1;i<=p[0];i++)vec[i].clear();
		}
	}
}
```

---

## 作者：pzc2004 (赞：0)

# 题目大意
给定一个正整数 $n$，将它的所有大于一的因数按照任意顺序排列在一个环上，你每次可以选择圈上相邻的两个数，在它们中间插入他们的最小公倍数，使得最后的环上不存在两个相邻且互质的数。你需要找到一个需要进行操作次数最少的排列。
# 题目分析
对于一种排列，容易发现最少需要进行的操作次数就等于该环上相邻且互质的数的对数。所以目标就是最小化相邻且互质的数的对数。  
我们先将 $n$ 分解质因数为 $p_1^{a_1}*p_2^{a_2}*...*p_m^{a_m}$。我们可以把 $n$ 的所有因数中被 $p1$ 整除的分为一组，再把剩下的中被 $p2$ 整除的分为一组，一直这样下去，在每组的边界上放能同时被两组的质因数整除的数。  
可以发现这样在 $n$ 不是两个不同的质数的乘积时结果一定是0，而在 $n$ 等于两个不同的质数的乘积时结果是1，所以一定是最优的。  
代码：
``` cpp
#include <bits/stdc++.h>
using namespace std;
template <class T>
inline void read(T &x)
{
	x= 0;
	char c= getchar();
	while(!isdigit(c)) c= getchar();
	while(isdigit(c)) x= x * 10 + (c & 15), c= getchar();
}
inline int ksm(int a, int b)//快速幂
{
	int s= 1;
	for(; b; b>>= 1, a*= a)
		if(b & 1) s*= a;
	return s;
}
inline int gcd(int a, int b)//最大公约数
{
	return b == 0 ? a : gcd(b, a % b);
}
#define N 100001
int n, zys[N], num[N], cnt, ans, b[N], tot;
vector<int> k[N];
inline void fenjie(int n)//分解质因数
{
	int m= n;
	for(int i= 2; i * i <= n; i++)
	{
		if(m % i == 0)
		{
			zys[++cnt]= i, num[cnt]= 0;
			while(m % i == 0) m/= i, ++num[cnt];
		}
	}
	if(m > 1)
	{
		zys[++cnt]= m, num[cnt]= 1;
	}
}
inline void dfs(int x, int y, int z)//x表示当前做到哪一个质因数，y表示当前的数，z表示y将要被分到哪一组
{
	if(x == cnt + 1)
	{
		if(y != 1) k[z].push_back(y);//不能有1
		return;
	}
	dfs(x + 1, y, z);
	if(z == 0) z= x;
	for(int i= 1; i <= num[x]; i++) dfs(x + 1, y * ksm(zys[x], i), z);
}
inline void calc()
{
	for(int i= 1; i < tot; i++)
		if(gcd(b[i], b[i + 1]) == 1) ++ans;
	if(gcd(b[tot], b[1]) == 1) ++ans;
}
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n), cnt= tot= ans= 0;
		fenjie(n);
		for(int i= 1; i <= cnt; i++) k[i].clear();
		dfs(1, 1, 0);
		for(int i= 1; i <= cnt; i++)
		{
			int x= -1, y= -1;//处理一下每一组的边界
			for(int j= 0; j < k[i].size(); j++)
			{
				if(k[i][j] % zys[((i + cnt - 2) % cnt + cnt) % cnt + 1] == 0)
				{
					x= k[i][j], k[i].erase(k[i].begin() + j);
					break;
				}
			}
			for(int j= 0; j < k[i].size(); j++)
			{
				if(k[i][j] % zys[i % cnt + 1] == 0)
				{
					y= k[i][j], k[i].erase(k[i].begin() + j);
					break;
				}
			}
			if(x != -1) b[++tot]= x;
			for(int j= 0; j < k[i].size(); j++) b[++tot]= k[i][j];
			if(y != -1) b[++tot]= y;
		}
		for(int i= 1; i <= tot; i++) printf("%d ", b[i]);
		calc();//计算答案
		printf("\n%d\n", ans);
	}
	return 0;
}
```

---

