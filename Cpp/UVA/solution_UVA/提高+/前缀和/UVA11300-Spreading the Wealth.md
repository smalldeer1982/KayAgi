# Spreading the Wealth

## 题目描述

圆桌旁边坐着$n$个人，每个人有一定数量的金币，金币的总数能被$n$整除。每个人可以给他左右相邻的人一些金币，最终使得每个人的金币数量相等。您的任务是求出被转手的金币的数量的最小值。

　

## 样例 #1

### 输入

```
3
100
100
100
4
1
2
5
4```

### 输出

```
0
4```

# 题解

## 作者：DarthVictor (赞：11)

2020.7.30新更新，之前不会用$\LaTeX$，现在加上了……

## 题目
[原题链接](https://www.luogu.com.cn/problem/UVA11300)
## 解说
真是一道苏维埃气息极其浓郁的题目啊，共产主义马上就要实现了！（财富液化委员会表示很赞）

![](https://cdn.luogu.com.cn/upload/image_hosting/h137119b.png?x-oss-process=image/resize,m_lfit,h_200,w_400)

但可惜的是这道题并没有那么友善。这是一道数学题。（兄弟们把害怕打在公屏上）

在经过繁杂的思考的思考后，我觉得思路大概就是下面这样：

首先非常显然最后所有人的金币都要变成$ave=\frac{sum}{n}=\frac{A_1+A_2+A_3+ \dots + A_n}{n}$（$A_i$为原数组）。

由于金币只能在相邻的人之间传递，所以我们不妨设$X_i$ 代表$i$ 向$i-1$号传递的硬币（正负表示方向，正数表示$i$向$i-1$传递的，负数表示$i-1$向$i$传递的，自然，$0$代表不用传递。由于是一个环，$X_1$就表示$1$和$n$号之间的关系）。

由于最后所有人金币均为$ave$，所以每个人的原金币减给出去的加拿过来的结果必定是$ave$，即$A_i-X_i+X_{i+1}=ave$。移个项，我们得到$X_{i+1}=ave-A_i+X_i$。由此，我们可以得到一列数组：

$$X_2=ave-A_1+X_1$$

$$X_3=ave-A_2+X_2=2 \times ave-A2-A1+X1$$

$$X4=ave-A3+X3=3 \times ave-A3-A2-A1+X1$$

$$\dots$$

$$X_n=(n-1) \times  ave-A_{n-1}-\dots-A_2-A_1+X_1$$

非常显然我们看到$X_i=(i-1) \times ave- A_{i-1} -\dots-A_2-A_1+X_1$，每个最后都有$X_1$，但是前面不太一样，那么我们不妨把它简化一下。设$C_i=A_1+A_2+\dots+A_{i-1} - (i-1) \times ave$，那么我们可以化简上面这一坨式子，得到：

$$C_1=0$$

$$X_2=X_1-C_2$$

$$X_3=X_1-C_3$$

$$X_4=X_1-C_4$$

$$\dots$$

$$X_n=X_1-C_n$$

这样的话就可以转回来看看我们要求什么了。答案应为$\vert X_1\vert + \vert X_2 \vert + \vert X_3 \vert+\dots+\vert Xn \vert$的最小值，根据上面得到的$X_i =X_1-C_i $，我们的答案可化为$\vert X_1 \vert+\vert X_1-C_2\vert+\vert X_1-C_2 \vert +\dots+\vert X_1-C_n\vert$。现在我们只要找一找选哪个数当做$X_1$可以使上式最小就行了。

我们知道$\vert X_1-C_i\vert$在数轴上表示两点之间距离，因此此题最终转化为在数轴上求一个点$X_1$，使其到点$0,C_2,C_3 \dots C_n$的距离之和最小。显然，$X_1$为这些数的中位数的时候这个数是最小的 ~~（怎么证明？回去看自己的初中课本谢谢）~~

那么，就是这样。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=1000000+2;
typedef long long ll;//数据范围显示要开long long
ll a[maxn],sum,ave,c[maxn];
int n;
int main(){
    while(scanf("%d",&n)!=EOF){
        sum=0;
        for(int i=1;i<=n;i++) {
            scanf("%lld",&a[i]);
            sum+=a[i];
        }
        ave=sum/n;
        c[1]=a[1]-ave;
        for(int i=2;i<=n;i++) c[i]=c[i-1]+a[i]-ave;
                //上面这两行用于计算Ci
        sort(c+1,c+1+n);
        ll mid=c[n/2];//中位数
        ll ans=0;
        for(int i=1;i<=n;i++) ans+=abs(mid-c[i]);
        printf("%lld\n",ans);
    }
    return 0;
}
```
## 尾声
其实上面的代码是有BUG的（SURPRISE！）

由于数据比较水，上面的代码A了。但事实上你拿5 1 2 3 4 5试试上面的代码，答案是4，上面的代码给的是5 。因为C n/2不是中位数，n为偶数时有两个中位数，所以出现了问题。

完全正确的代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=1000000+2;
typedef long long ll;
ll a[maxn],sum,ave,c[maxn];
int n;
int main(){
    while(scanf("%d",&n)!=EOF){
        sum=0;
        for(int i=1;i<=n;i++) {
            scanf("%lld",&a[i]);
            sum+=a[i];
        }
        ave=sum/n;
        c[1]=a[1]-ave;
        for(int i=2;i<=n;i++) c[i]=c[i-1]+a[i]-ave;
        sort(c+1,c+1+n);
        ll mid=c[n/2];
        ll ans1=0;
        for(int i=1;i<=n;i++) ans1+=abs(mid-c[i]);
        mid=c[n/2+1];
        ll ans2=0;
        for(int i=1;i<=n;i++) ans2+=abs(mid-c[i]);
        printf("%lld\n",min(ans1,ans2));
    }
    return 0;
}
```

幸甚至哉，歌以咏志。

---

## 作者：Sweetie_Liu (赞：6)

# UVA11300 Spreading the Wealth
### 一道经典的好题
#### 题面简化：给你一坨金币，让你平摊，求转移金币的最小值。
拿到手里我TM就像人机一样脑子里全是各种金币的转移，又是左到
右又是正负**极其的混乱**，但是如果手拿~~大伊万~~冷静考。

如果$x_1$给$x_2$ **a** 个金币，$x_2$再给$x_1$ **b** 个金币，这是就相当于$x_2$给出了$b-a$个金币,这样不难想到设 $x_i$ 为$i$给$i-1$的金币数，$x_i$可正可负。

我们显然可以在分配之前就可以知道**分配之后的数**，$M=\frac{\sum_{i=1}^n a_i}n$
然后我们可以得到$n$个，但本质上只有$n-1$的方程组：

$M = A_i-x_i+x_{i+1}(1\to n)$

***Ps* :看起来是$n$个方程，但实质是前$n-1$个方程推导出了第$n$个方程，因为它是个~~♂~~环。**

$x_2 = |x_1-(A_1-M)|$

$x_3 = M - A_2 + x_2$

$x_3 = M - x_2 - (A_2-M)$

$x_3 = x_1 - (A_1-M)-(A_2-M)$

$x_3 = |x_1 - (A_1+A_2-2\times M)|$

$x_i = |x1 - (\sum _{j=1}^{i-1}Aj - (i-1)\times M)|$

设$C_i=\sum_{j=1}^nA_j-i\times M$

$C_i$我们可以用**前缀和**处理，然后所有的$x_i$就可以被$x_1$表示出来。

我们要求的是$\sum_{i=1}^nxi$,那么我们的问题就转化成**给$x_1$选一个位置使得到所有的$C_i$的距离和最小**，我们显而易见这个位置是$C_i$数组的**中位数**

排序$O(n)$求解，总复杂度$O(nlogn)$

代码**要注意细节**

```cpp

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define int long long
#define Re register
using namespace std;
int read(){
	int w=1,x=0,ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	return x*w;
}
const int MAXN = (int)1e6+10;
int n,m,A[MAXN],M,Sum[MAXN];
signed main(){
	while(scanf("%lld",&n)!=EOF){
		int tmp = 0;
		for(Re int i=1;i<=n;i++){
			A[i] = read();
			tmp += A[i];
		}
		M = tmp/n;
		Sum[0] = 0;
		for(Re int i=1;i<=n;i++){
			Sum[i] = Sum[i-1]+A[i]-M;
		}
 //这里我们可以看出其实Sum[n]是0，也就是侧面证明了最后一个式子是没用卵用的，这里的sum[n]的贡献是x1自己
		sort(Sum+1,Sum+1+n);
		int los = n/2,ans = 0;
		for(Re int i=1;i<=n;i++){
			ans += abs(Sum[los]-Sum[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：风浔凌 (赞：5)

环形均分纸牌问题应该不少人都很熟悉了，而且题解区写的也比较全了......

## 我这篇题解主要是介绍一个新的STL——nth_element

## 以及解答几个其他题解里面有应用但是没有注释的问题。（比如说我第一次看就十分懵逼）

**如果从第i个人开始转手，那么他们的前缀和分别为**

**s[i+1]-s[i]**

**s[i+2]-s[i]**

**......**

**s[n]-s[i]**

**s[1]+s[n]-s[i]**

**......**

**s[i]+s[n]-s[i]**

**因为是均分，所以满足s[n]恒等于0，所以加和可得最小数量：**$\sum_{i=1}^n$abs(s[i]-s[k])

（为什么数量是前缀和相加呢，因为当轮到自己的时候前面应该已经均分过了，将自己和前面看作一个整体，而这时就必须要下一个进行交换，使得自己的体系平均下来和均值相等，而这个和均值相差的值，自然就是abs(前缀和)了，所以最后我们将它累加，就是答案。）



**显然当s[k]取中位数时数量最小。**
（而为什么有这个显然呢，借用别的dalao的话来说就是：原因各位可以想象将 S[i] 投影到一个坐标平面内。然后我们用一条线去扫，点到线的距离之和就是上面的式子的最小值。从中位数的位置变化到靠下的位置或是靠上的位置，都会使某一部分点的距离增大。）


### STL中的nth_element()方法的使用：

通过调用**nth_element(start, start+n, end)** 方法可以使第n大元素处于第n位置（**从0开始,其位置是下标为 n的元素**），并且比这个元素小的元素都排在这个元素之前，比这个元素大的元素都排在这个元素之后，但**不能保证他们是有序**的

但是明明已经有了sort排序，为什么要用这个呢——因为这个的时间复杂度比sort优，是log(n)级别的，显然更快一点。

我的代码中将每一项都减去了平均值，其实减不减无所谓，减掉反而又有一点多此一举了.......
```c
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAXN 1000010
using namespace std;
int n;
long long a[MAXN],s[MAXN],sum=0,ans=0;
int main(){
	while(scanf("%d",&n)!=EOF)
	{
	//scanf("%d",&n);
	memset(a,0,sizeof(a));
	memset(s,0,sizeof(s));
	sum=0;  ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum+=a[i];
	}
	sum=sum/n;
	for(int i=1;i<=n;i++)
	{
		a[i]-=sum;
		s[i]=s[i-1]+a[i];
	}
    int mid=(n+1)/2;
    //中位数的位置
    nth_element(s+1,s+mid,s+1+n);
    /*上文中有提到，所以中间这个加上的值就是表示从0开始，安排好第mid位为中位数，因此不必+1
    但是由于我们迭代器使用的是数组的位置，所以前后位置限定还是要+1的*/
    int cur=s[mid];
    for(int i=1;i<=n;i++)
    	ans+=abs(s[i]-cur);
	printf("%lld\n",ans);
}
	return 0;
}
```
### 话说环形均分纸牌的题目还真的不少，
### 这不是四倍经验么2333：
（大家如果觉得掌握的不好可以去AC这几道题，基本上都差不多，就是开long long和不开long long 的区别......，哦对了，输入格式也有一点点不一样，注意改一下）

[P4016](https://www.luogu.org/problemnew/show/P4016)

[P2512](https://www.luogu.org/problemnew/show/P2512)

[P3156](https://www.luogu.org/problemnew/show/P3156)

---

## 作者：邓布利多6 (赞：3)

## UVA11300 Spreading the Wealth
### 题目描述

圆桌旁边坐着 $n$ 个人，每个人有一定数量的金币，金币的总数能被 $n$ 整除。每个人可以给他左右相邻的人一些金币，最终使得每个人的金币数量相等。您的任务是求出被转手的金币的数量的最小值。

### 输入格式

输入包含多组数据。每组数据第一行为一个整数 $n(n<=1000000)$ ,以下 $n$ 行每行为一个整数，按逆时针顺序给出每个人拥有的金币数。输入结束标志为文件结束符($EOF$).

### 输出格式

对于每组数据，输出被转手的金币的数量的最小值。输入保证这个值在 $64$ 位无符号整数的范围之内。


### 题目分析
每个人最终的金币数 $\red {m =  \frac{\sum_{i = 1}^{n}a_i}{n}}$


------------

问题转化为第 $i$ 个人只会给第 $i-1$ 个人 , 假设他给了第 $i-1$ 个人 $x_i$ 个金币 , 那么有

```
for(int i = 1; i <= n; i++)
	m = a[i] - x[i] + x[i+1]
 ```
即，$m$ = 任意原数 $-$ 给掉的 $+$ 得来的


------------

然后移项得，$x_{i+1} = m - a_i + x_i$

$x_2 = m - a_1 + x_1 $

$x_3 = m - a_2 + x_2 = m - a_2 + (m - a_1 + x_1)$

整理得，$x_2 = x_1 - (a_1 - m)$

 $x_3 = x_1 - (a_1 + a_2 - 2m)$
 
$x_4 = x_1 - (a_1 + a_2 + a_3 - 3m)$

$......$

$\red{x_i = x_1 - (\sum_{j=1}^{i-1} a_j - (i-1) * m)}$


------------

发现除了 $x_1$，括号里面的值都是已知的 ,而题目其实是**最小化$ \sum_{i = 1}^{n}|x_i|$**.

### 正确解法
$x_i = x_1 - (\sum_{j=1}^{i-1} a_j - (i-1) * m)$ 

也就是数轴上 $x_1$ 到 $\sum_{j=1}^{i-1} a_j - (i-1) * m$ 的距离

所以问题就变成了取括号里面的数，找一个 $x_1$ 到它们的**距离和最短**，那么显然 $x_1$ 是这些东西的**中位数**， 通过排序求出中位数后，统计每个 $x_i$ 的绝对值之和即可。

### 代码
```
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1000001;
typedef long long LL;
LL n, a[N], m, x[N], ans, sum;
int main()
{
    while(cin >> n)
    {
		m = ans = 0;
        for(int i = 1; i <= n; i++)
            cin >> a[i], m += a[i];
        m /= n;
        x[1] = 0;
        for(int i = 2; i <= n; i++)  
            x[i] = x[i - 1] - m + a[i];
        sort(x + 1, x + 1 + n);  
        sum = x[n / 2 + 1];
        for(int i = 1; i <= n; i++)  
           ans += abs(sum - x[i]);
        cout << ans << endl;
    }
    return 0;
}

```


---

## 作者：Nepenthe (赞：3)

## Hint
算是环形均分问题的模板题了

首先我们定义 $a_i$ 表示第 $i$ 个人原有的金币数量,$x_i$ 表示第 $i$ 个人向第 $i-1$ 个传的金币数量,并规定

- $x_1$ 表示第一个人传给第 $n$ 个人的金币数
- $x_i$ 可以为负数,表示第 $i$ 个人很穷需要第 $x-1$ 给他 $x_i$ 个金币

那题意即为求出 $|x_1|+|x_2|+|x_3|...+|x_n|$ 的最小值

我们知道最后要达成均富,则最后所有人都要达到 $M=sum/n$ 个金币,我们可以列出下列等式
$$M=a_1-x_1+x_2$$
$$M=a_2-x_2+x_3$$
$$M=a_3-x_3+x_4$$
$$..........$$
我们可以想到用 $x_1$ 表示出所有 $x_i$ , $x_1+x_2+x_3...+x_n$ 这个式子转化成一元方便求最值

运用解方程组的基本数学方法我们可以得到
$$x_i=x_1-[\sum _{i=1}^{n-1} a_i-(n-1)M]$$
(这个很好得到我就不赘述了)

其中 $\sum _{i=1}^{n-1} a_i-(n-1)M$ 总是个定值,我们可以令它为 $b_i$

这样得到$$x_i=x_1-b_i$$
其中 $b_i$ 是个可以算出来的定值
所以 $$|x_1|+|x_2|+...+|x_n|=|x_1|+|x_1-b_2|+...+|x_1-b_n|$$
根据绝对值的定义可以看作 $x_1$ 到 $b_1,b_2...b_n$ 的距离之和

容易想到取 $x_1$为$\{b_n\}$的中位数

------

## Code
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
#define siz 1000002
using namespace std;
long long n, sum, M, x_1, ans;
long long a[siz], b[siz];
int main() {

	while(~scanf("%lld",&n)) {
	
		sum = 0, ans = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%lld",&a[i]);
			sum += a[i];
		}
		M = sum / n;
		
		b[1] = 0;
		for(int i = 2; i <= n; ++i)  
		   b[i] = b[i - 1] - M + a[i];
		sort(b + 1,b + 1 + n);  
		x_1 = b[n / 2];
		for(int i = 1; i <= n; ++i)  
		   ans += abs(x_1 - b[i]);
		
		printf("%lld\n",ans);
	}
	return 0;
}
```
**Tip** 即使 $n$ 是个偶数我们仍然可以令 ```x_1 = b[n / 2];``` 因为它一定是一个整数


---

## 作者：YellowBean_Elsa (赞：2)

#### 这里提供思路，式子请自行推倒或参考代码

注意到金币总数不变，所以每个人最后手中的金币数确定，则每个人要转出或转入的金币数一定。

又因为每个人只能和两个人交易，故确定和一个人的交易之后就可确定与另一个人的交易。

我们又推广发现，只要确定任意一组相邻两人的交易，其它所有交易都可确定。

所以交易总额就是个一元函数！

推式子发现这是个绝对值函数，于是我们利用初一数学中绝对值的几何意义可求得最小值。

式子就不推了，大概就是列 $n-1$ 个线性方程再用点错位相减。

代码里有一些详细式子和绝对值函数最值求法

```cpp
//coder: FeliksGM-YB
#include<bits/stdc++.h>
#define fu(i,a,b) for(int i = a, I = (b) + 1; i < I; ++i)
#define fd(i,a,b) for(int i = a, I = (b) - 1; i > I; --i)
typedef long long ll;
using namespace std;
const int N=1e6+5;
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x;
}template <class T> inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(!isdigit(ch))f=ch=='-'?-1:1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    x*=f;
}int n;
ll a[N],avg,ans;//avg: 平均数 
ll sum[N];//a 数组前缀和 
ll x[N];//x[i] = -i * avg + sum[i]
//令 k[i] 表示每个人定向转出金币数
//推出 k[i] = k[1] - x[i-1]
//绝对值函数最小值，变量为 k[1]，利用几何意义：
//k[1] 到 x[i] (1 <= i < n) 和 0 的距离之和
ll m;//表示 k[1]
//初一数学，取中位数即可 
int main(){
	while(~scanf("%d",&n)){
		avg=ans=0;
		fu(i,1,n)read(a[i]),avg+=a[i],sum[i]=sum[i-1]+a[i];
		avg/=n;
		fu(i,1,n-1)x[i]=sum[i]-i*avg;//求 x[i]
		x[n]=0;//大部分题解里都把这句直接去掉而上一步循环到 n, 效果一样
		//但其实意义有差别，这导致我看了半天（主要因为我太菜QwQaQ） 
		nth_element(x+1,x+(n+1>>1),x+n+1);//nth_element找中位数，快一点 
		m=x[n+1>>1];//取中位数，得绝对值函数最小值取到的点 
		fu(i,1,n)ans+=abs(m-x[i]);//求最小值 
		printf("%lld\n",ans);
	}return 0;
}
```



---

## 作者：张亦弛 (赞：2)

这道题目看起来很复杂，让我们慢慢分析。首先，最终每个人的金币数量可以计算出来，它等于金币总数除以人数n。接下来我们用M来表示每人最终拥有的金币数。

　　假设有4个人，按顺序编号为1, 2, 3, 4。假设1号给2号3枚金币，然后2号又给1号5枚金币，这实际上等价于2号给1号2枚金币，而1号什么也没给2号。这样，可以设x2表示2号给了1号多少个金币。如果x2<0，说明实际上是1号给了2号-x2枚金币。x1，x3和x4的含义类似。注意，由于是环形，x1指的是1号给4号多少金币。 
现在假设编号为i的人初始有Ai枚金币。对于1号来说，他给了4号x1枚金币，还剩Ai-x1枚；但因为2号给了他x2枚金币，所以最后还剩A1-x1+x2枚金币。根据题设，该金币数等于M。换句话说，我们得到了一个方程：A1-x1+x2=M。 
同理，对于第2个人，有A2-x2+x3=M。最终，我们可以得到n个方程，一共有n个变量，是不是可以直接解方程组了呢？很可惜，还不行。因为从前n-1个方程可以推导出最后一个方程（想一想，为什么）。所以，实际上只有n-1个方程是有用的。 
尽管无法直接解出答案，我们还是可以尝试着用x1表示出其他的xi，则本题就变成了单变量的极值问题。 

　　对于第1个人，A1-x1+x2=M  x2=M-A1+x1=x1-C1（规定C1=A1-M，下面类似）
  
　　对于第2个人，A2-x2+x3=M  x3=M-A2+x2=2M-A1-A2+x1=x1-C2 
  
　　对于第3个人，A3-x3+x4=M  x4=M-A3+x3=3M-A1-A2-A3+x1=x1-C3 
… 

　　对于第n个人，An-xn+x1=M。
  
　　我们希望所有xi的绝对值之和尽量小，即|x1|+|x1-C1|+|x1-C2|+…+|x1-Cn-1|要最小。注意到|x1-Ci|的几何意义是数轴上点x1到Ci的距离，所以问题变成了：给定数轴上的n个点，找出一个到它们的距离之和尽量小的点。不难猜到，这个最优的x1就是这些数的“中位数”（即排序以后位于中间的数），因此只需要排个序就可以了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;//n个人 
long long a[1000005];//每个人的初始金币数 
long long c[1000005];//递推数组 
long long tot;//记录总金币数 
long long m;//中位数 
long long x1;
long long ans;//转手金币数 
int main()
{
	while(scanf("%d",&n)!=EOF)//多组数据 
	{
		tot=0;
		ans=0;
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));//初始化 
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			tot+=a[i];//记录总金币数 
		} 
		m=tot/n;//每个人最后得到的金币数 
		for(int i=1;i<n;i++)
			c[i]=c[i-1]+a[i]-m;//递推 
		sort(c,c+n);//c数组从小到大排序，以便求中位数 
		x1=c[n/2];//x1是中位数 
		for(int i=0;i<n;i++)
			ans+=abs(x1-c[i]);//公式累加得答案 
		printf("%lld\n",ans);//输出 
	}
	return 0;
}
 
