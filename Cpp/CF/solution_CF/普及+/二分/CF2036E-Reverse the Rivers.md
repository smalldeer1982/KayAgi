# Reverse the Rivers

## 题目描述

A conspiracy of ancient sages, who decided to redirect rivers for their own convenience, has put the world on the brink. But before implementing their grand plan, they decided to carefully think through their strategy — that's what sages do.

There are $ n $ countries, each with exactly $ k $ regions. For the $ j $ -th region of the $ i $ -th country, they calculated the value $ a_{i,j} $ , which reflects the amount of water in it.

The sages intend to create channels between the $ j $ -th region of the $ i $ -th country and the $ j $ -th region of the $ (i + 1) $ -th country for all $ 1 \leq i \leq (n - 1) $ and for all $ 1 \leq j \leq k $ .

Since all $ n $ countries are on a large slope, water flows towards the country with the highest number. According to the sages' predictions, after the channel system is created, the new value of the $ j $ -th region of the $ i $ -th country will be $ b_{i,j} = a_{1,j} | a_{2,j} | ... | a_{i,j} $ , where $ | $ denotes the [bitwise "OR"](http://tiny.cc/bitwise_or) operation.

After the redistribution of water, the sages aim to choose the most suitable country for living, so they will send you $ q $ queries for consideration.

Each query will contain $ m $ requirements.

Each requirement contains three parameters: the region number $ r $ , the sign $ o $ (either " $ < $ " or " $ > $ "), and the value $ c $ . If $ o $ = " $ < $ ", then in the $ r $ -th region of the country you choose, the new value must be strictly less than the limit $ c $ , and if $ o $ = " $ > $ ", it must be strictly greater.

In other words, the chosen country $ i $ must satisfy all $ m $ requirements. If in the current requirement $ o $ = " $ < $ ", then it must hold that $ b_{i,r} < c $ , and if $ o $ = " $ > $ ", then $ b_{i,r} > c $ .

In response to each query, you should output a single integer — the number of the suitable country. If there are multiple such countries, output the smallest one. If no such country exists, output $ -1 $ .

## 说明/提示

In the example, the initial values of the regions are as follows:

  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 4 $  $ 6 $  $ 5 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 7 $ After creating the channels, the new values will look like this:

  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 1 | 4 $  $ 3 | 6 $  $ 5 | 5 $  $ 9 | 3 $  $ 1 | 4 | 2 $  $ 3 | 6 | 1 $  $ 5 | 5 | 2 $  $ 9 | 3 | 7 $  $ \downarrow $  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 5 $  $ 7 $  $ 5 $  $ 11 $  $ 7 $  $ 7 $  $ 7 $  $ 15 $ In the first query, it is necessary to output the minimum country number (i.e., row) where, after the redistribution of water in the first region (i.e., column), the new value will be greater than four and less than six, and in the second region it will be less than eight. Only the country with number $ 2 $ meets these requirements.

In the second query, there are no countries that meet the specified requirements.

In the third query, only the country with number $ 3 $ is suitable.

In the fourth query, all three countries meet the conditions, so the answer is the smallest number $ 1 $ .

## 样例 #1

### 输入

```
3 4 4
1 3 5 9
4 6 5 3
2 1 2 7
3
1 > 4
2 < 8
1 < 6
2
1 < 8
2 > 8
1
3 > 5
2
4 > 8
1 < 8```

### 输出

```
2
-1
3
1```

# 题解

## 作者：fanminghao000 (赞：4)

