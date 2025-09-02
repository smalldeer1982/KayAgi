# Max,Mex

## 题目背景

**hack 数据已添加，位于 Subtask#5，不计分。**

**请注意本题特殊的空间限制。**

本题中定义 $\max\{S\}$ 为 $S$ 中的最大值，$\operatorname{mex}\{S\}$ 为 $S$ 中最小没出现过的自然数。

## 题目描述

给定一个长度为 $n$ 的序列 $a$。

一次操作你可以选定一个 $(i,j)$，满足 $1\le i,j\le n$ 以及 $i\neq j$，令 $x=\max\{a_i,a_j\}$，$y=\operatorname{mex}\{a_i,a_j\}$，那么 $a_i=x$，$a_j=y$。

请问进行若干次操作后，$\sum_{i=1}^n a_i$ 最大为多少？

## 说明/提示

**【样例解释】**

操作 $(5,1)$，$(5,2)$，答案为 $2+2+4+5+1+4=18$。

**【数据范围】**

- Subtask#1（$10\text{pts}$）：$n=1$，**空间限制 4MB**；
- Subtask#2（$20\text{pts}$）：$a_i\ge 2$，**空间限制 512MB**；
- Subtask#3（$30\text{pts}$）：无特殊限制，**空间限制 512MB**。
- Subtask#4（$40\text{pts}$）：无特殊限制，**空间限制 4MB**。
- Subtask#5（$0\text{pts}$）：hack，**空间限制 512MB**。


对于 $100\%$ 的数据，$1\le n\le 10^6$，$0\le a_i\le 10^9$。

## 样例 #1

### 输入

```
6
0 0 4 5 1 4```

### 输出

```
18```

# 题解

## 作者：M1__ (赞：3)

# 题解：P11638 Max,Mex
[题目传送门](https://www.luogu.com.cn/problem/P11638?contestId=224170)
## 前置知识

$$\sum_{i=1}^n a_i=a_1+a_2+a_3+a_4+a_5+ \cdots+a_n$$

## 思路
> 本题中定义 $\max\{S\}$ 为 $S$ 中的最大值，$\operatorname{mex}\{S\}$ 为 $S$ 中最小没出现过的自然数。一次操作你可以选定一个 $(i,j)$，满足 $1\le i,j\le n$ 以及 $i\neq j$，令 $x=\max\{a_i,a_j\}$，$y=\operatorname{mex}\{a_i,a_j\}$，那么 $a_i=x$，$a_j=y$。

### subtask 1&2
- 对于 subtask1 与 subtask2，直接输出 $sum$ 即可。证明如下：
    - 当 $a_i \ge 2$ 时，$\operatorname{mex}\{a_i,a_j\}=0$，即 $a_j=0$，对 $\sum_{i=1}^n a_i$ 没有贡献，所以不需要进行操作，在代码中进行特判即可。这样可拿到 $[10,30]$ 分。
### subtask 3&4
- 对于 subtask3 与 subtask4，因为无特殊性质，所以需要判断关于 $\operatorname{mex}\{a_i,a_j\}$ 的所有情况，求出他们分别对 $\sum_{i=1}^n a_i$ 的贡献值并得出规律。

- 我们会发现如下规律：
  - 对于一个操作，不论是 $\operatorname{mex}\{a_i,a_j\}$ 还是 $\max\{a_i,a_j\}$，只要 $a_i,a_j \ge 2$ 时，根据 subtask 1&2 的结论，再进行操作显然对 $\sum_{i=1}^n a_i$ 没有贡献，所以我们只需统计数列中小于 $2$ 的个数和大于等于 $2$ 的数之和，并求出小于 $2$ 的数的最大贡献值即可。
  - 因此，对于一组 $a_i,a_j$ 有以下几种情况：
      - 当 $a_i=0,a_j=0$ 时，令 $a_j=\operatorname{mex}\{0,0\}=1$。此时 $a_i=0,a_j=1$。
      - 当 $a_i=0,a_j=1$ 时，令 $a_i=\max\{0,1\}=1$，$a_j=\operatorname{mex}\{0,1\}=2$。此时 $a_i=1,a_j=2$。
      - 当 $a_i=1,a_j=2$ 时，令 $a_i=\max\{1,2\}=2$，$a_j=\operatorname{mex}\{2,2\}=0$。此时 $a_i=2,a_j=0$。显然对 $\sum_{i=1}^n a_i$ 没有贡献，所以这个操作要舍去。
  - 综上，我们一共操作了三次，操作过后结果为 $a_i=1,a_j=2$，此时贡献值为 $1+2=3$。
  - 因此，我们可以推导出 subtask 3&4 的通项公式。即对于 $cnt$ 个 $0$，$ans$ 个 $1$，最后会有 $cnt+ans-1$ 个数操作成 $2$，剩下的一个数无法进行操作，即为 $1$。即对于小于等于 $2$ 的 $a_i,a_j$，最大贡献次数为：
    $$2 \times ((cnt+ans)-1)+1$$
  - 因此，subtask 3&4 的通项公式为：
    $$\sum _{i=1}^n a_i+2 \times ((cnt+ans)-1)+1-ans$$
     即：
     $$\sum _{i=1}^n [a_i\neq 0 \wedge a_i \neq 1 ]+2 \times cnt + ans-1$$
### 关于hack数据
事实上，这是本代码的一个小 Bug。         
当 $n=1,a_i=0$ 时，因为之前 $cnt$ 记录 $0$ 的个数时，$cnt$ 便不会为 $0$，因此卡过了上文中的关于 subtask1 的部分。所以只要在这之前进行特判便没有问题了。
## 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll cnt,ans,sum,n,a;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		sum+=a;
		if(n==1){
			cout<<a;
			return 0;
		}
		if(a==0) cnt++;
		if(a==1) ans++;
	}
	if(cnt+ans==0) cout<<sum;
	else cout<<cnt*2+ans+sum-1;
	return 0;
}

