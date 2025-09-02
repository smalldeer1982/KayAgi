# Guilty — to the kitchen!

## 题目描述

今天对Volodya来说是十分不幸的一天。他的代数考试挂掉了，并且不得不在厨房里干活，即做罗宋汤（一种传统的俄罗斯汤）。通过这样也能提高他的代数水平。

根据罗宋汤的配方,罗宋汤由$n$部分组成，并且它们必须按比例（$a_1:a_2:\ldots:a_n$）混合（因此，对于一个非负的$x$，它们为$a_1*x,a_2*x,\ldots,a_n*x$升），在厨房里 Volodya发现每种配料他相应的有$b_1,b_2,\ldots,b_n$升供他使用。为了纠正他在代数上的错误，他决定用一个容量为$V$升的锅尽可能的多做汤（这意味着这它能够做$0$到$V$升的汤）。Volodya最多能做多少汤？

## 样例 #1

### 输入

```
1 100
1
40
```

### 输出

```
40.0
```

## 样例 #2

### 输入

```
2 100
1 1
25 30
```

### 输出

```
50.0
```

## 样例 #3

### 输入

```
2 100
1 1
60 60
```

### 输出

```
100.0
```

# 题解

## 作者：Dry_ice (赞：9)

> 话说罗宋汤还真的不错呢。

这题数据范围是真的小，以现在的计算机速度其实 $n$ 可以开到 $2$ 个亿左右。

这题的主要思路就是**贪心**。

## 贪心介绍
**贪心**算法就是就当前情况考虑选择局部最优从而使得全局最优的算法，~~也可以用于DP骗分~~。使用**贪心**必须满足**各部分选择不分阶段**的条件，否则贪心会出问题。显然这里每种配料的选择是同一阶段，所以判定可以使用贪心算法。

## 贪心方法
由于要按照比例配制罗宋汤，所以只要让比例的每一份（单位 $1$）最大，就可以使得最终的体积最大。假设 $x=min\{B_j\div Aj\}(1\leq j \leq n)$，由于每种配料总量有限，所以每一种配料按照比例只能选择 $Ai\cdot x$ 的体积。那么最大总体积也就推倒出来了：
$$vmax=\sum_{i=1}^n A_i\cdot x$$

值得注意的是，锅的体积也是有限的，大小为 $V$，故：
$$ans=min(vmax, V)$$

最后记得要开浮点类型。

## CODE
```cpp
#include <stdio.h>
int n, V; double a[25], b[25];
inline double mn(double p, double q) {return p < q ? p : q;} //求较小值
int main(void) {
    scanf("%d %d", &n, &V);
    for (int i = 1; i <= n; ++i) scanf("%lf", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%lf", &b[i]);
    double x = b[1] / a[1], ans = 0;
    for (int i = 2; i <= n; ++i) x = mn(b[i] / a[i], x);
    for (int i = 1; i <= n; ++i) ans += a[i] * x;
    printf("%.4lf\n", mn(ans, V));
    return 0;
}
```

## The end. Thanks.
（记得点赞哦

---

## 作者：_HiKou_ (赞：3)

