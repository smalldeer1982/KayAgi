# Bricks and Bags

## 题目描述

There are $ n $ bricks numbered from $ 1 $ to $ n $ . Brick $ i $ has a weight of $ a_i $ .

Pak Chanek has $ 3 $ bags numbered from $ 1 $ to $ 3 $ that are initially empty. For each brick, Pak Chanek must put it into one of the bags. After this, each bag must contain at least one brick.

After Pak Chanek distributes the bricks, Bu Dengklek will take exactly one brick from each bag. Let $ w_j $ be the weight of the brick Bu Dengklek takes from bag $ j $ . The score is calculated as $ |w_1 - w_2| + |w_2 - w_3| $ , where $ |x| $ denotes the absolute value of $ x $ .

It is known that Bu Dengklek will take the bricks in such a way that minimises the score. What is the maximum possible final score if Pak Chanek distributes the bricks optimally?

## 说明/提示

In the first test case, one way of achieving a final score of $ 6 $ is to do the following:

- Put bricks $ 1 $ , $ 4 $ , and $ 5 $ into bag $ 1 $ .
- Put brick $ 3 $ into bag $ 2 $ .
- Put brick $ 2 $ into bag $ 3 $ .

If Pak Chanek distributes the bricks that way, a way Bu Dengklek can take the bricks is:

- Take brick $ 5 $ from bag $ 1 $ .
- Take brick $ 3 $ from bag $ 2 $ .
- Take brick $ 2 $ from bag $ 3 $ .

The score is $ |a_5 - a_3| + |a_3 - a_2| = |3 - 5| + |5 - 1| = 6 $ . It can be shown that Bu Dengklek cannot get a smaller score from this distribution.

It can be shown that there is no other distribution that results in a final score bigger than $ 6 $ .

## 样例 #1

### 输入

```
3
5
3 1 5 2 3
4
17 8 19 45
8
265 265 265 265 265 265 265 265```

### 输出

```
6
63
0```

# 题解

## 作者：lenlen (赞：19)

看到没人写题解，我来写一个。

### Problem

题目大意：你有一个序列 $a$，需要把它分成三组（不能为空），另一个人会在你的三组数里面各选一个数 $x,y,z$，他会使得价值 $\lvert x-y \rvert+\lvert y-z \rvert$ 最小，你需要使这个最大化最小的价值。

数据范围： $t \leq 10^4,\sum n \leq 2 \times 10^5,a_i \leq 10^9$。

### Solution

其实这个题目想到了就很简单了，首先不妨设 $x \geq z$，这个肯定是没有影响的，那么显然， $y$ 就有三种情况：

$$w=\begin{cases}
	& x+z-2y & (y<z)\\
    & x-z & (z \leq y \leq x)\\
    & 2y-x-z & (y \geq x)
\end{cases}$$

我们可以把 $a$ 数组排序。

首先我们可以排除掉第二种情况，因为我们可以发现，第二种情况最大化就是第一组放最大的数，第三组放最小的数，那么价值为最大值减最小值；而显然若我们在第二组放最大的数，第三组放最小的数，那么显然价值会大于等于最大值减最小值，所以第二种情况我们可以不考虑。

我们考虑第一种情况，首先我们显然可以在第一组只放最大值，然后枚举 $i$，第二组放 $a_1,a_2,\cdots,a_i$，剩下的放第三组，那么显然，另一个人会让我们的价值最小，所以 $w=a_n+a_{i+1}-2 \times a_i$。

第三种情况类似，只不过我们是先确定第三组内只放最小的数。然后同样枚举， $w=2 \times a_i-a_{i-1}-a_1$。

