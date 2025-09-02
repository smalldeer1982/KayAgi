# [YDOI R1] Running

## 题目背景

小 Z 要去跑步，他想开学后拉爆他的同学。

## 题目描述



小 Z 在一条公路上跑步，公路上有 $n$ 个超市，第 $i$ 个超市的位置为 $a_i$。当小 Z 经过一个超市的时间为奇数时，他就会去逛超市，从而被同学拉爆。

小 Z 最开始位于位置为 $0$ 的点。他会在每个单位时间向右跑 $v$ 个单位长度。

请求出：能够使小 Z 经过 $n$ 个超市中每一个超市时，都不去逛超市的 $v$ 的最大值。


规定 $v$ 必须是正整数，且小 Z 到达任意一个超市时，花费的时间必须为整数，换言之，你需要保证小 Z 到达任意一个超市的时间都是偶数。注意时间初始为 $0$。


## 说明/提示

### 【样例解释】
对于样例 $1$，可以证明不存在符合要求的速度。

对于样例 $2$，当 $v=5$ 时，到达第 $1\sim5$ 个超市的时间分别为 $2$，$4$，$6$，$8$，$10$，均为偶数，符合题目要求。可以证明不存在更快的符合要求的速度。


**本题采用捆绑测试**。

|子任务编号|$n\le$|$a_i\le$|分值|
|:--:|:--:|:--:|:--:|
|$1$|$1$|$3\times10^{18}$|$10$|
|$2$|$25$|保证 $a_1\le 2\times 10^6$|$10$|
|$3$|$10^4$|保证 $a_1\le 2\times 10^6$|$20$|
|$4$|$2\times10^6$|$3\times10^{18}$|$60$|

对于 $100\%$ 的数据，$1 \le n \le 2\times10^6$，$1\le a_1<a_2<\dots<a_{n-1}<a_n\le3\times10^{18}$。保证所有输入都是正整数。

## 样例 #1

### 输入

```
2
1 
2```

### 输出

```
-1```

## 样例 #2

### 输入

```
5
10 
20 
30
40
50```

### 输出

```
5```

# 题解

## 作者：System_Error_ (赞：12)

## subtask 1：

超市只有 $1$ 个，所以找到一个速度使得到达这个超市的时间为 $2$ 秒即是最大速度，即最大速度为 $\frac{a_1}{2}$，判断速度是否为整数，是则输出速度，否则无解。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a;
int n;
int main() {
	cin>>n>>a;
	if(a%2==0) cout<<a/2;
	else cout<<-1;
	return 0;
}
```

## subtask 2：

显而易见，$v$ 一定小于等于 $a_1$，而 $a_1 \le 2\times10^6$，所以枚举 $v$ 即可，判断到达超市的时间是不是偶数，总时间复杂度 $O(a_1n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[55];
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=a[1]; i>=1; i--) {
		bool f=true;
		for(int j=1; j<=n; j++) 
			if(a[j]%i||a[j]/i%2) f=false;
		if(f) {
			cout<<i;
			return 0;
		} 
	}
	cout<<-1;
	return 0;
}
```

## subtask 3：

在枚举 $v$ 的过程中，如果 $v \nmid a_1$，那么到达第一个超市的时间就不是整数，所以我们就可以只枚举 $a_1$ 的因数，这样就保证了到达第一个超市的时间为整数，总时间复杂度 $O(n\tau(a_1))$，$\tau(a_1)$ 是指 $a_1$ 的正因子个数。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[10005],ans=-1;
bool check(int x) {
	for(int i=1; i<=n; i++)
		if(a[i]%x||a[i]/x%2) return false;
	return true;
}
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=sqrt(a[1]); i>=1; i--) {
		if(a[1]%i==0) {
			if(check(i)) ans=max(ans,i);
			if(check(a[1]/i)) ans=max(ans,a[1]/i);
		}
	}
	cout<<ans;
	return 0;
}
```

## subtask 4：

我们先不管必须在偶数时间经过这个条件，要求出一个 $v$ 使得每次到达某个超市时时间是整数，就要保证 $v \mid a_i$，所以 $v$ 就是所有 $a_i$ 的公因数，最大的 $v$ 就是所有 $a_i$ 的最大公因数。

求出 $v$ 后可以证明至少有一个超市到达时间是奇数，原因是如果每个超市到达时间都是偶数，那么所有的 $a_i$ 除以 $v$ 后还至少有 $2$ 这个公因子，不符合 $v$ 是最大公因数的定义。

接着再看偶数时间经过这个条件，把 $v$ 除以 $2$ 后到达每个超市的时间会多一倍，所以这样就保证了到达时间为偶数，注意：如果 $2 \nmid v$，则 $v$ 除以 $2$ 后不是整数，不符合题意，输出无解，时间复杂度为 $O(n \log V)$。

~~相信聪明的你一定看得懂简单的代码~~。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
int n,a[N];
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>a[i];
	int v=a[1];
	for(int i=2; i<=n; i++)
		v=__gcd(v,a[i]);
	if(v%2==1) cout<<-1;
	else cout<<v/2;
	return 0;
}
```

