# Another Folding Strip

## 题目描述

对于一个长度为 $m$ 的数组 $b$，定义 $f(b)$ 如下：

考虑一个 $1 \times m$ 的纸带，所有单元格初始暗度为 $0$。你需要通过以下操作将其转化为第 $i$ 个位置的暗度为 $b_i$ 的纸带。每次操作包含两个步骤：

1. 在任意两个单元格之间的线上折叠纸带。你可以进行任意次折叠（包括不折叠）。
2. 选择一个位置滴下黑色染料。染料会从顶部渗透并向下流动，使其路径上所有单元格的暗度增加 $1$。滴完染料后展开纸带。

令 $f(b)$ 为达成目标配置所需的最小操作次数。可以证明总能通过有限次操作达成目标。

给定一个长度为 $n$ 的数组 $a$，计算

$$ \sum_{l=1}^n\sum_{r=l}^n f(a_l a_{l+1} \ldots a_r) $$

模 $998\,244\,353$ 的结果。

## 说明/提示

第一个测试用例中：
- $f(a_1)=f(\mathtt{0})=0$
- $f(a_1a_2)=f(\mathtt{01})=1$
- $f(a_1a_2a_3)=f(\mathtt{010})=1$
- $f(a_2)=f(\mathtt{1})=1$
- $f(a_2a_3)=f(\mathtt{10})=1$
- $f(a_3)=f(\mathtt{0})=0$

总和为 $0+1+1+1+1+0 = 4$。

