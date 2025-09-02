# [POI 2009] ARC-Architects

## 题目描述

给定一个序列 $a_i$（$1\leq a_i\leq 10^9$）且 $1\leq i\le n$ 且 $n\leq  
 1.5\times 10^7$，和一个整数 $k$（$k\leq n$ 且 $k\leq 10^6$），求出 $a$ 的一个长度为 $k$ 的子序列 $a_{b_i}$ 满足：

1. $1\leq b_1\leq b_2\leq \ldots\leq b_k$
2. 在满足 $1$ 的情况下 $a_{b_1}, a_{b_2},\ldots , a_{b_k}$ 字典序最大。


## 说明/提示

本题原为交互题，为评测方便，需要将下面的代码粘贴到文件中。

将第一次输入改为 `=inicjuj()` 形式，将之后的每一次输入改为 `=wczytaj()` 形式，将输出改为 `wypisz(jakoscProjektu)` 形式（`jakoscProjektu` 代表你输出的数）。

```cpp
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAGIC_BEGIN -435634223
#define MAGIC_END -324556462

#define MIN_K 1
#define MAX_K 1000000
#define MAX_N 15000000
#define MIN_A 1
#define MAX_A 1000000000
#define MIN_TYP 1
#define MAX_TYP 3
#define MIN_PAR 0
#define MAX_PAR 1000000000

#define ERROR 0
#define CORRECT 1

#define unlikely(x) __builtin_expect(!!(x), 0)

static int init = 0; // czy zostala juz wywolana funkcja inicjuj()
static int lib_n; // ile biblioteka podala juz liczb
static int con_k; // ile zawodnik podal liczb

static int N, K, A, TYP, PAR; // parametry testu wczytywane z pliku
static int bre, len_sub, bou, is_end; // zmienne pomocnicze

static int rand2_status = 198402041;

static inline int rand2(int a, int b){
  rand2_status = rand2_status * 1103515245ll + 12345;
  int x = rand2_status;
  if (x < 0) x = -x; // -2^31 sie nie zdarza :D
  x >>= 1;
  x = a + x % (b - a + 1);
  return x;
}

/* test losowy */
static inline int random_test()
{
    return rand2(1, A);
}

/* test z dlugim podciagiem nierosnacym */
static inline int decreasing_test()
{
    int tmp;
    if(bre == 0) {
        bre = rand2(0, (N - lib_n + 1 - len_sub));
        tmp = A;
        A -= rand2(0, (A - 1) / len_sub);
        len_sub--;
    }
    else {
        bre--;
        tmp = rand2(1, A);
    }
    return tmp;
}

/* test z dlugim podciagiem niemalejacym */
static inline int increasing_test()
{
    return bou - decreasing_test();
}

static void finish(int res, const char com[])
{
    if(res == ERROR)
        printf("%s\n", com);
    exit(0);
}

/* Inicjuje dane wejsciowe i zwraca liczbe projektow */
int inicjuj()
{
    if(init == 1)
        finish(ERROR, "Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    init = 1;
    scanf("%d", &K);
    if (K > 0){
      TYP = 0;
      N = MAX_N + 2;
      return K;
    }
    int magic_begin, magic_end;
    scanf("%d%d", &magic_begin, &TYP);
    if(magic_begin != MAGIC_BEGIN || TYP < MIN_TYP || TYP > MAX_TYP)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d%d%d%d", &N, &K, &A, &PAR);
    if(N < 1 || N > MAX_N || N < K || K > MAX_K || A < MIN_A || A > MAX_A 
        || PAR < MIN_PAR || PAR > MAX_PAR)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d", &magic_end);
    if(magic_end != MAGIC_END)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    con_k = 0;
    lib_n = 0;
    is_end = 0;
    if(TYP == 2 || TYP == 3) {
        len_sub = PAR;
        bre = 0;
    }
    if(TYP == 2)
        bou = A--;
    return K;
}

/* Sluzy do wczytania ciagu reprezentujacego jakosci projektow */
int wczytaj()
{
    if(unlikely(init == 0))
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(unlikely(lib_n > N || is_end == 1))
        finish(ERROR, "Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    if(unlikely(lib_n == N))
        return 0;
    lib_n++;
    switch (TYP) {
      case 0:
        scanf("%d", &A);
        if(A == 0)
          is_end = 1;
        return A;
        break;
      case 1: return random_test(); break;
      case 2: return increasing_test(); break;
      case 3: return decreasing_test(); break;
      default:
              finish(ERROR, "Nieznany typ testu");
    }
    return -1;
}

/* Sluzy do wypisania wyznaczonego podciagu */
void wypisz(int jakoscProjektu)
{
    if(init == 0)
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    printf("%d\n", jakoscProjektu);
    if(++con_k == K)
        finish(CORRECT, "");
}
```

