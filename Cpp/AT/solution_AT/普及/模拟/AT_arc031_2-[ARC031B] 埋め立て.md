# [ARC031B] 埋め立て

## 题目描述

很久很久以前，某地曾有一个岛国。这个岛国由一些岛屿组成。现在，这个岛国决定填海造陆，但还没有决定填海造陆的位置。政府希望填海造陆工程能够将所有岛屿连接起来，成为一个岛屿。

给出 $10$ 格 $×10$ 格的该国地图，请判断：能否仅将一格海洋变成陆地，使该国所有岛屿连接成一个岛屿。另外，地图中表示陆地的格子上下左右互相连接的区域称为一个岛屿。

## 样例 #1

### 输入

```
xxxxxxxxxx
xoooooooxx
xxoooooxxx
xxxoooxxxx
xxxxoxxxxx
xxxxxxxxxx
xxxxoxxxxx
xxxoooxxxx
xxoooooxxx
xxxxxxxxxx```

### 输出

```
YES```

## 样例 #2

### 输入

```
xxxxxxxxxx
xoooooooxx
xxoooooxxx
xxxoooxxxx
xxxxxxxxxx
xxxxxxxxxx
xxxxxxxxxx
xxxoooxxxx
xxoooooxxx
xxxxxxxxxx```

### 输出

```
NO```

## 样例 #3

### 输入

```
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
ooooxooooo
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx```

### 输出

```
YES```

# 题解

## 作者：Donald_Ducka (赞：6)

### 这道题是被同机房的大佬推荐做的
### 当他们在想高深算法的时候，我看了看题——
### 10*10的图，默默地开启了爆搜之路，直接爆搜结果A了
### 爆搜他不香么！！！


