# [COCI 2012/2013 #5] ARHIPELAG

## 题目背景

一个受欢迎的旅游目的地国家坐落在一个惊人美丽的群岛上沐浴在阳光下。这个国家的居民以其众多的岛屿为傲。然而,全球气候变暖让他们非常担心:海平面上升导致干燥土地的流失迅速增加，这削弱了群岛的美丽。

## 题目描述

这个群岛的地图是一个 $R$ 行 $C$ 列的方阵。`X` 表示陆地，`.` 表示海。据估计，在 $50$ 年里，海水将淹没目前所有三面或四面环海的土地。

假设地图外全被海覆盖。你的任务是计算出 $50$ 年后的群岛地图(在所描述的海平面上升之后)。

因为那时的土地可能会比今天更少，你不需要打印出整个地图，而只是包含所有的土地的最小的矩形部分。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le R,C \le 10$。


------------

**【说明】**

本题分值按 COCI 原题设置，满分 $80$。

题目译自 [COCI2012~2013](https://hsin.hr/coci/archive/2012_2013/) [CONTEST #5](https://hsin.hr/coci/archive/2012_2013/contest5_tasks.pdf) _**T2 ARHIPELAG**_。

## 样例 #1

### 输入

```
5 3
...
.X.
.X.
.X.
...```

### 输出

```
X```

## 样例 #2

### 输入

```
3 10
..........
..XXX.XXX.
XXX.......
```

### 输出

```
.XX...X
XX.....```

# 题解

## 作者：追梦之鲸 (赞：5)

[经典回顾P7645](https://www.luogu.com.cn/problem/P7645)

#### 思路

我们可以把这个 $R \times C$ 的字符矩阵 $S$ 化成一个 $R \times C$ 的数字矩阵 $M$ 来表示海岸线，这个 $M$ 矩阵中大于二的地方就是海，否则就是陆地。

我们先把 $M$ 矩阵里的数都变成零，也就是都是陆地。如果 $S_{i,j}$ 等于 ``.`` 那么就把 $M_{i,j}$ 变成等于一个大于三的数（因为这个地方的数大于三就表示这个地方要变成海，那这个地方原来是不是海就没关系了），我选的是五，然后把 $M_{i-1,j}\ M_{i+1,j}\ M_{i,j-1}\ M_{i,j+1}$ 都加一（海岸线嘛）。注：根据样例，地图外面都是海，所以要把地图里边的周围那一圈都加一，当然四个角上要加二。

好，现在我们来看一下样例，来加深一下对上面那段话的理解。

样例 #1

$S$ 矩阵：

```c
...
.X.
.X.
.X.
...
```

现在我们按上面那段话来把 $S$ 转换成 $M$。

$M$ 矩阵：

```c
989
838
828
838
989
```

我们来看看 $M$ 矩阵的变化：

```c
5+4 5+3 5+4
5+3 0+3 5+3
5+3 0+2 5+3
5+3 0+3 5+3
5+4 5+3 5+4

```

如果还不懂可以自己推一下。

#### Code：
```c
//本人码风可能有问题，请见谅
#include<bits/stdc++.h>
#define ri register
using namespace std;
template <class O>
inline void read(O &x) {ri char c = getchar();x=0;for (; !isdigit(c); c = getchar());for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);return;}
const int MAX=1e+9;
int fx[6]={1,-1,0,0};
int fy[6]={0,0,1,-1};
char ch;
int n,m,mp[12][12],a=MAX,b=MAX,c,d;
int main(){
	read(n);read(m);
	for(ri int i=1;i<=n;i++)
		for(ri int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='.'){
				mp[i][j]=5;
				for(ri int k=0;k<4;k++)
					mp[i+fx[k]][j+fy[k]]++;
			}
		}
	for(ri int i=1;i<=n;i++)
		{mp[i][m]++;mp[i][1]++;}
	for(ri int i=1;i<=m;i++)
		{mp[n][i]++;mp[1][i]++;}
	for(ri int i=1;i<=n;i++)
		for(ri int j=1;j<=m;j++)
			if(mp[i][j]<3){
				a=min(a,i);
				b=min(b,j);
				c=max(c,i);
				d=max(d,j);
			}
	for(ri int i=a;i<=c;i++){
		for(ri int j=b;j<=d;j++){
			printf("%c",mp[i][j]<3?'X':'.');
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：zhang1234 (赞：3)

## 1.思路

这道题是道模拟题，先用二维数组储存地图，再遍历，只要找到陆地就判断四面有几面是海洋，若大于等于三面就会被淹没，最后输出。

## 2.注意点

+ 因为地图外全被海覆盖，所以至少要在给出的矩阵周围再围上一圈海。

+ 在寻找陆地时不能将有三面或四面的陆地直接变成海，因为它周围的陆地原本是有 $i$ 面海，把它变成海后，周围的陆地就有了 $i+1$ 面海，会影响以后的判断，所以要先储存会被淹没的陆地，在遍历完后再将它们变成海。

+ 在遍历时要把不会淹没的陆地的横纵坐标的最大值和最小值保留下来，在输出时分别当做初始值和边界进行输出。

## 3.代码

```cpp
#include <iostream>
#include <cmath>

using namespace std;

char a[15][15];
int b[230][2];//储存要被淹没的陆地的坐标 

int main()
{
	int n,m;
	int maxx = -1,maxy = -1,minx = 15,miny = 15;//为了控制输出的矩阵大小 
	int z = 0; 
	char q;
	 
	cin>>n>>m;
	
	for(int i = 0;i <= n+1;i++)
	{
		for(int j = 0;j <= m+1;j++)
		{
			a[i][j] = '.';
		}
	}
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			cin>>q;
			if(q == 'X')
			{
				a[i][j] = q;
			}
		}
	}//输入50年前陆地的位置 
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			if(a[i][j] == 'X')
			{
				int sum = 0;//记录每块陆地的四面有多少是海洋 
				if(a[i-1][j] == '.')
				{
					sum++;
				}
				if(a[i+1][j] == '.')
				{
					sum++;
				}
				if(a[i][j-1] == '.')
				{
					sum++;
				}
				if(a[i][j+1] == '.')
				{
					sum++;
				}
				if(sum < 3)
				{
					maxx = max(maxx,i);
					maxy = max(maxy,j);
					minx = min(minx,i);
					miny = min(miny,j);
				}
				else
				{
					z++;
					b[z][0] = i;
					b[z][1] = j;
				}//判断此块陆地是否会被淹没
			}
		}
	}

	for(int i = 1;i <= z;i++)
	{
		a[b[i][0]][b[i][1]] = '.';
	}//将要淹没的陆地淹没 
	for(int i = minx;i <= maxx;i++)
	{
		for(int j = miny;j <= maxy;j++)
		{
			cout<<a[i][j];
		}
		cout<<endl;
	}
    return 0;
}
```


---

## 作者：Leo2020 (赞：3)


```
#include<bits/stdc++.h>//万能头文件 
using namespace std;
bool flag[15][15],f[15][15];//第一个flag用来判断岛屿和大海，第二个f记录是否淹没 
const int d[5]={1,0,-1,0,1};//上下左右四个方位 
int main(){
	int n,m;
	cin >> n >> m;//输入长，宽 
	for(int i=1;i<=n;i++){//为了后面运算防止超出范围，i和j要从1开始 
		for(int j=1;j<=m;j++){
			char t;
			cin >> t;
			if(t=='.')flag[i][j]=0;//判断岛屿海洋 
			else flag[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int tem=0;//计数器，存贮周围海洋的个数 
			if(flag[i][j]==1){
				for(int k=0;k<4;k++){//四个方位枚举 
					int x=i,y=j;
					x+=d[k];
					y+=d[k+1];
					if(flag[x][y]==0) tem++;
					
				}
			}
			if(tem>=3)f[i][j]=1;//这里不能写成下面那样，需要一个f来记录这里会不会被海水淹没 
			// 如果写成下面那样，在第一行做运算的时候，会把岛屿变成海洋
			//导致第二次运算错误
			// if(tem>=3)flag[i][j]=0;  <-千万不要这么写 
		}
	}
	int u=99,d=1,l=99,r=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(f[i][j]==1)flag[i][j]=0;
			if(flag[i][j]==1){
				u=min(u,i);//判断最上侧 
				l=min(l,j);//判断最左侧
				d=max(d,i);//判断最下侧
				r=max(r,j);//判断最右侧
			}
			
		}
	}
	if(u==99){//如果没有岛屿，全部输出"."； 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cout << '.';
			}
			cout << endl;
		}
	}
	for(int i=u;i<=d;i++){
		for(int j=l;j<=r;j++){
			if(flag[i][j]==0) cout << '.';//输出 
			else cout << "X" ;
		}
		cout << endl;//不要忘记每一行换行 
	}
	
	
	return 0;//华丽的结束 
}//QAQ 
```


---

## 作者：love_tide (赞：2)

## 搜索做法
- 数据很淼，所以选择了~~通俗易懂~~的搜索。

- 通过读题，本题的核心在于**海水将淹没目前所有三面或四面环海的土地**。

- 抽象点，如果一个陆地三面或者四面都是海洋，那么这块陆地被淹没。也就是本道题的核心：**四方搜索**。

- 本题的难点，也是区别于其他搜索题的，也就是本题的输出：**不用打印出整个地图，而只是包含所有的土地的最小的矩形部分**。我用了 max 和 min 函数来解决这一问题，找到最接近陆地的一个最小区间。

## 代码

细节在注释里解释。



```cpp
#include<bits/stdc++.h>

