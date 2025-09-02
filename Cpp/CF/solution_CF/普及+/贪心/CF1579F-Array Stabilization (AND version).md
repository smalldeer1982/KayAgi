# Array Stabilization (AND version)

## 题目描述

You are given an array $ a[0 \ldots n - 1] = [a_0, a_1, \ldots, a_{n - 1}] $ of zeroes and ones only. Note that in this problem, unlike the others, the array indexes are numbered from zero, not from one.

In one step, the array $ a $ is replaced by another array of length $ n $ according to the following rules:

1. First, a new array $ a^{\rightarrow d} $ is defined as a cyclic shift of the array $ a $ to the right by $ d $ cells. The elements of this array can be defined as $ a^{\rightarrow d}_i = a_{(i + n - d) \bmod n} $ , where $ (i + n - d) \bmod n $ is the remainder of integer division of $ i + n - d $ by $ n $ .  It means that the whole array $ a^{\rightarrow d} $ can be represented as a sequence $ $$$a^{\rightarrow d} = [a_{n - d}, a_{n - d + 1}, \ldots, a_{n - 1}, a_0, a_1, \ldots, a_{n - d - 1}] $ $ </p><p> </p></li><li> Then each element of the array  $ a\_i $  is replaced by  $ a\_i \\,\\&amp;\\, a^{\\rightarrow d}\_i $ , where  $ \\&amp; $  is a logical "AND" operator. </li></ol><p>For example, if  $ a = \[0, 0, 1, 1\] $  and  $ d = 1 $ , then  $ a^{\\rightarrow d} = \[1, 0, 0, 1\] $  and the value of  $ a $  after the first step will be  $ \[0 \\,\\&amp;\\, 1, 0 \\,\\&amp;\\, 0, 1 \\,\\&amp;\\, 0, 1 \\,\\&amp;\\, 1\] $ , that is  $ \[0, 0, 0, 1\] $ .</p><p>The process ends when the array stops changing. For a given array  $ a$$$, determine whether it will consist of only zeros at the end of the process. If yes, also find the number of steps the process will take before it finishes.

## 说明/提示

In the third sample test case the array will change as follows:

1. At the beginning $ a = [1, 1, 0, 1, 0] $ , and $ a^{\rightarrow 2} = [1, 0, 1, 1, 0] $ . Their element-by-element "AND" is equal to $ $$$[1 \,\&\, 1, 1 \,\&\, 0, 0 \,\&\, 1, 1 \,\&\, 1, 0 \,\&\, 0] = [1, 0, 0, 1, 0] $ $  </li><li> Now  $ a = \[1, 0, 0, 1, 0\] $ , then  $ a^{\\rightarrow 2} = \[1, 0, 1, 0, 0\] $ . Their element-by-element "AND" equals to  $ $ [1 \,\&\, 1, 0 \,\&\, 0, 0 \,\&\, 1, 1 \,\&\, 0, 0 \,\&\, 0] = [1, 0, 0, 0, 0] $ $  </li><li> And finally, when  $ a = \[1, 0, 0, 0, 0\] $  we get  $ a^{\\rightarrow 2} = \[0, 0, 1, 0, 0\] $ . Their element-by-element "AND" equals to  $ $ [1 \,\&\, 0, 0 \,\&\, 0, 0 \,\&\, 1, 0 \,\&\, 0, 0 \,\&\, 0] = [0, 0, 0, 0, 0] $ $  </li></ol> Thus, the answer is  $ 3 $  steps.<p>In the fourth sample test case, the array will not change as it shifts by  $ 2 $  to the right, so each element will be calculated as  $ 0 \\,\\&amp;\\, 0 $  or  $ 1 \\,\\&amp;\\, 1$$$ thus not changing its value. So the answer is -1, the array will never contain only zeros.

## 样例 #1

### 输入

```
5
2 1
0 1
3 2
0 1 0
5 2
1 1 0 1 0
4 2
0 1 0 1
1 1
0```

### 输出

```
1
1
3
-1
0```

# 题解

## 作者：Engulf (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1579F)

[更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-cf1579f)

## 分析

根据 $\&$ 操作的性质，**只要**有一个 $0$ 存在，这个数记作 $a_i$，那么 $a_{i+d}$ 就可以变成 $0$，然后 $a_{i+d}$ 又可以继续更新下一个数为 $0$，所以直接 bfs 解决即可。

