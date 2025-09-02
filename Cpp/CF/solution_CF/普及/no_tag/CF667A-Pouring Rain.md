# Pouring Rain

## 题目描述

有一个直径为 $d$ **厘米**的水桶。

原先桶里水深度为 $h$ **厘米**。

你在喝桶里的水，喝水的速度是 $v$ **毫升每秒**。

不喝水时桶内水面上升速度为 $e$ **厘米每秒**。

现在一边下雨，你一边喝桶里的水。

如果你喝的速度赶不上降水速度，输出"NO"，否则输出"YES"和你需要几秒喝光水。

## 样例 #1

### 输入

```
1 2 3 100
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
1 1 1 1
```

### 输出

```
YES
3.659792366325
```

# 题解

## 作者：我和鱼过不去 (赞：5)

### 众所周知
+ $1$ 毫升 = $1$ 立方厘米
+ 圆的面积 = $π * 半径^2$    
+ 圆柱的体积 = 圆的底面积 * 高  

先根据每秒钟喝水的速度 $v$ 毫升，求出每秒钟喝了几厘米的水。
然后再和每秒钟水面上升的速度 $e$ 毫升比较。  
~~这种一整行的输入对 Python 真不友好。~~

## $Code$
```python
s = input().split()
pi = 3.141592653589
for i in range(4):
    s[i] = float(s[i])
    
if s[2]/(pi*((s[0]/2)**2))<=s[3]:
    print('NO')
else:
    print('YES')
    print(s[1]/(s[2]/(pi*((s[0]/2)**2))-s[3]))
```


---

## 作者：Daidly (赞：0)

#### 前置知识：圆柱体体积公式

首先，我们是要判断喝的速度和增加的速度谁快，在这里，喝水的速度已经给出来了 $v$，要先求增加的速度 $V=\pi r^2e=\pi(\frac{d}{2})^2e$。

如果 $v<V$，也就是喝水的速度小于增加的速度，那么就喝不完，输出`NO`，并结束程序。


如果 $v>V$，也就是喝水的速度大于增加的速度，那么就喝得完，输出`YES`。

