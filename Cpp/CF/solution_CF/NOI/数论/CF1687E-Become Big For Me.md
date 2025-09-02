# Become Big For Me

## 题目描述

> 『来吧，让我们构筑起一个不会遗弃弱者的乐园吧！』——少名针妙丸&鬼人正邪，《东方辉针城》

针妙丸有一个万宝槌，可以将物体变大或者变小。她现在在对一个序列 $a$ 测试这一功能。具体而言，她有一个实数 $v=1$，她希望在不超过 $10^5$ 次操作后，将 $v$ 变为 $\gcd \limits_{i \neq j} \{a_i \times a_j\}$。其中，$\gcd \limits_{i \neq j} \{a_i \times a_j\}$ 指的是，序列 $a$ 中两个不同元素相乘得到的所有乘积的最大公约数。

在每一次操作中，针妙丸可以选择序列 $a$ 中的一个子序列 $b$，并且对其做如下两种操作中的一个：

- 放大：令 $v \leftarrow v \times \operatorname{lcm(b)}$；
- 缩小：令 $v \leftarrow \dfrac{v}{\operatorname{lcm(b)}}$。

其中，$\operatorname{lcm(b)}$ 指的是序列 $b$ 中所有元素的最小公倍数。此外，她不要求 $v$ 一定是个整数，也就是说执行缩小操作的时候，$v$ 可以不是 $\operatorname{lcm(b)}$ 的倍数。

更进一步地说，针妙丸希望她选取的所有子序列 $b$ 的长度不超过 $10^6$，即 $\sum |b| \leq 10^6$。请你为她找到一种操作方案。注意，您无需最小化任何东西。

## 样例 #1

### 输入

```
3
6 10 15```

### 输出

```
1
0 3 1 2 3```

## 样例 #2

### 输入

```
4
2 4 8 16```

### 输出

```
2
0 1 4
1 1 1```

# 题解

## 作者：zhoukangyang (赞：18)

学文化课回来的第一场 vp。

最后十五分钟把 E 写出来了，然后家里网络差，调试没删，题目里有 $i_p < i_{p+1}$ 这种奇怪限制，没过。在比赛结束前用洛谷交上去过了，但是在 vp 里不算。

## 题解

首先一个集合 $S$ 的 $\rm gcd$ 可以用 $\min-\max$ 反演转化为 $\operatorname{lcm}$，这样就可以做到 $2^{|S|}-1$ 次操作表示 $\gcd$ 了。

注意到一个数只有不超过 $8$ 种质因子，所以从 $S$ 中随便选一个数 $x$，对于 $x$ 的每种质因子找包含这个质因子次数最少的元素加进来，即可用不超过 $9$ 个元素表示整个集合的 $\gcd$。

结论：原问题的答案是 $(\gcd_{i} a_i)^2 \prod_{i} \frac{\gcd_{j \neq i} a_j}{\gcd_{j} a_j}$（对于每个质因数考虑一下就可以发现其正确性）

$\frac{\gcd_{j \neq i} a_j}{\gcd_{j} a_j} \neq 1$ 的 $i$ 只有不超过 $8$ 个（证明和上面比较类似，不再赘述），所以对于非 $1$ 的 $i$ 暴力即可。