---

## 作者：Dream_poetry (赞：8)

### 思路：
不难看出，若要使得到达每个点时都为整数，必须要使得 $v$ 是所有 $A_i$ 的最大公因数。

同时，因为要求到达每个点时都为偶数，就要将 $v$ 除以 $2$。

当 $v$ 除以 $2$ 后，如果还是一个整数，输出即可。否则输出 $-1$。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[5000005];
int w;

signed main(){
	cin>>n;
	cin>>a[1];
	w=a[1];
	for (int i=2;i<=n;i++){
		cin>>a[i];
		w=__gcd(w,a[i]);
	}
	if (w%2==1) cout<<-1;
	else cout<<w/2;
	return 0;
}
```



---

## 作者：dinghongsen (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/P10183)

### 解题思路

先求出所有超市位置的最大公约数，则这个最大公约数的一半就是小 Z 的速度。

因为奇数的一半不可能为整数，所以当这个最大公约数为奇数时，无解，反之输出这个最大公约数的一半。

### code
```
# include <bits/stdc++.h>
using namespace std;
long long a[2000010];
int main() {
	int n;
	scanf("%d", &n);
	scanf("%lld",  &a[1]);
	long long v = a[1];
	for (int i = 2; i <= n; i++) {
		scanf("%lld", &a[i]);
		v = __gcd(v, a[i]);
	}
	printf("%lld", (v % 2 == 0) ? v / 2 : -1);
	return 0;
}
```

---

## 作者：水星湖 (赞：3)

出题人口胡一下。

若保证到达任意一个超市时间为整数，需要满足速度是所有超市位置的公约数。然后考虑如何使到达每个超市时间为偶数。容易发现，当速度是所有超市位置的最大公约数时，必定到达其中一个或多个超市的时间是奇数，否则所有超市的位置除以最大公约数必然都有公因子 $2$。因此，要使时间是偶数，在所有数的最大公约数上除以 $2$ 即可，如果最大公约数是奇数的话就输出 $-1$。

---

## 作者：1qaz234Q (赞：3)

### 题目分析
因为要使小 Z 不去逛超市，所以到达超市的时间为偶数。如果到达超市的时间为奇数，那么就无解，输出 `-1`。如果到达超市的时间为偶数，那么答案就是所有 $a_i$ 除以 $2$ 的最大公因数。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int n;
    int c;
    cin>>n;
    cin>>c;//输入到达第一个超市的时间
    if(c%2==1){//无解
        cout<<-1;
        exit(0);//结束程序
    }
    int ans=c/2;
    for(int i=2;i<=n;i++){
        int a;
        cin>>a;
        if(a%2==1){//无解
            cout<<-1;
            exit(0);
        }
        int b=a/2;
        ans=__gcd(ans,b);//求出最大公因数
    }
    cout<<ans;//输出答案
}
```

---

## 作者：zhjx2023 (赞：2)

### 思路
题意:小 $ Z $ 跑公路，如果路上经过超市，且时间为奇数时，就会去逛。让你求出一个速度，使小 $ Z $ 不去逛超市。

