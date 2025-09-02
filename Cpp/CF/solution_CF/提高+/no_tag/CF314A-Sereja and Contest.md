# Sereja and Contest

## 题目描述

During the last Sereja's Codesecrof round the server crashed many times, so the round was decided to be made unrated for some participants.

Let's assume that $ n $ people took part in the contest. Let's assume that the participant who got the first place has rating $ a_{1} $ , the second place participant has rating $ a_{2} $ , $ ... $ , the $ n $ -th place participant has rating $ a_{n} $ . Then changing the rating on the Codesecrof site is calculated by the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF314A/c51703a6e7729252fb6f20e8a44b483ddf07fc8e.png).

After the round was over, the Codesecrof management published the participants' results table. They decided that if for a participant $ d_{i}&lt;k $ , then the round can be considered unrated for him. But imagine the management's surprise when they found out that the participants' rating table is dynamic. In other words, when some participant is removed from the rating, he is removed from the results' table and the rating is recalculated according to the new table. And of course, all applications for exclusion from the rating are considered in view of the current table.

We know that among all the applications for exclusion from the rating the first application to consider is from the participant with the best rank (the rank with the minimum number), for who $ d_{i}&lt;k $ . We also know that the applications for exclusion from rating were submitted by all participants.

Now Sereja wonders, what is the number of participants to be excluded from the contest rating, and the numbers of the participants in the original table in the order of their exclusion from the rating. Pay attention to the analysis of the first test case for a better understanding of the statement.

## 说明/提示

Consider the first test sample.

1. Initially the sequence of the contest participants' ratings equals \[5, 3, 4, 1, 2\]. You can use this sequence to calculate the sequence of rating changes: \[0, -9, -13, 8, 14\]. According to the problem statement, the application of the participant who won the second place will be considered first.
2. As soon as the second place winner is out from the ratings, the participants' rating sequence will equal \[5, 4, 1, 2\]. By this sequence you can count the new sequence of rating changes: \[0, -8, 2, 6\]. According to the problem statement, the application of the participant who won the second place will be considered. Initially this participant won third place.
3. The new rating sequence equals \[5, 1, 2\], the new sequence of rating changes equals \[0, -1, 1\]. The second place participant's application is taken into consideration, initially this participant won the fourth place.
4. The new rating sequence equals \[5, 2\], the new sequence of rating changes equals \[0, 0\]. No more applications will be considered.

Thus, you should print 2, 3, 4.

## 样例 #1

### 输入

```
5 0
5 3 4 1 2
```

### 输出

```
2
3
4
```

## 样例 #2

### 输入

```
10 -10
5 5 1 7 5 1 2 4 9 2
```

### 输出

```
2
4
5
7
8
9
```

# 题解

## 作者：liangbowen (赞：4)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF314A)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16693775.html)

这翻译明显错误，建议大家去原题面看。

## 简要题意

有一个序列 $a_1, a_2, \cdots, a_n$，每次按照公式 $d_i=\sum\limits_{j=1}^{i-1}\left[a_j \cdot (j-1)-(n-i) \cdot a_i\right]$ 计算。每次再找到最小的 $x$ 满足 $d_x < k$。

将 $a_x$ 删除，然后再来一轮。找不到 $x$ 时停止。依次输出所有被删除的数**原本的编号**。

## 思路

我们想让 $d_i$ 有承接关系，即，知道 $d_{i-1}$ 能快速算出 $d_i$。

这一点还是比较容易的，把 $a_i$ 的计算部分提出来即可。$d_i=\left[\sum\limits_{j=1}^{i-1}a_j \cdot (j-1)\right] - \huge[$ $(i - 1) \cdot (n-i) \cdot a_i\huge]$。

也就是说，我们可以计算：$x_i = \sum\limits_{j=1}^{i-1}a_j \cdot (j-1)$，当前的 $d_i$ 显然就是 $x_i - (i - 1) \cdot (n-i) \cdot a_i$。

这样，对于删除操作，我们就**不必重新计算**榜单了，如果删除掉 $i$，只需要**计算 $x_i$ 时忽略掉它**。

那么代码就十分容易了，直接模拟就行。时间复杂度显然是 $O(n)$。

实际可以直接用一个变量代替 $x_i$，扫一遍就做完了。

## 完整代码

```cpp
/*为了代码更通俗，使用了不关同步的 cin 与 cout。不保证在输入输出上会被卡常。*/
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
	int n, k, nowi = 0; //nowi 是真正的 i
    cin >> n >> k;
	long long d = 0; //由于每个di可以承接地算，所以直接扫一遍即可。删除就是不计算 i 的贡献入内 
	for (int i = 1; i <= n; i++)
	{
		nowi++;
		int ai; cin >> ai;
		if (d - 1ll * (i - 1) * (n - i) * ai < k) {cout << nowi << endl; n--, i--;}
		else d += 1ll * ai * (i - 1);
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：BADFIVE (赞：1)

**题意**：有 $n$ 个人参加了比赛，评分分别为 $a_1$，$a_2$，$...$ ，$a_n$ ，这个网站的评分是根据: $d_i=\sum\limits_{j=1}^{i-1}(a_j \cdot (j-1)-(n-i) \cdot a_i)$ 计算的。比赛结束后，评分为 $k$ 的将取消评分，并重新更新排行榜。   

**思路**：题目描述比较复杂，需要认真揣摩。其实只用从头到尾进行删除，删除可能改变表中数据，问最后谁会被取消评分。最后更新排行榜，输出参与者的原始编号。   
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n,k,tmp=0,j=1;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        if(tmp-(i-1)*(n-i)*a<k){
            cout<<j<<endl;
            n--,i--;
        }
        else tmp+=a*(i-1);
        j++;
    }
}
```

