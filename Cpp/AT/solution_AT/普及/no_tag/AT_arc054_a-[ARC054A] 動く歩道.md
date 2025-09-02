# [ARC054A] 動く歩道

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc054/tasks/arc054_a

高梁空港には、周長 $ L $ の円形の動く歩道があり、その床面は $ 1 $ 秒間に距離 $ X $ 進む速度で時計回りに動いています。 動く歩道のある円周上の点の位置は、その中で最も北にある点から時計回りに測った距離 ( $ 0 $ 以上 $ L $ 未満) であらわされます。 動く歩道の外周の位置 $ D $ の点には出口があり、そこから動く歩道の外に出ることができるようになっています。 それ以外の外周と内周には手すりがあるため、高橋君は出口以外の場所から外に出ることはできません。

高橋君は動く歩道の床面に対して $ 1 $ 秒間に距離 $ Y $ 進む速度で時計回りまたは反時計回りに歩くことができ、動く歩道上の位置 $ S $ の点に乗っています。

高橋君が出口にたどり着くまでにかかる最小の時間を求めてください。

なお、出口の $ 1 $ 箇所しかない動く歩道にわざわざ乗るような物好きな人は高橋君以外にはいないので、動く歩道を逆走しても誰にも迷惑をかけることはありません。

## 说明/提示

### 制約

- $ 1\ ≦\ L,X,Y\ ≦\ 10^9,\ 0\ ≦\ S,D\ ≦\ L-1 $
- 入力はすべて整数である。

### Sample Explanation 1

時計回りに歩き続けると $ 0.8 $ 秒で出口にたどり着くことができます。

### Sample Explanation 2

反時計回りに歩き続けると $ 0.25 $ 秒で出口にたどり着くことができます。

## 样例 #1

### 输入

```
6 2 3 1 5```

### 输出

```
0.8000000000```

## 样例 #2

### 输入

```
6 2 10 1 5```

### 输出

```
0.2500000000```

## 样例 #3

### 输入

```
6 3 1 5 3```

### 输出

```
1.0000000000```

## 样例 #4

### 输入

```
10 7 7 6 0```

### 输出

```
0.2857142857```

# 题解

## 作者：dabenBbx (赞：3)

一道纯正的数学题，下面进行分析：

### 分析

首先要知道圆环与人都有速度，所以人可能会有两种运动方向：顺时针或逆时针。

逆时针：
前提是人的速度要大于圆环的速度。此时可以算出两者的速度差，这样就可以看作圆环是不动的。再计算逆时针方向的人与出口的距离，即可算得结果。

顺时针：
先计算出顺时针方向的两者距离，在将两者的速度加在一起作为总速度。再用距离和总速度进行计算。

### 分类讨论

要分类讨论 $s$ 在 $d$ 的前面，还是 $d$ 在 $s$ 的前面。

 >注意：最后结果要保留 $10$ 位小数，且要输出换行！！！

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,x,y,s,d,d1,d2;
double ans;
int main(){
    cin>>l>>x>>y>>s>>d;
    if(d>s){//d大于s时
        d1=d-s;//顺时针方向距离
        d2=s+l-d;//逆时针方向距离
        if(y>x)//可以逆时针方向跑
        ans=min((double)d1/(x+y),(double)d2/(y-x));
        else
        ans=(double)d1/(x+y);//只可以顺时针跑
    }
    else
    {//s大于d时
        d2=s-d;//顺时针方向距离
        d1=d+l-s;//逆时针方向距离
        if(y>x)//可以逆时针方向跑
        ans=min((double)d1/(x+y),(double)d2/(y-x));
        else
        ans=(double)d1/(x+y);//只可以顺时针跑
    }
    cout<<fixed<<setprecision(10)<<ans<<"\n";//保留10位小数和换行
    return 0;
}
```


---

## 作者：zsq9 (赞：2)

[AC 记录](https://www.luogu.com.cn/record/195015360)

## 思路

有两种方向，根据时间公式就可以算出时间，逆时针：人的速度要大于圆环的速度。算出两者的速度差，再计算逆时针方向的人与出口的距离，就行了。顺时针：先计算出顺时针方向的两者距离，在将两者的速度加在一起作为总速度。再用距离和总速度进行计算。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, x, y;//不能用long long 
long long s, d;
double ans;
int main() {
  cin >> a >> x >> y >> s >> d;
  double x1 = x + y;
  if (x >= y) {
    double x2 = x - y; 
    double x3 = (d + a - s) % a;
    ans = min(x3 / x1, x3 / x2)*1.0;
  } else {
    double x2 = y - x;   
    double x3 = (d + a - s) % a;
    double x4 = (s + a - d) % a;
    ans = min(x4 / x2, x3 / x1)*1.0;
  }
  printf("%.7lf", ans);//也可以用setprecision(10)
  return 0;
}
```

