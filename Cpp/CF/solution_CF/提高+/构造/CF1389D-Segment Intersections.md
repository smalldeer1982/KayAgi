# Segment Intersections

## 题目描述

You are given two lists of segments $ [al_1, ar_1], [al_2,       ar_2], \dots, [al_n, ar_n] $ and $ [bl_1, br_1], [bl_2, br_2],       \dots, [bl_n, br_n] $ .

Initially, all segments $ [al_i, ar_i] $ are equal to $ [l_1,       r_1] $ and all segments $ [bl_i, br_i] $ are equal to $ [l_2, r_2] $ .

In one step, you can choose one segment (either from the first or from the second list) and extend it by $ 1 $ . In other words, suppose you've chosen segment $ [x, y] $ then you can transform it either into $ [x - 1, y] $ or into $ [x, y + 1] $ .

Let's define a total intersection $ I $ as the sum of lengths of intersections of the corresponding pairs of segments, i.e. $ \sum\limits_{i=1}^{n}{\text{intersection_length}([al_i, ar_i],       [bl_i, br_i])} $ . Empty intersection has length $ 0 $ and length of a segment $ [x, y] $ is equal to $ y - x $ .

What is the minimum number of steps you need to make $ I $ greater or equal to $ k $ ?

## 说明/提示

In the first test case, we can achieve total intersection $ 5 $ , for example, using next strategy:

- make $ [al_1, ar_1] $ from $ [1, 2] $ to $ [1, 4] $ in $ 2 $ steps;
- make $ [al_2, ar_2] $ from $ [1, 2] $ to $ [1, 3] $ in $ 1 $ step;
- make $ [bl_1, br_1] $ from $ [3, 4] $ to $ [1, 4] $ in $ 2 $ steps;
- make $ [bl_2, br_2] $ from $ [3, 4] $ to $ [1, 4] $ in $ 2 $ steps.

 In result, $ I =     \text{intersection_length}([al_1, ar_1], [bl_1, br_1]) +     \text{intersection_length}([al_2, ar_2], [bl_2, br_2]) + \\ +     \text{intersection_length}([al_3, ar_3], [bl_3, br_3]) = 3 + 2 + 0 = 5 $ In the second test case, we can make $ [al_1, ar_1] = [0,       1000000000] $ in $ 1000000000 $ steps and $ [bl_1, br_1] = [0,       1000000000] $ in $ 1000000000 $ steps.

In the third test case, the total intersection $ I $ is already equal to $ 10 > 3 $ , so we don't need to do any steps.

## 样例 #1

### 输入

```
3
3 5
1 2
3 4
2 1000000000
1 1
999999999 999999999
10 3
5 10
7 8```

### 输出

```
7
2000000000
0```

# 题解

## 作者：钓鱼王子 (赞：9)

来一个单次 $O(1)$ 的优秀做法。

发现两条线段的关系有三个阶段。

$1.$ 经历若干次操作相接触。

$2.$ 每进行一次操作重复区间长度增加 $1$，经历若干次操作相包含。

$3.$ 每进行两次操作重复区间长度增加 $1$。

其中，前两次的若干我们可以求出来。

先不考虑相交的情况。

令 $l_1<l_2$。

相交次数： $l_2-r_1$，包含的时候 $(r_2-l_1)\times 2-(r_1-l_1)-(r_2-l_2)$。

如果执行多次 $1+2$ 的方案比执行一次 $1+2$ 加多次 $3$ 更优，那么最好选 $1+2$，然后最后一次选残缺的 $1+2$（$2$ 没有用完）或多次 $3$，取一个 $\min$。

相交的话可以缩为一个点。

