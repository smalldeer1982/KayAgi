# Santa Claus and Robot

## 题目描述

Santa Claus has Robot which lives on the infinite grid and can move along its lines. He can also, having a sequence of $ m $ points $ p_{1},p_{2},...,p_{m} $ with integer coordinates, do the following: denote its initial location by $ p_{0} $ . First, the robot will move from $ p_{0} $ to $ p_{1} $ along one of the shortest paths between them (please notice that since the robot moves only along the grid lines, there can be several shortest paths). Then, after it reaches $ p_{1} $ , it'll move to $ p_{2} $ , again, choosing one of the shortest ways, then to $ p_{3} $ , and so on, until he has visited all points in the given order. Some of the points in the sequence may coincide, in that case Robot will visit that point several times according to the sequence order.

While Santa was away, someone gave a sequence of points to Robot. This sequence is now lost, but Robot saved the protocol of its unit movements. Please, find the minimum possible length of the sequence.

## 说明/提示

The illustrations to the first three tests are given below.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/055feaa24aaf28c272b502eb1fa7804fe2ce0a51.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/795acf4da6085a8e5b976c179bfde9796711ae28.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/75228340b2ee205f332e39cf435e438e28662e9d.png)

The last example illustrates that each point in the sequence should be counted as many times as it is presented in the sequence.

## 样例 #1

### 输入

```
4
RURD
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
RRULDD
```

### 输出

```
2
```

## 样例 #3

### 输入

```
26
RRRULURURUULULLLDLDDRDRDLD
```

### 输出

```
7
```

## 样例 #4

### 输入

```
3
RLL
```

### 输出

```
2
```

## 样例 #5

### 输入

```
4
LRLR
```

### 输出

```
4
```

# 题解

## 作者：xxxr_2024 (赞：2)

# CF748C Santa Claus and Robot
水题，建议降橙。
## 分析
题目相当于给你一条路径，求最少的“转折点”。

很简单，用 $sum$ 统计转折点数量，只要你的方向转变了，$sum$ 就加一。那怎么判断方向转变呢？因为一直都是按最短路径走的，所以只要你的方向满足从向右变成向左，向上变成向下，以及向左变成向右，向下变成向上，就转变了一次方向。

详细实现请看代码。
## 实例代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    const int N = 105;
    bool vis[N];
    string str, s;
    int T, k, sum = 0;
    bool f(char a)
    {
        return ((a == 'L' && vis['R'] == 1) || (a == 'R' && vis['L'] == 1) || (a == 'U' && vis['D'] == 1) || (a == 'D' && vis['U'] == 1)) ? 1 : 0;
    }
    signed work()
    {
        cin >> T >> str;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < T; i++)
        {
            if (f(str[i]))
            {
                memset(vis, 0, sizeof(vis));
                sum++;
            }
            vis[str[i]] = 1;
        }
        cout << sum + 1 << endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：_xbn (赞：2)

可能有同学样例没看懂，我在这里解释一下。

来看第一个样例：

