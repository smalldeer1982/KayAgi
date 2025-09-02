# [POI 2014] PTA-Little Bird

## 题目描述

有 $n$ 棵树排成一排，第 $i$ 棵树的高度是 $d_i$。

有 $q$ 只鸟要从第 $1$ 棵树到第 $n$ 棵树。

当第 $i$ 只鸟在第 $j$ 棵树时，它可以飞到第 $j+1, j+2, \cdots, j+k_i$ 棵树。

如果一只鸟飞到一颗高度大于等于当前树的树，那么它的劳累值会增加 $1$，否则不会。

由于这些鸟已经体力不支，所以它们想要最小化劳累值。

## 说明/提示

$1 \le n \le 10^6$，$1 \le d_i \le 10^9$，$1 \le q \le 25$，$1 \le k_i \le n - 1$。

## 样例 #1

### 输入

```
9
4 6 3 6 3 7 2 6 5
2
2
5
```

### 输出

```
2
1
```

# 题解

## 作者：Register (赞：39)

### 题目大意
鸟要飞过树林，每次只能飞一段，长度有限制，停靠在树上

如果这棵树比刚才的矮，无论中间有多高的屏障，不用耗费体力，否则耗费体力$1$

问:最开始在树$1$，飞到树$n$，需要多少体力
### 解题思路
观察数据范围，明显是要$O(qn)$的算法

首先会每次询问分别处理，不难得到$dp$的状态转移方程

$$F_i=min(a_j>ai?f_j:f_j+1)$$

$j$在可以调到的距离内

这个算法是$O(qn^2)$的，肯定会$TLE$，考虑优化

我们可以发现每次要转移的区间是**连续且单调的**

因此可以使用单调队列优化

这个优化要考虑$2$个因素（满足前面的前提下再考虑后面的）

1. $F_i$单调不下降

2. $a_i$单调上升

- 还要记得一句话：**如果一个选手比你小，还比你强，你就可以退役了**，这句话很多单调队列都用得上

### 代码
```cpp
#include <cstdio>
int n,m,x,head,tail,a[1000001],q[1000001],f[1000001];
int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
int main(){
	n=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	m=read();
	while(m--)
	{
		x=read();head=tail=1;q[tail]=1;
		for(register int i=2;i<=n;i++)
		{
			while(head<=tail&&i-q[head]>x) head++;
			if(a[q[head]]>a[i]) f[i]=f[q[head]];
			else f[i]=f[q[head]]+1;
			while(head<=tail&&(f[q[tail]]>f[i]||(f[q[tail]]==f[i]&&a[q[tail]]<=a[i]))) tail--;
			q[++tail]=i;
		}
		printf("%d\n",f[n]);
	}
    return 0;
}
```


---

## 作者：Ofnoname (赞：25)

本蒟蒻学习单调队列DP时，由于太弱做不来难题，所以找到了这道，学什么都应该循序渐进。

每一个询问单独考虑，显然点`i`可能由`i-K`，`i-K+1`……`i-1`递推得到，方程为 $f[i] = min(f[j] + (a[j]\le a[i])),(max(1,i-K)\le j < i)$，可以得到50分。

```cpp
#include <bits/stdc++.h>
#define MAX (1000000 + 7)
using namespace std;

int N, K, T, a[MAX], f[MAX];

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	
	scanf("%d", &T); while (T--)
	{
		scanf("%d", &K);
		for (int i = 2; i <= N; i++)
		{
			f[i] = 1e9;
			for (int j = max(1, i-K); j < i; j++)
				f[i] = min(f[i], f[j] + (a[i] >= a[j]));
		}printf("%d\n", f[N]);
	}
}
```

我们发现每个点只从前K个点中选取答案，并且选取的是`f`的最小值（`f`一样则显然取`a`最大更好），每一次`i`往后移的左右边界变化很小。

