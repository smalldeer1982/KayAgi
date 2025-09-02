# [PA 2024] Liderzy

## 题目背景

PA 2024 1B

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 1 [Liderzy](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/lid/)**

根据 PWN 字典（一本波兰语字典），「*lider*」是指「政党、工会或其他社会组织的领导人」。另一方面，在算法中，序列中出现次数严格大于序列长度一半的元素被称为序列的领导元素。例如，序列 $[7, 2, 5, 7, 7]$ 的领导元素是数字 $7$，而序列 $[2, 3, 2, 3]$ 则没有领导元素。

在本题中，我们将重点讨论「*lider*」一词的后一种含义。给定一个数列，你的任务是将它分成最小数目的数列（不一定连续），满足每个数列都有一个领导元素，并输出这个最小数目。可以证明这样的划分总是可能的。

## 说明/提示

输入的序列可以划分为 $[1,3,1]$ 和 $[2,2]$，这样划分后的两个序列就都有领导元素了（分别为 $1$ 和 $2$）。

## 样例 #1

### 输入

```
5
1 2 3 1 2
```

### 输出

```
2```

# 题解

## 作者：HaneDaniko (赞：9)

## 洛谷 P10351

### 题意简述

> 找到一个序列**每个划分都有主元素**的最少划分。

### 主要思路

这道题使用贪心。

首先我们需要知道，假如一个划分内的主元素出现次数为 $n$，那么这个划分内的最大承载元素就为 $2n-1$，可以证明假如再添加一个元素就不存在主元素了。

那么，对于一个出现次数为 $n$ 的数字，直接将它作为划分的主元素和拆成两部分比起来，直接划分只有一个减一，而拆成两部分的式子中有两个减一，其余部分不变。因此我们可以归纳出，**直接将出现次数较大的数作为一个划分的主元素是最优的**。

因此，这道题的主要思路就是：

1. 统计序列中每个元素的出现次数。

2. 将出现次数从小到大排序，根据贪心，每次取出出现次数最大的数作为主元素，统计该划分内的总数。

3. 当所有划分的总数大于等于 $n$ 后，当前的全部划分即为答案。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
struct num{
	int tot;
	bool operator<(const num &A)const{
		return tot>A.tot;
	}
}cnt[500001];
int n,tot,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		if(!cnt[x].tot) tot++;
		cnt[x].tot++;
	}
	sort(cnt+1,cnt+n+1);
	tot=n;
	for(int i=1;i<=n;++i){
		if(cnt[i].tot*2-1>=tot){
			ans++;
			break;
		}
		ans++;
		tot-=cnt[i].tot*2-1;
	}
	cout<<ans;
}
```

---

## 作者：zhengpie (赞：3)

### 1.思路

考虑**贪心**算法。

首先，我们先用**桶**的思想处理**每个数出现的次数**，用 $d_{a_i}$ 记录 $a_i$ 出现的次数：

```cpp
for(int i = 1,x;i <= n;i++){cin>>x;d[x]++;}
//这里无需定义数组，这样可以稍微省一点空间。（虽然本题空间还是很充裕的，但是养成好习惯）
```

然后把它**从大到小**排序一下，接着循环遍历每个 $d_i$，对于每一个 $d_i$ 都挑出 $d_i - 1$ 个数，这样，这 $2 \times d_i - 1$ 个数就满足题意。

### 2.细节

首先，根据上面的阐述，排序后遍历的代码应该是这样的：

```cpp
int t = n;//注意不能直接用n，因为循环边界里有n
for(int i = 1;i <= n/*如果每个d[i]都是1，那么最坏情况下遍历n次就可以*/;i++)
	if(d[i] * 2 <= t)//注意是小于等于，原因下面会讲
	{
		ans++;
		t -= d[i] * 2 - 1;
	}
