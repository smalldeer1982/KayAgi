# Cat, Fox and Maximum Array Split

## 题目描述

This is an interactive problem.

Fox gave Cat two positive integers $ n $ and $ k $ . She has a hidden array $ a_1, \ldots , a_n $ of length $ n $ , such that $ 1 \leq a_i \leq n $ for every $ i $ . Now they are going to play the following game:

For any two integers $ l, r $ such that $ 1 \leq l \leq r \leq n $ , define $ f(l, r) = (r - l + 1) \cdot \max\limits_{x=l}^r a_x $ . In other words, $ f(l, r) $ is equal to the maximum of the subarray $ a_l, \ldots, a_r $ multiplied by its size.

Cat can ask Fox at most $ 2 n $ questions about the array. He will tell her two integers $ l $ and $ x $ ( $ 1 \leq l \leq n, 1 \leq x \leq 10^9 $ ), and she will tell him one integer $ p $ as the answer — the smallest positive integer $ r $ such that $ f(l, r) = x $ , or $ n+1 $ if no such $ r $ exists.

Now, Cat needs to find the largest value $ m $ such that there exists a sequence $ c_1, \ldots, c_{k-1} $ such that $ 1 \leq c_1 < \ldots < c_{k-1} < n $ and $ f(1, c_1) = f(c_1 + 1, c_2) = \ldots = f(c_{k-1}+1, n) = m $ . If no such $ m $ exists, he should indicate this and take $ -1 $ as the answer. Note that for $ k = 1 $ , $ m $ is always equal to $ f(1, n) $ .

In other words, the goal is to find the largest $ m $ such that you can split the array into exactly $ k $ subarrays ( $ k $ is the constant given to you in the beginning of the interaction) so that all the subarrays have the product of their length and their maximum equal to $ m $ , or determine that no such $ m $ exists. Every element should belong in exactly one of the subarrays.

Cat doesn't know what he should do, so he asked you to play the game for him.

## 说明/提示

The hidden arrays in the three testcases are $ [1] $ , $ [1, 2] $ and $ [1, 3, 6, 1, 2, 1] $ . In the second testcase, no split satisfies the constraints, so the answer is $ -1 $ .

The answer for the first query of the third testcase is $ 7 $ since no valid $ r $ exists. For the second query of the third testcase, since $ 2 \cdot \max(1, 3) = 6 $ , we will get $ 2 $ as the answer, since $ r = 1 $ doesn't satisfy the constraint.

The sample interaction guessed all three answers ( $ 1, -1 $ and $ 6 $ ) correctly, so it received $ 1 $ after each answer.

## 样例 #1

### 输入

```
3
1 1

1
2 2

1

3

1
6 3

7

2

3

6

1```

### 输出

```
! 1


? 1 1

? 2 1

! -1


? 1 9

? 1 6

? 3 6

? 4 6

! 6```

# 题解

## 作者：g1ove (赞：10)

## 题意
给出长度为 $n$ 的数组和整数 $k$，定义 $f(l, r) = (r - l + 1)\times\max_{x=l}^ra_x$，询问是否存在一个最大值 $m$，使得把 $a$ 数组分成 $k$ 段后，使得每段 $f(l,r)=m$ 都成立。若无解 $m=-1$。输出 $m$。

你可以询问交互库 $2n$ 次，每次给出 $l,x$ 两个参数，交互库会回答一个满足 $f(l,r)=x$ 最小的 $r$。**如果不存在 $r$，则交互库会回答 $n+1$**。

注意，你并不知道 $a$ 数组中的元素。

交互库询问格式：`? l x`

答案输出格式：`! m`

注意输出空行和刷新。

对于每次你输出的答案，如果正确，交互库会给出 `1`，错误则给出 `-1`。请使用一个变量存储这个输入。

$\sum n\le 10^4$。
## 思路
神秘交互题。

首先，题目只给了我们 $2n$ 次询问交互库的次数，这让我们只能往线性方面思考。

