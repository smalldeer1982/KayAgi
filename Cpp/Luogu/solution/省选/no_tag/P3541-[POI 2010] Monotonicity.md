# [POI 2010] Monotonicity

## 题目描述

**译自 POI 2010 Stage 3. Day 0「[Monotonicity](https://szkopul.edu.pl/problemset/problem/HVVwfLd9uyYNOW6hUZ_Zcnqe/site/?key=statement)」**

对于一个整数序列 $a_1, a_2, \cdots, a_n$，我们定义其“单调序列"为一个由 $<$，$>$ 和 $=$ 组成的符号序列 $s_1, s_2, \cdots,s_{n-1}$，其中符号 $s_i$ 表示 $a_i$ 和 $a_{i+1}$ 之间的关系。例如，数列 $2, 4, 3, 3, 5, 3$ 的单调序列为 $<, >, =, <, >$。

对于整数序列 $b_1, b_2, \cdots, b_{n+1}$ 以及其单调序列 $s_1, s_2, \cdots, s_n$，如果符号序列 $s_1', s_2', \cdots, s_k'$ 满足对所有 $1 \le i \le n$ 有 $s_i = s_{((i - 1) \bmod n) + 1}'$，我们就说序列 $s_1, s_2, \cdots, s_n$ 「实现」了序列 $s_1', s_2', \cdots, s_k'$。也就是说，序列 $s_1, s_2, \cdots, s_n$ 可以通过重复多次 $s_1', s_2', \cdots, s_k'$ 序列并删除一个后缀得到。例如，整数数列 $2, 4, 3, 3, 5, 3$ 至少实现了以下符号序列：

* $<, >, =$
* $<, >, =, <, >$
* $<, >, =, <, >, <, <, =$
* $<, >, =, <, >, =, >, >$

给定一个整数序列 $a_1, a_2, \cdots, a_n$ 以及一个单调序列 $s_1, s_2, \cdots, s_k$，求出原整数序列最长的子序列 $a_{i_1}, a_{i_2}, \cdots, a_{i_m} (1 \le i_1 \lt i_2 \lt \cdots \lt i_m \le n)$ 使得前者的单调序列实现后者的符号序列。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 20000$，$1 \le k \le 100$，$1 \le a_i \le 1000000$，$s_j \in \{<, >, =\}$。

## 样例 #1

### 输入

```
7 3
2 4 3 1 3 5 3
< > =```

### 输出

```
6
2 4 3 3 5 3```

# 题解

## 作者：Code_星云 (赞：2)

很容易想到这题的 DP。$dp_{i,j}$ 表示目前到了 $a_i$，$s$ 序列匹配到了第 $j$ 位的最大长度。转移就从 $dp_{t, (j-1==0)?k:j-1}$ 转移来，其中 $t$ 要满足 $s_j$ 的条件。然后容易看出这个转移可以用权值线段树来优化。然后复杂度就是 $O(nk\log{n})$ 的。这道题需要动态开点。

需要注意的是，符号序列与数字序列不是一一对应的，而是两个数字间的相对关系。所以要特殊处理一下序列最开始的位置。我这里是用 $dp_{?,0}$ 来表示的。方案的话记录一下转移路径就行了。

```cpp
#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define px first
#define py second

const int K = 105;
const int N = 20005;
const int inf = 1000001;
int n, k, ans, top, bar[N], a[N], s[K], dp[N][K];
pii lst[N][K];

struct sgtree{
	int rt, tot = 0;
	struct segtree{
		int lc, rc, pl, maxn;
		#define lc(x) tree[x].lc
		#define rc(x) tree[x].rc
		#define pl(x) tree[x].pl
		#define maxn(x) tree[x].maxn 
	};
	segtree tree[N * 7];
	void pushup(int x){
		if(! lc(x)) maxn(lc(x)) = - inf;
		if(! rc(x)) maxn(rc(x)) = - inf;
		if(maxn(lc(x)) > maxn(rc(x))) maxn(x) = maxn(lc(x)), pl(x) = pl(lc(x));
		else maxn(x) = maxn(rc(x)), pl(x) = pl(rc(x));
	}
	void modify(int &x, int l, int r, int p, int id, int val){
		if(! x) x = ++ tot;
		if(l == r){maxn(x) = val; pl(x) = id; return;}
		int mid = (l + r) >> 1;
		if(p <= mid) modify(lc(x), l, mid, p, id, val);
		else modify(rc(x), mid + 1, r, p, id, val);
		pushup(x);
	}
	pii query(int x, int l, int r, int ql, int qr){
		if(ql > qr) return {0, - inf}; if(! x) return {0, - inf}; 
		if(ql <= l && r <= qr) return {pl(x), maxn(x)};
		int mid = (l + r) >> 1; pii q1 = {0, - inf}, q2 = {0, - inf};
		if(ql <= mid) q1 = query(lc(x), l, mid, ql, qr);
		if(qr > mid) q2 = query(rc(x), mid + 1, r, ql, qr);
		if(q1.py > q2.py) return {q1.px, q1.py};
		return {q2.px, q2.py};
	}
};
sgtree t[K];

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	for(int i = 1; i <= k; i ++){
		char c; cin >> c;
		if(c == '<') s[i] = 1; else if(c == '=') s[i] = 2; else s[i] = 3;
	}
	memset(dp, - 0x3f, sizeof dp);
	for(int i = 1; i <= n; i ++){
		dp[i][0] = 1; pii tmp1, tmp2, tmp; int flag;
		if(s[1] == 1){
			tmp1 = t[k].query(t[k].rt, 1, inf, 1, a[i] - 1);
			tmp2 = t[0].query(t[0].rt, 1, inf, 1, a[i] - 1);
		}
		if(s[1] == 2){
			tmp1 = t[k].query(t[k].rt, 1, inf, a[i], a[i]);
			tmp2 = t[0].query(t[0].rt, 1, inf, a[i], a[i]);
		}
		if(s[1] == 3){
			tmp1 = t[k].query(t[k].rt, 1, inf, a[i] + 1, inf);
			tmp2 = t[0].query(t[0].rt, 1, inf, a[i] + 1, inf);
		}
		if(tmp1.py > tmp2.py) tmp.py = tmp1.py, tmp.px = tmp1.px, flag = k;
		else tmp.py = tmp2.py, tmp.px = tmp2.px, flag = 0;
		for(int j = k; j >= 2; j --){
			pii tmp; int op = j - 1;
			if(s[j] == 1) tmp = t[op].query(t[op].rt, 1, inf, 1, a[i] - 1);
			if(s[j] == 2) tmp = t[op].query(t[op].rt, 1, inf, a[i], a[i]);
			if(s[j] == 3) tmp = t[op].query(t[op].rt, 1, inf, a[i] + 1, inf);
			if(dp[i][j] < tmp.py + 1){
				dp[i][j] = tmp.py + 1;
				lst[i][j] = {tmp.px, op};
			}
			if(dp[i][j] > 0) t[j].modify(t[j].rt, 1, inf, a[i], i, dp[i][j]);
		}
		if(dp[i][1] < tmp.py + 1){
			dp[i][1] = tmp.py + 1;
			lst[i][1] = {tmp.px, flag};
		}
		if(dp[i][1] > 0) t[1].modify(t[1].rt, 1, inf, a[i], i, dp[i][1]);
		t[0].modify(t[0].rt, 1, inf, a[i], i, dp[i][0]);
	}
	for(int i = 1; i <= n; i ++) for(int j = 0; j <= k; j ++) ans = max(ans, dp[i][j]);
	int x, y;
	for(int i = 1; i <= n; i ++) for(int j = 0; j <= k; j ++) if(dp[i][j] == ans){
		x = i; y = j; break;
	}
	while(y){
		bar[++ top] = x; int tx = x, ty = y;
		x = lst[tx][ty].px; y = lst[tx][ty].py;
	}
	bar[++ top] = x;
	printf("%d\n", ans);
	for(int i = top; i >= 1; i --) printf("%d ", a[bar[i]]);
	puts(""); return 0;
}
```


---

## 作者：Planetary_system (赞：1)

## 题面解释：
在给定的序列中找出长度最长并相邻两项直接关系满足给定条件的子序列。

## 思路分析：
$f_i$ 表示最后一位在 $i$ 的最长子序列长度，那么知道 $f$ 的值就能求出下一位满足的数量关系，只要在前面的找出满足条件的中 $f_i$ 的最大值直接转移就好。

然后这时我们就可以考虑到用三颗权值线段树维护三种符号，直接转移就好。

最后输出序列只需要倒着扫一遍即可，每次找出最后面一个满足条件的。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10; 
int n,k,tot,ans,dp[N],a[N],num[N],rt[10],tr[N<<4],ls[N<<4],rs[N<<4];
char s[N];
inline int Max(int x,int y){
	if(x>y)return x;
	return y;
}
inline void push_up(int p){
	tr[p]=max(tr[ls[p]],tr[rs[p]]);
	return;
}
inline void upd(int &p,int l,int r,int x,int y){
	if(!p)p=++tot;
	if(l==r){
		tr[p]=max(tr[p],y);
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)upd(ls[p],l,mid,x,y);
	else upd(rs[p],mid+1,r,x,y);
	push_up(p);
	return; 
}
inline int qry(int p,int l,int r,int pl,int pr){
	if(l<=pl&&pr<=r)return tr[p];
	int res=0;
	int mid=pl+pr>>1;
	if(ls[p]&&l<=mid)res=max(res,qry(ls[p],l,r,pl,mid));
	if(rs[p]&&mid<r)res=max(res,qry(rs[p],l,r,mid+1,pr));
	return res;
} 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(register int i=1;i<=n;i++)
		cin>>a[i];
	for(register int i=1;i<=k;i++)
		cin>>s[i];
	for(register int i=1;i<=n;i++){
		dp[i]=Max(qry(rt[0],a[i],a[i],0,1e6),
		      Max(qry(rt[2],0,a[i]-1,0,1e6),
			  	  qry(rt[1],a[i]+1,1e6,0,1e6)))+1;
		char ch=s[(dp[i]-1)%k+1];
		if(ch=='=')upd(rt[0],0,1e6,a[i],dp[i]);
		if(ch=='>')upd(rt[1],0,1e6,a[i],dp[i]);
		if(ch=='<')upd(rt[2],0,1e6,a[i],dp[i]);
		ans=Max(ans,dp[i]);
	}
	cout<<ans<<'\n';
	for(int i=n,j=ans;j>0;i--){
		char ch=s[(j-1)%k+1];
		if(dp[i]==j&&(j==ans||ch=='='&&a[i]==num[j+1]||ch=='>'&&a[i]>num[j+1]||ch=='<'&&a[i]<num[j+1]))
			num[j--]=a[i];
	}
	for(int i=1;i<=ans;i++)
		cout<<num[i]<<' ';	
	return 0;
} 
```

谢谢！

---

