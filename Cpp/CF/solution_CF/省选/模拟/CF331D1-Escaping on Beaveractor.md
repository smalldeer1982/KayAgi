# Escaping on Beaveractor

## 题目描述

别再忍受你讨厌的事情了！聪明的海狸决定逃离海狸科学学院（BSA）的校园。BSA 是一个位于平面上的 $ b×b $ 正方形区域，每个点 $ (x, y) $ 满足 $ 0 \le x, y \le b $ 都属于校园范围。为了让逃跑过程快捷且有趣，海狸发明了一辆名为“海狸车”的高效舒适交通工具。

校园内遵循严格的交通规则：共有 $ n $ 条箭头线段，这些箭头平行于坐标轴。箭头互不相交也不接触。当海狸车到达某条箭头时，会转向箭头指示的方向继续行驶，直到到达下一条箭头或驶出校园。海狸车每单位时间移动一个单位距离，不会遇到任何障碍。

科学家们计划将这辆全新的海狸车运送到“学术拖拉机”研究所，并让聪明的海狸去攻读研究生，磨练技巧。他们设计了 $ q $ 个计划，包含海狸车的起始位置 $ (x_i, y_i) $，初始行驶方向 $ w_i $，以及从起始位置出发后经过的时间 $ t_i $。

你的任务是对每个计划判断指定时间后，聪明海狸的位置。

## 样例 #1

### 输入

```
3 3
0 0 0 1
0 2 2 2
3 3 2 3
12
0 0 L 0
0 0 L 1
0 0 L 2
0 0 L 3
0 0 L 4
0 0 L 5
0 0 L 6
2 0 U 2
2 0 U 3
3 0 U 5
1 3 D 2
1 3 R 2
```

### 输出

```
0 0
0 1
0 2
1 2
2 2
3 2
3 2
2 2
3 2
1 3
2 2
1 3
```

# 题解

## 作者：skyskyCCC (赞：1)

## 前言。
本题解是 $D1$ 的题解：  
这篇题解是在 $D1$ 的基础上进行编写的，所以该代码仅仅针对该题，对于另外两个加强版是无法通过的，这里注重从 $0$ 开始的由简入难的思考过程。

这个基础题的思路就是模拟，因为这个 $b$ 实在是太小了。
## 分析。
### 题意简述：
给定一个 $b$ 阶方正地图，地图上存在 $n$ 条路标，其中保证任意的路径与坐标轴平行且两两互不相交，每当小海狸碰到箭头将立即转向箭头所指方向并行进，随后 $n$ 行是路标的起始坐标 $\left(x_1,y_1\right)$ 和终点坐标 $\left(x_2,y_2\right)$。随后给出 $q$ 次询问，每次询问给出海狸的初始坐标 $\left(x_i,y_i\right)$ 和初始的走向共四种情况，其中 ```U```、```D```、```L``` 和 ```R``` 分别表示向上移动，向下移动，向左运动和向右运动，还有距离开始经过的时间。时间的限制条件为 $t_i\leq 10^{15}$ 个单位时间。输出 $q$ 行。每行应包含两个整数，海狸在每个询问中当时间为 $t_i$ 时所处的坐标。如果在 $t_i$ 时间内成功离开地图，则打印他最后访问的地图内的坐标。 
### 正式的讲解：
因为有 $t_i$ 的限制条件，所以我们从中入手，显然这个数据太大了，如果对于每个询问都直接模拟会直接超时，所以我们考虑找一个简便的方法来减少每次询问的次数。首先我们需要根据这些路标把整个图建出来，然后开始模拟。有一个很显然的思路是找循环节，如果海狸进了循环，那么无论 $t_i$ 多大，都会在一个特定的范围内循环，所以直接找到循环节后找到 $t_i$ 所对应的那个坐标就行。那么此时这个循环的情况查询时间就成了 $O\left(1\right)$。这个情况在每次询问中直接预处理然后直接对循环节取余即可。

