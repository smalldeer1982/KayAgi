# [USACO16OPEN] 248 G

## 题目描述

贝西喜欢在手机上下载游戏来玩，尽管她确实觉得对于自己巨大的蹄子来说，小小的触摸屏用起来相当笨拙。

她对当前正在玩的这个游戏特别感兴趣。游戏开始时给定一个包含 $N$ 个正整数的序列（$2 \leq N \leq 248$），每个数的范围在 $1 \ldots 40$ 之间。在一次操作中，贝西可以选择两个相邻且相等的数，将它们替换为一个比原数大 1 的数（例如，她可以将两个相邻的 7 替换为一个 8）。游戏的目标是最大化最终序列中的最大数值。请帮助贝西获得尽可能高的分数！

## 说明/提示

在示例中，贝西首先合并第二个和第三个 1，得到序列 1 2 2，然后将两个 2 合并为 3。注意，合并前两个 1 并不是最优策略。

## 样例 #1

### 输入

```
4
1
1
1
2```

### 输出

```
3```

# 题解

## 作者：xiejinhao (赞：256)

#  $P3146$ $[USACO16OPEN]248$ 题解

### **这一篇题解送给初学区间$DP$的人，~~Dalao可以跳过啦~~**



------------
**原题链接**：[$P3146 \  [USACO16OPEN]248$](https://www.luogu.org/problem/P3146)

- 我们分析下题意：题目要求我们可以将两个相邻的相同的数合并，每次合并得到的数是原来的数$+1$，求最后能得到的最大分值。

其实看到合并这一类操作，我们大多会想到区间$DP$。

区间$DP$最简单的状态就是$f[l][r]$表示从左端点$l$到右端点$r$其中合并能获得的最大分值（依题意改变）。

其转移也很简单，我们只需要在$[l,r)$内枚举一个断点，比如本题的转移方程就是$f[l][r]=max(f[l][r],f[l][k]+1)$，这里先不考虑边界。

那么，我们对于每一个左端点等于右端点的小区间，也就是单点，其初值肯定只有那一个点的值，所以边界有：$f[i][i]=a[i]$。

其余的边界都要看题意而定。

看完这些，是不是觉得区间$DP$有点简单了？但是，区间$DP$真正的难点在于其转移的条件和你如何想到这样转移。当然，在你题写多了之后自然就可以秒切这一类水题了。**所以学好$DP$一定要多做题。**



------------
### **我们回到题目当中来**

因为这题也没有其他的条件，所以状态还是$f[l][r]$，不需要其他维度来记录其他信息。

**那么什么情况下才能转移呢？**

很明显的，我们需要左边一段区间$f[l][k]$与右边一段区间$f[k+1][r]$的值相等才能转移，玩过$2048$的小伙伴应该也很清楚。其中$k$是我们枚举在$[l,r)$间的断点，至于为什么是左闭右开，因为右边一段区间是$f[k+1][r]$，总不能$k+1>r$吧。

所以转移方程：

$$f[l][r]=max(f[l][r],f[l][k]+1),if:f[l][k]=f[k+1][r]$$

但是，我们这样的转移方程是有漏洞的，我们可以用一组数据卡掉一些转移条件只有$f[l][k]=f[k+1][r]$的题解：

```
    Input:
        8
        2
        1
        1
        2
        4
        2
        3
        4


    Output:
        4
        
下面这些方便你复制： 8 2 1 1 2 4 2 3 4
```
如果你按上面那么写就会输出$5$，但由于数据太水，你那么写也是可以通过本题的。

**为什么会出现错误呢**？因为如果$f[l][k]=f[k+1][r]=0$，这时$f[l][r]$如果为$0$,其值会错误的被更新，然后就挂了。

因为$f[l][r]$我们还没有更新到，而$f[l][k]$与$f[k+1][r]$也没被更新，你说能不挂嘛？

**那我们怎么解决呢**？这个简单，我们只需在保证$f[l][k]=f[k+1][r]$的基础上加一句：$f[l][k]>0$即可。这样就有效的避免了$f[l][k],f[k+1][r]$未更新到就更新了$f[l][r]$的情况。

**还有一个注意事项**：**最终答案不一定是**$f[1][n]$，因为不是这个区间都能够合并在一起，我们在转移的时候记录一个最大值即可。

但如果整个区间没有任何一个小区间可以合并呢？这启示我们，答案的初值要赋为单点的最大值。

由于这一题我们单点的值再也用不到了，输入时直接输入$f[i][i]$即可。



$Code:$（建议你自己先写一写，不能急着看代码）
------------
```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;

    const int N = 250;
    int f[N][N];

    int main() {
        int n, ans = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", f[i] + i);
            ans = max(ans, f[i][i]);
        }

        for(int len = 2; len <= n; len++) 
            for(int l = 1; l +len -1 <= n; l++) {
                int r = l + len - 1;
                for(int k = l; k < r; k++) 
                    if(f[l][k] == f[k + 1][r] && f[l][k]) {
                        f[l][r] = max(f[l][r], f[l][k] + 1);
                        ans = max(ans, f[l][r]);
                    }
            }

        printf("%d\n", ans);		
        return 0;
    } 
```
上面代码的时间复杂度为$O(N^3)$（~~应该是吧~~）

看完上面那些，相必你对区间$DP$有了更深一层的了解。

我们可以把区间$DP$进行一些总结：

1. 区间合并性

1. 注意转移条件

其余和普通$DP$应该时差不多的了。


------------

### **难道你以为这一题就完了？**

**不，这一题还有其他$DP$做法。**（我也不知道叫啥）

定义状态$f[i][k]$，表示第$i$个数合并得到数值为$k$，能够向右拓展的最右端点。因为是最右端点，所以这个$k$也一定是最大的。

那么我们怎么转移？我们学过线性$DP$应该都清楚。这次合并的价值是$+1$，那么上一次就是$k-1$，上一次的右端点就是$f[i][k-1]$，那么只要$f[i][k]$为$0$，即还没取到最优值，我们就可以转移：

$$f[i][k]=f[f[i][k-1]][k-1],if:f[i][k]=0$$

这个方程是比较难想的，也是比较复杂的，需要多思考。

那么如果$f[i][k]$不为$0$，说明数值$k$是可以合并到的，那么我们只需更新答案：

$$ans=max(ans,k),if:f[i][k]>0$$

我们枚举$k$即可。

**但是哪一层循环放外面呢？我们应该要清楚，这里的$k$才是阶段，而$1-n$那一层才是决策。**

**那么$k$最大是多少，最小又是多少**？我们来看$N∈[2,248]$，每一个数值$∈[1,40]$，那么$k$最大的情况就是$N=248$，所有数值都等于$40$，可以算出$k_{max}=47$，而最小呢？我们依次类推，$k_{min}=1$，即整个数列$N=1$，只有一个数$1$的情况。

转移边界:对于每一个数列的数值$a[i]$，$f[i][a[i]]=i+1$，即其最多向右合并到$i+1$。这个需要好好理解。

这样的$DP$基于倍增思想（我也不太清楚，~~倍增写得少~~）


$Code:$
------------


```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;

    const int N = 250, K = 50;
    int f[N][K];

    int main() {
        int n, x, ans = 0;
        scanf("%d", &n);
        for(int i = 1;i <= n; i++) {
            scanf("%d", &x);
            f[i][x] = i + 1;
            ans = max(ans, x);
        }

        for(int k = 1;k <= 47; k++)
            for(int i = 1; i <= n; i++) {
                if (f[i][k] == 0) 
                    f[i][k] = f[f[i][k - 1]][k - 1];
                if (f[i][k]) 
                    ans=max(ans, k);
            }

        printf("%d\n", ans);
        return 0;
    }
```
现在我们已经把时间优化到了$O(47N)$了，感觉很优秀？


------------

区间$DP$评测记录：[区间$DP$作法](https://www.luogu.org/record/22000476)

优化$DP$评测记录：[优化$DP$做法](https://www.luogu.org/record/22003885)


$End$
------------


---

## 作者：wdyhy (赞：81)

这个题状态比较奇妙，不妨设一个f[i][j]表示到第i个数，得到数值为j，向右合并的最右端点。

方程f[i][j]=f[f[i][j-1]][j-1];这个方程很像倍增。

然后这个j比较小，因为两个合并之后得到的数只大1，所以可以跑过去。





```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,ans;
int f[270000][66],a[270000];
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        f[i][a[i]]=i+1;
    }
    for (int j=2;j<=60;j++)
        for (int i=1;i<=n;i++){
            if (f[i][j]==0) f[i][j]=f[f[i][j-1]][j-1];
            if (f[i][j]>0) ans=max(ans,j);
        }
    printf("%d\n",ans);
    return 0;
}
```
脑坑了一个做法。
然后这个貌似区间dp也可以，数据太水

f[i][j]表示i~j区间得到的值

转移到f[k][j]和f[i][k]

不过也没写出来。


---

## 作者：LZDQ (赞：39)

一开始看到合并，基本上都是想到区间DP。

但是OI里面不能总是用套路。

大家都听说过或者玩过2048吧？

这题就是一维版本的2048（2048里是显示2的几次方，这里就直接显示几次方了）

------------

假如我们在玩2048，现在只有一行的数，如果我们要把最右边的数凑到最大，那么一直往右划就好了。

如果我们要把最左边的数凑到最大，那么一直往左边划就好了。

我们很容易想到这题枚举中间点，把它左边合并过来，右边合并过来，最大是多少。

不过这样每次合并到底是**先合并左边还是先合并右边**？

先别急。

这题中，我们可以只选择合并某两个数。

这样，往左划就跟往右划是一样的了。

哈哈，玩游戏有助于提升思维！

于是我们根据游戏推出了这题 $O(n^2)$ 算法。

------------

实现方法：
1. 枚举右端点
2. 从右端点往左扫，通过栈来存扫过的数
3. 如果栈顶的两个数相等，把这两个数都弄出来，把它们加一弄进去（重复）

简洁的代码：
```cpp
#include<cstdio>
const int MAXN=250;
int n;
int a[MAXN];
int top,stk[MAXN];
int ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        stk[top=1]=a[i];
        for(int j=i-1;j>0;j--){
            if(a[j]>stk[top]) break;	//接着划已经没用了
            stk[++top]=a[j];	//压栈
            while(top>1&&stk[top]==stk[top-1])
                stk[--top]++;	//合并两个数
        }
        if(ans<stk[1]) ans=stk[1];	//栈底为当前右端点合并后的最大值
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：djy213 (赞：30)

楼上各位写的都是DP啊

反正我写了“奇妙”的贪心，

基本思路是，从最小的数字开始合并，

如果连续（j-l+1）个数相同

以下叙述对该区间而言

1.偶数个，直接合并

2.奇数个，把所有数加1（不是合并），并通过把中点不变或变小；

这个2是为什么呢

因为当个数为奇数时，

有如下特性

因为它求的是最值

故可以把第一个或最后一个不合并其它合并（这个可以证一下）

这样该点不变，且永远不会变（这个易证）

这样该点把整个数列分成互不影响的两部分（这个废话）

故我们可以把第一个或最后一个不合并其它合并的情况同时表现出来，而他们互不影响

即2的做法

代码

```cpp
#include<cstdio>
using namespace std;
int n;
int a[249];
int main()
{
    freopen("248.in","r",stdin);
    freopen("248.out","w",stdout);
    int i,j,k=50,l,ans=0,r;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=k;i++)
    {
        for(j=1;j<=n;j++)
        if(a[j]==i)
        {
            l=j;
            while(a[j]==i&&j<=n)
                j++;
            j--;
            if((j-l+1)%2==0)
            {
                for(r=(l+j)/2+1;r<=n-(j-l+1)/2;r++)
                    a[r]=a[r+(j-l+1)/2];
                n=n-(j-l+1)/2;
                for(r=l;r<=(l+j)/2;r++)
                    a[r]++;
                j=r-1;
            }
            else
            {
                for(r=l;r<=j;r++)
                    a[r]++;
                a[(r+l)/2]--;
            }
            if(a[l]>k)k=a[l];
        }
    }
    for(i=1;i<=n;i++)
        if(a[i]>ans)
            ans=a[i];
    printf("%d",ans);
    fclose(stdin);fclose(stdout);
    return 0;
}
//抄代码的同学记得删文件操作呀
```

---

## 作者：Cripple_Abyss (赞：16)

- [题目传送门](https://www.luogu.com.cn/problem/P3146)

本题与[这道题](https://www.luogu.com.cn/problem/P3147)做法类似，可以说是双倍经验QwQ

为什么这两题一个是绿题，而另一个是蓝题？

## 言归正传
这题其实是一道**区间DP**的题目

$DP$三步法：

1. 状态定义：$f[i][j]$表示以$j$为起点，能合成数$i$的区间长度



1. 状态转移方程：$f[i][j]=f[i-1][f[i-1][j]]$

1. 状态初值：$f[t][i]=i+1$， $ t$ 为输入的数.


## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[65][300005],t,n,ans;
int main() {
	cin>>n;
	for (int i=1; i<=n; i++) {
		cin>>t;
		f[t][i]=i+1;
	}
	for (int i=2; i<=51; i++) //2048=2^11 题目明确最大范围是40 40+11=51 
		for (int j=1; j<=n; j++) {
			if (!f[i][j])
				f[i][j]=f[i-1][f[i-1][j]];
			if (f[i][j])
				ans=i;
		}
	cout<<ans;
	return 0;
}
```


都看到这了，点个赞呗QwQ

---

## 作者：览遍千秋 (赞：9)

## 前言

奇妙，最近在学区间动规，怎么区间动规的题目难度都那么高？

---

## 阶段、状态的划分

合并区间的长度为阶段，状态是每一个这样长度的区间。

---

## 状态的表示

$opt[i][j]$表示从$i$开始合并长度为$j$的区间的最大值

---

## 本题的特殊性

当$opt[j][k]=opt[k+1][r]$的时候，才可以进行状态转移

---

## 状态转移方程

$$opt[j][r]=max(opt[j][r],opt[j][k]+1)$$

---

## 代码

```cpp
#include<iostream>
#include<cstdio>

using namespace std;
#define maxn 257
int n,opt[maxn][maxn],a[maxn],ans;
inline void Init()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i++) 
    {
    	scanf("%d",&a[i]);
        opt[i][i]=a[i];
        ans=max(a[i],ans);
    }
}
inline void Work()
{
    for(register int i=2;i<=n;i++)
    {
        for(register int j=1;j+i-1<=n;j++)
        {
            int r=i+j-1;
            for(register int k=j;k<r;k++)
            {
                if(opt[j][k]==opt[k+1][r])
                    opt[j][r]=max(opt[j][r],opt[j][k]+1);
                ans=max(ans,opt[j][r]);
            }
        }
    }
    printf("%d\n",ans);
}
int main()
{
    Init();
    Work();
    return 0;
}
```

---

## 作者：ShineEternal (赞：5)

[更佳护眼的阅读效果。](https://blog.csdn.net/kkkksc03/article/details/105545884)

## description

在一个长度为 $n$ 的序列中，每次可以合并**相邻两个相等**的数。问能合并出的最大数。

## solution

涉及到了合并的问题，我们应当想到可以使用区间 dp。

那么我们就设 $f[l][r]$ 表示区间 $[l,r]$ 里的数经过合并可以得到的最大的一个数。

我们设想两个区间能够合并，就必须满足两个区间各自合并出的最大的数字相等，即 $f[i][k]==f[k+1][r]$，这里 $k,k+1$ 为两个区间的分界点，那么就可以合并。

合并之后就变成了整个大区间 $f[l][r]$，我们只需要判断是合并的价值更高还是原来大区间本身的价值更高就行了。

但是答案在输出的时候要囊括所有的区间，因为不一定合并到最大的区间的值最优。

时间复杂度：$O(n^3)$。

## code
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[300][300];
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&f[i][i]);
		ans=max(ans,f[i][i]);
	}
	for(int dis=2;dis<=n;dis++)
	{
		for(int l=1;l+dis-1<=n;l++)
		{
			int r=l+dis-1;
			for(int k=l;k<r;k++)
			{
				if(f[l][k]==f[k+1][r]&&f[l][k])
				{
					f[l][r]=max(f[l][k]+1,f[l][r]);
				}
			}
			ans=max(ans,f[l][r]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Manjusaka丶梦寒 (赞：5)

区间dp，这次设计的状态和一般的有一定的差异。

这次我们定义$dp[i][j]$表示$[i,j]$的可以合并出来最大取值，而不是合并区间$[i,j]$的最大取值。

同样的我们枚举区间长度，枚举左端点，求出右端点。

枚举$i$到$j$之间的每一个分割点，判断两点之间是否可以合并，取价值更高的答案。

$$dp[i][j]=max(dp[i][j],dp[i][k]+1) [dp[i][k]==dp[i][k+1]$$

Question 1:其他的点不需要更新，为什么？

这就要看我们设计的状态了，我们定义的是区间[i,j]可以合并出来的最大值，答案唯一，当然不能用其位置的更新了。

Question 2:答案是什么？

注意这里的答案不一定是$dp[1][n]$,你想当我们计算区间[1,n]时所有的$dp[i][k]!=dp[k+1][j]$那么区间$[1,n]$的答案为$0$，答案在之前已经得出，所以我们在过程中记录一下就好了。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define LL long long
#define mod int(1e9+7)
int n,a[250],dp[250][250],ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dp[i][i]=a[i];	//初始化dp数组 
    }
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n;i++)
        {
            int j=i+len-1;
            if(j>n)break;	//超出长度限制 
            for(int s=i;s<j;s++)
            {
                if(dp[i][s]==dp[s+1][j])dp[i][j]=max(dp[i][j],dp[i][s]+1);
            }
            ans=max(dp[i][j],ans);	//记录答案 
        }
    }
    printf("%d",ans);
} 
```

---

## 作者：在想Peach (赞：3)

正确的区间dp。

复杂度有点大，按理说常数会t，结果不开o2可以过，开了跑飞快..

显然一个区间的合并不一定是越大越有利，所以用（假的）dp存对于一个区间可以达到的值，用来更新大区间的值。

所以转移方程为：if(f[l][j-l][s]&&f[j+1][r-j-1][s])f[l][k][s+1]=1;

表示当组成此区间两个分区间都拥有同一个数时，这个区间的这个数加一即可被构成，然后递推到最后的大区间得到所有可取得的值，用一个变量存储最大构成值。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,x,ans;
bool f[255][255][45];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;f[i][0][x]=1;ans=max(ans,x); 
	 } 
	for(int k=1;k<n;k++)
	{
		for(int i=1;i+k<=n;i++)
		{
			int l=i,r=i+k;
			for(int j=l;j<r;j++)
			{
				for(int s=1;s<=40;s++)
				{
				if(f[l][j-l][s]&&f[j+1][r-j-1][s])f[l][k][s+1]=1;
				if(f[l][k][s+1])ans=max(ans,s+1);
			}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
 } 
```


---

## 作者：Jiang_zi_chuan (赞：2)

~~这道题比较水~~，设f[i][j]表示i~j区间合并的最大值。

但这道题目还有扩大数据范围后的做法：

我的转移方程：

```
f[i][j]=max(f[i][k]+1,f[i][j]);
```

我们设的是i~j区间的最大值，这里有个巧妙的转化，设f[i][j]为j开始最大值达到i的右边界。

如图：

![](https://images2017.cnblogs.com/blog/1109106/201710/1109106-20171022192148256-658352967.png)

最后，附上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int N, x, f[60][262200], ans;
int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
    	scanf("%d", &x), f[x][i] = i;
    for(int i = 2; i <= 58; i++)
        for(int j = 1; j <= N; j++){
            if(!f[i][j] && f[i - 1][j]) 
            	f[i][j] = f[i - 1][f[i - 1][j] + 1];
            if(f[i][j])ans = i;
        }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：andysk (赞：2)

[Problem](https://www.luogu.org/problemnew/show/P3146)



### 题意

有一列数字，对两两相邻的数字进行合并操作，其中合并的贡献是1，问最大的贡献。



### 题解

​		这个题很像[石子合并](https://www.luogu.org/problemnew/show/P1880)，也可以算是刚刚上手区间DP的经典题型吧

​		首先考虑状态，区间DP的重要思想就是把小区间的贡献算出来，然后计给大区间使用，包含这种思想的有著名的线段树和树状数组，在这里不详细讲。所以我们不妨设 $len$ 表示状态，为我们当前合并的区间长度。最开始我们的区间长度都是 $1$ ，之后在DP过程中枚举。

​		之后考虑转移，按照套路，不妨设 $l, r$ 表示当前区间的两个端点，$f[l,r]$ 表示合并 $[l,r]$ 区间的最大贡献。在 $l,r$ 中间我们再枚举一个的断点 $k$ ，表示在 $ len $ 长度的一个大区间内，有 $[l,k]$ 这个区间，这是一个小区间，根据区间DP用小区间更新大区间的思想，那么我们的转移就是：$f[l,r] = min(f[l][r], f[l][k])$

​		最后考虑一下初值，我们最开始这一个序列中的数都是一个一个来合并的，所以区间最开始的长度就是1，不妨在读入的时候就比较一下最大值。显而易见，$f[i,i] = a[i]$



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 300 + 5;

int n;
int a[SIZE], f[SIZE][SIZE];

inline int read()
{
    char ch = getchar();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
    return x * f;
}

int main()
{
    n = read();
    int ans = 0;
    for (int i = 1; i <= n; i++) a[i] = read(), ans = std::max(ans, a[i]);
    for (int i = 1; i <= n; i++) f[i][i] = a[i];
    for (int len = 2; len <= n; len++)
	for (int l = 1; l <= n - len + 1; l++)
	{
	    int r = l + len - 1;
	    for (int k = l; k < r; k++)
	    {
		if (f[l][k] == f[k + 1][r])
		    f[l][r] = std::max(f[l][r], f[l][k] + 1);
	    }
	    ans = std::max(ans, f[l][r]);
	}
    printf("%d", ans);
    return 0;
}

```




---

## 作者：Doveqise (赞：1)

这道题，一道简单区间DP，在这里主要介绍一下加强版[P3147 [USACO16OPEN]262144](https://www.luogu.org/problemnew/show/P3147)别人不太注意的数据范围问题...(假双倍经验)  
我们注意到题中说2≤N≤262 144，那么这个262 144是多少呢？  
266 144=$2^{18}$,所以我们循环时就循环到40+18=58就好。  
细节见代码↓（不想用58系列）
```c++
#include<bits/stdc++.h>
using namespace std;
int f[60][262144+5],ans;
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){int t;scanf("%d",&t);f[t][i]=i+1;}
    for(int i=2;i<=60;i++) for(int j=1;j<=n;j++){
		if(!f[i][j]) f[i][j]=f[i-1][f[i-1][j]];
        if(f[i][j]) ans=i;}
    printf("%d\n",ans);
    return 0;
}

```

---

