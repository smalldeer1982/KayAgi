# Shortest path of the king

## 题目描述

国王独自一人在国际象棋棋盘上。尽管他很孤独，但他并不会灰心，因为他有国家大事要做。例如，他必须对方格 $t$ 进行访问。因为国王没有浪费时间的习惯，所以他想从目前的位置（方格 $s$）上出发，走最少的步数。请你帮他做这件事。

在一次移动中，国王可以到达与他目前所在方格有共同的边或共同的顶点的方格里（通常情况下，他可以移动到 $8$ 个不同的方格里）。

## 样例 #1

### 输入

```
a8
h1
```

### 输出

```
7
RD
RD
RD
RD
RD
RD
RD
```

# 题解

## 作者：Loner_Knowledge (赞：26)

这道题是一道贪心模拟题

---

首先读题可以知道国王最多有八个可以移动的方向：`L,R,U,D,LU,LD,RU,RD`，那么当前位置与终点不同时就要优先走斜线，模拟一下即可知道最短路径的长度为起点与终点横坐标的差的绝对值与纵坐标的差的绝对值中较大的那一个。


由于走斜线的格式均是`L或R+U或D`，输出移动动作时可以将走斜线分解为横坐标走一步加纵坐标走一步。


```cpp
#include<cstdio>
char s1[3],s2[3];
int main() {
    int x,y;
    char cx,cy;
    scanf("%s%s",s1,s2);
    x=s1[0]-s2[0];
    y=s1[1]-s2[1];    //取坐标之差
    cx=x<0? 'R':'L';
    cy=y<0? 'U':'D';    //根据坐标差的正负选择方向
    if(x<0)
        x=-x;
    if(y<0)            //相当于取绝对值
        y=-y;
    printf("%d\n",x>y? x:y);
    for(;x||y;putchar('\n')) {    //循环条件，当前点与终点之间有距离
        if(x) {
            --x;
            putchar(cx);    //横坐标走一步
        }
        if(y) {
            --y;
            putchar(cy);    //纵坐标走一步
        }
    }
    return 0;
}
```

---

---

## 作者：pzc2004 (赞：17)

