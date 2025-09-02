# Mixing Water

## 题目描述

有两种无限的水源：

- 温度为 $h$ 的热水；
- 温度为 $c$ 的冷水（ $c \lt h$ ）。

您要执行以下交替移动的程序：

1. 取**一**杯**热**水，倒入一个无限深的桶中；
2. 取**一**杯**冷**水，倒入无限深的木桶中；
3. 取**一**杯**热**水 $\dots$ 
4. 依此类推 $\dots$

**注意，一定要从一杯热水开始**。

木桶最初是空的。你必须**至少倒一杯**到桶里。木桶中的水温是倒入的杯子温度的平均值。

您希望水温尽可能接近 $t$ 。因此，如果木桶中的温度是 $t_b$ ，那么 $t_b$ 和 $t$ （ $|t_b - t|$ ）的**绝对差**应该尽可能小。

你应该往桶里倒多少杯水，才能使桶里的温度尽可能接近 $t$ ？如果有多个绝对差最小的答案，则打印其中最小的答案。

1. 每个“一杯”的大小相同。
1. 桶一开始时为空。
1. 至少要倒一次水。
1. 第一杯永远是热水。

##### Translated By [Lj_zjl0](https://www.luogu.com.cn/user/311615) & Deepl

## 样例 #1

### 输入

```
3
30 10 20
41 15 30
18 13 18```

### 输出

```
2
7
1```

# 题解

## 作者：fighter (赞：7)

先考虑两种特殊的情况：

1. $t=h$，一步到位。
2. $t\leq \frac{h+c}{2}$，那么肯定是平均温度最接近，答案为2。

接着考虑$t>\frac{h+c}{2}$时的情况。假设我们已经加入了$x$轮热水和冷水，那么此时温度为$\frac{h+c}{2}$，共有$2x$杯水。

所以我们再倒入热水的时候，温度就变为$\frac{(x+1)h+xc}{2x+1}$，所以我们列出方程：$\frac{(x+1)h+xc}{2x+1}=t$。

解得$x=\frac{t-h}{h+c-2t}$，由于精度误差，我们再比较一下$x$和$x+1$即可。

注意千万不要用浮点运算比较，否则精度无法保证，需要把除法转成乘法比较。

```cpp
#include <bits/stdc++.h>
#define MAX 1005
#define ll long long
using namespace std;

template<typename T>
void read(T &n){
    n = 0;
    T f = 1;
    char c = getchar();
    while(!isdigit(c) && c != '-') c = getchar();
    if(c == '-') f = -1, c = getchar();
    while(isdigit(c)) n = n*10+c-'0', c = getchar();
    n *= f;
}
template<typename T>
void write(T n){
    if(n < 0) putchar('-'), n = -n;
    if(n > 9) write(n/10);
    putchar(n%10+'0');
}

ll a, b, c;

long double calc(int x){
    return 1.0*((x+1)*a+x*b)/(2*x+1);
}

int main()
{
    int T;
    cin >> T;
    while(T--){
        scanf("%lld%lld%lld", &a, &b, &c);

        if(c == a) puts("1");
        else if(c*2 <= a+b) puts("2");
        else{
            ll x = floor(1.0*(c-a)/(a+b-2*c));
            long double ans1 = calc(x), ans2 = calc(x+1);
            ll x1 = ((x+1)*a+x*b-c*(2*x+1))*(2*x+3), x2 = (-(x+2)*a-(x+1)*b+(2*x+3)*c)*(2*x+1);
            if(x1 <= x2){
                printf("%d\n", 2*x+1);
            }
            else printf("%d\n", 2*x+3);
        }
    }

    return 0;
}
```

---

## 作者：45dinо (赞：3)

思路和楼上大佬是类似的，只是实现方法略有不同。

分三种情况：
- 如果 $t=h$，答案是 1。
- 如果 $t\leq\dfrac {h+c} 2$，答案是 2，**因为温度最低为$\dfrac {h+c} 2$**。
- 如果 $t>\dfrac {h+c} 2$ 时：

可以确定的是，一定是第 $i$ 次加完热水后的结果，$i$ 怎么求呢？可以用数学方法，但比较麻烦，容易出现精度错误，故考虑二分。

二分需要说明单调性，设 $f(i)$ 为第 i 次加完热水后的温度，即 $f(i)=\dfrac {i\times h+(i-1)\times c} {2\times i-1}$。显而易见当 $i<j$ 时，$f(i)>f(j)$。

或者可以把 $f(i)$ 理解为 一杯重量为 $(i-1)\times 2$，温度为 $a$ 的水和一杯重量为 1，温度为 $h$ 的水。

因为 $a=\dfrac {h+c} 2$，所以 $a<h$，同样可以想到当 $i$ 越大时，$f(i)$ 越小。

尽管二分更难写一点，但二分更好想，而且更常用，所以要学会用二分的思维解决问题。

---

## 作者：_Sonnet (赞：2)

# 题意
有两种水，一种是温度为 $h$ 的热水，一种是温度为 $c$ 的冷水。你可以将这两种水交替倒入一个无限大的桶中。求使桶中温度最接近 $t$ 的的操作次数。

# 思路
一道数学题

令 $mid$ 为 ${\frac{h + c}{2}}$。

显然有共有三种情况。

1. $t \ge h$ 

	此时倒一次热水温差最小。

1. $t \le mid $ 

	此时倒一次热水和一次冷水时温差最小，所以答案为 $2$。

1. $ mid < t < h $

	
我们发现当我们的操作次数为**奇**时，水温会越来越低。为**偶**时，水温为 $mid$。

我们令最终答案为 $k$，$k$ 显然为奇。

那么第 $k - 1$ 次的水温总和就是 $(k - 1) \times mid$。