---

## 作者：opzc35 (赞：2)

## 题意

有一个环形跑道，长度为 $l$，以 $x$ 每秒顺时针移动。高桥君在这个跑道上运动，每秒走 $y$，从 $s$ 出发，$d$ 结束，问你他最少需要多久才能完成运动？

## 分析

纯纯的数学题，小学行程问题。

我们可以考虑两种情况，高桥君的速度比跑道快，高桥君的速度比跑道慢。

对于前者，如果高桥君如果往顺时针方向走，那么他每秒往顺时针方向走 $x+y$。如果高桥君往逆时针方向走，那么相当于往每秒逆时针方向走 $x-y$。

对于后者，如果高桥君往顺时针方向走，那么他每秒顺时针走 $x+y$，否则，还是相当于往顺时针方向每秒走 $y-x$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int l, x, y;
long long s, d;
double ans;
int main() {
  cin >> l >> x >> y >> s >> d;
  if (x >= y) {
    //步道更快
    int shun = x + y;
    int ni = x - y; //都是顺时针方向
    double dis = (d + l - s) % l;
    ans = min(dis / shun, dis / ni);
  } else {
    //人更快
    int shun = x + y; //顺时针方向
    int ni = y - x;   //逆时针方向
    double dis_shun = (d + l - s) % l;
    double dis_ni = (s + l - d) % l;
    ans = min(dis_ni / ni, dis_shun / shun);
  }
  printf("%.7lf", ans);
  return 0;
}
```

## TIPS

如何计算 s 到 d 的距离？顺时针方向只需要将 $d$ 加上 $l$ 后再减去 $s$ 就可以获得高桥君需要的距离。反之，$s + l - d$ 就可以获得逆时针方向高桥君需要行走的距离。

对于输出浮点数，可以使用代码

```cpp
 printf("%.7lf",ans);
```

即可输出 ans 的小数点 7 位。

---

## 作者：A_grasser (赞：2)

## 题意简化

求一个旋转圆形环道从一个位置到另一个位置的最小时间。

## 需要注意的地方

1. 日本题目记得输出加换行 

1. 在圆形环道上必须移动，不管你顺时针和逆时针走。

## 解法分析

该说什么呢？这道题是道水黄，全都是因为翻译问题导致通过率如此惨淡（本人亦为受害者）。

纯纯的模拟，我们首先看题。这个圆形环道很烦，那就化曲为直！就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/5zz2onhy.png)

是不是好理解多了？

根据题意也就能知道，到达指定点有两种走法：逆时针走和顺时针走。指定点与目标点也分两种：指定点坐标比目标点小和指定点坐标比目标点大。

时间公式是 $t=\dfrac{v}{s}$。

我们先考虑指定点坐标比目标点小的情况：

第一种就是顺时针走，那么速度就是步行速度加上步行道速度，距离就是 $D-S$。第二种是逆时针走，那么速度就是步行速度减上步行道速度，距离就是 $L-D+S$，也就是反着走，**前提是步行速度大于步行道速度，要不然不就被兜着走了**。

于是这部分的代码就是这个样子：

```cpp
if(S<=D){//目标点大于等于起始点 
    T=(D-S)/(X+Y);//普通顺时针走法 
    if(Y>X) T=min(T,(L-D+S)/(Y-X));//逆时针走法，前提是步行速度大于步行道速度 
}
```

---

再考虑指定点坐标比目标点大的情况：

第一种仍是顺时针走，那么速度扔是步行速度加上步行道速度，但距离是 $L-S+D$，毕竟就是先走回 $1$，接着走到 $L$，再走到 $D$。第二种是逆时针走，那么速度就是步行速度减上步行道速度，距离就是 $S-D$，毕竟是倒着走吗，**前提依旧是步行速度大于步行道速度，要不然不就被兜着走了**。

于是这部分的代码就是这个样子：

```cpp
else{//否则 
    T=(L-S+D)/(X+Y);//普通顺时针走法 
    if(Y>X) T=min(T,(S-D)/(Y-X));//逆时针走法，前提是步行速度大于步行道速度 
}
```


最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
double L,X,Y,S,D,T;//小数除法开double 
int main(){
    cin>>L>>X>>Y>>S>>D;
    if(S<=D){//目标点大于等于起始点
        T=(D-S)/(X+Y);//普通顺时针走法 
        if(Y>X) T=min(T,(L-D+S)/(Y-X));//逆时针走法，前提是步行速度大于步行道速度 
    }
    else{//否则 
        T=(L-S+D)/(X+Y);//普通顺时针走法 
        if(Y>X) T=min(T,(S-D)/(Y-X));//逆时针走法，前提是步行速度大于步行道速度 
    }
    cout<<setprecision(10)<<T<<endl;//保留到十位小数，记得换行 
    return 0;
}
```

