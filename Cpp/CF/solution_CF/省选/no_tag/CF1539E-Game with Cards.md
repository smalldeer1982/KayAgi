# Game with Cards

## 题目描述

The Alice's computer is broken, so she can't play her favorite card game now. To help Alice, Bob wants to answer $ n $ her questions.

Initially, Bob holds one card with number $ 0 $ in the left hand and one in the right hand. In the $ i $ -th question, Alice asks Bob to replace a card in the left or right hand with a card with number $ k_i $ (Bob chooses which of two cards he changes, Bob must replace exactly one card).

After this action, Alice wants the numbers on the left and right cards to belong to given segments (segments for left and right cards can be different). Formally, let the number on the left card be $ x $ , and on the right card be $ y $ . Then after the $ i $ -th swap the following conditions must be satisfied: $ a_{l, i} \le x \le b_{l, i} $ , and $ a_{r, i} \le y \le b_{r,i} $ .

Please determine if Bob can answer all requests. If it is possible, find a way to do it.

## 样例 #1

### 输入

```
2 10
3
0 3
0 2
2
0 4
0 2```

### 输出

```
Yes
0 1```

## 样例 #2

### 输入

```
2 10
3
0 3
0 2
2
3 4
0 1```

### 输出

```
No```

## 样例 #3

### 输入

```
5 10
3
0 3
0 3
7
4 7
1 3
2
2 3
3 7
8
1 8
1 8
6
1 6
7 10```

### 输出

```
Yes
1 0 0 1 0```

# 题解

## 作者：遮云壑 (赞：19)

# Description

开始有两个数，每次操作你要改掉其中的一个数，使这两个数始终在 $\left [ a_{l,i},b_{l,i} \right ] $ 和 $\left [ a_{r,i},b_{r,i} \right ] $ 中。

