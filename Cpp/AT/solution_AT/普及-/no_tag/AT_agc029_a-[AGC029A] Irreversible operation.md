# [AGC029A] Irreversible operation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc029/tasks/agc029_a

$ N $ 個のオセロの石が一列に並んでいます。 それぞれの石の状態は長さ $ N $ の文字列 $ S $ によって表されており、 $ S_i= $`B` のとき左から $ i $ 番目の石の表面は黒色、 $ S_i= $`W` のとき左から $ i $ 番目の石の表面は白色となっています。

ここで、以下の操作を行うことを考えます。

- 左から $ i $ 番目の石の表面が黒色、左から $ i+1 $ 番目の石の表面が白色であるような $ i $ ($ 1\ \leq\ i\ <\ N $) を一つ選び、 その $ 2 $ つの石をともに裏返す。つまり、左から $ i $ 番目の石の表面が白色、左から $ i+1 $ 番目の石の表面が黒色になるようにする。

最大で何回この操作を行うことができるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 2\times\ 10^5 $
- $ S_i= $`B` または `W`

### Sample Explanation 1

以下のようにして $ 2 $ 回の操作を行うことができます。 - 左から $ 2 $ 番目、$ 3 $ 番目の石を裏返す。 - 左から $ 1 $ 番目、$ 2 $ 番目の石を裏返す。

## 样例 #1

### 输入

```
BBW```

### 输出

```
2```

## 样例 #2

### 输入

```
BWBWBW```

### 输出

```
6```

# 题解

## 作者：CQ_Bab (赞：7)

# 思路
这道题其实就是一道求逆序对的题，若交换一次那就可以消除一个逆序对，而题目中说了必须要是 $S_i=\texttt{B}$ 且 $S_i+1=\texttt{W}$ 才能交换，那就可以倒着遍历每次遇到 $\texttt{W}$ 就将 $x$ 加一，否则将答案加上 $x$（因为你每次交换后连续都有一段 $\texttt{W}$ 那就可以一直交换）仔细想一想，每个字母 $\texttt{W}$ 到达其最左边的交换次数其实就是它前面 $\texttt{B}$ 字母的个数，这不就是求逆序对的个数吗?

# AC 代码
```
#include<bits/stdc++.h>
#define int long long // 十年OI一场空，不开long long 见祖宗 
using namespace std;
int B,W;
string s;
signed main(){
	cin>>s;
	for(int i=s.size()-1;i>=0;i--){ // 倒着遍历 
		if(s[i]=='W') W++; // 累加 
		else B+=W; // 加入答案 
	}
	cout<<B<<endl; // 输出 
	return false;
}

```

