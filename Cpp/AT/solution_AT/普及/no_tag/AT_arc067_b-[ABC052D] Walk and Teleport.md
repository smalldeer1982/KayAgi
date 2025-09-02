# [ABC052D] Walk and Teleport

## 题目描述

在东西方向延伸的直线上，有N个城市。城市坐标按从西到东递增。

你现在在某个城市里，想去其他所有的城市。移动的方法有以下两种。

一，在直线上按东西方向平移，每移动一个单位距离疲劳值加A

二，直接瞬移到某个坐标，并且疲劳值加B

请使用以上两种方式直到去完其他所有的城市，并求出最小的疲劳值。

## 说明/提示

2<=N<=1e5

1<=Xi,A,B<=1e9且X(i)<X(i+1)

## 样例 #1

### 输入

```
4 2 5
1 2 5 7```

### 输出

```
11```

## 样例 #2

### 输入

```
7 1 100
40 43 45 105 108 115 124```

### 输出

```
84```

## 样例 #3

### 输入

```
7 1 2
24 35 40 68 72 99 103```

### 输出

```
12```

# 题解

## 作者：Krimson (赞：6)

此题其实可以用斜率优化做~~脑子比较笨,没去想贪心~~  
设$f[i]$表示到达前i个点所需要的最小花费  
那么首先可以得到$f[i]$可以从$f[i-1]$得到，也就是说$f[i]=min(f[i],f[i-1]+A(dis[i]-dis[i-1]))$  
再考虑从$i-1$之前的点$j$瞬移过来之后再往回走去遍历那些$[j+1,i-1]$之间的点,可以得到方程  
$$
f[i]=min(f[i],f[j]+(dis[i]-dis[j+1])*2A+B)
$$  
然后假设存在一个$f[x]$比$f[j]$转移过来更优  
也就是  
$$
f[x]-f[j]-Adis[x+1]+Adis[j+1]<0\\
\frac{f[x]-f[j]}{dis[x+1]-dis[j+1]}<A
$$  
轻松得到斜率是$\frac{f[x]}{dis[x+1]}$,且$dis[x+1]$与$A$均含有单调性~~A根本就是定值吧！~~  
最后用单调队列维护一下凸包就好了  
以下是代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
int n;
const int MAXN=1e5+7;
ll dis[MAXN];
ll f[MAXN];
ll A,B;
int q[MAXN],l,r;
#define fz(i,j) (f[i]-f[j])
#define fm(i,j) (dis[i+1]-dis[j+1])
int main(){
    n=read(),A=read(),B=read();
    for(ri i=1;i<=n;++i) dis[i]=read();
    q[r++]=1;
    for(ri i=2;i<=n;++i){
        f[i]=f[i-1]+(dis[i]-dis[i-1])*A;
        while(l+1<r&&A*fm(q[l+1],q[l])>=fz(q[l+1],q[l]))++l;
        int x=q[l];
        f[i]=min(f[i],f[x]+B+(dis[i]-dis[x+1])*A*2);
        while(l+1<r&&fz(i,q[r-1])*fm(q[r-1],q[r-2])<=fm(i,q[r-1])*fz(q[r-1],q[r-2])) --r;
        q[r++]=i;
    }
    print(f[n]);
    return 0;
}
```


------------
其实回到刚才的斜率那里，已经证明贪心的正确性了  
把柿子再化一下,就相当于只要从从j到x走过去的花费大于B,那么直接瞬移一定更优

---

## 作者：封禁用户 (赞：4)

这是一道很水的绿题，简单地模拟即可求出答案。  
题目传送>>[AT2287](https://www.luogu.com.cn/problem/AT2287)
### 题意简述：  
一条直线上有$n$个城市，第$i$个城市的坐标为$x_i$，使用以下两种方式直到去完其他所有的城市，求最小疲劳值。  
1. 按东西方向平移，每移动一个单位距离疲劳值加$a$；  
2. 直接瞬移到某个坐标，疲劳值加$b$；   
### 题目分析：  
此题直接模拟即可，以第一种方式移动两城市间的距离为$x[i+1]-x[i]$，疲劳值为$a*(x[i+1]-x[i]))$,以第二种方式移动即瞬移，每两个城市间疲劳值为$b$，每次移动时进行对各种方式所需的疲劳值比较，采用疲劳值最小的方式移动，然后每次移动所需的疲劳值累加即可得到使用两种方式去完其他所有的城市的最小疲劳值。  
#### 额外需要注意的是题目所给的数据范围，需要使用long long！  
### Code:  
```cpp
#include<iostream>
using namespace std;
typedef long long ll;   \\类型定义long long 为ll,避免频繁使用long long时累手
ll x[200001];   \\开数组存每个城市的坐标 
int main()
{
	ios::sync_with_stdio(0);   \\关同步流，加速cin输入和cout输出 
	ll n,a,b,sum=0;   \\定义城市数，方式一、二的疲劳值，总疲劳值 
	cin>>n>>a>>b;
	for(ll i=1;i<=n;i++)
	{
		cin>>x[i];
	}
	for(ll i=1;i<n;i++)   \\注意此处i是<n
	{
		sum+=min(b,a*(x[i+1]-x[i]));   \\使用min函数求每次移动的最小疲劳值并进行累加 
	}
	cout<<sum;
	return 0;   \\结束整个程序 
}
```
### 结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/kcxoc7ym.png)  
企鹅的题解到此结束，祝各位OIers进步++~

---

## 作者：Thomas_Cat (赞：1)

题目很简单，这里著需要做出模拟就可以了，这里注意使用 `long long`。

~~真搞不懂为什么是绿而不是红~~

由于该题不是一个图论而是一个转化成贪心的图论，因此只需要在每一次加入新值的时候比较是使用 $a$ 方案还是 $b$ 方案好，这里注意 $a$ 方案的计算方式为 $a \times (x_{i+1}-x_i)$，直接列出代码即可。

注：计算公式为：$\min \{a \times (x_{i+1}-x_i),b\}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,a,b,sum=0;
    cin>>n>>a>>b;
    long long x[1000001];
    for(int i=1;i<=n;i++)
   	    cin>>x[i];
    for(int i=2;i<=n;i++)
   	    sum+=min(b,a*(x[i]-x[i-1]));
    cout<<sum;
	return 0;
}
```

