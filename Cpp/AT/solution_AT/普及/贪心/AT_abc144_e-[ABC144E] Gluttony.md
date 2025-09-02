# [ABC144E] Gluttony

## 题目描述

高桥君参加大胃王比赛。比赛由 $N$ 人组成的团队为基本单位参赛，高桥君的队伍的队员从 $1\sim N$ 编号。第 $i$ 名队员的消化代价为 $A_i$。

比赛有 $N$ 种不同的食物，每位队员需要负责吃掉其中一种食物，不能有两名队员吃同一种食物，也不能让一名队员吃多与一种食物。第 $j$ 种食物的难吃程度为 $F_j$。 消化代价 $x$ 的队员吃完难吃程度 $y$ 的食物需要花费 $x\times y$ 秒。 整个队伍的成绩是 $N$ 名队员吃完食物花费时间的最大值。

比赛前，高桥君的队伍会进行修行。一次修行可以将一名消化代价大于 $0$ 的队员的消化代价减少 $1$。由于修行需要消耗庞大的食费，因此最多只能进行 $K$ 次修行。

通过修行和适当选择每位队员吃的食物，高桥队在比赛中能够获得的最好成绩是多少？

## 说明/提示

$1$ 号队员进行 $4$ 次修行，吃 $2$ 号食物，花费 $0$ 秒。

$2$ 号队员进行 $1$ 次修行，吃 $3$ 号食物，花费 $1$ 秒。

$3$ 号队员进行 $0$ 次修行，吃 $1$ 号食物，花费 $2$ 秒。

总成绩取最大值 $2$ 秒。


$1 \le N \le 2\times 10^5$

$0 \le K \le 10^{18}$

$1 \le A_i \le 10^6$

$1 \le F_i \le 10^6$

## 样例 #1

### 输入

```
3 5
4 2 1
2 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 8
4 2 1
2 3 1```

### 输出

```
0```

## 样例 #3

### 输入

```
11 14
3 1 4 1 5 9 2 6 5 3 5
8 9 7 9 3 2 3 8 4 6 2```

### 输出

```
12```

# 题解

## 作者：ace_amuro (赞：6)

# 题目翻译

AtCoder ABC144E Gluttony

【题目描述】

高桥君参加大胃王比赛。比赛由 $N$ 人组成的团队为基本单位参赛，高桥君的队伍的队员从  $1\sim N$  编号。第 $i$ 名队员的消化代价为 $A_i$ 。

比赛有 $N$ 种不同的食物，每位队员需要负责吃掉其中一种食物，不能有两名队员吃同一种食物，也不能让一名队员吃多与一种食物。第 $j$ 种食物的难吃程度为 $F_j$ 。 消化代价 $x$ 的队员吃完难吃程度 $y$ 的食物需要花费 $x\times y$ 秒。 整个队伍的成绩是 $N$ 名队员吃完食物花费时间的最大值。

比赛前，高桥君的队伍会进行修行。一次修行可以将一名消化代价大于0的队员的消化代价减少1。由于修行需要消耗庞大的食费，因此最多只能进行 $K$ 次修行。

通过修行和适当选择每位队员吃的食物，高桥队在比赛中能够获得的最好成绩是多少？

【输入格式】

第1行，两个正整数 $N,K$ 

第2行， $N$ 个正整数 $A_1,A_2,\cdots,A_N$ 

第3行， $N$ 个正整数 $F_1,F_2,\cdots,F_N$ 

【输出格式】

输出高桥队的最好成绩

【输入样例\#1】
```
3 5
4 2 1
2 3 1
```
【输出样例\#1】
```
2
```

【样例\#1说明】

1号队员进行4次修行，吃2号食物，花费0秒。

2号队员进行1次修行，吃3号食物，花费1秒。

3号队员进行0次修行，吃1号食物，花费2秒。

总成绩取最大值2秒。

【数据说明】

 $1 \le N \le 2\times 10^5$ 

 $0 \le K \le 10^{18}$ 

 $1 \le A_i \le 10^6$ 

 $1 \le F_i \le 10^6$ 

# 题目解析

先考虑比赛时的策略：若 $A_i \ge A_j, F_i \ge F_j$ ，则 $\max\{A_iF_j , A_jF_i\} \le A_iF_i = \max\{A_iF_i, A_jF_j\}$ 。所以将 $A$ 升序排列， $F$ 降序排列后一一对应是最佳策略。