[代码](https://codeforces.com/contest/1687/submission/161356722)。比 std 更好写，复杂度也更好，在出题人的数据中最多只用了 $2164$ 次操作（显然每次操作不会用超过 $9$ 个元素）。

时间复杂度也好得多，是 $\Theta(n \log A + \omega(A)(n\omega(A)+ \sqrt{A}))$（这个 $\sqrt{A}$ 是质因数分解的，可以做到 $A^{\frac{1}{4}}$ 因此 $A$ 甚至可以 $10^{18}$）。

---

## 作者：whiteqwq (赞：18)

[CF1687E Become Big For Me](https://www.luogu.com.cn/problem/CF1687E)

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/16343401.html)

## 题意

你有一个变量 $v$ 初始值为 $1$，你还有一个集合 $A$，每次可以选择 $A$ 的一个子集并让 $v$ 乘或除这个集合的 $\text{lcm}$，你要使得最后 $v$ 的值变为：

$$\gcd_{i\ne j}\{A_i\times A_j\}$$

$2\leqslant |A|\leqslant 10^5,A_i\leqslant 10^6$，操作总数不能超过 $10^5$，操作集合大小之和不能超过 $10^6$。

## 分析

这道题是我听物理课时偶然想到的，挺喜欢这个 idea，就把它投到了 [CF](https://codeforces.com/contest/1687) 上，感觉区分度还可以。

竟然被评为了 \*3500，受宠若惊。

感谢 [SSerxhs](https://www.luogu.com.cn/user/29826) 神仙对做法的完善/bx/bx/bx！

考虑将 $\gcd_{i\ne j}\{A_i\times A_j\}$ 转化一下，其可以表示为所有质因子最小和次小（非严格）幂次的乘积。

类似 $\gcd-\text{lcm}$ 反演，我们对其施加广义 $\min-\max$ 容斥，可得：

$$\gcd_{i\ne j}\{A_i\times A_j\}=\prod_{T\subseteq U}\text{lcm}(T)^{(-1)^{|T|}(|T|-2)}$$

于是我们得到了一个 $O(2^nn)$ 次操作的解法。

一个经典结论是对于任意值域 $[1,10^6]$ 的集合 $S$，其都存在一个大小为 $7$ 的子集使得 $\gcd$ 等于 $\gcd(S)$。（$V$ 为值域）

构造则可以任选一个数，将其最小幂次对应的数加入集合，再检查这个数能否去除即可，正确性见 [CF](https://codeforces.com/blog/entry/103493)。

选择一个答案不变的集合，只需要依据上述方法选出一个 $\gcd$ 不变的集合，将其去除之后再选一遍即可，这样集合大小不会超过 $14$，对这个集合施用上面的算法即可通过。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,maxv=1000005,maxp=80005;
int n,ps,mnv,stp,ans;
int a[maxn],p[maxp],c[maxv],mn[maxv],id[maxv],zero[maxn],vis[maxp],ok[maxn],flg[maxn],mnexp[maxp],recmn[maxp];
vector<int>S;
set<int>s;
map<int,int>use;
void sieve(int n){
	c[1]=1;
	for(int i=2;i<=n;i++){
		if(c[i]==0)
			p[++ps]=i,id[i]=ps,mn[i]=i,s.insert(ps),mnexp[ps]=1000,zero[ps]=-1;
		for(int j=1;j<=ps&&i*p[j]<=n;j++){
			c[i*p[j]]=1,mn[i*p[j]]=p[j];
			if(i%p[j]==0)
				break;
		}
	}
}
inline void chk(int x,int id,int c){
	if(c<mnexp[x])
		mnexp[x]=c,recmn[x]=id;
}
void solve(){
	for(int i=1;i<=n;i++)
		if(ok[i]==0){
			int v=a[i];
			stp++;
			while(v>1){
				int p=mn[v],c=0;
				while(v%p==0)
					v/=p,c++;
				vis[id[p]]=stp,chk(id[p],i,c);
			}
			set<int>::iterator it=s.begin();
			while(it!=s.end()){
				if(vis[*it]==stp)
					it++;
				else zero[*it]=i,s.erase(it++);
			}
		}
	for(int i=1;i<=ps;i++)
		if(zero[i]!=-1)
			chk(i,zero[i],0);
	int st=1;
	while(ok[st])
		st++;
	int v=a[st],chs=0;
	while(v>1){
		int p=mn[v],c=0;
		while(v%p==0)
			v/=p,c++;
		if(mnexp[id[p]]!=c){
			if(ok[recmn[id[p]]]==0)
				chs++;
			ok[recmn[id[p]]]=1;
		}
	}
	if(chs<7)
		ok[st]=1;
}
long long gcd(long long a,long long b){
	return b==0? a:gcd(b,a%b);
}
int main(){
	sieve(1000000),scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	solve();
	s.clear();
	for(int i=1;i<=ps;i++)
		s.insert(i),mnexp[i]=1000,recmn[i]=0,zero[i]=-1;
	solve();
	for(int i=1;i<=n;i++)
		if(ok[i])
			S.push_back(i);
	long long g=0;
	for(int i=0;i<S.size();i++)
		for(int j=i+1;j<S.size();j++)
			g=gcd(g,1ll*a[S[i]]*a[S[j]]);
	if(g==1){
		puts("0");
		return 0;
	}
	for(int i=1;i<(1<<S.size());i++){
		int mul=__builtin_parity(i)==1? 1:-1;
		ans+=(abs(mul+(-mul)*(__builtin_popcount(i)-1)));
	}
	printf("%d\n",ans);
	int tot=0;
	for(int i=1;i<(1<<S.size());i++){
		int mul=__builtin_parity(i)==1? 1:-1,cnt=__builtin_popcount(i);
		int v=mul+(-mul)*(cnt-1),V=abs(v);
		for(int j=1;j<=V;j++){
			printf("%d %d ",v==V? 0:1,cnt);
			tot+=(v==V? 0:1,cnt);
			for(int j=0;j<S.size();j++)
				if((i>>j)&1)
					printf("%d ",S[j]);
			puts("");
		}
	}
	return 0;
}
```

## 彩蛋
![](https://cdn.luogu.com.cn/upload/image_hosting/0mknb0gz.png)


---

## 作者：周子衡 (赞：6)

为行文方便，下面以 $V=10^6$ 表示题中 $a_i$ 的最大范围。

我们先来看看怎么快速计算答案。考虑确定答案中每个质因子的次数，根据 $\mathrm{gcd}$ 的性质可知，对某个质数 $p$，答案中 $p$ 的次数即为 $a_1\sim a_n$ 含 $p$ 次数中最小的两个之和。那么，如果某个 $p$ 整除答案，那么 $p$ 必须整除 $a_1\sim a_n$ 中至少 $n-1$ 个数。我们可以找到 $a_1,a_2$ 的所有质因子，然后扫描整个数组，计算这些质因子在答案中的次数，从而求出答案。

如何构造题目中需要的方案呢？可以发现，$\gcd$ 与 $\operatorname{lcm}$ 的关系正如 $\min$ 与 $\max$ 的关系一般；我们用子序列 $\operatorname{lcm}$ 的乘除构造 $\gcd$，实际上就是用子集的 $\max$ 的加减构造子集的 $\min$。可以联想到下面的定理：

---------------------

**定理（min-max 容斥）** 设 $S$ 是某个实数可重集合，记 $c_i(1\leq i\leq |S|)$ 表示 $S$ 所有大小为 $i$ 的子集的最大值的和。则对 $1\leq k\leq |S|$ 有

$$
{\min}_ k\{S\}=\sum_{j=k}^{|S|}(-1)^{j-k}\binom{j-1}{k-1}c_j
$$

其中 ${\min}_ k\{S\}$ 为 $S$ 中第 $k$ 小的元素。

本题只需要用到 $k=1,2$ 时的形式：

$$
\min\{S\}=c_1-c_2+c_3-c_4+\cdots
$$

$$
{\min}_2\{S\}=c_2-2c_3+3c_4-4c_5+\cdots
$$

证明可以通过考虑 $S$ 中每个元素在左右分别出现的次数来完成。网上有很多此定理的证明，我们这里略去。

---------------------

$n$ 很小时，我们可以依照上面的定理来枚举 $\{1,2,3,...,n\}$ 的全部非空子集。验证一下可以发现，这个做法对 $n\leq 14$ 都是可取的。

对于更一般的情况，我们需要另辟蹊径。我们发现，许多元素都是“无用”的，将它们从原序列中删去并不会影响答案。

---------------------

**核心观察** 当 $n > 14$ 时，一定可以从序列里删掉一个元素使得答案不变。

**证明** 反证法，假设删掉任意一个元素都会使得答案改变。那么对于序列中任意一个元素 $x$，一定存在某个质数 $p$，使得 $x$ 在整个序列中含 $p$ 的次数是升序中的严格前二（也就是严格小于第三名），我们称 $p$ 保护了 $x$ 免被删去。可以发现一个质数至多保护两个数免被删去，由于 $n\geq 15$，那么至少有 $8$ 个质数 $p_1,...,p_8$ 保护了序列中至少一个数免被删去。而如果一个质数保护了序列里某个数免被删去，它一定整除序列里至少 $n-2$ 个数。那么有 $(p_1p_2\cdots p_8)^{n-2}\leq V^n$。而最小的 $8$ 个质数为 $2,3,5,7,11,13,17,19$，在计算器上摁一下可以知道上面的不等号是不可能成立的。故假设自相矛盾，原命题正确。

-------------------

很好！我们已经十分接近正解了。一个暴力的想法是，我们直接从原序列开始，当 $n > 14$ 时枚举每个元素是否可以被删去。这个做法较难用数据结构优化。不过，我们有一个非常优美的做法。

设原序列答案为 $\mathrm{ans}$。我们维护一个序列 $S$，对 $\mathrm{ans}$ 的每个质因子 $p$，我们都取原序列中 $p$ 幂次最低的两项加入 $S$ 中。现在 $S$ 的答案一定是 $\mathrm{ans}$ 乘上某些和 $\mathrm{ans}$ 互质的质数，我们需要把这些多出来的质因子消掉。解决方法也很简单：对每个多出来的质因子，从还没选的元素里选不是该质因子倍数的数加入 $S$ 中。可以发现这样构造出来的 $S$ 非常小。（实际上这样构出来的 $S$ 最多只有 $15$ 个元素，为了读者的身心健康我们这里略去证明。）再暴力枚举删除哪个元素即可。

下面的代码里，`dv` 数组预处理每个 $[1,V]$ 的数所含的质因子，`VAL` 维护答案的所有质因子，`P` 维护了 $S$。写得稍微有点乱，还请见谅。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> dv[2000000];
vector<int> P,VAL;
bool in_P[200000],in_val[2000000];

bool is_prm[2000000];int prm_lst[2000000],pcnt;

int pw[200000],pos[2];

int cntbit[1<<16];

void init(int n)
{
	for(int i=2;i<=n;i++)is_prm[i]=1;
	for(int i=2;i<=n;i++)
	{
		if(is_prm[i]){prm_lst[++pcnt]=i,dv[i].push_back(i);}
		for(int j=1;prm_lst[j]*i<=n;j++)
		{
			int u=prm_lst[j];is_prm[u*i]=0;
			dv[u*i]=dv[i];
			if(i%u==0)
			{
				break;
			}
			dv[u*i].push_back(u);
		}
	}
}

long long gcd(long long x,long long y){return y?gcd(y,x%y):x;}

int a[200000];
long long calc_ans(vector<int> P)
{
	long long ret=0;for(int i=0;i<P.size();i++)for(int j=i+1;j<P.size();j++)ret=gcd(ret,(long long)a[P[i]]*a[P[j]]);
	return ret;
}


int main()
{
	init(1000000);
	int n=0;scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	if(n<=14)
	{
		for(int i=1;i<=n;i++)P.push_back(i);
	}
	else
	{
		for(int i=0;i<dv[a[1]].size();i++)
		{
			int p=dv[a[1]][i];int cnt=0;
			for(int j=1;j<=n;j++)if(a[i]%p==0)cnt++;
			if(cnt>=n-1)VAL.push_back(p),in_val[p]=1;
		}
		for(int i=0;i<dv[a[2]].size();i++)
		{
			int p=dv[a[2]][i];int cnt=0;
			for(int j=1;j<=n;j++)if(a[i]%p==0)cnt++;
			if(cnt>=n-1)VAL.push_back(p),in_val[p]=1;
		}
		
		sort(VAL.begin(),VAL.end());VAL.erase(unique(VAL.begin(),VAL.end()),VAL.end());
		pw[0]=100;
		for(int i=0;i<VAL.size();i++)
		{
			pos[0]=pos[1]=0;
			for(int j=1;j<=n;j++)
			{
				int x=a[j];pw[j]=0;while(x%VAL[i]==0){x/=VAL[i],pw[j]++;}
				if(pw[j]<pw[pos[0]]){pos[1]=pos[0];pos[0]=j;}
				else if(pw[j]<pw[pos[1]])pos[1]=j;
			}
			P.push_back(pos[0]),P.push_back(pos[1]);in_P[pos[0]]=in_P[pos[1]]=1;
		}
		sort(P.begin(),P.end());P.erase(unique(P.begin(),P.end()),P.end());
		
		for(int i=2;i<=1000000;i++)
		{
			if(!is_prm[i])continue;
			if(in_val[i])continue;
			int cnt=P.size();
			for(int j=0;j<P.size();j++)if(a[P[j]]%i==0)cnt--;
			while(cnt<2)
			{
				for(int j=1;j<=n;j++)
				{
					if(!in_P[j]&&a[j]%i!=0)
					{
						in_P[j]=1,P.push_back(j);break;
					}
				}
				cnt++;
			}
			sort(P.begin(),P.end());P.erase(unique(P.begin(),P.end()),P.end());
			
		}
		while(P.size()>14)
		{
			for(int j=0;j<P.size();j++)
			{
				vector<int> Q;for(int k=0;k<P.size();k++)if(k!=j)Q.push_back(P[k]);
				if(calc_ans(P)==calc_ans(Q)){P=Q;break;}
			}
		}
	}
	
	vector<pair<int,int> > ans;
	int m=P.size();
	for(int i=1;i<(1<<m);i++)cntbit[i]=cntbit[i>>1]+(i&1);
	
	for(int i=1;i<(1<<m);i++)
	{
		int x=0;if(cntbit[i]&1)x=2-cntbit[i];else x=cntbit[i]-2;
		if(x>=0){for(int j=1;j<=x;j++)ans.push_back(make_pair(0,i));}
		else{for(int j=-1;j>=x;j--)ans.push_back(make_pair(1,i));}
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
	{
		printf("%d ",ans[i].first);int u=ans[i].second;
		printf("%d ",cntbit[u]);
		for(int j=0;j<m;j++)if(u&(1<<j)){printf("%d ",P[j]);}
		puts("");
	}
}
```

**后记**

感觉是个很奇怪的题，很难评判这题算不算是好题。

---

## 作者：Scintilla (赞：5)

令 $v_p(n)$ 表示最大的 $k$，满足 $p^k \mid n$。

对于所有质因子 $p$，设 $v_p(a_i)$ 中最小值和次小值为 $x_p, y_p$，则我们的目标值就是 $\prod_p p^{x_p + y_p}$。

~~根据提示，~~ 我们考虑扩展 $\min - \max$ 容斥

$$ \min_k(S) = \sum\limits_{T \subseteq S} (-1) ^ {|T| - k} \binom{|T| - 1}{k - 1} \max(T) $$

我们可以类似得到

$$ \gcd_k(S) = \sum\limits_{T \subseteq S} \text{lcm}(T) ^ {(-1) ^ {|T| - k} \binom{|T| - 1}{k - 1}} $$

所以

$$ \begin{aligned}
  \prod\limits_p p^{x_p + y_p} & = \gcd(a) \times \gcd_2(a) \\
  & = \sum\limits_{T \subseteq S} \text{lcm}(T) ^ {(-1) ^ {|T| - 1}} \times \text{lcm}(T) ^ {(-1) ^ {|T|} (|T| - 1)} \\
  & = \sum\limits_{T \subseteq S} \text{lcm}(T) ^ {(-1) ^ {|T|} (|T| - 2)} \\
\end{aligned} $$

但是这个做法的操作方案还是指数级别的。这个式子已经没有什么优化的空间了，我们不妨换个方向，尝试寻找目标值与原序列相等的长度能承受指数复杂度的序列。

不难发现，我们可以进行两次「找到一个和当前序列 $\rm gcd$ 相同的短子序列，然后把子序列从序列中丢掉」的操作，那么两次丢掉的数就能构成我们要找的序列了。事实上，因为 $2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 \times 19 > 10^6$，可以证明每次丢掉的序列长度最小值不超过 $7$，所以我们构造的序列长度不超过 $14$，这是可以接受的。 

那么怎么找出一个 $\gcd$ 与当前序列相等，并且长度 $\le 7$ 的子序列呢？考虑随机化。首先对序列去重，然后对于数 $u$，如果序列中存在 $v$ 使得 $v < u, v \mid u$，那么我们就忽略 $u$，在剩下的数里面一直随 $7$ 个，直到随到合法的情况。

这样看上去很对，写出来也跑得挺快，正确性我不会证，欢迎大哥来叉。

还有题解的做法：设选出的子序列为 $S$。任选一个数 $x = \prod_i p_i^{k_i}$，把 $x$ 加入 $S$，并对于所有 $i$，把 $v_{p_i}(a_i)$ 最小的数 $y$ 加入 $S$，然后若 $|S| = 8$ 则去掉 $x$，正确性不难证明。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define drep(i, s, e) for (int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define pv(a) cout << #a << " = " << a << endl
#define pa(a, l, r) cout << #a " : "; rep(_, l, r) cout << a[_] << ' '; cout << endl
 
const int N = 1e5 + 10;
const int W = 1e6;
const int L = 20;
const int K = 7;
 
int read() {
  int x = 0, f = 1; char c = getchar();
  for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
  for (; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - 48;
  return x * f;
}
 
mt19937 rnd(time(0));
 
int Rand(int l, int r) {
  return l + rnd() % (r - l + 1);
}
 
#define dig(x, i) ((x) >> (i) & 1)
#define pc(x) __builtin_popcount(x)
 
int p[W + 10], tot; bool tag[W + 10];
void sieve(int w) {
  rep(i, 2, w) {
    if (!tag[i]) p[++ tot] = i;
    for (int j = 1; j <= tot && i * p[j] <= w; ++ j) {
      tag[i * p[j]] = true;
      if (!(i % p[j])) break;
    }
  }
}
 
int C[L][L];
void init(int w) {
  rep(i, 0, w) C[i][0] = 1;
  rep(i, 1, w) {
    rep(j, 1, i) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
  }
}
 
int n, m, a[N], b[N], c[N], pw[N], id[N];
bool mask[N], pax[W + 10];
 
int check(int l, int r) {
  int res = 0;
  rep(i, l, r) res = __gcd(res, a[id[i]]);
  return res;
}
 
void filt() {
  int len = 0, cnt = 0, g = 0;
  rep(i, 1, n) if (!mask[i]) id[++ len] = i, g = __gcd(g, a[i]);
  if (!len) return;
  sort(id + 1, id + len + 1, [](int i, int j) { return a[i] < a[j]; });
  rep(i, 1, len) {
    int u = id[i];
    if (pax[a[u]]) continue;
    for (int j = a[u]; j <= W; j += a[u]) pax[j] = true;
    id[++ cnt] = u;
  }
  bool flag = false;
  int lim = min(cnt, K);
  while (!flag) {
    random_shuffle(id + 1, id + cnt + 1);
    rep(i, 0, cnt - lim) {
      if (check(i + 1, i + lim) == g) {
        rep(j, 1, lim) c[++ m] = id[i + j], mask[id[i + j]] = true;
        flag = true; break;
      }
    }
  }
  rep(i, 1, W) pax[i] = false;
  return;
}
 
void work() {
  sort(c + 1, c + m + 1);
  int lim = 1 << m, cnt = 0;
  rep(i, 1, m) cnt += C[m][i] * abs(i - 2);
  printf("%d\n", cnt);
  for (int s = 1; s < lim; ++ s) {
    int cnt = pc(s), t = (cnt & 1 ? -1 : 1) * (cnt - 2), op = 0;
    if (t < 0) op = 1, t = -t;
    while (t --) {
      printf("%d %d ", op, cnt);
      rep(i, 1, m) if (dig(s, i - 1)) printf("%d ", c[i]);
      printf("\n");
    }
  }
}
 
int main() {
  srand(time(0));
  n = read(), sieve(W), init(15);
  rep(i, 1, n) a[i] = read(), id[i] = i;
  filt(), filt();
  work();
  return 0;
}
```

---

## 作者：Kubic (赞：2)

一道很搞笑的 Div1E *3500，感觉实际难度称不上这个位置和评分。

可能是我的做法与 std 不同导致的？

upd: 被 hack 了，原因是有一些地方不小心写错了，改了一下又过了。那个 hack 应该是对着我代码造的，竟然真有人看我这毒瘤码风？？？另外，做法大概率是没有问题的。这也间接体现了数据有多难造（

题目中给了一个 $\gcd\limits_{i\neq j}\{a_ia_j\}$，我们先把它变换一下。实际上就是对于每一个质数取在 $a$ 中幂次的最小值和次小值之和。

而题目要求我们用子集 $\operatorname{lcm}$ 凑出这个数，很自然可以想到 Min-Max 容斥：

$$\operatorname{kthmin}(S)=\sum_{T\subseteq S,|T|\ge k}(-1)^{|T|-k}\dbinom{|T|-1}{k-1}\max(T)$$

其中 $\operatorname{kthmin}(S)$ 表示 $S$ 中的第 $k$ 小值，$\max(S)$ 表示 $S$ 中的最大值。注意这里 $S$ 和 $T$ 都是可重集。

根据上面的式子可以得到：

$$\gcd\limits_{i\neq j}\{a_ia_j\}=\prod_{i\in S}i\prod_{T\subseteq S,|T|\ge 2}(-1)^{|T|-2}(|T|-2)\operatorname{lcm}(T)$$

这样做的操作次数是指数级的，$n=10^5$ 显然太大了。我们又很难从合并同类项上面找到突破口。

此时一个很自然的想法就是减小 $n$，即选出较少的数使得它们的 $\gcd\limits_{i\neq j}\{a_ia_j\}$ 与原序列相同。而通过简单的计算可以得到我们只能选出不超过 $14$ 个数。

实际上这是可以做到的。

一个基本的构造思路是先选出两个数 $x_1,x_2$，考虑它们的质因子集合 $S_1,S_2$。

- 对于 $S_1\cap S_2$ 的部分，我们需要选出这些质数的最小值和次小值。

- 对于 $S_1\cup S_2-S_1\cap S_2$ 的部分，此时 $x_1,x_2$ 中已经有一个数在这个位置贡献了一个 $0$，我们只需要选出次小值即可。

- 对于剩余的部分，$x_1,x_2$ 已经贡献了两个 $0$，不需要额外选择。

按照这个过程直接做会先选择 $x_1,x_2$，然后再选择至多 $w(x_1)+w(x_2)$ 个数。其中 $w(x)$ 表示 $x$ 的不同质因子个数，当 $x\le 10^6$ 时 $w(x)\le 7$。稍微构造一下数据可以把这个做法卡到 $16$ 个数，无法通过。

但实际上在大部分情况下我们都可以使得 $x_1,x_2$ 被包含在后面的 $w(x_1)+w(x_2)$ 中。对于所有质数在 $a$ 中幂次的最小值和次小值，如果至少有两个位置不为 $0$，我们可以钦定 $x_1,x_2$ 分别为这两个位置所对应的数。稍加分析便可以发现这种选法可以满足要求。

现在我们只需要解决只有不超过一个位置不为 $0$ 的情况。

如果所有位置都为 $0$，那么直接输出 $0$ 即可。否则我们可以发现至少存在一个 $a_i$ 满足 $w(a_i)\le 6$。

我们钦定 $x_1$ 为那个不为 $0$ 的位置所对应的数。如果 $w(x_1)\le 6$，那么随便找另一个数钦定为 $x_2$ 即可，否则就找到一个满足 $w(a_i)\le 6$ 的 $a_i$，然后钦定 $x_2=a_i$ 即可。

这样讨论之后，我们就把选出的数的个数控制在 $14$ 个以内，然后再利用上面的式子即可通过。时间复杂度并不是很重要，只要不太离谱基本随便怎么写都可以。

这题的难点可能就是细节比较多容易写挂吧。。。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000005
#define pb push_back
const int INF=1e9;
int n,a[N],w[N],p[N],vs[N],mn1[N],mn2[N],ps1[N],ps2[N];
int x1,x2,ans,cnt[N],st[N];bool fl,vs1[N];vector<int> vc[N];
void sieve(int n)
{
	for(int i=2;i<=n;++i)
	{
		if(!vs[i]) p[vs[i]=++p[0]]=i;
		for(int j=1;i*p[j]<=n;++j)
		{vs[i*p[j]]=j;if(!(i%p[j])) break;}
	}
}
void ins(int x,int y,int w,bool fl=1)
{
	if(w<mn1[x]) mn2[x]=mn1[x],ps2[x]=ps1[x],mn1[x]=w,ps1[x]=y;
	else if(w<mn2[x]) mn2[x]=w,ps2[x]=y;if(fl) vc[x].pb(y);
}
int main()
{
	scanf("%d",&n);sieve(1e6);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=p[0];++i) mn1[i]=mn2[i]=INF;
	for(int i=1,lst=0,nw=0;i<=n;++i,lst=nw=0)
	{
		for(int j=a[i];j>1;j/=p[vs[j]])
		{if(vs[j]!=lst) ins(lst,i,nw),lst=vs[j],nw=0,++w[i];++nw;}
		ins(lst,i,nw);
	}
	for(int i=1;i<=p[0];++i) for(int j=1,t=0;j<=n;++j)
	{
		while(t<vc[i].size() && vc[i][t]<j) ++t;
		if(t==vc[i].size() || j!=vc[i][t]) ins(i,j,0,0);
		if(!mn2[i]) break;
	}
	for(int i=1;i<=p[0];++i)
	{
		if(mn1[i]) {x1=ps1[i];x2=ps2[i];break;}else if(mn2[i])
		{if(x1 && x1!=ps2[i]) {x2=ps2[i];break;}else x1=ps2[i];}
	}if(!x1) {printf("0\n");return 0;}
	if(!x2)
	{
		if(w[x1]<7) {for(int i=1;i<=n;++i) if(i!=x1) {x2=i;break;}}
		else for(int i=1;i<=n;++i) if(w[i]<7) {x2=i;break;}
	}vs1[x1]=vs1[x2]=1;
	for(int i=a[x1],lst=0;i>1;i/=p[vs[i]])
		if(vs[i]!=lst) ++cnt[vs[i]],lst=vs[i];
	for(int i=a[x2],lst=0;i>1;i/=p[vs[i]])
		if(vs[i]!=lst) ++cnt[vs[i]],lst=vs[i];
	for(int i=1;i<=p[0];++i)
	{
		if(cnt[i]>1) {vs1[ps1[i]]=vs1[ps2[i]]=1;continue;}
		if(cnt[i])
		{
			if(mn2[i]) vs1[ps2[i]]=1;
			else vs1[ps2[i]==x1 || ps2[i]==x2?ps1[i]:ps2[i]]=1;
		}
	}for(int i=1;i<=n;++i) if(vs1[i]) st[++st[0]]=i;
	for(int i=1,t;i<1<<st[0];++i)
	{t=__builtin_popcount(i);if(t>2) ans+=t-2;}ans+=st[0];
	printf("%d\n",ans);
	for(int i=1,t;i<1<<st[0];++i)
	{
		t=__builtin_popcount(i);
		for(int j=1;j<t-1;++j)
		{
			printf("%d %d ",t&1,t);
			for(int k=1;k<=st[0];++k) if(i>>k-1&1)
				printf("%d ",st[k]);putchar('\n');
		}
	}for(int i=1;i<=st[0];++i) printf("%d %d %d\n",0,1,st[i]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/1687/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1687E)

一道特别 nb 的题。

首先，题目要求的是 GCD，而我们拿得出手的是 LCM，这能给我们什么联想呢？**Min-Max 容斥**。考虑 Min-Max 容斥的扩展版本：$\text{kth}(S)=\sum\limits_{T\subseteq S}(-1)^{|T|-k}\dbinom{|T|-1}{k-1}\max(T)$，其中 $\text{kth}(S)$ 表示 $S$ 中第 $k$ 小的值。而题目所求本质上是对每个质因子求**最小值与次小值之和**，因此套用 Min-Max 容斥可以得到 $\min(S)+\text{secmin}(S)=\sum\limits_{T\subseteq S}((-1)^{|T|-1}+(|T|-1)(-1)^{|T|-2})\max(T)$，化简一下可以得到 $\sum\limits_{T\subseteq S}(|T|-2)(-1)^{|T|}\max(T)$。也就是说一种暴力的构造方法是，枚举所有集合 $T$，做 $(|T|-2)·(-1)^{|T|}$ 次 enlarge 操作（$a(a<0)$ 次 enlarge 操作等价于 $-a$ 次 reduce 操作），这样 $\sum |b|$ 是 $2^nn^2$ 的，最多只能处理 $n=14$，非常逊，因此我们需要优化它。

注意到 $\max\limits_{n\le 10^6}\omega(n)=7$，刚好是 $14$ 的一半，并且根据某经典结论，对于任意值域为 $10^6$ 的集合，总存在大小 $\le 8$ 的子集满足原集合的 GCD 等于该子集的 GCD，因此我们考虑借鉴该结论进行构造。先考虑《经典结论》的证法：随机选择一个数加入子集，枚举该数的所有质因子，再将集合中所有数中，该质因子出现次数最小的数加入集合，由于最多只有 $7$ 个质因子，因此最多新增 $7$ 个元素，集合大小也就进而 $\le 8$。

这样一来构造方式就明显多了。由于这里我们要求最小值和次小值，因此我们不妨先随机选择两个数 $x,y$ 加入集合，然后枚举 $x,y$ 的质因子：

- 如果该质因子是 $x,y$ 的公共质因子，那么我们就另选两个数，使得这个质因子出现次数刚好是最小值和次小值，并加入集合。
- 如果该质因子不是 $x,y$ 的公共质因子，也即，恰好能被 $x,y$ 之一整除，那么说明其最小出现次数为 $0$，只需另插入次小值即可。

这样最多插入 $7\times 2=14$ 个数，加上最初的两个，是 $16$ 个，好像还是不太行的亚子呢。因此需要继续优化，也就是说我们要选择合适的 $x,y$ 使得新加入的元素不超过 $12$ 个，怎么选呢？我们发现，如果一个质因子在集合中最小出现次数不为 $0$，那么我们就令 $x,y$ 为使该质因子出现次数达到最小值和次小值的数即可，这样遍历到该质因子时就不必另外添加其他数，最多就只有 $12$ 个。否则意味着存在一个数不是 $2$ 的倍数，也存在一个数不是 $3$ 的倍数，如果存在一个数同时满足这两个条件，我们就选择这个数作为 $x$，$y$ 可以随便选，否则就钦定这两个数为 $x,y$ 即可。

萌新好像还是第一次见到用 Min-Max 容斥构造的题呢，大佬不喜勿喷（

```cpp
const int MAXN = 1e5;
const int MAXV = 1e6;
int n, a[MAXN + 5];
int pr[MAXV / 5 + 5], prcnt = 0, vis[MAXV + 5], mnp[MAXV + 5];
void sieve(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pr[++prcnt] = i, mnp[i] = i;
		for (int j = 1; j <= prcnt && pr[j] * i <= n; j++) {
			vis[pr[j] * i] = 1; mnp[pr[j] * i] = pr[j];
			if (i % pr[j] == 0) break;
		}
	}
}
vector<pii> calc(int v) { // (质因子，出现次数） 
	vector<pii> res;
	while (v ^ 1) {
		int p = mnp[v], cnt = 0;
		while (v % p == 0) v /= p, cnt++;
		res.pb(mp(p, cnt));
	}
	return res;
}
bool in[MAXN + 5];
vector<int> occ[MAXV + 5];
pii c[MAXV + 5];
void calc_c() {
	for (int i = 1; i <= n; i++) {
		vector<pii> vec = calc(a[i]);
//		for (pii p : vec) printf("(%d, %d) ", p.fi, p.se);
//		printf("\n");
		for (pii p : vec) occ[p.fi].pb(p.se);
	}
	for (int i = 2; i <= MAXV; i++) if (!vis[i]) {
		if (occ[i].size() <= n - 2) c[i] = mp(0, 0);
		else if (occ[i].size() == n - 1) {
			c[i].se = 0; c[i].fi = 1e9;
			for (int x : occ[i]) chkmin(c[i].fi, x);
		} else {
			c[i].fi = c[i].se = 1e9;
			for (int x : occ[i]) {
				if (x < c[i].fi) c[i].se = c[i].fi, c[i].fi = x;
				else if (x < c[i].se) c[i].se = x;
			}
		}
	}
}
int getcnt(int v, int p) {
	int cnt = 0;
	while (v % p == 0) v /= p, cnt++;
	return cnt;
}
void work(int x, int y) {
	vector<pii> v1 = calc(a[x]), v2 = calc(a[y]);
	in[x] = in[y] = 1;
	for (pii p : v1) {
		if (a[y] % p.fi == 0) {
			vector<pii> vec;
			for (int i = 1; i <= n; i++)
				vec.pb(mp(getcnt(a[i], p.fi), i));
			sort(vec.begin(), vec.end());
			in[vec[0].se] = in[vec[1].se] = 1;
		}
	}
	if (n > 2) {
		for (pii p : v1) {
			if (a[y] % p.fi) {
				vector<pii> vec;
				for (int i = 1; i <= n; i++) if (i != x && i != y)
					vec.pb(mp(getcnt(a[i], p.fi), i));
				sort(vec.begin(), vec.end()); in[vec[0].se] = 1;
			}
		}
		for (pii p : v2) {
			if (a[x] % p.fi) {
				vector<pii> vec;
				for (int i = 1; i <= n; i++) if (i != x && i != y)
					vec.pb(mp(getcnt(a[i], p.fi), i));
				sort(vec.begin(), vec.end()); in[vec[0].se] = 1;
			}
		}
	}
}
void gen_smaller_set() {
	for (int i = 1; i <= MAXV; i++) if (c[i].fi && c[i].se) {
		vector<pii> vec;
		for (int j = 1; j <= n; j++)
			vec.pb(mp(getcnt(a[j], i), j)); 
		sort(vec.begin(), vec.end());
		work(vec[0].se, vec[1].se); return;
	}
	bool flg = 1;
	for (int i = 1; i <= MAXV; i++) flg &= (c[i].fi == 0 && c[i].se == 0);
	if (flg) puts("0"), exit(0);
	for (int i = 1; i <= n; i++) if (a[i] % 2) {
		if (a[i] % 3) {work(i, (i == 1) ? 2 : 1); return;}
		else {
			for (int j = 1; j <= n; j++) if (a[j] % 3) {
				work(i, j); return;
			}
		}
	}
}
int main() {
	scanf("%d", &n); sieve(MAXV);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	calc_c(); gen_smaller_set();
	vector<int> vec;
	vector<pair<int, vector<int> > > res;
	for (int i = 1; i <= n; i++) if (in[i]) vec.pb(i);
	for (int i = 1; i < (1 << vec.size()); i++) {
		int coef = ((__builtin_popcount(i) & 1) ? (-1) : 1) * (__builtin_popcount(i) - 2);
		vector<int> vecc;
		for (int j = 0; j < vec.size(); j++) if (i >> j & 1) vecc.pb(vec[j]);
		for (int j = 1; j <= abs(coef); j++) res.pb(mp(coef < 0, vecc));
	}
	printf("%d\n", res.size());
	for (int i = 0; i < res.size(); i++) {
		printf("%d %d", res[i].fi, res[i].se.size());
		for (int x : res[i].se) printf(" %d", x);
		printf("\n");
	}
	return 0;
}
```



---

## 作者：liyixin0514 (赞：0)

# [CF1687E Become Big For Me](https://www.luogu.com.cn/problem/CF1687E)

[更好的阅读体验](https://www.cnblogs.com/wingheart/p/18720598)

## 题意

给你长度为 $n$ 的序列 $\{a_i\}$。初始你有一个实数 $v=1$。你可以进行至多 $10^5$ 次操作后，把 $v$ 变成 $\gcd\{a_i \times a_j\}$。操作可以是两种中任意一种：

你可以选择任意序列 $a$ 的非空子集 $\{b\}$。

- $v \gets v \times \text{lcm}\{b\}$
- $v \gets \frac{v}{ \text{lcm}\{b\}}$

要求 $\sum |b| \le 10^6$。

$n \le 10^5, a_i \le 10^6$

## 思路

参考 zky 的做法。

显然可以改为考虑质因数的指数。实数 $v$ 也可以质因数分解，只是可能有负数指数。

$10^6$ 以内最多只有 $7$ 种质因数。

两个操作分别是指数相加或者相减。

$\gcd\{a_i \times a_j\}$ 就是每个质因数的指数是该质因数在整个序列所有数的最小指数加次小指数。

考虑把最小质数加次小指数刻画地更好一些，然后采用 min-max 容斥，变成若干 $\text{lcm}$ 相乘除。

$$\gcd \{S\} = \prod_{T \subseteq S} \text{lcm}\{T\}^{(-1)^{|T|-1}}$$

因为我们的操作只能乘除 $\text{lcm}$，所以要把问题刻画成只有 $\gcd,\text{lcm}$ 的乘除法。

最小指数显然可以乘上 $\gcd\{a_i\}$。

求次小指数，我们就是要找扔掉最小指数之后的 $\gcd$。

次小指数可以表示成 $\gcd\{a_i\} \times \prod_i \frac{\gcd_{i \neq j} \{a_j\}}{\gcd\{a_j\}}$。

如果 $a_i$ 是最小值，后面那里就会变成次小值除以最小值，所以前面还要乘回一个最小值。否则后面那里就是 $1$。

所以原问题刻画成 $(\gcd\{a_i\})^2 \prod_i \frac{\gcd_{i \neq j }\{a_j\}}{\gcd\{a_j\}}$。

对 $a_i$ 进行质因数分解。因为前面的 $\gcd$ 只有最多 $8$ 个数字有用（每个数字只有 $7$ 种质因子，即最多有 $7$ 个指数与 $\gcd$ 不同，所以最多选择 $8$ 个数即可），反演后就是 $2^8$ 次操作。

后面那里我们也只要有最小值的地方。也是最多只有 $8$ 个 $i$ 有用。然后每次计算除掉 $i$ 的 $\gcd$ 时，也只有最多 $8$ 个数字有用。所以是 $8 \times 2^8$ 次操作。

复杂度 $O(n\log n + n \omega(\sqrt{a}) + \sqrt{a})$。$\omega(a)$ 表示 $a$ 以内的质因子个数。这里把预处理质因子认为是 $\sqrt{a}$。实际上我写的埃氏筛，反正不是复杂度瓶颈。特判一下 $> \sqrt{a}$ 的质因子。

精细实现应该可以砍掉 $n \log n$，但是这又不是复杂度瓶颈。所以没有必要。

---

## 作者：wwwwwza (赞：0)

好题，这种 trick 第一次见。

根据 min-max 反演 

$$
\min\limits_{k}(S)=\sum\limits_{T\subseteq S} (-1)^{\left | T \right | -k} \binom{\left | T \right | -1}{k-1} \max(T)
$$ 
可以推出 gcd-lcm 反演 

$$\gcd\limits_{i \ne j}\{a_i\times a_j\}=\prod\limits_{T\subseteq S}\operatorname{lcm}(T)^{(-1)^{\left | T \right |}(\left | T \right |-2)}
$$

就得到了一个 $O(2^n n)$ 次操作的解法。

一个经典结论，在值域 $[1,10^6]$ 的集合 $S$，都存在一个大小为 $7$ 的子集的 $\gcd=\gcd(S)$ 。

与答案相同的子集的构造方式就是先拿出一个长度为 $7$ 的子集，再在剩余的原集合找 $7$ 个出来，答案集合大小不会超过 $14$。

找合法子集用的是[Scintilla](https://www.luogu.com.cn/user/126582)的随机化方法。

将集合打散，对于一个数如果有其因数已经被加入就忽略这个数。就这样找 $7$ 个数直到合法（好像还挺快的）。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,a[N],b[N],id[N],tot=0,ans=0;
bool vis[N],flag[N];
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
int check(int l,int r){
	int res=0;
	for(int i=l;i<=r;i++)res=gcd(res,b[id[i]]);
	return res;
}
void solve(){
	int len=0,cnt=0,g=0;
	for(int i=1;i<=n;i++)if(!flag[i])id[++len]=i,g=gcd(g,b[i]);
	if(!len)return;
	sort(id+1,id+1+len,[](int i,int j){return b[i]<b[j];});	
	for(int i=1;i<=len;i++){
		int u=id[i];
		if(vis[b[u]])continue;
		for(int j=b[u];j<=N-5;j+=b[u])vis[j]=1;
		id[++cnt]=u;
	}
	int ok=0,lim=min(cnt,7);
	while(!ok){
		random_shuffle(id+1,id+cnt+1);
		for(int i=0;i<=cnt-lim;i++){
			if(check(i+1,i+lim)==g){
				for(int j=1;j<=lim;j++)a[tot++]=id[i+j],flag[id[i+j]]=1;
				ok=1;break;
			}
		}
	}
	memset(vis,0,sizeof(vis));
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >>n;
	for(int i=1;i<=n;i++)cin >>b[i],id[i]=i;
	solve(),solve();
	sort(a,a+tot);
	for(int i=1;i<(1<<tot);i++){
		int res=0;
		for(int j=0;j<tot;j++)if((i>>j)&1)res++;
		ans+=abs(res-2);
	}
	cout <<ans<<"\n";
	for(int i=1;i<(1<<tot);i++){
		int res=0,cnt=0;
		for(int j=0;j<tot;j++)if((i>>j)&1)res++;
		cnt=res;
		res=((res&1)?-1:1)*(res-2);
		if(res==0)continue;
		for(int j=1;j<=abs(res);j++){
			if(res>0)cout <<0<<" ";
			else cout <<1<<" ";
			cout <<cnt<<" ";
			for(int k=0;k<tot;k++)if((i>>k)&1)cout <<a[k]<<" ";
			cout <<"\n";
		}
	}
	return 0;
}
```

---

## 作者：littlez_meow (赞：0)

[题目指路](https://codeforces.com/problemset/problem/1687/E)。

### 题意

给定一个长为 $n$ 的序列 $a$，你有一个初始为 $1$ 的数 $v$。你每次可以选择 $a$ 的一个子序列 $b$，让 $v$ 乘或除以 $b$ 的 $\operatorname{lcm}$。构造一种方案使得 $v=\gcd\limits_{1\le i<j\le n}\{a_ia_j\}$，要求所有操作 $b$ 的长度和不超过 $10^6$，操作数不超过 $10^5$。

### 思路

用 $\operatorname{lcm}$ 来表示 $\gcd$，想 $\min-\max$ 容斥。

题目里要求的那个非常抽象的 $\gcd$，仔细想想，会发现对于每一个质因子，都是最小次幂和次小次幂的乘积。

这启发我们使用广义 $\min-\max$ 容斥来表达这个东西。

我们可以得到最小幂次质因子的乘积为：

$$\prod\limits_{T\subseteq S}\operatorname{lcm}(S)^{(-1)^{|T|-1}}$$

同理，次小质因子乘积为：

$$\prod\limits_{T\subseteq S}\operatorname{lcm}(S)^{(-1)^{|T|-2}\binom{|T|-1}{1}}$$

记 $S=\{a_1,a_2,\cdots,a_n\}$，所以：

$$\gcd\limits_{1\le i<j\le n}\{a_ia_j\}=\prod\limits_{T\subseteq S}\operatorname{lcm}(S)^{(-1)^{|T|}(|T|-2)}$$

但是现在表示题目要求的数需要 $O(2^n\operatorname{Poly}(n))$ 次操作，只能做到 $n\le14$。

我们需要缩短 $a$ 序列。

发现值域 $[1,10^6]$ 以内，每个数最多有 $7$ 个本质不同质因数。这告诉我们，可以找到一个长为 $7$ 的 $a$ 的子序列使其和 $a$ 的 $\gcd$ 是一样的，在 $a$ 中删掉它，再找一个满足同样条件的子序列。把这两个序列拼在一起，得到的长为 $14$ 的序列和 $a$ 等效。套用上面的容斥即可。

问题转化为怎么求一个这样的子序列。

首先对于 $a$ 中一对元素 $u,v$，如果 $u|v$，那么 $v$ 不会对 $\gcd$ 造成任何贡献，可以直接忽略。剩下的元素不会太多，直接随机化，随机重排选前 $7$ 个，不会太慢。

时间复杂度能过。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
using namespace std;
const int MAXN=1e5+1,MAXV=1e6+1;
mt19937 gen(*new int^time(0));
int n,a[MAXN],mx;
int na[MAXN],nn;
bool del[MAXN],times[MAXV];
inline void compress(){
	int agcd=0,m=0,cnt=0;
	static int id[MAXN],tmp[MAXN];
	auto check=[&](int l,int r){
		int qwq=0;
		F(i,l,r){
			qwq=__gcd(qwq,a[tmp[i]]);
			if(qwq==1) return agcd==1;
		}
		return qwq==agcd;
	};
	F(i,1,n) if(!del[i]) id[++m]=i;
	memset(times,0,sizeof(bool)*(1+mx));
	sort(id+1,id+m+1,[&](int x,int y){return a[x]<a[y];});
	F(i,1,m) if(!times[a[id[i]]]){
		agcd=__gcd(agcd,a[id[i]]);
		for(int j(a[id[i]]);j<=mx;j+=a[id[i]]) times[j]=1;
		tmp[++cnt]=id[i];
	}
	m=min(cnt,7);
	while(m>0){
		shuffle(tmp+1,tmp+cnt+1,gen);
		F(i,1,n-m+1) if(check(i,i+m-1)){
			F(j,i,i+m-1) del[na[++nn]=tmp[j]]=1;
			return;
		}
	}
	return;
}
int k=0;
bool type[MAXN];
vector<int>b[MAXN];
inline void getans(){
	int m=(1<<nn)-1;
	F(i,1,m){
		int cnt=__builtin_popcount(i);
		cnt=(cnt&1)?2-cnt:cnt-2;
		if(cnt==0) continue;
		if(cnt<0){
			F(j,cnt,-1){
				type[++k]=1;
				F(t,0,nn-1) if((i>>t)&1) b[k].push_back(na[t+1]);
			}
		}else{
			F(j,1,cnt){
				type[++k]=0;
				F(t,0,nn-1) if((i>>t)&1) b[k].push_back(na[t+1]);
			}
		}
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	F(i,1,n) cin>>a[i],mx=max(mx,a[i]);
	compress();
	compress();
	getans();
	cout<<k<<"\n";
	F(i,1,k){
		sort(b[i].begin(),b[i].end());
		cout<<type[i]<<" "<<b[i].size()<<" ";
		for(int j:b[i]) cout<<j<<" ";
		cout<<"\n";
	}
	return 0;
} 
```

---

## 作者：elbissoPtImaerD (赞：0)

题目名称很理智！

stO zak Orz.

一个基本的观察是要将 $\gcd - \operatorname{lcm}$ 考虑成次数的 $\min - \max$。  
用 $\min - \max$ 反演，直到，对于一个集合 $S$，我们只需 $2^{|S|}-1$ 次操作即可表示 $\gcd$。

考虑将序列 $a$ 变短。

尝试从 $a$ 中随便取一个 $x$，再并上 $a$ 的所有质因子的最小次数对应的数字组成的集合 $S$。  
有 $\gcd\limits_{x\in S} x = \gcd\limits_{x\in a} x$。

由于 $\gcd\limits_{i\neq j} a_ia_j = \gcd\limits_ia_i^2 \prod\limits_i \frac{\gcd\limits_{i\neq j}a_j}{\gcd\limits_{j}a_j}$，所以我们只需额外考虑后面那个 $\prod$。

这很容易，因为 $\frac{\gcd\limits_{i\neq j}a_j}{\gcd\limits_{j}a_j}>1$ 的 $i$ 不会超过 $\max\limits_n \omega(n) = 9$ 个，我们对这 $9$ 个 $i$ 的分母暴力拼凑即可。

毛估估一下，次数很充足，复杂度能过。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1687/submission/246802535)

---

