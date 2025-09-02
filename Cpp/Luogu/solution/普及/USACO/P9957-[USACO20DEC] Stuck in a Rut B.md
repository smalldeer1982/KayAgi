# [USACO20DEC] Stuck in a Rut B

## 题目描述

Farmer John 最近扩大了他的农场，从奶牛们的角度看来这个农场相当于是无限大了！奶牛们将农场上放牧的区域想作是一个由正方形方格组成的无限大二维方阵，每个方格中均有美味的草（将每个方格看作是棋盘上的一个方格）。Farmer John 的 $N$ 头奶牛（$1\le N\le 50$）初始时位于不同的方格中，一部分朝向北面，一部分朝向东面。

每一小时，每头奶牛会执行以下二者之一：

 - 如果她当前所在的方格里的草已经被其他奶牛吃掉了，则她会停下。
 - 吃完她当前所在的方格中的所有草，并向她朝向的方向移动一个方格。

经过一段时间，每头奶牛的身后会留下一条被啃秃了的轨迹。

如果两头奶牛在一次移动中移动到了同一个有草的方格，她们会分享这个方格中的草，并在下一个小时继续沿她们朝向的方向移动。

请求出每头奶牛吃到的草的数量。有些奶牛永远不会停下，从而吃到无限多的草。 

## 说明/提示

### 测试点性质

 - 测试点 $2-5$ 中，所有坐标不超过 $100$。
 - 测试点 $6-10$ 没有额外限制。

## 样例 #1

### 输入

```
6
E 3 5
N 5 3
E 4 6
E 10 4
N 11 2
N 8 1```

### 输出

```
5
3
Infinity
Infinity
2
5```

# 题解

## 作者：FZY_CZY (赞：7)

这道题是在老师举办的 CSP-J 的模拟赛上见到的，赛上寄了，没写出来，痛定思痛，决定写着一篇题解。

