# [CEOI 2021] Diversity

## 题目背景

译自 CEOI2021 Day1 T1. [Diversity](https://hsin.hr/ceoi/competition/ceoi2021_day1_tasks.pdf)。  


## 题目描述

定义一个序列的 _多样性_ 为其不同的元素个数，一个序列的 _总多样性_ 为其所有子区间的 _多样性_ 的和。

例如，序列 $(1,1,2)$ 的 _多样性_ 为 $2$ ，因为其有两种元素；它的 _总多样性_ 为序列 $(1),(1),(2),(1,1),(1,2),(1,1,2)$ 的 _多样性_ 之和，即 $1+1+1+1+2+2=8$。

给出长为 $N$ 的序列 $\{a _i\}$ 与 $Q$ 个**互相独立**的询问，每个询问给出 $[l,r]$。求将原序列 $[l,r]$ 内的数重排可以得到的该区间最小的 _总多样性_。

## 说明/提示

#### 样例解释

对于第一组样例，无论怎样重排，询问区间的 _总多样性_ 总是 $10$。

对于第二组样例，序列所有元素都为 $1$，故无需重排。区间 $[1,2]$ 的 _总多样性_ 为 $3$，区间 $[2,4]$ 的 _总多样性_ 为 $6$。

对于第三组样例，第一个询问可将序列重排为 $(1,2,2,3)$，它的 _总多样性_ 为 $1+1+1+1+2+1+2+2+2+3=16$；第二个询问可将序列重排为 $(1,1,2)$，它的 _总多样性_ 为 $1+1+1+1+2+2=8$；第三个询问可将序列重排为 $(1,3)$，它的 _总多样性_ 为 $1+1+2=4$。

#### 子任务

所有测试点均满足 $1\leq N\leq 3\times 10^5$，$1\leq a_i\leq 3\times 10^5$，$1\leq Q\leq 5\times 10^4$。

各子任务的约束条件如下：
| 子任务编号 | 分值 |                             约束                             |
| :--------: | :--: | :----------------------------------------------------------: |
|    $1$     | $4$  | $1\leq N\leq 11$，$1\leq a_i\leq 3\times 10^5$，$Q=1$，$l_1=1$，$r_1=N$  |
|    $2$     | $10$ | $1\leq N\leq 3\times 10^5$，$1\leq a_i\leq 11$，$Q=1$，$l_1=1$，$r_1=N$  |
|    $3$     | $8$  | $1\leq N\leq 3\times 10^5$，$1\leq a_i\leq 23$，$Q=1$，$l_1=1$，$r_1=N$  |
|    $4$     | $16$ | $1\leq N\leq 3\times 10^5$，$1\leq a_i\leq 1000$，$Q=1$，$l_1=1$，$r_1=N$ |
|    $5$     | $26$ | $1\leq N\leq 3\times 10^5$，$1\leq a_i\leq 3\times 10^5$，$Q=1$，$l_1=1$，$r_1=N$ |
|    $6$     | $36$ | $1\leq N\leq 3\times 10^5$，$1\leq a_i\leq 3\times 10^5$，$1\leq Q\leq 5\times 10^4$ |

## 样例 #1

### 输入

```
3 1
1 2 3
1 3```

### 输出

```
10```

## 样例 #2

### 输入

```
4 2
1 1 1 1
1 2
2 4```

### 输出

```
3
6```

## 样例 #3

### 输入

```
5 3
1 2 1 3 2
2 5
1 3
3 4```

### 输出

```
16
8
4```

# 题解

## 作者：ForgotMe (赞：6)

发现这个总多样性很丑陋，我们用柿子来表示。

可以发现一种元素 $i$ 产生的贡献为

$$
\dfrac{n\times (n+1)}{2}-\sum_{j=1}^{cnt_i}\dfrac{f_{i,j}(f_{i,j}+1)}{2}
$$

$cnt_i$ 表示元素 $i$ 之间产生了 $cnt_i$ 个间隙，其中第 $j$ 个间隙的长度为 $f_{i,j}$，于是就用总区间的个数减去没有这个元素的区间个数。

于是可以得到总多样性 

$$
S=\sum_{i=1}^K(\dfrac{n\times (n+1)}{2}-\sum_{j=1}^{cnt_i}\dfrac{f_{i,j}(f_{i,j}+1)}{2})
$$

其中 $K$ 表示不同元素个数，$n$ 表示区间长度。

又注意到 $n-c_i=\sum_{i=1}^{cnt_i}f_{i,j}$，$c_i$ 为元素 $i$ 的出现次数。

于是拆拆拆，就可以得到：

$$
S=\dfrac{1}{2}(KN(N+1)-N(K-1)-\sum_{i=1}^K\sum_{j=1}^{cnt_i}f_{i,j}^2)
$$

于是任务为最大化 $\sum_{i=1}^K\sum_{j=1}^{cnt_i}f_{i,j}^2$。

然后就可以猜结论了。

## 结论 1

在一个最优解中，重排后的序列每一种数字一定都是连续的排在一起的，不会分开这里放一个那里放一个。

这个结论挺简单，证明略。

## 结论 2

知道了前面那个东西还是不太能做，考虑一下应该怎么摆放，显然分析到现在数字的大小并没有什么意义，而是在于每种数字的个数。

然后经过一顿猜，发现最优策略是把每种数字的个数从小到大排序，然后先第一种数字都塞头，再把第二种数字都塞尾，第三种数字都塞头，交错着塞。

感性理解一下，这样子分配会很均匀，所以不会劣。（如果要看证明的请去官方题解看那 3 页数学公式。。。）

猜到这个东西就可以 $\mathcal{O(nq\log n)}$ 了。64 pts 到手。

考虑如何维护这个东西，发现可以把每种数字的个数都塞进一个桶里，形式化的来说，设 $t_i$ 表示有 $t_i$ 种数字的个数都为 $i$。

惊奇的发现这个桶里有值的地方最多 $\mathcal{O(\sqrt{n})}$ 个，因为最坏情况为 $1+2+3+4+...+L\le n$，$L\le \sqrt{n}$。

如果我们知道桶里那些地方有值，该如何计算贡献？

假设左边已经塞了 $l$ 个数字右边塞了 $r$ 个数字，当前左边还要塞 $lput$ 种，右边还要塞 $rput$ 种，每种个数为 $len$ 的数字。

可以左边塞的这些数字造成的左边空隙的贡献之和为：

$$
\sum_{i=0}^{lput-1}(i\times len+l)^2
$$

这个东西很好算，拆开就是自然数 $1$ 次幂和，$2$ 次幂和。

其他的 $3$ 种情况可以仿照上面这种情况计算。

剩下的问题就是如何维护这个桶了，考虑莫队，开个 `set` 暴力维护桶里哪些地方有值，算贡献的时候直接把有值的地方拉出来就行了，但是这样子复杂度 $\mathcal{O}(q\sqrt{n}\log n)$，极其的不优美，而且由于洛谷的 120s 限制开不到 7s，无法通过。

考虑一下转移的时候 $\mathcal{O}(1)$ 转移，可以开一个操作栈记录下所有的转移（插入一个数字/删除一个数字），把数字拉出来的时候就看最后一次操作到底是插入还是删除（显然只有最后一次操作才有影响），但是拉出来的数字可能无序，需要排序，注意到拉出来的数字最多会有 $\mathcal{O}(\sqrt{n})$ 个，于是复杂度就只有 $\mathcal{O}(q\sqrt{n}+q\sqrt{n\log n})$，可以通过此题，如果你想 $\mathcal{O}(q\sqrt{n})$，请使用基数排序。。。

丑陋的代码

```cpp
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;
#define LL long long
inline int rd(){
	char c;
	int x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	return x*f;
}
#define mp make_pair
#define pp pair<int,int> 
int n,q,B,bl[300005],tong[300005],col[300005],len,c[2][300005],a[300005],K,oplen,num[1200005],Num[300005];
bool ok[300005];
pp opr[1200005];
LL ans[50005];
struct que{
	int l,r,id;
}Q[50005];
bool cmp(que a,que b) {
	return (bl[a.l]^bl[b.l])?bl[a.l]<bl[b.l]:((bl[a.l]&1)?a.r<b.r:a.r>b.r);
}
set<int>S;
set<int>::iterator it;
void add(int x){
	tong[col[a[x]]]--;
	if(!tong[col[a[x]]])opr[++oplen]=mp(-1,col[a[x]]);
	col[a[x]]++;
	if(col[a[x]]==1)K++;
	tong[col[a[x]]]++;
	if(tong[col[a[x]]]==1)opr[++oplen]=mp(1,col[a[x]]);
}
void dec(int x){
	tong[col[a[x]]]--;
	if(!tong[col[a[x]]])opr[++oplen]=mp(-1,col[a[x]]);
	col[a[x]]--;
	if(col[a[x]]==0)K--;
	tong[col[a[x]]]++;
	if(tong[col[a[x]]]==1)opr[++oplen]=mp(1,col[a[x]]);
}
LL Sum1(int n){
	return 1ll*n*(n+1)/2;
}
LL Sum2(int n){
	return 1ll*n*(n+1)*(2*n+1)/6;
}
//0 1 2
LL calc1(int N,int c,int len){
	return 1ll*c*c*(N+1)+1ll*Sum2(N)*len*len+2ll*Sum1(N)*len*c;
}
LL calc2(int N,int c,int len){
	return 1ll*c*c*(N+1)+1ll*Sum2(N)*len*len-2ll*Sum1(N)*len*c;
}
//i^2len^2+2*i*lenl
LL solve(int L,int R){
	int nlen=0;
	for(int i=oplen;i>=1;i--){
		if(ok[opr[i].second])continue;
		ok[opr[i].second]=1;
		if(opr[i].first==1)Num[++nlen]=opr[i].second;
	}
	for(int i=1;i<=len;i++){
		if(ok[num[i]])continue;
		ok[num[i]]=1;
		Num[++nlen]=num[i];
	}
	for(int i=oplen;i>=1;i--)ok[opr[i].second]=0;
	for(int i=1;i<=len;i++)ok[num[i]]=0;
	len=nlen;
	for(int i=1;i<=len;i++)num[i]=Num[i];
	sort(num+1,num+len+1);
	for(int i=1;i<=len;i++){
		c[0][i]=num[i];
		c[1][i]=tong[num[i]];
	}
	//表示长度为 (*it) 的有这么多个 
	int l=0,r=0,tot=0,N=R-L+1;
	LL Ans=0;
	for(int i=1;i<=len;i++){
		int lput=0,rput=0,Len=c[0][i];
		if(tot%2==0){
			lput=(c[1][i]+1)/2;
			rput=c[1][i]/2; 
		}else{
			rput=(c[1][i]+1)/2;
			lput=c[1][i]/2; 
		}
		Ans+=calc1(lput-1,l,Len);
		Ans+=calc2(lput-1,N-l-Len,Len);
		Ans+=calc1(rput-1,r,Len);
		Ans+=calc2(rput-1,N-r-Len,Len);
		l+=lput*Len,r+=rput*Len; 
		tot+=c[1][i];
	} 
	return 1ll*(1ll*K*N*(N+1)-1ll*N*(K-1)-Ans)/2;
}
int main() {
	scanf("%d %d",&n,&q);
	B=sqrt(n*1.0);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)bl[i]=(i-1)/B+1;
	for(int i=1;i<=q;i++)scanf("%d %d",&Q[i].l,&Q[i].r),Q[i].id=i;
	sort(Q+1,Q+q+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=q;i++){
		int L=Q[i].l,R=Q[i].r;
		oplen=0;
		while(l<L)dec(l),l++;
		while(L<l)l--,add(l);
		while(r<R)r++,add(r);
		while(R<r)dec(r),r--;
		ans[Q[i].id]=solve(L,R);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
    return 0;
}
```



---

## 作者：Purslane (赞：5)

# Solution

马上要省选了兄弟们，所以这篇题解着重讲解如何把这个题秒了，关键结论就不给证明了哦哦。

本题有点古早 CNOI 的感觉，来点公式化做题。

第一步，**尝试给出一个多项式时间复杂度的暴力**。在我刚开始学 OI 的时候（上高中之前），我始终打不出什么比较好的成绩，因为对于难题我只会写指数复杂度的爆搜。这道题的暴力，暴力应当就是处理单组询问，可以使用一大堆循环。现在我们只需要处理一个简单的最优化问题。

第二步，**对最优结构进行调整，得到最优解的必要条件**。相同的数一定会排在一块（使用调整法，记录将不连续但权值相同的数放在一起的增量），所以每个数的参量只有其出现次数。也就是给定序列 $a$，需要求 $\sum_{i=1}^m \sum_{j=i+1}^m (j-i)a_ja_i$ 的最小值（内部会有 $\sum_{i=1}^m \dfrac{a_i(a_i+1)}{2}$ 的贡献，但是显然是常量）。

直接调整可以发现 $a$ 一定是单峰的。这时候使用不要脸的打表手段得到，必定是最大值在最中间，然后从大到小往两侧交替加数。（证明略，据说很复杂）

这样最优结构是唯一确定的了，因此这道题就变为计算题而不是最优化题了。

第三步，**弄明白在给定最优解的情况下，如何计算答案**。

考虑记录 $pre_i$ 为 $\sum_{j=1}^i a_j$，$sum_i = \sum_{j=1}^i (i-j+1) a_j$。

这样有 $pre_i = pre_{i-1} + a_i$，$sum_i = sum_{i-1} + pre_i$。

则答案就是 $\sum_{i=1}^m \dfrac{a_i(a_i+1)}{2} + \sum_{i=1}^m a_i (pre_{i-1}+sum_{i-1})$。

因此得到了 $O(m)$ 的计算方法。

第四步，**分析问题性质，分析第三步如何加速，并且套用一些经典技巧对整体进行优化**。

显然有 $\sum_{i=1}^m a_i = len$，所以 $a_i$ 的取值只有 $O(\sqrt {len})$ 种。

所以排序之后的 $a_i$，按照相同值合并之后也只有 $O(\sqrt n)$ 个连续段。

而同一个连续段内，$sum$ 和 $pre$ 的变化都是很有规律的。随便写几项就可以发现（设有长度为 $k$ 个 $u$）：

$$
ans' \leftarrow ans + k \dfrac{u(u+1)}{2} + u(pre \times k + \dfrac{k(k+1)}{2} \times sum + u \sum_{i=1}^k \dfrac{(i-1)(i+3)}{2}) \\
sum' \leftarrow sum + u \times k \\
pre' \leftarrow pre + k\times sum + \dfrac{k(k+1)}{2} u
$$

稍微预处理一下就是 $O(\sqrt n)$ 单次的了。

剩下的问题是，怎么把所有的 $a$ 找到。这种问题往往能用莫队解决。

那么我们需要再区间数颜色这种问题的基础上，统计处颜色的数量的所有可能值。考虑建立一个双向链表，记录所有可能的 $a$ 的前驱和后继。

这样本题就可以在 $O(q \sqrt n )$ 的复杂度内完成了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,q,a[MAXN],ppre[MAXN],cnt[MAXN],cc[MAXN],pid[MAXN],nid[MAXN];
void add_node(int u,int pp,int nn) {
	return nid[pp]=u,pid[nn]=u,nid[u]=nn,pid[u]=pp,void();	
}
void del_node(int u) {int pp=pid[u],nn=nid[u];nid[pp]=nn,pid[nn]=pp,pid[u]=nid[u]=0;return ;}
void add(int u) {
	if(cc[cnt[u]+1]==0) add_node(cnt[u]+1,cnt[u],nid[cnt[u]]);
	if(cc[cnt[u]]==1) del_node(cnt[u]);
	cc[cnt[u]]--,cnt[u]++,cc[cnt[u]]++;
	return ;
}
void del(int u) {
	if(cc[cnt[u]-1]==0) add_node(cnt[u]-1,pid[cnt[u]],cnt[u]);
	if(cc[cnt[u]]==1) del_node(cnt[u]);
	cc[cnt[u]]--,cnt[u]--,cc[cnt[u]]++;
	return ;
}
int calc(void) {
	deque<pair<int,int>> dq;
	int u=pid[300000+1],flg=0;
	while(u!=0) {
		if(flg) dq.push_back({u,cc[u]-cc[u]/2}),dq.push_front({u,cc[u]/2});
		else dq.push_front({u,cc[u]-cc[u]/2}),dq.push_back({u,cc[u]/2});
		flg^=(cc[u]&1),u=pid[u];
	}
	int ans=0,pre=0,sum=0;
	while(!dq.empty()) {
		auto pr=dq.front(); dq.pop_front();
		int u=pr.first,k=pr.second;	
		ans+=k*u*(u+1)/2+u*(pre*k+k*(k+1)/2*sum+u*ppre[k]),pre=pre+k*sum+k*(k+1)/2*u,sum=sum+k*u;
	}
	return ans;
}
struct INFO {int l,r,id;}qr[MAXN];
bool operator <(INFO A,INFO B) {
	if(A.l/1300!=B.l/1300) return A.l/1300<B.l/1300;
	return A.r<B.r;	
}
int l=1,r=0,ans[MAXN];
void mo(void) {
	ffor(i,1,q) {
		while(r<qr[i].r) add(a[++r]);
		while(l>qr[i].l) add(a[--l]);
		while(r>qr[i].r) del(a[r--]);
		while(l<qr[i].l) del(a[l++]);
		ans[qr[i].id]=calc();
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) ppre[i]=ppre[i-1]+(i-1)*(i+2)/2;
	ffor(i,1,q) cin>>qr[i].l>>qr[i].r,qr[i].id=i;
	sort(qr+1,qr+q+1);
	pid[300000+1]=0,nid[0]=300000+1,cc[0]=cc[300000+1]=1000000000;
	mo();
	ffor(i,1,q) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

提供一种不要脑子的大常数做法，能跑过，目前 luogu 上最优解第二（虽然这说明不了什么）。

考虑怎样重排能最小化总权值，显然要将所有相同的数排到一起，于是就形成了一些连续段，每个连续段内的数相同，不同连续段之间的数都是不同的。

现在的问题就在于如何安排这些连续段的位置关系。不难发现此时总权已经和连续段内的数值无关了，只和连续段的长度有关。假如我们现在已经定出来了一种安排这些连续段的顺序，设整个询问区间 $[qx,qy]$ 长度为 $sum=qy-qx+1$，里面连续段的长度依次为 $len_1,len_2,\cdots,len_m$，我们就将每种数值的贡献分为三类：

1. 一个连续段内部的：这样的区间也就只包含了该连续段对应的那个数值，贡献为 $\sum\limits_{i=1}^m \frac{len_i(len_i+1)}{2}$，这和 $len_i$ 的放置顺序无关。
2. 一个端点在该连续段内部，另一个端点在连续段外部：那么在该段右侧的点可以当右端点，在左侧的点可以当左端点，贡献 $\sum\limits_{i=1}^m len_i(sum-len_i)$，和 $len_i$ 的放置顺序无关。
3. 整个区间跨越了该连续段：那么贡献 $\sum\limits_{i=1}^m\sum\limits_{j=1}^{i-1}len_j\times \sum\limits_{j=i+1}^{m}len_j$，容易发现左右两边乘的东西之和是固定的，为 $sum-len_i$，想到小学的时候学过的“和一定差小积大”，考虑使两边的差尽量大，这启发我们将连续段按照长度从小到大排序，第一小的放在开头，第二小的放在结尾，第三小的放在开头……这样看起来就最优了，证明可以参考官解。

想到这里就很简单了，考虑莫队，每次对询问统计答案的时候，发现**连续段的不同长度至多 $\mathcal{O}(\sqrt n)$** 种，于是考虑维护这 $\mathcal{O}(\sqrt n)$ 种取值，然后直接枚举一下再分配就行了，可以使用 set，但是多了一个 $\log n$，注定过不去。想到可以用 map 状物维护，如果一个点的出现次数已经被删成 $0$ 了，就从 map 里面删掉，最后遍历这个 map 取出所有有效位置即可。把 map 替换成 cc_hash_table 就可以更快，但是会发现取出来的数是无序的，直接上一个基数排序就做完了。然后具体怎么统计第 $3$ 种贡献，推推式子就做完了。主要是注意 long long 问题。我真不知道这个写法复杂度是多少，pbds 给人一种玄学的美。

gp_hash_table 删除元素巨慢，如果真要删还得 cc_hash_table。不删然后只是在出现次数为 $0$ 的位置 continue 可以在 luogu 上跑过去，不是很懂。

感觉我的贡献算复杂了。怎么会是呢？

[删除了为 $0$ 位置的版本(cc_hash_table)。](https://loj.ac/s/1988131)

[没有删除为 $0$ 位置的版本(gp_hash_table）](https://loj.ac/s/1988131)，离谱的是在 loj 上这么些用 gp 更快但是在 luogu 上 gp 就会 TLE on #86 但是 cc 就能过并且只要 206ms。

---

