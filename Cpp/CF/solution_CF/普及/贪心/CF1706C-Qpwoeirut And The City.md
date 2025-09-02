# Qpwoeirut And The City

## 题目描述

Qpwoeirut has taken up architecture and ambitiously decided to remodel his city.

Qpwoeirut's city can be described as a row of $ n $ buildings, the $ i $ -th ( $ 1 \le i \le n $ ) of which is $ h_i $ floors high. You can assume that the height of every floor in this problem is equal. Therefore, building $ i $ is taller than the building $ j $ if and only if the number of floors $ h_i $ in building $ i $ is larger than the number of floors $ h_j $ in building $ j $ .

Building $ i $ is cool if it is taller than both building $ i-1 $ and building $ i+1 $ (and both of them exist). Note that neither the $ 1 $ -st nor the $ n $ -th building can be cool.

To remodel the city, Qpwoeirut needs to maximize the number of cool buildings. To do this, Qpwoeirut can build additional floors on top of any of the buildings to make them taller. Note that he cannot remove already existing floors.

Since building new floors is expensive, Qpwoeirut wants to minimize the number of floors he builds. Find the minimum number of floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 说明/提示

In the first test case, it is optimal for Qpwoeirut to make the second building cool by building $ 2 $ additional floors on top of it, making it taller than both of its adjacent buildings. The final heights of buildings will be $ [2, \underline{3}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/5b747d1e682e5f282bdd90fc1247bc9f2859b4d3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/c25e1e8b92772ee4d6c001b5263ad32fc0bed1d3.png)In the second test case, the number of cool buildings is already maximized, so Qpwoeirut does not need to do anything.

In the third test case, it is optimal for Qpwoeirut to make the third and fifth buildings cool by building $ 2 $ additional floors onto the third building and $ 1 $ additional floor onto the fifth building. The final heights of buildings will be $ [3, 1, \underline{6}, 5, \underline{6}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/d8dd96553e5aa6fe2bbad7a9bf1dc528da32254c.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/6d7185baf1e5e2a187bb01c943d100104f7de6bc.png)It can be shown that it is impossible to make more than $ 2 $ of the buildings cool, or to make $ 2 $ buildings cool using fewer than $ 3 $ additional floors.

In the fourth test case, Qpwoeirut can either make the second building cool, or he can make the third building cool. Either way, he will be building $ 3 $ additional floors and maximizing the number of cool buildings. The final heights of buildings will be $ [4, 2, \underline{4}, 3, 5, 3, 6, 1] $ or $ [4, \underline{5}, 1, 3, 5, 3, 6, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/27f107a434b26468932a928c7c16fd0abda918f0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/4e2e7951e438027228057e8a21e8bea81f160a32.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/8e41aee337358c3f261ed9626c0e19808d3f7d2c.png)

## 样例 #1

### 输入

```
6
3
2 1 2
5
1 2 1 4 3
6
3 1 4 5 5 2
8
4 2 1 3 5 3 6 1
6
1 10 1 1 10 1
8
1 10 11 1 10 11 10 1```

### 输出

```
2
0
3
3
0
4```

# 题解

## 作者：Burnling (赞：10)

### 题意简述

- 给出一个长度为 $n$ 的序列 $h$，其中的每一项代表第 $i$ 座建筑物的高度。

  当 $h_i > h_{i-1}$ 且 $h_i>h_{i+1}$ 时，称第 $i$ 座建筑是“凉爽的” 。

  注意，第一座建筑和最后一座建筑不可能为“凉爽的”。

- 你可以增高任何一座建筑物的高度，使得最终“凉爽的”建筑物最多。

- 为了使“凉爽的”建筑物最多，求出需要增加的最小总高度。

- 多测。 $3 \leq n \leq 10^5,1\leq h_i \leq 10^9$。

### 算法分析

首先考虑在什么情况下“凉爽的”建筑物是最多的。

由于“凉爽的”建筑的定义，我们知道不会存在连续的“凉爽”建筑。

