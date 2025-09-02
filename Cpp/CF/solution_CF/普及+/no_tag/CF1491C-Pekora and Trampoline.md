# Pekora and Trampoline

## 题目描述

有 $n$ 个蹦床排成一列，每个蹦床有一个弹力值 $s_i$

每一轮的最开始，Pekora 会选择一个蹦床作为她的起点（任意一个蹦床都可以作为起点）。当她在蹦床 $i$ 时，她会跳到蹦床 $i+s_i$ 上，并且 $s_i$ 会变为 $\max(1,s_i-1)$（也就是说，蹦床每被跳一次弹力值就会减一，直到弹力值为 $1$）。当她跳到了第 $n$ 个蹦床的后面时，该轮结束。

现在，Pekora 想要把所有的 $s_i$ 都变成 $1$，问最少要多少轮才能实现这个目标

## 说明/提示

$1 \le T \le 500$  
$\sum n \le 5000$  
$1 \le s_i \le 10^9$

## 样例 #1

### 输入

```
3
7
1 4 2 2 2 2 2
2
2 3
5
1 1 1 1 1```

### 输出

```
4
3
0```

# 题解

## 作者：serverkiller (赞：15)

这里是官方题解。

考虑维护一个 $t_i$ 表示 $i$ 已经被前面的操作经过多少次。

可以发现，对于一个位置 $x$ ，它必然会让后面的 $x+S_x,x+S_x-1,...x+2$ 被经过若干次；

如果它被经过的次数超过了 $S_x-1$，它还会让 $x+1$ 被经过 $t_x-S_x+1$ 次。

最后将每个位置的 $\max(S_i-t_i-1,0)$ 相加即可。

- 这个东西可以数据结构维护，但是作为 `C` 位置的题目，我们删掉了数据结构的部分，允许了 $O(n^2)$ 的程序通过。

所以某些草标算的题解能不能尊重一下我们？

---

## 作者：nalemy (赞：9)

~~看到发这道题题解的都是各路红紫名dalao我一蒟蒻瑟瑟发抖~~

简述一下题意：

每一轮从任意一个蹦床$i$开始，向后跳到第$i+s_i$个蹦床，并令$s_i$的值减$1$，直到跳出所有蹦床，开始下一轮，直到所有$s_i=1$

> 对于这种题，要么从往前看算来源，要么从往后看算贡献

这道题，我们选择后者

对于这道题，~~不难~~想到贪心的思想

1. 每次从**第一个**$s_i=1$的蹦床开始跳一定是最优的

   **说明**：因为$s_i$一定只能由蹦床$j(j\le i)$来更新，所以对于**第一个**$s_i\not=1$的蹦床$i$，如果起点选到它后面，就永远更新不到他了~~（寂寞）~~。而如果起点选到它前面，因为有$s_j=1(j\lt i)$，所以它每次只能往后跳一步，并且途中不会做任何更新，等跳到蹦床$i$时就又回到了从蹦床$i$出发的局面（这不是跟从蹦床$i$起跳一样吗），所以为了优化循环我们干脆直接从蹦床$i$起跳（从$1$起跳也可以）

2. 用$t_i$表示**到目前**，**当前**蹦床$i$**需要被跳过多少次**才能使$t_i$前面的所有蹦床的弹力都变成$1$，考虑每次经过蹦床$i$时的$t_i$对应的情况

   **说明**：
   - 如果$t_i\gt s_i-1$，说明$s_i$已经变成$1$了，$t_i=s_i-1$之后（不算它）的那部分$s_i$都为$1$，所以**都会跳到蹦床**$i+1$**上去**。如果**不满足**这个情况，说明此时$s_i$还未变成$1$，所以还需要$s_i-t_i-1$轮
   - 而对于普遍情况（即$t_i\le s_i-1$的那一部分），它最少往前跳$2$个，最多跳$s_i$个（如果有这么多蹦床的话），所以它会**分别跳到**$[i+2,min(i+s_i, n)]$一床一次，所以给这个区间每个$t_i$加$1$，楼上题解也说了，可以用**差分**和**树状数组**的方法

