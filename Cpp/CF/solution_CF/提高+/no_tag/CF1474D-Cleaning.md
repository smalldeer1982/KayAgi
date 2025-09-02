# Cleaning

## 题目描述

During cleaning the coast, Alice found $ n $ piles of stones. The $ i $ -th pile has $ a_i $ stones.

Piles $ i $ and $ i + 1 $ are neighbouring for all $ 1 \leq i \leq n - 1 $ . If pile $ i $ becomes empty, piles $ i - 1 $ and $ i + 1 $ doesn't become neighbouring.

Alice is too lazy to remove these stones, so she asked you to take this duty. She allowed you to do only the following operation:

- Select two neighboring piles and, if both of them are not empty, remove one stone from each of them.

Alice understands that sometimes it's impossible to remove all stones with the given operation, so she allowed you to use the following superability:

- Before the start of cleaning, you can select two neighboring piles and swap them.

Determine, if it is possible to remove all stones using the superability not more than once.

## 说明/提示

In the first test case, you can remove all stones without using a superability: $ [1, 2, 1] \rightarrow [1, 1, 0] \rightarrow [0, 0, 0] $ .

In the second test case, you can apply superability to the second and the third piles and then act like in the first testcase.

In the third test case, you can apply superability to the fourth and the fifth piles, thus getting $ a = [2, 2, 2, 3, 1] $ .

In the fourth test case, you can apply superability to the first and the second piles, thus getting $ a = [1900, 2100, 1600, 3000, 1600] $ .

## 样例 #1

### 输入

```
5
3
1 2 1
3
1 1 2
5
2 2 2 1 3
5
2100 1900 1600 3000 1600
2
2443 2445```

### 输出

```
YES
YES
YES
YES
NO```

# 题解

## 作者：45dino (赞：15)

有一个更易懂，更巧妙的做法：

假如不能使用 ```superability```，如何进行判断？

从左往右扫一遍，进行“模拟操作”，并不难。

没听懂的朋友请看如下例子

比如，对于数列 $[1,4,6,1,2]$：
- 对于第二个数，前面剩下 $1$，所以剩下 $4-1=3$
- 对于第三个数，前面剩下 $3$，所以剩下 $6-3=3$
- 对于第四个数，前面剩下 $3$，而 $1<3$，所以一定不行，记为 $-1$
- 对于第五个数，前面已经记为 $-1$，所以接着记为 $-1$
- 所以这个数列无法全部被消去

如果使用```superability```，交换相邻两个，设为第 $x$ 个和第 $x+1$ 个，那么对于 $[1,x-1]$ 与 $[x+2,n]$ ，设两个数列分别剩下 $p$ 和 $q$ ，则 $p-a_y=q-a_x$，即经过交换后的四个数可以被消去。

枚举 $x$，进行判断即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=0;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
    return (flag?x:~(x-1));
}
int t,n,flag,a[200001],b[200001],c[200001];
signed main()
{
	t=read();
	while(t--)
	{
		flag=0;
		n=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			b[i]=c[i]=0;
		}
		c[n+1]=0;
		for(int i=1;i<=n;i++)
			b[i]=a[i]>=b[i-1]&&b[i-1]!=-1?a[i]-b[i-1]:-1;
		for(int i=n;i>=1;i--)
			c[i]=a[i]>=c[i+1]&&c[i+1]!=-1?a[i]-c[i+1]:-1;
		if(!b[n])
		{
			puts("YES");
			continue;
		} 
		for(int i=1;i<n;i++)
			if(b[i-1]!=-1&&c[i+2]!=-1&&b[i-1]<=a[i+1]&&c[i+2]<=a[i]&&a[i+1]-b[i-1]==a[i]-c[i+2])
			{
				puts("YES");
				flag=1;
				break;
			}
		if(!flag)
			puts("NO");
	}
	return 0;
}

