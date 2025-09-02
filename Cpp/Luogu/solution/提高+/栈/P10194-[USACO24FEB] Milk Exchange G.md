# [USACO24FEB] Milk Exchange G

## 题目描述

Farmer John 的 $N$（$1\le N \le 5\cdot 10^5$）头奶牛排成一圈。第 $i$ 头奶牛有一个容量为整数 $a_i$（$1\le a_i\le 10^9$）升的桶。所有桶初始时都是满的。

每一分钟，对于 $1\le i<N$，奶牛 $i$ 会将其桶中所有牛奶传递给奶牛 $i+1$，奶牛 $N$ 将其牛奶传递给奶牛 $1$。所有交换同时发生（即，如果一头奶牛的桶是满的，送出 $x$ 升牛奶同时收到 $x$ 升，则她的牛奶量保持不变）。如果此时一头奶牛的牛奶量超过 $a_i$，则多余的牛奶会损失。

在 $1,2,\ldots,N$ 的每一分钟后，所有奶牛总共还余下多少牛奶？ 

## 说明/提示

### 样例解释 1

最初，每个桶中的牛奶量为 $[2,2,2,1,2,1]$。

- $1$ 分钟后，每个桶中的牛奶量为 $[1,2,2,1,1,1]$，因此总牛奶量为 $8$。
- $2$ 分钟后，每个桶中的牛奶量为 $[1,1,2,1,1,1]$，因此总牛奶量为 $7$。
- $3$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $4$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $5$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $6$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。

### 样例解释 2

$1$ 分钟后，每个桶中的牛奶量为 $[1,3,6,4,4,3,3,1]$，因此总牛奶量为 $25$。

### 测试点性质

- 测试点 $4-5$：$N\le 2000$。
- 测试点 $6-8$：$a_i\le 2$。
- 测试点 $9-13$：所有 $a_i$ 在范围 $[1,10^9]$ 内均匀随机生成。
- 测试点 $14-23$：没有额外限制。

## 样例 #1

### 输入

```
6
2 2 2 1 2 1```

### 输出

```
8
7
6
6
6
6```

## 样例 #2

### 输入

```
8
3 8 6 4 8 3 8 1```

### 输出

```
25
20
17
14
12
10
8
8```

## 样例 #3

### 输入

```
10
9 9 10 10 6 8 2 1000000000 1000000000 1000000000```

### 输出

```
2000000053
1000000054
56
49
42
35
28
24
20
20```

# 题解

## 作者：szh_AK_all (赞：19)

