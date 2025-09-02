# Frog Jumping

## 题目描述

一只青蛙最初位于数轴上的 $0$ 位置。青蛙有两个正整数 $a$ 和 $b$。从位置 $k$ 出发，青蛙可以跳到 $k+a$ 或 $k-b$。

设 $f(x)$ 表示如果青蛙从不跳到区间 $[0, x]$ 之外的整数，那么它能够到达的不同整数的个数。青蛙不需要一次性访问所有这些整数，也就是说，只要青蛙从 $0$ 出发能够到达某个整数，这个整数就会被计入。

给定一个整数 $m$，求 $\sum_{i=0}^{m} f(i)$，即从 $i=0$ 到 $i=m$ 的所有 $f(i)$ 之和。

## 说明/提示

在第一个样例中，我们需要计算 $f(0)+f(1)+\ldots+f(7)$。有 $f(0) = 1, f(1) = 1, f(2) = 1, f(3) = 1, f(4) = 1, f(5) = 3, f(6) = 3, f(7) = 8$。这些值的和为 $19$。

在第二个样例中，有 $f(i) = i+1$，因此我们要求 $\sum_{i=0}^{10^9} i+1$。

在第三个样例中，无论如何青蛙都无法跳跃。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 5 3
```

### 输出

```
19
```

## 样例 #2

### 输入

```
1000000000 1 2019
```

### 输出

```
500000001500000001
```

## 样例 #3

### 输入

```
100 100000 1
```

### 输出

```
101
```

## 样例 #4

### 输入

```
6 4 5
```

### 输出

```
10
```

# 题解

## 作者：ChthollyTree (赞：13)

应该可以想到一个O(n) 的做法 求出 $\sum_{i=1}^{n}f(i)$

就是bfs，每次加入一个点i是时候，判断之前  i-a 是否之前可以到达

如果可以，那么点i可以到达，并用点i bfs扩展一波即可

这样每个点最多被遍历1次，所以是O(n)的

------------

然后我们打表找规律,发现当 n > 2*max(a,b)的时候，f(n) = $\frac{n}{gcd(a,b)}+1$

然后在 $i <= 2*max(a,b)$ 时暴力做，否则用规律就行了

比赛的时候其实我找到规律了，但是忘记了小数据可以暴力做这种操作，一直推式子

直到最后10min我才做出来这题。我太菜了

不过总算让 [ChthollyTree](https://codeforces.com/profile/ChthollyTree) 上紫了

```

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define LL long long
#define INF (LL)(0x3f3f3f3f)*(LL)0x3f3f3f3f
#define MAXN 300005 

LL n,m;
LL a,b,x;
LL ans = 0;
LL an[MAXN];
bool f[MAXN];
queue<int>q;

LL gcd(LL x,LL y) {
    if(x%y != 0) return gcd(y,x%y);
    return y; 
} 

LL orz(LL x) {
    return x*(x+1)>>1;
}

LL sqz(LL x,LL mo)
{
    if(x % mo == 0) return x/mo;
    else return x/mo+1;
}

LL stO(LL n) {
    return orz((n+1)/x)*x + ((n+1)%x)*(sqz(n+1,x));
}


int bfs(int i)
{
    int ans = 0;
    f[0] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        ans ++;
        if(x+a <= i && !f[x+a]) {
            f[x+a] = 1;
            q.push(x+a);
        }
        if(x-b >= 0 && !f[x-b]) {
            f[x-b] = 1;
            q.push(x-b); 
        }
    }
    return ans;
}


signed main()
{
    cin >> n >> a >> b;

    q.push(0);
    an[0] = 1;
    f[0] = 1;
    bfs(0);
    for(int i = 1; i <= max(a,b)*2; i ++) {
        if(i-a >= 0 &&f[i-a]) {
            f[i] = 1;
            q.push(i);
            an[i] = an[i-1]+bfs(i);
        } else {
            an[i] = an[i-1];
        }
    }

    x = gcd(a,b); 
    if(a > b)
      swap(a,b);
        
        for(int i = 0; i < min(n+1,2*b); i ++) { 
            ans += an[i];
        }
        if(n >= 2*b)
            ans += stO(n) - stO(2*b-1);		
    }
    cout<<ans;
    return 0;
 } 