```
本题思维难度略大，代码实现方面比较简单。

---

## 作者：_O_v_O_ (赞：2)

出题人题解。

我们注意到一对 $(x,y)$ 进行操作后：

- $x\ge2,y\ge2$ 很显然不优。
- $x=1,y\ge2$ 做完后 $x=0$。
- $x=0,y\ge1$ 做完后 $x=1$。
- $x=0,y=0$ 做完后 $x=2,y=1$。

那么假如共有 $x$ 个 $0$ 和 $1$，能达到的最大贡献为 $2\times(x-1)+1$，即留下来一个 $1$，剩下的全部变成 $2$。

那么答案为 $(\sum_{i=1}^n [a_i\neq0\land a_i\neq1] a_i)+2\times(\sum_{i=1}^n[a_i=0\lor a_i=1])-1 $。

注意特判 $a$ 中没有 $0$ 和 $1$ 的情况。

---

## 作者：sbno333 (赞：2)

考虑到如果对 $a_i\ge 2$ 特别操作，一定不优秀。

但是可以拿它充当凑数，带飞 $a_i=0$。

容易证明，总能找到一个数带飞 $a_i=0$。

考虑 $a_i\ge2$ 没办法变大，退而求其次保留，剩下的数尽量变大，显然最大变成 $2$。

假设都能变成 $2$，最后一次就是 $0$ 和 $1$ 把 $0$ 变成 $2$，不成立，故做不到。

但是可以只有 $1$ 个 $1$。

先把所有数全变成 $0$ 或 $2$，容易看出一定可以操作（对于 $1$，把他和 $a_i\ge1$ 操作，没有就先把一个 $0$ 和他操作变成 $2$，然后在和 $2$ 操作）。

然后每两个 $0$ 都可以两次操作变成一个 $2$ 一个 $1$，操作之后把 $1$ 变回 $0$。

操作之后剩下了 $0$ 再随便找个数把他变 $1$ 即可。

这些都依赖于 $n\ge2$。

于是代码呼之欲出了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n;
	cin>>n;
	if(n==1){
		int x;
		cin>>x;
		cout<<x;
	}else{
		int ans,sum;
		ans=sum=0;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			if(x>=2){
				ans+=x;
			}else{
				sum++;
			}
		}
		if(sum)
		ans+=2*sum-1;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：2)

本题是一道很好的思维题，本人因考虑不周，赛时卡了 $0.5h$，支持评黄。
## 题目分析
根据题意，每次操作我们可以进行两种操作：$\max$ 和 $\operatorname{mex}$，题面描绘得相当有迷惑性，但仔细读题我们可以发现：这一切操作都只于**两数之间**进行！这样，扑朔迷离的 $\operatorname{mex}$ 操作就显得清晰了，还给我们一个特殊性质：一次操作后当且仅当操作数中**存在 $0$** 时 $\operatorname{mex} (a,b)$ 的值才会大于 $0$ 从而大于 $\min (a,b)$，而我们知道 $\min (a,b)+\max(a,b)=a+b$（此时可将两数看成一个整体以便分析，不必考虑顺序），因此只有这样才能使操作后两数和较原先大！而本题空间限制小，且求的是和的最大，我们不禁就会想到，这和序列中的 **$0$ 的数量**是否有一些联系呢……
## 解题思路
得到初步想法后，为减少不必要的麻烦，我们规定每次操作中 $a_i≥a_j$（易得操作数顺序不影响整体结果），则每次操作后 $a_i$ 不变，$a_j$ 变为 $\operatorname{mex}(a_i,a_j)$。

由前文分析结合贪心思想我们猜测，$a_j$ 取 $0$ 操作才对结果有贡献。此时，由 $\operatorname{mex}$ 的定义，我们发现：当且仅当 $a_i=1$ 时 $a_j$ 变为 $2$（总和加 $2$），否则 $a_j$ 总是变为 $1$（总和加 $1$）。那么，正解是否就是将所有的 $0$ 变换掉呢？

顺着这个想法，我们可以发现，当原序列含 $1$ 时，每个 $0$ 都能变换成为 $2$；否则第一个 $0$ 变换为 $1$ 后后续每个 $0$ 都能变换成为 $2$。这题是否就此大功告成了呢？

注意，这有一个**思维陷阱**（本人赛时也曾[陷入过](https://www.luogu.com.cn/record/200787321)，差点以为贪心假了）！我们不仅可以对现成的 $0$ 进行操作，还能变换出 $0$！当正整数数量大于 $1$ 时，任意正整数都能经变换产生 $0$，而 $0$ 再次变换会成为 $1$ 或 $2$，则当序列中 $1$ 的数量大于 $1$ 时，将其中一个 $1$ 变换反而会使和增加。这样，再统计 $1$ 的数量，我们就能得到正解了。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;long long sum;
int cnt,cnt1=-1;
int main()
{ios::sync_with_stdio(0);
 cin.tie(0);
 cin>>n;
 for(int i=1,a;i<=n;i++)
 {cin>>a;
  if(a==0)
  cnt++;
  else 
  {if(a==1) cnt1++;
   sum=sum+a;
  }
 }
 //特判需格外注意变换能否进行
 if(cnt+cnt1==-1||n==1)
 {cout<<sum;
  return 0;
 }
 cout<<sum+cnt*2+cnt1;
 }
```
## Update 1.29
由讨论区得到的一些指正：对两个 $0$ 进行两次操作也可得到 $1$ 和 $2$，所以 $0,0$ 这组数据也能变换！

