# [USACO07DEC] Best Cow Line G

## 题目背景

*本题和 [2007 年 11 月月赛银组同名题目](/problem/P6140) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 打算带领 $N$（$1 \leq N \leq 5 \times 10^5$）头奶牛参加一年一度的”全美农场主大奖赛“。在这场比赛中，每个参赛者必须让他的奶牛排成一列，然后带领这些奶牛从裁判面前依此走过。

今年，竞赛委员会在接受报名时，采用了一种新的登记规则：取每头奶牛名字的首字母，按照它们在队伍中的次序排成一列。将所有队伍的名字按字典序升序排序，从而得到出场顺序。

FJ 由于事务繁忙，他希望能够尽早出场。因此他决定重排队列。

他的调整方式是这样的：每次，他从原队列的首端或尾端牵出一头奶牛，将她安排到新队列尾部。重复这一操作直到所有奶牛都插入新队列为止。

现在请你帮 FJ 算出按照上面这种方法能排出的字典序最小的队列。

## 样例 #1

### 输入

```
6
A
C
D
B
C
B```

### 输出

```
ABCBCD```

# 题解

## 作者：jiazhaopeng (赞：30)

[P2870 [USACO07DEC]最佳牛线，黄金Best Cow Line, Gold](https://www.luogu.com.cn/problem/P2870)

## 题意

- 给一个字符串，每次只能从两边取，加入到答案，要求取出来之后答案的字典序最小。
- $len$<=$500000$

## 思路

因为这道题要求答案字典序最小，所以我们有一个贪心策略：**每一次都取两端的较小者，一直取完**。这一定是没有问题的，此时局部最优解就是全局最优解。关键是当两端相同时应该怎么办。

当字符串为 $ACERHA$ 时，我们发现取哪一个 $A$ 都可以，因为 $C$ 和 $H$ 都比$A$ 大，我们一定会取完两个 $A$ 再取里面的字母。

当字符串为 $CAEAAC$ 时，我们发现，如果取左边的 $C$，答案会是这个样子： $CACAAE$ ，而取右边会是： $CAACAE$。

多玩几组数据会发现，**如果两端字母一样，就看看里面的那一位一样不一样。如果里面那一位不同，则取较小的字母所在的一端；如果里面那一位相同，就继续看里面的里面，一直到比出结果为止**。（当然，如果当前字符串本身就是个回文串，就取哪端都行了）

## 优化

但是，这样做最坏是 $n^2$ 的。比如，给一个 $AAAAAAAAAAA$，我们每次都要判断两端取哪一个更优，这是 $O(n)$ 的，需要做 $n$ 次，复杂度爆炸。我们不得不考虑优化。我们发现，如果我们针对这种最劣情况，要是能用某种方法迅速找出两端相同的长度，就可以把最劣情况的每一次判断做到 $logn$，问题就解决了。你一定能想到，这个地方可以用哈希。

如果你不会哈希的基本操作的话，可以参考机房大佬的博客：[lhm_的博客](https://www.luogu.com.cn/blog/lhm126/zi-fu-chuan-hash)

$Code$:
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#define N 500010
#define M 98244353
#define base 131
template<typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) {if (c == '-') flag = true; c = getchar(); }
	while (isdigit(c)) {x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	if (flag)	x = -x;
}
using namespace std;
int n;
char s[N];
long long ha1[N], ha2[N], bas[N];
//因为要正着的串和反着的串比较，所以要用两个哈希 
//bas[i]:base^i
char ans[N];
int top;
int lef, rig;//left, right
inline int che(int len) {//hash基本操作：比较两端是否相同 
	long long l = ((ha1[lef + len - 1] - ha1[lef - 1] * bas[len]) % M + M) % M;
	long long r = ((ha2[rig - len + 1] - ha2[rig + 1] * bas[len]) % M + M) % M;
	return l == r;
}
inline int halffind() {
	int l = 1, r = (rig - lef + 1) >> 1;
	int mid, res = 1;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (che(mid)) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}
int main() {
	read(n);
	for (register int i = 1; i < n; ++i) {
		s[i] = getchar();
		getchar();
	}
	s[n] = getchar();
	bas[0] = 1;
	for (register int i = 1; i <= n; ++i) {
		ha1[i] = (ha1[i - 1] * base + s[i]) % M;
		bas[i] = bas[i - 1] * base % M;
	}
	for (register int i = n; i; --i) {
		ha2[i] = (ha2[i + 1] * base + s[i]) % M;
	}
	
	lef = 1, rig = n;
	int len;
	for (register int i = 1; i < n; ++i) {
		if (s[lef] < s[rig]) {
			ans[++top] = s[lef++];
		} else if (s[rig] < s[lef]) {
			ans[++top] = s[rig--];
		} else {
			len = halffind();
			ans[++top] = s[lef + len] < s[rig - len] ? s[lef++] : s[rig--];
		}
	}
	ans[n] = s[lef];//最后一个直接扔到答案结尾即可，不用判断 
	for (register int i = 1; i <= n; ++i) {
		putchar(ans[i]);
		if (i % 80 == 0)	putchar('\n');
	}
	return 0;
}

```

第一次写题解，如果有错误，欢迎指出。

---

## 作者：Ameyax (赞：22)

首先贪心，左边和右边中选字典序小的。

但是当左右相同(如AABCAA)时就不好判断了。

~~这个题数据弱了，暴力的n方也能过，数据改到500000好了233~~

我们用$f[i]$表示从$i$开始的后缀，用$g[i]$表示从$i$开始的前缀。那么遇到$str[L]=str[R]$时，比较$f[L]$和$g[R]$即可。

如果暴力去算$f$和$g$显然会超时，将原串的后面添一个不存在的字符，然后把原串倒过来接上去。

$AABCAA==>AABCAA0AACBAA$

对新串求出后缀数组，$f[i]$就是$rank[i]$，$g[i]$就是$rank[2(n+1)-i]$。

~~%楼下那个说难度评高了的daolao~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 110000;
int n, m;
char str[MAX];
int SA[MAX], rnk[MAX], height[MAX], tax[MAX], tp[MAX], a[MAX];
void Sort()
{
    for (int i = 0; i <= m; ++i)
        tax[i] = 0;
    for (int i = 1; i <= n; ++i)
        tax[rnk[tp[i]]] ++;
    for (int i = 1; i <= m; ++i)
        tax[i] += tax[i - 1];
    for (int i = n; i >= 1; --i)
        SA[tax[rnk[tp[i]]] --] = tp[i];
}
bool cmp(int *f, int x, int y, int w)
{
    return (f[x] == f[y] && f[x + w] == f[y + w]);
}
void getSA()
{
    for (int i = 1; i <= n; ++i)
        rnk[i] = a[i], tp[i] = i;
    m = 127, Sort();
    for (int w = 1, p = 1, i; p < n; w += w, m = p)
    {
        for (p = 0, i = n - w + 1; i <= n; ++i)
            tp[++p] = i;
        for (i = 1; i <= n; ++i)
            if (SA[i] > w)
                tp[++p] = SA[i] - w;
        Sort(); swap(rnk, tp); rnk[SA[1]] = p = 1;
        for (int i = 2; i <= n; ++i)
            rnk[SA[i]] = cmp(tp, SA[i], SA[i - 1], w) ? p : ++p;
    }
}
void init()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%s", str + i);
    for (int i = 0; i < n; ++i)
        a[2 * (n + 1) - i - 1] = a[i + 1] = str[i];
    n = 2 * n + 1;
    getSA();
}
char ans[MAX];
int cnt;
int main()
{
    init();
    getSA();
    n = (n - 1) / 2;
    int L = 1, R = n;
    while (L < R)
    {
        if (a[L] < a[R])
            ans[++cnt] = (char)(a[L++]);
        else if (a[L] > a[R])
            ans[++cnt] = (char)(a[R--]);
        else
        {
            if (rnk[L] < rnk[2 * (n + 1) - R])
                ans[++cnt] = (char)(a[L++]);
            else
                ans[++cnt] = (char)(a[R--]);
        }
    }
    ans[++cnt] = (char)(a[L]);
    n = strlen(ans + 1);
    for (int i = 1; i <= n; ++i)
    {
        printf("%c", ans[i]);
        if (i % 80 == 0) putchar('\n');
    }
    return 0;
}
```

---

## 作者：cyh_toby (赞：5)

# 题意

题目链接：[P2870 [USACO07DEC]Best Cow Line G](https://www.luogu.com.cn/problem/P2870)

# 分析

容易想到贪心处理，尽可能选首尾字符中较小的那个；而当它们相等的时候，就需要比较第二个和倒数第二个，才能按最优策略实现；若还相等，就递归进行下去。

这其实就是在对字符串比大小——一段后缀和一段反串的后缀。

这就是比较两个后缀的大小，容易联想到后缀数组。而要使用后缀数组，只需要把反串接在原串后面，并在接缝处插入一个无穷小的字符（其实只需要比原串中的所有字符小即可），然后在新串上直接求后缀数组即可。

为什么要插入一个无穷小的字符？它相当于一个结尾标识，有了它，等价于接在原串后面的反串不会被算入原串的后缀中。如果不理解可以手动模拟。

需要注意的是洛谷 #22 是个 hack 点，容易 TLE，~~而且最近洛谷评测机日常波动~~，所以要优化细节卡常。具体卡常技巧可以参考 [oi-wiki](https://oi-wiki.org/string/sa/#_4) 。

# 源码

```cpp
const int N = 2*(5e5+5);
#define gc getchar

int n, w;
char s[N];
int sa[N], rk[N<<1], oldrk[N<<1], cnt[N], id[N], p[N]; 

inline bool cmp(int x, int y, int j) {
	return oldrk[x] == oldrk[y] && oldrk[x+j] == oldrk[y+j];
}

int main()
{	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		s[i] = gc();
		while (s[i] < 'A' || s[i] > 'Z') s[i] = gc();
		s[(n<<1)-i+2] = s[i];
	}
	s[n+1] = 'A' - 1;//赋值为极小, 避免对后缀排序产生影响 
	n = (n<<1)+1;
	
	for (int i = 1; i <= n; i++) cnt[(int)s[i]]++;
	w = 'Z'+5;
	for (int i = 1; i <= w; i++) cnt[i] += cnt[i-1];
	for (int i = n; i >= 1; i--) sa[cnt[(int)s[i]]--] = i;
	w = 0;
	for (int i = 1; i <= n; i++)
		rk[sa[i]] = s[sa[i]] == s[sa[i-1]] ? w : ++w;
	
	for (int j = 1; j < n; j <<= 1) {
		int t = 0;
		for (int i = n; i > n - j; i--) id[++t] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > j) id[++t] = sa[i] - j;
		
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) cnt[p[i] = rk[id[i]]]++;
		for (int i = 1; i <= w; i++) cnt[i] += cnt[i-1];
		for (int i = n; i >= 1; i--) sa[cnt[p[i]]--] = id[i];
		
		memcpy(oldrk, rk, sizeof(oldrk));
		w = 0;
		for (int i = 1; i <= n; i++)
			rk[sa[i]] = cmp(sa[i-1], sa[i], j) ? w : ++w;
	}
	
	int l = 1, r = (n-1)>>1, tot = 0;
	while (l <= r) {
		printf("%c", rk[l] < rk[n-r+1] ? s[l++] : s[r--]);
		if (++tot % 80 == 0) printf("\n");
	}
	return 0;
}
```

---

## 作者：Utsuji_risshū (赞：5)

这里写一篇**字符串哈希**的题解。~~其实是因为后缀数组码量稍大一丁点我不想写了~~。←不过提一句有的题目hash确实也可以作为SA的替代品， _**码量极短，还不易写错**_ 。在比较谁字典序小的时候，二分查找哈希值，找到最小元素使得哈希值不一样，然后比较之，就可以了哟，具体看code。

思路贪心，这个可以看楼上下，不过貌似没有人给证明正确性，这里给出一份[dalao的证明](https://www.cnblogs.com/liu-runda/p/6478318.html)。顺便安利一道[类似的题](https://www.lydsy.com/JudgeOnline/problem.php?id=4278).
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define dbg(x) cerr<<#x<<" = "<<x<<endl
#define ddbg(x,y) cerr<<#x<<" = "<<x<<"   "<<#y<<" = "<<y<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<typename T>inline char MIN(T&A,T B){return A>B?A=B,1:0;}
template<typename T>inline char MAX(T&A,T B){return A<B?A=B,1:0;}
template<typename T>inline T _min(T A,T B){return A<B?A:B;}
template<typename T>inline T _max(T A,T B){return A>B?A:B;}
template<typename T>inline T read(T&x){
    x=0;int f=0;char c;while(!isdigit(c=getchar()))if(c=='-')f=1;
    while(isdigit(c))x=x*10+(c&15),c=getchar();return f?x=-x:x;
}
const int N=500000+7;
const ull base=137;
int n,m;
ull ha[N],hb[N],p[N];
int a[N],b[N],c[N];
char ch[3];
inline ull get_ha(int l,int r){return ha[r]-ha[l-1]*p[r-l+1];}
inline ull get_hb(int l,int r){return hb[r]-hb[l-1]*p[r-l+1];}
inline int find_distinc(int i,int j){
	int L=0,R=n-j-i+2,mid;
	while(L<R){
		mid=L+R>>1;
		if(get_ha(i,i+mid)^get_hb(j,j+mid))R=mid;
		else L=mid+1;
	}
	return L;
}

int main(){//freopen("test.in","r",stdin);freopen("test.out","w",stdout);
	read(n);p[0]=1;
	for(register int i=1;i<=n;++i)scanf("%s",ch),a[i]=b[n-i+1]=ch[0]-'A';
	for(register int i=1;i<=n+1;++i)p[i]=p[i-1]*base;
	for(register int i=1;i<=n;++i)ha[i]=ha[i-1]*base+a[i];
	for(register int i=1;i<=n;++i)hb[i]=hb[i-1]*base+b[i];
	int i=1,j=1;
	while(i<=n-j+1){//ddbg(i,n-j+1);
		int len=find_distinc(i,j);//dbg(len);
		if(a[i+len]<=b[j+len])c[++m]=a[i++];
		else c[++m]=b[j++];
	}
	for(register int i=1;i<=m;++i)printf("%c",c[i]+'A'),i%80?0:puts("");
	return 0;
}
```


---

## 作者：_Anchor (赞：4)

# 题意

[传送门](https://www.luogu.com.cn/problem/P2870)

给定一个字符串，每次珂以取出当前字符串的头或者尾，将其加入答案串中（放到最后面），要求必须把该字符串取完，求字典序最小的方案

# 分析

SA简单题

题目要求的是求字典序最小，~~很容易想到SA来求~~

我们观察一下，对于每一位可能的情况就只有两种，所以我们想到贪心地取，每次取当前头和尾当中较小的那个字符

但是这样会出现一个问题：如果头和尾相同该怎么办？

比如这样的一个字符串：BCAB

现在我们取这个串就不知道该取头还是尾，这个时候如果我们贸然取头的话（变成CAB），我们下一步只能取到C或B（当前就应该取B）

这样干之后我们会取到BB作为当前已经取了的，实际上我们有更优的选择，那就是第一次取的时候取尾，然后我们珂以取到BA这个串，它的字典序更小

那么我们考虑在这种情况下怎么搞。

珂以发现，其实每次取都是在查看当前状态下，是当前串的字典序小，还是当前反串的字典序小，那么这就相当于是比较两个字符串的字典序谁大谁小的问题

很容易想到后缀数组SA来做。

具体就是设原串为A，设A的反串是~A，那么此时我们考虑拼接这样的一个字符串 B=A+（分隔符）+ ~A

此时我们对B串跑一边SA就可以得到原串和反串字典序排序之后的相对大小了（rk数组）

每次选字符的时候$O(1)$比较一下就行了

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=1e6+5,M=1e6+5,MOD=1e9+7;
char str[N];
int n,m,k,sa[N],rk[N],oldrk[N],id[N],px[N],cnt[N];
bool cmp(int x,int y,int w){return oldrk[x]==oldrk[y] && oldrk[x+w]==oldrk[y+w];}
void SA(){
	int i,p=0,w;
	m=300;
	for(i=1;i<=n;i++) ++cnt[rk[i]=str[i]];
	for(i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(w=1;w<n;w<<=1,m=p){
		for(p=0,i=n;i>n-w;i--) id[++p]=i;
		for(i=1;i<=n;i++) if(sa[i]>w) id[++p]=sa[i]-w;
		memset(cnt,0,sizeof(cnt));
		for(i=1;i<=n;i++) ++cnt[px[i]=rk[id[i]]];
		for(i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(i=n;i>=1;i--) sa[cnt[px[i]]--]=id[i];
		memcpy(oldrk,rk,sizeof(rk));
		for(p=0,i=1;i<=n;i++) rk[sa[i]]=cmp(sa[i],sa[i-1],w) ? p : ++p;
		
	}
	return ;
}
int main(){
	read(k);char ch;
	for(int i=1;i<=k;i++) while(isalpha(ch=getchar())) str[i]=ch;
	n=k<<1|1;
	for(int i=1;i<=k;i++) str[i+k+1]=str[k-i+1];
	SA();
	int l=1,r=k,tot=0;
	while(l<=r){
		if(rk[l]<rk[n+1-r]) putchar(str[l++]);
		else putchar(str[r--]);
		if((++tot)%80==0) puts("");
	}
	system("Pause");
	return 0;
}
```


---

## 作者：Catalan1906 (赞：3)

思路大概和其他的题解一样：
> 从当前字符串最前面，最后面选一个字典序较小的然后拉到一个新的字符串序列中，如果相同就一直往中间扫描直到发现不同为止（一个字符如果被选中之后那么就不可以再次选择了），所以我们左右各设一个指针扫描就好了，不需要递归。 —— WuPengrui_666 

此题解终结……诶等一下！84分是怎么回事！

哦，对了，数据被加强了

![毒瘤chen_zhe](https://i.loli.net/2019/01/24/5c49c67b275d8.png)

这里的题解都比较古老……都在数据被增强之前写的

那……我们谈一下正(you)确(hua)解(bao)法(li)

朴素暴力最坏可以达到$O(n^2)$，就是全部都是同一个字符的情况

对于这种情况，我们只需特判。因为只有一个字符，取出的字串也就只有一种可能，于是我们直接输出这n个字符不就好了呢~

code : 
```
#include <bits/stdc++.h>

using namespace std;

int main() {
    int cnt = 0, l = 1, r, n, flag = 1;
    scanf("%d", &n);
    char a[500010], c;
    for(int i = 1; i <= n; i++) {
        getchar(); a[i] = getchar();
        if(i == 1) c = a[i];
        else if(a[i] != c) flag = 0;
    }
    if(flag) {
        for(int i = 1; i <= n; i++) {
            putchar(c);
            if(i % 80 == 0) putchar(10);
        }
        return 0;
    }
    r = n;
    while(l < r) {
        cnt++;
        if(a[l] < a[r]) {
            putchar(a[l]);
            l++;
        } else {
            if(a[r] < a[l]) {
                putchar(a[r]);
                r--;
            } else {
                int x = l, y = r;
                while(x < y && a[x] == a[y]) x++, y--;
                if(a[x] < a[y]) {
                    putchar(a[l]);
                    l++;
                } else {
                    putchar(a[r]);
                    r--;
                }
            }
        }
        if(cnt % 80 == 0) putchar(10);
    }
    putchar(a[l]);
    return 0;
}
```

此题解终结~~（真的）~~

----

----

---

## 作者：wxgwxg (赞：3)

不知道这题难度为什么评那么高

第一眼就觉得是贪心

一个头指针，一个尾指针，哪边字母小就输出哪边

如果一样呢？就让头尾指针往后找，直到不一样为止

附上非常简短的代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,sum;
char s[200005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i];
    int head=1,tail=n;
    while(head<tail)
    {
        if(s[head]<s[tail]) cout<<s[head++];
        else if(s[head]>s[tail]) cout<<s[tail--];
        else {
            int x=head,y=tail;
            while(x<y&&s[x]==s[y])
            x++,y--;
            if(s[x]<s[y])  cout<<s[head++];
            else cout<<s[tail--];
        }
        sum++;
        if(sum%80==0) cout<<endl;
    }
    cout<<s[head]<<endl;
    return 0; 
}
```
来自之前无知的我写的2b题解,极限复杂度是n^2的

--------------------------------------------

学了后缀数组后，才知道只是个SA的裸题，但有一组30000个A的数据我的这个n^2程序还是过了，很有意思啊。

后缀数组做法，直接给串的后面加一个'0' 然后再加一个反过来的穿在后面，然后求后缀数组后和上面那程序差不多了，只是比较大小的时候从$O(n)$到$O(1)$了，复杂度 $nlogn$

代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=300055;
char s[N];
int sa[N],x[N],t[N],y[N],n,m,a[N],sum;
bool cmp(int o,int p,int q)
{
    return y[o]==y[p]&&y[o+q]==y[p+q];
}
void SA()
{
    m=28;
    for(int i=0;i<=m;i++) t[i]=0;
    for(int i=1;i<=n;i++) t[x[i]=a[i]]++;
    for(int i=1;i<=m;i++) t[i]+=t[i-1];
    for(int i=n;i>=1;i--) sa[t[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=0;i<=m;i++) t[i]=y[i]=0;
        for(int i=n-k+1;i<=n;i++) y[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++p]=sa[i]-k;
        for(int i=1;i<=n;i++) t[x[y[i]]]++;
        for(int i=1;i<=m;i++) t[i]+=t[i-1];
        for(int i=n;i>=1;i--) sa[t[x[y[i]]]--]=y[i];
        swap(x,y);
        x[sa[1]]=p=1;
        for(int i=2;i<=n;i++) x[sa[i]]=cmp(sa[i],sa[i-1],k)?p:++p;
        if(p>=n) break;m=p;
    } 
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>s[i],s[2*n+2-i]=s[i];
    for(int i=1;i<=2*n+1;i++)
    a[i]=s[i]-'A'+1;a[n+1]=0;
    n=n*2+1;
    SA();
    int a1=1,a2=1;
    n>>=1;
    while(a1+a2<n+2)
    {
        if(x[a1]>x[a2+n+1])
        cout<<s[n+1-a2],a2++;
        else cout<<s[a1],a1++;
        sum++;
        if(sum%80==0) puts("");
    }
    return 0;
}
```

---

## 作者：cold_cold (赞：1)

- 长度为N的字符串S，要让你构造一个字符串T，你可以每次在S中删去头部一个字符，加到T中，也可以在S的尾部删去一个字符加到T中，问你T的字典最小的答案是什么
- 挑S的头和尾部字典序列最小的字符
- 如果相等那么就继续向下一层挑S的次头和次尾部字典序列最小的字符


```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
int n,ji=0;
char a[30100];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		getchar(),scanf("%c",&a[i]);
	int h=1,t=n;
	while(h<t)
	{
		if(a[h]<a[t])
			printf("%c",a[h++]);
		else if(a[h]>a[t])
			printf("%c",a[t--]);
		else
		{
			int x=h,y=t;
			while(x<y&&a[x]==a[y])
				x++,y--;
			if(a[x]<a[y])
				printf("%c",a[h++]);
			else
				printf("%c",a[t--]);
		}
		ji++;
		if(ji==80)
			printf("\n"),ji=0;
	}
	printf("%c",a[h]);
    return 0;
}
```

---

## 作者：RainFestival (赞：0)

这道题我们用一种比较特殊的方法

题目要求字典序最小

我们在序列两头找小的放就行了

当然这只是一个初步思路~~不然怎么是蓝题~~

### 问题

如果两头一样怎么办？？？

那么你就比较下一个，然后取下一个小的

如果下一个还一样继续比较

如果你这么写，将会收获一个TLE

所以要优化

我们先判断又回文，从第二个到中间一个都比前面大的

那就直接输出（玄学优化，从84->100）

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char ans[500005],a[500005];
int n,p=0,k=0,same=0;
int main()
{
    scanf("%d",&n);
    same=1;
    for (int i=1;i<=n;i++)
        while (1)
        {
        	scanf("%c",&a[i]);
        	if (a[i]!=a[i-1]&&a[i]>1) same=0;
        	if (a[i]>='A'&&a[i]<='Z') break;
        }
    same=1; 
    for (int i=1;i<=n;i++) if (a[i]!=a[n-i+1]) same=0;
    for (int i=2;i<=n/2;i++) if (a[i]>a[i-1]) same=0;
    if (same)
    {
        for (int k=1;k<=n;k++)
        if (k%80==0) printf("%c\n",a[k]);
        else printf("%c",a[k]); 
        return 0;
    }
    
    
    
    int i=1,j=n;
    while (i<j)
    {
    	if (a[i]>a[j])
    	{
    		p++;
    		ans[p]=a[j];
    		j--;
    		//cout<<"> ";
        }
        else if (a[j]>a[i])
             {
                 p++;
                 ans[p]=a[i];
                 i++;
                 //cout<<"< ";
             }
             else
             {
                 int i1=i,j1=j,win=-1;
                 while (a[i1]==a[j1]&&i<j)
                 {
                     i1++;
                     j1--;	
                     if (i1>j1) break;
                     if (a[i1]>a[j1]/*&&a[j1]<=a[j]*/)
                     {
                         win=0;
                         break;
                     }
                     else if (a[i1]<a[j1]/*&&a[i1]<=a[i]*/)
                          {
                              win=1;
                              break;
                          }
                          //else if (a[i1]>a[i]&&a[j1]>a[j])
                               //{
                     	           //win=2;
                     	           //break;
                               //}
                               else continue;
                 }
                 //if (win==-1)
                 //{
                 	//for (k=i;k<=j;k++)
                 	//{
                 	    //p++;
                        //ans[p]=a[k];
                    //}
                    //cout<<"win=-1 ";
                    //break;
                 //}
                 if (win==-1)
                 {
                 	p++;
                    ans[p]=a[i];
                    i++;
                 }
                 else if (win==0)
                      {
                          //for (k=j;k>=j1;k--)
                          //{
                          //    p++;
                          //    ans[p]=a[k]; 
                          //}
                          //j=j1-1;
                          p++;
                          ans[p]=a[j];
                          j--;
                          //cout<<"win=0 ";
                      }
                      else if (win==1)
                           {
                               //for (k=i;k<=i1;k++)
                               //{
                                   //p++;
                                   //ans[p]=a[k];
                               //}
                               //i=i1+1;
                               p++;
                               ans[p]=a[i];
                               i++;
                               //cout<<"win=1 ";
                           }
                           //else
                           //{
                            //   for (k=i;k<=i1-1;k++)
                            //   {
                             //  	   p++;
                             //  	   ans[p]=a[k];
                             //  }
                             //  for (k=j;k>=j1+1;k--)
                             //  {
                             //      p++;
                             //      ans[p]=a[k];
                              // }
                              // i=i1;
                             // j=j1;
                               //cout<<"win=2 ";
                           //}
             }
        //cout<<i<<" "<<j<<" ";
        //for (int k=1;k<=n;k++)
        //if (k%80==0) printf("%c\n",ans[k]);
        //else printf("%c",ans[k]);
        //cout<<endl;
    }
    if (p<n)
    {
        p++;
        ans[p]=a[i];
    }
    for (int k=1;k<=n;k++)
        if (k%80==0) printf("%c\n",ans[k]);
        else printf("%c",ans[k]);
    return 0;
}
```

时间2965ms,空间1532kb,代码长度4.12kb

这是我在洛谷上提交的几乎最长的代码（除了p4420）

谢谢大佬们的观赏

---

## 作者：吴国铨 (赞：0)

就是每次从当前串找最左边和最右边的字符的大小关系，哪边小就取哪边。如果相等就麻烦点，要一位一位往里头找，比较两个字符是否不相等。当找到之后就按刚才的处理就好了


还有最后输出答案的时候要每80个换行，被坑了

 
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
//by zrt
//problem:
using namespace std;
typedef long long LL;
const int inf(0x3f3f3f3f);
const double eps(1e-9);
char s[60005];
int n,m;
const int MAXN=60005;
int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN],rank[MAXN];
void build_sa(int m){
    int *x=t,*y=t2;
    for(int i=0;i<m;i++) c[i]=0;
    for(int i=0;i<n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<m;i++) c[i]+=c[i-1];
    for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1){
        int p=0;
        for(int i=n-k;i<n;i++) y[p++]=i;
        for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(int i=0;i<m;i++) c[i]=0;
        for(int i=0;i<n;i++) c[x[y[i]]]++;
        for(int i=1;i<m;i++) c[i]+=c[i-1];
        for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(int i=1;i<n;i++){
            x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
        }
        if(p>=n) break;
        m=p;
    }
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%s",&s[i]);
    s[n]='$';
    for(int i=0;i<n;i++) s[i+n+1]=s[n-i-1];
    m=n;n<<=1;
    n=n+1;
    s[n]='\0';
    build_sa(128);
    for(int i=0;i<n;i++) rank[sa[i]]=i;
    int cc=0;
    int l=0,r=m-1;
    for(int i=0;i<m;i++){
        int a=rank[l];
        int b=rank[(m-r)+m];
        cc++;
        if(a<b){
            putchar(s[l++]);
        }else putchar(s[r--]);
        if(cc==80) cc=0,putchar('\n');
    }
    return 0;
}
```

---

## 作者：NaVi_Awson (赞：0)

本人蒻蒟，一种比较笨的方法，能过

从字典序性质来看，无论字符串末尾有多大，只要保证前面部分较小就可以

比较队首，队尾，小的直接输出

相等比较麻烦

附上的程序比较暴力（其实还可以优化）

每次相等时，往里面搜，找到一个能够比出大小的便输出

再加个判断：如果当前字母为序列中最小元素，直接输出

附上代码，必要时有注解：

```cpp
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
int n;
char a[30005];
int num[500];//保存每个字母出现次数
int l,r;
char minc;
int main()
{
    scanf("%d",&n);
    getchar();
    for (int i=1; i<=n; i++)
    {
        scanf("%c",&a[i]);
        num[a[i]]++;
        getchar();
    }
    for (int i='A'; i<='Z'; i++)
        if (num[i]!=0)//求出出现最小字母
        {
            minc=i;
            break;
        }
    l=1;
    r=n;
    for (int i=1; i<=n; i++)
    {
        if (num[minc]==0)//若最小字母已输出完，再找次小
        {
            for (int j=minc; j<='Z'; j++)
                if (num[j]!=0)
                {
                    minc=j;
                    break;
                }
        }
        if (a[l]<a[r]||a[l]==minc)//之前所说的判断
        {
            num[a[l]]--;
            putchar(a[l]);
            l++;
        }
        else if (a[l]>a[r])
        {
            putchar(a[r]);
            num[a[r]]--;
            r--;
        }
        else if (a[l]==a[r])
        {
            int j;
            for (j=1; j<=(n-i+1)/2; j++)
            {
                if (a[l+j]<a[r-j])
                {
                    putchar(a[l]);
                    num[a[l]]--;
                    l++;
                    break;
                }
                else if (a[l+j]>a[r-j])
                {
                    putchar(a[r]);
                    num[a[r]]--;
                    r--;
                    break;
                }
            }
            if (j>(n-i+1)/2)
            {
                    putchar(a[l]);
                    num[a[l]]--;
                    l++;
            }
        }
        if (i%80==0) cout<<endl;
    }
    return;
}
代码做了些手脚，抄题解的注意了！！！
```

---

