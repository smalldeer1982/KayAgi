# 拯救oibh总部

## 题目背景

oibh 总部突然被水淹没了！现在需要你的救援……


## 题目描述

oibh 被突来的洪水淹没了，还好 oibh 总部有在某些重要的地方起一些围墙。用 `*` 号表示，而一个四面被围墙围住的区域洪水是进不去的。

oibh 总部内部也有许多重要区域，每个重要区域在图中用一个 `0` 表示。

现在给出 oibh 的围墙建设图，问有多少个没被洪水淹到的重要区域。

## 说明/提示

对于 $100\%$ 的数据，$1 \le x,y \le 500$。

## 样例 #1

### 输入

```
4 5
00000
00*00
0*0*0
00*00```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 5
*****
*0*0*
**0**
*0*0*
*****```

### 输出

```
5```

# 题解

## 作者：Blue_wonders (赞：326)

## 最详细的dfs解释(附图附解析)
#### 遇到好多次这样的dfs思路了，所以就详解一下
### 思路
```
5 7
0 0 * * * 0 0
0 0 * 0 * 0 0
* * * 0 * * 0
* 0 * * * 0 0
* * * 0 * * 0
```
以这个样例详解一下做法
1. 首先输入
2. 然后搜索最外层，如果有空洪水就可以沿着空一直往里走，所以要dfs搜索一下(画叉号的是搜索有空的)
![](https://cdn.luogu.com.cn/upload/pic/53432.png)
3. 将所有外面能进来的格子填上数(深色的是后来填上的)
![](https://cdn.luogu.com.cn/upload/pic/53433.png)
4. 搜索所有白色格子就是最终答案
答案是 3
### AC代码
[AC详情](https://www.luogu.org/recordnew/show/17013744)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s=0;
int kx[5]={0,1,-1,0,0}; 
int ky[5]={0,0,0,1,-1};
int a[501][501];
void search(int x,int y){
    a[x][y]=1;//先标记被淹没了 
    for(int i=1;i<=4;i++){//向四个方向搜索 
        int x0=x+kx[i];
        int y0=y+ky[i];
        if(x0>0&&x0<=n&&y0>0&&y0<=m&&a[x0][y0]==0)search(x0,y0);
    }//如果新的数在整个数组范围内并且不是障碍(能走),那么就搜索从这个格子能走到其他哪些格子 
}
int main(){
    cin>>n>>m;
    char e;
    for(int i=1;i<=n;i++){//输入 
        for(int j=1;j<=m;j++){
            cin>>e;
            if(e=='*')a[i][j]=1;//如果是障碍就输入1 
            else a[i][j]=0;//可以过就是0 
        }
    }
    for(int i=1;i<=n;i++){//搜索第一列和最后一列的格子 
        if(a[i][1]==0)search(i,1);//如果有能过的就搜索 
        if(a[i][m]==0)search(i,m);
    }
    for(int i=1;i<=m;i++){//搜索第一行和最后一行的格子 
        if(a[1][i]==0)search(1,i);
        if(a[n][i]==0)search(n,i);
    }
    for(int i=1;i<=n;i++){//最后搜索没有被淹的格子 
        for(int j=1;j<=m;j++){
            if(a[i][j]==0)s++;
        }
    }
    cout<<s;//输出 
    return 0;
}
```
感谢大家能看我的题解!~

---

## 作者：是羊驼鸭 (赞：99)

这道题是一道挺基础的染色题

从（0,0）上下左右搜索染色，遇到障碍或者越界就回溯

最后会发现未被染色的非障碍的点就是被障碍保护的地区，最后遍历全地图寻找此类点数目即可

如果还想练习这类染色题目，可以再刷一下 1162 填涂颜色 来练练手

最后附上带有些许注释的小代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;   
char ch;   
int x,y,ans,map[550][550],dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};//dx,dy是上下左右四个方向（把0空了过去） 
void dfs(int m,int n)  
{ 
    if(m<0||n<0||m>x+1||n>y+1||map[m][n])  //如果越界或有障碍就回溯 
        return;  
    map[m][n]=2;   
    for(int i=1;i<=4;i++)  //上下左右搜索 
        dfs(m+dx[i],n+dy[i]);
}  
int main()
{
    scanf("%d%d",&x,&y);
    for(int i=1;i<=x;i++)  //习惯处理成数字地图 
        for(int j=1;j<=y;j++)
        {
            cin>>ch;  
            if(ch=='0')  
                map[i][j]=0; 
            else map[i][j]=1;
        }
    dfs(0,0);   //洪水开始泛滥 
    for(int i=1;i<=x;i++)  //寻找没有被洪水袭击的点即未被染色的点 
        for(int j=1;j<=y;j++)
            if(!map[i][j])
                ans++;   
    printf("%d",ans);
    return 0;  
}
```

---

## 作者：GaryH (赞：45)

# 题解

看题解里都是DFS或BFS或STL，那我就来一发DP。

## 1.题意

给一个$n \times m$的矩阵，求出矩阵中**与边界联通**的$0$的个数。

## 2.思路

我用 $\large dp_{i,j}$ 表示矩阵中$i$行$j$列的状态，其中：

如果 $\large dp_{i,j}=1$ 就表示矩阵中$i$行$j$列是墙；

如果 $\large dp_{i,j}=0$ 就表示矩阵中$i$行$j$列是当前未被淹没的空地；

相反，如果 $\large dp_{i,j}=2$ 就表示被淹没的空地。

然后，我们便可以把水淹没空地的过程抽象成被淹没的地**将'被淹没'的状态转移给旁边空地**的模型。

再说具体点，就是如果当前的 $\large dp_{i,j}$ 是2，就把它旁边的$0$也变成$2$，这就是深搜或宽搜的过程。

但是，我们可以对此过程进行一个优化，仔细想想，把刚才过程倒过来，就是：

如果当前的 $\large dp_{i,j}$ 是$0$且它四周有被淹没的地，或者说如果$\large dp_{i,j}=0$且$dp_{i-1,j}$或$dp_{i+1,j}$或$dp_{i,j-1}$或$dp_{i,j+1}$中任意一个是$2$,则 $\large dp_{i,j}$ 应变为$2$.

那我们现在就可以把代码写出来了。

我还是放一下代码，供大家参考。

## 3.Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[505][505],n,m,ans,last;
char ch;
int main(void){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			std::cin>>ch;
			if(ch=='*')dp[i][j]=1;
			//输入 
		}
	}
	for(int i=1;i<=n;i++){
		if(dp[i][1]==0)ans++,dp[i][1]=2;
		if(dp[i][m]==0)ans++,dp[i][m]=2;
		//初始化 
	}
	for(int i=1;i<=m;i++){
		if(dp[1][i]==0)ans++,dp[1][i]=2;
		if(dp[n][i]==0)ans++,dp[n][i]=2;
		//同上 
	}
	while(1){last=ans;ans=0;//一遍遍转移状态 
		for(register int i=1;i<=n;i++){
			for(register int j=1;j<=m;j++){
				if(dp[i][j]==0&&(dp[i-1][j]==2||dp[i+1][j]==2||dp[i][j-1]==2||dp[i][j+1]==2)){
					dp[i][j]=2;
					//状态转移 
				}
			}
		}
		for(register int i=1;i<=n;i++){
			for(register int j=1;j<=m;j++){
				if(dp[i][j]==0)ans++;
				//统计答案 
			}
		}
		if(last==ans){
			cout<<ans;
			return 0;
			//输出并退出 
		}
	}
	return 0;
}
```
## 好了，题解结束了，大家再见！

