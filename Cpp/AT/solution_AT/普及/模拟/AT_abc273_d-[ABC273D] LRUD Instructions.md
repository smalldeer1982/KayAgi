# [ABC273D] LRUD Instructions

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc273/tasks/abc273_d

$ H $ 行 $ W $ 列のグリッドがあります。上から $ i $ 行目、左から $ j $ 列目にあるマスをマス $ (i,\ j) $ で表します。  
 $ N $ 個のマス $ (r_1,\ c_1),\ (r_2,\ c_2),\ \ldots,\ (r_N,\ c_N) $ は壁になっています。

はじめ、高橋君はマス $ (r_\mathrm{s},\ c_\mathrm{s}) $ にいます。

高橋君に $ Q $ 個の指示が与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ i $ 番目の指示は文字 $ d_i $ と正整数 $ l_i $ の組で表されます。$ d_i $ は `L` 、`R` 、`U` 、`D` のいずれかの文字であり、それぞれ左、右、上、下の方向を表します。

$ i $ 番目の指示に対して高橋君は下記の行動を $ l_i $ 回繰り返します。

> 現在いるマスに対して、$ d_i $ が表す向きに壁のないマスが隣接しているなら、そのマスに移動する。 そのようなマスが存在しない場合は、何もしない。

$ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ i $ 番目までの指示を実行した直後に高橋君がいるマスを出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 10^9 $
- $ 1\ \leq\ r_\mathrm{s}\ \leq\ H $
- $ 1\ \leq\ c_\mathrm{s}\ \leq\ W $
- $ 0\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ r_i\ \leq\ H $
- $ 1\ \leq\ c_i\ \leq\ W $
- $ i\ \neq\ j\ \Rightarrow\ (r_i,\ c_i)\ \neq\ (r_j,\ c_j) $
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $について、$ (r_\mathrm{s},\ c_\mathrm{s})\ \neq\ (r_i,\ c_i) $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ d_i $ は `L` 、`R` 、`U` 、`D` のいずれかの文字
- $ 1\ \leq\ l_i\ \leq\ 10^9 $
- $ d_i $ 以外の入力値は整数

### Sample Explanation 1

与えられるグリッドと高橋君の初期位置は下記の通りです。 ここで、`#` は壁のマスを、`T` は高橋君がいるマスを表し、`.` がその他のマスを表します。 ``` ...#. .#... ..... ...T. ..#.. ``` $ 1 $ つ目の指示に対して高橋君は、左に $ 2 $ マス移動し、高橋君の位置は下記の通り、マス $ (4,\ 2) $ になります。 ``` ...#. .#... ..... .T... ..#.. ``` $ 2 $ つ目の指示に対して高橋君は、上に $ 1 $ マスに移動した後、次の移動先が壁であるために「何もしない」を $ 2 $ 回行います。その結果、高橋君の位置は下記の通り、マス $ (3,\ 2) $ になります。 ``` ...#. .#... .T... ..... ..#.. ``` $ 3 $ つ目の指示に対して高橋君は、左に $ 1 $ マス移動した後、次の移動先となるマスが存在しないために「何もしない」を $ 1 $ 回行います。その結果、高橋君の位置は下記の通り、マス $ (3,\ 1) $ になります。 ``` ...#. .#... T.... ..... ..#.. ``` $ 4 $ つ目の指示に対して高橋君は、右に $ 4 $ マス移動し、高橋君の位置は下記の通り、マス $ (3,\ 5) $ になります。 ``` ...#. .#... ....T ..... ..#.. ```

## 样例 #1

### 输入

```
5 5 4 4
3
5 3
2 2
1 4
4
L 2
U 3
L 2
R 4```

### 输出

```
4 2
3 2
3 1
3 5```

## 样例 #2

### 输入

```
6 6 6 3
7
3 1
4 3
2 6
3 4
5 5
1 1
3 2
10
D 3
U 3
L 2
D 2
U 3
D 3
U 3
R 3
L 3
D 1```

### 输出

```
6 3
5 3
5 1
6 1
4 1
6 1
4 1
4 2
4 1
5 1```

# 题解

## 作者：DYYqwq (赞：11)

# 题意

