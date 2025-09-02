# Kuro and GCD and XOR and SUM

## 题目描述

Kuro is currently playing an educational game about numbers. The game focuses on the greatest common divisor (GCD), the XOR value, and the sum of two numbers. Kuro loves the game so much that he solves levels by levels day by day.

Sadly, he's going on a vacation for a day, and he isn't able to continue his solving streak on his own. As Katie is a reliable person, Kuro kindly asked her to come to his house on this day to play the game for him.

Initally, there is an empty array $ a $ . The game consists of $ q $ tasks of two types. The first type asks Katie to add a number $ u_i $ to $ a $ . The second type asks Katie to find a number $ v $ existing in $ a $ such that $ k_i \mid GCD(x_i, v) $ , $ x_i + v \leq s_i $ , and $ x_i \oplus v $ is maximized, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR), $ GCD(c, d) $ denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ c $ and $ d $ , and $ y \mid x $ means $ x $ is divisible by $ y $ , or report -1 if no such numbers are found.

Since you are a programmer, Katie needs you to automatically and accurately perform the tasks in the game to satisfy her dear friend Kuro. Let's help her!

## 说明/提示

In the first example, there are 5 tasks:

- The first task requires you to add $ 1 $ into $ a $ . $ a $ is now $ \left\{1\right\} $ .
- The second task requires you to add $ 2 $ into $ a $ . $ a $ is now $ \left\{1, 2\right\} $ .
- The third task asks you a question with $ x = 1 $ , $ k = 1 $ and $ s = 3 $ . Taking both $ 1 $ and $ 2 $ as $ v $ satisfies $ 1 \mid GCD(1, v) $ and $ 1 + v \leq 3 $ . Because $ 2 \oplus 1 = 3 > 1 \oplus 1 = 0 $ , $ 2 $ is the answer to this task.
- The fourth task asks you a question with $ x = 1 $ , $ k = 1 $ and $ s = 2 $ . Only $ v = 1 $ satisfies $ 1 \mid GCD(1, v) $ and $ 1 + v \leq 2 $ , so $ 1 $ is the answer to this task.
- The fifth task asks you a question with $ x = 1 $ , $ k = 1 $ and $ s = 1 $ . There are no elements in $ a $ that satisfy the conditions, so we report -1 as the answer to this task.

## 样例 #1

### 输入

```
5
1 1
1 2
2 1 1 3
2 1 1 2
2 1 1 1
```

### 输出

```
2
1
-1
```

## 样例 #2

### 输入

```
10
1 9
2 9 9 22
2 3 3 18
1 25
2 9 9 20
2 25 25 14
1 20
2 26 26 3
1 14
2 20 20 9
```

### 输出

```
9
9
9
-1
-1
-1
```

# 题解

## 作者：int_R (赞：8)

模拟赛 T2，赛时写挂了，01Trie 好题。

对于每个询问找出 $v$：

1. $v+x\leq s$
2. $k|\gcd(v,x)$
3. $x \oplus v$ 最大

前两个为限制条件，考虑变化一下。

$$v\leq s-x,k\mid v,k\mid x$$

由于 $k,x$ 均为给出的，所以若 $k\nmid x$ 则直接输出 `-1` 即可。

所以只需要找出 $v\leq s-x,k\mid v$ 使得 $x \oplus v$最大。

见到异或，考虑 01Trie。我们开 $10^5$ 一棵 01Trie，每次将一个数 $x$ 加入到集合中时，$\forall i\in[1,10^5],i\mid x$，将它插入第 $i$ 棵 01Trie 中。

查询的时候，我们在第 $k$ 棵树上贪心的找到最大的异或值即可，每次尽可能使得二进制高位与 $x$ 不同，不必多说。但发现还有第一条限制没有满足，所以我们只需要对于 01Trie 上每个节点，维护一下经过了这个节点的数中的最小数，如果这个值 $> s-x$ 贪心时就不能进入这个子树。

根据调和级数时间复杂度为 $O(q\sqrt W + W\log^2 W)$，$W=10^5$ 为值域。

------------

