# Road to Post Office

## 题目描述

Vasiliy has a car and he wants to get from home to the post office. The distance which he needs to pass equals to $ d $ kilometers.

Vasiliy's car is not new — it breaks after driven every $ k $ kilometers and Vasiliy needs $ t $ seconds to repair it. After repairing his car Vasiliy can drive again (but after $ k $ kilometers it will break again, and so on). In the beginning of the trip the car is just from repair station.

To drive one kilometer on car Vasiliy spends $ a $ seconds, to walk one kilometer on foot he needs $ b $ seconds ( $ a&lt;b $ ).

Your task is to find minimal time after which Vasiliy will be able to reach the post office. Consider that in every moment of time Vasiliy can left his car and start to go on foot.

## 说明/提示

In the first example Vasiliy needs to drive the first 2 kilometers on the car (in 2 seconds) and then to walk on foot 3 kilometers (in 12 seconds). So the answer equals to 14 seconds.

In the second example Vasiliy needs to drive the first 2 kilometers on the car (in 2 seconds), then repair his car (in 5 seconds) and drive 2 kilometers more on the car (in 2 seconds). After that he needs to walk on foot 1 kilometer (in 4 seconds). So the answer equals to 13 seconds.

## 样例 #1

### 输入

```
5 2 1 4 10
```

### 输出

```
14
```

## 样例 #2

### 输入

```
5 2 1 4 5
```

### 输出

```
13
```

# 题解

## 作者：QQH08 (赞：10)

终于有一道本蒟蒻能做出来的题了。

首先，题意有坑。我这里粘上貌似正确的题意。

$Vasiliy$ 要从家到 $d$ 千米远的警察局去， $Vasiliy$ 有一辆车，但很破旧，每行驶 $k$
千米就要坏掉，需修复 $t$ 秒才能重新启动，已知 $Vasiliy$ 开车开 $1$ 千米要 $a$ 秒，
步行 $1km$ 要 $b$ 秒（$a < b$） ,$ Vasiliy$ 可以在任何一个时刻步行，请问 $Vasiliy$ 最少
要多少秒才能到达警察局。

------------

这题一看就是分类讨论吧。

我分了$4$种情况：

1. 当$d<k$，显然开车快，所以答案就是$a*d$。
2. 全部开车，答案显然是$d*a+t*(d/k)$。
3. 从第一个样例中发现，可以先开车$k$公里，再走路，所以答案是$k*a+b*(d-k)$。（因为全部走路肯定比这个慢，所以不考虑全部走路）
4. 从第二个样例中发现，可以在最后一次要修车的时候，开始走路。所以答案是 $(d%k)*b+t*(d/k-1)+a*(d-d%k)$ 。

最后，这题还有一个坑点，车即使到终点报废了也要修车。

