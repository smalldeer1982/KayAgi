# 停止問題

## 题目描述

Defunge 程序由一个 $R$ 行 $C$ 列的字符数组组成。下面是一个 Defunge 程序的例子：

```plain
6>--v.
.^--_@
```

Defunge 程序从程序的左上角（即第一行第一列）开始执行。**它的执行方向一开始为"右"**，每次朝着执行方向走一步，**如果走出界了，要跳到另一边**。每走到一个格子上，就要执行这个格子上的命令。 Defunge 程序还有一个存储器，这个存储器只能存储 $[0,15]$ 的一个整数，**存储器一开始存储** $\bold{0}$。

在 Defunge 程序中，有且只有 $11+10=21$ 种命令，下面是它们各自的含义：

- `<`：把执行方向设置为"左"。
- `>`：把执行方向设置为"右"。
- `^`：把执行方向设置为"上"。
- `v`：把执行方向设置为"下"。
- `_`：如果存储器存储的数字是 $0$，就把执行方向设置为"右"，否则设置为"左"。
- `|`：如果存储器存储的数字是 $0$，就把执行方向设置为"下"，否则设置为"上"。
- `?`：把执行方向设置为"上下左右"中的**任意**一个（类似于 dfs 把四个方向全搜一遍）。
- `.`：什么也不做。
- `@`：停止程序。
- `0`-`9`：把存储器设置为这个字符表示的数值。
- `+`：让存储器的数值加 $1$。注意当存储器的数值为 $15$ 时要把它设为 $0$。
- `-`：让存储器的数值减 $1$。注意当存储器的数值为 $0$ 时要把它设为 $15$。

现在，给你一个 Defunge 程序，请判断这个程序是否能停止（即执行到命令`@`）。如果能，输出`YES`，否则输出`NO`。

## 说明/提示

$1\leq R,C\leq 20$，保证程序里只有上文提到的 $21$ 种命令。

# 题解

## 作者：Fijian_Bus (赞：10)

作为一道黄题，题目本身并不难。

### 题目大意

给你一堆符号，每个符号都有特殊含义，按规则进行一顿操作。

理解题意后，还要想吗，这就是模拟啊！打判断语句就完事了！然后零分了。

### 进一步分析

看题目翻译：**把执行方向设置为"上下左右"中的任意一个（类似于深搜把四个方向）全搜一遍。**现在明白了，这题可能是搜索模拟的结合！

当符号是 $?$ 时最复杂，要向四个方向搜索。状态 $x,y$ 改变。故搜索 $(y+dy_i,x+dx_i,z,d)$ 即可。

多提一嘴，为了避免不必要的麻烦，在将数值减 $1$ 的时候，先增加 $15$ 的数值，再模 $16$ 更好。

### 代码实现

没什么复杂的思路，深搜加模拟。直接展示代码。自认为代码是比较易懂的。

```cpp
// At28 Stop
#include <bits/stdc++.h>
using namespace std;
#define N 55
const int dx[5] = {0,1,-1,0,0};
const int dy[5] = {0,0,0,1,-1};
int n, m;
char ch[N][N];
bool vis[N][N][N][N];

bool dfs(int y, int x, int z, int d)
{
	y = (y + n) % n;
	x = (x + m) % m;
	if(vis[y][x][z][d]) return false;
	vis[y][x][z][d] = true;
	// 疯狂打if 
	if(ch[y][x] == '>') d = 1;
	else if(ch[y][x] == '<') d = 2;
	else if(ch[y][x] == '^') d = 4;
	else if(ch[y][x] == 'v') d = 3;
	else if(ch[y][x] == '_') {
		// 分类讨论 
		if(!z) d = 1;
		else d = 2;
	} else if(ch[y][x] == '|') {
		if(!z) d = 3;
		else d = 4;
	} else if(ch[y][x] == '?') {
		// 这里就要向4个方向搜索了
		for(int i = 1; i < 4; i++) {
			if(dfs(y + dy[i], x + dx[i], z, i)) {
				return true;
			}
		}
	} else if(ch[y][x] == '@') return true; // 不用说 
	else if(ch[y][x] == '+') {
		z++;
		z %= 16;
	} else if(ch[y][x] == '-') {
		z += 15;
		z %= 16;
		// 等价于减一 
	} else {
		z = ch[y][x] - '0';
		// numbers
	}
   // 累死了
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
		scanf("%s", ch[i]);
	puts(dfs(0,0,0,1) ? "YES": "NO");
	return 0;
}
```
记住：搜索开始时状态应该为 $(0,0,0,1)$，因为在第一行第一列。