[双倍经验](https://www.luogu.com.cn/problem/P10318)

为什么楼下题解写的那么麻烦，我来一篇简单易懂的题解。

首先由于桶是环形排列的，所以为了方便起见，将原序列复制一遍，这样便将环展开了。

### 部分代码
```cpp
int n;
cin >> n;
for (int i = 1; i <= n; i++)
	cin >> a[i];
for (int i = n + 1; i <= n + n; i++)
	a[i] = a[i - n];
```

接下来定义两个数组 $l,r$，其中 $l_i$ 表示左边第一个牛奶量比 $a_i$ 小的桶的位置，$r_i$ 表示右边第一个牛奶量不比 $a_i$ 大的桶的（这样定义的用处见下文可知，并且这样定义容易求出 $l,r$ 数组）。

考虑如何求得 $l$ 数组。

对于边界情况，即 $i=1$ 时，显然，由于 $i$ 左边没有桶了，所以 $l_i=0$；那么对于 $i>1$ 的情况，首先可以得到如下暴力代码：
```cpp
for (int i = 2; i <= n; i++) {
  for (int j = i - 1; j >= 1; j--) {
    	if (a[j] < a[i]) {
          l[i] = j;
          break;
        }
  }
}
```
那么这种暴力方法的时间输在了哪里呢？假设桶的牛奶量序列为 ```1 10000000 100000000 4 3 2```，那么在求答案过程中，第 $2,3$ 个位置会经过多次，但是显然，凭借肉眼观察也能得知，第 $2,3$ 个位置的桶的牛奶量太大了，对 $l$ 数组不会有贡献。

如上的例子便启发我们，可以尽量避开一些对答案不会有影响的位置。假设目前考虑到了第 $i-1$ 个位置的桶的牛奶量是否小于第 $i$ 个位置的桶的牛奶量，则分为两种情况：一、$a_{i-1}<a_{i}$，则直接更新 $l_i$ 即可；二、$a_{i-1}\ge a_{i}$，则开始考虑避开一些对答案不会有影响的位置。

反过头来看看 $l$ 的定义：$l_i$ 表示左边第一个牛奶量比 $a_i$ 小的桶的位置，那这是不是代表第 $i-1$ 至第 $l_i+1$ 个位置的桶的牛奶量都是不小于第 $i$ 个位置的桶的牛奶量？显然是的，又因为 $a_{i-1}\ge a_i$，所以 $a_k\ge a_i(i-1\ge k\ge a_{i-1})$，也就是说，第 $i-1$ 至第 $l_i+1$ 个位置的桶对答案没有影响。那么可以一个个跳 $j$，若 $a_j<a_i$，则更新 $l_i$；否则，$j=l_j$。

求得 $r$ 数组的方法是类似的。

复杂度是均摊的。

部分代码：
```cpp
l[1] = 0;
for (int i = 2; i <= n + n; i++) {
	int x = i - 1;
	while (a[x] >= a[i] && x != 0)
		x = l[x];
	l[i] = x;
}//预处理左边第一个比a[i]小的
r[n + n] = n + n + 1;
for (int i = n + n - 1; i >= 1; i--) {
	int x = i + 1;
	while (a[x] > a[i] && x != 0 && x != n + n + 1)
		x = r[x];
	r[i] = x;
}//预处理右边第一个不比a[i]大的
```

接下来便是真正求答案的时刻了。

可以依次枚举每个位置对总答案产生的贡献，先来看个例子（也就是样例一）。
![](https://cdn.luogu.com.cn/upload/image_hosting/v1jj6ocu.png)

其中，黑色箭头指的是当前所考虑的 $i$ 为 $6$，黄色箭头指的是 $l_i=2$，蓝色箭头指的是 $r_i=7$，那么，可以发现，仅有绿色区域的牛奶会在第 $r_i$ 个位置损失，且这个绿色区域恰好是个矩形。那么，根据绿色区域的贡献，在第 $1$ 秒，牛奶会损失 $1$（也就是矩形的宽），在第 $2$ 秒牛奶会再损失 $1$，直到第 $4$（也就是矩形的长）秒，牛奶一直会损失 $1$。所以可以归纳出做法：

假设牛奶损失的值为其贡献值，则在计算每一秒所有桶的牛奶量总和时也就是用牛奶起初的总量减去这一秒牛奶的**总**贡献值。那么对于绿色区域，在第 $1$ 至第 $4$ 秒，牛奶的**总**贡献值会逐渐增加一，这正好可以用二阶差分来处理。下面列出表格，方便观察差分数组（设 $c$ 为矩形的长，$k$ 为矩形的宽）。
| 数组/下标   |  $1$  |  $2$ | $\dots$ | $c$ | $c+1$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
|总贡献值变化数组     |$+k$ | $+2k$ | $\dots$ | $+ck$ | $+ck$ |
| 差分 $1$ | $+k$ | $+k$ |$+k$ | $+k$| $+0$|
|差分 $2$| $+k$ | $+0$| $+0$ |$+0$ | $-k$|

这样看便很直观了。

考虑如何求 $c,k$。

可以发现，矩形的长为 $r_i-l_i-1$（范围是 $l_i+1$ 至 $r_i-1$），那么宽呢（也可以看成是高）？观察图片可知，在绿色区域上方的 $3$ 格牛奶并不会在 $r_i$ 这个位置损失，也就是说，这个绿色区域的左右两边的高度应该是相同的（正好印证了绿色区域是个矩形），而绿色区域的宽则要最大化左右两边相同的高度（因为牛奶可以损失便一定会损失）。

再来思考下 $l$ 数组的特性，在第 $l_i+1$ 至第 $i-1$ 个位置的桶的牛奶量不小与 $a_i$，而因为绿色区域的左边部分在 $l_i$ 的右上角，所以这也就代表了绿色区域的最低部分的高度高于 $a_{l_i}$；同理，对于 $r$ 数组，可以得知绿色区域的最低部分的高度高于 $a_{r_i}$。由于 $a_i$ 是在 $a_{l_{i}+1,l_{i}+2,\dots r_i-1}$ 中最小的，所以这代表绿色区域的最高部分不超过 $a_i$，由此，可以算出 $k$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
int l[200005], r[200005];
int ans[200005];

signed main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = n + 1; i <= n + n; i++)
		a[i] = a[i - n];
	l[1] = 0;
	for (int i = 2; i <= n + n; i++) {
		int x = i - 1;
		while (a[x] >= a[i] && x != 0)
			x = l[x];
		l[i] = x;
	}//预处理左边第一个比a[i]小的
	r[n + n] = n + n + 1;
	for (int i = n + n - 1; i >= 1; i--) {
		int x = i + 1;
		while (a[x] > a[i] && x != 0 && x != n + n + 1)
			x = r[x];
		r[i] = x;
	}//预处理右边第一个不比a[i]大的
	int tmp = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] < a[tmp] || tmp == 0)
			tmp = i;
		sum += a[i];
	}//找到高度最小的
	for (int i = tmp + 1; i <= tmp + n; i++) {
		if (a[i] == a[tmp])
			continue;
		//长方形的长：r[i]-l[i]-1；长方形的宽：a[i]-max(a[l[i]]+1,a[r[i]]+1)+1
		int chang = r[i] - l[i] - 1, kuan = a[i] - max(a[l[i]] + 1, a[r[i]] + 1) + 1;
		ans[1] += kuan;
		ans[chang + 1] -= kuan;
	}
	for (int i = 1; i <= n; i++)
		ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i++)
		ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i++)
		cout << sum - ans[i] << " ";
}
```
当然还有几个细节：
- 由于要计算每个桶的贡献，所以应从长度为 $2n$ 的序列中截取长度为 $n$ 的子段。设子段的左端点是 $left$，右端点是 $left+n-1$，则应让 $a_{left-1}$ 最小，也代表着 $a_{left+n-1}$ 最小。使得遇到的 $r_i\le left\le 2n(a_i\ne a_{left-1})$，做到不错算贡献值。

- 若 $a_i=a_{left-1}$，则直接跳过该点。

路过的各位请给个赞吧！

---

## 作者：zhicheng (赞：9)

### 思路

首先转化题意，容易发现第 $i$ 个答案 $ans_i$ 为长为 $i+1$ 的所有（循环）区间 $\min$ 的和。考虑拆贡献，去算每个 $a_i$ 会对哪些 $ans$ 产生多少的贡献。

先使用单调栈预处理出它前面**小于**它的最后一个数的位置 $l_i$、后面**大于等于**它的第一个数的位置 $r_i$（因为是循环数组，所以均可跨过头尾，但是不能跨过自己上一次出现的地方）。这样可以保证一个区间仅算一次，不重不漏。

然后分类讨论。设 $len$ 为区间长度：

- $\forall 1\leq len \leq \min(i-l_i,r_i-i)$，贡献 $len$ 次（两边均没有阻挡）。

- $\forall \min(i-l_i,r_i-i)+1 \leq len \leq \max(i-l_i,r_i-i)$，贡献 $\min(i-l_i,r_i-i)$ 次（有一边有阻挡）。

- $\forall \max(i-l_i,r_i-i)+1 \leq len \leq r_i-l_i-1$，贡献 $(r_i-l_i-1)-len+1$ 次（两边均有阻挡）。

- $\forall r_i-l_i\leq len\leq n$，没有贡献。

注意到三种情况都相当于在答案数组上区间加等差数列。直接维护二阶差分即可。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500010;
int p[N<<1],s[N<<1],a[N*3],l[N*3],r[N*3],q[N*3],cnt;
inline void add(int l,int r,int x,int y){ //维护二阶差分
	if(r<l){
		return;
	}
	p[l]+=x;
	p[r+1]-=y*(r-l)+x;
	s[l+1]+=y;
	s[r+1]-=y;
}
signed main(){
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i+n]);
		a[i+n*2]=a[i]=a[i+n];  //先复制三遍
		r[i]=3*n+1;
	}
	//单调栈
	for(int i=1;i<=n*3;i++){
		while(cnt&&a[q[cnt]]>=a[i]){
			cnt--;
		}
		l[i]=q[cnt];
		q[++cnt]=i;
	}
	cnt=0;
	for(int i=n*3;i>=1;i--){
		while(cnt&&a[q[cnt]]>a[i]){
			cnt--;
		}
		if(cnt){
			r[i]=q[cnt];
		}
		q[++cnt]=i;
	}
	//分类讨论
	for(int i=1;i<=n;i++){
		l[i]=max(l[i+n],i)-n;//取中间那一遍的结果，注意不能跨过自己
		r[i]=min(r[i+n],i+2*n)-n;
		add(1,min(i-l[i],r[i]-i),a[i],a[i]);
		add(min(i-l[i],r[i]-i)+1,max(i-l[i],r[i]-i),(min(i-l[i],r[i]-i))*a[i],0);
		add(max(i-l[i],r[i]-i)+1,r[i]-l[i]-1,(min(i-l[i],r[i]-i))*a[i]-a[i],-a[i]);
	}
	for(int i=1;i<=n;i++){
		s[i]+=s[i-1];
		p[i]+=s[i];
	}
	for(int i=2;i<=n;i++){
		p[i]+=p[i-1];
		printf("%lld\n",p[i]);
	}
	printf("%lld",p[n]);//最后一个答案和倒数第二个是相同的
}
```

