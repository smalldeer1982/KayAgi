# PASTE

## 题目描述

我们用文本处理器来处理一个特殊的文本文件，该文本文件共有 $N$ 行文本，每一行文本仅包含一个自然数，第一行为 $1$、第二行为 $2$，以此类推至 $N$ 行为自然数 $N$。

假设对该文本文件执行一次“剪切和粘贴”操作含义如下：首先选定连续的若干行文本，“剪切”操作将选定的文本从文件中剪下，而“粘贴”操作将剪切下来的文本插入到文件中的其他地方。

编写一个程序求出在进行了连续若干次“剪切和粘贴”操作后，文本文件中前十行的内容。


## 样例 #1

### 输入

```
13 3
6 12 1
2 9 0
10 13 8
```

### 输出

```
6
7
8
9
10
11
12
2
3
4```

# 题解

## 作者：fanhy (赞：19)

谁说$O(N*K)$算法要靠$RP$的

这题模拟才不到**300ms**，稳稳的

将一段文本剪切下来粘到另一段文本后面，相当于将这两段文本交换

使用temp数组记录下剪切下的文本，将另一段文本向前（插入行在原文本第一行之后）或向后（插入行在原文本第一行之前）。

将temp数组里的数赋值到该黏贴的位置就可以了。

AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
int n, k;
int doc[MAXN], temp[MAXN];
int cnt;

int main()
{
    for (int i = 1; i < MAXN; i++) doc[i] = i;
    cin >> n >> k;
    for (int oper = 0; oper < k; oper++)
    {
        int s, t, p1, p2, ins, len;
        cin >> s >> t >> ins;
        len = t - s + 1;
        p1 = ins + 1;
        p2 = p1 + len - 1;
        cnt = 0;
        for (int i = s; i <= t; i++) temp[++cnt] = doc[i];
        if (ins < s) for (int i = s - 1; i >= p1; i--) doc[i + len] = doc[i];
        else for (int i = t + 1; i <= p2; i++) doc[i - len] = doc[i];
        for (int i = p2; i >= p1; i--) doc[i] = temp[cnt--];
    }
    for (int i = 1; i <= 10; i++) cout << doc[i] << endl;
    return 0;
}
```

---

## 作者：囧仙 (赞：9)

## 题目大意

有 $n$ 个数 $1,2,\cdots n$ 。 $m$ 次操作。每次取出 $[A_i,B_i]$ 段，删除后插入第 $C_i$ 个位置后面。输出操作结束后前 $10$ 个数字。

## 题解

观察到题目只要我们输出前 $10$ 个数字，所以其他地方是什么数字不需要在意。

考虑到题目给出的操作形式比较难以处理，我们转换成 $(S_i,T_i,L_i)$ ，表示第 $i$ 个操作将 $[S_i,S_i+L_i)$ 移动到了 $[T_i,T_i+L_i)$ 。

观察到，操作 $(S_i,T_i,L_i)$ 是可逆的，其逆操作为 $(T_i,S_i,L_i)$ 。于是，我们可以将 $m$ 个操作倒过来做，反推出第 $i (i\in[1,10])$ 个地方原先是哪个地方的数字。分类讨论每个逆操作对当前位置 $t$ 的影响。

- 如果逆操作移动的区间包含了当前的 $t$ ，则令 $t\gets t+T_j-S_j$ 。

- 如果逆操作在 $t$ 之前，且这段区间移动后到了 $t$ 的后面，则令 $t\gets t-L_j$ 。

- 如果逆操作在 $t$ 之后，且这段区间移动后到了 $t$ 的前面，则令 $t\gets t+L_j$ 。

最后我们就能反推出 $t$ 原先在哪。由题意可得初始时第 $i$ 个位置放了 $i$ 。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =1e3+3;
int n,m,S[MAXN],T[MAXN],L[MAXN];
int main(){
    n=qread(),m=qread(); up(1,m,i){
        int a=qread(),b=qread(),c=qread();
        L[i]=b-a+1,S[i]=c+1,T[i]=a;
    }
    up(1,10,i){
        int t=i; dn(m,1,j){
            if(S[j]<=t&&t<=S[j]+L[j]-1) t+=T[j]-S[j]; else
            if(S[j]> t&&T[j]<=t) t+=L[j]; else
            if(S[j]< t&&t-L[j]<T[j]) t-=L[j];
        }
        printf("%d\n",t);
    }
    return 0;
}
```