管理员大大，求过~

---

## 作者：Jorisy (赞：7)

这是一道深搜&模拟题。  
首先，对于这个字符方阵，我们要明确方向：
```cpp
const int X[]={0,-1,1,0,0};
const int Y[]={0,0,0,-1,1};
//               ^ v < >
```
以及 `dfs()` 函数的参数：`行 x`、`列 y`、`存储器值 s` 和`方向 fx`。  
接着，对于每个符号，我们可以写出以下代码：
```cpp
switch(a[x][y])
{
	case '>':
		dfs(x+X[4],y+Y[4],s,4);
		break;
	case '<':
		dfs(x+X[3],y+Y[3],s,3);
		break;
	case '^':
		dfs(x+X[1],y+Y[1],s,1);
		break;
	case 'v':
		dfs(x+X[2],y+Y[2],s,2);
		break;
	case '_':
		if(s) dfs(x+X[3],y+Y[3],s,3);
		else dfs(x+X[4],y+Y[4],s,4);
		break;
	case '|':
		if(s) dfs(x+X[1],y+Y[1],s,1);
		else dfs(x+X[2],y+Y[2],s,2);
		break;
	case '?':
		for(int i=1;i<=4;i++)
		{
			dfs(x+X[i],y+Y[i],s,i);
		}
		break;
   case '@':
      cout<<"Yes"<<endl;
      exit(0);//强制退出程序
	case '.':
		dfs(x+X[fx],y+Y[fx],s,fx);
		break;
	case '+':
		s++;
		if(s>15) s=0;
		dfs(x+X[fx],y+Y[fx],s,fx);
		break;
	case '-':
		s--;
		if(s<0) s=15;
		dfs(x+X[fx],y+Y[fx],s,fx);
		break;
	default://剩下的情况就是数字
		s=a[x][y]-48;
		dfs(x+X[fx],y+Y[fx],s,fx);
}
```
经过观察和计算，可以发现，字符方阵就像**滚动条**，因此在每次函数开头，应附上如下代码：
```cpp
while(x<1) x+=r;
while(r<x) x-=r;
while(y<1) y+=c;
while(c<y) y-=c;
```
对于可结束的，我们可以判定到 `@`；那对于不可结束的呢？  
对于不可结束，你需要知道以下几点：

- 那一定是个死循环；
- 两次在位置 $[x,y]$ 时，其 $fx$ 和 $s$ 的值**两次都不变**。

因此，我们要开个“四维 `bool` 数组”来存储，每一“维”，都分别表示一个参数。
```cpp
bool b[25][25][20][5];//每一维分别为：x、y、s 和 fx
```
那么，每到一次函数，若目前该值已出现过，则 `return`；否则，将该值变为 `true`。  
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int X[5]={0,-1,1,0,0};
const int Y[5]={0,0,0,-1,1};
int r,c;
char a[25][25];
bool b[25][25][20][5];

void dfs(int x,int y,int s,int fx)
{
	while(x<1) x+=r;
   while(r<x) x-=r;
   while(y<1) y+=c;
   while(c<y) y-=c;
   //cout<<x<<' '<<y<<' '<<s<<' '<<fx<<endl;
	if(b[x][y][s][fx]) return;
	if(a[x][y]=='@')//@ 也可以特判
	{
		cout<<"YES"<<endl;
		exit(0);
	}
	b[x][y][s][fx]=true;//标记
	switch(a[x][y])
	{
		case '>':
			dfs(x+X[4],y+Y[4],s,4);
			break;
		case '<':
			dfs(x+X[3],y+Y[3],s,3);
			break;
		case '^':
			dfs(x+X[1],y+Y[1],s,1);
			break;
		case 'v':
			dfs(x+X[2],y+Y[2],s,2);
			break;
		case '_':
			if(s) dfs(x+X[3],y+Y[3],s,3);
			else dfs(x+X[4],y+Y[4],s,4);
			break;
		case '|':
			if(s) dfs(x+X[1],y+Y[1],s,1);
			else dfs(x+X[2],y+Y[2],s,2);
			break;
		case '?':
			for(int i=1;i<=4;i++)
			{
				dfs(x+X[i],y+Y[i],s,i);
			}
			break;
		case '.':
			dfs(x+X[fx],y+Y[fx],s,fx);
			break;
		case '+':
			s++;
			if(s>15) s=0;
			dfs(x+X[fx],y+Y[fx],s,fx);
			break;
		case '-':
			s--;
			if(s<0) s=15;
			dfs(x+X[fx],y+Y[fx],s,fx);
			break;
		default:
			s=a[x][y]-48;
			dfs(x+X[fx],y+Y[fx],s,fx);
	}
   //不可以回溯
}

