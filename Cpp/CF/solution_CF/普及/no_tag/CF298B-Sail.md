# Sail

## 题目描述

# 题意
从($s_x$,$s_y$)驶向($e_x$,$e_y$)给出时刻总数t,有四种风向东南西北($E$,$S$,$W$,$N$),每一时刻给出一种风向,$E$$-$>$x$坐标+1,$S$$-$>y坐标-1,$W$$-$>x坐标-1,$N$$-$>y坐标+1,可以选择随风移动也可以选择停留(但都会经过1个时刻)求到达终点所需要的最小时刻。

## 样例 #1

### 输入

```
5 0 0 1 1
SESNW
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 5 3 3 6
NENSWESNEE
```

### 输出

```
-1
```

# 题解

## 作者：_ZML_ (赞：2)

# 思路
没什么好解释的，能离终点更近就走，否则不走。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t,x,y,a,b;
	cin>>t>>x>>y>>a>>q;
	while(t--)
   	  	char q=getchar();
		if(x<a&&q=='E')x++;
		if(x>a&&q=='W')x--;
       		if(y<b&&q=='N')y++;
		if(y>b&&q=='S')y--;
		if(x==a&&y==b){
			cout<<i;
			return 0;
		} 
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：vanueber (赞：1)

[原题传送门-Luogu](https://www.luogu.com.cn/problem/CF298B)

[原题传送门-Codeforces](https://codeforces.com/problemset/problem/298/B)

# 题目大意

给定每天风向，可以选择移动或停留，问最少多少天能到达终点。

# 题目分析

考虑直接贪心，如果当天风向能够离终点更近那么移动，否则停留。

感性理解一下这为什么是正确的：如果当前这一步远离了终点，如终点在上方，可你却往下方移动，那么到达终点就比原来多需要一个向上的风向，这显然会使答案增大。

故若当前风向会使自己离终点更远，这一步停留比这一步移动更优。

于是编写代码时只需注意条件判断与结束判断即可。

# AC_code


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int t;
int sx,sy,ex,ey;
string ss;

int main()
{
	cin>>t>>sx>>sy>>ex>>ey;
	cin>>ss;//读入
	for(int i=0;i<t;i++) //E x+1 S y-1 W x-1 N y+1
	{
		if(sx==ex&&sy==ey)//判断是否到达终点
		{
			cout<<i;
			exit(0);
		}
		switch (ss[i])
		{
			case 'E':
				if(ex>sx)//判断能否离终点更近，下面同理
				{
					sx+=1;
				}
				break;
			case 'S':
				if(ey<sy)
				{
					sy-=1;
				}
				break;
			case 'W':
				if(ex<sx)
				{
					sx-=1;
				}
				break;
			case 'N':
				if(sy<ey)
				{
					sy+=1;
				}
				break;
		}
	}
	if(sx==ex&&sy==ey)//再判断一次（此时是判断经历所有时刻是否到达终点）
	{
		cout<<t<<endl;
		exit(0);
	}
	cout<<-1;
	return 0;
}

```

默哀RMJ，献上CF [AC记录](https://codeforces.com/problemset/submission/298/275675577)

---

## 作者：_Lightning_ (赞：1)

## CF298B Sail

### 思路：

要求最小时刻，只需要在每次输入字符时判断，如果走了能离终点更近就走，否则不走。

### AC Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y,a,i=0,b;
char q;
int main(){
	cin>>t>>x>>y>>a>>b;
	for(int i=1;i<=t;i++){
   	  	cin>>q;
		if(x<a&&q=='E')
			x++;
		if(x>a&&q=='W')
			x--;
       	if(y<b&&q=='N')
			y++;
		if(y>b&&q=='S')
			y--;
		if(x==a&&y==b){
			cout<<i<<'\n';
			return 0;
		} 
	}
	cout<<"-1\n";
	return 0;
}
```

---

## 作者：xuduang (赞：1)

## 题意

给出起点终点和一串指令，指令控制东西南北走，每一个单位时间可以选择按照指令走或停在原地不动，问最快从起点到达终点需要多少个单位时间。

## 分析

每一个指令只能选择走或不走，我们**贪心**算出哪一种选择更有贡献，即更接近终点。

接近终点，就要使前进的方向正确，反方向的指令不走，使我们能接近终点的指令就走，远离的就不动。显然不动比退步要更优。

思路也比较清晰了，就是这么一点，另外注意一下每个字母对应的偏移就好了。

## CODE

```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,sx,sy,ex,ey;
string t;
signed main()
{
	cin>>n>>sx>>sy>>ex>>ey;
	cin>>t;
	for(int i=0;i<t.size();i++)
	{
		char k=t[i];
		if(k=='N')
		{
			if(sy<ey)sy++;
		}
		if(k=='S')
		{
			if(sy>ey)sy--;
		}
		if(k=='W')
		{
			if(sx>ex)sx--;
		}
		if(k=='E')
		{
			if(sx<ex)sx++;
		}
		if(sx==ex&&sy==ey)
		{
			cout<<i+1;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```

---

## 作者：Linzijun_0607 (赞：1)

可以选择不动或者动，那我们只需要看移动对前往终点是否有帮助。能到终点时，就输出。如果到最后都没有，就输出 `-1`。

### 代码:
```
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int t,x,y,a,b;
	cin>>t>>x>>y>>a>>b;
	int i=0;
	while(t--){
		i++;
   	  	char q;
   	  	cin>>q;
		if(x>a&&q=='W')
		    x--;		
		if(x<a&&q=='E')
		    x++;
		if(y>b&&q=='S')
		    y--;       	
		if(y<b&&q=='N')
       	    y++;
		if(x==a&&y==b){
			cout<<i;
			exit(0);
		} 
	}
	puts("-1");
}
```

---

## 作者：XXh0919 (赞：1)

水题一道。

这一道题其实就是说在经过 $t$ 个时间的风力影响下，能否到达终点。其实想到达终点就要判断船只位置，若船只的 $x$ 坐标小于终点的 $x$ 坐标，就看是不是东风，若是的话就将船只的 $x$ 坐标加 $1$，反之就原地不动，等到下一个时间点；若船只的 $x$ 坐标大于终点的 $x$ 坐标，就看是不是西风，若是的话就将船只的 $x$ 坐标减 $1$，反之就还是不动。$y$ 坐标同理。这道题就被我们秒了。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long 

using namespace std;
const int N=1e5+15;
int t,sx,sy,ex,ey;
char c;

signed main(){
	scanf("%lld %lld %lld %lld %lld",&t,&sx,&sy,&ex,&ey);
	for(int i=1;i<=t;++i){
		scanf("%c",&c);
		if(sx<ex&&c=='E')sx++;
		if(sx>ex&&c=='W')sx--;
		if(sy<ey&&c=='N')sy++;
		if(sy>ey&&c=='S')sy--;
		if(sx==ex&&sy==ey){
			printf("%lld\n",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}
```


---

## 作者：zjhzs666 (赞：1)

# 题意
已知起点 $(x,y)$ 以及目标点 $(a,b)$，在 $t$ 秒内每秒会刮一次风，有四种风向东南西北 $(E,S,W,N)$。现在告诉你每秒的风向，每次你可以选择原地不动或者随风移动，求到达目标点所需要的最小时刻，如果无法到达目标点就输出 $-1$。


# 思路
由于我们需要求到达目标点所需要的最小时刻并且我们自己无法移动只能随风移动或不动，因此我们每次只需要判断风向来尽量向目标点靠近，只进行有价值操作，当有一轴位置到达目标点的相同轴位置便始终不需要改变，当到达目标点时便输出此时的时间然后退出即可。


**时间复杂度：** $O(t)$。


# 代码
```
#include<bits/stdc++.h>
using namespace std;
string q;
int t,x,y,a,b;
int main(){
	cin>>t>>x>>y>>a>>b>>q;
	for(int i=1;i<=t;i++){
		if(x<a&&q[i-1]=='E')x++;//x轴小了，可以走
		if(x>a&&q[i-1]=='W')x--;//x轴大了，可以走
		if(y<b&&q[i-1]=='N')y++;//y轴小了，可以走
		if(y>b&&q[i-1]=='S')y--;//y轴小了，可以走
		if(x==a&&y==b){//到达目标点
			cout<<i;//输出时间
			return 0;
		} 
	}
	cout<<-1;//t秒已经过了，还未到达目标点，game over！
	return 0;
}
```


---

## 作者：lizulong (赞：1)

## 题意：
有 $(E,S,W,N)$ 四种风向，每个风向按照，**东南西北**的方向一一对应，移动坐标，且每阵风只能移动一格坐标。

$E$：$x$ 坐标 $+1$；

$S$：$y$ 坐标 $-1$；

$W$：$x$ 坐标 $-1$；

$N$：$y$ 坐标 $+1$。

对于每一阵风，我们可以随着风向移动，也可以不动，但都会经过一时刻。

求从点 $(s_x,s_y)$ 到点 $(e_x,e_y)$ 的最短时刻。
## 思路：
对于每一阵风，如果它对我们到终点有帮助就移动。这样不浪费每一次步数，才能最快到达。

例如样例：
```cpp
5 0 0 1 1
SESNW
```
$x$ 轴和 $y$ 轴都需要加 $1$，所以我们需要一阵北风（N）和一阵东风（E）。

样例中则使用了第一和第四阵风。

## 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char feng_xiang;
signed main(){
	int t,sx,sy,ex,ey;
    cin>>t>>sx>>sy>>ex>>ey;
    for(int i=1;i<=t;i++){
    	cin>>feng_xiang;
    	if(feng_xiang=='E'&&sx<ex/*如果x坐标比目标x坐标小*/) sx++;
		else if(feng_xiang=='S'&&sy>ey/*如果y坐标比目标y坐标大*/) sy--;
		else if(feng_xiang=='W'&&sx>ex/*如果x坐标比目标x坐标大*/) sx--;
		else if(feng_xiang=='N'&&sy<ey/*如果y坐标比目标y坐标小*/) sy++;
		if(sx==ex&&sy==ey){cout<<i;return 0;}//如果已经到了目的地，输出最短时刻 
	}
	cout<<-1;//到不了 
    return 0;
}
```

---

## 作者：wbxxxx (赞：0)

一道令人愉悦的水题。

# 思路：

很简单的**贪心**思想，怎样离终点更近，就怎么走。

# 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int X=0,w=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-') w=-1;ch=getchar();}
    while(ch<='9' && ch>='0') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
//int a[10000009],b[100000009],f[10000009];
int n,m,i,j,k,sum,cnt,ans;
signed main()
{
	int t,x,y,a,b;
	t=read(),x=read(),y=read(),a=read(),b=read();
	while(t--)
	{
		i++;
   	  	char q;
   	  	cin>>q;
		if(x>a&&q=='W') x--;		
		if(x<a&&q=='E') x++;
		if(y>b&&q=='S') y--;       	
		if(y<b&&q=='N') y++;
		if(x==a&&y==b){
			cout<<i;
			return 0;
		} 
	}
	cout<<-1<<endl;
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF298B)
## 大意
有 $n$ 个方向，可走可不走（走和不走都要花费时间），问能否从 $(x_1,y_1)$ 到 $(x_2,y_2)$ ，若能走到，输出最少时间；若不能，输出 ```-1```。
## 思路
一道贪心。如果给出一个方向，能离终点更近，就可以走，否则不走。过程中如果走到终点，就直接输出；如果输入完都没有走到终点，就输出 ```-1```。
## [AC](https://www.luogu.com.cn/record/168257880) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,x1,y1,x2,y2,ans=0;
	cin>>n>>x1>>y1>>x2>>y2;
	while(n--){
		ans++; //不管走不走，时间都要加 
		char c;
		cin>>c;
		if(c=='E'&&x1<x2){ //接下来一堆判断 
			x1++;
		}
		if(c=='W'&&x1>x2){
			x1--;
		}
		if(c=='N'&&y1<y2){
			y1++;
		}
		if(c=='S'&&y1>y2){
			y1--;
		}
		if(x1==x2&&y1==y2){ //走到了，直接输出 
			cout<<ans;
			return 0;
		}
	}
	cout<<-1; //走完了都走不到，输出 -1 
	return 0;
}
```

---

## 作者：L_xcy (赞：0)

### 解题思路
我们既然可以选择走或不走，那如果走之后离终点更近了，那就走，否则就不走，如果最后都没有到终点，就输出 `-1`。

我觉得这题可以评橙。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,x,y,a,b;
	cin >> t >> x >> y >> a >> b;
	int ans = 0;
	while(t--){
		ans++;
   	  	char q;
   	  	cin >> q;
		if(x > a && q == 'W')
		    x--;		
		if(x < a && q == 'E')
		    x++;
		if(y > b && q == 'S')
		    y--;       	
		if(y < b && q == 'N')
       	    y++;
		if(x == a && y == b){
			cout << ans;
			exit(0);
		} 
	}
	puts("-1");
}
```

---

## 作者：hard_learn (赞：0)

# 简要题意

极地熊钓鱼，受风驱动船只移动。根据风向决定每秒移动方向，能锚定停留。给定风向序列和起终点坐标，求最早到达终点的秒数；若无法到达输出 $-1$。

# 思路
根据每秒风向更新船只位置，让船更近，直至到达目标或超过时间。达到目标输出到达时间，否则输出 $-1$ 表示无法到达。注意：可以原地不动。 

# 代码如下
```
#include<bits/stdc++.h>
using namespace std;
int t;
int sx,sy,ex,ey;
string s;
int sum=-1;
int main(){
    cin>>t>>sx>>sy>>ex>>ey;
    cin>>s;
    int ans=ex-sx;
    int cnt=ey-sy;
    for(int i=0;i<t;i++){
        if(ans>0&&s[i]=='E'){
            ans--;
        } 
		else if(ans<0&&s[i]=='W'){
            ans++;
        }
        if(cnt>0&&s[i]=='N'){
            cnt--;
        } 
		else if(cnt<0&&s[i]=='S'){
            cnt++;
        }
        if(ans==0&&cnt==0){
            sum=i+1;
            break;
        }
    }
    cout<<sum<<endl;
    return 0;
}

```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF298B)

题目描述：有 $t$ 阵风，每阵风都有一个风向，可以顺风飘或不动，现在要从 $(s_x, s_y)$ 到 $(e_x, e_y)$，求最少需要的时间。

对于每一阵风，如果它能使自己到终点的曼哈顿距离更近就顺风飘，否则原地不动。

代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a, b, c, d;
int main(){
	cin >> n >> a >> b >> c >> d;
	string s; cin >> s;
	for (int i = 0; i <= s.length(); i++){
		if (a > c && s[i] == 'W') a--;
		else if (a < c && s[i] == 'E') a++;
		else if (b > d && s[i] == 'S') b--;
		else if (b < d && s[i] == 'N') b++;//四种风向
		if (a == c && b == d){cout << i + 1; return 0;}
	}
	cout << -1;//到不了
	return 0;
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

给出 $n$，$sx$，$sy$，$ex$，$ey$。表示有 $n$ 个方向，初始坐标与终点坐标。然后会给出一个长为 $n$ 的字符串 $s$，表示每个时间点的风向。每个时间可以选择不动或者跟着风向移动一个单位距离。你需要求出到终点需要的时间，如果去不到，就输出 `-1`。

### 分析

既然可以选择不动或者动，那我们只需要看当前移动的方向对前往终点是否有帮助，有就移动，没有就等着。一到到达了终点时，就输出并退出。如果到最后都没有，就输出 `-1`。

### 代码

```
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n, sx, sy, ex, ey;
//      起点    终点 
signed main()
{
	cin >> n >> sx >> sy >> ex >> ey;
	for(int i = 1; i <= n; i++)
	{
		char c;
		cin >> c;
		if(c == 'E')
		{
			if(sx < ex)//有帮助 
			{
				sx++;
			}
		}
		if(c == 'W')
		{
			if(sx > ex)//如上 
			{
				sx--;
			}
		}
		if(c == 'S')
		{
			if(sy > ey)
			{
				sy--;
			}
		}
		if(c == 'N')
		{
			if(sy < ey)
			{
				sy++;
			}
		}
		if(sx == ex && sy == ey)//到了 
		{
			cout << i << endl;//直接输出 
			exit(0);
		}
	}
	puts("-1");//到不了 
	return 0;
}
```

---

## 作者：xudiyao (赞：0)

# 洛谷CF298B题解
## 题意简述
从 $(s_x,s_y)$ 根据风向行走，可停留也可前进一个单位长度，每进行一步时间单位一，问能否走到终点 $(e_x,e_y)$，若能，输出时间，否则输出 $-1$。
## 思路引导
### 1.暴力
这个就没必要解释了，~~毕竟万物皆可暴力~~。

每一次选择停或前进都分开进行判断，当到达终点时输出当前判断次数，时间复杂度 $O(t^2)$，但 $t$ 最大可达 $10^5$。
### 2.贪心
同时也是本题的正解，若不知道什么是贪心，可点[这里](https://blog.csdn.net/TuttuYYDS/article/details/124636914)。

那么贪心为什么是本题的正解呢？首先，你要去某一个地方，你的距离肯定是越来越近，本题中同样如此，你要到达终点，如果你走下这一步会距离它更远，那么肯定不走，否则肯定要前进。

按照输入顺序判断，若往对应方向走可以距离终点更近，那么就走，否则停留，如果此时坐标到达终点，输出 $i$，否则输出 $-1$，时间复杂度 $O(t)$。

## 代码
```cpp
#include<bits/stdc++.h>//万能头文件yyds ！！！ 
using namespace std;
char a[101000];
int main()
{
	int k,n,m,x,y;
	cin>>k>>n>>m>>x>>y;
	for(int i=1;i<=k;i++) cin>>a[i];
	for(int i=1;i<=k;i++)
	{
		if(a[i]=='E'&&n<x) n++;//如果往右走能距离终点更近，那么向右请进 。 
		else if(a[i]=='S'&&m>y) m--;//如果往下走能距离终点更近，那么向下请进 。 
		else if(a[i]=='W'&&n>x) n--;//如果往左走能距离终点更近，那么向左请进 。 
		else if(a[i]=='N'&&m<y) m++;//如果往上走能距离终点更近，那么向上请进 。 
		if(x==n&&y==m)//如果到达终点 。 
		{
			cout<<i;//输出代表时间的i 。 
			return 0;
		}
	}
	cout<<-1; 
	return 0;
}//AC撒花！！！
//杜绝抄袭，禁止复制题解！！！ 
```

---

## 作者：AstaSunch_ (赞：0)

# $\mathbf{0x00}$ 前言
蒟蒻的第 $\mathbf{\color{red}{19}}$ 篇题解。
# $\mathbf{0x01}$ 题意简述
从 $(s_x,s_y)$ 驶往 $(e_x,e_y)$，每小时有不同的风向，每次可以选择顺风行驶或原地不动（都会计算时间），问最少需要耗费多少小时？
# $\mathbf{0x02}$ 题目思路
一看就是贪心。

只要与终点 $(e_x,e_y)$ 有差距，则优先取靠前的风，通过风向继续航行至离终点更近的地方，如果所有风向已经用完了，但还是没有到达终点，则无解。

证明也很简单：对于更靠前的风 $x$ 和更靠后的风 $y$，如果互换位置，则代价一定会变大或不变，并且不会增加价值。
# $\mathbf{0x03}$ Code！

```cpp
//杜绝抄袭，从我做起
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int t,x1,y1,x2,y2,n,m;
char c[100005];
int main(){
	cin>>t>>x1>>y1>>x2>>y2;
	n=x2-x1,m=y2-y1;
	for(int i=1;i<=t;i++){
		cin>>c[i];
		if(c[i]=='S'&&m<0)m++;
		if(c[i]=='N'&&m>0)m--;
		if(c[i]=='E'&&n>0)n--;
		if(c[i]=='W'&&n<0)n++;
		if(n==0&&m==0){
			cout<<i<<endl;	
			return 0;
		}
	}
	cout<<-1<<endl;
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

首先用起始坐标和最终坐标算出位移，然后贪心取风。

对于每一个位置上的移动，如果一共都没有这么多的风可以取，那么一定无解，反之一定有解，并且最优方案一定是优先取前面的风。

这个贪心的证明也是显然的，如果交换一个较小位置的风和一个较大位置的风，价值是不变的而代价一定不会变小。

---

~~本题使用了物理上的正交分解法，将位移分解成东西向位移和南北向位移然后分开讨论。~~

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int x1,y1,x2,y2,n,dx,dy;
char c;
int main(){
	scanf("%d%d%d%d%d",&n,&x1,&y1,&x2,&y2);
	dx=x2-x1;
	dy=y2-y1;
	for(int i=1;i<=n;i++){
		c=getchar();
		while(c=='\n'||c=='\r')c=getchar();
		if(c=='S')if(dy<0)dy++;
		if(c=='N')if(dy>0)dy--;
		if(c=='E')if(dx>0)dx--;
		if(c=='W')if(dx<0)dx++;
		if(dx==0&&dy==0){
			printf("%d\n",i);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
```


---

