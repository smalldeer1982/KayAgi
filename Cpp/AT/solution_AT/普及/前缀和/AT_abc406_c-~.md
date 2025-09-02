# ~

## 题目描述

对于一个长为 $M$ 的数列 $A=(A_1,A_2,\cdots,A_N)$，$A$ 是波浪序列当且仅当以下条件被满足：
- $M\ge4$；
- $A_1<A_2$；
- 恰好存在一个 $2\le i<N$，满足 $A_{i-1}<A_i>A_{i+1}$；
- 恰好存在一个 $2\le i<N$，满足 $A_{i-1}>A_i<A_{i+1}$。

给定一个长为 $N$ 的排列 $P$，求 $P$ 有多少个连续子串是波浪序列。

## 说明/提示

### 样例 1 解释

$(1,3,6,4,2,5)$ 的连续子串中有两个波浪数列，为 $(3, 6,4,2,5)$ 和 $(1,3,6,4,2,5)$。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
6
1 3 6 4 2 5```

### 输出

```
2```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
0```

## 样例 #3

### 输入

```
12
11 3 8 9 5 2 10 4 1 6 12 7```

### 输出

```
4```

# 题解

## 作者：xiaoke2021 (赞：6)

观察题面，不难发现，题目要求求出序列 $A$ 所有的连续子序列中**恰好为一个峰连接一个谷**的数量。

上一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jcrkyu32.png)

我们发现，在一个可行答案中，必然以一个上升段开始，一个上升段结尾。也就是说，**每两个极长连续上升段**组成一组答案。注意是一组，不是一个。

上面这组答案中，第一个上升段长度为 3，第二个为 4。由于每一个上升段长度至少为 2（很显然），所以左边的上升段有 2 种可能的长度，右边则是 3 种。根据乘法原理，这组答案中有 6 个答案。

不妨依次存储每一个极长上升段的长度（例如计为 $a$，数量为 $cnt$），不难发现答案即为：

$$\sum^{cnt-1}_{i=1}{(a_i-1)(a_{i+1}-1)}$$


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int p[300000+5];
unsigned long long a[300000+5];
unsigned long long cnt;
unsigned long long ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	int k=0;
	p[0]=1e9+7;
	long long sum=0;
	for(int i=1;i<=n;i++){
		if(p[i]>p[i-1]){
			sum++;
		}else if(sum>=1){
			a[++cnt]=sum+1;
			sum=0;
		}
	}a[++cnt]=sum+1;
	if(a[cnt]==1) cnt--;
	for(int i=1;i<cnt;i++){
		ans+=(a[i]-1)*(a[i+1]-1);
	}cout<<ans;
	return 0;
}

