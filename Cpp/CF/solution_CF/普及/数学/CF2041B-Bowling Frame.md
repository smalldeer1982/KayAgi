# Bowling Frame

## 题目描述

题面涉及到政治敏感内容，请在 Codeforces 查阅。

## 样例 #1

### 输入

```
4
1 2
3 2
3 3
12 0```

### 输出

```
2
2
3
4```

# 题解

## 作者：沉石鱼惊旋 (赞：1)

## B. Bowling Frame

给定 $w$ 个白点和 $b$ 个黑点，拼三角形，要求三角形第 $i$ 行有 $i$ 个**同色**的点，最大化三角形行数。

多测，$1\leq t\leq 100$。

$0\leq w,b\leq 10^9$。

---

赛时看了喜提第一眼不会。丢给队友去写别的题了。

结论题。

定义 $S(n)=\frac{n(n+1)}{2}$ 即行数为 $n$ 的三角形需要的点数，不难通过等差数列求和推出。

答案即为最大的 $n$ 满足 $S(n)\leq w+b$。

接下来开始证明。首先如果 $w'\leq w,b'\leq b$ 且有 $w'$ 和 $b'$ 就可以组成一个三角形，那么 $w$ 和 $b$ 一定也能组成这么大的三角形。因为可以有剩余。

所以我们证明恰好等于的情况就可以。。

数学归纳法证明。

$n=0$ 时，$w,b$ 取任何值都可以拼出大小为 $n$ 的三角形。相当于一个不用就可以了。

若 $n=k$ 时，对于 $w$ 取任意值，$b$ 取任意值，成立，则 $n=k+1$ 时，$w$ 取任意值，$b$ 取任意值，也成立。

考虑新加的第 $k+1$ 行填什么颜色。**只要能填上，就可以化到 $n=k$ 时的情况**。

也就是说我们只需要证明：在拼出行数为 $k$ 的三角形时，此时 $w,b$ 取任何值（满足 $w+b=S(k+1)$），他们的的最大值都会比 $k+1$ 大也就是可以拼出第 $k+1$ 行。

第 $k+1$ 行有 $k+1$ 个点，而 $k+1$ 行的三角形需要 $S(k)$ 个点，较多颜色的那个点**至少**有 $\lceil\frac{S(k+1)}{2}\rceil$ 个。

证明 $k$ 取任意值都有 $k+1\leq \lceil\frac{S(k+1)}{2}\rceil$ 即可。

~~仍然可以数学归纳法。~~

大力拆式子。

$$
\begin{aligned}
k+1 &\leq \lceil\dfrac{S(k+1)}{2}\rceil\\
k+1 &\leq \lceil\dfrac{\frac{(k+1)(k+2)}{2}}{2}\rceil\\
k+1 &\leq \lfloor\dfrac{\frac{(k+1)(k+2)}{2}+1}{2}\rfloor\\
2(k+1)&\leq \dfrac{(k+1)(k+2)}{2}+1\\
4(k+1)&\leq (k+1)(k+2)+2\\
2(k+1)+2k+2&\leq 2(k+1)+k(k+1)+2\\
2k&\leq k(k+1)
\end{aligned}
$$

这个不等式在 $k=0$ 和 $k\geq 1$ 的时候都显然成立。因此 $k+1\leq \lceil\frac{S(k+1)}{2}\rceil$ 就是成立的。

<https://codeforces.com/contest/2041/submission/293495113>

---

## 作者：mnlbnkk (赞：1)

# 题意
一个 $n$ 排的三角形，第 $i$ 排有 $i$ 个球，球有黑色和白色两种颜色，一排只能放同样的颜色的球，求最多放几排
# 做法
首先这道题目有个要点就是怎么摆放都是可以的，如果放出来不是正确答案就是你的放置方法不优。所以不用考虑到底是黑球还是白球的情况。\
接下来做法就很简单了，把整的三角形需要的球的数量放到数组里，二分去找到可以放的最大三角形就可以了。\
补录：为什么我求出来的答案小了是因为方案不优？因为我么只用考虑黑球和白球之和正好是三角数的情况，因为其他情况可以通过把一些球给丢掉，然后假设两个的球的数量正好是 $x$，$y$，那就显而易见了，首先 $x + y = 1 + 2 + \ldots + n$ 然后x又可以表示成 $p_1 + p_2 + \dots +  p_k$ ，其中 $p_i\le n$，$p_i=2^t$，所以 $y$ 只用插空去放就OK了。
# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define P pair<ll,ll>
#define fi first
#define se second
#define Pp pair<ll,pair<ll,ll>>
using namespace std;
const ll N=1e6+9;
ll a,b,num[N];
int main()
{
	ll T;
	cin>>T;
	for(int i=1;i<N;i++)num[i]=num[i-1]+i;
	while(T--)
	{
		cin>>a>>b;
		ll tmp=a+b,lt=1,rt=N-1,ans;
		while(lt<=rt)
		{
			ll mid=lt+rt>>1;
			if(num[mid]>tmp) rt=mid-1;
			else lt=mid+1,ans=mid;
		}
		cout<<ans<<endl;
	}
	return 0;
 } 
