# Number of Ways

## 题目描述

You've got array $ a[1],a[2],...,a[n] $ , consisting of $ n $ integers. Count the number of ways to split all the elements of the array into three contiguous parts so that the sum of elements in each part is the same.

More formally, you need to find the number of such pairs of indices $ i,j $ $ (2<=i<=j<=n-1) $ , that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF466C/6d268bd0e5773093a8b59275245964aa2b1c55f9.png).

## 样例 #1

### 输入

```
5
1 2 3 0 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 1 -1 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
4 1
```

### 输出

```
0
```

# 题解

## 作者：Mistybranch (赞：18)

[传送门](https://www.luogu.com.cn/problem/CF466C)

题目大概意思是：将一个数组分成连续的三段，有几种分法可以使三段和相等。

因为这道题要不停的进行区间求和，所以说自然就会想到前缀和，下面以样栗为栗说思路：

```
5
1 2 3 0 3
```
这个数组从前往后的前缀和 $sum$ 为：

```
1 3 6 6 9
```
```cpp
for (int i = 1; i <= n; i++) {
	scanf("%lld", &ai);
	sum[i] = sum[i - 1] + ai;
}
```

我们设数组分成的三段中第二段第一个数的下表为 $i$，第三段第一个数的下表为 $j$，满足 $i < j$。

- 判断数组总和是否能被 $3$ 整除，如果不能，就输出 $0$，结束（如果不能被 $3$ 整除说明数组不能被分成和相等的三段）。

这里发现 $9$ 能被 $3$ 整除，不结束。

```cpp
if (sum[n] % 3 != 0) {
	printf("0\n");
	return 0;
}
```


- 否则从前往后遍历数组。

1. 如果当前 $sum_i$ 为 $sum_n \times \dfrac{1}{3}$，这个位置可以为 $i$。

2. 如果当前 $sum_i$ 为 $sum_n \times \dfrac{2}{3}$，这个位置可以为 $j$。此时答案加上 $j$ 之前可以为 $i$ 的数量。

```cpp
for (int i = 1; i <= n; i++) {
	if (i > 1 && i < n && sum[i] == sum[n] * 2 / 3) {
		res += cc;
	}
	
	if (sum[i] == sum[n] / 3) {
		cc++;
	}
}
```
完整代码：
```cpp


#include <bits/stdc++.h>

int n; 
long long sum[500009], res;

int main () {
	long long cc = 0, ai;
	
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &ai);
		sum[i] = sum[i - 1] + ai;
	}
	
	if (sum[n] % 3 != 0) {
		printf("0\n");
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		if (i > 1 && i < n && sum[i] == sum[n] * 2 / 3) {
			res += cc;
		}
		
		if (sum[i] == sum[n] / 3) {
			cc++;
		}
	}
	
	printf("%lld", res);
	
	return 0;
}

```


---

## 作者：wxzzzz (赞：7)

### 题意

求将 $a$ 序列分为 $3$ 等份的方案数。

### 思路

转化题意：求有多少能将 $a$ 序列分为 $3$ 等份的断点组合。

断点的性质：既然是分为 $3$ 等份，那么断点有两个，断点 $1$ 之前的数之和是整个序列之和的 $\dfrac{1}{3}$，断点 $2$ 之前的数之和是整个序列之和的 $\dfrac{2}{3}$。

知道性质，就可以枚举了，枚举断点前的位置 $i$。

如果 $i$ 满足第一个断点，将断点 $1$ 的数量累积；如果满足第二个断点，将答案累计**当前**第一个断点的方案数（因为断点 $1$ 必须在断点 $2$ 之前）。

注意，断点 $1$ 需要满足 $i<n-1$，因为之后至少有两个数；断点 $2$ 需要满足 $1<i<n$，因为前面至少有两个数，后面至少一个数。

最后，要特判 $i<3$ 以及序列的和不能被 $3$ 整除的情况，无解。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, sum, ans, a[500005];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], a[i] += a[i - 1];
	}

    if (n < 3 || a[n] % 3 != 0) {
        putchar('0');
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (1 < i && i < n && a[i] == a[n] / 3 * 2)
            ans += sum;
        if (i < n - 1 && a[i] == a[n] / 3)
            sum++;
    }

    cout << ans;
    return 0;
}
```

---

## 作者：noble_ (赞：6)

先做一下从前往后的前缀和和**从后往前**的前缀和。

因为要把原式分成三段，且相等。所以每一段都是$ Allsum / 3$。

我们再用个数组 $ c $记录一下$ [x,n]$中$ sum[i,n] = Allsum/3$的数量，其中$ i>=x $

这个是比较好做的，用我们从后往前的前缀和，如果$ sum[i,n]=Allsum/3 $。那么$ c[i]=1 $。

最后对$ c$求从后往前的前缀和就求出来了。


然后我们枚举一下$ i $，如果$ sum[1,i] = Allsum/3$，那么$ ans+=c[i+2] $（为什么是+2想想就明白了）



吐槽：感觉这题应该是普及+的。

---

## 作者：Kacho (赞：2)

好吧，最近一直都在刷前缀和的题目，主要是实在是前缀和太差了，也可以说基本忘光了。

这一道题，一开始的想法，很简单，一个 $i$ 和一个 $j$ 不就解决了的事情吗？一看数据范围：$1 \le n \le 500000$，如果真的按照这个做法来做的话，时间复杂度很显然是 $O(n^2)$，那么暴毙是跑不了的，所以我们来重新省视题意：平均分成三份，找到这个段数中间的数的数量。

那么我们有一件要先做的事情就是判断这个数列的总和能不能被3整除。
```cpp
n = R;
for(int i = 1; i <= n; i++){
   a[i] = R;
   sum += a[i];//求出数列和
}