```

但是，如果遍历中的 $d_i$ 不满足条件，那么后面的所有数放在同一个数列不就刚好满足题意吗？所以加上下面的代码：

```cpp
else
{
	ans++;//剩下的数可以组成队列
	//上面如果不取等的话，那么总结果就会少算一次
	break;	
}
```

### 3.完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d[500005],ans;
bool cmp(int x,int y)
{	
	return x > y;
}
signed main()
{
	cin>>n;
	for(int i = 1,x;i <= n;i++){cin>>x;d[x]++;}
	//这里无需定义数组，这样可以稍微省一点空间。（虽然本题空间还是很充裕的，但是养成好习惯）
	sort(d + 1,d + n + 1,cmp);
	int t = n;//注意不能直接用n，因为循环边界里有n
	for(int i = 1;i <= n/*如果每个d[i]都是1，那么最坏情况下遍历n次就可以*/;i++)
	{
		if(d[i] * 2 <= t)//注意是小于等于，原因下面会讲
		{
			ans++;
			t -= d[i] * 2 - 1;
		}
		else
		{
			ans++;//剩下的数可以组成队列
			//上面如果不取等的话，那么总结果就会少算一次
			break;	
		}
	}
	cout<<ans;
 	return 0;
}
```

---

## 作者：luochenkai (赞：3)

# P10315题解
## 输入
因为数列不一定连续，所以建议用桶的方式存储数据,也方后便续分割。

代码：
```cpp
	int n;
	int t;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t;
		a[t]++;//桶存储
	}
```
## 数列分割
注意：由于出现次数**严格大于序列长度一半**的元素领导元素，所以分割时应该减一。

代码：

```cpp
bool cmp(int x,int y){//自定义
	return x>y;
}
```

```cpp
	int num=n;//用于计算是否能够完全分割
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i]*2<=num){//判断能否完全分割
			ans++;//增加数列数量
			num-=a[i]*2-1;//注意减一
		}
		else break;//分割完成，跳出循环
	}
```
## 输出
我相信大家都会。
## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans=1;//别忘了初始有一个数列
int a[500005];
bool cmp(int x,int y){//自定义
	return x>y;
}
int main(){
	int t;
	cin>>n;
	int num=n;//用于计算是否能够完全分割
	for(int i=1;i<=n;i++){
		cin>>t;
		a[t]++;//桶存储
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i]*2<=num){//判断能否完全分割
			ans++;
			num-=a[i]*2-1;//减少还需分割数量
		}
		else break;//分割完成，跳出循环
	}
	cout<<ans;
	return 0;
}
```
我第一篇发布的题解，有写的不好的地方还请多多包涵。

---

## 作者：dinghongsen (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P10351)

### 解题思路

先用一个数组计数，再排序，把数量最多的放在前面，由于序列中出现次数严格大于序列长度一半的元素被称为序列的领导元素，所以每个序列的长度最小就是 $2 \times a_{i} - 1$（$a_{i}$ 指前面计数的数组的元素），再看一共能划分多少次序列，这样，划分的数目自然就最小，最后输出即可。

### code

```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n;
int a[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a[x]++;
    }
    sort(a + 1, a + n + 1, greater<int>());
    int cnt = n, ret = 0;
    for (int i = 1; i <= n && cnt > 0; i++) {
        cnt -= 2 * a[i] - 1;
        ret++;
    }
    printf("%d", ret);
    return 0;
}
```

---

## 作者：__XU__ (赞：1)

## P10351 题解

第一眼，一道普通的暴力题。

### 做法：

开个数组统计一下各各数出现的次数，从后往前遍历一遍，判断一下条件即可。

### 如何判断：

设一个数 $i$ 出现的次数为 $x_i$。不难发现，当 $2 \times x_i \le n$ 时，符合题目要求（自己可以尝试一下）。

这样就做完了！

## AC code

```
#include<bits/stdc++.h>
const int N=5e5+5;
using namespace std;
int n,a[N];
int s1[N],s2[N];
int cnt=1;
int t;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s1[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		s2[i]=s1[i];
//		cout<<s2[i]<<' ';
	}
	sort(s2+1,s2+n+1,cmp);
	t=n;
	for(int i=1;i<=n;i++){
		if(s2[i]*2<=t){
			cnt++;
			t-=s2[i]*2-1;
		}
		else{//不满足条件 终止程序 
			break;
		}
	}
	cout<<cnt;
 	return 0;
}
```

谢谢观看。

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

贪心思路：货尽其用，人尽其力。

我们每一次分段时一定会尽量的让这一段更长一些，同时让后面的也能足够长。而他没有要求连续，每一次截的是子序列，因此，同一个数一定会尽量选入同一个序列。这样，假定这个数共有 $k$ 个，我们就能带走另外 $k-1$ 个数。

而显然，$k$ 越大，带来的收益就越大。因此，我们选最后那 $k-1$ 个数时应当尽量选个数少的数。可以用双指针维护。

代码如下：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a,t[500005],ans;
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;++i)
    	cin>>a, t[a]++;
    sort(t+1,t+n+1); reverse(t+1,t+n+1);
    while(!t[n]) n--;
    for(int l=1,r=n;l<=r;++l){
    	int tmp=t[l]-1; ans++;
    	while(r>l&&tmp>=t[r]) tmp-=t[r],r--;
    	if(r>l) t[r]-=tmp;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10351)

## 题目大意
给定一个序列，在分成子序列数最小的情况下使得每个序列都有领导数（序列中出现次数大于序列长度一半的数被称为序列的领导数）。

## 解题思路
感谢大佬 @[White__Deer](https://www.luogu.com.cn/user/1039209) 指正错误并提供思路！

不难想到，对于当前数所在的序列，让其它数的数量是当前数数量 $-1$，则该序列是以当前数为领导数下最长的。

要想让分的序列更少，则优先选择出现数量更多的领导数，所以要对领导数的出现次数从大到小排序。

可以用数组 $b$ 存每个数字出现个数，除了只出现过一次的数字外，我们都可以通过分配使其成为领导数。所以我们可以通过枚举领导数来求最少序列个数。

其余见代码注释。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500001],b[500001],sum,ans;
bool cmp(int x,int y){return x>y;}
int main()
{
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	sum=n;//sum为剩余数字数量 
	for(int i=1;i<=n;i++)cin>>a[i],b[a[i]]++;
	sort(b+1,b+n+1,cmp);//从大到小排序 
	for(int i=1;i<=n;i++)
	{
		if(b[i]*2<=sum)ans++,sum-=b[i]*2-1;
		//其它数字数量可以与当前数凑成一个最长的序列，就尽量凑 
		else{cout<<ans+1;return 0;}
		//不行就把剩下的数与当前数凑成一个序列，然后输出答案 
	}
	return 0;
}
```
拜拜！

