# Tic-tac-toe

## 题目描述

Certainly, everyone is familiar with tic-tac-toe game. The rules are very simple indeed. Two players take turns marking the cells in a $ 3×3 $ grid (one player always draws crosses, the other — noughts). The player who succeeds first in placing three of his marks in a horizontal, vertical or diagonal line wins, and the game is finished. The player who draws crosses goes first. If the grid is filled, but neither Xs, nor 0s form the required line, a draw is announced.

You are given a $ 3×3 $ grid, each grid cell is empty, or occupied by a cross or a nought. You have to find the player (first or second), whose turn is next, or print one of the verdicts below:

- illegal — if the given board layout can't appear during a valid game;
- the first player won — if in the given board layout the first player has just won;
- the second player won — if in the given board layout the second player has just won;
- draw — if the given board layout has just let to a draw.

## 样例 #1

### 输入

```
X0X
.0.
.X.
```

### 输出

```
second
```

# 题解

## 作者：Alex_Wei (赞：22)

共 $175$ 个测试点。

模拟即可，判断三个棋子是否落在同一条线上可以用 $\mathrm{dfs}$。

#### 特判细节很重要！

---

实现细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char p[6][6];//棋盘 
int f,s,pf,ps;//f是'X'的个数，s是'0'的个数，pf是判断第一个人有没有赢，ps则是判断第二个人； 
void dfs(int a,int b,int c,int d,int e,char t)//a,b是方向,c,d是当前的坐标,e是个数,t是棋子的类型('X'或'0') 
{
	if(e==3){//如果3个连成了一条线
		if(t=='X')pf=1;//第一个人赢
		else ps=1;//第二个人赢
		return;//返回
	}
	else if(a+c<4&&a+c>0&&b+d<4&&b+d>0&&p[a+c][b+d]==t)//如果没出界，并且是同样的棋子
		dfs(a,b,a+c,b+d,e+1,t);//访问下一个坐标
}
int main()
{
	for(int x=1;x<4;x++)
		for(int y=1;y<4;y++){
			cin>>p[x][y];//输入 
			if(p[x][y]=='X')f++;//第一个人的棋子 
			if(p[x][y]=='0')s++;//第二个人的棋子 
		}
	if(s>f||f-s>1){//s>f是第二个人多下了，f-s>1是第一个人多下了 
		cout<<"illegal";//非法情况 
		return 0;//返回 
	}
	for(int x=1;x<4;x++)
		for(int y=1;y<4;y++)
			if(p[x][y]!='.')//如果这个地方不是空的 
				for(int a=-1;a<2;a++)
					for(int b=-1;b<2;b++)
						if(a!=0||b!=0)//并且方向正确
							dfs(a,b,x,y,1,p[x][y]);//访问这一个坐标，记录类型 
	if((pf&&ps)||(pf&&f==s)||(ps&&f>s))cout<<"illegal";//如果两个人都赢了，或者其中一个人赢了之后又下了一枚棋子（很坑！）都是非法的
	else if(pf)cout<<"the first player won";//第一个人赢
	else if(ps)cout<<"the second player won";//第二个人赢
	else if(f+s==9)cout<<"draw";//没有人赢，并且不非法，就是平局
	else if(f>s)cout<<"second";//没下满，第二个人下棋
	else cout<<"first";//第一个人下棋
	return 0;
}
```

$\mathrm{Upd:2019.12.11:}$ 添加 $\mathrm{Latex}$，美化文章。

---

## 作者：CrTsIr400 (赞：9)

## 1.先看懂这道题
**给你个$3\times 3$的井字棋盘，观察棋局的状态**

**如果不合法，就输出illegal**

如果有三点连成一条直线的 **（斜着也可以）**

就看哪个玩家赢

棋还没下完

就要**判断两种棋子数的多少而决定谁先下**
## 2.思路
**纯模拟，多个判断**

~~似乎有位dfs大佬乱写了个暴力~~

### 2.0 输入/预处理

输入~~似乎~~大家都会，不多讲

注意还要有个桶记录字符（到时候有用）

#### code：

```cpp
void in()
{
	char c;
	for(i=0;i<=2;i++)
	for(j=0;j<=2;j++)
	{
		while((c=getchar())!='X'&&c!='0'&&c!='.');
		if(c=='X')a[i][j]=1;//a数组就是下子数组，棋盘状况
		if(c=='0')a[i][j]=2;
		t[a[i][j]]++;//桶记录
	}
} 
```

### 2.1 判断非法情况

**非法情况：$t[1]<t[2]$ 或者 $t[1]-t[2]>1$**

没了。
#### code:

```cpp
void pd_is_ill()
{
	if(t[1]<t[2]||t[1]-t[2]>1)
   printf("illegal"),exit(0);
}
```

### 2.2 算算谁会赢

看了一圈，这个重头戏的代码都太长了，我简化了一下。

**注意：还有2条对角线！！！**

**其实就是横着判断，竖着判断，斜角判断，没了。~~（滑稽~~**
#### code:

```cpp
void pd_is_win()
{
	if(a[0][0]==a[1][1]&&a[1][1]==a[2][2])sc[a[0][0]]++;
	if(a[0][2]==a[1][1]&&a[1][1]==a[2][0])sc[a[0][2]]++;
	for(i=0;i<=2;i++)if(a[i][0]==a[i][1]&&a[i][1]==a[i][2])sc[a[i][0]]++;
	for(i=0;i<=2;i++)if(a[0][i]==a[1][i]&&a[1][i]==a[2][i])sc[a[0][i]]++;
}
```

### 2.3 继续判断

**还要判断非法情况！！！**

比如说这个数据：~~（小学蒟蒻被坑了）~~

```
XXX
...
000
```
我上次写的代码是这样的（没有判断非法情况）
```cpp
void pd_is_daw()
{
	if(sc[1]>sc[2])
	printf("the first player won"),exit(0);
	if(sc[1]<sc[2])
	printf("the second player won"),exit(0);
}
```
一看cf状态：

`wrong answer on test 6`

what???

再看一下这个数据

你敢说这不是平局？

人家能同时下两步棋吗？？？

**于是改成了这样：**

```cpp
void pd_is_daw()
{
	if((sc[1]&&sc[2])||(sc[1]>0&&t[2]==t[1])||(sc[2]>0&&t[1]>t[2]))
	printf("illegal"),exit(0);
	if(sc[1]>sc[2])
	printf("the first player won"),exit(0);
	if(sc[1]<sc[2])
	printf("the second player won"),exit(0);
}
```

效果不言而喻，AC了。

### 2.4 先后顺序

判断t[1]和t[2]哪个大就行。

**特别注意：如果$t[1]=t[2]$,要输出first!!!**

不想再说了，自己看代码吧。

#### code:
```cpp
void pd_is_f_s()
{
	if(t[0]==0)return;
	if(t[1]>t[2]&&t[1]-t[2]==1)
	printf("second"),exit(0);
	if(t[1]==t[2])
	printf("first"),exit(0);
}
```
## 3.完整代码
~~我才不发呢（滑稽~~

~~自己写去吧~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[3][3],i,j,t[3],sc[3];
void in()
{
	char c;
	for(i=0;i<=2;i++)
	for(j=0;j<=2;j++)
	{
		while((c=getchar())!='X'&&c!='0'&&c!='.');
		if(c=='X')a[i][j]=1;
		if(c=='0')a[i][j]=2;
		t[a[i][j]]++;
	}
} 
void pd_is_ill(){if(t[1]<t[2]||t[1]-t[2]>1)printf("illegal"),exit(0);}
void pd_is_win()
{
	if(a[0][0]==a[1][1]&&a[1][1]==a[2][2])sc[a[0][0]]++;
	if(a[0][2]==a[1][1]&&a[1][1]==a[2][0])sc[a[0][2]]++;
	for(i=0;i<=2;i++)if(a[i][0]==a[i][1]&&a[i][1]==a[i][2])sc[a[i][0]]++;
	for(i=0;i<=2;i++)if(a[0][i]==a[1][i]&&a[1][i]==a[2][i])sc[a[0][i]]++;
}
void pd_is_daw()
{
	if((sc[1]&&sc[2])||(sc[1]>0&&t[2]==t[1])||(sc[2]>0&&t[1]>t[2]))
	printf("illegal"),exit(0);
	if(sc[1]>sc[2])
	printf("the first player won"),exit(0);
	if(sc[1]<sc[2])
	printf("the second player won"),exit(0);
}
void pd_is_f_s()
{
	if(t[0]==0)return;
	if(t[1]>t[2]&&t[1]-t[2]==1)
	printf("second"),exit(0);
	if(t[1]==t[2])
	printf("first"),exit(0);
}
void pd()
{
	pd_is_ill();
	pd_is_win();
	pd_is_daw();
	pd_is_f_s();
	printf("draw");
	exit(0);
}
int main()
{
 	in();
 	pd();
	return 0;
}
```
完结撒花qwq

