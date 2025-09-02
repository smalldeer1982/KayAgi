# StickSuger

## 题目背景

YSGHYYDS

## 题目描述

YSGH 给你一个长度为 $n$ 的字符串 $S$。设 $S_x$ 表示字符串 $S$ 的第 $x$ 个字符。你可以选择一个二元组 $(i,j)$，然后交换 $S_i$ 和 $S_j$。二元组 $(i,j)$ 是合法的当且仅当 $1\leq i<j\leq n$ 并且交换后的字符串的字典序比原串大。

对于两个字符 $c_0,c_1$，称 $c_0>c_1$ 当且仅当 $c_0$ 的 ASCII 码大于 $c_1$ 的 ASCII 码。

对于两个长度为 $n$ 的字符串 $S,T$，$S$ 的字典序大于 $T$ 当且仅当存在一个 $i\in [0,n-1]$ 使得 $\forall j\in[1,i],S_j=T_j$， 并且 $S_{i+1}>T_{i+1}$。

如果存在多种合法方案，输出最大的二元组。

对于两个二元组 $(i_1,j_1)$，$(i_2,j_2)$，称  $(i_1,j_1)$ 小于 $(i_2,j_2)$ 当且仅当 $i_1<i_2\lor(i_1=i_2\land j_1<j_2)$。

如果不存在合法方案，则输出 `-1`。 

保证 $S$ 只包含小写英文字母。

## 说明/提示

**【样例解释 #1】**

如果选择二元组 $(2,3)$，交换 $S_2$ 和 $S_3$ 后的字符串为 `abc`，字典序比 `acb` 小，所以不合法。

如果选择二元组 $(1,3)$，交换 $S_1$ 和 $S_3$ 后的字符串为 `bca`，字典序比 `acb` 大，是合法的。

虽然 $(1,2)$ 也是合法的，但是没有 $(1,3)$ 大。所以答案是 $(1,3)$。 

**【样例解释 #2】**

容易看出任何一个二元组都不合法。

---

**【数据范围】**

**本题采用捆绑测试。**

对于 $100\%$ 的数据，$1\leq n\leq 10^6$，$S$ 只包含小写英文字母。

- Subtask 1（4 points）：$S$ 只包含一种字符。
- Subtask 2（10 points）：$n\leq 100$。
- Subtask 3（16 points）：$n\leq 500$。
- Subtask 4（25 points）：$n\leq 5000$。
- Subtask 5（18 points）：$n\leq 10^5$。
- Subtask 6（27 points）：$n\leq 10^6$。


## 样例 #1

### 输入

```
3
acb```

### 输出

```
1 3```

## 样例 #2

### 输入

```
6
zyxwvu```

### 输出

```
-1```

## 样例 #3

### 输入

```
14
aabbccddccbbaa```

### 输出

```
6 8```

# 题解

## 作者：HanPi (赞：10)

