# Cow and Friend

## 题目描述

贝茜有太多朋友了。因为她是所有人最喜欢的牛。她的朋友兔兔在试着跳到贝茜所在的地方，那么他们就可以玩了。

更具体地，兔兔他想跳几步使得他能从 $(0,0)$ 跳到 $(x,0)$。他只想着在二维平面上从一个点跳到另一个点当且仅当两个点的欧几里得距离是他 $n$ 个喜欢的数中的其中一个，也就是 $a_1, a_2, \ldots a_n$。

兔兔最少要跳几步才能从 $(0,0)$ 跳到 $(x,0)$ 呢？兔兔不必跳到一个整数的坐标，换句话说，他可以跳到一个不是整数的坐标。可以证明，兔兔总可以到达他的终点。

重新在此声明，两个点的欧几里得距离可以使用公式算出，设两个点的坐标分别为 $x_1,y_1$ 以及 $x_2,y_2$，那么有公式 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

如下图所示，如果兔兔喜欢的数是 $1$ 和 $3$的话，那么他可以跳两步从 $(0,0)$ 跳到 $(4,0)$。值得注意的是，这里还有别的方式使得他可以用 $2$ 步跳到 $(4,0)$ 的方法。

![CF1307B Cow and Friend](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1307B/f7586d192526c0aed9ac1b72d0c3e07431d38d89.png)

图中的就是样例的第一个测试的示意图，两次跳的距离都是 $3$ -- 一个兔兔喜欢的数。换句话说，每一次兔兔都会选一个数 $a_i$，然后任意地跳到一个与这个点距离为 $a_i$ 的地方。 相同的数可以使用多次。

## 样例 #1

### 输入

```
4
2 4
1 3
3 12
3 4 5
1 5
5
2 10
15 4```

### 输出

```
2
3
1
2```

# 题解

## 作者：cqbztz2 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1307B)

[更好的阅读体验？](https://www.luogu.com.cn/blog/493271/solution-cf1307b)

# Thinking

题目范围 $ n \leq 10^5 $，因此算法时间复杂度预计 $ O(n) $ 或 $ O(n$ $ \log $ $n) $。

通过时间复杂度预计算法，贪心，最多带一个二分。

考虑贪心：

首先判断一个特殊情况：如果有 $ a_i  = x $，即奶牛可以一次跳到终点，输出 $ 1 $。

对于其他情况：

由于奶牛可以可以跳到非整数坐标的点上，所以对于一段距离，只要这段距离小于奶牛弹跳高度的 $ 2 $ 倍，奶牛就可以分 $ 2 $ 次跳过去，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ylnftks.png)

同样，若这段距离小于奶牛的弹跳高度，奶牛显然能分两次跳过去。

题目要求跳跃次数最少，所以尽可能的每次跳跃最远，即每次跳跃 $ \sum max(a_i) $。而最后当距离终点不足每次跳跃的距离时，跳 $ 2 $ 次即可，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7w1tpl3w.png)

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int T,n,x,a,maxn;
  signed main(){
      cin>>T;
      while(T--){
          maxn=0;
          cin>>n>>x;
          bool flag=false;
          for(int i=1;i<=n;i++){
              cin>>a;
              if(a==x){
                  flag=1;
              }
              maxn=max(maxn,a);
          }
          if(flag==1){
              cout<<1<<endl;
          }
          else if(maxn>x){
              cout<<2<<endl;
          }
          else{
              cout<<int(ceil(x/(maxn*1.0)))<<endl;
          }
      }
      return 0;
  } 
