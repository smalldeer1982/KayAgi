# [ARC133A] Erase by Value

## 题目描述

给定一个整数序列 $A$，其中包含 $N$ 个元素 $A_1,A_2 \cdots A_N$ 。

小 S 现在要从 $A$ 中选择一个值 $x$。然后，他会按照元素在 $A$ 中的原始顺序，将不等于 $x$ 的元素组成一个新的整数序列 $a$。

请找出所有可能的 $a$ 序列中，字典序最小的那一个。

## 说明/提示

#### 制约
- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 所有的输入都是整数
#### 样例 1 解释
在这个样例中，如果选择 $x=2$，则 $a=(4,4,1)$。此外，如果选择 $x=4$，则 $a=(2,1,2)$，这时字典序是最小的。
#### 样例 2 解释
如果选择 $x=1$，则 $a$ 将为空，这显然是字典序最小的。另外，输出中可以包含额外的空格或换行符，不影响结果。

## 样例 #1

### 输入

```
5
2 4 4 1 2```

### 输出

```
2 1 2```

## 样例 #2

### 输入

```
3
1 1 1```

### 输出

```
```

## 样例 #3

### 输入

```
5
1 1 2 3 3```

### 输出

```
1 1 2```

# 题解

## 作者：David_yang (赞：3)

