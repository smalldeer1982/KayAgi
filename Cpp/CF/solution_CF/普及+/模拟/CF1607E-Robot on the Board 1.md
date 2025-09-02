# Robot on the Board 1

## 题目描述

The robot is located on a checkered rectangular board of size $ n \times m $ ( $ n $ rows, $ m $ columns). The rows in the board are numbered from $ 1 $ to $ n $ from top to bottom, and the columns — from $ 1 $ to $ m $ from left to right.

The robot is able to move from the current cell to one of the four cells adjacent by side.

The sequence of commands $ s $ executed by the robot is given. Each command is denoted by one of the symbols 'L', 'R', 'D' or 'U', and triggers the movement to left, right, down or up, respectively.

The robot can start its movement in any cell. The robot executes the commands starting from the first one, strictly in the order in which they are listed in $ s $ . If the robot moves beyond the edge of the board, it falls and breaks. A command that causes the robot to break is not considered successfully executed.

The robot's task is to execute as many commands as possible without falling off the board. For example, on board $ 3 \times 3 $ , if the robot starts a sequence of actions $ s= $ "RRDLUU" ("right", "right", "down", "left", "up", "up") from the central cell, the robot will perform one command, then the next command will force him to cross the edge. If the robot starts moving from the cell $ (2, 1) $ (second row, first column) then all commands will be executed successfully and the robot will stop at the cell $ (1, 2) $ (first row, second column).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1607E/e9041329204b86a5b243e3524c9fedaa23a2383e.png)The robot starts from cell $ (2, 1) $ (second row, first column). It moves right, right, down, left, up, and up. In this case it ends in the cell $ (1, 2) $ (first row, second column).Determine the cell from which the robot should start its movement in order to execute as many commands as possible.

## 样例 #1

### 输入

```
4
1 1
L
1 2
L
3 3
RRDLUU
4 3
LUURRDDLLLUU```

### 输出

```
1 1
1 2
2 1
3 2```

# 题解

## 作者：2huk (赞：3)

# E. [Robot on the Board 1](https://codeforces.com/contest/1607/problem/E)

## Description

一个机器人在一个 $n$ 行 $m$ 列的长方形网格上，它可以移到四个相邻的格子里。

给出一个字符串指令序列 $s$，里面只会出现 `U`，`D`，`L`，`R` 四种指令，分别对应往上下左右四个方向移动。

机器人可以在任何一个格子开始移动，它会严格按照顺序执行 $s$ 中的每个字符指令。当它移出了网格的边缘，它会停止工作，所以机器人不一定能成功的执行完一个命令集。

现在需要让你求出一个使机器人在停止工作之前尽可能执行更多命令的起点。

## Solution

四个方向同时取最优是不可能的，所以首先考虑将两个方向取最优。

具体地，开始时钦定答案为 $(1, 1)$，这样对于向下和向右的操作而言是最优的。

现在尝试按照指令字符串开始走。显然，如果走时不出界，那么继续走是更优的。

如果当前步是向下或向右，但是再走已经出界了，那么此时就已经找到了最优答案。因为我们开始时为向下和向右提供了足够大的空间，这两个操作走不了别的操作也就走不了了。

接下来考虑向上和向左的操作。如果当前步为向上或向左，且再走就要出界了，那么我们尝试将刚才走过的路线整体移动（当然，包括起点），使得这一步可以通过。

