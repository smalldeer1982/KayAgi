# Game

## 题目描述

Two players play the following game. Initially, the players have a knife and a rectangular sheet of paper, divided into equal square grid cells of unit size. The players make moves in turn, the player who can't make a move loses. In one move, a player can take the knife and cut the paper along any segment of the grid line (not necessarily from border to border). The part of the paper, that touches the knife at least once, is considered cut. There is one limit not to turn the game into an infinite cycle: each move has to cut the paper, that is the knife has to touch the part of the paper that is not cut before.

Obviously, the game ends when the entire sheet is cut into $ 1×1 $ blocks. During the game, the pieces of the sheet are not allowed to move. It is also prohibited to cut along the border. The coordinates of the ends of each cut must be integers.

You are given an $ n×m $ piece of paper, somebody has already made $ k $ cuts there. Your task is to determine who will win if the players start to play on this sheet. You can consider that both players play optimally well. If the first player wins, you also need to find the winning first move.

## 样例 #1

### 输入

```
2 1 0
```

### 输出

```
FIRST
1 0 1 1
```

## 样例 #2

### 输入

```
2 2 4
0 1 2 1
0 1 2 1
1 2 1 0
1 1 1 2
```

### 输出

```
SECOND
```

# 题解

## 作者：liuzhongrui (赞：1)

## 前言

有位大佬的代码已经很详细了，我仅分享一下我的思路，代码就不贴了。

## 思路

首先注意，水平和垂直切割是独立的。考虑单个水平线。它包含 $m$ 个单位段。在任何游戏状态下，玩家总是可以按照自己的意愿减少未切割单位的数量。想象一下，她从边缘开始增加一个段，每次增加 $1$ 个单位的长度。每次总未切割长度减少的要么是 $0$，要么是 $1$，最终它显然会达到 $0$。

垂直线也是一样的。因此，如果没有初始切割，游戏就是一个带有 $n-1$ 堆 $m$ 个石头和 $m-1$ 堆 $n$ 个石头的 NIM 游戏。可以用简单的公式解决。

初始的 $k$ 个切割只是一个技术难题。对于任何包含至少一个切割的垂直或水平线，它的堆大小应该减去此行上所有段的总长度。

接下来讨论如何在 NIM 游戏中进行第一步。假设 $res$ 是状态（格伦迪函数）的结果，$a_i$ 是第 $i$ 堆的大小。然后没有第 $i$ 堆的游戏的结果是 $res \operatorname{xor} a_i$。我们想要用某个 $x$ 替换 $a_i$，使得 $res \operatorname{xor} a_i \operatorname{xor} x = 0$。显然，唯一可能的是 $x = res \operatorname{xor} a_i$。最终的解决方案是：找到一堆满足 $(res \operatorname{xor} a_i) < a_i$，并将其减少到 $res \operatorname{xor} a_i$。


---

## 作者：FP·荷兰猪 (赞：0)

> 题意：给一个n*m的网格，两人轮流在上面沿着网络纸横切或者竖切，直接不能切者为输。初始状态是已经切了K刀了。。。

恶心。。。

博弈部分是正常的NIM游戏规则，但是对于图形的处理好麻烦的说

n*m的矩形网格，已经切了K条线 
再两人轮流操作 合法操作是在网格上画横线或竖线
长度自随意，但是必须产生新的切痕
网格的边界不能切
最后不能操作者败
不难发现行和列是相互独立的 
每一行和每一列单独看成成一堆石子，
完整部分的长度就是石子个数，
每切一刀就相当于取走若干石子

