# [ARC180B] Improve Inversions

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_b

$ (1,2,\cdots,N) $ の順列 $ P=(P_1,P_2,\cdots,P_N) $ が与えられます． また整数 $ K $ も与えられます．

あなたはこれから以下の操作を $ 0 $ 回以上行います．

- 整数 $ l,r $ ($ 1\ \leq\ l\ <\ r\ \leq\ N $) を選ぶ．ただしここで $ (l,r) $ は以下の条件をすべて満たす必要がある．
  - $ K\ \leq\ r-l $
  - 操作を行う段階で $ P_l\ >\ P_r $ である．
  - 同じ組 $ (l,r) $ を今までに選んだことが一度もない．
- そして，$ P_l $ と $ P_r $ の値を入れ替える．

あなたは操作回数を最大化したいです． その方法を一つ求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ K\ \leq\ N-1 $
- $ (P_1,P_2,\cdots,P_N) $ は $ (1,2,\cdots,N) $ の順列
- 入力される値はすべて整数

### Sample Explanation 1

この例では操作回数の最大値は $ 3 $ です． 出力例の操作の様子は以下のとおりです． - $ 1 $ 回目の操作: $ (l,r)=(2,3) $ を選ぶ．$ 1\ \leq\ 3-2,\ P_2\ >\ P_3 $ かつ $ (2,3) $ を選んだことはないので条件は満たされている．$ P_2,P_3 $ の値を入れ替え，$ P=(3,1,2) $ になる． - $ 2 $ 回目の操作: $ (l,r)=(1,3) $ を選ぶ．$ 1\ \leq\ 3-1,\ P_1\ >\ P_3 $ かつ $ (1,3) $ を選んだことはないので条件は満たされている．$ P_1,P_3 $ の値を入れ替え，$ P=(2,1,3) $ になる． - $ 3 $ 回目の操作: $ (l,r)=(1,2) $ を選ぶ．$ 1\ \leq\ 2-1,\ P_1\ >\ P_2 $ かつ $ (1,2) $ を選んだことはないので条件は満たされている．$ P_1,P_2 $ の値を入れ替え，$ P=(1,2,3) $ になる．

## 样例 #1

### 输入

```
3 1
3 2 1```

### 输出

```
3
2 3
1 3
1 2```

## 样例 #2

### 输入

```
5 4
1 4 3 2 5```

### 输出

```
0```

## 样例 #3

### 输入

```
4 2
4 1 2 3```

### 输出

```
2
1 4
1 3```

## 样例 #4

### 输入

```
10 5
8 7 6 10 9 3 1 5 2 4```

### 输出

```
15
3 8
2 8
3 10
3 9
1 8
2 10
2 9
2 7
1 10
5 10
1 9
4 10
4 9
1 7
1 6```

# 题解

## 作者：_lmh_ (赞：13)

贪心策略：枚举 $1\cdots n$ 的每个数 $i$，每次找出所有比它小的能和它交换的数，从大到小依次交换。称其为第 $i$ 轮交换。

例如：

```
10 5
8 7 6 10 9 3 1 5 2 4
```

枚举到 6 的时候发现它能和 5 2 4 交换，就先交换 5，再交换 4，最后交换 2。

第六轮交换的三步完成之后的结果应该是：

```
8 7 2 10 9 3 1 6 4 5
```

现在证明正确性。

首先证明交换次数为 $\sum_{i=1}^n\sum_{j=i+k}^n[a_i \ge a_j]$。

注意到，考虑每个数 $i$ 的时候所有数只有大于 $i$ 和小于等于 $i$ 的区别，而枚举 $1\cdots i-1$ 的时候交换到数都小于 $i$，不会对此产生影响。

再证明答案最大值为 $\sum_{i=1}^n\sum_{j=i+k}^n[a_i \ge a_j]$。

注意到它等价于把每组合法的交换方案拉出来同时执行。

如果进行了交换 $i,j(i<j)$，那么 $a_i$ 肯定变小，$a_j$ 肯定变大。

所以，对于 $u\le i-k$ 或 $u>j-k$，显然以它为左端点的合法交换方案数不变；对于 $i-k<u \le j-k \wedge u \ne i$，以它为左端点的合法方案数最多减一，如果 $u=i$ 则至少减一。