[原题](https://www.luogu.com.cn/problem/CF42A)

首先，如果要按比例混合，那么就要在材料够用的前提下找到最大的 x， 即 $x = b_i \div a_i$。这样可以满足比例而又不会缺材料。然后，取这其中最小的 x 来满足所有材料的需求。简单来说，就是**最大值中的最小值**。

因为在第一步找到了每种材料可以满足的最大的 x，如果取这些 x 里的最小值，一定可以满足 $x_i \geqslant x_{min}$。所以 $b_i \geqslant x_{min} \times a_i$。

最后，把每一种材料需要的总量（即 $a_i\times x_{min}$）加起来，即 $a_0 \times x_{min} + a_1 \times x_{min} + ... +a_n \times x_{min}$，即为 $(a_0+a_1+...+a_n) \times x_{min}$。最后如果结果大于锅的容量 V 就输出 V ，否则就输出结果。

结果与正确答案相差不超过 $10^{-4}$，所以保留 4 位小数即可。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v,i;
double a[114],b[514],x=1919810;//恶臭数组
double aoa=0;//表示 a 数组中数据的总和
int main(){
	cin>>n>>v;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
		aoa+=a[i];//累加
	}
	for(i=0;i<n;i++)
	{
		cin>>b[i];
		x=min(x,b[i]/a[i]);//寻找最小 x
	}
	if(aoa*x>=v)cout<<v;
	else cout<<fixed<<setprecision(4)<<aoa*x;
	return 0;
}
```

---

## 作者：GordonLu (赞：2)

# CF42A Guilty 题解
## · 题目 ·
这道题是可以简化以下的，意思是给你 $n$ , $v$ , $a_i$ , $b_i$ 让你求当 $ a_i \times x \le b_i $ 时 ，$\max( v , \sum\limits_{i=1}^n a_i \times x ) $ 的最大值
## · 分析 ·
我们先看一眼 $\max( v ,\sum\limits_{i=1}^n a_i \times x ) $ 因为 $v$ 是定值，所以我们只需求出 $ \Sigma_i^n a_i \times x $ 的最大值，而

 $ \sum\limits_{i=1}^n a_i \times x = x \times \sum\limits_{i=1}^n a_i $
 
我们又发现 $ \sum\limits_{i=1}^n a_i $ 是定值，所以我们让 $ x $ 尽可能大，又因为

$ a_i \times x \le b_i \Longleftrightarrow x\le \tfrac{b_i}{a_i} $

发现 $ \tfrac{b_i}{a_i} $ 也是定值，所以我们有了大致思路。

## · 代码 · 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,a[100],b[100];double v;
int main(){
    scanf("%d%lf",&n,&v);
    for(int i=1;i<=n;i++)scanf("%d",a+i),sum+=a[i];
    for(int i=1;i<=n;i++)scanf("%d",b+i);
    for(int i=1;i<=n;i++)v=min(v,double(b[i])/a[i]*sum);
    printf("%lf",v);
    return 0;
}


```


---

## 作者：monstersqwq (赞：2)

思路：

对于每个 $i$，$x_i$ 的最大值即为 $\dfrac{b_i}{a_i}$，$x_{max}=\min(x_1,x_2\cdots x_n)$。（因为要满足所有的配料，所以是最小值）

用 sum 记录 $\sum_{i=1}^na_i$（即当 $x=1$ 时各个配料之和），这样可以直接算出答案 $ans=x_{max} \times sum$，省去了一步求和。

当然，在最后，如果 $ans>v$，直接输出 $v$ 即可，可以简化为 $ans=\min(x_{max} \times sum,v)$，输出 $ans$ 即可。

注：因为涉及到除法，最好都使用 double 类型。

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>//可爱的头文件 
using namespace std;
double n,v,a[25],b[25],sum,maxx=1e9;//mixx的初值要定的大一些（其实定义为0也可以，个人习惯） 
int main()
{
	cin>>n>>v;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
		maxx=min(maxx,b[i]/a[i]); 
	printf("%.6lf\n",min(maxx*sum,v));
    return 0;
}
```


---

## 作者：KEBrantily (赞：1)

## 题意

给定两个序列 a 和 b。

序列 a 中的各个数之间的比例可以得出一个 x 。

当 b 中比例满足 a 中比例，即 $b_1$:$b_2$:$b_3$…… $=$ $a_1$:$a_2$:$a_3$……时，可以得出一个数 $x * \dfrac{b}{a} $。

( 不懂的请好好分析，这直接给出了解题的关键一步）


------------
## 分析
~~因为这是做汤~~**按照一定比例才能得出一个与 x 成倍数关系的数**。

所以我们可以知道，如果有**一个数与其他的数不成比例且小于其他数时，整个数列得出的数都会被那个数影响**。

所以我们先找出所有的 b/a 里面最小的那个，因为他决定了结果的大小。

然后让整个数列都以这个最小比例做汤求 x 。

另外，他给定了锅的大小也就是 x 的上限 v ，所以得出的那个数如果超过 v ，那就要把它赋值成 v 就好了。

注意：他要求你的数要与他的答案的差值大小不超过十的负四次方，也就是要你**至少精确到小数点后四位**。

------------
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define maxn 300050
#define maxm 1010

using namespace std;

int n;
double v,a[maxn],b[maxn],x[maxn];

int main(){
	cin>>n>>v;
	for(int i=1;i<=n;i++) cin>>a[i]; 
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		x[i]=b[i]/a[i];
	} 
	sort(x+1,x+n+1);我开了一整个数组来求一个最小值有点浪费，其实可以通过边求边比的方法取；
	double ans=0.0;
	for(int i=1;i<=n;i++){
		ans+=x[1]*a[i];
	}
	ans=min(ans,v);
	printf("%.4lf",ans);
	return 0;
}
```


