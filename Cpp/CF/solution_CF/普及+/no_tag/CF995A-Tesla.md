# Tesla

## 题目描述

Allen dreams of one day owning a enormous fleet of electric cars, the car of the future! He knows that this will give him a big status boost. As Allen is planning out all of the different types of cars he will own and how he will arrange them, he realizes that he has a problem.

Allen's future parking lot can be represented as a rectangle with $ 4 $ rows and $ n $ ( $ n \le 50 $ ) columns of rectangular spaces, each of which can contain at most one car at any time. He imagines having $ k $ ( $ k \le 2n $ ) cars in the grid, and all the cars are initially in the second and third rows. Each of the cars also has a different designated parking space in the first or fourth row. Allen has to put the cars into corresponding parking places.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF995A/34279eda6e70545a7bbf8d625eb53e7d26a4b91d.png)Illustration to the first example.However, since Allen would never entrust his cars to anyone else, only one car can be moved at a time. He can drive a car from a space in any of the four cardinal directions to a neighboring empty space. Furthermore, Allen can only move one of his cars into a space on the first or fourth rows if it is the car's designated parking space.

Allen knows he will be a very busy man, and will only have time to move cars at most $ 20000 $ times before he realizes that moving cars is not worth his time. Help Allen determine if he should bother parking his cars or leave it to someone less important.

## 说明/提示

In the first sample test case, all cars are in front of their spots except car $ 5 $ , which is in front of the parking spot adjacent. The example shows the shortest possible sequence of moves, but any sequence of length at most $ 20000 $ will be accepted.

In the second sample test case, there is only one column, and the cars are in the wrong order, so no cars can move and the task is impossible.

## 样例 #1

### 输入

```
4 5
1 2 0 4
1 2 0 4
5 0 0 3
0 5 0 3
```

### 输出

```
6
1 1 1
2 1 2
4 1 4
3 4 4
5 3 2
5 4 2
```

## 样例 #2

### 输入

```
1 2
1
2
1
2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
1 2
1
1
2
2
```

### 输出

```
2
1 1 1
2 4 1
```

# 题解

## 作者：rui_er (赞：1)

考虑把刚好在车位前面的车停进去，然后剩下的车统一轮换，能停的时候就停进去，不断重复这个过程。

因为中间的车道是 $2\times n$ 的格子，最坏情况一辆车要转一圈才能找到车位，找到车位后还要一次操作停进去，总共 $k$ 辆车，最坏的操作次数为 $k\times(2\times n+1)\le 10100\lt 20000$，因此这种方法可行。

无解的话就判断没有车被轮换的时候是全都停到了车位里还是全都动不了即可。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const int N = 205; 