[传](https://www.luogu.com.cn/problem/AT_arc133_a)送[门](https://atcoder.jp/contests/arc133/tasks/arc133_a)

第二篇题解（本来是第三篇，第二篇被打回了，然后题解通道就被关闭了......），如有不妥请~~忽视~~指出。

## 题目大意：

给定一个数组，要求将其中一种数字全部删除，使最后的数组字典序最小。

## 算法：

贪心

## 解析：

首先我们来想“亿”想，哪些因素会影响字典序？第一个是每个字母本的 ASCII 码，第二个才是它的长度。我最开始走入了一个误区：我总觉得删的数字越多越好，直到后来才想起这只是次要的，最主要的是前面的数字要尽量小。

那怎么让前面的数字尽量小呢？我们可以以样例 $1$ 为例子。假设我们删去了第一个数字，那么整个数组变成了 $4$ $4$ $1$，和最开始的 $2$ $4$ $4$ $1$ $2$ 比起来开头的 $4$ 反而比 $2$ 大，那肯定不行。所以就可以得出一个结论：删去数字后后面补上来的数字要比删去的数字小。

还有一个小的点要注意，那就是碰到第一个比它前面小的数字时就得立马删去前面那一个数字。因为我们比较两个字符串时是不是先比首位，首位相同比第二位，第二位相同就比第三位，以此类推。所以只要你这一位比别人大，后面的再小也没用。

针对样例 $3$ ，是不是没有一个数比前面的小？不过没关系，你再看看前面影响字典序的因素，第一个条件满足了，那么只需要让它变短就行了，所以我们只需要删除最后的数字就行了。

这几点都讲完了，那么代码也就呼之欲出了。下面是我写的代码，希望配合了注释后你能理解。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],t;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",a+i);		//小技巧：如果你不想打取地址符，可以这样写。因为a就代表a[0]的地址，加上几就是a几的地址。
	}
	for(int i=0;i<n;i++)
	{
		if(i==n-1)				//如果前面一直没找到，那么删最后的数字就行了。
		{
			t=a[i];
			break;
		}
		if(a[i]>a[i+1])
		{
			t=a[i];				//记录要删去的数字。
			break;				//找到后直接退出就可以了。
		}
	}
	for(int i=0;i<n;i++)
	{
		if(a[i]!=t)
		{
			printf("%d ",a[i]);
		}
	}
	printf("\n");				//最好输出一个换行，因为这是at的题。
	return 0;
}
```

注：代码已 AC，请放心食用。

最后，浏览过看过也要赞过。

---

## 作者：CleverPenguin (赞：2)

## 声明：本题解是对 HPY_xiaxii 贪心做法的证明。

[原文传送](https://www.luogu.com.cn/blog/HPY-xiaxi/solution-at-arc133-a)

算法：贪心。

考虑过程：要求结果的字典序要最小，由于字典序是从前往后的排序，所以，只需要从前向后，选择第一个大于后面一个数的位置，删除所有和它一样的数。

证明：设 $a_1$ 大于 $a_2$。

如果不删 $a_1$，删 $a_i$（$a_1$ 与 $a_i$ 不相同）：那么在 $a_1$ 位置上，因为 $a_1$ 大于 $a_2$，所以不删 $a_1$ 的字典序仍然大于删 $a_1$ 后的数组，因此，应当在第一次出现比下一个数大的时候就就删除它和与它相同的值。

贪心得证。

**注意：如果数组单调不递减，则选择最后一个值，删除它和与它相同的值，若所有数相同，则没有输出。**

代码参考原文。

---

## 作者：pfrig729 (赞：2)

~~写完翻译写题解~~
### 题意
给定一个整数数组 `a`，你从中选出一个值 `x` 删除，使剩下的部分字典序最小。
### 分析
1. 首先，定义一个结构体数组 `b`，存储每一个值第一次出现的位置 `fir` 以及它本身 `bi`（因为后面要排序会打乱顺序所以就不能用下标来存储了），此操作在输入时执行即可。

2. 接下来，对 `b` 数组进行排序。为了使剩下的部分字典序最小，对于删除的数 `x`，我们就要使其尽量靠前且删除后替代它的值（也就是 `x` 后面的那一个值）比 `x` 小，越合适的 `x`，我们将它放在 `b` 数组的越后面。

3. 最后，遍历原数组，如果 `a[i]` 等于 `b[n].bi`（也就是最适合当 `x` 的数），那么 `continue`，否则输出。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[200005];
struct _
{
	int bi,fir;//bi存储该值，fir表示该值第一次出现的位置
	bool yn=0;//用于判断是否是第一次出现
}b[200005];//存储a数组中的每一个值
inline bool cmp(const _ &x,const _ &y)
{
	if(x.fir<y.fir)
	{
		if(a[x.fir]>=a[x.fir+1])return 0;
		return 1;
	}
	else
	{
		if(a[y.fir]>a[y.fir+1])return 1;
		return 0;
	}
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		b[i].bi=i;//在读入时就顺便把每一个值存储了
		if(b[a[i]].yn==0)//如果没出现过
		{
			b[a[i]].yn=1;//记录
			b[a[i]].fir=i;//存储
		}
	}
	//注意刚刚读入时的循环，存储时第一次出现的位置是b[a[i]]，存储值是b[i]
	stable_sort(b+1,b+n+1,cmp);
	for(register int i=1;i<=n;++i)
	{
		if(a[i]==b[n].bi)continue;
		printf("%d ",a[i]);
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/144019446)

---

## 作者：Tracy_Loght (赞：1)

### 题目简介：
给定一个长度为 $N$ 的整数序列 $A$，从其中选择一个值 $x$。

将不等于 $x$ 的元素按照原始顺序组成一个新的整数序列 $a$。

要求输出所有可能的 $A$ 中字典序最小的那个序列。
### 想法：
#### 制约
- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 所有的输入都是整数

不得不说只有 200000 的限制，暴力就行。

暴力递推 `if(o[i]>o[i+1])`，找到后就记录答案，最后循环一遍就行。


```cpp

#include<bits/stdc++.h>
using namespace std;
long long n,ans;
long long o[200005];
int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++) std::cin>>o[i];//读入
	o[n+1]=-2133;//以防为纯上升子序列
	for(int i=1;i<=n;i++){
		if(o[i]>o[i+1]){//找到第一次大于情况就退出
			ans=o[i];
			break;
		}
	} 
	for(int i=1;i<=n;i++){
		if(o[i]!=ans)cout<<o[i]<<" ";	//输出没有 ans 的序列
	}
    return 0;
 } //完结撒花


---

## 作者：max666dong123 (赞：1)

## 题意
题目说给一个数字序列 $A$，删一个相同的数 $x$，使序列 $A$ 字典序最小。
## 思路
可以用贪心来解答，从第一个样例中我们就可以看出，把第一个下降的数字前一个的数字删掉。

第一组样例：
```cpp
5
2 4 4 1 2
```
可以看到是删除的 $4$，正好是第一个下降的 $1$ 前面的 $4$。

