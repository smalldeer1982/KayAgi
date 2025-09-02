# [COCI 2017/2018 #7] Clickbait

## 题目描述

在上网的时候，Slavko遇到了一个广告，这个广告上面有一个由容器和管道组成的系统（如图是一个系统的例子）和一行字：“如果往编号为1的容器里注水，请确定这些容器被注满水的顺序。”
这个系统包含K个编号为1到K的容器，并且我们可以用一个N×M的矩阵来描述它。**这些容器的形状为长方形**。容器和管道的轮廓将用这些字符表示：
- 如果字符为‘-’，那么这个位置是容器和管道的轮廓的水平部分。
- 如果字符为‘|’，那么这个位置是容器和管道的轮廓的垂直部分。
- 如果字符为‘+’，那么这个位置同时是容器和管道的轮廓的水平和垂直部分。（即容器的四个角，管道的拐弯部分），一个例外是容器与管道的相交部分，在这个位置不使用+。
在每一个容器内的某个位置内，都存在一个表示这个容器编号的数字串。矩阵内既不是容器和管道的轮廓，又不是表示容器编号的数字串的位置上的字符为'.'。
除了编号为1的容器以外，所有的容器的**顶部都接入且只接入了一条可以使水进入容器的**管道。编号为1的容器的顶部没有管道。
每个容器的**侧面**可以接入多条（也可以没有）可以使水流出容器的管道。**没有两个可以使水流出容器的管道与容器的连接处在同一个高度。**
管道必须有方向的连接两个容器，这也就意味着一条管道**不能**在某些地方分成两条管道，或是两条管道交汇成一条管道，并且没有两条管道会相交。并且管道永远不会向上拐弯，所以可以保证管道里的水可以正常的向下流动并且流入对应接入的容器里。
水只能进入没有被装满水的容器。如果一个容器中的水位达到了可以使水流出的管道的高度，水将会流入这个管道的另一端所接入的容器里，直到那个容器满了为止。
请帮助Slavko确定这些容器被注满水的顺序。
**请注意：**
- 在矩阵中，每一个字符'+'都**有且仅有一个**'-'字符在其左边或右边与其相邻，并且**有且仅有一个**'|'字符在其上边或下边与其相邻。其余的与其相邻的字符将均为'.'。
- 在字符矩阵中，管道与容器轮廓相邻的唯一可能的位置是管道与容器连接的位置。换句话说，除了管道与容器连接的情况，管道不可能与容器相邻。在与容器连接的位置，管道使水流入容器的一端用'|'标识，使水流出容器的一端用'-'标识。

## 样例 #1

### 输入

```
12 13
..+--+.......
+-|..|.......
|.|.1|--+....
|.+--+..|....
|......+----+
+---+..|..2.|
....|..+----+
.+--+........
.|...........
+---+........
|.3.|........
+---+........```

### 输出

```
2
3
1```

## 样例 #2

### 输入

```
8 10
..........
.......+-+
...+---|1|
...|...+-+
...|......
..+-+.....
..|2|.....
..+-+.....
```

### 输出

```
2
1```

# 题解

## 作者：O2人 (赞：10)

我发现，我现在在你谷发声（影响力大的）的唯一方式只有发题解了。

这是我初中三年第二次被你谷禁言，在一年的沉寂之后，我又在你谷上发声了，然而好景不长，我又被禁言了。

好了不扯了，看看这题吧。

###  _因为不可能有两个横着的管子插在同一行，所以这题就很好模拟了。_ 

 _**步骤：**_ 
	
 1.我们先暴力找到第一个箱子。
 
 2.然后再从下往上枚举水位，一旦发现这一行有管子连着，就马上顺这管子下去,到达箱子x。

3.对x重复2操作

4.如果没管子了，就输出此时编号