取最大值即可。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7232;
long long T,n,a[N],ans,num;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        sort(a+1,a+n+1);
        ans=0;
        for(int i=3;i<=n;i++) ans=max(ans,2*a[i]-a[i-1]-a[1]);
        for(int i=1;i<n-1;i++) ans=max(ans,a[n]+a[i+1]-2*a[i]);
        printf("%lld\n",ans);
    }
}
```


---

## 作者：Utopioa_iris (赞：0)

##  CF1740C Bricks and Bags 题解
### 题目大意：
输入一个序列长度为 $n$ 的序列 $a$，将其分为三段，一位朋友会选出 $x,y,z$，使得价值 $|x-y|+|y-z|$ 最小，而我们的任务是让此数尽可能大。
### 思路：
先简化式子：$w=|x-y|+|y-z|$。

这里我们将其拆分为两个模块 $|x-y|$ 和 $|y-z|$，分别设它为 $a$ 和 $b$：

先看 $a=|x-y|$：

$$\begin{cases} a=x-y & x \ge y \\ a=-x+y & x<y& \end{cases}$$

然后看 $b=|y-z|$：

$$\begin{cases} b=y-z & y \ge z \\ b=-y+z & y<z& \end{cases}$$

合起来就是：

$$\begin{cases} w=x-y+y-z=x-z & x \ge y \ge z \\ w=-x+y+y-z=2y-x-z & y \ge x,y\ge z  \\ w=x-y-y+z=x+z-2y & x \ge y,y \ge z \\w=-x+y-y+z=z-x & x<y<z & \end{cases}$$

那么逐步分析这些情况：

情况一与四相同，只是数字大小的变化，视为同一情况。而这种情况显然不是最优，最好情况下为最大值减去最小值，而若把 $x$ 和 $y$ 的值交换，也就是成为情况二，显然更优。

那么只需讨论情况二和三，情况二中，我们要使 $2 \times y$ 最大，使 $x$ 和 $z$ 尽可能小，排好序后将数列枚举一遍，就可以了。而情况三也一样，使 $y$ 尽可能小就行了。
### 代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1000001],ans; 
signed main()
{
	cin>>t;
	while(t--) 
	{
		ans=0;//记得多测重置 
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+n+1);//排序 
		for(int i=3;i<=n;i++) //避免数组越界，x和z重复，从3开始 
			ans=max(ans,2*a[i]-a[i-1]-a[1]);//当w=2y-x-z时，使z最小 
		for(int i=1;i<n-1;i++) //避免数组个数超过n 
			ans=max(ans,a[n]+a[i+1]-2*a[i]);//当w=x+z-2y时，使x最大 
		cout<<ans<<endl;
	} 
	return 0;//完美收工 
} 
```
### 谢谢大家

---

## 作者：_QWQ__QWQ_ (赞：0)

~~众所周知，这道题的难度是 1400，所以是简单题。~~

## 分析
首先，坚信这是一道简单题，所以不要想复杂了。

首先我们需要对 $ a $ 数组排序，这点是肯定的，为啥应该不用我解释。

下面，我们假设 $ p_1, \;p_2,\; p_3 $ 分别为朋友在第 $ 1 $ 个，第 $ 2 $ 个和第 $ 3 $ 个背包中选择的棍子下标（注意，这里的下标都是指的排序后的数组下标）。我们可以发现，所有的分类情况下一定会满足下列四种条件之一：
 
$ \begin{cases}
  p_1<p_2<p_3\\
  p_1>p_2>p_3\\
  \min(p_1,p_3)>p_2\\
  \max(p_1,p_3)>p_2\\
\end{cases}
$

翻译一下，这四种情况的答案分别是：

$ ans=\begin{cases}
 (a_{p2}-a_{p1})+(a_{p3}-a_{p2})\operatorname{if} p_1<p_2<p_3\\
  (a_{p3}-a_{p2})+(a_{p2}-a_{p1})\operatorname{if} p_1>p_2>p_3\\
  (a_{p1}-a_{p2})+(a_{p3} -a_{p2})\operatorname{if}\min(p_1,p_3)>p_2\\
  (a_{p2}-a_{p3})+(a_{p2} -a_{p1})\operatorname{if}\max(p_1,p_3)<p_2\\
\end{cases}
$

你感性理解一下，你就会发现前两种情况一定不会比后两种优（因为如果出现这两种情况，你只需要将其中两个背包交换一下位置就会转化为后面两种，而明显转化后会更优，这个你自己手模一下应该很显然），于是我们就只用考虑后面两种情况就可以了,即:

$ ans=\begin{cases}
  (a_{p1}-a_{p2})+(a_{p3}-a_{p2})\operatorname{if}\min(p_1,p_3)>p_2\\
  (a_{p2}-a_{p3})+(a_{p2} -a_{p1})\operatorname{if}\max(p_1,p_3)<p_2\\
