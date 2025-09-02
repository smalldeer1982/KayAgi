# Scoring Subsequences

## 题目描述

The score of a sequence $ [s_1, s_2, \ldots, s_d] $ is defined as $ \displaystyle \frac{s_1\cdot s_2\cdot \ldots \cdot s_d}{d!} $ , where $ d!=1\cdot 2\cdot \ldots \cdot d $ . In particular, the score of an empty sequence is $ 1 $ .

For a sequence $ [s_1, s_2, \ldots, s_d] $ , let $ m $ be the maximum score among all its subsequences. Its cost is defined as the maximum length of a subsequence with a score of $ m $ .

You are given a non-decreasing sequence $ [a_1, a_2, \ldots, a_n] $ of integers of length $ n $ . In other words, the condition $ a_1 \leq a_2 \leq \ldots \leq a_n $ is satisfied. For each $ k=1, 2, \ldots , n $ , find the cost of the sequence $ [a_1, a_2, \ldots , a_k] $ .

A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first test case:

- The maximum score among the subsequences of $ [1] $ is $ 1 $ . The subsequences $ [1] $ and $ [] $ (the empty sequence) are the only ones with this score. Thus, the cost of $ [1] $ is $ 1 $ .
- The maximum score among the subsequences of $ [1, 2] $ is $ 2 $ . The only subsequence with this score is $ [2] $ . Thus, the cost of $ [1, 2] $ is $ 1 $ .
- The maximum score among the subsequences of $ [1, 2, 3] $ is $ 3 $ . The subsequences $ [2, 3] $ and $ [3] $ are the only ones with this score. Thus, the cost of $ [1, 2, 3] $ is $ 2 $ .

 Therefore, the answer to this case is $ 1\:\:1\:\:2 $ , which are the costs of $ [1], [1, 2] $ and $ [1, 2, 3] $ in this order.

## 样例 #1

### 输入

```
3
3
1 2 3
2
1 1
5
5 5 5 5 5```

### 输出

```
1 1 2 
1 1 
1 2 3 4 5```

# 题解

## 作者：SunnyYuan (赞：6)

文中 $a$ 为题目中给的 $a$。

如果我们要求 $a_1, a_2, a_3, \dots, a_m$ 的结果，

那么我们可以把 $a$ 数组从后往前依次除以 $i$，$i$ 从 $1$ 到 $n$，

即为 $\frac{a_1}{m},\frac{a_2}{m - 1},\frac{a_3}{m - 2},\dots,\frac{a_{m - 1}}{2},\frac{a_m}{1}$，并将其保存在数组 $s$ 中。

因为 $a_1 \leq a_2 \leq a_3 \leq \dots \leq a_m$，且 $\frac{1}{i}$ 单调递增，所以 $s_1 \leq s_2 \leq s_3 \dots \leq s_m$。

那么我们自然而然地可以想到，每一次的结果就是末尾的几个数字的乘积（因为 $s$ 越大越好），即 $s_k \times s_{k + 1} \times \dots \times s_m$。

那么 $k$ 取多少呢？

我们只取对自己有利的部分，所以当 $s_k \geq 1$ 且 $s_{k - 1} < 1$ 时，我们可以达到最大值 $ans = s_k \times s_{k + 1} \times \dots \times s_m$。

因为 $s$ 单调不下降，所以可以使用二分来得出要保留的数字 $m - k$。

对每一个 $m$ 进行操作，$1 \leq m \leq n$。

时间复杂度：$O(n \log n)$。

**C++代码**

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: C. Scoring Subsequences
| Contest: Codeforces Round 856 (Div. 2)
| URL:     https://codeforc.es/contest/1794/problem/C
| When:    2023-03-06 08:30:32
| 
| Memory:  256 MB
| Time:    2500 ms
*******************************/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100010;

int n, a[N];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	for (int i = 1; i <= n; i++) {
		int l = -1, r = i + 1;
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			if (a[i - mid + 1] >= mid) l = mid;
			else r = mid;
		}
		cout << l << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) solve();

	return 0;
}
```

---

## 作者：Iamzzr (赞：3)

注意到 $a$ 是单调不降的。

容易发现以下两个性质：
- 当加入的数是当前的最大数，则这个数一定会在最佳答案的子序列中。
- 根据阶乘的定义，如果删除一个数，其值为 $a_i$，删除之前长度为 $d$，原花费为 $c$，那么删除之后的花费就是 $\dfrac{d}{a_i}\times c$。

根据以上两个性质，每读入一个 $a_i$，这个 $a_i$ 一定会被选，同时可以用双指针去除前面的数字。

```cpp
#include <iostream>

using namespace std;

const int N = 100010;

int T;
int a[N];

