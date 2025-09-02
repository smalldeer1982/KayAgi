# Likecloud-吃、吃、吃

## 题目背景

问世间，青春期为何物？

答曰：“甲亢，甲亢，再甲亢；挨饿，挨饿，再挨饿！”


## 题目描述

正处在某一特定时期之中的李大水牛由于消化系统比较发达，最近一直处在饥饿的状态中。某日上课，正当他饿得头昏眼花之时，眼前突然闪现出了一个 $n \times m(n,m \le 200)$ 的矩型的巨型大餐桌，而自己正处在这个大餐桌的一侧的中点下边。餐桌被划分为了 $n \times m$ 个小方格，每一个方格中都有一个圆形的巨型大餐盘，上面盛满了令李大水牛朝思暮想的食物。李大水牛已将餐桌上所有的食物按其所能提供的能量打了分（有些是负的，因为吃了要拉肚子），他决定从自己所处的位置吃到餐桌的另一侧，但他吃东西有一个习惯——只吃自己前方或左前方或右前方的盘中的食物。

由于李大水牛已饿得不想动脑了，而他又想获得最大的能量，因此，他将这个问题交给了你。

每组数据的出发点都是最后一行的中间位置的下方！

## 说明/提示

快吃！快吃！快吃！


## 样例 #1

### 输入

```
6 7
16 4 3 12 6 0 3
4 -5 6 7 0 0 2
6 0 -1 -2 3 6 8
5 3 4 0 0 -2 7
-1 7 4 0 7 -5 6
0 -1 3 4 12 4 2
```

### 输出

```
41
```

# 题解

## 作者：2016jzy (赞：81)

这题跟数字金字塔的做法类似。。

只不过数字金字塔是往两条路线搜索，这题是往三条路线搜。。。

动态方程：            f[i][j]=max(max(f[i-1][j],f[i-1][j-1]),f[i-1][j+1])+a[i][j];

```cpp
#include<iostream>
#include<cstring>                             //头文件
using namespace std;
int n,m,a[201][201],f[201][201]={0},x,y;
int main()
{
    cin>>n>>m;
    y=m/2+1;x=n;                           //求出李大水牛最开始的位置
    memset(a,-9999,sizeof(a));               //设置边界，为了避免李大水牛吃到餐桌外面去。。
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];               //输入
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            f[i][j]=max(max(f[i-1][j],f[i-1][j-1]),f[i-1][j+1])+a[i][j];         //动态方程
        }
    }
    cout<<max(max(f[x][y],f[x][y-1]),f[x][y+1])<<endl;       //因为最大值只可能在李大水牛的前方、左前方、右前方，所以只要找这三个的最大就行了
    return 0;
}
```

---

## 作者：feecle6418 (赞：65)

其实这道题里面，f数组完全是多余的。我们可以直接在a数组里面迭代更新。
又因为输入是从上往下输入，而第i行的状态只跟第i-1行有关，所以完全可以边输入边更新。所以，我们可以大大的简化代码：
```
//by tianbu
//24ms,2.79MB
//代码：0.34KB C++
#include <iostream>
using namespace std;
int a[1005][1005];
int main() {
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            a[i][j]+=max(a[i-1][j-1],max(a[i-1][j],a[i-1][j+1]));
        }
    }
    cout<<max(a[n][m/2],max(a[n][m/2+1],a[n][m/2+2]));
    return 0;
}
```


---

## 作者：冈崎梦美 (赞：23)

##打倒DP暴政，世界属于记搜！

~~虽然我不知道怎么回事这道题用记搜比DP慢就是了~~

这道题有个小坑点：有负数点（而且必须吃），所以如果一开始把记忆数组f赋值成-1就会挂。如果是DP就会WA,~~鬼知道为什么~~用记搜就会RE。


代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[202][202];
int f[202][202];
bool vis[202][202];//存放这个点有没有访问过
int n,m;
int my_max(int x,int y,int z)//三个数比较大小
{
    int ans=x;
    if (ans<y) ans=y;
    if (ans<z) ans=z;
    return ans;
}
int dfs(int x,int y)
{
    if (vis[x][y]) return f[x][y];
    for(int i=-1;i<=1;i++)
    {
        if ((y+i>0)&&(y+i<=n)&&(x-1>0))f[x][y]=max(f[x][y],dfs(x-1,y+i)+a[x][y]);//记忆化
    }
    vis[x][y]=true;
    return f[x][y];
}
int main()
{
    cin>>n>>m;
    memset(a,-9999,sizeof(a));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    memset(f,-0x3f,sizeof(f));//初始化
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=m;i++) f[1][i]=a[1][i],vis[1][i]=true;//第一排都无法再向下搜索了
    dfs(n+1,m/2+1);
    cout<<my_max(f[n][m/2],f[n][m/2+1],f[n][m/2+2])<<endl;//答案只有可能在这三个点里
    return 0;
}
//code by ちゃん
```

---

## 作者：prefer (赞：21)

看了其他dalao的记忆化搜索，我表示他们太强了

本蒟蒻只会易懂、好思考、好写的

# memory dfs

题目要注意：**他是从最后一行的中点的下方开始走的，不是从最后一行的中点的开始走的，也就是说他第一步可以选择(m,n/2+1),(m,n/2),(m,n/2+2)三个选择**

接下来我的代码就比较好懂了

枚举每次走三个方向，并记忆就好了

```cpp

#include<bits/stdc++.h>
using namespace std;
int m,n,a[205][205],f[205][205];
int read() {
	int ret=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) ch=='-'?f=-f,ch=getchar():ch=getchar();
	while(isdigit(ch))ret=(ret<<3)+(ret<<1)+(ch^48),ch=getchar();
	return ret*f;
}
void print(int x) {
	if(x<0) x=-x;
	if(x>10) print(x/10);
	putchar(x%10+'0');
}
int max(int a,int b) {
	return a>b?a:b;
}
int dfs(int Nowx,int Nowy) {
	if(f[Nowx][Nowy]) return f[Nowx][Nowy];
	if(Nowx<1||Nowy<1||Nowx>m||Nowy>n) return 0;
	return f[Nowx][Nowy]=max(dfs(Nowx-1,Nowy)+a[Nowx-1][Nowy],max(dfs(Nowx-1,Nowy-1)+a[Nowx-1][Nowy-1],dfs(Nowx-1,Nowy+1)+a[Nowx-1][Nowy+1]));//三个抉择
}
int main() {
	m=read(),n=read();
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			a[i][j]=read();
	print(max(dfs(m,n/2+1)+a[m][n/2+1],max(dfs(m,n/2)+a[m][n/2],dfs(m,n/2+2)+a[m][n/2+2])));//别忘记加上自己第一次的食物的能量
	return 0;
}

