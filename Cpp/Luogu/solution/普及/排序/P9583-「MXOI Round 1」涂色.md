# 「MXOI Round 1」涂色

## 题目描述

小 C 正在用彩铅给一张 $n$ 行 $m$ 列的方格纸涂色。初始时，所有方格都是空白的。

他一共要进行 $q$ 次涂色，每次涂色会选取一行或一列，给这一行或这一列的所有方格都添加 $1$ 层颜色。

小 C 喜欢浅色，所以他会在每次涂色结束后，把所有被涂上 $k$ 层颜色的方格的颜色都擦掉，让这些方格都变成空白的。

小 C 想知道，在最终共有多少方格被涂上了颜色。

## 说明/提示

#### 【样例解释 #1】

第 $1$ 行第 $1$ 列的方格没有被涂上颜色，第 $1$ 行第 $2$ 列的方格被涂上了 $1$ 层颜色，第 $1$ 行第 $3$ 列的方格没有被涂上颜色，第 $1$ 行第 $4$ 列的方格被涂上了 $1$ 层颜色；

第 $2$ 行第 $1$ 列的方格被涂上了 $1$ 层颜色，第 $2$ 行第 $2$ 列的方格被涂上了 $2$ 层颜色，第 $2$ 行第 $3$ 列的方格被涂上了 $1$ 层颜色，第 $2$ 行第 $4$ 列的方格被涂上了 $2$ 层颜色；

第 $3$ 行第 $1$ 列的方格被涂上了 $2$ 层颜色，第 $3$ 行第 $2$ 列的方格的颜色被擦掉了，第 $3$ 行第 $3$ 列的方格被涂上了 $2$ 层颜色，第 $3$ 行第 $4$ 列的方格的颜色也被擦掉了；

最终，共有 $8$ 个方格被涂上了颜色。

#### 【样例 #2】

见附加文件中的 `paint/paint2.in` 与 `paint/paint2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `paint/paint3.in` 与 `paint/paint3.ans`。

该样例满足测试点 $5$ 的限制。

#### 【样例 #4】

见附加文件中的 `paint/paint4.in` 与 `paint/paint4.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le n,m \le 2\times 10^5$，$1 \le k \le q \le 5 \times 10^5$，$op \in \{1,2\}$，保证当 $op=1$ 时 $1 \le x \le n$，当 $op=2$ 时 $1 \le x \le m$。

|测试点编号|$n,m \le$|$q \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim4$|$3000$|$3000$|无|
|$5\sim9$|$3000$|$5\times10^5$|无|
|$10\sim12$|$2\times10^5$|$5\times10^5$|A|
|$13\sim16$|$2\times10^5$|$5\times10^5$|B|
|$17\sim20$|$2\times10^5$|$5\times10^5$|无|

特殊性质 A：保证 $op=1$。

特殊性质 B：保证 $k=2$。

## 样例 #1

### 输入

```
3 4 5 3
1 3
2 4
1 2
1 3
2 2```

### 输出

```
8```

# 题解

## 作者：BL_zhanggezi (赞：28)

### 题目大意
原本所有方格都是空白的，每次涂色给一行或一列的所有方格都添加 $1$ 层颜色，**每次涂色结束后，把所有被涂上 $k$ 层颜色的方格的颜色都擦掉，让这些方格都变成空白的。**问最终共有多少方格被涂上了颜色。

### 思路
首先我们可以想到一种办法：二维差分。但是当我们看 $n$ 和 $m$ 的范围时我们会发现如果开二维数组会爆，所以我们可以开两个一维数组 $h$ 和 $s$ 来分别储存行和列被涂过的次数。

但开两个一维数组似乎只能使用暴力，因为我们需要求出每个方格被涂过的次数然后看看能否整除 $k$，这样还会超时。

是否能在此想法上优化？当然可以。我们可以用 $c$ 来保存如需把放个方格变成空白的 $h_i \bmod k$ 的值，而 $c=c-(s_i \bmod k) \bmod k$，所以我们可以使用循环来计算满足 $h_i \bmod k = c$ 的数量，而一段满足条件的 $h_i$ 可以使用二分查找数量，使用二分前要将 $h$ 从小到大排序，该部分代码如下（其中 $ans$ 的初始值为 $n \times m$，让 $ans$ 减去空白方格的数量就可以得出最终答案）：

```cpp
for(int i=1;i<=m;i++)
{
	c=s[i]%k;
	for(int j=(k-c)%k;j<=h[n];j+=k)//每次加k优化
	{
		ans=ans-(find_right(j)-find_left(j)+1);
      		//find_right(j)-find_left(j)+1是符合要求的数量
	}
}
```

当我们使用这种方法去写时，运行第四个样例时我们会发现它超时了。我们把超时的原因锁定在二分上，新的问题出现了：如何优化二分？

我们可以想想我们使用二分是用来干什么的？对，是求 $h_i = c$ 数量，所以我们可以使用数组计数进行优化。优化后的部分代码如下：

```cpp
for(int i=1;i<=m;i++)
{
	c=s[i]%k;
	for(int j=(k-c)%k;j<=h[n];j+=k)
	{
		ans=ans-ss[j];//ss[j]是符合要求的数量
	}
}
```

