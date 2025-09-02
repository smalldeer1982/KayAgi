# Vanya and Triangles

## 题目描述

Vanya got bored and he painted $ n $ distinct points on the plane. After that he connected all the points pairwise and saw that as a result many triangles were formed with vertices in the painted points. He asks you to count the number of the formed triangles with the non-zero area.

## 说明/提示

Note to the first sample test. There are $ 3 $ triangles formed: $ (0,0)-(1,1)-(2,0) $ ; $ (0,0)-(2,2)-(2,0) $ ; $ (1,1)-(2,2)-(2,0) $ .

Note to the second sample test. There is $ 1 $ triangle formed: $ (0,0)-(1,1)-(2,0) $ .

Note to the third sample test. A single point doesn't form a single triangle.

## 样例 #1

### 输入

```
4
0 0
1 1
2 0
2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
0 0
1 1
2 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1
1 1
```

### 输出

```
0
```

# 题解

## 作者：mcyqwq (赞：3)

## I.题意简述
给出平面上的 $n$ 个点，求三个点两两相连能构成的三角形个数。

数据范围 $1 \le n \le 2000, |x_i|,|y_i| \le 100$

## II 题目分析
根据三角形不等式，只要三个点不在同一条直线上，就可以构成三角形。

因此，我们可以暴力枚举三个点，计算出他们之间连线的斜率判断是否在同一直线上，时间复杂度 $O(n^3)$。

考虑优化枚举过程。

设经过 $x, y$ 两点的直线的斜率为 $slope_{x,y}$，枚举的第一个点为 $a$，第二第三个点分别为 $b, c$。若 $slope_{a, b} = slope_{a, c} $，则 $a, b, c$ 三点在同一直线上。对于每一个 $a$，我们可以将所有的 $slope_{a,i}$ 排序，将所有相等的一段记录下来。如果有 $k$ 个点与 $a$ 的连线的斜率相等，则有 $\dfrac{k * (k - 1)}{2}$ 个点对（三个点）不能构成三角形。

最后答案是所有连线的方案数 $\dfrac{n * (n - 1) * (n - 2)}{6}$ 减去不能构成三角形的情况数。

时间复杂度 $O(n^2 \log n)$。

## III 代码
```cpp
#include <cstdio>
#include <algorithm>
 
#define ll long long
 
const int N = 3005;
int n;
ll sum;
long double s[N];
 
struct point {
    int x, y;
}a[N];
 
long double slope(point a, point b) {//计算斜率 
    if(a.x - b. x == 0) return 1e5;//若x坐标相同，将斜率设为一个极大值 
    return (long double)1.0 * (a.y - b.y) / (a.x - b.x);
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    for(int i = 1, cnt, now; i <= n; i++) {//枚举第一个点 
        cnt = 0, now = 1;
        for(int j = i + 1; j <= n; j++) {//注意此处从i + 1开始即可，防止重复计数 
            s[++cnt] = slope(a[i], a[j]);
        }
        std :: sort(s + 1, s + cnt + 1);//计算斜率并排序 
        for(int j = 2; j <= cnt; j++) {
            if(s[j] == s[j - 1]) now++;//记录斜率相同的点数 
            else sum += (1ll * now * (now - 1) / 2), now = 1; 
        }
        sum += (1ll * now * (now - 1) / 2); 
    }
    printf("%lld", 1ll * n * (n - 1) * (n - 2) / 6 - sum);
    return 0;
}
```
## IV 总结
当题目要枚举 $i, j$ 使 $f(i) = f(j)$ 或求 $min\{|f(i) - f(j)|\}$ 时，可以先将所有 $f(i)$ 排序，再枚举相邻的两个，将时间复杂度中的一个 $n$ 优化为 $\log n$


------------
## CSP-S 2021 & NOIP2021 rp++

---

## 作者：Milthm (赞：2)

## CF552D 题解

### 题目解法

对于这个题，需要用到有关斜率的知识。

首先拿到题目，我们发现，如果直接数三角形，会比较麻烦。但是如果判断出不合法的情况，再用总数去减去就简单了。

对于总数，很明显等于 $C_n^3$，也就是 $\frac{n(n-1)(n-2)}{6}$。

接下来，如果三个点组成不了三角形，则这三个点一定是在同一条直线上的。

判断三个点是否在同一条直线上，只需要判断它们的斜率是否相同。

不妨将点分成 $(x1,y1),(x2,y2)$ 和 $(x2,y2),(x3,y3)$ 两组分别计算斜率。如果在一条直线上，那么两组的斜率肯定相同。

根据斜率公式，可得：$\frac{y2-y1}{x2-x1}=\frac{y3-y2}{x3-x2}$。

根据小学就学过的十字相乘，得出：$(y2-y1)(x3-x2)=(y3-y2)(x2-x1)$。

然后枚举三个坐标，恭喜你，~~你又水了一道绿~~。

### AC代码


