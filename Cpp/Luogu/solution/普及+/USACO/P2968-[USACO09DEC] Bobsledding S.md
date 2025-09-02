# [USACO09DEC] Bobsledding S

## 题目描述

Bessie has entered a bobsled competition because she hopes her hefty weight will give her an advantage over the L meter course (2 <= L <= 1,000,000,000).

Bessie will push off the starting line at 1 meter per second, but her speed can change while she rides along the course. Near the middle of every meter Bessie travels, she can change her speed either by using gravity to accelerate by one meter per second or by braking to stay at the same speed or decrease her speed by one meter per second.

Naturally, Bessie must negotiate N (1 <= N <= 100,000) turns on the way down the hill. Turn i is located T\_i meters from the course start (1 <= T\_i <= L-1), and she must be enter the corner meter at a speed of at most S\_i meters per second (1 <= S\_i <= 1,000,000,000). Bessie can cross the finish line at any speed she likes.

Help Bessie learn the fastest speed she can attain without exceeding the speed limits on the turns.

Consider this course with the meter markers as integers and the turn speed limits in brackets (e.g., '[3]'):

```cpp

|   1   2   3   4   5   6   7[3]
|---+---+---+---+---+---+---+
|                            \
Start                         + 8    
                               \
                                + 9    
                                 \
                                  + 10       +++ 14 (finish)
                                   \         /
                              11[1] +---+---+
                                        12  13[8]
```
Below is a chart of Bessie's speeds at the beginning of each meter length of the course:

````
Max:                              3               1       8 
Mtrs: 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 Spd:  1   2   3   4   5   5   4   3   4   3   2   1   2   3   4 
```
Her maximum speed was 5 near the beginning of meter 4. 

贝茜从山顶滑雪到山脚，山顶到山脚距离是L(2<L<10^9)米.贝茜在起点的速度是1米每 秒，但是他的速度是可以改变的，在每一米的速度可以是前一米的速度加1、减1，或者等于前一米 的速度.在滑行的过程中，贝茜会遇到N<=100000)个转弯处，第i个转弯处位于距离出发 Ti米处，为了安全，贝茜到达第i个转弯处的速度不能超过Si(1<Si<10^9)米 每秒.当然贝茜到达终点时的速度没有最大限制.请你计算贝茜在滑雪过程中最大的速度可以是多 少？


## 样例 #1

### 输入

```
14 3 
7 3 
11 1 
13 8 
```

### 输出

```
5 
```

# 题解

## 作者：1124828077ccj (赞：11)

这题初看有些无从下手。不过我们可以从后往前推出：对于每个拐角，经过它的速度的最大限制（既要小于题目给出的安全限制，又要确保后面的拐角能够顺利通过）。

知道这个之后，我们就可以从前往后模拟，计算出每两个拐角之间的速度最大值（不要忘了还有起点和终点），以及到达拐角时的速度。

到达拐角时的速度应该比较容易推，速度最大值要用点脑子（请参考代码）

附代码（并不会很长）

```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
int l,n,ans,m;//m表示到达某个拐角时的速度
typedef struct{
    int t,s,q;
}P;
bool cmp(P aa,P bb){
    return (aa.t<bb.t);
}
P p[100002];
int main()
{
    scanf("%d%d",&l,&n);
    for (int i=1;i<=n;i++)
    scanf("%d%d",&p[i].t,&p[i].s);
    sort(p+1,p+n+1,cmp);p[n].q=p[n].s;//切记要排序
    for (int i=n;i>=2;i--)
    p[i-1].q=min(p[i-1].s,p[i].q+p[i].t-p[i-1].t);//推出最大速度限制
    if (p[1].t+1<=p[1].q)ans=p[1].t+1;
    else ans=(p[1].q+p[1].t+1)/2;
    m=min(p[1].q,p[1].t+1);//起点与第一个拐角的信息
    for (int i=2;i<=n;i++)
    {
        if (m+p[i].t-p[i-1].t<=p[i].q) ans=max(ans,m+p[i].t-p[i-1].t);
        else ans=max(ans,(p[i].q+p[i].t-p[i-1].t+m)/2);
        m=min(p[i].q,m+p[i].t-p[i-1].t);//i和i-1个拐角的信息
    }
    printf("%d",max(ans,m+l-p[n].t));//不要忘了终点
    return 0;
}
```

---

## 作者：Lolierl (赞：5)

###  一道不错的贪心题。

感觉楼下题解解释的不是很清楚吧，我再补充一发。

100000的数据规模显然很难区间DP，于是我们考虑贪心。

这题的特性：速度变化量为±1或0。

不要觉得0没用！这一特性保证了，从拐弯点 i 到 i + 1 ， 若在拐弯点 i + 1 可以达到速度L、R， 那么速度 L + 1, L + 2, ..., R - 1都可以在 i + 1 处到达 

（应该很显然吧qwq）

于是我们可以证明一个引理


```cpp
引理：在v[i]取最大值时，v[ i + 1 ]要么无法满足限制，要么也可以取到最大值。

