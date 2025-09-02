# [ABC371E] I Hate Sigma Problems

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc371/tasks/abc371_e

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。また、$ f(l,r) $ を以下で定義します。

- $ (A_l,A_{l+1},\ldots,A_{r-1},A_{r}) $ に含まれる値の種類数
 
次の式の値を求めてください。

 $ \displaystyle\ \sum_{i=1}^{N}\sum_{j=i}^N\ f(i,j) $

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\leq\ N $
- 入力される数値は全て整数
 
### Sample Explanation 1

$ f(1,2) $ について考えます。$ (A_1,A_2)=(1,2) $ に含まれる値の種類数は $ 2 $ なので $ f(1,2)=2 $ です。 $ f(2,3) $ について考えます。$ (A_2,A_3)=(2,2) $ に含まれる値の種類数は $ 1 $ なので $ f(2,3)=1 $ です。 $ f $ の総和は $ 8 $ となります。

## 样例 #1

### 输入

```
3
1 2 2```

### 输出

```
8```

## 样例 #2

### 输入

```
9
5 4 2 2 3 2 4 4 1```

### 输出

```
111```

# 题解

## 作者：__Allen_123__ (赞：52)

你是一名 OI 教练。在一场比赛之前，你准备让你的学生更熟悉各种题型。

> 题库中有 $n$ 道题目，其中第 $i$ 道题目的题型为 $a_i$。在复习的时候一名学生只能刷题库中一段连续非空的题目。
>
> 身为一名教练，你想知道题库中的各种训练方式达到的效果。于是你想知道，每一个复习方案（即选题方案）中，有多少种不同的题型，输出它们的和。
>
> 即：设 $f(i,j)$ 代表 $a$ 中下标 $[i,j]$ 区间内的不同数字个数，请求出 $\sum\limits_{l=1}^{n} \sum\limits_{r=l}^{n}f(l,r)$ 的值。

你马上想到可以对于每一个 $a_i$，记录它上一次出现的位置 $lst_{a_i}$（如果没有则设为 $0$）。在考虑 $a_i$ 时，忽略其他题型对结果的影响。

相比上次而言，你如果想准确地求出每种方案中不同题型的总数和，需要把左端点在 $(lst_{a_i},a_i]$ 区间内，而右端点在 $[a_i,n]$ 内的区间数量计入答案，这样可以保证不重不漏，证明显然。

按照你的这种思路，当遍历到 $a_i$ 时，把最终答案加上 $(i-lst_{a_i})\times (n-i+1)$ 即可。

这样，对于每种题型，遍历到它时都这样计算答案，就得到了计入所有题型的结果。

[你的 AC 代码](https://atcoder.jp/contests/abc371/submissions/57793277)。

身为一名过去的 OI loser，你现在就正在为一群很可能成为 OI loser 的学生进行指导。而他们又有可能成为未来的 OI 教练。由此循环再循环。OI 也因此在。蓬勃地发展着啊。

几万人都有志于 OI，可最终只剩下几十个人成功。身为教练的你，也不知道他们会在哪里脱节。你能做的，只有让他们在这一节充分发挥自己的能力。至于他们自己，你也没办法。

你想起了你自己是 OIer 的时候，和机房的同学一起攻克难题或是摸鱼的回忆。你想起了第一次 AC 一道省选难度的题时你的快乐。你想起了你第一次 AK 模拟赛，被同学膜拜时的满足。但这一切都已经过去，一个失败者不会被人们喝彩。这些回忆只会让你感到更加悲伤。你绝望地在你的代码后面增加了几十行 `// I hate OI problems`，来发泄你的情绪，抒发你对 OI 题目的憎恨。

你被叫醒了。眼前的题目名称与代码重合，似乎早已有人比你更早抒发着自己的情绪。原来你在讲解一道 ABC 的 E 题时陷入了过于深刻的沉思，乃至趴倒在了桌子上。回忆与现实重叠，让你无法发话。因为，他们也是过去的你，你也是他们的未来。

---

## 作者：small_lemon_qwq (赞：20)

对于每个区间，如果有重复的数，我们认为最早出现的那个数有贡献。

例如 $1,2,3,4,1,4,5$ 中，第 $1,2,3,4,7$ 个数对答案有贡献。

统计每个数对答案的贡献即可。

我们设 $j$ 为满足 $a_j=a_i$ 且 $j<i$ 的最大值（若不存在为 $0$），那么 $a_i$ 的贡献就是 $(i-j)\times(n-i+1)$，其中 $(i-j)$ 为左端点的可能数，$(n-i+1)$ 为右端点的可能数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],ans;
unordered_map<int,int>mp;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=(i-mp[a[i]])*(n-i+1);
		mp[a[i]]=i;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：dayz_break404 (赞：11)

