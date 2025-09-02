# [ABC381D] 1122 Substring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc381/tasks/abc381_d

正整数からなる（空でも良い）数列 $ X=(X_1,X_2,\ldots) $ が以下の $ 3 $ つの条件をすべてみたすとき、かつそのときに限り、$ X $ を **1122 数列** と呼びます。  
（1122 数列の定義はF問題と共通です。）

- $ \lvert\ X\ \rvert $ は偶数である。ここで、$ \lvert\ X\ \rvert $ は $ X $ の長さを表す。
- $ 1\leq\ i\leq\ \frac{\lvert\ X\ \rvert}{2} $ をみたす整数 $ i $ について、$ X_{2i-1} $ と $ X_{2i} $ は等しい。
- 各正整数は $ X $ に現れないか、ちょうど $ 2 $ 回現れるかのどちらかである。すなわち、$ X $ に含まれる正整数は $ X $ にちょうど $ 2 $ 回ずつ登場する。

正整数からなる長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられるので、$ A $ の **連続する部分列** であって、1122 数列であるようなもののうち最長のものの長さを出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ N $
- 入力はすべて整数

### Sample Explanation 1

例えば $ A $ の $ 3 $ 項目から $ 6 $ 項目までの連続部分列をとると $ (1,1,2,2) $ となりますが、これは長さが $ 4 $ の 1122 数列となっています。 これより長い部分列であって、1122 数列の条件をみたすようなものは存在しないため、$ 4 $ を出力します。

### Sample Explanation 3

項数が $ 0 $ の列も 1122 数列の条件をみたしていることに注意してください。

## 样例 #1

### 输入

```
8
2 3 1 1 2 2 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
1
1```

### 输出

```
0```

# 题解

## 作者：chenxi2009 (赞：13)

# 思路
好多人都分了子串由奇数位开始和偶数位开始讨论。接下来给出一份**代码极短**、不用分讨的思路。

首先发现以 $A_i$ 为结尾的最长合法串的开头 $l_i$ 一定是递增的，我们用一个指针表示 $l$。接下来扫一遍就可以了。

具体而言：如果说当前的数字 $A_i$ 和 $A_{i+1}$ 相同，则可以以 $A_{i+1}$ 为结尾统计一下答案。但是 $A_i$ 这个数字不能再出现，所以计算答案之前要把 $l$ 移到上次 $A_i$ 出现的地方右边。

不同时，要考虑 $A_i$ 还可能和 $A_{i-1}$ 构成一对数字。只有当 $A_i\ne A_{i-1}$ 且 $A_i\ne A_{i+1}$ 时，$A_i$ 才一定不取，这时令 $l\leftarrow i+1$。\
不用担心正确性，如果 $A_i=A_{i-1}$，$A_i$ 和 $A_{i+1}$ 组成一对数字的时候会发现 $i-1$ 处出现了相同的数字，会自动排除掉。
# 代码
精简版代码 13 行。
```cpp
#include<bits/stdc++.h>
int n,a[200002],lst[200001],l = 1,ans;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++)scanf("%d",&a[i]); 
	for(int i = 1;i <= n;i ++){
		if(a[i] == a[i + 1]) l = std::max(l,lst[a[i]] + 1),ans = std::max(ans,i - l + 2);//串左端在上次出现位置后，l 至 i+1 长度为 i-l+2 
		if(a[i] != a[i - 1] && a[i] != a[i + 1]) l = i + 1;//如果出现这种情况，需要强制舍弃当前数 
		lst[a[i]] = i;//标记位置，是处理完 i+1 后才标记的，不影响自己组成数对 
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Little_x_starTYJ (赞：5)

### 前言
2024/11/22 星期五是我的生日。

Atcoder 很良心地把 $A\sim F$ 的题目全都命名为 $11/22$ 或者 $1122$，[详见](https://atcoder.jp/contests/abc381/tasks)。

时隔几个月，又一次排名接近 $1000$（实际排名 $1006$，还吃了 $7$ 发罚时）。

### 题目大意
由正整数组成的数列 $X=(X_1, X_2,\ldots)$ 当且仅当 $X$ 满足以下所有条件时，将 $X$ 称为 **1122 数列**。 
（1122 数列的定义与 F 题相同。）


- $\lvert X\rvert$ 是偶数。其中 $\lvert X\rvert$ 表示 $X$ 的长度。
- 满足任意的 $ 1\leq\ i\leq\frac{\lvert X \rvert}{2}$ 的整数 $i$，都有 $X_ {2i-1}$ 和 $X_ {2i}$ 相等。
- 每个正整数要么不出现在 $X$ 中，要么正好出现 $2$ 次。


给定一个长度为 $N$ 的正整数序列 $A=(A_1, A_2,\ldots, A_n)$，请求出 $A$ 的 **（连续）子序列** 是 1122 数列的最长长度。

### 解题思路
相信大家都做过 HH 的项链，那么这道题一定很简单。

我们一直统计满足题意的字符串的长度。直到某个数字出现了超过 $2$ 次，那么我们将这个数字的第一个出现位置给删除，并将答案减去删除的那么长的长度。

但是这道题并没有让我们求这个字符串，所以我们不用去删除那一堆数，只需要更新答案即可。

时间复杂度为 $\mathcal{O}(n)$。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
int lst[200010];
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int cnt = 0, l = 0, ans = 0;
	for (int i = 2; i <= n; ) {
		ans = max(cnt, ans);

		if (a[i] == a[i - 1]) {
			if (l == 0) {
				l = i;
			}
			if (lst[a[i]] >= l) {
				cnt -= (lst[a[i]] - l);
				l = lst[a[i]] + 2;
			} else {
				cnt += 2;
			}

			lst[a[i]] = i;
			i += 2;
		} else {
			if (cnt != 0) {
				i--;
				l = 0;
				cnt = 0;
			} else {
				i++;
			}
		}
		ans = max(cnt, ans);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：include13_fAKe (赞：4)

我们的做题记录上说这题要 dp，介绍一种不用 dp 的做法。

## 思路

因为所有的有效序列都有若干个重复的数组成。所以考虑拆开奇数位开始和偶数位开始的情况。

以下开设数组 $b$。对于 $1\le i< n$，$b_i= a_i\times[a_i=a_{i+1}]$（实际上我在 $a_i\ne a_{i+1}$ 时我令的是 $b_i=-1$）。相当于 $b$ 数组维护两个信息：

- 当前位置能否作为 $\texttt{1122}$ 序列的一部分。
- 当前位置的 $\texttt{1122}$ 序列里的值。考虑到数不能出现两次以上，该值可以判重。

接下来想判重的方法。

可以用一个 $sum$ 数组，$sum_i$ 表示这个数出现的次数（可合二为一处理），再用单调队列维护 $\texttt{1122}$ 串的首尾，当 $sum_i$ 超过 $\texttt{1122}$ 串可容纳的最大值时，将 $\texttt{1122}$ 串的尾指针往前移。

具体来说是头指针每一次往前移动 $2$ 个单位（原因前面已经解释）。当发现 $sum$ 的值超了就把尾指针往前移**直到 $sum$ 的值不超过规定的范围**（不是往前移两位，笔者交了这样的罚时）。当发现 $b_i$ 无值时，将 $sum$ 清空，因为无论如何从这里往后都不会有 $\texttt{1122}$ 串了。

然后要直接跳到这个 $b_i$ 无值的地方。防止将刚刚扫过的地方重新又扫一次导致时间复杂度退化。

按这样枚举以奇数位置开始和以偶数位置开始的情况。

因为顺序枚举每一个元素都是头指针走一次、尾指针走一次，所以时间复杂度为 $O(n)$ 毫无疑问。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[5*114514];
int b[5*114514];
int sum[5*114514];
int include13=0;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(a[i]==a[i+1]){
			b[i]=a[i];
		}
		else	b[i]=-1;
	}
//	for(int i=1;i<=n;i++){
//		cout<<b[i]<<' ';
//	}
//	cout<<endl;
	for(int i=1;i<=n;i+=2){
//		cout<<'#'<<i<<endl;
		int i1=i;
		int j=i;
		while(~b[j]&&j<=n){
			sum[b[j]]++;
			while(sum[b[j]]==2){
				sum[b[i1]]--;
				i1+=2;
			}
			j+=2;
//			cout<<j-i1<<endl;
			include13=max(include13,j-i1);
		}
		for(int k=i;k<=j;k+=2){
			if(~b[k])	sum[b[k]]=0; 
		}
		i=max(j-2,i);
	}
	for(int i=2;i<=n;i+=2){
//		cout<<'#'<<i<<endl;
		int i1=i;
		int j=i;
		while(~b[j]&&j<=n){
			sum[b[j]]++;
			while(sum[b[j]]==2){
				sum[b[i1]]--;
				i1+=2;
			}
			j+=2;
//			cout<<j-i1<<endl;
			include13=max(include13,j-i1);
		}
		for(int k=i;k<=j;k+=2){
			if(~b[k])	sum[b[k]]=0; 
		}
		i=max(j-2,i);
	}
	cout<<include13<<endl;
	return 0;
} //ABC381D 
```

