# Family Photos

## 题目描述

Alice and Bonnie are sisters, but they don't like each other very much. So when some old family photos were found in the attic, they started to argue about who should receive which photos. In the end, they decided that they would take turns picking photos. Alice goes first.

There are $ n $ stacks of photos. Each stack contains exactly two photos. In each turn, a player may take only a photo from the top of one of the stacks.

Each photo is described by two non-negative integers $ a $ and $ b $ , indicating that it is worth $ a $ units of happiness to Alice and $ b $ units of happiness to Bonnie. Values of $ a $ and $ b $ might differ for different photos.

It's allowed to pass instead of taking a photo. The game ends when all photos are taken or both players pass consecutively.

The players don't act to maximize their own happiness. Instead, each player acts to maximize the amount by which her happiness exceeds her sister's. Assuming both players play optimal, find the difference between Alice's and Bonnie's happiness. That is, if there's a perfectly-played game such that Alice has $ x $ happiness and Bonnie has $ y $ happiness at the end, you should print $ x-y $ .

## 样例 #1

### 输入

```
2
12 3 4 7
1 15 9 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
5 4 8 8
4 12 14 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0 10 0 10
```

### 输出

```
-10
```

# 题解

## 作者：Wen_kr (赞：15)

### **题目简述**

给定 $n$ 对照片， $Alice$ 与 $Bonnie$ 轮流取照片，每对照片只有取了第一张才能取第二张。

同时每对照片有四个权值 $a_1$ $b_1$ $a_2$ $b_2$，分别表示第一张照片对 $Alice$ 与 $Bonnie$ 的价值与第二张照片对上述二人的价值。

两人都以最优策略行动，且每回合可取可不取，两人都不取游戏结束。
求 $Alice$ 能得到的价值与 $Bonnie$ 能得到的价值的差的最大值。

### **思路简述**

考虑每一对照片：

①
若 $a_1 + b_1 >= a_2 + b_2$

显而易见 $a_1 - b_2 >= a_2 - b_1$

此时显然 $Alice$ 取照片 1 比取照片 2 优秀，因为若 $Alice$ 取了照片 1，则 $Bonnie$ 只能取照片 2，此时权值之差大于 $Alice$ 取照片 2 的情况。

对于 $Bonnie$ 而言 $b_1 - a_2 >= b_2 - a_1$ ，因此 $Bonnie$ 的最优策略也是先取照片 1.

②
若 $a_1 + b_1 < a_2 + b_2$ 并且 $a_1 > b_2$

我们得到 $a_1 - b_2 < a_2 - b_1$ 与 $b_1 - a_2 < b_2 - a_1$

对于这种情况显然两人不会先取照片 1。

然而若游戏进行到某一时刻，当双方都没有最优情况可取， $Alice$ 仍然会选择取照片 1，因为 $a_1 - b_2 > 0$ 这样取能使差值变大。

考虑 $Bonnie$ ，变式得到 $b_2 - a_1 > b_1 - a_2$

我们知道 $a_1 > b_2$ 因此右边的值为负数，所以如果 $Bonnie$ 取了照片 1，则差值一定变大，因此 $Bonnie$ 不论如何都不会取照片 1.

因此这种情况对答案的贡献为 $a_1 - b_2$

③
若 $a_1 + b_1 < a_2 + b_2$ 并且 $b_1 > a_2$

分析同上，对答案的贡献为 $a_2 - b_1$

④
若 $a_1 + b_1 < a_2 + b_2$ 并且 $a_1 <= b_2, b_1 <= a_2$
经过分析可以知道：

$a_1 - b_2$ 与 $b_1 - a_2$ 均 $<=0$，因此这对照片可以直接忽略。

现在我们把情况简化到了只有一种。

考虑如何处理情况 1

对于一张照片 $i$ ，若 $Alice$ 取了这张照片，那么对答案的贡献为 $a_i$

反之对答案的贡献为 $-b_i$

考虑怎么综合这两种情况。

我们把一张照片的权值变为 $((a_i + b_i) / 2,(a_i + b_i) / 2)$，并且给一开始的答案加上 $(a_i - b_i) / 2$