![](https://espresso.codeforces.com/832fb8f97a482be815e0f87edde26c9791a0d330.png)

我们把路径上每个按走的顺序标号（起点和终点也算）。

首先从 $1$ 走到 $2$，此时走的长度为$1$，一号点到二号点的最短路也为 $1$，所以不用把 $2$ 号点当做中转点。

接下来 $2$ 到 $3$，路径为 $1$，加上之前走的，总长为 $2$，长度与 $1$ 到 $3$ 的最短路相等，所以不用中转。

接下来 $3$ 到 $4$，路径为 $1$，加上之前走的，总长为 $3$，长度与 $1$ 到 $4$ 的最短路相等，所以不用中转。

接下来 $4$ 到 $5$，路径为 $1$，加上之前走的，总长为 $4$，这时长度与 $1$ 到 $5$ 的最短路不相等了，于是我们回到上一个点，把它作为一个中转点，这样就保证这个中转点到 $5$ 号点的距离右是最短路了。

最后一个点为停留的点，也算一个中转点，所以答案是 $2$。

可以发现，我们的做法就是根据样例模拟，当一个点到上一个中转点不是最短路时，我们可以把这个点的上一个点作为中转点，但还有一个问题，起点在哪？

由于起点在哪对答案并无影响，所以可以自己拟定一个起点。

那代码就非常好写了

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N];
char s[N];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int main()
{
    n = read(); cin >> (s + 1);
    int x = 0, y = 0, nx = 0, ny = 0;
    for (int i = 1; i <= n; i++)
    {
    	t++;
    	int tx = nx, ty = ny;
    	if(s[i] == 'U') nx = nx - 1; // up
		if(s[i] == 'D') nx = nx + 1; // down
		if(s[i] == 'L') ny = ny - 1;// left
		if(s[i] == 'R') ny = ny + 1;// right
		if(abs(nx - x) + abs(ny - y) != t)
		{
			ans++; x = tx; y = ty;
			t = 1;
		}
	}
	if(x != nx || y != ny) ans++;
	cout << ans << endl;
    return 0;
}
```


---

## 作者：ChenZQ (赞：1)

这道题其实可以按照贪心的做法来做。

先说求出平面两点的最短距离（不能走斜线的那种）：$| x_1 - x_2 | + | y_1 - y_2 |$。

接下来我们来说**贪心策略**：

首先我们将坐标 $(0,0)$ 设为起始点（设任意坐标都可以）。然后设 $tx$ 和 $ty$ 为上一个坐标，$nx$ 和 $ny$ 为当前坐标，$x$ 和 $y$ 为最后一个设立点的坐标。**如果发现当前点跟最后一个设立点的坐标所走过的路大于了他们两点之间的最短路**，就将这个坐标的上一个坐标新设一个点。

可能有人会问为什么是上一个坐标而不是当前坐标呢？

~~玄学~~因为当前坐标已和上一个点构不成最短距离，就不满足题意，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/xcozieal.png)

~~快踩爆这个蒟蒻，他连画图都这么丑。~~

我们当前已经遍历到最后一个下标了，我们发现，哎？这个下标怎么跟上一个点（黄色点）构成最短路了，那么我们应该是选择最后一个下标还是上一个下标呢。当然是上一个下标了，因为如果选的是最后一个点，那么上一个点和这个点构不成最短路，不符合要求。

思路部分都讲完了，接下来上代码。


### AC CODE
```
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int n, m, step;
char s[N];

int main()
{
    
    cin>>n>>s;
    int x = 0, y = 0, nx = 0, ny = 0;int ans=0;
    for(int i=0;i<n;i++)
    {
    	step++;
    	int tx=nx,ty=ny;
        if(s[i] == 'U') nx=nx-1;
        if(s[i] == 'D') nx=nx+1;
	if(s[i] == 'L') ny=ny-1;
	if(s[i] == 'R') ny=ny+1;
	if(abs(nx-x)+abs(ny-y)!=step)
	{
		ans++;x=tx;y=ty;
		step=1;
	}
    }
    if(x != nx || y != ny) ans++;
    printf("%d",ans);
}
```

创作不易，点个赞呗。

---

## 作者：Water_Cows (赞：1)

### Part 1 翻译

~~这个翻译够了吧。。。~~那我就解释第一组样例。

[![yM0l5j.png](https://s3.ax1x.com/2021/02/03/yM0l5j.png)](https://imgchr.com/i/yM0l5j)

从开始点 $p_1$ 出发，可以发现 $p_1 \to p_2$ 是最短路径。同理也可以发现 $p_2 \to p_3$ 也是最短路径。

有些人可能会问，一定是这 $3$ 个点吗？不一定，~~CF 那迷惑性行为您见得还少吗？~~。$p_2$ 可以放在 $p_4$。因为这样从出发点 $p_1 \to p_4$ 也是最短路径。

### Part 2 思路

可以发现，要从 一个点走到另一个点 且 这条路径是这两个点之间的最短路径，那这条路径不能有相反的方向。比如，一条 `LLU` 的路径是合法的，但是 `LRU` 是不合法的，因为走了回头路。

根据这个性质，我们可以发现：

- 有 `L` 就没有 `R`，反之亦然。
- 有 `U` 就没有 `D`，反之亦然。

那就可以愉快地写代码了。

### Part 3 代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N = 2e5 + 7;

int n, change[201], ans, vis[5];
char ch[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> ch[i];
    change['L'] = 1;
    change['U'] = 2;
    change['D'] = 3;
    change['R'] = 4;
    // 可以发现，“水火不容”的两个点相加和为5，就省去了冗长的判断。
    for(int i=1; i<=n; i++)
    {
        int x = change[ch[i]];
        if(vis[5 - x]) { // 如果发现与之对应的“水火不容”的点时，答案就+1
            ans++;
            vis[1] = vis[2] = vis[3] = vis[4] = 0;
            vis[x] = 1;
        }
        else vis[x] = 1;
    }
    cout << ++ans << '\n'; // 最后还有一条路径，记得把答案+1
}
```

