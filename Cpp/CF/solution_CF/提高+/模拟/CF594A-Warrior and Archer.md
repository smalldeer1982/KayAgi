# Warrior and Archer

## 题目描述

In the official contest this problem has a different statement, for which jury's solution was working incorrectly, and for this reason it was excluded from the contest. This mistake have been fixed and the current given problem statement and model solution corresponds to what jury wanted it to be during the contest.

Vova and Lesha are friends. They often meet at Vova's place and compete against each other in a computer game named The Ancient Papyri: Swordsink. Vova always chooses a warrior as his fighter and Leshac chooses an archer. After that they should choose initial positions for their characters and start the fight. A warrior is good at melee combat, so Vova will try to make the distance between fighters as small as possible. An archer prefers to keep the enemy at a distance, so Lesha will try to make the initial distance as large as possible.

There are $ n $ ( $ n $ is always even) possible starting positions for characters marked along the $ Ox $ axis. The positions are given by their distinct coordinates $ x_{1},x_{2},...,x_{n} $ , two characters cannot end up at the same position.

Vova and Lesha take turns banning available positions, Vova moves first. During each turn one of the guys bans exactly one of the remaining positions. Banned positions cannot be used by both Vova and Lesha. They continue to make moves until there are only two possible positions remaining (thus, the total number of moves will be $ n-2 $ ). After that Vova's character takes the position with the lesser coordinate and Lesha's character takes the position with the bigger coordinate and the guys start fighting.

Vova and Lesha are already tired by the game of choosing positions, as they need to play it before every fight, so they asked you (the developer of the The Ancient Papyri: Swordsink) to write a module that would automatically determine the distance at which the warrior and the archer will start fighting if both Vova and Lesha play optimally.

## 说明/提示

In the first sample one of the optimum behavior of the players looks like that:

1. Vova bans the position at coordinate $ 15 $ ;
2. Lesha bans the position at coordinate $ 3 $ ;
3. Vova bans the position at coordinate $ 31 $ ;
4. Lesha bans the position at coordinate $ 1 $ .

After these actions only positions $ 0 $ and $ 7 $ will remain, and the distance between them is equal to $ 7 $ .

In the second sample there are only two possible positions, so there will be no bans.

## 样例 #1

### 输入

```
6
0 1 3 7 15 31
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2
73 37
```

### 输出

```
36
```

# 题解

## 作者：while_true (赞：9)

由于本人在思索了很久后才把本题思路打通，所以为了帮助像我一样没有非常理解解法的人，我打算再将解法非常详细地叙述一遍，如果您无法理解解法，请跟着我再一步步将题目捋顺。  

## Step.1 解题意
题目要求其实很好理解，共给出 $n$ 个点的位置，A,B两个人轮流取点，A要求最后剩下的两个点尽量近，B要求最后剩下的两个点尽量远。
## Step.2 推一推
在这过程中，有一些东西可以被推知，这里做出详细的解释（由于解释太过于精细，dalao们请自行忽视）：   
1. 一共有几个点？显然 $n$ 个   

2. 最后剩下几个点？显然 $2$ 个   

3. 综合 $1,2$，可知两人一共取走了 $n-2$ 个点 