```
------------


---

## 作者：Su_Zipei (赞：1)

# 前方数学警告
## 分析:
搞了这么久终于碰到一个数学题了，这也是本蒟蒻做的第一个数学题吧，值得纪念。

第一次看见这题的时候，嗯，好像是个暴力。。。然后就打了一个暴力，发现样例过了？但自己造了组数据就有了点问题，我暴力的思路是由于一个人只能给左边或右边，于是把这两种情况都枚举一下，取最小值就好，但有可能跑一遍不能让整个数组都变成我想要的那个值，故我又加了一个bool表示有无把所有数字都变成那个数，这么写肯定T啊。

我:万一数据水呢？

数据:我不水。

所以交上去果断T掉了，我又想验证一下这么写可不可以，找某人代码过来对拍了一下，然后结果是我竟然把一个A掉的代码给拍出了错解？嗯，看来写个暴力还是有收获的，我其实很想把那个代码粘上来的，但它88行有点长~~我没存不小心弄丢了~~，来看一下正解吧。

首先我最开始发现的那个性质是没有问题的，即每个人只会被它周围的人影响，一旦他周围的人的转移硬币数确定了，那么这个人的转移硬币数也可求，于是受这一点启发，不妨设$x_i$表示第$i$个人给第$i-1$个人的硬币数，当$i==1$时，为给$n$的硬币数。由于最后要求所有人金币一样（共产主义），所以最后每个人的金币数量是确定的，即$M=tot/n$，也就是说每个人最后都是$M$，于是有$A_i+x_{i+1}-x_i=M$，就是原来有的加上得到的减去失去的等于最终的，光看这个式子，这啥也看不出来啊，所以继续观察这个式子，发现它跟周围的式子相加会出现一个神奇的结果，我们加一下看看。

$A_1+x_2-x_1=M$    1

$A_2+x_3-x_2=M$    2

$A_3+x_4-x_2=M$    3

1+2得$A_1+A_2+x_3-x_1=M*2$ -> $x_3=x_1-(A_1+A_2-M*2)$

1+2+3得$x_4=x_1-(A_1+A_2+A_3-M*3)$

……………

不难归纳得出$x_n=x_1-\sum_{i=1}^n(A_{i-1}+(i-1)*M)$
有这个式子我们就可以很简单~~困难~~的求出答案了，
设$B_i=\sum_{i=1}^n(A_{i-1}+(i-1)*M$，$B$数组可以由递推得到，那么
问题就简化成了在数组$B$中求一个数，使得剩余数到它的距离之和最小，答案是中位数，证明如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/kod3devn.png?x-oss-process=image/resize,m_lfit,h_00,w_500)

假设$a_1,a_2,a_3,a_4,a_5$有序，则$a_3$是中位数无疑，我们用线段来表示点与点之间的距离，可以看出蓝色框框内的线段是必不可少的，不管怎么划分都必须要有，如果这个点在$a_3$的左边，那么就会多出粉色的一截，在右边就会多出红色的一截，所以在中位数时是最小的。
那偶数呢？偶数不是有两个中位数吗？偶数时也画出一个这样的图，会发现当点在两个中位数之间距离都是一样的，并且是最小，所以为了方便，每次中位数都取$n+1>>1$就可以了。

中位数怎么找呢，排序一遍可以，但复杂度是$O(nlogn)$的，如果要使数组有序，那么肯定是要$sort$的，这里只求中位数，所以可以用$nth$_$element$，这个函数的用法是$nth$_$element(A+a,b,A+c)$，表示将数组A的区间$[a,c)$中第b大的数放在b位置上，不保证数组有序，但比这个数大的都在它前边，比它小的在它后边，平均时间复杂度$O(n)$。
```
#include<iostream>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e6+10;
ll a[N],b[N];
int main(){
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n){
        ll tot=0;
        for(int i=1;i<=n;i++)
            cin>>a[i],tot+=a[i],b[i]=0;
        tot/=n;
        for(int i=2;i<=n;i++)
            b[i]=b[i-1]+a[i]-tot;
        int mid=n+1>>1;
        nth_element(b+1,b+mid,b+n+1);
        ll temp=b[mid],res=0;
        for(int i=1;i<=n;i++)
            res+=abs(temp-b[i]);
        cout<<res<<'\n';
    }
}