\end{cases}
$

但是你会发现，即使是这样，我们任然不能很好的限制计算方法，于是我们考虑继续加强条件。

下面我们以第三种情况为例加强限制（第四种的推理过程是一样的）：

我们假设有 $ \min(p_1,\;p_3) > p_2 + 1 $（注意这里的都是下标之间的关系），我们分下列三种情况分析（注意，我们下面的讨论都基于我们假设朋友一定会选 $ p_1,\;p_2,\;p_3 $ 的基础上）：

1. 如果 $ p_2 + 1 $ 这根棍子被放在了第 $ 1 $ 个背包中，那么朋友在背包 $  1 $ 中选择下标为 $ p_2 + 1 $ 的棍子而不是 $ p_1 $，因为 $ a_{p_2 + 1} - a_{p_2} \leqslant a_{p_1} - a_{p_2} $，因此假设不成立；
2. 如果 $ p_2 + 1 $ 这根棍子被放在了第 $ 2 $ 个背包中，那么朋友在背包 $  2 $ 中选择下标为 $ p_2 + 1 $ 的棍子而不是 $ p_2 $，因为 $ (a_{p_1} - a_{p_2 + 1}) + (a_{p_3} - a_{p_2 + 1}) \leqslant (a_{p_1} - a_{p_2}) + (a_{p_3} - a_{p_2} )$，因此假设不成立；
3. 如果 $ p_2 + 1 $ 这根棍子被放在了第 $ 3 $ 个背包中，那么朋友在背包 $  3 $ 中选择下标为 $ p_2 + 1 $ 的棍子而不是 $ p_3 $，因为 $ a_{p_2 + 1} - a_{p_2} \leqslant a_{p_3} - a_{p_2} $，因此假设不成立。

于是我们发现，在 $ \min(p_1,\;p_3) > p_2 + 1 $ 时，朋友一定不会选择我们给他“指定”的那三个棍子，于是我们把条件收束为：

$ ans=\begin{cases}
  \min(p_1,p_3)>p_2  \& \min(p_1,p_3)=p_2+1\\
  \max(p_1,p_3)<p_2  \& \max(p_1,p_3)=p_2-1\\
\end{cases}
$

的时候我们才能确定朋友所选取的棍子就是我们“指定”的那三根。

这个条件化简一下其实就是：

$ ans=\begin{cases}
  \min(p_1,p_3)=p_2+1\\
  \max(p_1,p_3)=p_2-1\\
\end{cases}
$

而我们需要最大化 $ |a_{p_2}-a_{p_1}|+|a_{p_3} - a_{p_2}| $，于是我们很显然将 $ \min(p_1,\;p_3) $ 定为 $ 1 $ 或者让 $ \max(p_1,\;p_3) $ 为 $ n $，这样我们得到的解一定最优（注意此时我们是在计算答案，这里的 min 和 max 与上式中并不表同一含义，具体看下面的式子）。但是此时我们也只是确定了其中一边的取值，那么另一边枚举就行了，于是我们有以下计算式：

$ ans=\max\begin{cases}
  \max^n_{i=3}\{(a_i-a_1)+(a_i-a_{i-1})\}\text{此时的排列是1,i~n,2~i-1} \\
   \max^{n-2}_{i=3}\{(a_n-a_i)+(a_{i+1}-a_{i})\}\text{此时的排列是n,1~i,i+1~n-1}  \\
\end{cases}
$

于是我们就做完了，对就是这么简单，区区 1400 而已，是真的不能把他想的太难了，不然真的很容易想偏。

## 附源码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a[10000];
int main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=3;i<=n;i++){
			ans=max(ans,a[i]-a[1]+a[i]-a[i-1]);//1,i~n,2~i-1
		}
		for(int i=1;i<=n-2;i++){
			ans=max(ans,a[n]-a[i]+a[i+1]-a[i]);//n,1~i,i+1~n-1
		}
		printf("%d\n", ans);
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

### 题目大意

有一堆物品，每个物品有一个价值。一个人把这堆东西放进三个袋子里（每个袋子不为空，且保证至少有三个物品），另一个人要在三个袋子中分别取一个物品。设这三个物品价值为 $x$、$y$ 和 $z$，总价值为 $\left\vert x-y\right\vert+\left\vert y-z\right\vert$。取出时会**最小化**总价值，求怎么放能使总价值**最大**。

