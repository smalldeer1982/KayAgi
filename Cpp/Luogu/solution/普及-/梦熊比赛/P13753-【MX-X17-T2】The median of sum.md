# 【MX-X17-T2】The median of sum

## 题目描述

你有 $n$ 个整数 $a_1,a_2,\ldots,a_n$（可能有负数）。你需要把他们不重不漏地划分为 $k$ 组（$k$ 你可以任意指定）。令 $s_i$ 表示第 $i$ 组的所有数之和，请你求出序列 $s_1,s_2,\ldots,s_k$ 的中位数（此处定义为第 $\lfloor\frac{k+1}{2}\rfloor$ 小的数）的最小值。

形式化地，令全集 $U=\{1,2,\ldots,n\}$，你可以任意指定正整数 $k$ 和 $k$ 个集合 $S_1,S_2,\ldots,S_k$ 满足：

- $S_i\sube U$ 且 $S_i\ne \varnothing$；
- 对于任意的 $i,j\in [1,k]$ 满足 $i\ne j$，有 $S_i\cap S_j=\varnothing$；
- $S_1\cup S_2\cup\cdots\cup S_k=U$。

然后，令 $s_i=\sum_{x\in S_i} a_x$，你需要最小化 $s_1,s_2,\ldots,s_k$ 中第 $\lfloor\frac{k+1}{2}\rfloor$ 小的值。

## 说明/提示

**【样例解释】**

对于第一组数据，我们最优的方案是把第一个数分在第一组，第二个数分在第二组，这样得到 $s=[-1,1]$，中位数为 $-1$。可以证明不存在更优方案。

**【数据范围】**

记 $\sum n$ 为所有数据中 $n$ 的和。

对于 $20\%$ 的数据，$\sum n \le 10$。

对于另外 $20\%$ 的数据，$a_i\ge 0$。

对于另外 $20\%$ 的数据，$a_i \le 0$。

对于 $100\%$ 的数据，$1 \le T \le 100$，$1 \le n,\sum n \le 10^6$，$-10^9\le a_i\le 10^9$。

## 样例 #1

### 输入

```
3
2
-1 1
3
1 1 1
6
-1 1 4 5 1 -4```

### 输出

```
-1
1
-5```

# 题解

## 作者：__KevinMZ__ (赞：1)

# [题解：P13753 【MX-X17-T2】The median of sum](https://www.luogu.com.cn/problem/P13753)

贪心。

- 对于全部是正数的情况，将最小的分为一个集合，其他的分为一个集合。得到最小值。
- 对于有负数的情况，将负数分为一个集合，其他的分为一个集合。得到最小值。

可以证明，这两种方案都是选所有数的最小的和。

:::success[AC code]
```cpp lines=24-35
#include<bits/stdc++.h>
#define int __int128
#define ONLINE_JUDGE
using namespace std;
inline istream&operator>>(istream&is,int&k){
	int f=1;
	k=0;
	char ch=getchar();
	while(!isdigit(ch))(ch=='-'?f*=-1:f*=1),ch=getchar();
	while(isdigit(ch))k=(k<<3)+(k<<1),k+=ch-'0',ch=getchar();
	k*=f;
	return is;
}
inline ostream&operator<<(ostream&os,int k){
	if(k<0)putchar('-'),k*=-1;
	if(k>=10)os<<(k/10);
	putchar(k%10+'0');
	return os;
}
inline int qpow(int x,int y,const int mod=-1){int ans=1;while(y){if(y&1)ans*=x;x*=x;if(mod!=-1)ans%=mod,x%=mod;y>>=1;}return ans;}
int t;

void solve(){
	int n;
	cin>>n;
	int ans=0,minn=1e10;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		minn=min(minn,x);
		if(x<0)ans+=x;
	}
	if(ans)cout<<ans;
	else cout<<minn;
	cout<<"\n";
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	for(cin>>t;t--;solve());
	return 0;
}
/*
文件名: test.cpp
创建时间: 2025-08-17 16:52:04
作者: __KevinMZ__
*/
```
:::

---

## 作者：zyr2011 (赞：1)