---

## 作者：One_JuRuo (赞：6)

AC 后逛了逛题解，发现好像自己的代码比大佬都短很多？

## 思路

数据范围很小，先暴力求得 ```X```，```0```，```.``` 的个数，然后暴力求得连着的三个 ```X```，```0``` 的个数。

然后，我们来分类讨论：

- 非法的情况一定优先判断，只有不非法才可能是其他情况，那么非法的可能有：

	1. $A$ 和 $B$ 都能赢。
    
   2. ```X``` 的个数既不是 ```0``` 的个数也不是 ```0``` 的个数 $+1$。
   3. 只有 $A$ 能赢且 ```X``` 的数量等于 ```0``` 的数量
   4. 只有 $B$ 能赢且 ```X``` 的数量等于 ```0``` 的数量。

- 解释：
	1. 不可能出现两者皆赢的可能。
   2. 棋局中 $A$ 最多比 $B$ 多下一子，至少与 $B$ 一样。
   3. $A$ 已经赢了，但是 $B$ 还在继续下棋。
   4. $B$ 已经赢了，但是 $A$ 还在继续下棋。

- 然后是谁赢的情况，这个不用细说

- 该谁下棋的情况，如果 $A$ 的棋子数等于 $B$ 的棋子数，那么该 $A$ 下，如果 $A$ 的棋子数等于 $B$ 的棋子数 $+1$ 并且有空位置，则该 $B$ 下。

- 剩下的就是平局情况了。

