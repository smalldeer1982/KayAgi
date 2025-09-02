# Yunli's Subarray Queries (easy version)

## 题目描述

**这是该问题的简单版本。保证所有问题中，$r=l+k-1$ 。**

### 题面描述

对于任意数组 $b$，可以多次执行以下操作：

- 选择一个下标 $i$，令 $b_i=x$， 其中 $x$ 为任意整数（不限于区间 $[1,n]$ ）。

记 $f(b)$ 为数组 $b$ 中，存在一个长度至少为 $k$ 的连续子数组$^*$ 的最小操作次数。

给出一个大小为 $n$ 的数组 $a$，然后询问 $q$ 个问题。在每个问题中，你必须输出 $∑_{j=l+k-1}^r f([a_l,a_{l+1},…,a_j])$。注意在该题中，只被要求输出$f([a_l,a_{l+1},…,a_j])$。


------------
$^*$ 如果存在一个长度为 $k$ 的连续子数组，且开始于下标 $i$ $(1≤i≤|b|−k+1)$，则对于所有$i<j≤i+k−1$，满足 $b_j=b_{j−1}+1$。

## 说明/提示

保证在所有样例中，$n$ 的总和不超过 $2⋅10^5$，$q$ 的总和不超过$2⋅10^5$。


在第一个样例的第一个问题中，$b=[1,2,3,2,1]$。可以执行两次操作以构造一个长度为 $5$ 的连续子数组：

- 令$b_4=4$；
- 令$b_5=5$。

经过以上操作后，$b=[1,2,3,4,5]$。

在第一个样例的第二个问题中，$b=[2,3,2,1,2]$。可以执行三次操作以构造一个长度为 $5$ 的连续子数组：

- 令$b_3=0$；
- 令$b_2=-1$；
- 令$b_1=-2$。

经过以上操作后，$b=[-2,-1,0,1,2]$。

