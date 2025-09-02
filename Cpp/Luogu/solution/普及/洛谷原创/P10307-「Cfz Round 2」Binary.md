# 「Cfz Round 2」Binary

## 题目描述

给定 $n + 1$ 个整数 $a_0\dots a_n$。

对于整数 $u$，设它在二进制下为 $1$ 的位分别为 $k_1, k_2\dots k_m$，那么它的权值 $f(u) = a_{k_1} \oplus a_{k_2} \oplus \dots \oplus a_{k_m}$。此处的二进制位的编号从右到左，依次为 $0,1,2\dots$。其中 $\oplus$ 表示 [按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fromModule=search-result_lemma-recommend) 符号。

你想要知道有多少个 $0 \leq u \leq 2^n - 1$ 使得 $f(u) = f(u + 1)$。为了方便，请你用 **二进制形式** 输出答案（不取模）。

请注意：输出不能包含前导 $0$，除非答案为 $0$。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，

- $(0)_{10} = (0)_{2}$，所以 $f(0) = 0$；
- $(1)_{10} = (1)_{2}$，所以 $f(1) = a_0 = 0$；
- $(2)_{10} = (10)_{2}$，所以 $f(2) = a_1 = 1$；
- $(3)_{10} = (11)_{2}$，所以 $f(3) = a_0 \oplus a_1 = 0 \oplus 1 = 1$；
- $(4)_{10} = (100)_{2}$，所以 $f(4) = a_2 = 2$。

这其中有 $f(0) = f(1)$，$f(2) = f(3)$，所以输出 $(2)_{10} = (10)_{2}$。

#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \leq T \leq 10^3$，$1 \leq n \leq 2\times 10^5$，$\sum n \leq 6\times 10^5$，$0 \leq a_i \leq 2^{30} - 1$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
5
2
0 1 2
3
1 3 3 1
4
2 2 5 4 2
5
7 0 3 4 0 1
6
5 2 1 8 6 0 9```

### 输出

```
10
1
100
11
0```

# 题解

## 作者：szh_AK_all (赞：14)

这题挺巧妙的。

### 分析
可以想想，对于一个数 $x$，$x+1$ 在什么情况下会对答案产生贡献？假设在二进制下 $x+1$ 在 $x$ 的基础上产生了 $k$ 个进位，也就是说 $x$ 在二进制下第 $0,1,\dots,k-1$ 位都由 $1$ 变为了 $0$，而第 $k$ 位则由 $0$ 变为了 $1$，而其他位则不变。那么，也就是说，当 $a_0⊕a_1⊕\dots a_k-1=a_k$ 时，会对答案产生贡献。

所以，可以枚举进位个数 $i$，若 $a_0⊕a_1⊕\dots a_{i-1}=a_i$，则答案会增加。那么会增加多少呢？用排列组合的思想，即在 $n$ 位下已经确定了 $i+1$ 位的数字个数，也就是对于第 $i+2,i+3,\dots n$ 位来说，可以有两种选择：该位为 $0$ 或者 $1$，所以这样的数字个数为 $2^{n-(i+1)}$。由于题目要求用二进制的形式输出答案，所以在用二进制存储答案的数组的第 $n-(i+1)$ 设为 $1$ 即可。

还需注意判断边界，即 $i=0$ 或 $i=n$ 的情况，若它们满足条件，则各自会产生 $1$ 的贡献，即答案的第 $0$ 位增加 $1$。由于第 $0$ 位可能会增加两个 $1$，所以要处理下进位。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
int k[200005];//记录答案
int qian[200005];

int qpow(int a, int b) {//没用，就当做防抄袭吧
	int ans = 1;
	while (b) {
		if (b & 1)
			ans *= a;
		a *= a;
		b /= 2;
	}
	return ans;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n + 1; i++) {
			scanf("%d", &a[i]);
			qian[i] = qian[i - 1] ^ a[i];
		}
		for (int i = 0; i < n; i++) {
			if (i == 0 && a[1] == 0)
				k[n - 1]++;
			else if (i != 0) {
				if (qian[i] == a[i + 1])
					k[n - (i + 1)]++;
			}
		}
		if (qian[n] == a[n + 1])
			k[0]++;
		for (int i = 0; i <= n; i++) {
			k[i + 1] += k[i] / 2;
			k[i] %= 2;
		}
		int tot = n;
		while (tot > 0 && k[tot] == 0)
			tot--;
		for (int i = tot; i >= 0; i--) {
			cout << k[i];
			k[i] = 0;//记得清空
		}
		cout << endl;
	}
}
```