总结：情况较多，比较麻烦，但是数据范围很小。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[4];
int m[4][4],num[3],win[3];
int main()
{
	for(int i=1;i<=3;++i)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=3;++j) m[i][j]=(ch[j]=='X')?1:(ch[j]=='0')?2:0,++num[m[i][j]];//统计每个情况的个数 
	}
	/*统计两人能获胜的个数*/ 
	for(int i=1;i<=3;++i) if(m[i][1]==m[i][2]&&m[i][2]==m[i][3]) ++win[m[i][1]];//同行相同 
	for(int j=1;j<=3;++j) if(m[1][j]==m[2][j]&&m[2][j]==m[3][j]) ++win[m[1][j]];//同列相同 
	if(m[1][1]==m[2][2]&&m[2][2]==m[3][3]) ++win[m[1][1]];//斜角相同 
	if(m[3][1]==m[2][2]&&m[2][2]==m[1][3]) ++win[m[3][1]];//斜角相同
	/*非法情况*/
	if(win[1]&&win[2]) printf("illegal"),exit(0);
	if(num[1]!=num[2]&&num[1]!=num[2]+1) printf("illegal"),exit(0);
	if(win[2]&&num[1]==num[2]+1) printf("illegal"),exit(0);
	if(win[1]&&num[1]==num[2]) printf("illegal"),exit(0);
	/*某人赢的情况*/
	if(win[1]) printf("the first player won"),exit(0);
	if(win[2]) printf("the second player won"),exit(0);
	/*该某人下棋的情况*/
	if(num[1]==num[2]) printf("first"),exit(0);
	if(num[1]==num[2]+1&&num[0])printf("second"),exit(0);
	/*平局情况*/
	printf("draw");
	return 0;
}
```

---

## 作者：学霸壹号 (赞：6)

## 前言 
这是一篇C++题解，别的语言的oier请避开。

洛谷RemoteJudge 最近出了点问题，总是UKE，还是回[原OJ](http://codeforces.com/problemset/problem/3/C)评测吧。

[这道题](https://www.luogu.org/problem/CF3C)看起来很简单，就是判断几下，但其实坑特别多。接下来我们通过这篇题解，把坑一个一个用代码填上！~~顺便带一下，本蒟蒻提交了四次才AC，CF有175组数据，可怕！~~ 重要部分已经加粗。
## 代码及坑
1. 蒟蒻第一次把**题目中的$0$看成O了**，在这个题解中，你应该能看得清楚他们的区别。但愿你们不会犯这种蒟蒻的**低级错误**！
---
2. 你肯定会注意到，**first**、**second**这类单词太烦了，于是**宏定义**来帮忙！
```cpp
#define err "illegal"
#define nexta "first"
#define nextb "second"
#define awin "the first player won"
#define bwin "the second player won"
#define dr "draw"
```
---
3. 为了后面轻松，我们可以边读边把“X方”和“0方”**棋子的数量统计出来**。这样的话，后面例如判断**棋盘是不是已经满了**会快很多。
```
太简单了，代码不给！
```
---
4. 由于X方和0方是**轮流下棋**的，并且**X方先走**，所以X在棋盘中的数量要么和0**一样多**（上一步是0方下的），或者比0**多一**（马上0方下），如果不满足，则打印err（上面宏定义过）。
```cpp
if(tota<totb){
	cout<<err;
	return 0;
}
if(totb+1<tota){
	cout<<err;
	return 0;
}
```
~~蒟蒻手残见谅！代码写得有点绕~~

---
5. 判断**列**是否有三个**相同**的。
### 对于X方
```cpp
for(int i=0;i<3;++i)
	if(c[0][i]=='X'&&c[1][i]=='X'&&c[2][i]=='X'){
		as=true;	//s是“竖”，防止弄混
		break;
	}
```
### 对于0方
```cpp
for(int i=0;i<3;++i)
	if(c[0][i]=='0'&&c[1][i]=='0'&&c[2][i]=='0'){
		bs=true;	//s还是“竖”，防止弄混
		break;
	}
```
---
6. 判断**行**是否有三个**相同**的。
### 对于X方
```cpp
for(int i=0;i<3;++i)
	if(c[i][0]=='X'&&c[i][1]=='X'&&c[i][2]=='X'){
		ah=true;	//h是“行”，防止弄混
		break;
	}
```
### 对于0方
```cpp
for(int i=0;i<3;++i)
	if(c[i][0]=='0'&&c[i][1]=='0'&&c[i][2]=='0'){
		bh=true;	//h还是“行”，防止弄混
		break;
	}
```
7. 判断**对角线**是否有相同的，这里我就if语句，其中x代表“斜”
```cpp
if(c[0][0]=='X'&&c[1][1]=='X'&&c[2][2]=='X')
	ax1=true;
if(c[0][0]=='0'&&c[1][1]=='0'&&c[2][2]=='0')
	bx1=true;
if(c[0][2]=='X'&&c[1][1]=='X'&&c[2][0]=='X')
	ax2=true;
if(c[0][2]=='0'&&c[1][1]=='0'&&c[2][0]=='0')
	bx2=true;
