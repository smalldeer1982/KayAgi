# [BalticOI 2008] 手套

## 题目描述

化学教授名曰“酸雨”。在他家黑暗的地下室，有两个装有手套的抽屉，一个抽屉装左手手套，另一个装右手手套。每个抽屉中有 $n$ 种不同颜色的手套。教授知道在每个抽屉中，每种颜色的手套数目（在不同抽屉中，相同颜色的手套数目可能不同）。保证他能够找到同色的一副手套。

只有教授带相同颜色的一副手套时试验才可能会成功（与哪种颜色无关），所以在每次试验开始之前他都要去地下室从抽屉中拿手套，并且希望至少有一副一样颜色的手套。但是地下室太黑了，不出地下室就不可能分辨出任何手套的颜色。教授讨厌去地下室超过一次，同时也讨厌拿一堆手套回实验室（以防没有相同颜色的手套）。

#任务

写一个程序能够：

-    从标准输入中读取颜色种数和每种颜色手套的数目
-    计算在确保拿出的手套中有一副颜色相同的手套的情况下需要取出手套的最小数目（需要明确指出从每个抽屉中取出手套的确切数目）
-    将结果写到标准输出


## 说明/提示

有 $40$ 分 $n\le 4$ 且 $a_i,b_i\le 10$。 

对于所有数据，$1\le n\le 20$。

## 样例 #1

### 输入

```
4
0 7 1 6
1 5 0 6```

### 输出

```
2
8```

# 题解

## 作者：ModestCoder_ (赞：12)

先随便选择左手套的颜色，把一些颜色的左手套都取光，那么在这个情况下，右手套至少取多少只？

从样例下手
```
4
0 7 1 6
1 5 0 6
左手套选了2、3两种颜色，拿了8只手套，右手套就至少拿8个（1、4两种颜色手套都要拿，再多拿一只）
```


对于每种取颜色方案，都会得到一个二元组$(x,y)$表示这些颜色的左手套数量之和x，这些颜色的补集的右手套数量之和y

把这个二元组对应到平面直角坐标系里面，得到几何意义：$(0,0)$到$(x,y)$组成的矩形中的点都是不合法的方案

然后可以$O(2^n)$枚举所有颜色方案得到$2^n$个矩形，把这写矩形弄到坐标系里面，形成如下图

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190829192021450.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)

其中红点表示一个二元组，因为任何矩形里面的点是不可行的，然后发现这些矩形有一个**外围**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190829192551655.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)

蓝线表示外围，发现图中黄点是可以代表所有方案的，现在把问题转化成，对于所有黄点$(x,y)$，求$min(x+1+y+1)$

因为光是x和y是不满足要求，都各多取一只才满足要求

