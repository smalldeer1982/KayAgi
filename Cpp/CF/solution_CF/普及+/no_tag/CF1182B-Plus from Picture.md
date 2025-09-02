# Plus from Picture

## 题目描述

You have a given picture with size $ w \times h $ . Determine if the given picture has a single "+" shape or not. A "+" shape is described below:

- A "+" shape has one center nonempty cell.
- There should be some (at least one) consecutive non-empty cells in each direction (left, right, up, down) from the center. In other words, there should be a ray in each direction.
- All other cells are empty.

Find out if the given picture has single "+" shape.

## 说明/提示

In the first example, the given picture contains one "+".

In the second example, two vertical branches are located in a different column.

In the third example, there is a dot outside of the shape.

In the fourth example, the width of the two vertical branches is $ 2 $ .

In the fifth example, there are two shapes.

In the sixth example, there is an empty space inside of the shape.

## 样例 #1

### 输入

```
5 6
......
..*...
.****.
..*...
..*...
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 5
..*..
****.
.*...
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7 7
.......
...*...
..****.
...*...
...*...
.......
.*.....
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
5 6
..**..
..**..
******
..**..
..**..
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
3 7
.*...*.
***.***
.*...*.
```

### 输出

```
NO
```

## 样例 #6

### 输入

```
5 10
..........
..*.......
.*.******.
..*.......
..........
```

### 输出

```
NO
```

# 题解

## 作者：Pengzt (赞：4)