int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cin>>a[i][j];
		}
	}
	dfs(1,1,0,4);//深搜开始！
	cout<<"NO"<<endl;//没输出'YES'则输出'NO'
	return 0;
}
```
最后有一点要提醒一下：**末尾一定要换行！**

---

## 作者：_caiji_ (赞：4)

本题使用 dfs 就行了。

_upd on 2021/2/12：修改了排版和马蜂。_

### 做题思路
1. 打四个方向的表。
2. 定义函数 dfs ，传入四个参数 $x,y,dir,cnt$，分别表示现在在哪里、哪个方向、存储器里的值.
3. 先给 $x$ 和 $y$ 取模，注意取模的方法。为了防止负数取模，如果你的下标从 $0$ 开始，你可以使用 $x=(x+n)\mod n$，反之使用 while 循环模拟。
4. 再判断一下这个位置是不是搜过了。
5. 然后判一下这个格子是不是 $\texttt{"@"}$，如果是，就输出 $\texttt{"YES"}$，并`exit(0)`。
6. 最后暴力判断每一种命令，继续搜下去。
7. 主函数里输入并调用 dfs，如果 dfs 搜完了程序还没结束，说明不能停止（如果能停下来就会结束程序），输出 $\texttt{"NO"}$，注意换行。

### 代码实现
```cpp
#include <cstdio>
#include <cstdlib>//这里有exit(0)
using namespace std;
//                > v < ^ 这里和题目方向顺序不太一样，但对应好就行了
const int dx[]={0,0,1,0,-1},
          dy[]={0,1,0,-1,0};
int n,m;
char a[110][110];
bool vis[110][110][110][110];//vis[x][y][dir][cnt]表示这个情况是否搜过
void dfs(int x,int y,int dir,int cnt){//方向和存储器当参数传，就不用回溯了
    while(x<1) x+=n;
    while(n<x) x-=n;
    while(y<1) y+=m;
    while(m<y) y-=m;//用while代替取模
  	if(vis[x][y][dir][cnt]) return ;//如果这种情况搜过了直接return
    if(a[x][y]=='@') puts("YES"),exit(0);//搜到停止就结束程序
    vis[x][y][dir][cnt]=1;//标记搜过了
    switch(a[x][y]){//开始暴力判断
        case '>':dfs(x+dx[1],y+dy[1],1,cnt);break;
        case 'v':dfs(x+dx[2],y+dy[2],2,cnt);break;
        case '<':dfs(x+dx[3],y+dy[3],3,cnt);break;
        case '^':dfs(x+dx[4],y+dy[4],4,cnt);break;
		//四种方向
        case '+':dfs(x+dx[dir],y+dy[dir],dir,(cnt+1)%16);break;
        case '-':dfs(x+dx[dir],y+dy[dir],dir,(cnt-1+16)%16);break;
		//加和减，其中减法要+16的原因是防止出现-1%16的情况
        case '|':if(cnt==0) dfs(x+dx[2],y+dy[2],2,cnt);
                 else dfs(x+dx[4],y+dy[4],4,cnt);
        		 break;
        case '_':if(cnt==0) dfs(x+dx[1],y+dy[1],1,cnt);
                 else dfs(x+dx[3],y+dy[3],3,cnt);
        		 break;
		//根据存储的值确定方向
        case '.':dfs(x+dx[dir],y+dy[dir],dir,cnt);break;
        case '?':for(int i=1;i<=4;i++) 
          			dfs(x+dx[i],y+dy[i],i,cnt);
        		 break;
		//?直接枚举4种方向
        default:dfs(x+dx[dir],y+dy[dir],dir,a[x][y]-'0');break;
        //都对不上就是数字了
    }
    //vis[x][y][dir][cnt]=0;//和AT1350一样，不能回溯，不然会TLE
  	//原因：这种状态不能停止的话，后面再搜到这里就会再搜一次，浪费很多计算，我们可以直接剪掉这部分的枝
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
    dfs(1,1,1,0);
    puts("NO");//puts自带换行，当然你也可以printf("NO\n")
    return 0;
}
```
### 后记
```cpp
exit(0);
```
这个函数在`cstdlib`中，作用是直接结束程序。在这题里，如果搜到能停止，就会直接结束程序，根本没有后面`puts("NO")`的事。

---

## 作者：HYdroKomide (赞：4)

# **正文**
## 题意：
本题算是一道比较简单的紫题了，可以算一道模拟与搜索的结合，就按照原题中的方法搜索即可。这个翻译必须要吐槽一下，其中```什么都不做```代表按照原来的方向和原来的数值继续行走。
## 程序：
本题的代码比较清新，代码解释详见注释：
```cpp
#include<cstdio>
int n,m;
const int dx[]={0,0,1,-1};//定义方向（注意这里很容易疏忽大意，建议用草稿纸仔细算一遍，本蒟蒻就在这里卡了半个小时）
const int dy[]={1,-1,0,0};
char a[50][50];
bool vis[50][50][4][16];//表示坐标已访问的数组，注意一个坐标可以被多次访问，但是如果两次访问的方向和“值”都一样就代表死循环
bool run(int x,int y,int d,int num){
    x=(x+n)%n,y=(y+m)%m;//这里也很容易出错，因为如果x或者y搜到负数就必须先加上n或者m，所以不能直接写x%=n,y%=n;
    if(vis[x][y][d][num])return 0;
    vis[x][y][d][num]=true;//在这个状态下已经经过了这个坐标
    if     (a[x][y]=='>')d=0;
    else if(a[x][y]=='<')d=1;
    else if(a[x][y]=='v')d=2;
    else if(a[x][y]=='^')d=3;
    else if(a[x][y]=='_')d=num?1:0;
    else if(a[x][y]=='|')d=num?3:2;//改变方向
    else if(a[x][y]=='?'){//如果是?就向四个方向搜索
		for(int i=0;i<4;i++)
			if(run(x+dx[i],y+dy[i],i,num))
				return 1;
		return 0;
	}
    else if(a[x][y]=='@')return 1;//见到@直接输出
    else if(a[x][y]>='0'&&a[x][y]<='9')num=a[x][y]-'0';//见到数字就将其赋值给num
    else if(a[x][y]=='-')num=(num+15)%16;//为了保证符号恒正，这里使用+15再%16的方式给这个值-1
    else if(a[x][y]=='+')num=(num+ 1)%16;//同理，用+1再%16的方法给此值+1
	return run(x+dx[d],y+dy[d],d,num);//继续往下搜索
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%s",a[i]);//将字符数组以字符串形式读入
    printf(run(0,0,0,0)?"YES\n":"NO\n");
    return 0;
}