证明：设数列为 $a_1,a_2,a_3,a_4\dots a_n(a_1 \le a_2 \le a_3\le \dots a_n)$，这时来了一个 $x(x\le a_n)$，那么 $x$ 改为 $a_n$ 字典序一定会变小。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],n;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i-1]>a[i]){
			ans=a[i-1];
//			cout<<ans<<endl; 
			for(int j=1;j<=n;j++){
				if(a[j]==ans){
					continue;		
				}
				else{
					cout<<a[j]<<" ";
				}
			} 
			return 0;
		}
	}
	ans=a[n];
	for(int i=1;i<=n;i++){
		if(a[i]==ans){
			continue;		
		}
		else{
			cout<<a[i]<<" ";
		}		
	}
	
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)

# AT_arc133_a [ARC133A] Erase by Value 题解

[题面](https://www.luogu.com.cn/problem/AT_arc133_a)

## 思路

- 因为题目要求的是字典序最小，所以我们可以用贪心求解此题。

- 我们只需要从前往后找到值最大并且最靠前的 $x$。

- 也就是从前往后找如果 $a_x \le a_{x+1}$ 那么就继续往下找，否则就停止。

- 最后去除掉值等于 $a_x$ 的数输出就可以了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=200001;
int n,a[maxn];
int mp[maxn];
int pre[maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int id=0;
	while(id+1<=n&&a[id]<=a[id+1])
	{
		id++;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[id])
		{
			cout<<a[i]<<' ';
		}
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：MassPoint (赞：0)

## 思路

用贪心来做。只要找到整个 $a$ 数组的第一个上升子序列的末尾的元素 $ans$，再把数组中和 $ans$ 相等的数字删去即可。

证明如下：

设 $k$ 为 $a$ 数组的第一个上升子序列的末尾的元素的下标。

当 $k < n$ 时，因为 $a_{k}$ 小于 $a_{k+1}$，删去 $a_{k+1}$ 更优。

当 $k = n$ 时，因为 $a_{k}$ 为 $a$ 数组中的最大值，所以删去 $a_k$ 最佳。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
long long a[200002];
int n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	a[n+1]=-inf;	//防止 a 为纯上升序列时找不到 ans。
	for(int i=1;i<=n;i++)
		if(a[i]>a[i+1]){
			ans=a[i];
			break;
		}
	for(int i=1;i<=n;i++)
		if(a[i]!=ans)
			cout<<a[i]<<" ";
	cout<<endl;	//AT 题注意换行。
	return 0;
}
```

---

## 作者：Chillturtle (赞：0)

~~题解区全是同学（捂头）~~

# 题意

先输入 $n$，然后在数组 $a$ 里选出一个数 $x$，删掉所有 $x$，求最后留下数组的字典序最小。

# 思路

~~灰常简单~~，这是一道经典的贪心题目，先说结论：

- 从前往后循环，遇到第一个 $a_i$ 大于 $a_{i+1}$ 时，删除所有 $a_i$ 即可。
- 特别的，在整个数组中都没有符合上述条件时，直接删除最后一个即可。

**证明**如下：

- 当我们遇到 $a_i$ 大于 $a_{i+1}$ 时，如果删去 $a_i$ 那么留下的即是 $a_{i+1}$，如果删去 $a_{i+1}$ 留下的就是 $a_i$。因为 $a_i$ 大于 $a_{i+1}$ 所以删去 $a_i$ 一定优于删去 $a_{i+1}$。
- 第二种情况，即全数列为单调不减数列，则全数列最大值即为最后一个，所以删除最后一个即可。

由此，得证。

# AC code

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=2e5+10;
using namespace std;
int a[N];
int n;
signed main(){
	cin>>n;
	int jl=-1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(a[i]>a[i+1]){
			jl=a[i];
			break;
		}
	}
	if(jl==-1){
		jl=a[n];
	}
	for(int i=1;i<=n;i++){
		if(a[i]!=jl){
			cout<<a[i]<<" ";
		}
	}
	cout<<endl;
return 0;
}
```

---

## 作者：qiuzijin2026 (赞：0)

# [ARC133A] Erase by Value

## [题面](https://www.luogu.com.cn/problem/AT_arc133_a)

## 思路

贪心题。

结论：找到第一个 $a_{i}$ 使得 $a_{i}>a_{i+1}$ 删掉 $a_{i}$ 即可。

证明：设 $a_{i}$ 第一个使 $a_{i}>a_{i+1}$ 成立的数。

如果不删 $a_{i}$ 则第 $i$ 个位置的数为 $a_{i}$。

如果删 $a_{i}$ 则第 $i$ 个位置的数为 $a_{i+1}$。

因为 $a_{i}>a_{i+1}$，所以删 $a_{i}$ 的字典序比不删 $a_{i}$的字典序小。

得证。

**注意，如果不存在一个 $a_{i}$ 使得 $a_{i}>a_{i+1}$，则删掉最后一个数即可。**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[200005];
int ans;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i++)
		if(a[i]<a[i-1]){
			ans=a[i-1];
			break;
		}
	if(ans==0) ans=a[n];
	for(int i=1;i<=n;i++)
		if(a[i]!=ans) printf("%d ",a[i]);
	return 0;
}


