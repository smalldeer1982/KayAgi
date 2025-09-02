# Two Colors

## 题目描述

Monocarp 决定按照以下规则粉刷围栏：
- 每块木板必须被涂上恰好一种颜色；
- 使用的不同颜色总数必须恰好为两种；
- 相同颜色的木板必须形成连续序列，即对于所有被涂成同一颜色的木板对，它们之间不存在被涂成其他颜色的木板。

Monocarp 有 $m$ 种不同的颜料，其中第 $i$ 种颜色的颜料最多可以涂 $a_i$ 块木板。Monocarp 不会购买额外颜料。

你的任务是计算满足 Monocarp 所有描述的愿望的围栏涂色方式数目。两种涂色方式被认为是不同的，当且仅当存在至少一块木板在这两种方式中被涂成不同颜色。

## 说明/提示

第一个测试案例中，存在 $4$ 种不同的涂色方式（木板从左到右的颜色编号序列如下）：
1. $[1, 2, 2, 2, 2]$；
2. $[1, 1, 2, 2, 2]$；
3. $[2, 2, 2, 1, 1]$；
4. $[2, 2, 2, 2, 1]$。

第二个测试案例中，存在 $6$ 种不同的涂色方式（木板从左到右的颜色编号序列如下）：
1. $[1, 2, 2, 2, 2]$；
2. $[1, 1, 2, 2, 2]$；
3. $[1, 1, 1, 2, 2]$；
4. $[2, 2, 1, 1, 1]$；
5. $[2, 2, 2, 1, 1]$；
6. $[2, 2, 2, 2, 1]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5 2
2 4
5 2
3 4
12 3
5 9 8```

### 输出

```
4
6
22```

# 题解

## 作者：juruo_zhuyl (赞：9)

# CF2075C题解

[题目传送门](https://www.luogu.com.cn/problem/CF2075C)

[更差的阅读体验](https://www.luogu.com.cn/article/kp32s4vv)

## 题意：

有一排木板，要给它们上色，只能恰好染两种颜色，每种颜色最多可以涂 $a_i$ 块木板，相同颜色必须连续，求有几种染色方式。

## 思路：

先考虑暴力枚举两种颜色 $(i,j)$，判断 $a_i+a_j\ge n$ 是否满足，如果满足，$ans\leftarrow ans+\min(a_i,a_j)$ 最后输出 $ans$。时复 $O(n ^ 2)$。

~~炸得很惨。~~

不难发现，时间瓶颈主要在枚举 $j$ 上，那如何优化呢？

我们可以考虑二分，因为在排序后可以发现，如果 $a_i+a_j\ge n$ 则 $a_i+a_{j + 1}\ge n$ 一定满足。

所以开始优化：
   1. 先排序。
   2. 枚举 $i$。
   3. 二分一个分界点 $R$ 使得 $a_i+a_R\ge n$ 则 $j\ (R\le j\le n)$ 满足 $a_i+a_j\ge n$。

还是太慢。

然后则么优化呢？

不难发现，对于每个 $i$ 和 $j$，贡献为 $a_i-(n-a_j-1)$。但必须满足：$1\le a_i<n$。

其余见代码。

时复 $O(n\log n)$。

## AC Code：


```cpp
#include<bits/stdc++.h>
using namespace std;

long long T, n, m, ans, a[200010], b[200010];

