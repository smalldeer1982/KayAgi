# [CEOI 2017] Sure Bet

## 题目描述

现在有 $n$ 个A类灯泡和 $n$ 个B类灯泡，每个灯泡都有各自的权值。

我们将这些灯泡分为 $n$ 组，每组包含一个来自A类的灯泡和一个来自B类的灯泡。

你可以从中选取任意个灯泡，每选取一个灯泡需要花费 $1$ 的代价。

在你选取完之后，系统会随机在A类和B类中选择一个类型，并点亮那一类的所有灯泡。你选取的每个点亮的灯泡会给你带来等于它权值的收益。

现在请你合理选取灯泡，以最大化可能的最小收益。你只需要求出来这个收益即可。

## 说明/提示

**样例解释**

最优策略是选择第一组的B灯泡和第三组的A灯泡和第四组的A灯泡：

-    如果B类灯泡被点亮，收益是 $3.7-3=0.7$。
-    如果A类灯泡被点亮，收益是 $1.6+1.9-3=0.5$ 。

最小可能收益是 $0.5$。

**数据范围**

对于所有测试点，有 $1.0\le A_i,B_i\le 1000.0$，$0\le n\le 10^5$。

## 样例 #1

### 输入

```
4
1.4 3.7
1.2 2
1.6 1.4
1.9 1.5```

### 输出

```
0.5000```

# 题解

## 作者：Seauy (赞：40)

既然没有人写题解，那我就首当其冲吧

这道题方法其实很多

先说明一点，每次可以从 A类 获得 a 的权值，从 B类 获得 b，最小的情况是 min(a,b)，题目要我们求的就是最大的 min(a,b)

第一眼看上去就像动态规划，但是具体怎么规划我不知道

但是有一点确定，动态规划的朋友们，数据给你的权值要乘以 10^4 不然无法规划，数组也要开到原来的 10^4 倍

好了废话到此为止，重头戏现在开始

法一：三分法

这其实是这道题的正解

三分法，名字十分形象，跟二分法很类似，只不过它是每次三等分，有些情况会比二分快

比如这道题，其实二分根本做不了，只能用三分

为什么呢？大家都知道，二分的前提是数据呈单调上升，这样我们才能把一条图像分成大与小两部分