---

## 作者：rzh01014 (赞：3)

考虑双指针扫描整个数组，同时开桶数组维护左右指针间每个数字的出现次数。根据题意不难发现，只有连续两个数相同且没有出现过才能一直更新，因此根据此性质来右移右指针。若发现当前不满足，右移左指针，直到满足条件。答案为每次右指针右移到最大时当前区间的最大值。时间复杂度为 $O(n)$。   
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],t[N];
signed main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=1,r=1,ans=0;
	while(l<=n&&r<=n){
		while(r<l) t[a[r]]++,r++;
		while(r<=n&&(a[r]==a[r+1]&&t[a[r]]==0)||(a[r]==a[r-1]&&t[a[r]]==1)) t[a[r]]++,r++;
		ans=max(ans,r-l);
		t[a[l]]--,l++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Yxy7952 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc381_d)

建议评黄。

因为文章较长，有错误请指出。
## 题目大意

输入一个长度为 $n$ 的序列 $a$（$1\le a_{i}\le  n$），从这个序列中寻找一个最长的子序列（可以为空）满足下面 $3$ 个要求。

+ 子序列长度为偶数。

+ 每个 $a_{2i}$ 和 $a_{2i−1}$ 都相等。

+ 每个整数只能出现 $0$ 次或 $2$ 次。
## 思路1（双指针）

因为：

>子序列长度为偶数。

所以可以想到从数组的第 $1$ 个和第 $2$ 个下标都枚举一次。这个操作可以封装成函数，方便使用。


每次枚举时，右边界加 $2$，并判断条件是否满足。有两种情况：

### 1.
$a_{r}\ne a_{r+1}$，也就是不满足第 $2$ 个条件，这时因为这两个数不满足条件，包含他们的子序列肯定也不满足条件，所以立即丢弃他们，把标记数组清空，左边界和右边界变成右边界加 $2$。

### 2.
否则，把 $a_{r}$ 和 $a_{r+1}$ 这两个数记录出现次数。继续判断第 $3$ 个条件，如果不满足（即 $f_{a_{r}}>2$，$f$ 是标记数组），那就让左边界一直加 $2$，直到 $a_{r}$ 的出现次数为 $2$（即 $f_{a_{r}}=2$）。

最后，记录最大值就行了。

## 代码1
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[200005],f[200005];
int ans(int fir){
	int l=fir,r=fir,sum=0;
	memset(f,0,sizeof(f));
	for(;r<=n-1;){
		if(a[r]!=a[r+1]){
			while(l<r) f[a[l]]--,l++;
			r+=2;l+=2;
		}else{
			f[a[r]]+=2;
			while(f[a[r]]>2){
				f[a[l]]-=2;
				l+=2;
			}
			r+=2;
		}
		sum=max(sum,r-l);
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<max(ans(1),ans(2));
	return 0;
}
```
## 优化代码1

我们用 $f_{i}$ 数组存储 $i$ 最后一次出现的位置。

显然，如果 $f_{i}\ge l$（即 $i$ 这个数在 $l\sim r$ 这个序列中出现过），那么只需要将 $l=f_{a_{i}}+2$ 就行了。因为 $i$ 最后一次出现的位置加 $2$，这之后的数一定没有 $i$。

这样就可以优化掉那微小的常数了。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[200005],f[200005];
int ans(int fir){
	int l=fir,r=fir,sum=0;
	memset(f,0,sizeof(f));
	for(;r<=n-1;){
		if(a[r]!=a[r+1]) l=r=r+2;
		else{
			if(f[a[r]]>=l) l=f[a[r]]+2;
			f[a[r]]=r;
			r+=2;
		}
		sum=max(sum,r-l);
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<max(ans(1),ans(2));
	return 0;
}
```

## 思路2（动态规划）
我们用 $f_{i}$ 数组存储到 $i$ 为止最长的子序列长度。

用 $t_{i}$ 数组存储 $i$ 最后一次出现的位置（相当于优化代码1中的 $f$ 数组）。

首先，```f(a[i]==a[i+1]) f[i+1]=min(f[i-1]+2,i+1-t[a[i]]);``` 这个语句中 ```f[i-1]+2``` 表示从 $i-1$ 这个点走到 $i+1$ 这个点的最长序列长度（动态规划）（满足第 $1,2$ 条条件，不一定满足第 $3$ 条条件）。而 ```i+1-t[a[i]]``` 表示从 $i+1$ 这个点到 $t_{a_{i}}$这个点的序列长度（满足第 $3$ 条条件，不一定满足第 $1,2$ 条条件）。

这两者要取一个最小值，因为要保证序列合法。

之后还有一个问题：为什么不判断 $a_{i}\ne a_{i+1}$ 的情况呢？

因为这一定对答案没有影响。请读者自己思考，道理非常简单。
## 代码2
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[200005],f[200005],t[200005],ans=0;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]==a[i+1]) f[i+1]=min(f[i-1]+2,i+1-t[a[i]]);
		t[a[i]]=i;
		ans=max(ans,f[i+1]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：PUTONGDEYITIREN (赞：2)

# 思路
我们可以用尺取法，分别从偶数与奇数开始，每次取一个区间，扩大右端点，用一个桶来记录每个数出现的位置，每次找到一个数先判断他是否与他的下一个数相同，如果相同，把左端点放在右端点上。在判断这个数出现的位置是否在区间内，如果在，就把左端点给放到他出现的位置上，代码简洁易懂。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000006],t[1000006];
long long g(long long x){
	memset(t,0,sizeof(t));
	long long l=x,r=x,mx=0;
	for(;r<n;){
		if(a[r]!=a[r+1]) l=r+2,r+=2;
		else{
			if(t[a[r]]>=l) l=t[a[r]]+2;t[a[r]]=r;r+=2;
		} 
		mx=max(mx,r-l);
	}
	return mx;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cout<<max(g(0),g(1));
	return 0;
}