---

## 作者：Error_Eric (赞：8)

### Statement

转化下题意就是

对于 $1\le i\le n, i\in \mathbf{N}$ 求 $\sum_{j=1}^n\min\{a_j,a_j+1,\cdots a_{j+i}\}$。 其中 $a_{n+1}=a_1,a_{n+2}=a_2$ 以此类推。

### Sol

注意到一样的数字会越来越多，因此考虑计算每个数字对每个时间的答案的贡献。

手玩一下可以发现，如果把最小的放在最右边就不用考虑从 $a_n$ 跨越到 $a_1$ 的问题了，环上问题变成朴素的序列问题。

此时，题目可以看作每个数字如果比左边的小，就覆盖左边的。因此每个数字会一直往左覆盖直到遇到比自己小的为止。也会最终被右边第一个比自己小的覆盖。

以样例 2 为例。

```
编号1 2 3 4 5 6 7 8
    3 8 6 4 8 3 8 1
    3 6 4 4 3 3 1 1
    3 4 4 3 3 1 1 1
    3 4 3 3 1 1 1 1
    3 3 3 1 1 1 1 1
    3 3 1 1 1 1 1 1
    3 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1
```

六号位的 ``3`` 一路向左增加自己的个数直到遇到一号位的 ``3``，同时它也在第二秒后一路被八号位的 ``1`` 追赶减少自己的个数。同理每个数的贡献可以看作一个公差先为 $a_i$ （追赶左边的），然后为 $0$ （追赶左边的同时被右边追赶）最后为 $-a_i$ （被最后一个追）的三个等差数列接在一起（其中可能有几段长度为 $0$)。我们只需对每个位置分别预处理出左侧第一个小于等于自己的位置和后面第一个小于自己的位置即可确定这三段的长度。

不难发现这是一个区间加等差数列的问题。

~~然后某人开始自信地开始打线段树……~~

实际上只需要二位前缀和就可以解决只有一次整体查询的区间加等差数列问题。

### Code

