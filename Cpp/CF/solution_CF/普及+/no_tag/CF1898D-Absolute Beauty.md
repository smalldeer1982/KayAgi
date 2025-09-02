# Absolute Beauty

## 题目描述

Kirill has two integer arrays $a_1,a_2,…,a_n$ and $b_1,b_2,…,b_n$ of length $n$. He defines the _absolute beauty_ of the array $b$ as
$$
\sum_{i=1}^n|a_i-b_i|
$$
Here, $|x|$ denotes the absolute value of $x$.

Kirill can perform the following operation **at most once**:

- select two indices $i$ and $j$ ($1≤i<j≤n$) and swap the values of $b_i$ and $b_j$.

Help him find the maximum possible absolute beauty of the array $b$ after performing **at most one** swap.

## 说明/提示

In the first test case, each of the possible swaps does not change the array $ b $ .

In the second test case, the absolute beauty of the array $ b $ without performing the swap is $ |1-1| + |2-2| = 0 $ . After swapping the first and the second element in the array $ b $ , the absolute beauty becomes $ |1-2| + |2-1| = 2 $ . These are all the possible outcomes, hence the answer is $ 2 $ .

In the third test case, it is optimal for Kirill to not perform the swap. Similarly to the previous test case, the answer is $ 2 $ .

In the fourth test case, no matter what Kirill does, the absolute beauty of $ b $ remains equal to $ 16 $ .

## 样例 #1

### 输入

```
6
3
1 3 5
3 3 3
2
1 2
1 2
2
1 2
2 1
4
1 2 3 4
5 6 7 8
10
1 8 2 5 3 5 3 1 1 3
2 9 2 4 8 2 3 5 3 1
3
47326 6958 358653
3587 35863 59474```

### 输出

```
4
2
2
16
31
419045```

# 题解

## 作者：mountain_climber (赞：8)

先说突破点：将绝对值转换为数轴上的线段长度（距离）。

我们来考虑一下怎么做。

首先我们只能进行一次操作，具体来说一次操作是这样的：

- 操作对象：两条线段，分别为 $[a_{i},b_{i}]$ 和 $[a_{j},b_{j}]$。
- 操作内容：将其转变为两条线段，分别为 $[a_{i},b_{j}]$ 和 $[a_{j},b_{i}]$。

随后题意变成使操作过后增加尽量多的长度，此处可以开始具体分类讨论了：

**情况一**：两线段没有公共部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/3kcvgfqq.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/9qa1q2sj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/g2dwiorl.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/hmzwv1z0.png)

可以发现这种情况下不管怎么分配 $[a_{i},a_{j},b_{i},b_{j}]$ 都会为答案贡献两倍的两个线段的中间部分长度。

**情况二**：相交但是没有包含关系。

![](https://cdn.luogu.com.cn/upload/image_hosting/qw0pofnq.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ekn139ta.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/d4yha6w0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/g3nzk721.png)

可以发现这种情况下最好也只能使得变化前后的总长度保持不变，没有意义。

**情况三**：一个线段被另一个线段所包含。

![](https://cdn.luogu.com.cn/upload/image_hosting/fq4e9tir.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/bwuj0x6o.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxyq9pa6.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/fc5dt0g4.png)

可以发现这种情况下和情况二基本相同，也是没有意义的。

也就是说唯一有意义的操作就是情况一，现在问题就最终转变为了找到一组线段使其中间部分长度最长，其实就是找到最右的左端点和最左的右端点。

注意如果没有情况一就不做操作。

最后粘一下代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
const int N=2e5+10;
const int inf=0x3f3f3f3f;
int n,a[N],b[N];
void ipt(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
}
void solve(){
	int l=inf,r=0,ans=0;
	for(int i=1;i<=n;i++) ans+=abs(a[i]-b[i]); 
	for(int i=1;i<=n;i++){
		l=min(l,max(a[i],b[i]));
		r=max(r,min(a[i],b[i]));
	}
	printf("%lld\n",ans+(2*(r-l)>0?2*(r-l):0));
}
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		ipt();
		solve();
	} 
	return 0;
} 
```

[AC记录](https://codeforces.com/contest/1898/submission/236134367)

---

## 作者：LittleAcbg (赞：8)

![](https://cdn.luogu.com.cn/upload/image_hosting/t83tqcrn.png)

如图，进行一次操作后，可以增加一个区间的两倍。考虑 $l_i=\min(a_i,b_i),r_i=\max(a_i,b_i)$，此时对于任意 $1\le i,j\le n$，可以交换 $b_i,b_j$ 使得绝对值总和增加 $2\times(l_i-r_j)$。当然，当 $l_i\le r_j$ 时，由贪心思路，此时不交换，因为交换增加不了收益。

所以，按照贪心，我们选择最大的一个 $l_i$ 和最小的一个 $r_j$，进行操作。当然要与 $0$ 取最大，以免造成负面收益。

AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+9;
int t,n,a[N],b[N];
signed main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];
        int minn = 1e+9,maxx = 0,sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            minn = min(minn, max(a[i], b[i]));
            maxx = max(maxx, min(a[i], b[i]));
            sum += abs(a[i] - b[i]);
        }
        cout << sum + max(0LL, (maxx - minn) * 2) << endl;
    }
    return 0;
}
```

