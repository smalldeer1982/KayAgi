# Strange Shuffle

## 题目描述

This is an interactive problem.

 $ n $ people sitting in a circle are trying to shuffle a deck of cards. The players are numbered from $ 1 $ to $ n $ , so that players $ i $ and $ i+1 $ are neighbours (as well as players $ 1 $ and $ n $ ). Each of them has exactly $ k $ cards, where $ k $ is even. The left neighbour of a player $ i $ is player $ i - 1 $ , and their right neighbour is player $ i + 1 $ (except for players $ 1 $ and $ n $ , who are respective neighbours of each other).

Each turn the following happens: if a player has $ x $ cards, they give $ \lfloor x / 2 \rfloor $ to their neighbour on the left and $ \lceil x / 2 \rceil $ cards to their neighbour on the right. This happens for all players simultaneously.

However, one player $ p $ is the impostor and they just give all their cards to their neighbour on the right. You know the number of players $ n $ and the number of cards $ k $ each player has initially, but $ p $ is unknown to you. Your task is to determine the value of $ p $ , by asking questions like "how many cards does player $ q $ have?" for an index $ q $ of your choice. After each question all players will make exactly one move and give their cards to their neighbours. You need to find the impostor by asking no more than $ 1000 $ questions.

## 说明/提示

In the example the cards are transferred in the following way:

- $ 2 $ $ 2 $ $ 2 $ $ 2 $ — player $ 1 $ has $ 2 $ cards.
- $ 1 $ $ 2 $ $ 3 $ $ 2 $ — player $ 1 $ has $ 1 $ card.

After this turn the number of cards remains unchanged for each player.

## 样例 #1

### 输入

```
4 2

2

1

2

3

2```

### 输出

```
? 1

? 1

? 2

? 3

? 4

! 2```

# 题解

## 作者：fanfansann (赞：3)

# E - Strange Shuffle

**Problem E Strange Shuffle**

交互题，题目大意就是有 $n$ 个人， 编号 $1$ ~ $n$， 围成一个圈，每个人手里有 $k$ 张牌，从第 $1$ 秒开始，每一秒，所有的人，都将自己手中的牌的一半上取整，即 $\lceil\frac{k}{2}\rceil$ 给自己右边的人，与此同时，把自己手中的牌的一半下取整，即$\lfloor\frac{k}{2}\rfloor$ 给自己左边的人，但是有一个家伙比较特殊，他每次会把自己的全部的牌都给自己右边的人。你可以询问 $q\le1000$ 次，每次询问一个数 $x$，会回答你第 $x$ 个人手里的牌的数量。
$1\le n\le10^5,1\le k \le10^9$

**Solution**

我们可以先根据题意打表找规律。三分钟写一个最暴力的模拟程序：


