# Best Pair

## 题目描述

You are given an array $ a $ of length $ n $ . Let $ cnt_x $ be the number of elements from the array which are equal to $ x $ . Let's also define $ f(x, y) $ as $ (cnt_x + cnt_y) \cdot (x + y) $ .

Also you are given $ m $ bad pairs $ (x_i, y_i) $ . Note that if $ (x, y) $ is a bad pair, then $ (y, x) $ is also bad.

Your task is to find the maximum value of $ f(u, v) $ over all pairs $ (u, v) $ , such that $ u \neq v $ , that this pair is not bad, and also that $ u $ and $ v $ each occur in the array $ a $ . It is guaranteed that such a pair exists.

## 说明/提示

In the first test case $ 3 $ , $ 6 $ , $ 7 $ occur in the array.

- $ f(3, 6) = (cnt_3 + cnt_6) \cdot (3 + 6) = (3 + 2) \cdot (3 + 6) = 45 $ . But $ (3, 6) $ is bad so we ignore it.
- $ f(3, 7) = (cnt_3 + cnt_7) \cdot (3 + 7) = (3 + 1) \cdot (3 + 7) = 40 $ .
- $ f(6, 7) = (cnt_6 + cnt_7) \cdot (6 + 7) = (2 + 1) \cdot (6 + 7) = 39 $ .

The answer to the problem is $ \max(40, 39) = 40 $ .

## 样例 #1

### 输入

```
3
6 1
6 3 6 7 3 3
3 6
2 0
3 4
7 4
1 2 2 3 1 5 1
1 5
3 5
1 3
2 5```

### 输出

```
40
14
15```

# 题解

## 作者：XL4453 (赞：5)

### $\text{Difficulty : 2100}$
---
### 解题思路：

本题最关键的性质就是 $cnt$ 最多只会有 $\sqrt n$ 种取值，可以从这个角度入手。

枚举 $x$ 和 $y$ 的 $cnt$，然后在这些相等的 $cnt$ 中从大到小枚举所有的取值，加一个最优性剪纸就可以了。

---
### 复杂度分析：

枚举两种 $cnt$ 的取值的复杂度是 $O(n)$ 的，内层第二层循环一旦进行一次更新之后就直接退出，第一层循环只要进行一次更新就不可能在那个位置向后的位置更新，所以总访问次数是 $O(m)$ 的。处理的总复杂度为 $O(m+n)$，程序总复杂度 $O(n\log n)$，瓶颈在排序。

---
### 代码：

```cpp
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=300005;
int n,m,a[MAXN],T,x,y,ans;
vector <int> v[MAXN],rec;
map <pair<int,int>,bool> s;
map <int,int> cnt;
bool cmd(int x,int y){return x>y;}
void init(){
	ans=0;
	for(int i=0;i<rec.size();i++)v[rec[i]].clear();
	rec.clear();
	s.clear();
	cnt.clear();
	n=m=0;
}
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%I64d",&a[i]);
			cnt[a[i]]++;
		}
		for(int i=1;i<=n;i++){
			if(cnt[a[i]]!=0){
				v[cnt[a[i]]].push_back(a[i]);
				if(v[cnt[a[i]]].size()==1)rec.push_back(cnt[a[i]]);
				cnt[a[i]]=0;
			}
		}
		for(int i=0;i<rec.size();i++)sort(v[rec[i]].begin(),v[rec[i]].end(),cmd);
		
		for(int i=1;i<=m;i++){
			scanf("%I64d%I64d",&x,&y);
			s[make_pair(x,y)]=1;
			s[make_pair(y,x)]=1;
		}
		
		for(int i=0;i<rec.size();i++)
		for(int j=i;j<rec.size();j++){
			for(int k=0;k<v[rec[i]].size();k++)
			for(int l=0;l<v[rec[j]].size();l++){
				x=v[rec[i]][k];
				y=v[rec[j]][l];
				if(x==y)continue;
				if((rec[i]+rec[j])*(x+y)<ans)break;
				if(s[make_pair(x,y)]==0){
					ans=(rec[i]+rec[j])*(x+y);
					break;
				}
			}
		}
		printf("%I64d\n",ans);
		init();
	}
	return 0;
}
```


---

## 作者：_ajthreac_ (赞：4)

## 翻译
给定一个长为 $n$ 的数列 $a$，设 $cnt_x$ 为 $x$ 出现的次数，对 $a$ 中出现过的任意两个不同数 $x,y$ 定义 $f_{x,y}=(cnt_x+cnt_y)(x+y)$。现在有 $m$ 个无序不合法对 $(x_i,y_i)$，求所有合法对中，$f_{x,y}$ 的最大值。
## 题解
此题利用均摊复杂度，使一个看起来像暴力的算法通过。

考虑最暴力的做法：我们枚举 $x$ 和 $y$，然后计算它们的贡献，不合法对用 `std::set` 之类的存下来查找。

这个东西复杂度是爆炸的，我们考虑如何优化。

注意到所有 $cnt_x$ 加起来是 $n$（废话），考虑先枚举 $cnt_y\le cnt_x$ 再枚举 $y$。容易发现这样和上面的枚举方式等价，并且外面两层均摊 $O(n)$。