由于第一座和最后一座建筑一定不是“凉爽的”，所以最终“凉爽的”建筑数为 $\left\lceil \dfrac{n}{2} \right\rceil - 1$。

事实上，这个结果实际上是分类讨论得出的：

1. 若 $n$ 为偶数，可知最多有 $\dfrac{n-2}{2}$ 座建筑是“凉爽的”。
2. 若 $n$ 为奇数，可知最多有 $\dfrac{n-2+1}{2}$ 座建筑是“凉爽的”。

~~这个结论过于显然，就不举例了。~~

下一步考虑应该令哪些建筑物是“凉爽的”。

对于 $n$ 是奇数的情况，“凉爽的”建筑的位置是固定的。令这些位置的建筑的高度高于两侧建筑高度的最大值即可。

对于 $n$ 为偶数的情况，情况会稍微复杂一些：

这里令 $1$ 代表“凉爽的”建筑，令 $0$ 代表非“凉爽的”建筑。

在纸上写一写就会发现，符合题意的序列并不是唯一的。

比如 $n=8$ 时就有如下几种情况：

```text
- 1 0 1 0 1 0 -
- 1 0 1 0 0 1 -
- 1 0 0 1 0 1 -
- 0 1 0 1 0 1 -
```

但是，通过观察这四个序列，我们能发现一些规律：

1. 去掉第一项和最后一项，中间的每两个分成一组，每组一定是 `1 0` 与 `0 1` 其中之一。

2. 对于这些组，一定是前一部分是 `1 0` ，后一部分是 `0 1` ，并且仅会在整个序列中间更改一次顺序。

   因为 $1$ 的左右两边一定是 $0$ ，所以 `0 1` 后面不能接 `1 0` ，`1 0` 前面也不能是 `0 1`。

所以我们可以事先求出全是 `1 0` 的花费前缀和，求出全是 `0 1` 的花费后缀和，最后枚举在第 $k$ 组改变了顺序求最小值即可。

对于每个测试用例，复杂度为 $O(n)$。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5;
typedef long long ll;

