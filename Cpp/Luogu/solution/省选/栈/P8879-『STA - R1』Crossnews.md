# 『STA - R1』Crossnews

## 题目背景

Informational problems make us better.

## 题目描述

定义两个序列 $\{a_n\}$，$\{b_n\}$ 的联合权值为
$$\operatorname{unval}(a,b)=\sum_{i=1}^nb_i(b_i-a_i)$$

现给定一个序列 $\{a_n\}$，求满足 $\operatorname{unval}(a,b)$ 最小的单调不减序列 $\{b\}$，只需输出 $\operatorname{unval}(a,b)$ 的值即可。

注意，$\{b\}$ 中的元素不一定要为整数。

## 说明/提示

提示：如果你不会做这道题，可以问问 [APJifengc](/user/279652)。
***

样例 1 解释：使得联合权值取到最小值的 $\{b\}$ 为 `0.5 1 1.5 2 2.5`。

***
数据范围和约定：
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}\\\hline
\textsf{1} & 100 & 10 & \textbf{无} \\\hline
\textsf{2} & 10^6 & 5 & \{a\}\textbf{ 全部相等} \\\hline
\textsf{3} & 10^6 & 5 & \{a\}\textbf{ 单调不减} \\\hline
\textsf{4} & 10^4 & 30 & \textbf{无} \\\hline
\textsf{5} & 10^6 & 50 & \textbf{无}
\\\hline\hline
\end{array}
$$

对于全部数据，有 $1\le n\le 10^6$，$|a_i|\le 10^3$。

***

评分规则：

本题使用 Special Judge，如果你的答案是 $pans$，标准答案是 $cans$，则你将获得
$$\min\Bigg\{100,\Bigg\lfloor\dfrac{0.1}{\min\Big\{|pans-cans|,\Big|\dfrac{|pans-cans|}{cans}\Big|\Big\}}\Bigg\rfloor\Bigg\}$$
分。

**每个 Subtask 内捆绑测试**。即取 Subtask 内得分最小的作为 Subtask 得分。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
-13.7500000```

## 样例 #2

### 输入

```
10
1000 1 2 8 9 5 4 1000 -40 1000```

### 输出

```
-403015.7500000```

# 题解

## 作者：Thunder_S (赞：5)

## Solution

我们考虑如何得到最优的 $\{b_n\}$。

对式子进行简单的变形：

$$\sum_{i=1}^nb_i\left(b_i-a_i\right)=\sum_{i=1}^n\left(b_i-\frac{a_i}{2}\right)^2-\sum_{i=1}^n\frac{a_i^2}{4}$$

后面那部分是定值，我们只需要最小化前面那部分即可。

令 $A_i=\frac{a_i}{2}$（方便叙述）。

先从简单情况出发。当 $n=2$ 时，如果 $A_1\le A_2$，那么 $b_1=A_1,b_2=A_2$ 即可。但如果 $A_1>A_2$，由于题目要求 $b_1\le b_2$，我们就不能同时使两个括号内部为 $0$。下面我们证明，当 $b_1=b_2=\dfrac{A_1+A_2}{2}$ 时，取得最优结果。

建立一个平面直角坐标系。注意到 $\left(b_1-A_1\right)^2+\left(b_2-A_2\right)^2$ 就表示点 $\left(b_1,b_2\right)$ 到点 $\left(A_1,A_2\right)$ 距离的平方。所以我们需要最小化这个距离。

由于 $A_1>A_2,b_1\le b_2$，所以点 $(A_1,A_2)$ 在直线 $y=x$ 的下方，点 $(b_1,b_2)$ 在直线的上方（包括直线）。根据垂线段最短可以得到，当点 $(b_1,b_2)$ 在直线 $y=x$，且同时经过 $(b_1,b_2)$ 和 $(A_1,A_2)$ 的直线与 $y=x$ 垂直时，距离最短。可以解得此时 $b_1=b_2=\dfrac{A_1+A_2}{2}$。这个证法显然可以推到多个括号。

到此，我们解决了 $n=2$ 的问题。进一步的，我们似乎得到了一种通用的解法。

总结上面的做法，现在我们需要将 $A_i$ 分成若干个区间，并且保证每个区间的平均数单调不减，并且使区间数尽量大。对于每个区间，记录 $(l,v)$ 表示该区间长度为 $l$，平均数为 $v$。对于新的元素 $(1,A_i)$，如果 $A_i$ 小于上个区间的平均数，那么就合并两个区间。最后，如果 $i$ 所在区间记为 $(l_0,v_0)$，就有 $b_i=v_0$。

## Code
```cpp
#include<cstdio>
#define N 1000005
#define db double
using namespace std;
int n,cnt;
db ans,a[N];
struct node 
{
    int len;
    db val;
    node (int l=0,db v=0) {len=l;val=v;}
}q[N];
node merge(node x,node y) {return node(x.len+y.len,(x.val*x.len+y.val*y.len)/(x.len+y.len));}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%lf",&a[i]);
        a[i]/=2;
    }
    for (int i=1;i<=n;++i)
    {
        q[++cnt]=node(1,a[i]);
        while (cnt>1&&q[cnt].val<q[cnt-1].val) 
            q[cnt-1]=merge(q[cnt],q[cnt-1]),cnt--;
    }
    for (int i=1,j=1;i<=cnt;++i)
        while (q[i].len--)
        {
            ans+=q[i].val*(q[i].val-a[j]*2);
            j++;
        }
    printf("%.7lf\n",ans);
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：5)