```


---

## 作者：Reanap (赞：2)

在考场上，我被这道题搞自闭了，下来问了可爱的ytt，
~~开心地~~
发现他也自闭在这道题上了，
~~高度欣慰~~，就因为这道恶心的贪心，导致我只做了$A$ $C$两道题，快乐掉分。

一看这道题
~~根据多年贪心经验~~
就知道肯定是用最大值去选，即用总距离取个模，最后会剩下一段距离。

这段距离该怎么处理呢
（本题最大难点）
，很轻易地想到了三角形。根据两边之和大于第三边，两边之差小于第三边，我们发现剩下的这段距离同样可以用这个最大边处理，于是我傻乎乎地直接用两条最大边搭桥跨过这段距离，然后考场上我就这样子
~~WA穿了~~
。。。

用最大边构造等腰三角形搭桥没错，但是这不是最优解。仔细想一想，最终剩下一段的距离，如果我们少选一条最长边，发现离x的距离仍然满足三角形的性质，这不就比刚才少用了一条边吗？

因此代码打起来就很简单了，在没有与$x$相同的$a_i$的情况下就用上述情况解决，否则输出$1$。

细节见代码：

```cpp
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;
int n , x , a[MAXN];
map <int , int> M; 
int main() {
	int T;
	scanf("%d" , &T);
	while(T -- > 0) {
		M.clear();
		scanf("%d %d" , &n , &x);
		for (int i = 1; i <= n; ++i) {
			scanf("%d" , &a[i]);
			M[a[i]] = 1;
		}
		sort(a + 1 , a + 1 + n);
		if(M[x]) {
			printf("1\n");
			continue;
		}
		int ans = 0;
		if(x % a[n] == 0) {
			printf("%d\n" , x / a[n]);
			continue;
		}
		ans += x / a[n];
		printf("%d\n" , max(2 , ans + 1));
	}
	return 0;
}

```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1307/B)
就是计算从点 $(0,0)$ 跳到点 $(x,0)$ 所需的最少跳跃次数。每次跳跃的距离必须是兔兔喜欢的数之一。

## 思路
这题乍一看很复杂，但我们看看题中的这一句话：

> 可以证明，兔兔总可以到达他的终点。

我们可以大胆猜测，每次跳 $\max \limits_{1 \leq i \leq n}{a_i}$ 距离就是最优解，步数为 $\lceil \frac{x}{a_{max}} \rceil$ 步。

特判掉 $a_i = x$ 的情况即可。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n, x;
		cin >> n >> x;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		// 检查是否有 a_i == x
		bool hasX = false;
		for (int num : a) {
			if (num == x) {
				hasX = true;
				break;
			}
		}
		if (hasX) {
			cout << "1\n";
			continue;
		}
		// 找到最大的 a_i
		int maxA = *max_element(a, a+n);
		// 计算最少跳跃次数
		int jumps = max(2, (x + maxA - 1) / maxA);
		cout << jumps << '\n';
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn) $，本题中 $\sum{n} \leq 10^5$，可以通过本题。

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1307B)

[CF 传送门](https://codeforces.com/problemset/problem/1307/B)

[AC 记录](https://codeforces.com/contest/1307/submission/291191582)
# 题意简述
有一个点，初始在 $(0,0)$，已知这个点每次可以移动 $a_i\ (1\le i\le n)$ 个单位长度，求该点至少要移动几次才可以到达 $(0,x)$。
# 题解
首先画一个以 $(0,0)$ 为圆心，以 $a_i$ 为半径的圆（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/kpji1x8x.png)

显然，点 $A$ 到圆上任意一点的距离都为 $a_i$，因此，从 $A$ 出发，可以到达圆上任意一点。  
这时，画一个以 $(0,x)$ 为圆心，$a_i$ 为半径的圆。  
那么该圆上任意一点都可以到达 $(0,x)$。  
分为两种情况：
1. 该圆与第一个圆相交：
   ![](https://cdn.luogu.com.cn/upload/image_hosting/3155q7q0.png)  
   此时两圆的交点就是中转点。
   ![](https://cdn.luogu.com.cn/upload/image_hosting/lx8ft7zc.png)
   那么就需要移动两次。  
   只要 $a_i\times 2>x$ 即可（两圆必有交点）。
2. 该圆不与第一个圆相交：  
   此时仅需将 $A$ 点向右平移 $k\times a_i$ 个单位长度使两圆相交，如下图。
   ![](https://cdn.luogu.com.cn/upload/image_hosting/wllyocrl.png)

这里可以注意到，$a_i$ 要尽量大，这样更好满足 $a_i\times 2>x$，且点左移时也可以更快让两圆相交。

**注：当有 $a_i=x$ 时，直接输出 $1$。**
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
int t,n,x,a;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x)
{
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
signed main(){
	CLOSE
	cin>>t;
	while(t--){
	    cin>>n>>x;
	    int maxx=0,cnt=0,flag=0;
	    for(int i=1;i<=n;i++){
	        cin>>a;
	        maxx=max(maxx,a);//找最大的a[i]
	        if(a==x&&!flag){//若a[i]=x
	            flag=1;
	            cout<<"1\n";//直接输出1
	        }
	    }
	    int p=x/maxx;//往右移动的次数
	    if(flag) continue;
	    if(x<maxx) cout<<"2\n";
	    else if(x%maxx==0) cout<<p<<'\n';//可能正好可以到x
	    else cout<<p+1<<'\n';//否则就要折返，次数+1
	}
	return 0;
}
```

