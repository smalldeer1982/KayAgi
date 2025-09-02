# 【MX-X2-T3】「Cfz Round 4」Ninelie

## 题目背景

原题链接：<https://oier.team/problems/X2C>。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/3g0aruaq.png)

沿着单侧无尽响彻的旋律 流经眼前的街道 伴随着落幕的爱 渐行渐远  
那无法传达的理想构图日渐扭曲沉寂的抵抗在此刻觉醒 冲动也在此刻姗姗来迟  
支离破碎的哭喊和美梦 理想只剩下装饰的门面  
哪怕城市乐于被喧嚣嘈杂所淹没  
我也会继续高歌舍弃那掌控我的一切  
所以只愿那静谧 再度响彻  
> 无需畏惧 黎明已然降临

## 题目描述

给定一个长为 $n$ 的 $01$ 序列 $a_1, \ldots, a_n$ 以及一个正整数 $r$。

你可以对序列 $a$ 进行操作。每次操作需选定一个下标 $p$，满足 $p$ 为 $1$ 或 $n$ 或 $a_{p-1}\neq a_{p+1}$，然后将 $a_p$ 翻转（即将 $0$ 变为 $1$，将 $1$ 变为 $0$）。

请你在 $r$ 次操作内将序列 $a$ 变成全 $0$ 或全 $1$。**你不需要最小化操作次数**。如果无法完成，你需要报告无解。

**数据保证 $\bm{r = 2 \times 10^6}$ 或 $\bm{10^6}$，具体细节请参见【数据范围】一节。**

## 说明/提示

**【样例解释 #1】**

每次操作后的序列 $a$ 分别为：

- $[0,1,1,0]$；
- $[0,1,1,1]$；
- $[1,1,1,1]$。

此时序列 $a$ 中的全部元素均相同。

**【数据范围】**

对于所有测试数据，$2\le n\le 2\times 10^3$，$a_i\in\{0,1\}$，$r = 2 \times 10^6$ 或 $10^6$。

**本题采用捆绑测试。**

- Subtask 1（20 points）：$n\le 10$，$r=2\times 10^6$。
- Subtask 2（30 points）：$r=2\times 10^6$。
- Subtask 3（50 points）：$r=10^6$。

## 样例 #1

### 输入

```
4 1000000
0 0 1 0
```

### 输出

```
3
2 4 1
```

## 样例 #2

### 输入

```
5 1000000
1 1 1 1 1
```

### 输出

```
0

```

## 样例 #3

### 输入

```
10 1000000
0 1 0 0 1 1 0 0 1 0
```

### 输出

```
18
1 2 10 1 9 4 10 4 7 4 7 3 7 8 9 2 10 1
```

# 题解

## 作者：ppllxx_9G (赞：13)

## 题目大意

对于一个长度为 $n$ 的 $01$ 串 $s$，你可以对其进行最多 $r$ 次操作，对于每次操作，你可以选择一个下标 $p$ 满足 $p=1$，$p=n$，$s_{p-1}\not=s_{p+1}$ 中的至少一个，将 $s_p$ 反转。输出操作方案。

## 解题思路

最大限制次数 $r=10^6$，恰好是 $\frac{n^2}{4}$ 次，所以考虑能否使每一个位置的操作次数近似 $\frac{n}{4}$。所以想到**从中点向两侧遍历**。每侧 $\frac{n}{2}$ 个点，每个点可以进行 $\frac{n}{4}$ 次操作。

显然，如果一个点**当前不能被改变**，那我们能通过**改变它一侧的点**，使它变成**可以被改变状态**。其实这就是一个递归求解的过程。

* 对于中点左侧的点，如果不能被改变，选择**向左递归**。
* 对于中点右侧的点，如果不能被改变，选择**向右递归**。

这样我们先钦定中间两个点，使其变成一样的（最多需要 $\frac{n}{2}$ 次）。然后向左右分别求解（还剩 $\frac{n}{2}-1$ 个点），最坏情况是 $\frac{\frac{n}{2}(\frac{n}{2}-1)}{2} \times 2$ 次，加上最开始钦定时的 $\frac{n}{2}$ 次，刚刚好（应该卡不到吧）。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e3+5;
int n,a[N],r,ans,op[2000005],limit;
inline void change(int x,int o)
{
	if(x==1||x==n||a[x-1]!=a[x+1]) return a[x]^=1,op[++ans]=x,void(0);
	if(o) change(x-1,o),a[x]^=1,op[++ans]=x;
	else change(x+1,o),a[x]^=1,op[++ans]=x;
}
int main()
{
	scanf("%d%d",&n,&limit);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int l=n>>1,r=l+1;
	if(a[l]!=a[r]) change(l,1);
	l--,r++;
	while(l>=1) a[l]!=a[l+1]?change(l,1),l--:l--;
	while(r<=n) a[r]!=a[r-1]?change(r,0),r++:r++;
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++) printf("%d ",op[i]);
	return 0;
}
```

---

## 作者：block_in_mc (赞：12)

## 题目大意

对于一个长度为 $n$ 的 $01$ 串 $s$，你可以对其进行最多 $r$ 次操作，对于每次操作，你可以选择一个下标 $p$ 满足 $p=1$，$p=n$，$s_{p-1}\not=s_{p+1}$ 中的至少一个，将 $s_p$ 反转。输出操作方案。

## 解题思路

这里以 $s=\texttt{0010}$ 为例，我们发现：

* 依次选择 $p=2,3$ 进行操作，$s$ 变为 $\texttt{0100}$；
* 依次选择 $p=1,2$ 进行操作，$s$ 变为 $\texttt{1000}$；
* 选择 $p=1$ 进行操作，$s$ 变为 $\texttt{0000}$。

不难发现，前两步实际上让 $s$ 中的 $\texttt{1}$ 每次左移一步。形式化的说，先考虑将每一项都变成 $\texttt{0}$ 的情况，若 $s_x=1$ 且 $s$ 的前 $x-1$ 项均为 $\texttt{0}$，：

- 若 $s_{x+1}=\texttt{0}$，可以依次选择 $p=x-1,x$ 进行操作，将 $s_{x-1}$ 变为 $\texttt{1}$ 且 $s_x$ 变为 $\texttt{0}$，重复此操作直到将 $\texttt{1}$ 移至最左侧，并取 $p=1$ 进行操作；
- 若 $s_{x+1}=\texttt{1}$，可以直接选择 $p=x$ 进行操作将 $s_x$ 变为 $\texttt{0}$。

若将每一项都变成 $\texttt{0}$，从左往右依次将每个 $\texttt{1}$ 移至最左侧并反转；否则将每个 $\texttt{0}$ 移至最左侧并反转，取其操作次数中的较小值，可在 $2\times10^6$ 次内完成操作，当 $s=\texttt{01010101}\cdots$ 时取到最大值。

考虑如何优化。事实上，对于 $s=\texttt{0000010}$，我们将最右侧的 $\texttt{1}$ 移至最左侧消耗了大量的操作数，但也可以将 $\texttt{1}$ 移到最右侧消除。因此，我们可以将数组分为两半，反转右侧后分别考虑将所有的 $\texttt{0}$ 或 $\texttt{1}$ 移至最左侧所需的次数及方案，可在 $10^6$ 次内完成操作，当 $s=\texttt{01010101}\cdots$ 时取到最大值。

但是考虑 $s=\texttt{001100}$，分为两半 $\texttt{001|100}$，这时左侧的最后一个数可以直接反转，而不能移至最左侧，需要特判。

实现时，注意对于右侧数组反转后的第 $i$ 个数，它实际上是原数组中的第 $n-i+1$ 个数。同时，因为没有实际上修改 $s$，不能判断 $s_{i-1}=s_{i+1}$，而是 $s_{i+1}=\texttt{0}$（或 $\texttt{1}$）来判断能否直接反转。

## AC 代码

赛时实现较为复杂。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, c, ans1, ans0, num[2020], r[1010];
vector<int> res1, res0;
void deal1(int* p, int len, int tp) {
	for (int i = 1; i <= len; i++) {
		if (p[i] == 1) {
			int flag;
			if (tp == 0) flag = (0 != p[i + 1]);
			else flag = (i != len && 0 != p[i + 1]);
			if (i == 1 || flag) {
				ans1++;
				if (tp == 0) res1.push_back(i);
				else res1.push_back(n - i + 1);
			}
			else {
				for (int j = i; j >= 2; j--) {
					ans1 += 2;
					if (tp == 0) {
						res1.push_back(j - 1);
						res1.push_back(j);
					}
					else {
						res1.push_back(n - j + 2);
						res1.push_back(n - j + 1);
					}
				}
				ans1++;
				if (tp == 0) res1.push_back(1);
				else res1.push_back(n);
			}
		}
	}
}
void deal0(int* p, int len, int tp) {
	for (int i = 1; i <= len; i++) {
		if (p[i] == 0) {
			int flag;
			if (tp == 0) flag = (1 != p[i + 1]);
			else flag = (i != len && 1 != p[i + 1]);
			if (i == 1 || flag) {
				ans0++;
				if (tp == 0) res0.push_back(i);
				else res0.push_back(n - i + 1);
			}
			else {
				for (int j = i; j >= 2; j--) {
					ans0 += 2;
					if (tp == 0) {
						res0.push_back(j - 1);
						res0.push_back(j);
					}
					else {
						res0.push_back(n - j + 2);
						res0.push_back(n - j + 1);
					}
				}
				ans0++;
				if (tp == 0) res0.push_back(1);
				else res0.push_back(n);
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	int mid = (1 + n) / 2;
	for (int i = 1; n - i >= mid; i++)
		r[i] = num[n - i + 1];
	deal1(num, mid, 0);
	deal1(r, n - mid, 1);
	deal0(num, mid, 0);
	deal0(r, n - mid, 1);
	if (ans1 < ans0) {
		printf("%d\n", ans1);
		for (int i = 0; i < res1.size(); i++)
			printf("%d ", res1[i]);
	}
	else {
		printf("%d\n", ans0);
		for (int i = 0; i < res0.size(); i++)
			printf("%d ", res0[i]);
	}
	return 0;
}
```