[传送门](https://www.luogu.com.cn/problem/CF1539E)

# Solution 

这里讲的是 $O(n)$ 做法。

我们把答案看做一段 0 ，一段 1 的一个串。

如果说，我们的答案串里面有一串 0（ 1 同理），比方说是 $[l,r]$ ,那么这一段给出的每个数 $k_i$ 一定满足这样的条件

- $a_{0,i} \le k_i \le b_{0,i}$ 
- $a_{1,i} \le k_{l-1} \le b_{0,i}$ 

用人话说，所有数都满足 0 的范围， $l$ 的前一个数满足 1 的范围。（因为你一段 0 之前必然是一段 1 ）。 

因为你一个数改变了之后是要满足后面的条件，与前面的限制无关，所以这题我们可以**从后往前扫**，不断的缩小条件范围。

扫的过程中，维护第二个条件的区间，扫到的每一个位置假设作为上面说的 $l-1$ 试试第二个条件行不行，如果行的话就转移。当然你也要维护如果当前位置作为 $i$  ，第一个条件是否始终满足，可以用 & 运算来维护。

具体的算法实现过程看代码。

# Analysis

这个过程我们把所有的 $k$ 扫了一遍，复杂度 $O(n)$ 。

# Code

个人认为这是这题到目前为止解释最清楚的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int& x)
{
	x=0;int y=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x=x*y;
}
const int N=100010;
int n,m,mn[2],l[N][2],r[N][2],L[2],R[2],a[N],fir[2],both[2],pre[N][2];
int main(){
	read(n),read(m);
	//友情提醒：定义数组的地方瞅一眼，所有数组长度都是2哦 
	//0和1正好表示左手右手两个数 
	mn[1]=mn[0]=n+1,fir[0]=fir[1]=1,L[0]=L[1]=0,R[1]=R[0]=m;
	//mn表示上一个0/1的位置，转移用的（min缩写，最近的位置） 
	//fir表示，当前位置是否满足第一个条件（first缩写） 
	//L表示从上一位置过来中最大的L，R同理，这样k_i如果满足[L,R]的区间就满足了后面一段的区间 
	for(int i=1;i<=n;i++)read(a[i]),read(l[i][0]),read(r[i][0]),read(l[i][1]),read(r[i][1]);
	for(int i=n;i>=1;i--)
	{
		if(a[i]>=l[i][0]&&a[i]<=r[i][0])fir[0]&=1;else fir[0]&=0;
		if(a[i]>=l[i][1]&&a[i]<=r[i][1])fir[1]&=1;else fir[1]&=0;
		//是否满足第一个条件 
		
		L[0]=max(L[0],l[i][0]),R[0]=min(R[0],r[i][0]);
		L[1]=max(L[1],l[i][1]),R[1]=min(R[1],r[i][1]);
		//缩小区间 
		
		if(fir[0]&&a[i-1]>=L[1]&&a[i-1]<=R[1])both[0]=1;else both[0]=0;
		if(fir[1]&&a[i-1]>=L[0]&&a[i-1]<=R[0])both[1]=1;else both[1]=0;
		//是否两个条件都满足 
		
		if(both[0])pre[i][0]=mn[1];//pre表示后一个位置，也就是转移过来的那个位置 
		if(both[1])pre[i][1]=mn[0];//是不是用nxt会更好理解一点 
		//都满足，转移 
		
		if(both[0])mn[0]=i,fir[1]=1,L[0]=0,R[0]=m;
		if(both[1])mn[1]=i,fir[0]=1,L[1]=0,R[1]=m;
		//转移了，重置 
	}
	if(mn[0]>1&&mn[1]>1)//最近的0和1都不在1位置，则无解 
	{
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	int pos=0;
	if(mn[0]>1)pos=1;//从mn为1的那一位开始倒推得到答案 
	for(int i=1;i<=n;i=pre[i][pos],pos^=1)
	{
		for(int j=i;j<pre[i][pos];j++)printf("%d ",pos);
	}
	return 0;
} 
```

# Conclusion

- 对于答案是 01 交错的题目，要有把答案切成许多全 1 或全 0 串的思路。

- 对于值要满足后面会出现的限制条件，可以考虑倒着扫

---

## 作者：Kubic (赞：16)

简单但有意思的题。

这篇题解可以算是记录了我的思维过程。

首先一个常见套路就是把答案序列看作一段 $0$，一段 $1$ 交替。

考虑需要满足什么条件。

对于一段 $0$，假设为 $l,r$，显然 $\forall i\in [l,r],a_i\in [L_{0,i},R_{0,i}]$ 且 $a_{l-1}\in [L_{1,i},R_{1,i}]$。

对于一段 $1$ 可以同理推出条件。

那么就可以考虑 $dp_{i,0/1}$，表示前 $i$ 位，答案第 $i$ 位是 $0/1$ 是否合法。

对 $dp_{i,0}$ 转移时可以尝试找一个 $j<i$ 使得 $dp_{j,1}=1$ 且 $(j,i]$ 这一段 $0$ 合法。如果能找到则 $dp_{i,0}=1$，否则 $dp_{i,0}=0$。

对 $dp_{i,1}$ 可以同理转移。

我们可以预处理 $pos_{i,0/1}$，表示从第 $i$ 位往后的连续 $0/1$ 最远可以延伸到什么位置。这个可以使用倍增或二分 $O(n\log n)$ 预处理。

然后就很容易 $O(n)$ 地进行 dp 了，总复杂度 $O(n\log n)$。

于是我点开官方题解，居然可以 $O(n)$？？？

关上题解又想了想，似乎可以从后往前考虑。把 $dp$ 的意义改为从第 $i$ 位往后的状态。

那么可以发现，$dp_{i,0}$ 可能的最优的转移点一定是最小的使得 $dp_{j,1}=1$ 的 $j$，因为如果从一个 $j'$ 可以转移到 $i$ 且 $j<j'$，那么从 $j$ 也一定能转移。对 $dp_{i,1}$ 同理。

也就是说，我们可以动态维护当前 $dp_{i,0}=1$ 的最小的 $i$ 以及 $dp_{i,1}=1$ 的最小的 $i$。只需考虑中间这一段是否合法，这可以在遍历的过程中也动态维护出来。这样就达到了 $O(n)$ 的复杂度。

参考代码（$O(n)$）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
int n,m,mn[2],L1[2],R1[2],a[N],L[N][2],R[N][2],pr[N][2];bool fl,nw[2],tmp[2];
int main()
{
	scanf("%d %d",&n,&m);
	mn[0]=mn[1]=n+1;nw[0]=nw[1]=1;L1[0]=L1[1]=0;R1[0]=R1[1]=m; 
	for(int i=1;i<=n;++i)
		scanf("%d %d %d %d %d",&a[i],&L[i][0],&R[i][0],&L[i][1],&R[i][1]);
	for(int i=n;i;--i)
	{
		nw[0]&=a[i]>=L[i][0] && a[i]<=R[i][0];
		nw[1]&=a[i]>=L[i][1] && a[i]<=R[i][1];
		L1[0]=max(L1[0],L[i][1]);R1[0]=min(R1[0],R[i][1]);
		L1[1]=max(L1[1],L[i][0]);R1[1]=min(R1[1],R[i][0]);
		tmp[0]=nw[0] && a[i-1]>=L1[0] && a[i-1]<=R1[0];
		tmp[1]=nw[1] && a[i-1]>=L1[1] && a[i-1]<=R1[1]; 
		if(tmp[0]) pr[i][0]=mn[1];if(tmp[1]) pr[i][1]=mn[0];
		if(tmp[0]) mn[0]=i,nw[1]=1,L1[1]=0,R1[1]=m;
		if(tmp[1]) mn[1]=i,nw[0]=1,L1[0]=0,R1[0]=m;
	}if(mn[0]>1 && mn[1]>1) {puts("No");return 0;}puts("Yes");fl=mn[0]>1;
	for(int i=1;i<=n;i=pr[i][fl],fl^=1)
		for(int j=i;j<pr[i][fl];++j) printf("%d ",fl);return 0;
}
```

---

## 作者：7KByte (赞：9)

由于每次必须替换恰好一个，所以我们可以设计状态 $f[0/1][i][j]$ 表示上次替换的是 **左手/右手**，当前是第 $i$ 次询问，没有替换的那只手上的数组是第 $j$ 次询问的数，是否可到达。

朴素 $\rm DP$ 是 $\mathcal{O}(N^2)$。

考虑优化，由于每个状态只需要知道是否可达，即 $f$ 是一个 $0/1$ 数组，所以对于每个 $i$ ，我们用 ``set`` 维护 $f[0]$ 和 $f[1]$ 中为 $1$ 的位置 $j$ 即可。时间复杂度 $\mathcal{O}(N\log N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,m,u[N],g[2][N];
set<pair<int,int> >s[2];
typedef set<pair<int,int> >::iterator ite;
void calc(int x,int op){
	if(!x)return;
	int y=g[op][x];
	calc(y,op^1);
	rep(i,y+1,x)printf("%d ",op);
}
int main(){
	scanf("%d%d",&n,&m);
	int la,ra,lb,rb;
	scanf("%d%d%d%d%d",&u[1],&la,&ra,&lb,&rb);
	if(u[1]>=la&&u[1]<=ra&&!lb)s[0].insert(make_pair(0,0));
	if(u[1]>=lb&&u[1]<=rb&&!la)s[1].insert(make_pair(0,0));
	rep(i,2,n){
		scanf("%d%d%d%d%d",&u[i],&la,&ra,&lb,&rb);
		int flag0 = s[0].size() ? 1 : 0 , flag1 = s[1].size() ? 1 : 0;
		if(flag1)s[0].insert(make_pair(u[i-1],i-1));
		if(flag0)s[1].insert(make_pair(u[i-1],i-1));
		if(la<=u[i]&&u[i]<=ra){
			while(s[0].size()){
				ite cur = s[0].begin();
				if((*cur).first>=lb)break;
				s[0].erase(cur);
			}
			while(s[0].size()){
				if((*s[0].rbegin()).first<=rb)break;
				s[0].erase(*s[0].rbegin());
			}
		}
		else s[0].clear();
		if(lb<=u[i]&&u[i]<=rb){
			while(s[1].size()){
				ite cur = s[1].begin();
				if((*cur).first>=la)break;
				s[1].erase(cur);
			}
			while(s[1].size()){
				if((*s[1].rbegin()).first<=ra)break;
				s[1].erase(*s[1].rbegin());
			}
		}
		else s[1].clear();
		if(s[0].size())g[0][i]=(*s[0].begin()).second;
		if(s[1].size())g[1][i]=(*s[1].begin()).second;
	}
	if(s[0].size())puts("Yes"),calc(n,0);
	else if(s[1].size())puts("Yes"),calc(n,1);
	else puts("No");
	return 0;
}
```

---

## 作者：cyh_toby (赞：6)

[题目](https://www.luogu.com.cn/problem/CF1539E)

首先我的方法巨麻烦，还不好想，感觉可以被其它题解的方法吊打，但还是分享一下，就当拓宽思维和娱乐好了。

设 $f_{i,j}$ 表示到第 $i$ 个操作，当前 $a$ 的数值为 $j$ 是否可行， $g_{i,j}$ 表示到第 $i$ 个操作，当前 $b$ 的数值为 $j$，是否可行。用 $A_i$ 表示第 $i$ 个操作时 $a$ 的范围，同理 $B_i$。那么有

$$f_{i,j} = \begin{cases}0 & (j \not\in A_i) \\ f_{i-1,j} & (k_i \in B_i) \\ \text{or}_{l\in B_i} \{g_{i-1,l}\} & (k_i =j)\end{cases}$$

$g$ 的转移方程类似。

把 DP 的第二维放到线段树上，只要这颗线段支持*区间赋值、求区间或和* 即可在 $O(\log n)$ 的时间内进行转移。

总共有两颗线段树，在过程中用彼此的信息进行状态转移。最后任选一颗线段树，只要整棵树的或和为 $1$，就意味着可行，否则不可行。

剩下就是求方案。在转移过程中，分别维护 $book_a$ 和 $book_b$ 两个数组，表示在 $i$ 个操作，如果让 $a/b$ 变成 $k$，那么此时 $b/a$ 的值为多少。如果线段树支持查询区间内任意一个 $1$ 的出现位置，那么这两数组就能轻松维护。考虑逆推求出方案。在最后的时候，任选一个第一棵树为 $1$ 的位置，然后倒推，结合上述 $book$ 数组可以找到对应的 $b$ 的值，并判断当前操作是选择 $0$ 还是 $1$。

总时间复杂度 $O(n \log n)$。如果不太能理解上述过程，建议参考代码。

```cpp
const int N = 1e5+5;
#define lb lower_bound

int n, m;
struct Node {
	int k, al, ar, bl, br;
} a[N];
int b[N*5], tot;
int ans[N];

inline int get(int x) { return lb(b + 1, b + 1 + tot, x) - b; }

struct SegT {
	struct Node {
		int l, r, sum, tg;
		#define ls (p << 1)
		#define rs (p << 1 | 1)
	} t[N*20];
	int f[N];//记录第 i 步若 a/b 选择成为 k, 那么 b/a 是多少 
	void build(int p, int l, int r) {
		t[p].l = l, t[p].r = r, t[p].tg = -1;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
	}
	inline void push_up(int p) { 
		t[p].sum = t[ls].sum | t[rs].sum; 
	}
	inline void push_down(int p) {
		if (t[p].tg != -1) {
			t[ls].sum = t[ls].tg = t[p].tg;
			t[rs].sum = t[rs].tg = t[p].tg;
			t[p].tg = -1;
		}
	}
	void upd(int p, int l, int r, int x) {
		if (l > r) return;
		if (l <= t[p].l && t[p].r <= r) 
			return t[p].sum = t[p].tg = x, void();
		int mid = (t[p].l + t[p].r) >> 1;
		push_down(p);
		if (l <= mid) upd(ls, l, r, x);
		if (r > mid) upd(rs, l, r, x);
		push_up(p);
	}
	int find(int p, int l, int r) {//找到第一个 1 的位置(其实任意一个都可以) 
		if (!t[p].sum) return 0;
		if (t[p].l == t[p].r) return t[p].l;
		int mid = (t[p].l + t[p].r) >> 1, res = 0;
		push_down(p);
		if (l <= mid) res = find(ls, l, r);
		if (res) return res;
		if (r > mid) return find(rs, l, r);
		return 0;
	}
} A, B;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d%d%d", &a[i].k, &a[i].al, &a[i].ar, &a[i].bl, &a[i].br);
		b[++tot] = a[i].k, b[++tot] = a[i].al, b[++tot] = a[i].ar, b[++tot] = a[i].bl, b[++tot] = a[i].br;
	}
	b[++tot] = 0;
	sort(b + 1, b + 1 + tot);
	tot = unique(b + 1, b + 1 + tot) - b - 1;
	for (int i = 1; i <= n; i++) 
		a[i].k = get(a[i].k), a[i].al = get(a[i].al), a[i].ar = get(a[i].ar), a[i].bl = get(a[i].bl), a[i].br = get(a[i].br);
	A.build(1, 1, tot), B.build(1, 1, tot);
	A.upd(1, 1, 1, 1), B.upd(1, 1, 1, 1);
	for (int i = 1; i <= n; i++) {
		int k = a[i].k, al = a[i].al, ar = a[i].ar, bl = a[i].bl, br = a[i].br;
		int xa = A.find(1, al, ar), xb = B.find(1, bl, br);
		bool ina = (al <= k && k <= ar), inb = (bl <= k && k <= br);
		A.upd(1, 1, al - 1, 0), A.upd(1, ar + 1, tot, 0);
		if (!inb) A.upd(1, al, ar, 0);
		if (ina && !A.find(1, k, k) && xb) A.upd(1, k, k, 1), A.f[i] = xb;
		B.upd(1, 1, bl - 1, 0), B.upd(1, br + 1, tot, 0);
		if (!ina) B.upd(1, bl, br, 0);
		if (inb && !B.find(1, k, k) && xa) B.upd(1, k, k, 1), B.f[i] = xa;
	}
	int xa = A.find(1, 1, tot), xb = 0, p = 0;
	if (!xa) return printf("No\n"), 0;
	printf("Yes\n");
	for (int i = n; i >= 1; i--) {
		int k = a[i].k;
		if (!p) {
			if (xa != k || !A.f[i]) xb = k, ans[i] = 1;
			else xb = A.f[i], p = 1, ans[i] = 0;
		}
		else{
			if (xb != k || !B.f[i]) xa = k, ans[i] = 0;
			else xa = B.f[i], p = 0, ans[i] = 1;
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：Leap_Frog (赞：4)

### P.S.
补 VP 题。  

### Description.
卡老师手上拿着两份代码，都有一个分数值。  
刚开始卡老师一分都不会，所以两份代码的分数值都是 $0$。  
每次老K会给卡老师一份代码，卡老师必须且只能把他的一份代码卡成老K的。  
不过每次卡老师为了不被发现，所以每卡完一次都必须保证第一份代码的分数在 $[L_{i,0},R_{i,0}]$ 之间，第二份在 $[L_{i,1},R_{i,1}]$ 之间。  
问卡老师能不能卡到最后。  

### Solution.
首先，我们考虑把他当做一段 $0,1$ 串。  
然后，模拟一下，我们会发现。  
```
   a  ?
c1 a  c1  1
c2 c2 c1  0
c3 c3 c1  0
...
ck ck c1  0
```
如果有一段**极长** $0$ 串是合法的，当且仅当如下两个条件同时满足。  
$$\forall i\in[l,r],L_{i,0}\le c_i\le R_{i,0}$$  
$$\forall i\in[l,r],L_{i,1}\le c_{l-1}\le R_{i,1}$$  
**极长** $1$ 同理。  
我们观察式子发现，如果从前往后推，其中的 $C_{l-1}$ 不同会导致不具有单调性。  
但是从后往前推我们只需要记录 $\max\{L_{i-1,?}\}$ 和 $\min\{R_{i-1,?}\}$ 然后就可以 $O(1)$ 判断当前是否可行（对于条件 2。  
所以我们从后往前，这样对于一个转移点，必定是它后面的一段相邻区间可以转移到它。  
这样就具有单调性了，可以优化了。  
我们维护 $0$ 和 $1$ 分别的最后可行端点，检查能否转移到当前位置。  
然后就可以直接 $O(n)$ 扫一遍的复杂度内 AC 此题。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
const int N=100005;int n,m,l[N][2],r[N][2],c[N],nx[N][2];
int main()
{
	//以下代码中，wh 表示最靠前的可行位置，nw 表示当前第一个条件能否满足
 	//ck 表示当前能否满足两个条件，L,R 分别表示当前最大左界和最小右界
	read(n),read(m);int wh[2]={n+1,n+1};for(int i=1;i<=n;i++)
		read(c[i]),read(l[i][0]),read(r[i][0]),read(l[i][1]),read(r[i][1]);
	int nw[2]={1,1},ck[2]={0,0},L[2]={0,0},R[2]={m,m};for(int i=n;i;i--)
	{
		nw[0]&=l[i][0]<=c[i]&&c[i]<=r[i][0],nw[1]&=l[i][1]<=c[i]&&c[i]<=r[i][1];
		L[0]=max(L[0],l[i][1]),R[0]=min(R[0],r[i][1]),L[1]=max(L[1],l[i][0]),R[1]=min(R[1],r[i][0]);
		ck[0]=nw[0]&&(L[0]<=c[i-1]&&c[i-1]<=R[0]),ck[1]=nw[1]&&(L[1]<=c[i-1]&&c[i-1]<=R[1]);
		(ck[0]?nx[i][0]=wh[0]:0),(ck[1]?nx[i][1]=wh[1]:0);
		if(ck[0]) nw[1]=1,wh[1]=i,L[1]=0,R[1]=m;
		if(ck[1]) nw[0]=1,wh[0]=i,L[0]=0,R[0]=m;
	}
	if(wh[0]>1&&wh[1]>1) return puts("No"),0;else puts("Yes");
	for(int i=1,p=wh[1]>1;i<=n;i=nx[i][p],p^=1) for(int j=i;j<nx[i][p];j++) printf("%c ",'0'|p);
	return putchar('\n'),0;
}
```

---

## 作者：Cocoly1990 (赞：2)

挑战全网最劣解，狗都不写的 $\mathcal{O}(n\log n)$.

显然的，可以把答案看作一个 $01$ 序列，我们记 $f_{0/1,i}$ 表示第 $i$ 位填 $0/1$ 是否合法，若合法，$f_{0/1,i}=1$，否则为 $0$，这个状态表示之所以合理是因为我们转移所具有的特性。

那么很容易就有转移：

$$f_{0,i}= \max_{j<i}\{f_{j,1}\times \operatorname{check}{(j+1,i,0)}\}$$

$$f_{1,i}= \max_{j<i}\{f_{j,0}\times \operatorname{check}{(j+1,i,1)}\}$$

其中 $\operatorname{check}{(i,j,0/1)}$ 表示 $[i,j]$ 全部填 $0/1$ 并且 $i-1$ 填 $1/0$ 是否合法。

其中 $\operatorname{check}{(i,j,0)}$ 合法当且仅当 $\forall x\in[i,j],a_{l,x}\leq k_x\leq a_{r,x},b_{l,x}\leq k_{i-1}\leq b_{r,x}$.$\operatorname{check}{(i,j,1)}$ 同理。

这个不难理解对吧，现在我们获得了一份 $\mathcal{O}(n^2)$ 的算法。

但仍然可以更优秀。

上述式子是基于被动转移的角度，我们现在我们尝试从主动角度思考。什么时候 $f_{j,1}\rightarrow f_{0,i}$ 是可以转移的，也就是 $\operatorname{check}{(j+1,i,0)} = 1$.当然了，另一种情况同理。

我们发现这里的 $i$ 是有单调性的，也就是这里的 $f_{j,1}$ 所可以转移的位置是连续的区间。

我们记 $pos_{0/1,i}$ 表示第 $i$ 位填 $1/0$，之后填连续的 $0/1$，最多能填几位，这个 $pos$ 显然是可以二分的，二分成立的条件和上述 $\operatorname{check}$ 成立的条件完全一致。

对于 $\forall x\in[i,j],a_{l,x}\leq k_x\leq a_{r,x}$，我们用一个前缀和来快速维护，对于 $\forall x\in[i,j],b_{l,x}\leq k_{i-1}\leq b_{r,x}$，我们开 4 个 st 表来维护他。

下面是如何输出方案，只需要记录转移点就好了，但是注意，有时候可以从 $f_{0/1,0}$ 转移来，此时需要注意一些细节。

代码长得很丑，谨慎食用：

```
// 我只想要拉住流年\好好的 说声再见\遗憾感谢 都回不去昨天
// Problem: CF1539E Game with Cards
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1539E
// Memory Limit: 250 MB
// Author: Fomalhaut
// Time Limit: 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define Maxn 100007
#define int long long
using namespace std;
int pos[Maxn][2], f[Maxn][2];
int a[Maxn][2], b[Maxn][2], k[Maxn];
int n, m;
int ca[Maxn], cb[Maxn];
int ans[Maxn];
int out[Maxn];
int Maxa[Maxn][21], Mina[Maxn][21], Maxb[Maxn][21], Minb[Maxn][21];
void pre(){
	for(int i = 1; i <= n; i ++){
		if(k[i] >= a[i][0] && k[i] <= a[i][1]) ca[i] = 1;
		if(k[i] >= b[i][0] && k[i] <= b[i][1]) cb[i] = 1;
		ca[i] += ca[i - 1];
		cb[i] += cb[i - 1];
	}
	for(int i = 1; i <= n; i ++){
		Maxa[i][0] = a[i][0];
		Mina[i][0] = a[i][1];
		Maxb[i][0] = b[i][0];
		Minb[i][0] = b[i][1];		
	}
	for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            Maxa[i][j]=max(Maxa[i][j-1],Maxa[i+(1<<(j-1))][j-1]);
	for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            Mina[i][j]=min(Mina[i][j-1],Mina[i+(1<<(j-1))][j-1]);
	for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            Maxb[i][j]=max(Maxb[i][j-1],Maxb[i+(1<<(j-1))][j-1]);
	for(int j=1;j<=21;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            Minb[i][j]=min(Minb[i][j-1],Minb[i+(1<<(j-1))][j-1]);            
}
int queryama(int l,int r)
{
    int k=log2(r-l+1); 
    return max(Maxa[l][k], Maxa[r-(1<<k)+1][k]);
}
int queryami(int l,int r)
{
    int k=log2(r-l+1); 
    return min(Mina[l][k], Mina[r-(1<<k)+1][k]);
}
int querybma(int l,int r)
{
    int k=log2(r-l+1); 
    return max(Maxb[l][k], Maxb[r-(1<<k)+1][k]);
}
int querybmi(int l,int r)
{
    int k=log2(r-l+1); 
    return min(Minb[l][k], Minb[r-(1<<k)+1][k]);
}
signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> k[i];
		cin >> a[i][0] >> a[i][1];
		cin >> b[i][0] >> b[i][1];
	}
	pre();
	for(int i = 0; i < n; i ++){
		int l = i + 1, r = n, ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(ca[mid] - ca[i] == mid - i && k[i] >= querybma(i + 1, mid) && k[i] <= querybmi(i + 1, mid)){
				ans = mid; l = mid + 1;
			}else r = mid - 1;
		}
		pos[i][0] = ans;
		if(k[i] < b[i][0] || k[i] > b[i][1]) pos[i][0] = 0;
		l = i + 1, r = n, ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(cb[mid] - cb[i] == mid - i &&  k[i] >= queryama(i + 1, mid) && k[i] <= queryami(i + 1, mid)){
				ans = mid; l = mid + 1;
			}else r = mid - 1;
		}
		pos[i][1] = ans;	
		if(k[i] < a[i][0] || k[i] > a[i][1]) pos[i][1] = 0;
		//cout << i << " " << pos[i][0] << " " << pos[i][1] << endl;	
	}
	// int f = 1;
	// bool ff = 1;
	// for(int i = 1; i < n;){
		// if(pos[i][f] <= i){
			// ff = 0; break;
		// }
		// else i = pos[i][f];
		// f ^= 1;
	// }
	// bool fff = 1; f = 0;
	// for(int i = 1; i < n;){
		// //cout << i << f << " " << endl;
		// if(pos[i][f] <= i){
			// fff = 0; break;
		// }
		// else i = pos[i][f];
		// f ^= 1;
	// }		
	// cout << (ff | fff);
	//f[1][0] = (k[1] >= a[1][0] && k[1] <= a[1][1]);
	//f[1][1] = (k[1] >= b[1][0] && k[1] <= b[1][1]);	
	int _max0 = 0, _max1 = 0;
	//cout << pos[0][0] << " " << pos[0][1] << "!\n";
	//memset(f, -1, sizeof(f));
	f[0][1] = f[0][0] = 1;
	for(int i = 1; i <= n; i ++){
		//cout << _max0 << " " << _max1 << endl;
		if(pos[_max0][0] >= i && f[_max0][1]) f[i][0] = (_max0 == 0 ? n + 2 : _max0);
		if(pos[_max1][1] >= i && f[_max1][0]) f[i][1] = (_max1 == 0 ? n + 2 : _max1);
		if(f[i][1]){
			//_max0 = max(_max0, pos[i][0]);
			if(pos[i][0] > pos[_max0][0]){
				_max0 = i;
			}
		}
		if(f[i][0]){
			//_max1 = max(_max1, pos[i][1]);
			if(pos[i][1] > pos[_max1][1]){
				_max1 = i;
			}			
		}
 	}
 	// if(n == 2 && m == 10 && (f[n][0] | f[n][1])){
 		// cout << "Yes\n0 1";
 		// return 0; 
 	// }
 	cout << ((f[n][0] | f[n][1]) ? "Yes\n" : "No\n");
 	if(! (f[n][0] || f[n][1])) return 0;
	for(int i = 1; i <= n; i ++){
		//cout << f[i][0] << " " << f[i][1] << endl;
	}
 	int ii = n;
 	int ff = 0;
 	int cnt = 0;
 	ans[++ cnt] = n;
 	while(f[ii][ff] >= 1){
 		//cout << f[ii][ff] << endl;
 		ans[++ cnt] = f[ii][ff];
 		ii = f[ii][ff];

 		if(ii == n + 2){
 			cnt --;
 			break;
 		}
  		ff ^= 1;		
 	}
 	if(ii != n + 2) ans[++ cnt] = 1;
 	if(ii == n + 2) ans[++ cnt] = 0;
 	ff = 0;
 	memset(out, -1, sizeof out);
 	for(int i = 2; i <= cnt; i ++){
 		for(int j = ans[i] + 1; j <= ans[i - 1]; j ++){
 			out[j] = ff;
 		}
 		ff ^= 1;
 	}
 	if(out[1] != -1)
	 	for(int i = 1; i <= n; i ++){
	 		cout << out[i] << " ";
	 		if(i == n) return 0;
	 	}
 	ii = n;
 	ff = 1;
 	cnt = 0;
 	ans[++ cnt] = n;
 	while(f[ii][ff] >= 1){
 		//cout << f[ii][ff] << endl;
 		ans[++ cnt] = f[ii][ff];
 		ii = f[ii][ff];

 		if(ii == n + 2){
 			cnt --;
 			break;
 		}
  		ff ^= 1;		
 	}
 	if(ii != n + 2) ans[++ cnt] = 1;
 	if(ii == n + 2) ans[++ cnt] = 0;
 	ff = 1;
 	memset(out, -1, sizeof out);

 	
 	for(int i = 2; i <= cnt; i ++){
 		for(int j = ans[i] + 1; j <= ans[i - 1]; j ++){
 			out[j] = ff;
 		}
 		ff ^= 1;
 	}
 	for(int i = 1; i <= n; i ++){
 		cout << out[i] << " ";
 		if(i == n) return 0;
 	}
 	
}
```

---

## 作者：Nuisdete (赞：1)

考虑分 $01$ 段去做。

设 $f_{i, 0/1}$ 表示对于前 $i$ 个数，第 $i$ 个数填 $0/1$ 是否存在合法方案。

那么对于一个连续 $0$ 段的结尾 $i$，若它合法，则可以用它向外拓展一个连续 $1$ 段，而可以拓展的要求也很显然，记 $l_0$ 和 $r_0$ 是选 $0$ 的边界，$l_1$ 和 $r_1$ 是选 $1$ 的边界，能够拓展到 $j$ 当且仅当：

$$\max_{k = i + 1}^j l_{0, k} \leq x_i \leq \min_{k = i + 1}^j r_{0,k}\wedge\sum_{k = i + 1}^j [l_{1, k} \leq x_k \leq r_{1, k}] = j - i$$

这个东西维护一个指针表示最远拓展到的边界就可以二分加 st 表做到单 $\log$，或者单调队列可以做到线性。

```cpp
# include <cstdio>
# include <vector>
# include <list>
# include <algorithm>
# include <functional>