[P7478 【A】StickSuger](https://www.luogu.com.cn/problem/P7478)

### 题目大意:

给一个字符数组 $S$ ,长度为 $n$ .求一对最大的 $(i,j)$ 使得 $i<j$ 并且 $S[i]<S[j]$ . (比较时: $i$ 更大的大, $i$ 相同则 $j$ 更大的大)

**暴力解**

骗分是作为一个oier来说的基本功,既然想不到正解,暴力骗分也是不错的...?

从大到小枚举 $i$ ,再从大到小寻找满足条件的 $j$ ,一旦找到就停止.由于枚举的顺序,可以证明此时为最大的那一对.

```c
for(i=n-1;i>=1;--i)
{
    if(maxi||maxj)break;
    for(j=n;j>=i+1;--j)
    {
        if(S[j]>S[i])
        {
            maxi=i;
            maxj=j;
            break;
        }
    }
}
```
~~上述代码可以拿到51分的好成绩.~~

**优化暴力解**

看到题目中:
>Subtask 1（4 points）：$S$ 只包含一种字符。

考虑该情况: $S=\{b,b,b,b,b,...,b\}$ .

按照原暴力思路,枚举 $i$ 会在后面的无解情况中浪费很多时间.于是发现:

如果当某一个 $i$ 枚举完 $j$ 后找不到解,容易证明此时对于 $i$ 前面的连续的满足 $S_i=S_x$的 $x$ 也一定不会有解,因此可以跳过.

```c
#include <stdio.h>
char S[1000007];
int n;
int main()
{
    scanf("%d%s",&n,&S[1]);
    int i,j,maxi=0,maxj=0;
    for(i=n-1;i>=1;--i)
    {
        if(maxi||maxj)break;
        for(j=i+1;j<=n;++j)
        {
            if(S[j]>S[i])
            {
                maxi=i;
                maxj=j;
            }
        }
        while(S[i-1]==S[i]&&i>=1)i--;
    }
    if(maxi+maxj==0)puts("-1");
    else printf("%d %d",maxi,maxj);
    return 0;
}
```

该优化可以以 55ms 通过该题.

**类似的思路**

我们从大到小枚举 $j$ ,每次再从大到小寻找第一个合适的 $i$ ,如果比当前最优解更优则更新.如果枚举的 $i$ 已经小于最优解则不再枚举.

考虑该情况: $S=\{a,b,b,b,...,b\}$ , 因为后面几个相同, 容易证明 $j$ 取最后一个一定会比取前几个更优,因此当枚举完一个 $j$ 后可以直接跳过相同的.


```
#include <stdio.h>
int n;
char S[1000007];
int main()
{
    scanf("%d%s",&n,&S[1]);
    int i,j,a,b,maxi=0,maxj=0;
    for(j=n;j>=1;--j)
    {
        a=0,b=0;
        for(i=j-1;i>=1;--i)
        {
            if(S[i]<S[j])
            {
                a=i;
                b=j;
                break;
            }
            if(i<=maxi)break;
        }
        if(a>maxi)
        {
            maxi=a;
            maxj=b;
        }
        else if(a==maxi&&b>maxj)
        {
            maxi=a;
            maxj=b;
        }
        while(S[j-1]==S[j]&&j>=1)
        {
            j--;
        }
    }
    if(maxi+maxj==0)puts("-1");
    else printf("%d %d",maxi,maxj);
    return 0;
}
```

---

## 作者：Laser_Crystal (赞：4)

提供一种不同的思路。

如果我们**把这个字符串投射到坐标轴上**，会是怎么样的一个效果呢？

样例一：
![](https://cdn.luogu.com.cn/upload/image_hosting/pbmmfe01.png)

样例二：
![](https://cdn.luogu.com.cn/upload/image_hosting/n41gcqha.png)

样例三：
![](https://cdn.luogu.com.cn/upload/image_hosting/4matcy8h.png)

~~丑死了~~

题目要找的最大二元组，其实就是要找到一个$(i,j)$，使得$S_i<S_j$,并且$i$和$j$要尽量的大。

我们观察一下这个样例二，可以分析出来这种在坐标轴上单调递减的序列是不满足题目条件的。（其实仔细想一想就能出来，画图只是更直白一点）所以我们可以推导出来，**只要有一段单调递减的序列，那么这段序列上就不存在满足要求的二元组。**

由于题目要求这个$i$和$j$尽可能的大，那么我们应该可以想到这个的思路，就是**从后往前找一个顺次单调递减的序列，在这个序列结束后的第一个字符所处位置就是最大的$i$。**（样例一和三都满足情况）

这应该不难理解吧，因为i要尽可能的大，但是这个单调递减的序列上有没有满足的情况，所以我们只要在这个序列结束后（**就是图像第一次出现下降的时候**），记录这个位置，然后再后面这个单调的序列里面找最后一个比它大的就好了。由于序列是单调的，我们可以二分。

大概就是这么一张图：
![](https://cdn.luogu.com.cn/upload/image_hosting/k7ue8afr.png)
Code(25ms)
```cpp
#include<bits/stdc++.h> 
using namespace std;
char s[1000005];
int f[1000005],w=0;
int n;
inline int read()
{
   	int s=0,w=1;
   	char ch=getchar();
   	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   	return s*w;
}
int main()
{
   	n=read();
  	scanf("%s",s);
  	int k=n-1;
	while(s[k]>=s[k+1]&&k>=0) f[w++]=s[k],k--;//倒序查找
	if(k==-1)//如果一下子找到头了，就说明这一整个输入进来的都是单调递减的
	{
		cout<<"-1";
		return 0;
	}
	if(s[k]<f[0])//如果这个转折点比最后的那个点还小的话
	{
		cout<<k+1<<' '<<n;
		return 0;
	}
	int l,r,mid;
	l=0,r=w;
	while(l<r)//二分
	{
		mid=(l+r)/2;
		if(f[mid]<=s[k]) l=mid+1;
		else r=mid;
	}
	cout<<k+1<<' '<<n-r;
	return 0;
}
```
~~（好久不写代码感觉码风丑了）~~

qaq喵~

---

## 作者：TZMydl (赞：4)

考虑贪心，倒序遍历字符串。

对于当前某一个字符，我们只关心它后面字典序比它大的字符哪一个位置最靠后，而这是很好维护的。

只需要在遍历的时候存一下该字符第一次出现的位置即可，该位置一定是最大的。

对遍历到的字符查询一下字典序比它大的字符下标最大值即可，时间复杂度 $ O(26n) $ 。

由于只会无解的时候会跑满，其他情况搜到直接结束程序并输出即可，故我们可以轻松通过这道题。

code:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,cnt[31];
char s[1000005];
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=n;i>=1;--i){
		int res=0;
		for(int j=s[i]-'a'+1;j<=26;++j)
			if(cnt[j])
				res=max(res,cnt[j]);
		if(res){
			printf("%d %d\n",i,res);
			return 0;
		}
		if(!cnt[s[i]-'a'])cnt[s[i]-'a']=i;
	}
	puts("-1");
	return 0;
}
```



---

## 作者：Maxmilite (赞：2)

贡献本题第一发 Python 题解。

截至发表之时是第一份有形象图片解释的题解。

可能是一种比较快的解法。

![](https://z3.ax1x.com/2021/04/10/cavxzD.png)
( Python 区的第一份 AC 代码 )

### 简化版题意描述

给您一个字符串 $s$，要求您给出最大的一个数对 $(i, j)$，使得交换中字符 $s[i], s[j]$ 之后的字符串比源字符串的字典序要大。如果没有符合要求的数对，输出 $-1$

补充：
> **简化版字典序概念**：对于两个相等长度的字符串 $s, t$，从头开始找，直到找到一个两字符串中字符不同的位置。如果 $s$ 这个位置的字符比 $t$ 的 ASCII 码要大，那么我们就说 $s$ 的字典序大于 $t$。
> 
> **关于 $(i, j)$ 数对的大小比较**：设两个数对 $(i_1, j_1)$, $(i_2, j_2)$，如果 $i_1 > i_2$，那么第一个数对比第二个数对大，如果二者的 $i$ 相同，那么就按照相同方式比较 $j$。

### 思路

先说一下我们的思路：**从后往前找，直到找到一个极大点，然后在 “这个位置的前一个位置” 后面找到一个位置最大的比 “这个位置的前一个位置” 上的字符要大的字符，二者所在的位置构成的数对就是答案。**

> **关于极大点的定义**：对于一个位置 $i$ 使得 $s[i] > s[i - 1]$ 并且 $s[i] > s[i + 1]$

为什么要这么做？

我们不妨采用画图~~数形结合~~的技巧。

我们将随便一个字符串上的位置和该位置的 ASCII 码作为坐标点，连成一个平滑曲线。

![](https://z3.ax1x.com/2021/04/10/cd9t41.png)

箭头标的位置就是最后一个极大点。

我们为什么要找到这个极大点？

答案其实很简单，从图像中可以看出，**这个极大点以后的字符一定保证越来越小**。

如果我们交换了他后面的两个字符，那么**字符串字典序势必会变小**。

所以我们找到这个极大点，以他左边的一个点作为 $i$。

这样无论如何，**$i$ 后面至少有一个一个字符要比 $s[i]$ 大**，而这个位置就是那个极大点。

我们确定了 $i$ 以后，就开始从后往前找 $j$，直到找到一个 $j$ 点的字符比 $i$ 点的大。

然后输出答案，一气呵成。

这就是 **“从后往前找，直到找到一个极大点，然后在 “这个位置的前一个位置” 后面找到一个位置最大的比 “这个位置的前一个位置” 上的字符要大的字符，二者所在的位置构成的数对就是答案。”** 的意义。

那么我们如何实现呢？

知道了原理以后实现就很简单了。我先把局部代码贴上来。

```python
# 定义字符串为 s, cur 为极大点位置，初始值为 -1

for i in range(n - 1, 0, -1):
        if s[i] > s[i - 1]:
            cur = i - 1; break
```

很清晰，找到极大点并赋给 `cur`。

```python
# -1 就是没找到，是 cur 的初始值

if cur == -1:
        print("-1")
    else:
        for i in range(n - 1, cur, -1):
            if s[i] > s[cur]:
                print("%d %d" % (cur + 1, i + 1)); break
```

找到极大点前面一个点，然后从后往前找 $j$

至于为什么要输出 `(cur + 1, i + 1)`，自然是因为 Python 的字符串是以 $0$ 下标开始的。

### 代码 (Python)

```python
# !usr/bin/python3.7


def main():
    n = int(input())
    s = input()
    cur = -1
    for i in range(n - 1, 0, -1):
        if s[i] > s[i - 1]:
            cur = i - 1; break
    if cur == -1:
        print("-1")
    else:
        for i in range(n - 1, cur, -1):
            if s[i] > s[cur]:
                print("%d %d" % (cur + 1, i + 1)); break
    return


if __name__ == "__main__":
    main()
```

---

其实赛时我写了一份 C 语言代码，但是没有什么特别之处，就在此处文章末尾贴出了。

赛时跑了 22ms，还是挺快的。

吸氧以后刷进最优解前六，应该还是比较不错的。

![](https://z3.ax1x.com/2021/04/10/cdCgZ4.png)

代码 (C 语言)

```c
#include <stdio.h>

int n, cur;
char a[1000005];

int main()
{
    scanf("%d", &n);
	scanf("%s", a + 1);
    for (int i = n; i >= 2; --i)
		if (a[i] > a[i - 1])
		{
			cur = i - 1;
			break;
		}
	if (cur == 0)
		printf("-1\n");
	else
		for (int i = n; i >= cur + 1; --i)
			if (a[i] > a[cur])
			{
				printf("%d %d\n", cur, i);
				break;
			}
    return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
给定一个长度为 $n$ 的仅包含小写字母的字符串 $s$，请找到一个二元组 $(i,j)$（$i<j$）使得在交换字符串 $s$ 的第 $i$ 个和第 $j$ 个字符后会使新的字符串比原字符串的字典序大。若有多个满足要求的 $(i,j)$，输出 $i$ 最大的那一个，如果仍有多个方案，输出 $j$ 最大的那一个。

**数据范围：$1\leqslant n\leqslant 10^6$。**
## Solution
先从后往前扫，扫到第一个 $i\in[1,n)$ 使得 $s_i<s_{i+1}$（此处为 ASCII 码比较），记录下这个位置 $p$ 。然后判断是否存在这个位置，如果不存在输出 `-1`。

否则，再从 $n$ 开始往后扫到 $p+1$，扫到第一个 $i\in[p+1,n]$ 使得 $s_i>s_p$（同上）。此时 $(i,p)$ 即为满足要求的二元组，也就是答案，直接输出即可。
## Code
```cpp
char s[1000007];

int main() {
	int n = Rint, fl = -1; scanf("%s", s + 1);
	R(int, i, n - 1, 1) if(s[i] < s[i + 1]) {fl = i; break;}
	if(fl == -1) return printf("-1"), 0;
	print_space(fl);
	R(int, i, n, fl + 1) if(s[i] > s[fl]) return write(i), 0;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

## 题目简述

求 $a_i$ 的 ASCII 码小于 $a_j$ 的 ASCII 码 的最大 ( $i$ , $j$ )。

## 题目分析

用 $last_i$ 来记录 第 $i$ 个字母最后出现的位置，对于每一次输入枚举存不存在合理的解并更新。

## _Code_

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring> 
using namespace std;
#define ll long long
const int MAXN=30;
int n;
char a;
int p=0,q=0;
int last[MAXN];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		last[a-'a']=i;
		for(int j=a-'a'-1;j>=0;j--)
			if(last[j]&&(last[j]>p||last[j]==p&&q<i))
					p=last[j],q=i;
	}
	if(!p) cout<<"-1";
	else cout<<p<<" "<<q;
}
```


---

## 作者：feicheng (赞：2)

## $\text{Preface}$

一个和各位大佬不太一样的大常数做法。

[可能更好的体验](https://www.cnblogs.com/hl-fc/p/14639369.html)。

## $\text{Description}$

给定一长度为 $n$ 的字符串 $s$，求最大的二元组 $(i,j)$ 满足 $s_i < s_j$

定义二元组 $(x_1,y_1) < (x_2,y_2)$ 的概念为：

$$x_1 < x_2 \lor (x_1 = x_2,y_1 < y_2)$$

**限制**

$1\le n \le 10^6$

## $\text{Solution}$ 

这个思想非常的暴力：对于每一个字符 $ch$，我们在 $ch$ 的前面寻找第一个比其小的字符，统计答案即可。

如何比较快速的寻找一个字符前比其小的第一个字符？

我们可以记录一个 $A$ 数组，其中 $A_i$ 表示字符 `i+'a'` 最后一次出现的位置，每次枚举 $A$ 数组即可。

时间复杂度：$\Theta (n)$ （有一个 $26$ 的常数）

## $\text{Code}$ 

```cpp
constexpr int N = 1e6 + 10 ;

char s[N] ;
int n,flag;
int A[26] ; 

inline int Getpos(const int x) {
    int ans = -1;
    for(int i = 0;i < x;++i) ans = max(ans,A[i]) ;
    return ans ;  
}//寻找第一个位置

int main(int argc,const char **argv) {
    memset(A,-1,sizeof A) ;
    cin >> n >> (s+1) ;
    std::pair<int,int> ans ;
    for(int i = 1;i <= n;++i) {
        A[s[i]-'a'] = i ; 
        const int p = Getpos(s[i]-'a') ;
        if(p != -1) flag = 1,ans = std::max(ans,std::make_pair(p,i)) ; 
//我们发现对于二元组小于号的定义恰好满足 pair 的定义，就可以用pair来存储答案。
    }
    if(!flag) cout << -1 ;
    else cout << ans.first << " " << ans.second ; 
    return hl::flush(),0;
}
``` 

---

## 作者：Citnaris (赞：2)

# P7478 StickSuger

**题意**

给定一个序列 $x_1,x_2......x_n$ 求字典序最大的 $(i,j)$ 满足 $i<j,x_i<x_j$ ，其中 $x_1,x_2......x_n$ 均为小写字母。

$\texttt{Algorithm 1}$

直接倒序循环暴力枚举数对 $(i,j)$ ，找到一组满足条件的便终止，理论复杂度 $\mathcal{O}(n^2)$，得分 $55$ 。

$\texttt{Algorithm 2}$

注意到每个字符均为 $\texttt{'a'}$ 到 $\texttt{'z'}$ 之一，我们只需倒序枚举，找出第一个满足 $x_j=\texttt{char in range 'a' to 'z'}$，再从 $j$ 开始倒序枚举，找出第一个 $x_i<x_j$ 后更新答案即可。这样我们可以避免枚举不存在的可能性，比如 $x_i=\texttt{'A'},x_j=\texttt{'B'}$ 是不存在的，但在  $\texttt{Algorithm 1}$ 中枚举到了。理论复杂度 $\mathcal{O}(n)$ ，得分 $100$ 。

**Code**

```cpp
#include<cstdio>
#include<cstring>

using namespace std;

const int NR=1e6+5;
char a[NR];
int n,x,y;

inline void MAX(int tx,int ty)
{
    if((tx>x)||(tx==x&&ty>y)) x=tx,y=ty;
    return;
}

inline bool TRY()
{
    bool judge=0;
    for(int i=1;i<n;i++)
        if(a[i]>a[i-1])
        {
            judge=1;
            break;
        }
    if(!judge)
    {
        printf("-1\n");
        return false;
    }
    return true;
}

int main()
{
    scanf("%d",&n);
    scanf("%s",a);
    if(!TRY()) return 0;
    for(int i='a';i<='z';i++)
    {
        for(int j=n-1;j>=0;j--)
            if(a[j]==i)
            {
                for(int k=j-1;k>=0;k--)
                    if(a[k]<i)
                    {
                        MAX(k,j);
                        break;
                    }
                break;                    
            }
    }
    printf("%d %d\n",x+1,y+1);
    return 0;
}
```

---

## 作者：Max_s_xaM (赞：1)

# P7478 【A】StickSuger

要求出最大的合法二元组。

对于两个二元组 $(i_1,j_1)$，$(i_2,j_2)$，当 $i_1>i_2$ 时，$(i_1,j_1)$ 必定大于 $(i_2,j_2)$。所以解题策略为，贪心地求出最大的 $i$，再求出最大的 $j$。

从后向前遍历字符串 $S$，直到找到第一个 $i$，使得 $S_i<S_{i+1}$。这样，$(i,i+1)$ 必定为合法二元组且 $i$ 在所有合法二元组中最大。再从后向前找到第一个 $j$，使得 $i<j$ 且 $S_i<S_j$。$(i,j)$ 即为最大的合法二元组。

## Code
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	int n, p = -1;
	cin >> n;
	string s;
	cin >> s;
	for (int i = n - 2; i >= 0; i--) // 找到最大的 i 
	if (s[i] < s[i + 1])
	{
		p = i;
		break;
	}
	if (p < 0) cout << p << endl; // 无解 
	else
	{
		for (int i = n - 1; i >= p; i--) // 找到最大的 j 
		if (s[i] > s[p])
		{
			cout << p + 1 << " " << i + 1 << endl;
			break;
		}
	}
	return 0;
}


```


---

## 作者：_lfxxx_ (赞：1)

## 题意：
给定一串长度为 $n$ 的字符串 $S$ ，求满足 $S_i<S_j$ 且 $i<j$ 的 $i$ 和 $j$ 。如有多组满足的 $i$ 和 $j$ ，输出 $i$ 大的，如果 $i$ 相同，则输出 $j$ 大的。
## 思路：
从右边开始找 $i$ ，用 $h$ 记录右边最大的数的位置。

如果 $S_i<S_h$ ，从字符串最后一位往左找，一直找到 $h$ 。如果中间有比 $S_i$ 大的，输出 $i$ 和它的位置。然后结束程序。

最后如果没有结束程序就说明没有符合的，输出 $-1$ 。

## 注意事项：
字符串读入时会下标会从 $0$ 开始。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,h;
	string s;
	cin>>n>>s;
	h=n-1;
	for(int i=n-2;i>=0;i--){
		if(s[i+1]>s[h])
			h=i+1;//更新最大值
		if(s[i]<s[h])
			for(int j=n-1;j>=h;j--)
				if(s[j]>s[i]){//找到就输出+结束
					cout<<i+1<<' '<<j+1;
					return 0;
				}
	}
	cout<<-1;
	return 0;
}
```
~~月赛时我交了好几遍思路错误的代码，后来才想到正确的思路~~

---

## 作者：kkio (赞：0)

# P7478 StickSuger 题解 #
题目大意:

在一个字符串中，找一对${(i,j)}$,交换 $ S[i] $,$ S[j] $后使原字符串字典序变大，且$({i,j)}$最大

思路:

我们看到题目, 发现只要交换后字典序比原来大, 就只用按下标比较, 不需要找到最大字典序。

那么用$i$从后往前找, 找到一个合法的就记录。

讨论寻找时的情况, 先找到$i$时, 若发现$S[i] \ge\ S[i+1]$,则继续往后找, 如果每次的都是 $S[i] \ge\ S[i+1]$, 从$S[i]-S[n]$是递减的, 不可能有解。若是找到了$ S[i] < S[i+1] $, 说明找到了一个可以换的地方, 此时可以枚举$j$。

再从 $n$ 到 $i$ 找一个$j$, 使$S[j]>S[i]$即可。

由于都是从后往前找, 保证一找到就是$(i,j)$最大, 可以直接退出。

## AC代码 ##
```cpp
#include <cstdio>
char S[1000005];
int n;
int main(){
	scanf("%d",&n);
	scanf("%s",S+1);
	int ansl,ansr; 
	for(ansl=n-1;ansl>=1;--ansl)if(S[ansl]<S[ansl+1])break;//先找i，此时S[i]到S[n]是递减的。
	if(!ansl){puts("-1");return 0;}//没找到说明字符串递增,无解。
	for(ansr=n;ansr>ansl;--ansr)if(S[ansr]>S[ansl])break;//再找j,一找到就退出。
	printf("%d %d\n",ansl,ansr);
  	return 0;
}

```

第一次交28ms,时间复杂度最慢~~可能~~是$ O(2n)$


---

## 作者：Mysterious_Cat (赞：0)

### 题目大意：
求最大的$(i, j)$（在$i$取最大时，$j$取最大）使得$a_i<a_j$（ASCII）。
### 题目思路：
数据范围：$1\leq n\leq 10^6$，所以$O(n^2)$的暴力统计行不通，考虑用$box$数组存每个字母最后出现的位置，每读入一个数更新一次答案，复杂度$O(n)$。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int NR = 1e6 + 5;

int box[30];

int main()
{
    int n, ansi = 0, ansj = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        box[c - 'a' + 1] = i;
        for(int j = 1; j < c - 'a' + 1; j++)
        	if(box[j] && (ansj < box[j] || (ansj == box[j] && ansi < i))) ansi = i, ansj = box[j];
    }
    if(ansi) cout << ansj << " " << ansi;
    else cout << -1;
    
    return 0;
}
```


---

## 作者：Nygglatho (赞：0)

注：我题解内的二元组变量 $(i, j)$ 在题解中写的是 $(x, y)$

一个很显然的结论：设 $S_i$ 表示字符串 $S$ 的第 $i$ 个字符，那么，如果字符 $S_i$ 的位置小于字符 $S_j$ 的位置，那么，想要让 $S_i$ 的位置与 $S_j$ 的位置互换，必须要 $S_j$ 的 ASCII 码大于 $S_i$ 的 ASCII 码。

那么，我们就可以仅仅通过判断 ASCII 大小来决定是否合法了。

我们先建立一个数组 $mp$，里面存放着 `a` 至 `z` 每一个字符在 $S$ 中**最后**出现的地方。

然后再让 $i$ 在整个 $S$ 中遍历一遍，先把 $S_i$ 在 $mp$ 数组里更新一遍：
```cpp
for (int i = 0; i < st.size(); ++i) {
	mp[st[i] - 'a' + 1] = i + 1;//我个人mp数组使用范围是从1至26的
```
接着，我们可以新建一个二元组，把 $y$ 固定为 $i + 1$，再让 $j$ 遍历 `a` 至 $S_i$ 前面一个字符，每个字符都遍历一遍，把 $x$ 设置成 $mp_j$，即每一个字符中最靠后的一个位置，然后再与原来的 $x$ 和 $y$ 比较，如果更好就替换掉。
```cpp
for (int j = 1; j < st[i] - 'a' + 1; ++j) {
	if (mp[j] >= x) {
    //注意，上面“大于等于”不能改成“大于”，，因为有可能“y”比原来大。
    //不过也不需要刻意特判“y”，因为是升序遍历，每一个“i+1”（或“y”）都比以前大
		x = mp[j]; y = i + 1;
	}
}
```

---