最终的答案即为 bfs 的次数。注意，由于无论如何都会入队一次，最终答案需要**减一**。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f^=!(ch^45),ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
inline void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(int x){write(x);puts("");}

int n,d;
int a[1000005];

int main(){
	int T=read();
	while(T--){
		n=read(),d=read();
		for(int i=0;i<n;i++)a[i]=read();
		queue <int> q;
		for(int i=0;i<n;i++)if(!a[i])q.push(i);
		int ans=0;
		while(!q.empty()){
			int len=q.size();
			for(int i=0;i<len;i++){
				int u=q.front();q.pop();
				int v=(u+d)%n;
				if(a[v]){
					q.push(v);a[v]=0;
				}
			}
			ans++;
		}
		for(int i=0;i<n;i++)if(a[i])ans=-1;
		writeln(ans==-1?ans:ans-1);
	}
	#ifndef ONLINE_JUDGE
	system("pause");
	#endif
	return 0;
}
```

---

## 作者：_ChongYun_ (赞：4)


# 解析

对于 $\&$ 运算，有以下几种情况：

$0\&0=0$

$0\&1=0$

$1\&0=0$

$1\&1=1$

发现如果两个数中有一个是 $0$，那 $\&$ 的结果就是 $0$。

对于一个 $1 \le i \le n$，如果 $a_i=0$，那么就可以让 $a_{i+d}$ 变成 $0$，以此类推。

考虑 BFS，每次把 $a_{i+d}$ 变成 $0$。

BFS 的次数即为答案，如果最终还有元素为 $1$，那么一定无解，输出 $-1$。

实现时可以使用两个队列。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,d;
int a[1919810];
queue<int> q,q1;
int work(){
	int ans=0;
	bool flag=false;
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]) flag=true;
	}
	if(!flag) return 0;
	for(int i=1;i<=n;i++){
		if(!a[i]) q.push(i); 
	}
	while(!q.empty()){
		while(!q.empty()){
			int x=q.front();
			q.pop();
			if(a[x+d==n?n:(x+d)%n]){
				q1.push(x+d==n?n:(x+d)%n);
				a[x+d==n?n:(x+d)%n]=0;
			} 
		}
		while(!q1.empty()){
			q.push(q1.front());
			q1.pop();
		}
		ans++;
	}
	for(int i=1;i<=n;i++){
		if(a[i]) return -1;
	}
	--ans;
	return ans;
}
signed main(){
	cin>>t;
	while(t--) cout<<work()<<endl;
	return 0;
} 
```



---

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF1579F)

## 写在前面

此题解主要是讲思路，对实现并不多说。

# 思路

首先我们需要了解位运算与 $\&$ 这个东西。

$1\&1=1$，

$1\&0=0\&1=0\&0=0$。

然后我们观察一下这一组数据：
```
5 2
1 1 0 1 0
```
把它的几次变化记下来：

| 次数 | $a$ 数组 | $b$ 数组 |
| :-: | :-: | :-: |
| 第一次 | $\{1,1,0,1,0\}$ | $\{1,0,1,1,0\}$ |
| 第二次 | $\{1,0,0,1,0\}$ | $\{1,0,1,0,0\}$ |
| 第三次 | $\{1,0,0,0,0\}$ | $\{0,0,1,0,0\}$ |
| 第四次 | $\{0,0,0,0,0\}$ | $\{0,0,0,0,0\}$ |

仔细观察，你会发现“0”就像“病毒”一样，把“1”慢慢“感染”了，而每一次中，又有那些“1”会被“感染”，那些“1”会“存活”呢？

每一次，对于在 $i$ 这个位置的值 $a_i$，如果它是 $0$，那么它仍然是 $0$，如果它是 $1$，那么它就会变成 $a_{(i+d)\bmod n}$，开个整型队列和布尔型数组维护即可，记得判误解。

注意，上面那句话里的“位置”下标从 0 开始，而代码中下标从 1 开始。


# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N(1e6 + 7);
int t, n, d, x, sz, cnt, ans;
bool vis[N];
queue<int> q;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n >> d;
		for(int i(1); i <= n; ++ i) {
			cin >> vis[i];
			if(!vis[i]) {
				q.push(i);
			}
		}
		ans = cnt = 0;
		while(cnt < n) {
			cnt += (sz = q.size());
			if(!sz) {
				ans = 0;
				break;
			}
			while(sz --) {
				x = (q.front() + d - 1) % n + 1;	//一种巧妙的方法 
				q.pop();
				if(vis[x]) {
					q.push(x);
					vis[x] = false;
				}
			}
			++ ans;
		}
		cout << ans - 1 << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：Arghariza (赞：4)