这样处理，显而易见，若 $Alice$ 取了这张照片，贡献为 $(a_i + b_i) / 2 + (a_i - b_i) / 2 = a_i$
若 $Bonnie$ 取了，贡献为 $(a_i - b_i) / 2 - (a_i + b_i) / 2 = -b_i$

这样一来，每一张照片对于 $Alice$ 与 $Bonnie$ 就是等价的。

考虑对所有照片进行排序，由于我们按照 $(a_i + b_i) / 2$ 进行排序 与 按照 $a_i + b_i$ 进行排序结果是相同的，因此我们可以省掉除去的 2 ，节省可能的浮点运算。

因为 $a_1 + b_1 >= a_2 + b_2$，所以我们如果按从大到小排列好的照片序列取照片，一定满足先取了某一对照片中的第 1 张再取第 2 张。因此我们可以直接贪心地选取，让 $Alice$ 取最大的， $Bonnie$ 取次大的，一直这样取下去。如此一来，我们在累积答案的时候就可以忽略浮点数，让答案直接加上符合第 1 种情况照片对上每张照片的 $a_i$ ，当 $Alice$ 取的时候答案不加上 $a_i + b_i$ , $Bonnie$ 取的时候减去 $a_i + b_i$ 即可.

标程为从小到大排序，由于照片成对出现，所以把第奇数张都给 $Bonnie$ ，偶数张都给 $Alice$ (由于权值最大的照片排序后是第偶数张)

### **AC代码**
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int seq[200050];
int cnt,n;

