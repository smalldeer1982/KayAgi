# [NOISG 2018 Prelim] Snail

## 题目背景

翻译自 [NOISG 2018 Prelim A. Snail](https://github.com/noisg/sg_noi_archive/tree/master/2018_prelim)。

## 题目描述

有一只蜗牛被困在了高度为 $H$ 的井中。

这只蜗牛正在不停的尝试爬出这口井。具体来说，这只蜗牛会在一天中经历 $N$ 个阶段，阶段 $i$ 会向井口爬 $P_i$ 米（**可能为负**）。当蜗牛的高度**大于等于**井口的高度时，这只蜗牛就离开了井。当蜗牛的高度小于 $0$ 时，高度视为 $0$。

现要求你求出蜗牛最早什么时候离开井或报告无解。

**注意，天数和阶段都以 $0$ 开头，也就是说第一阶段实际上是第 $0$ 阶段。此外，你可能需要使用 `long long` 来存放输入的数字。**

## 说明/提示

### 【样例 #1 解释】
第 $0$ 天的第 $0$ 阶段，爬行 $1$ 米，共爬行 $1$ 米。

第 $1$ 天的第 $0$ 阶段，爬行 $1$ 米，共爬行 $2$ 米。

第 $2$ 天的第 $0$ 阶段，爬行 $1$ 米，共爬行 $3$ 米，离开井。

### 【样例 #2 解释】
显然，蜗牛永远无法离开。

### 【数据范围】
| Subtask | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | 样例 |
| $1$ | $11$ | $N=1$ |
| $2$ | $9$ | 所有的 $P_i$ 相同 |
| $3$ | $25$ | $H\times N \leq 10^4$ |
| $4$ | $17$ | $P_i\geq0$ |
| $5$ | $38$ | 无 |

对于 $100\%$ 的数据：$1 \leq H \leq 10^{12},-10^{12}\leq P_i\leq 10^{12},1\leq N \leq 10^4$。

## 样例 #1

### 输入

```
3 1
1```

### 输出

```
2 0```

## 样例 #2

### 输入

```
5 1
-1```

### 输出

```
-1 -1```

## 样例 #3

### 输入

```
5 2
4 -2```

### 输出

```
1 0```

# 题解

## 作者：ZMQ_Ink6556 (赞：7)

## 题解：P11296 [NOISG2018 Prelim] Snail

注意：这是一篇**非正式**做法的题解。**如果想要学习正确的解法，请移步其他题解**。

### 题外话

前一天看到这题，决定这题很有意思，作为一道橙题，它居然 AC 率不到 $2\%$，所以决定打一遍。于是加到做题计划里，今天切。打 WA 了拿到 $37$ 分之后，~~点击“查看题解”发现没有题解~~发现这题不知道什么时候升黄了。AC 后再看，这题不知道什么时候升绿了。第一次出现这么神奇的事情，写篇题解记录一下。

### 解题思路

首先，分析题意，需要我们模拟蜗牛向上爬的过程。每天有 $n$ 个阶段，每个阶段可能上升或下降。请问几天几阶段后能够爬出井。

### 第 $0$ 档部分分

样例，无需多言。

### 第 $1$ 档部分分

由于 $n = 1$，可得：

- 若 $p_0 > 0$，则 $ans = \lceil  \frac{h}{p_0} \rceil$。
- 若 $p_0 \le 0$，则 $ans = -1$。

### 第 $2$ 档部分分

考虑转换。若经过了 $x$ 个阶段，则答案为 $(\lfloor \frac{x}{n}\rfloor , x - \lfloor \frac{x}{n}\rfloor)$。此时，可以**直接转换到第二档部分分**的做法，只不过是把天换成阶段。

### 第 $4$ 档部分分

维护**前缀和**计算：

$$qzh_i = \sum_{j=0}^{i}p_i$$

此时可以快速计算出需要几个整天，然后从前到后找到第一个前缀和 $>$ 剩下的 $h$ 即为阶段的答案。

### 骗分算法 I

维护**前缀和**，找前缀和的**最小值**和**最大值**。

- 如果前缀和的最大值 $> h$，那么第一天就可以出去。
- 否则如果 $q_{n - 1} <= 0$，那么永远不能出去。
- 否则先快速计算 $\frac{h - q\text{中的最大值}}{q_{n - 1}}$，然后再暴力计算。

虽然这段代码只能拿到前面讲过的 $3$ 个部分分，但是由于后面 AC 代码要用到，所以放一下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long h , n , p[10005] , qzh[10005] , maxq , ans , pl = 1;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> h >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> p[i];
		qzh[i] = qzh[i - 1] + p[i];
		maxq = max(maxq , qzh[i]);
	}
	if(maxq < 0 || (maxq < h) && qzh[n] <= 0)
	{
		cout << "-1 -1";
		return 0;
	}
	ans = (h - maxq) / qzh[n];
	h -= ans * qzh[n];
	ans = ans * n - 1;
	while(h > 0)
	{
		h -= p[pl];
		ans++;
		pl++;
		if(pl > n)
		{
			pl = 1;
		}
	}
	cout << ans / n << ' ' << ans % n;
	return 0;
}
```

### 骗分算法 II

先跑一段暴力，找前 $100$ 天有没有答案，如果没有，那么按照上一个部分的算法跑，然后最后再跑一段暴力，如果 $5 \times 10^8$ 个阶段之内能够走出去，输出答案，否则输出 $(-1 , -1)$。得分：$80$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long h , n , p[10005] , qzh[10005] , maxq , minq , ans = -1 , pl = 1 , ch , cnt;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> h >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> p[i];
		qzh[i] = qzh[i - 1] + p[i];
		maxq = max(maxq , qzh[i]);
		minq = min(minq , qzh[i]);
	}
	ch = h;
	if(n * h <= 2000000000)
	{
		while(1)
		{
			if(h <= 0)
			{
				cout << ans / n << ' ' << ans % n;
				return 0;
			}
			h -= p[pl];
			h = min(h , ch);
			ans++;
			pl++;
			if(pl > n)
			{
				pl = 1;
			}
			cnt++;
			if(cnt > 500000000)
			{
				break;
			}
		}
		cout << "-1 -1";
		return 0;
	}
	if(qzh[n] > 0)
	{
		for(int i = 1 ; i <= n * (max(0ll , -minq) + 100) / qzh[n] ; i++)
		{
			if(h <= 0)
			{
				break;
			}
			h -= p[pl];
			h = min(h , ch);
			ans++;
			pl++;
			if(pl > n)
			{
				pl = 1;
			}
		}
	}
	for(int i = 1 ; i <= n * n ; i++)
	{
		if(h <= 0)
		{
			break;
		}
		h -= p[pl];
		h = min(h , ch);
		ans++;
		pl++;
		if(pl > n)
		{
			pl = 1;
		}
	}
	if(h > qzh[n] && qzh[n] > 0)
	{
		ans += (h - maxq) / qzh[n] * n;
		h -= (h - maxq) / qzh[n] * qzh[n];
	}
	while(h > 0)
	{
		h -= p[pl];
		ans++;
		pl++;
		if(pl > n)
		{
			pl = 1;
		}
		cnt++;
		if(cnt > 500000000)
		{
			cout << "-1 -1"; 
			return 0;
		}
	}
	cout << ans / n << ' ' << ans % n;
	return 0;
}
```