---

## 作者：Msents (赞：2)

将每对 $(a,b)$ 抽象为线段。

然后讨论一下有四种情况能产生贡献，这里合在一起讲两种，因为另外两种是反过来的的：
- 线段方向相反（比如 $a_i>b_i$ 和 $a_j<b_j$），且一个线段的右端点小于另一个线段的左端点。
- 线段方向相同，且一个线段的右端点小于另一个线段的左端点。

先求答案初值，然后找最小左端点和最大右端点，两者距离翻个倍即为贡献。

翻过来再求一遍，没了。

赛时答辩：

```cpp20
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=200000;
int n,a[MaxN+1],b[MaxN+1];
int Abs(int x){return x>0?x:-x;}
void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	int ans=0,sum=0;
	for(int i=1;i<=n;i++)sum+=Abs(a[i]-b[i]);
	ans=sum;
	int mx=0,mn=1e12;
	for(int i=1;i<=n;i++){
		if(a[i]<=b[i]){
			mn=min(mn,b[i]);
			mx=max(mx,a[i]);
		}
	}
	ans=max(ans,sum+(mx-mn)*2);
	mx=0,mn=1e12;
	for(int i=1;i<=n;i++){
		if(a[i]<=b[i]){
			mx=max(mx,a[i]);
		}
		if(a[i]>=b[i]){
			mn=min(mn,a[i]);
		}
	}
	ans=max(ans,sum+(mx-mn)*2);
	mx=0,mn=1e12;
	for(int i=1;i<=n;i++){
		if(a[i]<=b[i]){
			mn=min(mn,b[i]);
		}
		if(a[i]>=b[i]){
			mx=max(mx,b[i]);
		}
	}
	ans=max(ans,sum+(mx-mn)*2);
	mx=0,mn=1e12;
	for(int i=1;i<=n;i++){
		if(a[i]>=b[i]){
			mn=min(mn,a[i]);
			mx=max(mx,b[i]);
		}
	}
	ans=max(ans,sum+(mx-mn)*2);
	cout<<ans<<'\n';
}
#undef int
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：lutaoquan2012 (赞：2)

## 思路：

如果 $a_i>b_i$，将 $a_i,b_i$ 交换。之后考虑将原数组 $(a_i,b_i)$ 配成一对，这样这可以表示数轴上的一条线段，其长度为 $\left\vert a_i-b_i  \right\vert$。

所以接下来可以讨论两条线段的相对位置关系以及交换之后的形态，大体可以分为这两条线段完全不相交，部分相交和一条包含另一条的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/95vzf72n.png)

可以发现，只有在两条线段完全不相交的情况下才会导致的值增长。那么，接下来的问题就是如何寻找到能够增加最大的这样两条线段，也就是 $a_i-b_j$ 最大。如果这个值为正，那么就加，否则就什么也不做，即不做交换操作。实际上就是找到最大的 $a_i$ 和最小的 $b_j$ 即可。

时间复杂度为 $O(n)$。

## 代码：

```cpp
//
// Created by 55062 on 2024/2/26.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll T,n,a[200010],b[200010],ans,mi=1,mj=1,f;
ll hhh(ll i,ll j){
    return -abs(a[i]-b[i])-abs(a[j]-b[j])+abs(a[i]-b[j])+abs(b[i]-a[j]);
}
int main() {
    cin>>T;
    while(T--){
        cin>>n;
        ans=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        for(int i=1;i<=n;i++) ans+=abs(a[i]-b[i]);
        f=ans;
        for(int i=1;i<=n;i++){
            if(max(a[i],b[i])<max(a[mi],b[mi])) mi=i;
            if(min(a[i],b[i])>min(a[mj],b[mj])) mj=i;
        }for(int i=1;i<=n;i++) ans=max({ans,f+hhh(i,mi),f+hhh(i,mj)});
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：_ZML_ (赞：2)

# 思路

容易发现，如果 $a_i>b_i$ 则将 $a_i$ 和 $b_i$ 交换。

在数轴上标出要交换的四个数的位置若线段 $a_ib_i$ 和 线段 $a_jb_j$ 互不相交，此时交换比两条线段处于其他位置时更优。

具体证明这里就不再赘述，其他题解讲的已经很清楚了。

所以只需交换最大的 $a_i$ 和最小的 $b_j$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200010], b[200010];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		int mx=-1e9, mn=1e9;
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		} 
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(a[i]>b[i]) swap(a[i],b[i]);
		} 
		for(int i=1;i<=n;i++) {
			ans+=abs(b[i]-a[i]);
			mx=max(mx,a[i]); mn=min(mn,b[i]);
		}
		if(mx>mn) ans+=2*(mx-mn);
		cout<<ans<<"\n";
	} 
	return 0;
}