最后附上**AC代码**：

```C++
#include<iostream>
#include<cstring>
#define N 5010
using namespace std;
typedef long long ll;

int n, s[N], d[N];
int main() {
    int t; cin >> t;
    while(t--) {
    	cin >> n; ll cnt = 0, t = 0;
        // 多组数据一定记得数组清零 坑死我了
        memset(d, 0, sizeof(d));
        for(int i=0; i<n; i++)
			cin >> s[i];
        for(int i=0; i<n; i++){
            // 当前的t就是t_i
            t += d[i]; // d是t_i的差分
            // 两个if对应题解里面分析的两种情况
            if (t > s[i] - 1)
                d[i+1] += t - s[i] + 1, d[i+2] -= t - s[i] + 1;
            else cnt += s[i] - t - 1;
            if (i+2 <= min(s[i]+i, n))
                d[i+2]++, d[min(s[i]+i, n)+1]--;
        }
        cout << cnt << endl;
    }
    return 0;
}
```


---

## 作者：ailanxier (赞：6)

[题目链接](http://codeforces.com/problemset/problem/1491/C)

&emsp;&emsp;比赛时只想到了 $\mathcal O(n^3)$ 的暴力做法，正解是 $\mathcal O(n^2)$ ，并且是可以优化为 $\mathcal O(n)$ 的（贪心+差分）。

&emsp;&emsp;贪心是比较明显的，我们需要从左到右依次考虑每张床的贡献，因为第 $i$ 张床只能由 $[1,i-1]$ 的床跳过来，Pekora从第一张床开始跳一定是最优的。我们从左到右分析，用 $b_i$ 记录在 $i$ 床在之前被跳过的次数，**如果 $b_i>S_i-1$  ，说明 $S_i$ 在之前就已经降为 $1$ 了，多跳的部分会转移到 $b_{i+1}$ 上**；否则还需要在 $i$ 床上跳 $S_i-b_i-1$ 次。然后对于每张床我们只需要考虑它能直接跳到的地方：因为它要从 $S_i$ 减到 $1$ ，所以它会把 $[i+2,min(S_i+i,n)]$ 区间上的所有床都跳过一次，即这个区间上的 $b$ 都增一，这里如果用差分的话就是 $\mathcal O(1)$ 的区间修改复杂度了，当然用暴力扫一遍也是可以过这道题的。这里给出使用差分的代码，$b$ 在代码中为**差分数组**。

$\mathrm{Code}:$

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 6;
typedef long long ll;
int n,s[N],b[N];//注意b[i]为差分数组

int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        ll ans = 0;
        for(int i = 1;i <= n;i++) scanf("%d", s + i), b[i] = 0;b[n + 1]=0;
        int las = 0;
        for(int i = 1;i <= n;i++){
            int now = b[i] + las;  //now表示是i床在[1,i-1]中被跳了几次,即上面分析中的b[i]
            las = now;
            if(now > s[i] - 1){
                b[i+1] += now - s[i] + 1;
                b[i+2] -= now - s[i] + 1;
                now = s[i] - 1;
            }
            ans += s[i] - now - 1;
            if(min(s[i] + i, n) >= i + 2){
                b[i+2] ++;                     //相当于区间[i+2,min(s[i]+i,n)]增一
                b[min(s[i] + i, n) + 1]--;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```



---

## 作者：Priori_Incantatem (赞：3)

[原题链接](https://codeforces.ml/problemset/problem/1491/C)  [洛谷链接](https://www.luogu.com.cn/problem/CF1491C)  
[题目翻译](https://blog.csdn.net/Brian_Pan_/article/details/114259919)  
[我的Blog](https://blog.csdn.net/Brian_Pan_/article/details/114259573)

题意就不赘述了

考虑贪心，显然每轮最开始调到第一个 $s_i$ 不为 $1$ 的蹦床上是最优的，因为这样可以让后面的 $s$ 尽可能减少。  
定义 $c_i$ 为位置 $i$ 已经被踩了多少次

那么，我们贪心的从 $1$ 开始枚举跳到的第一个蹦床，设当前枚举到第 $i$ 个蹦床  
由于最终这个蹦床的 $s_i$ 会被踩到只剩 $1$，所以肯定会对区间 $[i+2,\min(i+s_i,n)]$ 的蹦床造成 $1$ 点贡献（后面会讲到对 $i+1$ 的贡献）
由于在正常情况下，当蹦床的 $s_i$ 达到 $1$ 的时候，就不会再从它开始起跳了，所以这样就不会对 $i+1$ 造成贡献。只有当 $s_i-c_i<1$ 的时候，也就是说从别的地方跳过来，才可以对 $i+1$ 做出贡献。所以蹦床 $i$ 对 $i+1$ 做出的贡献为 $\max(0,1-(s_i-c_i))$

在考虑完对后面蹦床的贡献后，我们考虑蹦床 $i$ 对最终答案的贡献。这个其实非常简单，就不细说了，贡献：$\max(0,(s_i-c_i)-1)$

总时间复杂度 $\mathcal O(T\cdot n\log n)$  
PS: 为了美观并且方便理解，这里只提供未开 long long 的代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=5010;
int n,ans;
int a[Maxn],sum[Maxn];
inline int lowbit(int x)
{
    return x&(-x);
}
void modify(int x,int v)
{
    if(x>n || x<1)return;
    while(x<=n)
    {
        sum[x]+=v;
        x+=lowbit(x);
    }
}
int query(int x)
{
    int ret=0;
    while(x)
    {
        ret+=sum[x];
        x-=lowbit(x);
    }
    return ret;
}
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
int main()
{
    // freopen("in.txt","r",stdin);
    int T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;++i)
        a[i]=read(),sum[i]=0;
        for(int i=1;i<=n;++i)
        {
            int tmp=a[i]-query(i);
            if(tmp>1)
            ans+=tmp-1;
            if(a[i]>1)
            modify(i+2,1),modify((i+a[i])+1,-1);
            if(tmp<1ll)
            modify(i+1,1-tmp),modify(i+2,tmp-1);
        }
        printf("%lld\n",ans);
        ans=0;
    }
    return 0;
}
```

**Update: 03.04:** 发现这个做法好像可以优化到 $\mathcal O(n)$。  
我们把树状数组换成差分，但看上去似乎差分只能支持区间修改，不支持在线的查询。  
但是，可以发现这些操作具有一些良好的性质：
1. 查询操作是从前往后依次查询的，也就是 $1\dots n$ 的位置都被挨个查了一遍。
2. 当我们查询完位置 $i$，之后的所有修改都不会跟 $1\dots i$ 有关系。

那么，我们可以在枚举蹦床的时候维护差分数组，也就是 `sum[i]+=sum[i-1]`。这样，单次查询和修改就都是 $\mathcal O(1)$ 的了。  
总时间复杂度 $\mathcal O(n)$。

**代码仍旧未开 long long**
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=5010;
int n,ans;
int a[Maxn],sum[Maxn];
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
int main()
{
    // freopen("in.txt","r",stdin);
    int T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;++i)
        a[i]=read(),sum[i]=0;
        for(int i=1;i<=n;++i)
        {
            sum[i]+=sum[i-1];
            int tmp=a[i]-sum[i];
            if(tmp>1)
            ans+=tmp-1;
            if(a[i]>1)
            {
                if(i+2<=n)
                sum[i+2]++;
                if(i+a[i]+1<=n)
                sum[i+a[i]+1]--;
            }
            if(tmp<1)
            {
                if(i+1<=n)
                sum[i+1]+=(1-tmp);
                if(i+2<=n)
                sum[i+2]-=(1-tmp);
            }
        }
        printf("%lld\n",ans);
        ans=0ll;
    }
    return 0;
}
```

---

## 作者：SSerxhs (赞：2)

提供一种 $O(\sum n)$ 的做法。

注意到操作顺序对序列没有影响，可以考虑每次都从 $\min\limits_{a_i\ne 1} \{i\}$ 开始（因为它不能被其他非 $1$ 点跳到）。

记 $i$ 被 $f_i$ 次跳到

1. 若 $f_i< a_i-1$

还需要从 $i$ 出发跳 $a_i-1-f_i$ 步，且包括之前跳的恰好跳到 $[i+1,\min(i+a_i)]$ 各一次，为了维护 $f_i$ 只需对这个区间做区间修改，可以差分实现。

2. 若 $f_i\ge a_i-1$

包括之前跳的恰好跳到 $[i+2,\min(i+a_i)]$ 各一次，且跳到 $i+1$ 共 $f_i-a_i$ 次，同上处理即可。

从左到右扫一次，$ans=\sum\limits_{i=1}^n \max{(0,a_i-1-f_i)}$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
std::mt19937 rnd(time(0));
inline int sj(int n)
{
	unsigned int x=rnd();
	return x%n+1;
}
#define rand fst
template<typename typC> void read(register typC &x)
{
	register int c=getchar(),fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
template<typename typC> void write(register typC x)
{
	if (x<0) putchar('-'),x=-x;
	static int st[100];
	register int tp=1,y;st[1]=x%10;x/=10;
	while (x) y=x/10,st[++tp]=x-y*10,x=y;++tp;
	while (--tp) putchar(st[tp]|48);
}
template<typename typC> void write(register typC *a,register int num)
{
	for (register int i=1;i<=num;i++) write(a[i]),putchar(i==num?10:32);
}
#define space(x) write(x),putchar(32)
#define enter(x) write(x),putchar(10)
const int N=5e3+2;
ll ans;
ll f[N],g[N];
int a[N];
int T,n,m,c,i,j,k,x,y,z,la;
int main()
{
	T=1;read(T);
	while (T--)
	{
		read(n);ans=0;
		for (i=1;i<=n;i++) read(a[i]);
		memset(f+1,0,n<<3);
		memset(g+1,0,n<<3);
		for (i=1;i<=n;i++) 
		{
		    f[i]+=(g[i]+=g[i-1]);
			if (f[i]<a[i]-1) ans+=a[i]-1-f[i]; else f[i+1]+=f[i]-(a[i]-1); 
			++g[i+2];--g[1+min(n,i+a[i])];
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：dcmfqw (赞：2)

~~毒瘤题，不知道多少人卡在这了~~

有一个贪心的想法，每次从最左边的非 1 暴力跳，不难证明正确性。

然后发现 $s_i\le10^9$，直接这么干会 T 飞。

但是发现 $s_i\ge n-i+1$ 时跳一次就出去了。

所以对于 $s_i > n-i+1$ 的 $s_i$，把它跳成 $n-i+1$ 再暴力跳，发现这是 $O(n^3)$，一组严格递减的数据就可以让它 T 飞。

所以我们要用并查集优化一下。

具体而言跳的时候如果跳到 1 了，显然可以直接跳到下一个不是 1 的地方。

这个东西用并查集优化一下，让 $find(x)$ 每次指向这一段 1 的最后一个。

这就可以 $O(n^2)$ 了，因为我们可以保证每个点被访问的次数级别为 $O(n)$。

看代码可能好懂一些。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _maxn = 200011;
int t, n, s[_maxn], fath[_maxn];
long long rans = 0;
int find(int at) {
  return fath[at] == at ? at : fath[at] = find(fath[at]);
}
int main() {
  scanf("%d", &t);
  while(t--) {
    scanf("%d", &n);
    for(register int i = 1; i <= n; ++i) {
      scanf("%d", &s[i]);
      fath[i] = i;
    }
    rans = 0;
    for(register int i = 1; i <= n; ++i) {
      if(s[i] + i > n + 1) {
        rans += s[i] - n + i - 1;
        s[i] = n - i + 1;
      }
      while(s[i] != 1) {
        ++rans;
        for(register int j = i; j <= n;) {
          if(s[j] == 1) {
            if(j <= n && s[j + 1] == 1) {//如果下一个是 1 的话就合并
              fath[find(j)] = find(j + 1);//注意合并方向
            }
            j = find(j) + 1;
          } else {
            --s[j];
            j += s[j] + 1;
          }
        }
      }
    }
    printf("%lld\n", rans);
  }
  return 0;
}
```
考完 3s 过掉的就是我了/ll

---

## 作者：Hisy (赞：0)

## 分析
考虑到 $i$ 只能够从 $[1,i-1]$ 来更新，因此选择前面的更新后面的更优。比如 $1$ 只能够自行更新，一定优先更新 $1$ 然后顺便更新后面的节点。

考虑维护一个 $b$，$b_i$ 表示 $i$ 前面跳的次数。如果 $b_i$ 的次数比 $a_i-1$ 要多，说明 $a_i$ 已经被跳成了 $1$，之后的会顺流到下一个 $a_{i+1}$。否则，还需要跳 $a_i-b_i-1$ 次进行更新，由于在此期间 $a_i\ge 2$，所以 $[i+2,i+a_i]$ 会被所有床跳一次，所以将这个区间内的 $b$ 都加上一次即可。这个可以用树状数组维护。

看到其他巨佬用差分 $\operatorname{O}(n)$ 求，感受到了被碾压的恐惧。
## 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 5005
using namespace std;
typedef long long ll;
int a[MAXN],b[MAXN],tree[MAXN<<1];
inline int lowbit(int p){
	return p&-p;
}
inline int query(int p){
	int res=0;
	for(int i=p;i;i-=lowbit(i)){
		res+=tree[i];
	}
	return res;
}
inline void modify(int p,int x){
	for(int i=p;i<MAXN;i+=lowbit(i)){
		tree[i]+=x;
	}
}
inline void change(int l,int r,int x){
	modify(l,x);
	modify(r+1,-x);
}
inline void work(){
	int n;
	scanf("%d",&n);
	memset(tree,0,sizeof(tree));
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	ll ans=0;
	for(int i=1;i<=n;++i){
		int que=query(i);
		if(que>=a[i]){
			change(i+1,i+1,que-a[i]+1);
		}else{
			ans+=a[i]-que-1;
		}
		if(min(a[i]+i,n)>=i+2){
			change(i+2,min(a[i]+i,n),1);
		}
	}
	printf("%lld\n",ans);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		work();
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

大意了，以为直接暴力草是对的，结果被卡T了半天才发现时间复杂度是错的。              

很显然我们从前向后枚举每次跳完是最优的。                     

接着我们考虑那些一口气直接跳挂的情况，这种情况就直接单独拿出来 $O(1)$ 算就好了。                

接着我们在操作时满足所有 $a_i + i \leq n$ 也就是说只要每个数贡献 $a_i$ 次运算那么时间复杂度就可以 $O(n ^ 2)$ ，我们发现我们中间一些已经变成 $1$ 的数在暴力中很浪费时间。                 

做过[大学](https://www.luogu.com.cn/problem/P5610)的同学应该很熟悉这种trick，直接暴力并查集维护这些数就好了，其实理清楚了的话题目还是很简单的。              


~~记得开long long~~        

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e4 + 5;
int n,a[Len],fa[Len];
inline int findSet(int x)
{
	if(x > n) return n + 1;
	return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);
}
inline void merge(int x,int y)
{
	int u = findSet(fa[x]) , v = findSet(fa[y]);
	fa[u] = v; 
}
inline void F(int x)
{
	int now = x;
	do
	{
		int to = findSet(now + a[now]);
		a[now] = max(a[now] - 1 , 1);
		if(a[now] == 1) merge(now , now + 1);
		now = to;
	}while(now <= n);
}
signed main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		for(int i = 1 ; i <= n + 1; i ++) fa[i] = i;
		int idx = 1;long long ans = 0;
		for(; idx <= n ; idx ++) 
		{
			if(a[idx] + idx - 1 > n) 
			{
				int res = a[idx] + idx - n - 1;
				ans += res;
				a[idx] -= res;
			}
			while(a[idx] > 1) F(idx) , ans ++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

