# Make Equal Again

## 题目描述

You have an array $ a $ of $ n $ integers.

You can no more than once apply the following operation: select three integers $ i $ , $ j $ , $ x $ ( $ 1 \le i \le j \le n $ ) and assign all elements of the array with indexes from $ i $ to $ j $ the value $ x $ . The price of this operation depends on the selected indices and is equal to $ (j - i + 1) $ burles.

For example, the array is equal to $ [1, 2, 3, 4, 5, 1] $ . If we choose $ i = 2, j = 4, x = 8 $ , then after applying this operation, the array will be equal to $ [1, 8, 8, 8, 5, 1] $ .

What is the least amount of burles you need to spend to make all the elements of the array equal?

## 样例 #1

### 输入

```
8
6
1 2 3 4 5 1
7
1 1 1 1 1 1 1
8
8 8 8 1 2 8 8 8
1
1
2
1 2
3
1 2 3
7
4 3 2 7 1 1 3
9
9 9 2 9 2 5 5 5 3```

### 输出

```
4
0
2
0
1
2
6
7```

# 题解

## 作者：vectorxyz (赞：2)

#### 题目大意
每次选择一个区间 $l$ 和 $r$，将区间内所有数加上 $k$，问最后要操作多少次使得所有数相等。

#### 题目分析
我们令 $l$ 为左边起不需要修改的区间，即 $a_1$ 到 $a_l$ 这些数相等，定义 $r$ 为右边起不需要修改的区间。然后分三种情况讨论。

把 $l+1$ 到 $n$ 修改成 $1$ 到 $l$ 的数，修改次数是 $n-l$；把 $1$ 到 $r - 1$ 修改成 $r$ 到 $n$ 的数，修改次数是 $r - 1$；如果 $a_1 = a_n$，那么就把中间的数修改成 $a_1$，修改次数是 $r - l+ 1$。

最后将以上三种情况去 $\min$ 就行了。

#### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N];

signed main()
{
    int T;
    cin >> T;
    while(T -- ){
        int n, ans = LONG_LONG_MAX;
        cin >> n;
        for(int i = 1;i <= n;i ++) cin >> a[i];
    
        int l = 1,r = n;
        
        while(l + 1 <= n && a[l + 1] == a[l]) l ++;
        while(r - 1 >= 1 && a[r - 1] == a[r]) r --;
        
        if(a[1] == a[n]) {
            ans =  min(ans, max(r - l - 1,(long long)0));
        }
        ans = min(min(n - l, r - 1), ans);
        
        cout << max((long long)0, ans) << endl;
    }
    return 0;
}
```
#### 后记
赛事一开始把他看成区间动规了（擦汗）。

[记录](https://www.luogu.com.cn/record/146918151)。


---

## 作者：RyanLi (赞：2)

传送门：洛谷 [Make Equal Again](https://www.luogu.com.cn/problem/CF1931C) | Codeforces [C. Make Equal Again](https://codeforces.com/contest/1931/problem/C)

更佳的阅读体验：[CF1931C 题解](https://blog.ryanli.top/index.php/archives/34/)

---

**简要题意**：给定一个有 $n$ 个整数的序列 $a$，可以进行**最多一次**操作，使 $a_i$ 到 $a_j$ 全部变为 $x$，代价为 $j - i + 1$。求使序列中所有元素相等的最小代价。

注意到，题目中给定了**最多一次**操作，因此如果序列所有元素不相等，我们必须只用一次操作将整个序列所有元素变为相等。因此，序列中最终的元素一定是 $a_1$ 或 $a_n$。

有了上述结论，我们只要维护 $a_1$ 和 $a_n$ 连续出现的个数即可。如果 $a_1 = a_n$，那么只要取中间的区间长度即可，否则在两侧的区间长度取最小值即可。

```cpp
#include <iostream>
using namespace std;

const int N = 2e5 + 10;
int t, n, a[N], l, r;