![](https://cdn.luogu.com.cn/upload/pic/53203.png)类似于这种图像，是二分所适用的，因为纵着切一刀可以分成大小一眼可辨的大与小两瓣

但是很显然，因为受“每拿一个灯泡就要耗费一权值”的限制，函数不呈单调上升，那是什么样呢？

![](https://cdn.luogu.com.cn/upload/pic/53205.png)

是类似的二次函数，满足规律“先上升再下降”（二次函数性质易证）

而我们要求的答案自然在最高处的“屈服点”

而我们用三分法对答案进行试探，每次三分必然产生“左，中，右”三段，而再进一步分析左中右的走势再判断屈服点在那一段

具体说，我们找到了两个点，a 与 b，把这一段分成了三段

1. a<=b时，答案则锁定在中与右段，则继续三分 a~R 段

2. a>b 时，答案则锁定在左与中段，则三分 L~b 段

具体代码就不展示了，因为我不是用三分过的 qwq


------------

法二：贪心（枚举）

我是用这个神奇算法过的，没有三分那么高大上

由于每一次都要花费一权值，那么高权值的灯泡不拿白不拿，那就全拿上了！

然而并不能很粗暴地全拿光，因为有可能好灯泡不是在 A类 与 B类 均匀分布的

所以更好的方法，是从 A类 拿一个贼大的，然后再从 B类 拿一堆尽量与 A 所获得的价值屏平衡

B 比 A 获得的多的时候，A 就不能坐以待毙了，要开始拿灯泡了

其实就是不断调整 A 与 B 获得的价值，使他们尽量平均

奉上代码（终于啊）
```cpp
/*
    n 个 A组 灯泡
    n 个 B组 灯泡
    你在其中任意选灯泡（每个灯泡有它的价值）
    每选一个要用一块钱
    选完之后任意点亮已选的 A 或 B 灯泡
    你会得到相应的价值
    求最大的最小收益
    (A 类得 a ，B 类得 b，求最大的min(a,b))
*/
#include<bits/stdc++.h>
using namespace std;

int n;
double A[100001],B[100001],ans;
bool visit[100001][2];

bool cmp(double a,double b)
{return a>b;}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) cin>>A[i]>>B[i];
    sort(A+1,A+n+1,cmp);
    sort(B+1,B+n+1,cmp);
    double a=0.0,b=0.0;
    for(double i=1,j=1;i<=n && j<=n;)
    {
        int x=i,y=j;
        a+=A[x]*double(!visit[x][0]);
        b+=B[y]*double(!visit[y][1]);
        visit[x][0]=visit[y][1]=1;
        ans=max(ans,min(a-i-j,b-i-j));
        if(a>=b) j++;
        if(a<=b) i++;
    }
    printf("%.4lf",ans);
    return 0;
}
```
~~话说这道题又不难，怎么没人写题解呢QAQ~~

---

## 作者：anyi777 (赞：36)

不难想到从大到小选择时的策略最优，对 $a$ 和 $b$ 数组做前缀和，然后用双指针就可以了。复杂度瓶颈在于排序时的 $O(n×log_2(n))$。

关键是在于双指针怎么走？

不妨设 $A[i]$ 表示数组 $a$ 的前缀和，$B[i]$ 表示数组 $b$ 的前缀和，发现当 $A[i]>B[j]$ 时，$ans=B[j]-i-j$，此时应该移动指针 $j$，因为移动指针 $i$ 只会使 $ans$ 更小，所以 $A[i]>B[j]$ 时移动指针 $j$，$A[i]<=B[j]$ 时移动指针 $i$

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
double a[N], b[N];

bool cmp(double a, double b){return a > b;}

int main(){
    int n;
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i] >> b[i];
    }
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    for (int i=1; i<=n; i++) a[i]+=a[i-1], b[i]+=b[i-1];
    double ans = 0;
    int i=1, j=1;
    while (i<=n && j<=n){
        if(a[i] > b[j]){
            ans = max(ans, b[j]-i-j);
            j++;
        }else{
            ans = max(ans, a[i]-i-j);
            i++;
        }
    }
    printf("%.4lf", ans); 
    return 0;
}
```


---

## 作者：water_tomato (赞：24)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p4653-ceoi2017sure-bet-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/P4653)。

有两组物品，每个物品都有一定的价值，你需要选择若干个物品，收益为两组物品中价值和较少的那组物品的价值和减去所选取的所有物品数。使收益最大化。

## 解析

发现肯定优先选择价值高的物品。

发现如果已经选择了若干个物品，接下来那个物品只有选择当前总价值低的那一组才有可能有更优解。

由上，本题可以用双指针解决。对于两组物品分别用一个指针维护，再依次尝试选择总价值低的那一组，在过程中统计答案。第一个物品可以随意选择，因为不可能出现一组选一组不选的情况，这还不如啥都不选。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,l,r;//l：A组,r:B组
double a[N],b[N],ans,suma,sumb;
inline bool cmp(double i,double j){
	return i>j;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf%lf",&a[i],&b[i]);
	sort(a+1,a+1+n,cmp);sort(b+1,b+1+n,cmp);
	for(r=1;r<=n;r++){//双指针
		sumb+=b[r];ans=max(ans,min(suma-(l+r),sumb-(l+r)));
		while(suma<sumb&&l<n){//尝试选择当前总价值低的那组
			suma+=a[++l];
			ans=max(ans,min(suma-(l+r),sumb-(l+r)));
		}
	}
	printf("%.4lf\n",ans);
	return 0;
}
```



---

## 作者：metaphysis (赞：20)

这个题目还是比较有趣，第一次看竟然题目都没看懂。经过 @草1药人 的解释、 观察样例解释以及自己的揣摩，弄明白了出题者的用意。大意就是给定 $A$、$B$ 两个实数数组，两个数组的大小均为 $n$，从数组 $A$ 中挑选 $x$ 个元素，令其和为 $S_x$，从数组 $B$ 中挑选 $y$ 个元素，令其和为 $S_y$，要求最大化 $min$($S_x-x-y$，$S_y-x-y$)。现有三篇题解都是用贪心法来解题，但未给出严格证明。有一篇题解提到可以使用三分搜索进行解题，但是语焉不详，没有具体分析，参考价值不大。@草1药人 也尝试使用此种方法，但是不确定是否可行。