---

## 作者：xxxjz (赞：33)

大家好，本蒟蒻今天又来给大家发题解了！！

好了，废话不多说，咱们归入正题。

大家第一眼看到这道题，脑子里第一反应的都应该是
#### 深度优先搜索，DFS 吧！
本蒟蒻刚学DFS不久~~其实好早前就学了，忘了~~，这是一道很好的DFS题，适合新手们练手，老手们复习。

首先我们要想清楚我们搜索的是什么

我们搜索的应该是会被淹到的部分，一旦找到会被淹到的部分，就把它变成‘*’。

所以这题就很像找
### 联通块！！！

所以，我们的代码应该是：
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
//#pragma GCC optimize(3)
//sort(st.begin(),st.end());
using namespace std;
int xx[10]={0,0,-1,1};
int yy[10]={1,-1,0,0};
int n,m,gs;
char ch[510][510];
void dfs(int x,int y)
{
	if(x<1||y<1||x>n||y>m||ch[x][y]=='*')return;//边界
	ch[x][y]='*';//标记
	for(int i=0; i<4; i++)
		dfs(x+xx[i],y+yy[i]);//深度优先搜索
}
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++)
	    for(int j=1; j<=m; j++)
	        cin>>ch[i][j];
	dfs(1,1);
	for(int i=1; i<=n; i++)
	    for(int j=1; j<=m; j++)
	    {
	    	if(ch[i][j]=='0')
	    	{
	    		gs++;
			}
		}
	cout<<gs;
    return 0;
}

```
可当你信心满满的提交时，你就会收到luogu测评器给你的拥抱！！

![](https://cdn.luogu.com.cn/upload/image_hosting/fvc7qf46.png)

想知道为什么吗？

看看我下面出的这个数据：

```
5 5
0*000
*0000
00000
00000
00000
```
你会发现他给出的答案是22。？？？？？

那是因为我们刚搜到第一个0后就搜不下去了。

所以我想到了一个新办法：
# 多搜一圈！！！


```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
//#pragma GCC optimize(3)
//sort(st.begin(),st.end());
using namespace std;
int xx[10]={0,0,-1,1};
int yy[10]={1,-1,0,0};
int n,m,gs;
char ch[510][510];
void dfs(int x,int y)
{
	if(x<0||y<0||x>n+1||y>m+1||ch[x][y]=='*')return;
	ch[x][y]='*';
	for(int i=0; i<4; i++)
		dfs(x+xx[i],y+yy[i]);
}
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++)
	    for(int j=1; j<=m; j++)
	        cin>>ch[i][j];
	dfs(0,0);//多搜一圈
	for(int i=1; i<=n; i++)
	    for(int j=1; j<=m; j++)
	    {
	    	if(ch[i][j]=='0')
	    	{
	    		gs++;
			}
		}
	cout<<gs;
    return 0;
}



```


---

## 作者：江挽 (赞：17)

### ~~极水的dfs~~

其实题目说了这么多  就是要我们去寻找

### 四面八方都是'*'的 '0'

#### 知道了这些  这题就迎刃而解了

------------


#### 代码实现时间

其实呢  就是搜索所有'0'的四面八方

### 所以我们的灵魂dfs要这个~~亚子~~


```
void dfs(int m,int n)
{
	if(m<0||m>1+x||n<0||n>1+y||mp[m][n]){    
    //不能搜边界以外的
        return;
    }
    mp[m][n]=2;//标记搜过的点
    for(int i=1;i<=4;i++)
    {
    		dfs(m+fx[i],n+fy[i]);//搜索四个方向
    }
    return ;
}
```


------------

### 然后呢我们主函数可以利用下面的代码实现为0和不为0的点
```cpp
for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(s=='0')
			{
				mp[i][j]=0;
			}
			else
			{
				mp[i][j]=1;
			}
		}
	}
```


#### 搜索过后判断mp[i][j]是否为0
若为零就ans++
```cpp
for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(!mp[i][j])
				ans++;
		}
	}
```


------------
## CODE
#### ~~我知道你们只看这个~~

#### 最后提醒 题解虽好 可不要抄袭哦

```cpp
#include<bits/stdc++.h>
#define ll long long
#define _ =read();
//一些代码风格
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while (ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}//快读
int fx[5]={0,1,-1,0,0};
int fy[5]={0,0,0,1,-1};//用来存方向
ll x,y,ans;
char s;//不必多说 存每个点是'0'还是'*'
int mp[505][505];//用万能头的话一定不要定义map 别怪我没提醒你
void dfs(int m,int n)
{
	if(m<0||m>1+x||n<0||n>1+y||mp[m][n]){
    //不能搜边界以外的
        return;
    }
    mp[m][n]=2;//标记搜过的点
    for(int i=1;i<=4;i++)
    {
    		dfs(m+fx[i],n+fy[i]);//搜索四个方向
    }
    return ;
}

