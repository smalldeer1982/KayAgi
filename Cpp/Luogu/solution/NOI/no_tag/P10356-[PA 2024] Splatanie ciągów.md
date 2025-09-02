# [PA 2024] Splatanie ciągów

## 题目背景

PA 2024 3A

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 3 [Splatanie ciągów](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/spl/)，感谢 Macaronlin 提供翻译**

定义一个数组的稳定性是最长严格单调递增或递减的连续子区间的长度。如数组 $[8,6,1,3,5,7,4,2]$ 的稳定性为 $4$，因为有一个连续递增子区间 $[1,3,5,7]$，并且没有比其更长的严格单调的连续子区间了。

定义 $A\ \text{i}\ B$ 是 $A$ 和 $B$ 按某个方式归并形成的新数组（即新数组可以划分为两个不交叉子序列，且分别是 $A$ 和 $B$），如 $A=[1,2,3],B=[4,5]$，则 $A\ \text{i}\ B$ 可以是 $ [1, 4, 2, 5, 3], [4, 5, 1, 2, 3]$ 或者 $[4, 1, 5, 2, 3]$，但不可能是 $[1,2,3,4,3]$ 或 $[1,2,3,5,4]$。

令 $f(A,B)$ 表示 $A\ \text{i}\ B$ 的最小稳定性。

给你一个长度为 $n$ 的数组 $A$ 和长度为 $m$ 的数组 $B$。令 $A'$ 是 $A$ 的非空子区间，$B'$ 是 $B$ 的非空子区间。对于所有在区间 $[1,n+m]$ 的整数 $x$，求有多少对 $(A',B')$ 满足 $f(A', B')=x$。答案对 $10^9+7$ 取模。

## 说明/提示

对于整个区间 $f([1,2,5,7,4],[8,3,6])=2$，如 $[1, 8, 2, 5, 3, 7, 4, 6]$ 的稳定性为 $2$，并且无法找出更小的了。

考虑区间 $[1,2,5,7]$ 和 $[3]$，有 $f([1,2,5,7],[3])=3$，如 $[1,2,5,3,7]$。可以证明对于 $([1,2,5,7],[3])$ 没有比 $3$ 更小稳定性的组合方式了。

考虑区间 $[4]$ 和 $[6]$，有 $f([4],[6])=2$，这两个区间只有两种拼接方式：$[4,6]$ 或 $[6,4]$，并且它们的稳定性都是 $2$。

样例中所有子区间组合的稳定性都不大于 $3$，所以对于 $x\ge 4$ 的情况答案均为 $0$。

## 样例 #1

### 输入

```
5 3
1 2 5 7 4
8 3 6
```

### 输出

```
0 84 6 0 0 0 0 0
```

# 题解

## 作者：C1942huangjiaxu (赞：4)

先考虑给定 2 个**单调递增**的数组 $A,B$，怎么求 $f(A,B)$。

不妨设 $A$ 长度为 $|A|=n$，$B$ 长度为 $|B|=m$，$n\ge m$。

那么我们考虑往 $A$ 中插入 $B$，假如插入 $x$ 在 $a_i,a_{i+1}$ 之间，可以发现 $a_i\lt x $ 和 $x\lt a_{i+1}$ 至少满足 $1$ 个，假如 $2$ 个都满足，那么我们可以交换 $x$ 和 $a_i$，这样一定不劣。

所以我们可以看做用 $m$ 个数，把 $A$ 分成了 $m+1$ 段，但因为插入每个数都会满足一个递增条件，那么就是把 $n+m$ 个数分成了 $m+1$ 段，也就是说我们构造出的答案为 $\lceil \frac {n+m}{m+1}\rceil$，同时可以发现这就是**答案的下界**。

因此，有 $f(A,B)=\lceil \frac {n+m}{m+1}\rceil$。

也就是说，**对于长度为 $n$ 的单调序列，要使答案不超过 $x$，那么 $m$ 要满足 $\lceil \frac {n+m}{m+1}\rceil \le x$，解得 $m\ge \lceil \frac {n-x}{x-1}\rceil$**。

现在令 $a_i$ 表示 $A$ 中的极长单调区间的长度，例如 $A=[1,2,3,4,8,7,6,5]$，有极长单调区间 $[1,2,3,4,8]$ 和 $[8,7,6,5]$，所以 $a=[5,4]$。

$b_i$ 同理。

考虑一般情况的 $f(A,B)$，同样考虑将短的序列往长的序列里面插入，那么可以得到 $f(A,B)$ 为最小的整数 $x$，满足 $\sum \lceil \frac {a_i-x}{x-1}\rceil\le |B|,\sum \lceil \frac {b_i-x}{x-1}\rceil\le |A| $，两个不等式分别对应 $B$ 短和 $A$ 短的情况。

题目要求的是恰好，可以转变为对于每个 $i$ 求有多少 $f(A',B')\le i$。 

可以发现对于任意 $x$，两个式子至少满足一个，因此可以分开求答案，最后减去总方案数，就能得到两个式子都满足的方案数。

