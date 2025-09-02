# Copying Homework

## 题目描述

Danang and Darto are classmates. They are given homework to create a permutation of $ N $ integers from $ 1 $ to $ N $ . Danang has completed the homework and created a permutation $ A $ of $ N $ integers. Darto wants to copy Danang's homework, but Danang asks Darto to change it up a bit so it does not look obvious that Darto copied.

The difference of two permutations of $ N $ integers $ A $ and $ B $ , denoted by $ diff(A, B) $ , is the sum of the absolute difference of $ A_i $ and $ B_i $ for all $ i $ . In other words, $ diff(A, B) = \Sigma_{i=1}^N |A_i - B_i| $ . Darto would like to create a permutation of $ N $ integers that maximizes its difference with $ A $ . Formally, he wants to find a permutation of $ N $ integers $ B_{max} $ such that $ diff(A, B_{max}) \ge diff(A, B') $ for all permutation of $ N $ integers $ B' $ .

Darto needs your help! Since the teacher giving the homework is lenient, any permutation of $ N $ integers $ B $ is considered different with $ A $ if the difference of $ A $ and $ B $ is at least $ N $ . Therefore, you are allowed to return any permutation of $ N $ integers $ B $ such that $ diff(A, B) \ge N $ .

Of course, you can still return $ B_{max} $ if you want, since it can be proven that $ diff(A, B_{max}) \ge N $ for any permutation $ A $ and $ N > 1 $ . This also proves that there exists a solution for any permutation of $ N $ integers $ A $ . If there is more than one valid solution, you can output any of them.

## 说明/提示

Explanation for the sample input/output #1

With $ A = [1, 3, 2, 4] $ and $ B = [4, 2, 3, 1] $ , $ diff(A, B) = |1 - 4| + |3 - 2| + |2 - 3| + |4 - 1| = 3 + 1 + 1 + 3 = 8 $ . Since $ 8 \ge 4 $ , $ [4, 2, 3, 1] $ is one of the valid output for this sample.

## 样例 #1

### 输入

```
4
1 3 2 4
```

### 输出

```
4 2 3 1
```

## 样例 #2

### 输入

```
2
2 1
```

### 输出

```
1 2
```

# 题解

## 作者：残阳如血 (赞：5)

# 思路分析
**前置知识：排列是没有重复元素的！**
## 猜想
我们可以进行一种猜想，对于 $x$，输出：
$$\begin{cases}
x+1&x<N\\
1&x=N
\end{cases}$$
将代码提交上去，我们可以发现这种猜想值正确的！
## 证明
~~但是作为一名合格的 OIer~~我们必须证明这种做法是正确的。

对于 $x<N$ 的情况，我们输出 $x+1$，那么 $diff$ 可以增加 $|x+1-x|=|1|=1$。因为排列没有重复元素，那么就有 $N-1$ 这种情况，执行完后 $diff=(N-1)\times 1=N-1$。

然后对于 $x=N$ 的情况，我们输出 $1$，那么增加了 $|N-1|=N-1$，$diff=N-1+N-1=2\times N-2$，对于 $N\ge 2$ 的情况中，总是满足 $2\times N-2\ge N$，这样我们就完成了我们的目的。
## 优化
我们可以发现 $a$ 数组中的值在本次使用后就没有再次用过，所以就根本没有必要把整个 $a$ 数组存储下来，我们只需定义一个 $tmp$，记录本次读入的值。
# 复杂度分析
## 时间复杂度
我们要从 $0$ 遍历到 $N-1$，时间复杂度为 $\mathcal O(n)$。
## 空间复杂度
优化前我们要存储整个 $a$ 数组，空间复杂度为 $\mathcal O(n)$。

优化后我们只需定义几个变量，空间复杂度降为 $\mathcal O(1)$。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int N, tmp;
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		cout << (tmp == N ? 1 : tmp + 1) << " ";
	}
	return 0;
}
```

---

## 作者：ChenZQ (赞：1)

 首先**简化题意**
 
 题目要求我们根据数组  $a$ 来求出数组  $b$。使得数组 $a$ 每个数的绝对值减去数组 $b$ 的每个数绝对值大于或等于 $n$。
 
说个跟其他题解不同的思路，其实我们直接输出 $a_i+1$ 就好了。因为题目要求大于等于 $n$，注意有一个**等于**！所以只要每个数的绝对值都能是一。那么我们就能满足题目要求。

所以贴代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int a[N];

signed main()
{
    int n;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if(a[i]==n) cout<<1<<" ";//边界判断。
        else cout<<(a[i]+1)<<" ";
    }
}
```

---

## 作者：LiAuPb (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1252A)

### 一、简要题意