再考虑内层的复杂度，我们从大到小枚举 $y$，这样只有 $(x,y)$ 不合法或 $x=y$ 时会跳过，否则直接更新答案跳出循环。显然每个不合法对最多被判断一次，$x=y$ 最多成立 $n$ 次，那么内层均摊是 $O(n\log n)$ 的。
## 代码
核心代码如下：
```cpp
const int N=400010;
int T,n,m,a[N],t[N],cnt[N];
signed main(){
  Read(T);
  while(T--){
    memset(cnt,0,sizeof cnt);
    Read(n),Read(m);set<pii > s;
    for(int i=1;i<=n;i++)Read(a[i]),t[i]=a[i];
    sort(t+1,t+1+n);int tmp=unique(t+1,t+1+n)-t-1;
    int mx=0;
    for(int i=1;i<=n;i++){
      a[i]=lower_bound(t+1,t+1+tmp,a[i])-t;
      cnt[a[i]]++,mx=max(mx,cnt[a[i]]);
    }
    vector<vector<int> > ps(mx+1);
    for(int i=1;i<=tmp;i++)ps[cnt[i]].pub(i);
    for(int i=1,u,v;i<=m;i++){
      Read(u),Read(v),s.insert(mp(min(u,v),max(u,v)));
    }
    int ans=0;
    for(int x=1;x<=tmp;x++){
      for(int j=1;j<=cnt[x];j++){//cnt_y
        for(int o=(int)ps[j].size()-1;~o;o--){
          int y=ps[j][o];
          if(y==x)continue;
          if(s.find(mp(min(t[x],t[y]),\
          max(t[x],t[y])))!=s.end())continue;
          ans=max(ans,(t[x]+t[y])*(cnt[x]+j));
          break;
        }
      }
    }
    printf("%lld\n",ans);
  }
  KafuuChino HotoKokoa
}
```
我的实现有一个很重要的细节，就是在枚举 $y$ 时，`ps[j]` 可能是空的，所以需要将 `ps[j].size()` 强转成 `int` 防止无符号整数溢出。

---

## 作者：jiangxinyang2012 (赞：2)

首先，数字有重复，我们可以先去重，并统计每个数字出现的次数。

接着，用哈希表记录不合法情况。

最后，想办法解决其他问题。

不难想到暴力方法：枚举第一个数和第二个数，暴力计算最优值。

枚举的优化：改变枚举对象，数字种类至多 $n$ 个，但出现次数约根号种。如果已知第一个数字和第二个数字的次数，那么只需要选择该次数中数值最大的即可。

现在问题是，有 $m$ 个搭配是不合法的，最大值可能不合法，此时我们只能继续往下找。由于不合法情况共m种，所以往下走的次数至多m次。

优化：因为还需要套哈希表、map 等数据结构，所以容易超时。我们还可以去重，枚举 a 和 b 跟 b 和 a 是等价的，如果我们枚举的是出现次数多的数字，那么另一个数字的出现次数不大于第一个数字的出现次数，从而实现线性枚举，因为次数之和为 $n$。

排序可以使用索引排序，vector 等，因为排序带 log，所以就不手写哈希表了，模数取不好还可能被卡呢！

---

## 作者：HoshizoraZ (赞：2)

看到关于出现次数的题目，可以考虑根号分治。

将所有数分为出现次数分别在 $[1,\sqrt{n}]$ 和 $(\sqrt{n},n]$ 的两部分。

- 对于 $cnt_x>\sqrt{n}$ 的数 $x$，这样的数不超过 $\sqrt{n}$ 个，可以把每个 $x$ 枚举 $y=1 \sim n$，找到与其匹配合法的数 $y$ 并进行计算。

如果查某个数字 $a$ 在序列中出现次数直接用 `std::map` 存，那这一部分的时间复杂度是 $\mathcal{O}(n \sqrt{n} \log n)$。

- 对于剩下的情况，即 $cnt_x,cnt_y \le \sqrt{n}$ 时，考虑改变枚举对象。

我们可以开 $\lfloor\sqrt{n}\rfloor$ 个不定长数组 $v$，$v_i$ 记录所有满足 $cnt_x=i$ 的 $x$。

假设确定了 $x,cnt_x,cnt_y$，那么只要 $y$ 越大，$(x+y)(cnt_x+cnt_y)$ 就越大。

所以对于每一个 $1 \le i \le \lfloor\sqrt{n}\rfloor$，将 $v_i$ 内数字**从大到小排序**。

我们先枚举一个数 $x$，再枚举另一个数的出现次数 $cnt$。对于某个 $cnt$，按照顺序枚举数组，如果找到第一个与 $x$ 能匹配的数 $y$，就**计算贡献并选择较大答案**，并**直接退出枚举**。

直接退出枚举的原因是其余三个量**不变**的时候，$y$ 变小了，答案显然不优。

好了，现在让我们看下这步的时间复杂度吧。

如果所有不同的数可以互相匹配（即 $m=0$），那么每个 $x$ 只会找 $\sqrt{n}$ 个数。

考虑加上不合法匹配的影响。由于 $1 \sim n$ 的所有 $x$ 间只有 $2m$ 组不合法匹配，所以上述步骤可能会加上 $2m$ 次的额外错误枚举。

如果还是用 `map` 判断不合法数对，那么时间复杂度是 $\mathcal{O}((n \sqrt{n}+m) \log n)$。

------------

但是这题的 $n,m \le 3 \times 10^5$，上面这个复杂度看着就过不去，何况 `map` 常数巨大。

所以还是要抓住题目的限制条件分析并做一些优化：

- 基础常数优化，例如降低 `map` 的插入、调用次数。
- 记录完每个数的出现次数后，将序列排序，并去重。

排序可以减少一半的枚举量，而去重的意义很大。如果 $cnt_x>1$ 的数很多，那去重后 $n$ 就会大幅度变小。

反之，如果去重得少，那 $cnt_x>\sqrt{n}$ 的数 $x$ 更少，枚举量永远无法到达复杂度理论最大值。

因此这个时间复杂度是远跑不满的，如果还是不放心，可以自己造大数据跑跑。

-----------

