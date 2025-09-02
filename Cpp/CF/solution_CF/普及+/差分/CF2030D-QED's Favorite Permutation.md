# QED's Favorite Permutation

## 题目描述

你有一个长度为 $n$ 的排列 $p$，也就是说，$1$ 到 $n$ 中的每个正整数都在 $p$ 中出现恰好一次。同时你还有一个长度也为 $n$ 的字符串 $s$，其中仅含 `L` 和 `R` 两种字符。（排列和字符串的下标均从 $1$ 开始编号）

定义一次操作为：任意选择一个编号 $i$（$1 \le i \le n$），在这之后：

* 如果 $s_i$ 为 `L`，则交换 $p_i$ 和 $p_{i-1}$。（保证 $s_1$ 不为 `L`）

* 如果 $s_i$ 为 `R`，则交换 $p_i$ 和 $p_{i+1}$。（保证 $s_n$ 不为 `R`）

接下来给出 $q$ 次询问，在第 $i$ 次询问中（$1 \le i \le q$），你将会得到一个编号 $x_i$（$1 \le x_i \le n$），表示如果 $s_{x_i}$ 为 `L`，则你需要将其改为 `R`；反之如果 $s_{x_i}$ 为 `R`，则你需要将其改为 `L`。在修改完成之后，你还需要判断能否通过上述操作使得排列 $p$ 单调递增（操作次数不限），即对任意的 $1 \le i \le n-1$，都有 $p_i < p_{i+1}$。

**询问中对字符串 $\bm{s}$ 的修改均为永久性的，会在询问结束后保留。在回答询问的过程中，你不应对排列 $\bm{p}$ 进行任何真实的操作。**

## 样例 #1

### 输入

```
3
5 3
1 4 2 5 3
RLRLL
2
4
3
8 5
1 5 2 4 8 3 6 7
RRLLRRRL
4
3
5
3
4
6 2
1 2 3 4 5 6
RLRLRL
4
5```

### 输出

```
YES
YES
NO
NO
YES
NO
NO
NO
YES
YES```

# 题解

## 作者：_mi_ka_ (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF2030D)

## 题目描述

给定一个长度为 $n$ 的排列 $p$（包含从 $1$ 到 $n$ 的所有数字），对应一串只由 `L` 和 `R` 组成的字符串，`L` 表示这个数可以和左边相邻的数字交换，`R` 表示这个数可以和右边相邻的数交换。$q$ 次询问每次改掉字符串中的一个字符（`L` 改为 `R`，`R` 改为 `L`），且每次修改后保留，问每次修改后是否能通过字符串中的 `L` 和 `R` 操作将此排列非降序排序。

## 解题思路

通过题意，我们会发现，一个数字 $p_i$ 可以向右交换，当且仅当 $s_i=$`R` 或者 $s_{i+1}=$`L`。换句话说，对于一个 $i(1\le i\le n)$，**只要 $s_i=$`L` 并且 $s_{i+1}=$`R`**，$p_i$ 及其左边的数就永远交换不到右边，$p_{i+1}$ 及其右边的数也永远交换不到左边，我们暂称 $i$ 和 $i+1$ 这条“无法逾越的线”叫做**分界线**。那么只要在**这条分界线左边（从 $p_1$ 到 $p_i$）没有涵盖从 $1$ 到 $i$ 所有的数**，那么它所缺少的数在分界线右边，永远不会交换到 $1$ 到 $i$ 内，此时序列永远不会非降序排序。只要序列中存在这样的分界线，答案一定是 NO，我们称这种分界线为**对答案有贡献的分界线**。

所以我们只需要维护这种对答案有贡献的分界线的个数 cnt，cnt 非零就输出 NO，否则就是 YES。这样一来，预处理是必不可少的，定义 bool 类型 check 数组，其中 $check_i$ 表示从 $p_1$ 到 $p_i$ 是否涵盖了从 $1$ 到 $i$ 的所有数字，并定义一个 set 来存储所有的分界线的左下标。

对于每次修改 $s_i$，如果 $i$ 或者 $i-1$ 为分界线的下标，说明这次修改把分界线破坏掉了，将其在 set 中删除，再根据分界线的下标确定是否将对答案有贡献的分界线破坏掉了，如果是，更新 cnt。修改完后，判断此时 $s_i$ 与其左边或者右边是否又组成了新的分界线，将分界线存入 set 中，并判断根据分界线左下标的 check 判断此分界线是否为对答案有贡献的分界线，更新 cnt。然后根据当前 cnt 值输出就可以了。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
#include<set>
#define N 200005
using namespace std;
int T,n,q;
int a[N];//序列p
char s[N];
bool check[N];
set<int>st;
int re()//防止作弊不放快读快写
void wr(int x)
signed main()
{
	T=re();
	while(T--)
	{
		int maxx=0,cnt=0;//maxx代表当前所输进来的最大值
		n=re(),q=re();
		for(int i=1;i<=n;i++)
			a[i]=re(),maxx=max(maxx,a[i]),check[i]=(maxx==i);//如果maxx不是i，说明当前p1~pi中有比i大的数，则p1~pi肯定不会涵盖1~i的所有元素
		cin>>s;
		for(int i=n;i;i--)
			s[i]=s[i-1];
		s[0]=0;//手动将字符串改为下标为1~n的
		for(int i=1;i<n;i++)
			if(s[i]=='L'&&s[i+1]=='R')//分界线
			{
				st.insert(i);
				if(!check[i])//对答案有贡献的分界线
					cnt++;
			}
		while(q--)
		{
			int k=re();
			s[k]=s[k]=='L'?'R':'L';//修改操作
			if(st.find(k)!=st.end())//k是一条分界线左下标
			{
				st.erase(k);
				if(!check[k])
					cnt--;
			}
			if(st.find(k-1)!=st.end())
			{
				st.erase(k-1);
				if(!check[k-1])
					cnt--;
			}
			if(s[k]=='L'&&s[k+1]=='R')
			{
				st.insert(k);
				if(!check[k])
					cnt++;
			}
			if(s[k]=='R'&&s[k-1]=='L')
			{
				st.insert(k-1);
				if(!check[k-1])
					cnt++;
			}//更新cnt
			puts(cnt?"NO":"YES");
		}
		st.clear();//多测清空
	}
	return 0;
}



```

---

## 作者：Super_Cube (赞：5)

# Solution

由于给的是排列，那么 $i$ 在排序后应该去到 $a_i$，这一段应该呈现为 $\texttt{R}\cdots\texttt{R}\texttt{L}\cdots\texttt{L}$，如果其中出现 $\texttt{LR}$ 那么不能成功移动。

对 $i\sim a_i$ 这一段打标记，若被标记的位置存在 $\texttt{LR}$ 则无法成功排序。维护所有被标记位置中 $\texttt{LR}$ 的出现个数，每次修改 $s_i$ 时判断 $i$ 是否被标记，若被标记则进行更新。

时间复杂度：$O(n+q)$。

---

## 作者：WRuperD (赞：3)

# CF2030D QED's Favorite Permutation 题解

[本文同步发表于我的博客](https://wruperd.github.io/post/2024-10-22-solution-cf2030d/)

CodeFancy 好喜欢考察这个 Trick 啊，已经见到第三次了。

首先手玩可以发现，不能交换两个位置 $i,j$ 上的数当且仅当 $x \in [i,j),s_x = L,s_{x+1} = R$。转换一下视角，由于是看全局能不能排序，所以我们可以预处理哪些位置 $x$ 满足 $s_x=L,s_{x+1}=R$ 的条件会使得答案为否。这个可以直接对于每一个 $[\min(a_i,i),\max(a_i,i))$ 差分去打一个区间加标记来解决。 

然后对于每一次单点修改你就更新一下 $x,x-1$ 这两个位置对答案的贡献就行了。复杂度是 $O(n)$。
 
 ```cpp
// Problem: D. QED's Favorite Permutation
// URL: https://codeforces.com/contest/2030/problem/D
// Writer:WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 5e5 + 10;

int a[MAX];
int s2[MAX];