```

---

## 作者：Emplace (赞：2)

## 思路
可以用一个双指针，和一个桶来记录，记得要从第一个数和第二个数分别开始。

### 简单版
我们先考虑可以重复，则直接如果检测到第二个指针与下一个不相同，就直接将第一个指针移动这。否则就将第二个指针往后移两步。最后每次操作都将这个长度取最大值。

### 进阶版
考虑不可以重复，则用一个桶记录每个数上一次出现地方。然后如果第二个指针对应的数上次出现的的地方在这个区间内，则将第一个指针拉到上一次出现的位置。其它步骤与简单版相同。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2000005],tong[2000005];
int ans(int top){
	int mx=0;
	memset(tong,0,sizeof(tong));
	for(int l=top,r=top;r<n;){
		if(a[r]!=a[r+1]){
			l=r=r+2;
		}
		else{
			if(tong[a[r]]>=l){
				l=tong[a[r]]+2;
			}
			tong[a[r]]=r,r+=2;
		}
		mx=max(mx,r-l);
	}
	return mx;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cout<<max(ans(1),ans(2));
	return 0;
}
```

---

## 作者：linjinkun (赞：1)

首先来推导一下性质，如果 $[l,r]$ 这个区间是满足题目要求的字符串的话，那么 $[l+2,r]$ 也是满足题目要求的字符串，这个很好理解，因为他满足这个性质，所以我们可以使用双指针来解决此题。

具体的过程就是设置四个变量 $l,r,fg,maxx$，初始时 $l = 1,r = 1,fg = 0,maxx = 0$，每一次都要清空上一次的数据，也就是 $num_{a_{l-1}} = 0$，$num$ 指的是元素统计数量的数组。接下来就是双指针部分，首先如果 $a_l = a_{l+1}$ 并且 $a_{l+2} \not= a_l$，那么才能进入双指针搜寻，搜寻的过程就是首先如果 $fg = 1$，那么 $r = l$，因为 $fg$ 的意思是上一次 $l$ 没搜到满足题目要求的字符串，所以这次就不能沿用上次的 $r$，只能重新令 $r = l$，所以 $fg$ 变量的含义就是上一次没搜到满足题目要求的字符串就是 $1$，搜到满足题目要求的字符串就是 $0$，回归正题，在每一次搜索循环中如果 $a_r = a_{r+1}$ 并且 $num_{a_{l+2}} \not= 2$，那么 $num_{a_{l+2}} = 2$，同时 $r = r+2$，否则的话，就直接退出循环。循环外的话，$maxx = \max(maxx,r-l)$，解释一下为什么此时区间长度为 $r-l$，因为此时 $r$ 一定不是满足题目要求的字符串的，因为这样 $r$ 才能以这个值来退出，所以实际上真正的 $r$ 应该是 $r-2$，那么这个区间实际上是 $[l,r-2+1]$，长度就是 $r-2+1-l+1 = r-l$。明白了之后我们回归正题，$maxx$ 求完后，我们应该让 $l = l+2$，因为上面说了，如果 $[l,r]$ 是满足题目要求的字符串，那么 $[l+2,r]$ 也一定是满足题目要求的字符串，接着就是 $fg = 0$，因为我们找到了满足题目要求的字符串，当然如果没找到满足题目要求的字符串的话，$fg = 1$。

