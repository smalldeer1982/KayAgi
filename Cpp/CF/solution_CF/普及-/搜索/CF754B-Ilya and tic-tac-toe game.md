# Ilya and tic-tac-toe game

## 题目描述

题目大意：

伊莉雅是一个4x4井字棋的年迈棋手，他总是用x（英文小写）棋，今天，他跟他的朋友亚瑟玩了很多很多局游戏，亚瑟很累了，但是现在还剩下最后一场游戏，现在轮到伊莉雅下棋，请问伊莉雅下完这颗棋子后能否取得胜利？
井字棋规则：

 棋盘的规格为4*4，其中伊莉雅棋子为x，亚瑟的棋子为o（英文小写o），x先下，o后下，当某种棋子在棋盘上连成三个时取得胜利！（这三个棋子可以是水平、竖直或斜方向的连续三个）

## 样例 #1

### 输入

```
xx..
.oo.
x...
oox.
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
x.ox
ox..
x.o.
oo.x
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
x..x
..oo
o...
x.xo
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
o.x.
o...
.x..
ooxx
```

### 输出

```
NO
```

# 题解

## 作者：B_lhx (赞：1)

[CF754B Ilya and tic-tac-toe game](https://www.luogu.com.cn/problem/CF754B)
===
思路：遍历棋盘，如果某格为'.'，则把这个格设为'x'，然后判断现在的棋盘有没有三连，在把格子变回'.'

![](https://cdn.luogu.com.cn/upload/image_hosting/i5jywnla.png)

```
#include<bits/stdc++.h>
using namespace std;
char a[10][10];//棋盘
bool in(int o,int p){//判断
	return o>=0&&o<4&&p>=0&&p<4;//返回的值为此坐标合不合法
}
void dfs(){
	for(int i = 0;i<4;i++){//遍历棋盘
		for(int j = 0;j<4;j++){
			if(a[i][j]=='x'){//如果是x
				if(in(i+2,j)&&a[i+1][j]=='x'&&a[i+2][j]=='x'){//八个方向判断有没有三连
					cout<<"YES";//如果有，输出
					exit(0); //结束整个程序
				}
				if(in(i-2,j)&&a[i-1][j]=='x'&&a[i-2][j]=='x'){//同上
					cout<<"YES";
					exit(0); 
				}
				if(in(i,j+2)&&a[i][j+1]=='x'&&a[i][j+2]=='x'){
					cout<<"YES";
					exit(0); 
				}
				if(in(i,j-2)&&a[i][j-1]=='x'&&a[i][j-2]=='x'){
					cout<<"YES";
					exit(0); 
				}
				if(in(i-2,j-2)&&a[i-1][j-1]=='x'&&a[i-2][j-2]=='x'){
					cout<<"YES";
					exit(0); 
				}
				if(in(i+2,j+2)&&a[i+1][j+1]=='x'&&a[i+2][j+2]=='x'){
					cout<<"YES";
					exit(0); 
				}
				if(in(i+2,j-2)&&a[i+1][j-1]=='x'&&a[i+2][j-2]=='x'){
					cout<<"YES";
					exit(0); 
				}
				if(in(i-2,j+2)&&a[i-1][j+1]=='x'&&a[i-2][j+2]=='x'){
					cout<<"YES";
					exit(0); 
				}
			}
		}
	}
}
int main(){
for(int i = 0;i<4;i++){//输入
	for(int j = 0;j<4;j++){
		cin>>a[i][j];
	} 
} 
for(int i = 0;i<4;i++){//遍历
	for(int j = 0;j<4;j++){
		if(a[i][j]=='.'){//如果能下
			a[i][j]='x';//下
			dfs();//判断能不能赢
			a[i][j]='.';//不能，则变回初始状态（回溯）
		}
	} 
} 
cout<<"NO";//如果程序还在运行，输出NO
	return 0;
}
```


---

## 作者：zengzhijie54188 (赞：1)

这道题其实很简单，只要读懂并理解题目，这道题就很好做了。
### 思路
这道题考察的是数组的运用还有模拟，主要做法就是把所有的棋盘的位置一个一个地搜查，首先先判断这个棋盘的位置是否是空格，如果是，则进入下一重判断。然后，观察一下如果在这个空格是下一颗棋的话，是否符合下图中$12$种情况中的其中一种，如果符合则输出 $YES$ 并结束程序，否则就进入下一从循环。模拟以上做法，打起代码就容易多了。

![](https://cdn.luogu.com.cn/upload/image_hosting/9bys3xnp.png)


上AC代码 （c++）
```cpp
#include<bits/stdc++.h>
using namespace std ;
char a[10][10] ;
int main()
{
	for ( int i = 1 ; i <= 4 ; i++ ) //输入棋盘 
	{
		for ( int j = 1 ; j <= 4 ; j++ )
		{
			cin >> a[i][j] ;
		}
	}
	for ( int i = 1 ; i <= 4 ; i++ ) //开始查找 
	{
		for ( int j = 1 ; j <= 4 ; j++ )
		{
			if ( a[i][j] == '.' )
			{
				if ( i + 1 <= 4 && a[i+1][j] == 'x' && i - 1 >= 1 && a[i-1][j] == 'x' ) //对于12种可以赢的途径进行搜索 
				{
					cout << "YES" ;
					return 0 ; //干脆利落，发现可以赢之后直接结束程序 
				}
				if ( j + 1 <= 4 && a[i][j+1] == 'x' && j - 1 >= 1 && a[i][j-1] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( i + 1 <= 4 && j + 1 <= 4 && a[i+1][j+1] == 'x' && i - 1 >= 1 && j - 1 >= 1 && a[i-1][j-1] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( i + 1 <= 4 && j - 1 >= 1 && a[i+1][j-1] == 'x' && j + 1 <= 4 && i - 1 >= 1 && a[i-1][j+1] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( i - 1 >= 1 && a[i-1][j] == 'x' && a[i-2][j] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( j - 2 >= 1 && a[i][j-1] == 'x' && a[i][j-2] == 'x' )
				{
				cout << "YES" ;
					return 0 ;
				} 
				if ( i + 2 <= 4 && a[i+1][j] == 'x' && a[i+2][j] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( j + 2 <= 4 && a[i][j+1] == 'x' && a[i][j+2] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( i - 2 >= 1 && j - 2 >= 1 && a[i-1][j-1] == 'x' && a[i-2][j-2] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( i + 2 <= 4 && j + 2 <= 4 && a[i+1][j+1] == 'x' && a[i+2][j+2] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
				if ( i - 2 >= 1 && j + 2 <= 4 && a[i-1][j+1] == 'x' && a[i-2][j+2] == 'x' )
				{
				    cout << "YES" ;
					return 0 ;
				}
				if ( i + 2 <= 4 && j - 2 >= 1 && a[i+1][j-1] == 'x' && a[i+2][j-2] == 'x' )
				{
					cout << "YES" ;
					return 0 ;
				}
			}
		
		}
	}
		cout<<"NO" ; //若果程序还在运行，则表示没有可以赢的下法，所以输出 NO 
		return 0 ; //好习惯 
 } 
 ```
 希望能帮助到大家！

---

## 作者：天天快乐 (赞：1)

既然没有人发布题解，就自己发布一篇吧。
Ilya and tic-tac-toe其实是[CF3c tic-tac-toe的升级版]。(http://codeforces.com/problemset/problem/3/C)
这题可以模拟，依次假设每个点下一枚棋，再判断是否符合条件，具体见代码：

```
#include <bits/stdc++.h>
using namespace std;

char b[6][6];
int dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int dy[8] = {0, 0, -1, 1, -1, -1, 1, 1};

bool f (int x, int y)
{
    bool t=false;
    
    for (int k=0; k<8; k++)
        if ((b[x+dx[k]][y+dy[k]] == 'x' && b[x+dx[k]*2][y+dy[k]*2] == 'x')
            || (b[x+dx[k]][y+dy[k]] == 'x' && b[x-dx[k]][y-dy[k]] == 'x')
            || (b[x-dx[k]][y-dy[k]] == 'x' && b[x-dx[k]*2][y-dy[k]*2] == 'x'))
            t = true;
        
    return t;
}

int main()
{
    int i, j;
    for (i=1; i<=4; i++)
        for (j=1; j<=4; j++)
            cin >> b[i][j];
        
    for (i=0; i<=4; i++){
        for (j=0; j<=4; j++){
            if (b[i][j] == '.'){
                b[i][j] = 'x';
                if (f(i, j)){
                    puts ("YES");
                    return 0;
                }
                else{
                    b[i][j] = '.';
                }
            }
        }
    }
    
    puts ("NO");
    return 0;
}
```

---

## 作者：purple7 (赞：0)

一开始看到题目还以为是简单的dfs，结果仔细一看是更简单的模拟  /xyx ，但函数已经命名为dfs了，请见谅。 
#### 本题思路：   
在字符数组里找  `x` ,找到后开始判定，有以下两种判定方式      

- `x.x`
- `xx.`   

我定义了两对方向数组 $mx$，$my$和 $xx$，$yy$。$mx$和$my$代表后面的那个位置，$xx$和$yy$代表中间的位置。分别判定就好。   
下面是代码附带注释：  
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10][10];
int mx[]={0,0,2,0,-2,   2,2,-2,-2},my[]={0,2,0,-2,0,    -2,2,2,-2};
int xx[]={0,0,1,0,-1,   1,1,-1,-1},yy[]={0,1,0,-1,0,    -1,1,1,-1};//这里的两个数组就是方向数组，要注意有八个方向
bool flag=false;
void dfs(int x,int y)
{

	for(int i=1;i<=8;i++)
	{
		if(a[x+mx[i]][y+my[i]]=='x'&&a[x+xx[i]][y+yy[i]]!='o')//模拟情况1，如果后面那个位置是x，中间那个不是o，就可以赢
		{	
		
			flag=true;
			return;
		}
		if(a[x+mx[i]][y+my[i]]=='.'&&a[x+xx[i]][y+yy[i]]=='x')//模拟情况2，如果中间那个位置是x，后面那个是"."，就可以赢
		{	
		
			flag=true;
			return;
		}
	}
}
int main()
{
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
	cin>>a[i][j];
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
	{
		if(a[i][j]=='x')//如果这个位置字母是x，就开始搜索
		dfs(i,j);
		if(flag==true) //如果可以赢，输出“YES”，结束程序
		{
			cout<<"YES";	
			return 0;
		}
	}
	cout<<"NO";//否则输出“NO”
	return 0;
}

```
代码结束


---

## 作者：zyc____ (赞：0)

## CF754B Ilya and tic-tac-toe game

~~不看标题都不知道这题和[CF3C](https://www.luogu.org/problemnew/show/CF3C)有关系~~

### Tic-Tac-Toe 魔改版

事实上就是道模拟，几个if即可搞定

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[4][4];
int blag; 
int main()
{
    while(cin>>s[0])
    {
        cin>>s[1]>>s[2]>>s[3];
        blag=0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(s[i][j]=='.')
                {
                    if(i>0&&s[i-1][j]=='x'&&i<3&&s[i+1][j]=='x')
                      blag=1;
                    if(j>0&&s[i][j-1]=='x'&&j<3&&s[i][j+1]=='x')
                      blag=1;
                    if(j>0&&i>0&&s[i-1][j-1]=='x'&&j<3&&i<3&&s[i+1][j+1]=='x')
                      blag=1;
                    if(j>0&&i>0&&j<3&&i<3&&s[i-1][j+1]=='x'&&s[i+1][j-1]=='x')
                      blag=1;
                    if(i>1&&s[i-1][j]=='x'&&s[i-2][j]=='x')
                      blag=1;
                    if(j>1&&s[i][j-1]=='x'&&s[i][j-2]=='x')
                      blag=1;
                    if(i<2&&s[i+1][j]=='x'&&s[i+2][j]=='x')
                      blag=1;
                    if(j<2&&s[i][j+1]=='x'&&s[i][j+2]=='x')
                      blag=1;
                    if(i>1&&j>1&&s[i-1][j-1]=='x'&&s[i-2][j-2]=='x')
                      blag=1;
                    if(i<2&&j<2&&s[i+1][j+1]=='x'&&s[i+2][j+2]=='x')
                      blag=1;
                    if(i>1&&j<2&&s[i-1][j+1]=='x'&&s[i-2][j+2]=='x')
                      blag=1;
                    if(i<2&&j>1&&s[i+1][j-1]=='x'&&s[i+2][j-2]=='x')
                      blag=1;
                }
            }
        }
        if(blag)
          cout<<"YES"<<endl;
        else
          cout<<"NO"<<endl;
    }
    return 0;
}
```


---

