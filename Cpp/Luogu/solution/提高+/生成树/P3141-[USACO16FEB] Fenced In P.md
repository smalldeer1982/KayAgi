# [USACO16FEB] Fenced In P

## 题目背景

*本题和 [金组同名题目](/problem/P6171) 在题意上一致，唯一的不同是数据范围。*

## 题目描述

Farmer John 意识到他的奶牛最近患上了一种恐惧症（害怕过于开阔的空间）。为了减少放牧的恐惧，FJ 决定在牧场中建一些水平和竖直方向的栅栏来将牧场分成若干个小区域。

整个牧场是一个矩形，两个角的坐标分别为 $(0,0)$ 和 $(A,B)$。FJ 在 $a_1,\ldots ,a_n$ 这 $n$ 个两两不同的位置建造了竖直方向的栅栏，每个栅栏从 $(a_i,0)$ 到 $(a_i,B)$；FJ 在 $b_1,\ldots ,b_m$ 这 $m$ 个两两不同的位置建造了水平方向的栅栏，每个栅栏从 $(0,b_i)$ 到 $(A,b_i)$。竖直方向的栅栏和水平方向的栅栏两两相交，将整个牧场分割成 $(n+1)(m+1)$ 个区域。

不幸的是，FJ 忘记了在栅栏上开门，奶牛都只能被困在一个个的小区域里！他想通过去掉一些栅栏来解决这个问题。他一次可以选择两个相邻的区域，将隔离这两个区域的栅栏去掉。FJ 的目标是让奶牛能够抵达牧场的任意一个地方。

这是一个例子：

```plain
+---+--+
|   |  |
+---+--+
|   |  |
|   |  |
+---+--+
```

去掉一些栅栏后的效果是这样的：

```plain
+---+--+
|      |
+---+  +
|      |
|      |
+---+--+
```

为了降低工程量，FJ 当然希望拆除的栅栏长度最短。

## 样例 #1

### 输入

```
15 15 5 2
2
5
10
6
4
11
3```

### 输出

```
44```

# 题解

## 作者：以墨 (赞：12)

本题就是最小生成树模型，但只会最小生成树是不够的~~~

楼下说的其实不对，因为我就是用Kruskal算法的~

但如果你不会Kruskal也可以往下看，因为并没有涉及太多的MST知识。

推导需要一步步来哦

-----------------------------------------------------------------------------------------------------------------------------------------------------------

**初始**

就用最基本的最小生成树算法

把所有的区域都看成是点，每拆掉一个围栏就相当于加上一条边，这样其实就是MST了。

但是！！！不要高兴太早，关注一下本题的数量级，（1<=n,m<=25,000），然而其中的区域至少有n\*m个，再加上Kruskal的排序，呵呵......

-----------------------------------------------------------------------------------------------------------------------------------------------------------

**观察**

注意一下，由于每一条围栏都是平行于所对应的边框的，所以，同一列的水平围栏长度相同，同一行的竖直围栏也长度相等。

这样就可以把水平围栏和竖直围栏分开算了，直接删去整行或整列。

是不是很简单？？？

但是，在删的过程中，由于到后面，并不是一整行或一整列上所有的围栏都要删去，有的删去甚至会出现环路，所以......

用x数组记录水平围栏的长度，用y数组记录竖直围栏的长度。

x1......xn+1，y1......ym+1

再用i,j两个指针记录当前扫到第几行或列。

当i,j都大于1的时候：

由于当x[i]<y[j]的时候，肯定要删第i列的水平栅栏，该列的栅栏个数为m(行数)-j(已经删了多少行)+1，对列有影响的是行（列与列不相交）

//不太理解可以自己画一个图，突然想吐槽题面的图了，居然都碎了~~~

当x[i]>y[j]的时候，肯定要删第j行的竖直栅栏，该行的栅栏个数为n(列数)-i(已经删了多少列)+1，对行有影响的是列（行与行不相交）

剩下的就看代码吧......

-----------------------------------------------------------------------------------------------------------------------------------------------------------