---

## 作者：cqbzlwz (赞：1)

#### [题目](https://www.luogu.com.cn/problem/CF1307B)

#### 思路

最开始以为是 DP 之类的东西，结果根本没法做，后来注意到了这句话：“注意，兔子可以跳到非整数坐标的点上。”然后就可以发现可以通过跳两次来前进一个原本构造不出来的长度，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/owiu0m8d.png)

不难发现，当兔兔能跳的长度为 $t$ 时，它可以花两步跳到横坐标在 $[0, 2*t]$，纵坐标为 $0$ 的地方。(可以用三角形三边的关系证明，即任意两边之和大于第三边，但可以横着跳 $2$ 步到 $(0,2*t)$ )。

横着跳显然要快一点，因此可以先横着跳。

因此可以设计出贪心：**优先横着跳**，如果**不能刚好**跳到终点就再跳 $2$ 步。

然而真的对吗？~~很明显不对。~~ 像这种题目，好比蜗牛爬井问题，要仔细检查**接近终点的**地方。

这是原来的策略：如果我们不能刚好跳到终点，设还剩下 $k$ 个单位长度，则这 $k$ 个单位长度跳 $2$ 次完成。

改变策略：观察跳 $2$ 次的范围： $[0,2*t]$ ，而 $k < t$ ，所以 $k + t$ 仍小于 $2t$ ！!因此我们可以先跳到**距离终点** $t+k$ 的位置，再跳 $2$ 步到终点，这样能省下 $1$ 步。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, x, a[100005], ans;
int main() {
	scanf("%d", &T);
	while (T--) {
		ans = INT_MAX;
		scanf("%d%d", &n, &x);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			int g;
			if (x % a[i]) {
				g = max(x / a[i] - 1, 0) + 2;
			} else {
				g = x / a[i];
			}
			ans = min(ans, g);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：npqenqpve (赞：1)

### 题意：

在数轴上给你一个点 $(0,n)$，和一些你可以走的距离 $a_i$ ，问最少多少次才能恰好走到 $(0,n)$ .

### 思路：

首先它说是最少次数，那肯定尽量走最长的距离，这么走最后会剩下 $n$ 对 $\max\{a_i\}$ 取模这么长需要走，显然这部分是可以走俩 $\max\{a_i\}$ 构成一个等腰三角形走完的，但答案难道就是
$$
\frac{n}{\max\{a_i\}}+2
$$
显然不是的，思考怎么让自己少走点，比如后退一步（少走一步最长距离），然后发现必然仍然满足三角形性质（此处排除恰好走完的情况，恰好走完特判就行），则省下了一步，既然如此，哪能不能少走两步呢，显然不可以，毕竟此题中 $2\times\max\{a_i\}+k$ 一定大于等于 $2\times\max\{a_i\}$ 。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,bool>m;
int main()
{
    int t,n,x,maxn=-1,ans=0,a[100005];cin>>t;
    while(t--)
    {
        cin>>n>>x;
        ans=maxn=0;
        memset(a,0,sizeof(a));
        m.clear();
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            m[a[i]]=1;
            maxn=max(maxn,a[i]);
        }
        if(m[x]==1) cout<<1<<"\n";
        else
        {
            cout<</*maxn<<" "<<*/max(2,x/maxn+(!(x%maxn==0)))<<"\n";
        }
    }
    system("pause");
}
```



---

## 作者：xlqs23 (赞：1)

**题意:**

已知$n$个可走距离，和$x$，问牛从$(0,0)$到$(x,0)$最少需要走多少步?牛可以这样直走，可以斜着走，每个可走距离可以用无限次。

**思路：**

设某个可走距离为k，走的步数一共就三个情况。

1.一次到达，满足$k==x$;

2.两次到达，满足$k>x$;(由勾股定理得，两个最小边之和大于第三边，则两次肯定是能到达的)。

3.多次到达，$k<x$;(我们只需用最大可走距离 $ceil(x/mx)$ )
举个例子来说:

3 12

3 4 5

这就是多次到达的问题，$ceil(12/5)=3$,也就是牛走了三次5.可以这样来分析，先让牛走直线，还剩7的距离，两个5走一个三角形的两边。

**AC代码：**

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,k,x,mx=0;
		bool flag=false;
		scanf("%d%d",&n,&x);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&k);
			if(k==x)	flag=true;
			mx=max(mx,k);
		}	
		if(flag)	puts("1");
		else
			printf("%d\n",max(2,(mx+x-1)/mx));//向下取整 
	}
	return 0;
}

---

## 作者：Ak_hjc_using (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1307B)

### 思路

考虑贪心。

先判断能不能一次整好跳过去，如果可以，输出 $1$。
如果不能一次整好跳到，就用最长的跳。

两次最长的可以跳到 $0$ 到最长距离中间的任何一个距离。
跳的次数等于：$(x + \max (a) - l) \div \max (a)$。
### 代码：
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int T;
    cin >> T;
    while(T --) {
        int n, x;
        cin >> n >> x;
        int l = 0;
        int res = 0;
        for(int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            if(x == temp) res = 1;
            l = max(l, temp);
        }
        if(res == 1) {
            cout << res << endl;
            continue;
        }
        res = 2;
        res = max(res, (x + l - 1) / l);
        cout << res << endl;
    }
}
```

---

## 作者：liuli688 (赞：0)

### 题目大意
在平面直角坐标系的 $(0,0)$ 处有一只兔子，它要跳到 $(x,0)$ 处。兔子可以跳到和它现在所在的点的欧几里得距离为一个长度为 $n$ 的数组 $a$ $a_1,a_2,\dots,a_n$的任意坐标为实数的点上。问兔子最少要跳几次。

### 思路
显然，想要跳的次数最少，要选 $a$ 中最大的元素（设它为 $mx$）当做兔子跳跃的距离。但是注意特判：如果 $a$ 中有元素的值和 $x$ 相等，则一次就可以跳到 $(x,0)$ 处。另外，如果没有元素的值和 $x$ 相等，但有元素大于 $x$，则两次也可以跳到 $(x,0)$ 处。

理一下思路： 
- 如果 $a$ 中有元素的值和 $x$ 相等，输出 `1`；
- 如果没有元素的值和 $x$ 相等，但有元素大于 $x$，输出 `2`；
- 否则，输出 $\lceil\frac{x}{mx}\rceil$。
### 代码：
```cpp
#define MAIN int main()
#define SPEEDUP ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define USING using namespace std
#define END return 0
#define DB double
#define LL long long
#define ULL unsigned long long
#define LD long double
#define STR string
#define EL '\n'
#define BK break
#define CTN continue
#define INF INT_MAX
#define UINF INT_MIN
#define IN(n) cin >> n
#define OUT(n) cout << n
#define OUTL(n) cout << n << EL
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
#include<bits/stdc++.h>
USING;
int t,n,x,a,i,mx;
bool flag;
MAIN
{
    IN(t);
    while(t--)
	{
        mx = UINF;
        IN(n >> x);
        flag = false;
        FP(i,0,n)
		{
            IN(a);
            if(a == x)//特判 a 中有元素的值和 x 相等
                flag = true;
            mx = max(mx,a);
        }
        if(flag)//特判
            OUTL(1);
        else if(mx > x)//判断是否有元素大于 x
            OUTL(2);
        else//数学计算
            OUTL(int(ceil(x / ((DB)mx))));
      }
      END;
  } 
```

---

## 作者：Harry_Hedwig (赞：0)

简单数论题~~最容易自闭了好耶~~。
# 0x00 思路
~~欢迎收看新一期废话一堆。~~

总结下来就几句话。

>一只兔子位于二维平面的原点 $(0,0)$ 处，它想通过一系列的跳跃，跳到点 $(x,0)$ 处。

>给定一个长度为 $n$ 的数组 $a_1,a_2,\dots,a_n$。

>兔子能从一个点跳到另一个点（**任意点，不一定为格点**），**当且仅当**两点之间的距离**等于上述数组中的某个元素的值**。

>请问，兔子从 $(0,0)$ 到 $(x,0)$ **最少**需要跳几次？

首先想，是不是 dp？

明显不是，因为 $x\le 10^9$，明显会炸的很惨。

然后我们就没思路了。

但是这题在 T2 的位置！这说明什么！我们需要瞎搞！

~~于是打开了几何画板。~~

嗯……随便跳……那不是圆吗？

于是我们画了一个圆。

![](https://cdn.luogu.com.cn/upload/image_hosting/ka5h74ig.png)

既然是随便跳，于是我们在圆上随意取一个点，而这个点**一定**可以跳到，由于没有到达终点，于是我们又加了一个圆。

![](https://cdn.luogu.com.cn/upload/image_hosting/fz6bbvsc.png)

为了瞎搞，我们打开了追踪。像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/8pvud3dp.png)

我们发现，经过两次长度均为 $a_i$ 的跳跃后，我们可以跳跃到以原点为圆心， $2\times a_i$ 为半径的圆中的**任意**一个点。

既然如此，我们只需要让终点**被覆盖**在这个大圆里面，即可在两次以内到达。

而最大可以触及的半径，就是最大的 $a_i$ 的两倍（设为 $m$）。所以如果 $x\le m\times 2$ 最多两次。而当在 $a_{1\sim n}$ 中有 $x$ 这个数时一次即可。

但是如果情况像这样呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/j5g9iqkz.png)

我们就一定会想要把终点囊括在 $2\times m$ 的圆（以兔子所在点为圆心）之中。

而最快的办法是**每一次**都跳最大值。

所以得出柿子：

$$2+\lceil(x-2\times m)\div m)\rceil$$

