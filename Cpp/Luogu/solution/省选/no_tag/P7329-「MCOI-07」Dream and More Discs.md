# 「MCOI-07」Dream and More Discs

## 题目背景

**本题为 IO 交互题。**

## 题目描述

Dream 将 Tommy 的所有音乐盘分为 $n$ 类，其中第 $i$ 类有 $2^m-1$ 片音乐盘。所有盘都有一个唯一的正整数重要度。  
现在 Dream 已经把所有类之内的音乐盘按照重要度递增排序。Dream 想知道**所有**盘中重要度第 $k$ 小是哪个盘。

由于音乐盘数量实在太多，Dream 不能直接给你所有音乐盘的重要度。在寻找答案时，Dream 允许你访问第 $i$ 类重要度第 $j$ 小的盘重要度值。

## 说明/提示

#### 样例 1 解释

Dream 的音乐盘重要度为 $[[2222,22222,222222],[22,222,2222222]]$。  
第 2 类型为 $[22,222]$；第 2 类型的第 2 小重要度为 $222$。  
全局第 2 小重要度也是这音乐盘。

#### 数据规模与约定

**本题采用捆绑测试。**

|  Subtask | 分值 | $n$ | $m$ | $k$ | $Th$ |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| 1 | 1 pts | $1$ | $1$| $1$| $15,000$ |
| 2 | 9 pts | $50$ | $8$ | 无 | $15,000$ |
| 3 | 19 pts | $20$ | $11$ | 无 | $15,000$ |
| 4 | 17 pts | $50$ | $11$ | 无 | $6,666$ |
| 5 | 23 pts | $50$ | $11$ | 无 | $2,333$ |
| 6 | 31 pts | $50$ | $11$ | 无 | $1,111$ |

对于所有数据，$1\le k\le n(2^m-1)$，所有音乐盘的重要度互不相同并且小于等于 $10^{18}$。

## 样例 #1

### 输入

```
2 2 2 22

222```

### 输出

```

? 2 2

! 2 2```

# 题解

## 作者：Cutest_Junior (赞：5)

## 题解 P7329 【[w33z-2018] Dream and More Discs】

### 题意

+ 阴间交互题；
+ 有 $n$ 类音乐盘，每类有 $2^m-1$ 片按重要度递增排序的音乐盘，所有盘重要度互不相同；
+ 每次可以询问第 $i$ 类第 $j$ 个盘的重要度，求所有盘中重要度第 $k$ 小的是哪个盘；
+ $n\le50$，$m\le11$，询问次数不超过 $1111$ 次，重要度都是不超过 $10^{18}$ 的正整数。

### 做法

记 $a_{i,j}$ 为第 $i$ 类第 $j$ 个盘的重要度。

对每个区间二分，若当前 $\sum\limits_{i=1}^{n}mid_i>k$，就可以找到 $p$ 满足 $a_{p,mid_p}>a_{i,mid_i}(1\le i\le n,i\ne p)$，把 $r_p$ 改为 $mid_p-1$，也就是说，原来从 $mid_p$ 到 $r_p$ 的这段区间的盘都不用考虑了。~~想一想，为什么。~~

根据上面的定义，比 $a_{p,mid_p}$ 小的至少有 $\left(\sum\limits_{i=1}^{n}mid_i\right)-1$（不包括它本身，所以要减一）个盘，而 $k<\sum\limits_{i=1}^{n}mid_i$，说明第 $k$ 个盘的重要度一定小于 $a_{p,mid_p}$。

同理，若当前 $\sum\limits_{i=1}^{n}mid_i\le k$，则可以找到 $p$ 满足 $a_{p,mid_p}<a_{i,mid_i}(1\le i\le n,i\ne p)$，把 $l_p$ 改为 $mid_p+1$。

可以发现每一类最多查询 $m$ 次，总查询次数 $O(nm)$。

十年 OI 一场空，不开 long long 见祖宗。

~~我才不会告诉你我因为没开 long long 连 WA 12 次。~~

### 代码

