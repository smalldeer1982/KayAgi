# Shawarma Tent

## 题目描述

首都柏林的地图可以看成一个坐标无限的平面。每一个坐标为整数的点有一个建筑物，每个建筑物都有连接到四个相邻建筑物的街道。所有街道都与坐标轴平行。

首都的主要学校位于 $(s_x,s_y)$。这所学校有 $n$ 名学生，第$i$名学生住在位于 $(x_i,y_i)$ 的房子里。有些学生可能住在同一所房子里，但没有学生住在 $(s_x,s_y)$。

下课后，每名学生沿着一条最短路径从学校走回家。所以第$i$个学生从学校到家的距离是 $|s_x-x_i|+|s_y-y_i|$。

柏林的供应部决定在首都某处（在某个坐标为整数的节点上）放置一个 shawarma 帐篷。如果从学校到第$i$名学生家的最短路径中至少有一条经过 shawarma 帐篷所在地，则认为第 $i$ 名学生将购买 shawarma 帐篷。学校所在地禁止放置 shawarma 帐篷，但 shawarma 帐篷可能与某名学生（甚至多名学生）的房屋在同一个坐标。

你想要找到购买 shawarma 帐篷的学生的最大可能数量以及此时帐篷的位置。

## 说明/提示

在第一个样例中，如果我们在 $(4,2)$ 放置 shawarma 帐篷，那么住在 $(4,2),(4,1)$ 和 $(5,1)$ 的学生将会购买它。

在第二个样例中，可以在 $(1,1)$ 放置 shawarma 帐篷，那么住在 $(0,0)$ 的两个学生将会购买它。

## 样例 #1

### 输入

```
4 3 2
1 3
4 2
5 1
4 1
```

### 输出

```
3
4 2
```

## 样例 #2

### 输入

```
3 100 100
0 0
0 0
100 200
```

### 输出

```
2
99 100
```

## 样例 #3

### 输入

```
7 10 12
5 6
20 23
15 4
16 5
4 54
12 1
4 15
```

### 输出

```
4
10 11
```

# 题解

## 作者：_Agave_ (赞：2)

**[题目](https://www.luogu.com.cn/problem/CF1271C)**

这道题他要我们找一个点，使得学生在上学时经过此点次数最多。

分析一下：

最短路每次都会从帐篷的东西左右一个格的位置，

所以我们帐篷地点选择的最优值一定在这四个点中


|  |  位置一|  |
| :----------: | :----------: | :----------: |
| 位置二 | 帐篷 | 位置三 |
|  | 位置四 |  |

我们就用一个桶记录四个位置的方案数。

对于每一个输入的 $x,y$ 我们这样判断：

$1.$ 在正东（正西，正南，正北）方向上，对应位置 $+1$

$2.$ （否则），与对应位置相邻的两个位置 $+1$ 

| 下与右 | ↓ | 下与左 |
| :----------: | :----------: | :----------: |
| → | 学校 |  ←|
|上与右 | ↑| 上与左 |

之后我们找出最大值并找出最大值对应的方位就行了

#### AC


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,sx,sy,way[5],dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0},num[5]={0,4,2,1,3};
//东西南北 
//          way[4]
//  way[2]  school  way[1]
//          way[3]
int main(){
	scanf("%d%d%d",&n,&sx,&sy);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);//用较快的输入输出方式，否则会有充裕（jishao）的时间 
		if(y==sy)way[sx>x?4:3]++;//way[3]与way[4] 
		else if(x==sx)way[sy>y?2:1]++;//way[1]与way[2]
		else{
			if(x>sx){way[3]++;}
			if(x<sx){way[4]++;}
			if(y<sy){way[2]++;}
			if(y>sy){way[1]++;}
		}
	}
	int maxn=max(max(max(way[1],way[2]),way[3]),way[4]);
	printf("%d\n",maxn);
	for(int i=1;i<=4;i++){
		if(way[i]==maxn){
			printf("%d %d",sx+dx[i],sy+dy[i]);//帐篷坐标 
			return 0;
		}
	} 
	return 0;
}