[CF1182B](https://www.luogu.com.cn/problem/CF1182B)

一道水题。

首先看数据范围 $w, h \le 500$，就大概能知道是枚举了。

先枚举这个“十”的中心点，再判断能否向四个方向上走，统计 $\texttt{* }$ 的数量是否等于总数量即可。

注意不能向一个方向走的话也是不行的。

时间复杂度 $\mathcal{O}(wh(w + h))$。

代码实现应该还挺简单的。

[评测记录](https://codeforces.com/contest/1182/submission/185248956)

---

## 作者：w9095 (赞：2)

[CF1182B Plus from Picture ](https://www.luogu.com.cn/problem/CF1182B)

### 写在前面

为什么在已经有 $12$ 篇题解后，我还是要写这篇题解？

因为这篇题解提供一个码量较小，且时间复杂度**严格 $O(wh)$** 的做法，目前这种做法题解区没有。

### 进入正题

设 $cnt[i]$ 表示地图中的 `*` 周围四联通有 $i$ 个 `*` 的位置的数量

考虑到地图中**有且仅有一个** `+` 形图形的性质：

$1$ ：若要保证有且仅有一个 `+` 形图形，则 $cnt[4]=1$ 。因为每个 `+` 形图形对应**一个**周围四联通有四个 `*` 的 `*` （中间那一个），所以周围四联通有四个 `*` 的 `*` **有且仅有一个** 。

括号圈起来的是这一条所描述的点，后面也是如此：

```latex
  *
*(*)*
  *
```

$2$ ：若要保证有且仅有一个 `+` 形图形，则 $cnt[1]=4$ 。因为每个 `+` 形图形对应**四个**周围四联通有一个 `*` 的 `*` （ `+` 形图形的最外围），所以周围四联通有一个 `*` 的 `*` **有且仅有四个** 。

```latex
  (*)
(*)*(*)
  (*)
```

$3$ ：若要保证除 `+` 形图形各点之外，整张地图均为 `.` ，则 $cnt[0]=0$ 且 $cnt[3]=0$ 。因为 `+` 形图形中**不存在这样的点**，若存在，则必然是 `+` 形图形各点之外的 `*` ，不能保证除 `+` 形图形各点之外，整张地图均为 `.` 。

```latex
. . . .(*)
. * . . .
*(*). . .
. * . . .
```

$4$ ：对于 $cnt[2]$ ，如果**上面的点与下面的点，左边的点和右边的点分别相同**，则这个点对结果无影响。因为 `+` 形图形**可能存在这样的点**。

```latex
 *
**(*)*
(*)
 *
```

$5$ ：对于 $cnt[2]$ ，如果不满足上面情况，则地图中除 `+` 形图形各点之外，整张地图必然不均为 `.` 。因为 `+` 形图形中同样**不存在这样的点**。

```latex
. . . .
.(*)* .
. *(*).
. . . .
```

所以，只要判断这五条性质，就能得出结果。

### 复杂度分析

很显然，扫一遍数组就可以得到结论了。

时间复杂度： $O(wh)$

空间复杂度： $O(wh)$

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int w,h,cnt[5];
char map1[501][501];
int main()
{
    scanf("%d%d",&w,&h);
    for(int i=0;i<w;i++)
        scanf("%s",map1[i]);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
            {
            int ans1=0,ans2=0;
            if(map1[i][j]!='*')continue; \\如果不是*，没有必要计算
            if(i-1>=0&&map1[i-1][j]=='*')ans1++;
		    if(i+1<w&&map1[i+1][j]=='*')ans1++; \\上下点的情况
		    if(j-1>=0&&map1[i][j-1]=='*')ans2++;
		    if(j+1<h&&map1[i][j+1]=='*')ans2++; \\左右点的情况
		    if(ans1%2&&ans2%2) \\判断上下左右点是否分别相等
		       { \\如果分别相等则对应的计数一定都为偶数
		       	printf("NO\n");
		       	return 0;
			   }
		    cnt[ans1+ans2]++;
            }
    if(cnt[0]==0&&cnt[1]==4&&cnt[3]==0&&cnt[4]==1)printf("YES\n"); \\综合五条性质判断
    else printf("NO\n");
    return 0;
}
```

### 后记

[AC记录](https://www.luogu.com.cn/record/97443804)

于 $2022$ 年 $12$ 月 $16$ 日达成最优解。

![](https://cdn.luogu.com.cn/upload/image_hosting/v4ujz48d.png)

---

## 作者：alex_liu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1182B)

思路：

简单的一道 dfs，第一眼看到数据范围就发现可以对每一个点进行深搜，向四个方向统计 `*` 的个数，先特判有一个方向为 0 的情况，再统计能连接到的所有 `*` 如果与总的 `*` 数量相同，就输出 `YES`，否则输出 `NO`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,all;
char c[505][505];
inline bool check(int x,int y){//特判是否出界 
	if(x<1||x>n||y<1||y>m)return 0;
	return 1;
}
inline int dfs(int x,int y){//向四个方向搜索 
	int x1=x-1,x2=x+1,x3=x,x4=x,y1=y,y2=y,y3=y+1,y4=y-1,cnt=0,cnt1=0,cnt2=0,cnt3=0,cnt4=0;
	while(!(c[x1][y1]^'*')&&check(x1,y1))++cnt1,--x1;
	while(!(c[x2][y2]^'*')&&check(x2,y2))++cnt2,++x2;
	while(!(c[x3][y3]^'*')&&check(x3,y3))++cnt3,++y3;
	while(!(c[x4][y4]^'*')&&check(x4,y4))++cnt4,--y4;
	cnt=cnt1+cnt2+cnt3+cnt4;
	if(cnt1&&cnt2&&cnt3&&cnt4)return cnt; 
	return -1;//如果有一个方向为 0 则返回 -1 
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			all+=(c[i][j]^'*'?0:1);//统计所有的 * 的个数 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!(c[i][j]^'*')){
				if(dfs(i,j)+1==all)ans++;//搜索每一个 * 点 
			}
		}
	}
	puts(ans==1?"YES":"NO");//有且仅有一个点 
	return 0;
}
```

做完这道题我思考了一下，其实本题是不会出现有两个或以上满足条件的点的。

证明：

假设现在有两个点满足条件，那么这两个点的上下或者左右的点一定不与另一个点相同，因为这两个点最多只会在同一纵列或者同一横排上。

---

## 作者：灵光一闪 (赞：2)

~~嗯，T2是不是和T1的超链接搞反了？？？明显一点思维难度都没有好吧？~~

思路：找到一个上下左右都是``*``的``*``，然后work;

具体看代码：
```
//老规矩，把注释的puts和cout启用就可以看出来了
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
char c[666][666];
int num,n,m;
void work(int x,int y){
    for(int i=x;c[i][y]=='*';i++){//向四周循环到没有*了
        num--;
//        cout<<1<<" ";
    }
    for(int i=x;c[i][y]=='*';i--){//同上
        num--;
//        cout<<2<<" ";
    }
    for(int j=y;c[x][j]=='*';j--){//同上
        num--;
//        cout<<3<<" ";
    }
    for(int j=y;c[x][j]=='*';j++){//emming……
        num--;
//        cout<<4<<" ";
    }
//    puts("");
    num+=3;//因为中心的那个点只用算一次，但我们算了四次，所以要补3次
//    cout<<num<<endl;
    if(num==0){//全都用光了
        puts("YES");
        exit(0);
    }
    else{//一旦发现有多余的，直接NO，因为符合if(c[i-1][j]=='*'&&c[i+1][j]=='*'&&c[i][j-1]=='*'&&c[i][j+1]=='*')这个条件的只能有一个，有第2个也是错，还不如直接结束程序
        puts("NO");
        exit(0);
    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c[i][j];
            if(c[i][j]=='*'){
                num++;//num是*的总数
            }
        }
    }
    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
//            cout<<i<<" "<<j<<endl;
            if(c[i-1][j]=='*'&&c[i+1][j]=='*'&&c[i][j-1]=='*'&&c[i][j+1]=='*'){//找到了
                work(i,j);//工作ing……
            }
        }
    }
    puts("NO");//连符合条件的都没有，直接NO不解释
    return 0;
}
```

---

## 作者：AgrumeStly (赞：2)

这是一道超级水的模拟 + 简单搜索。

说说思路：

先找到中心点，就是自己和上下左右都为 `*` 的。

上下左右上的所有 `*` 都删掉，然后再看看有没有多余的 `*` 如果有输出 `NO` 否则输出 `YES`。

比如说有这样一个 $n = 5$ 的图：

$$\begin{matrix}
.&.&.&.&*\\
.&.&*&.&.\\
.&*&*&*&*\\
.&.&*&.&.\\
.&.&*&.&.
\end{matrix}$$

首先一个一个找，当找到一个点，自己本身和上下左右均为 $*$ 时（如图中 $a$ 点）：

$$\begin{matrix}
.&.&.&.&*\\
.&.&*&.&.\\
.&*&a&*&*\\
.&.&*&.&.\\
.&.&*&.&.
\end{matrix}$$

将上下左右上的一条全部变为 $*$：

$$\begin{matrix}
.&.&.&.&*\\
.&.&.&.&.\\
.&.&.&.&.\\
.&.&.&.&.\\
.&.&.&.&.
\end{matrix}$$

那我们就会发现图中还有 $*$ 没有变成 $.$ 这就说明此加号不合法。

上代码：

```cpp
/*
  Problem:CF1182B
  Date:14/06/20 12:02
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#define line cout << endl
#define int long long 
using namespace std;
char ma[2005][2005];
int h, w;
bool flag;
void up (int i, int j) {
	ma[i][j] = '.';
	if (ma[i - 1][j] == '*')
		return up(i - 1, j);
}
void down (int i, int j) {
	ma[i][j] = '.';
	if (ma[i + 1][j] == '*')
		return down(i + 1, j);
}
void left (int i, int j) {
	ma[i][j] = '.';
	if (ma[i][j - 1] == '*')
		left(i, j - 1);
}
void right (int i, int j) {
	ma[i][j] = '.';
	if (ma[i][j + 1] == '*')
		return right(i, j + 1);
}
void kill (int i, int j) {
	ma[i][j] = '.';
	up (i - 1, j);
	down (i + 1, j);
	left (i, j - 1);
	right (i, j + 1);
}
void test () {//测试(i,j)是不是一个加号的中心
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++)
            if (ma[i][j] == '*' && 
                ma[i - 1][j] == '*' &&
                ma[i][j - 1] == '*' &&
                ma[i + 1][j] == '*' &&
                ma[i][j + 1] == '*') {//对第一个可能的十字的中心
	            	kill (i, j);//抹去这个十字
	                flag = true;
	                break;
            }
        if (flag) break;
    }
    for (int i = 1; i <= h; i++)//这时,应没有'*'了
        for (int j = 1; j <= w; j++)
            if (ma[i][j] == '*')
                flag = false;
}
signed main () {
	cin >> h >> w;
	for(int i = 1; i <= h; i++)
		for(int j = 1; j <= w; j++)
			cin >> ma[i][j]; 
	test();
	if(flag) puts("YES");
	else puts("NO");
	return 0;
}

谢谢。

---

## 作者：meyi (赞：2)

一道普通的模拟题，按题意带技巧模拟即可。（技巧见代码内注释，~~顺便吐槽一下恶意评分~~）
```cpp
#include<cstdio>
char a[501][501];
int h,w,s,t=5;	//h和w同题意，s为'*'的总个数，t为所找的十字内'*'的总个数
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;++i){
		scanf("%s",*(a+i)+1);
        //输入
		for(int j=1;j<=w;++j)a[i][j]=='*'&&++s;
        //统计全图中'*'的总个数
	}
	if(s<5)return puts("NO"),0;
    //应该没啥用的贪心，若总个数不到5个绝对无法构成十字
	for(int i=1;i<=h;++i)
		for(int j=1;j<=w;++j)
			if(a[i-1][j]=='*'&&a[i][j-1]=='*'&&a[i][j]=='*'&&a[i][j+1]=='*'&&a[i+1][j]=='*'){
            	/*因为要求仅有一个十字才符合条件，所以找到一个十字的
                  “中心点”就可以开始统计这个十字内'*'的个数了*/
				for(int k=2;i>k&&a[i-k][j]=='*';++k,++t);
				for(int k=2;j>k&&a[i][j-k]=='*';++k,++t);
				for(int k=2;i+k<=h&&a[i+k][j]=='*';++k,++t);
				for(int k=2;j+k<=w&&a[i][j+k]=='*';++k,++t);
                //累加该十字内'*'的个数
				return puts(s==t?"YES":"NO"),0;
                /*因为要求除去该十字内的'*'，全图没有其他的'*'，
                  所以比较该十字内'*'的个数和全图中'*'的个数就行了，
                  若不相等，则全图中必定还有其他的'*'不在该十字内，
                  不符合要求。*/
			}
	puts("NO");
    //若全图内没有一个十字的“中心点”，则不符合要求中的“至少有一个十字”
	return 0;
}
```


---

## 作者：VinstaG173 (赞：1)

`对于每个*格，沿上下左右方向找其他*，然后如果所有*都能按这个方法找到且上下左右都有*格，则输出YES，若所有*格都不满足，输出NO。具体见代码。`

Code:
```cpp
#include<cstdio>
int N,M,sum;
char c;
int mp[503][503];//记录输入，'*'为1，'.'为0
int main()
{
	scanf(" %d %d",&N,&M);
	for(int i=1;i<=N;++i)
	{
		for(int j=1;j<=M;++j)
		{
			scanf(" %c",&c);
			if(c=='*')mp[i][j]=1,++sum;
			else mp[i][j]=0;
		}
	}
	for(int i=1;i<=N;++i)
	{
		for(int j=1;j<=M;++j)
		{
			if(!mp[i][j])continue;//不是*，跳过
			int k,l,r=1,a=0,b=0,c=0,d=0;//k,l用于遍历，a,b,c,d表示左右上下是否有东西
			k=i,l=j-1;
			while(mp[k][l])--l,++r,a=1;//左
			k=i,l=j+1;
			while(mp[k][l])++l,++r,b=1;//右
			k=i-1,l=j;
			while(mp[k][l])--k,++r,c=1;//上
			k=i+1,l=j;
			while(mp[k][l])++k,++r,d=1;//下
			if(r==sum&&a&&b&&c&&d)return 0&printf("YES\n");//满足条件，输出YES
		}
	}
	return 0&printf("NO\n");//所有格都不满足，输出NO
}
```

---

## 作者：_JF_ (赞：1)

## CF1182B Plus from Picture 

[题目传送门](https://www.luogu.com.cn/problem/CF1182B)

深搜的练手题。

题目大意：找到一个 由 `*` 组成的 `+`，要求用完矩阵中全部的 `*` ，同时要求有且仅有一个。

思路：先找到一个 `*` ，让它成为中心点，然后向四个方向进行拓展，同时记录沿途 `*` 的个数。如果 `*` 的个数刚好和矩阵中 `*` 的个数相同，记为一种合法情况，再在最后判断它是否等于 $1$ 即可。
 
但是要注意一点，如果在一个矩阵中仅有一个 `*` ，按照刚才的方法统计到 $0$ 个，加上中心点的一个 `*` ，刚好和矩阵中 `*`，的个数相同，但是这种情况是不合法的。

解决方法就是开一个 flag，当遇到四个方向任意一个方向没有 `*` 的时候，不予累加以及判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1000;
char a[N][N];
int n,m,s1,s2,s3,s4;
bool flag;
bool check(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=m;
}
int dfs1(int x,int y)
{	
	int xx=x+1;
	int yy=y;
	if(check(xx,yy)&&a[xx][yy]=='*')
		s1++,dfs1(xx,yy);
	if(s1==0)flag=1;	
	return s1;
}
int dfs2(int x,int y)
{
	int xx=x-1;
	int yy=y;
	if(check(xx,yy)&&a[xx][yy]=='*')
		s2++,dfs2(xx,yy);
	if(s2==0)flag=1;	
	return s2;
}
int dfs3(int x,int y)
{
	int xx=x;
	int yy=y+1;
	if(check(xx,yy)&&a[xx][yy]=='*')
		s3++,dfs3(xx,yy);
	if(s3==0)flag=1;	
	return s3;
}
int dfs4(int x,int y)
{
	int xx=x;
	int yy=y-1;
	if(check(xx,yy)&&a[xx][yy]=='*')
		s4++,dfs4(xx,yy);	
	if(s4==0)flag=1;
	else
		return s4;
}
int main()
{
	int sum=0,ans=0;
	cin>>n>>m;
	if(n==1&&m==1)
		cout<<"NO"<<endl,exit(0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='*')
				sum++;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			flag=0;
			if(a[i][j]=='*')
			{
				s1=0,s2=0,s3=0,s4=0;
				int last=(dfs1(i,j)+dfs2(i,j)+dfs3(i,j)+dfs4(i,j))+1;
				if(last==sum&&!flag)
					ans++;
			}
		}
			
	if(ans!=1)
		cout<<"NO"<<endl,exit(0);
	else
		cout<<"YES"<<endl,exit(0);
}
```


---

## 作者：seanlsy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1182B)

**思路**

```.``` 比较好处理，可以直接判断。我们可以用搜索来处理 ```+``` 号。

首先统计出 ```*``` 的个数，然后再暴力枚举每个点是否可以作为起点，然后向四个方向搜索，并记录个数。如果 ```*``` 的个数和开始统计的结果一致，就说明合法否则不合法。

**MAIN CODE**
```cpp
for(int i=1;i<=w;i++)
  for(int j=1;j<=h;j++)
    if(c[i][j]=='*'&&c[i+1][j]=='*'&&c[i-1][j]=='*'&&c[i][j+1]=='*'&&c[i][j-1]=='*'){
	nx=i,ny=j;
	while(c[nx][ny]=='*') tt++,nx++;
        //向四个方向搜索，此时 tt 的初始值为 -3
	nx=i;
	while(c[nx][ny]=='*') tt++,nx--;
	nx=i;
	while(c[nx][ny]=='*') tt++,ny++;
	ny=j;
	while(c[nx][ny]=='*') tt++,ny--;
	if(tt^num)
		return puts("NO"),0;
	else return puts("YES"),0;
    }
```

---

## 作者：TLMPEX (赞：1)

思路：此题模拟加枚举即可，具体思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
char r[501][501];
int a[4]={-1,0,0,1},b[4]={0,-1,1,0};//方向数组
int pd(int i,int j){//判断上下左右是否是‘*’
	if(r[i][j]=='*'&&r[i+1][j]=='*'&&
	r[i-1][j]=='*'&&r[i][j+1]=='*'&&r[i+1][j]=='*')
		return 1;
	else return 0;
}
int main(){
	int n,m,i,j,x,t=0;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>r[i][j];
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)//枚举每一个点
			if(!t&&pd(i,j)){//如果目前还没找到‘+’并且上下左右都是‘*’
				t=1;//标记t为1
				r[i][j]='.';//把这个中心点置为‘.’
				for(x=0;x<4;x++){//向4个方向拓展
					int nx=i+a[x],ny=j+b[x];//下一个点的坐标
					while(nx>=1&&ny>=1&&nx<=n&&ny<=m&&r[nx][ny]=='*'){//如果下一个点在边界以内兵且是‘*’，则把这个点置为‘.’，并更新下一个点的坐标
						r[nx][ny]='.';
						nx+=a[x];
						ny+=b[x];
					}
				}
			}
	if(!t)cout<<"NO";//如果没找到‘+’号，则输出‘NO’
	else{
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(r[i][j]=='*'){//如果周围有多余的‘*’则输出‘NO’
					cout<<"NO";
					return 0;
				}
		cout<<"YES";//否则输出‘YES’
	}
}
```


---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1182B)

## 0.题目大意
给你一个图，让你去判断图中有没有类似于十字的符号。

## 1.思路解读
这是一道搜索题，我们要处理该图中所有的 ```*``` ，因为数据范围不大，我们可以直接枚举。枚举的思路就是用 ```cnt``` 储存下图中 ``` * ``` 的个数，再遍历图中有没有中间点，即十字交叉的交点，最后将统计出来的 ```ans``` 与 ```cnt``` 比较是否相等。枚举部分用 ```while``` 循环即可。

## 2.代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,cnt,ans=1;
int x,y;
char mz[510][510];
bool check(int x,int y){//判断该字符是不是"*"
	if(mz[x][y]=='*') 
		return true;
	return false;
}
bool dfs(int n,int m){//遍历这个图，找到一个中间点
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(check(i,j) && check(i-1,j) && check(i+1,j) && check(i,j+1) && check(i,j-1)){
				x=i,y=j;
				return true;
			}
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出流加速
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mz[i][j];
			if(mz[i][j]=='*')
				cnt++;//统计图中"*"的个数
		}
	}
	if(!dfs(n,m)){//如果图中没有中间点，直接返回
		cout<<"NO"<<endl;
		return 0;
	}
	k=x+1;
	while(k<=n && mz[k][y]=='*'){//枚举右侧
		ans++;
		k++;
	}
	k=x-1;
	while(k>=1 && mz[k][y]=='*'){//枚举左侧
		ans++;
		k--;
	}
	k=y+1;
	while(k<=m && mz[x][k]=='*'){//枚举上面
		ans++;
		k++;
	}
	k=y-1;
	while(k>=1 && mz[x][k]=='*'){//枚举下面
		ans++;
		k--;
	}
	if(ans==cnt)//判断是否相等
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
```


