# Sum Graph

## 题目描述

This is an interactive problem.

There is a hidden permutation $ p_1, p_2, \dots, p_n $ .

Consider an undirected graph with $ n $ nodes only with no edges. You can make two types of queries:

1. Specify an integer $ x $ satisfying $ 2 \le x \le 2n $ . For all integers $ i $ ( $ 1 \le i \le n $ ) such that $ 1 \le x-i \le n $ , an edge between node $ i $ and node $ x-i $ will be added.
2. Query the number of edges in the shortest path between node $ p_i $ and node $ p_j $ . As the answer to this question you will get the number of edges in the shortest path if such a path exists, or $ -1 $ if there is no such path.

Note that you can make both types of queries in any order.

Within $ 2n $ queries (including type $ 1 $ and type $ 2 $ ), guess two possible permutations, at least one of which is $ p_1, p_2, \dots, p_n $ . You get accepted if at least one of the permutations is correct. You are allowed to guess the same permutation twice.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ n=6 $ and the hidden permutation $ p = [1,4,2,5,3,6] $ .

Firstly, make a type $ 1 $ query on $ x=12, 2, 3 $ respectively. This adds four edges to the graph in total:

- An edge that connects node $ 6 $ and node $ 6 $ .
- An edge that connects node $ 1 $ and node $ 1 $ .
- An edge that connects node $ 1 $ and node $ 2 $ .
- An edge that connects node $ 2 $ and node $ 1 $ .

Since all of these queries are valid, the interactor returns $ 1 $ after each of them.

Then, query the number of edges in the shortest path between node $ p_1 = 1 $ and $ p_3 = 2 $ , which is equal to $ 1 $ .

Then, make a type $ 1 $ query on $ x=5 $ . This adds four edges to the graph in total:

- An edge that connects node $ 1 $ and node $ 4 $ .
- An edge that connects node $ 2 $ and node $ 3 $ .
- An edge that connects node $ 3 $ and node $ 2 $ .
- An edge that connects node $ 4 $ and node $ 1 $ .

Since this query is valid, the interactor returns $ 1 $ .

Then, query the number of edges in the shortest path between node $ p_1 = 1 $ and $ p_5 = 3 $ , which is equal to $ 2 $ .

Then, query the number of edges in the shortest path between node $ p_4 = 5 $ and $ p_5 = 3 $ . Such a path doesn't exist, therefore the interactor returns $ -1 $ .

Afterwards, due to some magic, two possible permutations that can be $ p $ are determined: the first permutation is $ [1,4,2,5,3,6] $ and the second permutation is $ [1,2,3,4,5,6] $ . Since the first permutation is equal to the hidden permutation, this test case is solved correctly. In total, $ 7 $ queries are used, which is within the limit of $ 2 \cdot 6 = 12 $ queries.

Since the answer is correct, the interactor returns $ 1 $ .

In the second test case, $ n=2 $ and the hidden permutation is $ p = [2,1] $ .

Since there are only $ 2! = 2 $ possible permutations, no queries are needed. It is sufficient to just output the two permutations, $ [1,2] $ and $ [2,1] $ . In total, $ 0 $ queries are used, which is within the limit of $ 2 \cdot 2 = 4 $ queries.

Since the answer is correct, the interactor returns $ 1 $ .

## 样例 #1

### 输入

```
2
6

1

1

1

1

1

2

-1

1
2

1```

### 输出

```
+ 12

+ 2

+ 3

? 1 3

+ 5

? 1 5

? 4 5

! 1 4 2 5 3 6 1 2 3 4 5 6


! 1 2 2 1```

# 题解

## 作者：Nuisdete (赞：2)

很诈骗。

如果想要连一次边查一次最短路这样的是做不出来的，我们考虑换一个思路。

不如一次性连完边再查最短路。

那么我们肯定是想要连成一个特殊的图，比如树这样的。

