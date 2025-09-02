# DZY Loves Chessboard

## 题目描述

一个棋盘上有一些格子是坏的，另一些是正常的。对于每一个正常的格子，都要在上面放上棋子。
请找到一组解使没有两个相同颜色的棋子相邻(两个格子相邻为它们存在共同的边)

## 样例 #1

### 输入

```
1 1
.
```

### 输出

```
B
```

## 样例 #2

### 输入

```
2 2
..
..
```

### 输出

```
BW
WB
```

## 样例 #3

### 输入

```
3 3
.-.
---
--.```

### 输出

```
B-B
---
--B```

# 题解

## 作者：wshim (赞：12)

本题可以用比较简单的方法来写，对于蒟蒻的我来说，就用比较水的方法来做吧，大佬勿喷，嘻嘻。
本题思路大概是这样的，（将一个符号的矩阵通过一系列的转换存入一个数组中，然后输出），好吧，直接上代码。
```cpp
#include<iostream>
using namespace std;
char a[101][101];//用来存修改后的矩阵
string b;//每行的输入可以通过字符串来输入
int n,m;
int main()
{
	cin>>n>>m;//输入矩阵的大小
	for(int i=1;i<=n;i++)
	{
		cin>>b;//把每行的字符，通过字符串来输入
		for(int j=1;j<=m;j++)
		{	
			if(b[j-1]=='.')
			{
				if((i+j)%2==1)
					a[i][j]='W';
				else
				a[i][j]='B';
			}//避免行和列中相邻的其中相邻
			if(b[j-1]=='-')
			a[i][j]='-';//如果棋盘为坏的，直接存入矩阵
		}//把修改后的矩阵存到a的二维数组里去
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cout<<a[i][j];//输出矩阵
			cout<<endl;//一定要记得换行，不然格式错误会很尴尬的
	}
			return 0;
}
 ```                      

---

## 作者：zhaotiensn (赞：11)

这一道题一眼看到像是**DFS**，因为数据范围比较小，只要求出保证相邻的不同的一组解就好了，坏掉的方格不用管，可以很简单的打好DFS，一旦找到一组解就返回，代码的实现也不难，一开始我这个蒟蒻就是这么想的，但是其实有更好的方法，代码的实现完全可以更加的简单。

因为坏掉的方格不用考虑，所以说坏掉的方格越多，限制的条件就越少。然后我们就可以倒过来思考，假设有一种情况可以在没有任何坏掉的方格的时候放满棋子，那么加上坏掉的方格也可以满足条件。然后就是求出这种情况了。

这种情况其实很简单，就是每一个斜行上的颜色一样，然后黑白交替出现。然后就是模拟，(i+j%2)相同的同一种颜色，坏掉方格直接输出'-'，代码很短。
给个图会意一下：

