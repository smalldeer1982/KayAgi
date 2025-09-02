# Bracket Xoring

## 题目描述

You are given a binary string $ s $ of length $ 2n $ where each element is $ \mathtt{0} $ or $ \mathtt{1} $ . You can do the following operation:

1. Choose a balanced bracket sequence $ ^\dagger $ $ b $ of length $ 2n $ .
2. For every index $ i $ from $ 1 $ to $ 2n $ in order, where $ b_i $ is an open bracket, let $ p_i $ denote the minimum index such that $ b[i,p_i] $ is a balanced bracket sequence. Then, we perform a range toggle operation $ ^\ddagger $ from $ i $ to $ p_i $ on $ s $ . Note that since a balanced bracket sequence of length $ 2n $ will have $ n $ open brackets, we will do $ n $ range toggle operations on $ s $ .

Your task is to find a sequence of no more than $ 10 $ operations that changes all elements of $ s $ to $ \mathtt{0} $ , or determine that it is impossible to do so. Note that you do not have to minimize the number of operations.

Under the given constraints, it can be proven that if it is possible to change all elements of $ s $ to $ \mathtt{0} $ , there exists a way that requires no more than $ 10 $ operations.

 $ ^\dagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences "(())()", "()", and "(()(()))" are balanced, while ")(", "(()", and "(()))(" are not.

 $ ^\ddagger $ If we perform a range toggle operation from $ l $ to $ r $ on a binary string $ s $ , then we toggle all values of $ s_i $ such that $ l \leq i \leq r $ . If $ s_i $ is toggled, we will set $ s_i := \mathtt{0} $ if $ s_i = \mathtt{1} $ or vice versa. For example, if $ s=\mathtt{1000101} $ and we perform a range toggle operation from $ 3 $ to $ 5 $ , $ s $ will be changed to $ s=\mathtt{1011001} $ .

## 说明/提示

In the first test case, it can be proven that it is impossible to change all elements of $ s $ to $ \mathtt{0} $ .

In the second test case, the first operation using the bracket sequence $ b = \mathtt{()()} $ will convert the binary string $ s=\mathtt{0000} $ to $ s=\mathtt{1111} $ . Then, the second operation using the same bracket sequence $ b = \mathtt{()()} $ will convert the binary string $ s=\mathtt{1111} $ back to $ s=\mathtt{0000} $ . Note that since all elements of $ s $ is already $ \mathtt{0} $ initially, using $ 0 $ operations is also a valid answer.

In the third test case, a single operation using the bracket sequence $ b = \mathtt{(())()} $ will change all elements of $ s $ to $ \mathtt{0} $ . The operation will happen as follows.

1. $ b_1 $ is an open bracket and $ p_1 = 4 $ since $ b[1,4]=\mathtt{(())} $ is a balanced bracket sequence. Hence, we do a range toggle operation from $ 1 $ to $ 4 $ on the binary string $ s = \mathtt{100111} $ to obtain $ s = \mathtt{011011} $ .
2. $ b_2 $ is an open bracket and $ p_2 = 3 $ since $ b[2,3]=\mathtt{()} $ is a balanced bracket sequence. Hence, we do a range toggle operation from $ 2 $ to $ 3 $ on the binary string $ s = \mathtt{011011} $ to obtain $ s = \mathtt{000011} $ .
3. $ b_3 $ is not an open bracket, so no range toggle operation is done at this step.
4. $ b_4 $ is not an open bracket, so no range toggle operation is done at this step.
5. $ b_5 $ is an open bracket and $ p_5 = 6 $ since $ b[5,6]=\mathtt{()} $ is a balanced bracket sequence. Hence, we do a range toggle operation from $ 5 $ to $ 6 $ on the binary string $ s = \mathtt{000011} $ to obtain $ s = \mathtt{000000} $ .
6. $ b_6 $ is not an open bracket, so no range toggle operation is done at this step.

In the fourth test case, the first operation using the bracket sequence $ b = \mathtt{(((())))} $ will convert the binary string $ s = \mathtt{01011100} $ to $ s = \mathtt{11111001} $ . Then, the second operation using the bracket sequence $ b = \mathtt{()()(())} $ will convert the binary string $ s = \mathtt{11111001} $ to $ s=\mathtt{00000000} $ .

## 样例 #1

### 输入

```
4
1
01
2
0000
3
100111
4
01011100```

### 输出

```
-1
2
()()
()()
1
(())()
2
(((())))
()()(())```

# 题解

## 作者：樱雪喵 (赞：16)

## Description

给定一个长度为 $2n$ 的 $\texttt{01}$ 串 $s$。一次操作定义为：

- 选择一个长度为 $2n$ 的合法括号串（所有括号均匹配）；
- 对于每个左括号，设它的位置为 $l$，与它匹配的右括号位置为 $r$，将 $s$ 的 $[l,r]$ 这个区间取反（$\texttt{0}$ 变成 $\texttt{1}$，$\texttt{1}$ 变成 $\texttt{0}$）。

请构造方案在 $10$ 次操作内将 $s$ 的所有位置变为 $\texttt{0}$，并输出方案。

多组数据，$T\le 10^3$，$\sum n\le 2\times 10^5$。

## Solution

先找一些比较容易直接看出来的性质。

- 每次操作都一定会改变 $s_1$ 和 $s_{2n}$，故 $s_1\neq s_{2n}$ 无解；
- 每次操作都会取反偶数个位置，故 $s$ 中有奇数个 $1$ 无解。


注意到只要这个字符串满足 $\forall i\bmod 2=0,s_i=s_{i+1}$（不含首尾），就可以用一次操作让整个字符串变成一样的。

先假设这里的 $s_1=\texttt{1}$，如果不是可以先做一次 $\texttt{()()\dots()}$ 操作将整个串取反。