```

---

## 作者：Z1qqurat (赞：2)

阿妹胫骨题！对于我这种没有实力切不了 Div2 D 的假蓝钩选手可谓是大有启发。

不要看到 $(a_i, b_i)$ 这种点对就想着二维点对，有一种东西叫做线段。我们以 $\min(a_i, b_i)$ 为左端点，$\max(a_i, b_i)$ 为右端点建立线段，那么一个位置贡献的权值就是该线段长度（$r_i - l_i$）。

考虑线段 $i, j$。显然只有两线段不交的时候它们交换才对答案有贡献，此时 $l_i \le r_i \le l_j \le r_j$，原先是 $[l_i, r_i], [l_j, r_j]$，如果换成 $[l_i, r_j], [r_i, l_j]$ 或者 $[l_i, l_j], [r_i, r_j]$，答案会加上 $2(l_j - r_i)$。你会发现无论 $l, r$ 中哪个才是 $b$，交换 $b_i, b_j$ 一定可以是答案变成最优的情况，所以我们只需要找到最大的一组 $l_j - r_i$ 即可。相当于找到最小的右端点 $R$，最大的左端点 $L$，如果 $L > R$，答案（线段总长）可以加上 $2(L - R)$。然后做完了，复杂度 $\mathcal {O}(\sum n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
int t, n, a[N], b[N], l, r;
ll ans;

void solve() {
    ans = 0, l = -2e9, r = 2e9;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        cin >> b[i]; if(a[i] > b[i]) swap(a[i], b[i]);
        ans += b[i] - a[i];
        l = max(l, a[i]), r = min(r, b[i]);
    }
    if(l > r) ans += 2ll * (l - r);
    cout << ans << "\n";
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}

---

## 作者：pineappler (赞：1)

[安利博客](https://www.luogu.com.cn/blog/pineappler/solution-cf1898d)
## 题面翻译
原翻译意思很明确了，这里再粘一下方便看。

**两个长度均为 $n$ 的数组 $a,b$。一次操作可以选择两个下标 $i,j$，交换 $b_i,b_j$。你需要进行**最多一次**操作，最大化 $\sum \limits_{i=1}^n |a_i-b_i|$。**

## 思路分析
**先说结论：推数学式子+预处理优化**

从头开始分析：
### 暴力
两层循环枚举 $i$，$j$，暴力交换，再求出交换后序列的值，复杂度 $O(n^{3})$。  

核心代码如下：
```cpp
int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			swap(b[i],b[j]);
			int cnt=0;
			for(int k=1;k<=n;k++){
				cnt+=abs(a[k]-b[k]);
			}
			ans=max(ans,cnt);
			swap(b[i],b[j]);//记得换回来 
		}
	}
```
### 优化其一
我们会发现，每次交换的只有那两个值，序列中其他位置对答案的贡献仍然不变。那么我们可以**预处理出原来的答案**，枚举 $b_i$，$b_j$ 时考虑对答案的影响。  

具体地，交换 $b_{i}$，$b_{j}$ 后得到的答案即为：原答案（```cur```）减去两个点对原答案的贡献，加上交换后两个点对原答案的贡献。

核心代码如下：
```cpp
int cur=0,ans=0;
for(int i=1;i<=n;i++) cur+=abs(a[i],b[i]);
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
			int now=cur-abs(a[i]-b[i])-abs(a[j]-b[j])+abs(a[i]-b[j])+abs(a[j]-b[i]);
			ans=max(ans,now);
            
	}
}
```
### 优化其二
**————正片开始————**

由于绝对值符号不利于继续推式子，手动枚举几组 $b_i$，$b_j$，$a_i$，$a_j$ 的大小情况观察对答案的影响（由于已知几个数的大小情况，优化一中用的公式可以化简绝对值符号）。  

因为 $i$ 与 $j$，$a$ 与 $b$是对称的，所以默认 $a_i$ 最小。

根据小学知识可得：
- 当 $a_i < a_j < b_i < b_j$ 时：$now \gets cur$

- 当 $a_i < a_j < b_j < b_i$ 时：$now \gets cur$

- 当 $a_i < a_j < b_i < b_j$ 时：$now \gets cur-2\times(b_i-b_j)$

- 当 $a_i < b_j < a_j < b_i$ 时：$now \gets cur-2\times(a_j-b_j)$

- 当 $a_i < b_i < a_j < b_j$ 时：$now \gets cur+2\times(a_j-b_i)$

- 当 $a_i < b_i < b_j < a_j$ 时：$now \gets cur+2\times(b_j-b_i)$

舍去收益为负或没有收益的情况（如果这样我大可以不换），并考虑 $a_i$ 和 $b_i$ 大小的不同情况（$a$ 和 $b$ 是对称的，直接把$a$，$b$ 对调就是 $b$ 的式子），得到：
- 当 $a_i < b_i < a_j < b_j$ 时：$now \gets cur+2\times(a_j-b_i)$

- 当 $a_i < b_i < b_j < a_j$ 时：$now \gets cur+2\times(b_j-b_i)$

- 当 $b_i < a_i < b_j < a_j$ 时：$now \gets cur+2\times(b_j-a_i)$

- 当 $b_i < a_i < a_j < b_j$ 时：$now \gets cur+2\times(a_j-a_i)$

观察这些式子，很容易发现一个重要的结论！

**交换 $b_i$，$b_j$ 后对答案的影响就是 $a_j$，$b_j$ 中的最小值减去 $a_i$，$b_i$ 中的最大值整体的二倍！**

即
$$now \gets \underset{1 \le i,j \le n}{ \max}2\times(\min(a_j,b_j)-\max(a_i,b_i))$$

虽然直接枚举还是 $O(n^2)$，但这个思路就有优化的空间了！

第一层循环还是枚举 $i$ ，为了让式子整体更大，$\min(a_j,b_j)$ 应该尽可能大。

因为 $\min(a_j,b_j)$ 与 $i$ 无关。所以预处理出前者的最大值和次大值，直接带入即可（需要次大值是因为最大值中的 $j$ 可能就是 $i$，避免自己和自己交换）。

可能有人会有疑问：我们交换的时候也没判断 $a_i$ 和 $b_i$ 是否小于 $a_j$ 和 $b_j$ 啊？

其实，若不满足该情况，算出的贡献是负的或没有贡献，会被自动舍去。若该解法有正贡献，当枚举到 $i$ ， $j$ 正好“对调”时就一定会出现。

至此，此题做完了。
## AC完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=200005,INF=1e9+5;
long long a[N],b[N];
int main(){
	long long T;
	scanf("%lld",&T);
	while(T--){
		long long n;
		scanf("%lld",&n);
		for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(long long i=1;i<=n;i++) scanf("%lld",&b[i]);
		long long ans=0,ori=0;
		long long max1=1,max2=1;
		for(long long i=1;i<=n;i++){
			ori+=abs(a[i]-b[i]);
			long long x=min(a[i],b[i]);
			if(x>min(a[max1],b[max1])){
				max2=max1;
				max1=i;
			}else if(x>min(a[max2],b[max2])){
				max2=i;
			}
		}
		for(long long i=1;i<=n;i++){
			if(i!=max1){
				ans=max(ans,2*(min(a[max1],b[max1])-max(a[i],b[i])));
			}else{
				ans=max(ans,2*(min(a[max2],b[max2])-max(a[i],b[i])));
			}
		}
		printf("%lld\n",ans+ori);
	}
	return 0;
}
```

