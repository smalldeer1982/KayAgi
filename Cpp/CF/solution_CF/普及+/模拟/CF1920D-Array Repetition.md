# Array Repetition

## 题目描述

Jayden has an array $ a $ which is initially empty. There are $ n $ operations of two types he must perform in the given order.

1. Jayden appends an integer $ x $ ( $ 1 \leq x \leq n $ ) to the end of array $ a $ .
2. Jayden appends $ x $ copies of array $ a $ to the end of array $ a $ . In other words, array $ a $ becomes $ [a,\underbrace{a,\ldots,a}_{x}] $ . It is guaranteed that he has done at least one operation of the first type before this.

Jayden has $ q $ queries. For each query, you must tell him the $ k $ -th element of array $ a $ . The elements of the array are numbered from $ 1 $ .

## 说明/提示

In the first test case:

- After the first operation $ a = [1] $ ;
- After the second operation $ a = [1, 2] $ ;
- After the third operation $ a = [1, 2, 1, 2] $ ;
- After the fourth operation $ a = [1, 2, 1, 2, 3] $ ;
- After the fifth operation $ a = [1, 2, 1, 2, 3, 1, 2, 1, 2, 3, 1, 2, 1, 2, 3, 1, 2, 1, 2, 3] $ .

In the fourth test case, after all operations $ a = [1, 2] $ .

## 样例 #1

### 输入

```
4
5 10
1 1
1 2
2 1
1 3
2 3
1 2 3 4 5 6 14 15 16 20
10 10
1 3
1 8
2 15
1 6
1 9
1 1
2 6
1 1
2 12
2 10
32752 25178 3198 3199 2460 2461 31450 33260 9016 4996
12 5
1 6
1 11
2 392130334
1 4
2 744811750
1 10
1 5
2 209373780
2 178928984
1 3
2 658326464
2 1000000000
914576963034536490 640707385283752918 636773368365261971 584126563607944922 1000000000000000000
2 2
1 1
1 2
1 2```

### 输出

```
1 2 1 2 3 1 2 3 1 3
9 8 1 3 1 3 6 3 8 8
11 11 11 10 11
1 2```

# 题解

## 作者：Luzhuoyuan (赞：14)

### 题目链接