int main()
{
	x _ y _
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			cin>>s;
			if(s=='0')
			{
				mp[i][j]=0;
			}
			else
			{
				mp[i][j]=1;
			}
		}
	}
	dfs(0,0);
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(!mp[i][j])//若该点为零就ans++
				ans++;
		}
	}
	cout<<ans;
	fclose(stdin);fclose(stdout);
	return 0 //不要忘记好习惯
}
```
## ~~万水千山总是情，过篇题解行不行~~


---

## 作者：dfydada⚡⚡⚡ (赞：15)

我用的是广搜，可以分为两部分来写：

1. 先把没有被圈的给标记为洪水淹没的地方，就算是挨着边也不能算。如样例1，为什么只有一个点，因为其他的算是淹没的，所以不能算。

1. 在求出没有被淹没的个数（这里是个数，而不是几块，~~题目描述的很清楚，自己却没看见~~）。

这两步可以用同一个函数，只需要用判断是否累加没淹没的点就可以了。

我们先初始化数组s，在把0都当成没淹没的点，其他的当成淹没的点。
```cpp
	memset(s,true,sizeof(s));
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>ch;
			ch=='0'?s[i][j]=true:s[i][j]=false;
		}
	}
```
然后我们就要做我们的第一步：
我们需要在循环条件格外加两个点，为了防止一些淹没的地方是没淹没的情况（所以上面才需要初始化，也可以手动赋值）。

我们标记只能从最外围开始标记，不能胡乱标记，所以要加个判断（只有是最边缘才标记）。

```cpp
	for(int i=0;i<=n+1;i++)
	{
		for(int j=0;j<=m+1;j++)
		{
			if(j==0||i==0||i==n+1||j==m+1)
			{
				if(s[i][j])
				{
					asd(i,j);
				}
			}
		}
	}
```
通过调用asd函数去扩散寻找连锁的点，把假淹没的地方标记为真淹没。

之后用一bool变量来判断开始累加

asd函数就是广搜模板：

```cpp
void asd(int u,int v)
{
	int t,q,r=1,f=0;
	a[r]=u;
	b[r]=v;
	s[u][v]=false;
	while(r>f)
	{
		for(int i=0;i<4;i++)
		{
			t=a[f+1]+x[i];
			q=b[f+1]+y[i];
			if(t>0&&q>0&&t<=n&&q<=m&&s[t][q])
			{
				r++;
				s[t][q]=false;
				a[r]=t;
				b[r]=q;
				if(boolr)判断是否累加
				{
					sum++;
				}
			}
		}
		f++;
	}
}
```
然后在一个一个（n*m）的去找，把所有点都累加就可以了。

总代码：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)//O2优化
using namespace std;
typedef long long ll;
const int N=3000+10;
int n,m;
int sum,a[N],b[N];
int x[]={1,-1,0,0},
	y[]={0,0,-1,1};
char ch;
bool boolr,s[N][N];
void asd(int u,int v)
{
	int t,q,r=1,f=0;
	a[r]=u;
	b[r]=v;
	s[u][v]=false;
	while(r>f)
	{
		for(int i=0;i<4;i++)
		{
			t=a[f+1]+x[i];
			q=b[f+1]+y[i];
			if(t>0&&q>0&&t<=n&&q<=m&&s[t][q])
			{
				r++;
				s[t][q]=false;
				a[r]=t;
				b[r]=q;
				if(boolr)
				{
					sum++;
				}
			}
		}
		f++;
	}
}
int main()
{
	memset(s,true,sizeof(s));
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>ch;
			ch=='0'?s[i][j]=true:s[i][j]=false;
		}
	}
	for(int i=0;i<=n+1;i++)
	{
		for(int j=0;j<=m+1;j++)
		{
			if(j==0||i==0||i==n+1||j==m+1)
			{
				if(s[i][j])
				{
					asd(i,j);
				}
			}
		}
	}
	boolr=true;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j])
			{
				asd(i,j);
				sum++;
			}
		}
	}
	cout<<sum;
	return 0;
}

```


---

## 作者：lk_liang (赞：13)

## 这道题可以用深度优先搜索(dfs)


------------
###  主要思路是枚举内圈0 遍历所有0 如果有任意的0碰到了边界

### 0 那么意味着这片零被淹没了

### 我们就只记录这片0访问过 不要其算入答案值中



------------


枚举地图内圈（外圈可不考虑 因为外圈的重要区域一定被淹没了）

然后在内圈中寻找 **‘0’** 就开始进入dfs**（前提是这个零没被访问
过） **

目的是标记所有和这个0连在一起的0

直接上代码


```cpp
#include <iostream>
using namespace std;
int n,m,sum,ans;
char map[550][550];   // map用来装图
bool vis[550][550],flag;
int dirx[4]={0,0,1,-1};    //  用来模拟上下左右的坐标变化
int diry[4]={-1,1,0,0};
void dfs(int x,int y)
{
	for(int i=0;i<4;i++)
	{
		int xx=x+dirx[i];
		int yy=y+diry[i];
		if((xx==1||xx==n||yy==1||yy==m)&&map[xx][yy]=='0') flag=true;   // 如果有任意的0碰到了边界0 那就是被淹没了 记flag
		if(map[xx][yy]=='*'||xx==1||xx==n||yy==1||yy==m||vis[xx][yy])  continue;
		sum++;
		vis[xx][yy]=true;
		dfs(xx,yy);
	}
}
int main()
{
	cin>>n>>m; 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>map[i][j]; 
	for(int i=2;i<n;i++)     //  枚举内圈
	{
		for(int j=2;j<m;j++)
		{
			if(map[i][j]=='0'&&!vis[i][j])  // 发现0且0没有被访问过
			{
				vis[i][j]=true;   // 记录这个点被访问过
				flag=false;       // 更新flag
				sum=1;            // 记录这一片的0（可能有很多片）所以要更新
				dfs(i,j);         // 开始递归
				if(flag) sum=0;   // 如果这一片区域是被淹没了的 记sum为0
				ans+=sum;		  // 更新答案
			}
		}
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：扬皓2006 (赞：9)

这仍是一道DFS求联通块的题目

可见P1596的代码上做些改动

安利一下我P1596的题解链接

[Here it is.](https://www.luogu.org/blog/20160614dbdaw/p1596-hu-ji-shuo-lake-counting-ti-xie)

好了废话不多说，进入代码:

```
#include<bits/stdc++.h>//万能头
using namespace std;
char a;//不用字符数组的原因是省空间
int x,y,coun;//coun为计数器，全局变量初始定义为0
int dx[4]={0,0,0,1,-1};//横轴4方向数组
int dy[4]={0,1,-1,0,0};//纵轴4方向数组
int ma[550][550];//地图数组
void dfs(int m,int n)//重头戏
{
	if(m<0||m>x+1||n<0||n>y+1||ma[m][n])//如越界或为围墙，返回 
	return ;	
	ma[m][n]=2;//标记为已走过
	for(int i=0;i<=3;i++)
	{
		dfs(m+dx[i],n+dy[i]);//搜索4方向
	}
}
int main()
{
	scanf("%d%d",&x,&y);//输入横轴长度，纵轴长度
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			cin>>a;//输入
			if(a=='0')
			ma[i][j]=0;//标记为空地
			else
			ma[i][j]=1;//标记为围墙
		}
	}
	dfs(0,0);//开始搜索
	for(int i=1;i<=x;i++)
		for(int j=1;j<=y;j++)
			if(!ma[i][j])
				coun++;	//未被染色就++
	cout<<coun;//输出
	return 0;
}