---

## 作者：Wi_Fi (赞：1)

题解区巨佬都是抽象成线段做的。本蒟蒻直接暴力分类讨论。

由于只能交换一次，我们假设交换涉及到的四个元素分别为 $a_i$，$a_j$，$b_i$，$b_j$，交换前绝对值为 $s1$，交换后绝对值为 $s2$。那么 $s1 = |a_i - b_i| + |a_j - b_j|$，$s2 = |a_i - b_j| + |a_j - b_i|$。

1. 若 $a_i \le b_i \le a_j \le b_j$  
  此时 $s1 = b_i - a_i + b_j - a_j $，$s2 = b_j - a_i + a_j - b_i $。 $s1 - s2 = 2b_i - 2a_j$，$s2$ 更优，所以此时交换更好。

2. 若 $a_i \le a_j \le b_i \le b_j$  
  此时 $s1 = b_i - a_i + b_j - a_j $，$s2 = b_j - a_i + b_i - a_j $。 $s1 - s2 = 0$，交不交换没有影响。

3. 若 $a_i \le a_j \le b_j \le b_i$
  此时 $s1 = b_i - a_i + b_j - a_j $，$s2 = b_j - a_i + b_i - a_j $。 $s1 - s2 = 0$，交不交换没有影响。
  
4. 若 $b_j \le a_i \le b_i \le a_j$
  此时 $s1 = b_i - a_i + a_j - b_j $，$s2 = a_i - b_j + a_j - b_i $。 $s1 - s2 = 2b_i - 2a_i$，所以此时交换更好。
  
5. 若 $a_j \le a_i \le b_j \le b_i$
  此时 $s1 = b_i - a_i + b_j - a_j $，$s2 = b_j - a_i + b_i - a_j $。 $s1 - s2 = 0$，交不交换没有影响。

6. 若 $b_j \le a_i \le b_i \le a_j$
  此时 $s1 = b_i - a_i + a_j - b_j $，$s2 = a_i - b_j + a_j - b_i $。 $s1 - s2 = 2b_i - 2a_i$，所以此时交换更好。
  
由于 $i$ 和 $j$ 不需要区分，所以剩余情况都可不用枚举。

注意到在交换更优的情况下，是 $\max\{a_i,b_i\} \le \min\{a_j,b_j\}$， $\max\{a_j,b_j\} \le \min\{a_i,b_i\}$ 或 $\min\{a_j,b_j\} \le \min\{a_i,b_i\}$ 且 $\max\{a_i,b_i\} \le \max\{a_j,b_j\}$。此时较原序列增加的结果是这四个元素中大小排在中间的两个元素差的绝对值的两倍。然后我们就可以直接循环了。