```

---

## 作者：yangwenbin (赞：16)

# P1508 Likecloud-吃、吃、吃

这道题与dp的数塔问题比较相似

只是这个是有三条路线的

所以我们可以用数塔问题的思维来解题

首先李大水牛一开始在最后一行的中间的下方故：
我么需要的答案为最后一行中间三个的最大值（及
max(dp[n][m/2+1],max(dp[n][m/2],dp[n][m/2+2]));
）

其次是递归公式 这是一个二维dp，dp公式是该值是他的左上、正上、右上的dp结果的最大值+自身（及
dp[i][j]=max(max(dp[i-1][j],dp[i-1][j+1]),dp[i-1][j-1])+dp[i][j];
）
### CODE
```
#include <bits/stdc++.h>     //万能头文件
using namespace std;
int n,m,dp[250][250];       //多开50，避免RE
int main(void){
	memset(dp,0,sizeof(dp));  //统一初始化
	cin>>n>>m;
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= m; ++j){
			cin>>dp[i][j];   //直接用dp数组存数值，节省空间（~~其实也省不了多少~~（强行划线））
		}
	}for (int i = 2; i <= n; ++i){
		for (int j = 1; j <= m; ++j){
			dp[i][j]=max(max(dp[i-1][j],dp[i-1][j+1]),dp[i-1][j-1])+dp[i][j];		//dp
		}
	}
	cout<<max(dp[n][m/2+1],max(dp[n][m/2],dp[n][m/2+2]));  //光荣输出，完结撒花
}
```


---

## 作者：wangcr (赞：9)

P1508题解

本蒟蒻第一次发题解，望管理员通过，还有请各位dalao勿喷..

其实这道题本身不难~~(然而本蒟蒻还是错了5次才AC)~~

楼下dalao已经说的足够清楚了，有两类思想可以解本题。

1、DFS加上剪枝~~(不加也可以，毕竟此题数据较小)~~

从起点，不断地向三个方向进行拓展，如果没有超出边界，取当前的最大值，即是否吃这个食物。最后在最上方进行搜索，找到最大值即可。

2、递推或者DP

因为李大牛只能向前，向左前方，向右前方(~~前进!!!~~)吃食物，为了让思路更清晰，我们便从上边往下边推。

状态转移方程：f[i][j]=f[i][j]+max(f[i-1][j],f[i-1][j-1],f[i-1][j+1])(1<=i<=m,1<=j<=n,f[i][j]表示在当李大牛在(i,j)时可以吃的食物的最大能量)

那么本蒟蒻用的是递推。

下面献上丑陋的代码...


------------------------华丽丽的分割线------------------------


```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[210][210];
int f[210][210];//用来记录当前能得到的最大能量值
int max(int i,int j,int k)
{
    if ((i>=j)&&(i>=k)) return i;
    if ((j>=i)&&(j>=k)) return j;
    return k;
}//手打MAX函数，速度比STL快很多
int main()
{
    int m,n;
    cin>>m>>n;
    memset(a,-9999,sizeof(a));
    for (int i=1;i<=m;i++)
    for (int j=1;j<=n;j++) cin>>a[i][j];//得到每个食物的能量
    for (int i=1;i<=m;i++)
    for (int j=1;j<=n;j++) {
        f[i][j]=a[i][j];
        f[i][j]=f[i][j]+max(f[i-1][j],f[i-1][j-1],f[i-1][j+1]);}
        //状态转移方程
    cout<<max(f[m][n/2+1],f[m][n/2],f[m][n/2+2]);
    //由于最后可以有三个点可以到达中点，所以我们最后还有比较一边，取其最大值..
}
```
冗长的代码结束了..

---

## 作者：K2sen (赞：8)

# P1508
### 所属知识点：DP

## 主要题意： 

就是求一个矩阵从下边走到上边,可以走自己前方或左前方或右前方.
问走到上边一共经过的路径和.

类型题：[P1216](https://www.luogu.org/problem/P1216)

## 解题思路：
参考上边的类型题(因为比较简单),我们可以从上边开始反着走走到下边.

反着走的话，我们可以知道当前这个地方的权值是由下方，左下方，走下方走来的.

因为问的是吃的能量最多，我们就取在三个地方中取一个max然后再加上当前这个地方的权值.

用一个式子可以表示为. f[i][j] = max(f[i - 1][j] , f[i - 1][j - 1], f[i - 1][j + 1]) + a[i][j];

f[i][j] 表示吃到这个地方一共可以吃到的最大能量值,

a[i][j] 表示这个地方食物的能量值.

### 期待已久的code上场啦：
```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define A 210

using namespace std;
int n, m, map[A][A];
int ans;

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			map[i][j] = read();
	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int a = max(map[i - 1][j - 1], map[i - 1][j]);
			map[i][j] += max(a, map[i - 1][j + 1]);
		}
	}
	ans = max(map[n][m / 2], map[n][m / 2 + 1]);
	ans = max(ans, map[n][m / 2 + 2]);
	cout<<ans;
}
```

---

## 作者：glorious_dream (赞：4)

```
### 这道题要用动态规划
# 我的思路是从已知图的下一行开始表示，根据题意，从下往上推
#include<cstdio>
#include<algorithm>
using namespace std;	
int a[220][220];   //是那个图
int main(){
	int m, n,ans = 0; //ans记录最大值
	scanf("%d%d",&m,&n);
	for(int i=0 ; i<=n+1 ; i++){  //要先把图外的地方标成负无穷，防止越界
		a[m+1][i] = -1e9;
	}
	for(int i=1 ; i<=m ; i++){   //同上
		a[i][0] = -1e9;
	}
	for(int i=1 ; i<=m ; i++){  //同上
		a[i][n+1] = -1e9;
	}
	a[m+1][(n+1)/2] = 0;  //初始化，从最下面一行的中间出发，这时就可以看出来，上面的初始化是防止越界，
    防止这个数下面的数是负数，所以把两边都标成负无穷，就可以继续进行了
	for(int i=1 ; i<=m ; i++){
		for(int j=1 ; j<=n ; j++){
			scanf("%d",&a[i][j]); //把图输进去
		}
	}
	for(int i=m ; i>=1 ; i--){  // **注意** i要从最后一行倒着循环
		for(int j=1 ; j<=n ; j++){
			a[i][j] = max(max(a[i+1][j-1],a[i+1][j]),a[i+1][j+1])+a[i][j];  //转移方程，每一个点都可以从左下/正下/右下走到，在三个中取一个最大的
		}
	}
	for(int i=1 ; i<=n ; i++){
		ans = max(ans , a[1][i]);  //第一行是最终的答案，用ans来记录第一行最大的数，就是答案
	}
	printf("%d",ans); //最后输出答案
	return 0;
}
```

---

## 作者：蒟蒻CGZ (赞：3)

我们知道，一个点只能从它的右上方、右边和右下方过来;

所以我们从终点向前倒带，得到递推式 f[i][j]=max(max(f[i-1][j],f[i-1][j-1]),f[i-1][j+1])+a[i][j]。

所以，可得：

# 程序

```cpp
#include <iostream>
using namespace std;
int a[1005][1005];
int main() {
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            a[i][j]+=max(a[i-1][j-1],max(a[i-1][j],a[i-1][j+1]));
        }
    }
    cout<<max(a[n][m/2],max(a[n][m/2+1],a[n][m/2+2]));
    return 0;
}
```

边输入边处理。

~~cgz出品，必是精品。~~

---

## 作者：Max_Leo (赞：2)

[传送门](https://www.luogu.org/problem/P1508)
##### 好像看到所有巨佬都是用反过来从上往下吃的
###### 本蒟蒻还是按照题目要求从从下往上吃
###### 其实动态转移方程都是
#### 一样的
### dp[i][j]=max(max(dp[i+1][j],dp[i+1][j-1]),dp[i+1][j+1])+mp[i][j];
##### dp[i][j]表示吃到第i行第j列所获得的能量，而这个位置可以从之前一行下面，左边，右边得来的。
刚开始的边界条件
```cpp
dp[n][m/2]=mp[n][m/2];
dp[n][m/2+1]=mp[n][m/2+1];
dp[n][m/2+2]=mp[n][m/2+2];
```
因为刚开始只能吃第n行中间的三个位置
### 不过 要注意**边界**
##### 可以先把每一个都赋值为最小值
```cpp
for(int i=0;i<=n+1;i++)
	for(int j=0;j<=m+1;j++)
		dp[i][j]=-0xfffff;
        //0x就是16进制
        //16进制中的-fffff就是-1048575
```
刚开始本人循环也只是从1到n，1到m没有考虑边界，然后就WA了一个点只拿了90分（那些第9个点WA了的也可以看看是不是边界没考虑）
#### 最后附上AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int dp[210][210];
int mp[210][210];
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin >> mp[i][j];
	for(int i=0;i<=n+1;i++)
        for(int j=0;j<=m+1;j++)
            dp[i][j]=-0xfffff;
	dp[n][m/2]=mp[n][m/2];
	dp[n][m/2+1]=mp[n][m/2+1];
	dp[n][m/2+2]=mp[n][m/2+2];
	for(int i=n-1;i>0;i--)//从倒数第二行开始
		for(int j=1;j<=m;j++)
			dp[i][j]=max(max(dp[i+1][j],dp[i+1][j-1]),dp[i+1][j+1])+mp[i][j];
	int ans=-0xfffff;
	for(int i=1;i<=m;i++)
		if(ans<dp[1][i])ans=dp[1][i];//再查找第1行（吃完）的最大值
	cout << ans;
	return 0;
}
```

---

## 作者：刘曜曜 (赞：2)

大家好，我是曜曜，~~没错就是那个人见人爱，花见花开的曜曜。~~你是不是对待会到来的讲解十分期待与激动呢？我也是的。废话不多说，我们开始吧！