### 究极骗分：

观察 [$80$ 分记录](https://www.luogu.com.cn/record/190307681)，发现错误的点都在我们已经解决的部分分，而且都是 $-1$ 的问题。

直接特判性质，然后把 $37$ 分代码和 $80$ 分代码嫁接，得到满分的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long h , n , p[10005] , qzh[10005] , maxq , minq , ans = -1 , pl = 1 , ch , cnt;
bool samep()
{
	for(int i = 1 ; i < n ; i++)
	{
		if(p[i] != p[i + 1])
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> h >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> p[i];
		qzh[i] = qzh[i - 1] + p[i];
		maxq = max(maxq , qzh[i]);
		minq = min(minq , qzh[i]);
	}
	ch = h;
	if(n == 1 || samep())
	{
		if(maxq < 0 || (maxq < h) && qzh[n] <= 0)
		{
			cout << "-1 -1";
			return 0;
		}
	}
	if(n * h <= 2000000000)
	{
		while(1)
		{
			if(h <= 0)
			{
				cout << ans / n << ' ' << ans % n;
				return 0;
			}
			h -= p[pl];
			h = min(h , ch);
			ans++;
			pl++;
			if(pl > n)
			{
				pl = 1;
			}
			cnt++;
			if(cnt > 500000000)
			{
				break;
			}
		}
		cout << "-1 -1";
		return 0;
	}
	if(qzh[n] > 0)
	{
		for(int i = 1 ; i <= n * (max(0ll , -minq) + 100) / qzh[n] ; i++)
		{
			if(h <= 0)
			{
				break;
			}
			h -= p[pl];
			h = min(h , ch);
			ans++;
			pl++;
			if(pl > n)
			{
				pl = 1;
			}
		}
	}
	for(int i = 1 ; i <= n * n ; i++)
	{
		if(h <= 0)
		{
			break;
		}
		h -= p[pl];
		h = min(h , ch);
		ans++;
		pl++;
		if(pl > n)
		{
			pl = 1;
		}
	}
	if(h > qzh[n] && qzh[n] > 0)
	{
		ans += (h - maxq) / qzh[n] * n;
		h -= (h - maxq) / qzh[n] * qzh[n];
	}
	while(h > 0)
	{
		h -= p[pl];
		ans++;
		pl++;
		if(pl > n)
		{
			pl = 1;
		}
		cnt++;
		if(cnt > 500000000)
		{
			cout << "-1 -1"; 
			return 0;
		}
	}
	cout << ans / n << ' ' << ans % n;
	return 0;
}
```

欢迎大家来 hack！此代码不保证正确性，如果你找到了一组 hack，请给此题解点个赞，并将 hack 放在评论区。如果我看到了，就会回来更新题解。

---

## 作者：MaiJingYao666 (赞：3)

# P11296 题解
有幸见证这道题黄升绿，说实话也配得上。  
一开始，很自信地数学枚举，但忽略了一个重点条件：“**当蜗牛的高度小于 0 时，高度视为 0**”。
***
### 题目翻译  
形如经典蜗牛爬井问题，但是蜗牛每天的动作多了**亿**点。问你在第几天第几个动作可以爬出井。
***
### 解题思路  
正如楼上题解，本人确实是 37 分军团的前队员 ~~（成功贡献 5 次）~~，但貌似楼上没有详细讲为什么要枚举 2 天，来锁定每一次每一个操作的**具体变化值**。  

情况1：$\sum^{n}_{i=1}p_i \ge 0$，则对于一个负数 $p_k$，$\sum^{k-1}_{i=1}p_i + \sum^{n}_{i=k+1}p_i \ge -p_k$，因此到了第 2 天的该位置，它不会被上文提到条件而改变实际改变值。

情况2：$\sum^{n}_{i=1}p_i \le 0$，这个就更好说了，无论如何也跳不上去，那也是 2 次就够了。  

再举几个例子：  
|天数|操作 1|操作 2|操作 3|操作 4|操作 5|操作 6|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**0**|1|3|-5|2|-3|3|
|**1**|1|4|0|2|0|3|
|**2**|4|8|3|5|2|5|
|**3**|6|9|4|6|3|6|
|**4**|7|10|5|7|4|7|
|……|……|……|……|……|……|……|

发现第二天及之后每天的**具体变化值**是固定的，如果在前两次就到了，直接输出，否则也只用先算出每天的变化量，用个简单的枚举和除法就可以确定是第几天和第几个部分了。

再考虑一种情况：  
当数列之和为非正数时，比如

|天数|操作1|操作2|操作3|操作4|
|:-:|:-:|:-:|:-:|:-:|
|**0**|1|-3|-2|4|
|**1**|1|0|0|4|
|**2**|5|2|0|4|
|**3**|5|2|0|4|
|……|……|……|……|……|……|……|
 
序列会在第二天及以后会基本固定住，所以当当前还没有到达高度 $H$，就证明无解了。
***
接下来处理好细节，比如 0 开始之类的。  
接下来奉上代码。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
__int128 read(){//作者太气了，其实long long就行
	__int128 res=0;
	char scan[1005];
	scanf("%s",scan);
	int idx=(scan[0]=='-'?1:0);
	for(int i=idx;i<strlen(scan);i++){
		res*=10;
		if(idx==1)res-=scan[i]-'0';
		else res+=scan[i]-'0';
	}
	return res;
}
void print(__int128 num){
	if(num<0){
		cout<<'-';
		num=-num;
	}
	if(num>9){
		print(num/10);
	}
	putchar(num%10+'0');
}
__int128 a[10005],b[20005];
long long h,n;
int main(){
	h=read(),n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	b[1]=0;
	for(int i=1;i<=2*n;i++){
		b[i+1]=b[i]+a[(i%n==0?n:i%n)];//伪前缀和处理具体变化量
		b[i+1]=max(b[i+1],(__int128)0);//处理掉到底
		if(b[i+1]>=h){//现在就可以
			cout<<(i-1)/n<<" "<<(i%n==0?n-1:i%n-1);
			return 0;
		}
	}
	__int128 tmp=0;//记录每天增长值
	for(int i=1;i<=n;i++){
		tmp+=a[i];
		if(tmp<=-h){//降到极限低度
			cout<<-1<<" "<<-1<<endl;
			return 0;
		}
	}
	if(tmp<=0){//非正增长值
		cout<<-1<<" "<<-1;
		return 0;
	}
	__int128 d=1e27,p,dd;
	for(int i=1;i<=n;i++){
		dd=(h-b[n+i+1]+tmp-1)/tmp;//向上取整
		if(dd<d){
			d=dd;
			p=i;
		}
	}
	print(d+1);
	cout<<" ";
	print(p-1);
}
```

---

## 作者：ToastBread (赞：3)

翻译自官方题解。

如果你爆 $37$ 分了，那么很可能是因为你枚举的时候不到位。

基本的思路是小学奥数：求出一天上滑的量，然后计算天数即可。最后一天加上去超过没加上去又没到井口的部分暴力求解即可。

**注意 $P_i$ 可能为负，也就是说，你枚举时必须枚举两天的量**。

感性理解：可能是 $-x,x$ 这种操作类型。

第一天上去了 $x$，第二天先回到 $0$ 然后再到 $x$。这种情况下如果 $H>x$ 则无解。

参考代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <assert.h>
#define INF 1012345678012345678LL
#define BIG 1000000000000LL
using namespace std;
typedef long long ll;
ll H;
int N;
ll P[10010];
ll simulate[20010]; // 是 P_i
ll increment = 0; // increment 增量，每次增长多少
bool printed = 0;
int main(void) {
    scanf("%lld%d", &H, &N);
    assert(1<=H && H<=BIG);
    assert(1<=N && N<=10000);//防君子不防小人
    for (int i=0;i<N;i++) {
        scanf("%lld", &P[i]);
        assert(-BIG<=P[i] && P[i]<=BIG);
    }
    // **模拟 2 天**
    simulate[0] = 0;
    for (int i=0;i<2*N;i++) { // 你可能忘记它而爆 37 pts
        simulate[i+1] = max(simulate[i]+P[i%N], 0LL); // 记得取 max
        if (simulate[i+1] >= H) { // 第一次就超过了
            printf("%d %d\n", i/N, i%N);
            printed = 1;
            break;
        }
    }
    if (!printed) {
        for (int i=0;i<N;i++) {
            increment += P[i]; // 可能向下到负数
            // 如果真到了呢？
            if (increment <= -H) { // 不可能的
                printf("-1 -1\n");
                printed = true;
                break;
            }
        }
    }
    if (!printed) {
        // 每天退步一点点
        if (increment <= 0) {
            // 那就不用爬了
            printf("-1 -1\n");
            printed = true;
        } else {
            ll bestDays = INF;
            int phase = 0;
            for (int i=0;i<N;i++) {
                ll days = 1+(H-simulate[N+i+1]+increment-1)/increment;
                if (bestDays > days) {
                    bestDays = days;
                    phase = i;
                }
            }
            printf("%lld %d\n", bestDays, phase);
            printed = true;
        }
    }
    return 0;
}

---

## 作者：ftzx (赞：2)

# [题目链接](https://www.luogu.com.cn/problem/P11296)
# 分析
很巧妙的一道题，细节也很多。  
事先说明：$h$、$p$、$n$ 与题目意思相同，$sum$ 表示每天总位移。  
不妨考虑下面情况：
~~~
5 2
6 -4
~~~
此时为直接枚举每天爬行。


注意：不能通过计算 $sum$ 通过直接 $h \div sum$ 来计算天数。  
因为在这种情况下，可能因为先前爬出去了后面又退回来。


那如何解决呢？


不妨通过枚举前 $2$ 天的位移，在这里我们定义 $i$ 为第 $i$ 个阶段（总的）  
$mn[i]$ 来表示在第 $i$ 天前的总位移。  
那么我们可以推出 
$$mn[i+1]=mn[i] + p[i]$$
但此时要注意 $p[i]$ 有可能为负，倒退回原点甚至更远，且 $0 \le i < 2 \times n$。  
所以应该改为 
$$mn[i+1] = \max(mn[i]+p[i],0)$$  
接下来就是简单的模拟实现了。  
# 实现
具体内容都在注释，不过多赘述。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=9223372036854775807;
ll h,n,p[10005],sum,mn[20005];
int main(){
	cin>>h>>n;
	for(int i=0;i<n;i++){
		cin>>p[i];
		sum+=p[i];//统计一天内总位移
	}
	//mn[i]指在第i次操作时之前的总位移 
	for(int i=0;i<2*n;i++){//枚举前两天的操作数 
		mn[i+1]=max(mn[i]+p[i%n],0LL);//第i+1次操作时之前的总位移 
		if(mn[i+1]>=h){
			cout<<i/n<<' '<<i%n;//第i/n天，第i%n阶段
			return 0; 
		} 
	}
  //在此时判断是否一天的位移为负数
  //因为会出现走出去后又走回去导致无法出去的情况
  //而在第一天内就会走出去的情况在46行实现
	if(sum<=0){
		cout<<"-1 -1";
		return 0;
	}
  //模拟爬行
	ll ansday=INF,jieduan=0;
	for(int i=0;i<n;i++){
		ll days=1+(h-mn[n+i+1]+sum-1)/sum;//计算
		if(ansday>days){
			ansday=days;
			jieduan=i;
		}
	}
	cout<<ansday<<' '<<jieduan;
	return 0;
}
```
蒟蒻第一次写题解，求过求过求过 Orz。

---

## 作者：A_small_WA (赞：2)

用了[2周的时间](https://www.luogu.com.cn/record/list?pid=P11296&user=1124323)，在官解读不懂，另一篇题解太复杂的情况下终于自力更生写出了这题。现在用比较通俗的思路带各位理一下做法。

第一眼看到这一题认为很简单。只用把每天的增加量 `sum` 算出来即可，用 $H\div sum$ 得到大概爬上去的时间（天数）和爬的距离，再直接模拟前后几天即可。注意当 $sum\le0$ 且第一天没爬上去时就不可能爬上去了。可是这种思路写出来的代码只有[26分](https://www.luogu.com.cn/record/192068769)。

于是开始重新审题，突然你发现了这样一句话：**当蜗牛的高度小于 $0$ 时，高度视为 $0$。**

然后考虑到前几天内存在高度小于 $0$ 的情况，必须把蜗牛高度 `nw` 和每天增加量 `sum` 分开算。等有一天（第 `day` 天）中每一阶段蜗牛高度都大于等于 $0$ 后再用公式计算，从这一天起，增加量是有效的。（不然爬的时候小于 $0$ 的部分会被抵消）。

具体地，蜗牛剩余攀爬距离（离井口的距离）为 $H-nw$；剩余攀爬天数**大约**为 $(H-nw)\div sum$；总攀爬天数大约为 $(H-nw)\div sum+day$；已攀爬距离为 $((H-nw)\div sum)\times sum+nw$。以上所有除法均为 C++ 中均为向下取整。再从总攀爬天数开始模拟即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10005;
long long p[N];
int main(){
	long long h,n,sum=0,nw=0,day=0,bj=1;
	cin>>h>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
		sum+=p[i];
	}
	while(bj==1){
	    bj=0;
		for(int i=1;i<=n;i++){
			nw+=p[i];
			if(nw<0){
				nw=0;
				bj=1;
                //记录是否有高度小于0的阶段。
			}
			if(nw>=h){
				cout<<day<<" "<<i-1;
				return 0;
			}
        //爬到就直接输出并结束。
		}
		if(sum<=0){
			cout<<-1<<" "<<-1;
			return 0;
		}
        //不可能爬上。
		day++;
	}
	long long w=(h-nw)/sum-1,k=nw+(w)*sum;
    //天数和阶段都从零开始，记得-1！
	w=w+day;
	for(int i=1;i<=n;i++){
		k+=p[i];
		if(k>=h){
			cout<<w<<" "<<i-1;
			return 0;
		}
	}
	w++;
	for(int i=1;i<=n;i++){
		k+=p[i];
		if(k>=h){
			cout<<w<<" "<<i-1;
			return 0;
		}
	}
}
```

正当我以为又水了一道绿题时，只有[37分](https://www.luogu.com.cn/record/192076927)，我气愤地下载了 #16 测试点数据，得到：

in:
```
1000 10
1 -2 3 -4 5 -6 7 -8 9 -4
```

out:`991 8`

发现蜗牛在一天中的某个阶段时可能突然爬的很高然后再落下来，这样我们的增加量计算方法就不管用了。为了应对这种情况，可以再采用一个变量 `mx` 表示一天中爬的最高的高度。则天数计算公式改为：$(H-nw-mx)\div sum$。其他公式也要对应改变。

再交：[还是37分](https://www.luogu.com.cn/record/191930772)。被迫下载 #20 测试点的测试数据：

in:
```
10 10
1 1 1 1 1 1 1 1 -100 2
```

out:
`1 7`

又恍然大悟了。像官解里说的，要模拟前两天，所以即使 $sum\le0$ 蜗牛也可能爬上去。把代码中的 `if(sum<=0)` 改成 `if(sum<=0&&day>=1)`。

再交：[38分](https://www.luogu.com.cn/record/191932170)。

发现 RE 报错信号为除数为 $0$。检查出这种写法可能会让 $sum=0$ 的情况跑出 `while` 循环。把 `if(sum<=0&&day>=1)` 再改成 `if(sum<0&&day>=1||sum==0)` 即可 [AC](https://www.luogu.com.cn/record/192067213)。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10005;
long long p[N];
int main(){
	long long h,n,sum=0,nw=0,mx=-1e18,day=0,bj=1;
	cin>>h>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
		sum+=p[i];
		mx=max(mx,sum);
	}
	while(bj==1){
	    bj=0;
		for(int i=1;i<=n;i++){
			nw+=p[i];
			if(nw<0){
				nw=0;
				bj=1;
			}
			if(nw>=h){
				cout<<day<<" "<<i-1;
				return 0;
			}
		}
		if(sum==0) {
			cout<<-1<<" "<<-1;
			return 0;
		}
		if(sum<0&&day>1){
			cout<<-1<<" "<<-1;
			return 0;
		}
		day++;
	}
	long long w=(h-nw-mx)/sum-1,k=nw+(w)*sum;
	w=w+day;
	for(int i=1;i<=n;i++){
		k+=p[i];
		if(k>=h){
			cout<<w<<" "<<i-1;
			return 0;
		}
	}
	w++;
	for(int i=1;i<=n;i++){
		k+=p[i];
		if(k>=h){
			cout<<w<<" "<<i-1;
			return 0;
		}
	}
	w++;
	for(int i=1;i<=n;i++){
		k+=p[i];
		if(k>=h){
			cout<<w<<" "<<i-1;
			return 0;
		}
	}
	return 0;
}
//前面说的已经很详细了，就不打注释了。
```

最后，这道题的细节还是蛮多的，需要细心和耐心，有任何错误请私信我。

这是本蒟蒻的第 $14$ 篇题解，感谢观看。

---

## 作者：DeepSleep_Zzz (赞：1)

**begin**

[P11296 题目传送门](https://www.luogu.com.cn/problem/P11296)

# 前言
这是一道细节贼多的模拟+数学题。

虽然这道题看起来人畜无害，像个小学数学题，但是你大抵是忽略了一句话：

>**当蜗牛的高度小于 $0$ 时，高度视为 $0$。**

如果你一直 37pts 那么不要怀疑，就是这句话造的孽。

# 分析
我们来仔细考虑一下题目中这句话，很容易发现，$h_{\texttt {snail}}<0$ 的情况只会出现在前两天。

所以我们考虑先暴力枚举前两天，然后再算出在第几天完成，再枚举阶段。

但是蜗牛有可能在一天内爬得很高然后又掉下来。我们为了应对这种情况，我们可以用一个 $maxp$ 来记录一天中爬的最高点，在计算天数时把它减掉，保证天数的正确性。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll h,n,p[10010],sum,now,ans,maxp=-2e12;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>h>>n;
    for (ll i=1;i<=n;i++)
    {
        cin>>p[i];
        sum+=p[i];
        maxp=max(maxp,sum);
    }
    for (ll i=1;i<=2;i++)
    {
        for (ll j=1;j<=n;j++)
        {
            now=max(0LL,now+p[j]);
            if (now>=h)
            {
                cout<<i-1<<" "<<j-1;
                return 0;
            }
        }
    }
    if (sum<=0)
    {
        cout<<"-1 -1";
        return 0;
    }
    h-=now;
    ans=(h-maxp)/sum+2;
    h-=(h-maxp)/sum*sum;
    for (ll i=ans+1;i<=ans+2;i++)
    {
        for (ll j=1;j<=n;j++)
        {
            h-=p[j];
            if (h<=0)
            {
                cout<<i-1<<" "<<j-1;
                return 0;
            }
        }
    }
    return 0;
}
```
**end**

---

## 作者：fengyaun (赞：1)

## [P11296 NOISG2018 Prelim Snail](https://www.luogu.com.cn/problem/P11296)

### 前言

这是一道非常好的模拟 / 贪心题， 适合练细节。

### 分析

该题恶心的一点其实在于:当蜗牛高度小于等于 $0$ 时，高度视为 $0$ ，那么这就不是一道小学奥数题了。

但分析一下，只要我们暴力模拟两次即可，因为对于高度小于等于 $0$ 的情况，显然只能对第一次产生影响，若对第二次仍有影响，那么蜗牛的每天攀爬和为负，即无解。

剩下的就是对于总攀爬高度除一下每日攀爬高度再处理一下余数即可。

其他细节诸如下标从 $0$ 开始，需使用 `long long` 等。

### 实现

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

long long h, n;

long long Max;

long long answer;

long long p[N];

long long pre[N];

signed main()
{
    cin >> h >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
        pre[i] = p[i] + (i == 0 ? 0 : pre[i - 1]);
        Max = max(Max, pre[i]);
    }
    long long now = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            now = max((long long)(0), now + p[j]);
            if (now >= h)
            {
                cout << i << " " << j;
                return 0;
            }
        }
    }
    if (pre[n - 1] <= 0)
    {
        cout << -1 << " " << -1;
        return 0;
    } 
    h -= now;
    answer = 1;
    answer += (h - Max) / pre[n - 1];
    h -= ((h - Max) / pre[n - 1]) * pre[n - 1];
    for (int i = answer + 1; ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            h -= p[j];
            if (h <= 0)
            {
                cout << i << " " << j;
                return 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：Herman526 (赞：1)

为了方便，我们将第 $i$ 天第 $j$ 个阶段称为第 $(iN+j)$ 个**时间段**（天数和阶段仍以 $0$ 开始，与题目保持一致），而第 $-1$ 个时间段则表示未开始爬行。此外，我们假设 $P_{iN+j}=P_j$（因为每天的第 $j$ 个阶段都是爬 $P_j$ 这么高）。

要判断什么时候蜗牛能爬出井，就得计算它经过每个时间段后，爬的高度是多少。我们设 $f_i$ 表示经过第 $i$ 个时间段后蜗牛的高度。由于**当蜗牛高度为负时，其高度为 $0$**，我们可以推出这样的转移方程：
$$f_i=\begin{cases}0&i=-1\\\max\{f_{i-1}+P_i,0\}&i⩾0\end{cases}$$
对上面的转移方程进行转化，可以得到：
$$f_i=\max\{\max_{0⩽j⩽i}\{∑_{k=j}^iP_k\},0\}(i⩾0)$$
简单证明一下这个结论：
- 当 $i=0$ 时，结论显然成立；
- 当 $i>0$ 时，假设结论对于 $i-1$ 成立，即 $f_{i-1}=\max\{\max\limits_{0⩽j⩽i-1}\{∑\limits_{k=j}^{i-1}P_k\},0\}$。又由于 $f_i=\max\{f_{i-1}+P_i,0\}$，那么
$$\begin{aligned}f_i=&\max\{P_i+\max\{\max\limits_{0⩽j⩽i-1}\{∑\limits_{k=j}^{i-1}P_k\},0\},0\}\\=&\max\{\max\{\max\limits_{0⩽j⩽i-1}\{P_i+∑\limits_{k=j}^{i-1}P_k\},P_i\},0\}\\=&\max\{\max\{\max\limits_{0⩽j⩽i-1}\{∑\limits_{k=j}^iP_k\},P_i\},0\}\\=&\max\{\max_{0⩽j⩽i}\{∑_{k=j}^iP_k\},0\}\end{aligned}$$
综上，结论得证。也就是说，当 $i⩾0$ 时，$f_i$ 其实就是选一个左端点 $l$，求出 $P$ 序列中区间 $[l,i]$ 内数和的最大值，再与 $0$ 取 $\max$。由于 $0<H$，所以你也可以将这个 $0$ 弃之不理，因为它不会对蜗牛爬出井的时间产生影响 **（后续的讨论也有部分在此前提下）**。将 $f_i$ 的定义转化以后，我们只要对爬出井的天数 $D$ 进行分类讨论即可：
- 若 $D=0$，我们可以对于每个 $0⩽i⩽N-1$ 暴力预处理出 $f_i$ 的值，并从小到大枚举 $i$，**一旦发现某个 $f_i⩾H$，就直接输出 $i$ 并退出**；
- 若 $D=1$，我们可以对于每个 $0⩽i⩽N-1$ 算出 $s_i=∑\limits_{j=0}^iP_i$ 的值，也即 $P$ 的前缀和。由于 $D=0$ 不满足条件，那么对于每个 $0⩽i⩽N-1$，$f_{N+i}$ 都一定等于 $f_{N-1}+s_i$（即 $P$ 的最大后缀和加上第 $1$ 天第 $0∼i$ 阶段爬行的高度）。判断是否有解时，可使用与上面类似的方法 **（有解直接退出）**；
- 若 $D⩾2$ **且 $s_{N-1}$ 为正**，且第 $0∼(D-1)$ 天内无法爬完，由于 $f$ 又可以转化为最大后缀和的形式，那么可以将蜗牛的爬行分为 $3$ 段：第 $0$ 天爬的 $f_{N-1}$，第 $1∼(D-1)$ 天内爬的 $s_{N-1}$ 及第 $D$ 天内爬的 $s_i$（其中 $i$ 为蜗牛爬出井时所在的阶段编号）。这样一来，$f_{DN+i}$ 就等于 $f_{N-1}+(D-1)s_{N-1}+s_i$。像上面一样，我们还是对于每个 $0⩽i⩽N-1$ 都算出 $D$ 的最小值。具体地，因为 $f_{N-1}+(D-1)s_{N-1}+s_i⩾H$，所以 $D⩾⌈\frac{H-f_{N-1}-s_i}{s_{N-1}}⌉+1$。我们只要对这些式子取最小值即可（还要记录最小值对应的 $i$）。

到了这里，我们还可以证明如下结论：当 $s_{N-1}⩽0$ 且在第 $0$ 或 $1$ 天蜗牛均爬不出井时，蜗牛永远也爬不出井。因为在 $D⩾2$ 且阶段为 $i$，且必须到该时间段才能爬出井时，蜗牛爬的高度为 $f_{N-1}+(D-1)s_{N-1}+s_i$，而既然在第 $1$ 天内爬不出井，那么 $f_{N-1}+s_i<H$。但这里的 $D-1>0$，$s_{N-1}⩽0$，所以 $f_{N-1}+(D-1)s_{N-1}+s_i$ 也会小于 $H$，爬不出井。因此，我们还要对这种情况进行特判。

经过上面的分类讨论，我们得到了一个时空复杂度均为 $O(N)$ 的做法。
```c++
#import<ios>
int n,i,g;long long h,u,v,f=1e18,w,x[10000],a[10000],s[10000];
main(){
	for(scanf("%lld%d",&h,&n);i^n;a[i]=std::max(0ll,x[i]+a[i-1]),s[i]=x[i]+s[i-1],++i)
		scanf("%lld",x+i);
	for(i=0;i^n;++i)if(h<=a[i])printf("0 %d",i),exit(0);//第 0 天
	for(i=0,u=a[n-1];i^n;++i)if(h<=u+s[i])printf("1 %d",i),exit(0);//第 1 天
	if(v=s[n-1],v<=0)puts("-1 -1"),exit(0);//特判
	for(i=0;i^n;++i)if(f>(w=(h-u-s[i]+v-1)/v))f=w,g=i;//第 ⩾2 天
	printf("%lld %d",f+1,g);
}
```

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：P11296 [NOISG2018 Prelim] Snail
## 思路：
首先要需要一个变量 $z$，记录当前蜗牛的位置，简单 for 循环使 $z$ 加上当前的 $P_i$，注意，当蜗牛高度为负数时，需将蜗牛高度 $z$ 清零。  
### 此步骤代码

```cpp
for(int i=0;i<q;i++){
	for(int j=0;j<n;j++){
		z+=a[j];
		if(t<=0){
          z=0;
        }
    }
}
```
之后要判断蜗牛高度是否到达井的高度，如果到达，则输出就行了，如果一定时间内并没要到达井的高度，则输出 "-1 -1"。
### 此步骤代码

```cpp
if(z>=h){
  cout<<i<<" "<<j;
  return 0;
}
```
## 注意：
- 要输出的是 $i$，$j$ 并不是 $i+1$，$j+1$。
- 你可能需要使用 long long 来存放输入的数字。
#### 此题比较水，就不给完整代码了

---

## 作者：ben090302 (赞：0)

这题并不是小学数学题。

一个思路是先跑出一天的净上升量，二分天数暴力检验最后一天，但是这样是错误的。

一种情况需要注意：第一天走着走着**触底了**也就是和 $0$ 取了个 $\max$，然后第一天没有上去最后停在了某一个高度，第二天继续走还是**触底**然后也没上去最后会卡在跟第一天一样的地方然后无解。

这个情况告诉我们，我们实际上要需要的不是第一天的净上升量，二十第一个不触底的一天的。

考虑假如第二天和第一天的停止位置相同而且都没有上去，那就无解了，否则前两天要么已经上去了要么第二天没有触底。于是我们要枚举模拟前两天然后判断无解然后二分可以解决后续。

需要注意我的这种写法依赖于 `int128`。

```
#include<bits/stdc++.h>
#define int long long
#define fk __int128
using namespace std;
const int N=1e4+5;
int H,n;
int P[N];
fk up;
fk PP;

bool check(int D){
	fk pos=PP;
	pos+=(D-1)*up;
	for(int i=1;i<=n;i++){
		pos=pos+P[i];
		if(pos>=H) return 1;
	}
	return 0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>H>>n;
	for(int i=1;i<=n;i++) cin>>P[i];
	fk pos=0;
	for(int i=1;i<=n;i++){
		pos=pos+P[i];
		pos=max(pos,(fk)0);
		if(pos>=H){
			cout<<0<<" "<<i-1;
			return 0;
		}
 	}
	fk ppos=pos;
	for(int i=1;i<=n;i++){
		pos=pos+P[i];
		pos=max(pos,(fk)0);
		if(pos>=H){
			cout<<1<<" "<<i-1;
			return 0;
		}
	}
	if(pos==ppos){
		cout<<"-1 -1";
		return 0;
	}
	up=pos-ppos;
	PP=pos;
	fk l=1,r=H;
	int ans_D=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;
			ans_D=mid+1;
		}else l=mid+1;
	}
	cout<<ans_D<<" ";
	pos=PP;
	pos+=(ans_D-2)*up;
	for(int i=1;i<=n;i++){
		pos=pos+P[i];
		if(pos>=H){
			cout<<i-1;
			return 0;
		}
	}
}
```

---

