# [ABC402D] Line Crossing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc402/tasks/abc402_d

在圆周上等间距地排列着 $N$ 个点，按顺时针方向依次编号为 $1,2,\ldots,N$。

有 $M$ 条互不相同的**直线**，其中第 $i$ 条直线通过两个不同的点：点 $A_i$ 和点 $B_i$（$1 \leq i \leq M$）。

请计算满足以下两个条件的整数对 $(i,j)$ 的个数：

1. $1 \leq i < j \leq M$
2. 第 $i$ 条直线与第 $j$ 条直线相交

## 说明/提示

### 约束条件

- $2 \leq N \leq 10^6$
- $1 \leq M \leq 3 \times 10^{5}$
- $1 \leq A_i < B_i \leq N$（$1 \leq i \leq M$）
- $(A_i,B_i) \neq (A_j,B_j)$（$i \neq j$）
- 输入中的所有数值均为整数

### 样例解释 1

如图所示，圆周上有 $8$ 个点和 $3$ 条直线：  
![](https://img.atcoder.jp/abc402/82c44ea5d5dd6546c7c8f32447490107.png)  
- 第 $1$ 条直线与第 $2$ 条直线相交  
- 第 $1$ 条直线与第 $3$ 条直线不相交  
- 第 $2$ 条直线与第 $3$ 条直线相交  

满足条件的整数对为 $(i,j)=(1,2),(2,3)$，因此输出 $2$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8 3
1 5
1 8
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
5 10
2 5
1 5
1 2
2 4
2 3
1 3
1 4
3 5
3 4
4 5```

### 输出

```
40```

# 题解

## 作者：chinazhanghaoxun (赞：1)

## 题意
如题目翻译。
## 分析
由于两条直线只有相交与平行这两种情况，而相交更为复杂，所以我们考虑平行的情况，观察这张图。
![图片](https://cdn.luogu.com.cn/upload/image_hosting/pln8z10p.png)
不难发现，如果平行，两条直线经过编号的和为 $1+4=5$ 和 $2+3=5$，于是推测两条直线的和相等时平行。而观察左侧两条，为 $1+4=5$ 和 $6+5=11$，$11\bmod 6=5$。因此，可以得到结论：
>经过的编号和模总点数相等的几条直线互相平行。

因此，只需要将模后的数相同的归到一起，最后将当前直线数减去与它平行的数量就是相交数量，代码易写。
## 代码
### 数组定义
$s$ 表示这一类平行一共有多少条。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, M = 3e5 + 5;
int n, m;
int a[M], b[M], s[N];
bool p[N];
long long ans;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> a[i] >> b[i];           
        s[(a[i] + b[i]) % n] ++; //个数加一
        ans += i - s[(a[i] + b[i]) % n]; //去除与这条直线平行的就是相交的
    }
    cout << ans;
    return 0;
}
```

---

## 作者：wyyinput (赞：1)

![样例一图片](https://img.atcoder.jp/abc402/82c44ea5d5dd6546c7c8f32447490107.png)

样例一图片。

## 思路
观察样例一图片，$1,5$ 和 $2,4$ 这两组线平行。有什么规律呢？不难发现，它们的和为 $6$。这比较好理解。

但，$1,5$ 和 $6,8$ 不也平行吗？不要慌。样例一有 $8$ 个点，而 $6+8$ 模 $8$ 后也是 $6$。所以我们有一个猜想，两点之和对总点数取模后相等的线互相平行。

一条直线平移到另一处，两个数模 $n$ 后一个 $+a$，一个 $−a$，刚好抵消。所以判断直线平行只需要算模 $n$ 的余数即可。我们可以用样例二验证，发现规律就是对的。

统计完平行，又怎么办？假设有 $k$ 条线互相平行，那么每条线都会与剩下的 $n-k$ 条线产生交点。所以它们的贡献就是 $k(n-k)$。注意每个交点会被两条直线统计，所以答案要减半。我采用桶记录平行线的数量。

时间复杂度 $O(n)$，跑得飞快。

于是代码就出来了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,t[1000000];
long long ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
 		scanf("%d%d",&a,&b);
		if(a+b>=n)
			++t[(a+b)%n];
		else
			++t[a+b];
  	}
	for(int i=0;i<n;i++){
	    if(t[i]){
	        ans+=t[i]*(m-t[i]);
	    }
	}
	printf("%lld\n",ans/2);
	return 0;
}
```
[AC记录](https://atcoder.jp/contests/abc402/submissions/65216268)

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc402_d [ABC402D] 线相交 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc402_d)

### 题目大意

有一个圆上有 $N$ 个等距点顺时针标为 $1,2,\ldots,N$，有 $M$ 条不同的直线，其中 $i$ 条线经过点 $A_i$ 和 $B_i$。有多少对线相交。

### 思路及实现

显然，问题转化为求平行更容易，因为同一平面内不是平行就一定相交，而一般来说，相交更普遍、容易出现。如何判断平行？如果枚举 $i,j$ 那就和枚举相交一样了。这里发现如果 $l_1 \mathrel{/\negmedspace/} l_2$，$l_1 \mathrel{/\negmedspace/} l_3$，那么 $l_2 \mathrel{/\negmedspace/} l_3$。如果有 $c$ 条线都互相平行，且没有更多线和它们平行，它们对于平行的就是 $\frac{c(c-1)}{2}$。答案就是 $\frac{M(M-1)}{2}$ 减去所有的平行贡献。

一种想法是斜率相等的线平行，计算 $A_i$ 和 $B_i$ 的坐标即可，但是对于 $N$ 的各种情况，这个坐标并不好算。当时我放弃了这个想法，有兴趣的读者可以尝试。

另一个简单的想法是对于所有线进行同一种操作，就是不断做平行于这个线的线，使所有互相平行的线最终都重合。如何做平行还要保证能归合到同一情况呢？记经过 $i$ 和 $j$ 点的直线是 $(i-1,j-1)$，把 $(i,j)$ 变成 $((i - 1 + N) \bmod N,(j + 1) \bmod N)$ 在大多数情况下是平行或重合原来的直线的，除非 $(i + 2) \bmod N = j$。不断重复，直到 $(i + 1) \bmod N = j$ 或者 $(i + 2) \bmod N = j$。

但是更好的做法是，发现上述变化前后，$i+j \equiv i - 1 + N + j + 1 \pmod N$。所以，所有互相平行的直线，$(i+j) \bmod N$ 都是相等的。现在，可以通过 $(i+j) \bmod N$ 表示 $(i,j)$ 的斜率了。统计每个 $(i+j) \bmod N$ 的直线数量即可。

时间复杂度 $O(N + M)$，空间复杂度 $O(N)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M, A, B, cnt[1000005], ans;
int main()
{
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= M; i++)
    {
        scanf("%lld%lld", &A, &B);
        cnt[(A + B) % N]++;
    }
    ans = M * (M - 1) / 2;
    for (int i = 0; i <= N - 1; i++)
        ans -= cnt[i] * (cnt[i] - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC402D] Line Crossing

对于两根线，两端点编号相加模 $N$ 结果相同和两线平行是充要条件。

将圆视作一个数轴，那么这两个端点到 $\frac{(A_i+B_i)\bmod N}{2}$ 的弧长是相等的，根据初中几何，我们能很容易推出这条弦与这条直径所在直线垂直。因此两端点编号相加模 $N$ 结果相同意味着两条弦与同一条直线垂直，即两线平行。

反之，两线平行，即两条弦与同一条直线垂直，那么一定存在一条直径满足同时与两条弦垂直。根据初中几何，我们能很容易推出对于每条线段两个端点到某个定点的弧长是相等的。即两端点编号相加模 $N$ 结果相同成立。

因此以 $(A_i+B_i)\bmod N$ 为属性值，求属性值不同的数对个数即可。具体的，记录每个属性值线段的个数，累加的时候加上与它属性值不同的线段个数即可。每个数对会被计数两次，输出一半即可。

## [Code](https://atcoder.jp/contests/abc402/submissions/65015148)

---

## 作者：small_lemon_qwq (赞：0)

显然，不平行的两条线一定相交，那么问题就变成了求斜率相同的线的对数，可以给斜率开一个桶，有手就行。

考虑到一条连接 $(a,b)$ 直线的斜率和 $(a+b)\bmod n$ 一一对应，所以可以给 $(a+b)\bmod n$ 开桶。

举个例子，比如一条连接 $(3,5)$ 的直线，现在我们想要知道 $2$ 连接什么能和这条直线平行，显然要连接 $6$，但是如果 $n=5$，就应该连接 $1$，但是显然满足 $(a+b)\bmod n$ 是相同的，所以直接给这个开桶就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,b[1000005];
pair<int,int>a[1000005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i].first>>a[i].second;
		int t=(a[i].first+a[i].second)%n;
		b[t]++;
	}
	int ans=m*(m-1)/2;
	for(int i=0;i<=n;i++){
		ans-=b[i]*(b[i]-1)/2;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：LittleAcbg (赞：0)

考虑补集转换。先计算直线的二元组数量，再扣除无交点直线的组数。

两条直线没有交点，就意味着它们平行。观察题目中的图像可以发现，一条直线平移到另一处，其 $A$ 和 $B$ 在模 $N$ 意义下一个 $+1$，一个 $-1$，所以判断直线平行只需要算 $A+B$ 模 $N$ 的余数即可。

但我们不能暴力枚举所有的两条直线，这样太慢了。将直线按 $A+B$ 模 $N$ 的余数分类，同一类的两两分组计算。假设其中一类的直线数量为 $num$，那么其中的平行直线就有 $\dfrac{num\times(num-1)}2$ 条。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+9;
int n,m,a,b,num[N];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &a, &b);
		++num[(a + b) % n]; // 记录 A+B 模 N 的余数
	}
	ll ans = (ll)m * (m - 1) / 2; // 直线二元组数量
	for (int i = 0; i < n; ++i) ans -= (ll)num[i] * (num[i] - 1) / 2; // 统计平行组数
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：fr_dr (赞：0)

## 题目大意
给出一个 $ n $ 等分圆，其上给出 $ m $ 组（每组两个）点的编号构成的直线，求有多少组线是相交的。
## 思路
发现直接考虑较困难，正难则反，发现如果直线两两相交，那么总相交数是好求的，就是求从 $ m $ 条线中选两个的组合，那么现在只需要减去互相平行的组合就行了。考虑如何构造平行线，发现一定是由某个点向两端扩展相同长度对应的点所连成的所有线互为平行线，那么无论这个长度多大其中位数不变。**发现互相平行的线其两端点的中点或在圆上其中点对称点相同**，那么我们可以将中点算出，通过这个判断是否是平行线，那么考虑将比 $ \frac{n}{2} $ 大的中点等效替换为其对称点记为 $ p_i  $ 那么 $ p_i $ 相同的点一定互为平行线计算其所有组合将其从答案中减去即可。
![](https://cdn.luogu.com.cn/upload/image_hosting/fc18kncn.png)
## 代码
```cpp
#include<iostream>
#include<map>
using namespace std;
long long n,m,a,b;
long double p[300010];
map<long double,int> k;
int main(){
	cin>>n>>m;
	long double s=n*1.0/2;
	long long ans=0;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		p[i]=(a*1.0+b*1.0)/2;  
		if(p[i]>s) p[i]-=s;
		ans-=k[p[i]];
		k[p[i]]++; 
	}
	ans+=m*(m-1)/2;
	cout<<ans;
}
```
复杂度应该是 $ O( m ) $ 的吧，若有错误请指正（ ~~bushi~~。

---

