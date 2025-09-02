# [USACO23FEB] Watching Mooloo B

## 题目描述

贝茜喜欢看 Mooloo 的演出。因为她是一只忙碌的奶牛，她计划在接下来的 $N (1 \le N \le 10^5)$ 天去看演出。因为 Mooloo 提供了订阅服务，她想要使她花费的钱最少。

Mooloo 有一个有趣的订阅服务系统：若要在此之后的连续 $d$ 天看演出，则在订阅时需要花费 $d+K(1 \le K \le 10^9)$ 个单位价格。你可以随时订阅；若本次订阅已经过期，你可以根据需要订阅多次。基于以上条件，请计算出贝茜最少要花费多少个单位价格，才能完成她的计划。

## 样例 #1

### 输入

```
2 4
7 9```

### 输出

```
7```

## 样例 #2

### 输入

```
2 3
1 10```

### 输出

```
8```

# 题解

## 作者：ivyjiao (赞：8)

题意：奶牛想看电视节目，这个电视节目支持两种充值方法：

1. 订阅 vip，每次花费 $k+1$ 元，能看 $1$ 天。
2. 续费，在已经订阅的情况下，花费 $1$ 元，多看 $1$ 天。

奶牛会在 $d_i$ 天看一次，求最省钱的订阅方法。

思路：如果下一次看距离这一次看的天数大于 $k$，则重新订阅，否则就续费。

时间复杂度是 $O(n)$。

代码：

```
#include<iostream>
using namespace std;
long long n,k,a[100001],ans,tmp;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		tmp=i;
		for(int j=i+1;j<=n;j++){
			if(a[j]-a[j-1]<=k){
				ans+=a[j]-a[j-1];
				tmp++;//如果续费是划算的
			}
			else break;//如果续费已经不再划算
		}
		ans++;
		ans+=k;
		i=tmp;
	}
	cout<<ans;
}

```

---

## 作者：incra (赞：2)

## 题解
一眼 DP。

设 $f_i$ 表示能看前 $1\sim i$ 集电视剧所花的最少钱数。
由于 $f_i$ 一定买了第 $i$ 次，所以不用把状态细分为是怎么买的。当然，细分状态也能过。

考虑 $f_i$ 和 $f_{i-1}$，若是续购，那么价格是 $d_i-d_{i-1}$，或者终端，在第 $i$ 重新购买，价格为 $k+1$。

