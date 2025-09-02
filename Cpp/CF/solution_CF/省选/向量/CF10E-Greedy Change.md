# Greedy Change

## 题目描述

给定 $n$ 种货币，每种货币数量无限。 现在要求以最少的货币数目表示一个数 $S$。 一种方法当然是 DP 求一个最优解了， 当然正常人的做法是贪心：每次取最大的不超过当前待表示数的货币。 现在，你的任务是证明正常人的表示法不一定最优：找到最小的 $S$，使得正常人的表示法比理论最优解差，或说明这样的 $S$ 不存在。

## 样例 #1

### 输入

```
5
25 10 5 2 1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3
4 3 1
```

### 输出

```
6
```

# 题解

## 作者：kczno1 (赞：44)

完全不会，  
看了论文A polynomial-time algorithm for the change-making problem后大概懂了，  
来叙述一下论文的意思。    

将原来的硬币系统记作向量$C=(c_1,c_2,...,c_n)$，满足$c_1>c_2>...>c_n$,且$c_n=1$    
将对价值x的一个表示记作向量V，即满足$V·C=x$  
将V用到的硬币数目记作size,即$size=V·(1,1,...,1)$  
将对x的贪心表示记作G(x),满足字典序最大    
将对x的最小表示记作M(x),满足size最小的前提下字典序最大    
易证一个贪心表示的子集也是一个贪心表示，一个最小表示的子集也是一个最小表示。  

令w为最小反例，即最小的w使得G(w)!=M(w)  
易证G(w)和M(w)的非零位集合无交  
令i和j为M(w)最小和最大的非零位  
有结论:$M(w)$和$G(c_{i-1}-1)$的1..j-1位相同，第j位大1  

证明:  
$G(w)$在1..i-1位上一定有非零位，所以$w>=c_{i-1}$  (1)

因为w是最小的反例，  
所以$G(w-c_j)=M(w-c_j)$，  
而$M(w-c_j)$就是$M(w)$在第j位上-1, 其他位都是一样的  
所以$M(w-c_j)$的前 $i-1$ 位为0  
所以$G(w-c_j)$的前 $i-1$ 位也为0  
所以$w-c_j<c_{i-1}$  (2)

由(1)有$c_{i-1}-1-c_{i}<w-c_{i}$    
所以$G(c_{i-1}-1-c_{i})<G(w-c_{i})=M(w-c_{i})$  
两边都给第i位加1，得$G(c_{i-1}-1)<M(w)$ (3)

由(2)有$w-c_{j}<=c_{i-1}-1$  
所以$G(w-c_{j})<=G(c_{i-1}-1)$  
所以$M(w-c_{j})<=G(c_{i-1}-1)$ (4)

结合(3),(4)  
可以发现本来$M(w)>G(c_{i-1}-1)$，但把第j位减1之后就 $\le$ 了  
说明他们j位之前相等  
而$M(w)$在j位之后都是0  
说明$M(w)$的第j位比$G(c_{i-1}-1)$大1

所以可以枚举$n^2$种i,j，然后$O(n)$判断，复杂度$O(n^3)$  

```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'-');
    if(c=='-')
    {
        int x=gc-'0';
        while(gc>='0')x=x*10+c-'0';
        return -x;
    }
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc

const int N=400+5,inf=2e9;
int n,c[N];
int ans=inf;
int G(int x)
{
	int ans=0;
	rep(i,1,n)
	{
		int d=x/c[i];
		ans+=d;
		x-=c[i]*d;
	}
	return ans;
}

int main()
{
	freopen("1.in","r",stdin);//freopen("1.out","w",stdout);
	n=read();
	rep(i,1,n)c[i]=read();
	rep(i,2,n)
	{
		int x=c[i-1]-1;
		int x0=x;
		int m=0;
		rep(j,i,n)
		{
			int d=x/c[j];
			m+=d;
			x-=c[j]*d;
			if(m+1<G(x0-x+c[j]))
				chmin(ans,x0-x+c[j]);
		}
	}
	if(ans==inf)puts("-1");
	else cout<<ans<<endl;
}
```

---

## 作者：WinterRain208 (赞：41)

$Greedy Change$题解

### 写在前面的话

这题码力要求不大，思维难度极强，不要看代码短，但评黑当之无愧。

之前题解大部分对代码部分解释不是很详细，导致包括我在内的很多人看不懂。

今天斗胆试试给出一个合理的解释。

### 题意

给你若干币值，要你求在这个币值系统下贪心算法求找零问题是不是最优的。