[题目传送门](https://www.luogu.org/problem/CF3A)

思路：这题搜索啥的全都不用，首先我们的知道国王移动到目标点的步数就是两点间的切比雪夫距离，啥是切比雪夫距离？切比雪夫距离就是两点间x坐标差的绝对值和y坐标差的绝对值的最大值。
$$dis_{a,b}=max(abs(x_a-x_b),abs(y_a-y_b))$$
然后模拟即可，先走斜的，再走直的。

代码：
```
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int main()
{
	cin>>s1>>s2;
	int x1=s1[0]-'a'+1,y1=s1[1]-'0',x2=s2[0]-'a'+1,y2=s2[1]-'0';//计算两个点的坐标
	int dis=max(abs(x1-x2),abs(y1-y2));//计算两点的切比雪夫距离
	printf("%d\n",dis);
	while(dis--)
	{
		if(x1>x2 && y1>y2){x1--;y1--;printf("LD\n");continue;}//判断一下
		if(x1>x2 && y1==y2){x1--;printf("L\n");continue;}
		if(x1>x2 && y1<y2){x1--;y1++;printf("LU\n");continue;}
		if(x1==x2 && y1>y2){y1--;printf("D\n");continue;}
		if(x1==x2 && y1<y2){y1++;printf("U\n");continue;}
		if(x1<x2 && y1>y2){x1++;y1--;printf("RD\n");continue;}
		if(x1<x2 && y1==y2){x1++;printf("R\n");continue;}
		if(x1<x2 && y1<y2){x1++;y1++;printf("RU\n");continue;}
	}
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：communist (赞：15)

#### 一句话题意：
在8 * 8的棋盘上，输出用最少步数从起点走到终点的方案

数据很小，可以广搜无脑解决

#### 定义数据结构体
```
struct pos{
    int x,y,s;		//x、y表示横纵坐标，s表示步数
    string move[100];	//存储每一步的方案
};
```
#### 移动时新旧状态传递
```
pos u=q.front();
q.pop();
for(int i=0;i<8;i++)
{
    pos th;
    th.x=u.x+dx[i];
    th.y=u.y+dy[i];
    th.s=u.s+1;
    for(int i=1;i<=u.s;i++)
        th.move[i]=u.move[i];
    th.move[th.s]=st[i];
}
```
#### 判断是否可以拓展
```
if(th.x<1||th.x>8||th.y<1||th.y>8||vis[th.x][th.y])
//越界或已访问
     continue;
```
#### 打标记，入队
```
vis[th.x][th.y]=1;	//标记为已访问
q.push(th);
```
### 完整代码
```
#include<iostream>
#include<queue>
using namespace std;
struct pos{
    int x,y,s;
    string move[100];
};
queue<pos>q;
int dx[8]={-1,1,0,0,-1,-1,1,1};
int dy[8]={0,0,1,-1,1,-1,1,-1};
string st[8]={"L","R","U","D","LU","LD","RU","RD"};
bool vis[10][10];
int x,y;
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    q.push((pos){s1[0]-'a'+1,s1[1]-'0',0,""});
    vis[s1[0]-'a'+1][s1[1]-'0']=1;
    x=s2[0]-'a'+1,y=s2[1]-'0';
    if(vis[x][y])
    {
        cout<<0<<endl;
        return 0;
    }
    while(!q.empty())
    {
        pos u=q.front();
        q.pop();
        for(int i=0;i<8;i++)
        {
            pos th;
            th.x=u.x+dx[i];
            th.y=u.y+dy[i];
            th.s=u.s+1;
            for(int i=1;i<=u.s;i++)
                th.move[i]=u.move[i];
            th.move[th.s]=st[i];
            if(th.x<1||th.x>8||th.y<1||th.y>8||vis[th.x][th.y])
                continue;
            vis[th.x][th.y]=1;
            if(th.x==x&&th.y==y)
            {
                cout<<th.s<<endl;
                for(int j=1;j<=th.s;j++)
                    cout<<th.move[j]<<endl;
                return 0;
            }
            q.push(th);
        }
    }
    return 0;
}
```

---

## 作者：动态WA (赞：7)

本题解为无脑dfs玩家准备，~~(虽然我知道dfs这道题慢多了，但是它不用思考啊)~~

基本思路：八个方向搜一遍，用一个数组记录走位，若到了终点发现步数较小，测更新ans和走位记录数组

~~然而你会发现样例都过不了~~

优化思路：用数组记录到每一个点的最小步数，若发现步数更小则更新，否则结束搜索

代码如下，~~我知道你们只会看这里~~：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<queue>
#include<cmath>
using namespace std;
typedef long long ll;
int qx,qy,zx,zy,c[10][10],p[100],b[100],ans=2147483647;
int fx[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
void dfs(int x,int y,int z){
	if (x==zx&&y==zy){
		if (z<ans){
			ans=z;
			for (int i=1;i<=z;i++)
				b[i]=p[i];
		}
		return;
	}
	if (c[x][y]<=z) return;
	else c[x][y]=z;
	for (int i=0;i<8;i++){
		int xx=x+fx[i][0];
		int yy=y+fx[i][1];
		if (xx<1||xx>8||yy<1||yy>8) continue;
		p[z+1]=i;
		dfs(xx,yy,z+1);		
	}
}
int main(){
	memset(c,0x3f,sizeof(c));
	char x;
	x=getchar();
	qx=x-'a'+1;
	scanf("%d",&qy);
	x=getchar();
	while (x=='\n'||x==' ') x=getchar();
	zx=x-'a'+1;
	scanf("%d",&zy);
	dfs(qx,qy,0);
	printf("%d\n",ans);
	for (int i=1;i<=ans;i++){
		switch(b[i]){
			case 0:printf("U\n");break;
			case 1:printf("RU\n");break;
			case 2:printf("R\n");break;
			case 3:printf("RD\n");break;
			case 4:printf("D\n");break;
			case 5:printf("LD\n");break;
			case 6:printf("L\n");break;
			case 7:printf("LU\n");break;
		}
	}
}
```


---

## 作者：Lucifer_Bartholomew (赞：4)

