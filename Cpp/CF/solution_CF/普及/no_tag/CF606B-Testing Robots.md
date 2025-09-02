# Testing Robots

## 题目描述

The Cybernetics Failures (CF) organisation made a prototype of a bomb technician robot. To find the possible problems it was decided to carry out a series of tests. At the beginning of each test the robot prototype will be placed in cell $ (x_{0},y_{0}) $ of a rectangular squared field of size $ x×y $ , after that a mine will be installed into one of the squares of the field. It is supposed to conduct exactly $ x·y $ tests, each time a mine is installed into a square that has never been used before. The starting cell of the robot always remains the same.

After placing the objects on the field the robot will have to run a sequence of commands given by string $ s $ , consisting only of characters 'L', 'R', 'U', 'D'. These commands tell the robot to move one square to the left, to the right, up or down, or stay idle if moving in the given direction is impossible. As soon as the robot fulfills all the sequence of commands, it will blow up due to a bug in the code. But if at some moment of time the robot is at the same square with the mine, it will also blow up, but not due to a bug in the code.

Moving to the left decreases coordinate $ y $ , and moving to the right increases it. Similarly, moving up decreases the $ x $ coordinate, and moving down increases it.

The tests can go on for very long, so your task is to predict their results. For each $ k $ from $ 0 $ to $ length(s) $ your task is to find in how many tests the robot will run exactly $ k $ commands before it blows up.

## 说明/提示

In the first sample, if we exclude the probable impact of the mines, the robot's route will look like that: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF606B/e99fac597a94e8717379dd6864b302ee973d5867.png).

## 样例 #1

### 输入

```
3 4 2 2
UURDRDRL
```

### 输出

```
1 1 0 1 1 1 1 0 6
```

## 样例 #2

### 输入

```
2 2 2 2
ULD
```

### 输出

```
1 1 1 1
```

# 题解

## 作者：drah_yrev (赞：0)

## 题意：
一个机器人在 $n×m$ 的地图上走，初始时在 $(x,y)$ 点，有一个操作序列 $s$，

四个方向为 `UDLR` 分别表示向上下左右，

如果下一步操作机器人会走出边界，则此操作无效；

判断机器人每一步后，所在的点是否走过，没有被走过则为 $1$，走过则为 $0$，最后输出地图上有多少点没有被机器人走过。

## 思路
模拟机器人的操作，用 $VIS$ 数组判断机器人是否走过，并记录当前机器人所在位置。

每走一步。输出是否走过。

最后判断 $VIS$ 数组中没有走过的数量。

## 代码
```cpp
#include<iostream>
using namespace std;
int n,m,nx,ny,cnt,vis[505][505];
string a;
int main() {
	cin>>n>>m>>nx>>ny>>a;
	cout<<"1 ";//提前输出一下。
	cnt++;//提前增加
	vis[nx][ny]=1;//提前判断。
	for(int i=0; a[i]; i++) {
		if(a[i]=='U'&&nx>1)nx--;
		if(a[i]=='D'&&nx<n)nx++;
		if(a[i]=='L'&&ny>1)ny--;
		if(a[i]=='R'&&ny<m)ny++;//分别判断四个方向是否出现以及改动现在位置。
		if(vis[nx][ny])cout<<"0 ";//如果走过输出0。
		else { //没走过输出一，并且标记为走过。且计数器加1
			cout<<"1 ";
			cnt++;
			vis[nx][ny]=1;
		}
	}
	cout<<n*m-cnt;//求出没有走过的
	return 0;
}

```



---

## 作者：幻想繁星 (赞：0)

## 题意：

一个机器人在 $n×m$ 的地图上走，初始时在 $(x,y)$ 点，有一个操作序列 $s$ ，`U D L R`分别表示向上下左右走，如果下一步操作机器人会走出边界，则此操作无效；判断机器人每一步操作后，所在的点是否走过，没有被走过则输出 $1$ ，走过则输出 $0$ ，最后输出地图上有多少点没有被机器人走过。
## 思路
模拟机器人的操作，使用二维数组标记所有的点是否被走过，每次操作后判断所在点对应数组是否为 $1$ 并输出，同时记录所走的点的个数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,ans,v[502][502];
string s;
int main()
{
	cin>>n>>m>>x>>y>>s;
	cout<<"1 ";
	ans++;
	v[x][y]=1;
	for(int i=0;i<s.size()-1;i++)
	{
		if(s[i]=='U'&&x>1)
			x--;
		if(s[i]=='D'&&x<n)
			x++;
		if(s[i]=='L'&&y>1)
			y--;
		if(s[i]=='R'&&y<m)
			y++;
		if(v[x][y])
			cout<<"0 ";
		else
		{
			cout<<"1 ";
			ans++;
			v[x][y]=1;
		}
	}
	cout<<n*m-ans;
	return 0;
}

