# Happy Line

## 题目描述

Do you like summer? Residents of Berland do. They especially love eating ice cream in the hot summer. So this summer day a large queue of $ n $ Berland residents lined up in front of the ice cream stall. We know that each of them has a certain amount of berland dollars with them. The residents of Berland are nice people, so each person agrees to swap places with the person right behind him for just 1 dollar. More formally, if person $ a $ stands just behind person $ b $ , then person $ a $ can pay person $ b $ 1 dollar, then $ a $ and $ b $ get swapped. Of course, if person $ a $ has zero dollars, he can not swap places with person $ b $ .

Residents of Berland are strange people. In particular, they get upset when there is someone with a strictly smaller sum of money in the line in front of them.

Can you help the residents of Berland form such order in the line so that they were all happy? A happy resident is the one who stands first in the line or the one in front of who another resident stands with not less number of dollars. Note that the people of Berland are people of honor and they agree to swap places only in the manner described above.

## 说明/提示

In the first sample two residents should swap places, after that the first resident has 10 dollars and he is at the head of the line and the second resident will have 9 coins and he will be at the end of the line.

In the second sample it is impossible to achieve the desired result.

In the third sample the first person can swap with the second one, then they will have the following numbers of dollars: $ 4\ 11\ 3 $ , then the second person (in the new line) swaps with the third one, and the resulting numbers of dollars will equal to: $ 4\ 4\ 10 $ . In this line everybody will be happy.

## 样例 #1

### 输入

```
2
11 8
```

### 输出

```
9 10 ```

## 样例 #2

### 输入

```
5
10 9 7 10 6
```

### 输出

```
:(
```

## 样例 #3

### 输入

```
3
12 3 3
```

### 输出

```
4 4 10 ```

# 题解

## 作者：Hisaishi_Kanade (赞：9)

首先你直接模拟复杂度上天，不能通过此题。

由于有解时最后单调不降，那么我们考虑排序。

排什么？找不变量。

假设当前 $a_i,a_{i+1}$ 需要进行操作。

那么结果变成 $a_{i+1}+1,a_i-1$。

$a_{i+1}$ 原 $pos_1=i+1$，值 $val_1$ 为 $a_{i+1}$ ，更改后 $pos_2=i$，$val_2$ 为 $a_{i+1}+1$。

不难发现 $val_1+pos_1=val_2+pos_2$。

不难推出，对于任意 $a_i$，$val+pos$ 是定值。

我们将 $a_i+i$ 排序得到序列 $b$，输出 $b_i-i$。

不难发现无解情况是有 $b_i=b_{i+1}\mid 1\le i<n$。

```cpp
#include <stdio.h>
#include <algorithm>
int n,i;
int a[200005];
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		a[i]+=i;
	}
	std::sort(a+1,a+n+1);
	for(i=1;i<n;++i)
	{
		if(a[i]==a[i+1])
		{
			puts(":(");
			return 0;
		}
	}
	for(i=1;i<=n;++i)
	{
		printf("%d ",a[i]-=i);
	}
	return 0;
}

```

---

## 作者：wsyhb (赞：5)

## 题意简述

$n$ 个人排成一列，其中从后往前的第 $i$ 个人手里有 $a_i$ 美元。

当一个人手里还有钱时，Ta 可以给 $1$ 美元给恰在 Ta 前面的那个人，并和那个人交换位置。

问是否存在一种交换的方案，使得对于任意一个人，其后面的人所拥有的钱数均不超过自己的钱数。

存在则输出交换后从后往前每个人手里的钱数。

**数据范围**：$1 \le n \le 2 \times 10^5$，$0 \le a_i \le 10^9$。

## 题解

首先，一个人往前移动一步，他手里的钱就会减 $1$；一个人往后移动一步，他手里的钱就会加 $1$。

因此，对于原本在 $i$ 号位置的人，若 Ta 移动到 $j$ 号位置去，他手里的钱就会减去 $j-i$，即变成 $a_i+i-j$。

那么问题转化为：记 $b_i=a_i+i$，要求重新排列 $b$，使得 $0 \le b_1-1 \le b_2-2 \le \cdots \le b_n-n$。（注意：由于我们总可以使一个没有钱的人，先从后面与 Ta 交换的人那里得到钱，再去和前面的人交换，所以不需要考虑交换过程中一个人的钱数是否非负）