---

## 作者：_buzhidao_ (赞：3)

[题面传送门](/problem/P10307)
# 题目分析
## 题目转化
给定 $n+1$ 个非负整数 $a_0...a_n$。

已知非负整数 $u(0\le u\le 2^n-1)$ 用二进制表示时的第 $i$ 位为 $k_i$。

定义 $f(u)=k_1a_{k_1}\oplus k_2a_{k_2}\oplus...\oplus k_na_{k_n}$。

求满足 $f(u)=f(u+1)$ 的 $u$ 的数量，并用二进制输出。
### 分析
> 这篇题解中，$i$ 均满足 $(u)_2$ 的后 $i$ 位均为 $1$ 且从后往前数的第 $i+1$ 位为 $0$。

易证若 $(u)_2$ 的后 $i$ 位为 $1$，从后往前数第 $i+1$ 位为 $0$，则 $(u+1)_2$ 的后 $i$ 位为 $0$，从后往前第 $i+1$ 位为 $1$。

> 举例：若 $(u)_2=10010111$，则 $i=3$，$(u+1)_2=10011000$，成立。

所以若 $f(u)=f(u+1)$，则 $1\times a_{k_1}\oplus 1\times a_{k_2}\oplus...\oplus 1\times a_{k_i}\oplus0\times a_{k_{i+1}}...\oplus 1\times a_{k_n}=0\times a_{k_1}\oplus 0\times a_{k_2}\oplus...\oplus 0\times a_{k_i}\oplus1\times a_{k_{i+1}}...\oplus 1\times a_{k_n}$ 即 $a_1\oplus a_2\oplus...\oplus a_i\oplus...\oplus a_n=a_{i+1}\oplus...\oplus a_n$。

所以若 $f(u)=f(u+1)$，则 $a_1\oplus a_2\oplus...\oplus a_i=a_{i+1}$。其中，$i$ 表示 $(u)_2$ 最后 $i$ 位均为 $1$ 而从后往前第 $i+1$ 位为 $0$。
# 解题思路
我们要在序列 $a$ 中寻找满足 $a_1\oplus a_2\oplus...\oplus a_i=a_{i+1}$ 的 $i$ 的个数。

但是，一个 $i$ 可能会对应多个 $u$ 值。因为 $i$ 表示 $(u)_2$ **最后 $i$ 位均为 $1$**，从后往前第 $i+1$ 位为 $0$，而没有规定其他位的值。

因为 $0\le u\le 2^n-1$，所以 $(u)_2$ 的最大位数是 $n-1$。如果 $(u)_2$ 的最后 $i$ 位均为 $1$，而第 $i+1$ 位为 $0$，那么 $(u)_2$ 就有 $n-(i+1)=n-i-2$ 位可以是**任意值**。这样的话，若 $a_1\oplus a_2\oplus...\oplus a_i=a_{i+1}$，则会有 $2^{n-i-2}$ 个 $u$ 满足 $f(u)=f(u+1)$。

但是，如果 $i$ 为 $n-1$（即 $u=2^n-1$），$n-i-2$ 的值是 $-1$，$2^{n-i-2}=\frac{1}{2}$ 不再是整数。但是在这种情况下，$u+1$ 的值为 $2^n$。若 $a_1\oplus a_2\oplus...\oplus a_{n-1}=a_n$，仍有一种情况。所以，我们需要特判。

