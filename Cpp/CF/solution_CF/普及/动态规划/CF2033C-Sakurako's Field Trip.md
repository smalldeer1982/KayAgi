# Sakurako's Field Trip

## 题目描述

Even in university, students need to relax. That is why Sakurakos teacher decided to go on a field trip. It is known that all of the students will be walking in one line. The student with index $ i $ has some topic of interest which is described as $ a_i $ . As a teacher, you want to minimise the disturbance of the line of students.

The disturbance of the line is defined as the number of neighbouring people with the same topic of interest. In other words, disturbance is the number of indices $ j $ ( $ 1 \le j < n $ ) such that $ a_j = a_{j + 1} $ .

In order to do this, you can choose index $ i $ ( $ 1\le i\le n $ ) and swap students at positions $ i $ and $ n-i+1 $ . You can perform any number of swaps.

Your task is to determine the minimal amount of disturbance that you can achieve by doing the operation described above any number of times.

## 说明/提示

In the first example, it is necessary to apply the operation to $ i=2 $ , thus the array will become $ [1, \textbf{2}, 1, \textbf{1}, 3] $ , with the bold elements indicating those that have swapped places. The disturbance of this array is equal to $ 1 $ .

In the fourth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [2, 1, \textbf{2}, \textbf{1}, 2, 4] $ . The disturbance of this array is equal to $ 0 $ .

In the eighth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [1, 4, \textbf{1}, 5, \textbf{3}, 1, 3] $ . The disturbance of this array is equal to $ 0 $ .

## 样例 #1

### 输入

```
9
5
1 1 1 2 3
6
2 1 2 2 1 1
4
1 2 1 1
6
2 1 1 2 2 4
4
2 1 2 3
6
1 2 2 1 2 1
5
4 5 5 1 5
7
1 4 3 5 1 1 3
7
3 1 3 2 2 3 3```

### 输出

```
1
2
1
0
0
1
1
0
2```

# 题解

## 作者：篮网总冠军 (赞：4)

一道简单的 dp 题。

因为每次交换的两个数是固定的，且只对相邻的数有影响，于是我们采取对每个数只枚举其前面的那个即可，枚举这个数换还是不换的最小值即可。