三分搜索要求给定变量 $x$，关于变量 $x$ 的函数 $f(x)$ 的几何图像是一个类似抛物线的形状（上抛物线或者下抛物线，或者台阶线，见于某些绝对值函数）。普通的二分搜索要求区间函数值单调，因此无法使用二分搜索来查找此类函数的极值，而用三分搜索则可以。因为数学上，在满足前提的情况下，可以保证极值点位于三分搜索的左三分之一和右三分之一这两者所约束的区间之内。

那本题的类抛物线函数在哪里？

假设按照最优方案选取，从 $A$ 数组中取了 $x$ 个元素，从 $B$ 数组取了 $y$ 个元素，由于需要最大化 $min$($S_x-x-y$，$S_y-x-y$)，直觉上，$S_x$ 应该尽量大，同样的，$S_y$ 也尽量大，而且两者应当尽量接近（能力所限，无法给出严格的证明，暂且认为是正确的，现有的题解中使用贪心法也基于此结论）。


那么，为了使得 $S_x$ 应该尽量大，$S_y$ 也尽量大，不妨将数组 $A$ 和 $B$ 中的元素按降序排列，按从大到小的顺序取 $A$ 和 $B$ 中的元素。

先固定 $x$ 的大小，即从 $1$ 到 $n$ 枚举 $x$ 的大小，假设当前得到的和为 $S_x$，此时函数值 $S_x-x$ 已经固定，随着在数组 $B$ 中取的元素个数 $y$ 的增大，很明显，$S_x-x-y$ 是递减的（可能非严格递减），而函数 $f(y)=S_y-x-y$ 的几何图像却有可能开始是递增的，然后到达一个极大值，接着又开始递减，构成一个类似抛物线的形状（或者在某些情况下甚至是单调递增的）。一个函数递减，另外一个递增然后递减（或者保持递增），则两者的合函数 $f(y)=min(S_x - x - y, S_y - x - y)$ 所构成的几何图像也是类似于抛物线的形状（可能并不光滑），因此可以通过三分搜索来确定一个 $y$ 值，使得 $f(y)$ 的值最大。


```
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

int n;
double a[MAXN], b[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    sort(a, a + n, greater<double>());
    sort(b, b + n, greater<double>());
    // 求前缀和，便于后续计算。
    for (int i = 1; i < n; i++) b[i] += b[i - 1];
    double r = 0, sx = 0;
    for (int x = 0; x < n; x++)
    {
        sx += a[x];
        int left = 0, right = n - 1, y;
        while (left <= right)
        {
            int leftThird = left + (right - left) / 3;
            int rightThird = right - (right - left) / 3;
            //if (min(sx, b[leftThird]) - (x + 1) - (leftThird + 1) >=
            //    min(sx, b[rightThird]) - (x + 1) - (rightThird + 1))
            if (min(sx, b[leftThird]) - leftThird >=
                min(sx, b[rightThird]) - rightThird)
                y = leftThird, right = rightThird - 1;
            else
                y = rightThird, left = leftThird + 1;
        }
        //r = max(r, min(sx - (x + 1) - (y + 1), b[y] - (x + 1) - (y + 1)));
        r = max(r, min(sx, b[y]) - (x + 1) - (y + 1));
    }
    cout << fixed << setprecision(4) << r << '\n';

    return 0;
}
```

---

## 作者：Sternenlicht (赞：10)

思路：贪心。

设两组灯泡中当前价值较高的是 A 组，价值较低的是 B 组，由题目可知，取 A 组不能使答案更优，因此只能取 B 组。

对于每组灯泡而言，先取的一定是价值高的，所以我们将每组灯泡从大到小排序，记录从前往后取的灯泡个数。