建议训练的类型题：
P1451 P1596
希望各位同学都能顺利学会DFS求联通块,搜索是很重要的一种做(pian)题(fen)方法，掌握了就能拿（pian）到更多分。

最后，希望管理大大能通过此题题解！

---

## 作者：Garrison (赞：9)

# 无聊的我决定发一篇题解
## 前言
一道很基础的DFS

~~输入不多讲，搜索太简单不多讲，讲完了~~
## 切入正题~满分思路
其实是一道求连通块的题，每次在边缘找，尽可能的将能扩展的点扩展，再将这些点统计一下得出个数，最后用总点数减去这些点就好了。
## 代码实现
### 输入
```
	std::ios::sync_with_stdio(false);
	std::cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			std::cin>>a[i][j];
			if(a[i][j]=='*')
				b[i][j]=1,++ans;
		}
```
## 依次搜索
要从分别四条边搜，否则会漏情况
```
	for(int i=1;i<=n;++i){
		if(a[i][1]=='0')
			s(i,1);
		if(a[i][m]=='0')
			s(i,m);
	}
	for(int j=1;j<=m;++j){
		if(a[1][j]=='0')
			s(1,j);
		if(a[n][j]=='0')
			s(n,j);
	}
```
## 输出
```
	std::cout<<n*m-ans<<"\n";
```
## 搜索
如何实现搜索？

1、边界条件 

2、判重/递归终止条件

3、每次递归要干什么（每次递归要将能拓展的点拓展，并将其改变）
```
void s(int x,int y){//位置
	if(x>n||y>m||x<1||y<1||b[x][y])//边界条件
		return;
	b[x][y]=1,++ans;//改变
	for(int i=0;i<4;++i)
		s(x+wx[i],y+wy[i]);//向四个方向拓展
}
```
## Code（很短的代码）
```
#include<iostream>
#define N 505
char a[N][N];
int ans,n,m;
bool b[N][N];
const int wx[5]={0,0,1,-1};
const int wy[5]={1,-1,0,0};
void s(int x,int y){
	if(x>n||y>m||x<1||y<1||b[x][y])
		return;
	b[x][y]=1,++ans;
	for(int i=0;i<4;++i)
		s(x+wx[i],y+wy[i]);
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			std::cin>>a[i][j];
			if(a[i][j]=='*')
				b[i][j]=1,++ans;
		}
	for(int i=1;i<=n;++i){
		if(a[i][1]=='0')
			s(i,1);
		if(a[i][m]=='0')
			s(i,m);
	}
	for(int j=1;j<=m;++j){
		if(a[1][j]=='0')
			s(1,j);
		if(a[n][j]=='0')
			s(n,j);
	}
	std::cout<<n*m-ans<<"\n";
	return 0;
}
```




---

## 作者：wangyansong (赞：6)

受到p1162题的启发，制造一个大的连通块。将外围全部套一层0将‘*’外部的所有0全部联通到一起，最后进行计数就可以
顺便说一下联通块
联通块这个比较抽象，举个例子就是假设一条鱼在一个池塘里游泳，那么在时间不限的情况下，小鱼会游过池塘的所有位置，而这个与小鱼的出发点是无关的。
所以在本题中，假设从一个坐标开始，对他能经过的所有点进行标记，那么在剩下的询问中，如果询问的坐标已经被标记，那么它所经过的点与假设的坐标是相同的。
```c
#include<bits/stdc++.h>
using namespace std;
int b[505][505];
char c;
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int n,z,m;
void dfs(int p,int q)
{
    if(p<0||p>n+1||q<0||q>m+1||b[p][q]) return ;//判边界要跟多一层判，这个很特殊
    b[p][q]=1;
    for(int i=0;i<4;i++)
    dfs(p+dx[i],q+dy[i]);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
     {
      cin>>c;
      if(c=='*') b[i][j]=1;//就是为了方便
        }
     dfs(0,0);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
     if(b[i][j]==0)z++;
     cout<<z;
     return 0;
}
```


---

## 作者：郭承毅 (赞：4)

(=￣ω￣=)喵了个咪————

我是郭承毅( • ̀ω•́ )✧

hi✿(。◕ᴗ◕。)✿

聊五分钱的天吗？|ω･)و ̑̑༉

发起进攻( ´-ω ･)▄︻┻┳══━一

这题用DFS和染色很简单！！！染四条边上每个位置的连通‘0’，接着再染，再染。。。。。。

作为新手（王小悦：对，你个垃圾），我表示这题完全看不懂好吗！！！（抄袭RS《好好说话》fromB站）

