# Exercising Walk

## 题目描述

给定一个矩形，左下角顶点坐标为$(x_1,y_1)$，右上角顶点坐标为$(x_2,y_2)$。现在有一个起点$(x,y)$,以及四个数$a,b,c,d$,问能否从起点开始走若干步（向左，向右，向上或向下），使向左、右、下、上分别**共**走了$a,b,c,d$步。

## 样例 #1

### 输入

```
6
3 2 2 2
0 0 -2 -2 2 2
3 1 4 1
0 0 -1 -1 1 1
1 1 1 1
1 1 1 1 1 1
0 0 0 1
0 0 0 0 0 1
5 1 1 1
0 0 -100 -100 0 100
1 1 5 1
0 0 -100 -100 100 0```

### 输出

```
Yes
No
No
Yes
Yes
Yes```

# 题解

## 作者：iMya_nlgau (赞：3)

## CF1332A 【Exercising Walk】

这道题给定了向左，右，下，上走的步数 $a,b,c,d$.

所以无论怎么走，水平方向上一定向右走了$(b-a)$步，竖直方向上向上走了$(d-c)$步，即最终位置为 $(x+b-a, y+d-c)$，只要判断这个位置在不在 $x_1,y_1,x_2,y_2$ 的范围内就可以了.

需要注意的是，即使 $b-a=0$ $($或 $d-c=0)$，如果 $x_1=x_2$ $($或$y_1=y_2)$，依然无路可走.

下面是$AC$代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int x,y,x1,y1,x2,y2;
		scanf("%d%d%d%d%d%d",&x,&y,&x1,&y1,&x2,&y2);
		int right=x+b-a,up=y+d-c;
		if(right<x1||right>x2||up<y1||up>y2
					||x1==x2&&a||y1==y2&&c){
			puts("No"); continue;
		}
		puts("Yes");
	}
	return 0;
}
```



---

## 作者：tuzhewen (赞：2)

做法十分显然，我们用一个变量存**向左走的步数减去向右走的步数**然后用另一个变量存**向上走的步数减去向走走的步数**，这样他们就互相抵消了一部分，最后在用原始的坐标去**减去**（为什么不是加上呢？因为我们上面是用**左**减去**右**，**上**减去**下**，如果说得到的是正数，那么我们就向左/上走，如果是负数则相反）这两个变量然后判断有没有出界即可。

但是要注意特判，如果说这只猫被困在了原地，左右都不能走一步或者上下都不能走一步（前提是我们必须要走左右的或者上下的），那么我们就`puts("NO")`然后`continue`

### ~~废话不多说~~上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int T;
ll a,b,c,d;
ll x_1,y_1;
ll x,y,n1,m1,n2,m2;
bool check(ll x,ll y) {
	if(x<n1||y<m1) return false;
	if(x>n2||y>m2) return false;
	return true;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        	scanf("%lld%lld%lld%lld%lld%lld",&x,&y,&n1,&m1,&n2,&m2);//以上输入
		if((x-1<n1&&x+1>n2&&(a||b))||(y-1<m1&&y+1>m2&&(c||d))) {puts("NO");continue;}//进行特判
		x_1=a-b;//计算差值（左右的）
		y_1=c-d;//计算差值（上下的）
		puts(check(x-x_1,y-y_1)?"YES":"NO");//判断&输出
        }
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1332A)

## 题目分析

本题虽然有四个方向，但实际上无论我们走了多少步，横坐标一定是 $(x - a + b)$ ，而纵坐标一定是 $(x - c + d)$ 。

求出坐标之后，我们需要做的就是进行判断，判断其是否在题目给出的范围中。

## 注意事项

本题需要我们进行特判，判定小猫是否可以活动。如果只能原地踏步，显然情况不合法。

写代码时我们先除去特殊情况，之后再进行判断。

## 贴上代码

```cpp
#include<iostream>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		register int a,b,c,d,x,y,x1,y1,x2,y2;
		cin>>a>>b>>c>>d>>x>>y>>x1>>y1>>x2>>y2;
		if(x1==x2&&y1==y2){
			cout<<"No"<<endl;
			continue;
		}
		else if(x1==x2&&(a||b)){
			cout<<"No"<<endl;
			continue;			
		}
		else if(y1==y2&&(c||d)){
			cout<<"No"<<endl;
			continue;
		}
		register int leftright,updown;
		leftright=x-a+b;updown=y-c+d;
		if(leftright<x1||leftright>x2||updown<y1||updown>y2) cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
}
```

---

## 作者：George1123 (赞：1)

# 题解-Exercising Walk

## [博客中阅读](https://www.cnblogs.com/Wendigo/p/12611937.html#A)

> [Exercising Walk](https://codeforces.com/contest/1332/problem/A)

> $T$ 组测试数据，每次给定 $a,b,c,d,x,y,x_1,y_1,x_2,y_2$。起点是 $(x,y)$，要左走 $a$ 步，右走 $b$ 步，下走 $c$ 步，上走 $d$ 步（这题的 $x$ 和 $y$ 轴与平时相反）。求是否有走法，使得走的过程中总是满足 $x_1\le x\le x_2$，$y_1\le y\le y_2$。如果满足输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

> 数据范围：$1\le T\le 10^3$，$0\le a,b,c,d\le 10^8$，$a+b+c+d\ge 1$，$-10^8\le x_1\le x\le x_2\le 10^8$，$-10^8\le y_1\le y\le y_2\le 10^8$。

本来以为直接**找到最终点看看在不在范围内**就够了，但是后来发现过不了样例。

有一种特殊情况：$[x_1=x]\&[x=x_2]\&[a,b>0]\&[a+b=0]$（一走就走出范围了），答案是 $\texttt{NO}$，你会输出 $\texttt{YES}$。

对于 $y,c,d$ 同理，所以特判一下就过了。

**易错点：**

1. 没看清这题的 $x$ 和 $y$ 轴与平时相反这个特点。
2. 没考虑到特殊情况（你样例都过不了啊）。

**代码：**

```cpp
//Data
int a,b,c,d,x,y,x1,y1,x2,y2;
il int yes(){
	if(a&&b) if(x==x1&&x==x2) return 0;
	if(c&&d) if(y==y1&&y==y2) return 0;
	x-=a,x+=b,y-=c,y+=d;
	return x1<=x&&x<=x2&&y1<=y&&y<=y2;
}