---

## 作者：oimaster (赞：0)

我们很容易发现这个 `+` 的中心上下左右都有 `*`。

运用这个特点，我们就可以枚举整个字符矩阵。当满足条件时跳出。如果没有找到就说明不存在 `+`，输出 $-1$。

然后我们假设中心点位于 $(x,y)$，显然 $(x-1,y)$，$(x+1,y)$，$(x,y-1)$，$(x,y+1)$ 都是 `*`。

接下来，为了判断没有多余的 `*`，我们可以使用往四周扩散的方法。准确地说，就是使用循环向上遍历所有为 `*` 地格子，当到 `.` 后就停止，每次可以把当前格子改成 `.`，为了方便下一步操作。以同样的方法向左、向右、向下。

最后，当我们四个方向都扩散完后，我们就知道这个 `+` 所有的格子都被还原成 `.` 了。这时候需要判断矩阵里还有没有 `*` 即可判断有没有多余的字符。

时间复杂度：$\text{O}(wh)$。

注意：在扩散时，我们要注意第一次扩散完后，所处的中心格可能也被设成 `.`，可能导致后面循环无法正常执行。

```cpp
#include<iostream>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	char c[n+2][m+2];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			cin>>c[i][j];
	int x,y;
	x=-1;
	y=-1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(c[i][j]=='*'&&
				c[i-1][j]=='*'&&
				c[i+1][j]=='*'&&
				c[i][j-1]=='*'&&
				c[i][j+1]=='*'){
					x=i;
					y=j;
					break;
				}
	if(x==-1&&y==-1){
		cout<<"NO"<<endl;
		return 0;
	}
//	cout<<x<<' '<<y<<endl;
	int tx,ty;
	tx=x;
	ty=y;
	while(tx>0&&c[tx][ty]=='*'){
		c[tx][ty]='.';
		--tx;
	}
	tx=x+1;
	while(tx<=n&&c[tx][ty]=='*'){
		c[tx][ty]='.';
		++tx;
	}
	tx=x;
	--ty;
	while(ty>0&&c[tx][ty]=='*'){
		c[tx][ty]='.';
		--ty;
	}
	ty=y+1;
	while(ty<=m&&c[tx][ty]=='*'){
		c[tx][ty]='.';
		++ty;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(c[i][j]!='.'){
				cout<<"NO"<<endl;
				return 0;
			}
	cout<<"YES"<<endl;
	return 0;
}
```