1. 看了题目脑海中第一印象就是最大公约数。
2. 要使小 $ Z $ 不去逛超市，那就是使所有数的最大公约数为整数。
3. 求出了最大公约数，问题就来了，他会在奇数的时间单位经过超市。
4. 若结果为偶数，那么就要除以一个 $ 2 $。
5. 若结果为奇数，就输出 $ -1 $ 就好了。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
//#define cin std:cin
//#define cout std:cout
using namespace std;
const ll N = 1e7 + 10, MOD = 1e9 + 7;
ll n, a;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> a;
	ll g = a;
	for (ll i = 1; i < n; i++) {
		cin >> a;
		g =__gcd(a,g);
	}
	cout<<(g%2==0?g/2:-1);
	return 0;
}
```
完结撒花

---

## 作者：sLMxf (赞：2)

### subtask 1
一个超市，最大速度就是 $\dfrac{a_i}{2}$。当然，如果 $2∤a_i$，输出 `-1` 即可。
### subtask 2
枚举速度，输出符合要求的最大答案即可。时间复杂度 $O(\text A\times n)$，其中 $\text A$ 表示 $a_i$ 的值域。
### subtask 3
方法二中，有许多速度是明显无效的，因为他们可能连到达 $a_1$ 的时间都不是。所以速度枚举变为枚举 $a_1$ 的因数，时间复杂度 $O(d(A)\times n)\approx O(n\sqrt{\text A})$，其中 $d(n)$ 表示因数个数。
### subtask 4
要保证到达超市的时间为整数，且最大，可以推出 $v=\gcd\{a_1,a_2,a_3,\cdots,a_n\}$。

如果还要保证时间为偶数，则 $v$ 要再乘上 $\dfrac{1}{2}$。当然，如果 $2∤v$，输出 `-1` 即可。

时间复杂度 $O(n\log \text A)$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int n,x,ans;
	cin>>n>>ans;n--;
	while(n--) cin>>x,ans=__gcd(ans,x);
	if(ans%2) cout<<-1;
	else cout<<ans/2;
	return 0;
}

```

---

## 作者：Vct14 (赞：2)

设小 Z 到达第 $i$ 个超市的时间为 $t_i$，那么根据 $Vt=S$ 可知 $t_i=\dfrac{a_i}{v}$。

因为 $t_i$ 必须为整数，所以 $v$ 一定整除 $a_i$，因此 $v$ 一定是所有 $a_i$ 的最大公因数 $g$ 的因数。

为了使 $t_i$ 均为偶数，即含有公因数 $2$，所以 $a_i$ 一定为偶数。此时 $g$ 为偶数。因此若 $g$ 为奇数，则无解。

如果 $v=g$，那么所有 $t_i$ 一定是互质的（注意不是两两互质）。那么一定存在 $t_i$ 不是偶数，否则 $t_i$ 有公因数 $2$，不会互质。因此 $v<g$。此时 $v_{\max}=\dfrac{g}{2}$。下证 $v=\dfrac{g}{2}$ 符合题意。

$g$ 为偶数时，使 $v=\dfrac{g}{2}$，则 $t_i=\dfrac{a_i}{v}=\dfrac{a_i}{\frac{g}{2}}=2\times\dfrac{a_i}{g}$ 为偶数，满足题意。证毕。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;int a,gcd;
	cin>>a;gcd=a;
	for(int i=2; i<=n; i++){
		cin>>a;
		gcd=__gcd(gcd,a);
	}
	if(gcd%2) cout<<-1;
	else cout<<gcd/2;
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：2)

~~公路跑拉爆全班。~~

时间距离公式：

$$s=vt$$

转换一下：

$$t=\frac s v$$

我们可以把每个商店到起点的距离看成一个 $s_i$，这样就可以通过一个固定的速度 $v$ 计算到每个商店所用的时间 $t_i$。

到每个商店的时间都是整数，所以对于每个 $1\le i\le n$，$s_i$ 是速度 $v$ 的倍数。换句话说，$v$ 是所有 $s_i$ 的公因数。

速度尽可能大。所以 $v$ 是所有 $s_i$ 的最大公因数。

但是在这种情况下，所有 $s_i$ 与 $v$ 的商肯定不能都再包含一个公因数 $2$，否则要使得 $v$ 为它们的**最大**公因数，$v$ 实际应该为 $2v$。也就是说，此时的 $t_i$ 肯定不全为偶数，不符合要求。

再看一眼公式，若等式右边的分母 $v$ 缩小的原来的 $\frac 1 2$，则分数值扩大 $2$ 倍，等式左边同样 $\times2$。

$$2t=\frac s {\frac v 2}$$

现在时间 $t_i$ 肯定是偶数了（因数 $2$ 都摆外边了）。