------------
## 言归正传——思路：
### 这是一道联系联通块和搜索的综合题目，数据只有10*10，所以暴力出奇迹！因为题目要寻找一个点使整个陆地联通，所以我们只需要从随便一个联通块的周围找点，把他填成陆地，然后判断联通块个数是否为一，如果是的话就直接输出YES结束，如果不是的话就继续寻找另外一个点，并将上一次填的点附回来（否则当联通块数目不唯一时就会出错！！！！）。
### 如果到最后还没有找到这样一个点的话直接输出NO；
## ~~记得加换行！！~~
# 代码：
```cpp
#include<bits/stdc++.h> //万能头
using namespace std;
int a[110][110];
bool vis[110][110]; //vis,vos,vus数组均为状
//                    态判断数组下面会讲
bool vos[110][110];
bool vus[110][110];
int ans=0;
int lian=0;
int dir[4][2]={1,0,0,1,-1,0,0,-1};//方向数组，走图搜索必备！
//四联通不解释啦！
bool sum=false;//跳出n层循环的必要变量贯穿始终！
struct node{
	int x,y;
	node(int xx,int yy)
	{
		x=xx;
		y=yy;
	}
};//用于bfs+队列
void dfs(int x,int y)
{
	for(int i=0;i<4;i++)
	{
		int tx=x+dir[i][0],ty=y+dir[i][1];
		if(tx>=0&&tx<=10&&ty>=0&&ty<=10 && a[tx][ty]==1 && !vis[tx][ty])
		{
			vis[tx][ty]=true;
			dfs(tx,ty);
		}
	}
}//为联通打标记，模板不须过多解释，
//主要是为下面BFS打好搜索标记
void gfs(int x,int y)
{
	for(int i=0;i<4;i++)
	{
		int tx=x+dir[i][0],ty=y+dir[i][1];
		if(tx>=0&&tx<=10&&ty>=0&&ty<=10 && a[tx][ty]==1 && !vos[tx][ty])
		{
			vos[tx][ty]=true;
			gfs(tx,ty);
		}
	}
}//这里操作的是vos 数组是为了
//在不影响总标记的情况下判断全图联通块的个数。
//注意每次使用之前都要清空。
void bfs(int x,int y)// 核心！！
{
	queue<node> q;//定义队列
	q.push(node(x,y));//将当前的点入队。
	while(!q.empty())//队列非空就进行循环
	{
		if(sum==true) break;
        //这里要照应到下面关于sum的赋值。
 //既：如果填点后全图联通块的数目为一，
 //sum赋为真值，然后用if + break 跳出层层循环！
		node now=q.front();
		q.pop();//啰嗦一句——
   //一定要在获取队首元素之后将其弹出，
   //否则你将一直用队首元素并且死在循环中。
		for(int i=0;i<4;i++)
		{
			int tx=now.x+dir[i][0],ty=now.y+dir[i][1];
			if(tx>=0&&tx<=10&&ty>=0&&ty<=10 && !vus[tx][ty])
      //啊哈vus数组出现——
      //在不影响全图原有联通块的情况下来判断
      //入队的联通块周围的点是否重复，
      //也是结束循环的必要数组！
			{
				vus[tx][ty]=true;
      //不管他是否符合接下来搜索的条件，先把标记打上，
      //因为已经搜过，避免重复搜索！
				if(a[tx][ty]==0) //这个判断~~精髓的很~~
      //如果他不是联通块的话，
      //也就是说如果当前的点是被填为陆地的话，
      //就进行近下来的操作，
      //跑一遍图看看联通块个数是否为1。
				{
					a[tx][ty]=1;//把他变为陆地，
					for(int i=1;i<=10;i++) for(int j=1;j<=10;j++) vos[i][j]=false;//切记初始化为0；
					vos[tx][ty]=true;
					gfs(tx,ty);//为联通块打标记
					bool flag=false;
   //判断联通块个数 的变量，
   //如果为一flag返回真值，否则返回假值；
					for(int i=1;i<=10;i++)
					{
						for(int j=1;j<=10;j++)
						{
							if(a[i][j]==1&&vos[i][j]==0)
							flag=true;//寻找是否还有别的联通块
						}
					}
					if(!flag)//如果没有就可以开始输出结果并结束程序
					{
						cout<<"YES"<<endl;
						sum=true;//sum出现开始跳循环啦！！！
						break;//跳一层
					}
					else a[tx][ty]=0;//把填成陆地的格子再挖成海 （滑稽~~~~~~）
				}
				else {
					q.push(node(tx,ty));//接着方向循环内最顶层的if
				}
			}
		}
	}
}
int main()//主函数
{
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++)
		{
			char c;cin>>c;
			if(c=='o')
			a[i][j]=1;
			else a[i][j]=0;
		}
	}//读入地图稍微处理一下，如果是陆地就赋为1，以后会方便
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++)
		{
			if(a[i][j]==1&&!vis[i][j])
			{
				vis[i][j]=true;
				dfs(i,j);
			}
		}
	}//先把图中所有的联通块都打上标记，方便下一步BFS
	for(int i=1;i<=10;i++)
    {
    	for(int j=1;j<=10;j++)
    	{
    		if(a[i][j]==1)//任意找到一个联通块，
    		{
    			bfs(i,j);//进行bfs
    			break;//直接跳出循环——没必要继续，
       //如果这个联通块周围任意一点不与其他联通块相接，
       //那么其他联通块周围的任意一点不与此联通块相接。
    		}
    	}
    }
    if(sum==true) return 0;//这里也需要跳否则会输出YEs和NO!
    cout<<"NO"<<endl;//如果没有输出YEs(sum为false)则视为无解
}
```


------------
### 虽说代码有点长，但暴力成分较多一点，注释已经非常清楚啦 ！很好理解bia
### 这是本蒟蒻第一篇题解，管理员大大求过呀！
### ~~第一次写忘记换行所以在发一次请管理原谅！！~~
### 难度建议设置为~~黄题~~，算法标签为搜索，广搜联通块

---