随着修行次数增多，成绩一定不会变差，所以可以二分答案。对于成绩 $x$ ，计算：“要使得每名队员的时间都小于等于 $x$ ，所需的最小修行次数”。计算方法是：按将 $A$ 升序排列， $F$ 降序排列后，计算要让 $A_iF_i \le x$ ， $A_i$ 需要减少的次数，这个次数等于 $\left\lceil\frac{A_iF_i-x}{F_i} \right\rceil$ 。最后判断修行总次数是否小于等于 $K$ 。

# 代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long LL;
const int MR=2e5+10;
int n;
LL k,a[MR],f[MR];

//判断能否在k次修行内，让所有人的成绩都小于等于x
bool check(LL x){
    LL cnt=0;
    //计算让所有人的成绩都小于等于x需要的修行次数
    for(int i=1;i<=n;i++){
        //如果成绩大于x
        //那么需要修行的次数等于a[i]*f[i]-x除以f[i]后向上取整
        if(a[i]*f[i]>x){
            cnt+=(a[i]*f[i]-x+f[i]-1)/f[i];
        }
    }
    return cnt<=k;
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>f[i];
    //排序，A升序，F降序
    sort(a+1,a+1+n);
    sort(f+1,f+1+n);
    reverse(f+1,f+1+n);
    LL l=-1,r=1e12+10,m;
    while(l<r-1){
        m=(l+r)/2;
        if(check(m)){
            r=m;
        }
        else{
            l=m;
        }
    }
    cout<<r<<endl;
    return 0;
}

```


---

## 作者：do_it_tomorrow (赞：3)

[更好的阅读体验](https://doittomorrow.xyz/post/abc144egluttony-de-ti-jie/)
# 题目大意：
有两个数组 $a_i$ 和 $f_i$，任意选取若干个 $a_i$ 使他们一共减少的数量在不超过 $k$ 的情况下，任意将 $a$ 数组与 $f$ 中的元素进行匹配，使两两间的乘积的最大值最小。

# 分析
首先考虑 $k=0$ 的情况：对于任意的 $a_i<a_j$，$f_x<f_y$，可以发现 $\max(a_i\times f_y,a_j\times f_x)\le \max(a_i\times f_y,a_j\times f_x)$。所以将 $a$ 数组升序排列，将 $f$ 数组降序排列，一一对应就是最优的情况了。

因为减少的量越大获得乘积的最大值越小，所以这个问题具有单调性，可以使用二分进行求解。

可以二分乘积的最大值最小值，通过最小值与 $f_i$ 求解出如果需要满足这个最小值 $a_i$ 的最大值，计算出需要更改的数量，并判断是否小于 $k$，即满足 $\sum_{i=1}^n\lceil \frac{A_i \times F_i-x}{F_i} \rceil <k$。

# AC Code
```c++
#include<bits/stdc++.h>
#define ceil(a,b) a/b+(a%b!=0)
#define int long long
using namespace std;
const int N=2e5+5;
int n,k,a[N],f[N],l=0,r=1e18,ans=-1,s[N];
bool cmp(int a,int b){
	return a>b;
}
bool ck(int x){
	int cnt=0;
	for(int i=1;i<=n;i++){
		int sb=a[i]*f[i];
		if(sb>x) cnt+=ceil((sb-x),f[i]);
	}
	return (cnt<=k);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>f[i];
	sort(a+1,a+1+n),sort(f+1,f+1+n,cmp);
	while(l<=r){
		int mid=(l+r)/2;
		if(ck(mid)){
			r=mid-1;
			ans=mid;
		}else l=mid+1;
	}cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：cjh20090318 (赞：3)

## 题意

翻译很清楚，略。

## 分析

经过观察最优方案一定是消化代价小的配难消化的菜。所以将 $F$ 从小到大排序，$A$ 从大到小排序，当然也可以反着来。

因为有 $K$ 次修行的机会，难以直接贪心。

因为随着时间增加，修行的使用次数会减少，存在单调性。所以考虑使用二分答案转化为判定性问题，即判定最多使用修行次数小于等于 $K$。

设对于第 $i$ 个人需要修行 $t$ 次，那么必须满足 $(A_i-t)F_i \le x$，所以 $t \ge A_i - \dfrac{x}{F_i}$。

因为 $t,A_i$ 均为整数，所以 $t \ge \left\lceil A_i - \dfrac{x}{F_i} \right\rceil = A_i - \left\lfloor \dfrac{x}{F_i} \right\rfloor$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<functional>
#define MAXN 200002
using namespace std;
typedef long long LL;
int n;
LL k;
int a[MAXN],f[MAXN];
LL check(const LL&x){
	LL ret=0;
	for(int i=1;i<=n;i++) ret+=max(a[i]-x/f[i],0ll);//注意下界是 0，不能做负数次修行。
	return ret;
}
int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&f[i]);
	sort(a+1,a+n+1,greater<int>()),sort(f+1,f+n+1);
	LL l=0,r=1000000000000ll;
	for(LL mid;l<r;){//二分答案。
		mid=(l+r)>>1;
		if(check(mid)>k) l=mid+1;
		else r=mid;
	}
	printf("%lld\n",l);
	return 0;
}
```

---

## 作者：Zjh6666 (赞：1)

# 洛谷[ABC144E] Gluttony
## 思路
这是一道十分经典的二分＋贪心题。　

我们可以先二分答案高桥队在比赛中能够获得的最好成绩，在  `check()` 函数中分析高桥队在比赛中能够获得的最好成绩是 $x$ 时需要的最少修行次数 $t$ ，如果 $t > k $ 那么 `l=mid+1`，否则 `r=mid`。

注意： 二分前要先排序，排序应该先从小到大排序在用 `reverse()` 函数反转，否则第 4 个点会 T 掉 ~~别问我是怎么知道的，都是泪QAQ~~

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[200005],f[200005];
bool check(long long x){
	long long t=0;
	for(int i=1;i<=n;i++){
		if(a[i]*f[i]>x){//如果消化代价a[i]的队员无法在x秒内吃完难吃程度f[i]的食物 
			t+=ceil(1.0*(a[i]*f[i]-x)/f[i]);//ceil(i)：将i向上取整 
		}//修行次数增加 
	}
	if(t>k){//如果不满足要求 
		return false;
	}
	return true;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>f[i];
	}
	sort(a+1,a+n+1);//对a[i]~a[n]从小到大排序    |
	sort(f+1,f+n+1);//			   　			|->贪心思想（让a[i]*f[i]尽可能小） 
	reverse(f+1,f+n+1);//对f[i]~f[n]从大到小排序 |
	long long l=0,r=1000000000000005,mid;
	while(l<r){//二分答案 
		mid=(l+r)/2;
		if(check(mid)){
			r=mid;//r有可能是解，所以不用 r-- 
		}else{
			l=mid+1;//l不可能是解 
		}
	}
	cout<<r;//输出 
 	return 0;
}
```