---

## 作者：LittleAcbg (赞：1)

验题人题解。

我们观察一个数对操作后得到的结果：

- $(0,0)\rightarrow(0,1)$
- $(0,1)\rightarrow(1,2)$
- $(0,n)\rightarrow(1,n)$（$n\ge2$）

而 $1\le x\le y$ 时 $(x,y)\rightarrow(0,y)$。

如果序列中有 $1$，那么它可以将所有 $0$ 都变成 $2$。

如果序列中没有 $1$，可以用 $0$ 和任何一个数搭配，将 $0$ 变成 $1$，再进行上述操作。

如果 $0$ 和 $1$ 都没有，就不进行操作。

可以注意到，还有一种能够增加贡献的方案是 $(1,1)\rightarrow(0,1)\rightarrow(1,2)$。

因此，如果序列中有 $1$，可保留一个 $1$，将其余 $1$ 和所有 $0$ 均变为 $2$。

否则如果有 $0$，我们将一个 $0$ 变成 $1$，其他 $0$ 变成 $2$。

注意特殊情况：

```plain
1
0
```

此时不进行操作。

没有 $0$ 时也不进行操作。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a,n0,n1; // 0 和 1 的数量
ll ans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a);
        ans += a;
        if (!a) ++n0; // 统计 0 和 1 的数量
        else if (a == 1) ++n1;
    }
    if (n1) // 有 1
        ans += n0 * 2 + n1 - 1; // 0 贡献 +2，1 贡献 +1
    else if (n0 >= 1 && (n0 != 1 || n != 1)) // 不是 1 0 的情况（参考上文），且有 0
        ans += (n0 - 1) * 2 + 1; // 一个 +1，其余 +2
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：wantongxue (赞：1)