```cpp
#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 55;

int l[N], r[N], mid[N];
ll ans[N];

void in(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%lld", &ans[x]);
}

int main() {
	int n, m, k, th;
	scanf("%d%d%d%d", &n, &m, &k, &th);
	for (int i = 1; i <= n; ++i) {
		l[i] = 1, r[i] = (1 << m) - 1;
		mid[i] = (l[i] + r[i]) >> 1;
		in(i, mid[i]);
	}
//	printf("%d %d\n", mid[1], mid[2]);
	for (int i = 1; i <= n * m; ++i) {
		int minn = 1, maxx = 1;
		int cnt = mid[1];
		for (int j = 2; j <= n; ++j) {
			cnt += mid[j];
			if (l[j] > r[j]) {
				continue;
			}
			if (l[minn] > r[minn]) {
				minn = j;
			}
			if (l[maxx] > r[maxx]) {
				maxx = j;
			}
			if (ans[j] < ans[minn]) {
				minn = j;
			}
			if (ans[j] > ans[maxx]) {
				maxx = j;
			}
		}
//		printf("cnt %d\n", cnt);
		if (k < cnt) {
			r[maxx] = mid[maxx] - 1;
			mid[maxx] = (l[maxx] + r[maxx]) >> 1;
			if (l[maxx] <= r[maxx]) {
				in(maxx, mid[maxx]);
			}
		}
		else {
			l[minn] = mid[minn] + 1;
			mid[minn] = (l[minn] + r[minn]) >> 1;
			if (l[minn] <= r[minn]) {
				in(minn, mid[minn]);
			}
		}
		if (i == n * m) {
			printf("! %d %d", minn, mid[minn]);
			return 0;
		}
	}
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

魔法题。

题目要求我们求 $n$ 个长度为 $2^m-1$ 的递增序列的第 $k$ 小元素。

## 算法 1

暴力求出来一整个数组所有元素并且排序，询问用量 $O(n2^{m})$，期望得分 $10$ 分。

## 算法 2

二分答案，再在每一行二分边界，询问用量 $O(nm\log\max)$，期望得分 $29$ 到 $41$ 分。

## 算法 3

长度 $2^m-1$ 提醒到一个类似于线段树的做法。

我们维护一个 **当前精度** $d$，初始为 $2^{m-1}$，和 **当前长度** $t$，初始为 $1$。

定义当前 **对应序列** 为每一个序列每 $d$ 元素提取出最后一个形成的 $n$ 个序列。 
定义当前 **答案估计** 为对应序列的全局 $\lfloor k\frac{t}{2^m-1}\rfloor$ 小。  
定义当前 **划分** 为对应序列里每一个序列的一个前缀，代表小于答案估计的元素集合。  

初始时候可以暴力提取出来每一个序列的第 $2^{m-1}$ 元素计算答案估计。  
每一轮，会进行如下操作：
 1. 将 $d$ 除以 $2$，将 $t$ 设为 $2t+1$。  
 2. 如果 $d=0$，那么上一轮已经找到答案了，停止。
 3. 先计算这轮的对应序列的划分的一个估计：不用这一轮的答案估计，而用上一轮的答案估计，构造出来这一轮的划分估计。
 4. 从上一轮的划分可以得到每一个序列有一个后缀必须不在划分估计里，有一个前缀必须在划分估计里。
 5. 上一轮的划分的结尾元素紧靠的下一个元素为唯一没有固定位置在划分估计里，我们需要提取它的值并且将它与上一轮的答案估计比较，判断是否加入前缀。
 6. 现在前缀大小会产生偏差。我们想让前缀包含恰好 $\lfloor k\frac{t}{2^m-1}\rfloor$ 元素，但是可能比较的时候导致前缀变更小或更大。定当前所有前缀大小之和为 $x$。
 7. 如果 $x>\lfloor k\frac{t}{2^m-1}\rfloor$，则把前缀外的最小 $x-\lfloor k\frac{t}{2^m-1}\rfloor$ 元素移动进前缀。
 8. 否则把前缀里的最大 $\lfloor k\frac{t}{2^m-1}\rfloor-x$ 值移动出前缀。
 9. 这些步骤直接用 $priority\_queue$ 即可；我们可以重新定义一个类型的 `operator<` 来调用交互库获取值。
 10. 更新答案估计。

最终答案必定为答案估计，由于最终 $t=2^m-1$ 所以最后必须答案估计是第 $k$ 小。  
接下来证明调用次数的复杂度；我们逐轮考虑。

第 5 步会贡献恰好 $n$ 个访问。  
第 10 步会贡献恰好 $n$ 个访问。  
剩下唯一可能贡献访问的地方是 7 和 8。$|\lfloor k\frac{t}{2^m-1}\rfloor-x|$ 是 $O(n)$。我们分别证明（1） $|\lfloor k\frac{t}{2^m-1}\rfloor-2\lfloor k\frac{\frac{t-1}{2}}{2^m-1}\rfloor|=O(n)$ 并且 （2） $|2\lfloor k\frac{\frac{t-1}{2}}{2^m-1}\rfloor-x|=O(n)$。
 1. $k$ 最大这个表达式会最大化；$|\lfloor n(2^m-1)\frac{t}{2^m-1}\rfloor-2\lfloor n(2^m-1)\frac{\frac{t-1}{2}}{2^m-1}\rfloor|=|\lfloor nt\rfloor-2\lfloor n\frac{t-1}{2}\rfloor|$ 然后 $=\lfloor nt\rfloor-2\lfloor n\frac{t-1}{2}\rfloor\le nt-n(t-1)+1=O(n)$
 2. $2\lfloor k\frac{\frac{t-1}{2}}{2^m-1}\rfloor$ 就是在第 5 步前的总共前缀大小，仅添加 $O(n)$ 元素。

于是理论上每一轮需要 $6n$ 访问；但是加一个缓存根本不可能卡到这样。  
询问用量 $O(nm)$，期望得分 $100$ 分。

---

## 作者：bamboo12345 (赞：1)

题意：很简单了，不再赘述。

做法：

# Sub 1：

是人都会。

# Sub 2,3：

我们考虑直接二分值域 $V$，然后在每一个类中去二分出有多少个 $\le x$ 的数去判断即可，询问次数 $O(nm\log V)$，可以通过 Sub 2,3。

# sub 4,5,6：

实在胡不出来部分分了，贴一个满分上来。

考虑我们其实并没有必要每次重新二分，而是可以并行地一起二分。

我们考虑对于现在所有的区间去询问 $mid$ 的值大小，当我们现在 $\sum mid > k$ 的时候，我们就让 $mid$ 值最大的 $r=mid$，因为他一定不可能选得更大；否则我们就让最小的 $l=mid$。

显然操作次数 $O(nm)$。

提一嘴，实现上记得开 `long long`，左闭右闭好写程度  >>> 左闭右开。

---

## 作者：wolfind (赞：1)

~~太魔法了。~~

这里提供一个稳定查询 $nm$ 次的二分做法。

按照我的习惯还是按照思路顺序来说。

首先上来就应该能想到如何 $O(nm)$ 去判断一个位置 $(i,j)$ 是不是第 $k$ 小。

废话，直接每类二分出来最后一个比 $(i,j)$ 小的位置不就好了？

![](https://cdn.luogu.com.cn/upload/image_hosting/ym96tovd.png)

如图，红线是二分出来的位置，那么我们就可以看看红线左边是不是有恰好 $k$ 个数字判断 $(i,j)$ 是不是第 $k$ 小的数。

每类二分一下复杂度是 $O(m)$，$n$ 类复杂度就是 $O(nm)$ 。如果再套一个对第 $k$ 小的数值大小的二分，就可以做到 $O(nm log10^{18})$，~~就是拿不到什么分~~。

其实这里就提示了我们一个想法。

我们不用 $k$ 去二分红线，而是**用红线去二分 $k$ 呢？**

![](https://cdn.luogu.com.cn/upload/image_hosting/lr74nti1.png)

假设我们在每一类随便选了一个位置作为红线所在的位置。

不妨把红线前的一个数都求出来，从小到大设为 $a<b<c<d$ 。

那么，我们把红线左边的数字总数设为 $s$ ，就会有：

1. $d$ 的排名一定大于等于 $s$。

2. $a$ 的排名一定小于等于 $s-n+1$ （这里减的 $n-1$ 是因为还有  $b,c,d$ 比它大）

都是很显然的事情，那么接下来我们怎么做呢？

全都一起二分！

如图，我们每类都有个二分边界 $l_i,r_i$ 并且把中点 $m_i$ 设为红线取的地方。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ur9q9d4.png)

然后找到所有中点大小最小的记为 $m_p$ ，最大的记为 $m_q$。

再记 $s=\sum\limits^{n}_{i=1}m_i$，那么：

1. $s-n+1\le k$ ，则令 $l_p=m_p$。

2. $s\ge k$ ， 则令 $r_q=m_q$。

可以发现上面两个条件至少有一个成立，所以可以不断缩小范围，最后就做完啦，~~怎么可能~~

## 细节

这题我想到这个做法之后调了2个小时才终于做出来，主要还是这个二分方法实在是太奇怪了，有很多细节要考虑。

### 1.越界！！！

![](https://cdn.luogu.com.cn/upload/image_hosting/drxyjr7j.png)

可以发现，有可能有一行非常大，这时候红线应该会二分到 $0$ ，但是这里显然是不能去问的。

有一种办法就是直接把 $0$ 的位置设成负数，当然我的办法很奇怪，~~大家就不用管了~~。（想看去代码看看？）

### 2.死循环。。。

众所周知，二分的时候一般会有两种写法：

```cpp
mid=(l+r)>>1;
if(判断) l=mid+1;
else r=mid;