简单题，赛时 A 得还是太慢了qwq。

### 题目描述

求序列中每一个子区间内含有不同数字的个数之和。

### 题目分析

看一眼数据范围，$O(n^2)$ 枚举每个区间肯定是不行的，必须需要线性的做法。

考虑添加每一个数字后对答案的贡献，枚举每一个区间的右端点，假设当前已经枚举到序列的 $i$ 位置，区间 $[1,i-1],[2,i-1],\dots,[i-2,i-1]$ 的对答案的总贡献为 $sum$，对于右端点从 $i-1$ 变化到 $i$ 对答案贡献的变化，进行分类讨论。

记 $las_{a_i}$ 表示 $i$ 之前距离 $i$ 最近的一个 $a_i$ 出现的位置。

1. 若 $las_{a_i}$ 为 $0$，说明之前的序列中从未出现过数字 $a_i$，那么对于任意一个 $1\le j<i-1 $，区间 $[j,i]$ 对答案的贡献必定会在 $[j,i-1]$ 的基础上增加 $1$，同时也会新增一个新的区间 $[i-1,i]$，对答案的贡献为 $2$，所以当前以 $i$ 作为右端点的区间对答案的贡献为 $sum+(i-2)\times 1+2=sum+i$。

2. 若 $las_{a_i}$ 不为 $0$，那么对于 $1\le j<las_{a_i}-1$，区间 $[j,las_{a_i}]$ 对答案的贡献不变；对于 $las_{a_i}\le j<i-2$，区间 $[j,i]$ 对答案的贡献在之前的基础上增加 $1$，同时会新增区间 $[i-1,i]$。

   追求严谨，再进行分类讨论：当 $las_i$ 等于 $i-1$ 时该区间对答案的贡献为 $1$，此时以 $i$ 为右端点的区间的总答案为 $sum+1$；当 $las_i$ 不等于 $i-1$ 时该区间对答案的贡献为 $2$，此时以 $i$ 为右端点的区间的总答案为 $sum+(i-2-las_{a_i})+2=sum+i-las_{a_i}$。（其实如果你细心便会发现当 $las_i$ 等于 $i-1$ 时 $sum+i-las_{a_i}$ 也是其总答案）

每次将 $ans$ 加上 $sum$ 即可，$las_{a_i}$ 数组也很好维护，每次更新即可，记得最后答案加上每个单个数字的答案 $n$。虽然分讨感觉很麻烦，代码还是很短的。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
#define ll long long
const int maxn=2e5+20;
int n,a[maxn],las[maxn];
ll ans,sum;
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	las[a[1]]=1;
	for(int i=2;i<=n;i++){
		if(las[a[i]]) sum+=i-las[a[i]];
		else sum+=i;
		ans+=sum;
		las[a[i]]=i;
	}
	ans+=n;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：csgpx (赞：4)