void solve(){
	int n = read(), m = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	string s;
	cin >> s;
	int l = 1, r = 0;
	for(int i = 1; i <= n; i++){
		s2[i] = 0;
	}
	for(int i = 1; i <= n; i++){
		int L = min(a[i], i), R = max(a[i], i);
		s2[L]++;
		s2[R]--;
	}
	int now = 0;
	for(int i = 1; i <= n; i++){
		now += s2[i];
		s2[i] = now;
	}
	// while(a[l] == l and l <= n){
		// l++;
	// }
	// while(a[r] == r and r >= 1){
		// r--;
	// }
	// // write(l), endl;
	// if(l == n + 1){
		// while(m--){
			// int x = read();
			// puts("YES");
		// }
		// return ;
	// }
	int cnt = 0;
	for(int i = 1; i < n; i++){
		if(s2[i] and s[i - 1] == 'L' and s[i] == 'R'){
			cnt++;
		}
	}
	while(m--){
		int x = read();
		// if(x < l or x > r){
			// if(cnt)	puts("NO");
			// else puts("YES");
			// continue;
		// }
		int pre = 0;
		if(s2[x - 1])	pre += (s[x - 2] == 'L' and s[x - 1] == 'R');
		if(s2[x])	pre += (s[x - 1] == 'L' and s[x] == 'R');
		int now = 0;
		if(s[x - 1] == 'L')	s[x - 1] = 'R';
		else s[x - 1] = 'L';
		if(s2[x - 1])	now += (s[x - 2] == 'L' and s[x - 1] == 'R');
		if(s2[x])	now += (s[x - 1] == 'L' and s[x] == 'R');
		cnt += now - pre;
		// write(cnt), put(), write(pre), endl;
		if(cnt){
			puts("NO");
		}else{
			puts("YES");
		}
	}
}

signed main(){
	int t = read();
	while(t--)	solve();
	return 0;
}
```

---

## 作者：luogu_starblue (赞：3)

# [CF2030D QED's Favorite Permutation](https://www.luogu.com.cn/problem/CF2030D)

## 题目大意

给定一个长度为 $n$ 的排列 $p$，以及一个长度为 $s$ 只包含 $ \texttt{L} $ 或 $ \texttt{R} $ 的字符串，可以对排列进行若干次操作。若 $s_i$ 为 $ \texttt{L} $，那么可以互换 $p_i$ 和 $p_{i-1}$，保证 $ s_1 \neq \texttt{L} $。若 $s_i$ 为 $ \texttt{R} $，那么可以互换 $p_i$ 和 $p_{i+1}$，保证 $ s_n \neq \texttt{R} $。有 $q$ 次询问，每次会修改一个位置的 $s_i$，将其修改为另一种字符。每次修改完后询问是否可以通过若干次操作将排列 $p$ 变为一个非递减序列。

## 解题思路

我们考虑每相邻 $2$ 个字符，发现如果是 LL,RR,RL 的话，那么所对应的 $2$ 个位置的数字一定是可以任意交换的，若其为 LR，则不能交换，然后考虑什么情况下的 LR 是合法的，因为 $p$ 是一个排列，设 L 所对应的下标为 $n$，排列 $p$ 的大小为 $m$，显然当 $\max_{i=1}^{n}p_i \le n $ 并且 $\min_{i=n+1}^{m} \ge n+1$ 时 LR 才是合法的。

因此我们需要一个数据结构来帮助我们查询最大最小，这里我选用了个人习惯的 线段树 ，当然用 st表 复杂度更加优秀。需要记录一下当前不合法的 LR 个数，每次修改的时候算一下贡献就可以，若没有不合法的则可以，否则不可以。

后来想了想似乎只需判断 $\sum_{i=1}^{n}p_i= \sum_{i=1}^{n}i$ 就可以了，~~但是我懒的写代码实现了~~。

我的代码时间复杂 $O(q\log n+n\log n)$。

赛时代码如下，~~较丑勿喷~~。


```cpp
#include<bits/stdc++.h>
#define mid (l+r>>1)
using namespace std;
const int maxn=2e5+9;
int a[maxn];
struct node
{
	int ma,mi;
}t[maxn<<2];
node merge(node a,node b)
{
	node c;
	c.ma=max(a.ma,b.ma);
	c.mi=min(a.mi,b.mi);
	return c;
}
void pushup(int cur)
{
	t[cur]=merge(t[cur<<1],t[cur<<1|1]);
}
void build(int cur,int l,int r)
{
	if(l==r)
	{
		t[cur]={a[l],a[l]};
		return ;
	}
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	pushup(cur);
}
node query(int cur,int l,int r,int x,int y)
{
	if(x<=l&&y>=r)
	{
		return t[cur];
	}
	if(y<=mid)return query(cur<<1,l,mid,x,y);
	else if(x>=mid+1)return query(cur<<1|1,mid+1,r,x,y);
	return merge(query(cur<<1,l,mid,x,y),query(cur<<1|1,mid+1,r,x,y));
}
char s[maxn];
bool vis[maxn];//vis数组没有用
void solve()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	cin>>s+1;
	int cnt=0;
	for(int i=1;i<n;i++)
	{
		if(s[i]=='L'&&s[i+1]=='R')
		{
			node l=query(1,1,n,1,i);
			node r=query(1,1,n,i+1,n);
			if(l.ma>i||r.mi<=i)
			{
				vis[i]=true;
				cnt++;
			}
		}
	}
	while(q--)
	{
		int p;
		cin>>p;
		int i=p;
		if(s[p]=='L'&&s[p+1]=='R')
		{
			node l=query(1,1,n,1,i);
			node r=query(1,1,n,i+1,n);
			if(l.ma>i||r.mi<=i)
			{
				vis[i]=false;
				cnt--;
			}
		}
		i=p-1;
		if(s[p-1]=='L'&&s[p]=='R')
		{
			node l=query(1,1,n,1,i);
			node r=query(1,1,n,i+1,n);
			if(l.ma>i||r.mi<=i)
			{
				vis[i]=false;
				cnt--;
			}
		}
		if(s[p]=='L')s[p]='R';
		else s[p]='L';
		i=p;
		if(s[p]=='L'&&s[p+1]=='R')
		{
			node l=query(1,1,n,1,i);
			node r=query(1,1,n,i+1,n);
			if(l.ma>i||r.mi<=i)
			{
				vis[i]=false;
				cnt++;
			}
		}
		i=p-1;
		if(s[p-1]=='L'&&s[p]=='R')
		{
			node l=query(1,1,n,1,i);
			node r=query(1,1,n,i+1,n);
			if(l.ma>i||r.mi<=i)
			{
				vis[i]=false;
				cnt++;
			}
		}
		if(!cnt)printf("YES\n");
		else printf("NO\n");
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}

```

---

## 作者：jr_inf (赞：3)

如果存在一个形如 `RXL` 的子串（其中 `X` 可以为任意字符），那么这三个数的位置可以随意交换，说明交换具有传递性。于是我们可以把排列分成若干连续段，满足段内的数可以随意交换，而不同段的数无法交换。这时相邻两段一定以 `LR` 分割。如果存在 $p_i$ 与 $p_{p_i}$ 不在同一段内，则答案为 `No`，否则为 `Yes`。

实现上，首先预处理出所有在 $p_i$ 与 $p_{p_i}$ 之间的**间隔**，然后维护所有分隔的位置，判断这些分割是否与某个间隔重合即可。单次查询只会改变左右两边的状态，所以是 $O(1)$ 的。总时间复杂度 $O(\sum n+\sum q)$。

code：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2e5+10;
int t,n,q,a[N],b[N],c[N],cnt;
string s;
bool upt(int x)
{
	if(x>=n||x<1)return 0;
	return b[x]&&!c[x]&&c[x+1];
}
void add(int l,int r)
{
	if(l>r)swap(l,r);
	b[l]++,b[r]--;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cnt=0;
		cin>>n>>q;
		for(int i=1;i<=n;i++)b[i]=0;
		for(int i=1;i<=n;i++)cin>>a[i],add(i,a[i]);
		for(int i=1;i<=n;i++)b[i]+=b[i-1];
		cin>>s;
		for(int i=0;i<n;i++)c[i+1]=(s[i]=='R');
		for(int i=1;i<n;i++)cnt+=upt(i);
		while(q--)
		{
			int x;
			cin>>x;
			cnt-=upt(x)+upt(x-1);
			c[x]^=1;
			cnt+=upt(x)+upt(x-1);
			puts(cnt?"NO":"YES");
		}
	}
}
```

