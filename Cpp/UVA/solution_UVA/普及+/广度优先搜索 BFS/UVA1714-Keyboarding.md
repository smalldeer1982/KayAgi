# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)

# 题解

## 作者：香风智乃 (赞：12)

**bfs**

找遍国内国外~~甚至翻墙~~都没找到一篇带完整代码的题解，所以我就贴上来吧qwq

坑点很多的一题（由于一本通的辣鸡翻译会错题意*n）。

1.多组数据

2.如果某方向上没有不同字符**光标不会动**

我们每次预处理出每个点向四个方向下次到达的点（四个方向都暴力找，所以比楼下julao慢）。然后跑bfs即可

注意bfs每次只能扩展一层！（所以不要把移动和选择写到一起qwq）

处理字符用map就好了

（卡了我一整天qwq）

[juruo's blog](https://www.cnblogs.com/kafuuchino/p/9596690.html)
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<map>
using namespace std;
inline int mini(int &a,int &b) {return a<b ?a:b;}
int d1[4]={0,1,0,-1};
int d2[4]={1,0,-1,0};
int n,m,len,a[52][52],b[10002],vis[52][52];
struct data{int x,y,step,dis;}dir[4][52][52];
map <char,int> Map;
void draw(){ //字符处理成数字好写
    for(int i=0;i<=9;++i) Map[(char)('0'+i)]=i+1;
    for(int i=0;i<26;++i) Map[(char)('A'+i)]=i+11;
    Map['-']=37; Map['*']=38;
} 
void pretreatment(){ //预处理四个方向上下次可到的点
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            for(int k=0;k<4;++k){
                int r1=i,r2=j;
                while(a[r1][r2]==a[r1+d1[k]][r2+d2[k]])    r1+=d1[k],r2+=d2[k];
                dir[k][i][j]=(data){r1,r2,0,0};
            }
} 
inline int bfs(){
    memset(vis,0,sizeof(vis));
    queue <data> h; int ans=0;
    int k=1;
    while(b[k]==a[1][1]&&k<=len) ++k;
    h.push((data){1,1,k,k-1}); vis[1][1]=k; //特判在起点选取的情况
    while(!h.empty()){
        data u=h.front(); h.pop();
        if(a[u.x][u.y]==b[u.step]){ //选择（千万不能和移动写在一起）
            if(u.step==len) {ans=u.dis+1; break;}
            vis[u.x][u.y]=u.step+1;
            h.push((data){u.x,u.y,u.step+1,u.dis+1});
            continue;
        }
        for(int i=0;i<4;++i){
            data to=dir[i][u.x][u.y]; to.x+=d1[i]; to.y+=d2[i]; //由于我的预处理没写完整要再加一次
            if(to.x<1||to.x>n||to.y<1||to.y>m) continue;
            if(vis[to.x][to.y]>=u.step) continue;
            vis[to.x][to.y]=u.step;
            h.push((data){to.x,to.y,u.step,u.dis+1});
        }
    }
    return ans;
}
int main(){
    //freopen("UVA1714.in","r",stdin);
    draw();
    char q[10002];
    while(scanf("%d",&n)!=EOF) //多组数据
    {
        scanf("%d",&m);
        for(int i=1;i<=n;++i){
            scanf("%s",q);
            for(int j=0;j<m;++j) a[i][j+1]=Map[q[j]];
        }
        scanf("%s",q); len=strlen(q);
        for(int i=0;i<len;++i) b[i+1]=Map[q[i]];
        b[++len]=38; //b数组存操作串
        pretreatment();
        printf("%d\n",bfs());
    }
    return 0;
}
```

---

## 作者：ELLIAS (赞：6)

## BFS
### NULL
这道题居然是`ACM-ICPC World Finals`的题目~~(蒟蒻瑟瑟发抖)~~

先来翻译一下题面~~(为什么我在讨论里发的翻译都没人看到)~~
#### Description
给定一个r行c列的在屏幕上的“虚拟键盘”，我们需要通过“上，下，左，右，选择”5个控制键来移动屏幕上的光标来打印文本。一开始，光标在键盘的左上 角，每次按方向键，光标总是跳到下一个在该方向上与当前位置不同的字符，若不存在则不移动。每次按选择键，则将光标所在位置的字符打印出来。
现在求打印给定文本（要在结尾打印换行符）的最少按键次数。

#### Input
第一行输入${r,c(1≤r,c≤50)}$

接下来给出一个 ${r* c}$ 的键盘，包括大写字母，数字，横线以及星号（星号代表${Enter}$换行） 最后一行是要打印的文本串s，s的长度不超过10000.

#### Output

输出打印文本（包括结尾换行符）的最少按键次数。保证一定有解。

Sample Input

2 19

ABCDEFGHIJKLMNOPQZY

X*****Y

AZAZ

Sample Output

19


注:　部分内容被省略　数据可能有多组

### EINS

用`nxt[][]`维护向四个方向能到的第一个非当前点字符的位置

BFS容器维护四个值:`nowx` 当前x坐标 `nowy` 当前y坐标 `ste` 当前有效字符长度 `sum` 总步数

先查看当前扩展的字符是否有效,有效则直接入队,判断是否结束,无效则考虑向周围移动.

### ZWEI
直接上代码
* `next` 处理部分
```cpp
for (rint i = 1; i <= n; i ++)
		{
			for (rint j = 1; j <= m; j ++)
			{
				ch = dat[i][j];

				if (dat[i-1][j] != ch) nxt[i][j][0] = make_pair (i-1, j);
				else nxt[i][j][0] = nxt[i-1][j][0];

				for (rint k = i + 1; k <= n; k ++)
				{
					if (dat[k][j] != ch) {nxt[i][j][1] = make_pair (k, j); break;}
				}

				if (dat[i][j-1] != ch) nxt[i][j][2] = make_pair (i, j-1);
				else nxt[i][j][2] = nxt[i][j-1][2];

				for (rint k = j + 1; k <= m; k ++)
				{
					if (dat[i][k] != ch) {nxt[i][j][3] = make_pair (i, k); break;}
				}
			}
		}
```
左和上直接继承,右侧暴力枚举,顺便更新路过的点也可以,但是~~我太菜了~~没写

* 比较基本的BFS
```cpp
		while (!que.empty())
		{
			fr = que.front(), que.pop ();
			nowx = fr.x, nowy = fr.y, nste = fr.ste, nsum = fr.sum;
			if (dat[nowx][nowy] == s[nste + 1])
			{
				que.push ((node) {nowx, nowy, nste + 1, nsum + 1});
				if (nste + 1 == lens) {printf ("%d\n", nsum + 1); break;}
			}
			else
			{
				for (rint i = 0; i <= 3; i ++)
				{
					gox = nxt[nowx][nowy][i].first, goy = nxt[nowx][nowy][i].second;
					if(!gox || !goy) continue;
					if (vis[gox][goy] < nste) { vis[gox][goy] = nste; que.push ((node){gox, goy, nste, nsum + 1});}
				}
			}
		}
```


### DREI
#### 注意事项
* 可能有多组数据
* 最后不要忘记打空格
* 小心字符串的输入和各种换行符
* 留心初始化

### VIER
最后,祝大家 `RP ++`

---

## 作者：Celtic (赞：3)

宽搜经典题。

先预处理一下这个位置向上下左右一下能跳到哪。

$BFS$维护一下打字打出了多少目标字符，目前光标在键盘上的位置和已经按了多少次。

如果曾经有一个状态位置和打出的目标字符数和现状态一样就剪枝。

如果当前按键和需要打的字符一样就直接按一下按键，然后$continue$。

一个小优化：如果之前在当前位置时打出的字符数不比现在的小就剪枝。

代码
```cpp
#include<bits/stdc++.h>
#define eps 1e-7
#define re register
#define N 2001001
#define MAX 51
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll& ret)
{
	ret=0;re ll pd=0;re char c=getchar();
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	ret=pd?-ret:ret;
}
ll r,c,len,ans;
char a[MAX][MAX],s[N];
ll dx[5]={0,-1,0,1,0};
ll dy[5]={0,0,1,0,-1};
pair<ll,ll> nxt[MAX][MAX][5];
struct node
{
	ll pos,deep,x,y;
	node(re ll a,re ll b,re ll t,re ll d)
	{
		pos=a;
		deep=b;
		x=t;
		y=d;
	}
};
ll vis[MAX][MAX]; 
int main()
{
	while(~scanf("%lld %lld",&r,&c))
	{
		for(re int i=1;i<=r;i++)
		for(re int j=1;j<=c;j++)
		{
			a[i][j]=getchar();
			while(!isdigit(a[i][j])&&(a[i][j]<65||a[i][j]>90)&&a[i][j]!='-'&&a[i][j]!='*')
				a[i][j]=getchar();
		}
	for(re int i=1;i<=r;i++)
		for(re int j=1;j<=c;j++)
		{
			for(re int k=1;k<=4;k++)
			{
				re ll x=i+dx[k],y=j+dy[k];
				while(x>0&&x<=r&&y>0&&y<=c&&a[x][y]==a[i][j])
				{
					x+=dx[k];
					y+=dy[k];	
				}
				if(x>0&&x<=r&&y>0&&y<=c)
					nxt[i][j][k]=make_pair(x,y);
				else
					nxt[i][j][k]=make_pair(0,0);
			}
		}
	scanf("%s",s+1);
	len=strlen(s+1);
	s[++len]='*';
	queue<node>q;
	q.push(node(0,0,1,1));
	memset(vis,-1,sizeof(vis));
	vis[1][1]=0;
	while(!q.empty())
	{
		re node qwq=q.front();
		q.pop();
		if(qwq.pos==len)
		{
			printf("%lld\n",qwq.deep);
			break;
		}
	//	printf("%lld %lld %lld %lld\n",qwq.pos,qwq.deep,qwq.x,qwq.y);
//		system("pause");
		if(a[qwq.x][qwq.y]==s[qwq.pos+1]&&vis[qwq.x][qwq.y]<qwq.pos+1)
		{
			q.push(node(qwq.pos+1,qwq.deep+1,qwq.x,qwq.y));
			vis[qwq.x][qwq.y]=qwq.pos+1;
			continue;
		}
		re node qaq=qwq;
		for(re int i=1;i<=4;i++)
		{
			qaq.deep=qwq.deep+1;
			qaq.x=nxt[qwq.x][qwq.y][i].first;
			qaq.y=nxt[qwq.x][qwq.y][i].second;
			qaq.pos=qwq.pos;
			if(qaq.x>0&&qaq.x<=r&&qaq.y>0&&qaq.y<=c&&vis[qaq.x][qaq.y]<qaq.pos)
			{
				q.push(qaq);
				vis[qaq.x][qaq.y]=qaq.pos;
			}
		}
	}
	}
	
    exit(0);
}
//It's enough to have a confidant in life. He is nothing but a clear conscience.
```


---

## 作者：Akaina (赞：2)

### Keyboarding

这个翻译确实很差，所以需要注意的点有：

1.文中“与当前位置不同的字符”的意思是“与当前位置的字符不同的字符"

2.多组数据

**剪枝一**：首先我们需要先预处理每个点往四个方向移动分别可以到达哪个点

那么问题来了：怎么判重呢？

每个位置是可以重复到达的，所以记录之前到达过的位置的判重方法是错误的，

那么对于一个点往右走再往左走，回到原位置的大量重复状态这种以前是通过判重来剪枝的情况，现在该如何剪枝呢？根据这道题的特性，我们可以得到以下的剪枝方法：

**剪枝二**：记录每个点之前扫描到该点时打印的字符串的最大长度，如果我们又搜索到该点，且当前打印的字符串长度小于等于之前记录的这个点打印的最长长度，则可以剪枝

我看到洛谷题解里的大部分题解是把选择和移动分开处理的，其实并不需要，因为每到一个点，就用处理起点的方法，直接能打印多少就贪心打印完就可以了。

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n,m,len;
struct node{
    int x,y;
}to[55][55][6];
char ch[55][55];
char goal[10010];
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
int check(int x,int y)
{
    if(x>=1&&x<=n&&y>=1&&y<=m)return 1;
    return 0;
}
void Deal_first()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=1;k<=4;k++)
            {
                int tx=i+dx[k],ty=j+dy[k];
                if(check(tx,ty)==0)continue;
                while(ch[tx][ty]==ch[i][j]&&check(tx,ty)==1)
                {
                    tx+=dx[k];ty+=dy[k];
                }
                if(!check(tx,ty))continue;
                to[i][j][k].x=tx;to[i][j][k].y=ty;
            }
        }
    }
}
struct jp{
    int x,y,cnt,ans;
};
queue<jp> q;
int vis[55][55];
void bfs()
{
    int tim=1;
    while(ch[1][1]==goal[tim])tim++;
    q.push((jp){1,1,tim,tim-1});
    vis[1][1]=tim;
    while(!q.empty())
    {
        jp A=q.front();q.pop();
        for(int i=1;i<=4;i++)
        {
            int tx=to[A.x][A.y][i].x,ty=to[A.x][A.y][i].y;
            if(check(tx,ty)==0)continue;
            int timm=0;
            while(ch[tx][ty]==goal[A.cnt+timm])timm++;
            if(A.cnt+timm==len+1)
            {
                printf("%d\n",A.ans+timm+1);
                return ;
            }
            if(vis[tx][ty]<A.cnt+timm)vis[tx][ty]=A.cnt+timm;
            else continue;
            q.push((jp){tx,ty,A.cnt+timm,A.ans+timm+1});
        }
    }
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        while(!q.empty())q.pop();
        memset(vis,0,sizeof(vis));
        memset(to,0,sizeof(to));len=0;
        for(int i=1;i<=n;i++)scanf("%s",ch[i]+1);
        scanf("%s",goal+1);
        len=strlen(goal+1);
        goal[++len]='*';
        Deal_first();
        bfs();
    }
    return 0;
}
```