//这里蒟蒻也不管那么多了，直接狠判断（很暴力，对不对？）
```
8. 弄了这么多，终于可以判断有没有赢的人啦！
```cpp
ga=as||ah||ax1||ax2;
gb=bs||bh||bx1||bx2;
//变量名没取好，ga是邻接二维矩阵（没学过图论的忽略）
```
9. 打印

首先建议读者先吸一口气，马上我们要开始总判断啦！

**首先**，如果**两个人都赢**了，肯定是err滴。

**其次**，如果X方赢了，但0方**还走了一步**（**怎么体现？0方的步数等于X放的步数，也就是刚刚0方走了一步**），肯定也是err滴。相反，0方赢了，但X方**还走了一步**（**X方的步数比0方的步数多**），那么同理，err。

代码：
```cpp
if(ga&&gb||ga&&tota==totb||gb&&tota>totb){
	cout<<err;
	return 0;
}
```
**说明是一个合法的格局（如果不合法，早结束了，看到上面的那行**return 0;**吗？）。我们可以看看是不是有人赢了**
```cpp
if(ga||gb){
	if(ga)
		cout<<awin;
	else
		cout<<bwin;
	return 0;
}
```
**到了现在，说明没人赢。棋盘是否满了？**
```cpp
if(tota+totb==9){
	cout<<dr;
	return 0;
}
```
**现在，说明没满。谁该走？打印一下就好啦！**
```cpp
if(tota==totb)
	cout<<nexta;
else
	cout<<nextb;
```
最后美美的**return 0;**

---
[完整代码（能不看就不看，自己完成它！）](https://www.luogu.org/paste/jgx4edp0)

---

## 作者：gary2005 (赞：4)

这题真的很坑

~~本蒟蒻提交了第六遍才AC~~

代码不难，就一些特殊判断，没必要想什么高级算法 只要if（）就搞定了！！！
**下面上代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    map<char,int> qipan;
    string chess[3];
    int sflag=0,fflag=0;
    for(int i=0;i<3;i++){
        cin>>chess[i];//first 玩家为X     second 玩家为0     空地为 . 
        qipan[chess[i][0]]++;
        qipan[chess[i][1]]++;
        qipan[chess[i][2]]++;
    } 
    if(qipan['X']<qipan['0']||qipan['0']<qipan['X']-1){
        cout<<"illegal";
        return 0;
    }
    if(chess[0][0]==chess[0][1]&&chess[0][1]==chess[0][2]&&chess[0][0]!='.'){
        if(chess[0][0]=='0') sflag=1;
        if(chess[0][0]=='X') fflag=1;
    }
    if(chess[1][0]==chess[1][1]&&chess[1][1]==chess[1][2]&&chess[1][0]!='.'){
        if(chess[1][0]=='0') sflag=1;
        if(chess[1][0]=='X') fflag=1;
    }
    if(chess[2][0]==chess[2][1]&&chess[2][1]==chess[2][2]&&chess[2][0]!='.'){
        if(chess[2][0]=='0') sflag=1;
        if(chess[2][0]=='X') fflag=1;
    }
    if(chess[0][0]==chess[1][0]&&chess[1][0]==chess[2][0]&&chess[0][0]!='.'){
        if(chess[0][0]=='0') sflag=1;
        if(chess[0][0]=='X') fflag=1;
    }
    if(chess[0][1]==chess[1][1]&&chess[1][1]==chess[2][1]&&chess[0][1]!='.'){
        if(chess[0][1]=='0') sflag=1;
        if(chess[0][1]=='X') fflag=1;
    }
    if(chess[0][2]==chess[1][2]&&chess[1][2]==chess[2][2]&&chess[0][2]!='.'){
        if(chess[0][2]=='0') sflag=1;
        if(chess[0][2]=='X') fflag=1;
    }
    if(chess[0][0]==chess[1][1]&&chess[1][1]==chess[2][2]&&chess[0][0]!='.'){
        if(chess[0][0]=='0') sflag=1;
        if(chess[0][0]=='X') fflag=1;
    }
    if(chess[0][2]==chess[1][1]&&chess[1][1]==chess[2][0]&&chess[0][2]!='.'){
        if(chess[0][2]=='0') sflag=1;
        if(chess[0][2]=='X') fflag=1;
    }
    if(sflag==1&&fflag==1||(sflag==1&&qipan['X']>qipan['0'])||(fflag==1&&qipan['X']==qipan['0'])) {
        cout<<"illegal";
        return 0;	
    }
    if(sflag==1) {
        cout<<"the second player won";
        return 0;
    }
    if(fflag==1) {
        cout<<"the first player won";
        return 0;
    }
    if(qipan['X']==qipan['0']&&qipan['.']!=0){
        cout<<"first";
        return 0;
    }
    if(qipan['X']>qipan['0']&&qipan['.']!=0){
        cout<<"second";
        return 0;
    }
    cout<<"draw";
    return 0;
}
```

---

## 作者：灵光一闪 (赞：3)

~~呃，开头不知说啥···~~

# **思路：暴力模拟。**

坑点：那是"0"!(数字) 不是"O"(字母)
~~我才不会告诉你们我WA了INF次~~