using namespace std;//我把输出，搜索都封装到了函数里面

int n,m;

int island;

char a[15][15];//这里我用了两个图，一个用来存储结果，一个用来判断

char b[15][15];

int maxx=-1,maxy=-1,minx=16,miny=16;//注意max，min的赋值，这里卡了我好久...

int search(int x,int y){//搜索是否四面或者三面环海
	
	int ans=0;
	
	if(a[x][y+1]!='X') ans++;
	
	if(a[x][y-1]!='X') ans++;
	
	if(a[x-1][y]!='X') ans++;
	
	if(a[x+1][y]!='X') ans++;
	
	if(ans>=3) return 1;
	
	if(ans<3){
		
		maxx=max(maxx,x);
		maxy=max(maxy,y);
		minx=min(minx,x);
		miny=min(miny,y);
		
	}
	
	return 0;
	
}

void printf(){
	
	for(int i=minx;i<=maxx;i++){
		
		for(int j=miny;j<=maxy;j++){
			
			if(b[i][j]!='X') cout<<".";
			
			else cout<<b[i][j];
			
		}
		
		cout<<endl;	
	
	}
	
	
}

void dfs(int x,int y){
	//我的搜索顺序是横着搜索，然后换行搜索下一行

	
	if(x==n&&y==m+1){//如果搜索完成，那么输出结束程序
		
		printf();
		
		return ;
	}
	if(y==m+1) {//换行
		
		dfs(x+1,1);
		
		return ;
	}
	
	if(a[x][y]=='X'){
						
		if(search(x,y)){//判断是否三面或四面环海
		
		b[x][y]='.';//被淹没
		
		}	
	
	}
			
		dfs(x,y+1);//递归继续搜索下一个元素
		
}

