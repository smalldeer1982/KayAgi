# Range Minimum Sum

## 题目描述

For an array $ [a_1,a_2,\ldots,a_n] $ of length $ n $ , define $ f(a) $ as the sum of the minimum element over all subsegments. That is, $ $$$f(a)=\sum_{l=1}^n\sum_{r=l}^n \min_{l\le i\le r}a_i. $ $ </p><p>A permutation is a sequence of integers from  $ 1 $  to  $ n $  of length  $ n $  containing each number exactly once. You are given a permutation  $ \[a\_1,a\_2,\\ldots,a\_n\] $ . For each  $ i $ , solve the following problem independently:</p><ul> <li> Erase  $ a\_i $  from  $ a $ , concatenating the remaining parts, resulting in  $ b = \[a\_1,a\_2,\\ldots,a\_{i-1},\\;a\_{i+1},\\ldots,a\_{n}\] $ . </li><li> Calculate  $ f(b)$$$.

## 说明/提示

In the second test case, $ a=[3,1,2] $ .

- When removing $ a_1 $ , $ b=[1,2] $ . $ f(b)=1+2+\min\{1,2\}=4 $ .
- When removing $ a_2 $ , $ b=[3,2] $ . $ f(b)=3+2+\min\{3,2\}=7 $ .
- When removing $ a_3 $ , $ b=[3,1] $ . $ f(b)=3+1+\min\{3,1\}=5 $ .

## 样例 #1

### 输入

```
4
1
1
3
3 1 2
5
4 2 1 5 3
8
8 1 4 6 7 3 5 2```

### 输出

```
0 
4 7 5 
19 21 27 17 19 
79 100 72 68 67 80 73 80```

# 题解

## 作者：Alex_Wei (赞：22)

### [CF1988E Range Minimum Sum](https://www.luogu.com.cn/problem/CF1988E)

对于不删数的经典问题，一种做法是枚举最小值的位置 $p$。设 $l, r$ 分别表示 $p$ 左右两侧值小于 $a_p$ 的第一个位置，若不存在则为 $0$ 和 $n + 1$，则所有左端点在 $[l + 1, p]$，右端点在 $[p, r - 1]$ 的子区间的最小值为 $a_p$。

推广到本题，依然枚举最小值的位置 $p$。考察删去不同位置时最小值为 $a_p$ 的子区间数量 $c$ 的情况。

- 如果删去 $p$，那么显然 $c = 0$。
- 如果删去 $[l + 1, p - 1]$ 的某个位置，那么 $c = (p - l - 1)(r - p)$。
- 如果删去 $[p + 1, r - 1]$ 的某个位置，那么 $c = (p - l)(r - p - 1)$。
- 如果删去 $[1, l - 1]\cup [r + 1, n]$ 的某个位置，那么 $c = (p - l)(r - p)$。
- 如果删去 $l$，设 $l_2$ 为 $l$ 左侧值小于 $a_p$ 的第一个位置，那么 $c = (p - l_2 - 1)(r - p)$。
- 如果删去 $r$，设 $r_2$ 为 $r$ 右侧值小于 $a_p$ 的第一个位置，那么 $c = (p - l)(r_2 - p - 1)$。