---

## 作者：Remake_ (赞：0)

题解全是$n^3$的啊，蒟蒻自己搞出了一个大常数的$n^2$做法，发篇题解~。

首先是我们知道对于每一行或者每一列必然只有一段连续的$1$，否则就是不合法的，直接退出。

然后统计一下每行每列$1$的个数，以及矩阵中总共$1$的个数。

最后枚举每个点，看一下他自己及其上下左右是不是都为```*```，同时我们还需要判断一下是不是所有的$1$都在这行这列上面。

如何判断呢，需要用到一个简单的容斥，我们知道:

这行这列中$1$的个数$=$这行中$1$的个数$+$这列中$1$的个数$-1$

为啥要$-1$呢？因为中心点被计算了两次~

所以判一下这行这列中$1$的个数与矩阵中$1$的总个数相不相等即可。

至此，这道题被我们用$n^2$过掉了。

然后为啥别的$n^3$算法吊打了我的$n^2$呢？其实是因为CF数据水，跑不满。

上一下代码吧：
```cpp
#include <bits/stdc++.h>
#define OVER_N cout << "NO", exit(0);
#define OVER_Y cout << "YES", exit(0);
using namespace std;
int w, h, onl = 1, cnt[505], cntt[505], tot;
char c[505][505];
string awa;
bool pd(string s)
{
    int p = -1;
    for (int i = 0; i < s.size(); i++)
    {
        if (!p && s[i] == '*')
            return false;
        s[i] == '*' ? p = 1 : p == -1 ? p = -1 : p = 0;
    }
    return true;
}
int main()
{
    cin >> w >> h;
    for (int i = 1; i <= w; i++)
        for (int j = 1; j <= h; j++)
        {
            cin >> c[i][j];
            tot += c[i][j] == '*';
            cnt[i] += c[i][j] == '*';
            cntt[j] += c[i][j] == '*';
        }
    for (int i = 1; i <= w; i++)
    {
        awa = "";
        for (int j = 1; j <= h; j++)
            awa += c[i][j];
        if (!pd(awa))
            OVER_N
    }
    for (int i = 1; i <= h; i++)
    {
        awa = "";
        for (int j = 1; j <= w; j++)
            awa += c[j][i];
        if (!pd(awa))
            OVER_N
    }
    for (int i = 1; i <= w; i++)
        for (int j = 1; j <= h; j++)
            if (c[i + 1][j] == '*' && c[i - 1][j] == '*' && c[i][j] == '*' && c[i][j - 1] == '*' && c[i][j + 1] == '*' && cnt[i] + cntt[j] - 1 == tot)
                OVER_Y
    OVER_N
}
```