唉。。。算了发个题解。。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[505][505];//地图
struct NODE//结构体，为了方向偏移
{
	int x,y;
};
NODE move[4]={{-1,0},{0,-1},{0,1},{1,0}};//方向偏移数组
void DFS(int x,int y)//染色
{
	if(mp[x][y]=='0')mp[x][y]='*';
	else return;//染色
	for(int i=0;i<4;i++)
	{
		int nx=x+move[i].x,ny=y+move[i].y;//下个位置
		DFS(nx,ny);
	}//方向偏移
	return;
}
int main()
{
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>mp[i][j];
	for(int i=1;i<=m;i++)//第1行和第n行上所有格子
	{
		DFS(1,i);
		DFS(n,i);
	}
	for(int i=1;i<=n;i++)//第2行至第n-1行上第一个或第m个
	{
		DFS(i,1);
		DFS(i,m);
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)//找一下‘0’
		{
			if(mp[i][j]=='0')
			{
				cnt++;//计数
			}
		}
	cout<<cnt<<endl;//输出
	return 0;
}
```

### 

P.s.王小悦是我的一个同班同学！！！

---

## 作者：liujiayuan (赞：3)

偷偷瞄了一眼题解区好像没有很多bfs解法，那我就来一波

## ~~还有为什么大部分人的解法都是水从四面八方淹过来啊总感觉怪怪的~~

此题思路还是很清晰的，枚举每个点，从每个未被标记过‘0’处开始bfs，覆盖该区域的每一个‘0’，并在flag标记数组中存好对应区域的编号，另外开一个bool类型的f数组，如果bfs在该区域中搜到了边界，就在f数组中把该编号记录为0，最后再把图遍历一遍，找每个非0的flag的编号，该编号在f中为1的，ans++，否则继续

思路讲解完毕，接下来见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,flag[505][505]={0},cnt=1;   //注意这个cnt变量
long long ans=0;
char ma[505][505];
bool f[250005];          //f数组存编号是否可行
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};    //四个方向
struct node
{
	int x,y;
};
inline void bfs(int a,int b)
{
	queue <node> q;
	node o;
	o.x=a;o.y=b;
	q.push(o);
	flag[a][b]=cnt;   
    //在此处以及下面的标记中，是把flag赋为cnt，作为编号
	while(!q.empty())
	{
		o=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nx=o.x+dx[i];
			int ny=o.y+dy[i];
			if(nx<0||ny<0||nx>=n||ny>=m)
			{
				f[cnt]=0;
				continue;
			}
			if(flag[nx][ny]!=0||ma[nx][ny]!='0')
			{
				continue;
			}
			node next;
			next.x=nx;next.y=ny;
			q.push(next);
			flag[nx][ny]=cnt;
		}
	}
}
int main()
{
	cin>>n>>m;
	int woc=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>ma[i][j];
			f[woc]=1;   //f数组初始化为1
			woc++;
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(ma[i][j]=='0'&&flag[i][j]==0)
			{
				bfs(i,j);
				cnt++;
			} 
            //从每一个未被标记过的‘0’开始搜
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(f[flag[i][j]]==1&&flag[i][j]!=0)
			{
				ans++;
			}
            //最后把图遍历一遍，找出其中所有编号在f数组中为1的点
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Komorebi_shine (赞：3)

感觉前面的题解都很难懂，在此讲一下广搜的STL版题解

首先根据楼下某大佬的建议，我们把矩阵周围都围上一层0，队列里先加入（0，0），相当于最后会把外面的一圈0填满后（不影响答案）从四周向里面扩展，就省去了循环枚举边界在分别搜索的过程。

这题的队列显然存的是坐标，两个量，所以可以用pair（有关pair请上网或查询资料），再使用queue及库函数解题（我本来就是准备练手STL的）

```cpp
#include<bits/stdc++.h>
using namespace std;
queue<pair<int,int> > duilie;
const int fx[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
int i,n,m,j,a[502][502],s;
char c;
bool pd(int x,int y)
{
	return (x>=0&&x<=n&&y>=0&&y<=m);
}
void bfs()
{
	if (duilie.empty()) return;
	int ii;
	for (ii=0;ii<4;ii++) if (a[duilie.front().first+fx[ii][0]][duilie.front().second+fx[ii][1]]==0)
	if (pd(duilie.front().first+fx[ii][0],duilie.front().second+fx[ii][1])) 
	{
		duilie.push(make_pair(duilie.front().first+fx[ii][0],duilie.front().second+fx[ii][1]));
		a[duilie.front().first+fx[ii][0]][duilie.front().second+fx[ii][1]]=-1;
	}
	duilie.pop();
	bfs();
}
int main()
{
	scanf("%d%d",&n,&m);
	for (i=0;i<=n+1;i++) a[i][0]=a[i][m+1]=0;
	for (j=0;j<=m+1;j++) a[0][j]=a[n+1][j]=0;
	for (i=1;i<=n;i++)
	 for (j=1;j<=m;j++)
	 {
	 	cin>>c;
	 	if (c=='*') a[i][j]=-1;
	 }
	duilie.push(make_pair(0,0));
	bfs();
	for (i=1;i<=n;i++)
	 for (j=1;j<=m;j++)
	  if (a[i][j]==0) ++s;
	printf("%d\n",s); 
}
```
这就是我交的代码。可惜的是，不论怎么改都是10WA，样例还是过的，根本调不出来，就有了外面那个帖。

以下是一组我手出的数据，把这个程序卡掉了
```
3 3
0*0
*0*
0*0
输出：1
我：2
```
究其原因还是我手贱，上面

return (x>=0&&x<=n&&y>=0&&y<=m);

这一句看错了，应该打成x<=n+1和y<=m+1，改过来就行了。（暴力防抄）

---

## 作者：doby (赞：3)

怎么还是只有Pascal题解……

直接水淹总部，计算没有墙的和没被淹的，剩下的就是没被淹到的……

```cpp
#include<iostream>
using namespace std;
int n,m,a[502][502]={{0}},b[502][502]={{0}},i,j,ans;
char c;
void ts(int x,int y)
{
    if(x<0||x>n+1||y<0||y>m+1||a[x][y]==1||b[x][y]==4){return;}//不说了，就是深搜……
    a[x][y]=2,b[x][y]++;//标记并且和墙错开
    ts(x+1,y);//四个方向
    ts(x-1,y);
    ts(x,y+1);
    ts(x,y-1);
}
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cin>>c;
            if(c=='*'){a[i][j]=1;}
            else{a[i][j]=0;}
        }
    }
    ts(0,0);//放水……
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(a[i][j]){ans++;}//如果有东西，加上……
        }
    }
    ans=n*m-ans;//面积-有东西的面积
    cout<<ans;
}
```

---

## 作者：linyorson (赞：2)

这题……就是填涂颜色的变版！可以用和填涂颜色一样的思路：先假设所有的都被围墙围住，再模拟洪水从四面八方涌来……OK！

```cpp

void dg(int x,int y)  
{  
    if(x<0 || y<0 || x>b+1 || y>a+1 || d[x][y]=='1' || d[x][y]=='*')return;  
    d[x][y]='1';  
    dg(x+1,y);dg(x,y-1);dg(x,y+1);dg(x-1,y);  
}  