你在一个 $ h \times w $ 的矩阵中，矩阵中有 $N$ 个障碍物。现在给你 $Q$ 次询问，对于每次询问，你需要回答出问向**前/后/左/右**走，会到达哪里（具体是前后左右会输入） 。

# Solution

观察题目，我们发现，无论问的是前/后/左/右，你都只会在**一条直线**上走，那对于这条直线，我们可以记录所有这条直线上的障碍物，然后找到距离当前点最近的障碍物，也就是说我们只能走到那个障碍物那块。。说的有点抽象，画个图吧！

![qwq](https://cdn.luogu.com.cn/upload/image_hosting/zkwfrwgv.png)

很显然，只要我们找到离我们最近的障碍物，就能知道我们最多会到哪里了。

但是还有问题啊，我们的数据范围会达到 $10^9$ 啊，怎么办？STL 大法吼啊！直接用 ```map``` 套 ```set``` 就可以啦！为什么选用 ```set``` 呢？是因为它可以自动排序呀！

还有不懂，看看代码吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
int hh , ww;
int sx , sy;
int n;
int q;
map<int , set<int> >h; // 统计行内障碍物
map<int , set<int> >l; // 统计列内障碍物
int main()
{
    scanf("%d%d" , &hh , &ww);
    scanf("%d%d" , &sx , &sy);
    scanf("%d" , &n);
    for(int i = 1 ; i <= n ; i ++)
    {
        int x , y;
        scanf("%d%d" , &x , &y);
        h[x].insert(y); // 放入数组
        l[y].insert(x);
        // 这里涉及了map的insert，不懂就bdfs吧qwq
    }
    scanf("%d" , &q);
    while(q --)
    {
        string op;
        int d;
        h[sx].insert(0);
        h[sx].insert(ww + 1);
		l[sy].insert(0);
		l[sy].insert(hh + 1);
        // 可以把边界也算作障碍，因为到了边界也和障碍一样不能走了qwq
        cin >> op;
		scanf("%d" , &d);
		if(op == "L")
		{
			int zhangai = *(-- h[sx].lower_bound(sy));
			// 0_______障碍_______能走的_______sx
			// 0_______能走的_____障碍________sx
			// <-----  越往左越好
			sy = max(0 , max(zhangai + 1 , sy - d));
		}
		if(op == "R")
		{
			int zhangai = *h[sx].upper_bound(sy);
			// 0_______障碍_______能走的_______sx
			// 0_______能走的_____障碍________sx
			//   越往右越好 ------->
            sy = min(ww , min(zhangai - 1 , sy + d));
		}
		if(op == "U")
		{
			int zhangai = *(-- l[sy].lower_bound(sx));
			sx = max(0 , max(zhangai + 1 , sx - d));
		}
		if(op == "D")
		{
			int zhangai = *l[sy].upper_bound(sx);
			sx = min(hh , min(zhangai - 1 , sx + d));
		}
        // 同理
		printf("%d %d\n" , sx , sy);
    }
    return 0;
}
```

---

## 作者：2020luke (赞：1)

# [[ABC273D] LRUD Instructions](https://www.luogu.com.cn/problem/AT_abc273_d) 题解

很好的一道大模拟，使我爆 $0$。

## 思路解析

大模拟，我们只需要用一个 $x,y$ 表示我们当前的位置，而对于每一个移动，我们就判断在当前移动方向上离当前点最近的点，若该点在当前行进路线上，则把当前位置设为该点前面的一个。

其中判断在当前移动方向上离当前点最近的点可以使用离散化，然后使用二分法查找第一个大于当前点的障碍物，而若是朝负方向移动，则可以修改 `lower_bound` 里的迭代器起终点和 `cmp` 函数，这样就可以用 `lower_bound` 实现反向二分。

**PS：考试时能用 `vector` 就千万不要用 `set`！！！常数奇大无比！！ [挂分记录](https://atcoder.jp/contests/abc273/submissions/48925624)**

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fir first
#define sec second
int h, w, n;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int sx, sy;
map<int, vector<int> > mph, mpl;
map<char, int> mpc;
int q;
void init() {
	mpc['U'] = 0;
	mpc['D'] = 1;
	mpc['L'] = 2;
	mpc['R'] = 3;
}
signed main() {
	init();
	cin >> h >> w >> sx >> sy;
	cin >> n;
	for(int i = 1, r, c; i <= n; i++) {
		cin >> r >> c;
		mph[r].push_back(c);
		mpl[c].push_back(r);
	}
	for(auto &it : mph) {
		it.sec.push_back(0);
		it.sec.push_back(2e9);
		sort(it.sec.begin(), it.sec.end());
	}
	for(auto &it : mpl) {
		it.sec.push_back(0);
		it.sec.push_back(2e9);
		sort(it.sec.begin(), it.sec.end());
	}
	cin >> q;
	int x = sx, y = sy;
	while(q--) {
		char ch;
		int l;
		cin >> ch >> l;
		int d = mpc[ch];
		int nx = x + dx[d] * l;
		nx = max(1ll, nx);
		nx = min(nx, h);
		int ny = y + dy[d] * l;
		ny = max(1ll, ny);
		ny = min(ny, w);
		if(d == 0) {
			if(!mpl[ny].empty()) {
				int temp = *lower_bound(mpl[ny].rbegin(), mpl[ny].rend(), x, [](int xx, int yy) {	//lambda表达式
					return xx > yy;
				});
				if(temp >= nx && temp <= x) {
					x = temp + 1;
				}
				else {
					x = nx;
				}
			}
			else {
				x = nx;
			}
		}
		else if(d == 1) {
			if(!mpl[ny].empty()) {
				int temp = *lower_bound(mpl[ny].begin(), mpl[ny].end(), x);
				if(temp >= x && temp <= nx) {
					x = temp - 1;
				}
				else {
					x = nx;
				}
			}
			else {
				x = nx;
			}
		}
		else if(d == 2) {
			if(!mph[nx].empty()) {
				int temp = *lower_bound(mph[nx].rbegin(), mph[nx].rend(), y, [](int xx, int yy) {
					return xx > yy;
				});
				if(temp >= ny && temp <= y) {
					y = temp + 1;
				}
				else {
					y = ny;
				}
			}
			else {
				y = ny;
			}
		}
		else if(d == 3) {
			if(!mph[nx].empty()) {
				int temp = *lower_bound(mph[nx].begin(), mph[nx].end(), y);
				if(temp >= y && temp <= ny) {
					y = temp - 1;
				}
				else {
					y = ny;
				}
			}
			else {
				y = ny;
			}
		}
		cout << x << " " << y << "\n";
	}
	return 0;
}
```



---

## 作者：Epoch_L (赞：1)

ABC273 A-F题解全部可见：[link](https://www.cnblogs.com/LAK666/p/16795179.html)

## D
有 `L` `R` `U` `D`四种操作，每次询问操作 $l_i$ 次，遇到墙则停下，问会到达哪个位置。
### Solution
很明显需要对于每一行列记录墙的位置，并且需要排好序方便二分查找，用 map 套 set 即可。

每次二分找到当前方向离当前位置最近的墙，看走 $l_i$ 步会不会被拦下来。

因为不能走出范围，这就很恶心，为了避免大量的特判，我们可以对于行，将 $0$ 和 $m+1$ 设为墙，对于列，将 $0$ 和 $n+1$ 设为墙，这样代码会好写很多。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
map<int,set<int> >f1;
map<int,set<int> >f2;
signed main()
{
	int n,m,sx,sy,t,q;
	read(n),read(m),read(sx),read(sy);
	read(t);
	while(t--)
	{
		int x,y;
		read(x),read(y);
		f1[x].insert(y);
		f2[y].insert(x);
	}
	read(q);
	while(q--)
	{
		f1[sx].insert(0);f1[sx].insert(m+1);
		f2[sy].insert(0);f2[sy].insert(n+1);//将边界设为墙
		char op;
		int d,tx,ty;
		cin>>op;read(d);
		if(op=='L')
		{
			ty=*--f1[sx].lower_bound(sy);
			if(sy-ty-1>=d)sy-=d;
			else sy=ty+1;
		}
		if(op=='R')
		{
			ty=*f1[sx].upper_bound(sy);
			if(ty-sy-1>=d)sy+=d;
			else sy=ty-1;
		}
		if(op=='U')
		{
			tx=*--f2[sy].lower_bound(sx);
			if(sx-tx-1>=d)sx-=d;
			else sx=tx+1;
		}
		if(op=='D')
		{
			tx=*f2[sy].upper_bound(sx);
			if(tx-sx-1>=d)sx+=d;
			else sx=tx-1;
		}
		printf("%lld %lld\n",sx,sy);
	}
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

我们需要实时维护位置，然后考虑二分这里最近的那个障碍物是否对下标有影响，所以可以用 set，智慧的你发现了下标会到 $10^9$ 所以，要套一个 map。

这道题其实考了你会不会 set。2020luke 在题解中表示：别用set，因为会超时。

但是我用了 set，没有超时，是怎么回事呢？

很简单，对比一下两行伪代码：

```cpp
set.lower_bound(x);
```
和：

```cpp
lower_bound(set.begin(),set.end(),x);
```

有什么区别呢？

科普一下，前者时间复杂度是 $O(\log n)$ 的。后者 $O(n)$ 时间复杂度的。所以才会挂掉，2020luke 使用了后者并警钟长鸣。

再次科普：```prev(it)``` 的作用是 $it$ 这个迭代器往前一个位置。

[link](https://atcoder.jp/contests/abc273/submissions/49166402)。

---

## 作者：kczw (赞：0)

# 题意
给定一个 $H\times W$ 地图，一个起点 $r_s,c_s$ 和 $N$ 个障碍物。有 $Q$ 个操作，对于每个操作，向上下左右的一个方向移动一定步数，若到地图边界或是遇上障碍物，停下。
# 思路
首先看到 $2\le H,W\le10^9$ 的数据范围，很容易知道此题铁定要离散。然后理所应当想到用 map 和 set。
- map 用于存储一列、一行是否有障碍物
- set 用于存储某列、某行障碍物具体的位置

以上两个数据结构的应用很容易能知道它们需要嵌套，即 `map<int,set<int>>`。

然后我们就可以在移动的方向上先用 map 查找是否有障碍物，如果有，再用 set 查询。
# 实现
```cpp
#include<iostream>
#include<map>
#include<set>
using namespace std;
map<int,set<int>> ll,__;
int h,w,I,J,q,id;
int main(){
	scanf("%d%d%d%d%d",&h,&w,&I,&J,&q);
	for(int i=1,x,y;i<=q;i++){
		scanf("%d%d",&x,&y);
		__[x].insert(y);
		ll[y].insert(x);
	}scanf("%d",&q);
	char p;
	for(int i=1,x;i<=q;i++){
		cin>>p;scanf("%d",&x);
		if(p=='U'){
			auto a=ll[J].lower_bound(I);
			if(a==ll[J].begin())I=max(I-x,1);
			else I=max(I-x,*--a+1); 
		}else if(p=='D'){
			auto a=ll[J].lower_bound(I);
			if(a==ll[J].end())I=min(I+x,h);
			else I=min(I+x,*a-1);
		}else if(p=='L'){
			auto a=__[I].lower_bound(J);
			if(a==__[I].begin())J=max(J-x,1);
			else J=max(J-x,*--a+1);
		}else{
			auto a=__[I].lower_bound(J);
			if(a==__[I].end())J=min(J+x,w);
			else J=min(J+x,*a-1);
		}printf("%d %d\n",I,J);
	}return 0;
}
```

---

## 作者：CodingShark (赞：0)

~~恭祝本蒟蒻在比赛时 AC 此题~~

根据题意，每次操作我们只需要找出指定方向上离当前点最近的障碍物即可。

不妨将每行和每列障碍的位置先存下来，接着排序，这样访问的时候可以直接二分查找。

另外记得要将边界条件加上，代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int H, W, N, Q, l, rs, cs;
char d[3];
unordered_map<int, vector<int>> wallR, wallC;
 
int main()
{
    scanf("%d %d %d %d %d", &H, &W, &rs, &cs, &N);
    for (int i = 1; i <= N; i++)
    {
        int r, c;
        scanf("%d %d", &r, &c);
        wallR[r].push_back(c);
        wallC[c].push_back(r);
    }
    for (auto &&v : wallR)
    	sort(v.second.begin(), v.second.end());
    for (auto &&v : wallC)
    	sort(v.second.begin(), v.second.end());
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%s %d", d, &l);
        if (d[0] == 'L')
        {
            vector<int> &v = wallR[rs];
            int pos = lower_bound(v.begin(), v.end(), cs) - v.begin();
            if (pos == 0)
                cs = max(1, cs - l);
            else
                cs = max(v[pos - 1] + 1, cs - l);
        }
        else if (d[0] == 'R')
        {
            vector<int> &v = wallR[rs];
            int pos = lower_bound(v.begin(), v.end(), cs) - v.begin();
            if (pos == v.size())
                cs = min(W, cs + l);
            else
                cs = min(v[pos] - 1, cs + l);
        }
        else if (d[0] == 'U')
        {
            vector<int> &v = wallC[cs];
            int pos = lower_bound(v.begin(), v.end(), rs) - v.begin();
            if (pos == 0)
                rs = max(1, rs - l);
            else
                rs = max(v[pos - 1] + 1, rs - l);
        }
        else
        {
            vector<int> &v = wallC[cs];
            int pos = lower_bound(v.begin(), v.end(), rs) - v.begin();
            if (pos == v.size())
                rs = min(H, rs + l);
            else
                rs = min(v[pos] - 1, rs + l);
        }
        printf("%d %d\n", rs, cs);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

二分题。

查找向前进方向走几步会碰到距离当前点**最近**的墙壁，如果没有墙壁的话就**一直前进**，如果碰到墙壁的话就**停在墙壁之前**，这样就能迅速完成一条指令。

可以用 `std::map<int, std::vector<int>>` 来维护每一行和每一列的墙壁，然后二分找到前进方向上距离当前点**最近的墙壁的位置**

时间复杂度 $O((N+Q) \log N)$。

#### 代码：
```
# include <bits/stdc++.h>
# define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
using MP = map<int, vector<int>>;
int main() {
    int h, w, si, sj, n;
    cin >> h >> w >> si >> sj >> n;
    MP mpL, mpR, mpU, mpD;
    rep(ni, n) {
        int i, j;
        cin >> i >> j;
        mpR[i].push_back(j);
        mpL[i].push_back(-j);
        mpD[j].push_back(i);
        mpU[j].push_back(-i);
    }
    auto init = [&](MP& mp, int r) {
        for (auto& p : mp) {
            sort(p.second.begin(), p.second.end());
            p.second.push_back(r);
        }
    };
    init(mpR, w+1);
    init(mpL, 0);
    init(mpD, h+1);
    init(mpU, 0);
    auto f = [&](MP& mp, int i, int j, int l, int r) {
        auto it = mp.find(i);
        if (it == mp.end()) return min(j+l, r-1);
        auto& is = it->second;
        int wj = *lower_bound(is.begin(), is.end(), j); 
        return min(j+l, wj-1);
    };
    int q;
    cin >> q;
    rep(qi, q) {
        char d; int l;
        cin >> d >> l;
        if (d == 'R') sj = f(mpR, si, sj, l, w+1);
        if (d == 'L') sj = -f(mpL, si, -sj, l, 0);
        if (d == 'D') si = f(mpD, sj, si, l, h+1);
        if (d == 'U') si = -f(mpU, sj, -si, l, 0);
        cout << si << ' ' << sj << '\n';
    }
    return 0;
}
```

---

## 作者：Register_int (赞：0)

思路非常暴力。既然模拟会超时，我们就优化模拟的过程。将所有障碍按行和列分别存入 `map` 套 `set` 中，那么就能快速找到位于高桥上下左右的最近障碍。判断走完 $L$ 步后的对应关系就可以做到单次 $O(\log n)$ 了。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<int, set<int>> row;
map<int, set<int>> col;

int h, w, n, q, x, y;

int r, c, l;

char opt[2];

int main() {
	scanf("%d%d%d%d", &h, &w, &x, &y);
	for (scanf("%d", &n); n--;) scanf("%d%d", &r, &c), row[r].insert(c), col[c].insert(r);
	for (scanf("%d", &q); q--;) {
		scanf("%s%d", opt, &l);
		switch (*opt) {
		case 'L': {
			auto it = row[x].lower_bound(y);
			if (it == row[x].begin()) y = max(y - l, 1);
			else y = max(y - l, *--it + 1);
			break;
		}
		case 'R': {
			auto it = row[x].lower_bound(y);
			if (it == row[x].end()) y = min(y + l, w);
			else y = min(y + l, *it - 1);
			break;
		}
		case 'U': {
			auto it = col[y].lower_bound(x);
			if (it == col[y].begin()) x = max(x - l, 1);
			else x = max(x - l, *--it + 1);
			break;
		}
		case 'D': {
			auto it = col[y].lower_bound(x);
			if (it == col[y].end()) x = min(x + l, h);
			else x = min(x + l, *it - 1);
			break;
		}
		}
		printf("%d %d\n", x, y);
	}
}
```

---

## 作者：郑朝曦zzx (赞：0)

## 一 解题思路
- 题目评价：很好的一道模拟题，有较多的细节，在 ABC D 题中难度较高 （AT 评分 1119）。
### 思路
比较容易想到，记录下每一行和每一列的墙，在移动的时候使用二分法判断最多可以移动几步，然后就做完了。

具体来说就是对于每一次移动，我们使用二分法以 $O(\log n)$ 的时间复杂度找到它前面的第一个“墙”，如果在它的距离大于 $k$ 那么直接走即可（肯定撞不到），否则能走几步走几步。
### 坑点
1. 地图很大，存不下
- 解决办法：用 map 记录
2. 遇到地图边界
- 解决办法：给每行每列强制加上头和尾

## 二 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
void fastInp()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int n, m, x, y, p, q;
map <int, vector <int> > wall_x, wall_y;
set <int> vx, vy;
int main()
{
//	freopen("input.txt", "r", stdin);
	fastInp();
	cin >> n >> m >> x >> y;
	cin >> p;
	for (int i = 1; i <= p; ++i)
	{
		int u, v; cin >> u >> v;
		vx.insert(u); vy.insert(v);
		wall_x[u].push_back(v);
		wall_y[v].push_back(u);	
	}
	for (set <int> :: iterator it = vx.begin(); it != vx.end(); ++it)
	{
		int i = (*it);
		wall_x[i].push_back(0);	
		wall_x[i].push_back(m + 1);
		sort(wall_x[i].begin(), wall_x[i].end());
	}
	for (set <int> :: iterator it = vy.begin(); it != vy.end(); ++it)
	{
		int i = (*it);
		wall_y[i].push_back(0);	
		wall_y[i].push_back(n + 1);
		sort(wall_y[i].begin(), wall_y[i].end());
	}
	cin >> q;
	for (int i = 1; i <= q; ++i)
	{
		if (wall_x[x].size() == 0)
		{
			wall_x[x].push_back(0);	
			wall_x[x].push_back(m + 1);
		}
		if (wall_y[y].size() == 0)
		{
			wall_y[y].push_back(0);	
			wall_y[y].push_back(n + 1);
		}
		int l; char c;
		cin >> c >> l;
		if (c == 'U')
		{
			int pos = lower_bound(wall_y[y].begin(), wall_y[y].end(), x) - wall_y[y].begin() - 1;
			pos = wall_y[y][pos];
			if (pos < x - l) x -= l;
			else x = pos + 1;
		}
		else if (c == 'D')
		{
			int pos = lower_bound(wall_y[y].begin(), wall_y[y].end(), x) - wall_y[y].begin();
			pos = wall_y[y][pos];
			if (pos > x + l) x += l;
			else x = pos - 1;
		}
		else if (c == 'L')
		{
			int pos = lower_bound(wall_x[x].begin(), wall_x[x].end(), y) - wall_x[x].begin() - 1;
			pos = wall_x[x][pos];
			if (pos < y - l) y -= l;
			else y = pos + 1;
		}
		else
		{
			int pos = lower_bound(wall_x[x].begin(), wall_x[x].end(), y) - wall_x[x].begin();
			pos = wall_x[x][pos];
			if (pos > y + l) y += l;
			else y = pos - 1;
		}
		cout << x << " " << y << endl;
	}
    return 0;
}
```


---

