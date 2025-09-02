# [CCC 2023 J5] CCC Word Hunt

## 题目描述

在 CCC 单词搜索游戏中，单词隐藏在一个字母网格中。隐藏单词的字母总是以顺序出现在水平、垂直或对角线段上，有两种方式。一种方式是单词的字母出现在一条线段上。另一种方式是单词的字母出现在一条线段上直到某个字母，然后在该字母处形成直角的第二条线段上。给定一个字母网格和一个要搜索的单词，你的任务是确定该特定单词在网格中隐藏的次数。

## 说明/提示

**本题采用捆绑测试**。

- 子任务 $1$（$2$ 分）：隐藏字符串一定在一条水平线段上。
- 子任务 $2$（$2$ 分）：隐藏字符串一定在一个水平或垂直线段上。
- 子任务 $3$（$2$ 分）：隐藏字符串一定在一个水平、垂直或对角线段上。
- 子任务 $4$（$9$ 分）：隐藏字符串一定在一个线段或两个互相垂直的线段上。

样例 $1$ 图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/wqo2un8k.png)

样例 $2$ 图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/v082p2qr.png)

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
MENU
5
7
F T R U B L K
P M N A X C U
A E R C N E O
M N E U A R M
M U N E M N S```

### 输出

```
3```

## 样例 #2

### 输入

```
NATURE
6
9
N A T S F E G Q N
S A I B M R H F A
C F T J C U C L T
K B H U P T A N U
D P R R R J D I R
I E E K M E G B E```

### 输出

```
4```

# 题解

## 作者：Lemonlwl (赞：6)

## P9303 [CCC 2023 J5] CCC Word Hunt 题解
### 题意：
对于给定字符串 $W$，你需要在给定的矩阵中找到它。

------------

### 分析：
查找方式一共有三种：

1. 水平或垂直查找。
1. 沿对角线查找。
1. 在以上查找过程中进行 $90$ 度翻折（只能翻折一次）查找。

------------

### 思路：
本题是显而易见的深搜题，因此我们可以用三个函数分别进行三种查找方式的调用，则第三种查找我们可以在前两个查找过程中调用。

1. 函数 ```dfs1``` 为垂直或水平搜索，在每一个位置判断：若方向翻折 $90$ 度后的下一个字符与字符串的下一个字符相同则沿该方向翻折，使用 ```dfs3``` 继续搜索。

1. 函数 ```dfs2``` 为对角线搜索，在每一个位置判断：若方向翻折 $90$ 度后的下一个字符与字符串的下一个字符相同则沿该方向翻折，使用 ```dfs3``` 继续搜索。

1. 函数 ```dfs3``` 为翻折方向搜索，在每一个位置判断：若下一个字符与字符串的下一个字符相同则继续搜索。

**注：在 $d$ 等于 $0$ 时，即第一个字符时不能翻折。**

------------

附上 [AC](https://www.luogu.com.cn/record/112259751) 代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string w;
int r,c,sum,len;
char a[105][105];
int x1[4]={-1,0,1,0};
int y1[4]={0,-1,0,1};
//水平与垂直方向。
int x2[4]={-1,1,1,-1};
int y2[4]={-1,-1,1,1};
//对角线方向。
void dfs3(int x,int y,int d,int dire,int flag){  //中途翻折方向，继续搜索。
	if(d==len-1){   //查到最后一个位置结束，下同。
		sum++;
		return;
	}
	if(flag==1){   //从水平或垂直方向翻折。
		int vx=x+x1[dire];
		int vy=y+y1[dire];
		//这里的dire是翻折过的方向，下同。
		if(vx>=1 && vy>=1 && vx<=r && vy<=c && a[vx][vy]==w[d+1]){
			dfs3(vx,vy,d+1,dire,1);
		}
	}
	if(flag==2){   //从对角线方向翻折。
		int vx=x+x2[dire];
		int vy=y+y2[dire];
		if(vx>=1 && vy>=1 && vx<=r && vy<=c && a[vx][vy]==w[d+1]){
			dfs3(vx,vy,d+1,dire,2);
		}
	}
}
void dfs1(int x,int y,int d,int dire){ //水平或垂直方向搜索。
	if(d==len-1){
		sum++;
		return;
	}
	int vx=x+x1[dire];
	int vy=y+y1[dire];
	if(vx>=1 && vy>=1 && vx<=r && vy<=c && a[vx][vy]==w[d+1]){
		dfs1(vx,vy,d+1,dire);
	}
	//翻折方向。
	int ax=x+x1[(dire+1)%4];
	int ay=y+y1[(dire+1)%4];
	//翻折向左。
	int bx=x+x1[(dire+3)%4];
	int by=y+y1[(dire+3)%4];
	//翻折向右。
	//中途翻折。
	if(d>0 && ax>=1 && ay>=1 && ax<=r && ay<=c && a[ax][ay]==w[d+1]){
		dfs3(ax,ay,d+1,(dire+1)%4,1);
	}
	if(d>0 && bx>=1 && by>=1 && bx<=r && by<=c && a[bx][by]==w[d+1]){
		dfs3(bx,by,d+1,(dire+3)%4,1);
	}
}
void dfs2(int x,int y,int d,int dire){ //对角线方向搜索。
	if(d==len-1){
		sum++;
		return;
	}
	int vx=x+x2[dire];
	int vy=y+y2[dire];
	if(vx>=1 && vy>=1 && vx<=r && vy<=c && a[vx][vy]==w[d+1]){
		dfs2(vx,vy,d+1,dire);
	}
	//翻折方向。
	int ax=x+x2[(dire+1)%4];
	int ay=y+y2[(dire+1)%4];
	//翻折向左。
	int bx=x+x2[(dire+3)%4];
	int by=y+y2[(dire+3)%4];
	//翻折向右。
	//中途翻折。
	if(d>0 && ax>=1 && ay>=1 && ax<=r && ay<=c && a[ax][ay]==w[d+1]){
		dfs3(ax,ay,d+1,(dire+1)%4,2);
	}
	if(d>0 && bx>=1 && by>=1 && bx<=r && by<=c && a[bx][by]==w[d+1]){
		dfs3(bx,by,d+1,(dire+3)%4,2);
	}
}
int main(){
	cin>>w>>r>>c;  //输入。
	len=w.length(); //长度。
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>a[i][j];  //输入。
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(a[i][j]==w[0]){
				//八个方向搜索。
				dfs1(i,j,0,0);
				dfs1(i,j,0,1);
				dfs1(i,j,0,2);
				dfs1(i,j,0,3);
				dfs2(i,j,0,0);
				dfs2(i,j,0,1);
				dfs2(i,j,0,2);
				dfs2(i,j,0,3);
			}
		}
	}
	cout<<sum<<endl; //输出。
	return 0;
}
```