```
ps：这题和填涂颜色还是有区别，闭合圈可能没有，也可能很多！如果纯抄的话……吃wa吧。当然，还有其他更优的思路……我就不想了，因为我的思路简单，程序短啊


---

## 作者：jujujujuruo (赞：2)

一道相对基础的bfs题，和P1162题目很相似，可以先去写那道题练练手。

对于（1，1）...到（x， y）
一般的dfs都是从第一个点（1，1）开始搜，但是为了防止题目比较坑如果第一个就走不通（例如样例二），可以考虑在外面加上一圈可以走的就可以了。

我的具体思路是用一个mapp的二维数组来模拟，把不能走的（就是* ）和走过的都标记为false，最后遍历一下哪些地方没走过的（就还是true）就AC啦！

具体的请看代码：

为了debug我加了一个print函数，为了保持美观~~我懒得删~~就留着了
```cpp
#include<cstring>
#include<cstdio>
#include<iostream>
using namespace std;

int dx[] = { 0, -1, 1, 0, 0},
    dy[] = { 0, 0, 0, 1, -1};
int x, y;
bool mapp[505][505];

void dfs(int p, int q);
void print();
int main()
{
    int i, j, ans = 0;
    char tem[505];
    scanf("%d %d", &x, &y);
    memset(mapp, 1, sizeof(mapp));
    for(i=1;i<=x;i++)
    {
        scanf("%s", tem+1);
        for(j=1;j<=y;j++)
        {
            if(tem[j]=='*')
                mapp[i][j] = false;
        }
    }
    //print();
    dfs(0, 0);
    //print();
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=y;j++)
        {
            if(mapp[i][j]) ans++;
        }
    }   
    printf("%d\n", ans);
    return 0;
}
void dfs(int p, int q)
{
    int i, tx, ty;
    for(i=1;i<=4;i++)
    {   
        tx = p + dx[i];
        ty = q + dy[i];
        if(tx>=0 && tx<= x + 1 && ty>=0 && ty <=y+1 && mapp[tx][ty])
        {
            mapp[tx][ty] = false;
            dfs(tx, ty);
        }
    }
    return ;
}
void print()
{
    int i, j;
    for(i=1;i<=x;i++)
    {
        for(j=1;j<=y;j++)
            printf("%d", mapp[i][j]);
        printf("\n");
    }
    printf("\n");
    return ;
}
```


---

## 作者：Cambridge (赞：2)


小学生又来发题解了！

讲下思路：我们从第0行第0列开始找起，也就是最外围的再外一层。为什么呢？如果我们从第1行第1列开始找，如果当前位置是围墙，就找不下去了，所以要从第0行第0列开始找。接下来从外往里逐个访问可能的位置，把洪水能到达的地方标记一下。搜索完之后，再枚举每一个位置，如果不是洪水能到达的地方而且不是围墙，累加器加1。讲完思路，如果读者还不懂，我继续在程序中解释： 

	#include<iostream>
	#include<cstring>
	#include<cstdio>
	#include<cmath>
	#include<string>
	#include<cstdlib>
	#include<algorithm>//文件头不解释
	using namespace std;
	int n,m,head,tail,f[505][505],xx,yy,sss,ll;
	int dx[4]={-1,1,0,0};
	int dy[4]={0,0,-1,1};//控制上下左右
	char st[505][505];
	void dfs(int x,int y)
	{
	if(x<0||x>n+1||y<0||y>m+1||f[x][y]==1)return ;//如果当前位置越界或者是围墙或者被访问过，返回上一层。
	    f[x][y]=1;//标记当前访问的位置，下次不用访问
	    for(int i=0; i<4; i++)
	    {
	    	dfs(x+dx[i],y+dy[i]);//上下左右都找一找
	    }
	   	return ;
	}
	int main()
	{
	  cin>>n>>m;//读入n和m 
	  for(int i=1; i<=n; i++)
	  	for(int j=1; j<=m; j++)
	  	   {
	  	   	cin>>st[i][j];
	  	   	if(st[i][j]=='*')f[i][j]=1;//如果是围墙，标记
	  	   }
	 dfs(0,0);//开始搜索
	  for(int i=1; i<=n; i++)
	  	for(int j=1; j<=m; j++)
	  		if(f[i][j]==0)ll++;//如果当前位置被围住了，累加器ll加1
	  cout<<ll;//输出结果 
	  return 0;
}

好了，本蒟蒻就讲到这里，希望对读者有所帮助。 


---

## 作者：龙行龘龘 (赞：2)

# 看大家的题解写的都好玄学...

#### 我的思路呢--就是直接爆搜。

广搜模板题啊,看各位DA LAO的题解都写得好玄学,我就不废话了,讲个~~简单~~做法吧!

我在输入时就顺便做了一个判断:如果是洪水进不去的*号区域,就先标记下(flag数组就是标记啦!)。

然后就是对行列依次进行遍历,判断是否标记过(判重),如果没有标记过,就对这个位置进行一次广搜。

然后就是最后的累加及输出了。

#### 那么核心来了(敲黑板),广搜包含的内容:

我首先就是手动模拟了一个用于存储二维位置的队列,先给定头(h)和尾(t)的初值,然后再把传进来的位置入队,把这个位置标记上。现在就进入循环了,循环条件就是队列不为空,手动模拟时就可以写成:
```cpp
do {
	
	} while(h <= t);
