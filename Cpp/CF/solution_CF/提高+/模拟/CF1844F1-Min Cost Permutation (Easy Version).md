# Min Cost Permutation (Easy Version)

## 题目描述

**The only difference between this problem and the hard version is the constraints on $t$ and $n$.**

You are given an array of $n$ positive integers $a_1,\dots,a_n$, and a (possibly negative) integer $c$.

Across all permutations $b_1,\dots,b_n$ of the array $a_1,\dots,a_n$, consider the minimum possible value of

$$
\sum_{i=1}^{n-1} |b_{i+1}-b_i-c|.
$$
 Find the lexicographically smallest permutation $b$ of the array $a$ that achieves this minimum.

A sequence $x$ is lexicographically smaller than a sequence $y$ if and only if one of the following holds:

-   $x$ is a prefix of $y$, but $x \ne y$;
-   in the first position where $x$ and $y$ differ, the sequence $x$ has a smaller element than the corresponding element in $y$.

## 说明/提示

In the first test case, it can be proven that the minimum possible value of $\sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c|$ is $27$, and the permutation $b = [9,3,1,4,5,1]$ is the lexicographically smallest permutation of $a$ that achieves this minimum: $|3-9-(-7)|+|1-3-(-7)|+|4-1-(-7)|+|5-4-(-7)|+|1-5-(-7)| = 1+5+10+8+3 = 27$.

In the second test case, the minimum possible value of $\sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c|$ is $0$, and $b = [1,3,5]$ is the lexicographically smallest permutation of $a$ that achieves this.

In the third test case, there is only one permutation $b$.

## 样例 #1

### 输入

```
3
6 -7
3 1 4 1 5 9
3 2
1 3 5
1 2718
2818```

### 输出

```
9 3 1 4 5 1
1 3 5
2818```

# 题解

## 作者：Wf_yjqd (赞：7)

蒟蒻不会 F2，但 F1 还是挺简单的吧。

------------

有一个显然的结论，若 $c\ge0$，直接从小到大排序即可。

可以利用数轴简单理解这一点。

我们考虑 $c<0$ 的情况。

如果不考虑字典序，显然根据上面结论，从大到小排序一定可以得到最小价值。

然后我们考虑在上述局面下进行挑战，若将后一个数向前移动几格可以让价值不变，且字典序变小，直接交换一定是最优的。

我们可以举例算出将 $j$ 移动到 $i$ 前，价值不变的条件为 $\left|a_j-a_{j-1}-c\right|+[i>1]\times\left|a_i-a_{i-1}-c\right|+[j<n]\times\left|a_{j+1}-a_j-c\right|=\left|a_i-a_j-c\right|+[i>1]\times\left|a_j-a_{i-1}-c\right|+[j<n]\times\left|a_{j+1}-a_{j-1}-c\right|$。

代入计算即可，复杂度 $\operatorname{O}(n^2)$。

------------

放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e3+84;
ll T,n,c,bu,a[maxn],sumbf,sumnow;
inline ll Cost(register ll x,register ll y){
    return a[x]-a[y]-c<0?a[y]+c-a[x]:a[x]-a[y]-c;
}
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&c);
        for(ll i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        sort(a+1,a+n+1);
        if(c<0){
            reverse(a+1,a+n+1);
            for(ll i=1;i<=n;i++)
                for(ll j=n;j>i;j--){
                    sumbf=Cost(j,j-1);
                    sumnow=Cost(i,j);
                    if(i>1){
                        sumbf+=Cost(i,i-1);
                        sumnow+=Cost(j,i-1);
                    }
                    if(j<n){
                        sumbf+=Cost(j+1,j);
                        sumnow+=Cost(j+1,j-1);
                    }
                    if(sumbf==sumnow){
                        bu=a[j];
                        for(ll k=j;k>i;k--)
                            a[k]=a[k-1];
                        a[i]=bu;
                        break;
                    }
                }
        }
        for(ll i=1;i<=n;i++)
            printf("%lld ",a[i]);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：Leasier (赞：2)

- **字典序最值问题可以考虑调整法。**

当 $c \geq 0$ 时，不难发现将 $a_i$ 升序一定是最优解之一，它又同时满足字典序最小，排序即可。

当 $c < 0$ 时，考虑将 $|b_{i + 1} - b_i - c|$ 看成 $|b_i - b_{i + 1} - (-c)|$，此时转化为 $c > 0$ 的问题，将 $a_i$ 降序即可取得**不考虑字典序**的最优解之一。

现在考虑字典序问题。先将 $a$ 降序排序，考虑依次确定每个 $b_i$ 最小可以取多少。

我们考虑令 $b_i \leftarrow a_j$，然后 $b_i$ 后面的部分用 $a_{i \sim n}$ 中除了 $a_j$ 之外的数填充。

设 $f(x) = |x - c|$，则我们只需要判断下面这个东西是否成立：

- $(f(a_j - a_{j - 1}) - f(a_i - a_j)) + [i > 1](f(a_i - b_{i - 1}) + f(a_j - b_{i - 1})) + [j < n](f(a_{j + 1} - a_j) - f(a_{j + 1} - a_{j - 1})) = 0$。

模拟上面的过程即可。时间复杂度为 $O(\sum n^2)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>

using namespace std;

typedef long long ll;

int a[5007];

inline int calc(int x, int c){
	return abs(x - c);
}

inline bool check(int l, int r, int n, int c){
	ll delta = calc(a[r] - a[r - 1], c) - calc(a[l] - a[r], c);
	if (l > 1) delta += calc(a[l] - a[l - 1], c) - calc(a[r] - a[l - 1], c);
	if (r < n) delta += calc(a[r + 1] - a[r], c) - calc(a[r + 1] - a[r - 1], c);
	return delta == 0;
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, c;
		cin >> n >> c;
		for (int j = 1; j <= n; j++){
			cin >> a[j];
		}
		if (c >= 0){
			sort(a + 1, a + n + 1);
		} else {
			sort(a + 1, a + n + 1, greater<int>());
			for (int j = 1; j < n; j++){
				for (int k = n; k > j; k--){
					if (check(j, k, n, c)){
						int t = a[k];
						for (int l = k; l > j; l--){
							a[l] = a[l - 1];
						}
						a[j] = t;
						break;
					}
				}
			}
		}
		for (int j = 1; j <= n; j++){
			cout << a[j] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