void solve() {

  int n;
  scanf("%d %*d", &n);
  
  std::vector<int> x(n + 1), l1(n + 1), l2(n + 1), r1(n + 1), r2(n + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d %d %d", &x[i], &l1[i], &r1[i], &l2[i], &r2[i]);
  }

  std::vector<bool> ok1(n + 1), ok2(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (x[i] >= l1[i] && x[i] <= r1[i]) ok1[i] = true;
    if (x[i] >= l2[i] && x[i] <= r2[i]) ok2[i] = true;
  }
  
  std::vector<int> f(n + 1), g(n + 1);
  std::fill(f.begin() + 1, f.end(), -1);
  std::fill(g.begin() + 1, g.end(), -1);

  std::list<int> mn1, mn2, mx1, mx2;
  
  for (int i = 0, p1 = 0, p2 = 0; i < n; ++i) {
    if (p1 < i) p1 = i;
    if (p2 < i) p2 = i;

    while (!mn1.empty() && mn1.front() <= i) mn1.pop_front();
    while (!mx1.empty() && mx1.front() <= i) mx1.pop_front();
    while (!mn2.empty() && mn2.front() <= i) mn2.pop_front();
    while (!mx2.empty() && mx2.front() <= i) mx2.pop_front();

    if (~g[i] && (mn2.empty() || l2[mn2.front()] <= x[i] && r2[mx2.front()] >= x[i])) {
      for (int j = p2 + 1; j <= n; ++j) {
        if (!ok1[j] || l2[j] > x[i] || r2[j] < x[i]) break; f[++p2] = i;
        while (!mn2.empty() && l2[j] >= l2[mn2.back()]) mn2.pop_back(); mn2.push_back(j);
        while (!mx2.empty() && r2[j] <= r2[mx2.back()]) mx2.pop_back(); mx2.push_back(j);
      }
    }

    if (~f[i] && (mn1.empty() || l1[mn1.front()] <= x[i] && r1[mx1.front()] >= x[i])) {
      for (int j = p1 + 1; j <= n; ++j) {
        if (!ok2[j] || l1[j] > x[i] || r1[j] < x[i]) break; g[++p1] = i;
        while (!mn1.empty() && l1[j] >= l1[mn1.back()]) mn1.pop_back(); mn1.push_back(j);
        while (!mx1.empty() && r1[j] <= r1[mx1.back()]) mx1.pop_back(); mx1.push_back(j);
      }
    }
  }

  puts(~f[n] || ~g[n] ? "Yes" : "No");
  if (!(~f[n] || ~g[n])) return;

  std::vector<char> vec;
  for (int opt = ~f[n] ? 0 : 1, st; n; n = st, opt ^= 1) {
    st = opt ? g[n] : f[n];
    for (int i = st + 1; i <= n; ++i) 
      vec.push_back(opt + '0');
  }

  for (auto it = vec.rbegin(); it != vec.rend(); it ++)
    putchar(*it), putchar(' '); putchar('\n');
}

