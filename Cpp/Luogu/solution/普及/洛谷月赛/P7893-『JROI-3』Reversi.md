# 『JROI-3』Reversi

## 题目背景

**赛时提醒：如果您始终是 30pts，且使用了题目给的快速读入，请重新拷贝修改后的快速读入。**

**赛时提醒：本题如果解法正确，快读可能无法起到优化作用。**

	这个恐怕是将存在乃至于记忆切割成三十二颗的争夺黑白棋。

    双方剩下的棋子数字都很小——也就是重要性很高吧。

				......
            
    ——哥哥为什么会让自己落单呢？她原本对此感到疑惑。

    不过，在得知答案之后，那可以说是理所当然的做法。

    首先，第一个理由极为单纯。

    故意将记忆托付给对方，暂时屈居败势的目的是——

    「……那种事……白……做不到啊……」

    想像了一下，白露出悲伤的笑容，做出这个结论。

    哥哥做的这些事，如果由白执行……白不觉得自己的精神能够保持正常。

    自己仅仅因为哥哥从身旁消失，就甚至一度怀疑哥哥的存在。

    ——被忘掉的话还好。

    ——忘掉哥哥的话——白确信自己的精神会无法保持正常。
    
				......
                
    （……这里……哥哥在……这里……）

    即使是空无一物的空间，但是白确信，她感觉得到哥哥的位置。

    白顿时眼眶一热，不过她强行忍住，继续思考。

    （……然后这就是……第二个……同时也是……最大的……理由。）

    白将写着【参】的棋子白色面朝上，用手指夹住。

    哥哥是『白色还是黑色』，这个问题也不需要犹豫。

    因为既然他将最后的棋局托付给『白』——那他当然是持白棋。

    这个现在看不见，甚至无法认知的棋局。

    既没有开始的记忆，也不知道盘面的经过如何。

    不过哥哥故意下输，并且为了让白能获胜所可能下的棋步……

    而对方看到之后，完全中了哥哥的计谋，被诱导而下的棋步……

    然后，为了逆转，哥哥可能选择的所有位置分布。

    将这些全部推测分析——仅用三步棋反败为胜。

				......
            
    然后——原先失去一天半的记忆——逆流了回来——


## 题目描述

**白**在和森精种玩黑白棋，但黑白棋的规则有所改变。

有 $n$ 个黑白棋子，第 $i$ 个棋子编号为 $i$。棋子初始全为黑，游戏中，仅由**白**一人操作，**白**希望尽可能多的把棋子变成白色。

**白**要求第 $k$ 个棋子和第 $k \times p$ 个不能同时变成白色。

**白**共玩了 $T$ 次，每次**白**想知道最多能把多少棋子变成白色。**每次游戏独立。**

为避免混淆，加粗的**白**是人名。

## 说明/提示

#### 样例 1 解释

可以选择第 $2,3$ 个棋子变色。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$T \le 5$，$n \le 2$；
- Subtask 2（5 pts）：$T \le 5$，$n \le 10$；
- Subtask 3（20 pts）：$T \le 5$，$n \le 10^6$；
- Subtask 4（70 pts）：无特殊限制。

对于 $100\%$ 的数据满足，$1 \le T \le 10^6$，$0 \le n \le 10^{18}$，$1 \le p \le 10^{9}$。

```
//快读模板
//赛时提醒：快读没有太大必要使用
inline long long read(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
```

## 样例 #1

### 输入

```
1
3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
1
100 5```

### 输出

```
84```

# 题解

## 作者：NightTide (赞：10)

## PART 0：说些闲话
这是去年十月份打的比赛，应该算我打的第一场月赛吧，最近突然想起来就来看看，发现还可以交题解就写一篇。

~~我才不会说是来贺快读模板的呢~~

## PART 1：题目大意
在 $[1,n]$ 中取若干个整数，使得 $k$ 和 $k \times p$ 不同时被选中，求最多能够选择多少个整数。

## PART 2：解题思路
首先阐述一下我们的策略，从大往小去选，一旦这个数 $k$ 可以被选择，也就是说 $k\times p$ 没有被选择，我们就选取它，这样一定是最优的。这是本蒟蒻比赛时的猜测。