观察答案有什么特点，明显的，答案总有一个区间覆盖了 $m=\max_{x=1}^na_x$。

我们不妨往这个方向思考一番。根据 $m$ 总会被区间覆盖，而且长度不固定，不难得出 $ans$ 如果存在一定是 $m$ 的倍数。

现在我们缩小了答案的区间。

我们想想怎么得到 $m$。不难发现，$f(1,n)=m\times n$，是固定的。我们可以通过从小到大询问 $m\times n$ 来得到 $m$。最劣情况下，我们使用了 $n$ 次询问。

我们现在知道了答案的下界，那么能不能推个上界出来呢？

根据 $f$ 这个式子的优良性质，我们可以得到一个显然的结论：$f(l,r)\ge f(l,k)+f(k+1,r)$。

假设 $ans=t\times m$。

我们可以归纳得到：$ans\times k\le f(1,n)$。

然后变一下这个式子：$t\times m\times k\le n\times m$。

所以 $t\le \frac{n}{k}$。

现在做法已经很明显了。我们枚举每个 $m$ 的倍数，总共会枚举 $\frac{n}{k}$ 次，然后每次验证答案最多会询问 $k$ 次，最多询问 $n+\frac{n}{k}\times k=2n$ 次。在答案中取最大值即可，可以通过此题。

最后留给读者一个思考：其实如果存在答案的话，答案是唯一的。读者可以自己证明一下。