---

## 作者：PR_CYJ (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF748C)
# 思路
简单模拟题。

题目给了一条路径，让求最少的转折点。因为两个转折点间要走最短路，所以可以可以按照题意模拟，每当遇到一个点，其与上一个点间的距离不等于走过的路时，就增加一个转折点。

由于题目中没有设置起点，所以随便找一个点作为起点即可。这里我选用了点 $(0,0)$ 作起点。

注意：**起点不算转折点，但终点算。**
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,sum,ltx,lty,nwx,nwy;
map<char,int> dx,dy;
int main()
{
	dx['U']=-1;
	dy['U']=0;
	dx['D']=1;
	dy['D']=0;
	dx['L']=0;
	dy['L']=-1;
	dx['R']=0;
	dy['R']=1;
	//注意方向数组的初始化 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char c;
		cin>>c;
		nwx+=dx[c];
		nwy+=dy[c];
		s++;
		if (abs(nwx-ltx)+abs(nwy-lty)!=s)
		{
			sum++;
			s=1;
			ltx=nwx-dx[c];
			lty=nwy-dy[c];
		}
	}
	cout<<++sum<<"\n";//终点也要算一个转折点 
}
```

---

## 作者：xzz_0611 (赞：0)

[洛谷题目传送门](/problem/CF748C)  
[CF 题目传送门](https://codeforces.com/problemset/problem/748/C)

难度不高，建议降橙。
### 题目大意
有一个机器人在网格上行走，它会沿着网格的线移动，求它最少要沿着最短路径到达几个点才能行完所有路程。
### 思路
最少的话就要让每条最短路径尽可能长，但由于路径是最短的，所以在每条路径中不能出现相反的行走路线，所以在每一个最短路径中，不可能同时出先 `L` 或 `R`、`U` 或 `D`。

可以对机器人每次行走的方向进行判断，如果出现了相反方向，就将答案加 $1$，并清空之前走的方向，反之则继续判断。
### Code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
bool vis[4];//储存已出现的行走方向
bool chk(char ch) {//判断是否有相反方向
	return (ch=='R'&&vis[2])||(ch=='U'&&vis[3])||(ch=='L'&&vis[0])||(ch=='D'&&vis[1]);
}
void visit(char ch) {//添加方向
	if(ch=='R') vis[0]=true;
	else if(ch=='U') vis[1]=true;
	else if(ch=='L') vis[2]=true;
	else vis[3]=true;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,ans=1;//答案初始要为1
	string str;
	cin>>n>>str;
	for(int i=0;i<n;++i) {
		if(chk(str[i])) {//如果有相反的
			++ans;
			memset(vis,false,sizeof(vis));//清空之前的数据
		}
		visit(str[i]);//添加这个方向
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Lan_yan (赞：0)

首先说明一下：

R 是 right，L 是 left，U 是 up，D 是 down。自己也可以对应一下样例图像。

## 思考

一般来说，你如果要走最短路，是不会走回头路的。

回头路在这里定义为：你曾经往左走过，现在往右，曾经往右走过，现在往左。上下同理。

机器人也一样。

那么，为什么在这题的样例里有“回头路”呢？

因为有多个点嘛。

那么，我们可以理解为：出现一个“回头路”时，**你就是要走新的路了**，也就是有新的点了。

所以，问题就转化为求有多少个“回头路”。

## 代码实现

```cpp
#include<bits/stdc++.h>//人见人爱的万能头
using namespace std;
int n,ans=0,p[5]={0};
char x;
int main()
{
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		cin>>x;//一步一步考虑
		int lan;
		if(x=='R')lan=0;//右
		if(x=='L')lan=3;//左
		if(x=='U')lan=1;//上
		if(x=='D')lan=2;//下
		if(p[3-lan]>0)//走回头路的情况
		{
			ans++;p[0]=0;p[1]=0;p[2]=0;p[3]=0;//走新的路当然要归零啦
		}
		p[lan]++;//每一次走的路记录下来
	}
	printf("%d",ans+1);//还有一个被遗忘的终点
	return 0;
}
```

完结撒花！

---

## 作者：nxd_oxm (赞：0)

# 题意
题目说有一串字符串 $s$，表示一个机器人在无限大的网格上行走的路线。`L` 代表左，`R` 代表右，`U` 代表上，`D` 代表下。

这个网格上呢有一些格点。现在题目告诉我们这个机器人走的都是这些点之间的最短路径，让我们求点的最小个数。

# 思路
贪心。

因为机器人走的是格点之间的最短路径，所以在两个点之间他只能向一个方向走（左上，左下，右上，右下）。（即两点构成了长方形，最短路径即是长加宽）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vv1sc71h.png)

所以在当前如果是同一方向就继往后搜，遇到变向就说明有下一个点。

### 样例

### 输入 #1

```
6
RRULDD
```

### 输出 #1

```
2
```

分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/tbqemu3g.png)

注意到这个答案是 $2$。因为起点是不算在里面的！

## Ac code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int n;
string a;
char ud=0,lr=0;
int sum=1;
signed main(){
	cin>>n>>a;
	f(i,0,n-1){
		if(a[i]=='U'||a[i]=='D'){
			if(a[i]!=ud){
				if(ud==0){
					ud=a[i];
					continue;
				}
				sum++;
				ud=a[i];
				lr=0;
			}
		}else{
			if(a[i]!=lr){
				if(lr==0){
					lr=a[i];
					continue;
				}
				sum++;
				lr=a[i];
				ud=0;
			}
		}
	}
	cout<<sum;
	return 0;
}

```

