# Min Cost Permutation (Hard Version)

## 题目描述

The only difference between this problem and the easy version is the constraints on $ t $ and $ n $ .

You are given an array of $ n $ positive integers $ a_1,\dots,a_n $ , and a (possibly negative) integer $ c $ .

Across all permutations $ b_1,\dots,b_n $ of the array $ a_1,\dots,a_n $ , consider the minimum possible value of $ $$$\sum_{i=1}^{n-1} |b_{i+1}-b_i-c|. $ $  Find the lexicographically smallest permutation  $ b $  of the array  $ a $  that achieves this minimum.</p><p>A sequence  $ x $  is lexicographically smaller than a sequence  $ y $  if and only if one of the following holds:</p><ul><li>  $ x $  is a prefix of  $ y $ , but  $ x \\ne y $ ;</li><li> in the first position where  $ x $  and  $ y $  differ, the sequence  $ x $  has a smaller element than the corresponding element in  $ y$$$.

## 说明/提示

In the first test case, it can be proven that the minimum possible value of $ \sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c| $ is $ 27 $ , and the permutation $ b = [9,3,1,4,5,1] $ is the lexicographically smallest permutation of $ a $ that achieves this minimum: $ |3-9-(-7)|+|1-3-(-7)|+|4-1-(-7)|+|5-4-(-7)|+|1-5-(-7)| = 1+5+10+8+3 = 27 $ .

In the second test case, the minimum possible value of $ \sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c| $ is $ 0 $ , and $ b = [1,3,5] $ is the lexicographically smallest permutation of $ a $ that achieves this.

In the third test case, there is only one permutation $ b $ .

## 样例 #1

### 输入

```
3
6 -7
3 1 4 1 5 9
3 2
1 3 5
1 2718
2818```

### 输出

```
9 3 1 4 5 1
1 3 5
2818```

# 题解

## 作者：Alex_Wei (赞：13)

### *[CF1844F2 Min Cost Permutation (Hard Version)](https://www.luogu.com.cn/problem/CF1844F2)

首先观察到，如果 $x \leq y$，那么 $|x - 1 - c| + |y + 1 - c| \geq |x - c| + |y - c|$，也就是和一定，数值越集中答案越小。于是猜测当 $c\geq 0$ 时递增一定能取到最小值。可以调整法，可以从 $c = 0$ 的特殊情况理解。这样就解决了 $c\geq 0$。

设 $c < 0$。注意到 $b_{i + 1} - b_i$ 的总和为 $b_n - b_1$，启发我们去掉绝对值符号得到下界 $b_n - b_1 - (n - 1) c$。发现每个 $b_{i + 1} - b_i < c$ 的 “下坠” 会在下界的基础上产生 $2(c + (b_i - b_{i + 1}))$ 的代价，因此就是要让 $b_{i} - b_{i + 1} > -c$ 的 $b_i - b_{i + 1}$ 总和尽量小，且 $b_n - b_1$ 尽量小。

将 $a$ 从大到小排序，则 $a$ 一定能取到最小值（调整法，结合上述分析和下文感性理解），和 $c \geq 0$ 时递增取到最小值相呼应。但 $a$ 的字典序不一定最小。

考虑 $a$ 的每个下坠 $a_i - a_{i + 1} > -c$。一个下坠不产生代价的必要条件是 $b_1\leq a_{i + 1}\leq a_i \leq b_n$，但此时 $b_n - b_{1}$ 相较于原来的 $a_n - a_1$，至少增加了 $2(a_i - a_{i + 1}) > 2(c + b_i - b_{i + 1})$，也就是增加的代价大于抵消的代价。而下坠是不交的，所以增加的总代价一定大于抵消下坠的代价之和。这说明每个下坠必然产生代价。在此基础上，为使 $b_n - b_1$ 最小，显然 $b_n$ 一定为 $a$ 的最小值 $a_n$，$b_1$ 一定为 $a$ 的最大值 $a_1$。

现在，我们要做的就是在相较于 $a$，**不新增或扩大任何下坠** 的基础上，最小化字典序。

有个很直接的贪心：

