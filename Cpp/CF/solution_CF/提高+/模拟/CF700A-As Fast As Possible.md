# As Fast As Possible

## 题目描述

On vacations $ n $ pupils decided to go on excursion and gather all together. They need to overcome the path with the length $ l $ meters. Each of the pupils will go with the speed equal to $ v_{1} $ . To get to the excursion quickly, it was decided to rent a bus, which has seats for $ k $ people (it means that it can't fit more than $ k $ people at the same time) and the speed equal to $ v_{2} $ . In order to avoid seasick, each of the pupils want to get into the bus no more than once.

Determine the minimum time required for all $ n $ pupils to reach the place of excursion. Consider that the embarkation and disembarkation of passengers, as well as the reversal of the bus, take place immediately and this time can be neglected.

## 说明/提示

In the first sample we should immediately put all five pupils to the bus. The speed of the bus equals $ 2 $ and the distance is equal to $ 10 $ , so the pupils will reach the place of excursion in time $ 10/2=5 $ .

## 样例 #1

### 输入

```
5 10 1 2 5
```

### 输出

```
5.0000000000
```

## 样例 #2

### 输入

```
3 6 1 2 1
```

### 输出

```
4.7142857143
```

# 题解

## 作者：SamariumPhosphide (赞：5)

首先，要让时间最少的情况下，最好让所有人都同时到达目的地，否则就会出现互相等待的情况，必然不是最优解。

因此，我们不妨设所有人同时到达目的地所用时间为 $ans$，那么每个人坐车的时间也一定，设为 $t$。

我们不妨把学生分成 $\lceil \frac{n}{k} \rceil$ 批。

以 $4$ 批为例，车的行进路线如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/cake5jvy.png)

每批从上一批上车到这一批上车的距离均相等，设为 $S$，那么从上图中可以看出，路程总长度为  $(\lceil \frac{n}{k} \rceil - 1) \times S + t \times v_2$。 

那么我们只需要把 $S$ 用 $t$ 表示即可，考虑第一批做完车后到达的位置为 $v_2 \times t$，第二批此时到达了 $v_1 \times t$ 的位置，相遇路程为 $(v_2 - v_1) \times t$。相遇速度和为 $v_1+v_2$。那么相遇时间为 $\frac{(v_2-v_1) \times t}{v_1+v_2}$。所以第一组总共用时为 $t+\frac{(v_2-v_1) \times t}{v_1+v_2}=\frac{2v_2}{v1+v2}t$。因此 $S=\frac{2v_1 v_2 t}{v1+v2}$。

所以 $[(\lceil \frac{n}{k} \rceil - 1) \frac{2v_1 v_2}{v1+v2} + v_2] \times t=l$。

将 $t$ 解出并带入计算 $ans$ 即可。

---

## 作者：Level_Down (赞：2)

### 题意简述：

有 $n$ 个人想要到 $l$ 米远的地方，他们的走路速度为 $v1$，现在有一辆车，最多坐 $k$ 人，速度为 $v2$，每个人最多上一次车，问这些人都到达的最早时间。

### 方法：

其实之前的题解里讲得非常对，但是我太弱了，又因为没有代码，我理解了好久才理解透彻。

所以这里想帮助一下我这种蒟蒻。

首先将这些人分成 $\lceil \dfrac{n}{k} \rceil$ 批，用代码写就是 `(ceil(n / k))`

每个人的乘车时间 $t$ 是固定的,且可得方程式：

$[(\lceil \dfrac{n}{k} \rceil - 1) \dfrac{2v1v2}{v1 + v2} + v2] * t = l$

解出 $t$，我们可以算出每批人到达所需要的时间 $tt$ 为：

$tt = \dfrac{2v2}{v1 + v2}t$

然后将 $tt$ 乘与总组数减一再加上最后一组都坐车的用时 $t$ 就是答案了。

终于到最喜闻乐见的代码环节了！

```cpp
#include  <bits/stdc++.h>
using namespace std;
double n,l,v1,v2,k,t,ans;
int main()
{
	cin >> n >> l >> v1 >> v2 >> k;
	t = (l / ((ceil(n / k) - 1) * (2 * v1 * v2) / (v1 + v2) + v2));//解方程。
	ans = (2 * t * v2) / (v1 + v2) * (ceil(n / k) - 1) + t;//计算答案。
	printf("%.10lf",ans);//输出，注意保留至少六位小数。
	return 0;//AC！
}
```