然后求黄点的坐标就是先预处理出所有矩形的右上角，然后排个序(x为第一关键字，y为第二关键字)，用个单调栈把黄点处理出来再算答案

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 2000010
using namespace std;
struct node{
	int x, y;
}s[maxn], stk[maxn];
int a[maxn], b[maxn], n, tot, top, ans1, ans2;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp(node x, node y){ return x.x == y.x ? x.y > y.y : x.x < y.x; }

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) b[i] = read();
	tot = 1 << n; 
	for (int i = 1; i <= tot; ++i)
		for (int j = 0; j < n; ++j)
			if ((i >> j) & 1) s[i].x += a[j + 1]; else s[i].y += b[j + 1];
	sort(s + 1, s + 1 + tot, cmp);
	s[0].x = s[1].x - 1;
	for (int i = 1; i <= tot; ++i){
		if (s[i].x == s[i - 1].x) continue;
		while (top && stk[top].y <= s[i].y) --top;
		stk[++top] = s[i];
	}
	int Max = 2147483647;
	for (int i = 2; i <= top; ++i)
		if (stk[i - 1].x + stk[i].y + 2 < Max)
			Max = stk[i - 1].x + stk[i].y + 2, ans1 = stk[i - 1].x + 1, ans2 = stk[i].y + 1;
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}
```


---

## 作者：Piwry (赞：3)

这题的题解数量好少...仅有的两篇题解的偏重点也都不同..虽然我也没法给出完全准确的解释，但还是就我个人理解写一下题解吧。

~~（话说如果不在意花纹的话手套是不分左右的吧（~~

（话说这还是我第一次写集合符号...如有不规范还请指出qwq）

关于符号：本文中 $A\subseteq B$ 表示 $A$ 是 $B$ 的子集（可能相等）， $A\subsetneq B$表示 $A$ 示 $B$ 的真子集；点坐标默认整数。

# 解析

对于每一种取法，我们设在左抽屉取了多少手套 $sl$ 以及在右抽屉取了多少手套 $sr$。那么就得到所有状态 $P=\{(sl, sr) | sl, sr\in N^{+}\}$，如果把这个二元组集合映射到坐标系，就可以得到一张含有**所有状态**的平面图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zaubilgu.png)
 _（图中数据不保证合法）_ 

但一部分元素是有特殊含义的，它们可能表示了**某种边界**。

我们考虑一种**最坏情况**：设颜色全集 $C=\{col|col\in N^{+}\}$，我们在左抽屉取走了颜色属于 $L, L\subseteq C$ 的所有手套，在右抽屉取走了颜色属于 $R, R=∁_CL$ 的所有手套。这时候，只要我们取 $∀col, col\in C$ 颜色的手套（也就是两个抽屉中随便拿一个）就可以满足题目条件。我们定这种情况为 `<状态一>`。

再将这个 "状态点" $(sl, sr)$ 和点 $(0, 0)$ 为对角端点做矩形，观察不在坐标轴上的那两条边：

![](https://cdn.luogu.com.cn/upload/image_hosting/37vav0n1.png)
~~（话说这里 $s, l$ 标反了...）~~

1. 对于平行于 $x$ 轴的边上的所有的点，只有 $sr$ 在变化。

2. 对于平行于 $y$ 轴上的边上的所有的点，只有 $sl$ 在变化。

如果这些点的 $L,R$ 没有变化，我们只需取 "不变的坐标" 所对应的抽屉的任意一只手套，仍旧可以满足题目条件。我们定这种情况为 `<状态二>`（不含 "如果"）。

而对于 "矩形内"（**不包括上述两条边**）的点，由于两个坐标都在变化，我们无法仅取一个手套就满足题目条件，设为 `<状态三>`。

但我们需要考虑**所有** `<状态一>` 的点产生的矩形，才能**确定**这些点的特殊含义。

不过在考虑它们的叠加效应之前，我们要先确认一件事：

- 为了确保有同色手套，我们考虑的是**最坏情况下**的答案，也就是说如果说一个点既是 `<状态一>`，又是 `<状态二>`，并**不会产生冲突且 "取" `<状态二>`；** 如果说一个点既是 `<状态一> `或 `<状态二>`，又说它是 `<状态三>`，我们 "取" 后者。

现在我们来看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zaubilgu.png)

设点集 $S$，$S$由所有**是且仅是**某个矩形的特定边（非坐标轴上边，统计边端点但右上角端点例外）上，且不在其它矩形内（不包括边）的点，**或**其右上角且不在其它矩形内的端点的坐标组成。

可以发现 $S$ 的所有元素正好形成了一条 "分界线"，而这条分界线的右上部分（不包括线，要求 $sl, sr$ 不能大于最多可取的值）就是**所有可能的答案。**

![](https://cdn.luogu.com.cn/upload/image_hosting/qo2rsmfi.png)

（注意像 $F_1-E$ 这坐标上的一段也是边）

实际上 $S$ 的元素就表示了一种 "边界"：对于上述边上的点（这里不包括边交接处点但包括端点），总保证再取一个手套（未规定左右抽屉）就可以满足题目条件；对于边的交界点，可以想到此时正好**有且仅有一个**颜色的手套没有出现（其他颜色则分别在左或右抽屉中都被取走了），而这种颜色**有且仅有两种**可能（由相交的边所属的端点决定）。可以知道 $S$ 包含所有可能的 （最坏）"边界状态"。

最后是求解的部分。只需在右上角这些点中找到一个 $x+y$ 最小的点就可以了。而根据单调性我们发现分界线外围一层的点最优，而这些点中又数 "凹进去" 的最 "里端" 点最优，易知满足条件的点数量是 $2^n$ 级，枚举求解即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/pi0h3z7h.png)

至于求边界线，按一个坐标排序后用单调栈依次尝试入栈即可。

# CODE

```cpp
#include <cstdio>
#include <algorithm>
using std::sort;
using std::pair;
typedef pair<int, int> pad;/*?*/

const int MAXN =20+1;

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int l[MAXN], r[MAXN];
int sl[1<<MAXN], sr[1<<MAXN]/*下标二进制中的 1代表拿，0代表不拿（完）*/, lg[1<<MAXN];
pad cache[1<<MAXN], stk[1<<MAXN];
int tot;