### 法一

使用 **multiset** 进行贪心：

一开始将所有的 $a_i+i$ 放入 multiset。

设当前考虑第 $x$ 个数，且上一个数为 $Last$，那么当前选 $\ge Last+x$ 的最小数是最优的。把这样的数用于更新 $Last$ 并从 multiset 中删除即可。

时间复杂度：$O(n\log{n})$。

（相比法一，法二其实更简洁，但我一开始看到题想到的是法一，觉得法一比较直接，所以讲了这个做法）

### 法二

$0 \le b_1-1 \le b_2-2 \le \cdots \le b_n-n$ 等价于 $1 \le b_1 < b_2 < \cdots <b_n$。

所以其实把 $b$ 从小到大**排序**并验证即可。

时间复杂度：$O(n\log{n})$。

## 代码

（以下为法一代码，法二代码略）

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=2e5+5;
int ans[max_n];
int main()
{
	int n;
	scanf("%d",&n);
	multiset<int> s;
	for(int i=1;i<=n;++i)
	{
		int a;
		scanf("%d",&a);
		s.insert(a+i);
	}
	for(int i=1;i<=n;++i)
	{
		multiset<int>::iterator it=s.lower_bound(ans[i-1]+i);
		if(it==s.end())
		{
			puts(":(");
			return 0;
		}
		ans[i]=*it-i;
		s.erase(it);
	}
	for(int i=1;i<=n;++i)
		printf("%d%c",ans[i],i<n?' ':'\n');
	return 0;
}
```

---

## 作者：zplqwq (赞：5)

# CF549G Happy Line

回来辣

这道题应该没有蓝题那么难吧qaq

## PART 1 题目

emmm，前面两个神都大概把思路说了，我再做些补充好了。

首先，题意很明确，就是问可不可以通过一系列操作变成非降序列即可。

至于为什么要用到排序，我来解释一下：

- 因为求**非降**序列，因此我们要排序。

其次，我们用什么排序

- 我们知道，这样用到**交换**的题目，冒泡是最好写的，但是冒泡时间复杂度较高，会**TLE**
- 那我们用什么排序？其他的向插入啊，选择啊之类的明显不容易
- 考虑时间复杂度，我们需要一个约为$O(nlogn)$的排序方法
- 而明显$sort$是个好东西

至于为什么无法直接排序，原因如下：

- 我们考虑道**中途会有变化（指的是加一减一）**，因此直接排序后变化无法处理

那我们如何解决呢？**考虑不变量**

- 什么不变，仔细想想，其实$a_i +i $不变
- 为什么？我们以$a[i+1]$为例，把它挪到i会+1，而同时$a_i$就会-1
- 而这样$a[i+1]$就不用-1 了
- 从而可以直接排序
- 最后仍需还原

那么，注意$a[i-1]-a[i]==1$时，此时，原序列不变。

至于如何处理：

- 特判一下还原后的序列满不满足条件即可

##  PART 2 代码

```c++
#include<bits/stdc++.h>//万能头
using namespace std;

int n,m;

const int N=10000010;

int a[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]+=i;//不变量
	}
	sort(a+1,a+1+n);//排序
	for(int i=1;i<=n;i++)
	{
		if(a[i-1]>=a[i]) //不满足的情况
		{
			cout<<":("<<endl;
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		a[i]-=i;//还原
		cout<<a[i]<<" ";//输出
	}
    return 0;
}

```





---

## 作者：dctc1494 (赞：2)

我们首先考虑暴力，显然是不行的，会炸，并且爆得很离谱。

所以这道题目我们要用贪心。

贪什么？因为题目要求我们将这个序列变为**非降的**，所以我们考虑排序。

我们可以将问题简化成：$b_i = a_i + i$。然后对 $b$ 进行排序。

我们来考虑无解的情况：如果 $b$ 中有两个数相等的话，就会是无解。

最后再输出 $b_i - i$ 即可。

最后放出 AC 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int N = 2e5 + 5; // 养成好习惯

int n, a[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] += i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i < n; ++i) {
		if (a[i] == a[i + 1]) { // 无解
            cout << ":(\n";
			return 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << (a[i] -= i) << ' ';
	}
    putchar('\n');

    return 0;
}
```

所以说这道题就是考思维，贪心的思想，只要你想出贪心的策略了，题目就会迎刃而解。