完整 AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,nm,k,as,x,h[200010],s[200010],ans=0,c,ss[500010];
int main()
{
	cin>>n>>m>>nm>>k;
	ss[0]=n;//初始化，开始时每个格子都没涂，所以没涂的行数有n 
	for(int i=1;i<=nm;i++)
	{
		cin>>as>>x;
		if(as==1) 
		{
			h[x]++;
			ss[h[x]-1]--;//涂过h[x]-1次的行数减1 
			ss[h[x]]++;//涂过h[x]次的行数加1 
		} 
		else s[x]++;
	}
	sort(h+1,h+n+1);//从小到大排序 
	ans=n*m;//答案初始化 
	for(int i=1;i<=m;i++)
	{
		c=s[i]%k;
		for(int j=(k-c)%k;j<=h[n];j+=k)
		{
			ans=ans-ss[j];
		}
	}//该部分解释同上推理过程 
	cout<<ans;//输出结果 

	return 0;
}
```

### 注意事项
使用 int 会爆，所以请使用 long long。

---

## 作者：wpy233 (赞：23)

- 引理一：最终涂色状态和涂色操作顺序无关

- 因为我们要得到的是最终的涂色状态，所以一个之前已经被涂上色的格子如果**在最后一次涂色后没有被擦去**，那么这个格子最后就会被涂上颜色。因此，涂色次数是 $k$ 的倍数的行和列都可以被忽略，最后只需要判断涂色次数为 $k$ 的交叉格并把它们擦除即可。

- 引理二：大小为 $n \times m$ 的方格纸上，$a$ 行 $b$ 列涂色格相交，在不考虑擦除的情况下，可以得到 $am+bn-ab$ 个涂色方格。

- 证明显然。

- 引理三：十年 OI 一场空，不开 $\texttt{ll}$ 见祖宗。

- 记得开 $\texttt{long}$ $\texttt{long}.$

代码（附注释）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long //记得开long long
ll a[200005]; //记得开long long
ll b[200005]; //记得开long long
ll c[500005]; //记得开long long
ll d[500005]; //记得开long long
inline ll read()
{
	char ch;
	ll x=0,f=1;
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')
			f=-1;
	for(; isdigit(ch);ch=getchar())
		x*=10,x+=(ch-'0');
	return x*f;	
}
int main()
{
	int n,m,q,k;
	n=read(),m=read();
	q=read(),k=read();
	int op,x;
	for(int i=1;i<=q;i++)
	{
		op=read();
		x=read();
		if(op==1) 
		{
			a[x]++;
			if(a[x]==k) 
				a[x]=0; 
		} //去除重复在k次以上的部分
		else 
		{
			b[x]++;
			if(b[x]==k) 
				b[x]=0;
		} //去除重复在k次以上的部分
	}
	ll ans1=0,ans2=0,ans;
	for(int i=1;i<=n;i++)
		if(a[i]>0)
		{
			ans1++; //统计去除后有多少被涂色的行
			c[a[i]]++; //用桶存储被涂色过a[i]次的行
		}
	for(int i=1;i<=m;i++)
		if(b[i]>0)
		{
			ans2++; //统计去除后有多少被涂色的列
			d[b[i]]++; //用桶存储被涂色过b[i]次的列
		}
	ans=ans1*m+ans2*n-ans1*ans2; //公式计算
	for(int i=1,j=k-1;i<=k-1,j>=1;i++,j--)
		ans-=c[i]*d[j]; //去除涂色次数加和为k的交叉格
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：22)

### Task 1~4

开一个二维数组，每次暴力 $O(n)$ 修改，总复杂度 $O(nq)$。

### Task 5~9

开两个数组 $r,c$，分别记录每行和每列进行的操作。

对于每个 $op=1$，令 $r_x$ 加一；

对于每个 $op=2$，令 $c_x$ 加一。

在操作结束后，把二维数组中的所有元素都求出来，并对 $k$ 取模，数一下不为 $0$ 的元素个数即可。时间复杂度 $O(q+n^2)$。

### Task 10~12

我们只需要开一个数组 $r$ 记录每行进行的操作。

每次操作，令 $r_x$ 加一。

在所有操作结束后，将 $r_i$ 都对 $k$ 取模，如果不为 $0$ 则说明这一行的格子都被涂上色了，给答案变量 $ans$ 增加 $m$，最后输出 $ans$ 即可。时间复杂度 $O(q+n)$。

### Task 13~16

还是开两个数组 $r,c$ 记录每行和每列进行的操作。

对于每个 $op=1$，令 $r_x$ 加一；

对于每个 $op=2$，令 $c_x$ 加一。

然后我们把所有 $r_i$ 和 $c_i$ 都对 $2$ 取模，记录一下 $r$ 中 $1$ 和 $0$ 的数量 $a,b$ 以及 $c$ 中 $1$ 和 $0$ 的数量 $f,g$。

显然地，对于某个格子，如果它所在行的 $r_i$ 的值与所在列的 $c_j$ 的值不同，则这个格子会被涂上颜色，否则行的操作会和列的操作抵消，这个格子不会被涂上颜色。

那么答案就是 $ag+bf$，输出其即可。时间复杂度 $O(q+n)$。

### Task 17~20

之前的操作不变，直接看最终统计答案的部分。

我们首先将 $r$ 和 $c$ 中所有元素均对 $k$ 取模。

对于某个格子，设其所在行为 $i$，所在列为 $j$，如果 $(r_i+c_j) \bmod k=0$，则说明行的操作和列的操作抵消了，这个格子不会被涂上颜色。否则，这个格子就被涂上颜色了。

我们开一个大小为 $k$ 的桶 $w$，统计一下 $r$ 中每个元素的出现次数。

我们从 $1$ 到 $m$ 枚举 $j$，计算 $c_j$ 对答案的贡献。根据我们上面得到的性质，若 $c_j$ 为 $0$，则它的贡献就是 $n-w_0$；否则，它的贡献就是 $n-w_{k-c_j}$。

最后输出所有元素的贡献之和即可。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5,K=5e5+5;
int c[N],r[N],w[K];
int main(){
	ios::sync_with_stdio(0);
	int n,m,q,k,op,x;
	ll cnt=0;
	cin>>n>>m>>q>>k;
	for(int tmp=1;tmp<=q;tmp++){
		cin>>op>>x;
		if(op==1) r[x]++;
		else c[x]++;
	}
	for(int i=1;i<=n;i++) w[r[i]%k]++;
	for(int j=1;j<=m;j++){
		c[j]%=k;
		if(c[j]==0) cnt=cnt+n-w[0];
		else cnt=cnt+n-w[k-c[j]];
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：卷王 (赞：9)

## 题目大意

一张 $n \times m$ 的方格纸，进行 $q$ 次操作，每一次涂一整行或一整列。最后求出涂色层数不被 $k$ 整除的方格个数。

## 大体思路

实际上这题的代码是非常简短的。

容易想到用 $row_x$ 表示第 $x$ 行一共被涂了几次，$col_y$ 表示第 $y$ 列一共被涂了几次。

但是光是这样是不行的，因为统计答案需要 $O(nm)$ 的时间复杂度。

看到模数 $k$ 的数据范围很小，完全够开一个桶，考虑从这里开始突破。建一个桶 $cnt_i$ 表示每一个 $row_i \bmod k$ 的数量。对于每一个 $col_i$，只有当 $row_i \bmod k = k- col_i$ 的时候才会被擦掉，应为 $(k-col_i) + col_i = k$。

但是有一点要注意一下，当 $col_i \bmod k$ 为 $0$ 的时候，应该特判，不管怎样 $row_i$ 都不可能是 $k$，因为已经对 $k$ 取模了。所以，在这种情况下，应该取 $row_i \bmod k = 0$ 的数量。

代码如下：

```cpp
#include <stdio.h>
typedef long long ll;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, q, k;
ll ans = 0;
int row[200007], col[200007];
int cnt[500007];