用两个指针分别维护两组灯泡，边贪心边更新答案。更新答案时，取当前总价值小的组中价值最大的即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
double a[N],b[N],ans,suml,sumr;//suml，sumr分别是A组灯泡和B组灯泡的指针 
int n,now;//now表示当前位置 
bool cmp(double x,double y){return x>y;}//排序函数
int main(){
	cin>>n;
	for (int i=1;i<=n;i++)cin>>a[i]>>b[i];//读入A组灯泡和B组灯泡 
	sort(a+1,a+n+1,cmp);sort(b+1,b+n+1,cmp);//从大到小排序 
	for (int i=1;i<=n;i++){
		suml+=a[i];
		ans=max(ans,min(suml-i-now,sumr-i-now));//使最小值最大
		while (sumr<suml&&now<n)//贪心，往后移动找最大值 
			now++,sumr+=b[now],
			ans=max(ans,min(suml-i-now,sumr-i-now));
	}
	cout<<fixed<<setprecision(4)<<ans<<'\n';//输出答案，保留4位小数 
	return 0;
}
```

---

## 作者：Jerrycyx (赞：6)

### 前言 & 吐槽

@[Seauy](https://www.luogu.com.cn/user/54591) 大佬的[题解](https://www.luogu.com.cn/article/5fbh997u)说二分做不了，但其实是可以的。

题面中将灯泡分组的说法具有误导性，实际上不用管这个分组，任意选就行。

-----

### 思路 & 解析

“最小值最大”是**二分答案**的经典标志，问题答案具有二段性：在最大的最小值以前，一定有方法使收益达到或超过目标，以后则一定不可能达到。

**二分这个最大的最小可能收益 `mid`**。如果有某种方法可以使两类灯泡都能大于等于这个最小可能收益，那么比它小的也都能达到，`l=mid`；否则如果不存在这样的方法，比它大的都达不到，`r=mid`。

附一个浮点数二分模板：

```cpp
const double EPS=1e-6;
double l=0,r=2e8;
while(r-l>EPS)
{
  double mid=(l+r)/2;
  if(check(mid)) l=mid;
  else r=mid;
}
```

问题的关键在于如何找这个方法，即 `check` 函数怎么写。

贪心的思路，如果要在某一类中选灯泡，选灯泡的代价都一样，那么一定是**优先选权值高的灯泡**。所以，我们将灯泡按照权值从大到小排序，并预处理出排序后的前缀和。

那么我们就可以**枚举一共选择的灯泡数量 $i$**，这样对于每一类灯泡，都必须保证选择灯泡的权值和减去 $i$ 大于等于 $mid$，即权值和大于等于 $mid+i$。

然后**在每一类灯泡中，选出最少的灯泡使其满足权值和大于等于 $mid+i$**，这个可以直接在刚才预处理的前缀和数组上跑二分查找。

最后，**如果两类所需要的灯泡数量小于等于 $i$**（在灯泡数量限制内可以选出足够满足条件的灯泡）**，这个 $mid$ 就是可行的**。否则若无论选择多少个灯泡都不能满足条件，这个 $mid$ 就是不合法的。

时间复杂度 $O(\log \frac{n V}{\epsilon} \times n \log n)$，$V$ 表示 $A,B$ 的值域，$\epsilon$ 表示精度（即上面模板中的 `EPS`）。

-----

### 代码 & 细节

一共有 $2n$ 个灯泡，枚举选择灯泡数量的时候别写成 $n$ 了。

如果二分查找满足条件的最少灯泡时发现无法使权值和大于等于 $mid+i$，代表即便全选也依然小于要求的下限 $mid$，此时已经不可能合法了。后面更大的 $i$ 更不可能找到合法选择方案，所以这里直接 `break` 掉就行了。

[代码](https://www.luogu.com.cn/record/198773597)：

```cpp
#include<cstdio>
#include<algorithm>
#include<functional>
using namespace std;

const int N=1e5+5;
int n;
double a[N],b[N];
double suma[N],sumb[N];

