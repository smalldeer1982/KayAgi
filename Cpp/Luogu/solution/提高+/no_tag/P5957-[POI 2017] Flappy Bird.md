# [POI 2017] Flappy Bird

## 题目背景

`《飞扬的小鸟》` 是一款风靡的小游戏。

## 题目描述

在游戏中，小鸟一开始位于 $(0,0)$ 处，它的目标是飞到横坐标为 $X$ 的某个位置上。

每一秒，你可以选择点击屏幕，那么小鸟会从 $(x,y)$ 飞到 $(x+1,y+1)$，或者不点击，那么小鸟会飞到 $(x+1,y-1)$。

在游戏中还有 $n$ 个障碍物，用三元组 $(x_i,a_i,b_i)$ 描述，表示在直线 $x=x_i$ 上，$y\le a_i$ 或者 $y\ge b_i$ 的部分都是障碍物，碰到或者擦边都算游戏失败。

现在，请你求出小鸟从 $(0,0)$ 飞到目的地最少需要点击多少次屏幕。

## 说明/提示

对于 $100\%$ 的数据，$0\le n\le 500000$，$1\le X\le10^9$，$0<x_i<X$，$-10^9\le a_i<b_i\le 10^9$。

-------

### 样例解释：
![](https://cdn.luogu.com.cn/upload/image_hosting/9lse80af.png)

## 样例 #1

### 输入

```
4 11
4 1 4
7 -1 2
8 -1 3
9 0 2```

### 输出

```
5```

# 题解

## 作者：AC_Panda (赞：14)

-   _Solution 1:_

 	对每个横坐标进行搜索（上/下）。
    
 	时间复杂度：$O(2^X)$
    
-   _Solution 2:_
	
	$DP$：令 $f_{i,j}$ 表示飞到点 $\left({i,j}\right) $ 最少需要点击屏幕的次数。
    
    根据飞行规则，点 $\left({i,j}\right) $ 可能且仅可能在点 $\left({i-1,j+1}\right) $ 时不点击屏幕和在点 $\left({i-1,j-1}\right) $ 点击屏幕抵达，即可得：
    
    状态转移方程：$f_{i,j}= min\left\{f_{i-1,j+1},f_{i-1,j-1}+1\right\} $ 
    
 	时间复杂度：$O(kX),k$ 为选取的 $j$ 的上界。

-   _Solution 3:_

	设$x$为上升的次数（即点击屏幕的次数），$y$为下降的次数，则从起点到到点$\left({a,b}\right)$时，满足
    
    $\begin{cases}x+y=a\\x-y=b\end{cases}$
    
    故有 $x=\dfrac{a+b}{2}$
    
    所以只需求出 $x=x_n$ 时，纵坐标的最小值。
    
    考虑记录当前可走区间的端点。
    
    由 $x=\dfrac{a+b}{2}$ 可得
    
    $\triangle x=\dfrac{\triangle a+\triangle b}{2}$
    
    即可得可走区间中的点必须和端点的奇偶性相同。
    
    转移：最低点 $l$ 一直不跳，最高点 $r$ 一直跳，新区间与可通行范围（障碍物）的交集即为新的可走区间。
    
    每次转移从一根障碍物，跳到相邻的另一根障碍物，为 $O(1)$ ,共 $n$ 次。
    
    时间复杂度：$O(n)$
#  **代码**
```
#include<bits/stdc++.h>
using namespace std;
int x,a,b,l,r,ll,n,X;
int main()
{
	scanf("%d%d",&n,&X);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&a,&b);
		if (r+(x-ll)>=b)r=(r-(x-ll)-b)&1?b-1:b-2;
		else r+=(x-ll);
		if (l-(x-ll)<=a)l=(a-l+(x-ll))&1?a+1:a+2;
		else l-=(x-ll);
		if(r<l){cout<<"NIE";return 0;}
		else ll=x;
	}
	cout<<((x+l)>>1);
}
```



---

## 作者：Durancer (赞：9)

### 前言

模拟+贪心，有一定的思维难度。

### 思路

提供一种另类的做法，旋转坐标系。

~~题解区没有，只好自力更生了~~

![](https://cdn.luogu.com.cn/upload/image_hosting/b7iytxdu.png)

通过逆时针旋转坐标系可以发现，纵坐标的变换很有规律了。

点击 $(x,y)\to (x+1,\dfrac{x+y}{2})$

不点击 $(x,y)\to (x+1,y)$

**注：** 此处的横坐标为了方便起见，依旧是用未翻转前的横坐标值来表示，仅仅是替换了纵坐标的计算方式。

那么继续考虑贪心的做法，首先一定是要使点击的次数是最小的，那么就可以尽量使小鸟每次通过的时候都是最靠近下方柱子。

设 $L,R$ 表示当前记录的下界和上界。

 $L$ 需要记录到当前的障碍物为止的下界的最大值。
 
 $R$ 记录到当前的障碍物为止的上界的最小值。
 
 如果出现 $L>R$ 的情况，表示无解。
 
 那么最后在有解情况下记录下来的 $L$ 就是通过的点击数的最小值。
 
 ```cpp
 #include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
using namespace std;
const int N=5e5+9;
int l[N],r[N],x[N];
int n,X;
int L,R,last;
bool flag=false;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')
			f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=getchar();
	}
	return f*x;
}
void get_ans()
{
	for(int i=1;i<=n;i++)
	{
		R=R+(x[i]-last);
		L=max(L,l[i]);//贪心,要过去就一定要飞到最大的下方柱子的高度+1处 
		R=min(R,r[i]);//上方柱子，应该是最下方。 
		if(L>R) 
		{
			printf("NIE\n");
			flag=true;
			exit(0);
		}
		last=x[i];
	}
}
int main()
{
	n=read();
	X=read();
	//坐标系逆时针旋转45°
	//x坐标依旧是用原先的
	//y左边换新，维护纵坐标贪心。
	//(x,y)->(x,(x+y)/2)
	for(int i=1;i<=n;i++)
	{
		x[i]=read();
		l[i]=read();
		r[i]=read();
		if(l[i]+x[i]==-1)
			l[i]=0;//保证奇偶性同步
		else l[i]=(x[i]+l[i])/2+1;//使l[i]变成，可以到达的最低点
		if(r[i]-1+x[i]==-1)//奇偶不同步
			r[i]=-1;//如果同时出现两个if里面的情况，无解
		else r[i]=(r[i]-1+x[i])/2; 
		if(l[i]>r[i]&&!flag)
		{
			//printf("NIE\n");
			flag=true;
		} 
	}
	if(flag) 
	{
		printf("NIE\n");	
		return 0;	
	}
	get_ans();
	if(!flag) printf("%d\n",L);
	return 0;
}
 ```



---

## 作者：二gou子 (赞：7)

## Solution

首先看到这题就联想到了一道 $dp$ 题：飞扬的小鸟。所以误以为这题也是 $dp$ 。有一个很一眼的暴力 $dp$ ，设 $f_{i,j}$ 表示横坐标为 $i$ 纵坐标为 $j$ 时的最小点击次数。但是由于本题坐标范围太大，这样做肯定是要爆炸的

换一种思路来考虑，假设我们在途中点击了 $x$ 次屏幕，终点坐标是 $end_x$，那么就应该下降了 $end_x-x$ 次（不管点不点击屏幕横坐标都会 $+1$ )。最后的纵坐标 $end_y=x-(end_x-x)=2x-end_x$，所以我们得出 $end_x+end_y=2x$，说明横纵坐标**奇偶性相同**。这个性质是我们判断过程中转移是否合法的关键一步。同时我们发现 $x=\frac{end_x+end_y}{2}$，而 $end_x$ 是题目中告诉我们的，是固定的。那也就是说我们只需要尽可能使 $end_y$ 小，就能得到最小的答案

一开始我专注于思考在中间过程中如何贪心地跳来使步数尽可能少，但是这样就会钻到一个死胡同。因为我们已经把 $x$ 用 $end_y$ 表示出来了，所以我们只需要寻找最小的 $end_y$ 就好了，至于中间怎么跳的根本不用管。换句话说，我们只需要保证这个最小的 $end_y$ 可以合法地转移而来就好了

至此，这个题的思路就很清晰了：设一个管道的上界（上端点）为 $up$，下界（下端点）为 $down$。先来考虑我们转移到下一个管道的下界和上界。设两个管道之间的距离为 $len$，即有 $len$ 次选择跳还是不跳。如果不考虑下一个管道本身的上下界限制，那么上下界应该分别是 $up+len$ 和 $down-len$。这个应该很显然，再和下一个管道的本身的限制取一个交集，就得到了一段合法区间。但是注意，我们还有奇偶性的限制。对于这条限制我们并不需要看中间点的限制，只需要看转移到下一个区间的端点就好了。如果端点和我们当前的端点奇偶性相同就不用管，如果不同的话就要把下界往下移或把上界往上移（因为要保证合法）。如果还是不太懂可以看代码。如果在过程中发现得出的下一个合法区间不存在（$up<down$），那么直接输出 $NIE$ 然后结束程序即可

最后得出的 $down$ 就是 $end_y$，直接由 $\frac{end_x+end_y}{2}$ 得出答案即可，总时间复杂度 $O(n)$

## Code

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
int n,end_x,up,down,last,x,a,b;
int main()
{
	scanf("%d%d",&n,&end_x);
	up=0,down=0,last=0;//初始在 (0,0) 
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x,&a,&b);
		int len=x-last;//与上一个管道的距离 
		if(up+len<b){//和下一个管道自身的限制不冲突 
			up+=len;
		}
		else{
			//最优当然是跳到纵坐标为 b-1 的位置，现在通过奇偶性判断能否到达。不能就跳到 b-2 。更新 up 同理 
			if((up+len+(b-1))&1) up=b-2; 
			else up=b-1;
		}
		if(down-len>a){//同上 
			down-=len;
		}
		else{
			if((down-len+(a+1))&1) down=a+2;
			else down=a+1;
		}
		if(down>up){
			printf("NIE\n");
			return 0;
		}
		last=x;
//		printf("last=%d down=%d up=%d\n",last,down,up);
	}
	
	down-=end_x-last;
	
	printf("%d\n",(down+end_x)/2);
	
	return 0;
}

