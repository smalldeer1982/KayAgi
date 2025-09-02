# Vanya and Computer Game

## 题目描述

Vanya and his friend Vova play a computer game where they need to destroy $ n $ monsters to pass a level. Vanya's character performs attack with frequency $ x $ hits per second and Vova's character performs attack with frequency $ y $ hits per second. Each character spends fixed time to raise a weapon and then he hits (the time to raise the weapon is $ 1/x $ seconds for the first character and $ 1/y $ seconds for the second one). The $ i $ -th monster dies after he receives $ a_{i} $ hits.

Vanya and Vova wonder who makes the last hit on each monster. If Vanya and Vova make the last hit at the same time, we assume that both of them have made the last hit.

## 说明/提示

In the first sample Vanya makes the first hit at time $ 1/3 $ , Vova makes the second hit at time $ 1/2 $ , Vanya makes the third hit at time $ 2/3 $ , and both boys make the fourth and fifth hit simultaneously at the time $ 1 $ .

In the second sample Vanya and Vova make the first and second hit simultaneously at time $ 1 $ .

## 样例 #1

### 输入

```
4 3 2
1
2
3
4
```

### 输出

```
Vanya
Vova
Vanya
Both
```

## 样例 #2

### 输入

```
2 1 1
1
2
```

### 输出

```
Both
Both
```

# 题解

## 作者：Tx_Lcy (赞：3)

这是一道简单的二分。
## 思路
首先我们发现这个 $\frac{1}{x}$ 和 $\frac{1}{y}$ 非常难受，因为我们难以处理有关分数的问题，所以我们不妨把它们都乘 $x \times y$。我们发现这时 $\verb!Vanya!$ 的攻击时间变成了 $y$，$\verb!Vova!$ 的攻击时间变成了 $x$，所以我们不妨 $\verb!swap(x,y)!$，接下来就是常规的二分答案了，不再赘述。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int x,y;
inline bool check(int v,int s){return (v/x+v/y)>=s;}
inline void solve(int xs){
	int l=1,r=9e18;
	while (l<r){
		int mid=(l+r)>>1;
		if (check(mid,xs)) r=mid;
		else l=mid+1;
	}
	if ((l/x)*x>(l/y)*y) cout<<"Vanya\n";
    else if ((l/x)*x<(l/y)*y) cout<<"Vova\n";
    else cout<<"Both\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T,z;cin>>T>>x>>y;
	swap(x,y);
	while (T--) cin>>z,solve(z);
	return 0;		
}
```


---

## 作者：XL4453 (赞：3)

### 解题思路：

首先发现其实最后一下是谁打出的只和最后的 1s 内剩余的血量有关。那么考虑先预处理出每一秒内每一种剩下的血量是由谁打出的就可以 $O(1)$ 查询了。

记录当前每一个角色攻击了几次，然后计算出下一次攻击是由谁发动的。

具体的，设当前 Vanya 攻击了 $cnt_1$ 次,Vova 攻击了  $cnt_2$ 次。那么，若 $\dfrac{cnt_1+1}{x}<\dfrac{cnt_2+1}{y}$，则下一次攻击由 Vanya 发动，反之则是由 Vova 发动。如果两者相等，则两人同时发动攻击，此时造成的是两点伤害。

注意本题 $10^6$ 的数据范围在相乘是会爆 int，所以记得开 long long。

----
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long num[2000006],n,x,y,z,cnt1,cnt2;
int main(){
	scanf("%lld%lld%lld",&n,&x,&y);
	for(int i=1;i<=x+y;){
		if((cnt1+1)*y<(cnt2+1)*x)cnt1++,num[i]=1,i++;
		if((cnt1+1)*y>(cnt2+1)*x)cnt2++,num[i]=2,i++;
		if((cnt1+1)*y==(cnt2+1)*x)cnt1++,cnt2++,num[i]=num[i+1]=3,i+=2;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&z);
		if(num[z%(x+y)]==1)printf("Vanya\n");else
		if(num[z%(x+y)]==2)printf("Vova\n");else
		printf("Both\n");
	}
	return 0;
}
```


---

## 作者：_determination_ (赞：2)

这个分数攻击间隔搞得非常难受，考虑将其转化为整数。

注意到我们只关心是谁补得最后一刀，所以只要保持两人攻速的比例一样即可。两人攻速同时乘 $xy$ 即可。