赛时代码，略显丑陋。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<numeric>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int _=5e5*4.1;
map<int,vector<int>*>mp;
ll n,a[_],b[_],last;
int o[_];
set<int>si;
typedef set<int>::iterator sit;
sit prei(sit sx){return --sx;}
sit sufi(sit sx){return ++sx;}
class SOL{
    public:
    map<int,ll>mtr;// 数组也行，赛时脑子炸了。
    void radd(int l,int r,ll val){
        mtr[l]+=val,mtr[r+1]-=val;
    }
    void rans(){
        ll ans0=accumulate(a+1,a+n+1,0ll),a=0;
        for(int i=1;i<=n;i++)
            cout<<(ans0+=(a+=mtr[i]))<<endl;
    }
}TR;// 最早是一个线段树，后来发现自己是个大聪明
int pre[_],suf[_];
bool cmp(int i1,int i2){
    if(a[i1]==a[i2]) return i1<i2;
    else return a[i1]<a[i2];
}
int main(){
    ios::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i],
        a[i+n]=a[i];
        if(last==0||a[i]<=a[last])
            last=i+n;
    }
    for(int i=1;i<=n;i++)
        a[i]=a[last-n+i];
    iota(o+1,o+n+1,1),
    sort(o+1,o+n+1,cmp);
    si=set<int>({0,(int)(n+1)});
    for(int i=1;i<=n;i++)
        si.insert(o[i]),
        pre[o[i]]=(*prei(si.find(o[i]))),
        suf[o[i]]=(*sufi(si.find(o[i])));
    
    for(int i=1;i<=n;i++){
        ++pre[i];
        if(a[i]<a[i-1])
            TR.radd(1,i-pre[i],a[i]);
        if(a[i]>a[suf[i]])
            TR.radd(suf[i]-i,suf[i]-pre[i],-a[i]);
    }
    TR.rans();
}
```

---

## 作者：huazai676 (赞：6)

#### 题意：长度为 $n$ 的环上放着 $n$ 个装满水的水桶，每秒钟每个水桶都沿着顺时针把自己桶内的水倒给下一个桶（由于桶大小不一可能会溢出）。对于第 $1,2,\dots,n$ 秒分别求出剩余水的总和。

先断环成链把数组复制一份添加到后面。对于每个水桶都模拟一遍复杂度是 $O(n^2)$ 的，而即使每次只找水桶后第一个小于它的桶复杂度依然是 $O(n^2)$，大小递减就卡掉了。

发现本质上第 $x$ 秒的答案是 $\sum\limits_{i=1}^n\min\limits_{j\in [i,i+x]}a_j$，也就是所有长度为 $x+1$ 的区间的最小值之和（且要求区间左端点在 $1$ 到 $n$ 中）。这启发我们找出维持某个最小值的区间，一次性统计其对不同长度答案的贡献。设 $L_i$ 为 $i$ 左边第一个小于 $a_i$ 的数的位置，$R_i$ 为 $i$ 右边第一个小于 $a_i$ 的数的位置，则区间 $(L_i,R_i)$ 的所有包含 $i$ 的子区间最小值都为 $a_i$。发现这些子区间中长为 $1$ 的有 $1$ 个，$2$ 有 $2$ 个...... $R_i-L_i-1$ 的有 $1$ 个。对答案的贡献是三段等差数列，分讨计算一下端点，线段树或者二阶差分维护一下即可。

但事情还没结束，水桶大小可以能相等：如果某些区间 $(L_i,R_i)$ 内包含了多个最小值点，某些子区间的贡献将被重复统计。如果存在 $i < j$，$(L_i,a_i,R_i)=(L_j,a_j,R_j)$，我们希望在统计 $j$ 的时候只统计不包含 $i$ 的子区间。所以我们可以修改 $L_i$ 的定义为 $i$ 左边第一个**小于等于** $a_i$ 的位置，这样每个子区间在最左边的最小值处被统计到。

因为只能统计左端点在 $1$ 到 $n$ 中的区间的贡献，所以可以容斥一下对所有 $(L_i \leq n,i,R_i)$ 的贡献减去 $(n+1,i,R_i)$ 的贡献。

如果用二阶差分可以做到 $O(n)$。下面写的是线段树。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long ll;

const int N=5e5+10;

int n,a[N<<1],st[N<<1],tp;
int L[N<<1],R[N<<1];

ll a0[N<<2],d[N<<2];

void modify(int u,int l,int r,int ql,int qr,ll k1,ll k2)
{
	qr=min(qr,n+1);
	if(ql>qr) return;
	if(ql<=l&&r<=qr)
	{
		a0[u]+=k1+k2*(l-ql);
		d[u]+=k2;
		return;
	}
	int mid=l+r>>1;
	if(ql<=mid) modify(u<<1,l,mid,ql,qr,k1,k2);
	if(qr>mid) modify(u<<1|1,mid+1,r,ql,qr,k1,k2);
}

ll query(int u,int l,int r,int x)
{
	if(l==r)
	{
		return a0[u];
	}
	int mid=l+r>>1;
	ll res=a0[u]+d[u]*(x-l);
	if(x<=mid) res+=query(u<<1,l,mid,x);
	else res+=query(u<<1|1,mid+1,r,x);
	return res;
}

void change(int i,int l,int r,int k)
{
	int k1=min(r-i+1,i-l+1),k2=max(r-i+1,i-l+1);
	modify(1,1,n+1,1,k1,a[i]*k,a[i]*k);
	modify(1,1,n+1,k1+1,k2,1LL*k1*a[i]*k,0);
	modify(1,1,n+1,k2+1,r-l+1,1LL*(k1-1)*a[i]*k,-a[i]*k);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=n+1;i<=n*2;i++) a[i]=a[i-n];
	a[n*2+1]=-1;
	for(int i=1;i<=n*2+1;i++)
	{
		while(tp&&a[i]<a[st[tp]])
		{
			R[st[tp]]=i;
			tp--;
		}
		st[++tp]=i;
	}
	tp=0;
	a[0]=-1;
	for(int i=n*2;i>=0;i--)
	{
		while(tp&&a[i]<=a[st[tp]])
		{
			L[st[tp]]=i;
			tp--;
		}
		st[++tp]=i;
	}
	for(int i=1;i<=n*2;i++)
	{
		if(L[i]>=n) continue;
		change(i,L[i]+1,R[i]-1,1);
		if(i>n) change(i,max(n+1,L[i]+1),R[i]-1,-1);
	}
	for(int i=1;i<=n;i++) printf("%lld\n",query(1,1,n+1,i+1));
	
	return 0;
}
```

---

## 作者：TBSF_0207 (赞：5)

提供一种比较易懂但是常数大一点的**单调栈+二次差分**写法。

我们先破环成链，将序列自我复制一次。

形式化的，要求的答案 $ans_k=\sum_{i=1}^n \min_{j=i}^{i+k} a_j$。

发现如果每个区间贡献单独考虑好像不太可做，那么可以考虑每个 $a_j$ 对答案的贡献。

考虑在一个无限自我复制的序列中，有一个位置 $x$，它左侧最近且满足 $a_{L-1}\le a_x$ 的位置为 $L$，它右侧最近且满足 $a_{R+1}<a_x$ 的位置为 $R$，很显然两者都可以用单调栈维护。

然后我们记 $L_i\in [L,x]$。

然后考虑 $a_x$ 的贡献。我们将所有时间向后推一秒。显然地从一个 $j$ 到达 $i(i>j)$ 的时刻是 $i-j+1$。那么对于 $i$ 来说，$a_x$ 在时间轴上的贡献就相当于 $[x-L_i +1,R-L_i +1]$。

这样我们就得到了一个 $a_x$ 对时间的贡献，那就是在时间轴 $[x-L+1,R-L+1]$ 一直到 $[1,R-x+1]$ 的等长区间上每一个区间区间加上 $a_x$ 的结果。

这个东西怎么维护呢？对于一个静态区间加很容易想到差分，那若干个区间加就相当于在差分数组上再区间加。可以对差分数组再做一次差分，就相当于在每个区间开头分别加上一个值，在每个区间结尾 $+1$ 的位置分别减去一个值。那么直接在二次差分数组上维护即可。

最后是为什么 $L,R$ 的边界要这么设置，其实是为了防止重复。对于一个位置 $x$，如果有 $y<x,a_y=a_x$，那么 $y$ 前面的贡献一定被计算过了，$L=y+1$ 即可。

总体时间复杂度 $O(n)$。

在代码实现中，由于假想是无限自我复制的序列，所以需要自复制**三遍**然后在最中间的序列进行答案累加。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=5e5+5;
int n,a[3*N],L[3*N],R[3*N];
stack<int>stk;
LL ans[N*3];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=n+1;i<=3*n;i++)
		a[i]=a[i-n];
	for(int i=1;i<=n*3;i++){
		while(!stk.empty()&&a[stk.top()]>a[i])stk.pop();
		if(stk.empty())L[i]=1;
		else L[i]=stk.top()+1;
		stk.push(i);
	}
	while(!stk.empty())stk.pop();
	for(int i=n*3;i>=1;i--){
		while(!stk.empty()&&a[stk.top()]>=a[i])stk.pop();
		if(stk.empty())R[i]=n*3;
		else R[i]=stk.top()-1;
		stk.push(i);
	}
	for(int i=n+1;i<=2*n;i++){
		ans[1]+=a[i];
		ans[i-L[i]+2]-=a[i];
		ans[R[i]-i+2]-=a[i];
		ans[R[i]-L[i]+3]+=a[i];
	}
	for(int i=2;i<=n+1;i++)
		ans[i]+=ans[i-1];
	for(int i=2;i<=n+1;i++)
		ans[i]+=ans[i-1],cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Dovish (赞：3)