int main() {

  int T = 1;
  while (T--) solve();

  return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

还挺不错的一个题。

## 思路

首先这道题最终的答案是一个 0/1 序列，这个不难想到可以分成连续的 0/1 段进行 DP 转移，DP 状态为 $f_{i,0/1}$ 表示前 $i$ 个数，以第 $i$ 个数为结尾的段颜色为 $0/1$ 时是否合法（存储 bool 值）。

然后考虑怎么转移这个方程。

显然，我们就是要对 $dp_{i,j}$ 找到一个满足题意的 $p$ 转移过来。那么 $p$ 需要满足什么条件呢？假设 $j=0$，$p$ 是上一个颜色段的结尾，则:

- $k_{p}$ 需要被 $q \in [p+1,i]$ 的所有的 $[a_{r,q},b_{r,q}]$ 的交集包含，因为这个区间内这一段区间对应的 $b$ 不会改变。

- $\forall q \in [p+1,i],k_q \in [a_{l,q},b_{r,q}]$

$j=1$ 同理。所有满足条件的 $p$ 都可以转移过来。

一开始我的想法是对每个点二分出来一个向左最远的合法点然后中间的区间都可以取到，后来手玩了一下，发现这个东西就发现这个没有单调性。

后来我想到了倒着考虑这个问题。也就是令 $dp_{i,0/1}$ 表示 $i \sim n$ 这段序列，以 $i$ 开始的颜色段颜色为 $0/1$ 的时候是否合法。

然后我们考虑对每个点向后处理最远到达的位置。这个有没有单调性呢？

由于这次我们的左端点确定了，假设在一个位置 $j$ 使得 $k_{i} \notin [a_j,b_j]$，那么后面的也一定不满足；如果有一个位置 $j$ 使得 $k_{j} \notin [a_j,b_j]$ 那么后面的也是无法改变这个结果的。

所以这个就具有单调性了，非常神奇。

于是我们考虑维护几个 ST 表然后二分一下每个点向右最远的位置。处理出来这个之后，DP 一下即可。

记录路径就不用说了吧，能做到这个级别的题的神仙们应该都知道怎么记录 qwq。

我的复杂度是 $O(n \log n)$ 的。主要是我看了题解的 $O(n)$ 做法木有太懂，我自己先琢磨琢磨/ll

## 代码

[Code & Submission](https://codeforces.com/contest/1539/submission/219249675)

---

## 作者：xfrvq (赞：0)

设 $f_{i,0/1,x}\in\{0,1\}$：以 $(k_{i-1},x)$ 或 $(x,k_{i-1})$ 的初始值做 $i,\cdots,n$ 的操作，有无合法方案。

+ 设 $g(x,y,i)$ 为 $x\in[La_i,Ra_i],y\in[Lb_i,Rb_i]$ 时 $1$ 否则 $0$。
+ $f_{i,0,x}=\max\{f_{i+1,0,x}g(k_i,x,i),f_{i+1,1,k_{i-1}}g(k_i,k_{i-1},i)\}$​。
+ $f_{i,1,x}=\max\{f_{i+1,1,x}g(x,k_i,i),f_{i+1,0,k_{i-1}}g(k_{i-1},k_i,i)\}$。

直接做需要主席树优化 dp 做区间推平，但注意到 $f_{i,0/1,0\cdots m}$ 只会有至多一段 $1$ 区间，剩下 $0$ 的前后缀。于是只用维护 $1$ 区间端点，总复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n,m,a[N],K[N],L0[N],R0[N],L1[N],R1[N];
int S0[N],T0[N],S1[N],T1[N];

#define in(x,l,r) (l <= x && x <= r)

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i)
		scanf("%d%d%d%d%d",K + i,L0 + i,R0 + i,L1 + i,R1 + i);
	T0[n + 1] = T1[n + 1] = m;
	for(int i = n;i >= 1;--i){
		if(!in(K[i],L1[i],R1[i])) S0[i] = m,T0[i] = -1;
		else S0[i] = max(S0[i + 1],L0[i]),T0[i] = min(T0[i + 1],R0[i]);
		if(!in(K[i],L0[i],R0[i])) S1[i] = m,T1[i] = -1;
		else S1[i] = max(S1[i + 1],L1[i]),T1[i] = min(T1[i + 1],R1[i]);
		bool x = i <= n && in(K[i - 1],S1[i + 1],T1[i + 1]) && in(K[i],L0[i],R0[i]) && in(K[i - 1],L1[i],R1[i]);
		bool y = i <= n && in(K[i - 1],S0[i + 1],T0[i + 1]) && in(K[i],L1[i],R1[i]) && in(K[i - 1],L0[i],R0[i]);
		if(x) S0[i] = 0,T0[i] = m;
		if(y) S1[i] = 0,T1[i] = m;
	}
	if(S0[1] && S1[1]) return puts("No"),0;
	puts("Yes");
	for(int i = 1,x = 0,y = 0;i <= n;++i)
		if(L0[i] <= x && x <= R0[i] && L1[i] <= K[i] && K[i] <= R1[i] && S0[i + 1] <= x && x <= T0[i + 1]) printf("1 "),y = K[i];
		else printf("0 "),x = K[i];
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：0)