code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 10005
using namespace std;
int n,k,m,res;
int g;
int main()
{
	scanf("%d",&g);
	while(g--)
	{
		scanf("%d%d",&n,&k);
		for(int i=n;i>=1;i--)
		{
			int x;
			printf("? %d %d\n",1,n*i);
			fflush(stdout);
			scanf("%d",&x);
			if(x<=n)
			{
				m=i;
				break;
			}
		}
		res=0;
		for(int i=1;i<=n/k;i++)
		{
			bool ok=1;
			int lst=1;
			for(int j=1;j<=k;j++)
			{
				if(lst>n)
				{
					ok=0;
					break;
				}
				int x;
				printf("? %d %d\n",lst,i*m);
				fflush(stdout);
				scanf("%d",&x);
				lst=x+1;
			}
			if(lst!=n+1) ok=0; 
			if(ok)
			{
				res=1;
				printf("! %d\n",i*m);
				fflush(stdout);
				break;
			}
		}
		if(!res) 
		{
			printf("! -1\n");
			fflush(stdout);
		}
		scanf("%d",&res);
	}
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

典中典想到倒数第二步。

首先可以发现 $f(l,r)$ 对于 $r$ 单增，所以一个查询 $l,x$，一定只存在一个 $r$ 满足条件。因此对于一个 $m$，我们可以直接从 $1$ 开始查询 $m$，看是否将 $a$ 数组分成 $k$ 段即可。每个 $m$ 需要花费 $k$ 次查询，所以我们至多枚举 $\dfrac{2n}{k}$ 个 $m$ 来依次判断。

再考虑上面的查询。由于需要查询具体的 $x$，所以在 $2n$ 次操作内能得到的信息极其有限。由于 $f(l,r)$ 中包含 $\max$，因此可以想到 $f(1,n)$ 一定等于 $\max \times n$，所以枚举 $\max$，再对于 $l=1$ 查询 $\max \times n$ 对应的 $r$ 是否存在，最多花费 $n$ 次查询就可以判断 $\max$ 的具体值。现在我们至多枚举 $\dfrac{n}{k}$ 个 $m$ 来依次判断。

由于 $f(l,r)$ 中包含 $\max$，所以只要有区间 $[l,r]$ 包含 $\max$，其 $f(l,r)$ 一定为 $\max$ 的倍数，所以最后的答案 $m$ 也一定为 $\max$ 的倍数。

考虑 $m$ 一定为 $\max$ 的倍数对枚举 $m$ 带来的影响。首先就可以枚举 $p$ 表示 $m$ 为 $\max$ 的 $p$ 倍，结合现在我们至多枚举 $\dfrac{n}{k}$ 个 $m$ 来依次判断，考虑 $p$ 的范围如何限制。

一个显然的性质 $f(l,r) \geq f(l,x) + f(x+1,r)(l \leq x < r)$。所以可以得到 $k \times m = k\times p \times \max \leq f(1,n) = \max \times n$，所以 $p \times k \leq n$，$p$ 的范围被缩小到 $\dfrac{n}{k}$ 内，因此直接枚举 $p$ 即可。

---

## 作者：DerrickLo (赞：1)

记 $p=\displaystyle{\max_{i=1}^{n}a_i}$，那么显然 $m$ 是 $p$ 的倍数，所以我们先考虑如何求出 $p$。

求出 $p$ 是不难的。$p$ 满足 $f(1,n)=p\times n$，所以我们只需要通过 $n$ 次枚举来找到 $p$。

接下来考虑 $m$ 的上界。记分割完之后包含 $p$ 的这一段长度为 $l$，那么 $m=l\times p$。对于其他段，由于最大值必然 $\le p$，所以长度必然 $\ge l$，那么总长度就 $\ge k\times l$，所以 $k\times l\le n$，也就是说 $l\le \lfloor\displaystyle{\frac{n}{k}}\rfloor$。

而对于每个 $l$，我们可以贪心地通过不超过 $k$ 次询问来找到答案，也就是说总询问次数不超过 $n+\lfloor\displaystyle{\frac{n}{k}}\rfloor\times k\le 2n$ 次，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		int maxx=0,x;
		for(int i=n;i;i--){
			cout<<"? "<<1<<" "<<n*i<<endl,cin>>x;
			if(x!=n+1){
				maxx=i;
				break;
			}
		}
		int flag=0;
		for(int i=n/k;i;i--){
			int now=1,cnt=0,ff=1;
			while(cnt<k){
				if(now>n){
					ff=0;break;
				} 
				cout<<"? "<<now<<" "<<maxx*i<<endl,cin>>x;
				if(x==n+1){
					ff=0;break;
				}
				cnt++,now=x+1;
			}
			if(!ff)continue;
			if(cnt==k&&now==n+1){
				cout<<"! "<<maxx*i<<endl;cin>>x;
				flag=1;break;
			}
		}
		if(!flag){
			cout<<"! -1"<<endl;cin>>x;
		}
	}
	return 0;
}
```

---

## 作者：Robin_kool (赞：0)

恶臭交互题。

考虑 $2 \times n$ 这个神秘的限制。

题目中给的 $f(l,x)$ 包含一个乘数为某段区间内的最大值。这让我们想到了先找出答案 $m$ 的下界，即整个序列的最大值。这个很简单，只需要暴力枚举最大值 $i$，询问 $f(1,i\times n)$ 即可。不难发现 $1 \leq i \leq n$，故这一部分最多处理 $n$ 次，我们仍有 $n$ 次的询问机会。

还能够发现 $f(l,r) \geq f(l,x)+f(x+1,r) (l \leq x < r)$，因为对于包含且比它小的区间，最大值一定是不劣的，而即使两段分开的区间最大值都为 $\max_{i=l}^r a_i$，贡献也是与原来一样。

假设 $ans = t \times m$。

对于我刚刚所说的最优情况拓展至 $k$ 段，可得到 $ans\times k \leq f(1,n)$。

大力展开，得到 $t \leq \frac{n}{k}$。

那么可以暴力枚举每个 $t'(1\leq t' \leq \frac{n}{k})$，然后让后面的段能尽量远就尽量远，超出了 $n$ 就说明 $t'$ 不满足。最多询问 $\frac{n}{k} \times k = n$ 次。此处省略向下取整。

综上所述，最劣情况也只是询问 $2n$ 次，不会超出范围。

代码很短，读者自行解决。

---