```

---

## 作者：Tomwsc (赞：5)

# AT_abc406_c [ABC406C] ~ 题解

## 思路

我们称满足第三个条件的值为峰值，满足第四个条件的值为谷值。容易发现，峰值和谷值是交错出现的，所以第 $i$ 个峰值只能和第 $i-1$ 个或第 $i+1$ 个谷值组成子串，第 $i$ 个谷值同理。现在考虑记录每一个峰值和谷值的下标，存放在一个数组中，这样子我们便可以不用管这个值是峰值还是谷值了。我们不妨只枚举第 $i$ 个值与第 $i-1$ 个值组成子串的情况，因为这样子可以避免去重。

考虑计算答案。

对于第 $i$ 个值和第 $i-1$ 个值组成子串的情况，如果在第 $i-2$ 个值到第 $i-1$ 个值之间有 $x$ 种子串的合法开头，在第 $i$ 个值到第 $i+1$ 个值之间有 $y$ 种子串的合法结尾，那么这个子串对答案的贡献便是 $x\times y$。

现在考虑计算出这两个值。

$y$ 很容易计算，它便等于第 $i+1$ 个值和第 $i$ 个值中间的数的个数加一。至于为什么要加一，是因为可以取到第 $i+1$ 个值。

那 $x$ 该怎么计算呢？我们考虑使用类似前缀和的思想，设 $s_i$ 表示前 $i$ 项中有多少个合法开头，则有递推式：

- $A_i>A_{i-1}$，$s_i\leftarrow s_{i-1}+1$。
- $A_i<A_{i-1}$，$s_i\leftarrow s_{i-1}$。

设我们把峰值和谷值的下标存储在 $d$ 数组中。那么此时，$x$ 的值便等于 $s_{d_{i-1}}-s_{d_{i-2}}$。

总时间复杂度为：$O(n)$。

## 代码

需注意一下细节的处理。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
#define regint register int
#define pb push_back
#define mp make_pair
#define PII pair<int , int>
using namespace std;
const int MAXN = 3e5 + 10;
int s[MAXN] , d[MAXN];
int n , cnt = 0;

void solve() {
	/*
	trust yourself
	*/
	cin >> n;
	vector<int>a(n + 1);
	for(regint i = 1;i <= n;i ++) {
		cin >> a[i];
	}
	for(regint i = 2;i < n;i ++) {
		if(a[i] < a[i - 1] && a[i] < a[i + 1]) {
			d[++ cnt] = i;
		}
		if(a[i] > a[i - 1] && a[i] > a[i + 1]) {
			d[++ cnt] = i;
		}
		if(a[i] > a[i - 1]) {
			s[i] = s[i - 1] + 1;
		} else {
			s[i] = s[i - 1];
		}
	}
	d[cnt + 1] = n;
	int ans = 0;
	for(regint i = 2;i <= cnt;i ++) {
		ans += (s[d[i - 1]] - s[d[i - 2]]) * (d[i + 1] - d[i]);
	}
	cout << ans;
	return;
}

signed main() {
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}
```

---

## 作者：littlebug (赞：4)

挺好玩的一个题。

---

## Solution

先分析下条件，可以发现第一个条件是没用的，因为只要满足第三四个条件，那么长度至少为 $4$（形如「大小大小」）。

因为第二个条件是容易的，直接枚举即可。所以考虑在左端点确定的情况下，如何根据条件三四确定右端点的取值范围。

可以想到预处理 $nxt_{0/1}$ 分别表示下一个满足 $a_{i-1} > a_i < a_{i+1}$ 和 $a_{i-1} < a_i > a_{i+1}$ 的位置。

对于每个满足条件二的 $i$，其可选区间的左端点即为：

$$
l = \max(nxt_{0,i+1} , nxt_{1,i+1}) + 1
$$

这样可以保证至少包含 $1$ 个满足条件三、$1$ 个满足条件四的数。最后 $+1$ 是因为 $a_l$ 满足条件需要它两边的数都存在，故 $a_{l+1}$ 必须取。

但题目要求的是恰好一个，所以就不能取到下一个满足条件的位置，故右端点为：

$$
r = \min(nxt_{0,l} , nxt_{1,l})
$$

不需要 $-1$，原因和上面还是一样的，因为 $a_r$ 满足条件需要它两边的数都存在，所以只要 $a_{r+1}$ 不取，$a_r$ 就不会满足条件。

这时候方案数即为 $r-l+1$。

时间复杂度 $O(n)$。

## Code

```cpp
int n,a[N],nxt[2][N];

il void solve()
{
    read(n),_::r(a,n);

    rep(i,n,n+n) nxt[0][i]=nxt[1][i]=20120712;
    rpe(i,n-1,2) nxt[0][i]=(a[i]>a[i-1] && a[i]>a[i+1] ? i : nxt[0][i+1]),nxt[1][i]=(a[i]<a[i-1] && a[i]<a[i+1] ? i : nxt[1][i+1]);

    int ans=0;
    rep(i,1,n-1) if(a[i]<a[i+1])
    {
        int l=max(nxt[0][i+1],nxt[1][i+1])+1;
        if(l>=20120712) continue;
        int r=min(nxt[0][l],nxt[1][l]);
        if(t>=20120712) r=n;
        ans+=r-l+1;
    }
    
    write(ans);
}
```