## 题目简述

> - 给定长度为 $n$ 的数列 $a_i$，求**实数不降**数列 $b_i$ 最小化
>
> $$
 \sum_{i=1}^n b_i(b_i-a_i)
 $$
>
> - $n\leq 10^6$。

## 解题思路

挺妙的题目。

我们可以先化一下式子，变成 
$$
\sum_{i=1}^n (b_i-\dfrac{a_i}{2})^2-\sum_{i=1}^n \dfrac{a_i^2}{4}
$$
右边显然是定值，我们只要左边尽可能小，假设 $A_i=\dfrac{a_i}{2}$。

我们先观察一下 $n=2$ 的情况，有两种情况：

- $A_1<A_2$ 那么取 $b_i=A_i$ 即可。
- 否则应该取 $b_i=\dfrac{A_1+A_2}{2}$。

也许我们可以观察到这样的情况，其实每个 $b_i$ 最理想的取值是 $A_i$，但是为了要满足单调不减的性质取不到 $A_i$。这个时候就应该和他的邻居一个取值。那么这个时候他的邻居也会受到影响，原来是可以取到 $A_i$ 的因为邻居的偏袒不得不取一个其他值使得总和最小。

我们不难发现，当我们要一段**极长**连续区间 $b[l,r]$ 取一个相等的数 $x$ 的时候，这个时候必然有：
$$
x=\dfrac{1}{r-l+1}\sum_{i=l}^r A_i
$$

> **证明：** 不难发现原式相当于 $\sum(x-A_i)=(r-l+1) x^2-2(r-l+1) \overline A x+C$，这里 $C$ 为常数，不难发现当 $x$ 取 $\overline A$ 时最小。

那有没有可能这个求出 $x$ 不满足不降呢？实际上如果不满足，也就是说 $x$ 取极大极小值的时候原式更小，那么这个时候，他就会和邻居一个数值，不满足极长。

我们最后只需要求出来这个 $b$ 即可。

考虑单调栈维护，每个位置维护一个极长区间的长度、数值 $len,x$，每次先进入一个 $(1,A_i)$ 如果当前栈末尾不满足单调的性质就不断向前一位合并，直到单调或只有一个元素位置。

至此我们就完成了这道题。