bool check(double flr)
{
	for(int i=1;i<=n<<1;i++) //注意要乘2
	{
		int mna=lower_bound(suma+1,suma+n+1,flr+i)-suma;
		int mnb=lower_bound(sumb+1,sumb+n+1,flr+i)-sumb;
		if(mna>n||mnb>n) return false;
		//判断越界（找不到可行解），后面再也不可能有解了
		if(mna+mnb<=i) return true; //判断条件==和<=均可通过
	}
	return false;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i],&b[i]);
	sort(a+1,a+n+1,greater<double>()); //从大到小排序，下同
	sort(b+1,b+n+1,greater<double>());
	for(int i=1;i<=n;i++) //预处理前缀和
	{
		suma[i]=suma[i-1]+a[i];
		sumb[i]=sumb[i-1]+b[i];
	}
	const double EPS=1e-6;
	double l=0,r=2e8;
	while(r-l>EPS)
	{
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.4lf\n",l);
	return 0;
}
```

-----

### 后记 & 扩展

此方法可以很轻松地扩展为“$k$ 类灯泡”问题（时间复杂度乘个 $k$），而 $O(n)$ 的直接贪心则做不到。

---

## 作者：yuyc (赞：5)

现有的题解的证明感觉写的不是很严谨，所以我来尝试对现有题解的贪心思路进行进一步的证明。

设选 $x$ 个 A 灯泡，$y$ 个 B 灯泡能使得最小可能收益最大，令 $suma_i = \sum_{j=0}^{i}a_i$，$sumb_i = \sum_{j=0}^{i}b_i$ ，即 $a$，$b$ 的前缀和数组，此时答案为 
$$
\min(suma_x-x-y,sumb_y-x-y)=\min(suma_x,sumb_y)-x-y
$$

设我们目前已经选了 $x_0$ 个 A 灯泡，$y_0$ 个 B 灯泡。

当 $x_0<x$ 且 $y_0<y$ 的时候，下一步选谁不重要。

这样随便选，直到选完某一个灯泡之后，如果出现了 $x_0=x$ 且 $y_0<y$，那么此时的最小可能收益为

$$\begin{aligned}

\min(suma_{x_0},sumb_{y_0})-x_0-y_0&=\min(suma_x,sumb_{y_0})-x-y_0\\
   &\le\min(suma_x,sumb_y)-x-y

\end{aligned}$$

此时假设 $suma_x\le sumb_{y_0}$，那么有 $suma_x<sumb_y$，也就是说，$suma_x-x-y_0\le suma_x-x-y$，即 $y_0\ge y$，与先前提到的 $y_0<y$ 矛盾，故 $suma_x> sumb_{y_0}$。

按照现有题解中贪心的思路，我们每次选的是权值和更小的那一种灯泡，要证明这个做法是对的，其实就是要证明在当前基础上，$y_0=y$ 成立之前，$suma_x> sumb_{y_0}$ 一直成立。

假设存在 $y_0<y$ 使得 $suma_x\le sumb_{y_0}$ 成立，那么此时最小可能收益为 $suma_x-x-y_0$，如果 $suma_x\le sumb_y$，那么答案为 $suma_x-x-y>suma_x-x-y_0$，答案比此时值还要劣，矛盾；否则 $suma_x>sumb_y$，但显然 $sumb_{y_0}<sumb_y$，与 $suma_x\le sumb_{y_0}$ 矛盾。
综上，不存在这样的 $y_0$，当 $x_0=x$ 且 $y_0<y$ 时，贪心策略正确。


$x_0<x$ 且 $y_0=y$ 的情况同理。

另外，CEOI其实是有官方题解的，[链接](https://ceoi2017.acm.si/files/ceoi2017-solutions-day1.pdf)。

官方题解给出的线性做法（抛开排序）其实是枚举选 A 灯泡的个数 $n_a$，对于每个 $n_a$，求得在选了 $n_a$ 个 A 灯泡的情况下，使得答案最大的选择的 B 灯泡的个数 $n_b$。可以证明，随着 $n_a$ 的增大，$n_b$ 不会减小，且增大 $n_b$ 能使最小可能收益更大，直到 $ \sum b_j −n_a  \ge\sum a_i −n_b$ 之后，增大 $n_b$ 会使最小可能收益变小，$n_a$、$n_b$ 可以使用双指针来维护。

这里只给出我用官方题解做法写的代码：

```cpp
#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e5 + 20, mod = 10007;
double a[N],b[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	double res = 0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		a[i]--,b[i]--;
	}
	sort(a + 1,a + n + 1,greater<double>());
	sort(b + 1,b + n + 1,greater<double>());
	double suma = 0,sumb = 0;
	for(int i=1,j=1;i<=n;i++){
		suma += a[i];
		while(j <= n && min(suma - j,sumb - i + b[j]) > min(suma - j + 1,sumb - i)){
			sumb += b[j];
			j++;
		}
		res = max(res,min(suma - j + 1,sumb - i));
	}
	cout<<fixed<<setprecision(4)<<res;
	return 0;
}
```

---

## 作者：Foofish (赞：5)

同步发表于 csdn [博客](https://www.cnblogs.com/Mercury-City/p/16023892.html)

这是一篇时间复杂度为 $O(n \log_2{n})$ 的双指针做法题解。

## 题意
有两组物品各 $n$ 个 $(1\leq n \leq 10^5)$ ，每组物品有一定的价值。你需要选择若干个物品，收益为两种物品中价值的 **和** 较少的那组物品的价值之和，减去选取的物品数量，使收益最大化。

## 思路

首先，显然的一点是，如果我们选择的话我们一定会选择这组中收益比较大一点的物品。

那么就好做了，因为如果我现在假如说令第一组取出的数的个数为 $l$ ,第二组取出的个数为 $r$ 。我现在个数为 $l$ 就只可能选的是前 $l$ 个，个数为 $r$ 就只可能是选择的前 $r$ 个。

那么我现在 **最优情况** 当第一组取 $l$ 个时，两堆数字和假如说已经求出了，答案分别是 $suma_{l}$ 和 $sumb_{r}$ 。我现在让第一组多选一个，即选择 $l+1$ 个，那么这时候，第二组是不可能将之前的选择撤销的，毕竟这只会让开销变得更大。而不会使答案变得更大。

那么 $l$ 和 $r$ 只需要分别在两堆上线性移动就 ok 了。

时间的瓶颈在于排序，去除排序时间复杂度是 $O(n)$ 的。

```cpp
#include <bits/stdc++.h>
#define double long double
using namespace std;
const int MAXN=100086;
int n;
double a[MAXN],b[MAXN];
bool cmp(const double &x,const double &y){
	return x>y;
}
double sum1,sum2,maxx;
bool judge(int l,int r){
//判断往后移动答案是否会变大，如果能变大就往后移，也是一种贪心的思想
	double res=min(sum1,sum2)-l-r+1; //没有移动之前的答案
	if(min(sum1,sum2+b[r])-l-r>res) return 1;
	else return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i]>>b[i];
	sort(a+1,a+n+1,cmp); sort(b+1,b+n+1,cmp);
	int r=1;
	for(int l=1;l<=n;++l){
		sum1+=a[l];
		double res=0;
		while(judge(l,r)&&r<=n) sum2+=b[r++];
		maxx=max(maxx,min(sum1,sum2)-l-r+1);
		//每次移动结束记录一下答案。
	}
	cout<<fixed<<setprecision(4)<<maxx<<endl;
    return 0;
}
//Welcome back,Newhanser.

