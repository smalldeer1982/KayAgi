# Escape

## 题目描述

The princess is going to escape the dragon's cave, and she needs to plan it carefully.

The princess runs at $ v_{p} $ miles per hour, and the dragon flies at $ v_{d} $ miles per hour. The dragon will discover the escape after $ t $ hours and will chase the princess immediately. Looks like there's no chance to success, but the princess noticed that the dragon is very greedy and not too smart. To delay him, the princess decides to borrow a couple of bijous from his treasury. Once the dragon overtakes the princess, she will drop one bijou to distract him. In this case he will stop, pick up the item, return to the cave and spend $ f $ hours to straighten the things out in the treasury. Only after this will he resume the chase again from the very beginning.

The princess is going to run on the straight. The distance between the cave and the king's castle she's aiming for is $ c $ miles. How many bijous will she need to take from the treasury to be able to reach the castle? If the dragon overtakes the princess at exactly the same moment she has reached the castle, we assume that she reached the castle before the dragon reached her, and doesn't need an extra bijou to hold him off.

## 说明/提示

In the first case one hour after the escape the dragon will discover it, and the princess will be 1 mile away from the cave. In two hours the dragon will overtake the princess 2 miles away from the cave, and she will need to drop the first bijou. Return to the cave and fixing the treasury will take the dragon two more hours; meanwhile the princess will be 4 miles away from the cave. Next time the dragon will overtake the princess 8 miles away from the cave, and she will need the second bijou, but after this she will reach the castle without any further trouble.

The second case is similar to the first one, but the second time the dragon overtakes the princess when she has reached the castle, and she won't need the second bijou.

## 样例 #1

### 输入

```
1
2
1
1
10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
2
1
1
8
```

### 输出

```
1
```

# 题解

## 作者：_LSA_ (赞：4)

## 分析
这是一道很简单的数学题，小学我们就学过追及问题。

$$t = \Delta s/\Delta v $$
即时间等于路程差比速度差

我们只需算出会被追上几次，
每追上一次丢一次珍宝，然后计算龙回去并研究珍宝的时间，
然后再继续追。

### 坑点
因为计算时时间不一定是整数，所以用**double**等小数类型储存，还有如果龙的速度比公主的慢，直接特判输出**0**。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double vp,vd,t,f,c;
int main(){
	cin >> vp >> vd >> t >> f >> c;
	double s1 = vp*t , s2 = 0;
	int ans = 0;
	if(vp >= vd){//特判
		cout << 0;
		return 0;
	}
	while(s1 < c){
		t += (s1-s2)*1.0/(vd-vp);//计算追及时间
		s1 = s2 = t*vp;//现在路程
		if(s1 >= c) break;//一定要写前面，不然样例二过不去
		ans++;
		t += s2/vd+f;//龙回去研究后的时间
		s1 = vp*t;//现在路程
		s2 = 0;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：foryou_ (赞：1)

我们知道，题目要求**最少**需要的宝石数。

于是，当公主到达安全距离之前，我们可以让她**每次在龙要追上时丢下宝石**。

具体实现：

- 计算龙的追及时间并加入总时间内，同时更新公主和龙走的距离；

- 丢下一颗宝石，更新总时间，同时再次更新公主和龙走的距离。

核心代码：

```cpp
while(s1<c){
    t+=(s1-s2)/(vd-vp); s1=s2=t*vp; //step1
    if(s1>=c) break; //注意特判
    ans++; t+=s2/vd+f; //step2
    s1=t*vp; s2=0;
}
```

坑点：

- 注意开 `float/double`；

- 若 $vp \ge vd$，直接输出 `0` 即可。

---

## 作者：dfgz (赞：1)

## 题意
公主先跑 $t$ 小时，然后龙追她，她可以扔一个宝石拖住龙 $f$ 小时，求她活着走到离洞口 $c$ 要用多少时间。


------------
## 思路

先求出初始时间 $t$ 公主可以跑的距离
在求出龙追上公主用的时间，然后就是龙追上公主就扔宝石，即时间加上 $f$ 当距离到达 $c$ 时跳出循环。


------------
## 特判

公主速度比龙快时输出即可。

------------

这样处理关于宝石的 
```cpp
while(1)
{
	tt=x/v;
	x+=tt*vp;
	if(x>=c) break;
	else
	{
		ans++;
		x+=(f+tt)*vp;
	}
}
```


------------


$ACcode$


```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,vp,vd,t,f,c;
int main()
{
	cin>>vp>>vd>>t>>f>>c;//同题意
	if(vp>=vd)//特判
		cout<<ans<<endl;
	else
	{
		double x=vp*t*1.0;//初始距离
		int v=vd-vp;//速度差
		double tt;
		while(1)
		{
			tt=x/v;//龙追上公主的时间（追及时间）
			x+=tt*vp;
			if(x>=c) break;//已到终点
			else
			{
				ans++;//计数
				x+=(f+tt)*vp;//龙捡宝石时公主走的
			}
		}
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：luosw (赞：1)

我又来写题解了，放代码：（注释有说明qwq）

```cpp

#include <bits/stdc++.h>
#define ll long long
#define ms(a) memset(a,0,sizeof(a))
#define pi acos(-1.0)
#define INF 0x3f3f3f3f
const double E=exp(1);
const int maxn=1e6+10;
using namespace std;
int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	int vp,vd,t,f,c;
	cin>>vp>>vd>>t>>f>>c;
	int ans=0;
	// 注意公主速度不小于龙的速度的情况
	if(vp>=vd)
		cout<<ans<<endl;
	else
	{
		double x=vp*t*1.0;
		int v=vd-vp;
		double t1;
		while(1)
		{
			t1=x/v;
			x+=t1*vp;
			// 如果在龙整理宝石的过程中，公主已经到安全区域
			if(x>=c)
				break;
			else
			{
				ans++;
				x+=(f+t1)*vp;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
``

---