```


---

## 作者：Graphcity (赞：4)

[更好的阅读体验](https://www.luogu.com.cn/paste/731uvea7)

### 思路

如果 $a$ 数组可以清空，则必须满足下面的 $n$ 个不等式：

$$
\begin{matrix}
a_1\ge 0 \\
a_2-a_1 \ge 0 \\
a_3-a_2+a_1\ge 0 \\
\cdots \\
a_n-a_{n-1}+a_{n-2}-\cdots =0 \\
\end{matrix}
$$

接着，我们把这 $n$ 个式子按照奇偶分类：

$$
\begin{matrix}
a_1\ge 0 \\
a_1-a_2+a_3\ge 0 \\
a_1-a_2+a_3-a_4+a_5\ge 0 \\
\cdots
\end{matrix}
$$

$$
\begin{matrix}
-a_1+a_2\ge 0 \\
-a_1+a_2-a_3+a_4\ge 0 \\
-a_1+a_2-a_3+a_4-a_5+a_6\ge 0 \\
\cdots
\end{matrix}
$$

可以发现，同一类的数，下标相同，对应的符号也相同。我们就可以用线段树 **批量修改一个数的值** 了。在一类不等式中，区间 $[l,r]$ 所表示的线段树结点维护那一类不等式 $[l,r]$ 范围中不等号左边的最小值。于是，整个问题就可以化为线段树的区间修改和区间查询操作。时间复杂度 $O(n \log n)$ 。

### 代码

```cpp
#include<bits/stdc++.h>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,flag,n,s1,s2,num[Maxn+5];
int a1[Maxn+5],a2[Maxn+5];

struct Node // 线段树
{
    int t[Maxn*4+5],tag[Maxn*4+5],num[Maxn+5];
    inline void push_up(int p) {t[p]=min(t[ls(p)],t[rs(p)]);}
    inline void push_down(int p)
    {
        t[ls(p)]+=tag[p],tag[ls(p)]+=tag[p];
        t[rs(p)]+=tag[p],tag[rs(p)]+=tag[p];
        tag[p]=0; return;
    }
    inline void Build(int l,int r,int p)
    {
        tag[p]=0;
        if(l==r) {t[p]=num[l]; return;}
        int mid=(l+r)>>1;
        Build(l,mid,ls(p)),Build(mid+1,r,rs(p));
        push_up(p);
    }
    inline void Update(int nl,int nr,int l,int r,int p,int k)
    {
        if(l<=nl && nr<=r) {t[p]+=k,tag[p]+=k; return;}
        int mid=(nl+nr)>>1;
        push_down(p);
        if(l<=mid) Update(nl,mid,l,r,ls(p),k);
        if(r>mid) Update(mid+1,nr,l,r,rs(p),k);
        push_up(p);
    }
    inline int Count(int nl,int nr,int l,int r,int p)
    {
        if(l<=nl && nr<=r) return t[p];
        int mid=(nl+nr)>>1,res=INT_MAX;
        push_down(p);
        if(l<=mid) res=min(res,Count(nl,mid,l,r,ls(p)));
        if(r>mid) res=min(res,Count(mid+1,nr,l,r,rs(p)));
        push_up(p);
        return res;
    }
} tr1,tr2;

inline int Check() // 判断是否能够清空
{
    int now=min(tr1.Count(1,s1,1,s1,1),tr2.Count(1,s2,1,s2,1));
    if(now<0) return 0;
    if(n%2==1 && tr1.Count(1,s1,s1,s1,1)) return 0;
    if(n%2==0 && tr2.Count(1,s2,s2,s2,1)) return 0;
    return 1;
}
inline void Change(int pos,int val) // 将位置为 pos 的数加上 val
{
    if(pos&1)
    {
        int p1=(pos+1)/2;
        tr1.Update(1,s1,p1,s1,1,val);
        if(pos!=n) tr2.Update(1,s2,p1,s2,1,-val);
    }
    else
    {
        int p1=pos/2;
        if(pos!=n) tr1.Update(1,s1,p1+1,s1,1,-val);
        tr2.Update(1,s2,p1,s2,1,val);
    }
}