- 题目大意：

给定一个长度为 $n$ 的 $01$ 数组 $a$ 和一个正整数 $d$。每一次操作令数组 $b$ 为 $a$ 向右**循环**移位 $d$ 位的数组，然后 $a_i$ 变成 $a_i\&b_i$ ，问多少次操作之后整个数组都变成 $0$。**如果不能通过有限次操作使得数组内的元素全部为 $0$ 则输出 $-1$**。

采用**多组数据**，第一行一个 $t$ 代表数据组数。每组数据第一行两个整数 $n,d$，第二行一个 $01$ 数组。

$1≤t≤10^3,1≤d≤n≤10^6,1≤\sum n≤10^6$

- $\mathtt{Solution}$

考虑 $d=1$ 的情况。

当数组每右移一位并且与上自身时，某一位上的 $0$ 显然不变，$1$ 直到有右边的一个 $0$ 到了这一位的时候才变成 $0$。也就是当左边有 $k$ 个 $1$ 的时候，你总要操作 $k+1$ 次才能把这个 $1$ 变成 $0$ 。

于是你发现这实际上是统计序列中**连续 $1$ 的最大个数**。

例如：

$\ \ \ \ \ 0\ 0\ 1\ 1\ 1\ 0\ 1\ 1\ 0\ 0\ 1$

$\to 0\ 0\ 0\ 1\ 1\ 0\ 0\ 1\ 0\ 0\ 0$

$\to 0\ 0\ 0\ 0\ 1\ 0\ 0\ 0\ 0\ 0\ 0$

$\to 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0$

手动模拟一下规律显然。

当 $d>1$ 时呢？

显然我们可以把 $1,2,...,n$ 分成 $g=\gcd(n,d)$ 组，每组互不干涉。

例如 $n=6,d=2$ 的时候这样：

$\{1,3,5\},\{2,4,6\}$

组内的元素就相当于 $d=1$ 的时候的移动了。

那也就是说原问题分成了 $g$ 个 $d=1$ 的子问题。注意当**有一组里面所有数都为 $1$ 的时候**这组无解。

总复杂度是 $O(n)$ 的，由于 $\sum n≤10^6$ ，所以可以通过，但是注意要开 $long\ long$。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 1e6 + 100;
int t, n, d, g, ans, s[maxn], tp[maxn << 1];

int gcd(int x, int y) {
    if (y == 0) return x;
    else return gcd(y, x % y);
}

