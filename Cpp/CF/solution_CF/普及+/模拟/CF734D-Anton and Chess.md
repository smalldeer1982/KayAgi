# Anton and Chess

## 题目描述

Anton喜欢下棋与编程，所以他决定写一个国际象棋游戏。然而，他认为8x8的棋盘太简单了，因此这个棋盘是无限大的。

他的第一个任务是检查当前状态下是否被将军，他并不知道如何实现这点，因此向你求助。

棋盘上有一个白色方的王与n个黑色方的棋子，它们仅由车、象和后组成。当至少一个黑色方的棋子可以在一步内移动到白色方王所在的格子时被视为将军。

帮助Anton写一个程序，在给定所有棋子的位置时判定白色方的王是否被将军。

以下是各种棋子的移动方式：

- 象可以斜着移动，格子不限。
- 车可以水平或垂直移动，格子不限。
- 后可以水平、垂直或斜着移动，格子不限。
- 所有的棋子不能越过已经占用的格子。

## 样例 #1

### 输入

```
2
4 2
R 1 1
B 1 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
4 2
R 3 3
B 1 5
```

### 输出

```
NO
```

# 题解

## 作者：A_R_O_N_A (赞：6)

[洛谷链接](https://www.luogu.com.cn/problem/CF734D)

[CF 原题链接](https://codeforces.com/problemset/problem/734/D)

## 题目大意

给你一个国际象棋的棋盘。再给你白方王，黑方车，象，后的坐标，让你判断白方王是否被将军。判断规则同现实中的国际象棋：

1. 后可以走斜线和直线，距离不限。

1. 象只能走斜线，距离不限。

1. 车只能走直线，距离不限。

1. 棋子不能越过已被占用的格子。

1. 如果白方王在任一黑方棋子的移动路径上，则视为将军。

## 题目分析

我们约定：$(x,y)$ 表示**第 $x$ 行第 $y$ 列的棋子。**

第一步先看数据范围：

对于任一棋子的坐标，有 $-10^9\le x,y\le 10^9$。

对于棋子的数量 $n$ 满足 $1\le n \le 5\times 10^5$。

首先一个一个模拟棋子的移动显然是不行的，因为最大距离可以达到 $10^{10}$，别说 $10^5$ 个棋子了，就算是只有 $10$ 个棋子也会 TLE，考虑优化。

我们注意到：**棋子不能越过已被占用的格子**，所以说被遮挡住的棋子实际上对白方王没有任何影响。又注意到白方王显然只能被上，下，左，右，左上，右上，左下，右下总共八个方向上的棋子将军，那么我们就可以对于白方王的每一个方向，枚举所有的黑方棋子的坐标，并找出在这个方向上面离王最近的棋子。再判断白方王是否能被这些棋子将军即可。

这样的时间复杂度显然是 $O(n)$ 的，可以通过此题。

需要注意的是，棋子离国王的距离最大可到达 $10^{10}$，需要开 `long long`。

## CODE

代码较长，这里只给主函数了，免得文章显得臃肿。

```cpp
ll kx,ky,n,mndis=LLONG_MAX;//国王的坐标，数量以及最近的距离
struct node{
	char type;
	ll nowx,nowy;
}a[500005];
struct danger{
	char type;
	ll nowx,nowy;
}e[9];//最多只会有八个棋子影响国王
//可以思考一下为什么
int main(){
	n=read();
	kx=read();ky=read();
	for(int i=1;i<=n;i++){
		cin>>a[i].type;
		a[i].nowx=read();
		a[i].nowy=read();
	}
	for(int i=1;i<=n;i++){//左上 
		if(a[i].nowx-kx==a[i].nowy-ky&&a[i].nowx-kx<0&&mndis>abs(a[i].nowx-kx)){
			e[1]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowx-kx);//距离可用绝对值储存，更好判断
		}
	}
	mndis=LLONG_MAX;//枚举完一个方向之后记得重置最小距离为极大值
	for(int i=1;i<=n;i++){//上 
		if(a[i].nowy==ky&&a[i].nowx-kx<0&&mndis>abs(a[i].nowx-kx)){
			e[2]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowx-kx);
		}
	}
	mndis=LLONG_MAX;
	for(int i=1;i<=n;i++){//右上 
		if(a[i].nowx-kx==ky-a[i].nowy&&a[i].nowx-kx<0&&mndis>abs(a[i].nowx-kx)){
			e[3]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowx-kx);
		}
	}
	mndis=LLONG_MAX;
	for(int i=1;i<=n;i++){//左 
		if(a[i].nowx==kx&&a[i].nowy-ky<0&&mndis>abs(a[i].nowy-ky)){
			e[4]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowy-ky);
		}
	}
	mndis=LLONG_MAX;
	for(int i=1;i<=n;i++){//右 
		if(a[i].nowx==kx&&a[i].nowy-ky>0&&mndis>abs(a[i].nowy-ky)){
			e[5]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowy-ky);
		}
	}
	mndis=LLONG_MAX;
	for(int i=1;i<=n;i++){//左下 
		if(kx-a[i].nowx==a[i].nowy-ky&&a[i].nowy-ky<0&&mndis>abs(a[i].nowy-ky)){
			e[6]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowy-ky);
		}
	}
	mndis=LLONG_MAX;
	for(int i=1;i<=n;i++){//下 
		if(a[i].nowy==ky&&a[i].nowx-kx>0&&mndis>abs(a[i].nowx-kx)){
			e[7]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowx-kx);
		}
	}
	mndis=LLONG_MAX;
	for(int i=1;i<=n;i++){//右下 
		if(kx-a[i].nowx==ky-a[i].nowy&&a[i].nowx-kx>0&&mndis>abs(a[i].nowx-kx)){
			e[8]={a[i].type,a[i].nowx,a[i].nowy};
			mndis=abs(a[i].nowx-kx);
		}
	}
  //所有方向枚举完毕
  //接下来判断每一个方向上距离最近的棋子能否将军
	if(e[1].type=='B'||e[1].type=='Q'){//左上，象和后可将军
		puts("YES");
		return 0;
	}
	if(e[2].type=='R'||e[2].type=='Q'){//上，车和后可将军
		puts("YES");
		return 0;
	}
	if(e[3].type=='B'||e[3].type=='Q'){//右上，象和后可将军
		puts("YES");
		return 0;
	}
	if(e[4].type=='R'||e[4].type=='Q'){//左，车和后可将军
		puts("YES");
		return 0;
	}
	if(e[5].type=='R'||e[5].type=='Q'){//右，车和后可将军
		puts("YES");
		return 0;
	}
	if(e[6].type=='B'||e[6].type=='Q'){//左下，象和后可将军
		puts("YES");
		return 0;
	}
	if(e[7].type=='R'||e[7].type=='Q'){//下，车和后可将军
		puts("YES");
		return 0;
	}
	if(e[8].type=='B'||e[8].type=='Q'){//右下，象和后可将军
		puts("YES");
		return 0;
	}
	puts("NO");
	return 0;
}
```

## 总结

思维难度中等，代码难度中等，码量较大，是一个不错的模拟题。

---

## 作者：泠小毒 (赞：1)

# Anton and Chess
给定一个无限大的棋盘，有1个白色的王和n个黑色的车(R)、象(B)、后(Q)

车只能横着走，象只能斜着走，后既可以横着走也可以斜着走

求此时白色的王有没有被将军，输出"YES"或"NO"
## 解法
找到白色的王
```
上、下、左、右、上左、上右、下左、下右
```
这八个方位的第一个棋子

分别检验它是否能将军即可
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{char opt;int x,y;}a[500010];
int n,x,y,U,D,L,R,UL,UR,DL,DR,flg;
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++)
	{
		for(a[i].opt=getchar();a[i].opt!='R'&&a[i].opt!='B'&&a[i].opt!='Q';a[i].opt=getchar());
		scanf("%d%d",&a[i].x,&a[i].y);
		if(a[i].x==x)
		{
			if(a[i].y>y)
			{
				if(U==0||a[i].y<a[U].y)
					U=i;
			}
			else
			{
				if(D==0||a[i].y>a[D].y)
					D=i;
			}
		}
		if(a[i].y==y)
		{
			if(a[i].x>x)
			{
				if(R==0||a[i].x<a[R].x)
					R=i;
			}
			else
			{
				if(L==0||a[i].x>a[L].x)
					L=i;
			}
		}
		if(a[i].x-x==a[i].y-y)
		{
			if(a[i].x>x)
			{
				if(UR==0||a[i].x<a[UR].x)
					UR=i;
			}
			else
			{
				if(DL==0||a[i].x>a[DL].x)
					DL=i;
			}
		}
		if(a[i].x-x==y-a[i].y)
		{
			if(a[i].x>x)
			{
				if(DR==0||a[i].x<a[DR].x)
					DR=i;
			}
			else
			{
				if(UL==0||a[i].x>a[UL].x)
					UL=i;
			}
		}
	}
	if(a[U].opt=='R'||a[U].opt=='Q')flg=1;
	if(a[D].opt=='R'||a[D].opt=='Q')flg=1;
	if(a[L].opt=='R'||a[L].opt=='Q')flg=1;
	if(a[R].opt=='R'||a[R].opt=='Q')flg=1;
	if(a[UL].opt=='B'||a[UL].opt=='Q')flg=1;
	if(a[UR].opt=='B'||a[UR].opt=='Q')flg=1;
	if(a[DL].opt=='B'||a[DL].opt=='Q')flg=1;
	if(a[DR].opt=='B'||a[DR].opt=='Q')flg=1;
	if(flg)puts("YES");else puts("NO");
	return 0;
}
```

---

## 作者：Escapism (赞：1)

模拟题。

# 题意

在一个无限的棋盘上有一个白方王与黑方的后、车和象。问白方王是否被将了。

# 思路

有两种，一种是判断每一个黑方棋子是否将到王；另一种是判断王的八个方向有没有可以将到王的棋子。

显然第二种的效率比第一种高的多，因而这里主要讲解第二种。

在王的八个方向能将到王的棋子有：

- 上：车、后
- 下：车、后
- 左：车、后
- 右：车、后
- 左上：主教、后
- 左下：主教、后
- 右上：主教、后
- 右下：主教、后

得出这一信息后，我们只需要得出在八个方向上第一个棋子是那种即可。如果是上面可以将王的子之一，那么就输出 yes,否则就 no。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 * 5 + 5;
struct node{
    char chess;
    int x,y;
} a[MAXN];
int n,x,y,up,dw,le,ri,lu,ld,ru,rd;
bool flag;
int main(){
	cin>>n>>x>>y;
	for(int i = 1;i <= n;i++){
		for(a[i].chess = getchar();a[i].chess != 'R' && a[i].chess != 'B' && a[i].chess != 'Q';a[i].chess = getchar());
		cin>>a[i].x>>a[i].y;
		if(a[i].x == x){
			if(a[i].y > y){
				if(up == 0 || a[i].y < a[up].y)
					up=i;
			}
			else{
				if(dw == 0 || a[i].y > a[dw].y)
					dw = i;
			}
		}
		if(a[i].y == y){
			if(a[i].x > x){
				if(ri == 0 || a[i].x < a[ri].x)
					ri = i;
			}
			else{
				if(le == 0 || a[i].x > a[le].x)
					le = i; 
			}
		}
		if(a[i].x - x == a[i].y - y){
			if(a[i].x > x){
				if(ru == 0 || a[i].x < a[ru].x)
					ru = i;
			}
			else{
				if(ld==0 || a[i].x > a[ld].x)
					ld = i;
			}
		}
		if(a[i].x - x == y - a[i].y){
			if(a[i].x > x){
				if(rd == 0 || a[i].x < a[rd].x)
					rd= i;
			}
			else{
				if(lu == 0 || a[i].x > a[lu].x)
					lu = i;
			}
		}
	}
	if(a[up].chess == 'R' || a[up].chess == 'Q')flag = 1;
	if(a[dw].chess == 'R' || a[dw].chess == 'Q')flag = 1;
	if(a[le].chess == 'R' || a[le].chess == 'Q')flag = 1;
	if(a[ri].chess == 'R' || a[ri].chess == 'Q')flag = 1;
	if(a[lu].chess == 'B' || a[lu].chess == 'Q')flag = 1;
	if(a[ru].chess == 'B' || a[ru].chess == 'Q')flag = 1;
	if(a[ld].chess == 'B' || a[ld].chess == 'Q')flag = 1;
	if(a[rd].chess == 'B' || a[rd].chess == 'Q')flag = 1;
	if(flag == true) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```


