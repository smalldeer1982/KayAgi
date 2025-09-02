# Traveling Salesman Problem

## 题目描述

你正位于一个无限的笛卡尔坐标系的点 $ (x , y) $上，你可以进行四种操作：

- 向左移动至 $ (x - 1, y) $ 
- 向右移动至 $ (x + 1, y) $ 
- 向上移动至 $ (x, y + 1) $ 
- 向下移动至 $ (x, y - 1) $ 

有 $ n $ 个宝箱在这个平面上。 第 $ i $ 个 宝箱的坐标为 $ (x_i,y_i) $ . 保证每个宝箱都在 $ x $ 轴 或 $ y $ 轴上。即 $ x_i=0 $ 或 $ y_i=0 $。

你现在点 $ (0,0) $ 上，想将所有宝箱全部收入囊中，并回到原点。
你想知道你需要的最小移动次数是多少。
本题使用多组测试数据。

## 样例 #1

### 输入

```
3
4
0 -2
1 0
-1 0
0 2
3
0 2
-3 0
0 -1
1
0 0```

### 输出

```
12
12
0```

# 题解

## 作者：Failure_Terminator (赞：3)

## Solution

这道题有一定的思考难度，但实现简单。

尝试先作图。

这是数据的第一个样例。

![](https://espresso.codeforces.com/c123b61473cd40ad008be769cb8c6c4b40bed43b.png)

#### 输入:
```4
0 -2
1 0
-1 0
0 2
```

#### 输出：
```
12
```

从图中不难发现，对于有这些坐标构成的图，对答案造成影响的有以下几个点：

- 最上面的一个点（$x$ 轴最大）；

- 最下面的一个点（$x$ 轴最小）；

- 最右面的一个点（$y$ 轴最大）；

- 最左面的一个点（$y$ 轴最小）；

而对于其他的点，路线总能将其连进去。

由于要从原点出发并重新回到原点，因此答案为：


$$2 \times (\max\{ x \}+\max\{ y \}-\min\{ x \}-\min\{ y \})$$


可以在输入时同步进行处理，时间复杂度为 $O(n)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}
void solve(){
	int n=read();
	int minx,miny,maxx,maxy;
	minx=maxx=miny=maxy=0;
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		minx=min(minx,x);
		miny=min(miny,y);
		maxx=max(maxx,x);
		maxy=max(maxy,y);
	}
	printf("%d\n",2*(maxx+maxy-minx-miny));
}
int main()
{
	int t=read();
	while(t--) solve();
	return 0;
}
```


---

## 作者：xiaomuyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1713A)

## 题目分析
总觉得我的思路比官方的样例解释的思路更优（？

考虑只在坐标轴上运动。

因为在同一个方向如果有两个箱子的话，是不可能先拿一个然后回到中间再走过去再拿一个的（那样更不优），所以说只要算一下去 $y$ 坐标正方向、负方向、$x$ 坐标正方向、负方向分别最远到哪儿，然后算一下距离，加起来就行了。
## 代码实现
```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=1e2+1;
const int inf=114514;
int t,n,x[maxn],y[maxn],ymin=inf,ymax=-inf,xmin=inf,xmax=-inf,res;
int main(){
	scanf("%d",&t);
	while(t--){
		ymin=inf,ymax=-inf,xmin=inf,xmax=-inf;
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d%d",&x[i],&y[i]);
			ymin=min(y[i],ymin);
			ymax=max(y[i],ymax);
			xmin=min(x[i],xmin);
			xmax=max(x[i],xmax);//计算各个方向的最远距离
		}
		res=abs(ymin)+ymax+abs(xmin)+xmax;
		if(ymin>0) res-=abs(ymin);//特判：如果没有箱子在这条坐标轴的这个方向上
		if(ymax<0) res-=ymax;
		if(xmin>0) res-=abs(xmin);
		if(xmax<0) res-=xmax;
		printf("%d\n",res*2);
	}
	return 0;
}
```

---

## 作者：C_Cong (赞：1)

[博客传送门](https://blog.ccongcirno.cn/2022/08/07/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3-CF1713A-%E3%80%90Traveling%20Salesman%20Problem%E3%80%91/#more)

### 题目大意

一个人站在原点， $x$ 轴与 $y$ 轴上分布有几个箱子，人每次只能走一个单位（上/下/左/右），求经过所有箱子并回到原点的最少步数

### 思路

箱子都在坐标轴上，而我们又知道两点之间线段最短

所以显然最短路就是到达各个轴上离原点最远的箱子后再折返

刚好在轴上来回走两次

至于题目给的样例图片走法

只要将路径平移至坐标轴就是我上面说的，总步数是一样的

因此只需要找出两条坐标轴正负半轴上离原点最远的箱子坐标就好了

答案就是找出来的四个点离原点的距离总和 $\times2$

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int t,n,mp[110][2],maxw[2],maxh[2];

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        maxw[0]=0;
        maxw[1]=0;
        maxh[0]=0;
        maxh[1]=0;
        for(int a=1;a<=n;++a)
        {
            
            scanf("%d%d",&mp[a][0],&mp[a][1]);
            if(mp[a][0]==0)
            {
                if(mp[a][1]>=0)
                {
                    maxh[1]=max(maxh[1],mp[a][1]);//y轴正方向
                }
                else
                {
                    maxh[0]=max(abs(mp[a][1]),maxh[0]);//y轴负方向
                }
            }
            else
            {
                if(mp[a][1]==0)
                {
                    if(mp[a][0]>=0)
                    {
                        maxw[1]=max(maxw[1],mp[a][0]);//x轴正方向
                    }
                    else
                    {
                        maxw[0]=max(abs(mp[a][0]),maxw[0]);//x轴负方向
                    }
                }
            }
            
        }
        printf("%d\n",(maxw[0]+maxw[1]+maxh[0]+maxh[1])*2);
    }
    return 0;
}
```