//Main
int main(){
	re int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d%d%d%d%d%d",&a,&b,&c,&d,&x,&y,&x1,&y1,&x2,&y2);
		if(yes()) puts("YES"); else puts("NO");
	}
	return 0;
}
```
---

**祝大家学习愉快！**

---

## 作者：xrdrsp (赞：1)

这是本人的第 $003$ 篇题解。

这个题作为 CF div.2 T1，还是比较水的（我比较菜）。

数据范围 $10^8$，暴力搜索肯定不行。

这时就要想一些省时间的方法了。

首先，可以模拟样例找规律。

可以发现，只要小猫有足够的活动空间（走完要求的路线之后还在区域内）就不会走丢。且小猫至少有 $1\times1$ 的空间（除非不需要走路）。

所以就可以写代码了。

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int l, r, d, u; 			// 左、右、下、上。
        int x, y, x1, x2, y1, y2;	// 小猫位置坐标和两个限制坐标。
        scanf("%d%d%d%d", &l, &r, &d, &u);
        scanf("%d%d%d%d%d%d", &x, &y, &x1, &y1, &x2, &y2);
        x = r - l + x;				// 计算：小猫在走完要求的路线后在不在规定的范围里。（x 坐标）
        y = u - d + y;				// 计算：小猫在走完要求的路线后在不在规定的范围里。（y 坐标）
        if (x >= x1 && x <= x2 &&
        y >= y1 && y <= y2 && 		// 判断走完后还在范围里。
        (x2 > x1 || l + r == 0) &&
        (y2 > y1 || u + d == 0)) {	// 判断是否有空间。l + r == 0 和 u + d == 0 分别表示 l == 0 && r == 0 和 u == 0 && d == 0。因为 l、r、d、u 均为非负整数。
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
```

---

## 作者：JustinXiaoJunyang (赞：0)

思维难度普及-，代码难度入门。

思路分析：

首先分析样例：

$a=3$ $b=2$ $c=2$ $d=2$，显然，这里从$(0,0)\rightarrow(-1,0)(-1,0)$ 仅需把横坐标左移一个，那么只有 $a=3$ 大概就是特殊的了。

这个是题面自带的样例描述路径：