题意就不赘述了，不懂的看这里：[题目](https://www.luogu.com.cn/problem/P9957)。

其实一开始我是想打暴力的，但是不会打。

后来想到了正解，结果打不出来。（也就是浅浅想了一个小时而已）

首先讲思路，思路很简单，就是对于每一个奶牛做一条它方向的射线，然后对于一条射线上没有任何交点的奶牛来说，它可以无限吃下去。

首先我们要去判断 $AO$ 与 $BO$ 的位置关系，第一步，不能使 $AO$ $\parallel$ $BO$，因为明显的，$AO$ 和 $BO$ 不能平行；然后对于每一个交点（这里统一称为 $O$ 点）：若 $AO>BO$ 则 $B$ 点在 $O$ 点时会停下；反之亦然。特别需要注意的是，若 $AO=BO$ 则不会停下。（由题意可得）

为了~~压缩时间复杂度~~保证当前奶牛的停止位置是在正确的位置（即遇到的第一个空地），我们需要进行排序（这个只是单独提出来，没必要说太多了）然后进行遍历，一次保证答案的正确性，这个就没什么多说的了，主要的思路大概就这么多了，剩下零碎的看代码注释。
```cpp
#include<bits/stdc++.h>
#define maxn 55
using namespace std;
struct node{
	int x,y,id;
};//结构体方便排序和处理
node N[maxn],E[maxn];
int sum_n,sum_e,ans[55];
bool cmp1(node a, node b)
{
	return a.x<b.x;
}
bool cmp2(node a, node b)
{
	return a.y<b.y;
}
int main(){
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		char c;
		int x,y;
		scanf(" %c%d%d",&c,&x,&y);//输入
		if (c=='N') N[++sum_n]={x,y,i};
		else E[++sum_e]={x,y,i};
	}
	sort(N+1,N+sum_n+1,cmp1);
	sort(E+1,E+sum_e+1,cmp2);
	//排序后可以减时间复杂度并且简化代码
	for (int i=1;i<=sum_e;i++)
	{
		for (int j=1;j<=sum_n;j++)//双重for，没什么好说的
		{
			if (N[j].x<E[i].x) continue;//如果这两条射线不相交就不存在交点O
			if (N[j].y>E[i].y) continue;//同上
			int A=N[j].x-E[i].x;
			int B=E[i].y-N[j].y;
			if (ans[N[j].id]) continue;//如果N[j]已经有答案，那么这就是最优的了（排过序）
			if (A<B) ans[N[j].id]=B;//如果AO<BO则B是A的答案
			if (A>B)
			{
				ans[E[i].id]=A;//同理
				break;//第一个即最优解，没必要继续遍历
			}
		}
	}
  //值得一提的是，不需要两次双for，因为在找E的最优解的时候，也找到了N的最优解，所以只需要一次双for就OK了（我模拟赛就是疯了，写了两次，而且都写错了）
	for (int i=1;i<=n;i++)
	{
		if (ans[i]) printf("%d\n",ans[i]);//奶牛会适量进食
		else printf("Infinity\n");//奶牛会吃撑死
	}
	return 0;
}
```

---

## 作者：ABCDEFG12345NM (赞：6)

起初写的时候少考虑了一个条件，然后在漫长的改正后代码量翻了一倍，结果竟奇迹般地对了。我看其它题解将思路讲完了，那我就写一下我这个代码的思路吧！

---

正片开始……

## 题目传送门 | Portals

[[USACO20DEC] Stuck in a Rut B](https://www.luogu.com.cn/problem/P9957)

---

## 题意归纳 | Title

在一个**无限大**的矩阵内有 $N$ 个点，每个点自出始位置朝给定方向运动，如果碰到其他点的轨迹就停止。  
输出每个点经过的格子数，如果并未被阻拦，那么输出 `Infinity`。

## 题目分析 | Analyse

当看到这道题的时候，我以为是大模拟，读题时 $10 ^ 9$ 的范围给我干沉默了。  
死了但还没死绝，灵光乍现……

在题目中我们可以发现，$N$ 只有 $50$，微乎其微，那么我们为什么不用 $O(N^2)$ 的时间复杂度枚举每个点对，接着用 $O(1)$ 的时间复杂度求点是否被截住与被截住时的长度呢？

有了这个**重大发现**后，重点就到了如何求被截住时的长度上面。

## 解题思路 | Thinking

**重点考虑一下如何分类讨论被截住时的长度**：

题面中写着：“所有 $x$ 坐标各不相同，所有 $y$ 坐标各不相同”，所以肯定不会出现同方向追上的状况，接着我们只用遍历方向不同的点对了。

假设点对 $A,B$ 中 $A$ 的位置为 $(x1,y1)$，$B$ 的位置为 $(x2,y2)$。  
他们相遇的地点肯定在 $(x1,y2)$ 或 $(x2,y1)$，具体在那里取决于两点的位置。  
下一步我们就可以求出两点到相遇位置的距离，再进行比较：
- 如果距离相等，则未被阻拦。
- 如果 $A$ 的距离大于 $B$，则 $B$ 阻拦 $A$。
- 如果 $B$ 的距离大于 $A$，则 $A$ 阻拦 $B$。

最后打擂台求出最近被阻截的地方，输出答案。

### 请注意：

如果一头奶牛提前被阻截了，就不会影响之后的奶牛了。对此，我先算出了每头奶牛被阻截的位置，接着计算时判断是否高于其被阻截的位置，这样就解决了。

## Code

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 5e1 + 10;
struct node
{
	bool fx;
	long long x, y;
} fe[MAXN];
struct WZ
{
	long long x, y;
} wz[MAXN];
long long ans;

int main ()
{
	long long N;
	cin >> N;
	for (int i = 1; i <= N; i ++)
	{
		char sx;
		cin >> sx >> fe[i].x >> fe[i].y;
		if (sx == 'E') fe[i].fx = true;
		else fe[i].fx = false;
	}
	for (int i = 1; i <= N; i ++)
	{
		ans = 1e9 + 10;
		for (int j = 1; j <= N; j ++)
		{
			if (i == j || fe[i].fx == fe[j].fx) continue;
			if (fe[i].fx == true)
			{
				if (fe[i].x > fe[j].x || fe[i].y < fe[j].y) continue;
				if (abs (fe[i].x - fe[j].x) <= abs (fe[i].y - fe[j].y)) continue;
				else
					if (ans > abs (fe[i].x - fe[j].x))
					{
						wz[i].x = fe[j].x, wz[i].y = fe[i].y;
						ans = abs (fe[i].x - fe[j].x);
					}
			}
			if (fe[i].fx == false)
			{
				if (fe[i].y > fe[j].y || fe[i].x < fe[j].x) continue;
				if (abs (fe[i].x - fe[j].x) >= abs (fe[i].y - fe[j].y)) continue;
				else
					if (ans > abs (fe[i].y - fe[j].y))
					{
						wz[i].x = fe[i].x, wz[i].y = fe[j].y;
						ans = abs (fe[i].y - fe[j].y);
					}
			}
		}
	}
	for (int i = 1; i <= N; i ++)
		if (wz[i].x == 0 && wz[i].y == 0)
			wz[i].x = 1e9 + 10, wz[i].y = 1e9 + 10;
	for (int i = 1; i <= N; i ++)
	{
		ans = 1e9 + 10;
		for (int j = 1; j <= N; j ++)
		{
			if (i == j || fe[i].fx == fe[j].fx) continue;
			if (fe[i].fx == true)
			{
				if (fe[i].x > fe[j].x || fe[i].y < fe[j].y) continue;
				else if (abs (fe[i].x - fe[j].x) <= abs (fe[i].y - fe[j].y)) continue;
				else if (fe[i].y > wz[j].y) continue;
				else ans = min (ans, abs (fe[i].x - fe[j].x));
			}
			if (fe[i].fx == false)
			{
				if (fe[i].y > fe[j].y || fe[i].x < fe[j].x) continue;
				else if (abs (fe[i].x - fe[j].x) >= abs (fe[i].y - fe[j].y)) continue;
				else if (fe[i].x > wz[j].x) continue;
				else ans = min (ans, abs (fe[i].y - fe[j].y));
			}
		}
        if (ans == 1e9 + 10) cout << "Infinity" << endl;
        else cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：blankslpl (赞：4)

# P9957 [USACO20DEC] Stuck in a Rut B
## 题意归纳：
- 在一个被视为无限大二维方阵的农场中，每个方格都有草，有 $N$ 牛（$1$ $\le$ $N$ $\le$ $50$）初始分布在不同方格，且朝向为北面或东面。
- 牛行为：每小时每条牛执行以下操作之一：若当前方格草已被其他牛吃掉则停下；否则吃完当前方格草，并按朝向移动一格。若两条牛在移动中到达同一有草方格，它们分享草后继续按原方向移动。
- 问题求解：要求计算出每条牛最终吃到的草数量，部分牛可能因永远不会停下而吃到无限多草。
## 题目思路：
- 主要围绕牛之间的相互阻拦来计算移动方格数（即吃到草数量），没有直接处理方格中草是否已被吃掉的情况。
- 北为向上，东为向右。
- 创建结构体数组去保存每条牛的输入顺序、$x$ 坐标、$y$ 坐标、$x+y$、走的方格数量。
- 根据思路优化，将结构体数组进行排序，只有排序后处在前面的牛才有可能阻拦当前这条牛。
- 同一条斜线或者同一个方向的牛，肯定拦不住。
- 然后就是考虑两条牛方向不同的情况，并找到最短的方格数。
## 思路优化点：
为何需要两个 cmp 排序：
- cmp1 为根据 $x+y$ 进行排序；cmp2  为根据 $id$ 排序，即恢复初始输入顺序排序
- 在判断牛之间的阻拦关系时，按 $x+y$ 排序是一种巧妙的策略，它能帮助我们按照一种合理的顺序去依次检查每条牛是否会被其他牛阻拦。排序后，前面的牛在某种程度上更有可能阻拦后面的牛（基于它们在二维平面上相对位置的一种潜在关联性）。因为这个排序值综合考虑了横坐标和纵坐标，能大致反映牛在二维方阵中的一种相对先后顺序，方便后续依次遍历判断阻拦情况。
- 当按 $x + y$ 从大到小排序后，在遍历判断阻拦时，只需要考虑前面的牛对当前牛的阻拦情况即可（内层循环中 $j < i$），这样缩小了需要检查的范围，使得阻拦判断的逻辑更容易实现和理解。例如，如果不进行这样的排序，要判断一条牛是否会被其他所有牛阻拦，就需要进行更复杂的两两比较逻辑，而现在基于排序后的顺序依次检查，大大简化了代码实现过程中的比较和判断逻辑，提高了效率并且让代码结构更清晰。
## Ac Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _ read<int>()
template <class T>inline T read()
{
	T r=0,f=1;char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-') f=-1;c=getchar();
	}
	while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f*r;
}
inline void out(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x<10) putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
int inf=2e9;
struct fish
{
	long long id, x, y, z, d;//x,y是初始位置，d是走的方格数量 
	char fx;//方向 
}a[100];
int n; 
bool cmp1(fish m, fish n)//按行列坐标之和进行排序排序
{
	return m.z > n.z;
}
bool cmp2(fish m, fish n)//把顺序调整回输入时候的顺序 
{
	return m.id < n.id; 
}
signed main()
{
	n=_;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		char c;
		cin>>c;//每头牛所在的x和y坐标不同 
		x=_,y=_;
		a[i]={i,x,y,x+y,inf,c};//无穷大 
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)//遍历每一头牛 
	{
		for(int j=1;j<i;j++)//只有前面的点才有可能阻拦第i头牛
		{
			if(a[j].z == a[i].z || a[j].fx == a[i].fx) continue;//同一条斜线或者同一个方向的牛，肯定拦不住 
			if(a[i].fx == 'E' && a[j].fx == 'N')//i为向右的，j向上，然后找出最快拦住这条牛的步数 
			{
				if(a[i].y < a[j].y) continue;//i在j的下方，肯定拦不住 
				if(a[j].y+a[j].d > a[i].y) a[i].d = min(a[i].d, a[j].x-a[i].x);//j所在y加上移动步数如果大于i所在y，可以拦截 
			}
			else//i为向上，j为向右 
			{
				if(a[i].x < a[j].x) continue;//i在j的左方，肯定拦不住 
				if(a[j].x+a[j].d > a[i].x) a[i].d = min(a[i].d, a[j].y-a[i].y);//j所在x加上移动步数如果大于i所在x，可以拦截 
			}
		} 
	}
	sort(a+1,a+n+1,cmp2); 
	for(int i=1;i<=n;i++)
	{
		if(a[i].d==inf) puts("Infinity");
		else 
		{
			out(a[i].d);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：Arson1st (赞：3)

## [P9957 [USACO20DEC] Stuck in a Rut B](https://www.luogu.com.cn/problem/P9957) 题解

### 排序+枚举

题目链接见上。题意比较清楚了，我们考虑如何计算答案。

首先可以抽象出 $n$ 条横平竖直的射线：（以样例为例，记端点为大写字母，射线为小写字母）

![样例解释](https://cdn.luogu.com.cn/upload/image_hosting/3kvgxzsj.png)

以射线 $i$ 为例。我们计算其能延伸的长度时应依次枚举其与射线 $h,f,k$ 的交点，比较交点到各自射线端点的距离。设交点为 $O$，那么一旦有 $CO>XO(X={B,F,E})$，则说明从 $C$ 引出的这条射线被挡住了，答案即为 $CO$。反之可更新竖直射线答案。也就是说，我们依次枚举端点在它右下方的射线并更新两者答案即可。若不能更新，则记为 $INF$。但是事情没有这么简单，考虑从 $E$ 点引出的射线 $k$，不难发现虽然 $EO<CO$，但 $EO'>DO'$！也就是说，看似 $k$ 能挡住 $i$，可实际上 $k$ 事先就被 $j$ 挡住了。所以我们需要先考虑下面的水平射线，使其先过滤被挡住的竖直射线。

这启示我们应当对两类射线分别排序，将竖直的射线按 $x$ 坐标，水平的射线按 $y$ 坐标从小到大排序。排序后选定一类（这里选择水平类），然后枚举另一类合法的射线（端点位于右下方的竖直射线，且尚未被阻挡的），通过交点更新答案。注意，一旦能够更新水平射线就应立即退出循环，否则更多竖直射线会被非法阻挡，且该水平射线的答案会停留在最右边一个挡住它的地方。

似乎题目并没有明确指出没有重叠的情况出现，但不考虑这种情况也能过。如果非要考虑的话就要额外特判同一水平或竖直直线上相邻两点的距离能否更新答案，并且排序时需要建立第二关键字。

```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int x, y, id;
} N[55], E[55];
int totn, tote, ans[55];

bool cmpx(node a, node b) {return a.x < b.x;}
bool cmpy(node a, node b) {return a.y < b.y;}

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i ++) {
		char op; int x, y;
		scanf(" %c%d%d", &op, &x, &y);
		if (op == 'N') N[++ totn] = {x, y, i};
		else E[++ tote] = {x, y, i};
	}
	sort(N+1, N+totn+1, cmpx);
	sort(E+1, E+tote+1, cmpy);
	for (int i = 1; i <= tote; i ++)
		for (int j = 1; j <= totn; j ++) {
			if (N[j].x < E[i].x) continue;
			if (N[j].y > E[i].y) continue;
			int a = N[j].x-E[i].x, b = E[i].y-N[j].y;
			if (ans[N[j].id]) continue;
			if (a < b) ans[N[j].id] = b;
			if (a > b) {ans[E[i].id] = a; break;}
		}
	for (int i = 1; i <= n; i ++)
		!ans[i] ? printf("Infinity\n") : printf("%d\n", ans[i]);
}
```



---

## 作者：dabenBbx (赞：1)

## 枚举 $+$ 排序

我们发现牛的种类就分两种，一个向北，一个向东。一种牛停止只会因为另一种牛吃完了草挡住了去路。所以我们可以将两种牛分类，并从小到大排序。然后枚举一种牛，再看会不会影响另一种牛吃草。

这道题的关键就是：有的牛会无限吃下去。我们只需要在牛停止时记下答案，跳出。在输出每只牛的结果时，如果一个牛没答案，就直接输出无限即可。

## **Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,totn,tote,ans[55];
struct edge{
	int x,y,id;
}n[55],e[55];
bool cmp1(edge a,edge b){
	return a.x<b.x;
}
bool cmp2(edge a,edge b){
	return a.y<b.y;
}
int main(){
	cin>>N;
	for(int i=1;i<=N;i++){
		char op;   
		int xx,yy;
		cin>>op>>xx>>yy;
		if(op=='N'){
			n[++totn].x=xx;
			n[totn].y=yy;
			n[totn].id=i;
		}else{
			e[++tote].x=xx;
			e[tote].y=yy;
			e[tote].id=i;
		}
	}
	sort(n+1,n+1+totn,cmp1);
	sort(e+1,e+1+tote,cmp2);
	for(int i=1;i<=tote;i++){
		for(int j=1;j<=totn;j++){
			if(e[i].x>n[j].x)
			   continue;
			if(e[i].y<n[j].y)
			   continue;
			if(ans[n[j].id])
	     	   continue;
			if(n[j].x-e[i].x<e[i].y-n[j].y)
			   ans[n[j].id]=e[i].y-n[j].y;
			else
			if(n[j].x-e[i].x>e[i].y-n[j].y){
				ans[e[i].id]=n[j].x-e[i].x;
				break;
			}
		}
	}
	for(int i=1;i<=N;i++){
		if(!ans[i])
		   cout<<"Infinity"<<"\n";
		else
		   cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：AlanFong (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9957)  
## 思路   
这一道题，是排序加上枚举。  
首先，我们将向北和向东的奶牛分别做统计，然后，将其分别按纵坐标与横坐标分别排序。  
接着，我们分别从两个部分中各枚举奶牛，判断其是否会被阻拦。   
这个过程讲求顺序，已经被拦截的奶牛不再前进，不会再阻拦更多奶牛。  
## 代码  
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int vis[2505];
struct node{
    int x,y,num;
};//num表示相应的初始编号
node nor[2505],eas[2505];//分成两个部分
int cntn,cnte;
bool cmp1(node a,node b)//按纵坐标排序
{
    if(a.x<b.x)
    {
        return 1;
    }
    if(a.x==b.x&&a.y>b.y)
    {
        return 1;
    }
    return 0;
}
bool cmp2(node a,node b)//按横坐标排序
{
    if(a.y<b.y)
    {
        return 1;
    }
    if(a.y==b.y&&a.x>b.x)
    {
        return 1;
    }
    return 0;
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        char ch;
        int x,y;
        cin>>ch>>x>>y;
        if(ch=='N')//分成两个部分
        {
            cntn++;
            nor[cntn].num=i;
            nor[cntn].x=x;
            nor[cntn].y=y;
        }else if(ch=='E')
        {
            cnte++;
            eas[cnte].num=i;
            eas[cnte].x=x;
            eas[cnte].y=y;
        }
    }
    sort(nor+1,nor+cntn+1,cmp1);
    sort(eas+1,eas+cnte+1,cmp2);
    for(int i=1;i<=cntn;i++)
    {
        for(int j=1;j<=cnte;j++)
        {
            if(nor[i].y>eas[j].y)//轨迹不重叠
            {
                continue;
            }
            if(eas[j].x>nor[i].x)
            {
                continue;
            }
            if(vis[nor[i].num])//已经被拦截
            {
                continue;
            }
            if(vis[eas[j].num])
            {
                continue;
            }
            int pointx=nor[i].x,pointy=eas[i].y;
            int arrtn=(eas[j].y-nor[i].y),arrte=(nor[i].x-eas[j].x);
            if(arrtn>arrte)//两种拦截情况
            {
                vis[nor[i].num]=arrtn;
            }
            if(arrtn<arrte)
            {
                vis[eas[j].num]=arrte;
            }//相等时继续前进
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==0)//从未被阻拦
        {
            cout<<"Infinity"<<endl;
            continue;
        }
        cout<<vis[i]<<endl;
    }
    return 0;
}
```

---

## 作者：cly312 (赞：0)

由于 $x, y \leq 10^9$，我们无法模拟每个时间段。因此，我们需要尝试判断两头牛何时会相交。

一个重要的观察是，牛不能后退，所以两头牛发生碰撞的唯一方式是 $n[x] > e[x]$ 且 $n[y] < e[y]$。

可以按牛的起始坐标进行排序，然后模拟这些碰撞。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag_2;
int n;
struct s{//sheep
	int ans=INT_MAX;
	char dir;
	int x,y;
};
s ss[55];//sheeps
bool check(s,s);
void chuli(s&,s&);
bool check(s a,s b){//路径上是否有同一点
	if(a.dir==b.dir) return false;
	if(a.dir!='N') swap(a,b);
	if(a.x<=b.x) return false;
	if(b.y<=a.y) return false;
	return true;
}
void chuli(s &a,s &b){
	bool flag=false;
	if(a.dir!='N'){
		swap(a,b);
		flag=true;
	}
	int x=a.x;
	int y=b.y;
	int dis_a=abs(y-a.y);
	int dis_b=abs(x-b.x);
	if(a.ans<dis_a&&b.ans==dis_b) b.ans=INT_MAX,flag_2=true;//如果A判断为被B撞且B在撞A之前已经停下了
	if(b.ans<dis_b&&a.ans==dis_a) a.ans=INT_MAX,flag_2=true;
	if(dis_a<dis_b&&a.ans>=dis_a&&b.ans>dis_b)
		b.ans=dis_b,flag_2=true;
	if(dis_a>dis_b&&b.ans>=dis_b&&a.ans>dis_a)
		a.ans=dis_a,flag_2=true;
	if(flag) swap(a,b);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>ss[i].dir>>ss[i].x>>ss[i].y;
	while(true){
		flag_2=false;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(check(ss[i],ss[j]))
					chuli(ss[i],ss[j]);
			}
		}
		if(!flag_2) break;
	}
	for(int i=1;i<=n;i++)
		if(ss[i].ans!=INT_MAX) cout<<ss[i].ans<<'\n';
		else puts("Infinity");
	return 0;
}
```

---

## 作者：not_so_littlekayen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9957)
                                   
[**A better reading experience?**](https://www.luogu.com.cn/article/8z073ew9)

思路：我们将东和北的牛分别排序一遍，运用函数判断两头牛所在直线的焦点，比较距离，距离焦点最近的牛取最小值。


问题来了：为什么东和北分别要排序一遍？


![](https://cdn.luogu.com.cn/upload/image_hosting/1gyovfkf.png?x-oss-process=image/resize,m_lfit,h_240,w_400)

如图所示，我们设上面一只朝东的牛一号牛，下面一只朝东的叫二号牛，朝北的叫三号牛。在不排序的情况下，程序会优先判断一号牛被三号牛挡住，可实际上是，**三号牛被二号牛所挡住了**。也就是说：**一号牛没有被三号牛挡住！**

这还是简单的情况，用几道判断就可以解决，要是牛的数量增加，那就可谓是“剪不断，理还乱”的情况了。但是我们在排序后就可以将这个问题完美解决。

代码如下：
```cpp
//illustrated by littlekayen_qwq!
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
int n, u, v;
struct node{
	int grass = inf;
	int x, y, num;
    bool skip = 0;//牛是否在之前就停下来了
}north[101], east[101];
void crush(int a, int b)//a向东， b向北 
{
	if(east[a].x > north[b].x)return ;//两条牛互相错开
    if(east[a].y < north[b].y)return ;//同上（感兴趣的读者可以自己模拟一下）
	int acnt = north[b].x-east[a].x, bcnt = east[a].y-north[b].y;//求距离
	if(acnt == bcnt)return ;
	if(acnt > bcnt&&!north[b].skip)east[a].grass = min(east[a].grass, acnt), east[a].skip = 1;
	if(acnt < bcnt&&!east[a].skip)north[b].grass = min(north[b].grass, bcnt), north[b].skip = 1;
}
bool cmp_east(node l, node r){return l.y < r.y;}
bool cmp_north(node l, node r){return l.x < r.x;}
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		int a, b;char c;
		cin >> c >> a >> b;
		if(c == 'N')
        {
            north[++u].x = a;
		    north[u].y = b;
            north[u].num = i;
        }
		else
        {
            east[++v].x = a;
		    east[v].y = b;
            east[v].num = i;
        }
		
	}
    sort(north+1, north+u+1, cmp_north);
    sort(east+1, east+v+1, cmp_east);//排序
	for(int i = 1;i <= v;i++)
		for(int j = 1;j <= u;j++)crush(i, j);
    node cow[101];
    for(int i = 1;i <= v;i++)cow[east[i].num].grass = east[i].grass;
    for(int i = 1;i <= u;i++)cow[north[i].num].grass = north[i].grass;
	for(int i = 1;i <= n;i++)
	{
		if(cow[i].grass == inf)cout << "Infinity";
		else cout << cow[i].grass;
		puts("");
	}
	return 0;
} 
```

---

## 作者：zxh923 (赞：0)

# P9957 [USACO20DEC] Stuck in a Rut B 题解

[题目传送门](https://www.luogu.com.cn/problem/P9957)

### 思路

我们首先把两种类型的路径分类，然后分别按照横，纵坐标进行排序。

接下来我们用横着的路径去判断每一条竖着的路径。如果这个位置能挡到这条路径，直接跳出循环并记录（因为我们已经排序，所以这就是第一个能挡住这头牛的路径）。

最后记得在判断时跳过已经被挡住的牛带来的影响。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cntn,cnte,ans[55];
struct node{
	int x,y,id;
}nor[55],eas[55];
bool cmpx(node x,node y){return x.x<y.x;}
bool cmpy(node x,node y){return x.y<y.y;}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		int x,y;
		cin>>c>>x>>y;
		if(c=='E')eas[++cnte]={x,y,i};
		else nor[++cntn]={x,y,i};
	}
	sort(nor+1,nor+cntn+1,cmpx);
	sort(eas+1,eas+cnte+1,cmpy);
	for(int i=1;i<=cnte;i++){
		for(int j=1;j<=cntn;j++){
			if(nor[j].x<eas[i].x||nor[j].y>eas[i].y)continue;
			int x=nor[j].x-eas[i].x,y=eas[i].y-nor[j].y;
			if(ans[nor[j].id])continue;
			if(x<y)ans[nor[j].id]=y;
			if(x>y){
				ans[eas[i].id]=x;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(ans[i])cout<<ans[i]<<'\n';
		else cout<<"Infinity\n";
	}
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

首先，本人没想出正解，其实就是差了一点点。所以本文先讲解正解，再讲下本人神奇做法。

# 正解

首先，暴力枚举是行不通的，所以我们考虑，什么情况下会被挡住。因为每个坐标的 $x,y$ 都不相同，所以一定是一个向东的和一个向北的，其中一个挡住了另一个。

那么到底是谁挡住了谁？我们可以知道，谁先到了交叉点，谁把对方挡住。所以我们可以枚举向东的牛和向北的牛，到交叉点近的牛挡住了对方，然后被挡住的牛 $ans$ 取最小值即可。如果有牛最后 $ans$ 还是初始值，说明它不会被挡住，就是输出无穷。

但是这题也有细节，我已经排过一遍坑了，请注意！

1. 两头牛同时到达，也就是到交叉点距离相同，谁都不会被挡住。
2. 向东的牛要按照 $x$ 从小到大枚举，向北的牛要按照 $y$ 从小到大枚举。

第 $2$ 个我要说明一下。比如样例中，$3$ 号牛本来会被 $5$ 号牛挡住，但 $5$ 号牛先被挡住了，所以 $3$ 号牛可以吃无限。

因为本人不才，代码就不放了。

# 不明解

这是本人的做法，也欢迎大家来 hack。类似的，我先判断向北的牛会吃多少草，再判断向东的。但是有可能像样例中的 $3$ 号牛和 $5$ 号牛一样，所以我跑了不知道几次循环，然后一直跑到 $ans$ 没有变化。这种方法也过了，但是我认为这有可能会被卡成 TLE 或 WA，而我又不会证明这个算法的时间复杂度和正确性，求证明时间复杂度或 hack。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, a, b, xxx, yyy, ans[55], aa[55];
struct E{
	ll id, x, y;
}p[2][55];
char ddd;
il bool cmp1(E x, E y){return x.x < y.x;}
il bool cmp2(E x, E y){return x.y < y.y;}
bool check(){
	bool flag = 0;
	for (int i = 1; i <= n; i++) if (ans[i] != aa[i]) flag = 1;
	for (int i = 1; i <= n; i++) aa[i] = ans[i];
	return flag;
}
int main(){
	scanf ("%lld", &n);
	for (int i = 1; i <= n; i++){
		ans[i] = aa[i] = 1e17;
		scanf ("%s %lld %lld", &ddd, &xxx, &yyy);
		if (ddd == 'N') p[0][++a] = E{i, xxx, yyy};
		else p[1][++b] = E{i, xxx, yyy};
	}
	sort (p[0] + 1, p[0] + a + 1, cmp1);
	sort (p[1] + 1, p[1] + b + 1, cmp2);
	do{
		for (int i = 1; i <= a; i++){
			E u = p[0][i];
			ans[u.id] = 1e17;
			for (int j = 1; j <= b; j++){
				E v = p[1][j];
				if (v.y < u.y || v.x > u.x || v.x + aa[v.id] < u.x) continue;
				if (v.y - u.y > u.x - v.x){
					ans[u.id] = v.y - u.y;
					break;
				}
			}
		}
		for (int i = 1; i <= b; i++){
			E u = p[1][i];
			ans[u.id] = 1e17;
			for (int j = 1; j <= a; j++){
				E v = p[0][j];
				if (v.x < u.x || v.y > u.y || v.y + aa[v.id] < u.y) continue;
				if (v.x - u.x > u.y - v.y){
					ans[u.id] = v.x - u.x;
					break;
				}
			}
		}
	}while (check());
	
	for (int i = 1; i <= n; i++)
		if (ans[i] == 1e17) puts("Infinity");
		else printf ("%lld\n", ans[i]);
	return 0;
}

```

---

