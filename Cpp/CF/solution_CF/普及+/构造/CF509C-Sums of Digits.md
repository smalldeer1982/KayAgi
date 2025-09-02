# Sums of Digits

## 题目描述

Vasya had a strictly increasing sequence of positive integers $ a_{1} $ , ..., $ a_{n} $ . Vasya used it to build a new sequence $ b_{1} $ , ..., $ b_{n} $ , where $ b_{i} $ is the sum of digits of $ a_{i} $ 's decimal representation. Then sequence $ a_{i} $ got lost and all that remained is sequence $ b_{i} $ .

Vasya wonders what the numbers $ a_{i} $ could be like. Of all the possible options he likes the one sequence with the minimum possible last number $ a_{n} $ . Help Vasya restore the initial sequence.

It is guaranteed that such a sequence always exists.

## 样例 #1

### 输入

```
3
1
2
3
```

### 输出

```
1
2
3
```

## 样例 #2

### 输入

```
3
3
2
1
```

### 输出

```
3
11
100
```

# 题解

## 作者：Silence_water (赞：7)

## CF509C 题解

[题目传送门](https://www.luogu.com.cn/problem/CF509C)

---

### 题目简述

> 定义两个长度为 $n$ 的序列 $a$ 和 $b$，$a$ 序列中元素严格单调递增且均为正整数，$b$ 序列中 $b_i$ 等于 $a_i$ 各个数位上的数之和。现给出 $b$ 序列，要求求出对应 $a$ 序列，并使得 $a_n$ 尽量地小。

---

### 题目分析

构造题。

采用贪心算法。使得 $a_n$ 尽可能的小，首先 $a_1$ 得尽可能的小。显然地，从右往左尽可能多填 $9$，当无法填时将剩余的数填入，这是 $b_1$ 一定时 $a_1$ 最小的填法。

我们将接下来数的填法转换为一个子问题：给定 $x$ 和 $y$，找到最小的使得数 $c$ 使得 $c>y$ 且 $c$ 各数位之和为 $x$。

用类似模拟的方法解决这一问题：

我们从右向左遍历 $y$ 的数字，尝试增加或改变当前数字，使得总和为 $x$。如果我们将从右往左第 $k+1$ 位上的数字增加，那么 $c$ 就已经保证大于 $y$ 了，因此第 $1$ 至 $k$ 位上可以填 $0-9$ 任意一个数字，从而可以使这 $k$ 位数字之和为 $0-9k$ 间的任意数字。

我们对填的数进行分类讨论：

1. $b_i>b_{i-1}$。此时贪心所填得的 $a_i$ 必然比 $a_{i-1}$ 要大。因此直接采用如填 $a_1$ 的方法填 $a_i$ 即可。

2. $b_i\le b_{i-1}$。此时我们需要找到一个位置 $m$，使得 $b_i>b_{i-1}-sum$。$sum$ 指 $a_{i-1}$ 的第 $1$ 至 $m-1$ 位上的数字之和。如图：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/xd6hs5xa.png)

   从而我们可以在第 $1$ 至 $m-1$ 位上填上数字使其总和变为 $res$。此时我们就可以像情况 $1$ 一样贪心地去填了。

   值得注意的是，当 $b_i>b_{i-1}-x$，但 $a_{i-1}$ 的第 $m$ 位上的数字 $p$ 为 $9$ 时，无法再加。此时我们就需要继续向高位找，同时将位上数字为 $9$ 的变为 $0$，直到出现一个数字小于 $9$ 为止。

在填的同时，注意 $a_i$ 的长度随 $i$ 的增大而单调不递减，因此 $len$ 需要在每次处理完后更新。

讲了这么多，还是举个例子说说：

```
input:
2
18
18
output:
99
189
```

$b_1=18$，因此 $a_1$ 最小为 $99$。而 $b_2=b_1$，属于情况 $2$，此时我们只需找到第 $m$ 位使得第 $1$ 至 $m$ 位上的数之和 $>b_{1}-b_{2}=0$。当 $m=2$ 时，发现 $a_1$ 的第 $2$ 位为 $9$，无法再加，因此我们将 $m+1$，发现 $a_1$ 的第 $3$ 位为 $0$，可以加上。因此我们在 $a_2$ 的第 $3$ 位填上一个 $1$，多余的数字等于 $18-(18-18)-1=17$。将 $17$ 贪心地分在 $2$ 个位置上，即为 $89$。因此 $a_2=189$。