---

## 作者：_sun_ (赞：1)

# 洛谷P9303

## DFS

### 题目描述

寻找目标单词，可以直着找，斜着找，可以转一次 $90$
度的弯。

### 思路

使用一个变量表示方向，再用另一个变量表示是否转弯。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
char a[110][110];
string s;
int q;//目标单词长度
int ans=0;
int dx[12] = {1, 0, -1, -1, -1, 0, 1, 1, 1, 0, -1, -1};
int dy[12] = {-1, -1, -1, 0, 1, 1, 1, 0, -1, -1, -1, 0};
// 从 2 - 9 的下标是顺时针八个方向 ，前两个和后两个是为了在转弯时方便
void dfs(int x,int y,int u,int fx,bool zj)
// x 指横坐标 ， y 指纵坐标 ， u 指搜索到目标单词的第几个字母 ， fx 指方向， zj 指是否转弯
{
    if(u>q)// 当搜索的字母数大于目标单词长度 ， 答案 + 1
    {
        ans++;
        return ;
    }
    if(fx==-1)// 没规定方向时 ， 八个方向都找一遍
        for (int i = 2; i <= 9; i ++ )
        {
            int xx=x+dx[i],yy=y+dy[i];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]==s[u])
                dfs(xx,yy,u+1,i,true);
        }
    else 
    {
        // 不转弯
        int xx=x+dx[fx],yy=y+dy[fx];
        if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]==s[u])
            dfs(xx,yy,u+1,fx,zj);
        if(zj)
        {
            // 顺时针转
            xx=x+dx[fx+2],yy=y+dy[fx+2];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]==s[u])
                dfs(xx,yy,u+1,fx+2,false);
            // 逆时针转
            xx=x+dx[fx-2],yy=y+dy[fx-2];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]==s[u])
                dfs(xx,yy,u+1,fx-2,false);
        }
    }
    return ;
}
int main()
{
    cin >> s;
    q=s.size()-1;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            cin >> a[i][j];
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
        {
            if(a[i][j]==s[0])// 找第一个字母
                dfs(i,j,1,-1,true);
        }
    cout << ans;
}
```


第一篇题解求过。

---

## 作者：ruanwentao666 (赞：1)

# P9303 [CCC 2023 J5] CCC Word Hun 题解
[题目传送门](https://www.luogu.com.cn/problem/P9303#submit)

## 题意分析
在一个字符矩阵中找出隐藏的字符串 $w$，输出矩阵中一共包含几个隐藏字符串。

怎么查找呢？题目中给出了 $2$ 种查找方式：

- 这个隐藏字符串按水平、垂直或对角斜线排成了一条直线。

- 这个隐藏字符串先进行一段，然后转 $90$  度再进行一段。

题目描述的很清楚，我就不过多赘述了。

## 思路讲解
首先看数据范围，$R,C\le 100$，那么我们脑海中最先想到的方法应该是深搜。为了方便写代码，我们分 $6$ 种情况去深搜：

1. 垂直向下查找。

2. 垂直向上查找。

3. 水平向右查找。

4. 水平向左查找。

5. 对角线查找。

6. 先查找一段，再折 $90$ 度查找。

有了这 $6$ 种情况，我们可以写出对应地 $6$ 个深搜函数。好了，直接上代码。

```cpp
#include<iostream>
using namespace std;
const int maxn = 105;
string W;
int r, c, ans;
char s[maxn][maxn];
int dfs1(int x, int y, int idx) {//情况1：垂直向下查找 
	if (idx == W.size())return 1;
	if (x<1 || y<1 || x>r || y>c)return 0;
	if (s[x][y] != W[idx])return 0;
	return dfs1(x + 1, y, idx + 1);
}
int dfs2(int x, int y, int idx) {//情况2：垂直向上查找 
	if (idx == W.size())return 1;
	if (x<1 || y<1 || x>r || y>c)return 0;
	if (s[x][y] != W[idx])return 0;
	return dfs2(x - 1, y, idx + 1);
}
int dfs3(int x, int y, int idx) {//情况3：水平向右查找 
	if (idx == W.size())return 1;
	if (x<1 || y<1 || x>r || y>c)return 0;
	if (s[x][y] != W[idx])return 0;
	return dfs3(x, y + 1, idx + 1);
}
int dfs4(int x, int y, int idx) {//情况4：水平向左查找 
	if (idx == W.size())return 1;
	if (x<1 || y<1 || x>r || y>c)return 0;
	if (s[x][y] != W[idx])return 0;
	return dfs4(x, y - 1, idx + 1);
}
int dfs5(int x, int y, int idx, int sel) {//情况5：对角线查找
	if (idx == W.size())return 1;
	if (x<1 || y<1 || x>r || y>c)return 0;
	if (s[x][y] != W[idx])return 0;
	if (sel == -1) {//第一次查找，可以往4个方向 
		return dfs5(x - 1, y - 1, idx + 1, 1) + dfs5(x - 1, y + 1, idx + 1, 2) + dfs5(x + 1, y - 1, idx + 1, 3) + dfs5(x + 1, y + 1, idx + 1, 4);
	}
	switch (sel) {
	case 1:
		return dfs5(x - 1, y - 1, idx + 1, 1);
	case 2:
		return dfs5(x - 1, y + 1, idx + 1, 2);
	case 3:
		return dfs5(x + 1, y - 1, idx + 1, 3);
	case 4:
		return dfs5(x + 1, y + 1, idx + 1, 4);
	}
}
int dfs6(int x, int y, int idx, int sel, bool flag) {//情况6：先查找一段，再折90°查找 
	if (s[x][y] != W[idx])return 0;
	if (idx == W.size()-1&&flag)return 1;
	if (idx == W.size()-1)return 0;
	if (x<1 || y<1 || x>r || y>c)return 0;
	if (sel == -1) {//第一次查找，可以往8个方向 
		int t1 = dfs6(x - 1, y, idx + 1, 1, 0) + dfs6(x + 1, y, idx + 1, 2, 0) + dfs6(x, y - 1, idx + 1, 3, 0) + dfs6(x, y + 1, idx + 1, 4, 0);
		int t2 = dfs6(x - 1, y - 1, idx + 1, 5, 0) + dfs6(x - 1, y + 1, idx + 1, 6, 0) + dfs6(x + 1, y - 1, idx + 1, 7, 0) + dfs6(x + 1, y + 1, idx + 1, 8, 0);
		return t1 + t2;
	}
	switch (sel) {
	case 1:
		if (flag) {
			return dfs6(x - 1, y, idx + 1, 1, flag);
		}
		return dfs6(x - 1, y, idx + 1, 1, 0) + dfs6(x, y - 1, idx + 1, 3, 1) + dfs6(x, y + 1, idx + 1, 4, 1);
	case 2:
		if (flag) {
			return dfs6(x + 1, y, idx + 1, 2, flag);
		}
		return dfs6(x + 1, y, idx + 1, 2, flag) + dfs6(x, y - 1, idx + 1, 3, 1) + dfs6(x, y + 1, idx + 1, 4, 1);
	case 3:
		if (flag) {
			return dfs6(x, y - 1, idx + 1, 3, flag);
		}
		return dfs6(x, y - 1, idx + 1, 3, flag) + dfs6(x - 1, y, idx + 1, 1, 1) + dfs6(x + 1, y, idx + 1, 2, 1);
	case 4:
		if (flag) {
			return dfs6(x, y + 1, idx + 1, 4, flag);
		}
		return dfs6(x, y + 1, idx + 1, 4, flag) + dfs6(x - 1, y, idx + 1, 1, 1) + dfs6(x + 1, y, idx + 1, 2, 1);
	case 5:
		if (flag) {
			return dfs6(x - 1, y - 1, idx + 1, 5, flag);
		}
		return dfs6(x - 1, y - 1, idx + 1, 5, flag) + dfs6(x - 1, y + 1, idx + 1, 6, 1) + dfs6(x + 1, y - 1, idx + 1, 7, 1);
	case 6:
		if (flag) {
			return dfs6(x - 1, y + 1, idx + 1, 6, flag);
		}
		return dfs6(x - 1, y + 1, idx + 1, 6, flag) + dfs6(x - 1, y - 1, idx + 1, 5, 1) + dfs6(x + 1, y + 1, idx + 1, 8, 1);
	case 7:
		if (flag) {
			return dfs6(x + 1, y - 1, idx + 1, 7, flag);
		}
		return dfs6(x + 1, y - 1, idx + 1, 7, flag) + dfs6(x - 1, y - 1, idx + 1, 5, 1) + dfs6(x + 1, y + 1, idx + 1, 8, 1);
	case 8:
		if (flag) {
			return dfs6(x + 1, y + 1, idx + 1, 8, flag);
		}
		return dfs6(x + 1, y + 1, idx + 1, 8, flag) + dfs6(x - 1, y + 1, idx + 1, 6, 1) + dfs6(x + 1, y - 1, idx + 1, 7, 1);
	}
}
int main() {
	cin >> W >> r >> c;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> s[i][j];
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			//对于以(i,j)开头的隐藏字符串 
			ans += dfs1(i, j, 0);
			ans += dfs2(i, j, 0);
			ans += dfs3(i, j, 0);
			ans += dfs4(i, j, 0);
			ans += dfs5(i, j, 0, -1);
			ans += dfs6(i, j, 0, -1, 0);
		}
	}
	cout << ans;
	return 0;
}
```

题目我们就写完了，声明一下：这是本人的第一篇题解，如有不足，请多多指教。

完结撒花！

---

## 作者：Jorisy (赞：1)

注意到数据范围很小，因此使用 dfs。

对每个点八个方向各搜一遍。而对于转弯，可以记录方向 $hd$ 与可否转向 $f$。每次搜完就累加答案即可。

于是就做完了。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int X[]={1,0,-1,0};
const int Y[]={0,1,0,-1};
const int X2[]={1,-1,-1,1};
const int Y2[]={1,1,-1,-1};
string s;
int n,m,ans;
char a[105][105];

void dfs(int dep,int x,int y,int hd,bool f=0)//上、下、左、右
{
	if(dep==s.size())
	{
		//cerr<<x<<' '<<y<<endl;
		ans++;//累加答案，下同
		return;
	}
	int x_=x+X[hd],y_=y+Y[hd];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&a[x_][y_]==s[dep]) dfs(dep+1,x_,y_,hd,f);//正常走，下同
	x_=x+X[(hd+1)%4];
	y_=y+Y[(hd+1)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs(dep+1,x_,y_,(hd+1)%4,1);//右转 90°，下同
	x_=x+X[(hd+3)%4];
	y_=y+Y[(hd+3)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs(dep+1,x_,y_,(hd+3)%4,1);//左转 90°，下同
}

void dfs2(int dep,int x,int y,int hd,bool f=0)//左上、左下、右上、右下
{
	if(dep==s.size())
	{
		//cerr<<x<<' '<<y<<endl;
		ans++;
		return;
	}
	int x_=x+X2[hd],y_=y+Y2[hd];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&a[x_][y_]==s[dep]) dfs2(dep+1,x_,y_,hd,f);
	x_=x+X2[(hd+1)%4];
	y_=y+Y2[(hd+1)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs2(dep+1,x_,y_,(hd+1)%4,1);
	x_=x+X2[(hd+3)%4];
	y_=y+Y2[(hd+3)%4];
	if(x_>0&&y_>0&&x_<=n&&y_<=m&&dep>1&&!f&&a[x_][y_]==s[dep]) dfs2(dep+1,x_,y_,(hd+3)%4,1);
}

int main()
{
	cin>>s>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==s[0])//相等时再搜
			{
				dfs(1,i,j,0);
				dfs(1,i,j,1);
				dfs(1,i,j,2);
				dfs(1,i,j,3);
				dfs2(1,i,j,0);
				dfs2(1,i,j,1);
				dfs2(1,i,j,2);
				dfs2(1,i,j,3);
			}
		}
	}
	cout<<ans;
 	return 0;
}
```

