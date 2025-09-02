# [ZSHOI-R1] 新概念报数

## 题目背景

Div.2 A 要什么背景？

## 题目描述

现在 Xttttr 和他的 npy 玩起了报数游戏，但是他们非常喜欢 $2$ 这个数字，于是制定了如下规则：

- 如果一个数 $a$ 满足 $\operatorname{popcount}(a) \geq 3$，那么这个数字是非法的，对方需要回答 ``No,Commander``。
- 否则，这个数是合法的，对方需要回答下一个合法的数。

坐在旁边的你当然不知道游戏的乐趣，你只想知道某次报数之后对方应该回答什么。

## 说明/提示

对于 $20\%$ 的数据，保证 $T\leq 100$，$a \leq 10^4$。

对于另外 $20\%$ 的数据，保证 $a$ 是合法的数字。

对于另外 $20\%$ 的数据，保证 $a$ 在值域内均匀随机。

对于 $100\%$ 的数据，$1\leq T \leq 10^5$，$0\leq a<2^{63}$。

## 样例 #1

### 输入

```
3
1
4
6```

### 输出

```
2
5
8```

## 样例 #2

### 输入

```
1
7```

### 输出

```
No,Commander```

# 题解

## 作者：maomao233 (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P9451)

直接分类讨论：

- 如果数 $a$ 满足 $\operatorname{popcount}(a)\ge3$，直接报告无解；

- 如果数 $a$ 满足 $\operatorname{popcount}(a)=1$，则直接输出 $a+1$ 即可，因为这样最多才使 $\operatorname{popcount}(a)=2$；