## 题解
首先我们将环长度断成两倍长度的链。

然后很显然的一步转化就是对于第 $j$ 个点在第 $k$ 次后，还剩下 $\min_{j=i}^{i+k}a_j$ 的水。

我们就可以非常容易想到用 $f_j$ 表示从 $i$ 到 $j$ 的最小值，然后用单调栈转移到 $i-1$。

问题在于如何统计答案。

仔细分析一下，如果我们将每一个 $i$ 的求得的 $f$ 称为版本 $i$ 的 $f$。那我们要统计的答案大致如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/pmsqxv4o.png)

形式化为：$ans_k=\sum_{i=1}^{n}f_{i+k}$。

这个东西你要用数据结构维护就非常鬼畜，~~至少我不会，而且我也不会告诉你我在考场上一直在想这个东西怎么用线段树实现。~~

注意到一个值在单调栈内的一次完整的入出可以在如上图的平面上构成一个矩形。而我们要求的就是这些矩形一个斜投影。

![](https://cdn.luogu.com.cn/upload/image_hosting/ktds3ha9.png)

如图，令矩形长宽为 $x$ 和 $y$，则对左下和右上角的答案区间内的贡献就是 $\min(x,y)$。余下的两坨的贡献是等差序列。

这两个东西都是可以用差分简单做的。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int inf=1e18,mod=998244353;
const int N=1000010,M=1000010;
struct query
{
	int tl,tr,xl,xr,val;
}q[N],z[N];
int pos=1,n,a[N];
int cf1[N],cf2[N],ans[N];
void get1(int l,int r,int t,int val)
{
	if(t==0||r==0)return;
	cf2[l]+=val;
	cf2[r+1]-=(t+1)*val;
	cf2[r+2]+=t*val;
}
void get2(int l,int r,int t,int val)
{
	if(t==0||r==0)return;
	cf2[r+2]+=val;
	cf2[l+1]-=(t+1)*val;
	cf2[l]+=t*val;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i+n]=a[i];
	}
	int base=a[n];
	z[1].xl=z[1].xr=n;
	z[1].tr=n;
	z[1].val=a[n];
	for(int i=1+n;i<=n*2;i++)
	if(a[i]<base)
	{
		pos++;
		z[pos].xl=i;
		z[pos].tr=n;
		z[pos].xr=i;
		z[pos].val=a[i];
		base=a[i];
	}
	else z[pos].xr=i;
	for(int i=1;i<=pos;i++)
	if(i>(pos-i+1))swap(z[i],z[pos-i+1]);
	int res=0;
	for(int i=n-1;i>=1;i--)
	{
		while(a[i]<z[pos].val)
		{
			z[pos].tl=i+1;
			q[++res]=z[pos];
			pos--;
		}
		pos++;
		z[pos].tr=i;
		z[pos].xl=i;
		z[pos].xr=z[pos-1].xl-1;
		z[pos].val=a[i];
	}
	while(pos)
	{
		z[pos].tl=1;
		q[++res]=z[pos];
		pos--;
	}
	for(int i=1;i<=res;i++)
	{
		int x=q[i].xr-q[i].tr,y=q[i].xl-q[i].tl;
		int lenth=min((q[i].xr-q[i].xl+1),(q[i].tr-q[i].tl+1));
		if(x>y)swap(x,y);
		if(y==0)continue;
		cf1[x]+=q[i].val*lenth;
		cf1[y+1]-=q[i].val*lenth;
		get1(x-lenth+1,x-1,lenth-1,q[i].val);
		get2(y+1,y+lenth-1,lenth-1,q[i].val);
	}
	for(int i=1;i<=n;i++)
	cf2[i]+=cf2[i-1];
	for(int i=0;i<=n;i++)cf1[i]+=cf2[i];
	for(int i=1;i<=n;i++)
	cf1[i]+=cf1[i-1]; 
	for(int i=1;i<=n;i++)
	cout<<cf1[i]<<'\n';
}
```

---

## 作者：Morax2022 (赞：2)

在这里提供一种有一部分不一样的线段树写法。

# Solution

断环为链后定义 $l_i$ 代表左边第一个高度小于 $a_i$ 的点坐标，$r_i$ 为右边第一个高度小于 $a_i$ 的点坐标。求法和第一篇题解一样，不断跳 $l$ 或 $r$ 来找到更小值。

接下来定义两颗线段树，一颗以时间为节点，代表在当前时间有多少牛奶会浪费掉。另一颗以 $a_i$ 为节点，代表在对答案做出贡献后剩的牛奶量。

然后找到 $a_{id}$ 使 $a_{id}$ 为 $a$ 中最小值，从 $id + 1$ 开始遍历到 $id + n$ 进行更新。这么做的原因是保证所有的 $a_i$ 都能在贡献后被更新为最小值（不然可以用后面思路试试第三个样例）。

不难发现当当前点是最小值时不会造成贡献，可以直接跳过。下一步对第二颗线段树中的 $i$ 点与 $r_i$ 点查询后做差，这个差就是 $l_i + 1$ 到 $r_i - 1$ 每个点至少会对答案造成的贡献。由于距离越远造成贡献的时间越晚，这里相当于对第一颗线段树的 $[1, r_i - l_i - 1]$ 区间更新。更新后为了这些值不会重复贡献，对第二颗线段树中的 $[l_i + 1, r_i - 1]$ 区间减。这样做的正确性可以保证，因为减了之后对于任意 $i$ 仍有 $a_i$ 大于等于 $a_{r_i}$。

总时间复杂度为 $O(n \log n)$，代码不算特别麻烦，我讲的不清楚的地方可以看一下代码。

# Code

```cpp
#include <bits/stdc++.h>
#define debug cout << "???\n";
#define int long long
using namespace std;
const int maxn = 1e6 + 5, base = 131, mod = 998244353, inf = 2e9;
const double eps = 1e-8;
int n, a[maxn];
struct Seg{
	struct seg{
		int l, r, val, tag;
	}t[maxn << 2];
	void pushup(int p){
		t[p].val = t[p << 1].val + t[p << 1 | 1].val;
	}
	void pushdown(int p){
		int l = t[p].l, r = t[p].r, mid = t[p].l + t[p].r >> 1;
		if (t[p].tag){
			t[p << 1].tag += t[p].tag, t[p << 1 | 1].tag += t[p].tag;
			t[p << 1].val += t[p].tag * (mid - l + 1);
			t[p << 1 | 1].val += t[p].tag * (r - mid);
			t[p].tag = 0;
		}
	}
	void build(int l, int r, int p, int op){
		t[p].l = l, t[p].r = r; int mid = l + r >> 1; if (l == r) {if (op) t[p].val = a[l]; return;}
		build(l, mid, p << 1, op), build(mid + 1, r, p << 1 | 1, op); pushup(p);
	}
	void update(int l, int r, int p, int k){
		if (l <= t[p].l && r >= t[p].r){
			t[p].val += (t[p].r - t[p].l + 1) * k;
			t[p].tag += k; return;
		}pushdown(p); int mid = t[p].l + t[p].r >> 1;
		if (l <= mid) update(l, r, p << 1, k);
		if (r > mid) update(l, r, p << 1 | 1, k); pushup(p);
	}
	int query(int x, int p){
		if (t[p].l == t[p].r) return t[p].val; pushdown(p);
		int mid = t[p].l + t[p].r >> 1;
		if (x <= mid) return query(x, p << 1);
		else return query(x, p << 1 | 1);
	}
}t, t2;
int L[maxn], R[maxn], id = 1, sum = 0;
main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n; for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i], a[i] < a[id] ? id = i : 0, sum += a[i];
	t.build(1, n * 2, 1, 0); t2.build(1, n * 2, 1, 1); R[n * 2] = n * 2 + 1; 
	for (int i = 2; i <= n * 2; i++){int j = i - 1; while(a[j] >= a[i] && j) j = L[j]; L[i] = j;}
	for (int i = n * 2 - 1; i >= 1; i--){int j = i + 1; while(a[j] >= a[i] && j <= n * 2 && j) j = R[j]; R[i] = j;}//求 li, ri 
	for (int i = id + 1; i <= id + n; i++){//从最小点加1开始 
		if (a[i] == a[id]) continue;
		int k = t2.query(R[i], 1) - t2.query(i, 1);//这里是 [li + 1, ri - 1] 每个点至少造成的贡献 
		t.update(1, R[i] - L[i] - 1, 1, k); t2.update(L[i] + 1, R[i] - 1, 1, k);//算贡献，去重 
	}for (int i = 1; i <= n; i++) sum += t.query(i, 1), cout << sum << '\n';//sum减去每个时间造成的贡献就是当前还剩的答案
}
```

希望能给大家带来帮助！

---

## 作者：hepp (赞：2)

填空：常年做【】的人通常【】。

没错，左偏树玄学复杂度做法奉上。

# 题解

## 特殊性质

从模拟赛过来的，其中给了一组部分分：**保证序列单调不降**。

那么开始举例思考，如：

**1 2 3 4 5 -> 1 1 2 3 4 -> 1 1 1 2 3 -> 
1 1 1 1 2 -> 1 1 1 1 1**


发现规律了吗？

一个单调不降的序列 $a$，设 $a_{max}$ 为序列最大值，$a_{min}$ 为序列最小值，每次产生的贡献 $ans = a_{max} - a_{min}$，然后 $a_{min} \to a_{max}$。

这个很容易用**大根堆**维护：记录序列最小值 $mi_i$，每次取出最大值，计算贡献，再放入一个最小值进入大根堆。

## 正解

容易想到将整个序列分成若干个单调不降序列，分别计算贡献（计算方式同上）。但是和特殊情况相比，需要多考虑一点，举例：

**1 3 2 4 -> 1 1 2 2 -> 1 1 1 2 -> 1 1 1 1**

按照我们分割的方法，序列开始被分割成了 **1 3** 和  **2 4**，然后 **1 3 -> 1 1**，**2 4 -> 2 2**，每个序列最小值最大值相等，应该结束。然而经过此次操作，两个序列合并成了一个更大的单调不降序列。

大根堆+合并，即想到**可并堆**，同时要记录下一个可能和自己合并的序列，所以要用链表。

### 另外一些细节

由于是一个环，分割时以整个序列最小值为起点，可以避免一个单调不降序列分布在序列的两端。

当 $a_{min} = a_{max}$ 且序列不能合并时，不需要进行操作（详细看代码）。


```cpp
#include<bits/stdc++.h>
#define int long long
#define ls k[x].lc
#define rs k[x].rc
using namespace std;
const int N=1e6+10,inf=1e9+10;
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x;
}
inline void write(int X)
{
	if(X>9) write(X/10);
	putchar(X%10+'0');
}
struct node{int lc,rc,v,dis;};//左偏树板子
node k[N];
int mi[N],a[N],b[N],rt[N],flg[N];
int n,id,num,sum,t[N],f[N],to[N];//to[i]:第 i 个序列的下一个可能合并的序列
void bid(int x){mi[x]=k[x].v=b[x];rt[x]=x;to[x]=x+1;t[++t[0]]=x;}
int fid(int x){return rt[x]=(rt[x]==x?x:fid(rt[x]));}
int mg(int x,int y)
{
	if(x==0||y==0)
		return x+y;
	if(k[x].v<k[y].v)
		swap(x,y);
	rs=mg(rs,y);
	if(k[rs].dis>k[ls].dis)
		swap(rs,ls);
	k[x].dis=k[rs].dis+1;
	return x;
}
signed main()
{
	//freopen("sink.in","r",stdin);
	//freopen("sink.out","w",stdout);
	n=read();mi[0]=num=inf;
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),sum+=a[i];
		if(a[i]<num)
			num=a[i],id=i;
	}
	b[++b[0]]=a[id];
	bid(b[0]);mi[n+1]=-inf;
	for(int i=(id+1)%n;;i=i%n+1)//以 a 序列最小值为起点
	{
		if(i==id) break;
		b[++b[0]]=a[i];
		bid(b[0]);
	}
	for(int i=0;i<=n;i++)
	{
		for(int j=t[0];j>=1;j--)
		{
			int x=fid(t[j]),z;
			z=rt[ls]=rt[rs]=mg(ls,rs);
			sum-=k[x].v-mi[x];//每次答案减少 max - min
			k[x].v=mi[x],ls=rs=0;
			rt[x]=rt[z]=mg(x,z);z=rt[z];
			to[z]=to[x];mi[z]=mi[x];
			int y=fid(to[x]);
			if(mi[y]>k[z].v)//如果可以合并
			{
				mi[y]=mi[z];
				rt[z]=rt[y]=mg(y,z);
				z=rt[z]; to[z]=to[y];
			}
			if(k[z].v>mi[z]&&!flg[z])//如果还需要操作而且没入队，进队
				f[++f[0]]=z,flg[z]=1;
		}
		if(i) write(sum),putchar(' ');
		t[0]=f[0],f[0]=0;
		for(int j=t[0];j>=1;j--)//每次从后往前合并，保证能合并的立刻合并
			t[j]=f[t[0]-j+1],flg[t[j]]=0,f[t[0]-j+1]=0;
	}
	return 0;
}

