# Points on Plane

## 题目描述

给出 $N$ 个整点 $(x_i,y_i)$，求一个排列 $p$，使得 $\sum\limits_{i=2}^N (|x_{p_i} - x_{p_{i-1}}| + |y_{p_i} - y_{p_{i-1}}|) \leq 2.5 \times 10^9$。

## 样例 #1

### 输入

```
5
0 7
8 10
3 4
5 0
9 12
```

### 输出

```
4 3 1 2 5 
```

# 题解

## 作者：Plozia (赞：7)

~~无耻的~~宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/110496321)

这道题是一道构造题，很有 CF 的风格。

首先，观察 $x,y \leq 10^6$ ,不难想到一个思路：排序， $x$ 为第一关键字， $y$ 为第二关键字。但显然这样是错的。因为我们只要构造一组跨度足够大的数据，就可以把这个做法卡掉。

但是，**排序** 的思路是值得我们探讨的，只是如何排序的问题。

想一想，我们要使得曼哈顿距离之和最小，那么我们就需要将这些点 **划分成几个部分**，使得每一个部分 **内部距离和足够小** ，并且几个部分之间 **移动的距离也需要足够小**。

所以，根据上述分析，我们能想到什么？莫队！

我们可以把二维坐标 $(x,y)$ 看作一维区间 $[l,r]$ ，将相邻两个点的移动变成区间的移动，要使区间移动次数尽量小，这不是莫队经常干的事吗qwq。

不过：如果我们按照常规莫队的套路（按照左端点所在块数为第一关键字，右端点为第二关键字），会发现只要构造这样一组数据就会 WA：

```cpp
假设此时坐标已经排过序了：
1e3,0
1e3,1
1e3,2
...
1e3,1e6
2e3,0
...
2e3,1e6
3e3,0
...
3e3,1e6
4e3,0
...
```

这样，本来可以每一个点只走一次，但是除了 $x=10^3$ 的点由于莫队的排序方式都被走了两次，就会导致路程浪费，得不偿失。

所以，这个地方需要加入一个常见的莫队优化（之所以说是常见是因为在很多莫队算法讲解的博客中都讲到了这个优化）：假设当前左端点在第 $b$ 块，如果 $b$ 为奇数，那么右端点从小到大排序，否则从大到小排序。这样，我们就能完美解决上述问题。

由于英文题面中有 `It is guaranteed that the answer exists.`，所以无需考虑无解情况。

时间复杂度： $O(nlogn)$，一次快排即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
int n,block;
struct node
{
	int l,r,id,b;
}que[MAXN];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}