int main()
{
    T=read();
    while(T--)
    {
        n=read(),flag=0;
        for(int i=1;i<=n;++i) num[i]=read();
        for(int i=1;i<=n;++i) // 求出每个不等式等号左边的值
        {
            if(i&1) a1[i/2+1]=num[i]-a2[i/2];
            else a2[i/2]=num[i]-a1[i/2];
        }
        s1=(n+1)/2,s2=n/2;
        for(int i=1;i<=s1;++i) tr1.num[i]=a1[i];
        for(int i=1;i<=s2;++i) tr2.num[i]=a2[i];
        tr1.Build(1,s1,1),tr2.Build(1,s2,1);
        if(Check()) {printf("YES\n"); continue;}
        for(int i=2;i<=n;++i)
        {
            Change(i,num[i-1]-num[i]),Change(i-1,num[i]-num[i-1]);
            // 相当于交换两数
            if(Check()) {printf("YES\n"); flag=1; break;}
            Change(i,num[i]-num[i-1]),Change(i-1,num[i-1]-num[i]);
        }
        if(!flag) printf("NO\n");
    }
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

挺有意思的一道题。

------------

看了官方题解的一个提示：考虑第 $1$ 个点只有一种转移。

于是想到贪心，从前往后遍历，每次用后一个减去前一个，如果不够减，不得不换顺序然后削，如果需要不止一次的换顺序，那就无解。

由于前后顺序影响，再反过来从 $n$ 到 $1$ 跑一遍。

但以上策略只够通过样例。

它一定会把换相邻两个数的机会用在第一个出现不行的位置，而实际上如果用在后面，可能可以同时解决两个无法消掉的问题。

暂时没想到如何继续贪心。

于是，用更加暴力的方法——枚举交换位置。

首先得预处理出从前往后以及从后往前两种方式能消掉的最长距离。同时记录 $ansl_i$ 和 $ansr_i$，分别表示从前往后以及从后往前第 $i$ 个位置与前一个消完剩下的数。

再枚举交换位置时，如果左边一个往前两个，和右边一个往后两个都在可直接消掉的范围内，考虑交换。

如果交换的为 $a_i$ 和 $a_{i+1}$，当且仅当 $ansl_{i-1}-a_{i+1}=ansr_{i+2}-a_i$，可以消完。

输出答案即可，复杂度 $\operatorname{O}(n)$。

------------

想和调整整用了一晚上。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int T,n,a[maxn],ansl[maxn],ansr[maxn];
inline void q(int *x){
    for(int i=2;i<=n;i++){
        if(!x[i-1]){
            x[n+10]=i-1;
            continue;
        }
        if(x[i]>=x[i-1])
            x[i]-=x[i-1];
        else{
            x[n+23]=1;
            x[n+10]=i-2;
            return ;
        }
    }
    x[n+10]=n;
    return ;
}
inline bool check(){
    for(int i=1;i<n;i++)
        if(i-2<=ansl[n+10]&&i+3>=ansr[n+10]&&ansl[i-1]<=a[i+1]&&ansl[i-1]-a[i+1]==ansr[i+2]-a[i])
            return 1;
    return 0;
}
int main(){
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++)
            ansl[i]=ansr[n-i+1]=a[i]=read();
        ansl[n+10]=ansr[n+10]=ansl[n+23]=ansr[n+23]=0;
        q(ansl);
        q(ansr);
        if(!ansl[n+23]&&!ansl[n]||!ansr[n+23]&&!ansr[n]){
            puts("Sherry");
            continue;
        }
        reverse(ansr+1,ansr+n+1);
        ansr[n+10]=n-ansr[n+10]+1;
        puts(check()?"Sherry":"cayh");
    }
    return 0;
}
```


---

## 作者：RyexAwl (赞：3)

令$a\_times[i]$为第$i$堆与第$i-1$堆进行操作的次数，$b\_times[i]$为第$i$堆和第$i+1$堆进行的操作次数。

因为要满足最后每堆个数均为$0$，因此$\forall1\le i\le n,a\_times[i]+b\_times[i]=a[i]$，且$a\_times[i]=b\_times[i-1]$。

而且我们要满足$b\_times[1]=a[1],a\_times[n]=a[n]$。

这样一来，我们合法的$a\_times,b\_times$都是唯一确定的，且要满足对于任一的$a\_times,b\_times$均要大于等于$0$。

而对于其$a\_times,b\_times$我们发现我们可以从左往右递推或者从右往左递推。

而且因为$a\_times[i]+b\_times[i]=a[i],a\_times[i]=b\_times[i-1]$，因此如果确定了其中的任意一个，另一个一定是可以唯一确定的。我们不妨从左往右依次确定$b\_times[i]$记作$pre[i]$，从右往左依次确定$a\_times[i]$记作$suf[i]$。

我们发现如果要令两次确定的$a\_times[i]$和$b\_times[i]$均一致，当且仅当$\forall 1\le i\le n,pre[i]=suf[i+1]$。

且我们发现上述等式是具有传递性的，即如果我们找到一个位置满足$pre[i]=suf[i+1]$，那么其所有位置一定满足这个性质。

但是我们发现我们从左往右递推的结果和从右往左递推的结果有可能并不是唯一确定的，如果不允许交换那么其必然是不合法的，但是我们现在允许交换那么我们直接枚举交换位置即可。

```cpp
#include <iostream>