- 如果数 $a$ 满足 $\operatorname{popcount}(a)=2$，就稍微麻烦一些。我们先设数 $a$ 在二进制表示下为 $a'$，则可以找到 $a'$ 最右侧的 $1$，然后将其“加 $1$”即可。通俗地讲，就是找到最右侧的 $01$，将其变为 $10$。例如：$1010$ 的下一个合法数字为 $1100$。请注意，这个过程并不是真正的加 $1$。
   
   这里可以使用 [$\operatorname{lowbit}$](https://oiwiki.com/ds/fenwick/#%E7%AE%A1%E8%BE%96%E5%8C%BA%E9%97%B4) 函数来找到二进制数最右侧的 $1$。例如，$\operatorname{lowbit}(x)$ 就是 $x\operatorname{and}-x$。注意 $\operatorname{lowbit}$ 函数返回的值是一个 $k$ 位的二进制数 $\begin{matrix}1\ \underbrace{000\cdots000}\\\ \ \ k-1\text{个}\end{matrix}$，也就是十进制数 $2^k$，所以最后将其再加上 $n$ 即为答案。
   
得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pop __builtin_popcountll
int lowbit(int x)
{
	return x&-x;
}
signed main()
{
	int t;
    cin>>t;
    while(t--)
	{
		int n;
    	cin>>n;
    	if(pop(n)>=3)
    	{
    		puts("No,Commander");
		}
    	else if(pop(n)==1)
    	{
    		cout<<n+1<<endl;
		}
    	else
		{
    		cout<<n+lowbit(n)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：zhangzhihao2 (赞：2)

# P9451 [ZSHOI-R1] 新概念报数 题解

### 蒟蒻的第二篇题解&在主题库的第一篇题解qwq

## 题目大意

**对于任意正整数 $n$，若 $\operatorname{popcount}(n) < 3$，则称 $n$ 为“合法的”。**

给出 $T$ 个整数，对于每个正整数 $a$，若 $a$ 为不合法的，输出 ``No,Commander``；否则，求大于 $a$ 的最小的合法的正整数

## 1.题意理解（关于 $\operatorname{popcount}$，知道的各位可以跳过）

开始做题前，理解 $\operatorname{popcount}(x)$ 函数是必要的。它的意思即为：**将 $x$ 转化为二进制后，数码中 $1$ 的个数。**

而在代码实现中，我们大可不必求出完整的二进制编码，**只需不断将 $x$ 除以 $2$，记录下余数为 $1$ 的个数即可**。具体代码如下：

```cpp
int popcount(long long x){
    int res=0;
    while(x){
        if(x%2) res++;
        x/=2;
    }
    return res;
}
```

时间复杂度为 $O(\log_2{x})$。

## 2.暴力方法

显然，本题的难点在于当 $a$ 合法时，如何快速求出下一个合法的数。暴力做法是：从 $a$ 向后枚举，找到第一个合法的数并输出。主函数代码如下 ~~（蒟蒻在考场上交的第一份）~~：

```cpp
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(popcount(n)>=3) cout<<"No,Commander"<<endl;
		else{
		    do n++;
		    while(popcount(n)>=3);
			cout<<n<<endl;
		}
	}
	return 0;
}
```
 暴力 $60$ pts。
 
 ## 3.正解思路
 
当 $a$ 每次 $+1$ 时，分最后一位为 $0$ 和 $1$ 时进行讨论：

1. **当最后一位为 $0$ 时，显然是 $\operatorname{popcount}(a)$ 简单地 $+1$**，因为最后一位由 $0$ 变为 $1$，没有引起其他变化。

2. **当最后一位为 $1$ 时，可以证明 $\operatorname{popcount}(a)$ 不变或减少**，因为最后一位由 $1$ 变为 $0$ 并发生进位，导致最后一个为 $0$ 的位置变为 $1$，其后的所有原本为 $1$ 的位置均变为 $0$。

易知，**当 $a$ 的任意一位 $+1$ 时，类似的结论仍然适用。** 这样就可以分类讨论答案了。由于 $a$ 合法时，$\operatorname{popcount}(a)<3$，所以分两类讨论：

1. 当 $\operatorname{popcount}(a)=1$ 时，即使最后一位为 $0$，其 $+1$ 后顶多使 $\operatorname{popcount}(a)=2$，保证依旧合法，故**直接输出 $a+1$ 即可**；

2. 当 $\operatorname{popcount}(a)=2$ 时，我们必须保持 $\operatorname{popcount}(a)$ **不增**，因此只能在为 $1$ 的一位上 $+1$。同时要满足答案最小，就必须加在值为 $1$ 的最低位上。

值为 $1$ 的最低位？树状数组中学到的 $\operatorname{lowbit}$ 正好能符合要求。如 $48=(110000)_2$ 的 $\operatorname{lowbit}$ 就是 $(10000)_2=16$。$\operatorname{lowbit}$ 函数的写法很简单，直接用 `define` 语句即可：

```cpp
#define lowbit(x) (x&(-x))
//这种神奇的算法基于原码、反码和补码的芝士，有兴趣的可以自行了解
//由于位运算的优先级奇低无比，最好多加几个括号QAQ

```

因此，**当 $\operatorname{popcount}(a)=2$ 时，输出 $a+\operatorname{lowbit}(a)$。** 这道题就做完了。

## 4.~~丑陋的~~完整代码

我知道各位看官就爱看这个，但是还是要弱弱地说一嘴：

**一定要开 `long long` 啊！！！**

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
int t,n;

int popcount(int x){
    int res=0;
    while(x){
        if(x%2) res++;
        x/=2;
    }
    return res;
}

signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        if(popcount(n)>=3) cout<<"No,Commander"<<endl;
        else{
            if(popcount(n)==1) cout<<n+1<<endl;
            else cout<<n+lowbit(n)<<endl;
        }
    }
    return 0;
}
```


---

## 作者：NASFsky (赞：2)

## 前言
这是一道中规中矩的 Div.2 A，所以我也用了一种初学者都会的办法来解决。虽然用时可能比较长，但是可以快速想到并打完代码。   
## 分析
由题意可得，我们要找的是**转化为二进制后**数位上 $1$ 的个数 $\leqslant 2$ 的这么一类数，那么容易得到：  $n=2^p+2^q$，其中 $p,q$ 均为自然数。  
那么我们可以进行预处理：将 $2$ 的自然数次幂并放在一个数组，然后将数组中元素两两相加，再进行从小到大的排序即可。  
每次询问时可以二分搜索，当然直接扫一遍也行，因为合法数的数量很少。  
详见代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n,cnt;
ll a[70],b[10000];
int main()
{
	a[0]=1;
	b[++cnt]=1;
	for(int i=1;i<=60;i++)
	{
		a[i]=a[i-1]*2;
		b[++cnt]=a[i];
	}
	for(int i=0;i<=60;i++)
	{
		for(int j=i+1;j<=60;j++)
		{
			b[++cnt]=a[i]+a[j];//注意不要加重复了！
		}
	}
	sort(b+1,b+cnt+1);
   //上面都在进行预处理
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=cnt;i++)//直接扫
		{
			if(b[i]==n)
			{
				printf("%lld\n",b[i+1]);
				break;
			}
			else if(n>b[i]&&n<b[i+1])
			{
				printf("No,Commander\n");
				break;
			}
		}
	}
	return 0;
} 
```


---

## 作者：Hughpig (赞：2)

我们首先看如何写出 $\text{popcount}$ 函数。

$\text{popcount}(a)$ 的含义：在二进制下 $a$ 中 $1$ 的个数。

我们可以手写一个 $\text{popcount}$ 函数，即每次看 $a$ 的二进制的末尾是否为 $1$，如果是的话就把答案 $+1$。

也可以用编译器自带的 `__builtin_popcountll()` 函数，作用与 $\text{popcount}$ 函数相同。

手写 $\text{popcount}$ 函数示例：

```cpp
int popcount(long long x){
	int cnt=0;
	while(x){
		if(x&1)cnt++;
		x>>=1;
	}
	return cnt;
}
```

然后对 $\text{popcount}(a)$ 分类讨论：

1. $\text{popcount}(a)\ge 3$

此时是无解情况，直接输出 `No,Commander`	即可。

2. $\text{popcount}(a)= 1$

此时，$a$ 的二进制表示中只有一个 $1$，此时下一个合法解就是 $a+1$。

证明：

假如 $a>1$，因为 $a$ 的二进制表示中只有一个 $1$，即 $1$ 后跟着若干个 $0$，那么 $a+1$ 即把最后一位从 $0$ 变为 $1$，此时 $a+1$ 的二进制表示中有 $2$ 个 $1$，是合法解。

假如 $a=1$，此时 $a+1=2=10_{(2)}$，此时 $a+1$ 的二进制表示中有 $1$ 个 $1$，也是合法解。

因为 $a+1$ 是大于 $a$ 的最小正整数，所以没有更小的解。

3. $\text{popcount}(a)= 2$

此时的情形为 $1$ 后面有若干个（可能是 $0$ 个）$0$，然后又有一个 $1$，然后又有若干个（可能是 $0$ 个）$0$。

例如：$10000100_{(2)}$ 就是这样的情况。

此时观察可以发现：下一个合法解就是把原数加上原数二进制表示下最后一个 $1$ 以及后面的 $0$ 构成的数。

如何求一个数二进制表示下最后一个 $1$ 以及后面的 $0$ 构成的数？我们可以用 $\text{lowbit}$ 函数，实现为：

`int lowbit(long long x){return x&-x};`

具体可参考[此处](https://blog.csdn.net/qq853674765/article/details/70050306)，这里不在赘述。

注意点：

1. 多组数据

2. $a\le 2^{63}$，需要用 `long long` 类型

综上，可写出代码：

```
#include<bits/stdc++.h>//头文件
#define ll long long//定义 long long 为 ll，减少打字量
using namespace std;

ll t,n;//定义

ll lowbit(ll x){//lowbit 函数
	return x&-n;
}

ll popcount(ll x){//popcount 函数
	int cnt=0;
	while(x){
		if(x&1)cnt++;
		x>>=1;
	}
	return cnt;
}

int main()
{
    cin>>t;//输入
    while(t--){
    	cin>>n;//输入
    	int qwq=popcount(n);
    	if(qwq>=3)cout<<"No,Commander\n";//无解情况
    	else if(qwq==1)cout<<n+1<<'\n';//popcount(a)=1 情况
    	else{
    		cout<<n-lowbit(n)+2*lowbit(n)<<'\n';//popcount(a)=2 情况
		}
	}
	return 0;
}
```

---

## 作者：sxq9 (赞：1)

## 暴力思路
比赛时没有想出正解，只好暴力找数，$60$ 分。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int g(int n){
	int cnt=0;
	for(;n;){
		cnt++;
		n=n&(n-1);
	}
	return cnt;
}
signed main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int a;cin>>a;
		if(g(a)>=3){
			cout<<"No,Commander"<<endl;
		}
		else {
			int x=a+1;
			while(g(x)>=3)x++;
			cout<<x<<endl;
		}
	}
	return 0;
}
```
## 满分思路
我们可以分类讨论：

1. popcount 大于等于 $3$ 时，输出 No,Commander 即可。
1. popcount 等于 $1$ 时，直接加 $1$ 不管进不进位就是合法的。
1. popcount 等于 $2$ 时，找到数二进制中最后一个 $1$ 处加 $1$ 就让 popcount 保持不变或至少加 1，这就使得答案一定是合法的，如此一来就可以了。

AC code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int g(int n){
	int cnt=0;
	for(;n;){
		cnt++;
		n=n&(n-1);
	}
	return cnt;
}
signed main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int a;cin>>a;
		int x=g(a);
		if(x>=3){
			cout<<"No,Commander"<<endl;
		}
		else if(x==1){
			cout<<a+1<<endl;
		}
		else{
		    cout<<a+(a&(-a))<<endl;
		}
	}
	return 0;
}
```

---

## 作者：SJZ2010 (赞：1)

### 题意简述

给出一个数字，如果这个数字在二进制下有 $\ge 3$ 个 $1$，输出 $\texttt{No,Commander}$，否则输出下一个在二进制下 $1$ 的个数 $\le 2$ 的数。

### 思路1

先把要输出 $\texttt{No,Commander}$ 的判断掉，再暴力枚举下一个数字。

预计得分 $\color{#FFC116}{\text{60pts}}$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,a;//三年OI一场梦，不开 long long 见祖宗
long long count(long long x){//这个函数用来算一个数在二进制下有几个 1
    long long cnt=0;
    long long flag=1;
    while(flag){
        if(x&flag)
            cnt++;
        flag<<=1;//flag一直是 100...00 （可能没有0），如果 x 在flag的 1 的那位上是1的话 x&flag !=0
    }
    return cnt;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a;
        if(count(a)>=3){//不可能的直接输出跳过
            cout<<"No,Commander"<<endl;
            continue;
        }
        a++;
        while(count(a)>=3)//暴力枚举
            a++;
        cout<<a<<endl;
    }
    return 0;
}
```
与是我们 $\color{#052242}{\text{TLE}}$ 了后两个点……

### 思路2

然后我们再想想，那么大的数据，肯定有规律。

二进制下 $1$ 的数量 $\le 2$ 的数，有什么特点呢？

奇数肯定是 $1000\dots\text{(一堆0)}\dots001$ ，我们发现如果这个数是奇数，$+ 1$ 就行。

偶数呢？

偶数肯定是 $100\dots00100\dots00$ ，在第二个 $1$ 后面怎么变都不合法。所以要使数是合法的，我们要改变第二个 $1$ 的位置，为了最小，将那个 $1$ 向左移动 $1$ 位。

### 但是！

我们要考虑一下这个数 $=2^k,k \in N^{+}$ 的情况，这样的话直接输出 $2^{k}+1$ 就行了。（不然只有 $\red{20pts}$）（其实还是分类讨论，用 $1$ 的个数做标准来分类）

与是我们就写出以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,a;
long long count(long long x){
    long long cnt=0;
    long long flag=1;
    while(flag){
        if(x&flag)
            cnt++;
        flag<<=1;
    }
    return cnt;
}
long long oneend(long long x){//这个函数算一个数最左边的 1
    long long cnt=0;
    long long flag=1;
    while((x&flag)==0){
        cnt++;
        flag<<=1;
    }
    return cnt;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a;
        long long x=count(a);
        if(x>=3ll){
            cout<<"No,Commander"<<endl;
            continue;
        }
        long long weishu=floor(log2(a))+1ll;//计算这个数在二进制下有几位
        if(x==1ll)
            cout<<a+1ll<<endl;//特判
        else//x==2
            if(a%2==0)
                cout<<(1ll<<(weishu-1ll))+(1ll<<(oneend(a)+1ll))<<endl;
            else
                cout<<a+1<<endl;   
    }
    return 0;
}
```

即使 $\green{\text{AC}}$ 了这题，我们再想想，能不能再让代码简洁一点呢？

我们发现 奇数和非 $2^k$ 这种形式的偶数其实是差不多的，不过奇数是“第零位”是 $1$ 而已。

于是我们再改进一下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,a;
long long count(long long x){
    long long cnt=0;
    long long flag=1;
    while(flag){
        if(x&flag)
            cnt++;
        flag<<=1;
    }
    return cnt;
}
long long oneend(long long x){
    long long cnt=0;
    long long flag=1;
    while((x&flag)==0){
        cnt++;
        flag<<=1;
    }
    return cnt;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a;
        long long x=count(a);
        if(x>=3ll){
            cout<<"No,Commander"<<endl;
            continue;
        }
        long long weishu=floor(log2(a))+1ll;
        if(x==1ll)
            cout<<a+1ll<<endl;
        else
	    cout<<(1ll<<(weishu-1ll))+(1ll<<(oneend(a)+1ll))<<endl;
    }
    return 0;
}
```
如有不足，欢迎指出！

---

## 作者：_5t0_0r2_ (赞：1)

# 分析：

首先，我们可以简单地求出 $\text{popcount}(a)$ 的值，然后我们分类讨论：

当 $\text{popcount}(a) \geq 3$ 时，直接回答 ``No,Commader``．

当 $\text{popcount}(a) \leq 1$ 时，下一个合法的数即为 $a + 1$。

当 $\text{popcount}(a) = 2$ 时，我们就找到二进制下 $a$ 最末尾的 $1$，求出其对应的值 $x$，答案即为 $a + x$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a;
//手写popcount
int popcount(int x){
	int ret = 0;
	for(;x;x >>= 1)
		ret += (x & 1);
	return ret;
}
int nex(int x){
	long long tmp = x,cnt = 1;
	for(;x;x >>= 1){
		if(x & 1)
			return cnt + tmp;
		cnt <<= 1; //每遍历一位，位置值就乘2
	}
}
signed main(){
	scanf("%lld",&t);
	for(int i = 1;i <= t;i++){
		scanf("%lld", &a);
		int tmp = popcount(a);
        if(a == 0){
            printf("1\n");
            continue;
		}
		else if(tmp >= 3){
			printf("No,Commander\n");
			continue;
		}
		else{
			if(tmp == 1){
				printf("%lld\n",a + 1);
				continue;
			}
			else{
				printf("%lld\n",nex(a));
				continue;
			}
		}
	}
	return 0;
}
```