```cpp
int n =  60;
int a[N], b[N];
int main()
{
    for(int i = 0; i < n; ++ i) {
        a[i] = 4;
    }
    int k = 15;
    int t = 10;
    while(t -- ) {
        memset(b, 0, sizeof b);
        for(int i = 0; i < n; ++ i) {
            if(i == k) {
                b[k + 1] += a[k];
                a[k] = 0;
                continue;
            }
            int l = (i - 1 + n) % n;
            b[l] += floor((double)a[i] / 2);
            int r = (i + 1) % n;
            b[r] += ceil((double)a[i] / 2);
            a[i] = 0;
        }
        for(int i = 0; i < n; ++ i)
            a[i] += b[i], printf("%d ", a[i]);
        puts("");
    }
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210202170341914.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)

好的，发现规律了，规律就是所有的数字，如果没有那个特殊的人来捣鬼，就不会发生任何变化，而那个捣鬼的人周围的数字，左边，会越来越小，右边会越来越大。所以我们只需要暴力找到  “疫区”（也就是发生变化的区域），然后如果大于 $k$ 就往左找，如果小于 $k$ 就往右找，最后找到那个疫区里唯一一个大小等于 $k$ 的数字，就是那个特殊的人。

如何暴力找？ $n\le 10^5$ ，直接 `for` 循环看上去会超时，因为题目仅能询问 $1000$ 次，那么考虑优化。首先我们最直观的走路优化加速的方法就是倍增。但是倍增会跳的非常的快，而且关键在于我们遇见一个 $k$ 不知道它到底是在疫区左边还是疫区右边，因为疫区还没有扩展出来，我们可能就已经跳过疫区了，这样可能需要来回找，有点麻烦，但是可做。考虑慢一点，我们发现，疫区是一个一个向外扩展，每次 $+1$ ，我们考虑一个慢一点的走路加速方式：等差数列。我们 `for` 循环，`cur` 指针指向当前的位置，每次走 $i$ 步，这样走 $1,2,\cdots n$ 步，这样走完一遍，最多需要走 $x$ 步，其中 $x=\frac{n(n+1)}{2},n\le10^5$，$x\le \sqrt{10^5}≈330$。而我们最多可以询问 $1000$ 次，完全没问题。那么会不会第一次找不到呢，我们可以很直观的发现第一次走，一定能找到，因为我们的指针 $cur$ 和疫区扩展的速度是一样的，所以一次是跳不过疫区的，所以第一次就能找到。

比赛的时候可以一个人写打表程序，一个人推规律，其实本题的规律非常简单，可以不打表也能看出来。因为我们知道一个数，除以二上取整，可能会大于单纯的除以二，除以二下取整，可能会小于，单纯的除以二，而题目中不同的人，最开始手里的牌都一样，他们给两边的人牌，两边的人也给他牌，正常人手里的牌的个数是不变的，而特殊的人的手里的牌，因为会全部给到右边的人手里，右边的人手里的牌多了之后，更右边的人手里的牌也会多，会一直多下去，题目中为了能保证这一点，特别增加了上取整来实现这一操作。同理，左边也会一直小，一直变小，而中间的那一位，因为给全部给右边， 而右边因为只多了一半，再还给左边那位特殊的人的时候，是要下取整，特殊的人左边，虽然少了一点，但是还是要给右边一半的值，而且要上取整，这样中间的那个特殊的人手里的牌会一直不变，也就一直保持为 $k$，这一点是本题解题的关键。

**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;
const int N = 3e5 + 7, mod = 1e9 + 7;
typedef long long ll;
typedef int itn;
int res;
int n, m, k;

int ask(int x)
{
    printf("? %d\n", x);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

int main()
{
    scanf("%d%d", &n, &k);
    int cur = 1;
    ask(cur);

    for(int i = 1; i <= n; ++ i) {
        cur = (cur + i - 1) % n + 1;//!
        res = ask(cur);
        if(res != k) {//找到了疫区
            if(res > k) {//右边，往左找
                while(true) {
                    cur = (cur == 1 ? n : cur - 1);
                    res = ask(cur);
                    if(res == k) {
                        printf("! %d\n", cur);
                        fflush(stdout);
                        return 0;
                    }
                }
            }
            else {
                while(true) {
                    cur = (cur == n ? 1 : cur + 1);
                    res = ask(cur);
                    if(res == k) {
                        printf("! %d\n", cur);
                        fflush(stdout);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}

```


---

## 作者：灵茶山艾府 (赞：3)

尝试打表找找规律，发现从内鬼开始往左右扩散，右侧元素会逐渐大于 $k$，左侧元素会逐渐小于 $k$，而距离内鬼很远的元素仍然为 $k$。

由于 $n$ 很大，可以先从 $1$ 开始每隔 $step=\sqrt n$ 步跳着找一个不等于 $k$ 的元素，然后暴力枚举到一个等于 $k$ 的元素即为答案（这一步也可以用二分实现，由于查询限制比较宽松这里就直接暴力了）。

这里有个细节，若 $\sqrt n|n$ 则可能会出现一直查询的是 $k$ 的情况，所以不妨在这附近选择一个与 $n$ 互质的 $step$。

AC 代码（golang）:

```go
package main

import (
	. "fmt"
	"math"
)

func gcd(a, b int) int {
	for a != 0 {
		a, b = b%a, a
	}
	return b
}

func main() {
	var n, k, v int
	Scan(&n, &k)
	step := int(math.Sqrt(float64(n)))
	for gcd(step, n) > 1 {
		step++
	}
	for i := 0; ; i += step {
		Println("?", i%n+1)
		Scan(&v)
		if v == k {
			continue
		}
		if v < k {
			for j := i + 1; ; j++ {
				Println("?", j%n+1)
				Scan(&v)
				if v == k {
					Println("!", j%n+1)
					return
				}
			}
		} else {
			for j := i - 1; ; j-- {
				Println("?", (j%n+n)%n+1)
				Scan(&v)
				if v == k {
					Println("!", (j%n+n)%n+1)
					return
				}
			}
		}
	}
}
```


---

## 作者：123456zmy (赞：3)

题意：  
这是一道交互题。

有 $n$ 个人，最开始时每个人都有 $k$ 张牌，你每次可以询问一个人手中的牌的数量。

每次询问之后，每个人都会给他左边的人一半的牌（下取整），然后把剩下的牌给他右边的人，特殊的，有一个人会把他所有的牌给他右边的人（第 $1$ 个人在第 $n$ 个人右边）。

你需要在 $1000$ 次询问内确定那个特殊的人。
___
首先，我们有一个比较显然的方法，每次随机查一个点，然后判断符合条件的特殊的人的位置的集合，当集合大小降为 $1$ 时这个数就是答案。~~然后您可以获得 2w+ 的操作次数。~~

观察发现，询问与可能的答案距离很远的点是没有太大意义的，所以我们可以随机询问可能的答案附近的点，然后 `srand(time(0))` 就可以通过此题。
___
（大概）证一下复杂度。第 $i$ 次询问返回 $k$ 时，说明答案不在这个数附近 $2i$ 个，删除答案集合中 $2i$ 个元素；如果返回的不是 $k$，则可以直接确定答案在这个数附近 $2i$ 个以内。在第 $\sqrt{n}$ 次查询的时候，答案集合会减小到一个比较小的值，所以询问次数在 $\sqrt{n}$ 左右。