结束！完结撒花！

等等，你问我为什么要向上取整？

想一想，如果不向上取整那么跳完算出的次数之后，兔子仍然不可以两次跳到终点，始终还差一丢丢，所以需要向上取整，完全进入~~射程~~范围之内。

# Code
```c
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,jump[N];
bool flag=0;
int main()
{
//	freopen("rabbit.in","r",stdin);
//	freopen("rabbit.out","w",stdout);
	int t,i,ax=0;
	scanf("%d",&t);
	while(t--)
	{
		flag=0;//是否可以1次直达
		ax=0;//m
		scanf("%d %d",&n,&m);//n,x
		for(i=1;i<=n;i++)
		{
			scanf("%d",&jump[i]);
			ax=max(ax,jump[i]);
			if(jump[i]==m)
				flag=1;
		}
		if(flag)
		{
			printf("1\n");
			continue;
		}
		if(ax+ax>=m)//已经可以2次到达
		{
			printf("2\n");
			continue;
		}
		printf("%d\n",2+(int)ceil((m-ax-ax)*1.0/ax));//不可以2次直达
	}
	return 0;
}
```

---

## 作者：cqbzhyf (赞：0)

这道题目是一次考试偶然遇到的……

[题面](https://www.luogu.com.cn/problem/CF1307B)

首先这是道**思维题**，但是由于受到搜索的熏陶，一开始就迭代加深，后来慢慢意识到不对劲（看到这组数据）：$n=2 ,k=5,a_1=15,a_2=4$.

于是手画了几个图，发现是道难（shui）题（ti）。

首先排序方便处理。

然后发现如果某个元素长度大于 $\frac{k}{2}$，直接如下跳跃，只需要两次：

![](http://61.186.173.89:2019/2022/02/18/a91e29bc5c127.png)

否则就一直用最大值，既是 $\frac{k}{Max}$ 向上取整。

注意特判某个元素等于 $k$，直接输出 $1$.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int num=0,ch=0;
	char c=getchar();
	while(!isdigit(c))ch|=(c=='-'),c=getchar();
	while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();
	return ch?-num:num;
}
int n,a[100005],x;
inline bool cmp(int x,int y){return x>y;}
signed main(){
//	freopen("rabbit.in","r",stdin);
//	freopen("rabbit.out","w",stdout);
	int T=read();
	while(T--){
		n=read(),x=read();
		bool flag=false;
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]==x)flag=true;
		}
		if(flag){
			puts("1");
		}else{
			sort(a+1,a+1+n,cmp);
			flag=false;
			for(int i=1;i<=n;++i){
				if(a[i]*1.0>x*1.0/2){
					puts("2");
					flag=true;
					break;
				}
			}
			if(!flag){
				printf("%d\n",(int)ceil(x*1.0/a[1]));
			}
		}
	}	
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