```

---

## 作者：seika27 (赞：0)

#### 题意
给定一个数列 $A$，去除 $A$ 中的一个元素，使 $A$ 的字典序最小。
#### 思路
找到第一个 $A_i$，使 $A_{i-1}>A_{i}$，将值为 $A_{i-1}$ 的元素删除，输出。

#### 贪心证明
设 $A_{i-1}>A_i$。

因为 $A_1\sim A_{i-1}$ 是单调不递减的，由此可得不删除 $A_{i-1}$ 的字典序不可能比删除 $A_{i-1}$ 后的小。

因此，当第一次出现 $A_{i-1}>A_i$ 时就删除 $A_{i-1}$。

贪心得证。

#### code
```cpp
#include <bits/stdc++.h>
#define int long long 
#define cin std::cin
#define cout std::cout
int n,x;
int f=1;
const int N=2e5+5;
int A[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>A[i];
		if(A[i-1]>A[i]&&f)
		{
			f=0;
		    x=i-1;
		}
	}
	if(x==0)x=n;				//如果A是连续不下降子序列，则删除第n项 

	for(int i=1;i<=n;i++)
	{
		if(A[i]==A[x])continue;
        cout<<A[i]<<" ";
	}
	return 0;
} 
```


---

## 作者：_xiaxii (赞：0)

# [The Problem's Link](https://www.luogu.com.cn/problem/AT_arc133_a)

~~还没有题解，赶紧水一篇。~~

## 题意
输入一个数列，删除其中同一个值的一些数，使得到的新数列字典序最小，并输出这个数列。

## 做法
如果采用枚举的做法，写起来较为复杂。由于本题求字典序最小，可以考虑**贪心**。从第一个数字向后遍历，如果有一个数比后面一个数**大**，则这个数就是要删除的数。将这个数删除之后，后面较小的数会填补到这个数的位置，由于是从前向后遍历的，所以这种做法的字典序就是最小的了。

我们采用 $ptr$ 来记录待删除的数的位置。在读入时就可以进行处理，如果这个数比上一个数小，且未使用过 $ptr$，则将 $ptr$ 赋值为当前的位置。

## 注意
若整个数列都是单调不减的，则 $ptr$ 内不会有值，此时需要特判将 $ptr$ 赋值为 $n + 1$ 即可。

注意输出的时候遇到值等于 $A_{ptr-1}$ 的数再 `continue`，而非 $A_{ptr}$，因为我们记录的是较大数后面的那个数的位置。

数据保证 $A_i \ge 1$，因此无需将 $A_0$ 赋值。

## 代码
```
#include <bits/stdc++.h>
using namespace std;