namespace wxy{
    #define int long long
    const int N = 2e5 + 50,inf = 1e18;
    int a[N],pre[N],suf[N];
    void main(){
        int t; std::cin >> t;
        while (t--){
            int n;std::cin >> n;
            for (int i = 1; i <= n; i++) std::cin >> a[i];
            suf[n + 1] = pre[0] = 0;
            for (int i = 1; i <= n; i++){
                if (a[i] - pre[i - 1] >= 0) pre[i] = a[i] - pre[i - 1];
                else pre[i] = inf;
            }
            for (int i = n; i >= 1; i--){
                if (a[i] - suf[i + 1] >= 0) suf[i] = a[i] - suf[i + 1];
                else suf[i] = inf / 2;
            }
            bool check = false;
            for (int i = 1; i <= n - 1; i++){
                if (pre[i] == suf[i + 1]){
                    check = true;
                    break;
                }else{
                    int x = a[i],y = a[i + 1];
                    if (y - pre[i - 1] >= 0 && x - suf[i + 2] >= 0){
                        if (y - pre[i - 1] == x - suf[i + 2]){
                            check = true;
                            break;
                        }
                    }
                }
            }
            if (check) std::cout << "YES" << std::endl;
            else std::cout << "NO" << std::endl;
        }
    }
}signed main(){wxy::main();return 0;}
```


---

## 作者：mango2011 (赞：1)

有趣的贪心题。

由于题目的限制，我们发现从两侧往中间贪心消除的办法显然不劣。从左到右，比如遇到了两个数 $x,y$ 如果 $x>y$ 则显然无法消除；否则直接变成 $0,y-x$；从右往左做法是类似的。

于是我们可以维护 $L_i,R_i$，表示分别从 $i$ 开始（结尾）从前（后）消除能够得到的数（可以用 $-1$ 表示不可能）。

如果不交换无法完成任务，那么我们考虑枚举交换的位置 $i$（$a_i$ 与 $a_{i+1}$ 交换，注意范围），然后发现会得到四个数：$L_{i-1},a_{i+1},a_i,R_{i+2}$，判断四个数是否满足条件是简单的。

下面给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
const int maxn=2e5+10;
int a[maxn];
int l[maxn],r[maxn];
bool chk2(int x,int y){
	return x==y;
}
bool chk3(int x,int y,int z){
	if(x>y){
		return 0;
	}
	return chk2(y-x,z);
}
bool chk4(int x,int y,int z,int w){
	if(x>y){
		return 0;
	}
	return chk3(y-x,z,w);
}
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=0;i<=n+5;i++){
		l[i]=0;
		r[i]=0;
	}
	l[1]=a[1];
	for(int i=2;i<=n;i++){
		if(l[i-1]==-1){
			l[i]=-1;
			continue;
		}
		if(l[i-1]>a[i]){
			l[i]=-1;
		}
		else{
			l[i]=a[i]-l[i-1];
		}
	}
	r[n]=a[n];
	for(int i=n-1;i>=1;i--){
		if(r[i+1]==-1){
			r[i]=-1;
			continue;
		}
		if(r[i+1]>a[i]){
			r[i]=-1;
		}
		else{
			r[i]=a[i]-r[i+1];
		}
	}
	if(l[n]==0){
		cout<<"YES"<<endl;
		return;
	}
	for(int i=1;i<n;i++){
		if(l[i-1]!=-1&&r[i+2]!=-1){
			if(chk4(l[i-1],a[i+1],a[i],r[i+2])){
				cout<<"YES"<<endl;
				return;
			}
		}
	}
	cout<<"NO"<<endl;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL); 
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：MatrixCascade (赞：1)

当时比赛的时候很 naive，码了快 30 分钟的线段树发现可以维护前后缀去做。。思索了一下感觉线段树码量很大，我可能调不出来。于是我删掉打了一大半的线段树，10 分钟惊险码完。

我们考虑开 2 个数组，$b[i]$ 表示 $1\to i-1$ 的数全消掉了，i 还剩下多少。$c[i]$ 表示 $i+1\to n$ 的数全消掉了，i 还剩下多少。

还需要 2 个辅助数组 $f1$,$f2$，表示 $1\to i$($i \to n$)之间有没有 $b[i]$($c[i]$)小于 0 的，如果有就设为 1。

然后依次枚举每一个 i($1\to n-1$)，然后枚举交换或不交换，注意，这里如果有 $f1[i-1]=1$ 或 $f2[i+2]=1$ 直接 continue（不可行）

判断也非常容易，$if(a[i]-b[i-1]==a[i+1]-c[i+2])$ 或者$if(a[i+1]-b[i-1]==a[i]-c[i+2])$，并且等式左右两边都大于 0 的时候，就是可行的解。

后记：pp 后 10 分钟发现我没开 ll，所以 resub 了，然后 **System Testing的时候我发现我数组没清空，心态当场爆炸**

~~最后发现我没 fst /cy/cy~~

赛后代码（格式化过的）：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T;
const int maxn = 4e5 + 10;
int n, m, a[maxn];
int b[maxn], c[maxn];
int f1[maxn], f2[maxn];
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        b[0] = b[n + 1] = c[0] = c[n + 1] = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &a[i]);
            b[i] = a[i];
            c[i] = a[i];
            f1[i] = f2[i] = 0;
        }
        for (int i = 1; i <= n; ++i)
        {
            b[i + 1] -= b[i];
            if (b[i] < 0)
                f1[i] = 1;
            f1[i + 1] |= f1[i];
        }
        if (f1[n] == 0 && b[n] == 0)
        {
            puts("YES");
            continue;
        }
        for (int i = n; i >= 1; --i)
        {
            c[i - 1] -= c[i];
            if (c[i] < 0)
                f2[i] = 1;
            f2[i - 1] |= f2[i];
        }
        int ff = 0;
        for (int pos = 1; pos < n; ++pos)
        {
            int pos2 = pos + 1;
            int x1 = b[pos - 1], x2 = c[pos2 + 1];
            //cout<<x1<<" "<<x2<<endl;
            if (f1[pos - 1] == 1 || f2[pos2 + 1] == 1)
            {
                continue;
            }
            if (a[pos] - x1 == a[pos2] - x2)
            {
                //cout<<pos<<endl;
                if (a[pos] - x1 >= 0)
                {
                    ff = 1;
                    break;
                }
            }
            if (a[pos2] - x1 == a[pos] - x2)
            {
                //cout<<pos<<endl;
                if (a[pos2] - x1 >= 0)
                {
                    ff = 1;
                    break;
                }
            }
        }
        if (ff)
        {
            puts("YES");
        }
        else
        {
            puts("NO");
        }
    }
    return 0;
}

```


