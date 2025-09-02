# Intense Heat

## 题目描述

给定一个含有 $n$ 个数的数组，以及 $k$，求所有长度大于等于 $k$ 的子串的平均数最大值。

## 样例 #1

### 输入

```
4 3
3 4 1 2
```

### 输出

```
2.666666666666667
```

# 题解

## 作者：Huhu12346 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1003C)

首先，我们得知道什么是前缀和.

简单来说：我们有一个数组 $x$ 和它的前缀和数组 $y$，他们满足以下公式。

$y_0 = x_0,$

$y_1 = x_0 + x_1,$

$y_2 = x_0 + x_1 + x_2,$

即 $y_n = x_1 + x_2 + \dots + x_n = \sum\limits_{i=1}^{n}x_i$。

那么前缀和能干吗？

对于一个给定的数组 $nums$，我们额外开辟一个前缀和数组进行预处理。

那么这题如何做呢？

其实就是前缀和的和然后暴力枚举长度。


下面奉上代码 QWQ：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double sum[5001],a[5001];
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        double dt=0;
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++)
	{            
            scanf("%lf",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        for(int i=m;i<=n;i++)
	{
            for(int j=1;j+i-1<=n;j++)
	    {
                dt=max(dt,(sum[i+j-1]-sum[j-1])*1.0/i);
            }
        }
        printf("%.10f\n",dt);
    }
}
```





---

## 作者：GossWandering (赞：3)

这题其实不用什么高深的算法，前缀和就可以搞定了。

## Step 1 前缀和是什么？

假设你已经计算出来了$\sum\limits_{i=x}^{y}a_i$，你如果还要算$\sum\limits_{i=x}^{y+1}a_i$，该怎么办呢？大家肯定都能想到朴素的算法：一个一个累加。

但是你已经算出来了$\sum\limits_{i=x}^{y}a_i$呀！你只需要再加上一个$a_{y+1}$就可以了。再一个一个累加，何苦呢？

于是我们引入前缀和的概念：

$\boxed{Sum_x=\sum\limits_{i=1}^{x}a_i}$

## Step 2 前缀和能干什么？

比如说你要求$\sum\limits_{i=x}^{y}a_i$。

$\quad\sum\limits_{i=x}^{y}a_i$

$=\sum\limits_{i=1}^{y}a_i-\sum\limits_{i=1}^{x-1}a_i$

$=Sum_y-Sum_{x-1}$

复杂度$O(1)$，而朴素算法是$O(y\!-\!x\!+\!1)$这大大优化了我们的程序！

## Step 3 前缀和怎么求？

$∵\sum\limits_{i-1}^xa_i=\sum\limits_{i-1}^{x-1}a_i+a_x$

$∴sum(x)\!=\!sum(x\!-\!1)\!+\!a_x$

## Step 4 所以这道题究竟怎么做？

- 先$O(n^2)$枚举子连续段首和段尾。
- 运用我们的神器——前缀和$O(1)$求出段和。
- 更新最大值：
- 程序：
```
#include<bits/stdc++.h>
#define ll long long
#define landingyu work();
#define AK return
#define IOI 0;
#define inf 0x3f3f3f3f
#define eps 0.00001
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}//快读，常数优化大佬中的大佬，不会的赶紧学一下吧！
using namespace std;
double a[5010],sum[5010];
double maxx=-0x3f3f3f3f;
void work(){
    int n=read(),k=read();//输入
    for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];//前缀和
    for(int i=1;i<=n;i++)//枚举起点
        for(int j=i+k-1;j<=n;j++)//枚举终点
		    maxx=max(maxx,(sum[j]-sum[i-1])/(j-i+1));//更新最大值
	printf("%.8lf",maxx);//输出
}
int main(){landingyu AK IOI}//膜拜大神，具体请看define
```

[博客](https://238000.blog.luogu.org/wen-zhang-zong-hui)食用更佳！！！

$Update2020/4/29:$加入“Step 3 前缀和怎么求？”部分

---

## 作者：千秋星辰 (赞：2)

**首先，这是一道暴力题。**

### 思路

1. ~~概括题意，但是题意已经够简练了。~~ 注意到符合条件的子串长度 $ len\ge k $。
2. 如果是长度 $ len=k $ 的话，显然这就是[P1886](https://www.luogu.com.cn/problem/P1886)的一部分，于是很简单地想到用类似的思路来实现。
3. 首先，枚举选中的区间的**左端点** i，这里复杂度是 $ O(n) $。
4. 然后，在左端点固定的情况下，选择最短的长度 k，计算这一段的和。
5. 最后，一边统计着子串的和一边扩大子串长度，也就是右移右端点。这里相当于指针从左端点 i 一只移到 n，复杂度可看做 $ O(n) $。

按照以上思路，**总复杂度** $ O(n^2) $，看到数据范围中 $ 1 \le n \le 5000$，完全不会  _TLE_。
### AC code
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define forever() while(true)
#define out(x) write(x),putchar(' ')
#define writen(x) write(x),putchar('\n')

namespace IO
{
	#define gc getchar
	#define pc putchar
	inline int read()
	{
		int x=0,y=1;char c=gc();
		while(c<'0'||c>'9'){if(c=='-') y=-y;c=gc();}
		while(c>='0'&&c<='9'){x=x*10+(c^'0');c=gc();}
		return x*y;
	}
	void write(int x)
	{
		if(x<0) x=-x,pc('-');
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	#undef gc
	#undef pc
}

using namespace std;
using namespace IO;
int n,k,a[5005];
double ans;

signed main()
{
	n=read(),k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i)
	{
		double res=0,tot=0;
		int p=i;
		while(tot<k-1&&p<=n)
		{
			res+=a[p];
			++tot;
			++p;
		}
		while(p<=n)
		{
			res+=a[p];
			++tot;
			ans=max(ans,res/tot);
			++p;
		}
	}
	cout<<fixed<<setprecision(10)<<ans;
	return (0^0);
}
```