----------

有用的话顶上去才能让更多人看到awa

---

## 作者：JZH123 (赞：0)

# 题目大意：
你在一个无穷大的平面直角坐标系上，你可以往左、右、上、下移动一步。

你需要收集一些宝箱并返回原点，求路程 $min$ 值。

# 思路：

第一个样例——

![](https://cdn.luogu.com.cn/upload/image_hosting/ekcvlx81.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

使用平移大法，把一些线段平移过来，就会组成一个长方形， $C$ 长方形就是答案。($C$表示周长）

求 $C$ 长方形，我们就需要知道纵坐标的 $max$ 值和 $min$ 值，两数之差就是长；我们还需要知道宽，就是横坐标的 $max$ 值和 $min$ 值相减。

那么 $S$ 长方形就是长加宽的和乘二。

### 注意事项：
有多组数据，纵坐标、横坐标的 $min$ ，$max$ 值和 $ans$  要初始化为零。

代码：
```
#include <bits/stdc++.h>
using namespace std;
int t, n;
int x, y;
int minx, maxx, miny, maxy;
int ans;
int main()
{
	scanf ("%d", &t);
	while (t --)
    {
		scanf ("%d", &n);
		while (n --)
        {
			scanf ("%d%d", &x, &y);
			minx = min(x, minx);
			maxx = max(x, maxx);
			miny = min(y, miny);
			maxy = max(y, maxy);
		}
		ans = ((maxx - minx) + (maxy - miny)) * 2;
		printf ("%d\n", ans);
		maxx = maxy = minx = miny = ans = 0;
	}
	return 0;
}
```

---

## 作者：HarunluoON (赞：0)

## 题意简述

从平面直角坐标系的原点出发，需要经过所有在坐标轴上的给定的点（“宝箱”）然后回到原点，不限顺序。每次移动可以向上、下、左、右四个方向移动一个单位长度。求出最少需要移动几个单位长度。

## 分析

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713A/2b602eaf16bce39f930bfcfcfb2b3ed7bd31fbab.png)

上图是样例的第 $1$ 测试组给出来的解释图片。我们可以把这个方案描述为`(0,0)->(1,0)->(1,1)->(1,2)->(0,2)->(-1,2)->(-1,1)->(-1,0)->(-1,-1)->(-1,-2)->(0,-2)->(0,-1)->(0,0)`，共 $12$ 次移动。

由于矩形的对边相等，我们能很容易地发现上面这种方案与下面这种只在坐标轴上移动的方案同为最优方案：`(0,0)->(1,0)->(0,0)->(0,1)->(0,2)->(0,1)->(0,0)->(-1,0)->(0,0)->(0,-1)->(0,-2)->(0,-1)->(0,0)`。

这种方案的特点是：沿着每一条半轴移动到距离原点最远的一个“宝箱”后返回原点。当然，如果一条半轴上没有“宝箱”，就不需要在这条半轴上移动。

我们可以使用四个变量 $maxx$、$minx$、$maxy$、$miny$ 分别记录 $x$ 轴正半轴、$x$ 轴负半轴、$y$ 轴正半轴、$y$ 轴负半轴上距离原点最远的“宝箱”与原点的距离。**因为这些变量每个都负责一条半轴，所以它们的初始值都应该为 $0$。**

因为到达一条半轴上所有的“宝箱”后需要返回原点，所以答案为 $2\times (maxx+maxy+\lvert minx\rvert+\lvert miny\rvert)$。由于 $minx$、$miny$ 为非正数，答案可以化简为：$2\times (maxx+maxy-minx-miny)$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
void work()//每个测试组（test case）
{
	int n,x,y,maxx=0,minx=0,maxy=0,miny=0;//分别记录 x 轴正半轴、x 轴负半轴、y 轴正半轴、y 轴负半轴上距离原点最远的“宝箱”与原点的距离
					       //若初始值不为 0，则有可能有“宝箱”被重复到达
	scanf("%d",&n);
	for(int i=1;i<=n;i++)//读入每一个“宝箱”的坐标
	{
		scanf("%d%d",&x,&y);
		if(x<minx) minx=x;
		if(x>maxx) maxx=x;
		if(y<miny) miny=y;
		if(y>maxy) maxy=y;
	}
	printf("%d\n",2*(maxx+maxy-minx-miny));//求出答案，输出
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	work();
	return 0;
}
```

---

## 作者：DANIEL_x_ (赞：0)

## 思路
和小奥求周长的题一样，将里面的边平移，最后这条路径形成的是一条环。

这个环的长和宽就是这几个要经过的点的横坐标的最大差值，和纵坐标的最大差值，
所以我们通过四个数 $maxx,maxy,minx,miny$ 来记录，最大最小值，最后输出的是 $2*(maxx-minx+maxy-miny)$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T, n, x, y, maxx, maxy, minx, miny;
signed main() {
	cin >> T;
	while(T--) {
		maxx = maxy = minx = miny = 0ll;
		cin>>n;
		for(int i = 0; i < n; i++) {
			cin>>x>>y;
			maxx = max(maxx, x),maxy = max(maxy, y),minx = min(minx, x),miny = min(miny, y); 
		}
		cout << (maxx-minx+maxy-miny) * 2 << endl;
	}
} 
```


---

## 作者：lsj2009 (赞：0)

## Problem

给定 $n$ 个在笛卡尔坐标系上的点 $(x_i,y_i)$，保证 $\forall i,[x_i=0\vee y_i=0]=\texttt{true}$，求从原点开始遍历所有点的曼哈顿距离最短路。

$n\le100,t\le100,-100\le x_i,y_i\le100$。

link-><https://codeforces.com/contest/1713/problem/A>。

## Solution

因为有 $\forall i,[x_i=0\vee y_i=0]=\texttt{true}$，即所有点都位于 $x$ 或 $y$ 轴上，则我们考虑从原点出发，从左到右遍历所有 $y_i=0,x_i\ge0$ 的点，然后折回来由上至下遍历所有 $x_i=0,y_i\ge0$ 的点，再从右到左遍历所有 $y_i=0,x_i<0$，再从下到上遍历所有 $x_i=0,y_i<0$ 的点（详见样例解释），根据小学数学可以轻松得到答案为 $2\times(\max\{\max\limits_{i=1}^n\{x_i\},0\}-\min\{\min\limits_{i=1}^n\{x_i\},0\}+\max\{\max\limits_{i=1}^n\{y_i\},0\}-\min\{\min\limits_{i=1}^n\{y_i\},0\})$。

## Code


``` cpp
#include<bits/stdc++.h>
#define F fisrt
#define S second
#define INF 0x7fffffff
#define inf 0x3f3f3f3f
#define inf 0x3f3f3f3f3f3f3f3f
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e2+5;
int x[N],y[N],n,T;
signed main() {
	scanf("%d",&T);
	while(T--) {
		int n;
		scanf("%d",&n);
		int maxx=0,maxy=0,minx=0,miny=0;
		_for(i,1,n) {
			scanf("%d%d",&x[i],&y[i]);
			maxx=max(maxx,x[i]); minx=min(minx,x[i]);
			maxy=max(maxy,y[i]); miny=min(miny,y[i]);
		}
		printf("%d\n",(maxx-minx)*2+2*(maxy-miny));
	}
	return 0;
}
```

---

## 作者：Anonymous__user (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1713A)。

**题目大意**：你在一个无限大的平面直角坐标系上，你可以向左、向右、向上、向下移动一步。你需要收集一些宝箱并返回原点，求最短路程。

**思路**：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713A/2b602eaf16bce39f930bfcfcfb2b3ed7bd31fbab.png)

  这是第一个样例的图片。我们发现把一些线段平移过来，会组成一个长方形，长方形的周长就是答案。为了求长方形的周长，我们需要知道纵坐标的最大值和最小值，把它们相减就是长；我们还需要知道宽，就是横坐标的最大值和最小值相减。那么长方形的面积就是长加宽乘二。