---

## 作者：Wendy_Hello_qwq (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/AT_arc054_a)

[原文食用效果更佳。](https://www.luogu.com.cn/article/jgyuvhzs)

## 题意

给定 $L,X,Y,S,D$，人和人行道都会移动，让你求到达出口的最小时间。

## 分析

看起来很难，实则仔细观察可以发现，是个很简单的追及问题，分类讨论即可，最后记得输出格式，保留 $10$ 位小数。

## Code

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int L, X, Y, S, D;
double ans, cnt, res;
int main() {
	scanf ("%d%d%d%d%d", &L, &X, &Y, &S, &D);
	// 人行道更快 
	if (D > S) {
		// 顺时针方向 
		ans = D - S;
		// 逆时针方向 
		cnt = S + L - D;
		// 人快，逆行 
		if (Y > X) res = min (ans * 1.0 / (X + Y), cnt * 1.0 / (Y - X));
		// 否则，反之 
		else res = ans / (X + Y);
	// 人更快 
	} else {
		// 顺时针方向 
		ans = S - D;
		// 逆时针方向 
		cnt = D + L - S;
		// 人快，逆行 
		if (Y > X) res = min (cnt * 1.0 / (X + Y), ans * 1.0 / (Y - X));
		// 否则，反之 
		else res = cnt / (X + Y);
	}
	// 注意保留 10 位小数 
	printf ("%.10lf\n", res);
	return 0;
}
```

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：joker_opof_qaq (赞：1)

## 题意
~~暗暗吐槽一句翻译。~~

求一个圆形环道从一个位置到另一个位置的最小时间。

## 思路 && 解法

速度公式是 $v=\frac{s}{t}$，可以推导出时间公式 $t=\frac{s}{v}$。

我们在这道题目中要同时考虑速度和时间两个元素。顺时针人的速度为 $y+x$，逆时针为 $x-y$。而距离分别为 $l-d+s$ 和 $l-s+d$。

根据时间公式就可以算出时间来了。

当然逆时针也可能无法到达，即速度为负数，需要特判。

---

## 作者：hh20080501hh (赞：1)

# 题面
[题面戳这](https://www.luogu.com.cn/problem/AT_arc054_a)
# 分析
一道纯物理题，不过题面的翻译有些问题，终点其实是不随人行道动的（手推一下样例就能推出来），还有 $x$ 是人行道的速度，不过这一点翻译里面并没有给出来。

题意读懂了，题目就好做了。通过物理公式 $t=\frac{x}{v}$ 很容易得出我们需要计算的物理量。

不过需要注意的是，这个人行道是环形的，所以当起点和终点相对位置不一样的时候走的路程也会不一样，所以我们可以进行分类讨论。

关于速度的处理，我们可以讲人行道看作静止的，来计算人和人行道的相对速度，值得注意的是，如果你按逆时针放向跑，你的速度是有可能小于或者等于 $0$ 的，在这种情况下，肯定比沿着顺时针跑更慢（仔细思考可以发现其实这样路程是一样的，但是速度却相差了两倍的 $y$ 呀）。

# 代码
题目分析完了，代码也不难写出了
``` cpp
#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-7;

int l , x , y , s , d;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> l >> x >> y >> s >> d;
	
	double shun_v = (double)y+x , ni_v = (double)y-x;
	double shun_len , ni_len;
	if (s>d)
	{
		shun_len = (double)d-s+l , ni_len = (double)s-d;
	}
	else if (s<d)
	{
		shun_len = (double)d-s , ni_len = (double)s-d+l;
	}
	else 
	{
		cout << "0.000000000" << endl;
		return 0;
	}
	
	if (ni_v<=0)
	{
		cout << fixed << setprecision(10) <<shun_len/shun_v << endl;
	} 
	else 
	{
		cout << fixed << setprecision(10) << min(shun_len/shun_v , ni_len/ni_v) << endl;
	}
	return 0;
}