还有一个什么用都没有的优化，对 $\sqrt {10^5}$ 及以下的数采用上述方法，对于以上的数的倍数不超过 $\sqrt {10^5}$ 个，直接进行最朴素的暴力查找，实测会快。~~但是考场这暴力写寄了。~~

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*f;
}
const int MAXN=1e5+10,MAXT=4e7+10,MAXB=330,INF=1e9+7;
int q,w=320,root[MAXB],MIN[MAXT],t[MAXT][2],cnt;bool vis[MAXN];
int main()
{
    q=read();cnt=w;
    for(register int i=1;i<=w;++i) root[i]=i,MIN[i]=INF;
    while(q--)
    {
        int opt=read(),x,k,s,ans=0;
        if(opt==1)
        {
            x=read();
            if(vis[x]) continue;vis[x]=true;
            for(register int i=1;i<=min(w,x);++i)
            {
                if(!(x%i))
                {
                    int p=root[i];MIN[p]=min(MIN[p],x);
                    for(register int j=16;j>=0;--j)
                    {
                        if(!t[p][(x>>j)&1]) t[p][(x>>j)&1]=++cnt,MIN[cnt]=INF;
                        p=t[p][(x>>j)&1],MIN[p]=min(MIN[p],x);
                    }
                }
            }
        }
        else
        {
            x=read(),k=read(),s=read();
            if(x%k){cout<<"-1\n";continue;}
            if(k<=w)
            {
                int p=root[k];
                if(MIN[p]>s-x){cout<<"-1\n";continue;}
                for(register int j=16;j>=0;--j)
                {
                    if(x&(1<<j))
                    {
                        if(t[p][0]&&MIN[t[p][0]]<=s-x) p=t[p][0];
                        else p=t[p][1],ans|=(1<<j);
                    }
                    else
                    {
                        if(t[p][1]&&MIN[t[p][1]]<=s-x) p=t[p][1],ans|=(1<<j);
                        else p=t[p][0];
                    }
                }
                cout<<ans<<'\n';
            }
            else
            {
                ans=-1;
                for(register int i=k;i<=s-x;i+=k)
                    if(vis[i]&&((x^i)>=(x^ans)||ans==-1)) ans=i;
                cout<<ans<<'\n';
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：Tari (赞：6)

简单数学 + 01trie  

首先我们要对每个数 $i$ 开一个 01trie，里面存有 $i$ 的所有倍数。  
因为$k|gcd(v,x)$ 即 $k|v\ \&\&\ k|x$，所以我们对于 $2$ 操作只需要在 $k$ 这颗 01trie 上面贪心找 $v$ 即可。

那么我们在 $1$ 操作时，可以把 $u$ 插入到 $u$ 的所有约数的 01trie 里即可（约数要 $\mathcal{O}(nlogn)$ 预处理）。

时间和空间都是 $\mathcal{O}(nlog^2n)$ 的。

```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
namespace Luitaryi {
inline int g() { R x=0,f=1;
	register char s; while(!isdigit(s=getchar())) f=s=='-'?-1:f;
	do x=x*10+(s^48); while(isdigit(s=getchar())); return x*f;
} const int N=100010,M=20000010,Y=100000,B=16,Inf=1e9;
int q,L,tot,rt[N],t[M][2],mn[M],vl[M];
vector <int> fac[N];
bool vis[N];
inline void ins(int& tr,int x,int d) {
	if(!tr) tr=++tot,mn[tr]=Inf;
	mn[tr]=min(mn[tr],x);
	if(d<0) return vl[tr]=x,void();
	ins(t[tr][x>>d&1],x,d-1);
}
inline int find(int tr,int x,int d) {
	if(!tr) return -1;
	if(d<0) return vl[tr]; R t0=t[tr][0],t1=t[tr][1];
	if(!t0||mn[t0]>L) return find(t1,x,d-1);
	if(!t1||mn[t1]>L) return find(t0,x,d-1);
	return find(t[tr][(x>>d&1)^1],x,d-1);
}
inline void main() {
	for(R i=1;i<=Y;++i) for(R j=i;j<=Y;j+=i) fac[j].push_back(i);
	q=g(); for(R i=1,op,x,k,s;i<=q;++i) { 
		op=g(); if(op&1) {
			x=g(); if(vis[x]) continue; vis[x]=true;
			for(R i=0,lim=fac[x].size();i<lim;++i) ins(rt[fac[x][i]],x,B);
		} else {
			x=g(),k=g(),s=g(); L=s-x;
			if(x%k||s-x<0) {puts("-1"); continue;}
			printf("%d\n",find(rt[k],x,B));
		}
	}
}
} signed main() {Luitaryi::main(); return 0;}
```
2019.11.11

---

## 作者：NatsumeHikaru (赞：3)

广告：[博客食用效果更佳](https://hikaru.com.cn/hikaru/248/)
#### Description

[here](https://codeforces.com/problemset/problem/979/D)

#### Solution

暴力。暴力。暴力。

每次判断一下 $k$ 能否整除 $x$ ，如果不能一定无解，输出 $-1$ 。

然后设定一个值，不要太大，比这个值小的直接枚举，比这个值大的就按倍数来枚举。

#### Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=100010;

bool vis[N];
int q,t,cnt,last;
int x,k,s;

int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%d",&t);
		if(t == 1){
			scanf("%d",&x);
			vis[x]=true;
			cnt++,last=x;
		}
		else{
			scanf("%d%d%d",&x,&k,&s);
			if(cnt == 1){
				if(last%k == 0 && x% k== 0 && last+x<=s)
					printf("%d\n",last);
				else puts("-1");
			}
			else{
				int res=-1;
				if(k >= 100 && x%k == 0)
					for(int i=k;i<=s-x;i+=k)
						if(vis[i])
							res=max(res,x^i);
				if(k < 100 && x%k == 0)
					for(int i=s;i>=0;--i){
						int v=x^i;
						if(vis[v] && v%k == 0 && x+v <= s){
							res=i;
							break;
						}
					}
				if(res >= 0) res^=x;
				if(cnt > 1) printf("%d\n",res);
			}
		}
	}
	return 0;
}
```



---

## 作者：FadedAW (赞：2)

借鉴了[大佬](https://blog.csdn.net/riba2534/article/details/80344026)

先讲一下2操作的意思：

x k s：从当前集合中找出一个最大的v，使得:

①v + x ≤ s  即 v ≤ s - x
       
②k | gcd ( v , x)  即 x 是 k 的倍数 （若 x 不是 k 的倍数 => 直接输出 “-1”）且 v 是 k 的倍数
       
③x xor v最大 

所以我们可以直接从集合中找出 ≤ s - x 且为 k 的倍数的数，再来判断最大的异或和。

用 set 预处理一下加入到集合的数u，记录 u 的各个因子。

再加入一些优化（看代码）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100000+5;
int Q;
set<int>s[N]; 
int main() {
	scanf("%d", &Q);
	while (Q--) {
		int t; scanf("%d", &t);
		if (t == 1) {
			int u; scanf("%d", &u);//用 set 预处理一下加入到集合的数u，记录 u 的各个因子。 
			for (int i = 1; i <= (int)sqrt(u); i ++ ) 
				if (u % i == 0) s[i].insert(u), s[u/i].insert(u);
		}
		else {
			int x, k, ss, ans = -1, maxn = -1; scanf("%d%d%d", &x, &k, &ss);
			if (x % k) {printf("-1\n"); continue;} //若 x 不是 k 的倍数 => 直接输出 “-1” 
			set<int>::iterator it = s[k].upper_bound(ss - x);//找到 > x的元素中最小的一个 
			if(s[k].empty() || it == s[k].begin()) {printf("-1\n"); continue;} //如果找不到 => 前两个条件不符合 => 直接输出 “-1” 
			--it;
			for (; it != s[k].begin(); --it) { 
				int v = *it;
				if (maxn > x + v) break;//v xor x 最大的结果就是 x + v，又 v 在递减 
				if (maxn < (v ^ x)) maxn = v ^ x, ans = v;//找出最大的异或值 
			}
			if (maxn < (*it ^ x)) ans = *it;//判断s[k].begin() 
			printf("%d\n", ans);
		}
	}
	return 0;
}

```



---

## 作者：5k_sync_closer (赞：1)

维护 $n$ 棵 01Trie，第 $i$ 棵维护集合中 $i$ 的倍数，插入 $x$ 时，$\forall d\mid x$ 把 $x$ 插入第 $d$ 棵 01Trie，

查询 $x,k,s$ 时，在第 $k$ 棵 01Trie 中查 $\le s-x$ 的，异或 $x$ 最大的数，

维护子树最小值，贪心进入某棵子树时判一下这个子树里有没有 $\le s-x$ 的点，没有就不能进。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct T
{
    int v, c[2];
} R[30000050];
bool b[100050];
int n, o, p[100050];
void I(int x, int r)
{
    R[r].v = min(R[r].v, x);
    for (int i = 20, p = r; i >= 0; --i)
        if (R[p].c[x >> i & 1])
            p = R[p].c[x >> i & 1], R[p].v = min(R[p].v, x);
        else
            p = R[p].c[x >> i & 1] = ++o, R[p].v = x;
}
int Q(int x, int s, int r)
{
    if (x + R[r].v > s)
        return -1;
    int q = 0, p = r;
    for (int i = 20; i >= 0; --i)
        if (R[p].c[~x >> i & 1] && x + R[R[p].c[~x >> i & 1]].v <= s)
            p = R[p].c[~x >> i & 1];
        else
            p = R[p].c[x >> i & 1];
    return R[p].v;
}
int main()
{
    for (int i = 1; i <= 1e5; ++i)
        R[p[i] = ++o].v = 1e9;
    scanf("%d", &n);
    for (int i = 0, o, x, k, s; i < n; ++i)
    {
        scanf("%d%d", &o, &x);
        if (o & 1)
        {
            if (!b[x])
            {
                b[x] = 1;
                for (int j = 1; j * j <= x; ++j)
                    if (!(x % j))
                    {
                        I(x, p[j]);
                        if (j * j != x)
                            I(x, p[x / j]);
                    }
            }
        }
        else
            scanf("%d%d", &k, &s), printf("%d\n", x % k ? -1 : Q(x, s, p[k]));
    }
    return 0;
}
```


---

## 作者：Terry_RE (赞：0)

# CF979D Kuro and GCD and XOR and SUM 题解

## 思路
首先观察一下查找的限制条件，即  
>$v + x \le s$  
>$k \mid \gcd(v,x)$  

观察后我们可以发现，条件可以转化为
>$v \le s - x$  
>$k \mid v$  
>$k \mid x$

我们从题目可以获得 $k$、$x$ 和 $s$。那么我们就可以计算前先判断一边答案：当 $x \bmod k \ne 0$ 时输出 $-1$。然后我们只需在另外两个限制条件查找答案即可。  
对于限制条件 $k \mid v$，我们只需要建立 $\sqrt{10^5}$  棵 01trie。插入时把这个数插入以这个数的因数为根的所有树中，再在查找时查找以 $k$ 为根的树即可，因数查找直接枚举即可。  
查找我们使用 dfs 遍历，查找时先搜与 $x$ 当前二进制位异或值为 $1$ 的子树。这样做查找到第一个符合条件的数即为答案。  
由于存数和判是否为空节点过于经典，这里不再赘述。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7;

int q;

bool vis[M];
bool is;

int ans;

class Trie{
public:
	int cnt = 400;
	int nxt[N][2];
	//int num[N];
	int book[N];

	void update(const int &a, const int &root){
		int pos = root;

	#define next nxt[pos][c]
		for(int i(17); i >= 0; --i){
			int c = (a>>i) & 1;

			if(next == 0)
				next = ++ cnt;

			pos = next;

			//num[pos] ++;
		}
	#undef next

		book[pos] = a;

		return ;
	}

	void dfs(const int &i, const int &x, const int &s, const int &root){
		if(is)
			return ;

		if(i == -1){
			if(book[root] <= s && book[root] != 0)
				ans = book[root], is = true;

			return ;
		}

		int pos = root;

		int c = (x>>i) & 1;
		int k = (s>>i) & 1;

		if(nxt[pos][c ^ 1])
			dfs(i-1, x, s, nxt[pos][c ^ 1]);

		if(nxt[pos][c])
			dfs(i-1, x, s, nxt[pos][c]);

		//cout << 'Y' << endl;
		return ;
	}
	
};
Trie c;

void insert(const int &a){
	if(vis[a])
		return ;

	vis[a] = true;

	for(int i(1); i * i <= a; ++i)
		if(a % i == 0){
			c.update(a, i);

			if(a / i != i)
				c.update(a, int(a/i));
		}

	return ;
}

int main(){
	cin.tie(0) -> ios::sync_with_stdio(false);

	cin >> q;

	while(q--){
		int opt;
		cin >> opt;

		if(opt == 1){
			int a;
			cin >> a;

			insert(a);
		}

		if(opt == 2){
			int x, k, s;
			cin >> x >> k >> s;

			if(x % k != 0 || s <= x){
				cout << -1 << "\n";
				continue;
			}

			ans = -1;
			maxx = 0;
			is = false;

			c.dfs(17, x, s - x, k);

			cout << ans << "\n";
		}
	}

	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

好题！观察下列式子：

$$
k\mid \gcd(v,x)
$$

然后可以惊恐的发现若 $k\nmid x$ 则无解，否则式子就变为了 $k\mid v$！

然后直接枚举所有满足 $k\mid v$ 且 $v\le s-x$ 的 $x\oplus v$ 最大的 $v$，经典问题使用 $N$ 个 01-Trie 维护即可。对每一个插入的数把它暴力插入到所有可能满足条件的数即可，时间复杂度为调和级数加一个 $\log$ 即 $O(n\log^2n)$ 可以通过。

---

## 作者：Laoshan_PLUS (赞：0)

对于每个询问找出 $v$，满足 $v+x\le s\land k\mid\gcd(v,x)$，使 $v\oplus x$ 最大。

异或和问题，独树一帜地考虑 01-Trie。对于使 $v\oplus x$ 最大，就是模板题，我们考虑怎么满足前两个限制。对于限制二，我们将其变形为 $k\mid v\land k\mid x$，因为 $k,x$ 是直接给出的，所以如果 $k\nmid x$ 直接输出 `-1` 即可。那对于 $k\mid v$ 怎么保证呢，方法简单粗暴：**建 $\boldsymbol v$ 的因数棵 01-Trie，加入一个元素时 `insert` 给它的所有的因数所代表的 01-Trie，然后查询时只需要查询 $\boldsymbol k$ 所代表的 01-Trie 即可**。因为因数只有 $\sqrt n$ 个，所以这样做的空间复杂度大概是 $2n\sqrt n$ 也就是大约 $6\times10^7$ 个 int，换算下来 200MB 多，而这题的空限 500MB，而且 Trie 这玩意本身空间就占不满，所以不用担心 MLE 的问题了。至于限制一，贪心地，我们存储每棵 01-Trie 的最小值，如果查询第 $k$ 棵 01-Trie 发现它的最小值就已经不满足限制一，就直接返回无解；否则，我们一定能找出一个使 $v\oplus x$ 最大的 $v$。

01-Trie 的空间本来就占不满，代码中统一使用了一个 `tot` 来控制 01-Trie 的位置，可以一定程度上减少空间的浪费。

```c++
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e5 + 5;
int q;
int trie[40000005][2], tot, v[40000005];
bool mp[MAXN];

void insert(int x, int ind) {
	v[ind] = min(v[ind], x);
	int p = ind;
	for (int i = 16; i >= 0; i--) {
		int c = (x >> i) & 1;
		if (!trie[p][c]) trie[p][c] = ++tot;
		p = trie[p][c];
		v[p] = min(v[p], x);
	}
}

int query(int x, int s, int ind) {
	if (x + v[ind] > s) return -1;
	int p = ind;
	for (int i = 16; i >= 0; i--) {
		int c = (x >> i) & 1, o = c ^ 1;
		if (trie[p][o] && x + v[trie[p][o]] <= s) p = trie[p][o];
		else p = trie[p][c];
	}
	return v[p];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	memset(v, 0x3f, sizeof(v));
	tot = 100000;
	cin >> q;
	int op, x, k, s;
	while (q--) {
		cin >> op >> x;
		if (op == 1) {
			if (mp[x]) continue;
			mp[x] = 1;
			for (int j = 1; j * j <= x; j++) {
				if (x % j != 0) continue;
				insert(x, j);
				if (j * j != x) insert(x, x / j);
			}
		} else {
			cin >> k >> s;
			if (x % k != 0) { cout << "-1\n"; continue; }
			cout << query(x, s, k) << '\n';
		}
	}
	
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
维护一个集合，支持：

- 加入一个数 $x$。
- 给定 $x$，$k$，$s$，求集合内满足 $x+v\leq s$ 且 $k|\gcd(x,v)$ 的使得 $x\oplus v$ 最大的 $v$。
### 分析
异或考虑 01-trie，如果只有 $x+v\leq s$ 和 $x\oplus v$ 最大，是 01-trie 的基础运用。

但是有这个 $k|\gcd(x,v)$ 就不好维护，考虑怎么处理。这个条件等价于 $k|x$ 且 $k|v$，前者直接判掉，后者只需要我们能维护出当前所有 $k|v$ 的 $v$ 的元素构成的 trie 即可。

所以我们可以离线，对于询问中每一个 $k$ 我们维护出 $k|v$ 的所有插入操作，这样成为 $O(n)$ 条时间轴，而每个插入操作只会在 $O(\sqrt n)$ 条时间轴产生贡献（因为是枚举因数），且完全不满，所以复杂度可以保证。对于每条时间轴正常 01-trie 上按位贪心即可，记得考虑对 $v$ 大小的限制。

代码实现起来比较方便的。
### 代码
由于 RMJ 炸了所以只在 CF 上过了，代码[见此](https://codeforces.com/problemset/submission/979/266680522)。

---

## 作者：lml0928 (赞：0)

### Part 0. 题目大意
[洛谷传送门](https://www.luogu.com.cn/problem/CF979D) [CF传送门](https://codeforces.com/problemset/problem/979/D)

一个初始为空的集合，将要进行 $q$ 次询问或操作：

 - `1 u`：往集合里插入一个 $u$。

 - `2 x k s`：找到一个 $v$，使得：
 
 	1. $v + x \le s$。
    
   1. $k \mid \gcd(v,x)$。
   
   1. $x \oplus v$ 最大。（$\oplus$ 表示按位异或）
   
输出每次询问的 $v$。
### Part 1. 思路
注：本题解中 $w$ 表示值域。

我们考虑使用 01Trie 解决此题。

第一个条件很好实现：插入时记录一下子树内部的最小值，这样就能判断是否可行了。第三个条件也很好实现：每一位尽量选和 $x$ 不同的（贪心思想），如果选不了了就输出 $-1$。

只有第二个条件很麻烦：01Trie 并不能处理这种条件。

我们将第二个条件转换一下，得到
$$k \mid x$$
$$k \mid v$$
第一个条件只需要在输入的时候判断一下就行了。但是为了处理第二个条件，我们只能把所有 $k$ 的倍数的元素扔到同一个 01Trie 里面。

于是，我们产生了一个疯狂的想法：开 $w$ 个 01Trie，使得每个 01Trie 里面只有这个 01Trie 的编号的倍数。虽然这个方法理论可行，但是空间会炸掉。

那我们能把这些树都开到一个数组里吗？

我们可以用前 $w$ 个数作为这些树的根节点，然后
正常连边就可以了。我们再用调和级数的时空复杂度处理一个数的所有因数。

总时间复杂度为 $O(w \cdot \log^2 w + q \cdot \log w)$，可以通过。

总空间复杂度为 $O(w \cdot \log^2w)$，在空间限制以内，其实挺紧张的。

### Part 2. 代码
~~供众人批判~~
```c++
#include<bits/stdc++.h>
using namespace std;
const int M = 4 * (int)1e7 + 10;
const int N = (int)1e5 + 10;
struct trie
{
	int nxt[M + 10][2];
	int mi[M + 10];
	int tot;
	trie()
	{
		tot = N - 10;
		memset(mi, 0x3f, sizeof mi);
	}
	void Insert(int x, int now)
	{
		for(int i = 18; i >= 0; i--)
		{
			int t = (x >> i) & 1;
			if(!nxt[now][t]) nxt[now][t] = (++tot);
			now = nxt[now][t];
			mi[now] = min(mi[now], x);
		}
	}
};
trie tr;
vector<int> ve[N];
void Init()
{
	for(int i = 1; i <= N - 10; i++)
	{
		for(int j = i; j <= N - 10; j += i)
		{
			ve[j].push_back(i);
		}
	}
}
int k, x, s;
int Dfs(int now, int stp)
{
	int son = (x >> stp) & 1 ^ 1;
	if(stp == -1) return tr.mi[now];
	if(tr.nxt[now][son] && tr.mi[tr.nxt[now][son]] + x <= s) return Dfs(tr.nxt[now][son], stp - 1);
	son ^= 1;
	if(tr.nxt[now][son] && tr.mi[tr.nxt[now][son]] + x <= s) return Dfs(tr.nxt[now][son], stp - 1);
	return -1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	Init();
	int q;
	cin >> q;
	while(q--)
	{
		int op;
		cin >> op;
		if(op == 1)
		{
			int x;
			cin >> x;
			for(auto i : ve[x]) tr.Insert(x, i);
		}
		else
		{
			cin >> x >> k >> s;
			if(x % k != 0) cout << "-1\n";
			else cout << Dfs(k, 18) << '\n';
		}
	}
	return 0;
}
```

---

## 作者：jijidawang (赞：0)

首先因为 $k\mid\gcd(v,x)\iff k\mid v\land k\mid x$，所以判完 $k\mid x$ 后就是限制 $k\mid v$。

考虑阈值分治，对于 $k\le B$，给每个 $k$ 开一棵 0-1 Trie 存储所有 $k$ 的倍数，那么问题就是 0-1 Trie 上查询带上界的最大异或和。每个结点维护子树内表示的数的最小值，查询时贪心查找，只查找最小值 $\le s-x$ 的位置即可保证不超上界。

对于 $k\ge B$，每次加入时用一个 set 记录，查询时暴力查询所有 $k$ 的倍数即可。

取 $B=90$，可以通过。

```cpp
const int N = 1e5 + 233, S = 15, B = 90;
int q;
stack<int> s;
struct Trie
{
	int nxt[N*5][2], mn[N*5], cnt;
	void insert(int x)
	{
		int p = 0;
		for (int i=S; i>=0; i--)
		{
			bool c = (x >> i) & 1;
			if (!nxt[p][c]) nxt[p][c] = ++cnt;
			s.push(p); p = nxt[p][c];
		}
		chkmin(mn[p], x);
		while (!s.empty()) chkmin(mn[s.top()], mn[p]), s.pop();
	}
	int query(int x, int bound)
	{
		if (mn[0] > bound) return -1;
		int p = 0, ans = 0, now = 0;
		for (int i=S; i>=0; i--)
		{
			bool c = (x >> i) & 1;
			if (nxt[p][!c] && (mn[nxt[p][!c]] <= bound)){p = nxt[p][!c]; ans += 1 << i;}
			else p = nxt[p][c];
		}
		return ans;
	}
	Trie(){memset(mn, 0x3f, sizeof mn); cnt = 0;}
}T[B+1];
unordered_set<int> _;
int main()
{
	scanf("%d", &q);
	int opt, x, k, s;
	while (q--)
	{
		scanf("%d%d", &opt, &x);
		if (opt == 1)
		{
			_.insert(x);
			for (int i=1; i<=B; i++)
				if (!(x % i)) T[i].insert(x);
		}
		else
		{
			scanf("%d%d", &k, &s);
			if (x % k){puts("-1"); continue;}
			if (k <= B){int ans = T[k].query(x, s - x); printf("%d\n", ~ans ? x ^ ans : -1);}
			else
			{
				int ans = 0; bool ok = false;
				for (int v=0; v<=s-x; v+=k)
					if (_.find(v) != _.end()) chkmax(ans, x ^ v), ok = true;
				printf("%d\n", ok ? ans ^ x : -1);
			}
		}
	}
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：0)

### 思路：

看到异或最大值，很会想到 01trie。

现在的问题是多了几个约束条件。我们观察第一个条件，就是要求 $v$ 的大小，这个很好维护，只需要维护最小值就行。

问题是第二个条件，第一步我们发现这个条件等价于 ```x%k==0&&v%k==0```。

简单的证明一下，首先如果一个数整除两个数的最大公约数，如果某一个数不是他的倍数，显然不可能。

当他们是他的倍数，那么他们的最大公约数也能整除这个数，最大公约数永远会包括这个 $k$。

现在的问题是如何建 trie，这里需要一些思维，发现数不会大于 $5\times 10 ^5$，因此我们对于每个数都建一个 trie。

 

而插入的时候，把这个数插进他的所有约数当中，这个约数需要预处理。这样我们选择的 $k$，答案就在 $k$ 的 trie 上，之后就是贪心异或。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pll;
const int N=1e5+10;
const int inf=1e9;
int tr[N*18*18][2],rt[N];
int mi[N*18*18];
int vis[N];
int st[N];
int cnt;
vector<int> d[N];
void init(){
    int i,j;
    for(i=1;i<=1e5;i++){
        for(j=i;j<=1e5;j+=i){
            d[j].push_back(i);
        }
    }
}
void insert(int rt,int x){
    int p=rt;
    mi[p]=min(mi[p],x);
    for(int i=18;i>=0;i--){
        int sign=x>>i&1;
        if(!tr[p][sign]){
            tr[p][sign]=++cnt;
        }
        p=tr[p][sign];
        mi[p]=min(mi[p],x);
    }
}
int query(int k,int x,int s){
    int p=rt[k];
    if(x%k!=0||mi[p]+x>s)
        return -1;
    ll ans=0;
    for(int i=18;i>=0;i--){
        int sign=x>>i&1;
        if(tr[p][!sign]&&mi[tr[p][!sign]]+x<=s){
            ans+=((sign^1)<<i);
            p=tr[p][!sign];
        }
        else{
            ans+=(sign<<i);
            p=tr[p][sign];
        }
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    init();
    int q;
    cin>>q;
    int mx=N*18*18;
    for(int i=0;i<mx;i++){
        mi[i]=inf;
    }
    while(q--){
        int opt;
        cin>>opt;
        if(opt==1){
            int u;
            cin>>u;
            if(st[u])
                continue;
            st[u]=1;
            for(auto x:d[u]){
                if(!vis[x]){
                    rt[x]=++cnt;
                    vis[x]=1;
                }
                insert(rt[x],u);
            }
        }
        else{
            int x,k,s;
            cin>>x>>k>>s;
            cout<<query(k,x,s)<<endl;
        }
    }
    return 0;
}
```


---

## 作者：Tastoya (赞：0)

### 题目大意
初始有一个空的集合，和 $Q$ 个操作。对于每个操作，有两种类型，分别用如下的两种形式表示：

`1 u`：加入 $u$ 到集合   
`2 x k s`：求一个最大的 $v$，使得:

1. $v+x \leq s$
2. $k \mid \gcd(v,x)$
3. $x \oplus v$ 最大（其中 $\oplus$ 表示按位异或，对应 C++ 中的 `^` 运算符）

如果找不到满足条件的 $v$，输出 $-1$。
### 思路

考虑第二个限制，我们可以转化为 $k \mid x \land k \mid v$，那么 $x$ 和 $v$ 都是 $k$ 的倍数，我们可以预处理加入集合的数 $u$，把它加入所有它因数的集合里。

这样在后面查找 $v$ 就直接在 $k$ 的集合中查找就能够保证满足第二个条件。

对于查询操作，直接找到小于等于 $s-x$ 的数，然后在集合中从大到小遍历。

知道，两个数异或值最大就是两个数的值相加，如果当前记录的最大异或值 `Max` 已经大于遍历到的 `x + v`，后面的部分肯定不会再对答案产生贡献了，可以直接退出循环。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100500;

int n;
int opt,u,x,k,s;

set<int> S[N];
// S[i] 中的任意数 x 满足 i | x 
// 即存的是 i 的倍数 
// 用于第二个条件 

long long ans,Max;

int main() {
    cin >> n;

    for(int i = 1;i <= n; i++) {
        cin >> opt;
        if(opt == 1) {
            cin >> u;
            for(int i = 1;i <= floor(sqrt(u)); i++) {
                if(u % i == 0) {
                    S[i].insert(u);
                    S[u / i].insert(u);
                }// 记录的是其倍数 
            }
        }
        else {
            cin >> x >> k >> s;
            
            ans = -1;
            Max = -1;

            if(x % k != 0) {
                cout << "-1\n";
                continue;
            }

            set<int>::iterator it = S[k].upper_bound(s - x);
            // 找到大于 v 的最小的数 
            if(it == S[k].begin() || S[k].empty()) {
                cout << "-1\n";
                continue;
            }

            it --;
            // 现在的 it 指向的是满足第一个条件和第二个条件的最大的数

            while(it != S[k].begin()) {
                int v = *it;

                if(Max > x + v) 
                    break;
                // 异或最大值就是 x + v 
                // Max 已经超过 x + v 肯定不能更新答案 
                
                if(Max < (v ^ x)) {
                    Max = v ^ x;
                    ans = v;
                }

                it --;
            }

            if((*it ^ x) > Max)
                ans = *it;
            
            cout << ans << "\n";
        }
    }
    return 0;
}
```

---