```cpp
#include<iostream>
#define int long long
using namespace std;
int x[2005],y[2005],n,ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];//输入x,y坐标
	}
	ans=n*(n-1)*(n-2)/6;//理论三角形总数
	for(int i=1;i<=n-2;i++){
		for(int j=i+1;j<n;j++){
			for(int k=j+1;k<=n;k++){
				if((y[j]-y[i])*(x[k]-x[j])==(y[k]-y[j])*(x[j]-x[i])){
					ans--;//如果三点一线就减去
				}
			}
		}
	}
	cout<<ans;//输出答案
	return 0;
} 
```
时间复杂度 $O(n^3)$。



---

## 作者：Exp10re (赞：0)

给一种题解区没有的 $O(n^2)$ 做法。

## 解题思路

注意到三个点不能构成面积不为 $0$ 的三角形，当且仅当其中一点在另外两点连接而成的直线上。

我们假定三个点为 $A,B,C$，那么显然的：当直线 $AB$ 与直线 $BC$ 斜率相等时三个点不能构成面积不为 $0$ 的三角形。

对于每个点，枚举其与其他点的斜率并进行计数。接下来枚举点对 $(A,B)$，那么点 $A$ 统计的斜率与直线 $AB$ 相同的点的个数减一就是其中一条边为 $AB$ 且不合法的三角形个数。

为什么要减一？因为点 $B$ 会被统计一次。

这样就求得了不合法的三角形个数，我们记它为 $cnt$。

因为每个三角形都被统计了 $6$ 次，因此本质不同的不合法三角形个数是 $\frac {cnt} 6$。

再考虑到所有三角形的数目是 $C^3_n$，因此答案就是 $C^3_n-\frac {cnt} 6$。

统计部分的斜率化为最简分数，用数组统计即可，时间复杂度 $O(n^2)$。

不知道为什么抢不过 $O(n^2\log n)$ 的最优解，可能常数比较大吧。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=2010,MAXP=203,Delta=201;
short book[MAXN][MAXP][MAXP*2];
long long a[MAXN][2],n;
inline long long abss(long long x)
{
	return x<0?-x:x;
}
struct slope
{
	long long x,y;
};
inline long long gcd(long long ta,long long tb)
{
	long long tc=ta%tb;
	while(tc!=0)
	{
		ta=tb;
		tb=tc;
		tc=ta%tb;
	}
	return tb;
}
inline slope getslope(long long x1,long long y1,long long x2,long long y2)
{
	long long xdis,ydis,t,g;
	xdis=x2-x1;
	ydis=y2-y1;
	if(xdis*ydis<0)
	{
		t=-1;
	}
	else if(xdis*ydis>0)
	{
		t=1;
	}
	else
	{
		if(xdis==0)
		{
			if(ydis==0)
			{
				return slope{0,0};
			}
			else
			{
				return slope{0,1};
			}
		}
		else if(ydis==0)
		{
			if(xdis==0)
			{
				return slope{0,0};
			}
			else
			{
				return slope{1,0};
			}
		}
	}
	if(xdis<0)
	{
		xdis*=-1;
		ydis*=-1;
	}
	ydis*=t;
	g=gcd(xdis,ydis);
	xdis/=g;
	ydis/=g;
	ydis*=t;
	return slope{xdis,ydis};
}
int main()
{
	long long i,j,ans=0,dec=0;
	slope t;
	scanf("%lld",&n);
	if(n<=2)
	{
		printf("0\n");
		return 0;
	}
	ans=n*(n-1)*(n-2)/6;
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i][0],&a[i][1]);
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(j==i)
			{
				continue;
			}
			t=getslope(a[i][0],a[i][1],a[j][0],a[j][1]);
			book[i][t.x][t.y+Delta]++;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i!=j)
			{
				t=getslope(a[i][0],a[i][1],a[j][0],a[j][1]);
				dec+=(book[i][t.x][t.y+Delta]-1);
			}
		}
	}
	printf("%lld",ans-dec/6);
	return 0;
}
```

---

## 作者：Parat_rooper (赞：0)

# 解题思路：
当我们第一眼看到这道题时，发现它是求三角形个数，首先肯定能想到用 $O(n ^ 3)$ 的时间去枚举三个点并校验能否组成三角形，如何统计答案。实际上这题的时限很大，朴素暴力是可以过的~~吧~~。在此就不详细再说。

然后我们考虑优化朴素算法。首先，我们发现如果直接去计算有多少个三角形是无法很好地优化的。这时我们运用逆向思维，可以考虑通过计算有多少点无法组成三角形，而后用总的点对数减去无法组成三角形的点对数。

而无法组成三角形的点必然就是三点共线的情况，这时我们很自然的想到通过斜率计算三点共线，而后我们枚举原点，通过斜率计算出有多少个点不能与该点构成三角形，统计答案。（不知道斜率的童鞋点[这里](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87/4914111?fr=aladdin)）

代码如下：

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 2001;

int n;
long long ans;

struct node {
  int x, y;
}a[kMaxN];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  for (int i = 1; i <= n; i++) {
    long double vis[kMaxN];//计算斜率
    for (int j = i + 1; j <= n; j++) {
      vis[j] = (a[j].x == a[i].x ? 1145141919.810 : double(a[j].y - a[i].y) / double(a[j].x - a[i].x));
    }//有点臭不要在意，注意j要从i+1开始，避免算重
    sort (vis + i + 1, vis + n + 1);//排序同样注意i+1
    int cnt = 1;//排序是为了快速计算出重复斜率数量
    for (int j = i + 2; j <= n; j++) {
      if (vis[j] != vis[j - 1]) {
        ans += 1ll * cnt * (cnt - 1) / 2ll, cnt = 1;
      } else {//统计重复斜率
        cnt++;
      }
    }
    ans += 1ll * cnt * (cnt - 1) / 2ll;
  }
  cout << 1ll * (n * (n - 1) / 2ll) * (n - 2) / 3ll - ans;
  return 0;
}
```
完结撒花~~~