int main() {
    scanf("%d", &t);
    while (t--) {
        l = r = 1;
        scanf("%d%d", &n, &a[1]);
        for (int i = 2; i <= n; ++i) {
            scanf("%d", &a[i]);
            if (a[i] == a[i - 1] && l == i - 1) l = i;  // 更新左端点
            if (a[i] != a[i - 1]) r = i;  // 更新右端点
        } if (a[1] == a[n]) printf("%d\n", max(r - l - 1, 0));
        else printf("%d\n", min(n - l, r - 1));
    } return 0;
}
```



---

## 作者：IANYEYZ (赞：1)

感觉做过，原因未知。

简单模拟题.

先找到最大的 $l$ 使得 $a_i = a_1$ 对所有的 $1 \leq i \leq l$ 成立。

再找到最小的 $r$ 使得 $a_i = a_n$ 对所有的 $r \leq i \leq n$ 成立。

随后如果 $a_1 = a_n$ 那么答案就是 $n - (l + n - r + 1)$。

否则就是 $n - \max\{l, n - r +1\}$。

代码（自行忽略 `debug` 库）：

```cpp
#include <iostream>
#ifndef ONLINE_JUDGE
#include "../../../debug.hpp"
#else
#define debug(...)
#define debugArr(...)
#endif
using namespace std;
int a[200010],t,n;
int main()
{
	cin >> t;
	loop:while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		a[n + 1] = 0;
		a[0] = 0;
		int l = 1,r = n;
		while (a[l] == a[1]) l++;
		l--;
		while (a[r] == a[n]) r--;
		r++;
		if (l == n || r == 1) {
			cout << 0 << "\n";
			goto loop;
		}
		int res = max(l, max(n - r + 1, (a[1] == a[n] ? l + n - r + 1 : 0)));
		debug(l,r,res);
		cout << n - res << "\n";
	}
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

因为只能进行一次操作，所以一定选择了中间的某一段（也可能包含左端点或者右端点）。

当 $a_1=a_n$ 时，最优操作就是选择不包含左侧连续相同和右侧连续相同的一段。

当 $a_1\not = a_n$ 时，最优操作就是选择不包含左侧连续相同或右侧连续相同的一段。

所以我们只需要统计左侧最长连续相同有多长，和右侧最长连续相同有多长。

然后讨论 $a_1$ 是否等于 $a_n$ 即可。

需要注意特判全相同的情况。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005],pr,sf;
inline void sol()
{
	scanf("%d",&n),pr=sf=1;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),pr+=(i>1&&pr==i-1&&a[i]==a[i-1]);
	for(int i=n-1;i;--i) if(a[i]==a[i+1]) ++sf;else break;
	printf("%d\n",(a[1]==a[n])?max(0,n-pr-sf):min(n-pr,n-sf));
}
int main()
{
	scanf("%d",&T);
	while(T--) sol();
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

## Make Equal Again

### Description

有一个长为 $n$ 的序列 $a$，你可以进行至多一次操作：选择 $i,j,x$ 满足 $1\le i\le j\le x$，使 $[i,j]$ 覆盖为 $x$。问使序列所有元素相同的最小的 $j-i+1$。

### solution

最终序列的每一个元素的值只能是 $a_1$ 或 $a_n$。先以 $a_1$ 计算，找出第一个和 $a_1$ 不相同的位置 $l$、最后一个和 $a_1$ 不相同的位置 $r$，更新答案为 $r-l+1$。$a_n$ 同理。

### [code](https://codeforces.com/contest/1931/submission/246350034)

---

## 作者：无名之雾 (赞：0)

# Make Equal Again 题解

~~超级大水题，然而我还是因为细节挂了一发~~

## 题意

给定一个长度为 $n$ 的数组 $a$，我们要进行一次操作，选择 $i,j,k$ 使得 $[1,j]$ 覆盖范围为 $x$。求最小的 $j-i+1$。

## 思路

思考一下，不难发现，最终序列的值只能都变成 $a_1$ 或 $a_n$，所以我们只需要线记住第一个与 $a_1$ 不相同的 $l$，最后一个与 $a_1$ 不相同的 $r$，更新答案即可。$a_n$ 同理。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],sum[200005];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main(){
	int t=read();
	while(t--){
		int ma1=0,man=0;
		int n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++){
			if(a[i]==a[1])ma1++;
			else break;
		}
		for(int i=n;i>=1;i+=-1){
			if(a[i]==a[n])man++;
			else break;
		}
		int ans=ma1+man;
		if(a[1]==a[n])cout<<n-min(ans,n)<<"\n";
		else cout<<n-min(max(man,ma1),n)<<"\n";
	}
	return 0;
}