![](https://cdn.luogu.com.cn/upload/image_hosting/390xtbzp.png)

如果可以将路线移动则移动，若不能则结束。这里判断能否移动可以维护当前走过的点中，行和列的最大值是多少。那么判断整体移动会不会出界只需要判断路线中最大行和列会不会出界即可。

## Code

```cpp
int T, n, m, len;
char s[N];
int sx, sy, nowx, nowy, maxx, maxy;

PII Solve()
{
	n = read(), m = read();
	scanf("%s", s + 1);
	len = strlen(s + 1);
	sx = sy = nowx = nowy = maxx = maxy = 1;
	
	for (re int i = 1; i <= len; ++ i )
	{
		re char c = s[i];

		if (c == 'U')
		{
			if (nowx > 1) -- nowx;
			else if (maxx < n) ++ maxx, ++ sx;
			else return {sx, sy};
		}
		else if (c == 'D')
		{
			if (nowx < n) ++ nowx;
			else return {sx, sy};
		}
		else if (c == 'L')
		{
			if (nowy > 1) -- nowy;
			else if (maxy < m) ++ maxy, ++ sy;
			else return {sx, sy};
		}
		else
		{
			if (nowy < m) ++ nowy;
			else return {sx, sy};
		}

		maxx = max(maxx, nowx);
		maxy = max(maxy, nowy);
	}
	
	return {sx, sy};
}
```

---

## 作者：Jur_Cai (赞：3)

题解区都是 $O(n)$ 的，本人太菜，vp 的时候只想到了三分的做法。

首先可以发现 $\sf{U,D}$ 和 $\sf{L,R}$ 操作是互不影响，所以可以分开做。

考虑放在第一行，每下移一行，相当于为 $\sf{U}$ 操作多了一个空间，$\sf{U}$ 的贡献增加，而 $\sf{D}$ 的贡献减少，可以发现是单峰的，三分即可。

笔者三分学得比较逊，所以写得有些奇怪。

``` cpp
#include<bits/stdc++.h>
using namespace std;
char op[1000005];
int n,m,len;
inline int fud(int pos) {
	int res=0;
	for(int i=1; i<=len; i++) {
		if(op[i]=='U') {
			if(pos>1) pos--,res++;
		} else if(op[i]=='D') {
			if(pos<n) pos++,res++;
		}
	}
	return res;
}
inline int flr(int pos) {
	int res=0;
	for(int i=1; i<=len; i++) {
		if(op[i]=='L') {
			if(pos>1) pos--,res++;
		} else if(op[i]=='R') {
			if(pos<m) pos++,res++;
		}
	}
	return res;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int l,r,ans;
		scanf("%d%d",&n,&m);
		scanf("%s",op+1),len=strlen(op+1);
      		//把可行的操作数当做函数值
		l=1,r=n,ans=1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(l==r) {
				ans=l;
				break;
			}
			if(l+1==r) {
				if(fud(l)>fud(r)) ans=l;
				else ans=r;
				break;
			}
			if(fud(mid-1)>fud(mid+1)) ans=mid-1,r=mid;
			else ans=mid+1,l=mid;
		}
		cout<<ans<<" ";
		l=1,r=m,ans=1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(l==r) {
				ans=l;
				break;
			}
			if(l+1==r) {
				if(flr(l)>flr(r)) ans=l;
				else ans=r;
				break;
			}
			if(flr(mid-1)>flr(mid+1)) ans=mid-1,r=mid;
			else ans=mid+1,l=mid;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：让风忽悠你 (赞：2)

[原题](https://www.luogu.com.cn/problem/CF1607E)

## 题意

给出一个 $n \times m$ 的矩形网格，上面有一个机器人会根据指令上下左右移动，当这个机器人走出网格它就会停止运动，要求当它的起点在何处时能执行的指令最多。

## 做法

首先思考在什么时候需要改变起点位置，我们发现当机器人仅向右和向下移动时，因为只有它超出右边界或者下边界的时候才会停止运动，所以此时起点坐标最优为 $(1,1)$，所以可以将初始起点设置为 $(1,1)$。

这个时候再看向上和向左移动，要使机器人能执行的指令最多，最先需要解决的就是当前的指令，所以此时就应当改变机器人坐标。

接下来就是考虑改变坐标后如何判断越界的问题了，其实只需要记录向下移动和向右移动距离的最大值，再假设从当前位置走是否越界就好了。

## 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1000005

using namespace std;

int T,n,m;
int sx,sy,x,y;
int maxx,maxy;
char s[N];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		sx=sy=1; // 假设初始起点为(1,1) 
		maxx=maxy=x=y=0;
		scanf(" %s",s+1);
		int len=strlen(s+1);
		for(int i=1;i<=len;i++){
			// 左右移动 
			if(s[i]=='R'){
				if(sx+x==m) break; // 判断越界
				x++;
			}
			else if(s[i]=='L'){
				if(sx+maxx>=m && sx+x==1) break; // 判断此时是否碰到边界以及改变起点位置是否合理 
				if(x<=0 && sx+x==1) sx++; // 判断是否需要改变起点 
				x--;
			} 
			// 上下移动同理 
			else if(s[i]=='D'){
				if(sy+y==n) break;
				y++;
			}
			else if(s[i]=='U'){
				if(sy+maxy>=n && sy+y==1) break;
				if(y<=0 && sy+y==1) sy++;
				y--;
			}
			maxx=max(maxx,x);
			maxy=max(maxy,y);
			// 找出向右向下移动距离的最大值 
		}
		printf("%d %d\n",sy,sx);
	}
	return 0;
}
```


---

## 作者：GenesisCrystal (赞：1)

## Solution

对于每一个字符，我们可以先移动，然后令 $Max_x, Max_y, 
Min_x,Min_y$ 分别等于最大的 $x$，最大的 $y$，最小的 $x$，最小的 $y$。

然后进行更新。

如果 $Max_x + |Min_x| + 1 > n$ （$+ 1$ 是因为还有中间的格子）或 $Max_y + |Min_y| + 1 > m$（$+ 1$的原因同上），那么就不能再走了，此时应该使用上一次的 $Max_x,Max_y,Min_x,Min_y$。

## Code
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 2;

ll t, n, m;
string s;

int main() {
	for (cin >> t; t; t--) {
		cin >> n >> m >> s;
		int x = 0, y = 0;
		int xx = 0, xy = 0, nx = 0, ny = 0;
		int ansx = 0, ansy = 0;
		for (char c : s) {
			x += (c == 'U' ? -1 : (c == 'D' ? 1 : 0));
			y += (c == 'L' ? -1 : (c == 'R' ? 1 : 0));
            int lxx = xx, lxy = xy, lnx = nx, lny = ny;
			xx = max(xx, x), xy = max(xy, y);
			nx = min(nx, x), ny = min(ny, y);
			if (abs(xx) + abs(nx) + 1 > n || abs(xy) + abs(ny) + 1 > m) {
				ansx = n - lxx, ansy = m - lxy;
				break;
			}
		}
		if (!ansx && !ansy) {
			ansx = n - xx, ansy = m - xy;
		}
		cout << ansx << ' ' << ansy << '\n';
	}
	return 0;
}
```

---

## 作者：Shxt_Plus (赞：0)

## 思路
考虑怎么让机器人不走出界。

不妨把机器人放在向上走和向左走能走到 $(1,1)$ 的位置，显然若走到这个位置还有可能出界必定无解，此时直接退出即可。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
char s[1000005];

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%s",&n,&m,s+1);
		int len=strlen(s+1);
		int mxz=0,mxy=0,mxs=0,mxx=0,xx=0,xy=0,x=1,y=1;
		for(int i=1;i<=len;i++)
		{
			if(s[i]=='U')xx--;
			else if(s[i]=='D')xx++;
			else if(s[i]=='L')xy--;
			else xy++;
			mxs=max(-xx,mxs);
			mxx=max(xx,mxx);
			mxz=max(-xy,mxz);
			mxy=max(xy,mxy);
			if(mxs+mxx>=n || mxz+mxy>=m)break;
			x=mxs+1,y=mxz+1;
		}
		cout<<x<<" "<<y<<"\n";
	}
	return 0;
}
```

---

## 作者：DFbd (赞：0)

## 思路
因为当机器人移出了网格的边缘，它会停止工作，所以我们要尽量让它不走出边界。

把在每一个命令执行后，$x$ 坐标增加多少，$y$ 坐标增加了多少记录下来，再根据 $x$ 和 $y$ 坐标的变化判断出 $x$ 和 $y$ 坐标的上限或下限。

记录下 $x$ 和 $y$ 坐标的上限和下限，如果有一个下限超过了上限，就证明没有一个点能使执行完此命令不出边界了，于是可以输出上一个命令的上下限内任何一个点。

最后，如果执行完最后一个命令还不会出界，输出上下限内任何一个点。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, x, y, mxx, mxy, mnx, mny;//mxx：x上限，mxy：y上限，mnx：x下限，mny：y下限
string s;
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m >> s;
    x = 0, y = 0;
    mxx = n, mxy = m;
    mnx = 1, mny = 1;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == 'L')
        y--;
      else if (s[i] == 'R')
        y++;
      else if (s[i] == 'U')
        x--;
      else
        x++;
      int lxx = mxx, lxy = mxy, lnx = mnx, lny = mny;
      if (x < 0)
        mnx = max(mnx, abs(x) + 1);
      else
        mxx = min(mxx, n - x);
      if (y < 0)
        mny = max(mny, abs(y) + 1);
      else
        mxy = min(mxy, m - y);
      if (mnx > mxx || mny > mxy) {
        cout << lxx << " " << lxy << "\n";
        break;
      }
    }
    if (mnx <= mxx && mny <= mxy) cout << mxx << " " << mxy << "\n";
  }
  return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1607E)