```

或者是这样:
```cpp
bool empty_queue() {
	if(head == tail) {
		return 1;
	}
	return 0;
}
void BFS {
	do{

	} while(!empty_queue);
}
```
这时,偏移数组就要大显神通了,我们for循环枚举四个方向偏移,然后进行各种判断边界以及判断是否没标记过还有是否不为*号。如果条件符合尾就进行自加,相当于为下一次入队获取空间,然后再将偏移后的位置进行入队操作,标记已经走过。

程序完美return!

顺便献上我的blog:https://www.luogu.org/blog/Root-std-admin/

代码奉上:

```cpp
//Written By:Jason_Root
//Time Limit : 1000 MS
//Memory Limit : 65536 KB
#include<bits/stdc++.h>
using namespace std;
int n,m;//输入
int s,state[25100][2];
int dx[4]= {0,0,1,-1},dy[4]= {1,-1,0,0};//偏移
bool flag[501][501];//标记
char c[501][501];//输入矩阵
inline int read() {//快读
	char ch = getchar();
	int x = 0, f = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void BFS(int x,int y) {
	int h = 0,t = 1;
	state[1][0] = x;
	state[1][1] = y;
	flag[x][y] = true;
	//初始赋值 
	do {
		h++;
		for (int i = 0; i <= 3; i++) {
			if (state[h][0]+dx[i] >= 0 && state[h][0]+dx[i] <= n-1 && state[h][1]+dy[i] >= 0 && state[h][1]+dy[i] <= m-1 && !flag[state[h][0]+dx[i]][state[h][1]+dy[i]] && c[state[h][0]+dx[i]][state[h][1]+dy[i]] != '*') {//各种花式判边 
				t++;
				state[t][0] = state[h][0]+dx[i];
				state[t][1] = state[h][1]+dy[i];
				flag[state[t][0]][state[t][1]] = true;
				//如此操作(广搜模板啦) 
			}
		}
	} while(h <= t);
	return;
}
void func() {
	ios_base::sync_with_stdio(false);
	n = read();
	m = read();
	for(int i = 0; i <= n-1; i++) {
		scanf("%s",c[i]);
		for(int j = 0; j <= m-1; j++)
			if (c[i][j] == '*') flag[i][j] = true;//是封闭区域标记 
	}
	for(int i = 0; i <= m-1; i++) {
		if (!flag[0][i]) BFS(0,i);
		if (!flag[n-1][i]) BFS(n-1,i);
	}
	for(int i = 0; i <= n-1; i++) {
		if (!flag[i][0]) BFS(i,0);
		if (!flag[i][m-1]) BFS(i,m-1);
	}
	//行列依次进行广搜 
	for(int i = 0; i <= n-1; i++)
		for(int j = 0; j <= m-1; j++)
			if (!flag[i][j]) s++;//没被水淹没计数加一 
	printf("%d",s);//输出 
	return;
}
int main() {
	func();
	return 0;
}

```
真心感谢大家观看,谢谢!!!

---

## 作者：DaftLord (赞：2)

{主要思想是模拟水从四面八方涌入，把会被淹没的点标记成1，最后再统计}

   

```cpp
pascal搜索;
var a:array[0..500,0..500] of char;
    i,j,n,m,ans:longint;
procedure search(x,y:longint);//搜索过程；
begin
 if (x<=0) or (y<=0) or (x>n) or (y>m) then exit;//如果越界就退出；
 if a[x,y]<>'0' then exit;//如果不是0就退出；
 a[x,y]:='1';//把这个点变成1，表示该点会被（不）水（知）淹（所）没（错）；
 search(x-1,y);//向上下左右四个方向搜索；
 search(x+1,y);
 search(x,y-1);
 search(x,y+1);
end;
begin
 readln(n,m);//输入；
 for i:=1 to n do
 begin
  for j:=1 to m do read(a[i,j]);
  readln;
 end;
 for i:=1 to n do//模拟水从四个方向涌来；
 begin
  search(i,1);//搜索第一列；
  search(i,m);//最后一列；
 end;
 for i:=1 to m do
 begin
  search(1,i);//第一行；
  search(n,i);//最后一行；
 end;
 ans:=0;
  for i:=1 to n do
   for j:=1 to m do 
    if a[i,j]='0' then inc(ans);//计数；
 writeln(ans);
end.
```

---

## 作者：Khassar (赞：1)

/\*
看了看没有c++的宽搜题解，那我就来一个

这是一道比较基础的搜索题，让洪水从四面八方淹过来，把淹了的点打上标记，

最后再扫一遍看看哪些点不是障碍还没被标记，那它就是没被淹到的地区。

思路下面的说的都挺好，主要都是清一色的深搜，就忍不住想贡献个宽搜的题解

顺便安利一下Blog：https://dedsecr.github.io/

\*/








```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<ctime>
#define ll long long
#define R register
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define D double
using namespace std;
const int N=505;
int n,m,a[N][N],vis[N][N],ans; 
//n是行，m是列，a数组用来记图，vis数组用来标记点有没有淹过，ans用来统计最终答案 
int dx[4]={0,1,0,-1};//宽搜用的方向数组 
int dy[4]={1,0,-1,0};
char ch;
queue <int> q1,q2;
inline int read() {//读入及输出优化 
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int main()
{
    n=read();m=read();
    Rf(i,1,n) Rf(j,1,m) {
        cin>>ch;//把图读进来 
        if(ch=='0') a[i][j]=1;//如果是'0'那它就是一块空地记为1
        //否则就是障碍，默认记为0，这样还能够免于特判边界 
    }
    //枚举外面一圈，如果不是障碍，就说明洪水能从此处进来，加入队列 
    Rf(i,1,n) {
        if(a[i][1]) {
            q1.push(i);q2.push(1);
            vis[i][1]=1;
        }
        if(a[i][m]) {
            q1.push(i);q2.push(m);
            vis[i][m]=1;
        }
    }
    Rf(i,1,m) {
        if(a[1][i]) {
            q1.push(1);q2.push(i);
            vis[1][i]=1;
        }
        if(a[n][i]) {
            q1.push(n);q2.push(i);
            vis[n][i]=1;
        }
    }
    //// 
    while(!q1.empty()) {//宽搜开始 
        R int nowx=q1.front(),nowy=q2.front();q1.pop();q2.pop();
        Rf(i,0,3) {//枚举四个方向 
            R int x=nowx+dx[i],y=nowy+dy[i];
            if(a[x][y]&&!vis[x][y]) {//如果这个点是空地并且没有被淹过 
            //那它现在被淹了，加入队列 
                q1.push(x);q2.push(y);
                vis[x][y]=1;
            }
        }
    }
    Rf(i,1,n) Rf(j,1,m) {//扫一遍全部的点
    //如果这个点不是障碍还没有被标记，那它就没有被淹，ans+1 
        if(!vis[i][j]&&a[i][j]) ans++;
    }
    write(ans);//ans就是最终答案了 
    return 0;
}

```

---

## 作者：流浪鬣狗 (赞：1)

# 不知何故A了
# ???
### 我也不知道是不是广搜？？
## 思路是这样的：
1. 先把地图保存到一个二维数组中
1. 围墙（“*”）记为1
1. 重要区域（“0”）记为0
1. 四圈判断，当前位置为1时，bfs函数一下（见程序）
1. bfs时，被淹的全记为-1
1. last，统计数组中1的个数，输出
# 莫名其妙的AC了

```cpp
#include<iostream> 
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>

using namespace std;
int a[510][510],n,m;
int fx[9]={-1,0,0,1},
	fy[9]={0,-1,1,0};
void bfs(int x,int y)
{
	if(a[x][y]==1)a[x][y]=-1;
	else return ;
	for(register int i=0;i<4;i++)
	{
		if(x+fx[i]>0&&x+fx[i]<=n&&y+fy[i]>0&&y+fy[i]<=m)
			bfs(x+fx[i],y+fy[i]);
	}
}
char ch[510];
int i,j,sum;
int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		for(j=1;j<=m;j++)
		{
			if(ch[j]=='*')a[i][j]=0;
			else a[i][j]=1;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==1)
				if(i==1||i==n)bfs(i,j);
				else if(j==1||j==m)bfs(i,j);
		}
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==1)sum++;
		}
	printf("%d\n",sum);
	//printf("%d\n",clock());
	return 0;
}