如果是，输出$-1$，否则输出能使贪心算法挂掉的最小钱数。

### 硬币问题的导入

首先题面中提到了两种硬币问题的算法，当然$dp$才是正解。再将这道题之前，我们需要来看看经典的硬币问题：

有$n$种硬币，面值为$a_1$到$a_n$，求组成给定价值$v$至少需要几个硬币。

考虑**贪心**算法。

策略：将$a$降序排列，然后从前往后扫，对于每个$a_i$，尽可能换，就是将$v$变成$v%$$a_i$，然后给计数器加上$v/$$a_i$。

但对于下面这组例子（取自本题）就是错误的。

```
3 6
4 3 1
```

贪心给出的答案是$3$$(4+1+1)$，但正解是$2$$(3+3)$。

考虑如何$dp$，设状态$dp_i$为面值为$i$时最少需要的硬币个数，那转移方程就是：

```cpp
dp[j]=min(dp[j]，dp[j-a[i]]+1);
```

当然我们要用双层循环。这就是硬币问题的最初版 。

也有非常多的变形，这里不一一赘述。

### 做法

本题算法：枚举法。

考虑直接枚举，但没有边界，而且$a_i$是非常大的，这方法肯定不行。

那么我们来考虑如何求出边界或者找出有选择性枚举的方法。这里我们选择后者。

对于一种币值 $A$ ，我们找出一个略大于 $A$ 仅用币值不小于 $B$ 且小于 $A$ 的货币表示的值 $X$
使得贪心算法在使用 $A$ 后要用更多零碎的货币

上面引用自楼上题解，我们围绕这句话做解释。

先讲讲这个略大于，原题解表述的不是很清楚。

$B <= 2A$且$X$不是$B$的倍数 。

先证前者，很容易举出反例：

$A=70,B=241,X=242$。

再考虑后者，首先，$X$必不能是$B$的倍数，不然因为$A>B$,这肯定不是最优解。

然后再讲这个句子的后半段，零碎的货币指在用完贪心算法之后 ，本来是$A$的倍数的$V$不能再整除$A$。

其他的细节请参考注释理解。

### $CODE$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,r) for(int i=j;i<=r;++i)//这里为了理解在代码中就不使用了 。
#define D(i,j,r) for(int i=j;i>=r;--i)
#define INF 0x3f3f3f3f

using namespace std;
const int N=1e5+5;

long long read(){//快读
	long long f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	return x*f;
}

inline void write(ll x){//快写
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}

ll n;//n:币值总数
ll a[410],ans=-1; //a：币值，ans：最小反例（答案）
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();//读入
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			int cnt1=1,cnt2=0,pos=a[i]-1,t;
        		//cnt1：非贪心算法下对于指定币值v的最优解。
              		//cnt2：贪心算法下对于指定币值v的最优解。
                    	//pos：枚举的 v
                        //t：同样是v，因为要计算两次所以要保存一个
			for(int k=i+1;k<=j;k++)
				cnt1+=(pos/a[k]),pos%=a[k];//非贪心
			t=pos=a[i]-1-pos+a[j];//适当减去答案为a[j]倍数
            		//不难看出，执行以上非贪心做法时pos可能最后不为零，这里减去它是为了调整答案，缩小误差
			for(int k=1;k<=n;k++)
				cnt2+=(pos/a[k]),pos%=a[k];//贪心求解
			if(cnt1<cnt2 && (ans==-1||ans>t))//判断
				ans=t;
		}
	write(ans);//输出
    return 0;
}
```

### 后记

如果看了以上代码和解释 还是不懂我认为 很正常，一方面我学艺不精，其次这题思维难度真的很高。

我当时在理解时就是盯着$std$一行一行看，思考每个语句和变量的 作用才理解 。

祝$AC$。

（其实这种题涉及到很多的证明，大胆猜想不要怕错）。

题解撰写不易，点个赞吧。

---

## 作者：shucai (赞：17)

## [题目传送门](https://www.luogu.com.cn/problem/CF10E)

### 题意

给定 $n$ 种货币，每种货币数量无限，用这些货币表示一个数 $S$，求**最小**使贪心不是最优解的数 $S$。

### 思路

本题我们可以用枚举法求解，但直接暴力枚举肯定不行，考虑优化。

我们可以对**枚举对象**进行选择，可以这样想：

贪心算法的流程是优先选择更大的（货币），**然后再用零碎的货币**，我们可以找到这样一个数$S$,使它接近于货币 $a_i$，并且只用小于 $a_i$ 且大于(或等于）$a_j$ 的货币表示，这样就可以在使用贪心的情况下，这个数 $S$ 用了货币**可以使用的最大货币**后，只能使用**更多零碎的货币**。

### **code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int data[10101];
signed main() {
    int n;
    cin >> n;
    int ans = -1;;

    for (int i = 1; i <= n; i++)
        cin >> data[i];

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
        //每次选定一个区间，区间的两端同分析的a[j]和a[i]
            int fans = 0, tans = 1, mod = data[i] - 1, mod_2;
// mod为枚举的S
            for (int k = i + 1; k <= j; k++) {
                tans = tans + mod / data[k];
                mod %= data[k];
            }//求非贪心结果

            mod_2 = mod = data[i] - 1 - mod + data[j];
//可以发现mod进行以上解法后可能不为0,也就是说我们求出来的的数是非法的,那我们就把余数减去,就成了一个合法解

            for (int k = 1; k <= n; k++) {
                fans = fans + mod / data[k];
                mod %= data[k];
            }//求贪心结果

            if (tans < fans && (ans == -1 || mod_2 < ans))
                ans = mod_2;
        }//判断

    cout << ans;
    return 0;
}
```
### 小结
此题思维难度极大，但只要反复琢磨，定可想出解法。