> 此时，不需要额外的二进制位来存储 $(u)_2$ 从后往前第 $i+1$ 位的 $0$，所以固定位数变成 $i$，空余位数为 $0$，情况数变成 $2^0=1$，仍为整数。

由于题目要求我们用**二进制**输出，但是这个二进制数会很长。所以，我们考虑建立一个 `bool` 数组，倒过来存放答案。数组的第 $0$ 位代表 $i=n-1$ 时是否可行。

建立一个变量 $\text{tmp}$，代表 $a_1\oplus a_2\oplus...\oplus a_{i}$。若 $\text{tmp}=a_{i+1}$，则将 `bool` 数组的第 $n-i-1$ 位替换为 $1$。

最后需要把数组第 $0$ 位加到数组中，再去除前导零并输出。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x){//快读
	x=0;int f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
int t,n,s[200005],tmp;
bool ans[200005],fl;
int main(){
	read(t);
	for(;t--;){
		read(n);tmp=0;
		for(int i=0;i<=n;++i) read(s[i]);
		for(int i=0;i<=n;++i){//计算答案
			if(tmp==s[i]) ans[n-i]=1;
			tmp^=s[i];
		}
		fl=0;
		if(ans[0]){//特判
		    for(int i=1;i<=n+1;++i){
		        if(!ans[i]){
		            ans[i]=1;break;
		        }
		        ans[i]=0;
		    }
		}
		for(int i=n+1;i>0;--i){//输出
			if(ans[i]) fl=1;//去除前导零
			if(fl) cout<<ans[i];
			ans[i]=0;//多测不清空，爆零两行泪
		}ans[0]=0;//同上，很容易遗漏
		if(!fl) cout<<0;//特判答案为零的情况
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路

如果 $f(u)=f(u+1)$ 那么 $u$ 一定是一个末尾有很多的 $1$。设末尾的第一个 $0$ 的位置为 $k$，则 $a_0\oplus a_1\oplus a_2\oplus \dots \oplus a_{k-1}=a_{k}$。

对末尾有 $k$ 个 $1$ 的数全排列，共有 $2^{n-k-1}$ 种方按。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int a[N],f[N],ans[N*2];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        int l=0;
        for(int i=0;i<=n;i++)
        {
            cin>>a[i];
            if(i==0)//对第0位分类讨论
            {
                f[i]=a[i];//f数组记录异或前缀和
                if(a[i]==0)//是0时相当于和异或前缀和相同
                {
                    int p=n-i-1;
                    if(p<0)p=0;
                    ans[p]++;
                    int c=p;
                    while(ans[c]>=2)//进位
                    {
                        ans[c]-=2;
                        ans[++c]++;
                    }
                    l=max(c,l);
                }
            }
            else
            {
                f[i]=f[i-1]^a[i];
                if(f[i-1]==a[i])
                {
                    int p=n-i-1;
                    if(p<0)p=0;
                    ans[p]++;
                    int c=p;
                    while(ans[c]>=2)
                    {
                        ans[c]-=2;
                        ans[++c]++;
                    }
                    l=max(c,l);
                }
            }
        }
        for(int i=l;i>=0;i--)//因为存储时从右到左，所以输出时倒序输出
        {
            cout<<ans[i];
            ans[i]=0;
        }
        cout<<'\n';
    }
    return 0;
}

```

---

## 作者：Wing_ (赞：1)

# P10307 题解
## 题目大意
给定 $n+1$ 个整数 $a_0 \ldots a_n$。对于整数 $u$，定义它的权值 $f(u)$ 为它的**二进制**表示中为 $1$ 的位的 $a$ 的异或和（举例见下图）。

![举例](https://cdn.luogu.com.cn/upload/image_hosting/utf4q6g5.png)

输出有多少个 $0\le u\le 2^n-1$（即 **$u$ 的二进制位数为 $n$，分别是第 $0\sim n-1$ 位**）使得 $f(u)=f(u+1)$，用**二进制**形式输出答案，**不取模**，**不含前导 $0$**。
## 题目分析
由于这个题目和二进制有关，我们可以先比较一下 $u$ 和 $u+1$ 的二进制，如图。

![u和u+1](https://cdn.luogu.com.cn/upload/image_hosting/ijikedho.png)

自己随便列举几个数后，可发现上图规律：一个数 $u$（**二进制**表示下）长度为 $n$，其从右向左依次是第 $0\sim n-1$ 位，设从右数第一个 $0$ 的位置为 $k$，则 $u$ 和 $u+1$ 的第 $k+1\sim n-1$ 位相同，第 $0\sim k$ 位相反。

由此可知 $u$ 和 $u+1$ 的第 $k+1\sim n-1$ 位的异或和必然相等，又由于异或满足**结合律**，那么当找到一个 $k$，满足 $a_0\bigoplus a_1\bigoplus\cdots\bigoplus a_{k-1}=a_k$ 时，此时只需令 $u$ 的第 $k$ 位为 $0$，第 $0\sim k-1$ 位为 $1$，第 $k+1\sim n-1$ 位随便取，都会有 $f(u)=f(u+1)$，有 $2^{n-k-1}$ 种方案（$(n-1)-(k+1)+1=n-1-k-1+1=n-k-1$）。

此时用二进制输出答案的优越性就体现出来了，只需**将答案数组的第 $n-k-1$ 位设为 $1$** 即可，但仍有一种**特殊情况**需要处理（接下来会讲到）。

我采用循环的方式实现。$k$ 从 $0$ 循环到 $n-1$，用 $res$ 记录当前异或和。循环完后，还剩下上面说的一种特殊情况：$a_0\bigoplus a_1\bigoplus\cdots\bigoplus a_{n-1}=a_n$，此时 $k=n$，带入 $n-k-1$ 结果为 $-1$，不合题意，故需单独处理。可以发现此时只有 $u$ 的 $0\sim n-1$ 位都是 $1$，即 $u=2^n-1$ 这一种情况，所以在循环结束后判断前 $n-1$ 个 $a$ 的异或和是否等于 $a_n$，若等于，则用**高精度加法**的方式给答案数组加上 $1$ 即可（别忘了是**逢二进一**）。

没有学过高精度的朋友请看这题 [P1601 A+B Problem（高精）](https://www.luogu.com.cn/problem/P1601)。

## 代码
上代码吧，讲得不明白的地方都在注释里了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N], b[N];//b是答案数组 
int T, n;
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i = 0; i <= n; i++) scanf("%d",&a[i]);
		int res=0;//一开始k为0,0~k-1不存在，故异或和初始化为0 
		for (int k = 0; k < n; k++)
		{
			/*
			先判断后更新res的原因：
			我们是循环枚举的k，更新前的res存储的恰好是0~k-1的异或和
			直接判断即可 
			*/
			if (res==a[k]) b[n-k-1]=1;
			else b[n-k-1]=0;
			res^=a[k];
		}
		//循环完res中存储了0~n-1的异或和 
		if (res==a[n])
		{
			//二进制高精度的+1 
			int tmp=1;
			for (int i = 0; i <= n; i++)
			{
				tmp+=b[i];
				b[i]=tmp&1;//位运算，&1相当于%2 
				tmp>>=1;//>>1相当于/2 
			}
		}
		int k = n;
		while (k>=0&&!b[k]) k--;//去前导0 
		if (k<0) printf("0\n");
		else
		{
			for (int i = k; i >= 0; i--) printf("%d",b[i]);//倒序输出！ 
			printf("\n");
		}
		for (int i = 0; i <= n; i++) b[i]=0;//多测要清空！（最好别用memset因为慢QWQ） 
	}
	return 0;
}
```

有不明白的地方或不足欢迎评论区指出，谢谢！

---

## 作者：4041nofoundGeoge (赞：0)

题目看起来很毒瘤，实则挺简单的。

## 思路

题目中描述：
> 给定 $n + 1$ 个整数 $a_0\dots a_n$。
> 对于整数 $u$，设它在二进制下为 $1$ 的位分别为 $k_1, k_2\dots k_m$，那么它的权值 $f(u) = a_{k_1} \oplus a_{k_2} \oplus \dots \oplus a_{k_m}$。此处的二进制位的编号从右到左，依次为 $0,1,2\dots$。其中 $\oplus$ 表示按位异或符号。
> 你想要知道有多少个 $0 \leq u \leq 2^n - 1$ 使得 $f(u) = f(u + 1)$。为了方便，请你用 **二进制形式** 输出答案（不取模）。

什么意思呢？就是说有一个函数 $f(x)$ 表示的是在整数 $x$ 的二进制表示下，为 $1$ 的位置有几个数位，分别异或得到一个函数值，题目要问 $f(u)=f(u+1)$ 有几个满足条件，答案以二进制写出。

理解题意就很简单了！我们根据题意不难发现（产生贡献为 $1$ 否则为 $0$，就可以想到异或，设这个数为 $P_x$）：
$$
\bigoplus^{x-1}_{i=0}P_i
$$
这个式子还可以写成：
$$
P_0\oplus P_1\oplus\cdots P_{x-1}
$$

通过 $f(u) = f(u + 1)$ 可以得知边界条件 $P_0=0$。然后我们就可以写代码了。

### 注意事项

1. 要用**二进制高精度**写代码。
2. 代码中要用到前缀和的思想（代码中的 `sum[i]=sum[i - 1]^a[i]`）。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200005;
int a[MAXN],k[MAXN];
int sum[MAXN];
int read()//快读
{
    int k=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
    return k*f;
}
void print(int x)//快输出
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else print(x/10),putchar(x%10+'0');
}
int main() {
	int t;
	t=read();
	while (t--) {
		int n;
		n=read();
		for (int i = 1; i <= n + 1; i++) {
			a[i]=read();
			sum[i]=sum[i - 1]^a[i];//前缀异或
		}
		for (int i = 0; i < n; i++) {
			if(i==0&&a[1]==0)k[n - 1]++;
			else if(i){
				if (sum[i]==a[i+1])k[n-(i+1)]++;
			}
		}
		if (sum[n]==a[n+1])k[0]++;
		for (int i = 0; i <= n; i++) {
			k[i+1]+=k[i]/2;
			k[i]%=2;
		}
		int m=n;
		while (m>0&&k[m]==0)m--;
		for (int i = m; i >= 0; i--) {
			print(k[i]);
			k[i]=0;
		}
		puts("");
	}
}
```

---

## 作者：liguangjun2023 (赞：0)

###### 算法分析
设  $u$  的右边有  $k$  个连续的  $1$ ，则满足 $ f(u)=f(u+1) $，总共有 $2^{n-k-1}$ 个数，即如果满足条件： $a_{0}\oplus a_{1}\oplus \dots \oplus a_{k-1}=a_{k}$, 有 $2^{n-k-1}$ 个数字。

枚举数列的每个数，如果当前值等于异或前缀和则有 $2^{n-k-1}$ 个数，利用数组统计每个位的结果数量。

输出结果要求为二进制表示，需要把结果中不同位进行进位处理，并且去掉前导  $0$  。


---


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,a[N],ans[N]; 

int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		for(int j=0;j<=n;j++){
			cin>>a[j];
		}
		int nm=0;
		// 遍历每一位，计算满足条件的数字数量 
		for(int j=0;j<n;j++){
			if(a[j]==nm){
				ans[n-j-1]+=1;			
			}
			nm^=a[j];			
		}
		// 特判最后一位 
		if(a[n]==nm){
			ans[0]+=1;
		}
		// 处理进位 
		for(int j=0;j<=n;j++){			
			ans[j+1]+=ans[j]/2; 
			ans[j]%=2;
		}
		// 删除前导 0		
		int p=n;
		while(ans[p]==0) p-=1;
		// 输出结果 
		if(p<0){
			cout<<0;
		}else
			while(p>=0)	cout<<ans[p--];			
		
		cout<<endl;
		memset(ans,0,sizeof(ans));		
	}
	return 0;
}
```