### 题目解法
我们容易发现，当 $k = 2$ 时，$\lfloor\frac{k+1}{2}\rfloor=1$，那么我们可以把这 $n$ 个整数分为 $2$ 组，当 $n$ 个整数中有负数时，一组全部放负数，一组全部放正数，那么答案显然是**所有负数的和**，当 $n$ 个整数中没有负数时，我们将最小的数单独作为一组，其他的数作为另一组，那么此时答案就是这个**最小的数**。**容易证明这是最优解**。 
### 满分代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
inline int min(int a,int b){
	return a<b?a:b;
}
inline void solve(){
	int n;cin>>n;
	int minv=1e18,sum=0;
	for(re int i=1;i<=n;++i){
		int s;cin>>s;
		minv=min(minv,s);//存最小的数 
		if(s<0){
			sum+=s;//有负数，直接累加 
		}
	}
	if(minv<0){//有负数的情况 
		cout<<sum<<endl;
	}
	else{//没有负数的情况 
		cout<<minv<<endl;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：chenzefan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13753)
## 前言
比赛比了 $10$ 分钟，只 AC 了前两题（没时间了），勿喷。
## 思路
首先第一眼看到了这么长串的题面先看样例，也许是题面较为恐怖，题意却十分简单。

简化版题意：给定一个整数 $n$ 和一个长度 $n$ 的序列 $a$，求将序列 $a$ 分成若干分后，每个集合内元素和的最小值，不要求连续。 

然后结合样例，结论随之出现：
- 如果序列 $a$ 中有负数，则直接输出所有负数之和即可（这样会很小）。
- 如果序列 $a$ 中没有负数，则输出所有元素的最小值即可。

然后可以考虑排序，毕竟不会超时。当然派也可以。

时间复杂度 $O(T \times n \log n)$，这是加了排序的复杂度，不加的话可能要多几个循环，时间复杂度更优，为 $O(T \times n)$。

注意由于 $-10^9 \le a_i \le 10^9$，所以本题要开 long long。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int t,n,a[N],ans;
signed main(){
    scanf("%lld",&t);
    while(t--){
    	scanf("%lld",&n);ans=0;
    	for(int i=1;i<=n;i++) scanf("%lld",a+i);
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++)
        	if(a[i]<0||i==1) ans+=a[i];
        	else break;
        printf("%lld\n",ans);
    }
    return 0;
}
```
撒花！

---

## 作者：__Kyw666__ (赞：1)

## 题意解释
有 $n$ 个数，分成 $k$ 组，把这 $1$ 到 $k$ 组中数字的和记为 $s_i$，问何时序列 $s$ 的中位数值最小。

## 思路分析
~~题目讲得很华丽，实际上很水。~~  
要使得序列 $s$ 的中位数最小，分的组数就不能多，很容易想到，分 $2$ 组就是最优解。  
因为求的是中位数，所以只要使其中一组尽可能的小即可。那么接下来就很简单了：
* 存在负数：把所有负数加到一组；
* 不存在负数：把所有数中最小的那一个单令为一组。

按以上内容模拟即可，详见代码。

## 代码实现
~~场切代码，马蜂不堪入目。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1e8+5;
ll T,n,a,minn,ans;
int main()
{
	cin>>T;
	while(T--)
	{
		ans=0;minn=1e9+5;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(a<0) ans+=a;//加负数
			else minn=min(minn,a);
        //顺便记下正数中的最小值
		}
		if(ans==0) ans+=minn;
      //没有负数，就记为正数中的最小值
		cout<<ans<<endl;
	}
	return 0;
}
```

结束！

---

## 作者：Vct14 (赞：1)

这题严格简单于 T1 吧。

首先答案一定是原序列中若干个数的和。因此答案理论下界为：若有负数，则为序列中所有负数之和；否则为序列中的最小值。我们考虑取 $k=2$，把序列中所有负数（若无负数，则为最小值）放到一组中，剩下的放到另一组里。显然第一组的和小于第二组的和，即第一组和为中位数。因此可以取到该下界。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;long long ans=0,mn=INT_MAX;
		while(n--){
			int x;cin>>x;mn=min(mn,1ll*x);
			if(x<0) ans+=x;
		}
        if(!ans) ans=mn;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：XingYueLi (赞：1)

## 思路

分类讨论：

- 若有负数，则把所有负数单独列成一组，所有非负数列成一组（可能没有非负数，但题目没有限制 $k>1$，即可以把所有数直接作为一组），此时中位数结果为负数组各数之和，所有的负数都参与运算，所有的非负数不参与运算，故当前结果最小。

- 若没有负数，则将非负数中最小的那个数单独作为一组，剩下的数作为另一组，此时中位数结果为最小的那个数，该情况仅有最小的数参与运算，若有其他非负数参与运算，则结果一定会变大，故当前结果最小。