## **所以肯定DFS**

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch>='0'&&ch<='9') ret=(ret<<3)+(ret<<1)+ch-'0',ch=getchar();
	return ret*f;
}
const int maxn=1005,flg[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m;
char A[maxn][maxn];
void DFS(int u,int x,int y){
	int L=0,H=0;
	while (A[x][y]!='+') y--;
	while (A[x+L+1][y]!='+') ++L;L+=2;
	while (A[x][y+H+1]!='+') ++H;H+=2;//算箱子宽度和高度
	for (int i=x;i<=x+L-1&&!u;i++)
	for (int j=y;j<=y+H-1&&!u;j++)
	if (A[i][j]>='0'&&A[i][j]<='9'){//找编号
		char ch=A[i][j];
		while (ch>='0'&&ch<='9') u=(u<<3)+(u<<1)+ch-'0',ch=A[i][++j];//类似快读的操作
		break;
	}
	for (int i=x+L-2;i>=x-1;i--)//枚举水位，并遍历
	if (A[i][y-1]=='-'||A[i][y+H]=='-'){
		int nx=i,ny,f;//f是方向，0，1，2，3具体代表什么方向看flg数组
		if (A[i][y-1]=='-') ny=y-1,f=3;
		else ny=y+H,f=1;
		while (true){
			nx+=flg[f][0],ny+=flg[f][1];
			if (A[nx][ny]=='+'){
				if ((f==0||f==2)&&A[nx][ny-1]!='.') f=3;else
				if ((f==0||f==2)&&A[nx][ny+1]!='.') f=1;else
				if ((f==1||f==3)&&A[nx+1][ny]!='.') f=2;//判断管子是否换方向
			}else
			if (A[nx-flg[f][0]][ny-flg[f][1]]=='|'&&A[nx][ny]=='-') break;//判断是否走到水箱上了
		}
		DFS(0,nx,ny);//继续走
	}
	printf("%d\n",u);
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) scanf("%s",A[i]+1);
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
	if (A[i][j]=='+'){DFS(1,i,j);return 0;}//第一个箱子肯定在最上面，因为'+'上不能插管子
	return 0;
}
```


---

## 作者：Engulf (赞：2)

每个水箱只会有一个水管连向它自己，说明把水箱抽象出来之后就是一棵树，对于一个水箱，由下至上，遇到一个水管就连边，这样对树后序遍历就是答案了。

接下来是实现部分的详解：
- 先找到数字，然后开始 flood fill，将整个水箱范围找出来（左下角和右上角），并把这范围内的权值都设为那个编号。
- 对于每个水箱，从下至上地找水管。如果发现了一个水管，就开始 dfs，沿着水管走，走到水箱顶后就获取走到的水箱的编号，连边。
- 最后后序遍历整棵树即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1005, M = N * N / 9;

int n, m;

char a[N][N];
bool vis[N][N];

int sx[M], sy[M], ex[M], ey[M];

int num[N][N];

void tank(int x, int y, int c) {
    if (x < 1 || x > n || y < 1 || y > m) return;
    if (vis[x][y]) return;
    if (a[x][y] == '+' || a[x][y] == '|' || a[x][y] == '-') return;
    sx[c] = min(sx[c], x - 1);
    sy[c] = min(sy[c], y - 1);
    ex[c] = max(ex[c], x + 1);
    ey[c] = max(ey[c], y + 1);
    vis[x][y] = 1;
    num[x][y] = c;
    static int dir[][2] = {1, 0, 0, 1, -1, 0, 0, -1};

    for (int k = 0; k < 4; k++) {
        int nx = x + dir[k][0], ny = y + dir[k][1];
        tank(nx, ny, c);
    }
}

int tube(int x, int y, char fr, int fx, int fy) {
    if (x < 1 || x > n || y < 1 || y > m) return 0;
    // if (x == 4 && y == 9) debug("fr: %c, cur: %c\n", fr, a[x][y]);
    if (fr == '|' && a[x][y] == '-') {
        // debug("we're at (%d, %d)\n", x, y);
        return num[x + 1][y];
    }

    char cur = a[x][y];
    a[x][y] = 'a';

    static int dir[][2] = {1, 0, 0, 1, -1, 0, 0, -1};

    for (int k = 0; k < 4; k++) {
        int nx = x + dir[k][0], ny = y + dir[k][1];
        if ((a[nx][ny] == '+' || a[nx][ny] == '|' || a[nx][ny] == '-') && !(nx == fx && ny == fy)) {
            // debug("(%d, %d) -> (%d, %d)\n", x, y, nx, ny);
            return tube(nx, ny, cur, x, y);
        }
    }
    return 0;
}

vector<int> g[M];

void dfs(int u) {
    for (auto v: g[u])
        dfs(v);
    cout << u << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i] + 1;

    memset(sx, 0x3f, sizeof sx);
    memset(sy, 0x3f, sizeof sy);

    int tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (!vis[i][j] && isdigit(a[i][j])) {
                int s = a[i][j] - '0';
                while (j + 1 <= m && isdigit(a[i][j + 1])) s = s * 10 + a[i][++j] - '0';
                tot = max(tot, s);
                tank(i, j, s);
            }
        }

    // for (int i = 1; i <= tot; i++) {
    //     debug("(%d, %d) to (%d, %d)\n", sx[i], sy[i], ex[i], ey[i]);
    // }

    // for (int i = 1; i <= n; i++, debug("\n"))
    //     for (int j = 1; j <= m; j++)
    //         debug("%c", a[i][j]);

    for (int i = 1; i <= tot; i++) {
        for (int j = ex[i]; j >= sx[i]; j--) {
            if (a[j][sy[i] - 1] == '-') {
                // debug("start at (%d, %d)\n", j, sy[i] - 1);
                int to = tube(j, sy[i] - 1, 'a', j, sy[i]);
                g[i].emplace_back(to);
                // debug("%d -> %d\n", i, to);
            } else if (a[j][ey[i] + 1] == '-') {
                // debug("start at (%d, %d)\n", j, ey[i] + 1);
                int to = tube(j, ey[i] + 1, 'a', j, ey[i]);
                g[i].emplace_back(to);
                // debug("%d -> %d\n", i, to);
            }
        }
    }

    dfs(1);

    return 0;
}
```

