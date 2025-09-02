# Remove the Ends

## 题目描述

你有一个长度为 $n$ 的数组 $a$，其中元素均为非零整数。初始时你有 $0$ 枚硬币，你将重复以下操作直到 $a$ 变为空：
- 设当前数组 $a$ 的大小为 $m$。选择一个整数 $i$（$1 \le i \le m$），获得 $|a_i|$ $^{\text{∗}}$ 枚硬币，然后：
  - 如果 $a_i < 0$，则将 $a$ 替换为 $[a_1,a_2,\ldots,a_{i - 1}]$（即删除从 $a_i$ 开始的后缀）；
  - 否则，将 $a$ 替换为 $[a_{i + 1},a_{i + 2},\ldots,a_m]$（即删除以 $a_i$ 结尾的前缀）。

请计算最终你能获得的最大硬币数量。

 $^{\text{∗}}$ 此处 $|a_i|$ 表示 $a_i$ 的绝对值：当 $a_i > 0$ 时等于 $a_i$，当 $a_i < 0$ 时等于 $-a_i$。

## 说明/提示

第一个测试用例中获得 $23$ 枚硬币的操作示例：
- $a = [3, 1, 4, -1, -5, \text{\color{red}{-9}}] \xrightarrow{i = 6} a = [3, 1, 4, -1, -5]$，获得 $9$ 枚硬币。
- $a = [\text{\color{red}{3}}, 1, 4, -1, -5] \xrightarrow{i = 1} a = [1, 4, -1, -5]$，获得 $3$ 枚硬币。
- $a = [\text{\color{red}{1}}, 4, -1, -5] \xrightarrow{i = 1} a = [4, -1, -5]$，获得 $1$ 枚硬币。
- $a = [4, -1, \text{\color{red}{-5}}] \xrightarrow{i = 3} a = [4, -1]$，获得 $5$ 枚硬币。
- $a = [4, \text{\color{red}{-1}}] \xrightarrow{i = 2} a = [4]$，获得 $1$ 枚硬币。
- $a = [\text{\color{red}{4}}] \xrightarrow{i = 1} a = []$，获得 $4$ 枚硬币。

最终共获得 $23$ 枚硬币。

第二个测试用例中获得 $40$ 枚硬币的操作示例：
- $a = [-10, -3, -17, \text{\color{red}{1}}, 19, 20] \xrightarrow{i = 4} a = [19, 20]$，获得 $1$ 枚硬币。
- $a = [\text{\color{red}{19}}, 20] \xrightarrow{i = 1} a = [20]$，获得 $19$ 枚硬币。
- $a = [\text{\color{red}{20}}] \xrightarrow{i = 1} a = []$，获得 $20$ 枚硬币。

