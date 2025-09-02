# Serval and Final MEX

## 题目描述

给定一个由 $n \ge 4$ 个非负整数组成的数组 $a$。

你需要对 $a$ 执行以下操作，直到其长度变为 $1$：
- 选择两个下标 $l$ 和 $r$（$1 \le {\color{red}{ l < r }} \le |a|$），将子数组 $[a_l, a_{l+1}, \ldots, a_r]$ 替换为一个整数 $\operatorname{mex}([a_l, a_{l+1}, \ldots, a_r])$。其中 $\operatorname{mex}(b)$ 表示整数集合 $b$ 的最小未出现值（MEX）$^{\text{∗}}$。具体来说，令 $x = \operatorname{mex}([a_l, a_{l+1}, \ldots, a_r])$，数组 $a$ 将变为 $[a_1, a_2, \ldots, a_{l-1}, x, a_{r+1}, a_{r+2}, \ldots, a_{|a|}]$。注意此操作后 $a$ 的长度将减少 $(r - l)$。

Serval 希望最终 $a$ 中的唯一元素为 $0$。请帮助他完成这一目标！

更正式地说，你需要找到一个操作序列，使得按顺序执行这些操作后，数组 $a$ 的长度变为 $1$，且该元素为 $0$。

可以证明，在题目约束下至少存在一个有效的操作序列，且任何有效操作序列的长度不超过 $n$。

注意：你**不需要**最小化操作次数。

$^{\text{∗}}$整数集合 $b_1, b_2, \ldots, b_k$ 的最小未出现值（MEX）定义为**不包含**在该集合中的最小非负整数 $x$。

## 说明/提示

第一个测试案例中，由于 $\operatorname{mex}([1,2,3,4]) = 0$，经过一次操作后数组变为 $[0]$。

第二个测试案例中，数组 $a$ 的变化如下：
$$[
\underline{0,1},0,0,1] \to [
\underline{2,0},0,1] \to [
\underline{1,0},1] \to [
\underline{2,1}] \to [
0].
$$

