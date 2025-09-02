# Hot Bath

## 题目描述

浴缸里有一个冷水龙头和一个热水龙头，流出的水温分别是 $t_1$ 和 $t_2$；它们的流速最大是 $x_1$ 和 $x_2$ 个单位每秒，并且可以调节到 $0$ 至最大流速间的任意一个整数速度。假如两个龙头的流速分别是 $y_1$ 和 $y_2$，那么最终的水温 $t$ 就是 $\dfrac{t_1\times y_1+t_2\times y_2}{y_1+y_2}$。

现在，你要安排两个水龙头的流速，满足： 

1. 最终水温不低于 $t_0$；
2. 在满足上一条的前提下，水温尽可能接近 $t_0$；
3. 在满足上一条的前提下，总流速尽可能大。

## 说明/提示

对于 $100\%$ 的数据，满足 $1\le t_1\le t_0\le t_2\le10^6$，$1\le x_1,x_2\le10^6$。

---
Translated by [残阳如血](/user/726139)。

## 样例 #1

### 输入

```
10 70 100 100 25
```

### 输出

```
99 33```

## 样例 #2

### 输入

```
300 500 1000 1000 300
```

### 输出

```
1000 0```

## 样例 #3

### 输入

```
143 456 110 117 273
```

### 输出

```
76 54```

# 题解

## 作者：Blunt_Feeling (赞：6)

# CF126A Hot Bath 题解
这是一道贪心题，贪心思想大致是先把两个水龙头的流速都开到最大，温度高了把热水流速降低一个单位，温度低了把冷水流速降低一个单位。当任意一个水龙头的流速小于0时结束循环。

值得一提的是，在while循环里要先考虑温度高的情况，再考虑温度低的情况。因为水温在一开始时肯定是偏高的，如果先考虑温度偏低的情况就有可能会出错。
```cpp
//定义
double best=0x3f3f3f3f,t;
pair<int,int> ans;
```
这里best用来存储最小的 t-t0 的值，所以要先给它赋一个较大的值；pair存储最佳的x1,x2。当然，再开两个变量来存储也是可以的。

这道题里还有一些比较坑的地方，详见代码。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t1,t2,x1,x2,t0;
double best=0x3f3f3f3f,t;
pair<int,int> ans;
int main()
{
	cin>>t1>>t2>>x1>>x2>>t0;
	double y1=x1,y2=x2;
	while(y1>=0&&y2>=0)//坑点一:这里是“>=”而不是“>”
	{
		t=double(t1*y1+t2*y2)/(y1+y2);//坑点二:别忘了转double
		if(t<t0) {y1--; continue;}//先考虑温度高的情况
		if(t-t0<best) best=t-t0,ans.first=y1,ans.second=y2;
		//坑点三:这里如果写成if(t<best)best=t的话会在精度上出问题
		y2--;//最后考虑温度低的情况
	}
	cout<<ans.first<<' '<<ans.second<<endl;
	return 0;
}
```

---

## 作者：Special_Tony (赞：5)

# 前置芝士
浓度问题中的十字交叉法（小学奥数）。

介绍一下十字交叉法（如果已经学过请跳过）：若冷水温度 $t1$，热水温度 $t2$，需求的温度为 $t0$，则冷热水流速之比为 $t2-t0:t0-t1$（注意不是 $t0-t1:t2-t0$）。

证明：$\frac{(t2-t0)\times t1+(t0-t1)\times t2}{(t2-t0)+(t0-t1)}=\frac{t2\times t1-t0\times t1+t0\times t2-t1\times t2}{t2-t1}=\frac{t0(t2-t1)}{t2-t1}=t0$。
# 思路
既然知道了流速之比，那我们只需要枚举冷水流速 $y1$（枚举热水流速同理），热水流速就可以 $O(1)$ 得出：$y2=\lceil y1\times\frac{t0-t1}{t2-t0}\rceil$，这里可以用 double，但是为了避免精度误差，这只蒟蒻还是使用了整数运算的方法：$y2=\lfloor\frac{y1\times(t0-t1)+t2-t0}{t2-t0}\rfloor$。当然如果此时 $y1>x2$ 了就不用继续枚举了，直接退出循环。如果当前答案比之前的最优答案不劣（$\frac{y2}{y1}\le\frac{ans1}{ans0}$），那就更新答案。同样为了避免精度误差，我们可以把这个式子改变一下：$\frac{y2}{y1}\le\frac{ans2}{ans1}\to\frac{y2}{y1}\times y1\times ans1\le\frac{ans2}{ans1}\times y1 \times ans1\to y2\times ans1\le ans2\times y1$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t1, t2, x1, x2, t0, ans1, ans2, t;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t1 >> t2 >> x1 >> x2 >> t0;
	if (t0 == t1)
		if (t0 == t2)
			cout << x1 << ' ' << x2;
		else
			cout << x1 << " 0";
	else if (t0 == t2)
		cout << "0 " << x2;
	else {
		ans2 = x2;
		for (int i = 1; i <= x1; ++ i) {
			t = ((ll) (t0 - t1) * i + t2 - t0 - 1) / (t2 - t0);
			if (t > x2)
				break ;
			if ((ll) t * ans1 <= (ll) ans2 * i)
				ans1 = i, ans2 = t;
		}
		cout << ans1 << ' ' << ans2;
	}
	return 0;
}
```

