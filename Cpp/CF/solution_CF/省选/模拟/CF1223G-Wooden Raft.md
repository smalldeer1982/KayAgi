# Wooden Raft

## 题目描述

假设你被困在一个荒岛上。唯一能自救的方法是制作一个木筏并出海。幸运的是，你有一把手工锯和附近有一片森林。此外，你已经砍倒了几棵树，并将其处理到现在你有 $n$ 根原木，第 $i$ 根原木的长度为 $a_i$。

你想要建造的木筏结构如下：$2$ 根长度为 $x$ 的原木，以及 $x$ 根长度为 $y$ 的原木。这样的木筏面积为 $x \cdot y$。由于你只能用原始的方式测量长度，$x$ 和 $y$ 都必须是整数，并且都至少为 $2$，因为宽度为 $1$ 的木筏不稳定。

你可以将原木锯成若干段，但不能把两根原木拼接成一根。你能制作的木筏的最大面积是多少？

## 说明/提示

在第一个样例中，你可以将长度为 $9$ 的原木锯成 $5$ 段：$2+2+2+2+1$。现在你可以用 $2$ 根长度为 $x=2$ 的原木和 $x=2$ 根长度为 $y=2$ 的原木，制作一个 $2 \times 2$ 的木筏。

在第二个样例中，你可以将 $a_4=18$ 锯成两段 $9+9$，将 $a_8=28$ 锯成三段 $10+9+9$。现在你可以用 $2$ 根长度为 $10$ 的原木和 $10$ 根长度为 $9$ 的原木，制作一个 $10 \times 9$ 的木筏。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
9 10 9 18 9 9 9 28 9
```

### 输出

```
90
```

# 题解

## 作者：lukelin (赞：7)

### 前言
$lukelin$ ~~自认为~~这篇题解写得非常地详细。  
**[更好的阅读体验](https://www.cnblogs.com/linzhengmin/p/11794875.html)**  
在下文中，我们记 $A$ 为 $a$ 数组中的最大值，在代码中就是 "_max" 。
### 题意简述
[题目链接](https://codeforces.com/problemset/problem/1223/G)  
给出一组 $n$ 块木板以及它们的长度 $a_i$，现在要切割出两块木板使之长度为 $x$ ，切割 $x$ 块木板使之长度为 $y$。  
求 $x \times y$ 的最大值。  
![](https://cdn.luogu.com.cn/upload/image_hosting/vok7us63.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  

### 题解
#### 基本思想
我们有一个非常美妙的使用二分的 $\Theta(Aln_Alog_A)$ 的做法，  
但是我们今天要说的是一个比它优秀的 $\Theta(Aln_A)$ 的算法。  
对于几乎所有的做法，都有两个显然的思想，  
枚举 $y$ ，然后计算 $x$；  
贪心地把长度为 $l$ 的木板分解为 $l = tx + ky + \delta, t \in [0, 2]$ 其中 $\delta$ 越小越好。  
有了这个思想以后我们还需要按照 $l / y$ 的值对木板分块(即块的区间 $[ ky, (k+1)y )$ )。  
![](https://cdn.luogu.com.cn/upload/image_hosting/xmna7gir.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
接下来我们可以来进行一波分类讨论。  
#### 两个 $x$ 在同一块木板中被切割出  
![](https://cdn.luogu.com.cn/upload/image_hosting/jq6shxb4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
我们记 $p_1, p_2$ 为两个点，且 $p_1$ 距离它所在块的右端点比 $p_2$ 更远。  
可以证明， $p_1$ 的决策一定劣于 $p_2$ ，因为在抛去 $ky$ 的情况下，
选择 $p_2$ 所得的 $x$ 显然更大。  
那么我们从右往左扫描，设当前的块为 $c$ 。  
在式子 $l = x + ky + \delta$，若当前的块为 $c$ ，当前块往右的所有块(包括自己)里所在块右端点最远的点为 $p$ 。  
则定义$x = (c \times y + p \% y) / 2$ ，剩下的部分给 $ky$ 。
记 $p$ 在 $c$ 中的映射为 $p'$，即 $p' \in c$ 且 $p' \equiv p \mod(y)$(下文中的 $p_1',p_2'$ 同理)。  
![](https://cdn.luogu.com.cn/upload/image_hosting/6m8vy343.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
具体如上图所示。  
#### 两个 $x$ 分别在两块木板中被切割出  
根据上面的结论，我们仍然从右往左扫描，设当前的块为 $c$。然后我们记，  
当前块往右的所有块(包括自己)里所在块右端点最远的木板为 $p_1$ 。  
当前块往右的所有块(包括自己)里所在块右端点次远的木板为 $p_2$ 。  
那么我们总结出并讨论如下四种情况:  
**情况1、2**：  
![](https://cdn.luogu.com.cn/upload/image_hosting/9zatrpv4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)$\quad \quad$![](https://cdn.luogu.com.cn/upload/image_hosting/3euqsmjo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
我们在情况一内分类讨论，发现只有两种情况可能最优，  
第一种是把 $p_2$ 木板分解完全(即 $=x + ky$，$k$ 为 $c$ 到 $p_2$ 所在块跨越的块数），第二种是把 $p_1$ 木板分解完全。  
但是注意到如果 $p_1$ 木板分解完全，那么 $p_2$ 木板长度显然不够了，于是我们牺牲 $p_2$ 木板裁出的一个 $y$ ，来保证能够切除一个 $x$ 。  

再来考虑情况二，我们发现情况二的不同之处是， $p_2$ 木板不能够牺牲一个 $y$ 来保证切除 $x$ 了(长度不足)，  
那么处理方法很简单，直接舍弃掉完全分解 $p_1$ 方案(~~滑稽~~)，只考虑完全分解 $p_2$。  

您觉得讨论结束了？还有两种哦 QwQ 。  

**情况3**:  
![](https://cdn.luogu.com.cn/upload/image_hosting/mbu0644m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
我们发现情况3与情况1相同(显然易见还是将 $p_1$ 或 $p_2$ 分解完全)。  

**情况4**  
![](https://cdn.luogu.com.cn/upload/image_hosting/qfjcxjgu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
我们发现情况4与情况2相同(显然易见还是不能牺牲 $p_2$ 的一个 $y$)。  

然后我们注意到计算的时候，$x$ 不一定小于 $y$的个数，所以要取一个 $min$ 。  

### 代码
note: 注释是英文的，因为怕出玄学错误。  
```cpp
/*
    author: lukelin
    note: I'm sorry that my English is poor.
*/
#include <cstdio>