复杂度 $\mathcal O(k\times m)$ ，其中 $k$ 为要求我们输出的数字的个数，该题中为 $10$ 。

---

## 作者：Mysterious_Mini (赞：7)

这是本蒟蒻的第 $5$ 篇题解。
### 思路：
$\texttt{STL}$ 大法好！

看到题目中的“剪切”，“粘贴”等词语，我立即想到了 `vector`。

在之前的题解中我已简单介绍了 `vector` 的操作：戳[这里](https://www.luogu.com.cn/problem/solution/CF990B)。

这篇题解会补充一下本题会用到的操作：

`assign(const_iterator first,const_iterator last)` ： 将操作向量中的 `[first,last)` 下标元素设置成当前向量元素。

`erase(iterator first,iterator last)` ： 删除向量中下标为 `[first,last)` 的元素。

`insert(iterator it,const_iterator first,const_iterator last)` ： 向量中迭代器指向元素前插入另一个相同类型向量的 `[first,last)` 间的数据。

`clear()` ： 清空向量。

了解了这些，你离 $\texttt{AC}$ 仅有一步之遥啦！
### 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector <int> txt, ctrlv; //皮一下：ctrl+v 是粘贴指令，所以我把剪切内容存在 ctrlv 里
int n, k, a, b, c;
int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        txt.push_back(i); //把1到n都插入向量（文本初始化）
    for(int i = 1; i <= k; i++)
    {
        cin >> a >> b >> c;
        ctrlv.assign(txt.begin() + a - 1, txt.begin() + b);
        txt.erase(txt.begin() + a - 1, txt.begin() + b);
        txt.insert(txt.begin() + c, ctrlv.begin(), ctrlv.end());
        ctrlv.clear(); //帅气的 vector 操作
    }
    for(int i = 0; i <= 9; i++)
        cout << txt[i] << endl; //输出，注意下标为0至9
    
    return 0;
}
```
完结撒花，[AC](https://www.luogu.com.cn/record/49895786)！

祝大家期中考试 $\texttt{RP++}$！

---

## 作者：Dlsksmilerrr_ (赞：7)

### ~~这题是蓝题？~~ 这作为蓝题~~数据也太水了~~

看某些大佬用链表和RP做，~~感觉太麻烦了~~

我用vector~~竟然莫名其妙的A了~~

其实这道题用一些~~简单的~~vector函数做就行了

首先开两个```vector```，一个存文本，一个存粘贴板

接下来分别用```assign()```，```erase()```，```insert()```
三个vector函数操作就~~完美的~~完成了这道题

## 下面是一个蒟蒻的18行vector代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,A,B,C;
vector <int> text;
vector <int> paster;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)text.push_back(i);
	for(int i=1;i<=k;i++){
		cin>>A>>B>>C;
		paster.assign(text.begin()+A-1,text.begin()+B);//把A到B这一段复制到粘贴板 
		text.erase(text.begin()+A-1,text.begin()+B);//删掉A到B这一段 
		text.insert(text.begin()+C,paster.begin(),paster.end());//把粘贴板里的内容粘贴到C的位置 
		paster.clear();
	}
	for(int i=0;i<10;i++)cout<<text[i]<<endl;//输出前10行 
	return 0;
} 
```


---

## 作者：zc_li (赞：5)

##  此题解使用链表做法，不难理解。
## 思路:
1. 就是用链表将剪切部分前一行的指针指向剪切部分后一行；

2. 将粘贴的地方前一行的指针指向剪切部分最开始的那行；

3. 然后将剪切部分尾部那行的指针指向原本粘贴位置的前一行的后一行；

4. 最后再从第一行开始输出到第十行就可以了。
## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,a[100005],gdd,gddd,pd,ppd,ans1,ans2;
  //制造链表！
