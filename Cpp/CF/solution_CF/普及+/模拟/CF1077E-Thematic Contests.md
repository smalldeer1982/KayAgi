# Thematic Contests

## 题目描述

`Polycarp`有$n$个问题，问题的主题分别是$a_1,a_2,\cdots,a_n$，`Polycarp`需要组织一些专题比赛，同时要满足以下条件：  
- 一场专题比赛中的所有题目的主题相同  
- 组织的所有专题比赛中主题互异  
- 从第二场比赛开始，比赛中的题目数必须是前一场比赛题目数量的$2$倍，第一场比赛的题目数量可以是任意的  
- 所有比赛使用的题目数量之和最大  

求所有比赛使用的题目数量之和的最大值  
注意：不需要使比赛的数量最大，不一定需要使用所有的题目，不一定需要使用所有的主题

## 样例 #1

### 输入

```
18
2 1 2 10 2 10 10 2 2 1 10 10 10 10 1 1 10 10
```

### 输出

```
14
```

## 样例 #2

### 输入

```
10
6 6 6 3 6 1000000000 3 3 6 6
```

### 输出

```
9
```

## 样例 #3

### 输入

```
3
1337 1337 1337
```

### 输出

```
3
```

# 题解

## 作者：Nephren_Sakura (赞：2)