### 分析

因为总价值和绝对值有关，所以可以分类讨论绝对值的正负，也就是值的大小关系。我们看到式子里 $y$ 出现了两次，就可以讨论 $y$ 的大小。

可以先设 $x \geqq z$，则有以下三种情况：

1. $y$ 小于 $x$ 和 $z$，总值为 $x+z-2y$。 

1. $y$ 大于 $x$ 和 $z$，总值为 $2y-x-z$。 

1. $y$ 在 $x$ 和 $z$ 之间，总值为 $x-z$。

而第三种情况明显不是最优，因为把 $x$ 和 $y$ 的值交换就能得到更优的方案，所以只需要枚举 $y$，求出第一种和第二种情况的最大值，然后比较即可。

具体实现在代码里。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 114514
#define M 1919810
#define ll long long
#define INF 2147483647000000
ll t,n,a[M];
int main(){
	cin>>t; //注意t组数据 
	while(t--){
		cin>>n;
		ll ans=-INF,ans_=-INF;
		for(int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1);
		//因为取出时要最小化总值，所以直接取排序后的数组里的前或后一个值 
		for(int i=1;i<=n-2;++i) ans_=max(ans_,a[n]+a[i+1]-2*a[i]);  //第一种，若要最大化总值则肯定要取最大值 
		for(int i=3;i<=n;++i) ans=max(ans,2*a[i]-a[1]-a[i-1]);      //第二种，相反与第一种，取最小值 
		//注意枚举范围（第二种情况理论上应从3开始枚举，但亲测2也可以）
		cout<<max(ans,ans_)<<'\n';
	}
	return 0;
}
```


---

## 作者：Daidly (赞：0)

很不错的一道思维题。

考虑 $w_1,w_2,w_3$ 之间的关系：

- 若 $w_1<w_2<w_2$ 或 $w_1>w_2>w_3$，则 $|w_1-w_2|+|w_2-w_3|=|w_1-w_3|\leq \max a_i-\min a_i$

- 对于剩下的所有情况都有 $|w_1-w_2|+|w_2-w_3|>|w_1-w_3|$，不妨令 $w_1=\max a_i,w_2=\min a_i$，则可以构造出比上面两种情况更大的答案。

由于 $w_1,w_3$ 可以调换对答案无影响，不妨设 $w_1<w_3$，则有：$w_2<w_1<w_3$ 和 $w_1<w_3<w_2$ 两种情况。

考虑策略：

- 若要使 $w_2<w_1<w_3$ 成立，则需要集合 $2$ 中的最大值小于集合 $1$ 中的最小值，集合 $1$ 中的最大值小于集合 $3$ 中的最小值。

- 若要使 $w_1<w_3<w_2$ 成立，则需要集合 $1$ 中的最大值小于集合 $3$ 中的最小值，集合 $3$ 中的最大值小于集合 $2$ 中的最小值。

由以上分析可知，我们在三个集合中选择的肯定是一段前缀后缀或者中间连续的（$a_i$ 排序后，下文也是）。而对于集合 $2$，一定是一段前缀或后缀，分别枚举集合 $2$ 的前后缀即可。

- 对于集合 $2$ 是一段前缀，则使最终答案最大的策略是在集合 $3$ 中只放一个数 $a_n$，其余放在集合 $1$。答案是 $\max\limits_{i=1}^{n-2}(a_{i+1}-a_i+a_n-a_i)$.

-  对于集合 $2$ 是一段前缀，则使最终答案最大的策略是在集合 $3$ 中只放一个数 $a_n$，其余放在集合 $1$。答案是 $\max\limits_{i=3}^{n}(a_{i}-a_{i-1}+a_i-a_1)$.

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2e5+5;
int t,n,a[N];

signed main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;++i)a[i]=read();
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=1;i<=n-2;++i)ans=max(ans,a[i+1]-a[i]+a[n]-a[i]);
		for(int i=n;i>=3;--i)ans=max(ans,a[i]-a[i-1]+a[i]-a[1]);
		print(ans),puts("");
	}
	return 0;
}
```

---

