# 论如何玩转 Excel 表格

## 题目描述

有一个 $2 \times n$ 的表格，表格内不重不漏地填有 $1 \sim 2 \times n$ 这些数字。你可以进行若干次操作，每次操作可以选择一个 $2 \times 2$ 的正方形区域，然后旋转 $180\degree$。

给出现在的状态以及目标状态。问是否可以达到目标状态。如果能，最少操作次数是多少。

## 说明/提示

#### 子任务

本题采用捆绑测试。

对于 $100\%$ 的数据：$1 \leq n \leq 10^6$。

本题共 $10$ 个子任务，各子任务的分值和限制如下：

子任务 $1$（$1$ 分）：保证输出一定为 `dldsgay!!1`。  
子任务 $2$（$1$ 分）：保证目标状态与现在状态一致。  
子任务 $3$（$4$ 分）：$n=1$。  
子任务 $4$（$5$ 分）：$n=2$。  
子任务 $5$（$14$ 分）：$1 \leq n \leq 20$。  
子任务 $6$（$19$ 分）：$1 \leq n \leq 100$。  
子任务 $7$（$19$ 分）：$1 \leq n \leq 1000$。  
子任务 $8$（$8$ 分）：保证目标状态第一行依次为 $1 \sim n$，第二行依次为  $n + 1 \sim 2n$。  
子任务 $9$（$10$ 分）：保证不存在无解情况。  
子任务 $10$（$19$ 分）：无特殊限制。

## 样例 #1

### 输入

```
1
1
2
2
1
```

### 输出

```
dldsgay!!1
```

## 样例 #2

### 输入

```
2
1 2
3 4
4 3
2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
1 2
3 4
1 2
4 3
```

### 输出

```
dldsgay!!1
```

## 样例 #4

### 输入

```
3
1 6 2
4 3 5
2 4 3
5 1 6
```

### 输出

```
2
```

# 题解

## 作者：RedreamMer (赞：21)