```
# 结语
这是一道红题难度的黄题，不过由于翻译的不准确加大了一丝题目的难度，需要认真思考才能不出问题。

---

## 作者：yangfengzhao (赞：0)

## 思路
纯纯小学奥数题：行程问题。\
考虑到：
1. 如果高桥如果往顺时针方向走：那么他每秒往顺时针方向走${x+y}$。如果高桥君往逆时针方向走：那么相当于往每秒逆时针方向走 ${x-y}$ 。
2. 如果高桥往顺时针方向走：那么他每秒顺时针走       ${x+y}$ 的距离；否则：还是相当于往顺时针方向每秒走 ${y-x}$ 的距离。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double Min(double a,double b) {
	return a>b?b:a;
}
int main() {
	int l,x,y,s,d;
	double ans=0;
	scanf("%d%d%d%d%d",&l,&x,&y,&s,&d);
	if(d>s) {
		double T_distance=d-s;//顺时针，同下 
		double F_distance=s+l-d;//逆时针，同下 
		if(y>x) {ans=Min(T_distance*1.0/(x+y),F_distance*1.0/(y-x));
		} else {
			ans=T_distance/(x+y);
		}
	} else {
		double T_distance=s-d;
		double F_distance=d+l-s;
		if(y>x) {
			ans=Min(F_distance*1.0/(x+y),T_distance*1.0/(y-x));
		} else {
			ans=F_distance/(x+y);
		}
	}
	printf("%10.lf\n",ans); //换行好习惯!
	return 0;
}
```
>**Tips**：岛国水题要换行！

---

## 作者：Like_Amao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc054_a)

**思路**

高桥君到达出口的方式无非就两种：相对于人行道顺时针走或者是逆时针走，所以我们只需要求出两种方法的时间，然后取最小值即可 **AC** 。

**注意事项**

首先，答案需要保留**十位小数**，不要弄错了；

其次，做 **AtCoder** 的题目时记得**输出换行**，不然有可能 **WA** 。

做完这些，我们就可以开始敲代码了。