树有 $n - 1$ 条边，我们取 $x = n$ 和 $x = n + 1$ 连上然后发现图成了一条链。

链上就非常好求解了，随意取一个点问 $n - 1$ 次可以找到一个端点，然后再用端点问 $n - 1$ 次就能够得到答案序列了。

因此我们不知道是左端点还是右端点，所以可以把两种情况都输出出来。

总询问次数是 $2n$，CF 官方题解里有更优秀的做法。

注意交互格式。

Code: [https://codeforc.es/problemset/submission/1815/201783591](https://codeforc.es/problemset/submission/1815/201783591)

---

## 作者：Hisaishi_Kanade (赞：2)

如果原图连成一棵树或者一个图还是什么，查最短路就很不好处理了。

我们大胆猜一手，如果可以连出一条链，然后确定一个端点就结束了。

具体的，设我们知道这个端点是 $u$，则对 $v\in[1,n]\wedge u\not = v$，进行 `? u v` 的操作。

注意到，我们不能确定这个端点在最开始还是最结束，所以正反都输出一次。

现在用了 $n-1$ 次操作。

如何确定这个端点？我们这次随便随便找一个点 $u$，然后对 $v\in[1,n]\wedge u\not = v$，进行 `? u v` 的操作。我们知道，我们查完之后排个序，必然是前 $1\sim x$ 出现 了两次，$x+1\sim n-x-1$ 出现一次。不难想到，$n-x-1$ 这个点必然是一个端点。

又用了 $(n-1)$ 次操作。

要求 $2n$，我们还有两次，需要两次连成一条链。

随便猜一个形态。 $1\to n\to 2\to n-1 \to 3\cdots$。

这是对的，我们发现从左往右数第奇数条边两端之和是 $n+1$，偶数是 $n+2$。

所以最开始连两次边：$n+1$ 和 $n+2$。

总共恰好 $2n$ 次。注意 `!` 输出答案之后还有一个输入 $1$。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define clr() fflush(stdout);
using namespace std;
const int N=2e3+5; int t, n, l, r; int ans[N], ret[N], p[N], ord[N];
inline int ask(int x, int y)
{
	printf("? %d %d\n", x, y); clr();
	scanf("%d", &x);
	return x;
}
inline void addedge()
{
	scanf("%d", &n);
	printf("+ %d\n", n+2); clr(); scanf("%*d");
	printf("+ %d\n", n+1); clr(); scanf("%*d");
	return ;
} int i, ms, mx, pos;
inline void decide()
{
	mx=ms=0; pos=0;
	rep(i, 2, n)
	{
		ms=ask(1, i);
		if(ms>mx)
		{
			mx=ms;
			pos=i;
		}
	}
}
inline void print()
{
	rep(i, 1, pos-1) ans[i]=ask(pos, i)+1;
	rep(i, pos+1, n) ans[i]=ask(pos, i)+1;
	printf("! ");
	l=1; r=n; ans[pos]=1; rep(i, 1, n) if(i&1) ord[i]=l++; else ord[i]=r--;
//	rep(i, 1, n) printf("%d\n", ord[i]);
	rep(i, 1, n) p[i]=ord[ans[i]]; rep(i, 1, n) printf("%d ", p[i]);
	rep(i, 1, n) p[i]=ord[n-ans[i]+1]; rep(i, 1, n) printf("%d ", p[i]); puts("");
	clr(); scanf("%*d");
	return ;
}
int main()
{
	scanf("%d", &t);
	while(t--) {addedge(); decide(); print();}
	return 0;
}
// 1-6-4-3-2-5
// 1-5
```

---

## 作者：World_Creater (赞：1)

被 $2000$ 交互题薄沙力 /kk。

这个题开始基本上没什么思路。

考虑先询问 $n+1$ 和 $n+2$。

不难发现这样连出来的是一条链：

![](https://cdn.luogu.com.cn/upload/image_hosting/t6a8ysbr.png)

如果我们知道了这条链的端点，我们就可以通过 $n-1$ 次询问得到其他节点的位置，注意到这条链虽然有两个端点，但由于回答允许我们给出两个排列，因此我们可以当成一个端点做。

考虑找出端点：我们询问所有点与 $1$ 的距离，距离最远的点一定是一个端点，这需要进行 $n-1$ 次询问。

然后根据找到的这个端点，再进行 $n-1$ 次询问得到其他节点的位置。

总询问 $n-1+n-1+2=2n$ 可以通过本题（后面的 $2$ 是一开始的连边）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int modify(int x)
{
	cout<<"+ "<<x<<endl;
	int t;
	cin>>t;
	return t;	
}
int query(int x,int y)
{
	cout<<"? "<<x<<" "<<y<<endl;
	int t;
	cin>>t;
	return t;
}
int n,ans1[2005],ans2[2005],p[2005],dis1[2005],dis2[2005];
pair<int,int> maxn;
void end()
{
	cout<<"! ";
	for(int i=1;i<=n;i++)
	{
		cout<<ans1[i]<<" ";
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans2[i]<<" ";
	}
	cout<<endl;
	int t;
	cin>>t;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		memset(dis1,0,sizeof(dis1));
		memset(dis2,0,sizeof(dis2));
		memset(ans1,0,sizeof(ans1));
		memset(ans2,0,sizeof(ans2));
		memset(p,0,sizeof(p));
		maxn={0,-1};
		modify(n+1),modify(n+2);
		p[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(i&1) p[i]=n+2-p[i-1];
			else p[i]=n+1-p[i-1];//把链的信息弄出来。
			// cerr<<p[i]<<" ";
		}
		for(int i=2;i<=n;i++)
		{
			dis1[i]=query(1,i);
			maxn=max(maxn,{dis1[i],i});//找到端点。
		}
		for(int i=1;i<=n;i++)
		{
			if(i==maxn.second) continue ;
			dis2[i]=query(maxn.second,i);//依靠距离来算出其他点的位置。
		}
		ans1[maxn.second]=1;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(dis2[j]==i) ans1[j]=p[i+1];
			}
		}
		ans2[maxn.second]=p[n];
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(dis2[j]==i) ans2[j]=p[n-i];
			}
		}
		end();
	}
}
```

---

## 作者：Hooch (赞：0)

可以发现若加入 $x=n+1$ 和 $x=n$，则图会变成（$n=6$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/jj3kjbgn.png)