---

## 作者：Prean (赞：2)

~~变菜了，一年前做这种题10min出结论，现在对着样例胡半天都没结果~~

首先考虑从判断无解入手。

定义两个位置 $ (i,j) $，若 $ a[i]=a[j]+(j-i) $，则 $ i $ 和 $ j $ 贴贴。~~别问我为啥叫贴贴，因为这个真的很形象~~

让我们考虑执行若干次操作，足够多操作结束后，这两个元素 **仍然贴贴，并且相邻**。证明很简单。

然后你发现，每进行一次操作，这玩意儿不变，但是仍然可以继续进行操作。

也就是如果存在两个贴贴的元素，那么无解。

然后考虑解决问题。假如 $ a[i] $ 最终需要移动到 $ j $，那么最终的序列 $ b $ 上，$ b[j]=a[i]+i-j $。证明也很简单。

所以问题变成了将 $ a[i]+i $ 分配位置，使最终的序列单调不降。排序就好了。

而且排好序后还方便判断无解。
```cpp
#include<algorithm>
#include<cstdio>
typedef unsigned uint;
uint a[200005];
signed main(){
	register uint i,n;scanf("%u",&n);
	for(i=1;i<=n;++i)scanf("%u",a+i),a[i]+=i;std::sort(a+1,a+n+1);
	for(i=1;i^n;++i)if(a[i]==a[i+1])return!printf(":(");
	for(i=1;i<=n;++i)printf("%u ",a[i]-i);
}
```

---

## 作者：ltz761222 (赞：1)

#### 题目类型
优化模拟类。

#### 解题面
做题时现将题目翻译成数学语言。——葛老师


---

对于 $\forall i \in (1 , n-1)$，如果 $a_{i} \gt a_{i-1}$，$a_{i} \to a_{i+1}-1$，$a_{i+1} \to a_{i}+1$。（若相邻的两个数是逆序对，将第一个数的数值减少 1，下标增加 1，同时将第二个数的数值增加 1，下标减少 1）

发现无论是 $a_{i} \to a_{i+1}-1$，还是 $a_{i+1} \to a_{i}+1$，下标与数值的和不变，于是设 $b_{i} = a_{i}+i$，原题转化如下：

对 $b_{i}$ 重排，使其满足 $b_{i}-i \le b_{i+1}-(i+1)$。  
即 $b_{i} \lt b_{i+1}$。

#### 做法总结
构造数组 $b_{i} = a_{i}+i$，并对 $b_{i}$ 升序排列，若存在 $b_{i} = b_{i+1}$，此题无解，否则顺序输出 $b_{i}-i$。

#### 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=2e5+10;
int a[N],b[N];
int n;

/*
2
11 8

9 10
*/
/*
5
10 9 7 10 6

:(
*/
/*
3
12 3 3

4 4 10
*/
/*
2
2 1

:(
*/

inline int  read();

inline bool check();//判断有无解 

int main ()
{
	scanf ("%d",&n);
	for (int i=1;i<=n;i++)
		a[i]=read(),b[i]=a[i]+i;
	stable_sort(b+1,b+n+1);
	
	if (check())
		puts(":(");
	else
		for (int i=1;i<=n;i++)
			printf ("%d ",b[i]-i);
	
	return La Ma Xu Da Du;
}

inline int read()
{
	int o=0,c=0;
	while (c<'0' or c>'9')
		c=getchar();
	while (c>='0' and c<='9')
		o=(o<<1)+(o<<3)+(c^48),c=getchar();
	return o;
}

inline bool check()
{
	for (int i=1;i<n;i++)
		if (b[i]==b[i+1])
			return true;
	return false;
}

```

---

## 作者：happy_zero (赞：1)

好题。

一次操作相当于同时进行：$a_{i-1}\leftarrow a_i+1,a_i\leftarrow a_{i-1}-1$。

发现若 $i$ 移到了位置 $j$，则其会变成 $a_i+i-j$。$a_i+i$ 不会变的，不妨令其为 $b_i$。

设最后第 $j$ 个位置是原来的 $pos_j$，那么原问题就转化为：使得 $b_{pos_j}-j$ 不降。这个东西很经典啊，其实就是要求 $b_{pos_j}$ 单增。

而原本的交换条件 $a_{i-1}>a_i$ 等价于 $b_{i-1}-(i-1)>b_i-i$ 等价于 $b_{i-1}\ge b_i$。

于是可以将 $b$ 从小到大排序，最后减去下标输出。易得无解当且仅当存在两个 $b$ 相同。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int a[N];
signed main() {
	int n; cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i] += i;
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) 
		if (a[i] == a[i - 1]) return cout << ":(", 0;
	for (int i = 1; i <= n; i++)
		cout << a[i] - i << ' ';
	return 0;
}
```

