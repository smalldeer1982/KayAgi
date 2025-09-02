# [NOI Online #1 提高组] 最小环

## 题目描述

给定一个长度为 $n$ 的正整数序列 $a_i$，下标从 $1$ 开始编号。我们将该序列视为一个首尾相邻的环，更具体地，对于下标为 $i$, $j(i \leqslant j)$ 的两个数 $a_i$, $a_j$，它们的距离为 $\min(j-i, i+n-j)$。

现在再给定 $m$ 个整数 $k_1$, $k_2$,..., $k_m$，对每个 $k_i(i=1$, $2$,..., $m)$，你需要将上面的序列 $a_i$ 重新排列，使得环上任意两个距离为 $k_i$ 的数字的乘积之和最大。

## 说明/提示

#### 输入输出样例 1 解释
- $k=0$ 时：答案为每个数平方的和。
- $k=1$ 时：一种最优方案：$\{3,1,2,4,6,5\}$。答案为 $3 \times 1 + 1 \times 2 + 2 \times 4 + 4 \times 6 + 6 \times 5 + 5 \times 3 = 82$。
- $k=2$ 时：一种最优方案：$\{3,6,1,4,2,5\}$。答案为 $3 \times 1 + 1 \times 2 + 2 \times 3 + 6 \times 4 + 4 \times 5 + 5 \times 6 = 85$。
- $k=3$ 时，一个合法的排列是 $1,5,3,2,6,4$ ，答案为 $88$。注意这里答案不是 $44$。

---

#### 数据范围与提示
对于所有测试数据：$1 \leqslant m \leqslant n \leqslant 2 \times 10^5$，$0 \leqslant k \leqslant \lfloor n/2\rfloor$，$1 \leqslant a_i \leqslant 10^5$。

| 测试点编号 | $n \leqslant$ | 特殊性质|
| :--- | :--- | :--- |
| 1 | $10$ | 无 |
| 2 | $18$ | 无 |
| 3 | $36$ | $n$ 为偶数且 $m=1$，$k=2$ |
| 4,5 | $1000$ | $m \leqslant 10$，$k=1$ |
| 6 | $50$ | $m \leqslant 10$，$k \leqslant 2$ |
| 7,8 | $3000$ | 无 |
| 9,10 | $2 \times 10^5$ | 无 |

## 样例 #1

### 输入

```
6 4
1 2 3 4 5 6
0
1
2
3```

### 输出

```
91
82
85
88```

# 题解

## 作者：Elegia (赞：57)

> Ran：@dengyaotriangle @LiM_817 @Elegia 你们仨分别写个T1-T3题解吧

被 迫 营 业 /cy

乘积最大化不够直观，我个人更喜欢改成 $2(\sum a_i^2 - Ans) = \sum (a_i - a_j)^2$，也就是说这道题是要最小化相邻位置的差平方和。

首先第一个值得注意的点是本质不同的图只有 $d(n)$ 种，这是因为考虑相邻关系 $i, (i+k)\bmod n, (i + 2k)\bmod n, \cdots$，这个东西走到一个环会需要 $n/\gcd(n, k)$ 次，也就是说得到了 $\gcd(n, k)$ 个相同大小的环。