洛谷题目链接：[AT_abc371_e](https://www.luogu.com.cn/problem/AT_abc371_e)。

赛时把 `v[i]` 打成 `v[a[i]]`,赛后一分钟过了。。。


---


题目大意：给一个整数序列，求所有连续子序列中不同值个数之和。

一开始想暴力枚举，因为看错题了。后来发现会超时，但没有答案累加的思路，就换了个方向：是否可以先假设每一子序列都有 $g$ 个贡献（$g$ 为整数序列中不同值的总数），再减去每一种值没有贡献的个数？所以首先计算出总贡献 $s$：

$$s = n \times (n + 1) \div 2 \times g$$

$n \times (n + 1) \div 2$ 为连续子序列个数，乘上 $g$ 则表示每个子序列都有 $g$ 个不同值。

为什么 $n \times (n + 1) \div 2$ 为连续子序列个数？

- 以 $1$ 为下标的元素为序列开头，有 $n$ 个子序列。

- 以 $2$ 为下标的元素为序列开头，有 $(n - 1)$ 个子序列。

- 以 $3$ 为下标的元素为序列开头，有 $(n - 2)$ 个子序列。

- ……

以此类推，连续子序列个数为： $1 + 2 + 3 + 4 + \cdots + n$，即：$n \times (n + 1) \div 2$。

再对每一种值没有贡献的个数进行讨论：

假设有序列 $1,3,2,2,3,2$。

对于 $1$，无贡献的子序列为：

- 第一个 $1$ 前没有子序列，即 $0 \times (0 + 1) \div 2 = 0$。

- 第一个 $1$ 至整数序列末尾的 $3,2,2,3,2$ 及其子序列，即 $5 \times (5 + 1) \div 2 = 15$。

共 $15$ 个子序列无贡献。

对于 $3$，无贡献的子序列为：

- 第一个 $3$ 前的 $1$，即 $1 \times (1 + 1) \div 2 = 1$。

- 第一个 $3$ 与第二个 $3$ 中间的 $2,2$ 及其子序列，即 $2 \times (2 + 1) \div 2 = 3$。

- 第二个 $3$ 至整数序列末尾的 $2$，即 $1 \times (1 + 1) \div 2 = 1$。

共 $5$ 个子序列无贡献。

对于 $2$，无贡献的子序列为：

- 第一个 $2$ 前的 $1,3$，即 $2 \times (2 + 1) \div 2 = 3$。

- 第一个 $2$ 与第二个 $2$ 中间没有子序列，即 $0 \times (0 + 1) \div 2 = 0$。

- 第二个 $2$ 与第三个 $2$ 中间的 $3$，即 $1 \times (1 + 1) \div 2 = 1$。

- 第三个 $2$ 至整数序列末尾没有子序列，即 $0 \times (0 + 1) \div 2 = 0$。

共 $4$ 个子序列无贡献。

因此，答案为 $ans = s - 15 - 5 - 4 = 39$。

可以发现，不同的值没有贡献的地方为当前出现的位置到上一次出现的位置中间的子序列及其子序列。

特别地，设一开始出现的位置为 $0$，最后出现的位置为 $n + 1$。

所以代码就出来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200010],g,ans,v[200010];//v[i]记录上一个值i出现的位置
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		if(!v[a[i]]) v[a[i]]=i,g++;
	} 
	ans=n*(n+1)/2*g;
	memset(v,0,sizeof v);
	for(long long i=1;i<=n;i++){
		long long s=i-v[a[i]]-1;
		ans-=s*(s+1)/2;
		v[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(v[i]){
			long long s=n-v[i];//就是这里!
			ans-=s*(s+1)/2;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Orange_qwq (赞：3)

[洛谷题目](https://www.luogu.com.cn/problem/AT_abc371_e) && [AT 链接](https://atcoder.jp/contests/abc371/tasks/abc371_e)。

赛时没想出来，智力堪忧。

upd：有一个链接打错了，麻烦管理员了 qwq。

## 题目大意

给你一个序列，求所有连续子串中，每个子串的不同的数的个数和。

## 思路

枚举子串显然会超时。

正难则反，既然从原序列考虑单个数行不通，那我们从单个数考虑对答案的贡献。

假设我们有一个序列 $A={a_1,a_2,\dots ,a_n}$，其中 $a_i(1\le i\le n)$ 互不相同。对于每个数，子串的起点在数的左边或是从这个数开始，子串的终点在这个数右边或是在这个数结束，满足这两个条件的子串，都包括这个数的贡献。所以我们可以根据乘法原理，在一段没有相同数的区间内，计算这个数的贡献。

那如果序列 $A$ 有重复的数字呢？

如果一个子串包括了重复的数，即子串的起点和终点在重复的数的两边，那么这些数的贡献只能是 $1$。但是如果一个子串只包括了一个数，那么这个数也贡献 $1$。

所以我们可以想到把上一次 $a_i$ 出现的位置记录下来。设当前的位置为 $i$，上一次 $a_i$ 出现的位置为 $j$，那么对于起点在 $(i,j]$ 之间的子串，$a_j$ 没有贡献，但 $a_i$ 都有贡献。我们每一次把数的贡献叠加就是答案。

这样会不会重复呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/zf883454.png)

如图所示，记两个标蓝的方块为重复的数。由于起点的不同，这样计算答案不会有重复。如果还是不清楚的可以自己手摸一遍，看图应该就能懂了。

## AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans;
int n, la[200010];
bool v[200010]; 
int main() {
	scanf("%d", &n);
	for (int i = 1, a; i <= n; ++i) {
		scanf("%d", &a);
		if (!v[a]) v[a] = 1;
		ans += (i - la[a]) * 1ll * (n - i + 1) * 1ll;
		v[a] = 1;
		la[a] = i;
	}
	printf("%lld", ans);
	return 0;
} 
```

---

## 作者：_ayaka_ (赞：2)

### 思路

我们将题目中的值称为“颜色”，用一个 $a$ 数组表示。

对于所有求区间不同数的数量的问题，我们的暴力算法是这样的：

- 从左端点到右端点，依次检索所有点；

- 如果此点的颜色未被标记，则标记此颜色的点。

那所有对此区间提供了贡献的点都是某个颜色在此区间第一次出现的点。

我们按照这个思路来看这道题，可以看出每个点所提供的贡献就是所有满足以此点为此点的颜色第一次出现的点的子区间的数量。

看不懂？举个例子，这里有一个数列，里面的元素为：$1,2,3,2,2$。我们以第四个点为例，计算第四个点的贡献。第四个点的颜色为 $2$，那所有以第四个点为颜色 $2$ 第一次出现的区间为：$\{3,4\},\{4,4\},\{4,5\}$。左端点扩展到第二个点就不行了，因为第二个点的颜色也是 $2$，将第二个点包含进去后，第四个点就不是第一个出现的点了。

不难发现这样的计算是有规律的，我们用 $last_i$ 表示第 $i$ 个颜色上次出现的下标，那只要左端点在 $last_{a_i}+1$ 到 $i$ 之间，右端点在 $i$ 到 $n$ 之间，第 $i$ 个点就有贡献。

我们就可以得出，第 $i$ 个点的贡献为 $(n-i+1)\times(i-last_{a_i})$。用此公式进行求解所有点的贡献，时间复杂度 $O(n)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],last[200005],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		ans+=(n-i+1)*(i-last[a[i]]);
		last[a[i]]=i;//更新last
	}
	cout<<ans;
}

```

---

## 作者：chenxi2009 (赞：1)

[专栏](https://www.luogu.com.cn/article/xto7v55s)食用效果更佳。
# 题目描述

给定一个长度为 $N$ 的数列 $A={A_1,A_2,\cdots A_N}$。定义 $f(l,r)$ 为 $A_l,A_{l + 1},\cdots A_N$ 中不同数的数量，求

$$
\sum_{i=1}^{n}\sum_{j=i}^{n}f(i,j)
$$

的值。

# 输入格式

第一行一个整数 $N$。\
第二行 $N$ 个整数，第 $i$ 个数为 $A_i$。

# 输出格式

输出答案。

# 数据范围

$1\le N\le 2\times 10^5$\
$1\le A_i\le N$\
$N \in \Z,A_i\in \Z$

# 解题思路

考虑每个数对答案 $ans$ 的贡献。

如果一个数 $x$ 未曾出现，它的贡献为 $0$；

如果一个数 $x$ 出现过，令其出现次数为 $apr_x$，并令大小为 $apr_x$ 的数组 $v_x$ 为记录出现的位置。形式化而言，$\forall i\in v_x,A_i=x$；$\forall i\notin v_x,A_i \ne x$。

容易发现，所有包含 $v$ 中元素的 $A$ 的子区间都对答案做出了贡献。

**换一种说法**，所有不包含 $v$ 中元素的区间都对答案没有贡献，其他的区间则对答案有贡献。

不包含 $v$ 中元素的区间是哪些呢？自然是包含于 $[1,v_1)$ 的区间，以及包含于 $(v_{x,1},v_{x,2})$ 的区间，以及包含于 $(v_{x,2},v_{x,3})$ 的区间…… 以及包含于 $(v_{x,apr_x-1},v_{x,apr_x})$ 的区间，以及包含于 $(v_{x,apr_x},n]$ 的区间。

一个普遍结论：对于区间 $[l,r]$，其子区间（包含的区间）有

$$
\frac{(r-l+2)\times(r-l+1)}{2}
$$

个。

于是对于上面的结论，数 $x$ **不作出贡献**的区间有

$$
\sum_{i=1}^{apr_x+1}{\frac{(v_{x,i}-v_{x,i-1})\times (v_{x,i}-v_{x,i-1}-1)}{2}}
$$

个。特别地，我们在其中令 $v_{x,0}=0,v_{apr_x+1}=N+1$。

总共有 $\frac{1}{2}N\times (N-1)$ 个区间，除去上面不作出贡献的，就是 $x$ 做出的贡献数。\
根据数据范围，对于每个 $x\in [1,n]$ 计算一遍即可。

由于 $(\sum_{i=1}^{N}{apr_i})=N$，所以时间复杂度为 $O(N)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
long long ans,ubl,las;
vector<int>v[200001];
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a[i]);
		v[a[i]].push_back(i);
	}
	for(int i = 1;i <= n;i ++){
		if(!v[i].size()){
			continue;
		}
		ubl = las = 0;//ubl 为不做出贡献的区间个数 
		for(int j = 0;j < v[i].size();j ++){
			ubl += (v[i][j] - las) * (v[i][j] - las - 1) / 2;
			las = v[i][j];
		}
		ubl += (n - las + 1) * (n - las) / 2;
		ans += ((long long)(n + 1)) * n / 2 - ubl;//累加贡献 
	}
	printf("%lld",ans);
	return 0;
}
```

记得在需要的位置开 `long long`。

---

## 作者：Lotus_Land (赞：1)

### 题意

给定一个长度为 $N$ 的数列 $A=(A_1,A_2,\dots,A_N)$。定义 $f(i,j)$ 为 $(A_i,A_{i+1},\dots,A_j)$ 中不同元素的种类数。求 $\sum\limits_{i=1}^{N}\sum\limits_{j=i}^{N}f(i,j)$。

### 分析

I Hate Sigma Problems.

最近的 E 好像一次比一次简单了。

考虑枚举右端点。记 $lst_{i}$ 为 $i$ 这个数最后一次出现的位置。每次在右端加入一个数，对前面所有左端点的影响：对 $1$ 到 $lst_i$ 的位置没有影响，对 $lst_{i}+1$ 到当前位置有影响。~~然后我就写了线段树，其实没必要。~~ 统计答案并更新 $lst_i$。

```cpp
int n;
int lst[N],a[N];
LL ans,sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		sum+=i-lst[a[i]];
		lst[a[i]]=i;
		ans+=sum;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：No_Rest (赞：0)

# 思路

典。

设对于每一个区间的每种数 $i$，将区间内第一个 $i$ 的贡献加一。

考虑每个数的贡献。对于 $a_i$，设 $a_i$ 前面第一个跟它相等的数的位置为 $b_i$。显然贡献为满足区间内不包含位置比 $i$ 更靠前的 $a_i$ 的区间个数。这样的话，区间左端点应该在 $(b_i , i]$ 这个区间内。容易看出，只要左端点在 $(b_i, i]$ 这个区间内，右端点只要在 $i$ 的右边（包括 $i$），$a_i$ 就一定是该区间内出现的第一个 $a_i$。这样 $a_i$ 的贡献为 $(i - b_i) \times (n - i + 1)$。若 $a_i$ 是数组内第一个 $a_i$ 要特判，贡献为 $i \times (n - i + 1)$。

对于 $b_i$ 的计算，我选择用 vector 存每种数出现的位置。但是 $a_i$ 数据范围很大，所以要离散化一下。

时间复杂度 $\mathcal O(n \log n)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 2e5 + 5;
ll n, a[maxn], b[maxn], m, ans;
vector <ll> v[maxn];
unordered_map <ll, ll> mp;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for(ll i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);//离散化
	m = unique(b + 1, b + n + 1) - b;
	for(ll i = 1; i <= m; ++i) mp[b[i]] = i;
	for(ll i = 1; i <= n; ++i) v[mp[a[i]]].push_back(i);
	for(ll i = 1; i <= m; ++i)
		for(ll j = 0; j < v[i].size(); ++j)
			if(!j) ans += v[i][j] * (n - v[i][j] + 1);//特判
			else ans += (v[i][j] - v[i][j - 1]) * (n - v[i][j] + 1);
	cout << ans;
	return 0;
} 