---

## 作者：Xswarx_XL (赞：0)

#[题目链接](https://www.luogu.com.cn/problem/P9303)

#大致题意：

就是让你在矩阵中找字符串。

#题目分析：

这明显一个深搜题目。

首先，我们要从网格中找到这个单词的首字母作为起点。

再审审题，起点周边八个方向都搜一圈，看看有没有这个单词第二个字母（这之间有细节，见程序）。

如果有，就以此方向为搜索方向，一直搜到底（终止条件和搜索条件见后文）。

但再审审题。

另一种方式是单词的字母出现在一个线段上，直到某个字母，然后出现在第二行在这个字母处形成直角的线段。

中途这个方向是可以转一次的，那么就要多写一种情况。

该怎么转呢，简单，要么向左转，要么向右转。
     
八种方向的转法如下表示：

左下转到左上，右下。

左上转到左下，右上。

右下转到左下，右上。

右上转到左上，右下。

上转到左，右。 

下转到左，右。 

左转到上，下。 

右转到上，下。

这样解决了转的问题，再来找搜索的终止条件和进行条件。

进行条件：

就是坐标不出界，下一个要搜位置上的字母是单词那个位置上的字母。

终止条件：

就是搜完了整个单词。

综上所述，如果还不懂，看看代码吧。

