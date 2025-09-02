# Rotation Matching

## 题目描述

After the mysterious disappearance of Ashish, his two favourite disciples Ishika and Hriday, were each left with one half of a secret message. These messages can each be represented by a permutation of size $ n $ . Let's call them $ a $ and $ b $ .

Note that a permutation of $ n $ elements is a sequence of numbers $ a_1, a_2, \ldots, a_n $ , in which every number from $ 1 $ to $ n $ appears exactly once.

The message can be decoded by an arrangement of sequence $ a $ and $ b $ , such that the number of matching pairs of elements between them is maximum. A pair of elements $ a_i $ and $ b_j $ is said to match if:

- $ i = j $ , that is, they are at the same index.
- $ a_i = b_j $

His two disciples are allowed to perform the following operation any number of times:

- choose a number $ k $ and cyclically shift one of the permutations to the left or right $ k $ times.

A single cyclic shift to the left on any permutation $ c $ is an operation that sets $ c_1:=c_2, c_2:=c_3, \ldots, c_n:=c_1 $ simultaneously. Likewise, a single cyclic shift to the right on any permutation $ c $ is an operation that sets $ c_1:=c_n, c_2:=c_1, \ldots, c_n:=c_{n-1} $ simultaneously.

Help Ishika and Hriday find the maximum number of pairs of elements that match after performing the operation any (possibly zero) number of times.

## 说明/提示

For the first case: $ b $ can be shifted to the right by $ k = 1 $ . The resulting permutations will be $ \{1, 2, 3, 4, 5\} $ and $ \{1, 2, 3, 4, 5\} $ .

For the second case: The operation is not required. For all possible rotations of $ a $ and $ b $ , the number of matching pairs won't exceed $ 1 $ .

For the third case: $ b $ can be shifted to the left by $ k = 1 $ . The resulting permutations will be $ \{1, 3, 2, 4\} $ and $ \{2, 3, 1, 4\} $ . Positions $ 2 $ and $ 4 $ have matching pairs of elements. For all possible rotations of $ a $ and $ b $ , the number of matching pairs won't exceed $ 2 $ .

## 样例 #1

### 输入

```
5
1 2 3 4 5
2 3 4 5 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5
5 4 3 2 1
1 2 3 4 5```

### 输出

```
1```

## 样例 #3

### 输入

```
4
1 3 2 4
4 2 3 1```

### 输出

```
2```

# 题解

## 作者：lianchanghua (赞：10)

这一题暴力模拟肯定是不行的，那有什么优化方法吗

首先我们要知道，把 $a$ 数组变为 $b$ 数组的方法跟我们转魔方一样，不能为了拼这面而弄乱了另一面，所以我们要计算一个里面的单个要多少步才可以退推出答案。

所以首要任务就是计算 $a$，$b$ 每个数位置的差值，找到差最大的。

AC 代码

```cpp
#include<bits/stdc++.h>//万能头 
#define int long long//宏定义 
using namespace std;
int a[200010],b[200010],aa[200010],bb[200010],ans[200010];//准备数组 
int n,anss; 
signed main(){
	std::ios::sync_with_stdio(false);//加速 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		aa[a[i]]=i;//计入a 
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		bb[b[i]]=i;//计入b 
		ans[(bb[b[i]]-aa[b[i]]+n)%n]++;//统计距离 
		/*
			我们一点点剥析，
			bb[b[i]]-aa[b[i]]		  即使计算他们的距离差
			(bb[b[i]]-aa[b[i]]+n)%n ，由于减出来可能是负数，所以要加上n，那该如
			何消n呢，在模一下n就好了 
		*/
	}
	sort(ans,ans+1+n);//排序算最大 
	cout<<ans[n]<<endl;//最大即是答案 
	return 0;
}
```


---

## 作者：Refined_heart (赞：2)

题目大意：给定两个排列，每次可以随意选择一个排列进行循环转动，问重合的数最多是多少个。

我们不妨每一次都对$b$排列进行操作。

那么，对于$a$排列的每个数，在$b$中处理出来$b$对应的数移动到$a$对应的数需要多少步数。对步数的出现次数进行维护，答案就是步数的最大出现次数。这对应着操作后最多有多少个$a_i,b_i$相等。

时间复杂度$O(n).$至于处理转动次数，参考代码中细节。

