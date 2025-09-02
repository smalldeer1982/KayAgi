# Bloxorz II

## 题目描述

由于大灾难的发生，科学院已经连续有很多年没有新生了(这个世界中的科学院其实也 有大学的职能)。于是这一年的新生测试就有里程碑一样的意义。作为科学院的顶级信息专 家，这一任务自然落到了你的头上。思来想去，你决定出这样的一个题，那就是 Bloxorz 游戏。

所谓 Bloxorz 游戏，如下图所示，就是在一个平台上有一个作为目标的 1×1 的洞，以 及一个大小为 2×1×1 的长方体。长方体可以沿着边在平台上滚动，但是不能与平台失去接触面。

![](https://cdn.luogu.com.cn/upload/image_hosting/z5kdhsry.png)

下面这张图反映了上图中的长方体向右滚动之后的局面。
![](https://cdn.luogu.com.cn/upload/image_hosting/6kgp8841.png)

而下面这张图就反映了向前方滚动之后的局面。

![](https://cdn.luogu.com.cn/upload/image_hosting/4rgnopmu.png)

任务就是让长方体进入目标洞。当然，这时长方体应该是竖立的。

滚动一次叫做一步。你的题目就是对于一个给定的局面，计算至少需要多少步才能把长 方体滚到目标洞里面去。自然，对于新生来说这个题是一个很难的题。

  被你虐了的新生感到很不服气。于是他们想了一个更难的题来让你做:
  
有一个无限大的平台以及一个建立在上面的坐标系。现在目标洞在(0, 0)处，长方体的 位置和状态(竖立、与 x 轴平行还是与 y 轴平行)给定，计算至少需要多少步才能使长方体 进洞。

  作为顶级信息专家......这当然难不倒你了。

## 说明/提示

对于 20% 的数据，$ \mid x \mid , \mid y \mid \le 100$。
对于 100% 的数据，$\mid x\mid , \mid y\mid \le 10^9$，输入数据不超过 100 组。

## 样例 #1

### 输入

```
U 0 0
H 0 0 
V 1 0```

### 输出

```
0
4
1```

# 题解

## 作者：_Warfarin_ (赞：4)

### 思路分析
上来我们一眼丁真为搜索，但再仔细一看数据范围 $|x|,|y| \leq 10^{9}$。  
显然，这需要我们来找找规律，既然求的是最小步数，我们就要思考，如何走效果最好，不难发现只有横着横向滚动和竖着竖向滚动时，两步就能走三格，这是最快的。  
因此我们可以发现，图中某些坐标 $ (x, y) $，如果满足 $ x \equiv 0 \pmod 3 $ 且 $  y \equiv 0 \pmod 3 $ 那么，它到达点 $(0,0)$ 的步数就为 $ x \div  3 \times  2 + y  \div  3 \times  2 $。 
可以发现，对于所有横纵坐标模 $ 3 $ 为 $ 0 $，且是立着的状态到终点的最小步数，我们能直接计算得出。  
假设这些状态叫做合适点,那么我们只要让起点状态用最小步数走到合适点上，那么从起点到终点的距离就可以相加得出。所以，我们只用考虑起点周围的最近的合适点，这只需要我们将起点映射到一个 $ 4 \times 4 $ 的格子中进行 bfs
即可。再求出该合适点到原点的步数并相加。
#### 注意事项
建议在映射时，矩阵开大一些，避免数组越界。
### AC 代码
```
#include <bits/stdc++.h>

#define ll long long
#define io cin.tie(0),cout.tie(0),ios::sync_with_stdio(false)
#define ri register int
#define lb long double

using namespace std;
const int N = 15;
typedef pair<int, int> qwq;
struct node
{
	int x, y, direction;
};
char op[2];
// 初始状态
int _x, _y;
//起点横纵坐标
int d[N][N][3];
//横坐标
//纵坐标
//方向
int next_x[3][4] = {{-2, 1, 0, 0}, {-1, 1, 0, 0}, {-1, 2, 0, 0}};
//下步横坐标变化
int next_y[3][4] = {{0, 0, -2, 1}, {0, 0, -1, 2}, {0, 0, -1, 1}};
//下步纵坐标变化
int next_direction[3][4] = {{2, 2, 1, 1}, {1, 1, 0, 0}, {0, 0, 2, 2}};
//下步方向变化
inline int bfs(int x, int y, int direction)
{
	memset(d, -1, sizeof d);
	d[x][y][direction] = 0;
	queue<node> q;
	q.push({x, y, direction});
	int ans = 1e10;
	while (q.size())
	{
		auto t = q.front();
		q.pop();
		int x = t.x, y = t.y, z = t.direction;
		if (x % 3 == 0 && y % 3 == 0 && z == 0)
		{
			int nx = _x + x - 3, ny = _y + y - 3;
			int xd = nx / 3 * 2, yd = ny / 3 * 2;
			//还原回去
			if (xd < 0 || yd < 0)
				continue;
			//负数，说明非法，直接跳过
			ans = min(ans, d[x][y][z] + xd + yd);
			//更新合法答案
		}
		for (ri i = 0; i < 4; i++)
		{
			int a = x + next_x[z][i];
			int b = y + next_y[z][i];
			int _direction = next_direction[z][i];
			if (a < 0 || a >= N || b < 0 || b >= N)
				continue;
			if (d[a][b][_direction] == -1)
			{
				d[a][b][_direction] = d[x][y][z] + 1;
				q.push({a, b, _direction});
			}
		}
	}
	return ans;
}
int main()
{
	io;
	while (cin >> op >> _x >> _y && op[0] != EOF)
	{
		int z;
		if (op[0] == 'U')
			z = 0;
		else if (op[0] == 'H')
			z = 1;
		else
			z = 2;
		int sx = _x % 3 + 3;
		int sy = _y % 3 + 3;
		cout << bfs(sx, sy, z) << endl;
	}
	return 0;
}
```

---

## 作者：bianshiyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10493)

建议可以先把[这题](https://www.luogu.com.cn/problem/P10485)做掉再来考虑这题。

# 分析
其实看到这题第一反应是直接爆搜，但是发现整个网格非常大，所以肯定有些性质需要挖掘。方块滚动时，竖着滚肯定比横着滚快（因为每次能多走一格），所以在距离终点较远的时候，选择一直竖着滚一定最优，由于竖着滚一次之后就“躺”下来了，所以还要滚一次让它“站”起来，这样子贪心的走两步可以滚三格。

所以一个显然的想法就是这样子一直操作直到离终点很近的地方，然后从这个位置开始爆搜就可以过，然后就开始思考怎么写代码，发现很不好写。首先是我们滚得时候不能滚过了（不能跑到其他象限去），这样可以保证每次滚 是最优的最优，否则如果滚过了的话还需要一定步数回来这样子最优性不能保证（反正我是没什么好的办法证明它是对的）。因为两个方向都要这样子操作，不妨假设先沿着 $x$ 轴滚动，再沿着 $y$ 轴滚动。我们要保证沿着 $x$ 轴滚完后要处于状态 U 或者 H，不然沿 $y$ 轴滚动就只能一次一步了。这个东西感觉说起来很简单，但是实现起来有些问题，比如考虑下面这一组数据：
```
V 0 1000000000
```
这是一个我们不能再沿着 $x$ 轴滚的数据（不然就会滚过了），但是此时这个方块沿 $x$ 轴放置我们就没有办法按照之前所述操作沿着 $y$ 轴滚动。考虑接下来怎么办，因为纵坐标很大，所以直接搜过去还是会超时，那么就还需要贪心地滚几步，下一步有向上，向左或者向右三种选择（之所以不考虑向下是因为越走越远一定不优）。向左和向右操作之后就可以直接按照之前说的方法沿着 $y$ 轴滚动然后爆搜，但是向上操作后我们仍然需要继续判断往哪边走，虽然这样子可以递推过来（即涉及到的子问题相等），但是 $y$ 很大没办法线性跑，所以又需要贪心分类或者来优化这个东西，总之非常麻烦。

我们希望寻找到可以通过所有数据的一般的解法，因为像上述做法一样分这么多类很不好写，而且容易写错。让我们来回顾一下上述做法为什么不太可写，原因是会出现一些不好解决的特例，~~废话~~，但是时间和空间都是正确的，所以我们可以改良上述方法。我们注意到上述做法采用了先滚后搜的策略，那么我们能不能调换一下顺序，先通过搜索找到附近的一个能直接贪心地滚到终点的状态，然后直接计算这个点到终点要多少步呢？你就会惊奇的发现这个是对的而且很好写。

首先对于任意一点 $(x,y)$，若满足 $x\bmod 3=0$ 且 $y\bmod3=0$ 且方块可以竖直立在这个点时，那么从这个点就可以直接按上述方法贪心地滚到终点，且答案很好算为 $2\lfloor \frac{x}{3}\rfloor+2\lfloor \frac{y}{3}\rfloor$，我们称这样的点为“好点”，好点每隔两步就会出现所以密度很大，也就是说任何一个初始状态周围都有很多这样子的好点，且距离一个初始状态很远的好点一定不优。不过这个距离远究竟是多远才算远呢？这个其实很不好说明，我们假设初始状态到某个好点 $(x,y)$ 且状态为站立的最小步数为 $dis_{x,y}$，那么最终答案为 $2\lfloor \frac{x}{3}\rfloor+2\lfloor \frac{y}{3}\rfloor+dis_{x,y}$，我们会发现答案由两部分构成：$2\lfloor \frac{x}{3}\rfloor+2\lfloor \frac{y}{3}\rfloor$ 和 $dis_{x,y}$，所以离起点近的好点可能离终点远，离起点远的好点可能离终点近，且求解 $dis_{x,y}$ 不仅仅要求到达好点，而且状态要合法，这样子可能导致距离好点很近，但是调整到合适的状态又需要很大的代价；也可能可以很快的调整状态，但是实际距离又很远。这就导致最终的答案很难说清在多远范围内一定找得到最优解，有些题解说附近的一层就是最优的，但是总感觉不好证，所以蒟蒻写了搜到最近两层的好点的代码，也就是以初始状态为中心周围 $15\times 15$ 的格子，~~实际上如果真的不放心，可以直接搜最近 $50$ 层，反正不会超时。~~

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=15;
int x,y,dis[N][N][3];
int dx[3][4]={{0,1,0,-2},{0,2,0,-1},{0,1,0,-1}};
int dy[3][4]={{1,0,-2,0},{1,0,-1,0},{2,0,-1,0}};
int dd[3][4]={{2,1,2,1},{1,0,1,0},{0,2,0,2}};
//滚动的横纵坐标以及方向数组
char s[3];

struct node{
	int x,y,di;
};

ll bfs(int x0,int y0,int di)
{
	int minx=x0-7,maxx=x0+7,miny=y0-7,maxy=y0+7;//最终的区域就是横坐标在[minx,maxx]，纵坐标在[miny,maxy]的部分。
    //这里之所以不直接对起始坐标取模再计算的原因是不好求出访问到的好点的原先坐标，不过这个也可以做，具体可以看楼上的题解
	ll res=1e18;//存最终的答案
	queue<node> q;
	memset(dis,-1,sizeof(dis));
	dis[x0-minx][y0-miny][di]=0;q.push((node){x0,y0,di});
	while(!q.empty())
	{
		node u=q.front();q.pop();
		if(u.x%3==0&&u.y%3==0&&u.di==0) res=min(res,(ll)(abs(u.x)/3*2+abs(u.y)/3*2+dis[u.x-minx][u.y-miny][u.di]));
        //这里要记得加上绝对值abs函数。
        //单独记录答案而不是入队时直接返回的原因是虽然dis满足单调性，但是abs(u.x)/3*2+abs(u.y)/3*2不满足所以所有状态都要求，然后取最小值
		for(int i=0;i<4;i++)
		{
			int xx=u.x+dx[u.di][i],yy=u.y+dy[u.di][i],di=dd[u.di][i];
			if(xx<minx||xx>maxx||yy<miny||yy>maxy) continue;
			if(dis[xx-minx][yy-miny][di]!=-1) continue;
			dis[xx-minx][yy-miny][di]=dis[u.x-minx][u.y-miny][u.di]+1;//每次扩展的代价都是1，所以某一个状态第一次入队时就是最优的
			q.push((node){xx,yy,di});
		}
	}
	return res;
}

int main()
{
	while(scanf("%s%d%d",s,&x,&y)!=EOF)
	{
		int di;//初始方向
		if(s[0]=='U') di=0;
		else if(s[0]=='V') di=1;
		else di=2;
		printf("%lld\n",bfs(x,y,di));
	}
	return 0;
}
```

---

