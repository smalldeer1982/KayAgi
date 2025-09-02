# 【MX-X8-T2】「TAOI-3」终有一天，飞向水平线的彼方

## 题目背景

原题链接：<https://oier.team/problems/X8C>。

---

天与海交界的地方，到底哪边更深呢？


## 题目描述

Mio 有一个长度为 $n$ 的正整数数列 $a_1, \ldots, a_n$。她会对这个序列进行若干次操作，每次她会选择一对正整数 $l,r$，满足 $1 \le l \le r \le n$，且 $(r-l+1)$ 为偶数，然后进行以下两种操作中的一种：

- 对于所有整数 $i \in [l,r]$，令 $a_i \gets a_i+\left(|i-\frac{r+l}{2}|+\frac{1}{2}\right)$。
- 对于所有整数 $i \in [l,r]$，令 $a_i \gets a_i-\left(|i-\frac{r+l}{2}|+\frac{1}{2}\right)$。

形象化地，你可以把这理解为，选择某区间内最中间的数作为中轴，然后把区间内的所有数加上或减去它与中轴的距离。例如，如果选择 $l=1$，$r=8$，效果就是把数列的前 $8$ 个数分别加上或减去 $4,3,2,1,1,2,3,4$。

在 Mio 的操作中，她希望任意时刻数列里的所有数都是正整数。

现在，Mio 想要知道，能否用这样的操作把数列 $a_1, \ldots, a_n$ 变成目标正整数数列 $b_1, \ldots, b_n$。

## 说明/提示

**【样例解释】**

对于第一组数据，一种合法的方案为：

先选取 $l=2$，$r=5$ 进行一次减少操作，数列变为 $[1,1,3,2,1]$。

再选取 $l=1$，$r=2$ 进行一次增加操作，数列变为 $[2,2,3,2,1]$。

对于第二组数据，可以证明不存在合法的方案。

**【数据范围】**

对于 $20\%$ 的数据，$n \le 5$，$a_i,b_i \le 4$。

对于另外 $40\%$ 的数据，$\forall 1 \le i \le j \le n$，$a_i=a_j$，$b_i=b_j$。

对于所有数据，保证 $1 \le T \le 5$，$1 \le n \le 10^5$，$1 \le a_i,b_i \le 10^9$。

## 样例 #1

### 输入

```
2
5
1 3 4 3 3
2 2 3 2 1
5
1 2 1 1 1
1 1 1 2 2
```

### 输出

```
Yes
No
```

# 题解

## 作者：ny_Dacong (赞：16)

upd on 2025.2.5：优化了语言。

# 思路

先给出这道题的万能策略：

每次操作的选段长度固定为 $2$。这样一次操作转化为让 $a_l,a_{l+1}(l+1 = r)$ 同时加上（或减去）$1$。

这样一来，依次遍历 $1 \sim n-1$，对 $a_i,a_{i+1}$ 进行 $|b_i-a_i|$ 次操作。如果大了就减，否则加。

注意由于操作后 $a_{i+1}$ 的值也会变，所以一会修改 $a_{i+1}$ 时要按照本次操作后的值计算。

如果最后，$a_n = b_n$，则有解（这就是一个解），否则**一定无解**。

以样例 1 为例，其变化过程为：

```txt
2 4 4 3 3
2 2 2 3 3
2 2 3 4 3
2 2 3 2 1
```

**证明为什么本策略无法得出解，就一定无解。**

假如本策略无解，然而有其它的方法使得有解，那么这个有解的方法一定使用了长度大于 $2$ 的操作。只要我们证明，**一次长度大于 $2$ 的操作可以用万能策略替代**，那么这个假设就可以证伪。

**证明：**

首先，对于**长度任意**的一次操作 $[l,r]$，令 $k_i = \left(|i-\frac{r+l}{2}|+\frac{1}{2}\right)$。例如，如果 $l=1$，$r=8$，$k_1 \sim k_8 = (4,3,2,1,1,2,3,4)$。

然后令 $d_i$ 表示，如果用开头的万能策略替代本次操作，需要进行 $d_i$ 次范围为 $[i,i+1]$ 的**加法**操作。特别的，如果 $d_i < 0$，表示需要执行 $-d_i$ 次减法操作。