```


---

## 作者：破壁人五号 (赞：2)

## 题意

- 一座城市为 $10^9\times 10^9$ 的网格；
- 学校在 $(s_x,s_y)$，$n$ 个学生的家分别在 $(x_i,y_i)$（坐标均为整数）；
- 学生每天放学会沿网格走最短路线之一回家；
- 现在要在某个整点修一个小卖部（不能修在学校里，但可以与学生的家重合），假如学生某条回家路线能经过小卖部，这名学生一定会经过它；
- 小卖部最多同时在多少名学生的回家路线上？并求出小卖部此时的坐标。

## 题解

一方面，每名学生的家可以给家与学校围成的长方形中的每一个整点的贡献 +1，贡献最大的点显然最适合修小卖部，这个点的贡献就是答案。

另一方面，把小卖部往学校靠近肯定不会变劣，因为之前包含它的长方形现在依然包含它。小卖部既然不能修在学校里，那我们修在学校东南西北相邻的四个点显然是较优的。

于是统计这四个点的贡献，得出答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
 
int main(){
    int n=getint(),x=getint(),y=getint();
    int u=0,d=0,l=0,r=0;
    for(int i=0;i<n;i++){
        int xx=getint(),yy=getint();
        if(xx<x)d++;
        if(xx>x)u++;
        if(yy<y)l++;
        if(yy>y)r++;
    }
    int ans=max({u,d,l,r});
    cout<<ans<<endl;
    if(ans==d){
        cout<<x-1<<" "<<y<<endl;
    }else if(ans==u){
        cout<<x+1<<" "<<y<<endl;
    }else if(ans==l){
        cout<<x<<" "<<y-1<<endl;
    }else{
        cout<<x<<" "<<y+1<<endl;
    }
    return 0;
}
```


---

## 作者：WOWHandsome (赞：2)

## 前言

这题是我们昨天考试的 $\text{T3}$，其实挺水的，找到规律就行了。现有的题解，大多都是直接讲思路，不好理解。而本篇题解，我画了一张图，相信大家能够更好地理解这个贪心的规律。

## 思路

本题如果没有 **帐篷不能摆放在学校所在地** 这一条件，那么就很好想了：我们直接 **把帐篷放在学校** 不就行了吗？这样人人都能买帐篷了。

可是现在不能直接把帐篷放在学校，其实也很好想。我们直接把帐篷放在**学校的上、下、左、右(四周)** 就可以了。请看下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mkp807py.png)

在这张图中，我们假设帐篷分别在 $1,2,3,4$ 四个点上。那么：

$1$ 号帐篷将覆盖 区域 $\#1$ 的所有学生，即覆盖了位于学校左边的所有学生；

$2$ 号帐篷将覆盖 区域 $\#2$ 的所有学生，即覆盖了位于学校右边的所有学生；

$3$ 号帐篷将覆盖 区域 $\#3$ 的所有学生，即覆盖了位于学校上边的所有学生；

$4$ 号帐篷将覆盖 区域 $\#4$ 的所有学生，即覆盖了位于学校下边的所有学生。

我们如果随意移动 $1,2,3,4$ 号帐篷的任意一个，就会发现，**再也没有其他摆法能像这种摆法一样，覆盖这么广的区域了！**

那么，这题不就解完了吗！

我们只需要在读入时分别统计 $1,2,3,4$ 号帐篷 **能否覆盖到第 $i$ 个学生**。若能，在对应帐篷的 **统计变量** 上增加 $1$。

最后，输出这四个帐篷统计变量的 **最大值**，并输出能覆盖到最多学生的帐篷的坐标就可以了！

## 代码

~~(我讲的这么详细了注释就不用了吧qwq)~~ 

这里的代码实现的区域编号跟我上面所讲的有点不同，大家可以按照我上面所讲的区域编号来，也可以参照我代码的。