&nbsp;

### 题目大意
给定 $t$ 个 $n\times m$ 的方格，每个方格上都有一个机器人，每个机器人都被下达了一串移动指令，它们将依次按照指令向上下左右移动。

需要注意的是，如果机器人在执行完某次指令后停在了方格外，它将停止工作。现在需要你为每个机器人安排一个位置，使它们都尽可能多的执行指令。

&nbsp;

### 解题思路
对于每组数据，我们记录机器人在执行每个指令后较原点向左右和上下偏移的距离，同时分别记录在执行每个指令前机器人向每个方向的最大偏移距离。

我们遍历所有操作，当发现机器人在执行某次操作后向一个方向偏离，同时这个偏离值与机器人向相反方向的最大偏移距离之和大于等于了一行（或一列）的格子数，我们就可以肯定机器人在这次操作后离开了方格。

举个例子：
```cpp
---------
| |	| | |
| | | | |
| | | | |
| |	| | |
---------
```
现在我们有一个 $4\times 4$ 的方格，假设机器人得到了这串指令：RRRUDDLLLLU。

不难发现，在机器人执行了第 $10$ 个指令后，它较原点向左偏移了 $1$ 个点，同时它向右最多偏移了 $3$ 个点，也就是说，原点的左侧至少要有一个点，而右边则至少要有三个点，但这在一个 $4\times 4$ 的方格中是不可能实现的，也就是说机器人执行完这个指令后移出了方格。