可以得出 $d_l = k_l$。

然后可以发现 $d_{l+1} = k_{l+1}-d_l$。也就是说，$l+1$ 这一位已经加上 $d_l$ 了，还需要加上 $k_{l+1}-d_l$ 就可以等于 $k_{l+1}$ 了。

进而可以发现，$d_i = k_i-d_{i-1}(l < i < r)$。

那么如果 $d_r = 0$，也就是说前面的操作足以让 $r$ 这一位完成修改了，这一位不用再操作了，那么就说明万能策略可以替代。

对 $d_r$ 进行展开：

$$
\begin{aligned}
d_r & = k_r-d_{r-1} \\
    & = k_r-k_{r-1}+d_{r-2} \\
    & = k_r-k_{r-1}+k_{r-2}-d_{r-3} \\
    & \dots \\
    & = k_r-k_{r-1}+k_{r-2}-k_{r-3}+ \dots +k_{l+1}-d_{l} \\
    & = k_r-k_{r-1}+k_{r-2}-k_{r-3}+ \dots +k_{l+1}-k_{l} \\
    & = k_r+k_{r-2}+k_{r-4}+k_{r-6}+ \dots - (k_{r-1}+k_{r-3}+k_{r-5}+k_{r-7}+\dots) \\
    & = 0
\end{aligned}
$$

发现 $k$ 的奇数项之和一定等于偶数项之和（因为是对称的），所以最后 $d_r$ 一定为 $0$。

证毕。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n;
long long a[100050],b[100050];
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		memset(a,0,sizeof(long long)*(n+10));
		memset(b,0,sizeof(long long)*(n+10));
		for(long long i = 1; i <= n; i++){
			scanf("%lld",&a[i]);
		}
		for(long long i = 1; i <= n; i++){
			scanf("%lld",&b[i]);
		}
		if(n == 1){
			puts("No");
			continue;
		}
		for(long long i = 1; i < n; i++){
			static long long tp;
			tp = b[i]-a[i];
			a[i] += tp;
			a[i+1] += tp;
		}
		if(a[n] == b[n]){
			puts("Yes");
		}else{
			puts("No");
		}
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：4)

**Upd 2025.2.1：在复盘的时候突然发现这样并不能概括所有情况，所以修改了一下操作简化部分。**
## 思路
尝试简化操作，我们可以通过选取多个连续长度为 $2$ 的区间达到给长度为偶数的区间全部加/减一的目的。\
那么，可以发现如果选择两个位置 $l$ 和 $r$ 使得 $r-l+1$ 为偶数，我们可以让 $a_{l\cdots r}$ 全部加一，再让 $a_{l+1\cdots r-1}$ 全部减一，等价于 $a_l$ 和 $a_r$ 加一。概括一下发现我们可以任意选取一个奇数位置上的值和偶数位置上的值，并让它们加/减相同的值。

