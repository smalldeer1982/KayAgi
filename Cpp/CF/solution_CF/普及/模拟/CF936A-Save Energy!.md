# Save Energy!

## 题目描述

Julia is going to cook a chicken in the kitchen of her dormitory. To save energy, the stove in the kitchen automatically turns off after $ k $ minutes after turning on.

During cooking, Julia goes to the kitchen every $ d $ minutes and turns on the stove if it is turned off. While the cooker is turned off, it stays warm. The stove switches on and off instantly.

It is known that the chicken needs $ t $ minutes to be cooked on the stove, if it is turned on, and $ 2t $ minutes, if it is turned off. You need to find out, how much time will Julia have to cook the chicken, if it is considered that the chicken is cooked evenly, with constant speed when the stove is turned on and at a constant speed when it is turned off.

## 说明/提示

In the first example, the chicken will be cooked for 3 minutes on the turned on stove, after this it will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/946fbd87d05fe2e24b8af4d0aa7735f7b1052cc7.png). Then the chicken will be cooked for one minute on a turned off stove, it will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/a9bdc1b9aee6e89dbd96641ebe23053a20526f44.png). Thus, after four minutes the chicken will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/6991f0a9cff42170b98fc979c8ddd5223ae7cf0e.png). Before the fifth minute Julia will turn on the stove and after $ 2.5 $ minutes the chicken will be ready ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/b3b22ef8237f8837aeb119d85eaee973ea63486d.png).

In the second example, when the stove is turned off, Julia will immediately turn it on, so the stove will always be turned on and the chicken will be cooked in 20 minutes.

## 样例 #1

### 输入

```
3 2 6
```

### 输出

```
6.5
```

## 样例 #2

### 输入

```
4 2 20
```

### 输出

```
20.0
```

# 题解

## 作者：hjsxhst2022 (赞：4)