今天上午发现做法 `MLE on test 77` 了，发现是 `map` 的问题。因为 `map` 当数组用，查询的时候 `map` 内部会加入新的节点，从而浪费大量空间，导致 MLE。

如果只想查询某个数是否存在，那么建议使用 `.find()` 或 `.count()`。当然也可以选择写更快的哈希。

下面贴上代码：

```cpp
int t, n, m, a[N], sz, lim, len;
int seq[N], val[N], vis[N];
map <int, int> cnt;
map <pair <int, int>, int> M;
vector <int> v[710];
ll ans;
 
bool cmp(int a, int b){
	return a > b;
}
inline ll max(ll a, ll b){
	return a > b ? a : b;
}
inline int read(){
	int num = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') num = num * 10 + c - '0', c = getchar();
	return num; 
}
 
int main(){	
	scanf("%d", &t);
	while(t--){
		n = read(), m = read(), cnt.clear(), M.clear(), lim = (int)sqrt(n);
		for(int i = 1; i <= n; i++)
			a[i] = read(), cnt[a[i]]++;
		sort(a + 1, a + n + 1), n = unique(a + 1, a + n + 1) - a - 1, sz = 0;	// 去重
		for(int i = 1; i <= n; i++){
			if(cnt[a[i]] >= lim)
				seq[++sz] = a[i];
			val[i] = cnt[a[i]];
		}
		for(int i = 1, u, v; i <= m; i++)
			u = read(), v = read(), M[make_pair(u, v)] = 1;
		ans = 0;
		for(int i = 1, num; i <= sz; i++){
			num = cnt[seq[i]];
			for(int j = 1; j <= n; j++)
				if(seq[i] != a[j] && !M.count(make_pair(seq[i], a[j])) && !M.count(make_pair(a[j], seq[i])))
					ans = max(ans, 1ll * (num + val[j]) * (a[j] + seq[i]));
		}
		for(int i = 1; i <= lim; i++) 
			v[i].clear();
		for(int i = 1, num; i <= n; i++){
			num = cnt[a[i]];
			if(num < lim) v[num].push_back(a[i]);
		}
		for(int i = 1; i <= lim; i++)
			sort(v[i].begin(), v[i].end(), cmp);
		for(int i = 1, num; i <= n; i++){
			num = cnt[a[i]];
			if(num < lim)
				for(int j = lim - 1; j >= 1; j--)
					for(auto k : v[j]){
						if(k <= a[i]) break;		// 小剪枝，只枚举比自己大的数
						if(!M.count(make_pair(a[i], k))){
							ans = max(ans, 1ll * (num + j) * (k + a[i]));
							break;
						}
					}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

> CF1637E Best Pair

高妙题，比赛的时候把我送走了。

考虑直接枚举 $x$ 和 $\leq cnt_x$ 的所有 $cnt_y$（这一步线性，因为 $\sum cnt_x = n$），此时 $x, cnt_x, cnt_y$ 均确定。从大到小检查 $x$ 和最大的出现次数为 $cnt_y$ 的 $y$ 是否是坏二元组。若是，则找第二大的，直到所有等于 $cnt_y$ 的 $y$ 被遍历完，若不是，说明再往下找一定不会优于当前的 $(x + y)(cnt_x + cnt_y)$，因为对于该式子仅有 $y$ 变小。

我们最多会用 $n + m$ 个二元组 $(x, y)$ 更新答案（最多会有 $m$ 次不合法情况，第一次合法就退出了），故总时间复杂度 $\mathcal{O}((n + m)\log n)$。[代码](https://codeforces.ml/contest/1637/submission/146186112)。

---

## 作者：CQ_Bab (赞：1)

# 思路
~~NB 题~~。

首先这道题你发现如果你知道了 $cnt_x,y$ 那么你就可以做了，因为限制一共 $m$ 跳所以按 $cnt_i=cnt_x$ 的 $i$ 从大往小排序然后暴力即可，那么这里我们会觉得是 $n^2$ 的，所以就要用一个结论，对于一个序列 $a$ 其不同的出现次数最多只有 $\sqrt{n}$ 种毕竟假设从 $1\sim i$ 都出现过总的次数就是 $i\times (i+1)\div 2$ 那么就可以发现我们只需要将次数离散化以下然后直接暴力跑的时间复杂度是对的，时间复杂度 $O(n\times \sqrt{n})$。
# 代码
细节见代码。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
il void print(long long x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
}
int T=1;
int n,m;
const int N=3e5+10;
int a[N];
int mp[N],tot,ma[N],b[N];
int cnt[N],idx,is[N],vis[N],vv[N];
vector<int>v[N];
vector<int>ve[N];
il bool cmp(int x,int y) {
	return a[x]<a[y];
}
int mm;
il int get(int x) {
//	cout<<mm<<endl;
	return lower_bound(a+1,a+1+mm,x)-a;
}
void solve() {
	in(n),in(m);
	int x;
	in(x);
	a[1]=x;
	b[1]=a[1];
	rep(i,2,n) in(a[i]),b[i]=a[i];
	sort(a+1,a+1+n);
	mm=unique(a+1,a+1+n)-a-1;
	rep(i,1,n) {
		b[i]=lower_bound(a+1,a+1+mm,b[i])-a;
		cnt[b[i]]++;
	}
	rep(i,1,n) vv[i]=cnt[b[i]];
	sort(vv+1,vv+1+n);
	int mm1=unique(vv+1,vv+1+n)-vv-1;
	rep(i,1,n) {
		if(!mp[cnt[b[i]]]) {
			mp[cnt[b[i]]]=lower_bound(vv+1,vv+1+mm1,cnt[b[i]])-vv;
			tot++;
		}
		v[mp[cnt[b[i]]]].pb(b[i]);
	}
	rep(i,1,tot) stable_sort(v[i].begin(),v[i].end());
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		ve[get(x)].pb(get(y));
		ve[get(y)].pb(get(x));
	}
	long long res=0;
	idx=mm;
	rep(y,1,idx) {
		for(auto to:ve[y]) {
			vis[to]=1;
		}
		rep(i,1,tot) {
			rep1(x,v[i].size()-1,0) {
				if(1!=vis[v[i][x]]&&y!=v[i][x]) {
					res=max(res,1ll*(vv[i]+cnt[y])*(a[y]+a[v[i][x]]));
					break;
				}
			}
		}
		for(auto to:ve[y]) vis[to]=false;
	}
	print(res);
	putchar('\n');
}
fire main() {
	in(T);
	while(T--) {
		solve();
		if(T) {
			rep(i,1,n) mp[i]=false,vv[i]=false;
			rep(i,1,mm) cnt[i]=false;
			rep(i,1,tot) v[i].clear();
			rep(i,1,idx) ve[i].clear();
			tot=idx=false;
		}
	}
	return false;
}
```