讲得这么详细直接放个代码没问题吧：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int a[N];
int num[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int maxx = 0;
	int l = 1;
	int r = 1;
	int fg = 0;
	while(l<=n)
	{
		num[a[l-1]] = 0;
		if(a[l] == a[l+1]&&a[l+2]!=a[l])
		{
			if(fg)
			{
				r = l;
			}
			while(r<=n)
			{
				if(a[r] == a[r+1]&&num[a[r]]!=2)
				{
					num[a[r]] = 2;
					r+=2;
				}
				else
				{
					break;
				}
			}
			maxx = max(maxx,r-l);
			l++;//这里本来是要+2的，但是后面又有一个+1，所以这里只需要+1
			fg = 0;
		}
		else
		{
			fg = 1;
		}
		l++;
	}
	printf("%d",maxx);
	return 0;
}
```

---

## 作者：Tairitempest (赞：1)

## [ABC381D] 1122 Substring
我们能从题目中看到：$ 1 \leq N \leq 2 \times 10^5$，$1 \leq A_i \leq N $。

考虑记录每个数字上一次出现的位置并进行 DP。设 $Num[i]$ 表示第 $i$ 个数，$f[i]$ 表示以第 $i$ 个数字为结尾的 “ 1122 串 ” 长度，$appear[k]$ 表示数字 $k$ 上一次出现的位置，并维护一个实时的断点 $B$ 来表示当前 “ 1122 串 ” 开始的位置，这样的话我们可以通过 $i-B$ 的奇偶性来判断当前数字和上一个应当相同还是应当不同。

如果第 $i$ 个数和第 $i-1$ 个数相同时，当前数字和上一个应当不同（即 $i-B$ 能被 $2$ 整除），那么第 $i$ 个数字为结尾的 “ 1122 串 ” 只能以第 $i-1$ 个数字作为开头。将断点 $B$ 设置为 $i-1$ ，将 $f[i]$ 设为 $2$。

如果第 $i$ 个数和第 $i-1$ 个数相同时，当前数字和上一个应当相同（即 $i-B$ 不能被 $2$ 整除），判断当前数字是否在那么第 $i-2$ 个数字为结尾的 “ 1122 串 ” 当中出现，即断点 $B$ 是否小于当前数字出现的位置。如果确实没有出现过，那么$f[i]=f[i-2]+2$；否则那么第 $i$ 个数字为结尾的 “ 1122 串 ” 只能以当前数字上一次出现的位置后的第一个数字 $appear[f[i]]+1$ 作为开头，计算得长度为 $i-appear[Num[i]]$，将断点 $B$ 设置为 $appear[f[i]]+1$ ，将 $f[i]$ 设为 $i-appear[Num[i]]$。

如果第 $i$ 个数和第 $i-1$ 个数不同时，当前数字和上一个应当不同，（即 $i-B$ 能被 $2$ 整除）其实我们什么都不用做。如果第 $i$ 个数和第 $i-1$ 个数不同时，当前数字和上一个应当相同，（即 $i-B$ 能被 $2$ 整除）那么上一个点就不能作为断点了，将断点 $B$ 设置为 $i$ 即可。

在完成上面的 DP 以后把 $f$ 数组全部扫一遍求出来最长的序列长度就可以了。时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int Num[200010],n,f[200010],B,appear[200010],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>Num[i];
		if(Num[i]==Num[i-1]){
			if((i-B)%2==0){
				B=i-1;
				appear[Num[i]]=i;
				f[i]=2;
			}
			else if(appear[Num[i]]<=B){
				f[i]=f[i-2]+2;
				appear[Num[i]]=i;
			}else{
				f[i]=i-appear[Num[i]];
				B=appear[Num[i]]+1;
				appear[Num[i]]=i;
			}
		}else if((i-B)%2==1) B=i;
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：I_Love_DS (赞：1)

赛后 $12$ 分钟 AC 你受得了吗。。

最后还是对拍救了我一命。。。

## 思路

双指针。

这题相较于普通的双指针题有些区别。

首先，我们可以把相同数值相邻位置的元素们捆绑在一起。

```cpp
	int l = 1;
	for (int i = 2; i <= n + 1; i++) 
		if (a[i] != a[i - 1]) 
			v.push_back({a[i - 1], i - l}), l = i;
// 经典常谈
```

接下来记 $x$（代码中的 $a_{i - 1}$）为块的元素，$y$（代码中的 $i - l$）为块的大小，$l,r$ 为双指针，$b_i$ 表示这个元素在 $l,r$ 里有没有出现过，$now$ 为现在的子段大小，$ans$ 为最大子段。

然后，我们分类讨论：

- 如果 $y < 2$ 则任何一对 $l,r$ 都不能包含这个块。直接把 $l$ 之前的块元素的 $b_x$ 设为 $0$ 即可，$now$ 清零。
```cpp
		if (v[i].cnt == 1) {
			ans = max(ans, now);
			now = 0; // 更新答案
			while (l <= i) b[v[l].x] = 0, ++l; // 清空
		}
```
- 如果 $y = 2$ 可证 $l,r$ 包含这个区间显然更优。将 $ans$ 和 $now$ 更新。
```cpp
			while (b[v[i].x] && l <= i) b[v[l].x] = 0, ++l, now -= 2;
            // 防止重复
			now += 2;
			ans = max(ans, now); // 更新答案
			b[v[i].x] = 1; // 指针范围内有这个元素
```
- 如果 $y > 2$ 可以取这个块的前两个值作为 $l,r$ 区间，记录答案。然后，把 $l$ 之前的块元素的 $b_x$ 设为 $0$，表明现在 $l,r$ 内没有元素。然后，再把 $now$ 设为 $2$，表明下一个 $l,r$ 里可以含有这个块的末尾两个值。
```cpp
        if (v[i].cnt > 2) {
			while (b[v[i].x] && l <= i) b[v[l].x] = 0, ++l, now -= 2; // 防止重复
			ans = max(ans, now + 2); // 更新左答案
			now = 2;
			ans = max(ans, now); // 更新右答案
			while (l < i) b[v[l].x] = 0, ++l; // 清空
			b[v[i].x] = 1; // 指针范围内有这个元素
		}
```

时间复杂度 $O(n)$。

## 完整代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n;
int a[200050], b[200050];

struct node {
	int x, cnt;
};

vector <node> v;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int l = 1;
	for (int i = 2; i <= n + 1; i++) 
		if (a[i] != a[i - 1]) 
			v.push_back({a[i - 1], i - l}), l = i;
	// 经典常谈
	// 变量意义上文有，不做解释
	int m = v.size();
	int now = 0, ans = 0;
	l = 0;
	for (int i = 0; i < m; i++) {
		if (v[i].cnt == 1) {
			ans = max(ans, now);
			now = 0; // 更新答案
			while (l <= i) b[v[l].x] = 0, ++l; // 清空
		} else if (v[i].cnt > 2) {
			while (b[v[i].x] && l <= i) b[v[l].x] = 0, ++l, now -= 2; // 防止重复
			ans = max(ans, now + 2); // 更新左答案
			now = 2;
			ans = max(ans, now); // 更新右答案
			while (l < i) b[v[l].x] = 0, ++l; // 清空
			b[v[i].x] = 1; // 指针范围内有这个元素
		} else {
			while (b[v[i].x] && l <= i) b[v[l].x] = 0, ++l, now -= 2;
            // 防止重复
			now += 2;
			ans = max(ans, now); // 更新答案
			b[v[i].x] = 1; // 指针范围内有这个元素
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：xixisuper (赞：1)

# AT_abc381_d [ABC381D] 1122 Substring 题解

~~关于这题我场上挂了 5 发这件事。~~

## 思路

一眼双指针。

考虑双指针维护以当前位置为右端点的极长 1122 子串，如果发现当前的两个数不相同，则把左端点右移到当前的右端点位置；如果发现某个数的出现次数 $>2$，则不断右移左端点，直到出现次数重新 $\le 2$。一个数的出现次数可以开一个桶维护。

当然我们可以分两类进行计算，第一类是结束位置是偶数的情况，第二类是结束位置是奇数情况，两种情况的计算方法相同。

右端点右移的时间复杂度为 $O(n)$，左端点右移的时间复杂度为 $O(n)$，故总时间复杂度为 $O(n)$，可以通过此题。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=2e5+10;
ll n,a[N],cnt[N],ans;
void solve(){
	ll l=0;
	for(ll i=2;i<=n;i+=2){
		cnt[a[i]]++,cnt[a[i-1]]++;
		if(a[i]!=a[i-1]){
			while(l<i){
				l++;
				cnt[a[l]]--;
			}
		}
		else{
			if(cnt[a[i]]>2){
				while(l<i&&cnt[a[i]]>2){
					l++;
					cnt[a[l]]--;
				}
			}
		}
		ans=max(ans,i-l);
	}
} 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i];
	solve();
	for(ll i=1;i<N;i++) cnt[i]=0;
	for(ll i=1;i<n;i++) a[i]=a[i+1];
	n--;
	solve();
	cout<<ans;
	return 0;
}
```

