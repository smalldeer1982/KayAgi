# Equalize the Array

## 题目描述

Polycarp was gifted an array $ a $ of length $ n $ . Polycarp considers an array beautiful if there exists a number $ C $ , such that each number in the array occurs either zero or $ C $ times. Polycarp wants to remove some elements from the array $ a $ to make it beautiful.

For example, if $ n=6 $ and $ a = [1, 3, 2, 1, 4, 2] $ , then the following options are possible to make the array $ a $ array beautiful:

- Polycarp removes elements at positions $ 2 $ and $ 5 $ , array $ a $ becomes equal to $ [1, 2, 1, 2] $ ;
- Polycarp removes elements at positions $ 1 $ and $ 6 $ , array $ a $ becomes equal to $ [3, 2, 1, 4] $ ;
- Polycarp removes elements at positions $ 1, 2 $ and $ 6 $ , array $ a $ becomes equal to $ [2, 1, 4] $ ;

Help Polycarp determine the minimum number of elements to remove from the array $ a $ to make it beautiful.

## 样例 #1

### 输入

```
3
6
1 3 2 1 4 2
4
100 100 4 100
8
1 2 3 3 3 2 6 6```

### 输出

```
2
1
2```

# 题解

## 作者：Frather_ (赞：10)

[~~无良商家推送blog~~这里阅读效果更佳](https://www.cnblogs.com/Frather/p/14430746.html)

# **题意**

[二次元跨界量子超级传送门](https://www.luogu.com.cn/problem/CF1490F)

~~二次元来了！快跑！~~

一天，雷姆姐姐在修剪花园。罗兹沃尔的花园非常豪华，而且都是由雷姆姐姐一手操办。傲娇~（不是

但是罗兹沃尔的强迫症又犯了，他不希望自己花园非常的凌乱，他希望自己花园中不同种类的花数目相同，所以安排雷姆姐姐帮他处理花园中的花。

然鹅雷姆姐姐每天都要~~和你玩耍~~努力工作，非常劳累，热心肠的你决定帮助她。

你可以帮雷姆把多余的花剪走，使得最后花园中不同种类的花数目相同。

问达成目的最少的操作数。

~~话说这样的题面你们不喜欢么。。。那还不赶紧点赞~~

# **解析**

显然是要寻找一条界限，使得**界限以上的不同元素出现次数相等**，**界限一下的元素删至数目为零**，直接枚举寻找这条界线就好了。

可以考虑对元素数据进行离散化，然后桶排序，将各个元素出现的次数记录到几个 $bkt[i] \  ( bucket )$ 里，然后可以进行两种操作：

+ 判断在界限以上的元素数目删除到界限值

+ 判断在界限一下的元素数目直接清除，也就是删除到 $0$ 。

然而直接挨个删除元素会超时，考虑如何进行优化。

不都已经把各种元素出现次数统计下来了吗，事先处理前缀和不就好了嘛~

所以删除次数显然易见：

+ 界限以上的元素所需的删除次数就是前缀和

+ 界限一下的元素删除次数是用前缀和减去这些元素的个数 $\times$ 界限值

# **你们最爱的环节**

```cpp
/*

Name: CF1490F Equalize the Array

By Frather_

*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

#define InF 0x3f3f3f3f

using namespace std;
/*=========================================快读*/
int read() //快读不解释
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
/*=====================================定义变量*/
int T;

int n;
int a[300030], a_[300030];

int n_; //记录界限值

int bkt[300030];
int sum[300030]; //记录前缀和

int ans[300030], ans_[300030];
int res = InF; //最终结果
/*====================== =============自定义函数*/
void prepare() //多组数据，清空变量
{
    n = 0;
    memset(ans, 0x3f, sizeof(ans));
    memset(ans_, 0x3f, sizeof(ans_));
    n_ = 0;
    memset(bkt, 0, sizeof(bkt));
    memset(sum, 0, sizeof(sum));
    res = InF;
}
/*=======================================主函数*/
int main()
{
    T = read();
    while (T--)
    {
        prepare();

        n = read();
        for (int i = 1; i <= n; i++) //读入数据，动态复制一组数据，利于下面的离散化
        {
            a[i] = read();
            a_[i] = a[i];
        }

        sort(a_ + 1, a_ + n + 1);

        n_ = unique(a_ + 1, a_ + n + 1) - a_ - 1;

        for (int i = 1; i <= n; i++) //离散化没什么解释的
            a[i] = lower_bound(a_ + 1, a_ + n_ + 1, a[i]) - a_;
        for (int i = 1; i <= n; i++) //桶排序记录元素出现次数
            bkt[a[i]]++;

        sort(bkt + 1, bkt + n_ + 1);

        for (int i = 1; i <= n_; i++)
            sum[i] = sum[i - 1] + bkt[i];
        for (int i = 1; i <= n; i++)
        {
            int t = lower_bound(bkt + 1, bkt + n_ + 1, i) - bkt;
            if (t > n_) //界限以上
                ans[i] = sum[n_];
            if (t < n_) //界限一下
                ans_[i] = sum[t - 1] + sum[n_] - sum[t - 1] - (n_ - t + 1) * i;
        }

        for (int i = 1; i <= n; i++) //统计答案
            res = min(res, min(ans[i], ans_[i]));
        printf("%d\n", res);
    }
    return 0;
}
```

# **友情提示**

$$多组数据一定要记得清空变量！！！$$

$$多组数据一定要记得清空变量！！！$$

$$多组数据一定要记得清空变量！！！$$

~~别问我为什么这么说。。。有苦有泪我不说~~

---

## 作者：DarkShadow (赞：5)

# CF1490F（枚举、前缀和）

## 题目大意：

给出 $N$ 个数，求最少删除多少个数是剩下的数出现次数相等。

## 思路分析：

首先可以想到暴力枚举剩下数的出现次数，每次 $O(N)$ 计算答案，出现次数在当前次数以下的数直接全部删掉，出现次数在当前次数以上的数就删到当前枚举的次数。同时由于数的范围很大，需要离散化后计算答案。

这种做法时间复杂度为 $O(NM)$ ，其中 $M$ 为离散化后数的值域，会 TLE。

考虑优化，因为我们每次都算的是一些不连续的数的和，我们可以把出现次数排序后用前缀和来快速计算答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/kqwu1jam.png)

设枚举的是第 $i$ 个数，前半部分答案就等于前 $i-1$ 个数的前缀和，后半部分答案就等于第 $i$ 个数到第 $M$ 个数的和，最后将两部分答案加起来就可以了。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200005;
int T,n,m,d[N],d1[N],num[N],pre[N];
int main(){
	scanf("%d",&T);
	int ans;
	while(T--){
		memset(num,0,sizeof(num));//多组数据记得清空
		ans=0x7fffffff;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&d[i]);
			d1[i]=d[i];
		}
		sort(d1+1,d1+1+n);
		m=unique(d1+1,d1+1+n)-(d1+1);//离散化
		for(int i=1;i<=n;i++)
			num[lower_bound(d1+1,d1+1+m,d[i])-d1]++;
		sort(num+1,num+1+m);
		for(int i=1;i<=m;i++)
			pre[i]=pre[i-1]+num[i];//计算前缀和
		for(int i=0;i<=m;i++)
			ans=min(ans,pre[i]+pre[m]-pre[i]-(m-i)*num[i+1]);//计算答案
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：二gou子 (赞：5)

## 题目大意

给出一个数列，将每一个数的出现次数变为$0$或$C$，其中$C$是一个任意正整数，每次操作可以删除一个数，问最少操作次数。

## 思路

首先肯定要开桶统计每个数的个数，但是注意到数列内的数范围较大，所以要先进行离散化。离散化之后开桶记录每个数的出现次数，则次数又构成了一个新的序列。这样问题就转化为：给出一个序列，对于序列中的每一个数，如果大于等于$C$，就变成$C$；反之，变成$0$。每次操作可以将任意一个数减$1$，求最小操作数。

我们这样思考：首先假设我们把所有的数都变成$0$，那其实也就是删掉原数列内的所有数，操作次数就是$n$。然后枚举$C$，小于$C$的数还是变成$0$不变，而大于等于$C$的数就要变成$C$。这些数原先要变成$0$，但是现在变成$C$。**相当于在$n$的基础上，节省了大于等于$C$的数的个数\*$C$次操作**。这样我们只需要枚举一下$C$，$O(1)$更新一下答案，这个题就做完了。

## Code
```C++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#define ll long long
using namespace std;
int t,n,maxx,p;
int a[2000005],b[2000005],sum[2000005];
ll summ,ans;
void lisan(){
	for(int i=1;i<=n;i++){
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	p=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+1+p,a[i])-b;
	}
}
int main()
{
	scanf("%d",&t);
	while(t--){
		summ=0,maxx=0,ans=1000000000000000;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		lisan();
		for(int i=1;i<=n;i++){
			sum[a[i]]++;
			maxx=max(maxx,sum[a[i]]);
//			printf("%d ",a[i]);
		}
		sort(sum+1,sum+1+p);
//		for(int i=1;i<=p;i++){
//			printf("%d ",sum[i]);
//		}
//		printf("\n");
//		printf("\n");
		for(int i=1;i<=p;i++){
			ans=min(ans,n-1ll*sum[i]*(p-i+1));
			while(sum[i]==sum[i+1]) i++;
		}
		printf("%d\n",ans);
		for(int i=1;i<=p;i++){
			sum[i]=0;
		}
	}
	return 0;
}

```
（由于$Div3$时间较紧，代码比较混乱，但思路才是主要的）

---

## 作者：_masppy_ (赞：2)

### 前言
[题目传送门](https://www.luogu.com.cn/problem/CF1490F)

&nbsp;

### 题目简述
给定一个序列，求最少从序列中删去几个数才能使序列中不同元素的出现次数相同。

~~简洁的题面，这使我的屁股脱落~~

&nbsp;

### 解题思路
首先记录每种数字在序列中出现了几次，设为 $ncnt$，每次找到新出现的元素就将 $ncnt$ 往后推一个，而出现之前有的元素就将相应的 $ncnt_i+1$。

然后，记录出现 $i$ 次的元素有多少种，记为数组 $aw$。

接着，设一个二维数组 $sum_{i,0/1}$，$sum_{i,0}$ 表示出现次数小于等于 $i$ 次的元素有多少种，$sum_{i,1}$ 则表示出现次数小于等于 $i$ 次的元素有多少个。

记录完这些，对于使序列中每个数都出现 $i$ 次所需要删除的元素个数，我们就可以推出一个非常奇怪的式子。

$$ans_i=sum_{i-1,1}+sum_{mx,1}-sum_{i,1}-sum_{mx,0}\times i+sum_{i,0}\times i$$

解释一下，$mx$ 表示一种元素最多出现几次，$sum_{i-1,1}+sum_{mx,1}-sum_{i,1}$ 表示将除了出现 $i$ 次的元素都删除，$-sum_{mx,0}\times i+sum_{i,0}$ 则表示把出现次数大于 $i$ 的元素都保留 $i$ 个。

具体代码如下：
```cpp
int main(){
    scanf("%d",&t);
	
    while(t--){
    	for(int i=1;i<=cnt;i++){//初始化数组
    		mp[num[i].x]=0;
    		aw[num[i].ncnt]=0;
		}
    	cnt=0;
    	int mx=0;
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++){
    		scanf("%d",&a[i]);
    		if(!mp[a[i]]){//出现新的就右移指针
    			mp[a[i]]=++cnt;
    			num[cnt].x=a[i];
    			num[cnt].ncnt=1;
			}
			else{//否则添加
				num[mp[a[i]]].ncnt++;
			}
		}
		
		for(int i=1;i<=cnt;i++){
			aw[num[i].ncnt]++;
			mx=max(num[i].ncnt,mx);
		}
		sum[0][0]=sum[0][1]=0;
		for(int i=1;i<=mx;i++){
			sum[i][0]=sum[i-1][0]+aw[i];
			sum[i][1]=sum[i-1][1]+aw[i]*i;
		}
		ll ans=200000;
		for(int i=1;i<=mx;i++){
			ans=min(ans,sum[i-1][1]+sum[mx][1]-sum[i][1]-sum[mx][0]*i+sum[i][0]*i);//计算最小值
		}
		printf("%d\n",ans);
    }
    return 0;
}
```
撒花撒花

---

## 作者：UperFicial (赞：2)

# 二分

### 前言

推柿子的时候把 $k=i$ 写成 $k=1$ 了，从而推了一下午好不容易找出 $bug$ /ll。

其实这道题貌似比 $E$ 要好想一点，把柿子推出来基本就 $A$ 了。

挂一下我的 [$E$](https://uperficial.blog.luogu.org/solution-cf1490e) 题题解（

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1490F)。

### 题意简述

给定长度为 $n$ 的序列 $a$，一次操作可删去序列中一个元素，求要使得序列中所有不同元素出现次数相等的最小操作次数。

### 题目分析

设 $cnt_{i}$ 为序列中 $a_i$ 出现次数，每当删去一个数 $a_i$ 也就会使相应的 $cnt$ 减一。

于是题目就转化成了每次可将 $cnt$ 的某个位置 $-1$，使 $cnt$ 的数量相等，求最小操作次数。

我们假设最终 $cnt$ 的数量都会变成 $R$。

那如果对于一个位置 $i$ 有 $cnt_i<R$ 的话怎么办？

昨晚我在机房讲这道题时有人说 $R$ 不合法。

~~但我觉得这更像是一个脑筋急转弯~~

直接把 $cnt_i$ 删光光不就行了？然后这个数就不在序列中了。

一次操作可以使 $cnt_i$ 减一，把 $cnt_i$ 删光就需要 $cnt_i$ 次操作。

那如果 $cnt_i\ge R$ 呢？那就需要把它删到 $R$，操作次数为 $cnt_i-R$。

很容易想到，假设我们要找出哪些是 $cnt$ 是大于 $R$ 的，哪些 $cnt$ 是小于 $R$ 的，我们事先可将 $cnt$ 从小到大排序。

假设我们找到了一个位置 $i$ 使得 $cnt_i\ge R$ 且 $cnt_{i-1}<R$，那么说明位置 $i-1$ 之前都需要减到 $0$，$i$ 之后需要减到 $R$。

便可得出一个此时操作次数的柿子：
$$
\sum_{k=1}^{i-1}cnt_k+\sum_{k=i}^n \left(cnt_k-R\right)
$$
但是注意，此处的 $n$ 是指 $cnt$ 的数量，并不是原题中的 $n$。

然后把括号拆开：
$$
\sum_{k=1}^{i-1}cnt_k+\sum_{k=i}^ncnt_k-\sum_{k=i}^nR
$$
没错，就是我，在推柿子的时候把最后一个求和的中的 ${k=i}$ 写成了 ${k=1}$（（（

发现前两个可以合并：
$$
\sum_{k=1}^ncnt_k-\sum_{k=i}^nR
$$
现在就变得好办多了，第一项是一个常数项，只需要把 $i$ 给找出来就好了。

经过排序后，$cnt$ 数组已经是**有序的了**。

我们要是想在某个有序数组上 $a$ 上查找一个位置使得 $i$ 使得 $a_i\ge x$ 会用到啥？

二分。

直接 `lower_bound(cnt+1,cnt+1+n,R)-cnt` 就可以得到 $i$ 了。

往原式直接带进去，只不过还要转化成：
$$
\sum_{k=1}^ncnt_k-(n-i+1)R
$$
就完事了，别忘 $R$ 是要枚举的，$cnt$ 数组自己处理就好，剩下的细节看代码吧。

时间复杂度 $O(n\log n)$。

空间复杂度 $O(n)$。

[$AC$ 记录](https://www.luogu.com.cn/record/46939750)

[$code$](https://paste.ubuntu.com/p/phyj3d3xpG/)
$$
\texttt{The End.by UF}
$$


---

## 作者：registerGen (赞：2)

[宣传一下这次 div3 的题解](https://registergen.github.io/post/solution-codeforces-round-702-div-3/)

考虑枚举这个 $C$，显然 $1\le C\le n$。

假设 $C$ 是固定的，则我们要删几个数呢？

对于出现次数 $<C$ 的数，我们要全删掉。

对于出现次数 $>C$ 的数，我们把它们删到剩下 $C$ 个数即可。

即，我们设出现了 $i$ 次的数有 $cntt_i$ 个。则要删掉的数有这么多个：

$$\sum_{i<C}i\times cntt_i+\sum_{i>C}(i-C)\times cntt_i$$

把括号拆开：

$$\sum_{i<C}i\times cntt_i+\sum_{i>C}i\times cntt_i-C\sum_{i>C}cntt_i$$

预处理 $i\times cntt_i$ 的前缀和，后缀和和 $cntt_i$ 的后缀和即可。

```cpp
int n,a[N+10];
int cntt[N+10];
ll psum[N+10],ssum[N+10],ssum2[N+10];
 
void solve(){
	rep(i,1,n)cntt[i]=0;
	std::map<int,int> cnt;
	n=ri();
	rep(i,1,n)a[i]=ri(),cnt[a[i]]++;
	for(std::map<int,int>::iterator it=cnt.begin();it!=cnt.end();it++)
		cntt[it->second]++;
	psum[0]=0;
	rep(i,1,n){
		psum[i]=psum[i-1]+cntt[i]*i;
	}
	ssum[n+1]=ssum2[n+1]=0;
	per(i,n,1){
		ssum[i]=ssum[i+1]+cntt[i]*i;
		ssum2[i]=ssum2[i+1]+cntt[i];
	}
	ll ans=0x3f3f3f3f;
	rep(i,1,n){
		ans=std::min(ans,psum[i-1]+ssum[i+1]-i*ssum2[i+1]);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：清烛 (赞：1)

（发现公式有一个地方锅了，重新审核）

挂一下 [My Blog](https://imyangty.com/oi/1309)
### 题意
给定序列 $\lbrace a\rbrace$，求最少删几个数可以满足每个数都出现刚好要么 $0$ 次要么 $c$ 次。

### 题解
考虑枚举这个 $c$。首先处理出每个数的出现次数然后把这些出现次数从小到大排序。

假定我们在考虑第 $i$ 个出现次数 $cnt_i$，如果所有的数的出现次数都要变为 $cnt_i$，说明多了的次数要减掉，比 $cnt_i$ 少的出现次数要全部删掉。处理前缀和 $s_i$。不难发现答案即为

$$
\min_{1\le i\le n}\lbrace s_{i - 1} + (s_n - s_i - (n - i) \times cnt_i)\rbrace
$$

$s_{i - 1}$ 为比 $cnt_i$ 出现少的，要全部删掉，$s_n - s_i$ 表示所有大于 $cnt_i$ 的 $cnt_k$ 之和，减掉不需要删除的 $(n - i) \times cnt_i$ 即可。

时间复杂度 $O(n\log n)$（`std::map` 计数 + 排序）

```cpp
int a[maxn], cnt[maxn], sum[maxn];
std::map<int, int> m;

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        m.clear();
        FOR(i, 1, n)
            ++m[read()];//记录出现次数
        n = m.size();
        int tot = 0;
        for (auto i : m)
            cnt[++tot] = i.second;
        std::sort(cnt + 1, cnt + n + 1);//把所有的出现次数排序
        sum[0] = 0;
        FOR(i, 1, n)
            sum[i] = sum[i - 1] + cnt[i];//前缀和
        int ans = 1e9;
        sum[n + 1] = 0;
        FOR(i, 1, n)
            ans = min(ans, sum[i - 1] + sum[n] - sum[i] - (n - i) * cnt[i]);//统计答案
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：henrytb (赞：1)

一句话题意：给一个数组 $a$，我们要任意画一条线 $C$，使得出现次数比 $C$ 多的数的出现次数要删到 $C$，出现次数比 $C$ 少的数的出现次数要删到 $0$，问所有划线的方案中最少要删多少个数。

首先我们先离散化一下数组 $a$，这样 $a$ 数组中的数可以扔进一个桶 $bin$ 里。

然后我们对这个桶数组进行排序（也就是将所有数的出现次数排个序），然后跑个前缀和。

由于所有数最多出现 $n$ 次，因此我们画的线 $C$ 一定不超过 $n$。那么我们可以枚举 $C$，对于每个 $C$，在桶中二分找到第一个 $\ge C$ 的数。在这个数前面的就都删到 $0$，删除次数就是个前缀和；在这个数后面的就都删到 $C$，删除次数就是用前缀和相减再减去这些数的个数 $\times C$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n;
int a[200005],b[200005];
int bin[200005],sum[200005];
int main() {
    for(scanf("%d",&_);_;--_) {
        scanf("%d",&n);
        rep(i,1,n) scanf("%d",&a[i]),b[i]=a[i];
        sort(b+1,b+n+1);
        int nn=unique(b+1,b+n+1)-b-1;
        rep(i,1,n) a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
        rep(i,1,nn) bin[i]=0;
        rep(i,1,n) bin[a[i]]++;
        sort(bin+1,bin+nn+1);
        rep(i,1,nn) sum[i]=sum[i-1]+bin[i];
        int anss=0x3f3f3f3f;
        rep(i,0,n) {
            int id=lower_bound(bin+1,bin+nn+1,i)-bin;
            int ans;
            if(id>nn) ans=sum[nn];
            else ans=sum[id-1]+(sum[nn]-sum[id-1]-(nn-id+1)*i);
            anss=min(anss,ans);
        }
        printf("%d\n",anss);
    }
    return 0;
}
```

---

## 作者：wurang (赞：0)

本题求**最少**需要删除多少个元素，才可以使得剩余的序列中，所有不同数字出现的次数均相等。

很明显，本道题的重点是**个数**，与数字大小无关，那么不难想到利用桶来做。
来看第一组样例：

```python
8
1 2 3 3 3 2 6 6
```
在这组样例中，有 ${1}$ 个 ${1}$ ， ${2}$ 个 ${2}$ ， ${2}$ 个 ${6}$ ， ${3}$ 个 ${3}$ 。个数为：

```python
1 2 2 3
```
此时统计出数量为 ${i}$ 的数字分别有 $t_{i}$ 个：

${1}$ 个 ${1}$ ， ${1}$ 个 ${3}$ ， ${2}$ 个 ${2}$ 。

那么可以枚举个数 ${x}$ ，将小于 ${x}$ 的数变成 0 ，大于 ${x}$ 的数变成 ${x}$ 。

由于小于 ${x}$ 的值会重复计算，所以利用前缀和优化。

令 ${maxsum}$ 表示数量最多的数有几个，有：

$$
{v} = qz[{x}-1] + \sum_{i=x+1}^{maxsum} t[i]*(i-x)
$$

其他细节见代码吧。


```cpp
#include<bits/stdc++.h>
using namespace std;

int tt;
int n;
int a[200005];
int b[200005];//每个数字分别有几个
int t[200005];//t[i]表示数量为i的数字有几个
int qz[200005];
int sum;//有多少个不同的数字
int maxsum;//数量最多的数字有几个
int maxx;//目前最大值
int ans;

int main(){
    cin >> tt;
    while(tt--)
    {
        ans = 2147483647;sum=0;maxsum=0;maxx=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(t,0,sizeof(t));
        memset(qz,0,sizeof(qz));
        cin >> n;
        for(int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        sort(a+1,a+n+1);
        for(int i = 1; i <= n; i++)
        {
            if(a[i] > maxx)//离散化
            {
                sum++;
                maxx = a[i];
            }
            b[sum]++;
        }
        for(int i = 1; i <= sum; i++)
        {
            t[b[i]]++;
            maxsum = max(maxsum,b[i]);
        }
        
        for(int i = 1; i <= maxsum; i++)//前缀和 
        {
            qz[i] = qz[i-1] + t[i];
        }
        
        for(int i = 1; i <= maxsum; i++)
        {
            int v=0;
            v = qz[i-1];//小于i个的数字去掉
            for(int j = i+1; j <= maxsum; j++)v += t[j]*(j-i);//大于i个的数字变成i个
            ans = min(ans,v);
        }
        cout << ans << endl;
    }
}

```

---

## 作者：songtaoran (赞：0)

### 题目大意
给你 $n$ 个数，你可以删掉一些元素，使得剩下的数出现次数相同。求最少删掉的元素个数。  
### 做法
假设剩下的所有的数的出现次数为 $x$，且原来这个数的出现次数为 $y$，则：  
+ 如果 $y < x$，则删减次数多出 $y$。因为无论怎么删 $y$ 都不会增加，于是只能全删掉了。
+ 如果 $y \geq x$，则删减次数多出 $y - x$。因为我们要求删减次数最小。

这时候就有人要说了：枚举出现次数是 $O(n)$ 的，枚举原来的数也是 $O(n)$ 的，那乘起来不就 $O(n^2)$ 了吗？  
考虑优化。  
设 $num_i$ 表示原来的数组中从小到大的可能的出现次数中的第 $i$ 个且一共有 $len$ 个。（其实这一步没优化多少，只不过后面要用）  
再设 $f_i$ 表示原来的数组中出现次数为 $i$ 的数的个数。  
这时，我们就可以用数学的方式优化到 $O(n)$ 了。  
首先设 $now$ 为剩下的所有的数的出现次数为 $num_1$ 的删减次数。即 $now = \sum_{i = 2}^{n} f_{num_i} \times (num_i - num_1)$。  
再设 $cnt$ 为所有满足 $y > num_1$ 的 $y$ 的和。  
如果剩下的所有的数的出现次数从 $num_i$ 变成了 $num_{i + 1}$，$now$ 和 $cnt$ 会发生什么改变呢？  
1. $now$ 会增加 $f_{num_{i - 1}} \times num_{i - 1}$。因为满足 $y < x$ 的 $y$ 新增加了 $num_{i - 1}$。
2. $now$ 会减少 $cnt \times (num_i - num_{i - 1})$。因为原来满足 $num_j > num_{i - 1}(j \geq i)$ 的数需要删掉 $num_j - num_{i - 1}$ 个元素。但现在只需要删掉 $num_j - num_i$ 个元素，多删了 $num_i - num_{i - 1}$。由于 $cnt$ 已经统计了 $\sum_{j = i}^{n} f_{num_i}$，于是再乘上一个 $cnt$ 即可。
3. $cnt$ 会减少 $f_{num_i}$。因为此时 $cnt = \sum_{j = i + 1}^{n} f_{num_i}$。

最后答案与 $now$ 取 $\min$ 即可。  
Tips: 多测记得清空哦~
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T, n, a[200010];
map<ll, ll> mp;
ll f[200010], num[200010], len;
int main(){
	cin >> T;
	while(T--){
		scanf("%lld", &n); mp.clear(); len = 0;
		for(ll i = 1; i <= n; i++) f[i] = num[i] = 0;
		for(ll i = 1; i <= n; i++){
			scanf("%lld", &a[i]); mp[a[i]]++;
		}
		for(ll i = 1; i <= n; i++)
			if(mp[a[i]] > 0){
				f[mp[a[i]]]++; mp[a[i]] = -1;
			}
		for(ll i = 1; i <= n; i++)
			if(f[i] > 0) num[++len] = i;
		ll now = 0, cnt = 0;
		for(ll i = 2; i <= len; i++) now += f[num[i]] * (num[i] - num[1]), cnt += f[num[i]];
		ll mn = now;
		for(ll i = 2; i <= len; i++){
			now += f[num[i - 1]] * num[i - 1];
			now -= cnt * (num[i] - num[i - 1]);
			mn = min(mn, now); cnt -= f[num[i]];
		}
		printf("%lld\n", mn);
	}
	return 0;
}
```
[提交记录 - $281327415$](https://codeforces.com/problemset/submission/1490/281327415)

---

## 作者：ZhaoV1 (赞：0)

## 解析

由于删除元素个数是根据所选择的 $C$ 而改变的，所以可以用键值对来存**存在** $\lambda$ **个相同元素的个数**（其中 $\lambda$ 为任意正整数）。具体来说，如果存在以下样例：

```
1 1 1 2 2 2 3 3 3 4 5 6 6 7
```
那么存在 $3$ 个相同元素的个数为 $3$。  

枚举所有可能的相同元素个数情况，找最优解的思路可以考虑，但在那之前还是先计算一下**时间复杂度**比较稳妥。

当 $n=200000$ 时，最坏的情况是 $\lambda$ 从 $1$ 一直枚举到最大值 $k$，则存在 $\frac{k×(k+1)}{2}=200000$ 使得 $k$ 最大，那么大约 $\lambda$ 最大能遍历至 $\sqrt{400000}$，进行双重 for 循环就是 $400000$，所以可以实现。

接下来枚举相同元素的个数为 $\lambda$。记正在处理的相同元素个数为 $\theta$，拥有 $\theta$ 个相同元素个数的总个数为 $\mu$。如果 $\theta<\lambda$，临时答案应加上 $\theta×\mu$，如果 $\theta>\lambda$，应加上 $(\lambda-\theta)×\mu$，最终答案取每个临时答案的最小值。

AC Code
---


```cpp
#define int long long
using namespace std;
const int N = 2e5+5;
int t,n;
int a[N];

void solve(){
	int res = 1e9+7;
	map<int,int> temp_mp,mp;//mp为int个数的元素种类有多少个
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		temp_mp[a[i]]++;
	}
	for(auto it : temp_mp) mp[it.second]++;

	for(auto it : mp){//单元素种类的保留个数 it.first
		int sum = 0;
		for(auto _it : mp){//对于其他个数的种类而言
			if(_it.first != it.first){
				if(_it.first > it.first) sum += abs(it.first-_it.first)*_it.second;
				else sum += _it.first*_it.second;
			}
		}
		res = min(res,sum);
	}
	cout << res << '\n';
}
```

---