祝$A$。


---

## 作者：WarningQAQ (赞：13)

### 思路：
对于一种币值 $A$ ，我们找出一个略大于 $A$ 仅用币值不小于 $B$ 且小于 $A$ 的货币表示的值 $X$ ，

使得贪心算法在使用 $A$ 后要用更多零碎的货币
这样，只要枚举 $A$ 、 $B$ ，找出最小的这样的值即可。

$\large{\text{code\;:}}$


------------
```cpp
#include "cstdio"
int n, dat[500], res = -1;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &dat[i]);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			int cnt1 = 1, cnt2 = 0, W = dat[i] - 1, t;
			for (int k = i + 1; k <= j; k++) //非贪心做法
				cnt1 += (W / dat[k]), W %= dat[k];
			t = W = dat[i] - 1 - W + dat[j];
			for (int k = 1; k <= n; k++) //贪心做法
				cnt2 += (W / dat[k]), W %= dat[k];
			if (cnt1 < cnt2 && (res == -1 || res > t)) //判断
				res = t; 
		}
	printf("%d", res);
	return 0;
}
```


---

## 作者：傅思维666 (赞：11)

## 题解：

很新颖的题，虽然很老了。

让我们给出反例证明一个假的贪心是假的。

先说一下这个贪心什么时候是对的：假如我们可以加上或减去数列里的一个数，那么这个贪心就是对的。只有加法的话，不对。理由在样例二中已经给的很清楚了。

那么我们只需要模拟两个过程：一个是贪心（可能会假），另一个是自己枚举的反例，找到了就输出，没找到就输出-1.

然后我们思考什么时候可能会有这种假的情况：

找一个面值A，如果有一个比A大一些，但是另一个面值B的整数倍的钱数，那么就有可能使得先选A，剩下的就变得零碎，如果直接用整数个B凑，就能凑齐的情况。

所以我们三重枚举来模拟这个过程即可。

代码：