```

---

## 作者：λᴉʍ (赞：6)

写了个比较好理解的做法

显然法证明$x$较大（具体是$x\geq a+b$）时$f(x+a)=f(x)+\frac{a}{\gcd(a,b)}$

设$p_i$表示最小的$r$使得$0$只经过$[0,r]$能到达$i$（如果永远不能则为$\infty$）

可以用一个最短路求出$p_i$

那么$\sum_{i\leq x}f(i)=\sum_{j=0}^i\max(0,x-p_j+1)$

这样可以$O(a+b)$直接计算出前面的一段$f$（看代码）

$\geq a+b$的部分，可以用上面的式子算

对每一个$i\mod a$，$f$就是一段等差数列，直接套公式算即可。

注意最短路算$f$要算到$2a+b$

https://codeforces.com/contest/1146/submission/53115782

https://www.cnblogs.com/xzz_233/p/10744690.html

---

## 作者：傅思维666 (赞：5)


## 题解：

~~2019.10.28模拟赛T2 60分场~~

~~出题人@Winniechen的数据挺良心的（滑稽）~~

我很疑惑，为什么大佬们一开始都能想到找规律出正解。我一开始只能想到深搜，所以用一个差不多是$O(n^2)$的算法拿了$10^3$的分，假如数据是按上面说的：$10^9$，这个算法得跑31年...

先贴一份代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int maxn=1e5+10;
int n,a,b,cnt,ans;
bool v[maxn];
void dfs(int pos,int l)
{
    if(pos<0 || pos>l || v[pos])
        return;
    v[pos]=1;
    cnt++;
    dfs(pos+a,l);
    dfs(pos-b,l);
}
signed main()
{
    scanf("%lld%lld%lld",&n,&a,&b);
    for(int i=0;i<=n;i++)
    {
        cnt=0;
        memset(v,0,sizeof(v));
        dfs(0,i);
        ans+=cnt;
    }
    printf("%lld",ans);
    return 0;
}
```

这就是编程的魅力，一再优化，你的31年，人家的一秒，这就是差距。国家实力就是这么被提升起来的。

接下来介绍正解：

根据我们手推样例，不难发现，会有一个路径让我们返回到出发点，这样的话就会开始循环跳来跳去。（其实这是我深搜的时候发现的），所以我们会发现一个性质：在一个区间中，如果有一个点能到达，那么这个点一定是$\gcd(a,b)$的倍数。

证明其实也好证：

假设我们向右跳了$x$次，向左跳了$y$次。那么就会存在一个点$k$：
$$
ax+by=k
$$
显然$k$一定是$\gcd(a,b)$的倍数。

那我们回头来求这个函数$f(i)$，不难看出，当$a>i$的时候，总和就是$a$，因为根本就动弹不了。

所以当$n<a$的时候就输出$n+1$即可（加的那个$1$代表$f(0)$）。

否则我们一次性在答案上加$a$（一次性累加$f(0)-f(a-1)$）。

然后我们在$[a,i]$这个区间上寻找一个可以让路径回到出发点的点$k$，这样的话我们就相当于处理出了一个临界值，之后的东西可以用刚才我们推出的规律处理。这个处理过程其实是一个模拟的过程，先一直往右跳，再一直往左跳，什么时候正好跳回来了就标记上（这个省略了标记的步骤，因为直接拿$i$记录了），最后加上跳跃的次数。

很显然，这种一次枚举跳很多步的时间复杂度是很优秀的。

这个时候跳出循环，然后按照我们发现的规律：所有可被到达的点都是$\gcd(a,b)$的倍数。这样处理出其他的点到$n$的情况。进行累加答案，输出即可。

代码：