---

华风夏韵，洛水天依！

---

## 作者：Clover_Lin (赞：3)

## 前言
欢迎查看我的[博客](https://blog.csdn.net/ArmeriaLeap/article/details/148034676)。

除了 A 题，唯一一道一遍过的题。
## 题目大意
我们定义满足以下所有条件的一个长度为 $N$ 的序列 $A=(A_1,A_2,\dots,A_N)$ 为**波浪序列**：
- $N\ge4$（其实满足后面就必须满足这个条件）。
- $A_1\le A_2$（小心不要忘了这个条件）。
- 有且只有一个峰。
- 有且只有一个谷。

现在有个长度为 $N$ 的序列 $P$，求有多少个**连续**的子段是波浪序列。
## 思路
我们看一下条件——有且只有一个峰、一个谷。但是，整个序列里面会有许多峰、许多谷。然后，我们会从中**选取**一个峰、一个谷和一些其他类别的元素构成波浪序列。显然，我们要记下所有峰、所有谷的位置。默认按从小到大顺序记。

接下来，我们枚举选取子段的**右端点**，从第一个既包含峰又包含谷的位置开始，一直枚举到 $N$。考虑左端点可能的取值范围。前面通过从小到大的顺序暗示了这里的重要算法——**二分**。二分什么呢？左端点下边界？上边界？都可以。因为它是上下边界都与峰谷的位置有关，而确定上边界的峰一定“紧挨着”确定下边界的峰（指的是中间不会有别的峰），谷也是同理。式子自己想想吧！不会可以看代码。
## 代码
请点击 [这里](https://atcoder.jp/contests/abc406/submissions/65892307) 查看 AC 记录。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, p[300010];
int c1, v1[300010]; // peak
int c2, v2[300010]; // valley
int s1[300010];
int s2[300010];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 2; i < n; i++)
	{
		s1[i] = s1[i - 1];
		if (p[i - 1] < p[i] && p[i] > p[i + 1])
			v1[++c1] = i, s1[i]++;
		s2[i] = s2[i - 1];
		if (p[i - 1] > p[i] && p[i] < p[i + 1])
			v2[++c2] = i, s2[i]++;
	}
	if (!c1 || !c2)
	{
		cout << "0" << endl;
		return 0;
	}
	long long ans = 0;
	for (int i = max(v1[1], v2[1]) + 1; i <= n; i++)
	{
		int p1 = lower_bound(v1 + 1, v1 + c1 + 1, i) - v1 - 1;
		int p2 = lower_bound(v2 + 1, v2 + c2 + 1, i) - v2 - 1;
//		if (p1 < 0 || p2 < 0) p1 = p2 = 0;
//		cout << i << " " << p1 << " " << p2 << ": " << endl;
//		cout << " - " << v1[p1] << " " << v2[p2] << endl;
//		cout << " - " << v1[p1 - 1] << " " << v2[p2 - 1] << endl;
		if (v1[p1] > v2[p2]) continue;
		int vmx = max(v1[p1 - 1], v2[p2 - 1]) - 1;
		int vmn = min(v1[p1], v2[p2]) - 1;
		vmx = max(vmx, 0);
		if (i - vmx < 4) continue;
		if (i - vmn + 1 < 4) vmn = i - 3;
		ans += vmn - vmx;
//		cout << i << " " << vmx << " " << vmn << endl;
	}
	cout << ans << endl;
	return 0;
}
```
## 总结
时间复杂度 $O(N\cdot\log N)$，二分很好用。

---

## 作者：shigengxin (赞：2)

### 思路
首先找出在 $P$ 的 $2 \sim N - 1$ 位置以内满足题目中条件三或条件四的位置，将它们称为**特殊位置**并存储在同一个数组中。

根据条件，在答案的连续子序列中必须只能够分别存在一个满足条件三的位置和一个满足条件四的位置，于是我们可以扫描之前存在数组中的每一个特殊位置。只有前后两个相邻的特殊位置所满足的条件不同时，我们才需要去考虑它们。例如，有 $x$ 和 $y$ 两个位置（$x < y$）分别满足条件三和条件四，且它们中间没有其他特殊位置：
* 首先，为了让 $x$ 和 $y$ 能够作为特殊位置，它们两边的数字也必须要被包含到连续子序列中来，此时区间 $[x - 1,y + 1]$ 形成的子序列是一个满足除条件二以外的子序列。
* 考虑是否能向两边扩张区间。
* 对于左端点，必须要保证它小于它右边的数字，于是考虑左端点情况：

  * 如果在 $x - 1$ 左侧存在其他特殊位置，将其记为 $r$。因为特殊位置需要包含两旁数字，因此只要 $r - 1$ 不在区间内就不会打破条件三或四。因此，此时左端点可以选择的情况数量为区间 $[r,x - 1]$ 内部满足 $P_i < P_{i + 1}$ 的位置 $i$ 的数量。
  * 如果 $x - 1$ 左侧不存在其他特殊位置，那么此时左端点可以选择的情况数量为区间 $[1,x - 1]$ 内部满足 $P_i < P_{i + 1}$ 的位置 $i$ 的数量。
* 对于右端点：

  * 如果 $y + 1$ 右侧存在其他特殊位置，记最近的特殊位置为 $r$。只要不选到 $r + 1$ 这个位置就不会打破条件三或四的限制。因此右端点可选区间 $[y + 1,r]$ 内的任意一个位置，方案数为 $r - y$。
  * 如果在 $y + 1$ 右侧不存在其他特殊位置，那么右端点可以选区间 $[y + 1,n]$ 内的任意一个位置，方案数为 $n - y$。

最后使用前缀和寻找一段区间内部有多少个位置满足 $P_i < P_{i + 1}$。
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[300005];
long long ans;
struct node{
    int num, op;
};
vector<node> v;
int sum[300005];
int find(int l, int r){
    if(l > r){
        return 0;
    }
    return sum[r] - sum[l - 1];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    for(int i = 2;i < n;i++){
        if(a[i] > a[i-1] && a[i] > a[i+1]){
            node ttt;ttt.num = i, ttt.op = 1;
            v.push_back(ttt);
        }
        if(a[i] < a[i-1] && a[i] < a[i+1]){
            node ttt;ttt.num = i, ttt.op = 2;
            v.push_back(ttt);
        }
    }
    for(int i = 1;i < n;i++){
        if(a[i] < a[i+1]){
            sum[i] = sum[i-1] + 1;
        }else{
            sum[i] = sum[i-1];
        }
    }
    sum[n] = sum[n-1];
    for(int i = 1;i < v.size();i++){
        if(v[i].op != v[i-1].op){
            int a, b;
            if(i - 2 >= 0)
                a = find(v[i-2].num, v[i-1].num - 1);
            else
                a = find(1, v[i-1].num - 1);
            if(i + 1 < v.size()){
                b = v[i+1].num - v[i].num;
            }else{
                b = n - v[i].num;
            }
            ans += 1LL * a * b;
        }
    }
    cout << ans;
}
```