> 初始令 $b_1 = a_1$，删去 $a_1$。设 **所有元素互不相同**。设当前已知 $b_i$ 求 $b_{i + 1}$，且所有未被删去的元素集合为 $S$。
>
> 找到 $S$ 中不小于 $b_i + c$ 的最小的元素 $S_j$，使得 $S_j$ 不是最大值也不是最小值，且删去 $S_j$ 之后，不会新增下坠，即 $S_j$ 的前驱（$S$ 中大于 $S_j$ 的最小值）减去后继（$S$ 中小于 $S_j$ 的最大值）不大于 $-c$，则 $b_{i + 1} = S_j$，删去 $S_j$。
>
> 若 $S_j$ 不存在，那么如果删去的不是 $S$ 的最大值，那么一定新增了下坠，不优。删去 $S$ 的最大值。
>
> 要求 $S_j\geq b_i + c$ 是因为我们不会无缘无故地选择 $b_i - b_{i + 1}$ 为下坠，除非迫不得已：就算选了 $S$ 的最大值，也会产生下坠。这说明 $b_i - b_{i + 1}$ 就是 $a$ 的下坠，可以放心选。

关于 $S_j$ 的求法，维护集合 $T$ 表示所有前驱减后继不大于 $-c$ 的元素，修改 $S$ 时对应修改 $T$ 即可。显然只有 $\mathcal{O}(1)$ 个位置需要更新。

若 $a$ 有相同的元素，改成维护位置即可，相当于为相同元素钦定了大小关系。

时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1844/submission/213462577)。

---

## 作者：Leasier (赞：3)