int main() {
	n = read(), m = read(), q = read(), k = read();
	while(q--) {
		int opt = read(), x = read();
		if(opt == 1) row[x] = (row[x] + 1) % k;
		else col[x] = (col[x] + 1) % k;
	}
	for(int i = 1; i <= n; i++) cnt[row[i]]++;
	for(int i = 1; i <= m; i++) ans += n - cnt[(k - col[i]) % k];
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：andyli (赞：7)

题目可以转化为求无色方格数量，即被涂色次数为 $k$ 的倍数的方格数量。  
记录每行、每列的涂色次数，枚举行的涂色次数 $c_0$，只需要知道有多少列的涂色次数 $c_1$ 满足 $(c_0+c_1)\bmod k=0$，故将列的涂色次数 $\bmod \ k$ 后放入桶中统计即可。用总方格数量减去无色方格数量即为题目所求。  

```cpp
#include "lib/all.hpp"

int main() {
    dR(int, n, m, q, k);
    vi row(n), col(m), cnt(k + 1);
    _for (q) {
        dR(int, t, x), x--;
        if (t == 1)
            row[x]++;
        else
            col[x]++;
    }
    _for (i, m)
        cnt[col[i] % k]++;
    cnt[k] = cnt[0];
    u64 ans = 0;
    _for (i, n)
        ans += cnt[k - row[i] % k];
    writeln(u64(n) * m - ans);
    return 0;
}
```

---

## 作者：佬头 (赞：4)

## Description
有一张 $n$ 行 $m$ 列的方格纸，起初所有方格都是空白的。接下来要进行 $q$ 次[**涂色**](https://www.luogu.com.cn/problem/P9583)，每次涂色会指定将某一行或某一列的所有方格都添加 $1$ 层颜色。每次涂色结束后，会把所有被涂上 $k$ 层颜色的方格的颜色都擦掉，让这些方格都变成空白的。求最终共有多少方格被涂上了颜色。

## Solution
既然每次涂色是涂一行或一列，就需要记录每一行以及每一列被涂上的颜色层数，前者计为 $r$，后者计为 $c$，擦颜色的话可以统计完后再考虑。可以想到的是，最终第 $i$ 行第 $j$ 列的格子被涂上了颜色当且仅当 $(r_i+c_j)\bmod k\mathrlap{\,/}{=}0$，即 $(r_i\bmod k+c_j\bmod k)\bmod k\mathrlap{\,/}{=}0$。定义 $f_j$ 表示与第 $j$ 列的颜色层数之和不是 $k$ 的倍数的行数，因此问题便转化为了求 $\sum\limits_{j=1}^{m}f_j$。由于 $k$ 的范围比较小，所以可以利用**计数排序**的思想统计一下 $s_i$ 表示满足 $r\bmod k=i$ 的行数，则 $f_j+s_{(k-c_j\bmod k)\bmod k}=n$，答案为 $\sum\limits_{j=1}^{m}n-s_{(k-c_j\bmod k)\bmod k}$。

## Code
```cpp
#include <iostream>
using namespace std;
const int N = 200005;
int n, m, q, k, row[N], col[N], s[(N<<1)+N];
long long ans;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(long long x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	n = read(), m = read(), q = read(), k = read();
	for(int i = 1; i <= q; ++ i)
		if(read() == 1) ++ row[read()];
		else ++ col[read()];
	for(int i = 1; i <= n; ++ i) ++ s[row[i] % k];
	s[k] = s[0];
	for(int i = 1; i <= m; ++ i) ans += n - s[k - col[i] % k];
	write(ans);
	return 0;
}
```


---

## 作者：zbk233 (赞：3)

## 1. 题意转换

题中每次操作都会将涂了 $k$ 层色的方格变为空白，那么可以看出，只要**最终**这个方格涂的色数是 $0$ 或 $k$ 的倍数，那么这个方格最终就会成为空白。

那么题意就可以转换为：在一个矩阵中，每次操作可以将一行或一列的数字全都加一，求最后**不是** $0$ 或 $k$ 的倍数的数字的个数。

## 2. 算法解析

### 2.1 读入

本题的操作只有对行或列的数字全都加一，那么我们就可以以行或列为**一个整体**进行考虑，基于这样的考虑，我们可以使用 $hang(i)$ 表示第 $i$ 行被染色的次数，$lie(i)$ 表示第 $i$ 列被染色的次数，当然，为了方便处理，我们可以在读入时进行模 $k$ 处理。

经过这样的操作之后，显然，对于矩阵中一个数 $a(i, j)$，它的值就是 $hang(i) + lie(j)$ 了。

### 2.2 统计

枚举每一个数显然会超时，我们考虑新的方法。

正难则反，直接求出模 $k$ 不等于 $0$ 的数的个数很困难，但是我们可以求出模 $k$ 等于 $0$ 的数的个数。

由于我们已经在读入时对 $hang(i)$ 与 $lie(j)$ 进行了模 $k$ 处理，那么这样模 $k$ 等于 $0$ 的数（$hang(i) + lie(j)$）的值只能是 $0$ 或 $k$。

我们可以枚举每一行的 $hang(i)$，并求出符合条件的 $lie(j)$ 的个数，这时候分两种情况。

1. $hang(i) = 0$，那么因为 $lie(j)$ 不可能等于 $k$，所以此时的 $lie(j) = 0$。

2. $hang(i) = x (x > 0)$，那么因为 $lie(j)$ 为正数，所以 $hang(i) + lie(j) = k$，所以此时的 $lie(j) = k - x$。

这时候我们就可以使用桶来保存 $lie$ 数组每一种值的个数，就可以解出答案了。

## 3. 解题代码

```cpp
#include <iostream>
#define ll long long
using namespace std;

int hang[200005], lie[200005];
int t[500005];

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n, m, q, k, ans = 0;
	cin >> n >> m >> q >> k;
	while (q--) {
		int op, x;
		cin >> op >> x;
		if (op == 1) {
			hang[x] = (hang[x] + 1)%k;
		}
		if (op == 2) {
			lie[x] = (lie[x] + 1)%k;
		}
	}
	for (int i = 1; i <= m; i++) {
		t[lie[i]]++;
	}
	for (int i = 1; i <= n; i++) {
		if (hang[i] == 0) ans += (m - t[0]);
		else ans += (m - t[k - hang[i]]);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：scp020 (赞：3)

# P9583 涂色 题解

## 解法

题中说求最终有多少个方格涂着颜色，那我们可以求有多少个方格没有颜色，用方格的总数减去没有颜色的方格数即为所求。

考虑本题涂色规律，涂上 $k$ 层颜料的方格其颜料会被擦去，这种操作的本质是对 $k$ 取模，所以没有颜色的方格即该方格所在的行、列被涂色的次数和可以被 $k$ 整除。

现在分别统计每个行、每个列的涂色次数，然后对行、列分别开两个桶，维护每行、每列的涂色次数对 $k$ 取模后的值。

然后枚举桶里的元素。设有 $rubh_i$ 个行的涂色次数对 $k$ 取模等于 $i$，$rubl_i$ 个列的涂色次数对 $k$ 取模等于 $i$，则想要让一个方格没有颜色，则必须满足 $hang_i + lie_i \equiv 0 \pmod{k}$，所以对于 $rubh_i$ 个行，只有 $rubl_{k-i}$ 个列与之匹配才能是没有颜色的方格，根据乘法原理，有 $rubh_i \times rubl_{k-i}$ 个方格没有颜色。特殊地，$rubh_0$ 与 $rubl_0$ 匹配。

求解公式即为 $rubh_0 \times rubl_0 + \sum \limits _{i=1} ^{i < k} rubh_i \times rubl_{k-i}$，时间复杂度 $\mathcal{O}(q + k)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	快读快写
	*/
};
using namespace fast_IO;
int n,m,q,k,hang[200010],lie[200010],rubh[500010],rubl[500010];
inline void delh(int x)
{
	if(x==k-1) rubh[x]--,rubh[0]++;
	else rubh[x]--,rubh[x+1]++;
}
inline void dell(int x)
{
	if(x==k-1) rubl[x]--,rubl[0]++;
	else rubl[x]--,rubl[x+1]++;
}
long long ans;
int main()
{
	read(n),read(m),read(q),read(k),rubh[0]=n,rubl[0]=m;
	for(int i=1,op,x;i<=q;i++)
	{
		read(op),read(x);
		if(op==1) hang[x]++,delh((hang[x]-1)%k);
		else lie[x]++,dell((lie[x]-1)%k);
	}
	ans+=1ll*rubh[0]*rubl[0];
	for(int i=1;i<k;i++) ans+=1ll*rubh[i]*rubl[k-i];
	cout<<1ll*n*m-ans;
	return 0;
}
```


---

## 作者：Phartial (赞：3)

考虑维护每个方格被涂色的次数 $a_{i,j}$，那么一个方格最终有颜色当且仅当 $a_{i,j}\not\equiv0\pmod k$。考虑通过容斥将原题转化为求 $(i,j)$ 的数量 $s$ 使得 $a_{i,j}\equiv 0\pmod k$，那么原题的答案即为 $nm-s$。

由于涂色操作只涉及到一整行或一整列，考虑维护两个数组 $r_i,c_i$ 表示第 $i$ 行/列被涂色的次数。则有 $a_{i,j}=r_i+c_j$。

问题变为求 $(i,j)$ 的数量使得 $r_i+c_j\equiv 0\pmod k$，条件可以简单转化为 $r_i\equiv -c_j\pmod k$，由于同余式两边的式子相互独立，考虑使用一个桶 $b_k$ 存储 $r_i=k$ 的个数，那么 $c_j$ 的贡献即为 $b_{(k-c_j)\bmod k}$。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1, kK = 5e5 + 1;

int n, m, q, k, r[kN], c[kN], b[kK];
LL s;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> q >> k;
  for (int o, x; q--; ) {
    cin >> o >> x;
    if (o == 1) {
      ++r[x];
    } else {
      ++c[x];
    }
  }
  for (int i = 1; i <= n; ++i) {
    ++b[r[i] % k];
  }
  for (int i = 1; i <= m; ++i) {
    s += b[(k - c[i] % k) % k];
  }
  cout << 1LL * n * m - s;
  return 0;
}
```


---

## 作者：二叉苹果树 (赞：3)

我们分别统计每行和每列涂色的次数，然后依次遍历每一行。

如果某一行进行了 $x\left(x > 0\right)$ 次涂色操作，那么显然所有进行 $k - x$ 次涂色操作的列与这一行相交的所有方格都会被擦掉。相反地，如果某一行没有进行涂色操作，那么我们需要统计涂色 $1 \sim k - 1$ 次的列，因为这些列对于这一行的涂色操作都是有效的。

```cpp
#include <bits/stdc++.h>
#define maxn 200005
#define maxk 500005

long long n, m, ans, sum;
int r[maxn], c[maxn], vis[maxn], t[maxk];
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q, k, op, x;
    std::cin >> n >> m >> q >> k;
    ans = n * m;
    for (int i = 1; i <= q; i++)
    {
        std::cin >> op >> x;
        if (op & 1)
            r[x] = (r[x] + 1) % k;
        else
        {
            if (!vis[x])
                vis[x] = 1;
            else
                t[c[x]]--;
            c[x] = (c[x] + 1) % k;
            t[c[x]]++;
        }
    }
    for (int i = 1; i <= k - 1; i++)
        sum += t[i];
    for (int i = 1; i <= n; i++)
    {
        if (r[i])
            ans -= t[k - r[i]];
        else
            ans += (sum - m);
    }
    std::cout << ans << std::endl;
    return 0;
}
```


---

## 作者：lemon_qwq (赞：2)

挺好的思维题。

看到题面，我们可以很轻松想到一个暴力：开一个二维数组模拟染色的操作，但是现实很残酷，$2\times10^5$ 根本开不开二维数组，于是我们要想新的做法。

也不难想到，我们可以用两个一维数组模拟第一排和第一列，因为染色是一整排一整列染的，所以第一排的某个元素染了就代表染的元素所属的那一列都被染色了，列同理。

但是行和列可能有重叠的地方，操作途中不好模拟，所以我们可以离线处理。

初始化 $ans=n\times m$，我们计算每一列有哪些位置是空白的，最终减去便是正确答案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,k,op,x,ans,a[500005],b[500005];
map<int,int>aa;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
	}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
main(){
//	freopen("paint4.in","r",stdin);
//	freopen("p.out","w",stdout);
	n=read(),m=read(),q=read(),k=read();
	ans=n*m;
	while(q--){
		op=read(),x=read();
		if(op==1){
			a[x]++;
			a[x]%=k;
		}else{
			b[x]++;
			b[x]%=k;
		}
	}
	for(int i=1;i<=m;i++)aa[b[i]]++;
	for(int i=1;i<=n;i++)ans-=(aa[-a[i]]+aa[k-a[i]]);
	cout<<ans<<endl;
	return 0;
}
```