if(sum % 3 != 0){//特判一下，因为如果这个数列和不能够被3整除的话
    		 //显然是不能找到解的
   printf("0\n");
   return 0;
}
_3 = sum / 3;//求出1/3的数值，为后面的前缀和数组做准备
sum = 0;//把sum清空，准备做另一个数组的累加器
```

这个时候，我们拥有个数列和的1/3的变量 $one-third$。

这个时候，我们可以做两次对于 $i$ 的遍历，分别用 $tag1$ 和 $tag2$ 数组进行记录。

一遍的 $i$ 从头开始遍历，这个时候如果 $sum = one-third$ 那么就把这个 $tag1[i]$ 记为1，并且把 $sum$ 重新归零。第二遍的 $i$ 从后开始往前遍历，此时开始累加 $sum$， 如果 $sum = one-third$ 那么把这个 $tag2[i]$ 记录为1。代码如下：
```cpp
for(int i = 1; i <= n; i++){
   sum += a[i];
   if(sum == _3) tag1[i] = 1;
}

sum = 0;
for(int i = n; i > 0; i--){
    sum += a[i];
    if(sum == _3) tag2[i] = 1;
}
```
之后就是用一个 $s[n - 2]$ 来储存一个前缀和的事情了，存储的就是 $tag1[1 $~$ n]$ 的总和，为什么是 $s[n - 2]$ 呢？因为我们对于数列的分点是做了两次的，也就是说，我们所要统计的起点到终点就是 $s[n - 2]$,如果继续往下做，会重复，会错。

那么上代码：
```cpp
for(int i = 1; i <= n; i++){
   s[i] = s[i - 1] + tag1[i];
}
```
接下来就是统计 $ans$ 的时候了，此时要做的就是用 $tag2 \times s[i - 2]$很简单的代码，就不给出sample了。

下面上AC的代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()

const int N = 1000005;

using namespace std;


inline int read() {
	int X = 0;
	bool flag = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') flag = 0;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		X = (X << 1) + (X << 3) + ch - '0';
		ch = getchar();
	}
	if(flag) return X;
	return ~(X-1);
}

int n, a[N], sum, _3;
bool tag1[N], tag2[N];
int ans, s[N];

signed main (){

    n = R;
    for(int i = 1; i <= n; i++){
        a[i] = R;
        sum += a[i];
    }

    if(sum % 3 != 0){
        printf("0\n");
        return 0;
    }
    _3 = sum / 3;
    sum = 0;

    for(int i = 1; i <= n; i++){
        sum += a[i];
        if(sum == _3) tag1[i] = 1;
    }

    sum = 0;
    for(int i = n; i > 0; i--){
        sum += a[i];
        if(sum == _3) tag2[i] = 1;
    }   

    for(int i = 1; i <= n; i++){
        s[i] = s[i - 1] + tag1[i];
    }

    for(int i = 3; i <= n; i++){
        ans += tag2[i] * s[i - 2];
    }

    printf("%lld\n", ans);

    return 0;
    
}
```
总结一下，难度其实挺大的，但是做好几个判断就好了，分点计数也做好就没有问题了。