---

## 作者：shuqiang (赞：4)

这是一道模拟题。

以 $a=0111001110110$ 为例，考虑把所有的 $1$ 改成 $0$，可以先从左往右扫一遍，把可以把 $1$ 改成 $0$ 的数全部改一遍，得到 $a=0001000010010$，这个例子告诉我们，可以先把有连续的 $1$ 的序列改成没有连续的 $1$ 的序列。

还是 $a=0001000010010$，考虑将第四个 $1$ 改成 $0$，因为 $a_3 \ne a_5$ 所以还不能改，可以把 $a_3$ 改成 $1$，这样就能把 $a_4$ 改成 $0$ 了，刚才的操作交换了 $a_3$ 和 $a_4$，同理，交换了 $a_2$ 和 $a_3$，$a_1$ 和 $a_2$，最后把 $a_1$ 改成 $0$，就实现了这种效果，遍历所有的 $1$ 进行上述操作，为了减少操作次数，我们可以把接近左边的 $1$ 往左边移动，接近右边的 $1$ 往右边移动。

处理连续的 $1$ 只需要 $1$ 次操作，而不连续的 $1$ 需要很多次操作，处理不连续的 $1$ 显然比处理连续的 $1$ 需要的操作多，所以操作次数最多的情况是 $a=01010101 \cdots$ 则最多操作 $\sum_{i = 1}^{500} (4i-1)+\sum_{i = 1}^{500} (4i-3)=1000000$ 次。刚好能过 $r=10^6$ 的限制，所以不存在无解的情况。

AC 代码:

```cpp
#include<iostream>
#include<vector>

using namespace std;

const int N = 2 * 1e3 + 10;
int n, r;
bool a[N], b = 0, c[N];
vector<int> ans;

void add(int x){
	ans.push_back(x);
	a[x] = !a[x];
}

void get_ans(){
	if(a[1] != b) add(1);
	for(int i = 2; i <= n-1; i++){
		if((a[i] != b) && (a[i-1] == b) && (a[i+1] != b)){
			add(i);
		}
	}
	if(a[n] != b) add(n);
	for(int i = 2; i <= n/2; i++){
		if(a[i] != b){
			for(int j = i; j >= 1; j--){
				if(j == 1) add(1);
				else{
					add(j-1); add(j);
				}
			}
		}
	}
	for(int i = n-1; i >= n/2+1; i--){
		if(a[i] != b){
			for(int j = i; j <= n; j++){
				if(j == n) add(n);
				else{
					add(j+1); add(j);
				}
			}
		}
	}
}

int main(){
	cin >> n >> r;
	for(int i = 1; i <= n; i++){
		cin >> c[i];
		a[i] = c[i];
	}
	get_ans();
	if(ans.size() <= r){
		cout << ans.size() << '\n';
		for(int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';
	}
	else{
		ans.clear();
		b = 1; for(int i = 1; i <= n; i++) a[i] = c[i];
		get_ans();
		cout << ans.size() << '\n';
		for(int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';
	}
	return 0;
}
```

---

## 作者：Milthm (赞：3)

考虑把原序列相邻的两个数进行异或，得到了一个长度为 $n-1$ 的新数组。

然后我们发现，这个 $a_{p-1}\neq a_{p+1}$ 就相当于新数组相邻的两个位置不同。且如果把中间这个位置取反，相当于把相邻的两个位置交换。

因为题目中说 $1$ 和 $n$ 位置可以随便取反，所以我们想到一个思路，即把新数组前一半的 $1$ 往前交换，把后一半往后交换，交换到 $1$ 或者 $n$ 就直接把 $1$ 改成 $0$ 就行了。