signed main() {
	scanf("%lld", &T);
	while(T--){
		ans = 0;//多测不清空，写完见祖宗 
		scanf("%lld%lld", &n, &m);
		for(int i = 1; i <= m; i++){
			scanf("%lld", &a[i]);
		}
		sort(a + 1, a + m + 1);
		for(int i = m; i >= 1; i--){
			if(a[i] >= n){
				a[i] = n - 1;//处理a[i] >= n 
			}else{
				break;
			}
		}
		b[m + 1] = 0;//多测不清空，写完见祖宗 
		for(int i = m; i >= 1; i--){
			b[i] = b[i + 1] - (n - a[i] - 1);//前缀差处理 
		}
		for(int i = 1; i <= m; i++){
			if(a[i] < n){
				int L = i, R = m + 1;//二分 
				while(L + 1 < R){
					int mid = (L + R) / 2;
					if(a[i] + a[mid] >= n){
						R = mid;
					}else{
						L = mid;
					}
				}
				long long t = a[i] * (m - R + 1);//计算 
				t += b[R];
				t *= 2;
				ans += t;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

莫抄袭，没了AC记录，空悲切！！！

---

## 作者：NEKO_Daze (赞：4)

[洛谷CF2075C](https://www.luogu.com.cn/problem/CF2075C) || [CodeForces 2075 C](https://codeforces.com/contest/2075/problem/C)

### 简要题意
对于一个长度 $n$ 空白方格，有 $m$ 种颜色的颜料，第 $i$ 种颜料可以对 $a_i$ 个连续格子染色。选取两种颜色 $x,y$，并将方格分为两半，左边全涂为颜色 $x$，右边全涂为颜色 $y$。求不同的方案数。

### 思路
对于方格中的断点 $k\in[1,n)$，前有 $k$ 个格子，后有 $n-k$ 个格子。将数组 $a$ 排序后，用 `lower_bound` 很容易找出满足 $a_i\ge k$ 或 $a_j\ge n-k$ 的颜料个数 $x,y$，根据乘法原理可知总共有 $xy$ 种可能，但由于两种颜色应不同，所以还需减去 $\min(x,y)$ 种情况，所以最后答案为 $xy-\min(x,y)$。时间复杂度 $O(t\times(n+m)\log m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int a[200005];
        for (int i = 0; i < m; ++i)
        {
            cin >> a[i];
        }
        sort(a, a+m);
        long long ans = 0;
        for (int k = 1; k < n; ++k)
        {
            long long x = m - (lower_bound(a, a+m, k) - a);
            long long y = m - (lower_bound(a, a+m, n-k) - a);
            ans += x * y - min(x, y);
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：ztd___ (赞：3)

虽然但是，黄题爆标没啥意义其实。

现有的题解和官方题解都是 $O((n + m) \log m)$ 的。  
我们来点线性做法。

通过题目的限制，很容易发现，染色情况必然是下面的情况。  
![](https://cdn.luogu.com.cn/upload/image_hosting/n0bcudzp.png)

这是因为如果两种颜色交替地涂，就满足不了“相同颜色的木板必须形成连续序列”这一要求了。

于是想到枚举中间间隔的那个位置，然后看左边能涂什么颜色，右边能涂什么颜色。

题目告诉我们有涂色次数的限制。即对于长度为 $k$ 的颜色段，只有 $a_i \ge k$ 的颜色 $i$ 才能涂。

因为 $1 \le a_i \le n$，所以容易想到用桶存储颜色。具体地，用 $s_j$ 表示 $a_i = j$ 的颜色 $i$ 的个数。

然后，碰到长度为 $k$ 的颜色段时，能在上面涂的颜色数量就是桶里边从 $k$ 到 $n$ 的颜色数量之和。即 $\sum_{i=k}^{n} s_i$。

这个东西可以**后缀和预处理**。

然后回到枚举的过程，假设我们枚举的这个点为 $i$，则左边区间（即区间 $[1, i]$）的长度就是 $i$，右边区间（即区间 $[i + 1, n]$）的长度就是 $n - i$。这样，能涂在左边的颜色数量和能涂在右边的颜色数量就可以求出来了。

设能涂在左边的颜色数量为 $c$，能涂在右边的颜色数量为 $d$。那么，方案数就是 $c \times d$。但是有可能两边的颜色相同，我们要排除这种情况。

令 $e = \max(c, d)$，$f = \min(c, d)$。因为能涂长段的颜色肯定也可以涂短段，所以对于 $e$ 里面包含的每种颜色，$f$ 里面必然也是包含的。

这样一来，$e$ 里面的每种颜色，只能与 $f$ 里面与自己不相同的 $f - 1$ 中颜色一起涂在木板上。所以这部分的方案数就是 $\sum_{i=e}^{n} s_i \times \sum_{i=f-1}^{n} s_i$。

代码很好写。注意后缀和数组的清空。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 55;
int n, m, a[N], s[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1;i <= n + 1;i++) s[i] = 0;
		for (int i = 1;i <= m;i++) {
			cin >> a[i];
			s[a[i]]++;
		}
		for (int i = n;i >= 1;i--) {
			s[i] += s[i + 1];
		}
		int ans = 0;
		for (int i = 1;i < n;i++) {
			int c = i, d = n - i;
			int e = max(c, d), f = min(c, d);
			ans += s[e] * (s[f] - 1);
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：WYX1210 (赞：1)

### 思路 
将 $a$ 数组排序，二分找出满足 $a_i \geq k$ 且 $a_j \geq n-k$ 的颜料数 $x,y$，总的方案数为 $xy$，由于不能选择同一个颜色，需要去掉 $\min(x,y)$ 种，所以方案数为 $xy - \min(x,y)$。

因为 $k$ 的取值为 $[1,n)$，所以遍历一遍即可。时间复杂度为 $O(n \log n)$。

---

## 作者：cflsfzh (赞：1)

看完这道题，先考虑只对于两个数字 $a$ 和 $b$ 来计算它们之间的贡献，显然就是 $b-(n-a-1)$ 或者是 $a-(n-b-1)$，于是是不是就做完了呢？但是，你不能很容易的 $O(n)$，至少我用的是 $O(n \log n)$。为什么？因为你发现这个计算贡献的公式是有限制的：
1. $a_i$ 的范围必须满足 $1 \leq a_i < n$。
2. $a$ 和 $b$ 必须满足贡献至少为 $1$，即满足 $a+b \geq n$。

所以，为了方便，我们可以从小到大排个序，对于当前枚举到的位置 $i$，用二分找到第一个满足要求二的点后，将贡献式子拆成 $a$ 和 $-(n-b-1)$ 两部分，第一部分显然，第二部分用前缀和维护即可，可以 $O(1)$ 算出。对于满足要求一，显然可以在输入时就处理。

最终时间复杂度 $O(n \log n)$。

[AC code。](https://codeforces.com/contest/2075/submission/311192122)

---

## 作者：A_R_O_N_A (赞：1)

大家好啊，我是 DS 魔怔人，所以我赛时拿 DS 无脑创过了这道题。

## 题意

你需要为 $n$ 个点涂色，你总共有 $m$ 个颜料，每个颜料最多可以涂 $a_i$ 个点，涂色需要满足以下要求：

1. 一个点只能涂一种颜色。
1. 需要使用**恰好两种颜色**涂色。
1. 同一种颜色必须形成一个连续的段。

## 思路

挺无脑的，我们可以遍历每一种颜色，然后钦定这个颜色为我们的**第一种颜色**，也就是涂色区间应该是从第 $1$ 号点开始一直涂到第 $x$ 号点，剩下的第 $x+1\sim n$ 号点涂另外一种颜色。那么很明显，如果一个颜色能涂 $a_i$ 个点，那么它能够涂的点的个数区间就是 $[1,a_i]$，但是这里要注意，如果 $a_i=n$，那么它能够涂的点的个数区间应该是 $[1,a_i-1]$，因为题目要求涂恰好两种颜色。那么另外的一个颜色为了把所有点涂满，它的涂的点的个数区间应该就是 $[n-a_i,n-1]$，当然注意一下 $a_i=n$ 的特殊情况即可，此时为 $[1,n-1]$。换言之只要其他的 $a_i$ 的值域满足 $[n-a_i,n-1]$，那么这个 $a_i$ 就能对当前我们钦定的颜色产生贡献。贡献就是 $a_i$ 与这个区间的交的整数数量。

然后我们就可以使用权值树状数组愉快地 AC 掉本题了。

当然，计算贡献的时候记得排除掉钦定的这个点的贡献。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
mt19937 myrand(time(0));
inline ll read(){
	ll x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*w;
}
void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	static int sta[35];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top)putchar(sta[--top]+'0');
}
ll n,m,t1[200005],t2[200005],a[200005];
inline ll lowbit(ll x){return x&(-x);}
void _add(ll x,ll k){
	ll val=x*k;
	while(x<=n){
		t1[x]+=k;
		t2[x]+=val;
		x+=lowbit(x);
	}
}
ll sum(ll *t,ll x){
	ll ret=0;
	while(x){
		ret+=t[x];
		x-=lowbit(x);
	}
	return ret;
}
void add(ll l,ll r,ll k){_add(l,k);_add(r+1,-k);}
ll Q(ll l,ll r){
	return (r+1)*sum(t1,r)-l*sum(t1,l-1)-(sum(t2,r)-sum(t2,l-1));
}
inline void work(){
	n=read();m=read();ll ans=0;
	for(int i=1;i<=n;i++)t1[i]=t2[i]=0;
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++)add(1,a[i],1);
	for(int i=1;i<=m;i++){
		add(1,a[i],-1);
		ans+=Q(max(n-a[i],1ll),n-1);//注意特殊情况
		add(1,a[i],1);
	}
	write(ans);puts("");
}
int t;
int main(){
	t=read();
	while(t--)work();
	return 0;
}
```

[提交记录](https://codeforces.com/contest/2075/submission/311120569)。

---