------------

接下来让我们来读题：长为n宽为m的桌子，因为n和m都小于200，所以是可以用一个二位数组来储存的。因为我们要求最大的能量，所以不难想到用dp。   
但是！！！！！！！！！！！！！！！！！！！！！！！！！！
身为一个蒟蒻，本蒟蒻养成了看到dp就逃跑的习惯。
那怎么做呢？——搜索似乎是一个不错的选择。

但是看了这道题的数据，普通的深搜似乎会tle。
怎么办呢？因为这道题的“向前或右前或左前”的搜索很容易出现重复，所以记忆化搜索是不错的。

------------

区别于普通的深搜，记忆化搜索的核心就在于判断这种情况有没有被计算过，如果有，直接return，如果没有，再搜索，这样就大大节省了时间。
代码如下：
```cpp
int dfs(int x,int y)//y代表横坐标，x代表纵坐标
{//dp数组用来储存在坐标为x，y时不算之前吃的东西，最多能获得多少能量，初值为零
//a数组用来储存这个图
    if(dp[x][y]!=0)return dp[x][y];//如果dp数组有非零值，那么可以直接返回这个值
    if(x-1<=0)return 0;//如果不能再走了，就不能再获得了，就返回0
    else if(n==1)dp[x][y]=max(dp[x][y],dfs(x-1,y)+a[x-1][y]);//如果宽度为1，那么一条路走到底
    else if(y-1>=1&&y+1<=n)
    dp[x][y]=max(max(dp[x][y],dfs(x-1,y)+a[x-1][y]),max(dfs(x-1,y+1)+a[x-1][y+1],dfs(x-1,y-1)+a[x-1][y-1]));
    else if(y==1)
    dp[x][y]=max(max(dp[x][y],dfs(x-1,y)+a[x-1][y]),dfs(x-1,y+1)+a[x-1][y+1]);
    else if(y==n)
    dp[x][y]=max(max(dp[x][y],dfs(x-1,y)+a[x-1][y]),dfs(x-1,y-1)+a[x-1][y-1]);
    //三种情况，对应李大水牛在桌子左侧，右侧，中间
    return dp[x][y];
}
```
那么刚开始应该从哪里开始走呢？在桌子下方的中间的下方
则横坐标是n+1除以2，纵坐标是m+1.
那么完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[205][205],dp[205][205];
int dfs(int x,int y)
{
    if(dp[x][y]!=0)return dp[x][y];
    if(x-1<=0)return 0;
    else if(n==1)dp[x][y]=max(dp[x][y],dfs(x-1,y)+a[x-1][y]);
    else if(y-1>=1&&y+1<=n)
    dp[x][y]=max(max(dp[x][y],dfs(x-1,y)+a[x-1][y]),max(dfs(x-1,y+1)+a[x-1][y+1],dfs(x-1,y-1)+a[x-1][y-1]));
    else if(y==1)
    dp[x][y]=max(max(dp[x][y],dfs(x-1,y)+a[x-1][y]),dfs(x-1,y+1)+a[x-1][y+1]);
    else if(y==n)
    dp[x][y]=max(max(dp[x][y],dfs(x-1,y)+a[x-1][y]),dfs(x-1,y-1)+a[x-1][y-1]);
    return dp[x][y];
}
int main()
{
    memset(dp,0,sizeof(dp));//初值为零
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        	scanf("%d",&a[i][j]);//输入，比cin快
    dfs(m+1,(n+1)/2);//开始搜索
    printf("%d",dp[m+1][(n+1)/2]);//输出
    return 0;
}
```
好了，这道题就这样结束了，大家是不是觉得这道题很简单了呢？

那么希望大家能在信息学的道路上越走越远，也希望大家可以多多支持我的题解，我是曜曜，大家再见！


---

## 作者：lemir3 (赞：2)

这道题因为起点在最下面，dp有点麻烦，写ms就好了

每个地方的最优解只来源于他上面的点，左上方的点以及右上方的点，因此dp方程就可以很快得出:

**dp[i,j]=max(dp[i-1,j],dp[i-1,j-1],dp[i-1,j+1])+这个点的值;**

搜到最上面时直接返回这个点值，搜到两边时就去掉会越界的那个路径

具体细节看代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int m,n;
int mapa[210][210];
int dp[210][210];

int ms(int,int);

int main()
{
    for(int i=0;i<=209;i++)
        for(int j=0;j<=209;j++)
            dp[i][j]=-2147483648;
/*这道题求最大值，就赋初值为极小（强烈建议把int的范围背下来:-2147483648~2147483647 记不到也可以用计算器算:-2^31~2^31-1）*/
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&mapa[i][j]);
    printf("%d",ms(m+1,n/2+1));//输出从起点出发的最大值（起点在最后一行中间的下方）
return 0;
}

int ms(int x,int y)
{
    if(dp[x][y]!=-2147483648)return dp[x][y];//ms标准步骤
    if(x==1)return mapa[x][y];//没有东西可吃了qwq
    if(n==1)return max(ms(x-1,y)+mapa[x][y],dp[x][y]);//这里有个坑点,如果数据的n为1，那么就只能沿直线吃，走下面2个分枝都会越界
    if(y==1)return max(ms(x-1,y),ms(x-1,y+1))+mapa[x][y];//如果吃到了最左边，就只能往上或往右吃了
    if(y==n)return max(ms(x-1,y),ms(x-1,y-1))+mapa[x][y];//同理
    return dp[x][y]=max(max(ms(x-1,y),ms(x-1,y-1)),ms(x-1,y+1))+mapa[x][y];//正常情况
}
```

**最后祝大家noip2018 rp++!**

---

## 作者：EarthGiao (赞：1)

## 【思路】
DP    

### 【题目分析】 
一个人从最后一行中间那个点的下方开始    
每一次都吃正前方，左前方和右前方的食物    
求一直吃到第一行能够吃到的最多能量是多少    

### 【初步判断】
一开始是顺着题意想的    
就从李大牛开始的位置开始    
一步一步广搜    
然后针对广搜到的点进行DP     
也就是求出他是从前面哪一个点转移过来的情况最优    
然后发现太麻烦了吧     

### 【转折】
这只是一道黄色的DP题       
应该代码不会超过50行      
为什么要这么麻烦呢？        
~~我不由开始怀疑人生~~      

### 【最终思路】
既然从起点到终点麻烦      
那就从终点到起点吧      
终点就是第一行      
那就成了一个顺序枚举的DP了      
每行每列依次枚举       
比较三个方向上的最优强开进行更新就好了     
最后的结果就是起点能够到达的那三个点里面结构最优的       

## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;
const int Max = 205;
int a[Max][Max];
int f[Max][Max];
bool use[Max][Max];
int x,y;
int M = 0;
int n,m;