证明：若可以满足限制，则设 v[ i ]取max(v [ i ]) - 1时max' (v[ i + 1 ]) = p, 那么 v [ i ] 取 max(v [ i ]) 时， v[ i + 1 ] 必然可以取p + 1
```

有了这条引理，我们可以得出：如v1， v2, ..., vn分别为可以让后面每一个拐弯角满足限制的速度最大值，那么这n个速度必然可以被同时满足，即为我们所求的方案。

于是，我们可以从后往前算出每个拐弯角让后面所有拐弯角都能满足限制的速度最大值。这时我们就得出最佳方案在每个拐弯点的速度。

怎么统计答案呢？我们注意到，在两个拐弯点间是没有速度限制的，也就是说，要想有速度最大值必然会先加速到一定值再减速。设初速度为v0， 末速度为v1， 两点距离为s。直接减（加）速所需距离为|v1 - v0|， 而剩下距离都可以用于一加一减。于是，

```
vmax = v1 + ( s - | v1 - v0 | ) / 2 (v1 > v0)

vmax = v0 + ( s - | v1 - v0 | ) / 2 (v1 < v0)
```

则可以化简为

```
vmax = ( s + v1 - v0 ) / 2 
```

代码：

```cpp
//可能保险开ll的码风比较丑陋qwq
//应该没什么难点，细节比较多，边界情况要注意一下
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std; 

struct h
{
	int t, s; 
}b[100005]; 

int cmp(h a, h b)
{
	return a.t < b.t; 
}
int main()
{
	int l, n; 
	scanf("%d%d", &l, &n); 
	
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &b[i].t, &b[i].s); 
	sort(b + 1, b + n + 1, cmp); 
	b[0].t = 0; b[n + 1].t = l;  
	
	long long ok[n + 2]; 
	memset(ok, 0, sizeof(ok)); 
	ok[n + 1] = 1e18; 
	for(int i = n; i >= 1; i--)
		ok[i] = ((b[i].s > ok[i + 1] + (b[i + 1].t - b[i].t)) ? ok[i + 1] + (b[i + 1].t - b[i].t) : b[i].s); 
	
	long long ans[n + 2], maxn = 1; 
	ans[0] = 1; 
	for(int i = 1; i <= n + 1; i++)
		ans[i] = ((ok[i] < ans[i - 1] + b[i].t - b[i - 1].t) ? ok[i] : ans[i - 1] + b[i].t - b[i - 1].t); 

	for(int i = 0; i <= n; i++)
		maxn = (((ans[i] + (b[i + 1].t - b[i].t + ans[i + 1] - ans[i]) / 2) > maxn) ? ans[i] + (b[i + 1].t - b[i].t + ans[i + 1] - ans[i]) / 2 : maxn); 
	maxn = ((ans[n + 1] > maxn) ? ans[n + 1] : maxn); 
	printf("%lld", maxn); 
	return 0; 
} 