再拿第 $2$ 个样例来说：

$b_1=3$，因此 $a_1$ 最小为 $3$。而 $b_2=2<3$，属于情况 $2$。找到第 $2$ 位，填入一个 $1$，剩余数字为 $2-(3-3)-1=1$，填入第 $1$ 位，因此 $a_2=11$。$b_3=1<2$，也属于情况 $2$。第 $1$ 位时 $x=0<1$，第 $2$ 位时 $x=1=1$，而第 $3$ 位时 $x=1+1>1$，因此在第 $3$ 位填入 $1$，剩余数字为 $1-(2-2)-1=0$，无需再补充。

---

### 代码展示

`gota` 函数，用于贪心地求出总和为 $x$ 的最小正整数。注意到代码中 `x-=9-c[++pos]` 这一语句，即使在 $x$ 不够减也没关系，循环结束后的一行 `c[pos]+=x` 可以将减多的 $x$ 通过减少 $c[pos]$ 来弥补。

```cpp
void gota(int x)
{
	int pos=0;
	while(x>0)
	{
		x-=9-c[++pos];
		c[pos]=9;
	}
	c[pos]+=x;
	if(pos>len)len=pos;
}
```

核心求解部分。解释写在代码中应该更清晰一点。

```cpp
for(int i=2;i<=n;i++)
{
	if(b[i]>b[i-1])// 情况一
		gota(b[i]-b[i-1]);
	else// 情况二
	{
		int dis=b[i]-b[i-1],pos=1;
      // 用dis表示差距，这需要通过把位上的数变为0来缩小。
		while(dis<=0||c[pos]==9)// 注意 dis>0 时也需满足 c[pos]!=9
			dis+=c[pos],c[pos++]=0;
		c[pos]++;// 在找到的位置+1
		gota(dis-1);// -1是因为上一行的+1
		if(pos>len)len=pos;
	}
	print(len);
}
```

---

### 总结

本题的讲解就到此结束了，语言措辞可能有些含糊，表述方式可能会有错误，如有疑问请您指正，谢谢。

---

## 作者：太阳起晚了呢 (赞：2)

## 解

显然答案是唯一的

这说明我们可以找到一些策略，使得答案唯一。 ~~废话~~

记 $c_i$ 为当前 $a_i$ 的第 $i$ 位数字 

那么从 $b_1$ 开始，我们需要找到一个最小的 $a_1$。

贪心策略显然，我们从第一位开始往后每一位都填上 $9$ 如果不够填就把剩下的填进去，这样一定能获得一个最小的 $a_1$。

~~证明略~~

那么考虑在限制了原序列单调递增的情况下，确保每一个 $a_i$ 最小，对于 $a_n$ 最小是不劣的，那么我们考虑已知 $a_{i-1}$ 和 $b_i,b_{i-1}$ 的情况下如何求出一个最小的 $a_i$。

分类讨论

（我们先把 $a_{i-1}$ 填充到 $a_i$）

如果 $\large b_i > b_{i-1}$ 

那么我们只需要像构造 $a_1$ 一样，往 $a_{i-1}$ 中一个一个填充 $9$ 就可以了。

如果 $\large b_i=b_{i-1}$ 

那么我们根据数位从小往大找到第一个不为 $9$ 的数位记作 $x$，给那一位数字加一，然后对于 $\large \sum_{i=1}^{x-1} c_i$ 以及这些位重复做上述贪心策略，即将 $x-1$ 位前的所有数位重构。

此处可以提前求一下前缀和。

如果 $\large b_i<b_{i-1}$

那么我们就需要对一些数位上的数重构，根据贪心的原则，在相同策略下数位和越小最后的数就越小，这意味着如果我们对于 $a_{i-1}$ 的部分连续数位为了减小数位和而贪心重构就一定会使这个数变小，那么我们需要找到一个在这段连续数位之后的数位进行加一，于是我们记 $delta=b_{i-1}-b_i$ 那么只需要在前缀和数组 $s$ 中 ``upper_bound`` 一下就可以了，注意加一的位置不能是 $9$ ，还要往前找第一个不是 $9$ 的位置。