---

## 作者：Jorisy (赞：1)

首先判不合法，也就是 $\text{popcount}(a)\ge3$。

然后分 $\text{popcount}(a)=1$ 和 $\text{popcount}(a)=2$ 两种情况。

对于 $\text{popcount}(a)=1$，显然答案就是 $a+1$（在出现 $\text{popcount}(a)=3$ 前，必然会有 $\text{popcount}(a)=2$）。

对于 $\text{popcount}(a)=2$，如果 $(a)_{10}=(1100\cdots00)_2$，那么下一个合法的数应当是 $(10000\cdots00)_2$，也就是 $\text{lowbit(a)}\times4$；否则，也就是当 $(a)_{10}=(100\cdots00100\cdots00)_2$ 时，我们考虑使第一段 $0$ 个数减一，第二段 $0$ 个数加一即可。

抽象代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n;
		cin>>n;
		if(__builtin_popcountll(n)>=3) puts("No,Commander");
		else if(__builtin_popcountll(n)==1||n&1) cout<<n+1<<endl;
		else if(n&((n&-n)<<1)) cout<<((n&-n)<<2)<<endl;
		else cout<<(n^(n&-n)|((n&-n)<<1))<<endl;
	}
 	return 0;
}
```

---

## 作者：HappyCode (赞：1)

### 部分分解法

- $T\le 100,a\le 10^4$ 。判断后直接枚举即可。
- 保证 $a$ 合法。不判断直接枚举即可。
- 保证 $a$ 随机。不可以总司令即可。

### 正解

使用 `__builtin_popcountll(long long)` 函数，然后判断是否合法。

不难发现，popcount 的值为 $0$ 或 $1$ 时，下一个合法数即是 $a+1$。

而 popcount 的值为 $2$ 时，下一个合法值为在二进制下最后一个 $1$ 的位置 $+1$。即 $2^{\text{ctz}(a)}$，$\text{ctz}$ 为末尾 $0$ 的个数。

记得开 `long long`。

### 代码

```cpp
#include<iostream>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        long long a,pop;
		cin>>a;
		pop=__builtin_popcountll(a);
		if(pop>=3){
			cout<<"No,Commander"<<endl;
		}else{
			if(pop<=1){
				cout<<a+1<<endl;
			}else if(pop==2){
				long long ans=1,b=__builtin_ctzll(a);
				for(long long i=1;i<=b;i++){
					ans*=2ll;
				}
				ans+=a;
				cout<<ans<<endl;
			}
		}
    }
    return 0;
}
```

---

## 作者：E5pe7ance_ (赞：1)

本篇题解介绍如何使用 $\text{bitset}$ 写这道题。

### 【题意分析】

$\text{popcount(}a{)}$ 是一个十进制整数在二进制下 $1$ 的个数。

后面根据题意分类讨论即可。

- 当 $\text{popcount(}a{)} \geq 3$ 时，该数非法，输出不可以总司令。

- 当 $\text{popcount(}a{)} = 1$ 时，输出 $a+1$ 即可，此时 $\text{popcount(}a{)}$ 最多为 $2$。

- 当 $\text{popcount(}a{)} = 2$ 时，则需加上一个最小的正整数，使其 $1$ 的个数不变或减少，即进位。我们只要找出 $a$ 最低位的 $1$ 的位置 $i$，并加上 $2^i$ 即可。最后一步操作可以使用 $\text{lowbit}$ 函数实现。

### 【实现方案】

[bitset 介绍](https://oiwiki.org/lang/csl/bitset/)

它可以将二进制数的每一位分别修改。

```bitset``` 自带的 ```count()``` 函数可以统计其中 $1$ 的数量。

```_Find_first()``` 可以返回其中最低位 $1$ 的**下标**。

注意，要加的是 $2^i$，则可以再定义一个 ```bitset```，将它的第 $i$ 位设为 $1$。最后将两数转化为整数并相加。

```cpp
#include <iostream>
#include <bitset> //bitset容器所在头文件
using namespace std;
typedef unsigned long long ull; //数据范围一定要开long long
int T;
int main() {
	cin >> T;
	while (T--) {
		ull k;
		cin >> k;
		bitset<63> s(k); // 将整数k转化为bitset(
		if (s.count() >= 3) cout << "No,Commander\n"; //1,不可以总司令
		else {
			if (s.count() == 1) cout << k+1 << endl; //2.
			else { //3.
			    int y = s._Find_first(); //找最低位1的位置
			    bitset<63> s1; 
			    s1[y] = 1; //将第i为设定为1
			    k += s1.to_ullong(); //转化为整数
			    cout << k << endl;
			}
		}
	}
	return 0;
}
// Nightsky_stars qwq
```

---

## 作者：蒟酱 (赞：1)

满足 $\operatorname{popcount}(x)<3$ 的数实际上很少，直接把所有这些数扔到 `set` 里面，询问就返回 `set` 中 $x$ 的下一个元素即可。记得开 `long long`。`set` 内的元素数量是 $\log^2w$，所以复杂度是 $\mathcal O(\log^2w\log\log^2w+T\log\log^2 w)=\mathcal O(\log^2w\log\log w+T\log\log w)$，足矣通过本题。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
using std::cin;using std::cout;
using lolu=unsigned long long;
std::set<lolu>s;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	for(int i=0;i<=63;i++)for(int j=0;j<=63;j++)s.insert((1ull<<i)|(1ull<<j));
	int T;cin>>T;for(lolu x;T--;){
		cin>>x;
		if(__builtin_popcountll(x)>=3)cout<<"No,Commander\n";
		else cout<<*next(s.find(x))<<'\n';
	}
	return 0;
}
```

