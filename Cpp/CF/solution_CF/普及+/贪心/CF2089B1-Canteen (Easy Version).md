# Canteen (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的区别在于此版本中，$$k=0$$。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a\_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 说明/提示

在此版本中，Ecrade 不能对 $$$a$$$ 进行修改。

在第一个测试用例中：
- 第一轮操作后，$$a=[0,0,0]$$，$$b=[4,0,0]$$。

在第二个测试用例中：
- 第一轮操作后，$$a=[3,0,0,1]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[1,0,0,0]$$，$$b=[0,1,0,0]$$；
- 第三轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,0,0]$$；
- 第四轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,0,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1```

### 输出

```
1
4
4
8```

# 题解

## 作者：Pretharp (赞：2)

先简单说一下题意，给定长度为 $n$ 的序列 $a$ 和 $b$，一次操作可以让两个序列中的对应位置减去二者较小值（即 $a_i \gets a_i - \min\{a_i,b_i\}$，$b_i$ 同理），然后将 $a$ 整体循环向右移一位（最后一个数放到序列开头）。问最早多少次操作后 $a$ 中所有数会变为 $0$，保证 $\sum a < \sum b$，即答案在有限次操作内。

先手动模拟观察性质。对于 $a_{l}$ 到 $a_r$，令 $s_1 = \sum\limits_{i=l}^r a_i$，$s_2 = \sum\limits_{i=l}^r b_i$，不难发现在 $r-l+1$ 次操作之后，一定有 $s_1 \gets s_1 - \min\{s_1,s_2\}$ 且 $s_2 \gets s_2 - \min\{s_1,s_2\}$。如果有 $s_1 \le s_2$，那么在 $r-l+1$ 次操作后 $s_1$ 的值一定为 $0$。换而言之，$a_l$ 到 $a_r$ 均变为了 $0$。

所以说对于 $a_i$，令它最早归 $0$ 的时刻为 $t$，那么一定有 $a_i$ 到 $a_{i+t-1}$ 这一段数的和小于等于 $b_i$ 到 $b_{i+t-1}$ 的和（为方便表示，此处并不严谨，假设下标从 $0$ 开始，如果下标 $x \ge n$，则应有 $x \gets x \bmod n$）。

此时我们只需要对于每一个 $a_i$ 求出它的最早归 $0$ 时刻 $t$，再将所有 $t$ 取最大值即为答案。这一过程可以用单调栈维护。实现细节参见[提交记录](https://codeforces.com/problemset/submission/2090/312014063)。

---

## 作者：sbno333 (赞：2)

赛时做了很一会。

我们考虑我们不是转 $a$ 数组，而是 $b$ 数组，显然就是向左转。

对于一个位置 $i$，我们考虑 $a_i$ 变为 $0$ 的时刻。

如果 $a_i\le b_i$，就是 $1$。

否则我们考虑转的 $b_i$。

如果是时刻 $2$，我们要满足 $a_i+a_{i+1}\le b_i+b_{i+1}$。事实上，通过简单归纳，问题转化为找到最小的 $c$ 满足 $\sum_{j=i}^{i+c-1}a_i\le \sum_{j=i}^{i+c-1}b_i$，当然因为是环所以稍微处理一下。

然后求所有这样的 $c$ 的最大值即可。

此处的转化容易证明，这里不过多赘述。

我们有个显然的套路就是断环成长度两倍的链，自然做就行。

我们让每个 $a_i$ 减去 $b_i$。

每个 $i$ 找到最小的 $c$ 使得 $\sum_{j=i}^{i+c-1}a_i\le 0$，求 $c$ 最大值。

我们可以实时线段树维护对于每个 $i$ 的 $c$，然后算最大值。

可是我们代码能力太弱了，又懒，怎么办呢？

发现转化后还有个点没用到就是我们求最大值就行。

所以我们可以维护此时的最大值。

考虑以 $i$ 开头所有长度在最大值以内的前缀和。

如果大于 $0$ 就暴力增加答案，往后扩容更多前缀和。

然而，如果答案不变，我们就麻烦了。

当 $i$ 向前一点的时候，所有前缀和都要加一个数，然后加入一个值，但是之前范围内的，现在可能不在范围内。

猛地，我们想到单调队列。

于是每次就是 $i$ 走一格以后如果队头在范围外就删掉。

然后前缀和都加上一个数，计懒标记即可。

然后加入自己。

然后如果队头大于 $0$，就暴力向后推，如果比队头小就加到队头变成新队头，否则不贡献，知道队头小于 $0$。

这里的代码把数组翻转，方便思考，所以维护后缀和。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define F first
#define S second
using namespace std;
int a[1000009];
pii q[1000009];
int h=300000,t=299999;
void _main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		int b;
		cin>>b;
		a[i]-=b;
	}
	for(int i=n+1;i<=n+n;i++){
		a[i]=a[i-n];
	}
	h=300000,t=299999;
	q[h]={0,-1e16};
	n*=2;
	for(int i=1;i<=n/2;i++){
		swap(a[i],a[n-i+1]);
	}
	int qq;
	qq=0;
	int ma;
	ma=1;
	int hz;
	hz=-1e18;
	a[0]=-1e18;
	for(int i=1;i<=n;i++){
		hz-=a[i-ma];
		hz+=a[i];
		if(h<=t){
			if(q[h].F<=i-ma){
				++h;
			}
		}
		int aa;
		aa=a[i];
		qq+=aa;
		aa-=qq;
		while(h<=t&&aa<=q[t].S){
			t--;
		}
		q[++t]={i,aa};
		while(q[h].S+qq>0){
			hz+=a[i-ma];
			ma++;
			if(hz-qq<q[h].S){
				q[--h]={i-ma,hz-qq};
			}
		}
	}
	cout<<ma<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

写得非常丑陋，导致只能过 Easy。

我们定义“有效操作”为 $t>0$ 的操作，即 $\min\{a_i,b_i\}>0$ 的操作，注意到操作完成之后只会剩下 $1$ 个非 $0$ 值，所以其实只有 $2n$ 个有效操作。

现在问题转化为了，我们如何快速带修地维护“有效操作”。

显然先破环为链，我们显然是找需要操作次数最少的“有效操作”进行配对。即每个 $a$ 找到它右边的一个 $b$ 进行配对，每个 $b$ 找到它左边的一个 $a$ 进行配对，对于每个配对，我们把它塞到 `set` 里就能求出最少移动数了。

注意如果有两个相同的 $a$ 配同一个 $b$，显然我们只用考虑后面的 $a$；如果两个相同的 $b$ 配同一个 $a$，那么显然只用考虑前面的一个 $b$。

显然对于一次有效操作，我们有如下 $3$ 种情况（另 $i'$ 表示 $i$ 前面的非零值，令 $j'$ 表示 $j$ 后面的非零值，“重构”是指重新寻找配对而并不一定会改变配对）：

- $a_i>b_j$，显然 $i,j'$ 要重构，因为 $j'$ 可能会配到 $i$。

- $a_i=b_j$，显然需要重构 $i',j'$。

- $a_i<b_j$，同 $a_i>b_j$ 的对称情况，需要重构 $i',j$。

显然非 $0$ 值用 `set` 维护就行了，因为带 $\log n$ 所以过不了 B2。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=2e5+5;
int T,n,k,a[N<<1],b[N<<1];
bool visa[N<<1],visb[N<<1];
set<int> A,B;
struct Node{
	int first,second;
	bool operator <(const Node &o) const{
		if(second-first!=o.second-o.first) return second-first>o.second-o.first; 
		if(first!=o.first) return first>o.first;
		return second>o.second;
	}	
};
priority_queue<Node> q;
void rebuildA(int pos){
	if(a[pos]){
		auto it=B.lower_bound(pos);
		if(it!=B.end()&&!visb[*it]) q.emplace(Node({pos,*it})),visa[pos]=visb[*it]=1;
	} else{
		auto it=A.lower_bound(pos);
		if(it!=A.begin()){
			--it;
			if(!visa[*it]) rebuildA(*it);
		}
	}
}
void rebuildB(int pos){
	if(b[pos]){
		auto it=A.upper_bound(pos);
		if(it!=A.begin()){
			--it;
			if(!visa[*it]) q.emplace(Node({*it,pos})),visa[*it]=visb[pos]=1;
		}
	} else{
		auto it=B.lower_bound(pos);
		if(it!=B.end()&&!visb[*it]) rebuildB(*it);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		A.clear(),B.clear();
		while(q.size()) q.pop();
		for(int i=1;i<=(n<<1);++i) visa[i]=visb[i]=0;
		for(int i=1;i<=n;++i) cin>>a[i],a[i+n]=a[i],A.insert(i),A.insert(i+n),visa[i]=visa[i+n]=1;
		for(int i=1;i<=n;++i) cin>>b[i],b[i+n]=b[i],B.insert(i),B.insert(i+n),q.emplace(Node({i,i})),q.emplace(Node({i+n,i+n})),visb[i]=visb[i+n]=1;
		int ans=0;
		while(A.size()&&(*A.begin())<=n){
			vector<Node> v;
			vector<int> va,vb;
			ans=q.top().second-q.top().first+1;
			while(q.size()&&q.top().second-q.top().first+1==ans){
				v.emplace_back(q.top());
				q.pop();
			}
			for(auto p:v){
				if(a[p.first]<b[p.second]){
					b[p.second]-=a[p.first];
					a[p.first]=0,A.erase(p.first);
				} else if(a[p.first]==b[p.second]) a[p.first]=b[p.second]=0,A.erase(p.first),B.erase(p.second);
				else{
					a[p.first]-=b[p.second];
					b[p.second]=0,B.erase(p.second);
				}
			}
			for(auto p:v) visa[p.first]=visb[p.second]=0,va.emplace_back(p.first),vb.emplace_back(p.second);
			sort(va.begin(),va.end());
			sort(vb.begin(),vb.end());
			reverse(va.begin(),va.end());
			for(auto p:va) rebuildA(p);
			for(auto p:vb) rebuildB(p);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