注意，当其是偶数时，最后两数如果相等，交换没有用处，就必须给答案加 $1$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[100005];
int dp[100005][2];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=2;i<=(n+1)/2;i++){
			dp[i][0]=min(dp[i-1][0]+(a[i]==a[i-1])+(a[n-i+1]==a[n-i+2]),dp[i-1][1]+(a[i]==a[n-i+2])+(a[i-1]==a[n-i+1]));
			dp[i][1]=min(dp[i-1][0]+(a[i-1]==a[n-i+1])+(a[i]==a[n-i+2]),dp[i-1][1]+(a[i]==a[i-1])+(a[n-i+1]==a[n-i+2]));
		}
		if (n%2==1)cout<<min(dp[(n+1)/2][0],dp[(n+1)/2][1])<<endl;
		else cout<<min(dp[(n+1)/2][0],dp[(n+1)/2][1])+(a[n/2]==a[n/2+1])<<endl;
	}
	return 0;
}
```

---

## 作者：include13_fAKe (赞：2)

近期看到新增了好多 CF 的题，都开放了题解，来水一篇。

## 思路

看起来像是 $O(\sum n)$ 或者 $O(\sum \log n)$ 的。

以下称长度 $n$ 为奇数的序列的**中心**为 $a_{\frac{n+1}{2}}$，长度 $n$ 的偶数的序列的中心为 $a_{\frac{n}{2}}$ 和 $a_{\frac{n}{2}+1}$。令目前所在的位置为 $p$，称**中心距**（Center Distance，以下简称 $dis$）为 $p$ 与离它较近的中心（如果有两个）的差的绝对值。

简单分析题目要求的交换的规则，发现可以枚举 $dis$。

设序列长度为 $n$，我们来看一下 $n$ 取不同的值时，有多少种不同的中心距。


---

找规律（建议多找几项）可得，$\max dis=\lfloor\frac{n-1}{2}\rfloor$。

然后我们来想一下应该如何计算答案。

当 $n\le 2$ 时，显然不用计算答案。

当 $n=3$ 时，容易发现答案即为 $[a_1=a_2]+[a_2=a_3]$。

当 $n=4$ 时，情况可分类讨论。

当 $a_1=a_2=a_3=a_4$ 时，答案明显为 $3$。

当 $a_1,a_2,a_3,a_4$ 没有任何三个数相同时，答案显然为 $0$，当它们有三个数相同时，无论如何交换，总有两个相同的数相邻，另外两个不同的数相邻，若 $a_2=a_3$，则答案为 $2$，否则答案为 $1$。

然后考虑到，因为是 $a_2$ 和 $a_3$ 交换，所以可以忽略掉 $[a_2=a_3]$ 的判断。故在**忽略掉后**（指忽略掉 $[a_2=a_3]$ 的判断后）当 $a_1,a_2,a_3,a_4$ 中有四个数相等时，答案为 $2$，有三个数相等时，答案为 $1$，否则答案为 $0$。

考虑 $n=6$ 的情况，需要按 $n=4$ 的方法计算 $a_2,a_3,a_4,a_5$ 和 $a_1,a_2,a_5,a_6$。其中需讨论 $[a_3=a_4]$。

$n$ 为更大的偶数的情况依 $n=6$ 的方法类推。

$n=5$ 时可拆开讨论 $a_2,a_3,a_4$ 和 $a_1,a_2,a_4,a_5$。$n$ 为更大奇数的情况以此类推。

实际上 $a_2,a_3,a_4$ 的情况还可以当 $a_2,a_3,a_3,a_4$ 讨论，只是不考虑中间两个数相等的情况。

这种做法启发我们从序列的**中心**往两端统计答案。

首先，若 $n$ 为奇数，则令 $lmid=rmid=\lfloor\frac{n+1}{2}\rfloor$，否则令 $lmid=\frac{n}{2},rmid=lmid+1$。每一次计算 $lmid,lmid-1,rmid,rmid+1$ 四个数值的答案即可。然后每一次 $lmid$ 自加 $1$，$rmid$ 自减 $1$，即每一次的 $dis$ 自加 $1$。

容易得到时间复杂度为 $O(\sum n)$，完全能跑过。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[114514];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int lmid,rmid;
	int include13=0;
	if(n%2){
		lmid=rmid=n+1>>1;
	}
	else{
		lmid=n>>1,rmid=(n>>1)+1;
		if(a[lmid]==a[rmid])	include13++;
	}
//	cout<<lmid<<' '<<rmid<<endl;
	while(lmid>1){
		int x1=a[lmid],x2=a[rmid],x3=a[lmid-1],x4=a[rmid+1];
		if(x1>x2)	swap(x1,x2);
		if(x3>x4)	swap(x3,x4);
//		cout<<x1<<' '<<x2<<' '<<x3<<' '<<x4<<'#'<<lmid<<' '<<rmid<<endl; 
		if(x1==x3&&x2==x4&&x1==x4&&x2==x3)	include13+=2;
		else if((x1==x3&&x1==x4)||(x2==x3&&x2==x4)||(x1==x3&&x2==x3)||(x1==x4&&x2==x4))	include13++;
		lmid--,rmid++;
	}
	cout<<include13<<endl;
	return;
}
int T;
int main(){
	cin>>T;
	while(T--)	solve();
	return 0;
} //你说你会哭 不是因为在乎  
```

[提交记录](https://codeforces.com/contest/2033/submission/289170693)

---

## 作者：jess1ca1o0g3 (赞：2)

## 思路

分享一个非常简单的做法。

从题目中可以知道用双指针，那如何判断是否交换 $a_l$ 和 $a_r$ 呢？对于一对 $l,r$，实际上只需要考虑已经看过的，保证身后的最优，整体就一定最优。如果 $a_l=a_{l-1}$ 或者 $a_r=a_{r-1}$，就可以考虑交换，这样可以使前后的相连的数字分开。最后判一遍相连的个数即可。复杂度 $\mathcal{O(n)}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c,d) for(int a=b;a<=c;a+=d)
#define R(a,b,c,d) for(int a=b;a>=c;a-=d)

using namespace std;
const int N=1e5+5,M=998244353;