---

## 作者：tallnut (赞：0)

简单构造题。
# 思路
我们先想想“最短路径”需要满足什么条件。如果机器人在两个点之间的路径上，既向上移了，又向下移了，那么相当于走了回头路，显然不是最短路径。向左和向右同理。

于是代码就很好写了。把字符串扫一遍，判断每一个字符是否与前面的发生冲突，如果冲突了就更新答案，然后清空标记数组（因为到了一个新的点，一切重来）。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/138406591)。
```
#include <iostream>
#include <cstring>
using namespace std;
int n,ans;
string s;
bool visited[100];
bool error(char c) { return ((c == 'L' && visited['R']) || (c == 'R' && visited['L']) || (c == 'U' && visited['D']) || (c == 'D' && visited['U'])); }
int main()
{
	cin >> n >> s;
	for (int i = 0;i < s.size();i++)
	{
		if (error(s[i]))
		{
			ans++;
			memset(visited,0,sizeof visited);
		}
		visited[s[i]] = true;
	}
	cout << ans + 1;
}
```

---

## 作者：filletoto (赞：0)

## 思路
定义变量 $ans$ 存储答案。

再定义数组 $vis$，每次进行一个行走操作就将 $vis$ 数组中对应下标赋值为 $1$，并且判断机器人是否走过与当前命令相反的方向，即 $vis$ 数组中下标为当前命令相反方向是否等于 $1$。

如果等于 $1$，则 $ans+1$，并将 $vis$ 数组全部变为 $0$。

注意输出时 $ans$ 要加 $1$。