**注意**：有多组数据，纵坐标、横坐标的最大最小值和 $ans$ 要清零。

**代码**：
```c
#include<bits/stdc++.h>
using namespace std;
long long t,n,x,y,minx=0,maxx=0,miny=0,maxy=0,ans;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>x>>y;
			minx=min(x,minx);
			maxx=max(x,maxx);
			miny=min(y,miny);
			maxy=max(y,maxy);
		}
		ans=(maxx-minx+maxy-miny)*2;
		maxx=0;maxy=0;minx=0;miny=0;
		cout<<ans<<endl;
		ans=0;
	}
	return 0;
}
```

---

## 作者：Simclover (赞：0)

这是一道简单的思维题。

我们先考虑如何到达离原点上下左右四个方向最远的点，那么我们就需要从原点分别走到这四个点之后再返回原点，有其他很多种走法，可以证明，不会有更短距离的走法的路径小于从原点分别走到这四个点之后再返回原点的走法的路径。

然后考虑如何走完所有的点，因为所有的点都是在坐标轴上的，所以所有的点就被包含在从原点分别走到这四个点之后再返回原点的走法的路径上了，于是我们只需要算出从原点分别走到这四个点之后再返回原点的走法的路径长度即可。

定义答案为 $ans$，定义上下左右四个方向离原点最远的点离原点的距离分别为 $x1$，$x2$，$y1$，$y2$。那么有以下的公式：