[AC 记录](https://www.luogu.com.cn/record/86337862)

---

## 作者：_acat_ (赞：3)

## 题目大意

给定一个长度为 $N$ 的字符串 $s$，仅包含字符 `W` 和 `B`。

每次操作可以选定 $s_i=$ `B` 且 $s_{i+1}=$ `W`，交换它们的颜色。

问最多能操作几次。

## Sol

本题只有两个不同字母，每次交换这两个字母相当于减少了一组逆序对。所以可较换次数就是这个**字符串的逆序对数量**。

可以通过记录当前位置之前 `B` 的数量为 `cntB`，遇到 `W` 则 `ans+=cnt`, 遇到 `B` 则 `cnt++`。

注：十年 OI 一场空，**不开 `long long` 见祖宗**。（懂得都懂）

代码就不给了，自己写吧。

---

## 作者：Fr0sTy (赞：2)

这道题与 [CF353D Queue](https://www.luogu.com.cn/problem/CF353D) 比较像，但后者更难一些，可以试试看。



### 题意简述
------------

给定一个字符串 $s$。使所有字母 $W$ 都在左边时最少交换几次。

### 解题思路
------------

当然可以枚举每个字母 $W$ 的情况，但显然会超时。

仔细想一想，每个字母 $W$ 到达其最左边的交换次数其实就是**它前面** $B$ **字母的个数**。

于是就 AC 了。 时间复杂度 $O(n)$。

哦对了，你还要开 `long long`。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
string str; long long sum_b,ans;
int main() {
	cin>>str;
	for(int i=0;i<str.size();i++) {
		if(str[i]=='B') sum_b++;
		if(str[i]=='W') ans+=sum_b;
	}
	printf("%lld",ans);
	return 0;
}
//code by TheCedar
```

---

## 作者：Leasier (赞：1)

本题实际上是在求逆序对。

设 $W = 0$、$B= 1$，则只要还存在逆序对，就一定可以交换。

你当然可以用归并排序 / 树状数组求逆序对，但由于本题实际只有两种数，所以可以遍历 $S$，遇到 `B` 则 `t += 1`，遇到 `W` 则 `ans += t`。

代码：
```cpp
#include <stdio.h>
#include <string.h>

typedef long long ll;

char s[200007];

int main(){
	int len, t = 0;
	ll ans = 0;
	scanf("%s", s);
	len = strlen(s);
	for (int i = 0; i < len; i++){
		if (s[i] == 'B'){
			t++;
		} else {
			ans += t;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Buried_Dream (赞：0)

## 题意：

给你一个字符串 $S$， 如果 $S_i$ 为 `B` 同时 $S_{i + 1}$ 为 `W`，则可以交换 $S_i, S_{i + 1}$，问最多进行几次这样的操作。

## 思路：

对于每个 `w`，都会和前面的 `B` 去交换一次，所以可以将这个题转换成求逆序对，所以就统计每个 `W` 前面到底有多少个 `B` 就可以了。

我们设 $Sum_i$ 表示第 $i$ 位前面的 `B` 的个数 (保证 $s_i$ 为 `W`)。

答案就是：

$ans = \sum_{i = 1}^{strlen(s)}Sum_i$。

## Ac code:

```cpp

/*
work by: TLE_Automation
Time: O(轻轻松松过)
knowledge: 垃圾算法
*/
#include<bits/stdc++.h>
#define il inline
#define re register
#define Orz puts("Szt Lps Fjh AK IOI!");
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;

const int INF = 1e9 + 7, mod = 1e9 + 7;
const int maxn = 2e5 + 10, MAXN = 3e3 + 10, N = 1e6 + 10;

namespace IO {
inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}
int ksm(int a, int b, int mod) {
	int base = a, res = 1;
	while(b) {
		if(b & 1) res = (res * base) % mod;
		base = (base * base) % mod, b >>= 1;
	}return res % mod;
}
int Gsc(int a, int b, int mod) {
	int base = a, res = 0;
	while(b) {
		if(b & 1) res = (res + base) % mod;
		base = (base + base) % mod, b >>= 1;
	}return res % mod;
}

inline int read() {
	int s = 0, w = 1;char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}}

using namespace IO;

char s[N];
int ans = 0, len, cnt;
bool check() {
	for(int i = 1; i < len; i++) {
		if(s[i] == 'B' && s[i + 1] == 'W') return false;
	}  return true;
} 

signed main() {
	int tests = 1; 
	while(tests--) {
	cin >> (s + 1);
	len = strlen(s + 1);
	for(int i = 1; i <= len; i++) {
		if(s[i] == 'B') cnt++;
		else ans += cnt;
	}
		cout << ans;		
	}
}
```

$$The\ End.$$

---

## 作者：Ezio__Auditore (赞：0)

## AT4500 [AGC029A] Irreversible operation
[[Statment]](https://www.luogu.com.cn/problem/AT4500)

$Date:\ Dec.\ 2nd$

---
#### 题意：
 &emsp;&emsp;给定长度为 $n$ 且只包含 'B'，'W' 字符串 $s$，当存在 相邻的 "BW" 时，你可以交换 "BW" 为 "WB"， 问最多能交换多少次。
 
---
#### 思路：
&emsp;&emsp;令 'B' = 1，'W' = 0，每次交换 "BW" 相当于减少了一组逆序对
。可以发现总共可较换次数就是**逆序对数量**。 
  - 简单理解: 如果还存在逆序对，由于只有 'B'，'W' 两种字符，所以一定存在相邻的 "BW" 可以交换。
  
  ~~没错我就是逆序对狂魔~~
  
#### 具体实现：
&emsp;&emsp;显然我们可以用归并排序或者树状数组求逆序对。

&emsp;&emsp;但是本题只有两个不同数字, 可以通过记录当前位置之前 'B' 的数量为 $cntB$，遇到 $W$ 则 $ans$ += $cntB$, 遇到 $B$ 则 $cntB$++。 
  
&emsp;&emsp;**故可以 $O(n)$ 求解。**

P.S. 本题 $n$ 比较大， 统计答案请开 long long。


### Code: 
---
(Merge Sort 版本)

---

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

const int kMaxN = 2e5 + 5;
char input[kMaxN];
int a[kMaxN];
typedef long long ll;
ll ans;
void merge_sort(int l, int r) { // 归并排序求逆序
  if (l == r) return ;
  static int tmp[kMaxN], h1, h2;
  int mid = (l + r) >> 1;
  merge_sort(l, mid);
  merge_sort(mid + 1, r);
  h1 = l, h2 = mid + 1;
  for (int i = l; i <= r; i++) {
    if ((a[h1] <= a[h2] || h2 > r) && h1 <= mid)
      tmp[i] = a[h1++];
    else
      tmp[i] = a[h2++], ans += mid - h1 + 1;
  }
  for (int i = l; i <= r; i++) a[i] = tmp[i];
}
int main() {
  std::cin >> (input + 1);
  int n = strlen(input + 1);
  for (int i = 1; i <= n; i++)
    a[i] = input[i] == 'B';
  merge_sort(1, n);
  printf("%lld\n", ans);
}

```
---
( $O(n)$ 处理版本)

---
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

const int kMaxN = 2e5 + 5;
char input[kMaxN];
typedef long long ll;
ll ans;
int main() {
  std::cin >> (input + 1);
  int n = strlen(input + 1);
  int cntB = 0;
  for (int i = 1; i <= n; i++) {
    if (input[i] == 'B') cntB++;
    else ans += cntB;
  }
  printf("%lld\n", ans);
  return 0;
}
```

---

## 作者：火车司机 (赞：0)

## 简要分析

最后的终止状态一定是所有的 "W" 都在所有的 "B" 前面，否则必然还可以继续交换

因此每个 "W" 都会与在原序列中在它之前的所有的 "B" 交换一次

直接 $O(n)$ 统计即可

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int n, ans;
char s[200005];
signed main()
{
	scanf("%s", s), n = strlen(s);
	for (ri i = 0, cnt = 0; i < n; ++i)
		if (s[i] == 'B')
			++cnt;
		else
			ans += cnt;
	printf("%lld\n", ans);
	return 0;
}
```


---