---

## 作者：Marsrayd (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF549G)

## 题意简述

题面已经叙述的十分简洁了（大雾）。

## $\texttt{SOLUTION}$

可以将操作看成两次移动。

不难发现如果 $a_i$ 向后移动一个位置就会 $+1$，向左移动一个位置就会 $-1$。

这个 $+1,-1$ 非常的麻烦，如何化解呢？

考虑将 $a_{1…n}$ 全都移到某一个位置（不妨将他们移动到 $a_n$ ），把移动后的值记在 $b$ 数组中。

这样 $+1,-1$ 就自然而然的化没了。

再将 $b$ 数组排序，就可以得出 $a_{1…n}$ 每个数的排名。

再将他们从 $a_n$ 移到他们该在的地方即可。

下面，我来模拟一下：

例子：

```
6
12 32 56 23 21 34
```

得出的 $b$ 数组即为：

```
17 36 59 25 22 34
```

所以每个数的排名（即最终位置）应该是：

| $a_1$ | $a_2$| $a_3$ | $a_4$ | $a_5$ | $a_6$ |
| :----------- | :----------- | :----------- | :----------- | :----------- | :----------- |
| $1$ | $5$ | $6$ | $3$ | $2$ | $4$ |

所以答案为：

```
12 24 24 30 35 53 
```

至于 ```:(``` 的判断。

我们求出答案后该序列不是非降的就是 ```:(``` 。

$\texttt{AC CODE}$

```
#include<bits/stdc++.h>
long long read(){
	long long x=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int n;
long long a[1000010];
struct node{
	long long val,id;
	bool operator <(const node &b)const	{ return val<b.val; }
}b[1000010];
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i].val=a[i]-(n-i),b[i].id=i;
	std::sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) b[i].val+=n-b[i].id;
	for(int i=1;i<=n;i++) { a[i]=b[i].val-i+b[i].id; if(a[i]<a[i-1]) return !printf(":("); }
	for(int i=1;i<=n;i++) printf("%lld ",b[i].val-i+b[i].id);
}
```

---

## 作者：XL4453 (赞：1)

### 解题思路：

原来的操作是交换，但可以换一种理解方式，将某个值向前移可以使得其值加一，向后移可以使得其值减一，最后要保证每一个位置都只有一个值，同时序列升序。

对于每一个位置，无论它怎么移动 $a_i+i$ 总是固定的，那么考虑先将所有的都移到第一个，也就是将其转化为 $a_i+i$。

然后将其往后移动，也就是按照从小到大的顺序分配到位置并还原为原来的序列，也就是对于排好序的序列的每一个 $a_i$ 都改为 $a_i-i$，这时，如果出现排序错误的现象，那么无解，否则就直接输出还原后的序列。

---
无解的原理是这样的，由于出现了 $a_i+i$ 和某一个 $a_j+j$ 相等，然后在拍完序后的序列中这两个相邻但是还原后的序列出需要减去位置的编号，所以得到了错误的序列。

从交换上理解就是这样的：不妨设 $i<j$，那么 $a_i>a_j$，在将两者向中间交换的时候，最后得到了：$a_k'+1,a_k'$ 这两个连续的数，此时如果再次交换发现这两个值无法变化，导致错误。

说人话就是 $2,1$ 交换完了还是 $2,1$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200005],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]+=i;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(a[i-1]-(i-1)>a[i]-i){
			printf(":(");
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]-i);
	}
	return 0;
}
```


---

## 作者：convie (赞：1)

这道题若使用暴力解法，时间复杂度将达到 $O(n^2)$，因此需要优化。通过观察可以发现，对于相邻元素，当前一个元素比后一个大时，可以交换它们并使前一个元素加一，后一个元素减一。因此，我们可以构建一个数组 $b$，其中 $b[i] = a[i] + i$。对 $b$ 数组进行排序后，若存在相等的元素，则该数列无解；否则，输出 $b[i] - i$ 即为答案。
```
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define ios ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define MAXN 200010
int a[MAXN];
int b[MAXN];
signed main(){
    ios;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)b[i]=a[i]+i;
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++)
    if(b[i]==b[i-1]){
        cout<<":(";
        return 0;
    }
    for(int i=1;i<=n;i++)
    cout<<b[i]-i<<" ";
    return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