翻译提供：[zhoujy1209](https://www.luogu.com.cn/user/946085)。

## 样例 #1

### 输入

```
3
7 5 3
1 2 3 2 1 2 3
1 5
2 6
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
2 5
5 4 2
4 5 1 2 3
1 4
2 5```

### 输出

```
2
3
2
2
2
2
1```

# 题解

## 作者：PNNNN (赞：5)

### G1

题目要求，对于一个子区间 $a_{l\sim l+k-1}$，最少要进行多少次单点修改，才能使 $\forall \  l < i \leq l+k-1,a_i=a_{i-1}+1$，其中 $k$ 是固定的。

对于这种问题，我们通常有一个 trick：将 $a_i$ 变为 $a_i-i$。这样的话，我们要求的答案就变为了 $k$ 减去变化后的 $a_{l\sim l+k-1}$ 中众数的出现次数。这个可以用线段树或者莫队做。

以下是线段树的代码，为了避免出现 $a_i < 0$，这里将 $a_i$ 变为了 $a_i-i+n$。

[代码](https://codeforces.com/contest/2009/submission/284650406)

时间复杂度为 $O(n\times\log n)$。

### G2
我们先用 G1 的方法求出 $f(\{a_i,a_{i+1},\dots, a_{i+k-1}\})$，并设其为 $w_i$。

与 G1 不同，G2 要求的的是 $\sum \limits_{i=l}^{r-k+1} \min \limits_{j=l}^{i} w_j$，其中 $r \geq l+k-1$。

看到对一段前缀取最小值，我们考虑如何模拟出这一过程。设 $p_0=l$，每次往后找到离 $p_0$ 最近的满足 $w_{p_0} > w_p$ 的 $p$，此时 $\min \limits_{j=l}^{i} w_j=w_{p_0}(p_0\le i\le p - 1)$，这段对答案的贡献为 $(p-p_0)\times w_{p_0}$ ，再将 $p_0$ 设为 $p$。不断这样做下去，直到 $p_0$ 后已经没有 $w_{p_0}>w_p$ 或者 $p_0>r-k+1$。

我们不可能每次询问都这样暴力做一次，考虑如何优化。显然，对于每个 $p_0$，其后最近的满足 $w_{p_0} > w_p$ 的 $p$ 都是不变的。考虑提前将每个 $p_0$ 的 $p$ 求出来，这个可以用单调栈求。然后我们需要用到另一个 trick：将 $p$ 向 $p_0$ 连一条长度为 $(p-p_0)\times w_{p_0}$ 的边，这样连出来一定是棵树。（我也不太清楚这个 trick 的名字，可能跟 AC 自动机的优化差不多。）

这样我们可以在树上二分出最后一个不大于 $r-k+1$ 的 $p_0$。具体实现：先一遍 dfs 将 $dep_i$ 和 $dis_i$ 求出，其中 $dep_i$ 表示 $i$ 的深度，$dis_i$ 表示 $i$ 到根节点（为了方便设为 $n-m+2$）的距离。接着将二分的左起始点设为 $1$，右起始点设为 $dep_l$，判断 $l$ 在树上的 $dep_l-mid$ 级祖先是否小于等于 $r-k+1$，移动 $l$ 和 $r$ 进行二分，设二分出来的答案为 $res$。这时答案就为 $dis_l-dis_{res}+(r-k-res+2)\times w_{res}$。

[代码](https://codeforces.com/contest/2009/submission/279915573)

我的树上 k 级祖先是用重链剖分求的，因此时间复杂度为 $O(n\times \log^2 n)$。可以将重链剖分换成长链剖分之类的，时间复杂度可以降到 $O(n\times\log n)$。或许可以直接上历史和线段树?

### G3
G3要求的东西变为了 $\sum \limits_{i=l}^{r-k+1} \sum \limits_{j=i}^{r-k+1} \min \limits_{g=i}^{j} w_g$。类似这种式子套上[P3246 [HNOI2016] 序列](https://www.luogu.com.cn/problem/P3246)的方法就行了。不知道能否将G2的方法继续扩展到G3，我还没想出来，如果可以的话还请告诉我！

这里仅仅贴一份用莫队实现的代码，具体思路还请参考 [P3246 [HNOI2016] 序列](https://www.luogu.com.cn/problem/P3246) 的题解：

[代码](https://codeforces.com/contest/2009/submission/280066658)

---

## 作者：Super_Cube (赞：3)

# Solution

设 $b_i=f([a_i,a_{i+1},\ldots,a_{i+k-1}])$，那么答案为 $b_l$。

对 $a$ 中所有数执行 $a_i\gets a_i-i$，那么原问题（修改最少的数使得区间变为公差为 $1$ 的递增数列）变为了新问题：修改最少的数使得区间所有数相等。肯定把非区间众数改为区间众数是最优的，所以 $b_i$ 即为 $k$ 减区间 $[i,i+k-1]$ 中众数的出现次数。

由于 $k$ 为定值，可利用类似滑动窗口的模式预处理出 $b_i$。

时间复杂度：$O(n+q)$。

---

## 作者：_H17_ (赞：0)

## 题目分析

既然是等差数列，需要满足 $a_i=a_{i-1}+1$，显然放在整个序列中，判断等差数列的办法就是 $a_i-i$ 是否都相等。

题目的询问是 $[l,r]$ 使用最少得修改使得 $a[l,r]$ 是等差数列（显然此时题目要求了 $r-l+1=k$，即全部区间）。

什么情况修改最少？找到最多的相等的 $a_i-i$。

最后一点：如何处理询问：考虑将所有询问离线，然后进行滑动窗口即可。

时间复杂度 $O(n\log n)$。其中 $\log$ 是因为 STL 容器（其实也可以理解为数据结构）维护造成的。

---

## 作者：cly312 (赞：0)

题目要求 $a_i=a_{i-1}+1$，设 $b_i=a_i-i$，如果 $b_i=b_j$，那么 $i$ 和 $j$ 就在正确的相对位置上。这应该很好理解吧，$a$ 是一个公差为 $1$ 的等差数列，下标也是一个公差为 $1$ 的等差数列，对应位置相减就相等了。

我们在输入 $a_i$ 的时候减去 $i$，然后用滑动窗口维护每个区间内出现最多的元素次数即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,qq;
int a[N],f[N]; 
int l,r;
void solve(){
	memset(a,0,sizeof a);
	memset(f,0,sizeof f);
	cin>>n>>k>>qq;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	 	a[i]=a[i]-i;
	}
	multiset<int> q; 
	map<int,int> h;
	for(int i=1;i<=n;i++){
		int v=h[a[i]]++;
		if(q.find(v)!=q.end()){
			q.erase(q.find(v));
		}
		q.insert(v+1);
		if(i>=k){
			f[i]=*q.rbegin();
			int w=h[a[i-k+1]]--;
			q.insert(w-1);
			if(q.find(w)!=q.end()){
				q.erase(q.find(w));
			}
		}
	}
	while(qq--){
		cin>>l>>r;
		int ans=k-f[r];
		cout<<ans<<'\n';
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```
也可以用莫队维护这个值：
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n,k,m;
	cin>>n>>k>>m;
	vector<int>a(n+1),bel(n+1);
	int tot=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]-=i;
		bel[i]=i/tot;
	}
	vector<vector<int>>q(m+1,vector<int>(3));
	for(int i=1;i<=m;i++){
		cin>>q[i][0]>>q[i][1];
		q[i][2]=i;
	}
	sort(q.begin()+1,q.end(),[&](auto &x,auto &y){
		if(bel[x[0]]!=bel[y[0]])return bel[x[0]]<bel[y[0]];
		if(bel[x[0]]&1) return x[1]<y[1];
		return x[1]>y[1];
	});
	vector<int> cnt(2*n+1,0);
	vector<int> sum(n+1,0);
	int mx=0;
	auto add=[&](int x){
		cnt[a[x]+n]++;
		sum[cnt[a[x]+n]]++;
		if(cnt[a[x]+n]>mx)mx=cnt[a[x]+n];
	};
	auto del=[&](int x){
		if(cnt[a[x]+n]==mx){
			if(sum[cnt[a[x]+n]]==1) mx--;
		}
		sum[cnt[a[x]+n]]--;
		cnt[a[x]+n]--;
	};
	vector<int>ans(m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(q[i][0]<l) add(--l);
		while(q[i][1]>r) add(++r);
		while(q[i][0]>l) del(l++);
		while(q[i][1]<r) del(r--);
		ans[q[i][2]]=q[i][1]-q[i][0]+1-mx;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：forever516 (赞：0)

# 题意
十分清晰，不做赘述。

# 解法
题目让我们输出构造一个公差为一的等差数列所需的操作数，这看起来有点难办。但是我们看到下标数列，可以发现这也是一个公差为一的等差数列！

于是我们可以对于
$a_i$
做操作
$a_i-1$。此时我们再观察，这就变成了输出构造一个公差为零的等差数列所需的操作数。这样本题就变成了维护以众数为键值的滑动窗口。

注意，这是可以事先离线预处理好的。最后答案就是输出
$k$
减去众数的出现次数即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,q,l,r;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k>>q;
		vector<int>a(n+1),f(n+2,0);
		map<int,int>head;
		multiset<int>s;
		for(int i=1;i<=n;i++)cin>>a[i],a[i]-=i;
		//本来是为了求要换几次，才能使数列成为d=1的等差数列
		//这样做可以让问题简化成要改几次使得序列相等 
		for(int i=1;i<=n;i++){
			int tmp=head[a[i]]++;
			if(s.find(tmp)!=s.end())s.erase(s.find(tmp));
			//模拟单调栈 
			s.insert(tmp+1);
			if(i>=k){
				f[i]=*s.rbegin();//本题的特殊情况 
				int w=head[a[i-k+1]]--;
				s.insert(w-1);
				if(s.find(w)!=s.end())s.erase(s.find(w));
			}
		}
		while(q--){
			cin>>l>>r;
			cout<<k-f[r]<<"\n";
		}
	}

	return 0;
}

```

---