struct dd{
	int nr;
	int zh;
}zz[100005]; 
int main() {
	cin>>n>>m;
	zz[0].zh=1;
	for(int i=1;i<=n-1;i++){
		zz[i].nr=i;
		zz[i].zh=i+1;
    }
    zz[n].nr=n;
    zz[n].zh=0;
	for(int i=1;i<=m;i++){
		int q,z,h,jl1=0,jl2=0,jl3=0;
		cin>>q>>z>>h;
		int gx=zz[0].zh;
		if(h>=q) h+=z-q+1;
		for(int j=1;gx;j++){
            //这三个重要位置找到就记录下来！
			if(j==q-1) jl1=gx;
			if(j==z){
				jl2=gx;
				if(jl1&&jl3) break;
			}
			if(j==h){
				jl3=gx;
				if(jl1&&jl2) break;
			}
			gx=zz[gx].zh;
		}
        //指针指向改变
		int jjl=zz[jl1].zh;
		zz[jl1].zh=zz[jl2].zh;
		zz[jl2].zh=zz[jl3].zh;
		zz[jl3].zh=jjl;
	}
	int gt=zz[0].zh;
    //输出！
	for(int i=1;i<=9;i++){
		cout<<zz[gt].nr<<endl;
		gt=zz[gt].zh;
	}
    //最后一行不用换行，虽然换了也可以但是有些强迫呀
	cout<<zz[gt].nr;
	return 0;
}
```

---

## 作者：Youngsc (赞：4)

[Youngsc](https://youngscc.github.io/)  
$ O(n*k) $ 的算法是要靠RP的。   
我们考虑更高效的算法。 

** %%%楼下大佬写非旋treap，蒟蒻不会，只好写一发Splay了 **  
** 都是Splay的基本操作，不会的学一学就好了 **  
** 只需要记下每个点子树大小就行，第$x$行的话就查找排名第$x+1$的节点（因为有两个虚拟节点） **  
** 注意的就是那个输入的$c$是指剪切掉$a$到$b$之后的第$c$行 **  
** 平衡树一发莽过去,比较水，复杂度$O(k\ log^n)$,不用看RP **

## code with Splay

```cpp
# include <bits/stdc++.h>
# define R register
# define LL long long
# define N 100010
# define inf 2000101900
# define db double

using namespace std;

int n,ch[N][2],fa[N],rt,k,x,y,z,cnt,t[N];

template <typename T> inline void in(R T& a){
    R char c=getchar();R T x=0,f=1;
    while (!isdigit(c)){if (c == '-') f=-1; c=getchar();}
    while (isdigit(c)) x = (x<<1)+(x<<3)+c-'0', c=getchar();
    a = x*f;
}

inline int build(R int l,R int r){
    R int mid = l+r>>1;
    t[mid] = r-l+1;
    if (l < mid) fa[ch[mid][0] = build(l,mid-1)] = mid;
    if (r > mid) fa[ch[mid][1] = build(mid+1,r)] = mid;
    return mid;
}

inline bool get(R int x){return ch[fa[x]][1] == x;}

inline void up(R int x){t[x] = t[ch[x][0]]+t[ch[x][1]]+1;}

inline void rotate(R int x){
    R int f1 = fa[x],f2 = fa[f1];
    R bool pd = get(x);
    if (f2) ch[f2][get(f1)] = x;
    fa[x] = f2;
    ch[f1][pd] = ch[x][pd^1], fa[ch[f1][pd]] = f1;
    ch[x][pd^1] = f1, fa[f1] = x;
    up(f1),up(x);
}

inline void splay(R int x,R int k){
    while (fa[x] != k)
    {
        R int f1 = fa[x],f2 = fa[f1];
        if (f2 != k)
        {
            if ((ch[f1][1] == x)^(ch[f2][1] == f1)) rotate(x);
            else rotate(f1);
        }
        rotate(x);
    }
    if (!k) rt = x;
}

inline int ask_before(R int x){
    splay(x,0);
    x = ch[x][0];
    while (ch[x][1]) x = ch[x][1];
    return x;
}

inline int ask_after(R int x){
    splay(x,0);
    x = ch[x][1];
    while (ch[x][0]) x = ch[x][0];
    return x;
}

inline void print(R int x){
    if (ch[x][0]) print(ch[x][0]);
    if (x>1 && x<=n+1) printf("%d\n",x-1),cnt++;
    if (cnt == 10) exit(0);
    if (ch[x][1]) print(ch[x][1]);
}

inline int find(R int x){
    R int now = rt;
    while (x)
    {
        if (t[ch[now][0]] >= x) now = ch[now][0];
        else if (t[ch[now][0]] + 1 == x) return now;
        else x -= t[ch[now][0]]+1,now = ch[now][1];
    }
}