---

## 作者：FallingFYC_ (赞：0)

# [原题](https://www.luogu.com.cn/problem/P9451)
比赛时明明想到了正确思路但没时间写qwq。

---
### upd 2023.7.17 感谢 @[Hughpig](https://www.luogu.com.cn/user/646208) 和 @[chenzuanhua](https://www.luogu.com.cn/user/1001552) 对本篇题解的纠错！修改了笔误与错别字。

---
### 分析&思路

首先要明确 $\operatorname{popcount}(a)$ 的意思：此函数返回的值是 $a$ 的二进制中 $1$ 的数量。

而 C++ 中的编译器自带了 $\operatorname{popcount}$ 函数，写法为：`__builtin_popcount(n)`，如果 $n$ 是 `long long` 类型的，则可以写为 `__builtin_popcountll(n)`。

---
很明显这题要用分类讨论：

1. $\operatorname{popcount}(a) \ge 3$

    直接输出 `No,Commander` 即可。
    
2. $\operatorname{popcount}(a) = 1$
	
    输出 $a + 1$ 即可。
    
    原因：
    
    若直接 $+ 1$ 那么会出现 $2$ 种情况：
    
    1. 进位（$a$ 只可能是 $1$） 
    
    	$1 + 1 = 2$，$2$ 的二进制是 $10$，符合条件。
        
    2. 不进位 
    
    	$\operatorname{popcount}(a + 1)$ 就一定为 $2$（原本就有的 $1$ 和新加上的 $1$），符合条件。
    