int main(){
	
	cin>>n>>m;
	
	for(int i=1;i<=n;i++){
	
		for(int j=1;j<=m;j++){
			
		cin>>a[i][j];
		
		b[i][j]=a[i][j];//存图
					
		}
	
	}
	
	dfs(1,1);
	
	return 0;
		
} 
```


---

## 作者：liswill (赞：1)

## 题意
给一个包含 `X` 和 `.` 的地图，分别表示陆地和大海。进行操作：对于每一个 `X` ，若其三面环海或四面环海，则将其改为 `.` 。输出包含所有的土地的最小的矩形部分。 

## 思路
咋一看，是一道搜索。难点在于要输出包含所有土地的最小矩形部分。先按题目要求处理地图，纯搜索即可。

然后寻找含有矩形的最小矩阵。先循环找出四个矩形的坐标，也就是行起始、行结束、列起始和列结束。

最后，在确定的矩形范围中，输出处理好的地图。

## 注意

这题题意有一个坑，就是处理沉岛的时候要新开一个 `bool` 数组标记，不能直接修改，不然会影响后面沉岛的判断。

## Code

```cpp
#include<bits/stdc++.h>
#define sp setprecision
#define RE return
#define ll __int64_t
#define FOR(i,a,b) for(int i=a;i<=b;i++)