---

## 作者：skin (赞：2)

# [Keyboarding](https://www.luogu.org/problemnew/show/UVA1714)
## 这是一道BFS（但用到了不少的SPFA的思想）的题，不过出题者十分**~~毒瘤~~**，有众多坑点：
1、按下方向键时跳到下一个不同的字符，也就意味着光标可以“**传送**”。

2、最后要打印一个回车，也就是“*”号。

3、选择也是一次操作。

4、可能有多组数据。

5、因为同样的字母会重复出现，所以如果BFS一个接一个的找时，第一个找到的未必是全局最优的，如图：
![](https://img2018.cnblogs.com/blog/1545387/201811/1545387-20181124163754169-489408515.png)

蓝色框是一个一个字符去BFS，先找到一个，再找下一个，（每个箭头算一步，因为光标会移动向该方向下一个不同的字符），红色是正确走法。
  
**思路**：

1、先预处理每个点可以到的地方（最多4个），存入f数组。

2、list数组保存每一个BFS到的点的x、y坐标，所用的步数（dep）及从出发点到这个点的路径中已打印的字符数（find）。

3、dep数组表示地图上每一个点作为一条路径的终点可以打印多少字符。

4、**（重点）如果从出发点到当前的点再到另一个点比出发点到那个点的原路径所打印的字符更多，那么更新那个点的find和dep值，也就是说以这个点为终点，有另一条路径，并且路径上打印的字符更多（类似SPFA）。反则不更新，因为已经被遍历过的点所用步数肯定比当前的点的步数少。**

5、如果当前点是下一个要打印的点，就find++，表示去寻找下一个字符。

6、找到最后一个字符后输出步数并return 0；

### Code
（因为~~我太弱了~~不会用队列，只好有循环数组）

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int dx[4]={-1,0,1,0};//四个方向
int dy[4]={0,-1,0,1};//四个方向
char s[110000],map[2100][2100];
int r,c,xx,yy,len,head,tail,dep[2100][2100];
struct node
{
    int x,y,dep,find;//x，y是坐标，dep表示当前所用步数，find表示以当前点为终点的路径中已打印的字符数
}list[1600000];
struct nodee
{
    int x[5],y[5],len;//x，y数组表示可以去到的位置，len表示可前往的点的数量
    nodee()
    {
        len=0;
    }
}f[2100][2100];
void chuli()//预处理每个点能去到的地方，记录在f数组里
{
    for(int i=1;i<=r;i++)
    for(int j=1;j<=c;j++)
    for(int k=0;k<=3;k++)
    {
        xx=i;
        yy=j;
        while(map[i][j]==map[xx+dx[k]][yy+dy[k]]&&
        xx+dx[k]&&yy+dy[k])//一直循环直到下一个点是合法的或者到达边界
        {
            xx+=dx[k];
            yy+=dy[k];
        }
        if(map[i][j]!=map[xx+dx[k]][yy+dy[k]]&&
        xx+dx[k]&&yy+dy[k])//如果下一个是点是合法的，就加入f数组
        {
            f[i][j].len++;
            f[i][j].x[f[i][j].len]=xx+dx[k];
            f[i][j].y[f[i][j].len]=yy+dy[k];
        }
    }
    return ;
}
int main()
{
    while(scanf("%d%d",&r,&c)!=EOF)//多组数据
    {
        memset(f,0,sizeof(f));
        memset(dep,-1,sizeof(dep));
        memset(list,0,sizeof(list));
        memset(map,' ',sizeof(map));//初始化
        for(int i=1;i<=r;i++)
        scanf("%s",map[i]+1);
        scanf("%s",s+1);
        len=strlen(s+1);
        s[len+1]='*';
        len++;//最后要打印一个回车，也就是“*”号
        chuli();//预处理
        xx=yy=1;
        head=1;
        tail=2;
        list[1].x=xx;
        list[1].y=yy;
        list[1].dep=0;
        list[1].find=0;
        while(head!=tail)
        {
            if(map[list[head].x][list[head].y]==s[list[head].find+1])//如果当前的点是下一个要打印的字符，就重新加入队列同时把已打字符数加1
            {
                list[tail]=list[head];
                list[tail].dep++;
                list[tail].find++;
                if(list[tail].find==len)//如果所有数都打印了，就输出并结束。
                {
                    printf("%d\n",list[head].dep+1);
                    break;
                }
                tail++;
            }
            for(int k=1;k<=f[list[head].x][list[head].y].len;k++)//逐个遍历当前点可以去到的其他点
            {
                xx=f[list[head].x][list[head].y].x[k];
                yy=f[list[head].x][list[head].y].y[k];
                if(dep[xx][yy]<list[head].find)//这个dep数组与结构体中的dep不同，dep数组表示地图中每一个点作为终点，路径上最多能打印的字符数，如果这个点作为终点有可打印更多的字符，就更新它并加入队列去更新更多的点
                {
                    list[tail].x=xx;
                    list[tail].y=yy;
                    list[tail].dep=list[head].dep+1;
                    list[tail].find=list[head].find;
                    dep[xx][yy]=list[head].find;
                    tail++;
                    if(tail>1500000)
                    tail=1;
                }
            }
            head++;
        }
    }
    return 0;
}
```

**不要试图抄袭、复制或是删掉注释后提交代码，就算我不把你打死，你也AC不了的。（~~因为我修改了一点小东西，嘿嘿嘿~~）**

---

## 作者：ASUKA_X (赞：2)

同机房的神犇已经发了一篇题解，但是代码没发全，自己 ~~复制~~ 借鉴优化的时候又撞了几次墙……所以本蒟蒻就来写一篇自己的题解

~~蒟蒻的优化之路（
4600ms -> 4870ms -> 2000ms~~

### **Eins** -  _Gedanke_ 

题目中说每次移动可以直接将光标移动至该方向上与当前字符不同的第一个字符的位置，所以可以想到预处理当前位置上下左右移动后的目的地。 _（注意此处移动所使用的步数是1而非两个位置之间的距离）_ 

因为r和c都非常小，所以可以暴力处理。

然后剩下的工作就是非常普通的BFS了。但是写烂了还是会和我的初版代码一样效率极低XD

### **Zwei** -  _Code_ 

看代码之前先学习一下英语（

pretreatment - 预处理

cursor - 光标

这是我的初版代码：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 60;
const int MAXM = 10010;

struct PTM {    //预处理时记录的移动目的地类型 
    int x, y;
};

struct Node {   //怼进队列里的当前位置 
    int x, y, step, cursor; //step是当前已经移动了多少次，cursor是当前已经敲出来的字符个数 
};

int r, c;                         //题里的数据 
char kb[MAXN][MAXN], goal[MAXM];  //kb是keyboard的缩写(不是那个TK队友的KB)、goal是目标字符串 
PTM towards[MAXN][MAXN][5];       //towards[i][j][k](0 < k < 5)表示(i, j)点上下左右移动后的目的地 
int exp[MAXN][MAXN], goalLen;     //exp数组记录可以移动的方向个数,goalLen是目标串长度 
bool vis[MAXN][MAXN][MAXM];       //一个非常冗杂而多余的Visit数组，代码龟速的罪魁祸首 
queue<Node>q;

void pretreatment() {             //预处理函数 
    goalLen = strlen(goal + 1);   //坑点1：目标字符串后有一个回车 
    goal[++goalLen] = '*';
    
    for(int i = 1; i <= r; i++)   //暴力预处理出移动目的地（略） 
        for(int j = 1; j <= c; j++) {
            exp[i][j] = 0;
            
            for(int k = i - 1; k >= 1; k--)
                if(kb[i][j] != kb[k][j]) {
                    towards[i][j][++exp[i][j]] = (PTM){k, j};
                    break;
                }
                    
            for(int k = i + 1; k <= r; k++)
                if(kb[i][j] != kb[k][j]) {
                    towards[i][j][++exp[i][j]] = (PTM){k, j};
                    break;
                }
                
            for(int k = j - 1; k >= 1; k--)
                if(kb[i][j] != kb[i][k]) {
                    towards[i][j][++exp[i][j]] = (PTM){i, k};
                    break;
                }
                
            for(int k = j + 1; k <= c; k++)
                if(kb[i][j] != kb[i][k]) {
                    towards[i][j][++exp[i][j]] = (PTM){i, k};
                    break;
                }
        }
    return;
}

void bfs() {           //常规BFS 
    memset(vis, false, sizeof(vis));
    
    while(!q.empty()) q.pop(); //每次BFS结束以后，queue里面总会剩点东西 
    
    vis[1][1][0] = true;    //vis[i][j][k]表示上一次经过点(i, j)处时，已经打出来的字符串长度是k（真的好麻烦） 
    q.push((Node){1, 1, 0, 0});
    
    while(!q.empty()) {
        Node now = q.front();
        q.pop();
        
        if(now.cursor == goalLen) {   //已经敲完了就输出（说实话把这个玩意单拎出来也会让搜索跑的很慢） 
            printf("%d\n", now.step);
            return;
        }
        
        if(kb[now.x][now.y] == goal[now.cursor + 1] && !vis[now.x][now.y][now.cursor + 1]) {  //如果当前位置时下一个字符(也就是说不需要移动) 
            vis[now.x][now.y][now.cursor + 1] = true;
            q.push((Node){now.x, now.y, now.step + 1, now.cursor + 1});    //入队 
        } else {
            for(int i = 1; i <= exp[now.x][now.y]; i++) {    //如果需要移动的话就动 
                int ux = towards[now.x][now.y][i].x, uy = towards[now.x][now.y][i].y;
                
                if(!vis[ux][uy][now.cursor]) {
                    vis[ux][uy][now.cursor] = true;
                    q.push((Node){ux, uy, now.step + 1, now.cursor});
                }
            }
        }
    }
}

int main() {
    while( cin>>r>>c ) {    //标准输入，坑点2：有多组数据（这对英语不好的我实在是太不友好了QAQ） 
        for(int i = 1; i <= r; i++)
            scanf("%s", kb[i] + 1);
        scanf("%s", goal + 1);
        
        pretreatment();
        
        bfs();
    }
    
    return 0;
}
```

显然这个代码看起来这么复杂，肯定会特别慢（确信

事实上跑了4600ms，学校的内网OnlineJudge会TLE。

emmmmmm怎么办呢?

试图优化的时候可以发现预处理的时候可以试图优化一下：每次更新向左或向上移动的时候，上面一个点的移动目的地已经处理好了，所以只需要判断一下上一个地方的字符和当前字符相不相同。

```cpp
for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++) {
            char ch = kb[i][j];
            
            if(kb[i - 1][j] != ch) //就像这样
            	exp[i][j][1] = make_pair(i - 1, j);
            else
            	exp[i][j][1] = exp[i - 1][j][1];
            
            for(int k = i + 1; k <= r; k++)
            	if(kb[k][j] != ch) {
            		exp[i][j][2] = make_pair(k, j);
            		break;
            	}
            	
            if(kb[i][j - 1] != ch)  //这里也是
            	exp[i][j][3] = make_pair(i, j - 1);
            else
            	exp[i][j][3] = exp[i][j - 1][3];
            	
            for(int k = j + 1; k <= c; k++)
            	if(kb[i][k] != ch) {
            		exp[i][j][4] = make_pair(i, k);
            		break;
            	}
        }
```

但是加上这个优化跑的更慢了？（可能是因为STL容器的天生劣势

这个优化的效果并不显著，因为r和c的范围就那么小。

所以想到应该是因为BFS写烂了……于是重写了一遍BFS：
```cpp
void bfs() {
	memset(maxCursor, -1, sizeof(maxCursor));
	
	while(!q.empty()) q.pop();
	
	maxCursor[1][1] = 0;  //取代vis数组的是这个东西 maxCursor[i][j]代表上一次经过点(i, j)时已经敲出来的字符串长度 效果显著（主要是清空上一个代码vis数组时会很慢）！ 
	q.push((Node){1, 1, 0, 0});
	
	while(!q.empty()) {
		Node now = q.front();
		q.pop();
		
		if(now.cursor == goalLen) { //似乎把这个放在下面会更快 
			printf("%d\n", now.step);
			return;
		}
		
		if(kb[now.x][now.y] == goal[now.cursor + 1] && maxCursor[now.x][now.y] <= now.cursor) {
			maxCursor[now.x][now.y] = now.cursor + 1;
			q.push((Node){now.x, now.y, now.step + 1, now.cursor + 1});
		} else {
			for(int i = 1; i <= 4; i++) {
				int ux = exp[now.x][now.y][i].first, uy = exp[now.x][now.y][i].second;
				
				if(maxCursor[ux][uy] < now.cursor) {
					maxCursor[ux][uy] = now.cursor;
					q.push((Node){ux, uy, now.step + 1, now.cursor});
				}
			}
		}
	}
}
```

然后Luogu和内网都可以很愉快的AC了（撒花）

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 60;
const int MAXM = 10010;

struct PTM {
	int x, y;
};

struct Node {
	int x, y, step, cursor;
};

int r, c, goalLen;
char kb[MAXN][MAXN], goal[MAXM];
pair<int, int>exp[MAXN][MAXN][5];
int maxCursor[MAXN][MAXN];
queue<Node>q;

void pretreatment() {
	goalLen = strlen(goal + 1);
	goal[++goalLen] = '*';
	
	fill (exp[0][0], exp[0][0] + MAXN * MAXN * 5, make_pair(0, 0));
	
	for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++) {
            char ch = kb[i][j];
            
            if(kb[i - 1][j] != ch)
            	exp[i][j][1] = make_pair(i - 1, j);
            else
            	exp[i][j][1] = exp[i - 1][j][1];
            
            for(int k = i + 1; k <= r; k++)
            	if(kb[k][j] != ch) {
            		exp[i][j][2] = make_pair(k, j);
            		break;
            	}
            	
            if(kb[i][j - 1] != ch)
            	exp[i][j][3] = make_pair(i, j - 1);
            else
            	exp[i][j][3] = exp[i][j - 1][3];
            	
            for(int k = j + 1; k <= c; k++)
            	if(kb[i][k] != ch) {
            		exp[i][j][4] = make_pair(i, k);
            		break;
            	}
        }
	return;
}

