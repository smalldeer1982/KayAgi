# Simple Skewness

## 题目描述

Define the simple skewness of a collection of numbers to be the collection's mean minus its median. You are given a list of $ n $ (not necessarily distinct) integers. Find the non-empty subset (with repetition) with the maximum simple skewness.

The mean of a collection is the average of its elements. The median of a collection is its middle element when all of its elements are sorted, or the average of its two middle elements if it has even size.

## 说明/提示

In the first case, the optimal subset is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626E/0b9550a7a9f20f7b56fdc9073fe6e2b4a2093ee5.png), which has mean $ 5 $ , median $ 2 $ , and simple skewness of $ 5-2=3 $ .

In the second case, the optimal subset is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626E/d0a3a979416d48c43b3c8a042caaf404373f99fe.png). Note that repetition is allowed.

In the last case, any subset has the same median and mean, so all have simple skewness of $ 0 $ .

## 样例 #1

### 输入

```
4
1 2 3 12
```

### 输出

```
3
1 2 12 
```

## 样例 #2

### 输入

```
4
1 1 2 2
```

### 输出

```
3
1 1 2 
```

## 样例 #3

### 输入

```
2
1 2
```

### 输出

```
2
1 2
```

# 题解

## 作者：TonyYin (赞：7)

## 题意

给定 $n$ 个非负整数，选一个子集，使得子集的平均值减去中位数最大。

求这个最大值。

## $\rm{Subtask}$ $1-\mathcal{O}(n^2)$

因为需要考虑中位数，容易想到按照子集大小的奇偶性分类讨论。

#### 子集大小为奇数

先来考虑奇数的情况。

容易想到 $\mathcal{O}(n)$ 枚举中位数。