因为最后一次操作次数为奇，所以倒的是热水，温度为 $h$。



于是我们就能得到这个公式：

 $$ \frac{(k - 1) \times mid + h}{k} = t$$

稍微转化一下:

$$ \frac{(mid - h)}{(mid - t)} = k$$

由于可能会有精度误差，我们在答案 $\pm 5$ 附近枚举一下就好。

代码见下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N = 1e3 + 100;
const int INF = 0x3f3f3f3f3f;
char a[N][N];
int summ;
signed main()
{
    int T;
    scanf("%lld" , &T);
    while(T --)
	{
		double h , c , t;
        scanf("%llf%llf%llf" , &h , &c , &t);
        double mid = (h + c) / 2;
        if(t == h)
		{
            puts("1");
            continue;
        }
        if(t <= mid)
		{
            puts("2");
            continue;
        }
        int ans = (mid - h) / (mid - t)  , anss = max(1ll , ans - 5ll);
        double maxx = INF;
        if(!(anss % 2))
		{
        	anss --;
		}
        for(int i = anss ; i <= ans + 5 ; i += 2)
		{
            if(fabs(1.0 * ((i - 1) * mid + h) / i - t) < maxx)
			{
            	maxx = fabs(1.0 * (i - 1) * mid + h) / i - t;
            	summ = i;
            }
        }
        printf("%lld\n" , summ);
	}
    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF1359C)

------------
# 思路
从热水开始，每次交替倒入盆中，可以发现如果倒的次数为偶数次，那么盆中水温一定为冷热水的平均值 $(h+c)/2$，令这个平均值为 $mid$，而如果倒的次数为奇数次，那么盆中水温将随着倒的次数的增多，从 $h$ 开始往 $mid$ 靠拢。


所以首先得出两个特判，如果 $t = h$ 输出 $1$，如果 $t \le mid$ 输出 $2$，剩余的，即 $mid \lt t \lt h$ 的部分，首先可以得到他们需要的倒水次数一定是奇数，且如果倒水次数从 $1$ 开始，按照奇数的顺序计算水温，则肯定会有某一次操作 $x$ 使得水温大于等于 $t$ ，且第 $x + 2$ 次操作使得水温小于 $t$，但是从 $1$ 开始每次加 $2$ 枚举，配合上数据组数会导致超时，所以还是要从公式入手。

可以得到，如果操作次数为偶数次，则平均水温一定为 $mid$，但此时答案操作次数为奇数次，令答案为 $ans$，则操作 $ans - 1$ 次时，得到水温总和为 $( ans - 1 ) \times mid$，第 $ans$ 次加入的是热水 $h$，所以可以得到如下公式：$[(ans-1) \times mid +h] \div ans = t$ 解出来为：$ans = (mid - h) \div (mid - t)$ 所以可以得到答案的近似操作次数。

由于操作次数一定是个整数，所以可以在求出此时的 $ans$ 后，在 $ans$ 周围枚举判断下哪一次操作才是真正的答案，计算误差不会太大，所以在 $\pm 3$ 范围内查找即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T;
signed main(){
    cin>>T;
    while(T--){
		double n,m,k,mid,b=1e8,c;
		cin>>n>>m>>k;
		mid=(n+m)/2.0;
		if(n==k){
		    cout<<1<<endl;
		    continue;
		}
		if(mid>=k){
		    cout<<2<<endl;
		    continue;
		}
		int a=(mid-n)/(mid-k),ans,i;
		i=max(1,a-3); 
		if(i%2==0){
			i--; 
		}
		for(;i<=a+3;i+=2){
		    c=fabs(1.0*((i-1)*mid+n)/i-k); 
		    if(c<b){
		        b=c;
		        ans=i;
		    }
		}
		cout<<ans<<endl;
    }
    return 0;
}
```
完结撒花~

---

## 作者：wangxinyi2010 (赞：0)

## Solution
本题难度：CF：1700，洛谷上对应绿题（水）。CF 上的标签是二分搜索和数学。  
此题需分类讨论倒水次数，这里设为 $n$：

- 若 $n$ 为偶数，则水温为 $\dfrac{h+c}2$。
- 若 $n$ 为奇数，则水温为
  $\dfrac{(n+1)\cdot h+(n-1)\cdot c}{2n}=\dfrac{1}{2}(h+c+\dfrac{h-c}{n})$，该数大于 $\dfrac{h+c}2$，小于等于 $h$，在有意义的范围内随 $n$ 的增加单调递减。

因此，若 $t=h$，则 $n=1$；若 $t\leq\dfrac{h+c}2$，则 $n=2$；若 $\dfrac{h+c}2\leq t<h$，求 $\dfrac{1}{2}(h+c+\dfrac{h-c}{n})=t$ 的解，得 $n=\dfrac{h-c}{2t-h-c}$。然后代入离 $n$ 最近的两个奇数的值进行计算，取离 $t$ 最近的结果输出。

注意 int 和 double 类型的使用。
## AC Code
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int T;
double a,b,t;//h,c,t
int main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		cin>>a>>b>>t;
		double lb=(a+b)/2.0,rb=a;
		if(t<=lb) cout<<2<<endl;
		else if(t>=rb) cout<<1<<endl;
		else{
			double n=(a-b)/(t-lb)/2.0;//解的另一种变形
			int a1,b1;
			double fa,fb;
			if(int(floor(n))%2==1){
				a1=floor(n);
				b1=floor(n)+2;	
			}
			else{
				a1=floor(n)-1;
				b1=floor(n)+1;
			}
			fa=fabs((a-b)/a1/2.0+lb-t);
			fb=fabs((a-b)/b1/2.0+lb-t);
			if(fa<=fb) cout<<a1<<endl;
			else cout<<b1<<endl;
		}
	}
	return 0;
}
```

---