---

## 作者：AC_Automation (赞：1)

我们有一个数组 a。我们要将其分成三份，使得这三份的和相等。我们用 kk 代表每一份的和。

很明显，$O(n^2)$的枚举一定会超时。这里我们考虑分别枚举之后统计答案。

考虑记录 bool 数组$b1_i$和$b2_i$。

当$\sum_{k=1}^ia_k=kk$时，令$b1_i=1$，否则，$b1_i=0$。

当$\sum_{k=i}^na_k=kk$时，令$b2_i=1$，否则，$b2_i=0$。

这样的话，我们就可以统计答案了！对于每个$b2_i=1$，可以与其对应的分割方案数量即为在 i-1 左侧的$b1_i=1$的数量。前缀和维护即可。

```cpp
#include<iostream>
#define int long long
using namespace std;
int a[500005];
bool b1[500005],b2[500005];
int c[500005];
signed main(){
	int n,sum=0,kk;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
	if(sum%3!=0){
		cout<<0;
		return 0;
	}//特判出局
	kk=sum/3;
	sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i];
		if(sum==kk)b1[i]=1;
	}//统计b1数组
	sum=0;
	for(int i=n;i>0;i--){
		sum+=a[i];
		if(sum==kk)b2[i]=1;
	}//统计b2数组
	for(int i=1;i<=n;i++){
		c[i]=c[i-1]+b1[i];
	}//前缀和
	int ans=0;
	for(int i=3;i<=n;i++){
		ans+=b2[i]*c[i-2];
	}//统计答案
	cout<<ans;
	return 0;
}

```


---

## 作者：Apro1066 (赞：1)

有前缀和的地方，怎么能缺少树状数组呢？（雾）

题目大意是给定长为$n$的序列$a_{i}$，将其分成3个连续子串，要求每个子串的和相同，求划分的方案数。

具体看一下代码，还是和纯前缀和的做法很像的。

```cpp
#include <stdio.h>
#include <iostream>
using namespace std;
long long int a[500001],bit[500001],n,s,t,lxydl,cnt;
inline int lowbit(int x)
{
	return x&-x;
}
inline void update(int x,int k)
{
	cnt++;//记录多少个符合总和2/3的 
	while(x<=n)
	{
		bit[x]+=k;//全部加上1 
		x+=lowbit(x);
	}
}
inline int query(int x)//查询 
{
	int sum(0);
	while(x>0)
	{
		sum+=bit[x];
		x-=lowbit(x);
	}
	return sum;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		s+=a[i];//求序列总和 
	}
	if(s%3)//总和不被3整除肯定无解 
	{
		cout<<0<<endl;
		return 0;
	}
	for(i=1;i<=n;i++)
	{
		t+=a[i];//不断加
		if(t==s/3*2 && i!=n)//如果找到总和2/3的，就记录到树状数组，此时树状数组的意义是记录总和2/3的区间 
		{
			update(i,1);//更新 
		}
	}
	for(t=0,i=1;i<=n;i++)//在扫一遍 
	{
		t+=a[i];
		if(t==s/3)//若找到总和1/3
		{
			lxydl=lxydl+cnt-query(i);//2/3的总数减去2/3的区间 
		}
	}
	cout<<lxydl<<endl;
	return 0;
}
```


---

## 作者：迟暮天复明 (赞：1)

好像我的做法和条件取得所有做法都不一样。
## Description
给定一个数组，求有多少组 $i,j$ 将整个数组分成和相等的三个数组。
## Solution
从左往右看一遍，记录每一个 $i$ 使得 $\sum_{k=1}^i a_k = \dfrac{S}{3}$