时间复杂度 $O(n^2)$，然后这个操作次数应该是 $\frac{n^2}4$ 量级的，不会超过限定次数。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 2005
using namespace std;
int n,r,a[N],f[N],ans[N*N],cnt;
signed main(){
	cin>>n>>r;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<n;++i)f[i]=a[i]^a[i+1];--n;
	for(int i=1;i<=n/2;++i){
		if(f[i])for(int j=i;j>=1;--j)ans[++cnt]=j;
	}
	for(int i=n;i>n/2;--i){
		if(f[i])for(int j=i+1;j<=n+1;++j)ans[++cnt]=j;
	}
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;++i)cout<<ans[i]<<" ";
	return 0;
}
```
无需畏惧，黎明已然降临！

---

## 作者：Big_Dinosaur (赞：2)

绿还是有的吧。

首先，有一个算法叫 `Meet in the middle`，需要借鉴思路。

`Meet in the middle` 指将搜索一分为二，两边分别搜索，最终合并。本题也可以将数组一分为二，两边分别计算最后合并。

如何计算单独一边的答案？

以前一半 $1\sim \lfloor\frac n 2\rfloor$ 操作为例，右侧只需反过来。

枚举 $i$：
- 若 $a_i=a_{i-1}$，无需操作。
- 若 $a_i\ne a_{i-1}$，且 $a_i$ 可以直接操作，直接操作。
- 若 $a_i\ne a_{i-1}$，且 $a_i$ 不可以直接操作，有点麻烦。如果对 $a_1$ 操作去翻后，$a_2$ 也可以取反。以此类推，可以将 $a_1\sim a_{i-1}$ 全部取反，此时 $a_i=a_{i-1}$。

用相似做法处理后半段，方法类似。

最后，前半段相等，后半段相等，但整个串不一定相等。此时在对前半段或后半段以此取反即可。

此时极限数据为 $a$ 数组 $01$ 交替出现。但经测试。次数不会超过 $10^6$。

__   _

代码如下：
```cpp
#include"bits/stdc++.h"
#define int long long
#define ri register int
using namespace std;
const int p=1e9+7;
namespace Dick{
	inline int r(){
		int x=1,y=0;char c=getchar();
		while(c<'0'||c>'9'){if(c=='-')x=-1;c=getchar();}
		while(c>='0'&&c<='9'){y=(y<<1)+(y<<3)+(c^48);c=getchar();}
		return y*x;
	}
	inline void bdc(int i){
		if(i==0)return;if(i<0){putchar('-');i=-i;}
		bdc(i/10);putchar(48^(i%10));
	}
	inline void ww(int mn){if(mn!=0)bdc(mn);else putchar('0');putchar(' ');}
	inline void w(int mn){if(mn!=0)bdc(mn);else putchar('0');}
	inline void wln(int mn){if(mn!=0)bdc(mn);else putchar('0');putchar('\n');}
}
using namespace Dick;
namespace qwq{
	int n,cnt,a[2333],p;
	vector<int>ve;
	inline void TMN(){
		n=r();cnt=r();
		for(ri i=1;i<=n;++i)a[i]=r();
		int mid=n>>1;
		for(ri i=2;i<=mid;++i){
			if(a[i]!=a[i-1]){
				if(a[i+1]==a[i])ve.push_back(i),a[i]=!a[i];
				else{
					for(ri j=i-1;j;--j)a[j]=!a[j],ve.push_back(j);
				}
			}
		}
		for(ri i=n-1;i>mid;--i){
			if(a[i]!=a[i+1]){
				if(a[i-1]==a[i])ve.push_back(i),a[i]=!a[i];
				else{
					for(ri j=i+1;j<=n;++j)a[j]=!a[j],ve.push_back(j);
				}
			}
		}
		if(a[1]!=a[n])for(ri i=mid;i;--i)ve.push_back(i),a[i]=!a[i];
		wln(ve.size());
		for(auto i:ve)ww(i);
	}
}
signed main(){
	qwq::TMN();
}
```

---

## 作者：66xyyd (赞：2)

## 题意

给出来长度为 $n$ 的 $01$ 序列 $a$ 和一个数 $r$，每一次操作可以把 $a$ 中的一个数取反，条件是这个数左右两侧的数不同或这个数在 $a$ 的最左侧/最右侧。要求在 $r$ 次操作内把 $a$ 变成全 $0$ 或全 $1$ 序列并输出方案。

~~题目说得很清楚了，看不懂自己去看就行。~~

## 题解

### $r=2 \times 10^6$ 的做法
先考虑前两档部分分。

1. 首先假设我们要把 $a$ 变成全 $x$ 序列。这样对于 $x=0$ 或 $x=1$ 分别求即可。

2. 枚举一个下标 $1<i<n$，假设下标 $1,2,3,\cdots,i-1$ 上的值已经都是 $x$ 了。（注意边界情况，$a_1$ 不是 $x$ 的话就把 $a_1$ 变成 $x$，$a_n$ 同理。）

3. 如果 $a_i=x$，直接跳过；否则启动分讨。

- 如果 $a_{i+1}$ 不是 $x$ 的话，直接把 $a_i$ 变成 $x$ 即可。

- 否则我们没办法直接改动 $a_{i}$ 的值。考虑直接改动 $a_{i-1}$ 的值，然后再对 $a_{i}$ 进行改动。这下我们发现 $a_i$ 的值变成了 $x$，而 $a_{i-1}$ 的值就不是 $x$ 了。对 $a_{i-1},a_{i-2},\cdots,a_{1}$ 重复类似的操作，然后直接把 $a_1$ 的值变为 $x$ 即可。（还有一种类似的操作方法，见补充）

举个例子。
```
0 1 1 0 1 0
```
假设我们目前枚举的是 $x=0$。

1. $a_1$ 是 $0$，不需要操作；

2. $a_2$ 是 $1$，但是 $a_3$ 也是 $1$，直接把 $a_2$ 变成 $0$；

3. $a_3$ 是 $1$，$a_4$ 是 $0$。这个时候要按照分类讨论中的改动方法。也就是依次改动 $a_2,a_3,a_1,a_2,a_1$，这样 $a_3$ 就变成了 $0$。

4. $a_4$ 是 $0$，不需要操作；

5. $a_5$ 是 $1$，$a_6$ 是 $0$，依次改动 $a_4,a_5,a_3,a_4,a_2,a_3,a_1,a_2,a_1$，这样 $a_5$ 就变成了 $0$。

6. $a_6$ 是 $0$，不需要操作。

~~喜提五十分~~

这里是具体实现（关键部分）：
```cpp
#include<iostream>
#include<vector>
using namespace std;
int a[20001],b[20001];
int n,r;
bool check(int x){
	return (x==1 || x==n) || (b[x-1]!=b[x+1]);
}
pair<bool,vector<int>> tryr(int x){
	vector<int> ans;
	for(int i=1;i<=n;i++){
		b[i]=a[i];
	}
	if(b[1]!=x){
		ans.push_back(1);
		b[1]=x;
	}
	if(b[n]!=x){
		ans.push_back(n);
		b[n]=x;
	}
	for(int i=2;i<n;i++){
		if(b[i]!=x){
			if(b[i+1]==x){
				for(int j=i;j>1;j--){
					if(!check(j-1)){
						cerr << "cyq is wrong!\n";
						exit(-1);
					}
					ans.push_back(j-1);
					b[j-1]=!b[j-1];
					if(!check(j)){
						cerr << "cyq is wrong!\n";
						exit(-1);
					}
					ans.push_back(j);
					b[j]=!b[j];
//					for(int j=1;j<=n;j++){
//						cout << b[i] << ' ';
//					}
//					cout << '\n';
				}
//				cout << '\n' << '\n';
				ans.push_back(1);
				b[1]=!b[1];
			} else{
				ans.push_back(i);
				b[i]=x;
			}
			
			
		}
		
	}
	return make_pair(int(ans.size())<=r,ans);
}
```

### $r=10^6$ 的做法

我们发现刚才举的例子中 $a_5$ 的步数太长，本来可以依次改动 $a_6,a_5,a_6$ 通过把非 $x$ 的值移动到最右侧解决的。

这启发我们把 $a$ 序列分成两个尽可能相等的部分，即 $a_1,a_2,\cdots,a_{\lfloor\frac{n}{2}\rfloor}$ 和 $a_{\lfloor\frac{n}{2}\rfloor +1},a_{\lfloor\frac{n}{2}\rfloor +2},\cdots,a_{n}$，左半部分的改动交给 $a_1$，右半部分的改动交给 $a_n$。左半部分的做法已经说过，右半部分的做法和左半部分是类似的（把非 $x$ 的下标向左移动的逻辑改成向右移动即可）。

于是我们就写出了满分代码（仅展示关键函数）：
```cpp
pair<bool,vector<int>> tryr(int x){
	vector<int> ans;
	for(int i=1;i<=n;i++){
		b[i]=a[i];
	}
	if(b[1]!=x){
		ans.push_back(1);
		b[1]=x;
	}
	if(b[n]!=x){
		ans.push_back(n);
		b[n]=x;
	}
	for(int i=2;i<=n/2;i++){
		if(b[i]!=x){
			if(b[i+1]==x){
				for(int j=i;j>1;j--){
					if(!check(j-1)){
						cerr << "cyq is wrong!\n";
						exit(-1);
					}
					ans.push_back(j-1);
					b[j-1]=!b[j-1];
					if(!check(j)){
						cerr << "cyq is wrong!\n";
						exit(-1);
					}
					ans.push_back(j);
					b[j]=!b[j];
//					for(int j=1;j<=n;j++){
//						cout << b[i] << ' ';
//					}
//					cout << '\n';
				}
//				cout << '\n' << '\n';
				ans.push_back(1);
				b[1]=!b[1];
			} else{
				ans.push_back(i);
				b[i]=x;
			}
			
			
		}
		
	}
	for(int i=n;i>n/2;i--){
		if(b[i]!=x){
			if(b[i-1]==x){
				for(int j=i;j<n;j++){
					if(!check(j+1)){
						cerr << "cyq is wrong!\n";
						exit(-1);
					}
					ans.push_back(j+1);
					b[j+1]=!b[j+1];
					if(!check(j)){
						cerr << "cyq is wrong!\n";
						exit(-1);
					}
					ans.push_back(j);
					b[j]=!b[j];
//					for(int j=1;j<=n;j++){
//						cout << b[i] << ' ';
//					}
//					cout << '\n';
				}
//				cout << '\n' << '\n';
				ans.push_back(n);
				b[n]=!b[n];
			} else{
				ans.push_back(i);
				b[i]=x;
			}
			
			
		}
		
	}
	return make_pair(int(ans.size())<=r,ans);
}
```
## 补充

1. 另外一种做法是：对于 $a_i \neq x$ 且 $a_{i+1}=x$ 的情况，依次改动 $a_{i-1},a{i-2},\cdots,a_{1}$，然后再依次改动 $a_{i},a{i-1},\cdots,a_{1}$。折半的优化和这篇题解中的思路是一致的。这个方法是我机房同学想出来的，这里是他的[提交记录](https://www.luogu.com.cn/record/171835595)。

2. 实在想不出来右半部分做法的可以看这里。我们从右往左扫过序列 $a$（在 $a_{\lfloor\frac{n}{2}\rfloor}$ 处停下）：

- $a_i=x$ 的情况也是直接跳过，$a_i \neq x$ 但 $a_{i-1} \neq x$ 的情况直接改动 $a_i$，这里和处理左半部分的思路是一致的（注意因为枚举顺序不同，下标从 $i+1$ 变成了 $i-1$）。

- 对于 $a_i \neq x$ 并且 $a_{i-1}=x$ 的情况，与左半部分类似地注意到只需要改动 $a_{i+1},a_{i}$ 即可让非 $x$ 的部分右移一位，依次改动 $a_{i+1},a_{i},a_{i+2},a_{i+1},\cdots,a_{n},a_{n-1},a_{n}$ 即可。

---

## 作者：zh1221_qwq (赞：1)

我们先会有一个很正常的想法，就是我们先钦定全变成 $0$ 或 $1$ 然后遇到不匹配的就判断是否能改，不能的话就判断能否改动前一个值从而使得能改，用一个循环实现。但这样改的次数最多是会超过 $1\times 10^6$ 的。

我们尝试优化这个过程，首先我们可以让 $0$、$1$ 中较少的那个数变成较多的那个数。然后将序列分成两半，左边的那一半往左改，右边的往右改。这样的话极限数据是 $0$、$1$ 交替的串，操作次数正好是 $1\times 10^6$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,a[2005],ans[2000005],cnt,tot,b;
int main(){
	cin>>n>>r;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i])cnt++;
	}
	if(cnt>=n/2)b=1;
	for(int i=n/2;i>=1;i--){
		if(a[i]!=b){
			int j=i;
			while(a[j-1]==a[j+1]&&j!=1)j--;
			while(j<=i)a[j]^=1,ans[++tot]=j++;
		}
	}
	for(int i=n/2+1;i<=n;i++){
		if(a[i]!=b){
			int j=i;
			while(a[j-1]==a[j+1]&&j!=n)j++;
			while(j>=i)a[j]^=1,ans[++tot]=j--;
		}
	}
	if(tot>r){
		cout<<-1;
		return 0;
	}
	cout<<tot<<"\n";
	for(int i=1;i<=tot;i++)cout<<ans[i]<<" ";
	return 0;
}

```