形成了一条 $6\to 1\to 5\to 2\to 4\to 3$ 的链，也就是 $n\to 1\to (n-1)\to \cdots \to \left\lfloor{n+1\over 2}\right\rfloor$。

如果我们随便找一个 $i$，然后对于每个 $j$ ( $j\ne i$ )， 都询问 `? i j`，找到询问过程中路径长度（就是交互器给出的输入）最大的 $k$。显然对于图中任意一个点，只有链头或者链尾离它最远，所以可以确定 $p_k$ 就是链首或链尾。

我们再次对于每个 $j$ ( $j\ne k$ )，都询问 `? j k`，因为 $p_k$ 是链尾或链首，所以询问的结果一定是 $1\sim n-1$ 的排列。若我们知道 $p_k$ 到底是 $n$ 还是 $\left\lfloor{n+1\over 2}\right\rfloor$，很容易就能推出序列 $p$。题目中指出要输出两个 $p$ 序列，若其中一个对就通过。所以我们把 $p_k$ 的两种情况都输出即可。询问次数刚好是 $2n$。

---

## 作者：Mr_Gengar (赞：0)

一道因缺思厅的交互题。

首先考虑通过操作一，用尽量少的次数使图联通。

不难想到可以使用 `+ n+1` 和 `+ n+2` 使图变成一条链（`+ n` 和 `+ n+1` 也可行）。

然后随机选定一个点与其他所有点求最短路，显然与该点距离最长的点一定为该链的其中一个端点。