// input data
int a[500005];
// make length -> pos & the prefix
int cnt[1000005], prfc[1000005];
int l1[1000005], l2[1000005];

#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)
inline void swap(int &a, int &b){
    int tmp = a; a = b, b = tmp;
}

long long ans;

inline void flush(int x, int cnty, int y){
    if (min(cnty, x) <= 1) return ;
    ans = max(ans, 1ll * min(cnty, x) * y);
}

int main(){
    int n, _max = 0; scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%d", &a[i]), ++cnt[a[i]];
        if (_max < a[i]) _max = a[i];
    }
    int prfc_lim = _max << 1; //the max id we will use in prfc
    for (int i = 1; i <= prfc_lim; ++i) prfc[i] = prfc[i - 1] + cnt[i];
    l1[0] = l2[0] = -1;
    for (int i = 1; i <= prfc_lim; ++i){
        //l1 - the longest wood whick less equal than i
        //l2 - the second longest wood whick less equal than i
        if (cnt[i] >= 2) l1[i] = l2[i] = i;
        else if (cnt[i] == 1) l2[i] = l1[i - 1], l1[i] = i;
        else l1[i] = l1[i - 1], l2[i] = l2[i - 1];
    }
    for (int y = 2; y <= _max; ++y){
        int ycnt = 0;
        for (int c = 1; c * y <= _max; ++c){
            //prefix[block c's end] - prefix[block c's begin - 1]
            ycnt += (prfc[c * y + y - 1] - prfc[c * y - 1]) * c;
        }
        // first the situation that both x in one wood
        int p = -1;
        for (int c = _max / y + 1; ~c; --c){
            // the start position and the end position of current block(c)
            int blk_sp = c * y, blk_ep = c * y + y - 1;
            if (l1[blk_ep] >= blk_sp && (p == -1 || p % y < l1[blk_ep] % y))
                p = l1[blk_ep];
            if (~p)
                flush((c * y + p % y) >> 1, ycnt - c, y);
        }
        // second the situation that each x in one different wood
        int p1 = -1, p2 = -1;
		for(int c = _max / y + 1; ~c; --c){
		    // the start position and the end position of current block(c)
		    int blk_sp = c * y, blk_ep = c * y + y - 1;
			if(~p2){
			    //situation 1 - now both p1 and p2 is behind c
			    flush(c * y + p1 % y, ycnt - c * 2 - 1, y);
			    flush(c * y + p2 % y, ycnt - c * 2, y);
			}
			if (~p1 && l1[blk_ep] >= blk_sp && l1[blk_ep] % y > p2 % y){
                if (l1[blk_ep] % y >= p1 % y){
                    //situation 3 - p1 is in c, p2 is behind c
                    flush(c * y + p1 % y, ycnt - c * 2, y),
                    flush(l1[blk_ep], ycnt - c * 2 - 1, y);
                }
                else{
                    //situation 4 - p1 is behind c, p2 is in c
                    flush(l1[blk_ep], ycnt - c * 2, y);
                }
            }
            //update
            if (l1[blk_ep] >= blk_sp && p2 % y < l1[blk_ep] % y)
                p2 = l1[blk_ep];
			if (p1 % y < p2 % y) swap(p1, p2);
			if (l2[blk_ep] >= blk_sp && p2 % y < l2[blk_ep] % y)
                p2 = l2[blk_ep];
			if (p1 % y < p2 % y) swap(p1, p2);
			if (~p2){
			    //situation 2 - p1, p2 is both behind c
                //* if (p1, p2) isn't both in c, it's useless but won't cause WA
			    flush(c * y + p2 % y, ycnt - c * 2, y);
			}
		}
    }
    printf("%I64d", ans);
    return 0;
}
```

---

## 作者：WeLikeStudying (赞：6)

- 一些巧妙的题目对我的帮助是启发式的。
- 先记下来，因为比较难以分类。
## **CF1223G Wooden Raft**
**题意**
- 给出一个数列 $\lbrace a_n\rbrace$ 代表每段木头的长度，你可以将每段木头锯成任意长度为整数的小段，找到 $2$ 根长为 $x$ 的木头，$x$ 根长度为 $y$ 的木头且满足 $x,y\ge 2$（容易发现它形成了一个木筏形状），求 $x\cdot y$ 的最大值。 

**暴力实现**
- 我们可以枚举 $x,y$，再用一个背包判断能否装下，复杂度 $\Theta(n^3)$ 。
- [代码实现](https://www.luogu.com.cn/paste/6wjxrcck)。
- 枚举 $x$ 二分 $y$ 复杂度 $\Theta(n^2\lg n)$ 。
- [代码实现](https://www.luogu.com.cn/paste/njl68zh9)。
- 没什么优化空间了，个人认为主要是因为我们用的 DP 太 low 了。

**思路**
- 显然 $\lbrace a_n\rbrace$ 应该先排序。
- 考虑枚举 $y$，然后有个比较巧妙的东西。
![](https://cdn.luogu.com.cn/upload/image_hosting/ot0s9uhb.png)
- 以下是每块模板的长度以 $y$ 的倍数为分界点所形成的图像。
- 妙处在哪？
- 若最大的数字为 $A$ ，第一次最多 $A$ 块，第二次 $\lfloor\frac A2\rfloor$，第三次 $\lfloor\frac A3\rfloor$ 块……
- 枚举块数的总和是一个调和级数：
$$\sum_{i=1}^n\bigg\lfloor\frac Ai\bigg\rfloor=O(A\ln A)$$
- 咱们下一段解决一个比较困扰的细节问题，如何这样分块，如果再用朴素的算法显然是不行的。
- 然后我们再试着利用块内的性质。

**分块的妙用**
- 怎么分？
- 每一块二分结果，总复杂度是 $O(A\cdot\ln A\cdot\lg n)$。
- 很危险。
- 开一大个桶，$b_i$ 保存值为 $i$ 的元素个数。
- $\Theta(A\ln A)$ 完美，~~尽管一下子就取到了最坏的复杂度~~。
- 鉴于后面的一些操作，我们可以再来一个指针查询每个元素的非零前驱，用于找到每块内的最大或次大元素。
- 同样的原因我们会维护一个前缀和用于求块内的区间和。

**继续实现细节**
- 考虑没有 $x$ 的情况能分多少段 $y$ 。
- 答案是 $\sum\lfloor\frac {a_i}y\rfloor$，这时候我们对于每块统计个数即可在 $\Theta(\lfloor\frac Ay\rfloor)$  的时间得到结果。
- 然后考虑两个相等的 $x$ 应该怎么办，这时候我们分两种情况讨论，两个 $x$ 在同一块木板内，或者不在。

**两块 x 木板在同一块木板内被切割**
![](https://cdn.luogu.com.cn/upload/image_hosting/yhrdmmsn.png)
- 像这图片一样，木板的选择是贪心的，满足两个条件：长度大于等于 $2x$，除以 $y$ 的余数最大（还有一个隐形的条件，必须是每块内部的最大值）
- 你也知道该怎么办了吧，枚举每个块，处理后缀模 $y$ 最大值。
- 如果枚举到 $ky\le2x<ky+y$ 后缀和，则 $y$ 的段数显然为 $-k+\sum\lfloor\frac {a_i}y\rfloor$ 两者取 $\min$ 得到合法的 $x$ 。

**两块 x 木板分别取自不同木板**
![](https://cdn.luogu.com.cn/upload/image_hosting/idv8apv9.png)
- 像这图片一样，木板的选择是贪心的，满足两个条件：长度大于等于 $x$，除以 $y$ 的余数最大（还有一个隐形的条件，必须是每块内部的最大值或次大值）
- 枚举每个块，处理后缀模 $y$ 最大值和次大值。
- 如果枚举到 $ky\le x<ky+y$ 后缀和（$x$ 应该取次大的），则 $y$ 的段数显然为 $-2k+\sum\lfloor\frac {a_i}y\rfloor$ 两者取 $\min$ 得到合法的 $x$。
- 还有另外一种情况：（$x$ 取最大的）此时要在更长的一块木头上削去一段（如果存在的话），$y$ 的段数为 $-2k-1+\sum\lfloor\frac {a_i}y\rfloor$，方法很类似这里就不给出图片了。

**代码实现**
- 时间复杂度 $\Theta(n+A\ln A)$ 空间复杂度 $\Theta(n+A)$。
- 常数似乎会比较大，不管了就这么发出来吧。
- [代码实现](https://www.luogu.com.cn/paste/0qonx74a)。

---

## 作者：Kelin (赞：4)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102535366)
给你$n$根木头，第$i$根长$a_i$

锯出$2$段长度为$x$的木头和$x$段长度为$y$的木头

木头锯完后**不能**再拼接且必须满足$x\ge2,y\ge2$

求$x\times y$的最大值

$n\le5\times10^5,2\le a_i\le5\times10^5$

---

## 题解
因为要锯$x$段长度为$y$的木头，$y$影响更大，所以考虑对于某一个$y$怎么要求出最大的$x$

对于一个$y$能锯的的木头总数$cntY=\sum_{i=1}^n\lfloor\frac{a_i}y\rfloor$

剩下两根长度为$x$的木头可以分两种情况讨论：①来自于同一根木头；②来自于不同木头

①：来自于同一根木头

假设限定$2x\in[ky,ky+y)$，那么$2x$的最大值就是$ky+\max\{a_i\mod y|a_i\ge ky\}$

$k$从大到小枚举并记录$a_i\mod y$的最大值即可

剩余木头数量即为$cntY-k$

②：来自于不同木头

假设限定$x\in[ky,ky+y)$，记录$a_i\mod y$的最大值$m_1$，次大值$m_2$

如果$x$取$ky+m_2$，那么剩余木头数量就是$cntY-2k$

如果$x$取$ky+m_1$，这样就要把一段更长的木头（如果存在的话）多锯开一小段，那么剩余木头数量就是$cntY-2k-1$

再处理一些细节即可（详见代码）

记$A=\max a_i$,时间复杂度$O(n+\sum_{y=2}^A\lfloor\frac Ay\rfloor)=O(n+A\ln A)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
	char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
	while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
const int N=5e5+5,M=N<<1,inf=~0u>>1;
typedef long long ll;
typedef int arr[N];
struct Pair{
	int Mod,Len;
	Pair(int x=-1,int y=-1){Mod=x,Len=y;}
	bool operator<(Pair b)const{return Mod==b.Mod?Len<b.Len:Mod<b.Mod;}
};
struct  Rest{
	Pair x,y;
	void Up(Pair z){y=max(y,min(x,z)),x=max(x,z);}
};
int n,Mx;arr pr,cnt,sum;ll ans,cntY;
inline void Upd(int x,int y){x<2?0:cmax(ans,(ll)x*y);}
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	sd(n);
	int x;
	fp(i,1,n)sd(x),++cnt[x],cmax(Mx,x);
	fp(i,1,Mx){
		sum[i]=sum[i-1]+cnt[i];	
		pr[i]=cnt[i]?i:pr[i-1];
	}
	fp(y,2,Mx){
		cntY=0;Rest res;
		for(int i=y;i<=Mx;i+=y)
			cntY+=(ll)(sum[min(i+y-1,Mx)]-sum[i-1])*(i/y);
		for(int k=Mx/y,m=Mx+1;k>=0;m=k*y,--k){
			int val=pr[m-1],More=(res.x.Mod>=0)+(res.y.Mod>=0),ky=k*y;
			if(val>=ky){
				res.Up(Pair(val% y,val));
				if(cnt[val]==1)val=pr[val-1];
				if(val>=ky)res.Up(Pair(val%y,val));
			}
			if(res.x.Mod>=0)
				Upd(min((ll)(ky+res.x.Mod)>>1,cntY-k),y);
			if(res.y.Mod>=0){
				Upd(min((ll)(ky+res.y.Mod),cntY-2*k),y);
				if(More+(res.x.Len<m)>1)
					Upd(min((ll)(ky+res.x.Mod),cntY-2*k-1),y);
			}
		}
	}
	printf("%lld\n",ans);
return 0;
}
```