注意边界。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
} 
using namespace std;
int n,m,a,b,c,d,t,ans,lim,x,y,xx,yy;
signed main(){
	t=read();
	while(t--){
		n=read(),m=read(),a=read(),b=read(),c=read();d=read();
		if(a>c)swap(a,c),swap(b,d);
		if(a==c&&b<d)swap(b,d);
		if(b>d){
			m-=(d-c)*n;b-=d-c;c=a;d=c;
		}
		else if(b>c){
			m-=(b-c)*n;d-=b-c;
			b=c;
		}
	//	printf("%lld %lld %lld %lld %lld\n",m,a,b,c,d);
		if(m<=0){
			puts("0");
			continue;
		}
		x=max(c,a)-min(a,c)+max(b,d)-min(b,d);
		y=max(b,d)-min(a,c);
	//	printf("%lld %lld\n",x,y);
		if(y){
		xx=m%y,yy=m/y;
		yy=min(yy,n);xx=m-yy*y;
		ans=min(yy?x*yy+xx*2:1000000000000000000ll,(yy<n&&xx<y)?x*(yy+1)-(y-xx):100000000000000000ll);}else ans=m*2;
		printf("%lld\n",ans);
	}
}
```


---

## 作者：devout (赞：6)

**description**

~~这题面真的不说人话~~

现在有$2n$个区间$[al_1,ar_1],[al_2,ar_2]\cdots[al_nar_n],[bl_1,br_1],[bl_2,bl_2]\cdots[bl_n,br_n]$

其中$[al_i,ar_i]$初始都是$[l_1,r_1]$，$[bl_i,br_i]$初始都是$[l_2,r_2]$

定义一次操作为任意选出一个区间，使他的左端点左移一位或右端点右移一位

问最少需要多少次操作，使得

$$\sum_{i=1}^n size(a_i\cap b_i)\geq k$$

其中一个区间$[l,r]$的大小定义为$r-l$

**solution**

首先可以用$k$减去本身就已经存在的交集大小

如果这个时候$k\leq 0$，那么直接输出$0$

剩下的情况，对于初始的$[l_1,r_1],[l_2,r_2]$，我们令$l_1\leq l_2$

那么可以分三种情况进行讨论

- 情况1，$l_1\leq l_2\leq r_2\leq r_1$

![](https://img-blog.csdnimg.cn/20200730212014361.png)

我们发现，对于绿色的部分，我们每次可以花费$1$的代价，让交集的大小增加$1$

所以对于任意的一个$i$，如果我们选择变动他，最优策略一定是直到这两个区间完全重合

所以我们先尽量把所有的$[l_2,r_2]$都变成$[l_1,r_1]$，此时如果交集已经$\geq k$，则直接输出$k$即可

如果不行，我们每次可以让其中一个区间的$a,b$都扩展$1$，相当于花费$2$的代价，让交集大小增加$1$，这个时候剩下的部分$\times 2$就可以了

- 情况2，$l_1\leq l_2\leq r_1\leq r_2$

这种情况和情况1本质上是一样的，这里不再过多赘述

- 丧心病狂的情况3，$l_1\leq r_1\leq l_2\leq r_2$

![](https://img-blog.csdnimg.cn/20200730212813907.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Rldm91dF8=,size_16,color_FFFFFF,t_70)

我们发现，按照情况1和2的方法再做的时候，我们不能再像以前一样，用$1$的代价让交集大小增加$1$了

而是可以利用$l_2-r_1+r_2-l_1$的代价，让交集增加$r_2-l_1$

于是，我们可以按照前两种的方法贪心啦！

~~然后你就成功的死在了第二个点~~

我们发现，当$l_2-r_1$非常非常大，而我们最后可能只剩下很少的时候，我们甚至还不如就让$a_1,b_1$的区间拓展到重合，然后每次花费代价为$2$，让交集增加$1$的解决掉

这个东西怎么办呢？我们可以暴力枚举将几个区间完全拓展了就好啦！

这样，情况1,2的复杂度都是$O(1)$，情况3的复杂度是$O(n)$，总复杂度$O(n)$

其实题面里还说了一句

It's guaranteed that the sum of $n$ doesn't exceed $2\times10^5$

其实这也提醒我们复杂度是$O(n)$的，如果你写了个$O(1)$的那肯定是错的

**code**

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

# define int long long 

int t,n,k;
int l1,r1,l2,r2;

signed main()
{
    read(t);
    while(t--){
        read(n),read(k);
        read(l1),read(r1);
        read(l2),read(r2);
        if(l2<l1)swap(l1,l2),swap(r1,r2);
        if(r1>=r2)k-=n*(r2-l2);
        else if(l2<=r1)k-=n*(r1-l2);
        if(k<=0){puts("0");continue;}
        if(r1>=r2){
            int len=l2-l1+r1-r2;
            if(n*len>=k)printf("%lld\n",k);
            else{
                k-=n*len;
                printf("%lld\n",n*len+k*2);
            }
        }
        else if(l2<=r1){
            int len=r2-r1+l2-l1;
            if(n*len>=k)printf("%lld\n",k);
            else{
                k-=n*len;
                printf("%lld\n",n*len+k*2);
            }
        }
        else{
            int len=r2-l1,cost=l2-r1;
            if(n*len>=k){
                int res=1e18;
                Rep(i,1,n)
                    if(k<i*len)break;
                    else res=min(res,(cost+len)*i+(k-i*len)*2);
                res=min(res,k+((k-1)/len+1)*cost);
                printf("%lld\n",res);  
            }
            else{
                int res=1e18;
                res=min(res,n*len+n*cost+2*(k-n*len));
                printf("%lld\n",res);
            }
        }
    }
    return 0;
}

```