第二个测试用例中，$f(a_1a_2a_3a_4a_5a_6) = 2$。下图展示了一种可能的操作序列：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2077E/80a2b52ea34f6bea16eaab9b1e723d17328eb717.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
0 1 0
6
1 0 0 1 2 1
5
2 1 2 4 3
12
76 55 12 32 11 45 9 63 88 83 32 6```

### 输出

```
4
28
47
7001```

# 题解

## 作者：kradcigam (赞：7)

怎么都不是这么做的？？？

先考虑计算 $f(a_1,a_2,\cdots,a_n)$。

考虑一次折叠相当于将编号为 $p_1<p_2<\cdots<p_k$ 的格子减一，然后要求 $p_i$ 和 $p_{i-1}$ 奇偶性不同。

考虑构建一张二分图，其中左部点表示入度，右部点表示出度。入度 $i$ 能和出度 $j$ 匹配，当且仅当 $j<i$，且$i,j$ 奇偶性不同。

那么最少操作次数，就等价于 $\sum_{i=1}^{n} a_i-\text{maxmatch}$。

计算 $\text{maxmatch}$ 考虑 Hall 定理，对于权值，我们可以等效看成多个点，令 $L$ 表示左部点集合，$N(S)$ 表示 $S$ 集合出边的并集。由于 $\text{maxmatch}=|L|-\max_{S\subseteq L}\{|S|-|N(S)|\}$，所以最少操作次数为 $\max_{S\subseteq L}\{|S|-|N(S)|\}$。

对于 $N(S)$，我们发现我们只关心 $S$ 集合中的编号最大值 $mx_1$，以及编号和 $mx_1$ 奇偶性不同的编号最大值 $mx_2$。我们发现，$mx_2$ 前面的位置选，不会对 $N(S)$ 造成影响，同时 $(mx_2,mx_1]$ 之间和 $mx_1$ 奇偶性相同的位置，也不会对 $N(S)$ 产生影响。于是，为了使得 $|S|$ 尽量大，我们会将这些点全选。

我们发现此时 $S$ 为 $\{i|i\le mx_2\}\cup\{i|i\in[mx_2,mx_1]\land i\equiv mx_1\pmod 2\}$，$N(S)$ 为 $\{i|i\le mx_2\}\cup\{i|i\in(mx_2,mx_1]\land i\not\equiv mx_1\pmod 2\}$。

那么 $|N(S)|-|S|$ 就为：

$$\max_{mx_1>mx_2\land mx_1\not\equiv mx_2\pmod 2\}}\{\sum_{i\in (mx_2,mx_1]\land i\equiv mx_1\pmod 2} a_i - \sum_{i\in (mx_2,mx_1]\land i\not\equiv mx_1\pmod 2} a_i\}$$

就得到了这个重要结论。

然后，我们发现，如果单纯是求最大区间偶数位置和减奇数位置和，是[Treasure Hunt](https://codeforces.com/contest/1787/problem/I)，所以一定有玄机。

我们考虑令 $s_i$ 为前 $i$ 个数，奇数位置减去偶数位置的差。

那么我们惊讶的发现，求的东西就可以等效成 $\max_{i=l-1}^{r} \{s_i\}-\min_{i=l-1}^{r} \{s_i\}$。

于是拆成两部分，单调栈维护了。

---

## 作者：KingPowers (赞：6)

挺有意思的一道题，部分内容参考官方题解，本题解将对所有的结论给出严谨证明。

首先转化掉折叠操作，显然对于两个奇偶性相同的下标，无论怎么折叠都无法使它们重合。进一步地，不难发现一次操作其实等价于选出一个相邻下标奇偶性不同的子序列都 $+1$，充分性考虑假如选择的子序列下标为 $i_1,i_2,\ldots,i_m$ 且 $i_j$ 和 $i_{j+1}$ 奇偶性不同，令中间的 $m-1$ 个折痕的方向向左向右交替，一定能得到一个合法的折叠方式。


先考虑怎么计算整个 $a$ 序列的答案，不妨把问题倒过来看，变成每次选择 $a$ 的一个合法子序列依次 $-1$，然后要把 $a$ 变成全 $0$。考虑一个比较套路的操作，将 $a$ 黑白染色然后取反，也就是令 $b_i=(-1)^ia_i$。

注意到一个性质是，对于任意一个子段 $[l,r]$，对 $a$ 序列进行任意一次操作之后 $\sum_{i=l}^r b_i$ 的值只有不变，$+1$ 和 $-1$ 三种情况，这取决于 $[l,r]$ 中有几个位置被选进操作的子序列，也就是说 $|\sum_{i=l}^rb_i|$ 的变化量不超过 $1$，所以可以分析出来答案的一个下界是 $\max_{1\le l\le r\le  n}|\sum_{i=l}^r b_i|$，也就是序列 $b$ 绝对值最大的子段和。

令一次操作选择的子序列的下标集合为 $S$，我们用这么一个贪心的策略来确定每次的 $S$：

- 初始先令 $S$ 为空，顺序遍历每个 $b_i$。

- 如果 $b_i=0$，直接跳过它。

- 否则如果 $S$ 为空或者 $S$ 最后一个下标的奇偶性与 $i$ 不同，将 $i$ 加入到 $S$ 中，其它情况跳过。

我们声称，重复此过程确定每次操作选择的子序列，即可使答案取到下界，下面给出证明。

令 $T$ 为一次操作前所有使得 $|\sum_{i=l}^rb_i|$ 取到最大值且 $b_l,b_r\not= 0$ 的 $(l,r)$ 集合，只需要说明 $\forall (l,r)\in S$ 在操作后 $|\sum_{i=l}^r b_i|$ 一定恰好减少 $1$ 即可。

首先要观察到，每对 $(l,r)$ 的奇偶性是相同的，因为如果不同则 $b_l$ 和 $b_r$ 是异号的，去掉其中一个一定可以使绝对值变大。

一个重要的结论是，$\forall (l,r)\in T$，一定有 $l\in S$。考虑反证法，假如 $l\not\in S$，说明 $S$ 中存在一个 $k<l$，满足 $k$ 与 $l$ 奇偶性相同，且 $k$ 与 $l$ 中间和 $l$ 奇偶性不同的位置都是 $0$，此时直接把 $l$ 移动到 $k$ 显然绝对值会更大，矛盾。

可以发现的是，此时 $\forall (l,r)\in T$，$[l,r]$ 中被选到 $S$ 中的位置一定有奇数个。同样考虑反证法，假如是偶数个，那么 $S$ 中最后一个 $\le r$ 的位置 $d$ 一定与 $l,r$ 的奇偶性不同，说明下一个与 $l,r$ 奇偶性相同且非 $0$ 的位置 $>r$，与 $T$ 定义中的 $b_r\not=0$ 矛盾。

如果 $l$ 为奇数，那么 $b_{[l,r]}$ 中被选择的位置变化量形如 $+1,-1,+1,\ldots,-1,+1$，总共为 $1$，显然 $l$ 为奇数时原来的 $\sum_{i=l}^rb_i<0$，所以此时绝对值会减少 $1$。

如果 $l$ 为偶数，那么 $b_{[l,r]}$ 中被选择的位置变化量形如 $-1,+1,-1,\ldots,+1,-1$，总共为 $-1$，显然 $l$ 为偶数时原来的 $\sum_{i=l}^r b_i>0$，所以此时绝对值会减少 $1$。

综上，我们说明了这种贪心策略能使答案取到下界。

> 官方题解在证明过程中写到 $\forall (l,r)\in T$ 还有 $r\in S$ 成立，笔者认为这是错误的，考虑 $b=\{-3,0,-3\}$，则显然 $T=\{(1,3)\}$ 且 $S=\{1\}$。如果确为官方题解笔误或者是我的理解错误，请您在评论区指出/bx/bx/bx。

因此对于整个序列 $a$，我们只需要求对应的 $\max_{1\le l\le r\le n}|\sum_{i=l}^rb_i|$ 即为答案，显然这个值等于 $b$ 序列前缀和数组的极差。回到原题，再对 $b$ 数组做一遍前缀和，问题就变成了类似于求所有子区间极差和的形式，这是一个经典问题，分治，扫描线，单调栈，随便选择一个你喜欢的做法求出即可。

这里使用了单调栈实现，时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int n, a[N], b[N];
int top, ans, st[N], L[N], R[N];
inline void add(int &x, int y){x += y; if(x >= mod) x -= mod;}
inline void sub(int &x, int y){x += mod - y; if(x >= mod) x -= mod;}
void Solve(){
	cin >> n;
	For(i, 1, n) cin >> a[i];
	For(i, 1, n){
		if(i & 1) b[i] = b[i - 1] + a[i];
		else b[i] = b[i - 1] - a[i];
	}
	top = ans = 0;
	For(i, 1, n) R[i] = n;
	For(i, 1, n){
		while(top && b[st[top]] < b[i]) R[st[top]] = i - 1, top--;
		L[i] = !top ? 0 : st[top] + 1; st[++top] = i;
	}
	For(i, 1, n) (ans += (R[i] - i + 1) * (i - L[i] + 1) % mod * (b[i] % mod) % mod) %= mod;
	top = 0;
	For(i, 1, n) R[i] = n;
	For(i, 0, n){
		while(top && b[st[top]] >= b[i]) R[st[top]] = i - 1, top--;
		L[i] = !top ? 0 : st[top] + 1; st[++top] = i;
	}
	For(i, 1, n) (ans -= (R[i] - i + 1) * (i - L[i] + 1) % mod * (b[i] % mod) % mod) %= mod;
	ans = (ans % mod + mod) % mod;
	cout << ans << '\n';
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

怎么题解区做的这么复杂？

存在非常简单的 $O(n \log n)$ 做法。

考虑刻画折叠后给一处位置染色所能带来的染色位置集合是什么样的。

手玩一下可以发现折叠后被叠起来的位置在原序列中距离为偶数，并且任意满足这样性质的位置集合都可以叠起来。

也就是选出的位置下标应当是奇偶交替的。

考虑对于一个数组求出其 $f$ 值，考虑从前往后 dp，对于一个前缀，我们设其进行了若干次操作，有 $i$ 次操作最后一个操作位置下标是奇数，$j$ 次操作最后一个操作位置下标是偶数，只考虑前缀内的操作最少花费了多少代价。

转移就是考虑在奇数位置消耗若干以偶数位置结尾的操作（将其转换为以奇数位置结尾的操作）以减少在这个位置新开操作的代价。在偶数位置的转移同理。

考虑将这个 dp 过程化简以方便对于每个子区间计算贡献，不难发现当你需要消耗操作减少代价时，如果不去尽可能的消耗操作，将消耗的机会留到后面是不优的（因为后面可能没有让你消耗操作减少代价的机会了），因此这个 dp 过程可以直接化简为从前往后贪心地考虑，在这个过程中将 $i,j$ 作为两个变量记录下来。

考虑对于子区间计算答案，考虑扫描线，由于 $i,j$ 是两个变量，直接记录下 $i=i_0,j=j_0$ 的区间数量是难以做到优秀的时间复杂度的，发现两个变量之间相对独立（消耗一种操作减少代价时另一种操作增量是固定的），所以考虑将两个变量拆开处理贡献，于是可以维护二元对 $(i_0,cnt)$ 表示有 $cnt$ 个区间满足 $i=i_0$，扫描线过程中还需要支持全局 $i_0$ 加法与取出 $i_0<0$ 的二元对，于是使用整体加法标记与优先队列直接暴力取出最小的 $i_0<0$ 的二元对来维护即可做到 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 2e5+114;
int a[maxn],n;
int tag;
priority_queue< pair<int,int> ,vector< pair<int,int> >,greater< pair<int,int> > > vec;//(val,cnt)
int ans;
void work(){
    ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    //最后一个位置是奇数
    for(int i=1;i<=n;i++){
        if(i%2==1){
            tag+=a[i];
            ans+=a[i]*(n-i+1)%mod;
            ans%=mod;
            vec.push(make_pair(a[i]-tag,1));
        }else{
            //施加一个减少 a[i] 的 tag
            tag-=a[i];
            //少于 0 的部分全部变成
            int cnt=1;
            while(vec.size()>0&&vec.top().first+tag<0){
                ans+=-(vec.top().first+tag)*(n-i+1)%mod*vec.top().second%mod;
                ans%=mod;
                cnt+=vec.top().second;
                vec.pop();
            }
            vec.push(make_pair(-tag,cnt));
        }
    }
    while(vec.size()>0) vec.pop();
    tag=0;
    //最后一个位置是偶数
    for(int i=1;i<=n;i++){
        if(i%2==0){
            tag+=a[i];
            ans+=a[i]*(n-i+1)%mod;
            ans%=mod;
            vec.push(make_pair(a[i]-tag,1));
        }else{
            //施加一个减少 a[i] 的 tag
            tag-=a[i];
            //少于 0 的部分全部变成
            int cnt=1;
            while(vec.size()>0&&vec.top().first+tag<0){
                ans+=-(vec.top().first+tag)*(n-i+1)%mod*vec.top().second%mod;
                ans%=mod;
                cnt+=vec.top().second;
                vec.pop();
            }
            vec.push(make_pair(-tag,cnt));
        }
    }
    while(vec.size()>0) vec.pop();
    tag=0;
    cout<<ans<<"\n";
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
6
1 0 0 1 2 1
*/
```