![(其实是国际象棋的棋盘）](https://cdn.luogu.com.cn/upload/pic/14904.png )

AC代码：（写的有点丑）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int n,m;
char a;

int main(){
	scanf("%d%d",&n,&m);//读入n，m
	for(int i=1;i<=n;i++){
		a=getchar();//读入换行符，防止被换行符影响
		for(int j=1;j<=m;j++){
			a=getchar();//读入a[i][j]的状态
			if(a=='-'){//为坏就直接输出'-'
				putchar('-');
			}else{
				if((i+j)&1){//(i+j)%2==1就把当前块变成白
					putchar('W');
				}else{
					putchar('B');//否则变成黑，边读边输，所以调试会有点奇怪
				}
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Apro1066 (赞：10)

看楼下大佬的题解还没有用深度优先搜索的，那么本蒟蒻就来一篇dfs的题解吧。

给出一张n*m的图，要在'.'的位置上填B或者W，给出要求B不能和B相邻，W不能和W相邻（就是黑白棋盘）。

从第一个点开始放棋子就行了，然后扫描，具体请看代码。

```cpp
#include <stdio.h>
#include <iostream>
using namespace std;
int tox[5]={0,1,0,-1,0};//这是4个方向 
int toy[5]={0,0,1,0,-1};//这也是（话说学过dfs的都知道吧） 
char a[101][101];
int n,m;
inline void dfs(int x,int y,int i)//当前坐标x,y，以及应该放什么样的棋子i 
{
	register int j;
	if(x<0 || x>n || y<0 || y>m)//如果越过了地图边界 
	{
		return;//返回上一层 
	}
	if(i==0)//如果i为0 
	{
		a[x][y]='W';//放w 
	}
	else//反之亦然 
	{
		a[x][y]='B';
	}
	for(j=1;j<=4;j++)//搜索4个方向 
	{
		int x1=x+tox[j];//试探下一个坐标 
		int y1=y+toy[j];
		if(a[x1][y1]=='.')//这个点为'.' 
		{
			if(i==0)//如果x,y是W，则接下来要放B 
			{
				dfs(x1,y1,1);//继续搜下一个点，然后下一个点应该放B 
			}
			else//同上 
			{
				dfs(x1,y1,0);
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			cin>>a[i][j];//输入地图 
		}
	}
	for(i=1;i<=n;i++)//先搜索一遍这个地图 
	{
		for(j=1;j<=m;j++)
		{//为什么不特判'-'的情况？因为我们针对这题只需要放W或B的棋子了，至于坏掉的格子我们不管，反正最后输出还是'-' 
			if(a[i][j]=='.')//从'.'开始搜 
			{
				dfs(i,j,1);
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			cout<<a[i][j];//打印地图 
		}
		cout<<endl;
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：chenxirui (赞：3)

## 其实呢这是一道特别  ~~简单~~  好的思维题
### 为啥这么说呢？
## 因为根本    不用  dfs！！！
~~开始吟唱~~



------------

且听我慢慢道来：

如果不加坏掉的方格这个条件， 我们很容易想到一种解法：
（用B代表黑， W代表白）

n = 1, m = 1

| B |
| :----------: |

n = 2, m = 2

| B | W |
| -----------: | -----------: |
| W | B |

n = 3, m = 3

| B | W | B |
| -----------: | -----------: | -----------: |
| W | B | W |
| B | W | B |

......


找到规律了吗？

### 没错！
## 只要没有坏掉的格子就直接输出就好了！

so......因为坏掉的格子不影响我们的答案，所以只要把格子坏掉的地方换成‘-’就行了！

### 这个方法是不是很 ~~邪门~~ 巧妙呢？

上代码！


```cpp
#include<cstdio>
int n, m;
char s[105][105];


int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", s[i]+1);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(s[i][j] == '.')
			{
				if((j%2) == (i%2)) printf("B");//找规律可知，找这种算法构造解的时候如果两个字同奇偶性，就是黑
				else printf("W");//否则就是白
			 } 
			else printf("-")//坏掉原样输出;
		}
		printf("\n");
	}
	return 0;
}
```

~~启示：以后做dfs的时候要偷懒~~

---

## 作者：hhrq (赞：1)

审题后发现$DFS$（深度优先搜索）即可做出来。

思路：

从左上角第一个棋子开始扫描，如果是好格，扫描上下左右，保存与相邻的棋子相反的颜色。扫描完毕，最后输出。


完整代码：
```
#include<cstdio>
#include<iostream>
using namespace std;

int n, m;
char map[105][105]; //棋盘 
int dx[4] = {0, 1, 0, -1};//斜度偏移数组，上下左右 
int dy[4] = {1, 0, -1, 0};

void dfs(char f, int x, int y)//F与上一次搜索的点的棋子不同， X是它的纵坐标，y是横坐标 
{
	map[x][y] = f;//保存 
	for(int i = 0;i < 4;i++)//扫描上下左右 
	{
		int x_new = x + dx[i], y_new = y + dy[i];//新位置 
		if(map[x_new][y_new] == '.' && x_new >= 1 && x_new <= n && y_new >= 1 && y_new <= m)//判断是否非法 
		{
			dfs(f == 'W'? 'B' : 'W', x_new, y_new);//搜索下一个 
		}
	}
}

int main()
{
	cin >> n >> m;//输入 
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			cin >> map[i][j];//输入 
		}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			if(map[i][j] == '.') dfs('B', i, j);//如果是好格，直接深搜 
		}
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			cout << map[i][j];//输出 
		}
		puts("");//换行 
	}
		
	return 0;
}