代码：
```cpp
/*WYF*/
#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX,N=2e5+5;
long long T,i,n,a[N],b[N],mi,ma,ans;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>T;
	while(T--)
	{
		cin>>n;
		mi=INF,ma=-INF,ans=0;
		for(i=1;i<=n;i++)cin>>a[i];
		for(i=1;i<=n;i++)cin>>b[i];
		for(i=1;i<=n;i++)mi=min(mi,max(a[i],b[i])),ma=max(ma,min(a[i],b[i])),ans+=abs(a[i]-b[i]);
		cout<<ans+max(0ll,2*(ma-mi))<<"\n";
	}
	return 0;
}
```


---

## 作者：Iniaugoty (赞：1)

看到两数差的绝对值想到什么？

数轴上两点间距离！

~~想不到请回初一重修。~~

那么就可以把一个 $i$ 对应的 $a _ i, b _ i$ 抽象成一条线段。贡献是所有线段长度之和。

考虑一次操作的影响：

- 如果两线段有重合，两种情况：（黑线是原本的，红线是操作后的）

![](https://cdn.luogu.com.cn/upload/image_hosting/c1i049vy.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/luywa1tm.png)

前者总长会**减少** $2$ 倍的中间部分，后者**不变**。

- 如果两线段没有重合，也有两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/qrlrpjjw.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/w74nnav2.png)

两者都会使总长**增加** $2$ 倍的中间部分。

那么最大化贡献肯定是要从后两种情况下手的（当然如果不存在那种情况，就不做任何操作）。也就是最大化 $2$ 倍的中间部分。容易想到，最长的中间部分的左端点应为 $\min _ {i = 1} ^ {n} \max \{ a _ i, b _ i \}$，右端点应为 $\max _ {i = 1} ^ {n} \min \{ a _ i, b _ i \}$（当然如果这个左端点在右端点的右边，就是不存在那种情况，不做任何操作）。

直接暴力算原本的贡献，再加上这个最大化的增量（可能为 $0$）即可。时空复杂度均为 $\mathcal O (n)$。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 2e5 + 5;
const int inf = 2e9;

int _, n, a[N], b[N];

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> _;
	while (_--) {
		cin >> n;
		F(i, 1, n) cin >> a[i];
		F(i, 1, n) cin >> b[i];
		int l = inf, r = -inf;
		LL sum = 0;
		F(i, 1, n)
			sum += abs(a[i] - b[i]),
			l = min(l, max(a[i], b[i])),
			r = max(r, min(a[i], b[i]));
		cout << sum + max(0, 2 * (r - l)) << "\n";
	}
	return 0;
}
```

---

## 作者：Dovish (赞：1)

## 题意
给定两个序列，求在最多交换一次 $b_i$ 和 $b_j$ 的情况下 求 $\sum_{i-1}^n \lvert{a_i-b_i}\rvert$ 的最大值。

## 思路
对于每一个 $a_i$ 和 $b_i$ 我们将其想象为数轴上的一条线段，答案为线段的总长。则对于我们要交换的两点的线段会有如下情况：

1. 相离：
![](https://cdn.luogu.com.cn/upload/image_hosting/uu1xzuli.png)

可以看出交换之后会多出 $2\times(a_j-b_j)$ 的贡献。

手摸一下也可以发现交换 $a$ 和 $b$ 不影响答案。

2. 相交
![](https://cdn.luogu.com.cn/upload/image_hosting/qeml4141.png)

讨论交换后的两种情况，可以发现，第一种与原先保持不变，第二种还减少了 $2\times(a_j-b_i)$。

3. 包含

![](https://cdn.luogu.com.cn/upload/image_hosting/xk897yn7.png)

我们还是讨论两种情况，结果同上，一样是第一种与原先保持不变，第二种减少 $2\times(a_j-b_i)$。

所以，综上所述，有正贡献的只有相离的情况，且只能做一次贡献。故我们只需要找到相离最远的两条线段。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200010],b[200010];
int T,n;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		for(int i=1;i<=n;i++)
		ans+=abs(a[i]-b[i]);
		int maxn=0,minn=1e18;
		for(int i=1;i<=n;i++)
		{
			maxn=max(maxn,min(a[i],b[i]));
			minn=min(minn,max(a[i],b[i]));
		}//找到最小的右端点和最大的左端点
		cout<<max(ans,ans+2*(maxn-minn))<<'\n';//不要忘了还可以不交换
	}
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
看到题并没有发现交换的两个点的特殊性，所以先打一个暴力看看交换的两个点的特殊性。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

inline int read(){
	register int x = 0, t = 1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48); 
	
		ch=getchar();
	}
	return x*t;
}

int n,a[200009],b[200009];
void todo()
{
	int sum=0,ans=0 ,ll,rr;
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	for(int i=1;i<=n;i++) sum+=abs(a[i]-b[i]);
	ans=sum;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			int now=abs(a[i]-b[j])+abs(a[j]-b[i]),old=abs(a[j]-b[j])+abs(a[i]-b[i]);
//			ans=max(ans,sum+now-old);
			if(ans<sum+now-old)
			{
				ans=sum+now-old;
				ll=j,rr=i;
			}
		}
	}
	cout<<ans<<" "<<ll<<" "<<rr<<endl;
}
signed main()
{
	int T=1;
//	cin>>T;
	while(T--)
	{
		todo();
	}
	return 0;
}
```