首先我们讨论 $k=1$ 的答案。~~这个都[出烂](https://loj.ac/problem/520)了。~~

将 $a$ 排序后，假设 $n\ge 2$，考虑将 $i$ 和 $i+2$ 连边，然后将 $1\rightarrow 2, (n-1)\rightarrow n$ 连边，这样是一个环，也容易发现它是最优的。这个东西为何是个下界呢？我们考虑把乘积看成面积，那么第 $i$ 个点就在 $(a_i, a_i)$ 上，我们要最小化所有走路扫过的以端点形成的正方形面积之和。容易分析得到通过直线 $x=a_i$ 和 $y=a_j$ 切出来的每一个小矩形被经过的次数都达到了下界。

接下来考虑每个环长度为 $g$ 的情况，容易猜到我们将 $a_1 \sim a_g$ 放到第一个环里，$a_{g+1} \sim a_{2g}$ 放到第二个，以此类推。接下来简单证明一下：

1. 注意到对于这个构造，如果加入一个 $\min \sim \max$ 之间的数，答案只会变小。
2. 如果将 $\min$ 或者 $\max$ 删去，答案也会变小。
3. 如果两个环的取值是交叉关系，设它们的值域是 $[l_1, r_1], [l_2, r_2]$，满足 $l_1 < l_2 < r_1 < r_2$，那么交换 $l_1, r_2$ 所属的值，显然每个环都加入了一个新的值，并去掉了极值。因此答案变小。
3. 如果两个环的取值是包含关系，设值域是 $l_1 \le l_2 \le r_2 \le r_1$，那么这个方案甚至不如将这些数排在一个环里，因此这个方案必然不优。

根据以上四条，环必然是按顺序放置的。

我们对每个 $g|n$ 进行计算，复杂度为 $\Theta(nd(n))$，在 $n\le 2\times 10^5$ 时 $nd(n)$ 大概是 3e7，可以通过此题。

事实上还有更快的方法，我们考虑一个方案和 $k=1$ 的方案的差值，只有两个相邻的环之间的地方有修改，因此我们实际上可以在 $\Theta(n/g)$ 的时间内计算出 $g$ 对应的答案。这一方法的复杂度 $\le nH_n = \Theta(n\log n)$。

综上，本题可以在 $\Theta(nd(n))$ 或 $\Theta(n\log n)$ 的时间内通过。

---

## 作者：dingcx (赞：54)

个人感觉这道题是比赛中最简单的一道题，~~但是考试时没有打出正解qwq~~

## 20pts 做法

拿到前两个测试点的分还是比较容易的。

对于每个询问，```dfs``` 枚举每个数，再加上一些玄学剪枝，基本上就能得 $20$ 分。

~~其实这个 20 只是大概，我也没有试过~~

## 60pts 做法（重点）

拿到 $60$ 分才是关键。

通过样例解释其实可以想到**贪心**的思路：让**大数和大数乘**，**小数和小数乘**，也就是**让积不平均**。

那么怎么实现这样的贪心呢？我在考试中联想到了一道你谷月赛题 [P5887](https://www.luogu.com.cn/problem/P5887)。（我也在这道题上发过题解QAQ）

于是就想到：求 $n$ 和 $k$ 最大公约数，记为 $t$，那么 $t$ 就是**互不相关的环的个数**。（如果不好理解可以画几个图）

那么答案最大的情况就是**大的放在一个环中**，**小的放在一个环中**，从而实现积的不平均。

或者说，记 $n/t=p$，那么第 $1$ 到第 $p$ 大的放在一个环中，第 $p+1$ 到第 $2p$ 大的放在一个环中，以此类推。

最后注意一下 $k=0$ 的情况和边界，代码就能写出来了。（这里就不贴了）

这样做在洛谷能拿 $80$，但 $O(nm)$ 的复杂度应该是过不了测试点 $7$ 和 $8$ 的，可能是因为洛谷的数据比较小(~~shui~~)。

## 100pts 做法

我在考试时感觉这么做只有 $60$，没往下想，结果后来才发现满分就在 **60 分的做法上优化**就行qwq

考虑到一个数的因子很少，这道题 $n$ 又是固定的，也就是说 $t,p$ 的个数很少，所以只用**记忆化**就行了。只要 $p$ 相同结果就相同，如果以前算过 $p$，就直接输出答案。

还要注意这题 $ans$ 要开 ```long long```，并且 $a$ **数组也要开**，因为乘起来的时候如果本身不是 ```long long``` 就会算成 ```int```。（或者在算答案的时候强转也可以）

## AC 代码

下面放 AC 代码（有注释）——

（~~我知道你们只看这里QAQ~~）

```cpp
#include<cstdio>
#include<algorithm>//要用sort
#define ll long long
using namespace std;
const int MAXN=2e5+10;
ll a[MAXN],f[MAXN];//f是记忆化
int read(){//快读
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int gcd(int a,int b){//求最大公约数
	if(b==0) return a;//算完了
	return gcd(b,a%b);//辗转相除
}
int main(){//主函数
	int n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);//排序
	while(m--){
		ll ans=0;//记录结果
		int k=read();
		if(k==0||n==1){//特判k=0和n=1，n=1不特判会出bug，但好像没有n=1的测试点
			for(int i=1;i<=n;i++) ans+=a[i]*a[i];//算平方和
			printf("%lld\n",ans);
			continue;
		}
		int t=gcd(n,k),p=n/t;//计算t和p
		if(f[p]){//以前算过
			printf("%lld\n",f[p]);//直接输出
			continue;
		}
		for(int i=1;i<=n;i+=p){//枚举环
			for(int j=0;j<p-2;j++) ans+=a[i+j]*a[i+j+2];//枚举每个乘积，记录
			ans+=(a[i]*a[i+1]+a[i+p-1]*a[i+p-2]);//加上前后两个边界
		}
		printf("%lld\n",ans);
		f[p]=ans;//记忆化
	}
	return 0;//华丽结束
}
```
最后祝大家~~爆零快乐~~，别忘了点个赞！

---

## 作者：Macesuted (赞：16)

[题面](https://www.luogu.com.cn/problem/P6187)

对于题面我们很容易发现，我们可以将n个数分成若干个长度相同的环。
通过样例我们就可以发现，对于每个环，我会把最大的数都放在里面，我会在最大的边上放次大的和更次大的。

如果你无法理解，我们看样例解释

样例1中给出的是`1 2 3 4 5 6`这几个数

#### k=1
我们的方案是$\{3,1,2,4,6,5\}$，我们能看见，在最大的6左边放了5，右边放了4，然后再对于可连接的两个点5、4，5
更大，我们把3放在5的边上，2放在4的边上，最后放下1

#### k=2
我们的方案是$\{3,6,1,4,2,5\}$，我们能把他分成两个环$\{6,4,5\}$，和$\{3,1,2\}$，可以看见，我们在第一个环中放了最大的几个，然后对于环内采用k=1时介绍的方法，然后解决完第一个环后用相同的方法解决第二个环

然而考试的时候我就是这么写的，最后只拿到了80，有20分TLE了

## 优化

很容易发现，环的长度为$\dfrac{n}{\gcd(n,k)}$ ，所以在整个程序中实际上会处理到的环的长度的数量并不是很多。

考虑记忆化，因为如果两个问题中环的长度相同，显然答案也相同。我们只要记忆化一下即可。


```cpp
#include <bits/stdc++.h>
using namespace std;

map<int, long long> record;

int gcd(int a, int b)
{
	int temp;
	while (b)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}(

long long a[200005];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%lld", a + i);
	sort(a, a + n, greater<long long>()); //从大到小排序
	for (int i = 0; i < m; i++)
	{
		int k;
		scanf("%d", &k);
		long long answer = 0;
		if (k == 0) //特判，不然下面gcd会出错
		{
			for (int p = 0; p < n; p++)
				answer += a[p] * a[p];
			printf("%lld\n", answer);
			continue;
		}
		int ring = n / gcd(n, k); //环长
		if (record[ring])		  //记忆化
		{
			printf("%lld\n", record[ring]);
			continue;
		}
		for (int p = 0; p < n; p += ring)
		{																  //对于每一个环，p记录每个环最开始的点的下标
			for (int x = 0, tp = p + 1; x < (ring - 2) / 2; x++, tp += 2) //一半环
				answer += a[tp] * a[tp + 2];
			for (int x = 0, tp = p; x < (ring - 1) / 2; x++, tp += 2) //另一半环
				answer += a[tp] * a[tp + 2];
			answer += a[p] * a[p + 1] + a[p + ring - 1] * a[p + ring - 2]; //最后处理两个半环链接的问题
		}
		printf("%lld\n", answer);
		record[ring] = answer; //记录
	}
	return 0;
}
```

---

## 作者：LZDQ (赞：7)

这题主要找规律。我们把 $n=5,k=2$ 的情况画出来，发现构成了一颗五角星。看起来没什么规律，但这个五角星跟一个环是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/gh507n1q.png?x-oss-process=image/resize,m_lfit,h_300,w_1000)

将 $n=10,k=4$ 的情况画出来，发现是两个环。

![](https://cdn.luogu.com.cn/upload/image_hosting/d1m1vb64.png?x-oss-process=image/resize,m_lfit,h_300,w_1000)

于是我们得出了一个结论：答案要将n个数分成 $gcd(n,k)$ 个环。

$2e5$ 内 $n$ 的因数比较少，可以预处理出 $k|n$ 的答案，每次 $\Theta(n)$ 求分成 $k$ 个环的最大值。

这种模型已经考过n遍了，考场上一时间想不到就打个暴力，比如 $k=1,a=\{1,2,3...10\}$ 暴力得出的答案为 $1,2,4,6,8,10,9,7,5,3$

![](https://cdn.luogu.com.cn/upload/image_hosting/xgei0xou.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

简单来说就是大的数控制大的数，10控制9和8 , 9控制7 , 8控制6

我们要求分成 $k$ 个环，只需把前 $\frac nk$ 大的数放进第一个环，第 $\frac nk+1$ 到 $\frac nk*2$ 大的数放进第二个环，以此类推。

别忘了 $k=0$ 的情况。

总时间复杂度 $\Theta(n\sqrt n)$，其中根号表示n的最大因数个数，跑不满。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2e5+5;
typedef long long ll;
int n,m;
int p[MAXN];
int a[MAXN];
ll ans[MAXN];
int gcd(int a,int b){
	if(!b) return a;
	return gcd(b,a%b);
}
int main(){
//	freopen("ring.in","r",stdin);
//	freopen("ring.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
		scanf("%d",a+i),ans[0]+=1ll*a[i]*a[i];
	sort(a+1,a+n+1);
	for(int i=1; i<=n/2; i++){
		if(n%i) continue;
		int w=n/i;	//一个环内数的个数
		*p=0;	//当前处理到哪个数
		for(int j=2;j<w;j+=2)
			p[++*p]=j;	//2,4,6...w-1或w-2
		p[++*p]=w;
		for(int j=w-(w&1)-1;j>0;j-=2)
			p[++*p]=j;	//w-1,w-3..1
		for(int j=w+1;j<=n;j++)
			p[j]=p[j-w]+w;	//复制
		for(int j=1; j<=n; j++)
			if(j%w) ans[i]+=1ll*a[p[j]]*a[p[j+1]];	//求和
			else ans[i]+=1ll*a[p[j]]*a[p[j-w+1]];
	}
	while(m--){
		int k;scanf("%d",&k);
		if(k) k=gcd(n,k);
		printf("%lld\n",ans[k]);
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

```


最后吐槽一下CCF，这题大部分人都没看到公告（我也没看到），~~说不定是出题人没考虑然后把锅甩给我们~~

![](https://cdn.luogu.com.cn/upload/image_hosting/xsk8601b.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

---

## 作者：hekaiyu (赞：6)

# 题意

[去看吧](https://www.luogu.com.cn/problem/P6187)

题目描述挺简洁的 ，可以理解为有 $n$ 数 ，被拆分为几个环 ，要使得每个环的答案之和最大 。 
# 分析
其实是基本的思路是贪心 ，将尽量大的数是相连可以使结果最大 。

下面以四个数为例：我们令 $a<b<c<d$ 。如果 $d$ 与 $a$ 和 $b$ 连。则 $ans=a\times d + b\times d+a\times c+b\times c$ 。如果 $d$ 与 $c$ 和 $b$ 连。则 $ans=b\times d + c\times d+a\times b+a\times c$ 。

$c\times(d-b)>a\times(d-b)$

$\iff c\times d-c\times b>a\times d-a\times b$

$\iff b\times d + c\times d+a\times b+a\times c>a\times d + b\times d+a\times c+b\times c$ 

**证毕 。** 

所以我们只要尽可能大的数放在同一个环 ，再将每个环内的尽可能大数放在一起 。 怎么解决呢 ？ 排个序就好了啊！

接下来让我们想想有多少个环 。 一个环有 $x$ 个数 ，如果相邻距离为 $k$ , 那么$(x\times k) \bmod n==0$ 。因为不管绕了几圈一定会回到开始的点 。 那么  $x=n/\gcd(n\times k )$ 。 
直接处理所有 $k$ ，$O(1)$ 询问答案 。 

哦，对了还需要特殊处理一下为0的情况（详细见代码）

上代码：
```
#include <bits/stdc++.h>
using namespace std;
long long x[200005],ans[200004];
int cmp (int a,int b){
	return a>b;
}
int gcd(int a,int b){
	if(b>a)swap(a,b);
	if(a%b==0)return b;
	else return gcd(b,a%b);
}
int main(){
//	freopen("ring.in","r",stdin);
//	freopen("ring.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&x[i]);
	}
	sort(x+1,x+1+n,cmp);
	for(int k=1;k<=n/2;k++){
		int a=gcd(n,k),num=n/a;
		if(ans[a])continue;
		for(int i=0;i<=n;i++){//此步请读者思考
			if(i%num==0){
				ans[a]+=x[i+1]*x[i+2];
				continue;
			}
			if((i+1)%num==0){
			ans[a]+=x[i]*x[i+1];
			} 
			else ans[a]+=x[i]*x[i+2];//手推规律
		}
	}
//	if(n%2==0)ans[n/2]=ans[n/2]/2;   坑 
	for(int i=1;i<=n;i++){
		ans[0]=ans[0]+x[i]*x[i]; 
	}
	for(int i=1;i<=m;i++){
		int k=0;
		scanf("%d",&k);
		if(k==0)printf("%lld\n",ans[0]);
		else{
		k=gcd(n,k);
		printf("%lld\n",ans[k]);
		}
	}
	return 0;
}
```

时间复杂度不会超过 $O(n\sqrt{n})$

（已更正部分书写错误）




---

## 作者：良心WA题人 (赞：5)

# 简洁题意：
一个环上有数字，给定一个距离 k ，构造一个序列使 $\sum^{n}_{i=1}(a_i\times a_{i+k})$ 最大。这里指的是环上加减。
# 分析：
这个题很容易想到一个策略，把两个大的相乘很明显更划算。于是能想到由 1 开始 bfs，扩展出来左右两边的数，从大到小放数字。但这样很容易出现一个问题：有些永远不可能搜到！比如题目中的样例，$k=3$ 情况就有一半会搜不到。有一种解决方法：标记每一位，像 tarjan 一样，每一个点看看有没有标记，没有标记就搜。这种方法时间复杂度是 $\Theta(n)$ 的，可行，但是我没有试过。这是考试的时候想的，但是时间不够，就没写了。下面说一个代码简洁的方法：

针对上面的问题不难发现，这样分出来每一次搜索可以划分为一组。那么一组有多少个呢？就是 $n\div gcd(n,k)$ 个。这个我不会证明，纯粹是一个一个试出来规律的。要是有巨佬会证明的在评论区说一下，我会加上并特别鸣谢的。于是，分成了很多组就好办了。每一组互不干扰，再根据前面 bfs 的方法，发现一组中分到的数字是连续的。不难发现，在一组中除了最大和次大、最小和次小相乘，这一组里面都是 $a_{i+2}\times a_{i}$ 的。注意，为了方便放大的数，这里的 a 是已经从大到小排序的。于是，我们也可以每次 i 加上一组的个数，这样就相当于把 a 的一部分分给前一组了。时间复杂度也是$\Theta(n)$的。

针对上面两种方法，时间复杂度仍然不够用，因为会有很多个 k 要求。但是发现，k 最大小于 $n\div2$，也就是 $10^5$ 种 k 要求，但是却会有 $10^5\times2$ 个 k。如果每个分别求，会 TLE 几个点。但是，求的个数比种数多很多，肯定有很多重复。所以可以用一个 f 数组存每个 k 的答案，遇到重复的直接输出。但是这样时间仍然很紧，不难发现只要分的组是一样的答案就是一样的。我们又能少输出很多个 k 了，注意这样优化第一个方法就也要求一个一组的个数。

总时间复杂度 $\Theta(kn)$。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
long long a[NN],f[NN];
int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	while(m--)
	{
		int k;
		scanf("%d",&k);
		long long ans=0;
		if(k==0||n==1)
		{
			if(f[0])
			{
				printf("%lld\n",f[0]);
				continue;
			}
			for(int i=1;i<=n;i++)
				ans+=a[i]*a[i];
			f[0]=ans;
			printf("%lld\n",ans);
			continue;
		}
		int team=n/gcd(n,k);
		if(f[team])
		{
			printf("%lld\n",f[team]);
			continue;
		}
		for(int i=1;i<=n;i+=team)
		{
			for(int j=0;j<team-2;j++)
				ans+=a[i+j]*a[i+j+2];
			ans+=(a[i]*a[i+1]+a[i+team-1]*a[i+team-2]);
		}
		f[team]=ans;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：codecode (赞：4)

#### 题解：

这是考场上的思路。

观察样例，$n=6$ 且 $k=2$ 时，事实上答案是由两部分合起来的。

一个是奇数位置上的数，它们的相邻的两两乘积之和；另一个是偶数位置上的数，它们的相邻的两两乘积之和。

我们称这样的两部分为两个环。

对于不同的 $k$，将会把原数列分割为 $\gcd(k,n)$ 个不交环之并。

这时，我们只需要处理每个环上的情况，而每个环上是 $k=1$ 时的情况。

可以证明，对于每个环，如果可以填入环的数固定，那么填入环的数的顺序是唯一的（同构意义下唯一的），并且必定是类似于这样排列的：

$$1 \quad 2 \quad 4 \quad 6 \quad 8 \quad 7 \quad 5 \quad 3$$

即从最大的开始，两边依次交替延伸。

**证明如下**：不妨设需要将 $n$ 个不同的数 $a_1,a_2,...,a_n$ 填入环，我们需要最大化

$$a_1a_2+a_2a_3+...+a_na_1$$

我们证明取到最大值时，若 $a$ 数列满足 $a_1$ 最大且 $a_2>a_n$，则

$$a_1>a_2>a_n>a_3>a_{n-1}>a_4>...$$

我们归纳证明这个命题。

$n=1,2,3$ 时命题平凡。

若 $n$ 时命题成立，则 $n+1$ 时：

考虑插入一个比**所有数**更大的数 $a_0$，插入在哪里会使得相邻两两乘积之和最大？

不难发现是在 $a_1$ 与 $a_2$ 之间。

归纳完毕。

**证毕**。

对于不同的环上的数，类似地可以证明：每个环上的所有数构成的集合，在**对原数组排序后的新数组**内是连续的一段。

于是我们可以先对输入数组排序，并针对每个**不同个数的环**预处理出答案。

对于每个输入，找出其所对应的环的个数，$\Theta(1)$ 回答。

注意对于 $k=0$ 时特判。

总时间复杂度 $\Theta(n\sqrt n +m)$。

考场上的代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+233;
int n,m,x;
int a[maxn];
long long k[maxn];
int gcd(int x,int y){
	return y==0?x:(y,x%y);
} 
int main(){
	//freopen("ring.in","r",stdin);
	//freopen("ring.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		k[0]+=a[i]*a[i];
	for(int i=1;i<=n;i++){
		if(n%i)continue;
		for(int j=0;j<n/i;j++){
			int w=j*i;
			for(int l=1;l<=i-2;l+=2)
				k[i]+=a[w+l]*a[w+l+2];
			for(int l=2;l<=i-2;l+=2)
				k[i]+=a[w+l]*a[w+l+2];
			k[i]+=a[w+1]*a[w+2];
			k[i]+=a[w+i-1]*a[w+i];
		}
	}
	for(int i=1;i<=m;i++){
		cin>>x;
		if(x==0){cout<<k[0]<<endl;continue;}
		int gc=gcd(x,n);
		cout<<k[n/gc]<<endl;
	}
	return 0;
}
```

可惜的是这个满分算法因为我 $a$ 数组没开long long爆零了。~~F*ck~~

~~可是现在还不知道为什么 $a$ 数组要开long long。~~

在此提醒大家，不开long long见祖宗QAQ！

---

## 作者：BFqwq (赞：3)

## T3
直接贪心。

显然，一个环会被分成 $\gcd(n,k)$ 个小块。

举个例子，$n=10,k=4$，我们通过尝试发现 $1,3,5,7,9$ 五个数在加上若干次距离为 $4$ 的步后可以互相到达，但到达不了 $2,4,6,8,10$；

同理 $2,4,6,8,10$ 可以互相到达但到不了 $1,3,5,7,9$。

这就相当于被分成了两个块，

每个小块内是 $n\div\gcd(n,k)$ 个数。

我们想要明确的一点是，这个题块内的乘法是成环状的，也就是不论如何放置数的位置，每一个数都必须与两个数相乘，且把乘法的顺序画出来一定是一个环。

就比如 $n=10,k=4$ 的情况下，第 $1$ 个数乘第 $5$ 个数，第 $5$ 个乘第九个，第 $9$ 个乘第 $3$ 个，第 $3$ 个乘第 $7$ 个，第 $7$ 个乘第 $1$ 个。

不妨令 $p=\gcd(n,k),q=n\div p$，

现在我们假定 $a_1,a_2\ldots a_q$ 在一个环内且大小递增，

那么显然，要让这个块的乘积最大，就要让大的数相乘。

也就是 $a_q$ 和 $a_{q-1},a_{q-2}$ 相乘。那么 $a_{q-3}$ 呢？显然与 $a_{q-1}$ 乘最优。

这边补充一下证明吧，用归纳的方法来证明。

首先考虑三个数的时候，显然成立（因为只能是 $a_q$ 和 $a_{q-1},a_{q-2}$ 乘）。

接着，如果对 $k$ 个数成立，下证对 $k+1$ 个也成立。

同样的，不妨设 $a_1\le a_2\le\cdots\le a_{k+1}$。

我们可以将问题转化为先将 $a_1\cdots a_k$ 排成环，然后将 $a_{k+1}$ 插入进去。

由于对 $k$ 个数成立，所以 $a_k$ 和 $a_{k-1}$ 一定会相乘。

现在我们将 $a_{k+1}$ 插在这两个数中间，乘积增加了 $a_{k+1}\times (a_{k-1}+a_{k})-a_k\times a_{k-1}$。

否则我们任意将它插在 $a_b$ 和 $a_c$ 之间，乘积增加 $a_{k+1}\times (a_{b}+a_{c})-a_b\times a_c$。

两者相减，得到： 

$$a_{k+1}\times a_k+a_{k+1}\times a_{k-1}-a_{k}\times a_{k-1}\ge a_{k+1}\times a_b+a_{k+1}\times a_c-a_b\times a_c$$

下证成立：

$$a_{k+1}\times (a_k+a_{k-1}-a_b-a_c)\ge a_{k}\times a_{k-1}-a_b\times a_c$$

$$LHS\ge a_k^2+a_k\times a_{k-1}-a_k\times a_b-a_k\times a_c$$

重新移项得：

$$a_k^2+a_b\times a_c\ge a_{k}\times a_b+a_k\times a_c$$

由排序不等式，证毕。

以此类推，可以直接确定块中环的形态。然后我们就可以直接分割序列求值了。

另外，由于询问的地方会有很多重复，因此我们可以记录一下每个 $p$ 对应的的答案，以加快速度。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(long long x,char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=300005;
long long ans1,ans,ans2,ans3;
int a[maxn];
int qwq[maxn];
int n,m;
int gcd(int a, int b){
	return b?gcd(b,a%b):a;
}
signed main(){
//	freopen("ring.in","r",stdin);
//	freopen("ring.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		ans1+=(long long)(a[i]*a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++){
		int k=read();
		if(k==0){
			print(ans1);
			continue;
		}
		int p=gcd(k,n);
		int q=n/p;
		if(qwq[p]){
			print(qwq[p]);
			continue;
		}
		ans=0;
		for(int i=0;i<p;i++){
        	int l=q*i+1,r=q*i+q;
        	if(q==1) ans+=a[i]*a[i];
        	else if(q==2) ans+=a[r]*a[l]*2;
        	else{
            	ans+=a[r]*a[r-1];
            	ans+=a[r]*a[r-2];
            	for(int j=r-3;j>=l;j--) ans+=a[j]*a[j+2];
            	ans+=a[l]*a[l+1];
        	}
    	}
    	print(qwq[p]=ans);
	}
	return 0;
}
```
原期望得分 $80$ 或 $100$。由于没看到公告而加了个特判抱灵。

---

## 作者：zhimao (赞：2)

个人认为这是三题里最简单的一题（但想不出如何贪就尴尬了）。
### 分析

首先，当k=0，ans=每个数的平方的和。
否则，我们发现：要使总乘积大，则大的跟大的乘，小的自然就跟小的乘。所以样例中k=1时，ans=1\*2+1\*3+2\*4+3\*5+4\*6+5\*6。

似乎完了？想多了。

注意当k=2或3时，样例解释却不这样。这是为什么呢？因为有环。当k=2，有（1-2-3）（4-5-6）二环；k=3，有（1-2）（3-4）（5-6）三环。

那么我们如何判环呢？显然，当gcd（n，k）=x时，有x个环（因为此时n | k·x）。

判完了环，就要算了。如果暴力算，时间复杂度为O（nm），不行。我们注意到分成环了以后，按数的大小排序后是有序的。如k=2时，ans=（1\*2+1\*3+2\*3）+（4\*5+4\*6+5\*6），与k=1时，ans=1\*2+1\*3+2\*4+3\*5+4\*6+5\*6很像。

于是我们生出一个想法：利用前缀和思想，c\[i\]=a\[1\]\*a\[2\]+a\[1\]\*a\[3\]+…+a\[i-2\]\*a\[i\]+a\[i-1\]\*a\[i+1\]（c\[1\]=a\[1\]\*a\[2\]；c\[n\]=c\[n-1\]+a\[n-1\]\*a\[n\]）

此时，从a\[l\]到a\[r\]乘积和为c\[r\]-c\[l-1\]。但这样a\[l\]\*a\[l+1\]变成了a\[l-1\]\*a\l+1\]；a\[r-1\]\*a\[r\]变成了a\[l-1\]\*a\[r+1\]，所以需要校正（当l=1或r=n是不用校正）。

## 注意
ans最大为100000\*100000\*200000爆longint，要用int64。

### 代码

激动人心的代码时刻到了。
```pascal
var a,b:array[0..200005] of longint;
  c:array[0..200005] of int64;
  n,i,j,m,x:longint;
  ans:int64;
function gcd(p,q:longint):longint;
begin
  if q=0 then exit(p);
  exit(gcd(q,p mod q));
end;
function find(l,r,x:longint):int64;
var k,bo:longint;
begin
  find:=0;
  bo:=gcd(r-l+1,x);
  if bo<>1 then\\分成环
    begin
      for k:= 1 to bo do
        find:=find+find(l+(r-l+1) div bo*(k-1),l+(r-l+1) div bo*k-1,x div bo);
    end
  else
    begin
      find:=c[r]-c[l-1];
      if r<>n then find:=find-a[r-1]*(a[r+1]-a[r]);
      if l<>1 then find:=find+a[l+1]*(a[l]-a[l-1]);
    end;
end;
procedure kb(l,r:longint);
var i,j,mid:longint;
begin
  i:=l;j:=r;mid:=a[(l+r) div 2];
  repeat
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
      begin
        a[0]:=a[i];a[i]:=a[j];a[j]:=a[0];inc(i);dec(j);
      end;
  until i>j;
  if i<r then kb(i,r);
  if l<j then kb(l,j);
end;
begin
  readln(n,m);
  for i:= 1 to n do
    begin
      read(a[i]);
      ans:=ans+a[i]*a[i];//k为0时
    end;
  kb(1,n);//别忘了排序
  c[1]:=a[1]*a[2];
  for i:= 3 to n do
    c[i-1]:=c[i-2]+a[i-2]*a[i];
  c[n]:=c[n-1]+a[n-1]*a[n];
  for i:= 1 to m do
    begin
      read(x);
      if x=0 then writeln(ans)
             else writeln(find(1,n,x));
    end;
end.

```

---

## 作者：chinaxjh (赞：2)

# 前言
本文主要是对易错点的分析，主要针对有思路却错了的同学，如果要看具体的思路和分析，建议去看其它几篇题解，我写出来肯定也不如他们好

总结：总体难度不大的一道贪心题
# 易错点分析
$$\text{Point 1}$$
### 不开$\text{long long}$
~~为什么总有人不开$\text{long long}$~~

首先，对于一般性的题目，建议能开$\text{long long}$都开$\text{long long}$，实际运行速度比$\text{int}$慢不了多少

对于本题而言，考虑最极端数据，假设$a_i$都为$10^5$,再观察样例，发现每个数都分别平方再相加的和会最大，于是我们可以得到
$$ans_{max}=a_{i_{max}}^2*n=2*10^{15}$$

~~不算都知道要开$\text{long long}$吧~~
$$\text{Point 2}$$
### 没有特判零
零是一个很~~猥琐~~的数字，常常在数论题里，零是需要我们特判的，在有些写法里，零是不需要特判的，但是出于安全考虑，还是建议特判

在本题中，出现了$\text{k=0}$的情况，如果是预处理所有答案的，有可能要特判，如果是像我一样的记忆化的话，可判可不判
### 没看到补充样例
~~应该只有我一个蒟蒻没看到吧~~

补充样例中说明
>附加说明：样例当 $k=3$ 时，一个合法的排列是 ${1,5,3,2,6,4}$，答案为 $88$。注意这里答案不是 $44$。

~~$CCF$怎么出题的，这种东西到最后一个小时才更新，而且连通知都不发一个...~~

比赛完之后看到有点搞不清楚状况，重新看了一眼题目，感觉还是有点乱，有个大佬告诉我说好像是因为一个环里只有两个数，前后都是同一个数，所以要重复计算，~~我也不知道$CCF$什么意思，反正到时候一半乘2就对了~~
# 代码
好像还没有看到我这种记忆化的，别的代码都是预处理的，两者时间复杂度的差距不大，都可以通过此题
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fori(i,a,n) for(i=a;i<=n;i++)
#define ford(i,n,a) for(i=n;i>=a;i--)
typedef long long ll;
typedef double db;
typedef long double ld;
typedef unsigned long long ull;
const int N=2e5+5;
ll a[N],n,m,i,k,ans,j,l,r,w,ji[N],ww;
ll gethuan(ll l,ll r)
{
	ll ans,j,las;
	if (r-l<=1) return a[r]*a[l];
	if (r-l<=2) return a[r]*(a[r-1]+a[r-2])+a[r-1]*a[r-2];//特判只有2个数或者3个数的环
	ans=a[r]*(a[r-1]+a[r-2]);
	las=r-3;
	ford(j,r-1,l+1)
	{
		ans+=a[j]*a[las];
		if (las>l) las--;
	}//贪心求答案
	return ans;
}
ll gcd(ll x,ll y)
{
	if (y==0) return x;
	return gcd(y,x%y);
}//取公约数算环的数量
int main()
{
	cin>>n>>m;
	fori(i,1,n)
	scanf("%lld",&a[i]);
	sort(a+1,a+1+n);//贪心要排序
	w=gethuan(1,n);
	fori(i,1,m)
	{
		scanf("%lld",&k);
		ans=0;
		if (gcd(n,k)>1)
		{
			ww=gcd(n,k);
			if (ji[ww]>0) printf("%lld\n",ji[ww]);//记忆化
			else {
				fori(j,1,ww)
		      	{
	     			l=(j-1)*(n/ww)+1; r=j*(n/ww);
		     		ans+=gethuan(l,r);
	     		}//计算每个环的最大值
	    		if (n/ww==2) ans*=2;//特判补充样例
                printf("%lld\n",ans);
	    		ji[ww]=ans;
			}
		} else {
			printf("%lld\n",w);//互质的情况就是一个环，开头已经算过了
		}
	}
}
```
# 后言
$Online$已经结束了，作为一场线上比赛，最大的作用还是给我们一种反思。希望大家在$Online$中犯的错误不要犯在复活的$NOIP$中。

~~今天为什么三道序列题啊啊啊！！！$CCF$出同类题出上瘾了？？？~~


$\mid\color{red}\text{诚实面对自己的悲伤，与事与愿违的世界释怀}$

---

## 作者：xukuan (赞：2)

这题是全场最好做的一题，构造方法很好想，是个人都猜的出，这里给出证明过程。

不妨设只有1个环

当同一组内的数字不超过4个的时候，直接大的配大的即可，这里看5个数字及以上的方法。

假设有$i,i+1,i+2,i+3,i+4$ 5个数字让你填。

显然大的要和大的在一起。

那么有两种填法：

1. $i+1,i+3,i+4,i+2,i$

2. $i,i+3,i+4,i+2,i+1$

不算i+4的贡献，那么第一种是$(i+1)(i+3)+(i+2)i$，第二种是$i(i+3)+(i+2)(i+1)$

第一种大。

所以构造方法就是$1,3,5,7,...,n,...,8,6,4,2$

那么环不止一个呢？

环的个数是$\frac{n}{gcd(n,k)}$,环的个数相同的解的个数相同。对于每一种我们暴力算，时间复杂度是$O(nd(n))$

话说有没有和我一样的傻逼写记忆化的时候记了$k$。注意这里要记$gcd(n,k)$或者$\frac{n}{gcd(n,k)}$

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=200010;
ll a[N],ans1,ans2,ans[N],n,m;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

ll gcd(ll x,ll y){
	return x%y==0?y:gcd(y,x%y);
}

int main(){
	freopen("ring.in","r",stdin);
	freopen("ring.out","w",stdout);
	n=read(); m=read();
	for(ll i=1; i<=n; i++) a[i]=read();
	for(ll i=1; i<=n; i++) ans1+=a[i]*a[i];
	sort(a+1,a+1+n);
	for(ll i=1; i<=n; i++) ans2+=a[i]*a[i+2]; ans2+=a[1]*a[2]+a[n-1]*a[n];
	while(m--){
		ll x=read();
		if(x==0){
			write(ans1); putchar('\n');
			continue;
		}
		ll _Gcd=gcd(n,x);
		if(_Gcd==1){
			write(ans2); putchar('\n');
			continue;
		}
		ll k=n/_Gcd;
		if(ans[k]){
			write(ans[k]); putchar('\n');
			continue;
		} 
		for(ll i=1; i<=n; i+=k){
			for(ll j=i; j<=i+k-1; j++){
				if(j+2<=i+k-1) ans[k]+=a[j]*a[j+2];
			}
			ans[k]+=a[i]*a[i+1]+a[i+k-2]*a[i+k-1];
		}
		write(ans[k]); putchar('\n');
	} 
	fclose(stdin); fclose(stdout);
	return 0;
} 
```

---

## 作者：xh39 (赞：1)

# 算法
算法:排序+贪心+最大公约数。

请解决以上 $3$ 个算法再来看此篇题解。
# 贪心

尽量把大的数安排在一起乘。比如样例$k=1$时,就要把$4,5$安排在$6$的旁边。然后再把$3$安排在$5$的旁边$,2$安排在$4$的旁边,$1$安排在$3$的旁边。

为什么可以这样做呢?拿样例解释,如果把$4$放在其他数旁边,那么只能用$1,2,3$来代替4的位置,这时候6就至少少了$6$分,而5放在其他数旁边最多只能多加$4$分(放在$4$旁边),明显不优,其他的数据亦可用这样的方法证明。

# 先来考虑$gcd(n,k)=1$

对于$gcd(n,k)=1$,那么从1开始,每次跳k步,总能n次之内总能跳完所有的数,也就是说所有需要相乘的数恰好构成一个环。

~~证明需要一定的数论知识,然而我太弱了这是猜的,所以有兴趣的可以自己去证明一下。~~

在这种情况下,直接按上述贪心做法就可以了。

预计$#4,#5,20$分。实际没测过。

# $gcd(n,k)=2$

此时可以自己写几种情况然后会发现恰好构成了$2$个环。

因为$gcd=2$,不可能只构成$1$个环,不然就不满足裴蜀定理。

也不可能是$3$个及以上的环,因为我们可以对奇数下标和偶数下标分别讨论,发现对于每种情况都是数量和间隔都除以了$2$(因为$n,k$都是偶数才符合$gcd(n,k)=2$)。

它们都除了$2$,那么公因数也会除以$2$。此时$gcd(n÷2,k÷2)=1$。所以就用上一种情况的~~猜想~~就可以了。

预计得分$#3,4,5,6; 40$分。实际没测过。


# gcd(n,k)=b(b为整数)

观察上述$2$种情况,也可以发现恰好构成了$b$个环。

此时就不会$wa$了,就要讨论时间复杂度。

由于我们对于每次询问都要求$gcd$,填数,所以时间复杂度为$O(n\times log_{2}(k)+n)$求解,所以总复杂度为$O(n\times log_{2}(n)+n)$。

预计得分$#1~#8,80$分。实际$80$分。

# 优化

因为要询问很多次,所以每次都查询就很浪费时间,但是如果$gcd(n,k)$相同答案也就相同,于是我们可以采用记忆化。

此时的复杂度跟所有的质数以及质数的大小有关,不好写,但是大家肯定都知道这是$log$(不知道以几位底,应该是自然对数$e$,我也不确定)级别的。

预计得分:$100$ 实际:$100$。

# 小细节
$k==0$时$n,k$没有公因数,所以要特殊处理。

所以$k==0$要特殊处理。不然会40分。
# ac代码
```cpp
//代码有些丑,知道了思路也就不用看代码了。
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int GCD[2019][2019];
int gcd(int a,int b){
	if(!b){
		return a;
	}
	if(a<=2000&&b<=2000){
		if(GCD[a][b]){
			return GCD[a][b];
		}
		return GCD[a][b]=gcd(b,a%b);
	}else{
		return gcd(b,a%b);
	}
}
long long a[1000005],n;
long long f[1000005];
long long zxh(int k){
	int i,j,tot=0,ykb,gcdnk=gcd(n,k),noip; //noip表示一次循环noip次。
	long long sum=0; 
	if(f[gcdnk]){ //记忆化。
		return f[gcdnk];
	}
	noip=n/gcdnk;
	a[n+1]=0;
	for(i=0;i<gcdnk;++i){ //对gcd(n,k)个环依次进行处理,这里没有真正填数,直接计算,也就是代码少一点常数小一点而已。可以在纸上画一个gcd(n,k)=1的情况观察规律。
		for(j=0;j<noip-2;++j){
			sum+=a[i*noip+j]*a[i*noip+j+2]; //规律
		}
		sum+=a[i*noip]*a[i*noip+1]+a[i*noip+noip-1]*a[i*noip+noip-2]; //最大的数与其他数不一样,要特殊讨论。
	}
	f[gcdnk]=sum; //记忆化。
	return sum;
}
int main(){
	long long sum=0;
	int m,i,j,tot=0,k;
	cin>>n>>m;
	for(i=0;i<n;++i){ //处理k=0。
		scanf("%d",a+i);
		sum+=a[i]*a[i];
	}
	sort(a,a+n);
	for(i=0;i<m;++i){
		scanf("%d",&k);
		if(!k){ //处理k=0。
			printf("%lld\n",sum);
		}else
		printf("%lld\n",zxh(k));
	}
	return 0;
}
```

---

## 作者：_Diu_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6187)

这一题可以说是一道没那么找规律的找规律了。

## 我会猜结论

- 结论一：询问 $k$，实质上是把原数组分成 $\gcd(k,n)$ 个环，每个环长度为 $n/\gcd(k,n)$，每个环相邻两个数相乘的和的最大值。

很好证明，我们可以分类讨论一下：

- 当 $\gcd(k,n)=1$ 时：

假设我们从编号为 $1$ 的个数开始，那么第二个就是 $1+k$，第 $i$ 个就是 $(ik)\bmod n+1$，我们会发现这些数构成的集合 $A=\{0,k,2k,3k,\dots,(n-1)k\}$ 在 $\bmod n$ 的意义下时互不相同的，恰好循环一次。

而第 $n+1$ 个数 $nk\bmod n=0$，恰好和第一个相同， 

- 当 $\gcd(k,n)>1$ 时：

假设 $d=\gcd(k,n)$。

- 引理一：$(kx)\bmod(xy)=x\bmod y$。

所以可知 $A=\{0,k,2k,3k,\dots,(n-1)k\}$ 在 $\bmod n$ 的意义下等同于 $A'=\{0,k/d,2k/d.3k/d,\dots,(n-1)k/d\}$ 在 $\bmod \frac nd$ 的意义下。

那么，根据刚才的结论，集合 $A'_1=\{0,k/d,2k/d.3k/d,\dots,(\frac nd-1)k/d\}$ 互不相同，集合 $A'_2=\{\frac ndk,(\frac nd+1)k/d,\dots,(2\frac nd-1)k/d\}$ 也互不相同。

总共刚好分成 $\frac nd$ 组。

---

## 我会贪心

- 结论二：最优解时将 $a$ 排序后，每连续 $d$ 个组合成一个环。

我们考虑反证法来证明。

假设上述方案不是最优解，那么肯定存在两个环，一个环中一个点 $x$ 的贡献为 $x\times(x_1+x_2)$，另外一个环中一个点 $y$ 的贡献为 $y\times(y_1+y_2)$。

并且满足 $x>y\ \&\&\ x_1+x_2<y_1+y_1$。

那么交换 $x,y$，会发现贡献是 $yx_1+yx_2+xy_1+xy_2=xx_1+xx_2+xy_1+xy_2-(x-y)(x_1+x_2)$。

很原来的贡献 $=xx_1+xx_2+xy_1+xy_2-(x-y)(y_1+y_2)$。

很明显，交换之后会更优。

也可以这样想：我们尽可能让大的和大的乘在一起，因此让最大的排在一个换里面。

## 我还会贪心

我们继续考虑一个环里如何分配是最优的。

我们的贪心思路还是这样：**尽可能让大的和大的乘在一起**。

因此，就有了这一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ui0r6r65.png)

（里面的数字表示它在这几个数的从大到小的排名）

我们先把最大的放在中间，为了保证与它乘的数尽量大，于是就把二和三放旁边。

剩下的最大的是第二大的数，为了保证与它乘的数尽量大，于是把第四大放在它旁边。

以此类推，就得到了上图。

严谨证明应该和结论二的方法差不多，用反证法应该可以证出来。

因此我们又可以得到一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qaq2pqgo.png)

其实这样贡献就是隔一个乘一次，再把前两个的乘积和后两个的乘积加起来就行了。

好处：不需要额外处理环的长度**只有 $2$** 的情况。

注意：要特判 $k=0$ 的情况。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,t,k,ans[N],a[N];
signed main(){
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),ans[0]+=a[i]*a[i];
	sort(a+1,a+n+1);
	for(int d=1;d<=n;d++){
		if(n%d)continue;
		for(int l=1;l<=n;l+=d){
			int r=l+d-1;
			for(int j=r;j>=l+2;j--)ans[d]+=a[j]*a[j-2];
			ans[d]+=a[r]*a[r-1]+a[l]*a[l+1];
		}
	}
	for(;t--;){
		scanf("%lld",&k);
		printf("%lld\n",k?ans[n/__gcd(k,n)]:ans[0]);
	}
}
```

---

## 作者：cirnovsky (赞：0)

## NOI-Online-T3-最小环

全场最水的一道题，但是可怕的心理作用还是让我放弃了这道题。

首先有一个显然的结论，我们需要把这 $n$ 个数分为 $\gcd(n,k)$ 个环。

~~虽说是显然但是不画画图还真的玩不动~~

给一下图示意一下：

![Annotation 2020-03-11 094939.png](https://i.loli.net/2020/03/11/QtvJrcZ2FGb1doe.png)

图中那个看起来像个五角星的东西其实就是个环

![Annotation 2020-03-11 095158.png](https://i.loli.net/2020/03/11/NOaqFVdiP2jeM61.png)

这个图中有 $\gcd(n,k)$ 个环，这就是我们的结论。

具体到实现，我们采用的是预处理出所有答案。

贪心策略即大的和大配。

比如说，我们现在分成 $k$ 环。

我们可以把前面 $1->n\div k$ 大的数放进第一个环里面。

第 $n\div k+1->n\div k\times 2$ 放进第二个环里。

后面就类似了

还有 $k=0$ 的情况需要特殊处理一下

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 5e5 + 5;
vector < int > integer(MAXN);
vector < long long > ans(MAXN);

int gcd(int x, int y) {
	return !y ? x : gcd(y, x % y);
}

signed main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &integer.at(i)), ans.at(0) += (long long)integer.at(i) * (long long)integer.at(i);
	sort(integer.begin() + 1, integer.begin() + 1 + n);
	for (int i = 1; i <= (n >> 1); ++i) {
		if (!(n % i)) {
			int t = n / i;
			vector < int > process(MAXN);
			int tot = 0;
			for (int j = 2; j < t; j += 2) process.at(++tot) = j;
			process.at(++tot) = t;
			for (int j = t - 1 - (t & 1); j > 0; j -= 2) process.at(++tot) = j;
			for (int j = t + 1; j <= n; ++j) process.at(j) = process.at(j - t) + t;
			for (int j = 1; j <= n; ++j)
				if (!(j % t)) ans.at(i) += (long long)integer.at(process.at(j)) * (long long)integer.at(process.at(j + 1 - t));
				else ans.at(i) += (long long)integer.at(process.at(j)) * (long long)(integer.at(process.at(j + 1)));
		}
	}
	for (int i = 0, x; i < k; ++i) scanf("%d", &x), printf("%lld\n", ans.at(x ? gcd(n, x) : 0));
	return 0;
}
```

---

## 作者：JohnVictor (赞：0)

结论：每个环都是最大的两侧依次放置次大的，第三大的，第四大的...

感觉这里的证明写在数学试卷上都不太够严谨，我来补一个严谨的数学证明。


~~（先D一下这个题：最后说数据n=2k时我没看见导致肯定爆零了）~~

我们可以假设 $k=\gcd(n,k)$。这是因为，所有这样的点对构成若干个环，和环的具体位置无关。当然这个感性认知一下就好了。

然后我们开始重点考虑 $k=1$。假设这些数为 $a_1>a_2>\cdots>a_n$。

我们希望 $a_1,a_2$ 相邻，那么反证：

如果 $a_1,a_2$ 之间有$a_{i_1},a_{i_2},\cdots,a_{i_k}$,我们把 $a_{i_1},a_{i_2},\cdots,a_{i_k},a_2$这个序列翻转，使得 $a_1,a_2$ 相邻。这时候计算差值。设 $a_2$ 后面的数为 $b$，$a_1$ 后面的数为 $c$，那么增加了$(a_1-c)(a_2-b)$，大于0。

类似地，可以完成证明。

多个环的情况，只要依次把每个环的值都最大化即可。这里调整的证明比前面关键的部分容易一些。

代码比起题目的证明的难度=0.如果要特判那还有点难度，~~关键是我特判了结果不用啊~~。

---

