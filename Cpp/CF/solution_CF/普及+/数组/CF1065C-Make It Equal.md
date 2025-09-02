# Make It Equal

## 题目描述

有一个由 $n$ 个塔组成的玩具建筑。每个塔由若干个立方体叠加而成。第 $i$ 个塔由 $h_i$ 个立方体组成，因此其高度为 $h_i$。

我们定义在某个高度 $H$ 上进行一次“切片”操作：对于每个塔 $i$，如果其高度大于 $H$，则移除顶部若干立方体，使该塔的高度变为 $H$。一次“切片”的代价等于所有塔中被移除立方体的总数。

如果一次切片的代价不超过 $k$（$k \ge n$），我们称其为一次“好切片”。

请计算，为了使所有塔的高度都相同，最少需要进行多少次好切片。可以保证一定可以做到。

## 说明/提示

在第一个样例中，最优方案是进行 $2$ 次切片。第一次在高度 $2$ 处切片（代价为 $3$），第二次在高度 $1$ 处切片（代价为 $4$）。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 5
3 1 2 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
2 3 4 5
```

### 输出

```
2
```

# 题解

## 作者：Blunt_Feeling (赞：7)

## CF1065C Make It Equal 题解
可以用前缀和来解。（~~哪来的树状数组~~

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)

由于 $1\le h_i\le 2$ · $10^5$，考虑到 $h_i$ 较小，可以先把所有 $h_i$ 都标记到一个桶里。回到题目中的这张图，不难发现，桶里的每个标记就可以表示为，在其高度及其以下高度都有一个方格。这样就可以利用桶的前缀和求出每个高度的方格个数。

接下来只需从上往下一层层遍历，每次加上一个前缀和，当前缀和的和超过 $k$ 时，把 $ans$ 加上 $1$ 就行了。但最后还有至关重要的一步：如果剩下没切走的方块个数还 $>n$，就要再把 $ans$ 再加上 $1$。不然就会像我之前一样[在第六个点WA](https://www.luogu.com.cn/record/35844360)。如果你不知道为什么，举个例子：

**输入：**
```cpp
5 30
2 1 18 18 2
```
标准输出为`2`，而如果不加这一句特判，就会输出`1`。

### Code
```
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
const int maxn=200050;
int n,k,h[maxn],sum[maxn],Min=0x3f3f3f3f,Max=0,tot[maxn],ans=0;
signed main()
{
	n=read(); k=read();
	For(i,1,n)
	{
		register int a=read();
		h[a]++;
		Min=min(Min,a); //找最大和最小值
		Max=max(Max,a);
	}
	Rep(i,Max,Min) sum[i]=sum[i+1]+h[i]; //前缀和
	int tot=0; //前缀和的和
	Rep(i,Max,Min)
	{
		if(tot+sum[i]>k)
		{
			ans++;
			tot=0; //tot归零不要忘
		}
		tot+=sum[i];
	}
	if(tot>n) ans++;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Zechariah (赞：3)

这题绝对没有省选/NOI-难度，我认为是一道树状数组模板
可以将这些数看成是堆起来的箱子数，我们可以处理出每一个高度有多少箱子，然后直接模拟  
因为显然切到最后，剩余的所有数都等于原序列中的最小值，所以原序列中的最小值min+1到原序列中的最大值max这一段里面的箱子都是要切掉的，可以从上往下直接模拟  
注意一些小细节：  
1）不要忘了处理最后可能的剩余，那是要花费一次切割的  
2）如果min==max，这时答案是0，不需要切，特判一下  

如何处理每个高度的箱子数呢？可以用树状数组  
具体看代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
const int N = 200010;
inline long long read()
{
    register long long num = 0;
    register char ch;
    register bool flag = false;
    while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
    if (ch == '-')flag = true; else num = ch ^ 48;
    while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
        num = num * 10 + (ch ^ 48);
    if (flag)return -num; return num;
}
long long c[N], maxn, minn = 1ll << 40, h[N];
inline void updata(register int x, register long long data)
{
    while (x <= maxn)
    {
        c[x] += data;
        x += lowbit(x);
    }
}
inline long long query(register int x)
{
    register long long ans = 0;
    while (x)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

int main()
{
    register int n = read(), k = read(), ans = 0;
    register long long sum = 0;
    for (register int i = 1; i <= n; ++i)
    {
        register long long x = read();
        h[i] = x;
        maxn = max(maxn, x);
        minn = min(minn, x);
    }
    for (register int i = 1; i <= n; ++i)
    {
        updata(1, 1);
        updata(h[i] + 1, -1);
    }
    register bool flag = true;
    if (maxn == minn){ printf("0");return 0; }
    for (register int i = maxn; i >= minn; --i)
    {
        register long long now = query(i);
        if (now + sum > k)
        {
            ++ans;
            sum = now;
            flag = false;
        }
        else
        {
            sum += now;
            flag = true;
        }
    }
    if (flag)++ans;
    printf("%d", ans);
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

# 简要题意

翻译很清楚。

# 思路

提供一种简单直接的思路。

可以发现最多会操作 $n$ 次。

那么就可以每次直接枚举切的高度 $h$，检查更改是否超过 $k$，之后暴力修改这一段，然后重复以上步骤。

但是直接这样做是 $\mathcal{O}(n^3)$。

发现需要维护区间和，那么就可以直接使用线段树维护，寻找比 $h$ 大的数可以使用二分（将原数组排序，在线段树上用单点查询二分），修改操作使用线段树推平，只修改比 $h$ 大的数**并不影响单调性**所以可以重复以上操作。

这样复杂度就是 $\mathcal{O}(n \log^3{n})$，因为需要单点查询所以多了一个 $\mathcal{O}(\log{n})$。

然后继续考虑优化。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/72zxz41d.png)

发现可以递推出切高度 $h$ 的贡献开始部分。

记录 $pos_i$ 为切高度 $i$ 时贡献开始的位置。

例如上图中，$pos_1 = 1,pos_2=2,pos_3=4,pos_4=5$。

切成高度 $h$ 后，$pos_i (i \in [1,h-1])$ 并不受影响。

然后复杂度就只有 $\mathcal{O}(n \log^2{n})$，顺利通过。

# code

```c++
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
#include <ctype.h>

using i64 = long long ;

const int N = 2e5 + 5 ;

char *p1,*p2,buf[1<<20];
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
inline i64 read(){
    i64 x=0,fh=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*fh;
}
void Write(i64 x){
    if(x>9)Write(x/10);
    putchar(x%10+'0');
}
inline void write(i64 x){
    if(x<0)putchar('-'),x=-x;
    Write(x);
}

int n;
i64 k;
i64 a[N],minn = 0x7fffffffff;

struct SegmentTree{
    int lazy[N<<2];
    i64 sum[N<<2];

    void build(int k = 1,int l = 1,int r = n) {
        if(l == r) {sum[k] = a[l];return;}

        int mid = l+r>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);

        sum[k] = sum[k<<1] + sum[k<<1|1];
    }

    void pushdown(int k,int l,int r) {
        if(!lazy[k]) return;

        int mid = l+r>>1;

        sum[k<<1] = (mid-l+1)*lazy[k];
        sum[k<<1|1] = (r-mid) * lazy[k];

        lazy[k<<1] = lazy[k];
        lazy[k<<1|1] = lazy[k];

        lazy[k] = 0;
    }

    i64 QuerySum(int k,int l,int r,int x,int y) {
        if(x <= l && r <= y) return sum[k];

        pushdown(k,l,r);

        int mid = l+r>>1;

        i64 val = 0;

        if(x <= mid)
            val += QuerySum(k<<1,l,mid,x,y);
        if(y > mid)
            val += QuerySum(k<<1|1,mid+1,r,x,y);
        
        return val;
    }

    void change(int k,int l,int r,int x,int y,i64 val) {
        if(x <= l && r <= y) {
            sum[k] = (r-l+1)*val;
            lazy[k] = val;
            return;
        }

        pushdown(k,l,r);

        int mid = l+r>>1;

        if(x <= mid)
            change(k<<1,l,mid,x,y,val);
        if(y > mid)
            change(k<<1|1,mid+1,r,x,y,val);

        sum[k] = sum[k<<1] + sum[k<<1|1];
    }
}t;//优化1 线段树

int pos[N];
bool check(int mid){
    
    int x = pos[mid];

    if(x == n+1) return 1;

    return t.QuerySum(1,1,n,x,n) - (i64)mid * (n-x+1) <= k;
}

int main(){
    
    n=read(),k=read();

    for(int i = 1; i <= n; i++) {
        a[i] = read();
        minn = std::min(minn,a[i]);//最后所有数一定是最小的
    }

    std::sort(a+1,a+n+1);

    for(int i = 1; i <= n; i++)
        if(pos[a[i]]) pos[a[i]] = std::min(pos[a[i]],i);//注意细节
        else pos[a[i]] = i;

    for(int i = 200000; i; i--)
        if(!pos[i]) pos[i] = pos[i+1]; // 记录切高度i时贡献从哪开始
    
    t.build();

    int ans = 0;
    while(true) {
        
        if(t.QuerySum(1,1,n,1,n) == minn * n) break;

        int l = minn, r = 200000;
        int x = -1;

        while(l <= r) {
            int mid = l+r>>1;

            if(check(mid)) r = mid-1,x=mid;
            else l = mid+1;
        }

        if(x == -1) break;

        ans++;
        
        t.change(1,1,n,pos[x],n,x);//区间推平操作
    }
    
    write(ans);
    return 0;
}
```

---

## 作者：MY_Lee (赞：2)

#### 闲聊
> 暴力碾标算，$n^2$ 过百万。

这句话在这题里还真有点灵验了。

---
#### 思路

我们看到题目中 $n\le2e5$ 的数据，肯定首选 $O(n\log n)$ 的算法(或许还有更牛的？)。

但是这里介绍一种复杂度大约为 $O(h+n)$，其中 $h$ 为序列中的最大数，下同。这样的一种**暴力**。虽然常数可能较大，但是足以 AC。

---
前置芝士：
1. 语言基础
1. 差分

---
先来讲讲 $O(h)$ 的预处理。

我们要统计出 $tong_{1\cdots n}$，其中 $tong_i$ 表示在序列中有几个大于 $i$ 的数。

我们可以在读入的时候，每输入序列的一个数，就把 $tong_1$ 到 $tong_{a_i}$ 全部加一。

显然暴力去做是 $O(nh)$，最大可达到 $4\times10^{10}$，原地起飞。

~~我不灰心！我不气馁！~~

考虑用神奇的差分来优化。

每输入一个数，只需把 $tong_1$ 加一，把 $tong_{a_i+1}$ 减一就可以了。原理这里不详细介绍了，想了解的同学可以自行百度。

于是时间直接被拉到 $O(2n)$，轻松卡进时限。

献上代码：
```cpp
for(register int i=1;i<=n;i++){
	scanf("%d",&x);//读入
	mx=mx>x+1?mx:x+1;
	mn=mn<x?mn:x;//预处理出最大值和最小值
	tong[1]++;
	tong[x+1]--;//差分
}
for(register int i=1;i<=mx;i++){
	tong[i]+=tong[i-1];
}//做完差分，它只是一个半成品，要把它前缀和。
```

---
接着是主(da)程(bao)序(li)：

有了预处理，这一部分就简单的直接掉橙。

看完题目，可以得出一条很简单的结论：最优解总是使序列中的每个数都等于原来的最小数。

我们可以用贪心的思想，从最大的数开始，如果把 $H$ 设在这个数 $x$ 可以，那就设在 $x$ 上；否则就设在 $x+1$ 上，同时 $ans+1$。如果现在已经是最小值了，那就直接输出，结束程序。

具体看代码吧：

```cpp
now=mx-1;//这里因为我上面求得的是 mx+1，所以这里要减一
while(now>mn){//如果还要继续操作
	int sum=0;//累计变化量
	while(sum+tong[now]<=k&&now>mn){//如果 H 还能往下走
		sum+=tong[now];
		now--;//就尽量往下走，统计更新变化量
	}
	ans++;//操作次数更新
}
```
---
总时间复杂度大概是 $O(2n+2h)$，比较快。

- 如果你不信，你可以[戳我](https://www.luogu.com.cn/record/32214211)

- 如果你还不信，你可以在最优解第 $42$ 名找到我。不要嫌名次低，这只是个**暴力**啊。

---
#### 番外

不知道写什么，那就[谢谢大家观看！](https://moon-snow.blog.luogu.org)

---

## 作者：bztMinamoto (赞：2)

本来以为高度都是$1e9$级别的……然后冥思苦想了一个可行做法……结果发现高度只有$2e5$级别……那不就是个水题么……

还是说一下我的做法吧……

考虑一下，如果竖着分割，那么相当于是原来的数组，那么如果我们按高度横着分割，每一层都有一定数量的点，那么题目就相当于每一次从最上层开始取连续的几层，且每一次取得总点数不超过$K$

这个东西肯定是贪心的，能多取就多取，而且发现如果按这样分割的话每一层的点数不会超过$n$，且点数是递增的

那么我们可以开一个桶，$cnt[i]$表示点数为$i$的总共有多少层，那么同一组内我们可以直接算出不超过$k$的话一次最多取多少，设为$t=i/k$，那么$res+=cnt[i]/t$

然后我们这样是整除的，所以每一层还会有剩下的，又因为我们取得时候必须先取完点数小的再取点数大的，所以记一个$add$表示前面还留了多少贡献，然后在1计算上面每一层取多少次之前先判断一下$add$要取掉多少就行了

然后记得最后如果$add$还有值的话要$++res$
```
//minamoto
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=2e5+5;
int cnt[N],a[N],n,res;ll add=0,k,p;
inline bool cmp(int a,int b){return a>b;}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<n;++i) cnt[i]=a[i]-a[i+1];
	for(int i=1;i<n;++i){
		if(add+1ll*i*cnt[i]<=k) add+=1ll*i*cnt[i];
		else{
			p=(k-add)/i,cnt[i]-=p,++res,add=0;
			p=k/i,res+=cnt[i]/p,cnt[i]%=p;
			add=1ll*cnt[i]*i;
		}
	}
	if(add) ++res;
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：Fan_Tuan (赞：0)

# 题意
给你 $n$ 堆正方体 , 每堆正方体由一些正方体组成 , 每次可以沿着某一高度切一刀 , 这个高度之上的正方体会被砍掉 , 要求每次砍掉的正方体不超过  $k$ 。
# 思路
首先可以桶排序 , 高度从高到低统计出每种高度正方体高度的个数 , 之后从高到低贪心的看是不是能砍即可 。（要注意不需要砍的情况）

# 代码
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;

const int maxn = 4e5 + 5;
int n, k, a[maxn], b[maxn], sum[maxn];
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + 1 + n);
	if (a[1] == a[n]) {
		printf("0");
		return 0;
	}
	int pos = 1;
	for (int i = 1; i <= n; i++) {
		while (pos <= 200000 && pos <= a[i]) {
			sum[pos] = (n - i + 1);
			pos++;
		}
	}
	for (int i = 1; i <= 200000; i++) b[i] = sum[200000 - i + 1];
	pos = 1;
	int ans = 0, cnt = 0;
	while (pos <= 200000) {
		if (cnt + b[pos] <= k) {
			cnt += b[pos];
			pos++;
			if (pos == 200001) ans++;
		}
		else {
			ans++;
			if (b[pos] == n) break;
			cnt = b[pos];
			pos++;
		}
	}
	printf("%lld", ans);
	return 0;
}
```


---