$(0,0)\rightarrow(-1,0)\rightarrow(-2,0)\rightarrow (-2,1)\rightarrow (-2,2)\rightarrow(-1,2)\rightarrow(0,2)\rightarrow(0,1)\rightarrow(0,0)\rightarrow(-1,0)$

当然，还要引入一道题：

从一个点出发，可以走水平或垂直的路在回到该点。那么一定左走等于右走且上走等于下走，引入了这个思路。

所以方法是：

计算 $a-c$ 及 $b-d$（众所周知不用绝对值），相当于省略了一部分。

接着初始坐标间这两个差，判断是否超出了范围！那么直接没戏输出 `NO`。

参考代码：

```cpp
#include <iostream>
using namespace std;

long long a, b, c, d, xcha, ycha, x, y, x1, y1, x2, y2;
bool chk(long long p, long long q)
{
	if (p < x1 || q < y1) return 0;
	if (p > x2 || q > y2) return 0;
	else return true;
}

int main()
{
    int t;
    cin >> t;
	while (t--)
	{
		cin >> a >> b >> c >> d;
        cin >> x >> y >> x1 >> y1 >> x2 >> y2;
		if ((x - 1 < x1 && x + 1 > x2 && (a || b)) || (y - 1 < y1 && y + 1 > y2 && (c || d)))
		{
		    cout << "No" << endl;
		    continue;
		}
		xcha = a - b;
		ycha = c - d;
		if (chk(x - xcha, y - ycha)) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
```

---

## 作者：AutumnKite (赞：0)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