**postscript**

当时这题交上去过的时候都不知道自己是怎么过的。。。

一直很慌，结果最后居然没有fst qwq

---

## 作者：huayucaiji (赞：3)

**UPD1：2020.8.1 修改一处笔误（望管理大大通过）**

-------

我们先打开单词小本本记录一下 [intersection](https://fanyi.baidu.com/?aldtype=85#en/zh/intersection) 这个词（虽然我会）。它的意思是交叉，十字路口。

我们切入正题。

首先我们会发现问题分成两个类别。第一类是 $[l_1,r_1],[l_2,r_2]$ 有交集。即 $\min(r_1,r_2)-\max(l_1,l_2)\geq 0$。交集的长度（即题目中的 $\operatorname{intersection\ length}$）也就为 $\min(r_1,r_2)-\max(l_1,l_2)$。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/z98707ua.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

那么此时我们选择这种做法（也就是官方解法）。我们每次将 $[l_1,r_1]$ 扩展为 $[l_1,r_1+1]$，或者同理将 $[l_2,r_2]$ 扩展为 $[l_2-1,r_2]$，知道两个区间完全相同为止，在这样扩充时，我们每用一步，就可以让交集长度增加 $1$。是最划算的。但是一旦两个区间完全相同，即 $l_1=l_2,r_1=r_2$ 时，我们不能在这样操作了，我们必须让两个区间的同一边长度都增加 $1$，才能让交集长度增加 $1$。这是唯一的选择了。那么第一类我们讨论完了。

再来看第二类，也就是一开始没有交集。那么我们可以让它有交集在用第一种情况的处理方法来处理。我们要枚举一个 $cnt$，代表要让多少对区间有交集。我们完全没有必要让所有的区间成双成对地有交集，毕竟有的用不上嘛~。我们让一堆区间有交集的最小步数就为 $\max(l_1,l_2)-\min(r_1,r_2)$。注意还要乘以 $cnt$。最后用第一种情况的处理方法来处理即可。时间复杂度为 $O(n)$。

**注意细节！比如开 long long**

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long//不开long long 见祖宗！
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int calc(int n,int k,int l1,int r1,int l2,int r2) {
	if(k<=0) {
		return 0;
	}
	
	if((max(r1,r2)-min(l1,l2))*n>=k+(min(r1,r2)-max(l1,l2))*n)//注意细节 {
		return k;
	}
	else {
		int tmp=(max(l1,l2)-min(l1,l2)+max(r1,r2)-min(r1,r2))*n;//细节
		return tmp+(k-tmp)*2;
	}
}

