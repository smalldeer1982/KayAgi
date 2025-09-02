# Views Matter

## 题目描述

You came to the exhibition and one exhibit has drawn your attention. It consists of $ n $ stacks of blocks, where the $ i $ -th stack consists of $ a_i $ blocks resting on the surface.

The height of the exhibit is equal to $ m $ . Consequently, the number of blocks in each stack is less than or equal to $ m $ .

There is a camera on the ceiling that sees the top view of the blocks and a camera on the right wall that sees the side view of the blocks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061B/f0bac26a304f5339f8800747dc3cc95aa0eba485.png)Find the maximum number of blocks you can remove such that the views for both the cameras would not change.

Note, that while originally all blocks are stacked on the floor, it is not required for them to stay connected to the floor after some blocks are removed. There is no gravity in the whole exhibition, so no block would fall down, even if the block underneath is removed. It is not allowed to move blocks by hand either.

## 说明/提示

The following pictures illustrate the first example and its possible solution.

Blue cells indicate removed blocks. There are $ 10 $ blue cells, so the answer is $ 10 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061B/5c39371a94179ca28ceb7e2172bc3ac014dca01f.png)

## 样例 #1

### 输入

```
5 6
3 3 3 3 3
```

### 输出

```
10```

## 样例 #2

### 输入

```
3 5
1 2 4
```

### 输出

```
3```

## 样例 #3

### 输入

```
5 5
2 3 1 4 4
```

### 输出

```
9```

## 样例 #4

### 输入

```
1 1000
548
```

### 输出

```
0```

## 样例 #5

### 输入

```
3 3
3 1 1
```

### 输出

```
1```

# 题解

## 作者：きりと (赞：4)

### 题目大意

见翻译。