#程序公示
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105],c[105][105];
int n,m,ans,dx[8]={1,1,-1,-1,1,-1,0,0},dy[8]={-1,1,-1,1,0,0,1,-1};
void dfs(int x,int y,int l,int fx,int f){
	if(l==strlen(s)-1){
		ans++;
		return;
	}		
	int ux=x+dx[fx],uy=y+dy[fx];
	if(ux>=0&&ux<n&&uy>=0&&uy<m&&c[ux][uy]==s[l+1])
		dfs(ux,uy,l+1,fx,f);
	if(f==0){
		int tf1,tf2;
		if(fx==0||fx==3)
			tf1=1,tf2=2;
		if(fx==1||fx==2)
			tf1=0,tf2=3;
		if(fx==4||fx==5)
			tf1=6,tf2=7;
		if(fx==6||fx==7)
			tf1=4,tf2=5;
		ux=x+dx[tf1],uy=y+dy[tf1];
		if(ux>=0&&ux<n&&uy>=0&&uy<m&&c[ux][uy]==s[l+1])
			dfs(ux,uy,l+1,tf1,1);
		ux=x+dx[tf2],uy=y+dy[tf2];
		if(ux>=0&&ux<n&&uy>=0&&uy<m&&c[ux][uy]==s[l+1])
			dfs(ux,uy,l+1,tf2,1);				
	}
}
int main(){
	cin>>s>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>c[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(c[i][j]==s[0]){
				if(strlen(s)==1)
					ans++;
				else
					for(int k=0;k<8;k++)
						if(c[i+dx[k]][j+dy[k]]==s[1])
							dfs(i+dx[k],j+dy[k],1,k,0);								
			}
	cout<<ans;
	return 0;
}
```

#小结：

- 本题和 P1101 单词方阵很像（仅代表个人看法），但某些地方有点不同，因此评黄很合理。

- 深搜练习题，增加熟练度。

---

## 作者：ccg12345 (赞：0)

#### 思路
看到题目后我立马想到了搜索方法中的洪水填充。

首先输入后先遍历一遍所有的字符，看与字符串的第一个字符是否相同，若相同则可以以这个点为起点开始搜索。每次若出格或不与想要的字符相同则立马返回，若字符一一对应则让结果加一。

因为可以在中途转 $90$ 度，所以我们 $8$ 个方向均要搜索，但要注意转弯时需要不是第一个字符且还未转过弯。

附代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1}, dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, r, c, ans = 0;
//dx[8],dy[8]分别是向8个方向分别移动后的行列变化，ans是总数
char a[105][105];
string s;
void srh(int x, int y, int now, int t, bool k)//分别是横坐标，纵坐标，进行到字符串的第几个字符，搜索方向和当前是否转过弯
{
	if(x <= 0 || x > r || y <= 0 || y > c || a[x][y] != s[now])
		return ;//字符出格或与s中的字符不匹配时退出
	if(now == s.length() - 1) 
	{
		ans++;
		return ;
	}//与字符串匹配，答案数加一
	srh(x + dx[t], y + dy[t], now + 1, t, k);
	if(k && now != 0)
	{
		srh(x, y, now, (t + 6) % 8, false);
		srh(x, y, now, (t + 2) % 8, false);
	}//若拐弯了立即将k设为false
}
int main()
{
    cin >> s;
    cin >> r >> c;
    for(register int i = 1; i <= r; i++)
    	for(register int j = 1; j <= c; j++)
    		cin >> a[i][j];
	for(register int i = 1; i <= r; i++)
    	for(register int j = 1; j <= c; j++)
    		if(a[i][j] == s[0])
    			for(register int k = 0; k < 8; k++)
    				srh(i, j, 0, k, true);//若与字符串第零个字符相同，则从此点开始搜索
    cout << ans << endl;
    return 0;
}
```


---

## 作者：AmaoFox (赞：0)

## 题意
[题目传送门](/problem/P9303)

+ 给定字符串 $W$，一个 $R \times C$ 的字符矩阵。
+ 字符串的方向可能为：水平、竖直、斜对角方向、走了几格转 $90\degree$ 然后又继续走（最多转一次）。
+ 求字符矩阵里有多少个 $W$。

## 做法
看看数据范围，什么，$2 \le W \le 299$，这显然是想让我们使用搜索的题目。

根据题目，我们的函数中要有五个参数：当前的坐标需要两个 `int`，当前的方向需要一个 `int`，搜到 $W$ 的第几个字符了需要一个 `int`，转没转过弯又需要一个 `bool`。  
转移只有两种：下一个字符或者转弯。
+ 下一个字符：改变坐标，不改变方向，字符编号加一，不改变转弯标记。
+ 转弯：不改变坐标，方向转 $90\degree$，不改变字符编号，改变转弯标记。

显然转弯操作是有条件的，我们刚搜了一个字符就转弯：和另一个方向的不转弯没有区别，那样就重解了。我们也不可能转弯了以后还转弯，因此必须要在没有转弯标记的时候才能转弯。  
答案加一，搜索结束的条件就是找到了最后一个字符。

那么什么时候开始搜索呢？

我们可以将字符串整个遍历一遍，只要找到最开头的那个字母，就把八个方向都开始搜一遍。

具体的实现，我们可以关注[代码](/paste/7p5rwpis)和[AC记录](/record/109304732)。

---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/P9303)