$l, r$ 容易单调栈求出，$l_2, r_2$ 可以 ST 表结合二分求出，时间复杂度 $\mathcal{O}(n\log n)$，[代码](https://codeforces.com/contest/1988/submission/270843357)。也可以单调栈求出，时间复杂度 $\mathcal{O}(n)$。

$l_2$ 的线性求法：按 $l$ 从小到大为第一关键字，$a$ 从大到小为第二关键字的顺序考虑所有位置，对每个位置，依次往栈内加入上一个位置的 $l$ 到当前位置的 $l - 1$ ，然后弹出所有值大于 $a$ 的位置，则栈顶即为 $l_2$。$r_2$ 同理。[代码](https://codeforces.com/contest/1988/submission/270901433)。

另一种求法是枚举作为 $l$ 或 $r$ 的 $i$，从 $i - 1$ 开始跳 $l$ 直到值大于 $a_i$，从 $i + 1$ 开始跳 $r$ 直到值大于 $a_i$，得到两条链（笛卡尔树上左儿子的右链和右儿子的左链），在链上双指针求出这些位置的 $l_2$ 和 $r_2$。[代码](https://codeforces.com/contest/1988/submission/270902181)。这个求法虽然写起来简单，但无法像上一种求法一样扩展至 $l_k, r_k$。

看了一下官方题解，大致是这样的：用所有区间减去以 $p$ 为一端且另一端在 $[l + 1, r - 1]$ 外的区间（在笛卡尔树上向下 DFS 时顺便维护），减去 $[l + 1, r - 1]$ 的子区间（容易计算），加上 $[l + 1, p - 1]$ 的子区间（容易计算），加上 $[p + 1, r - 1]$ 的子区间（容易计算），再加上左端点在 $[l + 1, p - 1]$ 且右端点在 $[p + 1, r]$ 的区间。最后一部分再分成左端点在左儿子 $ls$ 及其左侧且右端点在右儿子 $rs$ 及其右侧的区间（容易计算），和剩下的部分。剩下的部分可以在 $ls + 1\sim p - 1$ 的后缀最小值序列（左儿子的右链）和 $p + 1\sim rs - 1$ 的前缀最小值序列（右儿子的左链）上双指针计算。

---

## 作者：2huk (赞：20)

跟 [CF1913F](https://www.luogu.com.cn/article/tnxaf3y1) 很像，但是简单的多。

> - 给定长度为 $n$ 的序列 $a$。求出对于每个 $i = (1, 2, \dots, n)$，序列 $b = [a_1, a_2, \dots, a_{i - 1}, a_{i + 1} ,a_{i +2}, \dots, n]$ 的价值。
> - 序列 $c$ 的价值为 $\sum_{l=1}^{|c|} \sum_{r=l}^{|c|} \min _{l \le i \le r} c_i$。
> - $a_i \le n \le 5 \cdot 10^5$，$\sum n \le 10^6$。

若没有删除操作，而是直接求原序列 $a$ 的价值。那么有很经典的单调栈做法。求出 $i$ 之前第一个 $< a_i$ 的位置 $l_i$，或不存在为 $0$。以及 $i$ 之后第一个 $< a_i$ 的位置 $r_i$，或不存在为 $n + 1$。

只要 $l \in [l_i + 1, i], r \in [i, r_i-1]$，那么 $\min_{j=l}^r a_j = a_i$。因此答案为 $\sum a_i \times (i-l_i) \times (r_i - i)$。

仍然考虑这种拆贡献的做法。我们令 $f(i)$ 表示将 $a_i$ 删除后的答案。枚举 $j$ 考虑 $a_j$ 对哪些 $f(i)$ 有贡献。

分类讨论：

- $i = j$：显然没有贡献；
- $i < l_j$ 或 $i > r_j$：显然贡献不变，即 $a_j \times (j - l_j) \times (r_j - j)$；
- $i = l_j$：也就是说把 $j$ 左边第一个 $< a_j$ 的数删除了。那么新的 $l_j$ 可能会发生变化，需要重新计算。
- $i = r_j$：同上。需要重新计算 $r_j$。
- $l_j < i < j$：原来的 $j$ 由于在它之前的 $i$ 被删除变成了 $j - 1$，且新的 $l_j$ 不变。因此 $a_j$ 的贡献变成了 $a_j \times (j - 1 - l_j) \times (r_j -j)$；
- $j < i < r_j$：同上，新的贡献变成了 $a_j \times (j - l_j) \times (r_j - 1 - j)$。

除了 $i = l_j$ 和 $i = r_j$ 的情况外，都可以直接差分完成。对于这两种需要重新计算 $l_j, r_j$ 的情况可以二分 + RMQ 计算。

```cpp
// Problem: Range Minimum Sum
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1988E
// Memory Limit: 500 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

typedef long long ll;

#define int ll

int T, n, a[N];
int st[N][20];
int L[N], R[N];
int f[N];
int f_sum[N];		// f 的差分数组，用于区间加

void add(int l, int r, int d) {
	if (l <= r) f_sum[l] += d, f_sum[r + 1] -= d;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		st[i][0] = a[i];
		f[i] = f_sum[i] = 0;
	}
	
	for (int j = 1; j < 20; ++ j )
		for (int i = 1; i + (1 << j - 1) <= n; ++ i )
			st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	
	auto RMQ = [&](int l, int r) {
		int k = log2(r - l + 1);
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	};
	
	stack<int> stk;
	for (int i = 1; i <= n; ++ i ) {
		while (stk.size() && a[stk.top()] > a[i]) stk.pop();
		L[i] = stk.size() ? stk.top() : 0;
		stk.push(i);
	}
	
	while (stk.size()) stk.pop();
	
	for (int i = n; i; -- i ) {
		while (stk.size() && a[stk.top()] > a[i]) stk.pop();
		R[i] = stk.size() ? stk.top() : n + 1;
		stk.push(i);
	}
	
	for (int j = 1; j <= n; ++ j ) {
		// 删除 a[j] 后，哪些 f(i) 会收到影响？
		add(1, L[j] - 1, a[j] * (j - L[j]) * (R[j] - j));
		add(R[j] + 1, n, a[j] * (j - L[j]) * (R[j] - j));
		add(L[j] + 1, j - 1, a[j] * (j - 1 - L[j]) * (R[j] - j));
		add(j + 1, R[j] - 1, a[j] * (j - L[j]) * (R[j] - 1 - j));
	}
	
	for (int i = 1; i <= n; ++ i ) f[i] = (f_sum[i] += f_sum[i - 1]);
	
	for (int i = 1; i <= n; ++ i ) {
		// 将 L[i] 删除
		int l = 1, r = L[i] - 1, res = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			if (RMQ(mid, L[i] - 1) > a[i]) res = L[i] - mid, r = mid - 1;
			else l = mid + 1;
		}
		res += i - L[i];
		f[L[i]] += a[i] * res * (R[i] - i);
	}
	
	for (int i = 1; i <= n; ++ i ) {
		// 将 R[i] 删除
		int l = R[i] + 1, r = n, res = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			if (RMQ(R[i] + 1, mid) > a[i]) res = mid - R[i], l = mid + 1;
			else r = mid - 1;
		}
		res += R[i] - i;
		f[R[i]] += a[i] * (i - L[i]) * res;
	}
	
	for (int i = 1; i <= n; ++ i ) cout << f[i] << ' ';
	cout << '\n';
	return;
}

signed main() {
	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：8)

考虑建立笛卡尔树。

假若删去了点 $u$，考虑其影响。

对于 $u$ 的所有父亲而言，$u$ 被删去的影响实际上只是导致了其某个儿子子树减少了 $1$，这部分贡献可以通过笛卡尔树上从上到下 dp 直接做到 $O(n)$。

对于 $u$ 的儿子而言，没有影响。

关键在于如何处理原来以 $u$ 为最小值的区间也就是 $u$ 自己的贡献。观察到 $u$ 删去后原来包含 $u$ 的区间新最小值贡献应当来源于从点 $u$ 的左儿子开始一直跳右儿子形成的链，我们称之为右链，以及点 $u$ 的右儿子一直跳左儿子形成的链，我们成为左链，而具体地计算方式只要对右链与左链暴力归并的过程中计算即可。

但是为什么暴力归并的复杂度是对的呢？注意到一条右链只会在链顶作为左儿子被合并一次，一条左链只会在链顶作为右儿子被合并一次，所以总的复杂度还是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5+114;
int ls[maxn],rs[maxn],a[maxn];
int tp,st[maxn],n;
int lt[maxn],rt[maxn];
int val[maxn];
int ans;
int delta[maxn];
void solve(int cur,int Lt,int Rt){
    if(cur==0) return ;
    lt[cur]=Lt,rt[cur]=Rt;
    int Llen=max(0*1ll,(cur-1-Lt+1));
    int Rlen=max(0*1ll,(Rt-cur-1+1));
    int len=(rt[cur]-lt[cur]+1);
    val[cur]=a[cur]*(Llen*Rlen+len);
    ans+=val[cur];
    delta[ls[cur]]=delta[cur]+a[cur]*(Llen*Rlen+len)-(a[cur]*((Llen-1)*Rlen+len-1));
    delta[rs[cur]]=delta[cur]+a[cur]*(Llen*Rlen+len)-(a[cur]*(Llen*(Rlen-1)+len-1));
    solve(ls[cur],lt[cur],cur-1);
    solve(rs[cur],cur+1,rt[cur]);
}
int w[maxn];
int calc(int cur){
	vector<int> L,R;
	int lcur=ls[cur];
	while(lcur!=0){
		L.push_back(lcur);
		lcur=rs[lcur];
	}
	int rcur=rs[cur];
	while(rcur!=0){
		R.push_back(rcur);
		rcur=ls[rcur];
	}
	int Llst=cur,Rlst=cur;
	for(int x:L) w[x]=x-Llst,Llst=x;
	for(int x:R) w[x]=Rlst-x,Rlst=x;
	reverse(L.begin(),L.end());
	reverse(R.begin(),R.end());
	if(L.size()!=0) w[L.back()]=L.back()-lt[cur]+1;
	if(R.size()!=0) w[R.back()]=rt[cur]-R.back()+1;
	int sumL=0,sumR=0,res=0;
	int p1=0,p2=0;
	while(p1<L.size()||p2<R.size()){
		if(p1<L.size()&&p2<R.size()&&a[L[p1]]>a[R[p2]]){
			res+=a[L[p1]]*w[L[p1]]*sumR;
			sumL+=w[L[p1]];
			p1++;
		}else if(p1<L.size()&&p2<R.size()&&a[L[p1]]<=a[R[p2]]){
			res+=a[R[p2]]*w[R[p2]]*sumL;
			sumR+=w[R[p2]];
			p2++;
		}else if(p1==L.size()){
			res+=a[R[p2]]*w[R[p2]]*sumL;
			sumR+=w[R[p2]];
			p2++;	
		}else{
			res+=a[L[p1]]*w[L[p1]]*sumR;
			sumL+=w[L[p1]];
			p1++;
		}
	}
	return res;
}
void work(){
    cin>>n;
    for(int i=1;i<=n;i++) val[i]=delta[i]=lt[i]=rt[i]=ls[i]=rs[i]=st[i]=0;
    ans=0;
    tp=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int k=tp;
        while(k>0&&a[st[k]]>a[i]) k--;
        if(k) rs[st[k]]=i;
        if(k<tp) ls[i]=st[k+1];
        st[++k]=i,tp=k;
    }
    solve(st[1],1,n);
    for(int i=1;i<=n;i++){
        int Llen=max(0*1ll,(i-1-lt[i]+1));
        int Rlen=max(0*1ll,(rt[i]-i-1+1));
        int len=(rt[i]-lt[i]+1);
        cout<<ans-delta[i]-val[i]+calc(i)<<' ';
    }
    cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
}
/*
1
5
4 2 1 5 3
*/
```

---

## 作者：Kevin911 (赞：2)

赛后 vp 了一下这场比赛，发现这道 E 题还蛮典的。
## 思路
可以类比无删除的经典题，用单调栈或二分（代码中用倍增实现的）加 st 表，求出左右第一个比自己小的值的位置 $l_{i,0}$ 和 $r_{i,0}$，然后乘法原理把 $a_i \times (i-l_i) \times (r_i-i)$ 加起来，统计答案即可。

预处理原数组的区间最小值的河，考虑删除 $a_i$ 会产生什么影响。首先要扣除 $a_i$ 的贡献 $a_i \times (i-l_i) \times (r_i-i)$。其次，以 $i$ 为左边界或右边界的位置 $p$ 需要继续向左或右找第二个比它小的值的位置 $l_{p,1}$ 和 $r_{p,0}$，然后在于处理时把修改前后的差值统计到 $i$ 上，即

>$sum[l[i][0]]+=a[i]*(l[i][0]-l[i][1]-1)*(r[i][0]-i);$
>
>$sum[r[i][0]]+=a[i]*(i-l[i][0])*(r[i][1]-r[i][0]-1);$

然后 $l_{i,0}+1$ 到 $i-1$ 或 $i+1$ 到 $r_{i,0}$ 上的其它位置到右界限或左界限的距离的距离会减一，可以使用树状数组来维护。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int maxn=5e5+10;
int n;
int a[maxn],st[maxn][21],l[maxn][2],r[maxn][2];
ull s;
ull sum[maxn],c[maxn];
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c&15);
		c=getchar();
	}
	return x;
}
void print(int x)
{
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
int query(int x,int y)
{
	int lg=__lg(y-x+1);
	return min(st[x][lg],st[y-(1<<lg)+1][lg]);
}
int lbt(int x)
{
	return x&(-x);
}
void update(int x,int y)
{
	for(int i=x;i<=n;i+=lbt(i)) c[i]+=y;
}
int query(int x)
{
	int res=0;
	for(int i=x;i;i-=lbt(i)) res+=c[i];
	return res;
}
signed main()
{
	int t=read();
	for(int p=1;p<=t;p++)
	{
		s=0;
		n=read();
		for(int i=1;i<=n;i++) a[i]=read(),st[i][0]=a[i],sum[i]=0,c[i]=0;
		for(int i=1;i<=20;i++)
			for(int j=1;j+(1<<(i-1))<=n;j++) st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
		for(int i=1;i<=n;i++)
		{
			l[i][0]=l[i][1]=0;
			int d=0;
			for(int j=20;j>=0;j--)
				if(d+(1<<j)<i&&query(i-d-(1<<j),i-1)>a[i]) d+=(1<<j);
			if(d==i-1) continue;
			l[i][0]=i-d-1;
			int pos=i-d-1;
			d=0;
			for(int j=20;j>=0;j--)
				if(d+(1<<j)<pos&&query(pos-d-(1<<j),pos-1)>a[i]) d+=(1<<j);
			if(d==pos-1) continue;
			l[i][1]=pos-d-1;
		}
		for(int i=1;i<=n;i++)
		{
			r[i][0]=r[i][1]=n+1;
			int d=0;
			for(int j=20;j>=0;j--)
				if(i+d+(1<<j)<=n&&query(i+1,i+d+(1<<j))>a[i]) d+=(1<<j);
			if(d==n-i) continue;
			r[i][0]=i+d+1;
			int pos=i+d+1;
			d=0;
			for(int j=20;j>=0;j--)
				if(pos+d+(1<<j)<=n&&query(pos+1,pos+d+(1<<j))>a[i]) d+=(1<<j);
			if(d==n-i) continue;
			r[i][1]=pos+d+1;
		}
		for(int i=1;i<=n;i++)
		{
			s+=a[i]*(i-l[i][0])*(r[i][0]-i);
			update(l[i][0]+1,-a[i]*(r[i][0]-i));
			update(i,a[i]*(r[i][0]-i));
			update(i+1,-a[i]*(i-l[i][0]));
			update(r[i][0],a[i]*(i-l[i][0]));
			sum[l[i][0]]+=a[i]*(l[i][0]-l[i][1]-1)*(r[i][0]-i);
			sum[r[i][0]]+=a[i]*(i-l[i][0])*(r[i][1]-r[i][0]-1);
		}
		for(int i=1;i<=n;i++) print(s-a[i]*(i-l[i][0])*(r[i][0]-i)+sum[i]+query(i)),putchar(' ');
		putchar('\n');
	}
}
```

---

## 作者：729hao (赞：1)

[luogu 题目传送门](https://www.luogu.com.cn/problem/CF1988E)$\ \ \ $[CF 题目传送门](https://codeforces.com/contest/1988/problem/E)
# 思路
官方题解里用的是笛卡尔树，但是本蒟蒻太蒟了，不会笛卡尔树，怎么办？

**线段树**。

## step 1
假设现在没有删点，考虑一个数 $i$ 对答案的贡献。

令 $pos_i$ 表示数 $i$ 在序列中的位置。

不难想到，找到 $i$ 左侧比 $i$ 小的最靠右的数 $ml$，以及 $i$ 右侧比 $i$ 小的最靠左的数 $mr$，则 $i$ 的贡献为 $(pos_i-pos_{ml})\times (pos_{mr}-pos_i)\times i$。

如果一个数没有 $ml$，则 $ml=0$；如果没有 $mr$，则 $mr=n+1$。为了保证上述计算贡献的公式的正确性，应将 $pos_0$ 设为 $0$，$pos_{n+1}$ 设为 $n+1$。

这个就可以线段树来维护。$i$ 从 $1$ 到 $n$ 依次找对应的 $ml$ 和 $mr$，找完之后把 $i$ 放入线段树中即可。需要维护的信息只有区间最靠左和最靠右的值。

## step 2
现在我们考虑删数之后的情况。对于一个数 $i$，要删的数为 $j$，有如下几种情况：
### 1.$j<ml \lor j>mr$
很明显，这种情况下 $j$ 不会对答案产生影响。换句话说，会使答案增加 $0$。
### 2.$j=ml$
这个时候 $i$ 对应的 $ml$ 应该更新。而根据 $ml$ 的定义，$pos_j+1$ 到 $pos_i$ 之间没有比 $i$ 小的数，所以新的 $ml$ 一定在原来的 $ml$ 的左边。也就是说，新的 $ml$ 一定是 $i$ 左侧比 $i$ 小的**次**靠右的数 $sml$。

于是在找 $ml$ 的时候，顺便找一下即可。

这时会使答案增加 $-(pos_i-pos_{ml})\times (pos_{mr}-pos_i)\times i+(pos_i-pos_{sml}$ $\color{red}{-1}$ $)\times (pos_{mr}-pos_i)\times i$。

注意这个 $-1$，是因为 $j$ 被删掉了。
### 3.$j=mr$
与 $j=ml$ 差不多，就是从找左边变成了找右边。
### 4.$j=i$
这种情况下，$i$ 对答案的贡献是 $0$。即会使答案增加 $-(pos_i-pos_{ml})\times (pos_{mr}-pos_i)\times i$。
### 5.$j>ml \land j<i$
很明显，左边可以取的数少了 $1$ 个，答案会增加 $-(pos_i-pos_{ml})\times (pos_{mr}-pos_i)\times i+(pos_i-pos_{ml}-1)\times (pos_{mr}-pos_i)\times i$。
### 6.$j>i \land j<mr$
与 $j>ml \land j<i$ 差不多，就是从左边变成了右边。

## step 3
接下来就是统计答案。无视第一种情况。

第二、三、四种情况比较好统计，因为对于固定的 $i$，$j$ 也是固定的，可以 $O(1)$ 求出对答案的影响。

那么第五、六种情况呢？

这个时候，枚举 $i$ 似乎是不可行的了。那么考虑枚举 $j$。

稍微思考得到，$j$ 会让 $i$ 对答案造成影响的充要条件是 $j>i$ 且 $j$ 与 $i$ 之间的数都大于 $i$。

回顾之前的分析，以第五种情况为例，首先想想 $j$ 右边第一个满足条件的 $i$ 是什么呢？

在之前，我们定义了 $lm$ 和 $rm$。回顾定义，我们会发现：$rm$ 与 $i$ 之间的数一定大于 $i$。

同时也一定大于 $rm$。

所以，$j$ 右边第一个满足条件的 $i$ 一定是 $rm_j$！

>证明：$j$ 右边第一个会让答案造成影响的 $i$ 是 $rm_j$。
> 
> 假设命题不成立，则存在 $k$，$pos_k>pos_i \land pos_k<pos_{rm_j}$，且 $j$ 会影响 $k$。则有 $j>k$ 且 $j$、$k$ 之间的数皆大于 $k$。
>
>况一：$j$、$k$ 之间的数皆大于 $j$，根据上文定义，$k$ 就是 $rm_j$。
>
>况二：存在 $x$，$pos_x>pos_j\land pos_x<pos_k\land x<j$，且 $x$ 是满足上述条件中最靠左的一个。则 $j$、$x$ 中间的数皆大于 $x$，则 $j$ 必会影响 $x$，且 $rm_j$ 等于 $x$。

类似地，我们可以推出第二个满足条件的 $i$ 一定是 $rm_{rm_j}$，第三个以此类推。

第六种情况同理。

于是，我们就可以以 $O(n)$ 算出每个 $j$ 的影响了！

# AC code
$pos_i$：同上文的 $pos_i$。  
$m_{i,j,k}$：数 $i$ 左（$j=0$）/右（$j=1$）离 $i$ 第 $k+1$ 近且比 $i$ 小的数。  
$oans$：不删数时的答案。  
$ans_j$：第二三四种情况下 $j$ 对答案的影响。  
$lnum_j$：第六种情况下 $j$ 对答案的影响。  
$rnum_j$：第五种情况下 $j$ 对答案的影响。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5;
int T,n,a[N+5],pos[N+5],m[N+5][2][2];
long long oans,ans[N+5],lnum[N+5],rnum[N+5];
struct Seg{
	int l,r;
	int lm,rm;
}Tree[4*N+5];
void Build(int id,int L,int R){
	Tree[id].l=L;
	Tree[id].r=R;
	Tree[id].lm=Tree[id].rm=0;
	if(L==R)return;
	int mid=L+R>>1;
	Build(id<<1,L,mid);
	Build(id<<1|1,mid+1,R);
}
void Pushup(int id){
	Tree[id].lm=Tree[id<<1].lm==0?Tree[id<<1|1].lm:Tree[id<<1].lm;
	Tree[id].rm=Tree[id<<1|1].rm==0?Tree[id<<1].rm:Tree[id<<1|1].rm;
}
void Modify(int id,int x,int d){
	if(Tree[id].l>x||Tree[id].r<x)return;
	if(Tree[id].l==Tree[id].r){
		Tree[id].lm=Tree[id].rm=d;
		return;
	}
	Modify(id<<1,x,d);
	Modify(id<<1|1,x,d);
	Pushup(id);
}
int Query_l(int id,int L,int R){
	if(Tree[id].l>R||Tree[id].r<L)return 0;
	if(Tree[id].l>=L&&Tree[id].r<=R){
		return Tree[id].lm;
	}
	int ls=Query_l(id<<1,L,R);
	if(ls)return ls;
	return Query_l(id<<1|1,L,R);
}
int Query_r(int id,int L,int R){
	if(Tree[id].l>R||Tree[id].r<L)return 0;
	if(Tree[id].l>=L&&Tree[id].r<=R){
		return Tree[id].rm;
	}
	int ls=Query_r(id<<1|1,L,R);
	if(ls)return ls;
	return Query_r(id<<1,L,R);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		oans=0;
		Build(1,1,n);
		for(int i=1;i<=n;i++){
			cin>>a[i];
			pos[a[i]]=i;
			ans[i]=0;
			m[i][0][0]=m[i][0][1]=m[i][1][0]=m[i][1][1]=0;
			lnum[i]=rnum[i]=0;
		}
		m[0][0][0]=m[0][0][1]=m[0][1][0]=m[0][1][1]=0;
		m[n+1][0][0]=m[n+1][0][1]=m[n+1][1][0]=m[n+1][1][1]=n+1;
		pos[n+1]=n+1;
		pos[0]=0;
		for(int i=1;i<=n;i++){
			if(pos[i]!=1){
				m[i][0][0]=Query_r(1,1,pos[i]-1);
				if(m[i][0][0]&&pos[m[i][0][0]]>1){
					m[i][0][1]=Query_r(1,1,pos[m[i][0][0]]-1);
				}
			}
			if(pos[i]!=n){
				m[i][1][0]=Query_l(1,pos[i]+1,n);
				if(m[i][1][0]){
					if(pos[m[i][1][0]]<n){
						m[i][1][1]=Query_l(1,pos[m[i][1][0]]+1,n);
						if(m[i][1][1]==0)m[i][1][1]=n+1;
					}
					else m[i][1][1]=n+1;
				}
				else m[i][1][0]=m[i][1][1]=n+1;
			}
			else m[i][1][0]=m[i][1][1]=n+1;
			Modify(1,pos[i],i);
			oans+=(pos[i]-pos[m[i][0][0]])*1ll*(pos[m[i][1][0]]-pos[i])*i;
			ans[m[i][0][0]]-=(pos[i]-pos[m[i][0][0]])*1ll*(pos[m[i][1][0]]-pos[i])*i;
			ans[m[i][0][0]]+=(pos[i]-pos[m[i][0][1]]-1)*1ll*(pos[m[i][1][0]]-pos[i])*i;//第二种情况
			ans[m[i][1][0]]-=(pos[i]-pos[m[i][0][0]])*1ll*(pos[m[i][1][0]]-pos[i])*i;
			ans[m[i][1][0]]+=(pos[i]-pos[m[i][0][0]])*1ll*(pos[m[i][1][1]]-pos[i]-1)*i;//第三种情况
			ans[i]-=(pos[i]-pos[m[i][0][0]])*1ll*(pos[m[i][1][0]]-pos[i])*i;//第四种情况
		}
		for(int i=1;i<=n;i++){
			i=a[i];
			if(m[i][0][0]!=0)lnum[i]=lnum[m[i][0][0]]+(pos[m[i][0][0]]-pos[m[m[i][0][0]][0][0]])*1ll*m[i][0][0];
			ans[i]-=lnum[i];
			i=pos[i];
		}//第六种情况
		for(int i=n;i>=1;i--){
			i=a[i];
			if(m[i][1][0]!=n+1)rnum[i]=rnum[m[i][1][0]]+(pos[m[m[i][1][0]][1][0]]-pos[m[i][1][0]])*1ll*m[i][1][0];
			ans[i]-=rnum[i];
			i=pos[i];
		}//第五种情况
//		printf("oans:%lld\n",oans);
		for(int i=1;i<=n;i++){
			cout<<oans+ans[a[i]]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

```
时间复杂度 $O(n\log n)$，$4s$ 跑 $10^6$ 完全够了。

在代码中，实际答案 $=oans+ans_i-lnum_i-rnum_i$。

---

## 作者：TTpandaS (赞：1)

考虑不删数怎么做。

考虑每个数的贡献，即要求出每个数作为区间最小值的区间数量，建出笛卡尔树，用左子树大小加一乘右子树大小加一即可。

考虑删数怎么做。

删掉一个数后，他会使他的所有祖先都减少另一边子树大小加一的次数，这个可以在递归下去时处理出来。再考虑其子树内部的变化。一个重要的性质是：每次删掉一个点只会让其左儿子的右链与右儿子的左链进行合并，那么每个点进行合并的次数是 $O(1)$ 级别，总时间复杂度是 $O(n)$！

所以可以先把左儿子的右链与右儿子的左链所有点取出，从大到小排序重新计算贡献，它的贡献就是比它大的个数加一乘上其另一个子树大小加一。

---

## 作者：Hoks (赞：0)

## 前言
好题，思维难度和代码难度都很合适。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
如果并不带删除的话，这是一个经典问题。

我们考虑对于每一个 $i$，只计算他是区间最小值时的答案。

那么我们可以用单调栈维护出左右端点的取值范围，设为 $L\in[l_i,i],R\in[i,r_i]$。

那么对于 $i$ 来讲，贡献即为 $a_i\cdot(i-l_i+1)\cdot(r_i-i+1)$。

总的贡献即为 $\sum\limits_{i=1}^n a_i\cdot(i-l_i+1)\cdot(r_i-i+1)$。

接着考虑来删除数。

我们考虑当 $i$ 被删除时，$j$ 的贡献变化了多少。
1. 当 $j=i$ 时，以 $j$ 为区间最小值的贡献显然全没了，所以对于 $i$ 的答案的贡献为 $-a_j\cdot(j-l_j+1)\cdot(r_j-j+1)$。
2. 当 $j<i\le r_j$ 时，$j$ 的贡献从 $a_j\cdot(j-l_j+1)\cdot(r_j-j+1)$ 变为了 $a_j\cdot(j-l_j+1)\cdot(r_j-j)$，作差即可。
3. 当 $r_j=i-1$ 时，$j$ 有贡献的区间可以进一步往右扩展，考虑 ST 表+二分处理。
4. 当 $l_j\le i<j$ 时，$j$ 的贡献从 $a_j\cdot(j-l_j+1)\cdot(r_j-j+1)$ 变为了 $a_j\cdot(j-l_j)\cdot(r_j-j+1)$，作差即可。
5. 当 $l_j=i+1$ 时，$j$ 有贡献的区间可以进一步向左拓展，考虑 ST 表+二分处理。

不难发现，比较难处理的就是 $2.$ 和 $4.$。

我们考虑把 $i,j$ 颠倒：

对于任意 $i$，他对 $j\in(i,r_i]$ 的贡献都是 $a_i\cdot(i-l_i+1)$。

而对于 $j\in[l_i,i)$ 的贡献都是 $a_i\cdot(r_i-i+1)$。

也就是一个区间加，考虑直接差分最后计算即可。
## 代码

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,a[N],b[N],l[N],r[N],s[N];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='?'); }
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
struct ST
{
    int st[20][N],lg[N];
    void clear(){for(int j=0;j<=19;j++) for(int i=1;i+(1<<j)-1<=n;i++) st[j][i]=0;}
    void get_ST(int a[])
    {
        lg[0]=-1;for(int i=1;i<=n;i++) st[0][i]=a[i],lg[i]=lg[i>>1]+1;
        for(int j=1;j<=19;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    int get(int l,int r){int k=lg[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
inline int getl(int x,int y)
{
    int l=1,r=x,res=x;
    while(l<=r)
        if(st.get(mid,x)>=y) res=mid,r=mid-1;
        else l=mid+1;
    if(st.get(res,x)<y) res++;return res;
}
inline int getr(int x,int y)
{
    int l=x,r=n,res=x;
    while(l<=r)
        if(st.get(x,mid)>=y) res=mid,l=mid+1;
        else r=mid-1;
    if(st.get(x,res)<y) res--;return res;
}
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) a[i]=read();st.get_ST(a);int ss=0;
    for(int i=1;i<=n;i++) l[i]=getl(i,a[i]),r[i]=getr(i,a[i]),ss+=a[i]*(r[i]-i+1)*(i-l[i]+1);
    for(int i=1;i<=n;i++) b[i]=ss-a[i]*(r[i]-i+1)*(i-l[i]+1),s[i]=0;
    for(int i=1;i<=n;i++)
    {
        int ll=getl(l[i]-2,a[i]),rr=getr(r[i]+2,a[i]);
        b[l[i]-1]+=a[i]*(r[i]-i+1)*(l[i]-ll-1);
        b[r[i]+1]+=a[i]*(i-l[i]+1)*(rr-r[i]-1);
    }
    for(int i=1;i<=n;i++)
    {
        s[l[i]]-=a[i]*(r[i]-i+1);s[i]+=a[i]*(r[i]-i+1);
        s[i+1]-=a[i]*(i-l[i]+1);s[r[i]+1]+=a[i]*(i-l[i]+1);
    }ss=0;st.clear();
    for(int i=1;i<=n;i++) ss+=s[i],print(b[i]+ss),put(' ');put('\n');
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Microscopic_WaXeR (赞：0)

# 题目大意
给你一个长度为 $n$ 的排列 $a_i$，对于每一个 $i$，求去掉 $a_i$ 后的序列所有子串的最小值的和。

# 解题思路

看到这题数据范围是 $10^5$ 立刻想到对于每一个 $i$ 计算的时候应该使用原排列的贡献 $-$ 去掉 $a_i$ 后产生的影响。

接下来的问题就是如何计算产生的影响。我们显然可以通过单调队列求出每一个 $i$ 之前和之后最靠近它且比他它小的数，记作 $front_i$ 与 $back_i$，这样即可求出原排列的答案。

接着考虑删去一个 $i$ 会对答案造成哪些影响。首先，它本身的贡献会被减去，即 $\left(i-front_i\right)\times\left( back_i-i\right)$。其次，如果 $j$ 与 $front_j$ 或 $back_j$ 形成的区间包括了 $i$，那么也要减去相应的量，这个在之后的程序中会有所涉及，不难理解，因此不多赘述。最后，当 $front_j$ 或 $back_j$ 恰好等于 $i$ 时，此时对于 $j$ 而言，它的贡献就会增加，因为 $front_j$ 或 $back_j$ 会扩展。现在的问题来到了如何计算扩展的范围。这部分使用二分加上 ST 表即可。

时间复杂度：$O(n \log n)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=500010;
int T;
int n,a[N];
//int pre[N],nxt[N];
ll sum;
int st[N][25];
int fro[N],bac[N];
vector <int> pre[N],suf[N];
ll delta;
int query(int l,int r){
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
void work_pre(int maxn,int x){
	int l=0,r=maxn-1,mid,res=-1;
	while(l<=r){
		mid=l+r>>1;
		if(query(mid,maxn-1)<=a[x]){
			l=mid+1;
			res=mid;
		}
		else{
			r=mid-1;
		}
	}
	//cout<<x<<' '<<res<<endl;
	if(res!=-1) delta-=(ll)(maxn-res-1)*(bac[x]-x)*a[x];
}
void work_suf(int minn,int x){
	int l=minn+1,r=n+1,mid,res=-1;
	while(l<=r){
		mid=l+r>>1;
		if(query(minn+1,mid)<=a[x]){
			r=mid-1;
			res=mid;
		}
		else{
			l=mid+1;
		}
	}
	//cout<<x<<' '<<res<<endl;
	if(res!=-1) delta-=(ll)(res-minn-1)*(x-fro[x])*a[x];
}
void solve(){
	cin>>n;
	sum=0;
	for(int i=0;i<=n+1;i++){
		pre[i].clear();
		suf[i].clear();
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		st[i][0]=a[i];
	}
	st[0][0]=0;st[n+1][0]=0;
	for(int j=1;j<=20;j++)
		for(int i=0;i+(1<<j)-1<=n+1;i++)
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	a[0]=a[n+1]=0;
	deque <int> q;
	q.push_back(0);
	for(int i=1;i<=n;i++){
		while(!q.empty() && a[q.back()]>a[i])
			q.pop_back();
		fro[i]=q.back();
		pre[q.back()].push_back(i);
		q.push_back(i);
	}
	while(!q.empty()) q.pop_back();
	q.push_back(n+1);
	for(int i=n;i>=1;i--){
		while(!q.empty() && a[q.back()]>a[i])
			q.pop_back();
		bac[i]=q.back();
		suf[q.back()].push_back(i);
		q.push_back(i);
	}
	ll red=0;
	for(auto j:pre[0])
		red+=(ll)(bac[j]-j)*a[j];
	for(int i=1;i<=n;i++)
		sum+=(ll)(i-fro[i])*(bac[i]-i)*a[i];
	for(int i=1;i<=n;i++){
		red-=(ll)(bac[i]-i)*a[i];
		for(auto j:suf[i])
			red-=(ll)(j-fro[j])*a[j];
		delta=(ll)(i-fro[i])*(bac[i]-i)*a[i];
		for(auto j:pre[i])
			work_pre(i,j);
		for(auto j:suf[i])
			work_suf(i,j);
		//cout<<delta<<endl;
		//cout<<red<<endl;
		cout<<sum-delta-red<<' ';
		for(auto j:pre[i])
			red+=(ll)(bac[j]-j)*a[j];
		red+=(ll)(i-fro[i])*a[i];
	}
	cout<<endl;
}
int main(){
	cin>>T;
	while(T--)
		solve();
	return 0;
}

```

#### 后记

实际上这题思路非常好想，但是代码实现细节略多，难度大概 $2300$ 左右？

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18321473)

# 思路

如果没有删除操作，就是一个典中典。

直接枚举最小值 $a_i$，可以轻松 $\Theta(n)$ 找到其所能管辖到的最大区间 $[L_i,R_i]$。形式化地说，找到一个最小的 $L_i$ 和一个最大的 $R_i$，使得 $\min_{L_i \leq x \leq R_i}\{a_x\} = a_i$。

那么它对答案的贡献是 $a_i \times (i - L_i + 1) \times (R_i - i + 1)$。

加入删除操作，也是差不多的做法，依旧是枚举最小值。可以按照删除元素的位置 $t$ 进行如下分讨：

1. $t \in [1,L_i - 1)$ 或 $t \in (R_i + 1,n]$，显然对答案无影响，贡献为 $a_i \times (i - L_i + 1) \times (R_i - i + 1)$。

2. $t \in [L_i,i)$，在 $i$ 左边的选择会少一种，贡献为 $a_i \times (i - L_i) \times (R_i - i + 1)$。

3. $t \in (i,R_i]$，在 $i$ 右边的选择会少一种，贡献为 $a_i \times (i - L_i + 1) \times (R_i - i)$。

4. $t = L_i - 1$ 或 $t = R_i + 1$，比较特殊的一种情况，当删除这个位置后，$a_i$ 对应新的区间范围可能变化，需要重新求解。可以直接利用 ST 表二分求解。

所有贡献都是连续的，直接差分计算即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define ll long long

using namespace std;

typedef pair<int,int> pii;
const int N = 5e5 + 10,M = 24,inf = 1e9 + 10;
int n;
int arr[N],L[N],R[N],lg[N];
ll c[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct ST{
    #define pot(x) (1 << x)

    pii dp[N][M];

    inline pii Add(pii a,pii b){
        if (a.fst == b.fst) return {a.fst,min(a.snd,b.snd)};
        else if (a.fst < b.fst) return {a.fst,min(a.snd,b.fst)};
        else return {b.fst,min(a.fst,b.snd)};
    }

    inline void build(){
        for (re int i = 2;i <= n;i++) lg[i] = lg[i >> 1] + 1;
        for (re int i = 1;i <= n;i++) dp[i][0] = {arr[i],inf};
        for (re int j = 1;j <= lg[n];j++){
            for (re int i = 1;i + pot(j) - 1 <= n;i++) dp[i][j] = Add(dp[i][j - 1],dp[i + pot(j - 1)][j - 1]);
        }
    }

    inline pii query(int l,int r){
        int len = r - l + 1;
        return Add(dp[l][lg[len]],dp[r - pot(lg[len]) + 1][lg[len]]);
    }

    #undef pot
}st;

inline void add(int l,int r,ll k){
    if (l > r) return;
    c[l] += k; c[r + 1] -= k;
}

inline void solve(){
    n = read();
    fill(c + 1,c + n + 5,0);
    for (re int i = 1;i <= n;i++) arr[i] = read();
    st.build();
    for (re int i = 1;i <= n;i++) L[i] = R[i] = i;
    for (re int i = 1;i <= n;i++){
        while (L[i] > 1 && arr[L[i] - 1] > arr[i]) L[i] = L[L[i] - 1];
    }
    for (re int i = n;i;i--){
        while (R[i] < n && arr[R[i] + 1] > arr[i]) R[i] = R[R[i] + 1];
    }
    for (re int i = 1;i <= n;i++){
        int lnum = i - L[i] + 1,rnum = R[i] - i + 1;
        add(1,L[i] - 2,1ll * lnum * rnum * arr[i]);
        add(L[i],i - 1,1ll * (lnum - 1) * rnum * arr[i]);
        add(i + 1,R[i],1ll * lnum * (rnum - 1) * arr[i]);
        add(R[i] + 2,n,1ll * lnum * rnum * arr[i]);
        if (L[i] > 1){
            int l = 1,r = L[i] - 1;
            while (l < r){
                int mid = l + r >> 1;
                if (st.query(mid,i).snd == arr[i]) r = mid;
                else l = mid + 1;
            }
            int Lnum = i - l;
            add(L[i] - 1,L[i] - 1,1ll * Lnum * rnum * arr[i]);
        }
        if (R[i] < n){
            int l = R[i] + 1,r = n;
            while (l < r){
                int mid = l + r + 1 >> 1;
                if (st.query(i,mid).snd == arr[i]) l = mid;
                else r = mid - 1;
            }
            int Rnum = l - i;
            add(R[i] + 1,R[i] + 1,1ll * lnum * Rnum * arr[i]);
        }
    }
    for (re int i = 1;i <= n;i++) printf("%lld ",c[i] += c[i - 1]);
    puts("");
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Engulf (赞：0)

如果不删除元素，这是个经典问题，可以使用单调栈解决。

现在要删除元素，仍然考虑枚举区间最小值计算贡献。先单调栈处理出 $i$ 左边第一个 $<a_i$ 的数的下标 $L_i$ 和 $i$ 右边第一个 $<a_i$ 的数的下标 $R_i$，那么左端点在 $(L_i,i]$，右端点在 $[i, R_i)$ 的区间最小值都是 $a_i$。为了不用去管边界，如果左边没有比 $a_i$ 小的那么 $L_i=0$，若右边没有比 $a_i$ 小的那么 $R_i = n + 1$。

设删除第 $i$ 个元素后的答案为 $f_i$，枚举 $j$ 考虑 $a_j$ 对其他 $f_i$ 的影响。

- $i = j$ 时，$a_j$ 对答案无贡献。
- $i\in [1, L_j) \bigcup (R_j, n]$ 时，删除 $i$ 不影响 $a_j$ 造成贡献的区间，$f_i$ 加上 $a_j \cdot (j - L_j) \cdot (R_j - j)$。
- $i \in (L_j, j)$ 时，因为删除了 $i$，上面说的合法区间的左端点少了一个，所以 $f_i$ 加上 $a_j \cdot (j \color{red}-1 \color{black} - L_j)\cdot (R_j - j)$。
- $i \in (j, R_j)$ 时，因为删除了 $i$，上面说的合法区间的右端点少了一个，所以 $f_i$ 加上 $a_j \cdot (j - L_j)\cdot (R_j \color{red}-1 \color{black} - j)$。
- $i = L_j$ 时，原本 $j$ 左边第一个 $<a_j$ 的数被删掉了，设 $L_j$ 左边第一个小于 $a_j$ 的数的下标是 $k$，注意到 $k$ 是有单调性的，用数据结构维护区间最小值（我用的 ST 表），二分 $k$ 即可，$f_i$ 加上 $a_j \cdot (j \color{red} - 1 \color{black}-k) \cdot(R_j - j)$，同样地因为删掉了 $i$ 所以要 $-1$。
- $i = R_j$ 时，原本 $j$ 右边第一个 $<a_j$ 的数被删掉了，设 $R_j$ 右边边第一个小于 $a_j$ 的数的下标是 $k$，注意到 $k$ 是有单调性的，用数据结构维护区间最小值，二分 $k$ 即可，$f_i$ 加上 $a_j \cdot (j - L_j) \cdot(k \color{red} - 1 \color{black} - j)$，同样地因为删掉了 $i$ 所以要 $-1$。

发现上面的操作其实就是一个区间加法，离线询问，差分数组维护即可。讨论繁多，但代码实现优美。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 5e5 + 5;

int n;
int a[N];
int L[N], R[N];

ll f[N];

void add(int l, int r, ll v) {if (l <= r) f[l] += v, f[r + 1] -= v;}
void add(int i, ll v) {add(i, i, v);}

int st[N][20];
int query(int l, int r) {int k = __lg(r - l + 1); return min(st[l][k], st[r - (1 << k) + 1][k]);}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i], st[i][0] = a[i];

        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);

        stack<int> stk;
        stk.push(0);
        a[0] = 0;
        for (int i = 1; i <= n; i++) {
            while (!stk.empty() && a[stk.top()] >= a[i]) stk.pop();
            L[i] = stk.top();
            stk.push(i);
        }

        while (!stk.empty()) stk.pop();
        stk.push(n + 1);
        a[n + 1] = 0;
        for (int i = n; i; i--) {
            while (!stk.empty() && a[stk.top()] >= a[i]) stk.pop();
            R[i] = stk.top();
            stk.push(i);
        }

        for (int i = 0; i <= n; i++) f[i] = 0;

        for (int i = 1; i <= n; i++) {
            add(1, L[i] - 1, 1ll * a[i] * (i - L[i]) * (R[i] - i));
            add(R[i] + 1, n, 1ll * a[i] * (i - L[i]) * (R[i] - i));
            add(L[i] + 1, i - 1, 1ll * a[i] * (i - 1 - L[i]) * (R[i] - i));
            add(i + 1, R[i] - 1, 1ll * a[i] * (i - L[i]) * (R[i] - 1 - i));

            int l = 1, r = L[i] - 1, res = 0;
            while (l <= r) {
                int mid = l + r >> 1;
                if (query(mid, L[i] - 1) < a[i]) res = mid, l = mid + 1;
                else r = mid - 1;
            }
            add(L[i], 1ll * a[i] * (i - 1 - res) * (R[i] - i));

            l = R[i] + 1, r = n, res = n + 1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (query(R[i] + 1, mid) < a[i]) res = mid, r = mid - 1;
                else l = mid + 1;
            }
            add(R[i], 1ll * a[i] * (i - L[i]) * (res - 1 - i));
        }

        for (int i = 1; i <= n; i++) {
            f[i] += f[i - 1];
            cout << f[i] << " \n"[i == n];
        }
    }
    return 0;
}
```

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1988E)。

考虑求出每个数左右第一、二个比它小的位置，记为 $l_i$，$r_i$，$ll_i$，$rr_i$。则原序列的答案为 $\sum (i-l_i)(r_i-i)a_i$。

考虑删去 $a_i$ 的影响。显然以 $a_i$ 为最小值的区间的贡献会被减去。不妨只考虑 $i$ 左边的数的贡献的差，不难发现只有满足 $[x,i)$ 中不存在比 $a_x$ 小的数的 $x$ 才会受到影响。所以可以从左往右扫，维护一个单调栈，则只有单调栈内的数才会受影响。

若 $a_x>a_i$，则以 $a_x$ 为最小值的区间的右端点可以扩大到 $rr_x-1$ 处。这时增加的贡献是 $a_x(x-l_x)(rr_x-i-1)$。

若 $a_x<a_i$，则 $i$ 作为右端点的贡献会减少。此时减少的贡献为 $a_x(x-l_x)$，这些 $x$ 在单调栈是连续的，可以用前缀和维护。

$i$ 对右边的数的贡献同理。用单调栈算 $ll_i$，$rr_i$ 可以做到 $O(n)$，像我赛时一样使用幽默二分求解将会是 $O(n\log n)$。

**code**
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
int t,n,a[500005],q[500005],head,tail,lst[500005],nxt[500005],nxt2[500005],lst2[500005],mn[500005][21];
ll nans,sum[500005],ans[500005];
int qr(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}
int main(){
	t=read();
	while(t--){
		n=read(),nans=0,head=1,tail=0,a[n+1]=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			while(head<=tail&&a[q[tail]]>a[i]) nxt[q[tail]]=i,tail--;
			lst[i]=q[tail],q[++tail]=i;
		}
		for(int i=head;i<=tail;i++) nxt[q[i]]=n+1;
		for(int i=1;i<=n;i++)
			nans+=1ll*(nxt[i]-i)*(i-lst[i])*a[i];
		for(int i=1;i<=n;i++) ans[i]=nans-1ll*(nxt[i]-i)*(i-lst[i])*a[i],mn[i][0]=a[i];
		for(int i=1;(1<<i)<=n;i++)
			for(int j=1;j+(1<<i)<=n+1;j++)
				mn[j][i]=min(mn[j][i-1],mn[j+(1<<i-1)][i-1]);
		for(int i=1;i<=n;i++){
			int l=nxt[i],r=n+1;
			while(l+1<r){
				int mid=l+r>>1;
				if(qr(nxt[i]+1,mid)<=a[i]) r=mid;
				else l=mid;
			}
			nxt2[i]=r;
			l=0,r=lst[i];
			while(l+1<r){
				int mid=l+r>>1;
				if(qr(mid,lst[i]-1)<=a[i]) l=mid;
				else r=mid;
			}
			lst2[i]=l;
		}
		head=1,tail=0;
		for(int i=1;i<=n;i++){
			while(head<=tail&&a[q[tail]]>a[i]) 
				ans[i]+=1ll*a[q[tail]]*(q[tail]-lst[q[tail]])*(nxt2[q[tail]]-i-1),tail--;
			ans[i]-=sum[tail],q[++tail]=i,sum[tail]=sum[tail-1]+1ll*(i-lst[i])*a[i];
		}
		head=1,tail=0;
		for(int i=n;i;i--){
			while(head<=tail&&a[q[tail]]>a[i]) 
				ans[i]+=1ll*a[q[tail]]*(nxt[q[tail]]-q[tail])*(i-lst2[q[tail]]-1),tail--;
			ans[i]-=sum[tail],q[++tail]=i,sum[tail]=sum[tail-1]+1ll*(nxt[i]-i)*a[i];
		}
		for(int i=1;i<=n;i++)
			printf("%lld ",ans[i]);
		putchar(10);
	}
    return 0;
}
```

---

## 作者：arrow_king (赞：0)

# 题意

我们定义一个数组 $b_1,b_2,\dots,b_m$ 的价值是其所有区间的最小值之和，即
$$
\sum_{i=1}^m\sum_{j=i}^m\min_{i\le k\le j}\{b_k\}
$$
给定一个长度为 $n$ 的排列 $a_1,a_2\dots,a_n$，你需要对所有 $i$ 求出 $f(i)$ 的值，其中 $f(i)$ 定义为：

- 生成一个长度为 $n-1$ 的新数组 $c$，$c$ 是由 $a$ 数组中删掉 $a_i$ 而形成的；
- $f(i)$ 的值就是 $c$ 的价值。

$n\le5\times10^5$。

# 思路

官方题解用的笛卡尔树，但是蒟蒻太菜了，只会使用暴力线段树求答案。复杂度是 $O(n\log n)$。

我们首先思考一下没有那个鬼畜的删除操作该怎么写。由于这是个排列没有重复元素，因此我们考虑对每个元素求其贡献，也就是对每个 $i$ 求有多少个区间满足其最小值为 $a_i$，而这是单调栈的模板。我们定义 $l_i$ 为 $i$ 左边第一个比 $a_i$ 小的元素下标，$r_i$ 为 $i$ 右边第一个比 $a_i$ 小的元素下标，那么以 $a_i$ 为最小值的区间个数就是 $(i-l_i)(r_i-i)$。这是因为在 $(l_i,r_i)$ 中没有比 $a_i$ 更小的元素，因此区间可以任意取，利用乘法原理就可以得到答案。单调栈复杂度是 $O(n)$，因此总复杂度也是 $O(n)$。

现在有了这个删除操作，我们考虑怎么沿用上面的思路。对于下标在 $[1,l_i)\cup(r_i,n]$ 这个范围内的元素 $a_j$，删除它时不会对 $a_i$ 的贡献造成任何影响；在 $(l_i,i)$ 这个范围内，删除它会让包含 $a_i$ 区间潜在的左端点数量减 $1$（因为删掉了）。同样 $(i,r_i)$ 会让右端点数量减 $1$。

最困难的讨论在 $j=l_i$、$j=r_i$ 两个点上。在删除 $l_i$ 的时候我们发现 $a_i$ 区间能取的左端点数量**增加了**，会继续向左延伸直到**左边第二个比 $a_i$ 小的位置**；同样，在删除 $r_i$ 时右端点会延伸到右边第二个比 $a_i$ 小的位置。而这两个点（不妨记作 $L_i$ 和 $R_i$）也可以在单调栈过程中求出。

因此我们发现求出 $l,r,L,R$ 的耗时是 $O(n)$ 的，而后面统计贡献用到了 $4$ 次区间加和 $2$ 次单点加，这个过程可以使用线段树维护，因此复杂度是 $O(n\log n)$。

# 核心代码

场上没想明白有关 $L,R$ 的问题因此没调出来，这是赛后补题的代码。

```cpp
il void mian() {
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) R[i]=RR[i]=n+1;
	for(int i=1,l,r;i<=n;i++) {
		while(ttop>0&&a[stt[ttop]]>a[i]) RR[stt[ttop--]]=i;
		l=ttop+1,r=ttop;
		while(top>0&&a[st[top]]>a[i]) {
			R[st[top]]=i;
			stt[++ttop]=st[top--];
			r++;
		}
		for(int j=l;j<=(l+r)>>1;j++) swap(stt[j],stt[l+r-j]);
		st[++top]=i;
	}
	top=ttop=0;
	for(int i=n,l,r;i>=1;i--) {
		while(ttop>0&&a[stt[ttop]]>a[i]) LL[stt[ttop--]]=i;
		l=ttop+1,r=ttop;
		while(top>0&&a[st[top]]>a[i]) {
			L[st[top]]=i;
			stt[++ttop]=st[top--];
			r++;
		}
		for(int j=l;j<=(l+r)>>1;j++) swap(stt[j],stt[l+r-j]);
		st[++top]=i;
	}
	//使用单调栈来求出上述四个数组，复杂度为O(n)
	build(1,1,n);
	for(ll i=1;i<=n;i++) {
		modify(1,L[i]-1,1,n,1,a[i]*(i-L[i])*(R[i]-i));
		modify(L[i],L[i],1,n,1,a[i]*(R[i]-i)*(i-LL[i]-1));
		modify(L[i]+1,i-1,1,n,1,a[i]*(i-L[i]-1)*(R[i]-i));
		modify(i+1,R[i]-1,1,n,1,a[i]*(i-L[i])*(R[i]-i-1));
		modify(R[i],R[i],1,n,1,a[i]*(i-L[i])*(RR[i]-i-1));
		modify(R[i]+1,n,1,n,1,a[i]*(i-L[i])*(R[i]-i));
		//对6种情况的分类讨论并统计贡献
	}
	for(int i=1;i<=n;i++) printf("%lld ",query(i,1,n,1));
	//单点求和，输出答案
	putchar('\n');
}
```

**Upd**：其实线段树完全没有必要，我们是先进行区间加再查询单点值，完全可以使用差分数组将其优化到 $O(n)$。

[提交记录](https://codeforces.com/contest/1988/submission/270863077)

---