```

---

## 作者：vijone (赞：4)

#### [题目链接](https://www.luogu.com.cn/problem/P4653)

前置知识：①三分法②暴力

看到另外的题解都提到了三分，但没有一个给出了代码，而都选择了贪心解决。所以本蒟蒻就准备了这篇题解。

首先，定义一下，下文所说的收益是指在总共取一定数量的灯泡的情况下，a类灯泡的 权值之和 与b类灯泡的 权值之和 中的 **较小值** 减去代价和。

若我们以 **总共** 取的灯的个数为横坐标，最大收益为纵坐标，建立直角坐标系。设函数 $ f(x)$ 为在横坐标为x时（即取x盏灯时）的最大收益。

首先用贪心的思想考虑，肯定优先选择权值大的灯泡，所以我们可以对 a 种类的灯泡和 b 种类的灯泡分别按权值大小排序，用来确定我们的选取灯泡的顺序。但是，因为这题每取一盏灯都有花费，所以这导致了本题的 $ f(x)$ 是不单调的，却是单峰的。（因为代价可能比权值大，也可能比权值小，而权值 - 代价才是对答案的贡献，这个贡献若是负数，那还不如不贡献，若是正数，则必然选择贡献。）

既然是单峰函数，那必然想到三分求最值。

那么类比于二分答案，我们需要写一个 check 函数：而这个 check函数就是上文所说的 $ f(x) $  。即在总共取 x 盏灯时，a 与 b 两类灯泡中的较小权值的最大值。    
下面就是我写的 check 函数 
```cpp
double f(int x)//其中出现的 maxx 函数是指两者中的较大值
{
	int ia=1,ib=1;double suma=0.0,sumb=0.0;
    //首先，贪心的想想，因为要在a，b两者中取较小值，所以要a和b相对平均
	//我认为这里需要分类讨论，讨论 优先取 a 类灯泡 和 优先取 b 类灯泡 的收益较大值，所以这里要用两次循环。
	for(int i=1;i<=x;i++)
	{
		if(suma>sumb)
		{sumb+=b[ib];ib++;}
		else
		{suma+=a[ia];ia++;}
	}
	double anss=minn(suma,sumb)-double(x);
	ia=1;ib=1;suma=0.0;sumb=0.0;
	for(int i=1;i<=x;i++)
	{
		if(suma<sumb)
		{suma+=a[ia];ia++;}
		else
		{sumb+=b[ib];ib++;}
	}
	double tmp=minn(suma,sumb)-double(x);
	return maxx(tmp,anss);
}
```

但是，因为我们三分的 x （即 **总共** 取的灯的个数）是 int 类型的，所以三分法取三分之一时可能有一定的误差，所以我用了一种特殊的方法：三分优化暴力。（本题的暴力挺好想的，for 循环枚举上文所提到的 f 函数的 x 值，带入 f 函数算最值。时间复杂度 $O(n^{2})$ ）

具体实现：通过三分法确定最优的 x 的大致范围（代码中取 1000 ，亲测开到 100 会 WA ），然后在大致范围中暴力。最终时间复杂度在 $ O(n \; log_2 \; n)$ 左右。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double ans,a[200010],b[200010];
int lmid,rmid,l,r,n;
double maxx(double aaa,double bbb)
{
	return aaa>bbb?aaa:bbb;
}
double minn(double aaa,double bbb)
{
	return aaa<bbb?aaa:bbb;
}
bool cmp(double aa,double bb)
{
	return aa>bb;
}
double f(int x)
{
	int ia=1,ib=1;double suma=0.0,sumb=0.0;
	for(int i=1;i<=x;i++)
	{
		if(suma>sumb)
		{sumb+=b[ib];ib++;}
		else
		{suma+=a[ia];ia++;}
	}
	double anss=minn(suma,sumb)-double(x);//注意：权值和要减去代价。
	ia=1;ib=1;suma=0.0;sumb=0.0;
	for(int i=1;i<=x;i++)
	{
		if(suma<sumb)
		{suma+=a[ia];ia++;}
		else
		{sumb+=b[ib];ib++;}
	}
	double tmp=minn(suma,sumb)-double(x);
	return maxx(tmp,anss);
}
int main()
{
 	cin>>n;
 	for(int i=1;i<=n;i++)
 	{
 		scanf("%lf%lf",&a[i],&b[i]);
	 }
	 sort(a+1,a+n+1,cmp);
	 sort(b+1,b+n+1,cmp);
	 l=1;r=(int)n;
	 r=r*2;//一个注意点：因为定义中f(x)的参数x是总共取的灯数，所以r要取到两倍的组数（即 2*n）
	 while(r-l>=1000)//三分法确定大致范围
	 {
	 	int mm=r-l;
	 	mm=mm/3;
	 	rmid=r-mm;
	 	lmid=l+mm;
	 	if(f(rmid)>f(lmid))
	 	{
	 		l=lmid;
		 }
		 else
		 {
		 	r=rmid;
		 }
	 }
	 ans=0.0;
	 for(int i=l-1;i<=r+1;i++)//暴力
	 {
	 	ans=maxx(ans,f(i));
	 }
	 printf("%.4lf",ans);
	return 0;
}

```