```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=25003;
long long ans,x[N],y[N],n,m,A,B,a[N],b[N];
int i,j;
int FAST_READ()//快速读入
{
    int tot=0;char c;
    for(c=getchar();c==' '||c=='\n';c=getchar());
    while(c>='0'&&c<='9')
        tot=tot*10+c-'0',c=getchar();
    return tot;
}
int main()
{
    A=FAST_READ();B=FAST_READ();n=FAST_READ();m=FAST_READ();
    for(i=1;i<=n;i++)
        a[i]=FAST_READ();
    for(i=1;i<=m;i++)
        b[i]=FAST_READ();
    sort(a+1,a+n+1);sort(b+1,b+m+1);//注意，位置不是按升序给的
    for(i=1,x[n+1]=A-a[n];i<=n;i++)
        x[i]=a[i]-a[i-1];//记录间隔两行之间的水平围栏的长度，在0和n的位置人为加上围栏，方便计算
    for(i=1,y[m+1]=B-b[m];i<=m;i++)
        y[i]=b[i]-b[i-1];//同上
    n++;m++;
    sort(x+1,x+n+1);sort(y+1,y+m+1);//因为是最小，所以要排个序，有点贪心的感觉
    for(i=2,j=2,ans=x[1]*(m-1)+y[1]*(n-1);i<=n&&j<=m;)//i,j都为1时，预先处理
        if(x[i]<y[j])
            ans+=x[i++]*(m-j+1);
        else
            ans+=y[j++]*(n-i+1);
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：junxis (赞：2)

# Perface

感觉这题的题解写得都有点水……

# Analysis

一个格子想要与外界联通，要么是删掉横边，要么是删掉纵边。

设有 $n$ 条横边，$m$ 条纵边。

我们不妨逐行逐列地考虑，设当前删到 $p$ 条横边所在列，第 $q$ 条竖边所在行。

显然有一个无脑贪心策略，分别将横纵边排序，先删除短的。

若我们选择删这一行，不一定是需要全部删掉的，因为有一些格子可能已经被前面删列的时候“解放”了，经过推导，发现是 $(n-p+1)$ 条还需要删。

删列同理。


# CODE

容易实现。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 301000;

int n, m, A, B, a[N], b[N];

int main() {
	scanf("%d%d%d%d", &A, &B, &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i); a[++n] = A;
	for (int i = 1; i <= m; i++) scanf("%d", b + i); b[++m] = B;
	sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);
	for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
	for (int i = m; i >= 1; i--) b[i] -= b[i - 1];
	sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);
	int p = 2, q = 2;
	i64 ans = 1ll * a[1] * (m - 1) + 1ll * b[1] * (n - 1) // 注意特判第一条横纵边
	while (p <= n && q <= m) {
		if (a[p] < b[q]) ans += 1ll * a[p++] * (m - q + 1); // 删列
		else ans += 1ll * b[q++] * (n - p + 1); // 删行
	} // 无脑小贪心
	printf("%lld\n", ans);
}
```

---

## 作者：zby2022 (赞：2)

**事先声明**：本题由作者自己想出，没有抄袭，如有相同代码，必属巧合！！！

# 正片开始
### [题目传送门](https://www.luogu.com.cn/problem/P3141)

解题思路：**贪心**

先对围栏位置进行排序，

然后相邻两条求差，再对差排序。

可以知道，每次取的是最短的一条围栏，结果一定是最优的（横向和竖向也要最短的优先），

所以直接整行整列删即可。

但是全删了就会造成浪费，如果两个块已经连通，则不需要建边，所以乘的时候要注意，


```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,n,m,a[25050],b[25050],x[25050],y[25050];
inline int read(){                   //快读函数，与此题无关
    char c=getchar();
    for(;!isdigit(c);c=getchar());
    int d=0;
    for(;isdigit(c);c=getchar())
    d=(d<<3)+(d<<1)+(c^'0');
    return d;
}
int main(){
    A=read();
    B=read();
    n=read();
    m=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=m;++i) b[i]=read();
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    a[0]=0;
    b[0]=0;
    memset(x,0x3f,sizeof x);
    memset(y,0x3f,sizeof y);
    for(int i=1;i<=n;++i){
    	x[i]=a[i]-a[i-1];
    	x[n+1]=A-a[n];
    }
    
    for(int i=1;i<=m;++i){
    	y[i]=b[i]-b[i-1];
    	y[m+1]=B-b[m];
	}
	sort(x+1,x+n+2);
	sort(y+1,y+m+2);
    long long ans=(long long)x[1]*m+(long long)y[1]*n;
    int i=2,j=2;
    for(;i<=n+1&&j<=m+1;){
    	if(x[i]<y[j])ans+=(long long)x[i++]*(m-j+2);
    	else ans+=(long long)y[j++]*(n-i+2);
    }
    cout<<ans<<endl;
    return 0;
}
```
希望各位能看懂。

