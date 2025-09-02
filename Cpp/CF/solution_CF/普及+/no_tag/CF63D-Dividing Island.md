# Dividing Island

## 题目描述

## 题目简述

有一个 $a \times b$ 和一个 $c \times d$ 的矩形 $(b \neq d\;)$ ，其中长度为 $a$ 和 $c$ 的边共线，如图所示:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63D/d0dfe8fb20d3bd76651bd208632c7ccbf8e3af11.png)

要求将这个图形分为 $n$ 个完整的块，其中第 $i$ 块的面积为 $x_i$。

## 样例 #1

### 输入

```
3 4 2 2 3
5 8 3
```

### 输出

```
YES
aaabb
aabbb
cbb..
ccb..
```

## 样例 #2

### 输入

```
3 2 1 4 4
1 2 3 4
```

### 输出

```
YES
abbd
cccd
...d
...d
```

# 题解

## 作者：SpringFullGarden (赞：1)

## 题意

有一个 $a \times b$ 和一个 $c \times d$ 的矩形 $(b \ne d)$ 拼在一起，有一条公共边:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63D/d0dfe8fb20d3bd76651bd208632c7ccbf8e3af11.png)

要求将这个图形分为 $n$ 个联通的块，其中第 $i$ 块的面积为 $x_i$。

## 思路

沿着一条线不重复地把整个图形走完，就可以保证每一块都联通，所以没有无解情况。

有很多种走法，这里采用 `S` 型走法，要注意：

- $b, d$ 的大小关系；
- $\min(b, d)$ 的奇偶性所产生对起点的影响；
- `.` 的位置。

## 代码 

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define sp() putchar(' ')
#define et() putchar(' \n')
using namespace std;

inline int rd() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
inline void wt(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) wt(x / 10);
    putchar(x % 10 + '0');
    return;
}