当时水平太弱，误打误撞写出了正解，现在来想想为什么这样是对的？

原因很简单。我们依照这种方式，可以把 $[1,n]$ 上的整数分为若干段：$(\dfrac{n}{p},n],(\dfrac{n}{p^2},\dfrac{n}{p}],(\dfrac{n}{p^3},\dfrac{n}{p^2}],(\dfrac{n}{p^4},\dfrac{n}{p^3}]\dots$。总共是 $\left\lceil\log_pn\right\rceil$ 段，其中，第 $i$ 段所含有的元素个数是 $\dfrac{n(p - 1)}{p^i}$ 个。这样分段有什么好处呢？我们很容易发现，同一段中的任意数都可以被同时选中，于是我们来考虑一段一段的选。显而易见，选取越靠前的段，最终得到的元素个数就越多，所以显然是尽可能地选取较大的数，也就是我们这里较靠前的段是最优的。同时我们发现，相邻的两段是不能够被同时选取的，也就是说，最终的策略是选取第 $1,3,5,7,\dots$ 段。

但是这样实现起来似乎很复杂，有没有什么简单的方式呢？

当然是有的，这里先放出代码来：
```cpp
long long ans = 0;
for(long long i = 1; n > 0; i = -i, n /= p){
	ans += i * n;
}
printf("%lld\n",ans)
```

模拟一下即可理解：先加上 $n$，然后减去 $\dfrac{n}{q}$，再加上 $\dfrac{n}{q^2}$，……以此类推，这样的结果就和上面我们说的策略是一样的了。

## PART 3：完整代码
```cpp
#include<bits/stdc++.h>
#define MAXN 1000010
using namespace std;
long long t,n,p;
bool vis[MAXN];
inline long long read(){
   long long s = 0, w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9') { if(ch == '-') w = -1; ch = getchar(); }
   while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
   return s * w;
}
int main(){
	t = read();
	while(t--){
		n = read(); p = read();
		if(p == 1){
		    printf("0\n");
		    continue;
		}
		long long ans = 0;
		for(long long i = 1; n > 0; i = -i, n /= p){
			ans += i * n;
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：ycw123 (赞：4)

## Description
$T$ 组数据，每组数据给定 $n, p$，在由整数 $1 - n$ 中选取尽可能多的数组成集合 $S$，满足 $S$ 中任何一个元素都不是另一个元素的 $p$ 倍。求 $|S|$。

## Solution
考虑贪心。

如何才能选到尽可能多的数？

由于 $p$ 的倍数是每隔 $p$ 个才有一个，且若先前在较小的数中选取了某一个区间内的数，那么在相对应的区间内也仅仅是隔 $p$ 个才有一个不能选而已。

但是若在较小的区间内选择了一部分数，那么这部分数有可能同时还会影响到更小的某段区间中的数的选择。

因此先从大的数中选，可是选哪一段呢？答：直接选择 $\displaystyle(\frac{n}{p},n]$ 中的所有整数。为什么？

因为要在某个数本身和 $p$ 倍中做出选择，而我们知道选择一个较小的数是会同时影响到更小的数和更大的数的选择的，因此凡是需要作出选择的，我们都选较大的。

而又知道当 $\displaystyle(\frac{n}{p^2},\frac{n}{p}]$ 不被选择时，在小于等于 $\displaystyle\frac{n}{p^2}$ 的数中又有一部分能被选择。

这样从 $n$ 开始，每次除以 $p$，就出现了交替选于不选的情况，并且这样的解一定不是更劣的。循环求解。

时间复杂度 $O(\log_pn)$

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
long long n,p,cnt;
inline ll read(){
   register ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main(){
	cin>>t;
	while(t--){
		n=read(),p=read();
		if(p==1){
			printf("0\n");
			continue;
		}
		cnt=0;
		for(long long i=n,j=1;i>0;i/=p,j=-j){
			cnt+=j*i;
		}
		printf("%lld\n",cnt);
	}
	
	return 0;
}
```

---

## 作者：Keids (赞：3)

# P7893 『JROI-3』Reversi

原题链接：<https://www.luogu.com.cn/problem/P7893>