```cpp
# include <bits/stdc++.h>
using namespace std;

int n, x, y;
int ans1, ans2, ans3, ans4, _max;

signed main() {
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 1; i <= n; i++) {
		int p, q;
		scanf("%d%d", &p, &q);
		if (p < x) ans1++; 
		if (p > x) ans2++;
		if (q < y) ans3++;
		if (q > y) ans4++;
	}
	_max = max(max(ans1, ans2), max(ans3, ans4));
	printf("%d\n", _max);
	if (_max == ans1) printf("%d %d\n", x-1, y);
	else if (_max == ans2) printf("%d %d\n", x+1, y);
	else if (_max == ans3) printf("%d %d\n", x, y-1);
	else if (_max == ans4) printf("%d %d\n", x, y+1);
	return 0;
}
```

## 其他

好了，本篇题解就到这里了，如果你还是不懂或对代码有疑问，可以私信我，与我交流！

我的博客(周末会从洛谷博客更新) <https://www.baoyh.vip>

我的自建小OJ(可以作为刷题的补充题库) <https://www.dreamoj.com>

thanks！

---

## 作者：TEoS (赞：1)

通过分析样例可以发现，离学校越近的地点经过的路线也会越多，因此我们只要考虑学校周围的八个点即可。而且可以发现，对于一个点，路线会经过这个点的节点是确定的。因此在输入的时候可以统计学校周围八个节点被经过的次数，然后找最大的一个即可。注意判断边界。

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/12048490.html)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,sx,sy,ans=-1,ansx,ansy;
int dx[8]={-1,0,1,1,1,0,-1,-1},dy[8]={-1,-1,-1,0,1,1,1,0};
int cnt[8];//左上，上，右上，右，右下，下，左下，左 
void check(int x,int y)
{
	cnt[0]+=(x<=sx-1 && y<=sy-1);
	cnt[1]+=(y<=sy-1);
	cnt[2]+=(x>=sx+1 && y<=sy-1);
	cnt[3]+=(x>=sx+1);
	cnt[4]+=(x>=sx+1 && y>=sy+1);
	cnt[5]+=(y>=sy+1);
	cnt[6]+=(x<=sx-1 && y>=sy+1);
	cnt[7]+=(x<=sx-1);
}//统计
int main()
{
	scanf("%d%d%d",&n,&sx,&sy);
	for(int i=1,x,y;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		check(x,y);
	}
	for(int i=0,nx=sx+dx[i],ny=sy+dy[i];i<8;i++,nx=sx+dx[i],ny=sy+dy[i])
		if(nx>=0 && nx<=1e9 && ny>=0 && ny<=1e9 && cnt[i]>ans)
			ans=cnt[i],ansx=nx,ansy=ny;
	printf("%d\n%d %d",ans,ansx,ansy);
	return 0;
}
```


---

## 作者：Ezis (赞：1)

对于这道题，我们可以通过枚举样例，发现他只有八种情况：

左 $+$ 上

左 $+$ 下

右 $+$ 上

右 $+$ 下

上

下

左

右

在分别讨论即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int xx,yy;
int sum[10]; 
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&xx,&yy);	
		if(xx<x&&yy==y)
			sum[3]++;
		if(xx==x&&yy>y)
			sum[1]++;
		if(xx==x&&yy<y)
			sum[2]++;
		if(xx>x&&yy==y)
			sum[4]++;
		if(xx>x&&yy<y)
			sum[4]++,sum[2]++;
		if(xx<x&&yy<y)
			sum[3]++,sum[2]++;
		if(xx>x&&yy>y)
			sum[4]++,sum[1]++;
		if(xx<x&&yy>y)
			sum[3]++,sum[1]++;
	} 
	int ans=max(max(sum[1],sum[2]),max(sum[3],sum[4]));
	if(ans==sum[1]){ 
    	printf("%d\n%d %d",ans,x,y+1);
    	return 0;
  	}
	if(ans==sum[2]){
    	printf("%d\n%d %d",ans,x,y-1);
		return 0;
    }
	if(ans==sum[3]){
		printf("%d\n%d %d",ans,x-1,y);
		return 0;
	}
	if(ans==sum[4]){
		printf("%d\n%d %d",ans,x+1,y);
		return 0;
	}
	return 0;
}

```