int main(){
	int n =read();
	for(int i =0; i < n; ++i) l[i] =read();
	for(int i =0; i < n; ++i) r[i] =read();
	for(int i =2; i <= (1<<n); ++i) lg[i] =lg[i>>1]+1;
	/*这里理解下就好，i&-i见 lowbit*/
	for(int i =1; i < (1<<n); ++i) sl[i] =sl[(i&(-i))^i]+l[lg[i&(-i)]];
	for(int i =1; i < (1<<n); ++i) sr[i] =sr[(i&(-i))^i]+r[lg[i&(-i)]];
	for(int i =0; i < (1<<n); ++i) cache[i] =pad(sl[i], sr[((1<<n)-1)^i]);
	sort(cache, cache+(1<<n));
	for(int i =0; i < (1<<n); ++i){
		pad nw =cache[i];
		while(tot && nw.second >= stk[tot-1].second) --tot;
		stk[tot++] =nw;
	}
	/*这里直接找边的交界点*/
	pad ans =pad(0x5fffffff, 0x5fffffff);
	for(int i =1; i < tot; ++i)
		if(stk[i-1].first*1ll+stk[i].second < ans.first*1ll+ans.second) ans =pad(stk[i-1].first, stk[i].second);
	printf("%d\n%d", ans.first+1, ans.second+1);
}
```


---

## 作者：ghruik (赞：3)

  	发现这道题洛谷上居然没有题解，于是来补上一篇。  (	请不要吐槽我的码风）  
   
前言：首先这道题初看下来，很简单，不就小学奥数，爆搜搞掉，一顿乱贪心。就可以AC吗？ 
    
  旁边的大佬提醒我，在标签难度修改的情况下，还能有紫题，肯定不简单。于是我打了两个完美的零分算法。  
 最后迫于无奈，看了题解才写出，并且又坚定了我打题解的决心，全网上只有三篇题解，而且还有一篇官方题解（~~英文劝退~~）。   
  
  干货：首先定义x与y。x为取多少左手手套，y为取多少右手手套。
  
  再定义一种状态，完美最差状态，就是取得x，y中完美地没有相同颜色，且x或y再+1，就可能是可行答案（为什么是可能？我们等会再讲）。  
  
  最后定义最差状态，就是在某种完美最差状态x1，y1下，(x<x1,y=y1)或(x=x1,y<y1)或(x<x1,y<y1) 。其中也很好理解  那么多的x1,y1都不可能保证取到，取到的数量比其小，怎么可能是答案？  
  
  然后开始转化题目，
  我们要打破完美最差状况，找到一种可行的状态
  也就是 求一个点（x，y），它不在矩形（0,0）到（x[i],y[i]）之间（包括边）且（x+y最小）。于是问题开始。  
  （1）怎么求x[i],y[i]。  
  （2）怎么求这个点。![1.png](https://i.loli.net/2019/08/19/KyDG32aYkPEWczA.png)
  
  首先（1）问题。n<=20给了我们提示，可以直接爆搜，求出 $2^n$个完美最差状况，也就是对于每一个手套，要么取完左手，要么取完右手。于是对于每副手套爆搜下来，利用$2^n$的代价求出$2^n$种完美最差状况。    
  
  代码如下  
 ```
