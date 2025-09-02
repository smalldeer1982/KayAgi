# Good Subarrays

## 题目描述

有一个数组$a_1,a_2,\dots,a_n$，满足$\forall i \in[1,n]$ 有 $0 \le a_i \le 9$。

我们称一个子数组 $a_l,a_{l+1},a_{l+2},\dots,a_{r-1},a_r$ 是“好”的，当且仅当这个子数组中所有元素的和等于它的长度（即 $\sum_{i=l}^r a_i = r-l+1$ ）。

现在要你计算出数组 $a$ 中所有“好”的子数组的数量。

## 说明/提示

### 样例解释

第一组数据中， $a_{1\dots1},a_{2\dots3},a_{1\dots3}$ 是原数组的“好”子数组；

第二组数据中， $a_{1\dots1},a_{2\dots2},a_{1\dots2},a_{4\dots4},a_{5\dots5},a_{4\dots5}$ 这$6$个子数组是原数组的“好”子数组；

第三组数据中，只有 $a_{2\dots6}$ 是原数组的“好”子数组。


$1\le t\le 1000,1\le n\le 10^5,1\le \sum n \le 10^5$

## 样例 #1

### 输入

```
3
3
120
5
11011
6
600005```

### 输出

```
3
6
1```

# 题解

## 作者：Orange_qwq (赞：13)

$\texttt{upd on 2023.1.21}$ 修改了题解。

$\texttt{upd on 2023.1.22}$ 还是有点问题，这个屑又修改了题解。新年快乐！

## 前言