~~鸡冻人心的~~代码：
```
#include<iostream>
using namespace std;
int main()
{
    int a=0,b=0,c=0,q=0,w=0;//a:. b:0 c:X q:first w:second
    char s[3][3];
    for(int i=0;i<3;i++)
    {
        for(int o=0;o<3;o++)
        {
            cin>>s[i][o];
            if(s[i][o]=='.')
            {
                a++;
                continue;
            }
            else if(s[i][o]=='0')
            {
                b++;
                continue;
            }
            else
            {
                c++;
            }
        }
    }
    //a. b0 cX q:first w:second
    //--------------------------------------------------------------------非法区域
    if(c-b>=2||b>c)
    {
        cout<<"illegal";
        return 0;
    }
    if(c==b)
    {
    	for(int i=0;i<3;i++)
    	{
        	if(s[i][0]=='X'&&s[i][1]=='X'&&s[i][2]=='X')
        	{
        	    cout<<"illegal";
        		return 0;
        	}
    	}
    	for(int i=0;i<3;i++)
    	{
        	if(s[0][i]=='X'&&s[1][i]=='X'&&s[2][i]=='X')
        	{
        	    cout<<"illegal";
        		return 0;
        	}
    	}
		if(s[0][0]=='X'&&s[1][1]=='X'&&s[2][2]=='X')
    	{
    	    cout<<"illegal";
    	    return 0;
    	}
		if(s[2][0]=='X'&&s[1][1]=='X'&&s[0][2]=='X')
    	{
   	 	    cout<<"illegal";
   	 	    return 0;
    	}
	}
    if(c-b==1)
    {
    	for(int i=0;i<3;i++)
    	{
        	if(s[i][0]=='0'&&s[i][1]=='0'&&s[i][2]=='0')
        	{
        	    cout<<"illegal";
        		return 0;
        	}
    	}
    	for(int i=0;i<3;i++)
    	{
        	if(s[0][i]=='0'&&s[1][i]=='0'&&s[2][i]=='0')
        	{
        	    cout<<"illegal";
        		return 0;
        	}
    	}
    	if(s[0][0]=='0'&&s[1][1]=='0'&&s[2][2]=='0')
    	{
   	    	cout<<"illegal";
        	return 0;
    	}
    	if(s[2][0]=='0'&&s[1][1]=='0'&&s[0][2]=='0')
    	{
     	    cout<<"illegal";
        	return 0;
    	}
	}
    for(int i=0;i<3;i++)
    {
        if(s[i][0]=='X'&&s[i][1]=='X'&&s[i][2]=='X')
        {
            q=1;
        }
        if(s[i][0]=='0'&&s[i][1]=='0'&&s[i][2]=='0')
        {
            w=1;
        }
        if(q==1&&w==1)
        {
        	cout<<"illegal";
        	return 0;
		}
    }
    if(s[0][0]=='X'&&s[1][1]=='X'&&s[2][2]=='X')
    {
        q=1;
    }
    if(s[0][0]=='0'&&s[1][1]=='0'&&s[2][2]=='0')
    {
        w=1;
    }
    if(s[2][0]=='X'&&s[1][1]=='X'&&s[0][2]=='X')
    {
        q=1;
    }
    if(s[2][0]=='0'&&s[1][1]=='0'&&s[0][2]=='0')
    {
        w=1;
    }
    if(w==1&&q==1)
    {
    	cout<<"illegal";
    	return 0;
	}
	//----------------------------------------------------------------------------某一方胜
    for(int i=0;i<3;i++)
    {
        if(s[i][0]=='X'&&s[i][1]=='X'&&s[i][2]=='X')
        {
            cout<<"the first player won";
            return 0;
        }
        if(s[i][0]=='0'&&s[i][1]=='0'&&s[i][2]=='0')
        {
            cout<<"the second player won";
            return 0;
        }
    }
    for(int i=0;i<3;i++)
    {
        if(s[0][i]=='X'&&s[1][i]=='X'&&s[2][i]=='X')
        {
            cout<<"the first player won";
            return 0;
        }
        if(s[0][i]=='0'&&s[1][i]=='0'&&s[2][i]=='0')
        {
            cout<<"the second player won";
            return 0;
        }
    }
    if(s[0][0]=='X'&&s[1][1]=='X'&&s[2][2]=='X')
    {
        cout<<"the first player won";
        return 0;
    }
    if(s[0][0]=='0'&&s[1][1]=='0'&&s[2][2]=='0')
    {
        cout<<"the second player won";
        return 0;
    }
    if(s[2][0]=='X'&&s[1][1]=='X'&&s[0][2]=='X')
    {
        cout<<"the first player won";
        return 0;
    }
    if(s[2][0]=='0'&&s[1][1]=='0'&&s[0][2]=='0')
    {
        cout<<"the second player won";
        return 0;
    }
    //----------------------------------------------------------------------谁走区域
    if(a!=0)
    {
    	if(b==c)
    	{
    	    cout<<"first";
    	    return 0;
    	}
    	else if(c-b==1)
    	{
    	    cout<<"second";
    	    return 0;
    	}
    }
    //--------------------------------------------------------------绘图区域
    if(a==0) cout<<"draw";
    return 0;
}
```

好的，基本就是这样了，我相信你们能看懂，如果看不懂私信我，蟹蟹！

---

## 作者：Ousmane_Dembele (赞：2)