```

附：有没有大佬会分析这个的复杂度呀 qwq。

---

## 作者：__liujy (赞：1)

本题可以用单调栈和差分解答。

给出一个式子，对于第 $k$ 次操作，则 $ans=\sum^{n}_{i=1} \min^{i+k}_{j=i} a_{j}$，其中 $ans$ 为最终答案，我们围绕这个式子展开叙述。

暴力解这个式子能获得部分分，我们考虑正解。

令 $L$ 为最近满足 $a_{L-1} \le a_{i}$ 的位置；$R$ 为最近满足 $a_{R+1} < a_{i}$ 的位置。并且设 $l \in [L,i]$。

考虑 $a_{i}$ 对次数的贡献，把次数往后推一次，从 $i$ 到比 $i$ 大的 $j$ 时，需要 $j-i+1$ 次，因此 $a_{i}$ 的贡献就是 $[i-l+1,R-l+1]$。得到 $a_{i}$ 对次数的贡献后，就把与 $[x-L+1,R-L+1]$ 到 $[1,r-x+1]$ 等长的区间加 $a_{i}$。

这个过程要用单调栈和二次差分优化。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
typedef long long LL;
int n,a[N*3],l[N*3],r[N*3];
LL ans[N*3];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=(n<<1);i++) a[i+n]=a[i];
	stack<int> st;
	for(int i=1;i<=n*3;i++)
	{
		while(st.size()&&a[st.top()]>a[i]) st.pop();
		if(st.size()) l[i]=st.top()+1;
		else l[i]=1;
		st.push(i);
	}
	while(st.size()) st.pop();
	for(int i=n*3;i>=1;i--)
	{
		while(st.size()&&a[st.top()]>=a[i]) st.pop();
		if(st.size()) r[i]=st.top()-1;
		else r[i]=n*3;
		st.push(i);
	}
	for(int i=n+1;i<=(n<<1);i++)
	{
		ans[1]+=a[i];
		ans[i-l[i]+2]-=a[i];
		ans[r[i]-i+2]-=a[i];
		ans[r[i]-l[i]+3]+=a[i];
	}
	for(int i=1;i<=n+1;i++) ans[i]+=ans[i-1];
	for(int i=1;i<=n+1;i++) ans[i]+=ans[i-1];
	for(int i=2;i<=n+1;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：__CJY__ (赞：1)

## 题意简述
奶牛围成一圈，每分钟相互传递牛奶，超出桶容量则溢出。求每分钟后所有奶牛桶中剩余的牛奶总量。
## 思路
对于任意一头奶牛，其桶中的牛奶量只会因为接收到来自上一头奶牛的牛奶而增加，或者因为传递给下一头奶牛而减少。牛奶的传递是循环的，因此我们可以将奶牛排成一个环来处理。

我们可以发现，对于每个奶牛 $i$，其桶中的牛奶量最终会稳定在一个固定的值上，这个值取决于环中奶牛桶的容量分布。使用单调栈可以帮助我们快速找到每头奶牛最终稳定的牛奶量。具体来说，我们可以利用单调递增栈来找到每头奶牛左边和右边第一个比它容量小的奶牛的位置。

通过单调栈，我们可以确定每段区间内牛奶的最终稳定状态。对于每个区间，我们可以计算出该区间内牛奶的总量，并减去因为超出容量而损失的牛奶量。最后，通过累加每分钟后的剩余牛奶量，即可得到每一分钟后的总牛奶量。

* 单调栈用于找到每头奶牛左边和右边第一个比它容量小的奶牛的位置。

* 差分数组用于高效计算每分钟后的牛奶总量变化。

由于奶牛是排成一个环的，因此我们需要将数组扩展一倍来处理环形传递。

以下是解题步骤：
1. **处理单调栈**：找到每头奶牛左边和右边第一个比它容量小的奶牛的位置。
2. **计算差分数组**：根据单调栈的结果，计算每分钟牛奶总量的变化。
3. **累加差分数组**：得到每一分钟后的总牛奶量。
4. **输出结果**：输出每分钟后的总牛奶量。
## Code（只给关键部分）
```cpp
cin>>n;
for(ll i=1;i<=n;i++) cin>>a[i],a[n+i]=a[i];//复制数组到后半部分
//预处理左边第一个比当前元素小的位置
l[1]=0;
for(ll i=2;i<=n*2;i++){
	ll x=i-1;
	while(a[x]>=a[i]&&x) x=l[x];
	l[i]=x; 
}
//预处理右边第一个不比当前元素大的位置
r[n*2]=n*2+1;
for(ll i=n*2-1;i;i--){
	ll x=i+1;
	while(a[x]>a[i]&&x&&x!=n*2+1) x=r[x];
	r[i]=x;
}
//找到数组中的最小值及其索引，并计算数组的总和（省略）
//计算每个元素作为最大值时可以减少的总量，并更新 ans 数组（省略）
//通过前缀和计算 ans 数组的累积值，并得到每个位置的最终答案（省略）
```
**十年 OI 一场空，不开`long long`见祖宗！**

**注意数组大小！**

---

## 作者：A2_Zenith (赞：0)

想象一手，假设这个牛奶是有颜色的，初始时第 $i$ 桶牛奶具有颜色 $i$。那么在第 $k$ 天时，颜色 $i$ 的牛奶应该还剩下 $\min\limits_{j=i}^{i+k}a_j$。那么第 $k$ 天剩的总奶量应该就是 $\sum\limits_{i=1}^n\min\limits_{j=i}^{i+k}a_j$。下标按模 $n$ 理解。

这个时候，还是考虑一个算贡献的想法。对于 $i$，只要我们能够算出对于每个时刻 $k$，有多少 $\min\limits_{j=t}^{t+k} a_j = a_i$（这里我们认为，如果 $a_i$ 不是 $[t,t+k]$ 中最靠前的最小值，那么等号两端时不相等的），这个题就做完了。

我们不妨直接令 $L_i$ 为从 $i$ 往前（$i-1$ 的方向）数时最后一个满足 $a_j>a_i$ 的下标 $j$，$R_i$ 为从 $i$ 往后（$i+1$ 的方向）数时最后一个满足 $a_i \le a_j$ 的下标 $j$。那么，对于 $t \in [L_i,i]$，$k \in [i-t,R_i-t]$，$\min\limits_{j=t}^{t+k} a_j = a_i$。这是容易验证的。

也就是说，我们要做 $i-L_i+1(t \in [L_i,i])$ 次区间加，具体内容是给 $ans_k(k \in [i-t,R_i-t])$ 加上 $a_i$。

注意到这个操作我们做一次差分后 做 $2(L_i-i+1)(t \in [L_i,i])$ 次单点加，具体内容是给 $ans_{i-t}$ 加上 $a_i$，给 $ans_{R_i-t+1}$ 加上 $a_i$。

这东西依旧是差分序列上的两次区间加，再差分一次得到 $ans_0 \leftarrow ans_0 + a_i,ans_{i-L_i+1} \leftarrow ans_{i-L_i+1} -a_i,ans_{R_i-i+1} \leftarrow ans_{R_i-i+1} -a_i,ans_{R_i-L_i+2} \leftarrow ans_{R_i-L_i+2} +a_i$。做完了。时间复杂度是 $\mathcal{O}(n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define doub long double
#define PII pair<int,int>
using namespace std;
const int N=5e5+7;
stack<int> st;
int n,a[N*3],L[N*3],R[N*3],d[N*3];
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];for(int i=n+1;i<=3*n;i++)a[i]=a[i-n];
    for(int i=1;i<=3*n;i++){
        while(!st.empty()&&a[st.top()]>a[i])R[st.top()]=i-1,st.pop();
        st.push(i);
    }while(!st.empty())R[st.top()]=3*n,st.pop();
    for(int i=3*n;i>=1;i--){
        while(!st.empty()&&a[i]<=a[st.top()])L[st.top()]=i+1,st.pop();
        st.push(i);
    }while(!st.empty())L[st.top()]=1,st.pop();
    for(int i=n+1;i<=2*n;i++){
        d[0]+=a[i];
        d[i-L[i]+1]-=a[i];
        d[R[i]-i+1]-=a[i];
        d[R[i]-L[i]+2]+=a[i];
    }for(int i=1;i<=n;i++)d[i]+=d[i-1];
    for(int i=1;i<=n;i++)d[i]+=d[i-1],cout<<d[i]<<endl;
    return 0;
}
```