## Code
```c++
#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;
ll T, n, ans;
int main(){
	cin >> T;
	while(T--){
		ans = 0;
		cin >> n;
		vector<ll> a(n);
		for(int i = 0; i < n; i++){
			cin >> a[i];
		}
		sort(a.begin(), a.end());
		for(int i = 0; i < n; i++){
			if(a[i] < 0){
				ans += a[i];
			}
			else if(ans == 0){
				ans = a[i];
				break;
			}
			else break;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：sunyizhe (赞：0)

这题是个构造题，赛时花了一段时间想出来了，好像不是很难。这里尽量把我赛时的思路呈现给大家。

## 一、题意简化

有 $n$ 个数，现在要分成任意组（**可以为一组**），对 $k$ 组分别求和，求一种构造方案，使得中位数取到最小值（偶数个数取中间较小的）。

## 二、思路

建议读者可以先手搓一下样例，看一下有没有什么感觉。

这题对数的先后没有什么要求，也许可以先排序，尝试一下。

然后……不妨从特殊数据中得到一些提示？

### 2.1 特殊数据一

$\sum n \le 10$，那么可以考虑暴力，可以拿到 $20$ pts。但是暴力看似比较难实现，而且通过在暴力的基础上优化 AC 希望渺茫，没什么，这个特殊数据对我们可能没有太大帮助。

### 2.2 特殊数据二

$a_i \ge 0$，手动模拟一下分组情况试试？

先造一组不大的样例：

```
4
1 2 3 4
```

这里初步是可以猜到，中位数取决于整体的大小。读者可以自行枚举尝试一下。

尝试后，我们发现：对于该种情况，只要将最小的放在一组，剩下的全部放在一组，这就可以达到中位数最小的效果，因为这里只有两个数，在没有负数的情况下，最小的数一定大于等于剩下的任意一个数，更不用说是其他的任意几个数之和了。这里可以取等的原因是因为有 $0$。这样就又拿到了 $20$ pts。

### 2.3 特殊数据三

这个应该比较好想到，只要将所有的数放在一组即可。

### 2.4 对于一般的情况

观察特殊数据二，我们其实是构造了两组数，得到了两个和，使得较小的和尽量小。

观察特殊数据三，我们可以把所有的负数合成一组，这样这组数的和是最小的。

这样这题的答案就呼之欲出了：我们先将所有的负数放到一组，剩下的正数放到一组，得到两个和，容易证明所有负数的和一定是所有可能分组的和中最小的，因为如果这组中多放一个正数，则这个和会变大。输出所有负数的和即可。

而又想到开头说的“排序”，这里找到全体负数可以先对数组排序，在数组中二分查找 $0$，找到负数。（这里其实可以是非正数，$0$ 对答案无影响）。

## 三、代码

::::warning[代码的一些小细节]{open}
- 记得开 `long long`。
- 可能有些人（比如我）求和时喜欢用 C++ `<numeric>` 头文件中的系统函数 `accuculate` 进行区间的求和计算，但是要注意这个函数的返回值是 `inline int`，可能出现即使开了 `long long` 也没过的情况。建议手动实现 `accumulate` 函数。
- 如果还有一些代码方面的问题，欢迎评论/私信，我可能会考虑加入题解中，供大家对照问题。
::::

::::info[代码]
```cpp
// 这里省略了快读快写模板
const int N = 1e6 + 10;

long long n;
long long a[N];

/*
区间求和，但是赛时用的是accumulate（如下），所以不想改动传参格式了，直接替换了函数名
这里求和可以采用阳间一点的实现方法
*/
long long sum(const long long* s, const long long* t) {
    long long tot = 0;
    for (auto i = s; i != t; i++)
        tot += *i;
    return tot;
}

int main() {
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; i++) read(a[i]);

        sort(a + 1, a + n + 1);
        auto pos = upper_bound(a + 1, a + n + 1, 0);
        if (pos > a + 1) write(sum(a + 1, pos));
        else write(a[1]);

        puts("");
    }
    
    return 0;
}
```
::::

---

## 作者：jimmy9_666 (赞：0)

首先注意到划分的集合 $k$ 可以为任意正整数，这使得这道题变得很简单。

先来分讨一下，如果这 $n$ 个数中存在负数，那就将所有负数归为第一个集合，所有非负数归为第二个集合，这样划分 $k = 2$，那么我们的答案就是第 $\lfloor\frac{k+1}{2}\rfloor = 1$ 个集合内的数的和，换句话说，就是所有负数的和。

然后这 $n$ 个数中不存在负数，那么就将最小的数单独作为一个集合，其余的数作为第二个集合，答案为最小的数。

:::info[代码]

```cpp line-numbers
#include <algorithm>
#include <iostream>
#include <cstdio>
#define LL long long
#define int long long