[题目链接](https://www.luogu.com.cn/problem/CF1398C)

洗澡的时候想明白了（

## 题目大意

求 区间和 等于 区间长度 的 区间 的个数。

## 思路分析

看到“区间”两个字，很容易想到 **前缀和**。

令 $Sum_i$ 为前 $i$ 项的前缀和，那么我们要求 **使下面式子成立的 $(i,j)$ 组数**：

$$Sum_j-Sum_{i-1} =j-i+1 \ \ \ (i\le j)$$

移项，则我们需要求

$$Sum_j-j=Sum_{i-1}-i+1 \ \ \ (i\le j)$$

成立的情况总数。

既然是相等的，那我们暂时设 $Sum_j-j = x=Sum_{i-1}-i+1$，其中 $Sum_{i-1}-i+1$ 不一定存在。

因为等式左右两边相等，所以我们要算相等的 $x$ 有多少情况，即有多少种上述式子能够成立的情况。我们可以把每一次计算出来的 $x$ 扔进桶里，统计 $x$ 有多少个，如果后面计算时 $x$ 的数目不为 $0$，则上述式子成立，把 $x$ 的数目累加到答案 $ans$ 里去，并把桶中 $x$ 的数目 $+1$，以便后面的统计。


## $\texttt{AC Code}$

**注意**：$[0,i]$ 也能使式子成立，故需要将下标为 $0$ 的桶赋值为 $1$。

这个题目需要开 `long long`。

代码中 $mp$ 为桶，因为下标有可能是负数，所以使用 `map` 映射。如果不想用 `map` 的话可以把下标加上一个偏移量，但是这样不太保险，可能会出现数组开不够或是爆内存之类的问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll s[100010], n, ans;
map < ll, ll > mp;
// s 即前缀和数组
int main() {
	int t;
    char c;
	scanf("%d", &t);
	while (t--) {
		memset(s, 0, sizeof s), ans = 0;
		mp.clear();
		mp[0] = 1; // [0, i] 合法区间
		scanf("%lld", &n);
		for (int i = 1; i <= n; ++i) {
			cin >> c;
			s[i] = s[i - 1] + c - '0';
			ans += mp[s[i] - i] ++;
        // 累加答案并将桶数组 + 1
		}
		printf("%lld\n", ans);
	}
	return 0;
} 
```


---

## 作者：SpeedStar (赞：11)

#### 算法分析

注意到
$\sum\limits_{i = l}^r {{a_i}}  = r - l + 1 \Leftrightarrow \sum\limits_{i = l}^r {{a_i}}  - \sum\limits_{i = l}^r 1  = \sum\limits_{i = l}^r {\left( {{a_i} - 1} \right)}  = 0$，于是只需对每个元素$-1$，然后原问题就转化成统计和为$0$的子数组的个数。

#### C++代码
```cpp
#include <iostream>
#include <vector>
#include <map>
#define int long long

using namespace std;

int n;
string s;

signed main() {
	int t;
	cin >> t;
	
	while (t--) {
		cin >> n >> s;
		vector<int> v(n);
		for (int i = 0; i < n; ++i) v[i] = s[i] - '0' - 1;
		
		map<int, int> mp;
		int sum = 0, ans = 0;
		for (int i = 0; i < n; ++i) {
			sum += v[i];
			if (sum == 0) ans++;
			ans += mp[sum];
			mp[sum]++;
		}
		
		cout << ans << '\n';
	}
	
	return 0;
}
```


---

## 作者：rouxQ (赞：5)

## 题意
给定数组 $a$ 满足 $a_i\in \{0,1,...9\}$，求有多少个区间 $[l,r]$ 满足 $\sum_{i=l}^r=r-l+1$。
## $\operatorname{Sol}$
考场上的奇怪想法qwq。

把式子变形一下，变成
$$\sum_{i=l}^na_i+l-1=\sum_{i=r+1}^n+r$$

先枚举一下 $r$，把式子的右边丢进一个桶里。再开始枚举 $l$，为了保证区间合法，每次统计前先去除 $l-1$ 处的贡献，再统计答案，实现见代码。
## $\operatorname{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int t[1000001], a[100001], pre[100001];
char ch[100001];
int main (){
    int T;
    scanf("%d", &T);
    while(T--){
        memset(t, 0, sizeof(t));//多测清空桶
        int n;
        scanf("%d", &n);
        scanf("%s", ch + 1);
        for (int i = 1; i <= n; i++){
            a[i] = ch[i] - '0';
            pre[i] = pre[i - 1] + a[i];
        }
        for (int i = 0; i <= n; i++)
            t[pre[n] - pre[i] + i]++;//先把右边的式子丢进桶里
        long long ans = 0;
        for (int i = 1; i <= n; i++){
            t[pre[n] - pre[i - 1] + i - 1]--;//去除不合法的贡献
            ans += t[pre[n] - pre[i - 1] + i - 1];//统计答案
        }
        printf("%lld\n", ans);//记得开long long
    }
    return 0;
}
```

---

## 作者：Actinoi (赞：3)

### 为获取最佳阅读效果，建议访问：[Good Subarrays｜Actinoi's blog](https://www.actinoi.com/2020/08/30/1398c%20good%20subarrays/)

**题目链接：**[Good Subarrays](https://codeforces.com/contest/1398/problem/C)

**题目大意：**给定一个字符串，需要找到有多少个区间使得其区间内每个元素的和为区间长度。

#### 题解：

其区间内每个元素的和为区间长度， 也就是 区间和 = 区间长。

区间和可以用前缀和来维护，因此，可以得到：

$sum[i] - sum[j - 1] = i - j + 1$

移向，可以得到：

$sum[i] - i = sum[j - 1] - j + 1$

统计 $sum[i]-i$，如果出现重复的，那么  $sum[i] - sum[j - 1] = i - j + 1$ ，因此 $sum[i]$ 可以与前面的所有项组合。

特别需要注意的，当 $sum[i] - i= 0$ 时，那么，$[0, i]$ 区间和也就等于区间长度，因此 $sum[0] = 1$。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long sum[1000001], appear[1000001]; //记录前缀和， 记录出现过几次
int main() {
    long long t, n, ans = 0;
    scanf("%lld", &t);
    while (t >= 1) {
      	t--;
        memset(sum, 0, sizeof(sum));
        memset(appear, 0, sizeof(appear));
        appear[100000] = 1; //注意避免 sum[i] - i 越界！因此，把 100000 作为起点
        ans = 0;
        scanf("%lld", &n);
        char c;
        for (long long i = 1; i <= n; i++) {
            cin >> c;
            sum[i] = sum[i - 1] + c - '0'; //前缀和
            ans = ans + appear[sum[i] - i + 100000]; 
            appear[sum[i] - i + 100000]++; //更新答案
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Lynkcat (赞：3)

设 $S_i$ 为前缀和。

那么如果一对 $l,r$ 满足 $S_r-S_{l-1}=r-l+1$ ，那么它们对答案的贡献为 $1$ 。

移项得 $S_r-r=S_{l-1}-l+1$ 。

那么我们可以考虑遍历数组，先将 $i$ 作为 $l$ 时 $b_{S_{i-1}-i+1}$ 加一。然后答案加上当前 $i$ 作为 $r$ 时符合条件的 $l$ 的个数，即 $b_{S_{i}-i}$ 。

``` c++
#include<bits/stdc++.h>
#define int long long
#define N 1000000
int n,T,ans,a[N],s[N],b[N];
char st[N];
using namespace std;
signed main()
{
    cin>>T;
	while (T--)
	{
	    cin>>n;ans=0;
		for (int i=1;i<=n;i++) cin>>st[i];
		for (int i=1;i<=n;i++) a[i]=st[i]-'0',s[i]+=a[i]+s[i-1],b[s[i-1]-i+1]++,ans+=b[s[i]-i];
		for (int i=n;i>=1;i--) b[s[i-1]-i+1]--,s[i]=0;
		cout<<ans<<endl;
	}
}
```

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1398C)

---

先膜 Lautisticyc 巨佬，感谢她的付出。

我们设 $\operatorname {sum}$ 数组为前缀和，题目求有多少个 $sum_l - sum_r = r - l + 1$，

我们可以把所有的 $a_i$ 减一，这样就变成了求子段和为零了。

我们用一个桶储存每种前缀和出现的次数，再用 $ans$ 来统计。

注意，单独的一个零也是合法的子数组。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 100005;
int n,m,a[maxn],b[maxn],times;
int ton[maxn];

int main () {
	read(times);
	while (times --) {
		read(n);
		long long ans = 0;
		for (int i = 1 ; i <= n ; ++ i) scanf("%1d",&a[i]),a[i] = a[i - 1] + a[i],a[i] --,b[i] = a[i];
		a[n + 1] = 0;
		b[n + 1] = 0;
		sort(b + 1,b + 1 + n + 1);
		int num = n + 1;
		num = unique(b + 1,b + 1 + num) - b	- 1;
		ton[lower_bound(b + 1,b + 1 + num,a[n + 1]) - b] = 1;
		for(int i = 1 ; i <= n ; ++ i) {
			a[i] = lower_bound(b + 1,b + 1 + num,a[i]) - b;
			ans += ton[a[i]];
			++ ton[a[i]];
		}
		printf("%lld\n",ans);
		for(int i = 1 ; i <= n ; ++ i)	-- ton[a[i]];
		-- ton[lower_bound(b + 1,b + 1 + num,a[n + 1]) - b];
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

巨佬们都是用各种 dp 啊，map 啊做的，这道题蒟蒻又和巨佬们的思路不一样，蒟蒻是通过瞎推式子做出来的。

首先我们先搞一个前缀和，那么题目要求就可以翻译为：求出所有满足 $s[i]-s[j-1]=i-j+1(1 \le j \le i \le n)$ 的 $(i,j)$ 的对数。我们稍微改动一下，就是 $s[i]-s[j]=i-j(0 \le j <i \le n)$。移项，可得 $s[i]-i=s[j]-j(0 \le j <i \le n)$。发现等号左右两边都是形如“$s[x]-x$”的，于是我们增加一个数组 $d$，令 $d[x]=s[x]-x$。

现在就是要求所有满足 $d[i]=d[j](0 \le j < i \le n)$ 的 $(i,j)$ 的对数。这就很简单了，只需排个序，针对每个连续相等的数字串，比如 $d$ 为 $000111$（样例中第二个）。第一个串 $3$ 个 $0$，答案增加 $3 \times 2 / 2 = 3$，后面同理，因此答案为 $6$。

注意我们要用到 $d[0]$，所以记得每次清零，同时记得开 `long long`。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,a[100001],s[100001],d[100001];
ll ans;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(register int i=1;i<=n;++i)
		    scanf("%1d",&a[i]);
		for(register int i=1;i<=n;++i)
			s[i]=s[i-1]+a[i];
		for(register int i=1;i<=n;++i)
		    d[i]=s[i]-i;
		ans=0;
		d[0]=0;
		sort(d,d+n+1);
		for(register int i=0;i<=n;)
		{
			int pos=upper_bound(d+1,d+n+1,d[i])-d;
			ans+=(((ll)(pos-i))*((ll)(pos-i-1)))/2;
			i=pos;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：pomelo_nene (赞：0)

当时傻了，卡了半个小时。

考虑一段区间是 `good subarray` 的条件。设 $sum_i = \sum_{j=1}^i a_i$，$[i,j]$ 是 `good subarray` 的条件就是 $sum_i -i = sum_{j-1}-(j-1)$。

所以用 `map` 存一下 $sum_i-i$，最后统计一下答案就行了。

注意特判一下 $0$ 的情况。代码会有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int a[100005],n,t,sum[100005];
map<int,LL> maplive;
int main(){
	scanf("%d",&t);
	while(t-->0)
	{
		maplive.clear();
		scanf("%d",&n);
		LL ans=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%1d",&a[i]);
			sum[i]=sum[i-1]+a[i];
			++maplive[sum[i]-i];
		}
		for(map<int,LL>::iterator it=maplive.begin();it!=maplive.end();++it)
		{
			pair<int,LL> s=*it;
			if(s.first==0)	ans+=s.second*(s.second+1)/2;//如果为0 那么第一个0也能作为一个区间存在
			else	ans+=s.second*(s.second-1)/2;//否则第一个只能当做一个端点
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Sya_Resory (赞：0)

一道比较考思维的题目，但是代码实现很简单。作为一道C题，~~比起896C来~~还是很良心的。

## soln 1: 爆搜

用前缀和记录数组的和，再用两层循环枚举 $l,r$ 的位置，再进行 $O(1)$ 的判断。时间复杂度 $O(n^2)$ 。

但是这个方法会被 $t=1,n=10^5$ 的数据卡到TLE。所以，我们要找到更好的方法。

## soln 2: 前缀和+开桶计数

我们发现，对于每个右端点 $r$，统计出 $a_1,a_2,\dots,a_r$ 的区间和与区间长度 $r$ 的差 $delta_r$ ， 那么 $\forall l \in [1,r)$ ，如果 $delta_l = delta_r$ ，那么区间 $[l + 1,r]$ 一定是一个“好”的子数组。特别的，如果 $delta_r=0$ ，那么 $ans$ 的值还要加一（即区间 $[r,r]$ ）。

所以我们就可以边读入边处理，开个桶统计 $delta_r$ 以前的出现次数。~~我开了个数组 然鹅大佬们似乎都是用的map~~ 为了防止负下标，需要把 $delta_r$ 的值加上 $n$ 。

代码：

```cpp
#include <cstdio>
#include <cstring>

long long t,n,a[100005],cnt[1500005]; 
// cnt[]数组统计delta_r以前出现过的次数

int main() {
    scanf("%lld",&t);
    for(;t;t --) {
        long long sum = 0,ans = 0;
        memset(cnt,0,sizeof(cnt)); // 初始化
        scanf("%lld",&n);
        for(int i = 1;i <= n;i ++) { // 边读入边处理
            scanf("%1d",a + i); 
            sum += a[i]; // 统计前缀和
            int delta = sum - i + n; // 计算delta
            ans += cnt[delta] ++; // 统计贡献
            if(sum == i) ans ++;
        }
        printf("%lld\n",ans); // 输出
    }
    return 0;
}
```

---