$$ ans= (x1+x2+y1+y2) \times 2 $$

最后输出 $ans$ 即可，代码很好写就不放了。

---

## 作者：luo_shen (赞：0)

**题意**  
一个人在平面直角坐标系上行走，有一些必须到达的点在坐标轴上，求行走距离的最小值  
**解析**  
首先弄明白一个问题：这个人行走的时候需要脱离坐标轴吗？好像没这个必要吧，因为可以在往某个方向移动后，再沿着同样的路往回1走。所以可以处理出从原点需要向每条坐标轴的每个方向的最长长度，最后累加起来并乘 $2$ 即为结果。计 $mnx$ 为 $x$ 坐标最小值，代表往 $x$ 轴负半轴所需移动的最大距离；计 $mxx$ 为 $x$ 坐标最大值，代表往 $x$ 轴正半轴所需移动的最大距离；
计 $mny$ 为 $y$ 坐标最小值，代表往 $y$ 轴负半轴所需移动的最大距离；计 $mxy$ 为 $y$ 坐标最大值，代表往 $y$ 轴正半轴所需移动的最大距离。所以最终结果为：
$$ans=2\times(mxx-mnx+mxy-mny)$$  
**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,mxx,mxy,mnx,mny,n;
int main(){
    cin>>t;
    while(t--){
        mxx=0,mxy=0,mnx=0,mny=0;//mnx,mny初始化为1，不要赋值为极大值
        int x,y;
        cin>>n;
        while(n--){
            cin>>x>>y;
            mxx=max(mxx,x);//求mxx
            mxy=max(mxy,y);//求mxy
            mnx=min(mnx,x);//求mnx
            mny=min(mny,y);//求mny
        }
        cout<<(mxx-mnx+mxy-mny)*2<<endl;
    }
    return 0;
}
```

---

## 作者：Catcats (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1713A)

### 题目大意

有 $n$ 个点散布在一个坐标系的 $x$ 轴和 $y$ 轴之上，求一个初始位置在原点的点，至少经过多少距离才能经过所有的点并回到原点。

### 题目解法

既然所有点都在 $x,y$ 轴上，那么点自然也不用离开 $x,y$ 轴。

于是我们可以统计以下 $4$ 个数据：

- 在 $x$ 轴上的在原点最左边的点（记为 $y_1$）；
- 在 $x$ 轴上的在原点最右边的点（记为 $y_2$）；
- 在 $y$ 轴上的在原点最上面的点（记为 $x_1$）；
- 在 $x$ 轴上的在原点最下面的点（记为 $x_2$）；

那么（其中一条）最短路线是：

$O\to y_1\to y_2\to O\to x_1\to x_2\to O$（$O$ 为原点）。

这条路线的长度是 $2(|x_1-x_2|+|y_1-y_2|)$。

### AC 代码

注意多测。
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		int x_1=0,x_2=0,y_1=0,y_2=0;
		int x,y;
		while(n--){//求出最远的 x_1,x_2,y_1,y_2
			cin>>x>>y;
			if(!x){//等价于 x==0
				if(y>0){
					y_1=max(y_1,y);
				}
				else{
					y_2=min(y_2,y);
				}
			}
			else{
				if(x>0){
					x_1=max(x_1,x);
				}
				else{
					x_2=min(x_2,x);
				}
			}
		}
		cout<<(abs(x_1-x_2)+abs(y_1-y_2))*2<<endl;//长度
	}
}
```