int main()
{
	int a1,b1,a2,b2;
	scanf("%d",&n);
	long long ans = 0;
	for(int i = 1;i <= n; ++ i)
	{
		scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
		if(a1 + b1 >= a2 + b2)
		{
			seq[++cnt] = a1 + b1;
			seq[++cnt] = a2 + b2;
			ans += a1 + a2;
		}
		else if(a1 > b2)
			ans += a1 - b2;
		else if(b1 > a2)
			ans += a2 - b1;
	}
	sort(seq + 1,seq + 1 + cnt);
	for(int i = 1;i <= cnt;i += 2)
		ans -= seq[i];
	printf("%lld\n",ans);
}
```



  [1]: https://cn.vjudge.net/problem/CodeForces-725F

---

## 作者：EuphoricStar (赞：7)

不错的贪心题。

我们考虑一对照片只有一张的情况。那么先后手会按照 $a + b$ 降序取。因为若 $a_i + b_i \ge a_j + b_j$，变形得 $a_i - b_j \ge a_j - b_i$ 且 $b_i - a_j \ge b_j - a_i$，所以对于双方先取 $i$ 一定是不劣的。

回到原题，如果 $a_{i, 1} + b_{i, 1} \ge a_{i, 2} + b_{i, 2}$，那么 $(a_{i, 1}, b_{i, 1})$ 和 $(a_{i, 2}, b_{i, 2})$ 会成为先后手争夺的目标，因为双方都想取走上面的。我们把这种物品单独处理，也就是按照 $a + b$ 降序排序，然后先后手交替取。

取完这种物品后，就还剩下 $a_{i, 1} + b_{i, 1} < a_{i, 2} + b_{i, 2}$ 的物品，变形得 $(a_{i, 1} - b_{i, 2}) + (b_{i, 1} - a_{i, 2}) < 0$。分类讨论是哪一项 $< 0$：

- 如果 $a_{i, 1} - b_{i, 2} < 0$ 且 $b_{i, 1} - a_{i, 2} < 0$，那么这个物品就废掉了，因为双方都不想先取上面的物品，否则会给另一方带来收益。
- 如果 $a_{i, 1} - b_{i, 2} < 0$ 且 $b_{i, 1} - a_{i, 2} \ge 0$，那么 A 肯定不会取 $a_{i, 1}$，但是 B 取 $b_{i, 1}$ 一定不劣。这种情况我们把 $a_{i, 2} - b_{i, 1}$ 累加进答案。
- 否则 $a_{i, 1} - b_{i, 2} \ge 0$ 且 $b_{i, 1} - a_{i, 2} < 0$，这种情况跟上面是对称的，B 肯定不会取 $b_{i, 1}$，但是 A 取 $a_{i, 1}$ 一定不劣，把 $a_{i, 1} - b_{i, 2}$ 累加进答案。

[code](https://codeforces.com/problemset/submission/725/215451094)

---

## 作者：FutaRimeWoawaSete (赞：3)

**sol of CF725F**

注意题意，要求先选一对的第一张才能选第二张，不知道多少人被这 shaber 翻译祸害了。

第一眼感觉很像阿狸与桃子那道题。

我们先进行两次大的分类讨论：

- $a_1 - b_2 \geq a_2 - b_1$，此时也满足 $b_1 - a_2 \geq b_2 - a_1$，即互相都想选取第一张照片；

- $a_1 - b_2 < a_2 - b_1$，此时也满足 $b_1 - a_2 < b_2 - a_1$，即互相都不愿选择第一张照片；

不难想到对于第二类情况的约束性更强，对于第二类情况我们继续分讨：

- $a_1 - b_2 > 0$，即此时在最后没有选择的情况下 $A$ 会选第一张照片；

- $b_1 - a_2 > 0$，即此时在最后没有选择的情况下 $B$ 会选第一张照片;

- 可以证明上述两种情况在满足第二类大情况的前提下是不会一起出现的，否则会与第二类大情况的前提矛盾。

- 剩余的情况是 $a_1 - b_2 \leq 0$ 且 $b_1 - a_2 \leq 0$，则此时该对照片永远不会被选择。

发现第二类大情况的贡献独立，我们只需要考虑第一类大情况即可，设剩余 $x$ 对这样的照片。

将 $2\times x$ 张照片的值先都加上 $\frac{(a-b)}{2}$ 的贡献，将每张照片剩余的价值 $\frac{a+b}{2}$ 放入一个数组中降序排序，然后奇偶交题选择，若被 $A$ 选到就加上 $\frac{a+b}{2}$ 否则减去 $\frac{a+b}{2}$。

可以发现这样处理每张照片的贡献都是 $+a$ 或 $-b$ 的形式，并且由于 $a_1 - b_2 \geq a_2 - b_1$，降序排序后若已经决策到了一对照片的第二张照片，第一张照片已经被决策过了也是合法的选择。

```cpp
/*
2
5 1
0 -6
*/
#include "bits/stdc++.h"
using namespace std;
#define ll long long
const int Len = 2e5 + 5;
int n,m,ct;
double p[Len];double as;
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
	{
		int a1,b1,a2,b2;scanf("%d %d %d %d",&a1,&b1,&a2,&b2);
		if(a1 + b1 >= a2 + b2) 
		{
			as += 1.0 * (a1 - b1) / 2.0 , as += 1.0 * (a2 - b2) / 2.0;
			p[++ ct] = 1.0 * (a1 + b1) / 2.0;
			p[++ ct] = 1.0 * (a2 + b2) / 2.0;
		}
		else if(a1 > b2) as += a1 - b2;
		else if(b1 > a2) as += a2 - b1;
	}
	sort(p + 1 , p + 1 + ct);int opt = 0;
	for(int i = ct ; i >= 1 ; i --) 
	{
		opt ^= 1;
		if(opt) as += p[i];
		else as -= p[i];
	}
	printf("%.0lf\n",as);
	return 0;
}
```

---

## 作者：Yuby (赞：2)

[题面](https://www.luogu.com.cn/problem/CF725F)

点数：2900

##### 题意（复制过来的）：

有两个人 *Alice* 和 *Bonnie* 他们分别取照片，共有 $n$ 组照片，*Alice* 先取，每组照片有两张且必须先取第一张，再取第二张，每组照片对于 *Alice* 和 *Bonnie* 分别有价值 $A1$ , $B1$ , $A2$ , $B2$  ，分别表示 *Alice* 和 *Bonnie* 取每组照片的第一第二张能的得到的价值，假设 *Alice* 和 *Bonnie* 都足够聪明，他们都希望自己的价值减去别人的价值尽可能大，求 *Alice* 和 *Bonnie* 的价值差。

$n\leq100000$

##### 评价：

纯思维题（只要学过贪心即可）。

##### 算法分析：

首先注意到数据范围，$O(n \log n)$ 是可以的。

然后发现这个问题中子问题之间是独立的，因为无论哪一步取最后也要取完，这里注意是可取可不取，那就代表如果第一个以经被 *Alice* 去掉，那么等 *Bonnie* 去取一定。

所以，得到结论这题是贪心解决。

##### 具体分析：

在上面的废话后，我们开始分情况讨论。

考虑一下几种情况：

1.$ A1 + B1 \geq A2 +B2 $,为什么会想到这个呢？因为这个式子的变形为 $A1 - B2 \geq A2 - B1$，$B1 - A2 \geq B2 -A1 $。就是说两人都希望取第一张，不能确定对答案的贡献。

  下面为 $ A1 + B1 < A2 +B2 $，且必须要取，否则游戏结束。

2.  $ A1 > B2 $ 显然 $A1 - B2 < A2 - B1$，$ B1 - A2 < B2 - A1$，而且 $A1 - B2 > 0$，那么因为当前考虑必取所以如果为 *Alice* 还是会取第一张仍然为正贡献，如果为 *Bonnie* 那么因为取第一张为负贡献所以他一定只取第二张。因此这种情况的贡献为 $A1 - B2$。
3.  $ B1 > A2 $ 显然与上面同理，贡献为 $A2 - B1$。
4.  $ A1 \leq B2 $，那么得到 $B1 \leq A2$。之后带入得 $A1 - B2 \leq 0$ 且 $B1 - A2 \leq 0$，双方宁可游戏结束也不愿意取，所以游戏结束，不会有人取，对答案无贡献。

所以综合上面的，只有第一种情况需要贪心其他都为必然可以开始贪心了，下面的分析都是针对第一种情况。

考虑第 $i$ 组图片。

那么推一推式子。发现如果我们直接把答案上加 $A1 + A2 $ 然后把第一种情况中的两种情况变形为 $A1 + B1$、$A2 + B2$，我们发现取哪一个就减去哪一个即可。现在可以把每个 $i$ 得到的上面两个式子加入到一个数组中然后从小到大排序，这代表我们可以贪心了。

由于是从小到大排序，所以对于一组图片较大的在后面（成对出现），那么我们只需把第奇数张给 *Bonnie* ，然后第偶数张给 *Alice* 即可，即把减去所有第奇数个的价值，从 $0$ 开始存的话是第偶数个。

核心代码：

```cpp
ll n;
vector<ll>num; 
int main()
{
    n=read();
    ll ans=0; 
    for(ll i=1;i<=n;i++)
    {
    	ll a1=read(),b1=read(),a2=read(),b2=read();
    	if(a1+b1>=a2+b2)
    	{
    		num.push_back(a1+b1),num.push_back(a2+b2);
    		ans+=a1+a2;
		}
		else if(a1>b2)
		{
			ans+=a1-b2;
		}
		else if(b1>a2)
		{
			ans+=a2-b1;
		}
	}
	sort(num.begin(),num.end());
	for(ll i=0;i<num.size();i+=2)
	{
		ans-=num[i];
	}
	write(ans);
	return 0;
}
```



---

## 作者：Reaepita (赞：2)

对于每组照片我们分情况讨论：

情况 ① :$$A_1+B_1>=A_2+B_2(A_1-B_2>=A_2-B_1)$$

情况 ② :$$A_1+B_1<A_2+B_2(A_1-B_2<A_2-B_1)$$


对于情况 ① 

若 *Alice* 先取则对答案的贡献最大，为 $A_1-B_2$ 对 *Alice* 
最优

若 *Bonnie* 先取则对答案的贡献最小，为 $A_2-B_1$ 对 *Bonnie* 
最优

所以他们两个都想先取这组照片。

对于情况 ②
若 $A_1>B_2$ 则 $B_1<A_2 $ 那么对于 *Alice* 来说先让 *Bonnie* 取这组更优

但 *Bonnie* 同样十分聪明，所以 *Bonnie*永远不会取这组，而 *Alice* 就会取这组(这样也能对答案产生 $A_1-B_2$ 的贡献)

若 $A_1<B_2$ 同理 *Bonnie* 会先取这组对答案产生 $A_2-B_1$ 的贡献

经过以上分析我们可以发现，真正需要考虑的是情况 ①，而情况 ②直接求值就行了

我们可以考虑使用一个数组来存储 $A_1+B_1$ ,$A_2+B_2$ 的值，并且直接在最终答案上加 $A_1+A_2$，再对数组从小到大排序
对于数组的奇数位，我们用最终答案减去当前位的值

为什么这样做的答案是正确的？

若当前为 $A_1+B_1$ 则最后答案对于这一组照片得到的价值为 $A_1+A_2-A_1-B_1$
否则为 $A_1+A_2-A_2-B_2$
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100000+10;
int n,a[maxn*2],top=0;
int a1,b1,a2,b2;
long long ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
		if(a1+b1>=a2+b2)
		{
			a[++top]=a1+b1;
			a[++top]=a2+b2;
			ans+=a1+a2;
		}
		else if(a1>b2)ans+=a1-b2;
		else if(a2<b1)ans+=a2-b1;
	}
	sort(a+1,a+1+top);
	for(int i=1;i<=n*2;i+=2)ans-=a[i];
	printf("%lld\n",ans);
}
```