int main(){

    // freopen("cqoi15_query.in","r",stdin);
    // freopen("cqoi15_query.out","w",stdout);

    in(n),in(k);
    rt = build(1,n+2);
    for (R int i=1; i<=k; ++i)
    {
        in(x),in(y),in(z);
        x++,y++,z++; //虚拟节点
        x = find(x),y = find(y);
        R int a = ask_before(x),b = ask_after(y);
        splay(a,0),splay(b,a);
        R int now = ch[b][0];
        fa[now] = ch[b][0] = 0; up(b),up(rt);
        z = find(z);
        a = ask_after(z);
        splay(z,0); splay(a,z);
        fa[now] = a; ch[a][0] = now; up(a),up(rt);
    }
    print(rt);
    return 0;
}

```


---

## 作者：J_Ignite (赞：3)

## P1188 PASTE 题解
~~可以说是我做过的最水的一道蓝题了没有之一~~\
题意很清楚，就是剪切数列的一段，然后在插入到另一个地方。题解中还有平衡树做的，容我一拜，但是我只用`STL vector`就~~出乎意料的~~A了这道题 ~~竟然没T，真是奇了~~\
首先，介绍几个与本题相关的`vector`操作：(其中 `v` 是已生命的`vector<int>`变量）
- `v.push_back(i)` 将 i 加入序列尾部。
- `vector<int>::const_iterator` 生成一个常量迭代器。你可以认为就是对于序列中某一个元素的指针。
- `v.begin(),v.end()` 分别返回 `v` 指向第一个元素的迭代器和指向最后一个元素**的后一个元素**的迭代器。整个`v`的元素存放在 $[\ v.begin(),v.end()\ )$ 这个半开半闭区间内。

- `v.erase(vector<int>::const_iterator __first, vector<int>::const_iterator __last)` 删除掉 `__first` 和 `__last` 两个迭代器中间的数据（包括`__first`本身指向的数据,不包括`__last`指向的数据）。
- `v.insert(vector<int>::const_iterator __position, vector<int>::iterator __first, vector<int>::iterator __last)`  将 `__first` 和 `__last` 两个迭代器中间的数据（包括`__first`本身指向的数据,不包括`__last`指向的数据）插入到 `__position` 中。
- `vector<int> v(__first,__last)` 两个迭代器中间的数据（包括`__first`本身指向的数据,不包括`__last`指向的数据）创建一个新`vector`。
- 在迭代器上可以进行加减运算，比如说 `v.begin() + a` 表示的是首迭代器向后移 `a` 个元素后的迭代器，即 `v` 中的第 `a+1` 个元素。 

对于大部分操作，一定要注意“前闭后开”这个规则。\
知道了这些用法，根据题意模拟即可。小细节在代码注释里面。
## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100001;
int k, n;
vector<int> v;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        v.push_back(i);// 插入原有数据
    }
    while (k--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        vector<int>::const_iterator first = v.begin() + a - 1;
        vector<int>::const_iterator last = v.begin() + b;
        // 拷贝的是 [v[a] , v[b+1]) 中的元素
        vector<int> cut(first, last);// 注意要新建一个vector<int> 存储上面的区间数据
        v.erase(first, last);// 删除区间数据
        v.insert(v.begin() + c, cut.begin(), cut.end()); // 在指定位置插入
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", v[i]);// 输出
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
```

---

## 作者：Mysterious_Cat (赞：2)

### 题目思路 1：
使用 vector 暴力 $O(n \times k)$，这里放一下基本操作和代码。

```cpp
vector<int> v //int可以改成其他，v是变量名
v.begin() //返回首地址
v.end() //返回尾地址
v.push_back(int x) //在尾部加入元素x
v.insert(interator c, const int &x) //在迭代器指向元素c前插入x
v.insert(interator c, const_iterator first, const_iterator last) //在迭代器指向元素c前插入另一个相同类型向量的[first,last)间的数据
v.erase(iterator c) //删除向量中迭代器指向元素c
v.erase(iterator first,iterator last) //删除向量中[first,last)中元素
```

```cpp
scanf("%d %d %d", &a, &b, &c);
vector<int> tmp;
tmp.assign(tex.begin() + a - 1, tex.begin() + b);
tex.erase(tex.begin() + a - 1, tex.begin() + b);
tex.insert(tex.begin() + c, tmp.begin(), tmp.end());
```