int mp[114][114], x[30];

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
	puts("YES");
	int a = rd(), b = rd(), c = rd(), d = rd(), n = rd();
	for(int i = 1; i <= n; i++) x[i] = rd();
	if(b > d) {
		int flag = d & 1, nw = 1, cnt = 0;
		for(int i = 1; i <= b; i++) {
			int r = (i > d) ? a : a + c;
			if(flag) {
				for(int j = r; j; j--) {
					mp[i][j] = nw, cnt++;
					if(cnt >= x[nw]) nw++, cnt = 0;	
				}
			}
			else {
				for(int j = 1; j <= r; j++) {
					mp[i][j] = nw, cnt++;
					if(cnt >= x[nw]) nw++, cnt = 0;
				}
			}
			flag ^= 1;
		}
	}
	else {
		int flag = !(b & 1), nw = 1, cnt = 0;
		for(int i = 1; i <= d; i++) {
			int l = (i > b) ? a : 0;
			if(flag) {
				for(int j = a + c; j > l; j--) {
					mp[i][j] = nw, cnt++;
					if(cnt >= x[nw]) nw++, cnt = 0;	
				}
			}
			else {
				for(int j = l + 1; j <= a + c; j++) {
					mp[i][j] = nw, cnt++;
					if(cnt >= x[nw]) nw++, cnt = 0;
				}
			}
			flag ^= 1;
		}
	}
	for(int i = 1; i <= max(b, d); i++, puts("")) 
		for(int j = 1; j <= a + c; j++) 
			if(mp[i][j]) cout << char(mp[i][j] + 96);
			else cout << '.';
    return 0;
}
```

---

## 作者：renrua52 (赞：1)

# 思路
首先看下题意，地图的形状是两个矩形拼在一起且有一条边共线。题目保证sum(x)与地图面积相等。于是问题简化为：将地图分为面积为x[i]的n个联通块。
## 引理
非常容易想到的是，这样的问题是一定有解的；一种可行的填法是：先尽量将地图转化为简单图形（即将地图的一个“凸出”的块填满），于是易知剩下的解法。
## 建立模型
有了如上思路，我们可以简单地得到满足如下条件的构造方法：  
（1）各个分块相联通：按照“首尾相连”的顺序进行填充，一种字母填完后立即换成下一种字母继续填充；  
（2）对（1）的补充：为保证“首尾相连”的填法顺利进行，需要根据图形讨论起始点在图形左侧还是右侧（对x讨论，y的情况无需讨论，总可以从第一行开始）。
![](https://i.loli.net/2020/03/10/czRNdKuhlVAQi5P.png)   
观察该图并进行手算后得知，分类讨论情况如下:  
####  b > d  
<i> d % 2 == 0  
从最左侧开始(即x = 1)  
<ii> d % 2 != 0  
从最右侧开始(即x = a + c)  
####  b < d(可看作上一种情况的镜像)
<i> d % 2 != 0  
从最左侧开始(即x = 1)  
<ii> d % 2 == 0  
从最右侧开始(即x = a + c)  
  
显然，从最左侧开始时，初始方向向右；从最右侧开始时，初始方向向左。
# 实现
首先依以上结论得出初始位置x, y及方向值dir(用1或-1表示）。我们还可以预处理出二维数组g来表示可以到达的点，方便后续操作。  
随后以dir为方向扫描整张图，出现越界时（利用g数组判断）将x回退，同时y ++，dir *= -1，即完成了“掉头”操作。  
输出时，依然依据g数组来确定是否有一个有意义的值，并输出。  
## 注意事项
本题总体较为简单，唯一的易错点在于二维数组的大小。注意a, b, c, d <= 50，故a + c <= 100，N需要取到100方可避免越界。  
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 110;

int a, b, c, d, n, t;
bool g[N][N] = {0};
int dir, x, y;
char ans[N][N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); //读入优化，考场慎用 
	cin >> a >> b >> c >> d >> n;
	
	//预处理出g数组 
	for(int i = 1; i <= a; ++ i) for(int j = 1; j <= b; ++ j) g[i][j] = 1;
	for(int i = a + 1; i <= a + c; ++ i) for(int j = 1; j <= d; ++ j) g[i][j] = 1;
	
	//对x, y, dir进行讨论 
	if(b > d)
		if(d & 1) //注：d & 1 相当于 d % 2 
			x = a + c, y = 1, dir = - 1;
		else
			x = 1, y = 1, dir = 1;
	else
		if(b & 1)
			x = 1, y = 1, dir = 1;
		else
			x = a + c, y = 1, dir = -1; 
	
	//扫描填充 
	for(int i = 0; i < n; ++ i){
		cin >> t;
		while(t --){
			ans[x][y] = 'a' + i;
			x += dir;
			if(!g[x][y]){ //越界 
				x -= dir; //x回退一格 
				++ y; //进入下一行 
				dir = - dir; //掉头 
			}
		}
	}
	cout << "YES\n"; //一定存在解法 
	for(int i = 1; i <= max(b, d); ++ i){
		for(int j = 1; j <= a + c; ++ j)
			cout << (g[j][i] ? ans[j][i] : '.'); //根据g值判断是否存在有效值 
			//由于构建坐标系时(i, j)表示为先列后行，但输出时应先行后列，故写为ans[j][i]
		cout << endl;
	}
	
	return 0;
}
```


---

## 作者：Nuclear_Fish_cyq (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF63D)