------------

制作不易，不喜勿喷。

---

## 作者：Tune_ (赞：1)

看了下这题的其他题解，发现是暴力循环，~~竟然不会TLE~~

所以本蒟蒻来发个省时间的数学解~

1. 找到最少的一份量x（b[i]/a[i])
2. 算出以x为一份量时所做的汤的量
3. 如果大于v，就输出v

怎么样，是不是很简单？

以下是完整代码：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	double n,v,a[25],ans=0,x=9999999;
	double b[25];
	cin>>n>>v;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		if(b[i]/a[i]<x)//求出最小的x
			x=b[i]/a[i];
	}
	for(int i=1;i<=n;i++)
	{
		ans+=a[i]*x;//加起来~
		if(ans>v)//判断装不装得下
		{
			printf("%.6lf",v);
			return 0;
		}
	}
	printf("%.6lf",ans);//完工！
	return 0;
}

```


---

## 作者：Khassar (赞：1)

题意请看我的翻译，我觉得跟做题有关的的部分翻译的还可以~~（无关的地方翻译的是真不通，关键是后置要放前面不知道该放哪，以及有的单词找不到一个符合语境的意思）~~


算了我还是抽一下题面吧（作为一道A题还真恶心）


就是要按比例做汤，每个材料有个量，锅大小有一个上限，多做汤。


显然我们要是能定下一个材料的用量就能在O(n)的时间内判断（是否有一个材料用量超过了其总量或总量超过了锅的容量）并求解。


所以我们枚举第一个材料的用量，不过用量不一定是整数啊，那怎么办呢？


我们可以枚举小数，比如我枚举3位小数，我可以


```C++
for(int i=1;i<=b[1]*1000;++i)
```
我们在把i/1000这就是现在枚举的数了，具体这题需要枚举精度到几位小数呢？—6位小数！反正我是一位一位加上去的，可能是我写的丑……


```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<ctime>

#define ll long long
#define R register
#define IL inline
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define MP make_pair
#define PA pair<int,int>
#define MES(a,b) memset((a),(b),sizeof((a)))
#define MEC(a,b) memcpy((a),(b),sizeof((b)))
#define D double

using namespace std;

const int N=25;

int n,v;
D ans;
struct node {
    int a,b;
}c[N];