---

## 作者：_lxy_ (赞：2)

### 题意
有 $n$ 个人想要到 $l$ 米远的地方，他们的走路速度为 $v1$ ，现在有一辆车，最多坐 $k$ 人，速度为 $v2$ ，每个人最多上一次车，问这些人都到达的最早时间。
### 分析
一道经典的小学奥数题。题目中“这些人都到大的最早时间”是最后一个人到达的时间，因此我们要尽量让每一批的人同时到达，并且保证一直有一批人在坐车，且坐满了。设每批人坐车  $x$ 千米，坐车和步行一次走的总路程是 $2\times x$,速度和是 $v1+v2$ 。设共分为 $p$ 批，$p=\lceil {n/k}\rceil
$ ，每批人步行的总时间是 $(p-1)\times(2 \times x \div (v1+v2))$ ，每批人步行的总路程是 $v1\times (p-1)\times (2\times x\div (v1+v2))$ 。表示出了每批人步行的总路程，又知道坐车的总路程是 $x$ ，所以我们可以列出方程
$s=x+v1\times (p-1)\times (2\times x\div (v1+v2))$，解得$x=s\times (v1+v2)\div (2\times v1\times (p-1)+v1+v2)$，然后 就可以得出最短时间。

### 代码
```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define elif else if
#define endl4 endl<<endl<<endl<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ld EPS=1e-8;
const ll INF=1e18+7;
const int inf=1e9+7;
inline ll llmax(ll x,ll y){return x>y?x:y;}
inline ll llmin(ll x,ll y){return x<y?x:y;}
inline ll llgcd(ll x,ll y){return (y==0?x:llgcd(y,x%y));}
inline ll lllcm(ll x,ll y){return x*y/llgcd(x,y);}
inline int gcd(int x,int y){return (y==0?x:llgcd(y,x%y));}
inline int lcm(int x,int y){return x*y/gcd(x,y);}
double n,s,v1,v2,k;
int main()
{
    scanf("%lf%lf%lf%lf%lf",&n,&s,&v1,&v2,&k);
    int p=ceil(n/k); // 分的批数
    double x=s*(v1+v2)/(2*v1*(p-1)+v1+v2); // 算出每批人坐车的时间
    printf("%.6lf",(s-x)/v1+x/v2); // 按照题意输出最短时间
    return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
数学题，担心被卡精度所以也采用了一点点的二分。
## 分析。
一辆车可以载上 $k$ 个人，那么我们把这 $n$ 个人均分，分成 $\frac{n+k-1}{k}$ 组，我们将这个式子记为 $p$。设需要的最短时间为 $t$ 同时每个人在车上待得时间为 $t_2$ 则我们可以列方程如下：
$$v_1\times\left(t-t_2\right)+v_2\times t_2=l$$
这个式子表示的是乘车 $t_2$ 单位时间以 $v_2$ 的速度通过的路程加上步行 $t-t_2$ 单位时间以 $v_1$ 的速度通过的路程为两地之间的总路程。

我们发现 $t_2$ 可以用 $t$ 来表示，现在的分析就是小学的追击与相遇问题了：每次车载完一组人，回来去载那个步行的那群人的这个过程就是一个典型的相遇和追逐的问题。那么我们设车回来接人需要的时间为 $t_3$ 则我们可以得到：
$$t_2\times\left(v_2-v_1\right)=t_3\times\left(v_1+v_2\right)$$
这个式子是根据车离开和返回中的路程不变这一点进行速度差公式得出的。又因为存在约束条件：
$$t_2\times p+t_3\times\left(p-1\right)\leq t$$
上面的 $p$ 前文已经定义过，这个式子显然成立。所以直接解方程就可以了。二分进行精度检验即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
using namespace std;
int n,k;
double v1,v2,l;
bool check(double t){
      double t2=(l-v1*t)/(v2-v1);
      double t3=(v2-v1)*t2/(v2+v1);
      int p=(n+k-1)/k;
      double ans=t2*p+t3*(p-1);
      if(ans<=t){
	      return 1;
	  }
      return 0;
}
int main(){
	cin>>n>>l>>v1>>v2>>k;
    double ll=l/v2,rr=l/v1;
    for(int i=1;i<=10000;i++){
        double mid=(ll+rr)/2;
		if(check(mid)){
		    rr=mid;
		}
        else ll=mid;
    }
	printf("%.10f\n",rr);
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

