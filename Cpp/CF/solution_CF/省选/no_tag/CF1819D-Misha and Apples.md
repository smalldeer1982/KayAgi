# Misha and Apples

## 题目描述

给定 $n$ 个集合 $S_i$，第 $i$ 个集合的大小为 $k_i$，集合元素为 $1\sim m$ 的正整数。**特别地，若 $k_i = 0$，则 $S_i$ 可以是正整数 $1\sim m$ 的任意可空子集，由你确定**。

设 **可重集** $S$，初始为空。按编号从小到大依次遍历每个集合，往 $S$ 中加入 $S_i$ 所有元素。每次加入当前集合的所有元素后，若 $S$ 包含重复元素，则清空 $S$。注意，一个集合内的元素 **同时** 被加入 $S$。

你需要确定 $k_i = 0$ 的 $S_i$ 具体包含哪些数，使得最终的 $|S|$ 最大。求出这个最大值。

多组数据。

$1\leq T, \sum n, m\leq 2\times 10 ^ 5$，$0\leq \sum k_i\leq 2\times 10 ^ 5$，$S_i$ 的元素互不相同。

注意不保证 $\sum m$ 的数量级。

## 样例 #1

### 输入

```
4
3 4
2 1 2
2 4 1
2 1 2
4 4
2 1 2
2 3 4
0
1 1
2 5
0
0
5 3
0
3 1 2 3
2 3 1
0
1 3```

### 输出

```
2
1
5
3```

# 题解

## 作者：空气树 (赞：9)

首先考虑未知物品商店有哪些决策：一种是出现重复物品，让当前背包清空；一种是不出现重复物品，尽量填不会出现的物品。

显然，第二种决策，只会在最后出现，之后不会再让背包清空了。可以从后往前扫，找出最长后缀 $[r,n]$，使得背包不会清空。那么最后一次清空背包一定就在 $[r-1,n]$ 这段区间中。

问题就贪心地可以转换成找到最小的 $x \in [r-1,n]$，并且背包可以在 $x$ 商店后清空。

因为如果找到了这个 $x$，$[x+1,n]$ 出现的未知商店显然都是第二决策，并且只要出现一个答案就直接为 $m$ 了；否则答案可以直接模拟得出。

现在就考虑设 $f_i$ 表示，离开 $i$ 商店后能否让背包清空。设 $g_i$ 表示距离 $i$ 最近的可以清空背包的商店。
（注意这里考虑的是 $[1,i-1]$ 中）

如果 $i$ 商店未知，显然 $f_i=1$。

否则，考虑枚举其物品 $u_i$，并找到 $u_i$ 上一次出现的商店 $j$。那么如果  $[g_j+1,i-1]$ 这段商店经过后可以不被清空，就说明 $u_i$ 可以在 $i$ 处重复，所以    $f_i=1$。这里的判断可以先双指针得到最小的 $l_i$，使得 $[l_i,i-1]$ 可以不被清空。然后直接判断 $g_j+1$ 和 $l_i$ 大小即可。（注意还要再同理做一下上一个未知商店，因为其也可以出现 $u_i$。）

这样就可以求出所有的 $f_i$ 了，$g_i$ 显然随之求出。

于是就可以得到 $x$。那么问题就得到了解决。

时间复杂度为 $\mathcal {O(n)}$。

注意这题多组数据的清空！毕竟没保证 $m$ 总和的范围。


---

## 作者：hfjh (赞：6)

# CF1819D Misha and Apples 题解

我们考虑**最晚一次清空尽量早**，这样清空之后的的处理就很简单了。

我们定义 $cl_i$ 表示枚举到当前的 $i$ **最晚一次清空尽量早**，在 $cl_i$ 处。

我们定义 $f_i$ 表示在 $i$ 时候**是否可以**被清空。

我们定义 $mx$ 表示 $S_i$ 所有元素上一次出现位置**最晚一次**在哪里。 

当前在 $i$，先来求 $f_i$：

- 如果 $cl_{i} < mx$ ，显然当前一定出现重复元素，$f_i = 1$。