---

## 作者：M4rkSELby (赞：1)

简易构造题。在此先膜拜一下巨佬 zyt。

先随便写出一个序列 $a$，比如下面这个：

$0 0 0 1 1 0 1 1$。

考虑对于这个序列如何将其变成全 $0$ 或全 $1$。首先前面三个都是 $0$，先不动它们。然后的 $a_4$ 变成了 $1$。但此时的 $a_3 \ne a_5$，可以将其改成 $1$。继续往下，$a_5$ 又是 $1$。由于 $a_4$ 已经被改成了 $0$，$a_4=a_6$，不能对其进行修改。但仔细观察，此时我们可以掉过头去，把前面的所有 $0$ 都改成 $1$。接下来遇到 $a_6=0$，我们又可以把前面的所有 $1$ 都改成 $0$。最后的两个 $1$ 都可以直接修改为 $0$。

综上，我们修改的基本思路为：

- 若当前 $a_i=a_{i-1}$，不进行修改。
- 否则若 $a_{i-1} \ne a_{i+1}$，直接修改 $a_i$ 使其等于 $a_{i-1}$。
- 否则由于此时我们保证了任意时刻 $i$ 都有 $a_1$ 到 $a_{i-1}$ 的所有数字全部一致，可以直接从后往前把 $a_1$ 到 $a_{i-1}$ 都修改为 $a_i$。

这样的算法保证了对于任意时刻 $i$ 都有 $a_1$ 到 $a_i$ 的所有数字全部一致，故具有正确性。

然而朴素的构造修改次数会在形如 $1 0 1 0 1 0 1 0$ 的序列时达到最大，设序列长度为 $n$，此时修改次数达到 $1$ 到 $n-1$ 的和。当 $n=2\times 10^3$ 时会超出 $r=10^6$ 的限制。因此该算法需要优化。