using namespace std;

int read() {
	int k = 0, kk = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			kk = -1;
		c = getchar();
	}
	while ('0' <= c && c <= '9') {
		k = k * 10 + c - '0';
		c = getchar();
	}
	return k * kk;
}

void write(int x) {
	if (x < 0)
		putchar('-'), x = -x;
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e6 + 10;

int n;
int a[N];

signed main() {
	int T = read();
	while (T -- ) {
		n = read();
		for (int i = 1; i <= n; i ++ )
			a[i] = read();
		sort(a + 1, a + n + 1);
		if (a[1] >= 0) {
			write(a[1]);
			putchar('\n');
			continue;
		}
		int tmp = 0;
		for (int i = 1; i <= n; i ++ ) {
			if (a[i] < 0)
				tmp += a[i];
			else
				break;
		}
		write(tmp);
		putchar('\n'); 
	}
	return 0;
}
```

:::

---

## 作者：LiuDai (赞：0)

## 题意
将 $ n $ 个数任意分组，求各组和的中位数的最小值。

## 解法
贪心，还是很巧妙的。

先说结论：如果有正有负，将正数和负数各分一组；如果全为正数，将最小数分一组，其余数分一组；如果全为负数，全部分为一组。

思考过程：首先，$ 0 $ 可以忽略，因为无论 $ 0 $ 被分到哪组都对答案没有影响。为了让答案尽可能小，可以考虑将所有负数分到一起，但这样就有可能因为其他正数的分组导致取不到这个最小和，第一组样例启示我们，只有两组的情况下，答案即为其中小的那个和，于是把其他正数全部分一组就可以保证取到负数和（只有负数时显然另一组和为 $ 0 $ ）；如果全为正数时，同理，为了取到最小数，将其他数全部分一组。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int N = 1e5 + 5, inf = 0x3f3f3f3f3f3f3f3f;

int T, n;
ll ans[2];                                              // 开 long long 防止溢出

signed main() {
    cin >> T;
    for (int _ = 1; _ <= T; ++_) {
        cin >> n;
        ans[0] = 0;                                     // ans[0] 表示所有负数和
        ans[1] = inf;                                   // ans[1] 表示最小正数
        for (int i = 1; i <= n; ++i) {
            ll x;
            cin >> x;
            if (x < 0) ans[0] += x;                     // 如果为负分进第一组
            else ans[1] = min(ans[1], x);               // 尝试把这个正数分进第一组
        }
        cout << (ans[0] != 0 ? ans[0] : ans[1]) << endl;
    }
    return 0;
}
```
如果对你有帮助的话点个赞吧，~~管理大大求过~~

---

## 作者：bayiran (赞：0)

对于每一组数据，我们可以分三种情况来进行讨论，每组情况给出一个可以得出最小的中位数的划分。

1. 如果所有数都是正数，那么可以把最小数分一组，剩余的所有数分一组，这样中位数就是最小数。由于在这种情境下所有数都是正数，所以不会存在一个比最小数还小的数。此时最小数就是答案。

2. 如果所有数都是负数，那么可以把所有数分到同一组里。因为两个负数相加得到的结果，比任何一个负数都小，所以所有负数相加，最后的结果一定是最小的。

3. 如果既有正数也有负数，那么可以把所有非正数（零和负数）分为一组，所有正数分为一组。由于负数一定比正数小，所以把所有负数加起来的结果是最小的中位数。

综上，我们可以通过以下方式得出最小中位数。

1. 排序。
2. 如果排序后的第一位是正数，那么第一位就是答案。
3. 如果排序后的第一位是零或负数，那么答案就是所有的零和副数的和。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1000050];
signed main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        sort(a,a+n);
        if(a[0]>=0){
            cout<<a[0]<<endl;
            continue;
        }
        int ans = 0;
        for(int i=0;i<n;i++){
            if(a[i]>0){
                break;
            }
            ans += a[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

