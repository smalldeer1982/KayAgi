# [AGC035A] XOR Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc035/tasks/agc035_a

すぬけ君は $ N $ 枚の帽子を持っています。$ i $ 枚目の帽子には整数 $ a_i $ が書かれています。

$ N $ 頭のラクダが円環状に並んでいます。 すぬけ君はそれぞれのラクダに $ 1 $ 枚の帽子を被せようとしています。

どのラクダについても以下の条件が成立するような帽子の被せ方が存在するならば `Yes` を、そうでなければ `No` を出力してください。

- 両隣のラクダが被っている帽子に書かれた数のビットごとの排他的論理和が自身の被っている帽子に書かれた数と等しい
 
ビットごとの排他的論理和について $ n $ 個の非負整数 $ x_1,x_2,\ \ldots,\ x_n $ の排他的論理和 $ x_1\ \oplus\ x_2\ \oplus\ \ldots\ \oplus\ x_n $ は以下のように定義されます。

- $ x_1\ \oplus\ x_2\ \oplus\ \ldots\ \oplus\ x_n $ を二進表記した際の $ 2^k(k\ \geq\ 0) $ の位の数は $ x_1,x_2,\ \ldots,\ x_n $ のうち、二進表記した際の $ 2^k(k\ \geq\ 0) $ の位の数が $ 1 $ となるものの個数が奇数ならば $ 1 $、そうでなければ $ 0 $ となる。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります。

## 说明/提示

### 制約

- 入力は全て整数
- $ 3\ \leq\ N\ \leq\ 10^{5} $
- $ 0\ \leq\ a_i\ \leq\ 10^{9} $

### Sample Explanation 1

\- $ 1,2,3 $ が書かれた帽子を時計回りに被せたとき、どのラクダも問題文中の条件を満たすため、答えは `Yes` となります。

### Sample Explanation 2

\- そのような被せ方は存在しません。よって、答えは `No` となります。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4
1 2 4 8```

### 输出

```
No```

# 题解

## 作者：约瑟夫用脑玩 (赞：3)

这题不看题解的话可能考虑不全，~~如果像我一样一直不看题解也就 WA 个十次~~。

首先是一步众所周知的转化 $a_i=a_{i-1}\oplus a_{i+1}$ 等价于 $a_{i+1}=a_{i-1}\oplus a_i$。

然后一般人都能继续想到 $a_i=a_{i-1}\oplus a_{i-2}$，进而有 $a_{i+1}=a_{i-1}\oplus a_i=a_{i-1}\oplus a_{i-1}\oplus a_{i-2}=a_{i-2}$

也就是说 $\forall i,a_i=a_{i-3}$，这里由于是环下标对 $n$ 取个模均成立。

果断提出猜想：$n\bmod 3=0$，那么你没考虑到 $\forall i,a_i=0$。

令 $c_x$ 为 $x$ 在 $a$ 中的出现次数，特判后再猜想合法当且仅当 $\exists x\neq y\neq z\neq x,x\oplus y=z,c_x=c_y=c_z\neq0\ \land\ \forall t\notin\{x,y,z\},c_t=0$

说人话就是只有三个互不相同的数 $x,y,z$ 出现且出现次数相等，同时满足题目的异或条件。

然后你发现你还是 WA，考虑数据：`3 1 1 0`，你发现当 $x=y,z=0$ 时也成立。

那么最后可能的情况就是：

- $\forall i,a_i=0$
- $\exists x\neq y\neq z\neq x,x\oplus y=z,c_x=c_y=c_z\neq0\ \land\ \forall t\notin\{x,y,z\},c_t=0$
- $\exists x\neq z=0,c_x=2\times c_z\neq0\ \land\ \forall t\notin\{x,z\},c_t=0$

后两种情况用个 map 统计出现个数，然后遍历一下 map 即可判断。

时间复杂度 $O(n\log{n})$，无聊的写哈希表，或者精细实现（指只存三个数）上述过程也可以做到 $O(n)$，~~但我为了方便试错就写了 map~~。

注意情况二要判断是否满足题目的异或条件，即 $x\oplus y=z$！

如上述所说并不优秀的代码：

```
	int i,f=0;
	n=read();for(i=1;i<=n;f|=a[i++]=read());
	if(!f)puts("Yes"),exit(output);
	if((n%3)&&f)puts("No"),exit(output);
	for(i=1;i<=n;i++)
	{
		mp[a[i]]++;
	}
	if(mp.size()==3)
	{
		int lst=0,s=0;
		for(auto to:mp)
		{
			if(lst&&lst^s(to))puts("No"),exit(output);
			lst=s(to);s^=f(to);
		}
		puts(s?"No":"Yes");
	}
	else
	{
		if(mp.size()>3||mp.size()<2||mp.find(0)==mp.end())puts("No"),exit(output);
		int lst=0;
		for(auto to:mp)
		{
			lst=f(to)?s(to):0;
		}
		if(lst^(mp[0]<<1))puts("No"),exit(output);
		puts("Yes");
	}