由于或运算的性质，每个地区的水量按照国家编号从小到大排序是单调不降的。这个性质非常有利，于是我们可以执行二分来找到能满足每个约束条件的位置：对于 " $>$ "号，可以约束答案区间的起点；对于" $<$ " 号，可以约束答案区间的终点。最后，如果这个答案区间存在，输出区间里最小那个数就行了。时间复杂度 $O(nk+m\log m)$

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
	T=1;
	while(T--){
		int n,k,q;
		cin>>n>>k>>q;
		vector<vector<int> > a(k,vector<int>(n));
		for(int i=0;i<n;i++){
			for(int j=0;j<k;j++){
				cin>>a[j][i];
				if(i>=1) a[j][i]|=a[j][i-1];
			}
		}
		while(q--){
			int st=0,en=2e9+100,ci;cin>>ci;
			while(ci--){
				int r,c;
				char op;
				cin>>r>>op>>c;
				r--;
				if(op=='>'){
					int x=upper_bound(a[r].begin(),a[r].end(),c)-a[r].begin();
					st=max(st,x);
				}
				else{
					int x=lower_bound(a[r].begin(),a[r].end(),c)-a[r].begin();
					en=min(x-1,en);
				}
			}
			//cout<<st<<' '<<en<<endl;
			if(st<=en&&st<n) cout<<st+1<<endl;
			else cout<<-1<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：The_Elation_Aha (赞：2)

这场比赛告诉我们不要因为某道题的题面很长就不耐心看，直接跳到后面，最后遗憾离场。

----

### 题意

你有个 $n\times k$ 的正整数矩阵 $A$，你首先会对它的每一列求一次前缀**或**和。有 $q$ 次询问，每次询问有 $m$ 个限制，形式是对于某一列的第 $r$ 行的值需要严格大于/小于 $c$。你需要选择某一列满足所有限制，求出编号最小的一列，如果没有的话输出 $-1$。

这个题最难的就是理解题意，读懂了做法是好想的：首先要知道对矩阵的每一列进行了一次求前缀**或**和的操作，所以每一列的数是单调不降的，所以就可以二分。

对于每一个限制，自然可以二分到第一个大于/小于 $c$ 的数，记他的行数为 $p$。如果要求大于 $c$，则 $i\in[p,n]$ 的行都可以满足条件；如果要求小于 $c$，则 $i\in[1,p]$ 的行都可以满足条件。

由此，可以想到记录 $L,R$ 表示行数可以取到的范围，要求 $>c$ 则更新 $L$，$<c$ 则更新 $R$，最后看是否 $L\le R$ 就行了，但是还要注意会不会出现某个限制无法被满足的情况。

因为数据是 $n\times k\le 10^5$，所以要用 vector 来存，并且我们为了二分行数，所以 vector 的第一维是列数。

就没了，这种小朋友题真的是只要看了就做得出来，下次再也不因为懒得读题就跳了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const ll N=114514,M=1919810;
ll T;
ll n,m,Q,q;
vector <ll> aa[N],a[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>Q;
	for(int i=0;i<n;++i)
		for(int j=0,x;j<m;++j)
			cin>>x,aa[j].pb(x);
	for(int j=0;j<m;++j)
		for(int i=0;i<n;++i){
			a[j].pb(aa[j][i]);
			if(i) a[j][i]|=a[j][i-1]; //vector 越界会直接 RE 
		}
	while(Q--){
		cin>>q;
		ll fl=0,lx=1,rx=n;
		while(q--){
			ll r,c,p; char op;
			cin>>r>>op>>c,--r; //注意下标 
			if(op=='<'){
				p=lower_bound(a[r].begin(),a[r].end(),c)-a[r].begin();
				if(p<1) fl=1;
				else rx=min(rx,p);
			}
			else{
				p=upper_bound(a[r].begin(),a[r].end(),c)-a[r].begin()+1;
				if(p>n) fl=1;
				else lx=max(lx,p);
			}
		}
		if(lx<=rx&&!fl) cout<<lx<<'\n';
		else cout<<"-1\n";
	}
	return 0;
}/*Stop learning useless algorithm and go to learn how to use binary search*/
```

Besides,stop learning useless algorithms, go and solve some problems, learn how to use binary search.

---

## 作者：Sakura_Emilia (赞：1)

# Solution

这题目乍一看好像是位运算的问题，但其实就是一道普通的二分题目。

注意到在进行或运算的时候，数值一定是单调不减的。因此得到的矩形区域，从上往下各列是依次递增的。因此根据限定条件，对每一列应用二分查找即可。

具体的细节可以参考下面的代码。

还有一点是，由于数组的内存较大，直接开可能会爆，所以在这里开了二维 `vector` 来分配动态内存。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;

int n, k, q, m, r, c, start, End;
char op;
vector<vector<int>> g;

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> k >> q;
    g.resize(n + 1, vector<int>(k + 1));

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= k; j++)
            cin >> g[i][j];
    for(int i = 2; i <= n; i++)
        for(int j = 1; j <= k; j++)
            g[i][j] |= g[i-1][j];

    while(q--){
        start = 1, End = n;
        cin >> m;
        while(m--){
            cin >> r >> op >> c;
            int ll = 1, rr = n;
            if(op == '<'){
                if(g[1][r] >= c)
                    End = -1;
                else{
                    while(ll < rr){
                        int mid = (ll + rr + 1) >> 1;
                        if(g[mid][r] < c)
                            ll = mid;
                        else
                            rr = mid - 1;
                    }
                    End = min(End, ll);
                }
            } else{
                if(g[n][r] <= c)
                    End = -1;
                else{
                    while(ll < rr){
                        int mid = (ll + rr) >> 1;
                        if(g[mid][r] <= c)
                            ll = mid + 1;
                        else
                            rr = mid;
                    }
                    start = max(start, ll);
                }
            }
        }

        if(start <= End)
            cout << start << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}
```

---

## 作者：Segment_Treap (赞：1)

### $\textbf{1. Problem Statement}$
给定一个 $n \times m$ 的二维数组 $a$，之后，对数组进行变换：
>对于任意 $i,j$，$a_{1,j}|a_{2,j}|\dots|a_{i,j} \Rightarrow a_{i,j}$。

此外，还有 $q$ 组询问，每组询问有 $k$ 个条件，条件有两种类型：
- `r < c`，表示答案行第 $r$ 列上的值要 $<c$。
- `r > c`，表示答案行第 $r$ 列上的值要 $>c$。

请求出满足所有条件的行的编号的最小值，如果没有行满足条件输出`-1`。
### $\textbf{2. Hint}$
#### $\textbf{2.1 Hint 1}$
> 满足条件的行编号一定是连续的一段数。
#### $\textbf{2.2 Hint 2}$
> 给定一个数组 $a$，$a$ 的前缀或值单调不减。
### $\textbf{3. Solution}$
在 $\textbf{2.1 Hint 1}$ 中提到
> 满足条件的行编号一定是连续的一段数。

那么我们可以记录 $l,r$，表示满足答案的行编号的最小值和最大值，对于每个条件，就把 $l,r$ 往内缩。

在 $\textbf{2.2 Hint 2}$ 中提到
> 给定一个数组 $a$，$a$ 的前缀或值单调不减。

在变换后 $a$ 的每一列一定都单调不减，那么可以把 $l,r$ 往内缩的过程用倍增优化成 $\log$ 复杂度。

综上所述，对于每一组询问，时间复杂度为 $\Theta(k \times \log(n))$
### $\textbf{4. Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,q;
int main(){
	scanf("%d%d%d",&n,&m,&q);
	vector<vector<int>> a(n+1,vector<int>(m+1,0));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			a[i][j]|=a[i-1][j];
		}
	}
	for(;q--;){
		int k,L=1,R=n;
		scanf("%d",&k);
		for(;k--;){
			int r,c;
			char o;
			scanf("%d %c %d",&r,&o,&c);
			if(o=='>'){
				if(L>n||a[L][r]>c) continue;
				for(int i=20;i>=0;i--){
					if(L+(1<<i)>n) continue;
					if(a[L+(1<<i)][r]<=c) L+=(1<<i);
				}
				L++;
			}else{
				if(R<1||a[R][r]<c) continue;
				for(int i=20;i>=0;i--){
					if(R-(1<<i)<1) continue;
					if(a[R-(1<<i)][r]>=c) R-=(1<<i);
				}
				R--;
			}
		}
		if(L>R) printf("-1\n");
		else printf("%d\n",L);
	}
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2036E)

一道二分题。

发现一个前缀或一定是递增的，因为每一个二进制位要么从 $1$ 变为 $0$，要么不变。

将第 $i$ 个区域的 $n$ 个国家的土地的权值存下来。不难发现，对于每一个询问，最终的答案应该是一个区间。每一个要求相当于是更新区间的左右端点，用二分更新即可。

### Code 
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int K = 200005;
int n, k, q;
vector <int> vec[K];
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> k >> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			int x;
			cin >> x;
			vec[j].push_back(x);
		}
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j < n; j++) vec[i][j] |= vec[i][j - 1];
	}
	while (q--) {
		int m, l = 1, r = n;
		cin >> m;
		for (int i = 1; i <= m; i++) {
			int a, b, pos;
			char op;
			cin >> a >> op >> b;
			if (op == '>') l = Max(l, (int)(upper_bound(vec[a].begin(), vec[a].end(), b) - vec[a].begin() + 1));
			else r = Min(r, (int)(lower_bound(vec[a].begin(), vec[a].end(), b) - vec[a].begin()));
		}
		if (l > r) cout << -1;
		else cout << l;
		cout << '\n';
	}
	return 0;
}
```

---

