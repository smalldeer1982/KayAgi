# [ICPC 2015 WF] Keyboarding

## 题目描述

输入一个文本消息需要多少次按键？你可能认为这等同于文本中的字符数，但这仅在一次按键生成一个字符时才正确。对于口袋大小的设备，输入文本的可能性通常受到限制。有些设备仅提供少量按钮，远少于字母表中的字母数量。对于这样的设备，输入一个字符可能需要多次按键。为了解决这些限制，一种机制是在屏幕上显示虚拟键盘，并提供一个可以从一个键移动到另一个键的光标来选择字符。四个方向键控制光标的移动，当光标位于适当的键上时，按下第五个按钮选择相应的字符并将其附加到文本末尾。要终止文本，用户必须导航到并选择 Enter 键。这使用户可以使用任意字符集并仅用五个硬件按钮输入任意长度的文本。

在这个问题中，给定一个虚拟键盘布局，你的任务是确定输入给定文本所需的最少按键次数，其中按下任何一个五个硬件按钮都算作一次按键。键以矩形网格排列，每个虚拟键占据网格的一个或多个连接单元格。光标从键盘的左上角开始，并在四个基本方向上移动，以便它总是跳到该方向上属于不同键的下一个单元格。如果没有这样的单元格，光标不会移动。

![](https://cdn.luogu.com.cn/upload/image_hosting/3cxjl2y4.png)

图 1：样例输入 1。一个示例虚拟键盘和硬件按钮。

图 1，说明了样例输入 1，展示了一种在示例虚拟键盘上使用 30 次按键输入 CONTEST 的可能方式。红点表示按下选择按钮的虚拟键。

## 说明/提示

时间限制：3000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2015。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
```

### 输出

```
30
```

## 样例 #2

### 输入

```
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
```

### 输出

```
160
```

## 样例 #3

### 输入

```
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
```

### 输出

```
19
```

## 样例 #4

### 输入

```
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 输出

```
7
```

# 题解

## 作者：Durancer (赞：11)

#### 坑点提醒

1、最后需要你手动添加一个$“*”$

2、注意在其实位置按键的情况

#### 思路

首先我们可以把所有相关涉及到的字符都映射为数字，方便处理，包括$(A…Z),(1…9),("*""-")$这些东东，处理的时候别映射 $0$ 就行

当我们输入的时候直接映射到一个二维数组 $a$ 来装载键盘的每个键

将目标串映射到一个一维数组 $b$ 中来需要按得每一个键，最后别忘了手动添加一位来存 $"*"$

那么如何选择位置呢，如果在搜索的过程中暴力美剧会非常耗时间，那么这个时候就可以预处理每一个键第一个到达的位置即可

为了方便我们要设一个结构体类型的三维数组

结构体的变量分别为 到达的位置的横坐标 $x$ ,到达位置的纵坐标 $y$ ,到达这个位置的时候要匹配目标串的哪一位 $step$ ,以及到这个点已经走了几步 $dis$

三维数组 $f[k][i][j]$ 表示从 $(i,j)$向 $k$ 方向走到达的第一个位置的信息（即结构体中的内容）

那么预处理之后就开始广搜了

在开始广搜之前，因为我们是从第一位开始的，那么我们最好先预处理一下在第一位一共可以连续按几次，然后再把结构体重所表示的数据存进去，在代码中有就不详细说了

那么现在开始广搜

考虑两种情况，我们要把选择和匹配分开找

一、

那么先是匹配，要看一下堆顶的这个位置是否和当前要匹配的位置相同，如果是相同的时候，那就在进行判断一下这个是不是最终状态，如果是，那直接把答案赋值为当前的步数+1就是最有的答案

那如果不是最后的一个情况呢

可以设一个 $vis$ 数组，用来存当前堆顶的点接下来该匹配哪一位了，然后把相应的结构体中的数据都放进去继续查找

二、

最后再开始选择

首先枚举该点四个位置的到达点，当然因为我在预处理位置的时候有一个位置得移动忘加了，所以还要加上，一次移动

首先判断一下是否越界

然后再判断一下当前要选择的地方要比原坐标的要处理的位置要更大，那么就不需要更新 $vis$ 数组。

否则的话，就更新当前的 $vis$ 数组为现在要处理的位置（不用+1，因为是选择，即跳过当前的匹配直接跳进），然后把当前要选择的位置的数据放进去

最后直接输出即可

#### 代码实现

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
using namespace std;
const int N=59;
const int M=10009;
struct node{
	int x;
	int y;
	int step;//指下一个到了第几个位置， 
	int dis;//按了几次 
}f[5][N][N];//后两个表示坐标，前一个表示方向，即i,j在k方向上到的最近的点 
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
char wor[M];
int n,m,len,a[N][N],b[M],vis[N][N];
map<char,int> mp;
void prepare()//预先将所有的字符串处理成数字类型的，方便处理
{
	for(int i=0;i<=9;i++)
	mp[(char)('0'+i)]=i+1;
	for(int i=0;i<26;i++)
	mp[(char)('A'+i)]=i+11;//1-10被取过了 
	mp['-']=37;
	mp['*']=38; 
} 
void get()//处理一下四个方向可以到达的点 
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
			{
				int x=i;
				int y=j;
				while(a[x][y]==a[x+dx[k]][y+dy[k]])//如果一致的话 
				{
					x+=dx[k];
					y+=dy[k];//一致加到不同为止 
				}
				f[k][i][j]=(node){x,y,0,0};
			}
}
int search()
{
	memset(vis,0,sizeof(vis));
	queue<node> q;
	int ans=0;
	int k=1;
	while(a[1][1]==b[k]&&k<=len) ++k;//在起点选取的情况
	q.push((node){1,1,k,k-1});
	vis[1][1]=k;
	while(!q.empty())
	{
		node cun=q.front();
		q.pop();
		int x=cun.x;
		int y=cun.y;
		int now=cun.step; 
		if(a[x][y]==b[now])//此时相等了
		{
			if(now==len) 
			{
				ans=cun.dis+1;
				break;//如果找完了？直接跳出 
			}
			vis[x][y]=now+1;//更新一下，因为按了一遍键盘 
			q.push((node){x,y,now+1,cun.dis+1});
		} 
		for(int i=0;i<4;i++)
		{
			node chose=f[i][x][y];
			chose.x+=dx[i];
			chose.y+=dy[i];//预处理上在加一次，保证完整
			if(chose.x<1||chose.x>n||chose.y<1||chose.y>m) continue;//越界了
			if(vis[chose.x][chose.y]>=now) continue;//如果选择的地方的要处理的位置比现在的要大，不用改，防止变worse 
			vis[chose.x][chose.y]=now;//如果可行，那么把接下来要弄得位置给存进去
			q.push((node){chose.x,chose.y,now,cun.dis+1});//跳到那一步 
		} 
	} 
	return ans;
}
int main()
{
	prepare();
	while(scanf("%d",&n)!=EOF)//UVA经典输入方式
	{	
//		cin>>n;
		cin>>m;
		for(int i=1;i<=n;i++)//输入每一行的字符串
		{
			cin>>wor;		
			for(int j=0;j<m;j++)
				a[i][j+1]=mp[wor[j]];//将每个字符的代表的数字映射到a数组中
				//从1开始方便 
		} 
		cin>>wor;
		len=strlen(wor);
		for(int i=0;i<len;i++) b[i+1]=mp[wor[i]];//依旧是映射，从1开始
		len++;
		b[len]=38;//注意最后有一个*
		get();
		cout<<search()<<endl; 
	} 
	return 0;
} 
```


---

## 作者：斜揽残箫 (赞：5)

#### 【思路分析】

首先用字符串数组把键盘和要打的字母读入，**一定要在要求的字符串最后加个“$*$”。** ~~（感受一下本蒟蒻爆零的痛苦）~~

之后便开始我们愉快的搜索过程了：先计算出所要的字符串的长度，再寻找每一位上与答案字符串相符的字符，统计出到达每个字符的按键次数，取搜索成功的最小值即为答案。

到了这个时候便有问题了，因为键盘很大，要求我们打的字符串长度最多有10000，而且有很多对我们没有用的字符干扰，这样枚举每一个能到到达的位置必然会完美的 $TLE$。

这就要求我们思考了，如何能够减少无用的信息呢？

其实我们可以对键盘做一个预处理，**寻找在该方向上能够到达的第一个不同的字符，如果无解（超出键盘还没有找到），就把它附一个很大的数，表示找不到。**

可以用两个三维数组来存从当前字符是否能到到下个字符；
如下面的 $disx[k][i][j]$ 和 $disy[k][i][j]$ 。
其中的第一维 $[k]$ 表示向哪个方向移动，第二维 $[i]$，第三维 $[j]$ 表示坐标。

#### 【Code】
```cpp
void init()
{
	for(int i = 1; i <= n; ++i) {//枚举行；
		for(int j = 1; j <= m; ++j) {//枚举列；
			for(int k = 1; k <= 4; ++k) {//枚举每个方向；
				int sx = i, sy = j;
				while(mp[sx][sy] == mp[i][j]){
				//当寻找到的字符和原来的字符相同时，就继续枚举；
					sx += dx[k];
					sy += dy[k];
				}
				if(check(sx,sy)) {
				//待会在完整代码里展示出，判断是否出了边界；
					disx[k][i][j] = sx;
					disy[k][i][j] = sy;
				//如果没出边界，就附上从这个字符能到的下个字符的坐标；
				} else {
					disx[k][i][j] = INF;
					disy[k][i][j] = INF;//否则 附为 0x3f3f3f3f；
				}
			}
		}
	}
	return;
}
```
----

之后就开始我们最终的搜索了，因为前面的预处理，使得减少了很多冗杂的信息。

这个时候再设置一个三维数组表示到 $(x,y)$ 的已有的字符串长度的按键次数，开始先设置为 $0x3f3f3f3f $。设置一个结构体来表示到现在的坐标 $(x,y)$ 的按键次数和字符串长度；

如果**新找到的字符串的长度的按键次数**比**原有的字符串的长度的按键次数**少，就更新按键次数，使得再排除一些冗杂信息。~~（貌似有点绕口？）~~，不过我相信你们能看懂QAQ。

**易错点**

+ 在队列搜索中 要设定两个值 $now$ 和 $cur$ ，因为在每次放入新值时都会把 $now$ 给替换为别的值。我第一次就是因为这种情况导致一直调不出来。

-----
接下来就上代码了，一些解释我会写在代码里。

#### 【Code】
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>
#include<set>
#define ull unsigned long long
#define ll long long
#define M 1000010
#define N 1010
#define qaq cout<<"可行QAQ"<<endl
#define INF 0x3f3f3f3f
using namespace std;
const int mod1 = 19260817;
const int mod2 = 19660813;
/*================================================*/

int n,m,len;
char mp[55][55];//键盘
char yuan[10010];//要求的字符串
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};//方向
int disx[5][55][55],disy[5][55][55];//能到达的位置的坐标
struct node {
	int x , y , cnt , len ;
} now , cur ;//从左到右依次为 ： 横坐标，纵坐标，按键次数，字符串长度
int length[10010][55][55];//储存按键次数
queue<node> qp;

/*================================================*/

bool check(int x,int y) //判断是否出边界
{
	if(x < 1 || x > n) return false;
	if(y < 1 || y > m) return false;
	return true;
}

void init()
{
	for(int i = 1; i <= n; ++i) {//枚举行；
		for(int j = 1; j <= m; ++j) {//枚举列；
			for(int k = 1; k <= 4; ++k) {//枚举每个方向；
				int sx = i, sy = j;
				while(mp[sx][sy] == mp[i][j]){
				//当寻找到的字符和原来的字符相同时，就继续枚举；
					sx += dx[k];
					sy += dy[k];
				}
				if(check(sx,sy)) {
					disx[k][i][j] = sx;
					disy[k][i][j] = sy;
				//如果没出边界，就附上从这个字符能到的下个字符的坐标；
				} else {
					disx[k][i][j] = INF;
					disy[k][i][j] = INF;//否则 附为 0x3f3f3f3f；
				}
			}
		}
	}
	return;
}

int bfs() 
{
	
	memset(length,INF,sizeof(length));
	now.x = 1; now.y = 1; now.len = 0; now.cnt = 0;
	//初始化一开始的位置，按键次数，找到的字符串长度。
	length[0][now.x][now.y] = 0;//当找到的字符串长度为 0 是按键次数为 0
	qp.push((node){ now.x, now.y, now.cnt, now.len});//压入队列
	while(qp.size()) {
		cur = qp.front();//cur 是 光标的意思
		qp.pop();
		while(yuan[cur.len + 1] == mp[cur.x][cur.y]) {//寻找匹配的字符
			cur.len++;
			cur.cnt++;
		}
		if(cur.len == len) return cur.cnt;
		//退出条件 ：把要求的字符串打完了
		for(int i=1;i<=4;i++) {//向 4 个方向枚举
			now.x = cur.x; now.y = cur.y;
			now.len = cur.len; now.cnt = cur.cnt;
			//因为 下面 now.x 和 now.y 被附为了新值。
			//所以这里每一遍都要把 now = cur.
			if(disx[i][now.x][now.y] != INF ||
			    disy[i][now.x][now.y] != INF) {//如果有可到达的字符
				now.x = disx[i][cur.x][cur.y];
				now.y = disy[i][cur.x][cur.y];
				now.len = cur.len;
				now.cnt = cur.cnt + 1;//赋值
				if(now.cnt < length[now.len][now.x][now.y]) {//如果小于
					length[now.len][now.x][now.y] = now.cnt;
					//更新到现在长度的最小值。
					qp.push((node){now.x , now.y , now.cnt , now.len});
				}
			}
		}
	}
}

/*=================================================*/

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1 ;i <= n; ++i){
		scanf("%s",mp[i] + 1);
	}
	scanf("%s",yuan + 1);//读入
	yuan[strlen(yuan + 1)+ 1] = '*';//最后一定要加 * ； ！！！！
	len = strlen(yuan + 1);//计算要求的字符串长度
	init();
	int ans = bfs();
	printf("%d",ans);//输出
	return 0;
}
```
-----