mid=(l+r+1)>>1;
if(判断) r=mid-1;
else l=mid;
```

但是无论哪种，都得有个 $mid+1$ 或 $mid-1$ 。

所以我们改改原来的二分：

1. $s-n+1 < k$ ，则令 $l_p=m_p+1$。

2. $s\ge k$ ， 则令 $r_q=m_q$。

注意，第一种的等于情况没了。

但是，还有一个更加重要的情况：有某几行的 $l$ 等于 $r$ 了！

为什么要注意？比如下面这个情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/p7wnqyj4.png)

第三、四行的 $l$ 和 $r$ 已重合，但是其中一个一直占着最小值，另一个一直占着最大值，导致其他的无法继续二分下去。

那么我们怎么办呢？

直接跳过那些 $l=r$ 的！

因为它们已经二分完了，既然确定了那就直接不再考虑它们就好了！

但是这时候要注意，我们的二分判断条件会变！（就这卡了我1个小时）

比如说上面这个图，我们会发现，$b$ 的排名并不是一定小于 $s-n+1$，而是要注意小于它的还有一个 $a$ ！所以要再减 1 ！

具体在代码中实现就是先跳过 $l=r$ 的，找到最小的 $m_p$，再在 $l=r$ 的那些地方去看有多少 $m_i<m_p$ ，把二分判断的条件进行修改。

这题就终于做完了。

我的代码写的比较烂，如果实现的和我同学一样好的话其实是只用700B左右的。

```cpp
#include<bits/stdc++.h>
#define N 51
#define M (1<<11)
#define ll long long
using namespace std;
int n,m,k,Th;
int l[N],r[N],mid[N],s;
ll a[N][M];
struct node
{
	ll v;
	int x,y;
}b[N*M];
bool operator <(const node x,const node y)
{
	return x.v<y.v;
}
int cmp(node x,node y)
{
	return x.v>y.v;
}
ll ask(int x,int y)
{
	if(a[x][y]!=0)return a[x][y];
	cout<<"? "<<x<<" "<<y<<endl;
	cin>>a[x][y];
	return a[x][y];
}
int main()
{
	cin>>n>>m>>k>>Th;
	if(n==1&&m==1&&k==1)
	{
		cout<<"! "<<1<<" "<<1<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++)
		a[i][0]=-i,l[i]=1,r[i]=(1<<m)-1,mid[i]=(l[i]+r[i])>>1;
	while(1)
	{
		int t=0;
		s=0;
		for(int i=1;i<=n;i++)
		{
			if(l[i]!=r[i])t=1;
			s=s+mid[i];
		}
		if(!t)break;
		ll mi=0;
		int p;
		for(int i=1;i<=n;i++)
			if(l[i]!=r[i])
			{
				if(ask(i,mid[i])<mi||mi==0)
				{
					mi=ask(i,mid[i]);
					p=i;
				}
			}
		int tx=0;
		for(int i=1;i<=n;i++)
			if(l[i]==r[i])
				if(ask(i,l[i])<ask(p,mid[p]))
					++tx;
		if(s-n+1+tx<k)
		{
			l[p]=mid[p]+1;
			mid[p]=(l[p]+r[p])>>1;
		}
		else
		{
			ll ma=-n-1;
			for(int i=1;i<=n;i++)
				if(l[i]!=r[i])
				{
					if(ask(i,mid[i])>ma)
					{
						ma=ask(i,mid[i]);
						p=i;
					}
				}
			r[p]=mid[p];
			mid[p]=(l[p]+r[p])>>1;
		}
	}
	s=0;
	for(int i=1;i<=n;i++)
		s=s+l[i];
	int len=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=l[i];j<=r[i];j++)
		{
			b[++len].v=ask(i,j);
			b[len].x=i;
			b[len].y=j;
		}
	}
	sort(b+1,b+1+len);
	k=k-s+n;
	cout<<"! "<<b[k].x<<" "<<b[k].y<<endl;
	return 0;
}
```


---

## 作者：Albert_Wei (赞：0)

考虑 $n$ 个序列同时二分。设目前每个序列二分的左右边界为 $[l_1, r_1), [l_2, r_2), \cdots, [l_n, r_n)$，取中点为 $mid_1, mid_2, \cdots, mid_n$，若 $\sum\limits_{i = 1} ^ n mid_i \ge k$，我们将查询到的重要度最高的 $mid_j$ 的 $r_j$ 变为 $mid_j$，否则同理将重要度最低的 $mid_j$ 对应的 $l_j$ 变为 $mid_j$。考虑分析复杂度，我们每个区间的 $l, r$ 总共只会移动 $m$ 次，而每次二分只需要多查询一个点（即有断点移动的序列新的 $mid$）的重要度，故至多查 $nm$ 次。
```cpp
/*******************************
| Author:  Albert_Wei
| Problem: P7329 「MCOI-07」Dream and More Discs
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/P7329
| When:    2025-07-25 08:17:46
| 
| Memory:  250 MB
| Time:    2000 ms
*******************************/
#include <bits/stdc++.h>
#define int long long
#define F(i, l, r) for (int i = l; i <= r; i ++)
#define G(i, r, l) for (int i = r; i >= l; i --)
using namespace std;