---

## 作者：wishapig (赞：0)

线性做法看不太懂，这里是一个 $\log$ 的做法(/kel)。

显然一次折叠会使得若干位置的 $a_i$ 减一，考察这个位置集合的性质。

考虑这个位置集合中相邻的两个元素，它们之间至多只能存在一条折痕，同时由于折痕只能存在于两个相邻格子中间，因此这相邻的两个元素的奇偶性一定是不同的。

同时，只要这个位置集合满足相邻的两个元素的奇偶性都不同，就一定是可以被构造出来的（从前往后依次折叠即可）。

于是问题变成了，每次操作选定一个子序列 $-1$，满足子序列相邻两项坐标奇偶性不同，用最少的操作次数覆盖完 $a$。

这个问题就非常类似于积木大赛之类的套路，维护前面偶数结尾位置和奇数结尾位置可以延过来多少个子序列 $c_0,c_1$，然后对一个 $a_i$，以 $i$ 为奇数为例（偶数同理）：

- $a_i$ 需要从前面的偶数位置延过来，因此若 $c_0<a_i$，则需要补上 $a_i-c_0$ 个子序列，同时 $c_0:=0$，否则 $c_0$ 减去 $a_i$
- $c_1$ 会加上 $a_i$。

这样就可以线性地跑出一个序列的答案。