之后考虑求出最后一刀的时间，可以二分。有了时间直接检查这个时刻是谁补的刀即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int x,y;
void solve()
{
	int n;
	cin >>n;
	int l=0,r=9e18;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(mid/x+mid/y>=n)r=mid;
		else l=mid+1;
	}
	if(l%x==0&&l%y==0)cout << "Both" << endl;
	else if(l%x==0)cout << "Vanya" << endl;
	else cout << "Vova" << endl;
}
signed main()
{
	int T;
	cin >>T >>x >> y;
	swap(x,y);
	while(T--)solve();
	return 0;
}
```

---

## 作者：A_zjzj (赞：2)

竟然又没有人做这题了

### 一道二分题

其实就是要找什么时候这个怪兽被打了 $a_i$ 次，可以知道，这是有单调性的，我们就可以二分。

因为 $Vanya$ 一秒打 $x$ 次，那么每 $\frac{1}{x}$ 他就打一次，所以我们直接把 $mid\div x+mid\div y$ 就知道这个怪兽在 $mid$ 秒时被打了几次。

```cpp
#include<cstdio>
using namespace std;
int n,x,y,t;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	while(n--){
		scanf("%d",&t);
		long long l=-1,r=1e15,mid;
		while(l+1<r){
			mid=(l+r)>>1;
			if(mid/x+mid/y>=t)r=mid;
			else l=mid;
		}
		if(r%x==0&&r%y==0)puts("Both");
		else if(r%x==0)puts("Vova");
		else puts("Vanya");
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
二分裸题。

先谈谈为什么二分。怪物的血量是固定的，同时不会加血，所以肯定血量是越来越小的，所以一定存在一个时间点血量为 $0$ 即为暴击。然后后面因为持续减血，所以直接小于等于 $0$ 了。显然符合单调性，二分求解时间点即可。
## 分析。
前面说了大体思路，我们进一步详细地谈一谈。

首先第一个人攻击一次需要 $\frac{1}{x}$ 秒，第二个人攻击一次需要 $\frac{1}{y}$ 秒。这两个数字显然都是小数，处理起来肯定是个小数的情况，无法确定最后一击来自于谁。

考虑转换。注意到有冷却时间，同时存在小数的时间的相对的倍数是整数。所以我们假定时间单位为 $t=x\times y$ 秒，这样我们可以把第一个人攻击一次和第二个人攻击一次所需要的时间都乘上一个 $t$ 秒，然后就转化成了第一个人攻击一次需要的时间就是 $y\ t$ 第二个人攻击一次需要的时间就是 $x\ t$ 随后二分最后需要多少 $t$ 的时间才够攻击 $a\left[i\right]$ 次。其实本质上就是通分。

二分答案即可。如果二分的答案不够整除的话，显然就已经不够再打一次了，所以向下取整即可。然后最后算出来的肯定是个整数，对 $x$ 和 $y$ 取模即可，谁整除就是谁击败的。如果都是 $0$ 就是同时击败的。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,x,y,a;
long long l,r,mid;
int main(){
	cin>>n>>x>>y;
	while(n--){
		cin>>a;
		l=0;
		r=1e16;
		while(l<r){
			mid=(l+r)>>1;
			if(mid/x+mid/y>=a){
				r=mid;
			}
			else l=mid+1;
		}
		if(l%x==0&&l%y==0){
			cout<<"Both\n";
		}
		else if(l%y==0){
			cout<<"Vanya\n";
		}
		else if(l%x==0){
			cout<<"Vova\n";
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：daniEl_lElE (赞：1)

## 思路

考虑循环节，容易发现一秒钟会有 $x+y$ 次攻击且所有秒内相同。那么我们可以先将每种攻击所在的时间点记录下来，进行排序后，除了最后两次是在一起的其他都是对应的那一方击败怪物。所以我们可以预处理 $O((x+y)\log(x+y))$，然后 $O(1)$ 对于每个询问取模 $(x+y)$ 后回答。

有个小细节，这边如果只判最后两次一起，要找到最小正循环节，即 $x,y$ 均除以 $\gcd(x,y)$。

## 代码

```cpp

#include <bits/stdc++.h>
#define int long long
#define double long double
#define mp make_pair
#define s(i,j) (i-1)*n+j
using namespace std;
string s[2000005];
signed main(){
	int n,x,y;
	cin>>n>>x>>y;
	int g=__gcd(x,y);
	x/=g,y/=g;
	pair<int,int> pr[x+y+1];
	for(int i=1;i<=x;i++){
		pr[i].first=y*i;
		pr[i].second=1;
	}
	for(int i=1;i<=y;i++){
		pr[i+x].first=x*i;
		pr[i+x].second=2;
	}
	sort(pr+1,pr+x+y+1);
	for(int i=1;i<=x+y-2;i++){
		if(pr[i].second==1) s[i]="Vanya";
		else s[i]="Vova";
	}
	s[x+y-1]=s[0]="Both";
	int tot=0;
	while(n--){
		int q;
		cin>>q;
		tot+=q;
		cout<<s[q%(x+y)]<<endl;
	}
	return 0;
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

~~这哪有蓝题可言。~~

二分查找即可。

可以将 $\dfrac{1}{x \times y}$ 秒，作为一个时间单位，计算第 $t$ 个时间单位后 Vanya 和 Vova 的攻击次数为 $\dfrac{t}{y}+\dfrac{t}{x}$，显然随着 $t$ 的增加打击次数是增加的，所以对于每个怪物使用二分查找，初始 $l=1,r=10^{15}$。

输出答案时：

只需检查 `l%y==0`，即 Vanya 执行了最后一击；

只需检查 `l%x==0`，即 Vova 执行了最后一击；

都能整除，即 Both。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	long  long n,x,y;
	scanf("%lld%lld%lld",&n,&x,&y);
	while(n--) {
		long long m;
		scanf("%lld",&m);
		long long mid,l=0,r=1e18;
		while(l<=r) {
			mid=(l+r)>>1;
			if(mid/x+mid/y>=m) {
				r=mid-1;
			} else {
				l=mid+1;
			}
		}
		long long ans=l;
		if(ans%x==0&&ans%y==0)
			puts("Both");
		else if(ans%y==0)
			puts("Vanya");
		else if(ans%x==0)
			puts("Vova");
	}
	return 0;
}
```


---

## 作者：_Clown_ (赞：0)

# D.Vanya and Computer Game
$\mathtt{Difficulty}$=$\mathtt{1800}$

这道题目不难想到用二分答案解决，

我们考虑二分 $\texttt{boss}$ 死亡的时间，

不难得到式子 $Hit=\frac{T}{X}+\frac{T}{Y}$。

而显然这个东西是具有单调性的，

所以我们的算法没有假。

而知道时间以后，

我们只要判一下是否整除，

就可以判断是谁进行了最后致命一击。

于是代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
#define int long long
int X,Y;
signed main(void)
{
	BetterIO;
	register int Case;cin>>Case>>X>>Y;while(Case--)
	{
		register int A;cin>>A;
		register int Left(0),Right(LONG_LONG_MAX),Ret;
		while(Left<Right)
		{
			register int Mid((Left+Right)>>1);
			if(Mid/X+Mid/Y>=A)Right=Ret=Mid;
			else Left=Mid+1;
		}
		if(!(Ret%X)&&!(Ret%Y)){cout<<"Both"<<endl;continue;}
		if(!(Ret%X)){cout<<"Vova"<<endl;continue;}
		if(!(Ret%Y)){cout<<"Vanya"<<endl;continue;}
	}
	return 0;
}
```

---

## 作者：MVP_Harry (赞：0)

楼上给的一个二分解法，我提供一个$O(x + y)$的解法。

刚开始看到题目有点懵，后来发现$x, y \le 10^6$这个条件，于是想到了先预处理一波，然后$O(1)$判断。

令$dp[i]$为一个```pair```，其中$1 \le i \le x + y$，表示进行第$i$此攻击时，首项记录第一个人打了多少次，次项记录第二个人打了多少次。然后剩下的判断递推就比较简单了，唯一需要注意的是```both```的情况。

下面直接放代码，递推可以参考一下。

```
#include<bits/stdc++.h>
#define ll long long
#define rep(i, m, n) for (int i = m; i <= n; i++)
using namespace std;

const int maxn = 2e6 + 5;

ll N, x, y;
pair<ll, ll> dp[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> x >> y;
    rep(i, 1, x + y) {
        if ((dp[i - 1].first + 1) * y == (dp[i - 1].second + 1) * x) {
            dp[i].first = dp[i - 1].first + 1;
            dp[i].second = dp[i - 1].second + 1;
            dp[i + 1].first = dp[i - 1].first + 1;
            dp[i + 1].second = dp[i - 1].second + 1;
            i++;
            continue;
        }
        if ((dp[i - 1].first + 1) * y < (dp[i - 1].second + 1) * x) {
            dp[i].first = dp[i - 1].first + 1;
            dp[i].second = dp[i - 1].second;
        } else dp[i].second = dp[i - 1].second + 1, dp[i].first = dp[i - 1].first;
    }
    rep(i, 1, N) {
        int a;
        cin >> a;
        a %= (x + y);
        if (dp[a].first == dp[a - 1].first + 1 && dp[a].second == dp[a - 1].second + 1) cout << "Both\n";
        else if (dp[a].first == dp[a - 1].first && dp[a].second == dp[a - 1].second) cout << "Both\n";
        else if (dp[a].first == dp[a - 1].first && dp[a].second == dp[a - 1].second + 1) cout << "Vova\n";
        else if (dp[a].first == dp[a - 1].first + 1 && dp[a].second == dp[a - 1].second) cout << "Vanya\n";
    }
    return 0;
}
```


---

## 作者：Vnlamac (赞：0)

**前言：** 感谢教练又给了我水蓝题的机会！

**思路：** 一开始在模拟赛场上看到题目，手写想到了暴力求解，结果大样例就超时了。后来仔细读一读题（读题还是有用的），发现了新大陆。这道题的答案是根据秒数决定的，而这击杀怪物的秒数，具有递增性质，符合二分答案的要求，所以果断二分。

**解法：** 先二分秒数，在判断分别除以 $x$ 和 $y$ 的和是否大于怪物血量，如果大于，就记录答案。

**主要代码：**
```cpp
int l,r,mid,ans;//ans 记录答案， l 是左端点， r 是右端点
l=0;r=1e18;
while(l<=r){
	mid=l+r>>1;
	if(mid/x+mid/y>=num){ans=mid;r=mid-1;}
	else l=mid+1;
}
if(ans%x!=0)printf("Vanya\n");//说明最后一击是 Vanya
else if(ans%y!=0)printf("Vova\n");//最后一击是 Vova
else printf("Both\n");//两个人一起将怪物击杀
```

最后注意在开头将 $int$ 类型定义为 $long long$ 型，或者把代码中的 $int$ 改为 $long long$ 就行了。

---