---

## 作者：pengyule (赞：1)

看了赛后题解半晌没懂，寻思那个题解的思路不大适合我，然后我又自己推导了一个小时，终于推出来了，好不容易调好了代码考虑完了所有的疏漏，写篇题解庆祝一下。

# Editorial

来探究一下要成功的话 $a_1,a_2,\cdots,n$ 应该满足什么条件。

1. $a_n-(a_{n-1}-(\cdots-(a_2-a_1)))=0$，所以 $a_n-a_{n-1}+a_{n-2}-\cdots=0$，所以 $a_1+a_3+\cdots=a_2+a_4+\cdots$，即 $\sum{a_{odd}}=\sum a_{even}$。如果 $swap(a_x,a_y)(y=x+1)$，那么得到 $\begin{cases}
\sum{a_{odd}}+\Delta=\sum a_{even}-\Delta(x\ is\ odd) \\
\sum{a_{even}}+\Delta=\sum a_{odd}-\Delta(x\ is\ even) 
\end{cases}$，其中记 $\Delta=a_y-a_x$。
2. 不等式组 $S=\begin{cases}
a_2-a_1\geq 0\\
a_3-(a_2-a_1)\geq0\\
\cdots\\
a_n-(a_{n-1}-(\cdots-(a_2-a_1)))\geq0\end{cases}$ $\to S=\begin{cases}
a_2\geq a_1\\
a_1+a_3\geq a_2\\
\cdots\\\end{cases}$。下面考虑 $x$ 为奇数的情况：如果 $swap(a_x,a_y)(y=x+1)$，那么 $ \begin{cases}
a_1\\
a_1+a_3\\
\cdots\\\end{cases}$ 都要 $+\Delta$，$\begin{cases}
a_2\\
a_2+a_4\\
\cdots\\\end{cases}$ 都要 $-\Delta$，因此 $S$ 中不等式 $a_1+a_3+\cdots a_x\geq a_2+a_4+\cdots+a_{y-2}(1)$ 左边 $+\Delta$，它以后的所有不等式左右两边，如果是奇数项和的式子则 $+\Delta$，如果是偶数项和的式子则 $-\Delta$，它之前的所有不等式不作变化。如果用 $b_1,b_2,\cdots,b_{k}$ 依次表示 $S$ 中的不等式左边与右边的差，那么少加思考就能发现，$k=n-1$，不等式 $(1)$ 对应的值是 $b_{x-1}$。当不等式组成立再加推导，得到：对于 $b_x,b_{x+2},\cdots$，应满足 $b\geq 2\Delta$，即 $\Delta\leq\dfrac{\min\{b_x,b_{x+2},\cdots\}}{2}$；对于 $b_y,b_{y+2},\cdots$，应满足 $b\geq-2\Delta$，即 $\Delta\geq-\dfrac{min\{b_y,b_{y+2},\cdots\}}{2}$，而 $(1)$ 应满足 $\Delta\geq-b_{x-1}$，又因为 $b_{1\sim x-2}$ 是不变的，所以它们应该都 $\geq 0$。\
当 $x$ 为偶数时，同理，这里不加赘述了。