3. $\operatorname{popcount}(a) = 2$

	直接 $+ \operatorname{lowbit}(a)$ 即可。
    
   $\operatorname{lowbit}(a)$ 函数的返回的是 $a$ 的二进制中只保留最低位的 $1$ 及其后边所有的 $0$，再转成 $10$ 进制的数。
   
   举两个例子：
   
   1. $\operatorname{lowbit}(5) = 1$ 因为 $5$ 的二进制为 $101$，最低位的 $1$ 后面没有 $0$，因此就是 $1_{(2)}$。
   
   2. $\operatorname{lowbit}(10) = 2$ 因为 $10$ 的二进制为 $1010$，最低位的 $1$ 后面有 $1$ 个 $0$，因此就是 $10_{(2)}$。
   
   $\operatorname{lowbit}(n)$ 就等于 $n$ 按位与 $-n$。
   
   接下来说一下原因：
    
  	可以发现，在此种情况下，要加上的数值一定是原数的二进制中为 $1$ 的那两位所代表的十进制数中的一个（否则会出现加上后二进制中 $1$ 的数量为 $3$ 的情况）。
    
   如果加上二进制中第一个 $1$ 所代表的十进制数，那么会有 $2$ 种情况：
   1. 产生 $1$ 次进位 最终二进制中 $1$ 的数量还是 $2$，符合条件。
   2. 产生 $2$ 次进位 最终二进制中 $1$ 的数量为 $1$，符合条件。
   
   不可能再加上比它小的数，这就是最优策略了，加上的数字正好是 $\operatorname{lowbit}(n)$。