# ~~模拟过程~~
看王需要横移和竖移多少步，先把斜移的输出，在输出平移的。总步数就是斜移步数和平移步数的和。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	int a,y;
	char c,x;
	scanf("%c%d\n%c%d",&c,&a,&x,&y);
	int t=abs(c-x),k=abs(a-y),n=min(t,k),m=n+abs(t-k);
	printf("%d\n",m);//总步数
	for(int i=1;i<=n;++i)//斜移
	{
		if(c<x)putchar('R'),c++;
		else putchar('L'),x++;
		if(a<y)puts("U"),a++;
		else puts("D"),y++;
	}
	for(int i=n;i<m;++i)//平移
		if(a<y)puts("U");
		else if(a>y)puts("D");
		else if(c<x)puts("R");
		else puts("L");
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：灵光一闪 (赞：1)

我又来发题解了！

至于思路……我决定写在代码里

核心代码：
    if(s[0]-t[0]>0)//如果终点在左边就让c变成L
    {
        a=s[0]-t[0];
        c='L';
    }
    else//否则变成R
    {
        a=1-(s[0]-t[0])-1;
        c='R';
    }
    if(s[1]-t[1]>0)//一样的~
    {
        b=s[1]-t[1];
        d='D';
    }
    else
    {
        b=1-(s[1]-t[1])-1;
        d='U';
    }

    ans+=max(a,b);//这里很不容易理解，在后面我会解释一下
    cout<<ans<<endl;
    for(int i=max(a,b);i>=0;i--)
    {
        if(a>0)//如果要走就走
        {
            cout<<c;
            a--;
        }
        if(b>0)//同上
        {
            cout<<d;
            b--;
        }
        cout<<endl;
    }
    return 0;
}
然后我们就来讲ans+=max(a,b)

首先，我们知道：a左右，b上下

那么我们可以先走斜线，要的是 min(a,b) 次

然后就要走直线 （蒟蒻语文不好勿喷要 max(a,b)-min(a,b) 次

则max(a,b)-min(a,b)+min(a,b)=max(a,b)

完整代码：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<string>

using namespace std;