注意还有不转动的情况$(\text{pretest 4}).$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],b[200010],cnt[200010],pos[200010];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),pos[a[i]]=i;
	for(int i=1;i<=n;++i){
		scanf("%d",&b[i]);
		if(i<=pos[b[i]])cnt[pos[b[i]]-i]++;
		else{
			cnt[n-i+pos[b[i]]]++;
		}
	}
	int mx=-1;
	for(int i=0;i<=n;++i)mx=max(mx,cnt[i]);
	printf("%d\n",mx);
	return 0;
}
```


---

## 作者：liuzhongrui (赞：1)

## 思路

首先，左循环移位等同于 $n - 1$ 次右循环移位，调转过来亦是如此（姑且称之为“反之亦然”）。因此，我们只需执行一种类型的移动，比如向右移动。

此外，对 $b$ 进行右循环移位等同于对 $a$ 进行左循环移位，反之亦然。所以我们不需要对 $b$ 进行任何移动。

现在问题简化为在 $a$ 的所有右循环移位中找到最大数量的匹配对。由于 $n$ 次右循环移位后，$a$ 又回到原始状态，因此只有 $n - 1$ 种右循环移位。

由于两个数组都是排列，$a$ 中的每个元素只会与 $b$ 中对应相等的元素匹配一次。例如，如果 $a$ 是 $\{{2, 3, 1\}}$，$b$ 是 $\{{3, 1, 2\}}$，$a$ 中的数字 $3$ 只有在右循环移动一次后才会与 $b$ 中的数字 $3$ 匹配。因此，对于 $a$ 中的每个元素，我们可以找到与其对应相等的元素在右循环移位后匹配所需的次数。如果 $a_i = b_j$，那么只需 $k = j - i$ 次右循环移位，就能使 $a_i$ 与 $b_j$ 匹配。如果 $j - i < 0$，则需要 $n - j + i$ 次移位。

现在，对于每次移位，我们可以找到匹配对的数量，并取最大值。

时间复杂度为 $O(n)$ 或者如果使用映射的话为 $O(n\log{n})$。

## Code

跑得有点慢（映射解法），见谅！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int n;
int a[N], b[N], pos[N];
map<int, int> offset;
signed main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		pos[a[i]] = i;
	}
	for(int i = 1; i <= n; i++)
		cin >> b[i];
	for(int i = 1; i <= n; i++) {
		int cur = pos[b[i]] - i;
		if(cur < 0)
			cur += n;
		offset[cur]++;
	}
	int ans = 0;
	for(auto &it:offset)ans = max(ans, it.second);
	cout << ans;
	return 0;
}
```


---

## 作者：L_shadow (赞：1)

这道题看一眼题面，大概知道只能用 $\Theta(n)$ 或者 $\Theta(n \log_{2} n)$ 解决。

类似于桶（数组 $nowa$），我们可以用 $a_i$ 为下标，储存 $i$，这样查询的时候就只需要 $\Theta(1)$ 的复杂度。

当输入 $b_i$ 时，我们将同一个值（即 $b_i$）在两个序列中对应的下标（即 $i$ 和 $nowa_{b_i}$）的差值，当然，这里的差值可能是负的，那么我们可以通过 $+n$ 再模 $ n$ 得到一个相应的正数，最后再用一个桶记录这个正数，并求这个桶里面的最大值。

关于我为什么不用再跑一次循环：