读题很容易发现，这是一道关于容斥的题。

因为将第 $k$ 个棋子染色后，第 $k\times p$ 个棋子就不能染色。

从小到大选数 $k$，这个数字只会影响第 $k\times  p$ 位的数字；若从中间开始选数，则它会影响其 $k \times  p$ 位和 $k \div p$ 位的数字，所以从小到大选的方案是最优的。

我们考虑从 $1$ 开始看，则相当于 $p$ 的倍数都不能选择。

当一个数为 $p^i$ 时，例如样例二中 $25$ 为 $5^2$，因为选了 $1$ 所以不能选 $5$，导致了 $25$ 是可以选择的棋子。

所以我们以此类推，得到容斥的结论：

不能取的数为 $p^i$ （$i$ 为奇数）；可以取的但是被减掉的数为  $p^i$ （$i$ 为偶数）。

所以我们按照容斥加减即可。

（无需使用快读！）

代码如下：

```c++
#include<iostream>
#include<cstdio>
using namespace std;
long long t,n,p,ans,k;
int main(){
	scanf("%lld",&t);//t次询问
	while(t--){
		scanf("%lld%lld",&n,&p);
		ans=n,k=p;//答案为全部的数减去不能取的，再加上可以取但是被误删的
		if(p==1){//注意特判，p=1时倍数为本身，全部都不能取
			puts("0");
			continue;
		}
		for(int i=1;k<=n;n=n/k,i++){
			if(i&1)ans-=n/k;//奇数减
			else ans+=n/k;//偶数加
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

###### 空白永不败北！



---

## 作者：ylch (赞：2)

# LUOGU[P7893](https://www.luogu.com.cn/problem/P7893) 『JROI-3』Reversi

题解思路参考[文章](https://blog.csdn.net/tigerisland45/article/details/104526788)，对于描述稍有改动。

本题和 [UVA11246](https://www.luogu.com.cn/problem/UVA11246) 重题了，一道题目，双倍经验！

## PART 1: 题意简述

这道题直接看没有什么头绪，不过我们可以把题面“变个样”：

一个 $\{ 1 \ldots n \}$ 的集合，计算其子集合，使得子集合的总元素最多，且不存在两个元素 $x_1 \times p = x_2$，求出子集合最多有多少个元素？

## PART 2: 考场错解

在我们的模拟赛上我是这样考虑的：

读题可知，从 $p$ 开始循环必定是有一个 $p$ 的倍数的，我们再每次都把循环变量加 $p$，然后再进行如下判断：

`(i/k)%k!=0 or a[i/p]==1`（$i$ 是循环变量，$a$ 是桶数组）

对于判断语句的解释：如果 $\dfrac{i}{p}$ 的结果除不尽 $p$ 或者 $\dfrac{i}{p}$ 已经被使用，统计变量加一（表示 $i$ 是不能被使用的）。 

最后用 $n$ 减去统计变量，就求出了除不能使用的数外有多少符合要求的数字。

代码

```cpp
#include <iostream>
#include <map>
#define int unsigned long long
using namespace std;

int T, n, p;

inline int read(){
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
	return s*w;
}

signed main()
{
	T = read();
	while (T--)
	{
		n = read(), p = read();
		map<int,int> b;
		
		int ans = 0;
		for (int i = p; i <= n; i += p)
		{
			if ((i/p) % p != 0 || b[i/p] == 1)	ans++;
			else	b[i] = 1;
		}
		printf("%lld\n", n-ans);
	}
	return 0;
}
```

结果：[Unaccepted 0](https://www.luogu.com.cn/record/119812054)

~~可以说相当惨烈~~

## PART 3: 正解思路

后来听了老师的讲解才发现，这道题可以推式子。

开始时每个子集合集合有 $n$ 个元素，先删除 $p$ 倍的，也就是删除 $\{ p,2p,3p,4p \ldots \}$，后发现这样会多删除 $p^2$，所以要加回来 $p^2$ 倍的数。

这时候在后面计算时又会多出 $p^2$，如此迭代下去，得到最后答案为 $n - \dfrac{n}{p} + \dfrac{n}{p^2} - \dfrac{n}{p^3} + \dfrac{n}{p^4} \cdots$。

！！！还有一个巨坑：当 $p=1$ 时答案一定是 $0$，这里要是不特判的话就会死循环，从而 TLE。

## PART 5: 参考代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void write(int x)
{
	if (x<0) putchar('-'), x = -x;
	if (x>9) write(x/10);
	putchar((x%10)^48);
}

signed main()
{
	int t, n, p;
	
	t = read();
	while (t--)
	{	
		n = read(), p = read();
		
		if (p == 1) //特判
		{
			write(0), putchar('\n');
			continue;
		}
		
		int ans = 0;
		for (int sign=1; n>0; sign=-sign, n/=p)
		{
			ans += sign*n;
		}
		write(ans), putchar('\n');
	}
	return 0;
}
```