```
tips:cout<<endl的确比cout<<'\n'慢一点。

---

## 作者：小元勋 (赞：1)

- 环形的均分纸牌

- 我们可以先得出最后每个人的金币数为金币总数除以$N$。设$M$为最后每个人的金币数。

- 设$X_{i}$表示$i$将给左边那个人几个金币，如果$X_{i}<0$，则表示左边的人要倒拿金币出来。

- 假设每个人初始有金币数$A_{i}$。对于第$i$个人，他要给他左边的人拿$X_{i}$金币，而他右边的人又将给他拿$X_{i+1}$的金币，我们可以得到一个等式：

$$A_{i}-X_{i}+X_{i+1}=M$$

同理，我们可以得到一个方程组:

$$A_{1}-X_{1}+X_{2}=M$$

$$A_{2}-X_{2}+X_{3}=M$$

$$A_{3}-X_{3}+X_{4}=M$$

$$......$$

$$A_{i}-X_{i}+X_{i+1}=M$$

但我们并不能直接解方程组，因为最后一个等式可以由前面的等式推出来。

- 我们可以尝试用$X_{1}$表示出其他的$X_{i}$，本题就变成了单变量的极值问题。

定义: $C_{i}=A_{i}-M$

$$X_{2}=X_{1}-C_{1}$$

$$X_{3}=M-A_{2}+X_{2}=X_{1}-C_{2}$$

$$......$$

$$X_{i}=X_{1}-C_{i}$$

同时我们发现：

$$C_{i}=C_{i-1}+A_{i}-M$$

- 我们希望所有的$\sum{|C_{i}|}$最小，即

$$|X_{1}|+|X_{1}-C_{1}|+|X_{1}-C{2}|+...+|X_{1}-C_{n-1}|$$

最小。

注意$|X_{i}-C_{i}|$的几何意义为点$X_{i}$到$C_{i}$的距离,所以问题变成了：给定数轴上的$n$个点，找出一个点到他们的距离最小，显然最优的$X_{1}$为这些数的中位数。

- 递推出$C_{i}$数组，排序，求出中位数，再计算距离和就是答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000050

int n;
long long A[maxn],C[maxn];

inline long long read_() {
	long long x_=0,f_=1;char c_=getchar();
	while(c_<'0'||c_>'9') {if(c_=='-') f_=-1;c_=getchar();}
	while(c_>='0'&&c_<='9') {x_=(x_<<1)+(x_<<3)+c_-'0';c_=getchar();}
	return x_*f_;
}

void readda_() {
	while(scanf("%d",&n)!=EOF) {
		if(!n) {printf("0\n");continue;}
		long long M = 0;
		for(int i=1;i<=n;++i) {
			A[i] = read_();
			M += A[i];
		}
		M /= n;
		for(int i=1;i<=n;++i)
		C[i] = C[i-1] + A[i] - M;
		sort(C+1,C+1+n);
		long long x = C[n/2+1],ans = 0;
		for(int i=1;i<=n;++i)
		ans += abs(x-C[i]);
		printf("%lld\n",ans);
	}
}

int main() {
//	freopen("a.txt","r",stdin);
	//freopen("ac.txt","w",stdout);
	readda_();
	return 0;
}
```