```cpp
#include<cstdio>
using namespace std;
int n;
int a[410],ans=-1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int cnt1=1,cnt2=0,yu=a[i]-1,t;
			for(int k=i+1;k<=j;k++)
				cnt1+=(yu/a[k]),yu%=a[k];
			t=yu=a[i]-1-yu+a[j];
			for(int k=1;k<=n;k++)
				cnt2+=(yu/a[k]),yu%=a[k];
			if(cnt1<cnt2 && (ans==-1||ans>t))
				ans=t;
		}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：Gmt丶FFF (赞：10)

一个非常离谱的题。

首先有结论，如果有 $w$ 使贪心不为最优解，那么比 $w$ 小的第一个 $a_i$，用贪心法求面值为 $a_i-1$，除了最后选的一个数 $a_j$ 会比原方法多选一个，其余与用动态规划求 $w$ 面值的选取方式一样。

理论求法过于多，这次我们选择一个通俗易懂的讲法。

如果我们用贪心，那么我们一定会取当前的最大值，那么如果贪心是错的那么我们就不会取当前最大值。

所以我们对于每一位 $a_i$，我们要寻找不选它更优的方案，假设贪心中选取 $a_i$ 后会选择 $a_j$，那么动态规划一定会选取 $a_{i+1}$ 到 $a_{j-1}$ 的数，如果选取比 $a_j$ 还小的数，那么一定不会是最优。

证明不会选比 $a_j$ 小的数：假设我们把贪心中足够个 $a_j$ 拆成数个 $a_k(k<j)$，那么把 $a_k$ 间互相抵消后，贪心中数只会增加不会减少，因为拆开一次 $a_j$，至少会有两个数出现。

所以我们只需找到最小的数满足只取 $a_{i+1}$ 到 $a_{j-1}$ 的数且刚好大于 $a_i$ 可以满足的最小的 $w$。

那么求这个就可以先枚举 $i$，$j$，然后贪心求解。

如何贪心求解呢，首先我们先用面值为 $a_i-1$ 去拼凑，保证这些数最后凑出来不大于 $a_i$，拼凑出来肯定会有余数，那么减去这个余数，加上 $a_{j-1}$，由于最后余数肯定小于 $a_{j-1}$，所以加上 $a_{j-1}$ 后一定会大于等于 $a_i$。

证明上述贪心正确：因为求出来的余数 $t$ 一定小于 $a_{j-1}$，所以补上那个余数最小花费为 $t-a_{j-1}$，不存在利用其他数相加得成。

而这下就会有人问，因为有可能加上一个 $a_{j-1}$ 会补成之前的一个数 $a_p$，其实这不影响，如果补了以后 $a_{j-1}$ 有剩余，实际上在之前求解就会补上，不存在在后来再补。如果没有剩余，这种解会枚举的时候 $i$ 到 $g(p<g<j)$ 时满足这种情况，所以穷举的方法使得算法正确。

然后利用 $O(n)$ 验证贪心的步数是否大于刚刚拼凑的总步数即可。

最后对于每个可行解，取最小值。

时间复杂度：$O(n^3)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=405;
int n,a[N],ans=2e9+5;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			int num=a[i]-1,sum=0;
			for(int k=i+1;k<=j;k++)
			{
				sum+=num/a[k];
				num%=a[k];
			}
			int lim=a[i]-1-num+a[j];
			sum++;
			int tot=0;
			for(int k=1;k<=n;k++)
			{
				tot+=lim/a[k];
				lim%=a[k];
			}
			if(sum<tot)ans=min(ans,a[i]-1-num+a[j]);
		}
	}
	if(ans==2e9+5)ans=-1;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：MiRaciss (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF10E)

对于[这篇题解](https://www.luogu.com.cn/blog/user9168/solution-cf10e)的解释

>将原来的硬币系统记作向量 $C=(c_1,c_2,...,c_n)$ ,满足$c_1>c_2>...>c_n$，且 $c_n=1$

>将对价值 $x$ 的一个表示记作向量 $V$ ，即满足 $V⋅C=x$ 

>将 $V$ 用到的硬币数目记作 $size$ ,即 $size=V⋅(1,1,...,1)$

>易证一个贪心表示的子集也是一个贪心表示，一个最小表示的子集也是一个最小表示。

~~我猜这不需要解释~~

>令 $w$ 为最小反例，即最小的 $w$ 使得 $G(w)!=M(w)$

>易证 $G(w)$ 和 $M(w)$ 的非零位集合无交

如果 $G(w)$ 和 $M(w)$ 的非零位有交，那么记 $G(w)$ 和 $M(w)$ 的非零位的相交为i，那么可以得到 $G(w-c_i)!=M(w-c_i)$ ，所以 $w$ 不是最小反例，$w-c_i$ 才是。

>令 $i$ 和 $j$ 为 $M(w)$ 最小和最大的非零位

>有结论: $M(w)$ 和 $G(c_{i-1}-1)$ 的 $1..j-1$ 位相同，第 $j$ 位大1 

>证明：

> $G(w)$ 在 $1..i-1$ 位上一定有非零位，所以 $w>=c_{i-1}$(1)

如果 $G(w)$ 在 $1\simi-1$位上没有非零位，那么只会在 $i+1$ 位以后有非零位，字典序小于 $M(w)$ ，不满足字典序最大要求，所以只可能在 $1\sim i-1$ 位上有非零位。

>因为w是最小的反例，

>所以$G(w-c_j)=M(w-c_j)$,

如果$G(w-c_j)\neq M(w-c_j)$

那么说明 $w-c_j$ 是最小反例，而不是 $w$

>而 $M(w-c_j)$ 就是$M(w)$在第 $j$ 位上-1, 其他位都是一样的

>所以 $M(w-c_j)$ 的前 $i-1$ 位为0

>所以 $G(w-c_j)$ 的前 $i-1$ 位为0

>所以 $w-c_j \le c_{i-1}$ (2)

剩下的就应该没问题了。



---