int B[maxN];
//一定别忘了开long long
ll A1[maxN];
ll A2[maxN];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int N;
        scanf("%d",&N);
        for(int i = 1;i<=N;i++) scanf("%d",&B[i]);
        ll ans = 0;
        if(N & 1){ // N为奇数
            for(int i = 2;i<N;i+=2){
                int M = max(B[i-1],B[i+1]);
                if(B[i] <= M){
                    ans += (M+1-B[i]);
                }
            }
        }else{
            memset(A1,0ll,sizeof(A1));
            memset(A2,0ll,sizeof(A2));
            
            int cnt = 1;//第 cnt 组
            for(int i = 2;i<N-1;i+=2){
                int M = max(B[i-1],B[i+1]);
                if(B[i] <= M){
                    A1[cnt] = A1[cnt-1] + (M+1-B[i]);
                }else{
                    A1[cnt] = A1[cnt-1];
                }//求情况1增高的前缀和
                cnt++;
            }
            cnt = (N>>1)-1;
            for(int i = N-1;i>2;i-=2){
                int M = max(B[i-1],B[i+1]);
                if(B[i] <= M){
                    A2[cnt] = A2[cnt+1] + (M+1-B[i]);
                }else{
                    A2[cnt] = A2[cnt+1];
                }//求情况2增高的后缀和
                cnt--;
            }
            int r = (N >> 1);//一共有 (N/2)-1 组，但是考虑到下面的循环边界就加了一
            ans = 1e17;//最大值要足够大。。。
            for(int i = 1;i<=r;i++){
                //枚举在哪组变序
                ans = min(ans,A1[i-1]+A2[i]);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：wsx248 (赞：5)

由于题目要求让 $h_n$ 中“好的”元素最多，所以有显然的贪心想法：
1. 如果 $n$ 是奇数，直接从第 $2$、$4$、$6\dots$ 个这样取下去一定是最优的；
2. 如果 $n$ 是偶数，则情况稍微复杂一些，但是也不难得出结论：对相邻两个元素而言，必须选择其中一个元素才行。

把相邻两个位置视作一组，可以发现：
- 如果当前组内选择**奇数**位置上的元素，则下一组里只能选奇数位置元素
- 如果当前组内选择**偶数**位置上的元素，则下一组里两个位置都可以选

考虑动态规划：设 $\mathit{dp}_{i}$ 表示取走当前元素后增加的最小操作次数，易得转移方程（$add(i)$ 表示每个元素至少需要增加多少高度）：

$i\bmod2=1, \mathit{dp}_{i}=\min(\mathit{dp}_{i-2}, \mathit{dp}_{i-3})+add(i)$

$i\bmod2=0, \mathit{dp}_{i}=\mathit{dp}_{i-2}+add(i)$

最后结果从 $\mathit{dp}_{n-1},\mathit{dp}_{n-2}$ 中取得，单组数据时间复杂度 $O(n)$。
```
#include<iostream>
#include<cstring>
using namespace std;
const int N = 1e5+5;
int n;
int a[N];
int add[N];
long long dp[N];

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=2;i<n;i++)
			add[i] = max(0, max(a[i-1]-a[i], a[i+1]-a[i])+1);
		if(n&1)
		{
			long long ans = 0;
			for(int i=2;i<n;i+=2)
				ans += add[i];
			cout<<ans<<endl;
		}
		else
		{
			memset(dp, 0x3f, sizeof dp);
			dp[1] = 0;
			dp[2] = add[2];
			dp[3] = add[3];
			for(int i=4;i<n;i++)
			{
				if(i&1)
					dp[i] = min(dp[i-2], dp[i-3]) + add[i];
				else
					dp[i] = dp[i-2] + add[i];
			}
			cout<<min(dp[n-1], dp[n-2])<<endl;
		}
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1S94y1Q7zs)

### 2 思路

我们可以分为两个情况讨论：$n$ 为奇数或 $n$ 为偶数。

当 $n$ 为奇数时：

很明显，将偶数下标的楼层进行加高操作可以得到最多的酷的楼。模拟即可。

当 $n$ 为偶数时：

忽略第 $1$ 栋楼和第 $n$ 栋楼。将剩下的 $n-2$ 栋楼**依次**两两分成一组，一共 $\dfrac{n-2}{2}$ 组。

很明显，每一组有且只有一栋楼进行加高是最优的。

那么必定存在一组楼房，满足左边（包括自己）每一组楼房的左楼加高，右边（不包括自己）每一组楼房的右楼加高。

当然，也可以每一组楼房的左（或右）楼进行加高。

利用前缀和，枚举即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
#define inf (1ll<<52)
int t;
int n;
long long a[max_n+2];
long long s1[max_n+20];
long long s2[max_n+20];
long long ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1706C_1.in","r",stdin);
	freopen("CF1706C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lld",a+i);
		ans=0;
		if(n&1){
			for(int i=2;i<n;i+=2)ans+=max(0ll,max(a[i-1],a[i+1])-a[i]+1);
			printf("%lld\n",ans);
		}
		else{
			s1[0]=s2[n+1]=0;
			for(int i=2;i<n;i+=2)s1[i]=s1[i-2]+max(0ll,max(a[i-1],a[i+1])-a[i]+1);
			for(int i=n-1;i>1;i-=2)s2[i]=s2[i+2]+max(0ll,max(a[i-1],a[i+1])-a[i]+1);
			ans=inf;
			for(int i=0;i<n;i+=2){
				if(i>=n-2)ans=min(ans,s1[i]);
				else ans=min(ans,s1[i]+s2[i+3]);
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80265679)

By **dengziyue**

---

## 作者：ExplodingKonjac (赞：2)

**[原题链接](https://www.luogu.com.cn/problem/CF1706C)**

## 题目分析

题意：给你一个长度为 $n$ 的序列 $a$，称一个位置 $i$ 为好的，当且仅当 $a_{i-1}<a_i\land a_{i+1}<a_i$。且注意 $1$ 和 $n$ 永远不会是好的。一次操作可以把任意 $a_i$ 加一，求最少的操作次数以得到最多的好的位置。

容易发现好的位置相隔至少一个位置，所以可以很容易知道好位置数量的最大值。接下来分 $n$ 奇偶性讨论。

* $n$ 为奇数：
  
  此时好的位置一定是 $2,4,\dots,n-1$。对于这些位置算出来刚好加到大于两边的操作数即可。
  
* $n$ 为偶数：

  此时好的位置不固定。但是我们发现有 $\dfrac{n-2}{2}$ 个好位置，只有 $n-2$ 个空位来容纳它们，而两个好位置还不能相邻。那么我们发现任意一种放法都仅有一对相邻的好位置间隔为 $2$，其余间隔都为 $1$。求出每个前缀和后缀间隔为 $1$ 放满的答案，再枚举那一个 $2$ 的间隔即可。
  
## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

LL T,n,a[100005],f[100005],g[100005];
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		for(int i=1;i<=n;i++) qin>>a[i];
		f[1]=g[n]=0;
		for(int i=2;i<=n-1;i++) f[i]=f[i-1]+((i-1)&1)*max(0ll,max(a[i-1],a[i+1])+1-a[i]);
		for(int i=n-1;i>=1;i--) g[i]=g[i+1]+((n-i)&1)*max(0ll,max(a[i-1],a[i+1])+1-a[i]);
		LL ans=1e18;
		if(n&1) ans=f[n-1];
		else for(int i=2;i<n;i++) ans=min(ans,f[i-1]+g[i+1]);
		qout.writeln(ans);
	}
	return 0;
}
```


---

## 作者：luogu_gza (赞：1)

发现没有一个人是我的做法诶。

考虑一下钦定符合要求的下标。

发现 $n$ 为奇数的时候明显是 $2,4,6, \cdots ,n-1$。

那么 $n$ 为偶数的时候呢？

有三种情况。

第一种：$2,4,6, \cdots ,n-2$。

第二种：$3,5,7, \cdots ,n-1$。

第三种：我们以 $n=12$ 为例：

- $2,5,7,9,11$；

- $2,4,7,9,11$；

- $2,4,6,9,11$；

- $2,4,6,8,11$。

每一个都去计算明显十分繁琐，但是发现每一次“改变”对于答案的贡献是可以快速计算的。

代码（内涵注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MT int TTT=R;while(TTT--)
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
const int N=1e5+10;
int n;
int a[N];
int f(int i)//一个简单的计算单点贡献的函数
{
    if(a[i]>a[i-1]&&a[i]>a[i+1]) return 0;
    return max(a[i-1],a[i+1])+1-a[i];
}
signed main(){
    MT
    {
        n=R;fo(i,1,n) a[i]=R;
        if(n&1)//奇数的情况
        {
            int ans=0;
            for(int i=2;i<n;i+=2) ans+=f(i);
            write(ans),puts("");
        }
        else//偶数的贡献
        {
            int ans1=0,ans2=0,ans3=0,ans4=0;
            for(int i=2;i<n;i+=2) ans1+=f(i);//第一种情况
            for(int i=3;i<n;i+=2) ans2+=f(i);//第二种情况
            ans3=f(2);
            for(int i=5;i<n;i+=2) ans3+=f(i);//第三种情况预处理
            ans4=ans3;
            for(int i=5;i<n;i+=2) ans3=ans3-f(i)+f(i-1),ans4=min(ans4,ans3);//考虑每一个“改变”对于答案的贡献
            write(min({ans1,ans2,ans4})),puts("");//计算总的最小次数
        }
    }
}
```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**贪心**的思路：

- 我们把将 $h_i$ 变为 `Cool House` 所需要的点数称为 $i$ 的贡献。

- 我们将初始情况设为这样，并求和 `ans`：

~~~
奇数：1 2 1 2 1
偶数：1 2 1 2 1 1
~~~
- 如果 $n$ 为奇数，直接输出 `ans`。

- 如果 $n$ 为偶数，那么我们将序列（偶数个元素的情况）一步步挪成这个形式：

~~~
1 1 2 1 2 1
~~~

- 每次挪动时都是一种情况，所以将每次的情况的花费打擂台找最小。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define int long long//见祖宗
using namespace std;
const int N=1e5+5;
int t,n,res,ans,h[N];
inline int cool(int k)
{
	if(h[k]>h[k-1]&&h[k]>h[k+1])
	{
		return 0;
	}
	else
	{
		return max(h[k-1],h[k+1])-h[k]+1;
	}
}//求这个数的贡献
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>h[i];
		}
		ans=0;//清空！
		for(int i=2;i<n;i+=2)
		{
			ans+=cool(i);//求初始情况贡献
		}
		res=ans;//求每种情况
		if(n%2==0) 
		{
			for(int i=n-1;i>=3;i-=2)
			{
				res+=cool(i);
				res-=cool(i-1);//挪动操作
				ans=min(ans,res);//每挪动一次打一次擂台
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}

---

## 作者：zct_sky (赞：0)

### Solution:
-----
一道贪心题。

如果我们设 $f(i)$ 为把 $h_i$ 变成“凉爽”的建筑的操作次数，则 
$$f(i)=\begin{cases}0(h_i>h_{i-1},h_i>h_{i+1})\\\max\{h_{i-1},h_{i+1}\}+1-h_i(h_i \leq h_{i-1}\  or \ h_i \leq h_{i-1})\end{cases}$$


- 当 $n$ 为奇数时，最多有 $\dfrac{n-1}{2}$ 栋 “凉爽” 的建筑，那么最多的方案就是把每一个偶数号建筑变成“凉爽” 的建筑，答案就是 $\sum\limits_{i=2,2\mid i}^{n} f(i)$。

- 当 $n$ 为偶数时，最多有 $\dfrac{n}{2}-1$ 栋 “凉爽” 的建筑，但此时会有一个空位（$n$ 栋建筑和 $n-1$ 栋建筑 “凉爽” 的建筑数是一样的，如：$6$ 栋建筑和 $5$ 栋建筑 “凉爽” 的建筑数都是 $2$）。在这个空位之前，全都是偶数号建筑是“凉爽”的建筑，在这个空位之后，全都是奇数号建筑是“凉爽”的建筑（因为只有一个空位，所以只有一个奇偶转折点）。如果第 $j$ 号建筑是空位（假设 $j$ 是奇数），答案即为 $\sum\limits_{i=2,2\mid i}^{j-1} f(i) + \sum\limits_{i=j+2,2\nmid i}^{n-1} f(i)$（这个要用前缀和优化）。然后只需要暴力枚举出空位在哪里，并取每次答案的最小值即可。

### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
const int N=1e5+7;
ll t,n,h[N],s[2][N],ans;
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)h[i]=read();
		for(int i=2;i<n;i+=2)s[0][i]=s[0][i-2]+max(0ll,max(h[i-1],h[i+1])+1-h[i]);
		for(int i=(n%2?0:n-1);i>=3;i-=2)s[1][i]=(i==n-1?0:s[1][i+2])+max(0ll,max(h[i-1],h[i+1])+1-h[i]);
		if(n%2){
			ans=s[0][n-1]; 
		}else{
			ans=LLONG_MAX;
			for(int i=1;i<n;i+=2){
				ans=min(s[0][i-1]+s[1][i+2],ans);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：tzyt (赞：0)

题目链接[（CF](https://codeforces.com/problemset/problem/1706/C)，[洛谷）](https://www.luogu.com.cn/problem/CF1706C) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1706/)中观看。
## 思路

能发现，不管怎么样，城市中酷的房子最多有 $\lfloor \frac{n - 1}{2} \rfloor$ 个。

如果是奇数个的话，只有一种排布方法能达到这么多个酷的房子。也就是第一个样例展示的。

![](ttzytt.com/img/CF1706/and_the_city.png)

从第二个房子开始，把每个偶数位置的房子都搞成酷的，也就是酷和不酷的房子隔着出现。

计算把一个普通房子变成酷的房子的代价可以用如下方法：

```cpp
inline ll calc_cost(int i, int* h) {
    if (h[i] <= h[i - 1] || h[i] <= h[i + 1])
        return max(h[i - 1], h[i + 1]) - h[i] + 1;
    else
        return 0;
}
```

也就是把当前的房子搞的比相邻的最高的房子还要高一格。

但是偶数个房子的情况就比较复杂了。这种情况下 $\lfloor \frac{n - 1}{2} \rfloor$ 一定等于 $\frac{n}{2} - 1$。

那么就会有 $\frac{n}{2} + 1$ 个不酷的房子，也就一定有两个连在一起出现的不酷的房子，而这两个连续的不酷的房子可以出现在任何位置，我们需要考虑所有的情况。

比如 $n = 8$ 那么有如下几种排布方式。

$$
\texttt{010101}\textcolor{red}{\texttt{00}}\\
\texttt{0101}\textcolor{red}{\texttt{00}}\texttt{10}\\
\texttt{01}\textcolor{red}{\texttt{00}}\texttt{1010}\\
\textcolor{red}{\texttt{00}}\texttt{101010}
$$

但是如果从头到尾的把所有情况都计算一遍，时间就不够了。

所以我们可以只计算从一种情况到另一种情况之间代价的变化量。

比如：

$$
\texttt{010101}\textcolor{red}{\texttt{00}}\\
\downarrow\\
\texttt{0101}\textcolor{red}{\texttt{00}}\texttt{10}
$$

这个过程中，第六个房子从酷变为不酷，第七个房子从不酷变为酷。

假设我们当前正在把第 $i$ 个房子从酷变为不酷，第 $i + 1$ 个房子从不酷变为酷。我们只需要调用前面的 `calc_cost` 减去 $i$ 的价格再加上 $i + 1$ 的价格就行了。

```cpp 
//author: tzyt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

inline ll calc_cost(int i, int* h) {
    if (h[i] <= h[i - 1] || h[i] <= h[i + 1])
        return max(h[i - 1], h[i + 1]) - h[i] + 1;
    else
        return 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int h[n + 1];
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
        }
        ll ans = 0, tmp = 0;
        
        // 奇数情况的解法
        for (int i = 2; i < n; i += 2) {
            ans += calc_cost(i, h);
        }
        if (n & 1) {
            cout << ans << '\n';
            continue;
        }

        tmp = ans;
        for (int i = n - 2; i >= 2; i -= 2) {
            // 枚举连续 0 的位置
            tmp -= calc_cost(i, h);
            tmp += calc_cost(i + 1, h);
            ans = min(ans, tmp);
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：wzy2021 (赞：0)

先考虑当 $n$ 为奇数的时候，

则 $2, 4, \dots, n - 1$ 为最大限度，所以让这些楼层比两边高即可。

那么 $n$ 是偶数呢？$2, 4, \dots , n - 2$ 为最大限度，

然而最大限度的楼层不止一个！

比方说 $n = 6$，有

$$1 2 1 2 1 1$$

$$1 2 1 1 2 1$$

$$1 1 2 1 2 1$$

其中，$1$ 表示矮楼层，$2$ 表示高楼层。

可以发现，每两个方案中都是有关系的，

即比如

$$1 2 1 2 1 1$$

与

$$1 2 1 1 2 1$$

其中一个高楼层是从位置 $4$ 移动到 位置 $5$，

也就是说，在计算过程中，可以先算出 

$$1 2 1 2 1 1$$

所需要的代价，然后减去位置 $4$ 所需的代价，加上位置 $5$ 所需的代价，即可得到

$$121121$$

同理，最后一个也是可以得到的。

~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int a[N];

int main() {
	int T; scanf ("%d", &T);
	while (T --) {
		int n; scanf ("%d", &n);
		for (int i = 1; i <= n; ++i) scanf ("%d", &a[i]);
		long long ans = 0, sum = 0;
		for (int i = 2; i < n; i += 2) {
			sum = (sum + max (0, max (a[i - 1], a[i + 1]) + 1 - a[i]));
		}
		ans = sum;
		if (!(n & 1)) {
			for (int i = n - 2; i >= 2; i -= 2) {
				sum -= max (0, max (a[i - 1], a[i + 1]) + 1 - a[i]);
				sum += max (0, max (a[i], a[i + 2]) + 1 - a[i + 1]);
				ans = min (ans, sum);
			}
		}
		printf ("%lld\n", ans);
	}
	return 0;
}
~~~

没开 long long 见祖宗，十年打水一场空。

---

## 作者：cachejtt (赞：0)

## 题意
有一个长度为 $n$ 的小镇，上面排列着高度为 $h_i$ 的楼房，当一个楼房比它两边的楼房都要高时，我们称这个楼房是“帅气的”。注意最两边的两个楼房不算作是“帅气的”。

我们可以在一个楼房上盖砖头使得它的高度增加一。

现在问你，在保证“帅气的”楼房最多的情况下，最少需要盖多少块砖头？

## 思路
### 性质

##### 奇数
注意到 $n$ 为奇数时，“帅气的”楼房的个数一定为 $\frac{(n-1)}{2}$，且这些“帅气的”楼房一定在第 $2,4,6,\dots,n-1$ 的位置上，那么我们只需要做这些位置所需要叠的砖头数相加即可。注意当这个楼房本身是“帅气的”的时候并不需要盖砖头。

##### 偶数
当$n$ 为偶数时，我们最多可以让 $\frac{n-2}{2}$ 个楼房变成“帅气的”，这时就要考虑让中间的哪几个楼房变成“帅气的”了。

注意到两个“帅气的”楼房中间至少间隔一个小楼房，而中间一共有 $n-2$ 个楼房，其中有 $\frac{n-2}{2}$ 个楼房是“帅气的”，意味着有 $\frac{n-2}{2}$ 个小楼房。若每个“帅气的”楼房间间隔一个，还会多出一个空位，这意味着某两个“帅气的”楼房间有两个空位，也可能是头号位或尾号位的间隔。

但是，无论如何，这些位置都可以表示成：
$ 2,4,\dots,2\times i,2\times i+3,2\times i+5,\dots,n-1$，也就是说是一个以 $2$ 开始，间隔为 $2$ 的前缀序列，和一个以 $n-1$ 结束，间隔为 $2$ 的后缀序列合并而成。其中序列长度可以为 $0$。

### 做法

##### 奇数
如上所述，只需遍历对应位置，加上对应值即可

##### 偶数
开一个前缀数组 $sum$ 和后缀数组 $sum1$，预处理二者的值，最后枚举间断点，找最小值即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define int ll
using namespace std;
int t,n,h[100005],p,ans,ans1;
int sum[100005],sum1[100005];
signed main(){
  std::ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    ans=0;
    memset(sum1,0,sizeof(sum1));
    memset(sum,0,sizeof(sum));
    rep(i,1,n)cin>>h[i];
    if(n%2==1){
      rep(ii,1,n/2){
        p=ii*2;
        if(h[p]<=max(h[p-1],h[p+1])+1)ans+=max(h[p-1],h[p+1])+1-h[p];
      }
      cout<<ans<<"\n";
    }
    else{
      ans=0x3f3f3f3f3f3f3f3fll;
      for(int i=2;i<n;i+=2)sum[i]=sum[i-2]+max(0ll,max(h[i-1],h[i+1])+1-h[i]);
      for(int i=n-1;i>=2;i-=2)sum1[i]=sum1[i+2]+max(0ll,max(h[i-1],h[i+1])+1-h[i]);
      for(int i=1;i<=n-1;i+=2){
        ans=min(ans,sum[i-1]+sum1[i+2]);
      }
      cout<<ans<<"\n";
    }
  }
  return 0;
}
```

---

