# TV Subscriptions (Hard Version)

## 题目描述

The only difference between easy and hard versions is constraints.

The BerTV channel every day broadcasts one episode of one of the $ k $ TV shows. You know the schedule for the next $ n $ days: a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le k $ ), where $ a_i $ is the show, the episode of which will be shown in $ i $ -th day.

The subscription to the show is bought for the entire show (i.e. for all its episodes), for each show the subscription is bought separately.

How many minimum subscriptions do you need to buy in order to have the opportunity to watch episodes of purchased shows $ d $ ( $ 1 \le d \le n $ ) days in a row? In other words, you want to buy the minimum number of TV shows so that there is some segment of $ d $ consecutive days in which all episodes belong to the purchased shows.

## 说明/提示

In the first test case to have an opportunity to watch shows for two consecutive days, you need to buy a subscription on show $ 1 $ and on show $ 2 $ . So the answer is two.

In the second test case, you can buy a subscription to any show because for each show you can find a segment of three consecutive days, consisting only of episodes of this show.

In the third test case in the unique segment of four days, you have four different shows, so you need to buy a subscription to all these four shows.

In the fourth test case, you can buy subscriptions to shows $ 3,5,7,8,9 $ , and you will be able to watch shows for the last eight days.

## 样例 #1

### 输入

```
4
5 2 2
1 2 1 2 1
9 3 3
3 3 3 2 2 2 1 1 1
4 10 4
10 8 6 4
16 9 8
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3
```

### 输出

```
2
1
4
5
```

# 题解

## 作者：Meatherm (赞：5)

我们可以统计每一个连续的长度为 $d$ 的段包含了多少个不同的元素。

容易发现直接统计的复杂度是 $O(nd)$ 的。很明显无法通过。

考虑进行优化。我们用 $cnt[i]$ 表示元素 $i$ 在当前区间中出现了多少次，$sum$ 表示当前区间有多少个不同的元素。

在加入一个元素 $i$ 的时候，将 $cnt[i]$ 赋值为 $cnt[i]+1$。如果在操作前 $cnt[i]=0$，则表示这个元素从未出现过，$sum$ 需要 $+1$。

在删除一个元素 $i$ 的时候，将 $cnt[i]$ 赋值为 $cnt[i]-1$。如果在操作后 $cnt[i]=0$，则表示这个元素已经被全部删除，$sum$ 需要 $-1$。