void solve();
int T,n,a[N];

signed main(){
  scanf("%d",&T);
  while(T--) solve();
  return 0;
}

void solve(){
  scanf("%d",&n);
  L(i,1,n,1) scanf("%d",a+i);
  int l=2,r=n-1,ans=0;
  while(l<r){
    if(a[l]==a[l-1]||a[r]==a[r+1]) swap(a[l],a[r]);
    l++,r--;
  }
  L(i,1,n-1,1){
    if(a[i]==a[i+1]) ans++;
  }
  printf("%d\n",ans);
}
```

---

## 作者：chenxi2009 (赞：2)

# 思路
分对考虑同学，可以相互交换位置的同学组成一对，发现相邻对之间的同学的相邻关系可以互换（譬如 $1$ 与 $2$ 相邻，$n-1$ 与 $n$ 相邻交换可以变成 $1$ 与 $n-1$ 相邻，$2$ 与 $n$ 相邻）。于是对于每相邻的两对同学都考虑一遍取最小值即可。需要注意中间的一对同学可能互相邻。

时间复杂度为 $O(\sum n)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100001],ans;
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
		}
		for(int i = 2;i <= n - i + 1;i ++){
			ans += min((a[i] == a[i - 1]) + (a[n - i + 1] == a[n - i + 2]),(a[i] == a[n - i + 2]) + (a[n - i + 1] == a[i - 1]));
		}//当前一对同学和前面一对相对相邻的情况两种情况取最小值 
		ans += !(n & 1) && a[n >> 1] == a[(n >> 1) + 1];//需要注意中间的两名同学兴趣相同的情况
		printf("%d\n",ans);
	} 
	return 0;
} 
```

---

## 作者：Sakura_Emilia (赞：1)

# Solution

**只需要分类讨论即可。**

思维题。从两端往中心逐个确定是否要交换。

就是纯条件判断即可，不需要使用什么算法或思想。条件判断比较多，建议老老实实分门别类的讨论每一种情况，这样不容易出错。

根据对称性，左右两个端点处的学生必然不用交换。再来依次考虑位置 $2$ 和 $n-1$ 上的学生是否要交换，这两个位置确定后，再来分析 $3$ 和 $n-2$ 位置上的学生，以此类推，由外向内。

这种方法可以很好的递推，每次只需要考虑当前这一对更外层一对的情况即可。

使用 `i` 和 `int j = n - i + 1;` 来标记当前枚举的一对下标，`lastA = i - 1, lastB = n - (i - 1) + 1;` 为更外层一对的下标。

根据外层的情况，确定内层是否需要交换。每一步都是贪心，尽可能的让当前情况下代价最小。具体的细节可以看下面的代码。

最后特判奇数的情况，以及偶数情况下最内层的一对。因为偶数情况下最内层的一对是直接相邻的。

# Code