int n, m, a[5][N];
tuple<int, int> s[N], t[N];
vector<tuple<int, int, int> > ans;
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}
tuple<int, int> getNext(const tuple<int, int>& pos) {
	int x = get<0>(pos), y = get<1>(pos);
	if(x == 2) {
		if(y == n) return make_tuple(3, n);
		return make_tuple(2, y+1);
	}
	if(y == 1) return make_tuple(2, 1);
	return make_tuple(3, y-1);
}
bool isEmpty(const tuple<int, int>& pos) {
	return !a[get<0>(pos)][get<1>(pos)];
}
bool checkPark(const int& id) {
	if(abs(get<0>(s[id])-get<0>(t[id])) == 1 && get<1>(s[id]) == get<1>(t[id])) {
		ans.push_back(make_tuple(id, get<0>(t[id]), get<1>(t[id])));
		a[get<0>(s[id])][get<1>(s[id])] = a[get<0>(t[id])][get<1>(t[id])] = 0;
		return 1;
	}
	return 0;
}
bool rotateR() {
	bool ok = 0;
	rep(i, 2, 3) {
		rep(j, 1, n) {
			if(!a[i][j]) continue;
			tuple<int, int> nxt = getNext(make_tuple(i, j));
			if(checkPark(a[i][j])) ok = 1;
			else if(isEmpty(nxt)) {
				int id = a[i][j];
				ans.push_back(make_tuple(id, get<0>(nxt), get<1>(nxt)));
				a[i][j] = 0;
				a[get<0>(nxt)][get<1>(nxt)] = id;
				s[id] = nxt;
				ok = 1;
			}
		}
	}
	return ok;
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, 4) rep(j, 1, n) {
		scanf("%d", &a[i][j]);
		if(a[i][j]) {
			if(i == 1 || i == 4) t[a[i][j]] = make_tuple(i, j);
			else s[a[i][j]] = make_tuple(i, j);
		}
	}
	while(rotateR())
		;
	bool tag = 1;
	rep(i, 1, 4) {
		rep(j, 1, n) if(a[i][j]) {tag = 0; break;}
		if(!tag) break;
	}
	if(!tag) puts("-1");
	else {
		int sz = ans.size();
		printf("%d\n", sz);
		for(auto p : ans) printf("%d %d %d\n", get<0>(p), get<1>(p), get<2>(p));
	}
	return 0;
}
```

---

## 作者：Karry5307 (赞：1)

### 题意

给定一个 $4\times n$ 的地图，地图上有 $k$ 辆车，每辆车一开始都在中间两行，同时每辆车在旁边两行都有一个钦定的停车位。现在一个人每一次可以将一辆车往四个方向中的一个移动，但是如果将车移动到旁边两行必须满足目标位置是这个车钦定的停车位。构造一组方案在不超过 $20000$ 次操作以内将所有车停到钦定的停车位上。

$\texttt{Data Range:}1\leq n\leq 50,1\leq k\leq 2n$

### 题解

好题。~~虽然我一年前看这个题的时候发现根本不会做就让这题在计划里吃了一年灰~~

先将所有能停到停车位上的车停了。如果没有空位的话由于任何车都无法移动了那么必定无解，否则我们需要通过空位构造出解。

注意到每个格子上的车可以往四个方向上移动，相当于第二行的车可以往右边往左边或者是往第三行移动，第三行也能往右边往左边或者是往第二行移动。

这样就可以构造一个循环，每次将中间两行的所有车顺时针转一格，然后如果有能停的车就停，然后这么做 $2n$ 次。因为中间两列的每一辆车经过转 $2n$ 之后能到达中间两列的每一个格子，也就一定能够到达这辆车钦定的停车位前面的那个格子，然后停进去就好了。

操作次数的理论上界为 $2nk+k=10100$ 次远小于 $20000$ 次，可以通过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=251;
struct Item{
	ll c,x,y;
};
vector<Item>s;
ll n,m,cx,cy;
ll g[5][MAXN],prvx[5][MAXN],prvy[5][MAXN],nxtx[5][MAXN],nxty[5][MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void move()
{
	for(register int i=1;i<=n;i++)
	{
		g[1][i]==g[2][i]&&g[1][i]?s.push_back((Item){g[1][i],1,i}),g[2][i]=0:1;
		g[3][i]==g[4][i]&&g[3][i]?s.push_back((Item){g[4][i],4,i}),g[3][i]=0:1;
	}
}
inline void rotate()
{
	ll tx=cx,ty=cy,u,v;
	ll px=prvx[tx][ty],py=prvy[tx][ty];
	for(register int i=px,j=py;i!=tx||j!=ty;i=u,j=v)
	{
		if(g[i][j])
		{
			s.push_back((Item){g[i][j],nxtx[i][j],nxty[i][j]});
			swap(g[i][j],g[nxtx[i][j]][nxty[i][j]]);
		}
		u=prvx[i][j],v=prvy[i][j];
	}
	cx=nxtx[tx][ty],cy=nxty[tx][ty];
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=4;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			g[i][j]=read();
		}
	}
	for(register int i=1;i<=n;i++)
	{
		prvx[2][i]=2+(i==1),prvy[2][i]=i==1?1:i-1;
		nxtx[2][i]=2+(i==n),nxty[2][i]=i==n?n:i+1;
		prvx[3][i]=3-(i==n),prvy[3][i]=i==n?n:i+1;
		nxtx[3][i]=3-(i==1),nxty[3][i]=i==1?1:i-1;
	}
	move();
	for(register int i=1;i<=n;i++)
	{
		g[2][i]==0?cx=2,cy=i:1,g[3][i]==0?cx=3,cy=i:0;
	}
	if(!cx)
	{
		return puts("-1"),0;
	}
	for(register int i=1;i<=2*n;i++)
	{
		rotate(),move();
	}
	printf("%d\n",s.size());
	for(register Item i:s)
	{
		printf("%d %d %d\n",i.c,i.x,i.y);
	}
}
```