这是一道纯暴力的题，如果觉得太简单的话点[这里](https://www.luogu.org/problemnew/show/P1039)
或者[这里](https://www.luogu.org/problemnew/show/P1326)

[题目](https://www.luogu.org/problemnew/show/CF3C)

思路不难想：

先判断有没有违规，违规就是一个人出的子数比另一个人多两个及以上或者一个人赢了然后该他出子（其实还有一种，一个人有两条不相干的边都通了也是不合法的，但是因为是3,3的，两条通要6个肯定不合法，如果是n,n还要特判一下）

不违规，就看有没有人赢

有人赢就OK，没人赢就看有没有下完九手，下完了就平局，没下完就输出该谁了。

代码：
```
#include<bits/stdc++.h>
using namespace std;
char a[4][4];
int winner,go;//winner代表谁赢了，go代表going函数输出的东西
int win(){//我比较喜欢一次性把所有东西全算完
    int ans=222;//初始化
    for(int i=1;i<=3;i++){
        bool flag=false;
        for(int j=2;j<=3;j++)
           if(a[i][j]=='.'||a[i][j]!=a[i][1])flag=true;
        if(flag==false)
           if(a[i][1]=='0'&&ans==222)ans=2;
           else if(ans==222)ans= 1;
           else return 333;//很好理解吧
        for(int j=2;j<=3;j++)
           if(a[j][i]=='.'||a[j][i]!=a[1][i])flag=true;
        if(flag==false)
           if(a[i][1]=='0'&&ans==222)ans=2;
           else if(ans==222)ans=1;
           else return 333;
        return 0;
    }
    if(a[1][1]=='0'&&a[2][2]=='0'&&a[3][3]=='0'||a[1][3]=='0'&&a[2][2]=='0'&&a[3][1]=='0')//硬来了
       return 2;
    if(a[1][1]=='X'&&a[2][2]=='X'&&a[3][3]=='X'||a[1][3]=='X'&&a[2][2]=='X'&&a[3][1]=='X')
       return 1;   
    return 0;
}
int going(){//我比较喜欢一次性把所有东西全算完
    int t=0,s=0;
    for(int i=1;i<=3;i++)
       for(int j=1;j<=3;j++){
           if(a[i][j]=='X')t++;//计算X和0的个数
           if(a[i][j]=='0')s++;
       }
    if(t>s+1||s>t+1)return 10;//一人多走了两次以上
    if(winner==1&&t==s-1)return 10;//一人已赢然后又该这人走
    if(winner==2&&s==t-1)return 10;
    if(winner==1)return 1;
    if(winner==2)return 2;
    if(s+t==9&&winner==0)return 5;//平局
    if(t==s)return 3;//该第一个人走
    else return 4;//该第二个人走
}
int main(){
    for(int i=1;i<=3;i++)
       scanf("%s",a[i]+1);
    winner=win();
    if(winner==333){cout<<"illegal";return 0;}
    go=going();
    if(go==10){cout<<"illegal";return 0;}
    if(go==5){cout<<"draw";return 0;}
    if(go==1){cout<<"the first player won";return 0;}
    if(go==2){cout<<"the second player";return 0;}
    if(go==3){cout<<"first";return 0;}
    if(go==4){cout<<"second";return 0;}
    return 0;
}
```

---

## 作者：Loner_Knowledge (赞：2)

这是一道模拟题

---

纯模拟，然而坑点相当不少。


```cpp
#include<cstdio>
int fcnt,scnt;
char str[3][4];
bool Check1(char c) {            //这是检查赢家的函数
    for(int i=0;i<3;++i) {
        if(str[0][i]==c&&str[1][i]==c&&str[2][i]==c)    //检查纵向是否有三子
            return 1;
        if(str[i][0]==c&&str[i][1]==c&&str[i][2]==c)    //检查横向是否有三子
            return 1;
    }
    if(str[1][1]!=c)    //检查斜方向时如果中心不为该棋手的子，肯定赢不了
                        //此处是一个特判，如果将该处放到后面也一样
        return 0;
    if(str[0][0]==c&&str[2][2]==c)    //检查左上与右下
        return 1;
    if(str[0][2]==c&&str[2][0]==c)    //检查右上与左下
        return 1;
    return 0;        //如果没有结果，那么该棋手未赢
}
bool Check2() {                //这是检查棋盘合法性的函数
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j) {
            if(str[i][j]=='X')
                ++fcnt;
            else if(str[i][j]=='0')        //统计棋子数
                ++scnt;
        }
    if(fcnt!=scnt+1&&fcnt!=scnt)    //第一种是该下0时的情况，第二种是该下X时的情况，如果两个都不符合，不合法
        return 0;
    if(Check1('X')&&fcnt==scnt)        //检查如果X赢了然而不是轮到0下，说明在X赢后0又下了一步，不合法
        return 0;
    if(Check1('0')&&fcnt==scnt+1)    //同上，只不过X与0的位置调换
        return 0;
    return 1;        //如果还没检查出错误，那么合法
}
int main() {
    for(int i=0;i<3;++i)
        scanf("%s",str[i]);
    if(!Check2())            //检查棋盘合法性
        printf("illegal");
    else if(Check1('X'))    //检查先手棋手的胜负
        printf("the first player won");
    else if(Check1('0'))    //检查后手棋手的胜负
        printf("the second player won");
    else if(fcnt+scnt==9)    //如果棋子数和为9说明棋盘已满
        printf("draw");
    else if(fcnt==scnt)        //检查是否是轮到X下
        printf("first");
    else                    //如果以上都不符合，那么是轮到0下了
        printf("second");
    return 0;
}
```

---

---

## 作者：BBD186587 (赞：1)

## 大模拟 ##
此题坑点主要在判非法上，具体看代码~
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char a[5][5];
int sum1,sum2;
bool check2()
{
	if(a[1][1]=='X'&&a[1][2]=='X'&&a[1][3]=='X') return true;
	if(a[2][1]=='X'&&a[2][2]=='X'&&a[2][3]=='X') return true;
	if(a[3][1]=='X'&&a[3][2]=='X'&&a[3][3]=='X') return true;
	if(a[1][1]=='X'&&a[2][1]=='X'&&a[3][1]=='X') return true;
	if(a[1][2]=='X'&&a[2][2]=='X'&&a[3][2]=='X') return true;
	if(a[1][3]=='X'&&a[2][3]=='X'&&a[3][3]=='X') return true;
	if(a[1][1]=='X'&&a[2][2]=='X'&&a[3][3]=='X') return true;
	if(a[1][3]=='X'&&a[2][2]=='X'&&a[3][1]=='X') return true;
	return false;
}//'X'获胜
bool check3()
{
	if(a[1][1]=='0'&&a[1][2]=='0'&&a[1][3]=='0') return true;
	if(a[2][1]=='0'&&a[2][2]=='0'&&a[2][3]=='0') return true;
	if(a[3][1]=='0'&&a[3][2]=='0'&&a[3][3]=='0') return true;
	if(a[1][1]=='0'&&a[2][1]=='0'&&a[3][1]=='0') return true;
	if(a[1][2]=='0'&&a[2][2]=='0'&&a[3][2]=='0') return true;
	if(a[1][3]=='0'&&a[2][3]=='0'&&a[3][3]=='0') return true;
	if(a[1][1]=='0'&&a[2][2]=='0'&&a[3][3]=='0') return true;
	if(a[1][3]=='0'&&a[2][2]=='0'&&a[3][1]=='0') return true;
	return false;
}//'0'获胜
bool check1()
{
	if(sum1-sum2>1) return true;//棋子数非法
	if(sum2>sum1) return true;//棋子数非法
	if(check2()&&check3()) return true;//当前局面非法
	if(check3()&&sum1>sum2) return true;//当前局面非法
	if(check2()&&sum1==sum2) return true;//当前局面非法
	return false;
}//非法
int main()
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='X') sum1++;//sum1记录'X'个数
			else if(a[i][j]=='0') sum2++;//sum2记录'0'个数
		}
	if(check1()) return printf("illegal"),0;
	if(check2()) return printf("the first player won"),0;
	if(check3()) return printf("the second player won"),0;
	if(sum1+sum2==9) return printf("draw"),0;//判断平局
	if(sum1==sum2) return printf("first"),0;//判断此时是谁下棋
	return printf("second"),0;//判断此时是谁下棋
}
```
完结撒花~

---

## 作者：Lily_White (赞：1)

预处理。

这题如果直接在线判是不是合法会十分繁琐，一个好方法就是**先预处理出所有的合法的情况，然后直接看输入是不是这些中的一种**即可。

这里使用了$\texttt{dfs}$。利用$dep$的奇偶性判断是哪个人落子。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
bool win(const string& s, const char c) {
	rep(i, 3) if (s[i] == c and s[i + 3] == c and s[i + 6] == c) return true;
	rep(i, 3) if (s[i * 3] == c and s[i * 3 + 1] == c and s[i * 3 + 2] == c) return true;
	if (s[0] == c and s[4] == c and s[8] == c) return true;
	if (s[2] == c and s[4] == c and s[6] == c) return true;
	return false;
}
map <string, string> mem;
string s = ".........";
const string p = "X0", v[] = {"first", "second"};
void prework(int dep) {
	if (win(s, 'X')) {
		mem[s] = "the first player won";
		return;
	}
	else if (win(s, '0')) {
		mem[s] = "the second player won";
		return;
	}
	else if (dep == 9) {
		mem[s] = "draw";
		return;
	} 
	mem[s] = v[dep % 2];
	rep(i, 9) {
		if (s[i] != '.') continue;
		s[i] = p[dep % 2];
		prework(dep + 1);
		s[i] = '.';
	}
}
int main() {
	prework(0);
	string in;
	rep(i, 3) {
		string t;
		cin >> t;
		in += t;	
	}
	if (!mem.count(in)) cout << "illegal" << endl; else cout << mem[in] << endl; 
	return 0;
}
```