---

## 作者：rsg26 (赞：1)

这是一个不算根号分治（？）但是带根号的做法。。。

**做法**

$\text{Part 1}$ 预处理

* 将 $a$ 数组离散化
* 记录有多少种不同的 $cnt$ 值，并把它们都放到一个 $\texttt{vector}$ 中
* 对于每一个 $cnt$ 值 $y$ ，如果 $cnt_x = y$ ，那么将 $x$ 放到 $y$ 对应的 $\texttt{vector}$ 当中，并将这里每个 $\texttt{vector}$ 排序

一言以蔽之，就是为下面统计答案做了些准备。

$\text{Part 2}$ 统计答案

考虑先枚举 $x$ ，此时我们知道了 $cnt_x$ ，然后我们枚举 $cnt_y$ ，显然我们需要的就是 $y$ 最大。如何得到最大的 $y$ 呢，这就需要预处理的 $cnt$ 值为 $cnt_y$ 对应的 $\texttt{vector}$ 了。如果没有 $\texttt{bad pair}$ 的话，问题将变为直接找 $\texttt{vector}$ 中的最大值，那么我们灵机一动：把 $\texttt{bad pair}$ 打个记号不就行了吗，找最大值时直接略过。

伪代码大概长这样

```
for i 在 [1, n] 中
    for j 是一个 cnt 值
       for k 是 j 对应的 vector 中的值（从大到小）
           if (i, k) 不是 bad pair 且 i != k
               ans 更新
```

$\text{Part 3}$ 复杂度证明

第一眼看上去，这像是一个 $\mathcal{O}(n ^ 3)$ 的，毕竟有 $3$ 重循环嘛，但是我们想想，第二重循环枚举的 $cnt$ 值，最多只有 $\mathcal{O}(\sqrt n)$ 个！！！而第三重循环枚举的 $k$ 的次数的和，大概是 $\mathcal{O}(m)$ 的。所以总复杂度是 $\mathcal{O}(n\sqrt n)$ 。

这个复杂度实在有点烂，但能过，想学习更好的做法请移步其它题解。

$\text{Part 4}$ 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int NR = 3e5 + 5;

int T, n, m, mx, a[NR], b[NR], c[NR], cnt[NR], vis[NR], viss[NR];
long long ans;
vector < int > diffcnt, bad[NR];
vector < pair < int, int > > cntisx[NR];

inline int read() {
    register int x = 0; register char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
    return x;
}

inline void solve() {
    n = read(), m = read(), ans = 0; 
    for (int i = 1; i <= n; ++i) a[i] = read(), b[i] = a[i], cnt[i] = 0, viss[i] = 0, vis[i] = 0, bad[i].clear(), cntisx[i].clear();
    sort(a + 1, a + n + 1), sort(b + 1, b + n + 1), diffcnt.clear();
    for (int i = 1; i <= n; ++i) c[i] = lower_bound(b + 1, b + n + 1, a[i]) - b, cnt[c[i]] ++;
    for (int i = 1; i <= n; ++i) {
        if (!vis[cnt[c[i]]]) diffcnt.push_back(cnt[c[i]]), vis[cnt[c[i]]] = 1;
        cntisx[cnt[c[i]]].push_back(make_pair(a[i], c[i]));
    }
    for (auto x : diffcnt) sort(cntisx[x].begin(), cntisx[x].end());
    for (int i = 1; i <= m; ++i) {
        int x, y; x = read(), y = read();
        bad[lower_bound(b + 1, b + n + 1, x) - b].push_back(lower_bound(b + 1, b + n + 1, y) - b);
        bad[lower_bound(b + 1, b + n + 1, y) - b].push_back(lower_bound(b + 1, b + n + 1, x) - b);
    }
    for (int i = 1; i <= n; ++i) vis[i] = 0, sort(bad[i].begin(), bad[i].end());
    for (int i = 1; i <= n; ++i) {
        if (vis[c[i]]) continue;
        vis[c[i]] = 1;
        for (auto j : bad[c[i]]) viss[j] = 1;
        for (auto j : diffcnt)
            for (int k = cntisx[j].size() - 1; k >= 0; --k)
                if (!viss[cntisx[j][k].second] && cntisx[j][k].first != a[i]) {
                    ans = max(ans, 1ll * (a[i] + cntisx[j][k].first) * (cnt[c[i]] + j));
                    break;
                }
        for (auto j : bad[c[i]]) viss[j] = 0;
    }
    printf("%lld\n", ans);
}