给定一个字符串 $W$ 和一个字符阵，问一共能从字符阵中找到多少个字符串 $W$。

字符串有这几种可能的方向：

- 水平。
- 垂直。
- 对角斜线。
- 先进行一段，然后转 $90$ 度再进行一段。

## 思路

使用深度优先搜索。

遍历字符阵，找到开头的字符，开始搜索。

深度优先搜索的函数中有几个参数：

- 参数 $x$ 和 $y$：字符的坐标。
- 参数 $cnt$：到了字符串第几个字符。
- 参数 $dir$：当前的搜索方向。
- 参数 $change$：是否没有改变过方向。

在搜索中，如果当前坐标出界或者当前字符不是我们要的那个字符就直接返回，如果找到了最后一个字符就将答案加一。

要分别搜索 $8$ 个方向，分别是：

1. 水平方向（从左到右）

2. 水平方向（从右到左）
3. 垂直方向（从上到下）
4. 垂直方向（从下到上）
5. 主对角线（从左上到右下）
6. 主对角线（从右下到左上）
7. 副对角线（从右上到左下）
8. 副对角线（从左下到右上）

每次在移动的同时，将 $cnt$ 加一，匹配下一个字符。

当且仅当当前字符不是第一个字符（不能一个字符还没有匹配到了就改变方向了），即下标不是 $0$，且从未改变过方向时，可以改变方向，改变方向时要注意方向要变为和自己当前方向垂直的那两个方向。