完结撒花！

---

## 作者：哈哈人生 (赞：2)

## 题外话
这题还算简单，基本一眼就能看出方法。

## 思路
其实每一次变化的都是一行或者一列的数加一，最后统计的就是有多少个位置的数取模 $k$ 不为零。

直接模拟可以拿部分分，但看数据范围就知道会有一部分数据超时。

其实我们可以统计取模 $k$ 为零的位置，最后再用 $n \times m$ 减去它即可。求这个数我们可以用桶，去看它能组成多少个能被 $k$ 整除的数，行和列分别要用不同的桶统计哦。这样就把复杂度降到线性了。

具体来说，桶统计的就是行和列分别被修改的次数，过程取模，最后用 $ans$ 加上每个能互相组成 $k$ 的桶中的数的乘积（实现时就是从头到尾两边遍历），别忘了是 $0$ 的桶也要算上哦。

## 代码
听不懂看这里，代码不抽象。
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int n,m,q,k,op,x,h[200005],l[200005],mp[500005],mp2[500005];

unsigned int ans=0;

signed main() {

	ios::sync_with_stdio(false);

	cin.tie(0),cout.tie(0);

	cin>>n>>m>>q>>k;

	while(q--) {

		cin>>op>>x;

		if(op==1)h[x]++,h[x]%=k;//取模很重要，不然就爆掉

		else l[x]++,l[x]%=k;

	}

	for(int i=1; i<=n; i++)mp[h[i]]++;//桶

	for(int i=1; i<=m; i++)mp2[l[i]]++;

	ans+=mp[0]*mp2[0];//本身是0，统计

	for(int i=0; i<k; i++)ans+=mp[i]*mp2[k-i];//相加为k，统计

	cout<<n*m-ans;

	return 0;
}
```
请读者诚信粘贴题解，遵守洛谷社区守则，最后，点个赞吧。

---

## 作者：so_find_skind (赞：1)

这里介绍一种我自己想出来的方法（而且貌似就我一个人这么写 AC 了！）。

首先，一个格子最后变成空白的话，说明它一共被涂了 $pk$ 次（$p$ 为常数）。

但是，对数量巨大的格子进行一次次操作，想 AC 是不可能的，那该怎么办呢？

其实题目中说到了，每次涂色都是**一整行**涂色或**一整列**涂色，所以，我们实际上完全可以只模拟**每行**和**每列**，即用两个数组存**每行的总涂色次数**和**每列的总涂色次数**，代码：

```
while(q--){
        cin>>op>>x;
        op==1?s[x]++:t[x]++;
    }