int main()
{
	string s,t;
	char c,d;
	cin>>s>>t;
	long long int ans=0;
	long long int a,b;
	if(s[0]-t[0]>0)
	{
		a=s[0]-t[0];
		c='L';
	}
	else
	{
		a=1-(s[0]-t[0])-1;
		c='R';
	}
	if(s[1]-t[1]>0)
	{
		b=s[1]-t[1];
		d='D';
	}
	else
	{
		b=1-(s[1]-t[1])-1;
		d='U';
	}
	ans+=max(a,b);
	cout<<ans<<endl;
	for(int i=max(a,b);i>=0;i--)
	{
		if(a>0)
		{
			cout<<c;
			a--;
		}
		if(b>0)
		{
			cout<<d;
			b--;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：北雪2009 (赞：0)

~~因为最近社区估值正在刷刷刷的掉，所以本蒟蒻又来水一篇题解咯~~     

------------

这道题就是一道模拟题。当然，它也考坐标的知识。

首先我们得判断国王的坐标是在广场的上下左右哪个地方，然后在根据方位移动。不过我们可以确定两件事：
>方位的移动方式可以从一开始就可以确定，不用再在每一步中判断。   
>步数就是国王的xy坐标和广场的xy坐标中相差最大的坐标。   

证明：   
>首先，由于位置是确定的，并且我们可以靠两个位置的相差坐标来判断国王的某一坐标超过了广场坐标。所以，方位的移动方式可以从一开始就可以确定，不用再在每一步中判断。    
>首先，我们可以知道，任何位置都可以靠直线移动和斜线移动到达。所以，只要移动到两个相差的距离相等时时，就可以转变方向。所以，步数就是国王的xy坐标和广场的xy坐标中相差最大的坐标。     

有了这两条绝对定理，那我们就可以开始动手了。    

------------

首先先输入，然后就获取国王和广场相差的坐标距离，之后就要根据这个坐标距离来判断国王是在广场的上、下、左、右、左上、右上、左下、右下哪个方位，从而确定移动方向。   
然后就是比较重要的一点：去相差坐标距离的绝对值。


------------

取了绝对值后，我们就来模拟了。既然是模拟，就必须用一个东东：for语句。不过这个for语句是不一样的。这个for语句是这么写的：
```cpp
for(;x||y;putchar('\n'))
```
（当然，你也可以不用putchar而用其他的。） 

------------

在循环中，我们可以按照“先斜后直”的方案。每次枚举时，都要分别判断一下相差的纵横距离是否为正。如果为正，则输出一开始判断好的方向，并且还要减1。最最最主要的是，不用else，只需要两个独立判断就行了！   

------------

最后就可以  $return 0;$  啦！

终于完结了！（撒花！QAQ）   

[程序传送门](https://www.luogu.com.cn/paste/ba2z6ule)

---

## 作者：BBD186587 (赞：0)

## 爆搜 ##
(~~懒得打模拟~~)

思路：先bfs一遍记下路径与最短路，再dfs一遍倒序输出

上代码~
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
struct node
{
	int x,y;
}t;
const int dx[]={0,0,1,1,1,-1,-1,-1};
const int dy[]={1,-1,0,1,-1,0,1,-1};
queue <node> q;
int qx,qy,vis[210][210],d[210][210],zx,zy,n,tot;
char a[2],b[2];
string from[210][210],k[8]={"U","D","R","RU","RD","L","LU","LD"},lj[40010];
void dfs(int x,int y)
{
	lj[++tot]=from[x][y];
	if(x==qx&&y==qy) return;
	if(from[x][y]=="U") dfs(x,y-1);
	else if(from[x][y]=="D") dfs(x,y+1);
	else if(from[x][y]=="R") dfs(x-1,y);
	else if(from[x][y]=="RU") dfs(x-1,y-1);
	else if(from[x][y]=="RD") dfs(x-1,y+1);
	else if(from[x][y]=="L") dfs(x+1,y);
	else if(from[x][y]=="LU") dfs(x+1,y-1);
	else if(from[x][y]=="LD") dfs(x+1,y+1);
}//输出路径
int main()
{
	cin>>a[0]>>a[1]>>b[0]>>b[1],qx=a[0]-'a'+1,qy=a[1]-'0';
	t.x=qx,t.y=qy,vis[t.x][t.y]=1,q.push(t);
	zx=b[0]-'a'+1,zy=b[1]-'0',n=8;
	while(!q.empty())
	{
		int xx=q.front().x,yy=q.front().y;q.pop();
		for(int i=0;i<=7;i++)
		{
			int nx=xx+dx[i],ny=yy+dy[i];
			if(nx>=1&&ny>=1&&nx<=n&&ny<=n&&!vis[nx][ny])
				from[nx][ny]=k[i],vis[nx][ny]=1,d[nx][ny]=d[xx][yy]+1,t.x=nx,t.y=ny,q.push(t);//记录路径
		}
	}//bfs
	printf("%d\n",d[zx][zy]);
	dfs(zx,zy);
	for(int i=tot-1;i>=1;i--) cout<<lj[i]<<'\n';
	return 0;
}
```
完结撒花~

---

## 作者：GusyNight (赞：0)

```
解题说明：

这道题是求从棋盘一个位置到另一个位置的最短距离，

可以按照上下左右对角线八个方向进行移动。

首先应该把棋盘字母坐标转换为数字判断横纵坐标差值各是多少，

由于一步棋可以同时改变横纵坐标，
所以移动距离至少为这两个坐标中的最大值。

在移动时以坐标相等为终止条件，
否则就通过不断比较横纵坐标的大小进行方向判断。
```
```cpp
#include<bits/stdc++.h>
#define TP int
#define Max 100009
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int main(){
	string s1,s2;
	cin>>s1>>s2;
	cout<<max(abs(int(s1[0]-s2[0])),abs(int(s1[1]-s2[1])))<<endl;
	while(s1!=s2){
		if (s1[0]<s2[0]){
			s1[0]++,cout<<"R";
		}
		else if(s1[0]>s2[0]){
			s1[0]--,cout<<"L";
		}
		if (s1[1]>s2[1]){
			s1[1]--,cout<<"D"; 
		}
		else if(s1[1]<s2[1]){
			s1[1]++,cout<<"U";
		}
		cout<<endl;
	}
	return 0;
}
```

---

