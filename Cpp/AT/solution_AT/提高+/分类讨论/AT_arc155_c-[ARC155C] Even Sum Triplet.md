# [ARC155C] Even Sum Triplet

## 题目描述

给定两个长度为 $N$ 的整数序列 $A=(A_1,\ A_2,\ \dots,\ A_N)$ 和 $B=(B_1,\ B_2,\ \dots,\ B_N)$。

你可以进行任意次如下操作：

- 选择一个整数 $i\ (1\leq i\leq N-2)$，使得 $A_i+A_{i+1}+A_{i+2}$ 是偶数。然后将 $A_i,\ A_{i+1},\ A_{i+2}$ 按任意顺序重新排列。

请判断是否可以通过若干次操作使 $A$ 变为 $B$。

## 说明/提示

### 限制条件

- $3\leq N\leq 2\times 10^5$
- $1\leq A_i,\ B_i\leq 2\times 10^5$
- 所有输入的值均为整数

### 样例解释 1

$A_1+A_2+A_3=1+2+3=6$ 是偶数，因此可以选择 $i=1$ 进行操作。选择 $i=1$ 并将 $A_1,\ A_2,\ A_3$ 重新排列为 $A_3,\ A_1,\ A_2$，则 $A$ 变为 $(3,\ 1,\ 2,\ 4,\ 5)$。通过此操作可以使 $A$ 变为 $B$，因此输出 `Yes`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2 3 4 5
3 1 2 4 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5
1 2 4 6 5
5 1 4 2 6```

### 输出

```
No```

## 样例 #3

### 输入

```
9
2 10 4 3 6 2 6 8 5
2 4 10 3 8 6 6 2 5```

### 输出

```
Yes```

# 题解

## 作者：teylnol_evteyl (赞：9)

一道大分类讨论。

如果有一个可以交换的段包含奇数，那么你可以把所有奇数移到最左边并任意调整相对顺序，然后回到任意一种有一个可以交换的段包含奇数的状态。这种情况，如果偶数的数量为 $2$，这两个偶数是不能交换相对位置的，有至少 $3$ 个偶数就能交换偶数间相对位置。所以只需要判断 $a$ 和 $b$ 中的数是否相同以及两个偶数的相对位置即可。

如果没有一个可以交换的段包含奇数，则所有奇数都不能移动，同时奇数把整个序列分成几段，每一段中如果只有 $2$ 个偶数，那不能移动；如果有至少 $3$ 个偶数，那么块内的偶数是可以移动的。所以要判断 $a$ 是奇数的位置和 $b$ 是否相同，然后在每一段内判断 $a$ 和 $b$ 中的数是否相同以及两个偶数的段是否位置对应相同。

```
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, a[N], b[N];
int cnt[N];

