# [ABC194E] Mex Min

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc194/tasks/abc194_e

$ \mathrm{mex}(x_1,\ x_2,\ x_3,\ \dots,\ x_k) $ を、$ x_1,\ x_2,\ x_3,\ \dots,\ x_k $ に含まれない最小の非負整数と定義します。  
 長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ A_3,\ \dots,\ A_N) $ が与えられます。  
 $ 0\ \le\ i\ \le\ N\ -\ M $ を満たす全ての整数 $ i $ について $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2},\ A_{i\ +\ 3},\ \dots,\ A_{i\ +\ M}) $ を計算したとき、この $ N\ -\ M\ +\ 1 $ 個の値のうちの最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ M\ \le\ N\ \le\ 1.5\ \times\ 10^6 $
- $ 0\ \le\ A_i\ \lt\ N $
- 入力に含まれる値は全て整数

### Sample Explanation 1

\- $ i\ =\ 0 $ のとき : $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2})\ =\ \mathrm{mex}(0,\ 0)\ =\ 1 $ - $ i\ =\ 1 $ のとき : $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2})\ =\ \mathrm{mex}(0,\ 1)\ =\ 2 $ よって $ 1 $ と $ 2 $ のうちの最小値である $ 1 $ が答えです。

### Sample Explanation 2

\- $ i\ =\ 0 $ のとき : $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2})\ =\ \mathrm{mex}(1,\ 1)\ =\ 0 $ - $ i\ =\ 1 $ のとき : $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2})\ =\ \mathrm{mex}(1,\ 1)\ =\ 0 $ となります。

### Sample Explanation 3

\- $ i\ =\ 0 $ のとき : $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2})\ =\ \mathrm{mex}(0,\ 1)\ =\ 2 $ - $ i\ =\ 1 $ のとき : $ \mathrm{mex}(A_{i\ +\ 1},\ A_{i\ +\ 2})\ =\ \mathrm{mex}(1,\ 0)\ =\ 2 $ となります。

## 样例 #1

### 输入

```
3 2
0 0 1```

### 输出

```
1```

## 样例 #2

### 输入

```
3 2
1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3 2
0 1 0```

### 输出

```
2```

## 样例 #4

### 输入

```
7 3
0 0 1 2 0 1 0```

### 输出

```
2```

# 题解

## 作者：hellolin (赞：3)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_abc194_e)

[题面(AtCoder)](https://atcoder.jp/contests/abc194/tasks/abc194_e)

AtCoder Problems 评级难度：$\texttt{\color{#72ff72}{1088}}$。

## 题意

- 给你一个长度为 $N$ 的序列 $A$，求 $A$ 中所有长度为 $M$ 的连续子序列中，最小的 $\operatorname{mex}$ 值（定义 $\operatorname{mex}$ 为序列中最小未出现的自然数）。
- $1\le M\le N\le 15\times 10^5,\ 0\le A_i< N$。

## 思路

看到连续子序列，一下子想到类似滑动窗口的方法。

先算出窗口在初始位置时的 $\operatorname{mex}$ 值，在向右移动时检查移出的数，若该移出的数在当前窗口中出现次数变为 $0$，更新 $\operatorname{mex}$ 值即可。

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const static int N=2e6;
int n,m,a[N],ans;
map<int,int>t;

inline void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)++t[a[i]]; // 初始窗口
    for(int i=0;i<=n;i++) // 计算初始窗口 mex 值，注意范围要到 n
        if(!t[i])
        {
            ans=i;
            break;
        }
    
    for(int i=m+1;i<=n;i++) // 窗口向右滑动
    {
        --t[a[i-m]],++t[a[i]]; // 更新
        if(!t[a[i-m]]) // 发现 mex 值可能有变化
            ans=min(ans,a[i-m]);
    }
    cout<<ans<<endl;
}

#undef int
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
```

---

## 作者：endswitch (赞：1)

用的是滑动窗口+桶。

我们先预处理出来 $1$ 到 $m$ 的 $\operatorname{mex}$ 值，滑动窗口时更改桶序列并检查从桶序列中删除的数。若该元素在桶序列的出现次数归零，则与现有答案取更小的一个。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6;
int n,m,a[N],ans,f[N];
inline int min(int a,int b) {return a<b?a:b;}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) f[a[i]]++;
	for(int i=0;i<=n;i++)
		if(!f[i]) {
			ans=i;
			break;
		}
	for(int i=m+1;i<=n;i++) {
		f[a[i-m]]--,f[a[i]]++;
		if(!f[a[i-m]]) ans=min(ans,a[i-m]);
	}
	cout<<ans;
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/111876578)

---

## 作者：cyz_czy (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/AT_abc194_e)

这题是我们一中~~出的题目~~找的题目，~~是题单中最水的一道~~。

为了纪念这一道思维训练第一道 `AC` 的题目，我来写一篇题解。

## 思路
这道题目的范围特别容易 `T`，但我们对于这种类似于[滑动窗口](https://www.luogu.com.cn/problem/P1886)的题目，我们可以先将 $l_{1} $ 到 $l_{M}$ 中 `Mex` 的值求出，将该序列中每一个数 $p_{l_{i}}$ 加 $1$。这样在判断下一个子序列的时候，我们将 $p_{l_{1}} $ $-1$，将 $p_{l_{M+1}} $ $+1$ 就可以以一种很快的速度判断第二个子序列了（即弹出子序列第一个再加进下一个数）。

对于判断方法，我们可以将第一个子序列的 `Mex` 值记为 `mn`，然后当 $l_{i}$ $<$ `mn`（弹出的数小于 `mn`）以及 $l_{M+i}$ 不等于 $l_{i}$（新加进的数没有让弹出的数再次出现）以及 $p_{l_{i}} $ 不等于 $0$（没有这个数了）的时候，就会出现比 `mn` 更小的答案，此时就要更新答案了。

## Code:

```cpp
//代码内有队列的做法注释，便于理解

#include <iostream>

const int N=1e6+5e5+1e1;

int l[N];
int p[N];

inline int read();
inline void print(int x);

int n,m;

//std::queue<int> q; //队列注释

inline int f(){
	for(int i=1;i<=n;i++)
		/*q.push(l[i]),*/p[l[i]]++;
		
	for(int i=0;;i++)
		if(!p[i])
			return i;//找第一个子序列的 Mex 值
}

int main(){
	m=read();
	n=read();
	
	for(int i=1;i<=m;i++)
		l[i]=read();
	
	int mn=f();
	
	for(int i=1;i+n<=m;i++){
		
		p[l[i]]--;
		//q.pop();//弹出
		p[l[i+n]]++;
		//q.push(l[temp]);//放入
		
		if(l[i]<mn&&!p[l[i]]&&l[i+n]!=l[i])
			mn=l[i];//更新 Mex 值
		
		if(!mn)
			break;//不可能有比0还小的答案
	}
	
	print(mn);
	
	return 0;
}

//快读快写
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    
    while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	
    while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
   	
    return x*f;
}