int main() {
    T = read();
    while (T --) solve();
    return 0;
}
```

---

## 作者：include_BM (赞：1)

根号分治（**这不是这道题最简单的做法**）。

首先需要离散化（也可以用 `map`/`unordered_map` 代替数组），下文均为离散化之后的操作。

将所有的数分成两个集合：

1. $cnt[x]\le\sqrt{n}$，这样的 $x$ 数量较多，但 $cnt[x]$ 很小，处理时可以考虑直接枚举 $cnt[x]$ 而不是 $x$。

2. $cnt[x]>\sqrt{n}$，这些 $x$ 的 $cnt[x]$ 较大，但这种 $x$ 的数量很少（$<\sqrt{n}$），处理时直接枚举 $x$ 即可。

回到问题上，题目要 求 $(cnt[x]+cnt[y])(x+y)$ 最大值，分别考虑 $x,y$ 出自上述哪个集合（注意特判坏的数对）：

注：$t$ 表示上述第二个集合，$vc[i](i\le\sqrt{n})$ 表示所有满足 $cnt[x]=i$ 的 $x$ 构成的集合，$mp[x][y]=1$ 表示数对 $(x,y)$ 是坏的（如题），$b[i]$ 为离散化数组，它们在代码中的定义如下：

```cpp
long long b[N];
//乘起来会超过 int 的最大范围，为了偷懒全部开的 long long。
vector<int> vc[N],t;
//找出所有 x 后按降序排序。<- 注意这点以后会用。
unordered_map<int,bool> mp[N];
//mp[x].find(y)==mp[x].end() 表示 mp[x] 中不存在 y，即 mp[x][y]!=1。
```

1. $x,y$ 均出自上述第二个集合，由于这类数数量很少，直接枚举 $x,y$ 即可。

```cpp
for(auto x:t)
    for(auto y:t) if(x!=y&&mp[x].find(y)==mp[x].end()) ans=max(ans,(cnt[x]+cnt[y])*(b[x]+b[y]));
```

2. $x,y$ 均出自上述第一个集合，由于这类数 $cnt$ 很小，直接枚举 $cnt[x],cnt[y]$ 即可。

```cpp
for(int i=1;i<=sq;++i)//cnt[x]
    for(int j=i;j<=sq;++j)//cnt[y]
        for(auto x:vc[i])
            for(auto y:vc[j])
                if(x!=y&&mp[x].find(y)==mp[x].end()){ans=max(ans,(cnt[x]+cnt[y])*(b[x]+b[y]));break;}
//由于在 cnt[x],cnt[y],x 一定时希望 y 尽可能大，而 vc 已按降序排序，故找到一组可行数对直接 break。
//第 1,2 个循环总执行次数=n。
//每组坏的数对在第 3,4 个循环中最多出现两次，又因找到一组可行数对直接退出，这两个循环最多把所有坏的数对遍历两次，即总执行次数<=2*m，符合时间要求。
```

3. $x$ 出自上述第二个集合，$y$ 出自上述第一个集合，枚举 $x,cnt[y]$ 即可。

```cpp
for(auto x:t)
    for(int i=1;i<=sq;++i)//cnt[y]
        for(auto y:vc[i])
            if(x!=y&&mp[x].find(y)==mp[x].end()){ans=max(ans,(cnt[x]+cnt[y])*(b[x]+b[y]));break;}
//同上
```

最后输出 ans 即可，完整 **参考** 代码 [$\texttt{submission}$](https://codeforces.com/contest/1637/submission/146138192)。

---

## 作者：5ab_juruo (赞：1)

给定序列 $a$，记 $x$ 在 $a$ 中的出现次数为 $cnt_x$，令 $f(x,y)=(cnt_x+cnt_y)(x+y)$，同时给出 $m$ 对数 $(x_i,y_i)$，求不在这 $m$ 对数中的 $(x,y)$ 能得到的最大的 $f(x,y)$。

---

orz @zbs140。

注意到 $cnt$ 最多有 $O(\sqrt{n})$ 种取值，所以根据 $cnt$ 开桶，枚举 $cnt_x$，$cnt_y$。在每个桶中根据数值倒序排序，然后枚举。如果是不能选的就切到下一个。如果已经比当前答案大就退出。

显然外层枚举是 $O(n)$ 的，内层总共会枚举 $O(m)$ 次，核心部分是线性的。

---

如果没有 $cnt$ 的性质这道题还能做吗……

```cpp
/* name: 1637E
 * author: 5ab
 * created at: 22-02-12 23:30
 */
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int max_n = 300000;

int a[max_n], pa[max_n], b[max_n], cnt[max_n], bl;
vector<int> cnts[max_n+1], cid;
set<pair<int, int>> st;