---

## 作者：xyin (赞：1)

首先可以把每对逆序对所在的位置看成一个区间，该区间一定得满足：可以从左/右端点交换到右/左端点。同时我们手模也可以发现，如果一个数能从左端点交换到右端点，那么右端点的数一定也能交换到左端点。我们可以先预处理出这些逆序对的区间并，判断是否合法时只需判断这些区间是否合法。

什么样的区间是合法的？两种思考方向：

1. 如果有两个相连的字符为 $LR$，则这两个字符左边的数一定不能交换到右边，这两个字符右边的数一定不能交换到左边。
        
    这个比较好维护，每次维护整个字符串中 $LR$ 的数量记为 $tot$，每次修改时 $tot$ 的变化都是 $O(1)$ 的，字符串合法时当且仅当 $tot=0$。复杂度瓶颈在于预处理区间并，我用的 set 维护，时间复杂度 $O(n\log n+q)$。

2. 什么时候一个数能交换到它该去的位置？一定是形如 $x_1RRRLLLLx_2$ 时，此时 $x_1$ 能交换到 $x_2$，$x_2$ 也能交换到 $x_1$。形式化的，$x_1$ 和 $x_2$ 间连续的一段一定能划分成左右两部分，其中左部分全为 $R$，右部分全为 $L$（左区间和右区间的长度都可以为空）。
        
    记录不合法的区间数量为 $tot$，用线段数维护区间内 $R$ 的数量和 $L$ 的数量，支持单点修改和区间查询。我们要判断区间 $(l,r)$ 是否合法，只需查询 $(l,r)$ 内 $R$ 的个数记为 $sum$，如果 $(l+sum,r)$ 内 $L$ 的个数不等于 $r-l+1-sum$，则该区间非法，否则合法。同样的，每次修改时 $tot$ 的变化都是 $O(1)$ 的，字符串合法时当且仅当 $tot=0$。时间复杂度为 $O((n+q)\log n)$，代码也比上面的复杂。