求关注~~~


---

## 作者：zplqwq (赞：0)



## 前置芝士

1. 函数的基本知识

   此题后面要用到得公式，要用到函数的知识来推导

2. 坐标系的基本知识

   不用知道太多，但起码你得知道`x`和`y`分别表示啥

3. 斜率公式

   即$k$=$\frac {y2-y1} {x2-x1}$

## 题目分析

首先，题意就是求平面上$n$个点中三个点两两相连形成面积不为$0$的三角形的个数.

我们知道，三个点，**只有**三点共线的情况才**构不成**三角形。

那么我们只需求出三点共线的情况即可，若这三个点的坐标不共线，`cnt++`。

首先，设三个点的坐标分别为$(x1,y1),(x2,y2),(x3,y3)$

则因为这三个点共线，则他们的斜率必定相同。

那么，我们把这三个坐标分成两组：$(x1,y1),(x2,y2)$与$(x2,y2),(x3,y3)$

则第一组的斜率必定等于第二组的斜率。

也就是说$\frac {y2-y1} {x2-x1}$=$\frac {y3-y2} {x3-x2}$

我们十字交叉一下，可得：$(y2-y1)(x3-x2)=(y3-y2)(x2-x1)$

而这就是我们最重要的公式。

接下来只用枚举那三个坐标即可。

具体的看代码吧。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,m;

const int N=10000010;

struct qaq//存储xy的结构体
{
	int x,y;
};
qaq a[N];
int cnt=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;//输入
	}
	if(n<3)//这里有个特判，当点都不够三个的情况不可能组成三角形。
	{
		cout<<0<<endl;
		return 0;
	}
    //接下来就是代码最重要的部分
	for(int i=1;i<=n-2;i++)//枚举第一个点
	{
		for(int j=i+1;j<=n-1;j++)//二
		{
			for(int k=j+1;k<=n;k++)//三
			{
				if((a[j].y-a[i].y)*(a[k].x-a[j].x)==(a[j].x-a[i].x)*(a[k].y-a[j].y))//公式如上
				{
					continue;
				} 
				else
				{
					cnt++;//否则的话,cnt++
				}
			}
		}
	}
	cout<<cnt<<endl;//输出cnt
    return 0;
}

```

最后说一句，WC rp++！

注：感谢rui_er与Rui_R对我做这道题的时候的指导

---

## 作者：　　　吾皇 (赞：0)

### 刚拿到题后还是有点懵的，但花图研究一下就很清楚了![](https://cdn.luogu.com.cn/upload/pic/61527.png)
```
不妨将三个点叫做a、b、c，因为a、b定在一条直线上，所以只要b、
c在一条直线上，这三个点就不能构成三角形（在同一直线上）。
由于三个点的坐标都是整数，所以此时(c.y-a.y)=k(b.y-a.y),(c.x-a.x)=k(b.x-a.x).左右交叉相乘得k(c.y-a.y)(b.x-a.x)=k(b.y-a.y)(c.x-a.x)，即(c.y-a.y)(b.x-a.x)=(b.y-a.y)(c.x-a.x).
当a、b、c的坐标不满足上述条件时，ans++。
```
### 那么，代码如下
```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")//拿走不谢
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
struct san{
	int x,y;
}a[2001];//定义一个结构体来表示每个点的x，y坐标
int main(){
	cin>>n;
	if(n<3){//如果点的数量不到3个，则一定不可以构成三角形
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++) {
		cin>>a[i].x>>a[i].y;
	}
	for(int i=1;i<=n-2;i++)
	   for(int j=i+1;j<=n-1;j++)
	      for(int k=j+1;k<=n;k++){
            if((a[j].y-a[i].y)*(a[k].x-a[i].x)==(a[k].y-a[i].y)*(a[j].x-a[i].x)) continue;//如分析，当三点的坐标满足条件时跳过
            ans++;//否则答案值加一
		  }
	cout<<ans;
}
```
#### 解释一下 (c.y-a.y)=k(b.y-a.y),(c.x-a.x)=k(b.x-a.x)
```
设平面上有2点a、b，保证b在a的右上方。因为a、b在一条直线上，则若有一点c的坐标c.x=（b.x-a.x）,c.y=(b.y-a.y),点c.一定与a、b在同一直线上,同理可推得上式，可能解释不清楚看看就行
```



---