signed main() {
    t = read();
    while (t--) {
        ans = 0;
        n = read();
        d = read();
        g = gcd(n, d);
        for (int i = 1; i <= n; i++) {
            s[i] = read();
        }
        for (int i = 1; i <= g; i++) {
            int c = 0;
            for (int j = 1; j <= n / g; j++) tp[++c] = s[(i + d * j - 1) % n + 1];
            for (int j = 1; j <= n / g; j++) tp[++c] = s[(i + d * j - 1) % n + 1];
            int tmp = 0, res = 0;
            for (int i = 1; i <= c; i++) {
                if (tp[i] == 1) tmp++;
                else tmp = 0;
                res = max(res, tmp);
            }
            ans = max(ans, res);
        }
        write(ans == n / g * 2 ? -1 : ans);
        puts("");
    }
    return 0;
}
```

---

## 作者：frank15 (赞：2)

## 思路

首先，如果所有位置都为 $0$ 直接输出 $0$。~~废话~~

其次，如果所有位置都为 $1$ 直接输出 $-1$。~~废话~~

那么，为什么所有位置都为 $1$ 就直接输出 $-1$ 呢。

显然这是因为这些 $1$ 无论如何都无法 $\&0 $ 。

那么我们就可以想到：如果这个序列中存在一个 $1$ 永远都不能 $\&0$ ，那么这个序列无解。

由题意，每个位置每次操作且的对象都是相同的（即 $a_i$ 每次都是 $\&$  同一个位置的数），我们设当前位置的对象为 $x$。

假设当前位置值为 $1$ ，那么当前位置变为 $0$ 当且仅当  $x$ 在上一次操作的时候变成了 $0$。假设 $x$ 为 $1$ ，那么当前位置变为 $0$ 当且仅当  $x$ 的对象在上上一次操作的时候变成了 $0$ 。这样依次类推下去，直到一个位置初始值就为 $0$ 。

显然如果一个 $1$ 他对象的对象的对象的对象 $\ldots$ 都为 $0$ 那么无解。

那么这道题就做完了。

## 代码

当我们遇到一个 $0$ 的时候，我们就从它的位置开始不断减 $d$，同时记录一个 $cnt$ 表示距上一个 $0$ 有多少步，遇到 $0$ 就将 $cnt$ 清 $0$ 
遇到 $1$ 就拿 $cnt$ 更新答案，同时经过的所有点标记访问，最后如果有没有访问到的点就输出 $-1$, 复杂度为 $\mathcal{O}({n})$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,d;
int a[1000005];
bool vis[1000005];
int main(){
	scanf("%d",&t);
	while(t--){
		for(int i=1;i<=n;i++)
			vis[i]=0;
		scanf("%d%d",&n,&d);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int ans=0;
		for(int i=1;i<=n;i++)
			if(!a[i]&&!vis[i]){
				int cnt=0,st=i;
				while(!vis[st]){
					vis[st]=1;
					if(a[st])
						ans=max(ans,cnt);
					else
						cnt=0;
					st=(st-d+n-1)%n+1;
					++cnt;
				}
			}
		bool flag=0;
		for(int i=1;i<=n;i++)
			if(!vis[i])
				flag=1;
		if(flag)
			puts("-1");
		else
			printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：activeO (赞：2)


## 题目大意

给出一个长度为 n 的 01 数组 a 和一个常数 d。每一次操作， 令数组 b 为 a 向右循环一处 d 为的数组，操作完成后 $ a_i=a_i \& b_i $，问多少次操作后整个数组都变成 0。

## 思路

先考虑一个 n 方的 dfs ，按位与，只有 0 会有贡献，于是去 dfs 每一个 0 做出的贡献，并记录 i 这个数 $ (1\leq i \leq n) $ 是在哪一轮被改为 0 的。

## 代码：


```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll maxn=1e6+5;
const ll inf=0x3f3f3f3f3f3f;
const ll mod=1e9+7;
ll a[maxn],n,d;
ll cost[maxn];

void dfs(ll u){
    a[u]=0;
    ll v=(u+d+n)%n;
    if(a[v]==0) return;
    cost[v]=cost[u]+1;//第几轮会修改到
    dfs(v);//继续模拟新0
}

int main(){

    ll t;

    scanf("%lld",&t);

    while(t--){
        memset(vis,0,sizeof(vis));
        memset(cost,0,sizeof(cost));
        scanf("%lld %lld",&n,&d);
        for(int i=0;i<n;i++) scanf("%lld",&a[i]);
        for(int i=0;i<n;i++){
            if(a[i]) continue;
            dfs(i);
        }
        ll sum=0;
        for(int i=0;i<n;i++) sum+=a[i];
        if(sum) puts("-1");
        else{
            ll ans=-inf;
            for(int i=0;i<n;i++) ans=max(ans,cost[i]);//取最后一次修改做答案
            printf("%lld\n",ans);
        }
    }

    return 0;
}
```

复杂度 $ O(n^2) $ 绝对超时，
这是我们考虑一个简单又常用的优化，记录一个 vis 数组，当一个 0 的贡献完之后就打上标记，使他不会再被 DFS 到。这样每一个节点都只会 dfs 到一次，复杂度应该是 $ O(n) $ 的可以 AC。

## 最终代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll maxn=1e6+5;
const ll inf=0x3f3f3f3f3f3f;
const ll mod=1e9+7;
ll a[maxn],n,d;
ll cost[maxn];
bool vis[maxn];

void dfs(ll u){
    vis[u]=1;//打标记
    a[u]=0;
    ll v=(u+d+n)%n;
    if(vis[v]) return;//如果之前v这个已经贡献过了
    if(a[v]==0) return;
    cost[v]=cost[u]+1;//第几轮会修改到
    dfs(v);//继续模拟新0
}

int main(){

    ll t;

    scanf("%lld",&t);

    while(t--){
        memset(vis,0,sizeof(vis));
        memset(cost,0,sizeof(cost));
        scanf("%lld %lld",&n,&d);
        for(int i=0;i<n;i++) scanf("%lld",&a[i]);
        for(int i=0;i<n;i++){
            if(a[i]) continue;
            dfs(i);
        }
        ll sum=0;
        for(int i=0;i<n;i++) sum+=a[i];
        if(sum) puts("-1");
        else{
            ll ans=-inf;
            for(int i=0;i<n;i++) ans=max(ans,cost[i]);//取最后一次修改做答案
            printf("%lld\n",ans);
        }
    }

//顺便求一个关注qwq
    return 0;
}
```