[原题](https://www.luogu.com.cn/problem/CF936A)

小学数学！小学数学！！小学数学！！！

这一道题很明显是周期问题，步骤如下：

计算 $d$ 的几倍达到 $k$，即为一个周期

计算周期内鸡肉能够烤熟多少，然后看一下有几个这样的循环就好了。

按照上述步骤模拟就好了。

代码：
```
#include<bits/stdc++.h>//似乎不符合小周老师的做法））
using namespace std;
int main(){
	long long n,m;//注意了，开long long才能过
	double k,d,t,x,qwq,qaq;//输入不一定是整数
	cin>>k>>d>>t;
	n=(k-1)/d+1;//一个周期
	x=n*d;//一个周期会开关几次炉子
	m=t*2/(x+k);
	qwq=t*2-(x+k)*m;
	qaq+=x*m;
	if(qwq<=k*2-1)
		qaq+=qwq/2;
	else
		qaq+=k,qaq+=qwq-k*2;
	cout<<setprecision(10)<<qaq;//误差不超过10^9
}
```

---

## 作者：Provider (赞：4)

## 模拟

先求出d的几倍可以完全覆盖k 

然后把这个作为一个周期

计算周期内对食物能够烤熟多少 

然后看一下有几个这样的循环

最后结尾讨论一下即可

## CODE：

```
#include<bits/stdc++.h>
using namespace std;
double k,d,t,ans=0,r,rlen,change,rou;
int main()
{
    cin>>k>>d>>t; 
	r=(long long)((k-1)/d)+1;
	rlen=r*d;
	change=(long long)(2*t/(rlen+k));
	rou=2*t-(rlen+k)*change;
	ans+=change*rlen;
	if(rou<2*k) 
	ans+=rou/2;
	else ans+=k,ans+=rou-2*k;
	cout<<fixed<<setprecision(1)<<ans;
	return 0;
}
```

[搬运官方题解](http://codeforces.com/blog/entry/58056)

---

## 作者：hao_zi6366 (赞：2)



## 做题思路
一但炉子关闭 Julia 就会打开炉子，所以我们可以把一次的打开炉子作为周期。

这一个周期中包含了打开时的烹饪时间 $t_1$ 和关闭时的烹饪时间 $t_2$，由此可以算出一个周期可以达到的烹饪时间即 $n\times t_1+t_2$。

接着可以算一共需要几个周期，再用每个周期所花的时间与数量相乘并加上最后剩下的时间就可以了。

但要注意最后剩下的时间要分成关炉子和开炉子来讨论。

## 完整代码
```cpp
#include<bits/stdc++.h>
typedef long long ll;

int main(){
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
	
	double d,t,k;
	std::cin>>k>>d>>t;
	double yici=(std::ceil(k/d)*d-k)/2+k;			//算出一次可以完成的量
	ll cishu=t/yici;
	double yu=(t-yici*cishu),ans;					//算出剩下的时间
	if(yu<=k) ans=yu+(std::ceil(k/d)*d)*cishu;		//讨论剩下的时间
	else ans=(std::ceil(k/d)*d)*cishu+k+(yu-k)*2;
	std::cout<<std::fixed<<std::setprecision(9)<<ans;
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

## 题目描述

[Save Energy!](https://www.luogu.com.cn/problem/CF936A)

## 思路

### 遇事不决，小学数学。

#### 周期问题

先求出 $d$ 的几倍可以达到 $k$，并把这个作为一个周期。

然后计算在这个周期里面能烤熟多少鸡肉，看一下有几个这样的循环。

最后分类讨论就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
double k,d,t,len,cnt,ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>d>>t;
	n=(k-1)/d+1;
	len=n*d;
	m=t*2/(len+k);
	cnt=t*2-(len+k)*m;
	ans+=len*m;
	if(cnt<=k*2-1)
	{
		ans+=cnt/2;
	}
	else
	{
		ans+=k;
		ans+=cnt-k*2;
	}
	printf("%.9lf\n",ans);
	return 0;
}
```

---

## 作者：JustinXiaoJunyang (赞：2)

前排芝士：

Q：`setprecision` 函数如何使用？

A：`setprecision` 与 `printf` 设置精度相似，`setprecision()` 表示输出有效位，`setprecision(x) << fixed` 表示输出小数点后 $x$ 位。

思路分析：

这一道题很明显是周期问题，步骤如下：

1. 计算 $d$ 的几倍可以达到 $k$，并作为一个周期

2. 计算周期食物能烤熟的量

3. 计算周期次数

参考代码：

代码实现很简单，按照上述步骤模拟即可通过本题。

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double k, d, t;
	cin >> k >> d >> t;
	double small = (long long)((k - 1) / d) + 1;// min 这个变量名与 C++ 自带的函数重名，会 CE
	double small_len = small * d;
	double num = (long long)(2 * t / (small_len + k));
	double times = 2 * t - (small_len + k) * num;
	double ans = 0;
	ans += num * small_len;
	if (times < 2 * k) ans += times /2;
	else ans += k, ans += times - 2 * k;
	cout << fixed << setprecision(1) << ans;
	return 0;
}
```


---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF936A)

这题就是个简单的周期问题。我们只需要按照如下方法即可。

## 题目做法

我们只需要计算 $d$ 的几倍可以达到 $k$ ，也就是**一个周期**。

我们接着只需要计算周期内 Julia 的鸡肉能够烤熟多少，然后我们只需要看一下**有多少个这样的周期**就好了。

温馨提示：不开 `long long` 会见祖宗哦。

## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
double k, d, t, x, a, times;

signed main() {
	cin >> k >> d >> t;

	cout.flags(ios::fixed);
	cout.precision(1);

	n = (k - 1) / d + 1;
	x = n * d;
	m = t * 2 / (x + k);
	a = t * 2 - (x + k) * m;
	times += x * m;

	if (a <= k * 2 - 1) times += a / 2;
	else {
		times += k;
		times += a - k * 2;
	}

	cout << times;
	return 0;
}
```

讲两个代码里的东西，知道的大佬可以跳过。

首先请看官翻到第二行。

`#define int long long` 的意思是把程序里所有的 `int` 全部替换成 `long long` ，因为主函数不能返回 `long long` 类型（你已经把它替换成 `long long` 了），所以要把主函数的类型改成 `signed` 。

不过因为 `#define` 不会检查语法错误，所以还是建议使用 `typedef long long ll` ，由于本人太懒就不改了。

还有一个就是这段代码：

```cpp
cout.flags(ios::fixed);
cout.precision(1);
```

它其实跟你用这个是一样的：
```cpp
double xxx = 1145.14;
cout << fixed << setprecision(1) << xxx;
```

当然上面这段代码跟本题程序没有太大的关系，只是举个例子而已。

闲话：这段时间都不能在洛谷上用 Codeforces 的 Remotejudge 了，洛谷上又少了一道黄题，呜呜呜。

完结撒花。

---

