# [JOIG 2024] たくさんの数字 / Many Digits

## 题目描述

JOI 高中的 Aoi 决定在 $N\times N$ 的表格中写下 $N^2$ 个非负整数。具体地，给定两个长度为 $N$ 的序列 $A,B$，她会在第 $i$ 行第 $j$ 列的格子上写下 $A_i+B_j$。

Aoi 想知道写出这些数需要多少个字符。也就是说，你需要求出写出的 $N^2$ 个整数在十进制下的位数的和。

## 说明/提示

#### 【样例解释 #1】

|$+$|$\textbf{20}$|$\textbf{2}$|$\textbf{21}$|
|:-:|:-:|:-:|:-:|
|$\textbf{97}$|$117$|$99$|$118$|
|$\textbf{79}$|$99$|$81$|$100$|
|$\textbf{7}$|$27$|$9$|$28$|

未加粗字体为 Aoi 填写的内容。

例如，第 $1$ 行第 $1$ 列的方格中的整数为 $A_1 + B_1 = 97 + 20 = 117$，位数为 $3$。第 $3$ 行第 $2$ 列的方格中的整数为 $A_3 + B_2 = 7 + 2 = 9$，位数为 $1$。

$9$ 个数的位数分别为 $3, 2, 3, 2, 2, 3, 2, 1, 2$，故位数之和为 $3 + 2 + 3 + 2 + 2 + 3 + 2 + 1 + 2 = 20$。

该样例满足子任务 $2,3,8$ 的限制。

#### 【样例解释 #2】

|$+$|$\textbf{1}$|$\textbf{2}$|$\textbf{3}$|$\textbf{4}$|
|:-:|:-:|:-:|:-:|:-:|
|$\textbf{8}$|$9$|$10$|$11$|$12$|
|$\textbf{97}$|$98$|$99$|$100$|$101$|
|$\textbf{996}$|$997$|$998$|$999$|$1000$|
|$\textbf{9995}$|$9996$|$9997$|$9998$|$9999$|

未加粗字体为 Aoi 填写的内容。

例如，第 $2$ 行第 $3$ 列的方格中的整数为 $A_2 + B_3 = 97 + 3 = 100$，位数为 $3$。第 $4$ 行第 $2$ 列的方格中的整数为 $A_4 + B_2 = 9995 + 2 = 9997$，位数为 $4$。

可以得出答案为 $46$。

该样例满足子任务 $2,6,7,8$ 的限制。

#### 【样例解释 #3】

方格中仅有一个整数 $10^9$，位数为 $10$，故位数之和为 $10$。

该样例满足子任务 $1,2,4,5,8$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $2,5,8$ 的限制。

#### 【数据范围】

- $1\le N\le 1.5\times 10^5$；
- $1\le A_i\le 999,999,999(1\le i\le N)$；
- $1\le B_j\le 999,999,999(1\le j\le N)$。

#### 【子任务】

1. （$5$ 分）$N=1$；
2. （$11$ 分）$N\le 2000$；
3. （$15$ 分）$A_i\le 2000(1\le i\le N)$，$B_j\le 2000(1\le j\le N)$；
4. （$8$ 分）$10^8\le A_i\le 5\times 10^8(1\le i\le N)$，$10^8\le B_j\le 5\times 10^8(1\le j\le N)$；
5. （$22$ 分）$10^8\le A_i(1\le i\le N)$，$10^8\le B_j(1\le j\le N)$；
6. （$12$ 分）$A_i\le 1.5\times 10^5(1\le i\le N)$，$B_j = j(1\le j\le N)$；
7. （$13$ 分）$B_j=j(1\le j\le N)$；
8. （$14$ 分）无附加限制。

## 样例 #1

### 输入

```
3
97 79 7
20 2 21```

### 输出

```
20```

## 样例 #2

### 输入

```
4
8 97 996 9995
1 2 3 4
```

### 输出

```
46```

## 样例 #3

### 输入

```
1
500000000
500000000```

### 输出

```
10```

## 样例 #4

### 输入

```
7
436981378 523812834 456708479 413571178 506402783 598271009 523936624
401203104 501634329 506090236 527167431 485527116 439442403 568364549```