```

这个点很多人都想的出来，所以真正的问题，就是该如何算出一个**方格**的总操作次数呢？

其实也不难。

如下图，标示出了方格 $Q$，这个位置，同时属于也只属于第四行与第三列，也就是说，若是第四行涂色了 $x$ 次，第三列涂色了 $y$ 次，那么，方格 $Q$ 一定涂色了 $x+y$ 次（这个应该容易理解吧）。

![](https://cdn.luogu.com.cn/upload/image_hosting/iifejgf9.png)

此外，根据余数的可加性，即 $x \ \bmod k+y\ \bmod k=(x+y)\ \bmod k$，也就是说，若是一个在第 $i$ 行，第 $j$ 列格子最后变成了空白的，则一定有 $s_i\mod k+t_j\mod k=k$。

但是我们并不能直接 $O(nm)$ 把所有的格子都遍历一遍吧，那么该怎么做呢？

实际上也简单，那就是桶。

与 B 题不同的是，这次的桶储存的是每列的操作次数对 $k$ 取模的值，然后，再遍历每行，比如说现在到了第 $i$ 行，那么第 $i$ 行的所有格子中一定有且只有 $w[k-s_i\bmod k]$ （$w$ 是桶数组）个格子被涂过色且最后正好变成了空白的（容易证明，这里不再叙述，请读者自行推导）。

那么，求这个有什么用？

其实大佬肯定能看出来，用被**涂过色**的格子数减去**涂过色但是最后变成空白**的格子数，就是最后的答案。

被涂过色的格子数也简单，设有 $r$ 行**被涂过**，$g$ 列**被涂过**，那么被涂过色的格子数量就是 $rm+gn-rg$（你可以用容斥的思想推导出，这里就不具体推到了）。

光看文字可能不一定懂，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q,k,op,s[200005],t[200005],x,l,r,g,h,w[500005],ans;
int main(){
    cin>>n>>m>>q>>k;
    while(q--){
        cin>>op>>x;
        op==1?s[x]++:t[x]++;
    }
    for(int i=1;i<=n;i++){
        s[i]%=k;//为了方便，先取模
        if(s[i])//注意这里为了方便，舍去了不必要的一整行都是空白的情况
            g++;
    }
    for(int i=1;i<=m;i++){
        t[i]%=k;
        w[t[i]]++;//桶
        if(t[i])
            h++;
    }
    ans=g*m+h*n-g*h;
    for(int i=1;i<=n;i++){
        ans-=w[k-s[i]];//O(1)桶查找
    }
    cout<<ans;
    return 0;
}
```