---

## 作者：Asexual (赞：0)

~~这道题目太水~~，做好标记就好了，详情看代码
```cpp
#include<bits/stdc++.h>]
using namespace std;
int a[5][5];
char ch;
int c1,c2;
int b[10];
int win()
{
	int f1=0,f2=0;
	for(int i=1;i<=3;i++)
	b[i]=a[1][i]+a[2][i]+a[3][i];//横行的和 
	for(int i=4;i<=6;i++)
	b[i]=a[i-3][1]+a[i-3][2]+a[i-3][3];//竖列的和 
	b[7]=a[1][1]+a[2][2]+a[3][3];//对角线上的和 
	b[8]=a[3][1]+a[2][2]+a[1][3];
	for(int i=1;i<=8;i++)
	{
		if(b[i]==3000)
		{
			f1=1;
		}
		if(b[i]==300)
		{
			f2=1;
		}
	
	}		
	if(f2&&c1==c2+1)//虽然B已经赢了，但是A一定有一颗棋是在B赢后下的 
	{
		cout<<"illegal";
		exit(0);
	}
	if(f1&&c1==c2)//虽然A已经赢了，但是B一定有一个棋子是在B赢之后下的 
	{
		cout<<"illegal";
		exit(0);
	}
	if(f1&&f2)//A与B都赢，不可能在同一时刻 
	{
		cout<<"illegal";
		exit(0);
	}
	if(f1&&!f2)//只有A赢了 
	{
		cout<<"the first player won";
		exit(0);
	}
	if(!f1&&f2)//只有B赢了 
	{
		cout<<"the second player won";
		exit(0);
	}

}
int main()
{
	//freopen("1.in","r",stdin);
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			cin>>ch;
			if(ch=='X')
			{
				a[i][j]=1000;//对A的棋子进行标记 
				c1++;//计算A的棋子数 
			}
			if(ch=='0')
			{
				a[i][j]=100;//对B的棋子进行标记
				c2++;//计算B的棋子数 
			}
			if(ch=='.')
			{
				a[i][j]=10;//标记点 
			}
		}
	}
	for(int i=1;i<=3;i++)
	{//是否有非法字符 
		for(int j=1;j<=3;j++)
		{
			if(a[i][j]!=1000&&a[i][j]!=100&&a[i][j]!=10)
			{
				cout<<"illegal";
				return 0;
			}
		}
	}
	if(abs(c1-c2)>1||(c1==0&&c2==0)||c2>c1)
	{//A与B的棋子数相差过大 //没有下过  //B的棋子比A多 
		cout<<"illegal";
		return 0;
	}
	
	
	win();//判断输赢 
	if(c1+c2>=9)//已填满棋盘，平局 
	{
		cout<<"draw";
		return 0;
	}
	else if(c1-c2==1)//轮到B下 
	{
		cout<<"second";
		return 0;
	}
	else if (c1==c2)//轮到A下 
	{
		cout<<"first";
		return 0;
	}
	cout<<"illegal";
}
```


