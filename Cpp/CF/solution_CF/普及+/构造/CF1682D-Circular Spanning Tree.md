# Circular Spanning Tree

## 题目描述

There are $ n $ nodes arranged in a circle numbered from $ 1 $ to $ n $ in the clockwise order. You are also given a binary string $ s $ of length $ n $ .

Your task is to construct a tree on the given $ n $ nodes satisfying the two conditions below or report that there such tree does not exist:

- For each node $ i $ $ (1 \le i \le n) $ , the degree of node is even if $ s_i = 0 $ and odd if $ s_i = 1 $ .
- No two edges of the tree intersect internally in the circle. The edges are allowed to intersect on the circumference.

Note that all edges are drawn as straight line segments. For example, edge $ (u, v) $ in the tree is drawn as a line segment connecting $ u $ and $ v $ on the circle.

A tree on $ n $ nodes is a connected graph with $ n - 1 $ edges.

## 说明/提示

In the first test case, the tree looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/a3c1924547a7a2cf2e2e161bdb11c580efe3e855.png)In the second test case, there is only one possible tree with an edge between $ 1 $ and $ 2 $ , and it does not satisfy the degree constraints.

In the third test case,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/e5b3e28053fdc3d6ed84005d3e46d8276c4f8576.png) The tree on the left satisfies the degree constraints but the edges intersect internally, therefore it is not a valid tree, while the tree on the right is valid.

## 样例 #1

### 输入

```
3
4
0110
2
10
6
110110```

### 输出

```
YES
2 1
3 4
1 4
NO
YES
2 3
1 2
5 6
6 2
3 4```

# 题解

## 作者：KiloP (赞：8)

首先观察一下，当给定的总度数和是奇数时，肯定不行。

又发现，当每个点的度数模 $2$ 均为 $0$ 时，肯定不是一棵树，也不行。

猜想：剩下的都可以，下面来构造。

分情况讨论（于此与原 CF 题解略有不同）

* 若每个点的度数均为奇数，那么此时 $n$ 一定是偶数。

  那么我们就任选一点为根，连出一个菊花图即可。

* 否则，此时度数为奇数的点有偶数个，设为 $k$，此时，选一个度数为偶数的点为根。

  我们将根移除后的字符串以如下方式断开（将字符串认为是循环的）
  $$
  [0,0,\dots,1][0,0,\dots,1]\cdots[0,0,\dots,1]
  $$
  共 $k$ 组

  从根连出 $k$ 条链，每条链顺次连接上面一对方括号内的点，这样就能保证题目的条件满足。

下面说明这样构造的树没有其余交点。

首先，菊花图肯定是没有的。

来看后一种情况，此时，边只能分为两类：从根连出去的边和圆上相邻两个点之间的边。显然，两组边内部没有其他交点，而后者不可能与前者交于圆内部（画图理解下）。

这样这题就做完了，不懂的看代码吧（代码丑，不喜勿喷）。

```cpp
#include<bits/stdc++.h>

template<typename _Ty> void __(_Ty &x) {
	bool neg = false;
	unsigned c = getchar();
	for (; (c ^ 48) > 9; c = getchar()) if (c == '-') neg = true;
	for (x = 0; (c ^ 48) < 10; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	if (neg) x = -x;
}
template<typename _Ty> _Ty& read(_Ty &x) { __(x); return x; }
template<typename _Ty, typename ..._Tr> void read(_Ty &x, _Tr&... r) { __(x); read(r...); }

using namespace std;

int main() {

	int t, n;
	string s;
	for (read(t); t--; ) {
		read(n);
		cin >> s; s = " " + s;
		int _0 = 0, _1 = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '0') _0++;
			else _1++;
		}
		if (_1 % 2 != 0 || _1 == 0) {
			puts("NO");
			continue;
		}
		puts("YES");
		if (_0 == 0) {
			for (int i = 2; i <= n; ++i) cout << "1 " << i << endl;
		} else {
			int idx = 0;
			for (int i = 1; i <= n; ++i) if (s[i] == '0' && s[(i + n - 2) % n + 1] == '1') { idx = i; break; }
			int now = idx % n + 1;
			while (now != idx) {
				cout << idx << ' ' << now << endl;
				while(s[now] != '1') {
					cout << now << ' ' << now % n + 1 << endl;
					now = now % n + 1;
				}
				now = now % n + 1;
			}
		}
		
	}
	
	return 0;

}


```

