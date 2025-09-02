# Game of Pairs

## 题目描述

This is an interactive problem.

Consider a fixed positive integer $ n $ . Two players, First and Second play a game as follows:

1. First considers the $ 2n $ numbers $ 1, 2, \dots, 2n $ , and partitions them as he wants into $ n $ disjoint pairs.
2. Then, Second chooses exactly one element from each of the pairs that First created (he chooses elements he wants).

To determine the winner of the game, we compute the sum of the numbers chosen by Second. If the sum of all these numbers is a multiple of $ 2n $ , then Second wins. Otherwise, First wins.

You are given the integer $ n $ . Your task is to decide which player you wish to play as and win the game.

## 说明/提示

In the first sample, $ n = 2 $ , and you decide to play as Second. The judge chooses the pairs $ (1, 2) $ and $ (3, 4) $ , and you reply with the numbers $ 1 $ and $ 3 $ . This is a valid choice since it contains exactly one number from each pair, and the sum $ 1 + 3 = 4 $ is divisible by $ 4 $ .

In the second sample, $ n = 2 $ again, and you play as First. You choose the pairs $ (2, 4) $ and $ (1, 3) $ . The judge fails to choose a number from each pair such that their sum is divisible by $ 4 $ , so the answer is correct.

Note that the sample tests are just for illustration of the interaction protocol, and don't necessarily correspond to the behavior of the real interactor.

## 样例 #1

### 输入

```
2

1 1 2 2

0```

### 输出

```
Second

1 3```

## 样例 #2

### 输入

```
2


0```

### 输出

```
First
2 1 2 1```

# 题解

## 作者：AsunderSquall (赞：9)

**题意**  

先手把 $1,2,3,\cdots 2n$ 分成 $n$ 个二元组，后手在每个 $2$ 元组里选择一个数，使得它们的和是 $2n$ 的倍数。如果可以做到后手赢，否则先手赢。  

你可以选择是先手还是后手，请你赢得胜利。  

**题解**  

第一次在看懂题意 2 分钟内秒了一道 \*2800 的题，写篇题解纪念一下。  
其实感觉难度没有 \*2800。  

顺便吐槽一下，这个输入怎么分组的方式为什么放在那么隐蔽的位置啊。  

考虑一个简单的想法，他要求是 $2n$ 的倍数，假如我是先手，我可以想办法让后手对 $2n$ 取模的变化尽可能少。  

于是想到将 $i,i+n$ 分为一组，这样后手每次更改组内选择哪个，都只会改变 $n$ 的倍数。  
这样的话，后手得到的和只能是 $\frac {n(n+1)} 2 +kn = n(\frac {n+1} 2 +k)$  

显然当 $n+1$ 是奇数，即 $n$ 为偶数的时候先手这么构造就能胜利。  

然后考虑 $n$ 是奇数的情况，猜一波后手必胜。  
我们考虑，假如能够选择这样 $n$ 个数，使得他们对 $n$ 取模后是 $0,1,2,\cdots n-1$。那么和一定是 $ n \cdot(k+\frac {n-1} 2)$。  
如果 $k+ \frac {n-1} 2$ 为奇数，我们就选择正好相反的那一组数，和变为 $n \cdot (2n+1-k- \frac {n-1} 2)$。    
考虑 $(k+\frac {n-1} 2)$ 和 $ (2n+1-k- \frac {n-1} 2)$ 奇偶性相反，这样一定可以。  

然后看上去就是能够选择出这样一组数的，我们来证明一下。  

首先，对于一组数 $(i,j)$ 进行连边。  
然后，对 $(i,i+n)$ 进行连边。  

这样每个数只会连出去 $2$ 条边（算上重边）。因此整张图一定由若干个环组成。且每个环上，$i$ 和 $i+k$ 是相邻的。  
对于每个环，我们隔一个取一个就一定能取出满足条件的 $n$ 个数。  

这样就做完了。  

**代码**  

