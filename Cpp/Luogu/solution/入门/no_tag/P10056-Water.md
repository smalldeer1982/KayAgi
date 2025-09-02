# Water

## 题目描述

有 $n$ 个杯子，每个杯子的容积是 $a$，且初始装有 $b$ 体积水。
你可以进行任意次操作，每次操作选择任意两个杯子，将其中一个杯子内的水**全部倒入**另一个杯子中，但是过程中**杯子里的水不能溢出（即不能超过其容积）**，如果不满足则无法进行该操作。

请通过合法的操作，最大化装有最多水的杯子里水的体积。

## 说明/提示

#### 【样例 1 解释】

假设现在有两个杯子 $A,B$，可以先把 $A$ 中的全部水倒入 $B$ 中，此时 $A$ 有 $0$ 升水，$B$ 有 $4$ 升水，结束操作。此时最多水杯子内水的数量为 $4$。

#### 【数据规模与约定】

| 测试点编号 | $n\le$ | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1\sim2$ | $10^5$ | 保证无论如何操作都不会溢出 |
| $3 \sim 6$ | $10^6$ | 无 |
| $7 \sim 10$ | $10^9$ | 无 |

对于 $100\%$ 的数据，$1 \le n \le 10^9$，$1\le a\le 10^{18}$，$1\le b\le \min(a,10^9)$。


## 样例 #1

### 输入

```
5 2 2 ```

### 输出

```
4```

## 样例 #2

### 输入

```
11 5 7 ```

### 输出

```
10```

# 题解

## 作者：_little_Cabbage_ (赞：15)

# P10056 Water 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p10056)~~

这是一道规律题。

我们可以发现，总共有 $b\times n$ 体积的水。如果总共的体积数 $\le a$，那么就直接输出体积数就行了。否则，我们可以发现，因为倒水不能溢出，所以我们直接从每个杯子的容量中减去那些多出来的水，即 $a-a\bmod b$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,n;
	cin>>a>>b>>n;
	if(b*n<=a)
	{
		cout<<b*n;
	}
	else
	{
		cout<<(a-(a%b));
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/142865809)

---

## 作者：RainCQwQ (赞：6)

# P10056 Solution
## 思路整理
我的想法是这样的，分两种情况讨论：

1. 当无论如何操作水都不会溢出时，直接输出水的总量，即 $b \times n$。
2. 否则输出 $b \times \lfloor a \div n \rfloor$。

------------
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,n;
	scanf("%lld%lld%lld",&a,&b,&n);
	long long x=floor(a/b);
	if(b*n<=a) printf("%lld",b*n);
	else printf("%lld",x*b);
	return 0;
}
```

---

## 作者：_JF_ (赞：3)

不难发现，我们期望把尽可能多的杯子里面的水集中到一个杯子里面去。

所以存在以下两种情况：

- 可以把所有杯子里面的水集中到一个杯子里面，这个时候答案就是 $b\times n$。

- 或者，一个杯子最多只能装下 $\lfloor \frac{a}{b} \rfloor$ 个杯子中的全部水，不能集中全部杯子的。这个时候答案就是 $\lfloor \frac{a}{b} \rfloor \times b$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
//	freopen("text2.in","r",stdin);
//	freopen("text2.out","w",stdout);
	long long a,b,n;
	cin>>a>>b>>n;
	if(b*n<=a)	cout<<b*n<<endl;
	else	cout<<a/b*b<<endl;
}

---

## 作者：Pink_Cut_Tree (赞：2)

# P10056 Water 题解

本题像它的题目名称一样水。

### 解析

分类讨论：

1. 总水量小于等于 $a$。

直接输出 $a$ 即可（将所有水倒到一个瓶子里）。

2. 总水量超过 $a$。

由于水不能溢出，所以最后的水量一定是 $b$ 的倍数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,n;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>a>>b>>n;
	if(b*n<=a){
		cout<<b*n; return 0;
	}
	cout<<(a/b)*b;
return 0;
}

```


---

## 作者：indream (赞：2)

## P10056 Water 题解
[P10056](https://www.luogu.com.cn/problem/P10056) | [AC](https://www.luogu.com.cn/record/142865430)
### 思路
很简单。

首先，这个杯子不考虑溢出的情况下，把所有水倒到一个杯子里，这里面有 $bn$ 体积水。

考虑溢出，则这里面最多能装 $a-a \bmod b$，即 $\left\lfloor\dfrac{a}{b}\right\rfloor\times b$ 体积水。

综合一下，答案就是 $\min(a-a\bmod b,bn)$。

注意：**不开 `long long` 见祖宗！**
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    long long a,b,n;
    cin>>a>>b>>n;
    cout<<min(a-a%b,b*n);
    return 0;
}
```

---

## 作者：Double_Light (赞：1)

显然尽可能优先考虑一个杯子更优，分两种情况讨论。

如果所有的水加起来不够一个杯子的容积，直接输出所有水的体积之和 $b\times n$。

如果所有的水加起来大于等于一个杯子的容积，由于杯子内的水体积只能是 $b$ 的倍数（要求全部倒入），所以会有 $a\bmod b$ 的空间是空着的。最终的答案就是 $a-(a\bmod b)$。
```cpp
#include<iostream>
using namespace std;
long long a,b,n;//注意要开long long
int main(){
	cin>>a>>b>>n;
	if(b*n<a)cout<<b*n;
	else cout<<a-a%b;
	return 0;
}
```

---

## 作者：_anll_ (赞：0)

## 题目大意
给你 $n$ 个杯子，每个杯子的容积是 $a$，且初始均装有 $b$ 体积水。问你进行任意次操作，每次操作选择两个杯子，将其中一个杯子内的水**全部倒入**另一个杯子中，但注意不能超过容积。问你一个杯子内最多能装多少水。

## 大体思路
首先我们看清楚坑点：**全部倒入**。相信肯定有人和我一样，第一次没有看见这句话。

显然，认定一个杯子，其余杯子往里面倒水，直到溢出为止是最优方案。意识到这一点后，这道题就变成了纯暴力模拟，一个循环解决的事情。一共进行 $n$ 次循环，在第 $i$ 次循环时判断加了是否会溢出。如果溢出就终止循环，否则将水倒入该杯子。

## 代码展示
~~芥末简单还需要代码吗？~~ 如果对于上文有不理解的地方，欢迎结合代码理解。
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,a,b,ans;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>a>>b>>n;
    ans=b;
    for(int i=1;i<n;i++){
        if(ans+b<=a) ans+=b;
        else break;
    }
    cout<<ans;
    return 0;
}
```


---