---

## 作者：kimidonatsu (赞：1)

# CF1003C Intense Heat 题解

## 题意简述

* 给定一个长度为 $n$ 的序列。
* 求所有长度在 $k$ 及以上连续子串的最大平均数。

## 思路分析

明显的求和题，使用 **前缀和** 进行优化。

何谓前缀和？简单来说，如果对序列 $a$ 中的元素进行求和到第 $n$ 个为止，可以这样进行比较：

平时我们这样进行求和（即暴力枚举）：
$$
a_1 + a_2 + a_3 + \cdots + a_n = \sum_{i = 1}^{n}a_i
$$

前缀和，其实就是这样：新建一个序列 $b$，其中， $b_i = \sum_{j = 1}^{n} a_j$，据此，查找到第 $n$ 位的和，其实就是 $b_n$ 的值，步骤可以简化为：
$$
a_1 + a_2 + a_3 + \cdots + a_n = b_n
$$

已知 $a_1 \sim a_n$ 的和，就只要暴力枚举序列的长度即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 5e5 + 50;

int n, k;
double ans;
double a[N], p[N];

int main() {
    scanf("%d %d", &n, &k);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &a[i]);
        p[i] = p[i - 1] + a[i];
    }

    for (int i = 1; i <= n - k + 1; i++) {
        for (int j = i + k - 1; j <= n; j++)
            ans = max(ans, ((p[j] - p[i - 1]) * 1.0 / (j - i + 1)));	// 求平均值与最大值
    }
    printf("%.15lf\n", ans);
    return 0;
}

```

代码小注：
* 格式转换有坑。
* 精度保留 $6$ 位即可，也可使用 `iomanip` 库中的 `setprecision`。


---

## 作者：FTWIN (赞：1)

前缀和，这个不用说了吧...

题目翻译：求长度在k级以上的连续段的最大平均数。

解法：以前缀和暴力求平均数，枚举坐标。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long double s,maxv,n,k,a[10000];
int main(){
	maxv=0;
	memset(a,0,sizeof(a));
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
	for(int i=k;i<=n;i++){
		for(int j=i;j<=n;j++) maxv=max(maxv,((a[j]-a[j-i])*1.0/i));
	}
	cout<<setprecision(15)<<maxv<<endl;
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
给定一个长度为 $n$ 的数列，求数列中所有长度 $\geqslant k$ 的区间的最大平均值。

**数据范围：$1\leqslant k,n,a_i\leqslant 5000$。**
## Solution
我们通过预处理前缀和之后，再直接暴力枚举所有长度 $\geqslant k$ 的区间的平均值，取其最大值即可。
## Code
```cpp
int k, n, a[5007], s[5007];
double ans;