---

## 作者：gyh20 (赞：0)

先用贪心的思想，小卖部在学校四周一定是最优的，依次判断每一个位置的就价值，找出最有用的即可。

```cpp
#include<cstdio>
#include<iostream>
#define re register
using namespace std;
int a,b,c,d,x,y,n,xx,yy;
int main(){
scanf("%d%d%d",&n,&x,&y);
while(n--){
	scanf("%d%d",&xx,&yy);
	if(yy>y)++a;
	if(xx<x)++b;
	if(yy<y)++c;
	if(xx>x)++d;
}
int tmp=max(a,max(b,max(c,d)));
if(tmp==a){
	printf("%d\n",a);
	printf("%d %d",x,y+1);
}
else if(tmp==b){
	printf("%d\n",b);
	printf("%d %d",x-1,y);
}
else if(tmp==c){
	printf("%d\n",c);
	printf("%d %d",x,y-1);
}
else{
	printf("%d\n",d);
	printf("%d %d",x+1,y);
}
}
```


---

## 作者：fls233666 (赞：0)

#### 比赛时的解法

看题面——看完想不出解法。

**看样例——好像有某种规律？！**

仔细观察样例，可以发现样例给出的 shawarma 帐篷所在位置都在学校所在位置相邻的四个方向之一的位置上！！

也许这就是规律？我打了一个枚举学校四个相邻位置放置帐篷，然后暴力统计购买帐篷的人数的代码，交了上去。让我没有想到的是：$\color{green} Pretest \ Passed$

比赛结束后，更让我没有想到的是：$\color{green} System\ Test\ Passed$

？？？？？

----------

### 赛后认真研究题目得出的解法

看题面中这一句话：第 $i$ 个学生到学校的距离是 $|s_x-x_i|+|s_y-y_i|$。

也就是说，每个学生只能走上下左右四个方向，不会直接斜着走到学校。

那么，每个学生都只能从与学校相邻的上下左右四个位置之一进入学校。

也就是说，**每个学生从家到学校的最短路径一定会经过与学校相邻的上下左右四个位置之一**。

最终，我们得到一个贪心策略：

- 枚举学校相邻的四个位置。
- 分别暴力枚举判断每个学生是否会购买这个位置上的帐篷，统计会购买的人数。
- 输出会购买的人数最多的一个位置和购买的人数即可。

这也证明了上面的那个规律为什么是对的。

那么下面，放上代码：

```cpp
#include<iostream>
#include<cstdio>
#define rgt register int
using namespace std;

int stux[200100],stuy[200100],gstu[200100];
//gstu[]存储每个学生到学校的最短距离

int px[4]={0,-1,1,0};
int py[4]={-1,0,0,1};

inline int _abs(int b){
	return b<0?-b:b;
}  //手写绝对值函数

int main()
{
	int n,sx,sy,ansx,ansy,ans=0;
	scanf("%d%d%d",&n,&sx,&sy);
	for(rgt i=1;i<=n;i++){
		scanf("%d%d",&stux[i],&stuy[i]);
		gstu[i]=_abs(stux[i]-sx)+_abs(stuy[i]-sy);
	}
    //读入数据
    
	for(rgt tp=0,i=0;i<4;i++,tp=0){   //枚举四个方向
		for(rgt fp,j=1;j<=n;j++){   //枚举每个学生
			fp=_abs(stux[j]-(sx+px[i]))+_abs(stuy[j]-(sy+py[i]));   //算出这个学生到帐篷的最短距离
			if(fp+1==gstu[j])    //如果这个学生到帐篷的最短距离+1是这个学生到学校的最短距离，证明这个帐篷在这个学生从学校到家的最短路径上，那么这个学生一定会购买帐篷
				tp++;    //统计会购买的人数
		}
		if(tp>ans){   //比较并更新答案
			ans=tp;
			ansx=sx+px[i];
			ansy=sy+py[i];
		}
	}
    
	printf("%d\n%d %d",ans,ansx,ansy);
	return 0;
}
```


---