第三个测试案例中，数组 $a$ 的变化如下：
$$[
0,0,0,0,\underline{0,0}] \to [
0,0,\underline{0,0},1] \to [
\underline{0,0},1,1] \to [
\underline{1,1,1}] \to [
0].
$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
4
1 2 3 4
5
0 1 0 0 1
6
0 0 0 0 0 0
6
5 4 3 2 1 0
4
0 0 1 1
4
1 0 0 0```

### 输出

```
1
1 4
4
1 2
1 2
1 2
1 2
4
5 6
3 4
1 2
1 3
3
4 5
4 5
1 4
2
1 2
1 3
2
2 4
1 2```

# 题解

## 作者：ZMQ_Ink6556 (赞：6)

## 题解：CF2085B Serval and Final MEX

### 题意简述

您将获得一个数组 $a$，由 $n \ge 4$ 个非负整数组成。

您需要对 $a$ 执行以下操作，直到其长度变为 $1$：

选择两个索引 $l$ 和 $r(1 \le l < r \le |a|)$，并将子数组 $[a_l，a_{l+1} , \dots , a_r]$ 替换为单个整数 $\operatorname{mex}([a_l , a_{l+1} , \dots , a_r])$，其中 $\operatorname{mex}(b)$ 表示 $b$ 中整数的最小排除。

换句话说，设 $x=\operatorname{mex}([a_l , a_{l+1} , \dots , a_r])$，数组 $a$ 将变为 $[a_1，a_2 , \dots , a_{l-1} , x ，a_{r+1} , a_{r + 2} , \dots , a|a|]$。

请注意，在此操作后，$a$ 的长度减少了 $(r - l)$。

Serval 希望 $a$ 中的最后一个元素为 $0$。帮帮他！

更正式地说，您必须找到一系列作，这样在按顺序执行这些作后，$a$ 的长度变为 $1$，并且 $a$ 中的最后一个元素为 $0$。

可以证明，在问题的约束下至少存在一个有效的作序列，并且任何一个有效作序列的长度不超过 $n$。

请注意，您不需要最小化操作数。

### 解题思路

根据要求的结果倒推，最后一次操作必定是选中整个数组，然后将所有数变成一个 $0$。原因是如果不选中整个数组，那么最后剩下的元素是没选的数字的数量 $+ 1 > 1$，不满足只剩一个元素。

如果要在最后一次操作中使得数组变成 $0$，那么就要求此时数组中没有 $0$。

如何使得数组没有 $0$ 呢？我们可以把数组拆成两段：$[a_1 , a_2 , \dots , a_{n - 3} a_{n - 2}] , [a_{n - 1} , a_n]$，每段分别处理。

|              | 前段没有 $0$                                                   | 前段有 $0$                                                        |
| ------------ | ---------------------------------------------------------- | -------------------------------------------------------------- |
| **后段没有 $0$** | 直接把数组替换为 $\operatorname{mex}$                              | 将前段替换为 $\operatorname{mex}$ 再将整个数组替换为 $\operatorname{mex}$     |
| **后段有 $0$**  | 将后段替换为 $\operatorname{mex}$ 再将整个数组替换为 $\operatorname{mex}$ | 将前、后段分别替换为 $\operatorname{mex}$，再将整个数组替换为 $\operatorname{mex}$ |

**注意经过替换后数组长度会改变！**

依据思路分类讨论即可。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int t , n , a[5005];
inline bool zero(int l , int r)
{
	for(int i = l ; i <= r ; i++)
	{
		if(a[i] == 0)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
		}
		if(zero(n - 1 , n) && zero(1 , n - 2))
		{
			cout << "3\n" << n - 1 << ' ' << n << "\n1 " << n - 2 << "\n1 2\n";
		}
		else if(zero(n - 1 , n) && !zero(1 , n - 2))
		{
			cout << "2\n" << n - 1 << ' ' << n << "\n1 " << n - 1 << '\n';
		}
		else if(!zero(n - 1 , n) && zero(1 , n - 2))
		{
			cout << "2\n1 " << n - 2 << "\n1 3\n"; 
		}
		else
		{
			cout << "1\n1 " << n << '\n';
		}
	}
	return 0;
}
```

---

## 作者：Graph_Theory (赞：1)

### 题意
找一个 $l$ 和 $r$ 并将这个数组替换成不包含在该集合中的最小非负整数 $x$。输出任意一种方法使得数组变成 $0$。

### 思路
从样例一中发现，当数组不存在 $0$ 时，直接合并一次即可。

从二中发现，我们应将一个含有 $0$ 的序列替换成一个大于 $0$ 的整数。


所以我们只要让 $0$ 和任意一个数合并即可。这里我选择和他右边的合并除了 $a_n$ 就可以。

这里有个小细节就是合并完之后下标改变了，所以要记录一下。
### 代码
```cpp
for (int i=1;i<=n;i++)
	if(a[i]==0) 
	{
		if(i==n) sum.push_back({i-l-1,i-l  });//最后一个和前面合并
		else     sum.push_back({i-l  ,i-l+1});//其他的和后面合并
		i++,l++;//将0替换成非0
	}	
sum.push_back({1,n-l});//剩下都不是 $0$ 了，直接合并。
```

---

## 作者：chenruikai (赞：0)

### 题意
显然。
### 解
#### 法 1
因为有 $0$ 才会使最终结果不为 $0$，故把每一段含$0$ 的都 $\text{mex}$ 即可。然而，发现有 $l<r$ 的条件，要多判断一下。
#### 法 2
分为 2 段考虑，将前后分别转为不为 $0$ 的数字，然后两段合并即可。

易得，当前段有 $0$ 时，只需对前段整段操作一次即可；没有时，不用操作。后段亦然。

综上即可使俩段都成为正数，然后两个数操作一下就好了。