代码：
```cpp
#include <bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
/*
	n*m的矩形网格，已经切了K条线 
	再两人轮流操作 合法操作是在网格上画横线或竖线
	长度自随意，但是必须产生新的切痕
	网格的边界不能切
	最后不能操作者败
	不难发现行和列是相互独立的 
	每一行和每一列单独看成成一堆石子，
	完整部分的长度就是石子个数，
	每切一刀就相当于取走若干石子
	
*/ 
struct Line 
{
	int l,r;
	Line(int l = 0,int r = 0):l(l),r(r){}
};
bool cmp(Line a,Line b)
{
	if (a.l == b.l) return a.r < b.r;
	return a.l < b.l;
}
const int N = 100004;
vector<Line>fs[N],sc[N];//fs保存原始输入的线,sc保存处理过没有重叠部分的线
int take[N];//take[i]表示编号为i的行或者列已经被拿走的石头数
int n,m,k;
int id;//划过线的行或列的编号
map<int,int>row,cow;//row[i]表示纵坐标为i的行的坐标 
void init()
{
	mem(fs,0);mem(sc,0);mem(take,0);
	row.clear();cow.clear();
	id = 0;
	//输入
	for (int i = 0,x1,x2,y1,y2;i < k;++i)
	{
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if (x1 == x2)//竖线
		{
			if (y1 > y2) swap(y1,y2);
			if (cow.find(x1) == cow.end())//这一列没有出现过
			{
				cow[x1] = id;//给个编号 
				fs[id].push_back(Line(y1,y2));//给这个编号的列加入一条线段
				++id ;//更新编号 
			} 
			else //这一列已经被划过 也就是已经有编号了
			{
				fs[cow[x1]].push_back(Line(y1,y2));//加入线段 
			} 
		} 
		else //横线 -- 同理
		{
			if (x1 > x2) swap(x1,x2);
			if (row.find(y1) == row.end())
			{
				row[y1] = id;
				fs[id].push_back(Line(x1,x2));
				++id;
			}
			else 
			{
				fs[row[y1]].push_back(Line(x1,x2));
			}
		} 
	} 
	//处理重叠的线 保存于sc中
	for (int i = 0;i < id;++i)
	{
		sort(fs[i].begin(),fs[i].end(),cmp);//这一行或列的所有线排好 
		int l = fs[i][0].l,r = fs[i][0].r;//这一行或列的第一条线 
		for (int j = 1;j < fs[i].size();++j)
		{
			if (fs[i][j].l > r)//这是一条和前面一条没有覆盖的线
			{
				sc[i].push_back(Line(l,r));//前面一条存进去
				take[i] +=  r-l;//已经拿走的石头数 
				l = fs[i][j].l;//更新
				r = fs[i][j].r; 
			} 
			else //覆盖
			{
				r = max(r,fs[i][j].r);//延长前面那条线到后面那条线达到的长度 
			} 
		}
		take[i]+=r-l;
		sc[i].push_back(Line(l,r));//最后一根线不要忘 
	} 
}
void solve()//博弈的过程
{
	int s = 0;
	int r = m-row.size()-1,c = n-cow.size()-1;
	//r表示没有被切过的完整的行
	if (r&1) s^=n;//奇数个异或和为n，偶数个 异或和为0
	if (c&1) s^=m;
	//博弈 -- 当前局面的判断
	for (map<int,int>::iterator it = row.begin();it!=row.end();++it)//处理行 
	{
		int rest = n-take[it->second];//take[it->second]是该编号行拿走的石头数
		//rest是该行剩下的石头数
		s^=rest; 
	} 
	for (map<int,int>::iterator it = cow.begin();it!=cow.end();++it)//同理处理列 
	{
		int rest = m - take[it->second];
		s^=rest;
	}
	if (s==0)//败态 
	{
		puts("SECOND");
		return;
	}
	puts("FIRST");
	//胜态需要输出第一步的走法
	//首先考虑完整的行或列
	for (int i = 1;i < n;++i)
	{
		if (cow.find(i) == cow.end())
		{
	 		if (m>=(m^s))
	 		{
	 			int t = m - (m^s);
	 			printf("%d %d %d %d\n",i,0,i,t);
	 			return;
			}
			else break;//完整的都是一样 只需尝试一根即可 
		}
	}
	for (int i = 1;i < m;++i)
	{
	 	if (row.find(i) == row.end())
	 	{
	 		if (n>=(n^s))
	 		{
	 			int t = n - (n^s);
	 			printf("%d %d %d %d\n",0,i,t,i);
	 			return;
			}
			else break;
		}
	} 
	for (map<int,int>::iterator it = row.begin();it != row.end();++it)
	{
		int id = it->second;
		int rest = n - take[id];
		if (rest >= (rest^s))
		{
			int t = rest - (rest^s);
			int sum = 0,p = 0;
			sc[id].push_back(Line(n,n));
			for (int i = 0;i < sc[id].size();++i)
			{
				if (sum + sc[id][i].l- p >= t)
				{
					printf("%d %d %d %d\n",0,it->first,p+t-sum,it->first);
					return;
				}
				sum += sc[id][i].l- p;
				p = sc[id][i].r;
			}
		}
	}
	for (map<int,int>::iterator it = cow.begin();it != cow.end();++it)
	{
		int id = it->second,rest = m - take[id];
		if (rest >= (rest^s))
		{
			int t = rest - (rest^s);
			int sum = 0,p = 0;
			sc[id].push_back(Line(m,m));
			for (int i = 0;i < sc[id].size();++i)
			{
				if (sum+sc[id][i].l - p >= t)
				{
					printf("%d %d %d %d\n",it->first,0,it->first,p+t-sum);
					return;
				}
				sum += sc[id][i].l-p;
				p = sc[id][i].r;
			}
		}
	}
} 
int main()
{
	while (cin>>n>>m>>k)
	{
		init();//建图 
		solve();//博弈 
	}
	return 0;
}

```

---

