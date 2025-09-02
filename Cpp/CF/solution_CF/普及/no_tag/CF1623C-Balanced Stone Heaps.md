# Balanced Stone Heaps

## 题目描述

There are $ n $ heaps of stone. The $ i $ -th heap has $ h_i $ stones. You want to change the number of stones in the heap by performing the following process once:

- You go through the heaps from the $ 3 $ -rd heap to the $ n $ -th heap, in this order.
- Let $ i $ be the number of the current heap.
- You can choose a number $ d $ ( $ 0 \le 3 \cdot d \le h_i $ ), move $ d $ stones from the $ i $ -th heap to the $ (i - 1) $ -th heap, and $ 2 \cdot d $ stones from the $ i $ -th heap to the $ (i - 2) $ -th heap.
- So after that $ h_i $ is decreased by $ 3 \cdot d $ , $ h_{i - 1} $ is increased by $ d $ , and $ h_{i - 2} $ is increased by $ 2 \cdot d $ .
- You can choose different or same $ d $ for different operations. Some heaps may become empty, but they still count as heaps.

What is the maximum number of stones in the smallest heap after the process?

## 说明/提示

In the first test case, the initial heap sizes are $ [1, 2, 10, 100] $ . We can move the stones as follows.

- move $ 3 $ stones and $ 6 $ from the $ 3 $ -rd heap to the $ 2 $ -nd and $ 1 $ heap respectively. The heap sizes will be $ [7, 5, 1, 100] $ ;
- move $ 6 $ stones and $ 12 $ stones from the last heap to the $ 3 $ -rd and $ 2 $ -nd heap respectively. The heap sizes will be $ [7, 17, 7, 82] $ .

In the second test case, the last heap is $ 1 $ , and we can not increase its size.

In the third test case, it is better not to move any stones.

In the last test case, the final achievable configuration of the heaps can be $ [3, 5, 3, 4, 3, 3] $ .

## 样例 #1

### 输入

```
4
4
1 2 10 100
4
100 100 100 1
5
5 1 1 1 8
6
1 2 3 4 5 6```

### 输出

```
7
1
1
3```

# 题解

## 作者：ycy1124 (赞：19)

### 题意
有 $n$ 堆石子，我们可以从第三堆开始，每次拿出 $3 \times d_i$ 枚石子 $(0 \le d_i  \le \frac{a_i}{3 })$，将其中 $d_i$ 枚放入第 $i - 1$ 堆中，将 $2 \times d_i$ 枚石子放入第 $i - 2$ 堆石子中。现在问你，最少的那堆石子最多有几枚。
### 想法
看到最少的最多，自然想到二分答案。
### 做法
由于方便计算 $d_i$ 所以我们可以在读入的时候将整个数组反过来。对于每个 $mid$ 我们将这 $n$ 堆石子所能取到的最大的 $d_i$ 统计下来。并且在统计的过程中记录方案是否合法。
### 注意事项
1. 对于每个 $d_i$ 一定要对它取个 $\min{(d_i,\frac{a_i}{3})}$。

2. 一定要边求 $d_i$ 边判断数组的合法性，不能只判断最后两个数。

