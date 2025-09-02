# Robot Breakout

## 题目描述

## 题面翻译

有 $n$ 个机器人在一个平面上，第 $i$ 个机器人的位置是 $(X_i,Y_i)$。


在设计的时候，第 $i$ 个机器人可以执行的操作：

1. 位置从 $(X_i,Y_i)$ 变为 $(X_i-1,Y_i)$。

2. 位置从 $(X_i,Y_i)$ 变为 $(X_i,Y_i+1)$。

3. 位置从 $(X_i,Y_i)$ 变为 $(X_i+1,Y_i)$。

4. 位置从 $(X_i,Y_i)$ 变为 $(X_i,Y_i-1)$。

但设计出现了缺陷，某些机器人可能不能执行上述的某些操作。

你需要找一个点 $(A,H)$，使得 $n$ 个机器人都可以到达 $(A,H)$ 。注意，一开始的位置在 $(A,H)$ 也算到达，且对于 $A,H$ 的范围有限制 —— $-10^5\leq A,H \leq 10^5$。

## 样例 #1

### 输入

```
4
2
-1 -2 0 0 0 0
-1 -2 0 0 0 0
3
1 5 1 1 1 1
2 5 0 1 0 1
3 5 1 0 0 0
2
1337 1337 0 1 1 1
1336 1337 1 1 0 1
1
3 5 1 1 1 1
```

### 输出

```
1 -1 -2
1 2 5
0
1 -100000 -100000
```

# 题解

## 作者：chenlingxi (赞：13)

题意：给你一堆点，然后可以进行一些操作来移动点（如果有），问是否有可能使每个点最后移动到同一个点上

-----
显然，观察每个操作，得到以下几个结论

①：如果没有操作1，则最后点的横坐标一定大于等于该点的横坐标

就是它不能向左移

②：如果没有操作2，则最后点的纵坐标一定小于等于该点的纵坐标

③：如果没有操作3，则最后点的横坐标一定小于等于该点的横坐标

④：如果没有操作4，则最后点的纵坐标一定大于等于该点的纵坐标

那么每次就可以更新x和y的范围

如果maxx小于minx或者maxy小于miny那么无解

否则随便输出一个范围内的x，y

注意：初始赋值minx=miny=-1e5 maxx=maxy=1e5

因为题面上说了点的范围要在这之内

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,minx=-1e5,maxx=1e5,miny=-1e5,maxy=1e5;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			int a,b,c,d;
			scanf("%d%d%d%d",&a,&b,&c,&d);
			if(!a)minx=max(minx,x);
			if(!c)maxx=min(maxx,x);
			if(!b)maxy=min(maxy,y);
			if(!d)miny=max(miny,y);
		}
		if(minx>maxx||miny>maxy)printf("0\n");
		else printf("1 %d %d\n",minx,miny);
	}
}
```

---

## 作者：Zq_water (赞：5)

思路很简单，每次输入的 $f1$，$f2$，$f3$，$f4$ 都会把最大最小的坐标进行限制，我们只需要把 $minx$ 和 $x$ 取最大值，把 $maxx$ 和 $x$ 取最小值，把 $miny$ 和 $y$ 取最大值，把 $maxy$ 和 $y$ 取最小值，最后输出 $minx$ 和 $miny$ 就行了。

**注意**，当 $minx$ 比 $maxx$ 大时，或者 $miny$ 比 $maxy$ 大时，此时就没有符合的节点，则输出 $0$。


```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		int n,minx=-1e5,maxx=1e5,miny=-1e5,maxy=1e5;
		cin>>n;
		for(int i=1;i<=n;i++){
			int x,y,a,b,c,d;
			cin>>x>>y>>a>>b>>c>>d;
			if(!a) minx=max(minx,x);
			if(!c) maxx=min(maxx,x);
			if(!b) maxy=min(maxy,y);
			if(!d) miny=max(miny,y);
		}
		if(minx>maxx||miny>maxy) cout<<0<<endl;
		else cout<<1<<" "<<minx<<" "<<miny<<endl;
	}
}
```

---

## 作者：bigclever (赞：4)

显然，题目给出了每个机器人能否向四个方向移动的条件。我们可以通过这些条件来**约束**最终所有机器人都能到达的地方的**范围**。那么具体怎么约束呢？

设最终所有机器人都能到达的地方的左上角坐标为 $(a,b)$，右下角坐标为 $(c,d)$。观察后可以发现，对于任意操作，如果它**不能达成**，就可以更新范围。比如，如果第 $i$ 个机器人无法满足操作 $1$，那么最终的 $a$ **一定大于等于** $X_i$；如果第 $i$ 个机器人无法满足操作 $2$，那么最终的 $b$ **一定大于等于** $Y_i$。其它同理。最后若 $a>c$ 或 $b>d$，则无解；否则 $(a,b)$ 即为合法解。 

代码按上述思路模拟即可，不放了。

---

## 作者：Eazin_star (赞：3)

### 思路：
如果有这个操作不能做那么一定会对坐标产生影响。所以我们只需要用四个变量 $x1$，$x2$，$y1$，$y2$ 来表示。$x1$ 表示最小的 $x$，$x2$ 表示最大 $x$，$y1$ 表示最小的 $y$，$y2$ 表示最大的 $y$。
#### 坑点
如果 $x1$ 比 $x2$ 大或者 $y1$ 比 $y2$ 大，那么输出 $0$。


```cpp
#include <bits/stdc++.h>
using namespace std;

