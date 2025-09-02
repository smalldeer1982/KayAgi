# 「DBOI」Round 1 DTTM

## 题目背景

张则雨和穆制程坐在天台上看着满天的星辰。在他们的世界，流行一种连接星星的活动。他们对此有一种浪漫的诠释：如果连不完，剩下的一颗星星就是身旁的人；如果连得完，那身边的人和自己都是星星。

## 题目描述

星空中有 $n$ 颗星星，第 $i$ 颗位于坐标 $(x_i,y_i)$。你需要把星星连接成满足张则雨的如下需求：

- 每一颗星星都是且仅是一条线段的端点，所有线段互不相交（包括端点）。
- 所有线段左右端点 $|x_l-x_r|$ 之和有最小值。 

然而张则雨有点笨，并不知道应该怎么连。穆制程知道你是地球上最聪明的人，于是告诉你 $n$ 颗星星的坐标，你需要输出连接方案或者报告无解。

## 说明/提示

样例 1 的方案如图：

![](https://s1.ax1x.com/2023/04/06/ppomH5q.png)

样例 2 的方案如图：

![](https://s1.ax1x.com/2023/04/06/ppomDDH.png)

**本题使用捆绑测试与子任务依赖。**

| $\rm Subtask$ | $n\leqslant$ | $(x,y)$ | 特殊性质 | 得分 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $10$ | $0\leqslant x,y\leqslant 20$ | 无 | $10$ | 无 |
| $2$ | $10^3$ | $0\leqslant x,y\leqslant10^3$ | 无 | $15$ | $1$ |
| $3$ | $10^3$ | $0\leqslant x,y\leqslant10^9$ | 无 | $15$ | $1,2$ |
| $4$ | $5\times10^5$ |$-10^9\leqslant x,y\leqslant10^9$  | $A$ | $5$ | 无 |
| $5$ | $5\times10^5$ | $-10^3\leqslant x,y\leqslant10^3$ | 无 | $20$ | $1,2$
| $6$ | $5\times10^5$ | $-10^9\leqslant x,y\leqslant10^9$ | 无 | $35$ | $1,2,3,4,5$


特殊性质 $A$：满足所有 $x_i$ 都相等。

保证对于 $100\%$ 的数据，$1\leqslant n\leqslant5\times 10^5$，$0\leqslant|x|,|y|\leqslant 10^9$ 且对于任意 $i\ne j$，有 $(x_i,y_i)\neq (x_j,y_j)$。

## 样例 #1

### 输入

```
4
1 3
2 2
2 1
3 4```

### 输出

```
2
1 4
2 3```

## 样例 #2

### 输入

```
6
1 5
2 3
2 4
2 5
2 -1
3 -3```

### 输出

```
2
1 3
4 6
2 5```

# 题解

## 作者：wmrqwq (赞：7)

# 原题链接

[P9397 「DBOI」Round 1 DTTM](https://www.luogu.com.cn/problem/P9397)

# 题目简述

现在星空中有 $n$ 颗星星，每颗星星位于不同的坐标上，现在要满足以下两个要求：

1. 每一颗星星都是且仅是一条线段的端点，所有线段互不相交（包括端点）。

2. 所有线段左右端点 $|x_l-x_r|$ 之和有最小值。

现在需要得到线段左右端点 $|x_l-x_r|$ 之和的最小值以及连接方案，如果无解，就输出 $-1$。

# 解题思路

首先，我们考虑无解的情况，不难看出，如果 $n$ 为奇数，那么是一定无解的，因为到最后必定会有一颗星星不能与其他星星连接，这时，直接输出 $-1$ 即可。若 $n$ 为偶数，则现将所有的星星按照 $x$ 排序，如果 $x$ 相等就继续按照 $y$ 排序，最后只需要再讲将相邻的两个星星连线即可，这时就需要定义一个结构体：

```cpp
struct node
{
	int x,y,id;
}a[1000010];
```

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,sum;
#define QwQ return 0;
struct node
{
	int x,y,id;
}a[1000010];
bool cmp(node a,node b)
{
	if(a.x==b.x)//如果两颗星星的x轴相等
		return a.y<b.y;//就继续比较y轴
	return a.x<b.x;//否则直接比较x轴
}
int main()
{
	cin>>n;	
	if(n%2)//如果星星的数量为奇数，那么就直接输出-1
	{
		cout<<-1<<endl;
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		cin>>a[i].x>>a[i].y;//输入每个星星的x轴以及y轴
		a[i].id=i+1;//定义每颗星星的编号
	}
	sort(a,a+n,cmp);//将星星按照顺序排序
	for(int i=0;i<n;i+=2)
		sum+=a[i+1].x-a[i].x;//让相邻两颗星星的x相减，使其最小
	cout<<sum<<endl;//输出这个最小值
	for(int i=0;i<n;i+=2)
		cout<<a[i].id<<" "<<a[i+1].id<<endl;//输出这两颗星星的编号
	QwQ;//华丽的结束
}//clbzdq
```

---

## 作者：Shunpower (赞：4)

出题人题解。

考虑贪心，把 $x$ 坐标相同的点压在一起，同一 $x$ 坐标内 $y$ 从小往大排序。

考虑将 $x$ 坐标从小到大扫一遍，对于 $x=i$ 时，考虑当前坐标上的可用点数，如果为偶数直接内部消化匹配（$y$ 坐标最大的匹配次大的并且以此类推），如果为奇数考虑将 $y$ 坐标最小的点连到下一个 $x$ 坐标中 $y$ 最大的点上，这样可以保证不相交，剩下的内部消化匹配。

考虑按照同一 $x$ 坐标压在一起后一个组里的奇偶性。注意到必然有偶数个奇数组，否则点数为奇数，无解。很容易发现答案即为第 $1,2$ 个奇数组的 $x$ 坐标差加上第 $3,4$ 个、第 $5,6$ 个……第 $c,c+1$ 个的差。

如果需要证明，可以考虑，我们实际上是要两两配对所有奇数组，然后使得 $x$ 坐标差的和最小。只有上面说的那种配对方式能够达到答案下界。同时，由于任意两个奇数组之间都是偶数组，因此按照最初说的方式构造一定能保证达到下界且线段不交。

------------

下面是 std。

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rer(i, l, r, a) rep1(i, l, r) read(a[i])
#define ptc putchar
#define il inline
#define eb emplace_back
#define fst first
#define snd second
#define rout return 0
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 5e5 + 10;
namespace stupid_lrc {
	template <typename T> il bool read(T &x) {
		x = 0; bool f = false; char ch;
		while (!isdigit(ch = getchar())) {
			f ^= !(ch ^ '-');
			if (ch == EOF) return false;
		}
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
		if (f) x = ~x + 1; return true;
	}
	il int read() {int x; read(x); return x;}

	template <typename T> il bool read(pair <T, T> &x) {return read(x.fst) && read(x.snd);}

	template <typename T, typename ...L>
	il bool read(T &x, L &...y) {return read(x) && read(y...);}

	template <typename T> il T lowbit(const T &x) {return x & -x;}
}
using namespace stupid_lrc;
int n; pii a[MAXN];
ll ans; map <int, vector <pii> > pos;
vector <pii> now, opt;

int main() {
	read(n); rer(i, 1, n, a);
	if (n & 1) return puts("-1"), 0;
	rep1(i, 1, n) pos[a[i].fst].eb(a[i].snd, i);
	int lst = 0;
	for (auto &v : pos) {
		sort(v.snd.begin(), v.snd.end());
		if (lst) now.eb(v.fst, v.snd.rbegin() -> snd), v.snd.pop_back(), lst = 0;
		if (v.snd.size() & 1) now.eb(v.fst, v.snd.rbegin() -> snd), v.snd.pop_back(), lst = 1;
		int len = v.snd.size();
		rep1(i, 0, len - 1) opt.eb(v.snd[i].snd, v.snd[i + 1].snd), ++i;
	} int len = now.size();
	rep1(i, 0, len - 1) ans += now[i + 1].fst - now[i].fst, opt.eb(now[i].snd, now[i + 1].snd), ++i;
	printf("%lld\n", ans);
	for (auto v : opt) printf("%d %d\n", v.fst, v.snd);
	rout;
}
```

当然，在赛时提交记录中有更加优美的写法。

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 P9397 「DBOI」Round 1 DTTM](https://www.luogu.com.cn/problem/P9397)

## 解题思路

1. 每一颗星星都是且仅是一条线段的端点，一共有 $n$ 个端点，每一条线段有 $2$ 个端点，显然 $n$ 为奇数时无解，输出 `-1`。

2. 将线段按照 $x$ 坐标，再按照 $y$ 坐标排序。

3. 每次连接 $x$ 坐标相邻的星星，即可使 $x$ 坐标的差尽可能小，也不会出现相交的线段。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=500005;
struct Node
{
	int x,y,id;
}a[N];
bool cmp(Node u,Node v)
{
	if(u.x!=v.x)return u.x<v.x;
	return u.y<v.y;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		a[i].id=i;
	}
	if(n&1)
	{
		cout<<"-1"<<'\n';
		return 0;
	}
	sort(a+1,a+n+1,cmp);
	int sum=0;
	for(int i=1;i<=n;i+=2)
	{
		sum+=a[i+1].x-a[i].x;
	}
	cout<<sum<<'\n';
	for(int i=1;i<=n;i+=2)
	{
		cout<<a[i].id<<' '<<a[i+1].id<<'\n';
	}
	return 0;
}
```

---

## 作者：回声之歌 (赞：2)

- 若所有 $\mid x_l - x_r \mid$ 之和有最小值，则考虑贪心构造每组 $\mid x_l - x_r \mid$ 最小衍至最值。因所有纵坐标 $y$ 不对最值产生影响，则对于所有坐标，可以横坐标 $x$ 为第一关键字升序排序，那么对于 $\forall i \in \left[1, n - 1 \right]$，$x_{i + 1} - x_i$ 均有最小值，则按顺序依次连结每两个坐标，此时 $cost = x_2 - x_1 + x_4 - x_3 + \dots + x_n - x_{n - 1}$，值最小。

	以样例为例，对于输入 1，对所有坐标排序后，连结点 1 $\left(1, 3 \right)$ 与点 2 $\left(2, 1 \right)$，连结点 2 $\left(2, 2 \right)$ 与点 4 $\left(3, 4 \right)$，得 $cost = 2$；对于输入 2，对所有坐标排序后，连结点 1 $\left(1, 5 \right)$ 与点 5 $\left(2, -1 \right)$，连结点 2 $\left(2, 3 \right)$ 与点 3 $\left(2, 4 \right)$，连结点 4 $\left(2, 5 \right)$ 与点 6 $\left(3, -3 \right)$，得 $cost = 2$。以上两组构造皆满足分析且符合题意。

核心代码：
```cpp
struct node {
	int x, y, z;
	bool operator<(const node &b)const {return x < b.x;}
} a[500005];
sort(a, a + n);
for (int i = 0; i < n; cost += a[i + 1].x - a[i].x, i += 2);
```
- 若所有线段互不相交，试构造线段 $l_1, l_2$ 分析。设线段 $l_1$ 的端点为 $\left(x_1, y_1 \right), \left(x_2, y_2 \right) \left(x_1 \le x_2, y_1 \le y_2 \right)$，线段 $l_2$ 的端点为 $\left(x_3, y_3 \right), \left(x_4, y_4 \right) \left(x_3 \le x_4, y_3 \le y_4 \right)$，若对于所有坐标排序后，$\left(x_1, y_1 \right), \left(x_2, y_2 \right), \left(x_3, y_3 \right), \left(x_4, y_4 \right)$ 相邻，则有 $x_1 \le x_2 \le x_3 \le x_4$。当 $x_1 = x_2 = x_3, x_2 = x_3 = x_4$ 满足其一或全部满足时，若 $y_3 \le y_2 \le y_4$ 或 $y_1 \le y_3 \le y_2$，则线段相交，不合题意。
	
    若对于所有坐标，以纵坐标 $y$ 为第二关键字升序排序，则对于 $\left(x_1, y_1 \right), \left(x_2, y_2 \right), \left(x_3, y_3 \right), \left(x_4, y_4 \right)$，有 $y_1 \le y_2 \le y_3 \le y_4$，不满足 $y_3 \le y_2 \le y_4$ 和 $y_1 \le y_3 \le y_2$，对于任意线段 $l_i, l_j$ 皆同理，则满足题意。
    
核心代码：
```cpp
bool operator<(const node &b)const {
	if (x == b.x)return y < b.y;
	return x < b.x;
}
```
- 对于 $n$ 个坐标，若能满足题意地构造出 $k$ 个线段使有解，则必有 $n = 2k$，则 $n$ 为偶数；那么对于 $n$ 个坐标，若不能满足题意地构造出线段使无解，则 $n$ 为奇数。

核心代码：
```cpp
if (n & 1)printf("-1");
```

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO {
	int read() {
		int x = 0, f = 1;
		char c = getchar();
		while (c < '0' || c > '9') {
			if (c == '-')f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + (c ^ 48);
			c = getchar();
		}
		return x * f;
	}
	void write(int x) {
		if (x > 9)write(x / 10);
		putchar(x % 10 + 48);
	}
	void wrsp(int x) {write(x), putchar(' ');}
	void wrln(int x) {write(x), putchar('\n');}
} using namespace IO;
struct node {
	int x, y, z;
	bool operator<(const node &b)const {
		if (x == b.x)return y < b.y;
		return x < b.x;
	}
} a[500005];
int n, ans;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)a[i] = {read(), read(), i};
	if (n & 1)printf("-1");
	else {
		sort(a, a + n);
		for (int i = 0; i < n; ans += a[i + 1].x - a[i].x, i += 2);
		wrln(ans);
		for (int i = 0; i < n; wrsp(a[i].z + 1), wrln(a[i + 1].z + 1), i += 2);
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
一道稍加分析就可以做出来的题。
## 分析。
因为一条线段必定有两个端点，所以 $n$ 必须为复数，否则无解。

使左右端点绝对值的和最小，那么就要让相近的两个端点组成一条线段，我们可以先将每个端点的 $x$ 坐标排序，再将 $y$ 坐标排序，这样我们就可以看出每个端点距离坐标轴的远近。从而从左到右将 $x$ 坐标相邻的的端点连起来，因为坐标不可能相同，同时每个坐标点又是有序的，所以不可能出现相交的线段。

这样就可以满足题意。

同时因为我们是从左到右，从小到大两两相连，所以也可以保证左右端点的绝对值最小。

因为两两相连，所以注意在连线的时候 $i$ 每次要加二。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
using namespace std;
int n,ans;
struct node{
	int x,y,z;
}a[500005];
bool cmp(node p1,node p2){//自定义排序
	return (p1.x==p2.x)?p1.y<p2.y:p1.x<p2.x;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].z=i;
	}
	if(n%2==1){//判断n是否为复数
		cout<<"-1\n";
	}
	else{
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i+=2){
			ans+=a[i+1].x-a[i].x;
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i+=2){
			cout<<a[i].z<<" "<<a[i+1].z<<"\n";
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：66xyyd (赞：1)

该题解假设读者已经理解题目大意。

拿到题目，我们首先注意到第二个要求：

> - 所有线段左右端点 $|x_l-x_r|$ 之和有最小值。

也就是说这个最值问题只用比较 $x$。那么为了避免被浪费，我们应该让所有 $x$ 相邻的点链接成线段。因此我们对于样例可以这样构造解法（样例解释的解法具有一定误导性）：

![样例1](https://cdn.luogu.com.cn/upload/image_hosting/8pfcez5e.png?x-oss-process=image/resize,m_lfit,h_600,w_1000)

![样例2](https://cdn.luogu.com.cn/upload/image_hosting/9bavag4g.png?x-oss-process=image/resize,m_lfit,h_600,w_1000)

那么对于最优解的构造就可以这样：把所有点按 $x$ 排序，然后每两个点一连，计算最小值，输出。当然，我们还要审查第一个要求：

> - 每一颗星星都是且仅是一条线段的端点，所有线段互不相交（包括端点）。

让我们假设这样一个矛盾：有两个线段 $a$ 和 $b$，它们是交叉的，但是却满足我们的构造。但是这会引来一个显然的矛盾：$a$ 的右端点一定在 $b$ 的左端点的右方。这样的话，程序实际上会把 $a$ 的左端点和 $b$ 的左端点相连，把 $a$ 的右端点和 $b$ 的右端点相连。这两条线段 $a'$ 和 $b'$ 就不同于 $a$ 和 $b$，并且不再相交。因此我们的构造是符合要求的。

最后，还要注意如果 $n$ 为奇数，那么会剩下来一个点，因此要输出 `-1`。

代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int x,y,id;
}a[500001];
int n;
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	if(n&1){
		cout << "-1\n";
		return 0;
	}
	for(int i=0;i<n;i++){
		cin >> a[i].x >> a[i].y;
		a[i].id=i+1;
	}
	sort(a,a+n,[](const node &lhs,const node &rhs){return lhs.x==rhs.x?lhs.y==rhs.y?lhs.id<rhs.id:lhs.y>rhs.y:lhs.x<rhs.x;});
	long long summ=0;
	for(int i=0;i<n;i+=2){
		summ+=a[i+1].x-a[i].x;
	}
	cout << summ << '\n';
	for(int i=0;i<n;i+=2){
		cout << a[i].id << ' ' << a[i+1].id << '\n';
	}
	return 0;
}
```


---

## 作者：OcTar (赞：1)

## 题目传送门

[P9397 「DBOI」Round 1 DTTM](https://www.luogu.com.cn/problem/P9397)

## 题目分析
先来简化一下题意，平面上有 $n$ 个点，你要构造一种连接方式使得：

- $|x_l-x_r|$ 最小；

- 每个点最多连一条线且连线不能相交。

我们立即想到这是一道贪心题，现在考虑贪心策略。

首先必须要所有点两两连接，所以当 $n$ 为奇数时必然有一个点单出来，此时无解。

当 $n$ 为偶数时，我们先把它们“压缩”到数轴上，也就是只考虑横坐标。先对横坐标排序，能够发现我们肯定要连接横坐标相邻的点才能使 $|x_l-x_r|$ 最小。再将问题拓展成平面，解决线段不能相交的问题。我们发现上述连接方式也能够满足要求，完美！（读者可以自己画图举例试试）

于是自定义排序代码如下：

```cpp
struct node {
    int x, y;//点坐标
    int id;//点编号
	//运算符重载
    bool operator < (const node& rhs) const {
        if (x != rhs.x) {
            return x < rhs.x;
        }
        return y < rhs.y;
    }
};
```
完整代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 5e5 + 5;
struct node {
    int x, y;
    int id;
    bool operator < (const node& rhs) const {
        if (x != rhs.x) {
            return x < rhs.x;
        }
        return y < rhs.y;
    }
}a[maxn];
int n, sum;
int main() {
    scanf("%d", &n);
    if (n & 1) {
        printf("-1\n");
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 2; i <= n; i += 2) {
        sum += (a[i].x - a[i - 1].x);
    }
    printf("%d\n", sum);
    for (int i = 2; i <= n; i += 2) {
        printf("%d %d\n", a[i - 1].id, a[i].id);
    }
    return 0;
}
```
~~作者最开始把重载运算符的变量顺序写反了，喜提 $5$ pts的好成绩 (~~

---

## 作者：ccg12345 (赞：1)

## 思路

看到这道题的话我首先考虑到的是贪心与构造，一打开算法标签，确实是贪心与构造。

首先将 $n$ 按奇偶分类，如果 $n$ 是奇数，显然构造到最后会剩下一个点无法与其余点连接，直接输出 `-1` 即可。

若 $n$ 为偶数，则先将所有点先以 $x$ 排序，若 $x$ 相等再以 $y$ 排序，然后就每相邻两个连线即可。

这时候可能有人会问了：万一有两条线段交叉就不符合题意了啊。其实我们可以用反证法来证明必互不相交，若有一种情况满足题意的情况，使得有 $l_1$ 与 $l_2$ 有交点。不妨设 $l_1$ 的端点分别为 $A(x_1, y_1)$ 与 $B(x_2, y_2)$，$l_2$ 的端点分别为 $C(x_3, y_3)$ 与 $D(x_4, y_4)$。那么由我们的构造方式可设 $ x_1 \le x_2 \le x_3 \le x_4$。

易知两条线段相交的充要条件为：

1. 每条线段都分别**跨越**了另一条线段所在直线，即两个端点分别在该直线两侧。

2. 一条线段的端点恰好在另一条线段上。

第二种情况由题知不可能，只可能是第一种情况。

那么如何判断点在直线在哪一侧？

需要用到**叉积**。以点 $C$ 为例，首先以 $A$ 为起点，分别向 $B$ 与 $C$ 建立两个向量，即 $AC(x_3 - x_1, y_3 - y_1)$ 与 $AB(x_2 - x_1, y_2 - y_1)$，两者叉乘 $z = (x_3 - x_1) \times (y_2 - y_1) - (y_3 - y_1) \times (x_2 - x_1)$。

若 $z > 0$，则在右侧。

若 $z < 0$，则在左侧。

若 $z = 0$，则在直线上。

按此方法同理可算出 $D$ 的叉乘值，经验证它们必然在同一侧（留给有心者自行验证），所以矛盾。

附代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x*f;
}
struct mon{
	int x, y, val;
}a[500005] = {};
bool cmp(mon a, mon b)
{
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}
int main()
{
    int n, cnt = 0;
	n = read();
	for(register int i = 1; i <= n; i++)
		a[i].x = read(), a[i].y = read(), a[i].val = i;
	if(n % 2 == 1)
		printf("-1\n");
	else
	{
		sort(a + 1, a + n + 1, cmp);
		for(register int i = 1; i <= n; i += 2)
			cnt += a[i + 1].x - a[i].x;
		printf("%d\n", cnt);
		for(register int i = 1; i <= n; i += 2)
			printf("%d %d\n", a[i].val, a[i + 1].val);
	}
	return 0;
}
```


---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/P9397)
# 题目大意：
给定 $n$ 个点，要用互不相交的线段将它们中每两个点分一组，连一条线（每个点连一次就够了，不是两两连线），求每条线段左右端点横坐标差之和的最小值。
# 思路：
将 $n$ 个点按横坐标升序排序，然后选相邻的点连线，再把线段左右端点横坐标差累加到答案中，这样会使总和尽可能小且互不相交，最后输出答案以及每对点的编号就行了。
# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL n, ans; 
in void read(LL &x){
	x = 0;LL f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + (ch - 48),ch = getchar();}
	x *= f;
}
in void write(LL x){
    if(x < 0){putchar('-');x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
struct no {
	LL x, y, id; 
}a[1001001];
bool cmp(no x, no y) {return x.x < y.x || x.x == y.x  && x.y >  y.y; }
int main(){
	IOS;
	cin >> n; 
	if(n & 1) {cout << -1; return 0; }
	for(re int i = 1; i <= n; i ++) cin >> a[i].x >> a[i].y, a[i].id = i; //输入，并记录第i个点的编号，因为要排序
	sort(a + 1, a + n + 1, cmp); //排序
	for(re int i = 2; i <= n; i += 2) ans += a[i].x - a[i - 1].x; //累加答案
	cout << ans << "\n"; 
	for(re int i = 2; i <= n; i += 2) cout << a[i - 1].id << " " << a[i].id << "\n"; 
	return 0;
}
```

---

## 作者：FSHYLHX (赞：0)

# 思路分析
本题考虑贪心，运用排序，结构体等知识点。首先不考虑相交的情况，发现只用考虑每个点的横坐标即可。运用贪心的思想，可知当两两相邻的点连成一条线段时，能保证线段在横轴上没有重合。且又发现当两两相邻的点连成线段时，一定不会存在相交。
# 注意事项
因为要两两相连，当点数的个数为奇数时，便是无解的情况。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
#define N 500005
struct AB{
	int x, y, z;
}a[N];
bool cmp(AB a, AB b){
	if(a.x == b.x) return a.y < b.y;
	else return a.x < b.x;
}
int i,j,k,m,n,ans,sum;
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d%d",&a[i].x, &a[i].y);
		a[i].z = i;
 	}
	if(n % 2 == 1){
		printf("-1");
		return 0;
	}
	sort(a+1, a+1+n, cmp);
	for(int i=1; i<=n; i+=2) ans += a[i+1].x - a[i].x;
	printf("%d\n", ans);
	for(int i=1; i<=n; i+=2) printf("%d %d\n", a[i].z, a[i+1].z);
    return 0;
} 
```


---

## 作者：ZYH_juruo (赞：0)

# 题目传送门
[P9397 「DBOI」Round 1 DTTM](https://www.luogu.com.cn/problem/P9397)

# 分析题目
本题为一道贪心题，考虑如何贪心。

题目只求 $x_l-x_r$ 的最小值，所以只考虑横坐标。

既然是贪心，我们自然可以想到两个最近的 $x$ 坐标相减，那么就可以将原数组按照横坐标从小到大的顺序排序，然后两两横坐标相减累加起来。

定义结构体。
```cpp
struct node{
	int x,y,w;//w表示这个星星的编号
}a[maxn];
~~~~~~~
~~~~~~~
sort(a+1,a+n+1,cmp);
```
排序完毕，因为星星两两相连，所以循环时 $i$ 每次加 $2$。

于是我们得到代码。
```cpp
#include<bits/stdc++.h>
#define maxn 500005
using namespace std;
struct node{
	int x,y,w;
}a[maxn];
int n,sum;
bool cmp(node a,node b)
{
	return a.x<b.x||a.x==b.x&&a.y<b.y;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y,a[i].w=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i+=2)
		sum+=a[i+1].x-a[i].x;
	cout<<sum<<endl;
	for(int i=1;i<=n;i+=2)//注意每次加2
		cout<<a[i].w<<" "<<a[i+1].w<<endl;
	return 0;
}
```
然后发现只得了 $5$ pts，再回头读题，两两相连！当 $n$ 为奇数是无解！输出 $-1$。

# ACCODE
```cpp
#include<bits/stdc++.h>
#define maxn 500005
using namespace std;
struct node{
	int x,y,w;
}a[maxn];
int n,sum;
bool cmp(node a,node b)
{
	return a.x<b.x||a.x==b.x&&a.y<b.y;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y,a[i].w=i;
	sort(a+1,a+n+1,cmp);
	if(n%2)
		cout<<-1<<endl;
	else
	{
		for(int i=1;i<=n;i+=2)
			sum+=a[i+1].x-a[i].x;
		cout<<sum<<endl;
		for(int i=1;i<=n;i+=2)
			cout<<a[i].w<<" "<<a[i+1].w<<endl;
	}
	return 0;
}
```
这样我们就A掉了这题。

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

给定 $n$ 个点，使其两两相连，要求两两相连的线段不能相交，求 $|x_l-x_r|$ 之和的最小值。 

### 题目分析

我们先不考虑两两互不相交，仅考虑 $|x_l - x_r|$ 之和最小，我们可以将这些点都压缩为平面思考，也就是只考虑 $x$，我们不难发现，如果两两相邻的点相连可以使线段在 $x$ 轴上没有重合，也就是说 $|x_l - x_r|$ 之和最小。

于是我们再来考虑线段不能相交这个条件，我们发现对于相邻的两对点 $a,b,c,d$，上述连接方式是 $a \to b,c \to d$ 我们发现 $b_x \le c_x$ 且 $b_y \neq c_y$，也就是说，这两条线段是完全错开的。于是我们的连接方法就出来了。

但是你会发现交上去只有 $5$ pts。我们再回到题目，发现我们竟然没有判断无解的情况。

其实，只有当 $n$ 是奇数，所有数无法两两相连是才会无解。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct node{
	int x, y, id;
}a[500005];
int n, ans;

bool cmp(node u, node v)
{
	if(u.x == v.x)
		return u.y < v.y;
	return u.x < v.x;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d %d", &a[i].x, &a[i].y);
		a[i].id = i;
	}
	if(n & 1)
	{
		printf("-1\n");
		return 0;
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1;i <= n;i += 2)
		ans += a[i + 1].x - a[i].x;
	printf("%d\n", ans);
	for(int i = 1;i <= n;i += 2)
		printf("%d %d\n", a[i].id, a[i+1].id);
	return 0;
}
```

---

## 作者：XTC_lcd (赞：0)

**2023.6.17 update**
## 分析
首先阅读题目，要求两个端点相连，并且不能交叉，那么端点数量肯定为偶数，否则输出 $-1$。

其次是
>每一颗星星都是且仅是一条线段的端点，所有线段互不相交（包括端点）。

>所有线段左右端点 $|x_l-x_r|$ 之和有最小值。 

那么，我们可以通过对 $x$ 坐标和 $y$ 坐标排序找到最小的左右端点连接，这样，就会有序连接所有端点，不重复也不交叉。同时，因为我们是从左到右，从小到大两两相连，所以可以保证左右端点的绝对值最小，两全其美。
### 定义
```cpp
struct node
{
	int x, y, z;
};
```
### 排序
通过自定义排序解决：
```cpp
bool cmp(node p1, node p2) //自定义交换函数。
{
	return (p1.x == p2.x)?p1.y<p2.y:p1.x<p2.x;
}
```
### 计算
```cpp
if(n % 2 == 1) //不为偶数，根据题意输出 -1 后结束。
{
	cout << "-1\n";
	return 0;
}
else
{
	sort(a+1, a+n+1, cmp); //排序。
	for(int i = 1;i <= n;i += 2) //因为两个相连，所以注意在连线的时候 i 每次要加2。
	{
		ans += a[i + 1].x - a[i].x;
	}
	cout << ans << "\n";
	for(int i = 1;i <= n;i += 2) //同理，每次加2.
	{
		cout << a[i].z << " " << a[i + 1].z << "\n";
	}
}
```
## 完整代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
	int x,y,z;
};

bool cmp(node p1, node p2)
{
	return (p1.x == p2.x)?p1.y<p2.y:p1.x<p2.x;
}

int main()
{
	node a[500005];
	int n, ans;  
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i].x >> a[i].y;
		a[i].z = i;
	}
	if(n % 2 == 1)
	{
		cout << "-1" << endl;
	}
	else
	{
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1; i <= n; i += 2)
		{
			ans += a[i + 1].x - a[i].x;
		}
		cout << ans << endl;
		for(int i = 1; i <= n; i += 2)
		{
			cout << a[i].z << " " << a[i + 1].z << endl;
		}
	}
	return 0;
}
```
完成！

---

