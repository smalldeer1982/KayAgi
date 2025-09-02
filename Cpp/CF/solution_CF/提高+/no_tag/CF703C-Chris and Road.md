# Chris and Road

## 题目描述

And while Mishka is enjoying her trip...

Chris is a little brown bear. No one knows, where and when he met Mishka, but for a long time they are together (excluding her current trip). However, best friends are important too. John is Chris' best friend.

Once walking with his friend, John gave Chris the following problem:

At the infinite horizontal road of width $ w $ , bounded by lines $ y=0 $ and $ y=w $ , there is a bus moving, presented as a convex polygon of $ n $ vertices. The bus moves continuously with a constant speed of $ v $ in a straight $ Ox $ line in direction of decreasing $ x $ coordinates, thus in time only $ x $ coordinates of its points are changing. Formally, after time $ t $ each of $ x $ coordinates of its points will be decreased by $ vt $ .

There is a pedestrian in the point $ (0,0) $ , who can move only by a vertical pedestrian crossing, presented as a segment connecting points $ (0,0) $ and $ (0,w) $ with any speed not exceeding $ u $ . Thus the pedestrian can move only in a straight line $ Oy $ in any direction with any speed not exceeding $ u $ and not leaving the road borders. The pedestrian can instantly change his speed, thus, for example, he can stop instantly.

Please look at the sample note picture for better understanding.

We consider the pedestrian is hit by the bus, if at any moment the point he is located in lies strictly inside the bus polygon (this means that if the point lies on the polygon vertex or on its edge, the pedestrian is not hit by the bus).

You are given the bus position at the moment $ 0 $ . Please help Chris determine minimum amount of time the pedestrian needs to cross the road and reach the point $ (0,w) $ and not to be hit by the bus.

## 说明/提示

Following image describes initial position in the first sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703C/29c6d6ae7640c49d6f34bc7000bfa7024e7323b1.png)

## 样例 #1

### 输入

```
5 5 1 2
1 2
3 1
4 3
3 4
1 4
```

### 输出

```
5.0000000000```

# 题解

## 作者：仗剑_天涯 (赞：1)

这个题目嘛，主流做法是凸包DP，~~但是我如果用的是凸包就不会来发题解了。~~

看了一下网上大佬的博客，有了启发：

考虑凸包上是否存在一个点，其到达y轴的时间比人经过那点的时间还短，如果存在，那么人不可能在凸包运动到y轴之前顺利到达对岸。

再考虑凸包上是否存在一个点，其到达y轴的时间比人经过的时间还长，如果存在，那么人不可能在凸包运动到y轴之后顺利到达对岸。

**如果同时存在着两个点，人必定会撞到凸包。**

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,bo1,bo2;
double w,v,u,mx,x[100010],y[100010];
int main()
{
    cin>>n>>w>>v>>u;
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&x[i],&y[i]);
    }
    for(int i=1;i<=n;i++)
    {
        if(x[i]/(v*1.0)<y[i]/(u*1.0)) 
	{
		bo1=1;
	}//凸包上是否存在一个点，其到达y轴的时间比人经过那点的时间还短，如果存在，那么人不可能在凸包运动到y轴之前顺利到达对岸。
        if(x[i]/(v*1.0)>y[i]/(u*1.0)) 
	{
		bo2=1;
	}//凸包上是否存在一个点，其到达y轴的时间比人经过的时间还长，如果存在，那么人不可能在凸包运动到y轴之后顺利到达对岸。
    }
    for(int i=1;i<=n;i++)
    {
        mx=max(x[i]/(v*1.0)+(w-y[i])/(u*1.0),mx);
    }
    if(bo1==1&&bo2==1)
    {
        printf("%.10lf",mx);
    }//如果同时存在着两个点，人必定会撞到凸包。
    else
    {
        printf("%.10lf",w/(u*1.0));
    }
    return 0;
}
```


[大佬原文链接（咕掉了记得告诉我一声）](https://blog.csdn.net/mengwuyaaa/java/article/details/799219)

---

## 作者：wang_freedom (赞：0)

### 思路：
简单结论题。

考虑 $y$ 轴上哪一个点满足条件，人的最大速度为 $u$，车速为 $v$，用路程 $x$ 减去路程 $y$ 除以人的速度 $u$ 再乘上车速 $v$，去算答案，推出方程：$x-\dfrac{y}{u}\times v$。
### AC Code：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
#define pii pair<int,int>
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int n;
double x,y,minn=1e10,maxn,w,u,v,ans;
signed main(){
	cin.tie(0);cout.tie(0);std::ios::sync_with_stdio(0);
    cin>>n>>w>>v>>u;
    rep(i,1,n){
    	cin>>x>>y;
    	minn=min(minn,x-y/u*v);
		maxn=max(maxn,x-y/u*v);
	}
	ans=w/u;
	if(minn<0)
		ans+=maxn/v;
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
/*

*/

```

---

## 作者：enyyyyyyy (赞：0)

可以考虑 $y$ 轴上哪一个点满足条件，人的最大速度为 $u$，汽车的速度为 $v$，便可以用路程 $x$ 减去路程 $y$ 除以人的速度 $u$ 再乘上车速 $v$，去算答案，便可以推出方程：

$$ x - \dfrac{y}{u} \times v $$

所以代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll n;
double x, y, minn = 11451419810, maxn = 0, w, u, v, ans; //double类型
int main() {
	n = read();//快读
	cin >> w >> v >> u;//读入
	while (n--) { //遍历n次
		cin >> x >> y;//读入
		minn = min(minn, x - y / u * v);//求出最小
		maxn = max(maxn, x - y / u * v);//求出最大
	}
	ans = w / u;
	if (minn < 0) ans += maxn / v;//判断如果先与0，那么额外加上
	printf("%.10lf", ans);//保留10位小数
	return 0;
}
```


---