```
## P.S.
本篇代码逻辑上与楼上代码逻辑非常接近，本蒟蒻只是稍微优化了一下码风和逻辑上的小细节，希望这能够给您带来更好的阅读体验。
# **THE END**
-UPGRADE 2021.1.25：删去了代码的不必要部分

---

## 作者：ChikHid (赞：3)

#### ~~我又来写题解了~~

[题目传送](https://www.luogu.com.cn/problem/AT28)

[博客食用](https://www.luogu.com.cn/blog/XJK/solution-at28)

---
### 做题思路
首先分析题目，这是一道简单的模拟题，$R,C≤20$，只有$21$种情况和$4$个方向，可以使用dfs(深搜)，当然也可以使用bfs(广搜)。

**注意：标记点时需要记录点的位置、当前存储器内的数值和方向** 
***
### 那就看代码吧
~~xjk出品，必属精品~~

dfs代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int dx[5]={0,-1,0,1,0};
int dy[5]={0,0,-1,0,1};//四个方向:1:上，2:左，3:下，4:右
int f[25][25][20][5],n,m;//f数组用来标记当前状态是否到达过
char a[25][25];//a数组用来记录Defunge程序字符

bool dfs(int x,int y,int z,int c)//x,y表示位置，z表示数值，c表示方向
{
	if(x==0)//防止越界
		x=n;
	if(x>n)//防止越界
		x=1;
	if(y==0)//防止越界
		y=m;
	if(y>m)//防止越界
		y=1;
	if(z==-1)//防止越界
		z=15;
	if(z==16)//防止越界
		z=0;
	if(f[x][y][z][c])//如果之前有过这种状态就说明有死循环
		return false;
	f[x][y][z][c]=1;//标记
	switch(a[x][y])//判断21种命令
	{
		case '<':
			return dfs(x+dx[2],y+dy[2],z,2);//向左
		case '>':
			return dfs(x+dx[4],y+dy[4],z,4);//向右
		case '^':
			return dfs(x+dx[1],y+dy[1],z,1);//向上
		case 'v':
			return dfs(x+dx[3],y+dy[3],z,3);//向下
		case '_':
			if(z)//如果存储器存储的数字不是0
				return dfs(x+dx[2],y+dy[2],z,2);//向左
			else
				return dfs(x+dx[4],y+dy[4],z,4);//向右
		case '|':
			if(z)//如果存储器存储的数字不是0
				return dfs(x+dx[1],y+dy[1],z,1);//向上
			else
				return dfs(x+dx[3],y+dy[3],z,3);//向下
		case '?':
			return (dfs(x+dx[1],y+dy[1],z,1)||dfs(x+dx[2],y+dy[2],z,2)||dfs(x+dx[3],y+dy[3],z,3)||dfs(x+dx[4],y+dy[4],z,4));//四个方向
		case '.':
			return dfs(x+dx[c],y+dy[c],z,c);//状态不变
		case '@':
			return true;//程序结束
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return dfs(x+dx[c],y+dy[c],a[x][y]-48,c);//数字
		case '+':
			return dfs(x+dx[c],y+dy[c],z+1,c);//数值加一
		case '-':
			return dfs(x+dx[c],y+dy[c],z-1,c);//数值减一
	}
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	cout<<((dfs(1,1,0,4))?"YES":"NO")<<endl;//dfs返回值为true说明可以结束程序，输出YES，否则说明不能结束程序，输出NO
	return 0;
}
```
bfs代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int dx[5]={0,-1,0,1,0};
int dy[5]={0,0,-1,0,1};//四个方向:1:上，2:左，3:下，4:右
int f[25][25][20][5],n,m,h,t;//f数组用来标记当前状态是否到达过
char a[25][25];//a数组用来记录Defunge程序字符
int x[100005],y[100005],s[100005],c[100005];//x,y表示位置，s表示数值，c表示方向

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	h=1,t=2;//广搜预处理
	x[h]=1,y[h]=1,s[h]=0,c[h]=4;//广搜预处理
	while(h<t)
	{
		if(x[h]==0)//防止越界
			x[h]=n;
		if(x[h]>n)//防止越界
			x[h]=1;
		if(y[h]==0)//防止越界
			y[h]=m;
		if(y[h]>m)//防止越界
			y[h]=1;
		if(s[h]==-1)//防止越界
			s[h]=15;
		if(s[h]==16)//防止越界
			s[h]=0;
		if(a[x[h]][y[h]]=='@')//可以结束Defunge程序
		{
			cout<<"YES"<<endl;
			return 0;
		}
		if(!f[x[h]][y[h]][s[h]][c[h]])如果当前状态没有出现过
			switch(a[x[h]][y[h]])//判断21种命令
			{
				case '<':
					x[t]=x[h]+dx[2],y[t]=y[h]+dy[2],s[t]=s[h],c[t++]=2;//向左
					break;
				case '>':
					x[t]=x[h]+dx[4],y[t]=y[h]+dy[4],s[t]=s[h],c[t++]=4;//向右
					break;
				case '^':
					x[t]=x[h]+dx[1],y[t]=y[h]+dy[1],s[t]=s[h],c[t++]=1;//向上
					break;
				case 'v':
					x[t]=x[h]+dx[3],y[t]=y[h]+dy[3],s[t]=s[h],c[t++]=3;//向下
					break;
				case '_':
					if(s[h])//如果存储器存储的数字不是0
						x[t]=x[h]+dx[2],y[t]=y[h]+dy[2],s[t]=s[h],c[t++]=2;//向左
					else
						x[t]=x[h]+dx[4],y[t]=y[h]+dy[4],s[t]=s[h],c[t++]=4;//向右
					break;
				case '|':
					if(s[h])//如果存储器存储的数字不是0
						x[t]=x[h]+dx[1],y[t]=y[h]+dy[1],s[t]=s[h],c[t++]=1;//向上
					else
						x[t]=x[h]+dx[3],y[t]=y[h]+dy[3],s[t]=s[h],c[t++]=3;//向下
					break;
				case '?':
					x[t]=x[h]+dx[1],y[t]=y[h]+dy[1],s[t]=s[h],c[t++]=1;
					x[t]=x[h]+dx[2],y[t]=y[h]+dy[2],s[t]=s[h],c[t++]=2;
					x[t]=x[h]+dx[3],y[t]=y[h]+dy[3],s[t]=s[h],c[t++]=3;
					x[t]=x[h]+dx[4],y[t]=y[h]+dy[4],s[t]=s[h],c[t++]=4;//四个方向
					break;
				case '.':
					x[t]=x[h]+dx[c[h]],y[t]=y[h]+dy[c[h]],s[t]=s[h],c[t++]=c[h];//状态不变
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					x[t]=x[h]+dx[c[h]],y[t]=y[h]+dy[c[h]],s[t]=a[x[h]][y[h]]-48,c[t++]=c[h];//数字
					break;
				case '+':
					x[t]=x[h]+dx[c[h]],y[t]=y[h]+dy[c[h]],s[t]=s[h]+1,c[t++]=c[h];//数值加一
					break;
				case '-':
					x[t]=x[h]+dx[c[h]],y[t]=y[h]+dy[c[h]],s[t]=s[h]-1,c[t++]=c[h];//数值减一
					break;
			}
		f[x[h]][y[h]][s[h]][c[h]]=1;//标记
		h++;
	}
	cout<<"NO"<<endl;
	return 0;
}
```


---

## 作者：tribool4_in (赞：2)

此题就是道模拟，如果没有 ```?``` 则可以直接 ```while``` 循环模拟，但是有 ```?```，就要用深搜了（话说题中不是说了吗）。

把位置、方向、存储器的值都作为参数，然后开始搜索，一旦找到了 ```@``` 就输出 YES 并停止。如果搜到了一个**已经到过的点且当前方向与存储器的值都已经有过**，则说明会死循环，```return```。

代码：

```
#include <bits/stdc++.h>
const int N = 1e2 + 10;
using namespace std;
const int dx[5] = {0, 1, 0, -1}, dy[5]= {1, 0, -1, 0};
int n, m;
char s[N][N];
bool vis[N][N][N][N];
void dfs(int x, int y, int dir, int rec) {
	if (x < 1) x += n;
	if (x > n) x -= n;
	if (y < 1) y += m;
	if (y > m) y -= m;
	if (vis[x][y][dir][rec]) return;
	if (s[x][y] == '@') {
		puts("YES");
		exit(0);
	}
	vis[x][y][dir][rec] = 1;
	switch (s[x][y]) {
		case '>':
			dfs(x+dx[0], y+dy[0], 0, rec);
			break;
		case 'v':
			dfs(x+dx[1], y+dy[1], 1, rec);
			break;
		case '<':
			dfs(x+dx[2], y+dy[2], 2, rec);
			break;
		case '^':
			dfs(x+dx[3], y+dy[3], 3, rec);
			break;
		case '+':
			dfs(x+dx[dir], y+dy[dir], dir, (rec + 1) % 16);
			break;
		case '-':
			dfs(x+dx[dir], y+dy[dir], dir, (rec - 1 + 16) % 16);
			break;
		case '|':
			if (rec) dfs(x+dx[3], y+dy[3], 3, rec);
			else dfs(x+dx[1], y+dy[1], 1, rec);
			break;
		case '_':
			if(rec) dfs(x+dx[2], y+dy[2], 2, rec);
			else dfs(x+dx[0], y+dy[0], 0, rec);
			break;
		case '.':
			dfs(x+dx[dir], y+dy[dir], dir, rec);
			break;
		case '?':
			for(int i = 0; i < 4; i++) dfs(x+dx[i], y+dy[i], i, rec);
			break;
		default:
			dfs(x+dx[dir], y+dy[dir], dir, s[x][y]-'0');
			break;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
	}
	dfs(1, 1, 0, 0);
	puts("NO");
	return 0;
}
```

附：所以为啥存储器的减 1 写成这样也可以过啊，数据太水了吧（

```
dfs(x+dx[dir], y+dy[dir], dir, (rec - 1) % 16);
```

---

## 作者：Texas_the_Omertosa (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT28)

卡了我 6 天...（呜呜呜

### 0x01 思路

其实此题更像模拟，模拟这个程序执行过程。

不能结束是因为什么？死循环呗！

啥是死循环？在同一个地方用了两遍同样的值与朝向呗！

那我们就可以用一个下标分别为横坐标、纵坐标、值与朝向的四维数组标记。若发现为真，即为死循环，然后按题意一个一个执行操作即可。

### 0x02 AC Code

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int fx[5]={0,0,0,-1,1};
int fy[5]={0,-1,1,0,0};
char a[25][25];
bool v[25][25][17][5];
inline bool dfs(int x,int y,int num,int cx)
{
	x=(x+n)%n;
	y=(y+m)%m;//防止越界
	if(v[x][y][num][cx])return 0;//死循环
	v[x][y][num][cx]=1;//标记
	if(a[x][y]=='<')//左
	{
		cx=1;
	}
	else if(a[x][y]=='>')//右
	{
		cx=2;
	}
	else if(a[x][y]=='^')//上
	{
		cx=3;
	}
	else if(a[x][y]=='v')//下
	{
		cx=4;
	}
	else if(a[x][y]=='_')
	{
		if(!num)
		{
			cx=2;
		}
		else
		{
			cx=1;
		}
	}
	else if(a[x][y]=='|')
	{
		if(!num)
		{
			cx=4;
		}
		else
		{
			cx=3;
		}
	}
	else if(a[x][y]=='?')
	{
		for(int i=1;i<=4;i++)
		{
			if(dfs(x+fx[i],y+fy[i],num,i))
			{
				return 1;
			}
		}
		return 0;
	}
	else if(a[x][y]=='.');
	else if(a[x][y]=='@')
	{
		return 1;
	}
	else if(a[x][y]=='+')
	{
		num++;
		num%=16;
	}
	else if(a[x][y]=='-')
	{
		num+=15;
		num%=16;
	}
	else
	{
		num=a[x][y]-'0';
	}
	return dfs(x+fx[cx],y+fy[cx],num,cx);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	if(dfs(0,0,0,2))
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}
	return 0;
}
```