假如求出了 $\sum \lceil \frac {a_i-x}{x-1}\rceil=y$，那就是求 $B$ 有多少个长度大等于 $y$ 的区间，这是一个关于 $|B|=m$ 的 $2$ 次多项式。

**注意仅 $1\le y\le m$ 时满足，$y=0$ 可能要特殊处理，$y\gt m$ 要避免计算**。

先整理一下式子，**化为下取整，并用 $x$ 取代 $x-1$** 得到 $y=\sum \lfloor \frac {a_i-2}{x}\rfloor$。

要求所有子区间的答案，枚举每个 $x$，考虑到 $a_i-2\lt x$ 的 $a_i$ 是没有贡献的，也就是说对于 $x$，只有 $O(\frac n x)$ 个有用的 $a_i$。

只要能在 $\widetilde O(\frac n x)$ 的复杂度内求出答案就行了。

方法不少，但似乎都比较繁琐，这里说一下我的做法。

$a_i-2$ 相当于去掉左右端点，可以先去掉右端点，然后把极长区间长度看成 $r_i-l_i$。

然后可以先处理出以 $1$ 为左端点时，答案发生变化的右端点，然后再枚举答案发生变化的左端点，**总结就是每经过一个关键端点答案 $+1$，把除法解决掉**，用双指针维护 $\sum \lfloor \frac {r_i-l_i}{x}\rfloor\le m$ 的最右位置，然后将答案暴力展开成多项式，维护每一项的系数和。

注意到无用的 $a_i$ 相当于是一个空区间，也就是说我们每次求的是一个空区间和实区间交替的区间序列的答案，可能要分几种情况处理，但大体都是类似的。

这样每次是 $O(\frac n x)$ 的，时间复杂度 $O(n\ln n)$。