因此答案最大值就是初始的合法方案数，所以贪心策略是正确的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=507;
ll n,ans,a[N],pos[N],ok[N],k;
vector<pair<ll,ll> > vec;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for (int i=1;i<=n;++i) {cin>>a[i];pos[a[i]]=i;}
	for (int i=1;i<=n;++i){
		for (int j=1;j<i;++j) ans+=(ok[j]=(pos[j]>=pos[i]+k));
		ll now=i;
		for (int j=i-1;j;--j) if (ok[j]){
			vec.push_back(make_pair(pos[now],pos[j]));
			swap(pos[now],pos[j]);
			now=j;
		}
	}
	cout<<ans<<'\n';
	for (auto p:vec) cout<<p.first<<' '<<p.second<<'\n';
	return 0;
}
```

---

## 作者：Mirage_Insane (赞：4)

读完题之后应该很容易联想到逆序对，只不过前后两个位置 $l, r$ 之间须满足 $r - l \geq K$。

为了与平常的逆序对分开，下文称满足上述条件的逆序对为**绝对逆序对**。

操作次数的最大值就是这个排列的绝对逆序对个数。

难点在于如何拉序列。因为题目中有要求：一对 $(l, r)$ 最多只能出现一次，所以不能用普通的拉序列方式。

考虑贪心。

先假定当前枚举到 $i$ 位置，在其后面寻找能与其构成绝对逆序对的位置，设为 $j$，如果直接交换 $P_i$ 和 $P_j$，可能不是最优的。例子很好举：```4 1 2 3```，当 $K = 2$ 时，显然 $(1, 3)$ 和 $(1, 4)$ 都是绝对逆序对，但如果选择交换 $(1, 3)$ 的话，你就会发现```2 1 4 3```这个序列没有绝对逆序对了。解决方法也很显然，只需要在 $i$ 后面找到最大的数，并且能够与其构成绝对逆序对，再交换即可。

那么该按照怎样的顺序枚举 $i$ 呢？如果直接遍历的话也有问题，手玩最后一个样例容易发现，最初的序列中 $(3, 8)$ 是一个绝对逆序对，然而 $P_1$ 在进行完上述操作后会停留在第 8 个位置，这会使得 $(3, 8)$ 不再是一个绝对逆序对，不优。解决方法也容易发现，以序列 $P$ 中的元素大小为依据，从小到大依次访问每个下标就可以了。比如序列```4 1 2 3```，先访问 $i = 2$，再访问 $i = 3$，接着访问 $i = 4$，最后访问 $i = 1$ 即可解决问题。

由于 $P$ 是一个排列，既避免了元素重复等很多麻烦，也能进一步确保正确性。

时间复杂度 $\mathbb{O}(n^3)$，实际上找最大值那部分可以用数据结构优化一下，能够做到 $\mathbb{O}(n^2\log_n)$，但 $n$ 最大也就 500，实在没必要。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
int a[505], p[505];
bool cmp(int i, int j) {
	return a[i] < a[j];
}
vector<pair<int, int> > res; 
int main() {
	int n, m, ans = 0;
	SF("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) SF("%d", &a[i]), p[i] = i;
	sort(p + 1, p + 1 + n, cmp);
	for(int i = 1; i <= n;) {
		int Max = 0, id = -1;
		for(int j = p[i] + m; j <= n; j++) {
			if(a[p[i]] > a[j]) {
				if(a[j] > Max) {
					Max = a[j];
					id = j;
				}
			}
		}
		if(id == -1) i++;
		else {
			ans++;
			res.push_back(make_pair(p[i], id));
			swap(a[p[i]], a[id]);
		}
	}
	PF("%d\n", ans);
	for(pair<int, int> i : res) PF("%d %d\n", i.first, i.second);
	return 0;
}
```

---

## 作者：Targanzqq (赞：3)

### 思路：模拟+贪心

在这个题中 $n\le 500$，我们可以轻易想到用较高的 的复杂度来解这个题。首先我们考虑交换，我们要尽可能用小的去换大的，所以我们使用两层循环，第一层从小到打枚举，第二层从大到小枚举，如果第二层枚举的数比第一层小且位置在第一层的 $k$ 位以后，则直接把它们交换。