综合上述，得出代码。

```
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
const long long inf=1e17;
using namespace std;
long long a[200005],b[200005],minb[200005];
bool solve(int n){
	if(n==1) return false;
	if(n==2) return a[1]==a[2];
	long long sumodd=0,sumeven=0;
	for(int i=1;i<=n;i+=2) sumodd+=a[i];
	for(int i=2;i<=n;i+=2) sumeven+=a[i];
	b[1]=a[2]-a[1];
	int k=1;
	for(int i=3,j=2;i<=n && j<=n;){
		if(k&1) b[k+1]=a[i]-b[k],k++,j+=2;
		else b[k+1]=a[j]-b[k],k++,i+=2;
	}
	minb[k]=b[k];
	for(int i=k-2;i>=1;i-=2) minb[i]=min(b[i],minb[i+2]);
	minb[k-1]=b[k-1];
	for(int i=k-3;i>=1;i-=2) minb[i]=min(b[i],minb[i+2]);
	if(sumodd==sumeven && minb[1]>=0 && minb[2]>=0) return true;
	b[0]=inf,minb[n]=inf;
	for(int i=1;i<=n-1;i++){
		if(i>=3 && b[i-2]<0) break;
		if(1.0*(a[i+1]-a[i])<=minb[i]/2.0 && (a[i+1]-a[i])*1.0>=max(-b[i-1]*1.0,-minb[i+1]/2.0)){
			
			if((i&1) && sumodd+a[i+1]-a[i]==sumeven-a[i+1]+a[i]) return true;
			if(!(i&1) && sumeven+a[i+1]-a[i]==sumodd-a[i+1]+a[i]) return true;
		}
	}
	return false;
}

int main()
{
	int T,n;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(solve(n)) cout<<"YES"<<endl;
		else {
			for(int i=1;i<=n/2;i++) swap(a[i],a[n-i+1]);
			if(solve(n)) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
} 

```

---

## 作者：冷却心 (赞：0)

给题解区贡献一份赤石垃圾题解。做法较为复杂。这做法我写了 10min 调了 1h，/tuu。