请先查看[这篇题解](https://www.luogu.com.cn/blog/Leasier/solution-CF1844F1)。

现在我们只考虑 $c < 0$ 的情况。

考虑硬拆调整法中的不等式。忽略 $i = 1$ 或 $j = n$ 的情况并给值相同的 $a_i, a_{i + 1}$ 钦定大小顺序可得：

- $a_{j + 1} - a_{j - 1} \geq c$ 且 $a_j - b_{i - 1} \geq c$。

注意到 $b_1 = a_1$，考虑从这里开始一个一个调整出正确的 $b_i$ 以避免 $i = 1$ 的特判。

用一个 set 维护所有满足 $a_{j + 1} - a_{j - 1} \geq c$ 的二元组 $(a_j, j)$，每次取出 $a_j$ 最小的满足该条件者（如不存在则取出全局最大者，这里相当于是对 $j$ 相关的 corner case 的特批）加入答案，并用一个双向链表维护“$a_{i - 1}, a_{i + 1}$”即可。

时间复杂度为 $O(\sum n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

int a[200007], l[200007], r[200007], ans[200007];
set<pair<int, int> > s;

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, c;
		cin >> n >> c;
		for (int j = 1; j <= n; j++){
			cin >> a[j];
		}
		if (c >= 0){
			sort(a + 1, a + n + 1);
			for (int j = 1; j <= n; j++){
				ans[j] = a[j];
			}
		} else {
			sort(a + 1, a + n + 1, greater<int>());
			l[n + 1] = n;
			r[0] = 2;
			for (int j = 2; j <= n; j++){
				l[j] = j == 2 ? 0 : j - 1;
				r[j] = j + 1;
			}
			ans[1] = a[1];
			for (int j = 3; j < n; j++){
				if (a[r[j]] - a[l[j]] >= c) s.insert(make_pair(a[j], j));
			}
			for (int j = 2; j <= n; j++){
				int pos, p, q;
				set<pair<int, int> >::iterator it = s.lower_bound(make_pair(ans[j - 1] + c, 0));
				if (it == s.end()){
					pos = r[0];
				} else {
					pos = it->second;
					s.erase(it);
				}
				ans[j] = a[pos];
				p = l[pos];
				q = r[pos];
				r[p] = q;
				l[q] = p;
				if (l[p] == 0 || q > n || a[q] - a[l[p]] < c) s.erase(make_pair(a[p], p));
				if (p == 0 || r[q] > n || a[r[q]] - a[p] < c) s.erase(make_pair(a[q], q));
			}
		}
		for (int j = 1; j <= n; j++){
			cout << ans[j] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

$c\geq0$ 时，不难发现取排序好的 $a$ 即可取到最小值的同时取到最小字典序。

下面考虑 $c<0$ 的情况，以下设 $c'=|c|$。

首先同样可以感性理解出 $a$ 倒序可以取到最小值，然而不是最小字典序。

对于所有倒序排列后 $a_i-a_{i+1}\leq c'$ 的位置，其贡献为 $c'-(a_i-a_{i+1})$。对于所有其他位置，其贡献为 $(a_i-a_{i+1})-c'$。要想贡献不变，我们需要所有取 $(a_i-a_{i+1})-c'$ 的位置不变，剩下来分出的段一定满足第一个为段内最大值，最后一个为最小值。

考虑分成若干个段分别最优化最小字典序。贪心每一步选取最小符合要求的值。注意到一个值符合要求，当且仅当他未被选入序列的大于等于他的第一个数减去未被选入序列的小于等于他的第一个数不超过 $c'$（显然，此时我们可以在加入这个数后从大到小假如剩余的）。使用链表+线段树维护每个位置是否合法即可。总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
int a[1000005];
int lst[1000005],nxt[1000005],ok[1000005];
int merge(int x,int y){
	if(y) return y;
	else return x;
}
struct sgt{
	int f[1000005];
	void build(int i,int l,int r){
		if(l==r){
			if(ok[l]) f[i]=l;
			else f[i]=0;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int pos,int val){
//		if(pos<l||pos>r) exit(2);
		if(l==r){
			f[i]=val*l;
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos,val);
		else change(i*2+1,mid+1,r,pos,val);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql>qr) exit(2);
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return merge(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
int cnt=0;
void solve(){
	int n,c; cin>>n>>c; for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	if(c>=0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return ;
	}
	c=-c;
	reverse(a+1,a+n+1);
	vector<int> ans;
	for(int i=1;i<=n;i++){
		int j=i;
		while(j<n&&a[j]-a[j+1]<=c) j++;
		for(int k=i;k<=j;k++) lst[k]=k-1,nxt[k]=k+1;
		lst[i]=0,nxt[j]=0;
		for(int k=i;k<=j;k++) if(lst[k]==0||nxt[k]==0||(a[lst[k]]-a[nxt[k]]<=c)) ok[k]=1; else ok[k]=0;
		tree.build(1,i,j);
		int now=i; tree.change(1,i,j,i,0);
		if(i!=j) tree.change(1,i,j,i+1,1);
		lst[nxt[now]]=0;
		ans.push_back(a[now]);
		if(i==j) continue;
		while(1){
//			cout<<i<<" "<<j<<" "<<now<<"\n";
			int l=i,r=j-1;
			while(l<r){
				int M=(l+r+1)>>1;
				cnt++;
				if(a[M]<a[now]-c) r=M-1;
				else l=M;
			}
			l=min(l,j-1);
//			cout<<l<<" ";
			int p=tree.qry(1,i,j,i,l);
			if(!p)break;
//			if(p<i||p>l) exit(3);
//			cout<<l<<" "<<p<<"\n";
			tree.change(1,i,j,p,0);
			if(lst[p]){
				nxt[lst[p]]=nxt[p];
				if(nxt[lst[p]]&&lst[lst[p]]){
					if(a[lst[lst[p]]]-a[nxt[lst[p]]]>c) tree.change(1,i,j,lst[p],0);
				}
				else{
					tree.change(1,i,j,lst[p],1);
				}
			}
			if(nxt[p]){
				lst[nxt[p]]=lst[p];
				if(nxt[nxt[p]]&&lst[nxt[p]]){
					if(a[lst[nxt[p]]]-a[nxt[nxt[p]]]>c) tree.change(1,i,j,nxt[p],0);
				}
				else{
					tree.change(1,i,j,nxt[p],1);
				}
			}
			ans.push_back(a[p]);
			now=p;
		}
		ans.push_back(a[j]);
		i=j;
	}
	if(ans.size()!=n) exit(4);
	for(auto v:ans) cout<<v<<" "; cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t; cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

这么难的 $2800$！

有一个初步结论：若 $c \geq 0$ 则对 $a$ 从小到大排序，$c < 0$ 就倒着排序。这样可以取到最小值。

考虑权值的产生。一个式子是 $|b_{i + 1} - b_i - c|$ 的形式，如果这个值是一个正数，那么绝对值相当于没有加；但是如果是负数（设为 $-x$），则可以看作“亏损”了 $2x$ 的权值。而它为负数就是说 $b_i - b_{i + 1} > -c$，因此我们要做的就是尽量减少 $b_i - b_{i + 1}$ 在大于 $-c$ 时超出的部分（如果不超出则无所谓）。

考虑确认答案的过程，现在已经确认了 $b_{[1, i - 1]}$，要找到尽量小的 $a_j$ 满足这个超出部分的和不增加。那么这可以等价为以下两个条件：

- $a_{j - 1} - a_{j + 1} \leq -c$（否则产生了新的超出情况，不优）
- $b_{i - 1} - a_j \leq -c$（同理）

因此用 set 维护出满足 $a_{j - 1} - a_{j + 1} \leq -c$ 的所有 $a_j$，再每次从中选出满足条件二中最小的即可。选不出来就是说无论如何都要产生超出部分。鉴于这个部分越小越好，我们直接选剩下 $a$ 的最大值。

---