---

## 作者：xiaozhangawa (赞：2)

## 相关记号

在本文中，我们把 $A_{i-1}<A_i>A_{i+1}$ 叫做一个**峰**，把 $A_{i-1}>A_i<A_{i+1}$ 叫做一个**谷**。

## 思路

本题的重点就是要找出峰和谷，可以用两个数组 $h,l$ 来记录峰和谷的位置。然后根据 $A_1<A_2$ 这个条件容易知道每个符合要求的连续子序列一定是**先峰后谷**，也就是类似题目名字 `~` 的形状。

然后我们思考如何统计贡献。我们先来看一个简单的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/qdgbujoj.png)

这里我把峰标为蓝色，谷标为黑色。

因为满足要求的子序列只能恰好有一个峰和谷（条件 3、4），那么容易知道满足要求的子序列必须只能选相邻的峰和谷，但是可以把第一个和最后一个设为峰或谷。

那么我们先来看第一对峰谷组合 $3,5$，对于它们只有一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/7b4eikof.png)

再看 $5,4$（不选 $1,5$ 是因为前面讲到的先峰后谷），也只可能有一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/c3d2jxxz.png)

我们来看一下两次选择，都是从峰往左，取到前一个峰或谷（第 2 次），如果没有就取到头（第 1 次）；同理，从谷往右，取到下一个峰或谷，如果没有就取到头。

