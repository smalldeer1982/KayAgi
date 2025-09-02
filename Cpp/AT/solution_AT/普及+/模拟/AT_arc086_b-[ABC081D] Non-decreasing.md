# [ABC081D] Non-decreasing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc081/tasks/arc086_b

すぬけ君は長さ $ N $ の数列 $ a $ を持っています。$ a $ の ($ 1 $-indexedでの) $ i $ 番目の数は $ a_{i} $ です。

すぬけ君は以下の操作を何度でも行うことができます。

- 操作：$ 1 $ 以上 $ N $ 以下の整数 $ x,y $ を選び、$ a_y $ に $ a_x $ を加算する。

すぬけ君はこの操作を $ 0 $ 回以上 $ 2N $ 回以下行って $ a $ が下記の条件を満たすようにしたいです。そのような操作手順の一例を示してください。 なお、この問題の制約下で、条件を満たすような操作の手順が必ず存在することが証明できます。

- 条件：$ a_1\ \leq\ a_2\ \leq\ ...\ \leq\ a_{N} $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 50 $
- $ -10^{6}\ \leq\ a_i\ \leq\ 10^{6} $
- 与えられる入力は全て整数

### Sample Explanation 1

\- $ 1 $ 番目の操作により $ a\ =\ (-2,5,4) $ となります - $ 2 $ 番目の操作により $ a\ =\ (-2,5,8) $ となり、条件を満たします

### Sample Explanation 2

\- $ 1 $ 番目の操作により $ a\ =\ (-4,-3) $ となり、条件を満たします

### Sample Explanation 3

\- すでに条件を満たしています

## 样例 #1

### 输入

```
3
-2 5 -1```

### 输出

```
2
2 3
3 3```

## 样例 #2

### 输入

```
2
-1 -3```

### 输出

```
1
2 1```

## 样例 #3

### 输入

```
5
0 0 0 0 0```

### 输出

```
0```

# 题解

## 作者：npqenqpve (赞：3)

### 题意：

每次操作可以选择 $(i,j)$ 使得 $a_j\gets a_j+a_i$，至多 $2\times n$ 次操作，将原序列变得单调不降。

### 思路：

考虑到如果序列非负，前缀和即可，如果序列非正，则后缀和即可，需要 $n-1$ 次操作完成。

思考如何把序列变成非负（非正）的。

如果绝对值最大的那个数 $a_i$ 原来非负（非正），则可以把每个满足 $j\ne i$ 的 $a_j$ 加上 $a_i$，使得原序列变得非负（非正），需要 $n-1$ 次操作，完成后直接前（后）缀和即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[105];
struct node
{
    int v,id;
}p[105];
bool cmp(node a,node b){return a.v<b.v;};
signed main()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],p[i]=(node){a[i],i};
    sort(p+1,p+1+n,cmp);
    bool f=0;
    if(p[1].v>=0)
    {
        cout<<n-1<<"\n";
        for(int i=2;i<=n;i++) cout<<i-1<<" "<<i<<"\n";
    }
    else if(p[n].v<=0) 
    {
        cout<<n-1<<"\n";
        for(int i=n;i>=2;i--) cout<<i<<" "<<i-1<<"\n";
    }
    else 
    {
        cout<<2*n-2<<"\n";
        if(abs(p[1].v)<=p[n].v)
        {
            for(int i=1;i<=n;i++)
            {
                if(i!=p[n].id) cout<<p[n].id<<" "<<i<<"\n";
            }
            for(int i=2;i<=n;i++) cout<<i-1<<" "<<i<<"\n";
        }
        else 
        {
            for(int i=1;i<=n;i++)
            {
                if(i!=p[1].id) cout<<p[1].id<<" "<<i<<"\n";
            }
            for(int i=n;i>=2;i--) cout<<i<<" "<<i-1<<"\n";
        }
    }
    system("pause > null");
}
```



---

## 作者：灵茶山艾府 (赞：2)

### 题意

给一个长度为 $N$ 的序列，每次操作可以把某个数加到一个数上，打印使序列非降的操作，要求操作数不超过 $2N$。

### 题解

如果所有数都是非负的，我们可以把第一个数加到第二个数上，然后把第二个数加到第三个数上，……。这样操作后可以使 $a_i \le a_{i+1}$，操作次数为 $N-1$。

对于所有数都是非正的情况类似，从右往左操作即可。

对于有正有负的情况，记最大值为 $max$，最小值为 $min$。若 $max>-min$，把 $max$ 加到所有负数上，则可以使所有数非负；反之类似。操作次数至多为 $N-1$。

这样就可以用至多 $2N-2$ 次操作完成要求。

### AC 代码（Golang）

```go
package main

import . "fmt"

func main() {
	var n, minI, maxI int
	Scan(&n)
	a := make([]int, n)
	for i := range a {
		Scan(&a[i])
		if a[i] < a[minI] {
			minI = i
		} else if a[i] > a[maxI] {
			maxI = i
		}
	}

	ans := [][]int{}
	d := 1 // 遍历方向
	if a[minI] < 0 && a[maxI] > 0 {
		if a[maxI] > -a[minI] {
			for i, v := range a {
				if v < 0 {
					ans = append(ans, []int{maxI + 1, i + 1})
				}
			}
		} else {
			for i, v := range a {
				if v > 0 {
					ans = append(ans, []int{minI + 1, i + 1})
				}
			}
			d = 0
		}
	} else if a[maxI] <= 0 {
		d = 0
	}
	if d == 1 {
		for i := 1; i < n; i++ {
			ans = append(ans, []int{i, i + 1})
		}
	} else {
		for i := n; i > 1; i-- {
			ans = append(ans, []int{i, i - 1})
		}
	}

	Println(len(ans))
	for _, p := range ans {
		Println(p[0], p[1])
	}
}
```





---

