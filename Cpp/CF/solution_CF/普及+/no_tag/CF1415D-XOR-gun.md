# XOR-gun

## 题目描述

Arkady owns a non-decreasing array $ a_1, a_2, \ldots, a_n $ . You are jealous of its beauty and want to destroy this property. You have a so-called XOR-gun that you can use one or more times.

In one step you can select two consecutive elements of the array, let's say $ x $ and $ y $ , remove them from the array and insert the integer $ x \oplus y $ on their place, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Note that the length of the array decreases by one after the operation. You can't perform this operation when the length of the array reaches one.

For example, if the array is $ [2, 5, 6, 8] $ , you can select $ 5 $ and $ 6 $ and replace them with $ 5 \oplus 6 = 3 $ . The array becomes $ [2, 3, 8] $ .

You want the array no longer be non-decreasing. What is the minimum number of steps needed? If the array stays non-decreasing no matter what you do, print $ -1 $ .

## 说明/提示

In the first example you can select $ 2 $ and $ 5 $ and the array becomes $ [7, 6, 8] $ .

In the second example you can only obtain arrays $ [1, 1] $ , $ [3, 3] $ and $ [0] $ which are all non-decreasing.

In the third example you can select $ 1 $ and $ 2 $ and the array becomes $ [3, 4, 6, 20] $ . Then you can, for example, select $ 3 $ and $ 4 $ and the array becomes $ [7, 6, 20] $ , which is no longer non-decreasing.

## 样例 #1

### 输入

```
4
2 5 6 8```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
1 2 4 6 20```

### 输出

```
2```

# 题解

## 作者：chen_03 (赞：24)

首先，如果只用一次操作就能把序列变成非不降序列，那么就输出 $1$。

我们发现，如果存在连续的三个数，它们在二进制下的最高位是同一位（例如 $(100)_2,(110)_2,(111)_2$），那么对后面的两个数进行一次操作，就能使序列非不降，因为它们的最高位会相互抵消掉（$(110)_2\oplus(111)_2=(001)_2$，$(100)_2>(001)_2$）。

所以，如果只用一次操作行不通的话，那么对于每个二进制位，以它为最高位的数最多只有 $2$ 个。由于最多只有 $30$ 个二进制位，所以此时 $n\le 60$，暴力即可。

（同样地，若 $n>60$，那么一定可以只用一次操作就使序列非不降。）

暴力时，先对序列做一遍前缀异或和。由于要操作的一定是相邻的两个区间内的所有数，所以我们枚举断点，答案取最小值即可。注意特判无解的情况。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,a[100005],x,y,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=n-2;++i){
		x=a[i]^a[i+1];
		if(x<a[i-1] || x>a[i+2]){
			printf("1\n");
			return 0;
		}
	}
	for(int i=1;i<=n;++i)a[i]^=a[i-1];
	ans=n;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			for(int k=i;k<j;++k){
				x=a[k]^a[i-1];
				y=a[j]^a[k];
				if(x>y)ans=min(ans,j-i-1);
			}
		}
	}
	printf("%d\n",ans<n?ans:-1);
	return 0;
}
```


---

## 作者：Schwarzkopf_Henkal (赞：8)

很有意思的一道题，之前周指导有讲过这种类似的最小操作次数题（上次的例题是一道二维剪电线题）可以考虑有没有最大可行操作次数。然后这次就碰到了。

首先根据性质，要是有三个相邻的数二进制最高位相同，那么操作次数为 $1$。证明的话，容易想到因为数是不递减的，那么数的最高位也应该是不递减的，而对于三个相邻的最高位相同的数，只要异或后两个数，就能抵消最高位，一定小于第一个数。

要是不存在这样的数，那么由于 $a_i\leq 10^9$，而每一个最高位都最多有两个数，总的 $n$ 一定是小于等于一个非常小的数的。