吐槽一下，我把 `cin` 打成快读调了一年。（汗）
```cpp
int n,S;
int o[N],G[N];
bool v[N],t[N];
void dfs(int x){if (v[x]) return;S+=x,t[x]=v[x]=1;int y=x+n;if (y>2*n) y-=2*n;v[y]=1,dfs(G[y]);}
signed main()
{
	cin>>n;
    if (n%2==0) {cout<<"First"<<endl;for (int j=1;j<=2;j++) for (int i=1;i<=n;i++) cout<<i<<" ";cout<<endl;} else 
    {
        cout<<"Second"<<endl;
        for (int i=1,p;i<=n*2;i++) {cin>>p;if (o[p]) G[i]=o[p],G[o[p]]=i;else o[p]=i;}
        for (int i=1;i<=n*2;i++) if(!v[i]) dfs(i);
        for (int i=1;i<=n*2;i++) if (t[i]!=(S&1)) cout<<i<<" ";cout<<endl;
    }
}
```

---

## 作者：AuCloud (赞：5)

大概是数学题？

# 题意

给出整数N，在以下两种答案中选择一个：

- 给出一种方案，将$[1,2N]$ 区间内的所有整数两两分成一组，使其不存在某种选数方式同时满足：1.每组里选且只选1个数字 2.选中数字之和为$2N$ 的倍数

- 对于计算机给出的分组方案，给出一种选数方式，使其同时满足：1.每组里选且只选1个数字 2.选中数字之和为$2N$ 的倍数

# 题解

看起来这像是个博弈论

显然，两种情况会对应着两种不同的解法，我们来分类讨论

## N为偶数

当N为偶数时，一个比较显然的结论如下：

$$
\sum_{i=1}^{n}(i\space or\space (i+n))=\frac{n^2+n}{2}+kn≡\frac{n}{2}\space \space (mod\space n)
$$

而在$mod\space n$意义下不为零，在$mod\space 2n$意义下显然也不为零

这说明只要按照$(i,i+n)$ 这样分组，一定不会存在合法的解，如此构造即可。

## N为奇数

当N为奇数时，发现上面那个柿子的结果变成0了：

$$
\sum_{i=1}^{n}(i\space or\space (i+n))=\frac{n^2+n}{2}+kn≡0\space \space (mod\space n)
$$

这启发我们选择方案2

然后看着方案一的约束条件和题目的约束条件，列下来：

- 同组的选且只选一个（题目要求）

- $i$与$i+n$选且只选一个

思考一番，发现当然~~大概~~可以按2-SAT那么写，但是因为这题整个连成了几个环，所以可以有如下解法