妙妙题。

观察题目，发现如果一个人从 $i\to j$，那么最后他的金钱就会变成 $a_i-(j-i)=a_i+i-j$。不妨把所有人都先移到 $0$ 号点，那么他们此刻的金钱就都是 $a_i+i$。贪心考虑，金钱更多的显然有更大的权力，他们应该排到更前面去。于是先构造出方案，再看看这种方案是否合法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,a[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()+i;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)a[i]-=i;
	for(int i=1;i<n;i++)if(a[i]>a[i+1])return (void)printf(":("),0;
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```

感觉和其他题解本质上差不多，但是似乎或许会更好理解？

---

## 作者：Nine_Suns (赞：0)

我觉得还是有些难度的，~~毕竟我贪心构造这种题都不会做。~~

## Solution

看题面可以发现一些性质，称初始序列为 $A$，最终序列为 $B$，如果 $a_i$ 换到了 $b_j$ 的位置，那么 $b_j=a_i+j-i$，因为一个数往右移必然减 $1$，往左移必然加 $1$。

从最大值，也就是 $b_n$ 的构造开始，我们找到 $A$ 中换到 $n$ 后值最大的一个，即 $\max\{a_i+i-n\}$，然后把这个玩意丢到 $b_n$ 的位置，再对 $A$ 中的每个数加一（换到最后对全局的贡献），依次类推求 $b_{n-1},b_{n-2},...,b_1$。

正确性证明，显然我们只需要确定最大的 $a$ 能不能换到最后即可，设 $a_i-n+i$ 是最大值，对于前面的一个值 $a_j-n+j$ 有 $a_i-n+i>a_j-n+j$ 变一下形，$a_n+i-j>a_j$，所以一定能换到最后。

若 $a_i+i-n$ 中有两个相同的值，直接判断无解即可。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5+5, inf = 0x3f3f3f3f;
int n, a[N], b[N];

int main () {
	ios::sync_with_stdio(false); 
	cin.tie(0); cout.tie(0); 
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i], a[i] += i-n;
	sort(a+1, a+1+n); 
	for (int i = 2;i <= n;i++) if (a[i] == a[i-1]) return cout << ":(", 0;
	for (int i = 0;i < n;i++) b[n-i] = a[n-i]+i;
	for (int i = 1;i <= n;i++) cout << b[i] << ' ';
	return 0;
}
```


---

## 作者：lanos212 (赞：0)

好玩的思维题 qwq。

简化并拓展一下题面的条件，也就是一个数往左移动了 $k$ 格后，数值会增加 $k$，往右移动 $k$ 格后，数值会减小 $k$，要求重排成**非降序列**。

首先先看下什么情况下会无解，发现如果出现一个位置 $i$ 上的数 $a_i$，以及一个位置 $j$ 上的数 $a_j$，如果满足 $a_i-a_j=j-i$，这就一定是无解的，因为它们其中哪个在前面，都会比后面那个要大。

考虑有解的时候，对于任意一个数对 $(a_i,a_j)$，发现它们在答案中的前后顺序是一定的。比如说 `4 2 7` 中，发现 `4` 怎么移动，必须在 `2` 的右边才有解，`7` 怎么移，必须在 `4` 的右边才有解。易得当 $a_i-a_j>j-i$ 时，$a_i$ 必须在 $a_j$ 的右边，当 $a_i-a_j<j-i$ 时，$a_i$ 必须在 $a_j$ 的左边。显然这是具有传递性的，当 $a_i$ 要放在 $a_j$ 左边，$a_j$ 要放在 $a_k$ 左边时，$a_i$ 一定也在 $a_k$ 的左边。

发现知道所有数对的前后关系后，就可以进行排序了，写个排序的程序然后比较“大小”时使用上面的式子即可，注意位置修改后需要按照题意修改这个数的值。