同时我们可以知道，在最后一次操作前，两个相反方向的最大偏移距离之和不可能超过行列上的方格数（否则早就该结束运行了）于是我们的坐标只需要向右留出最终最大向右偏离的格数，向下留出最大向下偏移的格数。

代码如下：
```cpp
int main(){
    scanf("%d",&t);

    while(t--){
        ll mx=0,my=0;
        scanf("%lld%lld",&n,&m);
        ll minx=0,miny=0;
        char c[maxn];
        scanf("%s",c+1);
        int siz=strlen(c+1);
        for(int i=1;i<=siz;i++){
            sumx[i]=sumx[i-1];
            sumy[i]=sumy[i-1];
            if(c[i]=='L') sumx[i]--;\\记录偏移
            if(c[i]=='R') sumx[i]++;
            if(c[i]=='U') sumy[i]--;
            if(c[i]=='D') sumy[i]++;
            //cout<<sumx[i]<<" "<<sumy[i]<<" "<<mx<<" "<<my<<" "<<minx<<" "<<miny<<endl;
            if(sumx[i]>=0){//根据向不同方向偏移判断
                if(sumx[i]+minx>=m) break; 
                mx=max(mx,sumx[i]);
            }
            else{
                if(-sumx[i]+mx>=m) break;
                minx=max(-sumx[i],minx);
            }
            if(sumy[i]>=0){
                if(sumy[i]+miny>=n) break;
                my=max(my,sumy[i]);
            }
            else{
                if(-sumy[i]+my>=n) break;
                miny=max(-sumy[i],miny);
            }
        }
        printf("%lld %lld\n",n-my,m-mx);
    }
    return 0;
}
```
完结撒花OvO。