---

## 作者：Jeremiahy (赞：0)

## 题意

有一些在 $x$ 轴或 $y$ 轴上的点，每次你可以向上下左右移动一格，你开始在 $(0,0)$，结束也必须在 $(0,0)$，最少移动多少次可以经过所有点？

# 分析

经过简单的模拟，我们发现，每次在每个轴上的每个半轴的最远距离就是最远的点，加上来回就是 $2$ 倍。也就是说，我们只需要统计出四个半轴（ $x$ 正半轴，$x$ 负半轴，$y$ 正半轴，$y$ 负半轴）上最远的点的坐标相加乘 $2$ 即可。

有一个细节问题：有可能某几个半轴上没有点，这时就不需要涉足那个半轴了，只需要把四个半轴初始化为 $0$ 即可。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, N, S, W, E, x, y;
signed main () {
	cin >> t;
	while (t--) {
		N = S = W = E = 0;//初始化为 0 
		cin >> n;
		while (n--) {
			cin >> x >> y;
			if (x == 0 && y < 0) //y 负半轴
				S = min(S, y);
			else if (x == 0) // y 正半轴
				N = max(N, y);
			else if (x < 0) // x 负半轴
				W = min(W, x);
			else	 // x 正半轴
				E = max(E, x);
		}
		cout << abs(S) * 2 + abs(N) * 2 + abs(W) * 2 + abs(E) * 2 << '\n'; // 计算
	}
	return 0;
}
```


---

## 作者：Toothless03 (赞：0)

~~水一篇题解~~

由于每个箱子要么在 $x$ 轴上，要么在 $y$ 轴上，而又得从原点开始，回到原点上，所以最优策略是：从原点开始，先走到 $x$ 正半轴的最远端，再回到原点，再到 $x$ 负半轴的最远端，再回到原点，再到 $y$ 的正半周...

所以答案是每个半轴到原点的最长距离之和的 $2$ 倍

下面贴出核心代码

```cpp
int x_min = 0/* $x$ 负半轴*/, x_max = 0/* $x$ 正半轴*/;
int y_min = 0/* $y$ 负半轴*/, y_max = 0/* $y$ 正半轴*/;
for (int i = 0; i < n; i++) {
	int x, y; cin >> x >> y;
	if (x == 0)//如果在 $y$ 轴上
		y_min = min(y, y_min), y_max = max(y, y_max);
	if (y == 0)//如果在 $x$ 轴上
		x_min = min(x, x_min), x_max = max(x, x_max);
}
cout << 2 * (x_max - x_min + y_max - y_min) << endl;
```

---

## 作者：cachejtt (赞：0)

## 题意
给你一些点，都在平面直角坐标系的 $x$ 轴或 $y$ 轴上。你有一个盒子从原点出发，每次只能向上下左右四个方向一格，问你最少需要多少走多少步，才能吃掉所有的点，并回到原点。

## 思路
考虑先向左走到最远，再回到原点，以此吃掉 $x$ 轴负半轴的点；再向右走到最远，回到原点，吃掉 $x$ 轴正半轴的点。$y$ 轴同理。

因此只需记录各半轴最远点即可。将其绝对值相加，并将答案乘二。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t=1,n,x,y,xx1,xx2,xy1,xy2,sum;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    sum=0;
    xx1=xy1=0;
    xx2=xy2=0;
    rep(i,1,n){
      cin>>x>>y;
      if(x==0){
        if(y>=0)xy1=max(xy1,y);
        else xy2=min(xy2,y);
      }
      else if(y==0){
        if(x>=0)xx1=max(xx1,x);
        else xx2=min(xx2,x);
      }
    }
    xx2=-xx2;
    xy2=-xy2;
    cout<<(xx1+xx2+xy1+xy2)*2<<endl;
  }
  return 0;
}
```


