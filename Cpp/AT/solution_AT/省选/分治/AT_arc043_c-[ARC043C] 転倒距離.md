# [ARC043C] 転倒距離

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc043/tasks/arc043_c

$ 1 $ から $ N $ の整数を並び替えた数列をサイズ $ N $ の順列と呼ぶ。

同じサイズの順列 $ X,\ Y $ があるとき、$ X $ と $ Y $ で順序が入れ替わっている数字の組の数を $ X $ と $ Y $ の転倒距離と呼ぶ。

例えば $ [3,\ 1,\ 4,\ 2,\ 5] $ と $ [2,\ 5,\ 3,\ 4,\ 1] $ では以下の $ 7 $ 個の組の順序が入れ替わっているので転倒距離は $ 7 $ である。

- $ (1,\ 2),\ (1,\ 4),\ (1,\ 5),\ (2,\ 3),\ (2,\ 4),\ (3,\ 5),\ (4,\ 5) $

サイズ $ N $ の順列 $ A,\ B $ が与えられる。

$ A $ とも $ B $ とも転倒距離が等しいサイズ $ N $ の順列があるか判断し、あるならば $ 1 $ つ挙げよ。

答えが複数通りある場合はどれを挙げても良い。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1\ ≦\ N\ ≦\ 3,000 $ を満たすデータセットに正解した場合は $ 30 $ 点が与えられる。
- $ 1\ ≦\ N\ ≦\ 10^5 $ を満たすデータセットに正解した場合はさらに $ 70 $ 点が与えられる。合計で $ 100 $ 点となる。

### Sample Explanation 1

出力した順列を $ C $ とすると、$ A $ と $ C $の転倒距離も $ B $ と $ C $ の転倒距離も $ 5 $ である。

### Sample Explanation 2

$ A $ とも $ B $ とも同じ転倒距離の順列は存在しません。

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 3 2 1```

### 输出

```
5 2 1 3 4```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 2 4 3 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
9
3 1 4 2 5 9 7 6 8
2 1 8 3 5 7 9 4 6```

### 输出

```
3 1 2 8 4 5 7 9 6```

# 题解

## 作者：lamboo (赞：1)

### ARC043C 転倒距離

> 定义两个排列 $A, B$ 的距离为满足 $(i, j)$ 在 $A, B$ 中顺序相反的无序对数。现在给定排列 $A$ 和 $B$，构造一个排列 $C$ 使得 $dis(A, C) = dis(B, C)$。

若 $(i, j)$ 在 $A,B$ 中的相对位置相同，则对 $dis(A, C)$ 和 $dis(B, C)$ 有相同的贡献。若不同，则对其中一个有 $1$ 的贡献。容易发现有解当且仅当 $dis(A, B)$ 为偶数。将 $A$ 映射为 $1, 2\dots n$。则 $dis(A, B)$ 等于 $B$ 的逆序对数，设为 $s$。

现在我们要构造一个 $C$ 使得 $B$ 中一半的逆序对变成正序对。设 $p$ 为最早满足 $[1, p]$ 中逆序对数大于 $\frac s2$ 的位置。将 $1$ 到 $p - 1$ 排序，再将 $p$ 插入到中间即可。

看代码应该好懂一些吧。

```cpp
#include <bits/stdc++.h>

const int N = 1e5 + 10;

template<typename T = int> inline T read()
{
    T x = 0, f = 0; char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while ( isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return f ? -x : x;
}

struct BIT
{
    int f[N];
    #define lowbit(x) (x & -x)

    inline void Add(int x, int dat = 1)
    {
        for (; x < N; x += lowbit(x)) f[x] += dat;
    }

    inline int Ask(int x)
    {
        int res = 0;
        for (; x; x -= lowbit(x)) res += f[x];
        return res;
    }
}T;

int a[N], A[N], b[N], s[N];

int main()
{
    int n = read(), p = 0; int64_t sum = 0;
    for (int i = 1; i <= n; ++i) a[A[i] = read()] = i;
    for (int i = 1; i <= n; ++i) b[i] = a[read()];
    for (int i = 1; i <= n; ++i) s[i] = T.Ask(N - 1) - T.Ask(b[i]), T.Add(b[i]);
    for (int i = 1; i <= n; ++i) sum += s[i];
    if (sum & 1) return puts("-1"), 0; sum >>= 1;
    for (int i = 1; i <= n; ++i)
    {
        if (sum < s[i]) {p = i; break;}
        sum -= s[i];
    }
    std::sort(b + 1, b + p);
    for (int i = 1; i <= sum; ++i) std::swap(b[p], b[p - 1]), --p;
    for (int i = 1; i <= n; ++i) printf("%d ", A[b[i]]); puts("");
    return 0;
}

```


