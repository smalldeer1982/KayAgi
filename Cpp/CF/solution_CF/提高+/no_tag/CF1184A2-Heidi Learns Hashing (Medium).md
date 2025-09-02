# Heidi Learns Hashing (Medium)

## 题目描述

在学习了多项式哈希之后，Heidi 决定了解一下移位异或哈希。她遇到了这样一个有趣的问题。

给定一个长度为 $n$ 的二进制字符串 $y \in \{0,1\}^n$，求有多少个不同的 $k$（$0 \leq k < n$）满足存在 $x \in \{0,1\}^n$，使得 $y = x \oplus \mbox{shift}^k(x)$。

其中，$\oplus$ 表示按位异或操作，$\mbox{shift}^k$ 表示将一个二进制字符串循环右移 $k$ 位的操作。例如，$001 \oplus 111 = 110$，$\mbox{shift}^3(00010010111000) = 00000010010111$。

## 说明/提示

在第一个样例中：

- $1100\oplus \mbox{shift}^1(1100) = 1010$
- $1000\oplus \mbox{shift}^2(1000) = 1010$
- $0110\oplus \mbox{shift}^3(0110) = 1010$

不存在 $x$ 使得 $x \oplus x = 1010$，因此答案为 $3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1010
```

### 输出

```
3
```

# 题解

## 作者：Alex_Wei (赞：9)

> [题面传送门](https://www.luogu.com.cn/problem/CF1184A2)。

> 题意简述：给定一个长度为 $n$ 的二进制字符串 $y$，求有多少个 $k$ 满足存在一个长度为 $n$ 的二进制字符串 $x$ 使得 $x\oplus\mathrm{shift}^k(x)$。

> - $\oplus$ 为异或运算符。
> - $\mathrm{shift}^k(x)$ 为循环地将 $x$ 向右移动 $k$ 次后的二进制字符串，例如 $\mathrm{shift}^2(0110)=1001$。

非常巧妙的一道数学题。

---

对于每个 $k$，我们假定 $x$ 其中一位（第 $i$ 位）为 $0/1$，则第 $(i+k)\bmod n,\ (i+2k)\bmod n,\cdots$ 也一定能固定下来，最后必定会回到第 $i$ 位，形成一个 “假定环”。显然这样的环有 $\gcd(k,n)$ 个。

例如 $y=1010,\ k=3$，如果我们假定第 $0$ 位（位数从右往左数）为 $0$，则第 $(0+3)\bmod 4=3$ 位必须为 $0$，则第 $(3+3)\bmod 4=2$ 位必须为 $1$，则第 $(2+3)\bmod 4=1$ 位必须为 $1$，则第 $(1+3)\bmod 4=0$ 位必须为 $0$，这与我们一开始假定的第 $0$ 位为 $0$ 相符，故 $0110\oplus\mathrm{shift}^3(0110)=1010$。

当然，有的环无论如何假定，最后推出来的都与假定相违背。认真思考就会发现：**如果一个环上有奇数个 $1$，则这个环一定无法满足要求。**$x\oplus\mathrm{shift}^k(x)$ 的结果中，环上 $1$ 的个数一定为偶数（$1\oplus 1=0$ 抵消掉的是成对的 $1$）。

因为 $\gcd(n,k)$ 最多只有 $2\sqrt n$ 种取值（根据 “试除法”，一个数的因数个数上界为 $2\sqrt n$），所以只需要判断这 $2\sqrt n$ 个取值是否符合要求即可。时间复杂度 $O(n\sqrt n)$。

```cpp
int n,p[N],ans;
string s;
vector <int> f,bc[N];

int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++)if(n%i==0)bc[i].resize(i),f.pb(i);//计算n的因数
	for(int i=0;i<s.size();i++)for(auto it:f)bc[it][i%it]^=s[i]-'0';
	for(auto it:f)for(int j=0;j<it;j++)p[it]|=bc[it][j];//任意一个环不满足要求都不行
	for(int i=1;i<=n;i++)ans+=!p[__gcd(i,n)];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

有意思的简单题。

首先考虑 $k$ 是合法的条件是什么：$y_i=x_i\oplus x_{i+k}$。（那么现在有了一个 $\mathcal{O}(n^2)$ 的 2-SAT 做法）

经典的，$i\rightarrow i+k\rightarrow i+2k\rightarrow \cdots$ 会回到 $i$，并且环的长度是 $n/\gcd(n,k)$。那么一个环是合法的当且仅当环上的 $\bigoplus y_{i+tk}=0$。

因为 $\gcd(n,k)\mid n$，所以最多有 $d(n)$ 个取值，那么我们对于每一个取值暴力就是 $\mathcal{O}(nd(n))$ 的。

注意如果 $y_{1\sim n}=0$，$k=0$ 也是合法的。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

int n,ans[N];
string s;