---

## 作者：18lxxrz (赞：2)

这道题……


------------

把这些值排个序，由于是AB轮流取，A每次会选最大值因为A不想让答案损失太大，B每次会选最大值因为B想要答案损失最大，所以排完序后把奇数位置（假设从0开始）的给A，偶数位置的给B即可，由于把照片给A的情况对答案的贡献已经累加，所以只需要把给B的照片对答案的损失减去即可 


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1000000+100;
int n,a1,b1,a2,b2,a[maxn],res; 

int main ()
{
    while(~scanf("%d",&n)&&n)
    {
        ll ans=0;
        res=0;
        while(n--)
        {
           scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
            if(a1+b1<a2+b2)
            {
                if(a1>b2)ans+=a1-b2;
                else if(b1>a2)ans+=a2-b1;
            }
            else 
                ans+=a1+a2,a[res++]=a1+b1,a[res++]=a2+b2;
        }
        sort(a,a+res);
        for(register int i=0;i<res;i+=2)
			ans-=a[i];
        printf("%I64d\n",ans);
    }
    return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

神仙博弈。

根据取得的价值不同，有一些照片是两个人抢着要的，有一些只能主动让给对方，剩下的则是两个人都不要的垃圾。

不妨定义以第一个人为主视角，一次取照片的价值为所提供的的差值。这样的话，第一个人就是要求总价值最大，第二个就是要求最小。

先推一下一般式子，当第一个人取第一个照片的时候价值为：$a_1-b_2$，取第二个，也就是自己不取，而让第二个人取第一个的价值为：$a_2-b_1$.

若 $a_1-b_2>0$ 也就是取第一张照片会使得差值增大，那么如果最后能取这一张就一定会取，反之如果 $a_1-b_2<0$ 就一定不取，因为如果取了就会使得差值减小，反而对对方有利。对于另一种方法也是一样分析。

形式化地，有：

1. 若 $a_1-b_2>0$ 且 $a_2-b_1>0$ 那么发现这一组照片第一个人想取，第二个人不可能取，所以直接有 $a_1-b_2$ 的贡献。

2. 若 $a_1-b_2<0$ 且 $a_2-b_1<0$ 和上面一种类似，第一个人不取，第二个人想取，所以直接有 $a_2-b_1$ 的贡献。

3. 若 $a_1-b_2<0$ 且 $a_2-b_1>0$ 两个人都不想取，所以这一组照片没有任何贡献。

4. 若 $a_1-b_2>0$ 且 $a_2-b_1<0$ 那么两个人都想取这一组照片，也就是两人争夺。

可以发现，如果在存在第四种情况的同时还存在第一种或者第二种情况，后两者的优先级肯定是劣于前者，因为可以认为前两者的中都会有一个人放弃，所以另一个人无论什么时候取都是一样的。

---

接下来考虑第四种情况照片到底归谁。

这里使用贪心，先将答案加上 $a_1+a_2$ 并加入决策项 $a_1+b_2$ 和 $a_2+b_1$，这样去哪一个就是直接减去那一个。

于是这样就有形式化的决策了，直接从小到大排序，按照奇偶项分配给第一个人和第二个人就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,a[200005],cnt,ans,x1,x2,y1,y2;
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++){
		scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
		if(x1+y1>x2+y2){
			a[++cnt]=x1+y1;
			a[++cnt]=x2+y2;
			ans+=x1+x2;
			continue;
		}
		if(x1>y2){
			ans+=x1-y2;
			continue;
		}
		if(y1>x2){
			ans+=x2-y1;
			continue;
		}
	}
	sort(a+1,a+cnt+1);
	for(int i=1;i<=cnt;i+=2){
		ans-=a[i];
	}
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：MSavannah (赞：0)