inline int s(int x) { return lower_bound(b, b + bl, x) - b; }
inline bool cmp(int x, int y) { return x > y; }
inline void chmax(ll& a, ll b) { if (a < b) a = b; }

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int cas, n, m;
	ll ans;
	
	cin >> cas;
	while (cas--)
	{
		cin >> n >> m, st.clear(), cid.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
			b[i] = a[i];
		}
		sort(b, b + n);
		bl = unique(b, b + n) - b;
		
		for (int i = 0, x, y; i < m; i++)
		{
			cin >> x >> y;
			st.emplace(x, y);
		}
		
		for (int i = 0; i < n; i++)
			cnt[pa[i]=s(a[i])]++;
		for (int i = 0; i < n; i++)
			if (cnt[pa[i]] > 0)
			{
				if (!cnts[cnt[pa[i]]].size())
					cid.push_back(cnt[pa[i]]);
				cnts[cnt[pa[i]]].push_back(a[i]);
				cnt[pa[i]] *= -1;
			}
		
		ans = 0;
		sort(cid.begin(), cid.end(), cmp);
		
		for (int _i = 0, i = cid[0]; _i < cid.size(); _i++, i = cid[_i])
		{
			sort(cnts[i].begin(), cnts[i].end(), cmp);
			for (int _j = 0, j = cid[0]; _j <= _i; _j++, j = cid[_j])
			{
				for (int _k = 0, k = cnts[i][_k]; _k < cnts[i].size(); _k++, k = cnts[i][_k])
					for (int _l = 0, l = cnts[j][_l]; _l < cnts[j].size(); _l++, l = cnts[j][_l])
					{
						if (k == l)
							continue;
						if (1ll * (i + j) * (k + l) < ans)
							break;
						if (!st.count(make_pair(k, l)) && !st.count(make_pair(l, k)))
						{
							chmax(ans, 1ll * (i + j) * (k + l));
							break;
						}
					}
			}
		}
		
		cout << ans << endl;
		for (int i = 0; i < n; i++)
			if (cnt[pa[i]] < 0)
			{
				cnts[-cnt[pa[i]]].clear();
				cnt[pa[i]] = 0;
			}
	}
	
	return 0;
}
```

---

## 作者：苏联小渣 (赞：0)

看到出现次数，而且又是一个看起来不可直接维护的式子，不难想到根号分治。

- 结论：序列中出现次数 $>\sqrt{n}$ 的数，不超过 $\sqrt{n}$ 个。

证明显然。考虑先离散化，再把题目的限制存起来（对于每一个 $x$，开一个 vector 存不能选的数），然后枚举每一个 $x$，求出能使得答案最大化的 $y$。分两种情况：

第一种：$cnt_y>\sqrt{n}$。此时 $y$ 的取值不超过 $\sqrt{n}$ 种，把这些数存起来，然后对于 $x$，枚举这些 $y$ 使得 $(x,y)$ 合法，并统计答案。这部分复杂度 $O(n \sqrt{n})$。

第二种：$cnt_y\le \sqrt{n}$。此时变成了出现次数可枚举，所以我们就枚举出现次数。记录 $\sqrt{n}$ 个集合 $T_i$ 表示出现次数为 $i$ 的数的集合。假设我们枚举出现次数为 $i$，如果没有限制，那么将集合所有数从小到大排序，$T_{i,|T_i|}$ 就是该出现次数中能使答案最大的数。但是加上了限制，不过观察到限制总数是 $O(n)$ 级别的，也就是说，我们直接暴力找到该集合中，最大的 $y$ 使得 $(x,y)$ 合法就好了。用一个指针从头往前扫就行了。这部分复杂度 $O(n \sqrt{n})$。

总时间复杂度 $O(n \sqrt{n})$。

### Code：

````c++
#include <bits/stdc++.h>
using namespace std;
#define lc(x) x<<1
#define rc(x) x<<1|1
#define ll long long 
#define pi pair<int,int>
#define mk make_pair
#define fi first
#define se second 
#define pb push_back
int t, n, m, x, y, tot, lim, rev[300010], a[300010], cnt[300010], cur[300010];
ll ans;
vector <int> big, d[5010], cun[300010];
map <int, int> mp;
map <int, int> :: iterator it;
int main(){
	scanf ("%d", &t);
	while (t --){
		mp.clear();
		big.clear();
		tot = 0;
		ans = 0;
		scanf ("%d%d", &n, &m);
		lim = sqrt(n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			mp[a[i]] = 1;
		}
		for (it=mp.begin(); it!=mp.end(); it++){
			it->second = ++tot;
			rev[tot] = it->first;
			cnt[tot] = 0;
		}
		for (int i=1; i<=n; i++){
			a[i] = mp[a[i]];
			cnt[a[i]] ++;
		}
		for (int i=1; i<=lim; i++){
			d[i].clear();
		}
		for (int i=1; i<=tot; i++){
			cun[i].clear();
			if (cnt[i] > lim){
				big.pb(i);
			}
			else{
				d[cnt[i]].pb(i);
			}
		}
		for (int i=1; i<=lim; i++){
			sort (d[i].begin(), d[i].end());
		}
		for (int i=1; i<=m; i++){
			scanf ("%d%d", &x, &y);
			x = mp[x], y = mp[y];
			cun[x].pb(y), cun[y].pb(x);
		}
		for (int i=1; i<=tot; i++){
			sort (cun[i].begin(), cun[i].end());
			cur[i] = 1;
			for (int j=0; j<cun[i].size(); j++){
				cur[cun[i][j]] = 1;
			}
			for (int j=0; j<big.size(); j++){
				int id = big[j];
				if (!cur[id]) ans = max(ans, 1LL*(rev[id]+rev[i])*(cnt[id]+cnt[i]));
			}
			for (int j=1; j<=lim; j++){
				int mxp = d[j].size()-1;
				while (mxp >= 0 && cur[d[j][mxp]]) mxp --;
				if (mxp < 0) continue;
				ans = max(ans, 1LL*(rev[d[j][mxp]]+rev[i])*(cnt[d[j][mxp]]+cnt[i]));
			}
			for (int j=0; j<cun[i].size(); j++){
				cur[cun[i][j]] = 0;
			}
			cur[i] = 0;
		}
		printf ("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：ethan_zhou (赞：0)

### 题意

给一个长度为 n 的数组 a，定义 $cnt_x$ 为 x 这个值在 a 中的出现次数。定义函数 $f(x,y)=(cnt_x+cnt_y)(x+y)$（要求 $x < y$）。
还给出 m 个无序数对，称其为“坏数对”。

对于所有“不坏的”无序数对 $(x,y)$，求出 $f(x,y)$ 的最大值。

$n,m\le 3\times 10^5,a_i \le 10^9$

### 做法

我们先把 a 排个序，然后相同的一段缩成一个二元组 `{值,出现个数}`。

---

想想 m=0 咋做。想了半天，这个函数似乎没法硬维护，只能往性质方向想~~尤其是根号方面的~~。

考虑枚举一个 y，看看哪些 x 可能成为答案的：

- 如果出现 $x_1>x_2$，满足 $cnt_{x_1}\ge cnt_{x_2}$ 那 $x_2$ 必然没用

因此，所有可能成为答案的 x，都在 y-1 向左的 cnt 的单调栈上。

因此，我们只需要：

- 枚举右端点 y
    - 令 $x\gets y-1$
    - 不断进行直到 $x=0$：
        - 用 $f(x,y)$ 更新答案
        - $x\gets pre[x]$

内部每循环一次，$cnt_x$ 至少增加 1，而 $\sum cnt_i=n$，所以内部的循环最多不会跑超过 $\sqrt n$ 次，复杂度 $O(n\sqrt n)$。

---

而有 m 的时候，我们稍微改一下即可：

- 枚举右端点 y
    - 令 $x\gets y-1$
    - 不断进行直到 $x=0$：
        - 如果 $(x,y)$ 是好的
            - 用 $f(x,y)$ 更新答案
            - $x\gets pre[x]$
        - 否则
            - $x\gets x-1$

### 代码

考试的时候求前驱的部分写错了调半天没过，吐了

```cpp
const char nl = '\n';
const ll MXN = 1e6 + 5;
const ll INF = 1e18;