---

## 作者：vorDeal (赞：0)

~~Cfz Rounds 每场都出 Ad-hoc 异或题，干脆改名叫 Xor Rounds 好了。~~

观察到 $\sum n \leq 6 \times 10^5$，暴力是过不了的。

观察发现：对于一个自然数，将之加 $1$，则从某一位开始，它的二进制表示变化，该位变为 $1$，其后所有位变为 $0$。这是一个重要的结论。

记事件 $A_x$ 表示 $\bigoplus\limits_{i=0}^{x-1}=a_x$，特殊地，我们记 $A_0$ 为 $a_0=0$。由上述规律，事件 $A_x$ 的每次发生，都使得 $f(u)=f(u+1)$。

由于 $0 \leq u \leq 2^n-1$，考虑先计算事件 $A_0 \sim A_{n-1}$ 对答案的贡献，再特判事件 $A_n$ 的贡献。发现在所求区间内，事件 $A_x (0 \leq x \leq n-1)$ 如果发生，对答案的贡献为 $2^{n-i-1}$，而事件 $A_n$ 如果发生，贡献为 $1$。

使用二进制高精计算答案即可。

**AC Code：**
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

int t, n;
unsigned long long a[maxn], sum;
vector<int> ans;
bool flag;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i <= n; i++)
            cin >> a[i];
        sum = 0LL, ans.clear(), flag = false;
        for (int i = 0; i < n; i++)
        {
            if (sum == a[i])
                ans.push_back(1), flag = true;
            else if (flag)
                ans.push_back(0);
            sum ^= a[i];
        }
        if (!flag)
        {
            cout << (sum == a[n]) << endl;
            continue;
        }
        if (sum == a[n])
            ans.at(ans.size() - 1)++;
        for (int i = ans.size() - 1; i > 0; i--)
            ans.at(i - 1) += (ans.at(i) >> 1), ans.at(i) &= 1;
        if (ans.at(0) >= 2)
            cout << 1, ans.at(0) >>= 1;
        for (int i = 0; i < ans.size(); i++)
            cout << ans.at(i);
        cout << endl;
    }
    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