---

## 作者：yzx72424 (赞：4)

~~我也不知道这是贪心还是模拟QAQ（可能因为我太蒻了）~~
 

先假定水都放满，如果温度低了就降低水温低的出水速度，温度高了就简单水温高的出水速度。

 复杂度的话≈O(x1+x2) ~~=O(能过)~~

---

## 作者：xiaomimxl (赞：1)

# 题意：

两个水龙头出水温度为 $t_1$, $t_2$, 出水速度 $y_1$, $y_2$ 在 0 到 $x_1$, $x_2$ 之间调节，根据公式 $t=(t_1 \times y_1+t_2 \times y_2)\div(y_1+y_2)$ 算出水温，给定 $t_0$，要求温度在 $t_0$ 以上并尽可能接近 $t_0$，满足条件的多组数据中选出水速度最快的。要求输出为整数。所有数据范围为 $10^6$内 ``int``。

# 思路：

很容易想到直接数学计算，但是由于要求输出的是 ``int``，很难处理精度、误差。可以先假定水都放满，若温度过低则降低水温低的出水速度，反之亦然。每次变化都为 1，则复杂度为 ``x1+x2`` 。记录最低差值的即可。

# Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main ()
{
    long long int   t1,t2,t0,x1,x2;
    double t,min;
    long long int y1,y2;
    while (cin >>t1>>t2>>x1>>x2>>t0)
    {
       min=1e20;
       while (x1>=0 &&x2>=0)
       {
            t=(double)(t1*x1+t2*x2)/(x1+x2);
            if(t<t0)//小于要求的温度t0，说明此时的冷水的流量过大了，冷水的流量减少
            {
                x1--;
            }
            else
            {
                if(t<min)  // 当前流量x1，x2已经满足大于t0了 但是需要寻找满足大于t0的最小值
                           //所以 用一个 比较变量min来记录 当前的最小t
                {
                    min =t;
                    y1=x1;
                    y2=x2;
                }
                x2--;//此时满足t>t0，如果继续减小热水流量，若减少流量后 ，更新后的t依旧大于t0
                     //观察此时的t是否比 min小；如果小于t0了，则继续减少冷水的流量使其继续满足大于
                     //t0在进行，上述操作，一直到x1x2中一个变为0.
            }
       }
        cout<<y1<<" "<<y2<<endl;
    }
    return 0;
 
}
```


---

## 作者：baoxuanming (赞：1)

今天，我们来看一下CF126A。
先上原题：

	浴缸里有一个冷水龙头和一个热水龙头，流出的水温分别是t1和t2；
   	它们的流速最大是x1和x2个单位每秒，并且可以调节到0至最大流速间的
    任意一个整数速度。假如两个龙头的流速分别是y1和y2，那么最终的水温就是
    t = ((t1y1)+(t2y2))/(y1+y2)
    现在，你要安排两个水龙头的流速，满足： 1、最终水温不低于t0；
    2、在满足上一条的前提下，水温尽可能接近t0； 3、在满足上一条的前提下，
    总流速尽可能大。
	1 <= t1 <= t0 <= t2 <= 10^6;1 <= x1, x2 <= 10^6

看完这题你想到了什么？
对，枚举。
我们可以枚举y1 和 y2，用for循环嵌套就行。如：
```
for(int y1=0;y1<=x1;y1++)
   for(int y2=0;y2<=x2;y2++)
	{
		/*
			插入计算
		*/
	}