ll n, m, arr[MXN];
char str[MXN];
vec<ll> bad[MXN];

ll v[MXN], cnt[MXN], pre[MXN];
set<pi> last;
bool ban[MXN];
int main() {
    /* freopen("test.in", "r", stdin); */
    /* freopen("test.out", "w", stdout); */
    ios::sync_with_stdio(0);
    cin.tie(0);
    setp(6);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) {
            cin >> arr[i];
            bad[i].clear();
        }
        sort(arr + 1, arr + 1 + n);
        ll ind = 0;
        for (ll i = 1; i <= n; i++) {
            if (arr[i] != arr[i - 1]) {
                ++ind;
                v[ind] = arr[i];
                cnt[ind] = 0;
            }
            ++cnt[ind];
        }
        cnt[0]=INF;
        stack<ll> stk;
        stk.push(0);
        for (ll i = 1; i <= ind; i++) {
            while(cnt[i]>=cnt[stk.top()])stk.pop();
            pre[i] = stk.top();
            stk.push(i);
            /* cout << pre[i]; */
        }
        while (m--) {
            ll x, y;
            cin >> x >> y;
            x = lower_bound(v + 1, v + 1 + ind, x) - v;
            y = lower_bound(v + 1, v + 1 + ind, y) - v;
            if (x > y) swap(x, y);
            bad[y].push_back(x);
        }
        ll ir = ind, il, ans = 0;
        while (ir) {
            if (ban[ir])
                --ir;
            else {
                for (ll nx : bad[ir]) ban[nx] = 1;
                ll il = ir - 1;
                while (il) {
                    if (ban[il])
                        --il;
                    else {
                        ans = max(ans, (cnt[il] + cnt[ir]) * (v[il] + v[ir]));
                        il = pre[il];
                    }
                }
                for (ll nx : bad[ir]) ban[nx] = 0;
                --ir;
            }
        }
        cout << ans << nl;
    }
    return 0;
}
```


---

## 作者：pzc2004 (赞：0)

# Solution
首先思考没有 $m$ 的限制该怎么做。  
因为不同的 $cnt$ 最多只有 $\sqrt{n}$，设 $f_i$ 为 $cnt_x=i$ 的最大的 $x$，则 $ans=\max\limits_{j=1}^{i-1}(f_i+f_j)\times(i+j)$，复杂度 $O(N)$。  
加上 $m$ 的限制后同理，我们设 $p_i$ 为 $cnt_x=i$ 的数组，并对每个 $p_i$ 数组按照 $a_x$ 从大到小排序。然后我们对于每个 $i$，遍历比它小的 $j$，遍历 $p_i$，找到 $p_j$ 中最大的可以和当前的数组合的数，更新答案即可，若当前的数可以和 $p_j$ 中最大的数组合则停止遍历，具体见代码。  
每一条限制最多只会被遍历一次，复杂度 $O(N\log_2N)$，瓶颈在于排序。
# Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x= 0;
	char c= getchar();  
	while(!isdigit(c)) c= getchar();
	while(isdigit(c)) x= x * 10 + (c & 15), c= getchar();
}
#define N 300001
int n, m, t, a[N], b[N], cnt[N], nxt[N], l[N];
long long ans;
bool vis[N];
vector<int> p[N], k[N];
int main() {
	int T;
	read(T);
	while(T--) {
		read(n), read(m), ans= 0;
		for(int i= 1; i <= n; i++) read(a[i]), b[i]= a[i], p[i].clear(), k[i].clear(), cnt[i]= 0, l[i]= 0;
		sort(b + 1, b + n + 1), t= unique(b + 1, b + n + 1) - b - 1;
		for(int i= 1; i <= n; i++) a[i]= lower_bound(b + 1, b + t + 1, a[i]) - b, ++cnt[a[i]];
		for(int i= 1; i <= t; i++) k[cnt[i]].push_back(i);
		nxt[n]= n + 1;
		for(int i= n; i >= 1; i--) {
			if(!k[i].empty())
				k[i].push_back(0), nxt[i - 1]= i;
			else
				nxt[i - 1]= nxt[i];
			sort(k[i].begin(), k[i].end(), [](const int &a, const int &b) -> bool { return a > b; });
		}
		for(int i= 1, x, y; i <= m; i++) {
			read(x), read(y), x= lower_bound(b + 1, b + t + 1, x) - b, y= lower_bound(b + 1, b + t + 1, y) - b;
			p[x].push_back(y), p[y].push_back(x);
		}
		for(int i= 1; i <= t; i++) sort(p[i].begin(), p[i].end(), [](const int &a, const int &b) -> bool { return cnt[a] < cnt[b]; });
		for(int i= nxt[0]; i <= n; i= nxt[i]) {
			for(int j= nxt[0]; j <= i; j= nxt[j]) {
				for(auto &o : k[i]) {
					if(o == 0) break;
					vis[o]= 1;
					int ma= 0;
					while(l[o] < (int)p[o].size() && cnt[p[o][l[o]]] < j) ++l[o];
					int las= l[o];
					while(l[o] < (int)p[o].size() && cnt[p[o][l[o]]] == j) vis[p[o][l[o]]]= 1, ++l[o];
					while(vis[k[j][ma]]) ++ma;
					if(k[j][ma]) ans= max(ans, (long long)(i + j) * (b[o] + b[k[j][ma]]));
					for(int s= las; s < l[o]; s++) vis[p[o][s]]= 0;
					ma= 0;
					vis[o]= 0;
					if(las == l[o]) break;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Hywel (赞：0)

#### 思路
修正 $x$ 并遍历 $cnt_y \le cnt_x$。然后我们需要找到所有元素的最大 $y$，而且正好出现在 $cnt_y$ 次，满足 $x \neq y$ 和配对 $(x,y)$ 不是坏的。要做到这一点，我们只需遍历所有元素，这些元素以不增加的顺序恰好出现 $cnt_y$ 次，而 $pair(x,y)$ 是坏的或者可能 $x=y$。如果找到这样的 $y$，更新答案即可。

要检查配对是否是坏的，只需将所有配对添加到 set 中，然后检查配对是否在 set 中。此外，还可以对所有坏对进行排序，并使用 bitset 进行检查。这两种方法都是 $O(logn)$。

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
	template < typename T > inline void write( T x )
	{
	    if(x < 0)
	        putchar('-') , x = - x;
	    if(x == 0)
	    {
	        putchar('0') ;
	        return ;
	    }
	    if(x > 9)
	        write(x / 10) ;
	    putchar(x % 10 + '0') ;
	    return ;
	}
	template < typename T > inline void read( T &x )
	{
	    x = 0 ; int w = 1 ; char ch = getchar() ;
	    while( !isdigit( ch ) ) { if(ch == '-') w = -1 ; ch = getchar() ; }
	    while( isdigit( ch ) ) x = (x << 1) + (x << 3) + (ch ^ 48) , ch = getchar() ;
	    x *= w;
	}
}

#define writeln(x) write(x) , putchar('\n')
#define writesp(x) write(x) , putchar(' ')
using namespace IO ;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    map<int, int> cnt;
    for (auto &x : a) {
        cin >> x;
        cnt[x]++;
    }
 
    vector<pair<int, int>> bad_pairs;
    bad_pairs.reserve(2 * m);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        bad_pairs.emplace_back(x, y);
        bad_pairs.emplace_back(y, x);
    }
    sort(bad_pairs.begin(), bad_pairs.end());
 
    vector<vector<int>> occ(n);
    for (auto &[x, c] : cnt)
        occ[c].push_back(x);
 
    for (auto &v : occ)
        reverse(v.begin(), v.end());
 
    long long answer = 0;
    for (int cnt_x = 1; cnt_x < n; cnt_x++)
        for (int x : occ[cnt_x])
            for (int cnt_y = 1; cnt_y <= cnt_x; cnt_y++)
                for (auto y : occ[cnt_y])
                    if (x != y && !binary_search(bad_pairs.begin(), bad_pairs.end(), pair<int, int>{x, y})) {
                        answer = max(answer, 1ll * (cnt_x + cnt_y) * (x + y));
                        break;
                    }
 
    cout << answer << '\n';
}
 
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--)
        solve();
}
```