signed main() {
	int t=read();
	
	while(t--) {
		int n,k,l1,l2,r1,r2;
		n=k=l1=l2=r1=r2=0;
		cin>>n>>k>>l1>>r1>>l2>>r2;
		
		int ans=0x7fffffffffffffff;
		if(min(r1,r2)<max(l1,l2)) {
			for(int i=1;i<=n;i++) {
				ans=min(ans,
                		(max(l1,l2)-min(r1,r2))*i+calc(i,k,min(l1,l2),min(r1,r2),min(r1,r2),max(r1,r2)));//细节，我们要进行计算的是我们处理完的区间，是有交集的，保证有交集即可。
			}
		}
		else {
			ans=calc(n,k-(min(r1,r2)-max(l1,l2))*n,l1,r1,l2,r2);
		}
		
		printf("%lld\n",ans);//lld的细节
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：3)

$O(1)$ 贪心。

下面把一对区间**均**延长至 $[min(l_1,l_2),max(r_1,r_2)]$ 的情形叫做「完全延长」。

记 $d$ 为延长前已经重合的长度；$D$ 为完全延长时重合的长度，即 $max(r_1,r_2)-min(l_1,l_2)$。

若 $d>0$，判断 $k \le n*d$，若满足直接输出 $0$。

否则，由于从开始重合到完全重合，每次延长一个单位重合长度就会加一，而到完全重合之后要延长两个单位才能使重合长度加一，所以得到如下贪心策略：

1. 若 $k \le D$，只需延长一对区间；
2. 若 $k>D$，则考虑三种贪心策略，取最小值：
   1. 完全延长一对区间，然后在这对区间的基础上延长；
   2. 若 $k \le n*D$，则完全延长 $\lfloor \frac{k}{D} \rfloor$ 对区间。剩余的 $k$，要么在某对完全延长的区间上延长，要么用一对没有延长过的区间；
   3. 若 $k > n*D$，则完全延长 $n$ 对区间，剩余的 $k$ 在某对完全延长的区间上延长。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var t, n, k, l1, r1, l2, r2, ans int64
	for Fscan(in, &t); t > 0; t-- {
		Fscan(in, &n, &k, &l1, &r1, &l2, &r2)
		if l1 > l2 {
			l1, r1, l2, r2 = l2, r2, l1, r1
		}
		d, D := min(r1, r2)-l2, max(r1, r2)-l1 // d=已经重合的长度，D=完全重合的长度
		if d > 0 {
			k -= n * d
			if k <= 0 {
				Fprintln(out, 0)
				continue
			}
			D -= d
			d = 0
		} else {
			d = -d
		}
		if k <= D {
			ans = d + k // 只需延长一对
		} else {
			ans = d + D + (k-D)*2 // 完全延长一对+在这对的基础上延长
			if k <= n*D {
				ans = min(ans, k/D*(d+D)+min(k%D*2, d+k%D)) // 完全延长 k/D 对，剩余的 k，要么在某对完全延长的区间上延长，要么用一对没有延长过的区间
			} else {
				ans = min(ans, n*(d+D)+(k-n*D)*2) // 完全延长 n 对，剩余的 k 在某对完全延长的区间上延长
			}
		}
		Fprintln(out, ans)
	}
}
```



---

## 作者：__3E24AC7002AD9292__ (赞：1)

萌新打 VP 赛场切的题，但是这真的有 $2100$？

如果想要让一对线段做更多的贡献，分情况讨论一下：

- 如果两个线段左右端点不完全相等，那么操作让它们更接近相等就行。
- 如果左右端相等，那么花 $2$ 个操作扩展同一对线段线段的右端。

因为 $n$ 比较小，且我比较懒，可以直接枚举进行修改的线段对数，其余不变，显然要先让这些线段接近相等，还达不到要求再去同时扩展右端。


```cpp
n=read(),k=read(),l=read(),r=read(),_l=read(),_r=read();
int x=max(0ll,min(r,_r)-max(l,_l));
if (k-x*n<=0){
    cout<<"0\n";
    continue;
}
int c=0,_k=k,ans=1e18,y=max(r,_r)-min(l,_l);
for (int i=1;i<=n;i++){
    c+=abs(_l-l)+abs(_r-r);
    k=k-y*i-x*(n-i);
    if (k<=0) ans=min(ans,c+k);
    else ans=min(ans,c+k*2);
    k=_k;
}
cout<<ans<<'\n';
```

---

## 作者：tbdsh (赞：0)

前言：纪念调了半个模拟赛然后发现只需要改一点点东西就能过。 

## 题意简述
[更好的阅读体验](/article/16tvkzpy/)

[洛谷题目传送门](/problem/cf1389d)

[CodeForces 题目传送门](//codeforces.com/contest/1389/problem/d)

有 $t$ 组数据。每组数据给定两组线段 $a,b$，每一组有 $n$ 条。其中 $a$ 中的所有线段初始都为 $[l_1,r_1]$，$b$ 中的所有线段初始都为 $[l_2,r_2]$。

$a$ 中第 $i$ 条线段为 $[al_i,ar_i]$，$b$ 中第 $i$ 条线段为 $[bl_i,br_i]$

每次操作可以选择一个线段 $[l,r]$，将其变成 $[l-1,r]$ 或 $[l,r+1]$。

定义 $I=\sum\limits_{i=1}^n(\min(ar_i,br_i)-\max(al_i,bl_i))$。求至少需要多少次操作能够使得 $I\ge k$。

## 分析
首先特判掉初始 $I$ 就已经 $\ge k$ 的情况。

然后我们枚举 $i\in[1,n]$。对于每个 $i$ 做如下相同的操作：

1.如果 $al_i>bl_i$，那么将 $al_i,bl_i$ 和 $ar_l,br_l$ 分别交换。

2.如果当前 $\min(ar_i,br_i)-\max(al_i,bl_i)$ 为 $0$，那么将较小的 $ar_i$ 更新为 $bl_i$。

3.接下来我们在 $I<k$ 的前提下使 $al_i$ 和 $bl_i$，$ar_i$ 和 $br_i$ 尽可能的靠近，并将修改的操作次数更新至 $ans$ 中。这里是可以 $O(1)$ 求的，具体可以看代码。

4.注意到我们在两条线段已经有交集的情况下，同时扩展一边使答案加一。所以记录在当前操作下，求出直接用 $2\times \max(0,k-I)$ 次操作使 $I=k$ 的答案 $t$，并与之前记录的答案 $p$ 取最小值。

那么此时我们就已经使所有的 $al_i=bl_i$，所有的 $ar_i=br_i$。此时再将答案 $ans$ 变为 $ans+2\times \max(0,k-I)$ 与 $p$ 取最小值即可。

时间复杂度：$O(n)$。
## Code
可能因为我这种思路比较好想，然后实现起来就比较麻烦。~~然后导致调了一上午。~~
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
int n, k, l1, r1, l2, r2;
int ans, cnt;
struct Node{
  int l, r;
}a[MAXN], b[MAXN];
void xg(int &l1, int &r1, int &l2, int &r2){
  if (l1 > l2){
    swap(l1, l2);
    swap(r1, r2);
  }
  if (r1 < l2){
    ans += abs(l2 - r1);
    r1 = l2;
  }
}
void Solve(){
  cin >> n >> k >> l1 >> r1 >> l2 >> r2;
  int _l1 = l1, _r1 = r1, _l2 = l2, _r2 = r2;
  if (l1 > l2){
    swap(l1, l2);
    swap(r1, r2);
  }
  cnt = max(0ll, min(r2, r1) - max(l1, l2)) * n;
  if (cnt >= k){
    cout << "0\n";
    return ;
  }
  ans = 0;
  int yuanshen = 1e18;
  cnt = max(0ll, min(r2, r1) - max(l1, l2)) * n;
  bool f = 0;
  if (!cnt){
    f = 1;
  }
  for (int i = 1; i <= n && cnt < k; i++){
    int L1 = l1, L2 = l2, R1 = r1, R2 = r2;
    if (f){
      xg(L1, R1, L2, R2);
    }
    int qwq = max(0ll, min(k - cnt, abs(R2 - R1)));
    cnt -= max(0ll, min(R2, R1) - max(L1, L2));
    ans += qwq;
    if (R2 > R1){
      R1 += qwq;
    }else {
      R2 += qwq;
    }
    cnt += max(0ll, min(R2, R1) - max(L1, L2));
    qwq = max(0ll, min(k - cnt, abs(L1 - L2)));
    cnt -= max(0ll, min(R2, R1) - max(L1, L2));
    ans += qwq;
    if (L1 > L2){
      L1 -= qwq;
    }else {
      L2 -= qwq;
    }
    cnt += max(0ll, min(R2, R1) - max(L1, L2));
    yuanshen = min(yuanshen, ans + max(0ll, k - cnt) * 2);
  }
  ans += max(0ll, k - cnt) * 2;
  cout << min(ans, yuanshen) << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}

```