---

## 作者：DJRzjl (赞：0)

## [CF995A](https://www.luogu.com.cn/problem/CF995A)

- 考虑先将目标车位就在旁边的车，可以一步到达的车一步归位，如果这之后场上不存在空位，那么所有车都被卡住动不了了，此时一定无解。

其他情况下，考虑如下构造方案：

1. 以一定顺序让每部车移动一格，比如让它们沿中间两行顺(/逆)时针转，$(2,a)\to(2,a+1),(2,n)\to(3,n),(3,b)\to(3,b-1),(3,1)\to(2,1)$​。其中 $a$​ 满足属于 $[1,n)$​，$b$​ 属于 $(1,n]$​，若准备移动的车前面被另一车卡住则不移动它。但要注意，一定是某辆车移动后，再移动它原来位置后方（相对于移动方向）的车，这是为了不在这一步中将这辆车移动多次，这个循环的交界处的车移动情况也要特殊考虑。
2. 将移动一步可以到达目标车位的车归位。

重复上面两步，直到所有车归位。这样构造下，每辆车的移动轨迹都是沿中间两行 $2n$ 个格子顺(/逆)时针转了一圈，并且每辆车每次循环移动一次，而每移动到一个新位置都会执行 $2$​ 操作一次，所以每辆车一定都在转完一圈之前归位了。那么，这个构造方案理论最坏移动次数就为 $2n*k$，加上归位的 $k$ 步，总步数不会超过 $10100$，远小于 $20000$ 的限制，可以通过本题。​

---

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,cnt,tot,mp[10][100];
pair<int,pair<int,int> >ans[200000];
void insert(int id,int x,int y){ans[++tot]=make_pair(id,make_pair(x,y));}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<5;++i) for(int j=1;j<=n;j++) scanf("%d",&mp[i][j]);
	int old=-1,op;
	while(cnt<k){
		if(old==tot||tot>=12000) return puts("-1")&0;
		old=tot;
		for(int j=1;j<=n;j++){
			if(mp[2][j]&&mp[1][j]==mp[2][j]) mp[2][j]=0,insert(mp[1][j],1,j),++cnt;
			if(mp[3][j]&&mp[4][j]==mp[3][j]) mp[3][j]=0,insert(mp[4][j],4,j),++cnt;
		}
		op=0;
		if(mp[2][1]&&!mp[3][1]) swap(mp[2][1],mp[3][1]),insert(mp[3][1],3,1),op=1;
		for(int j=2;j<=n;j++) if(mp[2][j]&&!mp[2][j-1]) swap(mp[2][j],mp[2][j-1]),insert(mp[2][j-1],2,j-1);
		if((n!=1||!op)&&mp[3][n]&&!mp[2][n]) swap(mp[3][n],mp[2][n]),insert(mp[2][n],2,n);
		for(int j=n-1;j>0+op;j--) if(mp[3][j]&&!mp[3][j+1]) swap(mp[3][j],mp[3][j+1]),insert(mp[3][j+1],3,j+1);
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%d %d %d\n",ans[i].first,ans[i].second.first,ans[i].second.second);
	return 0;
}
```


---