考场上二分写挂 60 pts QWQ。

看到本题，数据范围很大，显然是用数学方法。

那么，我们分几种情况讨论。

首先，$\forall i\in[1,n]a_i=x$ 答案为 $1$。（显然）

现在答案至少为 $2$，那么我们继续讨论。

如果 $\forall i\in[1,n]a_i>x$，那么我们可以以 $a_i$ 为腰构造等腰三角形，答案为 $2$。  

否则，我们取 $k=\max\limits_{i=1}^n a_i$。那么，我们先拼 $k$ ，当剩下的长度 $l<2k$ 时，以 $k$ 为腰构造等腰三角形，那么化简可得，答案为 $\lceil\dfrac{x}{k}\rceil$。

时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
}
const int maxn=1e5+5;
int T,n,x,a[maxn];
int main(){
	T=read();
	while(T--){
		bool p=0;
		n=read(),x=read();
		int k=-1; 
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]==x)
				p=1;
			k=max(k,a[i]);
		}
		if(p)
			puts("1");
		else if(k>x)
			puts("2");
		else
			printf("%d\n",(x+k-1)/k);
	}
	return 0;
}
```

---

## 作者：YYen (赞：0)

### 思路：贪心
约定兔兔目前的位置为 $ last $ ，想要跳到的地方为 $ x $ ，
那么从 $ last $ 跳到 $ x $ 的跳法只有 $ 3 $ 种情况：

情况①： $ 1 $ 步到达。该情况仅成立于 $ {\exists}a_{i}=x-last $ 。

情况②： $ 2 $ 步到达。该情况仅成立于以 $ (0,last) $ 和 $ (0, x) $ 为圆心， $ \max(a_{i}) $ 为半径画圆，两圆有交点时，亦即 $ 2 \times \max(a_{i}) \geq x - last $ 。

情况③：若干步到达。此情况用于上述情况①和情况②条件均不满足时。只需要从 $ last $ 出发，不断使用 $ \max(a_{i}) $ 向 $ x $ 逼近，直到情况①或情况②任一满足。

### 代码
```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