**代码**


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int l,x,y,s,d;
	double ans=0;
	cin>>l>>x>>y>>s>>d;
	if(d>s)//人行道比人更快 
	{
		double Clockwise_distance=d-s;//顺时针方向的距离 
		double Counterclockwise_distance=s+l-d;//逆时针方向的距离
		if(y>x)//只要人比人行道快，就能逆行 
		{
			ans=min(Clockwise_distance*1.0/(x+y),Counterclockwise_distance*1.0/(y-x));//取顺时针和逆时针时间较少的为答案 
		}
		else//人比人行道慢，不能逆行 
		{
			ans=Clockwise_distance/(x+y);//顺时针的速度 
		}
	}
	else//人比步行道快 
	{
		double Clockwise_distance=s-d;//顺时针方向的距离 
		double Counterclockwise_distance=d+l-s;//逆时针方向的距离
		if(y>x)//只要人比人行道快，就能逆行 
		{
			ans=min(Counterclockwise_distance*1.0/(x+y),Clockwise_distance*1.0/(y-x));//取顺时针和逆时针时间较少的为答案 
		}
		else//人比人行道慢，不能逆行 
		{
			ans=Counterclockwise_distance/(x+y);//顺时针的速度 
		}
	}
	cout<<fixed<<setprecision(10)<<ans<<endl;//做岛国的题换行是个好习惯 
	return 0;//结束！ 
}
```

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc054_a)

## 题意

求一个圆形环道从一个位置到另一个位置的最小时间。

## 思路

速度公式：$v=\frac{s}{t}$。

首先分类讨论，圆形跑道有逆时针和顺时针两种情况。

先考虑指定点坐标比目标点小的情况，前提是步行速度大于步行道速度，不然就不进反退了。

第一种就是逆时针走，那么速度就是 $X-Y$，距离就是 $D−S$，时间为 $\frac{(D-S)}{(X-Y)}$。

第二种是顺时针走，那么速度就是 $X+Y$，距离就是 $L−D+S$，时间为 $\frac{(L-D+S)}{(X+Y)}$。

然后考虑指定点坐标比目标点大的情况，第一种就是逆时针走，那么速度就是 $X-Y$，距离就是 $D−S$，时间为 $\frac{(S-D)}{(X-Y)}$。

第二种是顺时针走，那么速度就是 $X+Y$，距离就是 $L−D+S$，时间为 $\frac{(L+D-S)}{(X+Y)}$。

题目这就做完了，最后，一定要换行。

---

## 作者：chl090410 (赞：0)

## The Solution to AT_arc054_a [ARC054A] 動く歩道

### Description

有一个长度为 $L$ 的环形人行道以 $X$ 格每秒的速度顺时针转动，人的速度为 $Y$ 格每秒且最初位于 $S$ 处。人行道的出口在 $D$ 处（出口不随人行道一起转动）。人可以顺时针走，也可以逆时针走。求人到出口所需的最短时间。

### Solution

我们可以先把人顺时针、逆时针走到出口的所需走的距离算出来，再分别计算人顺时针、逆时针走的速度，因为顺时针走时人与人行道方向一致，所以此时人的速度为 $(Y+X)$，而逆时针走时人与人行道方向相反，所以此时人的速度为 $(Y-X)$。

而最短时间的计算，我们分两种情况讨论。

- 若 $X\ge Y$，此时人逆时针走的速度 $\le0$，等于顺时针以 $(X-Y)$ 的速度前进，显然没有顺时针的 $(X+Y)$ 快。此时直接输出顺时针走所需时间即可。

- 若 $X\le Y$，此时可以用时间公式 $t=\dfrac{s}{v}$ 分别算出顺时针与逆时针走的所需时间，再输出较小的那个即可。

最后，别忘记要换行。

### Accode

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
double ps,kl;
int ans,cnt,n,k,l,p,s,ni,sh,vn,vs; 
signed main(){
	cin>>n>>k>>l>>p>>s;
	if(p==s){
		cout<<"0.0000000000"<<endl;
		return 0;
	}else if(p<s){
		sh=s-p;ni=p+n-s;
	}else{
		sh=s+n-p;ni=p-s;
	}
	vs=k+l;
	vn=l-k;
	if(vn<=0){
		ps=(sh*1.0)/(vs*1.0);
		printf("%.10lf\n",ps);
		return 0;
	}else{
		ps=(sh*1.0)/(vs*1.0);
		kl=(ni*1.0)/(vn*1.0);
		printf("%.10lf\n",min(ps,kl));
	}
	return 0;
}


---

## 作者：maple_trees_112 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc054_a)
## 题意

求一个圆形环道从一个位置到另一个位置的最小时间。

## 思路

既然是圆形环道，那就有逆时针和顺时针两种走法。

速度公式为：$v=\frac{s}{t}$。

若指定点坐标比目标点小：

- 顺时针方向：速度就是用步行速度加上步行道的速度，即 $x+y$ ，路程是 $d-s$ ，速度就是 $(d - s)/(x + y)$
- 逆时针方向：速度就是用步行速度减去上步行道的速度，（前提是速度大于步行道的速度）即 $x-y$ ，路程是 $l - d + s$ ，速度就是 $(l - d + s)/(x - y)$。

若指定点坐标比目标点大：

- 顺时针方向：速度就是用步行速度减去上步行道的速度，即 $x + y$ ，路程是 $l + d - s$ ，速度就是 $(l + d - s)/(x + y)$。

- 逆时针方向：速度就是用步行速度减去上步行道的速度，（前提是速度大于步行道的速度）即 $x-y$ ，路程是 $s - d$ ，速度就是 $(s - d)/(x - y)$。

做到这里这里，这道题就基本结束了，在最后说一句，**一定要换行**。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
double l,x,y,s,d,t;
int main(){
	cin >> l >> x >> y >> s >> d;
	if(s <= d)
	{
		double s1 = d - s,v1 = x + y;
		t=s1 / v1;
		if(y > x)
		{
			double s2 = l - d + s,v2 = y - x;
			t = min(t,s2 / v2);
		}
	}
	else
	{
		double s3 = l - s + d,v3 = x + y;
		t = s3 / v3;
		if(y > x)
		{
			double s4 = s - d,v4 = y - x;
			t = min(t,s4 / v4);
		}
	}
	printf("%.10lf\n",t);
}
~~~

---

