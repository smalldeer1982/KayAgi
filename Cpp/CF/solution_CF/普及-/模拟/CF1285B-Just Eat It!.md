# Just Eat It!

## 题目描述

### 题意简述

给定长度为 $n$ 的数列 $a=[a_1,a_2,...,a_n]$。

Yasser 会选择所有的 $n$ 个数，并算出它们的和 $\sum a_i$。

Adel 会选择两个正整数 $l,r(1\leq l \leq r \leq n)$，并算出 $\sum_{i=l}^{r} a_i$。Adel 不能选择 $l=1,r=n$。

如果 Yasser 算出的和在任意情况下（即 Adel 选取任意的 $l,r$ 都是如此）**严格大于** Adel 算出的，那么 Yasser 会开心。否则 Yasser 不会开心。

请你判断 Yasser 是否开心。

## 样例 #1

### 输入

```
3
4
1 2 3 4
3
7 4 -1
3
5 -5 5```

### 输出

```
YES
NO
NO```

# 题解

## 作者：Little_x_starTYJ (赞：6)

### 解题思路:
这道题目就是让我们求出不同时包含两端的**最大子段和**。

我们仅仅需要求出 $a_1 \sim a_{n - 1}$ 的最大子段和与 $a_2 \sim a_n$ 的最大子段和，再与 $\sum_{i=1}^n a_i$ 进行比较即可。

在处理最大子段和的时候要分成两种情况：

1. ```dp[i] = dp[i - 1] + a[i];```
2. ```dp[i] = a[i];```

第 $1$ 种情况就是添加一个元素 $a_i$ 到当前序列中，第 $2$ 种情况就是再定义一个目前只包含元素 $a_i$ 的序列。那么，我们每次找出这两种情况的最优解，就可以解决这道题目。

如果没有看懂，可以去看看[这个](https://blog.csdn.net/weixin_44023658/article/details/105928520)。

注意：题目要求是**绝对大于！！！！！**


CODE:
```cpp
#include <iostrem>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];
long long sum(int l, int r) {
    long long sum = 0, max2 = -1e18;
    while (l <= r) {
        sum += a[l];
        max2 = max2 > sum ? max2 : sum;
        sum = max(sum, 0ll);
        l++;
    }
    return max2;
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        long long s = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            s += a[i];
        }
        if (sum(1, n - 1) < s && sum(2, n) < s) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：Awdrgysxc (赞：4)

## 【$Analysi$】
$A$是$Sum$,而$B$是不含两端的最大子段和，可以$DP$求出

$F_{ijk}$表示前i个数字，第i个是否选(j)，是否选了开头(k)

## 【$Code$】
```cpp
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
static char s[1<<20|1]={0},*p1=s,*p2=s;
inline char gc() { return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++); }
//inline char gc() { return getchar(); }
inline int read()
{
	int ret=0;bool flag=0;char c=gc(); while ((c<'0')|(c>'9')) flag ^= !(c^'-'),c=gc();
	while ((c>='0')&(c<='9')) ret=(ret<<1)+(ret<<3)+(c^'0'),c=gc(); return flag?-ret:ret;
}

typedef long long int64;

const int MaxN = 1e5 + 111;

int64 F[MaxN][2][2], A[MaxN];

int q, n;

int64 ans, ss;