然后再算原来水的体积 $S=\pi r^2h=\pi(\frac{d}{2})^2h$。用 $\frac{S}{v-V}$ 就行啦（保留 $12$ 位小数）。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pi 3.14159265358979
int main(){
	double d,h,v,e;
	cin>>d>>h>>v>>e;
	double V=e*pi*(d/2)*(d/2);
	if(v<=V){
		cout<<"NO";
	}else{
		double S=pi*(d/2)*(d/2)*h;
		cout<<"YES"<<endl<<fixed<<setprecision(12)<<S/(v-V);
	}
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

- 首先算出桶的底面积：
$$di=\pi\,\cdot\,\frac{4}{d ^ 2}$$

- 接着就可以算出初始水的毫升量以及雨量：
$$hbegin(hb)=di\,\cdot\,h,\;vrain(vr)=di \,\cdot\,e$$

那么如果 $vrain$ 比 $v$ 大的话，就意味着雨量比喝水量要大，直接输出 $NO$ 即可。否则可以算出时间：

$$t=\frac{hbegin}{v-vrain}$$

当然直接判断 $t$ 的正负号也行。

```cpp
#include <bits/stdc++.h>
#define pi acos(-1) 
using namespace std;

double d, h, v, e, di, hb, vr;

int main() {
	scanf("%lf%lf%lf%lf", &d, &h, &v, &e);
	di = pi * d * d / 4;
	hb = h * di;
	vr = e * di;
	if (vr >= v) printf("NO");
	else printf("YES\n%.12lf", hb / (v - vr));
	return 0;
}
```

---

## 作者：CLCK (赞：0)

~~哇哇哇这题目单位。。。还好加粗了~~

注意，$v$ 是**毫升每秒**！！！

一开始先把 $v$ 转换单位（为计算方便转成**厘米每秒**）：

$$v1=v/s$$

若 $v1 < e$ 就输出 `NO`。

否则输出 `YES` 和秒数

$$h/(v1 - e)$$

即可（此处 $v1 - e$ 是一秒减少的**高度**，$h$ 为原始高度）。

代码如下，简单明了：

```cpp
#include <iostream>
#include <cmath> //acos函数的库
const double pi = acos(-1.0); //pi的标准求法
using namespace std;
double d, h, v, e;
int main() {
    cin >> d >> h >> v >> e;
    v = v / ((d / 2) * (d / 2) * pi); //单位转换，自己更新
    if (v <= e) {
        cout << "NO" << endl;
    } else {
        double ans = h / (v - e); //答案
        cout << "YES" << endl << ans << endl;
    }
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
一个水桶直径为 $d$ 厘米，初始时水面高度为 $h$ 厘米。你每秒钟喝 $v$ 毫升水，而由于下雨，水桶里面的水在不喝水的时候每秒会上升 $e$ 厘米。求你最少需要多少秒才能喝完水桶里面的水，或者你喝水的速度赶不上水桶里面的水增多的速度。

**数据范围：$1\leqslant d,h,v,e\leqslant 10^4$。**
## Solution
我们都知道，圆柱的底面积 $S=\pi r^2=\pi(\dfrac{d}{2})^2=\dfrac{\pi d^2}{4}$，那么原来水的体积 $V=Sh=\dfrac{\pi d^2h}{4}$。

由于这里说的是水桶里的水每秒上升的**高度**，所以我们需要转化成体积为 $\dfrac{\pi d^2e}{4}$。然后我们在拿这个和 $v$ 比较，如果 $v\leqslant \dfrac{\pi d^2e}{4}$，那么你喝水的速度赶不上水桶里面的水增多的速度，不能喝完里面的水，否则答案就是 $\dfrac{\dfrac{\pi d^2h}{4}}{v-\dfrac{\pi d^2e}{4}}=\dfrac{\dfrac{\pi d^2h}{4}}{\dfrac{4v-\pi d^2e}{4}}=\dfrac{\pi d^2h}{4v-\pi d^2e}=\dfrac{h}{\dfrac{4v}{\pi d^2}-e}$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

const double pi = acos(-1.0);
double d, h, v, e;

int main() {
	scanf("%lf%lf%lf%lf", &d, &h, &v, &e);
	if(v <= d * d / 4.0 * pi * e) return printf("NO"), 0;
	printf("YES\n%.12lf", h / (4.0 * v / (pi * d * d) - e));
	return 0;
}

```

---

## 作者：TLMPEX (赞：0)

思路：坑点：毫升转厘米。把毫升转换成厘米，就是每秒的毫升数除以圆通底面积，主要思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
const double pi=3.141592653589;
int main(){
	double d,h,v,e,s,l;
	cin>>d>>h>>v>>e;
	s=pi*(d/2)*(d/2);//算出底面积
	l=v/s;//算出每秒的厘米数
	if(l<=e)cout<<"NO";//如果喝水速度比下雨速度慢，则输出‘NO’
	else cout<<"YES"<<endl<<h/(l-e);//否则输出‘YES’并输出时间
}
```


---

## 作者：LRL65 (赞：0)

这就是一道小学数学题。

拿到题，先把毫升换成厘米，那么推出喝水的速度v2= $\dfrac{v}{\Pi\cdot (\dfrac{d}{2})^2}$ cm/s

然后我们再将v2与e比较，如果小于，那么就输出"NO"，如果大于，就输出"YES"和所需的时间$\dfrac{h}{v2-e}$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double d,h,v,e;
const double pi=3.1415926535898;
int main() {
	cin>>d>>h>>v>>e;
	v=v/(pi*(d/2)*(d/2));
	if(v<e)cout<<"NO"<<endl;
	else  {
		cout<<"YES"<<endl;
		printf("%.12lf",h/(v-e));//因为样例2保留了12位，所以保险起见，也保留12位
	}
	return 0;
}
```


---

## 作者：三点水一个各 (赞：0)

### 题意

桶直径 $d$ 厘米，原先桶里水深度为 $h$ 厘米，你喝水的速度是 $v$ 毫升每秒，不喝水时桶内水面上升速度为 $e$ 厘米每秒。

现在一边下雨，你一边喝桶里的水（雾）。

如果你喝的速度赶不上降水速度，输出"NO"，否则输出你需要几秒（一个实数）喝光水。

### 做法

因为喝水速度单位是恶心的**毫升每秒**，

所以可以将它化为厘米每秒，也就是 $e2=\dfrac{v}{s}$（$s$为底面积，单位平方厘米）。

如果它小于等于$e$，那就会喝不完，输出"NO"。

否则输出"YES"和深度除以速度 $\dfrac{h}{e2-e}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
double pi=3.1415926535897932384626433832795028841971693993751058209749445923078164,s,e2,ans;
int d,h,v,e;
int main()
{
    scanf("%d%d%d%d",&d,&h,&v,&e);
    s=pi*(d/2.0)*(d/2.0);  //底面积
    e2=v/s;  //喝水速度
    if(e>=e2) printf("NO");
    else printf("YES\n%.12lf",h/(e2-e));
    return 0;
}

---

## 作者：zoobidubi (赞：0)

这题算是一题标准的小学奥数了吧（逃

就用小学奥数的思路来讲讲这题

首先我们要定义double变量(这点很重要，不然乘出来都是整数且是错误的答案会很难调）

读入这几个数，先特判，算会喝掉的体积，就是底面积乘上单位时间下雨会上升的高度e，就是单位时间雨会增加的体积

如果这个喝的速度（毫升）比下雨的速度小，那么永远都喝不完，就直接输出NO（注意是大写的）

否则就输出上升速度/高度，再乘上初始水位h，除以会上升的体积，就是要喝完水用的体积



Code

```cpp
#include<bits/stdc++.h>
#define pai 3.141592653589 
using namespace std;
double d, h, v, e, r, will;
int main()
{
    cin >> d >> h >> v >> e;
    r = d / 2;
    will = r * r * pai * e; 
    if (will > v)//这里其实严格来说要挂等号的
    //但是我一开始忘了，居然也过了，所以加或不加都没多大影响
    {
    	cout << " NO";
    	return 0;
    }
    else 
    {
    	cout << "YES" << endl;
        cout << fixed << setprecision(12) << (will / e) * h / (v - will); 	
        //注意，因为第二组样例输出了12位小数，为了保险起见
        //我还是输出12位小数，这个是用cout版本来修改输出的小数位数的
        //虽然单词长会比较难记，但是多一种方法也是好的
    }
    return 0;
}

```
`


---

## 作者：StudyingFather (赞：0)

我们可以计算出每秒新增水的体积 $ v_n = \pi r^2e $ ，如果新增水的体积大于喝掉的水的体积 $ v $ ，就可以输出"NO"。

否则，我们用初始时刻水杯中水的总体积除以每秒水杯减少的体积（即 $ v-v_n $），就是本题的答案。

```cpp
#include <stdio.h>
#define PI 3.1415926535897
int main()
{
 int d,h,v,e;
 scanf("%d%d%d%d",&d,&h,&v,&e);
 double s=(d*1.0/2)*(d*1.0/2)*PI,v1=s*e;
 if(v1>=v)puts("NO");
 else
 {
  puts("YES");
  printf("%.8lf",s*h/(v-v1));
 }
 return 0;
} 
```

---

## 作者：Ba_creeper (赞：0)

## 题解 CF667A 【Pouring Rain】
#### 题目分析：
根据题意模拟即可。

特判：如果这个喝的速度比下雨的速度小，就直接输出NO。

注意单位为毫升每秒，我们可以计算出每秒下雨的体积为 $d^2/4\pi$，计算出来之后和下雨速度相比较即可。

如果符合题意，输出YES，回车之后输出深度除以速度的值 $\dfrac{h}{\dfrac{v}{s}-v}$。

#### 代码
```cpp
#include<iostream>
#include<cstdio>
const double PI=3.1415926535;
int main()
{
	int d,h,v,e;
	scanf("%d%d%d%d",&d,&h,&v,&e);
	double s=(d*1.0/2)*(d*1.0/2)*PI;
	double v1=s*e;
	if(v1>=v)
		puts("NO");
	else
	{
		puts("YES");
		printf("%.12lf",s*h/(v-v1));
	}
	return 0;
}
```

---