具体地，从开头开始令每两个相邻的 $\texttt{1}$ 配成一对括号，显然这些括号位置的取反次数都是 $1$；每两个相邻的 $\texttt{1}$ 之间一定有偶数个 $\texttt{0}$，我们把它们两两配对成 $\texttt{()()\dots}$ 的形式，那么它们因为包含在一组 $\texttt{1}$ 形成的括号内，均不会被取反。  
例如 $s=\texttt{1000011001}$，则构造操作 $\texttt{(()())(())}$。

所以我们如果能构造一些前置操作使字符串满足这个条件就做完了。

考虑对于一个任意的串，怎么让 $s_i$ 和 $s_{i+1}$ 相等：
- 若本身就 $s_i=s_{i+1}$，在这里放一对 $\texttt{()}$，那么这两位的取反状态一定是一样的；
- 否则要么放两个左括号要么放两个右括号，我们根据前面未匹配的括号数判断：如果有未匹配的括号（显然这不会是一个奇数），在这里放 $\texttt{))}$，否则放 $\texttt{((}$。

第二种情况一定出现偶数次（否则不满足有偶数个 $1$），所以这样构造出的括号串一定是匹配的。

综上，我们至多使用三步操作使 $s$ 全为 $0$。

写代码的时候精神状态堪忧，可能和上面讲的没什么关系。（upd: 重写了。）

```cpp
const int N=4e5+5;
int T,n,a[N],b[N],c[N];
char s[N];
int main()
{
    T=read();
    while(T--)
    {
        n=read()<<1; scanf("%s",s+1);
        for(int i=1;i<=n;i++) a[i]=s[i]-'0';
        int cnt=0; for(int i=1;i<=n;i++) cnt+=a[i];
        if(a[1]!=a[n]||(cnt&1)) {printf("-1\n");continue;}
        if(a[1])
        {
            printf("3\n"); 
            for(int i=1;i<=n;i++) a[i]^=1,printf(i&1?"(":")"); printf("\n");
        }
        else printf("2\n");
        int sum=0; a[1]^=1,a[n]^=1;
        printf("(");
        for(int i=2;i<n;i+=2) 
        {
            if(a[i]==a[i+1]) printf("()");
            else if(!sum) printf("(("),a[i+1]^=1,sum^=1;
            else printf("))"),a[i]^=1,sum^=1;
        }
        printf(")\n(");
        for(int i=2;i<n;i+=2) printf(a[i]?")(":"()");
        printf(")\n");
    }
    return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：6)

## 思路

显然总异或和为 1 一定无解。

发现每次操作首位和末位一定会被翻转，于是 $s_1\neq s_{2n}$ 也无解。

首先一步操作使 $s_{2i}=s_{2i+1}$。具体地，见到相等就放 `()`，见到不等就放 `((` 或 `))`。

考虑操作 `(()()()...())`，仅会翻转第一个和最后一个。

考虑操作 `((()()...()))`，除了第二个和倒数第二个都会翻转。

同时使用以上两种，那么除了两端四个以外都会翻转。

这意味着我们可以进行形如 `11000011->11111111` 的操作。（对于不需操作的地方，填 `()`，两次操作之后不变）

注意两端四个对这个操作是必需的，并且不可重叠。

进行两次这个操作，可以使整串全 `0` 或全 `1`。全 `1` 就再加一步全 `()` 整体翻转。

例如 `1100001100110011`，一次变成 `1111111100111111`，两次变成 `1111111111111111`。

好像有步数更少的做法。无所谓。我的比较好想吧。

## code

```cpp
#include<stdio.h>
#include<vector>
#include<string>
#define N 400009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,tmp;char s[N],o;vector<string>ans;
struct __readt__{inline __readt__(){read(t);}}_readt___;
main()
{
	read(n);
	for(int i=0;i<n<<1;s[i++]^='0')for(;s[i]=nc(),(s[i]^'0')&&(s[i]^'1'););
	int sum=0;
	for(int i=0;i<n<<1;sum^=s[i++]);
	if(sum){printf("-1\n");goto nxt;}
	if(s[0]^s[(n<<1)-1]){printf("-1\n");goto nxt;}
	ans.clear();ans.emplace_back("");
	tmp=0;
	for(int i=0;i<n;++i)
		if(s[i<<1]==s[i<<1|1])ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
		else if(tmp^=1)ans.back()+="((",s[i<<1]^=1;
		else ans.back()+="))",s[i<<1|1]^=1;
	// for(int i=0;i<n<<1;putchar('0'^s[i++]));putchar('\n');
	ans.emplace_back("");
	tmp=-1;o=s[0];
	for(int i=0;i<n;++i)
		if(s[i<<1]==o)
			if(tmp>>31)
				if(i<n-1&&(s[i+1<<1]^o))ans.back()+="((",s[i<<1]^=1,tmp=i;
				else ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
			else ans.back()+="))",s[i<<1|1]^=1,tmp=-1;
		else ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
	if(~tmp)s[tmp<<1|1]^=1,ans.back()[tmp<<1|1]=')';
	// for(int i=0;i<n<<1;putchar('0'^s[i++]));putchar('\n');
	ans.emplace_back("");
	tmp=-1;
	for(int i=0;i<n;++i)
		if(s[i<<1]^s[i<<1|1])
			if(tmp>>31)ans.back()+="((",s[i<<1]^=1,tmp=i;
			else ans.back()+="))",s[i<<1|1]^=1,tmp=-1;
		else if(tmp>>31)ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
			else ans.back()+=")(";
	// for(int i=0;i<n<<1;putchar('0'^s[i++]));putchar('\n');
	ans.emplace_back("");
	tmp=-1;o=s[0];
	for(int i=0;i<n;++i)
		if(s[i<<1]==o)
			if(tmp>>31)
				if(i<n-1&&(s[i+1<<1]^o))ans.back()+="((",s[i<<1]^=1,tmp=i;
				else ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
			else ans.back()+="))",s[i<<1|1]^=1,tmp=-1;
		else ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
	if(~tmp)s[tmp<<1|1]^=1,ans.back()[tmp<<1|1]=')';
	// for(int i=0;i<n<<1;putchar('0'^s[i++]));putchar('\n');
	ans.emplace_back("");
	tmp=-1;
	for(int i=0;i<n;++i)
		if(s[i<<1]^s[i<<1|1])
			if(tmp>>31)ans.back()+="((",s[i<<1]^=1,tmp=i;
			else ans.back()+="))",s[i<<1|1]^=1,tmp=-1;
		else if(tmp>>31)ans.back()+="()",s[i<<1]^=1,s[i<<1|1]^=1;
			else ans.back()+=")(";
	// for(int i=0;i<n<<1;putchar('0'^s[i++]));putchar('\n');
	if(s[0])
	{
		ans.emplace_back("");
		for(int i=n;i--;ans.back()+="()");
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();printf("%s\n",ans[i++].c_str()));
	nxt:if(--t)main();
}
```

---

## 作者：_H17_ (赞：2)

## 题目分析

讲一种神奇、难理解的方法。

首先，通过观察可以发现，每次操作必然同时改变首尾，所以首尾不同需要输出 `-1`。

接着，每次取得一个括号区间长度一定是偶数，如果有奇数则总有一个配不上的，毕竟括号都是一对的，所以和是奇数也输出 `-1`。

然后呢？首尾如果都是 $1$ 那就反转一次所有的。

接下来只用考虑首尾是 $0$ 的了。

其实两次操作即可（不包括为首尾翻转）。

放一个样例：

Input File:

```
100111
```

Output File:

```
3
()()()//翻转变成 011000
()(())
(()())
```

每次是 $0$ 就从后找到 $0$ 匹配位括号，两次就消了。

于是对于 $0$，把前一半设为 `(`，后一半设为 `)`，两次操作都这样做。

对于 $1$ 需要一次从前面 `(` 补上 `)` 来 $1 \to 0$，然后第二次反过来因为有括号包夹即 `(...()...)`，所以第二次不变。

当然对于 $1$，一次是补上 `)`，另一次就是加上 `)`。

实现上比较巧妙，可以自行体会一下。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=400001;
int T,n,num[N],sum;
string s,a,b;
void Main(){
	cin>>n>>s;
	sum=0,n*=2,a=b="";//初始化、长度二倍
	for(int i=0;i<n;i++)
		num[i]=s[i]-'0',sum+=num[i];//数字化、求和
	if(num[0]!=num[n-1]||sum&1){//首尾不一、奇数
		cout<<"-1\n";
		return;
	}
	if(num[0]==1){//首尾是 1
		cout<<"3\n";
		for(int i=0;i<n;i++)//改全部
			num[i]^=1;
		sum=n-sum;
		for(int i=1;i<=n/2;i++)//注意 () 是两个字符，所以除以 2
			cout<<"()"; 
		cout<<'\n';
	}
	else
		cout<<"2\n";
	for(int i=0,bl=0,c=0;i<n;i++){
		if(num[i]){//需要改变
			if(bl)
				a+='(',b+=')';
			else
				a+=')',b+='(';
			bl^=1;//到底是补 ) 还是加 (
		}
		else{//不用改
			if(c<(n-sum)/2)//前一半
				a+='(',b+='(';
			else//后一半
				a+=')',b+=')';
			c++;
		}
	}
	cout<<a<<'\n'<<b<<'\n';
	return;
}
int main(){
	for(cin>>T;T--;)
		Main();
	return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言
一周不写构造感觉身上有设计蚂蚁在爬。

其实是觉得最近 DS 写太多了要稍微锻炼一下脑子。

感觉 F 小于 E。

# Solution

首先无解条件显然：$1$ 个数为奇数，或者 $s$ 开头结尾不相等。

大胆猜测剩下情况下都有解。

我们先手玩一番看看一次操作，每种字符的实际影响是什么。

容易发现：奇数位上 `(` 翻 `)` 不翻，偶数位上 `(` 不翻 `)` 翻。

这个奇偶位效果不一样非常恼火，我们考虑每次操作添加一个“对所有偶数位取反”，现在都是 `(` 翻 `)` 不翻，只要总的操作次数为偶数，就可以消除对偶数位取反这玩意。

但是我们发现每次操作第一位和最后一位必变化，所以当它们都是 $1$ 的时候可以先乱操作一次。

继续猜测接下来两次可以解决，考虑构造方案。

发现当 $s_i=0$ 时候两次操作括号串对应位置应该相同，否则应该相异。

简单了啊，对于所有 $0$ 的位置前一半弄 `(` 后一半弄 `)`，对于所有 $1$ 的位置让 `(` 在两次操作交替出现。

证明一下为啥这样对：

首先由于 $0$ 和 $1$ 出现次数是偶数，可以保证两个串 `(` 和 `)` 一样多。

其次括号序列的要求是任意前缀和非负，分开考虑 $0$ 位置和 $1$ 位置对前缀和的贡献。

$0$ 位置在最后一位贡献为 $0$，其余位置贡献 $\ge 1$。

$1$ 位置在任意时刻贡献 $\ge -1$ 且最后一位贡献为 $0$。

综上，前缀和保持了非负。

分析到这里，你会发现其实偶数位取反不必要了，但是它引导了你每次考虑两步操作，我觉得还是相当有用的，故保留。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,i;
string s,a[2];
char c[2]={'(',')'};
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>s;n*=2;
		int ans=2,cnt[2]={0,0};
		if(s[0]=='1')
		{
			ans++;
			for(i=0;i<n;i++) s[i]=s[i]^1;
		}
		for(i=0;i<n;i++) cnt[s[i]-'0']++;
		if((cnt[0]&1)||s[0]!=s[n-1])
		{
			cout<<-1<<"\n";
			continue;
		}
		cout<<ans<<"\n";
		cnt[0]/=2;
		a[0].resize(n),a[1].resize(n);
		for(i=0;i<n;i++)
		{
			if(s[i]=='0') a[0][i]=a[1][i]=c[--cnt[0]<0];
			else a[0][i]=c[cnt[1]&1],a[1][i]=c[(++cnt[1
			])&1];
		}
		if(ans==3)
		{
			for(i=0;i<n/2;i++) cout<<"()";
			cout<<"\n";
		}
		cout<<a[0]<<"\n"<<a[1]<<"\n";
	}
	return 0;
}
```
# The End.

---

## 作者：larsr (赞：0)

## 判断合法
设 $m=2n$。

可以考虑到，每次的操作 $s_1$ 和 $s_m$ 都要翻转，那么当 $s_1 \neq s_m$ 时无解。

又可以考虑到 $s$ 会有偶数位要翻转，那么当 $1$ 的数量为奇数时无解。
## 括号序列对 $s$ 的影响
设 $f(x)=[2|x]$，$B_{i,0}$ 为 $b_{1\dots i}$ 中左括号的数量，$B_{i, 1}$ 为 $b_{1\dots i}$ 中右括号的数量。

可以想到 $s_i$ 翻转次数为 $B_{i,0} - B_{i - 1,1}$。其中 $B_{i,0}$ 代表配对括号的左括号在 $i$ 之前的，$B_{i-1,1}$ 代表配对括号右括号在 $i-1$ 之前的。这样就可以算出包含 $i$ 的配对括号个数。

那么翻转后的 $s_i$ 为 

$$s_i \operatorname{xor} f(B_{i,0}-B_{i-1,1})$$

因为 $f$ 是考虑奇偶性的，所以原式为

$$s_i\operatorname{xor} f(B_{i,0}+B_{i-1,1})$$
$$s_i\operatorname{xor} f(i + [b_i = \text{')'}])$$
## 解决
如果 $s_1 = s_m = 1$，那么可以通过 `()()...()()` 翻转成 $s_1 = s_m = 0$。那么我们只用处理首尾为 $0$ 的 $s$ 即可。

此时 $k$ 必须为 $2$ 的倍数才能完成任务，那么我们就考虑 $k = 2$ 时如何解决。

设 $b_1$ 为第一次翻转时的括号序列，$b_2$ 为第二次翻转时的括号序列。那么

$$s_i \operatorname{xor} f(i + [b_{1,i} = \text{')'}])\operatorname{xor} f(i + [b_{2,i} = \text{')'}]) = 0$$

$$s_i \operatorname{xor} f(i + [b_{1,i} = \text{')'}] + i + [b_{2,i} = \text{')'}]) = 0$$

$$s_i \operatorname{xor} f([b_{1,i} = \text{')'}] + [b_{2,i} = \text{')'}]) = 0$$

$$s_i = f([b_{1,i} = \text{')'}] + [b_{2,i} = \text{')'}])$$

那么当 $s_i=0$ 时，需要 $b_{1,i} = b_{2,i}$。当 $s_i=1$ 时，需要 $b_{1,i} \neq b_{2,i}$。
## 构造
对于所有 $s_i=0$ 的，前一半的 $i$ 设置 $b_{1,i} = b_{2,i}=\text{'('}$，后一半的 $i$ 设置 $b_{1,i} = b_{2,i}=\text{')'}$。

对于所有 $s_i = 1$ 的，如果是第奇数个出现的，那么 $b_{1,i}=\text{'('},b_{2,i}=\text{')'}$，否则 $b_{1,i}=\text{')'},b_{2,i}=\text{'('}$。

考虑合法性，首先左括号的数量一定等于右括号的数量。其次，如果单考虑 $s_i = 0$ 的必定合法，而 $s_i=1$ 的对前缀的左括号和右括号数量差的影响 $\leq 1$，并且 $b_{1,1}=b_{2,1}=\text{'('}$，所以构造完的括号序列是合法。

总的来说，题解是比较好懂的，但要自己想的话非常困难，这就是构造题和思维题的难处。
## code
```cpp
#include<cstdio>
#define N 500010
using namespace std;
int n, a[N], m;
int p[2][N];
char s[N];
void slove()
{
	scanf("%d%s", &n, s + 1);
	m = 2 * n;
	int sum = 0;
	for(int i = 1; i <= m; i++)a[i] = s[i] - '0', sum += a[i];
	if(a[1] != a[m] || sum % 2 != 0)
	{
		printf("-1\n");
		return;
	}
	if(a[1])
	{
		printf("3\n");
		for(int i = 1; i <= n; i++)printf("()");
		printf("\n");
		for(int i = 1; i <= m; i++)a[i] ^= 1;
		sum = m - sum;
	}
	else printf("2\n");
	int b = m - sum, num = 0, k = 0;
	for(int i = 1; i <= m; i++)
	{
		if(!a[i])
		{
			if(num * 2 >= b)p[0][i] = p[1][i] = 0;
			else p[0][i] = p[1][i] = 1;
			num++;
		}
		else
		{
			if(k)p[0][i] = 0;
			else p[0][i] = 1;
			p[1][i] = p[0][i] ^ 1;
			k ^= 1;
		}
	}
	for(int i = 1; i <= m; i++)
	{
		if(p[0][i])printf("(");
		else printf(")");
	}
	printf("\n");
	for(int i = 1; i <= m; i++)
	{
		if(p[1][i])printf("(");
		else printf(")");
	}
	printf("\n");
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)slove();
	return 0;
}
```

---

## 作者：Maverik (赞：0)

##### Statement

给一个长度为 $2n$ 的 $01$ 串。你可以进行 $k$ 次操作（$k$ 由你决定），每次你可以给出一个匹配的括号序列 $S$，这次操作将会进行：

+ 对于任意一个 $i(1 \le i \le 2n)$，若 $S_i$ 为 $\texttt{(}$，定义与其匹配的右括号位置为 $p_i$。对区间 $[i,p_i]$ 进行 $01$ 反转。

构造一种使得给出串变成全 $0$ 串的方案，或报告无解，输出 $\texttt{-1}$。多组数据。$n \le 2 \times 10^5, k \le 10$。

##### Solution

找一些无解的充分条件，由于匹配括号之间必然有偶数个括号，所以任意操作只会取反偶数位置，有奇数个 $1$ 无解。同时 $a_1$、$a_n$ 必然被取反 $k$ 次，$a_1\neq a_n$ 也无解，同时还能知道 $k$ 的奇偶性，但性质太弱了没什么用。考虑用一些固定的操作凑点东西，首先 ```()()...()``` 相当于全局取反，```(((...)))``` 相当于取反奇数位。对于原序列考虑，相邻 $1$ 之间有偶数个 $0$ 的时候可以构造 ```(()()...()())``` 使得两个 $1$ 变成零，而偶数 $1$ 段仍然如此，推广一下可以发现用一步操作变为全相等的序列，满足相邻 $1$ 之间有偶数个 $0$、相邻 $0$ 之间有偶数个 $1$。归纳后等效于 $\forall i\neq n \wedge i\neq 1 \wedge i\bmod 2=0,a_i=a_{i+1}$ 时一定可以通过一步操作使得全局相等，再选择拼上全局取反就全 $0$ 了。如何构造出上述条件的序列，这仍然是容易的，对于已经相等的位置对，填 ```()``` 不会改变相对的奇偶性；对于不相等的位置对，要不填 ```((```、要不填 ```))```，这和普通的括号序构造是等价的，用栈贪心构造就行。由此，最多用三次操作就可以还原。

##### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int n,a[maxn],opt[maxn];
char s[maxn],oper[maxn];
vector<string>ans;
vector<int>stk;
inline void print()
{
	string str;
	for(int i=1;i<=n;i++) str.push_back(oper[i]);
	ans.push_back(str);
	for(int i=1;i<=n;i++)
	{
		if(oper[i]=='(') stk.push_back(i);
		else opt[stk.back()]^=1,opt[i+1]^=1,stk.pop_back();
	}
	for(int i=1,sum=0;i<=n;i++) sum^=opt[i],a[i]^=sum,opt[i]=0;
}
inline void solve()
{
	cin>>n>>(s+1),n*=2;
	for(int i=1;i<=n;i++) a[i]=s[i]=='1';
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=a[i];
	if((cnt&1) || a[1]!=a[n]) return cout<<"-1\n",void();
	
	cnt=0,oper[1]='(',oper[n]=')';
	for(int i=2;i<n;i+=2)
	{
		if(a[i]==a[i+1]) oper[i]='(',oper[i+1]=')';
		else if(cnt) oper[i]=oper[i+1]=')',cnt--;
		else oper[i]=oper[i+1]='(',cnt++;
	}
	print();
	if(!a[1]){ for(int i=1;i<=n;i++) oper[i]=(i&1)?'(':')'; print(); }
	cnt=0,oper[1]='(',oper[n]=')';
	for(int i=2;i<n;i+=2)
	{
		if(!a[i]) oper[i]='(',oper[i+1]=')';
		else oper[i]=')',oper[i+1]='(';
	}
	print();
	cout<<ans.size()<<'\n';
	for(auto str:ans) cout<<str<<'\n';
	ans.clear(); for(int i=1;i<=n+5;i++) opt[i]=0;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T; cin>>T; while(T--) solve();
}
```



---

## 作者：PersistentLife (赞：0)

来发不一样的做法。

显然的，有解的必要条件是：最左边和最右边的字符相同，且 $1$ 的出现次数为偶数。通过构造可以证明是充要的。

考虑这样一个 pattern：`(())`，放上它可以实现类似于将 $x,x+1(x \bmod 2=0,2 \le x \le 2n-2)$ 翻转的效果，再考虑这样一个 pattern：`((()))`，放上它可以实现类似于将 $x,x+3(x \bmod 2=0, 2 \le x \le 2n-4)$ 翻转的效果。

对于所有 $x(x \bmod 2=0,2 \le x \le 2n-2)$，连边 $x,x+1$；对于所有 $x(x \bmod 2=0,2 \le x \le 2n-4)$，连边 $x,x+3$，可以发现连出来了一条链，从一端往另一端扫过去就行，由于 $1$ 出现偶数次，容易发现一定能构造出解。

但是还有一个限制，一次操作的所有 pattern 不能相交，先考虑 `(())`，可以按下标奇偶分类；再考虑 `((()))`，可以按下标模 $3$ 分类。操作完之后，如果发现串变成了 `1000...0001` 或 `0111...1110`，就用 `(()()...()())` 操作一下；然后如果串变成了 `1111...1111`，就用 `()()...()()` 操作一下。

操作次数是 $2+3+1+1=7$ 次。

---

## 作者：BreakPlus (赞：0)

赛后 3min 过了这题。

----

+ 先保证首尾都为 $0$，即可以一次 $T_0=\texttt{()()} \cdots \texttt{()}$，询问 $T_0$ 来解决首位都为 $1$ 的情况。首位不一致无解，奇数个 $1$ 也无解。

+ 然后假设我们又进行了偶数次操作，则我们可以将奇数层括号看作不翻转，偶数层看作翻转。

---


+ 我们将序列以一种方式划分。如 $n=3$ 是这样的：$a_1\ ; \ a_2, a_3\ ; \ a_4, a_5\ ; \ a_6$。即除首尾外两个一组。之所以这样操作，是因为首位一定分别取 $\texttt{(}$ 和 $\texttt{)}$，我们无法对其进行有意义的操作。

+ 考虑假设对于任意正整数 $k$，第 $2k-1$ 和 $2k$ 个数之间的间隔为偶数个元素，且第一个 $1$ 出现在一个组的左边的元素。如 $n=3$ 时可以是 $S = 0\ ;\ 1, 0\ ;\ 0, 1\ ;\ 0$。

+ 设本次操作串 $T'$ 初始为 $\texttt{()()()}$。若 $a_2$ 和 $a_5$ 均为 $1$，我们可以通过交换 $T'_2$ 和 $T'_5$ 实现消去 $a_2,a_5$ 的操作。即 $T' = \texttt{((()))}$。然后再操作 $T_0$ 反转回来。

+ 对于多个 $1$ 的情况可以进行多次交换，可以在一次操作中同时实现两两消去 $1$。对于第一个 $1$ 在一个组的右边的情况读者可以自行考虑如何归约成在左边的情况。

---

+ 但如何使第 $2k-1$ 和 $2k$ 个数之间的间隔为偶数个元素？我们发现，很容易做到交换一个组里的两个元素。而对于两个 $1$，若间隔为奇数个元素，一定可以通过将其中一个 $1$ 交换到它的组里的另一个地方来调整。

+ 而若两个 $1$ 均无法调整（所在的两个组都是 $1$，动不了），它们之间的间隔一定是几个完整的组，即偶数个元素，不用管它。

+ 至此我们可以完成将序列调整为我们想要的状态的操作。

----

```cpp
ll n; char str[400005], tmp[400005];
char ans[15][400005]; ll cnt;
void input(){
    ++cnt; memcpy(ans[cnt], tmp, sizeof(tmp));
    ll now = 0;
    for(ll i=1;i<=n;i++){
        if(ans[cnt][i]==')') --now;
        if((now+1)&1) {
            str[i]-='0'; str[i]^=1; str[i]+='0';
        }
        if(ans[cnt][i]=='(') ++now;
    }
}
void redo(){
    for(ll i=1;i<=n;i+=2) tmp[i]='(', tmp[i+1]=')';
}
vector<ll>seq; vector<P> pi;
void solve(){
	n=read()*2; seq.clear();cnt=0;pi.clear();
    scanf("%s",(str+1));
    ll q=0;
    for(ll i=1;i<=n;i++) q += (str[i]=='1');
    if(q&1 || ((str[1]-'0') ^ (str[n]-'0'))) {
        puts("-1");
        return;
    }
    if(str[1]=='1'){
        
        for(ll i=1;i<=n/2;i++) tmp[i]='(';
        for(ll i=n/2+1;i<=n;i++) tmp[i]=')';
        input();
    }
    ll lst = -1;
    for(ll i=2;i<n;i++){
        if(str[i]=='1'){
            if(lst == -1){
                lst = i;
            }else {
                if((i-lst-1)&1){
                    if(str[lst]==str[lst^1]) seq.pb(minn(i, i^1)), pi.pb(lst, i^1);
                    else seq.pb(minn(lst, lst^1)), pi.pb(lst^1, i);
                }else{
                    pi.pb(lst, i);
                }
                lst = -1;
            }
        }
    }
    redo(); 
    for(auto op: seq){
        swap(tmp[op], tmp[op^1]);
    }
    input();
    redo();
    for(ll i=0;i<pi.size();++i){
        ll l = pi[i].fi, r = pi[i].se;
        if(l%2==0) {
            swap(tmp[l],tmp[r]);
        }else{
            if(!(i>0 && pi[i-1].se+1==l)) tmp[l-1]='(';
            if(!(i<pi.size()-1 && pi[i+1].fi==r+1)) tmp[r+1]=')';<<pi[i+1].se<<endl;
        }
    }
    input();

    seq.clear(); pi.clear();
    lst = -1;
    for(ll i=2;i<n;i++){
        if(str[i]=='1'){
            if(lst == -1){
                lst = i;
            }else {
                if((i-lst-1)&1){
                    if(str[lst]==str[lst^1]) seq.pb(minn(i, i^1)), pi.pb(lst, i^1);
                    else seq.pb(minn(lst, lst^1)), pi.pb(lst^1, i);
                }else{
                    pi.pb(lst, i);
                }
                lst = -1;
            }
        }
    }
    redo(); 
    for(auto op: seq){
        swap(tmp[op], tmp[op^1]);
    }
    input();
    redo();
    for(ll i=0;i<pi.size();++i){
        ll l = pi[i].fi, r = pi[i].se;
        if(l%2==0) {
            swap(tmp[l],tmp[r]);
        }else{
            if(!(i>0 && pi[i-1].se+1==l)) tmp[l-1]='(';
            if(!(i<pi.size()-1 && pi[i+1].fi==r+1)) tmp[r+1]=')';
        }
    }
    input();
    printf("%lld\n", cnt);
    for(ll i=1;i<=cnt;i++){
        for(ll j=1;j<=n;j++) putchar(ans[i][j]);
        puts("");
    }
}
```

---

## 作者：Aleph_Drawer (赞：0)

### 0 前言

高妙构造题！

Tony 老师还是太强大了。唉，是这样的。

讲的很长，主要是为了说清楚。

### 1 题目大意

给你一个由 $\texttt{01}$ 构成的序列。你可以做不超过 $10$ 次如下操作：选定一个合法括号序列，对每一对位置为 $l,r$ 的匹配括号，将序列上 $[l,r]$ 的位置取反。

### 2 题解

本题有多种解法，以下分享类似于 `小吴同学wtc` 的解法。

事实上，感觉本题只要确定一个比较对的方向，然后想，就可以做出来了。因为限制其实给的很松，正统 `wtc` 解法上限为 $3$，我就稍微菜一点，要 $4$。

首先我们先判断一手无解。显然，如果 $a_1 \operatorname{xor} a_{2n} = 1$ 或者 $\bigoplus_{i = 1}^{2n} a_i = 1$ 那么是无解的。

其他情况都是有解的，会在接下来的解法中说明。

首先忽略 $a_1$ 和 $a_{2n}$，考虑什么情况下是可以做到做一次就可以满足全部数都是 $\texttt 0$ 或者 $\texttt 1$。

显然的，类似于 $\texttt{100001111110011001}$ 是可以做到一次转换的。具体的，输出序列可以为 $\texttt{(()())()()(())(())}$。构造方法如下：

1. **两两**匹配所有的 $\texttt 1$，分别向它们赋值 $\texttt ($ 和 $ \texttt)$。
2. **两两**匹配所有的 $\texttt 0$，分别向它们赋值 $\texttt ($ 和 $ \texttt)$。

容易观察到如果满足上面的条件，构造出来的括号序列一定是合法的。

那么，什么样的序列才能满足这样构造满足条件呢？

设一段两两匹配的 $\texttt 1$ 区间为 $[l,r]$。那么，我们要求 $\forall [l,r] , r - l - 1 \equiv 2 \pmod 0$，即中间夹着的 $\texttt 0$ 均为偶数个。显然序列如果是这样的格式，就可以按照上述方法构造满足要求。

接着想怎么让一个任意数列构造成这个样子。我们可以说明任意的之前判断有解的数列都可以变成这种格式。

先 rand 一个数列方便理解（忽略掉了第一个和最后一个）：
$$
\texttt{0110101011000101010110100111}
$$
这是一个任意的，满足有解条件的序列。不妨先给他们两两分组。

发现这么一件事情，一个满足要求（即使得存在一次转换使得满足全部数相同）的数列一定是 $\texttt{10}$ 然后接若干段 $\texttt{00}$ 然后接一个 $\texttt {01}$ 或者是 $\texttt{11}$ 这两种东西拼接在一起。

不妨来决定哪个两两构成的小组是要“翻转”的。来演示一下流程。

首先是对于一组内存在两个不同的数，我们按照上面的规则，决定翻转还是不翻转：
$$
\texttt{[01]10101011000101010110100111}
$$
选中的该组为 $\texttt{01}$，前面没有 $\texttt{10}$，于是它就要变为 $\texttt{10}$，要翻转。
$$
\texttt{{\color{purple}01}[10]101011000101010110100111}
$$
（红色表示要翻转的颜色，蓝色表示“前面的”$\texttt{10}$，而紫色就是二者兼备）

选中的改组为 $\texttt{10}$，前面**有** $\texttt{10}$，于是他就要变为 $\texttt{01}$，要翻转。
$$
\texttt{{\color{red}0110}{\color{blue}10}[11]000101010110100111}
$$
现在来到了一组内存在两个相同的数的情况，我们仍然是按照上面的规则，决定翻转还是不翻转。

由于选中的该组为 $\texttt{11}$，而前面存在 $\texttt{10}$，那么它是要变为 $\texttt{00}$ 的，要翻转。
$$
\texttt{{\color{red}0110}10{\color{red}11}0001{\color{red}01}01{\color{red}0110}1001[11]}
$$
而对于选中的该组为 $\texttt{11}$，由于前面不存在 $\texttt{10}$，那么它是不需要翻转的。

最终结果如下：
$$
\texttt{{\color{red}0110}10{\color{red}11}0001{\color{red}01}01{\color{red}0110}100111}
$$
那么，我们简单总结一下：我们记录一个标记表示前面存不存在 $\texttt{10}$。如果遇到一组内存在两个不同的数，那么翻转标记，同时按照要求决定要不要翻转这组数。如果一组内两个数相同，就按照标记的要求修改即可。

那么最后一个关键问题来了，我们如何处理“两个两个翻转的这种操作”？以及，如果你还记得，我们为什么要忽视 $a_1, a_{2n}$ 这两个数？

仍然还是以上面那个数列为例子，这次，我们在两侧加上 $a_{1}$ 和 $a_{2n}$。
$$
\texttt{{\color{green}1}{\color{red}0110}10{\color{red}11}0001{\color{red}01}01{\color{red}0110}100111{\color{green}1}}
$$
首先我们先在两侧填写 $\texttt ($ 和 $\texttt )$。
$$
\texttt{{\color{green}1}{\color{red}0110}10{\color{red}11}0001{\color{red}01}01{\color{red}0110}100111{\color{green}1}} \\
\texttt{({\color{red}??}????????????????????????)}
$$
此时我们还是一组一组的考虑。红色表示我正在考虑的位置。假设这个组是要翻转的。那么，不难发现，填写 $\texttt{)(}$ 就可以符合要求。为什么？因为我们之前已经有了一个左括号（这正是之前忽略 $a_1$ 和 $a_{2n}$ 的原因，为了填写 $\texttt{(}$ 以及 $\texttt )$），所以此时填写 $\texttt{)(}$ 就可以使得左边的数被翻转。而右边的那个数，由于最右侧有一个括号，所以最后它也是会被翻转的。

不难发现，此后考虑序列的时候仍然存在一个左括号的环境，而且由于左右两侧括号的存在，这样填写一定合法，所以可以推广到所有的需要翻转的组：
$$
\texttt{{\color{green}1}{\color{red}0110}10{\color{red}11}0001{\color{red}01}01{\color{red}0110}100111{\color{green}1}} \\
\texttt{()()({\color{red}??}????????????????????)}
$$
那么，对于不需要翻转的组，我们怎么做呢？考虑填写 $\texttt{()}$。检验合理性和上述两个条件。首先，由于之前已经有一个左括号环境，那么此时这一个组就相当于翻转了两次，就相当于没有翻转，是合理的。然后是两个条件，首先左括号环境还在，没问题。而且这样子填写也肯定还是合法的。

那么，问题就解决了，按照上述方法全部填写完毕并操作。
$$
\texttt{{\color{green}1}{\color{red}0110}10{\color{red}11}0001{\color{red}01}01{\color{red}0110}100111{\color{green}1}} \\
\texttt{()()(())(()())(())()(()()())} \\
\texttt{0100110000001100110011001110}
$$
然后再做一下我们之前提到的操作。之前忽略了 $a_1$ 和 $a_{2n}$，仿照上述方法，填写 $\texttt ($ 和 $\texttt{)}$。我们就得到了如下结果：
$$
\texttt{0100110000001100110011001110} \\
\texttt{((())(()()())(())(())(())())} \\
\texttt{1111111111111111111111111111}
$$
最后一个问题，如何让所有数变成 $\texttt{0}$？

这个随便做吧，只要用 $\texttt{(()()()...()())}$ 来翻转上述情况（也有可能不需要），然后用 $\texttt{()()()...()()}$ 把整个序列变成 $\texttt 0$ 即可。

操作次数最多 $4$ 次。时间复杂度明显是 $O(n)$ 的。

### 2 代码

很丑很丑。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 4e5 + 405;

int t, n, a[N];
bool isflp[N];
int opr[11][N], oprsum = 0;

int main() {
    scanf("%d", &t);
    for(; t; --t) {
        oprsum = 0;
        scanf("%d", &n);
        char str = getchar();
        int len = 0;
        while(str < 33 || str > 126) str = getchar();
        while(str >= 33 && str <= 126) {
            a[++len] = str - '0';
            str = getchar();
        }
        if(a[1] != a[2 * n]) {
            printf("-1\n");
            continue;
        }
        int xorsum = 0;
        for(int i = 1; i <= 2 * n; i++) {
            xorsum ^= a[i];
        }
        if(xorsum) {
            printf("-1\n");
            continue;
        }
        bool tag = 0;
        for(int i = 2; i < 2 * n; i += 2) {
            if(tag == 0) {
                if(a[i] == 0 && a[i + 1] == 0) isflp[i >> 1ll] = 1;
                if(a[i] == 0 && a[i + 1] == 1) isflp[i >> 1ll] = 1, tag = 1;
                if(a[i] == 1 && a[i + 1] == 0) isflp[i >> 1ll] = 0, tag = 1;
                if(a[i] == 1 && a[i + 1] == 1) isflp[i >> 1ll] = 0;
            }
            else if(tag == 1) {
                if(a[i] == 0 && a[i + 1] == 0) isflp[i >> 1ll] = 0;
                if(a[i] == 0 && a[i + 1] == 1) isflp[i >> 1ll] = 0, tag = 0;
                if(a[i] == 1 && a[i + 1] == 0) isflp[i >> 1ll] = 1, tag = 0;
                if(a[i] == 1 && a[i + 1] == 1) isflp[i >> 1ll] = 1;
            }
        }
        oprsum++;
        a[1] ^= 1, a[2 * n] ^= 1;
        opr[oprsum][1] = 1, opr[oprsum][2 * n] = 2;
        for(int i = 2; i < 2 * n; i += 2) {
            if(isflp[i >> 1ll]) opr[oprsum][i] = 2, opr[oprsum][i + 1] = 1, a[i] ^= 1, a[i + 1] ^= 1;
            else opr[oprsum][i] = 1, opr[oprsum][i + 1] = 2;
        }
        oprsum++;
        a[1] ^= 1, a[2 * n] ^= 1;
        opr[oprsum][1] = 1, opr[oprsum][2 * n] = 2;
        tag = 0;
        bool tag2 = 0;
        for(int i = 2; i < 2 * n; i++) {
            if(tag == 0) {
                if(a[i] == 1) opr[oprsum][i] = 1, tag = 1, tag2 = 0;
            }
            else if(tag == 1) {
                if(a[i] == 1) opr[oprsum][i] = 2, tag = 0;
                else if(a[i] == 0) {
                    if(tag2 == 0)
                        opr[oprsum][i] = 1, tag2 = 1;
                    else if(tag2 == 1)
                        opr[oprsum][i] = 2, tag2 = 0;
                }
            }
        }
        oprsum++;
        if(a[1] == 1) {
            for(int i = 1; i <= 2 * n; i += 2)
                opr[oprsum][i] = 1, opr[oprsum][i + 1] = 2;
        }
        else {
            opr[oprsum][1] = 1, opr[oprsum][2 * n] = 2;
            for(int i = 2; i < 2 * n; i += 2)
                opr[oprsum][i] = 1, opr[oprsum][i + 1] = 2;
            oprsum++;
            for(int i = 1; i <= 2 * n; i += 2)
                opr[oprsum][i] = 1, opr[oprsum][i + 1] = 2;
        }
        printf("%d\n", oprsum);
        for(int i = 1; i <= oprsum; i++) {
            for(int j = 1; j <= 2 * n; j++) {
                printf("%c", opr[i][j] == 1 ? '(' : ')');
            }
            printf("\n");
        }
    }
    return 0;
}
```

---