## 参考代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1e6+5;
int n;
double a[MAXN],ans;
struct node{
	int len;double val;
	node (int le=0,double va=0){len=le,val=va;}
}st[MAXN];int cnt=0;
node merge(node x,node y){
	return node(x.len+y.len,(x.len*x.val+y.len*y.val)/(x.len+y.len));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i]);
		a[i]/=2;
	}
	for(int i=1;i<=n;i++){
		st[++cnt]=node(1,a[i]);
		while(cnt>1&&st[cnt].val<st[cnt-1].val)
			st[cnt-1]=merge(st[cnt],st[cnt-1]),--cnt;
	}
	int l=0;
	for(int i=1;i<=cnt;i++)
		while(st[i].len--){
			++l;
			ans+=(st[i].val*(st[i].val-2*a[l]));
		}
	printf("%.9f",ans);
	return 0;
}
```



---

## 作者：WRT_Partisan (赞：3)

## 题意简述
已知序列 $\{a_n\}$，求使 $\sum_{i=1}^nb_i(b_i-a_i)$ 最小的单调不减序列 $\{b\}$，输出 $\sum_{i=1}^nb_i(b_i-a_i)$ 的值。

## 题目分析
首先考虑：已知 $a$，求使 $b(b-a)$ 最小的 $b$。

将 $\sum_{i=1}^nb_i(b_i-a_i)$ 变形：

$$
\begin{aligned}
    \sum_{i=1}^nb_i(b_i-a_i) &= \sum_{i=1}^nb^2_i-a_ib_i \\
    &= \sum_{i=1}^n(\dfrac {a_i}2-b_i)^2-\dfrac {a_i^2}4 \\
    &= \sum_{i=1}^n(\dfrac {a_i}2-b_i)^2-\sum_{i=1}^n\dfrac {a_i^2}4
\end{aligned}
$$
因为 $\sum_{i=1}^n\dfrac {a_i^2}4$ 是个定值，所以只需要 $\sum_{i=1}^n(\dfrac {a_i}2-b_i)^2$ 最小。可以发现，当 $b_i=\dfrac {a_i}2$ 时，$\sum_{i=1}^n(\dfrac {a_i}2-b_i)^2$ 最小。

但是，题目要求 $\{b\}$ 是一个单调不减的序列，所以接下来我们考虑 $n=2$ 的情况。

当 $n=2$ 时，如果 $a_1\le a_2$，因为 $b_1=\dfrac {a_1}2,b_2=\dfrac {a_2}2$，所以 $b_1\le b_2$，满足单调不减。但是如果 $a_1>a_2$，就不能使 $b_1=\dfrac {a_1}2,b_2=\dfrac {a_2}2$，需要如下操作：

当 $n=2$ 时，$\sum_{i=1}^n(\dfrac {a_i}2-b_i)^2=(\dfrac {a_1}2-b_1)^2+(\dfrac {a_2}2-b_2)^2$。我们发现，$(\dfrac {a_1}2-b_1)^2+(\dfrac {a_2}2-b_2)^2$ 就是点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 到点 $(b_1,b_2)$ 的距离的平方，所以我们要让点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 到点 $(b_1,b_2)$ 的距离最小。

![](https://pic.imgdb.cn/item/67131d66d29ded1a8ce524c3.png)

建立一个平面直角坐标系。

因为 $a_1>a_2$，所以点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 一定在直线 $y=x$ 的下方；因为 $b_1\le b_2$，所以点 $(b_1,b_2)$ 一定在直线 $y=x$ 的上方（包括直线）。

所以点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 到点 $(b_1,b_2)$ 的最小距离是点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 到直线 $y=x$ 的垂线段（垂线段最短）。

因为点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 到点 $(\dfrac {a_1}2,\dfrac {a_1}2)$ 的距离和点 $(\dfrac {a_1}2,\dfrac {a_2}2)$ 到点 $(\dfrac {a_2}2,\dfrac {a_2}2)$ 的距离都等于 $a_1-a_2$，根据三线合一，可得 $(b_1,b_2)$ 是 $(\dfrac {a_1}2,\dfrac {a_1}2)$ 和 $(\dfrac {a_2}2,\dfrac {a_2}2)$ 的中点。

所以 $b_1=b_2=\dfrac {\dfrac {a_1}{2}+\dfrac{a_2}{2}}{2}$，也就是 $\dfrac {a_1}{2}$ 和 $\dfrac {a_2}{2}$ 的平均值。

我们用单调栈来维护 $\{b\}$ 的单调性。单调栈中的每一项为 $(size,b)$，$size$ 指的是当前这一段的长度，$b$ 指的是这一段 $b$ 的值。每次将 $(1,\dfrac {a_i}2)$ 入栈，如果 $\dfrac {a_i}2$ 小于前一项的 $b$，那么将这一项取出和要入栈的 $(1,\dfrac {a_i}2)$ 进行合并操作（取平均值），将合并后的项入栈并重复上述操作。

在所有的 $a_i$ 都入栈后，单调栈每一项的 $\sum_{i=l}^rb_i(b_i-a_i)$ 和就是答案。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node{int s;double b;};
int n,top,cnt;
double a[1000005],ans;
Node st[1000005];
int main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> a[i];
		st[top++]=(Node){1,a[i]/2};
		while (top>1 && st[top-1].b<st[top-2].b)
			st[(--top)-1]=(Node){st[top-1].s+st[top].s,(st[top-1].s*st[top-1].b+st[top].s*st[top].b)/(st[top-1].s+st[top].s)}; 
	}
	for (int i=0;i<top;i++)
		for (int j=1;j<=st[i].s;j++)
			ans+=st[i].b*(st[i].b-a[++cnt]);
	cout << fixed << setprecision(7) << ans;
	
	return 0;
}
```