---

## 作者：liuziqin (赞：0)

## 思路

可以证明，合法子串只有 $S_{2i-1}=S_{2i}$ 以及 $S_{2i}=S_{2i+1}$ 两种情况，因此我们可以分别枚举。

考虑开一个队列来存储当前子串的所有元素，每当加入一个新元素时，将队列里和相同的元素**以及该元素前面的所有元素**弹出队列，最后统计答案即可。

## Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int a[N],last[N],mp[N];
bool used[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)mp[i]=-1;
	int ans=0;
	for(int i=1;i<=n;i++){
		last[i]=mp[a[i]];
		mp[a[i]]=i;
	}//记录距离该元素最近的相同元素
	queue<int>q;
	for(int i=1;i<=n;i+=2){
		if(a[i]==a[i+1]){
			while(used[a[i]]&&!q.empty()){
				int tmp=q.front();
				q.pop();
				used[a[tmp]]=0;
			}//弹出相同元素
			q.push(i);
			used[a[i]]=1;
			int t=q.size();
			ans=max(ans,t*2);
		}
		else{
			while(!q.empty()){
				int tmp=q.front();
				used[a[tmp]]=0;
				q.pop();
			}
		}//如果不合法，就要清空队列
	}
	while(!q.empty()){
		used[a[q.front()]]=0;
		q.pop();
	}
	for(int i=2;i<=n;i+=2){
		if(a[i]==a[i+1]){
			while(used[a[i]]&&!q.empty()){
				int tmp=q.front();
				q.pop();
				used[a[tmp]]=0;
			}
			q.push(i);
			used[a[i]]=1;
			int t=q.size();
			ans=max(ans,t*2);
		}
		else{
			while(!q.empty()){
				int tmp=q.front();
				used[a[tmp]]=0;
				q.pop();
			}
		}
	}//同上
	cout<<ans<<"\n";
}
```

---

## 作者：postpone (赞：0)

类似双指针，记录起点的位置；在遍历过程中，再用一个数据结构记录合法的数字最晚出现的位置。

$A_i$ 的范围是 $\left[1, N\right]$，因此可以直接用数组记录位置，若 $A_i$ 的范围很大，则用哈希表。

在遍历的过程中，如果不合法（相邻两个数字不相等），直接更新答案。

如果遇到重复的，先更新答案，然后把起点放到重复数字出现的位置后，再往后遍历。

再看奇偶数位置，这个是比较好解决的：将上述过程封装，然后分别从第一个奇、偶位置开始遍历即可。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto work = [&](int x) -> int {
        int res = 0;
        int st = x - 2;
        vector<int> f(n + 1, -1);

        for (int i = x; i < n; i += 2) {
            if (a[i] != a[i - 1]) {
                res = max(res, i - st - 2);
                st = i;
                continue;
            }
            if (f[a[i]] > st) {
                res = max(res, i - st - 2);
                st = f[a[i]];
            }
            f[a[i]] = i;
            if (i + 2 >= n) {
                res = max(res, i - st);
            }
        }
        return res;
    };

    cout << max(work(1), work(2)) << endl;

    return 0;
}
```

---

## 作者：Hughpig (赞：0)

双指针做法。

考虑先固定左端点 $l$，右端点 $r\ (r\le n)$ 在当前区间合法的情况下不断向右延申。然后再不断左移左端点 $l\ (l\le r)$，直到区间合法。不断重复，然后在区间合法的时候记录区间长度取最大值即可。

记 $cnt_{x}$ 为 $x$ 在区间内的出现次数。

根据题意，一个合法区间内每个数的出现次数都是 $0$ 或 $2$，且每对相邻的两数相等。记一个变量 $qwq$ 为区间内出现次数不为 $0$ 或 $2$ 的数的个数（可以理解为区间的不平衡度）。

显然，在 $qwq$ 为 $0$ 时区间合法；在 $qwq$ 为 $1$ 时，当前区间不合法，但是如果 $a_{r+1}=a_r$，那么带上下一个元素区间又会变得合法，所以此时这个区间还是有可能合法的。但是若 $qwq>1$，哪怕再加入下个元素也没有合法可能了。

因此：

* 如果区间内某数出现次数大于 $2$，此时区间必然不合法。
* 如果 $qwq>1$，此时有不止一个数出现次数不为 $0$ 或 $2$，也不合法。

然后每次移动端点时判断一下区间是否合法，更新答案即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);i<=(r);++i)
constexpr int N=2e5+9;

ll n,a[N],l=1,r=0,qwq,ans;
map<ll,ll> cnt;