于是就变得很简单了。首先处理出区间 $[1,d]$ 的值。对于后面的区间 $[i,i+d-1](2\leq i \leq n-d+1)$，删除 $a[i-1]$，加入 $a[i+d-1]$ 即可。注意一定要先删除后加入。至于为什么...可以去看看样例，这里就不再说明。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=200010,M=1000010;
int a[N];
int n,k,d;
int sum[M],cnt;
int T;
int ans;
inline void add(int x){
	if(!sum[a[x]])
		++cnt;
	++sum[a[x]];	
	return;
}
inline void del(int x){
	--sum[a[x]];
	if(!sum[a[x]])
		--cnt;
	return;	
}
int main(void){
	scanf("%d",&T);
	while(T--){
		memset(sum,0,sizeof(sum));
		cnt=0;
		scanf("%d%d%d",&n,&k,&d);
		for(rr int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		for(rr int i=1;i<=d;++i)
			add(i);
		ans=cnt;
		for(rr int i=d+1;i<=n;++i){
			del(i-d);
			add(i);		
			ans=std::min(ans,cnt);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：杨铠远 (赞：2)

思路很简单：

类似滑动窗口，$O(n)$扫描的同时维护一个桶和一个队列
当队列长度超过d的时候弹队头，满足条件时更新答案就好了
具体细节看代码
```cpp
//Code by : Y-k-y
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#include <map>
#define ll long long
const int N=1000010;
using namespace std;
inline int rnd(){
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void wr(int x){
	if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');
}
int n,k,d,T,ans;
int a[N],t[N],q[N];
int main(){
	cin>>T;
	while(T--){
		n=rnd();k=rnd();d=rnd();
		memset(t,0,sizeof(t));
		for(int i=1;i<=n;i++)a[i]=rnd();
		ans=1e9;
		int head=1,tail=0,sum=0;
		for(int i=1;i<=n;i++){
			t[a[i]]++;
			q[++tail]=i;
			if(t[a[i]]==1)sum++;
			while(head<=tail&&i-q[head]>=d){
				t[a[q[head]]]--;if(t[a[q[head]]]==0)sum--;head++;
			}
			if(i-q[head]+1>=d)ans=min(ans,sum);
		}
		wr(ans);puts("");
	}
	return 0;
}

```


---

## 作者：傅思维666 (赞：1)


## 题解：

滑动窗口题目的数据加强版（对比$Easy\,\,\, Version$）

其实最初认识滑动窗口这种题的时候是学单调队列的时候。但是显然这道题不能用数据结构来做。那么我们回归滑动窗口的本质来尝试着做这道题。

滑动窗口的本质是啥？~~滑动啊！~~

那我们就可以进行模拟：先手动跑第一个线段（初始窗口），统计颜色出现的次数（存到$cnt[i]$数组，注意这个数组一定要开成$10^6$.如果这个颜色是第一次出现（即$cnt[i]=0$），那么就把颜色数（$sum$变量）++）

然后开滑。每到一个新元素，先删除滑动之前最古老的那个元素。然后再把最新的元素加进来，然后看一看这个$cnt[i]$是否需要把$sum$也随着改动。然后就可以AC了。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2*1e5+10;
const int maxk=1e6+10;
int n,k,d;
int a[maxn];
int cnt[maxk],sum,ans;
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(cnt,0,sizeof(cnt));
        sum=0;
        scanf("%d%d%d",&n,&k,&d);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=d;i++)
        {
            if(!cnt[a[i]])
                sum++;
            cnt[a[i]]++;
        }
        ans=sum;
        for(int i=d+1;i<=n;i++)
        {
            cnt[a[i-d]]--;
            if(!cnt[a[i-d]])
                sum--;
            if(!cnt[a[i]])
                sum++;
            cnt[a[i]]++;
            ans=min(ans,sum);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```



---

## 作者：20120511qhc (赞：0)

# 思路

此题因为数据范围大，无法暴力枚举，考虑优化。

因为数字的范围比较大，所以开 `map`。

我们还可以用一个 $cnt$ 变量维护现在的区间内的元素种类数量，并用一个 $ans$ 每次更新。

# AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, d, a[200005], t;
int main(){ 
  for(cin >> t; t; t--){
    cin >> n >> k >> d;
    for(int i = 1; i <= n; i++){
      cin >> a[i];
    }
    int cnt = 0, minn = 1e9;
    map<int, int> mp;
    for(int i = 1; i <= d; i++){
      mp[a[i]]++;
      if(mp[a[i]] == 1) cnt++;
    }
    minn = min(minn, cnt);
    for(int i = d + 1; i <= n; i++){
      mp[a[i]]++;
      if(mp[a[i]] == 1) cnt++;
      mp[a[i - d]]--;
      if(mp[a[i - d]] == 0) cnt--;
      minn = min(minn, cnt);
    }
    cout << minn << "\n"; 
  }
  return 0;
}
```


---

## 作者：qiuzijin2026 (赞：0)

# TV Subscriptions (Hard Version)

## [题面](https://www.luogu.com.cn/problem/CF1225B2)

## 思路

用类似单调队列的方法做。

窗口从左到右滑动时，只需要维护一下新加入的和被删除的。

我们设 $s(i)$ 表示 $i$ 在这个区间里出现了几次，$l$ 表示在这个区间里出现了几种不同的数。

加入时，设现在加入的是 $x$：

- 如果 $s(x)=0$，那么 $s(x)$ 加一，$l$ 加一。

- 如果 $s(x)>0$，那么 $s(x)$ 加一。

删除时，设现在删除的是 $x$：

- 如果 $s(x)=1$，那么 $s(x)$ 减一，$l$ 减一。

- 如果 $s(x)>1$，那么 $s(x)$ 减一。

用一个 $ans$ 记录最小值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,d;
int t;
int a[200005];
int s[1000005]; 
int l;
int ans;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&t);
	while(t--){
		memset(s,0,sizeof(s));
		l=0;
		ans=INT_MAX;
		scanf("%d%d%d",&n,&k,&d);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<d;i++){
			if(s[a[i]]==0) l++;
			s[a[i]]++;
		} 
		for(int i=d;i<=n;i++){
			s[a[i-d]]--;
			if(s[a[i-d]]==0) l--;
			if(s[a[i]]==0) l++;
			s[a[i]]++;
			ans=min(ans,l);
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：happybob (赞：0)

## 题意

给定一个 $n$ 个元素的序列 $a$，另外还给定 $k, d$，其中 $a_i \leq k$，现在要求的是所有 $[l, l + d - 1]$ 区间中出现的不同的数的个数最小是多少，其中 $l \geq 1, l + d - 1 \leq n$。

## 解法

~~首先希望审核该题解的管理员给这道题评个难度。~~

我提供一个本题最差解法，限时 $2s$，这份题解最坏的数据点跑了 $1.138ms$，还开了部分的指令集，不过用这份代码交到本题的[弱化版](https://www.luogu.com.cn/problem/CF1225B1)上却跑得很快，最坏的点只跑了 $15ms$，在洛谷轻松 Rank1。

这份题解用的是莫队，因为考虑要求的是区间中出现的不同的数的个数，是莫队经典写法。

但是普通莫队加上部分指令集和快读虽然能过，但是时间很离谱，花了 $1809ms$
，并且只能用 GNU C++14 才能过，GNU C++17 (64) 过不去。

我们知道莫队有一个地方可以优化，那就是排序。但我指的优化并不是奇偶排序，而是根本不用排序。

明显我们的排序是按 $l$ 分块，$r$ 递增的排序。但是这道题中显然 $l, r$ 一开始都是递增的，根本不用排序，这样即可过此题。

代码：

```cpp
#pragma GCC optimize("-Ofast")
#pragma GCC target("avx,sse,sse2,sse3,sse4")
#pragma unroll 10
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1e6 + 5;

int t, n, k, d, cnt[N], a[N], tcnt = 0, len, res = 0;

inline int read()
{
	register char ch = getchar();
	register int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}

struct Node
{
	int l, r;
	bool operator<(const Node& g) const
	{
		int i = l / len, j = g.l / len;
		return (i ^ j ? i < j : i & 1 ? r < g.r : r > g.r);
	}
}q[N];

void add(int x)
{
	if (++cnt[a[x]] == 1) ++res;
}

void del(int x)
{
	if (--cnt[a[x]] == 0) --res;
}

int main()
{
	t = read();
	for (int i = 1; i <= t; i++)
	{
		res = 0;
		tcnt = 0;
		n = read(), k = read(), d = read();
		len = sqrt(n);
		memset(cnt, 0, sizeof(cnt));
		for (int j = 1; j <= n; j++) a[j] = read();
		for (int j = 1; j + d - 1 <= n; j++)
		{
			++tcnt;
			q[tcnt].l = j;
			q[tcnt].r = j + d - 1;
		}
		//sort(q + 1, q + tcnt + 1);
		int nl(1), nr(0), ans = 1e9;
		for (int j = 1; j <= tcnt; j++)
		{
			int l(q[j].l), r(q[j].r);
			while (nl < l) del(nl++);
			while (nl > l) add(--nl);
			while (nr < r) add(++nr);
			while (nr > r) del(nr--);
			ans = min(ans, res);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```



---

## 作者：DepletedPrism (赞：0)

题意简述:

给定一段序列, 在其中取出一段连续的, 且长度为 $d$ 的一段, 使其包含的不同数字个数最小

其中 $n \leq 2 \times 10^5$

-----

第一眼看去想起来了 [HH 的项链](https://www.luogu.org/problem/P1972), 从 $1$ 开始统计 $[i,\ i+d-1]$ 内不同数字个数就好了, 这里我使用了树状数组的解法, 时间复杂度 $O(T \cdot n \log n)$.

值得注意的地方, 有这题多组数据且数据组数 $T \leq 2 \times 10^5$, 清空的时候需要有点技巧, 不能无脑 ``memset`` 上去, CF 讨论贴里就有人因为这个 TLE 了 = =

其实这道题有 $O(Tn)$ 的做法, 记 ``cnt[i]`` 表示当前区间内数字 ``i`` 出现次数, 用类似莫队的维护方法维护就好了.

-----

树状数组写法代码

```cpp
// CF B
// DeP
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
namespace IO {
    const int MAXSIZE = 1 << 18 | 1;
    char buf[MAXSIZE], *p1, *p2;
 
    inline int Gc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2)? EOF: *p1++; }
    template<class T> void read(T& x) {
        x = 0; int f = 0, ch = Gc();
        while (!isdigit(ch)) f |= ch == '-', ch = Gc();
        while (isdigit(ch)) x = x * 10 + ch - '0', ch = Gc();
        if (f) x = -x;
    }
}
using IO::read;
 
const int MAXN = 2e5+5, MAXK = 1e6+5;

int n, k, d;
int A[MAXN], numPos[MAXK];
 
namespace BIT {
    int C[MAXN];
 
    inline int lowbit(int x) { return x & -x; }
 
    void add(int pos, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) C[i] += val;
    }
 
    int sum(int pos) {
        int ret = 0;
        for (int i = pos; i; i -= lowbit(i)) ret += C[i];
        return ret;
    }
}
 
int main() {
    int T; read(T);
    while (T--) {
        // input
        read(n); read(k); read(d);
        for (int i = 1; i <= n; ++i) read(A[i]);
        // init
        memset(numPos, 0, sizeof numPos);
        // 这里没有 TLE 就是个奇迹...
        for (int i = 1; i <= n; ++i) {
            int res = BIT::sum(i);
            if (res) BIT::add(i, -res);
        }
        // solve
        int ans = k, ptr = 1;
        for (int i = 1; i+d-1 <= n; ++i) {
            int L = i, R = i+d-1;
            for (int j = ptr; j <= R; ++j) {
                if (numPos[A[j]] != 0) BIT::add(numPos[A[j]], -1);
                BIT::add(j, 1);
                numPos[A[j]] = j;
            }
            ptr = R + 1;
            ans = min(ans, BIT::sum(R) - BIT::sum(L-1));
        }
        // output
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：big_news (赞：0)

区间的长度是固定的，那么只需要开一个桶，维护一下在某段区间内有那些元素。

考虑从一个区间滑动到另一个区间，那么这时候区间内元素个数是可以 O(1) 维护的，然后就没什么了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int CN = 1e6+6;
const int INF = 0x3f3f3f3f;

int read(){
    int s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne;
}

int t,n,k,d,a[CN];
int tot[CN];

int main()
{
    t = read();
    while(t--){
        memset(tot,0,sizeof(tot));
        
        n = read(); k = read(); d = read();
        for(int i=1;i<=n;i++) a[i] = read();
        
        int ans = INF,cnt = 0;
        for(int i=1;i<d;i++) {if(!tot[ a[i] ]) cnt++; tot[ a[i] ]++;}
        for(int i=d;i<=n;i++){
            if(!tot[ a[i] ]) cnt++; tot[ a[i] ]++;
            tot[ a[i-d] ]--; if(!tot[ a[i-d] ]) cnt--;
            ans = min(ans, cnt); 
        }
        
        printf("%d\n",ans);
    }
    
    return 0;
}
```

---