考虑使用折半搜索的思想。先将序列劈成 $2$ 段，对 $a_1$ 到 $a_{n/2}$ 进行修改操作，再对 $a_{n/2+1}$ 到 $a_n$ 进行修改操作。若修改后 $a_{n/2} \ne a_{n/2+1}$，我们再统一将 $a_{n/2+1}$ 到 $a_n$ 全部修改为 $a_{n/2}$。正确性应该比较显然，读者可以自行模拟一下。此时最多修改次数为 $(\frac{n}{2}-1) \times \frac{n}{2} + \frac{n}{2}$，刚刚好为 $10^6$。经过这样的优化，可以通过此题。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define mk make_pair
#define pii pair<int,int>
#define mod 1000000007
using namespace std;
il int rd(){
	int sum=0,p=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')p=-1;ch=getchar();}
	while(isdigit(ch)){sum=sum*10+(ch-'0');ch=getchar();}
	return sum*p;
}
il void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10+48);
}
const int JYAAKIOI=1145141919810;
int n,r,m,a[100086];
vector<int>v;
signed main(){
	//freopen("jytwcsnm.in","r",stdin);
	//freopen("jytwcsnm.out","w",stdout);
	n=rd();r=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=2;i<=n/2;++i){
		if(a[i]==a[i-1])continue;
		if(a[i-1]!=a[i+1]){
			a[i]=a[i-1];
			v.push_back(i);
			continue;
		}
		for(int j=i-1;j>=1;--j){
			a[j]=1-a[j];
			v.push_back(j);
		}
	}
	for(int i=n-1;i>=n/2+1;--i){
		if(a[i]==a[i+1])continue;
		if(a[i-1]!=a[i+1]){
			a[i]=a[i+1];
			v.push_back(i);
			continue;
		}
		for(int j=i+1;j<=n;++j){
			a[j]=1-a[j];
			v.push_back(j);
		}
	}
	if(a[n/2]!=a[n/2+1]){
		for(int j=n/2+1;j<=n;++j){
			a[j]=1-a[j];
			v.push_back(j);
		}
	}
	wr(v.size()),putchar('\n');
	for(auto vv:v)wr(vv),putchar(' ');
	return 0;
}
```

---

## 作者：Reply_ (赞：1)

# P10854题解
### 题意
在 $a$ 数组中，对于一些拥有特定特性的数值我们可以将其反转，直至最后的 $a$ 数组变为全是 $0$ 或全是 $1$。
### 解法
提供一种好想且实现简单的写法。对于一个值，若符合要求且需要修改，直接修改即可，若不符合要求且需要修改，那么须修改其左边或右边的值即可。

那么如何抉择呢？

首先，加入是从左往右进行调整显然是不优的，看这么一组样例：

$0,1,1,0,1$ 

若要从左往右调整为 $0$ ，修改第二项以后就变成

$0,0,1,0,1$

对于数组第三项若要更新，又要修改第二项的值，等价于白白多进行了一次数组第二项修改，出现冗余

如何优化呢？

无独有偶，正着修改不行，反着修改亦不行，那么考虑从中间修改，设中间值序号为 $mid$ ，这时的数组被分成两半，其中的 $1$ 至 $mid$ 中，从右向左进行更新，可以证明必然在不符合条件的情况下，修改左边和修改右边的数值中，是修改左边的更优，反之亦然。

代码细节如下，结合注释理解


```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
#define F(i,a,b) for(int i = (a);i<=(b);i++)
using namespace std;
inline int read(){R int x=0,t=1;R char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') t=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*t;}
const int N=2e3+10;
int w,n,a[N],r;
vector<int>ans;//存储答案
void dfs1(int t)
{
	if(t==1){
		ans.push_back(1);
		a[t]=1-a[t];//如果是1就直接更改 
		return;
	}
	if(a[t-1]==a[t+1]){
		dfs1(t-1);//右半部分改左边更优 
		a[t]=1-a[t];
		ans.push_back(t);
	}
	else{
		ans.push_back(t);
		a[t]=1-a[t];
		return;
	}
}
void dfs2(int t)
{
	if(t==n){
		ans.push_back(n);
		a[t]=1-a[t];//如果是n就直接更改 
		return;
	}
	if(a[t-1]==a[t+1]){
		dfs2(t+1);//右半部分改右边更优 
		a[t]=1-a[t];
		ans.push_back(t);
	}
	else{
		ans.push_back(t);
		a[t]=1-a[t];
		return;
	}
}
signed main()
{
	n=read(),r=read();
	for(int i = 1;i<=n;i++) 
		a[i]=read();
	w=a[(n+1)/2];//w是我们预期更改成的数值
	//将w设为最中间的值可以方便些 
	for(int i = n/2;i>=1;i--){//这里处理左半边部分的情况 
		if(a[i]!=w){
			dfs1(i);
		}
	} 
	for(int i = (n+1)/2+1;i<=n;i++){//这里处理右半边部分的情况 
		if(a[i]!=w){
			dfs2(i);
		}
	}
	cout << ans.size() << '\n';//输出答案 
	for(int i = 0;i<ans.size();i++) cout << ans[i] << ' ';
	return 0;
}

```

---

## 作者：Crsuh2er0 (赞：1)

读完本题题面，使用样例数据进行一些试探后得到：
- $0$ 或 $1$ 的段不能合并。例如 $0110110$ 中两段 $1$ 无法合并。
- 要将中间的一块 $1$ 清空为 $0$，我们可以把它往左边或右边移动到边缘再清除。
- 连续的一段可以用 $O(段长)$ 次操作变为只保留左端点或右端点的长度为 $1$ 的段。
- 进一步地，想到根据每一段 $1$ 的左右端下标分别距离 $1$ 和 $n$ 的距离来决定从左边消除还是从右边消除。
- 最终，距离 $1$ 近的可以移到左端，距离 $n$ 近的可以移到右端。

进一步探究此方案的最坏情况，发现是 $010101 \cdots 0101$，简单计算可得此时的操作次数刚好是 $10^6$ 次。

以上做法将整个序列 $a$ 清空为 $0$，其实也可以将整个序列变为 $1$，做法类似。

注意本题**不需要最小化 $m$**，只需要给出一种规定操作数内的方案，所以我们只写一种做法就好。若要最小化 $m$，本题难度将再上升一个等级。

---

## 作者：thh_loser (赞：1)

# P10854 【MX-X2-T3】「Cfz Round 4」Ninelie 题解

[题目链接](https://www.luogu.com.cn/problem/P10854)

## 题意

给定一个长为 $n$ 的 $01$ 序列 $a_1, \ldots, a_n$ 以及一个正整数 $r$。问能否使用给定的操作将序列中的数变为一样的数。

具体操作方式：每次操作需选定一个下标 $i$，满足 $i$ 为 $1$ 或 $n$ 或 $a_{i-1}\neq a_{i+1}$，然后将 $a_i$ 翻转（即将 $0$ 变为 $1$，将 $1$ 变为 $0$）。

## 思路

仔细理解题意便可注意到从两侧开始转是最优的，因为转中间的一定会留下一个数无法转换，且显然每次在边上将一段连续的全部转换最优。

每次转换将两段挨着的不同段合并，代价为一端的长度，合并后代价为两段长度相加。

看到这有没有想起一道经典题目——[合并果子](https://www.luogu.com.cn/problem/P1090)

而且甚至简单于那道题的是这道题只有两端需要维护，每次取两端中代价小的那一边，更新，直到将序列覆盖。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,a[2010];
int st[3100010],cnt;
int le,re;
int main(){
	cin>>n>>r;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	le=1;
	re=n;
	while(a[le]==a[1])le++; 
	le--;
	while(a[re]==a[n])re--;//初始化 
	re++;
	while(!(le>=n||re<=1)){//直到覆盖整个区间 
		if(le-1<n-re){//左端更优 
			for(int i=le;i>=1;i--){a[i]=(a[i]?0:1);st[++cnt]=i;}//统计答案 
			int k1=le+1,k;
			for(k=k1;k<=n&&a[k]==a[k1];)k++;
			le=k-1;
		}
		else{//右端更优 
			for(int i=re;i<=n;i++){a[i]=(a[i]?0:1);st[++cnt]=i;}
			int k1=re-1,k;
			for(k=k1;k>=1&&a[k]==a[k1];)k--;
			re=k+1;
		}
//		for(int i=1;i<=n;i++){
//			cout<<a[i]<<" ";
//		}
//		cout<<endl;
		if(cnt>r){//判断 
			cout<<"-1";
			return 0;
		}
	}
	if(cnt>r){
		cout<<"-1";
		return 0;
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++)cout<<st[i]<<" ";
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

简单思维题。

### 思路

读完题稍加思考就可以得出几个显而易见的结论：每次操作只能操作于每个极长连通块的两个端点；消除一个极长连通块等价于每次在两个端点附近进行一对操作使其向一侧平移，最终平移出整个序列；若一个极长连通块一侧存在与它值相等的极长连通块，那么这个当前的连通块必须在这个连通块移出后才能从相应的一侧移出。

对这个做法的次数进行分析，发现其操作次数是 $\frac{n^2}{2}$ 级别的，只能通过 $r=2\times 10^6$ 的数据。

考虑进行优化，发现可以对其从序列中间进行分割，每个极长连通块都往自己更近的一边移动，可以通过。

update：朴素做法复杂度存在问题，感谢 @[guojiahong](https://www.luogu.com.cn/user/1083200) 指出问题。

---

## 作者：xuan_gong_dong (赞：0)

## 题面

[P10854 【MX-X2-T3】「Cfz Round 4」Ninelie](https://www.luogu.com.cn/problem/P10854)

## 分析

### $50$ 分
注意到 $r$ 很大，考虑从左向右依次枚举每一个 $1$，若可以直接消去则消去，否则将 $1$ 挪到第一位，再消去，注意每一个 $1$ 左边都全是 $0$ ，曾经有 $1$ 的都会在之前移动消去掉。

再考虑如何移动。

- 如果当前的 $1$ 右边为 $0$，直接翻转前一个点，再反转该点，然后前一个点再进行上述操作。
- 如果当前的 $1$ 右边为 $1$, 直接消去即可。

注意可以直接将编号为 $1$ 和 $n$ 的点初始强制变为 $0$（初始为 $0$ 不操作）。

### $100$ 分
上述情况可能会超过 $r= 2 \times 10^6$ 的限制，所以加一个小优化：处于序列前一半的向左移动，后一半向右移动，移动方法同理。

复杂度 $O(n^2)$ 直接拿下！
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r;
int ans[2000010];
int a[20010];
int main() {
	scanf("%d%d",&n,&r);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
	}
	int cnt=0;
	if(a[1]==1) {
		ans[++cnt]=1;
	}
	if(a[n]==1) {
		a[n]=0;
		ans[++cnt]=n;
	}
	for(int i=2; i<n/2; i++) {
		if(a[i]==1) {
			int id=i-1;
			if(a[i+1]==1) {
				ans[++cnt]=i;
				a[i]^=1;
			} else {
				ans[++cnt]=i-1;
				a[i-1]^=1;
				ans[++cnt]=i;
				a[i]^=1;
				while(id!=1) {
					ans[++cnt]=id-1;
					a[id-1]^=1;
					ans[++cnt]=id;
					a[id]^=1;
					id--;
				}
				ans[++cnt]=id;
				a[id]^=1;

			}
		}
	}
	for(int i=n-1; i>=n/2; i--) {
		if(a[i]==1) {
			int id=i+1;
			if(a[i-1]==1) {
				ans[++cnt]=i;
			} else {
				ans[++cnt]=i+1;
				ans[++cnt]=i;
				while(id!=n) {
					ans[++cnt]=id+1;
					ans[++cnt]=id;
					id++;
				}
				ans[++cnt]=id;

			}
		}
	}
	printf("%d\n",cnt);
	for(int i=1; i<=cnt; i++) {
		printf("%d ",ans[i]);
	}
//	for(int i=1;i<=n;i++)cout<<a[i];
	return 0;
}

```

---

## 作者：Your_Name (赞：0)

## 题意
给一个只由 $0$ 和 $1$ 组成的序列，对于一个下标 $p$，满足 $p$ 为 $1$ 或 $n$ 或 $a_{p-1}\neq a_{p+1}$，就能将 $a_p$ 翻转（即将 $0$ 变为 $1$，将 $1$ 变为 $0$），问怎么样才能把这个序列变成全 $0$ 或全 $1$， 输出选出的下标组成的序列。
## 思路
**（一）** 因为需要变成全 $1$ 或全 $0$，所以只要看是变成全 $0$ 还是变成全 $1$ 的花费次数少，输出少的即可。

**（二）注：这里为了叙述方便，我们以变成全 $0$ 举例。**

首先，假设我们的序列长这样：
* 010

我们来看看这个怎么操作。

* 010 我们操作 $1$
* 110 我们操作 $2$
* 100 我们操作 $1$
* 000

（记住这个`1,2,1`，后面代码里用了）

 _太神奇了！_$1$ 号点竟然把我们的 $1$“吃了”。

由此我们可以看出只有左右端点的反转没有限制条件，所以可以想到把所有 $1$ 都放到端点清除。

**（三）** 可怎么把中间的 $1$ 放到端点呢？

我们可以观察下面的例子：
* 00010 我们操作 $3$;
* 00110 我们操作 $4$;
* 00100

你发现了什么？
是不是我们的 $1$ 跑到他的左边一个位置去了！

所以我们可以**重复这个操作**，把所有 $1$ 都移动到端点消除。

你可能会问：万一它移动的路径上有别的 $1$ 怎么办？

其实没有这个问题，因为我们处理每一个的顺序只要**从两端到中间**就行，这样的话就可以保证它移动的路径上没有别的 $1$。

又因为如果每个 $1$ 都是到一个端点的话有可能会超出 $r$ 的范围，所以我们直接把整个序列劈成两半，左边 $1$ 去左边端点，右边 $1$ 去右边端点，可以证明一定不会有 $-1$ 的情况，且总操作次数一点不会大于 $r$。

变成全 $1$ 同理，我就不赘述了。

**（四）** 到这还没完，你可以看看下面这种情况。
* 00011000

按我们刚刚说的分法，我们是不是要把它分成这个样子：
* 0001|1000

然后把 $4$ 位置上的 $1$ 调到最左边，把 $5$ 位置上的 $1$ 调到最右边。
可是我们用肉眼也看得出，左边这个 $1$ 完全可以直接改，没必要移动。

因此这是我们要特判的一种情况。

接着，因为我们操作的顺序已经保证了从它的移动路径上没有别的 $1$，那端点本身呢？

因此，当端点本身就不满足我们的条件时，还需要直接改一下才行。不然每次到端点的时候还要分类。

## AC Code
注释写的挺详细的，看不懂上面的可以瞅一眼。

提一嘴，注释里的全 $0$，全 $1$ 是变成全 $0$，变成全 $1$ 的意思。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int n, a[N], b[N], r;//a是变全0用的数组，b是变全1用的数组
vector<int> ans1, ans2;//ans1是变全0用的，ans2是变全1用的存操作数组
void sl(int x)//全0左边
{
    if (x == 2)
    {
        a[x] ^= 1;
        ans1.push_back(1);
        ans1.push_back(2);
        ans1.push_back(1);
        //到了端点后的情况，上面写了
        return;
    }
    a[x - 1] ^= 1;
    a[x] ^= 1;//直接修改
    ans1.push_back(x - 1), ans1.push_back(x);//加入答案
    sl(x - 1);//往前处理
}
void sr(int x)//全0右边
{
    if (x == n - 1)
    {
        a[x] ^= 1;
        ans1.push_back(n);
        ans1.push_back(n - 1);
        ans1.push_back(n);
        //到了端点后的情况，上面写了
        return;
    }
    a[x + 1] ^= 1;
    a[x] ^= 1;//直接修改
    ans1.push_back(x + 1), ans1.push_back(x);//加入答案
    sr(x + 1);//往后处理
}
void sl1(int x)//全1左边
{
    if (x == 2)
    {
        b[x] ^= 1;
        ans2.push_back(1);
        ans2.push_back(2);
        ans2.push_back(1);
        //到了端点后的情况，上面写了
        return;
    }
    b[x - 1] ^= 1;
    b[x] ^= 1;//直接修改
    ans2.push_back(x - 1), ans2.push_back(x);//加入答案
    sl1(x - 1);//往前处理
}
void sr1(int x)//全1右边
{
    if (x == n - 1)
    {
        b[x] ^= 1;
        ans2.push_back(n);
        ans2.push_back(n - 1);
        ans2.push_back(n);
        //到了端点后的情况，上面写了
        return;
    }
    b[x + 1] ^= 1;
    b[x] ^= 1;//直接修改
    ans2.push_back(x + 1), ans2.push_back(x);//加入答案
    sr1(x + 1);//往后处理
}
int main()
{
    cin >> n >> r;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i];//复制一份
    }
    int mid = n / 2;//劈开
    //下面是全0
    if (a[1] != 0)
    {
        a[1] = 0;
        ans1.push_back(1);
    }
    if (a[n] != 0)
    {
        a[n] = 0;
        ans1.push_back(n);
    }//处理端点
    for (int i = 2; i <= mid; i++)
    {
        if (a[i] == 1)
        {
            if (a[i - 1] != a[i + 1])
            {
                a[i] ^= 1;
                ans1.push_back(i);
            }//特判能直接改的情况
            else
                sl(i);
        }
    }//从两端到中间
    for (int i = n - 1; i > mid; i--)
    {
        if (a[i] == 1)
        {
            if (a[i - 1] != a[i + 1])
            {
                a[i] ^= 1;
                ans1.push_back(i);
            }//特判能直接改的情况
            else
                sr(i);
        }
    }//从两端到中间
    //下面是全1
    if (b[1] != 1)
    {
        b[1] = 1;
        ans2.push_back(1);
    }
    if (b[n] != 1)
    {
        b[n] = 1;
        ans2.push_back(n);
    }//处理端点
    for (int i = 2; i <= mid; i++)
    {
        if (b[i] == 0)
        {
            if (b[i - 1] != b[i + 1])
            {
                b[i] ^= 1;
                ans2.push_back(i);
            }//特判能直接改的情况
            else
                sl1(i);
        }
    }//从两端到中间
    for (int i = n - 1; i > mid; i--)
    {
        if (b[i] == 0)
        {
            if (b[i - 1] != b[i + 1])
            {
                b[i] ^= 1;
                ans2.push_back(i);
            }//特判能直接改的情况
            else
                sr1(i);
        }
    }//从两端到中间
    if (ans1.size() < ans2.size())
    {
        // cout <<"全0"<<' ';
        cout << ans1.size() << endl;
        for (auto i : ans1)
        {
            cout << i << ' ';
        }
    }
    else
    {
        // cout <<"全1"<<' ';
        cout << ans2.size() << endl;
        for (auto i : ans2)
        {
            cout << i << ' ';
        }
    }//输出小的
    return 0;
}
```
这么看还是挺好写的，注意一下复制相同代码时要改些什么就行。

**完结撒花！**

---

## 作者：firstlight (赞：0)

# 解法描述：

## 初始想法：

观察 $a=001000$ 这样一个序列，我们可以发现操作序列 $op=2,3,1,2,1$ 是可行的。

而对于 $a=000100$ 这样一个序列，操作序列 $op=5,4,6,5,6$ 要优于操作序列 $op=3,4,2,3,1,2,1$。

所以对于序列 $a$ 中的任意一个 $1$，我们可以看作将这个 $1$ 向左或向右移动至头尾后再消除。设这个 $1$ 的下标为 $i$。当 $i=1$ 或 $i=n$ 时，这样的消除的代价为 1；当 $1\lt i \lt n$ 时，这样的移动的代价为 2。

所以对于任意一个序列，我们均可以使用这样的方式将这个序列变成全部为 $0$ 的状态，计算状态时将序列以中点分为两段，分别向两端移动并消除即可。注意一个 $1$ 再移动前需要保证在他之前的所有 $1$ 已经被完全消除。

我们可以序列中的所有 $1$ 的位置用一个数组记录下来，如果 $1$ 在序列的右半段，则将其赋成其相反数。之后将这一数组排序即可满足合法的操作顺序，之后进行转化后即可输出操作序列。

## 进行优化：

但这时有两种情况并不能以简单的这样的方式做到最简：

1. 序列中的 $1$ 的数量大于 $0$ 的数量时。
2. 初始序列中存在若干连续的 $1$ 时。

对于情况 1，我们可以直接将 $0$ 与 $1$ 互换，这样等价于在原序列上对 $0$ 进行操作。

对于情况 2，我们可以在记录排序前将所有的连续的 $1$ 消除为单独的一些 $1$ 并单独记录代价。

这样处理后，操作复杂度最大的情况为 $n=2000$ 时，$0/1$ 交替出现的序列，此时需要的代价为 1000000，所以对于所有的情况均有解，没有需输出 $-1$ 的情况。

# code:
赛时代码，有些繁琐。
```cpp
// Problem: P10854 【MX-X2-T3】「Cfz Round 4」Ninelie
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10854
// Memory Limit: 512 MB
// Time Limit: 1000 ms