IL int read() {
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
IL void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

IL bool cmp1(node x,node y) {return x.a<y.a;}

signed main()
{
    n=read();v=read();
    Rf(i,1,n) c[i].a=read();
    Rf(i,1,n) c[i].b=read();
    sort(c+1,c+1+n,cmp1);
    Rf(i,1,c[1].b*1000000) {
        R D t=1.0*i/1000000;
        R D sum=t;
        Rf(j,2,n) {
            R D x=1.0*t/c[1].a*c[j].a;//按比例换算
            if(x>c[j].b) {//超过了这个材料的上限
                sum=-1;
                break;
            }
            sum+=x;
        }
        if(sum>v) sum=-1;//超过了锅的容量
        ans=max(ans,sum);
    } 
    printf("%.7lf",ans);


    return 0;
}

```

---

## 作者：xgwpp6710 (赞：0)

~~该死的，我看这题翻译还以为只要输出一位小数，害得我 WA 了一次。。。~~

其实这题还是很简单的。

我们可以先抛开桶的容量不看，先看配料至多做出多少罗宋汤。

那么显然就是要求出最大的 $x$。

那么显然 $x_{\max}≤\min\{ \frac{b_i}{a_i} \}$。

因此可以得出，配料最多做出 $x_{\max}\cdot\sum\limits_{i=1}^n a_i$ 升罗宋汤。

最终把这个值跟桶的容量作比较取较小值即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double v,a[100005],b[100005],s,minx=998244353.0;
int main()
{
	cin>>n>>v;
	for(int i=1;i<=n;i++) cin>>a[i],s+=a[i];
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		minx=min(minx,b[i]/a[i]);//求出 x 的最大值
	}
	cout<<min(minx*s,v);//比较配料和桶，应该取哪个作为最终限制
	return 0;
}
```

---

## 作者：qfpjm (赞：0)

# 题目大意

- 在比例符合要求的情况下，Volodya 最多能做多少汤？且锅只有 $V$ 的大小。

# 题解

- 首先我们要知道这道题里面 $x$ 是什么，其实是配料比例里每份所能取得的最大值。为什么是一个固定的数，因为这样才能使做的汤最多且配料符合比例。

- 那么，我们只需求出 $x$，就可以得到答案。

- 如何求 $x$？对于一对 $a,b$ 他们的 $x$ 便是 $a \div b$（这小学就学过了吧，我就不多讲为什么了）。那么，延伸过来，有多组 $a_i,b_i$。这样我们需要照顾到最小的那对 $a_i,b_i$ 的那个 $x$，所以最终的 $x$ 就是最小 $a_i \div b_i$。

- 求出 $x$ 后，最多能做的汤即为 $ans = \sum\limits_{i=1}^na_i \times x$。

- 但要注意，结果是 $\min(ans,V)$，保留四位小数。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

double n, V, a[1005], b[1005], x, ans;

int main()
{
	cin >> n >> V;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> b[i];
	}
	x = b[1] / a[1];
	for (int i = 2 ; i <= n ; i ++)
	{
		x = min(x, b[i] / a[i]);
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		ans += a[i] * x;
	}
	cout << fixed << setprecision(4) << min(V, ans);
	return 0;
}

```


---

## 作者：Terraria (赞：0)

前言：这道题我调了十几分钟，就是为了用二分求出最小的 $x$（见题意），结果突然发现是自己想多了。

也就是说，我们要求出一个能满足题意条件的最小的 $x$ 后与 $a_i$ 相乘累加的结果。问题是要怎么求这个 $x$。

由于每一个东西都有一定的限量，即 $b_i$，所以我们考虑从 $b_i$ 下手。对于每一个所占比例和限量，肯定是要求最小的 $\dfrac{b_i}{a_i}$，这个值就是 $x$。

于是代码就出来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v;
double x=0x7fffff,ans=0;
int a[100];
int b[100];
double Min(double a,double b){return a>b?b:a;}
int main(){
	cin>>n>>v;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) x=Min(1.0*b[i]/a[i],x);
	for(int i=1;i<=n;i++) ans+=a[i]*x;
	ans=Min(v*1.0,ans);
	cout<<ans;
}
```
注意最后面有一个```ans=Min(v*1.0,ans);```，如果不加上这一句的话连第三个样例都过不了。

---

## 作者：yzh_Error404 (赞：0)

### 题意分析

汤有 $n$ 种配料，组合形式为 $a_1:a_2:……:a_n$ 。

每种配料有 $b_i$ 升，锅容积为 $V$ 升。

知道了这些，可以想出一个简单的方法：

遍历每一个 $a_i$ 和 $b_i$ ，易得第 $i$ 种配料最多可以满足 $\dfrac{a_i}{b_i}$ 升汤。

遍历记录每一个 $\dfrac{a_i}{b_i}$ 并存入优先队列中，取队首最大值，然后让这个最大值乘 $a$ 数组总和的积与容积 $V$ 比较，输出较小的一个即可。

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<double,vector<double>,greater<double> >q;//优先队列
int n,v;
double a[25],b[25],al;//al表示a数组总和
inline double minn(double a,double b)//因为min函数只适用于int类型的数，所以重新定义一个minn函数
{
	if(a>b)return b;
	else return a;
}
int main()
{
	scanf("%d%d",&n,&v);
	for(register int i=1;i<=n;i++)
	{
		scanf("%lf",&a[i]);
		al+=a[i];//累加总和
	}
	for(register int i=1;i<=n;i++)
	{
		scanf("%lf",&b[i]);
		q.push(b[i]/a[i]);//在遍历中存入b[i]/a[i]的值
	}
	printf("%.6lf",minn(al*q.top(),v));//比较并输出
	return 0;
}

```


---