---

## 作者：弦巻こころ (赞：1)

一道比较有趣的构造.

题意

定义两个排列的颠倒值为$(i,j)(i\in[1,n],j\in[1,n] $&&$ i<j)$ 且$i ,j$满足

$i,j$在$A$的前后顺序与$i,j$在$B$的前后顺序相反

然后求构造一个排列$C$满足 $A,C$的颠倒值= $B,C$的颠倒值

首先我们要知道如何快速的求两个序列之间的転倒距離,我们将$a[i],b[i]$先离散到对应$c[i]$中($c[i]$表示$b[i]$在$a[i]$的桶的出现位置),然后再求一个逆序对,就可以知道两个序列的転倒距離.

具体的我不是很会描述,不过大家看代码应该可以明白()

```cpp
	rep(i,1,n)a[rd()]=i;
	rep(i,1,n)b[i]=rd(),c[i]=a[b[i]];
    //将b[i]离散到a[i]的桶中. 
 
```

一个比较明显的结论就是如果对于一个无序对(i,j),它在A中与在B中的先后顺序相同的话,那么对于$A,C$与$B,C$的$(i,j)$它的贡献一定是相同的,我们将其对应到我们的离散数组中,也就是 $c[i]<c[j]$且$i<j$时$(b[i],b[j])$这个无序对不会有贡献.

我们可以先求出$A,B$之间的転倒距離,然后考虑如何构造一个合法的$C$.


我们发现如果$A$,$B$之间的颠倒距离($c$中逆序对个数)为奇数的话,它一定是不合法的,输出$-1$.

我们考虑对于$c$中的逆序对,如果它在新的$C$中变为顺序对那么会对$B$产生$1$的贡献,否则会对$A$产生$1$的贡献.

一个合法的构造就是原$c$中逆序对,对$A$与$B$贡献相同时的情况.

假设c中逆序对个数为$sum$

那么我们就可以将$sum/2$,然后将$sum/2$个逆序对变为顺序对.

设对于每个$i,j<i(j,i)$为逆序对的个数为$s[i]$

如何进行操作呢,我们如果将$1$~$mx$反转那么会将原来的$\sum_{i=1}^{mx}s[i]$逆序对变为顺序对,那么我们只需要枚举$mx$在哪里即可

如果最后个数不够了,再$for$循环寻找最后一个数需要插入的位置即可

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=114514;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
int rd(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int ans[N],a[N],b[N],c[N],tr[N];
int n,mx,cnt,sp;long long sum,s[N];
int lb(int x){return x&(-x);}
void add(int x){while(x)tr[x]++,x-=lb(x);}
int ask(int x){int k=0;while(x<=n)k+=tr[x],x+=lb(x);return k;}
//树状数组统计逆序对 
int main(){n=rd();
	rep(i,1,n)a[rd()]=i;
	rep(i,1,n)b[i]=rd(),c[i]=a[b[i]];//将b[i]离散到a[i]的桶中. 
	rep(i,1,n)add(c[i]),s[i]=ask(c[i]+1),sum+=s[i];
	if(sum&1){puts("-1");return 0;}sum/=2;
	rep(i,1,n)if(s[i]){
		if(s[i]<sum)sum-=s[i];
		else{if(s[i]==sum)mx=i,sum=0;
			else mx=i-1;break;
		} 
	}//寻找需要翻转的位置 
	rep(i,1,mx/2)swap(b[i],b[mx-i+1]),swap(c[i],c[mx-i+1]);
	if(sum){sum=s[mx+1]-sum;//如果sum多余但比s[mx+1]小,暴力寻找插入的位置 
		rep(i,1,mx){if(c[i]>c[mx+1])cnt++;
			if(cnt==sum){sp=i;break;}
		}
	}rep(i,1,n){if(sp&&i==mx+1)continue;
		printf("%d ",b[i]);if(sp==i)printf("%d ",b[mx+1]);
	}
}
```



---

