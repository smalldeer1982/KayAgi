# Chessboard Dance

## 题目描述

在棋盘上跳舞是件有意思的事情。现在给你一张国际象棋棋盘和棋盘上的一些子以及你的初始位置和方向。求按一定操作后，棋盘的状态。

操作有四种，描述如下：

move n        n是非负整数，表示你按目前所在方向前进n步，如果即将走出棋盘，则停止。如果面前有棋子，则将其向前推一步。

turn left    向左转90度

turn right    向右转90度

turn back    向后转


## 样例 #1

### 输入

```
......bA
.....^..
........
........
........
........
........
........
move 2
turn right
move 1
#
```

### 输出

```
......>b
........
........
........
........
........
........
........
```

# 题解

## 作者：冰糖鸽子 (赞：9)

[原题传送门](https://www.luogu.com.cn/problem/P2033)

蒟蒻第二道蓝题，居然一次过的qwq

题意：

- 有一个 $8 \times 8$ 矩阵，有些地方有物品，有一个地方是你

- 你所在位置用 `^` 、`<` 、`>` 、`v` 四个字母中一个表示，你最开始面向的方向就是箭头的朝向

- 有许多条命令，整个输入一一行一个 `#` 结束

- 命令1： `move n` ,表示你要往前(你面向的方向)走 $n$ 步，如果走到矩阵边缘就不走了

- 命令2： `turn XX` 其中 XX 可能是 `right`,`left`,`back`，分别表示向右，向左，向后转

- 重点：你向前走时，如果你前面有物品，则你要推着物品一起走，如果物品前面还有物品，则要一起往前推 $……$

思路：

- 首先，输入时确定好你的方向和位置

- 输入命令时先输入第一个词，然后判断是往前走还是转弯

- 往前走的话就执行 $n$ 次往前走一步

- 转弯的话就把方向 $+$ $m$

可能你不太懂，那就看代码吧，都在注释里了：

```cpp
#include <bits/stdc++.h>//懒人神器
using namespace std;
char q[8][8],vs[4] = {'<','^','>','v'};//q是棋盘，vs是最后输出时纠正方向用的
int fx[4] = {0,-1,0,1},fy[4] = {-1,0,1,0};//炒鸡好用的移动数组
int qx,qy,f;//qx和qy是你的位置，f是方向
string pd;
void d(int x,int y)
{
    int lx = x + fx[f];//预览x
    int ly = y + fy[f];//预览y
    if(lx < 0 || lx > 7 || ly < 0 || ly > 7)//如果越界了
    {
        return;//结束，返回到上一层
    }
    if(q[lx][ly] != '.')//如果当前方向前面有棋子
    {
        d(lx,ly);//以那个棋子递归
    }
    q[lx][ly] = q[x][y];//将棋子往前移动一格
    q[x][y] = '.';//自己走了之后就变为空
    qx = lx;//这里注意，因为只要运行到了这里那最后lx和ly就是你往前走后的位置
    qy = ly;//所以将你的位置设置成lx和ly
}
int main()
{
    for(int i = 0;i < 8;i++)//直接输入
    {
        for(int j = 0;j < 8;j++)//输入
        {
            cin >> q[i][j];
            if(q[i][j] == '<')//方向为左
            {
                f = 0;//设置方向
                qx = i;//设置位置
                qy = j;//设置位置
            }
            if(q[i][j] == '^')//同上
            {
                f = 1;
                qx = i;
                qy = j;
            }
            if(q[i][j] == '>')//同上
            {
                f = 2;
                qx = i;
                qy = j;
            }
            if(q[i][j] == 'v')//同上
            {
                f = 3;
                qx = i;
                qy = j;
            }
        }
    }
    cin >> pd;//先输入
    int a;//move命令所用的
    while(pd != "#")//结束之前
    {
        if(pd == "move")//往前走的命令
        {
            cin >> a;//走多少步
            for(int i = 0;i < a;i++)//简化过程
            {
                d(qx,qy);//参考第7行d函数
            }
        }
        if(pd == "turn")//转向命令
        {
            cin >> pd;
            if(pd == "left")
            {
                f--;//往左
            }
            if(pd == "right")
            {
                f++;//往右
            }
            if(pd == "back")
            {
                f += 2;//往后
            }
            if(f >= 4)//超出了
            {
                f -= 4;//转回去
            }
            if(f < 0)//成了负数
            {
                f += 4;//转回去
            }
        }
        cin >> pd;//再次输入命令
    }
    q[qx][qy] = vs[f];//将你设成当前方向的状态
    for(int i = 0;i < 8;i++)//输出
    {
        for(int j = 0;j < 8;j++)//输出
        {
            cout << q[i][j];//输出，不加空格
        }
        cout << endl;//记得换行
    }
    return 0;//结束
}
```


---

## 作者：wuyonghuming (赞：3)

# 技巧：
### 方法一
输入中有可能会向四个方向移动，但是把每个方向写一遍会让代码变长，所以我们可以记住四个方向，写一个包含四个方向的函数，通过这个函数，完成移动。**这个函数可以通过递归实现**，如果前面那个点是空的，那么把这个棋子移到前面那个点之后就结束了；如果那个点有棋子，横坐标轴和纵坐标轴都按照方向变化，因为会把前面的棋子推走，而且被推走的棋子可能会有多个，所以递归处理，变化后，从变化过的点开始继续递归，这里也就是核心的代码了，可以大大减少代码量。
```cpp
void yidong(int xx,int yy)//递归的坐标
{
	int nx=xx+fx[z],ny=yy+fy[z];//按方向走后会到哪
	if(nx<1||nx>8||ny<1||ny>8)//如果走出棋盘
		return;//结束了
	if(s[nx][ny]!='.')//如果下一个点不是空
		yidong(nx,ny);//递归
	s[nx][ny]=s[xx][yy];//这个点的棋子到了下一个点
}
```
### 方法二
这个方向是数组唯一可以变化的值，转弯后这个会在"^,>,v,<"四个值中变化，如果每次变化后都要一个一个判断就会让代码变长，我们可以**通过一个数组把这四个方向记录下来**，**还有一个变量来记住现在的方向** ($1$~$3$)，可以通过这个**直接找到对应的字符**。下面是相关的操作。

$1.$刚开始输入
```cpp
for(int k=0;k<=3;k++)//寻找四个方向代表的字符有没有和当前字符相同的
{
	if(f[k]==s[i][j])//如果有
	{
		x=i;//开始的x坐标是i
		y=j;//开始的y坐标是j
		z=k;//开始的方向是k
	}
}
```
$2.$转向
```cpp
cin>>str;//输入方向
if(str=="left")//如果是左边
	z=(z+3)%4;//加上3再对4取模，防止超过3
else if(str=="right")//如果是右边
	z=(z+1)%4;//加上1再对4取模
else //如果都不是，就一定是转到后面
	z=(z+2)%4;//加上2对4取模
s[x][y]=f[z];//现在是新的符号了
```
### 方法三
有四个方向，可以先记录在数组里面，**记住要按顺序，否则会乱**，比如可以这样记录：
```cpp
int fx[4]={-1,0,1,0};
int fy[4]={0,1,0,-1};
```
分别代表↑，→，↓，←。
# 代码：
~~因为我的代码是目前最短的，我就尝试发题解了~~
```cpp
#include <bits/stdc++.h>//头文件
using namespace std;
char s[10][10],f[4]={'^','>','v','<'};//四个方向代表的字符
int fx[4]={-1,0,1,0};//横坐标方向
int fy[4]={0,1,0,-1};//纵坐标方向
int x,y,z,a;//x代表横坐标，y代表纵坐标，z代表方向
void yidong(int xx,int yy)//递归的坐标
{
	int nx=xx+fx[z],ny=yy+fy[z];//按方向走后会到哪
	if(nx<1||nx>8||ny<1||ny>8)//如果走出棋盘
		return;//结束了
	if(s[nx][ny]!='.')//如果下一个点不是空
		yidong(nx,ny);//递归
	s[nx][ny]=s[xx][yy];//这个点的棋子到了下一个点
}
int main()//主函数
{
	string str;//读入的命令
	for(int i=1;i<=8;i++)//有八行
	{
		for(int j=1;j<=8;j++)//有八列
		{
			cin>>s[i][j];//输入棋盘第i行第j列状态
			for(int k=0;k<=3;k++)//四种方向
			{
				if(f[k]==s[i][j])//如果是其中一种
				{
					x=i;//开始在第i行
					y=j;//开始在第j列
					z=k;//第k种
				}
			}
		}
	}
	while(cin>>str)//当能输入
	{
		if(str[0]=='#')//如果结束了
			break;//跳出循环
		if(str[0]=='t')//当命令是旋转时
		{
			cin>>str;//输入字符串
			if(str=="left")//如果是向左
				z=(z+3)%4;//加三个，如减一，可能成为负数
			else if(str=="right")//如果向右
				z=(z+1)%4;//加一
			else //如果都不是
				z=(z+2)%4;//加二再对四取模
			s[x][y]=f[z];//这个地图这个点改变了
		}
		else//如果是移动
		{
			cin>>a;//输入一个数
			for(int i=1;i<=a;i++)//循环a次，每次只处理一次移动，更加简单
			{
				yidong(x,y);//在这个点进行移动
				int nx=x+fx[z],ny=y+fy[z];//计算移动后的横坐标和纵坐标
				if(nx>0&&nx<9&&ny>0&&ny<9)//如果不出棋盘
				{
					s[x][y]='.';//这个点空了
					x=nx;//下一个点的行坐标更新
					y=ny;//下一个点的纵坐标更新
				}
			}
		}
	}
	for(int i=1;i<=8;i++)//从第一行到最后一行
	{
		for(int j=1;j<=8;j++)//从第一列到最后一列
		{
			cout<<s[i][j];//输出最后答案
		}
		puts("");//空一行
	}
	return 0;//别忘了
}
```
# 感谢：
### 感谢管理审核，感谢大家观赏


---

## 作者：Wei_taming (赞：2)

我们用一个状态d来表示当前面向的方向，d = 0 1 2 3分别对应上左下右，之后开几个常量数组来对应某一方向的位移和字符，这样就可以大大减少代码量
```cpp
#include <cstdio>
#include <cctype>

#define ok(x, y) (1 <= x && x <= 8 && 1 <= y && y <= 8)

const int xx[] = {-1, 0, 1, 0};
const int yy[] = {0, -1, 0, 1};
const char u[] = {'^', '<', 'v', '>'};

int x, y, d, s;
char m[10][10], o[10], p[10];

int main() {
	for (int i = 1; i <= 8; ++ i) {
		scanf("%s", m[i] + 1);
		for (int j = 1; j <= 8; ++ j)
			for (int k = 0; k < 4; ++ k) 
				if (m[i][j] == u[k]) x = i, y = j, d = k;
	}
	while (scanf("%s", o + 1), o[1] != '#') {
		if (o[1] == 'm') {
			scanf("%d", &s);
			int tx = x + xx[d], ty = y + yy[d];
			while (s && ok(tx, ty)) {
				if (m[tx][ty] != '.') {
					int dx = tx + xx[d], dy = ty + yy[d];
					while (ok(dx, dy) && m[dx][dy] != '.')
						dx += xx[d], dy += yy[d];
					while (dx != tx || dy != ty)
						m[dx][dy] = m[dx - xx[d]][dy - yy[d]],
						dx -= xx[d], dy -= yy[d];
				}
				m[tx][ty] = m[x][y];
				m[x][y] = '.';
				x = tx; y = ty;
				tx += xx[d]; ty += yy[d];
				-- s;
			}
		}
		else {
			scanf("%s", p + 1);
			if (p[1] == 'l') d = (d + 1) % 4;
			else if (p[1] == 'r') d = (d + 3) % 4;
			else d = (d + 2) % 4;
			m[x][y] = u[d];
		}
	}
	for (int i = 1; i <= 8; puts(""), ++ i)
		for (int j = 1; j <= 8; ++ j)
			putchar(m[i][j]);
	
	return 0;
}
```


---

## 作者：LinAPro (赞：2)

### 题解 P2033 【Chessboard Dance】
 _这是一道思路很清晰的模拟题_
 
 _其实并不复杂，只是有4种方向让人很抓狂。_
 
 _不多说，上代码。_ 


------------
71分代码
```
#include<bits/stdc++.h>
using namespace std;
char a[10][10];
char q[6];//操作的前一串
char w[6];//操作的后一串
int meet;//你的朝向 1↑ 2↓ 3← 4→
int x;
int y;//你的坐标
void move(int n) {//移动
	if(meet==1) {
		for(int i=1; i<=n; i++) {
			if(x==1)continue;//到达边界时就不再操作
			if(a[x-1][y])a[x-2][y]=a[x-1][y];
			a[x-1][y]=0;
			x--;
		}
	}
	if(meet==2)
		for(int i=1; i<=n; i++) {
			if(x==8)continue;//到达边界时就不再操作
			if(a[x+1][y])a[x+2][y]=a[x+1][y];
			a[x+1][y]=0;
			x++;
		}
	if(meet==3)
		for(int i=1; i<=n; i++) {
			if(y==1)continue;//到达边界时就不再操作
			if(a[x][y-1])a[x][y-2]=a[x][y-1];
			a[x][y-1]=0;
			y--;
		}
	if(meet==4)
		for(int i=1; i<=n; i++) {
			if(y==8)continue;//到达边界时就不再操作
			if(a[x][y+1])a[x][y+2]=a[x][y+1];
			a[x][y+1]=0;
			y++;
		}
}
int main() {
	for(int i=1; i<=8; i++)
		for(int j=1; j<=8; j++) {
			cin>>a[i][j];
			if(a[i][j]=='.')a[i][j]=0;
            //将“.”清为零，好做以后的操作
			if(a[i][j]=='^') {//记录当前坐标
				x=i;
				y=j;
				meet=1;//记录当前方向
				a[i][j]=0;//当前坐标录入后记得清零
			}
			if(a[i][j]=='v') {
				x=i;
				y=j;
				meet=2;
				a[i][j]=0;
			}
			if(a[i][j]=='<') {
				x=i;
				y=j;
				meet=3;
				a[i][j]=0;
			}
			if(a[i][j]=='>') {
				x=i;
				y=j;
				meet=4;
				a[i][j]=0;
			}
		}
    //操作输入
	while(cin>>q) {
		if(q[0]=='#')break;
		if(q[0]=='m') {
			int n;
			cin>>n;
			move(n);//移动
		} else if(q[0]=='t') {
			cin>>w;//1↑ 2↓ 3← 4→
			if(w[0]=='l') {//左转
				if(meet==1)meet=3;
				else if(meet==2)meet=4;
				else if(meet==3)meet=2;
				else if(meet==4)meet=1;
			}
			if(w[0]=='r') {//右转
				if(meet==1)meet=4;
				else if(meet==2)meet=3;
				else if(meet==3)meet=1;
				else if(meet==4)meet=2;
			}
			if(w[0]=='b') {//后转
				if(meet==1)meet=2;
				else if(meet==2)meet=1;
				else if(meet==3)meet=4;
				else if(meet==4)meet=3;
			}
		}
	}
	for(int i=1; i<=8; i++) {
		for(int j=1; j<=8; j++) {
			//如果a[i][j]是我们现在位置的话
            if(i==x&&j==y) {
				if(meet==1)cout<<"^";
				if(meet==2)cout<<"v";
				if(meet==3)cout<<"<";
				if(meet==4)cout<<">";
				continue;
			}
            //如果a[i][j]为空
			if(a[i][j]==0)cout<<".";
            //不然a[i][j]就是字母。
            else cout<<a[i][j];
		}
		cout<<endl;
	}
	//cout<<meet<<" "<<endl;
	return 0;
}

```
为什么这个代码只有71分呢？

因为"如果面前有棋子，则将其向前推一步。"

但是题目没提到的是

如果你的前面有棋子，棋子的前面也有棋子。

棋子要一起向前推。

所以加上一个将棋子的前面的棋子也向前推的函数
```
void T(int x,int y)
{
	if(x<1||x>8||y<1||y>8)return;//到了边界就不推了。
	if(meet==1)
	{
		if(a[x-1][y])T(x-1,y);
		a[x-1][y]=a[x][y];
		a[x][y]=0;
	}
	if(meet==2)
	{
		if(a[x+1][y])T(x+1,y);
		a[x+1][y]=a[x][y];
		a[x][y]=0;
	}
	if(meet==3)
	{
		if(a[x][y-1])T(x,y-1);
		a[x][y-1]=a[x][y];
		a[x][y]=0;
	}
	if(meet==4)
	{
		if(a[x][y+1])T(x,y+1);
		a[x][y+1]=a[x][y];
		a[x][y]=0;
	}
}
```
最后是AC代码：
```
//伸手可耻，题目并不难，可以根据思路自己写！ 
#include<bits/stdc++.h>
using namespace std;
char a[10][10];
char q[6];//操作的前一串
char w[6];//操作的后一串
int meet;//你的朝向 1↑ 2↓ 3← 4→
int x;
int y;//你的坐标
void T(int x,int y)//移动
{
	if(x<1||x>8||y<1||y>8)return;//到达边界时就不再操作
	if(meet==1)
	{
		if(a[x-1][y])T(x-1,y);
		a[x-1][y]=a[x][y];
		a[x][y]=0;
	}
	if(meet==2)
	{
		if(a[x+1][y])T(x+1,y);//到达边界时就不再操作
		a[x+1][y]=a[x][y];
		a[x][y]=0;
	}
	if(meet==3)
	{
		if(a[x][y-1])T(x,y-1);//到达边界时就不再操作
		a[x][y-1]=a[x][y];
		a[x][y]=0;
	}
	if(meet==4)
	{
		if(a[x][y+1])T(x,y+1);//到达边界时就不再操作
		a[x][y+1]=a[x][y];
		a[x][y]=0;
	}
}
void move(int n) {
	if(meet==1) {//上
		for(int i=1; i<=n; i++) {
			if(x==1)continue;//到达边界时就不再操作
			if(a[x-1][y])T(x-1,y);
			x--;
		}
	}
	if(meet==2)//下
		for(int i=1; i<=n; i++) {
			if(x==8)continue;//到达边界时就不再操作
			if(a[x+1][y])T(x+1,y);
			x++;
		}
	if(meet==3)//左
		for(int i=1; i<=n; i++) {
			if(y==1)continue;//到达边界时就不再操作
			if(a[x][y-1])T(x,y-1);
			y--;
		}
	if(meet==4)//右
		for(int i=1; i<=n; i++) {
			if(y==8)continue;//到达边界时就不再操作
			if(a[x][y+1])T(x,y+1);
			y++;
		}
}
int main() {
	for(int i=1; i<=8; i++)
		for(int j=1; j<=8; j++) {
			cin>>a[i][j];
			if(a[i][j]=='.')a[i][j]=0;//将“.”清为零，好做以后的操作
			if(a[i][j]=='^') {
				x=i;
				y=j;
                //记录当前坐标
				meet=1;
                //记录当前方向
				a[i][j]=0;
                //当前坐标录入后记得清零
			}
			if(a[i][j]=='v') {
				x=i;
				y=j;
				meet=2;
				a[i][j]=0;
			}
			if(a[i][j]=='<') {
				x=i;
				y=j;
				meet=3;
				a[i][j]=0;
			}
			if(a[i][j]=='>') {
				x=i;
				y=j;
				meet=4;
				a[i][j]=0;
			}
		}
    //操作输入
	while(cin>>q) {
		if(q[0]=='#')break;
		if(q[0]=='m') {
			int n;
			cin>>n;
			move(n);//移动
		} else if(q[0]=='t') {
			cin>>w;//1↑ 2↓ 3← 4→
			if(w[0]=='l') {//左转
				if(meet==1)meet=3;
				else if(meet==2)meet=4;
				else if(meet==3)meet=2;
				else if(meet==4)meet=1;
			}
			if(w[0]=='r') {//右转
				if(meet==1)meet=4;
				else if(meet==2)meet=3;
				else if(meet==3)meet=1;
				else if(meet==4)meet=2;
			}
			if(w[0]=='b') {//后转
				if(meet==1)meet=2;
				else if(meet==2)meet=1;
				else if(meet==3)meet=4;
				else if(meet==4)meet=3;
			}
		}
	}
	for(int i=1; i<=8; i++) {
		for(int j=1; j<=8; j++) {
			if(i==x&&j==y) { //如果a[i][j]是我们现在位置的话
				if(meet==1)cout<<"^";
				if(meet==2)cout<<"v";
				if(meet==3)cout<<"<";
				if(meet==4)cout<<">";
				continue;
			}
            //如果a[i][j]为空
			if(a[i][j]==0)cout<<".";
            //不然a[i][j]就是字母。
			else cout<<a[i][j];
		}
		cout<<endl;
	}
	//cout<<meet<<" "<<endl;
	return 0;
}

```


---

## 作者：Mashiro_ylb (赞：2)

#恶心的大模拟

这是一道说难也不难，说简单但很恶心的模拟题（代码较长，实现较为复杂）。其实这道题没什么好说的，按照题意按部就班地进行模拟就行了（一定要沉住气，我有好几次有想要砸电脑的冲动）。实际实现起来的话，建议在判断障碍物时使用递归代替循环，这样能有效减小代码长度与实现复杂度；在处理方向时，把4个方向用编号代替然后建立两个一维数组存储该编号下移动所造成的x，y坐标变化即可。具体实现就是靠耐力了，题意没有什么不可理解的，还是那一句话，按部就班地进行模拟即可（这道题还是很恶心的！！！）

详情请见代码

···cpp  **(๑•̀ㅂ•́)و✧**

















```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#define Mashiro_ylb
using namespace std;
bool flag = 1;
template<class T>void read(T &x)    //读入优化
{
    int f = 0; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x = f? -x : x;
}
void write(long long x)  //输出优化
{
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int maxn = 27;
char data_char_map[maxn][maxn];
struct node
{
    int x;
    int y;
    int fang_xian;
} weizhi_MAP;  //当前的坐标以及方向
char fang_xian[4] = {'v','>','^','<'};  //4个方向
int dx[4] = {1,0,-1,0};  //该编号下行走x，y的坐标变化
int dy[4] = {0,1,0,-1};
int weizhi_MAP_vitor(int x, int y)  //查询边界
{
    if(x < 1 || x > 8)
        return 0;
    if(y < 1 || y > 8)
        return 0;
    return 1;
}
void move_tihua_dfs_map(int x, int y)  //查询障碍物
{
    if(data_char_map[x][y]=='.')
    {
        data_char_map[x][y] = data_char_map[x-dx[weizhi_MAP.fang_xian]][y-dy[weizhi_MAP.fang_xian]];
        data_char_map[x-dx[weizhi_MAP.fang_xian]][y-dy[weizhi_MAP.fang_xian]] = '.';
    }
    else
    {
        move_tihua_dfs_map(x+dx[weizhi_MAP.fang_xian],y+dy[weizhi_MAP.fang_xian]);
        data_char_map[x][y] = data_char_map[x-dx[weizhi_MAP.fang_xian]][y-dy[weizhi_MAP.fang_xian]];
        data_char_map[x-dx[weizhi_MAP.fang_xian]][y-dy[weizhi_MAP.fang_xian]] = '.';
    }
}
void move_next_map()  //移动
{
    for(int i = 0; i <= 8; i++)
    {
        data_char_map[0][i] = '.';
        data_char_map[i][0] = '.';
        data_char_map[9][i] = '.';
        data_char_map[i][9] = '.';
    }
    data_char_map[weizhi_MAP.x][weizhi_MAP.y] = '.';
    if(!weizhi_MAP_vitor(weizhi_MAP.x+dx[weizhi_MAP.fang_xian], weizhi_MAP.y+dy[weizhi_MAP.fang_xian]))
        return ;
    move_tihua_dfs_map(weizhi_MAP.x+dx[weizhi_MAP.fang_xian], weizhi_MAP.y+dy[weizhi_MAP.fang_xian]);
    weizhi_MAP.x += dx[weizhi_MAP.fang_xian];
    weizhi_MAP.y += dy[weizhi_MAP.fang_xian];
}
int main()
{
    char a[maxn];
    char b[maxn];
    int bushu_map_char;
    while(scanf("%s",data_char_map[1]+1))
    {
        if(data_char_map[1][1] == '-')
            break;
        for(int i = 2; i <= 8; i++)
        {
            scanf("%s",data_char_map[i]+1);
        }
        for(int i = 1; i <= 8; i++)
        {
            for(int j = 1; j <= 8; j++)
            {
                if(data_char_map[i][j] == 'v')  //预处理坐标和方向
                {
                    weizhi_MAP.x = i;
            weizhi_MAP.y = j;
            weizhi_MAP.fang_xian = 0;
                }
                else if(data_char_map[i][j] == '>')
                {
                    weizhi_MAP.x = i;
            weizhi_MAP.y = j;
            weizhi_MAP.fang_xian = 1;
                }
                else if(data_char_map[i][j] == '^')
                {
                    weizhi_MAP.x = i;
            weizhi_MAP.y = j;
            weizhi_MAP.fang_xian = 2;
                }
                else if(data_char_map[i][j] == '<')
                {
                    weizhi_MAP.x = i;
            weizhi_MAP.y = j;
            weizhi_MAP.fang_xian = 3;
                }
            }
        }
        while(scanf("%s",a))
        {
            if(a[0] == '#')
                {
                    flag = 0;
                    break;
                }
            if(a[0] == 't')
              {
                scanf("%s",b);
                if(b[0] == 'l')
                    weizhi_MAP.fang_xian = (weizhi_MAP.fang_xian + 1) % 4;
                else if(b[0]=='r')
                    weizhi_MAP.fang_xian = (weizhi_MAP.fang_xian + 3) % 4;
                else
                    weizhi_MAP.fang_xian = (weizhi_MAP.fang_xian + 2) % 4;
              }
            else
              {
                read(bushu_map_char);
                for(int i = 0; i < bushu_map_char; i++)
                  {
                    move_next_map();
                  }
              }
        }
        data_char_map[weizhi_MAP.x][weizhi_MAP.y] = fang_xian[weizhi_MAP.fang_xian];
        for(int i = 1; i <= 8; i++)  //输出
          {
            for(int j = 1; j <= 8; j++)
              {
                printf("%c", data_char_map[i][j]);
              }
            putchar(10);
          }
        putchar(10);
        if(flag == 0) return 0;  //弹出程序
    }
    return 0;
}
```
```cpp

---

## 作者：就皮这一下 (赞：1)

首先确认：这道题应该是一道模拟题。暴力模拟过程，最后输出最后的棋盘。

让我们看看这道题的要点：

- 改变方向和移动
- 推动棋子
- 删掉越界的棋子，阻止小箭头越界

接下来，让我们分析一下如何处理这些条件。

### 改变方向

有一个很方便的做法：顺时针依次把各个方向设定为 0,1,2,3，利用取模运算实现“循环”的效果。

![图片.png](https://i.loli.net/2020/05/07/PSJxiaCMhkGoBdl.png)

### 移动箭头

可以像冒泡排序那样一点点把它“挪”走。换言之，我们会“一步一步”地移动——毕竟 8*8 的棋盘，几乎不会 TLE。

### 推动棋子

如果我们在移动箭头的时候发现被棋子挡住了去路，我们就可以**把这个棋子向同向移动一格**。
下面的代码也可以用来移动箭头。

``` cpp
void push_forward(int sx,int sy) {
    bool valid(int,int);
    if (!valid(sx,sy)) {map[sx][sy] = '.';return;}
    int nx = sx+dx[orien], ny = sy+dy[orien];
    if (map[nx][ny] != '.') push_forward(nx, ny);
    std::swap(map[sx][sy], map[nx][ny]);
}
```

为了确保大家都能看明白，再附一幅图。

![](https://cdn.luogu.com.cn/upload/image_hosting/w8zc5h72.png)

### 删掉越界棋子，阻止小箭头越界。

~~这一步我偷了个小懒~~所谓删掉越界棋子，不过就是把棋子变成空地，因此我**在棋盘周围围上一圈空地，移动时直接把棋子和空地交换位置，下次操作之前把“出界的棋子”变成空地**（详细实现请向上翻）。

最后，阻止小箭头越界难度更低了，我这里用的是提前计算出小箭头要到哪里，然后特判。

```cpp
void move (int &x,int &y,int step) {
    int nx = dx[orien]*step+x, ny = dy[orien]*step+y;
    if (!valid(nx, ny)) {
        switch(orien) {
            case 0:nx = 1;step = x-nx;break;
            case 1:ny = 8;step = ny-y;break;
            case 2:nx = 8;step = nx-x;break;
            case 3:ny = 1;step = y-ny;break;
        }
    }
    while(x != nx || y != ny) {
        push_forward(x, y);
        x += dx[orien], y+= dy[orien];
    }
}
```

## 最后的思路

算出箭头的末状态，然后一步一步地挪动；如果撞到了棋子，就递归移动棋子。开始的时候，把箭头替换成 $ 符号，输出时再根据朝向处理。

~~很抱歉，由于谷 markdown 玄学问题，完整代码贴不上了（哭）~~
好在关键代码都在上面，希望大家能有自己实现程序的能力~




---

## 作者：_Ayanami_ (赞：1)

## 模拟题

这里我们分别解释一下需要做两个操作

#### 转向操作:
开一个f记录当前方向

0、1、2、3分别表示上、右、下、左
```cpp
if(s=="turn")
{
	cin>>s;
	if(s=="right")
	{
		f++;//向右转
	}
	if(s=="back")
	{
		f+=2;//向后转(向右转两次)
	}
	if(s=="left")
	{
		f+=3;//向左转(向右转三次)
	}
	f%=4;//记得%4
}
```
#### 前进+推棋子操作:

每次向当前方向前进一步

如果前方是棋子就执行推棋子操作
```cpp
if(s=="move")
{
	cin>>m;
	while(m>0&&in(x+fx[f],y+fy[f]))//如果仍在界内
	{				
		if(a[x+fx[f]][y+fy[f]]!='.')//如果前方是棋子
		{
			Push(x+fx[f],y+fy[f]);//推棋子
		}
		x+=fx[f];//方向数组
		y+=fy[f];//移动一步
		m--;
	}
}
```
推棋子时注意前面有多个相连棋子要一起推

我们直接从当前位置向前while找到第一个不是棋子的地方(空地或边界)

然后从那个位置开始反过来for一遍更新位置

例如当前状态为

EDC.BA<.

第一次会找到C和B中间的空地

EDCBA<..

第二次会直接找到边界

DCBA<...
```cpp
void Push(int xx,int yy)//推棋子
{
	v=1;
	while(a[xx+v*fx[f]][yy+v*fy[f]]!='.'&&in(xx+(v+1)*fx[f],yy+(v+1)*fy[f]))//找到第一个非棋子的位置
	{
		v++;//前方相连的棋子数
	}
	for(int i=v;i>0;i--)
	{
		a[xx+i*fx[f]][yy+i*fy[f]]=a[xx+(i-1)*fx[f]][yy+(i-1)*fy[f]];//前移一格
		a[xx+(i-1)*fx[f]][yy+(i-1)*fy[f]]='.';//原来的位置更新空地
		
	}
}
```
完整代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int x,y,f,m,v,fx[4]={-1,0,1,0},fy[4]={0,1,0,-1};
char a[10][10],t;
string s,ss;
bool in(int xx,int yy)//判定是否越界
{
	if(xx>0&&xx<9&&yy>0&&yy<9)//如果在界内
	{
		return true;//返回真
	}
	else
	{
		return false;//否则返回假
	}
}
void Push(int xx,int yy)//推棋子
{
	v=1;
	while(a[xx+v*fx[f]][yy+v*fy[f]]!='.'&&in(xx+(v+1)*fx[f],yy+(v+1)*fy[f]))//找到第一个非棋子的位置
	{
		v++;//前方相连的棋子数
	}
	for(int i=v;i>0;i--)
	{
		a[xx+i*fx[f]][yy+i*fy[f]]=a[xx+(i-1)*fx[f]][yy+(i-1)*fy[f]];//前移一格
		a[xx+(i-1)*fx[f]][yy+(i-1)*fy[f]]='.';//原来的位置更新空地
	}
}
int main()
{
	//读入棋盘初始状态
	for(int i=1;i<9;i++)
	{
		for(int j=1;j<9;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='^')
			{
				a[i][j]='.';
				f=0;
				x=i;
				y=j;
			}
			if(a[i][j]=='>')
			{
				a[i][j]='.';
				f=1;
				x=i;
				y=j;
			}
			if(a[i][j]=='v')
			{
				a[i][j]='.';
				f=2;
				x=i;
				y=j;
			}
			if(a[i][j]=='<')
			{
				a[i][j]='.';
				f=3;
				x=i;
				y=j;
			}
		}
	}
	//读入操作+处理
	cin>>s;
	while(s!="#")
	{
		if(s=="turn")
		{
			cin>>s;
			if(s=="right")
			{
				f++;//向右转
			}
			if(s=="back")
			{
				f+=2;//向后转(向右转两次)
			}
			if(s=="left")
			{
				f+=3;//向左转(向右转三次)
			}
			f%=4;//记得%4
		}
		if(s=="move")
		{
			cin>>m;
			while(m>0&&in(x+fx[f],y+fy[f]))//如果仍在界内
			{				
				if(a[x+fx[f]][y+fy[f]]!='.')//如果前方是棋子
				{
					Push(x+fx[f],y+fy[f]);//推棋子
				}
				x+=fx[f];//方向数组
				y+=fy[f];//移动一步
				m--;
			}
		}
		cin>>s;
	}
	//输出最终状态
	for(int i=1;i<9;i++)
	{
		for(int j=1;j<9;j++)
		{
			if(i==x&&j==y)
			{
				if(f==0)
				{
					cout<<'^';
				}
				if(f==1)
				{
					cout<<'>';
				}
				if(f==2)
				{
					cout<<'v';
				}
				if(f==3)
				{
					cout<<'<';
				}
			}
			else
			{
				cout<<a[i][j];
			}
			
		}
		cout<<endl;
	}
}
```

---

## 作者：月下诺 (赞：0)


 

 题目简述就是推棋子走棋盘（不能出棋盘），然后经历一系列花里胡哨的操作以后 判断位置
一开始在做的时候没有考虑一个问题 所以没有AC 原因如下：

因为"如果面前有棋子，则将其向前推一步。"

但是题目没提到的是

如果你的前面有棋子，棋子的前面也有棋子。

棋子要一起向前推。

所以加上一个将棋子的前面的棋子也向前推的函数

后来加上了 所以就是下面的AC代码了

 ```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10][10];
char b[6];//操作的前一串
char c[6];//操作的后一串
int fangxiang;//你的朝向 1↑ 2↓ 3← 4→
int x,y;
void yidong(int x, int y) { //移动
	if(x<1||x>8||y<1||y>8)
		return;//到达边界时就不再操作
	if(fangxiang==1) {
		if(a[x-1][y])
			yidong(x-1,y);
		a[x-1][y]=a[x][y];//替换坐标位置
		a[x][y]=0;//原来位置化0
	}
	if(fangxiang==2) {
		if(a[x+1][y])
			yidong(x+1,y);//到达边界时就不再操作
		a[x+1][y]=a[x][y];//替换坐标位置
		a[x][y]=0;//原来位置化0
	}
	if(fangxiang==3) {
		if(a[x][y-1])
			yidong(x,y-1);//到达边界时就不再操作
		a[x][y-1]=a[x][y];//替换坐标位置
		a[x][y]=0;//原来位置化0
	}
	if(fangxiang==4) {
		if(a[x][y+1])
			yidong(x,y+1);//到达边界时就不再操作
		a[x][y+1]=a[x][y];//替换坐标位置
		a[x][y]=0;//原来位置化0
	}
}
void move(int n) {
	if(fangxiang==1) {//上
		for(int i=1; i<=n; i++) {
			if(x==1) continue;//到达边界时就不再操作
			if(a[x-1][y])
				yidong(x-1,y);
			x--;
		}
	}
	if(fangxiang==2)//下
		for(int i=1; i<=n; i++) {
			if(x==8) continue;//到达边界时就不再操作
			if(a[x+1][y])
				yidong(x+1,y);
			x++;
		}
	if(fangxiang==3)//左
		for(int i=1; i<=n; i++) {
			if(y==1)continue;//到达边界时就不再操作
			if(a[x][y-1])
				yidong(x,y-1);
			y--;
		}
	if(fangxiang==4)//右
		for(int i=1; i<=n; i++) {
			if(y==8)continue;//到达边界时就不再操作
			if(a[x][y+1])
				yidong(x,y+1);
			y++;
		}
}
int main() {
	for(int i=1; i<=8; i++)
		for(int j=1; j<=8; j++) {
			cin>>a[i][j];
			if(a[i][j]=='.')
				a[i][j]=0;//将“.”清为零，好做以后的操作
			if(a[i][j]=='^') {
				x=i;
				y=j;
				//记录当前坐标
				fangxiang=1;
				//记录当前方向
				a[i][j]=0;
				//当前坐标录入后记得清零
			}
			if(a[i][j]=='v') {
				x=i;
				y=j;
				fangxiang=2;
				a[i][j]=0;
			}
			if(a[i][j]=='<') {
				x=i;
				y=j;
				fangxiang=3;
				a[i][j]=0;
			}
			if(a[i][j]=='>') {
				x=i;
				y=j;
				fangxiang=4;
				a[i][j]=0;
			}
		}
	//操作输入
	while(cin>>b) {
		if(b[0]=='#')break;
		if(b[0]=='m') {
			int n;
			cin>>n;
			move(n);//移动
		} else if(b[0]=='t') {
			cin>>c;//1↑ 2↓ 3← 4→
			if(c[0]=='l') {//向左转
				if(fangxiang==1)
					fangxiang=3;
				else if(fangxiang==2)
					fangxiang=4;
				else if(fangxiang==3)
					fangxiang=2;
				else if(fangxiang==4)
					fangxiang=1;
			}
			if(c[0]=='r') {//向右转
				if(fangxiang==1)
					fangxiang=4;
				else if(fangxiang==2)
					fangxiang=3;
				else if(fangxiang==3)
					fangxiang=1;
				else if(fangxiang==4)
					fangxiang=2;
			}
			if(c[0]=='b') {//向后转
				if(fangxiang==1)
					fangxiang=2;
				else if(fangxiang==2)
					fangxiang=1;
				else if(fangxiang==3)
					fangxiang=4;
				else if(fangxiang==4)
					fangxiang=3;
			}
		}
	}
	for(int i=1; i<=8; i++) {
		for(int j=1; j<=8; j++) {
			if(i==x&&j==y) { //如果a[i][j]是我们现在位置的话
				if(fangxiang==1)
					cout<<"^";
				if(fangxiang==2)
					cout<<"v";
				if(fangxiang==3)
					cout<<"<";
				if(fangxiang==4)
					cout<<">";
				continue;
			}
			//如果a[i][j]为空
			if(a[i][j]==0)
				cout<<".";
			//不然a[i][j]就是字母。
			else cout<<a[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：brealid (赞：0)

作者使用了**位域**完成了这题。

引入：
> 有些信息在存储时，并不需要占用一个完整的字节， 而只需占几个或一个二进制位。例如在存放一个开关量时，只有0和1 两种状态， 用一位二进位即可。为了节省存储空间，并使处理简便，Ｃ语言又提供了一种数据结构，称为“位域”或“位段”。所谓“位域”是把一个字节中的二进位划分为几 个不同的区域，并说明每个区域的位数。每个域有一个域名，允许在程序中按域名进行操作。 这样就可以把几个不同的对象用一个字节的二进制位域来表示。  
> ——摘自 csdn博客 sty124578

[右转了解位域 in luogu blog](https://www.luogu.com.cn/blog/hkxa/introduction-BitField)

这里处理转向，使用位域将会非常方便。  
首先定义移动用数组
```cpp
const int xx[] = {1, 0, -1, 0}, yy[] = {0, -1, 0, 1};
```
注意到如果这样写，
- $(xx[0],yy[0])$就对应向下
- $(xx[1],yy[1])$就对应向左
- $(xx[2],yy[2])$就对应向上
- $(xx[3],yy[3])$就对应向右

然后考虑到 4 种情况，方向值 ``dir`` 是在 $\bmod\ 2^2$ 意义下的。
所以定义
```cpp
struct pos {
    int x, y;
    uint8 dir : 2;
    void turn(char ch)
    {
        switch (ch) {
            case 'l' : dir--; break; // left
            case 'r' : dir++; break; // right
            case 'b' : dir ^= 2; break; // back
        }
    }
};
```
注意到 ``turn`` 函数里，我没有使用模运算，而是直接加，减。（对于 ``turn back`` 操作，``+2/-2`` 在 $\bmod\ 2^2$ 意义下只需要改变第 2 个 bit 的值即可，所以对于 ``dir ^= 2`` 请感性理解）

[AC Code](/paste/dxt4tpng)

---

## 作者：我没有小白 (赞：0)

~~比时间复杂度简单多了~~

~~而且思路非常暴力~~

话不多~~bb~~

让我们一起来看这道题暴力的思路 ~~虽然没几个人做~~

# 什么dance

首先我做这道题的时候先考虑的是，这真是一道好玩的模拟，他跟推箱子相仿，~~我感觉我都可以写推箱子了qwq~~

于是怀着程序员的好奇心开始写这道题了

首先我们为了防止程序简单，我们记录当前点的坐标，然后将当前点抹为$"."$，以便于我们程序更好的进行。

然后就是前进的问题。

如果前面是空地，毫无疑问，直接向前走。

如果前面是字符，先别急着往前推，我们先遍历字符前面的点，如果遍历到一个空地，我们再推

如果当前点到达了边界，直接break掉，完事。

然后献上我丑陋的代码
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

char s[10][10];
int dic=0,x,y;       //1上 2下 3左 4右
int db[5]= {0,2,1,4,3};
int dr[5]= {0,4,3,1,2};
int dl[5]= {0,3,4,2,1};
char pri[4]= {'^','v','<','>'};
void debug() {
	for(int i=1; i<=8; i++) {
		for(int j=1; j<=8; j++) {
			if(x==i&&y==j)cout<<pri[dic-1];
			else
				cout<<s[i][j];
		}
		cout<<endl;
	}
}
void go_up(int k) {
	int dx=x,dy=y;
	for(int i=x-1; i>=1; i--) {
		if(dx==1)break;
		if(!k)break;
		if(s[i][y]=='.') {
			dx--;
			k--;
			continue;
		}
		if(s[i][y]!='.') {
			int flag=i;
			for(int j=i; j>=1; j--)
				if(s[j][y]=='.'||j==1) {
					flag=j;
					break;
				}
			for(int j=flag; j<=i; j++)
				s[j][y]=s[j+1][y];
			dx--,k--;
		}
	}
	x=dx;
}
void go_down(int k) {
	int dx=x,dy=y;
	for(int i=x+1; i<=8; i++) {
		if(dx==8)break;
		if(!k)break;
		if(s[i][y]=='.') {
			dx++;
			k--;
			continue;
		}
		if(s[i][y]!='.') {
			int flag=i;
			for(int j=i; j<=8; j++)
				if(s[j][y]=='.'||j==8) {
					flag=j;
					break;
				}
			for(int j=flag; j>=i; j--)
				s[j][y]=s[j-1][y];
			dx++,k--;
		}
	}
	x=dx;
}
void go_lf(int k) {
	int dy=y;
	for(int i=y-1; i>=1; i--) {
		if(dy==1)break;
		if(k==0)break;
		if(s[x][i]=='.') {
			dy--;
			k--;
			continue;
		}
		if(s[x][i]!='.') {
			int flag=i;
			for(int j=i; j>=1; j--) {
				if(s[x][j]=='.'||j==1) {
					flag=j;
					break;
				}

			}
			for(int j=flag; j<=i; j++)
				s[x][j]=s[x][j+1];
			dy--,k--;
		}
	}
	y=dy;
}
void go_ri(int k) {
	int dy=y;
	for(int i=y+1; i<=8; i++) {
		if(dy==8)break;
		if(!k)break;
		if(s[x][i]=='.') {
			dy++;
			k--;
			continue;
		}
		if(s[x][i]!='.') {
			int flag=i;
			for(int j=i; j<=8; j++) {
				if(s[x][j]=='.'||j==8) {
					flag=j;
					break;
				}

			}
			for(int j=flag; j>=i; j--)
				s[x][j]=s[x][j-1];
			dy++,k--;
		}
	}
	y=dy;
}
int main() {
//	freopen("aa.out","w",stdout);
	for(int i=1; i<=8; i++)
		for(int j=1; j<=8; j++) {
			cin >> s[i][j];
			if(s[i][j]=='^') {
				dic=1;
				s[i][j]='.';
				x=i,y=j;
			}
			if(s[i][j]=='v') {
				dic=2;
				x=i,y=j;
				s[i][j]='.';
			}
			if(s[i][j]=='<') {
				x=i,y=j;
				s[i][j]='.';
				dic=3;
			}
			if(s[i][j]=='>') {
				x=i,y=j;
				s[i][j]='.';
				dic=4;
			}
		}
	string a,b;
	int c;
	int t=0;
	while(1) {
		cin >> a;
		if(a=="#")break;
		else if(a=="turn") {
			cin >> b;
			if(b=="right")dic=dr[dic];
			else if(b=="left")dic=dl[dic];
			else if(b=="back")dic=db[dic];
		} else if(a=="move") {
			cin >> c;
			if(dic==1)go_up(c);
			else if(dic==2)go_down(c);
			else if(dic==3)go_lf(c);
			else if(dic==4)go_ri(c);
		}
//		printf("%d:",++t);
//		puts("");
//		debug();
	}
	debug();
}
```

管理大大求过

---

## 作者：Steinway (赞：0)

~~这题一点都不恶心~~  
  
~~这题一点都不难~~

~~我差点就一遍AC了~~

讲下思路吧（下面几个dalao都是变态 这道题我码了1个半小时）  

首先是移动和转向 用简单的几个函数就可以解决了

然后就是比较难的连续方块有字母 我选择用类似冒泡的思想 不停的转移 然后第一个方块用 方向字符代替就好了

（被函数起始化导致变量莫名其妙归0坑的不知所措）

然后便是大家都喜欢的 270行代码（窃笑

```
// #define fre yes

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10;
char Map[maxn][maxn];

int flag = 0,sx,sy,tnt,tot;

//毒瘤快读
template<typename T>inline void read(T&x)
{
    x = 0;char c;int lenp = 1;
    do { c = getchar();if(c == '-') lenp = -1; } while(!isdigit(c));
    do { x = x * 10 + c - '0';c = getchar(); } while(isdigit(c));
    x *= lenp;
}

//开始检测初始位置（就是><v^的位置）
void Magic()
{
    int poi = 1;
    int dx = 0,dy = 0;
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if(Map[i][j] == '^')
            {
                dx = i;
                dy = j;
                flag = 1;
                poi = 0;break;
            }
            if(Map[i][j] == '>')
            {
                dx = i;
                dy = j;
                flag = 2;
                poi = 0;break;
            }
            if(Map[i][j] == 'v')
            {
                dx = i;
                dy = j;
                flag = 3;
                poi = 0;break;
            }
            if(Map[i][j] == '<')
            {
                dx = i;
                dy = j;
                flag = 4;
                poi = 0;break;
            }
        } if(poi == 0) break;
    } sx = dx;sy = dy;
}

//判断是否出界
bool legal(int x,int y)
{
    if(x >= 0 && y >= 0 && x < 8 && y < 8) return true;
     return false;
}

//有关物品碰撞之后移动的处理（就是前面有连续的物品 我们需要连续移动它们）
void check(int x,int y)
{
    tnt = 0;char z,c;
    if(flag == 1)
    {
        while(x>=0)
        {
            x--;
            if(legal(x,y) && Map[x][y] == '.')
            {
                if(tnt == 0) Map[x][y] = Map[x+1][y];
                else Map[x][y] = z;
                break;
            }
            if(legal(x,y))
            {
                tnt++;
                c = Map[x][y];
                if(tnt == 1) Map[x][y] = Map[x+1][y];
                else { Map[x][y] = z; }
                z = c;
            } else break;
        }
    }
    if(flag == 2)
    {
        while(y<=7)
        {
            y++;
            if(legal(x,y) && Map[x][y] == '.')
            {
                if(tnt == 0) Map[x][y] = Map[x][y-1];
                else Map[x][y] = z;
                break;
            }
            if(legal(x,y))
            {
                tnt++;
                c = Map[x][y];
                if(tnt == 1) Map[x][y] = Map[x][y-1];
                else { Map[x][y] = z; }
                z = c;
            } else break;
        }
    }
    if(flag == 3)
    {
        while(x<=7)
        {
            x++;
            if(legal(x,y) && Map[x][y] == '.')
            {
                if(tnt == 0) Map[x][y] = Map[x-1][y];
                else Map[x][y] = z;
                break;
            }
            if(legal(x,y))
            {
                tnt++;
                c = Map[x][y];
                if(tnt == 1) Map[x][y] = Map[x-1][y];
                else { Map[x][y] = z; }
                z = c;
            } else break;
        }
    }
    if(flag == 4)
    {
        while(y>=0)
        {
            y--;
            if(legal(x,y) && Map[x][y] == '.')
            {
                if(tnt == 0) Map[x][y] = Map[x][y+1];
                else Map[x][y] = z;
                break;
            }
            if(legal(x,y))
            {
                tnt++;
                c = Map[x][y];
                if(tnt == 1) Map[x][y] = Map[x][y+1];
                else { Map[x][y] = z; }
                z = c;
            } else break;
        }
    }
}

//移动我们的小指针 这里对应我们题中move
void Move(int x,int y,int z)
{
    if(flag == 1)
    {
        while(z--)
        {
            x--;
            if(legal(x,y))
            {
                if(Map[x][y] != '.') { check(x,y);Map[x][y] = '^';Map[x+1][y] = '.'; }
                else Map[x][y] = '^',Map[x+1][y] = '.';
            } else { x = 0;break; }
        }
    } 
    if(flag == 2)
    {
        while(z--)
        {
            y++;
            if(legal(x,y))
            {
                if(Map[x][y] != '.') { check(x,y);Map[x][y] = '>';Map[x][y-1] = '.'; }
                else Map[x][y] = '>',Map[x][y-1] = '.';
            } else { y = 7;break; }
        }
    }
    if(flag == 3)
    {
        while(z--)
        {
            x++;
            if(legal(x,y))
            {
                if(Map[x][y] != '.') { check(x,y);Map[x][y] = 'v';Map[x-1][y] = '.'; }
                else Map[x][y] = 'v',Map[x-1][y] = '.';
            } else { x = 7;break; }
        }
    }
    if(flag == 4)
    {
        while(z--)
        {
            y--;
            if(legal(x,y))
            {
                if(Map[x][y] != '.') { check(x,y);Map[x][y] = '<';Map[x][y+1] = '.'; }
                else Map[x][y] = '<',Map[x][y+1] = '.';
            } else { y = 0;break; }
        }
    } sx = x;sy = y;
}

//强行转向（很难看 不建议这样打）
void change(int x,int y)
{
    if(x == 1 && y == 1) flag = 4;
    else if(x == 1 && y == 2) flag = 2;
    else if(x == 1 && y == 3) flag = 3;
    else if(x == 2 && y == 1) flag = 1;
    else if(x == 2 && y == 2) flag = 3;
    else if(x == 2 && y == 3) flag = 4;
    else if(x == 3 && y == 1) flag = 2;
    else if(x == 3 && y == 2) flag = 4;
    else if(x == 3 && y == 3) flag = 1;
    else if(x == 4 && y == 1) flag = 3;
    else if(x == 4 && y == 2) flag = 1;
    else if(x == 4 && y == 3) flag = 2;
}

int main()
{
//下了几次数据（蒟蒻）
#ifdef fre
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
	
    for (int i=0;i<8;i++) scanf("%s",Map[i]);
    //模拟题很喜欢用函数 不知道是不是好习惯
    Magic();
    while(1)
    {
        string c;
        cin >> c;
        if(c == "#") break;
        else if(c == "move")
        {
            int x;
            read(x);
            if(x == 0) continue;
            Move(sx,sy,x); //当前位置和移动步数
        }
        else if(c == "turn")
        {
        	//蒟蒻常用string 灰常好用 打一遍用一年 string不花一分钱
            string r;
            cin >> r;
            string a="left",b="right",c="back";
            if(r == a) change(flag,1); 
            else if(r == b) change(flag,2);
            else if(r == c) change(flag,3);
            if(flag == 1) Map[sx][sy] = '^';
            if(flag == 2) Map[sx][sy] = '>';
            if(flag == 3) Map[sx][sy] = 'v';
            if(flag == 4) Map[sx][sy] = '<';
        }
    }
	
    //输出
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            printf("%c",Map[i][j]);
        } puts("");
    } return 0;
}//Over
```


---

## 作者：Scarlet_Hypoc (赞：0)

这道题恶心就恶心在它有四个方向，这说明你的每个操作都需要判断四种做法，这就使得代码量很大了，但其实只要有耐心不难AC（鬼知道为什么现在才8个人AC），题目中还有一个地方我认为没有解释清楚的，搞得我纠结了半天（这代码量错了重来要命的啊），最后竟然蒙对了！

题中说“如果面前有棋子，则将其向前推一步”并不是指本来要走n步的但是你遇到棋子后就只走一步，是指你走几步就会把它也推几步，其他也没有啥坑点了，上代码！



        

```cpp
#include <cstdio>
#include <cstring>
int n=8;
char s[10][10];
int x,y,fx;//fx表示方向，用8表示上，4表示左，6表示右，2表示下（其实就是小键盘上的方向，方便嘛）
void turnleft()//左转
{
    if(fx==2)fx=6;
    else if(fx==6)fx=8;
    else if(fx==8)fx=4;
    else if(fx==4)fx=2;
}
void turnright()//右转
{
    if(fx==2)fx=4;
    else if(fx==4)fx=8;
    else if(fx==8)fx=6;
    else if(fx==6)fx=2;
}
void turnback()//后转
{
    if(fx==2)fx=8;
    else if(fx==4)fx=6;
    else if(fx==8)fx=2;
    else if(fx==6)fx=4;
}
void change()//修改‘我’的样子
{
    if(fx==2)s[x][y]='v';
    if(fx==4)s[x][y]='<';
    if(fx==8)s[x][y]='^';
    if(fx==6)s[x][y]='>';
}
void output()//输出
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        printf("%c",s[i][j]);
        printf("\n");
    }
}
void find()//寻找一开始‘我’的位置，并记录方向
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s[i][j]=='^')
            {
                x=i;y=j;fx=8;
                break;
            }
            if(s[i][j]=='v')
            {
                x=i;y=j;fx=2;
                break;
            }
            if(s[i][j]=='<')
            {
                x=i;y=j;fx=4;
                break;
            }
            if(s[i][j]=='>')
            {
                x=i;y=j;fx=6;
                break;
            }
        }
    }
}
void movedown()//向下移动
{
    if(x==n)return;
    int xx=x,yy=y;
    char mv='.';//用mv记录上一个棋子，一开始为.  因为第一个棋子——也就是自己——移动后原来的位置一定会变成.
    while(s[xx][yy]!='.'&&xx<=n)//如果前面还有棋子并且未越界
    {
        char mm=mv;//记录上一个棋子
        mv=s[xx][yy];//记录这一个棋子
        s[xx][yy]=mm;//换成上一个棋子
        xx++;//一定要记得++！！
    }
    s[xx][yy]=mv;//将上一个棋子放下来
    x++;//！！
}
void moveup()//以下同上
{
    if(x==1)return;
    int xx=x,yy=y;
    char mv='.';
    while(s[xx][yy]!='.'&&xx>=1)
    {
        char mm=mv;
        mv=s[xx][yy];
        s[xx][yy]=mm;
        xx--;
    }
    s[xx][yy]=mv;
    x--;
}
void moveleft()
{
    if(y==1)return;
    int xx=x,yy=y;
    char mv='.';
    while(s[xx][yy]!='.'&&yy>=1)
    {
        char mm=mv;
        mv=s[xx][yy];
        s[xx][yy]=mm;
        yy--;
    }
    s[xx][yy]=mv;
    y--;
}
void moveright()
{
    if(y==n)return;
    int xx=x,yy=y;
    char mv='.';
    while(s[xx][yy]!='.'&&yy<=n)
    {
        char mm=mv;
        mv=s[xx][yy];
        s[xx][yy]=mm;
        yy++;
    }
    s[xx][yy]=mv;
    y++;
}
void moving(int p)//移动
{
    while(p--)//判断方向
    {
        if(fx==2)movedown();
        if(fx==4)moveleft();
        if(fx==8)moveup();
        if(fx==6)moveright();
    }
}
int main()//因为代码量庞大且复杂，于是把它变成了一个个函数方便理解且方便检查，函数意义上面有解释
{
    for(int i=1;i<=n;i++)
    scanf("%s",s[i]+1);
    find();
    char ss[11];
    while(scanf("%s",ss+1),ss[1]!='#')
    {
        if(ss[1]=='t')
        {
            char sa[11];
            scanf("%s",sa+1);
            if(sa[1]=='r')turnright();
            if(sa[1]=='l')turnleft();
            if(sa[1]=='b')turnback();
        }
        else
        {
            int move;
            scanf("%d",&move);
            moving(move);
        }
    }
    change();
    output();
}
```

---