int a[100005];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        map<int, int> m; // m维护ai的出现次数 
        int n, x;
        cin >> n >> x;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            m[a[i]]++; // 记录ai的出现次数 
        }
        sort(a + 1, a + n + 1);
        int last = 0, ans = 0;
        while (last != x)
        {
            if (m[x - last]) // 1步到达 
            {
                ans++;
                last = x;
            }
            else if (2 * a[n] >= x - last) // 2步到达 
            {
                ans += 2;
                last = x;
            }
            else // 若干步到达 
            {
                ans += ceil(1.0 * (x - 2 * a[n]) / a[n]);
                last += ceil(1.0 * (x - 2 * a[n]) / a[n]) * a[n];
            }
        }
        cout << ans << endl; 
    }
    return 0;
}
```


---

## 作者：Ludo (赞：0)

## Part I. 题意简述

就是任意在一堆数里面选，每次可以跳到距离与你选的那个数相同的那些点，问你最快到达某个点要多久。

## Part II. 思考过程

其实自己卡了很久。这里就提供一个思考方向。

第一步，观察数据范围，能更容易入手，那么可以发现时间复杂度大概是 $O(T \times N) = O(10^9)$ （可能有点不严谨，建议请留个言吧）。并且考虑到输入需要输入 $n+2$ 个数，我们需要使用 $O(n)$ 算法通过此题。


我们第二步，思考一个问题，为什么题目会那么笃定地说一定能到达终点？

那就应该只有一个数喜欢的时候也可以到终点对吧。

考虑以下两张图。

第一个是样例的第 $4$ 组数据，一开始并没有样例解释。

尝试自己推一下吧。其实疑惑的地方就是这里，因为你不知道怎么走。

解决这种题目，实在想不出时，可以考虑使用几何画板等工具画一画。

尝试一个数喜欢是不是能到终点。

首先在起点作一个半径是 $15$ 的圆。然后也在终点作一个半径是 $15$ 的圆，因为我们要试着找到一个最短的路，最短的路径应该在圆交点处产生。找到交点了！一看，跟样例解释一样。中途点都是 $(5,10 \sqrt{2})$。

![](https://cdn.luogu.com.cn/upload/image_hosting/kbwx3mjf.png)

因此，只要两个圆（分别以起点终点为圆心）相交或相切，那么两步即可到达。

第二个例子，两圆相离了。转个角度一想，那跳几下（跳几下，使起点位置发生改变，起点的圆也顺着改变位置）就能让两圆相切或相离了呀！

有颜色的线段是跳跃的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/jmhi4jd7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/bhu4r6vn.png)

如果想样例第二组测试数据那样呢？那就直接橫跳呀，因为直线距离最短！

## Part III. 代码

讲了好多，觉得有点啰嗦。看图一边理解吧。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int t,n,a[100001],k,ak,tmp,ans;
int main()
{
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d",&n,&k);
		ans=2147483647; //把ans置为最大值
		for (int i=1;i<=n;i++)  //当时不知道拿最大的跳就行，只知道要O(n)做法所以没去管
		{
			scanf("%d",&a[i]);
			tmp=0;
			ak=k;
			if (ak%a[i]==0) //一直横着跳就好
			{
				tmp=(ak/a[i]);
				ak=0;
			}
			else
			{
				if (ak>2*a[i])
				{
					tmp+=(ak-2*a[i])/a[i]; //起点位置变化，步数也要加
					ak-=tmp*a[i];          //起点与终点的横坐标之差
					if (ak>2*a[i]) ak-=a[i],tmp++; //没到呢，还要再走，要让圆相交
				}
				if (ak) tmp+=2; //加了个if以防万一，具体是还没跳完呢，斜着跳要两步
			}
			ans=min(tmp,ans);  //取最小值
		}
		printf("%d\n",ans);
	}
}
```