int main(void)
{
	q = read();
	for (;q--;)
	{
		n = read(), ss = ans = 0;
		for (int i = 1;i <= n; ++i) F[i][0][0] = F[i][0][1] = F[i][1][0] = F[i][1][1] = 0;
		for (int i = 1;i <= n; ++i)
			A[i] = read(), F[i][1][0] = A[i], ss += A[i]; F[1][1][1] = A[1], F[1][1][0] = 0;
		for (int i = 2;i <= n; ++i) 
			F[i][1][0] = std::max(F[i - 1][1][0] + A[i], A[i]),
			F[i][1][1] = F[i - 1][1][1] + A[i];//, printf("gg i = %d %d %d\n", i, F[i][1][0], F[i][1][1]);
		for (int i = 1;i < n; ++i)
			ans = std::max(std::max(F[i][1][1], F[i][1][0]), ans);
		ans = std::max(ans, F[n][1][0]);
		//printf("%d %d\n", ss, ans);
		puts(ss > ans ? "Yes" : "No");
	}
}
```

---

## 作者：chenyuchenghsefz (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1285B)

可以用 DP 做。

设 $f_i$ 是从 $a_1$ 到 $a_i$ 的最大连续子序列的和。则 $f_n$ 就是原序列最大连续子序列的和（当然要去掉原序列）。

每输入一个 $a_i$，都要判断是否要加入之前的连续子序列。

- 如果 $f_{i-1}+a_i>a_i$，即 $f_i>0$，则 $f_i=f_{i-1}+a_i$。

- 不然的话，定义一个 $l$ 来记录连续子序列的左端点。$f_i=a_i$。

- 如果要把 $a_n$ 加入序列且 $l=1$ 那么不加入 $a_n$。

[AC 记录](https://www.luogu.com.cn/record/103519716)
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long f[100100]={0};
int a[100100];
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		long long n,s=0,l=1,ans=-1000000100;
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
			s+=a[j];
			if(f[j-1]>0)
			{
				if(l==1&&j==n)
				continue;
				f[j]=f[j-1]+a[j];
			}
			else
			f[j]=a[j],l=j;
			ans=max(ans,f[j]);
		}
		if(ans<s)
		cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：zjhzs666 (赞：1)

# CF1285B Just Eat It! 题解


[题目传送门](https://www.luogu.com.cn/problem/CF1285B)


## 题意


共 $t$ 组数据，每次给定长度为 $n$ 的序列 $a$，判断 $a$ 是否会有一个子段的总和大于或等于 $a$ 序列的总和。


## 思路


### 解法一


根据题意进行模拟，枚举序列的所有子段，每次计算子段的总和，找出总和最大的子段，再与序列之和进行比较，$O(n^3)$ 做法。


### 解法二


利用前缀和对解法一进行优化，$O(n^2)$ 做法。


### 解法三（正解）


对于一个子段，如果它要添加一个新的元素 $x$ ，当该字段之和 $mx$ 的值为正数时，添加 $x$ 后 $mx$ 的值会比 $x$ 的值要大即可以添加 $x$，当 $mx$ 的值为负数时，添加 $x$ 后 $mx$ 的值会比 $x$ 的值要小，此时就应当放弃该子段将 $x$ 作为一个新的子段继续进行求解。$O(n)$ 做法。空间复杂度 $O(1)$。


**注意：要开 long long；要特判子段是否不为原序列。** 


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,x,mx,ans,s,l; 
int main(){
	cin>>t;
	while(t--){
		s=mx=0;
		ans=-1e16;
		l=1;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			s+=x;
			if(mx>0){
				if(l==1&&i==n)
					continue;
				mx+=x;
			}
			else mx=x,l=i;
			ans=max(ans,mx);
		}
		if(s>ans)cout<<"YES\n";
		else cout<<"NO\n"; 
	}
	return 0;
} 
```



---

## 作者：Jerrycyx (赞：1)

**注：这应该是最快的题解了（总共 $321$ ms）。**

## 简化题意

判断一个序列是否满足：**该序列和严格大于其所有连续子序列和（不包括原序列）**

# 解析

【简化题意】中“严格大于其所有连续子序列和（不包括原序列）”，可以转化成“**严格大于非原序列的最大连续子序列和**”。所以我们只需要求出“非原序列的最大连续子序列和”并将其与原序列和相比较即可。

求出“非原序列的最大连续子序列和”，我们可以采用 **DP** 的方法。**设 $p_i$ 表示从 $a_1$ 到 $a_i$ 的最大连续子序列和**，那么 $a_n$ 就表示“最大连续字段和”。

对于每个原序列的每个数 $a_i$，都需要决定**是否将其加入之前的连续子序列**。

+ 对于“加入”的情况，明显 $p_i=p_{i-1}+a_i$。

+ 对于“不加入”的情况，那么新的 $p_i=a_i$。

$p_i$ 应该取以上两种情况的结果的**最大值**。即：

$$p_i = \max \begin{cases}
   p_{i-1}+a_i \\
   a_i
\end{cases}$$

注意要**排除“最大连续子序列为原序列”的情况**。我们可以用变量 $l$ 记录最大连续子序列的左端点，当需要把 $a_n$ 加入序列且 $l=1$ 时不予更新。

另外，因为 $p$、记录总值和记录最大连续子序列的变量均为多个 $a$ 数组元素累加的结果，所以**需要开 `long long`**。

时间复杂度为 $O(n)$，线性，所有题解中**最快**。

# 代码