然后这样可以证明，很容易出现循环节，所以可行。剩下的直接模拟即可，时间复杂度就大大降低了。然后最后处理一下直接跑出跑出地图，就直接结束模拟即可，因为海狸已经跑出地图并留下最后的访问过的坐标了。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
int n,b,x1,x2,y_1,y2,q1,x,y;
long long t;
char way;
int disx,disy;
long long timee;
int G[1005][1005],vis[1005][1005],sum[1005][1005];
struct node{
	int x,y;
}a[1005*1005];
int dx[7]={0,1,0,-1,0};
int dy[7]={0,0,1,0,-1};
map <char, int> ma;
void add(int x1,int y_1,int x2,int y2){//建图。 
	int dis=0;
	if (x1==x2){
		(y_1<y2)?dis=2:dis=4;
		//处理上下移动的情况。 
	}
	else{
		(x1<x2)?dis=1:dis=3;
		//处理左右移动的情况。 
	}
	G[x2][y2]=dis;
	while (x1!=x2||y_1!=y2){
		G[x1][y_1]=dis;
		x1+=dx[dis];
		y_1+=dy[dis];
	}
}
int main(){
	ma['R']=1;
	ma['U']=2;
	ma['L']=3;
	ma['D']=4;
	cin>>n>>b;
	for (int i=1;i<=n;i++){
		cin>>x1>>y_1>>x2>>y2;
		//cout<<"yep!\n";
		add(x1,y_1,x2,y2);
	}
	cin>>q1;
	for (int i=1;i<=q1;i++){
		timee=0;
		cin>>x>>y>>way>>t;
		disx=dx[ma[way]];
		disy=dy[ma[way]];//看看距离。 
		while(x>=0&&x<=b&&y>=0&&y<=b&&t>0){
			if(G[x][y]){//如果存在路标。 
				disx=dx[G[x][y]];
				disy=dy[G[x][y]];
			}
			if(G[x][y]&&vis[x][y]==i){//如果存在循环节。 
				/*t%=(timee-(long long)sum[x][y]);
				x=a[(long long)sum[x][y]+t].x;
				y=a[(long long)sum[x][y]+t].y;
				break;*/
				long long summ=sum[x][y];
				long long xhj=timee-summ;
				t%=xhj;
				x=a[summ+t].x;
				y=a[summ+t].y;
				break;
			}
			sum[x][y]=timee;
			a[timee].x=x;
			a[timee++].y=y;
			vis[x][y]=i;
			t--;
			x+=disx;
			y+=disy;//更新新的坐标.
		}
		if(x<0){
		    x=0;
		}
		if(x>b){
		    x=b;
		}
		if(y<0){
		    y=0;
		}
		if(y>b){
		    y=b;
		}//判断边界情况，是否越界，越界就记录海狸出去的那一个点。 
		cout<<x<<" "<<y<<"\n";
	}
	return 0;
}
/*
4 2
0 0 1 0
2 0 2 1
2 2 1 2
0 2 0 1
15
1 1 R 7
0 0 U 3
1 1 R 888888888888887
0 0 U 404040404040403
2 1 D 1000000000000000
2 0 R 324354768576473
2 0 L 325436475453245
2 0 U 764536452343654
2 0 D 943654765876545
1 1 U 1000000000000000
1 1 D 989898789898789
1 1 L 123456787654344
0 1 L 0
0 1 L 1
0 1 L 999999999999993
*/
```
## 后记。
一个很好想的思路，但是细节蛮多的。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Ghosty_Neutrino (赞：0)

## 分析
$b\times b$ 的平面上有 $n$ 条互不相交且平行于坐标轴的有向线段，运动到线段上之后运动方向会改变成沿着线段的方向。

有 $q$ 组询问，每组给出起始坐标，出发方向和运动距离，求最后停在哪个位置。如果中途会离开平面范围内就输出从哪个位置离开的。
## 分析
把询问离线，考虑计算从每条线段的终点以及每组询问的起点出发，下一次拐弯是在哪里。

我们可以将 $4$ 个方向分开做，对于一个方向，我们把所有线段及询问按照这个方向排序（如方向为向右，则按照 $x$ 坐标从大到小排序），用扫描线进行处理：扫到一条线段时，将它覆盖的区间插入线段树，计算答案时直接查询即可。

把这个拐弯关系建成图，由于一个点只会有 $1$ 条出边，所以图会是个内向基环树森林，可以直接倍增预处理。

在处理某线段中间的拐弯时，我们可以在拐弯处插入一个新节点。

对于离开平面的情况，在离开平面处建一个点，并把它的出边指向自己。

还要注意一点：虽然保证线段不相交，但并不保证询问的起点不在线段上，因此这里要小心地特判。
## 代码

```cpp
#include'bits/stdc++.h'
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
li read(){
	li x = 0,c = gc;
	while(!isdigit(c)) c = gc;
	while(isdigit(c)){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = gc;
	}
	return x;
}
void print(li q){
	if(q >= 10) print(q / 10);
	pc(q % 10 + '0');
}
int n,s,m;
struct jt{
	int xa,ya,xb,yb,p,id;
	int mxx,mxy,mnx,mny;
	bool fg;
}a[500010],d[500010];
int asx[100010],asy[100010];
struct qy{
	int x,y,p;
	li t;
}b[100010];
int tot;
inline bool cp0(jt q,jt w){return q.mny == w.mny ? q.fg < w.fg : q.mny < w.mny;}
inline bool cp1(jt q,jt w){return q.mxx == w.mxx ? q.fg < w.fg : q.mxx > w.mxx;}
inline bool cp2(jt q,jt w){return q.mxy == w.mxy ? q.fg < w.fg : q.mxy > w.mxy;}
inline bool cp3(jt q,jt w){return q.mnx == w.mnx ? q.fg < w.fg : q.mnx < w.mnx;}
int t[500010];
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define md int mid = l + r >> 1
void init(int q,int l,int r){
	t[q] = -1;
	if(l == r) return;
	md;
	init(ln);init(rn);
}
inline void ps(int q){
	if(t[q] == -1) return;
	t[ls] = t[rs] = t[q];t[q] = -1;
}
void xg(int q,int l,int r,int al,int ar,int x){
	if(l >= al && r <= ar){
		t[q] = x;
		return;
	}
	ps(q);
	md;
	if(mid >= al) xg(ln,al,ar,x);
	if(mid < ar) xg(rn,al,ar,x);
}
int cx(int q,int l,int r,int x){
	if(l == r) return t[q];
	ps(q);
	md;
	if(mid >= x) return cx(ln,x);
	return cx(rn,x);
}
int s1[62][500010];
li s2[62][500010];
inline void ins(int u,int v,int w){s1[0][u] = v;s2[0][u] = w;}
inline void buildst(){
	register int i,j;
	for(i = 1;i <= 60;++i){
		for(j = 1;j <= tot;++j){
			s1[i][j] = s1[i - 1][s1[i - 1][j]];
			s2[i][j] = s2[i - 1][j] + s2[i - 1][s1[i - 1][j]];
			if(s2[i][j] > 1e18) s2[i][j] = 2e18;
		}
	} 
}
void file(){
	freopen("331d3.in","r",stdin);
	freopen("331d3.out","w",stdout);
}
int main(){
	int i,j,u;
	char c;
	n = read();s = read();
	for(i = 1;i <= n;++i){
		a[i].xa = read();a[i].ya = read();a[i].xb = read();a[i].yb = read();
		if(a[i].xa == a[i].xb && a[i].ya == a[i].yb){
			--n;--i;continue;
		}
		if(a[i].xa == a[i].xb){
			if(a[i].ya < a[i].yb) a[i].p = 2; 
			else a[i].p = 0;
		}
		else{
			if(a[i].xa < a[i].xb) a[i].p = 1;
			else a[i].p = 3; 
		}
		a[i].id = i;
	}
	m = read();tot = n + m;
	for(i = 1;i <= m;++i){
		b[i].x = read();b[i].y = read();c = gc;while(c < 'A' || c > 'Z') c = gc;b[i].t = read();
		b[i].p = c == 'D' ? 0 : c == 'R' ? 1 : c == 'U'? 2 : 3;
		a[i + n].xa = a[i + n].xb = b[i].x;a[i + n].ya = a[i + n].yb = b[i].y;a[i + n].id = i + n;a[i + n].p = b[i].p;a[i + n].fg = 1;
	}
	for(i = 1;i <= n + m;++i){
		a[i].mxx = max(a[i].xa,a[i].xb);a[i].mnx = min(a[i].xa,a[i].xb);
		a[i].mxy = max(a[i].ya,a[i].yb);a[i].mny = min(a[i].ya,a[i].yb);
	}
	#define x1 xa
	#define y1 ya
	#define x2 xb
	#define y2 yb
	sort(a + 1,a + n + m + 1,cp0);
	init(1,0,s);
	for(i = 1;i <= n + m;++i){
		if(!a[i].fg){
			if(a[i].p != 0) xg(1,0,s,a[i].mnx,a[i].mxx,i);
		}
		if(a[i].p == 0){
			u = cx(1,0,s,a[i].mxx);
			a[++tot].x1 = a[i].mxx;a[tot].id = tot;
			if(u == -1){
				a[tot].y1 = 0;
				ins(a[i].id,tot,a[i].mny);
				ins(tot,tot,0);
			}
			else{
				if(a[u].p == 2){
					a[tot].y1 = min(a[i].mny,a[u].mxy);
					ins(tot,a[u].id,a[u].mxy - a[tot].y1);
				}
				else{
					a[tot].y1 = a[u].mxy;
					ins(tot,a[u].id,abs(a[u].x2 - a[tot].x1));
				}
				ins(a[i].id,tot,a[i].mny - a[tot].y1);
			}
		}
	}
	sort(a + 1,a + n + m + 1,cp1);
	init(1,0,s);
	for(i = 1;i <= n + m;++i){
		if(!a[i].fg){
			if(a[i].p != 1) xg(1,0,s,a[i].mny,a[i].mxy,i);
		}
		if(a[i].p == 1){
			u = cx(1,0,s,a[i].mxy);
			a[++tot].y1 = a[i].mxy;a[tot].id = tot;
			if(u == -1){
				a[tot].x1 = s;
				ins(a[i].id,tot,s - a[i].mxx);
				ins(tot,tot,0);
			}
			else{
				if(a[u].p == 3){
					a[tot].x1 = max(a[i].mxx,a[u].mnx);
					ins(tot,a[u].id,a[tot].x1 - a[u].mnx);
				}
				else{
					a[tot].x1 = a[u].mxx;
					ins(tot,a[u].id,abs(a[u].y2 - a[tot].y1));
				}
				ins(a[i].id,tot,a[tot].x1 - a[i].mxx);
			}
		}
	}
	sort(a + 1,a + n + m + 1,cp2);
	init(1,0,s);
	for(i = 1;i <= n + m;++i){
		if(!a[i].fg){
			if(a[i].p != 2) xg(1,0,s,a[i].mnx,a[i].mxx,i);
		}
		if(a[i].p == 2){
			u = cx(1,0,s,a[i].mxx);
			a[++tot].x1 = a[i].mxx;a[tot].id = tot;
			if(u == -1){
				a[tot].y1 = s;
				ins(a[i].id,tot,s - a[i].mxy);
				ins(tot,tot,0);
			}
			else{
				if(a[u].p == 0){
					a[tot].y1 = max(a[i].mxy,a[u].mny);
					ins(tot,a[u].id,a[tot].y1 - a[u].mny);
				}
				else{
					a[tot].y1 = a[u].mxy;
					ins(tot,a[u].id,abs(a[u].x2 - a[tot].x1));
				}
				ins(a[i].id,tot,a[tot].y1 - a[i].mxy);
			}
		}
	}
	sort(a + 1,a + n + m + 1,cp3);
	init(1,0,s);
	for(i = 1;i <= n + m;++i){
		if(!a[i].fg){
			if(a[i].p != 3) xg(1,0,s,a[i].mny,a[i].mxy,i);
		}
		if(a[i].p == 3){
			u = cx(1,0,s,a[i].mxy);
			a[++tot].y1 = a[i].mxy;a[tot].id = tot;
			if(u == -1){
				a[tot].x1 = 0;
				ins(a[i].id,tot,a[i].mnx);
				ins(tot,tot,0);
			}
			else{
				if(a[u].p == 1){
					a[tot].x1 = min(a[i].mnx,a[u].mxx);
					ins(tot,a[u].id,a[u].mxx - a[tot].x1);
				}
				else{
					a[tot].x1 = a[u].mxx;
					ins(tot,a[u].id,abs(a[u].y2 - a[tot].y1));
				}
				ins(a[i].id,tot,a[i].mnx - a[tot].x1);
			}
		}
	}	
	for(i = n + m + 1;i <= tot;++i) a[i].x2 = a[i].x1,a[i].y2 = a[i].y1;
	for(i = 1;i <= tot;++i) d[a[i].id] = a[i];
	buildst();
	li nw,lft;
	for(i = 1;i <= tot;++i) if(d[i].fg){
		nw = i;lft = b[d[i].id - n].t;
		for(j = 60;j >= 0;--j) if(lft >= s2[j][nw]){
			lft -= s2[j][nw];
			nw = s1[j][nw];
		}
		asx[d[i].id - n] = d[nw].x2;asy[d[i].id - n] = d[nw].y2;
		if(s1[0][nw] != nw){
			if(d[s1[0][nw]].x2 > d[nw].x2) asx[d[i].id - n] += lft;
			else if(d[s1[0][nw]].x2 < d[nw].x2) asx[d[i].id - n] -= lft;
			else if(d[s1[0][nw]].y2 > d[nw].y2) asy[d[i].id - n] += lft;
			else if(d[s1[0][nw]].y2 < d[nw].y2) asy[d[i].id - n] -= lft; 
		}
	}
	for(i = 1;i <= m;++i) print(asx[i]),pc(' '),print(asy[i]),pc('\n');
	return 0;
}
```

---