int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(n), getint(k);
	_for(i, 1, n) {getint(a[i]); s[i] = s[i - 1] + a[i];}
	_for(j, k, n)
		_for(i, 1, n - j + 1)
			ans = max(ans, (s[i + j - 1] - s[i - 1]) * 1.0 / j);
	printf("%.12lf", ans);
	return 0;
}
```

---

## 作者：s_c_lmlm_L (赞：0)

这道题数据范围不算很大，所以并不用多么恐怖的算法，其实幼稚园都知道的[前缀和](https://baijiahao.baidu.com/s?id=1724991165268207416&wfr=spider&for=pc)就欧克啦。
（题目：普及/提高-，实际：普及-）

------------

$Step1$ 制作前缀和，记录每个 $[l,r]$ 的和
$$[l,r]=S_r-S_{l-1}$$
 $Step2$ 每次枚举左端点 $l$ ,再枚举右端点 $r$ ，使区间 $[l,r]$ 平均值最大
 $$\max(maxn,(s[r]-s[l-1])/(r-l+1))$$

时间复杂度为 $O(n^2)$
           
## $AC$ $code$
```
#include<bits/stdc++.h>//万能头
using namespace std;
long long n,k,a[N],s[N];//定义变量，a为原数组
int main() {
	cin>>n>>k;
	for(int i=1;i<=n;i++) 
    {
		cin>>a[i];
		s[i]=s[i-1]+a[i];//建立数组a的前缀和
	}
	for(int i=1;i<=n-k+1;i++) 
		for(int j=i+k-1;j<=n;j++) 
        	maxn=max(maxn,(s[j]-s[i-1])*1.0/(j-i+1));//求平均值的最大值
	cout<<fixed<<setprecision(6)<<maxn;
    //四舍五入到第6位，如果不用万能头文件的话需要用到<iomanip>
}
```



---

## 作者：hanyipu1414 (赞：0)

# 一、思路
用前缀和记录 $1$ 到 $r$ （右端点）所有数的和，之后用 $l$ （左端点）和 $r$ 来暴力就行了，具体的看代码。
# 二、Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=5114;
int n,k;
double ans=-1.0,a[NR],sum[NR];
int main()
{
	sum[0]=0;//初始化
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];//前缀和
	}
	for(int l=1;l<=n-k+1;l++)//暴力过程
	    for(int r=l+k-1;r<=n;r++)//枚举区间[l,r]的区间平均值，l与r的距离至少为k
	        ans=max(ans,(sum[r]-sum[l-1])/(r-l+1));//区间[l,r]的区间平均值
	printf("%.10lf",ans);//输出
	return 0;
}
```


---

## 作者：ciwomuli (赞：0)

题目大意为在一个序列中找长度大于k的序列中平均值最大的

我们用dp[i][j]表示序列中i与i的前j个（包括i）的和

这很明显可以用递推求出

在递推时当j>=k时顺便更新ans就好了

上代码

```
#include <iostream>
#include <iomanip>
using namespace std;
double dp[5005][5005];
long double ans = 0;
int main(){
    int n,tk;
    cin >> n>>tk;
    for (int i=1;i<=n;i++){
        cin >> dp[i][1];
    }
    for (int i=1;i<=n;i++){
        for (int k = 1;i-k>=-1;k++){
            dp[i][k] = dp[i - 1][k - 1]  + dp[i][1];
            if(k>=tk && ((long double)dp[i][k]/k)>ans)
                ans = (long double)dp[i][k]/k;
        }
    }
    cout <<setprecision(10)<<ans;
}
```

---