void chu()
{   
	tot++;
	for (i=1;i<=n;i++)
	  if  (s[i]==1) ans[tot].x+=a[i];
	  else ans[tot].y+=b[i];
}
void dfs(int x)
{
	if (x>n) {chu();return;}
	s[x]=0;dfs(x+1);
	s[x]=1;dfs(x+1);
}
```

  然后（2）问题。我们已经求出了这些矩形，然后显而易见，对于每个拐角处的点（x，y），（x+1，y+1）是可能的最优解。  
  
  证明如下
  对于每一个矩形与其他矩形相交的地方为拐角点，也就是标红点处（落了一个点没涂，不过不影响理解）
  ![1.png](https://i.loli.net/2019/08/19/9DqAYbw5xu7gGfS.png)
  
  对于每条边与另一条边相交的地方的（x，y）x与y都再+1  
  比在这条边其他地方使用此操作会更优。  
  
  然后对于每个点都使用此操作，记录当前的x与y是否最优。就在这时，你突然发现了一个有趣的地方。也就是我之前留下的可能。
  
  ![1.png](https://i.loli.net/2019/08/19/LuFDZY3mJqliy6z.png)
  
  这几个涂绿的点（依旧落下了那个点，不过依旧不影响理解）
  他们 即使使用上述操作，所得到的的点依旧是不可以的，因为那些点，被包括在其他矩形里
  所以我们要删去这些点，删去方法为删去使那些点产生的矩形就是被完美包住的矩形
  
  删去后![1.png](https://i.loli.net/2019/08/19/3cWFIObe7rCq2tU.png)
  
  ~~请不要吐槽我改好后的图~~，然后对于每个拐角进行上述操作，即可得到答案。删去方法为，先以某一维排序（可以从小到大也可以从大到小，作者用的从大到小），再使用单调栈求出一串上升序列（当前一维按从小到大排的话，求一串下降序列）当横坐标相同时取最大的纵坐标
  
  代码如下
```
    sort(ans+1,ans+1+tot,cmp);
    int x=-1,z=0,big=-1;
    for (i=1;i<=tot;i++)
    {
    	if (ans[i].x==x)
    	{
    		 if (ans[i].y>big)
        	 {
          	c[z].y=ans[i].y;
           	big=ans[i].y;
         	 }   
	}
	 else {
		if (ans[i].y>big)
		{ 
		z++;
		c[z].x=ans[i].x;
		c[z].y=ans[i].y;
   	        big=ans[i].y;
		x=ans[i].x;
         	}
	      }
    }
	for (i=1;i<=z-1;i++)
	{
		if (c[i+1].x+c[i].y+2<mmin)
		{
			mmin=c[i+1].x+c[i].y+2;
			k1=c[i+1].x+1;
			k2=c[i].y+1;
		}
	}
```
最后是总代码

```
#include<bits/stdc++.h>
using namespace std;	int mmin=2000000010,ans1,ans2,s[100],k1,k2,tot;
int n,i;
int a[100],b[100];
struct LINE{
	int x,y;
}ans[2000000],c[2000000];
bool cmp(LINE a1,LINE a2)
{
	return a1.x>a2.x;
}//从大到小排序
void chu()
{  	 tot++;
	 for (i=1;i<=n;i++)
	 if  (s[i]==1) ans[tot].x+=a[i];//如果当前是1则取左手套否则取右手套	  
         else ans[tot].y+=b[i];
}
void dfs(int x)
{
	if (x>n) 
	{chu();return;}
	s[x]=0;dfs(x+1);
	s[x]=1;dfs(x+1);//标准爆搜
}
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for (i=1;i<=n;i++)
	scanf("%d",&b[i]);

    	dfs(1);
    	sort(ans+1,ans+1+tot,cmp);
    	int x=-1,z=0,big=-1;
    	for (i=1;i<=tot;i++)
        {
    	  if (ans[i].x==x)//当横坐标相同时，要取最大的纵坐标
    	  {
    		if (ans[i].y>big)
    		{
    		 c[z].y=ans[i].y;big=ans[i].y;、、更新
                }
  	  }
	   else {
		if (ans[i].y>big)
		{ 
		z++;
		c[z].x=ans[i].x;
		c[z].y=ans[i].y;big=ans[i].y;//当x减小时，求上升的y
		x=ans[i].x;}
		}
		}
	for (i=1;i<=z-1;i++)
	{
		if (c[i+1].x+c[i].y+2<mmin)
		{
		mmin=c[i+1].x+c[i].y+2;
		k1=c[i+1].x+1;
		k2=c[i].y+1;
		}//查找
	}
	printf("%d\n%d",k1,k2);
}
	