[CF 原题传送门](https://codeforces.com/problemset/problem/63/D)

[提交记录](https://www.luogu.com.cn/record/128196293)


## 做法

我们发现，如果我们可以找到一条遍历所有格子的线路的话，我们就可以找到对应的一个答案。我们可以从线的起点开始，在线的前 $x_1$ 个格子上填 `a`，在线的前 $x_2$ 个格子上填 `b`，在线的前 $x_3$ 个格子上填 `c`，以此类推。由于总可以构造出这样的线路，所以不存在无解的情况。那么，现在问题就是如何构造这条回路了，实际上，只要你能想出任意一个线路都可以，但那样就太没有规律了，我这里采用了一种 S 字形的线路，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ug0kbn3a.png)

接下来就是一些细节了。首先，线路的起点在左右两端都有可能，要看情况选择，不然就会形成类似下图绿色路线的不完整错误路线。

![](https://cdn.luogu.com.cn/upload/image_hosting/e36b3jqg.png)

上代码。可能码风比较奇怪，不要太在意。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, a, b, c, d, s[26], maxx, maxy, x, y, ans[50][100];
bool fac;
bool check(int tx, int ty){//判断点是否在图形内 
	return (tx >= 0 && ty >= 0) && ((tx < b && ty < a) || (tx < d && ty >= a && ty < maxy));
}
void move(){//移动一格 
	if(fac){
		if(!check(x, y - 1)){
			fac = !fac;
			x++;
		}
		else{
			y--;
		}
	}
	else{
		if(!check(x, y + 1)){
			fac = !fac;
			x++;
		}
		else{
			y++;
		}
	}
	return;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout << "YES" << endl;
	cin >> a >> b >> c >> d >> n;
	maxx = max(b, d);
	maxy = a + c;
	if((b >= d && d % 2 == 1) || (b < d && b % 2 == 0)){//判断初始时面朝方向和位置
		y = maxy - 1;
		fac = true;
	}
	for(int i = 0; i < n; i++){
		cin >> s[i];
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < s[i]; j++){
			ans[x][y] = i;
			move();
		}
	}
	for(int i = 0; i < maxx; i++){
		for(int j = 0; j < maxy; j++){
			if(check(i, j)){
				cout << (char)(ans[i][j] + 'a');
			}
			else{
				cout << '.';
			}
		}
		cout << endl;
	}
	return 0;
}

```


---

## 作者：Fantasy_Segment_Tree (赞：0)

## part $1$ 题目大意

本题给定一个 $a \times b + c \times d$ 的图形，求能否把这个图形分成 $n$ 个连续块，其中第 $i$ 个块占的总格子数量是 $x_i$，询问有无解法，如果有，求其中一种方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63D/d0dfe8fb20d3bd76651bd208632c7ccbf8e3af11.png)

## part $2$ 思路

问题 $1$：**本题有无解的情况吗？**

![](https://cdn.luogu.com.cn/upload/image_hosting/u1rhq7pj.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

如果把每一个块按照箭头所指的方向进行摆放，例如：

```
aaaab
ccbbb
cccdd
eeedd
ee...
ee...
```

这样我们就可以在保证每个块连续的情况下满足要求了,所以不管数据是什么，本题都一定有解。

问题 $2$：**如果到第 $d$ 行，第 $d$ 行的最后一个块结束点在右边怎么办？**

这个问题留到 part $3$ 进行解答。

## part $3$ 具体实现思路

①细节调整 $1$：如果 $b < d$ 则交换 $b$ 和 $d$，$a$ 和 $c$。**注意：最后输出要把整个图形左右颠倒！**

②把整个图形从中间分开，变成 $(a + c) \times d$ 和 $a \times (b - d)$ 的两个长方形。

③如果是奇数行，则从左到右，如果是偶数行，则从右到左。

④在对 $(a + c) \times d$ 这个长方形进行分块时，设置两个计数器：$k$ 和 $p$，分别代表现在到了第几个块，以及现在到了第 $k$ 个块的第几个格子。每到一个格子就把这个格子变为第 $k$ 个块的其中一个格子，同时 $p = p + 1$（占有格子数量加 $1$）。如果 $p = x_k$ 则 $k = k + 1$（进入下一个块）。

⑥细节调整 $2$ & part 2 问题解答：**如果到第 $d$ 行，第 $d$ 行的最后一个块结束点在右边怎么办？** 其实这个问题很好解决：你直接把$(a + c) \times d$ 这个长方形左右颠倒一下不就结束了？

## part $4$ 代码

```cpp
#include <iostream>
using namespace std;

int a, b, c, d, n, x[30], mp[105][105], mp2[105][105], ff = 0;

int main() {
	cin >> a >> b >> c >> d >> n;
	for(int i = 1; i <= n; i++) cin >> x[i];
	if(b < d) swap(b, d), swap(a, c), ff = 1;
	int k = 1, p = 0, flag = 0;
	for(int i = 1; i <= d; i++) {
		if(flag == 0) {
			for(int j = 1; j <= (a + c); j++) {
				mp[i][j] = k;
				p++;
				if(p == x[k]) p = 0, k++;
			}
		} else {
			for(int j = (a + c); j >= 1; j--) {
				mp[i][j] = k;
				p++;
				if(p == x[k]) p = 0, k++;
			}
		}
		flag = 1 - flag;
	}
	if(flag == 1) {
		for(int i = 1; i <= d; i++) {
			for(int j = 1; j <= (a + c); j++) {
				mp2[i][j] = mp[i][a + c - j + 1];
			}
			for(int j = 1; j <= (a + c); j++) {
				mp[i][j] = mp2[i][j];
			}
		}
		flag = 0;
	}
	for(int i = d + 1; i <= b; i++) {
		if(flag == 0) {
			for(int j = 1; j <= a; j++) {
				mp[i][j] = k;
				p++;
				if(p == x[k]) p = 0, k++;
			}
		} else {
			for(int j = a; j >= 1; j--) {
				mp[i][j] = k;
				p++;
				if(p == x[k]) p = 0, k++;
			}
		}
		flag = 1 - flag;
	}
	cout << "YES\n";
	if(ff == 0) {
		for(int i = 1; i <= b; i++) {
			for(int j = 1; j <= (a + c); j++) {
				if(mp[i][j] == 0) cout << ".";
				else cout << char(mp[i][j] + 'a' - 1);
			}
			cout << endl;
		}
	} else {
		for(int i = 1; i <= b; i++) {
			for(int j = (a + c); j >= 1; j--) {
				if(mp[i][j] == 0) cout << ".";
				else cout << char(mp[i][j] + 'a' - 1);
			}
			cout << endl;
		}
	}
}
```

---

## 作者：Union_Find (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF63D)

# First 题意

给你一个图形，它是由 $a \times b$ 和 $c \times d$ 的矩形拼接得到的，如下图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63D/d0dfe8fb20d3bd76651bd208632c7ccbf8e3af11.png)

其中，$a,c$ 共线。有 $n$ 个图形 $(n \le 26)$，它们的面积分别是 $x_1,x_2,\cdots,x_n$，现在将这几个图形拼成上图，求拼接方法。

# Second 思路

思路就是将这几个图形按照蛇形依次摆放，这样就可以保证不会断,所以一定有解。

但是，蛇形不能断，就需要判定奇偶性，详见代码注释。

# Third Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ll long long
ll a, b, c, d, n, s[305], mp[505][505], dir, xx, yy, bb[505][505];
bool flag = 0;
int main(){
	scanf ("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &s[i]);
	for (int i = 1; i <= b; i++)
		for (int j = 1; j <= a; j++)
			bb[i][j] = 1;
	for (int i = 1; i <= d; i++)
		for (int j = a + 1; j <= a + c; j++)
			bb[i][j] = 1;//标记是否可以放置图形 
	if (b > d){
		if (d & 1) xx = 1, yy = a + c, dir = -1;
		else xx = 1, yy = 1, dir = 1;
	}
	else{
		if (b & 1) xx = 1, yy = 1, dir = 1;
		else xx = 1, yy = a + c, dir = -1;
	}//判断奇偶性 
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= s[i]; j++){
			mp[xx][yy] = i;
			yy += dir;
			if (!bb[xx][yy]) xx++, yy -= dir, dir = -dir;
		}
	}//放置图形 
	puts("YES");
	for (int i = 1; i <= max(b, d); i++){
		for (int j = 1; j <= a + c; j++)
			if (!bb[i][j]) cout << '.';
			else cout << (char)(mp[i][j] + 'a' - 1);
		puts("");
	}//输出
	return 0;
}
```

---