最终共获得 $40$ 枚硬币。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
6
3 1 4 -1 -5 -9
6
-10 -3 -17 1 19 20
1
1```

### 输出

```
23
40
1```

# 题解

## 作者：nochiras (赞：0)

注意到一个重要的性质：我们每次只会操作最左边的正数或者最右边的负数。这样操作显然更优。从样例解释 1 出发再考虑把这个问题转化为在分界点左右分别取出正数与负数。

```cpp
std::vector<i64> pre(n + 2), suf(n + 2);
pre[1] = a[1] > 0 ? a[1] : 0;
for (int i = 2; i <= n; i++) {
    pre[i] = pre[i - 1];
    pre[i] += a[i] > 0 ? a[i] : 0;
}
suf[n] = a[n] < 0 ? -a[n] : 0;
for (int i = n - 1; i >= 1; i--) {
    suf[i] = suf[i + 1];
    suf[i] -= a[i] < 0 ? a[i] : 0;
}
```

之后从 $1$ 枚举到 $n$ 并记录每个位置的 $pre_i + suf_i$ 与 $ans$ 取 $\max$ 即可。

---

## 作者：zzldd (赞：0)

如果 $a_i \ge 0$，则取 $a_i$ 时会删去 $a_1$ 到 $a_{i-1}$。 \
如果 $a_i < 0$，则取 $a_i$ 时会删去 $a_{i+1}$ 到 $a_n$。\
显然，当 $a_i \ge 0$ 时，我们在取 $a_i$ 前，可以先取 $a_1$ 到 $a_{i-1}$ 区间所有 $a_j \ge 0$，且这时我们获得的金币数最多。\
同理，当 $a_i < 0$ 时，我们在取 $a_i$ 前，可以先取 $a_{i+1}$ 到 $a_n$ 区间所有 $a_j < 0$，且这时我们获得的金币数最多。\
我们考虑建立一个前缀和数组 $qz$，记录 $a_1$ 到 $a_i$ 区间所有 $a_j \ge 0$ 的和，同时建立一个后缀和数组 $hz$，记录 $a_i$ 到 $a_n$ 区间所有 $a_j < 0$ 的绝对值之和，之后枚举 $1-n$，对于每一位，最佳答案即为 $qz_i + hz_i$。我们使用 $ans$ 记录当前最优解，最后输出 $ans$ 即可。\
记得开 long long

```cpp
#include<bits/stdc++.h>
#define int long long //一定要开long long,否则会挂
using namespace std;
int T,n,a[200005],qz[200005],hz[200005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;int ans=0;
		qz[0]=0,hz[n+1]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			qz[i]=(a[i]>=0?qz[i-1]+a[i]:qz[i-1]); //前缀和
		}for(int i=n;i>=1;i--) hz[i]=(a[i]<0?hz[i+1]+abs(a[i]):hz[i+1]);  //后缀和
		for(int i=1;i<=n;i++) ans=max(qz[i]+hz[i],ans);
		cout<<ans<<"\n";
	}
}
```

---

## 作者：Listar (赞：0)

题意
---

我们任选一个数，如果这个数是正数，我们的结果要加上这个正数，则我们需要删去前边的区间，下一步操作只能在后边的区间进行。

如果这个数是负数，我们结果要加上这个数的相反数，则我们需要删去后边的区间


思路
---

对于一个正数，左边删去的区间和后边结果已经无关，如果左边区间中依然存在一个正数，我们可以先对左边区间的正数进行操作，然后在对这个正数进行操作，负数可以类比正数从右向左操作。

但是这样依然不好分类，我们不妨把数组分为两部分进行，左边一部分只进行正数的删减，从左向右，保证了没有正数浪费，右边一部分只考虑负数的删减，从右向左，保证了没有负数浪费。

我们可以考虑 $n+1$ 种分组方式，这种计算方法保证了，能算出该种分组方式下的最优解，我们只需求出

这样我们把时间缩短为 $O(n^2)$，但是依然面临时间问题。

我们考虑给分组进行排序，第一组的左半部分为零，然后一次把右半部分最左侧元素加入左半部分，构成剩下 $n$ 组。

这样对于上一组已经求出的结果，我们可以仅讨论每次分组与上一次分组中移动的那一个元素。如果移动的元素是正数，我们只需要在上次结果上加上这一个数，如果是负数，我们需要在上次结果上减去这一个相反数，也即加上这个数。

对于上述操作的解释是，正数在右侧未被计入，到左侧之后需要被计入，负数在右侧被计入，到左侧之后不被计入，需要减去绝对值。

最后我们统计每次分组的值，只需求出其中最大的即可。


代码实现
---

python 代码

```python
def solve():
    n=int(input())
    l=list(map(int,input().split()))
    ##输入

    s=0 #统计答案数字
    for i in range(n):
        if l[i]<0:
            s-=l[i]  #通过减去负数实现加绝对值

    line=[s]
    ## 收集答案

    for i in range(n):
        s+=l[i]
        line.append(s)

    print(max(line))
    ##从所有答案中选择最大的