从信息的方面看，[标算](https://codeforces.com/blog/entry/86464)丢失了前 $\sqrt{n}$ 次查询的信息，而这个做法将每次查询的信息都利用了起来，所以比标算约少 $\sqrt{n}$ 次查询。
___

```cpp
int n,k,a[100001],b[100001],val;
bitset<100001>ans,tmp;

//...

main()
{
	srand(time(0));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)a[i]=k,ans[i]=1;
	while(ans.count()>1)
	{
		int q=(rand()*32768|rand())%n+1;
		while(ans[q]==0||ans[q%n+1]==0)q=(rand()*32768|rand())%n+1;//随机选择答案附近的点
		query(q);//查询 q
		scanf("%d",&val);
		find(q,val);//找出所有的匹配的位置。
		ans&=tmp;//取交集
		for(int i=3;i<n;i++)f(b[i],a[i-1],a[i+1]);
		f(b[n],a[n-1],0),f(b[1],a[n],a[2]),b[2]=(a[3]>>1)+a[1];//求出下一轮每个人的牌的数量
		memcpy(a,b,sizeof(a));
	}
	for(int i=1;i<=n;i++)if(ans[i]==1)
	{
		cout<<"! "<<i<<endl;
		return 0;
	}
}
```

---

## 作者：_Felix (赞：2)

upd 2022/4/21: 1e5 写成 1e3 了。

## 题意
有 $n$ 个人，围成一圈，每个人有 $a_i$ 张牌。其中有一个内鬼。

初始 $a_i=k$

每次，每个人给他左侧的人 $\lfloor \frac {a_i} 2\rfloor$ 右侧的人 $\lceil \frac {a_i} 2\rceil$。但是内鬼会给右边的人 $a_i$ 张。

可以发现，如果一个人暂时没有受到内鬼的影响，那么他有 $k$ 张牌。

内鬼则向左右两边传播异常，左边 $<k$ 的区域越来越大，右边 $>k$ 的区域越来越大。而内鬼自己一直是 $k$ 张牌。



于是我们从 $1$ 开始询问，每次 $+(i+1)$ ，原因是如果这个人不属于异常，它左右 $2i$ 区域也不会是内鬼，当我们扫到一个值 $\neq k$ 的，说明它受到内鬼影响，内鬼在它附近（询问次数）的范围内。直接暴力扫即可。

询问次数 $1+2+...+500>100000$ 因此是合法的方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int n,k;
int ask(int x){
    printf("? %d\n",x); fflush(stdout);
    scanf("%d",&x);
    return x;
}
int calc(int x){
    x=x%n;
    if(x<=0) x+=n;
  //  cout<<x<<endl;
    return x;
}
int check(int x){
    int tmp=ask(x);
    return (tmp==k);
}
int main(){
    scanf("%d%d",&n,&k);
    int nw=1,val=0;
    for(int i=1;i<=n;i++){
        val=ask(nw);
        if(val!=k) break;
        nw+=(i+1); nw=calc(nw);
    }
    if(val>k){//内鬼在左侧
        for(int i=1;i<=n;i++){
            int tmp=calc(nw-i);
            if(check(tmp)){
                printf("! %d\n",tmp);
                return 0;
            }
        }
    } else {//内鬼在右侧
        for(int i=1;i<=n;i++){
            int tmp=calc(nw+i);
            if(check(tmp)){
                printf("! %d\n",tmp);
                return 0;
            }
        }
    }
    return 0;
}

```

---

## 作者：duyi (赞：0)

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/14364145.html#cf1470c-strange-shuffle)

# CF1470C Strange Shuffle


观察发现，内鬼的影响会逐轮向两侧扩散。

具体来说：

- 对于 $1\leq i\leq\lfloor\frac{n - 1}{2}\rfloor$，在第 $i$ 轮后，内鬼左边的 $i$ 个数都**小于** $k$，且从内鬼开始**向左递增**；内鬼右边的 $i$ 个数都**大于** $k$，且从内鬼开始**向右递减**。内鬼始终等于 $k$，距离内鬼超过 $i$ 的数还未被影响到，所以也等于 $k$。

- 对于 $i > \lfloor\frac{n - 1}{2}\rfloor$，在第 $i$ 轮后序列里所有数都被影响过了。此时序列里**最大的数**就是内鬼右边的数，从它开始向右依次递减，在内鬼的**对面**减到 $k$，然后继续递减，直到到达内鬼的左边，内鬼的左边就是序列里最小的数。内鬼始终保持为 $k$。

暴力做法：先在任意位置询问 $1$ 次。在接下来的任意时刻，序列里至少有 $1$ 个大于 $k$ 的数，它在内鬼的右侧；也至少有一个小于 $k$ 的数，它在内鬼的左侧。用 $n$ 次询问，暴力找到这样两个数。然后在它们之间二分出内鬼的位置。操作次数：$1 + n + \lfloor\log_2(n)\rfloor$。

当 $n\leq 900$ 时，我们就使用上述做法，这可以避免讨论很多特殊情况。下面考虑 $n$ 较大时：

观察操作次数的限制：$1000$。容易联想到根号做法。设 $B = \lfloor\sqrt{n}\rfloor$。先在任意位置询问 $B$ 次。在接下来的任意时刻，序列里总存在连续的 $B$ 个大于 $k$ 的数，和连续的 $B$ 个小于 $k$ 的数。我们每隔 $B$ 个位置询问一次，就一定能找出这样的两个数。然后再和上面一样二分答案。操作次数：$B + \lceil\frac{n}{B}\rceil + \lfloor\log_2(n)\rfloor \approx 2\sqrt{n} + \log_2(n)$，可以通过。

[参考代码-在CF查看](https://codeforces.com/problemset/submission/1470/108766008)

---

**总结**：

一开始要多观察和分析，不要被题面里的上取整、下取整搞晕，可以借助程序，就能发现整个过程的规律其实是简洁优美的，细节并不繁琐。

然后分块和二分，都是交互题里比较经典的做法。

**归类**：分块，二分。

**难度**：中。



---