[题目传送门](https://codeforces.com/contest/1332/problem/A)

### 题意

在二维平面上有一个矩形 $(x_1,y_1),(x_2,y_2)$，你初始在 $(x,y)$。你被强制规定往左、右、上、下四个方向分别走恰好 $a,b,c,d$ 步。

你可以任意调整走的顺序。判断是否可以不走出这个矩形。

$0\le a,b,c,d\le 10^8,-10^8\le x_1\le x\le x_2\le 10^8,-10^8\le y_1\le y\le y_2\le 10^8$。

### 题解

如果 $a+b \ge 1$ 且 $x_1=x=x_2$，那么一定不合法。纵坐标同理。

首先因为走的步数是强制规定的，所以我们可以得到终点 $(x_t,y_t)$。

我们考虑先在原地不断左右来回走，把 $a,b$ 抵消成只剩一个。然后直接沿着剩下那个的方向走完即可。纵坐标同理。

可以发现，这样走一定能始终保持在 $(x,y)$ 和 $(x_t,y_t)$ 形成的矩形内。

那么我们只要判断 $(x_t,y_t)$ 是否在 $(x_1,y_1),(x_2,y_2)$ 这个矩形内即可。

### 代码

```cpp
int a, b, c, d, x, y, x1, y1, x2, y2;
void solve(){
	read(a), read(b), read(c), read(d);
	read(x), read(y), read(x1), read(y1), read(x2), read(y2);
	if ((a || b) && x1 == x2) return prints("No"), void(0);
	if ((c || d) && y1 == y2) return prints("No"), void(0);
	x = x + b - a, y = y + d - c;
	if (x1 <= x && x <= x2 && y1 <= y && y <= y2) return prints("Yes"), void(0);
	prints("No");
}
```

---

## 作者：rui_er (赞：0)

这题大概就是把不行的条件判掉，剩下的都是可以的。

首先，因为 $a+b+c+d\geq 1$，所以 $x_1=x_2$ 且 $y_1=y_2$ 的显然不行。

其次，如果一个方向上不能走，即 $x_1=x_2$ 或 $y_1=y_2$，且那个方向要走的步数不为 $0$，这种情况也不行。

然后，因为反方向可以相互抵消（左→右回到原位），可以先把反方向减去它们的最小值，然后判断空间是否足够即可。

完整代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int T;
int a, b, c, d, x, y, x1, y1, x2, y2; 

int main()
{
	cin>>T;
	while(T--)
	{
		a = b = c = d = x = y = x1 = y1 = x2 = y2 = 0;
		cin>>a>>b>>c>>d>>x>>y>>x1>>y1>>x2>>y2;
		if(x1 == x2 && y1 == y2)
		{
			cout<<"No"<<endl;
			continue;
		}
		if(x1 == x2 && (a || b))
		{
			cout<<"No"<<endl;
			continue;
		}
		if(y1 == y2 && (c || d))
		{
			cout<<"No"<<endl;
			continue;
		}
		int tmp = min(a, b);
		a -= tmp;
		b -= tmp;
		tmp = min(c, d);
		c -= tmp;
		d -= tmp;
		if(x - x1 < a || x2 - x < b || y - y1 < c || y2 - y < d)
		{
			cout<<"No"<<endl;
			continue;
		}
		cout<<"Yes"<<endl;
	}
	return 0;
}
```

---

## 作者：codemap (赞：0)

~~一道比较水的题~~

因为行走的步数可以交换,所以完全可以先往上往下轮流走完上下的步数,然后往左往右轮流走完左右的步数

这样走显然是最优的,也就是说如果$x+(b-a)$和$y+(d-c)$均在范围内就可以,否则则不行

这里要注意一点,$CF$友善地在样例里做了提示,如果上下或左右的范围只有一个格,而且要动,则不行

上代码

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,i,a,b,c,d,x,y,x1,y1,x2,y2;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a>>b>>c>>d>>x>>y>>x1>>y1>>x2>>y2;//全在一行输入
		if(x1==x&&x2==x&&(a!=0||b!=0))//如果上下的范围只有一格而且要动
		{
			cout<<"No"<<endl;//不行
			continue;//直接跳过
		}
		if(y1==y&&y2==y&&(c!=0||d!=0))//如果左右的范围只有一格而且要动
		{
			cout<<"No"<<endl;//不行
			continue;//直接跳过
		}
		if(x+b-a>=x1&&x+b-a<=x2&&y+d-c>=y1&&y+d-c<=y2)//在范围内
			cout<<"Yes"<<endl;//则可以
		else//否之
			cout<<"No"<<endl;//则不可以
	}
	return 0;//结束
}
```
# 请勿抄袭

---

## 作者：gyh20 (赞：0)

特判是否能往上下左右。

再特判最终位置是否合法。
```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int t,n,m,a,b,c,d,x,y,xx,yy,xxx,yyy;
signed main(){
	t=read();
	while(t--){
		a=read(),b=read(),c=read(),d=read();
		x=read();y=read();xx=read();yy=read();xxx=read();yyy=read();
		xx-=x;yy-=y;xxx-=x;yyy-=y;
		if((a||b)&&(!xx&&!xxx)){
			puts("NO");
			continue;
		}
		if((c||d)&&(!yy&&!yyy)){
			puts("NO");
			continue;
		}
		if((-(a-b)<xx)||(b-a>xxx)||(-(c-d)<yy)||(d-c>yyy)){
			puts("NO");
			continue;
		}
		puts("YES");
	}
}
```


---

## 作者：dead_X (赞：0)

## 1 题意简述
给定一个初始点 $(x,y)$ ，并再给定一个左上角为 $(x1,y1)$ ，右下角为 $(x2,y2)$ 的矩形，再给定四个整数 $u,d,l,r$，问能不能设计一个长度为 $u+d+l+r$ 的移动序列，其中分别有 $u,d,l,r$ 个使该点向上，下，左，右移动1单位长度的操作，使得该点始终在矩形内或矩形上。
## 2 思路简述
细节奇多……

首先基本思路是向上向下交替，最后剩下的一次性走完，左右同理

但是如果 $l=r=1,x=x1=x2$，那么应该是不行的，因为无论先走哪边都会出去。

所以加一个小特判。
## 3 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int main()
{
	int T=read();
	while(T--)
	{
		int a=read(),b=read(),c=read(),d=read();
		int n=read(),m=read(),o=read(),p=read(),q=read(),r=read();
		if((a||b) && n==o && o==q) 
		{
			cout<<"No"<<endl;
			continue;
		 } 
		 if((c||d) && m==p && p==r) 
		{
			cout<<"No"<<endl;
			continue;
		 } 
		if(a>b) if(a-b>n-o)
		{
			cout<<"No"<<endl;
			continue;
		 }  else c=c;
		else if(b-a>q-n) 
		{
			cout<<"No"<<endl;
			continue;
		}
		if(c>d) if(c-d>m-p)
		{
			cout<<"No"<<endl;
			continue;
		} else c=c;
		else if(d-c>r-m)
		{
			cout<<"No"<<endl;
			continue;
		}
		cout<<"Yes"<<endl;
	}
	return 0;
}
```
## 4 总结
粪题 耗时略长

---