int main()
{
	cin >> m >> n;
	memset(a,-999999,sizeof(a));
	for(register int i = 1;i <= m;++ i)
		for(register int j = 1;j <= n;++ j)
			cin >> a[i][j];
	y = (n / 2) + 1;
	x = m + 1;
	for(register int i = 1;i <= m + 1;++ i)
		for(register int j = 1;j <= n + 1;++ j)
			f[i][j] = max(f[i - 1][j],max(f[i - 1][j - 1],f[i - 1][j + 1])) + a[i][j];
	cout << max(f[x - 1][y],max(f[x - 1][y - 1],f[x - 1][y + 1])) << endl;
	return 0;
}
```

---

## 作者：SnowLove (赞：1)

我的方法是从后往前dp，完全模拟吃的过程就OK。

talk is cheap,look my codes:


```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int a[205][205];
int f[205][205];
int Max(int a,int b,int c){     //三者取最大 
    int n;
    if(a>b)n=a;
    else n=b;
    if(n>c)return n;
    return c;
}
int main(){
    int n,m,t,x=0,ans=-99999;
    scanf("%d%d",&n,&m);
    t=m/2+1;                     //从最后一排中间开始吃 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=n;i>=1;i--){
        x++;                        
        if(x>t-1)x=t-1;         //当x>t-1时,就可以从1到m dp
        for(int j=t-x;j<=t+x;j++){      //因为一开始有的地方吃不到，所以不能直接从1到m dp
            f[i][j]=Max(f[i+1][j],f[i+1][j-1],f[i+1][j+1])+a[i][j];   //分别从下，下左，下右吃上去 
        }
    }
    /*for(int i=1;i<=n;i++){            //测试
        for(int j=1;j<=m;j++){
            printf("%d ",f[i][j]);
        }
        printf("\n");
    }*/
    for(int i=1;i<=m;i++){            //第一行的最大值即为答案 
        if(f[1][i]>ans)ans=f[1][i];
    }
    printf("%d\n",ans);
}
```

---

## 作者：ty520 (赞：1)

//我发现c语言的题解一向是特别特别的少 所以来普及一下子

```cpp
//其实就是递推，代码很好写
//每一个点可以由它上方的点，它上方右边和左边的点走到
//所以此点的最大值就是能够走到他的点的最大值加上它自己的值
//至于楼下大佬们说的什么负值问题和能不能到的问题，个人认为是他们开了两个数组
//那个有时候是没必要的
#include<stdio.h>
#include<stdlib.h>
int max(int x,int y){if(x>y) return x;else return y;}
int main(){
    int f[401][401],m,n,maxx;
    int i,j,k;
    scanf("%d %d",&m,&n);
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++){
            scanf("%d",&f[i][j]);
        }
    for(i=2;i<=m+1;i++)
        for(j=1;j<=n;j++){
            f[i][j]=max(f[i-1][j],max(f[i-1][j-1],f[i-1][j+1]))+f[i][j];
            }
    maxx=f[m+1][n/2+1];
    printf("%d",maxx);
    return 0;
}
```

---

## 作者：Thor_Odinson (赞：1)

记忆化搜索，注意x==1的情况

废话不多说，直接上代码

~~哦，对了，为了防止抄代码，蒟蒻标上了行数~~

```cpp
 1 #include<iostream>
 2 #include<cstdio>
 3 #include<cstring>
 4 #include<cmath>
 5 #include<algorithm>
 6 using namespace std;
 7 const int MAXN=233;
 8 void read(int &n)
 9 {
10     char c='+';int x=0;bool flag=0;
11     while(c<'0'||c>'9')
12     {c=getchar();if(c=='-')flag=1;}
13     while(c>='0'&&c<='9')
14     {x=x*10+(c-48);c=getchar();}
15     flag==1?n=-x:n=x;
16 }
17 int n,m;
18 int a[MAXN][MAXN];
19 int dp[MAXN][MAXN];
20 int xx[5]={-1,-1,-1};
21 int yy[5]={-1,0,+1};
22 int M_S(int x,int y)
23 {
24     if(x==1)
25     {
26         if(!dp[x][y])
27             dp[x][y]=a[x][y];
28         return dp[x][y];
29     }
```
30
```cpp
31     if(dp[x][y])
32         return dp[x][y];
33     for(int i=0;i<3;i++)
34     {
35         int wx=x+xx[i];
36         int wy=y+yy[i];
37         if(wx>=1&&wx<=n&&wy>=1&&wy<=m)
38         dp[x][y]=max(dp[x][y],M_S(wx,wy)+a[x][y]);
39     }
40     return dp[x][y];
41 }
42 int main()
43 {
44     read(n);read(m);
45     for(int i=1;i<=n;i++)
46         for(int j=1;j<=m;j++)
47             read(a[i][j]);
48     M_S(n,m/2+1);
49     M_S(n,m/2);
50     M_S(n,m/2+2);
51     int ans=max(max(dp[n][m/2],dp[n][m/2+1]),dp[n][m/2+2]);
52     printf("%d",ans);
53     return 0;
54 }
```

---

## 作者：zz11560 (赞：1)

pascal代码++。

转移方程

        j[a-1,b-1]:=max(j[a-1,b-1],i[a-1,b-1]+j[a,b]);

        j[a-1,b]:=max(j[a-1,b],i[a-1,b]+j[a,b]);

        j[a-1,b+1]:=max(j[a-1,b+1],i[a-1,b+1]+j[a,b]);

j为该单位总得到的能量，

i为该单位食物得到的能量。

上面每步的原因是当前位置的最大值为能到达的当前位置的前个位置最大值+自己位置值。

开始的时候该最小的初始化最小，然后开始动归。

#1 AC1ms/18035kB

#2AC1ms/18035kB

#3AC1ms/18035kB

#4AC0ms/18035kB

#5AC2ms/18035kB

#6AC 3ms/18035kB

#7AC4ms/18035kB

#8AC1ms/18035kB

#9AC7ms/18035kB

#10AC6ms/18035kB

源代码


```cpp
[color=black]代码：[/color][codep ]
var a,b,c,d,n,m:longint;
    i,j:array[-1..1000,-1..1000] of longint;
function max(o,p:longint):longint;
begin
  if o<p then max:=p
   else max:=o;
end;
Begin
  readln(m,n);
  for a:=1 to m do
   for b:=1 to n do
    read(i[a,b]);
  for a:=1 to m+1 do
   for b:=1 to n do
    j[a,b]:=-1000000;
  j[m+1,n div 2+1]:=0;
  for a:=m+1 downto 1 do begin
    for b:=1 to n do
      begin
        j[a-1,b-1]:=max(j[a-1,b-1],i[a-1,b-1]+j[a,b]);
        j[a-1,b]:=max(j[a-1,b],i[a-1,b]+j[a,b]);
        j[a-1,b+1]:=max(j[a-1,b+1],i[a-1,b+1]+j[a,b]);
      end;
    end;
  d:=-1000000;
  for a:=1 to n do if j[1,a]>d then d:=j[1,a];
  writeln(d);
end.
[/codep ]
```

---

## 作者：lf_星辰 (赞：0)

# 动态规划方法
核心语句：st[i][j]+=max(st[i-1][j-1],max(st[i-1][j],st[i-1][j+1]));

末行取中点：
```
	if(n%2==0){//n为偶数时，最后一行能到达n/2,n/2+1（~~题目未要求~~） 
		l=n/2;
		cout<<max(st[m][l],st[m][l+1]);//两数取最大值 
	} 
```
```cpp
	if(n%2==1){//n为奇数时，最后一行能到达n/2-1,n/2,n/2+1
		l=n/2+1; 
		cout<<max(st[m][l-1],max(st[m][l],st[m][l+1]));//三数取最大值
	}
```
### 总代码，呈上：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int st[1010][1010],l,k;
int main(){
	int m,n;
	cin>>m>>n;
	for(int i=1;i<=m;i++ ){
		for(int j=1;j<=n;j++){//二维数组输入 
			cin>>st[i][j];
		}
	}
	for(int i=1;i<=m;i++){//将左、右列赋值成较小数，以便比负数小 
		st[i][0]=-10000000;
		st[i][n+1]=-10000000;
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){//动归，下行数=左上，上，右上，最大数相加 
			st[i][j]+=max(st[i-1][j-1],max(st[i-1][j],st[i-1][j+1]));
		}
	}
	if(n%2==0){//n为偶数时，最后一行能到达n/2,n/2+1（题目未要求） 
		l=n/2;
		cout<<max(st[m][l],st[m][l+1]);//两数取最大值 
	} 
	else if(n%2==1){//n为奇数时，最后一行能到达n/2-1,n/2,n/2+1（题目未要求）
		l=n/2+1; 
		cout<<max(st[m][l-1],max(st[m][l],st[m][l+1]));//三数取最大值
	} 
	return 0;
}
```


---

## 作者：Thomasguo666 (赞：0)

# 蒟蒻的第二篇题解
## 写的不咋地请见谅 
囧rz ○|￣|_

看到各位大佬都巧用初始化memset函数，本蒟蒻来一发特判 ~~万一初始化的不够小呢（本蒟蒻对数据类型的边界不是很清楚）~~

注意:是从输入数据最后一行中间开始吃的，所以我居然~~NC的~~倒着存了起来。

这种情况下的状态转移方程：

dp[i][j]=max(max(dp[i+1][j],dp[i+1][j-1]),dp[i+1][j+1])+a[i][j]