### 题目思路 2：
答案只关心前$10$个数字，所以反向逆推。

对于每次操作，取出$[A_i,B_i]$移动至$[C_i,C_i+B_i-A_i]$，其逆操作为，取出$[C_i+1,C_i+B_i-A_i+1]$移动至$[A_i,B_i]$。

对于数$i$的位置$t$，每次逆操作影响为
$\begin{cases} {t \leftarrow t-C_i+A_i-1, C_i<t<C_i+B_i-A_i+2} \\ {t \leftarrow t-B_i+A_i-1,C_i+1<t<B_i+1} \\ {t \leftarrow t+B_i-A_i+1,A_i \le t \le C_i} \end{cases}$

最后输出$t$即可


---

## 作者：zpf_13516358919 (赞：2)

```cpp
//O(nk)的算法是要靠RP的
//我们考虑更高效的算法
//因为只输出前十个数,我们考虑能不能把前十个数倒着操作,
//找到其在初始序列中的位置
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define in(x) read(x)
#define LL long long
const int maxn=1010;
const LL INF=(LL)1<<60;
LL Min(LL a,LL b){ return a<b ? a : b ;}
using namespace std;
LL n,k,A[maxn],B[maxn],C[maxn],L,R,now,dis;
void read(LL &x)
{
    LL _re=0,_ch=1; char _c=getchar();
    while (_c<'0'|| _c>'9') { if(_c=='-')_ch=-1; _c=getchar();}
    while ( _c>='0'&&_c<='9') _re=_re*10+_c-'0', _c=getchar();
    x=_re*_ch;
}
void put(LL x)
{
    if(x<0) putchar('-') ,x=-x;
    if(x>9)put(x/10);
    putchar(x%10+48);
}
int main()
{
    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    in(n); in(k);
    for(int i=1;i<=k;i++) in(A[i]),in(B[i]),in(C[i]);
    for(int i=1;i<=10;i++)
    {
        now=i; //now代表数在目前序列中的位置
        for(int j=k;j>=1;j--)
        {
            L=min(A[j],B[j]);
            R=max(A[j],B[j]);//取出区间左右端点
            dis=L-(C[j]+1);//算出偏移量
            if(n-(R-L+1)<C[j])continue;
            L-=dis; R-=dis;//算出要移动的序列在现在数列中的位置
            if(now>=L&&now<=R)now+=dis;
                        //数的位置在要移动的区间里,就跟着一起移动
            else if(now<L)
            {
                //如果数的位置在移动序列的左边
                               //取出序列后数的位置是不移动的
                                  if(Min(A[j],B[j])-1<now)now+=(R-L+1);
                                //序列插入的位置在数的左边,那么数的位置要右移区间长度个单位
            }
            else if(now>R)
            {
                //如果数的位置在移动序列的右边
                                 //取出序列后数将会左移区间长度个单位
                                 if(Min(A[j],B[j])-1>=now-(R-L+1))now-=(R-L+1);
                                 //如果序列又插入到数移动后的位置的左边,那么数又移动回去
                                 //只有序列插入到右边,数的移动才成立
            }
        }
                //算出数倒序移动k次后在原序列中的位置,就是原数
        put(now),putchar(10);
    }
    fclose(stdin);fclose(stdout);
    return 0;
}

```

---

## 作者：SunsetSamsara (赞：1)

看到这题大家基本用的都是 C++,来用 C 写一发

这题其实数据过水,有些人(像我)打的大模拟都能在 $300ms$ 内跑完,没加快读也根本没被卡。

假如用 C 语言写的话，没有 `vector` 坑就会多很多，

比如在删除粘贴内容、给粘贴内容留空间时前移/后移序列时，要注意前移是正着枚举，后移是反着枚举。~~在这个坑上我跳了 $4$ 遍,每次都没找到 bug。~~

接下来是我的~~大模拟~~代码环节!