---

## 作者：lichenghan (赞：0)

# CF1607E 题解

### 题意描述

有一个机器人在一个 $n\times m$ 的格子上，按照一个上下左右的命令集移动。如果出了边界就停止。现在让你选择一个起始点，让机器人能正常执行的命令最多。输出这个起始点。

### 思路

我们先假定起始点是 $(1,1)$ 。

如果下一步向上越界，则尝试把起始点下移（若当前起始点在最底下直接停止）；

如果下一步向左越界，同理。

如果下一步向右或下越界，则直接退出（因为我们保证已经是“顶”着上，左边界了）。

时间复杂度 $\Theta(n)$ 。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,m,lch;
char ch[1000010];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%s",&n,&m,ch+1);//从ch[1]开始
		lch=strlen(ch+1);
		int sx=1,sy=1,cx=1,cy=1,dx=1,ry=1;
		for(int i=1;i<=lch;i++){
			if(ch[i]=='U'){
				if(cx==1){
					if(dx==n) break;
					sx++;dx++;
				}
				else cx--;
			}else if(ch[i]=='D'){
				if(cx==n) break;
				cx++;
			}else if(ch[i]=='L'){
				if(cy==1){
					if(ry==m) break;
					sy++;ry++;
				}
				else cy--;
			}else{
				if(cy==m) break;
				cy++; 
			}
			dx=max(dx,cx);
			ry=max(ry,cy);
		}
		printf("%d %d\n",sx,sy);
	}
} 
```



---

## 作者：Madefaker (赞：0)

##### E. Robot on the Board 1

题目大意：

给定一个 $n \times m(1 \le n,m \le 10^6)$ 的矩形桌面，放置一个小机器人在某一个格子上。给出一串指令 $s(1 \leq s.size() \le 10^6)$ 由 `L`，`R`，`D`，`U` 组成，分别表示向左、右、上、下走。接着小机器人按顺序执行这些指令，但是如果出边界则会摔在地上报废。求使机器人在报废之前走的指令数最多的那个机器人**起始位置** $(r,c)$。

------

思路：

记录机器人顺着指令会走到的位置，即可能往左、右走多少格，往上、下走多少格，假设往左、右走的格子数量为 $a,b$（$a$ 是非负数，$b$ 是非正数），往上、下走的格子数量为 $c,d$（$c$ 是非负数，$d$ 是非正数）。我们考虑横向，纵向同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/jehvwt27.png)

如上图，这个矩形的 $m$ 一定要能够容纳 $a-b+1$ 个数，也就是 $m \ge a - b + 1$。一旦 $m < a-b+1$，则该机器人将无可避免地报废，此时 $c$ 的取值就确定了，也就是在 $m==a-b+1$ 的时候上图那个 $x$ 的位置。

那么我们在 $m == a-b+1$ 时就确定好 $c$ 的取值即可。把上图的 $x+b$ 看作最左边的点 $1$，那么 $x=-b+1$。故 $c=-b+1$。

------

实现：

按照“思路”内容模拟即可。

时间复杂度 $O(n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >>t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		string s;
		cin >> s;
		int x = 0, y = 0, xmin = 0, xmax = 0, ymin = 0, ymax = 0, xpos = 0, ypos = 0;
		for(char op : s) {
			if(xmax - xmin + 1 >= m && xpos == 0) 
				xpos = - xmin + 1;
			
			if(ymax - ymin + 1 >= n && ypos == 0) 
				ypos = - ymin + 1;
			if (op == 'L') xmin = min(xmin, --x);
			else if(op == 'R') xmax = max(xmax, ++x);
			else if(op == 'U') ymin = min(ymin, --y);
			else ymax = max(ymax, ++y);
		}
		if(xpos == 0) xpos = - xmin + 1;
		if(ypos == 0) ypos = - ymin + 1;
		cout << ypos << " " << xpos << endl;
	}
	return 0;
}
```



---