using namespace std;

template <typename T>
inline T
read()
{
    T sum=0,fl=1;
    int ch=getchar();
    for (;!isdigit(ch);ch=getchar())
        if (ch=='-')	fl=-1;
        for(;isdigit(ch);ch = getchar())    sum=sum*10+ch-'0';
        return sum*fl;
}

using namespace std;

char a[15][15];
bool sur[15][15];//标记数组，用于标记没有沉的岛
int cnt,cols=1000005,cole=-1,rows=1000005,rowe=-1;
int main(){
    int n=read<int>(),m=read<int>();
    FOR(i,1,n){
        FOR(j,1,m)  cin>>a[i][j];
    }
    FOR(i,1,n){//处理环海沉岛
        FOR(j,1,m){
            cnt=0;
            if(a[i][j]=='X'){
                if(a[i-1][j]=='X')    cnt++;
                if(a[i+1][j]=='X')    cnt++;
                if(a[i][j-1]=='X')    cnt++;
                if(a[i][j+1]=='X')    cnt++;
            }
            if(cnt>1) sur[i][j]=true;//如果附近有两座及以上的岛，就不会沉 
            //*若发现沉岛，不能直接将地图的此位置修改为 '.' !
        }
    }
    FOR(i,1,n){
        FOR(j,1,m){
            if(sur[i][j]){//如果当前位置有岛屿
                cols=min(cols,i);
                rows=min(rows,j);
                cole=max(cole,i);
                rowe=max(rowe,j);//求矩形范围坐标
            }

        }
    }
    FOR(i,cols,cole){
        FOR(j,rows,rowe){
            if(a[i][j]=='.'/*本来就是海*/||!sur[i][j]/*沉了*/)   printf(".");
            else    printf("X");
        }
        puts("");
    }
    RE 0;
}