## Statement

有 $n$ 对照片，两个人 $A$ 和 $B$ 轮流取，$A$ 先取。**取照片时，必须先取那对照片的第一张，再取第二张。** 每对照片有四个值 $a_1,b_1,a_2,b_2$，表示第一张和第二张对 $A$ 和 $B$ 来说的喜悦值。轮到一个人时，她可以选择不取，如果连续两轮中 $A$ 和 $B$ 都选择不取那么游戏结束。双方都希望自己的喜悦值与对方的喜悦的差尽量大。假设两个人都采用最佳策略，求最后 $A$ 的喜悦值和 $B$ 的喜悦值的差值。

## Solution

考虑如果没有“对于每一对，取了第一张才可以取第二张”的限制怎么做。显然如果选 $(a_1,b_1)$ 更优，就说明 $a_1-b_2\geq b_1-a_2$ 移项之后发现只需要按照 $a+b$ 降序选取就可以了。

如果加上限制，对于 $a_1+b_1\geq a_2+b_2$ 的照片对，显然两个人都以取走第一张为最有策略，对于一对来说一定能保证第一张先取再取第二张且所有照片都会被取光，直接排序先后手轮流取就可以了。

对于 $a_1+b_1<a_2+b_2$ 的照片对，移项得到 $(a_1-b_2)+(b_1-a_2)<0$。