4. 显然，两人取走的点是一样多的。也就是说，由于他们一共取走 $n-2$ 个点，因此 $A$ 和 $B$ 两人分别取走了 $\frac{n-2}{2}$ 个点。而学过小学数学的人都知道：  
$$\frac{n-2}{2}=\frac{n}{2}-\frac{2}{2}=\frac{n}{2}-1$$ 
  所以，两人分别取走了 $\frac{n}{2}-1$个点  
  
  5.$A$ 会取哪些点？$B$ 会取哪些点？这是**理解本题的关键**。首先有两个点能使A,B两人的收益同时最大（这不废话吗），但这两个点是**固定**的，即当数据给出时便已经确定。所以A为了使两点距离尽量近，会选择取走两点左右的点，更具体说，他会选择去掉**端点**位置的点。而B要使两点距离尽量远，会选择去掉**两点中间**位置的点。这里要注意的是，由于这两个点同时保证了A,B两人的利益最大化，所以两人都不会选择去掉这个点。   
  
  6. 如何确定两点位置？这是**构造代码的核心**。这其实很好理解。尤其是我们已经得出了上面的结论。由于B只会取两点之间的点且B取了 $\frac{n}{2}-1$ 个点（前文已推知），因此最后剩下两点之间的距离为 $(\frac{n}{2}-1)+1=\frac{n}{2}$，即两点间距离等于点数加一，详情可以参照[小学奥数：植树问题](https://mp.weixin.qq.com/s?__biz=MjM5MjYxOTMyMQ==&mid=2247496762&idx=7&sn=e62e998f200f0f8e0433c2965aaa7aac&chksm=a6a13a6c91d6b37a7acb8577d7bd0bd6a407a264c3cce55e6a1a330b60e23209b130b274ae5b&scene=27)。（注意这里假设每个点间距离为 $1$）。设较近的点距离为 $k$，则较远的点距离为 $k+\frac{n}{2}$。   
     
 
## Step.3 码一码（构造代码）
我们知道了剩余两个点的位置关系，就可以通过枚举第一个点的位置，得到第二个点的位置，得到两点间的距离。那如何确定当前枚举的情况是好的呢？由于A先取，具有先手优势，于是我们应当取两个点之间的距离最小值。   
需要注意的一点是，在枚举之前，由于输入的序列没有单调性，于是我们应先将其排序。   
### 代码如下：
```cpp
#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

const int N = 2e5 + 5;

int n;
int a[N];

int ans = (1 << 30);

signed main() {
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	
	sort(a + 1, a + n + 1);
	
	for(int i = 1; i <= (n >> 1); i ++) {
		ans = min(a[i + (n >> 1)] - a[i], ans);
	}
	
	cout << ans << endl;
	
	return 0;
}
```
**这里对位运算作出解释：$(n>>1)$ 代表 $n$ 二进制右移一位，等价于 $n\over 2$**    
写的这么认真，还不点赞吗？   
求过QWQ

---

## 作者：零殇 (赞：5)

#### 题意

给出 $n$ 个点的位置，$AB$ 两人轮流去掉一个点，$A$ 要令最后两点距离尽量小，$B$ 反之。求最后距离。

#### 思路

首先，我们自然要先给序列排序。

$A$ 的目的是令两点距离尽量小，最优策略就是将端点位置去掉。

$B$ 的目的是令两点距离尽量打，最优策略就是将中间位置去掉。

因为两人去掉的个数是一样的，且总共去掉了 $n-2$ 个点，所以两点之间隔了 $\frac{n}{2}-1$ 个点。

那么，我们就只要枚举距离 $\frac{n}{2}-1$ 的两点位置就好了。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,minn=2147483647,a[3000000];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n/2;i++)
		minn=min(minn,a[i+n/2]-a[i]);
	printf("%d",minn);
	return 0;
}
```

完结撒花~

---

## 作者：lukelin (赞：2)

### 题解
这是一道结论题，还是有一些思维难度的。  
我们发现，如果一个人要让两个人远离，那么他肯定会取中间的部分，而如果要让两个人靠近，那么必定回取两边的部分，所以说最后两个人在数组里的距离一定是$\frac{n}{2}$，由于A是先手，所以取min。
### 代码
```cpp
#include <cstdio>
#include <algorithm>

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int a[200005];