谢谢您的阅读。如有错误请您指出。

---

## 作者：Martian148 (赞：4)

# 这道题方法其实很多

### 说实话这道题的正解是三分，当然wyj用二分代替三分不算，但这里还是推荐用三分。
#### but三分代码过于long我果断用贪心强刷过，哈哈哈，下面讲一下贪心的解法
#### 如果要取，肯定调最大的取，所以要先将A,B数组排序，但是当取A的大于取B的时候，再取A已经没有意义了，因为最小值是不变的，所以要保持取A的和取B的相对平衡，就像毛毛虫算法一样，A>=B了B往前拱，否则A向前拱，因为A，B数组不能加两次，所以要用vis数组标记一下。枚举每个i和j，ans从每次答案中刷出一个最优解就AC了，下面给出我的代码。
```cpp

#include<bits/stdc++.h>
using namespace std;
int n;
double a[100005],b[100005],ans;
bool vis[100005][2]; 
int read(){
    int ret=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
    while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
bool cmp(double a,double b){
    return a>b;
}
int main(){
//    freopen("NOIP.in","r",stdin);
//    freopen("NOIP.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i],&b[i]);
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+n,cmp);
    memset(vis,1,sizeof vis);
    double A=0,B=0;
    for(int i=1,j=1;i<=n&&j<=n;){
        int x=i,y=j;
        A+=a[x]*vis[x][0];
        B+=b[y]*vis[y][1];
        vis[x][0]=vis[y][1]=0;
        ans=max(ans,min(A-i-j,B-i-j));
        if(A>=B)j++;
        else i++;
    }
    printf("%.4lf",ans);
    return 0;
} 
```