每次要让一个奇数位置上的变量和一个偶数位置上的变量偏移相同值，只要统计奇数位置和偶数位置上需要的总偏移量，比较是否相等就可以了。显然我们先做操作里增加的部分就可以不让变量变成非正数。时间复杂度 $O(Tn)$。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,n,a[200000],b[200000];
long long sum[2];
int main(){
	scanf("%d",&T);
	while(T --){
		sum[0] = sum[1] = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
		for(int i = 1;i <= n;i ++) scanf("%d",&b[i]);
		for(int i = 1;i <= n;i ++) sum[i & 1] += a[i] - b[i];//统计需要的偏移量
		if(sum[0] == sum[1]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：GONGX (赞：4)

## 题意简述
给定两个长度为 $n$ 的正整数数组 $a$ 和 $b$。每次操作选择一个长度为偶数的区间，并对数组 $a$ 区间内的元素进行对称的加减操作。我们需要判断能否通过若干次操作将数组 $a$ 变为目标数组 $b$。

## 解题思路
### 核心思路
每次操作的影响可以分解为对相邻元素的调整。例如，选择长度为二的区间 $[i, i+1]$ 进行加减操作，相当于同时调整 $a_i$ 和 $a_{i+1}$ 的值。更长的偶数区间操作均可分解为多次相邻操作的叠加，而同理，更长的奇数区间也可以进行分解，因此无需使用更长的区间操作。通过这样的分解，我们可以将整个问题转化为逐个处理每个元素，并将差值传递到下一个元素。

### 具体实现
首先从第一个元素开始，依次将每个元素 $a_i$ 调整到到目标值 $b_i$，并将差值 $d_i = b_i - a_i$ 传递给下一个元素 $a_{i+1}$。

最后在处理完前 $n-1$ 个元素后，检查最后一个元素 $a_n$ 是否等于目标值 $b_n$。若相等，则存在合法操作序列；否则不存在。

时间复杂度为 $O(T\cdot n)$。

### 正确性证明
每次操作可以视为对相邻元素的调整，通过合理选择操作顺序，可以确保中间过程所有元素保持为正整数。最终条件 $a_n = b_n$ 是问题有解的必要且充分条件。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int T, n, a[N], b[N];

int main() {
    ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr); // 对于 cin,cout 的优化
    cin >> T; // 输入测试数据组数
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];
        for (int i = 1; i < n; ++i) {
            int d = b[i] - a[i]; // 当前差值
            a[i + 1] += d; // 传递差值
        }
        cout << (a[n] == b[n] ? "Yes\n" : "No\n"); // 用三目运算符输出答案
    }
    return 0;
}
```

## 总结
本题的关键在于将复杂的区间操作转化为相邻元素的差值传递，并通过检查最后一个元素是否匹配来判断可行性。这种方法高效且简洁。

---

## 作者：zlqwq (赞：3)

前言：赛时有一段时间一直没思路，所以交了好多发阳寿随机数。

正解：题目里已经给了人话翻译，就是中间只加一，然后往外扩散。不难发现，我们两个一组处理，跟我们一坨区间处理最后达成的效果其实是一样的，故我们两个为一组扫一遍，一直往后加答案，如果第 $n$ 位都可以满足，那前边的一定可以。时间复杂度 $O(n)$。


```cpp
#include<iostream>
#define int long long
using namespace std;
int a[100005],b[100005];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		int c=b[i]-a[i];
		a[i+1]+=c;
	}
	if(a[n]==b[n]){
		cout<<"Yes\n";
	}
	else cout<<"No\n";
}
signed main(){
    int T;
    cin>>T;
    while(T--){
    	solve();
    }
    return 0;
}
```

---

## 作者：251Sec (赞：2)

### 题意简述

给定两个数列 $\{a_n\},\{b_n\}$。进行任意多次操作，每次操作选择一个长度为偶数的区间，把最中间两个数增加 $1$，把旁边两个数增加 $2$，再把旁边两个数增加 $3$，以此类推。同理可以作减少操作。不允许产生负数。问能不能把 $a$ 变成 $b$。

$1 \le T \le 5$，$1 \le n \le 10^5$，$1 \le a_i,b_i \le 10^9$。

### 解法

首先不产生负数这个条件是无用的，因为我们总可以先做增加操作再做减少操作。令 $c_i=a_i-b_i$，问题等价于使用这样的操作把数列 $c$ 的所有数变成 $0$。

注意到操作不改变所有偶数位置的数之和减去所有奇数位置的数之和。则合法的一个必要条件是，数列 $c$ 的奇数位置数之和等于偶数位置数之和。

这是充分条件。考虑从左到右对长度为 $2$ 的区间操作使得左边的数变成 $0$。那么我们最终可以导出除了最后一个数以外的所有数为 $0$，而操作不改变偶数位置数和奇数位置数的差值，那么可以推出最后一个数为 $0$，于是我们得到了合法方案。

---

## 作者：ty_mxzhn (赞：2)

注意到假设我们想达到加上 $2 \ 1 \ 1 \ 2$ 的效果，完全可以先变成 $2 \ 2 \ 2 \ 2$ 然后中间减一下。

类比我们可以发现我们只会对相邻的两个数操作。

考虑构建如下模型：求出数组的奇数位减去偶数位作为特征值。

为什么是对的呢？因为一次两边各 $\pm1$ 的操作不会改变奇数位的和减去偶数位的和的值。这里证明了必要性。

考虑证明充分性，只需要构造操作方案。我们可以把 $2 \ 0 \ 0$ 变成 $0 \ 0 \ 2$，所以我们可以把奇数位扔一起偶数位扔一起然后操作。

据此我们只需要比对两数组特征值即可，时间复杂度 $O(n)$。

---

## 作者：BeeAC (赞：2)

## 思路
设所有 $r=l+1$ 的操作为“简单操作”，那么对于所有简单操作，都可以看成将 $a_l,a_r$ 同加或同减 $1$。

由于所有操作都关于中轴对称，所以都可以看成从两端开始重复进行简单操作得到的。例如 $l=1,r=8$，效果就是把数列的前 $8$ 个数分别加上或减去 $(0,0,0,0,0,0,0,0\rightarrow\dots\rightarrow4,4,0,0,0,0,4,4\rightarrow\dots\rightarrow4,3,-1,0,0,-1,3,4\rightarrow\dots\rightarrow4,3,2,3,3,2,3,4\rightarrow\dots\rightarrow4,3,2,1,1,2,3,4)$。

显然可以从 $i=1$ 开始反复进行简单操作，使得 $a_1=b_1,a_2=b_2,\dots,a_{n-1}=b_{n-1}$。若 $a_n=b_n$，则存在合法方案，否则不存在。

时间复杂度 $O(Tn)$，期望得分 $100$ 分。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int t,n,a[N],b[N],sa,sb;
void read(int &x)
{
	x=0;int f=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		f=c=='-';
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	x=f?-x:x;
	return;
}
int main()
{
	read(t);
	while(t--)
	{
		sa=sb=0;
		read(n);
		for(int i=1;i<=n;++i)
			read(a[i]);
		for(int i=1;i<=n;++i)
			read(b[i]);
		for(int i=1;i<n;++i)
		{
			int t=b[i]-a[i];
			a[i]+=t;
			a[i+1]+=t;
		}
		printf("%s\n",a[n]!=b[n]?"No":"Yes");
	}
	return 0;
}
```