线性时间复杂度，完全够用了。

---

## 作者：流光萤影 (赞：1)

## 前言：

**本题解使用语言：C++20 O2。**

## 正文：

**思路**：

用 $h$ 记录每次 $op = 1$ 的操作，用 $l$ 记录每次 $op = 2$ 的操作。

那么，若 $h _ i \times l _ i \bmod k \ne 0$，则代表此方格被染色了。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,h[200005],l[200005],q,k;
long long ans;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m >> q >> k;
    for(register int op,x;q;--q)
    {
		cin >> op >> x;
		if(op == 1) ++h[x];
		else ++l[x];
	}
	for(register int i(1);i <= n;++i) for(register int j(1);j <= m;++j) if((h[i]+l[j])%k) ++ans;
	cout << ans;
}
```

但是，$O(nm + q)$ 的时间复杂度会超时。

我们可以进一步优化：开一个桶 $t$，记录每一个 $l _ i$ 对 $k$ 取模的值。

则对于每一行：被涂色的方格数为 $m - t _ {k - h _ i \bmod k}$。

特别的，若 $h _ i \bmod k = 0$，则第 $i$ 行被涂色的方格数为 $m - t _ 0$。

这样，时间复杂度便可以降至 $O(n + m + q)$。

**AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,h[200005],l[200005],q,k,t[5000005];
long long ans;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m >> q >> k;
    for(register int op,x;q;--q)
    {
		cin >> op >> x;
		if(op == 1) ++h[x];
		else ++l[x];
	}
	for(register int i(1);i <= m;++i) ++t[l[i]%k];
	for(register int i(1);i <= n;++i) ans += m-t[h[i]%k?k-h[i]%k:0];
	cout << ans;
}
```

---

## 作者：liangjindong0504 (赞：1)