![](https://pic.tonyyin.top/2021/04/05/9b79d51da9e7a.png)

如上图，对数列按照升序排序。选定中位数后，我们每次从中位数左侧添加一个点，再从中位数右侧添加一个点。又因为我们想要子集的**平均值最大**，所以**贪心地，每次分别从两侧取一个最大的数**，也就是取最靠右的点，直到有一个区间被取完。

比如上图中，$(4, 10)$，$(3, 9)$，$(2, 8)$ 两两为一组，每次分别被取出。

于是对于每个中位数，只需要 $\mathcal{O}(n)$ **枚举两侧添加点的个数**，就可以确定出选取的情况，求出平均值与中位数的差。

由于方案已经确定，直接输出即可。

这样可以得到整体复杂度为 $\mathcal{O}(n^2)$ 的算法，期望得分未知。

#### 子集大小为偶数

##### 结论

对于大小为偶数的子集，观察可以得到结论：**对于任意大小为偶数的子集，一定存在大小为奇数的子集比其更优**，下面进行证明。

##### 分析

按照上面的贪心策略任取一个大小为奇数的子集，将其升序排序，设为 $\{a_1, a_2, \cdots a_{2n-1}\}$.

现在向子集中添加一个数，使其大小变为偶数。根据上面提到的**贪心策略**，新加入的数 $x$ 有以下两种情况：

1. $x$ 在 $a_1$ 左侧，即 $x\leq a_1$，
2. 紧邻中位数右侧，即 $a_n\leq x\leq a_{n+1}$.

在上面的图里，可以形象地看到，$x$ 的第一种情况是选择 $1$，第二种情况是在 $6, 7$ 中选一个。

第一种情况，显然不会使答案变大，因为 $x$ 对平均值的影响太大了。

对于第二种情况，下面进行详细证明。

##### 证明

为了方便，我们把加入 $x$ 后的数列重新升序排序，不妨设为 $\{b_1, b_2, \cdots b_{2n}\}$.

加入 $x$ 前的答案为：
$$
A=\frac{\sum_{i=1}^{2n}b_i-b_{n+1}}{2n-1}-b_{n}
$$
加入后的答案为： 
$$
B=\frac{\sum_{i=1}^{2n}b_i}{2n}-\frac{b_{n} + b_{n + 1}}{2}
$$


两者作差并化简后得到：
$$
A-B=\frac{\sum_{i=1}^{2n}b_i}{2n(2n-1)}+\frac{b_{n+1}-b_n}{2}-\frac{b_{n+1}}{2n-1}
$$
又因为 $B\geq 0$，所以：
$$
\frac{\sum_{i=1}^{2n}b_i}{2n}\geq \frac{b_n+b_{n+1}}{2}
$$
即：
$$
\frac{\sum_{i=1}^{2n}b_i}{2n(2n-1)}\geq \frac{b_n+b_{n+1}}{2(2n-1)}
$$
代入 $A-B$ 中得到：
$$
\begin{aligned}
A-B&\geq \frac{b_n+b_{n+1}}{2(2n-1)}+\frac{b_{n+1}-b_n}{2}-\frac{b_{n+1}}{2n-1}\\
&=\frac{b_n+b_{n+1}+(2n-1)(b_{n+1}-b_n)-2b_{n+1}}{2(2n-1)}\\
&=\frac{b_n+b_{n+1}+2n\cdot b_{n+1}-2n\cdot b_n-b_{n+1}+b_n-2b_{n+1}}{2(2n-1)}\\
&=\frac{(n-1)(b_{n+1}-b_n)}{(2n-1)}\geq 0
\end{aligned}
$$
于是我们证明了：加入 $x$ 前的答案一定不小于加入 $x$ 后的答案，也就是：**对于任意大小为偶数的子集，一定存在大小为奇数的子集比其更优**。

#### $\mathcal{O}(n^2)$ 代码

以下代码输出的是：**平均值与中位数的差**的最大值

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
const int inf = 0x3f3f3f3f3f3f3f3f;
inline int read() {}//快读
int n, a[MAXN], sum[MAXN];
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	double ans = (-1.0) * inf;
	for(int i = 1; i <= n; i++) {//枚举中位数，两侧同时添加点，尽可能靠右
        double mmax = (double)(a[i]);//只取中位数
        for(int j = 1; j <= min(i - 1, n - i); j++) {//subtask1 暴力枚举两侧加2*j个点
            int add_l = sum[i - 1] - sum[i - j - 1];
            int add_r = sum[n] - sum[n - j];
            mmax = max(mmax, (double)(add_l + add_r + a[i]) / (double)(2 * j + 1));
        }
        ans = max(ans, mmax - (double)(a[i]));
	}
	printf("%.2lf\n", ans);
	return 0;
}
```



## $\rm{Subtask}$ $2-\mathcal{O}(n\log n)$

考虑如何把时间复杂度优化到 $\mathcal{O}(n\log n)$ 级别。

$\mathcal{O}(n^2)$ 的做法中，我们先枚举中位数 $mid$，再枚举两侧添加的元素个数 $len$.

在此基础上，设第 $i$ 次添加的两个元素**下标**分别为 $x_i$ 和 $y_i$. 

当确定中位数时，答案只与平均值有关，考虑计算添加 $(x_i, y_i)$ 对平均值的贡献。

贡献，也就是添加这两个数之后，**平均值的变化量**，若平均值变大，则贡献为正，反之为负。

显然地，**随着 $i$ 的增长**，$a_{x_i}+a_{y_i}$ 会持续下降，**对平均值的贡献也会越来越少**。

我们最后一次选取的两个元素 $x_{len}, y_{len}$，必定满足贡献大于 $0$，并且是最接近 $0$ 的。

因此我们可以通过**二分**，找到贡献紧邻最接近0的数。

这样就确定了选择哪些数，前缀和计算答案即可。

具体实现时，我们不需要准确地计算出每两个元素的贡献。若**加入两个元素后的平均值大于原数列的平均值，则贡献为正**，否则贡献为负。这部分需要利用前缀和求出数列平均值。

对于输出方案，已经确定，直接输出即可。

这样就得到了 $\mathcal{O}(n\log n)$ 的算法，期望得分 $\rm{100pts}$.

## $\rm{100pts}$ 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
const int inf = 0x3f3f3f3f3f3f3f3f;
inline int read() {
	int ret = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch <= '9' && ch >= '0') {
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	return ret;
}
int n;
int a[MAXN], sum[MAXN];
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	double ans = (-1.0) * inf; int ans_cnt = 0, ans_mid = 0;
	for(int i = 1; i <= n; i++) {//枚举中位数，两侧同时添加点，尽可能靠右
		int l = 1, r = min(i - 1, n - i), mid;
		double mmax = (double)(a[i]); int cnt = 0;
		while(l <= r) {
			mid = (l + r) >> 1;
			int sum1 = sum[i - 1] - sum[i - mid] + sum[n] - sum[n - mid + 1];
            //j = mid - 1，即加入前的平均值
			int sum2 = sum[i - 1] - sum[i - mid - 1] + sum[n] - sum[n - mid];
            //j = mid，加入两个元素后的平均值
			if((double)(sum1 + a[i]) / (double)(2 * mid - 1) < (double)(sum2 + a[i]) / (double)(2 * mid + 1)) {
				if((double)(sum2 + a[i]) / (double)(2 * mid + 1) > mmax) {
					mmax = (double)(sum2 + a[i]) / (double)(2 * mid + 1);
					cnt = mid;
				}
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		if(mmax - double(a[i]) > ans) {
			ans = mmax - (double)(a[i]);
			ans_cnt = cnt;
			ans_mid = i;
		}
	}
	cout << ans_cnt * 2 + 1 << endl;
	for(int i = ans_mid - ans_cnt; i <= ans_mid; i++) cout << a[i] << " ";
	for(int i = n - ans_cnt + 1; i <= n; i++) cout << a[i] << " ";
	return 0;
}```