bool cmp(const node &fir,const node &sec)
{
	if(fir.b!=sec.b) return fir.b<sec.b;
	if(fir.b&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

int main()
{
	n=read();block=1000;//此处设块长为 1000，无需担心被上述反例卡掉（各位读者可以自行计算是否会被卡掉）
	for(int i=1;i<=n;i++) {que[i].l=read();que[i].r=read();que[i].id=i;que[i].b=(que[i].l-1)/block+1;}
	sort(que+1,que+n+1,cmp);
	for(int i=1;i<=n;i++) cout<<que[i].id<<" ";
	cout<<"\n";
	return 0;
}
```

---

## 作者：zac2010 (赞：4)

一道有趣的构造题，只需要了解莫队的复杂度就可以轻松过题。

我们采用莫队思想，按照 $\sqrt {10^6}$ 给权值分块，按照莫队的排序方法，这样可以构造出 $\sum\limits_{i=2}^N |x_{p_i} - x_{p_{i-1}}| + |y_{p_i} - y_{p_{i-1}}| \leq 3.5 \times 10^9$ 的方案。

来看看是怎么算出来的（下文中的“块”指的是左端点同个块的那些点）。左端点贡献不超过 $10^6*10^3$，即点数乘以每个点最多的贡献。

然而右端点可能在每到达一个新的块中时会产生 $10^6$，这种情况最多有 $10^3$ 种，再考虑块中的移动，每个块内部的右端点会产生块的个数乘以权值范围的贡献即 $10^3*10^6$。

上述三者相加是 $3 \times 10^9$，但由于有地方会多出一些，故而 $3 \times 10^9$ 变成了 $3.5 \times 10^9$。至于哪里多算，下面会提到。

我们考虑怎么优化右端点，这时会自然而然地想到莫队奇偶性优化，使一个块到一个新的块这个过程中右端点的大幅度移动消失了。具体的，右端点的移动只剩每个块内部的右端点会产生块的个数乘以权值范围的贡献 $10^3*10^6$ 了。

再看哪里估计少了，发现左端点一个块移动到另一个块时，最多会有 $2 \times 10^3$ 的移动距离，不过这样的贡献最多只有 $10^3$ 个，也就是块数个。

[代码](https://codeforces.com/contest/576/submission/201206025)。

---

## 作者：灵茶山艾府 (赞：4)

提供一种线性做法。将平面分成 $1000\cdot 1000$ 大小的块，由于坐标范围在 $[0,10^6]$ 内，这样可以得到 $1001\cdot 1001$ 个块。

然后遍历每个块，为了保证从一个块到另一块时，相邻点的距离尽可能地小，可以按照偶数行从左至右，奇数行从右至左的方式遍历。对于每一块内部，取纵坐标最小最大的两个点 $p$ 和 $q$，若该块位于偶数行则先输出 $p$，以及非 $p$ 非 $q$ 的其余点，然后输出 $q$；若该块位于奇数行则先输出 $q$，以及非 $p$ 非 $q$ 的其余点，然后输出 $p$。

AC 代码：（Golang）

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	type pair struct{ x, y int }

	var n int
	Fscan(in, &n)
	g := [1001][1001][]int{}
	ps := make([]pair, n+1)
	for i := 1; i <= n; i++ {
		Fscan(in, &ps[i].x, &ps[i].y)
		x, y := ps[i].x/1000, ps[i].y/1000
		if x&1 > 0 {
			y = 1000 - y
		}
		g[x][y] = append(g[x][y], i)
	}
	for i := 0; i < 1001; i++ {
		for j := 0; j < 1001; j++ {
			ids := g[i][j]
			if len(ids) == 0 {
				continue
			}
			minI, maxI := ids[0], ids[0]
			for _, id := range ids[1:] {
				if ps[id].x < ps[minI].x {
					minI = id
				} else if ps[id].x > ps[maxI].x {
					maxI = id
				}
			}
			if i&1 > 0 {
				minI, maxI = maxI, minI
			}
			Fprint(out, minI, " ")
			for _, id := range ids {
				if id != minI && id != maxI {
					Fprint(out, id, " ")
				}
			}
			if maxI != minI {
				Fprint(out, maxI, " ")
			}
		}
	}
}
```


---

## 作者：Z1qqurat (赞：3)

一句话题意：按一种方式重排序列使相邻点的曼哈顿距离尽量小。

看到这个曼哈顿距离，其实有一种很奇妙的转化：将坐标 $(x, y)$ 转化为区间 $[x, y]$，那么对于两个点 $a_i$，$a_{i + 1}$，其曼哈顿距离就是指针 $lt$，$rt$ 从 $x_i$，$y_i$ 移动到 $x_{i + 1}$，$y_{i + 1}$ 的距离，不难发现很像一个莫队的指针移动。而我们参照莫队的排序方式（奇偶排序）来确定顺序即可达到较优。

所以我们将 $(x, y)$ 当作区间的询问进行莫队奇偶排序即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 5;
int n, t;
struct Qr{
    int l, r, id;
    bool operator <(const Qr &b) const {
        if(l / t == b.l / t) {
            if((l / t) & 1) return r < b.r;
            return r > b.r;
        }
        return l < b.l;
    }
}qr[N];

int main() {
    scanf("%d", &n); t = sqrt(n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &qr[i].l ,&qr[i].r), qr[i].id = i;
    sort(qr + 1, qr + n + 1);
    for (int i = 1; i <= n; ++i) printf("%d ", qr[i].id);
    puts("");
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

小清新构造题。

## 题意

给定 $N$ 个点，求一个排列，使得相邻两点的距离比较小（不是最小）。

## 思路

这个题如果把 $x$ 看成左指针，$y$ 看成右指针，那么到新的点 $|x_{p_i}-x_{p_{i-1}}|$ 就相当于左指针挪动，$|y_{p_i}-y_{p_{i-1}}|$ 就相当于右指针挪动。

这就类似莫队的挪动指针，所以按莫队的排序来排即可。

莫队的时间复杂度是 $O(N\sqrt N)$，每一次移动指针都是 $O(1)$ 的，相当于点之间的一格距离。所以 $10^6\times10^3\leq2.5\times10^9$，能过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, slen, pos[N];
struct node {
	int l, r, id;
	bool operator < (const node& x) const {
		if (pos[l] != pos[x.l]) return l < x.l;
		return (pos[l] & 1 ? r < x.r : r > x.r);
	}
} s[N];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n, slen = sqrt(n);
	for (int i = 1; i <= n; i ++)
		pos[i] = (i - 1) / slen + 1;
	for (int i = 1; i <= n; i ++)
		cin >> s[i].l >> s[i].r, s[i].id = i;
	sort(s + 1, s + 1 + n);
	for (int i = 1; i <= n; i ++)
		cout << s[i].id << '\n';
	return 0;
}
```


---

## 作者：Deuteron (赞：2)

### 题意：

给出 $N$ 个整点 $(x_i,y_i)$ ，求一个排列 $p_i$ ，使得$\sum\limits_{i=2}^N |x_{p_i} - x_{p_{i-1}}| + |y_{p_i} - y_{p_{i-1}}| \leq 25 \times 10^8$ 。

## solution

我们通过~~看题目标签~~观察法，发现我们如果将点 $(x,y)$ 看做询问 $(l,r)$ 这样这个柿子就变成了莫队的复杂度。

而通过~~常识~~证明，莫队的复杂度是 $O(n\sqrt n)$ 的，而 $10^6\times \sqrt {10^6} = 10^9 \le 25 \times 10^8$ 。

注意这里需要使用莫队的一个小优化。

如果当前左端点所在的块为奇数，则按照从小到大排序，否则按照从大到小排。这个优化很有用。经测试，可以做到 $4.6\times10^9 \rightarrow 1.3\times 10^9$ （太蒻了，不会证）

## code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e6+1000,SN=1000;
typedef long long ll;
int n,sn;
struct de{
	int l,r,id;
};
de d[N];
int a[N];
inline int blk(int x){
	return (x-1)/SN;
}
inline int cmp(de x,de y){
    int dlx=blk(x.l),dly=blk(y.l);
    return dlx!=dly?(dlx<dly):(dlx&1)?(x.r<y.r):(x.r>y.r);
}
static char buf[100000],*pa=buf,*pd=buf;
#define gc pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++
inline int read(){
    register int x(0);register char c(gc);
    while(c<'0'||c>'9')c=gc;
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc;
    return x;
}
inline void write(register int x){
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int l,r;
		l=read();
		r=read();
		d[i].l=l,d[i].r=r;
		d[i].id=i;
	}
	sort(d+1,d+n+1,cmp);
	for(int i=1;i<=n;i++){
		write(d[i].id);
		putchar(' ');
	}
	return 0;
}
```


---

## 作者：OIer_ACMer (赞：1)

~~为啥飞机上有这么多点？？？~~

------------
注意：本片题解是本人第一次写分块与莫队之类的题目，有些思路参考[大佬题解](https://blog.csdn.net/qq_41955236/article/details/81626065)。

------------
## 开幕雷击：
如果你现在发现你的样例无法通过，同时又刚好看到这篇题解，你就会发现，这道题，是一道隐藏的 SPJ！！！~~但害得我调了三十多分钟。~~

------------
## 大致思路：
一开始，当你看到体面可能会有点懵，但是满足题目要求，只要总路程小于 $2.5 \times 10 ^ {9}$ 就好，然而这道题有将近 $1 \times 10^{6}$ 个点，点的坐标范围也是在 $(0,0)$ 到 $(1 \times 10^{6},1 \times 10^{6})$ 之间，所以如果样例比较极端，再随便连的话超过 $2$ 秒是分分钟的事情，所以要进行优化。

这时，我们可以观察到，题目要求 $\sum\limits_{i=2}^N |x_{p_i} - x_{p_{i-1}}| + |y_{p_i} - y_{p_{i-1}}| \leq 2.5 \times 10^9$，想一想，这个公式有点像**莫队**的普通使用方法，没错，莫队在这里面发挥了大作用，还有，由于数据量过大，分块肯定少不了。我们再根据题目本身想一想：要求点与点之间的曼哈顿距离尽量小，那么**就要满足每次连的点横纵坐标的差值尽量小**。所以，结合上述思路，我们就可以大致推出代码框架：

1. 先用结构体定义每个点的信息，$x$ 和 $y$ 表示每个点的横纵坐标，$id$ 表示每个点的编号，$level$ 表示每个点每个点属于奇数块还是偶数块。

2. 接着，我们将每个点按照输入时的奇偶顺序（也就是和 $biao$ 变量相除的结果，因为将 $n$ 开了根号就是**把** $n$ **平均分成了** $n$ **份**，而我们每一列表示一个奇偶点组，用 $x$ 去除根据**求得的商的奇偶性就可以判断是奇数组还是偶数组**，具体的请读者自行画图理解）进行排序，将各组排好序后直接输出就可以了。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int x, y, level, id;
    bool operator<(const node &a) const
    {
        if (level == a.level)
        {
            if (level % 2)
            {
                return y < a.y;
            }
            return y > a.y;
        }
        return level < a.level;
    }
}point[N];
int n, biao;
int main()
{
    n = read();
    biao = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        point[i].x = read();
        point[i].y = read();
        point[i].id = i;
        point[i].level = point[i].x / biao;
    }
    sort(point + 1, point + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        cout << point[i].id << ' ';
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121460207)

---

## 作者：Wf_yjqd (赞：1)

刷分块遇到的。

------------

构造一个二维转移的路径小于等于一个挺大的定值 $2.5\times10^9$。

很难不想到莫队的转移，一维对应左端点，另一维对应右端点。

所以此题等于构造一个尽可能小（不需要最小）的莫队区间转移的复杂度。

由于 $n$ 最大为 $10^6$，直接按传统排序方式很容易被卡。

反例只需要将左端点在同一个块中的区间右端点平均分布在每个块内，在左端点到下一个块时，右端点需要很长（几乎为 $n$）的移动。

所以需要用到莫队经典的卡常方法：奇偶排序。

当左端点所在块为奇数时，右端点从小到大排序；当左端点所在块为偶数时，右端点从大到小排序。

于是右端点的移动总距离大约减少一半。平均复杂度（即此题的权值）降低 $\frac{1}{4}$。

那么此题只需要奇偶排序，然后按顺序输出编号即可。

复杂度 $\operatorname{O}(n\times\log{n})$。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+84;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,SizE;
struct Query{
    int l,r,id;
    friend bool operator<(Query kn,Query sr){
        if((kn.l-1)/SizE==(sr.l-1)/SizE){
            if(((kn.l-1)/SizE)&1)
                return kn.r<sr.r;
            return kn.r>sr.r;
        }
        return kn.l<sr.l;
    }
}q[maxn];
int main(){
    n=read();
    SizE=sqrt(n+1);
    for(int i=1;i<=n;i++){
        q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+n+1);
    for(int i=1;i<=n;i++)
        printf("%d Sherry",q[i].id);
    return 0;
}
```

结论题真的水。

---

## 作者：_Ch1F4N_ (赞：1)

注意到 $\sum\limits_{i=2}^N |x_{p_i} - x_{p_{i-1}}| + |y_{p_i} - y_{p_{i-1}}|$。 本质上是两个点之间的**曼哈顿距离** 。

而曼哈顿最小距离生成树要 $O(n^2 \log n)$ ，显然过不了。

注意到我们写过一个叫莫队的东西。

而莫队的复杂度为 $O(n \sqrt n)$  ，也就是我们要求的东西。

加一点小优化，奇偶排序。

就可以过了。

怎么证明？

可以看一看[这一篇博客](https://www.cnblogs.com/WAMonster/p/10118934.html)

精简来说就是控制了左右指针跨越块的数量。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
struct query{
    int l,r,id;
}q[maxn];
int n;
int sq;
bool cmp(query a,query b)
{
    if(a.l/sq==b.l/sq)
    {
        if(a.l/sq&1)
        {
            return a.r<b.r;
        }
        else
        {
            return a.r>b.r;
        }
    }
    else
    {
        return a.l<b.l;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    sq=1145;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
    }
    sort(q+1,q+n+1,cmp);
    for(int i=1;i<=n;i++)
        cout<<q[i].id<<' ';
}
```



---

## 作者：Styx (赞：1)

这道题是道思维题

首先是题意：定义曼哈顿距离为两点之间x坐标差的绝对值与y坐标差的绝对值，在定义哈密顿路径为所有相邻两点间的曼哈顿距离之和，给出一些点的xy坐标，求一个点排列使哈密顿路径小于25*1e8

首先看到点的xy坐标均在1e6以内，然后如果按照直接优先x再y的顺序排序，只需要一组x坐标1-5e5的数据，每个x坐标的y坐标为1e6和0，然后距离就被卡到了5e11。

虽然上面的思想有错误，但是是有借鉴意义的，如果将哈密顿路径理解为复杂度，长度理解为变量，这显然是n^2的，然后你会想到一些优化的方法，比如说莫队。

然后就可以根据莫队的思想将x坐标分块，分成0-999,1000-1999……的1000块，每块里按照y从小到大的顺序排序，这样子块内y是单调递增的，最多增大1e6，x就算上下乱跳，也最多变化1e3*1e3=1e6，总变化最多2e9

但是还是有点锅，就是块与块之间切换的时候，如果是从最大y切到下一坐标最小y，最多要跳1e6，总变化会多增加1e9

所以按照一个块y递增，下一个块y递减的顺序排列，这样子就稳了

然后你就能A掉他

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct node
{
	int x,y,kd;
};

vector<node> g[1010];
int n;

int cmp1(node x,node y)
{
	return x.y<y.y;
}

int cmp2(node x,node y)
{
	return x.y>y.y;
}

int main()
{
	node tmp;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&tmp.x,&tmp.y);
		tmp.kd=i;
		g[tmp.x/1000].push_back(tmp);
	}
	for(int i=0;i<=1000;i++)
	{
		if(i&1)
		{
			sort(g[i].begin(),g[i].end(),cmp1);
		}
		else
		{
			sort(g[i].begin(),g[i].end(),cmp2);
		}
	}
	for(int i=0;i<=1000;i++)
	{
		for(int j=0;j<g[i].size();j++)
		{
			printf("%d ",g[i][j].kd);
		}
	}
}
```

---

## 作者：End1essSummer (赞：0)

这一道题如何转化成莫队问题其他题解已经讲的很清楚了，所以我来注重讲一讲此题所用的奇偶排序优化。

我们发现如果按照普通莫队排序的话二元组的 $x_i , y_i$ 趋向会变成这个样子(横为 $x$ 竖为 $y$)

![](https://cdn.luogu.com.cn/upload/image_hosting/nekyv77w.png)

而奇偶排序优化主要就是通过其奇偶性来决定从小到大排序还是从大到小排序，使得他变成这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/dapb0f6f.png)

主要原理是右指针跳完奇数块之后回跳时能顺路把偶数块跳完，以此类推。这样就起到了优化时间复杂度的效果，也可以完美的通过第一篇题解中给出的hack样例。

---

## 作者：ttq012 (赞：0)

**Solution**

对于输入的每一个点 $(x_i, y_i)$ 可以将其看做为一个“区间” $[x_i, y_i]$。然后跑莫队。

然而莫队的时间复杂度是 $\mathcal O(n\times \sqrt n)$ 的，这样明显会超时。

然后看题解发现莫队有一个神奇的玄学优化：当当前块的编号为奇数的时候，按照纵坐标降序排列，否则按照纵坐标升序排列。

然后 CodeForces 的评测机跑的很快，就过去了。

注意：每一个块是按照 $x_i$ 从小到大分的！

[莫队时间复杂度分析](https://blog.csdn.net/qq_39562952/article/details/90376886)

**Code**

```cpp
// Think twice, code once.
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int l, r, id;
};
vector <Node> z[1145];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution <int> rnd(1000, 1000);
    int n, mx = 0;
    cin >> n;
    int block = rnd(gen); // 调整块长
    for (int i = 1; i <= n; i ++) {
        Node p;
        cin >> p.l >> p.r;
        p.id = i;
        z[p.l / block].emplace_back(p);
        // mx = max(mx, i / block);
    }
    for (int i = 0; i <= block; i ++)
        if (i & 1)
            sort (begin(z[i]), end(z[i]), [&] (const Node &lhs, const Node &rhs) {
                return lhs.r < rhs.r;
            });
        else
            sort (begin(z[i]), end(z[i]), [&] (const Node &lhs, const Node &rhs) {
                return lhs.r > rhs.r;
            });
    for (int i = 0; i <= block; i ++)
        for (int j = 0; j < z[i].size(); j ++)
            cout << z[i][j].id << ' ';
    cout << '\n';
    return 0;
}