---

## 作者：Lijunzhuo (赞：1)

因为每一次操作可选择的区间长度不一定，所以考虑转化：我们注意到，每一次操作都可以化为若干次区间长度为 $2$ 的操作。所以考虑暴力，从左往右遍历，用区间长度为 $2$ 的操作尽可能的使数列 $A$ 和 $B$ 相等。最后判断末尾一项是否相等。若是，则可以完成操作；若否，则不可能完成操作。代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,A[114514],B[114514],C[114514];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&B[i]);
		for(int i=1;i<n;i++)
			A[i+1]+=B[i]-A[i];
		if(A[n]==B[n]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
/*
证明：
+4+3+2+1+1+2+3+4
可以化为：
+1+1+1+1+1+1+1+1
+1+1+1+1+1+1+1+1
+1+1+1+1+1+1+1+1
+1+1+1+1+1+1+1+1
  -1-1
    -1-1
      -1-1
      -1-1
        -1-1
          -1-1
*/
```
[记录](https://www.luogu.com.cn/record/200942878)。

---

## 作者：liyunhe (赞：1)

### 题意解析

我们可以任选长度为偶数的一段，加上或减去一个“V 字形”，当长度为 $4$ 时，将加上或减去 $2,1,1,2$。

### 思路重点

看到这样的题，应该无法直接完成，尝试转化。

**注意到：“V 字形” 可以等价于 $1,1$ 的覆盖效果**。证明如下：

- “V 字形” 包括 $1,1$。
- 所有“V 字形” 均可以用 $1,1$ 表示。
  - 长度为 $4$ 时，用 $2,2,2,2$（四个 $1,1$）减去 $1,1$ 就可以变为 $2,1,1,2$。
  - 长度为 $6$ 时，用 $3,3,3,3,3,3$（九个 $1,1$）减去 $1,1,1,1$，变为 $3,2,2,2,2,3$，再减 $1,1$ 变为 $3,2,1,1,2,3$。
  - 以此类推。

这样题目就变为了可以将相邻的两个数同时加一或减一，能否使数列 $a$，变为数列 $b$。

### 具体操作

创建一个新数列表示 $a$ 和 $b$ 的差值，从左到右遍历数组，对于每个非零的差值，尝试通过将当前元素和下一个元素同时减去该差值来消除它。这模拟了将相邻两个数同时减 1 的操作（若差值为负则相当于同时加 1）。

```cpp
for(int i=0;i<n;i++){
        dif[i]=b[i]-a[i];
    }
    for (int i=0;i<n-1;i++){
        if (dif[i]!=0) {
            int k=dif[i];
            dif[i]-=k;
            dif[i+1]-=k;
        }
    }
```

检查最后一位是否为 $0$，即数组是否完全清空。

```cpp
    if (dif[n-1] != 0) {
        return 0;
    }
    return 1;
```

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100005],b[100005],dif[100005];
bool canTransform() {
    for(int i=0;i<n;i++){
        dif[i]=b[i]-a[i];
    }
    for (int i=0;i<n-1;i++){
        if (dif[i]!=0) {
            int k=dif[i];
            dif[i]-=k;
            dif[i+1]-=k;
        }
    }
    if (dif[n-1] != 0) {
        return 0;
    }
    return 1;
}

int main() {
	int T;
	cin>>T;
	while(T--){
	    cin>>n;
	    for(int i=0;i<n;i++){
	        cin>>a[i];
	    }
	    for(int i=0;i<n;i++){
	        cin>>b[i];
	    }
	    if(canTransform())cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
    return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
鉴于数据量，我们需要一个线性复杂度的程序。

观察操作，发现描述的花里胡哨的操作本质上就是将两个相邻的数同增同减。

所有更大的 $l$ 和 $r$ 都可以通过同加减操作模仿。

而后，对序列模拟操作即可，不用考虑正负数。

实操处理负数：将后一个数与再后一个同加亿点点就行。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,a[100100],b[100010],cha;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}//朴实无华的输入
		bool f=1;
		for(int i=1;i<n;i++){
			a[i+1]+=(b[i]-a[i]);
		}//模拟
		if(a[n]==b[n])cout<<"Yes\n";//判断最后一位
		else cout<<"No\n";
	}
}
/*
1 3 1 3 1
3 1 3 1 3

*/
```

---

## 作者：封禁用户 (赞：0)

很有迷惑性的一道题。  
### 具体思路
用一个数组 $c$ 记录 $a_i$ 与 $b_i$ 之差，然后只考虑区间长度为 $2$ 的修改操作，因为大于 $2$ 的区间修改其实可以拆解为若干个区间长度为 $2$ 的加与减两种操作，因为其更改的差值为 $1$。因此可以采用贪心，每次枚举第 $i$ 个数，如果 $c_i\ne 0$，就直接对区间 $[i,i+1]$ 进行对应的修改，使 $c_i$ 变为 $0$。最后判断第 $n$ 个数，如果 $c_n=0$ 代表可以转换成功，反正不可以。  
### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define I_love_Foccarus return
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
#define in(a) a=read()
#define fi first
#define se second
const int N = 1e5 + 5;
const int inf = INT_MAX;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	I_love_Foccarus x*f;
}
void fast() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int a[N] , b[N] , c[N];
signed main() {
	//fast();
	int t;
	in(t);
	while(t--){
		int n;
	    in(n);
	    rep(i,1,n)in(a[i]);
	    rep(i,1,n)in(b[i]);
	    rep(i,1,n)c[i]=a[i]-b[i];
		rep(i,1,n-1){
			if(c[i]!=0){
				c[i+1]-=c[i];
			}
		}
		cout<<(c[n]==0?"Yes":"No");
		cout<<'\n'; 
	}

	I_love_Foccarus 0;
}
```

---

## 作者：_lmh_ (赞：0)

题目里的操作比较抽象，只考虑最简单的一种：将相邻两个数同时 $+1$ 或 $-1$，容易发现其他所有操作都可以用这种操作“模拟”出来。

例如一个长度为 $6$ 的操作 `+3 +2 +1 +1 +2 +3`，可以先将所有数都 $+3$，再让中间四个数 $-1$，最后让最中间两个数 $-1$。

发现可以交换操作顺序，于是我们在操作时先加后减，这样就不会出现负数。

判断一个序列是否合法也是简单的，因为一次操作不会改变奇数位与偶数位之差，只需判断两个序列的这个值是否相等即可。如果相等的话，构造方案是简单的，只需要从前到后调整每一位即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,a,sum;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;sum=0;
		for (int i=1;i<=n;++i){
			cin>>a;
			if (i&1) sum+=a;else sum-=a;
		}
		for (int i=1;i<=n;++i){
			cin>>a;
			if (i&1) sum-=a;else sum+=a;
		}
		if (sum==0) cout<<"Yes\n";else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11643 题解

## 思路

对于一次操作 $[l,r]$，均可以表示成若干次操作 $[i,i+1]$。

举个例子，一个长度为 $8$ 的区间的操作，会使对应位置的值增或减 $4,3,2,1,1,2,3,4$，一个长度为 $2$ 的区间的操作，会使对应位置的值增或减 $1,1$，设一开始变化量的序列为 $0,0,0,0,0,0,0,0$，则进行若干次 $1,1$，序列可以这样变化：

$$
0,0,0,0,0,0,0,0 \\
4,4,0,0,0,0,0,0 \\
4,3,-1,0,0,0,0,0 \\
4,3,2,3,0,0,0,0 \\
4,3,2,1,-2,0,0,0 \\
4,3,2,1,1,3,0,0 \\
4,3,2,1,1,2,-1,0 \\
4,3,2,1,1,2,3,4 \\
$$

那么，现在记 $c_i = b_i - a_i$，我们要通过若干次相邻两个位置一起增或减 $1$ 的操作，使得全部为 $0$ 的初始序列变为 $c$。

像上方序列变化一样，从左到右依次改变每一个位置，左端点枚举到 $n-1$，使得序列前 $n-1$ 个数字都满足条件，最后看一下第 $n$ 位是否满足条件即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[++idx]=c,c=getchar();
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=100005;

int T,n;
int a[N],b[N];

signed main() {
    read(T);
    while (T--) {
        read(n);
        _rep(i,1,n) read(a[i]);
        _rep(i,1,n) read(b[i]);
        _rep(i,1,n-1) {
            int k=b[i]-a[i];
            a[i]+=k,a[i+1]+=k;
        }
        if (a[n]!=b[n]) puts("No");
        else puts("Yes");
    }
    return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

容易想到将操作化简。

---

**Part 1：**

设原始序列为：$[x,0,0,x]$。

选取 $l=1$，$r=2$ 进行 $x$ 次减少操作，数列变为 $[0,-x,0,x]$。

选取 $l=2$，$r=3$ 进行 $x$ 次增加操作，数列变为 $[0,0,x,x]$。

选取 $l=3$，$r=4$ 进行 $x$ 次减少操作，数列变为 $[0,0,0,0]$。

那么我们可以发现对于该数列的任意一个长度为 $4$ 的子串，对应位同时分别增减 $[1,0,0,1]$ 是合法操作。

根据证明过程同理可得，对于该数列的任意一个长度为偶数的子串，对应位同时分别增减 $[1,0,\dots,0,1]$ 是合法操作。

我们称这样的操作叫做广义增加或广义减小操作。

---

**Part 2：**

设原始序列为：$[n,n-1,\dots,2,1,1,2,\dots,n-1,n]$。

选取 $l=n$，$r=n+1$ 进行 $1$ 次广义减少操作，数列变为 $[n,n-1,\dots,2,0,0,2,\dots,n-1,n]$。

选取 $l=n-1$，$r=n+2$ 进行 $2$ 次广义减少操作，数列变为 $[n,n-1,\dots,0,0,0,0,\dots,n-1,n]$。

以此类推。

我们发现所有合法的操作都可以通过增减 $[1,1]$ 实现。

---

Amazing 啊！

那么我们直接从左往右算就行了。

做完了。

---

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005],b[100005],c[100005];
signed main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        cin>>a[i];
        for(int i=1;i<=n;i++)
        cin>>b[i];
        for(int i=1;i<=n;i++)
        c[i]=a[i]-b[i];
        for(int i=2;i<=n;i++)
        c[i]-=c[i-1];
        if(c[n])puts("No");
        else puts("Yes");
    }
    return 0;
}
```

建议评黄。

---