---

## 作者：123zbk (赞：0)

## 题目大意
有两组线段，每组有 $n$ 条，一开始所有第一组内的线段都等于 $\left[l_{1}, r_{1}\right]$，第二组的线段都等于 $\left[l_{2}, r_{2}\right]$。每次操作可以选择一条线段并将其扩展 $1$ 单位长度。求使每组对应线段的**交集**的长度之和达到（大于等于）$k$ 所需的最少操作数。

## 解题思路
首先应先把 $n$ 条线段已经交上的部分减掉，如果此时 $k\le0$ 直接输出 $0$ 即可。 

此时我们默认 $l_1 \le l_2$，一共分三种情况：

- 第一种，$l_1 \le l_2 \le r_2 \le l_1$，也就是第一条线段完全包含第二条线段。

最优的策略一定是扩展第二条线段直至与第一条线段重合。此时操作 $1$ 次，交集长度加 $1$。

这种情况最多能操作 $r_1 -r_2+l_1-l_2$ 次。如果交集长度仍小于 $k$，就应该同时拓展对应线段的头或尾。此时操作 $2$ 次，交集长度加 $1$。

- 第二种，$l_1 \le l_2 \le r_1 \le l_2$，也就是两条线段有交集。

第一种情况基本一致。

先将两条线段拓展至重合。此时操作 $1$ 次，交集长度加 $1$。