```

  
  
  
  
  
  

---

## 作者：Cry_For_theMoon (赞：1)

想起了自己的小奥学习时光......

--------

是小奥里最不利原则的一个应用题。

假设左边取 $x$ 个，右边取 $y$ 个。如果有一种方案，使得选取以后不能配对成一副手套，则这样取是不合要求的。

所谓“最不利”是这样的一类状态：当前状态不合题意，但是任意进行一步就会符合题意。考虑颜色集合 $U=\{1,2,...,n\}$，记 $S$ 是一个 $U$ 的子集，而 $T$ 是 $S$ 在 $U$ 中的补集。那么当我们把 $L$ 中颜色属于 $S$ 的全部取走，把 $R$ 中颜色属于 $T$ 的全部取走，此时就是一个最不利状态：无法形成一幅手套，但是下一次随便取能取的一边，一定能形成一幅手套。

我们容易发现，本题中，“最不利状态”只可能是上述的这种形态。换言之，有 $2^n$ 个最不利状态。

一个状态合法，就不能弱于最不利状态。换言之对于所有的最不利状态 $(x_i,y_i)$。我们选取的状态 $(x,y)$ 要满足 $x\gt x_i \lor y\gt y_i$。我们的目标是最小化 $x+y$ 的和。此时这个问题变得可做起来。

注意到，要么存在某个 $i$ 满足 $x=x_i+1$ ，或者存在某个 $j$ 满足 $y=y_j+1$，这样答案才是最优秀的。

我们不妨设 $x=x_i+1$ 这种情况满足（另一种同理），则我们暴力枚举 $x_i+1$，对于所有的 $x_j\gt x_i$，记 $maxy=\max\{y_j\}$，则此时的最优秀点对是 $(x_i+1,maxy+1)$。但是要注意到当 $|L|\lt x_i+1$ 或者 $|R|\lt maxy+1$ 的时候这种取法是不存在的，需要特判。

那么通过初始把 $x_i$ 降序排序，就可以在 $O(n\times 2^n)$ 的时间内解决这个问题。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const ll MAXN=20,INF=1e18;
int n,a[MAXN],b[MAXN];
ll f[1<<MAXN],g[1<<MAXN],ans=INF;
ll A,B;
array<ll,2>ret[1<<MAXN];
ll st[(1<<MAXN)+1],top;
bool cmp1(const array<ll,2>& a1,const array<ll,2>& a2){
    return a1[0]>a2[0];
}
bool cmp2(const array<ll,2>& a1,const array<ll,2>& a2){
    return a1[1]>a2[1];
}
int main(){
    cin>>n;
    rep(i,0,n-1)cin>>a[i],f[1<<i]=a[i];
    rep(i,0,n-1)cin>>b[i],g[1<<i]=b[i];
    rep(i,1,(1<<n)-1){
        f[i]=f[lowbit(i)]+f[i^lowbit(i)];
        g[i]=g[lowbit(i)]+g[i^lowbit(i)];
    }
    rep(i,0,(1<<n)-1){
        ret[i]={f[i],g[((1<<n)-1)^i]};
    }
    sort(ret,ret+(1<<n),cmp1);
    ll maxy=-INF;
    rep(i,0,(1<<n)-1){
        ll val=ret[i][0]+1+max(1LL,maxy+1);
        if(val<ans && ret[i][0]!=f[(1<<n)-1] && maxy!=g[(1<<n)-1]){
            ans=val;A=ret[i][0]+1;B=max(1LL,maxy+1);
        }
        maxy=max(maxy,ret[i][1]);
    }
    sort(ret,ret+(1<<n),cmp2);
    ll maxx=-INF;
    rep(i,0,(1<<n)-1){
        ll val=ret[i][1]+1+max(1LL,maxx+1);
        if(val<ans && ret[i][1]!=g[(1<<n)-1] && maxx!=f[(1<<n)-1]){
            ans=val;A=max(1LL,maxx+1);B=ret[i][1]+1;
        }
        maxx=max(maxx,ret[i][0]);
    }
    cout<<A<<endl<<B<<endl;

    return 0;
}
```

---

## 作者：masonpop (赞：0)

先固定数量 $(x,y)$，考虑如何判断是否合法。很容易形式化描述，即如下命题。

不存在将 $\{1,2,\cdots,n\}$ 划分成两个不交集合 $\{p_1,p_2,\cdots,p_k\}$ 和 $\{q_1,q_2,\cdots,q_{n-k}\}$ 的方案，使得：

① $\sum\limits_{i=1}^ka_{p_i}\ge x$

② $\sum\limits_{i=1}^{n-k}b_{q_i}\ge y$

这个很好理解，就是无论如何，你都不能从两堆不交的颜色中一边取 $x$ 个，一边取 $y$ 个。

接下来的转化很显然。注意到一共只有 $O(2^n)$ 个这样的约束条件，将 $(x,y)$ 视为坐标系内的点，问题进一步转化为：

有 $m$ 个长宽均在坐标轴上的矩形，右上坐标均给定，已知点 $(x,y)$ 不包含于这些矩形的并，最小化 $x+y$。

画个图。大概长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/9v0gmwqz.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

很容易发现，最优的点一定是标绿的这些点横纵坐标均 $+1$ 的结果。而这些点个数也是 $O(2^n)$ 的，至于这个矩形并的轮廓，单调栈维护即可。

（这里图手抖画错了，显然最两边那两个绿点取不到，知道就行）

总复杂度 $O(2^n)$。[代码](https://www.luogu.com.cn/paste/bpz1m8ho)。

---