```

---

## 作者：queenbee (赞：0)

# CF2041B Bowling Frame 题解

## 思路

  [题目传送门](https://www.luogu.com.cn/problem/CF2041B)，对于 $w+b$ 个保龄球，可以先将其摆放成一个没有限制的最大三角形，再考虑限制条件，将白色和黑色中少的按限制排列，再用多的填补缝隙，发现当有 $n$ 行时，总有组合使得这些行的保龄球数量为 $sum$，满足 $sum=i,1\le i \le \frac {n\times(n+1)}2$，所以当 $\min(w,b) \le \frac {n\times(n+1)}2$ 时总有情况满足限制条件，只需求出能拼成的最大三角形边长即可。一个边长为 $n$ 的三角形共需要 $\frac {n\times(n+1)}2$ 个保龄球瓶，$\frac {n\times(n+1)}2=w+b$ 的正数解向下取整即为所求，由求根公式得 $ans=\lfloor \frac {-1+\sqrt{1+8\times(w+b)}} 2\rfloor$。

## 程序
```cpp
#include<bits/stdc++.h>	//我爱万能头 
using namespace std;
#define int long long
int t;
int w,b;
double ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>w>>b;
		ans=(-1+sqrt(1+8*(w+b)))/2.0;	//求解 
		cout<<floor(ans)<<endl;		
	}
	return 0;	//完结撒花 
}

```

---

## 作者：Hughpig (赞：0)

先考虑如果瓶子不带颜色咋做。设瓶子个数是 $n$，最多能摆成 $x$ 排。摆出 $x$ 排需要的瓶子个数是 $\displaystyle\sum_{i=1}^{x}i=\dfrac{x(x+1)}{2}=\dfrac{x^2+x}{2}$。所以 $x$ 是 $\sqrt{n}$ 级别的。直接枚举摆出多少排的时间复杂度为 $O(\sqrt n)$。

思考带上这个颜色咋做。显然因为颜色的限制，可能会造成一些瓶子的浪费使得最终答案变小。为了最大化能摆的排数，我们要尽可能减少瓶子的浪费。

假设不带颜色最多能摆 $x$ 排，剩余 $n-\dfrac{x^2+x}{x}$ 个瓶子。先拿黑色瓶子摆，设最多能摆 $y$ 排。如果摆完没有瓶子剩余，那么不会造成任何浪费，直接去摆白色瓶子即可。

如果有浪费的话：设浪费了 $y'$ 个瓶子，显然 $y'\le y$，否则可以再摆一排，不符合最多能摆 $y$ 排的设定。

然后我们把当前摆完的最后一排拿出来，共有 $y+y'$ 个空余瓶子。如果 $y+y'\le x$，那么可以直接放到对应的排，不会造成任何浪费。否则就在前面找有 $y+1-y'$ 一排空出来，和浪费的正好凑满新的有 $y+1$ 的瓶子的一排，也不会造成浪费。

然后拿白瓶子把剩下的空位填上即可。由于黑瓶子没有浪费，白瓶子把最优情况所剩余的空位都填了，所以可以填到最优情况，不造成浪费。

所以颜色对答案没有影响，直接枚举即可。时间复杂度 $O(\sqrt{n})$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll t,w,b;

int main(){
    cin>>t;
    while(t--){
        cin>>w>>b;
        w+=b;
        ll cnt=1;
        while(w>=cnt)w-=cnt,++cnt;
        cout<<cnt-1<<'\n';
    }
}
```

---

## 作者：LittleDrinks (赞：0)

## [B. Bowling Frame](https://codeforces.com/contest/2041/problem/B)

不考虑颜色的限制，答案为最大的满足 $(\sum_{i=1}^ki)\leq w+b$ 的 $k$，这是原问题答案的上界。

首先考虑，当 $w+b=\dfrac{k(k+1)}{2}$ 时，必然有 $w,b\leq\dfrac{k(k+1)}{2}$。选取 $1$ 到 $k$ 共 $k$ 个数中的若干个相加，可以得到 $[1,\dfrac{k(k+1)}{2}]$ 中的所有数字，因此，存在一种放置方法可以恰好把 $b$ 个保龄球瓶全部按照要求放好，由于总和的限制，此时剩下的空位个数必然为 $w$。于是我们证明了，当 $w+b=\dfrac{k(k+1)}{2}$ 的时候，可以取得答案的上界。

然后考虑，当 $w+b>\dfrac{k(k+1)}{2}$ 时，肯定会浪费掉若干个保龄球瓶，舍弃这若干个保龄球瓶后两种颜色瓶子的个数满足 $w'+b'=\dfrac{k(k+1)}{2}$，化归到上一种情况，也可以取到答案的上界。

综上，开头所说的答案上界 $k$ 即为原问题的答案。可以用求根公式 $O(1)$ 求出，也可以直接累加 $O(\sqrt{w+b})$ 求出。

#### [AC 代码](https://codeforces.com/contest/2041/submission/293293697)

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve()
{
    int w, b;
    cin >> w >> b;
    ll ans=1;
    for (; ans*(ans+1)/2 <= w+b; ++ans);
    cout << ans-1 << endl;
}

int main()
{
    int t; cin >> t;
    while (t--) { solve(); }
}
```

---