附上AC代码：
```cpp
#include <iostream>
using namespace std;
int dp[300][300],a[300][300];
int main()
{
    int n,m;
    cin>>n>>m;
    for (int i=n;i>=1;i--)
    {
        for (int j=1;j<=m;j++) cin>>a[i][j];
    }
    //倒着存
    for (int j=1;j<=m;j++)
    {
    	dp[n][j]=a[n][j];//初始化
	}
    for (int i=n-1;i>0;i--)
    {
        dp[i][1]=max(dp[i+1][1],dp[i+1][2])+a[i][1];
        dp[i][m]=max(dp[i+1][m],dp[i+1][m-1])+a[i][m];
        //特判
        for (int j=2;j<m;j++)
        {
            dp[i][j]=max(max(dp[i+1][j],dp[i+1][j-1]),dp[i+1][j+1])+a[i][j];//状态转移
        }
    }
    cout<<max(max(dp[1][m/2],dp[1][m/2+1]),dp[1][m/2+2]);//从中间开始吃的，所以只有中间的格子才算
    return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一道题采用DP来做，我觉得从上到下找会比较方便，定义一个f数组，f[i][j]表示第f[i][j]的最大得分。


下面是代码：
```c++
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define MAXX 210
int n,m;
int a[MAXX][MAXX],f[MAXX][MAXX];
inline void Dp() {
	scanf("%d%d",&n,&m);
	int y=m/2+1,x=n;
	memset(a,-63,sizeof(a));//一开始把a数组定义得无限大
	for(int i=1; i<=n; i++)//输入
		for(int j=1; j<=m; j++)
			scanf("%d",&a[i][j]);
	for(int i=1; i<=n; i++)//不断地取最优值，三个方向，记得i-1
		for(int j=1; j<=m; j++)
			f[i][j]=max(max(f[i-1][j],f[i-1][j-1]),f[i-1][j+1])+a[i][j];
	printf("%d\n",max(max(f[x][y],f[x][y-1]),f[x][y+1]));
}
int main() {
	Dp();
	return 0;
}
```

---

## 作者：瑞星 (赞：0)

这题我认为其实并不是完全的多维动态规划。
其实只是一个矩形的数塔问题。
用一样的方法解不一样的题即可。

那么？怎么解？
动态规划三要素：阶段、状态、决策。
那么这题的三要素就是：
阶段：矩形中每一个点。
状态：到当前这个点的最大能量（最优解）。
决策：从三步中选一步走到下一个新状态。
三要素明确完毕，即可开始写题。

我的代码都注释很详细了，有些细节大家需注意。

```cpp
#include<iostream>

using namespace std;

int n,m;				//m行n列
int map[1001][1001];	//存图
int f[1001][1001];	  //设计状态f[i][j]表示在此坐标时的最大值
int ans=-1;			 //答案

int main()
{
	//freopen("temp.in","r",stdin);
	//freopen("temp.out","w",stdout);

	//1:输入并初始化
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>map[i][j];
			f[i][j]=map[i][j];	//存图的时候就开始初始化f数组
		}
			
	//2:计算
	//状态转移方程f[i][j]=max(f[i][j],f[i+1][k]) (k为j-1到j+1 && 不越界)
	for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
			f[i][j]=max(f[i-1][j-1],max(f[i-1][j],f[i-1][j+1]))+map[i][j];	//这里一定要加上此位置的原值，否则更新将出错
		
	//3:输出
	for(int i=(n+1)/2-1;i<=(n+1)/2+1;i++)
		ans=max(ans,f[m][i]);	//因为大水牛在(最后一行+1)行中间位置的下方，所以只从最后一行的中间三个位置找最大值
	cout<<ans;
	return 0;
    
    /**
    	总体来说，很简单的一道dp。
        我就不再多做解释了。
    */
}

```

---

## 作者：Lyrics (赞：0)

类似于求最大值的或最小值的可以考虑DP

李大水牛既然爱从下往上吃，我们就可以考虑从上往下吃（逆向思维，倒推法）

因为每次只会吃自己前方或左前方或右前方的食物，所以我们的第一行的f初始化为a；

而且需要注意的是我们要初始化全部的f为一个特别小的数（要负的，因为样例给的有负的）

所以我们用memset(f,-0x3f,sizeof f)这样把数组f初始化成一个特别小的负数就可以了

其他的就是2维背包，和IOI1999数塔问题有点像可以看看。

然后这题的DP方程很好写，就是： f[i][j]=max(f[i-1][j],max(f[i-1][j-1],f[i-1][j+1]))+a[i][j];

剩下的代码完成比较简单，见下面的CODE。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[205][205],f[205][205],n,m;
namespace qaq{
    int main(){
        memset(f,-0x3f,sizeof f);
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++)f[1][i]=a[1][i];
        for(int i=2;i<=m;i++)
            for(int j=1;j<=n;j++){
                f[i][j]=max(f[i-1][j],max(f[i-1][j-1],f[i-1][j+1]))+a[i][j];
            }
        printf("%d\n",max(f[m][n/2+1],max(f[m][n/2],f[m][n/2+2])));
        return 0;
    }
}
int main(){
    qaq::main();
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

#蒟蒻的题解

思路:记忆化搜索

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <map>
using namespace std;

using int_t = signed long long int;
//矩阵的行数，列数
int_t yMax, xMax;
//矩阵
int_t matrix[202][202] = {0};
//要实现记忆化搜索，保存之前的搜索结果
//memory[x][y][已经得到的能量值]

map<int_t, int_t> memory[201][201];
//搜索函数
//x:当前x
//y:当前y
//v:已获得的能量
int_t search(int_t x, int_t y, int_t v) {
    if (memory[x][y].find(v) != memory[x][y].end()) return memory[x][y][v];
    int_t v1 = 0, v2 = 0, v3 = 0;
    //判断是否可以向左上走
    if (x != 1 && y != 1) {
        v1 = search(x - 1, y - 1, v) + matrix[x - 1][y - 1];
    }
    //判断是否可以向上走
    if (y != 1) {
        v2 = search(x, y - 1, v) + matrix[x][y - 1];
    }
    //判断是否可以向右上走
    if (x != xMax && y != 1) {
        v3 = search(x + 1, y - 1, v) + matrix[x + 1][y - 1];
    }
    //找到最大值
    int_t result = max(max(v1, v2), v3);
    //保存结果
    memory[x][y][v] = v + result;
    return v + result;


}

int main() {
    cin >> yMax>>xMax;
    for (int i = 1; i <= yMax; i++)
        for (int j = 1; j <= xMax; j++)
            cin >> matrix[j][i];
    cout << search(xMax / 2 + 1, yMax + 1, 0);
}
```

---

## 作者：Xiao_Ling (赞：0)

###这题我认为是个dp

###因为一开始有个位置条件，所以会有一些点是到达不了的