---

## 作者：清烛 (赞：0)

差点就在场上写出这题了。。

首先这题有一个非常关键的性质就是，**不同的 $cnt_i$ 只有 $O(\sqrt n)$ 种**。

因此我们枚举 $cnt_x$ 和 $cnt_y\le cnt_x$，这样子复杂度就是 $O(n)$ 的，从大到小找到第一个不和 $a_i$ 形成 bad pair 的 $j$（可以用 `set` 维护，$O(\log n)$），这样的复杂度是 $O(n\log n)$ 的。

```cpp
using ll = long long;
using pii = pair<int, int>;
const int maxn = 3e5 + 5;
int n, m;
map<int, int> cnt;
set<pii> bad;
vector<int> occ[maxn];

int main() {
    int T; read(T);
    while (T--) {
        map<int, int>().swap(cnt);
        set<pii>().swap(bad);
        read(n, m);
        FOR(i, 1, n) {
            int x; read(x);
            ++cnt[x], vector<int>().swap(occ[i]);
        }
        FOR(i, 1, m) {
            int x, y; read(x, y);
            bad.insert({x, y}), bad.insert({y, x});
        }
        for (auto &p : cnt) occ[p.second].push_back(p.first);
        FOR(i, 1, n) reverse(occ[i].begin(), occ[i].end());
        ll ans = 0;
        FOR(cntx, 1, n)
            for (auto x : occ[cntx])
                FOR(cnty, 1, cntx)
                    for (auto y : occ[cnty])
                        if (x != y && !bad.count({x, y})) {
                            chkmax(ans, 1ll * (x + y) * (cntx + cnty));
                            break;
                        }
        print(ans);
    }
    return output(), 0;
}
```

---