---

## 作者：hanzhongtlx (赞：2)

我们首先发现当中位数确定的时候，选取尽量大的数构成的集合平均数越大，差值也就越大。  

然后我们假设现在有奇数个数时，加入一个数，不会使得这个差值变大（这个很容易发现，不太明白可以手玩）。  

于是中位数只有 $n$ 个取值了，于是我们枚举每一个数作为中位数，找到每一种情况时两边选多少会有最大差值。  

这个差值是个单峰的函数，类似二次函数（开口向下）。

考虑二分。  

这时候我们算出前后各取 $mid$ 个数的差值，和各取 $mid+1$ 个数的差值，从而可以轻易判断此时函数的单调性。  

然后根据函数的知识向左，向右取就很容易判断了。   

最后注意特判 $n\leq2$ 的情况与无论如何差值总不大于 $0$ 的情况。  

```
#include"iostream"
#include"cstdio"
#include"cmath"
#include"algorithm"
using namespace std;

#define read(x) scanf("%d",&x)
#define MAXN 200005
#define db double
#define ll long long

int n;
int a[MAXN];
ll sum[MAXN];
int maxmid,maxl;
db maxn=0;

int main()
{
    read(n);
    for(int i=1;i<=n;i++) read(a[i]);
    sort(a+1,a+n+1),sum[0]=0;
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(ll)a[i];
    if(n<=2)
    {
        printf("%d\n",n);
        for(int i=1;i<=n;i++) printf("%d ",a[i]);
        return 0;
    }
    for(int i=2;i<=n-1;i++)
    {
        int lo=min(i-1,n-i);
        int mid,l=1,r=lo;
        db now1,now2;
        while(l<r)
        {
            mid=(l+r)>>1;
            now1=((db)(sum[i]-sum[i-mid-1]+sum[n]-sum[n-mid]))/(2*mid+1);
            if(mid<lo) now2=((db)(sum[i]-sum[i-mid-2]+sum[n]-sum[n-mid-1]))/(2*mid+3);
            else now2=-1;
            if(now1<now2) l=mid+1;
            else r=mid;
        }
        mid=(l+r)>>1;
        db now=((db)(sum[i]-sum[i-mid-1]+sum[n]-sum[n-mid]))/(2*mid+1);     
        if(now-(db)a[i]>maxn)
        {
            maxn=now-(db)a[i];
            maxmid=i;
            maxl=mid;
        }
    }
    if(maxn==0)
    {
    	printf("1\n%d\n",a[1]);
    	return 0;
    }
    printf("%d\n",maxl*2+1);
    for(int i=1;i<=maxl;i++) printf("%d ",a[maxmid-i]);
    printf("%d ",a[maxmid]);
    for(int i=maxl;i>=1;i--) printf("%d ",a[n-i+1]);
    return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：1)

[My Blog](https://www.cnblogs.com/lyttt/p/14079428.html)

[题目链接](https://codeforces.com/problemset/problem/626/E)

### 题目解析

首先考虑固定一个中位数，来使平均数最大。

我们可以将这$n$个数排序，然后从中位数的地方左右拓展，根据贪心，大的数肯定是要选的，所以中位数以前中间不会$skip$掉某些数然后选别的，肯定是挨着往前选，而中位数以后肯定是从最大的地方倒着选过来。这个过程中我们发现平均数先变大后变小。这个很好理解：刚开始加入的数都比较大，后来加入的数都越来越小，在某一时刻会使平均数变小。

那么这是个单峰函数，可以三分加入的数的个数，不过要注意中间可能会出现一段与$x$平行的一段。

值域是$1e6$级别的，但是我们要相信$cf$优秀的评测速度和它$3s$的时限（雾

不过可以证明中位数一定在原$n$个数之中，节省掉大量枚举中位数的时间。这个结论换句话说说，也就是选出来的数的个数一定是奇数的时候比较优。

简单证明：

不妨设一个奇数长度的答案序列为$a[1...2k-1]$（已排序），并且他们的平均数为$av$。现在证明向这个序列中加入一个数，答案不会更优。根据之前的说法，新加入的数如果小于中位数，那么它小于$a[1]$；如果它大于中位数，那么它满足$a[k]<=x<=a[k+1]$，那么这两种情况在加入有序序列后为$a[0]/a[k+1]$

先讨论$a[k+1]$的情况：新的中位数为$\frac{a[k]+a[k+1]}2$，会变大。而由于这是设的一个答案序列，所以是在中位数为$a[k]$的情况下的平均值的最大值，那么$a[k+1]$小于平均值，否则它应该在原答案序列中，那么新的平均数会变小。所以答案会变小。

对于$a[0]$的情况：增加$a[0]$后，由于$a[0]$是一个极小值，所以对平均数的影响要大于对中位数的影响（平均值易受极端值的影响），所以平均值减少得比中位数快，那么答案会变小。

（怎么感觉都好玄乎，感性理解$2333$

但其实没有这个结论似乎也不需要枚举完值域，枚举$2n-1$个数就可以了吧（每个数，和每相邻两个数的平均值

------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define N 200005
#define MOD 998244353
#define INF 0x3f3f3f3f3f3f3f3f
#define LL long long
LL rd()
{
	LL x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return f*x;
}
int n,a[N];
LL s[N];
double mx=-INF;
double f(int pos,int len)
{
	LL sum=s[pos]-s[pos-len-1]+s[n]-s[n-len];
	double av=1.0*sum/(2.0*len+1.0);
	return av-a[pos];
}
pair<double,int> tri(int pos,int l,int r)
{
	while(l+3<r)
	{
		int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		double lans=f(pos,lmid),rans=f(pos,rmid);
		if(lans<rans) l=lmid;
		else r=rmid;
	}
	pair<double,int> res=make_pair(0,0);
	
	for(int i=l;i<=r;i++)
	{
		double tmp=f(pos,i);
		if(tmp>res.first)
			res=make_pair(tmp,i);
	}
	return res;
}
int main()
{
	n=rd();
	for(int i=1;i<=n;i++)
		a[i]=rd();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i];
	
	pair<int,int> ans=make_pair(0,0);//选一个 为0 (排除掉负数 
	for(int i=1;i<=n;i++)
	{
		pair<double,int> res=tri(i,0,min(i-1,n-i));
		if(res.first>mx)
		{
			mx=res.first;
			ans=make_pair(i,res.second);
		}
	}
	
	printf("%d\n",ans.second*2+1);
	for(int i=ans.first-ans.second;i<=ans.first;i++)
		printf("%d ",a[i]);
	for(int i=n-ans.second+1;i<=n;i++)
		printf("%d ",a[i]);
	return 0;
}
/*

*/
```