```
然后定义一个max，为适合值；再有一个a，计算与t0的差，有小于它的就刷新，最后得到max。


---

## 作者：To_Carpe_Diem (赞：0)

# Hot Bath 题解

## 题目简述

$5$ 个正整数 $t_{1}$，$t_{2}$，$x_{1}$，$x_{2}$，$ t_{0} $。

这是一个简单的**数学推理题**。我们需要找到两个龙头的流速 $y_1$ 和 $y_2$，使得满足以下条件：

1. 最终水温不低于 $t_0$；

2. 在满足上一条的前提下，水温**尽可能接近** $t_0$；

3. 在满足上一条的前提下，**总流速**尽可能大。

## 思路实现

根据题目描述，我们可以得出以下结论：

- 如果 $t_1 \geq t_0$，那么只需打开冷水龙头即可，此时 $y_1$ 取最大值 $x_1$，$y_2$ 取 0。

- 如果 $t_2 \leq t_0$，那么只需打开热水龙头即可，此时 $y_1$ 取 0，$y_2$ 取最大值 $x_2$。

接下来我们考虑 $t_1 < t_0 < t_2$ 的情况。我们可以将问题分成**两个子问题**：

1. 打开冷水龙头，关闭热水龙头：此时只需调节冷水龙头的流速 $y_1$。根据公式 $\dfrac{t_1\times y_1}{y_1} = t_1$，我们可以得到此时的水温。如果水温小于 $t_0$，则继续减小 $y_1$ 的值；如果水温大于等于 $t_0$，则记录下此时的**流速和水温差**。

2. 打开热水龙头，关闭冷水龙头：此时只需调节热水龙头的流速 $y_2$。根据公式 $\dfrac{t_2\times y_2}{y_2} = t_2$，我们可以得到此时的水温。如果水温大于 $t_0$，则继续增大 $y_2$ 的值；如果水温小于等于 $t_0$，则记录下此时的**流速和水温差**。

最后，我们从两个子问题中找到**水温差最小**的情况即可。

## Code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    long long t1, t2, x1, x2, t0;
    cin >> t1 >> t2 >> x1 >> x2 >> t0;

    double minDiff = 1e9; // 记录水温差的最小值
    pair<int, int> ans; // 记录结果

    // 子问题一：打开冷水龙头，关闭热水龙头
    for (int y1 = x1; y1 >= 0; y1--) {
        double temp = t1 * y1 / (double)y1; // 计算水温
        if (temp < t0) {
            break; // 水温小于 t0，继续减小 y1 的值
        }
        if (temp - t0 < minDiff) {
            minDiff = temp - t0;
            ans = make_pair(y1, 0);
        }
    }

    // 子问题二：打开热水龙头，关闭冷水龙头
    for (int y2 = x2; y2 >= 0; y2--) {
        double temp = t2 * y2 / (double)y2; // 计算水温
        if (temp >= t0) {
            break; // 水温大于等于 t0，继续增大 y2 的值
        }
        if (t0 - temp < minDiff) {
            minDiff = t0 - temp;
            ans = make_pair(0, y2);
        }
    }

    cout << ans.first << " " << ans.second << endl;

    return 0;
}
```

该解法的时间复杂度为 $O(x_1 + x_2)$，即龙头的最大流速和。

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF126A)

我们来看看这道题目，让我们找到在水温不低于 $t_0$ 的情况下，尽可能的接近 $t_0$，并且总流速尽可能大。

我们可以直接从 $x_1$ 和 $x_2$ 枚举一下，直到流速为**负数时停止**即可（这个需要注意）。

我们最小的数需要设定为 $1\times10^7$。

还有最主要的思想，就是贪心。

如果水温高了，那么调低热水的流速。

如果水温低了，那么调低冷水的流速。

我们的代码就这样出来了：