```

---

## 作者：__Dist__ (赞：0)

~~应该没有人像我一样没看见**只能操作至多1次吧**~~

- 如果 $a$ 中所有元素相同，答案为 $0$。

- 否则：

	- 记 $p$ 为 $a$ 的由相同元素组成的最长前缀的长度。
    
    - 记 $q$ 为 $a$ 的由相同元素组成的最长后缀的长度。
    
    - 然后分两种情况讨论：
    
    	1. $a_1 = a_n$，答案为 $n - p - q$。相当于把两边的元素排除掉不操作，把中间那一部分不相同的进行操作。
        
        2. 否则，答案为 $\min(n-p,n-q)$。相当于把排除掉一边的不操作，把剩下进行操作。

为什么要这么做呢？因为至多只能操作 $1$ 次，我们需要让操作的区间尽可能小，花费才尽可能小。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 5;

int n;
int a[MAXN];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	if(n == 1) {
		cout << 0 << '\n';
		return;
	}
	if(a[1] != a[n]) {
		int ans = INT_MAX;
		int i = 1;
		while(a[i] == a[i + 1] && i + 1 <= n) i++;
		ans = n - i;
		i = n;
		while(a[i] == a[i - 1] && i - 1 >= 1) i--;
		ans = min(ans, i - 1);
		cout << ans << '\n';
	}
	else {
		int i = 1;
		while(a[i] == a[i + 1] && i + 1 <= n) {
			i++;
		}
		int j = i;
		if(i == n) {
			cout << 0 << '\n';
			return;
		}
		i = n;
		while(a[i] == a[i - 1] && i - 1 >= 1) i--;
		i = n - i + 1;
		cout << n - j - i << '\n';
	}
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

注意只能操作一次，开始没看到迷惑了好久。我们可以分两种讨论，一种是数列前后相同，那直接前后分别找最长的连续串，中间剩下的就是答案。否则在操作 $(1,x)$ 和 $(x,n)$ 种决策一种。

上面我也不知道在说什么。总结一下，其实就是先分别从前后最长的连续串，这两个串定为不变串的代价是 $n$ 减长度，取小值即可。特殊的，假如两端相同，答案是 $n$ 减两串的长度。

```cpp
void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int pre = 1; a[n + 1] = -1;
	for (int i = 1; i <= n; i++) 
		if (a[i] != a[i + 1]) {
			pre = i;
			break;
		}
	int suf = n; a[0] = -1;
	for (int i = n; i >= 1; i--) 
		if (a[i] != a[i - 1]) {
			suf = i;
			break;
		}
	suf = (n - suf + 1);
	if (a[1] == a[n]) cout << max(0, n - pre - suf);
	else cout << min(n - pre, n - suf);
	cout << '\n';
}
```

---

## 作者：2021sunzishan (赞：0)

## 题目大意:
给定 $n$ 个整数，进行一次操作使区间 $l\sim r$ 的值都变为一个任意值，代价为 $r-l+1$。问使这 $n$ 个数都相同的最小代价是多少。

## 思路：
注意此题只能操作一次。

分别从后和从前遍历连续的数的个数，下面就分情况讨论。
1. 前后连续的数相同，只需要改中间的数。

2. 若不同，哪个连续的长就保留哪个，再修改剩下的数。

以上就是思路了，看不懂就看看代码吧。

**切勿抄袭！！！**

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
int t,n;
int a[N];
inline int read(){//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		int s1=1,s2=1,k1=a[1],k2=a[n];
		//s1统计从前面的最大连续长度，k1是从前面的连续数是哪一个，s2,k2是从后面的
		for(int i=2;i<=n;i++)//从前
			if(a[i]==a[i-1])
				s1++;
			else
				break;
		for(int i=n-1;i>=1;i--)//从后
			if(a[i]==a[i+1])
				s2++;
			else
				break;
		if(k1==k2)//相等
			printf("%d\n",max(0,n-s1-s2));//可能全是一个值，就小于0了，剩下的改
		else
			printf("%d\n",n-max(s1,s2)); //取max，剩下的都要改
	}
	return 0;
}
```
完结~

---

## 作者：minVan (赞：0)

**题目大意**

你需要选定一个区间 $[l,r]$，将 $a_l,a_{l+1},\cdots,a_r$ 均赋值为 $x$，代价为 $r-l+1$，问将 $a_1$ 至 $a_n$ 全部相等的最小代价为多少。

**解题思路**

考虑最大的 $i$，使得 $a_1=a_2=\cdots=a_i$，长度为 $c_1=i$；考虑最小的 $i$，使得 $a_i=a_{i+1}=\cdots=a_n$，长度为 $c_2=n-i+1$。