给定一段长度为 $N$ 的序列 $A$，使其重新排列成一个序列  $B$。并使 $A$ 与 $B$ 的每个元素之差的绝对值之和不小于 $N$。

### 二、简要思路

将第二句话复制到百度翻译上我们可以得到：

给他们做作业，创建从 $1$ 到 $N$ 的 $N$ 个整数的排列。

所以只需要把值为 $1$ 和 $N$ 的数位置互换就可以了（其它数相减等于零，把 $1$ 和 $N$ 的数位置互换后两序列之差等于 $\left|N - 1\right| + \left|1 - N\right|$ $=$ $2(N - 1)$，远大于 $N$）。

### 三、代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x1, xn;
int a[100010];
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);    //输入
		if(a[i] == 1){    //如果值为一
			x1 = i;    //记录下标
		}
		if(a[i] == n){    //如果值为n
			xn = i;    //记录下标
		}
	}
	swap(a[x1], a[xn]);    //将值交换
	for(int i = 1; i <= n; i++){
		printf("%d ", a[i]);    //输出
	}
	return 0;
}
```


---

## 作者：zjr0330 (赞：1)

首先我们分析一下题目，他先给我们一个序列，让我们调换一下这个序列的顺序，使得序列每个相邻的元素的绝对值加和 $\ge n$。

其实这一题不是很难，我们仅需将序列最小值换成 $n$ ，序列最大值换成 $1$ 即可。

打个比方，比如一个长度为 $5$ 的序列，序列为 $5$、$2$、$3$、$4$、$1$，那么我们只需把 $1$ 换成 $n$，也就是 $5$，把 $5$ 换成 $1$ 即可。换完的序列如下：$1$、$2$、$3$、$4$、$5$，符合要求。

接下来就是简单的代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long n, a[100010], ss = 11451419198108122;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ss = min(ss, a[i]);    //记录下最小值。
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] == 1) {
			cout << n << " ";    //如果是1，输出n。
		}
		else if (a[i] == n) {
			cout << ss << ' ';    //如果是n，输出1。
		} else {
			cout << a[i] << " ";    //否则照常输出。
		}
	}
	return 0;
}
```


---

## 作者：pangyixuan (赞：0)

题目大意

现在有 $n$ 串数字和 $1$ 串序列，现在要求你输出 $1$ 组序列，使得：

第一：长度需要为 $n$ 。

第二：每一组对应的位置的差的绝对值之和需要小于 $n$ 。

根据题目意思我们可以得知：

我们只需要将序列中的最小值换成 $n$ ，将序列中最大值换成 $1$ 即可。

最后放上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],n;
int main(){
    cin>>n;
    int minn=N;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        minn=min(minn,a[i]);
    }
    for(int i=1;i<=n;i++){
        if(a[i]==n){
            cout<<minn<<" ";
        }else if(a[i]==1){
            cout<<n<<" ";
        }else{
            cout<<a[i]<<" ";
        }
    }
    return 0;
}
```


---

## 作者：Big_Dinosaur (赞：0)

构造题。
### 做法
为了使 $\sum_{i=1}^N|A_i-B_i|\le n$，可以将 $B_i$ 设为 $n-A_i+1$，这样，就可以使每组 $|A_i-B_i|$ 都较大。

这时 $\sum_{i=1}^N|A_i-B_i|=\sum_{i=1}^N|A_i-(n-A_i+1)|=\sum_{i=1}^N|A_i\times2-n+1|$，可以发现它大于 $n$。

### AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a;
signed main(){
	cin>>n;
    for(int i=1;i<=n;++i){
		cin>>a;
        cout<<n-a+1<<' ';
	}
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，因为只需输出任意一个合法排列，所以可以考虑构建一种一定满足条件的情况。其实只需要把输入中 $1$ 和 $N$ 的位置互换。此时，$\operatorname{diff}(A,B)=|1-N|+|N-1|=2N-2$。因为 $\frac{2N-2}{N}=2-\frac{2}{N}$，所以 $N$ 越小 $\frac{2N-2}{N}$ 就越小。又因为 $\min N=2$，所以 $\min\frac{2N-2}{N}=1$，所以 $2N-2$ 任何时候都大于或等于 $N$。
## 代码
```python
a = int(input())
b = list(map(int,input().split()))
for c in range(a):
    if b[c] == 1:
        b[c] = a
    elif b[c] == a:
        b[c] = 1