最后将该点作为其中一个端点与其它所有点求最短路，就可以确定所有点的位置。

因为端点有两个，所以要将该点置于链的两端求出两种可能，分别输出即可。

最终正好用完 $2n$ 次操作，可以通过本题。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int kMaxN = 1e3 + 1;

LL t, n, l, r, x, p, mx, a[kMaxN], b[kMaxN], c[kMaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n, mx = 0, l = 1, r = n;
    cout << "+ " << n + 1 << endl, cin >> x;
    cout << "+ " << n + 2 << endl, cin >> x;
    for (int i = 1; i <= n; i++) {
      c[i] = (i & 1 ? l++ : r--);
    }
    for (int i = 2; i <= n; i++) {
      cout << "? 1 " << i << endl;
      cin >> x;
      if (x > mx) {
        mx = x, p = i;
      }
    }
    a[p] = c[1], b[p] = c[n];
    for (int i = 1; i <= n; i++) {
      if (i == p) {
        continue;
      }
      cout << "? " << p << " " << i << endl;
      cin >> x;
      a[i] = c[1 + x], b[i] = c[n - x];
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " ";
    }
    for (int i = 1; i <= n; i++) {
      cout << b[i] << " ";
    }
    cout << endl;
    cin >> x;
  }
  return 0;
}
```

---

## 作者：zhlzt (赞：0)

###  题解

首先，分别使 $x=n+1$ 和 $n+2$，使用类型 1 操作。显然，所有节点构成一条链（例如，当 $n=6$ 时，应该为  $1 - 6 - 2 - 5 - 3 - 4$ ）。

接下来，使用类型 2 查询 $(1,i)~(2 \le i \le n)$，取查询结果的最大值。设 $pos$ 为查询结果最大时对应的 $i$。易知，节点 $p_k$ 是链的端点之一。

然后，使用类型 2 查询 $(i,pos)~(1\le i \le n\land i\neq pos)$。由于节点 $p_k$ 是链的一个端点，因此所有查询结果都是不同的，从 $p_k$ 出发的长度为 $n-1$ 的路径也就知道了。

虽然节点 $p_k$ 到底是哪个端点并不清楚，但这个问题很容易解决：因为这个问题允许输出两个满足条件排列组合，所以最后只需要尝试两个端点并输出相应的排列组合即可。

总共使用了 $2$ 次类型 1 运算和 $2(n-1)$ 次类型 2 运算，总计 $2n$ 次运算。这么做，复杂度是 $O(tn)$ 的，时间非常宽松。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int ans1[maxn],ans2[maxn];
int dp[maxn];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		printf("+ %d\n",n+1); fflush(stdout);
		int rub1;scanf("%d",&rub1);
		printf("+ %d\n",n+2); fflush(stdout);
		int rub2;scanf("%d",&rub2);
		int pos=0,dis=0;
		for(int i=2;i<=n;i++){
			printf("? 1 %d\n",i); fflush(stdout);
			int temp;scanf("%d",&temp);
			if(temp>dis) dis=temp,pos=i;
		}
		dp[0]=pos;
		for(int i=1;i<=n;i++){
			if(i==pos) continue;
			printf("? %d %d\n",pos,i); fflush(stdout);
			int temp;scanf("%d",&temp); dp[temp]=i;
		}
		for(int i=0;i<n;i++){
			if(i&1^1) ans1[dp[i]]=(i>>1)+1;
			if(i&1^0) ans1[dp[i]]=n-(i>>1);
			int j=n-1-i;
			if(j&1^1) ans2[dp[i]]=(j>>1)+1;
			if(j&1^0) ans2[dp[i]]=n-(j>>1);
		}
		printf("! "); fflush(stdout);
		for(int i=1;i<=n;i++) printf("%d ",ans1[i]);
		for(int i=1;i<=n;i++) printf("%d ",ans2[i]);
		printf("\n"); fflush(stdout);
		int rub;scanf("%d",&rub);
	}
	return 0;
} 
```