然后我们打一个暴力，具体的思路就是我们要选一对相邻的点，然后我们要让左边的点异或上左边往左多少点的异或和大于右边的点往右异或上多少点的异或和，求最小操作次数，只需要暴枚就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],mx[100005],c[100005],ans=1e9;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        c[i]=c[i-1]^a[i];
        int cur=a[i];
        while(cur){
            mx[i]++;
            cur>>=1;
        }
    }
    for(int i=1;i<=n-2;i++)
        if(mx[i]==mx[i+1]&&mx[i]==mx[i+2]){
            printf("1");
            return 0;
        }
    for(int i=1;i<n;i++)
        for(int j=i;j>=1;j--)
            for(int k=i+1;k<=n;k++)
                if((c[i]^c[j-1])>(c[k]^c[i]))
                    ans=min(ans,k-j-1);
    if(ans==1e9)
        printf("-1");
    else printf("%d",ans);
}
```

---

## 作者：yuzhuo (赞：3)

这是一道好题。

## 思路

首先我们会发现：如果 $a_{i-1},a_i,a_{i+1}$ 的最高位一样，则必定会有 $a_{i-1}>a_i\oplus a_{i+1}$，即答案为 $1$。

反之，如果没有这种情况，即至多 $n=60$，我们就可以用以下方法 $O(n^3)$ 过。

令 $\oplus _i^j=a_i\oplus a_{i+1}\oplus \cdots \oplus a_j$，如果最后有逆序对，则必定有连续两个逆序。

我们不妨设最后 $a_x>a_{x+1}$。

由于是相邻两个更新数值，所以 $a_i=\oplus _l^r$。
由于最后是 $a_x$ 和 $a_{x+1}$，所以 $a_x$ 不会和 $a_{x+1}$ 进行操作。

我们不妨设 $a_x=a_p\oplus a_{p+1}+\dots \oplus a_x$，那么我们枚举 $x$，$p$，$q$，用异或前缀和 $O(1)$ 算出 $a_i\oplus a_{i+1}+\dots \oplus a_j$，就可以 AC。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
int n, a[N], s[N], ans;
main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		s[i] = s[i - 1] ^ a[i]; //计算异或前缀和
	}
	//把所有答案为1的情况O(n)算出来
	for (int i = 1; i < n - 1; ++i) {
		int x = a[i] ^ a[i + 1]; //设操作a[i],a[i+1]
		if (x < a[i - 1] || x > a[i + 2]) { //不满足条件时，输出1
			puts("1");
			return 0;
		}
	}
	//则此时答案>1,n<=60
	ans = 100; //答案必然不超过100
	for (int p = 1; p <= n; ++p)
		for (int q = p + 1; q <= n; ++q)
			for (int x = p; x < q; ++x) {
				//枚举p,q,x
				if ((s[x]^s[p - 1]) > (s[q]^s[x]))
					ans = min(ans, q - p - 1); //更新答案
			}
	if (ans < 100) cout << ans << endl;
	else puts("-1"); //输出答案
}
```

---

## 作者：shenmadongdong (赞：3)

首先如果有 3 个数它的二进制下最高位相同的话异或前两个数一定比第三个数小，那答案必定为 1

由于这个序列是单调不减的，根据抽屉原理可以求得当 $n>60$ 时必定有 3 个数最高位相同，可以直接判掉

那也就是说我们只要解决 $n \leq 60$ 的情况即可

只要打一个 $O(n^3)$ 的暴力就能过

具体实现可以看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],cnt[35],pos[100010],tmp=1,tot,ans=1e9;
int main()
{
    cin>>n;
    if (n>60) return puts("1"),0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
    {
        int r=0,_min,pos;
        for(int j=i;j<n;j++)
        {
            int l=0;
            for(int k=i;k<=j;k++) l^=a[k];//枚举区间异或值
            _min=r=a[j+1],pos=j+1;
            for(int k=j+2;k<=n;k++) 
            {
                r^=a[k];
                if (r<_min) pos=k,_min=r;//记录最小值
            }
            if (l>_min) ans=min(ans,pos-i-1);//更新答案
        }
    }
    cout<<(ans==1e9?-1:ans)<<'\n';
    return 0;
}
```

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 2000}$
---
### 解题思路：

有三个最高位相同的数直接对前两个操作就能满足要求了。

否则的话二进制上的每一个位置只能由两个，而如果这样的话可能的 $n$ 就是 $O(\log a)$ 的。直接暴力枚举就可以了。

复杂度：$O(\log^3a)$。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,num[100005],x[100005],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&num[i]);
	if(n>100){
		printf("1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)x[i]=x[i-1]^num[i];
	ans=2147483647;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	for(int k=j+1;k<=n;k++){
		if((x[j]^x[i-1])>(x[k]^x[j])){
			ans=min(ans,k-i-1);
		}
	}
	if(ans!=2147483647)	printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
```