这里解释一下为什么续购价格是 $d_i-d_{i-1}$，由于第 $i-1$ 天一定买了，并且在 $1\sim i-1$ 天中一定有一次是新买，即价格是 $k+1$。所以这里的 $f_1$ 不能按平常更新，只能新买，即价格为 $k+1$。
## 代码
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 100010;
int n;
LL k;
LL a[N];
LL f[N];
int main () {
	cin >> n >> k;
	for (int i = 1;i <= n;i++) cin >> a[i];
	f[1] = k + 1;
	for (int i = 2;i <= n;i++) f[i] = min (f[i - 1] + k + 1,f[i - 1] + a[i] - a[i - 1]);
	cout << f[n] << endl;
	return 0;
}
```

---

## 作者：是青白呀 (赞：1)

## 题目大意
奶牛有 $n$ 天想看电视节目，分别为 $a_1,a_2,\dots ,a_n$，但是看电视需要充值 vip，其中充值一次需要 $k+1$ 元即可看 1 天，若享受连续包天服务，每延长一天 vip 需要多花费 1 元，求奶牛需要花费的最小钱数。

## 解决方案

对于任意一个 $a_i$，除第一次只能重新充值外，都有重新充值和继续包天的两种方案，其中第一种方案会花费 $k+1$ 元，第二种方案从上一次看完电视到这一次看电视中间的每一天都要花 1 元，去除上次交过费的一天后，一共要充值 $a_i-a_{i-1}$ 元。由于无论选择哪种方案，选择后的结果都是“这一天购买了 vip”，对之后的决策没有影响，所以直接比较 $k+1$ 和 $a_i-a_{i-1}$ 的大小，选择较小的一个累加进答案即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,k,a[N];
signed main(){
	read(n),read(k);
	for(int i=1;i<=n;i++)
	    read(a[i]);
	int ans=k+1;
	for(int i=2;i<=n;i++){
		ans+=min(k+1,a[i]-a[i-1]);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：wuhan1234 (赞：0)

## 1.编程思路
由题意可知，
$ d_1 $ 天可先订购一天，订阅成本为 $ 1+k $。

从第 $ d_2 $ 天到 $ d_N$ 天，任意的第 $d_i$ 天可以有两种选择：

（1）在之前的第 $d_{i-1} $天的基础上连续订阅到 $ d_i$ 天，成本为 
$ d_i-d_{i-1} $；

（2）在 $ d_i $ 天重新订阅 1 天，订阅成本为 $ 1+k$。

两者之间选取成本少的即可。

## 2.源程序

```c
#include <stdio.h>
int main()
{
    int n;
    long long k;
    scanf("%d%lld",&n,&k);
    long long ans;
    long long pred,d;
    scanf("%lld",&pred);
    ans=1+k;
    int i;
    for (i=2;i<=n;i++)
    {
        scanf("%lld",&d);
        if (d-pred<=1+k) ans+=d-pred;
        else  ans+=1+k;
        pred=d;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Bulyly (赞：0)

### 解析
这道题的实现方法应该有很多，我们机房就出现了几种，下面说说我的 dp 写法。

- 令 $f[i]$ 表示计划里的第 $i$ 天时的最小费用，显然 $f[i]$ 只有两种转移路径，与之前的某一天连买，或者从该天开始单独买。

- 令 $a[i]$ 表示计划里的第 $i$ 天，当与之前某天 $j$ 之后连买时，$f[i]=f[j]+a[i]-a[j+1]+1$。由此看出，每次转移时只需要找到最小的 $f[j]-a[j+1]+1$ 即可。我们可以每次转移的时候来更新这个最小值即可。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long

using namespace std;

const int N=100010;
int f[N],a[N];

signed main()
{
	int n,k;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
	
	memset(f,127,sizeof f);
	f[0]=0;
	int Min=f[0]-a[1]+1;
	for(int i=1;i<=n;i++)
	{
		f[i]=min(f[i-1]+1+k,Min+k+a[i]);
		Min=min(Min,f[i]-a[i+1]+1);
//		cout<<f[i]<<" "<<Min<<endl;
	}
	printf("%lld",f[n]);
	
	return 0;
}
```
完结撒花~


---

## 作者：liyuanchen2021 (赞：0)

本题用到的算法是线性 DP。

对于第 $d_1$ 天，只有一种选择——买票，当天花费为 $k+1$。

对于第 $d_i$ 天，有两种选择：

- 买票，当天花费为 $k+1$；
- 不买票，当天花费为 $d_i - d_{i-1}$。

我们设 $f_i$ 为前 $d_i$ 天的花费总和，递推式如下：

- 若 $i=1$，则 $f_i=k+1$；
- 若 $i>1$，则 $f_i=\min\{f_{i-1}+(k+1),f_{i-1}+(d_i-d_{i-1})\}$。

最后输出 $f_n$ 即可。

```cpp
#include <iostream>
using namespace std;
long long d[100005], f[100005];
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)	cin >> d[i];
	f[1] = k + 1ll;
	for (int i = 2; i <= n; i++)
		f[i] = min(f[i - 1] + (d[i] - d[i - 1]), f[i - 1] + (k + 1ll));
	cout << f[n] << endl;
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

首先我们可以考虑暴力。可以令 $f_i$ 表示取到 $i$ 位置的最大值，所以我们可以推出递推方程：

$f_i = f_{j-1}+d_i-d_j+1+k$

其中 $j$ 为使得 $f_i$ 取得最小值的点。

这样的复杂度是 $\Theta (n^2) $，会得到 TLE 。

考虑优化，我们再整理一下这一条式子：

$f_i = (f_{j-1}-d_j)+(d_i+1+k)$

我们发现，对于同一个 $i$，$(d_i+1+k)$ 为定值，所以我们可以考虑维护 $(f_{j-1}+d_j)$ 的最小值。而 $(f_{j-1}+d_j)$ 仅与 $j$  有关，所以，我们维护最小值是容易的。

接下来是本题的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
long long n,d[N],f[N],k,minn;//minn就是前缀最小值
inline long long min(long long x,long long y){return x<y?x:y;}
int main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&d[i]);
	minn=f[0]-d[1];
	for(int i=1;i<=n;i++){
		f[i]=min(f[i-1]+k+1,d[i]+minn+k+1);
		minn=min(minn,f[i]-d[i+1]);//维护最小值
	}
	printf("%lld",f[n]);
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

简单的贪心。

假设第 $x$ 次看电视在第 $a_1$ 天，第 $x+1$ 次看电视在第 $a_2$ 天。

观察订阅方式，可以发现对于第 $a_2$ 天来说，它要么从第 $a_1$ 天开始连续订阅，花费 $a_2-a_1$ 的代价。要么从今天开始重新订阅，花费 $1+k$ 的代价。并且前一天的选择与后一天没有任何关系。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,D,ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	n=read();k=read();D=read();
	if(n==1){
		cout<<1+k<<endl;return 0;
	}
	ans+=(1+k);
	for(int i=2;i<=n;i++){
		int d=read();
		if((d-D)<=1+k)ans+=(d-D);
		else ans+=(1+k);
		D=d;
	}
	cout<<ans;
	return 0;
}

```


---