对于样例：
```
5
1 2 3 4 5
1 2 3 4 5
```
输出：
```
8 1 5
```
对于样例：
```
3
1 10 10
1 15 20
```
输出：
```
38 2 1
```
不难发现，答案是最小的 $\min(a_i,b_i)$ 和最大的 $\max(a_j,b_j)$ 的差的和的两倍，从数形结合的角度来说，答案就是右端点最左的线段的右端点和左端点最右的线段的左端点交换，多出的部分就是 $({\textstyle \max _{i=1}^{n}}\min (a_i,b_i)-{\textstyle \min_{i=1}^{n}}\max(a_i,b_i))\times 2 $。

最后再加上开始的值，就是：

$$\sum_{i=1}^{n} |a_i-b_i|+({\textstyle \max _{i=1}^{n}}\min (a_i,b_i)-{\textstyle \min_{i=1}^{n}}\max(a_i,b_i))\times 2 $$ 
注意这里 $({\textstyle \max _{i=1}^{n}}\min (a_i,b_i)-{\textstyle \min_{i=1}^{n}}\max(a_i,b_i))$ 可能小于 $0$ 所以最终答案就是：

$$\sum_{i=1}^{n} |a_i-b_i|+\max(0,({\textstyle \max _{i=1}^{n}}\min (a_i,b_i)-{\textstyle \min_{i=1}^{n}}\max(a_i,b_i))\times 2 ) $$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200009],b[200009],
	mx,mn;
long long ans;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		mn=0x3f3f3f3f,mx=-1,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++) ans+=abs(b[i]-a[i]);
		for(int i=1;i<=n;i++)
			mn=min(mn,max(a[i],b[i])),
			mx=max(mx,min(a[i],b[i]));
		cout<<ans+max(0,2*(mx-mn))<<endl;
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
给定两个长度为 $n$ 的数组 $a$、$b$，有至多一次的交换次数，可以交换 $b_i$ 和 $b_j$，我们要使 $\sum_{i=1}^{n}|a_i-b_i|$ 最大。
## 大体思路
这道题主要进行下数学推导，我们分类讨论 $a_i$、$b_i$、$a_j$、$b_j$ 的大小关系不同的情况下对答案的不同贡献，因为带着绝对值不好推导，一共就几种情况，既然 $i$ 与 $j$ 和 $a$ 与 $b$ 可以对称取到，不妨设 $a_i<a_j$，这样我们枚举的情况就更少了。

最后发现如果交换 $b_i$ 和 $b_j$ 的话，舍去贡献小于等于零的情况，对答案的贡献是 $2\times (\min(a_j,b_j)-\max(a_i,b_i))$。

但是我们还要跑一个 $O(n^2)$ 的遍历，遍历一下最大的  $2\times (\min(a_j,b_j)-\max(a_i,b_i))$ 是多少，所以我们考虑再次优化一下。

显然我们要求 $\min(a_j,b_j)$ 更大，$\max(a_i,b_i)$ 更小，所以我们不如直接把 $a_i$ 和 $b_i$ 中大的放在 $b_i$ 上，小的放在 $a_i$ 上，这对答案没有任何影响（答案做了绝对值），这样数组中最大的 $b_i$（$maxx$）就是最大的 $\min(a_j,b_j)$，最小的 $a_i$（$minn$）就是最小的 $\max(a_i,b_i)$。

首先处理所有的 $|a_i-b_i|$，如果 $maxx>minn$，再加上 $2\times(maxx-minn)$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],b[200005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(a[i]>b[i]){
				swap(a[i],b[i]);//便于下面处理 
			}
		}
		long long ans=0,maxx=-INT_MAX,minn=INT_MAX;
		for(int i=1;i<=n;i++){
			ans+=abs(a[i]-b[i]);//正常处理一下 
			maxx=max(maxx,a[i]);
			minn=min(minn,b[i]);//让最大值最小，让最小值最大 
		}
		if(maxx>minn){//判断最大的贡献是不是零贡献或负贡献 
			ans+=2*(maxx-minn);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF1898D)

## 思路

将绝对值之差看成线段长度，易知 $a_i,b_i$ 的顺序不影响答案，因此令 $a_i \le b_i$。

如果两条线段有交集，那么改变端点并不会改变答案，因此我们只需要更换两条没有交集且距离最远的线段即可。

所以我们求出最靠右的左端点 $l$ 和最靠左的右端点 $r$，若 $l > r$，则说明这两条线段没有交集，更换这两个端点；否则不进行操作。

然后直接算出答案。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 2e5 + 5;

LL t, n, a[kMaxN], b[kMaxN], mn = 2e9, mx = -2e9, ans;