```cpp
#include<stdio.h>
int arr[100001];
int paste[100001];
int N,K;
int main(){
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;++i){
		arr[i]=i;
		//初始化不能漏,不然输出会全是0 
	}
	int A,B,C;//操作参数 
	int len;//剪贴长度 
	for(int i=1;i<=K;++i){
		scanf("%d%d%d",&A,&B,&C);
		len=B-A+1;
		for(int i=A,j=1;i<=B;++i,++j){//j表示在剪贴板上哪个位置
			paste[j]=arr[i];
			//复制数组 
		}
		for(int i=A;i+len<=N;++i)
			arr[i]=arr[i+len];//别忘了前移
		for(int i=N;i>=C+len+1;--i)//注意得倒着枚举 
			arr[i]=arr[i-len];//再给剪贴板腾空间
		for(int i=C+1,j=1;j<=len;++i,++j)
			arr[i]=paste[j];//粘贴上去
	} 
	for(int i=1;i<=10;++i)
		printf("%d\n",arr[i]); 
}
```

---

## 作者：七碳烷烃 (赞：1)

## 这道题可以直接用链表来做
注：这篇题解中的链表是用**指针**实现的，理解起来可能比较有难度。
### 题意简述
这道题会给出$K$次操作，每次给出一个剪贴开头和结尾，再给出一个插入的位置。  
题面不难理解，只需要注意插入的位置是在**取出要剪切的的那一段之后的位置**。
### 题目分析
链表插入和删除都非常快，查询链表中某一元素位置的平均复杂度为$O(N)$，而知道位置后，插入和删除的时间复杂度都为$O(1)$，因此我们可以考虑用链表来实现。总的时间复杂度为$O(N*K)$。在这道题的数据规模上**完全没问题**。
  
我们首先找到第$A$行和第$B$行的指针，将第$A$行到第$B$行这一段从链表中“摘出来”，之后再找到第$C$行的指针，在第$C$行之后插入即可。  

需要注意的是，由于存在插入到第$0$行的可能性，因此我们需要定义一个排在链表头的"head"元素，查询第$0$个元素时就返回它的指针。
  
定义一个元素结构体，构造函数等已略去。
```cpp
template <typename T>
struct element{
	T object;
	element<T> *prev;
	element<T> *next;
};
```
之后我们需要给出双向链表的实现，具体代码请看完整代码部分，这里给出最核心的剪贴代码。其中``ch``为我们定义的链表类型的变量，``getPointer()``为获取某一个元素的指针的函数。
```cpp
for(int i = 1; i <= m; i++) {
   int l, r, p; // 分别代表输入的A B C
   scanf("%d%d%d", &l, &r, &p);
   element<int> *pl, *pr, *pp;
   pl = ch.getPointer(l);
   pr = ch.getPointer(r);
   // 获取要剪切的两端的指针
   pl->prev->next = pr->next;
   pr->next->prev = pl->prev;
   // 从链表中删除
   pp = ch.getPointer(p);
   pl->prev = pp;
   pr->next = pp->next;
   pp->next->prev = pr;
   pp->next = pl;
   // 将剪切出来的那一段插入到c行后面
}
```
### 完整代码
```cpp
/* Headers */
#include <cstdio>
#include <iostream>
using namespace std;
/* Type and variables */
int n, m;

template <typename T>
struct element{
    T object;
    element<T> *prev;
    element<T> *next;
    element() {f
        object = 0;        
    }
    element(T value) {
        object = value;        
    }
    element(T value, element<T>* prev, element<T>* next) {
        object = value;
        this->prev = prev;
        this->next = next;    
    }
};
template <typename T> // 模板类
class chain{
    int eleCount; // 已有元素数量
    element<T> *head;
    element<T> *tail;
public:
    chain(){ // 链表的构造函数，首先构造一个头部元素
        eleCount = 0;
        head = new element<T>(0);
        tail = head;
        head->prev = head;
        head->next = head;
    }
    element<T>* getPointer(int pos) { // 获取排列在第pos位的元素的指针
        element<T> *p = head;
        for(int i = 1; i <= pos; i++) {
            p = p->next;
        }
        return p;
    }
    void addElement(T value) { // 在尾部添加一个元素
        eleCount++;
        element<T> *p = new element<T>(value, tail, tail->next);
        p->prev->next = p;
        p->next->prev = p;
        tail = p;
    }
    void print(int c) { // 输出链表中除头部元素外的前c个元素
        element<T> *p = head;
        for(int i = 1; i <= c; i++) {
            p = p->next;
            cout << p->object;
            putchar('\n');
        }
    }
};
chain<int> ch = chain<int>();
/* Functions */
/* Main */
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        ch.addElement(i);
    for(int i = 1; i <= m; i++) {
        int l, r, p;
        scanf("%d%d%d", &l, &r, &p);
        element<int> *pl, *pr, *pp;
        pl = ch.getPointer(l);
        pr = ch.getPointer(r);
        // 获取这一段两边的指针
        pl->prev->next = pr->next;
        pr->next->prev = pl->prev;
        // 将这一段从链表中移除
        pp = ch.getPointer(p);
        // 获取移除后要粘贴的位置的指针
        pl->prev = pp;
        pr->next = pp->next;
        pp->next->prev = pr;
        pp->next = pl;
        // 再把这一段插入到要粘贴的位置后面
    }
    ch.print(10); // 最后输出即可 >w<
    return 0;
}
```
227ms