inline void print(int x){
  	if(x<0){
	  	putchar('-');x=-x;
	}

  	if(x>9){
	  	print(x/10);putchar(x%10+'0');
	}

 	else
		putchar(x+'0');

  	return ;
}
```

[AC 记录](https://www.luogu.com.cn/record/111891474)

---

## 作者：lfxxx (赞：0)

按照题意直接扫描一遍，把当前扫到的数加入集合，这个数往前数 $m$ 个数的数从集合中删除，用线段树维护集合加入删除与求 mex 即可。

具体来说记录每个区间内的元素值，在线段树上二分，假若左区间中有空缺的位置就去往左区间递归，否则去往右区间递归。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e6+114;
const int top = 1e9+114;
int a[maxn];
struct Node{
	int sum,ls,rs;
	int val;
}SGTtree[maxn*30];
int tot,root;
void pushup(int cur){
	SGTtree[cur].val=SGTtree[SGTtree[cur].ls].val+SGTtree[SGTtree[cur].rs].val;
}
void add(int &cur,int lt,int rt,int pos,int v){
	if(cur==0) cur=++tot;
	if(rt<pos||lt>pos) return ;
	if(lt==rt){
		SGTtree[cur].sum+=v;
		SGTtree[cur].val=(SGTtree[cur].sum==0?0:1);
		return ;
	}
	int mid=(lt+rt)/2;
	add(SGTtree[cur].ls,lt,mid,pos,v);
	add(SGTtree[cur].rs,mid+1,rt,pos,v);
	pushup(cur);
}
int mex(int cur,int lt,int rt){
	if(lt==rt) return lt;
	int mid=(lt+rt)/2;
	if(SGTtree[SGTtree[cur].ls].val==(mid-lt+1)){
		return mex(SGTtree[cur].rs,mid+1,rt);
	}
	else return mex(SGTtree[cur].ls,lt,mid);
}
int n,m,anser=1000000000000000000;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]++;
	}
	for(int i=1;i<=n;i++){
		add(root,1,top,a[i],1);
		if((i-m+1)>=1){
			if((i-m)>=1)
				add(root,1,top,a[(i-m)],-1);
			anser=min(anser,mex(root,1,top)-1); 
		}
	}
	cout<<anser;
}
```


---

## 作者：loser_seele (赞：0)

介绍本题的两个解法。

首先答案显然为最小的非负整数，这个整数在某个长度为 $ M $ 的区间根本没出现过。