# P11638 Max,Mex
[传送门](https://www.luogu.com.cn/problem/P11638)
## 思路
容易发现能使操作后总和增大的一对 $(i,j)$ 只能为 $(x,0)$。

- 总和增加 $2$ $(x=1)$。
- 总和增加 $1$ $(x\ne1)$。

容易发现 $1$ 和 $0$ 可以互相转化。

- 通过 $(1,x)$ 可以将 $1$ 转化为 $0$ $(x\ne0)$。

- 通过 $(0,x)$ 可以将 $0$ 转化为 $1$ 。

因此我们只需要保留或创造一个 $1$ 并将余下 $1$ 和 $0$ 全部转换为 $0$ 后再全部转换为 $2$ 即可。

### hack

当 $n=1$ 时，这时无法操作，直接输出总和即可。

### Code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,ans,cnt,a;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a==0||a==1) cnt+=2-a;
		ans+=a;
	}
	if(cnt!=0&&n!=1) ans=ans+cnt-1;
	cout<<ans; 
	return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

特判 $n=1$。

容易发现 $\max$ 的部分对于总和并无帮助，而二元组的 $\text{mex}$ 又不会大于 $2$，我们可以得出结论：

> 所有满足 $a_i\ge2$ 的点，对其进行操作必然不优。

这一部分直接统计即可。

然后，我们充分利用大眼观察法。

注意到选中数对 $(0,1)$ 后，会转化为 $(1,2)$。

再注意到选中数对 $(0,0)$ 后，会转化为 $(0,1)$。

再再注意到选中数对 $(1,1)$ 后，会转化为 $(0,1)$。

~~注意力惊人。~~

那么我们就可以以保留一个 $1$ 为代价把所有 $0$ 或 $1$ 修改为 $2$ 了。

列式算一下就做完了。

---

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sum,ai;
int sum0,sum1,sum2;
signed main(){
    int n;
    cin>>n;
    if(n==1){
        int x;
        cin>>x;
        cout<<x;
        return 0;
    }
    for(int i=1;i<=n;i++)
    cin>>ai,sum0+=ai==0,sum1+=ai==1,sum2+=ai==2,sum+=ai;
    sum+=max(0ll,sum0*2+sum1-1);//显然不会变小
    cout<<sum;
    return 0;
}
```

---

## 作者：__CJY__ (赞：1)

##  思路
对于任意两个元素，如果其中一个是 $0$ 或 $1$，可以通过操作将其变成一个更大的值（可以是 $2$），从而增加序列的和；如果序列中没有 $0$ 或 $1$，则无法通过操作增加和。

首先把该读的都读入进来，计算序列的总和 $s$，统计序列中 $0$ 的个数 $c_0$ 和 $1$ 的个数 $c_1$。

如果序列中没有 $0$ 或 $1$（即 $c_0+c_1=0$），则无法通过任何操作增加序列的和。因此，直接输出初始和 $s$。

如果序列中有 $0$ 或 $1$，可以通过操作来增加和：
* 每个 $0$ 可以变成 $2$（通过与任何大于 $1$ 的元素进行操作），因此每个 $0$ 贡献 $2$。
* 每个 $1$ 可以变成 $2$（通过与任何大于 $1$ 的元素进行操作），因此每个 $1$ 贡献 $1$。

由于初始和中已经包含了一个 $1$ 的贡献，所以在计算最终和时，需要减去一个 $1$ 以避免重复计算。

所以最终答案是 $2 \times c_0+c_1+s-1$，其中 $2 \times c_0$ 表示所有 $0$ 变成 $2$ 的贡献，$c_1$ 表示所有 $1$ 变成 $2$ 的贡献，$s-1$ 是因为原始和中已经包含了一个 $1$ 的贡献。

---

## 作者：Luogu_916767 (赞：0)

### 题目大意

给定一个长度为 $n$ 的序列 $a$。

一次操作你可以选定一个 $(i,j)$，满足 $1\le i,j\le n$ 以及 $i\neq j$，令 $x=\max\{a_i,a_j\}$，$y=\operatorname{mex}\{a_i,a_j\}$，那么 $a_i=x$，$a_j=y$。

### 思路分析

看着太复杂了，我们简化一下，不放令 $a_i > a_j$。则：

一次操作你可以选定一个 $(i,j)$，满足 $1\le i,j\le n$ 以及 $i\neq j$，令 $y=\operatorname{mex}\{a_i,a_j\}$，那么让 $a_j=y$。

不难发现，如果 $a_i \ge 2$ 且 $a_j \ge 2$ 则此操作之后，和一定会变小。

所以我们一共有 $3$ 种情况：

* $(0, 0)$，我们可以将其变成 $(0, 1)$，再将其变成 $(1, 2)$，再将其变成 $(0, 2)$。
* $(1, 0)$，我们可以将其变成 $(1, 2)$，再将其变成 $(0, 2)$。
* $(1, 1)$，我们可以将其变成 $(1, 0)$，再将其变成 $(1, 2)$，再将其变成 $(0, 2)$。

总结一下，我们可以将任意两个 $0$ 或 $1$ 的数变成 $(0, 2)$。最后剩下的 $0$ 我们随便找一个数把它变成 $1$ 就好了。

### Code

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int n,x;
int ans,sum;

signed main(){
	cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        if(x >= 2){
            ans+=x;
        }else{
            sum ++ ;
        }
    }
    if(n == 1){
        cout<<x;
        return 0;
    }
    ans += 2 * sum;
    if(sum){
        ans -- ;
    }
    cout<<ans;
	return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
首先可以发现，算出的两个数放在哪个上并不关键。

其次，对于操作，当 $x \ge 2$ 且 $y \ge 2$ 时，显然不优。

当 $x = 0$ 时，只要还有**另一个**数，那么 $x$ 可变为一，贡献为一。

当 $x = 1$ 时，只要还有一个**零**，那么 $x$ 可以变为二，贡献为一。

当数组中有 $1$ 无 $0$ 时，可用两个一生产出 $0,1$ ，再次操作为 $1,2$。

当数组中有 $0$ 无 $1$ 时，可用两个零生产出 $0,1$ ，再次操作为 $1,2$。

当数组中无 $0$ 无 $1$ 时，不必操作。

整合一下：

若数组中无零无一，则输出和。

只要有两个以上的零或一，即可生产一个二，零一数量减少一个。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,n,zero,ans,one;
bool f;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		
		if(a==1||a==0){
			if(!f)f=1;
			else ans+=2;
		}
		else ans+=a;
	}
	if(f&&n>1)ans++;
	cout<<ans;
}
```
含 mex 操作的题：