```cpp
#include<cstdio>
#define int long long
using namespace std;
int n,a,b,pos,i; 
int ans,tmp=1;
int gcd(int x,int y)
{
    return y?gcd(y,x%y):x; 
}
signed main()
{
    scanf("%lld%lld%lld",&n,&a,&b); 
    ans+=a;
    if(n<a) 
    {
        printf("%lld",n+1); 
        return 0; 
    }
    for(i=a;i;i++)
    {
        while(pos+a<=i)
        {
            tmp+=((i-pos)/a);
            pos+=((i-pos)/a)*a;
            tmp+=(pos/b); 
            pos%=b;
            if(!pos) 
                break;
        } 
        if(!pos) 
            break;
        ans+=tmp; 
        if(n==i) 
            break;
    }
    if(!pos)
    {
        int p=gcd(a,b); 
        int j=n-n%p;
        tmp=(int)(i+j)*(j/p-i/p+1)/2;
        tmp-=(int)(j+p-1-n)*(j/p);
        ans+=tmp+n-i+1;
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：_sys (赞：5)

首先我们定义

***

**$mini$为令$x$走到$x+1$需要的区间$[x,Right]$种最小的$Right$**

举个例子，$a=2,b=3$，我要从$0$走到$1$，那至少要在$[0,4]$内走$(Lift->Lift->Right)$才能走到，所以此时$mini=4$

如何求$mini$呢，我们求出$exgcd(a/\gcd(a,b),b/\gcd(a,b))$得到系数$x,y$。此时，我们让$x$变成正数。

之后，如果能往左走就往左走，否则往右走。

每次走到的位置取$\max$就是$mini$的值。

***

那么有如下引理：

***

引理1:

**对于位置$x>=mini$，可以在$[0,x]$内走到$x$**

证明：

根据$mini$的定义，$x \mod mini$可以在$[x \mod mini,(x \mod mini)+mini]$内走到

而$x < x \mod mini$，即$x \leq (x \mod mini)+mini$

所以$x$可以在$x \mod mini,x]$内走到，即在$[0,x]$内走到

***

引理2:

**$mini \leq a+b-1$**

证明:

如果$mini = a+b-1$满足定义即可。

根据$mini$的求法，我们会发现

+ 每次往左走时开始的位置必然$ < b$，我们设他为$x$

+ 此时一直往左走，走到的位置可以表示为$x+ay$，和$mini$的差值$ < a$，所以$\max ${ $x+ay$ } $ \geq b$，说明此时可以往右走，返回第一步。

+ 由此下来，永远不会超出$mini$

***
此时，我们已经证明了$mini$的性质与$mini$的大小范围。

于是考虑对于$> mini$的数$x$，如果$gcd(a,b)|x$，那么$x$就会给$f(x$~$m)$作贡献。

也就是说大于$mini$的数的贡献是**等差数列**

再考虑$[0,mini]$的数

我们定义$dis[x]$表示这个范围内的一个数$x$在$[0,dis[x]]$内就可以走到

有引理：


**$dis[x] \leq mini+x$**

证明:

不用再说了吧$...$

$x$可以在$[x,x+mini]$内走到。
***

那我们发现，我们让每一个位置$x$为一个节点，向$x+a$和$x-b$连边，$0$为源点，最小化走到每个结点的路径上节点编号的最大值

据某$dalao$说可以$dijkstra$

但是我当时直接用了$SPFA$

~~根据提交结果可知在这个图中不会被卡~~

代码如下:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=400005;
long long m,a,b,c,x,y,now,mini,ans,dis[Maxn];
bool vis[Maxn];
long long gcd(long long x,long long y)
{
	return x==0?y:gcd(y%x,x);
}
void exgcd(long long a,long long b,long long &X,long long &Y)
{
    if(b==0)
        X=1,Y=0;
    else
    {
        exgcd(b,a%b,X,Y);
        long long tmp=X;
        X=Y;
        Y=tmp-a/b*Y;
    }
}
void get_mini(void)
{
	while(x<=0) x+=b/c,y-=a/c;
	y*=-1;
	while(x+y)
	{
		if(now>=b&&y) now-=b,y--;
		else now+=a,x--;
		mini=max(mini,now);
	}
}
void SPFA(void)
{
	queue <int> Qu;
	Qu.push(0);
	memset(dis,0x3f,sizeof(long long[2*mini+1]));
	dis[0]=0;
	while(!Qu.empty())
	{
		int u=Qu.front();
		vis[u]=false;
		Qu.pop();
		if(u+a<=2*mini&&max(u+a,dis[u])<dis[u+a])
		{
			dis[u+a]=max(u+a,dis[u]);
			if(!vis[u+a])
				Qu.push(u+a),vis[u+a]=true;
		}
		if(u-b>=0&&dis[u]<dis[u-b])
		{
			dis[u-b]=dis[u];
			if(!vis[u-b])
				Qu.push(u-b),vis[u-b]=true;
		}
	}
}
int main()
{
	scanf("%lld%lld%lld",&m,&a,&b);
	c=gcd(a,b);
	exgcd(a/c,b/c,x,y);
	get_mini();
	SPFA();
	for(int i=0;i<=mini;i++)
		ans+=max(0LL,m-dis[i]+1);
	if(m<=mini)
	{
		printf("%lld",ans);
		return 0;
	}
	long long Begin=mini+c-mini%c,End=(m/c)*c,Element=(End-Begin)/c+1;
	ans+=(m+1)*Element-(Begin+End)*Element/2;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：xhhhh36 (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1146D)
# 暴力
从小到大使用 dfs，显然 $[0,i]$ 一定不比 $[0,i-1]$ 扩展的少。又考虑到每个点 $i$ 一定仅被 $i-a$ 扩展，那么当枚举到 $i$ 时，尝试使用 $i-a$ 扩展 $i$ 并从此点进行 dfs 即可，保证每个点只扩展一次，复杂度 $O(n)$。
# 正解
打表可以发现，当 $i>a+b-1$ 时，有 $f(i)=\lfloor\frac{i}{\gcd(a,b)}\rfloor+1$，剩余的部分按照暴力求解即可。
# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int m,a,b,i,ans,lst;
bool v[1000005];
void dfs(int x)
{
	if (v[x]) return;
	lst++;
	v[x]=1;
	if (x+a<=i) dfs(x+a);
	if (x-b>=0) dfs(x-b);
}
signed main()
{
	cin>>m>>a>>b;
	int k=a+b-1;
	i=0;
	dfs(0);
	ans+=lst;
	for (i=1;i<=min(k,m);i++)
	{
		if (i-a>=0&&v[i-a])
		{
			dfs(i);
		}
		ans+=lst;
	}
	if (m<k)
	{
		cout<<ans<<endl;
		return 0;
	}
	int c=__gcd(a,b);
	for (i=k+1;i<=m;i++)
	{
		if (i%c==0) break;
		ans+=i/c+1;
	}
	int d=m/c*c-1;
	ans+=(d-i+1)+((m/c-1)+(i/c))*(m/c-1-(i/c)+1)/2*c;
	for (i=d+1;i<=m;i++)
	{
		ans+=i/c+1;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18184947)。

首先根据裴蜀定理，能走到的点 $x$ 肯定满足 $\gcd(a, b) | x$。  
于是令 $g = \gcd(a, b)$，可以考虑求解 $\lfloor\frac{m}{g}\rfloor, \frac{a}{g}, \frac{b}{g}$，最后记得去判一下 $[g\lfloor\frac{m}{g}\rfloor, m]$ 这个区间，因为只有这个区间是不满（区间长度可能 $< g$）的，其他的直接 $\times g$ 即可。  
接下来的求解都以新的规模来做。

考虑到 $+ a$ 这个操作，这启发可以类似同余最短路的想法，记录到 $\bmod a = p(0\le p < a)$ 的点，要走到这样的点至少答案都得是多少，记为 $mx_p$。  
然后 $mx_p$ 是可以递推的，考虑从 $-ib\bmod p$ 推到 $-(i + 1)b\bmod p$，那么这一步推过去肯定就需要 $-b$ 了，考虑在维护一下当 $-ib\bmod p$ 时此时推到的数 $x$ 的值，那么肯定需要 $x\ge b$，所以先加 $a$ 加到 $x\ge b$，再 $-b$ 即可，其中还没 $-b$ 时 $x$ 的最大值就是可能的最大值，与 $mx_{-ib\bmod p}$ 取 $\max$ 后即是 $mx_{-(i + 1)b\bmod p}$。  
即初始化 $x = 0, mx_0 = 0, i = 0$，接下来若 $x < b$，则一直 $+ a$ 直到 $x\ge b$，然后 $mx_{-(i + 1)b\bmod p} \leftarrow \max\{mx_{-ib\bmod p}, x\}$，最后 $x\leftarrow x - b$。  
当然能够证明其实 $-ib\bmod p = x$，这因为如果不成立显然有 $x\ge a$，那么到了上一步肯定再 $x\ge b + a$，但是上一步若 $x \ge b$ 就停止了操作，肯定 $x\in [b, b + a)$，所以不成立。

那么要表示出 $i$ 需要的最小值就是 $\max\{i, mx_{i\bmod a}\}$。  
通过递推过程能够发现 $mx_p\le a + b$，所以当 $i\ge a + b$ 时肯定需要的最小值就是 $i$。

所以可以考虑暴力处理出 $x\in [0, a + b]$ 范围内的 $f(x)$，前缀和即可。  
对于 $x\in (a + b, m]$ 肯定有 $f(x) = x + 1$，用一个等差数列求和即可。

时间复杂度 $\mathcal{O}(a + b)$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
const int maxV = 2e5 + 10;
int mxp[maxV];
int cnt[maxV];
int main() {
   int M, A, B;
   scanf("%d%d%d", &M, &A, &B);
   int g = std::__gcd(A, B);
   int m = M / g, a = A / g, b = B / g;
   for (int i = 0, p = 0, mx = 0; i < a; i++)
      mxp[p] = mx, p < b && (p += (b - p + a - 1) / a * a), mx = std::max(mx, p), p -= b;
   int n = std::min(m, a + b);
   for (int i = 0; i <= n; i++)
      cnt[std::max(i, mxp[i % a])]++;
   for (int i = 1; i <= n; i++)
      cnt[i] += cnt[i - 1];
   ll ans = 0;
   for (int i = 0; i <= n; i++)
      ans += 1ll * cnt[i] * g;
   if (m == n)
      ans -= 1ll * cnt[m] * ((m + 1) * g - 1 - M);
   else {
      int l = n + 1, r = m - 1;
      ans += 1ll * (l + r) * (r - l + 1) / 2ll * g;
      ans += 1ll * m * (M - m * g + 1);
      ans += M + 1 - (n + 1) * g;
   }
   printf("%lld\n", ans);
   return 0;
}
```

---