```cpp
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;
const int N = 1e6 + 8;

int T, n, lastA, lastB;
int a[N];

inline void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    int ans = 0;
    for(int i = 2; i <= n / 2; i++) {
        int j = n - i + 1;
        lastA = i - 1, lastB = n - (i - 1) + 1;
        if(a[lastA] == a[lastB]) {
            if(a[i] == a[j]) {
                if(a[i] == a[lastA])
                    ans += 2;
            } else {
                if(a[i] == a[lastA])
                    ans++;
                if(a[j] == a[lastB])
                    ans++;
            }
        } else {
            if(a[i] == a[j]) {
                if(a[i] == a[lastA] || a[i] == a[lastB])
                    ans++;
            }
        }
    }

    if(n % 2 == 1) {
        if(a[(n + 1) / 2] == a[(n + 1) / 2 - 1])
            ans++;
        if(a[(n + 1) / 2] == a[(n + 1) / 2 + 1])
            ans++;
    } else{
        if(a[n / 2] == a[n / 2 + 1])
            ans++;
    }

    cout << ans << endl;
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：_Lazy_whr_ (赞：0)

Obviously，这是一道 DP。

因为每次交换的两个数是固定的而，且只对相邻的数有影响，于是我们只需要枚举其前面数，两种转移就是这个数换还是不换的较小值。

注意一个地方：当 $N$ 是偶数时，交换的两个数相同，那么答案就是无意义的，此时答案要加 $1$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define x1 x10
#define y1 y10
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
// #pragma GCC target("avx")
// #pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read () {
		int x = 0, f = 1;
		char ch = getchar ();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar ();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar ();
		}
		return x * f;
	}
	
	template<typename T> inline void read (T &x) {
		x = read ();
		return;
	}
	
	template<typename T,typename... Args> inline void read (T &x,Args &...x_) {
		read (x);
		read (x_...);
		return;
	}
}

namespace Constants {
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = 3.14159265358979323;
}

using namespace std;
using namespace FastIO;
using namespace Constants;

void CLOSE () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
	return;
}

const int N = 1e5 + 10;

int n;
int a[N], dp[N][2];

signed main() {
	CLOSE ();
	int t = read ();
	while (t--)
	{
		read (n);
		for (int i = 1; i <= n; i++) {
			read (a[i]);
		}
		for (int i = 2; i <= (n + 1) >> 1; i++) {
			dp[i][0] = min(dp[i - 1][0] + (a[i] == a[i-1]) + (a[n - i + 1] == a[n - i + 2]), dp[i - 1][1] + (a[i] == a[n - i + 2]) + (a[i - 1] == a[n - i + 1]));
			dp[i][1] = min(dp[i - 1][0] + (a[i - 1] == a[n - i + 1]) + (a[i] == a[n - i + 2]), dp[i - 1][1] + (a[i] == a[i - 1]) + (a[n - i + 1] == a[n - i + 2]));
		}
		if (n & 1) {
			cout << min (dp[(n + 1) >> 1][0], dp[(n + 1) >> 1][1]) << endl;
		} else {
			cout << min (dp[(n + 1) >> 1][0], dp[(n + 1) >> 1][1]) + (a[n >> 1] == a[(n >> 1) + 1]) << endl;
        }
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

一眼 DP。

对于第 $i$ 个第 $n - i + 1$ 个数，只有两种可能：正着或者反着。

设 $dp_{i,j}$ 表示前 $i$ 个数和后 $i$ 个数的干扰数最小值，$j$ 表示上一个是正着放还是反着放。

转移方程分情况讨论，即 $dp_{i,j} = \min(dp_{i - 1,0} + [a[i] = a[i - 1]] + [a[n - i + 1] = a[n - i + 2]]$，其中 $[x]$ 是艾弗森括号，条件成立值为 $1$，不成立值为 $0$。

最后的答案如果 $n$ 是偶数，还要统计 $a[\frac{n}{2}]$ 是否等于 $a[\frac{n}{2} + 1]$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
int t,n,ans;
int a[N],dp[N][2];
void solve(){
	cin >> n;
	if (n == 1){
		cout << 0 << endl;
		return;
	}
	for (int i = 1 ; i <= n ; i++){
		cin >> a[i];
	}
	int w = (n + 1) / 2;
	for (int i = 2 ; i <= w ; i++){
		dp[i][0] = min(dp[i - 1][0] + (a[i] == a[i - 1]) + (a[n - i + 1] == a[n - i + 2]),dp[i - 1][1] + (a[i] == a[n - i + 2]) + (a[n - i + 1] == a[i - 1]));
		dp[i][1] = min(dp[i - 1][0] + (a[n - i + 1] == a[i - 1]) + (a[i] == a[n - i + 2]),dp[i - 1][1] + (a[n - i + 1] == a[n - i + 2]) + (a[i] == a[i - 1]));
	}
	if (n & 1) cout << min(dp[w][0],dp[w][1]) << endl;
	else cout << min(dp[w][0],dp[w][1]) + (a[n / 2] == a[n / 2 + 1]) << endl;
}
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：K_J_M (赞：0)

# Sakurako's Field Trip
## 题目描述
老师让学生排成一列，每个学生的兴趣主题是 $a_i$。干扰是相邻学生兴趣相同的对数，即满足 $a_j=a_{j+1}$ 的情况数（$1\le j<n$）。
你可以选择任意学生位置 $i$，将其与位置 $n-i+1$ 的学生交换，操作次数不限。
任务是通过这些交换操作，计算队伍中最小的干扰数。
## Solution
考虑 dp 。由于每一次交换只对 $i$ 和 $n-i+1$ 有影响，所以可以只对一半进行 dp。设 $dp_{i,0}$ 表示对 $i$ 和 $n-i+1$ 进行 $0$ 操作的最小干扰数， $dp_{i,1}$ 表示对 $i$ 和 $n-i+1$ 进行 $1$ 操作的最小干扰数。值得注意的是，我们从中间位置往两边 dp。那么 dp 方程为
$$\begin{cases}
dp_{i,0}=\min{\begin{cases} dp_{i+1,0}+[a_i=a_{i+1}]+[a_{n-i+1}=a_{n-i}]\\ dp_{i+1,1}+[a_i=a_{n-i}]+[a_{n-i+1}=a_{i+1}] \end{cases}}\\
dp_{i,1}=\min{\begin{cases} dp_{i+1,0}+[a_{n-i+1}=a_{i+1}]+[a_{i}=a_{n-i}]\\ dp_{i+1,1}+[a_i=a_{i+1}]+[a_{n-i+1}=a_{n-i}] \end{cases}}
\end{cases}$$
初始值分为两种，如果 $n$ 为奇数，那么 $dp_{(n-1)/2+1,0}=dp_{(n-1)/2+1,1}=0$，若 $n$ 为偶数，那么 $dp_{n/2,0}=dp_{n/2,1}=[a_{n/2}=a_{n/2+1}]$，其他情况为 $∞$。最终答案为 $\min(dp_{1,0},dp_{1,1})$。时间复杂度为 $\mathcal O(n)$。\
[Ac Code](https://www.luogu.com.cn/paste/fac70r3y)

---

## 作者：splendore (赞：0)

实际上，是否交换 $i$ 与 $n-i+1$ 对后继交换并无影响，所以只要每次求交换与不交换的最小值即可。

最中间的间隔可能遗漏，需要特判。

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int a[N];
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	int ans=0;
	for(int i=2,j=n-1;i<j;++i,--j){
		int x=int(a[i-1]==a[i])+int(a[j]==a[j+1]);
		int y=int(a[i-1]==a[j])+int(a[i]==a[j+1]);
		ans+=i==n-i+1?(a[i+1]==a[i]):min(x,y);
	}
	printf("%d\n",ans+(n&1?(a[n>>1]==a[(n+1)>>1])+(a[(n+1)>>1]==a[(n+3)>>1]):(a[n>>1]==a[n/2+1])));
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：sintle (赞：0)

## 题目链接

- [洛谷 CF2033C Sakurako's Field Trip](https://www.luogu.com.cn/problem/CF2033C)

## 解题思路

因为可以随便转换，所以每对点的交换是对其他点对没有任何影响的。

所以考虑贪心，对于每个点对想办法减少代价。

设两个点分别为 $i,j$（$i+j-1=n$）,

故一定产生代价的情况可以分成以下四种：

1. $a_i=a_j$ 且 $a_i=a_{i+1}$ 或 $a_i=a_{j-1}$（产生 $1$ 的代价）

2. $a_i=a_j=a_{i+1}=a_{j-1}$（产生 $2$ 的代价）

3. $a_{i+1}=a_{j-1}$ 且 $a_i=a_{i+1}$ 或 $a_j=a_{i+1}$（产生 $1$ 的代价）

最后特判中间两个人会不会产生代价，这道题就这么做完了~

## 参考代码

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;

int T , n , a[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while(T--)
    {
        cin >> n;
        for(int i = 1 ; i <= n ; i++)
        {
            cin >> a[i];
        }
        int ans = 0;
        for(int i = 1 ; i <= (n - 1) / 2 ; i++)
        {//第二种情况会被前后各判一次，故不需要特判
            if(a[i + 1] == a[n - i])
            {
                if(a[i] == a[i + 1] || a[n - i + 1] == a[i + 1])
                {
                    ans++;
                }
            }
            if(a[i] == a[n - i + 1])
            {
                if(a[i] == a[i + 1] || a[i] == a[n - i])
                {
                    ans++;
                }
            }
        }
        if(n % 2 == 0 && a[n / 2] == a[n / 2 + 1])
        {
            ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