每次都如上操作一定是最优的。

本题结束 注意数组开大

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=605;
int n;
int lst=0,lstl;
int c[maxn],s[maxn],r[maxn],t[maxn];
void st(int (&a)[maxn],int sum,int &l)
{
    int p=0;
    while(sum>0)
        sum-=9-a[++p],a[p]=9;
    a[p]+=sum;
    l=p;
}
void update(int sum,int l)
{
    lstl=l;
    s[0]=0;
    for(int i=1;i<=l+5;i++) c[i]=r[i],s[i]=s[i-1]+r[i];
    lst=sum;
}
int main()
{
    scanf("%d",&n);
   	while(n--)
    {
        int sum;scanf("%d",&sum);
        int l;
        for(int i=1;i<=lstl;i++) r[i]=c[i];l=lstl;
        if(sum>lst)
        {
            st(r,sum-lst,l);l=max(l,lstl);
            for(int i=l;i>=1;i--) printf("%d",r[i]);
            putchar('\n');
            update(sum,l); 
        }
        else
        {
            for(int i=1;i<=lstl;i++) r[i]=c[i];l=lstl;
            //cout<<s[1]<<endl;
            int x=upper_bound(s+1,s+1+lstl,lst-sum)-s;
            //cout<<x<<endl;
            for(int i=1;i<=x;i++) r[i]=0;
            
            x+=1; while(r[x]==9) x++; 
            r[x]+=1;
            //cout<<x<<endl;
            //cout<<s[x]<<endl;
			int lft=sum-(lst-s[x-1])-1;
			//cout<<lft<<endl;
            if(x>l) l=x;
            int tl;
            memset(t,0,sizeof t);
            st(t,lft,tl);
            for(int i=1;i<=x-1;i++) r[i]=t[i];
            for(int i=l;i>=1;i--) printf("%d",r[i]);
            putchar('\n');
            update(sum,l);
        }
    }
    return 0;
}
```

---

## 作者：CarroT1212 (赞：1)

### 题目大意

给定长度为 $n$ 的序列 $b$，请你求出一个长度为 $n$ 的序列 $a$，使得对于每一个整数 $i\,(1 \le i \le n)$，$a_i$ 各数位数字之和恰好等于 $b_i$，且 $a$ 严格递增，$a_n$ 尽可能小。（$1 \le n \le 300$，$1 \le b_i \le 300$）

### 解法分析

让最后一位尽量小显然就是让每一位都尽量小。

设 $a_{i,j}$ 为 $a_i$ 中第 $j$ 位数的值（个位为第 $1$ 位，十位为第 $2$ 位，以此类推），令 $a_0=0$。

首先把“$a$ 严格递增”这个条件转化一下，变为“对于每一个整数 $i\,(1 \le i\le n)$，存在一个整数 $j$ 使得 $a_{i,j}>a_{i-1,j}$，且对于每一个 $k\,(k>j)$，$a_{i,k}=a_{i-1,k}$”。也就是说，我们想根据 $a_{i-1}$ 得到 $a_i$，就必须保证 $a_i$ 中有某一位是大于 $a_{i-1}$ 的，而且 $a_i$ 高于它的数位都要与 $a_{i-1}$ 相等，低于它的数位没有限制。于是求 $a_i$ 时，我们可以枚举大于 $a_i$ 的这一位在哪，显然位数越低答案越优。

到这里就只有数位之和等于 $b_i$ 的条件需要考虑了。设枚举到的大于 $a_{i-1}$ 的是第 $j$ 位，则需要同时满足两种极限情况才存在符合条件的 $a_i$：即使 $1\sim j-1$ 位全部填 $0$，第 $j$ 位填 $a_{i-1,j}+1$，后面的数位跟 $a_i$ 相同，$a_i$ 的数位之和也不大于 $b_i$；即使 $1\sim j$ 位全部填 $9$，后面的数位跟 $a_i$ 相同，$a_i$ 的数位之和也不小于 $b_i$。这些判断可以通过预处理出 $a_{i-1}$ 的数位和实现。如果两个要求都满足，就可以开始构造 $a_i$ 了。$j$ 后面的数位跟 $a_{i-1}$ 相同，$a_{i,j}$ 优先填 $a_{i-1,j}+1$，然后贪心地填前面的数位，也就是从小往大填，每一位都尽量多填，填到 $9$ 了就换下一位。如果前面的数位都填完了还是塞不下 $b_i$，则就把没塞下的部分扔到第 $j$ 位去。这样我们就求出了最小的 $a_i$，跳出枚举即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const int N=10007;
int n,b[N],str[307][N],len[307];
int main() {
	scanf("%d",&n);
	len[0]=1;
	for (int i=1;i<=n;i++) {
		scanf("%d",&b[i]);
		int sum=0;
		for (int j=1;j<=len[i-1];j++) sum+=str[i-1][j];
		for (int j=1;;j++) {
			sum-=str[i-1][j];
			if (str[i-1][j]!=9) {
				if (sum+str[i-1][j]+1<=b[i]&&b[i]<=sum+9*j) {
					len[i]=max(len[i-1],j);
					for (int k=j+1;k<=len[i-1];k++) str[i][k]=str[i-1][k];
					str[i][j]=max(str[i-1][j]+1,b[i]-sum-9*(j-1));
					int cnt=b[i]-sum-str[i][j];
					for (int k=1;cnt>0;k++,cnt-=9) str[i][k]=min(cnt,9);
					break;
				}
			}
		}
		for (int j=len[i];j;printf("%d",str[i][j--]));
		printf("\n");
	}
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

一道很好的构造题。简单来说，给你一个序列 $\{b\}$，$b_i$ 表示 $a_i$ 各位数字之和，请还原出序列 $\{a\}$。有两个附加条件，一是序列 $\{a\}$ 单增，二是 $\{a\}$ 尽可能的小。

对于第二个条件，很容易想到要贪心求解。倘若没有第一个条件，那么显然 $b_i = 9a+b(0<b<9)$ 的形式是最优的，即还原出的数形如 $b99\cdots9$。那么有第一个条件时，不难想到根据 $b_{i - 1}$ 与 $b_i$ 的大小进行分类讨论。

- 先从 $b_{i - 1} < b_i$ 这种简单的情况看起。相较于前一个数，只需要把多的部分 $b_i - b_{i - 1}$ 按照贪心的思想去填入即可。举个栗子，如果 $a_{i - 1} = 129$，多出了 $8$ 需要填，那么在 $2$ 上加上 $7$ 补成最大的上限 $9$，然后将剩余的 $8 - 7 = 1$ 填入 $1$，最后变成了 $299$。

- 再来看 $b_{i - 1} \ge b_i$ 的情况。从低位往高位找到第一个不是 $9$ 的位置，尝试将该位加 $1$，往高位的方向均不变，往低位的方向重新排列。这里需要注意是否合法（也就是剩余数字之和在减去那些已经确定的数后是否大于**等于** $0$）。当然，往低位的方向的排列方式直接按照贪心的思路即可。若位数不够，则需要补 $0$，这也是为什么之前判断合法时只需要满足大于等于 $0$ 即可。如果全部遍历完也未出现可以填的，那么只能新开一位并填上 $1$，然后剩下的按照贪心的思路即可。

在编写代码的时候，分类三种构造的函数。第一种是无条件限制，直接贪心填入。第二种是弱依赖，即需要补充多的部分的第一种情况。第三种便是需要较大改动的第二种情况，其中按照贪心进行填入的部分直接调用第一个函数即可。

完整代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,a[MAX];
string ans[MAX];
string easy_make (int x);
string medium_make (string la,int x);
string hard_make (string la,int x);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	for (int i = 1;i <= n;++i) a[i] = read ();
	for (int i = 1;i <= n;++i)
	{
		if (i == 1) ans[i] = easy_make (a[i]);
		else if (a[i] > a[i - 1]) ans[i] = medium_make (ans[i - 1],a[i]);
		else ans[i] = hard_make (ans[i - 1],a[i]);
	}
	for (int i = 1;i <= n;++i) cout<<ans[i]<<endl;
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
string easy_make (int x)//直接贪心填入
{
	string s = "";
	for (int i = 1;i <= x / 9;++i) s += '9';
	x %= 9;
	if (x) s = char (x + 48) + s;
	return s;
}
string medium_make (string la,int x)
{
	int len = la.size ();int sum = x;
	string s = "";
	for (int i = 0;i < len;++i) sum -= la[i] - '0';
	for (int i = len - 1;~i;--i)
	{
		if (!sum) s = la[i] + s;
		else s = char (la[i] + min (9 - (la[i] - '0'),sum)) + s,sum -= min (9 - (la[i] - '0'),sum);//尽量凑成 9
	}
	return easy_make (sum) + s;
}
string hard_make (string la,int x)
{
	int len = la.size ();
	for (int i = len - 1;~i;--i)
	{
		if (la[i] != '9')
		{
			string s = "";int sum = 0;
			for (int j = 0;j < i;++j) s += la[j],sum += la[j] - '0';
			s += char (la[i] + 1);sum += la[i] - '0' + 1;
			if (x - sum < 0) continue;//要合法才行
			string nw = easy_make (x - sum);
			int p = len - s.size () - nw.size ();
			for (int j = 1;j <= p;++j) s += '0';//补 0 保证 ans_i 单调递增
			return s + nw; 
		}
	}
	string s = "1";++len;//直接新开一位
	string nw = easy_make (x - 1);
	int p = len - s.size () - nw.size ();
	for (int i = 1;i <= p;++i) s += '0';//补 0 保证 ans_i 单调递增 
	return s + nw; 
}
```