## CF1539E 【Game with Cards】

### 题意

+ 有两个数 $b,c$，初始均为 $0$；
+ $n$ 次操作，第 $i$ 次把 $a_i$ 赋值给 $b$ 或 $c$，接着要满足 $l_{0,i}\le b\le r_{0,i},l_{1,i}\le c\le r_{1,i}$；
+ 判断是否有方案，有就输出；
+ $n\le10^5,a_i\le10^9$。

### 做法

把赋值给 $b$ 用 0 表示，赋值给 $c$ 用 1 表示。

假设一段极长的 0 位于 $[x,y]$，需要满足：
1. 任意 $x\le i\le y$，$l_{0,i}\le a_i\le r_{0,i}$；
2. 任意 $x\le i\le y$，$l_{1,i}\le a_{x-1}\le r_{1,i}$。

设 $dp_{0,i}$ 表示 $i$ 为一段极长 0 的末尾时，$[1,i]$ 能否满足条件。

发现能转移到 $dp_{0,i}$ 的所有 $j$ 的 $a_j$ 都互不相同，没有单调性，很难快速维护。

但是发现当 $x$ 相同的时候，$y$ 越小越容易满足单调性（两条限制均变少），可以考虑从后往前 DP。

设 $dp_{0,i}$ 表示 $i$ 为一段极长 0 的开头时，$[i,n]$ 能否满足条件。

记录最小的 $i$ 使 $dp_{0,i}=1$。动态维护是否满足转移的条件，满足即转移。

---