###所以我们先进行**预处理**，让他们不会影响到结果

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int m,n,ans=0;
int a[210][210]={0},f[210][210]={0};//数组一般要比数据范围大一点以防爆炸 
int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]); 
    int u=3,p=m;
    while(u<n)//这里是预处理，用u来控制 ，u即是李大水牛所能吃到的位置，因为一开始在中间，能吃左右前，故u=3 
    {
        int o=(n-u)/2,i=(n+u)/2+1;
        //画图可知他不能吃到的位置的起点（从中间向两边赋值为0，避免影响） 
        while(i<=n) a[p][i]=0,i++;
        while(o>0)     a[p][o]=0,o--;
        p--;//这里是控制层数，因为我是从下至上来进行预处理的（我觉得方便一点,,,,) 
        u+=2;//每一次都吃边上的话，可吃的地方向两边延伸1格，当u不再小于n时，说明以后的格子他都能吃到 
    }
    for(int i=m;i>0;i--)//dp时间 
        for(int j=n;j>0;j--)//这里不能为j=n-1，因为当n=1时无法dp，，（血的教训，，） 
            {
                int mx=-1;
                //由下至上的推，最终可得最大能量 
                mx=max(mx,a[i][j]+f[i+1][j-1]);//左 
                mx=max(mx,a[i][j]+f[i+1][j]);//前 
                mx=max(mx,a[i][j]+f[i+1][j+1]);//右 
                f[i][j]+=mx;
            }
    for(int i=1;i<=n;i++)    ans=max(f[1][i],ans);//搜索最大能量 
    cout<<ans;
    return 0;
}
```

---

## 作者：1v7w (赞：0)



    
    
    
    
```cpp
#include <cstdio>
#include <algorithm>
long long f[210][210];
long long map[210][210];
int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            scanf("%lld", &map[i][j]);
        }
    }
    // 在移动过程中有些点是无法到达的
    // 把这些点全部都设置为0
    // i>m-((n-3)/2)     在某行就全部能到达了
    // j<n/2+1-(m-i+1)    表示i行能到达的最左端
    // j>n/2+1+(m-i+1)    表示i行能到达的最左端
    for(int i=m; i>=m-((n-3)/2); i--)
    {
        //第i行从最左边到 这一行能到达的最左边都设置为0
        for(int j=1; j<n/2+1-(m-i+1); j++)
            map[i][j] = 0;
        //第i行从最右边到 这一行能到达的最右边都设置为0
        for(int j=n; j>n/2+1+(m-i+1); j--)
            map[i][j] = 0;
    }
    //把到达餐桌另一端的f都求出来
    for(int i=m; i>=1; i--)
    {
        for(int j=1; j<=n; j++)
        {
            // 左下方
            f[i][j] = std::max(f[i][j], f[i+1][j-1]);
            // 下方
            f[i][j] = std::max(f[i][j], f[i+1][j]);
            // 右下方
            f[i][j] = std::max(f[i][j], f[i+1][j+1]);
            f[i][j] += map[i][j];
        }
    }
    //求最大f
    long long maxx = 0;
    for(int i=1; i<=m; i++)
            if(maxx < f[1][i])
                maxx = f[1][i];
    printf("%lld", maxx);
    return 0;
}
```

---

## 作者：geek痕 (赞：0)

应该说这和很多人曾经学动态规划的那道求累加和最大的题类似，但不同的是，这道题目中起点不是固定的，要根据输入算出。

然后是审题。注意这一句“而自己正处在这个大餐桌的一侧的中点下边”以及“只吃自己前方或左前方或右前方的盘中的食物”。

换句话说，如果从起点来看的话，起点的可选项应该有三个，而不是一个。

分别是最后一行中点的左一格，中点，以及中点的右一格。

代码简单就不用注释了吧。










```cpp
#include <iostream>
using namespace std;
int powera[205][205];
int dp[205][205];
int main() {
#ifdef LOCAL
    freopen("test.in","r",stdin);
#endif
    int y,x;
    cin>>y>>x;
    for(int ynow=1; ynow<=y; ynow++) {
        for(int xnow=1; xnow<=x; xnow++) {
            cin>>powera[xnow][ynow];
        }
    }
    for(int ynow=1; ynow<=y; ynow++) {
        for(int xnow=1; xnow<=x; xnow++) {
            for(int i=-1; i<=1; i++) {
                dp[xnow][ynow]=max(dp[xnow][ynow],dp[xnow+i][ynow-1]+powera[xnow][ynow]);
            }
        }
    }
    int ans=0;
    for(int i=(x+1)/2-1; i<=(x+1)/2+1; i++) {
        ans=max(ans,dp[i][y]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Phoenix_Zenghao (赞：0)

一开始没怎么想，以为就是背包型的dp。

做着做着发现，实际就是一个二维的dp背包。

dp【i】【j】表示横纵坐标。由下至上来优化得到answer。

最后在第一排再扫一遍即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200+50;
int n,m,a[maxn][maxn],dp[maxn][maxn];
int main()
{
    memset(dp,-0x3f3f3f3f,sizeof(dp));//因为有负数。
    cin>>m>>n;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
        }
    }
    dp[m+1][n/2+1]=0;//初始化
    for(int i=m;i>=1;i--)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=max(dp[i+1][j]+a[i][j],dp[i+1][j-1]+a[i][j]);
            dp[i][j]=max(dp[i][j],dp[i+1][j+1]+a[i][j]);//从下，从左下，从右下。
        }
    }
    int tot=-0x3f3f3f3f;
    for(int i=1;i<=n;i++)
    tot=max(tot,dp[1][i]);
    cout<<tot<<endl;
    return 0;
}
```

---

## 作者：Nibelungen (赞：0)

##DP，可以参照紫书p270。思路下面的题解都写得很清晰。我错在最后的答案d[m][n/2]写成了n/2+1因为数组是从0开始的。

   
    
    

```cpp
#include<cstdio>
#include<algorithm>
#define maxn 1000
using namespace std;
int n,m,board[maxn][maxn],vis[maxn][maxn];
int main(){
    scanf("%d%d",&m,&n);
 for(int a=0;a<m;a++)
    for(int b=0;b<n;b++)
    scanf("%d",&board[a][b]);
 for(int a=0;a<n;a++)  //初始化，在下面的循环有用，其实也可以省略这一步
    vis[0][a]=board[0][a];
for(int a=1;a<=m;a++)  //因为上一步在第0排已经初始化所以可以从1开始了
 for(int b=0;b<n;b++){
        int move[3]={b-1,b,b+1};    //左前，前方，右前
        if(move[0]<0) move[0]=0;  //如果越界
        if(move[2]>=n) move[2]=n-1;
        for(int z=0;z<3;z++)
        vis[a][b]=max(vis[a][b],vis[a-1][move[z]]+board[a][b]); //重点！需要自己体会
    }
    printf("%d",vis[m][n/2]);
}
```

---

## 作者：hicc0305 (赞：0)

一道简单的矩阵dp题目，用dp[i][j]存储到i，j这个点的最大值，从下到上递推出第一列的最大值，在比较一下就可以了


转移方程见程序，注意一些地方是死角，走不到，不用加进去。（PS：不知为什么数组开201,201过不了……多开一点才过）


```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int a[401][401];
int dp[401][401];
int main()
{
    memset(a,0,sizeof(a));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    for(int i=m+1;i>=2;i--)//从最后一行的下一列开始
    {
        int l=n/2+1-(m-i+1),r=n/2+1+(m-i+1);//要枚举j左右值，也就把走不到的地方排出了
        for(int j=max(l,1);j<=min(r,n);j++)
        {
            dp[i-1][j-1]=max(dp[i-1][j-1],dp[i][j]+a[i-1][j-1]);
            dp[i-1][j]=max(dp[i-1][j],dp[i][j]+a[i-1][j]);
            dp[i-1][j+1]=max(dp[i-1][j+1],dp[i][j]+a[i-1][j+1]);//转移方程，可能有点麻烦，但不用脑子
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[1][i]);//比较求最值
    printf("%d",ans);
    return 0;
}
```

---

## 作者：qaqRose (赞：0)

非常简短的代码，应该也很好理解

题目是从下边的中间开始向上，寻找一条最大能量的路径，每次只找左上、上、右上三个方向

所以我们可以从第二行开始向下递推，每次讲左上、上、右上中能量最大传递下来，

这样m+1行的中间就相当于保存一条从底中间向上的一条最大能量路径


```cpp
#include<iostream>
using namespace std;
int m,n;
int a[210][210];
int main(){
    freopen("2.txt","r",stdin);
    cin>>m>>n;
    for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
    cin>>a[i][j]; 
    for(int i=2;i<=m+1;i++)    //从第二行开始   到m+1行 
    for(int j=1;j<=n;j++){
        int t=max(a[i-1][j-1],a[i-1][j]);  //求出左上 上 右上 三个食物的最大能量 
        a[i][j] +=max(t,a[i-1][j+1]);       //加上并保存       
    }                                    // 从上往下递推 即可求出最大能量 
    cout<<a[m+1][n/2+1]; // 注意 结果保存在m+1行的中间  下标从1开始 所以是 n/2+1
    return 0;
} 
```

---

## 作者：耗纸大大 (赞：0)

```cpp
#include<iostream>
#include<cstring>
#define finf -0x7f    //初始化用的。也可以用const int finf=-0x7f
#define sph 210      //我最讨厌用啥maxn，maxm的缩写了。。然后我就打上了自己的缩写。。
using namespace std;
int n,m,x,y,maxl;
int dp[sph][sph];      //储存每一步的最优值
int map[sph][sph];  //用来输入数值
int main()
{
    cin>>m>>n;
    memset(map,finf,sizeof(map));
    for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
      cin>>map[i][j];
    for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
     dp[i][j]=max(max(dp[i-1][j],dp[i-1][j-1]),dp[i-1][j+1])+map[i][j];  //状态转移方程。这里就不写了，它的来就是，每一步都是下面三个然后，找最优的。。
     y=n/2+1;x=m;        //推到最后的值附近。
    for(int i=-1;i<2;i++) if(maxl<dp[x][y+i]) maxl=dp[x][y+i];  //根据状态转移方程可知最后的答案就在李xx的附近。
    cout<<maxl<<endl;
}
```

---

## 作者：Tmistra (赞：0)

# 可以从上往下递推，最后输出最下面那行中间三个的最大值

## 递推式 a[i,j]:=max(a[i,j]+a[i-1,j],a[i,j]+a[i-1,j-1],a[i,j]+a[i-1,j+1]);

```cpp
Program xxx;
var
    n,m,i,j:longint;
    a:array[0..201,0..201] of longint;//存放矩阵
function max(a,b,c:longint):longint;//取三者最大值
begin
    if (c>b) and (c>a) then exit(c);
    if (a>b) and (a>c) then exit(a);
    if (b>a) and (b>c) then exit(b);
end;
begin
    readln(n,m);
    for i:=1 to n do begin
        for j:=1 to m do
            read(a[i,j]);
        readln;
    end;//读入数据
    for i:=2 to n do
        for j:=1 to m do
            a[i,j]:=max(a[i,j]+a[i-1,j],a[i,j]+a[i-1,j-1],a[i,j]+a[i-1,j+1]);//递推
    writeln(max(a[n,(m+1) div 2],a[n,(m+1) div 2+1],a[n,(m+1) div 2-1]));//输出最大值
end.
```

---

## 作者：桑梓暖阳 (赞：0)

看楼下没有记忆化，补上一个

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int m ,n;
int f[201][201],a[201][201];
void dfs(int x,int y){
    if(x==1){ f[x][y]=a[x][y]; return; }
    if(f[x][y]!=0) return;
    for(int i=-1;i<=1;i++)
        if(y+i>=1&&y+i<=n){
            dfs(x-1,y+i); 
            f[x][y]=max(f[x][y],f[x-1][y+i]+a[x][y]);
        }  
}
int main(){
    //freopen("1508.in","r",stdin);
//    freopen("1508.out","w",stdout);
    scanf("%d%d",&m ,&n);
    for(int i=1;i<=m ;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    dfs(m ,n/2+1);
    dfs(m,n/2);
    dfs(m,n/2+2);
    int ans=max(max(f[m ][n/2],f[m ][n/2+1]),f[m ][n/2+2]);
    printf("%d",ans);
    return 0;
}

```

---

## 作者：yyy2015c01 (赞：0)

倒着想。。

最后一行中点下方开始走，就是最后一行中点附近三个数(f[m][n/2±1])任选一个开始。

从最后一行中点附近三个数任选一个开始乱走一通走到第一行的最大和，和从第一行任意一个地方开始乱走一通走到最后一行中点附近三个数的最大和，结果是相同的。

这就好想多了。

PS：别管什么走到不走到！

AC代码：

```cpp
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <cctype>
using namespace std;
int table[202][202]={0};
int f[202][202]={0};
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    for (int i=1;i<=m;i++) {
        for (int j=1;j<=n;j++) {
            scanf("%d",&table[i][j]);
        }
    }
    for (int i=1;i<=n;i++) {
        f[1][i]=table[1][i]; 
    } 
    for (int i=2;i<=m;i++) {
        for (int j=1;j<=n;j++) {
            f[i][j]=max(f[i-1][j-1],max(f[i-1][j],f[i-1][j+1]))+table[i][j];
        }
    }
    int _max=INT_MIN;
    for (int i=n/2;i<=n/2+2;i++) {
        _max=max(f[m][i],_max);
    }
    printf("%d",_max);
    return 0;
}
```

---

## 作者：chaijing (赞：0)

来吧。。好久没水过题解了。。来一发短小精干的C++代码。

这道题和经典的数字金字塔一模一样。从吃的最后一行（即输入的第一行）往吃的第一行（即输入的最后一行）的方向推。

其实这道题压根不用判断什么吃不吃得到。DP完之后在吃的那行的中间三个数即为最优解。真正进行DP时那些吃不到的地方对结果无影响。

俗话说知识越多越反动。之前我判断过一次能否吃得到，结果90分。

```cpp
//P1508 Likecloud-吃、吃、吃
#include<iostream>
using namespace std;
int f[202][202],a[202][202];  //f（i.j）表示从坐标i，j一直往后吃所能吃到的最大值
int main()
{
    int n,m,i,j,t,k=0;
    cin>>n>>m;
    t=m/2+1;   //中间位置纵坐标
    for(i=1;i<=n;i++)
      for(j=1;j<=m;j++)
        cin>>a[i][j];   //输入啦
    for(j=1;j<=m;j++) f[1][j]=a[1][j];  //初始化第一行
    for(i=2;i<=n;i++)
      for(j=1;j<=m;j++)
        f[i][j]=max(f[i-1][j-1],max(f[i-1][j],f[i-1][j+1]))+a[i][j];  //三种情况哦：左上，上，右上。注意最后还要加上本身
    for(i=t-1;i<=t+1;i++)
      if(f[n][i]>k) k=f[n][i];   //找出最后一行中间三个数的最大值
    cout<<k<<endl;
    return 0;
}
```

---

## 作者：Neil1110 (赞：0)

直接用一个深搜就能ac的，数组是从0开的，所以从（m, n/2）这个位置开始，

向上深搜，每次尝试左上、右上、正上三个位置。


**注意几个地方：**

**1. 从最后一行的下面开始，不是最后一行。**

**2. 去过的地方存一下，不然可能会TLE。**

**3. 边界是到了第一行，即x==0。**

**4. 分类处理一下最后一列和第一列的情况。**


似乎不需要优化就能ac的。


```cpp

#include<iostream>
using namespace std;
const int maxn=210;
int n,m;
int map[maxn][maxn],dp[maxn][maxn];
int dp1(int x,int y)
{
    if(x==0)
        return map[x][y];
    if(dp[x][y]!=-2147483647)
        return dp[x][y];
    else
    {
        if(y==n-1)
            return dp[x][y]=max(dp1(x-1,y-1),dp1(x-1,y))+map[x][y];
        else if(y==0)
            return dp[x][y]=max(dp1(x-1,y+1),dp1(x-1,y))+map[x][y];
        else
            return dp[x][y]=max(max(dp1(x-1,y-1),dp1(x-1,y+1)),dp1(x-1,y))+map[x][y];
    }
}
int main()
{
    int i,j;
    cin>>m>>n;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            cin>>map[i][j];
            dp[i][j]=-2147483647;
        }
    dp[m][n/2]=-2147483647;
    cout<<dp1(m,n/2)<<endl;
    return 0;
}

```

---

## 作者：cbx8888 (赞：0)

这道题是很基础的动态规划（我呸。。。这不就是个贪心）

这个人从最后一行的下方，也就是第n+1行的m/2+1开始（向上）走

定义f[i][j]为当前在i行j列，能取得的最大能量


当他（它？）在第i行j列的时候，能走到第i-1行的j、j-1、j+1的位置（这样思考可以正推）

这道题其实正推（枚举已知状态推出位置状态）比较方便（等下回说方便在哪），主要是不用考虑推出去的


状态是否存在——能推出去怎么会不存在呢？自己yy一下

所以在这种情况下，只要考虑边界就行

由此得出转移方程（说实话这种方法没试过。。。大家可以去尝试下）


f[i-1][j]=max(f[i][j]+a[i-1][j],f[i-1][j])

f[i-1][j+1]=max(f[i][j]+a[i-1][j+1],f[i-1][j+1])

f[i-1][j-1]=max(f[i][j]+a[i-1][j-1],f[i-1][j-1])

但是如果按照我们动规的一般思路，是枚举未知状态i，j然后由i+1行的已知状态来求（我用的是这种）

和上面的正推一样，当这个人在第i行j列的时候，能够从第i+1行的j、j-1，j+1的位置走过来

这个时候就要考虑一个问题，上一行的这三个状态是否存在呢？

T T T T T T T

F T T T T T F

F F T T T F F

S
比如像n=3，m=7时，T表示状态存在，F表示状态不存在，S是出发点

转移的时候一定要注意上一个状态是否存在，然后还要注意边界。。。

注意：判断状态是否存在的时候，你可以拿j与m/2+1的差的绝对值与n-i+1比较一下

如果比n-i+1大，就不存在了，但是这种方法在表示[i+1][j-1],[i+1][j+1]的时候就比较麻烦了

写起来很容易出错。。。

但是下面的这份代码就用简单粗暴的方法解决了这个问题（增加的时空复杂度倍数控制在很小的常数级别）


AC代码君，上吧！

```cpp
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<math.h>
using namespace std;
int i,j,k,n,m,ans;
int a[205][205],f[205][205];
bool p[205][205];
int dfs(int x,int y)
{
    p[x][y]=true;//标记为存在
    if(x==1) return 0;//到了第一行
    if((p[x-1][y-1]==false)&&(y>1)) dfs(x-1,y-1);//注意边界
    if(p[x-1][y]==false) dfs(x-1,y);
    if((p[x-1][y+1]==false)&&(y<m)) dfs(x-1,y+1);//注意边界
    return 0;
}
int main()
{
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    k=m/2+1;
    memset(p,false,sizeof(p));//p数组表示了所有的状态是否存在,初始化
    dfs(n+1,k);//暴力灌水floodfill
    for(i=n;i>=1;i--)//从第n行推到第1行
        for(j=1;j<=m;j++)
        {
            if(p[i][j]==false) continue;//判断状态是否存在
            f[i][j]=max(f[i][j],f[i+1][j]);//这边不用判断。。为什么自己想
            if(p[i+1][j-1]==true) f[i][j]=max(f[i][j],f[i+1][j-1]);//判断状态是否存在
            if(p[i+1][j+1]==true) f[i][j]=max(f[i][j],f[i+1][j+1]);//判断状态是否存在
            f[i][j]+=a[i][j];
        }
    for(i=1;i<=m;i++)
        ans=max(ans,f[1][i]);//从第一行所有状态中取最大值
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：hfctf0210 (赞：0)

动态规划初步练手题！但要注意不少细节

```cpp
#include<iostream>
using namespace std;
int n,m,a[201][201],f[202][201];
int maxd(int a,int b,int c)//计算3个数的最大值
{
    if(a>b&&a>c)return a;
    if(b>c)return b;
    return c;
}
int main()
{
    int i,j,max1=-2147483647,t=0,mid;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    cin>>a[i][j];
    if(m==1)
    {
        int s=0;
        for(i=1;i<=n;i++)
        s+=a[i][1];
        cout<<s;
        return 0;
    }
    mid=m+1>>1;
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    f[i][j]=-2147483647;//初始化价值为-∞
    for(i=n;i>=1;i--)//从下往上搜索
    {
        t++;
        for(j=max(0,mid-t);j<=min(m,mid+t);j++)//注意不能越界
        f[i][j]=maxd(f[i+1][j-1],f[i+1][j],f[i+1][j+1])+a[i][j];
    }
    for(j=max(0,mid-t);j<=min(m,mid+t);j++)//没用的不搜索了，否则可能会影响结果
    max1=max(max1,f[1][j]);
    cout<<max1;
}
```

---

## 作者：plazum (赞：0)

类似于P1216数字金字塔，这里的方法基本上就是P1216的题解中Okami同学给出的思路……

http://www.luogu.org/wiki/show?name=%E9%A2%98%E8%A7%A3+P1216

注意只有一列的情况……

```cpp

#include<stdio.h>
int m,n,i,j,a[200][200];
#define MAX(a,b) ((a)>(b)?(a):(b))
int main()
{
    for(scanf("%d%d",&m,&n);i<m;i++)for(j=0;j<n;j++)scanf("%d",a[i]+j);
    if(n==1){
        for(i=j=0;i<m;i++)j+=*a[i];
        printf("%d",j);
        return 0;
    }
    for(i=1;i<m;i++){
        *a[i]+=MAX(*a[i-1],a[i-1][1]);
        for(j=1;j<n-1;j++)a[i][j]+=MAX(MAX(a[i-1][j-1],a[i-1][j]),a[i-1][j+1]);
        a[i][n-1]+=MAX(a[i-1][n-2],a[i-1][n-1]);
    }
    printf("%d",MAX(MAX(a[m-1][n/2-1],a[m-1][n/2]),a[m-1][n/2+1]));
    
    return 0;
}

```

---

## 作者：darkfire3133 (赞：0)


1 1 1 1 1 1 1 1 1

1 1 1 1 1 1 1 1 1

1 1 1 1 1 1 1 1 1

0 1 1 1 1 1 1 1 0

0 0 1 1 1 1 1 0 0

0 0 0 1 1 1 0 0 0

X

如图，X是起始点，1是能吃到的，[color=red]注意0是吃不到的[/color]，不要把在0位置的点算进去。


观察上图，可以看出[color=red]当i==n时只有中间三个点可以走到，i每减一，可以到达的点数+2，而且是在第i行的基础上左右各加一[/color]。

用f[i][j]表示到(i,j)时食物可以提供的最大能量，由此得

```cpp

for(int i=n-1;i>=1;i--)
    for(int j=1;j<=m;j++)
    {
        if(j<=m/2-1-(n-i) || j>=m/2+3+(n-i))
            continue;
        dp[i][j]=table[i][j]+max(dp[i+1][j-1],dp[i+1][j],dp[i+1][j+1]);//方程
    }

```

我的代码：


```cpp

/*For the Alliance!!!*/
#include<iostream>
#include<cstring>
using namespace std;
int table[202][202];
int dp[202][202];
int max(int a,int b,int c)
{
    if(a<b)
        a=b;
    if(a<c)
        a=c;
    return a;
}
int main()
{
    memset(dp,0,sizeof(dp));
    int m,n,ans=-65536;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>table[i][j];
    dp[n][m/2]=table[n][m/2];
    dp[n][m/2+1]=table[n][m/2+1];
    dp[n][m/2+2]=table[n][m/2+2];
    for(int i=n-1;i>=1;i--)
        for(int j=1;j<=m;j++)
        {
            if(j<=m/2-1-(n-i) || j>=m/2+3+(n-i))
                continue;
            dp[i][j]=table[i][j]+max(dp[i+1][j-1],dp[i+1][j],dp[i+1][j+1]);
        }
    for(int i=1;i<=n;i++)
        if(dp[1][i]>ans)
            ans=dp[1][i];
    cout<<ans<<endl;
    return 0;
}

<hr>
```

---

## 作者：Ing1024 (赞：0)

### 蒟蒻写的题解水平不高，还望各位大佬多多批评指教
这道题因为李大水牛只能走到他左上、右上和上方的点，所以很容易就可以得出状态转移方程:

dp[i][j]=max{dp[i+1][j],dp[i+1][j+1],dp[i+1][j-1]}

其实在李大水牛走的过程中，有一些点是走不到的，所以我们可以略微剪下枝
~~（好吧其实也减不了多少）~~
~~算了我的语文太差~~，

还是直接上代码吧
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[201][201],dp[201][201];
bool b[201][201];
int main()
{
	int m,n,i,j;
	cin>>m>>n;
	for(i=1;i<=m;i++)
	for(j=1;j<=n;j++) 
	{
		cin>>a[i][j];
		dp[i][j]=0;
	}
	for(i=n/2;i<=n/2+2;i++) b[m][i]=true;
	for(i=1;i<=n;i++) dp[m][i]=a[m][i];
	for(i=m-1;i>=1;i--)
	{
		for(j=1;j<=n;j++)
		{
			if(!b[i+1][j]&&!b[i+1][j-1]&&!b[i+1][j+1]) {b[i][j]=false; continue;}//判断该点能否走到 
			if(b[i+1][j]) {dp[i][j]=max(dp[i+1][j],dp[i][j]);b[i][j]=true;} 
			if(b[i+1][j+1]){dp[i][j]=max(dp[i+1][j+1],dp[i][j]);b[i][j]=true;}     //状态转移 
	 		if(b[i+1][j-1]) {dp[i][j]=max(dp[i+1][j-1],dp[i][j]);b[i][j]=true;}
			dp[i][j]=dp[i][j]+a[i][j];	
		}
	}
	int ans=0;
	for(i=1;i<=n;i++) if(b[1][i])ans=max(ans,dp[1][i]);//取底部能走到的最大值 
	cout<<ans<<endl; 
	return 0;
}
```
之前没有用Markdown，修改了一下。


---

