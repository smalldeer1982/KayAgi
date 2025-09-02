# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 样例 #1

### 输入

```
2\n1\n3 ```

### 输出

```
16```

# 题解

## 作者：FlashHu (赞：22)

这题推式子恶心。。。。。

考虑分治，每次统计跨过$mid$的所有区间的答案和。$i$从$mid-1$到$l$枚举，统计以$i$为左端点的所有区间。

我们先维护好$[i,mid]$区间内最小值$mn$和最大值$mx$。我们可以想到，对于某一个左端点，它的右端点$j$在一定的范围内，最小值和最大值都不会变。这里就看到一些可以重复利用并快速计算的信息了。

维护两个指针$p,q$，分别表示$[mid+1,r]$内元素值第一个小于$mn/$大于$mx$的位置，那么$\sum\limits_{j=mid+1}^rans[i,j]$就可以分成三类讨论。暂时假设$p<q$。

$j\in[mid+1,p-1]$时，区间的最值不变，都是$mn,mx$，直接高斯求和

$$ans\leftarrow mn\cdot mx\sum\limits_{j=mid+1}^{p-1}j-i+1$$

$j\in[p,q-1]$时，区间最大值不变，但最小值取的是$[mid+1,j]$里的了。预处理$mid+1$到$r$的前缀最小值$min_j$，同时记录$min_j$和$min_j\cdot j$的前缀和（$p\ge q$同理）

$$ans\leftarrow mx\sum\limits_{j=p}^{q-1}min_j(j-i+1)$$

$$ans\leftarrow mx\sum\limits_{j=p}^{q-1}min_j\cdot j+mx(1-i)\sum\limits_{j=p}^{q-1}min_j$$

$j\in[q,r]$时，最值和$mn,mx$无关了，记录$min_jmax_j$和$min_jmax_j\cdot j$的前缀和

$$ans\leftarrow \sum\limits_{j=q}^rmin_jmax_j(j-i+1)$$

$$ans\leftarrow \sum\limits_{j=q}^rmin_jmax_j\cdot j+(1-i)\sum\limits_{j=q}^rmin_jmax_j$$

容易发现$mn,mx,p,q$都是单调移动的，那么就大功告成啦！

```cpp
#include<bits/stdc++.h>
#define LL long long
#define RG register
#define R RG LL//常数大也无所谓了
#define G if(++ip==ie)fread(ip=buf,1,N,stdin)
#define A(V) (ans+=V)%=YL
using namespace std;
const LL N=1<<19,YL=1e9;
char buf[N],*ie=buf+N,*ip=ie-1;
LL ans,a[N],mns[N],mxs[N],mnj[N],mxj[N],mms[N],mmj[N];
inline LL in(){
    G;while(*ip<'-')G;
    R x=*ip&15;G;
    while(*ip>'-'){x*=10;x+=*ip&15;G;}
    return x;
}
inline LL S(R l,R r){//高斯求和
    return (l+r)*(r-l+1)/2%YL;
}
void solve(R l,R r){
    if(l==r){A(a[l]*a[l]);return;}
    R m=(l+r)>>1,i,j,p,q,mn=YL,mx=0;
    solve(l,m);solve(m+1,r);
    mns[m]=mxs[m]=mnj[m]=mxj[m]=mms[m]=mmj[m]=0;
    for(j=m+1;j<=r;++j){//预处理，变量名不解释
        mn=min(mn,a[j]);mx=max(mx,a[j]);
        mns[j]=(mns[j-1]+mn)%YL;
        mxs[j]=(mxs[j-1]+mx)%YL;
        mnj[j]=(mnj[j-1]+mn*j)%YL;
        mxj[j]=(mxj[j-1]+mx*j)%YL;
        mms[j]=(mms[j-1]+mn*mx)%YL;
        mmj[j]=(mmj[j-1]+mn*mx%YL*j)%YL;
    }
    mn=YL;mx=0;
    for(p=q=m+1,i=m;i>=l;--i){//计算答案
        mn=min(mn,a[i]);mx=max(mx,a[i]);
        while(p<=r&&mn<a[p])++p;//单调移动
        while(q<=r&&mx>a[q])++q;
        if(p<q){
            A(mn*mx%YL*S(m-i+2,p-i));//注意做减法的都要加一下模数
            A(mx*(mnj[q-1]-mnj[p-1]+YL)+mx*(mns[q-1]-mns[p-1]+YL)%YL*(1-i+YL));
            A(mmj[r]-mmj[q-1]+(mms[r]-mms[q-1]+YL)*(1-i+YL));
        }
        else{
            A(mn*mx%YL*S(m-i+2,q-i));
            A(mn*(mxj[p-1]-mxj[q-1]+YL)+mn*(mxs[p-1]-mxs[q-1]+YL)%YL*(1-i+YL));
            A(mmj[r]-mmj[p-1]+(mms[r]-mms[p-1]+YL)*(1-i+YL));
        }
    }
}
int main(){
    R n=in();
    for(R i=1;i<=n;++i)a[i]=in();
    solve(1,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Mirach (赞：10)

[老年选手的博客](https://www.cnblogs.com/penth/p/10624801.html)

Problem
------

[SPOJ-NORMA2](https://www.spoj.com/problems/NORMA2/) & [bzoj3745](https://www.lydsy.com/JudgeOnline/problem.php?id=3745)

题意概要：给定一个正整数序列 $\{a_i\}$，求

$$\sum_{i=1}^n\sum_{j=i}^n(j-i+1)\min(a_i,a_{i+1},\cdots,a_j)\max(a_i,a_{i+1},\cdots a_j)$$

$n\leq 5\times 10^5$

Solution
------

这题正解是一个完美的 $O(n\log n)$ 分治，但比较麻烦，鉴于这个分治做法已经漫天飞了，所以这里不讲那个算法

我在考场上在最后二十分钟想到了并打出了另一个分治做法，非常很好写跑得也很快，最终可以 AC

可以考虑对于一个序列 $\{a_i\}$，找到其最大值 $mx$ 与最小值 $mi$，有大量区间都是以这两点为最值点的，而同时这些区间的左右端点分别都是连续的，所以可以考虑将这些区间一起计算

具体的，若找到的最大值与最小值分别在 $p_1,p_2$ 取到（不妨设 $p_1\leq p_2$），则以这两者为最值点的区间 $[l,r]$ 满足 $1\leq l\leq p_1,p_2\leq r\leq n$，这些区间的长度和可以 $O(1)$ 算出，也即可以 $O(1)$ 算出这些区间的贡献

进一步的，需要加上其他不是 **同时以这两者为最值点** 的区间贡献。设统计左右端点都在 $[l,r]$ 内的区间贡献也即刚刚这一步处理为函数 $f(l,r)$，则其他区间的贡献即 $f(l,p_2-1)+f(p_1+1,r)-f(p_1+1,p_2-1)$（由于前面两个式子中重复计算了左右端点都在 $[p_1+1,p_2-1]$ 内的区间贡献，所以需要第三个函数去减去这部分多余的贡献）

所以现在可以得到一个基本的做法（统计 $[l,r]$ 区间）：

- $O(1)$ 找到区间最大最小值所在位置 $p_1,p_2(p_1\leq p_2)$
- $O(1)$ 统计左端点在 $[l,p_1]$、右端点在 $[p_2,r]$ 的区间的贡献
- 分治统计区间 $[l,p_2-1],[p_1+1,r]$，并减去 $[p_1+1,p_2-1]$ 的答案

这个做法慢成龟龟，然后我灵机一动：分治下去的区间不是会继续使用当前最值点为最值点吗？（即 $[l,p_2-1]$ 会使用 $p_1$ 为最值点，进而可能再次调用区间 $[p_1+1,p_2-1]$，这里的统计就冗余了，如果加个记忆化那么原来每次分出三个区间就可以均摊成两个了……）

然后就加了一下 $map$ 的记忆化，极限数据只需要 $0.4s$

之前证了一波伪的复杂度 $O(n\log n)$，后来被同校 dalao 精心卡掉了 ~~虽然构造了一个多小时~~

实际上复杂度是 $O(n^2\log n)$ 的，那个 $\log$ 还是 $map$ 的复杂度 ~~没错这是个暴力，但很难卡满，在考试中、spoj和bzoj上都没能卡掉我♪(^∇^*)~~

实际运行效率很高，未经st表优化的代码在bzoj上跑到 $\mathrm{rank6}$，比我写的正解快一倍，同时代码也很短很好写 ~~毕竟是在十分钟内写完调完的~~，只有 $\mathrm{1.2k}$

Code
-------

由于想到这个解法时时间紧迫，没来得及写 $st$ 表做 $\mathrm{rmq}$ ~~但还是过掉了~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename _tp> inline _tp read(_tp&x){
    char c11=getchar(),ob=0;x=0;
    while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
    while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=501000,p=1e9,inf=0x3f3f3f3f;
int a[N],n;

map <int,int> mp[N];

inline int getsum(int l,int r){return 1ll*(l+r)*(r-l+1)/2%p;}
inline int qm(int x){while(x<0)x+=p;while(x>=p)x-=p;return x;}

int force(int l,int r){
    int res(0);
    for(int i=l;i<=r;++i){
        int mx=-inf,mi=inf;
        for(int j=i;j<=r;++j){
            mx=max(mx,a[j]);
            mi=min(mi,a[j]);
            res=qm(res+1ll*(j-i+1)*mi%p*mx%p);
        }
    }return res;
}

int solve(int l,int r){
    if(l>r)return 0;
    if(mp[l].find(r)!=mp[l].end())
        return mp[l][r];
    if(r-l<=10)
        return mp[l][r]=force(l,r);
    int mx=-inf,mxd;
    int mi=inf,mid;
    for(int i=l;i<=r;++i){
        if(a[i]>mx)mx=a[i],mxd=i;
        if(a[i]<mi)mi=a[i],mid=i;
    }
    int L=min(mxd,mid),dl=L-l+1;
    int R=max(mxd,mid),dr=r-R+1;
    int dx=R-L-1,res(0);
    if(dl>dr)swap(dl,dr);
    for(int i=1;i<=dl;++i)
        res=qm(res+getsum(i+dx+1,i+dx+dr));
    res=1ll*res*mx%p*mi%p;
    return mp[l][r]=qm(res+qm(solve(l,R-1)+solve(L+1,r))-solve(L+1,R-1));
}

int main(){
    read(n);
    for(int i=1;i<=n;++i)read(a[i]);
    printf("%d\n",solve(1,n));
    return 0;
}
```