const int N = 1e6 + 5;

int read() {
    char c = getchar(); int x = 0, p = 1;
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') p = -1, c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * p;
}

int n, m, k, l[N], r[N], mid[N], val[N], T;

int query(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    return read();
}

signed main() {
    n = read(), m = read(), k = read(), T = read();
    F(i, 1, n) l[i] = 0, r[i] = (1 << m), mid[i] = (1 << m - 1);
    F(i, 1, n) val[i] = query(i, mid[i]);
    F(s, 1, n * m) {
        int smid = 0;
        F(i, 1, n) smid += mid[i]; 
        auto upd = [&](int id) {
        	mid[id] = (l[id] + r[id]) >> 1;
        	if (r[id] != l[id] + 1) val[id] = query(id, mid[id]);
        };
        if (smid > k) {
            int id = 1;
            F(i, 1, n) if (r[i] > l[i] + 1 && (r[id] == l[id] + 1 || val[i] > val[id])) id = i;
            r[id] = mid[id], upd(id);
        	if (s == n * m) cout << "! " << id << ' ' << mid[id] << '\n';
        } else {
            int id = 1;
            F(i, 1, n) if (r[i] > l[i] + 1 && (r[id] == l[id] + 1 || val[i] < val[id])) id = i;
            l[id] = mid[id], upd(id);
        	if (s == n * m) cout << "! " << id << ' ' << mid[id] << '\n';
        }
    }
    return 0;
}

/*
n = 3, m = 3, k = 10
1 3 5 7 9 11 13
2 4 6 8 10 12 14
15 16 17 18 19 20 21
*/ 

```

---