---

## 作者：sandwich (赞：0)

我最爱暴力了~~但是暴力不爱我~~

这题做了很久

原因是不太清楚究竟怎么判断A赢或B赢

### 那就来讲讲几种~~比较坑的~~情况吧
- 1、当X的数量=0的数量时，由于X是先走的，所以下一步应该是0，是second
- 2、当X的数量=0的数量时，若X可以连起来，这种情况就不存在了（~~具体自己想~~）
- 3、当3×3的表格填满时，若0的数量>X的数量，也不存在（X先走）

接下来就是代码了，~~哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈~~

```cpp
#include<bits/stdc++.h>
using namespace std;
char x[3][3];
int main()
{
    int ans1=0,ans2=0;
    for(int i=1;i<=3;i++)
      for(int j=1;j<=3;j++)
	  {
	  	cin>>x[i][j];
	  	if(x[i][j]=='X') ans1++;
	  	if(x[i][j]=='0') ans2++;
	  }
	//cout<<ans1<<" "<<ans2;
    if(abs(ans2-ans1)>=2||ans2>ans1) {cout<<"illegal";return 0;}
		int ans3=0,ans4=0;
		if((x[1][1]==x[2][2]&&x[1][1]==x[3][3]&&x[1][1]=='0')||
		   (x[1][3]==x[2][2]&&x[1][3]==x[3][1]&&x[1][3]=='0')||
		   //对角 
		   (x[1][1]==x[1][2]&&x[1][1]==x[1][3]&&x[1][1]=='0')||
		   (x[2][1]==x[2][2]&&x[2][1]==x[2][3]&&x[2][1]=='0')||
		   (x[3][1]==x[3][2]&&x[3][1]==x[3][3]&&x[3][1]=='0')||
		   //行 
		   (x[1][1]==x[2][1]&&x[1][1]==x[3][1]&&x[1][1]=='0')||
		   (x[1][2]==x[2][2]&&x[1][2]==x[3][2]&&x[1][2]=='0')||
		   (x[1][3]==x[2][3]&&x[1][3]==x[3][3]&&x[1][3]=='0')
		   //列 
		   )
		ans4=1;
		if((x[1][1]==x[2][2]&&x[1][1]==x[3][3]&&x[1][1]=='X')||
		   (x[1][3]==x[2][2]&&x[1][3]==x[3][1]&&x[1][3]=='X')||
		   //对角 
		   (x[1][1]==x[1][2]&&x[1][1]==x[1][3]&&x[1][1]=='X')||
		   (x[2][1]==x[2][2]&&x[2][1]==x[2][3]&&x[2][1]=='X')||
		   (x[3][1]==x[3][2]&&x[3][1]==x[3][3]&&x[3][1]=='X')||
		   //行 
		   (x[1][1]==x[2][1]&&x[1][1]==x[3][1]&&x[1][1]=='X')||
		   (x[1][2]==x[2][2]&&x[1][2]==x[3][2]&&x[1][2]=='X')||
		   (x[1][3]==x[2][3]&&x[1][3]==x[3][3]&&x[1][3]=='X')
		   //列 
		  )
		ans3=1;
		//cout<<ans3<<" "<<ans4<<endl;
		if(ans4==1&&ans1>ans2) {cout<<"illegal";return 0;}
		if(ans3==1&&ans2==ans1) {cout<<"illegal";return 0;}
		if(ans3==1&&ans4==0) {cout<<"the first player won";return 0;}
		if(ans3==0&&ans4==1) {cout<<"the second player won";return 0;}
        if(ans3==1&&ans4==1) {cout<<"draw";return 0;}

		if(ans1>ans2&&ans1+ans2!=9) {cout<<"second";return 0;}
		if(ans2==ans1&&ans1+ans2!=9) {cout<<"first";return 0;}
		
		if(ans3==0&&ans4==0) {cout<<"draw";return 0;}
    return 0;
}
/*
XXX
00X
000

XX0
0X0
0XX

XXX
000
...
*/
```


---