注意一点，在循环中不需要特判 $y1+y2$ 是否为 $0$（我就被这个卡了 $20min$）。

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int t1,t2,x1,x2,t0;
double maxx=1e7,t;
int ans_1,ans_2;
int main(){
	scanf("%d%d%d%d%d",&t1,&t2,&x1,&x2,&t0);//输入
	double y1=x1,y2=x2;
	while(y1>=0&&y2>=0){//开始循环
		t=double(t1*y1+t2*y2)/(y1+y2);//这里不需要特判
		if(t<t0){
			y1--;
			continue;
		}
		if(t-t0<maxx){
			maxx=t-t0;
			ans_1=y1;
			ans_2=y2;
		}
		y2--;
	}
	printf("%d %d",ans_1,ans_2);
	return 0;
}
```

---

## 作者：zct_sky (赞：0)

### Solution:
-----
首先我们可以把题目的式子进行化简：

$$t_0 = \dfrac{t_1y_1 + t_2y_2}{y_1 + y_2}$$

$$t_0 = \dfrac{t_1y_1 + t_1y_2 + y_2(t_2 - t_1)}{y_1 + y_2}$$

$$t_0 = t_1 + \dfrac{y_2(t_2 - t_1)}{y_1 + y_2}$$

$$\dfrac{t_0 - t_1}{t_2 - t_1} = \dfrac{y_2}{y_1 + y_2}$$

$$\dfrac{y_2}{y_1} = \dfrac{t_0 - t_1}{t_2 - t_0}$$

于是题意就变成了：

1. 分数 $\dfrac{y_2}{y_1}$ 满足 $0 \le y_2 \le x_2, 0 \le y_1 \le x_1$。

2. 在满足以上条件的前提下，$\dfrac{y_2}{y_1} \ge \dfrac{t_0 - t_1}{t_2 - t_0}$。

3. 在满足以上条件的前提下，$\dfrac{y_2}{y_1} - \dfrac{t_0 - t_1}{t_2 - t_0}$ 最小。

4. 在满足以上条件的前提下，$y_2,y_1$ 尽量大。

由于精度 ~~及本人实力~~ 问题，我们可以枚举 $y_1$ 的值，求出 $y_2$ 的近似值，并更新答案。

对于一些特殊情况，需要进行特判：

- $t_0 - t_1 = 0 \And t_0 - t_1 = 0$ 即 $t_0 = t_1 \And t_0 = t_2$，最佳答案为 $y_1 = x_1,y_2 = x_2$。

- $t_0 - t_1 = 0 \And t_0 - t_1 \ne 0$ 即 $t_0 = t_1 \And t_0 \ne t_2$，最佳答案为 $y_1 = x_1,y_2 = 0$。

- $t_0 - t_1 \ne 0 \And t_0 - t_1 = 0$ 即 $t_0 \ne t_1 \And t_0 = t_2$，最佳答案为 $y_1 = 0,y_2 = x_2$。

时间复杂度为 $\Theta(x_1)$。

### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
ll t1,t0,t2,x1,x2,up,down;
const double eps=1e-14;
int main(){
	t1=read();t2=read(),x1=read();x2=read();t0=read();
	up=t0-t1;down=t2-t0;
	if(!up||!down){//特判 
		printf("%lld %lld",x1*(!up),x2*(!down));
		return 0;
	}
	double tp=up*1.0/down;
	ll y1=0,y2=x2;//y1枚举范围为 1-x1，若没找到，说明 y1=0，此时最优解 y2=x2 
	
	double y3=1145141919810;
	for(ll i=1;i<=x1;i++){
		ll j=(ll)(i*tp+0.5);
		for(ll jj=j-3;jj<=j+3;jj++){
			if(jj>x2)break;
			if(jj<0)continue;
			
			double k=jj*1.0/i;
			if(k<tp-eps)continue;
			
			if(y3-k>eps||y3==k){
				y3=k;
				y1=i;
				y2=jj;
			}
		}
	}
	printf("%lld %lld",y1,y2);
	return 0;
}
```

---

## 作者：felixshu (赞：0)

 **[我是传送门](https://www.luogu.com.cn/problem/CF126A)**

这题是贪心，开始时，把水都开到最大，也就是最大流速。

然后，如果水温高于 $T0$。就把冷水增多。但水温高于 $T0$ 时，就要考虑尽可能的低。

所以，用 $min$ 来求与 $T0$ 温度差的最小值。 (如果是 $min$ 求温度最小值而不是温度差，精度会出现问题）。

水流速度在 $0$ 与最大流速之间，枚举出温度大于 $T0$，温度最接近 $T0$ 的流速。

然后输出温度最小时的流速就好了。

## 下面是AC代码
```
#include<bits/stdc++.h>
using namespace std;
int  t1,t2,t0,x1,x2,p1,p2;
double t,minn=1e6;
int main()
{
	cin>>t1>>t2>>x1>>x2>>t0;
	double y1=x1,y2=x2;
	while(y1>=0&&y2>=0)//这里用>=,不能等于.
	{
		t= double((t1*y1)+(t2*y2))/(y1+y2) ;//求出温度，要转double
		if(t<t0)
		{
			y1--;//温度过低，减少冷水
		}
		else{
			if(t-t0<minn)//求出温度差的最小值
			{
				minn=t-t0;
				p1=y1;	
				p2=y2;
			}
			y2--;//减少热水，如果依然大于t0。
            		//就p1=y1   p2=y2
			}
	}
	cout<<p1<<" "<<p2<<endl;
	return 0;
}
```

---