int main()
{
	cin>>n;up(1,n,i)cin>>a[i];
	while(r<n){
		while(r<n){
			++r;++cnt[a[r]];
			if(cnt[a[r]]==2||cnt[a[r]]==0)--qwq;
			else ++qwq;
			if(qwq==0)ans=max(ans,r-l+1);
			if(cnt[a[r]]>2)break;
			if(qwq>1)break;
		}
		while((cnt[a[r]]>2||qwq>1)&&l<r){
			cnt[a[l]]--;
			if(cnt[a[l]]==2||cnt[a[l]]==0)--qwq;
			else ++qwq;
			++l;
			if(qwq==0)ans=max(ans,r-l+1);
		}
	}
	while(l<r){
		cnt[a[l]]--;
		if(cnt[a[l]]==2||cnt[a[l]]==0)--qwq;
		else ++qwq;
		++l;
		if(qwq==0)ans=max(ans,r-l+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

~~Atcoder 抽疯了出这么多 1122 串的问题。~~

### 小知识

Substring 是子串的意思。

Subsequence 是子序列的意思。

子串意思是从字符串（或数组中）中截取一段连续的元素。

子序列是从字符串（或数组）中截取一段**不连续**的元素。

例如设 $S=\texttt{abcdef}$。

$S$ 的子串形如 $\tt{abc}$、$\tt{cde}$、$\tt{def}$、
$\tt{cd}$。

$S$ 的子序列形如 $\tt{acd}$、$\tt{df}$、
$\tt{abdf}$。

特别地，子串是一种特殊的子序列。

## 思路

不难发现，对于 $1\le l<r\le N$，如果 $\{A_l,A_{l+1},A_{l+2},\dots,A_{r}\}$ 是 1122 子串（注意 **不是子序列**），如果移除最后两个元素得到序列 $\{A_l,A_{l+1},A_{l+2},\dots,A_{r-2}\}$ 也是一个 1122 子串。

所以我们可以通过滑动窗口算法解决这个问题。

对于偶数 $r=2,4,\dots$，令 $f(r)$ 为最小的奇数 $l(1\le l\le r+1)$ 使得 $\{A_l,A_{l+1},A_{l+2},\dots,A_{r}\}$ 是 1122 子串。如果 $l=r+1$，那么这个 $\{A_l,A_{l+1},A_{l+2},\dots,A_{r}\}$ 是一个空串。

> 从 $A$ 的奇数索引元素开始的 $A$ 的最长子数组的长度，即在 $A_1,A_3,\dots$ 中，是一个 1122 序列的。英文原文：the length of the longest subarray of 
$A$ starting from an odd-indexed element of 
$A$, one in $A_1,A_3,\dots$ that is a 1122 sequence.

形式化我们就可以用 $f(r)$ 表示成 $\max\limits_{r=2,4\dots}(r-f(r)+1)$。

接着我们就要求 $f(r)$ 的值了。

当 $r=2$，且 $A_1=A_2$ 时，我们就有 $l=1$ 否则有 $l=3$。

当我们知道 $f(r-2)$ 时，我们可以求出 $f(r)$：
1. 如果 $A_{r-1}\not=A_r$，则 $f(r)=r+1$。
2. 如果 $A_{r-1}=A_r$ 且 $\{A_{f(r-2)},A_{f(r-2)+2},\dots,A_{r-3}\}$ 中没有任何元素等于 $A_{r-1}$ 那么 $f(r)=f(r-2)$
3. 如果 $A_{r-1}=A_r$ 且 $k∈\{A_{f(r-2)},A_{f(r-2)+2},\dots,A_{r-3}\}$ 使得 $A_{r-1}=A_k$，那么 $f(r)=k+2$。注意，这样的 $k$ 总是唯一的。

暴力的时间复杂度 $O(N^2)$

接着我们设法优化。由于 $A_i\le N\le2\times10^5$，我们可以为每个 $1\le x\le N$ 记录 $i=1,3,\dots,r-3$ 中最大的 $i$，即可检查最大的 $i$ 与 $A_i=A_{r-1}$ 是否大于等于 $f(r-2)$。存在，我们只要为 $r$ 更新一个元素（即对于 $x=A_{r-1}$，用 $f(i)=x$ 到 $(r-1)$ 更新最大的 $i$），我们就可以用 $O(N)$ 的时间复杂度解决此问题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
int n,l,ans=0;
int a[N],last[N+1];
int main() {
	cin>>n;
	for(int i = 0; i < n; ++i)cin>>a[i];
	for(int i = 0; i < N; ++i)last[i+1]=-2;
	l=0;
	for(int i=0;(i+1)<n;i+=2){
		if(a[i]!=a[i+1])l=i+2;
		else l=max(l,last[a[i]]+2);
		ans=max(ans,i+2-l);
		last[a[i]]=i;
	}

	for(int i = 0; i < N; ++i)last[i+1]=-2;
	l=1;
	for(int i=1;(i+1)<n;i+=2){
		if(a[i]!=a[i+1])l=i+2;
		else l=max(l,last[a[i]]+2);
		ans=max(ans,i+2-l);
		last[a[i]]=i;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给出定义，一个长度为 $n$ 的序列 $X$ 为 `1122` 序列，当且仅当满足以下条件。

- $n$ 为偶数；
- 对于所有的 $1\le i\le\frac{n}{2}$ 都有 $X_{2i-1}=X_{2i}$;
- $X$ 中的每个数在 $X$ 中只出现两次。

现给定一个长度为 $N$ 的数列 $A$，请求出 $A$ 中最长 `1122` 连续子序列的长度，数据范围 $N\le 2\times 10^5$。

## 解题思路

要求出一个区间，满足某些条件的最长长度，可以使用单调队列来进行维护。具体来说，若 $a_i=a_{i-1}$，我们便可把 $a_i$ 加入单调队列中，同时更新 $a_i$ 出现的次数；否则便把队列和次数清空，进行下一次的区间统计。同时，$a_i$ 加入队列后，有可能其出现次数 $>1$（这里把两个相同的数字合为一个），不符合 `1122` 序列的定义，于是就需要不断弹出队头，直到 $a_i$ 的出现次数 $=1$ 为止。最后处理完队列（也就是我们选的区间）后，长度即为 $r-l+1$，统计最大值即可。

需要注意的是，由于我们把两个合为一个，所以对于 $i$ 需进行两遍统计，一遍为奇一遍为偶，防止漏掉某些数（如样例 $2$）。由于每一个数只会进队和出队不超过两次，所以总时间复杂度为 $O(N)$，可以通过此题。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,a[200001],q[200001],bz[200001],ans,head=1,tail;

int main()
{
    n=read();
    for(R int i=1; i<=n; ++i) a[i]=read();
    
    for(R int i=2; i<=n; i+=2)
    {
		if(a[i]==a[i-1]) q[++tail]=a[i], ++bz[a[i]];
		
		else
		{
			while(head<=tail) --bz[q[head++]];
			head=1; tail=0;
		}
		
		while(bz[a[i]]>1 && head<=tail) --bz[q[head++]];
		ans=max(ans,tail-head+1);
	}
	
	for(R int i=1; i<=n; ++i) bz[i]=0;
	head=1; tail=0;
	
	for(R int i=3; i<=n; i+=2)
	{
		if(a[i]==a[i-1]) q[++tail]=a[i], ++bz[a[i]];
		
		else
		{
			while(head<=tail) --bz[q[head++]];
			head=1; tail=0;
		}
		
		while(bz[a[i]]>1 && head<=tail) --bz[q[head++]];
		ans=max(ans,tail-head+1);
	}
    
    write(ans<<1);
    return 0;
}
```

---

## 作者：daitangchen2008 (赞：0)

## 分析：  
分成两种情况：从 1 开始和从 2 开始，分类讨论。  
记以每个 $i$ 位置为最后位置的串的开头为 $j$，那答案即为最大的 $i-j$。  
每次更新 $j$ 时，先判断相邻的两个位置是否相同。如果不同就更新；再判断是否出现过，出现过再更新 $j$。每次操作结束后更新位置。  
时间复杂度 $O(n)$，可以通过。  
## 代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define fi first
#define se second
#define ce continue
const int N=5e5+10;
const int mod=998244353;
priority_queue<int> q;
set<int> s;
stack<int> sta;
int n;
int a[N];
string st;
int mhash[N];
signed main()
{
	int n;
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int last=0;
	int duan=0;
	for(int i=2;i<=n;i+=2)
	{
		if(a[i]!=a[i-1])
		{
			duan=i;
			continue;
		}
		ans=max(ans,i-max(duan,mhash[a[i]]));
		if(mhash[a[i]]!=0)
		duan=max(duan,mhash[a[i]]);
		mhash[a[i]]=i;
	}
	for(int i=1;i<=N-300;i++)
		mhash[i]=0;
	duan=1;
	for(int i=3;i<=n;i+=2)
	{
		if(a[i]!=a[i-1])
		{
			duan=i;
			continue;
		}
		ans=max(ans,i-max(duan,mhash[a[i]]));
		if(mhash[a[i]]!=0)
		duan=max(duan,mhash[a[i]]);
		mhash[a[i]]=i;
	}
	cout<<ans<<endl;
	return 0;
 } 
```

---

## 作者：huangrenheluogu (赞：0)

考虑奇数、偶数位开始分开处理，假设 $(i-1,i)$ 是最后一位，用队列维护一下前面可以连续到哪里即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, pre[N], suf[N], ans, a[N], f[N], q[N], h, t;
bool vis[N];
inline void solve(){
    h = 1;
    for(int i = 2; i <= n; i += 2){
        if(a[i] == a[i - 1]){
            if(vis[a[i]]){
                while(vis[a[i]]){
                    vis[q[h]] = 0;
                    h++;          
                }
            }
            q[++t] = a[i];
            vis[a[i]] = 1;
            ans = max(ans, t - h + 1 << 1);
        }
        else{
            while(h <= t){
                vis[q[h]] = 0;
                h++;
            }
        }
    }
    h = 1, t = 0;
    for(int i = 3; i <= n; i += 2){
        if(a[i] == a[i - 1]){
            if(vis[a[i]]){
                while(vis[a[i]]){
                    vis[q[h]] = 0;
                    h++;          
                }
            }
            q[++t] = a[i];
            vis[a[i]] = 1;
            ans = max(ans, t - h + 1 << 1);
        }
        else{
            while(h <= t){
                vis[q[h]] = 0;
                h++;
            }
        }
    }
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    solve();
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

将数组 $a$ 变成元素加个数的形式，元素数组为 $b$，个数为 $c$，如 $\mathtt{1,1,2,2,3,3,3}$，$b$ 就是 $\mathtt{1,2,3}$，$c$ 就是 ${2,2,3}$。用双指针来做。用 $v$ 统计是否出现，$j$ 表示左指针，$i$ 表示右指针。统计答案就是 $i-j+1$。

* 当 $c_i=1$ 时，说明 $i$ 不能贡献，直接将 $j$ 移动到 $i+1$。
* 当 $c_i>2$ 时，$i$ 只能作为开头或结尾，若 $b_i$ 没出现过，统计一次答案。然后将 $j$ 移动到 $i$，标记 $b_i$ 出现。
* 当 $c_i=2$ 时，若 $b_i$ 出现过，则一直移动 $j$ 直到 $v_{b_i}=0$。然后标记 $b_i$ 出现。

移动 $j$ 时要将 $v_{b_j}$ 变为 $0$。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=2e5+5;
int n;
int a[N],b[N],c[N];
int v[N];
void solve()
{
    cin>>n;
    int tot=0;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        if(a[i]!=a[i-1]) b[++tot]=a[i],c[tot]=1;
        else c[tot]++;
    }
    int j=1,ans=0;
    for(int i=1;i<=tot;i++)
    {
        if(c[i]<2) while(j<=i) v[b[j++]]=0;
        else if(c[i]>2) 
        {
			if(!v[b[i]]) ans=max(ans,(i-j+1)*2);
            while(j<i) v[b[j++]]=0;
            v[b[i]]=1;
        }
        else 
        {
            while(j<=i&&v[b[i]]) v[b[j++]]=0;
            v[b[i]]=1;
        }
        if(j<=i) ans=max(ans,(i-j+1)*2);
    }
    cout<<ans<<'\n';
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：ran_qwq (赞：0)

分左端点 $l$ 为奇数和偶数两种情况，两种情况是类似的，所以不妨设 $l$ 为奇数。

对每个 $l$，暴力找最大的 $r$。具体地，记录每个数字的出现次数 $b_i$，如果当前的数已经出现过了就退出。这是 $O(n^2)$ 的。

进一步观察，发现 $r$ 满足单调性。这是因为 $l$ 增大时，有些数的出现次数会变少，而没有数出现次数会变多。直接双指针可以做到 $O(n)$。

```cpp#include<bits/stdc++.h>
#define il inline
#define ui unsigned int
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define ldb long double
#define pii pair<int,int>
#define vi vector<int>
#define vpii vector<pii>
#define fir first
#define sec second
#define gc getchar
#define pc putchar
#define mst(a,x) memset(a,x,sizeof a)
#define mcp(a,b) memcpy(a,b,sizeof b)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pct __builtin_popcount
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f,MOD=998244353;
const ll INFll=0x3f3f3f3f3f3f3f3f;
il int rd() {int x=0,f=1; char ch=gc(); while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=gc();} while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc(); return x*f;}
il ll rdll() {ll x=0; int f=1; char ch=gc(); while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=gc();} while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc(); return x*f;}
il void wr(int x) {if(x==INT_MIN) return printf("-2147483648"),void(); if(x<0) return pc('-'),wr(-x); if(x<10) return pc(x+'0'),void(); wr(x/10),pc(x%10+'0');}
il void wrll(ll x) {if(x==LLONG_MIN) return printf("-9223372036854775808"),void(); if(x<0) return pc('-'),wrll(-x); if(x<10) return pc(x+'0'),void(); wrll(x/10),pc(x%10+'0');}
il void wr(int x,char *s) {wr(x),printf("%s",s);}
il void wrll(ll x,char *s) {wrll(x),printf("%s",s);}
il int vmod(int x) {return x>=MOD?x-MOD:x;}
il int vadd(int x,int y) {return vmod(x+y);}
il int vsub(int x,int y) {return vmod(x-y+MOD);}
il int vmul(int x,int y) {return 1ll*x*y%MOD;}
il int qpow(int x,int y) {int res=1; for(;y;y>>=1,x=vmul(x,x)) if(y&1) res=vmul(res,x); return res;}
il void cadd(int &x,int y) {x=vmod(x+y);}
il void csub(int &x,int y) {x=vmod(x-y+MOD);}
il void cmul(int &x,int y) {x=vmul(x,y);}
il void cmax(int &x,int y) {x<y&&(x=y);}
il void cmaxll(ll &x,ll y) {x<y&&(x=y);}
il void cmin(int &x,int y) {x>y&&(x=y);}
il void cminll(ll &x,ll y) {x>y&&(x=y);}
int n,ans,a[N],b[N];
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1,j=1;i<=n;i+=2) {
		while(j<n&&a[j]==a[j+1]&&!b[a[j]]) b[a[j]]++,j+=2;
		cmax(ans,j-i); if(j>i) b[a[i]]--; else j+=2;
	}
	mst(b,0);
	for(int i=2,j=2;i<=n;i+=2) {
		while(j<n&&a[j]==a[j+1]&&!b[a[j]]) b[a[j]]++,j+=2;
		cmax(ans,j-i); if(j>i) b[a[i]]--; else j+=2;
	}
	wr(ans,"\n");
}
signed main() {
//	freopen("in.in","r",stdin),freopen("out.out","w",stdout);
	int T=1; while(T--) QwQ();
}
```

---

## 作者：cjh_trailblazer (赞：0)

[at原题面](https://atcoder.jp/contests/abc381/tasks/abc381_d)
## 题目分析：
~~最红温的一集。~~

对于此题，不难发现，合法序列一定是一个区间，我们考虑双指针。

刚开始，$l,r$ 指针一起前跳，扫到合法序列，即 $a[i]=a[i+1]$ 时，$r$ 往前跳，当桶数组重复时，记录答案，$l$ 前跳 $2$ 位即可。
### 红温事项：
形如 $1112233$ 这种序列，由于 $111$ 的存在，导致 $l$ 指针前跳 $2$ 位时，可能会多指一位到最后的 $1$，所以要特殊处理一下，将 $l$ 指针再后移一位接着跳即可。
## [Code](https://atcoder.jp/contests/abc381/submissions/60085037)

---

## 作者：z_yq (赞：0)

# 题意
意思足够清楚，但是建议去前面的第一二三题翻一翻定义。
# 做法
可以发现，$i,j$ 同为奇数的时候，数字更大的从其下标开始的数列的结尾更大，所以定义二维数组 $book_{i,0/1}$ 和 $pos_{i,0/1}$，其中后面表示奇偶性，前面表示下标，然后按照题意模拟即可，思路简单，但是细节挺多的，建议评绿。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+9;
int n,a[N],book[N][2],mp[N],ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	mp[0]=-1;
	while(a[mp[1]+1]==a[mp[1]+2] && book[a[mp[1]+1]][1]==0 && mp[1]+2<=n) mp[1]+=2,book[a[mp[1]]][1]=2;
	ans=mp[1];
	for(int i=2;i<=n;i++)
	{
		if(mp[i-2]>=i-1)book[a[i-1]][i%2]--;
		if(mp[i-2]>=i-2)book[a[i-2]][i%2]--;
		mp[i]=max(mp[i-2],i-1); 
		while(a[mp[i]+1]==a[mp[i]+2] && book[a[mp[i]+1]][i%2]==0 && mp[i]+2<=n) mp[i]+=2,book[a[mp[i]]][i%2]=2;
		ans=max(ans,mp[i]-i+1);
		//cout<<i<<' '<<mp[i]<<' '<<book[a[mp[i]+1]][i%2]<<endl;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
分类讨论，分别计算左端点是奇数、左端点是偶数的答案。
计算答案可以用双指针。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=1e15;
int n,ans,t,a[N],b[N];
map<int,int>cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>b[i];
	for(int i=1;i+1<=n;i+=2) a[++t]=(b[i]==b[i+1]?b[i]:-1);
	for(int i=1,j=0;i<=t;++i)
		if(a[i]>0){
			if(j<i) j=i,cnt.clear(),++cnt[a[i]];
			while(j<t&&a[j+1]>0&&!cnt[a[j+1]]) ++j,cnt[a[j]]=1;
			cnt[a[i]]=0;
			ans=max(ans,j-i+1);
		}
	t=0; cnt.clear();
	for(int i=2;i+1<=n;i+=2) a[++t]=(b[i]==b[i+1]?b[i]:-1);
	for(int i=1,j=0;i<=t;++i)
		if(a[i]>0){
			if(j<i) j=i,cnt.clear(),++cnt[a[i]];
			while(j<t&&a[j+1]>0&&!cnt[a[j+1]]) ++j,cnt[a[j]]=1;
			ans=max(ans,j-i+1);
			cnt[a[i]]=0;
		}
	cout<<ans*2;
	return 0;
}
```

---

## 作者：Ericzc (赞：0)

## 题目分析

这题纯水，但本蒟蒻调了 **~~70 minute~~** **QWQ！！！**

首先解释一下 1122 sequence，要满足以下三点：

- $\lvert X \rvert$ 是偶数。这里 $\lvert X \rvert$ 表示 $X$ 的长度。
- 对于满足 $1\leq i\leq \frac{|X|}{2}$ 的每个整数 $i$ ， $X_{2i-1}$ 和 $X_{2i}$ 都相等。
- 每个正整数要么完全不出现在 $X$ 中，要么正好出现两次。也就是说， $X$ 中包含的每个正整数在 $X$ 中恰好出现两次。

我们的任务是去找出一个最长的 1122 sequence 字串（连续的），但是一看数据范围 $N \leq 10^5$，暴力肯定过不了，那怎么办呢？有一种优化方法叫[尺取法](https://blog.csdn.net/2301_77899321/article/details/131600037)，我们用他优化。定义一个桶，用来存上一次这个数出现的位置，为什么存位置呢？其实你也可以存出现了几次，但是这样做码长且时间复杂度多一个常数。然后我们去遍历时去对比 $tong_i$ 是否大于 $l$，如果大于就把 $l$ 更新。**注意：不要忘记更新答案，并且答案每次 $+2$，而且要分奇数起点和偶数起点处理**。

## Code：
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,a[2000005],tong[2000005];		//tong 是用来统计第 a_i 个数在那个位置出现  

int Find_ans(int top) 
{
	int sum = 0;
	memset(tong,0,sizeof(tong));		//一定要初始化，不然执行两遍可能会出错  
	for(int l = top,r = top;r < n;)
	{
		if(a[r] != a[r + 1]) l = r = r + 2;		//当相邻两个不相等时，说明不是 1122 sequence 所以要跳过 
		else
		{
			if(tong[a[r]] >= l) l = tong[a[r]] + 2; //当发现这个数在区间内出现过，那么刷新到上次位置的后面 
			tong[a[r]] = r,r += 2;
		}
		sum = max(sum,r - l);		//更新最大值 
	}
	return sum;
}
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	cout << max(Find_ans(1),Find_ans(2));		//在奇数起点和偶数起点的最大 1122 sequence length 取 Max 
	return 0;
}
```
实在没调出来的可以用以下样例调一下：

### In:
```
34
1 1 1 1 2 2 3 3 4 4 5 5 3 3 6 6 7 7 8 8 9 1 1 2 2 3 3 4 4 5 6 7 8 8
```
### Out: `12`

---

