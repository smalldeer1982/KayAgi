# Birthday Gift

## 题目描述

Yarik's birthday is coming soon, and Mark decided to give him an array $ a $ of length $ n $ .

Mark knows that Yarik loves bitwise operations very much, and he also has a favorite number $ x $ , so Mark wants to find the maximum number $ k $ such that it is possible to select pairs of numbers \[ $ l_1, r_1 $ \], \[ $ l_2, r_2 $ \], $ \ldots $ \[ $ l_k, r_k $ \], such that:

- $ l_1 = 1 $ .
- $ r_k = n $ .
- $ l_i \le r_i $ for all $ i $ from $ 1 $ to $ k $ .
- $ r_i + 1 = l_{i + 1} $ for all $ i $ from $ 1 $ to $ k - 1 $ .
- $ (a_{l_1} \oplus a_{l_1 + 1} \oplus \ldots \oplus a_{r_1}) | (a_{l_2} \oplus a_{l_2 + 1} \oplus \ldots \oplus a_{r_2}) | \ldots | (a_{l_k} \oplus a_{l_k + 1} \oplus \ldots \oplus a_{r_k}) \le x $ , where $ \oplus $ denotes the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Exclusive_or), and $ | $ denotes the operation of [bitwise OR](https://en.wikipedia.org/wiki/Logical_disjunction).

If such $ k $ does not exist, then output $ -1 $ .

## 说明/提示

In the first test case, you can take $ k $ equal to $ 2 $ and choose two segments \[ $ 1, 1 $ \] and \[ $ 2, 3 $ \], $ (1) | (2 \oplus 3) = 1 $ . It can be shown that $ 2 $ is the maximum possible answer.

In the second test case, the segments \[ $ 1, 1 $ \] and \[ $ 2, 2 $ \] are suitable, $ (1) | (1) = 1 $ . It is not possible to make more segments.

In the third test case, it is not possible to choose $ 2 $ segments, as $ (1) | (3) = 3 > 2 $ , so the optimal answer is $ 1 $ .

## 样例 #1

### 输入

```
8
3 1
1 2 3
2 2
1 1
2 2
1 3
2 3
0 0
3 2
0 0 1
4 2
1 3 3 7
2 2
2 3
5 0
0 1 2 2 1```

### 输出

```
2
2
1
2
3
-1
1
2```

# 题解

## 作者：lfxxx (赞：10)

考虑给 $x$ 加 $1$ 限制变成小于 $x$。

那么枚举 $x$ 的某一位 $1$，小于的限制等价于对于这一位前面的所有 $0$ 或起来的值是 $0$ 这一位同样要求是 $0$ 后面的位没有限制。

现在变成 $\log V$ 个问题，每个问题的限制是某些位一定是 $0$，又因为是或起来，所以划分的 $k$ 段每段也需要满足这个限制。

然后由于异或的性质，事实上要求的是每一段限制的位数出现次数是偶数，直接每次贪心的取一段极短合法前缀删掉即可。

总复杂度是 $O(n \log^2 V)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+114;
int a[maxn],n,x;
int ans;
vector<int> dight;
int cnt[31];
int calc(){
    for(int i=0;i<31;i++) cnt[i]=0;
    int sum=0;
    for(int i=1;i<=n;i++){
        for(int x:dight){
            if((1ll<<x)&a[i]) cnt[x]++;
        }
        bool flag=true;
        for(int x:dight) if(cnt[x]%2==1) flag=false;
        if(flag==true){
            for(int x:dight) cnt[x]=0;
            sum++;
        }
    }
    for(int x:dight) if(cnt[x]%2==1) return -1;
    return sum;
}
void work(){
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>a[i];
    x++;
    ans=-1;
    dight.clear();
    for(int i=30;i>=0;i--){
        if((1ll<<i)&x){
            dight.push_back(i);
            ans=max(ans,calc());
            dight.pop_back();
        }else{
            dight.push_back(i);
        }
    }
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
}
```

---

## 作者：NightDiver (赞：8)

看到位运算，我们可以按位考虑，毕竟 ```^ | &``` 都不进位（以下的“位”均为二进制下的）。

对 $x$，我们从高位向低位考虑。由于 $2$ 的幂的性质，高位若“胜负已分”，则低位不会对相对大小关系产生影响，这么做是可行的。

现在我们的复杂度添上了一层 $\log$。

接着考虑，由于或``` | ```运算的性质，对于所有数的某一位来说，一旦出现了一个 $1$，那么或之和中这一位必定为 $1$。

由此，我们进行分类讨论。

1.若 $x$ 的这一位是 $1$，那么不等式左侧部分值的这一位可 $0$ 可 $1$。

2.若 $x$ 的这一位是 $0$，那么不等式左侧部分值的这一位只能是 $0$，若有 $1$，则我们不得不用异或的性质将 $1$ 消去。

那么如何将 $1$ 消去呢？

从第一个该位为 $1$ 的数开始考虑，由于我们不能打乱序列的顺序，所以第一个这样的数只能和第二个这样的的数抵消，第三个数不得不和第四个进行抵消。

![](https://cdn.luogu.com.cn/upload/image_hosting/obzhufdd.png)

上图大括号内进行异或，竖直分割线表示相邻两个异或和之间或。

注意，上述操作都是**不得不**这样做的，所以如果进行不下去，那么就说明无解TAT。

需要注意的是：分类讨论的第一种情况的"可 $0$"情况之后就没必要进行下去了，因为后面要进行更多的合并，答案一定不优于现有的。

具体到代码实现上来说，一个大括号内的异或和可以存到大括号开头的位置上，其余位置打上 $-1$ 的标记，下次遍历到直接不管。

[代码在这里](https://www.cnblogs.com/TongKa/p/18122463)

---

## 作者：hao_zi6366 (赞：4)

## 题目分析
 
显然，由于或运算和异或运算不进位，我们可以按位分析，统计出每一位上 $1$ 的个数，存在两种情况： 
- 当这一位是出现**奇数**个 $1$ 时，无论如何拆分，所得结果中这一位一定是 $1$；
- 当这一位是出现**偶数**个 $1$ 时，显然，可以通过拆分，让所得结果中这是 $1$ 或 $0$。  

所以我们从高位到低位依次分析这一位的情况，存在：
- $x$ 上该位是 $1$，当前位可以改变，使用掩码（见代码）统计答案；
- $x$ 上该位是 $1$，当前位是 $1$，不用管；
- $x$ 上该位是 $0$，当前位是可以改变，要更新掩码；
- $x$ 上该位是 $0$，当前位是 $1$，就保证不了比 $x$ 小了，要跳出循环。

最后输出就好啦。  

小贴士：等于不好判断，通过让 $x$ 自增来优化判断条件。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define inf 0x7fffffff
typedef long long ll;
int main(){
	/*freopen("xxx.in","r",stdin);
	freopen("xxx.out","w",stdout);*/
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
	
    int t;
	std::cin>>t;
	while(t--){
        int n,x;
        std::cin>>n>>x;
        std::vector<int> a(n+1),pre(n+1),cnt(31);
        for(int i=1;i<=n;i++){
            std::cin>>a[i];
            pre[i]=pre[i-1]^a[i];       //前缀异或
            for(int j=0;j<=30;j++){
                cnt[j]+=(a[i]>>j&1);    //每一位上1的个数
            }
        }
        if(pre[n]>x){                   //分不了
            std::cout<<"-1\n";continue;
        }
        x++;    //让<=变成<
        int msk=0;  // 掩码
        int ans=0;
        for(int i=30;i>=0;i--){
            if(x&(1<<i)){           //x在第i位上是1
                if(!(cnt[i]&1)){    //cnt[i]是偶数
                    int sum=0;
                    for(int j=1;j<=n;j++){
                        sum+=((pre[j]&(msk|(1<<i)))==0); //用掩码统计可以分成的组数
                    }
                    ans=std::max(sum,ans);
                }
            }else{
                if(cnt[i]&1)break;  //x上是0，当前位是1就保证不了比x小了
                msk|=(1<<i);
            }
        }
        std::cout<<ans<<"\n";
    }
	return 0;
}
```

---

## 作者：xyz105 (赞：4)

来写个较其它题解更玄学一点的做法。


### 题目描述

给定两个整数 $n,x$ 和长度为 $n$ 的序列 $a$，求出最大的 $k$ 使得整个序列 $a$ 可以被分成相邻的 $k$ 个区间 $[l_1,r_1],[l_2,r_2],[l_3,r_3],\ldots,[l_k,r_k]$，满足：

- 这些区间刚好覆盖 $[1,n]$，且没有交集。
- $(a_{l_1}\oplus a_{l_1+1}\oplus \ldots\oplus a_{r_1})|(a_{l_2}\oplus a_{l_2+1}\oplus \ldots\oplus a_{r_2})|\ldots|(a_{l_k}\oplus a_{l_k+1}\oplus \ldots\oplus a_{r_k})\le x$，其中 $\oplus$ 为按位异或运算， $|$ 为按位与运算。


### 解题思路

首先形如 $(a_l\oplus a_{l+1}\oplus \ldots\oplus a_r)$ 的表达式让人不由得联想到前缀异或和，即设

$$s_i=a_1\oplus a_2\oplus \ldots\oplus a_i$$

特别地，令 $s_0=0$。则根据异或运算的特性，有

$$\begin{aligned} a_l\oplus a_{l+1}\oplus \ldots\oplus a_r&=(a_1\oplus a_1)\oplus(a_2\oplus a_2)\oplus\ldots\oplus(a_l\oplus a_{l+1}\oplus \ldots\oplus a_r) \\ &=(a_1\oplus a_2\oplus \ldots\oplus a_{l-1})\oplus(a_1\oplus a_2\oplus \ldots\oplus a_r) \\ &=s_{l-1}\oplus s_r \end{aligned}$$

于是题目中最后一个条件变为：

$$(s_{l_1-1}\oplus s_{r_1})|(s_{l_2-1}\oplus s_{r_2})|(s_{l_3-1}\oplus s_{r_3})|\ldots|(s_{l_k-1}\oplus s_{r_k})\le x$$

又注意到对于任意 $1\le i<k$，有 $r_i+1=l_{i+1}$，所以 $l_{i+1}-1=r_i$。故上式变为：

$$(0\oplus s_{r_1})|(s_{r_1}\oplus s_{r_2})|(s_{r_2}\oplus s_{r_3})|\ldots|(s_{r_{k-1}}\oplus s_{r_k})\le x$$

其中 $(0\oplus s_{r_1})$ 实际上就是 $s_{r_1}$。

> 引理：对于两个非负整数 $a,b$，有 $a|(a\oplus b)=a|b$。
>
> 证明：  
> $\qquad$ 按二进制位考虑。  
> $\qquad$ 对于任意位，若 $a$ 在该位上是 $1$，则 $a|(a\oplus b)$ 在该位的值必然是 $1$。  
> $\qquad$ 若 $a$ 在该位上是 $0$，则 $b$ 在该位上只有为 $1$，才能使 $a|(a\oplus b)$ 在该位的值也为 $1$。  
> $\qquad$ 综上，$a|(a\oplus b)$ 在某一位的值是 $1$ 当且仅当 $a$ 和 $b$ 当中至少一个在该位的值也是 $1$，相当于 $a|(a\oplus b)=a|b$，证毕。

使用上述结论，上式可进一步做如下改变：

$$\begin{aligned} (0\oplus s_{r_1})|(s_{r_1}\oplus s_{r_2})|(s_{r_2}\oplus s_{r_3})|(s_{r_3}\oplus s_{r_4})|\ldots|(s_{r_{k-1}}\oplus s_{r_k})&\le x \\ (s_{r_1}|(s_{r_1}\oplus s_{r_2}))|(s_{r_2}\oplus s_{r_3})|(s_{r_3}\oplus s_{r_4})|\ldots|(s_{r_{k-1}}\oplus s_{r_k})&\le x \\ s_{r_1}|(s_{r_2}|(s_{r_2}\oplus s_{r_3}))|(s_{r_3}\oplus s_{r_4})|\ldots|(s_{r_{k-1}}\oplus s_{r_k})&\le x \\ s_{r_1}|s_{r_2}|(s_{r_3}|(s_{r_3}\oplus s_{r_4}))|\ldots|(s_{r_{k-1}}\oplus s_{r_k})&\le x\end{aligned}$$

最终得出 $s_{r_1}|s_{r_2}|s_{r_3}|\ldots|s_{r_k}\le x$，限制为 $1\le r_1<r_2<r_3<\cdots<r_k=n$。

现在考虑贪心的取数过程。假设初始时所有 $n$ 个数字（$s_1,s_2,s_3,\ldots,s_n$）都选，然后拆二进制位考虑（从高到低），根据 $x$ 的限制逐步删除那些不合法的数字。假定目前选的所有数字在第 $i$ 位上的按位与结果为 $a$，$x$ 的第 $i$ 位是 $b$。分类讨论：
- 若 $a=0,b=0$，选数情况不变。
- 若 $a=0,b=1$，则更低位的计算无需考虑 $x$ 的限制。此时应立即更新答案并输出结果，否则可能会在对更低位的处理中删掉更多数字。
- 若 $a=1,b=1$，说明通过现在删数使得 $a=0$（转化为上一种情况）并更新答案也是可以的（$x$ 的限制也满足啊）。可以对于现在选的这些数字创建一个用来满足 $a=0$ 的“副本”（实际代码实现中不必这么真正地写）。
  - 对于“副本”的操作：把这个“副本”中所有第 $i$ 位是 $1$ 的数字统统删掉，并用“副本”中剩余的数字个数更新答案。注意到 $r_k=n$，说明最后一个数字不能删，否则该操作不合法，不应执行。
  - 对于原先的那些数字，则保持选数情况不变，进行更低一位的计算。
- 若 $a=1,b=0$，则不得不在现在选的这些数字上直接进行删数操作。操作过程同上述情况中对于“副本”的操作，但如果该操作不合法则直接停止计算。

这样答案就能得出来了。


### 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 10;

int t, n, x, s[MAXN];

bool no[MAXN];

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &x);
		for (int i = 1; i <= n; i++)
			scanf("%d", s + i), s[i] ^= s[i - 1];
		memset(no, 0, sizeof(bool) * (n + 5));
		int ans = -1, res = n;
		for (int i = 29; i >= 0; i--)
		{
			bool i1 = 0;
			for (int j = 1; j <= n; j++)
				if (!no[j]) i1 |= ((s[j] >> i) & 1);
			if (!i1 && ((x >> i) & 1)) {ans = max(ans, res); break;}
			if (i1 && ((x >> i) & 1) && !((s[n] >> i) & 1))
			{
				int res1 = res;
				for (int j = 1; j <= n; j++)
					if ((s[j] >> i) & 1) res1 -= !no[j];
				ans = max(ans, res1);
			}
			if (i1 && !((x >> i) & 1))
			{
				if ((s[n] >> i) & 1) break;
				for (int j = 1; j <= n; j++)
					if ((s[j] >> i) & 1) res -= !no[j], no[j] = 1;
			}
			if (!i) ans = max(ans, res);
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
```

---

## 作者：Exp10re (赞：3)

学校模拟赛的签到题。

个人认为难度不止 `*1900`？可能是我做这类题目不太熟练。

## 解题思路

因为不同二进制位之间互不干扰，将其按照二进制位拆分。

记 $ (a_{l_1} \oplus a_{l_1 + 1} \oplus \ldots \oplus a_{r_1}) | (a_{l_2} \oplus a_{l_2 + 1} \oplus \ldots \oplus a_{r_2}) | \ldots | (a_{l_k} \oplus a_{l_k + 1} \oplus \ldots \oplus a_{r_k}) = S $，$a_1 \oplus a_2 \oplus \cdots \oplus a_n = M$ 。

下文称两个连续子段之间“有一个划分”。

对于每一个二进制位，不难证明有以下性质：

- 若 $M$ 在该位的值为 $1$，那么无论何种划分方式，$S$ 在该位的值都为 $1$。

- 否则，$S$ 在该位不为 $1$，当且仅当不存在 $i$，使得 $a_{l_i} \oplus a_{l_i + 1} \oplus \ldots \oplus a_{r_i}$ 在该位为 $1$。

则每一个二进制位的划分，有如下划分思路：

- 对于 $M$ 在该位的值为 $1$ 的情况，其无论如何划分均对答案无影响（即 $S$ 在该位必定为 $1$）。

- 否则 $\forall 1\leq i \leq n$，若 $a_i$ 在该位的值为 $1$，记为 $1$，否则记为 $0$，那么我们可以得到一个 $01$ 序列。如果我们想使得 $S$ 在该位为 $0$，那么在该 $01$ 序列的第 $2k-1$ 和第 $2k$（$k\in \mathbb{N}^+$）个 $1$ 之间不能有任何划分，否则如果我们想使得 $S$ 在该位为 $1$，无论如何划分均对答案无影响。

因此，我们考虑以下类似于数位 DP 的做法：

- 初始时默认每两个数之间都有一个划分。

- 从高位往低位枚举。

- 若 $M$ 在该位为 $1$，$x$ 在该位为 $0$，则显然无解。

- 若 $M$ 在该位为 $1$，$x$ 在该位为 $1$，则无论如何划分都不会影响答案。

- 若 $M$ 在该位为 $0$，$x$ 在该位为 $1$，那么尝试使用上文提到的划分方法使该位为 $0$。不难发现，若该位的高位均与 $x$ 相等，而该位为 $0$，那么低位的划分无意义，那么当前的划分情况就是一个答案，故尝试统计这种情况下划分的段数，在结束后输出最大值，然后不进行划分（即使该位为 $1$）再往低位进行枚举。

- 若 $M$ 在该位为 $0$，$x$ 在该位为 $0$，那么这一位必须使用上述方法设为 $0$。

类比数位 DP 不难发现这个思路正确。

时间复杂度 $O(n\log n)$。

## 代码

`check` 表示计算当前划分段数，`dec` 表示按照上述方法删除划分使得 $S$ 在该位为 $0$，`cop` 表示照上述方法删除划分使得 $S$ 在该位为 $0$ 之后尝试统计答案。

代码居然意外的短。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=101001;
long long a[MAXN],brk[MAXN],gt[MAXN],n,maxn;
long long check()
{
	long long i,ans=0;
	for(i=1;i<=n-1;i++)
	{
		ans+=brk[i];
	}
	return ans;
}
void dec(long long b)
{
	long long flag=0,i;
	for(i=1;i<=n-1;i++)
	{
		if(a[i]&b)
		{
			flag^=1;
		}
		if(flag==1)
		{
			brk[i]=0;
		}
	}
	return;
}
void cop(long long b)
{
	long long i;
	for(i=1;i<=n-1;i++)
	{
		gt[i]=brk[i];
	}
	dec(b);
	maxn=max(maxn,check());
	for(i=1;i<=n-1;i++)
	{
		brk[i]=gt[i];
	}
	return;
}
void work()
{
	maxn=0;
	long long x,m=0,i,t,b;
	scanf("%lld%lld",&n,&x);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		m^=a[i];
		brk[i]=1;
	}
	if(m>x)
	{
		printf("-1\n");
		return;
	}
	for(i=29;i>=0;i--)
	{
		b=(1<<i);
		if(m&b)
		{
			if(x&b)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if(x&b)
		{
			cop(b);
		}
		else
		{
			dec(b);
		}
	}
	if(i==-1)
	{
		maxn=max(maxn,check());
	}
	printf("%lld\n",maxn+1);
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：xiazha (赞：3)

好题。

拆位+贪心。

### Editorial

首先，将 $x$ 加一，题目变为小于 $x$ 的最大段数。

接着，我们设 $p_i$ 为 $a_1$ 至 $a_n$ 的异或和在二进制表示下的第 $i$ 位。$c_i$ 为 $x$ 在二进制表示下的第 $i$ 位。

然后倒序枚举每一位，分三种情况讨论：

- $a_i=1$，$c_i=1$ 或 $a_i=0$，$c_i=0$。

这种情况没有任何影响，忽略。

- $a_i=0$，$c_i=1$。

更新答案。统计答案只需暴力分段，若目前这一段异或和的第 $i$ 位为 $0$，则直接分为一段。

- $a_i=1$，$c_i=0$

终止循环。因为后面就算有第二种情况出现，也会受到第 $i$ 位与其之前位的限制。

初始我们设 $ans=-1$，这样就不用判断无解了。

### Solution

注意，下面的代码与上述内容不完全一致，因为这样可以省去一些码长，请读者自行理解。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,x,ans,a[100005];
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>x;x++;
		for(int i=1;i<=n;i++) cin>>a[i],a[i]^=a[i-1];
		ans=-1;
		for(int i=30,y=0;i>=0;i--) 
			if(x&(1<<i))
			{
				y|=(1<<i);
				int cnt=0;
				if(a[n]&y)
				{
					y^=(1<<i);
					continue;
				}
				for(int i=1;i<=n;i++)
					if((a[i]&y)==0)
						cnt++;
				ans=max(ans,cnt);
				y^=(1<<i);
			}
			else y|=(1<<i);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Guchenxi0971 (赞：1)

### 题目大意

将一个数组划分成多个区间，它们独自异或的值或起来小于等于一个数，求最大划分段数

### 分析

首先可以发现，将这个数组的每个值或起来它们的值一定是大于等于合并一些或并将其变为异或的值，那么我们可以枚举将那些位置的值改为 0。假设二进制下第 $i$ 为一的值排完序是 $a[i][1]$ 到 $a[i][m]$。那么如果 $m$ 是奇数，肯定无法将其变为 0，那么只有将一些相邻的第 $i$ 位为 1 的块合并，（看不懂建议看代码），可以理解为颜色段覆盖和全局颜色段统计。（本人不会 ODT，只好用线段树写）我将一个颜色段的权值变为 0，再将其右端点的值改为 1，这样区局和就是全局的颜色段数。同时线段树还可以维护这个点是属于哪个颜色段的（有线段树维护并查集）。那么要怎么使用呢？

（设全部或起来的值为 $sum$，给定的限制为 $x$）

我们从二进制高位向低位遍历，每位可以分两种情况讨论：

1.  $sum$ 二进制的此位为 1，但是 $x$ 二进制这位不是 1，那么一定要将这位改成 0，只需要将相邻俩个 $a[i]$ 数组的及其中间的颜色段合并。如果 $sum < x$ 那么答案是当前全局的颜色段数。
2.  $sum$ 和 $x$ 的二进制的这位都是 1，因为这位之前的每位都相同，那么只要这位变小就会满足条件，但是没必要真正修改颜色段。

具体细节还是看代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Max=1e5+10;
int a[Max];

vector<int> vis[31];
int fa[Max];

int FindFa(int x){
	return x==fa[x]?x:fa[x]=FindFa(fa[x]);
}


struct SegmentTree{
	int tag,sum,val;
}tr[Max<<2];

void pushup(int now){
	tr[now].val=tr[now<<1].val+tr[now<<1|1].val;
}

void build(int now,int l,int r){
	if(l==r){
		tr[now].sum=l;
		tr[now].val=1;
		tr[now].tag=0;
		return;
	}
	tr[now].tag=0;
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	pushup(now);
}

void Work(int now,int tag){
	tr[now].tag=tag;
	tr[now].sum=tag;
	tr[now].val=0;
}

void pushdown(int now){
	if(tr[now].tag){
		Work(now<<1,tr[now].tag);
		Work(now<<1|1,tr[now].tag);
		tr[now].tag=0;
	}
}

void Update(int now,int l,int r,int L,int R,int val){
	if(L<=l&&R>=r){
		Work(now,val);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(now);
	if(L<=mid)Update(now<<1,l,mid,L,R,val);
	if(R>mid)Update(now<<1|1,mid+1,r,L,R,val);
	pushup(now);
}

void Modify(int now,int l,int r,int to,int val){
	if(l==r){
		tr[now].val=1;
		return;
	}
	pushdown(now);
	int mid=(l+r)>>1;
	if(to<=mid)Modify(now<<1,l,mid,to,val);
	else Modify(now<<1|1,mid+1,r,to,val);
	pushup(now);
}

int Query(int now,int l,int r,int to){
	if(l==r)return tr[now].sum;
	pushdown(now);
	int mid=(l+r)>>1;
	if(to<=mid)return Query(now<<1,l,mid,to);
	else return Query(now<<1|1,mid+1,r,to);
}
int QueryVal(int now,int l,int r,int L,int R){
	if(L<=l&&R>=r){
		return tr[now].val;
	}
	pushdown(now);
	int mid=(l+r)>>1;
	int ans=0;
	if(L<=mid)ans+=QueryVal(now<<1,l,mid,L,R);
	if(R>mid)ans+=QueryVal(now<<1|1,mid+1,r,L,R);
	return ans;
}

struct Segment{
	int l,r;
}se[Max];
int n,x;
void merge(int x,int y){
	x=FindFa(x);
	y=FindFa(y);
	if(x==y)return;
	else{
		if(se[x].l>se[y].r){
			fa[x]=y;
			Update(1,1,n,se[y].l,se[x].r,y);
			se[y].r=se[x].r;
		}else{
			fa[x]=y;
			Update(1,1,n,se[x].l,se[y].r,y);
			se[y].l=se[x].l;
		}
		Modify(1,1,n,se[y].r,1);
	}
}

void work(){
	scanf("%lld%lld",&n,&x) ;
	for(int i=0;i<=30;++i){
		vis[i].clear();
	}
	int sum=0;
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		int x=a[i];
		int cnt=0;
		while(x){
			int z=x&1;
			x>>=1;
			if(z)vis[cnt].push_back(i);
			++cnt;
		}
		sum|=a[i];
	}
	int ans=-1;
	for(int i=1;i<=n;++i){
		fa[i]=i;
		se[i].l=se[i].r=i;
	}
	if(sum<=x){
		ans=n;
	}
	build(1,1,n);
	for(int i=30;i>=0;--i){                 
		if((sum&(1ll<<i))&&(!(x&(1ll<<i)))){
            //若当前位为1，但需要的是0，必须改（因为满足前面所有的都相同） 
			if(vis[i].size()%2==0){
                //如无法便为1那么结束 
				sum^=(1ll<<i);
				for(int j=0;j<(int)vis[i].size();j+=2){
					int Beg=Query(1,1,n,vis[i][j]);       
                    //合并当前为1的点形成的区间,消去当前位的1 
					int End=Query(1,1,n,vis[i][j+1]);
					merge(Beg,End);	
				}
				if(sum<=x)ans=max(ans,tr[1].val);
			}else break;
		}else{
			if(sum&(1ll<<i)&&(x&(1ll<<i))){ 
			//若两者都为1那么改为当前一定满足条件，但是不需要真的更改，只用查询即可 
				if(vis[i].size()%2==0){
					int Res=tr[1].val;
					for(int j=0;j<(int)vis[i].size();j+=2){
						int Beg=FindFa(Query(1,1,n,vis[i][j]));
						int End=FindFa(Query(1,1,n,vis[i][j+1]));
						Res-=QueryVal(1,1,n,se[Beg].r,se[End].l);
						if(se[End].l==se[End].r)Res++;
					}
					ans=max(ans,Res);
				}
			}
		}
	}
	cout << ans << "\n";
}

signed main(){
	int T;
	scanf("%lld",&T);
	while(T--)work();
	return 0;
}

/*
可以先将所有数或起来，然后枚举将哪一位变为0 
因为异或只会少，不会多 
*/
```

---

## 作者：Cells (赞：0)

## 写在前面

感谢 [ma_niu_bi](https://www.luogu.com.cn/user/528917) 提供帮助。

## 思路

首先看到位运算一般来说都要按位处理。

以下的操作全部在二进制下进行，设 $(a_{l_1}\oplus a_{l_1+1}\oplus ...\oplus a_{r_1})|(a_{l_2}\oplus a_{l_2+1}\oplus ...\oplus a_{r_2})|...|(a_{l_k}\oplus a_{l_k+1}\oplus ...\oplus a_{r_k}) = y$

我们先将 $x \leftarrow x + 1$，因为 $y \le x$ 不好搞，转化成 $y < x$ 方便我们做后续的操作。

由于 $y < x$，那么肯定在 $i$ 位上，$x$ 是 $1$，但是 $y$ 是 $0$，并且高于 $i$ 位都应该是相同的（$i$ 是多少我不知道）。当我们有了这个条件，低于 $i$ 位的 $y$ 的值就无关紧要了。那我们对高于 $i$ 位的 $x$ 值进行分类讨论。

- 当 $x$ 值为 $0$，这时候 $y$ 值必须为 $0$，根据或运算的性质，这一位上划分的每一个区间的异或值都应该是 $0$，再来根据异或运算的性质，这一位每个区间的 $1$ 的个数都应该是偶数！

- 当 $x$ 值为 $1$，这时候 $y$ 值可 $0$ 可 $1$，所以我们直接不处理，因为处理了的答案肯定不优于跳过的答案。

所以整体的流程就出来了，枚举每个分界点 $i$，枚举更高位，如果 $x$ 值为 $0$，我们对 $a$ 数组跑一次前缀和，统计这一位 $a$ 的 $1$ 的个数，如果这一位 $1$ 的总数是奇数，那么分界点 $i$ 就不存在合法的划分，我们把每个前缀和弄到一起，枚举每个位置，如果这个位置所有位的前缀都是偶数，我们直接划分。

最后取 $\max$。

下面是一些有趣的问题，你可以不看，免得把脑子搅浑了。

关于这个分界点 $i$ 的问题，你可以理解为这只是主观认为在这里区分开了大小，但实际上当我们碰见 $x$ 的值为 $1$ 时，真正区分开大小的位置可能不是 $i$ 位，而不管这一位只是因为答案要求最大，所以才不管的。

## Code

```c++
# include <bits/stdc++.h>
# define int LL
# define geti(x, i) (((x) >> (i)) & 1)
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
using namespace std;

using LL = long long;

const int N = 1e5 + 10;

int T, n, x, cnt, tot, ans;
int a[N], s[40][N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	while(T --){
		ans = -1;
		cin >> n >> x;
		x ++;
		rep(i, 1, n) cin >> a[i];
		
		pre(i, 30, 0){
			if(geti(x, i) == 0) continue;//大于的前提就是x是1，或为0 
			cnt = tot = 0;
			
			bool ok = true;
			
			rep(j, i, 30){
				if(geti(x, j) && j != i) continue;//当前分界点这一位必须为0 
				
				cnt ++;
				rep(k, 1, n) s[cnt][k] = s[cnt][k - 1] + geti(a[k], j);//统计1的个数前缀和 
				if(s[cnt][n] & 1){//如果总数是奇数 
					ok = false;
					break;
				}
			}
			
			if(!ok) continue;//不成立 
			
			rep(j, 1, n){
				bool flag = true;
				
				rep(k, 1, cnt){
					if(s[k][j] & 1){
						flag = false;
						break;
					}
				}
				
				if(flag) tot ++;//这个位置所有位全部是偶数 
			}
			
			ans = max(ans, tot);
			
		}
		
		cout << ans << "\n";
	}
	
	return 0;
}
```

本人的位运算部分很烂，写一篇题解来提高一下，大佬轻喷QWQ。

---

## 作者：anonymous_Y (赞：0)

但是我觉得位运算好难啊。

首先我们可以得到一个性质如果我们将每个数字都分为一段，也就是将所有数字或起来，一定要比我们将他们进行分段异或再或起来要来的值来的更大。

而对于位运算的处理方法其实就只有一种就是进行按位操作。

而题目说的是要保证小于 $x$ 那么我们考虑对 $x$ 进行判断。

记 $ temp _ i $ 为第 $ i $ 位的最大值。

假设我们现在判断到了第 $i$ 位，其中前 $i - 1$ 位的值都相同，那么有以下几种情况：

如果 $temp _ i$ 为 $1$ 的时候但是 $x$ 在这一位上0的时候，明显不成立，因为奇数个的1无论如何操作都无法变为 $0$ 。那么情况就是不成立的。

如果 $temp _ i$ 为0，而且 $x$ 在该位是 $1$ 的时候，我们发现只要这一位已经定了大小，所以后面无论是 $1$ 或者 $0$ 都已经不会再影响大小了。

剩下的两种情况显然无法进行操作。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int a[maxn],temp[35];
int n,x;
void init(){
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i]; 
}
void pre(){
	int t=0;
	for(int i=1;i<=n;i++) t^=a[i];
	for(int i=0;i<=30;i++){
		temp[i]=t&1;
		t>>=1;
	}
}
int work(int tmp){
	int cnt=0,now=0;
	for(int i=1;i<=n;i++){
		now^=a[i];
		if((now|tmp)==tmp) now=0,cnt++;
	}
	return cnt;
}
int solve(){
	int ans=-1,tmp=0;
	for(int i=30;i>=0;i--){
		if(temp[i]==1&&!(x&(1<<i))) break;
		else if(temp[i]==0&&(x&(1<<i))){
			tmp|=((1<<i)-1);
			ans=max(ans,work(tmp));
			tmp^=((1<<i)-1);
		}
		tmp|=(x&(1<<i));
	}
	return ans;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		init();pre();x++;
		cout<<solve()<<endl; 
	}
	return 0;
}
```

---