---

## 作者：徐天乾 (赞：1)

这题与[P2727](https://www.luogu.com.cn/problem/P2797)（点这里）解法相同。（兄弟们，双倍经验，快点去）

在P2727的基础上，枚举求最大时，顺便记录所在的点和向左右扩展的数量。

最后直接输出即可。

```cpp
#include<bits/stdc++.h>
#define M 200200
using namespace std;
long long a[M],b[M];
int i,n,l,r,mid,T,W,X;double maxn;
double f(int x){return double(b[n]-b[n-x]+b[i]-b[i-x-1])/double(x*2+1)-double(a[i]);}
int main(){
	scanf("%d",&n);maxn=-1; //注意！maxn=-1必须加，否则要特判n<=2的情况
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for (i=1;i<=n;i++) b[i]=b[i-1]+a[i];
	for (i=1;i<=n;i++){
		l=1;r=min(i-1,n-i);X=0;
		while (l<=r){
			mid=(l+r)>>1;
			if (f(mid-1)<=f(mid))
				l=mid+1,X=mid;
			else r=mid-1;
		}
		if (f(X)>maxn)
			maxn=f(X),T=i,W=X; //与P2727的区别
	}
	printf("%d\n",W*2+1);  //左边取W个，右边取W个，以及那个点
	for (i=T-W;i<=T;i++) printf("%d ",a[i]); //输出左边最大的W个，顺便输出枚举的点T
	for (i=n-W+1;i<=n;i++) printf("%d ",a[i]); //输出右边最大的W个
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

首先将原序列排序。

看到中位数相关，先要考虑选出来的集合的大小的奇偶性。

考虑这样一个事情，加入我们选出来的数的数量是偶数，比如 $a\le b\le c\le d$，那么算出来答案应该是 $\dfrac{a+b+c+d}{4}-\dfrac{b+c}{2}=\dfrac{(a-c)+(d-b)}{4}$。

如果选奇数个的话，只需要选 $a,b,d$ 即可，答案是 $\dfrac{a+b+d}{3}-b=\dfrac{(a-b)+(d-b)}{3}$，因为 $b\le c$，所以 $a-b\ge a-c$，所以后者一定更优。

因此选偶数个一定存在一种方案让它被选奇数个代替。

接着考虑奇数个的情况。

考虑钦定中位数，那么它左边的数和它右边的数选出来的数量都一定相等。

贪心地，从大往小选一定更优。

那么我们选的数就是从大往小选的，注意到此时平均值会呈现先增大后减小的过程，因此它一定是一个单峰函数，二分或者三分处理出极值即可。

---

## 作者：Mihari (赞：0)

# 题目

[传送门](http://codeforces.com/problemset/problem/626/E)

# 题解

令 $len$ 为选出数列长度，首先，我们需要证明，$len$ 为偶数情况的一定劣于 $len$ 为奇数的情况

>假设这个差最大的子集中有偶数个元素，那么去掉中间较大的元素后对平均数减小的影响比对中位数的减小影响小，所以最后的解更优了，所以最后的集合的元素数量一定是奇数。

那么，我们现在已经确定 $len$ 为奇数的情况是最优，所以我们只需用 $\mathcal O(n)$ 的复杂度枚举中位数的位置，然后，我们再三分数列长度的一半 $len$，最后的长度即为 $len\times 2+1$

至于为什么这个偏度值对于 $len$ 是单峰的，此处给出证明：

>设数列中位数为 $m$，比 $m$ 小的前 $x$ 个数为 $f(x)$，数列最大的前 $x$ 个数为 $g(x)$，那么，数列的最优偏度值为 $p=\frac{f(x)+g(x)+m}{2x+1}-m$，再设数列变长 $\Delta$，那么变长后的数组偏度值为 $p'=\frac{f(x+\Delta)+g(x+\Delta)+m}{2x+1+2\Delta}-m$

>那么
>$$
\begin{aligned}
p-p'&=\frac{f(x)+g(x)+m}{2x+1}-m-\left\{ \frac{f(x+\Delta)+g(x+\Delta)+m}{2x+1+2\Delta}-m \right \} \\&=\frac{f(x)+g(x)+m}{2x+1}-m-\left\{ \frac{f(x)+\sum_{i=x+1}^{x+\Delta}a[i]+g(x)+\sum_{i=1}^\Delta a[i]+m}{2x+1+2\Delta}-m \right \} \\&=\left [ f(x)+g(x)+m \right ](2x+2\Delta+1)-\left [ f(x)+g(x)+m+\sum_{i=x+1}^{x+\Delta}a[i]+\sum_{i=1}^\Delta a[i]\right ](2x+1) \\&=2\Delta\left [ f(x)+g(x)+1\right ]-(2x+1)\left [\sum_{i=1}^\Delta(a[i]+a[x+i])\right ]
\end{aligned}
$$
>当 $\Delta$ 变大时，前一部分随 $\Delta$ 等倍变大，而后者会随着 $\Delta$ 的变大，刚开始会增加得很快，之后越来越小，即 $p-p'$ 随 $x$ 变大，先变大后变小，所以 $p'$ 随 $x$ 变大，先变大后变小，即证明是单峰

三分这个长度 $len$，然后算答案即可

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13379847.html
```


---

## 作者：YuRuiH_ (赞：0)

**思路：三分+贪心**

**首先将a[1...n]从大到小排序，在固定中位数的位置后，子集的构成必然是在中位数位置的两侧选取相同个，显然，每侧要尽量选取较大的值。**

**可以发现，选取的个数与平均数具有凸函数性质，所以通过三分找到临界点。整体复杂度O(nlogn)。**

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 2e5+5;
int n,a[maxn];
int o1,o2;
double ans,s[maxn];
double f(int p,int x,int a,int b){
    return (s[x-1]+s[p+x]-s[p]+b)/(2*x+a);
}
void sol(){
    double median;
    int i,j,p1,p2;
    int mid1,mid2,l,r,t1,t2;
    for(i = 0;i < 2*n-1;i++){
        if(i&1) p1=i/2,p2=p1+1,t1=2,t2=a[p1]+a[p2],median=1.0*t2/2.0;
        else p1=p2=i/2,t1=1,t2=a[p1],median=a[p1];
        l = 0,r = min(p1,n-p2);
        while(r-l>2){
            mid1 = l+(r-l)/3;
            mid2 = l+2*(r-l)/3;
            if(f(p2,mid1,t1,t2)>=f(p2,mid2,t1,t2)) r = mid2;
            else l = mid1;
        }
        for(j = l;j <= r;j++){
            if(ans < f(p2,j,t1,t2)-median){
                o1 = i,o2 = j;
                ans = f(p2,j,t1,t2)-median;
            }
        }
    }
    printf("%d\n",2*o2+1+(o1&1));
    for(i = 0;i < o2;i++) printf("%d ",a[i]);
    printf("%d ",a[i=o1/2]);
    if(o1&1) printf("%d ",a[i=o1/2+1]);
    for(j = 0;j < o2;j++) printf("%d ",a[++i]);
}
 
int main(){
    int i,j;
    scanf("%d",&n);
    for(i = 0;i < n;i++) scanf("%d",&a[i]);
    sort(a,a+n);
    reverse(a,a+n);
    s[0] = a[0];
    for(i = 1;i < n;i++) s[i] = s[i-1]+a[i];
    sol();
 
    return 0;
}

```


---