## 代码
```cpp
#include <iostream>
using namespace std;
int n,vis[200],ans;
char ch;
inline bool check(char c)
//vis数组中下标为当前命令相反方向是否等于1。
{
	if((c=='L'&&vis['R'])||(c=='R'&&vis['L'])||(c=='U'&&vis['D'])||(c=='D'&&vis['U'])) return true;
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		if(check(ch))
		{
			ans++;
			vis['L']=vis['R']=vis['U']=vis['D']=0;//将vis数组变为0	
		}
		vis[ch]=1;
	}
	cout << ans+1 << endl;



	return 0;
}
```

---

## 作者：WaterSky (赞：0)

[用来凑字数的题目传送门：Santa Claus and Robot。](com.cn/problem/CF748C)

## Part 1：题目翻译。
这个翻译令人满意。但是要注意一点：在翻译中并没有写 ```RULD``` 到底对应上下左右哪一个，这四个字母分别对于右上左下。

## Part 2：题目算法分析。
这道题是为了寻找一个机器人用最短路径到达一定个数的点数，已经给出机器人路径，输出最少有多少必定经过的点。

由于数据大小：$ 1 \leq n \leq 2·10^{5} $。所以第一个想出的是贪心。

那么要怎么“贪”呢？题目说明这个机器人一定走的是最短路径，如果目前来看不是的话，那么就说明这一个必定经过的地点到目前下一个中间还隔了一个必定经过的地点。这样一分析，我们所要达到的目标由最开始的转变成了找到有多少个非最短路径。

那么怎么判断呢？对于每一步，由于我们对下一个目标不确定，所以我们只能通过目前与之前来判断，那么~~我目前只能想到的~~就只有“走回头路”。我们可以用两个变量来记录目前自己的上下和左右的方向，如果目前的与之前的相矛盾，那么就说明这个地点有一个必定经过的点，答案更新。

## Part 3：代码。
```
#include <bits/stdc++.h>
using namespace std; 
long long n,ans;
char x=' ',y=' ';
string a;
int main() 
{
   	cin>>n>>a;
   	for(int i=0;i<a.size();i++)
   	{
		if(a[i]=='R' || a[i]=='L')
			if(x==' ' || x==a[i]) x=a[i];
            //如果目前的方向与之前的不矛盾，那么不变。
            //特殊的，如果之前这个方向不确定，那么我们就可以明确目标，将 x 赋值。
			else  x=a[i],y=' ',ans++;   
            //否则，更新这个方向的路线，然后将另一个方向转化为不确定，记得答案增加。
		else
			if(y==' ' || y==a[i]) y=a[i];
			else  y=a[i],x=' ',ans++;  	
            //同上
	}
	cout<<ans+1;
    return 0;
} 
```

---

## 作者：RBI_GL (赞：0)

### 题意：

机器人在网格线上行走，从 $p1$ 点开始，沿最短路径到 $p2$，再沿最短路径到 $p3$，依此类推。在此过程中留下了行走的运动轨迹，用 ```RULD``` 表示。若只给出运动轨迹，求最少的 $pi$ 点的个数。


### 思路：

$pi$ 到 $pi+1$ 是沿最短路径走的，因此在此路径中不可能同时出现 $UD$ 或 $LR$ 两个方向。因此只要同时出现，那一定证明此刻已往下一个目标点走。

用四个方向的标记分别记录，然后对于每个点后都要初始化标记的值。

### $Code$：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char a[200005];
map<char,int> mp;
int vis[5];
int ans=1;
bool judge(int x) {
	if(x==0 && vis[1]) return true;
	if(x==1 && vis[0]) return true;
	if(x==2 && vis[3]) return true;
	if(x==3 && vis[2]) return true;
	return false;
}
int main() {
	mp['L']=0;
	mp['R']=1;
	mp['U']=2;
	mp['D']=3;
	while(scanf("%d",&n)==1) {
		scanf("%s",a);
		ans=1;
		memset(vis,0,sizeof(vis));
		for(int i=0; i<n; i++) {
			int tmp=mp[a[i]];
			if(judge(tmp)) {
				memset(vis,0,sizeof(vis));
				ans++; 
			}
			vis[tmp]=1;
		}
		printf("%d\n",ans);
		return 0;
	}
	return 0;
}
```

---