[statement](https://www.luogu.com.cn/problem/P10307)

## 赛时做法

### 为何按位输出

这启示我们按位考虑。

本文中二进制串的表达为 $b_0...b_n$ 。

设当前 $u$ 的二进制的表达为 $b_0...b_k01111111$（长度为 $n+1$），$+1$ 后则变为 $b_0...b_k10000000$。

到此，你应该能看出规律了吧。

设 $lowbit(u+1)$ 所对应的二进制位为 $b_k$，如果 $b_k$ 位从 $0$  变成 $1$ 的过程中对答案产生贡献，则有 $a_k= a_{k+1}  \ \oplus \ a_{k+2} \ \oplus \ ... \ a_n $，若产生贡献，则令 $d_k=1$，否则 $d_k=0$，这可以 $\Theta(n)$ 解决。

考虑有多少个 $u$ 使 $u$ 的 $b_k$ 位为 $0$，$u+1$ 的 $b_k$ 位为 $1$，记满足条件的 $u$ 的个数为 $s_k$。

打表找规律，$s_0,s_1,s_2,...,s_n=2^0,2^0,2^1,...,2^{n-1}$。

由此，对 $s_n...s_1$ 将 $d_k$ 加入一个字串末尾，最后对 $s_0$，若 $d_0=1$，则把该字串当成二进制串并 $+1$。

## code

```
#include<bits/stdc++.h>
using namespace std;
void slv(){
	int n;
	cin>>n;//cout<<n<<endl;
	int tmp1=0,tmp2=0;
	string ans="0";
	int fl=0;
	for(int i=0;i<=n;i++){
		int x;cin>>x;
		tmp2^=x;
		//cout<<tmp1<<' '<<tmp2<<' '<<i<<endl; 
		if(tmp1==tmp2) {
			if(i!=n) ans+='1';
			if(i==n) fl=1;
		}
		else if(i!=n)ans+='0';
		tmp1^=x;
		tmp2^=x;
	}int len=ans.length();
	//cout<<ans<<endl;
	if(fl){
		for(int i=len-1;i>=0;i--){
			if(ans[i]=='1') ans[i]='0';
			else{
				ans[i]='1';
				break;
			}
		}
	}int a=0;
	for(int i=0;i<len;i++){
		if(ans[i]=='1') a=1;
		if(a) cout<<ans[i];
	}if(!a) cout<<0;
	cout<<endl;
}
int main(){
	int t;cin>>t;
	while(t--) slv();
	return 0;
}
```

---

## 作者：mystic_qwq (赞：0)

闲话：第一次写题解，求通过qwq  
赛时最后几分钟找到了规律。
***
考虑如果 $a_0=0$，会发生什么。也就是 如果两个相邻的数，像这样：
$$\overline{1xx\cdots xx0}\to\overline{1xx\cdots xx1}$$
这对相邻的数  $\oplus$ 起来就是 $0$，在 $\{0,1,\cdots,2^n-1\}$ 里，有 $1/2$ 的数是前面这样的。结合要输出一个长 $n$（算上前导零）的数，很容易想到这便是第一个要输出的数字。

如果 $a_1=a_0$，
$$\overline{1xx\cdots x01}\to\overline{1xx\cdots x10}$$
$1/4$ 的数是这样的（根据乘法原理），这就是第二个要输出的数。

同理，若 $a_2=a_1\oplus a_0$，考虑数字 
$$\overline{1xx\cdots 011}\to\overline{1xx\cdots 100}$$
$1/8$ 的数字是这样的 $\cdots$ 以此类推。

最后就是 $a_n=\oplus_{i=1}^{n-1}$ 的情况了。但这时候发现，只要输出 $n$ 个数，怎么多了一个？这时候便想到（结合了样例），$a_n$ 的情况和 $a_{n-1}$ 的情况对答案的贡献都是 $1$。所以在做题的时候要把答案都记录在数组里，最后处理进位即可。

这里也可以这么想：一共 $2^n$ 个数，每次取一半取一半，最后就只剩下一个了。如果这些数字全是 $0$ , 那还得再提 $1$ 位。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
  //freopen("1.in","r",stdin);
  //freopen("3.out","w",stdout);
  cin.tie(0)->sync_with_stdio(0);
  int sum=0;
  int T,n,a,isp,ans[200001];
  cin>>T;
  while(T--){
    memset(ans,0,sizeof ans);
    cin>>n;
    for(int i=0;i<=n;++i){
      cin>>a;
      if(a==sum) ans[i]=1;//记录答案
      sum^=a;//前缀异或和
    }
    ans[n-1]+=ans[n];//n-1、n对答案贡献都是1
    for(int i=n-1;ans[i]>1;--i)ans[i]=0,++ans[i-1];
    int start=-1;
    for(int i=0;i<n;++i) if(ans[i]){start=i;break;}
    if(start==-1) {cout<<"0\n"; sum=isp=0; continue;}
    for(int i=start;i<n;++i) cout<<ans[i];
    sum=isp=0;
    cout<<'\n';
  }
}
```

---