---

## 作者：quanjun (赞：2)

### 题目链接
[https://codeforces.com/problemset/problem/1415/D](https://codeforces.com/problemset/problem/1415/D)

### 题目大意

给定一个长为 $n$ 的不降序列，每次操作可以任选相邻的两个数，并将这两个数替换为两个数按位异或的结果，现在需要破坏序列的不降，求最少操作次数，无解输出 $-1$。  

## 方法一：二分答案

首先，要破坏数列的非严格单调递增特性，肯定会选择两个连续的元素 $a_i$ 和 $a_{i+1}$，然后：

- 选择将 $a_i$ 结尾的连续若干个元素（$\ldots, a_{i-2}, a_{i-1}, a_i$）进行异或；
- 选择将 $a_{i+1}$ 开头的连续若干个元素（$a_{i+1}, a_{i+2}, \ldots$）进行异或

并令 **前者**（以 $a_i$ 结尾的连续若干个数的异或和）大于 **后者**（以 $a_{i+1}$ 开头的连续若干个数的异或和）。

为什么操作连续的若干个数？

举个形象一点的例子，这个就跟伐木一样，比如说我要砍倒一棵树，我肯定会选择同一个高度砍，不会说先在距离地面 $0.2$ 米的位置砍两刀，然后再到距离地面 $0.5$ 米的位置砍几刀，…… 肯定是在同一个位置。

因为我们的目的是破坏数列“非严格单调递增“的性质，所以我们只需要存在一对元素满足条件即可，很明显：

1. 它们是相邻的
2. 左边的那个数是一段连续的元素的异或和（对应以某个 $a_i$ 结尾的连续若干个数）
3. 右边的那个数也是一段连续的元素的异或和（对应以 $a_{i+1}$ 开头的连续若干个数）

考虑可以操作 $m$ 次时是否满足条件（破坏数列的“非严格单调递增“性质），因为要将一段连续的区间内的元素消到只剩 $2$ 个数（然后左边那个数大于右边那个数），操作一次会消去一个数，所以 $m$ 次操作对应一个长度为 $m+2$ 的区间。

当 $m$ 确定时，枚举每个下标 $i$，对于下标 $i$，我们要确定的事情是：  

> 是否存在一个以 $a_i$ 结尾的连续子序列（假设这个连续子序列的异或和为 $x$）以及一个以 $a_{i+1}$ 开头的连续子序列（假设这个连续子序列的异或和为 $y$），满足 $x \gt y$ 且两个连续子序列包含的元素个数不超过 $m+2$。

如果有的话就说明 $\Rightarrow$ 消除不超过 $m$ 次能够是数列不满足”非严格单调递增”的性质。

注意：是 **”不超过 $m$ 次”** 而不是 **”恰好 $m$ 次”**。

这是为什么呢？我们多定义两个状态 $b_j$ 和 $c_j$，这两个状态在 $j \le i$ 和 $j \gt i$ 时表示的含义不同，其中：  

### 当 $j \le i$ 时：

$b_j$ 表示的是 $a_j \oplus a_{j+1} \oplus \ldots a_i$（即以 $a_j$ 开头以 $a_i$ 结尾的连续子序列中所有元素的异或和），推导公式：

$$
b_j = \begin{cases}
a_i & j = i \\
a_j \oplus b_{j+1} & j \lt i 
\end{cases}
$$

$c_j$ 表示的是 $b_j, b_{j+1}, \ldots, b_i$ 的最大值，推导公式：  

$$
c_j = \begin{cases}
b_i & j = i \\
\max\{ b_j, c_{j+1} \} & j \lt i 
\end{cases}
$$

此时的状态是从后往前推（$i \rightarrow i-1 \rightarrow i-2 \rightarrow \ldots$），可以发现 $c_j$ 从后往前是非降的，因为 $c_j$ 表示的并不是从 $a_i$ 异或到 $a_j$ 的结果（这是 $b_j$ 表示的），而是从 $a_i$ 异或到 $a_j$ 的过程中能够得到的结果的最大值。

也就是说，$c_j$ 表示的含义是 $a_i$ 往前合并 **不超过** $i - j$ 次的情况下能够获得的最大值。

### 当 $j \gt i$ 时：  

$b_j$ 表示的是 $a_{i+1} \oplus a_{i+2} \oplus \ldots a_j$（即以 $a_i$ 开头以 $a_j$ 结尾的连续子序列中所有元素的异或和），推导公式：  

$$
b_j = \begin{cases}
a_{i+1} & j = i+1 \\
a_j \oplus b_{j-1} & j \gt i+1 
\end{cases}
$$

$c_j$ 表示的是 $b_{i+1}, b_{i+2}, \ldots, b_j$ 的最大值，推导公式：  

$$
c_j = \begin{cases}
b_{i+1} & j = i+1 \\
\min\{ b_j, c_{j-1} \} & j \gt i+1 
\end{cases}
$$

（注意，区别于 $j \le i$ 的情况，这里 $c_j$ 求的是最小值）

此时的状态是从前往后推（$i+1 \rightarrow i+2 \rightarrow i+3 \rightarrow \ldots$），可以发现 $c_j$ 从前往后是非增的，因为 $c_j$ 表示的是从 $a_{i+1}$ 异或到 $a_j$ 的过程中能够得到的结果的最小值。

也就是说，在 $g \gt i$ 时，$c_j$ 表示的含义是 $a_{i+1}$ 往后合并 **不超过** $j - i - 1$ 次的情况下能够获得的最大值。  

那么怎么能确保不超过 $m$ 次操作能够存在两个相邻的数前者大于后者呢？  

**枚举合并的过程中最前面那个数的下标！**

以 $a_i$ 结尾合并 $m$ 次能合并到 $a_{i-m}$，所以我们从 $\max\{ i-m, 1\}$ 到 $i$ 枚举下标 $j$，对于的下标区间范围是 $[j, j+m+1]$ —— 注意 $j+m+1$ 可能大于 $n$，所可以开一个 $k = j+m+1$，对于的区间范围是 $[j, k]$，当 $k \gt n$ 时就不用继续操作了（因为 $k \gt n$ 是左边一段变小，而右边一段固定，继续 $j++$ 只会让左边一段异或和的最大值变小，而右边一段异或和的最小值是不会发生任何变换，所以继续 $j++$ 没意义）它表示的含义是：

- $a_i$ 能够合并到的最左边的数是 $a_j$
- $a_{i+1}$ 能够合并到的最右边的数是 $a_k$

那么 $a_i$ 往左合并的过程中的最大值就是 $c_j$，$a_{i+1}$ 往右合并的过程中的最小值就是 $c_k$。只要 $c_j \gt c_k$，就说明不超过 $m$ 次操作能够是数列变得不满足”非严格单调递增”性质。

对应的我可以开一个 `check(int m)` 函数进行判断。

但是这种方法只能判断在不超过 $m$ 次合并时能够满足条件，不过可以发现，当 $m$ 大于等于我们的最小操作次数时，check 函数总会返回 true；当 $m$ 小于我们的最小操作次数时，check 函数总会返回 false。

所以可以对 check 函数二分答案。

示例程序：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int n, a[maxn], b[maxn], c[maxn];

bool check(int m) {
    for (int i = 1; i < n; i++) {
        b[i] = c[i] = a[i];
        for (int j = i-1; j >= max(1, i-m); j--) {
            b[j] = a[j] ^ b[j+1];
            c[j] = max(b[j], c[j+1]);
        }
        b[i+1] = c[i+1] = a[i+1];
        for (int j = i+2; j <= min(i+m+1, n); j++) {
            b[j] = a[j] ^ b[j-1];
            c[j] = min(b[j], c[j-1]);
        }
        for (int j = max(1, i-m); j <= i && j+m+1 <= n; j++)
            if (c[j] > c[j+m+1])
                return true;
    }
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 0, r = n-2, res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << res << endl;
    return 0;
}
```

### 方法二：贪心思想+枚举答案

上面二分答案的解法虽然能通过，但是分析一下，由于 `check(m)` 的时间复杂度是 $O(n \cdot m)$ 的，$m$ 接近 $n$，所以总的时间复杂度是 $O(n^2 \log n)$ 的，之所以能过的原因最主要我觉得还是因为：

1. 当 $n$ 比较大时，答案很小
2. 题目的 $n$ 可能给的比较小
3. 或者别的原因（欢迎评论区补充）

可以发现，因为 $1 \le a_i \le 10^9$，所以 $a_i$ 的二进制表示最多 $30$ 位，而数列是非严格单调递增的，所以根据鸽笼/雀巢/抽屉原理，当 $n \gt 60$ 时，必然存在连续的三个数 —— 假设这三个数是 $a_i, a_{i+1}, a_{i+2}$ —— 的最高位的位数是相同的，此时将后两个数（即 $a_{i+1}$ 和 $a_{i+2}$）异或能够消去最高位的 $1$，此时 $a_i \gt a_{i+1} \oplus a_{i+2}$（注意：本题中 $a_i \ge 1$，若 $a_i$ 可以取 $0$ 那还需要考虑排除 $0$ 的影响），即：当 $n \gt 60$ 时，答案为 $1$。

而当 $n \le 60$ 时，直接用二分或者枚举答案都是可以的。  

也就是说，在题目里面可以加一行  

```c++
if (n > 60) {
    cout << 1 << endl;
    return 0;
}
```

来优化我们的程序。  


---

## 作者：HPXXZYY (赞：2)

$\color{blue}{\texttt{[Solution]}}$

如果有连续的 $3$ 个数，它们的最高位一样，那么答案就是 $1$（我们可以把后面两个数异或，其最高位一定为 $0$，便小于第 $1$ 个数）。

根据抽屉原理可知当 $n>60$ 时，一定存在上述情况（因为只有 $30$ 个二进制位，每个位只有 $0,1$ 两种情况）。即当 $n>60$ 的时候，答案一定是 $1$。

当 $n\leq 60$ 的时候，我们容易知道：最优解下一定是把连续的一段区间异或了。

所以我们可以用一个 $O(n^3)$ 的暴力来解决问题。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e5+100;
int a[N],ans=0x3f3f3f3f,n;
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	if (n>60){printf("1");return 0;}
	for(int i=1;i<=n;i++)
		a[i]^=a[i-1];
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if ((a[j]^a[i-1])>(a[k]^a[j]))
					ans=min(ans,k-i-1);
	if (ans==0x3f3f3f3f) printf("-1");
	else printf("%d",ans);
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

首先，有个显然的 $O(n^3)$ 暴力，即每次枚举两个相邻区间进行异或操作。但这肯定会超时。

因为 $a_i\le 10^9$，也就是说每个数不会超过 $2^{30}$。可以观察到这样一个性质：只要有三个相邻的数的最高二进制位相同，则可以通过把后两个数异或，使得序列不降被破坏。那么根据抽屉原理，$n>60$ 时必然存在这样的情况。

因为原始数列不降，所以最高二进制位一定不降，相当于有 $30$ 个抽屉，$n>60$ 时必然会有至少一个抽屉里的数大于等于 $3$ 个。

---

## 作者：Kevin911 (赞：1)

假设序列的最高位位置的序列为 $b$，则根据抽屉原理可知最多只会有 $31$ 种不同的位置，因为原序列单调不降，所以若 $n\geq62$，则必会又连续三个最高位置相同的，种情况下直接异或后两个可得到比前一个个更小的值，所以答案是始终是 $1$。否则用 $O(n^3)$ 暴力枚举。

具体细节详见代码。~~虽然没啥细节~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int a[maxn];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]^=a[i-1];
	if(n>100) cout<<1;
	else
	{
		int ans=1e9;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=i;k<j;k++)
					if((a[k]^a[i-1])>(a[j]^a[k])) ans=min(ans,j-i-1);
		if(ans==1e9) cout<<-1;
		else cout<<ans;
	}
}
```


---

## 作者：him的自我修养 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1415D)

# 思路
首先，根据抽屉原理，我们可以知道 $n > 60$ 的时候所有的 $a_{i}$ 转化成二进制后必然有三数最高位相同,也就是说 $1$ 次就行了，比如说 $(111)_{2},(110)_{2},(100)_{2}$ 让 $(111)_{2} \bigoplus (110)_{2} = (001)_{2}$ 和 $(100)_{2}$ 产生逆序对，所以最多一次就够了。

那如果 $n \le 60$ 呢？我们不难想到一个 $O(n^{3})$ 的暴力。

### 暴力思路
首先，定义 $f(l,r)=a_{l}\bigoplus a_{l+1} \bigoplus a_{l+2} ... \bigoplus a_{r}$ 如果最后的两个数出现了逆序对，那么前面就必有逆序对。所以，我们可以枚举端点，用异或前缀和 $O(1)$ 算出$a_{i}\bigoplus a_{i+1} \bigoplus a_{i+2} ... \bigoplus a_{j}$。这样就可以A掉这道题了。

# code 
```
#include <bits/stdc++.h>
using namespace std;
int a[105],f[105];
int main(){
	int n;
	cin >>n;
	if(n>60){
		cout <<1;
		exit(0);
	}
	int ans=1e9;
	for(int i=1;i<=n;i++){
		cin >>a[i];
		f[i]=f[i-1]^a[i];
	}
	for(int i=1;i<n;i++){
		for(int j=i;j>=1;j--){
			for(int k=i+1;k<=n;k++){
				if((f[i]^f[j-1])>(f[k]^f[i])){
					ans=min(ans,k-j-1);
				}
			}
		}
	}
	if(ans==1e9){
		ans=-1;
	}
	cout <<ans;
	return 0;
}
```


---

## 作者：氧少Kevin (赞：0)

# CF1415D - XOR-gun
- https://www.luogu.com.cn/problem/CF1415D
- 鸽巢原理

## 题意
给出一个长为 $n(2\leq n\leq 10^5)$ 的**不降**序列 $a_i(1\leq a_i\leq 10^{18})$，可以进行如下操作：

- 任选两个**相邻**的数字，并将这两个数字替换为它们按位异或的结果。

现在需要破坏序列的不降特性，求上述操作最少需要进行的次数。无解输出 $-1$。

## 思路

$2\leq a_i\leq 10^{18}$，这说明 $a_i$ 的二进制表示最多有 $60$ 位。

序列元素是不降的，因此 $\operatorname{Hibit}(a_{i})\leq \operatorname{Hibit}(a_{i+1})$，其中 $\operatorname{Hibit}(x)$ 代表 $x$ 的二进制最高位数值。

由鸽巢原理知，当 $n>60$ 时，必然存在两个相邻的元素 $a_i,a_{i+1}$，满足  $\operatorname{Hibit}(a_{i}) = \operatorname{Hibit}(a_{i+1})$。

又因为序列元素是不降的，所以必然有 $a_i\operatorname{xor} a_{i+1} < a_{i-1}$。

因此，当 $n>60$ 时，答案为 $1$。

当 $n\leq 60$ 时，暴力判断即可。

---

## 作者：baoziwu2 (赞：0)

~~异或出喵题~~

利用前缀和思想，不难想到一个 $O(n^3)$ 的暴力：预处理出异或前缀和数组，枚举分界点 $i$，然后分别向 $i$ 两端枚举区间长度得到答案。

接下来从异或的角度去考虑，异或可以理解为不进位加法，即对于 $2$ 进制下最高位 $pos$ 位都为 $1$ 的两个数异或之后一定变小，所以只要存在 $3$ 个最高位相同且均为 $1$ 的三个数则答案为 $1$。根据抽屉原理，当 $n > 60$ 时满足条件。

```C++
#include <iostream>

using namespace std;

int const N = 2e5 + 5;

int n;
int a[N], sum[N];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	
	if(n > 60) {
		cout << 1 << endl;
		return 0;
	}
	for(int i = 1; i <= n; ++ i) 
		cin >> a[i], sum[i] = sum[i - 1] xor a[i];
	
	int ans = 1e9;
	for(int i = 1; i < n; ++ i)
		for(int j = i; j >= 1; -- j)
			for(int k = i + 1; k <= n; ++ k)
				if((sum[i] xor sum[j - 1]) > (sum[k] xor sum[i])) 
					ans = min(ans, k - j - 1);  
	
	if(ans == 1e9) ans = -1;
	cout << ans << endl;
	return 0;
}
```

---