对所有区间来求，考虑从前面扫描到后面，对每个 $a_i$ 求出它对答案的贡献。

具体来说，每个区间起点 $l$ 到当前位置 $i$ 的时候，其 $c_{0,l},c_{1,l}$ 都是确定的，于是 $a_i$ 的操作就可以写为（以 $i,l$ 的奇偶性相同的情况为例）：

- 会产生 $\max(0,a_i-c_{0,l})$ 个新子序列，并令 $c_{0,l}:=\max(0,c_{0,l}-a_i)$
- $c_{1,l}:=c_{1,l}+a_i$

于是多个 $l$ 的操作就可以同时进行，维护四颗权值线段树分别维护所有起点是偶数/奇数的 $c_{0/1}$。

那么就要维护以下操作：

- 所有权值 $+d$
- 区间求和（权值个数/权值之和）
- 单点加

所有权值 $+d$ 相当于位移，不好操作，所以维护一个基准点表示 $0$ 的位置，这样就变成了基准点的移动。

最后求出 $a_i$ 的贡献之后，区间右端点可以在 $[i,n]$ 中取，因此还要乘上 $n-i+1$ 再加到答案中。

时间复杂度 $O(\sum n\log W)(W=\sum a_i)$。

好像要卡一下空间。

```cpp
struct seg_tree{ int rt; ll d; } T[2][2];
inline void pushdown(int now){
	if (tag[now]){
		if (ls[now]) cnt[ls[now]]=sum[ls[now]]=0,tag[ls[now]]=1;
		if (rs[now]) cnt[rs[now]]=sum[rs[now]]=0,tag[rs[now]]=1;
		tag[now]=0;
	}
}
void update(int& now, ll l, ll r, ll x, int y){
	if (!now) now=++tsiz;
	cnt[now]+=y,sum[now]=(sum[now]+1ll*x%mod*y%mod+mod)%mod;
	if (l==r) return;
	ll mid=(l+r)>>1; pushdown(now);
	mid>=x?update(ls[now],l,mid,x,y):update(rs[now],mid+1,r,x,y);
}
pair<int,int> query(int now, ll l, ll r, ll x, ll y){
	if (!now) return make_pair(0,0);
	if (l==x && r==y){
		int d1=cnt[now],d2=sum[now];
		cnt[now]=sum[now]=0,tag[now]=1;
		return {d1,d2};
	}
	ll mid=(l+r)>>1; pushdown(now);
	if (mid>=y){
		auto P=query(ls[now],l,mid,x,y);
		cnt[now]=cnt[ls[now]]+cnt[rs[now]];
		sum[now]=(sum[ls[now]]+sum[rs[now]])%mod;
		return P;
	} else
	if (mid<x){
		auto P=query(rs[now],mid+1,r,x,y);
		cnt[now]=cnt[ls[now]]+cnt[rs[now]];
		sum[now]=(sum[ls[now]]+sum[rs[now]])%mod;
		return P;
	} else {
		auto P1=query(ls[now],l,mid,x,mid),P2=query(rs[now],mid+1,r,mid+1,y);
		cnt[now]=cnt[ls[now]]+cnt[rs[now]];
		sum[now]=(sum[ls[now]]+sum[rs[now]])%mod;
		return {P1.first+P2.first,(P1.second+P2.second)%mod};
	}
}
//求区间中的权值个数和权值之和，在查询完之后直接删除这部分
int main(){
	for (cin>>Tc; Tc; Tc--){
		scanf("%d",&n); int ans=0;
		
		for (int i=1; i<=n; i++){
			scanf("%d",&x);
			update(T[i&1][0].rt,-L,L,T[i&1][0].d,1);
			update(T[i&1][1].rt,-L,L,T[i&1][1].d,1);
			
			int res=0;
			auto P0=query(T[i&1][0].rt,-L,L,T[i&1][0].d,T[i&1][0].d+x);
			int c0=P0.first,s0=P0.second;
			res=(res+1ll*c0*(x+T[i&1][0].d%mod)+mod-s0)%mod;
			T[i&1][1].d-=x; T[i&1][0].d+=x;
			update(T[i&1][0].rt,-L,L,T[i&1][0].d,c0);
			
			auto P1=query(T[(i&1)^1][1].rt,-L,L,T[(i&1)^1][1].d,T[(i&1)^1][1].d+x);
			int c1=P1.first,s1=P1.second;
			res=(res+1ll*c1*(x+T[(i&1)^1][1].d%mod)+mod-s1)%mod;
			T[(i&1)^1][0].d-=x; T[(i&1)^1][1].d+=x;
			update(T[(i&1)^1][1].rt,-L,L,T[(i&1)^1][1].d,c1);
			
			ans=(ans+1ll*(res%mod+mod)*(n-i+1))%mod;
		}
		printf("%d\n",ans);
		
		for (int i=1; i<=tsiz; i++) ls[i]=rs[i]=cnt[i]=sum[i]=tag[i]=0;
		tsiz=T[0][0].d=T[0][0].rt=T[0][1].d=T[0][1].rt=T[1][0].d=T[1][0].rt=T[1][1].d=T[1][1].rt=0;
	}
}
```

---