---

## 作者：matrixPower (赞：2)

[传送门](https://www.luogu.com.cn/problem/P5053)

哎呀，其实是一道很~~水~~的深搜啦。

1. 先暴力找到第一个箱子。

2. 从上往下查找，若这个水位有管子连通，就沿着这个管子走。

3. 如果此时此刻没有管子啦，输出此时的编号，并结束程序。

4. 重复操作 2。

---

## 作者：封禁用户 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P5053)
## 思路
读完题可以发现，这是一道深搜题。

只需要几个简单的操作就可以了。

### Sol:
先找到一个容器，继续搜索，如果上面或下面有水管，沿着水管走。如果没有路了，输出编号。多次重复步骤。

因为没有水管会向上，没有相交的水管，所以只要安照步骤做就能过了。

## 核心伪代码
```cpp
	for(/*x ~ x+len1-1并且id为0*/){
	  	for(/*y ~ y+len2-1并且id为0*/){
	    	if(/*是数字*/){
	    		char ch=mapn[i][j];
	    		while(/*是数字*/){
				    //算箱子的编号 
			        //往右搜索数字 
		 	   	}
		    	break; 
			}
		}
	}	
	for(/*x+len1-2 ~ x-1*/){
	  	if(/*i,y+1或i,y+len2是"-"*/){
	      	int px=i,py,ndc;
		  	if(/*是"-"*/) py=y-1,ndc=3;
		  	else{
		    	py=y+h,ndc=1;
		    	while(1){
		  	    	//改变方向 
		  	    	if(/*是"+"*/){
		  	  	 	    //向下，上，右 
			    	}
			    	else if //又遇到了容器 
		    	} 
			}
		   dfs(px,py,0);
	  	} 
		printf("%d\n",id);
	}
}
```

---

## 作者：Erica_N_Contina (赞：1)

# [COCI2017-2018#7] Clickbait
## 简明题意

有一个由容器和管道组成的系统（直接读入图形），如果往编号为 $1$ 的容器里注水，请确定这些容器被注满水的顺序。

除了编号为 $1$ 的容器以外，所有的容器的顶部都接入且只接入了一条可以使水进入容器的管道。

没有两条管道会相交，管道永远不会向上拐弯。

水流满足物理学规律。




## 思路

看到题目第一眼：呀我懵了，第二眼：呀**大模拟**。

我们忽略题目，直接看看样例：

```Plain Text
12 13
..+--+.......
+-|..|.......
|.|.1|--+....
|.+--+..|....
|......+----+
+---+..|..2.|
....|..+----+
.+--+........
.|...........
+---+........
|.3.|........
+---+........
```


![image.png](https://img1.imgtp.com/2023/07/30/ZKv9ZEWw.png)

画出来就是这样的，红色的是水箱，绿色的是水管。

在输入的时候记录第一个水箱的位置，然后在输入完后从第一个水箱的位置进入 **dfs**。

每当我们进入一个水箱，我们就从下往上扫描水箱的出口（即出了水进来的那个水管还有没有别的水管），扫描到一个就进去，沿着水管一直走，知道到达一个新的水箱，然后我们进入一个新的 dfs。

那么怎么样判断是否到了一个新的水箱呢？

我们发现在水管弯折的地方有一个 `+` 号（即如果是水管，则在两个方向不同的水管之间会有 `+` 号连接），但是如果是水管与水箱壁之间，则不会有 `+` 号连接，而是两个方向不同的水管靠在要求（即 `-` 和 `|` 靠在一起）。当我们遇到这种情况时，我们就知道我们到了一个新水箱了。

对于其他的，没什么技巧，直接枚举就行了。dfs 的每一步见代码里的注释。

相信本题的时间复杂度，即使最差，那也就是 $O(n^2)$ 罢了。

## Code

```C++
#include <bits/stdc++.h>
using namespace std;

const int N=1005;
int dxdy[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//方向增量数组
int n,m;
char a[N][N];

void dfs(int u,int x,int y){
	int lon=0,hei=0;//记录当前水箱的宽高
	
	/////////计算水箱的宽高//////////
	while (a[x][y]!='+') y--;
	while (a[x+lon+1][y]!='+') ++lon;
	lon+=2;//加上两边的加号
	while (a[x][y+hei+1]!='+') ++hei;
	hei+=2;
	
	//////////找编号//////////
	for (int i=x;i<=x+lon-1&&!u;i++)
		for (int j=y;j<=y+hei-1&&!u;j++)
			if (a[i][j]>='0'&&a[i][j]<='9'){
				char tmp=a[i][j];
				while (tmp>='0'&&tmp<='9'){
					u=u*10+tmp-'0';
					tmp=a[i][++j];//读入编号,因为编号不一定是一位数
				}
			break;
			}
	
	//////////找出口//////////
	for (int i=x+lon-2;i>=x-1;i--)//从下往上逐层扫描
		if (a[i][y-1]=='-'||a[i][y+hei]=='-'){//出口的位置是固定的,要么是y-1,要么是y+hei
			int nowx=i,nowy,flg;//flg标记方向,对应dxdy数组
			if (a[i][y-1]=='-')nowy=y-1,flg=3;
			else nowy=y+hei,flg=1;
			while(1){//一直走,直到走到新的水箱
				nowx+=dxdy[flg][0],nowy+=dxdy[flg][1];
				if (a[nowx][nowy]=='+'){//要拐弯了
					if ((flg==0||flg==2)&&a[nowx][nowy-1]!='.') flg=3;
					else if ((flg==0||flg==2)&&a[nowx][nowy+1]!='.') flg=1;
					else if ((flg==1||flg==3)&&a[nowx+1][nowy]!='.') flg=2;//判断水管是否换方向
				}else if (a[nowx-dxdy[flg][0]][nowy-dxdy[flg][1]]=='|'&&a[nowx][nowy]=='-') break;//判断是否走到新的水箱
			}
			dfs(0,nowx,nowy);//继续走
		}
	
    //////////输出编号//////////
	//找完所有的出口,这个水箱的水没办法继续流出去了,就会被填满,输出这个水箱的编号
	printf("%d\n",u);
}
int main(){
	int si,sj;
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='+'&&si==0)si=i,sj=j;//记录第一个水箱的右上角的+的坐标
		}
	dfs(1,si,sj);//dfs入口坐标是每个水箱的右上角的+的坐标
	return 0;
}
```




---

## 作者：Genius_Star (赞：1)

### 思路：
第一眼看题没懂，感觉好怕怕。

后来再看，就是个大模拟（~~写完还挺有成就感~~）。

首先，我们需要找到第一个容器，即编号为 $1$ 的容器。我们可以从矩阵的第一行开始，逐个遍历每个字符，一旦遇到一个字符为数字 $1$ 的位置，即找到了第一个容器。

然后，我们从下往上枚举水位。

对于每个水位，我们从第一个容器开始，通过管道将水流动到下一个容器，直到无法流动为止。

为了确定水是否能够流动到下一个容器，我们需要检查当前水位所在行的每个字符。

如果字符为 ``|``，表示水可以流动到下一行，并且我们需要找到连接到当前容器的管道的另一端所连接的容器。

一旦找到下一个容器，我们更新当前容器的编号，并继续向下流动水。

如果当前行没有 ``|`` 字符，表示水已经无法继续流动，我们输出当前容器的编号。

重复以上步骤，直到所有的容器都被注满水为止。

### 代码实现：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1005;

int n,m;
char mp[N][N];
int be[N][N];

struct con{
    int l,r,u,d;
}d[N*N];
int k;

void get_con(int x,int y,int id){
    int i=x,j=y;
    while(mp[i][j]!='|') j--; d[id].l=j;
    j=y;
    while(mp[i][j]!='|') j++; d[id].r=j;
    j=y;
    while(mp[i][j]!='-') i--; d[id].u=i;
    i=x;
    while(mp[i][j]!='-') i++; d[id].d=i;
    for(j=d[id].l;j<=d[id].r;j++) be[d[id].u][j]=id;
}

int find(int x,int y,int dir){
    while(!be[x][y]){
        if(mp[x][y]=='-'){
            if(dir==3) y--;
            else y++;
        }
        else if(mp[x][y]=='|') {
            if(dir==0) x--;
            else x++;
        }
        else{
            if(dir==3 || dir==1){
                if(x>0 && mp[x-1][y]=='|') x--,dir=0;
                else x++,dir=2;
            }
            else{
                if(y>0 && mp[x][y-1]=='-') y--,dir=3;
                else y++,dir=1;
            }
        }
    }
    return be[x][y];
}
void dfs(int u){
    int v;
    for(int i=d[u].d;i>=d[u].u;i--){
        v=0;
        if(d[u].l>0 && mp[i][d[u].l-1]=='-') v=find(i,d[u].l-1,3);
        if(d[u].r<m-1 && mp[i][d[u].r+1]=='-') v=find(i,d[u].r+1,1);
        if(v) dfs(v);
    }
    printf("%d\n",u);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",mp[i]);
    
    //find con
    int x;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            if(!isdigit(mp[i][j])) continue;
            x=mp[i][j] -'0';
            while(j+1<m && isdigit(mp[i][j+1])) x=x*10+mp[i][++j]-'0';
            k=max(k,x);
            get_con(i,j,x);
        }
    
    dfs(1);
    
    return 0;
}

```

---

## 作者：HeCao2008 (赞：1)

## 题目思路

这道题题面非常长，但是仔细读就会发现实际上告诉的就是输入每个字符代表着什么，都是哪个部分，非常好理解~~虽然我理解了很久~~。

一般这种题目已经告诉怎么做的，都是先按着题目所描述的纯模拟，然后在考虑别的算法，然而这道题可以**纯模拟**。

读题不难发现这道题和箱子有密切的关联，而且是从第一个箱子开始漏的，所以程序第一步就是要找出第一个箱子
仔细想一下，因为箱子上面是不可能叠着箱子的，所以只要从第一行开始暴力搜索，搜索到 + 就代表找到了箱子的拐角
水是从下往上慢慢升高的，所以只需要暴力模拟到有管道的那一层，就继续顺着搜索。

一旦搜索到箱子，就重复和第一个箱子一样的操作，继续一层一层搜索下去，直到装满了，回溯。

最后考虑特殊情况：最不想碰到的情况当然是箱子中某一层有两根管道延伸出去，当然题目告诉你这不可能所以暴搜就好了。


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int direction[4][2]={{-1,0},{0,1},{1,0},{0,-1}}; //数组名已经很明显了，就是左上右下四个方向 
char c[1001][1001];
int n,m;
void dfs(int x,int y,int id){
	int len=0,height=0;
	while(c[x][y]!='+')y--;
	while(c[x+len+1][y]!='+')len++;
	  len+=2; // 不要忘，加号还没算 
	while(c[x][y+height+1]!='+')height++;
	 height+=2; // 不要忘，加号还没算
	for(int i=x;i<=x+len-1&&!id;i++)
	  for(int j=y;j<=y+height-1&&!id;j++)
	    if(c[i][j]>='0'&&c[i][j]<='9'){
	    	char cc=c[i][j];
	    	while(cc>='0'&&cc<='9'){
			    id=id*10+cc-'0'; //与快读读入数字差不多，然而这里是算箱子的编号 
		        cc=c[i][++j]; //快读是继续读入，这里也是继续往右搜索数字 
		    }
		    break; 
		}
	for(int i=x+len-2;i>=x-1;i--) //枚举水
	  if(c[i][y-1]=='-'||c[i][y+height]=='-'){ //枚举到了
	      int prex=i,prey,nowdirection;
		  if(c[i][y-1]=='-')
		    prey=y-1,nowdirection=3;
		  else
		    prey=y+height,nowdirection=1;
		    while(1){
		  	    prex+=direction[nowdirection][0];
		  	    prey+=direction[nowdirection][1];
		  	    if(c[prex][prey]=='+'){
		  	  	    if((nowdirection==0||nowdirection==2)&&c[prex][prey-1]!='.')
					  nowdirection=3; //向下枚举
					else if((nowdirection==0||nowdirection==2)&&c[prex][prey+1]!='.')
					  nowdirection=1; //向上枚举 
					else if((nowdirection==1||nowdirection==3)&&c[prex+1][prey]!='.')
					  nowdirection=2; //向右枚举 
			    }
			    else if(c[prex-direction[nowdirection][0]][prey-direction[nowdirection][1]]=='|'&&c[prex][prey]=='-')break; //判断是否又遇到了容器 
		    } 
		   dfs(prex,prey,0); //搜索 
	  } 
	  cout<<id<<endl;
}
int main(){
	freopen("clickbait.in","r",stdin);
	freopen("clickbait.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%s",c[i]+1); //读入字符串基本操作
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++) //暴力搜索，找到第一个箱子 
	    if(c[i][j]=='+'){
	    	dfs(i,j,1);  
	    	return 0; //找到了就可以完事了 
		} 
	return 0; //主程序就这些 
}
```


## 结语

很多 DFS （比如说这题）实际上都是模拟，比较考代码，所以做这种题的时候要仔细，写错一个字就等于一个字没写。

**谢谢大家的阅读**

---

## 作者：jackzhangcn2013 (赞：0)

# 题目大意

现在有很多容器竖着挂在墙壁上，有许多管道连接它们。最开始往容器里注水，求容器注满的顺序。

# 解法

手模样例，我们发现水位从下到上，每遇到一根管道就会往管道连接的容器注水，直到注满为止。

于是就可以采用 DFS 算法进行模拟。

对于每个容器，遍历水位从下到上，判断两边是否有管道连接，如果有就沿着管道走，走到新容器后重复本步骤。

题目比较人性化的一点在于同一水位不会有两根管道连接，这样就不需要~~用作者极度匮乏的科学知识~~考虑特殊情况了。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1005;
const int Mod = 1e9 + 7;
using namespace std;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int n, m;
char a[N][N];
inline pair<int, int> getHW(int x, int y) // 获取高和长
{
    int h = 1, w = 1; // h：高 w：长
    while (a[x + h][y] != '+')
    {
        h++;
    }
    while (a[x][y + w] != '+')
    {
        w++;
    }
    w++, h++;
    return {h, w};
}
inline int getId(int x, int y, int h, int w) // 获取当前容器编号
{
    for (int i = x; i <= x + h - 1; i++)
    {
        for (int j = y; j <= y + w - 1; j++)
        {
            if (a[i][j] >= '0' && a[i][j] <= '9')
            {
                string str;
                while (a[i][j] >= '0' && a[i][j] <= '9')
                {
                    str += a[i][j];
                    j++;
                }
                return stoi(str);
            }
        }
    }
    return -1;
}
void dfs(int u, int x, int y) // 箱子编号为 u，(x, y) 是容器边框上第一行的点
{

    while (a[x][y] != '+') // 将 (x, y) 移至容器左上角
    {
        y--;
    }
    auto [h, w] = getHW(x, y);
    u = getId(x, y, h, w);
    for (int i = x + h - 2; i >= x - 1; i--) // 从下往上加水
    {
        if (a[i][y - 1] == '-' || a[i][y + w] == '-') // 左右有管道连接
        {
            int nx = i, ny, dir;
            if (a[i][y - 1] == '-') // 左
            {
                ny = y - 1, dir = 3;
            }
            else // 右
            {
                ny = y + w, dir = 1;
            }
            while (true)
            {
                nx += dx[dir], ny += dy[dir];
                if (a[nx][ny] == '+') // 来到转折处
                {
                    if (dir % 2) // 横着，只能往下
                    {
                        dir = 2;
                    }
                    else // 竖着，左右都有可能
                    {
                        if (a[nx][ny - 1] == '-') // 左
                        {
                            dir = 3;
                        }
                        else if (a[nx][ny + 1] == '-') // 右
                        {
                            dir = 1;
                        }
                    }
                }
                else if (a[nx - dx[dir]][ny - dy[dir]] == '|' && a[nx][ny] == '-') // 碰到容器
                {
                    break;
                }
            }
            dfs(0, nx, ny);
        }
    }
    cout << u << endl;
}
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] == '+')
            {
                dfs(0, i, j);
                return 0;
            }
        }
    }
    return 0;
}
```

---