```

---

## 作者：Dita (赞：3)

 [题目](https://www.luogu.com.cn/problem/P5957)
 
 
~~本想用 [飞扬的小鸟](https://www.luogu.com.cn/problem/P1941)水，好像不对劲~~

**solution**

前一篇题解已经把到达一个点 $(a, b)$ 所需点击屏幕的次数为 $\frac{a + b}{2}$ 解释清楚了，在此主要强调一下**转移**

根据这个的性质，不难发现所到达的点的横纵坐标都是同奇偶的(很显然吧，因为点击的次数不可能是半次啊 = =）    

利用这个性质和上一个柱子所在位置对这个位置的限制条件（不理解的可以看代码理解）对到达这个柱子时的所能到达的高度范围进行确定，再利用柱子判断这个范围合不合法就好了

**代码变量声明**

- $lmax, lmin$, 为根据条件所锁定的区间范围

- $lx$ 为上一个柱子所在的位置

- $X$ ~~好像没啥用~~

- $a, b$ 柱子的下上边缘 


**code**

```
/*
work by:Ariel_
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, X, lmin, lmax, lx;
int main(){
   n = read(), X = read();
   for(int i = 1; i <= n; i++){
   	 int x = read(), a = read(), b = read();
	 lmin = lmin - (x - lx), lmax = lmax + (x - lx);
	 lmin = max(a + 1, lmin), lmax = min(b - 1, lmax);
	 if(x & 1) lmax -= !(lmax & 1), lmin += !(lmin & 1);
     else lmax -= lmax & 1, lmin += lmin & 1;
	 if(lmax <= a || lmin >= b || lmax < lmin) {
          printf("NIE\n");
          return 0;
     }
      lx = x;
   }
   printf("%d\n", (lmin + lx) >> 1);
   puts("");
   return 0;
}

```

---

## 作者：wendywan (赞：2)

# 题目：P5957 [POI2017] Flappy Bird

[题目传送门](https://www.luogu.com.cn/problem/P5957)

---


## 前言：
本题是贪心的模拟，不算很难吧。

看到好像其他题解好像思路不一样，打一个。

不废话开始。

---

## 题目意思： 
有一个二维的空间，一只小鸟在飞。
如果点一下小鸟就会上升，否则小鸟会下降。

如一个很丑陋的图:
![如图：](https://cdn.luogu.com.cn/upload/image_hosting/2s8oqepb.png)


---


## 思路：
就是一个很理所当然的贪心，主要是在模拟游戏的状态。

为了尽量少点击次数（即贪心贪最大）我们尽可能不点。

每轮只需要计算最低到哪里，这样就可以最大化我们每次点击次数的价值从而更加贴近答案。

观察最低的地方会不会碰到障碍物 ，
然后要观察上面的障碍物和下面的障碍物，然后看看可不可以通过。

**最极端**的就是如果你既不能通过又没有时间去点击了，那就直接结束了，记得输出 “NIE”。


---


## 复杂度分析：
$O(N)$ 显然不会超时，放心做。


---


## Code：
详细见代码注释：
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
int N, X, x, a, b;
//n个障碍物 目标是飞到X x直线上 b<=y<=a的位置都是障碍物  
int click, p, ans, nx;
signed main(){
	cin >> N >> X;
	for( int i = 1; i <= N; i ++ ){// 一个一个障碍物判 
		cin >> x >> a >> b;
		click += x - nx;// 计算最多点多少往上调的范围 
		p -= x - nx;// 不点击的话往下降会降的最低哪里 
		nx = x;
		if( p <= a ){// 如果不点击会撞到最下面的障碍，就保持以最少的点击次数通过
			int t = ( a + 1 - p + 1 ) / 2; // 通过下面障碍的最少点击次数，一上一下可维持位置不变，向上取整
			p += 2 * t;// 通过障碍时的高度
			click -= t;//把能往上的高度减了 
			ans += t;// 加上这次的点击次数 
		}
		if(click < 0 || p >= b ){// 如果不能通过调节来通过障碍那就结束了 
			cout << "NIE" <<endl;
			return 0;
		}
		click = min( click, (b - 1 - p) / 2 );// 更新可以向上调节的高度 且可以不碰到障碍 
	}
	cout << ans << endl;//输出 
    return 0;
}

```

---

## 易错：

记得要更新高度！

---

## 作者：程门立雪 (赞：2)

# Flappy Bird

>在游戏中，小鸟一开始位于 $(0,0)$ 处，它的目标是飞到横坐标为 $X$ 的某个位置上。
>
>每一秒，你可以选择点击屏幕，那么小鸟会从 $(x,y)$飞到 $(x+1,y+1)$，或者不点击，那么小鸟会飞到 $(x+1,y-1)$。
>
>在游戏中还有 $n$ 个障碍物，用三元组 $(x_i,a_i,b_i)$ 描述，表示在直线$x=x_i$ 上，$y\le a_i $或者 $y\ge b_i$ 的部分都是障碍物，碰到或者擦边都算游戏失败。现在，请你求出小鸟从 $(0,0)$ 飞到目的地最少需要点击多少次屏幕。

**题解：**

设$x$为一共上升的次数,即点击屏幕的次数，$y$为一共下降的次数。

从起点到点$(a, b)$,可得

$x + y = a$    (每次上升与下降都会向前走)

$x - y = b$

解得：$x = \frac{a+b}{2} $。

根据$ x = \frac{a + b}{2}$,可知最后所到达的点一定是同奇同偶，因为 $a + b$ 要能被$2$整除。

因为它的上升下落，和它的前进是同时进行的，所以可以根据上一个柱子所在的位置对达到这个柱子时所能达到的高度范围进行确定。

再利用同奇同偶这一性质，对范围进行缩小。

再用柱子的高度判断范围合不合法。

最后的答案就是$\frac{a + b}{2}$,即$\frac{lmin \ + \ x}{2}$。
```c
#include <cstdio>
#include <iostream>
#define orz cout << "AK IOI" <<"\n"

using namespace std;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48);ch = getchar();}
	return x * f;
}
int n, X, minn, maxx, lx, x, a, b; 
int main()
{
    //freopen(".in","r",stdin); 
    //freopen(".out","w",stdout);
    n = read(), X = read();
    for(int i = 1; i <= n; i++)
	{
		x = read(), a = read(), b = read();
		minn = minn - (x - lx), maxx = maxx + (x - lx);
		minn = max(a + 1, minn), maxx = min(b - 1, maxx);
		if(x % 2 == 0) maxx -= !(maxx % 2 == 0), minn += !(minn % 2 == 0);
		else maxx -= (maxx % 2 == 0), minn += (minn % 2 == 0);
		if(minn > maxx ||minn <= a || maxx >= b) {printf("NIE\n"); return 0;}
		lx = x;
	} 
	printf("%d", (x + minn) >> 1);
	return 0;
}
```


---

## 作者：900102bj (赞：1)

## [P5957 Flappy Bird](https://www.luogu.com.cn/problem/P5957 "P5957 Flappy Bird")
## 题意
一开始小鸟在 $(0,0)$，他需要飞到横坐标为 $X$ 的任意位置上，每一秒可以点击屏幕使得它从 $(x,y)$ 移动到 $(x+1,y+1)$，也可以不点移动到 $(x+1,y-1)$，有 $n$ 个障碍物，在 $x_{i}$ 位置并且挡住了 $y$ 小于等于 $a_{i}$ 的区域和大于等于 $b_{i}$ 的位置，问最少点几次屏幕能到达目标或输出不可到达。
## 题解
发现点击的次数只和到终点时的 $y$ 坐标有关。

考虑 $dp_{i,0/1}$ 表示到达第 $i$ 个障碍物时候最小/最大的 $y$ 坐标是什么，转移考虑从上一次的最低最高点飞过来，再考虑距离的奇偶性即可。

 dp 转移方程：

$dp_{i,0}=\max(a_{i}+1+[x_{i}\bmod2=1]\bigoplus[\left\vert a_{i}+1\right\vert \bmod2=1],dp_{i-1,0}-(x_{i}-x_{i-1}))$

$dp_{i,1}=\min(b_{i}-1-[x_{i}\bmod2=1]\bigoplus[\left\vert b_{i}-1\right\vert \bmod2=1],dp_{i-1,1}+(x_{i}-x_{i-1}))$


注意如果某个点 $dp_{i,0}>dp_{i,1}$，那么说明不可能到达。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,X;
const int maxn=5e5+10;
int x[maxn],a[maxn],b[maxn];
int dp[maxn][2];
int main(){
    scanf("%d%d",&n,&X);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&x[i],&a[i],&b[i]);
    }
    bool flag=0;
    dp[0][0]=dp[0][1]=0;
    for(int i=1;i<=n;i++){
        int d=x[i]-x[i-1];
        dp[i][0]=max(a[i]+1+((x[i]&1)^(abs(a[i]+1)&1)),dp[i-1][0]-d);
        dp[i][1]=min(b[i]-1-((x[i]&1)^(abs(b[i]-1)&1)),dp[i-1][1]+d);
        if(dp[i][0]>dp[i][1]){
            printf("NIE");
            return 0;
        }
    }
    printf("%d",(dp[n][0]+x[n])>>1);
    return 0;
}
```


---

## 作者：yxy666 (赞：1)

首先第一个规律从 $(0,0)$ 走到 $(x,y)$ 不管中间到哪个节点再继续走,最后需要点击屏幕的次数 $(x+y)/2$ ,可以从增量的角度思考，上行 $(1,1)$ ，下行  $(1,-1)$ 。接下来就是贪心了，不管怎么样你需要走到 $X[n]$,这个无可厚非的,那只有让 $Y$ 小一点了呗,只有实在没办法的时候才会去点击。

$code$ :
```cpp
#include<bits/stdc++.h>
#define maxn 500005
using namespace std;
int n,X,down,up,a[maxn],b[maxn],x[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}
int main(){
    n=read(),X=read();
    for (int i=1;i<=n;i++) x[i]=read(),a[i]=read(),b[i]=read();
    for (int i=1;i<=n;i++){
        int dis=x[i]-x[i-1];
        if (down-dis<a[i]+1){
        	if ((a[i]+1-down+dis)%2) down=a[i]+2;else down=a[i]+1;
        }else down-=dis;
        if (up+dis>b[i]-1){
            if((up+dis-b[i]+1)%2) up=b[i]-2;else up=b[i]-1;
        }else up+=dis;
        if (up<down) {printf("NIE\n");return 0;}
    }
    printf("%d\n",(down+x[n])/2);
    return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

一眼题。

不难注意到几个性质：

1. 不管你跳到哪个位置，横纵坐标和一定是一个偶数。
2. 最优的情况下，小鸟的位置一定较为靠下。

此题可解。维护小鸟在上一个障碍处的可行区间，然后在转移到下一个障碍处的可行区间。初始状态可以认为障碍在 $x=0$ 处，可行区间 $l=r=0$。

然后，注意一下维护可行区间的时候判断横纵坐标的和为偶数的限制。就没了。

以及注意一下，负数取模还是负数，强转一下正数。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif
inline int read() {
	int r = 0; char c = getchar_unlocked();
	while (c < '0' || c>'9') c = getchar_unlocked();
	while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = getchar_unlocked();
	return r;
}
inline void write(long long x) {
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 ^ 48);
}
inline void writi(long long args) {
	write(args); putchar_unlocked(10);
}
constexpr bool online = 0;
int n, m, x, a, b, lx, up, dn;
inline int md(int v) {
	if (v >= 0) return v % 2;
	return (-v) % 2;
}
signed main() {
	if (online)
		freopen("Flappy.in", "r", stdin),
		freopen("Flappy.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1;i <= n;++i) {
		cin >> x >> a >> b; b--; a++;
		/*
		不能一直贴下缘，要记录可行区间。
		其实显然，飞到同一个位置，不论什么方式，都只会需要特定的步数，可以反推。
		因此，记录可行区间上下界。
		*/
		int dx = x - lx; lx = x;
		int nup = up + dx, ndn = dn - dx;
		nup = min(nup, b); ndn = max(ndn, a);
		if (md(x)) nup -= 1 - md(nup), ndn += 1 - md(ndn);
		else nup -= md(nup), ndn += md(ndn);
		if (nup < ndn) {
			cout << "NIE\n";
			return 0;
		}
		dn = ndn;up = nup;
	}
	cout << (dn + lx) / 2 << endl;
	return 0;
}
//私は猫です
//9:00 passed big exam
```

---