完结~（暗示

---

## 作者：0x3F (赞：1)

模拟 + DFS。

关于 `什么都不做` ：指的是保持**现在的方向和存储器的值不变**。

关于 `+` 和 `-`：意思是**对 $16$ 取模**。

还有，如果**走出界**了，要**跳到另一边**。

还有，DFS 状态不仅要存储位置，**还要存储当时的方向和当时存储器的值。($vis$ 数组也要多开两维存储！)**

最后，为了方便起见，在我的代码中，一旦搜到了 `@`，就**直接使用 `exit(0)` 来退出程序。**

没了。

```cpp
#include <bits/stdc++.h>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ALL 4
using namespace std;
int r, c;
char arr[22][22];
bool vis[22][22][16][4];

inline void dfs(int x, int y, int val, int dir) {
	if (vis[x][y][val][dir]) return;
	vis[x][y][val][dir] = 1;
	switch (arr[x][y]) {
		case '<': {
			dir = LEFT;
			break;
		}
		case '>': {
			dir = RIGHT;
			break;
		}
		case '^': {
			dir = UP;
			break;
		}
		case 'v': {
			dir = DOWN;
			break;
		}
		case '_': {
			if (val) dir = LEFT;
			else dir = RIGHT;
			break;
		}
		case '|': {
			if (val) dir = UP;
			else dir = DOWN;
			break;
		}
		case '.': {
			break;
		}
		case '@': {
			cout << "YES" << endl;
			exit(0);
			break;
		}
		case '+': {
			if (val == 15) val = 0;
			else val++;
			break;
		}
		case '-': {
			if (val == 0) val = 15;
			else val--;
			break;
		}
		case '?': {
			dir = ALL;
			break;
		}
		default: {
			val = arr[x][y] - 48;
			break;
		}
	}
	if (dir == ALL) {
		x--;
		if (x == 0) x = r;
		dfs(x, y, val, UP);
		x++;
		if (x == r+1) x = 1;
		
		x++;
		if (x == r+1) x = 1;
		dfs(x, y, val, DOWN);
		x--;
		if (x == 0) x = r;
		
		y--;
		if (y == 0) y = c;
		dfs(x, y, val, LEFT);
		y++;
		if (y == c+1) y = 1;
		
		y++;
		if (y == c+1) y = 1;
		dfs(x, y, val, RIGHT);
		y--;
		if (y == 0) y = c;
	} else {
		switch (dir) {
			case UP: {
				x--;
				if (x == 0) x = r;
				break;
			}
			case DOWN: {
				x++;
				if (x == r+1) x = 1;
				break;
			}
			case LEFT: {
				y--;
				if (y == 0) y = c;
				break;
			}
			case RIGHT: {
				y++;
				if (y == c+1) y = 1;
				break;
			}
		}
		dfs(x, y, val, dir);
	}
}
int main() {
	cin >> r >> c;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> arr[i][j];
		}
	}
	dfs(1, 1, 0, RIGHT);
	cout << "NO" << endl;
	return 0;
}
```