题目传送门：[link](https://www.luogu.com.cn/problem/CF1077E)

首先，我们不难看出，题目主题与答案无关。

因此我们可以将主题离散化之后存入桶中。

然后有一个贪心的思想：

令 $sum_i$ 表示主题为 $i$ 的题目的出现次数：

不妨设 $sum_{a_1}<sum_{a_2}<\dots<sum_{a_n}$，则若主题 $a_i$ 被使用过了，主题 $a_{i+1},a_{i+2},\dots,a_{n}$ 必定都被使用过。

这样的话我们可以得知 $sum_{a_n}$ 一定被使用过。

所以枚举 $sum_{a_n}$ 的使用题目数量，然后设当前使用题目数量为 $j$，在第 $a_i$ 个主题

若 $2 \mid j$ 并且 $j \div 2 \le sum_{a_{i-1}}$ 则可以继续向前并统计答案。

细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int lsh[1000005],n=read(),a[1000005],sum[1000005],maxi=-1e18,ans=-1e18;
void help(){
    for(int i=1; i<=n; i++)
        lsh[i]=a[i];
    sort(lsh+1,lsh+n+1);
    int len=unique(lsh+1,lsh+n+1)-(lsh+1);
    for(int i=1; i<=n; i++)
        a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
    return;
}
signed main(){
    for(int i=1; i<=n; i++)
        a[i]=read();
    help();//离散化
    for(int i=1; i<=n; i++)
        sum[a[i]]++,maxi=max(maxi,a[i]);
    sort(sum+1,sum+maxi+1);//按sum排序，即让不妨设的条件满足
    for(int i=1; i<=sum[maxi]; i++){
        int j=i,hp=maxi-1,s=i;//s当前的答案，hp表示当前在哪个主题，j表示当前场次有多少个题目
        while(j%2==0&&sum[hp]>=j/2){//满足条件
            j/=2;
            s+=j;
            hp--;//更新
        }
        ans=max(ans,s);//更新答案
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：CreeperK (赞：2)

## Codeforces Round 521 Div.3 E

其实这题我在40分钟时就想出来了。。。但硬是调了我30多分钟，直到1时22分才交上去。

下面进入正题。

首先，不难看出，题目编号与答案无关，答案只与每个编号有多少题有关。因此，我们可以离散化一下，方便后面统计。

```cpp
scanf("%d",&n);
for(int i=1;i<=n;i++)scanf("%d",&a[i]),q[a[i]]++;//q是一个map，保证不会爆空间。
sort(a+1,a+n+1);//排序
int m=unique(a+1,a+n+1)-(a+1);//离散化
for(int i=1;i<=m;i++)v[i]=q[a[i]];//新的题目数数组
sort(v+1,v+m+1);
```

然后，不难发现，因为必须恰好两倍，所以限制很强，序列必须为：

$v$,$v*2$,$v*4$,$v*8$......$v*2^k$。

其中，v表示第一个比赛的题目数。而且，不难看出，$v<=n$。

所以我们可以枚举v。

但接下来，就是我的思路跟别人不大一样的地方。别人是二分，我是枚举可延伸的序列长度。

因为$v*2^k<=n<=200000$，所以$k<18$，枚举量非常低。然后，就可以看看它能“延伸多长”，像下面的代码一样：
```cpp
maxn=v[m];//最大题目数至少有v[m]个
	for(long long i=1;i<=v[m];i++){
		int k=min(20,m),cur=m,sum=0;//k表示当前位置幂次，cur表示第几个，sum表示序列长度。
		while(cur>=1 && k>=0){
			while(i*1ll*(1<<k)>v[cur])k--;//如果太大，就--。
			while(i*1ll*(1<<k)<=v[cur] && cur>=1 && k>=0)cur--,k--,sum++;//cur往前，k往前，序列长度++。
		}
		maxn=max(maxn,i*((1<<sum)-1));//题目数取最大值
	}
```

可能不是特别好理解，我们可以举个例子：

对于样例：
```cpp
18
2 1 2 10 2 10 10 2 2 1 10 10 10 10 1 1 10 10
```
v数组应该是：
```cpp
4 5 9
```
首先i=1，则k=3。

往前，k=2，$2^2<=5$，可以。

往前，k=1，$2^1<=4$，可以。

因此序列长度为3。

对于i=2，同上，序列长为3。

对于i=3，首先k=2。

往前，k=1，$3*2^1>5$，k=0，$3*2^0<=5$，可以。

此时k=0，所以最大序列长为2。

其它情况同理。

有人可能会注意到，i=1的时候，cur=1时k并不等于0，不是意味着i还可以乘以2吗？为什么不以这个乘以2的值作为开头呢？

是可以，但没有必要，因为在i推进的过程中，i*2一样会被枚举到，在后面就可以更新了。

完整代码如下：
```cpp
//qaq
#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int a[200005];
long long v[200005];
int vis[200005];
int k,cur;
long long maxn;
map<int,long long> q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),q[a[i]]++;
	sort(a+1,a+n+1);
	int m=unique(a+1,a+n+1)-(a+1);
	for(int i=1;i<=m;i++)v[i]=q[a[i]];
	sort(v+1,v+m+1);
	maxn=v[m];
	for(long long i=1;i<=v[m];i++){
		int k=min(20,m),cur=m,sum=0;
		while(cur>=1 && k>=0){
			while(i*1ll*(1<<k)>v[cur])k--;
			while(i*1ll*(1<<k)<=v[cur] && cur>=1 && k>=0)cur--,k--,sum++;
		}
		maxn=max(maxn,i*((1<<sum)-1));
	}
	printf("%d",maxn);
}
```

---

## 作者：kimi0705 (赞：0)

本文经作者实验，[blog](https://www.luogu.com.cn/blog/AK-CSP-IOI/solution-cf1077e) 食用更佳。
## 前言
受@[$\bf\color{bfbfbf}{CreeperK}$](/user/52913)的影响，会做了此题。

~~(此题解是把他的内容说的更详细一点)~~
## 正题
### 题面翻译
Polycarp 有 $n$ 个问题，问题的主题分别是 $a_1,a_2,\cdots,a_n$，Polycarp 需要组织一些专题比赛，同时要满足以下条件：  

- 一场专题比赛中的所有题目的**主题相同**。
- 组织的所有专题比赛中**主题互异**。
- 从**第二场**比赛开始，比赛中的题目数必须是前一场比赛题目数量的 $2$ 倍，第一场比赛的题目数量可以是任意的。
- 所有比赛使用的题目数量之和最大。

求**所有比赛**使用的**题目数量之和**的**最大**值。

注意：**不需要**使**比赛的数量最大**，**不一定**需要使用**所有的题目**，**不一定**需要**使用所有的主题**。

### 思路
首先，不难看出，**主题编号、题目下标与答案无关**，**答案只与每个主题有多少题有关。**
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 100;
int n, m; 										// n 为几个数，m 为几个不同的数
int a[N];
int t[N];
map<int, int> A;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) A[a[i]]++;
	for (auto i : A) t[++m] = i.second;			// 等于这个数出现的个数。
	sort(t + 1, t + m + 1);						// 排序。
	return 0;
}
```
其次，由题意知，比赛的题目数量必须是 $t_1,t_1\times2,t_1\times2^2,t_1\times2^3,t_1\times2^4\dots ,t_1\times2^k$

$\because n \le 2\times10^5 \therefore \max t_i \le 2 \times 10 ^ 5 \because 2^{18} = 262144 \therefore k \le 17$

所以直接枚举。

可以参考样例及代码:
### 样例
$v=[4,5,9]$

---
首先，$i=1$，则 $k=3$。

往前，$k=2$，$2^2\le5$，可以。

往前，$k=1$，$2^1\le4$，可以。

因此序列长度为 $3$。

答案为 $1\times(2^0+2^1+2^2)=2^3-1$。

---
首先，$i=2$，则 $k=2$。($2\times2^2\le9$)

往前，$k=2$，$2\times2^1\le5$，可以。

往前，$k=1$，$2\times2^0\le4$，可以。

因此序列长度为 $3$。

答案为 $2\times(2^0+2^1+2^2)=2\times(2^3-1)$。

---
首先，$i=3$，则 $k=2$($3\times2^1\le9$)。

往前，$k=2$，$2\times2^0\le5$，可以。

**不能往前了**，因此序列长度为 $2$。

答案为 $3\times(2^0+2^1)=2\times(2^2-1)$。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 100;
int n, m, ans; 										// n 为几个数，m 为几个不同的数
int a[N];
int t[N];
map<int, int> A;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) A[a[i]]++;
	for (auto i : A) t[++m] = i.second;				// 等于这个数出现的个数。
	sort(t + 1, t + m + 1);							// 排序。
	ans = t[m]; 									// 最大题目数至少有t[m]个（只要取题目数最大的主题就好了）
	for (int i = 1; i <= t[m]; i++) {				// 枚举最前面(t_1)
		int k = min(17LL, m), now_point = m,sum = 0;// k 表示当前位置的幂次，now_point表示当前位置，sum表示序列长度。
		while (now_point >= 1 && k >= 0) {			// 当前位置大于 1 ; k == 0 表示枚举到第一位了
			while (i * (1 << k) > t[now_point]) k--;// 如果最大的数都不行了，，幂次--。
			if (now_point >= 1 && k >= 0)			// 这样也是可以的，@CreeperK 的是一次处理多个的。
				now_point--, k--, sum++; 			// now_point往前，k往前，序列长度++。
		}
		ans = max(ans, i * ((1 << sum) - 1)); 		//题目数取最大值
	}
	cout << ans;
	return 0;
}
```


---

## 作者：Pretharp (赞：0)

首先，题目主题的编号很大但又不影响答案，所以我们先将所有题目主题的编号离散化后装进一个桶，设这个桶为 $b$，$b_i$ 表示题目主题编号（离散化后）为 $i$ 的题目的数量。

如果最后一次比赛出了 $x$ 道题目，那么所有比赛出的题目数将会是 $x,\ x\div2,\ x\div2^2,\ldots\ ,\ x\div2^k$。枚举 $x$，考虑到 $x$ 初始越大那么答案就有可能越大，所以我们不妨设这 $x$ 道题目由题目数最多的主题中出，接下来：

1. 每次将 $x\div2$，如果其为整数并且剩下的主题中某个主题拥有至少 $x\div2$ 的题目数那么就令 $x$ 为 $x\div2$，并且继续操作 $1$；

2. 当操作 $1$ 无法继续，那么记录答案，之后更换初始的 $x$ 值继续如上操作，直到 $x=1,\ 2,\ \ldots,\ \max\{b_i\}$ 都枚举过后找到最大答案。

单次操作 $1$ 的时间复杂度为 $O(\log\ n)$，需要枚举 $O(n)$ 次，时间复杂度共 $O(n\ \log\ n)$。

[代码](https://codeforces.com/contest/1077/submission/213279326)

---

## 作者：chengning0909 (赞：0)

# CF1077E

## 题意

Polycarp 有 $n$ 个问题，问题的主题分别是 $a_1, a_2, \dots, a_n$，Polycarp 需要组织一些专题比赛，同时要满足以下条件：  

- 一场专题比赛中的所有题目的主题相同  

- 组织的所有专题比赛中主题互异  

- 从第二场比赛开始，比赛中的题目数必须是前一场比赛题目数量的 $2$ 倍，第一场比赛的题目数量可以是任意的  

- 所有比赛使用的题目数量之和最大  

求所有比赛使用的题目数量之和的最大值。

注意：不需要使比赛的数量最大，不一定需要使用所有的题目，不一定需要使用所有的主题。

## 思路

我们考虑用一个桶来记录所有专题的题目数量。

因为专题的值高达 $10 ^ 9$，需要离散化一下。

所以就有一种做法：

1. 将所有的主题的题目数量存下来。

2. 枚举第一场比赛用多少题目，不断地将题目数量 $\times 2$，判断是否可行。

但是，这种做法有一个问题，时间复杂度过高，所以我们可以将**判断是否可行**这个步骤用二分来实现，由于每次需要的题目数量都是原来的两倍，所以将专题对应的题目数量从小到大排序后，就具有单调性了。

---

## 作者：wnsyou (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1077E)

## 题意

有 $n$ 个问题，每个问题有一个分类 $a_i$。

现在要举办一些比赛，要求：

- 一场比赛中所有题目的分类相同。
- 所有比赛的分类是互不相同的。
- 第一场比赛的题目数量任意，但从第二场开始，每一场比赛的题目数量都必须是前一场的两倍。

求所有比赛的题目数量之和的最大值。

## 思路

一看数据范围，就知道要离散化。

有一个明显的贪心：按照每个分类的出现次数排序。把出现次数较少的分类放在后面是不可能使答案更优的，所以可以排序。

(温馨提示：接下来的部分中第 $i$ 种主题指的都是离散化后的。)

我的做法是 `dp`。

- 状态：$dp_{i,j}$，表示第 $i$ 种主题选择 $j$ 道题情况下，前 $i$ 种主题选择的题目数量最大值。
- 转移：$dp_{i,j}=\max\limits_{k=1}^{i-1}\{\max\limits_{l=1,l\times 2=j}^{b_k}\{dp_{k,l} \}\}+j$。
- 目标状态：$\max\limits_{i=1}^{m}\{\max\limits_{j=1}^{b_i}\{dp_{i,j} \}\}$，其中 $m$ 表示离散化后主题的数量，$b_i$ 表示第 $i$ 个主题中的题目数量。

但是很明显，二维状态存不下、转移时直接查找会 `TLE`，怎么办呢？

我们可以把最后一次比赛选择 $i$ 道题的最大答案记录下来，这样既可以省掉 $i$ 这一个维度，还可以节省掉查找的时间，两全其美。

具体实现看代码。

## Code

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n, a[N], m, b[N], c[N], dp[N], ans;
// c[i] 用来记录最后一次比赛选择 i 道题的最大答案

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  // 以下内容为离散化
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    if (a[i] == a[i - 1]) {
      b[m]++;
    } else {
      b[++m] = 1;
    }
  }
  // 接下来是 dp 求答案
  sort(b + 1, b + m + 1); // 按出现次数从小到大排序
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= b[i]; j++) { // 离散化后第 i 个主题选择了 j 个题目
      dp[j] = 0;
      if (!(j % 2)) { // j 是偶数，那么它的前面还可以添加比赛
        dp[j] = c[j / 2];
      }
      dp[j] += j; // 加上这次选择的题目数量
      ans = max(ans, dp[j]); // 统计答案
    }
    for (int j = 1; j <= b[i]; j++) {
      c[j] = max(c[j], dp[j]); // 注意细节！这里的最大值是不可以放在上面去更新的！
    }
  }
  cout << ans;
  return 0;
}
```


---

## 作者：Suiseiseki (赞：0)

这一题有一个~~很明显~~规律，就是每一个主题只会在一天的比赛中出现

那么接下来我们就可以很愉快的二分啦

```cpp
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
int a[200005];
map<int,int> mp;
int Id;
int getId(int p){//和离散化差不多
	if(mp.count(p)>0){
		return mp[p];
	}
	mp[p]=++Id;
	return Id;
}
int mx(int a,int b){//本人习惯
	return a>b?a:b;
}
int main(){
	int n;
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		a[getId(x)]++;
	}
	sort(a+1,a+1+Id);//排序嘛，不就是为了二分吗
	int ans=0;
	int last,now,pos;
	for(int i=1;i<=n;i++){//枚举第一个数，1~n
		last=1;
		now=0;
		for(int k=i;k<=n;k<<=1){
			pos=lower_bound(a+last,a+1+Id,k)-a;//找到下一个最优的
			if(pos>Id){
				break;
			}
			now+=k;//当前答案更新
			last=pos+1;
		}
		ans=mx(ans,now);//最终答案更新
	}
	printf("%d\n",ans);
	return 0;
}

```

---