最终方案数就是左边能取的数 $\times$ 右边能取的数。

为了方便，我们可以把 $A_1$ 和 $A_N$ 看成既是峰又是谷的元素，那么对于第 $i$ 个峰、第 $j$ 个谷，有贡献 $(h_i-\max\{h_{i-1},l_{j-1}\})\times(\min\{h_{i+1},l_{j+1}\}-l_j)$。

那么现在的问题是怎么取 $i,j$。

因为我们只取相邻的两个峰和谷，所以我们可以用双指针。首先，$i\gets i+1$，然后用 `while` 循环取到大于 $h_i$ 的首个 $l_j$，再统计贡献，具体细节见代码注释。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[300010],h[300010],l[300010];
signed main(){
	int n,ans=0,ht=0,lt=0;
	cin>>n;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 2;i < n;i++){
		if(a[i-1]<a[i] && a[i+1]<a[i]) h[++ht]=i;//记录峰
		else if(a[i-1]>a[i] && a[i+1]>a[i]) l[++lt]=i;//记录谷
	}
    //将a[1]和a[n]看作峰和谷
	h[0]=l[0]=1;
	h[ht+1]=l[lt+1]=n;
	for(int i = 1,j = 1;i<=ht && j<=lt;i++){
		while(j<=lt && l[j]<h[i]) j++;//找到第一个>h[i]的l[j]（其实也可以用upper_bound）
		if(j<=lt) ans += (h[i]-max(h[i-1],l[j-1]))*(min(h[i+1],l[j+1])-l[j]);//注意先判越界
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc406/submissions/65957193)。

~~赛时是不是没有条件 2 啊？~~

---

## 作者：_xdd_ (赞：1)

前言：C 题一眼秒了，但 B 题因为神秘精度问题炸了。

### 题目大意

定义“波浪线数列 $A$”为满足以下条件的数列：

- 其长度大于等于 $4$。
- $A_1<A_2$。
- 仅存在一个数 $i$ 使 $A_{i-1}<A_i>A_{i+1}$。
- 仅存在一个数 $j$ 使 $A_{j-1}>A_j<A_{j+1}$。
  
给出一个 $1$ 到 $N$ 中整数的排列 $P=(P_1,P_2,…,P_N)$，求其中“波浪线数列”的数量。

### 解题思路

首先处理一下 $P$ 数列，定义 $f_i=P_i-P_{i-1}$，特别的，$f_1=0$（方便后面处理），因为 $P_i$ 的准确值是没有意义的，我们只需要知道相邻数的大小关系。

在 $f$ 数列中，若 $f_i<0$ 则代表 $P_i<P_{i-1}$，$f_i>0$ 则代表 $P_i>P_{i-1}$。

容易发现“波浪线数列”中间有且仅有一段是递减的，也就是在 $f$ 数列中的负数，只要它的前后有至少 $1$ 个正数，就可以确定一段“波浪线数列”。

拿样例 #1 来说，$f=(0,2,3,-2,-2,3)$，中间 $f_4$ 到 $f_5$ 是负数，这一段前面有 $2$ 个正数，也就是说“波浪线数列”前面的部分有 $2$ 种可能：$(1,3,6)$ 或 $(3,6)$，这也是为什么要让 $f_1=0$。这一段后面有 $1$ 个正数，也就是说“波浪线数列”后面的部分有 $1$ 种可能。根据乘法原理，方案数为 $2\times1=2$ 种。