---

## 作者：FLAMEs_ (赞：3)

### 不说废话，开门见山，上思路：


将所查询到的每个点都判定一次状态(是否符合当前所寻找的字符），符合便直接加入队列；而若不符，则考虑向四周移动，用两个数据(移动次数，已选的字符数)记录状态后再加队列即可。

----------------------------
更详细解释先看俺的代码中的注释撒。
```cpp
#include <bits/stdc++.h>
using namespace std;
map <char,int> Map;//用map转换字符的存储，便于计算
int n,m,ans,mp[57][57],xx[4]={0,1,0,-1},yy[4]={1,0,-1,0},nex[57][57][4][2],lst[10007],vis[57][57],len;
void premap()//预处理Map
{
    for(int i=1;i<=10;i++) Map[(char)('0'+i-1)]=i;//数字对应
    for(int i=0;i<=25;i++) Map[(char)('A'+i)]=i+11;//大写字母对应
    Map['-']=37; Map['*']=38;//特殊字符
}
void prenex()//此处预处理next数组（next[i][j][k][0,1]表示从(i,j)点出发向k方向（形象化）移动到的位置，用第四个下标存储到达位置(0:x坐标，1:y坐标)）
{
   for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   for(int k=0;k<4;k++)
   {
	    int x=i+xx[k],y=j+yy[k];
	    while(mp[i][j]==mp[x][y]) x+=xx[k],y+=yy[k];//寻找在该方向下可移动到的最远距离
	    nex[i][j][k][0]=x; nex[i][j][k][1]=y;//移动
   }
}
struct node
{
	int x,y,stp,dis;
   //stp为当前所查询到的个数，dis为光标移动的次数，x,y即为当前坐标
};
void bfs()//主体
{
    queue <node> q;
    q.push((node){1,1,0,0});//最开始的状态
    while(!q.empty())
    {
        node u=q.front();
	q.pop();
        if(mp[u.x][u.y]==lst[u.stp])//如果这个字符是你目前想要的字符。
        {
            if(u.stp==len)//判定程序是否结束。
            {
                ans=u.dis+1;
                return;
            }
            u.stp++; u.dis++;//匹配
            vis[u.x][u.y]=u.stp;//更新
            q.push(u);
        }
        else//不匹配，向后寻找。
        {
            for(int k=0;k<4;k++)//开始向四个方向寻找。
            {
                int x=nex[u.x][u.y][k][0],y=nex[u.x][u.y][k][1];
                if(x<1||x>n||y<1||y>m)continue;//越界判定
                if(vis[x][y]>=u.stp)continue;//找到的点已经比当前状态更优，避免重复计算，进行优化。
                vis[x][y]=u.stp;
                q.push((node){x,y,u.stp,u.dis+1});
            }
        }
    }
}
char ch[10007];
void data_init()//初始化
{
	memset(nex,0,sizeof(nex));
   memset(mp,0,sizeof(mp));
   memset(lst,0,sizeof(lst));
   memset(vis,-1,sizeof(vis));
   ans=0;
}
int main()
{
    premap();
    while(scanf("%d",&n)!=EOF)
    {
    	data_init();
        scanf("%d",&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",ch);
            for(int j=0;j<m;j++)
            mp[i][j+1]=Map[ch[j]];//数据处理
        }
        scanf("%s",ch); len=strlen(ch);
        for(int i=0;i<len;i++) lst[i]=Map[ch[i]];//转换
        lst[len]=38;//注意，此处一定要加上结尾的换行符。
        prenex();
        bfs();
        cout<<ans<<"\n";
    }
    return 0;
}
```


---

## 作者：scp020 (赞：2)

# P6909 [ICPC2015 WF] Keyboarding 题解

我不理解，为什么这道题没有多组测试但是一大堆题解写了多测。

一道有坑的题。结尾要打印空格，即 `*`。而且最后搜到空格还要再按键。

## 解法

看到数据范围 $n,m \le 50$，于是考虑广度优先搜索。

因为光标总是跳到下一个在一方向上与当前位置不同的字符，所以我们考虑 $\mathcal{O}(n^3)$ 预处理出每个位置上下左右能跳到哪里，方便下面的搜索。

搜索中我们记录搜到的位置、已经打印出的字符数量和按键次数。

对于每次搜索，如果现在搜到的位置可以打印出字符，那么我们就将其打印出来，再向 $4$ 个方向搜索下面的字符。注意到我们用的是广度优先搜索，所以第一次打印完所有字符一定是最优解。

### 剪枝

1. 考虑如果一个位置的一个方向上没有与这个位置不同的字符，那我们就不去搜索这个方向，可以通过预处理完成。

2. 考虑到搜索时有可能出现从一个点开始向左搜索但是没有搜到答案又向右搜回这个点的情况，我们就标记搜到一个位置最多可以打印出的字符，记作 $vis_{i,j}$，如果搜到一个点现在打印出的字符比 $vis_{i,j}$ 小，则剪枝。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	快读快写，这里不贴了。忽略即可。
	*/
};
using namespace fast_IO;
int n,m,dx[100][100][5],dy[100][100][5],vis[100][100];
char a[100][100];
string st;
inline void init()
{
	for(int x=1;x<=n;x++)
		for(int y=1;y<=m;y++)
		{
			dx[x][y][2]=dx[x][y][4]=x,dy[x][y][1]=dy[x][y][3]=y;
			for(int i=x;i && a[x][y]==a[i][y];i--) dx[x][y][1]=i;
			for(int i=x;i<=n && a[x][y]==a[i][y];i++) dx[x][y][3]=i;
			for(int i=y;i<=m && a[x][y]==a[x][i];i++) dy[x][y][2]=i;
			for(int i=y;i && a[x][y]==a[x][i];i--) dy[x][y][4]=i;
			dx[x][y][1]--,dy[x][y][2]++,dx[x][y][3]++,dy[x][y][4]--;
		}
}
struct node
{
	int x,y,pos,cost;
};
node tmp;
deque<node> q;
inline bool inrange(const int &x,const int &y,const int &i)
{
	return (dx[x][y][i]>=1 && dx[x][y][i]<=n && dy[x][y][i]>=1 && dy[x][y][i]<=m);
}
int main()
{
	read(n),read(m),memset(vis,-1,sizeof(vis));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) read(a[i][j]);
	read(st),st=st+"*",init(),q.clear(),q.push_back((node){1,1,0,0});
	while(!q.empty())
	{
		tmp=q.front(),q.pop_front();
		if(a[tmp.x][tmp.y]==st[tmp.pos])
		{
			if(tmp.pos==st.size()-1)
			{
				cout<<tmp.cost+1<<"\n";
				return 0;
			}
			vis[tmp.x][tmp.y]=tmp.pos+1,q.push_back((node){tmp.x,tmp.y,tmp.pos+1,tmp.cost+1});
		}else
		{
			for(int i=1;i<=4;i++)
				if(inrange(tmp.x,tmp.y,i) && vis[dx[tmp.x][tmp.y][i]][dy[tmp.x][tmp.y][i]]<tmp.pos)
					vis[dx[tmp.x][tmp.y][i]][dy[tmp.x][tmp.y][i]]=tmp.pos,
					q.push_back((node){dx[tmp.x][tmp.y][i],dy[tmp.x][tmp.y][i],tmp.pos,tmp.cost+1});
		}
	}
	return 0;
}
```

---

## 作者：红尘仙 (赞：2)

## $$Keyboarding题解$$

### 【引言】：

更新了一下图片失效的问题

---
### 【题意】 ：
其实题意已经很清楚了，但是还是觉得在叙述一下。首先按键次数和选择次数是不一样的，我一开始就混了，区别提醒一下。还有就是不要忘记结尾处有一个换行符。

---
### 【思路分析】：
**代码就最后附上吧，里面也有点注释，可以帮助理解**
看到这个题，首先看到数据范围 $n ,m \leq 50,$,挺显然得，要么$DP$，要么是搜索，但是仔细看一下这道题，和深搜和宽搜的练习题好像呀，都是什么向上移动呀，向下移动之类的。我们确定是搜索。那我们用搜索去做就$OK$了。

我们可以思考一下其思路。~~force 废话~~。那么就考虑一下暴力怎么写，我们进行搜索的时候，往往就陷入这种沉思之中，先考虑一下搜什么，我的做法是去搜点，搜索每一个能到达的点。并且用$opt$来记录一下现在选择了几个数了，或者说，匹配了几个数了。

那么搜索的终止条件也就是 $if(opt + 1 == len )$ ,那么这时候我们只需要在选择按下键位即可，总共也就是$step+1$（step为到达当前该点的按键次数） ;

如果没到， 那么怎么去搜索， 我们继续向下搜索，假设当前的节点为$now$, 
那么出现两种情况
 1.这一个点的字符和下一个我们要打的一致，
 2.这一个点的字符和下一个我们要打的不一致

--- 
 考虑一致的时候：
  首先我们发现这个时候特别简单，我们需要按下这个键位，这一点横纵坐标也不需要改，改的是$opt和step$,也就是按键次数和选择的均加上一，压入队列即可。$so\ \ easy$吧
  
  考虑不一致的时候：
  这时我们发现 ，如果不一致，那么我们无从下手，因为我们不知道我们下一步往哪里走，不要急，下面再说，我们就假设我们下一个为$next$好吧，我们要看一下这一个点的选择和我们$now$这个点的选择次数，由于这个是从我们这个$now$蹦跶过去的，所以选择次数为$now$决定，$so$,我们也就是可以和上面一样了，压入队列即可。
  
---

接下来就是我们的移动了
看一下这个图：无图无灵魂
![](https://cdn.luogu.com.cn/upload/image_hosting/59csnoh4.png)


1.**向下走**
我们看一下当它向下走的时候，这个时候，我们进行枚举
我们发现了$* \ \ * $这两个，那么我们向下的移动的位置也就是 $now.x , now.y + 1$了，那如果我们黄的也是$ * $呢， 那么我们继续向下走，我们发现无论走到哪里，都是$ * $,那么我们还走他干啥？，我们肯定不会选择呀，$so$,我们选取在那一个方向上第一个不一样的作为该点的下一个移动位置就好了。

那么我们对于下界的枚举就是 
  ```
  for(int i = now.y ; i <= 总行数 ； 一行一行枚举) 
  {
  if(发现不一样的)，记录并且退出 。必须退出
  }
  ```
其他的也一样，就不说了，就只说一下界限吧；
2.**向上走**
($ i = now.y \ \ ;\ \ i ≥ 1 ; i--  $)

3.**想左走**
($ i = now.x \ \ ;\ \ i ≥ 1 ; i--  $)

4. **向右走**
($ i = now.x \ \ ;\ \ i \leq 总列数; i++  $)

---

思路到此就结束了，附代码吧！

### 【code】:
```
/*
 by : Zmonarch
 思路： 1.多写几个函数，头脑清晰
 		2. 暴力搜索，就是麻烦一点（亿点，我就是菜，） 
 知识点 : force  
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <map> 
#define int long long
#define QwQ printf("运行过了\n") ;
#define inf 0x3f 
using namespace std;
const int maxn = 600 ;
inline int read()
{
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)){ if(ch == '-') f = - 1 ; ch = getchar() ; }
	while( isdigit(ch)){ x = x * 10 + ch - '0' ; ch = getchar() ; }
	return x * f ;
} 
int r , c ;
char str[maxn][maxn] , s[10000 + 5] ;
int G[maxn][maxn] , vis[maxn][maxn] ;
struct Point
{
	int x , y , opt , step; //横坐标，纵坐标,选择次数和按键次数
} ;
struct Next //定义下一步的坐标，也就是看向上下左右行不行，行的下一个坐标
{
	int x , y;
} ;
Next nxt[maxn][maxn][6] ;//下一步的坐标 
queue<Point> q ;
int len = 1 ;
void move() //判断移动是否可行
{
	//每一个点都进行判断 
	for(int i = 1 ; i <= r ; i++)
	{
		for(int j = 1 ; j <= c ; j++)
		{
			//判断向左 
			for(int jk = j - 1 ; jk >= 1 ; jk--)
			{
				if(str[i][j] != str[i][jk])
				{
					nxt[i][j][0] = (Next){ i , jk } ;
					break ;
				}
			}
			//判断向右 
			for(int jk = j + 1 ; jk <= c ; jk++) 
			{
				if(str[i][j] != str[i][jk])
				{
					nxt[i][j][1] = (Next){i , jk} ;
					break ;
				}
			}
			//判断向上 
			for(int jk = i - 1 ; jk >= 1 ; jk--)
			{
				if(str[i][j] != str[jk][j])
				{
					nxt[i][j][2] = (Next){jk , j} ;
					break ;
				}
			} 
			//判断向下 
			for(int jk = i + 1 ; jk <= r ; jk++)
			{
				if(str[i][j] != str[jk][j])
				{
					nxt[i][j][3] = (Next){jk , j} ;
					break ;
				}
			}
		}
	}	
}
void prepare()
{
	r = read() , c = read() ;
	len = 1 ;
	for(int i = 1 ; i <= r ; i++)
	{
		scanf("%s" , str[i] + 1) ;
	}
	scanf("%s" , s + 1) ;
	while(s[len]) len ++ ;
 	s[len] = '*' ;//要在结尾处添加一个换行符
	move() ; 
	
} 
void search()
{
	memset(vis , -1 , sizeof(vis)) ;
	queue<Point> q ;
	q.push((Point){1 , 1 , 0 , 0}) ;
	while(!q.empty())
	{
		Point now = q.front() ;
		q.pop();
		int x = now.x , y = now.y ;
		int opt = now.opt , step = now.step ;
		if(str[x][y] == s[opt + 1]) 
		{
			q.push((Point){x , y , opt + 1 , step + 1}) ;
			if(opt + 1 ==  len)
			{
				printf("%d\n" , step + 1 );
				return ;
			}
		}
		else 
		{
			for(int i = 0 ; i <4 ; i++) //枚举一下四个可以走的下一个位置 
			{
				int dx = nxt[x][y][i].x , dy = nxt[x][y][i].y;
				if(dx == 0) continue ;
				if(dy == 0) continue ; 
				if(vis[dx][dy] < opt)
				{
					vis[dx][dy] = opt ;
					q.push((Point){dx , dy ,opt , step + 1}) ;//这个不选择 
				}
			}
		}
	}
}
signed main()
{
	prepare() ; //预处理出能够走位置
	search() ;
	return 0 ;
} 
```

---

## 作者：破忆 (赞：1)

## 【题意】
给定一个$r$行$c$列的在电视上的「虚拟键盘」，通过「上，下，左，右，选择」共$5$个控制键，你可以移动电视屏幕上的光标来打印文本。一开始，光标在键盘的左上角，每次按方向键，光标总是跳到**下一个在该方向上与当前位置不同的字符，若不存在则不移动**。每次按选择键，则将光标所在位置的字符打印出来。求打印给定文本的最少按键次数。

## 【分析】

数据范围不大，暴力$BFS$即可

BFS队列中的元素记录当前位置和当前匹配的位数

但是要求下一个字符与当前位置不同，可能会有大量无用计算

需要预处理出每个位置在每个方向上下一个位置

## 【算法】
BFS

## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,len,vis[55][55],mi[55][55];
char s[10005];
struct point{
	int a,x,y,sx[4],sy[4];
	void init(){//预处理
		sy[0]=sy[2]=y,sx[1]=sx[3]=x;
		for(int i=x;i&&mi[i][y]==a;i--) sx[0]=i;sx[0]--;
		for(int i=x;i<=n&&mi[i][y]==a;i++) sx[2]=i;sx[2]++;
		for(int j=y;j<=m&&mi[x][j]==a;j++) sy[1]=j;sy[1]++;
		for(int j=y;j&&mi[x][j]==a;j--) sy[3]=j;sy[3]--;
	}
}mp[55][55];
struct node{
	int a, b, t, step;
	node(int aa,int bb,int tt,int ss){
		a=aa,b=bb,t=tt,step=ss;
	}
};
void bfs(){
	queue<node> q;
	q.push(node(1, 1, 0, 0));
	while(!q.empty()){//逐个匹配
		node k=q.front();
		q.pop();
		if(mp[k.a][k.b].a==s[k.t]){
			if(k.t==len){
				printf("%d\n",k.step+1);
				return;
			}
			vis[k.a][k.b] =k.t+1;
			q.push(node(k.a,k.b,k.t+1,k.step+1));
			continue;
		}
		for(int i=0;i<4;i++) {
			int dx=mp[k.a][k.b].sx[i],dy=mp[k.a][k.b].sy[i];
			if(dx<1||dx>n||dy<1||dy>m) continue;
			if(dx==k.a&&dy==k.b) continue;
			if(vis[dx][dy]>=k.t) continue;
			vis[dx][dy]=k.t;
			q.push(node(dx,dy,k.t,k.step+1));
		}
	}
}
void work(){
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			mi[i][j]=mp[i][j].a=s[j];
			mp[i][j].x=i,mp[i][j].y=j;
			vis[i][j]=-1;
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++) mp[i][j].init();
	scanf("%s", s);
	len=strlen(s);
	s[len]='*';
	bfs();
}
int main(){
// 	freopen("P6909.in","r",stdin);
// 	freopen("P6909.out","w",stdout); 
	while(scanf("%d%d",&n,&m)==2) work();
	return 0;
}
```


---

## 作者：Bobi2014 (赞：0)

> 我爱 bfs，bfs 爱我。

### 前置知识

- [bfs](https://oi-wiki.org/graph/bfs/)

### 思路

我们可以先把字符串和键盘的字符都映射成数字，方便处理。

我们对整个键盘做 bfs，队列中的对象存储位置（$x$、$y$）、匹配完毕的字符数量、走的步数。

bfs 肯定需要一个存储每种情况下目前最小步数的数组，这个数组如果只有 $2$ 维，也就是只有位置，肯定是不行的，因为在一个位置上匹配了 $1$ 个字符和匹配了 $10$ 个字符是不一样的，所以考虑 $3$ 维，存储位置、匹配的字符数量。

接下来就跟普通 bfs 一样了，只需要注意如果当前键盘上的字符和要匹配的字符串字符一样，要步数加 $1$，匹配字符数也要加 $1$。（如果可以匹配多次，就要匹配多次，建议使用 while）

---

## 作者：sieve (赞：0)

# 题解：[P6909 [ICPC2015 WF] Keyboarding](https://www.luogu.com.cn/problem/P6909)

洛谷上的翻译有锅，这里给出正确的翻译：

给定一个 $r$ 行 $c$ 列的在电视上的「虚拟键盘」，通过「上，下，左，右，选择」共 $5$ 个控制键，你可以移动电视屏幕上的光标来打印文本。一开始，光标在键盘的左上角，每次按方向键，光标总是跳到下一个在该方向上与当前**字符**不同的字符，若不存在则不移动。每次按选择键，则将光标所在位置的字符打印出来。

现在求打印给定文本（要在结尾打印换行符，就是一个 `*`）的最少按键次数。

更完整的翻译？[戳这里](https://www.luogu.com.cn/problem/U388901)。

## 思路

原题可以使用暴力 BFS 通过，不需要预处理。给出的这道题是官方数据，可以卡掉暴力。

首先，我们预处理除每一个点下一个走到的位置。因为有 $4$ 个方向，所以要再开一维。也就是 $nxt_{i,j,k}$ 表示第 $i$ 行 $j$ 列的字符，按照方向数组中 $k$ 的方向，下一个字符，我们还需要将位置存起来，BFS 更新坐标要用。

然后，我们继续用一个 $dis$ 数组。

这次的 $dis$ 数组存的是匹配到的位置。如果 $dis_{i,j}$ 为 $-1$，表示没有匹配到。否则，表示匹配到第 $dis_{i,j}$ 个字符。

对于结束条件，如果匹配完了 $|s|$ 个字符，直接输出答案。否则，判断移动到的点是否合法，然后判断是不是匹配到的字符位置比之前的多，如果是，就更新答案。因为最后还有输出一个换行，所以直接在 $s$ 的后面加上一个 `*` 即可。

我们定义 $nxt_{pos}$ 表示下一个点匹配到的字符。如果这个地方的字符是 $s_{pos + 1}$，表示匹配成功，$nxt_{pos}$ 加一。然后，统计步数的时候，因为匹配到了还要按下确认键，所以，如果匹配成功，则是步数加一，否则是步数加二。

一开始的时候，如果起点不是匹配的，步数是 $0$，$pos$ 是 $0$，否则两个都是 $1$。

## 注意！细节点来了！

即使按照上面的写法，我们只能得到 $80pts$。我就被这里卡了一个多小时。

来看一组 hack 数据：

input:

```
12 11
AAAAAAAAAAA
ABBBBBBBBBA
ABCCCCCCCBA
ABCDDDDDCBA
ABCDEEEDCBA
ABCDEFEDCBA
ABCDEEEDCBA
ABCDDDDDCBA
ABCCCCCCCBA
ABBBBBBBBBA
AAAAAAAAAAA
***********
AAA
```

output:

```
5
```

可是我们的输出是：$9$。

原因是：我们少判断了一个条件。

如果当前位置一直确认就可以，可是，我们会跳来跳去，然后再确认。所以，如果当前位置的字符和 $s_{u.pos + 1}$ 相同，那么，我们就可以直接确认，不需要跳来跳去。所以，我们在出队的时候要加一个判断。就是如果可以匹配，直接进行确认。然后入队。

## 核心代码：

```cpp
if(a[u.x][u.y]==s[u.pos+1])
{
	no tmp={u.x,u.y,u.step+1,u.pos+1};
	if(tmp.pos==len)
	{
		cout<<tmp.step;
		return;
	}
	q.push(tmp);
}
```

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55;
int n,m,len;
int dis[N][N];
string s;
char a[N][N];
struct node{
	char ch;
	int x,y;
};
node nxt[N][N][5];
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,1,-1};
struct no{
	int x,y,step,pos;
};
void print()
{
	cout<<"\n[note]Start to print.\n";
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			cout<<setw(5)<<dis[i][j];
		}
		cout<<'\n';
	}
	cout<<"[note]End to print.\n";
	return;
}
void bfs()
{
	queue<no> q;
	if(a[1][1]==s[1])
	{
		q.push(no{1,1,1,1});
		dis[1][1]=1;
	}
	else
	{
		q.push(no{1,1,0,0});
		dis[1][1]=0;
	}
	if(a[1][1]==s[1]&&len==1)
	{
		cout<<1;
		return;
	}
	while(!q.empty())
	{
		no u=q.front();
		q.pop();
		if(a[u.x][u.y]==s[u.pos+1])
		{
			no tmp={u.x,u.y,u.step+1,u.pos+1};
			if(tmp.pos==len)
			{
				cout<<tmp.step;
				return;
			}
			q.push(tmp);
		}
		int x=u.x,y=u.y;
		for(int i=1;i<=4;++i)
		{
			node nex=nxt[x][y][i];
			int nx=nex.x,ny=nex.y;
			char ch=nex.ch;
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m)
			{
				int nxt_pos=u.pos;
				if(ch==s[u.pos+1]) nxt_pos++;
				if(nxt_pos==len)
				{
					cout<<u.step+1+(nxt_pos!=u.pos);
					return;
				}
				if(nxt_pos>dis[nx][ny])
				{
					dis[nx][ny]=nxt_pos;
					q.push(no{nx,ny,u.step+1+(nxt_pos!=u.pos),nxt_pos});
//					print();
//					cout<<nx<<' '<<ny<<' '<<u.step+1+(nxt_pos!=u.pos)<<'\n';
				}
			}
		}
	}
	return;
}
signed main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			dis[i][j]=-1;
			cin>>a[i][j];
		}
	}
	cin>>s;
	s+='*';
	len=s.length();
	s=' '+s;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			for(int k=1;k<=4;++k)
			{
				nxt[i][j][k]={0,-1,-1}; 
				int nx=i,ny=j;
				while(nx>=1&&nx<=n&&ny>=1&&ny<=m)
				{
					nx+=dx[k],ny+=dy[k]; 
					if(a[nx][ny]!=a[i][j])
					{
						nxt[i][j][k]={a[nx][ny],nx,ny};
						break;
					}
				} 
			}
		}
	}
	bfs();
	return 0;
} 
```

---

## 作者：QinghongLi (赞：0)

# 题意
给定一个 $c$ 行 $r$ 列的字符库，通过移动到不同字符，并使用确认按钮选择字符，拼凑出给定的字符，求最小步数。

# 分析
在 bfs 中我们储存 $4$ 个信息，当前点的 $x$ 坐标，当前点的 $y$ 坐标，当前点已经花费的步数，当前点已经打出了多少个字符（也就是待匹配位置），然后再每次枚举 $4$ 个方向之前，我们先循环尝试选择按钮，以此更新匹配位置，记忆化的储存每个点的最大匹配，如果当前点匹配小于或者等于之前的匹配，那就舍弃当前状态。

显然是 bfs 不过需要注意的东西蛮多的：

1. 需要预处理下一步到达的位置，方法类似 dp。
1. 初始位置需要提前处理。
1. 数据有重复的连续字母，有时候到下一个位置不需要移动的操作。
1. 能用 stl 队列就用队列，我是硬用的数组，开的 $20000000$ 还搞了循环使用才勉强过……

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int bfs[20000004][4];
int next1[99][99][4][2],kk[99][99];
char s[77][77],h[50000007];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    scanf("%s",h+1);
    int len=strlen(h+1);
    h[++len]='*';
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            next1[i][j][0][1]=j;
            next1[i][j][2][0]=i;
            if(s[i][j]!=s[i-1][j])next1[i][j][0][0]=i-1;
            else next1[i][j][0][0]=next1[i-1][j][0][0];
            if(s[i][j]!=s[i][j-1])next1[i][j][2][1]=j-1;
            else next1[i][j][2][1]=next1[i][j-1][2][1];
        }
    for(int i=n;i>0;i--)
        for(int j=m;j>0;j--){
            next1[i][j][1][1]=j;
            next1[i][j][3][0]=i;
            if(s[i][j]!=s[i+1][j])next1[i][j][1][0]=i+1;
            else next1[i][j][1][0]=next1[i+1][j][1][0];
            if(s[i][j]!=s[i][j+1])next1[i][j][3][1]=j+1;
            else next1[i][j][3][1]=next1[i][j+1][3][1];
        }
    int head=1,tail=2;
    bfs[head][0]=bfs[head][1]=bfs[head][2]=1;
    if(s[1][1]==h[1])
        bfs[head][2]=2;
    while(1){
        int x=bfs[head][0],y=bfs[head][1],t=bfs[head][3],v=bfs[head][2];
        while(s[x][y]==h[v])
            t++,v++;
        if(v<=kk[x][y]){
            head++;
            continue;
        }
        kk[x][y]=v;
        if(v==len+1){
            cout<<t+(s[1][1]==h[1]?1:0);
            return 0;
        }
        for(int i=0;i<4;i++){
            int x1=next1[x][y][i][0],y1=next1[x][y][i][1];
            if(x1>0&&y1>0&&x1<=n&&y1<=m&&kk[x1][y1]<v){
                bfs[tail][0]=x1;
                bfs[tail][1]=y1;
                bfs[tail][3]=t+1;    
                bfs[tail][2]=v;
                tail++;
                if(tail>20000000)tail=1;
            }
        }
        head++;
        if(head>=20000000)head=1;
    }
    return 0;
}

```

---

## 作者：niuzh (赞：0)

### 思路

由于数据范围较小，可以用广度优先搜索。

因为光标会到下一个在一个方向上与当前位置上的字符不同的字符，所以可以先预处理出每个位置上下左右能到哪里，方便下面的搜索。

搜索中，如果当前搜到的位置可以打印出字符，那么我们就将其打印出来（由于按按键也算一下，所以直接入队），否则再向 $4$ 个方向搜索下面的字符，由于用的是 `BFS`，所以第一次打印完所有字符一定是最优解。

有可能搜到一个点时当前点已有到此点的更优解，所以可标记一个位置的目前最优解，为 $vis$。当搜到一个点 $(i,j)$ 时，如果当前输出字符小于等于 $vis_{i,j}$ 时（用的是 `BFS`，一定最优解），可直接剪掉。

#### 坑点

最后还要打一个 `*` 与按一下。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[4]= {0,1,0,-1},dy[4]= {1,0,-1,0},N=50+10,M=1e4+10;
struct node
{
	int x,y,i,dis;
};
map<char,int> ascii;
int n,m,a[N][N],l[M],vis[N][N];
pair<int,int> nxt[N][N][4];
string s;
void init()
{
	for (int i=1; i<=10; i++)
	{
		ascii[char('0'+i-1)]=i;
	}
	for (int i=0; i<=25; i++)
	{
		ascii[char('A'+i)]=i+11;
	}
	ascii['-']=37;
	ascii['*']=38;
}
void init_nxt()
{
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			for (int k=0; k<4; k++)
			{
				int x=i+dx[k],y=j+dy[k];
				while (x>0&&x<=n&&y>0&&y<=m&&a[i][j]==a[x][y])
				{
					x+=dx[k];
					y+=dy[k];
				}
				nxt[i][j][k].first=x;
				nxt[i][j][k].second=y;
			}
		}
	}
}
void bfs()
{
	queue<node> q;
	q.push((node){1,1,0,0});
	while (!q.empty())
	{
		node f=q.front();
		q.pop();
		if (a[f.x][f.y]==l[f.i])
		{
			if (f.i==s.size())
			{
				cout<<f.dis+1;
				return;
			}
			vis[f.x][f.y]=f.i;
			f.i++;
			f.dis++;
			q.push(f);
		}
		else
		{
			for (int k=0; k<4; k++)
			{
				int x=nxt[f.x][f.y][k].first,y=nxt[f.x][f.y][k].second;
				if (x<1||x>n||y<1||y>m||vis[x][y]>=f.i)
				{
					continue;
				}
				vis[x][y]=f.i;
				q.push((node){x,y,f.i,f.dis+1});
			}
		}
	}
}
int main()
{
	memset(vis,-1,sizeof(vis));
	init();
	cin>>n>>m;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			char c;
			cin>>c;
			a[i][j]=ascii[c];
		}
	}
	cin>>s;
	for (int i=0; i<s.size(); i++)
	{
		l[i]=ascii[s[i]];
	}
	l[s.size()]=ascii['*'];
	init_nxt();
	bfs();
	return 0;
}
```

---