void bfs() {
	memset(maxCursor, -1, sizeof(maxCursor));
	
	while(!q.empty()) q.pop();
	
	maxCursor[1][1] = 0;  //取代vis数组的是这个东西 maxCursor[i][j]代表上一次经过点(i, j)时已经敲出来的字符串长度 效果显著！ 
	q.push((Node){1, 1, 0, 0});
	
	while(!q.empty()) {
		Node now = q.front();
		q.pop();
		
		if(now.cursor == goalLen) { //似乎把这个放在下面会更快 
			printf("%d\n", now.step);
			return;
		}
		
		if(kb[now.x][now.y] == goal[now.cursor + 1] && maxCursor[now.x][now.y] <= now.cursor) {
			maxCursor[now.x][now.y] = now.cursor + 1;
			q.push((Node){now.x, now.y, now.step + 1, now.cursor + 1});
		} else {
			for(int i = 1; i <= 4; i++) {
				int ux = exp[now.x][now.y][i].first, uy = exp[now.x][now.y][i].second;
				
				if(maxCursor[ux][uy] < now.cursor) {
					maxCursor[ux][uy] = now.cursor;
					q.push((Node){ux, uy, now.step + 1, now.cursor});
				}
			}
		}
	}
}

int main() {
	while( scanf("%d%d", &r, &c) != EOF ) {
		for(int i = 1; i <= r; i++)
			scanf("%s", kb[i] + 1);
		scanf("%s", goal + 1);
		
		pretreatment();
		
		bfs();
	}
	
	return 0;
}
```

## ~THE END~

---

