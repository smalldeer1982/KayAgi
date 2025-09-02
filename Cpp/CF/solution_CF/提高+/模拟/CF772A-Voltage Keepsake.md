# Voltage Keepsake

## 题目描述

You have $ n $ devices that you want to use simultaneously.

The $ i $ -th device uses $ a_{i} $ units of power per second. This usage is continuous. That is, in $ λ $ seconds, the device will use $ λ·a_{i} $ units of power. The $ i $ -th device currently has $ b_{i} $ units of power stored. All devices can store an arbitrary amount of power.

You have a single charger that can plug to any single device. The charger will add $ p $ units of power per second to a device. This charging is continuous. That is, if you plug in a device for $ λ $ seconds, it will gain $ λ·p $ units of power. You can switch which device is charging at any arbitrary unit of time (including real numbers), and the time it takes to switch is negligible.

You are wondering, what is the maximum amount of time you can use the devices until one of them hits $ 0 $ units of power.

If you can use the devices indefinitely, print -1. Otherwise, print the maximum amount of time before any one device hits $ 0 $ power.

## 说明/提示

In sample test 1, you can charge the first device for the entire time until it hits zero power. The second device has enough power to last this time without being charged.

In sample test 2, you can use the device indefinitely.

In sample test 3, we can charge the third device for $ 2/5 $ of a second, then switch to charge the second device for a $ 1/10 $ of a second.

## 样例 #1

### 输入

```
2 1
2 2
2 1000
```

### 输出

```
2.0000000000```

## 样例 #2

### 输入

```
1 100
1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 5
4 3
5 2
6 1
```

### 输出

```
0.5000000000```

# 题解

## 作者：Martin6666 (赞：2)

```
#include<bits/stdc++.h>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 111115;
int n, m;
struct node {
	int p,c;
	double t;
} a[maxn];
int main() {
	scanf("%d %d",&n,&m);
	long long sum=0;
	for(int i=1; i<=n; ++i) {
		scanf("%d %d",&a[i].p,&a[i].c);
		a[i].t=a[i].c*1.0/a[i].p;
		sum+=a[i].p;
	}
	if(m>=sum) {
		printf("-1\n");
		return 0;
	}
	double l=0.0000001,r=1e18;
	while(r-l>=0.0000001) {
		double mid=(l+r)/2;
		double s=0;
		for(int i=1; i<=n; ++i) {
			if(a[i].t<mid) s+=(mid-a[i].t)*a[i].p;
		}
		if(s>m*mid) r=mid-0.0000001;
		else l=mid+0.0000001;
	}
	printf("%lf",l);
	return 0;
}

```

---

## 作者：xxzjbd (赞：1)

## 二分答案，题稍微有些坑
先来解释下题意，其实这题没有很复杂，因为时间可以是任意实数，只需要满足在某个时间，充电器的总供电能保证每个用电即可。本蒟蒻开始认为只有一个充够了整数秒才可以接下一个，这就成大模拟了。

本题分为两种情况，设用电器功率 $W1$ ，充电器功率 $W2$ ，原有电量 $sum$ 。

当 $W1$ $< = $ $W2$ 时，不会出现供电不足，输出 $-1$ 。或者存在某个时间，使 $W1$ * $t$ $+$ $sum$ 最接近 $W2$ * $t$ 。显然，当 $t$ 继续增大大时，耗电增长比供电快，无法持续供电，此时 $t$ 即为答案。由此得出，本题满足单调性，所以利用二分求解。

注意两点
1. 本题有精度要求，不能直接套二分模板。
2. 右边界很大，$0x3f3f3f3f$ 直接错，最后开到了 $1e10$ 。 

## 代码如下
```cpp
#include<cstdio>
#define int long long
using namespace std;
double sum,tot;
int a[100010],b[100010];
signed main(){
	int n,p;
	scanf("%lld%lld",&n,&p);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%lld%lld",&a[i],&b[i]);
		sum+=a[i];
	}
	if(sum<=p){
		printf("-1");
		return 0;
	}	
	double l=0,r=10000000000;
	for(int i=1;i<=200;i++){//精度问题不能用l<=r 
		sum=0;
		int v=0;
		double mid=(l+r)/2;
	    tot=mid*p;
		for(int j=1;j<=n;j++)
			if(mid*a[j]-b[j]>0){
				sum+=mid*a[j]-b[j];
				if(sum>tot){
					v=1;
					r=mid;
					break;
				}
			}
		if(!v)l=mid; 
	}
	printf("%.10lf\n",l);
	return 0; 
}
```
## 谢谢观赏

---

## 作者：wawatime1 (赞：1)

### 题目分析
这道题咋跟 [p3743](https://www.luogu.com.cn/problem/P3743) 一模一样呢？

此题显然是**二分答案**：题目要找设备能一起运行的最长时间，这个时间值有范围且具有**单调性**（若 $t$ 时间满足条件，小于 $t$ 的时间必然满足），所以适合二分答案。

- 二分**范围**设定：左边界设为 $0$，因为时间不能为负；右边界设为 $10^{10}$，假设在这个较大时间内可找到答案，若最后右边界仍为 $10^{10}$，表示要无限使用设备，输出 $-1$。

- 判断函数 check：二分过程中，对中间时间 $mid$，通过 check 函数判断充电宝在 $mid$ 时间内提供的能量能否弥补各设备消耗的能量。遍历每个设备，若设备在 $mid$ 时间消耗能量大于初始能量，计算出充电宝需补充的能量并累加，最后对比充电宝提供能量与总补充能量需求。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, p, a[100005], b[100005];
bool calc(double x) {
    double need = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] * x > b[i]) {
            need += a[i] * x - b[i];
        }
    }
    return p * x >= need;
}
int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    double l = 0, r = 1e10;
    while (r - l >= 1e - 6) {
        double mid = (l + r) / 2;
        if (calc(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (r == 1e10) {
        cout << -1;
    } else {
        cout << r;
    }
    return 0;
}
```

---

## 作者：DennyQi (赞：1)

二分答案。

设最后花的时间为$k$，则如果第$i$个机器满足$b_i-ka_i \geq 0$，则不需要充电。否则就需要花$\dfrac{ka_i-b_i}{p}$的时间来充电。如果所有充电时间的总和超过了$k$，那么显然无法满足。

如果每秒钟消耗的电量小于等于每秒能充电的电量，那么电会越充越多，也就能永远工作下去了。注意在累加总时间的时候会超过$\text{int}$。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
const int N = 100010;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n;
long long tot;
double p,a[N],b[N],l,r,mid;
inline bool judge(double k){
	double res = 0;
	for(int i = 1; i <= n; ++i){
		if(b[i] - k*a[i] > 1e-6) continue;
		res += (k * a[i] - b[i]) * 1.00 / p;
	}
	if(res - k > 1e-6) return 0;
	return 1;
}
int main(){
	scanf("%d%lf",&n,&p);
	for(int i = 1; i <= n; ++i){
		scanf("%lf%lf",a+i,b+i);
		tot += a[i];
	}
	if(p - tot >= 0){
		printf("-1\n");
		return 0;
	}
	l = 0.00000, r = 99999999999999.99999;
	while(r - l >= 1e-6){
		mid = (l+r) * 1.00 / 2.00;
		if(judge(mid)){
			l = mid;
		}else{
			r = mid;
		}
	}
	printf("%.12f\n",l);
	return 0;
}
```

---