---

## 作者：lyxeason (赞：1)

根据贪心的思想，肯定优先选价值高的（这题的 $n$ 组没什么用）。由于要让最小值最大，所以当选完一个后，如果其中一组的价值总和比另一组多，那么肯定选另一组的更优。因为如果仍然选择价值高的组的灯泡那么最小值不会变大，只有选另一组的灯泡才可能使最小值变大。

所以就有这样一种算法，先从大到小排序，设立两个指针分别表示 $A,B$ 组的灯泡选到了哪一个，之后选择已选的灯泡价值总和较少的一组选电灯泡，以此类推。答案就可以一边算一边更新。

需要先排序且每一次都会把一个指针向后推，所以时间复杂度 $O(n \log n + 2n)$。

------------
### 代码
###### 代码里有注释

```cpp


#include <cstdio>
#include <algorithm>

using namespace std;

int N;
double A[100009];
double B[100009];
bool st[100009][2]; //记录哪些位置算过了，以免重复计算
double res;

void In () {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lf%lf", &A[i], &B[i]);
}

inline bool Cmp (double a, double b) {
    return a > b;
}

inline double Max (double a, double b) {
    return a > b ? a : b;
}

inline double Min (double a, double b) {
    return a < b ? a : b;
}

void Solve () {
    int i = 1;
    int j = 1; //两个指针
    double tA = 0;
    double tB = 0; //当前两个组选的灯泡的价值之和

    for (int i = 1; i <= N; i++) st[i][0] = st[i][1] = true;
    sort(A + 1, A + N + 1, Cmp);
    sort(B + 1, B + N + 1, Cmp);
    while (i <= N && j <= N) {
        tA += (A[i] * st[i][0]);
        tB += (B[j] * st[j][1]); //这里乘 st 就是为了避免重复加，因为一次只会有一个指针向后移，另一个不会
        res = Max(res, Min(tA - i - j, tB - i - j)); //实时更新答案
        st[i][0] = st[j][1] = false; //标记算过了当前指针的位置
        if (tA >= tB) j++;
        else i++; //选总和较少的往后推
    }
}

void Out () {
    printf("%.4lf\n", res);
}

int main () {

    In();
    Solve();
    Out();

    return 0;
}
```

---

## 作者：XL4453 (赞：1)

题目分析：

考虑贪心。

当发现有一组灯泡，不妨设其为 $A$ 组灯泡，比另一组的价值高的时候，那么再去取 $A$ 组的灯泡并不能增加其收益，所以一定要取另一组，也就是 $B$ 组的灯泡。

而无论对于哪一组灯泡，优先取价值更高的灯泡一定是没有问题的，否则将一个价值不高的灯泡更换成一个价值更高的灯泡一定答案不会更劣，只有可能相等或更优，那么也就是意味着所有的灯泡一定是从排好序的灯泡组的第一个一直取到当前的那一个的。

------------

这时本题的做法就很清楚了，现将两组灯泡分别按价值从大到小排序，然后分别维护两组灯泡从前到后一共取了多少个灯泡。

对于每一次决策，从当前总价值小的那一组灯泡里取一个价值最大的，更新答案即可。

------------
本题的另一种做法：三分法，思路是这样的（参考了metaphysis大佬的题解，自己所做的时候由于太菜没有想到）：先确定 $A$ 中取得灯泡，然后再用三分法求解此时 $B$ 中灯泡的最大价值。

但蒟蒻认为这种做法不是最优的。

这时因为三分法利用到的性质只有“优先取价值更大灯泡”，而没有利用到一组灯泡价值已经比另一组灯泡更高时直到另一组灯泡价值反超前一定不再次取价值更高的一组灯泡。

------------
二分斜率的 wqs二分 算法思路和三分法差不多，这里不再赘述。

------------
代码（贪心算法）：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
double a[100005],b[100005],ans,tota,totb;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&a[i],&b[i]);
		a[i]=-a[i];b[i]=-b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int j=0;
	for(int i=1;i<=n;i++){
		tota-=a[i];
		ans=max(ans,min(tota-i-j,totb-i-j));
		while(totb<tota&&j<n){
			j++;totb-=b[j];
			ans=max(ans,min(tota-i-j,totb-i-j));
		}
	}
	printf("%.4f",ans);
	return 0;
}
```



---