#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 2010;
typedef long long ll;

int n, r;
int a[N];
int ans[N], op[N];

int main()
{
	scanf("%d%d", &n, &r);
	
	int mid = n >> 1;
	
	for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	
	// 记录序列中1和0的数量，如果1的数量大于0的数量，则反转
	int c1 = 0, c2 = 0;
	for(int i = 1; i <= n; i ++ ) 
	{
		if(a[i] == 1) c1 ++ ;
		else c2 ++ ;
	}
	
	if(c1 > c2)
	{
		for(int i = 1; i <= n; i ++ ) 
			a[i] = (a[i] == 1 ? 0 : 1);
	}
	
	int res = 0;
	
	// 清除序列中可清除的1
	for(int i = 2; i < n; i ++ )
		if(a[i] && a[i + 1] && !a[i - 1])
		{
			a[i] = 0;
			ans[ ++ res] = i;
		}
	
	for(int i = n - 1; i >= 2; i -- )
		if(a[i] && a[i - 1] && !a[i + 1])
		{
			a[i] = 0;
			ans[ ++ res] = i;
		}
	
	int cnt = 0; // 记录需操作的 1 并记录代价
	for(int i = 1; i <= n; i ++ )
		if(a[i])
		{
			if(i <= mid) 
			{
				op[ ++ cnt] = i;
				res += 2 * (i - 1) + 1;
			}
			else
			{
				op[ ++ cnt] = -i;
				res += 2 * (n - i) + 1;
			}
		}
	
	printf("%d\n", res);
	
	// 输出操作序列
	for(int i = 1; ans[i]; i ++ ) printf("%d ", ans[i]);
	
	sort(op + 1, op + cnt + 1);
	
	for(int i = 1; i <= cnt; i ++ ) 
	{
		if(op[i] < 0)
		{
			int j = -op[i];
			while(j < n)
			{
				printf("%d %d ", j + 1, j);
				j ++ ;
			}
			printf("%d ", n);
		}
		else 
		{
			int j = op[i];
			while(j > 1)
			{
				printf("%d %d ", j - 1, j);
				j -- ;
			}
			printf("1 ");
		}
	}
	
	return 0;
}
```

---

## 作者：zhoumurui (赞：0)

### 题面展示

给定一个长为 $n$ 的 $01$ 序列 $a_1, \ldots, a_n$ 以及一个正整数 $r$。

你可以对序列 $a$ 进行操作。每次操作需选定一个下标 $p$，满足 $p$ 为 $1$ 或 $n$ 或 $a_{p-1}\neq a_{p+1}$，然后将 $a_p$ 翻转（即将 $0$ 变为 $1$，将 $1$ 变为 $0$）。

请你在 $r$ 次操作内将序列 $a$ 变成全 $0$ 或全 $1$。**不需要最小化操作次数**。如果无法完成，报告无解。

### 解题思路

由于本题中序列长度不长，所以时间比较充裕，完全可以分别进行全 $0$ 和全 $1$ 序列的构造。下面以全 $0$ 的构造为例，全 $1$ 序列的构造类似。

我们最容易想到的铺法是遍历整个序列，发现 $1$ 就想办法把它变成 $0$。

首先因为我们是遍历整个序列的，所以当发现 $1$ 时，这个 $1$ 的前一位显然是 $0$（或者没有前一位）。这样，如果这个 $1$ 在第一位或最后一位，或是它后面还有一个 $1$，就可以把它直接用一步操作消掉。

如果它后面是个 $0$ 呢？我们这样考虑，这个 $1$ 前面显然是没有 $1$ 了，这样序列可能长这样：

`0 0...0 0 1 0 ...`

那么这个 $1$ 左侧的 $0$ 显然可以变成 $1$，然后这个 $1$ 就消掉了。

但是又出现一个 $1$ 啊？没关系，我们发现我们这个步骤刚好是将这个 $1$ 向左挪动了一位。我们只要慢慢地将它挪到第一位，就可以直接消掉它了。

这就是我们的初步思路。

当然，我们发现这样写只能得 $50$ 分。这是因为我们刚才的挪 $1$ 的操作实在是太慢了，没有满足最后一档数据在 $10^6$ 次操作内完成的要求。

生成随机数据可以发现，操作数一般只比 $10^6$ 高一点点，因此我们可能只需要一些简单的优化。

比如，我们刚才把 $1$ 往左挪，但是如果这个 $1$ 的位置比较靠右，可能向右挪会比较方便？

于是我们考虑先遍历一遍把容易消掉的 $1$ 都先消掉，把难以处理的孤立 $1$ 先晾在一边，这样处理过以后就只剩下孤立的 $1$ 了。

把数列从中间劈开，左边的 $1$ 往左挪，右边的 $1$ 往右挪。注意挪动孤立 $1$ 的顺序：左半边左侧先挪右边后挪，右半边右侧先挪左边后挪，否则后面的 $1$ 可能被前面的 $1$ 挡住挪不动，就像这样，假设下面的 $1$ 要往右边挪：

` 1 0 1 0 ...`
我们会发现左边的 $1$ 挪不动了，应该先把右边的 $1$ 挪开，最好是把最右边的 $1$ 先挪到右侧终点。

这样优化后这题就能 AC 了，但是本人菜，无法证明对于长度在 $2000$ 以内的 01 串，下面的代码是否都能在 $10^6$ 步内完成处理。如果有大佬提供证明的话，这里将会补上。

### 核心代码展示

```cpp
int a1[2024],a2[2024],op1[2000005],op2[2000005];
int op3[2000005],op4[2000005];
signed main(){
    cin>>n>>r;
    for (int i=1;i<=n;i++){
        cin>>a1[i];
        a2[i]=a1[i];
    }
    for (int i=1;i<n;i++){
        if (a1[i]==1){
            if (i==1||a1[i+1]==1){
                op1[++cnt1]=i;
                a1[i]=0;
            }
            else{
                continue;
            }
        }
    }
    for (int i=1;i<=n;i++){
        if(2*i-1>=2*(n-i+1)-1){
            continue;
        }
        if (a1[i]==1){
                for (int j=i-1;j>=1;j--){
                    op1[++cnt1]=j;
                    op1[++cnt1]=j+1;
                    a1[j]=1;
                    a1[j+1]=0;
                }
                op1[++cnt1]=1;
                a1[1]=0;
        }
    }
    for (int i=n;i>=1;i--){
        if(2*i-1<2*(n-i+1)-1){
            continue;
        }
        if (a1[i]==1){
                for (int j=i+1;j<=n;j++){
                    op1[++cnt1]=j;
                    op1[++cnt1]=j-1;
                    a1[j]=1;
                    a1[j-1]=0;
                }
                op1[++cnt1]=n;
                a1[n]=0;
        }
    }
    for (int i=1;i<n;i++){
        if (a2[i]==0){
            if (i==1||a2[i+1]==0){
                op2[++cnt2]=i;
                a2[i]=1;
            }
            else{
                continue;
            }
        }
    }for (int i=1;i<=n;i++){
        if(2*i-1>=2*(n-i+1)-1){
            continue;
        }
        if (a2[i]==0){
                for (int j=i-1;j>=1;j--){
                    op2[++cnt2]=j;
                    op2[++cnt2]=j+1;
                    a2[j]=0;
                    a2[j+1]=1;
                }
                op2[++cnt2]=1;
                a2[1]=1;
        }
    }
    for (int i=n;i>=1;i--){
        if(2*i-1<2*(n-i+1)-1){
            continue;
        }
        if (a2[i]==0){
                for (int j=i+1;j<=n;j++){
                    op2[++cnt2]=j;
                    op2[++cnt2]=j-1;
                    a2[j]=0;
                    a2[j-1]=1;
                }
                op2[++cnt2]=n;
                a2[n]=1;
        }
    }
    
    int cnt3=0,cnt4=0;
    for(int i=1;i<=cnt1;i++){
        if (op1[i]==op1[i+1]){
            i++;
            continue;
        }
        op3[++cnt3]=op1[i];
    }
    for(int i=1;i<=cnt2;i++){
        if (op2[i]==op2[i+1]){
            i++;
            continue;
        }
        op4[++cnt4]=op2[i];
    }
    if (cnt3<=cnt4){
        cout<<cnt3<<endl;
        for (int i=1;i<=cnt3;i++){
            cout<<op3[i]<<" ";
        }
        if (cnt3)cout<<endl;
    }
    else{
        cout<<cnt4<<endl;
        for (int i=1;i<=cnt4;i++){
            cout<<op4[i]<<" ";
        }
        if (cnt4)cout<<endl;
    }

---

## 作者：flyingfrog (赞：0)

## Description
给定一个长度为 $n$ 的 $01$ 串 $a$，对任意满足 $i=1$ 或 $i=n$ 或 $a_{i-1}\neq a_{i+1}$ 的 $a_i$ 可以进行翻转，求满足操作次数小于 $r$ 的能使 $a$ 变为全 $0$ 或全 $1$ 的操作序列。

## Solution

观察数据，发现 $n$ 最大为 $2\times 10^3$，启发得到如下解法：

1. 从 $i=2$ 处出发，如果 $a_1\neq a_2$，就将 $a_1$ 翻转；
2. 如此保证 $a_{1\sim i-1}$ 全部相同，如果 $a_{i-1}\neq a_i$，就从 $a_{i-1}$ 开始翻转，一直到 $a_1$ 结束，便能使 $a_{1\sim i}$ 为全 $0$ 或全 $1$，操作次数为 $i - 1$；
3. 从 $i=2$ 推进到 $i=n$。
4. 反向尝试一次，取最优解。

以 $\{0,1,0,1\}$ 举例来说：

1. $a_1\neq a_2$，故翻转 $a_1$，此时 $\{1,1,0,1\}$，$tot=1$；
2. $a_2\neq a_3$，故先翻转 $a_2$ 后翻转 $a_1$，此时$\{0,0,0,1\}$，$tot=3$；
3. $a_3\neq a_4$，故将 $a_3$ 到 $a_1$ 依次翻转，此时 $\{1,1,1,1\}$，$tot=6$；
4. 反向尝试得到 $\{0,0,0,0\}$，$tot=6$，完毕。

最大总次数 $tot$ 为 $\sum^{n}_{i=2}(i-1)$ 即 $\frac{n(n-1)}{2} $，将 $n=2\times 10^3$ 代入可以满足 $r=2\times 10^6$ 的子任务 1 与 2，但不一定满足 $r=10^6$ 的子任务3。

考虑优化。$tot$ 随 $n$ 的增长速度大致为 $n^2$ 量级，而 $2\times(\frac{n}{2})^2= \frac{1}{2}n^2$，因此尝试将 $a$ 分为左右两部分，对左右两部分别尝试第一种解法。

但这样可能会使左右两子串 $01$ 不相同，需要进一步操作，但次数不会超过 $n$，可以证明最后操作次数不会超过 $r=10^6$。

仍然以 $\{0,1,0,1\}$ 举例来说：

1. 分为左右 $\{0,1\}$，$\{0,1\}$；
2. 分别解决得到 $\{1,1\}$，$\{0,0\}$，拼接得到 $\{1,1,0,0\}$，$tot=2$；
3. 两侧 $01$ 不同，将左侧翻转，此时 $\{0,0,0,0\}$，$tot=4$，完毕。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 2;
const int R = 2e6 + 2;

int n, r, cnt;
int a[N], op[R];

void print(){
	cout << cnt << '\n';
	for(int i = 1; i <= cnt; i ++)  cout << op[i] << ' ';
	exit(0);
}

void solvel(){
	for(int i = 2; i <= (n >> 1); i ++){
		if(a[i - 1] != a[i]){
			for(int j = i - 1; j; j --){
				op[++ cnt] = j;
				a[j] ^= 1;
			}
		}
	}
}

void solver(){
	for(int i = n - 1; i > (n >> 1); i --){
		if(a[i + 1] != a[i]){
			for(int j = i + 1; j <= n; j ++){
				op[++ cnt] = j;
				a[j] ^= 1;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> r;
	for(int i = 1; i <= n; i ++)  cin >> a[i];
	solvel();
	solver();
	if(n & 1){
    // 翻转两侧
		int mid = 1 + n >> 1;
		if(a[1] != a[mid]){
			for(int i = mid - 1; i; i --)
				op[++ cnt] = i;
		}
		if(a[n] != a[mid]){
			for(int i = mid + 1; i <= n; i ++)
				op[++ cnt] = i;
		}
	}else{
    // 翻转一侧
		if(a[1] != a[n]){
			for(int i = (n >> 1); i; i --)
				op[++ cnt] = i;
		}
	}
	print();
	
	return 0;
}
```

---

## 作者：dutianchen1 (赞：0)

# P10854 Ninelie

~~赛时一开始写法太暴力了，调了半天。~~

### 思路简析
由于题目不要求最小化操作次数 $m$，所以我们不必考虑最优化移动，仅需考虑出某一种较为优秀的转化方法即可。

分析题目，我们要把原本的零一串转化为全 $0$ 或全 $1$ 串，可以考虑指定把 $0$ 转化为 $1$，当然，取个数较少的转化也可。本题解仅考虑将 $0$ 转化为 $1$。

转化思路如下：

- 对于 $ \forall num_{i} = 0$，如果处在 $i=1$ 或 $i=n$ 或者可以转化（满足 $num_{i-1} \ne num_{i+1}$ ），直接转化即可。
- 如果当前的 $num_{i}=0$ 无法直接转化，考虑向靠近（从 $\frac{n}{2}$ 处划分左右，左侧 $i=1$，右侧向 $i=n$）的一侧位移，直到可以转化（比如到达两侧或者满足 $num_{i-1} \ne num_{i+1}$）为止。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll n,r,tot;
ll num[N];
ll ans[N];
int main() {
	n=read();
	r=read();
	for(int i=1;i<=n;i++)
	{
		num[i]=read();
	}
	for(int i=1;i<=n/2;i++)
	{
		if(num[i]==0)
		{
			if(i==1||i==n||num[i-1]!=num[i+1])
			{
				num[i]=1;
				ans[++tot]=i;
				continue;
			}
			for(int j=i-1;j>=1;j--) 
			{
				num[j]=0;num[j+1]=1;
				ans[++tot]=j,ans[++tot]=j+1;
			}
			num[1]=1;
			ans[++tot]=1;
		} 
	}
	for(int i=n;i>n/2;i--)
	{
		if(num[i]==0)
		{
			if(i==1||i==n||num[i-1]!=num[i+1])
			{
				num[i]=1;
				ans[++tot]=i;
				continue;
			}
			for(int j=i+1;j<=n;j++) 
			{
				num[j]=0;num[j-1]=1;
				ans[++tot]=j,ans[++tot]=j-1;
			}
			num[n]=1;
			ans[++tot]=n;
		} 
	}
	if(tot>r){
		cout<<-1<<'\n';
		return 0;
	}
	cout<<tot<<'\n';
	for(int i=1;i<=tot;i++)
	{
		cout<<ans[i]<<' ';
	}
	return 0;
} 

```

---

## 作者：guojiahong (赞：0)

首先，不存在无解情况。  
只需要从中间开始向两边改变成固定的 $0$ 或 $1$，如果不能改变，改变更靠近编号 $1$ 或 $n$ 的 $01$ 后再改变自己（递归），可以保证操作次数小于 $\frac{n^2}{4}$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r;
int a[2001],t[2001];
int ans[2][2000001],cnt[2];
void s1(int w,int b)
{
	if(w==1||t[w-1]!=t[w+1])
	{
		t[w]=!t[w];
		cnt[b]++;
		ans[b][cnt[b]]=w;
		return ;
	}
	s1(w-1,b);
	t[w]=!t[w];
	cnt[b]++;
	ans[b][cnt[b]]=w;
	return ;
}
void s2(int w,int b)
{
	if(w==n||t[w-1]!=t[w+1])
	{
		t[w]=!t[w];
		cnt[b]++;
		ans[b][cnt[b]]=w;
		return ;
	}
	s2(w+1,b);
	t[w]=!t[w];
	cnt[b]++;
	ans[b][cnt[b]]=w;
	return ;
}
bool _do(int b)
{
	for(int i=1;i<=n;i++)t[i]=a[i];
	for(int i=n/2;i>=1;i--)if(t[i]!=b)s1(i,b);
	for(int i=n/2+1;i<=n;i++)if(t[i]!=b)s2(i,b);
	if(cnt[b]>r)return 0;
	else return 1;
} 
int main(){
	cin.tie(0);cout.tie(0);
	cin>>n>>r;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(_do(0))
	{
		cout<<cnt[0]<<'\n';
		for(int i=1;i<=cnt[0];i++)cout<<ans[0][i]<<' ';
		return 0;
	}
	if(_do(1))
	{
		cout<<cnt[1]<<'\n';
		for(int i=1;i<=cnt[1];i++)cout<<ans[1][i]<<' ';
		return 0;
	}
	cout<<-1;
	return 0;
}
```

---