[$\Large\texttt{P6687}$](https://www.luogu.com.cn/problem/P6687)

~~又是一道套路题~~

算法：逆序对（归并排序）

---

$\Large\texttt{Solution}$

题目应该很好理解，就不做赘述。

对于一个 $2*2$ 的表格：

```
1 2
3 4
```

旋转一次后：

```
4 3
2 1
```

可以发现每一列的两个数字是永远呆在一起的，只是上下可能会调换位置。

所以我们可以判断是否有解的问题：以第一个表格第一行作为关键字建桶，将第二行的数放入桶中，与之对应，再遍历第二个表格。

若在 $b[i][j]$ 找到一个关键字 （令这个数字在第一个表格中为 $a[n][m]$ ）判断：

1. **与 $b[i][j]$ 同一列的数**是否等于 **与$a[n][m]$ 同一列的数**。

2. 若 $|m-j|$为奇数，则这一列数字肯定反转了奇数次，则这一列数字一定**顺序相反**。

3. 若 $|m-j|$为偶数，则这一列数字肯定反转了偶数次，则这一列数字一定**顺序一样**。

---

然后就是求解。

因为同一列的数永远不会**分离**，所以将它们看作同一个数，每次旋转，意义就是交换 $i$ 和 $i+1$ 两个数，然后你就会发现这就是一道经典的逆序对问题。

最后，不要忘记特判列数等于 $1$ 的情况。

---

$\Large\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7;
#define int long long
#define MP make_pair

int a, s1[2][N + 10], s2[2][N + 10], top, s[N + 10], l[N + 10], ans, st[N + 10];

void msort(int n, int m)
{
    if (n == m)
        return;
    int mid = (n + m) / 2;
    msort(n, mid);
    msort(mid + 1, m);
    int i = n, j = mid + 1, k = n;
    while (i <= mid && j <= m)
    {
        if (s[i] > s[j])
        {
            l[k++] = s[j++];
            ans += mid - i + 1;
        }
        else
        {
            l[k++] = s[i++];
        }
    }
    while (i <= mid)
        l[k++] = s[i++];
    while (j <= m)
        l[k++] = s[j++];
    for (int i = n; i <= m; i++)
        s[i] = l[i];
}

signed main()
{
    scanf("%lld", &a);
    for (int i = 0; i <= 1; i++)
        for (int j = 1; j <= a; j++)
            scanf("%lld", &s1[i][j]);
    for (int i = 0; i <= 1; i++)
        for (int j = 1; j <= a; j++)
            scanf("%lld", &s2[i][j]);
    for (int i = 1; i <= a; i++) st[s1[0][i]] = i;//以第一行为关键字将第二行数字放入桶中
    if (a == 1)//考场上写的11分代码
    {
        if (s1[0][1] == s2[0][1] || s1[1][1] == s2[1][1])
            puts("0");
        else
            puts("dldsgay!!1");
        return 0;
    }
    else if (a == 2)
    {
        if (s1[0][1] == s2[0][1] && s1[1][1] == s2[1][1] && s1[0][2] == s2[0][2] && s1[1][2] == s2[1][2])
            puts("0");
        else if (s1[0][1] == s2[1][2] && s1[1][2] == s2[0][1] && s1[0][2] == s2[1][1] && s1[1][1] == s2[0][2])
            puts("1");
        else
            puts("dldsgay!!1");
        return 0;
    }
    for (int i = 1; i <= a; i++)//判断是否有解以及建造一个要排序的数组s
    {
        if (st[s2[0][i]])
        {
            if ((i - st[s2[0][i]]) & 1)
            {
                puts("dldsgay!!1");
                return 0;
            }
            s[i] = st[s2[0][i]];
            continue;
        }
        else if (st[s2[1][i]])
        {
            if ((i - st[s2[1][i]]) & 1 == 0)
            {
                puts("dldsgay!!1");
                return 0;
            }
            s[i] = st[s2[1][i]];
            continue;
        }
        puts("dldsgay!!1");
        return 0;
    }
    for (int i = 1; i <= a; i++)
        if (!s[i])
        {
            puts("dldsgay!!1");
            return 0;
        }
    msort(1, a);
    printf("%lld", ans);
    return 0;
}
```

[$\Large\texttt{My Blog}$](https://www.cnblogs.com/RedreamMer/)

---

## 作者：yangwenbin (赞：16)

# P6687 【论如何玩转 Excel 表格】
还没认真阅读题目的人请走这里（[传送门](https://www.luogu.com.cn/problem/P6687)）

这是洛谷月赛的div1.T3难度还算正常。

仔细阅读题目可以发现一点，在同一竖排上只有两种情况

```
如
1 2
3 4
```
第一列只能是
```
1 或 3
3    1
```
故可以把每一列压缩成1和-1

每次操作会把+1变成-1（同理-1也会变成+1）

过可以提前判断不成立的情况

```
if((arr[g[a]].vis1 == a && (g[a]-i) % 2 == 0) || ( arr[g[a]].vis2 == a && ( g[a]-i ) % 2 != 0)){
	continue;
}else{
	printf("dldsgay!!1\n");
	return 0;
}
```
在输入目标时各判断一次

然后是处理了

这里我用了一个特殊的想法（分治）

在压缩后可以变成一个一维的数组，在操作室就类似于排序，这里利用归并排序每次交换（插入）记录次数（不用在意正负，因为不成立已经与处理了）

```
void merge(long long left,long long right){
	if(left == right){
		return ;
	}
	long long mid=(left+right)/2;
	merge(left,mid);
	merge(mid+1,right);
	long long p=left,i=left,j=mid+1;
	while ( i<=mid && j<=right){
		if(arr[i].index>arr[j].index){
			tot=tot+mid-i+1;
			temp[p++].index=arr[j++].index;
			//temp[p].vis=arr[j].vis|(());
		}else{
			temp[p++].index=arr[i++].index;
		}
	}
	while(i<=mid){
		temp[p++].index=arr[i++].index;
	}
	while(j<=right){
		temp[p++].index=arr[j++].index;
	}
	for (i = left; i <= right; ++i){
		arr[i].index=temp[i].index;
	}
}
```

基本就是一个归并的板子


# 记得用快读和开long long


~~(十年OI一场空，不开long long见祖宗）~~

最后是
# code
```
#include <bits/stdc++.h>
using namespace std;
struct point{
	long long vis1,vis2;
	long long index;
}arr[1000050],temp[1000050],ans[1000050];
long long g[2000050];
long long n,tot;
inline int read(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
void merge(long long left,long long right){
	if(left == right){
		return ;
	}
	long long mid=(left+right)/2;
	merge(left,mid);
	merge(mid+1,right);
	long long p=left,i=left,j=mid+1;
	while ( i<=mid && j<=right){
		if(arr[i].index>arr[j].index){
			tot=tot+mid-i+1;
			temp[p++].index=arr[j++].index;
			//temp[p].vis=arr[j].vis|(());
		}else{
			temp[p++].index=arr[i++].index;
		}
	}
	while(i<=mid){
		temp[p++].index=arr[i++].index;
	}
	while(j<=right){
		temp[p++].index=arr[j++].index;
	}
	for (i = left; i <= right; ++i){
		arr[i].index=temp[i].index;
	}
}
int main(){
	n=read();
	for (long long i = 1,a; i <= n; ++i){
		a=read();
		g[a]=i;
		arr[i].vis1=a;
	}
	for (long long i = 1,a; i <= n; ++i){
		a=read();
		g[a]=i;
		arr[i].vis2=a;
	}
	for (long long i = 1,a; i <= n; ++i){
		a=read();
		arr[g[a]].index=i;
		if((arr[g[a]].vis1 == a && (g[a]-i) % 2 == 0) || ( arr[g[a]].vis2 == a && ( g[a]-i ) % 2 != 0)){
			continue;
		}else{
			printf("dldsgay!!1\n");
			return 0;
		}
	}
	for (long long i = 1,a; i <= n; ++i){
		a=read();
		arr[g[a]].index=i;
		if((arr[g[a]].vis2 == a && (g[a]-i) % 2 == 0) || ( arr[g[a]].vis1 == a && ( g[a]-i ) % 2 != 0)){
			continue;
		}else{
			printf("dldsgay!!1\n");
			return 0;
		}
	}
	merge(1,n);
	printf("%lld\n", tot);
	return 0;
}
```

---

## 作者：Provicy (赞：9)

比赛时题目看错了，尴尬（

观察任意一次 $2*2$ 的旋转之后，原来在同一列的数现在仍在同一列；并且，每次旋转会交换同列两个数的顺序。于是我们得到无解的两种情况：

$1$、在原状态中同一列的两个数在目标状态中不处于同一列。

$2$、在原状态中处于第 $x$ 列的两个数，在目标状态中不改变顺序却和 $x$ 非同奇偶，或者在目标状态中不改变顺序却和 $x$ 同奇偶。

然后我们把原状态中第 $i$ 列的两个数打包给个编号为 $i$，并在目标状态中找到对应的编号，这样我们就可以得到一个长度为 $n$ 的排列。题目变为每次可以交换相邻两个数，把这个长度为 $n$ 的排列变为严格上升。

这显然是个求序列逆序对个数的题目...直接用归并排序或者树状数组即可。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <bitset>
#define ri register
#define inf 0x7fffffff
#define E (1)
#define mk make_pair
//#define int long long
#define double long double
using namespace std; const int N=2000010;
inline int read()
{
    int s=0, w=1; ri char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch-'0'), ch=getchar();
    return s*w;
}
void print(int x) { if(x<0) x=-x, putchar('-'); if(x>9) print(x/10); putchar(x%10+'0'); }
int n,a[N][2],b[N][2],book[N][3],h[N];
struct Node{ int x,id; }e[N]; int c[N];
inline int lowbit(int x) { return x&(-x); }
inline void Add(int x,int p) { for(;x<=n;x+=lowbit(x)) c[x]+=p; }
inline int Ask(int x) { int res=0; for(;x;x-=lowbit(x)) res+=c[x]; return res; }
inline bool cp(Node x,Node y) { return x.x<y.x; }
signed main()
{
    n=read();
    for(ri int i=1;i<=n;i++)
    {
        a[i][0]=read(); int u=a[i][0];
        book[u][0]=i;
    }
    for(ri int i=1;i<=n;i++)
    {
        a[i][1]=read(); int v=a[i][1];
        book[v][0]=i;
    }
    for(ri int i=1;i<=n;i++)
    {
        int u=a[i][0], v=a[i][1];
        book[u][1]=v, book[v][2]=u;
    }
    for(ri int i=1;i<=n;i++) b[i][0]=read();
    for(ri int i=1;i<=n;i++) b[i][1]=read();
    for(ri int i=1;i<=n;i++)
    {
        int u=b[i][0];
        int v=b[i][1];
        if(book[u][0]!=book[v][0]) { puts("dldsgay!!1"); return 0; }
        if(book[u][1]&&book[v][2])
        {
            if((i&1) != (book[u][0]&1)) { puts("dldsgay!!1"); return 0; }
        }
        if(book[u][2]&&book[v][1])
        {
            if((i&1) == (book[u][0]&1)) { puts("dldsgay!!1"); return 0; }
        }
    }
    for(ri int i=1;i<=n;i++)
    {
        int u=b[i][0];
        e[i].x=book[u][0], e[i].id=i;
    }
    long long ans=0;
    for(ri int i=1;i<=n;i++)
    {
        Add(e[i].x,1);
        ans+=(long long)i-Ask(e[i].x);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：a___ (赞：8)

先看图：   

![](https://cdn.luogu.com.cn/upload/image_hosting/jvefuegq.png)  
~~（略丑，用的mspaint，我还是没搞明白怎么把图调小）~~

___

我们发现，如果我们对于表格黑白染色（如图），那么对于每一次旋转操作，**仅会发生黑格与黑格交换，白格与白格交换，且原先上下对应（在同一列）的黑白两格仍保持上下对应**，原来在下面的交换到了上面，原来在上面的交换到了下面。   

____

根据这一性质，我们可以做出以下判断：   
1. **如果原来两个数上下对应，任意次旋转后两个数一定仍保持上下对应。**   
2. **原先在黑格的数只能被转到黑格上；原先在白格的数只能被转到白格上。**   

____

据此，我们可以做出对初始状态到目标状态可行性的判断，方法如下：   
1. 将偶数列的数上下对调（为了将同色格全转化到同一行讨论）   
2. 比较初始状态同一黑格（数字相同）对应白格是否相同，若不同，则不可到达   

____

由于已知黑白格相互对应，所以我们接下来可以仅取黑格（对调后的第一行）进行讨论，因为如果 黑格 转到 目标位置，其 对应白格 也一定转到 该黑格的目标位置 所对应的目标位置。 

我们发现，问题变成，已知两个排列，每次可以把相邻两数交换，问至少几次交换可以使两排列相同。   

我们惊喜地发现，这不就是 [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966) 的简化版吗！   

这个 **最小次数** 相当于把 目标排列中的 **数的位置** 当做权值的 **一次排序中交换的最小次数** ，   
而我们知道 **排序中最小交换次数** 等于 **逆序对个数**（[P1774 最接近神的人](https://www.luogu.com.cn/problem/P1774)），   
于是我们使用 **归并排序** 求一次逆序对（[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)）就好了！

___

[AC代码](https://www.luogu.com.cn/paste/hb32umxg)（常数巨大，勿喷）

---

## 作者：tengkaize (赞：5)

事实上将一个 $2 \times 2$ 的正方形区域旋转 $180\degree$ 等价于将左上数字与右下数字，以及右上数字与左下数字交换，所以我们可以得到两个性质：

1. **上下相对的数字在变换过程中保持相对**

2. **表格内一个数字的运动轨迹一定为折线形**

性质 1 很容易理解，它是我们用来判无解的重要依据之一~~但实际上数据太水并没用~~

性质 2 稍微较难，让我们来看个例子，比如这个 $2 \times 5$ 的表

| w | m | w | m | w |
|:-:|:-:|:-:|:-:|:-:|
| m | w | m | w | m |

每次进行旋转时，**w 格子里的数只会跑到 w 格子里，绝对不会跑到 m 格子里，反之亦然**

因此我们得到了判定无解思路二，即验证没有 w 格子里的数跑到了 m 格子里

性质 2 还将表格上的旋转操作化为了序列上元素的交换操作

选取现在表格的一条折线和目标表格的**同一条**折线分别作为现在序列和目标序列，容易发现最少操作次数即为目标序列相对于现在序列的**逆序对个数**

求逆序对可以用归并排序 or 树状数组来求，~~什么冒泡？你没看见那个 $n \le 10^6$ 吗？~~ 由于逆序对的数量级是 $n^2$ 的，$(10^6)^2$ 肯定超了 `int`，所以开 `long long` ~~大坑，我被卡了一小时~~

下面是代码

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

void r(int& i) {
    i = 0;
    int c = getchar();
    for (; c < '0' || '9' < c; c = getchar()) ;
    for (; '0' <= c && c <= '9'; c = getchar()) i = i * 10 + (c  -'0');
}

int n;
int a[1000001][2], b[1000001][2], m[2000001], c[1000001], t[1000001];

// 归并排序求逆序对
long long count_inversion(int b, int e) {
    if (e - b <= 1) return 0;
    int m = b + ((e - b) >> 1);
    long long cnt = count_inversion(b, m) + count_inversion(m, e);
    int l = b, r = m, s = b;
    while (l < m && r < e) {
        if (c[l] > c[r]) {
            cnt += e - r;
            t[s++] = c[l++];
        }
        else {
            t[s++] = c[r++];
        }
    }
    if (l < m) memcpy(t + s, c + l, (m - l) * sizeof(int));
    else memcpy(t + s, c + r, (e - r) * sizeof(int));
    memcpy(c + b, t + b, (e - b) * sizeof(int));
    return cnt;
}

int main() {
    r(n);
    for (int i = 1; i <= n; ++i) r(a[i][0]);
    for (int i = 1; i <= n; ++i) r(a[i][1]);
    for (int i = 1; i <= n; ++i) r(b[i][0]);
    for (int i = 1; i <= n; ++i) r(b[i][1]);
    for (int i = 1; i <= n; ++i) {
        // m 数组记录了 m 格子上 a 中数字对应的下标
        m[a[i][i & 1]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        if (m[b[i][i & 1]]) {
            // 准备求逆序对
            c[i] = m[b[i][i & 1]];
        }
        else {
            // 无解情况
            // 若 m[b[i][i & 1]] == 0
            // 则 w 格子里的数跑到了 m 格子里
            puts("dldsgay!!1");
            return 0;
        }
    }
    printf("%lld\n", count_inversion(1, n + 1));
    return 0;
}
```

---

## 作者：Dzhao (赞：3)

# 题解 P6687
[题目传送门](https://www.luogu.com.cn/problem/P6687)

相信大家题意已经懂了，这里直接讲思路了。

我们可以先模拟一下旋转180°后一个 $2 \times 2$ 的矩阵会发生什么变化：

$\begin{bmatrix}1&2\\3&4\end{bmatrix}$ **$\longrightarrow$** 
$\begin{bmatrix}4&3\\2&1\end{bmatrix}$

我们发现$\begin{bmatrix}2\\4\end{bmatrix}$移到了右边一列，而 $2$ 和 $4$ 也正好上下对调。

因此我们可以推出结论：一开始在同一列的数最后还是在同一列，而有些格子又是可以互相到达的，一个树可以带着他的同伴向斜向方向上移动，用一个矩阵染色可表示为：

![](https://cdn.luogu.com.cn/upload/image_hosting/67s2gh1l.png)

黑色格子可以相互到达，白色格子可以相互到达于是我们可以在操作前先判断一下开始到结束的同伴有没有变，黑色格子里的数是否还在黑格子里，白色格子的数是否还在白格子里，然后我们就将问题转换为了交换相邻两列格子，问最少多少步到目标状态。

我们可以在进一步抽象，将每一列格子抽象成一个编号，而目标状态就抽象成 $1 \sim n$ 的升序序列（即$1\ 2\ 3\ ... \ n$），初始状态抽象成每列格子在目标状态下对应的编号，等于这道题就变成了给你一个 $1 \sim n$ 的无序序列，最少要几次冒泡排序能使序列变的有序，这可以用逆序对来解决，复杂度 $O(n^2)$ ，我们可以再用个树状数组，或者用归并排序，将其优化成 $O(n \log n)$ 。

$\mathcal{View \  \ Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T> //快读 
inline void rd(T &x)
{
	x=0;bool f=0;char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;
}
typedef long long ll;
const int N=1e6+5;
int n,a[3][N],b[3][N],mch[N<<1],col[N<<1],c[N],num[N],tr[N];
inline void add(int x,int z) {for(;x<=n;x+=x&-x) tr[x]+=z;}
inline int sum(int x) {int res=0;for(;x;x-=x&-x) res+=tr[x];return res;}

int main()
{
	rd(n);
	for(int i=1;i<=2;i++)
		for(int j=1;j<=n;j++) rd(a[i][j]);
	for(int i=1;i<=2;i++)
		for(int j=1;j<=n;j++) rd(b[i][j]);
	for(int i=1;i<=n;i++) mch[a[1][i]]=a[2][i],mch[a[2][i]]=a[1][i];
	for(int i=1;i<=n;i++)
		if(mch[b[1][i]]!=b[2][i]) //是否始终和自己的同伴在一起 
		{
			printf("dldsgay!!1\n");
			return 0;
		}
	for(int i=1;i<=2;i++)
		for(int j=1;j<=n;j++)
			col[a[i][j]]=(i+j)%2;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=n;j++)
			if(col[b[i][j]]!=(i+j)%2) //是否始终在相同颜色的格子里 
			{
				printf("dldsgay!!1\n");
				return 0;
			}
	for(int i=1;i<=n;i++)
		c[b[1][i]]=i,c[b[2][i]]=i; //将结束状态抽象成序列 
	for(int i=1;i<=n;i++) num[i]=c[a[1][i]]; //将初始状态抽象成序列 
	ll ans=0;
	for(int i=1;i<=n;i++) //用 BIT计算逆序对个数 
	{
		ans+=sum(n)-sum(num[i]);
		add(num[i],1);
	}  
	printf("%lld\n",ans);
 	return 0;
}
```
是一道比较好且不难的建模题，一定要弄懂，并会运用。

$\mathcal{THANKS \ \ FOR\ \ WATCHING}$

---

## 作者：zzr8178541919 (赞：2)

个人认为：本道题的正解是：**树状数组**

如何想到的呢？

首先对于一个数字，无论怎么转，他总有一些点是到不了的（推理一下或者画一画），也就是说，这个点可以到达的地方是一条固定的路线，是一条锯齿状的线路（这应该都能发现吧）

#### 再仔细看一看，发现这条路线上的所有的点的位置是可以随便交换的

因此我们得到以下的几个想法：

#### 1.令现在状态为A状态，目标状态为B状态。那么A状态的一条线路一定要和B状态的一条线路上的点都对应（位置不一定要相同，但是构成的集合是一样的）
#### ２．无论如何旋转，上下的两个数字除了方向都不会变，即ＡＢ不可能变成ＡＣ。

有这两个，就可以把无解的情况判断出来

接下来，预处理出Ａ状态的每一对数要到Ｂ状态的哪一列，记录到一个数组中，按从小到大的顺序排序。然后处理就行了。

#### 注意，对于一个靠后的数对转到前面去时，在该数对前面的数对都会向后移动一位。因此我们用一个树状数组来记录每一个位置向后移动的次数。处理每位时统计起来即可
AC代码：

```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int mod=998244353;
const int maxn=2e6+5;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9' || ch<'0')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n;
int a[3][maxn];
int b[3][maxn];
int f1[15];
int f2[15];
int tree[maxn];
struct node
{
	int x,y;
}s1[maxn],s2[maxn];
struct vode
{
	int tag;
	int p;
}place[maxn];
int lowbit(int x)
{
	return x & (-x);
}
void add(int x,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
	tree[i]+=val;
}
struct node1
{
	int x;
	int to;
}wns[maxn];
int Find(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
	res+=tree[i];
	return res;
}
int to[maxn];
bool cmp(node1 a,node1 b)
{
	return a.to<b.to;
}
signed main()
{
	n=read();
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=read();
		}
	}
	int flag=0;
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=n;j++)
		{
			b[i][j]=read();
			int op=0;
			if((i+j) & 1)
			op=1;
			place[b[i][j]].tag=op;
			place[b[i][j]].p=j;
			if(b[i][j]!=a[i][j])
			flag=1;
		}
	}
	flag=0;
	for(int i=1;i<=n;i++)
	{
		vode p1=place[a[1][i]];
		vode p2=place[a[2][i]];
		if(p1.p!=p2.p)
		{
			printf("dldsgay!!1\n");
			return 0;
		}
		//cout<<p1.p<<" "<<p2.p<<endl;
		//cout<<p1.tag<<" "<<((i+1) & 1)<<endl;
		int dist=abs(i-p2.p);
		if(p1.tag!=((i+1) & 1))
		{
			printf("dldsgay!!1\n");
			return 0;
		}
		to[i]=p1.p;
		wns[i].to=p1.p;
		wns[i].x=i;
	}
	int ans=0;
	sort(wns+1,wns+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int p=wns[i].x+Find(wns[i].x);
		ans=(ans+(p-i));
		add(1,1),add(wns[i].x+1,-1);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：sfmmdm (赞：2)

~~这题居然卡常，没快读还过不了！因此本蒟蒻被卡了3个substackQAQ~~

让我们想想每次操作会发生什么：

假设要旋转的这部分原来长这样

| 13 | 14 |
| :----------: | :----------: |
| 1 | 3 |
| 2 | 5 |

转完后变成

| 13 | 14 |
| :----------: | :----------: |
| 5 | 2 |
| 3 | 1 |

即对角线交换。

我们发现，无论怎么交换，同一列的两个数永远不会分开，所以，只要在初始状态里面~~在一起~~的两个数，在目标状态分开了，那就是不可能的。

而且，一次旋转会让一组数颠倒过来，并且水平移动一格，那么如果初始状态到目标状态距离为**奇数**格，那么就应该是颠倒状态，反之，就和原来一样。如果不满足这两个条件，就是不可能的。

那么，相当于我们把同一列的两个数看做一个整体，每次旋转，就是交换两组数。

问你从初始状态到目标状态，最少的旋转（交换）次数。

这……不是求逆序对吗？

然后问题完美解决了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1000005][2],b[1000005][2],st[2000005][2],c[1000005],t[1000005];
long long ans;
inline int lowbit(int x) {
	return x&(-x);
}
int read() {
	char ch=getchar();
	int x=0;
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
int query(int x) {
	int ret=0;
	while(x) {
		ret+=t[x];
		x-=lowbit(x);
	}
	return ret;
}
void change(int x,int y) {
	while(x<=n) {
		t[x]+=y;
		x+=lowbit(x);
	}
}
int main() {
	n=read();
	bool flag=0;
	for(int i=1; i<=n; i++) {
		a[i][0]=read();
		st[a[i][0]][0]=i;
		st[a[i][0]][1]=0;
	}
	for(int i=1; i<=n; i++) {
		a[i][1]=read();
		st[a[i][1]][0]=i;
		st[a[i][1]][1]=1;
	} //输入初始状态时，用st数组，st[i][0]表示数字i在初始状态的列数，st[i][1]表示行数
	for(int i=1; i<=n; i++) {
		b[i][0]=read();
	}
	for(int i=1; i<=n; i++) {
		b[i][1]=read();
		if(st[b[i][0]][0]!=st[b[i][1]][0]) flag=1;//如果在目标状态的同一列的两个数初始状态不在同一列，就是不可能的。
		int x=st[b[i][0]][0]-i+st[b[i][0]][1];//单纯判断b[i][0]在初始和目标状态的列数，同时如果颠倒了，则st[b[i][0]][1]会等于1，否则等于0，二者相加如果为奇数则不可能。
		if(x%2==1) flag=1;
		c[i]=st[b[i][0]][0];
	}
	if(flag==1) {
		printf("dldsgay!!1\n");
		return 0;
	}
	if(n==1) {//n==1时，没有办法旋转，如果一样就转0次，否则就不可能
		if(a[1][0]==b[1][0]&&a[1][1]==b[1][1]) printf("0\n");
		else printf("dldsgay!!1\n");
		return 0;
	}
	if(n==2) {
		if(a[1][0]==b[1][0]&&a[1][1]==b[1][1]&&a[2][0]==b[2][0]&&a[2][1]==b[2][1]) printf("0\n");
		else if(a[1][0]==b[2][1]&&a[1][1]==b[2][0]&&a[2][0]==b[1][1]&&a[2][1]==b[1][0]) printf("1\n");
		else printf("dldsgay!!1\n");
		return 0;
	}
	for(int i=n; i; i--) { //树状数组求逆序对
		ans=ans+query(c[i]-1);
		change(c[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}
```

**最后提示，一定要写快读，不写会被卡，~~血与泪的教训~~**

---

## 作者：Vocalise (赞：1)

一道似乎挺有趣的题，不过听大家说太简单了（？）

首先考虑旋转操作。

你会发现实际上就是两个对角线的交换。

那如果我们把某一奇偶性的所有列上下交换，这个操作自然就变成了相邻两列的直接交换了。

因为每一列在操作中显然是不会拆散的，所以可以 $O(n)$ 地判断 $a$ 和 $b$ 的每一列构成的序列是否只是不同的两个排列。如果 $b$ 中出现了 $a$ 中没有的一列，则无解。

否则，我们考虑问题为：两个排列，其中一个排列通过交换相邻元素构成另一序列的最少操作次数。

通过简单的置换可以将目标转化为升序排列，发现我们就是将原序列冒泡排序。

冒泡排序的最小交换次数显然就是逆序对数，用树状数组统计即可。

时间是 $O(n\log n)$ 的。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

typedef long long ll;
const int MAXN = 2000001;

int n,a[2][MAXN],b[2][MAXN];
int m[MAXN];

bool Deter() {
	for(int i = 1;i <= n;i++) m[a[0][i]] = a[1][i];
	for(int i = 1;i <= n;i++) {
		if(m[b[0][i]] != b[1][i]) return false;
	}
	return true;
}

ll s[MAXN];

int lowbit(int x) { return x & (-x); }

void Insert(int i,ll x) {
	for(;i < MAXN;i += lowbit(i))
		s[i] += x;
}

ll Query(int i) {
	ll res = 0;
	for(;i;i -= lowbit(i)) res += s[i];
	return res;
}

int main() {
	n = read();
	for(int i = 1;i <= n;i++) a[0][i] = read();
	for(int i = 1;i <= n;i++) a[1][i] = read();
	for(int i = 1;i <= n;i++) b[0][i] = read();
	for(int i = 1;i <= n;i++) b[1][i] = read();
	for(int i = 2;i <= n;i += 2) std::swap(a[0][i],a[1][i]);
	for(int i = 2;i <= n;i += 2) std::swap(b[0][i],b[1][i]);
	if(!Deter()) return std::puts("dldsgay!!1"), 0;
	for(int i = 1;i <= n;i++) m[b[0][i]] = i;
	for(int i = 1;i <= n;i++) a[0][i] = m[a[0][i]];
	ll ans = 0;
	for(int i = 1;i <= n;i++) {
		ans += i - 1 - Query(a[0][i]);
		Insert(a[0][i],1);
	}
	std::printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：TEoS (赞：0)

分析题意后可以发现就是求逆序对，此外要判断是否合法。

合法的条件：对应列的数字是否匹配，是否能通过旋转从而重合。

第一个条件，输入的时候存储，判断即可。

第二个条件，存储始末状态的位置，若始末状态相同则间隔需要为偶数，反之为奇数。

然后用树状数组求逆序对即可。

有点小卡常，打了个快读才 AC 。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int N=2e6+100;
int n;
int x[N],y[N],dx[N],qx[N],l[N],t[N];
ll ans;
int read(){
    int w=1,num=1;
    char ch;
    while(ch=getchar(),ch<'0' || ch>'9')
        if(ch=='-') w=-1;
    num=ch-'0';
    while(ch=getchar(),ch>='0' && ch<='9')
        num=(num<<3)+(num<<1)+ch-'0';
    return num*w;
}
void add(int x)
{
	for(;x<=n;x+=x&-x)
		t[x]++;
}
int ask(int x)
{
	int now=0;
	for(;x;x-=x&-x)
		now+=t[x];
	return now;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		dx[i]=read();
	for(int i=1,k;i<=n;i++)
		k=read(),x[k]=dx[i],y[dx[i]]=k,l[dx[i]]=l[k]=i;//存储初状态
	for(int i=1;i<=n;i++)
		qx[i]=read();
	for(int i=1,k;i<=n;i++)
	{
		k=read();
		if((x[k]!=qx[i] && y[k]!=qx[i])||(x[k]==qx[i] &&(l[k]-i)%2==1)||(y[k]==qx[i] &&(l[k]-i)%2==0))//不合法的情况
		{
			puts("dldsgay!!1");
			return 0;
		}
		ans=ans+ask(n-l[k]);
		add(n-l[k]+1);//树状数组求逆序对
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：KSToki (赞：0)

看许多大佬都用了逆序对，蒟蒻比赛时就想到了用**模拟**解决这个问题。~~模拟大法好~~

大佬们都说了，旋转$180$相当于上下翻转并左右翻转，这个条件是用来判无解的。在当前状态中同一列的两个数必须在目标状态的同一列中，且通过讨论奇偶性确定其是否经过翻转。接下来解决有解的情况。

基本策略是每次找目标数列中的第一列在当前数列中的位置，记为$x$列，并把其移到位，统计步数，然后扔掉。显然如此暴力的方法是正确的，但时间复杂度达到了$O(n^2)$，会T到飞起。

考虑优化，我们发现每次操作会使第$x$列前的所有列向后移动一格并上下翻转。此时就算经过移动，该在某一列前面的还是在它前面。因此我们只需打个标记，并不用真正的去移动，统计答案时为初始位置+标记数-目标位置。

如果一个一个去打标记的话，那优化就大可不必了，还是$O(n^2)$。区间打标记、单点查询标记数量，你想到了什么？

没错，就是线段树/树状数组！由于线段树常数较大，推荐使用树状数组。时间复杂度为$O(nlogn)$，可以通过。

代码，记得开long long：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[3][1000001],b[3][1000001];
ll ans;
inline int read()//快读，卡常必备
{
	int f=1,res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return f*res;
}
////////
int c[1000001];
int lowbit(int x)
{
	return x&(-x);
}
void update(int x,int y)
{
	for(;x<=n;x+=lowbit(x))
	    c[x]+=y;
}
int sum(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
	    res+=c[x];
	return res;
}
////////树状数组模板
int r[2000001];
int main()
{
	n=read();
	for(register int i=1;i<=n;++i)
	    a[1][i]=read();
	for(register int i=1;i<=n;++i)
	    a[2][i]=read();
	for(register int i=1;i<=n;++i)
	    b[1][i]=read(),r[b[1][i]]=i;
	for(register int i=1;i<=n;++i)
	    b[2][i]=read(),r[b[2][i]]=i;//记录它的所在列，由于数字范围明确且较小，不使用map
	for(register int i=1;i<=n;++i)
	{
		////以下是无解判断
                if(r[a[1][i]]!=r[a[2][i]])
		{
			printf("dldsgay!!1\n");
			return 0;
		}
		int line=r[a[1][i]];
		int tag=sum(line);
		if((line+tag-i)&1)
		{
			if(tag&1)
			{
				if(b[1][line]==a[2][i])
				{
					printf("dldsgay!!1\n");
					return 0;
				}
			}
			else
			{
				if(b[1][line]==a[1][i])
				{
					printf("dldsgay!!1\n");
					return 0;
				}
			}
		}
		else
		{
			if(tag&1)
			{
				if(b[1][line]==a[1][i])
				{
					printf("dldsgay!!1\n");
					return 0;
				}
			}
			else
			{
				if(b[1][line]==a[2][i])
				{
					printf("dldsgay!!1\n");
					return 0;
				}
			}
		}
        ////以上是无解判断
		ans+=(ll)line+tag-i;
		update(1,1);
		update(line,-1);//精髓：统计答案并更新树状数组
	}
	printf("%lld\n",ans);
	return 0;
}
```
完！

---