综上，算出到每个商店的距离的最大公因数后，除以 $2$，所得的商就是答案。如果除法后变成了小数，就说明无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[2000005],sum=0;
long long gcd(long long a,long long b){
    if(b==0) return a;
    else return gcd(b,a%b);
}
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) sum=gcd(min(sum,a[i]),max(sum,a[i]));
    if(sum%2==0) printf("%lld",sum>>1);//通过余数判断有无解
    else printf("-1");
    return 0;
}
```

---

## 作者：xxboyxx (赞：1)

### 思路

如果某些超市的距离是奇数，那么为了保证整除，所以速度和时间都应该是奇数，显然不符合题意，直接判定无解。对于剩下的情况，为了保证时间是偶数，可以提前将所有的距离除以 $2$。要求速度最大且保证整除，所以求得这些数的最大公因数。

### 代码

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,ans;
int a[2000005];
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		if (a[i]%2==1)//无解 
		{
			cout<<-1;
			return 0;
		}
		a[i]/=2;//先除以2 
	}
	ans=a[1];
	for (int i=2;i<=n;i++)
		ans=__gcd(ans,a[i]);//求最大公因数 
	cout<<ans;
	return 0;
}
```


---

## 作者：Link_Cut_Y (赞：1)

不妨设相邻两个超市之间的距离为 $d_1, d_2 \cdots d_{n - 1}$，题意即为：

> 求最大的 $v$，使得 $\forall i < n$，都存在正整数 $k$，使得 $d_i = 2kv$。

首先我们要保证所有的 $d$ 为偶数，否则上面的条件一定不成立。

若 $d$ 均为偶数，将 $2$ 除掉，题意转化为：

> 求最大的 $v$，使得 $\forall i < n$，都存在正整数 $k$，使得 $\dfrac{d_i}{2} = kv$。

只需要求出 $\dfrac{d_i}{2}$ 的最大公约数即可。复杂度 $O(n \log V)$。

```cpp
int a[N], d[N], n;
int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}
signed main() {
	read(n);
	rep(i, 1, n) read(a[i]);
	sort(a + 1, a + n + 1); bool flg = 0;
	rep(i, 1, n) d[i] = a[i] - a[i - 1];
	rep(i, 1, n) if (d[i] & 1) {
		flg = 1; break;
	} if (flg) { puts("-1"); return 0; }
	rep(i, 1, n) d[i] /= 2ll;
	int D = d[1]; rep(i, 2, n) D = gcd(D, d[i]);
	write('\n', D);
}
```

---

## 作者：modfish_ (赞：1)

## 思路
显然，当存在某个 $a_i$ 为奇数时无解。因为此时只要 $v\mid a_i$，都会有 $2\nmid\frac{a_i}{v}$。

而对于 $a_i$ 为偶数，我们希望 $v$ 质因子中 $2$ 的数量要小于 $a_i$ 质因子中 $2$ 的数量。可转化为 $v\mid\frac{a_i}{2}$。

所以，$v$ 最大值即为：

$$\gcd(\frac{a_1}{2},\frac{a_2}{2},\dots,\frac{a_n}{2})$$

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll gcd(ll a, ll b){
	if(a < b) swap(a, b);
	if(!b) return a;
	return gcd(b, a % b);
}

int main(){
	int n;
	scanf("%d", &n);
	ll res = 0;
	for(int i = 1; i <= n; i ++){
		ll a;
		scanf("%lld", &a);
		if(a & 1){
			printf("-1");
			return 0;
		}
		res = gcd(res, a / 2);
	}
	printf("%lld", res);
	return 0;
}
```


---

## 作者：hhhppp (赞：1)

## 简述题意

给出一条数轴上的 $n$ 个坐标，你需要确定一个速度 $v$，使得经过每个坐标时花费的时间正好为偶数，输出这个速度的最大值。

## 思路

题目说要确保每过一个坐标花费的时间正好为**整数**，那么每一个坐标必定是这个速度 $v$ 的倍数，因此我们很容易想到**最大公约数**。所以我们先求出这些数的最大公约数。

其次，又要确保每过一个坐标花费的时间正好为**偶数**，那么如果这个最大公约数为奇数，则无解。否则输出这个最大公约数除以二。

为何要除以二呢？我们都知道要使一个数决定为偶数，需要将这个数乘二，在公式 $t=\frac{s}{v}$ 中，如果时间 $t$ 乘二，那么要使等式成立，可以将 $v$ 除以二，因此，答案为最大公约数除以二。

最后记得看数据范围~。

## _那么，理论存在，实践开始。_ 


## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
int n,a[3000000],ans=-1,t,k,g;
int gcd(int a,int b){return a%b==0?b:gcd(b,a%b);}//求最大公约数 
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
    }
    return x*f;
}
//题目要求用较快的输入方式，那就加个快读吧 
signed main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	g=a[1];
	for(int i=2;i<=n;i++) g=gcd(g,a[i]);
	if(g%2==0) printf("%lld\n",g/2);
	else printf("-1\n");
	return 0;
}
```