我们仔细研究一下，因为如果这个数交换了，假设说与当前数为 $i$，与 $i$ 交换的数为 $j$，枚举完 $j$ 之后，后面的数显然比 $j$ 小，如果可以换的话一定要换，因为我们的目的是增加交换次数，**而这样换是没有后效性的**。主要有两点原因：

- 我们从小到大枚举第一层，那么更大的数的位置不会变。
- 我们把大数和小数交换，把大数换到后面去，也增加了更大的数与这个数交换的机会

因此，如果我们按以上规则“能换则换”，对当前数需要交换的更小的数和比当前数更大的数来说没有影响。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k,a[501],p[501],ans;

vector<int> ans1,ans2;

signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];p[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
	    int now=0;
	    for(int j=i-1;j>=1;j--){
	    	if(p[j]>=p[i]+k){
	    		ans++;
	    		ans1.push_back(p[i]);
	    		ans2.push_back(p[j]);
	    		swap(p[i],p[j]);
	    		i=j;
			}
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans1.size();i++){
		cout<<ans1[i-1]<<" "<<ans2[i-1]<<endl;
	}
}
```

---

## 作者：incra (赞：3)

### Solution
考虑贪心的操作，对于任意满足条件的 $(i,j)$，不妨设 $i<j$，则我们按照 $a_i$ 从小到大，$a_j$ 从大到小删，一定最优。

简单证明：大的数能被删一定要在尽可能早的删，如果迟了就删不了了。
### Code
[Link](https://atcoder.jp/contests/arc180/submissions/55021797)。

---

## 作者：ClearluvXL (赞：2)

# B - Improve Inversions

## 思路

首先如果我们此时的位置是 $l$，我们能够进行操作的位置的范围是 $[l+k,n]$。

那么我们在当前的 $[l+k,n]$ 中找出能够满足 $a_{l}>a_{i}$ 的位置 $i$。假设满足条件的位置有 $k$ 个。

可以肯定的是，此时最多能够进行 $k$ 次交换。理由如下：

- 第一次选择集合内最大的数 $r$，将 $l,r$ 交换，此时集合内剩下的数依旧满足距离条件，并且因为我们取出的是最大的数，所以此时集合内剩余的数都比交换后的 $l$ 小。

那么我们能够进行这个操作一共 $k$ 次（如果每对 $(l,r)$ 都没被用过的话）。

现在考虑是从那些位置开始呢？

根据贪心的思想来说：我们应该从小的数的位置开始，为什么呢？每次交换，毫无疑问，会将更大的数放在后面，更小的数放在前面。

这对于前面的数的交换情况不影响，但是会影响中间的交换情况。

`3 6 5 1 2 4 7`

现在我们假设 $l$ 为 $6$ 所在位置，当 $k=3$ 时，那么他能交换的数为 $2,4$。如果此时我们按照上述方法交换了，$6$ 到 $4$，$4$ 到 $2$，$2$ 到 $6$。此时 $5$ 就没有可以交换的了。但是，不难观察到在此之前 $5$ 其实可以和 $4$ 交换的，并且并不影响 $6$ 的交换次数。

所以我们从初始位置上数更小的位置开始是更优的，并且还能够保证，交换到当前位置的数，一定是在之前就完成了可能的交换操作的，因为换到这个位置的数一定比当前的数小，也就一定在当前数之前操作。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int,int> pii;

const int N=510;
const int mod=998244353;

int n,k;
int a[N];
 
vector<pii> ans;

bool sg[N][N];

vector<pii> so;
 
int main(){
	
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		so.push_back({a[i],i});
	}
	
	sort(so.begin(),so.end());
	
	for(int i=0;i<n;i++){
		int l=so[i].se;
		vector<pii> q;
		for(int r=l+k;r<=n;r++){
			q.push_back({a[r],r});
		}
		if(l+k<=n){
			sort(q.begin(),q.end());
			reverse(q.begin(),q.end());
			bool flag=1;
			while(flag){
				flag=0;
				for(auto [x,r]:q){
					if(!sg[l][r]&&a[l]>a[r]){
						swap(a[l],a[r]);
						sg[l][r]=1;
						ans.push_back({l,r});
						flag=1;
						break;
					}
				}	
			}
		}
	}
	
	cout<<ans.size()<<endl;
	for(auto [l,r]:ans){
		cout<<l<<" "<<r<<endl; 
	}
	
	return 0;
}//end
```

---