---

## 作者：rainygame (赞：0)

模拟赛 1.5h 爆切 T1，并荣获全场最菜解。/kk

首先容易想到在每个桶的地方计算贡献，即它从上一个拿来时损失的牛奶。假设这是一个序列而不是一个环，维护一个递增的单调栈，设 $i$ 前面第一个小于等于 $a_i$ 的是 $a_j$，那么 $(j,i)$ 这部分的牛奶到 $i$ 时都会有损耗。注意到损耗即为弹栈时弹出的那些点减去 $a_i$ 的值，可以在弹栈的过程中求出一组 $(t_k,v_k)$ 表示 $[t_k,t_{k+1})$ 这段时间的损耗为每秒 $v_k$。

现在序列变成了环，不过也没有关系，可以用二分+ST 表求出和单调栈一样的信息。具体地，从后往前每次求出第一个 $[j,n]$ 最小值小于最后的 $v_k$ 的值，特判一些情况即可。

最后需要类似区间加等差数列的操作，但我不会。但可以用 BIT 维护差分数组区间加操作，最后再做一次前缀和就可以了，时间复杂度 $O(n \log n)$。

```cpp
#pragma GCC optimize(2, 3, "Ofast")
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 500005
#define MAXK 19

int n, m, s;
int a[MAXN], pre[MAXN], f[MAXN][MAXK];
vector<pair<int, int>> vec[MAXN];
stack<int, vector<int>> st;

int qry(int l, int r){int k(__lg(r-l+1)); return min(f[l][k], f[r-(1<<k)+1][k]);}

namespace BIT{
#define lbw(x) ((x) & -(x))
    int c[MAXN];
    void add(int x, int k){for (; x<=n; x+=lbw(x)) c[x] += k;}
    void add(int l, int r, int k){add(l, k); add(r+1, -k);}
    int qry(int x){int res(0); for (; x; x-=lbw(x)) res += c[x]; return res;}
}
void add(int l, int r, int d){BIT::add(l, r, d);}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n; for (int i(1); i<=n; ++i) cin >> a[i], f[i][0] = a[i], s += a[i];
    for (int i(1); i<=n; ++i){
        while (st.size() && a[st.top()] > a[i]){
            vec[i].push_back({i-st.top(), a[st.top()]}); st.pop();
        }
        pre[i] = st.empty() ? -1 : i-st.top()-1; st.push(i);
    }
    for (int j(1); j<MAXK; ++j) for (int i(1); i+(1<<j)-1<=n; ++i) f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
    for (int i(1); i<=n; ++i) if (pre[i] == -1){
        while (true){
            int l(i), r(n), mid;
            while (l < r){
                mid = (l+r+1)>>1;
                if (qry(mid, n) < (vec[i].size() ? vec[i].back().second : INT_MAX)) l = mid; else r = mid-1;
            }
            if (l == i){pre[i]=n-1; break;} if (a[l] <= a[i]){pre[i]=n-l+i-1; break;} vec[i].push_back({n-l+i, a[l]});
        }
    }
    for (int i(1); i<=n; ++i) vec[i].push_back({pre[i]+1, 0});
    for (int i(1); i<=n; ++i){
        for (int j(0); j+1<vec[i].size(); ++j) add(vec[i][j].first, vec[i][j+1].first-1, vec[i][j].second-a[i]);
    }
    for (int i(1), q(0); i<=n; ++i) cout << (s -= BIT::qry(i)) << '\n';

    return 0;
}

```

---

