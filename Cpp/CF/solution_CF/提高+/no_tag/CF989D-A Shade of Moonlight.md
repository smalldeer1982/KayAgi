# A Shade of Moonlight

## 题目描述

 Gathering darkness shrouds the woods and the world. The moon sheds its light on the boat and the river."To curtain off the moonlight should be hardly possible; the shades present its mellow beauty and restful nature." Intonates Mino.

"See? The clouds are coming." Kanno gazes into the distance.

"That can't be better," Mino turns to Kanno.





The sky can be seen as a one-dimensional axis. The moon is at the origin whose coordinate is $ 0 $ .

There are $ n $ clouds floating in the sky. Each cloud has the same length $ l $ . The $ i $ -th initially covers the range of $ (x_i, x_i + l) $ (endpoints excluded). Initially, it moves at a velocity of $ v_i $ , which equals either $ 1 $ or $ -1 $ .

Furthermore, no pair of clouds intersect initially, that is, for all $ 1 \leq i \lt j \leq n $ , $ \lvert x_i - x_j \rvert \geq l $ .

With a wind velocity of $ w $ , the velocity of the $ i $ -th cloud becomes $ v_i + w $ . That is, its coordinate increases by $ v_i + w $ during each unit of time. Note that the wind can be strong and clouds can change their direction.

You are to help Mino count the number of pairs $ (i, j) $ ( $ i < j $ ), such that with a proper choice of wind velocity $ w $ not exceeding $ w_\mathrm{max} $ in absolute value (possibly negative and/or fractional), the $ i $ -th and $ j $ -th clouds both cover the moon at the same future moment. This $ w $ doesn't need to be the same across different pairs.

## 说明/提示

In the first example, the initial positions and velocities of clouds are illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989D/6b59db1b0f945dc8c0522b3919b522e12ff2a152.png)The pairs are:

- $ (1, 3) $ , covering the moon at time $ 2.5 $ with $ w = -0.4 $ ;
- $ (1, 4) $ , covering the moon at time $ 3.5 $ with $ w = -0.6 $ ;
- $ (1, 5) $ , covering the moon at time $ 4.5 $ with $ w = -0.7 $ ;
- $ (2, 5) $ , covering the moon at time $ 2.5 $ with $ w = -2 $ .

Below is the positions of clouds at time $ 2.5 $ with $ w = -0.4 $ . At this moment, the $ 1 $ -st and $ 3 $ -rd clouds both cover the moon.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989D/b8fb3c4da428759ede2c4e873e8aa9a06eae9b62.png)In the second example, the only pair is $ (1, 4) $ , covering the moon at time $ 15 $ with $ w = 0 $ .

Note that all the times and wind velocities given above are just examples among infinitely many choices.

## 样例 #1

### 输入

```
5 1 2
-2 1
2 1
3 -1
5 -1
7 -1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 10 1
-20 1
-10 -1
0 1
10 -1
```

### 输出

```
1
```

# 题解

## 作者：BYWYR (赞：4)

## 思路

原题说的是两个人的速度同时加 $w$，我们转换成月亮会进行移动。

月亮以每个时刻从中间向两侧移动最多 $w$ 个单位的速度移动。

我们可以把时间放在纵坐标，把位置放在横坐标，画出这样一张图。