---

## 作者：Iron_Heart (赞：1)

## 思路

搜索 + 模拟。

一开始从起始点开始搜，然后根据当前点的字符和题意变换方向和存储器的数值。

一搜到 `@` 就返回 `true`。

如果遍历完所有情况都没有搜到 `@`，返回 `false`。

其他细节见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int dx[] = {0, 1, -1, 0};
const int dy[] = {-1, 0, 0, 1};
int n, m;
char mp[25][25];
bool vis[25][25][5][18];

// 0 是往左，1 是往下，2 是往上，3 是往右
bool dfs(int x, int y, int d, int num) {
    // 走到另一边
    x = (x - 1 + n) % n + 1;
    y = (y - 1 + m) % m + 1;
    if (vis[x][y][d][num]) {
        return 0;
    }
    vis[x][y][d][num] = 1;
    if (mp[x][y] == '@') {
        return 1;
    } else if (mp[x][y] == '<') {
        d = 0;
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (mp[x][y] == '>') {
        d = 3;
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (mp[x][y] == '^') {
        d = 2;
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (mp[x][y] == 'v') {
        d = 1;
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (mp[x][y] == '_') {
        if (!num) {
            d = 3;
        } else {
            d = 0;
        }
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (mp[x][y] == '|') {
        if (!num) {
            d = 1;
        } else {
            d = 2;
        }
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (mp[x][y] == '?') {
        // 遍历四个方向
        for (int i = 0; i < 4; ++i) {
            if (dfs(x + dx[i], y + dy[i], i, num)) {
                return 1;
            }
        }
        return 0;
    } else if (mp[x][y] == '.') {
        return dfs(x + dx[d], y + dy[d], d, num);
    } else if (isdigit(mp[x][y])) {
        // isdigit(x) 就是判断字符 x 是否为数字
        // x - '0' 的作用是将字符转为数字
        return dfs(x + dx[d], y + dy[d], d, mp[x][y] - '0');
    } else if (mp[x][y] == '+') {
        ++num;
        if (num == 16) {
            num = 0;
        }
        return dfs(x + dx[d], y + dy[d], d, num);
    } else {
        --num;
        if (num == -1) {
            num = 15;
        }
        return dfs(x + dx[d], y + dy[d], d, num);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        // 从索引 1 开始输入
        scanf("%s", mp[i] + 1);
    }
    puts(dfs(1, 1, 3, 0) ? "YES" : "NO");
    return 0;
}
```


---

## 作者：a1029 (赞：0)

### 思路是深搜加模拟。
按题意模拟 12 个操作。

**特别要注意的是**，数值的处理应该是这样的：

加一：
```cpp
num++;
num %= 16;
```
减一：
```cpp
num += 15;
num %= 16;
```
本题的最大坑点就在这里，按常规的不行，~~我就因为这 WA 了好多次。~~

且本题解的不同之处在于**暴力五维数组**，加上一个数值的下标，比较省时。

## Code
```
#include <bits/stdc++.h>
using namespace std;

char g[25][25];
bool vis[25][25][20][4][4];
int m, n, num, dx = 0, dy = 1;

void move(int x, int y) {
	if (x > m) x = 1;
	if (y > n) y = 1;
	if (x < 1) x = m;
	if (y < 1) y = n;
	if (vis[x][y][num][dx + 1][dy + 1]) return;
	char c = g[x][y];
	vis[x][y][num][dx + 1][dy + 1] = true;
	if (c == '>') {
		dx = 0;
		dy = 1;
		move(x, y + 1);
	}
	if (c == '<') {
		dx = 0;
		dy = -1;
		move(x, y - 1);
	}
	if (c == '^') {
		dx = -1;
		dy = 0;
		move(x - 1, y);
	}
	if (c == 'v') {
		dx = 1;
		dy = 0;
		move(x + 1, y);
	}
	if (c == '_') {
		if (num == 0) {
			dx = 0;
			dy = 1;
			move(x, y + 1);
		}
		else {
			dx = 0;
			dy = -1;
			move(x, y - 1);
		}
	}
	if (c == '|') {
		if (num == 0) {
			dx = 1;
			dy = 0;
			move(x + 1, y);
		}
		else {
			dx = -1;
			dy = 0;
			move(x - 1, y);
		}
	}
	if (c == '?') {
		dx = 0;
		dy = 1;
		move(x, y + 1);
		dx = 0;
		dy = -1;
		move(x, y - 1);
		dx = -1;
		dy = 0;
		move(x - 1, y);
		dx = 1;
		dy = 0;
		move(x + 1, y);
	}
	if (c == '.') move(x + dx, y + dy);
	if (c == '@') {
		puts("Yes");
		exit(0);
	}
	if (isdigit(c)) {
		num = c - '0';
		move(x + dx, y + dy);
	}
	if (c == '+') {
		num++;
		num %= 16;
		move(x + dx, y + dy);
	}
	if (c == '-') {
		num += 15;
		num %= 16;
		move(x + dx, y + dy);
	}
}

int main()
{
	cin >> m >> n;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> g[i][j];
	move(1, 1);
	puts("No");
	return 0;
}

```


---