---

## 作者：Ender_hz (赞：0)

# 题意

给定一个正整数 $n(n\le100)$，在平面直角坐标系中有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，满足：

+ $x_i=0$ 或 $y_i=0$
+ $0\le|x_i|,|y_i|\le100$

你需要以 $(0, 0)$ 为起点和终点，通过上下左右移动的方式访问每一个点，求最短路径长。



# 分析

注意到所有的点都在坐标轴上，我们可以分别访问 $x$ 轴正半轴，$x$ 轴负半轴，$y$ 轴正半轴，$y$ 轴负半轴上的点，记录每个半轴上最远的点的坐标即可。

注意每次访问需要回到 $(0, 0)$，计两倍路程。

# 代码

```cpp
#include<iostream>
#define sfor(i, h, t) for(int i = (h); i <= (t); ++i)
using namespace std;
const int MAXN = 0x186A8;
int T = 1, N;
int num[MAXN];
int ans, minx, maxx, miny, maxy;
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N;
        ans = minx = maxx = miny = maxy = 0;
        int x, y;
        sfor(i, 1, N) {
            cin >> x >> y;
            maxx = max(x, maxx);
            minx = min(x, minx);
            maxy = max(y, maxy);
            miny = min(y, miny);
        }
        ans = maxx - minx + maxy - miny;
        cout << (ans << 1) << endl;
    }
    return 0;
}
```



---