![](https://s4.ax1x.com/2021/12/16/T979bt.png)

此图转载于 [Link](https://blog.csdn.net/c_czl/article/details/89646150)

对于两个人，如果它们的交集在黄色区域内，那么就能够在某一时刻同时覆盖月球。

对于这张图，显然我们只需要考虑相交的那个矩形的最上面的那个点。

- 相遇时间，$y=(X_2+L-X_1)/2$

- 相遇位置，$x=(X_1+X_2+L)/2$

在黄色区域内

$∴$ $y>=x/w$ 且 $y>=-x/w$

$∴ X_2+L-X_1>|X_1+X_2+L|/w$

只要满足以上条件即可。


------------


所以我们把向右走的位置和向左走的位置分开，分别排序，显然从左往右满足单调性。

然后就单调扫一遍就好了。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,l,w,a[100005],b[100005];
ll cnt1,cnt2,ans; 
int main(){
	cin>>n>>l>>w;
	for(int i=1;i<=n;i++){
		int u,v;
		cin>>u>>v;
		if(v==1) a[++cnt1]=u;//右边
		else b[++cnt2]=u;//左边
	}
	sort(a+1,a+1+cnt1);
	sort(b+1,b+1+cnt2);//排序
	for(int i=1,j=1;i<=cnt1;i++){
		while(j<=cnt2&&abs(a[i]+b[j]+l)>=1ll*w*(b[j]-a[i]+l))
			j++;
		ans+=cnt2-j+1;
	}//单调扫一遍
	cout<<ans<<endl;
   return 0;//完美结束
}

```



---

## 作者：minecraft_herobrine (赞：0)

### 题解

先复盘一下这个图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989D/6b59db1b0f945dc8c0522b3919b522e12ff2a152.png)

注意到若两个线段有公共点只可能是方向相反的情况，所以可以对每一个区间先按照方向分为两组，再按照端点位置排序，只有被分在不同组的才可能~~香♂蕉~~相交。

还有下面的两个规律：

- 所有同向区间的相对距离总是不变，因为所有同向区间都是相对静止的
- 给所有区间的速度加上 $w$，只会影响不同向区间相交的位置，并不会改变它们相交的时间，因为它们的相对速度还是 $2$

发现第二个规律改变区间的速度没有卵用，可以改写一下第二条规律为“给所有的区间速度加上 $w$ 等价于区间速度不变，给原点的速度加上 $w$ ”。

为了让读者更好理解，现在在平面上画一个二位的坐标系，其中x轴就是像上图一样的数轴，而y坐标表示的是时间，表示经过了 $y$ 秒之后的x轴是什么样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/7o5r5w8z.png)

阴影区域是两个线段的交点橙色线以上则被计入，因为原点添加的这个速度 $w$ 可正可负，所以是画出的橙色线的形状类似于绝对值函数。

假设左侧区间的左端点是 $x1$，右侧区间的左端点是 $x2$，则可以知道这两个区间的右端点分别为 $x1+L$ 和 $x2+L$。

不难发现只要交集持续的最后一刻只要在橙色线的上方就可以计入答案，而又根据上面那个图可以发现两个区间最后还有交集是在左区间左端点和右区间右端点的中点，也就是 $\frac{x1+(x2+L)}{2}$。相对应的时间便是用 $x2+L$ 减去这个位置就是 $\frac{x2+L-x1}{2}$。而两条橙色的直线方程是 $y=±x/w$ ，所以判定是否在橙色区域就可以了。

然后就用两个指针分别从两个方向值不同的组开始找，每次判断是否满足 $x2+L-x1>|x1+x2+L|/w$。为了避免除法，把式子改写成 $w*(x2+L-x1)>|x1+x2+L|$ 就可以了。

计算过程中有可能爆int，所以需要开long long。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN=1e5+10;
struct Segment
{
	ll x,d;
	bool operator < (const Segment &f) const
	{
		if(d==f.d) return x<f.x;
		return d>f.d;//把1放前面，-1放后面
	}
}s[MAXN];
int main()
{
	ll n,L,wmax,l,r,i,p=0,res=0;
	scanf("%lld %lld %lld",&n,&L,&wmax);
	for(i=1;i<=n;i++)
	{
		scanf("%lld %lld",&s[i].x,&s[i].d);
		if(~s[i].d) p++;//记录1区间
	}
	sort(s+1,s+n+1);
	l=1;r=p+1;//p点是1和-1的分界点，p是最后一个1区间的位置
	while(l<=p)
	{
		while(r<=n && labs(s[r].x+s[l].x+L)>=wmax*(s[r].x-s[l].x+L)) r++;
		res+=n-r+1;l++;
	}
	printf("%lld",res);
	return 0;
}
```

---