---

## 作者：Tauber (赞：1)

## 分析题目
### 若a为不减序列
在仅考虑一组数值 a , b 时存在函数 $ f(b)=b(b-a)$ ，其中 a 为定值。根据初中数学二次函数的相关概念可得 
- $ f(b)_{min}=f(\frac{a}{2})$  


由此我们便可以推广到对于任意不减序列 a 都有唯一确定的不减序列 b 使得联合权值 $unval(a,b)$ 最小，此时 $b_i=\frac{a_i}{2}$ 。
### 在a的单调性不能保证时
将等式变形，得到
- $unval(a,b)=\sum_{i=1}^n (b_i-\dfrac{a_i}{2})^2-\sum_{i=1}^n \dfrac{a_i^2}{4}$

假设一组数据 $a_1$ ，$a_2$ ，$b_1$ ，$b_2$ 满足 $a_1>a_2$ 且 $b_1\le b_2$ 。  
不难发现此时的联合权值 $unval(a,b)$ 与 $(b_1-\dfrac{a_1}{2})^2+(b_2-\dfrac{a_2}{2})^2$ 成正相关，由平面间两点距离公式 $ |AB|=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 可得 $(b_1-\dfrac{a_1}{2})^2+(b_2-\dfrac{a_2}{2})^2$ 是点 $(b_1,b_2)$ 与点 $(\frac{a_1}{2},\frac{a_2}{2})$ 距离的平方。

因为 $a_1>a_2$ 且 $b_1\le b_2$ ，所以点 $(b_1,b_2)$ ，点 $(\frac{a_1}{2},\frac{a_2}{2})$ 分居直线 $y=x$ 两侧，因此当点 $(b_1,b_2)$ 与点 $(\frac{a_1}{2},\frac{a_2}{2})$ 的连线与直线 $y=x$ 垂直，即 $b_1=b_2=\frac{\frac{a_1}{2}+\frac{a_2}{2}}{2}$ 时两点距离最小，由此推广到整个序列 a ， b 。此时联合权值 $unval(a,b)$ 取到最小值。
## 实现方式
### 单调栈
由b序列单调不减的特性联想到单调栈，维护一个单调栈，在a序列单调不减时将 $\frac{a_i}{2}$ 作为 $b_i$ 入栈，否则不断弹栈至满足单调性，并计算其平均值再入栈。
### 压缩
不难发现，如果将每一个 $b_i$ 作为单独的元素入栈会产生大量相邻的重复元素而造成资源浪费，因此可以使用结构体仅将元素数值和长度入栈。
## 下附代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Stu{
	int l;
	double x;
}st[1000010];
int n,top;
double ans,ls[1000010];
int a[1000010];
void print()//检查b值是否正确
{
	for(int i=0;i<=top-1;i++)
	{
		cout<<st[i].x<<" "<<st[i].l<<endl;
	}
}
int main()
{
	cin>>n;
	cout<<fixed<<setprecision(7);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ls[i]=1.0*a[i]/2;
		if(top==0)
			st[top].l=1,st[top++].x=ls[i];
		else{
			int l=1;
			double sum=ls[i];
			while(sum/l<st[top-1].x&&top!=0)
			{
				l+=st[top-1].l;
				sum+=st[top-1].x*st[top-1].l;
				top--;
			}
			st[top].x=sum/l,st[top++].l=l;
		}
	}
	//print();
	int z=1;
	for(int i=0;i<=top-1;i++)
	{
		for(int j=1;j<=st[i].l;j++)
		{
			ans+=st[i].x*(st[i].x-a[z++]);
		}
	}
	cout<<ans;
	return 0;
 } 
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8879)