给一下参考代码吧，但细节比较多所以代码比较恶心，而且都是展开后的式子估计也看不懂，所以建议自己先写暴力然后一点点优化。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+5,P=1e9+7,i2=P+1>>1;
typedef long long ll;
typedef pair<int,int> pii;
int n,m,a[N],b[N],ans[N],s0[N],s1[N],s2[N];
ll va[N];
vector<pii>A,B;
void solve(vector<pii>&A,int x,int n,int m){
	if(A.empty()){
		ans[x]=(ans[x]+1ll*n*(n+1)/2%P*(1ll*m*(m-1)%P))%P;
		return;
	}
	vector<int>tr;
	for(auto [l,r]:A){
		int u=l+x;
		while(u<=r)tr.push_back(u-1),u+=x;
	}
	tr.push_back(n);
	for(int i=1;i<tr.size();++i){
		int w=tr[i]-tr[i-1];
		s0[i]=(s0[i-1]+w)%P;
		s1[i]=(s1[i-1]+1ll*(P-i)*w)%P;
		s2[i]=(s2[i-1]+1ll*i*i%P*w)%P;
	}
	for(int i=0,j=0;i<A.size();++i){
		int ls=1,l=A[i].first,r=A[i].second;
		if(r==n)break;
		if(i>0)ls=A[i-1].second+1;
		int u=r-x;
		vector<int>tl;
		while(u>=l)tl.push_back(x),u-=x;
		tl.push_back(u+x-ls+1);
		ls=r;
		while(tr[j]<=r)++j;
		for(int k=0;k<tl.size();++k){
			int ct=max(1,k),sum=0,o=m-k+j;
			if(ct<m)sum=(sum+1ll*(m-ct)*(m-ct+1)%P*(tr[j]-r))%P;
			int z=min(m-k+j-1,(int)tr.size()-1);
			if(z>j)sum=(sum+(1ll*o*o+o)%P*(s0[z]-s0[j]+P)+(2ll*o+1)*(s1[z]-s1[j]+P)+s2[z]-s2[j]+P)%P;
			ans[x]=(ans[x]+1ll*tl[k]*sum)%P;
			if(k==m-1)break;
		}
	}
	ll cnt=1ll*(A[0].first-1)*A[0].first/2;
	for(int i=0;i<A.size();++i){
		int l=A[i].second+1,r=n;
		if(i+1<A.size())r=A[i+1].first-1;
		if(l<=r)cnt+=1ll*(r-l+2)*(r-l+1)/2;
	}
	ans[x]=(ans[x]+cnt%P*(1ll*m*(m-1)%P))%P;
	for(auto [l,r]:A){
		va[0]=1ll*(r-l+1)*(r-l+2)/2;
		int i=1;
		while(i*x<=r-l){
			int d=r-l-i*x;
			va[i]=1ll*(d+1)*(d+2)/2;
			++i;
		}
		va[i]=0;
		for(int j=0;j<i;++j){
			cnt=va[j]-va[j+1];
			int ct=max(1,j);
			if(ct<m)ans[x]=(ans[x]+1ll*(m-ct)*(m-ct+1)%P*(cnt%P))%P;
		}
	}
	for(int i=0;i<A.size();++i){
		int ls=1,l=A[i].first,r=A[i].second;
		if(i)ls=A[i-1].second+1;
		if(ls>=l)continue;
		vector<int>tr;
		int u=l+x;
		while(u<=r)tr.push_back(x),u+=x;
		tr.push_back(r-u+x+1);
		for(int j=0;j<tr.size();++j){
			int ct=max(1,j);
			if(ct<m)ans[x]=(ans[x]+1ll*(m-ct)*(m-ct+1)%P*(l-ls)%P*tr[j])%P;
		}
	}
}
void solve(vector<pii>A,int n,int m){
	for(int i=1;i<n+m;++i){
		solve(A,i,n,m);
		ans[i]=(ans[i]+1ll*m*(m-1)%P*(n+1))%P;
		vector<pii>tmp;
		for(auto [x,y]:A)if(y-x>i)tmp.emplace_back(x,y);
		A=tmp;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=m;++i)scanf("%d",&b[i]);
	for(int i=1,j;i<n;i=j){
		j=i+1;
		if(a[j]>a[i])while(j<n&&a[j+1]>a[j])++j;
		else while(j<n&&a[j+1]<a[j])++j;
		if(j-1>i)A.emplace_back(i,j-1);
	}
	for(int i=1,j;i<m;i=j){
		j=i+1;
		if(b[j]>b[i])while(j<m&&b[j+1]>b[j])++j;
		else while(j<m&&b[j+1]<b[j])++j;
		if(j-1>i)B.emplace_back(i,j-1);
	}
	solve(A,n-1,m+1),solve(B,m-1,n+1);
	printf("0");
	ans[0]=1ll*n*(n+1)/2%P*(1ll*m*(m+1)%P)%P;
	for(int i=1;i<n+m;++i)printf(" %d",1ll*(ans[i]+P-ans[i-1])*i2%P);
	return 0;
}
```

---

## 作者：无名之雾 (赞：3)

模拟赛 T3。场上根据特殊性质的指引想了一半。确实是很好的题。

## solution

首先考虑一个特殊情况：

当 $A_i=i$ 且 $B_i=i+n$，即 $A$ 与 $B$ 都分别单调递增。

我们最终的序列一定形如 $\{a\dots ab \dots ba\dots ab \dots b\}$，即 $ab$ 交错的连续段。此时最长下降序列长度显然为 $2$，最长上升子序列应该是前缀为 $a$，后缀为 $b$ 的最长子串。

若 $n\ge m$，我们最优的构造显然是用 $b$ 去切割 $a$。考虑 $m$ 个数可以把 $A$ 切成 $m+1$ 段。除却最后一段每一段末尾都应该有一个 $b$ 去切割。然后初始从 $A$ 中抽出来一个数作为最后用来分隔的数。答案就是 $\lceil \frac{n-1}{m+1}\rceil+1=\lceil \frac{n+m}{m+1}\rceil$。$n<m$ 同理。

推广到一段长度为 $x$ 的单调连续段。向其中插入另一个序列的 $y$ 个数，则新序列的最长连续段下界就应该是 $\lceil\frac{x+y}{y+1}\rceil$。构造方法同上。

也就是说对于一个长度为 $x$ 的单调连续段，使他的最长连续区间不超过 $k$。就有 $\lceil\frac{x+y}{y+1}\rceil \le k$，$k\le \lceil\frac{x-z}{z-1}\rceil$。

然后考虑 $a_i,b_i$ 定义为 $A,B$ 序列中极长单调连续段的长度。并用 $l_1,l_2$ 表示 $A,B$ 序列的长度。

考虑将前面对于单调序列的研究推广到一般序列。我们依旧是将短的向长的里面插。对于使 $f(A,B)$ 最小的整数 $x$ 有，$\sum\lceil \frac{a_i-x}{x-1}\rceil \le l_2$ 或 $\sum\lceil \frac{b_i-x}{x-1}\rceil \le l_1$ 分别对应 $A$ 短或 $B$ 短。

为了方便化简成下取整用 $x$ 替换 $x-1$ 有式子 $\sum\lfloor \frac{a_i-2}{x}\rfloor \le l_2$ 或 $\sum\lfloor \frac{b_i-2}{x-1}\rfloor \le l_1$。

然后两种情况分开算，用所有方案减一下就是答案。

赛时也就想到了这里，直接做是 $O(n^3)$，可以在洛谷上获得 $40$ 分，但是在模拟赛里只给了 $30$ 分，[submission](https://www.luogu.com.cn/record/200315185)。

$a_i-2$ 的组合意义实际上就是段区间去掉两个端点。所以这些区间都是不交的。枚举 $x$ 发现 $a_i-2\le x$ 的段才有用。所以没被覆盖的线段分组处理，覆盖的 $x$ 个一组处理。

考虑一下贡献，其中 $L_i$ 表示 $i$ 所在段右面的权值减去 $i$ 所在段及其左面完整段的权值。$R_i$ 表示 $i$ 所在段左边及其左边完整端带来的权值。

从长为 $n$ 的序列里选长度小于 $x$ 的区间，那么方案数为 $x(n-x)+\frac{x(1+x)}{2}$，展开后是一个二次式。用 $R_r-L_l$ 替换一下。从左往右扫一遍用 $3$ 个 SGT 分别维护不同次项的贡献。特判一下同一段中的情况，调和级数枚举做就行了。

时间复杂度 $O(n \ln n \log n)$，[code](https://www.luogu.com.cn/paste/vy0qm6j4)。

---

## 作者：qiuzx (赞：3)

[PA2024 题解全集](https://www.luogu.com.cn/article/gi139pd4)

首先肯定需要用一种比较好的方式刻画 $f(a,b)$。这个有很多种求法，贪心 dp 等均可，但很多种求法都不是一个好的形式，导致没有办法去做后面的问题。我们先做一些转化以方便后面的叙述，如果我们对序列 $a$ 记一个 $01$ 序列 $c$，其中 $c_i=1$ 当且仅当 $a_i>a_{i+1}$，则 $a$ 的最长单调子段长度就是 $c$ 中的最长 $0$ 或 $1$ 连续段的长度 $+1$。下面我们在计算 $f(a,b)$ 的时候，不妨假设 $|a|\ge|b|$，然后考虑逐个将 $b$ 中的元素插入 $a$。

我们在插入的时候一定是希望能够破坏掉一个较长的 $0$ 或 $1$ 连续段。假设有连续的一些 $0$，考虑当插入的数 $b_i$ 满足什么条件的时候能够在里面插入一个 $1$。设这些 $0$ 对应到原序列中为 $a_{j-1}<a_j<a_{j+1}$，则若 $b_i>a_j$，我们有 $a_{j-1}<b_i>a_j<a_{j+1}$，若 $b_i<a_j$，我们有 $a_{j-1}<a_j>b_i<a_{j+1}$。而这两种情形都是将 $00$ 变成了 $010$。这就意味着在不考虑 $b$ 插入的相对顺序的前提下，我们可以在 $01$ 序列的任意位置插入任意字符。如果 $n>m$，所以这 $m$ 个数一定插这 $n-1$ 个空一定不会不够插，而在我们插入过的位置它与两端都不一样，所以在同一位置插入更多的数不会更优。又因为如果我们钦定了在哪些位置进行插入不管需要插入的数是什么，总是能属于上面两种情况之一，即总是存在一种方案，所以如果固定了最后的 $01$ 序列，直接从左往右插入就是一种满足相对顺序的方案。当然上面漏掉了 $n=m$ 的情况，不过容易验证 $n=m$ 的时候答案为 $2$，所以可以不管。

因此求 $f(a,b)$ 的过程可以看作先求出 $a$ 对应的 $01$ 序列，然后求在其中任意插入 $m$ 个字符得到的 $01$ 序列的最长连续段的最小值。这显然只和每个连续段的长度相关，所以假设 $c$ 的连续段长度依次为 $s_1,s_2,\cdots,s_k$，则如果我们希望这个最小值不大于 $x$，那么至少需要插入 $\displaystyle\sum_{i=1}^k\lfloor\dfrac{s_i-1}x\rfloor$ 个字符。容易说明当 $m$ 不小于这个值的时候方案是一定存在的。这个求 $f$ 的形式是很好的，所以我们可以进一步优化这个做法。

我们先将求 $f(a',b')=x$ 的个数改为求 $f(a',b')>x$ 的个数，这样最后减一下即可得到正确答案。也可以再改写一下变成 $f(a',b')-1>x$ 的个数，这样就转化为了 $01$ 序列的最大连续段长度 $>x$ 的个数。下面对这个计数。由于我们算这个值的时候大小较大的一个序列是关键的，所以不妨先对最终的 $|a'|>|b'|$ 的情况计数，再将 $a,b$ 交换一下即可得到另一种情况。下面我们假定只需要计算 $x\ge 1$ 的答案，因为 $x=0$ 时答案就是所有情况的数量，显然可以直接计算，这样可以避免讨论一些情况。注意到 $|a'|=|b'|$ 时答案为 $1$，所以只会在 $x=0$ 时计算进去，这样就不用管 $|a'|=|b'|$ 了。

考虑对 $a$ 分治，但这样如果从中间将一个连续段劈开不太方便表示这一段的限制。所以我们对 $a$ 算出的 $s$ 序列进行分治（即极长 $01$ 连续段的长度序列）。当只剩下一个 $s$ 的时候，$x$ 的答案可以被表示为 $\displaystyle\sum_{i=1}^{s}\sum_{j=i}^sw(\lfloor\dfrac{j-i}x\rfloor)$，其中 $w(x)$ 表示在 $b$ 中选择一个长度小于 $x$ 的连续段的方案数，可以 $O(1)$ 计算。这个式子可以枚举 $j-i$ 做到 $O(s^2)$，但不可以接受。注意到 $\displaystyle\sum_x\lfloor\dfrac{j-i}x\rfloor=O(s\log s)$，所以如果我们枚举 $x$ 之后去枚举 $\lfloor\dfrac{j-i}x\rfloor$，就可以做到 $O(s\log s)$ 计算，而枚举这个之后满足这个条件的 $(i,j)$ 的个数可以 $O(1)$ 计算，这样我们就解决了分治底层的计算问题。

下面考虑如何计算跨过中点的区间个数。由于我们劈开序列的地方是两个连续段的交界处，所以左右两部分对 $b$ 中选择长度限制的贡献是直接相加，这个是相对独立的。类似上面的方法，注意到 $\sum \lfloor\frac{s_i}x\rfloor$ 不超过 $\frac{r-l+1}x$，所以我们考虑对每一对 $(x,k)$，其中 $kx\le r-l+1$，计算有多少个左端点满足左边的 $\sum \lfloor\frac{s_i}x\rfloor$ 限制恰好是 $k$，右边类似。这样我们只需要算 $O((r-l)\log(r-l))$ 个值，是可以接受的。假定我们已经算好了这些值，记为 $L_{x,k}$ 和 $R_{x,k}$，则我们需要算 $\displaystyle\sum_{i}\sum_jL_{x,i}R_{x,j}w(i+j)$。注意到 $w(x)$ 是前面一段二次函数后面一段常数，所以预处理 $R_{x,j},R_{x,j}\times j,R_{x,j}\times j^2$ 这三个值的前缀和即可枚举 $i$ 之后 $O(1)$ 计算答案。所以就只剩下如何计算 $L,R$ 了。

注意到当我们在移动左端点的时候，如果从 $l$ 移动到 $l-1$，那么一个 $x$ 的限制会加上 $1$，当且仅当当前这个连续段的长度恰好是 $x$ 的倍数。这样我们在扫描的时候每次在当前连续段的所有因数 $x$ 处打一个标记，表示这个位置需要更新 $x$。这样的复杂度是 $O(r-l+cnt)$，其中 $cnt$ 是更新的次数之和。而这个更新次数显然等于所有 $x$ 的最大可能值之和，就是 $O((r-l)\log (r-l))$，因此可以接受。在得到这些标记之后，计算 $L,R$ 是容易的。这样就做完了，复杂度 $O(n\log^2n)$。

``` c++
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define mod 1000000007
#define F first
#define S second
#define ll long long
#define N 300010
using namespace std;
int n,m,a[N],b[N],liml[N],limr[N],f[N<<1],sum[N][3];
vector<int> fac[N],updl[N],updr[N];
void upd(int len)
{
	int i,j;
	for(i=1;i<=len;i++)
	{
		for(j=2;j*i+1<=len;j++)
		{
			int lim=j-1;
			if(lim>=m)
			{
				lim=(1ll*(m+1)*m/2)%mod;
			}
			else
			{
				lim=(1ll*(m+m-lim+1)*lim/2)%mod;
			}
			int l=i*j+1,r=i*j+i;
			r=min(r,len);
			l=len-l+1,r=len-r+1;
			swap(l,r);
			f[i]=(f[i]+1ll*lim*((1ll*(l+r)*(r-l+1)/2)%mod))%mod;
		}
	}
	return;
}
void solve(int l,int r)
{
	int i,j,mn=1,mx=0;
	vector<int> seq;
	for(i=l+1;i<=r;i++)
	{
		seq.push_back(a[i]>a[i-1]);
		mn=min(mn,seq.back());
		mx=max(mx,seq.back());
	}
	if(mn>=mx)
	{
		upd(seq.size());
		return;
	}
	vector<int> pts;
	for(i=l+1;i<r;i++)
	{
		if((a[i]>a[i-1])!=(a[i+1]>a[i]))
		{
			pts.push_back(i);
		}
	}
	int mid=pts[pts.size()>>1];
	solve(l,mid);
	solve(mid,r);
	int cur=0;
	for(i=1;i<=seq.size();i++)
	{
		updl[i].clear();
		updr[i].clear();
	}
	for(j=mid-1;j>=l;j--)
	{
		if(j<mid-1&&seq[j-l]==seq[j-l+1])
		{
			cur++;
		}
		else
		{
			cur=1;
		}
		for(i=0;i<fac[cur-1].size();i++)
		{
			updl[fac[cur-1][i]].push_back(j);
		}
	}
	cur=0;
	for(j=mid;j<r;j++)
	{
		if(j>mid&&seq[j-l]==seq[j-l-1])
		{
			cur++;
		}
		else
		{
			cur=1;
		}
		for(i=0;i<fac[cur-1].size();i++)
		{
			updr[fac[cur-1][i]].push_back(j);
		}
	}
	for(i=1;i<=seq.size();i++)
	{
		mx=0;
		for(j=0;j*i<=seq.size();j++)
		{
			liml[j]=limr[j]=0;
			mx=j;
		}
		int lst=mid-1;
		for(j=0;j<updl[i].size();j++)
		{
			liml[j]=lst-updl[i][j];
			lst=updl[i][j];
		}
		liml[j]=lst-l+1;
		lst=mid;
		for(j=0;j<updr[i].size();j++)
		{
			limr[j]=updr[i][j]-lst;
			lst=updr[i][j];
		}
		limr[j]=r-lst;
		sum[0][0]=limr[0],sum[0][1]=0,sum[0][2]=0;
		for(j=1;j<=mx;j++)
		{
			sum[j][0]=(sum[j-1][0]+limr[j])%mod;
			sum[j][1]=(sum[j-1][1]+1ll*limr[j]*j)%mod;
			sum[j][2]=(sum[j-1][2]+1ll*limr[j]*j*j)%mod;
		}
		for(j=0;j*i<=seq.size();j++)
		{
			if(!liml[j])
			{
				continue;
			}
			int lo=max(0,m-j+1);
			if(lo<=mx)
			{
				int coef=(sum[mx][0]+mod-(lo==0?0:sum[lo-1][0]))%mod;
				coef=(1ll*coef*liml[j])%mod;
				coef=(1ll*coef*((1ll*(m+1)*m/2)%mod))%mod;
				f[i]=(f[i]+coef)%mod;
			}
			if(m-j>=0)
			{
				lo=min(m-j,mx);
				int A=m+m+1-j+1,B=(mod+j-1)%mod;
				int coef=(sum[lo][0]+mod-(j==0?sum[0][0]:0))%mod;
				coef=(1ll*coef*((1ll*A*B)%mod))%mod;
				coef=(coef+1ll*(A+mod-B)*(sum[lo][1]+mod-(j==0?sum[0][1]:0)))%mod;
				coef=(coef-sum[lo][2]+(j==0?sum[0][2]:0))%mod;
				coef=(coef+mod)%mod;
				coef=(1ll*coef*liml[j])%mod;
				coef=(1ll*coef*(mod+1)/2)%mod;
				f[i]=(f[i]+coef)%mod;
			}
		}
	}
	return;
}
int main(){
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<m;i++)
	{
		scanf("%d",&b[i]);
	}
	for(i=1;i<=max(n,m);i++)
	{
		for(j=i;j<=max(n,m);j+=i)
		{
			fac[j].push_back(i);
		}
	}
	solve(0,n-1);
	swap(n,m);
	swap(a,b);
	solve(0,n-1);
	f[0]=(1ll*((1ll*n*(n+1)/2)%mod)*((1ll*m*(m+1)/2)%mod))%mod;
	printf("0 ");
	for(i=0;i<n+m-1;i++)
	{
		printf("%d ",(f[i]+mod-f[i+1])%mod);
	}
	puts("");
	return 0;
}
```

---

## 作者：云浅知处 (赞：2)

模拟塞搬了这个题，写 3h 代码通过了大样例，[结果 FST 荣获 $1$ 分](https://qoj.ac/submission/415922)，操吴戈兮披犀甲

考虑两个单调的序列，长度分别是 $x,y$，他们合并起来的最小的 $f$ 怎么算。

发现合并之后会得到一个长度为 $x+y$ 的序列，同时会分成 $y+1$ 段，而且显然新插入的数要么可以放到左边的段内，要么可以放到右边的段内，于是下界是 $\lceil(x+y)/(y+1)\rceil$。

我们发现下界一定是可以取到的。钦定 $x$ 的划分，以及划分点分到左边还是右边，直接顺次填入，如果出现了 $x_i<y_j<x_{i+1}$ 这样导致两个段合并的，发现总可以把 $j$ 向前提一位或者向后放一位从而分隔开。那么这样交换会不会相交呢，发现需要这一段长度为 $1$，而且两边都向另一侧钦定，发现这个时候一定不如直接向 $len=1$ 的这一侧钦定。于是答案就是 $\lceil(x+y)/(y+1)\rceil$。

接下来考虑一般情况，把 $A,B$ 分段，如果答案想要为 $x$，那么需要两边分的段数都够用。设左边的段长构成序列 $a$，右边是 $b$，考虑 $\lceil(a_i+y)/(y+1)\rceil\le x$，即 $(a_i+y)/(y+1)\le x$，可以算出
$$
a_i+y\le xy+x\iff a_i-x\le (x-1)y\\\iff y\ge \left\lceil\frac{a_i-x}{x-1}\right\rceil=\left\lfloor\frac{a_i-2}{x-1}\right\rfloor
$$
于是只需要 $\sum \lfloor (a_i-2)/(x-1)\rfloor \le |B|$。另一边也一样。

注意到两边只有一个会卡满约束。考虑对一个 $x$ 算有多少区间符合条件，用总数减掉两边分别卡掉的即可。考虑怎么算卡掉的，发现相当于取若干整段和两个散段。

枚举左端点 $l$ 所在整段，对于 $l,r$ 同段的形式，此时算出的 $\lfloor (r-l+1)/(x-1)\rfloor\le \lfloor n/(x-1)\rfloor$， 枚举结果容易算出方案数，进而计算贡献；对于 $l,r$ 不同段的，我们可以从分段点处分开，那么贡献为 $l$ 处的散段贡献与 $r$ 左边的若干整段和一个散段贡献之和，也就是要算
$$
\sum_{l,r}g(w_l+v_r)
$$
其中 $w_l$ 表示 $l$ 到这一段右端点的贡献，$v_r$ 表示 $r$ 左边的若干整段和一个散段的贡献之和，$g(k)$ 表示 $B$ 中选一个长度 $\le k$ 的区间的方案数，这个是一个前面二次函数后面平着的形式。

这个形式不完全是二次函数，直接维护一次项和二次项可能会算错后面的部分（也是我场上 FST 的原因）。

注意到 $w_l$ 不超过这一段的段长除以 $x-1$，我们考虑枚举 $w_l$ 的值，算出 $\sum_r g(w_l+v_r)$，这样复杂度也就是调和级数。双指针维护最大的 $p$ 满足第一个 $w_l+v_r\ge m$ 的 $r$ 在这一段内，然后可以算出具体的分段点在哪里。

那么对 $p$ 前面段内的 $r$ 我们需要维护 $\sum v_r,v_r^2$，后面段内的 $r$ 直接维护个数即可，这一段的一个前缀的 $\sum v_r,v_r^2$ 有一个等差数列求和以及等差数列平方和的形式，可以 $O(1)$ 算出。

综上，总复杂度 $O(n\ln n)$。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,ll y,int p=mod){
	int ans=1;y%=(p-1);
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
mt19937 rnd(time(0));
int randint(int l,int r){return rnd()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}
int cmod(int x){if(x>=mod)x-=mod;return x;}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=3e5+5;
int a[N],b[N],n,m;

const int Iv6=inv(6);
const int Iv2=inv(2);

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.out","w",stdout);
#endif

	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();

	vector<int>ca(n+1),cb(m+1);
	for(int i=1;i<=n;i++)ca[i]=n-i+1;
	for(int i=1;i<=m;i++)cb[i]=m-i+1;
	for(int i=1;i<=n;i++)add(ca[i],ca[i-1]);
	for(int i=1;i<=m;i++)add(cb[i],cb[i-1]);

	vector<int>ans(n+m+1);
	for(int k=2;k<=n+m;k++)ans[k]=1ll*((1ll*n*(n+1)/2)%mod)*((1ll*m*(m+1)/2)%mod)%mod;

	auto calc=[&](){
		vector<pair<int,int> >As;
		vector<vector<pair<int,int> > >vec(n+1);

		int p=1;	
		while(p<=n-1){
			int q=p+1;
			while(q<=n-1&&(a[q+1]>a[q])==(a[p+1]>a[p]))q++;
			As.emplace_back(mk(p,q)),p=q;
		}
		for(int i=1;i<=n;i++)vec[i].emplace_back(mk(0,1));
		for(auto [l,r]:As){
			for(int j=1;j<=r-l;j++)vec[j].emplace_back(mk(l,r));
		}

		auto getSum=[&](int L,int R){
			return 1ll*(L+R)*(R-L+1)%mod*Iv2%mod;
		};
		auto Sum=[&](int L,int R){
			return 1ll*(L+R)*(R-L+1)%mod*Iv2%mod;
		};
		auto getv_1=[&](int L,int x){ // sum i = 0...L floor(i/x)
			int ans=0,p=(int)(L/x);
			add(ans,1ll*Iv2*(p-1)%mod*p%mod*x%mod);
			add(ans,1ll*p*(L%x+1)%mod);
			return ans;
		};
		auto getv_2=[&](int L,int x){ // sum i = 0...L floor(i/x)*(L-i+1)
			int ans=0;
			for(int i=1;i*x<=L;i++){
				int l=i*x,r=min(L,(i+1)*x-1);
				add(ans,1ll*min(i,m+1)*Sum(L-r+1,L-l+1)%mod);
			}
			return ans;
		};
		auto getv_3=[&](int L,int x){ // sum i = 0...L floor(i/x)^2
			int ans=0,p=(int)(L/x);
			add(ans,1ll*Iv6*p%mod*(p-1)%mod*(p+p-1)%mod*x%mod);
			add(ans,1ll*p*p%mod*(L%x+1)%mod);
			return ans;
		};
		auto getv_4=[&](int L,int x){ // sum i = 0...L floor(i/x)^2 * (L-i+1)
			int ans=0;
			for(int i=1;i*x<=L;i++){
				int l=i*x,r=min(L,(i+1)*x-1);
				add(ans,1ll*min(i,m+1)*min(i,m+1)%mod*Sum(L-r+1,L-l+1)%mod);
			}
			return ans;
		};

		vector<int>mis(n+m+1);
		for(int k=2;k<=n;k++){
			int pre=n,sum0=0,sum1=0,sum2=0,rr1=0,rr2=0,rr0=1;
			int ms=0;

			auto A=vec[k];

			vector<pair<int,int> >B;
			for(int i=0;i<A.size();i++){
				#define l fi
				#define r se
				B.emplace_back(A[i]);
				int p=A[i].r;
				int nx=(i==((int)(A.size())-1)?n:A[i+1].l);
				while(p<nx){
					int q=min(nx,p+k-1);
					B.emplace_back(mk(p,q)),p=q;
				}
				#undef l
				#undef r
			}
			A=B;

			int nowsum=0,p=(int)(A.size())-1;
			for(int i=A.size()-1;i>=0;i--){
				#define l fi
				#define r se

				int len=max(0,A[i].r-A[i].l-1);
				if(len>=2){
					add(sum1,getv_2(max(len-2,0),k-1));
					add(sum2,getv_4(max(len-2,0),k-1));
				}
				add(sum0,getSum(max(len-k+1,0),len));

				for(int j=0;j*(k-1)<=A[i].r-A[i].l;j++){
					int cl=j*(k-1)+2,cr=min((j+1)*(k-1)+1,A[i].r-A[i].l);
					int cnt_l=cr-cl+1;if(j==0)cnt_l++;

					if(cnt_l<=0)break;

					while(p>=i+1&&nowsum+j>m+1){
						nowsum-=(A[p].r-A[p].l-1)/(k-1);
						int lle=A[p].r-A[p].l;
						add(rr1,mod-1ll*lle*nowsum%mod);
						int v1=0,v2=0;
						if(lle>=2)v1=getv_1(lle-2,k-1),v2=getv_3(lle-2,k-1);
						add(rr1,mod-v1);

						add(rr2,mod-1ll*nowsum*nowsum%mod*lle%mod);
						add(rr2,mod-2ll*nowsum*v1%mod);
						add(rr2,mod-v2);
						p--;
					}

					add(sum1,1ll*j*cnt_l%mod*(A[p].r-A[i].r)%mod);
					add(sum1,1ll*rr1*cnt_l%mod);

					add(sum2,1ll*j*j%mod*cnt_l%mod*(A[p].r-A[i].r)%mod);
					add(sum2,2ll*j*rr1%mod*cnt_l%mod);
					add(sum2,1ll*rr2*cnt_l%mod);

					int nowv=nowsum+j;
					if(nowv>=m+1){
						add(sum1,1ll*(m+1)*(n-A[p].r+1)%mod*cnt_l%mod);
						add(sum2,1ll*(m+1)*(m+1)%mod*(n-A[p].r+1)%mod*cnt_l%mod);
						continue;
					}
					int lft=m+1-nowsum-j;assert(lft>=0);

					int rle=1;
					if(p+1<A.size())rle=A[p+1].r-A[p+1].l+1;
					int rt=min(1ll*(lft+1)*(k-1)-1,1ll*max(0,rle-2));

					int rv1=getv_1(rt,k-1),rv2=getv_3(rt,k-1);

					int cnt_r=min(1ll*(lft+1)*(k-1)+1,(ll)(rle));
					add(sum1,1ll*(j+nowsum)*cnt_r%mod*cnt_l%mod);
					add(sum1,1ll*cnt_l*rv1%mod);

					add(sum2,1ll*(j+nowsum)*(j+nowsum)%mod*cnt_r%mod*cnt_l%mod);
					add(sum2,2ll*(j+nowsum)*rv1%mod*cnt_l%mod);
					add(sum2,1ll*rv2*cnt_l%mod);

					add(sum1,1ll*(m+1)*(n-A[p].r+1-cnt_r)%mod*cnt_l%mod);
					add(sum2,1ll*(m+1)*(m+1)%mod*(n-A[p].r+1-cnt_r)%mod*cnt_l%mod);
				}

				int llen=max(0,A[i].r-A[i].l-2);
				int vl=getv_1(llen,k-1);
				int vvl=getv_3(llen,k-1);

				add(sum0,1ll*min(k,A[i].r-A[i].l)*rr0%mod);

				add(rr2,vvl);
				add(rr2,2ll*(len/(k-1))*rr1%mod);
				add(rr2,1ll*(len/(k-1))*(len/(k-1))%mod*(A[p].r-A[i].r)%mod);
				
				add(rr1,getv_1(llen,k-1));
				add(rr1,1ll*(len/(k-1))*(A[p].r-A[i].r)%mod);

				if(A[i].r-A[i].l+1>=k+1)rr0=0;
				rr0+=min(k,A[i].r-A[i].l);

				pre=A[i].l;
				nowsum+=(int)(A[i].r-A[i].l-1)/(k-1);

				#undef l
				#undef r
			}
			
			ms=1ll*((1ll*(m+m+3)*sum1-1ll*sum2-1ll*(m+m+2)*n%mod*(n+1)%mod*Iv2)%mod+mod)*Iv2%mod;
			add(ms,1ll*sum0*(m+1)%mod);
			mis[k]=ms;
			if(k>=3&&mis[k]==0&&mis[k-1]==0)break;

			add(ans[k],mod-ms);
		}
	};

	calc();
	swap(n,m),swap(a,b);
	calc();

	for(int i=n+m;i>=1;i--)add(ans[i],mod-ans[i-1]);
	for(int i=1;i<=n+m;i++)cout<<ans[i]<<" \n"[i==n+m];

	return 0;
}
```

---