---

## 作者：Leasier (赞：0)

Brainful problem /jw

一定要注意交互格式啊啊啊！！！

------------

题目只要求我们给出两种可能的答案 $(p_1, p_2)$ 这一点是很奇怪的，注意到每次询问的 $i, j$ 是**无向图**的最短路，则我们只能得出 $p$ 和 $\operatorname{rev}(p)$。

- 这里可以参考样例的第二组数据 $n = 2$，此时我们无法确定 $p$ 是 $[1, 2]$ 还是 $[2, 1]$。

我们希望将整张图连通以便进行询问，考虑令 $x = n + 1$ 进行一次操作。此时 $\forall 1 \leq i \leq \lfloor \frac{n}{2} \rfloor$，有边 $(i, n - i + 1)$。此时原图被分为 $\lceil \frac{n}{2} \rceil$ 个连通块，看上去不太能操作。

注意到无论我们令 $x$ 为几，只加一条边都会遇到这样的窘境 /ng

我们期待图的形态看上去比较特殊，注意到若再令 $x = n + 2$ 进行一次操作，此时原图变为：

- $1 \to n \to 2 \to n - 1 \to 3 \to n - 2 \to \cdots$，这样的数字时对应位置的值。

这样的链的形态看上去比较符合我们的期待，现在考虑问出这条链。

不妨随意钦定一个点——比如说 $1$，我们尝试问出这条链上到 $1$ 距离指定的点。此后，我们可以依次问出 $1$ 两侧的点的下一个点。

最终操作次数 $\leq 2n - 1$，可以通过。

代码：
```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int dis[1007], nxt[1007], p1[1007], p2[1007];
deque<int> q1, q2;
vector<int> v[1007];

inline void init(int n){
	for (int i = 1; i <= n; i++){
		nxt[i] = 0;
		v[i].clear();
	}
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, one;
		cin >> n;
		init(n);
		cout << "+ " << n + 1 << endl;
		cout.flush();
		cout << "+ " << n + 2 << endl;
		cout.flush();
		for (int j = 2; j <= n; j++){
			int dis;
			cout << "? 1 " << j << endl;
			cout.flush();
			cin >> dis;
			v[dis].push_back(j);
		}
		for (int j = 2; !v[j].empty(); j++){
			int dis;
			cout << "? " << v[j][0] << " " << v[j - 1][0] << endl;
			cout.flush();
			cin >> dis;
			if (dis == 1){
				nxt[v[j - 1][0]] = v[j][0];
				if (v[j - 1].size() == 2 && v[j].size() == 2) nxt[v[j - 1][1]] = v[j][1];
			} else {
				nxt[v[j - 1][1]] = v[j][0];
				if (v[j].size() == 2) nxt[v[j - 1][0]] = v[j][1];
			}
		}
		q1.clear();
		q1.push_back(1);
		for (int j = v[1][0]; j != 0; j = nxt[j]){
			q1.push_back(j);
		}
		if (v[1].size() > 1){
			for (int j = v[1][1]; j != 0; j = nxt[j]){
				q1.push_front(j);
			}
		}
		for (int j = 1; j <= n; j++){
			p1[q1[j - 1]] = j;
		}
		q2.clear();
		q2.push_back(1);
		if (v[1].size() > 1){
			for (int j = v[1][1]; j != 0; j = nxt[j]){
				q2.push_back(j);
			}
		}
		for (int j = v[1][0]; j != 0; j = nxt[j]){
			q2.push_front(j);
		}
		for (int j = 1; j <= n; j++){
			p2[q2[j - 1]] = j;
		}
		cout << "! ";
		for (int j = 1; j <= n; j++){
			cout << p1[j] << " ";
		}
		for (int j = 1; j <= n; j++){
			cout << p2[j] << " ";
		}
		cout << endl;
		cout.flush();
	}
	return 0;
}
```

---