---

## 作者：void_zxh (赞：1)

这题是一个经典的环形均分纸牌问题    
设每个人手中原本有A[i]个金币
我们可以把所有的移动简化为：  
  	第i个人给第i-1个人x[i]个金币(x[i]可以为负)
    
显然最后每个人手中的金币数为tot/n (tot为A[1]+...+A[n])

设M=tot/n

那么显然有下列等式

	A[1]-x[1]+x[2]=M
    A[2]-x[2]+x[3]=M
    ......
    A[n]-x[n]+x[1]=M
将x[i]全部代换为x[1]可得

	x[i]=(i-1)M-(A[1]+...+A[i-1])+x[1]
    
令c[i]=(A[1]+...+A[i-1])-(i-1)M 
	其中c[1]=0
 
那么答案就转换为

Abs(x[1]-c[1])+Abs(x[2]-c[2])+...+Abs(x[n]-c[n])

这可以转换为数轴上点的距离，显然x[1]取c[1]、...、c[n]的中位数时

答案最小

那么这题就解完了

附上我的程序：
```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <map>
#include <queue> 
using namespace std;
#define ll long long
#define N 1000005

inline ll read()
{
	ll x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-48;c=getchar();}
	return x*f;
}

ll n;
ll a[1000005],c[1000005];

ll Abs(ll x)
{
	return x<0?-x:x;
}

int main()
{
	int i;
	ll mid,ui,ans,tot;
	while(~scanf("%lld",&n))
	{
		tot=0; 
		for(i=1;i<=n;i++)
		{
			a[i]=read();
			tot+=a[i];
		}
		mid=tot/n;
		c[1]=0;
		for(i=2;i<=n;i++)
			c[i]=c[i-1]+a[i]-mid;
		sort(c+1,c+n+1);
		ui=c[n/2]; ans=0;
		for(i=1;i<=n;i++)
			ans+=Abs(ui-c[i]);
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：zzh_han (赞：0)

## 题目含义

现在有 $n$ 个人现在每个人手上都有 $f[i]$ 枚金币，现在要平分这些金币，每个人可以把自己的金币分给左右两边的人，每分一枚金币就要增加1的代价。现在问我们最少花费多少的代价来平分这些金币 

## 做法

我们假设现在是 $a$ 给 $b$   $x1$ 枚金币每个人应平均分的 $m$ 枚金币那就可以得到方程 $b$ = | $a$ - ( $x1$ - $m$)|

 一位一位写出后我们可以发现这是一个换最后得到的就是 $ans[i]=$$\sum\limits_{i=1}^nf_j$-i*M

得到这个公式后我们就可以利用一个前缀合优化来求出答案

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
long long a[1000010],f[1000010],sum,ans;
int n,i;
int main()
{
	while(~scanf("%d",&n)) //多组数据
	{
		ans=0;
		sum=0;
		for(i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			sum+=a[i];//前缀和
		}
		sum/=n;
		for(i=1;i<=n;i++) a
            [i]-=sum;
		for(i=1;i<=n;i++) 
            f[i]=f[i-1]+a[i];
		sort(f+1,f+n+1);
		for(i=1;i<=n;i++) 
            ans+=abs(f[i]-f[(n+1)/2]);
		cout<<ans<<endl;
	}
	return 0;
}
```
[这道题](https://www.luogu.com.cn/problem/P2512)和这个一模一样


---

## 作者：hzoi_liuchang (赞：0)

一句话题意：有n个人围成一圈，每个人有一定数量的金币，每个人可以给和他相邻的人一些金币，求挪动的最少金币使他们平分金币
 分析
对于每一个人，他的金币数只能从他前面那一个人或者后面那一个人那里得到

同样地，他的金币也只能传递给前面的那个人或者后面的那个人

但是无论怎么传递，他们最终剩余的金币数是相同的，而且这个金币数我们可以直接算出来

我们设最终每个人都有的金币数为m，人数为n

在读入时，我们开一个变量ans记录n个人的金币数之和，那么m=ans/n

我们设b[i]为第i个人给第i-1个人的金币数，需要注意的是，因为题目中说n个人围成了一个环，所以b[1]为第1个人给第n个人的金币数

（注意，这里的b数组可正可负，如果是正数，表明第i个人给了第i-1个人金币，如果为负数，表明第i-1个人给了第i个人金币，如果为0，则两个人不发生金币交换）

对于第一个人，他给了第n个人b[1]个金币，同时，第二个人又给了他b[2]个金币，他的初始金币数为a[1]，最终金币数为m

所以我们可以列出式子 m=a[1]-b[1]+b[2]   -------- 1式

同样，对于第二个人 m=a[2]-b[2]+b[3]     -------- 2式

……

对于第n个人：m=a[n]-b[n]+b[1]     -------- n式

所以m=a[n]-b[n]+b[n+1]

为了找规律方便，我们引入一个数组c，令c[1]=a[1]-m，c[2]=a[1]+a[2]-m*2,c[n]=a[1]+a[2]+...+a[n]-m*n

通式为c[0]=0,c[i]=a[i]+c[i-1]-m;

对于第二个人（由1式得）：b[2]=m-a[1]+b[1]=b[1]-c[1];

对于第三个人（由2式得）：b[3]=m-a[2]+b[2]=m-a[2]+m-a[1]+b[1](将b[2]=m-a[1]+b[1]代入)=2m-a[1]-a[2]+b[1]=b[1]-c[2];

对于第四个人（由3式得）：b[4]=m-a[3]+b[3]=3m-a[1]-a[2]-a[3]+b[1]=b[1]-c[3]

……

我们希望所有的b[i]的绝对值之和尽量小，也就是使

|b[1]-c[0]|+|b[1]-c[1]|+|b[1]-c[2]|+|b[1]-c[3]|+……+|b[1]-c[n-1]|最小

对于任意两个数a、b，我们知道|a-b|的绝对值表示它们在数轴上的距离

所以原式我们可以看成坐标为b[1]的点到以上所有点距离之和的最小值

这时，就有一个结论，给定数轴上的n个点，在数轴上所有点中，中位数离所有顶点的距离之和最小

下面我们给出简单的证明

如果n为奇数，我们举一个5的例子
![](https://cdn.luogu.com.cn/upload/image_hosting/alacfzn7.png)
根据结论，这时c2点为最优决策

我们用反证法，如果我们将决策点向左移动一个单位,那么该点到c0、c1的距离分别减小1，到c2、c3、c4的距离分别增加1，总的距离增加了1，显然不是最优决策

如果我们将决策点向右移动一个单位,那么该点到c0、c1、c2的距离分别增加1，到c3、c4的距离分别减小1，总的距离增加了1，显然不是最优决策

所以中位数最优

同样的，如果n为偶数，我们只需要在[c[n/2-1]，c[n/2]]这个区间内任取一个数就是最优决策，证明同上

不要忘了排一下序

所以，最终我们要将b[1]的值赋值成c[n/2]

而c数组我们提前处理得到，所以问题就迎刃而解了

到这里，其实b数组并没有什么用，只是在证明过程中出现，所以我们只要定义一个整形变量存储b[1]就可以了

记得要开long long哦

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=1e6+5;
typedef long long ll;//注意要开long long
ll a[maxn],c[maxn];
ll n;
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(c,0,sizeof(c));
        memset(a,0,sizeof(a));
        ll tot=0;
        for(ll i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            tot+=a[i];
        }
        ll pj=tot/n;//求出每个人最终拥有的金币数
        for(ll i=1;i<n;i++){
            c[i]=a[i]+c[i-1]-pj;
        }//预处理c数组
        sort(c,c+n);//排序，不要忘了
        ll ans=c[n/2];
        ll cnt=0;
        for(ll i=0;i<n;i++){
            cnt+=abs(ans-c[i]);
        }
        printf("%lld\n",cnt);
    }
    return 0;
}