---
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t , a;

int lowbit(int n) {return n & -n;}

signed main()
{
    cin >> t;
    while (t--)
    {
        cin >> a;
        int cnt = __builtin_popcountll(a);
        if (cnt >= 3) cout << "No,Commander";
        else if (cnt == 1) cout << a + 1;
        else cout << a + lowbit(a);
        cout << endl;
    }
    return 0;
}
```

---

## 作者：SunsetVoice (赞：0)

比赛时只有 $60$，我太弱了。

首先考虑暴力。万能头里面自带 $\text{popcount}$ 函数，在此不再细说。考虑数字是否合法，非法直接输出，合法向后枚举，直到下一个合法的数出现。

时间复杂度 $O(T\times a)$ 然后就时间就炸飞了。

不合法无需优化，合法则可以推一下规律。

对于一个合法的数 $a$，有 $\text{popcount}(a)=1$ 和 $\text{popcount}(a)=2$ 两种可能。当为前者时，考虑在 $a$ 的二进制表示下在最右位加 $1$，这样就算不进位，新数的 $\text{popcount}$ 值也只是加了一个 $1$，不会超过 $3$。

如果是后者会麻烦一点，因为此时如果产生进位则新数的 $\text{popcount}$ 值会等于 $3$，则为非法。此时要保证进位，则需要在其数二进制下最低位的 $1$ 处加一。此时可以保证进位。

时间复杂度最坏情况 $O(T\log a)$，可以通过。至于为什么还有一个 $\log a$，$\text{lowbit}$ 可以回答你。

还自己写了 $\text{popcount}$，读者可以换成自带函数。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int r;
int pop(long long k){
	r = 0;
	while(k){
		r+=k&1;
		k>>=1;
	}
	return r;
}
int main(){
	long long T,i,n,j;
	cin>>T;
	while(T--){
		cin>>n;
		if(pop(n)>=3){
			cout<<"No,Commander"<<endl; 
		}else{
			if(pop(n)==1)cout<<n+1<<endl;
			else{
				cout<<n+(n&(-n))<<endl;
			}
		}
	}
	
	return 0;
	
}
```

---

## 作者：XSJProgrammer (赞：0)