---

## 作者：Cure_Wing (赞：1)

[CF1223G Wooden Raft](https://www.luogu.com.cn/problem/CF1223G)

### 解析

观察一下所求的答案是一个乘积的形式，而 $x$ 和 $y$ 两个量都是自变量，且不好直接计算。但是 $x$ 和 $y$ 的最大值只有 $\max\{a_i\}\le5\times10^5$，算是一个可以接受的范围。通常我们可以考虑枚举其中一项，推出另外一项的最优情况。

首先枚举 $x$ 是没有前途的。因为首先你要确定 $x$ 的来源，即从一根木棒中取出还是两根木棒取。可以发现取两根木棒枚举的复杂度已经达到了 $O(n^2)$，没有优化的余地了。

只能枚举 $y$ 了。当 $y=i$ 时，对于长度为 $a_i$ 的木棒，它所能分割出最多的长度为 $i$ 的木棒的段数为 $\left\lfloor\dfrac{a_i}{i}\right\rfloor$。此时我们要找出两根长度为 $x$ 的木棒，考虑两个来源：

1. 从一根木棒截取：

对于多余的 $a_i\bmod i$ 的长度，不可以作为 $y$，一定可以将其纳入 $x$ 的截取范围。对于原本可以作为 $y$ 的一段，如果想要将其变为 $x$ 的一部分，可以整段拿走，否则会多出无用的部分。由于没有找到一种方法说明从长度为 $y$ 的木棒中取出的段数与答案有单调性，于是只能枚举从 $y$ 的木棒中取出多少段。在能取得的段数相同的时候，绝对优先考虑剩余部分较长的木棒。可以发现，截取段数较多的木棒可以选择取出较少的 $y$ 长度的木棒，可以并入截取段数较少的木棒共同选择。通过分析，可以发现取出段数从大到小枚举是比较方便的。

假设完全分割可以得到的长度为 $i$ 的段数为 $cnt$，当前枚举取出段数为 $j$，能取出 $j$ 段的木棒长度 $a_k\bmod i$ 后最大的木棒长度为 $m$，那么此时 $x\times y=\min\{cnt-j,\dfrac{j*i+(m\bmod i)}{2}\}\times i$。

2. 从两根木棒截取

同样可以采用和 1 相同的贪心思路，对于分别取出 $j$ 段的两根木棒，优先选择对 $i$ 取模后较大的两根。具体可以参照上面推理或参考代码。需要考虑两种情况：根据模 $i$ 较大的长度取，根据模 $i$ 较小的长度取。

时间复杂度方面，令 $m=\max\{a_i\}$，枚举取出的段数总次数为 $m+\dfrac{m}{2}+\dfrac{m}{3}+\cdots+1\approx m\ln m$，时间复杂度即为 $O(n+m\ln m)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=1000006;
int n,a,c[N],pre[N],m,cnt;
long long ans;
inline void max(int x,int y){ans=std::max(ans,1ll*(x>1)*x*y);}
signed main(){
	freopen("poly.in","r",stdin);
	freopen("poly.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;for(int i=1;i<=n;++i){cin>>a;++c[a];m=std::max(m,a);}pre[0]=-1;//为了方便计算及查找区间内是否存在木棒，我们对木棒的长度开桶。
	for(int i=1;i<=2*m;++i){
		if(c[i]) pre[i]=i;
		else pre[i]=pre[i-1];
		c[i]+=c[i-1];
	}
	for(int i=2;i<=m;++i){
		cnt=0;
		for(int j=i;j<=m;j+=i) cnt+=(c[j+i-1]-c[j-1])*(j/i); 
		int mx1=0,mx2=0;
		for(int j=m/i;j>=0;--j){
			int L=j*i,R=L+i-1;
			if(pre[R]>=L&&pre[R]%i>mx1%i) mx1=pre[R];
			max(std::min(cnt-j,j*i+mx1%i>>1),i); 
		}
		mx1=0;
		for(int j=m/i;j>=0;--j){
			int L=j*i,R=L+i-1;
			if(mx1&&mx2){
				max(std::min(cnt-2*j-1,j*i+mx1%i),i);
				max(std::min(cnt-2*j,j*i+mx2%i),i);
			}
			if(mx1&&pre[R]>=L&&pre[R]%i>mx2%i){//新取一根
				if(pre[R]%i>=mx1%i){
					max(std::min(cnt-2*j-1,pre[R]),i);
					max(std::min(cnt-2*j,j*i+mx1%i),i);
				}else max(std::min(cnt-2*j,pre[R]),i);
          //有些时候另外一种取法可以省略，具体原因呢可以自己分析
			}
			R=pre[R];
			if(R>=L){//多取多好
				if(R%i>=mx1%i){mx2=mx1;mx1=R;}
				else if(R%i>mx2%i) mx2=R;
				R=c[R]-c[R-1]>1?R:pre[R-1];
				if(R>=L&&R%i>mx2%i) mx2=R;
			}
			if(mx1&&mx2) max(std::min(cnt-2*j,j*i+mx2%i),i);
		}
	}
	cout<<ans;
	return 0;
}//第五十四回 史太君破陈腐旧套 王熙凤效戏彩斑衣
```

---