[绿题](https://www.luogu.com.cn/problem/P10369)。

---

## 作者：glass_goldfish (赞：0)

如果两个操作数 $x,y$ 进行操作，那么只有 $x=0$ 或是 $y=0$ 时才能让这两个数的和增加。但是，我们不仅可以把 $0$ 变成其他数，还能把其他数（比如 $1$）变为 $0$！把所有的 $1$ 变为 $0$，然后和其他数配对，就是最优解。

所以，最终答案就是（假设一共有 $orz$ 个 $0$ 和 $1$，去除了序列中的 $0$ 和 $1$ 之后序列的和为 $ans$）：
$$ans+2\times orz-1$$

这个式子中的 $-1$ 是因为第一个变换后的 $0$（原先序列中的 $0$ 和 $1$）只能变为 $1$，而其他变换后的 $0$（原先序列中的 $0$ 和 $1$）能够变为 $2$。

但是，这里有个坑点（hack 数据）：如果 $n=1$，那么最终的答案只能是序列的和，而不是上面那个式子。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f
using namespace std;
int n,x,ans,orz;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(x==0||x==1)orz++;
		else ans+=x;
	}
	if(n!=1&&orz!=0)cout<<ans+2*orz-1;
	else cout<<ans;
	return 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

读完题，我们会发现，因为我们要把所选的一个数变为两数最大值，而另一个数为两数的 $mex$。所以，所选取的两个数中，有一个一定为 $0$，否则答案就会变劣。

那么，我们就可以考虑 $0$ 和什么数搭配可以使答案变优。

如果所选数为两个 $0$，那么就可以变为一个 $0$ 和一个 $1$，然后变为 $1$ 和 $2$，且最后的 $1$ 可以和其它 $0$ 搭配。而其余的情况的，都可以使其产生一个 $1$。

因为 $0$ 能变 $1$，$1$ 能变 $2$。所以，每一个 $0$ 产生的贡献为 $2$，每一个 $1$ 产生的贡献为 $1$，所以我们可以直接计算。

若有 $0$ 和 $1$，则最后答案要减去 $1$，因为最后的 $0$ 和 $1$ 不可以合并。

若 $n$ 为 $1$，则无法合并，需要特判。

总时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

下面是代码环节：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, sum, num, num1;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		int x;
		cin >> x;
		sum += x;
		if (x == 0) {
			num ++;
		} else if (x == 1) {
			num1 ++;
		}
	}
	if (n == 1) {
		cout << sum;
		return 0;
	}
	sum += num * 2 + num1;
	if (num || num1) {
		sum --;
	}
	cout << sum;
	return 0;
}
```

---