从右往左看一遍，记录每一个 $j$ 使得 $\sum_{k=j}^n a_k = \dfrac{S}{3}$

然后如果不出意外的话，每组 $i,j$ 都是所求的数对，但要小心一点，就是 $\{1,i\}$ 和 $\{j,n\}$ 两个区间可能交叉！所以要筛选出不交叉的区间。

怎样筛选呢？我定义一个当前指针 $cur$ ，我扫到每一个 $i$ 时，将 $cur$ 移到满足第 $cur$ 个 $j$ 的下标严格大于这个 $i$ 的下标 $+1$ ，则从 $cur$ 及以后的所有 $j$ 都能和当前 $i$ 匹配。

为什么是下标 $+1$ 呢？因为要给第二个区间留位置。

于是这个题目就做完了。记得开 $long\;long$ ！

## Code
```cpp
#define int ll
int n, a[500010], ansl[500010], ansr[500010], cntl, cntr, ans, s[500010];

signed main() {
  int cur = 1;
  read(n);
  rep(i, 1, n) read(a[i]), s[i] = s[i - 1] + a[i];
  if(s[n] % 3) {
    print(0);
    goto end;
  }

  rep(i, 1, n) if(s[i] == s[n] / 3) ansl[++cntl] = i;
  rep(i, 1, n) if(s[n] - s[i - 1] == s[n] / 3) ansr[++cntr] = i;
  
  rep(i, 1, cntl) {
    while(ansr[cur] <= ansl[i] + 1 && cur <= cntr) ++cur;
    ans += cntr - cur + 1;
  }
  print(ans);

end:
  return 0;
}
```


---

## 作者：Light_Star_RPmax_AFO (赞：0)

 思路——前缀和 + 后缀和 

**暴力**

```cpp
#include <bits/stdc++.h>
#define F(i,j,k) for(int i=j;i<=k;i++)
using namespace std;

int n, a[500010],s,ans;

int main() {
	cin >> n;
	F(i, 1, n) {
		cin >> s;
		a[i] = a[i - 1] + s;
	}
	if (a[n] % 3 != 0) {
		cout << '0';
		return 0;
	}
	F(i, 1, n-2) {
		F(j, i+1, n-1) {
			if (a[j] - a[i] == a[n] - a[j] && a[n] - a[j] == a[i]) {
				ans++;
			}
		}
	}
	cout << ans;
}
```
这样就 AC 了 $\dfrac{5}{6}$。

**Part 1**

不难想到将一个序列分为 **相等的三份**，其实每一份就是 **序列和** 的 $\dfrac{1}{3}$。

**Part 2**

如果序列不能被 $3$ 整除，那么就是无解的，输出 $0$。

**Part 3**

先确定 $\sum\limits_{k=1}^{i-1}a_k$ 和 $\sum\limits_{k=j+1}^{n}a_k$ 两个，因为已经确定了其中一个累加端点，如果两个都为 **序列和** 的 $\dfrac{1}{3}$ 那么最后一个也是。

这样就分成了相等的三份。

**Part 4**

再次使用前缀和，找到 每个数之前 的可以有几个为 **序列和** 的 $\dfrac{1}{3}$ 的数累加就可以了。

 **AC Code**

```cpp
#include <bits/stdc++.h>
#define F(i,j,k) for(int i=j;i<=k;i++)
#define int long long
using namespace std;

int n, a[500010], ans,sum;
int s[500010];
int use1[500010], use2[500010];

signed main() {
	cin >> n;
	F(i, 1, n) {
		cin >> a[i];
		sum += a[i];
	}
	if (sum % 3 != 0) {
		cout << '0';
		return 0;
	}
	sum /= 3;
	for (int i = 1, sums = 0; i <= n; i++) {
		sums += a[i];
		if (sums == sum)use1[i] = 1;
	}
	for (int i = n, sums = 0; i >= 3; i--) {
		sums += a[i];
		if (sums == sum)use2[i] = 1;
	}
	for (int i = 1; i <= n-2; i++) {
		s[i] = s[i - 1] + use1[i];
	}
	for (int i = 3; i <= n; i++) {
		ans += use2[i] * s[i - 2];
	}
	cout << ans;
}
```


---