我们可以在第二个桶记录正数的同时更新最大值，这样，既不用排序，又不用再跑一次循环。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],b[N],nowa[N],nowb[N],ans;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
		nowa[a[i]]=i;//装桶，储存的是相应的位置 
	}
	for(int i=1; i<=n; i++) {
		scanf("%d",&b[i]);
		nowb[(i-nowa[b[i]]+n)%n]++;
		ans=max(ans,nowb[(i-nowa[b[i]]+n)%n]);
        	//在记录桶的同时，更新最大值 
	}
	cout<<ans;
}
```


---

## 作者：whiteqwq (赞：1)

[CF1365C Rotation Matching](https://www.luogu.com.cn/problem/CF1365C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1713360)

## 题意
题意：给定两个排列$a_1,a_2\cdots a_n$与$b_1,b_2\cdots b_n$，可以将$a$循环移动若干次（一次循环移动指将$a_1,a_2\cdots a_n$变为$a_n,a_1\cdots a_{n-1}$），求$a$排列$b$排列最多能有几个匹配（即相同位置的数相同）。

数据范围：$1\leqslant n\leqslant 2\cdot 10^5$。

## 分析
分析数据范围，这道题明显是$O(n)$，最多带上一两个$\log$或一个根号。

考虑循环移动的意义——$a$排列内数字的的相对位置不会改变（将环拆成链来看），同时因为$b$排列不会移动，因此对于原排列$a$与经过若干次操作的排列$a'$，存在一个数$d$（$0\leqslant d\leqslant n-1$）使$a_i=a_{(i+d)\ \bmod\ n}'$，即对于任意一个数$k$（$1\leqslant k\leqslant n$），$k$在$a$中的位置与在$a'$中的位置的距离（注意，这里的距离也是将环拆成链看的距离，后面的距离也是指这种距离）都是相等的。

因此，对于任意一个数$k$（$1\leqslant k\leqslant n$），$k$在$a$中的位置与$k$在$b$中的位置的距离就是使这两个数匹配的移动次数。

于是我们可以记录$1$到$n$所有数在$a$排列与$b$排列中的位置，然后计算他们之间的距离，即使它们匹配的移动次数，并记录每个移动次数的出现次数，最大的出现次数便是答案了。

## 代码
```
#include<stdio.h>
const int maxn=1000005;
int i,j,k,m,n,ans;
int a[maxn],b[maxn],c[maxn],d[maxn],cnt[maxn];
inline int max(int a,int b){
	return a>b? a:b;
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		c[a[i]]=i;
	}
	for(i=1;i<=n;i++){
		scanf("%d",&b[i]);
		d[b[i]]=i;
	}
	for(i=1;i<=n;i++)
		cnt[(c[i]-d[i]+n)%n]++;
	for(i=0;i<n;i++)
		ans=max(ans,cnt[i]);
	printf("%d\n",ans);
	return 0;
}
```

## 后话（可跳过）
一开始看到这道题是不想做的：

![](https://fp1.fghrsh.net/2020/06/08/870cb0675648932d67ac172d9a9fcb03.png)

这个翻译。。。

最后还是看了一下英文题面，发现真的水。。。然后一下子就做出来了。

---

## 作者：TruchyR (赞：0)

容易发现循环左移 $x$ 次等价于循环右移 $n-x$ 次，所以只考虑循环右移。  

下文中的右移次数指小于 $n$ 次的右移，因为每右移 $n$ 次都等于没变。  

由于给定的是排列，所以对于 $a$ 中的每个数只有一种转法可以与 $b$ 中这个数对齐。

具体的，假设 $a$ 中 $i$ 出现的位置是 $A_i$，$b$ 中 $i$ 出现的位置是 $B_i$，旋转了 $x$ 次后对齐，可以得到 $A_i+x \equiv B_i \pmod{n}$，即 $x \equiv B_i-A_i \pmod{n}$。  

上面说过右移次数小于 $n$，所以有 $x=(B_i-A_i) \bmod n$。  

令 $C_i=(B_i-A_i) \bmod n$，问题转化为求 $C$ 中出现次数最多的数，开一个桶记录即可。  

[提交记录](https://codeforces.com/problemset/submission/1365/275083952)，里面的桶写的比较简洁。

---

## 作者：do_while_true (赞：0)

考虑~~奇技淫巧~~`map`

$mp_i$ 表示 $b$ 数组向左移动 $i$ 个单位后的答案，通过记录每一个数在 $a$ 中的位置，然后 $b$ 的数到 $a$ 的位置需要移动几个，把贡献加进 $mp$ 即可。

$\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int T,n,a[200010],b[200010];
int vis[200010],ans;
map<int,int>mp;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		vis[a[i]]=i;//记录出现位置
	}
	for(int i=1;i<=n;i++) {
		scanf("%d",&b[i]);
		if(i==vis[b[i]]) {//如果位置未动，只需要加一个mp[0]即可
			mp[0]++;
			ans=max(ans,mp[0]);
		}
		else {
			int x=i-vis[b[i]];
			mp[x]++;//不跨越边界到达a
			ans=max(ans,mp[x]);
			mp[-(n-x)]++;//跨越边界
			ans=max(ans,mp[-(n-x)]);
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果。](https://vipblog.github.io/oPwX6bNsk/)

## description：

- 给定两个长度为 $n$ 的 $1\sim n$ 的排列 $a_i,b_i$。

- 你可以对任意一个排列进行若干次长度为 $k$ 的 **循环右移或左移**；这里的循环移动指每个元素依次向左或右移动 $k$ 个，如果移出边界的元素再折回到排列的头或尾。

- 你需要求出在移动过后最多有多少个对应的位置使得 $a_i=b_i$。

- $1\le n\le 2\times 10^5$，$1\le a_i,b_i\le n$。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：

我们直接在众多种移动方法中保留任意一种其实就行了。

我们对于 $a$ 中的每个元素，记录其与对应的 $b$ 中相等的元素所相差的距离，众数即为答案。

## code：

```cpp
#include<cstdio>
using namespace std;
int abs(int x)
{
	if(x<0)return -x;
	return x;
}
int max(int x,int y)
{
	if(x>y)return x;
	return y;
}
int a[200005],b[200005],dis[200005],mp0[200005],mp[200005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mp0[a[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		mp[b[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		dis[(n+mp0[i]-mp[i])%n]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,dis[i]);
	}
	if(n==1)printf("1\n");
	else
	printf("%d\n",ans);
	return 0;
}
```

---