```

---

## 作者：Alvin0228 (赞：0)

### 题意描述

任意排列 $n$ 个数，问是否存在一个排列，使 $a_{n-1} \oplus a_{n+1}=a_n $。

### 题目分析

因为本题的数据量过大，深搜是过不了的，所以我们应该考虑 $n$ 个数内在的联系。

不难发现，$a_{n}=a_{n-1} \oplus a_{n+1}$ 可以化为 $a_{n-1} \oplus a_{n} \oplus a_{n+1} = 0$。

然后我们发现，任意三个数的异或值为 $0$，也就是对于任意四个数，都满足 $a_{n-1} \oplus a_{n} \oplus a_{n+1} = 0$，$a_{n} \oplus a_{n+1} \oplus a_{n+2} = 0$，所以 $a_{n-1}=a_{n+2}$，即每三个数都相等，因为数据是环状的结构，所以 $n$ 可以被 $3$ 整除。

现在我们考虑上述情况中的特殊例子：

第一种情况是两个数相等，即 $a_n=a_{n+1}$，此时通过计算，可得 $a_{n+2}=0$；

第二种情况是三个数都相等，即 $a_n=a_{n+1}=a_{n+2}=0$，此时发现所有数都是 $0$，所以不用考虑 $n$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005];//记得开 long long。 
int main ()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	long long n=0,x=-1,y=-1,z=-1,xn=0,yn=0,zn=0,t=0;//因为没赋初值 WA了十几次。 
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n);
	x=a[t];//xn,yn,zn是三个数出现的次数，因为最多符合条件的状态只有三个数，所以只计算三个数就行了。 
	for (;t<n;t++)
	{
		if (a[t]!=x) break;
		xn++;
	}
	if (t!=n) y=a[t];
	for (;t<n;t++)
	{
		if (a[t]!=y) break;
		yn++;
	}
	if (t!=n) z=a[t];
	for (;t<n;t++)
	{
		if (a[t]!=z) break;
		zn++;
	}
	if (t==n&&x!=-1&&y!=-1&&z!=-1&&n%3==0&&xn==n/3&&yn==n/3&&zn==n/3)//第一种情况，有且仅有三个不同数，且数量相等，异或值为 0。 
	{
		if ((x^y^z)==0) 
		{
			cout<<"Yes";
			return 0;
		}
	}
	if (t==n&&x!=-1&&y!=-1&&z==-1&&n%3==0)//第二种情况是两个数，有一个为 0。 
	{
		long long n3=n/3;
		if ((xn==n3&&yn==2*n3&&x==0)||(xn==2*n3&&yn==n3&&y==0)) 
		{
			cout<<"Yes";
			return 0;
		}
	} 
	if (t==n&&x==0&&y==-1&&z==-1)//第三种情况是全为 0。 
	{
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
	return 0;
}
```

---