int n,ptr;
int a[200001];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]<a[i-1]&&!ptr)ptr=i;//如果后一个数比前一个数小且未更新ptr
	}
	if(!ptr) ptr=n+1;//特判当ptr未更新时
	for(int i=1;i<=n;i++)
		if(a[i]!=a[ptr-1])cout<<a[i]<<" ";//如果不是要删除的数就输出
} 
```

实测[满分](https://www.luogu.com.cn/record/119947078)。


---

## 作者：Kano_zyc (赞：0)

~~看了一下我貌似还是此题最优解~~

## 题意简述

给定一个包含 $N$ 个数的序列 $A$，从中删去一个数 $X$，使序列字典序最小。

## 思路分析

我们做题要有一种直觉，一看此题数据范围这么小，完全可以暴力枚举来解决。暴力找到第一个 `a[i]>a[i+1]`，然后马上退出，最后再枚举一遍。

## 做法正确性

正确性主要基于以下两点：

- 这个策略总是能找到一个可以删除的元素。因为即使序列是严格递增的，我们也可以删除最后一个元素。所以这个策略总是能找到一个解。

- 因为我们总是删除第一个可以删除的元素，所以留下的小元素一定是最多的，故剩下的序列字典序最小。

证毕。

## AC code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include<vector>
#include <algorithm>
#incldue <map>
#define N 200010
#define re register unsigned int
//#define int long long
using namespace std;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<20+5];
inline int read(){
	int x=0,f=1;
	char c=gc();
	while(!isdigit(c)){
        if(c=='-')f=-1;
		c=gc();
	}while(isdigit(c)){
		x=x*10+(c^48);
		c=gc();
	}return x*f;
}
int n, a[N], b[N];
signed main() 
{
    n = read();
    for (re i = 1; i <= n; i++)
        a[i] = read();
    int ans ;
    a[n + 1] = -114514;
    for (re i = 1; i <= n; i++) {
        if (a[i] > a[i + 1]) {
            ans = a[i];
            break;
        }
    }
    for (re i = 1; i <= n; i++) {
        if (a[i] != ans)
            printf("%d ", a[i]);
    }
    return 0;
}
```


---

## 作者：tuanzi_pal (赞：0)

### 思路
可以采用暴力枚举，但会超时，所以我们想到了贪心，如果要使这个数列的字典序最小，我们需要找一个最长的单调递增的序列，然后将它第一个违反单调递增的数字的前一个数字删掉即可。如果没找到，说明这个序列是单调递增的，那么删掉队列最后一个数字，也就是最大的数字即可。
### 证明
假设第一个违反单调递增的数是 $a_i$。
那么 $a_1$ ~ $a_{i-1}$ 一定是单调递增的，所以在这一段中末尾的 $a_{i-1}$ 一定是最大的，且因为它是第一个找到的，所以它一定是尽量靠前的，由此可得删除 $a_{i-1}$ 一定是最优的。
### Code
```cpp
#include<bits/stdc++.h>
const int N=2e5+5;
using namespace std;
int res=-1;
int a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i-1]>a[i]&&res==-1) res=a[i-1];// 记录第一个违反单调递增的数字的前一个数字 
	}
	if(res==-1) res=a[n];//如果没找到，记录数列最后一个数字 
	for(int i=1;i<=n;++i){
		if(a[i]==res) continue;//判断并输出即可 
		cout<<a[i]<<" ";
	}
	return 0;
}
```
完结撒花 ~

---

## 作者：nxd_oxm (赞：0)

# 题意
题目说给一个数字序列，让你删一些相同的数，使序列字典序最小。

# 思路
因为要让字典序最小，字典序就是越靠前地位越高，所以最前面的应该优先删除。

所以我们只要找到第一次不是单调递增的地方，就可以把它及其他与他相同的数删去，这样可以使其字典序最小。
满足题意。

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans;
int a[200001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<a[i-1]&&!ans){
		    ans=i-1;
		}
	}
	if(!ans){
	    ans=n;
	}
	for(int i=1;i<=n;i++){
		if(a[i]!=a[ans]){
        cout<<a[i]<<" ";
      }
	}
} 
```

---

## 作者：luojunkai (赞：0)

分析：

首先：字典序：从前往后依次比较，遇到第一个 $>$ 或 $<$ 的数时即比较出了答案，若最后一个数仍相同则两者相同。

其次：从前往后找，若 $A_i \le A_{i + 1}$ 则 $A_i$ 在 $A_{i + 1}$ 前更优哦，$A_i$ 不必去；若 $A_i>A_{i + 1}$ 则 $A_{i + 1}$ 在前，$A_i$ 去掉会使整个序列字典序更小。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
int main()
{
	long long n,x=0;
	cin>>n;
	for(int i=0;i<n;i++)scanf("%lld",&a[i]);
	while(x+1<n&&a[x]<=a[x+1])x++;
	long long t=a[x];
	for(int i=0;i<n;i++)
	{
		if(a[i]!=t)printf("%lld ",a[i]);
	}
}
```


---