---

## 作者：king_xbz (赞：1)

看到好像没有用栈写这道题的？听说$O（n*k）$过不了？我还真不信这个邪！于是历时进1h，我终于用栈+模拟的方法A了这道题。

首先我们可以开一个数组a[]来储存该文本，注意，由于我们需要额外$B−A+1$的空间来作为“剪切板”暂存剪下来的内容，这里需要开2倍数组大小，不然会RE。
```cpp
for(fint i=1;i<=2*n;i++)
	a[i]=i;//初始化文本
```
接下来，我们用一个栈q来存储剪下来的部分，其大小即为$B−A+1$。并分向前和向后两类进行讨论，将原位的元素前移/后移

最后将栈q中的元素依次弹出补上上一步腾出来的空位

这一部分的具体代码实现如下：
```cpp
for(fint i=1;i<=k;i++)
{
	x=read(),y=read(),z=read();
	int turn=y-x+1,start=z+1,to_end=y+1,end=z+turn,to_start=x-1;  
   //设置前移后移的位置	
   for(fint j=x;j<=y;j++)
	q.push(a[j]);//剪切
	if(z>=x)
	for(fint j=to_end;j<=end;j++)
	a[j-turn]=a[j];
	for(fint j=to_start;j>=start;j--)
	a[j+turn]=a[j];//移动位置
	for(fint j=end;j>=start;j--) 
	a[j]=q.top(),q.pop();//弹出完成粘贴补位
	while(!q.empty())
	q.pop();//用完清空好习惯（其实这里不清空也行）
}
```
最后上完整代码[点我获取](https://www.luogu.com.cn/paste/96i2mo00)

排版已使用LaTeX完善，求管理大大给过。祝大家AC愉快。

---

## 作者：MloVtry (赞：0)

$O(n*k)$的算法是要靠RP的。

我们考虑更高效的算法。

因为只输出前十个数,我们考虑能不能把前十个数倒着操作,找到其在初始序列中的位置。

但是我太懒了，懒得动这个脑子。

本质上是一段区间的移动，平衡树莽过去就行了，$O(nlog_n)$，不用看RP。

代码（非旋Treap）
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
struct node
{
	int key,fhq;
	int l,r,siz;
	void anode(int it)
	{
		key=it;fhq=rand();
		l=r=0;siz=1;
	}
}tre[N];
void update(int now)
{
	tre[now].siz=tre[tre[now].l].siz+tre[tre[now].r].siz+1;
}
void split(int now,int k,int &x,int &y)
{
	if(!now)
	{
		x=y=0;return;
	}
	if(tre[tre[now].l].siz>=k)
		y=now,split(tre[now].l,k,x,tre[now].l);
	else x=now,split(tre[now].r,k-tre[tre[now].l].siz-1,tre[now].r,y);
	update(now);
}

int merage(int x,int y)
{
	if(x*y==0) return x+y;
	if(tre[x].fhq<tre[y].fhq)
	{
		tre[x].r=merage(tre[x].r,y);
		update(x);return x;
	}
	else
	{
		tre[y].l=merage(x,tre[y].l);
		update(y);return y;
	}
}
int n,m,rot;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) tre[i].anode(i),rot=merage(rot,i);
	
	while(m--)
	{
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		int x=0,y=0,z=0;
		split(rot,b,x,z);
		split(x,a-1,x,y);
		x=merage(x,z);
		split(x,c,x,z);
		rot=merage(x,merage(y,z));
	}
	int x=0,y=0,T=10;
	split(rot,T,x,y);
	while(T--)
	{
		split(x,1,y,x);
		printf("%d\n",tre[y].key);
	}
	return 0;
}
```

---