3. 注意最后两个数将会没有 $d_i$。
### 代码
```cpp
#include<bits/stdc++.h>//114514
using namespace std;
int a[200001];
int tmp1[200001],tmp2[200001];
int main(){
	int t;
	scanf("%d",&t);
	while(t){
		t--;
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[n-i+1]);//将数组反着输入。
		}
		int l=0,r=int(1e9);
		int ans=0;
		while(l<=r){
			int mid=l+r>>1;
			bool bj=0;
			for(int i=1;i<=n-2;i++){
				if(a[i]+tmp1[max(0,i-1)]+tmp2[max(0,i-2)]<mid){//判断。
					bj=1;
				}
				tmp1[i]=min(int(floor(1.00*max(a[i]+tmp1[max(0,i-1)]+tmp2[max(0,i-2)]-mid,0)/3)),a[i]/3);//统计 d 数组。
				tmp2[i]=min(int(floor(1.00*max(a[i]+tmp1[max(0,i-1)]+tmp2[max(0,i-2)]-mid,0)/3)),a[i]/3)*2;//统计 d 数组。
			}
			if(bj){
				r=mid-1;
				ans=mid-1;
				//printf("1 %d %d\n",l,r);
			}
			else if(a[n-1]+tmp1[max(0,n-2)]+tmp2[max(0,n-3)]<mid||a[n]+tmp2[max(0,n-2)]<mid){
				r=mid-1;
				ans=mid-1;
				//printf("2 %d %d\n",l,r);
			}
			else{
				l=mid+1;
				ans=mid;
				//printf("3 %d %d\n",l,r);
			}
		}
		printf("%d\n",ans);//输出答案。
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/169690639)。

最后复杂度 $\mathcal{O}(n\log n)$ 通过此题。

---

## 作者：yeshubo_qwq (赞：8)

## 思路
二分答案，重点在于如何验证答案。

考虑反着做一遍来验证答案。

一个位置最好能在符合条件的情况下尽量把多余的给前面，但不能超过原有的，把后面位置给的再给前面（因为题目里是正着做的，而我们是反着做的）。

在这个过程中，如果出现负数肯定是不行的。

最后判断前两个位置是否符合条件即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,i,l,r,mid,ans,a[200010],b[200010];
bool check(int x){
	int d;
	for(int i=n;i>=3;i--){
		if(a[i]<x)return 0;//负数肯定是不行的
		d=min(a[i]-x,b[i])/3;
		//a[i]-x为可以给前面的，b[i]是原有的，取min保证不会将后面位置给的再给前面
		a[i-2]+=2*d;a[i-1]+=d;a[i]-=d*3;
	}
	return a[1]>=x&&a[2]>=x;//判断前两个位置是否符合条件
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
		l=1;r=1e9;
		while(l<=r){//二分答案
			mid=(l+r)>>1;
			if(check(mid))l=mid+1,ans=mid;
				else r=mid-1;
			for(i=1;i<=n;i++)a[i]=b[i];//check中改变了a数组，还原
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：vvauted (赞：2)

## Solution 

求最小值最大是二分 $ans$ 的标志，考虑 $O(n)$ 暴力 $check(x)$：

设 $g_i$ 表示 $h_{i}$ 被加上的值，那么我们即为检验：

$$\forall i\in [1,n],h_i+g_i\ge x$$



显然 $b_i$ 是在  $a_{i}$ 对 $a_{i-1},a_{i-2}$ 做贡献之后才加进来的，不参与这个贡献，但会对这个贡献产生影响：

对于 $i$，考虑让其满足条件的情况下，选出尽量大的 $d$，那么这个最大值为 $d=\lfloor\frac{\max\ (h_i+g_i-x,0)} 3\rfloor$，但由于 $b_i$ 不参与贡献，那么 $d=\min(\lfloor\frac{\max\ (h_i+g_i-x,0)} 3\rfloor,a_i)$。

因为求 $d$ 需要在知道 $g$ 的情况下，于是循环倒着跑，预处理出 $g_i$。

## Code
```cpp
#include <stdio.h>
#define Maxn 1000005
#define inf 1e9 + 1

int a[Maxn], b[Maxn], n, t, c[Maxn];
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

bool check(int x) {
	for(int i = 1; i <= n; ++ i) b[i] = a[i], c[i] = 0;
	
	for(int i = n, p; i > 2; -- i) {
		p = max(min(b[i], c[i] + b[i] - x), 0) / 3;
		b[i] -= p * 3;
		c[i - 1] += p;
		c[i - 2] += p * 2;
	}
	
	for(int i = 1; i <= n; ++ i) if(b[i] + c[i] < x) return 0;
	
	return 1;
}