int t;


int main() {
	cin >> t;
	while (t--) {
		int n, x1=-1e5, x2=1e5, y1=-1e5, y2=1e5;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			int x, y, a, b, c, d;
			cin >> x >> y >> a >> b >> c >> d;
			if (!a)
				x1 = max(x1, x); //如果不能往左走，则当前x取最大
			if (!b)
				y1 = max(y1, y); //如果不能往上走，则当前y取最大
			if (!c)
				x2 = min(x2, x); //如果不能往右走，则当前x取最小
			if (!d)
				y2 = min(y2, y); //如果不能往下走，则当前y取最小
		}
		if (x1 > x2 || y1 > y2) //判是否无解
			cout << 0 << endl;
		else
			cout << 1 << " " << x1 << " " << y1 << endl;
	}	
	return 0;
}
```

---

## 作者：ys_kylin__ (赞：1)

[原题](https://www.luogu.com.cn/problem/CF1196C)

这一道题首先需要限定机器人的活动范围，也就是他能移动的区域。只需要把每一个机器人的活动范围框出来，最后就可以找出那个地方了。

而每次，如果机器人的活动有故障的话，就压缩他的活动范围，经过不断的压缩，机器人的相交点不断缩小，答案也就出来了。

- 注意，范围 $ \le 10^5$，$\ge -10^5$，所以要将框区域的数字定义为最大和最小。

接下来是代码部分。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,y,anx,any;
		scanf("%d",&n);
		x=1e5,y=1e5,anx=-1e5,any=-1e5;//因为要作比较 ，所以初始化为最大与最小
		for(int i=1,sx,sy,a,b,c,d;i<=n;i++){
			scanf("%d%d%d%d%d%d",&sx,&sy,&a,&b,&c,&d);
			if(b==0)//对于每一个信息，都要处理出机器人的活动范围
				y=min(y,sy);
			if(c==0)
				x=min(x,sx);
			if(a==0)
				anx=max(anx,sx);
			if(d==0)
				any=max(any,sy);
		}
		if(anx>x||any>y) //没有可到达的地方
			printf("0\n");
		else
			printf("1 %d %d\n",anx,any);//最后限制出的anx,any就是最后的答案
	}
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：1)

# Robot Breakout(CF1196C)
## 思路

这道题因为平面极大，暴力枚举每个点肯定会超时。所以，我们不妨从机器人出发。

我们可以枚举每个机器人可以执行的操作：

1. 位置从 $(X_i,Y_i)$ 变为 $(X_i-1,Y_i)$，即向左走。
2. 位置从 $(X_i,Y_i)$ 变为 $(X_i,Y_i+1)$，即向上走。

3. 位置从 $(X_i,Y_i)$ 变为 $(X_i+1,Y_i)$，即向右走。

4. 位置从 $(X_i,Y_i)$ 变为 $(X_i,Y_i-1)$，即向下走。

如果一个机器人执行不能执行操作 $4$，那么下图的蓝色区域为该机器人的行动范围：

![](https://cdn.luogu.com.cn/upload/image_hosting/b1lbjw3h.png)



那么很多个机器人，它们的集合点就应该是这些区域的相交处：

![](https://cdn.luogu.com.cn/upload/image_hosting/4y4eoz3d.png)

我们便可以用变量 $up,down$ 储存集合点 $y$ 坐标的上下界，$left,right$ 储存集合点 $x$ 坐标的上下界。

如果当前机器人，无法下行，则 $down=\max(down,a_iy)$；

如果当前机器人，无法左行，则 $left=\max(left,a_ix)$；

如果当前机器人，无法下行，则 $up=\min(up,a_iy)$；

如果当前机器人，无法左行，则 $right=\min(up,a_ix)$；

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5;
int n;
struct bot {
	int x, y;
	int f[5];
} a[MAXN];
int r=1e5, up=1e5, l=-1e5, down=-1e5;
void work(){
	r=1e5, up=1e5, l=-1e5, down=-1e5;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i].x);
		scanf("%lld", &a[i].y);
		for (int j = 1; j <= 4; j++) {
			scanf("%lld", &a[i].f[j]);
		}
		if(a[i].f[1]==0){//不能向左走
			l=max(l,a[i].x);
		}
		if(a[i].f[2]==0){//不能向上走
			up=min(up,a[i].y);
		}
		if(a[i].f[3]==0){//不能向右走
			r=min(r,a[i].x);
		}
		if(a[i].f[4]==0){//不能向下走
			down=max(down,a[i].y);
		}
	}
	if(l<=r&&down<=up) printf("1 %lld %lld\n",l,down);
	else printf("0\n");
}
signed main() {
	int q;
	scanf("%lld",&q);
	while(q--){
		work();
	}
	return 0;
}
```