若 $a_1=a_n$，则前缀后缀均可忽略掉，总代价为 $\max\{0,n-c_1-c_2\}$；否则只能忽略掉一个，总最小代价为 $n-\max\{c_1,c_2\}$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int i = 2, c1 = 1, c2 = 1;
    while(i <= n && a[i] == a[i - 1]) {
      ++c1, ++i;
    }
    i = n - 1;
    while(i >= 1 && a[i] == a[i + 1]) {
      ++c2, --i;
    }
    if(a[1] == a[n]) {
      cout << max(0ll, n - c1 - c2) << '\n';
    } else {
      cout << min(n - c1, n - c2) << '\n';
    }
  }
  return 0;
}
```

---

## 作者：__Octhyccc__ (赞：0)

题意简述：有 $n$ 个数，你可以选择一个区间 $l,r$（区间包含 $l,r$，也可以不选，不选代价为 $0$），令代价为 $r-l+1$，将区间内部的元素变为任意整数，求代价的最小值，多组数据。

现从前往后扫一遍，到这个数不等于开头的数为止，在从后往前扫一遍，方法同上，令这两个数的值为 $a_1,a_2$。

这么做是因为要尽量让 $l$ 变大，$r$ 变小，用更小的代价。

然后看一下开头和结尾是否相等，相等的话把 $a_1,a_2$ 加起来（因为头和尾相等的话这个区间两边都可以缩小），但是结果有可能大于 $n$，所以 $ans=\min(a_1+a_2,n)$。

否则的话头和尾不相等，为了使代价最小，取最大值。即 $ans=\max(a_1,a_2)$。

输出 $ans$ 即可，别忘了多测清空变量。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[200000],cnt;
int main(){
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		int cnt1=1,cnt2=1;
		for(int i=1;i<n;i++){
			if(a[i]==a[i-1])cnt1++;
			else break;
		}
		for(int j=n-2;j>=0;j--){
			if(a[j]==a[j+1])cnt2++;
			else break;
		}
		if(a[0]==a[n-1]){
			cnt1+=cnt2;
			if(cnt1>n)cnt1=n;
		}
		else cnt1=max(cnt1,cnt2);
		printf("%d\n",n-cnt1);
		cnt1=0,cnt2=0;
	}
	return 0;
}
```

---

## 作者：wyyqwq (赞：0)

题意：给出长度为 $n$ 的序列，进行一次覆盖操作，操作的代价为区间的长度，求将这个序列变为所有数相同的代价。

不难看出肯定是把中间的某一段覆盖掉，所有从两头分别找最长的数字相同的前缀和后缀即可。

```c++
void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	int l = 1, r = n + 1;
	while(l + 1 <= n && a[l + 1] == a[l] && l <= r) l ++;
	while(r - 1 >= 1 && a[r - 1] == a[1] && l <= r) r --;
	int ans = (r - l - 1);
	l = 0, r = n;
	while(r - 1 >= 1 && a[r - 1] == a[r] && l <= r) r --;
	while(l + 1 <= n && a[l + 1] == a[n] && l <= r) l ++;
	cout << max(0, min(ans, r - l - 1)) << endl;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 题意
题意挺简单，就是说你可以改变 $a_i$ 到 $a_j$ 使得所有数字相同，但你需要付出代价 $j - i + 1$，当然你也可以选择不改变。
### 思路
把前面有几个数字连在一起记在一个变量 $lq$ 里。然后从后面开始遍历，如果 $a_n$ 等于前面连 $a_1$ 表示，后面连的数字和前面连的数字一样，那么继续遍历每发现一个 $a_i$ 和 $a_1$ 相同，那么 $lq$ 加一，直到不相同位置。如果 $a_n$ 不等于 $a_1$，那么把后面有几个数字连在一起记在一个变量 $lh$ 里。最后输出 $n$ 减去 $lq$ 和 $lh$ 的最大值。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[200005];

signed main()
{
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int j;
		bool xiang = true;
		cin >> a[1];
		int ji = a[1];
		for(int i = 2; i <= n; i++){
			cin >> a[i];
			if(a[i] != ji){
				xiang = false;
			}
		}
		if(xiang){
			cout << 0 << endl;
			continue;
		}
		int lq = 1;
		for(int i = 2; i <= n; i++){
			if(a[i] == a[1]){
				lq++;
			}
			else{
				break;
			}
		}
		int lh = 0;
		if(a[n] == a[1]){
			for(int i = n; i >= 1; i--){
				if(a[i] == a[1]){
					lq++;
				}
				else{
					break;
				}
			}
		}
		else{
			lh = 1;
			for(int i = n - 1; i >= 1; i--){
				if(a[i] == a[n]){
					lh++;
				}
				else{
					break;
				}
			}
		}
			cout << n - max(lq, lh) << endl;
	}
	return 0;
}
```


---