- 如果 $cl_i \ge mx$，并且 $[cl_i+1, mx]$ 之前存在一个空集，那么这个空集一定可以为我所用，让我在 $i$ 清空，$f_i = 1$。

- 否则 $f_i = 0$。

> 注意我们的 $f_i$ 表示能否被清空，而不是一定被清空。 

然后来更新 $cl_{i + 1}$ ：

初始化 $cl_{i+1} = cl_i$

- 如果 $cl_{i + 1} < mx$，那么在 $i$ 处会被清空，我们要让**最晚一次清空尽量早**，我们就要让 $mx$ 被清空掉，所以 `++cl[i + 1]`，直到 $cl_{i+1} \ge mx$，进入下面的流程。

- 如果 $cl_{i+1} \ge mx$ ，如果 $f_{cl_{i+1}} = 0$，那么 `++cl[i + 1]`，直到 $f_{cl_{i+1}} = 1$

最后 $cl_n$ 就是最晚一次清空位置了。

之后看 $cl_n\sim n$ 有没有空集，若有答案就是 $m$，若没有答案就是 $cl_n \sim n$ 集合元素个数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10; 
int T, k[N], n, m, x, cl, mx;
int w[N], f[N], pr[N], ans = 0;
vector<int> a[N];
vector<int> now;
void input(){
	cin>> n >> m;
	for(int i = 1; i <= n; ++i){
		cin>>k[i];
		pr[i] = pr[i - 1] + (k[i] == 0);
		for(int j = 1; j <= k[i]; ++j) cin>>x, a[i].push_back(x);
	}
}
void op(){
	cl = 0;f[0] = 1;
	for(int i = 1; i <= n; ++i){
		mx = 0;
		for(int j : a[i]) mx = max(mx, w[j]), w[j] = i;
		if(mx > cl) f[i] = 1;
		else if(mx <= cl && pr[i] - pr[cl]) f[i] = 1;
		while(cl < mx || f[cl] == 0) ++cl; 
	}
	if(pr[n] - pr[cl]) ans = m;
	else{
		for(int i = cl + 1; i <= n; ++i){
			ans += a[i].size();
		}
	}	
}
void qk(){
	ans = 0;
	for(int i = 1; i <= n; ++i){
		for(int j : a[i]) mx = max(mx, w[j]), w[j] = 0;
	}
	for(int i = 1; i <= n; ++i){
		a[i].clear();
		f[i] = 0;
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(false); 
	cin>>T;
	while(T--){
		input();
		op();
		cout<<ans<<'\n';
		qk();
	} 
	return 0;
} 
```

---

## 作者：Alex_Wei (赞：3)

### [CF1819D Misha and Apples](https://www.luogu.com.cn/problem/CF1819D)

将商店卖的苹果种类看成集合 $S_i$，设 $f_i$ 表示最小的 $j$ 使得编号为 $f_i\sim j$ 的集合都可以被保留。

考虑转移，显然 $f_{i - 1}\leq f_i$。

- 若 $k_i = 0$，则令 $S_i = \varnothing$ 即可使 $f_i = f_{i - 1}$。
- 若 $k_i > 0$，考虑最大的 $p < i$ 使得 $S_p$ 和 $S_i$ 有交。若不存在，则 $f_i = f_{i - 1}$。否则若此时 $S_p$ 仍未被删去，则整个背包就空了。
  - 若 $p < f_{i - 1}$，$p$ 无论如何一定被删去，$f_i = f_{i - 1}$。
  - 若 $p\geq f_{i - 1}$ 就不太好办了。发现此时 $f_i$ 等于最小的 $q + 1$，满足 $p\leq q$ 且存在一种方案使得 $S_q$ 之后整个背包为空。

因此，设 $g_i$ 表示是否存在一种方案使得处理 $S_i$ 之后整个背包为空。

- 若 $k_i = 0$，总可以使得背包为空：若处理 $S_i$ 之前背包为空，则令 $S_i = \varnothing$；否则令 $S_i$ 为之前的背包。故 $g_i = 1$。
- 若 $k_i > 0$，如果 $f_{i - 1}\sim i - 1$ 之间有 $k_j = 0$，则可以通过合理地设置 $S_j$ 清空背包，$g_i = 1$。否则考虑最大的 $p < i$ 使得 $S_p$ 和 $S_i$ 有交。若不存在，显然 $g_i = 0$。
  - 若 $p < f_{i - 1}$，则无论如何 $S_i$ 无法被删去，$g_i = 0$。
  - 若 $p \geq f_{i - 1}$，则 $S_i$ 可以通过 $S_p$ 将整个背包清空，$g_i = 1$。

用 `set` 维护所有 $g_i = 1$ 的 $i$，时间复杂度 $\mathcal{O}(n\log n + \sum k_i)$。

每次查询 `lower_bound` 之后 $f$ 值变成对应后继加 $1$，具有单调性，直接双端队列维护。

若 $f_n\sim n$ 之间有 $k_i = 0$，显然答案为 $m$。否则答案为之间的 $k_i$ 之和。

时间复杂度 $\mathcal{O}(n + \sum k)$。注意清空的复杂度，因为 $\sum m$ 没有保证。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1e9 + 7;
void add(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int N = 2e5 + 5;

int n, m, k[N], c[N];
int f[N], g[N], pre[N];
vector<int> arr;
void solve() {
  cin >> n >> m;
  deque<int> d;
  for(int i = 1, a; i <= n; i++) {
    cin >> k[i];
    c[i] = c[i - 1] + !k[i];
    f[i] = f[i - 1];
    g[i] = c[i] - c[f[i - 1] - 1] > 0;
    int p = 0;
    for(int _ = 1; _ <= k[i]; _++) {
      cin >> a, arr.push_back(a);
      p = max(p, pre[a]), pre[a] = i;
    }
    if(p >= f[i - 1]) {
      while(!d.empty() && d.front() < p) d.pop_front();
      if(d.empty()) f[i] = i + 1;
      else f[i] = d.front() + 1;
      g[i] = 1;
    }
    if(g[i]) d.push_back(i);
  }
  for(int it : arr) pre[it] = 0;
  arr.clear();
  int ans = 0;
  for(int i = f[n]; i <= n; i++)
    if(!k[i]) return cout << m << "\n", void();
    else ans += k[i];
  cout << ans << "\n";
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  f[0] = 1;
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：pengyule (赞：3)

借鉴了 Codeforces 中 @Cxny 的提交记录，非常清晰易懂。

---

不难想到最后我们需要找到一个最早的位置，使得我们能够将最晚一次清空控制在此处。这样一来，后面的处理就是平凡的了。

考虑用双指针来对每一个 $i$ 求出 $lim$ 表示我们能够将到 $i$ 目前为止的最晚一次清空控制在 $lim$ 处。同时对于每个 $i$ 求一个 $can_i$ 表示在 $i$ 处清空是否可能。

初始令 $lim\gets 0,can_0\gets 1$。  
当到达一个 $i$ 时，先来求 $can_i$。如果 $lim<mx$，其中 $mx$ 为 $a_i$ 中所有元素的上一次出现位置的最大值，那么 $can_i=1$；如果 $lim\ge mx$，但是 $[lim+1,mx]$ 中存在一个空集，那么自然也可以调控使得 $i$ 处出现一次清空；其余情况都不可能在 $i$ 处实现清空。  
接下来需要更新出 $i+1$ 的 $lim$ 了。如果此时 $lim<mx$，那么 $i$ 处会爆炸，为了使最后一次爆炸早于 $i$ 我们需要让 $mx$ 被某一次爆炸炸掉，因此让 $lim\gets lim+1$；等到 $lim\ge mx$ 时，如果 $can_{lim}=1$，则还是要 $lim\gets lim+1$，直到稳定。

最后的 $lim$ 就是我们能够将最晚一次清空控制在的最早位置。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
int x,f;
const int buflen=1<<21;
char buf[buflen],*p1=buf,*p2=buf;
inline char gc(){
	return p1==p2&&(p2=buf+fread(p1=buf,1,buflen,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	x=0,f=1;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=gc();
	return f?x:-x;
}
}
using IO::read;
const int N=2e5+5;
int n,m,las[N],cnt_empty[N];
bool canclearhere[N];
vector<int>a[N];
void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		int k=read();
		a[i].resize(k);
		for(int j=0;j<k;j++)a[i][j]=read(),las[a[i][j]]=0;
		cnt_empty[i]=cnt_empty[i-1]+!k;
	}
	canclearhere[0]=1;
	int clearable_lim=0;//how early can you hold the currently last clearance at
	for(int i=1;i<=n;i++){
		int mx=0;
		for(int j:a[i])mx=max(mx,las[j]),las[j]=i;
		if(clearable_lim<mx||cnt_empty[clearable_lim]<cnt_empty[i])canclearhere[i]=1;
		else canclearhere[i]=0;
		while(clearable_lim<mx||!canclearhere[clearable_lim])clearable_lim++;//obviously clearable_lim will not exceed i
	}
    if(cnt_empty[clearable_lim]<cnt_empty[n])cout<<m<<'\n';
    else {
        int sum=0;
        while(clearable_lim+1<=n)clearable_lim++,sum+=a[clearable_lim].size();
        cout<<sum<<'\n';
    }
}
int main(){
	int T=read();
	while(T--)solve();
}
/*
Typical mistake(s): for(i,1,m)las[i]=0 ----> TLE on test 50!

g++ -o 1819D.exe 1819D.cpp -O2 -Wall -Wextra -std=c++11
1819D
4
3 4
2 1 2
2 4 1
2 1 2
4 4
2 1 2
2 3 4
0
1 1
2 5
0
0
5 3
0
3 1 2 3
2 3 1
0
1 3

*/
```

---

## 作者：complete_binary_tree (赞：1)

显然，我们要让最后一次清空最提前。

那么我们设 $f_i$ 为 $S_i$ 之前最后一次被清空最提前的位置。

然后我们要满足以下几个条件：

- 最后一次清空以后，也就是 $[f_i,i)$ 中的元素都不能和 $S_i$ 重复。

- 位置 $f_i$ 是可以被清空的。

前面那个条件很容易满足，预处理一下不能被清空的最后一位在哪里就行了。（记作 $mx_i$）

后面那个条件，我们可以再设一个 $g_i$，为到 $i$ 能否清空。

- 首先，$f_i$ 之前肯定是要被清空的。也就是说，我们只需要看 $(f_i, i]$ 是否能删除就行了。

  - 如果这段中有 $k_i = 0$（能自定义）的段，那么肯定能删除。（这个预处理一下就能 $O(1)$ 求了）
  
  - 否则，要看 $mx_i$ 在不在 $(f_i, i)$ 里面，如果在也能删除。
  
  - 如果不在，那么也就删除不了了。

那么 $f_i$ 的转移就可以是：

- 首先，$f_i$ 肯定大于等于 $f_{i - 1}$。因为 $f_{i - 1}$ 之前的东西肯定都被清空掉了。所以 $f_i$ 初始值为 $f_{i - 1}$。

- 然后，$mx_i$ 肯定不能在 $f_i$ 到 $i$ 之间。否则 $i$ 就会被清除了。那么 $f_i$ 自增直到 $\ge mx_i$。（当然直接取 $\max$ 应该也没问题）

- 还有，$g_{f_i}$ 要为 $1$。所以直接往后找找到一个 $1$ 就行了。

然后我们可以先更新 $g_i$，再更新 $f_{i+1}$。

最后，统计答案的时候，如果 $(f_n, n]$ 中有空集，那么直接输出 $m$，否则只要模拟一下即可。

由于 $\sum m$ 没有保证，所以需要注意一下清空的复杂度。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int t, k[N], n, m, lst[N], mx[N], g[N], lstcan[N];
vector<int> s[N];
queue<int> q;

int main(){
	scanf( "%d", &t );
	while( t-- ){
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; ++i ){
			mx[i] = 0;
			scanf( "%d", &k[i] );
			s[i].resize( k[i] + 1 );
			if( k[i] == 0 ) lstcan[i] = i; else lstcan[i] = lstcan[i - 1];
			for( int j = 1; j <= k[i]; ++j ){ scanf( "%d", &s[i][j] ); mx[i] = max( lst[s[i][j]], mx[i] ); lst[s[i][j]] = i; q.push( s[i][j] ); }
		}
		for( int i = 1; i <= n + 1; ++i ) g[i] = 0;
		g[0] = 1;int f = 0; //其实 f 没必要开成数组，现场计算现场用即可。
		for( int i = 1; i <= n; ++i ){
			if( lstcan[i] > f || mx[i] > f ) g[i] = 1; else g[i] = 0;
			while( g[f] == 0 || f < mx[i] ) ++f;
		}
		int ans = 0;
		if( lstcan[n] > f ) printf("%d\n", m);
		else{ for( int i = f + 1; i <= n; ++i ) ans += k[i]; printf("%d\n", ans); }
		while( !q.empty() ) lst[q.front()] = 0, q.pop(); //注意清空的时间复杂度
	}
	return 0;
}
```

---

## 作者：_SunLig (赞：0)

# CF1819D Misha and Apples 题解

记 $R_i$ 表示最小的 $j$ 使得存在一种方案使得 $[i,j]$ 不会使得 $S$ 被清空。

在这种情况下，我们贪心的令所有 $k=0$ 的集合为空集。显然可以通过维护某个元素这一次出现和上一次出现的位置快速计算出所有的 $S$。

设 $dp_i$ 表示是否可以构造一种方案使得，加入集合 $S_i$ 后，$S$ 被清空。

首先，$dp_i$ 应该从一个可以被清空的前缀 $j$ 转移而来。并且区间 $[j+1,i-1]$ 应该是可以被控制的，不会被强制清空。

贪心的二分出最远的 $j$。

区间 $[j+1,i]$ 可以被构造，需要满足区间长度不为 $1$，且区间存在一个 $k=0$ 的集合或区间本来就会被清空。

注意到 $j$ 具有单调性，实际上可以用双指针 $O(n)$ 维护。

构造答案是简单的，同样对于 $n$ 找出最远的 $j$。

如果 $[j+1,n]$ 中存在一个 $k=0$ 的集合，答案显然为全集 $m$。

否则答案为 $|\bigcup_{i=j+1}^nS_i|$。

时间复杂度 $O(n)$。

---

## 作者：Unnamed114514 (赞：0)

定义 $f_i$ 表示前 $i$ 个是否清空。

显然可以求出 $pos$ 表示 $k=0$ 的都被扬掉的情况下，$i$ 后面第一次清空的位置，那么显然 $f_{pos}\gets f_{pos}\operatorname{or} f_{i-1}$，这玩意显然用双指针即可。

考虑 $k=0$ 可以怎么发挥作用，对于每个 $pos'<pos$ 显然 $S_{pos'}$ 中的元素不会在其它里面出现，且 $i\to pos'$ 不会清空。

此时我们只需要让一个 $k=0$ 的玩意出现一个 $S_{pos'}$ 里面的元素，就能让它在 $pos'$ 之后的位置被清空。

我们记 $i$ 之后的第一次出现 $k=0$ 的位置为 $lst$，那么 $[lst,pos)$ 都会与 $f_{i-1}$ 进行逻辑或。

初看区间或，似乎需要用 DS，实则不然。

$pos$ 显然可以 $O(1)$ 转移。

我们把 $[1,i]$ 中 $f$ 为 $0$ 的维护一个队列，显然随着 $i$ 的增大 $lst$ 会增大，所以 $<lst$ 的显然没用。

然后队列里面剩下的就是 $[lst,pos)$ 的值。

此时注意到如果 $f_{i-1}=1$ 那么直接给队列里面都赋值成 $1$ 并清空队列即可；如果 $f_{i-1}=0$ 显然不需要操作。

每个点入队出队一次，是 $O(n)$ 的。

下面再讲讲答案的求解方法。

我们在清空之后分割出来了若干个段，显然只需要考虑最后一个段。

枚举起点 $i$，要保证这个段不会出现清空操作，用类似于 $f$ 转移的方法判即可，然后因为这是一个完整的段，所以前面的要保证 $f_{i=1}=0$。

然后若这个区间中有 $k=0$ 的话，显然可以把剩下的都选出来，答案是 $m$，否则就是这里面数的数量。

另外，判断一段是否会清空的时候，笔者最先想到的是 `bitset`，但是会寄，实际上直接暴力就行了，维护 $cnt$ 表示出现次数，每次直接暴力修改即可。因为第一步是双指针只会加一次减一次，第二步只会加一次所以直接暴力就是对的。

---

## 作者：DerrickLo (赞：0)

我们考虑记 $f_i$ 表示遍历完 $[1,i]$  的集合之后能否清空。

我们先考虑一个区间 $[j,i]$ 能否恰好在 $i$ 删空，显然要满足以下条件：

- $[j,i-1]$ 的集合中没用相同的数。

- $[j,i-1]$ 中有空集合或者 $[j,i-1]$ 中有与 $S_i$ 相同的元素。

那么我们发现可以二分找到满足第一个条件的最小的 $j$，然后对于第二种条件的每一种情况，我们可以找到满足这种情况的最大的 $j$，然后我们只需要判断这个区间内是否有 $f_j=1$ 即可，可以使用前缀和判断。

求完 $f_i$ 后，我们考虑枚举最后被删完的集合 $i$，事实上对于 $i$ 的答案也是很好计算的。

时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,k[200005],x,lst[200005],f[200005],s[200005],cnt[200005],l[200005],fr[200005],cntt[200005];
vector<int>ve[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m,f[0]=s[0]=1;
		for(int i=1;i<=n;i++)ve[i].clear(),f[i]=s[i]=0;
		for(int i=1;i<=n;i++){
			cin>>k[i],ve[i].emplace_back(0);
			for(int j=1;j<=k[i];j++)cin>>x,ve[i].emplace_back(x);
		}
		int j=1;
		for(int i=1;i<=n;i++){
			for(int a=1;a<=k[i];a++)cnt[ve[i][a]]++,fr[ve[i][a]]=1;
			int now=0;
			for(int a=1;a<=k[i];a++)now+=cnt[ve[i][a]]<=1;
			while(j<=i&&now<k[i]){
				for(int a=1;a<=k[j];a++){
					if(fr[ve[j][a]])now-=cnt[ve[j][a]]<=1;
					cnt[ve[j][a]]--;
					if(fr[ve[j][a]])now+=cnt[ve[j][a]]<=1;
				}
				j++;
			}
			l[i]=j;
			for(int a=1;a<=k[i];a++)fr[ve[i][a]]=0;
		}
		int lst1=0;
		for(int i=1;i<=n;i++){
			if(k[i]==0){
				f[i]=1,s[i]=s[i-1]+1,lst1=i;
				continue;
			}
			int ll=max(1ll,l[i-1]);
			if(ll<=lst1){
				int now=(ll==1)?s[lst1-1]:(s[lst1-1]-s[ll-2]);
				if(now)f[i]=1;
			}
			for(int j=1;j<=k[i];j++){
				if(ll<=lst[ve[i][j]]){
					int now=(ll==1)?s[lst[ve[i][j]]-1]:(s[lst[ve[i][j]]-1]-s[ll-2]);
					if(now)f[i]=1;
				}
			}
			s[i]=s[i-1]+f[i];
			for(int j=1;j<=k[i];j++)lst[ve[i][j]]=i;
		}
		int ans=0,flag=0,ss=0;
		for(int i=n;i;i--){
			int now=1;
			for(int j=1;j<=k[i];j++)cntt[ve[i][j]]++,now&=cntt[ve[i][j]]<=1,ss++;
			if(!now)break;
			flag|=k[i]==0;
			if(f[i-1])ans=max(ans,flag?m:ss);
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++)for(int j=1;j<=k[i];j++)lst[ve[i][j]]=cnt[ve[i][j]]=cntt[ve[i][j]]=0;
	}
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

注意到最后会影响答案的一定是一段后缀，那么我们可以考虑求出不会出现清空的**最大一段后缀**，即找到一个最前面的位置 $pos$，使得 $[1,pos]$ 被清空且 $[pos+1,n]$ 不会有已知集合出现被清空的情况。这时如果 $[pos+1,n]$ 中有 $k_i=0$ 的集合存在，那么一定可以让答案为 $m$，否则答案就是这段区间内所有集合大小之和。

如何求出这个 $pos$ 呢？考虑什么时候有**可能会**恰好在 $i$ 位置清空。第一种情况，$i$ 集合内的某个数在 $[pos+1,i-1]$ 中出现过，且最晚的出现位置为 $mx$。因为这时候它并没有被清空，所以一定会在 $i$ 位置满足清空的条件。第二种情况，$[pos+1,i]$ 中有 $k_i=0$ 的集合，那么一定可以构造一种方案来清空，例如在其中填入 $i$ 集合中的任意一个数。求完后 $pos$ 可以实时更新，因为要让 $pos$ 尽量小，所以对于第一种不得不清空的情况，$pos$ 的最小值就是 $mx$，如果比 $mx$ 还靠后那显然不优。而如果此时 $pos$ 移到的位置不可能被清空，那只能继续往后移，直到找到一个可能可以被清空的位置。

按上述方法模拟一遍即可，总时间复杂度 $O(n)$。

---

## 作者：daniEl_lElE (赞：0)

首先注意到最后 $S$ 中仅包含一段后缀中的元素，且后缀中任意两个元素不相同。

考虑 $dp_i$ 表示 $[1,i]$ 是否可以被消除。不难发现若 $dp_i=1$，可以转移到的 $j$ 是一段区间，有两种情况：

* $[i+1,j]$ 会被消除，且其中没有 $k_i=0$。那么 $dp_i$ 只能转移到 $dp_j$。
* 不考虑 $k_l=0$ 的情况下，$[i+1,j]$ 会被消除，且第一个 $l>i,k_l=0$ 满足 $l\leq j$。那么 $dp_i$ 可以转移到 $[l,j]$。

$j$ 可以双指针求，转移可以前缀和优化。

接下来从后往前扫，同样分成上面两种情况。

* $dp_i=1$，$[i+1,n]$ 不会被消除，不存在 $i<l\leq n$ 使得 $k_l=0$。那么会给答案贡献 $|S_{[i+1,n]}|$ 的一种方案。
* $dp_i=1$，$[i+1,n]$ 不会被消除，存在 $i<l\leq n$ 使得 $k_l=0$。那么会给答案贡献 $m$ 的一种方案。

总复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k[200005];
vector<int> vc[200005];
int pre[200005],aim[200005],ins[200005],cnt,nxt0[200005];
void solve(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>k[i];
		vc[i].clear();
		for(int j=1;j<=k[i];j++){
			int v; cin>>v; vc[i].push_back(v);
		}
	}
	nxt0[n+1]=n+1;
	for(int i=n;i>=1;i--){
		nxt0[i]=nxt0[i+1];
		if(k[i+1]==0) nxt0[i]=i+1;
	}
	for(int i=0;i<=n+2;i++) pre[i]=0;
	pre[0]=1,pre[1]=-1;
	int r=0;
	for(auto v:vc[1]) aim[v]=1; cnt=0;
	for(int i=1;i<=n;i++){
//		cout<<i<<" ";
		while(cnt==0&&r!=n){
			r++;
			for(auto v:vc[r]) ins[v]=1,aim[v]=0;
			if(r==n) break;
			for(auto v:vc[r+1]) aim[v]=1,cnt+=aim[v]&ins[v];
		}
		pre[i]+=pre[i-1];
		if(pre[i-1]>0){
//			cout<<nxt0[i]<<" "<<r<<"\n";
			if(nxt0[i]<=r) pre[nxt0[i]]++,pre[r+2]--;
			if(k[i]>0) pre[r+1]++,pre[r+2]--;
			else pre[i+1]++,pre[r+2]--;
		}
		for(auto v:vc[i]) cnt-=aim[v]&ins[v],ins[v]=0;
	}
	for(int i=1;i<=n;i++) for(auto v:vc[i]) aim[v]=ins[v]=0;
//	for(int i=0;i<=n;i++) cout<<pre[i]<<" ";
	int vis0=0;
	int maxv=0,tag=0,cnt=0;
	for(int i=n;i>=1;i--){
		for(auto v:vc[i]){
			if(ins[v]) tag=1;
			ins[v]=1,cnt++;
		}
		if(tag) break;
		if(!k[i]) vis0=1;
		if(pre[i-1]>0&&vis0) maxv=m;
		else if(pre[i-1]>0) maxv=max(maxv,cnt);
	}
	for(int i=1;i<=n;i++) for(auto v:vc[i]) aim[v]=ins[v]=0;
	cout<<maxv<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int t; cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Kevin090228 (赞：0)

## Misha and Apples

我们只需要知道最后一次清空在第几次操作时候，就可以轻松求出答案了，下面考虑怎么求出每次操作后可不可能将集合清空。

考虑上一次清空为 $x$ 时，下一次清空可能在什么地方。设 $f(x)$ 表示最小的 $y$，满足 $[x+1,y]$ 的集合中有重复元素，则显然下一次清空的位置一定 $\leq f(x)$，因为在位置 $f(x)$ 必然会出现相同元素导致清空。设 $g(x)$ 表示 $x$ 之后的第一个为空集的 $y$，则从 $g(x)$ 位置开始就可以一定做到清空了，所以可以清空的区间为 $[\min\{f(x),g(x)\},f(x)]$。

随便写一个玩意转移一下这个东西即可。最后求答案的时候，我们需要找到所有满足可以在第 $x$ 次操作清空，且可以在到操作结束之前都不清空的 $x$，然后分 $x+1$ 到结尾的过程中有没有空集讨论答案即可。

$f(x),g(x)$ 的计算显然可以 $O(\sum k_i)$，转移可以 $O(n)$，统计答案只需倒序枚举每个操作，同样可以 $O(n)$。

于是我们就可以通过本题。



---

## 作者：Nuisdete (赞：0)

首先有一种清零的方式是在一个 $0$ 点买 $a$ 苹果，然后在第 $x$ 个商店中有 $a$ 苹果，这样就可以在第 $x$ 个商店这个地方清零了，能卡掉很多假做法。

我们考虑最后剩的苹果一定是原序列的一个后缀 $i$，并在 $i - 1$ 这个商店清零，同时，如果有两个商店同时有 $a$ 苹果，那么这两个商店一定不能同时选择。

那么我们找到 $lstS$ 表示最靠后的有同种苹果的商店（编号靠前的那个），那么答案后缀一定在 $lstS + 1 \sim n$ （或者为空）。

那么如果我们枚举 $lstS \sim n$，找到最先能够清空的那个商店不就找到答案后缀了？

现在问题变为求能否在每个商店清空背包。

这个也很简单，只需要找到最近的和它有着至少一种相同苹果的商店 $i$（或者是 $0$ 商店），然后在它之前找到最近的一个商店 $j$ 能够清零，并且在 $j + 1 \sim$ 当前枚举到的商店之间没有两个有着同种苹果的商店就行了，`st` 表维护区间最靠后的前驱再用树状数组线段树啥的维护区间是否有能清零的商店就行了。

Code：[https://codeforces.com/problemset/submission/1819/202796663](https://codeforces.com/problemset/submission/1819/202796663)。

---