先考虑如何判定一个序列是否合法。容易发现这个操作顺序无关，很平凡，所以我们从前往后扫一遍做该操作，最后看序列里面是否存在孤立的正整数即可。形式化的，我们设 $a'_i$ 表示对前缀 $i$ 做完操作之后 $a_i$ 变成多少了，那么我们对 $i,i+1$ 的操作就形如：$a'_i \gets a'_i - \min\{a'_i, a_{i+1}\},a_{i+1} \gets a_{i+1} - \min\{a'_i,a_{i+1}\}$。此时如果 $a'_i$ 依然非零，那么它就成为了孤立点，也就是当 $a'_i > a_{i+1}$ 的时候非法。并且我们还要求 $a'_n=0$，即 $a'_{n-1}=a_n$。

能发现对于合法的序列，$a'_k=a_k-a_{k-1}+a_{k-2}-a_{k-3}+\cdots$。于是我们设 $b_k=a_k-a_{k-1}+a_{k-2}-a_{k-3}+\cdots$。综上可得结论：一个序列合法当且仅当任意 $1 \le i < n$ 都满足 $b_i \le a_{i+1}$，并且 $b_{n-1}=a_n$。

先把不需要操作的判掉，然后考虑交换。如果我们交换了 $a_{i-1},a_i$，$1 < i < n$，那么所有 $j \ge i$ 并且 $j \equiv i \pmod 2$ 的 $b_j$ 增加 $2(a_{i-1}-a_i)$；所有 $j \ge i$ 并且 $j \not\equiv i \pmod 2$ 的 $b_j$ 减去 $2(a_{i-1}-a_i)$。

我们不妨令 $c_i=a_{i+1}-b_i=b_{i+1}$，那么序列合法条件就是任意 $c_i$ 都非负并且 $b_{n-1}=a_n$，那么我们的操作就相当于把 $c$ 分成奇偶两部分之后的后缀加法和减法。

记 $\delta=2(a_{i-1}-a_i)$。以 $i$ 为偶数为例，那么偶数子列中是后缀减去 $\delta$，需要满足非负，条件就是这个后缀的最小值大于等于 $\delta$；同样的，奇数子列中后缀加上 $\delta$，需要满足非负，条件就是这个后缀的最小值大于等于 $-\delta$。

此外还有三个特殊的贡献：

- 原本需要满足的 $b_{i-2} \le a_{i-1}$ 变成 $b_{i-2} \le a_i$；
- $b_{i-1}$ 变成了 $b_{i-1}-a_{i-1}+a_i$，需要满足 $b_{i-1}-a_{i-1}+a_i \le a_{i-1}$。
- $b_{n-1}$ 通过操作会加上或减去 $\delta$，要判定它是否等于 $a_n$。

并且注意我们的操作对 $i-2$ 以前的位置没有影响，所以如果存在小于等于 $i-3$ 的位置 $p$ 不满足 $b_p \le a_{p+1}$，那么序列非法。

最后把上面这若干条件一起判定，同时合法就有解。

哥们能发现上面并未讨论当 $a_n$ 和 $a_{n-1}$ 交换的情况，所以最后单独做即可。

[https://codeforces.com/contest/1474/submission/320460725](https://codeforces.com/contest/1474/submission/320460725)。

---

## 作者：sosksyx_is_my_wife (赞：0)

### 链接
[Link](https://www.luogu.com.cn/problem/CF1474D)

### 题意

有一个长度为 $n$ 的数组 $a$。

现在要进行一些操作将数组的所有元素清除：

- 选定两个**下标连续**的数，若两个数均不为 $0$，则将两个数均减 $1$。

在此之前，你可以使用**一次**超能力（可以不使用）：任选两个**下标连续**的数并交换。

多次询问，判断是否可以清空 $a$ 数组。

### 题解

先考虑不使用超能力检验合法性。

首先从左到右去处理，发现 $a_1$ 只能和 $a_2$ 框在一起，于是 $a_1$ 若想变为 $0$，就要令 $a_2\gets a_2-a_1$，也就是框起来减 $a_1$ 次。

这时，$a_2$ 和 $a_3$ 的关系可以看作刚才 $a_1$ 和 $a_2$ 的关系，因为 $a_1$ 此时为 $0$ 动弹不得，接着另 $a_3\gets a_3-a_2$，以此类推到 $a_n$。

发现这是一个类似于“前缀差”的过程，设这个前缀差数组为 $s_i$。

形式化的：$s_i=a_i-s_{i-1}$，$s_1=a_1$。

需要注意的一点是，由于不允许负数的出现，所以 $s_i$ 每一项的值都必须为非负整数。

所以以此类推，得出不交换的时有解的充要条件：对于 $a_i$ 的前缀差 $s_n$，满足 $\forall i,s_i\geq 0$ 且 $s_n=0$。

发现交换这个限制很强，只能凭借枚举交换的位置然后挨个检验。

假设当前交换 $\{a_i,a_{i+1}\}$，**注意**，为了防止混淆，申明一下 $a_i$ 和 $a_{i+1}$ 表示的是**交换之前**的数，然后把受到影响的量列出来找一下规律：

- 交换之前：
  - $s_i=a_i-s_{i-1}$
  - $s_{i+1}=a_{i+1}-(a_i-s_{i-1})=s_{i-1}+(a_{i+1}-a_i)$
  - $s_{i+2}=a_{i+2}-(a_{i+1}-(a_i-s_{i-1}))=a_{i+2}+(a_i-a_{i+1})-s_{i-1}$
- 交换之后：
  - $s_i=a_{i+1}-s_{i-1}$
  - $s_{i+1}=a_{i}-(a_{i+1}-s_{i-1})=s_{i-1}+(a_{i}-a_{i+1})$
  - $s_{i+2}=a_{i+2}-(a_{i}-(a_{i+1}-s_{i-1}))=a_{i+2}+(a_{i+1}-a_{i})-s_{i-1}$

容易发现影响的量与奇偶性有关，于是按奇偶讨论：

- 如果 $j$ 与 $i$ 奇偶性相同，则 $s_j\gets s_j +2\times(a_{i+1}-a_{i})$
- 如果 $j$ 与 $i$ 奇偶性不同，则 $s_j\gets s_j -2\times(a_{i+1}-a_{i})$

当然啦，$j$ **必须大于** $i$，不然是无法被影响到的。

于是，做法已经十分显然了：

- 先把 $s_i$ 求出来，然后枚举每一对交换，计算交换后的 $s_n$ 是否等于 $0$。
- 还要提前预处理后缀最小值 $\mathrm{smx}_{i,0/1}$，第一维代表位置，第二维代表奇偶，在枚举的时候按奇偶性讨论最小值是否大于 $0$ 即可。

### 一些小细节

其一，如果不交换时有的 $s_i$ 小于 $0$，且第一个小于 $0$ 的位置为 $p$，则大于 $p$ 的位置是交换不了的。

其二，上文提到的做法是从左到右跑的，还需要从右到左跑一遍（翻转数组再跑一遍即可）。

### Code

```cpp
const int N=2e5+10;
const int INF=1e18;
int a[N],n;
int s[N];
int smn[N][2];
bool check(){
	
	//找第一个小于 0 的位置 
	int pos=n;
	for(int i=1;i<=n;i++){
		s[i]=a[i]-s[i-1];
		if(s[i]<0&&pos==n) pos=i;
	}
	
	//处理后缀 max 
	smn[n+1][0]=smn[n+1][1]=INF;
	for(int i=n;i>=1;i--){
		int t=i&1;
		smn[i][t]=min(smn[i+1][t],s[i]);
		smn[i][!t]=smn[i+1][!t];
	}
	
	bool flag=(s[n]==0&&pos==n);
	for(int i=1;i<pos;i++){
		bool x=0,y=0;
		int c=2*(a[i+1]-a[i]);
		if(s[n]+c*(i%2!=n%2?-1:1)==0) x=1;//奇偶性分讨 
		int t=i&1;
		if(smn[i][t]+c>=0&&smn[i][!t]-c>=0) y=1;
		if(x&&y) flag=1;
	}
	
	if(pos!=n){//最后这一对直接暴力，不然会很复杂 
		swap(a[pos],a[pos+1]);
		int tmp=pos;pos=0;
		for(int i=1;i<=n;i++){
			s[i]=a[i]-s[i-1];
			if(s[i]<0&&pos==0) pos=i;
		}
		if(s[n]==0&&!pos) flag=1;
		swap(a[tmp],a[tmp+1]);
	}
	return flag;
}
signed main(){
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		bool flag=0;
		
		//正反各跑一遍 
		if(check()) flag=1;
		reverse(a+1,a+1+n);
		if(check()) flag=1;
		
		for(int i=1;i<=n;i++) a[i]=0;
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [ CF1474D Cleaning](https://www.luogu.com.cn/problem/CF1474D)

显然，对于一个数，它只能和前一个数或后一个数进行消除。我们记 $pre_i$ 表示 $a_i$ 和 $a_{i-1}$ 进行的消除次数，$suf_i$ 表示 $a_i$ 和 $a_{i+1}$ 进行的消除次数。如果不考虑交换，那么满足 $\forall 1\leq i \leq n$，使得 $pre_i=suf_{i-1}$。可以发现，上面的式子具有传递性，因此只要 $\exists i$，使得 $pre_i=suf_{i-1}$ 就可以把整个序列消除。

考虑怎么求这两个数组。对于第一个和最后一个数，它们只能和第二个或倒数第二个进行消除。因此，我们可以正序求 $suf$，倒序求 $pre$。

接下来考虑交换 $a_i,a_{i+1}$。如果满足 $a_i-pre_{i+2} \geq 0 $ 并且 $a_{i+1}-suf_{i-1} \geq 0$ 并且 $a_i-pre_{i+2}=a_{i+1}-suf_{i-1}$，那么交换完后序列可以被删除。

code 
```
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N=200010;
int T,n;
int a[N],suf[N],pre[N];
signed main()
{
	scanf("%lld",&T);
	while (T--)
	{
		scanf("%lld",&n);
		for (int i=1;i<=n;++i) scanf("%lld",&a[i]);
		suf[0]=pre[n+1]=0;
		for (int i=1;i<=n;++i)
		{
			if (a[i]-suf[i-1]>=0) suf[i]=a[i]-suf[i-1];
			else suf[i]=LONG_LONG_MAX;
		}
		for (int i=n;i>=1;--i)
		{
			if (a[i]-pre[i+1]>=0) pre[i]=a[i]-pre[i+1];
			else pre[i]=LONG_LONG_MAX-1;
		}
		bool flag=false;
		for (int i=1;i<n;++i)
		{
			if (suf[i]==pre[i+1])
			{
				flag=true;
				break;
			}
			else
			{
				int x=a[i],y=a[i+1];
				if (x-pre[i+2]>=0&&y-suf[i-1]>=0)
				{
					if (x-pre[i+2]==y-suf[i-1])
					{
						flag=true;
						break;
					}
				}
			}
		}
		if (flag) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