void bd(int x){
	int f=1;
	for (int i=1; i<=x; i++){
		int xr=0;
		for (int j=i; j<=n; j+=x) xr^=s[j]-'0';
		f&=!xr;
	}
	ans[x]=f;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>s;
	s=" "+s;
	memset(ans,-1,sizeof ans);
	int cnt=0,fl=1;
	for (int i=1; i<=n; i++) fl&=(s[i]=='0');
	for (int i=1; i<n; i++){
		int t=__gcd(i,n);
		if (ans[t]==-1) bd(t);
		cnt+=ans[t];
	}
	cout<<cnt+fl<<"\n";
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题目的格式好像有一个字符串炸了，不过无伤大雅。

题意简述：给定一个长度为 $n$ 的 $01$ 串 $y$。当 $k$ 取 $0$ 到 $n-1$ 时，求有几个 $k$ 能够满足存在一个 $x$ 使得其和 $x$ 循环右移 $k$ 位异或能够得到 $y$。
## 分析。
这个题乍一看没有什么思路，我们不妨从 $x$ 上下手。我们假定存在 $x$ 为 $x_1\ x_2\ x_3\ x_4$。我们令 $k=2$。事实上，我们无论假设的数量和内容对不对，我们的目的是去寻找 $k$ 所以如果能够从中找出规律，我们就可以扩展到一般情况。当 $k=2$ 时，这个 $x$ 的顺序就变成了 $x_2\ x_3\ x_0\ x_1$。如果我们想要得到 $y$ 则有四种情况：$x_0\oplus x_2=y_0$，$x_1\oplus x_3=y_1$，$x_2\oplus x_0=y_2$ 和 $x_3\oplus x_1=y_3$。

显然是一个环，具体来说，就是一个个的圈。当我们假设 $x_0=1$ 时显然根据题目要求，因为 $n$ 和 $k$ 都是定值，所以可以转一圈求出其它的值。如果这样一圈下来，最终得出的 $x_0=1$ 则没有问题。我们扩展到整个数组中去，可以发现，对于任意一个 $k$ 都能存在一个可能的环，也对于 $x$ 可以都转一圈求出来。

因为存在 $x$ 的某一位 $i$ 是 $0$ 或者 $1$ 时，其 $\left(i+j\times k\right)\bmod n$ 位也能被固定下来，所以如果想要转一圈回来，则一定要有 $n$ 长度的距离，又因为每一次走 $k$ 步，所以走的距离就是 $\operatorname{lcm}(k,n)$。那么次数就是 $cnt=\frac{\operatorname{lcm}(k,n)}{k}$ 次。因为每次经过的位置互不相同，所以可以将步长看做是 $\frac{n}{cnt}=\gcd(k,n)$。我们可以发现，因为转着一圈中回到起点时，不能改变我们假设的 $1$ 或者 $0$，所以在这个过程中遇到的 $1$ 或者 $0$ 的个数需要是偶数，因为在题目的要求下，求出的公式因为 $1\oplus1=0$ 所以 $1$ 的个数必定为偶数个才能满足我们的要求。此时算法就很显然了，因为右移是否合法只跟和它有关的最大公约数有关，所以只需要求求出 $\gcd(i,n)$ 即可，没有求过的直接暴力走即可，最后看一下路程是否合法。

不会优化，所以大胆地采用暴力的手段，因为求的个数也就是求最大公约数的过程，所以整个的时间复杂度是没有问题的。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
char y[200005];
int ans,pd,len[200005];
bool vis[200005];
int gcd(int a,int b) {
    return b>0?gcd(b,a%b):a;
}
int main(){
	memset(len,-1,sizeof(len));
	cin>>n>>y;
	for (int i=0;i<=n-1;i++){
		if(y[i]=='1'){
			pd=1;
			break;
		}
	}
	if(!pd){
	    ans++;
	}
	for (int i=1;i<=n-1;i++){
		int sum=gcd(i,n);
		if(len[sum]==-1){
			bool flag=1;
			memset(vis,0,sizeof(vis));
			for (int i=0;i<=n-1;i++){
				if(vis[i]){
					continue;
				}//如果被标记了直接跳过。
				vis[i]=1;
				int y_ps=y[i]-'0',loc=(i+sum)%n;//记录当前的目标和要改变的位置。
				while(!vis[loc]) {
					vis[loc]=1;// 标记走过的位置。
					y_ps^=y[loc]-'0';
					loc=(loc+sum)%n;//到下一个位置上去。
				}
				//cout<<y_ps<<" ywwy\n";
				if(y_ps){
				    len[sum]=0;
				    flag=0;
				    break;
				}//注意这里可能不止有一个不合法或者合法。 
			}
			if(flag==1){
				len[sum]=1;
			}
			//cout<<len[i]<<" 389\n";
		}
		if(len[sum]){
		    ans++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