---

## 作者：zfn07 (赞：1)

此题评分有点高呀(~~应该是橙题才对~~)
但是我竟然错了一次，想知道错在哪吗？
继续看吧。

26分代码：
首先我们知道只需模拟即可，于是代码出炉了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,a,b,x[10005],i,ans=0;
	cin>>n>>a>>b;
	for(i=1;i<=n;i++)
		cin>>x[i]; 
	for(i=1;i<n;i++)
		ans+=min(a*(x[i+1]-x[i]),b); 
	cout<<ans<<endl;
	return 0; 
}
```
知道错在哪了吗？我的x数组下标开小了！！！qwq

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,a,b,x[100005],i,ans=0;//必开long long(x[i]<=1e9,n<=1e5,ans早爆int了)
	cin>>n>>a>>b;
	for(i=1;i<=n;i++)
		cin>>x[i]; 
	for(i=1;i<n;i++)
		ans+=min(a*(x[i+1]-x[i]),b); //看是瞬移的疲劳值少还是走路的疲劳值少
	cout<<ans<<endl;//输出
	return 0; 
}
```


---

## 作者：rui_er (赞：1)

~~真心不明白为什么这题是绿题，只是一个模拟。~~

# 读懂题意是关键

我第一次提交的时候对题面理解有误，加了一句```sort(x, x+n);```，结果WA了很多测试点。其实这里是需要按照顺序到达每个地点的QAQ。

# 模拟方法

对于每一个地点，判断两种方案中耗费疲劳值最少的方案，详见代码。

```cpp
#include <iostream>
using namespace std;

#define ll long long

int main()
{
    ll n, a, b;
    cin>>n>>a>>b;
    ll x[100001];
    for(ll i=1;i<=n;i++) cin>>x[i];
    ll sum = 0;
    for(ll i=1;i<n;i++)
    {
        ll l = x[i+1] - x[i];
        sum += min(b, a*l);
    }
    cout<<sum<<endl;
	return 0;
}
```

---

## 作者：·糯· (赞：0)

## 题目分析
此题只用在循环中每次做判断即可，如果此城市到下一城市一个单位一个单位走更省，就加上此代价，如果瞬移更省，就加上瞬移的代价，最终输出总代价即可。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x[100010],a,b,sum;
int main(){
	cin>>n;
	cin>>a>>b;
	for(int i=1;i<=n;i++)
		cin>>x[i];
	for(int i=1;i<n;i++){
		if(a*(x[i+1]-x[i])>=b)
			sum+=b;//瞬移更省
		else
			sum+=a*(x[i+1]-x[i]);//一步一步走更省
	}
	cout<<sum<<endl;
	return 0;
}

```


---

## 作者：Eason_AC (赞：0)

## Content
一条直线上有 $n$ 个城市，第 $i$ 个城市的坐标为 $x_i$。你在某一个城市内，每一次你可以按两种方式之一进行移动：

- 左右移动，每移动一个单位疲劳值增加 $a$。
- 瞬移到某一个坐标，疲劳值增加 $b$。

求出去过所有的城市的最小疲劳值。

**数据范围：$2\leqslant n\leqslant 10^5,1\leqslant x_i,a,b\leqslant 10^9,x_i\leqslant x_{i+1}$。**
## Solution
简单的模拟。

我们可以想到，如果你在某一个城市内但没有具体指定哪一个城市，那么最优的方案明显是选择最左边或者最右边的城市，然后逐次前往每个城市。这里以选择最左边的城市为例。

再想，我们如果直接在第 $i$ 个城市和第 $i+1$ 个城市之间左右移动，需要消耗的疲劳值肯定是 $a\times(x_{i+1}-x_i)$，瞬移的话疲劳值是 $b$，那么要疲劳值最小的话肯定取其最小值。所以，答案就是 $\sum\limits_{i=1}^{n-1}\max(a\times(x_{i+1}-x_i),b)$。

这篇在 NOIP2020 之前写下的最后一篇文章，也许是我的绝笔了吧。
## Code
```cpp
int n, a, pl[100007];
long long ans, b;

int main() {
	n = Rint, a = Rint, b = Rll;
	F(i, 1, n) pl[i] = Rint;
	F(i, 1, n - 1) {
		int dis = pl[i + 1] - pl[i];
		ans += min(1ll * dis * a, b);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：atarashiTLE (赞：0)

一道水绿。

### 【题意简述】

给出 $n,a,b$ 与需要到达的$n$座城市，求出最小花费。

有$2$种移动方式:

1. 单步移动。每次移动$1$个城市的距离，花费为 $a$。
2. 瞬移。直接移动到任意一个城市，花费为 $b$。

#### 【一些坑点】

1. 不开`long long`见祖宗。
2. 城市序列不需要排序。
3. 赋初值。

### 【做法】

贪心决定每一次的走法（要么是走  $|X_aX_{a+1}|$  次单步,要么是走一次瞬移）。

code:

```cpp
#include <iostream>
using namespace std;
int main()
{
    long long n, a, b, arr[100010];
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    long long ans = 0;
    for (int i = 1; i < n; i++)
        ans += min(a * abs(arr[i] - arr[i - 1]), b);
    cout << ans << endl;
    return 0;
}
```

---