```



---

## 作者：就是小马啊 (赞：0)

染色问题
思路：遇到不是非保护的地区需要染色，将该点的值赋为‘1’，最后统计为值为‘0’的个数即为所求的答案。
注意：若某一行或某一列全为 * 时，只使用一个dfs(0, 0)可能搜索不全导致答案错误。
下面是代码
```cpp
#include <iostream>
#include<cstdio>
using namespace std;
int x, y;
char m[505][505];
void dfs(int a, int b) {
    if (a < 0 || a >= x || b < 0 || b >= y || m[a][b] != '0')
        return;
    m[a][b] = '1';
    dfs(a + 1, b);
    dfs(a - 1, b);
    dfs(a, b + 1);
    dfs(a, b - 1);
}
int main() {
    int ans = 0;
    cin >> x >> y;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> m[i][j];
        }
    }
    for (int i = 0; i < x; i++) {
        dfs(i, 0);
        dfs(i, y - 1);
    }
    for (int j = 0; j < y; j++) {
        dfs(0, j);
        dfs(x - 1, j);
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (m[i][j] == '0')    ans++;
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：小丑 (赞：0)

转载自http://blog.csdn.net/yuyaohekai/article/details/50359724

这是暴力搜索；

然后
就相当于先当所有地方都没有被水淹没，然后一点一点地搜索，一点点地用水淹没过去，碰到墙就停止。最后只要统计下没被淹没的地方就可以。

```delphi
var
   n,m,i,j,ans,k:longint;
   s:ansistring;
   a:array[0..501,0..501] of longint;
begin
  readln(n,m);
  for i:=1 to n do
    begin
      readln(s);
      for j:=1 to m do
      begin
        if s[j]='0' then a[i,j]:=2;
        if s[j]='*' then a[i,j]:=1;
      end;
    end;
{上面是将符号转化为每个点的状态，a[i,j]表示当前这个点，1为围墙，2为空地，0代表已被水淹没了。}
  for i:=1 to n do
  begin
    for j:=1 to m do
    if a[i,j]=2 then a[i,j]:=0 else if a[i,j]=1 then break;
    for j:=m downto 1 do
    if a[i,j]=2 then a[i,j]:=0 else if a[i,j]=1 then break;
  end;
  for i:=1 to m do
  begin
    for j:=1 to n do
    if a[j,i]=2 then a[j,i]:=0 else if a[j,i]=1 then break;
    for j:=n downto 1 do
    if a[j,i]=2 then a[j,i]:=0 else if a[j,i]=1 then break;
  end;
{以上是各个方向上的搜索}
  ans:=0;
  for k:=1 to n do
  for i:=1 to n do
    for j:=1 to m do
    if a[i,j]=0 then
    begin
      if a[i-1,j]<>1 then a[i-1,j]:=0;
      if a[i+1,j]<>1 then a[i+1,j]:=0;
      if a[i,j-1]<>1 then a[i,j-1]:=0;
      if a[i,j+1]<>1 then a[i,j+1]:=0;
    end;
{最后在筛选一遍看看有没有漏网之鱼}
  for i:=1 to n do
    for j:=1 to m do if a[i,j]=2 then inc(ans);
  writeln(ans);
end.
{统计加上输出}
```
这道题主要要细心，想到多种复杂的情况，所以请有耐心。

很容易出现过了样例然而评测没分的状况。


---

## 作者：zhanghb (赞：0)

这是一道十分经典的深搜问题

由题意可知，被‘*’包围的0有几个，就是我们所需要的答案

那什么样的0才算被包围呢，也就是说，这个0无论上下左右这么搜索，遇到的都是‘*’，不会碰到边界

那反过来想，我们只要从边界出发，把所有可以到达边界的0全部用1或非0的其他任何字符代替，最后统计剩下几个0，就是我们需要的答案

-------------------------------
附AC代码
```
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int qp[505][505] = { 0 };
int tx[5] = { 0,1,-1,0,0 };
int ty[5] = { 0,0,0,1,-1 };
int n, m;
int dfs(int x,int y)
{
	int i;
		for(i=1;i<=4;i++)//上下左右共搜索四次
		if (qp[x + tx[i]][y + ty[i]]==0&&qp[x + tx[i]][y + ty[i]]!=1&& x + tx[i] >= 0 && x + tx[i] <= n + 1 && y + ty[i] >= 0 && y + ty[i] <= m + 1)//判断下一步不越界且值为0
		{
			qp[x+tx[i]][y+ty[i]]=2;//把下一步值为2
			dfs(x + tx[i], y + ty[i]);//走出下一步
		}
}
int main()
{
	char a[505][505];
	int i, j, cn=0;
	cin >> n >> m;//输入行数和列数
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
		{
			cin >> a[i][j];//输入字符
			if (a[i][j] == '0')
				qp[i][j] = 0;
			if (a[i][j] == '*')
				qp[i][j] = 1;//为了方便处理，把字符转化成数字（不做也可以）
		}
	qp[0][0] = 2;
	dfs(0, 0);//从坐标0，0开始搜索，搜索到n+1,m+1;把边界都搜索到
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
				if (qp[i][j] == 0)
				cn++;//统计剩下的0
	cout << cn;//输出
}
```


---