```
蒟蒻好久不写题解了，有错误请指出~

---

## 作者：shenxinge (赞：3)

>题目链接：[就是这里](https://www.luogu.com.cn/problem/P2968)

~~话说这USACO的图标都好形象生动啊！！！~~

首先，我们需要一张生动形象的图片来解释说明一下这个神奇的样例：（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/ss9b3k2c.png)

其实我们知道，在出发的时候 **（可以设出发的是第0点）**，贝茜的速度为1.

在$1-7$的过程中，我们可以把可以变化的总路程设为$S$，此时$S$=$7$-$0$=$7$

**（因为一开始是不可以变化的，即0时刻是不能进行变化，故只能进行7次变化）**

这时候，聪明的同学就要问了：怎么样才能达到最大值呢？

很简单，我们要运用一下小小的**贪心**。

我们只要是的每次达到的都是能达到点的**最大值**，那我们就可以取到**最大的值**。

**也就是说我们只要使得每次得到的限制值$node_i.limit$,我们只要保证到达这一点的速度尽量地达到这一个值就可以贪心取到最大值。**

其实我们只要设前一个点的速度为$v_0$ 后一个点的速度为$v_1$.

```latex
1.当v1>v0时，这明显是v0上升达到最大值后下降得来的v1，上升的距离就是（S-（v1-v0））/2(均分，如果没有均分就停止加减速。）需要加上的值为v0
2.当v1<v0时，明显是v0上升至一定值再下降，此时下降的距离是（S-(v0-v1)）/2,需要加上的值为v1。
```
所以自然就得到了此公式 $ans=max(ans,(S-v0+v1)/2+v0)$


这时候，又有的同学要问了：怎么证明**存在性**呢？万一达不到呢？

这是一个好问题。

我们一旦$v_0+S<=v_1$ 那么此刻必不会有上述公式的实现，此时最大的速度就是$v_0+S$,前面的速度也就要改为$v_0+S$

思路到此就为止了，但是还是需要进行一些必要的初始。

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/or3pwy11.png)

此时的第二个点8 1，距离上一个点是1，但是变化的距离是2，所以此时的点7的限制值应当进一步减小，所以得到的应该是下图中的：

![](https://cdn.luogu.com.cn/upload/image_hosting/go5zc8wn.png)

**这样一来就可以写代码了：（有本人的调试语句QAQ）**

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define rnt register int
using namespace std;
inline int read()
{
	int x=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-f;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
struct node
{
	int tim,lmt; 
}s[maxn];
inline bool cmp(node a,node b){return a.tim<b.tim;}
int L,n,ans;
int main()
{
	L=read(),n=read();
	for(rnt i=1;i<=n;i++)
		s[i].tim=read(),s[i].lmt=read();
	sort(s+1,s+1+n,cmp);
	for(rnt i=n-1;i>=1;i--) //处理limit的，如果说到达不了，limit就必须减弱 
		s[i].lmt=min(s[i].lmt,s[i+1].lmt+s[i+1].tim-s[i].tim);
	s[++n].tim=L,s[n].lmt=0x3f3f3f3f; 
	rnt last=1; //前一个速度，贪心进行使用 
	for(rnt i=1;i<=n;i++) //带贪心 
	{
//		printf("round: %d first last: %d ans: %d\n",i,last,ans);
		int v0=last,v1=s[i].lmt,S=s[i].tim-s[i-1].tim;
		if(v0+S<=v1) ans=max(ans,v0+S),last=v0+S;
		else ans=max(ans,(S-v0+v1)/2+v0),last=v1;
//		printf("round: %d after v0: %d v1: %d S: %d ans: %d\n",i,v0,v1,S,ans);
	}
	printf("%d\n",max(ans,last));
	return 0;
}

```
## end

**切了一道蓝题好激动啊！！！**


---

## 作者：Usada_Pekora (赞：1)

本题考虑 dp 。

以每个转弯点 $i$ 为状态，设 $ f[i] $ 表示在 $ i $ 点时，能达到的最大速度，由于速度是可以随时改变的，所以保持任意小于 $ f[i] $ 的速度也可以到达当前点。

但显然直接这么做是有后效性的：后面点的速度限制会影响当前点的状态。所以需要从后往前对最小速度做一个预处理:

$ s[i] = \min ( s[i] , s[i+1] + t[i+1] - t[i] )$ 

这样一来就消除了后效性，详细处理见代码。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,l,ans;
int f[100005];
struct node{
    int s,t;
}a[100005];
inline bool cmp(const node x,const node y){
    return x.t<y.t; //按高度排序 
}
inline int max(int x,int y){
	return x>y?x:y;
}
inline int min(int x,int y){
	return x<y?x:y;
}
int main(){
    scanf("%d%d",&l,&n);
    for(int i=1;i<=n;++i)
    scanf("%d%d",&a[i].t,&a[i].s);
    sort(a+1,a+1+n,cmp);
    f[0]=1;a[n+1].s=1e+9;a[n+1].t=l;//设置边界 
    for(int i=n;i>=1;--i)
        a[i].s=min(a[i].s,a[i+1].s+a[i+1].t-a[i].t);
    for(int i=1;i<=n+1;++i){
        f[i]=min(a[i].s,f[i-1]+a[i].t-a[i-1].t);
        ans=max((f[i]+f[i-1]+a[i].t-a[i-1].t)/2,ans);
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：ZYH_juruo (赞：0)

# 题目传送门
[P2968 [USACO09DEC] Bobsledding S](https://www.luogu.com.cn/problem/P2968)
# 题目大意
有长度为 $l$ 的赛道，给出 $a_1$ 的初始速度为 $1$，下一个位置的速度可 $\pm1$ 或不变。有 $n$ 个位置的速度限制为不高于 $s_i$。请求出全程中最大的速度可以为多少。
# 题目分析
看到楼下的大佬基本上是用的贪心，我来贡献一个 dp 做法。
首先看一个样例：
```cpp
10 2
5 5
7 2
-----------------------------------------
1  2  3  4  5  6  7  8  9  10 
            5     2
```
如果我们在 $i=5$ 的位置取到最大值 $5$ 的话，显然，在 $i=7$ 的位置就不能取到不超过 $2$ 的值，所以这告诉我们什么？后面的限制决定了前面的限制。
```cpp
-----------------------------------------
1  2  3  4  5  6  7  8  9  10 
            4     2

```
$s_5$ 就只能变成 $4$ 了。


所以，我们要在之前对 $s_i$ 做一个从后往前的预处理。

也就是 $s_i=\min(s_i,s_{i+1}+t_{i+1}-t_i)$。

$dp[i]$ 表示在 $t[i]$ 位置时可以取到速度的最大值。然后只需要让 $ans$ 打擂台取最大值就行了。

如果实在不懂的就看代码理解吧。

代码附上。
```cpp
#include<bits/stdc++.h>
#define maxn 114514
using namespace std;
int n,m,ans;
int dp[maxn];
struct bob{
    int s,w;
}a[maxn];
bool cmp(bob a,bob b)
{
    return a.w < b.w; //按照坐标排序 
}
int main(){
    cin>>m>>n;
    for(int i = 1;i <= n; i++)
    	cin>>a[i].w>>a[i].s;
    sort(a + 1, a + 1 + n, cmp);
    dp[0]=1;
	a[n+1].s=1e+4;
	a[n+1].w=m;//初始化 
    for(int i = n; i >= 1; i--)//从后往前 
        a[i].s=min(a[i].s,a[i+1].s+a[i+1].w-a[i].w);
    for(int i = 1; i <= n + 1; i++)//这个需要正序 
	{
        dp[i]=min(a[i].s, dp[i-1] + a[i].w - a[i-1].w);
        ans=max(ans, (dp[i] + dp[i-1] + a[i].w - a[i-1].w)/2);
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：Hisaishi_Kanade (赞：0)

首先，显然按照 $t_i$ 升序排序。

我们发现不能直接硬贪心，当 $s_i\gg s_{i+1}$ 但是 $t_i$ 相差不大时，就甚至无法满足条件。

那么我们必须先预处理出对于 $i$，我们在此能达到的最大速度 $p_i$，使得后面的速度都可以满足条件。

正着做显然是不行的，你不能预知后面的限制。所以倒过来做，$p_{i}=\min\{s_i,p_{i+1}+t_{i+1}-t_{i}\}$。

得到 $p$ 之后，我们要求出他能达到的最大速度了。

我们进行绘图。

如下图，$A,B$ 的纵坐标是 $s_i$，横坐标是 $t_i$，折线表现的是速度的变化。

[![p9UJ9z9.png](https://s1.ax1x.com/2023/05/05/p9UJ9z9.png)](https://imgse.com/i/p9UJ9z9)


$A\to B$ 的路径中，我们一共有五秒但是我们只能向上两格到达 $C$ 就得落回来。

这是距离差大于限制差的情况。

如果距离差小于限制差，那么就会出现本应 $A\to C$，但是距离不够只能 $A\to B$。

[![p9UJ3eP.png](https://s1.ax1x.com/2023/05/05/p9UJ3eP.png)](https://imgse.com/i/p9UJ3eP)

我们从头开始做，记录当前的速度。

如果是第一种情况，则记录这条折线的最高点为可能答案，取最大。

速度每计算一个都要更新，具体看代码。

```cpp
#include <stdio.h>
#include <iostream>
using std::cin;
#include <algorithm>
#define rep(i,l,r) for(i=l;i<=r;++i)
#define req(i,r,l) for(i=r;i>=l;--i)
#define ll long long
int t,n,i;
ll d1,d2,L;
const int N=200005;
ll pos[N],s[N],limit[N];
ll max(ll x,ll y){return x>y?x:y;}
ll min(ll x,ll y){return x<y?x:y;}
ll abs(ll x){return x<0?-x:x;}
class li
{
	public:long long pos,s;
	inline const bool operator<(const li &other)const
	{
		return pos<other.pos;
	}
}l[N];
int main()
{ 
//	int t;scanf("%d",&t);
//	while(t--)
//	{
		ll ret=0;
		scanf("%d %d",&L,&n);
		rep(i,1,n+1)
			limit[i]=0,l[i].pos=l[i].s=0;
		rep(i,1,n)
		{scanf("%lld %lld",&l[i].pos,&l[i].s);
		}
		std::sort(l+1,l+n+1);
		limit[n]=l[n].s;
		req(i,n-1,1)
			limit[i]=min(limit[i+1]-l[i].pos+l[i+1].pos,l[i].s);
		int p=1;;
		l[n+1].pos=L;
		limit[n+1]=1ll<<40;
		rep(i,0,n)
		{
			if(p+(l[i+1].pos-l[i].pos)<=limit[i+1])//第二种情况
				p+=l[i+1].pos-l[i].pos,ret=max(ret,p);
			else
			{
				int d=((p+l[i+1].pos-l[i].pos)-limit[i+1]+1)/2;//结合第一个图理解一下
				ret=max(ret,p+l[i+1].pos-l[i].pos-d);
				p=limit[i+1];//一定会落会限制
			}
		}
		printf("%lld\n",ret);
//	}
	return 0;
}
 

```

---

## 作者：QianhanOfficial (赞：0)

```cpp
//这道题算法是蒟蒻自己想出来的 竞赛课上被坑了一节课 终于想了出来一个方法
//代码可能有点长 但大部分都是代码风格原因orz 核心代码并不多
//我会尽量写出详细的解释 感谢观看。
/*
这里我的算法是：
1.正向扫一遍转弯处
2.反向扫一遍转弯处
3.正向扫一遍算出两点之间可达到的最大速度
那么，怎么扫呢？
我们可以发现 从上一个点(转弯处 下文简称"点")到下一个点 速度的增加和减少是受到距离限制的 而且变化量和距离相同。
这样如果画出一个平面直角坐标系 以x轴为t(距离)，以y轴为s(速度) 描上所有的点之后 他们的连线的斜率 就是我们“扫”的关键。
简单来说，正向扫的时候就是斜率<=1的我们不管，斜率>1的我们把斜率搞成斜率=1，而反向的时候就是斜率>-1的我们搞成斜率=-1。
怎么搞呢？
先正向枚举每一个点 如果当前点限速比上一个点限速大 且两点之间距离小于限速之差 那么就把枚举到的点的限速降低到上一个点的限速+两点之间距离(即Bessie能够在这段距离内达到的最大速度) 如果当前点比上一个点限速小 那就先不管 等着反向扫描帮我们处理。
反向的时候：基本相同 如果上一个点限速比当前限速大 且两点之间距离小于限速之差 那么就处理上一个点的限速到当前点的限速+两点距离 如果上一个点比当前点限速小 因为我们在正向的时候已经处理过了 所以不管。
最终我们会得到一个漂亮的坐标系图象 而聪明的你们会发现 其实在两点之间的这段距离中 Bessie的速度没有限制，也就是说我们可以在两点之间先加速再减速到限速大小 这样就能得到可能的最大值。
所以再枚举一遍所有的点 不过计算的是两点之间的最大速度(两点之间的最大速度>=限速较高的点的速度) 如何计算呢？看代码注释orz
最后 别忘了冲过终点的速度没有限制 所以比较一下得到的答案和最后一个点的限速+与终点距离。
*/
#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>

inline int readin()//优化读入
{
	int x = 0;
	bool shit = false;
	char ch = getchar();
	for(;!isdigit(ch); ch = getchar()) (ch == '-') && (shit = true);
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return shit ? -x : x;
}

inline int max(int x, int y)//手写max 快
{
	return x > y ? x : y;
}

struct node//结构体储存转弯处信息
{
	int t;//离起点距离
	int s;//限速
}a[233333];

int l, n, maxn;//l总长度 n转弯个数 maxn最终答案

inline bool cmp(node x, node y)//结构体排序比较
{
	return x.t < y.t;
}

int main()
{
	//freopen("testdata.in", "r", stdin);
	l = readin();
	n = readin();
	for(register int i = 1; i <= n; ++i)//常规读入
	{
		a[i].t = readin();
		a[i].s = readin();
	}
	a[0].t = 0;//初始化起点处离起点距离为0(废话
	a[0].s = 1;//这里设置初速度为1 题干中有说过 别忘了
	std::sort(a + 1, a + n + 1, cmp);//注意，给出的转弯顺序可能不是有序的
    //接下来是核心代码
	for(register int i = 1; i <= n; ++i)//正向扫一遍拐弯
	{
		if(a[i].s > a[i - 1].s)//如果当前点限速比上一个转弯处高
		{//注:初始状态也需要看作一个"转弯处"
			if(a[i].t - a[i - 1].t < a[i].s - a[i - 1].s)
			{
            	//如果两点之间距离比限速之差要小 证明从上一个点到当前点(i)不受速度限制 可以一直增加 速度增加的量就是两点距离 即a[i].t-a[i-1].t 然后加上上一个点的速度
				a[i].s = a[i].t - a[i - 1].t + a[i - 1].s;
			}
            //其他情况不管
		}
	}
	for(register int i = n; i >= 1; --i)//反向扫描
	{
		if(a[i - 1].s > a[i].s)//之前讲的比较清楚了 看代码
		{
			if(a[i].t - a[i - 1].t < a[i - 1].s - a[i].s)
			{
				a[i - 1].s = a[i].t - a[i - 1].t + a[i].s;
			}
		}
	}
	for(register int i = 1; i <= n; ++i)//比较一遍
	{
		int ta = a[i - 1].t + abs(a[i].s - a[i - 1].s);
        //我们如何计算两点之间速度的最大值呢？很明显我们构造的是一个斜边水平放置的等腰直角三角形 使两个点紧靠在直角边上 直角所在的点就是最大值 不过需要下取整
        //ta就是 与当前点关于三角形斜边上的高对称的点的横坐标 ta=上一个点的横坐标+两点限速之差 画个图就能清楚明白啦 
		int sa = max(a[i].s, a[i - 1].s);
        //sa是对称点的纵坐标 sa=两点间限速较大值
		int ans = (a[i].t - ta) / 2 + sa;
        //精髓 直角点纵坐标是对称两点的距离/2(下取整)+sa
		maxn = max(maxn, ans);
        //更新答案
        //可能有同学会问：遇到前一个点比后一个点高的情况怎么办？你这个不就凉了吗？其实并不是 如果分情况讨论，最终化简出的式子是一模一样的。
	}
	maxn = max(maxn, l - a[n].t + a[n].s);//比较终点 别忘了
	printf("%d", maxn);
	return 0;
}
```

---