int main() {
    cin >> T;
    while (T--) {
        int n; cin >> n;
        int l = 1, r;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            r = i;
            while (a[l] < r - l + 1) l++;
            cout << r - l + 1 << " ";
        }
        puts("");
    }
    return 0;
}

```

---

## 作者：incra (赞：3)

### [题目链接](https://www.luogu.com.cn/problem/CF1794C)
### 题解
本题解参考了[官方题解](https://codeforces.com/blog/entry/113500)。

假设要求序列 $a_1,a_2,\dots,a_k$ 的得分。

把 $i$ 项除以 $k-i+1$，序列变为 $\dfrac{a_1}{k}, \dfrac{a_2}{k-1}, \dots, , \dfrac{a_k}{1}$。容易发现 $\dfrac{a_1}{k}\times \dfrac{a_2}{k-1}\times \dots\times  \dfrac{a_k}{1}=\dfrac{a_1\times a_2 \times \dots \times a_k}{k!}$。

由于 $a_1\le a_2\le \dots\le a_k$ 且 $\dfrac{1}{k}\le\dfrac{1}{k-1}\le\dots\le\dfrac{1}{1}$，所以我们有 $\dfrac{a_1}{k}\le \dfrac{a_2}{k-1}\le\dots,\le \dfrac{a_k}{1}$。

所以为了使答案最大，就要满足对于所有在答案中的 $i$ 都满足 $\dfrac{a_i}{k-i+1}\ge1$。由于该序列满足单调性，所以我们可以二分出第一个 $\dfrac{a_i}{k-i+1}\ge1$ 的位置 $i$，答案就是 $k-i+1$。

最后要注意一下，$\dfrac{a_i}{k-i+1}\ge1$ 可以改为 $a_i\ge k-i+1$，防止精度误差。
### 代码
```cpp
#include <iostream>
using namespace std;
const int N = 100010;
int n;
int a[N];
int main () {
	int T;
	scanf ("%d",&T);
	while (T--) {
		scanf ("%d",&n);
		for (int i = 1;i <= n;i++) scanf ("%d",&a[i]);
		for (int i = 1;i <= n;i++) {
			int l = 1,r = i;
			while (l < r) {
				int mid = l + r >> 1;
				if (a[mid] >= i - mid + 1) r = mid;
				else l = mid + 1;
			}
			cout << i - l + 1 << ' ';
		}
		cout << endl;
	}
    return 0;
}
```

---

## 作者：_JF_ (赞：2)

[CF1794C](https://www.luogu.com.cn/problem/CF1794C)

难度不是很大。主要是二分方式。

首先，题目要求值最大且覆盖区间最长。

因为要求最大，且序列单调递增。所以很容易想到，是从后往前取造成的贡献最大。

但是这样有一个反作用，加入说区间是 $[1,i]$，当前取到了 $x$，如果 $\frac{a_x}{i-x+1}<(i-x+1)$，那就必然说明这里就产生了小于 $1$ 的数，必然要比取 $[x+1,i]$ 要小。（可以考虑一一对应去看，$a_i$ 对应 $1$，$a_{i-1}$ 对应 $2$，显然是每个 $a_i$ 都要大于底下的那个数，这个值才可能最大）。

所以就考虑二分这个位置，然后不断地记录能取区间最大值，最后出来的就是值最大，且区间长度最大了。

用 $n$ 来表示 $\sum n$，时间是 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N],s1[N],s[N];
int Slove(int x){
	int l=1,r=x,len=0,sum=0;
	while(l<=r){
		sum++;
		if(sum>x)	break;
		int mid=(l+r)>>1;
		if(x-mid+1<=a[mid])	len=max(len,x-mid+1),r=mid-1;
		else	l=mid+1;
	}
	cout<<len<<" ";
}
int main(){
	int n,t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		cout<<1<<" ";
		for(int i=2;i<=n;i++){
			Slove(i);
		}
		cout<<endl;
	}
}
```


---

## 作者：lxg_honoka (赞：1)

[CF1794C. Scoring Subsequences](https://codeforces.com/problemset/problem/1794/C) 



核心算法：**双指针**

实测离线会超时，而因为是求 $1- k$ 的 $cost$，可以在线做

由于数列是不递减的，所以右边的数据是较大的，会被选取，只需判断左边界在哪。

记子序列长度为 $len$，初始时左边界为 $1$，每读入一个数据，判断边界值是否大于 $len$，如果小于就应舍去。



```cpp
#include<bits./stdc++.h>
using namespace std;

const int maxn = 1e5+10;
int a[maxn];

int main ()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);

        int l = 1;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            while (a[l] < i-l+1)	//此处应该时while，而非if
                l++;
            printf("%d ", i-l+1);
        }
        printf("\n");
    }

    return 0;
}

```



---