首先明确题目意义： $\operatorname{popcount}(a)$ 代表 $a$ 的二进制表示中 $1$ 的个数。这个函数我们可以随手实现一个。只需使用短除法，将 $a$ 转化为二进制。注意因为我们只需数出 $a$ 中 $1$ 的个数，因此不需要将所得的余数们倒序排列，转换一位数一位即可。代码：
```cpp
int popcount(long long a){
	int c=0;
	while(a>0){
		c+=a%2;
		a/=2;
	}
	return c;
}
```
有了这个函数，我们的第一个思路自然是暴力。无需解释太多，一个一个数下去即可，代码：
```cpp
#include<iostream>
using namespace std;
int popcount(long long a){
	int c=0;
	while(a>0){
		c+=a%2;
		a/=2;
	}
	return c;
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		long long a;
		cin>>a;
		if(popcount(a)>=3)cout<<"No,Commander"<<endl;
		else{
			long long i;
			for(i=a+1;popcount(i)>=3;i++);
			cout<<i<<endl;
		}
	}
}
```
然而暴力是出不了奇迹的，只能出 TLE：[https://www.luogu.com.cn/record/115761256](https://www.luogu.com.cn/record/115761256)

回看题目，只要一个数的 $\operatorname{popcount}$ 小于等于 $3$ 就是合法的，所以可以在给定的 $0\le a \le 2^{63} $ 区间内，将所有合法的数枚举出来。分成数字中有 $1$ 个 $1$ 和 $2$ 个 $1$ 两种情况：

```cpp
long long pow2(int a){
	long long ans;
	if(a==0)return 1;
	if(a%2==0){
		ans=pow2(a/2);
		ans*=ans;
		return ans;
	}else return 2*pow2(a-1);
}
vector<long long>legal;
void get(){
	for(int i=0;i<64;i++){
		legal.push_back(pow2(i));
	}
	for(int i=0;i<64;i++){
		for(int j=0;j<i;j++){
			long long ans=pow2(i);
			ans+=pow2(j);
			legal.push_back(ans);
		}
	}
	sort(legal.begin(),legal.end());
}
```
```sort``` 负责排序，从而使接下来查找成为可能： ```pow2``` 则是快速幂。另外C++的STL中有 ```find``` 函数，专门用于查找。它有三个参数，分别是查找区域头指针、尾指针、查找元素。我们保留 ```popcount``` 用于快速判断一下非法情况：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int popcount(long long a){
	int c=0;
	while(a>0){
		c+=a%2;
		a/=2;
	}
	return c;
}//to check if illegal

long long pow2(int a){
	long long ans;
	if(a==0)return 1;
	if(a%2==0){
		ans=pow2(a/2);
		ans*=ans;
		return ans;
	}else return 2*pow2(a-1);
}
vector<long long>legal;
void get(){
	for(int i=0;i<64;i++){
		legal.push_back(pow2(i));
	}
	for(int i=0;i<64;i++){
		for(int j=0;j<i;j++){
			long long ans=pow2(i);
			ans+=pow2(j);
			legal.push_back(ans);
		}
	}
	sort(legal.begin(),legal.end());
}
int main(){
	get();
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		long long a;
		cin>>a;
		if(popcount(a)>=3)cout<<"No,Commander"<<endl;
		else{
			cout<<*(find(legal.begin(),legal.end(),a)+1)<<endl;
		}
	}
}
```

[https://www.luogu.com.cn/record/115761256](https://www.luogu.com.cn/record/115761256)

完结!
第一次发题解，求通过!

---

## 作者：_O_v_O_ (赞：0)

首先，我们要明确 $\operatorname{popcount}$ 的意思：

>$\operatorname{popcount(x)}$ 表示二进制下 $x$ 中 $1$ 的个数，其中 $x$ 为十进制。
>
>来自 [赛时公告栏](https://www.luogu.com.cn/paste/fu7dgk4r)。

所以，我们可以直接模拟出该过程：

```cpp
int popcuont(int x){
	int num=0;  //num为统计二进制中有多少个1.
	while(x!=0){  //将x不停右移，直到x为0，这样右移完后所有位都当过最低位。
		if(x&1) num++;  //如果最低位为1，则计数器加一。
		x=x>>1;
	}
	return num;
} 
```

接下来判断题目中输入的数的 $\operatorname{popcount}$ 是否大于三即可如果大于三，直接输出 ``No,Commander``。

然后就是 $\operatorname{popcount}(a)$ 小于三的情况，我们发现暴力往后枚举会超时，所以我们需要分类讨论。

分类讨论无非就 $3$ 种情况：

- $\operatorname{popcount(a)}$ 为 $0$，也就是 $a$ 为 $0$。
- $\operatorname{popcount(a)}$ 为 $1$。
- $\operatorname{popcount(a)}$ 为 $2$。

对于前两种情况直接输出 $a+1$ 即可，证明：

1. $a$ 是 $0$：直接输出 $1$。
2. $\operatorname{popcount(a)}$ 为 $1$：$a+1$ 的 $\operatorname{popcount}$ 最多为 $2$。

对于最后一点，输出它加它的 $\operatorname{lowbit}$ 因为这样相当与将它离最低位最近的 $1$ 向右移动一位，这也是它下一个满足条件的数。

最后，要开 ``long long``。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long

int t;

int lowbit(int x){
	return x&-x;
}

int popcuont(int x){
	int num=0;
	while(x!=0){
		if(x&1) num++;
		x/=2;
	}
	return num;
} 

signed main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(popcuont(n)>=3){
			cout<<"No,Commander\n";
		}
		else{
			if(popcuont(n)==2){
				cout<<n+lowbit(n)<<endl;
			}
			else cout<<n+1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：WhitD (赞：0)

## 题目大意
(题干中的 "popcount(a)" 指的是**二进制数** $a$ 中 1 的个数)。

给定 $T$ 个十进制整数 $a$，如果其二进制下有三个及三个以上 $1$ 则输出 "No,Commander"，否则输出下一个二进制中只含有两个及两个以下 $1$ 的**十进制数**。
## 思路
### 解决 “popcount”
我们首先考虑如何判断 $1$ 的个数，可以先将十进制数转化为二进制数存储在数组里，然后逐位判断，由于题干给出了 $a$ 的取值范围为 $a\le{2^{63}}$，所以数组开到 $65$ 是足够的，复杂度也可以接受。
### 如何寻找下一个合法的数
显然，如果该数的 popcount 值大于 $2$，直接输出文字即可。如果 popcount 值为 $0$，说明这个数只能是 $0$，那下一个合法的数就是 $1$，直接输出即可。

如果 popcount 值为 $1$，我们考虑可能的情况，显然只有 $1,10,100,1000......$ 等等一类二进制数，那此时合法的下一个数就是该十进制数 $+1$。

当 popcount 值为 $2$ 时，朴素的枚举方法就是一直对原数加一，然后判断是否合法，但是这样的时间复杂度是不可接受的。

我们继续考虑可能的情况，举个简单的例子吧：对于 $10100$ 这个数，我们枚举 $10101,10110,10111,11000$，下一个合法的数为 $11000$。从 $10100$ 到 $11000$，从 $20$ 到 $24$，我们发现二进制数中间的 $1$ 向前移了一位，十进制数多了 $4$ 也就是 $2^2$，原二进制的 $1$ 在第三位，$2$ 的指数是 $2$。
#### 于是
我们可以发现，二进制数的 $1$ 前移一位就是原十进制数加上了 $2$ 的 （“$1$” 原来所在位置 $-1$）次方，然后我们就在可接受的时间复杂度下内找到了下一个合法的数。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;//不开long long见祖宗
ull T,a[70];
ull popcount(ull x)//处理popcount
{
	ull i=0,cnt=0;
	memset(a,0,sizeof(a));
	while(x>0)
	{
		i++;
		a[i]=x%2;
		x/=2;
		if(a[i])	//注意这里的a数组是倒序的
			cnt++;
	}
	return cnt;
}
int main()
{
	cin>>T;
	while(T--)
	{
		ull x;
		cin>>x;
		ull pc=popcount(x);			
		if(pc>2)
			cout<<"No,Commander"<<endl;
		else if(pc==1||pc==0)
			cout<<x+1<<endl;
		else//根据思路模拟即可
		{
			for(int i=1;i<=65;i++)
			{
				if(a[i])
				{
					ull cnt=1;
					for(int j=1;j<i;j++)//懒得打快速幂了（反正不会TLE）（划掉）
						cnt*=2;
					cout<<x+cnt<<endl;
					break;
				}	
				
			}
		}
	}
	return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

考虑贪心：如果当前 $1$ 的数量不足 $1$，直接 $+1$ 即可。因为如果末位是 $0$，加 $1$ 一定可以保证 $1$ 的数量小于 $3$；末位是 $1$，则末位变成 $0$，仍符合要求。

继续考虑当前 $1$ 的数量为 $2$ 时的做法。我们发现在非 $1$ 位加 $1$ 会使得数字不合法；为了找到最少的数字，我们只需要在最右的 $1$ 位置加 $1$，$1$ 的数量仍然可以保持在 $2$ 以内。

如何找到最右侧的 $1$ 呢？显然这就是 $\operatorname{lowbit}$ 函数啊！$\operatorname{lowbit}(x) = x \operatorname{and} (-x)$。

**【代码】**

```cpp
if(__builtin_popcountll(n) >= 3){cout << "No,Commander\n";continue;}
if(__builtin_popcountll(n) < 2) {cout << n + 1 << endl;continue;}
cout << n + (n & -n) << endl;
```

---

## 作者：fish_love_cat (赞：0)

**第一个前置芝士：**

什么是 $\operatorname{popcount}(a)$？

[~~爆裂计数？~~](https://fanyi.baidu.com/?aldtype=23#en/zh/pop%20count)

其实这个东西指的是 $a$ 在二进制下值是 $1$ 的位的数量。那么知道了这么一个关键的定义，做起这题就不难了。

---

**第二个前置芝士：**

介绍一个良心函数：

```cpp
__builtin_popcountll(n);
```

这个函数可以返回 $n$ 在二进制下值是 $1$ 的位的数量。有没有感觉很熟悉？这简直就是为这道题量身定做的啊！

---

**第三个前置芝士：**

```cpp
bitset<61> b(n);
```

这个东西可以把 $n$ 直接搞成二进制，$n$ 二进制的每一位都存在 $b$ 里。我们可以直接对 $b$ 的每个位置进行修改，也可以利用自带的 `b.to_ullong()` 把它再转回十进制。这可相当的方便呢。

不过需要注意的是，$b_i$ 上的数值大小换成十进制就是 $2^i$。所以显然的，$i$ 越大，$b_i$ 所代表的数值也越大，别弄错了。~~有个笨蛋搞反了，被卡半小时，因此排名垫底，这个笨蛋是谁我不说。~~

---

**思路：**

先用良心函数 `int x=__builtin_popcountll(n);` 求出位数，然后分情况进行讨论。

---

情况一：$x<2$

结论：直接 $+1$，报出第一个大于当前数字的数。

证明：因为此时 $+1$ 在最坏最糟的情况下，也不过是让 $x=2$。这仍是合法的，也是最优的，所以 $+1$ 即可。

---

情况二：$x>2$

结论：违法，输出 `No,Commander` ~~并速速拷走~~即可。

证明：题目叫我这么干的，没有证明。

---

情况三：$x=2$

显然的，这个时候我们只能在值是 $1$ 的位数不变或减少前提下，加上一个能使新数满足这些条件的最小的数。而这个数要满足的条件经过手搓了亿些数据后可以发现：

假设原数的二进制是：`1 …（省略 k1 个 0）… 1 …（省略 k2 个 0）…`。

那么就应该加上这样的一个二进制数（也就是新数）：`1 …（省略 k2 个 0）…`。

证明：因为不能再多加值是一的位数了，不然就属于不合法的情况了，所以新数的二进制位上值是一的那一位必须与原数重合。要重合有三种选择，但很显然，只与较低位重合结果最小，也最优。所以上面那个手搓出来的东东是正确的。

---

**实现：**

情况一二无需赘述，在此只重点介绍如何实现复杂的情况三。

我们先使用 `bitset` 存储 $n$，然后暴力从低位扫到高位。如果第一次遇上了 $1$，那么就代表这是较低位。我们模拟一下加的过程即可。~~（有个笨蛋居然写成了从高到低扫过去，警钟长鸣）~~

这里有两种情况，正常直接把当前位置置成 $0$，进位到下一位把高位改 $1$ 即可。

但是要想想另一种情况，如果他的下一位本来就是 $1$ 怎么办？这个棘手了，如果按照刚刚的做法，低位的一就直接被吃掉了！所以我们要再特判一下是不是连一，如果是，就继续进位，把两个一都变成 $0$，再把这两个的下一位置成 $1$。

这时，我们就可以直接在 `bitset` 的每一个位置上，直接进行模拟加法进位的操作，非常的方便。

然后……好像没有然后了，用我们方便的 `bitset` 的自带的 `b.to_ullong()` 函数转成十进制输出就行了。

---

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
// __builtin_popcountll();
int main(){
    int t;
    cin>>t;//多测
    while(t--){
        long long n;
        cin>>n;
        if(n==0) cout<<1<<endl;//情况 1 的一部分
        else{
            int x=__builtin_popcountll(n);
            if(x==1) cout<<n+1<<endl;//情况 1 的一部分
            else if(x>=3) cout<<"No,Commander\n";//情况 2
            else{//情况 3
                bitset<61> b(n);
                for(int i=0;i<=60;i++){
                    if(b[i]==1){
                        if(b[i+1]==1) b[i]=0,b[i+1]=0,b[i+2]=1;//连一
                        else b[i]=0,b[i+1]=1;//单个一
                        break;
                    }
                }
                cout<<b.to_ullong()<<endl;//转十进制函数
            }
        }
    }
    return 0;
}
//qwq
```

---