```

---

## 作者：CaoSheng_zzz (赞：0)

考虑每个点的贡献，及每个点的点权在每个区间第一次出现会对区间产生贡献。

那怎么统计区间，对于当前点产生的贡献为前面一个相同点权的点后面一个点到当前点总共的区间数量，对于区间数量的计算我们可以用到高斯求和公式。

```cpp
	int n = read() ; vector<int> a(n) ;
	int ans = 0 ;
	for(int i=0 ; i<n ; i++) {
		int A = read() ;
		ans += (n - i) * ((i + 1) - a[A - 1]) ;
		a[A - 1] = i + 1 ;
	}
	output(ans) , ent ;
	return 0 ;
```

---

## 作者：Liyunze123 (赞：0)

# 题意
设 $f(i,j)$ 为 $i$ 到 $j$ 不同数字个数。

求 $\displaystyle\ \sum_{i=1}^{N}\sum_{j=i}^N\ f(i,j)$。
# 题解
不难把式子转换成 $\displaystyle\ \sum_{i=1}^{n}\sum_{j=1}^i\ f(j,i)$。

即对于每个 $i$，只要求 $\displaystyle \sum_{j=1}^i\ f(j,i)$。求值可以从 $i\times (i+1) \div 2$ 减去重复数字的影响。

设上次减去了 $s$，这次还得减 $s$。因为 $f(i,j)$ 中减了几，$f(i,j+1)$ 至少得减同样的数。

还要减去 $a_i$ 的影响，就是 $a_i$ 上一次出现的位置，设其为 $k$，那么 $f(1,i)$ 一直到 $f(k,i)$ 都额外出现一个重复数字，总共减了 $k$。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],c[200010],b[200010];
long long s,ans,u;
vector<int>e;
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++)scanf("%d",&a[w]),e.push_back(w);
	sort(e.begin(),e.end()),e.erase(unique(e.begin(),e.end()),e.end());
	for(int w=1;w<=n;w++)a[w]=lower_bound(e.begin(),e.end(),a[w])-e.begin();
	for(int w=1;w<=n;w++){
		long long t=w*(w+1ll)/2;
		if(c[a[w]])s+=c[a[w]],c[a[w]]=w;
		else c[a[w]]=w;
		ans+=t-s;
	}
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一个长度为 $n$ 的数组 $a$，定义 $f(l,r)$ 为 $a_l,a_{l+1},\cdots,a_r$ 中值的种类数。求：
> $$
> \sum_{i=1}^n\sum_{j=i}^n f(i,j)
> $$
> $n\le 2\times 10^5$，$1\le a_i\le n$。

## 解法

考虑 dp。令 $g(i)$ 表示 $\sum_{j\le i} f(j,i)$ 的值，尝试从 $g(i-1)$ 转移到 $g(i)$。我们用一个 $t$ 数组记录一下每个值**最近一次出现的位置**，初始设为 $0$；那么对于 $i$，它的值有贡献当且仅当 $j\in (t_{a_i},i]$，即区间中还没有 $a_i$ 的值时 $a_i$ 加入会有 $1$ 的贡献；这样的区间一共有 $i-t_{a_i}$ 个，即 $a_i$ 的贡献，那么就有转移：
$$
g(i)=g(i-1)+i-t_{a_i}
$$
边转移边更新 $t$，答案取 $\sum g(i)$ 即可。时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn], g[maxn], n;
#define ll long long
ll f[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	f[1] = 1, g[a[1]] = 1; ll ans = f[1];
	for (int i = 2; i <= n; i ++) 
		f[i] = f[i - 1] + i - g[a[i]], g[a[i]] = i, ans += f[i];
	return printf("%lld\n", ans), 0;
}
```

---

## 作者：zdd6310 (赞：0)

# [ABC371E] I Hate Sigma Problems

## Description

给你一个长度为 $n$ 的序列 $a$。

定义函数 $f(l,r)$ 为 $a_l,a_{l+1},\dots,a_{r}$ 中出现不同数的个数。

求 $\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}f(l,r)$。

## solution

可以对与每一个数来考虑。

对于一个数值 $c$，$c$ 对于一个区间 $[l,r]$ 有贡献当且仅当存在 $i\in [l,r]$，$a_i=c$。

而且这个数值对于一个区间的贡献就是 0 或者 1。因为是不用数的个数，出现多次算一次。

发现这东西不好算，正难则反。

求有多少个区间的贡献是 0。也就是多少个区间没有出现过 $c$。

将每一个 $c$ 出现的位置记录下来，相邻两个出现位置之间 的区间 全部没有出现过 $c$。

这可以用 vector 记录，直接全部颜色扫一遍就好了，复杂度 $O(n)$。

## code

小技巧：可以在 vector 的最前添加 0，最后添加 $n+1$，就不用额外计算了。

---