（upd：重新写一下这里有争议的地方，见谅orz![yun](https://cdn.luogu.com.cn/upload/pic/62240.png)）

将同组之间连双向边，$i$与$i+n$之间连双向边，表示选了边的一个端点就不能选另一个端点

对于连好的图的每个连通块（其实是一个大环）跑dfs，染色染成黑/白，保证相邻点不同色

然后将所有染成黑色节点的值加在一起，根据上面的公式，我们得知和会变成形如$kn$的一个数

-------

当然我们要保证的是对$2n$ 整除

当 $k$ 为偶数时，黑色节点就满足答案了

但是当$k$ 为奇数时呢？

考虑把所有数都加在一起：

$$
\sum_{i=1}^{2n}i=\frac{2n(2n+1)}{2}=n(2n+1)=2n^2+n
$$

而黑色节点和为$kn$

则白色节点的和就是$2n^2+(1-k)n$ 。因为$k$是奇数，所以$1-k$是个偶数，显然这个数对$2n$ 整除

所以当黑色点不行的时候输出白色点即满足题意

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct hehe{
	int num, id;
}a[1000001];
int head[1000001], nxt[2000001], to[2000001], tot;
bool fl[1000001], used[1000001];
bool cmp(hehe x, hehe y)
{
	return x.id < y.id;
}
void add(int x, int y)
{
	nxt[++tot] = head[x];
	head[x] = tot;
	to[tot] = y;
}
void dfs(int x, int from)
{
	if(used[x]) return;
	if(!fl[from]) fl[x] = 1;
	else fl[x] = 0;
	used[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(y == from) continue;
		dfs(y, x);
	}
}
int main()
{
	int n;
	cin >> n;
	if(n & 1)
	{
		cout << "Second" << endl;
		for(int i = 1; i <= 2 * n; i++)
		{
			cin >> a[i].id;
			a[i].num = i;
		}
		for(int i = 1; i <= n; i++)
		{
			if(a[i].id != a[i + n].id) add(i, i + n), add(i + n, i);
		}
		sort(a + 1, a + 2 * n + 1, cmp);
		for(int i = 1; i <= 2 * n; i += 2)
		{
			add(a[i].num, a[i + 1].num);
			add(a[i + 1].num, a[i].num);
		}
		for(int i = 1; i <= n * 2; i++)
		{
			if(!used[i])
			{
				dfs(i, 0);
			}
		}
		int sum = 0;
		for(int i = 1; i <= 2 * n; i++)
			if(fl[i]) sum = (sum + i) % (2 * n);
		bool fin;
		if(!sum) fin = 1;
		else fin = 0;
		for(int i = 1; i <= 2 * n; i++)
			if(fl[i] == fin) cout << i << ' ';
		cout << endl;
	}
	else
	{
		cout << "First" << endl;
		for(int i = 1; i <= n; i++) cout << i << ' ';
		for(int i = 1; i <= n; i++) cout << i << ' ';
		cout << endl;
	}
	return 0;
}

```

---

## 作者：FiraCode (赞：2)

## 题解思路：
当 $n$ 是偶数先手必胜。

当 $n$ 是奇数后手必胜。

我们来证明一下：

1. $n$ 是偶数是先手必胜
>既然 $n$ 是偶数，那么先手有一个构造方案：
>> 把 $\mod n$ 相等的数放在一起，例如：$(1 , 1) , (1 , n + 1)$。

>> 所以后手拿的数只有 $1 + ... + n$。
>> 他就是 $(1 + n) \times n \div 2$，对于这个值，那么为什么他一定不是 $2n$ 的倍数呢？

>> $n = 2m$

>> 因为 $n$ 是偶数，而 $n + 1$ 就是个奇数，那这个数是不是 $n$ 的倍数呢？

>> 我们考虑一下：

>> 因为 $n = 2m$ 所以原式就变成了：$(2m + 1) \times m$。

>> 那么我们想让 $(2m + 1) \times m$ 是 $n$ 的倍数，那么我们要有个 $2$，但由于 $2m + 1$ 一定是奇数，所以他一定不是 $n$ 的倍数。\
>> 因为他不是 $n$ 的倍数，那他就不可能是 $2n$ 的倍数了。

>> 证毕。

> 那么为什么 $n$ 是偶数时后手必败呢？我们只要证明当 $n$ 是奇数时后手必胜就可以了。

2. 当 n 为奇数时后手必胜
> 首先我们证明一个性质：
>> $(2n + 1) \times n \mod 2n = n$

>> 因为他乘了奇数倍，所以他 $\mod 2n$ 一定是 $n$，因为它比奇数倍还多了一个 $n$。

>> 若我们选 $n$ 个数，定义 $sum$ 为选的 $n$ 个数的和。那么 $sum \mod n = 0$。

>> 那么我们有两种情况 $sum \mod 2n = n$，$sum \mod 2n = 0$。

>> 若 $sum \mod 2n = 0$，那么我们就是答案；若 $sum \mod 2n = n$，那么另外 $n$ 个数就是答案。

> 那么只要 $\mod n = 0\ 1\ 2\ ......\ n - 1$ 的数各有两个，那么我不管怎么塞，我们去出来这 $n - 1$ 个数。

**注意：奇数的情况时要`fflush(stdout)`，不然会Idleness limit exceeded on test 3，洛谷显示UKE**

[AC记录](https://www.luogu.com.cn/record/74627624)

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 1000010;
typedef long long ll; 
int n;
int a[N];
bool vis[N] , vis2[N] , vis3[N];
vector <int> e[N];
vector <int> g[N];
int main() {
	scanf ("%d" , &n);
	if (n & 1) {//奇数的情况 
		puts("Second");
		fflush(stdout);
		for (int i = 1; i <= n * 2; ++ i) {
			scanf ("%d" , &a[i]);//读入 
			e[i % n].push_back (a[i]);
			g[a[i]].push_back (i);
		}
		for (int i = 1; i <= n * 2; ++ i) {
			int root = i % n;
			if (vis[root]) continue; 
			int u = i;
			while (1) {
				vis[u % n] = vis2[u] = 1;//把他标记上 
				int v = -1;
				for (auto x : g[a[u]])
					if (!vis[x % n])
						v = x;
				if (v == -1) break;
				if (v > n) v -= n;//>n 就 -n 
				else v += n;//否则加上n 
				u = v;
			}
		}
		ll ans = 0;
		for (int i = 1; i <= n << 1; ++ i) 
			if (vis2[i]) //统计他们的和 
				ans += i;
		if (ans & 1) {//sum % 2n == n
			bool ok = false;//控制空格，避免后面多输出一个空格，当然加不加都无所谓 
			for (int i = 1; i <= n << 1; ++ i) 
				if (!vis2[i]) {//那么另外的那些就是答案 
					if (ok) printf (" ");
					printf ("%d" , i);
					ok = true;
				}
			puts("");
		}else {//否则 sum % 2n == 0 
			bool ok = false;//ok含义同上 
			for (int i = 1; i <= n << 1; ++ i)
				if (vis2[i]) {//那么就是原来的数 
					if (ok) printf (" ");
					printf ("%d" , i);
					ok = true;
				}
			puts("");
		} 
	}else {
		puts ("First");//偶数的情况，先手必胜 
		for (int i = 1; i <= n << 1; ++ i) {//直接输出 
			printf ("%d" , i % n + 1);//把两个同余的放在一块 
			if (i == n << 1) puts("");
			else printf (" ");
		} 
	}
	return 0;
}
```
码字不易，求赞！

---

## 作者：_Fontainebleau_ (赞：1)

### 题意
- 先手将 $1\sim{2n}$ 两两配对，分成 $n$ 组，后手在每组中取一个数，使得它们的和是 $2n$ 的倍数。若可以做到则后手胜，否则先手胜。
- 对于给定的 $n$，请你判断先手胜或后手胜，并给出做法。

### 做法

#### $n$ 是偶数

容易发现，只需要按 $(i,i+n)$ 分组，无论怎样，最后的结果在 $\bmod{n}$ 意义下都不是 $0$，而是 $\displaystyle\sum_{i=1}^n{(i\text{ or }i+n)}\equiv\sum_{i=1}^n{i}=\frac{n^2+n}2\equiv\frac{n}2\pmod{n}$，更无论 $2n$。于是先手必胜。

#### $n$ 是奇数

此时，上式为 $0$：$\displaystyle\sum_{i=1}^n(i\text{ or }i+n)\equiv\sum_{i=1}^n{i}=n\frac{n+1}2\equiv0\pmod{n}$。所以不妨猜测此时后手必胜。

注意，当 $n$ 是奇数时，$\displaystyle\sum_{i=1}^{2n}=\frac{2n(2n+1)}2=n(2n+1)$ 注意到 $2n+1$ 是一个奇数。如果取法合法，那么剩下的部分的和一定是 $kn,2\nmid k$。反过来，如果当前取了 $kn$ 这个情况，只需要选剩下的就行了。也就是说我们不用管 $2n$，只要 $\bmod{n}=0$ 就可以了。所以现在我们只要找一个模 $n$ 的完全剩余系。要找完全剩余系 $i,i+n$ 就不能同时选，与此同时，同一 $\textbf{pair}$ 的也不能同时选。所以我们将不能选的关系连成边。注意到现在每个点的度都是 $2$。也就是说，最后一定的图一定是很多个互不相交环。又因为，每个点一定跟同一 $\textbf{pair}$ 的点在一个环上，所以这个环是偶环。对于每一个环，我们隔一个取一个，就可以了！最后的结果一定取遍完系。最后看他们的和是否是 $2$ 的倍数，如果不是，就选剩下的。

### 代码
```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,cnt;
bool used[1000006];
bool col[1000006];
int h[1000006],t[4000006],nxt[4000006];
struct point{
	int id,vl;
}a[1000006];
inline bool operator <(const point &a,const point &b)
{
	return a.id<b.id;
}
inline void addedge(int a,int b){t[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;}
void dfs(int x,bool c)
{
	used[x]=true;col[x]=c;
	for(int p=h[x];p;p=nxt[p])
	{
		int v=t[p];
		if(!used[v])	dfs(v,c^1);
	}
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	cin>>n;
	if(n&1)
	{
		cout<<"Second"<<endl;
		for(int i=1;i<=2*n;i++)	cin>>a[i].id,a[i].vl=i;
		for(int i=1;i<=n;i++)
			if(a[i].id!=a[i+n].id)	addedge(i,i+n),addedge(i+n,i);
		sort(a+1,a+1+2*n);
		for(int i=1;i<=2*n;i+=2)	addedge(a[i].vl,a[i+1].vl),addedge(a[i+1].vl,a[i].vl);
		for(int i=1;i<=2*n;i++)if(!used[i])dfs(i,0);
		long long sum=0;bool t;
		for(int i=1;i<=2*n;i++)if(col[i])sum+=i;
		sum%=(2*n);
		if(sum)	t=false;
		else	t=true;
		for(int i=1;i<=2*n;i++)
			if(col[i]==t)	cout<<i<<' ';
		cout<<endl;
	}
	else
	{
		cout<<"First"<<endl;
		for(int i=1;i<=n;i++)	cout<<i<<' ';
		for(int i=1;i<=n;i++)	cout<<i<<' ';
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：wenhao801 (赞：1)

很好玩的一个题！

### 题意

现在有 $2n$ 个数 $1, 2, \cdots, 2n$。

Alice 和 Bob 在玩游戏。Alice 把这 $2n$ 个数分为 $n$ 组，每组两个数，然后 Bob 会从每组中选择一个数，把这选出来的 $n$ 个数求和，如果这个和 $\equiv 0 \pmod {2n}$，那 Bob 就赢了，否则 Alice 赢。你需要选择一方并帮它做出选择，然后获得胜利。

$1 \le n \le 5 \times 10^5$。

### 题解

先打了个暴力跑了一下，发现当 $n$ 为奇数时似乎 Bob 一定有解；当 $n$ 为偶数时，Alice 让 $1$ 和 $n$ 配对，$2$ 和 $n+1$ 配对，…… 可以胜过 Bob。我们可以进行解释：这是因为 Bob 选出来的和一定是 $kn+(1+2+\cdots+n)$ 的形式（其中 $k \in [0, n]$），而 $1+2+\cdots+n=n(n+1)/2$，这显然甚至不是 $n$ 的倍数。

这之后，*我受前几天做过的 AGC020C 的启发*，考虑到每组中选出一个数后还会剩下一个数，于是不妨算一下这些剩下的数的和：考虑 $1+2+\cdots+2n = n(2n+1)$，而我们选走的数的和是 $2n$ 的倍数，所以剩下的数的和模 $2n$ 一定余 $n$。

然后我花了一年意识到：这意味着我们只需要选出模 $n$ 余 $0$ 的一组数即可！

这一步的帮助实在是太大了，比如下面这组样例：

```
1 5
4 3
10 2
6 8
7 9
```

可以直接变成

```
1 0
4 3
0 2
1 3
2 4
```

这里，如果我们选了 $(0, 2)$ 中的 $0$，那么可以在 $(2, 4)$ 中把没选的 $2$ 选上，然后再选 $(4, 3)$ 中的 $4$、$(1, 3)$ 中的 $3$、$(1, 0)$ 中的 $1$，最终我们绕了一圈回来了。也就是说我们可以不重不漏地选出来 $0, 1, \cdots, n-1$。而它们的和就恰是 $n(n-1)/2$，$n$ 是奇数，问题解决。

~~话说，这个题的出题人是怎么写出 $n$ 是偶数时的 SPJ 的啊？？~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

inline int read() {
	int ret = 0, t = 1;
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	if (c == '-') t = -1, c = getchar();
	while (c >= '0' && c <= '9') ret = (ret * 10) + c - '0', c = getchar();
	return ret * t;
}

const int MAXN = 1001000;
int a[MAXN][2], b[MAXN][2]; bool out[MAXN], vis[MAXN];

int main () {
	int n = read(), i, j;
	if (n % 2 == 0) {
		puts("First");
		for (i = 0; i < 2 * n; i++) printf("%d ", i % n + 1);
		puts(""); fflush(stdout);
		return 0;
	}
	puts("Second"); fflush(stdout);
	for (i = 1; i <= n * 2; i++) {
		int x = read();
		if (a[x][0]) a[x][1] = i; else a[x][0] = i;
	}
	for (i = 1; i <= n; i++) {
		int u = a[i][0] % n, v = a[i][1] % n;
		if (b[u][0]) b[u][1] = i; else b[u][0] = i;
		if (b[v][0]) b[v][1] = i; else b[v][0] = i;
	}
	for (i = 0; i < n; i++) if (!vis[i]) {
		int now = i, pos = b[i][0];
		do {
			out[pos] = a[pos][1] % n == now; vis[now] = 1;
			now = a[pos][0] % n + a[pos][1] % n - now; pos = b[now][0] + b[now][1] - pos;
		} while (now != i);
	}
	int s = 0; for (i = 1; i <= n; i++) s = (s + a[i][out[i]]) % (n << 1);
	s = bool(s); for (i = 1; i <= n; i++) printf("%d ", a[i][out[i] ^ s]); puts("");
	fflush(stdout);
	return 0;
}
```


---

## 作者：Fuyuki (赞：1)

分两种情况讨论。

## n 为偶数

$\sum_{i=1}^{n}i=\frac{n(n+1)}{2}\equiv \frac{n}{2}\pmod{n}$

因此，按 $(i,i+n)$ 的形式划分可以保证无论怎么选，数字和在模 $n$ 的意义下都不为 $0$，因此可以使得先手必胜。

## n 为奇数

将输入的每个对都看作是图上连接的一条边，再将形如 $(i,i+n)$ 的边都连上。

可以发现，此时每个点的度数都等于二，因此这张图是由若干不交的环组成。

对每个环黑白染色，然后将所有黑点取出一定是一个合法的方案。

因为 $\sum_{i=1}^{n}i=\frac{n(n+1)}{2}\equiv 0\pmod{n}$，所以此时的数字和一定是 $n$ 的倍数。

并且因为 $\sum_{i=1}^{2n}i=n(2n+1)\equiv n\pmod{2n}$，所以如果数字和模 $2n$ 不为 $0$，将所有白点取出一定满足模 $2n$ 等于 $0$。

那么此时后手必胜。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define V inline void
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=1e6+1;
vector<int>e[N];
int n,m,sum,tag[N],a[N],id[N];
V check(int&x){x-=m,x+=x>>31&m;}
V first(){
	cout<<"First"<<endl;
	FOR(i,1,m)cout<<i%n+1<<' ';
}
V add_edge(int x,int y){e[x].push_back(y),e[y].push_back(x);}
V dfs(int u,int p=0){
	if(tag[u]=p)check(sum+=u);
	for(int v:e[u])if(!~tag[v])dfs(v,p^1);
}
V second(){
	cout<<"Second"<<endl;
	FOR(i,1,m)tag[i]=-1;
	FOR(i,1,m)
		if(!id[scanf("%d",a+i),a[i]])id[a[i]]=i;
		else add_edge(id[a[i]],i);
	FOR(i,1,n)add_edge(i,i+n);
	FOR(i,1,m)if(!~tag[i])dfs(i,1);
	if(sum)FOR(i,1,m)tag[i]^=1;
	FOR(i,1,m)if(tag[i])cout<<i<<' ';
}
int main(){scanf("%d",&n),m=n<<1,n%2==0?first():second();}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

哭唧唧，我是真的不会做奇数。

----------------------------------------

首先读完迷惑的题意，我们猜一定是两种对立的情况下双方各存在必胜策略。

不难想到根据 $n$ 的奇偶性讨论。

- 当 $n$ 是偶数时，我们将 $(i,i+n)$ 配对输出即可。在模 $n$ 意义下任意的选取等价于 $\sum_{i = 1} ^ n i \equiv \frac{n+1}{2} \pmod n$，则该数不是 $n$ 的倍数，自然也不是 $2n$ 的倍数；

- 当 $n$ 是奇数时，我们知道 $\sum_{i = 1} ^ {2n} i = \frac{2n(2n+1)}{2}$，考虑将 $(i,i+n)$ 连边并将题目给出的所有二元对连边，$2n$ 个点 $2n$ 条边每个点度数为 $2$，该图为许多个环的组合；

- 继续分析，如果有一个解记其和为 $s1$，则 $s1 + s2 = \frac{2n(2n+1)}{2}$，由于 $s1 \equiv 0 \pmod {2n}$，所以 $s2 \equiv n \pmod {2n}$；

- 继续观察，我们发现所有环都是偶环。因为所有的 $(i,i+n)$ 是相对的，有 $i$ 必定有 $i+n$，所以环的大小必定为偶数；

- 将原图黑白染色，则所有的 $i,i+n$ 必定异色，而由于在模 $n$ 意义下 $\sum_{i = 1}^ni \equiv 0\pmod {n}$，则黑/白两种颜色各自的和在模 $2n$ 意义下只有可能为 $0,n$ 两种情况。

- 用 $s1$ 表示黑色颜色的点和，$s2$ 表示白颜色的点和，若两种颜色各自的和在模 $2n$ 意义下都为 $0$ 或是 $n$，都将导致 $s1 + s2 \equiv 0 \pmod {2n}$，这是不可能的情况，所以 $s1,s2$ 必定一个的余数是 $0$，另一个的余数是 $n$。

时间复杂度线性。

```cpp
/*
要选 n 个数必须保证是 2n 的倍数。
每个二元组都要选一个，很有鸽巢原理的感觉。根据样例不难发现对于 2 的情况我们应该成为 A
对于 1 的情况我们应该成为 B
最小和为(n+1)n/2，最大和为3/2n^2+n/2不妨先考虑什么情况下一定能构造出无解的情况
我们知道，S1 + S2 = 2n * (2n + 1) / 2 = (2n+1)n
感觉没有什么很厉害的想法，不妨还是猜结论
奇数一定 B，偶数一定 A？ 
然后偶数可以直接(i,i+n)就卡死了，奇数感觉还是有点不会证明 
After reading the solution
好，妙，佩服。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
#define ll long long
int n,m,head[Len << 1],cnt,ad[Len << 1],cl[Len];
ll sum[3];
struct node
{
	int next,to;
}edge[Len << 2];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void col(int x)
{
	sum[cl[x]] += x;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(!cl[to]) 
		{
			cl[to] = 3 - cl[x];
			col(to);
		}
	}
}
int main()
{
	cin >> n;
	if(n % 2 == 0) 
	{
		cout << "First" << endl;
		for(int i = 1 ; i <= (n << 1) ; i ++) 
		{
			if(i <= n) cout << i << " ";
			else cout << i - n << " ";
		}
		return 0;
	}
	else 
	{
		cout << "Second" << endl;int x;
		for(int i = 1 ; i <= (n << 1) ; i ++) 
		{
			cin >> x;
			if(!ad[x]){ad[x] = i;}
			else add(ad[x] , i) , add(i , ad[x]);
		}
		for(int i = 1 ; i <= n ; i ++) add(i , i + n) , add(i + n , i);
		for(int i = 1 ; i <= (n << 1) ; i ++) if(!cl[i]){cl[i] = 1;col(i);}
		int dx = (sum[1] % (2 * n) == 0) ? 1 : 2;
		for(int i = 1 ; i <= (n << 1) ; i ++) if(cl[i] == dx) cout << i << " ";
		cout << endl; 
	}
	return 0;
}
```

---

## 作者：timefinder (赞：0)

蒟蒻的第一道 2800。

---

考虑共一个二元组中只能选一个，而在 $1$ 到 $2n$ 中恰好有 $n$ 对模以 $n$ 余数相同的二元组。按照 $n=4$ 为例，$\{1,5\}\{2,6\}\{3,7\}\{4,8\}$。如果我们选择先手，就这样分组，那么后手选择的数之和模以 $n$ 将恰为 $\frac{n(n-1)}{2}$。若 $n$ 为偶数，则后手选择的数之和模以 $n$ 为 $(\frac{n}{2})\times (n-1)$，既然 $n-1$ 为奇数，这个余数就失去了原 $n$ 中的一个 $2$ 因子，故后手选择的数之和不为 $n$ 的倍数。

考虑证明 $n$ 为奇数后手必胜。将每一个数字建点，如果我们将系统给出的每一对间连边，并将模以 $n$ 相同的之间连边，如下图
![](https://cdn.luogu.com.cn/upload/image_hosting/w0zr6n19.png)
因为如果图中有奇环，那么必有（至少）一个节点同时和两个模以 $n$ 异于自己的点连边，与题意矛盾。所以图中不存在奇环，这必然是一个二分图，也就意味着必有一种选择方式使得模以 $n$ 为 $0,1,2,...,n-1$ 的数字各被取到一个。如此，这些数字的和模以 $n$ 将为 $\frac{n(n-1)}{2}=(\frac{n-1}{2})n$ 即 $n$ 的倍数。若此时选择的数**除以** $n$ 之和 $cal$ 为奇数，且 $n-1$ 不为 $4$ 的倍数，直接可行；若 $cal$ 为偶，$n-1$ 为 $4$ 倍数亦可。反之，可以选择另一组点（原先选黑，如今就选白），即可。证明如下：

设黑点中除以 $n$ 恰为 $1$ 的有 $k$ 个，则白点中除以 $n$ 恰为 $1$ 的有 $n-k$ 个。既然 $n,k$ 均为奇数，那么 $n-k$ 为偶数，即选黑选白 $cal$ 奇偶性颠倒。

**code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,a[N],pir[N],t[N];
int vis[N]; 
vector<pair<int,int> > g;
int main(){
	cin>>n;
	if(n%2==0){
		printf("First\n");
		fflush(stdout);
		for(int i=1;i<=2*n;i++) a[i]=i%n+1,cout<<a[i]<<' ';
		fflush(stdout);
	}else{
		printf("Second\n");
		fflush(stdout);
		for(int i=1;i<=2*n;i++){
			cin>>a[i];
			if(pir[a[i]]) g.push_back({pir[a[i]],i});
			else pir[a[i]]=i;
		}
		for(pair<int,int> x:g){
			t[x.first]=x.second;
			t[x.second]=x.first;
		}
		int cal=0;
		for(int j=1;j<=n;j++){
			if(vis[j]) continue;
			vis[j]=1;
			cal+=j/n;
			for(int i=j;;){
				vis[t[i]]=-1;
				int x;
				if(t[i]>n) x=t[i]-n;
				else x=t[i]+n;
				if(vis[x]) break;
				vis[x]=1;
				cal+=x/n; 
				i=x;
			}
		}
		if((n-1)%4==0){
			if(cal%2==0){
				for(int i=1;i<=2*n;i++) if(vis[i]==1) cout<<i<<' ';
			}else{
				for(int i=1;i<=2*n;i++) if(vis[i]==-1) cout<<i<<' ';
			}
		}else{
			if(cal%2==1){
				for(int i=1;i<=2*n;i++) if(vis[i]==1) cout<<i<<' ';
			}else{
				for(int i=1;i<=2*n;i++) if(vis[i]==-1) cout<<i<<' ';
			}
		}
	}
	cout<<'\n';
	fflush(stdout);
	int res;cin>>res;
	return 0;
}
```

---