```


---

## 作者：yangzd (赞：0)

# 题目大意：

一个机器人在 $n \times m$ 的地图上走，初始时在 $(x,y)$ 点，有一个操作序列 $s$ ，```U D L R```分别表示向上下左右走，如果已经在边界且下一步要走出边界机器人会停在边界而不会走出边界，从机器人的初始位置开始，如果他当前位置没有被走过则输出 $1$ ，走过则输出 $0$ ，最后输出地图上有多少点没有被机器人走过（不考虑最后一步）

# 分析：

模拟，统计访问过的位置数```cnt```。

对于中间移动的位置若已经访问过，则输出 $0$ ，反之输出 $1$ 。

对于末尾，若该位置已经访问过，输出 $n \times m-cnt$ ，反之输出 $n \times m-cnt+1$ 。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,m,x,y,visited[605][605];
char s[10005];

signed main()
{
	ios::sync_with_stdio(0);
	
    cin >> n >> m >> x >> y >> s;
    
    memset(visited,0,sizeof(visited));
    
    long long cnt=1;
    
    visited[x][y]=1;
    
    cout << "1 ";
    
    for(long long i=0; i<strlen(s)-1; i++)
    {
        if(s[i]=='U' && x-1>=1)
			x--;
			
        else if(s[i]=='D' && x+1<=n)
			x++;
			
        else if(s[i]=='L' && y-1>=1)
			y--;
			
        else if(s[i]=='R' && y+1<=m)
			y++;
			
        if(!visited[x][y])
		{
			cout << "1 ";
			
			cnt++;
		} 
		
        else
        	cout << "0 ";
        	
        visited[x][y]=1;
    }
    
    cout << n*m-cnt << endl;
    
    return 0;
}
```

---

## 作者：ztxtjz (赞：0)

## 【题意】
机器人按操作行动，若当前位置没有走过输出1，已走过输出0，最后一个数输出一共有多少个位置没有去过。

U：横坐标减一；

D：横坐标加一；

L：纵坐标减一；

R：纵坐标加一。

## 【思路】
由于不能超出边界，只要特判一下就可以。

每一次**行动前**判断当前位置是否走过，如果没有走过则ans加一。

详情见代码
## 【代码】
```cpp
#include <cstdio>
int n,m,x,y,ans;
bool vis[505][505];
char c;
int main()
{
	scanf("%d%d%d%d",&n,&m,&x,&y);getchar();  //消去第一行输入的'\n'
	while((c=getchar())!='\n')
	{
		if(!vis[x][y])  //没有走过输出1 
		{
			printf("1 ");
			ans++;  //ans记录走过的位置数 
			vis[x][y]=1;  //标记为已走过 
		}
		else  //走过输出0 
			printf("0 ");
		//运动特判超界 
		if(c=='U') x=x-1>=1?x-1:1;
		else if(c=='D') x=x+1<=n?x+1:n;
		else if(c=='L') y=y-1>=1?y-1:1;
		else y=y+1<=m?y+1:m;
	}
	printf("%d",n*m-ans);  //n*m为总位置数，ans为走过的位置数，输出未走过的位置数 
	return 0;  //完结 
}
```


---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

### 思路

机器人需要按操作行动，若当前位置未走过，则输出 ```0```，否则输出 ```1```。

可以用一个 ```vis``` 数组存放已经走过的位置。

### 代码

```cpp
include<iostream>
using namespace std;
const int N=505;
int n,m,dx,dy,cnt,vis[N][N];
string s;
int main(){
	cin>>n>>m>>dx>>dy>>s;
	cnt++;
	vis[dx][dy]=1;
    cout<<"1 ";
	for(int i=0;i<s.size()-1;i++){
        //判断方向
		if(s[i]=='U'&&dx>1) dx--;
		if(s[i]=='D'&&dx<n) dx++;
		if(s[i]=='L'&&dy>1) dy--;
		if(s[i]=='R'&&dy<m) dy++;
		if(vis[dx][dy]){
        	cout<<"0 ";	//已走过输出0
        }else{
            cnt++;
            vis[dx][dy]=1;
			cout<<"1 "; //未走过输出1
		}
	}
	cout<<n*m-cnt<<endl;
	return 0;
}
```

---