int main() {
	scanf("%d", &t);
	
	while(t --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
		int l = 0, r = inf, mid;
		
		while(l + 1 < r) {
			mid = l + r >> 1;
			if(check(mid)) l = mid;
			else r = mid;
		}
		
		printf("%d\n", l);
	}
}
```



---

## 作者：cwd2023 (赞：1)

# CF1623C题解
#### by cwd2023 

---

### 题目大意：

有一些石子堆，你可以通过一些操作改变它们的数量，你要使石子堆中**数量最大的值最小**（人话：尽可能**平均**）。

---

### 思路:
由最大值最小可以看出是二分答案，至于怎么验证，我们可以把每一堆中超过二分过程中的  $mid$  的部分拿走，但不能超过  $h[i]$。

取走的部分放在哪呢?   

我们发现  $h[1]$  和  $h[2]$  两个位置十分特殊，只获得石子，不贡献石子，是答案的瓶颈，所以我们从后向前放，尽量满足  $h[1]$  和  $h[2]$。

---

### Code:
#### 详细注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n;
ll a[200010],h[200010];
bool check(ll x){
	for(ll i=1;i<=n;i++)h[i]=a[i];
//传递石子过程中会改变原数组的值，所以换个数组来记
	for(ll i=n;i>=3;i--){
		if(h[i]<x)return false;//不能小于答案
		ll y=min(h[i]-x,a[i])/3;
//对应思路第一段
//注意，此时的h[i]包含了n到i+1之间的石子贡献，要与a[i]区分
		h[i]-=3*y,h[i-1]+=y,h[i-2]+=2*y;//操作
	}
	return h[1]>=x&&h[2]>=x;
//检查h[1]和h[2]是否满足条件
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ll l=1,r=0;
		for(ll i=1;i<=n;i++){
			cin>>a[i];
			r=max(r,a[i]);//求值域范围
		}
		while(l<=r){//二分
			ll mid=(l+r)/2;
			if(check(mid))l=mid+1;
			else r=mid-1;
		}
		cout<<r<<"\n";
	}
	return 0;
}
```
#### 无注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,ma;
ll a[200010],h[200010];
bool check(ll x){
	for(ll i=1;i<=n;i++)h[i]=a[i];
	for(ll i=n;i>=3;i--){
		if(h[i]<x)return false;
		ll y=min(h[i]-x,a[i])/3;
		h[i]-=3*y,h[i-1]+=y,h[i-2]+=2*y;
	}
	return h[1]>=x&&h[2]>=x;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ll l=1,r=0;
		for(ll i=1;i<=n;i++){
			cin>>a[i];
			r=max(r,a[i]);
		}
		while(l<=r){
			ll mid=(l+r)/2;
			if(check(mid))l=mid+1;
			else r=mid-1;
		}
		cout<<r<<"\n";
	}
	return 0;
}
```
最后，希望我的题解对你有所帮助，感谢观看。   
### 望管理员通过！

---

## 作者：BigSmall_En (赞：1)

## 题意描述

有 $n$ 堆石子，每第 $i$ 堆石子有 $h_i$ 个石子。每次从第 $3$ 堆石子开始**从前往后**进行以下操作：

1. 选择第 $i$ 堆石子。
2. 选择一个数字 $d(0\leq 3\times d\leq h_i)$ , 将第 $i$ 堆石子减少 $3\times d$ 个石子，同时给第 $i-1$ 堆石子 $d$ 个石子，第 $i-2$ 堆石子 $2\times d$ 个石子。

要求经过操作之后，最小堆的石子数量最大，求这个数量是多少。

## 题解

看到最小堆的石子数量最大容易想到二分答案，同时容易发现答案满足单调性。

但是要考虑二分答案的 `check` 如何书写。

考虑怎么贪心最优秀。

假设现在二分的答案值为 $ans$ 。

发现对于最后一堆石子，它不能从别的堆中获得石子，所以考虑起来比较容易。为了使前面的石子数量尽可能的多，它应该在满足自己满足 $\geq ans$ 的前提下给更多的石子给前面。这个 $d$ 为 $\lfloor\frac{h_n-ans}{3}\rfloor$  

这样子前面的堆的石子就增加了，假设这时每一堆石子的个数为 $b_i$ 。则 $b_{n-1}=h_{n-1}+\lfloor\frac{h_n-ans}{3}\rfloor$ 则第 $n-1$ 堆就应该给前面 $3\times \lfloor\frac{b_{n-1}-ans}{3} \rfloor$ 个石子。但是由于只能从前往后进行操作，所以最多给 $3\times\lfloor\frac{h_{n-1}}{3} \rfloor$ 个石子。

即对于第 $i$ 堆取 $3\times\lfloor\frac{\min\{b_i-ans,a_i\}}{3}\rfloor$ 给前面的石子。

## 代码

剩下的实现就不难了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=200005,INF=0x3f3f3f3f;
int T,n,a[N],b[N];
inline bool check(int lim){
	//cout<<"check:"<<lim<<endl;
	for(int i=1;i<=n;++i)
		b[i]=a[i];
	for(int i=n;i>=3;--i){
		if(b[i]<lim)return 0;
		int can=min(a[i],(b[i]-lim))/3;
		b[i]-=can*3;
		b[i-1]+=can*1;
		b[i-2]+=can*2;
	}
	if(b[1]<lim||b[2]<lim)return 0;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		int l=INF,r=0,mid=0,ans;
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			l=min(l,a[i]);r=max(r,a[i]);
		}
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid))l=mid+1,ans=mid;
			else r=mid-1;
		}printf("%d\n",ans);
	}	
	return 0;
}
```