分类讨论：

1. $a_1-b_2<0$ 且 $b_1-a_2<0$ 那么肯定谁都不选。

2. $a_1-b_2\geq 0$ 且 $b_1-a_2<0$ 那么 $A$ 会选，给答案带来 $a_1-b_2$ 的贡献。

3. $a_1-b_2<0$ 且 $b_1-a_2\geq 0$ 那么 $B$ 会选，给答案带来 $a_2-b_1$ 的贡献。

[code](https://www.luogu.com.cn/record/167780729)

---

## 作者：king_xbz (赞：0)

贼麻烦的一道题，也是蛮有趣的一道博弈论。

首先很清楚需要分类讨论$a_1-b_2≥a_2-b_1$的情况和$a_1-b_2<a_2-b_1$

在第一种情况下策略是取$a_1$,取$b_2$,此时两人最优策略都是先去取第一张。

对于第二种情况

若$a_1>b_2$，尽管先取b是更优的策略，但是在没得选的情况下，A还是要先选第一个，这样可以扩大领先优势，贡献是$a_1-b_2$。

否则的话相反，B会取b，A会取a，贡献是$a_2-b_1$

然后进行排序，让A选最大的，B选次大的，这就是两人的最优策略。

代码:

```cpp
#include<bits/stdc++.h>
#define fint register int
#define N 347895
#define int long long
using namespace std;
int ans[N];
signed main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	int cnt=0;
	int aa=0,bb=0;
	while(n--)
	{
		int a,b,x,y;
		cin>>a>>b>>x>>y;
		if(a-y>=x-b)
		{
			aa+=a+x;
			ans[++cnt]=a+b,ans[++cnt]=x+y;
		}
		else
		if(a-y<x-b)
		{
			if(a>y)
			aa+=a,bb-=y;
			else
			if(b>x)
			aa+=x,bb-=b;
		}
	}
	sort(ans+1,ans+cnt+1);
	int jian=0;
	for(fint i=1;i<=cnt;i+=2)
	jian-=ans[i];
	cout<<aa+bb+jian;
	return 0;
}
```

# 

---