然后贴上我貌似非常短代码（~~点个赞再走嘛~~）：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll d,k,a,b,t;
int main(){
	scanf("%lld%lld%lld%lld%lld",&d,&k,&a,&b,&t);
	if(d<k){
		printf("%lld",a*d);
		return 0;
	}
	ll ans=k*a+b*(d-k);
	ans=min(ans,d*a+t*(d/k));
	ans=min(ans,(d%k)*b+t*(d/k-1)+a*(d-d%k));
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：__AFOier__ (赞：2)

这是本蒟蒻第一次发题解，语文不好，请原谅。

好了，本题解将聊一聊这道不用循环就能A的程序。

我们先推导一下公式。


设开了q次车（开k千米车算一次）之后才开始走路。

于是乎，可得：

总时间T=q*(a*k+t)(开了q次车，每次花a*k在路上，t在修车）
-t(最后一次不用修车）+b*(d-qk)(走路花了多久）

那我们比较一下q次与q+1次后停车的时间差：

q（ak+t)-t+b(d-qk)   VS  (q+1)(ak+t)-t+b(d-(q+1)k)

即：-t    VS    ak-bk

即  t+ak    VS   bk



所以停车时只有两种情况。

-1   t+ak>bk,此时最好开完一次就停车

-2   t+ak<bk 此时最好开到最后在停车

可是到了最后，又有新情况：

是修好车，继续开到完，还是弃车步行？

废话，当然哪个时间少就采用哪个方案

上代码;

```c
#include<iostream>
#include<cstdio>
#define LL long long//用来偷懒
using namespace std;
int main() {
	LL d,k,a,b,t,ans;
	scanf("%lld%lld%lld%lld%lld",&d,&k,&a,&b,&t);//输入，最好longlong
	//接下来是比较开到底快还是尽快弃车快
	if (t<(b-a)*k) {
		LL cat=d/k,kitty=d%k;
		if (t+kitty*a<b*kitty) ans=cat*(a*k+t)+a*kitty;
		else ans=cat*(a*k+t)-t+b*kitty;
		//比较修好车，继续开到完和弃车步行哪个快。
	} else {
		ans=a*k+b*(d-k);
	}
	printf("%lld",ans);//输出
	return 0;
	/*
        给一个好理解的题意
	题目描述
 	瓦徳有一辆车，他要从家去邮局。他家距邮局d公里。瓦徳的车很差，
 	它每行驶k公里就需要修理t秒后才能重新发动。开一公里汽车瓦徳需
 	要花a秒，步行一公里他需要花费b秒(a<b)。你的任务是求瓦徳到达邮
 	局的最短时间。瓦徳可以在任何时候离开车开始步行。
    输入
    第一行包含5个正整数d，k，a，b，t。
    输出
    求瓦徳到达邮局的最短时间。
	*/
}
```

PS :本蒟蒻第一次发题解，不喜勿喷。
PS：蒟蒻：读音（ju ruo）

我的博客：[](https://www.luogu.org/blog/catoj/)



---

## 作者：Aragron_II (赞：1)

#### [CF702D](https://www.luogu.com.cn/problem/CF702D) 题解



------------

就是一道小学数学题吧

#### 题目大意：

给你一个长度为 $ D $ 的路程，有两种行进方式，一种是选择用车行进，但是车子每行进 $ K $ 长度的路程之后，就会坏掉，如果想继续使用，就要用 $ t $ 时间去修复。

车子行进1单位要用 $ a $ 时间，步行1单位要用 $ b $ 时间，随时都可以弃车开始选择步行，问最短时间到达目的地。


------------

#### 思路：



1、首先将问题分成两种情况：

 ① $ d<k $

② $ d>=k $

对于第①种情况，也就是不需要修车子就可以选择车子驾驶到终点的话，那么输出是 $ min（d*a，d*b）$ ；题目中保证了 $ a<b $，那么答案一定是 $ d*a $ ；



2、然后考虑第②种情况，我们首先肯定一点，如果我们修了一次车的话，车子肯定要行进k单位长度是最优的，因为修完一次车子之后 ，在 $ k $ 单位内，车子行进一定是快于步行的。

那么问题关键就锁定在了修车子上来。

那么对于这种大情况，我们还可以分出来三种小情况，逐个分析：

①从起点到位子 $ K $ 用车，剩下部分就步行了。

②从起点到位子 $ d/k*k $ 用车，剩下部分用步行。

③从起点到终点都用车。

对于三种情况分别计数取最小即可。



------------


#### 代码：

```
#include <bits/stdc++.h> 
using namespace std;
long long d,k,a,b,t,ans,x;
int main() {
    cin >> d >> k >> a >> b >> t; //输入
	x = d / k;
	if ( k > d ) { //第一种情况
		cout << d * a << endl; //步行，输出
		return 0;
	}
    if ( k * a + t - k * b > 0) { //第二种情况
    	ans = k * a - k * b + d * b; 
	} else { //第三种情况
		long long sum1 = x * ( k * a - k * b + t ) + d * b - t;
		long long sum2 = x * ( k * a + t ) + ( d - x * k ) * a; 
    	ans = min ( sum1 , sum2 ); //取最小值
	}	
    cout << ans << endl; //输出答案
    return 0;
}
```



---

## 作者：Warriors_Cat (赞：1)

## ~~又来水一波CF的题了~~

看着这样一道这么水的灰题，怎么不忍心A掉Ta呢？

看了一下楼上的代码（~~其实楼上是我同学~~），感觉还是挺不错的，可本蒟蒻的思路和Ta却有所不同

刚看这道题，额...谁翻的译啊！跟题目丝毫沾不上边，幸亏我看了原题。

还有，本蒟蒻~~在一次比赛中~~做过这道原题，所以看到这道题也是激动不已啊！

其实这一道题可以用O(1)水过，

简单翻译一下此题：

有一人要从家到d千米的警察局去，Ta有一辆车，但很破旧，每行驶k千米就要报废，需修复t秒才能重新启动，已知Ta开车开1千米要a秒，步行1km要b秒（a < b）, Ta可以在任何一个时刻步行，请问Ta最少要多少秒才能到达警察局。

本蒟蒻的思路如下：

首先，先行k千米，然后判断坐车快还是走路快；

如果走路快，则直接下车；

如果坐车快，则到最后还要在特判一次；

最后输出，时间复杂度为O(1)。

## 具体代码如下：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long//宏定义 
ll d, k, a, b, t, ans;
int main(){
	ios::sync_with_stdio(false);//输入输出加快 
	cin >> d >> k >> a >> b >> t;
	if(d < k){//d小于k需要特判 
		cout << d * a;//直接坐车即可 
		return 0; 
	}
	ans += k * a;//先走k千米 
	if(t + k * a <= k * b){//判断走路还是坐车
	    //如果坐车 
		ans += (t + k * a) * (d / k - 1);//断点，还有最后几千米 
		int s = d - (d / k * k);//找出那几千米 
		if(t + s * a <= s * b) ans += t + s * a;//继续特判 
		else ans += s * b;
	}
	else ans += (d - k) * b;//如果走路则直接下车 
	cout << ans;
	return 0;
}
```
这就是本蒟蒻的思路，如有不懂者，欢迎留言。

## 求过！！

### 重要的事情说“一”遍！

谢谢各位读者的阅读以及管理员的审阅。

---

## 作者：BADFIVE (赞：0)

**题意** ： Vasiliy 要开车去一个地方，距离他家 $d$ $km$ ，他的车每行驶 $k$ $km$ 就需要修复 $t$ 秒才能继续前进，但是他有两种走法，一种是开车 $1$ $km$ 需要 $a$ 秒；另一种是走路 $1$ $km$ 需要 $b$ 秒。(易得 $a<b$)  
**思路** ：   
这里需要分类讨论：     
第一种情况 ： 当 $d<k$ 时，他就不需要修车，就可以直接到达目的地，所以答案为：距离乘以时间，即 $d \ast a$  
第二种情况 ： 当 $d \geq k$ 时，他就需要修车，但这里还需要分类讨论   
$\bullet(1)$ ： 开车走了 $k$ $km$ ，剩下的距离走路的时间比修车再开车过去的时间短   
$\bullet(2)$ ： 开车走了 $d/k \ast k$ $km$ ，剩下的路程用走路是最短时间   
还需要注意一个点，当 $d$ 刚好被 $k$ 整除，也就是说可以直接开车到终点，但是到了终点还需要修一次车，也就是在原来的时间上加 $t$ 。  
$AC$代码：   
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int d,k,a,b,t,ans=0,cnt=0;
	cin>>d>>k>>a>>b>>t;
	cnt=d/k;
	if(k>d){
		cout<<d*a;
		return 0;
	}
	if(k*a+t-k*b>0)cout<<k*a-k*b+d*b;
	else{
		int sum1=cnt*(k*a-k*b+t)+d*b-t;
		int sum2=cnt*(k*a+t)+(d-cnt*k)*a;
		cout<<min(sum1,sum2);
	}
}
```


---

## 作者：Dimly_dust (赞：0)

AC时我口吐芬芳了下：艹，竟然有129个测试点。。。

**讲下思路：**

首先可以模拟一下，可以想到，如果车速比步速块，那么前 $k$ 公里路肯定选择坐车，因为开始时车是好的，不用花费多余的时间来修理车，否则直接全程步行就好了(步速大于车速，必选步行)。

接下来我们把剩余的 $d-k(d > k)$ 公里路分为两段:

设 $othr=d \% k, car=d / k$，则就分为 $car * k$ 和 $othr$两段路。

对于前$car*k$ 公里路，如果选择开车(此时车已经坏了)

- 那么总时间就等于开车所需要的时间加上修车所需要的时间， $t1 = car * k * a + car * t$, 如果选择步行

- 那么$t2 = car * k * b$;选择时间短的就好了。对于剩余的 $othr$ 公里路开车需要 $t+othr *a$, 步行需要 $othr * b$，同样选择比较小的就好了。

**AC Code:**

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#define mearv(a, b) memset(a, b, sizeof(a))
#define mestrc(a, b, c) memset(&(a), b, sizeof(c))

typedef long long LL;
using namespace std;
const int MAXN = 100000;
const LL INF = 1e15;

int main()
{
    LL d, k, a, b, t;
    scanf("%I64d%I64d%I64d%I64d%I64d", &d, &k, &a, &b, &t);
    LL ans = 0;
    if(a < b)
    {
        if(d > k) ans += k * a, d -= k;//此时可以把路程分为两段。
        else ans += d * a, d = 0;//总路程小于乘一次车的路程，则直接开车走完全程
    }
    else ans += d * b, d = 0;//b步速大于车速，步行走完全程
    if(d > 0)
    {
        LL othr = d % k, car = d / k;
        if(car * (t + k * a) < car * k * b) ans += car * (t + k * a); //前car * k 公里的选择
        else ans += car * k * b;
        if(othr * b < t + othr * a) ans += othr * b; //后 othr公里的选择
        else ans += t + othr * a;
    }
    printf("%I64d\n", ans);
    return 0;
}
```


---