---

## 作者：ArrogHie (赞：1)

## 题意

有 $n$ 堆石头，每堆石头的石头数量为 $h_i$，你可以将第 $i$ 堆石头执行如下操作：

将 $3k$ 个石头从第 $i$ 堆中拿出，将其中 $k$ 个石头放入第 $i-1$ 堆， $2k$ 个石头放入第 $i-2$ 堆。

操作的限制为，你只能从第 $3$ 堆依次操作至第 $n$ 堆，即不能先操作后面的石头堆再操作前面的石头堆，且每堆石头只能操作一次。

求最后石头数量最少的石头堆里的石头数量最大是多少。

## 题解

字里行间全是二分。

二分答案，如何判断答案是否可行。

设二分的答案为 $ans$， $a_i$ 为第 $i$ 堆石头初始的石头数， $b_i$ 为其他石头堆最多能给第 $i$ 堆多少石头，则第 $i$ 堆石头在满足条件的情况下最多能拿出去的石头数为 $\min(a_i,a_i+b_i-ans)$，之后 $b_i$ 再减去拿出去的石头。最后判断是不是所有的 $i$ 都满足 $ans\leq a_i+b_i$ 即可。

---

## 作者：focus_aurora (赞：0)

## 思路

二分答案。

对最少一堆石子的个数进行二分。

首先负数肯定不可以。

倒着判断每一个数，在不超过原有的前提下，尽量多的给到前面的石子堆中。

进行模拟即可。

最后判断前两个位置是否符合条件。

符合要求，在二分中记录答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n;
int a[N],b[N];
int lll(int x){
	for(int i=n;i>=3;i--){//倒着判断
		if(a[i]<x){//不符合要求，直接特判
			return false;
		}
		int d=min(a[i]-x,b[i])/3;//不超过原有的前提下
		a[i]-=3*d;//模拟
		a[i-1]+=d;
		a[i-2]+=2*d;
	}
	if(a[1]>=x&&a[2]>=x){//前两个位置是否符合要求
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){//多测！
		cin>>n;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);//输入
			b[i]=a[i];//记录a数组
		}
		int ans=0;
		int l=1,r=1e9;
		while(l<=r){//二分
			int mid=(l+r)>>1;
			if(lll(mid)){
				l=mid+1;
				ans=mid;//记录答案
			}
			else{
				r=mid-1;
			}
		}
		for(int i=1;i<=n;i++){//恢复原数组
			a[i]=b[i];
		}
		cout<<l-1<<"\n";//输出答案
	}
    return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