下面的码写的是归并排序，时间复杂度 $O(n \log n)$。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300001],b[300001];
inline void no(){cout<<":("; exit(0);}//输出无解 
inline void merge(int l,int r){
	if (l==r) return;
	int mid=(l+r)>>1,x=l,y=1+((l+r)>>1),tmp=l;
	merge(l,mid); merge(mid+1,r);
	while (x<=mid && y<=r){
		if (a[x]-a[y]==y-x) no();//此时无解 
		if (a[x]-a[y]>y-x) b[tmp]=y-tmp+a[y],++tmp,++y;//a[y]应该放在a[x]左边
		else b[tmp]=x-tmp+a[x],++tmp,++x;//a[x]应该放在a[y]左边
	}
	while (x<=mid) b[tmp]=x-tmp+a[x],++tmp,++x;
	while (y<=r) b[tmp]=y-tmp+a[y],++tmp,++y;
	for (int i=l;i<=r;++i) a[i]=b[i];
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	merge(1,n);
	for (int i=1;i<n;++i) if (a[i]>a[i+1]) no();
	for (int i=1;i<=n;++i) cout<<a[i]<<' ';
	return 0;
}
```


---

## 作者：TachibanaKanade (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF549G)

思维难度略大的题。

题目中每一次操作的方式即对于两个相邻的元素 $a_{i-1}$ 和 $a_i$，把 $a_{i-1}$ 减 $1$，$a_i$ 加 $1$，并把它们交换位置。

这时不妨理解为 $a_i$ 往前移动了一位，数值减 $1$；$a_{i-1}$ 向后移动了一位，数值加 $1$。

即，将一个元素向后移可以让它的数值加 $1$，向前移可以使得其值减 $1$（这里的前后以下标大小区分）。

但显然这样还是不好直接排序，考虑把加 $1$ 减 $1$ 化掉。

此时不妨假设把 $a$ 中的每个数值全部移到 $a_1$，再按从小到大的顺序向后排。

令排序后的数组为 $b_i$，则此时实际的 $a_i$ 为 $b_i-i$。

然后把 $a_i$ 还原回来，如果不是单调递增的就是无解的。但很多题解并没有讲明白为什么这样就是无解的。

简单说明一下，就是对于 $i$ 和 $i-1$ 交换完之后还是 $i$ 和 $i-1$，此必然无解；而 $i$ 和 $i-j$ 交换后为 $i-j+1$ 和 $i-1$，最终总能得到前后两者差 $1$ 的情况，所以无解。

码风是一年前的，有点丑就是说。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node { int a, b; } a[200005];
bool cmp(node s1, node s2) { return s1.b < s2.b; }
signed main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].a;
        a[i].b = a[i].a + i;
    } sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) a[i].a = a[i].b - i;
    for (int i = 1; i < n; i++) if (a[i].a > a[i + 1].a) return !printf(":(\n");
    for (int i = 1; i <= n; i++) cout << a[i].a << " ";
}
```


---

## 作者：Goldia (赞：0)

### 大致思路
- 首先看到这道题，就应该明白这其实是道排序题，因为题目要求得到一个不下降的序列。对于每两个元素交换时，a[i]与a[i+1]会变为a[i+1]+1,a[i-1]-1,显然如果a[i-1]-a[i]==1，那么一定无解，比如样例2中10,9交换后还是10,9。
- 那么对于这样的排序规则，最容易实现的肯定是冒泡排序，只需重新定义一下排序规则，然后再进行排序就好了，不过n的范围是2e5，肯定会超时的，所以我们要考虑nlogn的算法。
- c++当然还是sort最方便，但直接排肯定是不行的，我们可以这样考虑，把a[i+1]挪到i的位置上会让他+1，而a[i]会-1，这就像在楼梯上排序一样。我们要做的就是把楼梯还原回平面，这样就能正常的进行排序了，之后再把序列还原就可以了，至于无解的情况，就判断一下还原后的序列是否满足不下降就好了。
### code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define LL long long
#define R register
int n,a[200005];
int main()
{
	scanf("%d",&n);
	for(R int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]+=i;
	}
	sort(a+1,a+n+1);
	for(R int i=1;i<=n;i++)a[i]-=i;
	for(R int i=2;i<=n;i++)if(a[i-1]>a[i]){puts(":(");return 0;}
	for(R int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```


---