### At last, thanks for watching~

---

## 作者：流绪 (赞：0)

### 贪心！

给一个序列，你每次可以走序列其中任意一个值的长度，问走 x 的长度最少需要几步。

首先我们要走最少的步数，那么每一步肯定要尽量长，所以我们贪心的每次都走最长的那一步，这样的话需要走 ceil(x/maxx) 步。但是这样一定最小吗？不，我们还需要特判一些情况。

⑴x 刚好是一个步长的倍数，这时候需要走 x/ai 步，我们需要在输入的时候判断这个情况，并将之与答案比较，取小的数。

⑵最大步长大于 x，那么我们取最大步长的时候需要走两步，这也不一定最小，同样的，我们让他与答案比较，取小的数。

把上面的几种情况的答案取最小值，就是题目所问的最小步数啦。

我的代码写的麻烦了，其实当其中一步步长和 x 相等时直接 return 的话，下面 maxx>x 的情况可以直接输出 2，因为比他小的答案只可能是 1，而如果是 1 的话，前面已经 return 掉了，不会运行到这里来。

下面是 AC 代码，细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
ll a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--)
	{
		int n,x;
		cin >> n >> x;
		ll maxx = -inf;
		ll flag = 1,ans=inf;
		for(int i=1;i<=n;i++)
		{
			cin >> a[i];
			maxx = max(maxx,a[i]);//取最大值
			if(a[i] == x)//特判步长等于x
			{
				cout << 1 <<endl;
				flag = 0;
			}
			if(a[i] % x==0)//特判x是步长倍数
				ans = min(ans,a[i]/x);
		}
		if(flag)
		{
			if(maxx > x)//步长比x大时
				ans = min((ll)2,ans);
			else
			{//普通情况,步长取最大值时
				ll p = ceil((x+0.0)/maxx);
				ans = min(p,ans);
			}
			cout << ans <<endl;
		}
	 } 
	return 0; 
}  
```


---