就是从第三堆石头开始从前往后按照题目的要求往前放石头，使得最小的一堆石头里面的石子在所有方案中最大。

注意看一定是拿出来 $3n$ 个石头，前面两堆都要放。
## 大体思路
求最大值问题优先想到二分答案，我们二分一下数量最少的一堆石子的个数即可，从后往前 check 一下是否合法。

二分最少的石子个数 $x$，维护 $b$ 数组和 $c$ 数组，分别代表未修改前的 $hh$ 数组和前面被当前这一堆石头放进来的石子数，算出最多可以向前传的石子数 $d$，模拟往前传，注意因为题目中是从前向后进行向前传操作，而我们是从后向前模拟，所以每次传不能超过 $hh_i$ 个，这里要特判一下，模拟完之后循环判定一下最小值成不成立即可。

合法的话记录 $ans$，让 $l$ 再向前贪一位，不合法的话 $m=mid-1$。

详见代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long hh[200005],b[200005],c[200005];
int n;
bool check(long long x){
	if(x<=14){
		x++;
		x--;
	} 
	for(int i=1;i<=n;i++){
		b[i]=hh[i];//b记录未修改前的hh数组 
		c[i]=0;//c存储前面被当前这一堆石头放进来的石子数 
	}
	for(int i=n;i>=3;i--){
		if(x>b[i]+c[i]){//留下的最小值比现在有的还多 
			return 0;//直接放弃 
		}
		long long d=(b[i]+c[i]-x)/3;//能够往前放的最大d 
		if(hh[i]<d*3){//因为题目要求是从前往后传，所以不能出现传出负数的情况 
			d=hh[i]/3;
		}
		b[i]-=d*3;//这个节点在这个情况下减去他往前放的 
		c[i-1]+=d; 
		c[i-2]+=d*2;//前面俩节点加上这个节点往前放的
	}
	for(int i=1;i<=n;i++){
		if(b[i]+c[i]<x){//如果有小于这个最小数量的石头堆 
			return 0;//当前最小值不合法 
		}
	}
	return 1;//否则合法 
}
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>hh[i];
		}
		long long l=1,r=1e9,ans;//二分边界
		while(r>=l){//二分模版 
			long long mid=(l+r)>>1;
			if(check(mid)){
				l=mid+1;
				ans=mid;
			}
			else{
				r=mid-1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：ryl_ahu (赞：0)

#### 比较模版的二分。

一般二分的题目都是二分枚举答案，这道题也是一样的，二分枚举数量最少的一堆石子的最大值。

我们二分枚举答案 $x$，对于每一次，判断能否通过题目中的操作使得石子数量最少的一堆的数量为 $x$：

- 从后往前来算。
- 所有的除了前两堆以外的石子堆我们都让它的数量为 $x$。
- 对于第 $i$ 堆石子会比 $x$ 多出来 $y$ 颗石子（$y$ 可以等于 $0$），将 $\lfloor y\div 3\rfloor$ 颗石子给到第 $i-1$ 堆，将 $\lfloor y \div 3 \rfloor \times 2$ 颗石子给到第 $i-2$ 堆。
- 最终如果第 $1$ 堆和第 $2$ 堆石子的数量都大于等于 $x$，则石子数量最少得一堆数量可以为 $x$。

根据以上语句来写二分时的判断条件即可。

需要注意，我们不能直接在原数组上进行操作，会影响下一次的判断。所以最好是再用另外一个数组来记录每次往前面的石子堆放几颗石子。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long h[200005];
long long g[200005];//从后面的石子堆挪过来的石子
int n, t;
bool erfen(int mid){
	int d;
	for (int i = 1; i <= n; i++) {
		g[i] = 0;//初始化，用memset有可能会TLE
	}
	for (int i = n; i >= 3; i--) {//从后往前推
		if (h[i] + g[i] < mid) {//如果比数量最少的还要少就肯定不行
			return false;
		}
		if (g[i] >= mid) {
			d = h[i];
		}
		else {
			d = h[i] + g[i] - mid;
		}
		//将多余的石子给到前面两堆
		g[i - 1] += d / 3;
		g[i - 2] += d / 3 * 2;
	}
	if (h[1] + g[1] >= mid && h[2] + g[2] >= mid) {//所有元素都大于等于mid即为可以
		return true;
	}
	else {
		return false;
	}
}
int main() {
	int l, r, mid, sc;
	cin >> t;
	while (t--) {
		cin >> n;
		l = 0, r = 1e9;
		for(int i = 1; i <= n; i++) {
			cin >> h[i];
		}
		while (l <= r) {//二分
			mid = (l + r) / 2;//枚举数量最少的一堆石子的最大值
			if (erfen(mid)) {
				l = mid + 1;
				sc = mid;
			}
			else {
				r = mid - 1;
			}
		}
		cout << sc << endl;
	}
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1623C)

# 思路

“最小石堆数量最大”二分答案的标志，由于最后一堆石子不能收到其他石堆的援助，所以从后往前遍历，尽量让后面的石堆满足前面的石堆，我们用 $ dis $ 表示前面石堆收到的石子，复制一份 $ a $ 数组到 $ dev $ 里，核心代码:

$$ d = \operatorname{min}(dev_i,dev_i+dis_i-x)/3 $$ 

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int t,a[N],dev[N],dis[N],n;
bool check(int x){
	int k;
	for(int i=1;i<=n;i++)
		dev[i]=a[i],dis[i]=0;//dis储存i-1和i-2增加的石子数量 
	for(int i=n;i>=3;i--){
		k=min(dev[i],dev[i]+dis[i]-x)/3;//核心代码：从后往前遍历，尽量让后面的满足前面的石堆 
		if(k<0) k=0;//负数不行 
		dev[i]-=k*3;
		dis[i-1]+=k;
		dis[i-2]+=k*2;//模拟过程 
	}
	for(int i=1;i<=n;i++)
		if(dev[i]+dis[i]<x)
			return false;//二分找大于mid的 
	return true;
}
int read(){
	int f=1,res=0;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*f;
} 
void write(int x){
	if(x>9) write(x/10);
	if(x<0) x=-x,putchar('-');
	putchar(x%10+'0');
}
int main(){
	t=read();
	while(t--){
		n=read();
		int l=1e9,r=-1e9,mid=0,ans;
		for(int i=1;i<=n;i++){
			a[i]=read();
			dev[i]=a[i];//复制一份a数组 
			l=min(l,a[i]),r=max(r,a[i]);//二分范围 
		}
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid))
				l=mid+1,ans=mid;//储存答案 
			else 
				r=mid-1;
		}
		write(ans);
		printf("\n");//完结撒花 
	}
	return 0;
}
```


---

## 作者：sprads (赞：0)

**题目链接**：[CF1623C](https://codeforces.com/problemset/problem/1623/C)

二分答案 + 贪心

二分答案通过口胡得到，相对简单。

重点讲一讲贪心。

设我们通过二分到最小值为 $cap$，石堆 $i$ 原有石头 $h_i$ 个，经过移动，现有石头 $a_i$，现在需要判断 $cap$ 是否能够移动石头得到。

一个基础的想法：对于石堆 $i$，显然希望尽可能地将 $i$ 堆的石块移给 $i-1$ 和 $i-2$，但需要保证通过 $i+1$ 和 $i+2$ 的“支援”仍能使 $a_i \ge cap$。 

**逆序考虑**，也就是从 $n$ 枚举到 $3$，**每次都**贪心进行操作。这样枚举到 $i$，得到的就是第 $i$ 堆石头在 **$cap$ 约束**下，从大于 $i$ 的石堆移来石头，能够得到的**最大**数量。此时，多出 $cap$ 的石头就可以给 $i-1$ 和 $i-2$。

如果此时 $a_i< cap$，$cap$ 不能得到。否则可以移动的石头为 $d = \left \lceil\dfrac{\min(h_i,a_i-cap)}{3}\right \rceil$（显然不能超过 $h_i$），给 $i-1$ 堆 $d$ 块石头，$i-2$ 堆 $2\cdot d$ 块石头。

枚举完 $n$ 到 $3$ 后，判断 $a_1$ 和 $a_2$ 是否大于等于 $cap$ 即可。

**代码**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n;
ll h[200005],a[200005];
bool check(ll cap){
	for(int i = 1;i <= n;i++)
		a[i] = h[i];//提前复制一遍
	for(int i = n;i >= 3;i--){
		if(a[i] < cap)return 0;//最大值都不行，显然不可以
		ll d = min(h[i],a[i] - cap) / 3;//求得d
		a[i - 1] += d;
		a[i - 2] += 2 * d;//分发石头
	}
	return a[1] >= cap && a[2] >= cap;//最后判断一下
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		ll L = 1e9,R,ans;
		for(int i = 1;i <= n;i++)
			scanf("%lld",&h[i]),L = min(L,h[i]);
		R = h[n];//L下界，R上界
		while(L <= R){
			int mid = (L + R) / 2;
			if(check(mid)){
				ans = mid;
				L = mid + 1;
			}
			else R = mid - 1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：PosVII (赞：0)

[CF1623系列](https://www.luogu.com.cn/blog/271260/cf1623-bi-sai-ji-lu)

一眼看出是二分答案，即二分最终答案并检查在此限制条件下是否可行。但是读错题意以为可以反着来做。

对于检查函数，我们可以将一个数大于答案的部分传递给下面的数，但是因为本题要求正着传，所以说一个数传递完后还是可以接受补给，这意味着它本来还可以做贡献。于是考虑倒着枚举，看当前的数可以接受多少补给再传递。因为是先传递再补给，所以不能预支补给传递，分开讨论即可。

注意，数组很大，所以不要将整个数组清空。

时间复杂度 $\mathbin{\mathrm{O(n \log n)}}$。

[Code](https://codeforces.com/contest/1623/submission/146893519)

---

## 作者：huyangmu (赞：0)

这道题要求最小值最大，且答案具有单调性，考虑二分答案。

下一步需要判断二分出的答案 $x$ 是否正确，因为 $x$ 是序列中的最小值，所以其余的数都要大于等于 $x$，考虑通过若干次操作，使得序列中最大的数最大，判断最大的数是否大于等于 $x$，如果是，则 $x$ 为合法答案。

要使得最大的数最大，可以从后往前遍历数组，每次让当前的 $a_{i}$ 提供最多的值给 $a_{i-1}$ 和 $a_{i-2}$，且要保证操作完之后 $a_{i}$ 仍然大于等于 $x$，通过这种操作，最后序列的最大值最大为 $\max \{a_{1},a_{2}\}$。

### AC Code


```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5 + 5;
int T, n, a[N], b[N], l, r, ans, sum;
bool check (int x){
	for (int i = 1; i <= n; ++i) b[i] = a[i];
	for (int i = n; i >= 3; --i){
		if (b[i] < x) return 0;
		int pos = min (a[i] / 3, (b[i] - x) / 3);
		b[i - 2] += 2 * pos;
		b[i - 1] += pos;
		b[i] -= 3 * pos;
	}
	return b[2] >= x && b[1] >= x;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --){
		cin >> n;
		l = LONG_LONG_MAX, sum = ans = 0;
		for (int i = 1; i <= n; ++i){
			cin >> a[i];
			l = min (l, a[i] / 3);
			sum += a[i];
		}
		r = sum / n;
		while (l <= r){
			int mid = l + r >> 1;
			if (check(mid)){
				ans = mid;
				l = mid + 1; 
			}else r = mid - 1;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

