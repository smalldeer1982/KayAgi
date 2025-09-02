# Alice's Adventures in Cards

## 题目描述

Alice 正在和红心皇后、红心国王以及红心杰克玩纸牌游戏。这个游戏中有 $ n $ 种不同的纸牌类型。Alice 手上现在有一张类型为 $ 1 $ 的纸牌，她需要通过一系列的交换，得到类型为 $ n $ 的纸牌，才能逃出仙境。而其他三名玩家手上各自持有每种类型的纸牌一张。

在这个游戏中，Alice 可以与这些玩家进行纸牌交换。每位玩家对不同类型纸牌的偏好用排列 $ q $、$ k $ 和 $ j $ 来表示，分别对应红心皇后、红心国王和红心杰克。

对于任意玩家，如果在他们的排列 $ p $ 中，满足 $ p_a > p_b $ ，那么该玩家就认为类型为 $ a $ 的纸牌比类型为 $ b $ 的更有价值。于是，他们愿意用类型为 $ b $ 的纸牌换取类型为 $ a $ 的纸牌。而 Alice 的偏好简单直观：纸牌类型 $ a $ 比类型 $ b $ 更有价值，当且仅当 $ a > b $ ，并且她只会按照这种偏好进行交换。

请判断 Alice 能否通过与其他玩家的交换，从类型为 $ 1 $ 的纸牌升级到类型为 $ n $ 的纸牌。如果可以，请给出可能的交换方案。

$ ^{\text{∗}} $ 长度为 $ n $ 的排列是一个包含 $ n $ 个不同整数（从 $ 1 $ 到 $ n $）的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 和 $ [1,3,4] $ 则不是。

## 说明/提示

在第一个测试用例中，Alice 可以与红心国王交换以获得类型为 $ 2 $ 的纸牌，接着再与红心皇后交换以得到类型为 $ 3 $ 的纸牌。

在第二个测试用例中，尽管 Alice 能与红心皇后交换得到类型为 $ 3 $ 的纸牌，再接着与红心国王交换得到类型为 $ 2 $，最后与红心杰克交换得到类型为 $ 4 $ 的纸牌，但这种方案不符合 Alice 的偏好原则，因此无效。我们可以证明在这种情况下 Alice 无法获得类型为 $ 4 $ 的纸牌。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
3
1 3 2
2 1 3
1 2 3
4
2 3 1 4
1 2 3 4
1 4 2 3```

### 输出

```
YES
2
k 2
q 3
NO```

# 题解

## 作者：CWzwz (赞：2)

[CF2028D Alice's Adventures in Cards](https://www.luogu.com.cn/problem/CF2028D) 题解

[Codeforces](https://codeforces.com/contest/2028/problem/D)

---

奇怪题，好像不太符合 cf 一贯的出题风格。B 题浪费了 50min，赛后 3min 才过 D。菜完了。

玩家手中的数 $a$，可以**直接**变到 $i$，当且仅当在任意一个人的排列 $p$ 中，$p_i>p_a$。

考虑从小到大枚举 $i$，从前面的状态，转移出 $f_i$ 表示数 $i$ 是否可能被玩家拿到。容易做到 $\log$ 转移，三个值域 BIT，每个维护一个人，支持查询：对于所有 $j$ 满足 $p_j>x$ 且 $j<i$，$f_j$ 的或和。

那么 $f_n$ 表示能否拿到 $n$，但是还要输出过程。因为手上的数是越换越大的，所以从 $n$ 往前回溯，记 $now$ 为当前的数这个可以由 $n-1$ 开始，从大到小枚举数 $i$，如果 $i$ 可以被拿到（$f_i=1$）且由 $i$ 可以直接换到 $now$，就跳到 $i$。最后把跳的过程反序输出就行了。

[Submission](https://codeforces.com/contest/2028/submission/290962834)

---

## 作者：xzy090626 (赞：2)

我们考虑跑一个类似于 dijkstra 的东西。每次找编号最小的数 $x$ 来松弛，找到它能走到的所有 $>x$ 的位置。

如何找呢？显然一个数 $y>x$ 合法，当且仅当三个排列中存在其中一个的偏好置换中，$pos_y<pos_x$。那么由于我们需要快速算这个，为了保证复杂度就要把所有 $<x$ 的数删掉。这样，就只需要 $pos_y<pos_x$ 的数了。

我们可以用 set 维护三个排列的偏好置换，按照偏好从小到大排序。每次从 set 的左端开始遍历即可，已经松弛过的位置显然可以在每个 set 中删掉了。复杂度 $O(n\log n)$。

upd：补一下不太美观的代码。需要注意的是，这份题解的做法似乎并不是最简单的解法。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
#include<string>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<time.h>
#include<bitset>
#include<random>
#include<iomanip>
#include<assert.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define pb push_back
using namespace std;
const int N = 2e5 + 7;
int n,m;
pii s[4][N];
int pos[4][N];
set<pii>st[4];
void solve(){
	cin>>n;
	for(int i=1;i<=3;++i) st[i].clear();
	for(int i=1;i<=3;++i){
		for(int j=1;j<=n;++j){
			cin>>s[i][j].x;
			s[i][j].y = j;
		}
		sort(s[i]+1,s[i]+n+1);
		for(int j=1;j<=n;++j){
			st[i].insert({j,s[i][j].y});
			pos[i][s[i][j].y] = j;
		}
	}
	priority_queue<int,vector<int>,greater<int>>q;
	vector<bool>vis(n+5),ok(n+5);
	vector<pii>lst(n+5);
	q.push(1); ok[1] = 1;
	set<int>tt;
	for(int i=2;i<=n;++i) tt.insert(i);
	// ok 代表是否已经被松弛
	while(!q.empty()){
		int u = q.top();q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		vector<int>vec;
		// 找可以去的点
		for(auto c:tt){
			if(c<=u) vec.push_back(c);
			else break;
		}
		for(auto c:vec){
			tt.erase(c);
			ok[c] = 1;
			for(int i=1;i<=3;++i){
				pii tmp = {pos[i][c],c};
				if(st[i].count(tmp)) st[i].erase(tmp);
			}
		}
		vec.clear();
		for(int i=1;i<=3;++i){
			for(auto c:st[i]){
				if(pos[i][c.y]>=pos[i][u]) break;
				if(ok[c.y]) continue;
				if(tt.count(c.y)) tt.erase(c.y);
				ok[c.y] = 1;
				q.push(c.y);
				vec.push_back(c.y);
				lst[c.y] = {u,i};
			}
		}
		// 删掉 u 
		for(auto c:vec){
			for(int i=1;i<=3;++i){
				pii tmp = {pos[i][c],c};
				if(st[i].count(tmp)) st[i].erase(tmp);
			}
		}
	}
	if(!vis[n]){
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
	vector<pii>ans;
	int x = n;
	while(x!=1){
		ans.push_back({x,lst[x].y});
		x = lst[x].x;
	}
	cout<<ans.size()<<'\n';
	reverse(ans.begin(),ans.end());
	for(auto c:ans){
		if(c.y==1) cout<<"q ";
		else if(c.y==2) cout<<"k ";
		else cout<<"j ";
		cout<<c.x<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;cin>>T;
	for(int _=1;_<=T;++_){
		solve();
	}
	return 0;
}
```

---