---

## 作者：activeO (赞：1)

## 题目大意

给出一个长度为 n 的 01 数组 a 和一个常数 d。每一次操作，
令数组 b 为 a 向右循环一处 d 为的数组，操作完成后 $ a_i=a_i \& b_i $，问多少次操作后整个数组都变成 0。

# 思路
发现只有 0 会做出贡献，对于每一个 0，去模拟他的贡献，如果会产生新的 0，就继续去 dfs 新的 0。最后如果 a 数组没有全部变为 0，则输出 -1，否则输出最后修改的那一轮。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll maxn=1e6+5;
const ll inf=0x3f3f3f3f3f3f;
const ll mod=1e9+7;
ll a[maxn],n,d;
ll cost[maxn];
bool vis[maxn];

void dfs(ll u){
	vis[u]=1;
	a[u]=0;
	ll v=(u+d+n)%n;
	if(vis[v]) return;
	if(a[v]==0) return;
	cost[v]=cost[u]+1;//第几轮会修改到
	dfs(v);//继续模拟新0
}

int main(){
	
	ll t;
	
	scanf("%lld",&t);
	
	while(t--){
		memset(vis,0,sizeof(vis));
		memset(cost,0,sizeof(cost));
		scanf("%lld %lld",&n,&d);
		for(int i=0;i<n;i++) scanf("%lld",&a[i]);
		for(int i=0;i<n;i++){
			if(a[i]) continue;
			dfs(i);
		}
		ll sum=0;
		for(int i=0;i<n;i++) sum+=a[i];
		if(sum) puts("-1");
		else{
			ll ans=-inf;
			for(int i=0;i<n;i++) ans=max(ans,cost[i]);//取最后一次修改做答案
			printf("%lld\n",ans);
		}
	}
	
	return 0;
}
```


---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1579F)

# 分析

遇见这道题是在模拟赛里，一看到题目就稀里糊涂的想到了暴力，可能数据太水了吧，居然 A 了。

我考虑了两个小小的优化：

1.就是把所有的 $a_i$ 为 $1$ 的 $i$ 记录下来，再去操作。

2.因为逻辑与是一个比较特殊的运算，只有两个数均为 $1$ 时，结果才为 $1$，所以有 $0$ 的时候一定为 $0$。

但是实际上还是有很多可恶~~毒瘤~~的数据卡的，不太推荐。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int t,n,d,cnt;
bool a[MAXN],b[MAXN];
int f[MAXN];
int calc(){
	int sum=0,maxx=0;
	for(int i=1;i<=cnt;i++){
		sum=0;
		while(1){
			sum++;
			f[i]+=d;
			f[i]%=n;
			if(f[i]==0)f[i]=n;//注意，如果取模完以后为0，那么它的值其实是n
			if(a[f[i]]==0)break;
			if(sum>n)return -1;//操作n+1次后如果还没有结果，那么一定无解
		}
		maxx=max(maxx,sum);
	}
	return maxx;
}
int main(){
	scanf("%d",&t);
	while(t--){
		cnt=0;
		scanf("%d%d",&n,&d);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]==1)f[++cnt]=i;//标记i
		}
		if(cnt==0)printf("0\n");
		else{
			int h=calc();
			printf("%d\n",h);
		}
	}
	return 0;
}
```

----
接下来我们就再想优化。

上文已经说到，因为逻辑与是一个比较特殊的运算，只有两个数均为$1$时，结果才为 $1$,所以有 $0$ 的时候一定为 $0$。

所以若某个 $i$ 让 $a_i$($a_i=1$) 不断进行循环移位 $d$ 位时，永远碰不到  $0$，那么就无解。

否则就把答案记录下来输出就 Ok 了。

---

## 作者：JCLinux (赞：1)