int main(){
    int n = read();
    for (int i = 0; i < n; ++i) a[i] = read();
    std::sort(a, a + n);
    int ans = 1000000000;
    for (int i = 0; i < n / 2; ++i)
        ans = std::min(ans, a[i + n / 2] - a[i]);
    printf("%d", ans);
    return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

**前言。**

- 关于本题。

做法：找策略，简单的博弈论与贪心。

题意：[题目传送门](https://www.luogu.com.cn/problem/CF594A)。

综合评价：理清思路即不难。

- 关于博客。

近期因为一些特殊原因（同学之间），博客文章均被隐藏，请不要去我的博客看了，以后我会逐步开放文章，请谅解。

**分析**

因为 $A$ 要使两点距离尽可能近，但 $B$ 要使两点距离尽可能远，可以知道：

如果使两点距离短，那么一定是从两边取，因为从两边开始取，那么两点距离将不断减小。

如果使两点距离长，那么一定是从中间取，因为从中间开始取，那么两点距离将不断扩大或者不变。

如此进行，那么当只剩下两个点的时候，就剩下了 $n-2$ 个点，所以 $A$ 与 $B$ 每人取了 $\frac{n}{2}-1$ 个点。

由于 $B$ 的做法，那么剩下的两个点在 $a$ 数组的距离是 $\frac{n}{2}$，同时 $A$ 的先手也决定了是其最小值。

排序后枚举即可。

代码如下，仅供参考：
```
/*
语言：C++14(GCC 9）
用时：2.72s
代码长度：300B
占用内存：792.00KB
*/
#include<iostream>
#include<algorithm>//sort在这里面
#include<cmath>
using namespace std;
int n,a[200005];
int ans=0x3f3f3f3f;//ans要设得尽可能大
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for (int i=1;i<=n/2;i++){
        ans=min(ans,a[i+n/2]-a[i]);
    }//计算
    cout<<ans<<"\n";
    return 0;
}//by zzy
``` 
**后记。**

没有什么好说的。

---

## 作者：让风忽悠你 (赞：1)

[原题](https://www.luogu.com.cn/problem/CF594A)

## 做法

首先要知道让所剩两点距离尽量远的基本策略就是将只留下两边，把中间挖空，相反使其尽量近的策略就是删去两边，留下最近两点。

那么对于一个长度为 $n$ 的序列，$A,B$ 能删除的数的数量都是 $ \frac{n-2}{2} $，而 $A$ 又是先手，所以最后的结果必然是 $ \min \{ a_{n/2+i}-a_i\}$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 200005
#define inf 0x7fffffff

using namespace std;

int n,res=inf;
int a[N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n); // 先排序使其位置有序 
	for(int i=1;i<=n/2;i++)
		res=min(res,a[i+n/2]-a[i]);
	printf("%d",res);
	return 0;
}
```


---

## 作者：傅思维666 (赞：1)

## 题解：

题面说得不太好，重新给一遍题目大意：给出偶数的N，和N个点的坐标（数轴，整数），A,B轮流拿走一个点，A先拿，A要使两点距离尽可能近，B要使两点距离尽可能远，假设AB两人都使用最佳策略，求最后两点间距离。

其实感觉算不上紫题。

肯定要先按坐标排序啊，然后因为A要使得最后的两点距离尽可能近，那就要从两边选点，B就要从中间选点了。那么这就是一个简单的贪心，直接按题意，枚举所有可行点对即可。复杂度卡在排序上。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=2e5+5;
const int INF=1e9;
int n;
int a[maxn];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int ans=INF;
    for(int i=1;i<=n/2;i++)
        ans=min(ans,a[i+n/2]-a[i]);
    printf("%d",ans);
    return 0;
}
```



---

## 作者：hgoicjl (赞：1)

### 题意：
给出偶数个点，AB两人轮流去掉一个点，直到只剩两个

A要使两点距离尽可能近，B要使两点距离尽可能远

假设AB两人都使用最佳策略，A先去掉一个点，求最后两点间距离

### 算法：
**博弈**

### 解法：
设最后的两个点是 $[l,r]$ ，一共有$k$个点

则A要使距离尽可能近，会去掉$(0,l)\bigcup(r,+\infty)$ 中的点

B要使距离尽可能近，会去掉$(l,r)$ 中的点

显然A和B所去掉的点数量是一样多

所以$r$与$l$之间有$k-1$个点

A是先手，所以枚举所有可能的最小值即可

### code
```
#include<bits/stdc++.h>
using namespace std;
int a,b[2000005],ans=0x3f3f3f3f;
int mian()
{
	cin>>a;
	for(int i=1;i<=a;i++)
		cin>>b[i];
	sort(b+1,b+a+1);//点并不是升序排序
	for(int i=1;i<=a/2;i++)
		ans=min(ans,b[i+a/2]-b[i]);//保证l,r之间有k-1个点并且求最小值
	cout<<ans<<endl;
	return 0;
 } 
```
***
**你说抄题解的人会不会WA呢（滑稽）**

---

## 作者：Convergent_Series (赞：0)

首先，根据样例 $2$ 可得，给出的点不一定按顺序，需要先排序。

A 若想使两点距离尽可能小，就要取走间隔最大的点，一定都在最终点的外围。  
B 若想使两点距离尽可能大，就要取走间隔尽可能小的点，一定都在最终点之间。

一共会取走 $n-2$ 个点，由于两人轮流取点，所以最终点间隔 $\frac{n-2}{2}=\frac{n}{2}-1$ 个点。

由于 A 是先手，所以答案会尽可能小。枚举最终点，求出距离，取最小值即可。


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,minn=INT_MAX;
int a[200010];
signed main()
{
	cin>>n;
	int i; 
	for(i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(i=1;i<=n/2;i++) minn=min(minn,a[i+n/2]-a[i]);
    //注意枚举范围
	cout<<minn;
	return 0;
}
```

---

## 作者：ZVitality (赞：0)

博弈论题一般先模拟数据，找最优思路的套路。

先拿样例：

```.klain
6
0 1 3 7 15 31
```

可以发现：

如果把 $0$ 或者 $31$ 去掉会更近，因为极端去掉了就只有中间了。这是先手的策略。

而后者要求尽量大，那可以发现如果把中间删去会更加容易让两边的极端留下，然后就可以尽可能大。

所以，在两轮之内，两边会删掉，中间也会被删两个，两个点的距离为 $\lfloor\frac{n}{2}\rfloor-1$，只要扫一遍取最小值就好了。

因为题目没有说点单调递增，所以要排序。

---

## 作者：TachibanaKanade (赞：0)

鉴定为恶评题。水一手贡献分。

[题目链接](https://www.luogu.com.cn/problem/CF594A)

首先考虑两个人分别的最优策略是什么。

A 要使两点尽可能地近，则他一定是优先从两边的点开始去。

B 要使两点尽可能地远，则他一定是优先从中间的点开始去。

不妨假设最后剩下的两个点为 $a$ 和 $b$。

从 B 的策略考虑，因为两人所去掉的点数相同，可以看出 $a$ 与 $b$ 之间的距离为 $\dfrac{n}{2}$。

故枚举所有距离为 $\dfrac{n}{2}$ 的点后取最小值即可。

记得排序。

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200200;
int n, x[maxn], d[maxn], ans = 0x3f3f3f3f;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n / 2; i++) d[i] = x[n / 2 + i] - x[i];
    sort(d + 1, d + n / 2 + 1);
    cout << d[1];
}
```


---

## 作者：CyaNgw_DyG (赞：0)

## 题意
给出 $n$ 个点（$n$ 为**偶数**)，$A$，$B$ 两人依次各自删掉一个点，删到只剩两个点为之。

$A$ 想让剩下的两个点的差小，$B$ 想让剩下的两个点的差大，

求他们用**最佳策略**后剩下两个点的差为多少。


------------

## 思路
本题纯属**博弈论**。

具体要让剩下的两个数**相差得远的同时又是最近**，

题目中输入的 $n$ 个数与输入顺序无关，所以我们可以先`sort`**从小到大排序**，


那么最终剩下的两个数在**排序后数组的下标**就一定就会相差          $\dfrac{n}{2}$。

如何证明呢，利用**反证法**：

若让最终的两个数在排序后数组的下标相差 $\dfrac{n}{2}-x$，$1\le x\le\dfrac{n}{2}$，

那么**最佳策略**就会让最终答案的两个数的下标相差 $\dfrac{n}{2}+x$，则达不到最近。

所以只需要把每两个下标相差 $\dfrac{n}{2}$ 的数的差算出来取所有中的最小值即可。



------------

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int rd(){int Q;scanf("%d",&Q);return Q;}
int n=rd(),a[2000010],ans=1000000000;
int main(){
   for(int i=1;i<=n;a[i++]=rd());
   sort(a+1,a+1+n);
   for(int i=1;i<=n/2;i++)
      ans=min(ans,a[i+n/2]-a[i]);
  cout<<ans;
} 
```


---

## 作者：Yukinoshita_Yukino (赞：0)

结论题。

题意：A和B轮流取石子，A想最后剩下两个的石子距离最小，B想最后剩下两个的石子距离最大
。求实际取完后的石子距离。

A最优的是从两边取，B最优是从中间取。

这样一共取了 $n-2$ 次，A和B每人取了 $\frac{n}{2}-1$ 次石子。

由于B的贪心性质，可以得到剩下的两个点在数组的距离为 $\frac{n}{2}$ 。

由于A是先手，所以我们只需求所有在数组中距离为 $\frac{n}{2}$ 的最小值。

原序列没有排序，需要先排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
int ans=0x7fffffff,n,cnt[maxn];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>cnt[i];
	sort(cnt+1,cnt+n+1);
	for(int i=1;i<=(n>>1);i++) ans=min(ans,cnt[i+(n>>1)]-cnt[i]);
	cout<<ans;
	return 0;
}

```

---

## 作者：_Clown_ (赞：0)

# A.Warrior and Archer
$\mathtt{Difficulty}$=$\mathtt{2300}$

这道题目其实算是一道结论题。

我们首先将序列排个序。

因为 A 要使两点距离尽可能近，

然而 B 要使两点距离尽可能远。

我们首先想到：
- A 肯定从两边开始取。
- B 肯定从中间开始取。

这样破坏道只剩 $2$ 个点的时候，

因为一共少了 $n-2$ 个点，

所以每人取了 $\frac{n}{2}-1$ 个点。



然后我们就得到了这道题的核心结论,即：
>  枚举距离为 $\frac{n}{2}$ 的点，再取最小值即可。

代码不难写出
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,A[200001];
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("IN.in","r",stdin);
	#endif
	register int i,j;cin>>N;
	for(i=1;i<=N;i++)cin>>A[i];
	sort(A+1,A+N+1);
	register int Ans(INT_MAX);
	for(i=1;(j=i+N/2)<=N;i++)Ans=min(Ans,A[j]-A[i]);
	cout<<Ans<<endl;
	return 0;
}
```


---