```cpp
#include<cstdio>
#define max(x,y) x>y?x:y
#define N 200005
using namespace std;

int t,n;
int a[N];
long long p[N];

int main()
{
	scanf("%d",&t);
	for(int I=1;I<=t;I++)
	{
		scanf("%d",&n);
		long long tot=0;	//tot 记录原序列和 
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			tot+=a[i];
		}
		long long ans=-1000000005;			//ans 记录最大连续子序列
		int l=1;
		for(int i=1;i<=n;i++)
		{
			if(p[i-1]+a[i]>a[i])
			{
				if(l==1&&i==n) continue;	//排除“最大连续子序列为原序列”的情况 
				p[i]=p[i-1]+a[i];
			}
			else p[i]=a[i],l=i;		//更改左端点 
			ans=max(ans,p[i]);		//在求 p[i] 时顺便把 ans 也求出来 
		}
		if(tot>ans) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## CF1285B Just Eat It! 题解
### 思路
乍一看是一道普通前缀和，但此题中枚举 $l$ 和 $r$ 的时间复杂度就有 $O(n^2)$，$n \le 10^5$，必定超时。现在我们考虑优化，题目只说了 Yasser 的值严格大于 Adel 的值，所以我们可以直接把 Adel 的值设到最大用于比较，然后维护一个 $mini$ 数组，记录 $[f[1],f[i-1]]$ 区间内的最小值，把 $f[i-1]-sum[i]$ 的值与 Yasser 的值比较。（$sum[\ ]$ 为前缀和数组）

注意：需要特判 $i=n$ 时的情况。

### 代码

```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(int x)
{
    if(x<0){x=-x;putchar(45);}
    if(x>9) write(x/10);
    putchar(x%10+48);
    return;
}
#define int long long
using namespace std;
const int maxn=1e5+5;
const int inf=1e15+5;
int t,n;
int tot;
int a[maxn],sum[maxn],mini[maxn];
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		tot=0;
		bool flag=true;
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			tot+=a[i];
			sum[i]=sum[i-1]+a[i];
		}
		mini[1]=0;
		for(int i=2;i<=n;i++)
		{
		    mini[i]=min(mini[i-1],sum[i-1]);
		}
		for(int i=1;i<n;i++)
		{
			int x=sum[i]-mini[i];
			if(x>=tot)
			{
				flag=false;
				break;
			}
		}
		int cnt=inf;
		for(int i=1;i<n;i++)
		{
		    cnt=min(cnt,sum[i]);
		}
		if(sum[n]-cnt>=tot)
		{
		    flag=false;
		}
		if(flag)
		{
		    printf("YES\n");
		}
		else
		{
		    printf("NO\n");
		}
	}
	return 0;
}

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/CF1285B)

这道题其实很简单，就是求整个序列的总和和[最大子段和](https://www.luogu.com.cn/problem/P1115)，而我们再求最大子段和的时候还需要避开 $l=1,r=n$ 的情况，这个也很好处理，只需要在求最大子段和的时候记录一个 $l$ 表示当前这个子段和的左端点，当我们发现下一位也可以放入当前的子段和的时候，如果 $l=1,i=n$ 则表明当前这个子段和不能应用，即这个子段和的左端点是 $1$，右端点是 $n$，所以我们就需要忽略掉这个子段和。

整个问题的答案就是如果整个序列的总和**严格大于**（即大于，非大于等于）最大子段和，那么输出```YES```，否则输出```NO```。

这里我就给出求最大子段和的代码。 

```cpp
a[i]:表示输入的序列
f[i]:表示第1位到第i位的最大子段和
ans:表示满足条件的最大子段和（即非左端点为1，右端点为n的情况）的值 

for(int i=1;i<=n;i++) 
{
	if(f[i-1]+a[i]>a[i])//这一位放在子段和里更优
		if(l==1&&i==n) //代表此子段和不能取
			continue;
		else f[i]=f[i-1]+a[i];//放进去
	else f[i]=a[i],l=i;//以这一位单独开始一个子段和更优，则需要更新子段和的左端点，即更新成i
	ans=max(ans,f[i]); //记得要求最大值 
}
```

## 十年OI一场空，不开long long见祖宗！ 

---

## 作者：YLWang (赞：0)

简单题。

因为没开long long挂了一次。见祖宗了。

首先我们考虑只要算出第二个人所有取法中和最大的一个方案，再把它和所有数的和比较就行了

做一个前缀和，考虑枚举右端点位置 $i$。这时候要使和最大，就是要在 $i$ 左边找一个位置 $j$，使得$sum[i] - sum[j]$ 尽可能大。因为$sum[i]$是固定的，所以直接维护一个最小值就可以了。

注意在$i = n$的时候需要特判一下。

```cpp

#define int long long
const int MAXN = 100005;
int n, a[MAXN], sum[MAXN];
signed main()
{
	int T = read();
	while(T--) {
		n = read();
		For(i, 1, n) a[i] = read(), sum[i] = sum[i-1] + a[i];
		int msum = 0, maxi = 0;
		For(i, 1, n) {
			if(i != n) ckmax(maxi, sum[i] - msum);
			else For(j, 1, n) ckmax(maxi, sum[i] - sum[j]);
			if(msum > sum[i])
				msum = sum[i];
		}
		if(maxi < sum[n]) puts("YES");
		else puts("NO");
	}
    return 0;
}
```

---