于是我们可以将一个数出现的位置塞进一个数组 $ pos $ 里，然后从小到大枚举答案 $ j $，检查 $ j $ 对应的 $ pos $ 是否存在两个元素间隔 $ > M $。由于 $ pos $ 的总元素个数显然等于数组元素个数，所以总时间复杂度 $ \mathcal{O}(n) $，可以通过。

第二种解法：区间 $ mex $，这个有原题 [P4137](https://www.luogu.com.cn/problem/P4137)。

于是从题解里套用一个回滚莫队的做法：

$ mex $ 显然满足删除可以简单维护，但是增加不行的性质。

于是先算出整个序列 $ mex $，然后考虑回滚莫队，将询问的左端点所在的块从小到大，右端点从大到小排序，于是右端点只要支持朴素删除即可。如果没看懂可以参考 [这篇题解](https://www.luogu.com.cn/blog/stochcorz/report-p4137)。

算出所有区间的 $ mex $ 之后取最小值即可。

于是时间复杂度 $ \mathcal{O}(n\sqrt{n}) $，但由于询问是一个类似滑动窗口的结构所以实际上根本跑不满，随手通过。

如果原题是这个数据范围估计是很难通过，但这题数据范围较大的同时也开大了时间限制。

代码：（其实是上面的题解魔改来的）

```cpp
#include <bits/stdc++.h>
#define ri register int
#define getchar() (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
#define N 2000005
#define B 1000
using namespace std;
char ou[1 << 22], buf[1 << 22], *p1 = buf, *p2 = buf;
int n, m, s, a[N], bel[N], cnt[N], tmp[N], ans[N], L[N / B + 5], R[N / B + 5], p3 = -1;
struct query
{
	int l, r, id;
	inline bool operator<(const query &x) const
	{
		return bel[l] ^ bel[x.l] ? bel[l] < bel[x.l] : r > x.r;
	}
} q[N];
template <typename T>
inline void read(T &x)
{
	register T c = getchar();
	for (; c < 48 || 57 < c;)
		c = getchar();
	for (; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c ^ 48);
}
template <typename T>
inline void print(const T x)
{
	if (x > 9)
		print(x / 10);
	ou[++p3] = x % 10 | 48;
	if (p3 > (1 << 21))
		fwrite(ou, 1, p3 + 1, stdout), p3 = -1;
}
inline int mnn(const int a, const int b)
{
	return a < b ? a : b;
}
signed main()
{
	read(n), read(m);
	for (ri i = 1; i <= n; ++i)
	{
		read(a[i]), bel[i] = (i - 1) / B + 1;
		if (a[i] <= n + 1)
			++cnt[a[i]];
	}
	while (cnt[s])
		++s;
	int tmpp=m;
    m=n-m+1;
	for (ri i = 1; i <= m; ++i)
	q[i].l=i, q[i].r=i+tmpp-1, q[i].id = i;
	for (ri i = 1; i < bel[n]; ++i)
		L[i] = R[i - 1] + 1, R[i] = i * B;
	L[bel[n]] = R[bel[n] - 1] + 1, R[bel[n]] = n, sort(q + 1, q + 1 + m);
	for (ri k = 1, i = 1, l, r, p; k <= bel[n]; ++k)
	{
		l = L[k], r = n, p = s;
		for (ri t; bel[q[i].l] == k; ++i)
		{
			if (bel[q[i].r] == k)
			{
				ri t = 0;
				for (ri j = q[i].l; j <= q[i].r; ++j)
					if (a[j] <= n + 1)
						++tmp[a[j]];
				while (tmp[t])
					++t;
				ans[q[i].id] = t;
				for (ri j = q[i].l; j <= q[i].r; ++j)
					if (a[j] <= n + 1)
						--tmp[a[j]];
				continue;
			}
			for (; r > q[i].r; --r)
				if (a[r] <= n + 1 && !--cnt[a[r]])
					p = mnn(p, a[r]);
			t = p;
			for (; l < q[i].l; ++l)
				if (a[l] <= n + 1 && !--cnt[a[l]])
					t = mnn(t, a[l]);
			ans[q[i].id] = t;
			while (l > L[k])
			{
				--l;
				if (a[l] <= n + 1)
					++cnt[a[l]];
			}
		}
		while (r < n)
		{
			++r;
			if (a[r] <= n + 1)
				++cnt[a[r]];
		}
		for (; l < L[k + 1]; ++l)
			if (a[l] <= n + 1 && !--cnt[a[l]])
				s = mnn(s, a[l]);
	}
    int minn=2e9;
	for (ri i = 1; i <= m; ++i)
	minn=min(minn,ans[i]);
	cout<<minn;
}
```


---