## PART 5: 结尾

管理员大大辛苦啦~

谢谢大家！祝大家 AC！

---

## 作者：JiaY19 (赞：1)

比较简单的一道题。

#### 大致题意

第 k 个棋子和第 $k \times p$ 个不能同时变成白色。


#### 思路

对于每一次游戏，我们可以倒着进行染色。

这样就能分成一大段一大段来进行染色。

大致的操作就是，我们选一个变量 $ans$。

每一个奇数次。

都有：

```cpp
ans += n - n / p;
```
至于偶数次，就不需要有这样的操作。

当然，每次操作后，都需要更新 $n$。

```cpp
n /= p;
```
上面两行就是代码的核心部分了。

#### 关于正确性

可以用调整法来证明。

由于我们上面的核心代码选的是这个数字区间**可以同时选择所有最后面**的一段。

所以我们发现若是将其中一个数调整成前面的某数，那么他不仅会对第 $[\frac{k}{p}]$ 个数产生影响，同样会对第   $kp$ 个数产生影响，所以答案不会更优。

#### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t , n , p , ans , flag;

int read()
{
	int X = 0 , W = 1;
	char qwe = getchar();
	while(!isdigit(qwe))
	{
		if(qwe == '-') W=  -1;
		qwe =  getchar();
	}
	while(isdigit(qwe)) X = (X * 10 + (int)(qwe - '0')), qwe = getchar();
	return X * W;
}
	
signed main()
{
	t = read();
	while(t--)
	{
		n = read() , p = read() , ans = 0 , flag = 1;
		if(p == 1)
		{
			cout << 0 << endl;
			continue;
		}
		while(n)
		{
			if(flag) ans += n - n / p;
			n /= p;
			flag ^= 1;
		}
		printf("%lld\n" , ans);
	}
	return 0;
}

```

完结撒花！

---

## 作者：Light_Star_RPmax_AFO (赞：0)

## 前言

[传送](https://www.luogu.com.cn/problem/P7893)


# 思路——容斥

看得出选择了 $y$ 就一定不能选择 $y\times p$。

那么又可以得出以下结论选择了 $(\frac{n}{p^{x-1}},\frac{n}{p^x}]$ 那么就一定不能选择 $(\frac{n}{p^{x}},\frac{n}{p^{x+1}}]$。

有了以上结论我们就可以思考：

是取 $(\frac{n}{p^{x-1}},\frac{n}{p^x}]$ 多还是 $(\frac{n}{p^{x}},\frac{n}{p^{x+1}}]$ 多。

不难发现明显是 $\frac{n}{p^{x-1}}-\frac{n}{p^x}>\frac{n}{p^{x}}-\frac{n}{p^{x+1}}$ 所以我们选出前一段。

模拟：

```cpp
while(n){
	ans+=(x?n:-n);//选取前一段，减去后一段。
	n/=p;
	x=!x;//正负改变
}
```

# AC Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline long long read(){
   long long s = 0, w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9') { if(ch == '-') w = -1; ch = getchar(); }
   while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
   return s * w;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,p,ans=0;bool x=1;
		n=read(),p=read();
		if(p==1){
			cout<<0<<endl;
			continue;
		}
		while(n){
			ans+=(x?n:-n);
			n/=p;
			x=!x;
		}
		cout<<ans<<endl;
	}	
}
```

---

