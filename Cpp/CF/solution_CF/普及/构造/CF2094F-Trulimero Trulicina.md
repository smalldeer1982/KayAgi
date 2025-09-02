# Trulimero Trulicina

## 题目描述

Trulicina 给你三个整数 $n$、$m$ 和 $k$。题目保证 $k \geq 2$ 且 $n \cdot m \equiv 0 \pmod{k}$。

请输出一个 $n \times m$ 的整数网格，满足以下所有条件：
- 网格中的每个整数都在 $1$ 到 $k$ 之间（包含 $1$ 和 $k$）。
- 从 $1$ 到 $k$ 的每个整数出现的次数相同。
- 共享一条边的两个单元格不能包含相同的整数。

可以证明这样的网格总是存在。如果存在多个解，输出任意一个即可。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
2 2 2
3 4 6
5 5 25```

### 输出

```
1 2
2 1
1 6 1 6
2 5 2 5
3 4 3 4
17 2 12 25 14
3 1 6 19 11
8 20 23 24 4
9 10 5 13 21
22 7 15 18 16```

# 题解

## 作者：zhangli828 (赞：1)

## 题目大意
请你构造一个含有 $1\sim k$ 的 $n\times m$ 网格，并且每个数的数量相等，没有两个数所在的表格的边相邻，请你输出一种合法的构造。
## 题目解法
最朴素的填法就是依次填上 $1\sim k$。但我们发现如果 $m$ 是 $k$ 的倍数，则上下相邻的两个数相等。为了避免上下相邻的两个数相等，我们把奇数行位移一位即可。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, m, k;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << (((i - 1) * m + j + (i % 2 && m % k == 0)) % k ? ((i - 1) * m + j + (i % 2 && m % k == 0)) % k : k) << ' ';
        // (i % 2 && m % k == 0) 代表如果 m 是 k 的倍数，i 为奇数则位移
      }
      cout << '\n';
    }
  }
  return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意

给定 $n\times m$ 格子，往里面填入 $[1,k]$ 的整数，使得各个整数出现次数相同且相同整数不相邻。

### 思路

简单构造。我们观察 $k=2$ 的情况，不难发现这个结果其实非常容易满足。

如果按照横平竖直的顺序，依次填入 $[1,k]$，在很多情况下就可以满足条件。唯一一点例外是当 $m$ 是 $k$ 的倍数时，每一横行的所有数都会相同。

严谨一点说，当 $m$ 不是 $k$ 的倍数时，依次填入 $[1,k]$，由于 $k\ge 2$，所以一个数左右两边一定是与此数不同的。而上下的数由于存在余数的缘故，也一定不同。

因此特判 $m$ 是 $k$ 的倍数的情况，将一行所有数平移一格并将头部数字放到尾部即可。

### 程序如下

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int T,n,m,k;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		int cur=0;
		for(int i=1;i<=n;i++){
			if(m%k==0&&i%2==0){
				cur++;
				for(int i=1;i<=m;i++)printf("%d ",(++cur)%k+1);
				cur--;
			}
			else
				for(int i=1;i<=m;i++)
					printf("%d ",(++cur)%k+1);
			puts("");
		}
	}
	return 0;
}
```

### THE END

![](https://cdn.luogu.com.cn/upload/image_hosting/1mwql2t3.png)

---

## 作者：szh_AK_all (赞：0)

模拟题。

首先如果 $m$ 不被 $k$ 整除，那么显然可以将 $1\sim k$ 按从左到右、从上到下的顺序放进我们需构造的二维数组中，然后一直循环重复这样的操作即可。

如果 $m$ 被 $k$ 整除，那么对于行号为奇数的行，将 $1\sim k$ 按顺序放入该行即可；对于行号为偶数的行，考虑将 $1$ 和 $2$、$3$ 和 $4$、$5$ 和 $6$ 等交换位置，注意特判 $k$ 为奇数的情况，当 $k$ 为奇数时将最后三个数 $k-2,k-1,k$ 互换位置即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N], b[N];
 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, m, k;
		cin >> n >> m >> k;
		int now = 1;
		if (m % k == 0) {
			if (k % 2 == 0)
				for (int i = 1; i <= k; i += 2)
					b[i] = i + 1, b[i + 1] = i;
			else {
				for (int i = 1; i <= k - 3; i += 2)
					b[i] = i + 1, b[i + 1] = i;
				b[k - 2] = k - 1, b[k - 1] = k, b[k] = k - 2;
			}
			for (int i = 1; i <= n; i++) {
				if (i % 2 == 1)
					for (int j = 1; j <= m; j++) {
						if (j % k == 0)
							cout << k;
						else
							cout << j % k;
						cout << " ";
					} else {
					for (int j = 1; j <= m; j++) {
						if (j % k == 0)
							cout << b[k];
						else
							cout << b[j % k];
						cout << " ";
					}
				}
				cout << "\n";
			}
			continue;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cout << now << " ";
				now++;
				if (now > k)
					now -= k;
			}
			cout << "\n";
		}
	}
}
```

---

## 作者：Ag2WO4 (赞：0)

分类讨论：
- 如果 $m$ 和 $n$ 都不能被 $k$ 整除则直接 $1$ 到 $k$ 循环摆 $\frac{mn}k$ 遍然后穿到矩阵里，余数产生的列号位移让相同的数包碰不上的。
- 如果其中一种能被 $k$ 整除（不妨设是 $n$）可以则直接每行 $1$ 到 $k$ 循环摆 $\frac nk$ 遍，每行之间位移一格，同样包碰不上的。
#### Python 代码
```python
for _ in range(int(input())):
    m,n,k=map(int,input().split())
    if m%k and n%k:
        for i in range(m):print(*((i*n+j)%k+1 for j in range(n)))
    else:
        for i in range(m):print(*((i+j)%k+1 for j in range(n)))
```
#### C/C++ 代码
```c
#include<stdio.h>
int t,m,n,k,j;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&m,&n,&k);
        j=n;
        if(m%k&&n%k)
        {
            while(m--)
            {
                while(--n)printf("%d ",(m*j+n)%k+1);
                n=j;
                printf("%d\n",m*j%k+1);
            }
        }
        else
        {
            while(m--)
            {
                while(--n)printf("%d ",(m+n)%k+1);
                n=j;
                printf("%d\n",m%k+1);
            }
        }
    }
}
```

---