---

## 作者：1234567890sjx (赞：0)

这是蓝题？？

考虑按照顺序从前往后模拟，若某一次计算的时候当前枚举到的用户的评分为 $k$ 那么就删除这个用户的评分，并直接用上一次计算到评分的用户的评分去更新下一个用户的评分，然后计算下一个用户是否评分为 $k$ 并继续往后推即可。

时间复杂度为 $O(n)$，代码十分好写。

---

## 作者：_dijkstra_ (赞：0)

化简一下式子，把 $a_i$ 的部分提取出来。

然后发现，相邻两个 $d_i$ 是有共同点的，都含有一个 $a_i \times (i - 1) \times (n - i)$，这一点推一下式子很容易求出。

然后就可以用一个变量维护多出来的部分。这样，在均摊每一次 $O(1)$ 的时间内，就能求出 $d_i$ 了。

更新榜单也很容易，毕竟每次只删一个，类似的更改 $n$ 即可。

具体参考代码。

## 代码

码风奇怪，凑合着看看吧。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,k,I=0,d=0;
	scanf("%lld%lld",&n,&k);
	for (int i=1; i<=n; i ++){
		int a;
		scanf("%d",&a);
		I ++;
		if (d - a*(i-1)*(n-i) < k){
			printf("%lld\n",I);
			i --;
			n --;
		}else{
			d += a*(i-1);
		}
	}
	return 0;
}
```

---

## 作者：Lee666666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/solution/CF314A)

~~题目难点：题意过于迷惑和标签的震慑~~

假设你已经理解了题意

暴力算法：从前往后枚举，一旦发现某个 $d_i < k$，删除并重新计算所有的 $d_i$，时间复杂度 $O(n^2)$，但该题的数据范围是 $n \leq 2 \times 10^5$，所以需要优化。

观察这个计算评分的式子

$$d_i=\sum_{j = 1}^{i - 1}{a_j \cdot (j - 1) - (n - i) \cdot a_i}$$

$$d_i=\sum_{j = 1}^{i - 1}{a_j \cdot (j - 1)} - (i - 1) \cdot (n - i) \cdot a_i$$

你会发现对于一个 $a_i$，如果 $a_1$ 到 $a_{i - 1}$ 以及 $n$ 都没有改变，那么 $d_i$ 也不会有任何改变。换句话来说，$a_{i+1}$ 到 $a_n$ 的改变对于 $d_i$ 的计算没有影响。

这意味着：在你从前往后枚举时，即时你发现了某个 $d_i < k$ 并将其删除后，你并不需要修改前面所有的值，因为完全没有必要。而删除 $d_i$ 对后面所有的值的影响有两个：
1. $n$ 减少了 1，完全可以 $O(1)$ 的时间解决
2. 少了一个 $a_j \cdot (j - 1)$，对于这一点，我们可以声明一个变量 $sum$，去维护$\sum_{j = 1}^{i - 1}{a_j \cdot (j - 1)}$，这样 O(1) 时间修改，$O(1)$ 时间查询~~我这是怎么了~~。

上代码~

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int maxn = 200015;

inline int read() {
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) {
            f = -1;
        }
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        s = (s << 3) + (s << 1) + ch - 48;
        ch = getchar();
    }
    return s * f;
}

int n, k, id = 1, tmp;
LL sum;

int main() {
    n = read();
    k = read();
    for (register int i = 1; i <= n; i++) { // 直接顺序枚举边输入便算
        tmp = read();
        if (sum - 1LL * (i - 1) * (n - i) * tmp < k) { // 分类讨论
            n--;
            i--;
            printf("%d\n", id);
        }
        else {
            sum += 1LL * tmp * (i - 1);
        }
        id++;
    }
    return 0;
}
```

时间复杂度 $O(n)$，空间复杂度 $O(1)$。

---

## 作者：开始新的记忆 (赞：0)

题目大意：从头到尾进行删除，删除可能改变表中数据，问最后谁会Unrated

扫一遍即可

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[2000010],ans=0,t=1;
int main()
{	cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
        long long x;
        cin>>x;
        if(ans-(i-1)*(n-i)*x<k)
        {
            cout<<t<<endl;
            --n;
			--i;
        }
        else 
			ans+=x*(i-1);
        ++t;
    }
	return 0;
}
```



---