## 题目大意
长度为 $n$ 的数组，只由 0 1 组成，下标从 0 开始。

定义一种操作，包含以下两个步骤：

1.把数组中每个数右移 $d$ 位。

2.把移动后的数组和原来的数组中的每个数相**与**，得到新的数组。

问：经过几次这种操作之后，整个数组全部变成 0 

## 思路：
首先想到的是暴力模拟，一看数据范围，行不通。

我们考虑：把数组中的数变成 0 ，是原有的 0 的功劳。那我们考虑只模拟 0 行不行。

考虑一种情况：前半段全部是 0 ，后半段全部是 1 ， $d=1$ ，此时我们会发现，**只有最后一个 0 是起作用的**，其他的全部打酱油。也就是说，对于后面的 0 来说，他已经有了~~仙人~~（前继），能由它完成的转化，**一定抢先一步叫他前继完成了**。因此，当一个 0 的任务已经被完成了，他就可以从队列中被删掉了，这样就保证了没有夯余。于是我们就可以愉快的进行模拟了。

有一点要注意的是，这个题目要你求需要几次操作才能完成，因此我用了两个队列，这样就能将轮与轮之间区分开。

还有一点要注意的是结束条件的判定，当队列空的时候结束，扫描一遍整个数组，还有不为 0 的就说明，没办法完成任务，输出 -1 即可。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,d,times;
bool arr[1000006];
queue<int> q;
queue<int> cache;
int main()
{
    cin.sync_with_stdio(false);//提高输入的速度
    cin >> t ;
    while(t--)
    {
        cin >> n >> d;
        times=0;
        memset(arr,0,n+1);
        for(int i=0;i<n;i++) cin >> arr[i];
        for(int i=0;i<n;i++)
        {
            if(!arr[i]) q.push(i);
        }
        while(!q.empty())
        {
            while(!q.empty())
            {
                int tmp=q.front();
                q.pop();
                if(arr[(tmp+d)%n])
                {
                    arr[(tmp+d)%n]=0;
                    cache.push((tmp+d)%n);
                }
            }
            while(!cache.empty())
            {
                q.push(cache.front());
                cache.pop();
            }
            times++;
        }
        bool flag=1;
        for(int i=0;i<n;i++) if(arr[i]){flag=0;break;}
        if(flag) cout << times-1 << endl;
        else cout << -1 << endl;
    }
    return 0;
}

```


---

## 作者：wimg6_ (赞：0)

注意到与的性质，会发现 $S=a_1\operatorname{and} a_2\operatorname{and}\cdots\operatorname{and}a_n$ 中，只要 $\exists\ a_i=0\ (1\leq i\leq n)$，那么就会有 $S=0$。

所以考虑对于每一个 $a_i=0\ (1\leq i\leq n)$，在下一次操作中让 $a_{i+d}=0$ 即可。（下标默认在模 $n$ 意义下考虑，下同。）

于是我们可以考虑进行广度优先搜索，广度优先搜索的次数就是答案。如果有一个数，其无论如何都不会变为 $0$，那么输出 $-1$ 即可。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,d,ans,kans,a[1000010];
queue<int>q;
void bfs(){
    while(!q.empty()){
        if(ans==n){
            printf("%d\n",kans);
            return ;
        }
        kans++;
        int l=q.size();
        while(l--){
            int na=q.front();
            q.pop();
            if(a[(na+d-1)%n+1]) a[(na+d-1)%n+1]=0,ans++,q.push((na+d-1)%n+1);
        }
    }
    if(ans==n) printf("%d\n",kans);
    else printf("-1\n");
    return ;
}
int main(){
    // freopen("CF1579F.txt","w",stdout);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&d);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        ans=kans=0;
        while(!q.empty()) q.pop();
        for(int i=1;i<=n;i++)
            if(!a[i]) q.push(i),ans++;
        bfs();
    }
    return 0;
}
```

**更新日志**

修复了一些格式问题。

---

## 作者：__PJL__ (赞：0)

### 思路

观察题目，不难发现，如果序列中有一个 $0$，那么这个 $0$ 移动后无论在哪个位置，这个位置一定也会变为 $0$，所以可以把题目理解成，每次将序列中的 $0$ 右移 $d$ 位，问多少次可以用 $0$ 覆盖掉序列中的所有 $1$，bfs 即可。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 1;