表白翻译qwq，简直是你谷CF题的翻译里的一股清流，简单明了地把所有条件都说清楚了。 ![qq](https://cdn.luogu.com.cn/upload/pic/62224.png)

### 解题思路

这题细节有点小多。

首先能想到的是：我们要尽量让对于从最大高度向下的每一行，存在尽可能少且不为零的方块，这样才能使 $ans$ 最大。

然后又能发现，从俯视图来看，每列都得至少有一个方块。

那么可以发现，对于某些每层只有一个的方块来说，必须保留，我们称这种方块为唯一方块。而对于出现多次的，保留一个就彳亍，这个被保留的要优先给不存在唯一方块的列。

可以预料的是，将每一列上的方块数从大到小排序后，一定有一种情况，可以得到最大的 $ans$：

我们定义一个指针 $cnt$ ，表示 $>cnt$ 的行数每行一个方块。

- 当第 $i$ 列中， $cnt>a[i+1]$ 时，直接把第 $i$ 行多出来的保留，剩下的果断舍弃。
- 反之，我们只需要保留当前列的第 $cnt$ 个数字，去除剩下的，由 $cnt$ 的定义可以保证其正确性。

具体还是要看代码实现，个人认为此题难点不在思路而在代码实现细节。

$m$ 是没啥用的干扰项，~~毕竟足足亲 $m$ 何足挂齿~~。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define forr(i,l,r) for(int i=l;i<=r;i++)
#define ffor(i,r,l) for(int i=r;i>=l;i--)
#define int long long
const int N=1e5+10;
int a[N];
bool cmp(int q,int p)
{
    return q>p;
}
signed main()
{
    int n,m;
    cin>>n>>m;
    forr(i,1,n)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    int ans=0,cnt=a[1];
    forr(i,1,n-1)
    {
        if(cnt>a[i+1])
        {
            ans+=a[i+1]+a[i]-cnt;
            cnt=a[i+1];
        }
        else
        {
            ans+=a[i]-1;
            cnt=max(cnt-1,1LL);   //cnt必须为正，原因显然。
        }
    }
    cout<<ans+a[n]-cnt<<endl;   //最后一位要单独处理，因为此时下一列是0。
}

```

---

## 作者：封禁用户 (赞：2)

## CF1061B Views Matter 题解
$\text{Update}$：更改了一点格式问题，麻烦管理员了。
###  题目思路

这道题我们可以用**贪心**解决。

首先，我们将这个图形按照小方块的数量进行升序排序，方便后续操作。

观察可得：

- 向右保留会导致剩余列数 $-1$，剩余行数不变。

- 向右上保留会导致剩余列数 $-1$，剩余行数 $-1$。
- 向上保留会导致剩余列数不变，剩余行数 $-1$。

每一次如果能够向右上保留，则向右上保留，否则向可行的方向保留即可。

因为已经进行过了升序排列，所以我们可以得知在到达图形末尾前，我们可以保证向右保留或向右上保留可行。

到达图形末尾时有两种可能的情况：

1. 保留到了右上角的方块
2. 没有保留到右上角的方块

对于情况 $1$：我们不需要做任何额外操作

对于情况 $2$：我们需要再保留最后一列中已经保留的方块上面的所有方块。

这时，我们可以保留最少的方块数。其余方块均可移除。

让我们来研究一下样例加深理解：

对于样例 $\#3$:
![输入数据对应的图表](https://cdn.luogu.com.cn/upload/image_hosting/5xeu9hek.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们先对数据进行排序：

![排序后的结果](https://cdn.luogu.com.cn/upload/image_hosting/l4ehfnnn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然后进行以上操作：

![1](https://cdn.luogu.com.cn/upload/image_hosting/5vp3a0pk.png?x-oss-process=image/resize,m_lfit,h_170,w_225) ![2](https://cdn.luogu.com.cn/upload/image_hosting/l6zfozpx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

计算得出，图形中共有 $15$ 个小方块，我们最少保留 $5$ 个，即最多移除 $10$ 个方块，可以保证，此时是最优的解法之一。

对于样例 $\#5$:
![输入数据对应的图表](https://cdn.luogu.com.cn/upload/image_hosting/ng76725w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们先对数据进行排序：

![排序后的结果](https://cdn.luogu.com.cn/upload/image_hosting/szqjadj3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然后进行以上操作：

![1](https://cdn.luogu.com.cn/upload/image_hosting/iq06r764.png?x-oss-process=image/resize,m_lfit,h_170,w_225) ![2](https://cdn.luogu.com.cn/upload/image_hosting/3nzhkw8f.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在这个样例中，保留到结尾行时并没有到达图形的左上角，所以选取保留图形之上的所有方块保留。

计算得出，图形中共有 $5$ 个小方块，我们最少保留 $4$ 个，即最多移除 $1$ 个方块。



### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , a[100005] , h = 0 , need = 0;
long long cnt = 0;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 0 ; i < n ; i++)
	{
		cin >> a[i];
		cnt += a[i];
	}
	sort(a , a + n);
	for(int i = 0 ; i < n ; i++)
	{
		if(a[i] > h)
		{
			h++;
		}
	}
	need = a[n - 1] + n - h;
	cout << cnt - need;
	return 0;
}
```

---

## 作者：一扶苏一 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10212991.html)

## Description

给定一个只有一行的，由 $n$ 组小正方体组成的方块，每组是由 $a_i$ 块小正方体竖直堆叠起来的，求最多能抽掉多少块使得它的左视图和俯视图不变。方块不会掉落

## Input

第一行是两个整数 $n~,~m$，代表方块组数和另一个没什么卵用的参数。

下面一行 $n$ 个数字，代表 $a_i$

## Output

一行一个数字代表答案

## Hint

$1~\leq~n~\leq~10^5,1~\leq~a_i~\leq~10^9$

## Solution

总感觉这场cf是自闭场啊……B题就开始自闭了……38min才过B

考虑因为只有一行同时要求俯视图不变，所以等价于要求每组上都必须留至少一个小正方体。再考虑左视图，相当于每个高度上都至少有一个。于是我们发现原来每组间的顺序是无所谓的，于是我们将他们按照高度排序。

现在我们考虑相邻两个，我们设右侧的一组 $B$ 较高，左侧的一组 $A$ 较低，则显然需要用 $B$ 和它右侧的正方体组填充满 $A$ 和 $B$ 之间高度差的一块。在这一些方块中我们选哪一组进行填充对左视图是没有影响的，但是 $B$ 和 $B$ 右侧如果有没有被选择过被留下的组，那么它必须在最下面一行被选择从而保证这一组的俯视图不变。如果我们选择这样没被选择的组进行填充，那么它们就不用在最下面一行被选择了，相当于节省了一个方块。所以我们维护扫描到当前位置一共还有多少组没有被选择过，优先选择这一些即可。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#define putchar(o) puts("I\
am a  cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;

int n, m;
ll ans;
int MU[maxn];
bool vis[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(m);
	for (rg int i = 1; i <= n; ++i) {
		qr(MU[i]);
		ans += MU[i];
	}
	std::sort(MU + 1, MU + 1 + n);
	int pre = 0;
	for (rg int i = n; i; --i) {
		++pre;
		pre -= MU[i] - MU[i - 1];
		ans -= MU[i] - MU[i - 1];
		pre = std::max(0, pre);
	}
	qw(ans - pre, '\n', true);
	return 0;
}
```



---

## 作者：huang0409 (赞：2)


我们可以计算需要保留的有多少，然后总数减去这些，就是能够去掉的。
首先对数组进行排序，假设一开始高度是０，碰到第一个大于当前高度的，高度加１，这些是必须要保留的，然后再计算最后一个和当前的高度差，这也是不能去掉的，然后每一行必须保留一个，最后再减去就可以了。

```

```


---

## 作者：QWQ_123 (赞：0)

思路比较简单。

考虑从上往下依次放。

就是说先将 $a$ 从大到小排序。

然后第一个位置保留填 $a_1$，第二个位置保留 $a_1-1$，若第二个位置 $< a_1-1$ 那么考虑从 $a_i+1 \sim a_1-1$ 这一段都要在第一个位置保留，然后依次类推。

具体看代码罢。

```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m;
int a[100010];
long long sum = 0;

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]), sum += 1ll * a[i];
	if (n == 1) {
		puts("0");
		return 0;
	}
	sort(a + 1, a + 1 + n);
	reverse(a + 1, a + 1 + n);
	int ans = 1;
	int nowid = a[1] - 1;
	for (int i = 2; i <= n; ++i) {
		// cout << nowid << ' ' << a[i] << endl;
		if (nowid > a[i]) {
			ans += nowid - a[i];
	 		nowid = a[i];
		}
		if (nowid > 0) {
			++ans;
			nowid--;
		} else if (a[i]) ++ans;
	}

	if (nowid) ans += nowid;

	// cout << ans << endl;

	printf("%lld\n", sum - ans);

	return 0;
}
```

---