比如说，如果当前是水平方向（从左到右），那么方向就可以改变为垂直方向（从下到上）或垂直方向（从上到下）。如果当前是主对角线（从左上到右下），那么方向就可以改变为主对角线（从右下到左上）或副对角线（从右上到左下）。

改变方向后，注意要把 $change$ 设为 `false`，阻止程序再次改变方向。

## 代码

具体实现细节见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int R = 105;
char a[R][R];
string str;
int r, c, ans;

// 深度优先搜索，x和y是坐标，cnt是记录到了字符串第几个字符，dir是方向记录，change是是否改表过方向（因为只能改变一次方向）
void dfs(int x, int y, int cnt, int dir, bool change) {
    if(x < 1 || x > r || y < 1 || y > c || a[x][y] != str[cnt]) // 如果出界或者当前字符不是我们要的那个字符就直接返回
        return;
    if(cnt == str.size() - 1) { // 如果找到了最后一个字符那么就++ans
        ++ans;
        return;
    }
    if(dir == 1) { // 水平方向（从左到右）
        dfs(x, y + 1, cnt + 1, 1, change);
        if(cnt && change)   // 当且仅当当前字符不是第一个字符（不能一个还没有找了就转弯了），即下标不是0，且从未改变过方向时，改变方向
            dfs(x - 1, y, cnt + 1, 4, false),  // 垂直方向（从下到上）
            dfs(x + 1, y, cnt + 1, 3, false);  // 垂直方向（从上到下）
    } else if(dir == 2) { // 水平方向（从右到左）
        dfs(x, y - 1, cnt + 1, 2, change);
        if(cnt && change)   // 改变方向
            dfs(x - 1, y, cnt + 1, 4, false),  // 垂直方向（从下到上）
            dfs(x + 1, y, cnt + 1, 3, false);  // 垂直方向（从上到下）
    } else if(dir == 3) {  // 垂直方向（从上到下）
        dfs(x + 1, y, cnt + 1, 3, change);
        if(cnt && change)   // 改变方向
            dfs(x, y - 1, cnt + 1, 2, false), // 水平方向（从右到左）
            dfs(x, y + 1, cnt + 1, 1, false); // 水平方向（从左到右）
    } else if(dir == 4) {  // 垂直方向（从下到上）
        dfs(x - 1, y, cnt + 1, 4, change);
        if(cnt && change)   // 改变方向
            dfs(x, y - 1, cnt + 1, 2, false), // 水平方向（从右到左）
            dfs(x, y + 1, cnt + 1, 1, false); // 水平方向（从左到右）
    } else if(dir == 5) {  // 主对角线（从左上到右下）
        dfs(x + 1, y + 1, cnt + 1, 5, change);
        if(cnt && change)   // 改变方向
            dfs(x - 1, y + 1, cnt + 1, 6, false),  // 主对角线（从右下到左上）
            dfs(x + 1, y - 1, cnt + 1, 7, false);  // 副对角线（从右上到左下）
    } else if(dir == 6) {  // 主对角线（从右下到左上）
        dfs(x - 1, y + 1, cnt + 1, 6, change);
        if(cnt && change)   // 改变方向
            dfs(x + 1, y + 1, cnt + 1, 5, false),  // 主对角线（从左上到右下）
            dfs(x - 1, y - 1, cnt + 1, 8, false);  // 副对角线（从左下到右上）
    } else if(dir == 7) { // 副对角线（从右上到左下）
        dfs(x + 1, y - 1, cnt + 1, 7, change);
        if(cnt && change)   // 改变方向
            dfs(x + 1, y + 1, cnt + 1, 5, false),  // 主对角线（从左上到右下）
            dfs(x - 1, y - 1, cnt + 1, 8, false);  // 副对角线（从左下到右上）
    } else {    // 副对角线（从左下到右上）
        dfs(x - 1, y - 1, cnt + 1, 8, change);
        if(cnt && change)   // 改变方向
            dfs(x - 1, y + 1, cnt + 1, 6, false),  // 主对角线（从右下到左上）
            dfs(x + 1, y - 1, cnt + 1, 7, false); // 副对角线（从右上到左下）
    }
}