但是最多只能操作 $r_2-r_1+l_2-l_1$次。剩下的每操作 $2$ 次交集长度加 $1$。

- 第三种，$l_1 \le r_1 \le l_2 \le r_2$

这种情况就不能像刚才那么做了。因为我们发现这两条线段大概率没有交点，也就是说我们想让线段操作 $1$ 次而交集就加 $1$ 时是需要先走 $l_2-r_1$ 步的。也就是说可能这样走还不如操作 $2$ 次交集加 $1$ 次数少。所以这里将两种情况都讨论一下就行了。

## code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,l1,r1,l2,r2,res;
signed main()
{
    cin>>T;
    while(T--)
    {
        scanf("%lld%lld%lld%lld%lld%lld",&n,&k,&l1,&r1,&l2,&r2);
        if(l1>l2)
        {
            swap(l1,l2);
            swap(r1,r2);
        }
        if(max(l1,l2)<=min(r1,r2))//有交集 
        {
        	k-=n*(min(r1,r2)-max(l1,l2));
		}
        if(k<=0)
        {
            puts("0");
            continue;
        }
        if(r1>=r2)
        {
            int len=r1-r2+l2-l1;
            if(n*len>=k)
            {
                printf("%lld\n",k);
            }
            else
            {
                k-=n*len;
                printf("%lld\n",n*len+k*2);
            }
        }
        else if(l2<=r1)
        {
            int len=r2-r1+l2-l1;
            if(n*len>=k)
            {
                printf("%lld\n",k);
            }
            else
            {
                k-=n*len;
                printf("%lld\n",n*len+k*2);
            }
        }
        else
        {
            int len=r2-l1,ans=r2-r1+l2-l1;
            if(n*len>=k)
            {
                res=((k-1)/len+1)*ans-(((k-1)/len+1)*len-k);
                //cout<<"res1:"<<res<<endl;
                for(int i=1;i<=n;i++)
                {
                    if(i*len>k)
                    {
                        break;
                    }
                    res=min(res,i*ans+2*(k-i*len));
                    //cout<<"res2:"<<res<<endl;
                }
                printf("%lld\n",res);
            }
            else
            {
                res=n*ans+2*(k-n*len);
                printf("%lld\n",res);
            }
        }
    }
    return 0;
}
/*
1
3 5
1 2
3 4
*/
```

---