---

## 作者：copper_ingot (赞：0)

蒟蒻的第二篇题解

这题的思路其实非常简单，就是计算出每个机器人可以行走的范围，然后找到所有机器人都可以到达的地方，也就是这些范围的交集。

对于每个机器人，如果它的运动没有任何问题的话，移动范围是这样的：

![CF1196C_1](https://cdn.luogu.com.cn/upload/image_hosting/wol8xdfs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们假设这个机器人不能往下，那么它的移动范围就变成了这样：

![CF1196C_2](https://cdn.luogu.com.cn/upload/image_hosting/49izozs0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果这个机器人还不能往左，范围就是这样：

![CF1196C_3](https://cdn.luogu.com.cn/upload/image_hosting/qdj46u5c.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果它只能往右，那么范围就变成了往右无限延伸的射线；如果机器人根本动不了，范围就是机器人所在的点。

那么根据样例的第二个点，我们可以做出如下的图：

![CF1196C_4](https://cdn.luogu.com.cn/upload/image_hosting/2qwz47kj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

图中绿点的位置就是三个机器人唯一可以聚集的地方。

我们可以定义四个变量 $mxx$、$mxy$、$mnx$ 和 $mny$ 用来记录机器人行走的范围，如果机器人移动有问题，那么就缩小范围。

最后输出一个范围内的位置即可。

记得要初始化为最大值或最小值。

贴上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000;
int t, n, mxx, mxy, mnx, mny;
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		mxx = MAXN, mxy = MAXN, mnx = -MAXN, mny = -MAXN;
		for (int i = 1; i <= n; i++){
			int x, y, f1, f2, f3, f4;
			scanf("%d%d%d%d%d%d", &x, &y, &f1, &f2, &f3, &f4);
			if (!f1) mnx = max(mnx, x);
			if (!f2) mxy = min(mxy, y);
			if (!f3) mxx = min(mxx, x);
			if (!f4) mny = max(mny, y);
		}
		if (mnx > mxx || mny > mxy) printf("0\n");
		else printf("1 %d %d\n", mnx, mny);
	}
	return 0;
}
```

---