[[to Codeforces]](https://codeforces.com/contest/1920/problem/D) [[to Luogu]](https://www.luogu.com.cn/problem/CF1920D)

### 题意简述

有一个初始为空的序列 $a$，你需要对其进行 $n$ 次操作，每次操作为以下两种之一：

- `1 x`：向序列末尾加入一个正整数 $x$；
- `2 x`：将序列**复制 $x$ 份**插入原序列末尾，保证之前已经进行过 $1$ 操作。

所有操作结束后有 $q$ 个询问，每次给定一个正整数 $k$，表示询问最终序列第 $k$ 位的数（序列从 $1$ 开始编号）。每个测试点 $t$ 组测试用例。

$1\le t\le 5000;1\le n,q,\sum n,\sum q\le 10^5;1\le k\le\min(10^{18},c)$，其中 $c$ 为最终序列长度；对于操作 $1$，$1\le x\le n$；对于操作 $2$，$1\le x\le 10^9$。

### 做法

看到题目，我们很容易想出一种方法：预处理第 $i$ 次操作后的序列长度 $l_i$，倒序枚举每个操作，并让 $k$ 不停对 $l_i$ 取模，如果处理到一个操作 $1$ 且此时 $k=0$，那么答案就是这个操作中的 $x$。

但是显然这样是不行的，最终序列会超级超级长，询问也太多了。我们发现 $k\le 10^{18}$，也就是说只会询问到 $10^{18}$ 以内的位置，于是我们惊奇地发现有用的 $2$ 操作至多只有 $\lfloor\log 10^{18}\rfloor=59$ 次，因为每次 $2$ 操作至少将序列长度变为原来的 $2$ 倍，后面的操作都没被访问到，可以直接忽略。

但是还有一个问题：如果 $1$ 操作太多，时间还是会爆炸。所以我们对每个 $2$ 操作开一个 `vector`，把它之后到下一个 $2$ 操作之前的每个 $1$ 操作存进去，并记录第 $i$ 个 $2$ 操作刚操作完的长度 $g_i$ 以及下一个 $2$ 操作之前的最后一个操作结束后的长度 $l_i$。如果取模后 $k>g_i$，那么直接按照模数在 `vector` 中找就行了。复杂度为 $O(q\log V)$，其中 $V$ 为 $k$ 的值域。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;
const int N=1e5+5;
int T,n,m,k,op[N],a[N],l[70],g[70];
vector<int> ve[70];
inline int read(){
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
signed main(){
    T=read();
    while(T--){
        n=read(),m=read();k=0;
        for(int i=1;i<=n;i++)op[i]=read(),a[i]=read();
        for(int i=0;i<=60;i++)ve[i].clear();
        l[0]=g[0]=0;
        for(int i=1;i<=n;i++){
            if(op[i]==1){ve[k].pb(a[i]),l[k]++;if(l[k]>1e18)break;}
            else{k++;if(l[k-1]>1e18/(a[i]+1)){k--;break;}l[k]=g[k]=l[k-1]*(a[i]+1);}
        }
        while(m--){
            int x=read();
            for(int i=k;i>=0;i--){
                x=(x-1)%l[i]+1;
                if(x>g[i]){printf("%d ",ve[i][x-g[i]-1]);break;}
            }
        }
        puts("");
    }
    return 0;
}
```

（逃

---

## 作者：ax_by_c (赞：3)

# 闲话

其他题解怎么都用了个二分啊，是不是闲的啊。

# 题意简述

你需要维护一个数列，有 $n$ 次操作。

操作一：在数列末尾添加一个数。

操作二：把整个数列复制若干遍后接在最后。

最后 $q$ 个询问，每次问你某个位置上的数是几。

# 解题思路

可以发现每次操作二至少使长度翻倍，所以有效的操作二个数至多只有 $\log_2 V$ 个。

那操作一呢？

当你把位置确定在两个操作二之间的操作一时，显然可以直接算出是哪个操作，从而得到答案。

那怎么确定呢？

既然操作二只有 $\log_2 V$ 个，我们可以暴力。

从最后一个操作二开始，设当前询问位置为 $pos$，上一个操作结束时数列长度为 $len$，因为后面的位置都是前面复制来的，所以映射到前面的位置即为 $(pos-1)\bmod len +1$。

而对于操作一，不可能一个个的判断，所以我们可以维护前一个操作二的位置，并直接跳过去。

同时，如果可以确定询问位置在这两个操作二之间，则可以直接算出答案。

时间复杂度 $O(q\log_2 V)$。

# 示例代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,q;
int op[N];
ll kr[N];
ll sz[N];
int mxr;
int pr[N];
int Q(int ed,ll pos){
    if(op[ed]==2){
        return Q(ed-1,(pos-1)%sz[ed-1]+1);
    }
    else{
    	if(sz[ed]==pos){
            return kr[ed];
    	}
        if(sz[pr[ed]]<pos){
    	    return kr[ed-sz[ed]+pos];
    	}
    	return Q(pr[ed],pos);
    }
}
void slove(){
    scanf("%d %d",&n,&q);
    mxr=0;
    bool edd=0;
    for(int i=1;i<=n;i++){
        scanf("%d %lld",&op[i],&kr[i]);
        if(edd)continue;
        if(op[i]==1){
            sz[i]=sz[i-1]+1;
            pr[i+1]=pr[i];
            if(sz[i]>1e18){
		        mxr=i;
		        edd=1;
	        }
        }
        else{
            sz[i]=sz[i-1]*ll(kr[i]+1);
            pr[i+1]=i;
            if((ll)(1e18)/(ll)(kr[i]+1)<sz[i-1]){
                mxr=i;
                edd=1;
            }
        }
        mxr=i;
    }
    ll pos;
    for(int cs=1;cs<=q;cs++){
        scanf("%lld",&pos);
        printf("%d ",Q(mxr,pos));
    }
    putchar('\n');
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--)slove();
    return 0;
}
```

---

## 作者：kimidonatsu (赞：2)

直接拿到题目容易想到暴力手段，但是 $1 \leq k_i \leq 10^{18}$ 的数据范围着实劝退，考虑优化。

因为题目中有一部分操作是 **复制**，不必直接 copy 而可以追溯复制的内容。

对于一些问题，我们可以试着追溯到第 $k$ 个数的添加位置。比如说：

$$
\underbrace{[l _ 1, l _ 2,...l _ {x}]} _ {\text{length } x} \underbrace{[l _ 1, l _ 2,...l _ {x}]} _ {\text{length } x} \underbrace{[l _ 1, l _ 2,...l _ {x}]} _ {\text{length } x} ... \underbrace{[l _ 1, \star {l _ 2},...l _ {x}]} _ {\text{length } x}
$$

若标 $\star$ 的 $l_2$ 即使第 $k$ 个元素，找到第 $k$ 个元素其实也就等同于找到第 $k \mod x$ 个元素（当然会有 $k \mod x = 0$ 的特例，这里放在下文讨论）。

首先作两个简单的定义：

- $lst_i$：在完成前 $i$ 此操作后的最后一个元素
  
- $f_i$：在完成前 $i$ 此操作后的元素数
  

现在考虑回答某个对于 $k$ 的查询，如果 $f_i = k$，那显然答案就是 $lst_i$

否则，我们就需要找出 $f_i \gt k$ 的第一个 $i$。不难发现这个 $i$ 其实就是一次复制操作，我们的答案肯定位于其中一个重复操作中。此时我们的列表如下：

$$
\underbrace{[l _ 1, l _ 2,...l _ {f _ {i-1}}]} _ {\text{length } f _ {i-1}} \underbrace{[l _ 1, l _ 2,...l _ {f_ {i-1}}]} _ {\text{length } f _ {i-1}} \underbrace{[l _ 1, l _ 2,...l _ {f _ {i-1}}]} _ {\text{length } f _ {i-1}} ... \underbrace{[l _ 1, \star {l _ 2},...l _ {f _ {i-1}}]} _ {\text{length } f _ {i-1}}
$$

让第 $k$ 个元素成为最后一次复制中加 $\star$ 的 $l_2$。如你所见，找到第 $k$ 个元素其实也就等同于去找到第 $(k \mod f_{i - 1})$ 个元素。因此进行 $k := k \mod f_{i - 1}$，然后重复下去。

回到之前提出的特例 $k \equiv 0 (\mod f_{i - 1})$，那么答案就是 $lst_{i - 1}$。

注意到进行 $\log{(\max k)}$ 次第二种操作后，元素数就会超过 $\max k$，所以我们只需要关心前 $\log(\max k)$ 次的第二种操作。由此，反向遍历 $\log{(\max k)}$ 次第二种操作即可并按照上述思路解决即可。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 2e18;

void solve() {
	int n, q;
	std::cin >> n >> q;

	std::vector<int> lst(n + 1);
	std::vector<i64> f(n + 1);
	std::vector<int> pos;

	for (int i = 1, flg = 1; i <= n; i++) {
		int a, v;
		std::cin >> a >> v;

		if (a == 1) {
			lst[i] = v;
			f[i] = f[i - 1] + 1;
		} else {
			lst[i] = lst[i - 1];
			f[i] = ((v + 1) > inf / f[i - 1]) ? (i64) 2e18 : f[i - 1] * (v + 1);

			if (flg) {
				pos.emplace_back(i);
			}
		}

		if (f[i] == inf)
			flg = false;
	}

	while (q--) {
		i64 k;
		std::cin >> k;

		for (int i = pos.size() - 1; ~i; i--) {
			int idx = pos[i];

			if (f[idx] > k && f[idx - 1] < k) {
				if (k % f[idx - 1] == 0) {
					k = f[idx - 1];
					break;
				}
				k %= f[idx - 1];
			}
		}

		std::cout << lst[std::lower_bound(f.begin() + 1, f.end(), k) - f.begin()] << " ";
		if (q == 0) {
			std::cout << "\n";
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

```

---

## 作者：yingjingxu_NaS2O3 (赞：1)

## 分析

这里提供一种不使用二分和搜索的做法。

核心算法：模拟。

### 读入和准备

不妨记数列 $S_1$ 为 $a_{1,1},a_{2,1},\dots,a_{n,1}$，

则可记数列 $S_2$ 为 $S_1,S_1,\dots,S_1,a_{1,2},a_{2,2},\dots,a_{n,2}$，

依此类推，则最终数列 $S_n$ 为 $S_{n-1},S_{n-1},\dots,S_{n-1},a_{1,n},a_{2,n},\dots,a_{n,n}$，

由此，我们不妨使用 `map` 记录下数列中的 $a_{i,j}$，将其所在位置与其对应，便于后续使用，同时，每执行一次操作 $2$，就将位置在 $pos$ 数组中记录。

同时我们注意到题目中给出的 $1\le k \le \min(10^{18},c)$，其中 $c$ 为最终序列长度，则当数在最终数列的位置超过了 $10^{18}$ 时，我们就停止维护。

#### 注意：

- 原题中的操作 $2$ 是将序列**复制** $x$ 份插入原序列末尾，所以记录位置时应当将位置乘上 $x+1$；
- 判断位置是否超过 $10^{18}$ 时可能会导致溢出，请使用 `__int128` 或除法判断。

由此可以得出以下代码：

```cpp
bool flag=0;
for(int i=1;i<=n;i++)
{
	int op,x;
	scanf("%lld",&op);
	scanf("%lld",&x);
	if(flag)
		continue;
	if(op==1)
	{
		_Mp[++pos[cnt]]=x;
		if(pos[cnt]>1e18)
			flag=1;
	}
	else
	{
		cnt++;
		pos[cnt]=pos[cnt-1]*(x+1);
		if((__int128)pos[cnt-1]*(x+1)>1e18)
		{
			flag=1;
			cnt--;
		}
	}
}
```

### 询问和回答

利用循环找到第一个不小于 $x$ 的 $pos_i$，判断其是否在 `map` 中，若在，直接输出；若不在，则

$$x \gets \begin{cases} pos_i & x \equiv 0\ (\bmod \ pos_i) \\ x\mod pos_i & x \not\equiv 0\ (\bmod \ pos_i) \end{cases}$$

重复以上过程直至结束。

由此可以得出如下代码：

```cpp
while(q--)
{
	int x,tmp=cnt;
	scanf("%lld",&x);
	while(1)
	{
		while(x<pos[tmp])
			tmp--;
		if(_Mp[x])
		{
			printf("%lld ",_Mp[x]);
			break;
		}
		else
			x=(x-1)%pos[tmp--]+1;
	}
}
```

#### 注意：

- 多组询问；
- 多测要清空。

## 最终代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q,cnt;
map<int,int> _Mp;
int pos[200005];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		memset(pos,0,sizeof pos);
		cnt=1;
		_Mp.clear();
		scanf("%lld%lld",&n,&q);
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			int op,x;
			scanf("%lld",&op);
			scanf("%lld",&x);
			if(flag)
				continue;
			if(op==1)
			{
				_Mp[++pos[cnt]]=x;
				if(pos[cnt]>1e18)
					flag=1;
			}
			else
			{
				cnt++;
				pos[cnt]=pos[cnt-1]*(x+1);
				if((__int128)pos[cnt-1]*(x+1)>1e18)
				{
					flag=1;
					cnt--;
				}
			}
		}
		while(q--)
		{
			int x,tmp=cnt;
			scanf("%lld",&x);
			while(1)
			{
				while(x<pos[tmp])
					tmp--;
				if(_Mp[x])
				{
					printf("%lld ",_Mp[x]);
					break;
				}
				else
					x=(x-1)%pos[tmp--]+1;
			}
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：ZLCT (赞：1)

# CF1920D Array Repetition
## 题目翻译
给定一个长度为 $0$ 的序列 $a$，下面要进行 $n$ 次操作。每次操作为向末尾加入一个 $x$ 或将序列复制 $x$ 份。操作完后需要求出第 $w$ 位是多少。
## 简单分析
首先大概估计一下，就可以算出如果真的要计算各位的数值，那么如果执行复制操作的次数很多，那总长度会约为 $2^n$，那这都需要高精度来存输入了。\
于是我们观察数据范围会发现 $w\le\min(len,10^{18})$（$len$ 为最后序列长度）。\
这就告诉我们了至少在 $10^{18}$ 以后的数对于我们来说是无用的。
## 进一步解析
但是这样的规模对于我们还是很难接受的，我们只能接受 $O(n)$ 的记录。\
我们发现如果全是加一个数的操作，那么我们完全可以接受全部储存下来，但是难点就在于如何处理复制操作。\
因为一次复制会把原来序列全部复制一遍，所以假设原序列长为 $l$，复制了 $k$ 份，那么显然对于 $i\in[1,l]$ 和 $i+lj(j\in[0,k-1])$ 位置的数一定是一样的。\
那么我们对于复制操作就可以 $O(1)$ 跳到复制前序列的对应位置。
## 深度剖析
那么现在我们的问题就变成了如何实现这个过程。\
我们考虑记录 $len_i,lst_i$ 分别表示操作完前 $i$ 次操作的序列长度和序列的最后一个元素。\
这个的计算方法十分简单：\
如果是加入 $x$ 操作则 $len_i=len_{i-1}+1,lst_i=x$。\
如果是复制 $x$ 次操作则 $len_i=len_{i-1}*(x+1),lst_i=lst_{i-1}$。\
对于询问，我们不断查找第一个小于等于 $w$ 的 $len_i$ ，如果 $len_i=w$ 则说明找到了，否则进行跳的操作，也就是令 $w=(w-1)\bmod len_i +1$。\
我们通过分类讨论来证明一下这种操作的可行性。\
假设我们找到的 $len_i$ 所对应的第 $i$ 次操作是复制，那么根据前面的解析一定是正确的。\
如果对应的操作是加入，那么如果 $len_i\ne w$，这是不可能的事情，因为我们的查找保证了 $len_i\ge w$ 且 $len_{i-1}<w$，所以这一步一定是复制操作。\
那这样的复杂度呢？
## 复杂度证明
由于每次我们的操作都是针对复制的，所以每次都会令 $w=(w-1)\bmod len_i +1$。这是一个很常见的复杂度证明，假设 $w\ge\frac{len_i}{2}$，则至少减少 $\frac{len_i}{2}$；如果 $w<\frac{len_i}{2}$，则结果一定 $<\frac{len_i}{2}$。所以每次至少 $\div2$，一共最多就需要进行 $q\log w$ 轮，每轮都有个二分查找，于是总复杂度 $O(q\log w\log n)$。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int len[112345],lst[112345],q,n;
int ans(int x){
	while(x){
		int st=upper_bound(len+1,len+1+n,x)-len-1;
		if(len[st]==x){
			return lst[st];
		}else{
			x=(x-1)%len[st]+1;
		}
	}
}
void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		int op,x;cin>>op>>x;
		if(op==1){
			lst[i]=x;
			len[i]=len[i-1]+1;
		}else{
			lst[i]=lst[i-1];
			if(x+1<2e18/len[i-1])len[i]=len[i-1]*(x+1);
			else len[i]=2e18;
		}
	}
	while(q--){
		int x;cin>>x;
		cout<<ans(x)<<' ';
	}cout<<'\n';
	return;
}
signed main(){
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Ag2WO4 (赞：1)

这题是循环节套娃，可以在每个复制操作前记录当前序列的长度，就是接下来有限的循环节的长度；每次加入操作更新循环节即可。查询时先按循环节长度确定是否在某循环节内，再看是不是刚好是加入的值，如果是就输出，如果不是就对内层循环节长度取模，如此继续。询问位置最多只有 $10^{18}$，而复制操作可能会非常多，记得剪枝。
```python
def r(x):
    x=int(x)
    if x in b:return b[x]
    for i in a:
        x=(x-1)%i+1
        if x in b:return b[x]
for _ in range(int(input())):
    a=[0];b={};c,d=map(int,input().split())
    for i in range(c):
        d,e=map(int,input().split())
        if a[-1]>10**19:continue
        if d&1:a[-1]+=1;b[a[-1]]=e
        else:a.append(a[-1]*(e+1))
    a=a[::-1];print(str(list(map(r,input().split())))[1:-1].replace(',',''))
```

---

## 作者：fcy20180201 (赞：1)

## 思路
最直接的思路肯定是记录每一次操作后的序列长度，因为一个位置有数之后就不会改变，所以询问时找到**最早操作后序列长度 $\ge$ 询问位置**的操作，然后倒推还原询问位置在之前的序列中的位置：

- 如果推到的位置是 $1$ 操作：如果**询问位置在这时的位置是最后一个**，即询问位置上的数在这时出现，那么直接输出；否则什么都不干。

- 如果推到的位置是 $2$ 操作，那此时的序列就是前一个序列多次出现构成的，所以询问位置在前一个序列的位置就是询问位置在当前序列的循环节里的位置，所以**取模**即可（如果下标以 $1$ 开头，注意细节）。

### 处理细节
首先要解决的是最终序列太长的问题，但发现询问的位置 $\le 10^{18}$，并且每步倒推只需要用到前一个序列的长度，因此**只要保存 $10^{18}$ 以内的序列长度**（关于怎么不用 `__int128` 判断序列长度是否在 $10^{18}$ 以内，请见代码）。

第二是怎样快速找到“最早操作后序列长度 $\ge$ 询问位置的操作”。注意到序列**长度递增**，因此在序列长度 $\le10^{18}$ 的操作里**二分**。

第三是怎样快速倒推。我们发现倒推操作 $1$ 时只有发现答案才有用，**其他的操作 $1$ 都没用**，并且做操作 $2$ 序列长度每次至少 $\times 2$，**所以至多有 $59$ 个**。因此我们对于每个操作都记录**前一个操作 $2$ 在哪里**，把这个操作倒推好后算一下这个操作和前一个操作 $2$ 之间有没有答案（见代码），如果有就输出，否则直接倒推前一个操作 $2$。

设 $V=10^{18}$，则时间复杂度 $\mathcal O(q(\log n+\log V))$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll inf=1e18;
int t,n,q,op[100005],lst[100005];
ll x,res[100005],num[100005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&q);
		int pos=0;//记录二分范围
		for(int i=1;i<=n;i++){
			scanf("%d%lld",&op[i],&num[i]);
			res[i]=0;//多测记得清空！！！
			if(op[i]==1 && !pos && res[i-1]<inf)res[i]=res[i-1]+1;//如果是 1 操作
			if(op[i]==2 && !pos && 1.0*inf/res[i-1]>=1.0*(num[i]+1))res[i]=res[i-1]*(num[i]+1);
			//如果是 2 操作（判断序列长度 ≤10^18 可以用把乘移项成除，用小数做）
			lst[i]=(op[i-1]==2?i-1:lst[i-1]);//记录前一个二操作
			if(!pos && !res[i])pos=i;
			//当序列长度 ≥10^18 时，res 是 0，就能确定二分范围
		}
		if(!pos)pos=n+1;//特判序列长度全 ≤10^18 的情况
		while(q--){
			scanf("%lld",&x);
			int i=lower_bound(res+1,res+pos,x)-res;//二分
			for(int j=i;;j=lst[j]){//倒推
				if(op[j]==2)x=(x-1)%res[j-1]+1;//倒推操作 2，模前一个序列的长度
				if(j-1-lst[j]>res[j-1]-x){printf("%lld ",num[j-1-(res[j-1]-x)]);break;}
				//计算两个操作 2 之间有没有答案
			}
		}
		puts("");//记得换行啊
	}
	return 0;
}

```

---

## 作者：Comentropy (赞：1)

赛时做完了，但是赛后发现被卡了，好在没有 FST。

## 操作
操作其实非常好想，由于每一次进行第二种操作都会直接复制前缀并粘贴到后面，所以可以维护一个序列，保存 **真实数组** 中对应的下标：

对于第一种操作：直接把对应下标加到序列末尾，并保存其元素。

对于第二种操作：由于是对前缀的复制，所以不需要再存一遍，我们保存这一段数组的右端点，假设 $n$ 为当前的下标，则 $n \leftarrow n(x+1)$，得到了右端点，即新的下标。

当前保存的就是序列中的前一个元素对应的数组的复制，所以处理询问时如下操作。

可以二分查找（右端点单调）到对应真实数组下标对应序列中的位置。

1. 若当前元素有值，输出即可；否则进行第二步。
2. 当前元素没有值，则说明是前面的复制：于是可以对前缀长度取模，得到在前缀中的下标，再二分查找对应序列的位置。跳转回第一步。

以此进行即可。

## 时间复杂度

时间复杂度，插入显然是 $O(1)$ 的，我们着重分析询问：

对应题目中 $n$ 的意义，此时进行一次二分查找是 $O(\log{n})$ 的，考虑至多进行查找的次数。

由于每次复制都至少使得长度翻倍，则若当前跳转到复制段（没有具体数值），就会往前跳，至少使得下标除以 $2$；否则会跳出循环。

所以，该算法的时间复杂度为：$O(n+q\log{n} \cdot \log{ \max{k} })$，其中 $k$ 为询问的下标。

## 一个优化

实际上，我们并不需要每次都二分，而是可以先逐个取模，最后二分。设，我们在序列中保存的真实右端下标为 $lst_i$。

对于每一次 **复制** 的操作，如果对于第 $i$ 次操作，给的下标 $k$，满足 $lst_{i-1}<k<lst_i$，那么如上，可以使得 $k 
\leftarrow k \mod lst_{i-1}$，直到 $k=0$ 或不被包含在复制的周期里。

这样进行操作，由于 $k$ 单调递减，并且由上面的时间复杂度分析可知，这样的操作至多进行 $\log{k}$ 次。

而且，如果我们保存了每一段的最后一个数，由上可以得到不被复制段包含的，或者处于复制段末尾的 $k$，可以此时再进行二分操作。

时间复杂度 $O(n+q(\log{k}+\log{n}))$，代码可见 [官方题解](https://codeforces.com/blog/entry/122560)。

## Code

这里给出不加优化的代码，请注意 ```int128``` 的使用细节，赛后被卡了，此处已经修复。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long LL;
typedef __int128_t lint;
// const lint INF=1000000000000000000;
vector<pair<lint,int> > b;
inline int get(LL k){
    int l=0,r=b.size()-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(b[mid].first<k)
            l=mid+1;
        else
            r=mid;
    }
    return r;
}
void solve(){
    b.clear();
    int n,q;
    scanf("%d%d",&n,&q);
    lint idx=0;
    while(n--){
        int opt,x;
        scanf("%d%d",&opt,&x);
        if(idx>=(lint)1e18) // pay attention to this line.
            continue ;
        if(opt==1){
            idx++;
            b.push_back({idx,x});
        }else{
            idx+=idx*x;
            b.push_back({idx,0});
        }
    }
    while(q--){
        LL k;scanf("%lld",&k);
        int r=get(k);
        // printf("find: %d\n",r);
        while(b[r].second==0){
            k%=(LL)b[r-1].first;
            if(k==0)    k=b[r-1].first;
            r=get(k);
        }
        printf("%d ",b[r].second);
    }
    printf("\n");
    return ;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给你一个空序列 $a_i$，你需要对其进行 $n$ 次操作，每次操作为以下两种之一：

如果输入 $1$，就向序列末尾加入一个正整数 $x$。

如果输入 $2$，将序列复制 $x$ 份插入原序列末尾，保证之前已经进行过 $1$（也就是上面的）操作。

以上所有操作结束后有 $q$ 个询问，每次给定一个正整数 $k$，表示询问最终序列第 $k$ 位的数。
## 分析
开一个结构体数组记录每次新加的数，上一次的数组长度和当前数组的长度，每次进行操作 $2$ 时候就记录下一个，如果数组长度大于 $10$ 的 $18$ 次方就不管了，不再进行任何操作，后面操作都无效。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
const ll MAXN=105;
ll Tex,n,q,opt,x;
vector<ll> Len;
struct node{
	vector<ll> in;
	ll len,tmp;
	node(){
		in.clear();
		len=0;
		tmp=0;
	}
	bool operator < (const node & p) const {return len<p.len;}
}a[MAXN];
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') f=-1,ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f*x;
}
inline void print(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
void dfs(ll x){
	ll idx=lower_bound(Len.begin(),Len.end(),x)-Len.begin();
	ll mod=a[idx].tmp+a[idx].in.size();
	ll real=x%mod==0 ? mod : x % mod;
	if(real<=a[idx].tmp) dfs(real);
	else print(a[idx].in[real-a[idx].tmp-1]),putchar(' ');
}
void fun(){
	n=read();q=read();
	Len.clear();
	for(int i=0;i<80;i++){
		a[i].in.clear();
		a[i].len=0;
		a[i].tmp=0;
	}
	Len.push_back(0);
	ll cnt=1,p=0;
	for(int i=1;i<=n;i++){
		opt=read();x=read();
		if(p) continue;
		if(opt==1) a[cnt].in.push_back(x);
		else{
			a[cnt].len=(a[cnt].tmp+a[cnt].in.size())*(x+1);
			Len.push_back(a[cnt].len);
			if(a[cnt].len>1e18) p=1;
			cnt++;
			a[cnt].tmp=a[cnt-1].len;
		}
	}
	a[cnt].len=a[cnt].tmp+a[cnt].in.size();
	Len.push_back(a[cnt].len);
	while(q--){
		x=read();
		dfs(x);
	}
	putchar('\n');
}
int main(){
	Tex=read();
	while(Tex--) fun();
	return 0;
} 
```

---

## 作者：Hellen68 (赞：0)

## 思路

### 存储
一共两种操作：要么在末尾加一个数 $x$，要么把整一段复制 $x$ 次。前一个简单，直接加上去就行了，但第二个……它复制上那么一顿，如果直接记录的话，第一爆空间，第二，查找的时候找都没法找（毕竟谁会一个个枚举呢）！

那么我们考虑第二种操作。

设原序列为 $\texttt {abcd}$，多复制 $5$ 份，那么序列变成：

$\texttt {abcd abcd abcd abcd abcd abcd}$

**注意：多复制 $x$ 份指在原序列末尾增加 $x$ 份，即序列长度变为原序列的 $x + 1$ 倍！**

现在，我们取第 $18$ 个数。第 $18$ 个数是第 $5$ 个区间的第 $2$ 个数。但整个数列是被 copy 过的，所以……发现什么了？

**第 $18$ 个数和第 $2$ 个数不是一个数吗！第 $k$ 个区间的第 $x$ 个数，跟第一个区间的第 $x$ 个数，不是一样吗！**

问题变简单了，序列长度大幅缩水。

但我们总要记录区间长度吧，总之你得找着这个数是谁，在哪。

所以，在每次操作的后面，我们都记录一下操作结束后序列长度，这样那么老长的序列就变为一个数字了。另外，为了优惠第一个操作，我们还要记录下每次操作完后序列的最后一个数是谁。

但是还有个问题。如果第二个操作做多了，序列长度还是会爆表，直接炸了 longlong。但好在题目的询问中只询问到 $10^{18}$，所以……后面的各种内容，我们……**直接扔了不要了**！（好粗暴哈哈哈）

------

### 查询
存是存完了，找呢？

嘿嘿，用二分，而且是直接二分。

如果我们要查的这个数在这个区间的范围内——换句话说，就是第 $k$ 次操作范围包含了第 $x$ 个数，我们就返回区间数。如果不符合范围，就朝两边查找。这是一个非常基本的二分查找。

当然了，要避坑。如果查的数是第 $k - 1$ 个区间的末尾，就会发生奇奇怪怪的死循环。另外，在存储的时候，如果复制操作后的区间有一半超过 $10^{18}$ 的线了，如果整个区间全部切掉，也会导致查找区间不在存储范围内而死循环。


## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 5;
const ll N = 1e18;
int t , n , q;
int lst[maxn] , b;
ll sum[maxn]; 
//sum[i]:第i次操作结束后，序列长度 
//lst[i]：第i次操作结束后，序列的最后一个数
//那么如果sum[i]>1e18，不再记录任何值（你查询区间都不到那你记它干嘛) 
int cnt; //记录2操作的数量 
ll ffind(ll pos , ll l , ll r) {
	ll mid = (l + r) >> 1;
	if(pos > sum[mid - 1] && pos <= sum[mid]) return mid;
	else if(pos == sum[mid - 1]) return mid - 1;
	else if(pos > sum[mid]) ffind(pos , mid + 1 , r);
	else ffind(pos , l , mid);
}
int main() {
//	freopen("CF1920D.in" , "r" , stdin);
//	freopen("CF1920D.out" , "w" , stdout);
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --) {
		b = 0;
		cin >> n >> q;
		int flag = 1;
		//cout << "I'm alive!" << endl;
		for(int i = 1 ; i <= n ; ++ i) {
			int opt , x;
			cin >> opt >> x;
			if(flag && opt == 1 && sum[i - 1] + 1 <= N) {
				++ b;
				sum[i] = sum[i - 1] + 1;
				lst[i] = x;
			}
			else if(flag && sum[i - 1] <= N / (x + 1)) {
				++ b;
				sum[i] = sum[i - 1] * (x + 1);
				lst[i] = lst[i - 1];
			}
			else if(flag && sum[i - 1] < N) {
				++ b;
				sum[i] = N;
				lst[i] = -1;
			}
			else flag = 0;
		}
//		cout << "!" << b << endl;
//		cout << endl << endl << endl;
//		for(int i = 1 ; i <= b ; ++ i) {
//			cout << sum[i] << " " << lst[i] << endl;
//		}
//		cout << endl << endl << endl;
		for(int i = 1 ; i <= q ; ++ i) {
			ll k;
			cin >> k;
			ll cnt = ffind(k , 1 , b);
			while(k != sum[cnt] || lst[cnt] == -1) {
				k %= sum[cnt - 1];
				if(k == 0) k = sum[cnt - 1];
				cnt = ffind(k , 1 , cnt - 1);
			}
			cout << lst[cnt] << " ";
			
		}
		cout << endl;
	}
	return 0;
}

```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1920D)

&nbsp;

### 题目大意：
给定一个空序列 $a$，对其进行 $n$ 次操作，操作类型有以下两种：
- 在序列末端添加一个数 $x$。
- 将序列复制 $x$ 遍，添加到序列末尾。

之后询问 $q$ 次，求出序列中下标为 $q_i$ 的元素。 

&nbsp;

### 解题思路：
发现操作一只能在序列末端添加数，于是序列显然可以被分为两部分考虑，前面一半为复制得来，后一半为直接添加。

考虑如何确定二操作和一操作部分的分界线，发现可以对于每次复制操作都记录操作后的序列长度，然后将每个添加操作依次与前一个复制操作对应。存储方法很多，这里采用 `vector`。

对于在添加操作部分的直接对应下标求值，在复制操作的部分则对于复制前的序列长度取模，重复上述操作即可。

代码如下：
```
=int main(){
	scanf("%d",&t);
	
	while(t--){
		scanf("%d%d",&n,&m);
		vec[0].clear();
		
		int cnt=0;
		ll len=0ll;
		a[0][2]=0;//将空序列记为一次复制操作，使得后续添加操作有对应的赋值操作
		for(int i=1;i<=n;i++){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			if(len==mx) continue;
			
			if(x==1){
				len++;
				vec[cnt].push_back(y);
			}
			else{
				cnt++;
				vec[cnt].clear();
				a[cnt][0]=len;
				if((y+1ll)>mx/len) len=mx;//最长不超过1e18
				else len=len*(y+1ll);
				a[cnt][1]=y;
				a[cnt][2]=len;
			}
		}
		
		for(int i=1;i<=m;i++) ans[i]=0,scanf("%lld",&q[i]);
		
		for(int i=cnt;i>=0;i--){
			for(int j=1;j<=m;j++){
				if(q[j]>a[i][2]&&(!ans[j])){//考虑添加操作部分
					ans[j]=vec[i][q[j]-a[i][2]-1ll];
				}
				if(!i) continue;
				q[j]=q[j]%a[i][0];	//将下标对应到复制操作前的序列中
				if(!q[j]) q[j]=a[i][0];
			}
		}
		
		for(int i=1;i<=m;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```
完结撒花 OvO！！！

---

## 作者：1234567890sjx (赞：0)

设 $f_i$ 表示前 $i$ 个操作形成的序列的长度。

然后对于每一次询问，在整个序列操作中二分查找出第 $k$ 个元素是在哪一次操作中第一次出现在序列中的。特殊的，如果二分查找发现第 $k$ 个元素所在的操作是一次 `2` 操作即复制操作，那么就在这个操作之前的地方再次二分出这个元素是 `2` 操作的第几次循环的第几个元素中出现的…… 以此类推。

因为 $2^{30}=1,073,741,824>10^9$，所以有效的 `2` 操作嵌套最多只会有 $\log 10^9\approx 30$ 次，所以放心暴力即可。

特殊的，注意可能会爆 `long long` 的地方，用 `__int128` 存储即可。

[Code](https://www.luogu.com.cn/paste/v7we8aeq)

---

## 作者：huangrenheluogu (赞：0)

发现 $2$ 操作会让长度至少变成原来的 $2$ 倍，说明有用的 $2$ 操作不会很多。

那么直接暴力看着处在哪一个循环里，如果在前面的循环里，就去上一层；否则，在新加的数中就可以输出答案。

开始让答案爆了 `__int128` 喜提一发罚时警示后人。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N = 1e5 + 5, inf = 1e18;
int n, q, ans[N], dep, T, op, x, maxn, d;
struct node{
	int R, len;
	vector<int>num;
	inline void clear(){
		R = len = 0;
		num.clear();
	}
}a[N];
inline void init(){
	for(int i = 1; i <= dep; i++){
		a[i].clear();
	}
	dep = maxn = 1;
}
inline int solve(int x){
	d = maxn;
	while(1){
		if(x > a[d].R) return a[d].num[x - 1 - a[d].R];
		d--;
		x %= a[d].len;
		if(!x) x += a[d].len;
	}
}
inline void read(int &x){
	x = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while('0' <= c && c <= '9'){
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
}
signed main(){
	read(T);
	while(T--){
		init();
		read(n), read(q);
		while(n--){
			read(op), read(x);
			if(a[dep].len > inf) continue ;
			if(op == 1){
				a[dep].len++;
				a[dep].num.push_back(x);
			}
			else{
				x++;
				dep++;
				a[dep].R = a[dep - 1].len * x;
				a[dep].len = a[dep].R;
				if(a[dep].R <= inf) maxn = dep + 1;
			}
		}
		if(maxn > dep) maxn--;
		for(int i = 1; i <= q; i++){
			read(x);
			ans[i] = solve(x);
		}
		for(int i = 1; i <= q; i++) printf("%lld ", (long long)ans[i]);
		puts("");
	}
	return 0;
}
/*
1
12 5
1 6
1 11
2 392130334
1 4
2 744811750
1 10
1 5
2 209373780
2 178928984
1 3
2 658326464
2 1000000000
914576963034536490 640707385283752918 636773368365261971 584126563607944922 1000000000000000000
*/
```

---

## 作者：hanjinghao (赞：0)

## 题意

多组询问。对于每组询问，给定两个正整数 $ n, q $。你有一个初始为空的序列，接下来 $ n $ 次操作，每次会给定 $ (1, x) $，表示在序列末尾添加 $ x $；或者给定 $ (2, x) $，表示把整个序列复制 $ x $ 次。$ q $ 次询问，每次给定一个正整数 $ k $，你需要回答序列的第 $ k $ 个数是什么。

保证 $ 1 \le n, q \le 10 ^ 5 $，$ 1 \le x \le 10 ^ 9 $，$ 1 \le k \le 10 ^ {18} $，所有询问中的 $ n $ 的总和不超过 $ 10 ^ 5 $，$ q $ 的总和不超过 $ 10 ^ 5 $。

## 思路

首先对于 $ 1 \le i \le n $，求出第 $ i $ 次操作后序列的长度（对 $ 2 \times 10^{18} $ 取 $ \min $），设其为 $ f_i $。询问的时候，通过二分求出分界点 $ p $，满足第 $ p $ 次操作后序列长度小于 $ k $ 且第 $ p + 1 $ 次操作后序列长度大于等于 $ k $。如果第 $ p + 1 $ 次操作是操作一，那么说明这个数恰好是第 $ k $ 个数，直接输出答案；否则，将 $ x $ 对 $ f_p $ 取模（如果为 $ 0 $，则令 $ x $ 等于 $ f_p $），然后回到上一步，一层一层推下去，直到得出答案。

由于每两层，$ x $ 至少减半，层数只会有 $ O(\log x) $。又因为每层需要二分一次，所以总时间复杂度为 $ O(q \log x \log n) $。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template < typename T >
inline void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline void writesp(T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline void writeln(T x)
{
	write(x);
	putchar(10);
}

const int N = 1e5 + 5;
const ll INF = 2e18;
int a[N], typ[N], c[N], cur[N];
ll f[N];

inline void Mul(ll &x, ll y)
{
	ll tmp = (INF + x - 1) / x;
	if (y >= tmp) x = INF;
	else x *= y;
}

int main()
{
	int T;
	read(T);
	while (T--)
	{
		int n, q, len = 0;
		read(n);
		read(q);
		for (int i = 1; i <= n; ++i)
		{
			read(typ[i]);
			read(c[i]);
			if (typ[i] == 1)
			{
				a[++len] = c[i];
				f[i] = f[i - 1] + 1;
				if (f[i] > INF) f[i] = INF;
			}
			else
			{
				f[i] = f[i - 1];
				++c[i];
				Mul(f[i], c[i]);
			}
			cur[i] = len;
		}
		while (q--)
		{
			ll x;
			read(x);
			while (1)
			{
				int num = 0, lft = 1, rgh = n;
				while (lft <= rgh)
				{
					int md = (lft + rgh) >> 1;
					if (f[md] < x)
					{
						num = md;
						lft = md + 1;
					}
					else rgh = md - 1;
				}
				if (typ[num + 1] == 1)
				{
					writesp(c[num + 1]);
					break;
				}
				ll dv = x / f[num], rst = x - dv * f[num];
				if (!rst) rst = f[num];
				x = rst;
			}
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

## 思路
这道题可以进行两个操作：

- 在序列的末尾想添加一个数 $x$。
- 把此序列看成 $s$，将 $s$ 的后面添加 $x$ 个 $s$。

我们要思考的问题是到底要进行那个操作，我们可以暴力解决。

操作一：

- 不可能一个个判断，因为复杂度会超，我们可以先想想操作二。

操作二：

- 显然复杂度只有 $\log_2$ $V$ 个，在此可以使用暴力。

回看操作一：

- 看前一个操作二的位置，答案就显而易见了。

复杂度：$O(q$ $\log_2$ $V)$

---