---

## 作者：zsh_haha (赞：0)

### 题目大意

对于一个长度为 $n$ 的序列，对其中的数随便排列，并将其分成 $k$ 个部分，要求每个部分中的个数最多的数的个数必须超过该部分的数的总数的一半，求 $k$ 最小为多少。

### 思路讲解

设序列中值为 $i$ 的数的个数为 $a_i$，其中 $a$ 的长度为 $m$，我们可以将前 $k$ 大的 $a_i$ 对应的 $i$ 作为 $k$ 个部分中的个数最多的数，剩下的数作为其余的数。

那么如何求出 $k$ 呢？

已知一个部分中的个数最多的数的个数为 $a$，那么其余的数必须严格小于 $a$，也就是小于等于 $a-1$，那么 $k$ 个部分中每个部分中的个数最多的数的个数之和若为 $b$，那么其余的数的个数必须小于等于 $b-k$。

那么 $k$ 也很好求出来了。我们先把 $a$ 从大到小排序，让 $i$ 从 $1$ 开始从小到大遍历，第一个满足 

$$\sum^{i}_{j=1}a_j-i\ge\sum^{m}_{j=i+1}a_j$$

的 $i$ 就是我们要求的 $k$。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[500001],b[500001]/*b 是前缀和数组，以快速求和*/;
bool cmp(long long x,long long y){
	return x>y;
}
int main(){
	long long n,m,x;
	cin>>n;
	for(long long i=1;i<=n;i++){
		scanf("%lld",&x);
		if(a[x]==0){
			m++;
		}
		a[x]++;
	}
	sort(a+1,a+1+500000,cmp);//从大到小排序 
	for(long long i=1;i<=m;i++){
		b[i]=b[i-1]+a[i];//求前缀和 
	}
	for(long long i=1;i<=m;i++){
		if(b[i]-i>=b[m]-b[i]/*相当于题解中的不等式*/){
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10351)
## 解题思路
简单贪心题。

我们先把数组中的数字都计一下数，统计每个数组出现了几次。

接着，把计数数组从大到小排序，方便等一下贪心。

接着，$i$ 从 $1$ 到 $n$ 遍历，因为领导元素是序列中出现次数严格大于序列长度一半的元素，所以每一个数，都最多会领导 $a_i-1$ 个数字。我们就让 $s$ 每次加上 $2\times a_i-1$，如果 $s\ge n$，直接输出 $i$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		a[x]++;
	}
	sort(a+1,a+n+1,greater<int>());
	int s=0;
	for(int i=1;i<=n;i++)
	{
		s+=a[i]*2-1;
		if(s>=n)
		{
			cout<<i;
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：coderJerry (赞：0)

### 题目描述
将一个长度为 $n$ 的序列 $a$ 分成若干段，使得每一段内都有一个元素出现次数大于该序列长度的一半。
### 题目分析
我们可以先搞一个桶记录该数值出现的个数，然后因为题目要求分割成的段数尽量少，我们对这个桶从大到小排序，每次贪心的选择出现次数最多的一个元素（设有 $x$ 个），那么最好的情况下这个元素就能够构造长度为 $2x-1$ 的子序列，统计好输出即可。具体实现可以参考下面。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int mp[500010];
bool cmp(int x,int y){return x>y;}
int n,x;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        mp[x]++;
    }
    sort(mp+1,mp+n+1,cmp);
    int y=n,cur=0;
    while(y>0){
        ++cur;
        y=y-(mp[cur]*2-1);
    }
    cout<<cur<<endl;
    return 0;
}
```

---

## 作者：TheForgotten (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10351)

## 题意简述
编写一个程序来确定给定序列可以被分成多少个子序列，每个子序列至少包含一个序列中出现次数严格大于序列长度一半的元素。

## 解题思路
代码需要实现一个计算最小子序列数的算法，可以使用排序和贪心策略。

首先，读取输入的序列长度和序列本身，并使用桶记录每个数字的出现次数。
然后，将数组中的元素复制到第三个数组中，并进行降序排序。
对于每个元素，如果它的出现次数乘以 $2$ 不超过当前剩余序列长度 $siz$，就增加 $ans$ 的值，并更新 $siz$，在最后输出 $ans$ 就可以找到最小的答案。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int o=500005;
int n,a[o],b[o],c[o],leng,ans=1;
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>n;
	leng=n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=n;i++) c[i]=b[i];
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(c[i]*2<=leng){
			ans++;
			leng-=c[i]*2-1;
		}
		else break;
	}
	cout<<ans;
 	return 0;
}
```
> 任何一个伟大的思想，都有一个微不足道的开始。

---

## 作者：gh_AC (赞：0)

### 题意：

输入一些数，把他们分成一些可以间断的序列，并且这些序列中一定有一个数的数量严格大于序列总长度的一半（我们将这个数称为领导元素）。我们需要输出将这些数分成最少的序列的个数。

### 思路：

我们可以先将所有的数的数量求出来，然后就可以得出以这个数为领导元素能组成序列的最大长度，然后我们将这些数的数量排序，然后从大到小地遍历每一个数的数量，每一次用总数减去以这个数为领导元素能组成序列的最大长度，直到总数小于一时也就代表所有数都用完了，就输出遍历的次数。

### AC 代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=500005;
int n,a;
int s[N],x,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		s[a]++;
		// 保存每个数的数量 
		x=max(x,a);
	}
	sort(s+1,s+1+x);
	while(n>0){
		n-=(s[x]*2-1);
		// 当这个数为领导元素时，这个序列的最长长度就是此元素数量减一 
		x--,ans++;
		// 累加序列个数 
	}
	cout<<ans;
	return 0;
}
```

---

