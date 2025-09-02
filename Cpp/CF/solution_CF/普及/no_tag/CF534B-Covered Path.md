# Covered Path

## 题目描述

小 $P$ 用车载计算机测量出，汽车在某段路径的起点速度为 $v_1$ 米/秒，终点速度为 $v_2$ 米/秒，我们知道这段路需要 $t$ 秒通过。假设每秒内的速度恒定，每秒之间速度的差值不超过 $d$ 。求路径段的最大可能长度，单位为米。

## 样例 #1

### 输入

```
5 6
4 2
```

### 输出

```
26```

## 样例 #2

### 输入

```
10 10
10 0
```

### 输出

```
100```

# 题解

## 作者：XL4453 (赞：14)

提供一种复杂度为 $O(1)$ 的直接计算法。

---
### 解题思路：

首先发现，将 $v_1$ 和 $v_2$ 交换并无影响，所以为了方便，直接将 $v_1$ 强制定为相对较小的那一个。

考虑贪心，在能将速度最后降到要求的前提下尽量增加速度，到最后在往下降。

数据范围很小，直接模拟就行了。

但这种只给了几个数的题不优化一下有点过意不去。

----
前置知识：速度图像中面积表示位移。

若将问题放在实数范围下，也就是没有秒间换速度的限制，问题就可以直接转换为物理中运动中的速度问题，直接用面积法求解，复杂度是 $O(1)$ 的。

回到本题，发现其实更改的就是将整个问题的范围变为高斯函数下的直线交点与面积问题，推一推式子依然可以 $O(1)$ 求出。

---
### 推式子：

以时间为 $x$ 轴，速度为 $y$ 轴建立坐标系。

写出两条直线。

$\begin{cases}y=dx+v_1\\y=-dx+v_2+dt\end{cases}$

解得

$\begin{cases}x=\dfrac{v_2-v_1+dt}{2d}\\y=\dfrac{v_1+v_2+dt}{2}\end{cases}$

这里其实只需要 $x$，而这个是在实数范围下的，转换一下就是：$x=\left\lfloor\dfrac{v_2-v_1+dt}{2d}\right\rfloor$。

这个点及其左边都是开满加速度，右边也是，只有这个点到下一个需要考虑到回不来的情况。

分开来算，左边和右边都是等差数列求和：左边面积为 $v_1x+\dfrac{dx(x-1)}{2}$，右边：$v_2(t-x-1)+\dfrac{d(t-x-1)(t-x-2)}{2}$，比较简单，不多赘述。

然后考虑最中间一段，肯定是两边较小的一个加满加速度，然后这样一定能到达另一个且总和最大，注意得出这个结论要两方面考虑。这一步的计算需要算出左右两边的速度，然后取最小值，加上 $d$，还是比较简单的。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int v1,v2,t,d,x,ans,kx,ky;
int main(){
	scanf("%d%d%d%d",&v1,&v2,&t,&d);
	if(v1>v2)swap(v1,v2);//v1<v2
	if(d==0){
		printf("%d\n",v1*t);
		return 0;
	}
	x=(v2-v1+d*t)/(2*d);
	ans+=x*v1+d*(x-1)*x/2;
	ans+=(t-x-1)*v2+d*(t-x-1)*(t-x-2)/2;
	kx=v1+d*(x-1);
	ky=v2+d*(t-x-2);
	if(kx>ky)swap(kx,ky);//kx<ky
	ans+=kx+d;
	printf("%d",ans);
	return 0;
} 
```


---

## 作者：BrokenStar (赞：3)

## 思路

我们知道求路程的公式 $s=vt$

题目中给出的时间是固定的，也就是说 $t$ 是固定的，想要答案路程 $s$ 尽量大，就要使速度 $v$ 尽量大。

题目中仅给出了起始速度和终点速度，考虑贪心，先每秒加速 $d$ 至 $v2+d$ ，这样每秒速度就能达到可以达到的最大值，再一次减速到 $v2$ ，达到最终速度。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int v1,v2,t,d,ans;
int main(){
    cin>>v1>>v2>>t>>d;
    ans=v1+v2;
    t-=2;
    if(v1>v2){
        swap(v1,v2);
    }
    while(v2-v1>d){
        v1+=d;
        ans+=v1;
        t--;
    }
    if(!(t&1)){
        while(t>0){
            v1+=d;
            v2+=d;
            ans+=v1+v2;
            t-=2;
        }
    }
    else{
        v1+=d;
        ans+=v1;
        t--;
        while(t>0){
            v1+=d;
            v2+=d;
            ans+=v1+v2;
            t-=2;
        }
    }
    cout<<ans<<endl;
	return 0;
}


```


---

## 作者：A_small_WA (赞：2)

题意十分明确，就是一道简单的贪心题，那么我们先来思考贪心策略。