bool check(int l, int r)
{
	if(l > r) return false;
	if(l == r && a[l] == a[r]) return false;
	if(r - l == 1)
	{
		if(a[l] == b[l] && a[r] == b[r]) return false;
		else return true;
	}
	for(int i = l; i <= r; i ++ ) cnt[a[i]] ++ ;
	for(int i = l; i <= r; i ++ )
	{
		if(!cnt[b[i]]) return true;
		cnt[b[i]] -- ;
	}
	return false;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i ++ ) scanf("%d", &b[i]);
	
	bool flag = true;
	for(int i = 1; i <= n - 2; i ++ )
		if((a[i] + a[i + 1] + a[i + 2]) % 2 == 0 && (a[i] % 2 || a[i + 1] % 2))
			flag = false;
	
	if(flag)
	{
		for(int i = 1; i <= n; i ++ )
			if(a[i] % 2 && a[i] != b[i])
			{
				puts("No");
				return 0;
			}
		int l = 1;
		for(int i = 1; i <= n; i ++ )
			if(a[i] % 2)
			{
				if(check(l, i - 1))
				{
					puts("No");
					return 0;
				}
				l = i + 1;
			}
		if(check(l, n)) puts("No");
		else puts("Yes");
	}
	else
	{
		if(check(1, n)) puts("No");
		else
		{
			bool flag = true;
			for(int i = 1; i <= n - 2; i ++ )
				if((b[i] + b[i + 1] + b[i + 2]) % 2 == 0 && (b[i] % 2 || b[i + 1] % 2))
					flag = false;
			if(flag) puts("No");
			else
			{
				int oc = 0;
				for(int i = 1; i <= n; i ++ )
					if(a[i] % 2 == 0)
						oc ++ ;
				if(oc != 2) puts("Yes");
				else
				{
					int fo;
					for(int i = 1; i <= n; i ++ )
						if(a[i] % 2 == 0)
						{
							fo = a[i];
							break;
						}
					for(int i = 1; i <= n; i ++ )
						if(b[i] % 2 == 0)
						{
							if(b[i] == fo) puts("Yes");
							else puts("No");
							return 0;
						}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：Leasier (赞：9)

满足条件的情况仅有两种：

- $A_i, A_{i + 1}, A_{i + 2}$ 中恰好有一个偶数。
- $A_i, A_{i + 1}, A_{i + 2}$ 全是偶数。

对于第二种情况，随便操作都不影响其他部分是否可以操作，所以你咋搞都可以。

现在开始分类讨论：

1. 无法进行第一种操作

此时我们可以对每个极长全偶连续段进行排序。

2. 可以进行第一种操作

此时我们可以将那个偶数的位置随便移动。考虑把偶数和奇数分开，此时我们可以随便排列所有奇数，但必须出现至少三个偶数才能改变偶数间的相对顺序。

不难发现这个过程是可逆的，于是我们对 $A, B$ 分别进行上述变换并判断变换后是否相同即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int a[200007], b[200007], cnt[7], val[7][200007];

inline void transform(int a[], int n){
	bool flag = false;
	for (int i = 1; i + 2 <= n; i++){
		if (a[i] % 2 + a[i + 1] % 2 + a[i + 2] % 2 == 2){
			flag = true;
			break;
		}
	}
	if (!flag){
		for (int i = 1; i <= n; i++){
			int pos = i;
			while (pos <= n && a[pos] % 2 == 0) pos++;
			if (pos - i >= 3) sort(a + i, a + pos);
			i = pos;
		}
	} else {
		int cur = 0;
		cnt[0] = cnt[1] = 0;
		for (int i = 1; i <= n; i++){
			int type = a[i] % 2;
			val[type][++cnt[type]] = a[i];
		}
		for (int i = 0; i <= 1; i++){
			for (int j = 1; j <= cnt[i]; j++){
				a[++cur] = val[i][j];
			}
		}
		sort(a + cnt[0] + 1, a + n + 1);
		if (cnt[0] >= 3) sort(a + 1, a + cnt[0] + 1);
	}
}

int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++){
		cin >> b[i];
	}
	transform(a, n);
	transform(b, n);
	for (int i = 1; i <= n; i++){
		if (a[i] != b[i]){
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
一道还不错的分类讨论题，本身涉及的知识点不多，就是细节比较多，细心点调是没有什么大问题的。

题意简述：给定两个长为 $n$ 的序列 $a$ 和 $b$。选定一个 $i$ 使其满足 $1\leq i\leq n-2$ 的条件。如果 $a_i+a_{i+1}+a_{i+2}$ 的值为偶数，那么可以任意交换这三个数。请问能否通过这种操作使得序列 $a$ 变成序列 $b$。
## 分析。
根据我们小学的知识，我们不难发现，如果保证三个数的和为偶数，那么仅存在两个情况：要么均是偶数，要么一个偶数，两个奇数。

我们先从一个奇数，两个偶数的情况入手。考虑构造。分成两个情况：在 $a_i$ 前的数的奇偶性来分类讨论。设 $a_i$ 为偶数且 $a_{i+1}$ 和 $a_{i+2}$ 均是奇数。如果 $a_{i-1}$ 为偶数，那么必定能够使 $a_{i-1}$ 移动到 $a_{i+2}$ 后面去，且前面的序列不变，同时构造除了一个新的区间及 $a_i+a_{i+1}+a_{i+2}$ 放在前面。举个例子：
```
1 2 5 7 //因为1，2，5的和为偶数，所以符合条件，交换1和5的位置。
5 2 1 7 //因为2，1，7的和为偶数，所以符合条件，交换位置。
5 7 2 1 //因为5，7，2的和为偶数，所以符合条件，交换位置。
2 5 7 1 //注意此时存着一个新的区间即2 5 7。
```
事实上，我们不难将其拓展到一般情况下，因为在其中的交换对于任意的这种情况都是可以构造出来的。同理，如果我们将 $a_{i-1}$ 看做是偶数，那么通过交换 $a_i$ 和 $a_{i+1}$ 以及 $a_{i+2}$ 的位置即可使 $a_{i-1}$ 和 $a_{i+1}$ 与 $a_{i+2}$ 构成一个新的区间。举个例子：
```
2 4 5 7 //4+5+7为偶数，所以交换。
2 5 7 4 //此时2+7+5为偶数，构成一个新的。
```
仍然可以拓展到一般情况。所以我们可以得出结论：相邻的三个数中有一个偶数，两个奇数时，这两个奇数可以一起向左边或者右边移动（右边和上面的左边同理）一位，构造出一个新的合法区间。那么我们在任意交换的过程中，考虑每一个数的相对位置的变化情况。我们不妨设有两个奇数 $f$ 和 $s$ 存在。同时有一个合法区间 $x+y+z$ 存在（这个区间仍然是第一个数为偶数，后两个数为偶数）。那么我们显然可以让 $s$ 和 $x+y$ 组合成为一个新的区间，然后 $i$ 也可以同 $x+y$ 组合，然后通过移动，我们就可以再使得 $x+y+z$ 的区间再次存在，所以此时我们可以总结出一个规律：如果三个数可以组成一个合法区间，那么奇数的相对顺序可以随意改变，并且偶数的相对顺序不变。

注意到，在一个偶数，两个奇数的情况下，偶数的顺序是不会受到影响的，而可以改变相对顺序的只能是三个偶数的情况，此时因为均是偶数，所以可以任意交换，使得其相对顺序改变。此时算法就很显然了，先去判断一下是否存在合法区间然后分成是否存在三个偶数的合法区间，如果 $a$ 和 $b$ 均有，那么肯定可以，如果只有一个存在那么不行。如果两个都没有，判断一些奇数和偶数的相对位置能不能对应即可。相应的，如果序列中只有 $1$ 个或者 $2$ 个偶数，此时偶数的相对顺序是固定的，则直接暴力判断偶数的相对顺序能否对应即可。剩下的都是奇数的情况，都是奇数肯定交换不了，所以判断一下是否严格上下对应，直接输出即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n,a[200005],b[200005];
int a2[200005],b2[200005],flag;
int tot1,tot2,sum;
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
bool cheak1(){
	sum=0;
	for(int i=1;i<=n-2;i++){
		if(((a[i]&1)+(a[i+1]&1)+(a[i+2]&1))==2){
			tot1=tot2=0;
			//判断一些偶数的移动情况。 
	        for(int i=1;i<=n;i++){
		        if(!(a[i]&1)){
				    a2[++tot1]=a[i];
				}
		        if(!(b[i]&1)){
				    b2[++tot2]=b[i];
				}
        	}
	        if(tot1==2&&a2[1]!=b2[1]){//只有两个偶数
		        return 0;
	        } 
	        return 1;
		}
	}
	for(int i=1;i<=n;i++){
		a2[i]=a[i];
		b2[i]=b[i];
		//记得还原一些。 
	}
	for(int i=1;i<=n;i++){
		if((a2[i]&1)&&(a2[i]!=b2[i])){
			return 0;
		}//奇数不对于，相对位置不可改变。 
		if(a2[i]&1){
			sort(a2+sum,a2+i);
			sort(b2+sum,b2+i);
			for(int j=sum;j<=i-1;j++){
				if(a2[j]!=b2[j]){
					return 0;
				}
			}
			if(((i-1)-sum)==2&&a[i-1]!=b[i-1]){
				return 0;
			}
			sum=i;
		}
	}
	sort(a2+sum,a2+n+1);
	sort(b2+sum,b2+n+1);
	if(n-sum==2&&a2[n]!=b2[n]){ 
		return 0;
	}
	return 1;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		a2[i]=a[i];
	}
	for(int i=1;i<=n;i++){
		read(b[i]);
		b2[i]=b[i];
	}
	//记录序列。 
	sort(a2+1,a2+n+1);
	sort(b2+1,b2+n+1);
	//排序用来判断是否存在的数相同。 
	for(int i=1;i<=n;i++){
		if(a2[i]!=b2[i]){
			printf("No");
			return 0;
		}//有的数个数不同，不能构造。 
	}
	for(int i=1;i<=n;i++){
		if(a[i]&1){
			flag=1;
			break;
		}//奇数。 
	}
	if(!flag){
		cout<<"Yes\n";
		return 0;
	}//均是一种数合法的情况，肯定可以。 
	if(!cheak1()){
		cout<<"No\n";
		return 0;
	}
	for(int i=1;i<=n;i++){
	    swap(a[i],b[i]);
	}
	if(!cheak1()){
		cout<<"No\n";
		return 0;
	}
	cout<<"Yes\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_Imaginary_ (赞：1)

### 前言

比赛时死活调不出来，赛后 2 分钟就 AC 了，成功错失一次蓝名的好机会。

## Problem

给你两个数列，可以进行如下操作：

选取连续 3 个数，如果它们的和是偶数，那么可以随便排列。

问第一个能否变成第二个。

## Solution

最简单的，如果组成两个数列的数不全一样，直接寄。这个开个桶或者排序一遍都可以。考虑剩下来的情况。

一个直观的想法是，按奇偶分类。可以发现，能够操作当且仅当：

- 三个偶数

- 一个偶数两个奇数


可以发现，在一堆连续偶数中，只要超过 2 个，就可以随便排列。

首先，如果所有的奇数都动不了，那么除非这些奇数本来 $A$ 和 $B$ 就对应相同，否则肯定寄。

举个例子：

```
9 8 2 4 3 4 6 3
9 2 4 8 3 6 4 3
```

当 $A$ 和 $B$ 的奇数对应相同时，所有偶数被分成了若干块，只能在块内移动。所以，开个桶比较每个块内是否对应相同即可。

在上面的例子中，`4 6` 不能变成 `6 4`，所以寄了，由此：

**特判**：如果一个块内只有两个偶数，那它们不能移动。

现在，只要有一个奇数能动，那就可以把两个奇数并在相邻的两项。

举例：

```
1 1 [4 5 1] 4
1 1 [1 5 4] 4
```

记 `0` 为偶数，`1` 为奇数，那么 `1 0 1 -> 1 1 0`，所以可以并在一起。

并在一起后，还可以平移：`1 1 0 <-> 0 1 1`；

它们还能交换顺序：`1 3 2 <-> 3 1 2`；

对于一长串的 `1`，可以整体平移：

```
111110
111011
101111
011111
```

感性理解可知，每次可以选一长串的奇数，不断把别的奇数并进来，直到形成一大串，然后移到最左端。

此时，所有偶数都在最右端。

根据前面提到的，奇数之间可以借助偶数交换相邻两个，所以不断地操作可以把奇数进行排序。

**注意特判只有两个偶数的情况**：如果偶数的个数超过 3 个，那么可以用操作随便乱动。否则，偶数的**相对位置**就被定死了。

最后，所有操作都是可逆的，那么如果 $B$ 也能类似操作成一堆奇数在最左边，就可行。

如果 $B$ 不能呢？那肯定寄了。因为 $A$ 能操作到的都是能够进行操作的数组。

我的处理方法是：把 $A$ 和 $B$ 交换，再看看行不行。

具体看代码。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=200005;
int n;
int a[N],b[N],c[N],d[N];
bool check()// 如果奇数可以移动，检查偶数
{
	int t1=0,t2=0;
	for(int i=1;i<=n;i++)
	{
		if(!(a[i]&1)) c[++t1]=a[i];
		if(!(b[i]&1)) d[++t2]=b[i];
	}
	if(t1==2&&c[1]!=d[1])// 只有两个偶数
	{
		return 0;
	}
	return 1;
}
bool solve()
{
	for(int i=1;i<=n-2;i++)
	{
		int t=(a[i]&1)+(a[i+1]&1)+(a[i+2]&1);
		if(t==2)
			return check();
	}
	int lst=0;
	for(int i=1;i<=n;i++)
	{
		c[i]=a[i];
		d[i]=b[i];
	}
	for(int i=1;i<=n;i++)
	{
		if((c[i]&1)&&(c[i]!=d[i]))//奇数不对应相同，且不能移动，一定不行
			return 0;
		if(c[i]&1)
		{
			sort(c+lst,c+i);
			sort(d+lst,d+i);
			for(int j=lst;j<=i-1;j++)//这一块内偶数的构成不同
				if(c[j]!=d[j])
					return 0;
			if((i-1)-lst==2&&a[i-1]!=b[i-1])//检查2个偶数的问题
				return 0;
			lst=i;
		}
	}
	sort(c+lst,c+n+1);
	sort(d+lst,d+n+1);
	if(n-lst==2&&c[n]!=d[n])//检查2个偶数的问题
	{
		return 0;
	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		c[i]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		d[i]=b[i];
	}
	sort(c+1,c+n+1);
	sort(d+1,d+n+1);
	for(int i=1;i<=n;i++)
	{
		if(c[i]!=d[i])
		{
			printf("No");
			return 0;
		}
	}
	bool ok=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]&1)
		{
			ok=1;
			break;
		}
	}
	if(!ok)
	{
		printf("Yes");
		return 0;
	}
	bool t1=solve();
	if(!t1)
	{
		printf("No");
		return 0;
	}
	for(int i=1;i<=n;i++) swap(a[i],b[i]);
	bool t2=solve();
	if(!t2)
	{
		printf("No");
		return 0;
	}
	printf("Yes");
	return 0;
}

```

---