## 样例 #1

### 输入

```
3
12 5 8 3 15 8 0```

### 输出

```
12
15
8```

# 题解

## 作者：a___ (赞：6)

水题，~~建议降黄~~。    

如果交互库下不下来的可以选择直接复制我的[模板](https://www.luogu.com.cn/paste/ypdfalec)。

其实就是单调队列模板题，之前两个题解一个堪称史上最短题解，另一个说了半天废话最后放了一堆要么过不了要么太繁琐的代码，于是我就来水题解了。

虽然题目有些迷惑写了 $1\leq b_1\leq b_2\leq \ldots\leq b_k$，但实际是指 $1\leq b_1\lt b_2\lt \ldots\lt b_k$，也就是说同一个数并不能选多次。于是正确的题意为在序列 $a$ 中选一个长度为 $k$ 的子序列使其字典序最大。   

具体思路很简单，因为字典序是从前向后比较，所以我们要让前面的数尽可能大，所以我们每次选一个最大值输出；因为后选的不能在前选的前面以及总共只有 $n$ 个数，所以有 $b_1\in[1,n-k+1],b_2\in[b_1+1,n-k+2],\dots,b_k\in[b_{k-1}+1,n]$。     

想要解决这个问题，我们可以维护一个单调递减的单调队列，在维护到第 $n-k+i$ 个数的时候取一次最大值并删除，就得到第 $i$ 个位置的值。由于是单调队列，后面取的一定在前面取的值的后面（因为前面的已被顶掉）；仅算到 $n-k+i$ 个数是为了让后面留出至少 $i-1$ 个数的位置；至于每次删掉最值是为了让后面不重复取。     

然后我们惊奇地发现，开 **一个** `int` 大小为 $1.5e7$ 的数组竟然不会炸 125MB。于是我们可以先把所有数读进来，这样就可以知道 $n$ 是多少了。由于我们只有在最后 $k$ 位需要从前面弹数，而且我们最多只需要前 $k$ 大的数，所以队列开到 $2e6$ 就好了。      

实现上还有一个问题就是平时单调队列需要把相等数全部弹出，但我们这里要把相等的数留下来，因为我们可以取不在同一位置上的相等的数。     

最后说一下交互，注意按 **评测方式** 中说的来，注意不要与交互库重变量名。

c 代码（因为交互库是.c，所以我就写成c了）
```c
/*前180行是交互库，这里省略*/
#define MAXN 15000010
#define MAXM 2000010
int q[MAXM],s,t;
int a[MAXN];
int main()
{
	int k=inicjuj();
	int i;
	do a[++a[0]]=wczytaj(); while(a[a[0]]);
	--a[0];int x=a[0]-k+1;s=0;t=1;
	for(i=1;i<=a[0];i++)
	{
		while(s<=t&&q[t]<a[i])--t;/*不要写=，保留相等数*/
		if(t-s+1<k)q[++t]=a[i];/*保持在k个数之内*/
		if(i>=x)wypisz(q[s]),++s;/*取出最大值*/
	}
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：5)

。。一开始想到了线段树，想了一会以后才发现是单调队列。

主要就是优化方面：队列内超过k个元素就弹出队尾。


---

## 作者：dapanggoule (赞：3)

这是本人的第四篇题解，但前三篇都没通过。

观察题面：按顺序选数，求字典序最大，就相当于几个数字比大小，而题目要求这几个数的位数都为k，所以又从首位开始比较。即：

假设k=3，134，234，353，135，643，645中找最大的，肯定是先看首位，找到6，再看下一位，4，再下一位，5，于是答案是645

那么就可以贪心，4，6，3，6，2，1中选3个数，令其下标为1~6，选第一个数时，要在1~（6-2）中选最大，因为要保证至少还有2个数可以选，如果有多个一样的数，显然要选下标小的。选出第一个数=>6，2。那么下一次就要在（2+1）~（6-1）中选，即从上一个选中的下标+1~6-（k-i）。

有人就想：这么简单，爆搜不就行了。~~我其实一开始也是这么想的~~，看看数据范围1<=n<=15000000。呵呵……

那只能用一些快速求不修改RMQ的数据结构，st表是一个很好的选择。


正常的st表是用来存区间最大或最小值的，但从上面的贪心部分可以看出，下标是在变化的。被我们班上的一个大佬提醒:可以用st数组存下标。那么只需要中转一次就可以解决。

code：
```cpp
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN=15000000;
#define MAXNLOG 21
int St[MAXN][MAXNLOG];
int a[MAXN];
int k;
int main()
{
    cin >>k;
    int cnt;
    int n=0;
    cin >>cnt;
    while (cnt!=0)
    {
        n++;
        a[n]=cnt;
        //cout <<a[n]<<' ';
        St[n][0]=n;
        cin >>cnt;
    }
    for (int j=1;j<=MAXNLOG;j++)
    {
        for (int i=1;i+(1<<j)-1<n;i++)
        {
            int x=St[i][j-1];
            int y=St[i+(1<<(j-1))][j-1];
            if (a[x]>a[y])//这个就是所谓的中转，a[St[…][…]];
            {
                St[i][j]=x;
            }
            else if (a[x]==a[y])
            {
                St[i][j]=min(x,y);//取最小下标
            }
            else
            {
                St[i][j]=y;
            }
        }
    }
    /*for (int j=1;j<=MAXNLOG;j++)
    {
        for (int i=1;i<=n;i++)
        {
            cout <<St[i][j-1]<<' ';
        }
        cout <<endl;
    }*/
    int l=1;
    for (int i=k;i>0;i--)
    {
        int r=n-i+1;//左右区间下标
        double cmp=log2(r-l+1);
        int len=cmp;
        int x=St[l][len];
        int y=St[r-(1<<len)+1][len];
        if (a[x]>a[y])
        {
            cout <<a[x]<<endl;
            l=x+1;//更新
        }
        else
        {
            cout <<a[y]<<endl;
            l=y+1;
        }
    }
    return 0;
}
```
然而，MLE了，

所以，为了节省空间，尝试一下线段树

code：
```cpp
#include <iostream>

using namespace std;

#define MAXN 15000000
long tree[3*MAXN];
long a[MAXN];
long k;
long n;
void build(long i,long l,long r)
{
    if (l==r)
	{
		tree[i]=l;
		return ;
	}
	long mid=(l+r)/2;
	//cout <<l<<' '<<r<<' '<<mid<<' '<<i<<endl;
	build(i*2,l,mid);
	build((i*2)+1,mid+1,r);
	if (a[tree[i*2]]>a[tree[(i*2)+1]])
    {
        tree[i]=tree[i*2];
    }
    else if (a[tree[i*2]]==a[tree[(i*2)+1]])
    {
        tree[i]=min(tree[i*2],tree[(i*2)+1]);
    }
    else
    {
        tree[i]=tree[(i*2)+1];
    }
    return ;
}
long cmp;

long query(long i,long l,long r,long x,long y)
{
	if (x<=l&&r<=y)
    {
        return tree[i];
    }
    long maxn=9999999;
	long mid=(l+r)/2;
	if (x<=mid)
    {
        cmp=query(i*2,l,mid,x,y);
        if (a[maxn]<a[cmp])
        {
            maxn=cmp;
        }
        else if (a[maxn]==a[cmp])
        {
            maxn=min(cmp,maxn);
        }
    }
	if (y>mid)
    {
        cmp=query(i*2+1,mid+1,r,x,y);
        if (a[cmp]>a[maxn])
        {
            maxn=cmp;
        }
        else if (a[maxn]==a[cmp])
        {
            maxn=min(cmp,maxn);
        }
    }
	return maxn;
}
int main()
{
    cin >>k;
    long cnt;
    cin >>cnt;
    while (cnt!=0)
    {
        n++;
        a[n]=cnt;
        cin >>cnt;
    }
    build(1,1,n);
    /*for (long i=1;i<=100;i++)
    {
        cout <<tree[i]<<' ';
    }*/
    long l=1;
    for (long i=k;i>0;i--)
    {
        long r=n-i+1;
        //cout <<l<<' '<<r<<' ';
        cmp=query(1,1,n,l,r);
        l=cmp+1;
        cout <<a[cmp]<<endl;
    }
    return 0;
}

```
依旧，还是有MLE的

那就只能用单调队列了
```cpp
#include <iostream>
#include <queue>

using namespace std;

#define MAXN 15000000
struct NUM
{
    long num,i;
};
deque <NUM> q;
long k,a[MAXN];
long n;
int main()
{
    cin >>k;
    long cnt;
    cin >>cnt;
    while (cnt!=0)
    {
        n++;
        a[n]=cnt;
        cin >>cnt;
    }
    long l=1;
    long r;
    for (long i=k;i>0;i--)
    {
        r=n-i+1;
        for (long j=l;j<=r;j++)
        {
            if(q.empty())
            {
                NUM x;
                x.num=a[j];
                x.i=j;
                q.push_back(x);
            }
            else if (q.back().num<a[j])
            {
                while (!q.empty()&&q.back().num<a[j])
                {
                    q.pop_back();
                }
                NUM x;
                x.num=a[j];
                x.i=j;
                q.push_back(x);
            }
            else
            {
                NUM x;
                x.num=a[j];
                x.i=j;
                q.push_back(x);
            }
        }
        cout <<q.front().num<<endl;//<<' '<<l<<' '<<r;
        l=1+q.front().i;
        while (!q.empty())
        {
            q.pop_back();
        }
    }
    return 0;
}

```
**最后，感谢管理员抽空审查**


---

## 作者：Alex_Wei (赞：2)

> [P3487 [POI2009]ARC-Architects](https://www.luogu.com.cn/problem/P3487)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/poi.html)。

POI 真的很喜欢出 [单调队列](https://www.cnblogs.com/alex-wei/p/DP_Involution.html)！

字典序最大给予我们贪心的思路，即优先选择最大的数字肯定更优，若数字相同则尽量选更前面的，因为这样剩下来的选择就更多。如 $[9,7,9,6]$，选前面的 $9$ 就比选后面的 $9$ 好。

但是有 $b_i < b_{i + 1}$ 的限制，说明如果我们选最大的，可能导致后面没法选了。因此不妨设我们在选 $b_i$，我们只能从下标为 $[b_{i - 1} + 1, k - i + 1]$ 的数当中挑选，因为如果 $b_i$ 再大一点，那么无论如何我们都选不齐 $k$ 个数。实现就是经典滑动窗口，若当前数等于单调队列队尾则不弹出，保证了相同数优先选择更前面的。时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int NN = 1.5e7 + 5;
int hd = 1, tl, d[NN], n, k, a[NN];
void push(int p) {while(hd <= tl && a[d[tl]] < a[p]) tl--; d[++tl] = p;}
int main() {
	k = inicjuj(), a[1] = wczytaj();
	for(int i = 2; a[i - 1]; i++, n++) a[i] = wczytaj();
	for(int i = 1; i <= n - k; i++) push(i);
	for(int i = n - k + 1, lim = 1; i <= n; i++) {
		while(hd <= tl && d[hd] < lim) hd++; push(i);
		wypisz(a[d[hd]]), lim = d[hd] + 1;
	}
	return 0;
}
```

---

## 作者：highscore (赞：1)

# [POI2009]ARC-Architects
题意：给定一个序列，从中挑选k个数，满足下标单调递增，并且字典序最小；
思路：由于字典序最小，所以考虑贪心，即前面的数尽可能大，所以用单调队列维护最大值；
细节：注意单调队列对头应该是上次选的数的下一个数，另外要满足k个数，所一直以维护队尾；
因为是交互题，注意变量名重复；
```
/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    carclib.c                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Biblioteka do wczytywania danych wejsciowych i wypisywania *}
{*            wyniku                                                     *}
{*                                                                       *}
{*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAGIC_BEGIN -435634223
#define MAGIC_END -324556462

#define MIN_K 1
#define MAX_K 1000000
#define MAX_N 15000000
#define MIN_A 1
#define MAX_A 1000000000
#define MIN_TYP 1
#define MAX_TYP 3
#define MIN_PAR 0
#define MAX_PAR 1000000000

#define ERROR 0
#define CORRECT 1

#define unlikely(x) __builtin_expect(!!(x), 0)

static int init = 0; // czy zostala juz wywolana funkcja inicjuj()
static int lib_n; // ile biblioteka podala juz liczb
static int con_k; // ile zawodnik podal liczb

static int N, K, A, TYP, PAR; // parametry testu wczytywane z pliku
static int bre, len_sub, bou, is_end; // zmienne pomocnicze

static int rand2_status = 198402041;

static inline int rand2(int a, int b){
  rand2_status = rand2_status * 1103515245 + 12345;
  int x = rand2_status;
  if (x < 0) x = -x; // -2^31 sie nie zdarza :D
  x >>= 1;
  x = a + x % (b - a + 1);
  return x;
}

/* test losowy */
static inline int random_test()
{
    return rand2(1, A);
}

/* test z dlugim podciagiem nierosnacym */
static inline int decreasing_test()
{
    int tmp;
    if(bre == 0) {
        bre = rand2(0, (N - lib_n + 1 - len_sub));
        tmp = A;
        A -= rand2(0, (A - 1) / len_sub);
        len_sub--;
    }
    else {
        bre--;
        tmp = rand2(1, A);
    }
    return tmp;
}

/* test z dlugim podciagiem niemalejacym */
static inline int increasing_test()
{
    return bou - decreasing_test();
}

static void finish(int res, char *com)
{
    if(res == ERROR)
        printf("%s\n", com);
    exit(0);
}

/* Inicjuje dane wejsciowe i zwraca liczbe projektow */
int inicjuj()
{
    if(init == 1)
        finish(ERROR, "Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    init = 1;
    scanf("%d", &K);
    if (K > 0){
      TYP = 0;
      N = MAX_N + 2;
      return K;
    }
    int magic_begin, magic_end;
    scanf("%d%d", &magic_begin, &TYP);
    if(magic_begin != MAGIC_BEGIN || TYP < MIN_TYP || TYP > MAX_TYP)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d%d%d%d", &N, &K, &A, &PAR);
    if(N < 1 || N > MAX_N || N < K || K > MAX_K || A < MIN_A || A > MAX_A 
        || PAR < MIN_PAR || PAR > MAX_PAR)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d", &magic_end);
    if(magic_end != MAGIC_END)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    con_k = 0;
    lib_n = 0;
    is_end = 0;
    if(TYP == 2 || TYP == 3) {
        len_sub = PAR;
        bre = 0;
    }
    if(TYP == 2)
        bou = A--;
    return K;
}

/* Sluzy do wczytania ciagu reprezentujacego jakosci projektow */
int wczytaj()
{
    if(unlikely(init == 0))
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(unlikely(lib_n > N || is_end == 1))
        finish(ERROR, "Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    if(unlikely(lib_n == N))
        return 0;
    lib_n++;
    switch (TYP) {
      case 0:
        scanf("%d", &A);
        if(A == 0)
          is_end = 1;
        return A;
        break;
      case 1: return random_test(); break;
      case 2: return increasing_test(); break;
      case 3: return decreasing_test(); break;
      default:
              finish(ERROR, "Nieznany typ testu");
    }
    return -1;
}

/* Sluzy do wypisania wyznaczonego podciagu */
void wypisz(int jakoscProjektu)
{
    if(init == 0)
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    printf("%d\n", jakoscProjektu);
    if(++con_k == K)
        finish(CORRECT, "");
}
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=2e7+7;
int n,k,h1=1,h2=0,t=1;
int a[MAXN],q[MAXN];
int main(){
    k=inicjuj();
    while(1) {
        a[++n]=wczytaj();
        if(a[n]==0)break;
    }
    n--;
//    cout<<n<<" "<<k<<" "<<h1<<" "<<h2<<" "<<t<<" "<<q[1]<<"\n";
    for(int i=1;i<=k;i++){
        while(t<=n-k+i){
            while(h2>=h1&&q[h2]<a[t]){
                h2--;
            }
            q[++h2]=a[t];
            t++;
        }
//        cout<<q[h1]<<"\n";
        int jakoscProjektu=q[h1];
        wypisz(jakoscProjektu);
//        wypisz('\n');
        h1++;
    }
}
```

---

## 作者：CatFromMars (赞：0)

早起试机=w=

由于这道题要求字典序最大，所以容易想到是一个贪心。第一个数最大是多少？因为这里要求是一个长度为 $k$ 的子序列，因此第一个的下标不能超过 $(n - k + 1)$，即第一个数为 $[1, n - k + 1]$ 的最大值。推而广之，第 $i(i>1)$ 个数应该是 $[b_i + 1, n - k + i]$ 的最大值。这很明显是一个滑动窗口解决的问题。

注意：通常我们滑动窗口求最大是用“队尾元素小于等于加入元素”以此判断出队尾条件。但是这题不一样。对于多个最大值情况，我们会选择下标最小的。因此这个时候队尾与新加入元素相等，队尾仍在决策集合中，应当保留。因此这里的出队条件是“严格小于”。

```cpp
void INIT() {
	qk = inicjuj();
	int n = 1;
	while(1) {
		a[n] = wczytaj();
		if(!a[n]) {
			n--;
			break;
		}
		else n++; 
	}
	
	for(int i = 1; i <= n - qk + 1; i++) {
		while(fr <= tl && a[que[tl]] < a[i]) tl--;
		que[++tl] = i;
	}
	int lim = que[fr];
	wypisz(a[que[fr]]); fr++;
	for(int i = n - qk + 2; i <= n; i++) {
		while(fr <= tl && que[fr] < lim) fr++;
		while(fr <= tl && a[que[tl]] < a[i]) tl--;
		que[++tl] = i;
		lim = que[fr];
		wypisz(a[que[fr]]);
		fr++;
	}
}
```

---