```

---

## 作者：GaryH (赞：1)

# 题解

## 1.题意

给定一个矩阵，每个元素可能是 ' . ' 或 ' - ' ,将是‘ - ’的填成不同的两种字母，要求相邻的两个字母不一样。

## 2.思路

首先，我们对于此题就应该想到**搜索**。虽然此题还有更巧妙的方法，但这只是因为此题的特殊性而使得特殊方法成立。而此题的正常方法就是搜索。

而搜索又分两种，第一种是**深度优先搜索**，即$DFS$，第二种则是广度优先搜索，即$BFS$。此题两种都可以选，但我认为，在两种方法都可以时，我们应该选择**时间最快**的方法（因为在比赛中$rank$高低先看时间再看空间嘛），而$BFS$一般都比$DFS$快，所以在这里我选了$BFS$。

那我们就只需用**队列**来实现。同时把步数相同的节点存进队列，再对地图进行改造即可。

## 3.CODE & AC记录

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[101][101],head,tail,nt[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char ch;
struct node{
	int x,y;
	bool p;
}q[100001];
//队列 
inline void bfs(int l,int k){
	head=tail=0;
	q[0].x=l;
	q[0].y=k;
	q[0].p=1;
	a[l][k]=1;
	while(head<=tail){
		//广搜模板 
		int nx,ny;
		//下一步的坐标 
		for(int i=0;i<=3;i++){
			nx=q[head].x+nt[i][0];
			ny=q[head].y+nt[i][1];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]==2)/*能不能走*/{
				q[++tail].x=nx;
				q[tail].y=ny;
				q[tail].p=!q[head].p;
				//入队 
				a[q[tail].x][q[tail].y]=q[tail].p;//改造地图 
			}
		}
		head++;
		//所有以head为父节点的扩展路径都入队，就将head出队 
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='-'){
				a[i][j]=-1;
			}else{
				a[i][j]=2;
			}
			//初始化地图 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==2){
				bfs(i,j);
				//还没放字母就搜一遍 
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==-1){
				cout<<'-';
			}
			if(a[i][j]==1){
				cout<<'B';
			}
			if(a[i][j]==0){
				cout<<'W';
			}
			//输出地图 
		}
		cout<<endl;
	}
	return 0;
}
```

[AC #1](https://www.luogu.com.cn/record/28686402)

### 好了，题解结束了，再见！

---

## 作者：CobaltChloride (赞：1)

- **~~既然没有Pascal的题解，那本蒟蒻来水一发~~**

```
//本题用Pascal写难就在换行符处理,本来应该是红题
var n,m,i,j:longint;
c:char;
a:array[1..100][1..100] of char;
begin
readln(n,m);//防止换行符影响
for i:=1 to n do begin
for j:=1 to m do begin
read(c);
if c='.' then begin
if (i+j) mod 2=0 then a[i][j]:='B'
else a[i][j]:='W';
end;//交替记录B,W
if c='-' then a[i][j]:='-';//坏格子
end;
readln;//防止换行符影响
end;
for i:=1 to n do begin
for j:=1 to m do write(a[i][j]);
writeln;//别忘换行
end;
end.
```

---

## 作者：MilkyCoffee (赞：0)

自认为解释的非常清楚。

这道题我会运用二维$DFS$的方法来做。

首先，我定义一个 $chess$ 二维 $char$ 数组并且遍历它，如果它是一个好格，就先用黑格来 $dfs$。

字符 $fill$ 是来存储是黑格还是白格的变量，$x$ 和 $y$ 都是记录当前坐标的，然后枚举四个方向，在这里我选择了用数组 $mov$ 包装它，这样就能十分方便的算出新的 $x$ 和 $y$ ，我们叫它 $x1$ 和 $y1$。

如果新的 $x1$ 和 $y1$ 在边界里并且是一个好格的话，就可以来继续 $dfs$ 了，如果上一个 $dfs$ 存储的 $fill$ 是一个黑子的话，就把新的格子存储一个白格，如果是一个白格的话，就把新的格子存储一个黑格，**不要忘记把过程存储到  chess 中（因为 chess 已经没有用处了，直接把新的变量存储进去就可以）**

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, cnt;
char chess[105][105];
int mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 包装四个方向

void dfs(char fill, int x, int y) {
    chess[x][y] = fill; // 把新的路径存储进chess中
    for (int i = 0; i < 5; i++) {
        int x1 = x + mov[i][0]; // 算出对应方向新的x
        int y1 = y + mov[i][1]; // 算出对应方向新的y
        if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= m && chess[x1][y1] == '.') { // 如果在边界内并且新格子是一个好格的话
            if (fill == 'B') // 如果这一个格子是黑色，那么下一个格子就要是白色
                dfs('W', x1, y1);
            else // 反之
                dfs('B', x1, y1);
        }
    } 
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> chess[i][j]; // 输入
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (chess[i][j] == '.')
				dfs('B', i, j); // 如果是好格就遍历
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << chess[i][j]; // 输出
		cout << endl;
	}
	return 0;
}
```


---

## 作者：GVNDN (赞：0)

这题，DFS我花了2小时做，结果第9个点还超时了。。。（我太菜了）

后来转念一想：直接强行先间隔染好色，再根据格子好坏输出不就好了？？？！！！（中途也有大佬提醒我这样的做法，但我当时想错了，只是在原有的搜索基础上改善了代码，~~然而还是t了~~）

上代码：
```cpp
#include<iostream>
#include<string>
using namespace std;