---

## 作者：D2T1 (赞：4)

[Codeforces link](https://codeforces.com/problemset/problem/1682/D)

[Luogu link](https://www.luogu.com.cn/problem/CF1682D)

# 题解 CF1682D

## Part 0. 无解情况

首先考虑无解情况。

首先，若 $s$ 中 $\texttt{1}$ 的个数是奇数，肯定无解。

其次，树肯定是有叶子的，而叶子的度数肯定是 $1$，所以若 $s$ 中没有任何一个 $\texttt{1}$，也无解。

其余情况都有解。

------------

## Part 1. 含有偶数度数节点的情况

我们可以把序列拆分成若干个 $[\texttt0,\texttt0,...,\texttt0,\texttt1]$ 的子序列（单独的 $\texttt1$ 也可以作为一个子序列）。注意这是个环，所以序列首尾相接。然后任意挑出一个位于某个子序列首的 $\texttt0$ 作为根。接下来：

- 每个序列连成一条链；
- 每个序列的第一个元素接上根节点。

因为 $\texttt1$ 有偶数个，所以链也有偶数条，从而根节点的度数也是偶数，符合题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/1rot6lyu.png)

------------

## Part 2. 不含有偶数度数节点的情况

任意挑一个节点为根，构造菊花图即可。

```cpp
//CF1682D
#include <cstdio>

const int N = 2e5 + 10;
int t, n;
char s[N];

int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d%s", &n, s+1);
		
		int cnt = 0;
		for(int i = 1; i <= n; ++ i){
			if(s[i] == '1'){
				++ cnt;
			}
		}
		if(cnt == 0 || cnt & 1){
			puts("NO");
			continue;
		}
		puts("YES");
		
		if(cnt == n){
			for(int i = 2; i <= n; ++ i){
				printf("1 %d\n", i);
			}
			continue;
		}
		
		int st = 0;
		if(s[n] == '1' && s[1] == '0'){
			st = 1;
		} else {
			for(int i = 1; i <= n; ++ i){
				if(!st && s[i] == '0' && s[i-1] == '1'){
					st = i;
				}
			}
		}
		
		#define pre(i) (i==1 ? n : i-1)
		#define nxt(i) (i==n ? 1 : i+1)
		bool flg = true;
		for(int i = st+1; flg || i < st; ++ i){
			if(i == n+1){
				i = 1;
				if(st == 1) break;
				flg = false;
			}
			if(pre(i) == st || s[pre(i)] == '1'){
				printf("%d %d\n", i, st);
			}
			if(s[i] == '0'){
				printf("%d %d\n", i, nxt(i));
			}
		}
	}
	return 0;
}
```

---

## 作者：zjqzjq (赞：3)

~~我的第一篇题解~~

根据树的性质，一棵 $n$ 个节点的树，一定有 $n-1$ 条边。每一条边连接了两个点，因此所有点的度之和是 $2*(n-1)$ ，是偶数。

因此如果 $\sum_{i=1}^ns_i \mod \ 2=1$ ，就无法构造出答案，输出 NO。

如果所有的 $s_i=0$ ，也是无解的。因为要连通，所有的节点的度都不能为 $0$ ，所以至少也是$2$，所有节点的度之和最少也是 $2*n,2*n>2*(n-1)$ 。

否则一定可以构造出。方法如下：

**第一步**：先找到一个 $s_i=1$ 的节点，然后按顺时针连边如果下一个节点 $s_j=0$ ，就连上。如果下一个节点 $s_j=1$ ，就不连。最后除了所有满足 $s_{i+1}=1$ 的节点不符合要求，其他节点都符合要求。

**第二步**：然后再固定一个不符合要求节点当根，与其他不符合要求的节点都相连。最后一定符合要求，而且中间一定没有两条边相交。

如图：

![bug](https://cdn.luogu.com.cn/upload/image_hosting/f21cl7kz.png?x-oss-process=image/resize,m_lfit,h_200,w_300)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200010],len=0;
char c[200010];
void Do(){
	cin>>n;
	len=0;
	bool flag=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		c[i]-='0';
		flag^=c[i];
		cnt+=c[i];
	}
	if(flag || cnt==0){//无解情况
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
	c[n+1]=c[1];
	for(int i=1;i<=n;i++){
		if(c[i+1]==0){
			cout<<i<<" "<<i%n+1<<"\n";//第一步
		}
		if(c[i+1]){
			a[++len]=i;//统计第一步不合法的点
		}
	}
	for(int i=2;i<=len;i++){//第二步
		cout<<a[1]<<" "<<a[i]<<"\n";
	}
}
int main(){
	cin>>t;
	while(t--){
		Do();
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

我宣布 D<C<B。

![](https://cdn.luogu.com.cn/upload/image_hosting/2cibksci.png)

## Solution

首先，一棵树上不可能有奇数个奇度点，因为这样总度数是奇数，而显然一棵树的总度数必须是偶数（一条边需要算两次）。把这个无解判掉。

还有非常阴间的 $s_i=0,\forall i$，这种情况边数超过了 $n-1$ 所以也是无解的。

接下来考虑怎么对其他情况构造。

然后我们考虑如何对这个构造下手。可以想到树上很特殊的度数点就是叶子了，叶子的度数肯定是 $1$。所以我们有一个 naive 的想法就是先用一个菊花把所有奇度点先干掉，然后考虑怎么把偶度点引进到树里面。现在菊花的中心并不重要，可以先假设在圆心处搞了一个虚点比较方便理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/riqsj3ft.png)

然后由一些刻板思考模式可以发现，每个奇度点可以管理自己某一侧的所有偶度点，像链一样串起来，然后只要把连接处改到链尾就可以把这一长串都串起来了，并且由于每一条边都贴着圆周，所以肯定在圆内是没有交的。特别地，对于一个点都管不了的奇度点，维持原状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/3p1tkxf6.png)

所以现在只剩下一个问题：“菊花”的中心在哪里。

容易发现，由于奇度点一定有偶数个，所以连到中间那个虚点上的边数一定是偶数条。我们考虑如果存在一条边连到的是偶度点，我们直接把“菊花”中心挪到那个点上行不行。

显然其他点还是能照常连过来，只有那个点所在的一长串会有一些变动。但又因为那一长串至少还存在一个奇度点兜底，所以还是能向这个中心贡献一条边。于是这个点还是偶数度的。

很容易可以发现这样所有边还是不在圆内相交的（只有中心发散了一些边出去，其他的边都贴着圆周，所以肯定不在圆内交），构造满足题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/jl7g2t3g.png)

没有一条边连到的是偶度点怎么办？那就说明所有点都是奇度数点。因为我们已经判断完了必然有偶数个奇数点，所以这种情况其实就是实打实的菊花。直接随便挑一个中心构造菊花即可。

这样构造覆盖了所有有解情况，于是这题就做完了。

## Code

略有一点丑的 vp 代码。

```cpp
int tc;
int n;
char c[N];
vector <pii> ans;
vector <pii> ldr;
int re(int x){
    if(x==-1) return n;
    else return x+1;
}
void solve(){
    cin>>n;
    ans.clear();
    ldr.clear();
    fr1(i,0,n-1) cin>>c[i];
    bool flg=0;
    fr1(i,0,n-1) flg^=(c[i]-'0');
    if(flg) return cout<<"NO\n",void();
    fr1(i,0,n-1){
        if(c[i]=='1'){
            int j=(i+1)%n,cnt=1;
            while(c[j]=='0'){
                ans.pb(mp(re(j-1),re(j)));
                cnt++;
                j=(j+1)%n;
            }
            ldr.pb(mp(re(j-1),cnt));
            if(j<=i) break;
            i=j-1;
        }
    }
    int cnt=0;
    for(auto i:ldr) if(i.se>1) cnt++;
    if(cnt&1){
        for(auto i:ldr){
            if(i.se==1){
                for(auto j:ldr){
                    if(i==j) continue;
                    ans.pb(mp(i.fi,j.fi));
                }
                break;
            }
        }
    }
    else{
        for(auto j:ldr){
            if(j==ldr[0]) continue;
            ans.pb(mp(ldr[0].fi,j.fi));
        }
    }
    if(ans.size()!=n-1) return cout<<"NO\n",void();
    cout<<"YES\n";
    for(auto i:ans) cout<<i.fi<<" "<<i.se<<'\n';
}
```

[AC Record.](https://codeforces.com/contest/1682/submission/267290332)

---

## 作者：DaiRuiChen007 (赞：0)

# CF1682D 题解



## 思路分析

先判定无解的情况：若所有点的度数都为偶数或者又奇数个点的度数也为奇数时，该问题无解。

那么对于剩下的情况，度数为奇数的点都恰好有偶数个。

我们可以先构造一条 $1\to 2\to\cdots\to n$ 的链，然后比较度数，可以证明与目标系数不同的点也是偶数个。

我们考虑把这些点按顺序把相邻的点配对，然后构造一种方法使得一对需要改变度数的 $(i,j)$ 的度数都改变奇偶性，且不影响其他点的度数。

考虑令 $\deg_i\gets \deg_i+1,\deg_j\gets \deg_j-1$，假如我们断掉 $(j,j+1)$，连接上 $(i,j+1)$ 就可以满足此构造要求。

对于 $j=n$ 的情况，假设与 $i$ 相连且小于 $i$ 的点为 $x$ 我们就断掉 $(i,x)$ 替换成 $(n,x)$ 即可，由于我们的构造过程保证了对于每一个没被考虑到的的 $i$ 这样的 $x$ 总是存在的。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
char deg[MAXN];
int p[MAXN],link[MAXN];
inline void solve() {
	int n,tot=0;
	scanf("%d%s",&n,deg+1);
	for(int i=1;i<=n;++i) tot+=deg[i]-'0',p[i]=i,link[i]=i-1;
	if(tot==0||tot%2==1) {
		puts("NO");
		return ;
	}
	vector <int> fail;
	for(int i=1;i<=n;++i) {
		if(i==1||i==n) { 
			if(deg[i]=='0') fail.push_back(i);
		} else {
			if(deg[i]=='1') fail.push_back(i);
		}
	}
	puts("YES");
	for(int i=0;i<(int)fail.size();i+=2) {
		if(fail[i+1]==n)  {
			printf("%d %d\n",link[n],n);
			link[n]=link[fail[i]];
			link[fail[i]]=0;
		} else link[fail[i+1]+1]=fail[i];
	}
	for(int i=1;i<=n;++i) if(link[i]>0) printf("%d %d\n",i,link[i]);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：Zeardoe (赞：0)

注意到一棵树上每个节点度数的大小之和为 $2n-2$，并且每个节点的度数至少是 $1$。因此如果 $s$ 中的 $1$ 的个数是 $0$ 或者奇数，直接判 $\tt NO$。

如果我们将相邻两个 $1$ 及其中间部分看作一个整体，在其内部构造一条链（改变了其两端 $1$ 的奇偶性），那么可以转换成若干个 $0...0$，形成环状结构（只要进来的边和出去的边在同一个节点上即可），如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ftad366x.png)

这样，我们连了 $n$ 条边，满足了所有点的奇偶性，但是我们不能有环，并且要减少一条边。需要做一些微调。
发现，将 $1-2$ 和 $1-3$ 两条边缩成 $2-3$，不会改变奇偶性。于是有：

![](https://cdn.luogu.com.cn/upload/image_hosting/kgtnzd8d.png)

正好可以。这启发我们找到通法：我们把块内和外界连边的点叫做“窗户”；对于第一块有 $1$ 的，一定包含两个以上节点。这一块我们把其第一、二个节点设为单向窗户，其他块把其第一个节点设为双向窗户。对于第一块，其第一个和第二个节点不连边，入块边连接第一个节点，出块边连接第二个节点。对于其他块内节点，相邻连边，入块边和出块边都连接第一个节点。形成一个环状结构，并且符合题目要求。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i, a, b) for(int i = a; i <= b; i++)
#define mod9 998244353
#define mod1 1000000007
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define endl '\n'
vector<pii> edge;
vector<char> c;
vector<int> window;
int first1; 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        int n; cin >> n;
        c.clear(); c.resize(n + 1);
        edge.clear(); window.clear();
        first1 = 0;
        f(i, 1, n) cin >> c[i];
        int cnt = 0, lst = 0;  //lst:上一个1在哪里；
        //cnt:1的个数
        f(i, 1, n) {
            if(!first1 && lst) {
                first1 = lst;
                window.push_back(i);
            }
            if(c[i] == '1') {
                cnt++;
                if(lst) {//末尾1
                    if(first1 != i - 1) edge.push_back({i - 1, i});
                    lst = 0;
                }
                else {//打头1
                    lst = i;
                    if(first1) window.push_back(i);
                }
            }
            else {
                if(lst) {
                    //在中间
                    if(first1 != i - 1) edge.push_back({i - 1, i});
                }
                else window.push_back(i);
            }
        }
        if(cnt == 0 || (cnt & 1)) {
            cout << "NO\n";
            continue;
        }
        int root = 0;
        f(i, 0, (int)window.size() - 1) {
            if(window[i] - 1 == first1) root = i;
            
        }
    //    cout << root << endl;
        for(int i = root; i != (root == 0 ? (int)window.size() - 1 : root - 1); i = (i == (int)window.size() - 1 ? 0 : i + 1)) {
            edge.push_back({window[i], window[(i == window.size() - 1 ? 0 : i + 1)]});
        }
        
        edge.push_back({window[(root == 0 ? (int)window.size() - 1 : root - 1)], first1});
        cout << "YES\n";
        f(i, 0, edge.size() - 1) {
            cout << edge[i].first << " "<< edge[i].second<< endl;
        }
    }
    return 0;
}
```

---

## 作者：lingfunny (赞：0)

# 793div2 D

首先考虑满足边的奇偶性条件。

如果 $\texttt{1}$ 的数量为奇数显然无解，如果为偶数，就连接两个 $\texttt{1}$ 之间的所有边。

比如 $\texttt{1001001001110}$，连接 $1\leftrightarrow 2\leftrightarrow3\leftrightarrow4$，$7\leftrightarrow8\leftrightarrow9\leftrightarrow10$ 和 $11\leftrightarrow12$。

然后缩点，看成 $6$ 个点，分别是 $(1\sim4),5,6,(7\sim10),(11\sim12),13$。

此时每个点都满足奇偶性条件，如果想加边需要满足一个点一次性加两条边。

主要问题是不连通，考虑把其中一个 $\texttt{100...001}$ 拆开，拆成 $\texttt{1}$ 和 $\texttt{0...001}$，此时再按顺/逆时针串在一起即可。

如下图：

![Snipaste_2022-05-23_13-12-10.png](https://s2.loli.net/2022/05/23/MiCxNPARoZl6fa8.png)

![Snipaste_2022-05-23_13-13-30.png](https://s2.loli.net/2022/05/23/tARzMnJ71axXwiB.png)

不难看出这个构造没有交叉。因为缩起来的点内部都是**沿着圆周**连接边的，不会对其他边产生**可行性影响**。并且你连的新边之间也没有交叉。

构造不了的情况就是没有点可以拆，即没有出现过 $\texttt{1}$，显然这种情况下无解，因为叶节点必须度数为 $1$，不可能没有奇数。

一些注意点：拆点后必须用**原边连接的两个点**去连其他点；对于一个缩点后的连通块，连接这个连通块的边必须连的是同一个点，比如上图 $1\sim4$ 连在一起，用 $5,13$ 两个点连接它的时候必须连同一个点，如 $(5,2),(13,2)$ 或 $(5,1),(13,1)$，但是 $(5,1),(13,2)$ 是不合法的。因为奇偶性限制。

---

## 作者：include_BM (赞：0)

若 $s$ 不满足以下 $2$ 个条件，那么一定不合法：

1. $s$ 中有偶数个 $1$，因为一棵树所有点度数之和为 $2n-2$（$2$ 倍边数），是一个偶数。
2. $s$ 中至少有 $1$ 个 $1$，因为一棵树至少有一个叶子节点，而叶子节点的度为 $1$。

若 $s$ 满足以上条件，可以选一个度为奇数的点顺时针方向上第一个点作为起点，延伸出若干条链，每条链按顺序经过一些度为偶数的点，最后停在一个度为奇数的点，为了使边不交叉，可以顺时针经过两个度为奇数的点之间的所有度为偶数的点，大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/f3ols7zg.png)

可以发现起点度偶数或奇数均能满足要求。

---

## 作者：Inzam_Z (赞：0)

# CF1682D
## 题目大意

有一个大小为N的环和一个01字符串s，节点编号从1到N顺时针排列。求大小为N的生成树，满足以下条件：

- 节点i的度数奇偶性与字符串s上的第i个字符相同， `deg[i] % 2 == int(s[i - 1])`
- 树上的边，在上述的环中不能交叉，端点交叉除外

如果有解输出 `YES` 以及所有边，反之输出 `NO` 。

## 解题思路

我们不妨尝试在一个环上对边进行操作。首先如果要求有奇数个度为 `1` 的节点，就一定是不合法的，因为无向图的度的和必定是偶数，一条边贡献两个度。其次没有 `1` 也是不合法的，因为度为 `2n` ，只能是一个环。

我们考虑一下有解的情况，如何输出边。为了方便表示，我们解题过程使用 `0 ～ n-1` 编号节点，最后输出 `-1` 即可。

我们先把所有的点按照环的方式相连，此时所有的结点度数都是偶数2。我们找到第一个要求节点度数是奇数的点 `cur` ，显然我们需要把一条边去掉，于是我们把 `(cur + 1) % n` 过来的边去掉，并把 `(cur + 1) % n` 作为树的根节点，然后从根节点的下一个节点开始遍历一遍环，如果节点要求度为奇数，就把下一个节点连向当前节点的边指向根节点。此时当前节点度 `-1` ，就是奇数。

由于输出是树，我们只需要记录每个节点的父节点就可以了，边的转移也只需要把下一个节点的父节点设置为根。

## 正确性证明

大概讲一下证明思路吧

### 环上连线没有交叉

环上只有两种边，和相邻节点的连线或者连向根节点的边。所以不存在交叉的可能

### 保证节点奇偶性

对于非根节点，奇偶性是显然的。一开始所有节点都是度为偶数，遇到要求度为奇数的就减少一个度。

对于根节点，一开始的度数为奇数，此时已经处理了 1 个奇数节点，还剩下奇数个节点要求度是奇数，之后每一次处理根节点都会增加一个度。

- 如果根节点要求自己是奇数度数，那么接下来要处理的点会少一个，也就是自己。剩下偶数个节点需要处理，最后根节点度是奇数。
- 如果根节点要求自己是偶数度数，那么接下来要处理奇数个节点，最后根节点度数是偶数。

## 参考代码

懒得加注释了，后面有空再加。

```cpp
//InzamZ
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define f(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define F(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)
#define FIO std::ios::sync_with_stdio(false);\
            std::cin.tie(0)
#define FFFOUT freopen("./out.txt" , "w", stdout)
#define FFFIN freopen("./in.txt" , "r", stdin)
const int maxn = 5e5 + 10;
const int maxb = 110;
int T = 1, n, m, rt, ans = 0, a[maxn], b[maxn];
vector<int>e[maxn], v;
string s;

int solve() {
    ans = 0;
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            a[i] = 1;
            ans++;
        }
        else
            a[i] = 0;
        b[i] = (i - 1 + n) % n;
    }
    if (ans % 2 == 1 || ans == 0)
        cout << "NO\n";
    else {
        for (int i = 0; i < n; ++i) {
            if (a[i] == 1) {
                b[(i + 1) % n] = (i + 1) % n;
                rt = (i + 1) % n;
                break;
            }
        }
        for (int i = 1; i <= n - 1; ++i) {
            int cur = (rt + i) % n;
            if (a[cur] == 1)
                b[(cur + 1) % n] = rt;
        }
        cout << "YES" << '\n';
        for (int i = 0; i < n; ++i) {
            if (rt != i)
                cout << i + 1 << ' ' << b[i] + 1 << '\n';
        }
    }
    return 0;
}

signed main() {
    FIO;
    cin >> T;
    while (T--) {
        // cout << "Case #" << T + 1 << ":" << endl;
        solve();
    }
    return 0;
}

```


---