T=int(input())
for i in range(T):solve()
```

---

## 作者：thedyingkai (赞：0)

### 思路
题意简单来说就是 $a_i<0$ 时，删去 $a_i$ 及其后面的数，得到 $-a_i$ 个金币，$a_i>0$ 时，删去 $a_i$ 及之前的数，得到 $a_i$ 个金币。

把 $a_i$ 逐个加入到数组中考虑，此时前面已经有了若干个数。
- 若下一个数是负数，可以先选择去掉这个负数，这样得到的新数组和没有考虑这个数的数组相同，金币总数增加 $-a_i$。
- 若下一个数是正数，先选择他就会删掉整个数组，所以最后选择他，但是如果先选择负数，会把他直接删掉，相当于没选择他，所以只能先选择在他前面的其他正数；这样，每次都选择正数，得到的总金币数就是 $S_{a_{\text{ 正 }}}$，将该结果与 $-S_{a_{\text{ 负 }}}$ 比较，取较大值即可。

所以我们有了这个简短的代码。
### AC code
```cpp
#define ll long long
#define rep(i,x,n) for(int i=x;i<=n;i++)
template<class T> bool chmax(T &a,T b){if(a<b){a=b;return 1;}else return 0;}
void solve() {
    int n;
    cin>>n;
    vector<ll> dp(2);
    rep(i,0,n-1){
        ll a;
        cin>>a;
        if(a<0) dp[1]-=a;
        else dp[0]+=a;
        chmax(dp[1],dp[0]);
    }
    cout<<dp[1]<<endl;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV19cAaeVEme?t=869)

---

## 作者：hbhz_zcy (赞：0)

题意：对于给出的序列 $\{a_i\}$ 不断执行下面的操作直至序列为空：任意选择一个位置 $p$，$a_p>0$ 则取位置 $p$（不含）之后的作为新序列，$a_p<0$  取位置 $p$（不含）之前的作为新序列。每次操作的贡献为 $|a_p|$，求总贡献和的最大值。  
容易发现若按常规思路去做区间 `dp` ，时空复杂度上都是行不通的。于是尝试去考虑前 $p-1$ 个元素到前 $p$ 元素的变化：  
$a_p<0$，那么我们可以在前 $p-1$ 个元素对应的任意一个操作序列的开头添加选择位置 $p$ 的操作，发现并没有影响到已有的操作。  
$a_p>0$，则 **当且仅当** 前 $p-1$ 个元素对应的任意一个操作序列没有使用过 $a_{p_0}<0$ 向左截取，才可能被添加进去。而所有的这些序列都可以在末尾再去选择 $p$，从而减小这一步操作的影响。  
![](https://cdn.luogu.com.cn/upload/image_hosting/683y56al.png)  

采用上述的方法，发现每一步的操作总是在原操作序列两端作添加，因此更改原操作序列并不能使额外的位置得到选择，从而每一步的最优可以推导出全局的最优。  
具体实现比较简单，维护两个变量 $ans,ansr$，一个记录任意操作的最大贡献和，另一个记录仅进行向右截取，从未向左截取的最大贡献和。遇到 $a_p>0$ 仅 $ansr$ 可以选取，遇到 $a_p<0$ 则两者都选取，取最大值计入 $ans$ 之中，$ansr$ 不变。  
```cpp
//g++ c.cpp -o c -g -std=c++14 -O0 -Wall
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int qd(){
	int ng=0,rt=0;char c=getchar();
	while(c<'0'||c>'9')  ng^=c=='-',c=getchar();
	while('0'<=c&&c<='9')  rt=(rt<<3)+(rt<<1)+c-48,c=getchar();
	return ng?-rt:rt;
}
const int maxn=2e5+10;
int a[maxn];
int main(){
	freopen("in.txt","r",stdin);
	int T=qd();
	while(T--){
		int N=qd();LL ansr=0,ans=0;
		for(int i=1;i<=N;i++){
			int x=qd();
			if(x<0)  ans=max(ans-x,ansr-x);
			else ansr+=x;
		}
		printf("%lld\n",max(ans,ansr));
	}
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

**一定不要把这题想复杂**。

经过手玩发现合法操作方案一定由左半部分正数及右半部分负数组成。

预处理前缀正和以及后缀负和，枚举正负分界点取最大值即可。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
using ll = long long;
ll a[N], pfp[N], pfn[N], res;
int n;
void init_global()
{
}
void init_local()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", a + i);
	for (int i = 1; i <= n; i++)
	{
		pfp[i] = pfp[i - 1];
		pfn[i] = pfn[i - 1];
		if (a[i] > 0)
			pfp[i] += a[i];
		if (a[i] < 0)
			pfn[i] -= a[i];
	}
}
void run()
{
	res = 0;
	for (int i = 0; i <= n; i++)
	{
		res = max(res, pfp[i] + pfn[n] - pfn[i]);
	}
	printf("%lld\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