print(*b)
```

---

## 作者：Neilchenyinuo (赞：0)

## 题目大意

现在有 $n$ 串数字和 $1$ 串序列，现在要求你输出 $1$ 组序列，使得：

1. 长度为 $n$。

2. 每一组相对应位置的差的绝对值之和小于 $n$。

## Solution

1. 我们仅需将序列最小值换成 $n$，序列最大值换成 $1$ 即可。

2. 为什么呢？打个比方，比如长度为五的序列，为 $5$、$2$、$3$、$4$、$1$，我们将 $1$ 换成 $n$ 也就是 $n$，再把 $5$ 换成 $1$ 原序列就成了 $1$、$2$、$3$、$4$、$5$，符合题目要求。所以，写代码时，根据这段话模拟即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],n,mini=1e9;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		mini=min(mini,a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1)
			cout<<n<<" ";
		else if(a[i]==n)
			cout<<mini<<" ";
		else
			cout<<a[i]<<" ";
	}
	return 0;
}
```


---

## 作者：_ouhsnaijgnat_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1252A)

这道题个人认为是一道贪心。

# 题目大意

给你一个序列 $A$，其长度为 $N$，然后让你构造一个序列 $B$，这个序列要遵守两条原则。

第一个：$B$ 这个序列的长度也是 $N$。

第二个：$a_{i}$ 和 $b_{i}$ 的差值（也就是相减的绝对值）要小于 $n$。

# 思路

题目意思懂了，接下来开始思考怎么做。

首先，我们可以将它分类讨论。

当 $a_{i}$ 为 $1$ 时，$b_{i}$ 为 $N$ 最优，因为 $n-1$ 刚好小于 $n$。

当 $a_{i}$ 为 $N$ 时，$b_{i}$ 为 $1$ 最优，理由同上。
虽然
当 $a_{i}$ 为其他数时，$b_{i}$ 直接等于 $a_{i}$ 就可以了，这样差值等于 $0$，但是上面组成的差值已经大于 $n$ 了，所以可以直接等于 $a_{i}$。

综上，直接把序列 $A$ 里面所有的 $1$ 改成 $N$，所有的 $N$ 改成 $1$ 就可以对了。

没想到吧，这么简单。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],n;
int main() {
	cin>>n;
	int mn=1e9;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mn=min(mn,a[i]);
	}
	for(int i=1;i<=n;i++){
		if(a[i]==n){
			cout<<mn<<' ';
		}else if(a[i]==1){
			cout<<n<<' ';
		}else{
			cout<<a[i]<<' ';
		}
	}
	return 0;
}
```


---

## 作者：Szr__QAQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1252A)

[提交记录](https://www.luogu.com.cn/record/109956601)



------------
**题目大意**：

给定一段长度为 $n$ 的序列，并将该序列重新排列，使得新序列与原序列每个元素的对应位置的差的绝对值之和大于等于序列的长度 $n$，若有多种情况则输出其中一种即可。


------------
**本题思路**：

既然要使新序列与原序列每个元素的对应位置的差的绝对值之和大于等于序列的长度 $n$，那么我们 **将新序列中的 $1$ 修改成 $n$，再把新序列中的 $n$ 修改成 $1$，并保持其余元素不变即可**。

那么这是为什么呢？因为既然序列中除 $n$ 和 $1$ 之外的所有元素不变，所以新序列与原序列每个元素的对应位置的差的绝对值之和就是

**$ |1-n| + |n-1| $**

又因为 $n$ 大于等于 $2$，所以原式可化简为 

 **$ 2 ( n - 1 ) $**

由此，上述结论成立。

但还有一个问题，为什么这个数列中一定会出现 $1$ 和 $n$ 呢，其实，这题的翻译有一点疏漏，在原题的输出格式中还有这么一句话：

**作为提醒，排列中的所有元素必须在 $1$ 到 $n$ 之间并且是不同的**。

看到这里，大家已经可以去愉快地打代码啦。


------------
**完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int qaq=1e5+3;
int a[qaq];
int n;

int main(){
	ios::sync_with_stdio(false);cin.tie();cout.tie();
	
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==n)
		{
			cout<<"1 ";
			continue;
		}
		if(a[i]==1)
		{
			cout<<n<<" ";
			continue;
		}
		cout<<a[i]<<" ";
	}
	return 0;
}
```


------------
本人只是一名小蒟蒻，若有错误请指正，谢谢大家。







---

## 作者：MRZMRZ (赞：0)

这道题我在Codeforces上已经AC了，其实看懂题目意思就很简单了。

我们只要构造一个序列：让原来题目给出的序列中的$1$改为$n$，$n$改为$1$，其余保持不变。这样的$diff(A,B)$刚好为$n$，满足题意。

那么上一下代码吧：

``` cpp
//ZJ_MRZ's Code
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
long long n,a[100010];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++) {
		if(a[i]==1) {
			cout<<n<<" ";
		} else
		if(a[i]==n) {
			cout<<"1 ";
		}
		else
			cout<<a[i]<<" ";
	}
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/ak3nptvl.png)

---