### code

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define r0 return 0
#define inf (0x7fffffff)
#define maxn ( 300000 +5)
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int n,a[maxn],f[maxn],ans;
signed main(){
    cin >> n;
    for(int i=1;i<=n;i++)cin >> f[i],a[i]=f[i]-f[i-1];
    a[1]=0;
    for(int i=1;i<=n;i++)if(a[i]<0){
        int left=i,right;
        for(right=i;a[right+1]<0;right++);
        int cntl=0,cntr=0;
        for(int j=left-1;a[j]>0;j--,cntl++);
        for(int j=right+1;a[j]>0;j++,cntr++);
        ans+=cntl*cntr;
        i=right;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：BennyT (赞：1)

# 题解：AT_abc406_c [ABC406C] ~

## 思路

因为题目中要求恰好有一个 $ A_{i\ -\ 1}\ <\ A_i\ >\ A_{i\ +\ 1} $ 和一个 $ A_{i\ -\ 1}\ >\ A_i\ <\ A_{i\ +\ 1} $，所以我们可以枚举每一个起点，然后求出从该点出发的终点区间长度。

以样例三为例，从第 6 个点出发的终点区间为 $[10,11]$，即为答案中存在两个以 6 为起点的序列，终点为 10 或 11。

那么我们要怎么求这个区间呢？

首先使用 $t_i$ 和 $t2_i$ 分别表示上凸和下凹的前缀和，然后对于每一个满足条件的 $i$ 分别二分起点为 $i$ 的且其中上凸和下凹的数量 $\le 1$ 的区间终点和起点为 $i$ 的且其中上凸和下凹的数量 $\ge 1$ 的区间终点，即为终点区间的起点和终点。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[300010],t[300010],t2[300010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=2;i<n;i++){//求前缀和 
		if(a[i]>a[i-1]&&a[i]>a[i+1])t[i]=1;
		if(a[i]<a[i-1]&&a[i]<a[i+1])t2[i]=1;
		t[i]+=t[i-1];
		t2[i]+=t2[i-1];
	}
	ll ans=0;
	for(int i=2;i<=n;i++){//此处枚举序列中的第二个数（a2） 为起点 
		if(a[i]>a[i-1]){
			int l=i,r=n;
			ll cnt=0;
			while(l<r){//二分终点区间终点 
				int mid=(l+r)>>1;
				if(t[mid-1]-t[i-1]>=1&&t2[mid-1]-t2[i-1]>=1){
					r=mid;
				}
				else{
					l=mid+1;
				}
			}
			if(!(t[l-1]-t[i-1]>=1&&t2[l-1]-t2[i-1]>=1))continue;
			cnt+=n-l;
			l=i;
			r=n;
			while(l<r){//二分终点区间起点 
				int mid=(l+r+1)>>1;
				if(t[mid-1]-t[i-1]<=1&&t2[mid-1]-t2[i-1]<=1){
					l=mid;
				}
				else{
					r=mid-1;
				}
			}
			if(!(t[l-1]-t[i-1]<=1&&t2[l-1]-t2[i-1]<=1))continue;
			cnt-=n-l-1;
			ans+=cnt;
			
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wwwidk1234 (赞：1)

[前往博客园食用更佳（？）](https://www.cnblogs.com/wwwidk1234/p/18881803)

> 对于一个整数序列 $A = (A_1, A_2, \ldots, A_{|A|})$，如果它同时满足以下四个条件，我们称其为**波浪形序列**：
>
> 1. 序列长度 $|A|$ 至少为 $4$。
> 2. 满足 $A_1 < A_2$。
> 3. 存在**唯一**一个整数 $i$（$2 \leq i < |A|$），使得 $A_{i-1} < A_i > A_{i+1}$（这个点即为**波峰**）。
> 4. 存在**唯一**一个整数 $i$（$2 \leq i < |A|$），使得 $A_{i-1} > A_i < A_{i+1}$（这个点即为**波谷**）。
>
> 给定一个排列 $P = (P_1, P_2, \ldots, P_N)$（即 $(1, 2, \ldots, N)$ 的某种排列），求 $P$ 中所有满足波浪形条件的**子串**的数量。

首先我们可以先找出“波峰” 和“波谷” 的位置 $mx_i$ 和 $mn_i$（为了方便，分别在序列最前和最后加一个极大和极小值）。

由题意知，一个波浪形序列的形状可以分成五个部分：**（最远可达上一个波谷）第一次上升→波峰→下降→波谷→第二次上升（最远可达下一个波峰）**。

记 $k$ 为波峰和波谷的数量（显然波峰和波谷的数量必定是相等的），对于每一个 $i(1 < i < k)$，波浪形序列的第一次上升部分可以是 $mn_i \sim mx_i-1$，第二次上升部分可以是 $mn_{i+1} \sim mx_{i+1}$。

在第一和二次上升部分的取值范围内分别找出任意两个下标，就可以组成一种方案。根据乘法原理，当前波峰对答案的贡献就是这两个部分数的个数的乘积。

比如样例三的数据可以画成如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9u94z2an.png)

其中用圆圈圈住的为波峰，用三角形圈住的为波谷。在波峰 $9$ 的左边的 $3,8$ 为第一次上升部分，有 $2$ 个数，在波谷 $2$ 右边的 $10$ 为第二次上升部分，有 $1$ 个数。波峰 $9$ 对答案的贡献就是 $2 \times 1=2$。

[Submission #65914061.](https://atcoder.jp/contests/abc406/submissions/65914061)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=3e5+7;
constexpr int inf=12181218;
int n;
int a[N];
vector<int> mx,mn; //波峰和波谷
inline ll cnt(int l,int r)
{
    return r-l+1;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    a[0]=inf,a[n+1]=-inf;
    for(int i=1;i<=n;i++)
    {
        if(a[i-1]<a[i]&&a[i]>a[i+1]) mx.push_back(i);
        if(a[i-1]>a[i]&&a[i]<a[i+1]) mn.push_back(i);
    }
    int k=mx.size();
    ll ans=0;
    // for(int i=0;i<k;i++) cerr<<mn[i]<<' '<<mx[i]<<'\n';
    for(int i=0;i<k-1;i++)
    {
        // cerr<<mx[i]<<' '<<mn[i]<<' '<<mx[i+1]<<'\n';
        // cerr<<cnt(mn[i],mx[i]-1)<<' '<<(cnt(mn[i+1]+1,mx[i+1]))<<'\n';
        ans+=(cnt(mn[i],mx[i]-1))*(cnt(mn[i+1]+1,mx[i+1]));
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：canwen (赞：0)

个人觉得，论思维难度的话，比 D 难。

## 分析
可以 $O(n)$ 预处理出以下内容，其中 $x$ 要求最小化。

$up_i = x(x > i)$ 使得 $A_{x} > A_{x-1}$，$down_i = x(x>i)$ 使得 $A_x < A_{x-1}$，$up1_i = x(x<i)$ 使得 $A_x > A_{x+1}$。

我们枚举每个小波浪的起点 $1\le i \le n$，需要先满足 $A_i < A_{i+1}$，那么我们只需要判断 $up_{i+1}$ 是否存在且与 $i$ 之间的差大于 $1$（因为至少隔了一个数字）。

大概如下图，那么只需要乘法原理确定左右端点即可（可以根据图自己先实现一下）。

那么时间复杂度是 $O(n)$ 的。

![KYL 好帅！](https://cdn.luogu.com.cn/upload/image_hosting/m0nhh1wv.png)


## Code
```cpp
const int N = 3e5 + 5;
int a[N],n,up[N],down[N];
int up1[N];
void solve(){
	n=in();
	_rep(i,1,n) a[i] = in();
	up[n] = 0;
	_rrep(i,n-1,1){
		if(a[i] < a[i+1]) up[i] = i + 1;
		else up[i] = up[i+1];
	}
	down[n] = 0;
	_rrep(i,n-1,1){
		if(a[i] > a[i+1]) down[i] = i + 1;
		else down[i] = down[i+1];
	}
	up1[1] = 0;
	_rep(i,2,n){
		if(a[i-1]>a[i]) up1[i] = i - 1;
		else up1[i] = up1[i-1];
	}
	int ans = 0;
	_rep(i,1,n-3){
		if(a[i] < a[i+1]){
			int k = up[i+1];
			if(k >= 1 && k <= n && k - (i+1) > 1){
				if(down[k] == 0){
					if(up1[i] == 0) ans += (n-k+1) * i;
					else ans += (n-k+1) * (i-up1[i]);
				}
				else if(up1[i] == 0) ans += (down[k] - k) * i;
				else ans += (down[k] - k) * (i - up1[i]);
			}
		}
	}
	out(ans), pc;
}
```

[Accept record](https://atcoder.jp/contests/abc406/submissions/65898109)。

---

## 作者：LionBlaze (赞：0)

> e <<<<<<<<< c >>>>>>>> d！！
>
> 但好像确实没什么特别难的点。谔谔。难度大约为黄。

我们首先理解题目中的条件。一个序列 $a$ 是波浪形的（参考题目名称 `~`），显然通俗来讲，当且仅当它：

- 刚开始的一小段上升（$a_2>a_1$）。
- 存在且仅存在一个波峰（$a_{i-1}<a_i>a_{i+1}$）。
- 存在且仅存在一个波谷（$a_{i-1}>a_i<a_{i+1}$）。

显然波峰必然在波谷之前。

那么显然我们可以预处理出整个序列的所有波峰或者波谷，然后枚举所有波峰。

接着我们考虑包含这个波峰的波浪形子串需要在哪些地方开始，又需要在哪些地方结尾。答案也是显而易见的：从子串开头到这个波峰没有任何波峰或波谷，而子串结尾位于从这个波峰的下一个波谷开始一直到这个波谷的下一个波峰或者波谷。

![](https://s21.ax1x.com/2025/05/18/pEvD3lT.png)

注意显然的边界条件：显然如果子串的开头/结尾是原串的一个波峰/波谷，则这个地方实际上在子串中不算波峰/波谷。这样数学式子就很容易推出来了。

显然我们可以设 $a,b,c,d$ 分别为上一个波谷的位置，这一个波峰的位置，下一个波谷的位置和下一个波峰的位置，则显然可以选择的位置数量为：

$$ (b-a)(d-c) $$

什么你问 $a,b,c,d$ 怎么获得？显然我们需要预处理出所有波峰和波谷的位置，这样 $b,d$ 可以显然地获得。我们显然还可以用双指针维护 $a,c$，但是如果你不会则显然也可以使用二分查找。

代码。别说我代码写的烂了我赛时这个“一个波峰一个波谷”这个性质导致代码有点烂将就着看吧。

> It works, why?

```cpp
#include <cstdio>
#include <algorithm>


using namespace std;

bool x1[300005], x2[300005];
int X1[300005], X2[300005];
int a[300005];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
	}
	int c1 = 0, c2 = 0;
	for (int i = 2; i < n; i++)
	{
		if (a[i] > a[i - 1] && a[i] > a[i + 1])
		{
			x1[i] = true;
			X1[++c1] = i;
		}
		if (a[i] < a[i - 1] && a[i] < a[i + 1])
		{
			x2[i] = true;
			X2[++c2] = i;
		}
	}
	X2[++c2] = 11451419;
	X1[++c1] = n;
	X1[0] = 1;
	int cur = 1;
	long long sum = 0;
	for (int i = 1; i < c1; i++)
	{
		if (X2[cur] < X1[i]) ++cur;
		if (X1[i + 1] < X2[cur]) continue;
		sum += 1ll * (X1[i + 1] - X2[cur]) * (X1[i] - max(X1[i - 1], X2[cur - 1]));
	}
	printf("%lld\n", sum);
	return 0;
}
```

[sub](https://atcoder.jp/contests/abc406/submissions/65938033)。

---