```







---

## 作者：zplqwq (赞：0)

题目让我们求曼哈顿距离 $\text{dist}\le 2.5 \times 10^9$ 。

实际上就是让这个曼哈顿距离尽可能的小，毕竟如果你能达到最优的话这个这个限制肯定没用。

那怎么做，如果你去问一个初学者的话他肯定告诉你 **排序** 就行了。

具体怎么排序呢？先按照 $x$ 排序，如果要是相等的话按照 $y$ 来排序呗。

但这样显然是错的，只要你数据跨度足够大，那就没辙了。

那这样是否意味着排序行不通呢？答案是不一定。

我们发现，曼哈顿距离最小，意味着我们要把这些点分块，使得块内的贡献足够小，两个块之间的距离也足够小。

然后我们又发现，如果我们把点 $(x,y)$ 看做一个区间 $[l,r]$ ，那么假设我们知道了 $[l,r]$ 的答案，那么 $[l+1,r],[l-1,r],[l,r+1],[l,r-1]$ 的答案我们都可以求。因为是相邻的点，所以转移到这些答案的复杂度是 $O(1)$ 的。

那么一个算法就显然了，莫队。

既然是莫队就必须考虑一个问题，如何排序？

显然按照刚才讲的排序方法是行不通的，那么莫队还有哪些常见的排序方法呢？奇偶排序！

然后就做完了。

最后注意调下块长吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,block;
struct node
{
	int l,r,id,ans;
}ask[N];
bool cmp(node x,node y)
{
    if(x.ans==y.ans)
	{
        if (x.ans&1==1) return x.r<y.r;
        else return x.r>y.r;	
    }
    else return x.ans<y.ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	block=1000;
	for(int i=1;i<=n;i++) 
	{
		cin>>ask[i].l;
		cin>>ask[i].r;
		ask[i].id=i;
		ask[i].ans=(ask[i].l-1)/block+1;//属于哪个块 
	}
	sort(ask+1,ask+1+n,cmp);
	for(int i=1;i<=n;i++) cout<<ask[i].id<<" ";
	return 0;
}
```

看到这个代码肯定会有人问，诶莫队更新答案不应该是

```cpp
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(r++, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(--r, -1);
```

这样的吗？

但与其他的题不同，这道题要求给出的是 **排列** 所以并不需要更新答案。

---