---

## 作者：Hadtsti (赞：0)

### 题意简述

设 $f(x)$ 为正整数 $x$ 各数位上数字之和。给出长为 $n$ 的正整数序列 $b_i$。要求构造正整数序列 $a_1,a_2,\cdots,a_n$，满足：

- $\forall 1\le i\le n,f(a_i)=b_i$

- $\forall 1\le i<n,a_{i+1}>a_i$

- $a_n$ 最小。

### 题目分析

我们先让 $a_1$ 最小，再在 $f(a_2)=b_2$ 的基础上找到 $>a_1$ 的最小 $a_2$ 一定是所有情况中最小的。类似地，当我们计算出最小的 $a_i$ 后，我们只需要找到 $f(a_{i+1})=b_{i+1}$ 且 $>a_i$ 的最小 $a_{i+1}$ 也一定是所有情况中最小的。

所以我们实际上需要实现这样一个函数 $calc(x,y)$，表示所有数位上数字和为 $x$，且 $>y$ 的最小数。这是一个比较简单的数位 DP。

具体地，把 $y$ 按数位倒着考虑，依次固定前 $i-1$ 位，枚举第 $i$ 位，之后的位数则预处理满足条件的的最小答案或者无解。

最后对于每个 $b_i$，计算得 $a_i=calc(b_i,a_{i-1})$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
string ls="0",f[410][4010];
bool cmp(string a,string b)//a>b?
{
	if(a.size()^b.size())
		return a.size()>b.size();
	for(int i=0;i<a.size();i++)
		if(a[i]^b[i])
			return a[i]>b[i];
	return 0;
}
string calc(int x,string lb)
{
	vector<int>vec;
	int sum=0;
	for(auto i:lb)
		vec.push_back(i-'0'),sum+=i-'0';
	reverse(vec.begin(),vec.end());
	for(int i=0;i<vec.size();i++)
	{
		sum-=vec[i];
		for(int j=vec[i]+1;j<=9;j++)
		{
			if(x-(sum+j)<0||x-(sum+j)>9*i)
				continue;
			return lb.substr(0,vec.size()-i-1)+char(j+'0')+f[i][x-(sum+j)];
		}
	}
	int i=lb.size();
	while(!f[i][x].size())
		i++;
	return cmp(f[i][x],lb)?f[i][x]:"1"+f[i][x-1];
}
int main()
{
	for(int j=0;j<=9;j++)
		f[1][j]+=char(j+'0');
	for(int i=2;i<=400;i++)
	{
		for(int k=0;k<=9*i;k++)
		{
			for(int j=0;j<=min(9,k);j++)
				if(f[i-1][k-j].size())
				{
					f[i][k]=char(j+'0')+f[i-1][k-j];
					break;
				}
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		ls=calc(x,ls);
		printf("%s\n",ls.c_str());
	}
	return 0;
}
```


---