---

## 作者：luxiaomao (赞：1)

赛时来晚了，不然说不定可以拿下本题首杀呢。（~~你就吹吧~~）

## [P10183](https://www.luogu.com.cn/problem/P10183) 数学的简单应用

首先看题意。

给出一条直线上的 $n$ 个坐标，你需要给出一个速度 $v$，使得经过每个坐标时都刚好花费偶数单位的时间，最大化这个速度。

我们先简化一下题意：不要求偶数单位的时间，只要求整数单位的时间。

那么，如果经过一个坐标 $a_i$ 时时间为整数，那么 $a_i$ 必然是 $v$ 的倍数，或者说 $v$ 是 $a_i$ 的因数。

同时满足所有的 $a_i$ 的 $v$，就是 $\{a_1,a_2,\dots,a_n\}$ 的公因数。因为题目要求最大化该速度，那我们就求出 $a$ 序列的**最大公因数**。

问题来了：如何使经过每个坐标刚好花费偶数时间呢？

让我们审视一下初二的物理入门公式：

$$t = \dfrac{s}{v} $$

其中 $t$ 是时间，$s$ 是路程，$v$ 是速度。

如果要使 $t$ 绝对成为一个偶数，我们将其**乘上二**即可。

那如何使等式右边保持平衡呢？

首先路程 $s$ 是无法改变的（输入坐标时已经确定），那只能看速度了。

由于速度 $v$ 在分母位置，所以我们将其除以二，式子变成了这样：

$$2 \times t = \dfrac{\ s\ }{\frac{v}{2}}$$

也就是说，我们求出序列 $a$ 的最大公因数后，将其除以二就能得到答案了。

那如果这个最大公因数**是个奇数**，除以二除不干净怎么办呢？这就是无解的情况了。

## Code Time

本题代码实现其实不难。我求最大公因数的 `gcd()` 函数是自己手写的辗转相除法，读者也可以采用内置的 `__gcd()` 函数来完成。

另外辗转相除法最坏复杂度是 $O(\log \max\{a,b\})$ 的，随机数据情况下接近 $O(1)$，能够通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a,g;
int gcd(int x,int y){return y?gcd(y,x%y):x;}

signed main()
{
	scanf("%lld",&n);
	while(n--)
	{
		scanf("%lld",&a);
		g = gcd(g,a);
	}
	if(g%2)printf("-1");
	else printf("%lld",g/2);
	return 0;
}
```

~~厚脸皮求赞~~

---

## 作者：Mierstan085 (赞：0)

首先感谢 @jjh20100730 dalao 提供的思路。

这是一道一道简单的数学题。

首先不难发现，起始时间为 $0$，那么到达每一个超市时的时间必须要能被 $v$ 整除，注意到题目要求最大，所以是要求 $a_i$ 的最大公因数。

注意到到达每个超市的时间必须要是偶数，这样的话不满足 $v$ 是最大公因数的条件，因为如果到达每个商店都是偶数的话，每个 $a_i$ 都是可以被 $2$ 整除的，那么这时的最大公因数是 $2v$，故不满足条件。

继续看条件，注意到把 $v$ 除以二后，到达每个超市的时间都会 $\times 2$，满足了偶数时间的条件。但是在 $v$ 是奇数的情况下，由于 $v$ 不能被 $2$ 整除，所以是无解的，所以要在 $v \bmod 2 = 1$ 的情况下输出 $-1$。

让我们来看代码吧！

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[(int)(2e6 + 5)];
int main(){
    int n;
    cin >> n;
    
    long long v;
    for (int i = 0; i < n; i ++){
        cin >> a[i];
        if (i == 0) v = a[0];
        else{
            v = __gcd(v, a[i]);
        }
    }
    
    if (v % 2 == 1) cout << -1;
    else cout << v / 2;
    return 0; // 撒花！
}
```

