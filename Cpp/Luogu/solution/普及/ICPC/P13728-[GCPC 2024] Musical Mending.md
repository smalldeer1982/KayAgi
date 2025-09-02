# [GCPC 2024] Musical Mending

## 题目描述

在音乐会即将开始前，你发现你的钢琴完全走音了！由于你具备相对音高的能力，你能够分辨出任意琴键与第一个琴键之间的音高差。虽然这无法帮助你确定绝对音高，但你决定至少将各琴键之间的音高调整为相对正确。为此，你需要确保每个琴键的音高恰好比前一个琴键高 $1$，比后一个琴键低 $1$。

由于音乐会即将开始，你需要最小化总的调音工作量，即你对每个琴键施加的音高变化的绝对值之和。

例如，图 M.1 展示了样例输入 3 的一种解决方案，总调音工作量为 $23$。

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/4shk0pix.png)

图 M.1：样例输入 3 的可视化。
:::

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
0 1 2 3 4 5 6```

### 输出

```
0```

## 样例 #2

### 输入

```
5
0 1 4 3 6```

### 输出

```
4```

## 样例 #3

### 输入

```
6
0 -2 10 6 7 -1```

### 输出

```
23```

## 样例 #4

### 输入

```
4
0 -4 -2 1```

### 输出

```
7```

## 样例 #5

### 输入

```
9
0 23452 145043 -3423 -20 9845 435 -3 4453```

### 输出

```
186237```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

我们发现值域小，所以考虑枚举第一个键的实际音高。首先，因为是等差数列，所以让所有的 $a_i$ 减去 $i$ 之后问题就变成了让所有数相等的最小代价。考虑这个式子是 $\min_{x\in \Z}\left(\displaystyle\sum_{i=1}^n|a_i-x|\right)$，我们可以把小于 $x$ 的数和大于的分开算。我们枚举 $x$ 向上扫的时候两种数的和与数量变化只取决于等于新的 $x$ 的数有多少，所以可以预处理并直接算出来，总复杂度 $O(N+V)$，其中 $V$ 为值域，这里取 $5\times 10^5$（因为要减去 $i$）。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int cnt[800010],a[800010];
signed main()
{
	int n,minn=1e9;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]-=i;
		minn=min(minn,a[i]); 
	}
	for(int i=1;i<=n;i++) a[i]-=minn,cnt[a[i]]++;
	int ans0=0,ans1=0,mn=0,cnt0=0,cnt1=n;
	for(int i=1;i<=n;i++) ans1+=a[i];
	mn=ans1;
	for(int i=0;i<=8e5;i++)
	{
		ans1-=cnt[i]*i;
		cnt1-=cnt[i];
		ans0+=cnt[i]*i;
		cnt0+=cnt[i];
		mn=min(mn,(ans1-cnt1*i)+(cnt0*i-ans0));
	}
	cout<<mn;
}

---

## 作者：chenjunnan (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P13728)
## 形式化题意：
给定一个数列，定义将 $u$ 修改为 $v$ 的费用为 $|u-v|$，求将原数列修改为一个公差为 1 的等差数列的最小费用。
# 算法分析
考虑将每一项 $t_i$ 减去 $(i-1)$，于是目标等差数列的每个数均转化为首项。目标等同于求一个数到数列中所有数的距离最小。  
这是一道很裸的贪心。显然这个值不会小于数列最小值，不会大于数列最大值。而在最小值与最大值之间取值时，最小值和最大值的贡献和保持不变。于是可以忽略最小值与最大值，继续考虑。如此反复，即可得出当取到数列的中位数（项数为偶数时取中间两项之间任意一数均可）时即得答案。
# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define gc() getchar_unlocked()
#define pc(a) putchar_unlocked(a)
#define f(i,a,b,n) for(int i=a;i<=b;i+=n)
#define TT template <typename T>
using namespace std;
TT inline T in(){
	T x=0,f=1;char c=gc();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=gc();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x*f;
}
TT inline void out(T x){
	if(x<0) pc('-'),x=-x;
	if(x<10) pc(x^48);
	else out(x/10),pc((x%10)^48);
}
ll n=in<ll>(),t[100005],s,ans;
int main(){
	f(i,0,n-1,1) t[i]=in<ll>()-i;//读入并减去序号得新数列
    sort(t,t+n);//排序
    s=t[n>>1];//求得中位数
    f(i,0,n-1,1) ans+=abs(t[i]-s);//计算结果
    out<ll>(ans);//输出
	return 0;
}
```