int main() {
    // 读入
    cin >> str >> r >> c;
    for(int i = 1; i <= r; ++i)
        for(int j = 1; j <= c; ++j)
            cin >> a[i][j];
    for(int i = 1; i <= r; ++i)
        for(int j = 1; j <= c; ++j)
            if(a[i][j] == str[0])   // 找到开头的字符，开始搜索
                for(int k = 1; k <= 8; ++k) // 8个方向
                    dfs(i, j, 0, k, true);  // 坐标(i,j)，下标为0，方向为k，尚未改变过方向
    cout << ans;
    return 0;
}
```


谢谢大家！完结撒花！


---

## 作者：Leaves_xw (赞：0)

**思路：**

这道题其实并不难，用到了连通块的思想，即从一个点出发，四个方向搜寻，并放入栈中，可以从[这里](https://www.luogu.com.cn/problem/list?page=1&tag=175)看到例题。

那么按照连通块寻找，如果发现有组成的目标字符串，则将 $cnt$ 累加 $1$，最后输出 $cnt$ 就行。

可以参考：

```
int main()
{
    int cnt=0;
    string s;
    cin>>s;
    int r,c;
    cin>>r>>c;
    int C[105][105];
    for(int i=1;i<=r;i++)for(int j=1;j<=c;j++)cin>>C[i][j];
    q.push(s);
    vis[s.st][s.nd]=true;
    while(!q.empty())
    {
    	pii u=q.front();
    	q.pop();
    	ans++;
    	int x=u.st,y=u.nd;
    	for(int i=0;i<=3;i++)
    	{
    		int fx=dx[i]+x,fy=dy[i]+y;
    		if(!check(fx,fy))continue;
    		vis[fx][fy]=true;
    		q.push({fx,fy});
    	}
    }
    return cnt;
}
```

---

## 作者：封禁用户 (赞：0)

发现这题好多人用大模拟，其实很简单就能实现，附上最短代码。

#### 题目分析
我们简化一下题意，就会发现有几种情况：
- 水平方向查找。

- 拐角查找。

- 斜线查找。

首先，水平和拐角肯定很好实现，我们可以模拟，然后拐角我们就需要用到搜索了。

我们 DFS 先维持两种状态，记 $cnt$ 为是转弯的次数，$d$ 为查到哪个字母，$x$ 为查到位置的行，$y$ 为列，$tx$、$ty$ 是上次方向。

显然，转弯是 $x$ 和 $y$ 加上八字偏移量，然后把转弯数加 $1$，上次的坐标就是转弯的八字偏移量。

不回头很好判断，那怎么判断是否按照同方向走呢？我们初始的 $tx$ 赋一个最小值，如果上一次的等于这一次的八字偏移量，我们就可以往同方向走了。


那么 $cnt$ 为 $0$ 时，我们下一次的方向就是下面的，我们还可以加上水平和拐角一起实现。
```cpp
if( x < 1 || y < 1 || x > n || y > m || f[x][y] != s[d] ) return;
if(d == strlen(s)-1) res ++;
for(int i = 0 + z; i < 4 + z; i++)
{
  // 不回头
  if(tx == -nx[i] && ty == -ny[i]) continue;
  // 沿着同方向走
  if(tx == -99 || (tx == nx[i] && ty == ny[i])) 
      dfs(d + 1,  x + nx[i], y + ny[i], cnt, nx[i], ny[i], z);
  // 转弯cnt == 0 时可转 因为只能转一次
  else if(!cnt)  
      dfs(d + 1,  x + nx[i], y + ny[i], cnt + 1, nx[i], ny[i], z);
}
```


---