```

---

## 作者：Nemonade (赞：1)

思路其实很简单，读入后一个一个点地判断是否为字符 'X' ，统计相邻的海的个数，从而判断该国土是否会被淹没，最后跑一遍输出即可。

注意有以下细节：

1. 要注意给出矩阵外也是海，也就是说当国土在地图边缘时要特判。

2. 标记时一定要创建一个副本，否则会导致数据紊乱。

code

```cpp 
#include<bits/stdc++.h>
using namespace std;
const int N=13;
//偏移量 
int dxy[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
int n,m;
//答案左上角和右下角 
int ix=INT_MAX,iy=INT_MAX,mx=-1,my=-1;
//储存国土 
char mp[N][N],tmp[N][N];
int main(){
    cin>>n>>m;
    //输入并且复制 
    for(register int i=1;i<=n;++i){for(register int j=1;j<=m;++j){
        cin>>mp[i][j];tmp[i][j]=mp[i][j];
    }}
    //全部枚举 
    for(register int x=1;x<=n;++x){for(register int y=1;y<=m;++y){
    	//如果不是国土就下一个 
        if(mp[x][y]=='.') continue;
        int sum=0;
        for(register int i=0;i<=3;++i){
            int dx=x+dxy[i][0],dy=y+dxy[i][1];
            if(dx<0||dy<0||dx>n+1||dy>m+1) continue;
			//dx==0||dy==0||dx==n+1||dy==m+1(地图外)也是海
            if(mp[dx][dy]=='.'||dx==0||dy==0||dx==n+1||dy==m+1) ++sum;
        }
		//储存在副本里，否则会影响以后的判断
        if(sum>=3) tmp[x][y]='.';
    }}
    //跑一遍求出答案矩阵 
    for(register int x=1;x<=n;++x){for(register int y=1;y<=m;++y){
        if(tmp[x][y]=='X'){
        	//暴力求出答案矩阵
            ix=min(ix,x);
            iy=min(iy,y);
            mx=max(mx,x);
            my=max(my,y);
        }
    }}
    //输出 
    for(register int x=ix;x<=mx;++x){for(register int y=iy;y<=my;++y){
        cout<<tmp[x][y];
    }cout<<endl;}
    return 0;
}
```

---

## 作者：ZBAA_MKC (赞：1)

这是一道有一些细节的模拟题。

#### 思路分析

先输入后把一开始有陆地的地方在另一个数组中标为 `true`,之后再判断陆地被水淹没是要根据**原始状态**来判断该陆地是否被淹没，否则可能会把不应该被淹没的陆地也更改为被淹没。

对于输出，使用打擂台法来枚举有陆地的最小行，最小列以及最大行，最大列。


#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

char mp[15][15];
bool f[15][15];
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int main()
{
    int r, c;
    cin >> r >> c;
    for (int i = 0; i <= r + 1; i++)
    {
    	for (int j = 0; j <= c + 1; j++)
    	{
    		mp[i][j] = '.'; //初始化
		}
	}
    for (int i = 1; i <= r; i++)
    {
    	for (int j = 1; j <= c; j++)
    	{
    		cin >> mp[i][j]; //输入和标记
    		if (mp[i][j] == 'X')
    		{
    			f[i][j] = true;
			}
		}
	}
	for (int i = 1; i <= r; i++) //判断是否会被水淹没
	{
		for (int j = 1; j <= c; j++)
		{
			int cnt = 0; 
			if (mp[i][j] == 'X')
			{
				for (int k = 0; k < 4; k++)
				{
					if (!f[i + dx[k]][j + dy[k]])
					{
						cnt++;
					}
				}
				if (cnt >= 3)
				{
					mp[i][j] = '.';	
				}
			}
		}
	}
	int xmin = r + 1, ymin = c + 1, xmax = 0, ymax = 0;
	for (int i = 1; i <= r; i++) //判断输出范围
	{
		for (int j = 1; j <= c; j++)
		{
			if (mp[i][j] == 'X')
			{
				xmax = max(i, xmax);
				ymax = max(j, ymax);
				xmin = min(i, xmin);
				ymin = min(j, ymin);
			}
		}
	}
	for (int i = xmin; i <= xmax; i++) //按判断好的范围输出
	{
		for (int j = ymin; j <= ymax; j++)
		{
			cout << mp[i][j];
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：zymooll (赞：0)

英文版原题链接：[Link](https://hsin.hr/coci/archive/2012_2013/contest5_tasks.pdf)

这题是一道不错的模拟题，需要注意以下几个点
1. 需要另外开个数组来确定是否被淹没
2. 数组要开大（如果你用的我这种方法判定是否被淹没的话）
3. 题目可以保证不需要特判完全淹没

具体思路见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ls;
int r,c,dmap[20][20],dmap1[20][20];
//dmap存储结果 dmap1存储原图
int fx[4][2]={-1,0,0,-1,1,0,0,1};
//四个方向 上述写法等同于int fx[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
int main(){
    cin>>r>>c;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>ls;
            if(ls=='X')dmap[i][j]=dmap1[i][j]=1;
            //令海洋为0，陆地为1
        }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            if(dmap[i][j]){//枚举每个陆地
                int js=0;
                for(int k=0;k<4;k++){
                    /*
                    这一段是判断我四周是不是海洋
                    这边利用了main函数外定义变量初始化为0的特性
                    在本题中即是除了我们输入的陆地，剩下的都是海洋
                    */
                    if(!dmap1[i+fx[k][0]][j+fx[k][1]]){
                        js++;
                    }
                }
                if(js>=3)dmap[i][j]=0;
            }
        }
    }
    int maxx=-0x7f,maxy=-0x7f,minx=0x7f,miny=0x7f;
    for(int i=1;i<=r;i++){//确定需要输出的边界
        for(int j=1;j<=c;j++){
            if(dmap[i][j]){
                maxx=max(maxx,i),minx=min(minx,i);
                maxy=max(maxy,j),miny=min(miny,j);
            }
        }
    }
    for(int i=minx;i<=maxx;i++){//根据预定边界输出
        for(int j=miny;j<=maxy;j++){
            if(dmap[i][j])cout<<'X';
            else cout<<'.';
        }
        cout<<endl;
    }
    return 0;
}
```

---