### 输出

```
463```

# 题解

## 作者：Xuan_qwq (赞：5)

我们知道，一个数 $x$ 有 $k$ 位，等价于 $10^{k-1} \leq x < 10^{k}$。

那么，$a_i+b_j$ 有 $k$ 位等价于 $10^{k-1} \leq a_i+b_j < 10^{k}$，即 $10^{k-1}-a_i \leq b_j < 10^{k}-a_i$。

所以我们考虑枚举每一个 $a_i$，对所有 $1\le k \le 10$ 计算 $B$ 中满足 $10^{k-1}-a_i \leq b_j < 10^{k}-a_i$ 的 $b_i$ 数量 $s_{i,k}$，这可以很容易地用 `lower_bound` 函数求出。

最终答案为：
$$ans=\sum_{i=1}^n \sum_{k=1}^{10}s_{i,k}\times k$$

至于为什么只需要计算 $1\le k \le 10$ 即可，是因为 $a_i+b_j$ 的最大值不超过 $999999999+999999999=1999999998 < 10^{10}$，所以一个和最多只有 $10$ 位。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[150005],b[150005],n,ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++)cin>>b[i];
	sort(b,b+n);
	for(int i=0;i<n;i++){
		int lim=1;//lim为10的k-1次方
		for(int k=1;k<=10;k++){
			if(lim*10<a[i]){//小优化，如果a[i]>10^k，那就不用算
				lim*=10;
				continue;
			}
			int ps1=lower_bound(b,b+n,lim-a[i])-b;
			int ps2=lower_bound(b,b+n,lim*10-a[i])-b;
			ans+=k*(ps2-ps1);//计算 k*s[i][k]
			lim*=10;
			if(b[n-1]+a[i]<lim)break;//和上面差不多的小优化
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：3)

## 1. 题目分析
做题先看数据范围，首先我们肯定都能想到 $O(n^2)$ 的暴力做法，绝对是过不了的。所以我们需要用一些算法进行优化，我使用的是排序加二分。
## 2. 题目做法
我们可以想到对于 $A$ 数组中的每一个数 $a$，我们可以求出 $B$ 数组中有多少数小于等于 $a$，并且其中有多少个数与 $a$ 相加可以进位。如何判断是否可以进位呢，设 $a$ 的位数为 $x$，如果一个数大于等于 $10^x - a$，它与 $a$ 相加便可进位。先对 $B$ 数组排序，再用二分统计答案即可。  
这样做的话，那么我们还要用 $B$ 数组反过来扫一遍，但是对于每一个 $b$，我们只能先求出小于 $b$ 的在 $A$ 数组中的数，否则会算重。其余步骤都一样。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=150010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n;
int efind(int x[],int y)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(x[mid]<=y)
			l=mid+1;
		else
			r=mid;
	}
	x[l]>y?l--:1;
	return l;
}
int efind2(int x[],int y)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(x[mid]<y)
			l=mid+1;
		else
			r=mid;
	}
	x[l]>=y?l--:1;
	return l;
}
int a[N],b[N],t,tt,w,ww;
long long sum;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		t=a[i],w=0;
		while(t)
			w++,t/=10;
		ww=pow(10,w);
		t=efind(b,a[i]);
		tt=min(efind2(b,ww-a[i]),t);
		sum+=tt*w+(t-tt)*(w+1);
	}
	for(int i=1;i<=n;i++)
	{
		t=b[i],w=0;
		while(t)
			w++,t/=10;
		ww=pow(10,w);
		t=efind2(a,b[i]);
		tt=min(efind2(a,ww-b[i]),t);
		sum+=tt*w+(t-tt)*(w+1);
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：Eason_cyx (赞：2)

有意思题，**注意数据范围是 $1.5 \times 10^5$，不是 $10^5$，感谢 @[Ljx19223112](/user/1213719) 帮助。**

以下用 $|a_i|$ 表示正整数 $a_i$ 的位数。

首先 $\Theta(n^2)$ 可以获得 $16$ 分，这个复杂度显然不够用。

因为所有的 $a_i,b_j < 10^9$，所以总位数不会超过 $10$ 位。那么对于一个 $a_i$，显然和一个正整数加起来获得的最小位数就是 $|a_i|$。那么我们枚举最终位数是多少位。假设现在枚举到 $a_i$ 加上一个 $b_j$ 之后是 $k+1$ 位数，那么显然有 $10^k-a_i \le b_j < 10^{k+1}-a_i$，因为我们只关心位数之和，所以我们可以算出来 $b$ 数组中所有满足这个条件的 $b_j$，这个过程可以用二分来完成。记 $b_l \sim b_r$ 之间的数都满足上面的条件，则这些数对答案贡献就是 $(r-l+1)\times(k+1)$。

时间复杂度 $\Theta(n\log n)$，主要开销在 $b$ 数组的排序（为了进行二分）。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],b[200005];
long long p10[25];
int len(int x) {
	int cnt = 0;
	while(x) cnt++,x /= 10;
	return cnt;
}
signed main() {
	p10[0] = 1;
	for(int i = 1;i <= 18;i++) p10[i] = p10[i-1] * 10;
	int n; cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) cin >> b[i];
	sort(b+1,b+n+1);
	int ans = 0;
	for(int i = 1;i <= n;i++) {
		int siz = len(a[i]) - 1;
		while(true) {
			int cha1 = p10[siz] - a[i],cha2 = p10[siz+1] - a[i];
			if(cha1 > b[n]) break;
			int pos1 = lower_bound(b+1,b+n+1,cha1) - b,pos2 = lower_bound(b+1,b+n+1,cha2) - b - 1;
			ans += (siz + 1) * (pos2 - pos1 + 1);
			siz++;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：kuaiCreator (赞：2)

# P11201 [JOIG 2024 Open] たくさんの数字 / Many Digits
## 题目大意
给定 $n$ 个元素数组 $a$ 和数组 $b$。将 $a_i+b_j$ 填入二维矩阵的第 $i$ 行和第 $j$ 列。求出该矩阵中每个数字的位数总和。
## 解题思路
考虑 $n$ 的数据范围为 $1.5\times 10^5$，不能直接模拟即超时间也超空间。  
满分思路为二分查找，即首先先将两个数组按从小到大排序，然后求出两个数组和的最小与最大值的位数。枚举数组 $a$ 中的每一个元素，查找 $b$ 中和为某一位数的元素的左右界，这里还需要枚举具体的位数，由于位数并不大，最多为 $11$ 位，这层枚举可以视为常数。  
时间复杂度为 $O(n\log{n})$，空间复杂度为 $O(n)$ 能够通过本题。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef  long long ll;
const int N = 1.5e5+5;
ll n, a[N], b[N], ans;
int getLen(int x) {		//获取位数
	int cnt = 0;
	while (x)  cnt++, x /= 10;
	return cnt;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	sort(a + 1, a + 1 + n);				//排序数组a
	sort(b + 1, b + 1 + n);				//排序数组b
	int minLen = getLen(a[1] + b[1]);	//获得最小数的位数
	int maxLen = getLen(a[n] + b[n]);	//获得最大数的位数
	for (int i = 1; i <= n; i++) {		//枚举数组 a
		for (int len = minLen; len <= maxLen; len++) {	//枚举长度 len
			ll lb = pow(10, len - 1);	//获得长度为len的最小值
			ll rb = pow(10, len) - 1;	//获得长度为len的最大值
			int l = lower_bound(b + 1, b + 1 + n, lb - a[i]) - b;	//二分查找左界
			int r = upper_bound(b + 1, b + 1 + n, rb - a[i]) - b;	//二分查找右界
			ans += (r - l) * len;		//获取a[i]+b[j]长度len的元素对数并乘上位数
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：_Weslie_ (赞：2)

除了搬题人之外的首 A，来纪念一下。

## Solution P11201

### Idea

我们先对 $b$ 数组排序，然后枚举 $a$ 数组。

不难发现：对于 $a_i$，假如最后写出的数有 $k$ 位，则一定有 $10^{k-1}-a_i\le b_j < 10^k-a_i$。

不难发现对于每一个 $k$ 对应的都是一个连续区间，于是可以二分。

具体实现起来，可以用 `lower_bound` 快速解决。

讲一下下面代码里的 `lpos` 和 `now` 为什么可行：你会发现对于 $k_1-k_2=1$ 的情况，两个要求分别是 $10^{k_2-1}-a_i \le b_j < 10^{k_2}-a_i$ 及 $10^{k_1-1}-a_i \le b_j < 10^{k_1}-a_i$。代入 $k_1-1=k_2$ 可得第一个式子是 $10^{k_1-2}-a_i \le b_j < 10^{k_1-1}-a_i$。两个式子一综合，这个显然就可行了。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=150005;
int n,a[N],b[N];
const int mi10[10]={0,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
long long ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	sort(b+1,b+n+1);
	for(int i=1,lpos,now;i<=n;i++){
		lpos=n+1;
		for(int j=9;j>=0;j--){
			now=lower_bound(b+1,b+n+1,mi10[j]-a[i])-b;
			ans=ans+1ll*(lpos-now)*(j+1);
			lpos=now;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ny_jerry2 (赞：1)

## 思路
这道题我们暴力是行不通的。  
我采用的是 _**排序加二分**_ 。

首先，我们对整个序列排个序（第二个序列）。

接下来，遍历每一个第一个序列中的元素，同时遍历可能会构成的位数。

在这里，我们可以求出满足条件的最小值与最大值，因此可以使用二分，这样我们就算出了每一个元素关于该位数可能产生的贡献。  
因为之前排了序，因此单调性可以保证。

时间复杂度：大约 $O(n \log n)$（算得不是很精准，中间会有很大的常数）。
## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=2e5;
int a[N],b[N];
int n;
int len(int x){
	int sum=0;
	while(x){
		x/=10,sum++;
	}
	return sum;
}
int find2(int x,int y){
	int l=1,r=n;
	while(l<r){
		int mid=(l+r+1)>>1;
		int c=len(b[mid]+y);
		if(c>x){
			r=mid-1;
		}else{
			l=mid;
		}
	}
	return l;
}
int find(int x,int y){
	int l=1,r=n;
	while(l<r){
		int mid=(l+r)>>1;
		int c=len(b[mid]+y);
		if(c<x){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
	sort(b+1,b+n+1);
	long long sum=0;
	for(int i=1;i<=n;i++){
		for(int j=len(a[i]);j<=12;j++){
			int l=find(j,a[i]);
			int r=find2(j,a[i]);
			int y=len(a[i]+b[l]);
			if(y!=j){
				continue;
			}
			sum+=1ll*(r-l+1)*j;
		}
	}
	cout<<sum;
}
```

---

## 作者：yanlikun (赞：0)

# 思路
观察数据范围，发现 $O(n^2)$ 做法无法通过。然而，通过观察样例二，可以发现，我们对 $b$ 数组排完序之后，得到的二维表格每一行的每一个数的位数都是单调不减的。因此，我们先预处理出 $k$ 位数的最小值，即 $10^k$ ，得到数组 $opt$ 。此时，对于每个数 $a_i$ ，在排好序的 $b$ 数组中二分找到第一个大于等于 $opt_{k+1}-a_i$ ，得到为 $k$ 位数的 $a_i+b_j$ 有多少个，将其贡献相加即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll a[150005],b[150005];
ll opt[20];
ll ans;
int main()
{
	cin>>n;
	ll x=1;
	for(int i=2;i<=18;i++)
	{
		x*=10;
		opt[i]=x;
	}
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		int x=a[i],sum=0,op=0,now=0;
		while(x)
		{
			op=x%10;
			x/=10;
			sum++;
		}
		for(int j=sum;j<=18;j++)//从a[i]的位数开始枚举
		{
			int x=lower_bound(b+1,b+n+1,opt[j+1]-a[i])-b;
			if(x==n+1)
			{
				ans+=j*(x-now-1);
				break;
			}
			if(x==0)
				continue;
			ans+=j*(x-now-1);
			now=x-1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