---

## 作者：lijianACE (赞：0)

## Anton and Chess 题解    
通过证明： 
![](https://cdn.luogu.com.cn/upload/image_hosting/qgfhhru7.png) 

[洛谷传送门](https://www.luogu.com.cn/problem/CF734D)  

[CF 传送门](https://codeforces.com/contest/734/problem/D)  
题目解析：现已知白王的位置，求在他的八个方是否存在棋子能够威胁道他。  

题意很简单，正当我打了一个暴力交了上去。  
_**TLE**_   
哈哈，忘看范围了，喜提 TLE。  

仔细一看范围。 
>
> $1\le n\le 5\times 10^5$
> 
这个范围极大，所以最后代码要么 $O(N)$，要么 $O(\log_{2}{N})$，要么就是 $O(1)$。  
考虑到输入就要 $O(N)$，所以基本只可能是 $O(N)$ 做法。  

具体怎么做呢？  

做过八皇后的可能 DNA 已经动了，但别急，这里做成类似八皇后的肯定会炸，因为题目有一个限制条件。  
>
>**所有的棋子不能越过已经占用的格子。**
>
如果一个一个判定过去，时间估计得爆。  
但古话说得好，“成也萧何，败也萧何”，这题的限制条件，同时也是解题的关键。  

我们思考后就会发现，白王只有八个方向能攻击到他，挺多就八个棋子对他可能有威胁。（因为棋子不能跳过棋子）  
所以其实很简单，只要定义个结构体数组，分别存每个方向上存在的棋子和距离，当在这儿条线上有其他棋子并且距离更短，就更新它。

怎么判断是否在同一条线上呢？我打了个表出来给大家看。  
| $x-n,y+n(1)$ | $x,y+n(8)$ | $x+n,y+n(7)$ |
|:-:|:-:|:-:|
| $x-n,y(2)$ | $x,y$ | $x+n,y(6)$ |
| $x-n,y-n(3)$ | $x,y-n(4)$ | $x+n,y-n(5)$ |  

所以，只需要根据上面数值的规律进行更改就行了。  
当然，我猜可能有人会问，数组所标记方向（下标为后面括号里的值）的顺序能改吗？  
**我的建议是：最好不要。**  
如果你稍微研究一下上面的顺序，就会发现：  

**当 $i\equiv 0\pmod{2}$ 的时候，棋子必须竖直移动，当 $i\equiv 1\pmod{2}$ 时候，棋子必须沿对角线移动。**  

有了这个方法，就不须一个一个枚举过去了，能节省好几行代码。（但输入的代码还是很长）  
思考难度较低，代码长度中。（但有规律）  
Code:   
 
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y,rp=0;//防止人品爆int（doge
const long long C=5*1e9;
struct threat{
	long long j;
	char name;
};
threat a[9];
int main(){
	for(int i=1;i<=8;i++){
		a[i].j=C;
		a[i].name='N';
	}
	int n;
	scanf("%d",&n);
	char c;
	long long x_ , y_;
	scanf("%lld%lld",&x,&y);
	for(int i=1;i<=n;i++){
		c=getchar();
		if(c!='Q'&&c!='B'&&c!='R') c=getchar();//如果是换行符就再输一次
		scanf("%lld%lld",&x_ ,&y_ );
		rp++;//rp+=10086
		if(x_==x){//下面的代码很长，建议配合上面的图食用
			if(y<y_&&a[8].j>y_-y){
				a[8].j=y_-y;
				a[8].name=c;
			}
			if(y>y_&&a[4].j>y-y_){
				a[4].j=y-y_;
				a[4].name=c;
			}
		}
		if(y_==y){
			if(x<x_&&a[6].j>x_-x){
				a[6].j=x_-x;
				a[6].name=c;
			}
			if(x>x_&&a[2].j>x-x_){
				a[2].j=x-x_;
				a[2].name=c;
			}
		}
		if(x_-y_==x-y){
			if(x_>x&&a[7].j>x_-x){
				a[7].j=x_-x;
				a[7].name=c;
			}
			if(x_<x&&a[3].j>x-x_){
				a[3].j=x-x_;
				a[3].name=c;
			}
		}
		if(x_+y_==x+y){
			if(y<y_&&a[1].j>y_-y){
				a[1].j=y_-y;
				a[1].name=c;
			}
			if(y>y_&&a[5].j>y-y_){
				a[5].j=y-y_;
				a[5].name=c;
			}
		}
	}
	bool f=false;
	for(int i=1;i<=8;i++){
		if(i%2==0){//是否在对角线上
			if(a[i].name=='R'||a[i].name=='Q'){
				f=true;
				break;
			}
		}
		else{
			if(a[i].name=='B'||a[i].name=='Q'){
				f=true;
				break;
			}
		}
	}
	if(f==true){
		printf("YES");
	}
	else{
		printf("NO");
	}
    return 0;
} 
```
题解写的不是很好，望见谅！

如果有误，敬请指导。  

QWQ   
2024.10.25 第一次打回，忘记加空格了

---

## 作者：Jerrycyx (赞：0)

初看以为要棋盘离散化 + 斜向转横竖向 + 车和象分别判断，实际上没有那么复杂。

因为王只会被它上下左右或斜四个方向的棋子吃，所以只需要判断这八个方向离它最近的棋子是否可以吃它即可，其它的一定都会被挡住。

注意代码中 `unordered_map` 或 `map` 常数巨大，$5 \times 10^5$ 数据下跑 $O(N)$ 都有点吃力（$827$ ms），所以当数据更大或者非 $O(N)$ 时应当慎用。

[AC 记录](https://codeforces.com/contest/734/submission/288733124)

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<unordered_map>
#define x0 x000
#define y0 y000 //防CE
using namespace std;

const int N=5e5+5,HAHA=1e9+7; //一个不可能取到的数，随意定就好了
int n,x0,y0;
int pu=-HAHA,pd=HAHA,pl=-HAHA,pr=HAHA;
pair<int,int> plu={-HAHA,-HAHA},pru={-HAHA,HAHA},pld={HAHA,-HAHA},prd={HAHA,HAHA};
unordered_map<int,map<int,char>> ump; //根据测试，unordered_map 套 map 比其它组合略快

bool check() //判断八个方向最近的是否能吃
{
	#define haha(x) ((x!=-HAHA)&&(x!=HAHA))
	if(haha(pl) && ump[x0][pl]!='B') return true;
	if(haha(pr) && ump[x0][pr]!='B') return true;
	if(haha(pu) && ump[pu][y0]!='B') return true;
	if(haha(pd) && ump[pd][y0]!='B') return true;
	
	if(haha(plu.first) && ump[plu.first][plu.second]!='R') return true;
	if(haha(pru.first) && ump[pru.first][pru.second]!='R') return true;
	if(haha(pld.first) && ump[pld.first][pld.second]!='R') return true;
	if(haha(prd.first) && ump[prd.first][prd.second]!='R') return true;
	#undef haha
	
	return false;
}

int main()
{
	scanf("%d%d%d",&n,&x0,&y0);
	for(int i=1;i<=n;i++)
	{
		char op[5]; scanf("%s",op);
		int x,y; scanf("%d%d",&x,&y);
		ump[x][y]=op[0];

    //更新最近点
		#define updmin(s,t) s=min(s,t)
		#define updmax(s,t) s=max(s,t)
		if(x==x0)
		{
			if(y>=y0) updmin(pr,y);
			if(y<=y0) updmax(pl,y);
		}
		if(y==y0)
		{
			if(x>=x0) updmin(pd,x);
			if(x<=x0) updmax(pu,x);
		}
		if(x+y==x0+y0)
		{
			if(x>=x0) updmin(pld.first,x),updmax(pld.second,y);
			if(x<=x0) updmax(pru.first,x),updmin(pru.second,y);
		}
		if(x-y==x0-y0)
		{
			if(x>=x0) updmin(prd.first,x),updmin(prd.second,y);
			if(x<=x0) updmax(plu.first,x),updmax(plu.second,y);
		}
		#undef updmin
		#undef updmax
	}
	if(check()) printf("YES\n");
	else printf("NO\n");
	return 0;
}
```

---