不要直接复制哦
```


---

## 作者：noall (赞：0)

### UVA11729 Commando War

我真是烦这种数学题啊，~~让人头秃~~。

这是道类似[P2512 【HAOI2008】糖果传递](https://loj.ac/problem/10010)的题，思想好像是叫做纸牌均分问题？？#(不确定)


#### 思路

这道题有两个需要思考的点。

假设有$\mathtt{1,2,3,4}$这$4$个人。

如果1号给2号3枚金币，然后2号再给1号5枚金币。可以看作是1号1枚金币也没有给2号，而2号给了1号2枚金币。

我们可以用$x_2$来表示**2号给了1号$x_2$枚金币**，当然，如果$x_2<0$，那么实际上1号给了2号$-x_2$枚金币。

由于是环形，所以$x_1$表示1号给4号的金币数。

我们已知人数$n$和总金币数$tot$，那么，我们可以根据$tot/n$得到$M$，即每人最终所拥有的金币数。

假设编号为$i$的人初始有$A_i$枚金币。对于1号来说，他给了4号$x_1$枚金币，所以剩下$A_1-x_1$枚硬币，而2号又给1号$x_2$枚金币，所以1号的金币数最终为$A_1-x_1+x_2$枚。

由此，我们可以得到方程$A_1-x_1+x_2=M$。

同理，对于第2个人，我们可以得到$A_2-x_2+x_3=M$。

最终，我们可以得到n个方程。

我们可以用$x_1$表示出其他的$x_i$。

对于第1个人，$A_1-x_1+x_2=M \Longrightarrow x_2=M-A_1+x_1=x_1-C_1$（定义$C_1=A_1-M$）

对于第2个人，$A_2-x_2+x_3=M \Longrightarrow x_3=M-A_2+x_2=2M-A_1-A_2+x_1=x_1-C_2$（定义$C_2=A_1+A_2-2M$）

对于第3个人，$A_3-x_3+x_4=M \Longrightarrow x_4=M-A_3+x_3=3M-A_1-A_2-A_3+x_1=x_1-C_3$（定义$C_3=A_1+A_2+A_3-3M$，以此类推）

……

###### 顺便一说

可以看出，$C_i$是可以推出来的。

即当$i=0$时，$C_0=0$。递推式为$C_i=C_{i-1}+A_i-M$。

根据题目的要求，我们希望所有的$x_i$的绝对值之和最小，也就是$|x_1|+|x_1-C_1|+|x_1-C_2|+|x_1-C_3|+...+|x_1-C_{n-1}|$。

那么，我们的初一数学知识可以告诉我们，$|x_1-C_1|$的几何意义其实就是在数轴上，$x_1$到$C_1$的距离。

这时，问题变成了：给定数轴上$n$个点，找出一个到他们的距离之和尽量小的点。

也就是，中位数。

~~证明是不可能证明的，这辈子是不可能证明的。~~

那么就easy了。

#### code

放上我这蒟蒻的代码。

```c++
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e6+7;

#define int long long
#define intt int
#define mian main()
#define in inline
#define re register

in int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n,a[maxn],c[maxn],tot,m;

mian{
	while(scanf("%lld",&n)==1){//读入量大
        tot=0;
		for(re int i=1;i<=n;i++) a[i]=read(),tot+=a[i];
		m=tot/n;c[0]=0;//算M；初始化C0
		for(re int i=1;i<=n;i++) c[i]=c[i-1]+a[i]-m;//递推Ci
		sort(c+1,c+1+n);
		int x1=c[(n+1)/2],ans=0;//中位数
		for(re int i=1;i<=n;i++) ans+=abs(x1-c[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

最后要强烈安利一波自己的博客：[更好的阅读体验](https://www.langlangago.xyz/index.php/archives/51/)

---