---

## 作者：ZVitality (赞：0)

看了一下题解，虽然大多思路都相同，但是我觉得我的是最好看且最容易理解的。（有些题解用了一些奇奇怪怪的位运算真的很难看且没有必要）

思路很好想，枚举每一个点为中心，然后就可以往上下左右延申，最后判断它为`*`的总个数是否和这个“十字”个数相同就好了。

因为是简单题，我就直接放一下代码吧。

```.cpp
#include <bits/stdc++.h>
using namespace std;
 
int w , h , sum , ans;
bool Map[ 505 ][ 505 ];
char c;
 
int Check( int x , int y ) {
	int cnt = 1 , ans1 , ans2 , ans3 , ans4;//注意，这四个变量是对上下左右是否有“*”的判断，如果没有就是不行的。具体问题可以看代码后面的数据。
    ans1 = ans2 = ans3 = ans4 = 0;
	for( int i = x - 1 ; i >= 1 && Map[ i ][ y ] ; i-- , cnt++ , ans1 = 1 );
	for( int i = x + 1 ; i <= w && Map[ i ][ y ] ; i++ , cnt++ , ans2 = 1 );
	for( int i = y - 1 ; i >= 1 && Map[ x ][ i ] ; i-- , cnt++ , ans3 = 1 );
	for( int i = y + 1 ; i <= h && Map[ x ][ i ] ; i++ , cnt++ , ans4 = 1 );
    if( !ans1 || !ans2 || !ans3 || !ans4 ) return 0;
	return cnt == sum;
}
 
int main() {
	scanf( "%d%d" , &w , &h );
	for( int i = 1 ; i <= w ; i++ )
		for( int j = 1 ; j <= h ; j++ ) {
			cin >> c;
			if( c == '*' ) sum++ , Map[ i ][ j ] = 1;
		}
	for( int i = 1 ; i <= w ; i++ )
		for( int j = 1 ; j <= h ; j++ )
			if( Map[ i ][ j ] )
				if( Check( i , j ) )
					ans++;
	puts( ans == 1 ? "YES" : "NO" );
	return 0;
}
```

Hack数据：

```.cpp
.*.
**.
.*.
```

这是不行的。

---

