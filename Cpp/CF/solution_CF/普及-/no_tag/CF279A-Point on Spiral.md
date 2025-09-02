# Point on Spiral

## 题目描述

Valera the horse lives on a plane. The Cartesian coordinate system is defined on this plane. Also an infinite spiral is painted on the plane. The spiral consists of segments:  $ [(0,0),(1,0)] $ , $ [(1,0),(1,1)] $ , $ [(1,1),(-1,1)] $ , $ [(-1,1),(-1,-1)] $ , $ [(-1,-1),(2,-1)] $ , $ [(2,-1),(2,2)] $  and so on. Thus, this infinite spiral passes through each integer point of the plane.

Valera the horse lives on the plane at coordinates $ (0,0) $ . He wants to walk along the spiral to point $ (x,y) $ . Valera the horse has four legs, so he finds turning very difficult. Count how many times he will have to turn if he goes along a spiral from point $ (0,0) $ to point $ (x,y) $ .

## 样例 #1

### 输入

```
0 0
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
0 1
```

### 输出

```
2
```

## 样例 #4

### 输入

```
-1 -1
```

### 输出

```
3
```

# 题解

## 作者：ChenZQ (赞：4)

首先声明一下，此题解是在[这个题解](https://www.luogu.com.cn/blog/Freedom-200/solution-cf279a)的基础上改动的。以这个题解为基础，延伸出的一种新解法。

首先，我的思路是暴力枚举。枚举每一条线段，看看是否有和题目中给定的坐标相重合。

这是超级暴力代码：
```
#include<bits/stdc++.h>//来自上面链接的解题代码。
using namespace std;
int n,m,x1,x2,i,now,sum;
int main(){
    scanf("%d%d",&n,&m);
    x1=x2=0;now=1;
    if (x1==n&&x2==m){printf("0\n");return 0;}
    while (1){
        for (i=1;i<=now;i++){
            x1++;
            if (x1==n&&x2==m){
                printf("%d\n",sum);
                return 0;
            }
        }
        sum++;
        for (i=1;i<=now;i++){
            x2++;
            if (x1==n&&x2==m){
                printf("%d\n",sum);
                return 0;
            }
        }
        sum++;now++;
        for (i=1;i<=now;i++){
            x1--;
            if (x1==n&&x2==m){
                printf("%d\n",sum);
                return 0;
            }
        }
        sum++;
        for (i=1;i<=now;i++){
            x2--;
            if (x1==n&&x2==m){
                printf("%d\n",sum);
                return 0;
            }
        }
        sum++;now++;
    } 
    return 0;
}
```

这种方法是一个一个地枚举线段上的每一个点。但是每个线段的范围我们是知道的，因此，我们可以很容易地写出另一种解法。也就是判断题目给定的坐标是否在这个线段的范围内。

以下为代码:
```
#include<bits/stdc++.h>
using namespace std;
int n,m,x1,x2,i,now,sum;

int main()
{
	scanf("%d%d",&n,&m);
	x1=x2=0;now=1;
	if (x1==n&&x2==m) puts("0"),exit(0);
	while (1)
	{
		int tx=x1,ty=x2;
		x1+=now;
		if(n>=min(tx,x1) && n<=max(tx,x1) && m>=min(ty,x2) && m<=max(ty,x2)) printf("%d",sum),exit(0);
		sum++;
		tx=x1,ty=x2;
		x2+=now;
		if(n>=min(tx,x1) && n<=max(tx,x1) && m>=min(ty,x2) && m<=max(ty,x2)) printf("%d",sum),exit(0);
		sum++;now++;
		tx=x1,ty=x2;
		x1-=now;
		if(n>=min(tx,x1) && n<=max(tx,x1) && m>=min(ty,x2) && m<=max(ty,x2)) printf("%d",sum),exit(0);
		sum++;
		tx=x1,ty=x2;
		x2-=now;
		if(n>=min(tx,x1) && n<=max(tx,x1) && m>=min(ty,x2) && m<=max(ty,x2)) printf("%d",sum),exit(0);
		sum++;now++;
	} 
}


```

---

## 作者：Shimotsuki (赞：3)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/CF279A)

[传送门 to CF](https://codeforces.com/problemset/problem/279/A)

思路：很明显，这是一道找规律题，考虑根据题目要求在之上作图，先放一张自己画的简陋的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/84h6aifa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，在点 $(1,0)$ 处转弯 0 次，在点 $(1,1)$ 处转弯 1 次，在点 $(-1,1)$ 处转弯 2 次，在点 $(-1,-1)$ 处转弯 3 次，在点 $(2,-1)$ 处转弯 4 次。从以上数据，我们可以发现一个规律：转弯的次数可能是 $\left (  \max\left \{  \left |  x\right |, \left |  y\right | \right \}-1\right ) \times 4$ 。

但问题还没有结束，我们还需要判断同横坐标次数相同之类的特殊情况，然后次数加 1 ，加 2 ......

代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

int main(){
	int x,y;
	scanf("%d %d",&x,&y);
	if(!x&&!y) return printf("0"),0;
	int d=max(abs(x),abs(y));
	int ans=(d-1)<<2;
	if(x==d&&y>1-d&&y<=d) 
		return printf("%d",ans+1),0;
	if(y==d&&x>=-d&&x<=d)
		return printf("%d",ans+2),0;
	if(x==-d&&y>=-d&&y<=d)
		return printf("%d",ans+3),0;
	if(y<0&&x>y&&x<=-y)
		return printf("%d",ans+4),0;
	printf("%d",ans);
	return 0;//大功告成
} 
```


---

## 作者：zhengjh2818 (赞：2)

## 闲话多说
本期没有！

你干嘛，哈哈~哎呦！

## 题目介绍
[题目传送门](https://www.luogu.com.cn/problem/CF279A)

## 解题思路
![](https://cdn.luogu.com.cn/upload/image_hosting/cjrug6ap.png)

如图所示，螺旋遍历，从坐标 $(0,0)$ 开始，先向下走一格，到 $(1,0)$；向右走一格，到 $(1,1)$；向上走两格，到 $(-1,1)$；向左走两格，到 $(-1,-1)$；依次循环。

不难发现，方向为先向下（$i-1$），再向右（$j+1$），再向上（$i+1$），最后向左（$j-1$），以此四个方向为一个周期，循环对坐标加减。

加减几格，从图中可知，每一个步数使用过两次后，就要对步数进行加 $1$ 处理，配套方向进行螺旋遍历。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,num,way,sum;
int js;
int main(){
	cin>>n>>m;
	if(n==0&&m==0){
		cout<<0<<"\n";
		return 0;
	}
	num=1;
	way=1;
	sum=-1;
	while(1){
		js++;
		sum++;
		if(way==1){
			for(int i=1;i<=num;i++){
				x++;
				if(x==n&&y==m){
					cout<<sum;
					return 0;
				}
			}
		}else if(way==2){
			for(int i=1;i<=num;i++){
				y++;
				if(x==n&&y==m){
					cout<<sum;
					return 0;
				}
			}
		}else if(way==3){
			for(int i=1;i<=num;i++){
				x--;
				if(x==n&&y==m){
					cout<<sum;
					return 0;
				}
			}
		}else{
			for(int i=1;i<=num;i++){
				y--;
				if(x==n&&y==m){
					cout<<sum;
					return 0;
				}
			}
		}
		way=(way+1)%4;
		if(way==0) way=4;
		if(js==2){
			num++;
			js=0;
		}
	}
	return 0;
}
```
~~**蒟蒻的第三篇题解一审，望审核员大人通过。**~~

---

## 作者：MrJC_Pandingding (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF279A)
# 解题思路
首先，我们列出 $-2\le x\le2,-2\le y\le2$ 范围内每一个点上的答案：

|  | $-2$ | $-1$ | $0$ | $1$ | $2$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $-2$ | $7$ | $7$ | $7$ | $7$ | $6$ |
| $-1$ | $8$ | $3$ | $3$ | $2$ | $6$ |
| $0$ | $8$ | $4$ | $0$ | $2$ | $6$ |
| $1$ | $8$ | $4$ | $0$ | $1$ | $6$ |
| $2$ | $8$ | $4$ | $5$ | $5$ | $5$ |

我们把这些点按圈分开。不难发现，一圈上的数是有规律的。已第 $2$ 圈(最中间一点为第 $0$ 圈)为例，这一圈中，只有 $(2,-1)$ 上的答案是 $4$，$x=2,y\ge0$ 的点都是 $5$，$y=2,x\le1$ 的点都是 $6$，$x=-2,y\le1$ 的点都是 $7$，$y=-2,x\ge-1$ 的点都是 $8$。列个表看看：

| 范围 | 答案 |
| :-----------: | :-----------: |
| $(2,-1)$ | $4$ |
| $x=2,y\ge0$ | $5$ |
| $y=2,x\le1$ | $6$ |
| $x=-2,y\le1$ | $7$ |
| $y=-2,x\ge-1$ | $8$ |

我们还有一个问题：圈数如何求。观察发现，$x=\pm2$ 或 $y=\pm2$ 且另外一个的绝对值不超过 $2$ 的点都是第 $2$ 圈。仔细看这些点，发现圈数 $n=\max(|x|,|y|)$。

最后，此代码时间复杂度为 $\operatorname{O}(1)$，绝对不会超时。上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main()
{
	scanf("%d%d",&x,&y);
	n=max(abs(x),abs(y));//n 代表圈数
	if(!n)//(x,y)=(0,0)，要特判
		printf("0");
	else if(x==n&&y==1-n)
		printf("%d",n-1<<2);
	else if(x==n&&y!=-n)
		printf("%d",n-1<<2|1);
	else if(y==n)
		printf("%d",n-1<<2|2);
	else if(x==-n)
		printf("%d",n-1<<2|3);
	else printf("%d",n<<2);
	return 0;
}
```

---

## 作者：vanueber (赞：2)

[原题传送门](https://codeforces.com/problemset/problem/279/A)

# 题目分析

根据题意我们可以绘制出下图

![图](https://cdn.luogu.com.cn/upload/image_hosting/aygxndb2.png)

其中 $O$ 为出发点。经过观察，我们发现每走两步，下一次走的长度就会长一个单位长度，而走的方向也是有规律的（左 -> 上 -> 右 -> 下），于是依照这一特点，我们可以写出暴力程序。具体实现见代码。

# 代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int x, y;
int a, b, dir;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1}; //方向
int len = 1, cnt, lencnt;

int main()
{
	cin >> x >> y;
	if (x == 0 && y == 0) //特判
	{
		cout << 0 << endl;
		return 0;
	}

	while (true)
	{
		if (x == a && y == b) //走到了(x,y)
			break;
		a += dx[dir];
		b += dy[dir];
		lencnt++;

		if (lencnt == len)
		{
			cnt++;
			dir = (dir + 1) % 4; //改变方向
			lencnt = 0;
			if (dir % 2 == 0)
				len++; //每走2步步长加一
		}
	}
	if (lencnt == 0)
		cout << cnt - 1 << endl;
	else
		cout << cnt << endl;
	return 0;
}
/*
cnt表示转弯次数，即答案
dir表示方向
lencnt表示走的次数（因为走一次步长为1，要走多次）
len表示步长
*/

```

[AC记录](https://codeforces.com/problemset/submission/279/217945152)



---

## 作者：Rookie_t (赞：1)

经过模拟可知

第一次转弯之前 $x$ 肯定了一次 $1$。

第二次转弯之前 $y$ 肯定加了一次 $1$；

第三次转弯之前 $x$ 肯定加了一次 $2$；

第四次转弯之前 $y$ 肯定加了一次 $2$。

以此类推，第 $n$ 次转弯之前，如果 $n$ 是奇数，$x$ 肯定加了一次 $\left\lceil n/3 \right\rceil$；

如果 $n$ 是偶数，$y$ 肯定加了一次 $\left\lceil n/3 \right\rceil$。

所以，我们就可以开始模拟了。

纯暴力解法： 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,y,x1,y1,kkk = 1,sum = 0;//kkk不要过分解读，真不知道起啥名了 
signed main(){
	ios::sync_with_stdio(false);//加速cin，cout 
	cin>>x>>y;
	if(x == x1 && y == y1){//特判直接过 
		cout<<0;
		return 0;
	}
	for(i = 1;i<=now;i++){
		x1++;
		if(x1 == x && x2 = y){
			cout<<sum;
			return 0;
		} 
	}//第一次 
	sum++;
	for(int i = 1;i<=kkk;i++){
		y1++;
		if(x1 == x && x2 == y){
			cout<<sum;
			return 0;
		}
	}//第二次 
	sum++;
	kkk++;
	for(int i = 1;i<=kkk;i++){
		x1--;
		if(x1 == x && x2 == y){
			cout<<sum;
			return 0;
		}
	}
	sum++;
	for(int i = 1;i<=kkk;i++){
		y1--;
		if(x1 == x && x2 == y){
			cout<<sum;
			return 0;
		}
	}
	sum++;
	kkk++;
	return 0;
}
```
看在本蒟蒻敲了这么多字的份上，走过路过的大佬给个赞呗$qwq$


---

## 作者：UncleSam_Died (赞：0)

### 解题思路
按照题目中的规律画出来的图片如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/vuxotutl.png)

那么，我们直接根据规律判断当前查询的节点在那一条线段上就可以了。易得，当前的基础转向次数为 max$(|x|-1,|y|-1)\times 4$，那么加上一个在当前周期内部的转向次数就可以了。
### AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull usigned long long
using namespace std;
const string TypideName="c";
inline void readc(char &c){
	c=getchar();
	while(c==' '||c=='\n')
		c=getchar();
}inline void writec(char c){putchar(c);}
template<typename T>inline void read(T& x) {
	if(typeid(x).name()==TypideName){char ch;readc(ch);x=ch;return;}
	x = 0; bool f = false; char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-') f = !f; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x = (f ? -x : x); return;
}template<typename T>inline void put(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) put(x / 10);
	putchar(x % 10 + '0'); return;
}template<typename T>inline void write(T x) {
	if(typeid(x).name()==TypideName){writec(x);return;}
	put(x);
}
template<typename T,typename... Args>
inline void read(T& x,Args&...x_) {read(x),read(x_...);}
template<typename T,typename... Args>
inline void write(T x,Args...x_){write(x),write(x_...);}
int x,y;
inline void work(){
	read(x,y);
	if(x==0&&y==0) {write(0);return;}
	int ans=(max(abs(x),abs(y))-1)*4;
	if(y<0&&x>y&&x<=-y) ans+=4;
	else if(x==max(abs(x),abs(y))&&y>1-max(abs(x),abs(y))&&y<=max(abs(x),abs(y))) ans+=1;
	else if(y==max(abs(x),abs(y))&&x>=-max(abs(x),abs(y))&&x<=max(abs(x),abs(y))) ans+=2;
	else if(x==-max(abs(x),abs(y))&&y>=-max(abs(x),abs(y))&&y<=max(abs(x),abs(y))) ans+=3;
	write(ans,'\n');
}
signed main(){
	work();
	return 0;
}



```


---

## 作者：zqh123b (赞：0)

### 题目分析
题意不再赘述。  
先看一张手绘的解释图（请大家不要在意细节）：
![题面解释图](https://cdn.luogu.com.cn/upload/image_hosting/ngzsej44.png)
很明显，可以得出以下结论：  
1. 每走两步转一次弯。
2. 每走两步每次的步数加一

有以上两个结论，就可以快乐地模拟了。

### 代码实现
具体代码如下（所有细节见代码注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[4]={1,0,-1,0};
//         | |  | |
//         下右 上左
//         | |  | |
int dy[4]={0,1,0,-1};
int x,y;//目标位置
int fangxiang=0;//方向（对应dx,dy数组）
int nowx,nowy;//当前位置
int cishu=0;//转弯次数
int changdu=1,nchangdu=0;//每一步的长度
int main(){
	cin>>x>>y;
    while(nowx!=x||nowy!=y){//只要不到目标位置
        if(changdu==nchangdu){//达到长度
            cishu++;//转弯
            fangxiang++;//转弯
            fangxiang%=4;//避免越界
            if(fangxiang==0||fangxiang==2)changdu++;//两步一加长度
            nchangdu=0;//归零
        }
        nowx+=dx[fangxiang];//移动
        nowy+=dy[fangxiang];//移动
        nchangdu++;//增加长度
    }
    cout<<cishu<<endl;
	return 0;
}
```

### 注意事项
1. 转弯时要注意 $fangxiang \bmod 4$ 避免数组越界。
2. 初始每步长度为 $1$。

---

## 作者：sssscy_free_stdio (赞：0)

本题很简单，由手动模拟可知每移动两次，下一次移动的距离就会长 $1$，且方向也有规律，因此可以写出暴力。

AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,nx,ny,dir,nl=1,c,tc;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int main(){
	scanf("%d%d",&x,&y);
	if(x==0&&y==0){
		printf("0");
		return 0;
	}while(1){	
		if(x==nx&&y==ny){
			break;
		}nx+=dx[dir],ny+=dy[dir],tc++;
		if (tc==nl){
			c++,dir=(dir+1)%4,tc=0;
			if(dir%2==0){
				nl++;				
			}
		}
	}if(tc==0){
		printf("%d",c-1);
	}else{
		printf("%d",c);
	}return 0;
}
```
于是，我们就愉快的 AC 了！

---

## 作者：ruanshaochuan______ (赞：0)

直接模拟螺旋即可，用一个变量 $cnt$ 记录转弯次数，用一个 $len$ 变量记录走几次转弯，用两个变量 $ex,ey$ 记录当前得坐标，用一个 $nb$ 变量记录离上一次转弯走了几步，用两个变量记录当前方向。   
由于走两次增加一次步数，所以当 $cnt \bmod 2=1$ 时，$len+1$。  
注意，如果此时刚转弯输出便为 $cnt-1$。   
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int ex,ey,dx,dy,nx=0,ny=0,len=1,cnt=0,nb=0;
	cin>>ex>>ey;
	dx=1,dy=0;
	if(!ex&&!ey)
	{
		cout<<0;
		return 0;
	}
	while(nx!=ex||ny!=ey)
	{
		nx+=dx;
		ny+=dy;
		nb++;
		if(nb==len)
		{
			if(cnt%2)
				len++;
			cnt++;
			if(dy==0&&dx==1)
			{
				dy=1,dx=0;
			}else
			if(dy==1&&dx==0)
			{
				dy=0,dx=-1;
			}else
			if(dy==0&&dx==-1)
			{
				dy=-1,dx=0;
			}else
			if(dy==-1&&dx==0)
			{
				dy=0,dx=1;
			}
			nb=0;
		}
	}
	if(nb)
		cout<<cnt;
	else
		cout<<cnt-1;
}
```

---

## 作者：Crasole (赞：0)

## 题意

一个点，在一个二维平面上走蛇形路线，第一次从 $(0 , 0)$ 走到 $(1 , 0)$，第二次走到 $(1 , 1)$，第三次走到 $(-1 , 1)$ 以此类推。

现在问，从点 $(0 , 0)$ 走到点 $(x , y)$ 要转几次弯。

## 思路

首先，我们先根据题目的描述画出点在平面上行走的路线。

![](https://cdn.luogu.com.cn/upload/image_hosting/w0uivsmr.png)

根据上图我们可以发现，这个点每次都走了一定长度以后就会转换，而且这个走的长度是向左或者向右增加一的。

当思路理清之后，这道题目就很简单了，我们用 $nlen$ 表示当前走的距离，$len$ 表示需要走的距离，$dir$ 表示当前的方向（$0$ 表示右，$1$ 表示上，$2$ 表示左，$3$ 表示下），我们用数组来存储每个方向的移动，当 $nlen = len$ 时，我们就更改方向，$dir = (dir+1) \bmod 4$，然后判断方向是否为 $0$ 或 $2$，如果是就要增加长度，$len + 1$，同时清空 $nlen$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int x,y,dir,nx,ny,ans=0,len,nlen=0;
int main(){
	cin>>x>>y;
	len=1;
	while(x!=nx||y!=ny){
		if(nlen==len){
			ans++;//转弯次数加1
			dir=(dir+1)%4;//转向
			if(dir==2) len++;
			if(dir==0) len++;
            //判断是否需要更改长度
			nlen=0;
		}
		nx=nx+dx[dir],ny=ny+dy[dir];
		nlen++;//移动
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：小杨小小杨 (赞：0)

## 题意
构造一个蛇形矩阵。
## 思路
既然已经有人提供了规律法，那么这里我提供一个暴力枚举的方法。   
构造出整个矩阵，然后暴力查找到当前位置转了几次弯。    
规律：    
第一次转弯前：$x$ 加一次 $1$；   
第二次转弯前：$y$ 加一次 $1$；  
第三次转弯前：$x$ 加两次 $1$；  
第四次转弯前：$y$ 加两次 $1$；
以此类推。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x1,x2,i,now,sum;
int main(){
	scanf("%d%d",&n,&m);
	x1=x2=0;now=1;
	if (x1==n&&x2==m){printf("0\n");return 0;}
	while (1){
		for (i=1;i<=now;i++){
			x1++;
			if (x1==n&&x2==m){
				printf("%d\n",sum);
				return 0;
			}
		}
		sum++;
		for (i=1;i<=now;i++){
			x2++;
			if (x1==n&&x2==m){
				printf("%d\n",sum);
				return 0;
			}
		}
		sum++;now++;
		for (i=1;i<=now;i++){
			x1--;
			if (x1==n&&x2==m){
				printf("%d\n",sum);
				return 0;
			}
		}
		sum++;
		for (i=1;i<=now;i++){
			x2--;
			if (x1==n&&x2==m){
				printf("%d\n",sum);
				return 0;
			}
		}
		sum++;now++;
	} 
	return 0;
}

```


---