---

## 作者：曹老师 (赞：2)

**贪心**

**容易想到：被分割成(n+1)(m+1)个矩形，就有(n+1)(m+1)-1 条边被删除**

处理出平行于x轴和y轴边的长度：存到x，y数组里

**贪心：每次取出最短的边**

**若是平行于x轴就删去m−j+1条该边，若是平行于y轴就删去n−i+1条该边**

**重要理解：**~~借用一下~~

1、当x[i]<y[j]的时候，肯定要删第i列的水平栅栏，该列的栅栏个数为m(行数)−j(已经删了多少行)+1，对列有影响的是行（列与列不相交）

2、当x[i]>y[j]的时候，肯定要删第j行的竖直栅栏，该行的栅栏个数为n(列数)−i(已经删了多少列)+1，对行有影响的是列（行与行不相交）
  

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=25005;
LL int A,B,n,m,a[L],b[L],ans,x[L],y[L];
int main()
{
	scanf("%lld%lld%lld%lld",&A,&B,&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++)
		scanf("%lld",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
		x[i]=a[i]-a[i-1];	
	x[n+1]=A-a[n++];
	for(int i=1;i<=m;i++)
		y[i]=b[i]-b[i-1];
	y[m+1]=B-b[m++];
	sort(x+1,x+n+1);
	sort(y+1,y+m+1);
	ans=x[1]*(m-1)+y[1]*(n-1);
	for(int i=2,j=2;i<=n&&j<=m;)
        if(x[i]<y[j])
			ans+=x[i++]*(m-j+1);
        else
			ans+=y[j++]*(n-i+1);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

把拆栅栏看成把两个相邻格子连一条边，把牧场连通看成把对应图连通。如果建立这个 $n+1$ 行 $m+1$ 列的网络图，两个相邻点权值为它们之间的栅栏长度，发现我们需要这个图的最小生成树的权值。

考虑快速模拟 Kruskal 过程。可以把图中的边排序，使得 Kruskal 遍历边的时候，同一行或者同一列的边在一块。

加入一整行列的时候计算贡献，这个贡献等于（权值）乘（Kruskal 成功连边次数）。在合并一行的时候，如果当前没有合并行 **或** 合并列，所有行肯定互相互相独立，所有 $m$ 连边都会成功。否则，每两对相邻合并过的列会产生一次连边失败，需要从 $m$ 减去（合并列次数-1）。合并列相似。

代码：

```cpp

int a[100005], b[100005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int A, B, n, m; gi(A), gi(B), gi(n), gi(m);
	rep1(i, n) gi(a[i]); sort(a+1, a+n+1); n++;
	a[n] = A; for(int i=n; i>=1; i--) a[i] -= a[i-1];
	rep1(i, m) gi(b[i]); sort(b+1, b+m+1); m++;
	b[m] = B; for(int i=m; i>=1; i--) b[i] -= b[i-1];
	sort(a+1, a+n+1); sort(b+1, b+m+1);
	int p1 = 1, p2 = 1;
	int on = 0, om = 0;
	ll ans = 0;
	// cout << n << ' ' << m << endl;
	n--; m--;
	while(a[p1] && b[p2]) {
		if(a[p1] < b[p2]) ans += 1ll*a[p1++]*(m-(on?max(om-1,0):0)),on++;
		else ans += 1ll*b[p2++]*(n-(om?max(on-1,0):0)),om++;
	}
	while(a[p1]) ans += 1ll*a[p1++]*(m-(on?max(om-1,0):0)),on++;
	while(b[p2]) ans += 1ll*b[p2++]*(n-(om?max(on-1,0):0)),om++;
	print(ans);
}

```

---

## 作者：Orion_Rigel (赞：1)

First Blood！

顺利的拿到了一血。

其实就是最小生成树，但是由于边数比较多，kruskal显然不行。

我们可以每次加入一行，因为一行的边的长度是相同的，这样就会快很多。

只要在纸上推一下就可以发现规律了。

题目中有明显的使用%I64d的叙述，建议修改成%lld

···
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int x[30001],y[30001];
int cntx,cnty,xx,yy,cnt=0,px=1,py=1;
long long ans=0;
int main()
{
    scanf("%d%d%d%d",&xx,&yy,&cntx,&cnty);
    for (int i=1;i<=cntx;++i) scanf("%d",&x[i]);x[++cntx]=xx;
    sort(x+1,x+cntx+1);
    for (int i=1;i<=cnty;++i) scanf("%d",&y[i]);y[++cnty]=yy;
    sort(y+1,y+cnty+1);
    for (int i=cntx;i>=1;--i) x[i]=x[i]-x[i-1];
    sort(x+1,x+cntx+1);
    for (int i=cnty;i>=1;--i) y[i]=y[i]-y[i-1];
    sort(y+1,y+cnty+1);
    int flagx=0,flagy=0,nowx=0,nowy=0;
    while (cnt<cntx*cnty-1)
    {
        if (x[px]<y[py])
        {
            if (!flagx||!flagy)
            {
                cnt+=cnty-1;
                ans+=(ll)(cnty-1)*x[px];
            }
            else
            {
                cnt+=cnty-nowx;
                ans+=(ll)(cnty-nowx)*x[px];
            }
            nowy++;
            flagy=1;
            px++;
        }
        else
        {
            if (!flagx||!flagy)
            {
                cnt+=cntx-1;
                ans+=(ll)(cntx-1)*y[py];
            }
            else
            {
                cnt+=cntx-nowy;
                ans+=(ll)(cntx-nowy)*y[py];
            }
            nowx++;
            flagx=1;
            py++;
        }
    }
    printf("%lld\n",ans);
}
···
```

---

## 作者：Error_Eric (赞：0)

### Statement

[Link](https://www.luogu.com.cn/problem/P3141)

### Sol 

更加简单的解法：

首先行列格子的顺序不重要，因此只需分别算出每个行和列的代价然后排序就行了。

模拟 kruskal 的过程。注意到代价最小的行和列肯定要全选。那就直接全部选上。现在网格里面有一个大十字。

接下来从剩余行和列里面选出代价最小的那个。比如说选出了一个行，那么只需要将这行中 $l$ 个格子连到原来的大十字上就能保证联通了。这里的 $l$ 是剩余没有被选中过的列的个数。

因为过程比较简单，用 Python 可以实现一些很 fancy 的东西。

### Code

```python
a, b, n, m = map(int, input().split())
a = sorted([int(input()) for _ in range(n)] + [0,a])
b = sorted([int(input()) for _ in range(m)] + [0,b])
da = sorted([a[i+1] - a[i] for i in range(n + 1)], reverse= True)
db = sorted([b[i+1] - b[i] for i in range(m + 1)], reverse= True)
ans = da.pop() * m + db.pop() * n
while len(da) + len(db) > 0:
    if len(da) == 0 : d = db
    elif len(db) == 0 : d = da
    else:  d = da if da[-1]< db[-1] else db
    ans += d[-1] * (len(da) + len(db) - len(d))
    d.pop()
print(ans)
```

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://www.luogu.com.cn/problem/P3141)

如果此题数据要小一点，那么我们可以用克鲁斯卡尔算法通过，但是这个数据太大了，空间会爆炸，时间也会爆炸。

我们发现，如果用 MST 做，那么很多边的边权都一样，我们可以整行整列地删除。

我们造一个样例解析一下：

```
+-+--+---+
| |  |   |
+-+--+---+
| |  |   |
| |  |   |
+-+--+---+
```
首先，我们删除第一列的栅栏：

```
+-+--+---+
| |  |   |
+ +--+---+
| |  |   |
| |  |   |
+-+--+---+
```

此时答案是 $1$。

再删除第一排的栅栏:

```
+-+--+---+
|        |
+ +--+---+
| |  |   |
| |  |   |
+-+--+---+
```
此时答案是 $3$。

我们继续删除第二列的栅栏：

```
+-+--+---+
|        |
+ +  +---+
| |  |   |
| |  |   |
+-+--+---+
```

此时答案是 $5$。

我们继续删除第二行的栅栏：

```
+-+--+---+
|        |
+ +  +---+
|        |
|        |
+-+--+---+
```

此时答案是 $9$。

我们把第三列的栅栏删除，由于之前删除的两行栅栏导致第三列栅栏少删除一个，不用删除。

你可以继续造更大的数据发现规律：

我们先把每一列，每一行的栅栏长度算出来，从小到达排序，然后用双指针算法，两个指针 $i$ 和 $j$，第一个记录统计到哪一行，第二个记录统计到哪一列，这两个变量的初始值应该为 $2$，然后把第一列，第一行栅栏删除。讨论时，如果我们当前讨论的行比列要短，就删除 $m-j+1$ 个栅栏，因为之前删除的栅栏导致我们现在不用删除一些栅栏。反之，同理，就是 $n-i+1$ 个栅栏。如果一个指针走完了，那么所有的都是联通的，就不用再循环了。时间复杂度 $O(n)$，通过。

## AC Code：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int h, w, n, m;
int a[300000], b[300000];
long long a1[300000], b1[300000];
long long ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> h >> w >> n >> m;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= m; i ++) cin >> b[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	n++;
	a[n] = h;
	m++;
	b[m] = w;
	for (int i = 1; i <= n; i ++) {
		a1[i] = a[i] - a[i - 1];
	}
	for (int i = 1; i <= m; i ++) {
		b1[i] = b[i] - b[i - 1];
	}
	sort(a1 + 1, a1 + n + 1);
	sort(b1 + 1, b1 + m + 1);
//	for (int i = 1; i <= n; i ++) {
//		cout << a1[i] << ' ';
//	}
//	cout << '\n';
//	for (int j = 1; j <= m; j ++) {
//		cout << b1[j] << ' ';
//	}
//	cout << '\n';
	int i = 2, j = 2;
	ans = a1[1] * (m - 1);
	ans += b1[1] * (n - 1);
	while (i <= n && j <= m) {
		if (a1[i] < b1[j]) {
			ans += a1[i] * (m - j + 1);
			i++;
		}
		else {
			ans += b1[j] * (n - i + 1);
			j++;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 0：前言
建议先完成 [P6171](https://www.luogu.com.cn/problem/P6171) 和 [P5687](https://www.luogu.com.cn/problem/P5687) 后再来完成此题。

好像题解都没有图，这里有图，而且提供一个和其他题解不太一样的做法，比起克鲁斯卡尔，更容易理解。

主要思路来自 <https://www.luogu.com.cn/blog/208529/solution-p5687>。

## Part 1：主要思路
首先，我们对于整个题目进行一个抽象化。

比如说，我们现在的图是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/tt1vie3g.png)

我们可以以每个格子为点建图。

那么怎么加边呢？

不难发现一件事情，就是我们要使得每个格子都联通，那么就是要求出所有格子组成的这个图的最小生成树。

答案既然要我们求最小代价，那么也就对应这里的最小生成树的大小，所以我们可以让边权变为两个格子之间的隔板的长度。

于是，对于这个图，我们就能建另外一个图了：

![](https://cdn.luogu.com.cn/upload/image_hosting/zlc7ht9v.png)

这时，我们需要对这个图求最小生成树。

我们可以发现，这时候，这道题和 [P5687](https://www.luogu.com.cn/problem/P5687) 一模一样。

那我们怎么做呢？

首先，我们得明确一个很简单的贪心性质：

对于点 $(i,j)$，如果点 $(i-1,j)$ 和点 $(i,j-1)$ **都已经在当前的最小生成树内**，那么将点 $(i,j)$ 加入最小生成树后，答案的变化为 $\min(a_i,b_j)$。

而且：还有一个性质，就是边种行和列的数的顺序的改变不会影响答案。

不难发现，不论样例怎样我们，都必须选第一行和第一列。

接着，我们对于每一列的横线，从第二个开始，选择所有比其小的竖线的值，接着剩下的所有的数的个数个这个列的横线的值。

也就是说，设这一行的横线的值为 $val$，一行竖线上的值组成的数组（已经排好序）为 $\{a\}$（大小为 $sz$），$\{a\}$ 一共有 $t$ 个数比 $val$ 小，那么最后这一列所有横线对答案所产生的贡献为 $\sum_{i=1}^{i \le t} a_i + val \times (sz-t)$。

对于这个式子，$val$、$sz$、$\{a\}$ 是知道的，而 $t$ 可以通过二分求得，$\sum_{i=1}^{i \le t} a_i$ 可以通过前缀和求得。

于是这题就做完了。

时间复杂度 $O(n\log{n})$（$n$、$m$ 同阶）。

记得开 `long long`。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#define rep(i, l, r) for(int i = l; i <= r; i++)
#define per(i, l, r) for(int i = l; i >= r; i--)
#define sort stable_sort
#define map unordered_map
#define int long long
using namespace std;
typedef long long ll;

int A, B, n, m;
int aa[300010], bb[300010];
int a[300010];
int b[300010];
int sum[300010];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> A >> B >> n >> m;
    rep(i, 1, n){
        cin >> aa[i];
    }
    rep(i, 1, m){
        cin >> bb[i];
    }
    sort(aa + 1, aa + n + 1), sort(bb + 1, bb + m + 1); // 对原来的数组进行排序
    aa[n + 1] = A, bb[m + 1] = B;
    rep(i, 1, n + 1){ // 算出每条边的边长
        a[i] = aa[i] - aa[i - 1];
    }
    rep(i, 1, m + 1){
        b[i] = bb[i] - bb[i - 1];
    }
    n++, m++; // 这里要加上两边，但是建图后你会发现会少一条边，所以只要加一
    /* 剩下的部分和 P5637 一模一样 */
    sort(a + 1, a + n + 1), sort(b + 1, b + m + 1); // 对数组进行排序
    int ans = a[1] * (m - 1) + b[1] * (n - 1); // 计算答案
    rep(i, 1, m){ // 求前缀和
        sum[i] = sum[i - 1] + b[i];
    }
    rep(i, 2, n){
        int now = lower_bound(b + 2, b + 1 + m, a[i]) - b; // 二分寻找答案，原理上面说了
        ans += sum[now - 1] - sum[1];
        ans += (m - now + 1) * a[i];
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：zhzkiller (赞：0)

[本题弱化版](https://www.luogu.com.cn/problem/P6171)

## 题目描述
给定一个网格图每一行的位置 $a_i$ 和每一列的位置 $b_i$，要求在这个图上找最小生成树。

## 解题思路
先把相邻行 / 列的距离求出来。

~~随便看看复杂度也知道这道题不是让你水 kruskal 和 prim 的。~~

虽然但是，最小生成树**一定包含最短的那条边**这个结论依然适用，在本题则是**最短的那一条行或列**。

找到了，$ans$ 也更新了，后面咋办？

既然我们找到的行 / 列已经联通，我们不妨一这条行 / 列为基础，向图的剩下相邻行 / 列进行 $O(n)$ 贪心。以下 $a$ 与 $b$ 数组均代表相邻距离。

假设我们现在以列进行贪心，当前所在列为 $i$，则我们要做的就是让所有 $i$ 上的点与列 $i-1$ 联通（反向同理），不难想到有两种情况：

**·** 任意一条连接 $i-1$ 与 $i$ 的边长（即所有的 $a_x$）均大于第 $i$ 列的 $b_i$。

**·** 存在若干条连接 $i-1$ 与 $i$ 的边长小于等于第 $i$ 列的 $b_i$。

对于第一种情况，我们无脑将第 $i$ 列联通即可，然后在这些 $a_x$ 中找一条最小的连上。

对于第二种情况，我们则可以将较小的列联通边 $a_x$ 连接，然后按其数量与 $n$ 的差连接第 $i$ 列上的边。

以行贪心同理。

但是判断大小关系又要 $O(n)$ 的复杂度，这不乱 TLE？

**预处理嘛！**

类似离散化，我们 `sort` 后进行前缀和，每次查询的时候用 `upperbound` 函数查一下，每次复杂度 $O(\log n)$。整体时间复杂度 $O(n\log n)$。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=250010;

ll n,m,A,B;
ll a[N],b[N],tem[N];
ll backa[N],backb[N];
ll suma[N],sumb[N],ans;
ll mxa=1e10,mxb=1e10;
int tara,tarb;

void prework()
{
	memcpy(backa,a,sizeof(a));
	memcpy(backb,b,sizeof(b));
	sort(backa+1,backa+n+1);
	sort(backb+1,backb+m+1);
	for(int i=1;i<=n;i++) suma[i]=suma[i-1]+backa[i];
	for(int i=1;i<=m;i++) sumb[i]=sumb[i-1]+backb[i];
}

ll querya(int x)
{
	return upper_bound(backa+1,backa+n+1,x)-backa-1;
}

ll queryb(int x)
{
	return upper_bound(backb+1,backb+m+1,x)-backb-1;
}

int main()
{
	scanf("%lld %lld %lld %lld",&A,&B,&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&tem[i]);
	tem[++n]=A;sort(tem+1,tem+n+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=tem[i]-tem[i-1];
		if(mxa>a[i]) mxa=a[i],tara=i;
	}
	for(int i=1;i<=m;i++) scanf("%lld",&tem[i]);
	tem[++m]=B;sort(tem+1,tem+m+1);
	for(int i=1;i<=m;i++)
	{
		b[i]=tem[i]-tem[i-1];
		if(mxb>b[i]) mxb=b[i],tarb=i;
	}
	
	prework();
	if(mxa<mxb)
	{
		ans+=mxa*(m-1);
		for(int i=tara-1;i;i--)
		{
			ll tem=queryb(a[i]);
			if(tem==0) ans+=sumb[1]+a[i]*(m-1);
			else ans+=sumb[tem]+a[i]*(m-tem);
		}
		for(int i=tara+1;i<=n;i++)
		{
			ll tem=queryb(a[i]);
			if(tem==0) ans+=sumb[1]+a[i]*(m-1);
			else ans+=sumb[tem]+a[i]*(m-tem);
		}
	}
	else
	{
		ans+=mxb*(n-1);
		for(int i=tarb-1;i;i--)
		{
			ll tem=querya(b[i]);
			if(tem==0) ans+=suma[1]+b[i]*(n-1);
			else ans+=suma[tem]+b[i]*(n-tem);
		}
		for(int i=tarb+1;i<=m;i++)
		{
			ll tem=querya(b[i]);
			if(tem==0) ans+=suma[1]+b[i]*(n-1);
			else ans+=suma[tem]+b[i]*(n-tem);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：羚羊WANG (赞：0)

相信大家看到这里的时候，对题目意思已经有了深入的了解

题目意思是说将图形分割成$n*(n+1)$个区域

那么就是删除$n*(n+1)-1$条边

而且我们会发现，这些删除的边都没有特殊的条件

所以，我们每次删边的时候可以考虑贪心

如果这条边平行于$x$轴就删去$m−j+1$条该边，如果这条边平
行于$y$轴就删去$n−i+1$条该边

这样子操作下来，我们就会发现，我们每一步删边都是删的最
值，所以这样子删边删完之后，求到最后一个，我们找到的一
定是最值

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int a[50010];
int b[50010];
int x[50010];
int y[50010];
int A,B;
int ans;
int l,r;
signed main(){
	A=read();
	B=read();
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
		a[i]=read();
	for(register int i=1;i<=m;++i)
		b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(register int i=1;i<=n;++i)
		x[i]=a[i]-a[i-1];
	x[n+1]=A-a[n];
	n++;
	for(register int i=1;i<=m;++i)
		y[i]=b[i]-b[i-1];
	y[m+1]=B-b[m];
	m++;
	sort(x+1,x+n+1);
	sort(y+1,y+m+1);
	l=2;
	r=2;
	ans=x[1]*(m-1)+y[1]*(n-1);
	while(l<=n && r<=m)
		{
			if(x[l]<y[r])
				{
					ans=ans+x[l]*(m-r+1);
					l++;
				}
			else
				{
					ans=ans+y[r]*(n-l+1);
					r++;
				}
		}
	write(ans);
	return 0;
}

```


---