int n, d, T, ans, a[MAXN], b[MAXN], h = 1, t;
void bfs() {
	while(h <= t) {
		int len = t - h + 1;
		for(int i = 1; i <= len; i++) {
			int x = b[h++], y = (x + d) % n; 
			if(a[y] > 0) {
				b[++t] = y, a[y] = 0;
			}
		}
		ans++;
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) {
		ans = 0;
		cin >> n >> d;
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		for(int i = 0; i < n; i++) {
			if(a[i] == 0) {
				b[++t] = i;
			}
		}
		bfs();
		for(int i = 0; i < n; i++) {
			if(a[i] != 0) {
				ans = -1;
			}
		}
		cout << ans - (ans != -1) << "\n";
	}
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

传送门：  [CF1579F Array Stabilization (AND version)](https://www.luogu.com.cn/problem/CF1579F)


# 题意

给定一个长度为 $n$ 的 $01$ 数组 $a$ 和一个正整数 $d$。每一次操作令数组 $b$ 为 $a$ 向右循环移位 $d$ 位的数组，然后 $a_i$ 变成 $a_i\&b_i$ ，问多少次操作之后整个数组都变成 $0$。如果不能通过有限次操作使得数组内的元素全部为 $0$ 则输出 $-1$。

$1≤t≤10^3,1≤d≤n≤10^6,1≤\sum n≤10^6$

# 思路

首先看到 $n$ 的范围，很明显要用 $O(n)$ 做法。

我们磨一下样例，发现每次操作中，每个 $\large a_i \gets a_i \& a_{(i+d)\mod n}$。而与运算中，只要有一个运算数是 $0$，结果就是 $0$。想到这里，这题就不难了。直接宽搜，每次以满足 $a_i =0$ 的 $i$ 为起点，搜索 $\large a_{(i+d) \mod n}$，如果搜到的数是 $1$，把它改成 $0$；如果搜到 $0$，说明这个点能通过更少的操作次数变成 $0$，所以不用考虑。

最后所有点都搜完了，如果还有点是 $1$，说明它再怎么改也改不了了，无解；否则输出每个点最少操作次数的最大值。

# 上代码！

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,d,qu[1000001],l,r,dis[1000001],ans,u,nu;
bool a[1000000];
void bfs()
{
	while(l<r)
	{
		u=qu[++l];
		nu=(u+d)%n;
		if(a[nu])dis[nu]=dis[u]+1,a[nu]=0,qu[++r]=nu;
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&d),l=r=ans=0;
		for(int i=0;i<n;++i)
		{
			scanf("%d",a+i);
			if(!a[i])qu[++r]=i,dis[i]=0;//如果是0，入队准备搜索。
			else dis[i]=0xfffffff;
		}//循环的数组下标从0开始比较方便。
		bfs();
		for(int i=0;i<n;++i)ans=max(ans,dis[i]);
		if(ans==0xfffffff)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Erotate (赞：0)

可以发现当 $d=1$ 时，每右移一位，只有当 1 碰到 0 时，才可以把前面的连续的一消去。也就是说，对于一段长度为 $k$ 的 1 串，你需要  $k+1$ 次操作才能消去。于是我们只需要统计序列中连续 1 串的最大长度即可。

当 $d>1$ 时，我们只需要把 $n$ 个数分成 $\gcd{(n,d)}$ 组，再对每一组进行与 $d=1$ 时一样的方法解决即可。因为这样每组互不干涉。当有一组里面所有数都为 1 的时候直接输出 $-1$。

代码：
```cpp
#include<bits/stdc++.h>
#define lhr long long
using namespace std;
lhr t,n,d,a[1000005],c[2000005],g,ans;
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>n>>d;
        g=gcd(n,d);
        for(int i=1;i<=n;++i) cin>>a[i];
        for(int i=1;i<=g;++i){
            lhr cc=0,tmp=0,cnt=0;
            for(int j=1;j<=n/g;++j) c[++cc]=a[(i+d*j-1)%n+1];
            for(int j=1;j<=n/g;++j) c[++cc]=a[(i+d*j-1)%n+1];
            for(int i=1;i<=cc;++i){
                if(c[i]==1) tmp++;
                else tmp=0;
                cnt=max(cnt,tmp);
            }
            ans=max(ans,cnt);
        }
        cout<<(ans==n/g*2?-1:ans)<<endl;
    }
    return 0;
}
```


---