int n, m, f[110][110], v[] = {2, 0, 3, 2};    //f用来染色
bool b[110][110] = {0};    //b用来表示格子的好坏

int main(){
	cin >> n >> m;
	string s;
	for(int i = 1; i <= n; i++){
		cin >> s;
		for(int j = 1; j <= m; j++)
			if(s[j - 1] == '.')
				b[i][j] = 1;
	}

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(j == 1)
				f[i][j] = v[f[i - 1][j]];
				//v[2] = 3, v[3] = 2；而当格子为(1, 1)，即f[i - 1][j] = 0时，默认填入2，即v[0] = 2)
			else
				f[i][j] = v[f[i][j - 1]];

	for(int i = 1; i <= n; i++){    //根据格子好坏进行输出
		for(int j = 1; j <= m; j++)
			if(b[i][j]){
				if(f[i][j] == 2) cout << "B";
				else if(f[i][j] == 3) cout << "W";
			}
			else cout << "-";
		if(i != n) cout << endl;
	}
}
```

---

## 作者：棽木 (赞：0)

## 这大概是最简短的解法了吧





```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int m,n;
char mp[150][150];

int main()
{
    cin>>n>>m;
    for(int i=0; i<n; i++)
        {
            cin>>mp[i];             //读一行
            for(int j=0; j<m; j++)  //处理这一行
                if(mp[i][j]=='.')   //如果这个位置是好的
                    (i+j)%2==0 ? mp[i][j]='B' : mp[i][j]='W' ; 
                    //判断位置的奇偶，第一行i=0 位置的奇偶就是(i+j）的奇偶,偶位置放B，奇位置放W，
                    //下一行 i=i+1, （i+j）奇偶正好和上一行相反，实现了左右棋子不一样上下也不一样。这里使用对角线来考虑也可以。
            cout<<mp[i]<<endl;      //同时输出改好的这一行
        }
    return 0;
}

```


---

## 作者：Purslane (赞：0)

# 这道题似乎与DFS没关系
## 大家都看过国际象棋棋盘吧
## 其实这道题可以就像国际象棋那样黑白交错的摆放，遇到坏的就标记为‘-’
## 不需要打那么多的dfs（~~还有超时的风险，所以我不敢用~~）
### 不说了，上代码~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100-10; //超强防伪
char a[MAXN][MAXN]; //字符数组，存贮修改后的数组 
int n,m; //行&列 
int main() {
	cin>>m>>n; //防伪专用，输入请自行修改
	for(int i=0;i<n;i++) {
		string k;
		cin>>k; //读入这一行的情况 
		for(int j=0;j<m;j++) {
			if(k[j]=='-') a[i][j]='.'; //坏掉了&防伪专用，请自行修改 
			else if((i+j)&1) a[i][j]='B'; //放黑色 
			else a[i][j]='W'; //放白色 
		}
	}
	for(int i=0;i<n;i++) {
		cout<<a[i]<<"\n"; //超强输出 
	}
	return 0;
}


```


---

## 作者：cheater__ (赞：0)

打表大法

首先我们先把一个全部格子都是好的n*m棋盘用一个字符数组存，然后输入字符，如果当前输入字符为‘-‘，则替换掉原数组的字符。
如第i行第j列字符为B(或W),输入字符为‘-‘，则将a[i][j]替换为‘-‘。
最后输入输出时记得换行即可

附蒟蒻ac代码，大佬勿喷！！！
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define maxn 110

char a[maxn][maxn];
int n,m;

int main()
{
    char c;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	{
		if(i%2 == 0)
			for(int j=1;j<=m;j+=2)
				a[i][j] = 'W',a[i][j+1] = 'B';
		else
			for(int j=1;j<=m;j+=2)
				a[i][j] = 'B',a[i][j+1] = 'W';
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%c",&c);
		for(int j=1;j<=m;j++)
		{
			scanf("%c",&c);
			if(c == '-')
				a[i][j] = '-';
		}
	}
    for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%c",a[i][j]);
		printf("\n");
	}
	return 0;
}

```


---