由于 $v_1$ 和 $v_2$ 的顺序不影响最终结果，所以我们不妨令这两个数中较小的为 $v_1$,较大的为 $v_2$，方便之后做题。另外，定义一个变量 $vnow$ 为当前速度，初始值为 $v_1$。

因为要使总路程尽可能地大，所以我们希望每一秒都使 $vnow$ 加上一个 $d$ 。但是题目规定到达终点时速度必须为 $v_2$，所以中途必需要减速。同样地，我们为了使总路程最大，减速的时间应当是越往后越好。

题意明确了我们每一秒最多可以将 $vnow$ 减速 $d$，可以推导出在第 $i$ 秒时在剩余时间内最多能将速度减到 
$vnow-\left(t-i\right)\times d$。根据这个算式，每秒加速前比较 $vnow-\left(t-i\right)\times d$ 和 $vnow$ 的大小即可决定是否继续加速。

但是，根据这个思路写出代码后运行，会发现样例一输出了 $28$。输出中间变量，得到 $1\sim4$ 秒之内 $vnow$ 的值分别为：`5 7 9 7`

之后我就终于知道问题出在哪里了。

有可能出现在第 $i$ 秒时小车减速还来得及，于是加速了，但是到了第 $i+1$ 秒小车再减速却来不及了的情况。因此每一秒我们要比较的应该是 $vnow-\left(t-i\right)\times d$ 和 $vnow-d$ 的大小。特别地，如果 $vnow-d>vnow-\left(t-i\right)\times d$ 但是 $vnow<vnow-\left(t-i\right)\times d$，那就应该让 $vnow$ 加速到 $v_2+\left(t-i\right)\times d$。

我讲的思路可能有点繁琐，但也是出于分享自己遇到的困难的初衷，有什么问题欢迎私信。

最后是代码，我觉得有了上述分析大家应该都能写出来了吧。
```cpp
#include <bits/stdc++.h>
using namespace std;
int v1,v2,t,d;
long long ans,vnow;
int main(){
	cin>>v1>>v2>>t>>d;
	if(v1>v2) swap(v1,v2);
	ans+=v1,vnow=v1;
	for(int i=2;i<=t;i++){
		if(vnow-(t-i+1)*d>=v2) vnow-=d,ans+=vnow;
		else{
			vnow+=d;
			if(vnow-(t-i)*d>=v2){
				vnow=v2+(t-i)*d;
			}
			ans+=vnow;
		}
	}
	cout<<ans;
	return 0;
}
```
这是蒟蒻的第5篇题解，支持一下孩子吧！

---

## 作者：开始新的记忆 (赞：1)

题目大意：给四个数v1，v2，t，d，表示汽车初始速度为v1，终止速度为v2，开了t秒，每秒可以使原速度加减1-d中的一个数。求汽车最长行驶距离。

比较简单的贪心，先把v1和v2之间的差变为1-d中（一次可追平），然后贪心，每次都取d即可


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<map>
using namespace std;
int main()
{   int v1,v2,t,d,ans;
    cin>>v1>>v2>>t>>d;
    ans=v1+v2;
    t-=2;
    if(v1>v2) swap(v1,v2);
    while(v2-v1>d)
    {
        v1+=d;
        ans+=v1;
        t--;
    }
    if(t%2==0)
    {
        while(t>0)
        {
            v1+=d;
            v2+=d;
            ans+=v1+v2;
            t-=2;
        }
    }
    if(t%2==1)
    {
        v1+=d;
        ans+=v1;
        t--;
        while(t>0)
        {
            v1+=d;
            v2+=d;
            ans+=v1+v2;
            t-=2;
        }
    }
    cout<<ans;
	return 0;
}

```


---

## 作者：Kobe_BeanBryant (赞：0)

## 题意：
给定四个数，分别用来表示汽车的初始速度为 $ n $，停止速度为 $ m $，行驶了 $ x $ 秒，每秒可以让原来的速度加或者去减 $ 1 $ 到 $ y $ 中的一个数。

求汽车最长行驶距离。

## 思路:
路程的公式 $ s=vt $。

1. 时间是固定的。
2. 使速度尽量大。
3. 每秒加速 $ d $ 至 $ v2+d $。
4. 每再一次减速到 $ v2 $。 
5. 达到最终速度。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,y;
long long ans=0;
int main(){
    scanf("%lld%lld%lld%lld",&n,&m,&x,&y);
    ans=n+m,x-=2;
    if(n>m)
		swap(n,m);
    while(m-n>y)
		n+=y,ans+=n,x--;
    if(x%2)
        while(x>0)
            n+=y,m+=y,ans+=n+m,x-=2;
    if(!x%2)
        n+=y,ans+=n,x--;
        while(x>0)
            n+=y,m+=y,ans+=n+m,x-=2;
    printf("%lld\n",ans);
	return 0;
}

```

---