---

## 作者：zhangjiting (赞：1)

## 题意 

高桥君参加大胃王比赛。比赛由 $N$ 人组成的团队为基本单位参赛，高桥君的队伍的队员从 $1\sim N$ 编号。第 $i$ 名队员的消化代价为 $A_i$。

比赛有 $N$ 种不同的食物，每位队员需要负责吃掉其中一种食物，不能有两名队员吃同一种食物，也不能让一名队员吃多与一种食物。第 $j$ 种食物的难吃程度为 $F_j$。 消化代价 $x$ 的队员吃完难吃程度 $y$ 的食物需要花费 $x\times y$ 秒。 整个队伍的成绩是$N$名队员吃完食物花费时间的最大值。

比赛前，高桥君的队伍会进行修行。一次修行可以将一名消化代价大于 $0$ 的队员的消化代价减少 $1$。由于修行需要消耗庞大的食费，因此最多只能进行 $K$ 次修行。

通过修行和适当选择每位队员吃的食物，高桥队在比赛中能够获得的最好成绩是多少？

## 思路

一眼二分答案。

先考虑如何分配人和食物。

让最大的数对最小的数，最大的成绩会最小。所以，对数组 $a$ 升序排序，对数组 $f$ 降序排序，就会最小化最大时间。

二分一个最大消化时间，每个人需要修炼的次数就是 $\lceil \frac{A_i \times F_i-x}{F_i} \rceil$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],f[200005],n,k,ans;
int check(int x){
	int s=0;
	for(int i=1;i<=n;i++){
		if(a[i]*f[i]>x){
			s+=(a[i]*f[i]-x)/f[i]+((a[i]*f[i]-x)%f[i]>0);
		}
	}
	return s;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>f[i];
	sort(a+1,a+n+1);
	sort(f+1,f+n+1,greater<int>());
	int l=0,r=LONG_LONG_MAX;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)<=k) {
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：shaozhehan (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT_abc144_e)

[AtCoder 链接](https://atcoder.jp/contests/abc144/tasks/abc144_e)

题目大意：

有 $N$ 个人，第 $i$ 个人的消化代价为 $a_i$。同时，有 $N$ 堆食物等着吃，第 $i$ 堆食物的难吃程度为 $f_i$。消化代价为 $x$ 的人消化难吃程度为 $y$ 的食物需要 $xy$ 分钟。但是，这 $N$ 个人可以进行最多 $K$ 次修行，每次修行可以使其中一个人的消化代价减去 $1$。设这 $N$ 个人的消化时间为所有人需要消化他们吃的食物的事件的最大值。问你消化时间的最小值。

思路：

我们暂时不考虑修行。

显然，如果 $a_i\geq a_j\And f_i\leq f_j$，那么 $a_if_j\geq a_jf_j\geq a_jf_i$，所以如果我们将数列 $a$ 升序排列、数列 $f$ 降序排列，就可以使得 $\sum\limits_{i=1}^{N}a_if_i$ 取到最小值。

但是，这 $N$ 个人还可以进行 $K$ 次修行，怎么办呢？我们考虑[二分](https://oiwiki.org/basic/binary/#%E4%BA%8C%E5%88%86%E7%AD%94%E6%A1%88)消化时间 $t$。我们设最小值 $l=0$、最大值 $r=10^{12}+10$。

其中，我们还需要写判断消化时间 $t$ 是否可行的函数 $chk$。我们可以遍历数组 $a$，如果 $a_if_i>t$，那么我们就需要 $\left\lceil\dfrac{a_if_i-t}{f_i}\right\rceil$ 次修行使得 $a_if_i\leq t$。这里，考虑到浮点误差的风险，我们不使用 ```cmath``` 中的 ```ceil``` 函数，而是改用 $\left\lfloor\dfrac{a_if_i-t+f_i-1}{f_i}\right\rfloor$ 来计算 $\left\lceil\dfrac{a_if_i-t}{f_i}\right\rceil$。最终，我们把计算结果加到储存修行次数的变量 $sum$ 里，如果 $sum\leq k$，这种方法就可行，否则就不可行。

我们可以写出 $chk$ 函数的代码。
```cpp
inline bool chk(const long long &x){// 全程开 long long！
    long long sum = 0;
    for (int i = 1; i <= n; i++){
        if (1ll * a[i] * f[i] > x){
            sum += (1ll * a[i] * f[i] - x + f[i] - 1) / f[i];// 避免浮点误差，向上取整公式
        }
        if (sum > k){// 不符合要求就退出函数
            return false;
        }
    }
    return true;// 符合要求
}
```
最终，我们输出答案就大功告成了。

坑点：

1. 慎用 ```int```，以防炸精度！
1. 因为有可能 $\sum\limits_{i=1}^{N}a_if_i=0$，所以二分的最小值 $l$ 要设为 $0$ 而不是 $1$！
1. 数列 $f$ 需要降序排序，我们要写 $cmp$ 函数而不是重载运算符，以免波及其他运算！
1. $N$ 和 $K$ 要定义在主函数外面，以防 $chk$ 函数导致编译错误！

完整代码贴在[这里](https://www.luogu.com.cn/paste/jmdik7bo)。

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题需要用到的只有二分与贪心，其实也是很简单的。

首先我们可以想到用人小的去吃数值较大的食品，那么我们就可以把两组数据分别按照从小到大与从大到小进行排序，然后二分找合适的用时，用贪心的方式看看这个时间能否全部吃完，如果能就向下再二分，否则向上。这样就没有问题了。
## 本题代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200001],b[200001];
bool cnp(long long a,long long b){return a>b;}
bool pd(long long x,long long n,long long k)
{
	long long sum=k;
	for(long long i=1;i<=n;i++)
	{
		if(a[i]*b[i]>=x)
		{
			sum-=(a[i]*b[i]-x)/b[i]+((a[i]*b[i]-x)%b[i]!=0);
		}
	}
	if(sum>=0) return 1;
	else return 0;
}
int main()
{
	long long n,k;
	cin>>n>>k;
	for(long long  i=1;i<=n;i++) cin>>a[i];
	for(long long  i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1,cnp);
	long long l=0,r=a[n]*b[1];
	while(l<=r)
	{
		long long mid=(l+r)/2;
		if(pd(mid,n,k)==1) r=mid-1;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：chrispang (赞：0)

这道题是一道二分答案的题，并不是特别难，那么本蒟蒻就给大家浅浅的分析一下吧！

首先我们可以想到让消耗代价小的队员去吃难吃程度大的食物，消耗代价大的队员去吃难吃程度小的食物，这样贪心思路就完成啦！

然后我们二分需要花费的时间最大值，如果发现一个队员无法在规定时间里吃完东西，则进行修行。如此算下来，最后看看修行次数是否小于等于 $k$ 就可以了。

上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, k, a[200010], f[200010];
bool check(int x) {
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		//需要修行的次数：(a[i] * f[i] - x) / f[i]向上取整 
		if(a[i] * f[i] > x) cnt += (a[i] * f[i] - x + f[i] - 1) / f[i];
	return cnt <= k;
}

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> f[i];
	sort(a + 1, a + n + 1); //升序
	sort(f + 1, f + n + 1, greater<int>()); //降序 
	int l = -1, r = 1e15 + 10;
	while(l < r - 1) { //区间只剩下两个时，退出 
		int mid = (l + r) / 2; //枚举花费时间 
		if(check(mid)) r = mid; //说明可以，接着找是否有更小的值 
		else l = mid; //否则接着往大的找 
	}
	cout << r << endl;
    return 0;
}
```
最后，请大家给本蒟蒻点个赞吧，谢谢啦！！！

---

## 作者：lzbzl (赞：0)

# AT_abc144_e Gluttony 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc144_e)

一道贪心加二分答案的题目。

### 分析
通过观察题目可提取关键词：最大值最小，所以可以确定这题大概率是一道二分答案。我们可以二分枚举最大成绩，再结合一点贪心。

### 贪心思路

我们先假设只有两个人 $a$ 和 $b$ 和两种食物 $c$ 和 $d$。我们有两种选择：$ac$ 和 $bd$ 或 $ad$ 和 $bc$。我们需证明这两种情况哪一种是最优解。假设第二种情况最优，即：
$$
\max(ad,bc)>\max(ac,bd)
$$
简单运算可得该假设正确。所以人的消化能力升序排列，食物降序排列然后两两相乘即为最优解。

我们用二分查找最大的最小值。当 $a_i×f_i$ 大于当前枚举的最大最小值 $x$，则利用修行降低 $a_i×f_i$ 的大小，修行次数为 $\sum_{i=1}^n⌈\frac{a_i×f_i-x}{f_i}⌉$，只需判断总修行次数为多少然后进行二分。

代码贴上方便理解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],b[200005];
bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]*b[i]>x)
		{
			cnt+=ceil((double)(a[i]*b[i]-x)/(double)(b[i]));
		}
	}
	return cnt<=m;
}
bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int j=1;j<=n;j++)
		cin>>b[j];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1,cmp);
	int l=0,r=1e18;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	cout<<r;
	
	return 0;
}
```
感谢管理员审核。

---

## 作者：wbxxxx (赞：0)

# 思路： 
这是一道贪心和二分的组合题，要使最大吃完食物时间尽可能的短，我们需要将每个人的消化代价从小到大排序，食物难吃程度从大到小排序，然后二分，贪心即可。其中用 $cyt$ 函数来判断最好成绩是 $x$ 的最小修行次数。

其中我们还可以特判一下输出 $0$ 的情况。

**代码：**

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 100000009
using namespace std;
int read()
{
    int X=0,w=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-') w=-1;ch=getchar();}
    while(ch<='9' && ch>='0') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}//快读

int a[10000009],b[100000009],c[10000009];
int n,m,i,j,k,cnt,sum;
bool cyt(int x)
{
	int ans=0;
	for(int i=1;i<=n;i++) {
		cnt=a[i]*b[i];
		if (cnt>x) ans+=(a[i]*b[i]-x+b[i]-1)/b[i];
	}//判断最小修行次数，如果成绩大于 x ，结果向上取整
	return ans<=m;
}
bool cmp(int a,int b){
	return a>b;
}//倒序
signed main()
{
    int x=0,y=1e12+10,jj=0;
	n=read(),m=read();
	for (i=1;i<=n;i++) a[i]=read(),jj+=a[i];//计算总消化代价;
	for (i=1;i<=n;i++) b[i]=read();
	if (m>=jj){
		cout<<0;
		return 0;
	}//特判一下，如果修行次数大于总消化代价，直接输出 0 即可 
	sort(a+1,a+n+1);
	sort(b+1,b+n+1,cmp);//从大到小排序 
	while (x<y-1)
	{
		sum=(x+y)/2;
		if (cyt(sum)) y=sum;
		else x=sum;
	}
	cout<<y;
	return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 思路

简单二分，首先要知道，如何搭配所花费的时间最少，就是让吃东西代价最小的去吃最难吃的食物 ~~（有点残忍）~~，至于为什么，其它题解已经说得很清楚了。接着直接二分，当成绩为 $t$ 时，需要修行次数 $\leq k$，说明更大的 $t$ 一定可行，应当尝试更小的 $t$。当成绩为 $t$ 时，需要修行的次数 $>k$，说明更小的 $t$ 一定不行，应当尝试更大的 $t$。所以直接二分 $t$ 即可。但是在 ``check`` 函数里有一个问题。就是我们无法得知当前这个人的成绩要到 $t$ 之内，需要修行多少次，我们不妨设这个次数为 $x$，$a_i$ 和 $f_i$ 分别存第 $i$ 位选手吃东西的代价与第 $i$ 个食物的难吃程度。则获得以下式子：

  $$(a_i-x)\times f_i = t$$

  则有，

  $$a_i \times f_i-x\times f_i = t$$

  左右两边同时除以 $f_i$，则有，

  $$a_i - \frac{t}{f_i} = x$$

  所以得知这个人的成绩要到 $t$ 之内，需要修行 $a_i - \frac{t}{f_i}$ 次。那么这个时候，代码就很好实现了。

  ### 代码

  
```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;

int a[200005], f[200005], n, k;
bool check(int t){
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] * f[i] > t){ 
			cnt += a[i] - t / f[i]; 
		}
	}
	return (cnt <= k);
}

bool cmp(int x, int y){
	return x > y;
}

signed main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++){
		cin >> f[i];
	}
	sort(a + 1, a + n + 1);//把人从小到大，把食物从大到小
	sort(f + 1, f + n + 1, cmp); 
	int l = 0, r = 1e12;
	while(l < r){
		int mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

一道很简单的二分加贪心，但我在比赛时没过。

因为我输入错了，它竟然加上样例还有 $6$ 个点是对的，于是我查了半小时都没发现这件事，到最后只能怀疑是自己想法错了放弃。

首先二分答案 $sum$。

现在的问题是你要将 $A,F$ 数组一一对应，如果 $A_i \times F_i>sum,k=k-(A_i-sum/F_i)$，看 $k$ 最后是否小于 $0$。

然后你就会发现其实只要把 $A$ 从小到大，$F$ 从大到小排序，然后算出来的就是最优解

为什么呢？我们可以取两个数来试试。

取 $A_1$，$A_2$，$A_1<A_2$。

取 $B_1=sum/F_1$,$B_2=sum/F_2,F_1>F_2$。

减去的数很显然越小越好，所以减去的数为：

$$\min(\max(0,A_1-B_1)+\max(0,A_2-B_2),\max(0,A_1-B_2)+\max(0,A_2-B_1))$$

总共有六种情况,分别为（$T$ 为被减去的数）：

1. $A_1<A_2<B_1<B_2,T=0$

2. $A_1<B_1<A_2<B_2,T=0$

3. $B_1<A_1<A_2<B_2,T=\min(A_1-B_1,A_2-B_1)=A_1-B_1$

4. $A_1<B_1<B_2<A_2,T=\min(A_2-B_2,A_2-B_1)=A_2-B_2$

5. $B_1<A_1<B_2<A_2,T=\min(A_1-B_1+A_2-B_2,A_2-B_1)=A_1-B_1+A_2-B_2$

6. $B_1<B_2<A_1<A_2,T=A_1-B_1+A_2-B_2$

发现没有啊，都对应的啊

所以就直接贪心就好啦。

### 完整代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long ll;
int n,he;
ll a[1000009],b[1000009];
ll ans=0;
bool check(ll sum,ll k)
{
  he=1;
  for (int i=n;i>=1;i--)
  {
    if (a[he]*b[i]<=sum) {he++;continue;}
    if ((a[he]-sum/b[i])>k) return false;
    k-=a[he]-sum/b[i];
    he++;
  }
  return true;
}
int main()
{
  ll k;
  scanf("%d%lld",&n,&k);
  for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
  for (int i=1;i<=n;i++) scanf("%lld",&b[i]);
  sort(a+1,a+1+n); sort(b+1,b+1+n);
  ll l=0,r=0;
  r=b[n]*a[n];ans=r;
  while (l<=r)
  {
      ll mid=(l+r)/(ll)2;
      if (check(mid,k)) ans=mid,r=mid-1;
      else l=mid+1;
  }
  printf("%lld\n",ans);
  return 0;
}
```


---

