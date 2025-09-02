# [ABC032C] 列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc032/tasks/abc032_c

 長さ $ N $ の非負整数列 $ S={s_1,s_2,...,s_N} $ と整数 $ K $ があります。 あなたの仕事は、以下の条件を満たす $ S $ の **連続する** 部分列のうち、最も長いものの長さを求めることです。部分列の長さは $ 1 $ 以上の列でないといけません。

- その部分列に含まれる全ての要素の値の積は、$ K $ 以下である。

もし条件を満たす部分列が一つも存在しないときは、$ 0 $ を出力してください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。満点は $ 100 $ 点である。

- $ N≦1000 $ を満たすデータセット $ 1 $ に正解した場合は、$ 20 $ 点が与えられる。
- 追加制約のないデータセット $ 2 $ に正解した場合、上記の点数に加え $ 80 $ 点が与えられる。

### Sample Explanation 1

部分列 $ S[2..5]=s_2,s_3,s_4,s_5 $ を選ぶと、積は $ 3×1×1×2=6 $ となり、$ K $ 以下になります。

## 样例 #1

### 输入

```
7 6
4
3
1
1
2
10
2```

### 输出

```
4```

## 样例 #2

### 输入

```
6 10
10
10
10
10
0
10```

### 输出

```
6```

## 样例 #3

### 输入

```
6 9
10
10
10
10
10
10```

### 输出

```
0```

## 样例 #4

### 输入

```
4 0
1
2
3
4```

### 输出

```
0```

# 题解

## 作者：残阳如血 (赞：1)

### $\textbf{Solution}$
双指针。

首先先判一个特殊情况：若序列中存在 $0$，由于 $k\ge 0$，则答案必然为 $n$。

用双指针 $i,j$ 维护区间 $[i,j]$，$s$ 统计区间所有元素的积，跑一遍板子就行了。

注意，当 $i$ 移出区间时，只有 $j\ge i$（即当前区间存在）才要除以 $a_i$。

### $\textbf{Code}$
[record](https://atcoder.jp/contests/abc032/submissions/62481216)。

```cpp
#include <bits/stdc++.h>
using lint = long long;
const int N = 1e5 + 10;

int n, len;
lint k, s = 1, a[N];

int main() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; ++i) std::cin >> a[i];
	for (int i = 1; i <= n; ++i)
		if (!a[i]) return std::cout << n << std::endl, 0;
	
	for (int i = 1, j = 0; i <= n && j <= n; ++i) {
		while (j < n && s * a[j + 1] <= k) s *= a[++j];
		len = std::max(len, j - i + 1);
		if (j >= i) s /= a[i];
	}
	std::cout << len << std::endl;
	return 0;
}
```

---

## 作者：jinhangdong (赞：0)

考虑用双指针。

首先如果这些数里有 $0$ 那么最终答案肯定是 $n$。

然后考虑双指针，如果当前的乘积乘下一个还满足条件，就成，右端点右移。然后记录答案，左端点左移，顺便把乘积更新，注意如果左端点大于右端点不能更新。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int a[N],l=1,r,n,k,Max,mul=1;
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		if(!a[i])//a[i]是0，说明最终成绩是0，最多长度可以是n
		{
			cout<<n<<"\n";
			return 0;
		} 
	}
	while(l<n)
	{
		while(r<n&&mul*a[r+1]<=k)
		{
			r++;
			mul*=a[r];
		}
		Max=max(Max,r-l+1);//更新答案
		if(l<=r) mul/=a[l];
		l++;
	}
	cout<<Max<<"\n";
	return 0;
}
```

---

## 作者：InversionShadow (赞：0)

双指针维护最长乘积小于等于 $k$ 的区间，动态维护区间乘积 $ans$ 即可。

时间复杂度 $\mathcal{O(n)}$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 100;

int n, k, a[N], mx, ans = 1; 

signed main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] == 0) {
      cout << n << '\n';
      return 0;
    }
  }
  for (int i = 1, j = 0; i <= n; i++) {
    while (j < n && ans * a[j + 1] <= k) {
      ans *= a[++j];
      mx = max(mx, j - i + 1);
    }
    if (j >= i) {
      ans /= a[i];
    }
  }
  cout << mx << '\n';
  return 0;
}
```

---

## 作者：CatnipQwQ (赞：0)

显然我们不能枚举每个区间并判断是否合法。但是因为 $s_i\geq 0$，所以如果一个区间满足条件且其中没有 $0$，那么它的子区间也满足条件。于是不难想到枚举左端点并双指针维护右端点。具体来说，我们维护一个指针 $r$ 表示左端点为 $i$ 时最大的右端点，再维护 $i\sim r$ 内的乘积。每次只需要将 $r$ 后移直到如果再次后移就会不合法，更新答案后再将 $s_i$ 从乘积中除去即可。注意当 $r<i$（即不存在符合条件的区间）时可能要特判。

但是上面的做法不能处理存在 $s_i=0$ 的情况。但是因为 $k\geq 0$，所以在这种情况下原来的序列的乘积必定等于 $0$，也就是必定合法。所以特判这种情况，直接输出 $n$ 就行啦 awa。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000000];
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i=1; i<=n; i++)
	{
		scanf("%d", &a[i]);
		if(a[i]==0)
		{
			printf("%d\n", n);
			return 0;
		}
	}
	int prod=1, r=0, ans=0;
	for(int i=1; i<=n; i++)
	{
		while(r<n && 1ll*prod*a[r+1]<=k)
		{
			r++;
			prod*=a[r];
		}
		ans=max(ans,r-i+1);
		if(r<i)
		{
			r=i;
			prod=1;
		}
		else
			prod/=a[i];
	}
	printf("%d\n", ans);
	return 0;
}
```

---