### code
```cpp
#include <bits/stdc++.h>
using namespace std;

int qread()
{
    int res = 0;char ch = getchar();
    for(;ch < '0' || ch > '9';ch = getchar());
    for(;ch >= '0' && ch <= '9';ch = getchar())
        res = (res << 1) + (res << 3) + ch - '0';
    return res;
}
int csyy , num , len;
bool have_bef , have_af;
int main()
{
    csyy = qread();
    while(csyy--)
    {
        have_bef = have_af = false;
        len = qread();
        for(int i = 0;i < len;i++)
        {
            num = qread();
            if(i >= 2)have_af = (have_af || num == 0);
            else have_bef = (have_bef || num == 0);
        }
        if(have_bef && have_af)printf("3\n3 %d\n1 2\n1 2\n" , len);
        else if(have_bef && !have_af)printf("2\n1 2\n1 %d\n" , len - 1);
        else if(!have_bef && have_af)printf("2\n3 %d\n1 3\n" , len);
        else printf("1\n1 %d\n" , len);
    }
    return 0;
}
```

---

## 作者：BDFZ_hym_AK_hym_ing (赞：0)

### 题目解读：
你将获得一个长为 $n$ 的数组 $a$，你可以进行任意次合并操作，让数组 $a$ 中剩下唯一一个 $0$。  
合并操作定义：选取一段连续数字，让这些数字合并为第一个未出现的自然数。  
**注意合并后位置有改变！！！**
### 做法分析：
这题可以直接分类讨论。
由样例一得到当数组中全部不为 $0$ 时，可以对所有数字进行合并。  
所以最后一步前数组内一定没有 $0$。  
1. 当数组初始已经全部不为 $0$ 时，直接全部合并。  
例子：见样例一。
2. 当第一个数字不为 $0$ 且后面有数字为 $0$ 时，将除第一个数字外的数字合并，因为后面有数字为 $0$，所以数组会变为第一个数字和另一个不为 $0$ 的数字，此时也可以直接合并。  
例子（括号代表一次合并操作，下面同）：
```markdown
1 1 0 1 2
1 (1 0 1 2)
1 3
(1 3)
0
```
3. 当最后第一个数字不为 $0$ 且前面有数字为 $0$ 时，将除最后第一个数字外的数字合并，因为前面有数字为 $0$，所以数组会变为一个不为 $0$ 的数字和最后第一个数字，此时也可以直接合并。  
例子：
```markdown
1 1 0 1 2
(1 1 0 1) 2
2 2
(2 2)
0
```
4. 当第一个数字和最后第一个数字都为 $0$ 时，可以将前面 $2$ 个数字直接合并，因为第一个数字为 $0$，所以合并出来的数不为 $0$，又因为最后第一个数字为 $0$，所以转化为情况 $2$。  
例子：
```markdown
0 2 0 3 0
(0 2) 0 3 0
1 0 3 0
1 (0 3 0)
1 1
(1 1)
0
```
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[5005],hd,tl; 
int main(){
	
	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin>>t;
	while(t--)
	{
		cin>>n;
		long long i;
		bool flag=true;
		for(i=1;i<=n;i++)
		{
			cin>>a[i];
			if(!a[i])
			{
				flag=false;
			}
		}
		if(flag)//情况1
		{
			cout<<1<<"\n";
			cout<<1<<" "<<n<<"\n";
			continue;
		}
		if(a[1])//情况2
		{
			cout<<2<<"\n";
			cout<<2<<" "<<n<<"\n";
			cout<<1<<" "<<2<<"\n";
			continue;
		}
		if(a[n])//情况3
		{
			cout<<2<<"\n";
			cout<<1<<" "<<n-1<<"\n";
			cout<<1<<" "<<2<<"\n";
			continue;
		}
        //情况4
		cout<<3<<"\n";
		cout<<1<<" "<<2<<"\n";
		cout<<2<<" "<<n-1<<"\n";
		cout<<1<<" "<<2<<"\n";
	}
	
	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

### 解法

让一个数列 $b$ 的 $\operatorname{mex}(b)$ 变为 $0$。那么这个长度为 $n$ 数列最小值一定是 $1$。所以我们要将数列构造成最小值为 $1$。

接着，任何两个不为 $0$ 的数的 $\operatorname{mex}$ 一定是 $0$。而一个为 $0$ 的数的和不为 $1$ 的 $\operatorname{mex}$ 一定是 $1$。

这时我们只要有 $4$ 个任意的数就一定能构造成 $0$。先操作两个不为 $0$ 的数，再操作刚刚得出的 $0$ 和任意一个不为 $1$ 的数，最后操作任何两个不为 $0$ 的数。例如样例。

|操作|结果|
|:-:|:-:|
|(1,2)|0,3,4|
|(1,2)|1,4|
|(1,2)|0|

那如果数列长度大于 $4$ 呢？此时只要操作一个长度为 $len-3$ 的数列即可。

---

## 作者：YuYuanPQ (赞：0)

赛时思路和实现都想复杂了，以此题解祭。

---
我们可以从最后的序列入手：\
如果一个序列最后的 $\operatorname{mex}$ 值是 $0$，那么上一个序列中必然没有 $0$，即都是非 $0$ 数。

有了这个东西，我们就可以自然而然地想到一个方法：把原序列变成倒数第二步的局面。怎么变呢？

容易想到的是，因为倒数第二步的序列中全是非 $0$ 数，那再往前，如果存在 $0$，我们一定是通过把 $0$ 和其他数一起消掉这个 $0$ 的。（注意，其他数也可以是另外的 $0$）

实际上到这一步你就能发现，只需要很少的次数就能使其原序列满足条件了。

接下来讲讲具体实现：

分类讨论：
- 当序列中没有 $0$ 时：直接一次做掉。
- 当 $a_1$ 为非 $0$ 数时：这样就能直接把 $2\sim n$ 的数都变为非 $0$ 数，再加上第 $1$ 个数非 $0$，这样就是倒数第二步的局面了。
- 当 $a_1$ 为 $0$ 且 $a_n$ 为非 $0$ 数时：同理。
- 当 $a_1$ 和 $a_n$ 都是 $0$ 时：稍微复杂一点，但也很好想。这里就不讲了。（代码中为了好算，是先对后面进行操作）

赛时没调出来是因为我的实现方法很复杂，较难实现对特殊情况的判断。

## Code
```cpp
#include<bits/stdc++.h>

typedef int IT;
typedef long long LL;
typedef __int128 int128;
typedef double DB;
typedef long double LDB;

#define pb push_back
#define fst first
#define sec second
#define psh push
#define mkp make_pair
#define PII pair<IT,IT>
#define PLI pair<LL,IT>
#define lowbit(x) ((x)&(-x))
using namespace std;

const int N=5e3+10;

int n;
int a[N];

int ls;
struct node{
    int l,r;
}ans[10];

void sl_reset();
void solve(){
    sl_reset();
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    bool nozero=1;
    for(int i=1;i<=n;i++){
        if(!a[i]){
            nozero=0;
            break;
        }
    }

    if(nozero){
        ++ls;
        ans[ls].l=1,ans[ls].r=n;
    }
    else if(a[1]){
        ++ls;
        ans[ls].l=2,ans[ls].r=n;
        ++ls;
        ans[ls].l=1,ans[ls].r=2;
    }
    else if(a[n]){
        ++ls;
        ans[ls].l=1,ans[ls].r=n-1;
        ++ls;
        ans[ls].l=1,ans[ls].r=2;
    }
    else{
        ++ls;
        ans[ls].l=n-1,ans[ls].r=n;
        ++ls;
        ans[ls].l=1,ans[ls].r=n-2;
        ++ls;
        ans[ls].l=1,ans[ls].r=2;
    }

    printf("%d\n",ls);
    for(int i=1;i<=ls;i++) printf("%d %d\n",ans[i].l,ans[i].r);
    return;
}
void sl_reset(){
    ls=0;
    return;
}

int main(){
    int T=1;
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}
```

[Link](https://codeforces.com/contest/2085/submission/312204878)

---