~~吐槽一句：大号打排名奇低，[小号](https://www.luogu.com.cn/user/977622)打排名老高。~~

忠告：用好大样例。

### **【主要思路】**

**【暴力思路】**

首先，不难想到使用最暴力的算法，每次操作看看有几个涂色，时间复杂度 $O(nq)$，肯定超时。

**【正解思路】**

正难则反。既然直接看有几个方格涂色的要超时，那我们就统计有几个方格未涂色。

$Que1$：什么情况下该方格没有涂色？

$Ans1$：设该方格涂了 $p$ 次，只要 $p \mid k$，该方格就没有涂色，换句话来说，$p$ 是 $k$ 的倍数就没有涂色。

再根据输入的信息，不难发现我们可以统计每行每列的涂色情况（每行或每列每个方格涂了几次）。

将统计每行、每列出现次数的两个数组全部模 $k$。

接下来，对于每个方格，仅需看它的行与列相加是否是 $k$ 或 $0$ 即可。时间复杂度 $O(n^2)$

好了，如果你想到这里，那么恭喜你，你的分数有 $45$ 了（也许吧，没试过，根据测试点范围猜的）！

当然，这里还是“正”的，但是这种方法可以引出正解。

枚举每行肯定不变，时间复杂度已经有 $O(n)$，这意味着每列必须在 $O(1)$ 的时间里计算完（```log n``` 不可能实现）。

每行都已被取模，假设这一行取模后为 $d$，那么这一行的每列被 $k$ 取模都必须是 $(n-d)\bmod k$。

基于此，不难想出再设一个数组存储每列被 $k$ 模以后的得数出现次数，就可以 $O(1)$ 求出每行有几个方格没有涂色。

有了上面的推理，统计答案也不难了，只需输出 $nm-s$ 即可。$s$ 为没涂色的方格数量。

**【代码&记录】**

最后，把代码奉上。（主函数代码）

重要的东西：

**不开 ```long long``` 见祖宗！**
```cpp
signed main(){
	//输入不讲 
	n=read();
	m=read();
	q=read();
	k=read();
	//统计每行每列涂色次数 
	while(q--){
		op=read();
		x=read();
		if(op==1){
			hang[x]++;
		}else{
			lie[x]++;
		}
	}
	//将每列余数出现次数存储 
	for(int i=1;i<=m;i++){
		yul[lie[i]%k]++;
	}
	//统计有几个方格没有涂色 
	for(int i=1;i<=n;i++){
		sum+=yul[(k-hang[i]%k)%k];
	}
	//最终答案 
	write(n*m-sum);
	//功德圆满 
	return 0;
} 
```
提交记录：[记录](https://www.luogu.com.cn/record/122929985)。

**【总结】**

本题并没有考察太多算法，但是这题充分考察了我们的代码能力，对于像我这样的初学者有很大的帮助。

---

## 作者：huoxin (赞：1)

# 题目大意

每个格子的值为这个格子所在的行与所在的列的值之和，求值不为 $k$ 的倍数的格子数量。

# 分析

注意到不需要关注每一个格子，只需要求总数即可。

所以可以先行与列的值求和，再统计列中有哪些值，再判断这些值能否与某些行构成 $k$ 的倍数即可。


# code

```cpp
#include<bits/stdc++.h>
//using namespace std;
const int maxn = 2e5+5;
const int maxq= 5e5 +5;
int l1[maxn],l2[maxn],s[maxq];
int main(){
	int n,m,q,k;long long ans=0;
	scanf("%d%d%d%d",&n,&m,&q,&k);
	for(int i=1;i<=q;++i){
		int o,x;
		scanf("%d%d",&o,&x);
		if(o==1){
			++l1[x];
			if(l1[x]==k)l1[x]=0;
			
		}
		if(o==2){
			++l2[x];
			if(l2[x]==k)l2[x]=0;
		}
	}
	for(int i=1;i<=m;++i)++s[l2[i]];
	for(int i=1;i<=n;i++){
		if(l1[i]==0)ans+=m-s[0];
		else ans+=m-s[k-l1[i]];
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：zzy0618 (赞：1)

### 解题思路

我们可以改变一下题意。

一个 $n\times m$ 的数组 $a$，初始全部为 $0$。每次可以将一排或一列全部加上 $1$。求最后有多少数取模于 $k$ 不为 $0$。

这下就要明朗上许多。然而 $n,m\le 2\times 10^5$，不谈时间，就开数组也不行。我们可以维护两个数组 $mx$ 和 $my$。$mx_i$ 表示第 $i$ 行加了多少次 $1$，$my_i$ 表示第 $i$ 列加了多少次 $1$。这样，最终的 $a_{i,j}$ 可以表示为 $mx_i+my_j$，操作复杂度从 $O(n)$ 降为 $O(1)$。

可是我们不能枚举行列，那样依然会超时。首先，在操作过程中不断对 $mx,my$ 进行取模，因为操作 $k$ 次等于没操作。最终我们的 $a$ 数组只会有两种情况，等于 $k$ 或者不等于 $k$，不可能是 $k$ 的倍数，当然为 $0$ 就无需考虑。

设 $mx$ 中不为 $0$ 的个数为 $s_1$，$my$ 中不为 $0$ 的个数为 $s_2$。如果没有等于 $k$ 的情况，我们可以发现最终答案 $ans=s_1\times m+s_2\times n-s_1\times s_2$。

对于有等于 $k$ 的情况，我们记录一个 $st$。$st_i$ 表示有多少个 $mx_j$ 的值为 $i$。这样只要枚举 $my$，将 $ans-st_{k-my_i}$。因为 $mx,my$ 均已取模，所以 $st$ 的大小只用为 $k$。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long//要开 long long 
using namespace std;
const int N=200005;
int n,m,q,k;
int opt,x,ans;
int s1,s2;
int mx[N],my[N],st[500005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q>>k;
	while(q--){
		cin>>opt>>x;
		if(opt==1)++mx[x],mx[x]%=k;
		else ++my[x],my[x]%=k;
	}
	for(int i=1;i<=n;i++)
		if(mx[i])
			st[mx[i]]++,s1++;
	for(int i=1;i<=m;i++)
		if(my[i])
			s2++;//计算 s1,s2,st 数组
	ans=s1*m+s2*n-s1*s2;
	for(int i=1;i<=m;i++)
		ans-=st[k-my[i]];
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

这道题并不难，但却把我卡在 $60$ 分无法自拔，赛后才灵光一闪，加了两个字符，对了。

我们可以统计每一行，每一列被整个涂色的次数，不难证明，如果某个对应的行的涂色数量加列的涂色数量是 $k$ 的倍数或 $0$，我们认为这个格子是白的，否则是有色的。

我们可以先考虑行，将不同余数的可能的存起来，设这些行都涂了色，并计算此时的答案，然后考虑列，对于每一列，计算它除以 $k$ 的余数，可以快速计算出另一个余数与它的和为 $k$ 的倍数的情况下的另一个余数，不难证明这一列上每一涂过色的行如果层数为这个余数，那么就将其变白。

最后在这一列加颜色，只要这一列的层数不是 $k$ 的倍数或 $0$，那么其它空白的行就可以涂。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[9][900009];//本来想评最短，但WA了
long long e;//不开long long见祖宗
long long n,m,q,k;
int main(){
	cin>>n>>m>>q>>k;
	for(long long i=1;i<=q;i++){
		long long o,z;
		cin>>o>>z;
		a[o][z]++;//方便处理，不用判断
	}
	for(long long i=1;i<=n;i++){
		
		if(a[1][i]){
		a[0][a[1][i]%k]++;//废物利用，将a数组压榨干净，统计对应余数的数量
			a[4][0]++;//统计被涂色的行，方便空白的行
			e+=m; //假设每一行都涂色成功
		}
	}
	for(long long i=1;i<=m;i++){
		e-=a[0][(k-a[2][i]%k)%k];//减去涂上这列后每一行变白的格子
		if(a[2][i]%k){//原来没写%k，样例全对，数据60（就不能按样例全对的面子上给个85？）
			e+=n-a[4][0];//涂上这一列空白的行
		}
	}
	cout<<e;//输出答案
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

[题目传送门](/problem/P9583)
# 思路
我们首先可以考虑纯模拟（每次操作暴力枚举修改），当然这样时间复杂度是 $O(nq)$，肯定太慢了。

既然不能暴力枚举修改，那我们将所有修改 $x$ 行的次数记为 $sum1_x$，将所有修改 $y$ 列的次数记为 $sum2_y$，最后枚举每个 $i$ 行 $j$ 列的点，如果这个点上有颜色，则涂的次数肯定**不**是 $k$ 的倍数，而涂的次数是 $sum1_i+sum2_j$，所以只要统计出所有满足 $(sum1_i+sum2_j)\bmod k\ne0$ 的点的个数即可。

但是这样还是太慢了。我们可以考虑反过来想，即所有点的个数减去不满足要求的点个数。不满足要求，就是指 $(sum1_i+sum2_j)\bmod k=0$。

我们设 $x=sum1_i\bmod k,y=sum2_j\bmod k$，如果 $x,y$ 都为 $0$ 或 $x+y=k$，则这个点不满足要求，我们可以定义两个桶 $tot1$ 和 $tot2$，$tot1_i$ 表示对于所有 $sum1_j$，$sum1_j\bmod k=i$ 的个数，$tot2_i$ 同理。根据乘法原理，所有答案就是 $tot1_i\times tot2_{(k-i)\bmod k}$（当然你也可以把 $i=0$ 的情况特殊处理）。最后别忘了答案要求的是合法个数而不是不合法个数，我们要用总数减去不合法个数。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll; //不开 long long 见祖宗
ll n, m, q, k, op, x, sum1[200005], sum2[200005], sum, tot1[500005], tot2[500005];
int main () {
	cin >> n >> m >> q >> k;
	while (q --) {
		cin >> op >> x;
		if (op < 2)
			++ sum1[x];
		else
			++ sum2[x];
	}
	for (ll i = 1; i <= n; ++ i)
		++ tot1[sum1[i] % k];
	for (ll i = 1; i <= m; ++ i)
		++ tot2[sum2[i] % k];
	for (ll i = 1; i < k; ++ i)
		sum += tot1[i] * tot2[k - i];
	cout << n * m - sum - tot1[0] * tot2[0]; //总数减不合法个数
	return 0;
}
```

---

## 作者：zct_sky (赞：0)

### Solution
-----
注意到 $n,m$ 范围为 $[1,2\times 10^5]$，所以暴力枚举肯定不行，考虑用桶记录行和列的涂色次数。

然后因为 $k$ 的范围为 $[1,5\times 10^5]$，所以可以再用桶来记录原来桶中涂色次数对 $k$ 取模的行列个数。 

记 $t_{0,i}$ 为涂色次数为 $i$ 次的行个数，$t_{1,i}$ 为涂色次数为 $i$ 次的列个数。

则若不计涂色为 $k$ 次的格子，有颜色的格子数应为 $(n-t_{1,0})\times m+(m-t_{0,0})\times n-(n-t_{1,0})\times(m-t_{0,0})$。

因为 $a_{i,j}$ 涂色次数也表示第 $i$ 行涂色次数和第 $j$ 行涂色次数和，或者说：每有一对行列涂色次数和为 $k$，就对应一个格子没有颜色。

那么实际上有颜色格子数还需减去 $\sum\limits_{i=1}^{k-1} t_{0,i}\times t_{1,k-i}$。

最后记得开 `long long`。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
const int N=2e5+7;
const int K=5e5+7;
int n,m,t1[2][N],t2[2][K],q,k;
ll ans;
int main(){
	n=read();m=read();q=read();k=read();
	for(int i=1;i<=q;i++){
		int op=read(),x=read();
		t1[op-1][x]++;
	}
	for(int i=1;i<=n;i++)
		t2[0][t1[0][i]%k]++;
	for(int i=1;i<=m;i++)
		t2[1][t1[1][i]%k]++;
	ans=1ll*(n-t2[0][0])*m+1ll*(m-t2[1][0])*n-1ll*(n-t2[0][0])*(m-t2[1][0]);
	for(int i=1;i<k;i++)
		ans-=1ll*t2[0][i]*t2[1][k-i];
	printf("%lld",ans);	
	return 0;
}
```

---

## 作者：Paris_Commune (赞：0)

### 前言

被 hack 了，更改了数组大小。

赛时忘了 $k$ 的倍数也会变成空白，事实上也写得不对。

### 正解

用 $h_i$，$l_i$ 存第 $i$ 行或列被涂了几次。

如果涂了 $i$ 层，则涂了 $i\bmod k$ 行。

再用 $v_i$ 表示有多少个涂了 $i$ 层的行。

### AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,k,l[500005],h[500005],v[500005],ans;
signed main(){
//	freopen("paint2.in","r",stdin);
	cin>>n>>m>>q>>k;
	for(int i=1;i<=q;i++){
		int op,x;
		cin>>op>>x;
		if(op==1){
			h[x]++;
		}
		else l[x]++;
	}
	for(int i=1;i<=n;i++){
		v[h[i]%k]++;
	}
	for(int i=1;i<=m;i++){
		if(l[i]%k==0)ans+=n-v[0];
		else ans+=n-v[k-l[i]%k];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：rainygame (赞：0)

这道题需要一点小技巧，不过感觉比 pjT3 简单了不少。

首先直接模拟肯定是不可能的，我们考虑特殊性质 A。这个非常简单，只需要记录每个行有多少次加和，如果这一行的次数不能整除 $k$ 就加一次 $m$，然后计算加了多少个 $m$ 即可。

但是现在多了一个列的加和，我们该怎么做呢？

正难则反，我们可以考虑求出每行有多少个可以整除 $k$ 的位置，假设这一行有 $a$ 次修改，那么我们可以考虑把 $k-a$ 给“凑”出来。

我们只需要查找一共有多少个 $k-a$ 次查询的，那么剩下的就是非空白的。

而这个找次数的可以使用 `upper_bound` 和 `lower_bound` 来实现。

注意前面所说的所有操作都是在模 $k$ 意义下进行的。

时间复杂度 $O(q+(n+m) \log m)$。

赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001

int n, m, q, k, opt, x, ans;
int cnt1[MAXN], cnt2[MAXN];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m >> q >> k;
    if (k == 1){
    	cout << 0;
    	return 0;
	}
    
    while (q--){
    	cin >> opt >> x;
    	if (opt == 1) cnt1[x] = (cnt1[x] + 1) % k;
    	else cnt2[x] = (cnt2[x] + 1) % k;
	}
	sort(cnt2+1, cnt2+m+1);
	for (int i(1); i<=n; ++i) ans += m-(upper_bound(cnt2+1, cnt2+m+1, (k-cnt1[i])%k)-lower_bound(cnt2+1, cnt2+m+1, (k-cnt1[i])%k));
	
	cout << ans;

    return 0;
}

```


---

## 作者：船酱魔王 (赞：0)

# P9583 涂色 题解

## 题意回顾

$ n $ 行 $ m $ 列方格，$ q $ 次整行或整列加一操作，求最后有多少个格子的数值模 $ k $ 非 $ 0 $。

$ 1 \le n,m \le 2 \times 10^5 $，$ 1 \le k \le q \le 5 \times 10^5 $。

## 分析

先预处理出对于所有行列的操作次数。

我们对于每一行，统计这一行内有多少模 $ k $ 余 $ 0 $ 的，最后答案为 $ n \times m $ 再减去这些即可。

对于所有模 $ k $ 余 $ 0 $ 的格子，显然组成他的行和列的操作数量的和模 $ k $ 余 $ 0 $。如果我们知道行的情况的话，显然可以知道如果格子模 $ k $ 余 $ 0 $，列需要满足的模 $ k $ 余数。

我们开桶子统计有多少列操作次数模 $ k $ 余每个数，然后对于每一行可以统计出答案。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
const int K = 5e5 + 5;
int n, m, q, k;
int a[N];
int b[N];
int ca[K];
int cb[K];
int main() {
	std::ios::sync_with_stdio(false);
	cin >> n >> m >> q >> k;
	int op, x;
	for(int i = 1; i <= q; i++) {
		cin >> op >> x;
		if(op == 1) {
			a[x]++;
		} else {
			b[x]++;
		}
	}
	long long ans = (long long)n * m;
	for(int j = 1; j <= m; j++) {
		cb[b[j] % k]++;
	}
	for(int i = 1; i <= n; i++) {
		ans -= cb[k - (a[i] % k)];
		if(a[i] % k == 0) {
			ans -= cb[0];
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