---

## 作者：辰星凌 (赞：4)

# **【题解】Norma [COCI2014] [SP22343]**

[广告](https://www.cnblogs.com/Xing-Ling/p/11771658.html)

**传送门：[$\text{Norma [COCI2014]}$](https://www.luogu.org/problem/SP22343) [$\text{[SP22343]}$](https://www.luogu.org/jump/spoj/22343)**

## **【题目描述】**

给定一个整数 $n$ 和一个长度为 $n$ 的序列 $a$，子序列是指原序列中一段连续的序列。子序列的价值定义为它们中的**最小值**乘以**最大值**再乘以**该子序列长度** 。现要计算所有子序列的价值之和，答案对 $1e9$ 取模。

-------

## **【分析】**

询问过于奇葩，万能的线段树都没法搞，单调队列也许可做，但太复杂了。

可以用类似 $\text{CDQ}$ 的思想递归分治：将一段区间分为左右两半，计算其中一半对另一半的贡献，得到另一半的答案。

对于一个区间 $[L,R]$，求出其中穿过了 $a[mid]$ 的所有子序列价值总和，然后再递归求解 $[L,mid]$ 以及 $[mid\!+\!1,R]$，可以保证子序列的计算一定不重不漏。

考虑处理一个区间 $[L,R]$ ，先枚举 $i \in [L,mid]$ 固定左端点，求出以每个 $i$ 作为左端点的所有子序列贡献和。

对于每个 $i$：

用 $mi,mx$ 分别表示 $min \{ a[i] \cdots a[mid] \}$ 和 $max \{ a[i] \cdots a[mid] \}$

设两个指针 $j,k$，    
$j$ 表示满足 $mi \leqslant min \{ a[mid\!+\!1] \cdots a[j] \}$ 的最大的 $j$ 的位置，  
$k$ 表示满足 $mx \geqslant max \{ a[mid\!+\!1] \cdots a[k] \}$ 的最大的 $k$ 的位置。

设 $w_{1}=min\{j,k\},w_{2}=max\{j,k\}$，此时右半部分被分成了三个部分，分别对其求解。

$(1).$ **完全满足** $mi,mx$ **的部分：** $[mid\!+\!1,w_{1}]$  

可知这一整段的元素数值范围都在 $[mi,mx]$ 以内，因此右端点在取 $[mid\!+\!1,w_{1}]$ 中的任意一个位置时，子序列最小值都始终为 $mi$，最大值也始终为 $mx$，至于区间长度，直接套等差数列公式就好了，小学数学不再赘述（这玩意儿有个很高大上的名字：[高斯求和](https://baike.baidu.com/item/%E9%AB%98%E6%96%AF%E6%B1%82%E5%92%8C/7487795?fr=aladdin)）。

**第** $1$ **部分对左端点** $i$ **的总贡献可表示为：** $ans_{1}[i]=mi*mx*\frac{(((mid\!+\!1)\!-i\!+\!1)+(w1\!-\!i\!+\!1))*(w1\!-\!(mid\!+\!1)\!+\!1)}{2}$ 。

$(2).$ **满足** $mi,mx$ **其一的部分：** $[w_{1}\!+\!1,w_{2}]$

这部分比较难想，在草稿纸上比划了好久才搞出来，而且还不太好描述。

分为 $j<k$ $($ 即 $w_{1}\!<\!k\!=\!w_{2})$ 和 $j>k$ $($ 即 $w_{1}\!<\!j\!=\!w_{2})$ 两种情况讨论。

以 $j<k$ 为例，此时要计算右端点 $[w_{1}\!+\!1,w_{2}]$ 对 $i$ 的贡献可以直接用 $mx$，但 $mi$ 不行，要用两个前缀和数组预处理一下这个东西。

由于子序列长度在不断的变化，但 $mid+1$ 是始终不变的，可以轻松处理出左端点为 $mid+1$ 的子序列贡献和，记为 $S_{1}$ 。再看左边部分没有计算的部分长度，对于每一个 $i$，它也是固定的 $(mid-i+1)$，于是还要用一个数组 $S'_{1}$ 记录每个前缀最小值的前缀和。

这个东西不太好描述，见下面的式子：

$S_{1}[x]$ $(mid\!+\!1\!\leqslant\!x\!\leqslant\!R)$ $=$ $\sum_{i=mid+1}^{x} ((i\!-\!(mid\!+\!1)\!+\!1)*max\{a[mid\!+\!1] \cdots a[i]\})$ 

$S'_{1}[x]$ $(mid\!+\!1\!\leqslant\!x\!\leqslant\!R)$ $=$ $\sum_{i=mid+1}^{x} max\{a[mid\!+\!1] \cdots a[i]\}$ 

该做法的正确性来自于：随着右端点的递增，$mid\!+\!1$ 到**右端点**的**前缀最大值单调不下降**，**最小值单调不上升**，所以可以直接用前缀和数组中的两个位置相减**得到一段的贡献**。

$j>k$ 的情况同理，预处理两个数组 $S_{2},S'_{2}$即可。

**第** $2$ **部分对左端点** $i$ **的总贡献可表示为：**  $ans_{2}[i]=\begin{cases}
mx*((S_{1}[k]\!-\!S_{1}[w1])+(mid\!-\!i\!+\!1)*(S'_{1}[k]\!-\!S'_{1}[w1]))&(j<k)\\
 mi*((S_{2}[j]\!-\!S_{2}[w1])+(mid\!-\!i\!+\!1)*(S'_{2}[j]\!-\!S'_{2}[w1]))&(k<j)
 \end{cases}$ 。


$(3).$ **完全不满足** $mi,mx$ **的部分：** $[w_{2}\!+\!1,R]$

其实只要 $(2)$ 搞了出来，$(3)$ 就没啥难度了，一样的处理方法，维护两个前缀和数组 $S_{3},S'_{3}$。

**第** $3$ **部分对左端点** $i$ **的总贡献可表示为：** $ans_{3}[i]=(S_{3}[R]\!-\!S_{3}[w2])+(mid\!-\!i\!+\!1)*(S'_{3}[R]\!-\!S'_{3}[w2])$ 。

**最后，注意取膜！！！开** $long$ $long$ **防止中间乘爆。**

时间复杂度为： $O(nlogn)$ 。

## **【Code】**

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#define LL long long
#define Re register LL
using namespace std;
const LL N=5e5+3,logN=19,P=1e9;
LL n,ans,a[N],S1[N],S2[N],S3[N],S1_[N],S2_[N],S3_[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void sakura(Re L,Re R){
    if(L==R){(ans+=a[L]*a[L]%P)%=P;return;}//这个特判必须要加
    if(L+1==R){(ans+=(a[L]*a[L]%P+a[R]*a[R]%P+a[L]*a[R]%P*2%P)%P)%=P;return;}//这里好像不用特判也可以QAQ
    Re mid=L+R>>1,mi=a[mid],mx=a[mid],i=mid,j=mid,k=mid;//注意j,k预处理为mid而不是mid+1
    Re MI=a[mid+1],MX=a[mid+1];//这里MI,MX和上面的mi,mx取inf,-inf也可以
    S1[mid]=S2[mid]=S3[mid]=S1_[mid]=S2_[mid]=S3_[mid]=0;//重置前缀和
    for(Re i=mid+1;i<=R;++i){
        MI=min(MI,a[i]),MX=max(MX,a[i]);//更新前缀最大值
        (S1[i]=S1[i-1]+MI*(i-(mid+1)+1)%P)%=P,(S1_[i]=S1_[i-1]+MI)%=P;//递推更新S1
        (S2[i]=S2[i-1]+MX*(i-(mid+1)+1)%P)%=P,(S2_[i]=S2_[i-1]+MX)%=P;//递推更新S2
        (S3[i]=S3[i-1]+MI*MX%P*(i-(mid+1)+1)%P)%=P,(S3_[i]=S3_[i-1]+MI*MX%P)%=P;//递推更新S3
    }
    while(i>=L){
        mi=min(mi,a[i]),mx=max(mx,a[i]);
        while(j<R&&a[j+1]>mi)++j;//移动MI指针j
        while(k<R&&a[k+1]<mx)++k;//移动MX指针k
        Re w1=min(j,k),w2=max(j,k);//获取三部分的两个分界点
        if(w1>mid)(ans+=mi*mx%P*((mid+1-i+1+w1-i+1)*(w1-(mid+1)+1)/2%P)%P)%=P;//完全满足的部分
        if(j>w1)//满足mi但不满足mx
            (ans+=mi*((S2[j]-S2[w1]+P)%P+(mid-i+1)*(S2_[j]-S2_[w1]+P)%P)%P)%=P;
        if(k>w1)//满足mx但不满足mi
            (ans+=mx*((S1[k]-S1[w1]+P)%P+(mid-i+1)*(S1_[k]-S1_[w1]+P)%P)%P)%=P;
        (ans+=((S3[R]-S3[w2]+P)%P+(mid-i+1)*(S3_[R]-S3_[w2]+P)%P)%P)%=P;//完全不满足的部分
        --i;//移动左指针
    }
    sakura(L,mid),sakura(mid+1,R);//递归搞下面
}
int main(){
//  freopen("norma.in","r",stdin);
//  freopen("norma.out","w",stdout);
    in(n);
    for(Re i=1;i<=n;++i)in(a[i]);
    sakura(1,n);
    printf("%lld\n",ans%P);
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}
```



---

## 作者：柠檬熟了 (赞：0)

**紫题买一赠一**  **[P6406 Norma](https://www.luogu.com.cn/problem/P6406)**

##

## 题意翻译

在给定的序列 $T[N]$ 中**任取两点**，记两点区间内 **最大值，最小值，区间长度** 的 **积** 为 $S$，求**所有**可能的 $S$ 的 **和**。

## 题目分析

先来分析要求的**时间复杂度**，本题中 $N= 5\times 10^5$，可以推断时间复杂度应当在 $O(N\log N)$ 以内。

于是我们充分发扬人类智慧，在这个时间复杂度基础上，可以想到分治的算法。

采用**二分**处理完两点**均在** 左半 或 右半 的情况，**剩余的情况**中必然一点选在左半区间，一点选在右半区间，**单次复杂度**在 $O(N)$ 级别。

仅需考虑剩余情况，

若是暴力选取，即**分别在左右区间枚举**选点，则**单次复杂度**为 $O(N^2)$，不合要求。

故想到须**预处理**右半内容，使得在**左半区间**内枚举时可以 $O(1)$ 得到**右半区间**的**贡献**。

（~~主要是我写的预处理右边，实际上处理左边似乎也行...？~~

## 具体实现

（~~万恶的表达式推导！~~

给定序列 $T[N]$，在左区间选点 $Lp$，右区间选点 $Rp$。

($S=\min \{ T[Lp] \cdots T[Rp] \}\times \max \{ T[Lp] \cdots  T[Rp] \}\times (Rp-Lp+1)$

定义**当前区间** 左边界 $L$，右边界 $R$，中项 $M=(L+R)/2$。

在左区间 $[L, M]$ 内**倒序**枚举 $Lp$，同时更新 $[T[Lp], T[M]]$ 内最小值 $Mi$，最大值 $Mx$。

在右区间 $[M+1, R]$ 中找到**最小的** $k$ 使得 $T[k]<Mi$，同时找到**最小的** $l$ 使得 $T[l]>Mx$。

易证随着 $Lp$ **递减**，$k, l$ 均成**单调递增**趋势，故**一次完整枚举**时间复杂度为 $O(N)$。


------------


**不妨设** $k \ge l$，于是显然**右区间**被分成 $[M+1, l), [l, k), [k, R]$ **三段**：

- 当 $Rp$ 落在 $[M+1, l)$ 中时，$[T[Lp],T[Rp]]$ 区间内**极值**即是 $Mi, Mx$。

  $$
  \because  \min \{ T[Lp]\cdots T[Rp] \}=Mi，\max \{ T[Lp] \cdots T[Rp] \}=Mx \\
  $$
  $$
  \therefore S=Mi\cdot Mx\cdot (Rp-Lp+1)\\
  $$
  $$
  \text 又\because Rp\in[M+1,l)\\
  $$
  $$
  \therefore \sum S=(Mi\cdot Mx)\cdot(\sum_{i=M+1}^{l-1}i-Lp+1)\\\\
  $$
  $$
  =(Mi\cdot Mx)\cdot [(M+1-Lp+1)+(l-1-Lp+1)]*(l-1-M-1+1) /2\\
  $$
  $$
  =(Mi\cdot Mx)\cdot (M+l-2\cdot Lp+2)\cdot (l-M-1)/2\\
  $$
  对于每次枚举，$M，Lp，l$ 均为定值，故可 $O(1)$ 求解贡献。

- 当 $Rp$ 落在 $[l, k)$ 中时，$[T[Lp],T[Rp]]$ 区间内最小值为 $Mi$，最大值在 $[l, Rp]$ 中。
  $$
  \because \min \{ T[Lp]\cdots T[Rp] \}=Mi，\max \{ T[Lp]\cdots  T[Rp] \}\in[l, Rp] \\
  $$
  $$
  \therefore S=Mi\cdot \max \{T[l] \cdots  T[Rp] \}\cdot (Rp-Lp+1)\\
  $$
  $$
  \text 记 \max \{T[l] \cdots  T[Rp] \}=MAX[Rp]\\
  $$
  $$
  \because Rp\in[l, k)\\
  $$
  $$
  \therefore \sum S=Mi\cdot\sum_{i=l}^{k-1} [MAX[i]\cdot (i-Lp+1)]\\
  $$
  $$
  =Mi\cdot\{\sum_{i=l}^{k-1} [MAX[i]\cdot (i+1)]-\sum_{i=l}^{k-1} (MAX[i]\cdot Lp)\}\\
  $$
  对于每次枚举，$Lp，l，k$ 为定值，且 $l，k\in[M+1, R]$

  故只需在枚举前维护两个前缀和，$\sum MAX[i]$，$\sum MAX[i]\cdot(i+1)$ 

  $i\in [M+1,R]$

  枚举时对应项代入式子即可 $O(1)$ 求解贡献。

  (当 $k \le l$ 时，上述 $\max$ 与 $\min$ 取反即可，并还需维护两个 $MIN$ 前缀和)

  

- 当 $Rp$ 落在 $[k, R]$ 中时，$[T[Lp],T[Rp]]$ 区间内最小值在 $[k, Rp]$ 中，最大值在 $[l, Rp]$ 中。

  $$
  \because \min \{ T[Lp]\cdots  T[Rp] \}\in[k, Rp]， max \{ T[Lp] \cdots T[Rp] \}\in[l, Rp] \\
  $$
  $$
  \therefore S=\min \{T[k] \cdots  T[Rp]\}\cdot \max \{T[l] \cdots  T[Rp] \}\cdot (Rp-Lp+1)\\
  $$
  $$
  \text 记 \max \{T[l] \cdots  T[Rp] \}=MAX[Rp]，\min \{ T[k] \cdots  T[Rp] \}=MIN[Rp]\\
  $$
  $$
  \because Rp\in[k, R]\\
  $$
  $$
  \therefore \sum S=\sum_{i=k}^{R} [MAX[i]\cdot MIN[i]\cdot(i-Lp+1)]\\
  $$
  $$
  =\sum_{i=k}^{R} [MAX[i]\cdot MIN[i]\cdot(i+1)]-\sum_{i=k}^{R} (MAX[i]\cdot MIN[i]\cdot Lp)\\
  $$
  对于每次枚举，$Lp，k，R$ 为定值，且 $k\in [M+1, R]$

  同理维护前缀和，$\sum MAX[i]\cdot MIN[i]\cdot (i+1)$，$\sum MAX[i]\cdot MIN[i]$

  枚举时对应项代入式子即可 $O(1)$ 求解贡献。


------------

将三段所得贡献**累加**，即得到确定 $Lp$ 且 $Rp \in [M+1, R]$ 时的贡献和，时间复杂度 $O(1)$。

枚举 $Lp \in [L, M]$ 并累加贡献即得答案。



## 玄学优化

- 递归到段长 $R-L \le 2$ 时可直接返回此段贡献。

  ```c++
  if (R==L) return T[L]*T[L];
  if (R==L+1) return T[L]*T[L]+T[R]*T[R]+T[L]*T[R]*2;
  ```


- 取模爆炸？难以调试？来试试 ```__int128``` 吧！

  将代码中**所有**使用的**计算数组**改为 ```__int128``` 类型，只需最后**输出答案**时取模即可！

    （空间可过，需要自己写输入输出函数。

## 代码

```cpp
#include <bits/stdc++.h>
#define MOD 1000000000
using namespace std;
__int128 a[500005];
__int128 sum1[500005], sum2[500005], sum3[500005], sum4[500005];
__int128 sum5[500005], sum6[500005];
__int128 ans=0;
int N;

inline __int128 read(){
    __int128 x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void print(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
//使用__int128减少不必要的取模
__int128 TF (int L, int R) {
	__int128 temp=0;
	__int128 M, mi=1<<30, mx=0, k, l, w1, w2; 
	//mi -> min[a[L]...a[M]], mx -> max[a[L]...a[M]]
	//w1 -> min(k, l), w2 -> max(k, l)
	if (L==R) return a[L]*a[L]; //段长小于等于 2 时直接返回
	if (L+1==R) return (a[L]*a[R]*2+a[L]*a[L]+a[R]*a[R])%MOD;
	else M=(L+R)>>1, temp+=TF(L, M), temp+=TF(M+1, R); 
   //否则二分求解两点都取在左半、右半的贡献
	temp=temp%MOD, k=M+1, l=M+1;
   //预处理前缀和 MIN[i]，(M+1 <= i <= R)
	sum1[M+1]=a[M+1], sum1[M]=0;
	for (int p=M+2; p<=R; ++p)
		sum1[p]=min(sum1[p-1]-sum1[p-2], a[p])+sum1[p-1];
   //预处理前缀和 MIN[i]*(i+1)，(M+1 <= i <= R)
	sum2[M+1]=sum1[M+1]*(M+2), sum2[M]=0;
	for (int p=M+2; p<=R; ++p)
		sum2[p]=(sum1[p]-sum1[p-1])*(p+1)+sum2[p-1];
	//预处理前缀和 MAX[i]，(M+1 <= i <= R)
   sum3[M+1]=a[M+1], sum3[M]=0;
	for (int p=M+2; p<=R; ++p)
		sum3[p]=max(sum3[p-1]-sum3[p-2], a[p])+sum3[p-1];
   //预处理前缀和 MAX[i]*(i+1)，(M+1 <= i <= R)
   sum4[M+1]=sum3[M+1]*(M+2), sum4[M]=0;
	for (int p=M+2; p<=R; ++p)
		sum4[p]=(sum3[p]-sum3[p-1])*(p+1)+sum4[p-1];
   //预处理前缀和 MIN[i]*MAX[i]，(M+1 <= i <= R)
   sum5[M+1]=sum1[M+1]*sum3[M+1], sum5[M]=0;
	for (int p=M+2; p<=R; ++p)
		sum5[p]=(sum1[p]-sum1[p-1])*(sum3[p]-sum3[p-1])+sum5[p-1];
   //预处理前缀和 MIN[i]*MAX[i]*(i+1)，(M+1 <= i <= R)
   sum6[M+1]=sum1[M+1]*sum3[M+1]*(M+2), sum6[M]=0;
	for (int p=M+2; p<=R; ++p)
		sum6[p]=(sum1[p]-sum1[p-1])*(sum3[p]-sum3[p-1])*(p+1)+sum6[p-1];
	//开始枚举 Lp（下文中使用 p）
	for (int p=M; p>=L; --p) {
		//更新 Mi，Mx
		mi=min(mi, a[p]), mx=max(mx, a[p]);
		//递增查找 k，l
		while (k<=R&&a[k]>=mi) ++k;
		while (l<=R&&a[l]<=mx) ++l;
		w1=min(k, l), w2=max(k, l);
		//M+1 <= Rp < l 时的贡献
		temp+=((M-p+2)+(w1-p))*(w1-M-1)*mi*mx/2, temp=temp%MOD;
		//l <= Rp < k 或 k <= Rp < l 时的贡献
		if (k<l) temp+=((sum2[w2-1]-sum2[w1-1])-(sum1[w2-1]-sum1[w1-1])*p)*mx, temp=temp%MOD;
		else temp+=((sum4[w2-1]-sum4[w1-1])-(sum3[w2-1]-sum3[w1-1])*p)*mi, temp=temp%MOD;
		//k <= Rp <= R 时的贡献
		temp+=(sum6[R]-sum6[w2-1])-(sum5[R]-sum5[w2-1])*p, temp=temp%MOD;

	}
	return temp;
}
int main () {
	N=read();
	for (int i=1; i<=N; ++i)
		a[i]=read();
	print(TF(1, N))%MOD;
}
```



---

## 作者：Eltaos_xingyu (赞：0)

双倍经验：[$P6406$](http://www.luogu.com.cn/problem/P6406)

## 题目描述

给定一个序列$ a_i,\cdots,a_n $，求：

$$\sum_{i=1}^{n}\sum_{j=i}^{n}(j-i+1)\min(a_i,a_{i+1},\cdots,a_j)\max(a_i,a_{i+1},\cdots,a_j)$$

## 分析

根据 $ n \leq 5\times10^5 $，$O(n^3)$ 的暴力肯定要炸，于是考虑分治，即把序列分成左区间与右区间，分别计算以下三种情况：

1. 区间左右端点均落在左区间。

2. 区间左右端点均落在右区间。

3. 区间左端点落在左区间，区间右端点落在右区间。

其中第 $1$，$2$ 种情况用分治递归解决就行了，于是来着重解决如何求第 $3$ 种情况的问题。

首先，暴力枚举求第 $3$ 种情况的时间复杂度显然是 $O(n^2)$，总时间复杂度是 $O(n^2 \log n)$，肯定是过不了的。于是可以想一些关于区间的优化：

线段树？好吧，这个蒟蒻作者不会线段树维护区间最大最小值。

单调队列？虽然使用单调队列可以不用分治，但是由于区间长度是不定的，这也需要 $O(n^2)$ 的时间复杂度，还是过不了。

前缀和？前缀最小最大值的前缀和？这能算吗......好像真可以......

于是用分治+前缀和预处理，$O(n \log n)$ 的时间复杂度就能过掉此题。

## 具体实现

~~（为什么要推这种式子啊）~~

如果在左区间内定一个下标 $ i $，对于每一个 $ i $，记 $ mi $ 为在 $ a_i,\cdots ,a_{mid} $ 内的最小值下标，$ mx $ 为该区间内最大值下标。显而易见，当 $ i=mid,mid-1,\cdots,1 $ 时，$ mi $ 与 $ mx $ 也是严格单调递减的。

同样的，记 $ mi_{to} $ 为右区间内最后一个大于 $ a[mi] $ 的下标，$ mx_{to} $ 为右区间内最后一个小于 $ a[mx] $ 的下标。同样显而易见的是，当 $ i=mid,mid-1,\cdots,1 $ 时，$ mi_{to} $ 与 $ mx_{to} $ 也是严格单调递增的。

所以，我们可以将第三种情况对于每一个 $ i $ 分 $ 3 $ 个部分来求：

### 第一个部分：$ [mid+1,\min(mi_{to},mx_{to})) $

这一部分最大值为 $ mx $，最小值为 $ mi $，直接等差数列求和就行了，这里就不赘述了。

### 第二个部分：$ [\min(mi_{to},mx_{to}),\max(mi_{to},mx_{to})) $

这一部分 $ mi_{to} $ 与 $ mx_{to} $ 只有一个可用，这个时候就要用前缀和了。假定 $ mi_{to} > mx_{to} $，最小值可用 $ mi_{to} $，最大值就只能用右区间的前缀最大值的前缀和。但是由于 $ i $ 不定，又不能针对于每一个 $ i $ 都算一遍（不然时间复杂度就爆炸了），所以前缀和要算两次，具体如下：

设 $ sum1_k $ 是 $ \max(a_{mid},\cdots,a_k) $ 的前缀和，$ sum2_k $ 是 $ (k + 1) \times \max(a_{mid},\cdots,a_k) $ 的前缀和。

由于区间长度为 $ k-i+1 $，所以可知，这一部分的贡献是 $ sum2[\max(mi_{to},mx_{to})]-sum2[\min(mi_{to},mx_{to})]-i\times(sum1[\max(mi_{to},mx_{to})]-sum1[\min(mi_{to},mx_{to})]) $。

~~（作者推式子好累，但打式子更累）~~

$ mi_{to} < mx_{to} $ 是一样的。

### 第三个部分：$ [\max(mi_{to},mx_{to}),r] $

只要第二部分搞出来了那这一部分就没什么问题了，不过是求 $ \max(a_{mid},\cdots,a_k) \times \min(a_{mid},\cdots,a_k) $ 和 $ (k+1)\times\max(a_{mid},\cdots,a_k) \times \min(a_{mid},\cdots,a_k)  $ 的前缀和就行了。

这样这道题就搞出来了。

什么？你说取模爆炸了？来试试 \_\_int128 吧！（见代码）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
const __int128 mod=1e9;
long long a[MAXN];
__int128 summin1[MAXN],summin2[MAXN],summax1[MAXN],summax2[MAXN],summul1[MAXN],summul2[MAXN];
__int128 fz(int l,int r){
	if(l==r)return a[l]*a[l];
	if(l+1==r)return (a[l]*a[l]+a[r]*a[r]+2*min(a[l],a[r])*max(a[l],a[r]));
	__int128 mid=(l+r)/2;
	__int128 ans=(fz(l,mid)+fz(mid+1,r));
	__int128 nowmin=a[mid+1],nowmax=a[mid+1];
	summin1[mid]=summin2[mid]=summax1[mid]=summax2[mid]=summul1[mid]=summul2[mid]=0;
	summin1[mid+1]=a[mid+1];
	summin2[mid+1]=a[mid+1]*(mid+2);
	for(int i=mid+2;i<=r;i++){
		if(a[i]<nowmin)nowmin=a[i];
		summin1[i]=summin1[i-1]+nowmin;
		summin2[i]=(i+1)*nowmin+summin2[i-1];
	}
	summax1[mid+1]=a[mid+1];
	summax2[mid+1]=a[mid+1]*(mid+2);
	for(int i=mid+2;i<=r;i++){
		if(a[i]>nowmax)nowmax=a[i];
		summax1[i]=summax1[i-1]+nowmax;
		summax2[i]=(i+1)*nowmax+summax2[i-1];
	}
	nowmin=a[mid+1],nowmax=a[mid+1];
	summul1[mid+1]=a[mid+1]*a[mid+1];
	summul2[mid+1]=a[mid+1]*a[mid+1]*(mid+2);
	for(int i=mid+2;i<=r;i++){
		if(a[i]<nowmin)nowmin=a[i];
		if(a[i]>nowmax)nowmax=a[i];
		summul1[i]=summul1[i-1]+nowmax*nowmin;
		summul2[i]=(i+1)*nowmax*nowmin+summul2[i-1];
	}
	int mi=mid,mx=mid,mi_to=mid,mx_to=mid;
	for(int k=mid;k>=l;k--){
		if(a[k]<a[mi])mi=k;
		if(a[k]>a[mx])mx=k;	
		while(a[mi_to]>=a[mi]&&mi_to<=r)mi_to++;
		if(mi_to>mid)mi_to--;
		while(a[mx_to]<=a[mx]&&mx_to<=r)mx_to++;
		if(mx_to>mid)mx_to--;
		ans+=(((min(mi_to,mx_to)-k+1+mid-k+2)*(min(mi_to,mx_to)-mid))*a[mi]*a[mx])/2;
		if(mi_to>mx_to)ans+=(summax2[mi_to]-summax2[mx_to]-k*(summax1[mi_to]-summax1[mx_to]))*a[mi];
		else ans+=(summin2[mx_to]-summin2[mi_to]-k*(summin1[mx_to]-summin1[mi_to]))*a[mx];
		ans+=(summul2[r]-summul2[max(mx_to,mi_to)]-k*(summul1[r]-summul1[max(mx_to,mi_to)]));
	}
	return ans;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cout<<(long long)((fz(1,n))%mod);
}
```


---

## 作者：_ctz (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP22343)

[My Blog](https://ctz45562.github.io/2019/12/29/SPOJ22343-NORMA2-Norma/)

对于一段中点为$mid$的区间$[l,r]$，它的贡献是经过$mid$的子区间权值加上$[l,mid]$和$[mid+1,r]$的贡献，然后就能分治下去了。

这样只需要考虑怎么算出经过某个点的区间的权值和就可以了。

我的脑回路不太正常，搞了一个无脑暴力的做法：

记$mi_i$为$i$到$mid$所有数的最小值，$ma_i$为最大值，$len_i$为$i$到$mid$的长度。

枚举右端点，考虑左端点的影响。对于$j\in[l,mid],i\in[mid+1,r]$，大力分类讨论$[j,i]$的贡献：

- $case1:mi_j< mi_i\land ma_i>ma_i:mi_jma_j(len_j+len_i)$
- $case2:mi_j<mi_i\land ma_j\le ma_i:mi_jma_i(len_j+len_i)$
- $case3:mi_j\ge mi_i\land ma_j>ma_i:mi_ima_j(len_j+len_i)$
- $case4:mi_j\ge mi_i\land ma_j\le ma_i:mi_ima_i(len_j+len_i)$

显然$ma$和$mi$是单调的，而且一个左端点的变化情况只有可能是$case1\rightarrow case2 \rightarrow case4$或$case1\rightarrow case3\rightarrow case4$。所以可以用一个指针维护左端点情况，在随着右端点移动向左跑；再对$case2,3$开两个队列判断是否可以进入$case4$，对每种$case$开两个变量随便搞一搞就行了。复杂度还是$O(n\log n)$。

~~最棒的是这个方法无论是代码难度、美观度还是常数都被正解踩爆了呢~~

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>

#define maxn 500005
#define inf 0x3f3f3f3f

const int mod = 1e9;

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
int a[maxn],mi[maxn],ma[maxn],mul[maxn],ans;
queue<int>min_q,max_q;
#define clear(q) while(!q.empty())q.pop()
inline int mix(int x,int y){return x+y>=mod?x+y-mod:x+y;}
void solve(int l,int r){
	if(l==r){ans=mix(ans,1ll*a[l]*a[l]%mod);return;}
	clear(min_q);
	clear(max_q);
	int mid=l+r>>1,j=mid,min_max_sum,min_max_cnt,min_sum=0,min_cnt=0,max_sum=0,max_cnt=0,sum=0,cnt=0,Mi=inf,Ma=0;
	mi[mid]=ma[mid]=a[mid],min_max_sum=min_max_cnt=mul[mid]=1ll*a[mid]*a[mid]%mod;
	for(register int i=mid-1;i>=l;--i)mi[i]=min(mi[i+1],a[i]),ma[i]=max(ma[i+1],a[i]),mul[i]=1ll*mi[i]*ma[i]%mod,min_max_sum=mix(min_max_sum,1ll*mul[i]*(mid-i+1)%mod),min_max_cnt=mix(min_max_cnt,mul[i]);
	for(register int i=mid+1;i<=r;++i){
		Mi=min(Mi,a[i]),Ma=max(Ma,a[i]);
		while(j>=l){
			if(mi[j]<Mi&&ma[j]>Ma)break;
			min_max_sum=mix(min_max_sum,mod-1ll*mul[j]*(mid-j+1)%mod);
			min_max_cnt=mix(min_max_cnt,mod-mul[j]);
			if(mi[j]>=Mi&&ma[j]<=Ma)sum=mix(sum,mid-j+1),++cnt;
			else if(mi[j]>=Mi)max_sum=mix(max_sum,1ll*ma[j]*(mid-j+1)%mod),max_cnt=mix(max_cnt,ma[j]),max_q.push(j);
			else min_sum=mix(min_sum,1ll*mi[j]*(mid-j+1)%mod),min_cnt=mix(min_cnt,mi[j]),min_q.push(j);
			--j;
		}
		while(!min_q.empty()){
			int k=min_q.front();
			if(mi[k]<Mi)break;
			min_sum=mix(min_sum,mod-1ll*mi[k]*(mid-k+1)%mod),min_cnt=mix(min_cnt,mod-mi[k]);
			sum=mix(sum,mid-k+1),++cnt;
			min_q.pop();
		}
		while(!max_q.empty()){
			int k=max_q.front();
			if(ma[k]>Ma)break;
			max_sum=mix(max_sum,mod-1ll*ma[k]*(mid-k+1)%mod),max_cnt=mix(max_cnt,mod-ma[k]);
			sum=mix(sum,mid-k+1),++cnt;
			max_q.pop();
		}
		ans=mix(ans,mix(mix(mix(min_max_sum,1ll*min_max_cnt*(i-mid)%mod),mix(1ll*max_sum*Mi%mod,1ll*max_cnt*Mi%mod*(i-mid)%mod)),mix(mix(1ll*min_sum*Ma%mod,1ll*min_cnt*Ma%mod*(i-mid)%mod),mix(1ll*sum*Mi%mod*Ma%mod,1ll*cnt*Mi%mod*Ma%mod*(i-mid)%mod))));
	}
	solve(l,mid),solve(mid+1,r);
}
int main(){
	int n=read();
	for(register int i=1;i<=n;++i)a[i]=read();
	solve(1,n);
	printf("%d\n",ans);
}

```

---

## 作者：KokiNiwa (赞：0)

# NORMA

[题目链接](https://www.luogu.com.cn/problem/SP22343)

## 题解

这是一个序列上的问题。

考虑分治，每一次分治$[l,r]$这个区间。设分治中心中心为$mid$。

```Sol(l,r)```函数表示把$[l,r]$这个区间的所有子区间的贡献加到答案上。考虑对于并不能通过分治解决的区间（即跨过$mid$的区间），也就要求出每一个在$[l,mid]$上的为左端点的点的所有右端点的和。设目前处理的左端点为$x$，区间$[x,mid]$的最大值为$mx$，最小值为$mn$。那么这块总可以管辖一段右边区间的范围。设最小值可以延续到$p$，最大值可以延续到$q$（不妨设$p<q$）。那么我们将右边$[mid+1,r]$这段区间分为三段：

1. $[mid+1,p]$这一段。这段的$mx$和$mn$值都是不变的，那么贡献为$mx\cdot mn \cdot \sum_{i=mid+1-x+1}^{p-x+1}i$。这个可以直接计算和。
2. $[p+1,q]$这一段。这段的$mn$是不变的，$mx$在变化。贡献为$mn \cdot \sum_{i=p+1}^{q}\max\{x,i\}\cdot(i-x+1)$。可以再化简一下后面那块：$\max\{x,i\}\cdot (i-x+1)=\max\{x,i\}\cdot i+(1-x)\cdot \max\{x,i\}$。
3. $[q+1,r]$这一段。这段的$mn,mx$都是在变化的。贡献为$\sum_{i=q+1}^{r}\max\{x,i\}\cdot \min\{x,i\}\cdot (i-x+1)$。把后面化简一下：$\max\{x,i\}\cdot \min\{x,i\}\cdot (i-x+1)=\max\{x,i\}\cdot \min\{x,i\}\cdot i + \max\{x,i\}\cdot \min\{x,i\}\cdot (1-x)$

于是可以预处理出区间最大值，最小值，以及几个其他的值，就可以了。

列一下，一共要预处理这么几个数：

1. $\min\{x,i\}$，就是前缀最小值。
2. $\max\{x,i\}$，就是前缀最大值。
3. $\min\{x,i\}\cdot i$的前缀和。
4. $\max\{x,i\}\cdot i$的前缀和。
5. $\max\{x,i\}\cdot \min\{x,i\}\cdot i$的前缀和。
6. $\max\{x,i\}\cdot \min\{x,i\}$的前缀和。

这里的所有前缀、后缀最小值其实都可以从$mid+1$开始算，因为$[x,mid]$这段已经不能覆盖后面的最小值了。

## 样例解释

这部分并没有什么用。。。

### 样例输入

```
3
1 1 2
```

### 样例输出

```
18
```



```
1 1 1*1*1=1
1 2 1*1*2=2
1 3 1*2*3=6
2 2 1*1*1=1
2 3 1*2*2=4
3 3 2*2*1=4
```

## 代码

[Link](https://paste.ubuntu.com/p/gNHpgzS4jT/)



---

## 作者：maomao9173 (赞：0)

[更好的阅读体验点击这里。](https://www.cnblogs.com/maomao9173/p/10907114.html)

要命的题目。

写法：分类讨论进行计算。

枚举过每一个$mid$的所有区间。对于左端点$i∈[l, mid - 1]$，向左推并计算$[l,mid]$范围内的最大$/$最小值。


然后右端点$p$分三种类型考虑。

- $p∈[mid + 1, p1 - 1]$，其中$p1$是第一次出现比$maxw$大或者比$minw$小的数的位置。

- $p∈[p1, p2 - 1]$，其中$p2$是第二次出现比$maxw$大或者比$minw$小的数的位置。

- $p∈[p2, r]$，$r$是当前枚举区间的右端点。

其中情况一高斯求和，情况二和情况三可以化为前缀最大最小值之和$/$积带几个系数的形式$O(N)$维护。

要命原因：取膜。

两年$OI$一场空，_______。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 500000 + 5;
const LL Mod = 1000000000;
#define min(x,y) (x < y ? x : y)
#define max(x,y) (x > y ? x : y)
#define mul(x,y) ((1ll * (x % Mod) * (y % Mod)) % Mod)
#define add(x,y) ((0ll + (x % Mod) + (y % Mod)) % Mod)

int n, arr[N]; LL ans;

int _maxw[N], _minw[N];

LL mn1[N], mn2[N], mx1[N], mx2[N], mnmx1[N], mnmx2[N];

int get_maxp (int w, int l, int r) {
    if (_maxw[r] <= w) return r + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (_maxw[mid] > w) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
} 

int get_minp (int w, int l, int r) {
    if (_minw[r] >= w) return r + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (_minw[mid] < w) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

void cdq (int l, int r) {
    if (l == r) {
        ans = add (ans, mul (arr[l], arr[r])); 
        return;
    }
    int mid = (l + r) >> 1;
    cdq (l, mid + 0);
    cdq (mid + 1, r);
    int maxw = arr[mid], minw = arr[mid];
    mx1[mid - 1] = mx2[mid - 1] = 0;
    mn1[mid - 1] = mn2[mid - 1] = 0;
    mnmx1[mid - 1] = mnmx2[mid - 1] = 0;
    _maxw[mid] = _minw[mid] = arr[mid];
    for (int i = mid + 1; i <= r; ++i) {
        _maxw[i] = max (_maxw[i - 1], arr[i]);
        _minw[i] = min (_minw[i - 1], arr[i]);
    }
    for (int p = mid; p <= r; ++p) {
        mx1[p] = add (mx1[p - 1], mul (_maxw[p], (p + 1)));
        mx2[p] = add (mx2[p - 1], _maxw[p]);
        mn1[p] = add (mn1[p - 1], mul (_minw[p], (p + 1)));
        mn2[p] = add (mn2[p - 1], _minw[p]);
        mnmx1[p] = add (mnmx1[p - 1], mul (_maxw[p], mul (_minw[p], (p + 1))));
        mnmx2[p] = add (mnmx2[p - 1], mul (_maxw[p], _minw[p]));
    }
    for (int i = mid; i >= l; --i) {
        maxw = max (maxw, arr[i]);
        minw = min (minw, arr[i]);
        int p1 = get_maxp (maxw, mid + 1, r); // [mid + 1, r]内第一个比maxw大的地方 
        int p2 = get_minp (minw, mid + 1, r); // [mid + 1, r]内第一个比minw小的地方 
        if (p1 > p2) swap (p1, p2); // 不关注大小，主要看划分
//		cout << p1 << " " << p2 << endl; 
        ans = add (ans, mul (1ll * (p1 - mid - 1) * (p1 + mid - i * 2 + 2) / 2, mul (minw, maxw))); // Part 1
        if (arr[p1] > maxw) {
            ans = add (ans, mul (minw, add (add (mx1[p2 - 1], -mx1[p1 - 1]), -mul (i, add (mx2[p2 - 1], -mx2[p1 - 1]))))); 
        } else {
            ans = add (ans, mul (maxw, add (add (mn1[p2 - 1], -mn1[p1 - 1]), -mul (i, add (mn2[p2 - 1], -mn2[p1 - 1])))));
        }
        if (p2 <= r) {
            ans = add (ans, add (add (mnmx1[r], -mnmx1[p2 - 1]), -mul (i, add (mnmx2[r], -mnmx2[p2 - 1])))); 
        }
    }
}

signed main () {
//	freopen ("data.in", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    cdq (1, n);
//	cout << ans << endl;
    cout << (((ans % Mod) + Mod) % Mod) << endl;;
}
```

---