这个模型正是单调队列裸题[P1440 求m区间内的最小值](https://www.luogu.org/problem/P1440)和[P1886 滑动窗口](https://www.luogu.org/problem/P1886)的模型。

我们可以用单调队列来维护前K个数里`f[i]`的最小值（`f[i]`一样则取`a[i]`最大值）。实时将超过长度限制（小于`i-K`）和无用（比`i`靠左并且f值还比`i`大）元素弹出并将`i`入队即可。

需要注意的是，`f[i]`不能用来更新自己，所以要先更新`f[i]`,再弹出无用元素，最后将`i`入队。

```cpp
#include <bits/stdc++.h>
#define MAX (1000000 + 7)
using namespace std;

int N, K, T, a[MAX], f[MAX];
int L, R, Q[MAX];

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	
	scanf("%d", &T); while (T--)
	{
		scanf("%d", &K), Q[L = R = 1] = 1;
		for (int i = 2; i <= N; i++)
		{
			while (L<=R && i-K>Q[L]) L++;
			f[i] = f[Q[L]] + (a[Q[L]] <= a[i]);
			while (L<=R && (f[Q[R]]>f[i] || (f[Q[R]]==f[i] && a[Q[R]]<=a[i]))) R--;
			Q[++R] = i;
		}printf("%d\n", f[N]);
	}
}
```

---

## 作者：asuldb (赞：17)

恩这道题其实本质上是个dp嘛

我们设f[i]表示到第i棵树时的最小体力花费，那么我们的答案就显而易见了，就是f[n]

那么比较暴力的O(n^2)思路就比较好想了，就是对于每棵树找他前面的树同时记录最小值就好了

我们看到n的范围很大，最大到1000000

再乘一个p，那么复杂度送你上天

那我们就需要单调队列优化了

我们可以看到我们刚才那种dp的思路中前面的状态和当前并没有什么关系，这就符合单调队列优化的条件了

我们要在单调队列记录的有三个量：坐标、高度和花费

那我们应该使那个量单调呢，显然是花费，我们应该保证在队列中花费从队首到队尾是单调递减的，这样从队首取出的花费就是最小的

但仅让花费单调就够了吗，显然是不够的，在花费相同时我们应该让高度保持单调，使高度大的在队列前端

也就是说我们要让队首是所有前面合法状态中花费最少且高度最高的，这样才可以使当前答案达到最优

于是我们在整个单调队列的单调机制是什么呢

那就是从队首到队尾花费保持单调递增，在花费相同时让高度保持从队首到队尾单调递减
同时注意判断队首的坐标是不是加上k也没法到达当前点，如果没有办法到达当前点，那就更无法到达之后的点，于是这样的队首直接弹出就好了

同时由于我太懒了，这里的单调队列是拿deque实现的，非常的丑，可能有些辣眼睛

上代码吧
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define re register
#define maxn 1000001
using namespace std;
struct node {
    int p,h,w;
};
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
      x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
int n,a[maxn],m,k,f[maxn];
inline void solve()
{

    memset(f,0,sizeof(f));
    deque<node> q;
    q.push_back((node){1,a[1],0});
    for(re int i=2;i<=n;i++)
    {
        bool flag=false;
        while(q.size()&&q.front().p+k<i) q.pop_front();
        if(q.front().h>a[i]) f[i]=q.front().w;
        else f[i]=q.front().w+1;
        while(q.size()&&f[i]<=q.back().w&&!flag)
        {
            while(q.size()&&f[i]==q.back().w&&!flag)
            {
                if(q.size()&&q.back().h<a[i]) q.pop_back();
                if(q.back().w<f[i]||q.back().h>=a[i]) flag=true;
            }
            if(flag) break;
            q.pop_back();
        }
        q.push_back((node){i,a[i],f[i]});
    }
    printf("%d",f[n]);
    putchar(10);
}
int main()
{
	//freopen("data.in", "r", stdin);
	//freopen("my.out", "w", stdout);
    n=read();
    for(re int i=1;i<=n;i++)
        a[i]=read();
    m=read();
    for(re int i=1;i<=m;i++)
    {
        k=read();
        solve();
    }
    return 0;
}
```

---

## 作者：right_cat (赞：9)

显然这道题可以用**贪心**做，而且**时间复杂度比用单调队列优化DP低得多**。

我们用d表示树的编号，假设小鸟现在在d[i]的树，在所有可飞跃的树中(d[i+1]~d[i+k])，按以下策略选择：

**优先考虑d[j]<d[i]的d[j],选择最大的d[j]，如果有多个d[j]最大，选择最大的j。**

**如果没有d[j]<d[i]的d[j]，只能考虑d[j]>=d[i]的d[j]，同样选择最大的d[j]，如果有多个d[j]最大，选择最大的j。**

贪心的正确性显然。

代码实现：
```cpp
#include <cstdio>
 
const int MAXN = 1000000;

//快读 
inline int read() {     
    int x = 0, f = 1;     
    char s;     
    while((s = getchar()) < '0' || s > '9')     
        if(s == '-')      
            f = -1;     
    while(s >= '0' && s <= '9')     
        x = (x << 3) + (x << 1) + (s ^ '0'), s = getchar();     
    return x * f;     
} 

//快输 
inline void write(int x) {  
    if(x < 0)   
        x = -x, putchar('-');  
    if(x / 10)  
        write(x / 10);  
    putchar(x % 10 + '0');  
} 
 
int n, q;
int d[MAXN + 5], k[MAXN + 5];
 
inline int answer(const int x) { //这里的x代表k[i] 
    int ans = 0; 
    int i = 1; //小鸟一开始的位置为1 
    while(true) {
        if(i + x >= n)  { //如果当前小鸟的位置可以直接飞到终点，由于不可能有比直接飞到终点的情况更优，所以直接飞到终点
            if(d[n] >= d[i]) //如果终点大于小鸟的位置，答案就加1 
                ++ans;
            break;
        }
        bool flag = true; //表示能否找到小于d[i]的d[j] 
        int maxn = 0, numn;
        for(int j = i + x; j > i; j--) { 
            if(d[j] < d[i]) {
                flag = false; //找到就把flag置为false 
                if(d[j] > maxn) //倒序找则不能取等，因为要求最大的j 
                    maxn = d[j], numn = j; //找到最大最远的小于d[i]的d[j] 
            }
        }
        if(flag) { //如果没有d[j]小于d[i] 
            int Max = 0, num;
            for(int j = i + x; j > i; j--)
                if(d[j] > Max)
                    Max = d[j], num = j; //找到最大最远的d[j] 
            ++ans; //没有d[j]小于d[i]，则答案必须加1 
            i = num; //将小鸟的位置变为符合策略的j 
        } else {
            i = numn; //同上 
        }
    }
    return ans; 
}
 
int main() {
    n = read();
    for(int i = 1; i <= n; i++)
        d[i] = read();
    q = read();
    for(int i = 1; i <= q; i++)
        k[i] = read(); //不喜欢边输入边输出，所以用数组存 
    for(int i = 1; i <= q; i++) {
        int ans = answer(k[i]); 
        write(ans), putchar('\n'); //输出答案 
    }
}
```

---

## 作者：nth_element (赞：8)

这道题实在是一道 **毒瘤** 题，太坑爹了。那个写 $deque$ 的题解亲测只有[80分](https://www.luogu.org/recordnew/show/16473401)，原因 **不言而明 **，这道题居然 ~~丧心病狂~~ 到 **卡STL** 。

***

好了，不吐槽了，进入正题

## 题目分析：

- 这是一道十分 **简单** 的DP，相信大家也可以很容易地吧DP状态转移方程给推出来。我就献丑给大家推一遍，如有错漏，请留言，谢谢。
- 我们可以定一个函数 $f(i)$ ,它表示跳到 $i$ 棵树上去的 $f(i)$  的劳累值。由题可知，可以 $i-v,i-v+1,i-v+2,......i-2,i-1$ 棵树上跳到 $i$ 棵树，所以可以推出DP状态转移方程 **$f(i)=min\{f(j)+(h(i)>=h(j))\},j\in[i-v,i)$**
- 时间复杂度： $\Theta(n^2)$ , 空间复杂度： $\Theta(n)$ 。

***

## code 1:

```cpp
#include<bits/stdc++.h>
#define Maxn 1000010
#define int long long
using namespace std;
int n;
int h[Maxn];
int p;
int f[Maxn];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&h[i]);
    }
    scanf("%lld",&p);
    while(p--)
    {
        memset(f,0,sizeof(f));
        int v;
        scanf("%lld",&v); 
        f[1]=0;
        for(int i=2;i<=n;i++)
        {
            int tmp=0x80000000;
            for(int j=i-v;j<i;j++)
            {
                tmp=min(tmp,f[j]+(h[i]>=h[j]));
            }
            f[i]=tmp;
        } 
        printf("%lld\n",f[n]);
    }
    return 0;
}
```

[记录：5AC，4RE，1TLE](https://www.luogu.org/recordnew/show/16579646)

***

## 优化 1：

我们考虑用**单调队列**优化,将其优化成 $\Theta(n)$ 。作为一个钟爱于STL的 Oler，我选择了方便而又快捷的 $deque$ 。

我们用单调队列维护 $f(j)+(h(i)>=h(j))$ 。维护 $f(j)$ ,将队列中 $f(j)$  **严格** 单调递减，使得队列中的 $f(j)$ 取出来时永远是最小的；在队尾的 $f(j)$ 相等时，我们还要将队列中的 $height(j)$ 进行维护，使得队列中的 $height(j)$ 单调递增，使得队列中的 $height(j)$ 的队首取出来永远是是最大的，使得 $(h(i)>=h(j))$ 尽量为0。

去头就简单了，假如 $j$ 是过期的数据，即 $j<i-v$ ,我们就把 $j$ 给 $pop$ 掉。

***

## code 2:

```cpp
#include<bits/stdc++.h>
#define Maxn 1000010
#define int long long
using namespace std;
int n;
int h[Maxn];
int p;
int f[Maxn];
struct node
{
    int id,v;
};
deque<node>dq;
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&h[i]);
    }
    scanf("%lld",&p);
    while(p--)
    {
        memset(f,0,sizeof(f));
        dq.clear();
        int v;
        scanf("%lld",&v); 
        dq.push_back((node){1,0});
        for(int i=2;i<=n;i++)
        {
            while(!dq.empty()&&dq.front().id<i-v)
            {
                dq.pop_front();
            }
            f[i]=dq.front().v+(h[i]>=h[dq.front().id]);
            while(!dq.empty()&&(dq.back().v>f[i]||(dq.back().v==f[i]&&h[i]>=h[dq.back().id])))
            {
                dq.pop_back();
            }
            dq.push_back((node){i,f[i]});
        } 
        printf("%lld\n",f[n]);
    }
    return 0;
}
```

[记录：8AC，2TLE](https://www.luogu.org/recordnew/show/16473088)

***

## 优化 2：

题目太过于 **毒瘤** ，卡掉了STL，使得STL惨遭TLE，所以我们考虑数组模拟 $deque$ 。

定义头指针 $head$ ，尾指针 $tail$ ，通过移动头尾指针，来模拟 $deque$ 。 $pop\_front$ 即为 $head++$ , $pop\_back$ 即为 $tail--$ 。我们很轻松就可以AC了。

注：


> STL好用是好用，但一定要注意STL的劣势，那就是在调用函数的时候比数组慢太多。一般来说，STL不会被卡；但难保有如此一道像这一道一样的毒瘤题呢？！

***



 ## code 3：

```cpp
#include<bits/stdc++.h>
#define Maxn 1000010
#define int long long
using namespace std;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int n;
int h[Maxn];
int p;
int f[Maxn];
struct node
{
    int id,v;
};
node que[Maxn];
signed main()
{
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(h[i]);
    }
    read(p);
    while(p--)
    {
        memset(f,0,sizeof(f));
        memset(que,0,sizeof(que));
        int v;
        read(v);
        que[1].id=1;
        que[1].v=0;
        int head=1;
        int tail=2;
        for(int i=2;i<=n;i++)
        {
            while(head<tail&&que[head].id<i-v)
            {
                head++;
            }
            f[i]=que[head].v+(h[i]>=h[que[head].id]);
            while(head<tail&&(que[tail].v>f[i]||(que[tail].v==f[i]&&h[i]>=h[que[tail].id])))
            {
                tail--;
            }
            que[++tail].id=i;
            que[tail].v=f[i];
        } 
        printf("%lld\n",f[n]);
    }
    return 0;
}
```

[记录：10AC](https://www.luogu.org/recordnew/show/16473849)

***


最后，给你一个 $struct$ 封装的 $deque$ 。

## code 4:

```cpp
#include<bits/stdc++.h>
#define Maxn 1000010
#define int long long
using namespace std;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int n;
int h[Maxn];
int p;
int f[Maxn];
int que_id[Maxn],que_v[Maxn];
struct dque
{
    int head,tail;
    dque()
    {
        head=1;
        tail=0;
    //	memset(que,0,sizeof(que));
    }
    inline bool empty()
    {
        return head>tail;
    }
    inline int front_id()
    {
        return que_id[head];
    } 
    inline int front_v()
    {
        return que_v[head];
    } 
    inline int back_id()
    {
        return que_id[tail];
    }
    inline int back_v()
    {
        return que_v[tail];
    }
    inline void pop_front()
    {
        head++;
    }
    inline void pop_back()
    {
        tail--;
    }
    inline void push_back(int id,int v)
    {
        que_id[++tail]=id;
        que_v[tail]=v;
    }
    inline void clear()
    {
        head=1;
        tail=0;
    }
}dq;
signed main()
{
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(h[i]);
    }
    read(p);
    while(p--)
    {
        memset(f,0,sizeof(f));
        dq.clear();
        int v;
        read(v);
        dq.push_back(1,0);
        for(int i=2;i<=n;i++)
        {
            while(!dq.empty()&&dq.front_id()<i-v)
            {
                dq.pop_front();
            }
            f[i]=dq.front_v()+(h[i]>=h[dq.front_id()]);
            while(!dq.empty()&&(dq.back_v()>f[i]||(dq.back_v()==f[i]&&h[i]>=h[dq.back_id()])))
            {
                dq.pop_back();
            }
            dq.push_back(i,f[i]);
        } 
        printf("%lld\n",f[n]);
    }
    return 0;
}
```

[记录：9AC，1TLE](https://www.luogu.org/recordnew/show/16475283)

***

# 如果作者有疏漏或错误的地方，请私信给我，或在评论中留言，谢谢。

---

## 作者：zqy1018 (赞：4)

要用单调队列这一点比较明显，DP也可以看得出来。

所以就是单调队列+DP。

保证单调队列里的元素相同体力消耗下靠近队首的高度尽量高即可，

相当于在维护队列体力消耗值从队首到队尾递增的基础上对高度进行递减的维护。

时间复杂度是O(Nq)。

```cpp
int n,a[1000005],m,d,que[1000005],f,r,dp[1000005];
void init(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
}
void solve(){
    m=read();
    while(m--){
        d=read();
        f=r=0;
        dp[1]=0,que[r++]=1;
        for(int i=2;i<=n;i++){
            while(r-f&&i-que[f]>d)f++;
            dp[i]=dp[que[f]]+(a[que[f]]<=a[i]);
            while(r-f&&(dp[que[r-1]]>dp[i]||(dp[que[r-1]]==dp[i]&&a[que[r-1]]<a[i])))
                r--;
            que[r++]=i;
        }
        printf("%d\n",dp[n]);
    }
}
```
仍然推销博客：[传送门](http://zqy1018.leanote.com/)


---