希望审核大大可以通过。

---

## 作者：Ferm_fire_yu (赞：0)

题目要求到达每个超市的时间都是偶数，不妨可以把超市的位置除以二，有要求可以到达每个超市，就可以通过对上述处理后的位置取最大公约数来获得答案。同时我们发现如果超市的位置不是偶数则无解输出 $-1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,ans=0;//记得开long long

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a%2!=0){
			cout<<-1;
			return 0;
		}
		ans=__gcd(ans,a/2);
	}
	cout<<ans;
	
	return 0;
}
```


---

## 作者：we_are_the_chuibing (赞：0)

### 思路

注意到经过每个超市的时间必须为整数，由此我们可以得出在满足此条件下，$v$ 的最大值为所有 $a_i$ 的最大公约数。可以推断出，此时经过超市的时间一定至少有一个奇数，因为全是偶数，所有的到达时间都有 $2$ 这个因子，与最大公约数定义不符。所以我们需要将 $v$ 除以 $2$，这样每个到达时间就会 $\times 2$，将每个到达时间都变成偶数。如果 $v$ 是奇数，输出 $-1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[2000001],g;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	g=a[1];
	for(int i=2;i<=n;i++)g=__gcd(g,a[i]);
	if(g%2)cout<<-1;
	else cout<<g/2;
	return 0;
}
```


---

## 作者：sbno333 (赞：0)

我们发现要维护时间为整数，这是相对重要的要处理的点。

从零点出发，每次移动 $v$，到达 $a_i$ 需要 $\frac {a_i} v$。

$\frac {a_i} v$ 为整数当且仅当 $v$ 为 $a_i$ 的因数。

那么我们的 $v$ 就需要是所有 $a_i$ 的公因数，由于任何公因数都是最大公因数的因子，因此我们取最大公因数。

接着到达超时的时间就是 $a_i$ 除去最大公因数，可以证明这些时间不可能都是偶数，否则最大公因数可以更大。

因此我们考虑让最大公因数还给 $a_i$ 一部分因数，使得时间重新变为偶数，最大公因数每除以一个数，时间就乘这个数。

由于要求 $v$ 最大，因此这个数要尽量小。

我们只需要时间是 $2$ 的倍数即可，由于最开始不是都是 $2$ 的倍数，所以必须乘，又由于是 $2$ 的倍数，那就要乘 $2$。

因此我们要使得这个数为 $2$。

当最大公因数为奇数时，则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int gc;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		gc=__gcd(gc,a);
	}
	if(gc%2){
		cout<<-1<<endl;
	}else{
		cout<<gc/2<<endl;
	}
	return 0;
} 
```

---

## 作者：_little_Cabbage_ (赞：0)

# P10183 [YDOI R1] Running 题解

~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p10183)~~

这是一道数学题。

根据题意，我们可以发现答案是这 $n$ 个数的最大公因数。而可以证明，这样至少会有一个位置的到达时间是奇数，因奇 $\times$ 偶 $=$ 偶，所以我们可以把 $n$ 个数的最大公因数除以 $2$，就能满足偶数经过时间这个条件。

注意要开 `long long`。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[2000010];
signed main()
{
	long long n;
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	long long ans=a[1];
	for(long long i=2;i<=n;i++)
	{
		ans=__gcd(ans,a[i]);
	}
	if(ans%2==1)
	{
		cout<<-1;
	}
	else
	{
		cout<<ans/2;
	}
	return 0;
}
```

---

## 作者：hjqhs (赞：0)

要求其实就是任意一个 $a_i$ 除以 $v$ 后是二的倍数。即为任意一个 $a_i$ 都是 $2\times v$ 的倍数。那只要求出 $v$ 的最大公约数，看看是否是二的倍数即可。  
```cpp
// Problem: T412398 [YDOI R1] Running
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T412398?contestId=152504
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Created Time: 2024-02-24 17:47:53
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;
const int N = 100005;
const int INF = 0x3f3f3f3f;
void solve() {
	int n, t = 0; cin >> n;
	rep(i, 1, n) {
		int x; cin >> x;
		if(i == 1) t = x;
		else t = __gcd(t, x);
	}
	cout << (t % 2 ? -1 : t / 2);
	return;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1;
	// cin >> T;
	while(T --) solve();
	return 0;
}
```

---