[这里给出第二种思考方向的代码，可以参考对拍](https://www.luogu.com.cn/paste/tsunrshy)

---

## 作者：Aegleseeker_ (赞：1)

题目中的交换是连续的，也就是说如果想从 $p_i$ 交换到 $i$，必须保证 $[\min(p_i,i),\max(p_i,i)]$ 这个区间内是“连通”的，即区间中任意 $k$ 都能交换到 $k+1$。

我们考虑一个区间什么时候不连通。不难发现当区间内存在 `LR` 子串时，该区间不连通。因为 `L` 只能负责往左交换，`R` 只能负责往右交换，到这就断开了，所以该区间不“连通”，无法使排列单调。

现在做法显然易见了，我们维护 $p_i$ 要去哪，那么这个交换所要经过的区间是必须得连通的。我们利用差分，求出哪些点不能和其相邻的点出现 `LR` 子串，我门称之为“关键点”。询问的时候，动态维护 $cnt$，即还有多少个“关键点”。判断 $cnt=0$ 即可。

---

## 作者：myyyIisq2R (赞：1)

要把一个排列移成单调递增的形式其实要求每个数的移动区间内必不能出现形如 `LR` 的子段。那么题目的本质就是给出 $n$ 个区间，维护一个由 $L,R$ 构成的字符串，询问所有给定区间中是否出现了 `LR` 这一子串。

我们可以预处理出每一个位置有多少个区间包含它，每次查询就是看改变字符串有没有新增 `LR` 并且被某一区间包含。

可以通过差分预处理每一个位置有多少覆盖区间，用 `set` 维护所有被区间包含的 `LR` 子段。若 `set` 为空输出 `YES`，否则输出 `NO`，复杂度 $O(T(n+m \log n))$。

```cpp
while(T--)
{
    int n = read(),m = read();
    memset(d,0,sizeof(int)*(n+1));
    for(int i{1};i<=n;i++)
    {
      p[i] = read();
      int l = i,r = p[i];
      if(p[i] == i) continue;
      if(l > r) swap(l,r);
      d[l]++,d[r]--;
    }
    for(int i{1};i<=n;i++) d[i] += d[i-1];
    cin>>s;
    s = "="+s;
    set<int>q;
    for(int i{1};i<n;i++)
      if(s[i] == 'L' && s[i+1] == 'R' && d[i]) 
      q.insert(i);
    while(m--)
    {
      int pos= read();
      if(s[pos] == 'L') 
      {
        s[pos] = 'R';
        if(pos < n && s[pos+1] == 'R') if(q.count(pos)) q.erase(pos);
        if(pos > 1 && s[pos-1] == 'L') if(d[pos-1]) q.insert(pos-1);
      }
      else 
      {
        s[pos] = 'L';
        if(pos > 1 && s[pos-1] == 'L') if(q.count(pos-1)) q.erase(pos-1);
        if(pos < n && s[pos+1] == 'R') if(d[pos]) q.insert(pos);
      }
      
      if(q.size()) puts("NO");
      else puts("YES");
    }
}
```

---

## 作者：Priestess_SLG (赞：1)

考虑一个非常食的写法。

首先观察性质，若存在 $i\in[1,n)\cap\mathbb{N_+}$，$s_i$ 为 `L` 且 $s_{i+1}$ 为 `R` 则 $[1,i]$ 区间中任何一个数都不能移动到 $[i+1,n]$ 区间，反之同理。

因此考虑维护若干个连续段 $[l_1,r_1],[l_2,r_2],\ldots,[l_k,r_k]$ 满足每一个连通块内所有元素都可以互相交换，且任意两个不同的连通块内任意元素都无法互相交换。

然后考虑什么样的序列可以被排序。对于每一个连通块 $[l,r]$，若该区间想要在排序之后所有元素都位于正确的位置，则需要满足该连通块内初始元素恰好为 $l,l+1,l+2,\ldots,r$。又因为该区间内恰好有 $r-l+1$ 个元素，所以只需要满足：

+ 区间内最大值为 $r$。
+ 区间内最小值为 $l$。

使用 ~~SJH Table~~ ST 表维护区间最值，即可做到 $O(n\log n)$ 预处理 $O(1)$ 求区间最值。

但是问题是本题还带单点修改，因此考虑使用 set 来维护每一个这样的连续段，修改一个点的值的时候只需要在 set 上暴力分裂合并所有区间，因此总的时间复杂度为 $O(n\log n)$，可以通过。

代码有很多的情况，十分难写，~~但是我赛时 $10$ 分钟想 $15$ 分钟一遍写过了~~。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N=200100;
char s[N];
int a[N],f[N][20],g[N][20],lg[N],b[N];
int qu(int l,int r){
    int len=lg[r-l+1];
    return max(f[l][len],f[r-(1ll<<len)+1][len]);
}
int qw(int l,int r){
    int len=lg[r-l+1];
    return min(g[l][len],g[r-(1ll<<len)+1][len]);
}
signed main(){
    lg[0]=-1;
    for(int i=1;i<N;++i)lg[i]=lg[i/2]+1;
    int T;cin>>T;
    while(T--){
        int n,q;cin>>n>>q;
        for(int i=1;i<=n;++i)cin>>a[i];
        scanf("%s",s+1);
        for(int i=1;i<=n;++i)f[i][0]=g[i][0]=a[i];
        for(int i=1;i<20;++i)for(int j=1;j<=n-(1ll<<i)+1;++j)
        f[j][i]=max(f[j][i-1],f[j+(1ll<<(i-1))][i-1]),g[j][i]=min(g[j][i-1],g[j+(1ll<<(i-1))][i-1]);
        int c1=0,c2=0;
        vector<int>poss;
        poss.eb(0);
        for(int i=1;i<n;++i){
            if(s[i]=='L'&&s[i+1]=='R')b[i]=1;else b[i]=0;
            if(s[i]=='L'&&s[i+1]=='R')poss.eb(i);
        }
        poss.eb(n);
        set<pair<int,int>>seg;
        for(int i=1;i<poss.size();++i){
            seg.insert({poss[i-1]+1,poss[i]});
            int qmi=qw(poss[i-1]+1,poss[i]),qmx=qu(poss[i-1]+1,poss[i]);
            if(qmi==poss[i-1]+1&&qmx==poss[i])++c1;
            else ++c2;
        }
        // for(auto &[l,r]:seg)cout<<"["<<l<<","<<r<<"] ";
        //     cout<<'\n';
        while(q--){
            int o;cin>>o;
            if(s[o]=='L'){
                // cout<<"#1\n";
                if(o!=n&&s[o+1]=='R'){
                    auto it=seg.lower_bound({o+1,0ll});
                    auto it1=it;--it1;
                    auto [l,r]=*it;
                    int qmi=qw(l,r),qmx=qu(l,r);
                    if(qmi==l&&qmx==r)--c1;
                    else --c2;
                    auto [L,R]=*it1;
                    qmi=qw(L,R),qmx=qu(L,R);
                    if(qmi==L&&qmx==R)--c1;
                    else --c2;
                    seg.erase(it),seg.erase(it1);
                    qmi=qw(L,r),qmx=qu(L,r);
                    if(qmi==L&&qmx==r)++c1;
                    else ++c2;
                    seg.insert({L,r});
                }
                if(o!=1&&s[o-1]=='L'){
                    // cout<<"#3\n";
                    auto it=seg.lower_bound({o,0ll});--it;
                    auto [l,r]=*it;seg.erase(it);
                    if(qw(l,r)==l&&qu(l,r)==r)--c1;
                    else --c2;
                    if(qw(l,o-1)==l&&qu(l,o-1)==o-1)++c1;
                    else ++c2;
                    if(qw(o,r)==o&&qu(o,r)==r)++c1;
                    else ++c2;
                    seg.insert({l,o-1});
                    seg.insert({o,r});
                }
            }else{
                if(o!=1&&s[o-1]=='L'){
                    auto it=seg.lower_bound({o,0ll});
                    auto it1=it;--it1;
                    auto [l,r]=*it;
                    int qmi=qw(l,r),qmx=qu(l,r);
                    if(qmi==l&&qmx==r)--c1;
                    else --c2;
                    auto [L,R]=*it1;
                    qmi=qw(L,R),qmx=qu(L,R);
                    if(qmi==L&&qmx==R)--c1;
                    else --c2;
                    seg.erase(it),seg.erase(it1);
                    qmi=qw(L,r),qmx=qu(L,r);
                    if(qmi==L&&qmx==r)++c1;
                    else ++c2;
                    seg.insert({L,r});
                }
                if(o!=n&&s[o+1]=='R'){
                    auto it=seg.lower_bound({o+1,0ll});--it;
                    auto [l,r]=*it;seg.erase(it);
                    if(qw(l,r)==l&&qu(l,r)==r)--c1;
                    else --c2;
                    if(qw(l,o)==l&&qu(l,o)==o)++c1;
                    else ++c2;
                    if(qw(o+1,r)==o+1&&qu(o+1,r)==r)++c1;
                    else ++c2;
                    seg.insert({l,o});
                    seg.insert({o+1,r});
                }
            }
            // for(auto &[l,r]:seg)cout<<"["<<l<<","<<r<<"] ";
            // cout<<'\n';
            // cout<<c1<<' '<<c2<<'\n';
            // if(s[o]=='L'){
            //     if(o!=n&&s[o+1]=='R'){
            //         modify(1,n-1,1,o,0);
            //     }
            //     if(o!=1&&s[o-1]=='L'){
            //         modify(1,n-1,1,o-1,1);
            //     }
            // }else{
            //     if(o!=n&&s[o+1]=='R'){
            //         modify(1,n-1,1,o,1);
            //     }
            //     if(o!=1&&s[o-1]=='L'){
            //         modify(1,n-1,1,o-1,0);
            //     }
            // }
            if(s[o]=='L')s[o]='R';else s[o]='L';
            if(c2==0)cout<<"YES\n";else cout<<"NO\n";
        }
    }
}
```

---

## 作者：I_will_AKIOI (赞：1)

由于作者很菜，文章中若有出现笔误欢迎在评论区纠正。

我们把由一些 `R` 加上一些 `L` 组成的极长连续段叫做块，例如 $\text{RRLL}$ 是一个块，块的左右端点为 $l,r$，令这个块中最右边的 $\text{R}$ 的位置为 $mid$。首先我们发现在一个块中，可以交换相邻的两个数，于是就相当于在进行冒泡排序，也就是说，只需要判断每个块的数排序后是否是 $[l,r]$，由于 $p$ 为排列，因此只需要查询区间最小值和区间最大值，就能判断这个块是否合法，这个操作可以使用 ST 表来完成。

接着考虑单点修改后，块会怎么变化，画图枚举一下所有情况，发现会有分裂块、合并块等操作，于是用 set 维护一下每个块的信息，我们设修改的位置为 $x$，首先需要找到 $x$ 属于的块，才能进行修改，但是我们无法直接找到，因此需要维护每个块的左右端点，再开两个 set 维护，用 `s.lower_bound()` 或 `s.find()` 函数找到 $x$ 所属块的左右端点，然后组成一个新的块进行查询。接着具体的操作见下文。

情况一：修改块的左端点。

+ 子情况一：$x$ 的左边是 $\text{L}$，右边是 $\text{R}$。例如 $s=\text{RRLLRLL},x=5$，此时把 $s_5$ 变为 $\text{L}$ 后，$s$ 变为 $\text{RRLLLLL}$，会发现第一个块和第二个块合并了，也就是会和前一个块合并。

+ 子情况二：即不属于子情况一的其他情况，例如 $s=\text{RRLLRRLL},x=5$，把 $s_5$ 变为 $\text{L}$ 后，$s$ 变为 $\text{RRLLLRLL}$，会发现第一个块和第二个块本来是 $[1,4]$ 和 $[5,8]$，现在变为 $[1,x]$ 和 $[x+1,8]$，也就是把 $s_x$ 分给了前一个块。

情况二：修改块的右端点。

+ 子情况一：$x$ 的左边是 $\text{L}$，右边是 $\text{R}$。例如 $s=\text{RRLRRLL},x=3$，此时把 $s_3$ 变为 $\text{R}$ 后，$s$ 变为 $\text{RRRRLL}$，会发现第一个块和第二个块合并了，也就是会和下一个块合并。

+ 子情况二：即不属于子情况一的其他情况，例如 $s=\text{RRLLRRLL},x=4$，把 $s_4$ 变为 $\text{R}$ 后，$s$ 变为 $\text{RRLRRRLL}$，会发现第一个块和第二个块本来是 $[1,4]$ 和 $[5,8]$，现在变为 $[1,x-1]$ 和 $[x+1,8]$，也就是把 $s_x$ 分给了下一个块。

情况三：修改块的 $mid$ 或 $mid+1$。

例如 $s=\text{RRLL}$，其中 $mid=2$，会发现修改 $s_2$ 或 $s_3$ 后，块的情况不变。

情况四：修改块的其他部分，也就是不属于情况一、二、三的情况。

+ 子情况一：$s_x=\text{R}$。例如 $s=\text{RRRLLL},x=2$，把 $s_2$ 变为 $\text{L}$ 后，$s$ 变为 $\text{RLRLLL}$，会发现本来一个块 $[1,6]$，变成了 $[1,x]$ 和 $[x+1,6]$，也就是把块从 $x$ 的地方分裂了，$x$ 属于第一个块。

+ 子情况二：$s_x=\text{L}$。例如 $s=\text{RRRLLL},x=4$，把 $s_4$ 变为 $\text{R}$ 后，$s$ 变为 $\text{RRRLRL}$，会发现本来一个块 $[1,6]$，变成了 $[1,x-1]$ 和 $[x,6]$，也就是把块从 $x-1$ 的地方分裂了，$x$ 属于第二个块。

进行八种大力分讨之后，本题就做完了，复杂度为 $O(q\log n)$，但是常数超级大，而且难写难调，千万不要学习。在分讨中找前一个区间或后一个可以先用 `s.find()` 找到所属区间，然后利用迭代器的前移一位和后移一位来寻找，其中也别忘记更新合法块个数和每个块的左右端点。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#define N 200005
using namespace std;
struct Data
{
	int l,r;
	bool ok;//块是否合法
	bool operator<(const Data &w)const{return w.l<l;}
	bool operator>(const Data &w)const{return w.l>l;}
};//记录块的结构体，需要重载运算符
int n,q,sum,a[N],maxx[20][N],minn[20][N],Log[N];
char c[N];
set<Data,greater<Data> >s;//存储每个块
set<int>s1,s2;//存储左右端点
int qmaxx(int l,int r)//区间最大值
{
	int s=Log[r-l+1];
  return max(maxx[s][l],maxx[s][r-(1<<s)+1]);
}
int qminn(int l,int r)//区间最小值
{
	int s=Log[r-l+1];
  return min(minn[s][l],minn[s][r-(1<<s)+1]);
}
bool check(int l,int r)//判断[l,r]是否合法
{
	if(qmaxx(l,r)==r&&qminn(l,r)==l) return 1;
	return 0;
}
void solve()
{
	s.clear(),s1.clear(),s2.clear();
	sum=0;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],maxx[0][i]=minn[0][i]=a[i];
	for(int i=1;(1<<i)<=n;i++) for(int j=1;j+(1<<i)-1<=n;j++) maxx[i][j]=max(maxx[i-1][j],maxx[i-1][j+(1<<i-1)]),minn[i][j]=min(minn[i-1][j],minn[i-1][j+(1<<i-1)]);
  //建立 ST 表
	for(int i=1;i<=n;i++) cin>>c[i];
	int l=1,r=1;
	while(l<=n)//预处理出每个块
	{
		Data w;
		while(c[r]!='L') r++;
		while(r<n&&c[r+1]!='R') r++;
		int maxx=qmaxx(l,r),minn=qminn(l,r);
		w.l=l,w.r=r,w.ok=check(l,r);
		sum+=w.ok;
		s.insert(w);
		s1.insert(l),s2.insert(r);
		r++,l=r;
	}
	while(q--)
	{
		int x;
		cin>>x;
		auto lt=s1.upper_bound(x),rt=s2.lower_bound(x);
		lt--;
		auto it=s.find(Data{*lt,*rt,check(*lt,*rt)});
		if(*lt==x)//情况一
		{
			if(c[x]!=c[x-1]&&c[x]!=c[x+1])//子情况一
			{
				auto pre=it;
				pre--;
				Data w;
				w.l=(*pre).l,w.r=(*it).r,w.ok=check(w.l,w.r);
				s1.erase((*pre).l),s1.erase((*it).l);
				s1.insert(w.l);
				s2.erase((*pre).r),s2.erase((*it).r);
				s2.insert(w.r);
				if((*it).ok) sum--;
				if((*pre).ok) sum--;
				if(w.ok) sum++;
				s.erase(*it),s.erase(*pre);
				s.insert(w);
			}
			else//子情况二
			{
				auto pre=it;
				pre--;
				Data w1,w2;
				w1.l=(*pre).l,w1.r=x,w1.ok=check(w1.l,w1.r);
				w2.l=x+1,w2.r=(*it).r,w2.ok=check(w2.l,w2.r);
				s1.erase((*pre).l),s1.erase((*it).l);
				s1.insert(w1.l),s1.insert(w2.l);
				s2.erase((*pre).r),s2.erase((*it).r);
				s2.insert(w1.r),s2.insert(w2.r);
				if((*it).ok) sum--;
				if((*pre).ok) sum--;
				if(w1.ok) sum++;
				if(w2.ok) sum++;
				s.erase(*it),s.erase(*pre);
				s.insert(w1),s.insert(w2);
			}
		}
		else if(*rt==x)//情况二
		{
			if(c[x]!=c[x-1]&&c[x]!=c[x+1])//子情况一
			{
				auto nxt=it;
				nxt++;
				Data w;
				w.l=(*it).l,w.r=(*nxt).r,w.ok=check(w.l,w.r);
				s1.erase((*it).l),s1.erase((*nxt).l);
				s1.insert(w.l);
				s2.erase((*it).r),s2.erase((*nxt).r);
				s2.insert(w.r);
				if((*it).ok) sum--;
				if((*nxt).ok) sum--;
				if(w.ok) sum++;
				s.erase(*it),s.erase(*nxt),s.insert(w);
			}
			else//子情况二
			{
				auto nxt=it;
				nxt++;
				Data w1,w2;
				w1.l=(*it).l,w1.r=x-1,w1.ok=check(w1.l,w1.r);
				w2.l=x,w2.r=(*nxt).r,w2.ok=check(w2.l,w2.r);
				s1.erase((*nxt).l),s1.erase((*it).l);
				s1.insert(w1.l),s1.insert(w2.l);
				s2.erase((*nxt).r),s2.erase((*it).r);
				s2.insert(w1.r),s2.insert(w2.r);
				if((*it).ok) sum--;
				if((*nxt).ok) sum--;
				if(w1.ok) sum++;
				if(w2.ok) sum++;
				s.erase(*it),s.erase(*nxt);
				s.insert(w1),s.insert(w2);
			}
		}
		else if(c[x]=='R')
		{
			if(c[x+1]!='L')//情况四的子情况一，情况三由于不涉及修改块的信息所以省略不写
			{
				Data w1,w2;
				w1.l=(*it).l,w1.r=x,w1.ok=check(w1.l,w1.r);
				w2.l=x+1,w2.r=(*it).r,w2.ok=check(w2.l,w2.r);
				s1.erase((*it).l);
				s1.insert(w1.l),s1.insert(w2.l);
				s2.erase((*it).r);
				s2.insert(w1.r),s2.insert(w2.r);
				if((*it).ok) sum--;
				if(w1.ok) sum++;
				if(w2.ok) sum++;
				s.erase(*it);
				s.insert(w1),s.insert(w2);
			}
			
		}
		else if(c[x]=='L')
		{
			if(c[x-1]!='R')//情况四的子情况二
			{
				Data w1,w2;
				w1.l=(*it).l,w1.r=x-1,w1.ok=check(w1.l,w1.r);
				w2.l=x,w2.r=(*it).r,w2.ok=check(w2.l,w2.r);
				s1.erase((*it).l);
				s1.insert(w1.l),s1.insert(w2.l);
				s2.erase((*it).r);
				s2.insert(w1.r),s2.insert(w2.r);
				if((*it).ok) sum--;
				if(w1.ok) sum++;
				if(w2.ok) sum++;
				s.erase(*it);
				s.insert(w1),s.insert(w2);
			}
		}
		if(c[x]=='R') c[x]='L';
		else c[x]='R';
		//别忘记修改原来的数组
		if(sum==s.size()) cout<<"YES\n";//所有块都合法
		else cout<<"NO\n";
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	for(int i=2;i<=200000;i++) Log[i]=Log[i>>1]+1;
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Pursuewind (赞：1)

# 题意

给定一个字符串 $S$（下标从 $1$ 开始），和一个长度为 $n$ 的 $1 \sim n$ 的排列 $p$，你需要进行若干次操作，使得 $p$ 上升，操作如下：

- 如果 $S_i=\text{L}$，你可以选择交换 $p_i$，$p_{i-1}$。

- 如果 $S_i=\text{R}$，你可以选择交换 $p_i$，$p_{i+1}$。

你有 $q$ 次更改，每次给出 $x,c$，将 $S_x$ 更改为字符 $c$，然后询问在当前的 $S$ 下，能否将 $p$ 变成上升的。

# 题解

不难发现，相邻的两个数 $i,i+1$（$1 \le i < n$），如果不能交换他们，当且仅当 $S_i=\text{L}$，$S_j=\text{R}$。

所以，如果 $S_i=\text{L}$ 且 $S_{i+1}=\text{R}$（$1 \le i < n$），而且 $1 \sim i$ 与 $i+1 \sim n$ 中存在逆序对，换句话说，如果$\max\limits_{o=1}^i p_o>\min\limits_{o=i+1}^n$，那么你不能将 $p$ 变成上升的。

由于 $p$ 是不带修的，我们可以预处理出每个位置 $i$，是否满足 $\max\limits_{o=1}^i p_o>\min\limits_{o=i+1}^n$。首先预处理初始的答案，然后发现每次修改只会影响 $i=x-1$ 与 $i=x$，对这两个位置处理即可。

细节有点多，可以结合代码理解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N], pre_max[N], per_min[N];
char s[N];
bool vis[N], can[N];
int n, m;
void solve(){
	cin >> n >> m;
	for (int i = 1; i <= n; i ++){
		cin >> a[i];
		vis[i] = can[i] = 0;
	}
	cin >> s + 1;
	pre_max[1] = a[1];
	per_min[n] = a[n];
	for (int i = 2; i <= n; i ++){
		pre_max[i] = max(pre_max[i - 1], a[i]); 
	}
	for (int i = n - 1; i >= 1; i --){
		per_min[i] = min(per_min[i + 1], a[i]);
	}
	for (int i = 1; i < n; i ++){
		if (pre_max[i] > per_min[i + 1]) vis[i] = 1;
	}
	int sum = 0;
	for (int i = 1; i < n; i ++){
		if (s[i] == 'L' && s[i + 1] == 'R'){
			can[i] = vis[i];
		} 
		sum += can[i];
	}
	while (m --){
		int x;
		cin >> x;
		s[x] = (s[x] == 'R' ? 'L' : 'R');
		if (x == 1){
			if (s[2] == 'R'){
				if (s[1] == 'R'){
					sum -= can[1];
					can[1] = 0;
				}
				else{
					can[1] = vis[1];
					sum += vis[1];
				}
			}
		}
		else if (x == n){
			if (s[n - 1] == 'L'){
				if (s[n] == 'L'){
					sum -= can[n - 1];
					can[n - 1] = 0;
				}
				else{
					can[n - 1] = vis[n - 1];
					sum += vis[n - 1];
				}
			}
		}
		else{
			if (s[x + 1] == 'R'){
				if (s[x] == 'R'){
					sum -= can[x];
					can[x] = 0;
				}
				else{
					can[x] = vis[x];
					sum += vis[x];
				}
			}
			if (s[x - 1] == 'L'){
				if (s[x] == 'L'){
					sum -= can[x - 1];
					can[x - 1] = 0;
				}
				else{
					can[x - 1] = vis[x - 1];
					sum += vis[x - 1];
				}
			}
		}
		if (sum) cout << "NO\n";
		else cout << "YES\n";
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
```

---

## 作者：MightZero (赞：1)

### Solution
首先我们可以发现题目给出的两种转移实际上都是双向的，因此可以考虑排列中的每个元素所能到达的位置，构造无向图；对于每个位置，若 $s_i = L$，连边 $i \leftrightarrow i-1$，否则连边 $i \leftrightarrow i+1$。

注意到给定的 $s$ 中存在的形如 `LR` 的子串将图分割成若干个连通块；若排列可以通过交换被单调递增排序，则对于每个连通块 $[l,r]$，$\{ p_l,p_{l+1},\cdots,p_r \}$ 排序后得到的序列必然为 $\{ l,l+1,\cdots,r\}$。

那么对于每次修改，只需要维护连通块的变化并且判断每个连通块是否符合条件即可；对于连通块的维护，可以使用 `ODT` 维护区间的合并与分裂；快速判断连通块是否满足条件可以通过和哈希解决，用 `set` 存储所有不合法的连通块即可。

同时，可以注意到在本题中如果维护连通块的元素和，必然不存在两组不同的排列使得所有连通块的的元素和都与元素下标之和相等；因此也可以直接维护前缀和判断是否满足条件而不必使用和哈希（本人太菜了没看出来）。

### Code

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
const ll N=2e5+5;
const ll mod=1e9+7,M=30;
char s[N];
ll p[N],n,q;
struct _hash
{
    ll _val[M];
    _hash(){loop(i,0,M-1)_val[i]=0;}
    _hash(ll x){_val[0]=1;loop(i,1,M-1)_val[i]=(_val[i-1]*x)%mod;}
    inline _hash operator+(const _hash& hs)
    {
        _hash res;
        loop(i,0,M-1)res._val[i]=(_val[i]+hs._val[i])%mod;
        return res;
    }
    inline _hash operator-(const _hash& hs)
    {
        _hash res;
        loop(i,0,M-1)res._val[i]=(_val[i]-hs._val[i]+mod)%mod;
        return res;
    }
    inline bool operator==(const _hash& hs)
    {
        loop(i,0,M-1)if(_val[i]!=hs._val[i])return 0;
        return 1;
    }
}hs1[N],hs2[N];
set<ll> odt,unv;
void solve()
{
    odt.clear();
    unv.clear();
    n=read(),q=read();
    loop(i,0,n+1)hs1[i]=_hash(),hs2[i]=_hash();
    loop(i,1,n)p[i]=read(),hs1[i]=hs1[i-1]+_hash(p[i]);
    loop(i,1,n)hs2[i]=hs2[i-1]+_hash(i);
    odt.insert(n+1);
    odt.insert(1);
    scanf("%s",s+1);
    loop(i,1,n-1)
    {
        if(s[i]=='L'&&s[i+1]=='R')
        {
            odt.insert(i+1);
            auto it=odt.lower_bound(i+1);
            it--;
            ll pre=*it;
            if(hs1[i]-hs1[pre-1]==hs2[i]-hs2[pre-1]);
            else unv.insert(pre);
        }
    }
    auto _it=odt.lower_bound(n+1);
    _it--;
    ll _pre=*_it;
    if(hs1[n]-hs1[_pre-1]==hs2[n]-hs2[_pre-1]);
    else unv.insert(_pre);
    while(q--)
    {
        ll p=read();
        if(s[p]=='L'&&s[p+1]=='R')
        {
            assert(odt.count(p+1));
            auto it=odt.lower_bound(p+1);
            auto itn=it;
            it--,itn++;
            ll pre=*it,nxt=*itn;
            unv.erase(p+1);
            unv.erase(pre);
            odt.erase(p+1);
            if(hs1[nxt-1]-hs1[pre-1]==hs2[nxt-1]-hs2[pre-1]);
            else unv.insert(pre);
        }
        if(s[p]=='R'&&s[p-1]=='L')
        {
            assert(odt.count(p));
            auto it=odt.lower_bound(p);
            auto itn=it;
            it--,itn++;
            ll pre=*it,nxt=*itn;
            unv.erase(p);
            unv.erase(pre);
            odt.erase(p);
            if(hs1[nxt-1]-hs1[pre-1]==hs2[nxt-1]-hs2[pre-1]);
            else unv.insert(pre);
        }
        if(s[p]=='L'&&s[p-1]=='L')
        {
            odt.insert(p);
            auto it=odt.lower_bound(p);
            auto itn=it;
            it--,itn++;
            ll pre=*it,nxt=*itn;
            unv.erase(pre);
            if(hs1[nxt-1]-hs1[p-1]==hs2[nxt-1]-hs2[p-1]);
            else unv.insert(p);
            if(hs1[p-1]-hs1[pre-1]==hs2[p-1]-hs2[pre-1]);
            else unv.insert(pre);
        }
        if(s[p]=='R'&&s[p+1]=='R')
        {
            odt.insert(p+1);
            auto it=odt.lower_bound(p+1);
            auto itn=it;
            it--,itn++;
            ll pre=*it,nxt=*itn;
            unv.erase(pre);
            if(hs1[nxt-1]-hs1[p]==hs2[nxt-1]-hs2[p]);
            else unv.insert(p+1);
            if(hs1[p]-hs1[pre-1]==hs2[p]-hs2[pre-1]);
            else unv.insert(pre);
        }
        if(s[p]=='L')s[p]='R';
        else s[p]='L';
        puts(unv.size()?"No":"Yes");
    }
}
signed main()
{
    ll T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

简单观察发现，操作很强大，只有当出现 `LR` 时，才会将两个区域隔开，然后如果后缀 `min` 小于这个位置，那么这个 `LR` 就使实现不可能了，当且仅当这样的 `LF` 数量为 $0$ 时，可以实现，于是直接维护一个后缀 `min`，修改判断即可。前缀 `max` 同理，时间复杂度 $\mathcal{O}(n)$。
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int R(int n){return myrand()%n+1;}
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10,mod=998244353,inf=1e9;
inline void Min(int &x,int y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
int n,q,min[N],a[N];
char s[N];
bool vis[N];
signed main(){
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    int T;std::cin>>T;
    while(T--){
        std::cin>>n>>q;
        int num=0;
        for(int i=1;i<=n;++i)std::cin>>a[i],vis[i]=0;
        min[n]=a[n];for(int i=n-1;i;--i)min[i]=std::min(min[i+1],a[i]);
        std::cin>>s+1;
        for(int i=n;i>1;--i){
            if(s[i]=='R'&&s[i-1]=='L'){
                if(min[i]<i)vis[i]=1,num++;
            }
        }
        while(q--){
            int x;std::cin>>x;
            if(s[x]=='L')s[x]='R';
            else s[x]='L';
            if(vis[x]){
                vis[x]=0;num--;
            }
            if(vis[x+1]){
                vis[x+1]=0;num--;
            }
            if(s[x+1]=='R'&&s[x]=='L'){
                if(min[x+1]<x+1)vis[x+1]=1,num++;
            }
            if(s[x]=='R'&&s[x-1]=='L'){
                if(min[x]<x)vis[x]=1,num++;
            }
            if(num){
                std::cout<<"NO\n";
            }else{
                std::cout<<"YES\n";
            }
        }
    }   
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2030D)

# 前置知识

[差分](https://oi-wiki.org//basic/prefix-sum/#%E5%B7%AE%E5%88%86)

# 解法

对于移动，我们可以无脑进行交换来保证移动，然后将中途交换的位置再交换回去。

通过手摸不难发现，$p_{i}$ 能移动到 $i$ 当且仅当 $s_{\min(i,p_{i}) \sim \max(i,p_{i})}$ 中不含有 ``LR`` 子串。

反向考虑，即 ``LR`` 子串不被上述区间包含，差分判断即可。

# 代码

```cpp
ll a[200010],d[200010];
char s[200010];
int main()
{
	ll t,n,m,x,sum,i,j; 
	cin>>t;
	for(j=1;j<=t;j++)
	{
		cin>>n>>m;
		sum=0;
		for(i=1;i<=n;i++)
		{
			cin>>a[i];
			d[min(a[i],i)]++;
			d[max(a[i],i)]--;
		}
		for(i=1;i<=n;i++)
		{
			d[i]+=d[i-1];
		}
		cin>>(s+1);
		for(i=1;i<=n-1;i++)
		{
			if(s[i]=='L'&&s[i+1]=='R')
			{
				sum+=(d[i]!=0);
			}
		}
		for(i=1;i<=m;i++)
		{
			cin>>x;
			if(s[x]=='L')
			{
				s[x]='R';
				if(x+1<=n&&s[x+1]=='R')
				{
					sum-=(d[x]!=0);
				}
				if(x-1>=1&&s[x-1]=='L')
				{
					sum+=(d[x-1]!=0);
				}
			}
			else
			{
				s[x]='L';
				if(x+1<=n&&s[x+1]=='R')
				{
					sum+=(d[x]!=0);
				}
				if(x-1>=1&&s[x-1]=='L')
				{
					sum-=(d[x-1]!=0);
				}
			}
			if(sum!=0)
			{
				cout<<"No"<<endl;
			}
			else
			{
				cout<<"Yes"<<endl;
			}
		}
		for(i=1;i<=n;i++)
		{
			d[i]=0;
		}
	}
	return 0;
}
```

---

## 作者：zzhbpyy (赞：0)

## 分析

不难发现：若字符串 $s$ 中出现 `LR` 说明排列 $p$ 在此处分为两段，也就是说左边的数不能通过交换移到右边，右边也不能交换到左边。可以先枚举每一个 $i$，用权值树状数组维护 $1\sim i$ 中有几个 $1$ 到 $i$ 之间的数，从而得出是否能从这一位置断开。考虑用 `std::set` 存储所有的 `LR` 字串，删掉可以断开的位置，最后判断集合是否为空即可。

## Code

```c++
#include<bits/stdc++.h>
#define lb(x) ((x)&-(x))
using namespace std;
int n,t,a[200005],tr[200005],q;
bool vis[200005];
string s;
set<int>ss;
void add(int x,int d){
	for(;x<=n;x+=lb(x))tr[x]+=d;
}
int query(int x){
	int ans=0;
	for(;x;x-=lb(x))ans+=tr[x];
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n>>q;ss.clear();
		for(int i=1;i<=n;i++)cin>>a[i],vis[i]=false;
		for(int i=1;i<=n;i++){
			add(a[i],1);
			if(query(i)==i)vis[i]=true;
		}cin>>s;s=' '+s;
		for(int i=1;i<n;i++){
			if(s[i]=='L'&&s[i+1]=='R'&&!vis[i])ss.insert(i);
		}int i;
		while(q--){
			cin>>i;//cerr<<":::__ "<<i<<'\n';
			if(s[i]=='L'){
				if(s[i+1]=='R')ss.erase(i);
				if(s[i-1]=='L'){
					if(!vis[i-1])ss.insert(i-1);
				}s[i]='R';
			}else{
				if(s[i+1]=='R'){if(!vis[i])ss.insert(i);}
				if(s[i-1]=='L')ss.erase(i-1);
				s[i]='L';
			}//cerr<<"debug::"<<*(s.begin())<<'\n';
			cout<<(ss.empty()?"YES":"NO")<<'\n';//cerr<<"";
		}
		for(int i=1;i<=n;i++)add(a[i],-1);
	}
}
```

---

## 作者：zhouruoheng (赞：0)

## D 

### 翻译 

QED 给出一个长度为 $n$ 的排列 $p$ 和字符串 $s$，$s$ 中只包含字符 $\texttt{L}$ 和 $\texttt{R}$。QED 只喜欢按非递减顺序排序的排列。要对 $p$ 排序，他可以选择以下任意操作并执行任意次数：

- 选择一个 $s_i=L$ 下标 $i$，然后，交换 $p_i$ 和 $p_{i-1}$。保证 $s_1 \neq \texttt{L}$。
- 选择一个 $s_i=R$ 下标 $i$，然后，交换 $p_i$ 和 $p_{i+1}$。保证 $s_n \neq \texttt{R}$。

他还给出了 $q$ 个查询。在每个查询中，他会选择一个下标 $i$，并将 $s_i$ 反转，即从 $\texttt{L}$ 改为 $\texttt{R}$ (或从 $\texttt{R}$ 改为 $\texttt{L}$)。这些更改是**永久**的。

每次查询后，他会问你是否可以通过执行上述任意次数的操作，将 $p$ 以非递减的顺序排序。请注意，在回答每个问题之前， $p$ 的排列都会重置为原来的形式。

长度为 $n$ 的排列是由 $n$ 个不同的整数组成的数组，这些整数从 $1$ 到 $n$ 按任意顺序排列。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是一个排列($2$ 在数组中出现了两次)， $[1,3,4]$ 也不是一个排列($n=3$，而数组中有 $4$)

### 分析 

首先 $\texttt{L}$ 和 $\texttt{R}$ 相当于左移和右移，以及我们只需要考虑右移（或左移）即可。

对于每个形如 $\texttt{RRR} \dots \texttt{LLL} \dots$ 的子串 $[l,r]$，其中的 $p_i$($l \le i \le r$) 显然可以到达 $[l,r]$ 中的任一位置，也就是说我们可以任意安排 $[l,r]$ 的顺序。  
可知 $s$ 由多个上述子串构成。

而对于 $1 \le i < n$，若 $s_i=\texttt{L}$ 且 $s_{i+1}=\texttt{R}$，都会在 $i$ 处形成一个断点。也就是说 $[1,i]$ 中的数都不可能右移到 $[i+1,n]$ 的位置。因为只考虑右移，我们只考虑最大值，序列要合法就必须所有的 $[l,r]$ 的最大值小于等于 $r$。

因此我们考虑每个 $\texttt{L} \texttt{R}$，下标为 $i$ 和 $i+1$，如果 $[1,i]$ 的最大值大于 $i$，就说明不可以实现。统计这样不合法的 $\texttt{L} \texttt{R}$ 的个数 $cnt$，等于 $0$ 输出 `YES`。

最后思考修改后会有什么影响，就是看看改之前和改之后是不是 $\texttt{L} \texttt{R}$，更新 $cnt$ 即可。

我用的是 ST 表维护区间最值。

### code 

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,q;
int log_2[N];
int a[N];
string s;
int f[N][25];
void init()
{
    for(int i=1;i<=n;i++) f[i][0]=a[i];
    for(int j=1;j<=20;j++) 
        for(int i=1;i+(1<<j)-1<=n;i++)
            f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
}
int query(int l,int r)
{
    int t=log_2[r-l+1];
    return max(f[l][t],f[r-(1<<t)+1][t]);
}
bool check(int x)
{
    return query(1,x)>x;
}

void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    init();
    cin>>s;
    s='0'+s;
    int cnt=0;
    for(int i=2;i<n;i++)
        if(s[i]=='L'&&s[i+1]=='R') 
            if(check(i))
                cnt++;
    while(q--)
    {
        int x;
        cin>>x;
        if(s[x]=='L')
        {
            s[x]='R';
            if(s[x+1]=='R') if(check(x)) cnt--;
            if(s[x-1]=='L') if(check(x-1)) cnt++;
        }
        else 
        {
            s[x]='L';
            if(s[x-1]=='L') if(check(x-1)) cnt--;
            if(s[x+1]=='R') if(check(x)) cnt++;
        }
        if(!cnt) puts("YES");
        else puts("NO");
    }
}
int main ()
{
    for(int i=2;i<=N-5;i++) log_2[i]=log_2[i/2]+1;
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}

```

---

## 作者：MicroSun (赞：0)

CSP 考前写题解加 rp（

---

发现如果存在一个 $i$ 满足 $i=\texttt{L},i+1=\texttt{R}$，那么 $i$ 及其左边的数无法到达 $i+1$ 或其右边的位置，$i+1$ 及其右边的数无法到达 $i$ 及其左边的位置，那么能使数列有序的充要条件是对于所有满足 $i=\texttt{L},i+1=\texttt{R}$ 的 $i$ 满足 $\max_{j=1}^i p_j<\min_{j=i+1}^n p_j$。发现 $p$ 不会被修改，于是维护一个前缀 $\max$ 和后缀 $\min$，对于每次修改 $\Omicron(1)$ 计算不满足条件的 $i$ 的个数是否为 $0$ 即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;++i)
#define dep(i,s,e) for(int i=s;i>=e;--i)
#define mem(a) memset(a,0,sizeof(a));

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=2e5+10;

ll a[N],mn[N],mx[N];
char s[N];
bool ok[N],able[N];
void solve(){
	int n,q;
	cin>>n>>q;
	rep(i,0,n+1) a[i]=ok[i]=able[i]=mn[i]=mx[i]=s[i]=0;
	rep(i,1,n) cin>>a[i];
	mx[1]=a[1];
	rep(i,2,n) mx[i]=max(mx[i-1],a[i]);
	mn[n]=a[n];
	dep(i,n-1,1) mn[i]=min(mn[i+1],a[i]);
	cin>>(s+1);
	int cnt=0;
	rep(i,1,n-1){
		if(s[i]=='L'&&s[i+1]=='R') ok[i]=1;
		if(mx[i]>mn[i+1]) able[i]=1;
		if(ok[i]&&able[i]) ++cnt;
		//cerr<<ok[i]<<' '<<able[i]<<endl;
	}
	//cerr<<able[4];
	while(q--){
		int u;
		cin>>u;
		if(s[u]=='L') s[u]='R';
		else s[u]='L';
		bool nowok=(s[u]=='L'&&s[u+1]=='R');
		if(able[u]) cnt+=nowok-ok[u];
		ok[u]=nowok;
		nowok=(s[u-1]=='L'&&s[u]=='R');
		if(able[u-1]) cnt+=nowok-ok[u-1];
		ok[u-1]=nowok;
		if(cnt>0) cout<<"NO\n";
		else cout<<"YES\n";
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

考场上一个小时才想出来的做法。

考虑将能交换的两个位置连边，那么整个序列被划分成了若干个区间，在 $i$ 位分开区间当且仅当 $s_i=L$ 且 $s_{i+1}=R$，称 $i$ 为特殊位置。一个区间中的数可以到达任意位置。

$a_i$ 可以到达 $i$ 当且仅当是一个区间的，即中间没有特殊位置。

因此可以预处理出哪些位置不能成为特殊位置，和统计出违法的数量。

用线段树解决即可。

（二）

AC 代码。

```cpp
//2024-10-19 22:52:13
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
using namespace std;
bool MBE;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
const int mxn=2e5+10;
int ans,n,q,a[mxn];
bool tree[mxn<<2];
char s[mxn];
void pushdown(int o){
	if(tree[o])tree[o*2]=tree[o*2+1]=1;
}
void build(int o,int l,int r){
	tree[o]=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(o*2,l,mid),build(o*2+1,mid+1,r);
}
void update(int o,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		tree[o]=1;
		return;
	}
	pushdown(o);
	int mid=(l+r)>>1;
	if(L<=mid)update(o*2,l,mid,L,R);
	if(R>mid)update(o*2+1,mid+1,r,L,R);
}
bool query(int o,int l,int r,int pos){
	if(l==r)return tree[o];
	pushdown(o);
	int mid=(l+r)>>1;
	if(pos<=mid)return query(o*2,l,mid,pos);
	else return query(o*2+1,mid+1,r,pos);
}
int solve(int x){
	if(x==0||x==n)return 0;
	if(!(s[x]=='L'&&s[x+1]=='R'))return 0;
	return query(1,1,n,x);
}
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int T=read();
    while(T--){
    	n=read(),q=read();
    	for(int i=1;i<=n;i++)
    		a[i]=read();
    	build(1,1,n);
    	ans=0;
    	for(int i=1;i<=n;i++){
    		if(i<a[i])update(1,1,n,i,a[i]-1);
    		if(i>a[i])update(1,1,n,a[i],i-1);
    	}
    	scanf("%s",s+1);
    	for(int i=1;i<n;i++){
    		if(s[i]=='L'&&s[i+1]=='R')
    			ans+=query(1,1,n,i);
    	}
    	while(q--){
    		int x=read();
    		ans-=solve(x-1);
    		ans-=solve(x);
    		s[x]='L'+'R'-s[x];
    		ans+=solve(x-1);
    		ans+=solve(x);
    		if(!ans)puts("YES");
    		else puts("NO");
    	}
    }
    bool MED;
    cerr<<(&MED-&MBE)/1048576.0<<" MB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：conti123 (赞：0)

## CF2030D

若第 $i$ 位为 `L` 或第 $i-1$ 位为 `R`，则认为 $i-1$ 和 $i$ 联通。

则可以的充要条件是：$\forall i\in[1,n]$，$i$ 与 $pos_{i}$ 联通。

其中 $pos_{i}$ 为 $i$ 这一权值对应的位置。

换句话说，对于每个连通块 $[l,r]$，应该满足：

$$\min_{i=l}^rp_i=l,\max_{i=l}^rp_i=r$$

由于操纵不改变原排列，考虑先将原序列分成若干连通块。

然后统计出连通块内有多少个地方断开了，更改时判断有没有加上去就行了或者新断开了其它地方。

```cpp
void solve(){
	cin>>n>>m;
	string s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>s;
	s=" "+s;
	int mx=0,mi=1e9,id=0;
	for(int i=1;i<=n;i++){
		mx=max(mx,a[i]);
		if(mx==i)
			while(id<i)
				pos[++id]=i;
	}
	int cnt=0;
	for(int i=2;i<=n;i++){
		if(s[i]=='R'&&s[i-1]=='L'&&pos[i-1]==pos[i])
			cnt++;
	}
	while(m--){
		int x;
		cin>>x;
		if(s[x-1]=='L'&&s[x]=='R'&&pos[x-1]==pos[x])
			cnt--;
		if(s[x]=='L'&&s[x+1]=='R'&&pos[x]==pos[x+1])
			cnt--;
		if(s[x]=='L')
			s[x]='R';
		else
			s[x]='L';
		if(s[x-1]=='L'&&s[x]=='R'&&pos[x-1]==pos[x])
			cnt++;
		if(s[x]=='L'&&s[x+1]=='R'&&pos[x]==pos[x+1])
			cnt++;
		cout<<(cnt==0?"YES":"NO")<<"\n";
	}
}
```

---