### 题目大意
对于两个序列 $a,b$，定义：
$$
\operatorname{unval}(a,b)=\sum_{i=1}^n b_i(b_i-a_i)
$$
现在给定序列 $a$，求一个序列 $b$，满足 $b$ 单调不减，且 $\operatorname{unval}(a,b)$ 的值尽可能小。
### 解题思路
将式子做以下变化：
$$
\operatorname{unval}(a,b)=\sum_{i=1}^n (b_i-\frac{a_i}{2})^2-\frac{a_i^2}{4}
$$
由于右边一项是不会随着 $b$ 变化的，我们现在目标是最小化：
$$
\frac{\sum_{i=1}^n (b_i-a_i')}{n}
$$
其中 $a_i'=\frac{a_i}{2}$。

考虑一个极端情况：$a_i'$ 单调不上升，可以发现原式最小时 $b_i$ 全取相同值：
$$
\operatorname{avg}=\frac{\sum_{i=1}^n a_i'}{n}
$$
现在由于 $a_i'$ 可能不是单调不上升，所以考虑将 $a_i'$ 划分成若干个连续子段，每段的平均值单调上升，
并且区间数尽可能的多。

用 **单调栈** 维护上述过程，栈内是若干个平均值单调增的区间。

当插入一个新区间时，若该区间的平均值比栈顶小，则与栈顶区间合并。

时间复杂度 $O(n)$。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
const int maxn=1e6+3;
int n;
db a[maxn];
struct node{
    db x,y;
}st[maxn];
bool cmp(node u,node v){
    return u.x/u.y>v.x/v.y;
}
int top=0;
int main(){
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        a[i]/=2;
    }
    for (int i=1;i<=n;i++){
        node cur=(node){a[i],1};
        while (top>0&&cmp(st[top],cur)){
            cur.x+=st[top].x;
            cur.y+=st[top].y;
            top--;
        }
        st[++top]=cur;
    }
    db ans=0;
    for (int i=1;i<=top;i++){
        ans-=st[i].x/st[i].y*st[i].x;
    }
    printf("%.10f\n",ans);
}
```

---

## 作者：Union_of_Britain (赞：0)

据说是 Hanghang 验的题。牛逼！为什么题解区都是一种做法？

如果所有 $b_i$ 都和 $\frac{a_i}{2}$ 相等，那是最好的。现在 $b$ 具有不降的要求，我考虑把后缀 $[L,n]$ 加上 $dx$，答案不应增加；因此：

$$\sum_{i=L}^n b_i-\frac{a_i}2\ge 0$$

然而，在 $L=1$ 或者 $b_L>b_{L-1}$ 的位置减去 $dx$ 再结合上面的式子将得到：

$$\sum_{i=L}^n b_i-\frac{a_i}2= 0$$

因此，任何一个连续相等段全都取 $\frac{a}{2}$ 的平均值。根据不等式还得到：第一个 $b$ 一定 $\le \frac a2$。

在调整过程中，容易证明我一定不会拆开某一段。因此，我只需考虑一个下降的数对前面数的改变；

方法是不断向前取平均值直到满足递增性质。

我们证明这是最优的：如果不取足够，不符合条件（为什么不此时调整前面的，类似地参见下一段）；取多了，不符合第一个 $b\le \frac a2$ 的条件。

正好取在这个位置 $p$ 的时候，注意到此时对 $1\sim p-1$ 的递增限制变严了，如果有 $1\sim p-1$ 的改变一定可以在上一次执行，因此 $1\sim p-1$ 不会改变。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
double A[maxn],s[maxn],b[maxn];
int n;
stack<pair<int,int> > st;
double calc(pair<int,int> p){
	return (s[p.second]-s[p.first-1])/(p.second-p.first+1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>A[i];A[i]/=2;
		s[i]=s[i-1]+A[i];
	}
	for(int i=1;i<=n;i++){
		int l=i;
		while(st.size()&&calc(st.top())>calc({l,i})){
			l=st.top().first;
			st.pop();
		}
		st.push({l,i});
	}
	while(!st.empty()){
		pair<int,int> p=st.top();
		for(int i=p.first;i<=p.second;i++)b[i]=calc(p);
		st.pop();
	}
	double ans=0;
	for(int i=1;i<=n;i++)ans+=b[i]*(b[i]-2*A[i]);
	printf("%.10lf\n",ans);
	return 0;
}

```

---