int main() {
  for (cin >> t; t; t--, mn = 1e18, mx = -1e18, ans = 0) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i], (b[i] < a[i]) && (swap(a[i], b[i]), 1);
    }
    for (int i = 1; i <= n; i++) {
      mn = min(mn, b[i]), mx = max(mx, a[i]);
    }
    if (mn <= mx) {
      ans = mx + mx - mn - mn;
    }
    for (int i = 1; i <= n; i++) {
      ans += b[i] - a[i];
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

将 $a,b$ 转换成一条条线段后，对于所有的 $(i,j)$，有以下几种情况：

1. ![](https://cdn.luogu.com.cn/upload/image_hosting/geyuvqcj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

交换后：

![](https://cdn.luogu.com.cn/upload/image_hosting/mnbo6awl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

没变。

2. ![](https://cdn.luogu.com.cn/upload/image_hosting/mnbo6awl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

交换后：

![](https://cdn.luogu.com.cn/upload/image_hosting/geyuvqcj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

没变。

3. ![](https://cdn.luogu.com.cn/upload/image_hosting/63q46xv5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

交换后：

![](https://cdn.luogu.com.cn/upload/image_hosting/9xdq2og5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

多了 $2\times (a_j-b_i)$。

所以答案为 $\sum\limits_{i=1}^{n}|a_i-b_i|+\max\limits_{i=1}^n a_i-\min\limits_{i=1}^{n}b_i$，复杂度 $O(n)$。

---

## 作者：joe_zxq (赞：0)

# Part 1 题目翻译

给定两个长度为 $n$ 的序列 $a$ 和 $b$，你可以进行**至多一次**操作：

- 选择两个下标 $i$ 和 $j$ 满足 $1 \le i < j \le n$，交换 $b_i$ 和 $b_j$。

你需要最大化 $\sum \limits_{i=1}^n |a_i-b_i|$，请求出这个最大值。

# Part 2 解法思路

这道题的核心在于，我们可以将两个数 $x$ 和 $y$ 的差的绝对值转化为一条左右端点分别是 $x$ 和 $y$ 的线段的长度。

于是我们研究的问题便转化为将一条左右端点是 $a_i$ 和 $b_i$ 的线段和一条左右端点是 $a_j$ 和 $b_j$ 的线段变为一条左右端点是 $a_i$ 和 $b_j$ 的线段和一条左右端点是 $a_j$ 和 $b_i$ 的线段后两条线段长度和增加了多少。我们可以对下面三种情形进行分类讨论：

- 当两条线段有公共部分但不存在包含关系时，长度和不变或者减少原来公共部分长度的两倍。
- 当两条线段存在包含关系时，长度和不变或者减少原来较短线段长度的两倍。
- 当两条线段没有公共部分时，长度和增加原来两线段之间的距离的两倍。

因此，为了让长度和增加，必须选择第三种情形。我们需要最大化选择的两线段之间的距离。

代码实现很简单，此处不加以赘述。

# Part 3 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, a[200024], b[200024], l = 1e18, r = 0, ans = 0;

void solve() {
	cin >> n;
	l = 1e18, r = 0, ans = 0;
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (ll i = 1; i <= n; i++) {
		cin >> b[i];
		ans += abs(a[i] - b[i]);
		l = min(l, max(a[i], b[i]));
		r = max(r, min(a[i], b[i]));
	}
	ans += max(0ll, (r - l) * 2);
	cout << ans << endl;
}

int main() {

	ll tc;
	cin >> tc;
	while (tc--) {
		solve();
	}

	return 0;
}
```



---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据，给定两个长 $n$ 的数列 $a,b$。至多交换一次 $b_i,b_j(1\le i,j\le n)$ 最大化 $\sum\limits_{i=1}^n |a_i-b_i|$。
# 思路
首先，各位应该知道，$|a-b|$ 其实可以理解为数轴上 $a$ 和 $b$ 的距离。

交换的行为涉及了四个数 $a_i,b_i,a_j,b_j$，可以抽象成数轴上的四个点。然后本来的 $|a_i-b_i|$ 和 $|a_j-b_j|$ 在数轴上也就是点 $a_i$ 和 $b_i$ 的连线以及 $a_j$ 和 $b_j$ 的连线变成了点 $a_i$ 和 $b_j$ 的连线以及 $a_j$ 和 $b_i$ 的连线。

这样的变化只有一种情况是可以使得 $b_i,b_j(1\le i,j\le n)$ 变大，就是当点 $a_i$ 和 $b_i$ 的连线以及 $a_j$ 和 $b_j$ 的连线没有重叠时。

这个结论很好证明。画个数轴，随便选两条不重合的线段，令两线段端点依次分别为 $A,B,C,D$，然后将四个点重新两两分组相连，那么线段总长度就从 $|AB|+|CD|$ 变成了 $|AC|+|BD|$ 或者 $|AD|+|BC|$，增加的总长一定是两倍的 $|BC|$。

所以如果要最大化 $b_i,b_j(1\le i,j\le n)$，定要找类上文中最大的 $|BC|$ 段。同时我们知道类点 $C$ 的点其实就是某线段的右端点，而类点 $B$ 的点就是某线段的左端点，最大化 $|BC|$ 就是最大化 $C$ 以及最小化 $B$。

所以我们只要求 $\max\limits_{i=1}^n(\min(a_i,b_i))$ 即为最大的 $C$，和 $\min\limits_{i=1}^n(\max(a_i,b_i))$ 即为最小的 $B$，这样 $|BC|$ 就一定是最大的。

最后判断是否 $B$ 在 $C$ 的左端，如果在右端说明无法使得 $\sum\limits_{i=1}^n |a_i-b_i|$ 变大。因为这种情况的出现只能说明一件事，$\min\limits_{i=1}^na_i\ge \max\limits_{i=1}^nb_i$ 或者 $\min\limits_{i=1}^nb_i\ge \max\limits_{i=1}^na_i$。
# 实现
```cpp
#include<iostream>
#include<math.h>
#define N 200005
#define int long long
using namespace std;
int t,n,a[N],b[N],sum,Max,Min;
signed main(){
	scanf("%lld",&t);
	while(t--){Max=0;Min=1e9;sum=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++){
			scanf("%lld",&b[i]);
			sum+=abs(a[i]-b[i]);
			Max=max(Max,min(a[i],b[i]));
			Min=min(Min,max(a[i],b[i]));
		}printf("%lld\n",max(0ll,(Max-Min)<<1)+sum);
	}	
	return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

# 题意：

给定两个长度为 $n$ 的数组 $a,b$ 。我们可以进行 **至多一次**的操作，每次操作可以交换 $b_i$ 和 $b_j$。 询问 $\sum^{n}_{i=1}{|a_i-b_i|}$ 的最大值。

# 思路：

考虑建图转换问题，把每一对 $(a_i,b_i)$ 当做一条线段，该线段的左端点为 $\min{(a_i,b_i)}$，右端点为 $\max{(a_i,b_i)}$，在后文中分别叫做 $lef_i$ 与 $rig_i$。

转化问题为图中线段总长度最大值。

考虑交换后对于答案的影响。任意选取两条线段 $i,j$，明显的，有三种情况。

- $lef_i \le rig_i < lef_j \le rig_j$

- $lef_i \le lef_j \le rig_i < rig_j$

- $lef_i \le lef_j \le rig_j \le rig_i$

因为 $i,j$ 可以交换且顺序不定，所以这三种仅仅是本质不同，分别对应为。

- 不相交

- 部分相交

- 包含

考虑这三种情况交换后对于答案的贡献，可以发现分别为。

- $+ 2\times(lef_i-rig_j)$

- $- 2\times(rig_i-lef_j)$

- $- 2\times(rig_j-lef_j)$

可以发现仅有两条线段不相交的时候对于答案是有正贡献的，而这个贡献最大就是 $2\times(\max(lef)-\min(rig))$。

然后我们就可以 $O(n)$ 求出答案了。

# code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[200010];
int b[200010];
int rig,lef;
long long ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		rig=INT_MAX;lef=ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}	
		for(int i=1;i<=n;i++){
			cin>>b[i];
			rig=min(rig,max(a[i],b[i]));
			lef=max(lef,min(a[i],b[i]));
			ans+=abs(a[i]-b[i]);
		}
		cout<<(rig>=lef?ans:ans+2*(lef-rig))<<endl;
	}
}
```

---

## 作者：huangrenheluogu (赞：0)

翻译已经比较好了，直接进入正题。

考虑两对数，$a_i,a_j,b_i,b_j$，看看是不是需要交换。

由于 $a_i,a_j,b_i,b_j$ 的顺序有很多情况，所以我们举两种典型情况。

- 情况一：$a_i\le b_i\le a_j\le b_j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/e39r7yz5.png)

发现 $(a_i,b_i),(a_j,b_j)$（蓝色）劣于 $(a_i,b_j),(a_j,b_i)$（红色）。

- 情况二：$a_i\le a_j\le b_i\le b_j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/auq9gpyf.png)

发现此时交换 $i,j$ 没有影响。

其他情况其实差不多，大家可以自己手摸一下，在题解里就不赘述了。

经过手摸几组，发现题意可以转化为 $l_i$ 是 $\min\{a_i,b_i\}$ 到 $\max\{a_j,b_j\}$ 的线段，我们需要不相交的线段 $l_i,l_j$（$l_j$ 在 $l_i$ 右侧），交换之后对结果的贡献就是 $l_i$ 右端点和 $l_j$ 左端点距离的两倍。

所以我们就可以贪心了，用最大的 $l$ 和最小的 $r$ 匹配。

然后代码就比较简洁了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, inf = 1e18;
int n, T, r, l, ans;
struct data{
	int x, y;
	inline void dd(){
		if(x > y) swap(x, y);
	}
}a[N];
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld", &n);
		ans = 0ll;
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].x);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].y);
		for(int i = 1; i <= n; i++) a[i].dd();//由上面的分析，不妨 x < y，不影响
		l = -inf, r = inf;
		for(int i = 1; i <= n; i++){
			l = max(l, a[i].x);
			r = min(r, a[i].y);
			ans += a[i].y - a[i].x;
		}
		ans += max(0ll, l - r) * 2;
		printf("%lld\n", ans);
	}
	return 0;
}
```

由于洛谷上目前是 UKE，但是 CF 上过了，所以放一下提交记录。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ebi2lxt.png)

upd：洛谷上过了。

---