---

## 作者：kill_wcz (赞：0)

我们的故事，以我打扰开始，以我多余结束。
### 题解：P13728 [GCPC 2024] Musical Mending
---
题目大意：

[题目](https://www.luogu.com.cn/problem/P13728)
#### 思路：
题目中的钢琴键必须是逐渐上升，且差值都为一的。  
因为直接处理太麻烦，所以我们把差值先处理。  
把输入的数组每个数都减自己的坐标，存储为一个新的数组。 
```cpp
for (int i = 0; i < n; i++) {//输入
	cin >> a[i];
}
for (int i = 0; i < n; i++) {//处理
	b[i] = a[i] - i;
}
```
经过上面的步骤，我们成功将问题转化为如何用最小的代价将新数组中的每个数变成相同的。  
那就非常简单，所有数要变成的数就是排序后数组的中位数。
::::info[证明]{open}
我们设所有数字要变成 $x$ 。  
首先，将数组排序。  
排序后，我们会发现，为了使所有数字变成相同的，一些数字要变大，而一些数字要变小。  
若 $x$ 左侧的数据比右侧多， $x$ 增大时总距离会减小。  
若 $x$ 右侧的数据比左侧多， $x$ 增大时总距离会增大。  
当 $x$ 处于中位数位置时，两侧数据数量相等，总距离达到最小值。
::::
所以我们得出代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=0,a[1000001],b[1000001];
signed main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		b[i] = a[i] - i;
	}
	sort(b,b+n);
	int mid = b[n / 2];
	for(int i=0; i<n; i++) {
		ans += abs(b[i] - mid);
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：wuhaolinwhl (赞：0)

## [P13728](https://www.luogu.com.cn/problem/P13728)题解  
### 题目大意：  
题目给定一个长度为 $n$ 的数组，我们要将它变成一个上升序列且后一项只比前一项大一，使每一项改变前后的差值的绝对值相加最小。  
### 思路解析：  
这道题的贪心思路是定义一个 $b[i]$ 数组等于 $t[i]-i$ 的值。将 $b$ 数组排序，取 $b[i]$ 的中位数为数组改变结果后的开头。最后求解就好了。  
对于这个方案的论证是这样的。因为题目要求后一项一定是前一项加一，所以对于一个合法的数组当它的每一项减掉了自己的编号后都是相等的。于是我们就可以通过对 $b$ 数组进行排序来取中位数求得开头的值。至于为什么要取中位数应该都知道吧（在一个数组中，所有数与中位数的差值的绝对值总和最小）。  
### 代码如下。  
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,sum,s[1000005],l[1000005];
long long ans;
struct NODE
{
	int a,id;
}t[1000005];
bool cmp(NODE x,NODE y)
{
	return x.a<y.a;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>s[i];
    	t[i].a=s[i]-i;
    	t[i].id=i;
	}
	sort(t+1,t+n+1,cmp);//排序，用数组即可。
	for(int i=0;i<n;i++)
	{
		l[i+1]=i+t[(n+1)/2].a+1;
	}
	for(int i=1;i<=n;i++)
	{
		ans+=abs(l[i]-s[i]);
	}
	cout<<ans;
    return 0;
}
```
庆祝自己第一篇题解通过，完结撒花。

---

