# Perform Easily

## 题目描述

After battling Shikamaru, Tayuya decided that her flute is too predictable, and replaced it with a guitar. The guitar has $ 6 $ strings and an infinite number of frets numbered from $ 1 $ . Fretting the fret number $ j $ on the $ i $ -th string produces the note $ a_{i} + j $ .

Tayuya wants to play a melody of $ n $ notes. Each note can be played on different string-fret combination. The easiness of performance depends on the difference between the maximal and the minimal indices of used frets. The less this difference is, the easier it is to perform the technique. Please determine the minimal possible difference.

For example, if $ a = [1, 1, 2, 2, 3, 3] $ , and the sequence of notes is $ 4, 11, 11, 12, 12, 13, 13 $ (corresponding to the second example), we can play the first note on the first string, and all the other notes on the sixth string. Then the maximal fret will be $ 10 $ , the minimal one will be $ 3 $ , and the answer is $ 10 - 3 = 7 $ , as shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/75869e5e3f35cb76d96c1bbe62cb5730522c5a69.png)

## 说明/提示

In the first sample test it is optimal to play the first note on the first string, the second note on the second string, the third note on the sixth string, the fourth note on the fourth string, the fifth note on the fifth string, and the sixth note on the third string. In this case the $ 100 $ -th fret is used each time, so the difference is $ 100 - 100 = 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/4a9f5f121daaf96225841a762483d6d36c81ea82.png)In the second test it's optimal, for example, to play the second note on the first string, and all the other notes on the sixth string. Then the maximal fret will be $ 10 $ , the minimal one will be $ 3 $ , and the answer is $ 10 - 3 = 7 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/d3f532a5b4af047547fabc1dd582c7d88c33efa7.png)

## 样例 #1

### 输入

```
1 4 100 10 30 5
6
101 104 105 110 130 200```

### 输出

```
0```

## 样例 #2

### 输入

```
1 1 2 2 3 3
7
13 4 11 12 11 13 12```

### 输出

```
7```

# 题解

## 作者：Time_tears (赞：18)

这个题理解题意后还是比较可做的。

因为是要差最小，所以我们考虑定最大值或者最小值，这里以最大值为例。

因为 $a$ 数组的大小仅仅为 6，所以我们可以枚举出所有 $b-a$ 的大小。

假如说我们选取某一个 $b_i-a_j$ 为最大值，那么就是要在剩下的所有 $b_k$ 中，每个都选取一个 $a_l$ 使得 $b_k-a_l$ 在不超过 $b_i-a_j$ 的情况下，尽量的大。

容易发现，这个东西可以先从小到大排序，然后可以用一个线段树快速维护，或者你也可以用可删除堆去搞。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,a[6],sum,cnt,minn[N<<2];
struct node {
	int id,x;
	bool operator <(node a) const {
		return x<a.x;
	}
} b[N*6];
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
void Build(int p,int l,int r) {
	if(l==r)return minn[p]=-0x3f3f3f3f,void();
	int mid=l+r>>1;
	minn[p]=-0x3f3f3f3f,Build(p<<1,l,mid),Build(p<<1|1,mid+1,r);
}
void Change(int p,int l,int r,int x,int y) {
	if(l==r)return minn[p]=y,void();
	int mid=l+r>>1;
	if(x<=mid)Change(p<<1,l,mid,x,y);
	else Change(p<<1|1,mid+1,r,x,y);
	minn[p]=min(minn[p<<1],minn[p<<1|1]);
}
signed main() {
	for(int i=0; i<6; ++i)a[i]=read();
	n=read();
	for(int i=1,x; i<=n; ++i) {
		x=read();
		for(int j=0; j<6; ++j)b[++cnt].x=x-a[j],b[cnt].id=i;
	}
	sort(b+1,b+6*n+1),Build(1,1,n);
	int ans=0x3f3f3f3f;
	for(int i=1; i<=6*n; ++i)Change(1,1,n,b[i].id,b[i].x),ans=min(ans,b[i].x-minn[1]);
	printf("%d",ans);
	return 0;
}

```


---

## 作者：QianianXY (赞：9)

[传送门](https://www.luogu.com.cn/problem/CF1413C)

## 题目分析

详细介绍一种不计排序，复杂度为 $O(n)$ 的双指针贪心做法。

把所有 $6\cdot n$ 种可能的差放到一个结构体数组 $a$，记录该差的值和来自哪一个 $b_i$（记为第 $i$ 种），根据值从小到大排序。

令指针 $p,q$ 表示在 $a$ 中选取区间的左右端点。可知若 $n$ 种元素都各有大于等于 $1$ 个包含在区间内，则该区间是合法区间，由于 $a$ 中元素有序，答案为 $p,q$ 两点值的差。

题目所求即为两端点值之差最小的合法区间。

初始化：$p=1,q=0$。定义数组 $cnt_i$，表示第 $i$ 种元素在区间内的数量，并由该数组可方便更新区间内元素种类的个数。

操作时分两类讨论。

1. 当区间内元素种类不足 $n$ 种时，不断将 $q+1$，直到区间内有 $n$ 种元素为止。

2. 当区间内有 $n$ 种元素时，不断将 $p+1$，并更新题目所求最小值，直到区间内元素种类不足 $n$ 种为止。

直到指针 $q$ 扫完数组 $a$ 为止。此时答案即为所求，正确性是显然的，可反复阅读上文后理解。

最后注意细节，特判元素只有一种时的情况，答案为 $0$。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1000010
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int c[N], b[N], n, tot, cnt[N], p = 1, q, cntn, ans = 1e9;
struct Node {int v, id;} a[N];

inline bool cmp(const Node &a, const Node &b) {return a.v < b.v;}

int main()
{
	for (rei i = 1; i <= 6; i++) read(c[i]);
	read(n); if (n == 1) {putchar('0'); return 0;}
	for (rei i = 1; i <= n; i++) read(b[i]);
	for (rei i = 1; i <= n; i++)
		for (rei j = 1; j <= 6; j++)
			a[++tot] = (Node){b[i] - c[j], i};
	for (rei i = 1; i <= n; i++) cnt[i] = 0;
	sort(a + 1, a + 1 + tot, cmp);
	while (q < tot)
	{
		if (!cnt[a[++q].id]) cntn++;
		++cnt[a[q].id];
		while (p < q && a[q].v - a[p].v >= ans)
		{
			if (cnt[a[p].id] == 1) cntn--;
			--cnt[a[p].id];
			++p;
		}
		while (p < q && cntn == n)
		{
			ans = min(ans, a[q].v - a[p].v);
			if (cnt[a[p].id] == 1) cntn--;
			--cnt[a[p].id];
			++p;
		} 
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Spasmodic (赞：5)

亏我考试想那么久，没看 2D，结果错失 Expert /ll

### 1.Problem
给定数组 $a_{1,2,\dots,6}$ 和 $b_{1,2,\dots,n}$，求

$$\min_{\forall 1\le i\le n,1\le id_i\le 6}\{\max_{1\le i\le n}\{b_i-a_i\}-\min_{1\le i\le n}\{b_i-a_i\}\}$$

### 2.Solution
显然可以想到二分答案，考虑判断可行性，可以想到这样的一种做法：

将所有可能的差全部放进一个数组里面，排序之后 two pointers，如果有一个时刻选定的区间里面恰好 $1,2,\cdots,n$ 对应的差都有，那么就说明是可行的，反之不可行。

我们可以再思考一下：这个二分必要吗？

其实是不必要的。直接 two pointers，只要记录到目前区间是可行的那么就更新答案。

如果用二分则复杂度为 $\mathcal O(n\log b)$，如果用第二种那么复杂度为 $\mathcal O(n)$。

### 3.Code
考试时 nt 了，只想到了二分的做法，下面是 $\mathcal O(n\log b)$ 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100005;
ll T,n,a[6],b[N];
struct IO_Tp {
    const static int _I_Buffer_Size = 2 << 22;
    char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer;

    const static int _O_Buffer_Size = 2 << 22;
    char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;

    IO_Tp() { fread(_I_Buffer, 1, _I_Buffer_Size, stdin); }
    ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }

    IO_Tp &operator>>(ll &res) {
    	ll f=1;
        while (!isdigit(*_I_pos)&&(*_I_pos)!='-') ++_I_pos;
        if(*_I_pos=='-')f=-1,++_I_pos;
        res = *_I_pos++ - '0';
        while (isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
        res*=f;
        return *this;
    }

    IO_Tp &operator<<(ll n) {
    	if(n<0)*_O_pos++='-',n=-n;
        static char _buf[10];
        char *_pos = _buf;
        do
            *_pos++ = '0' + n % 10;
        while (n /= 10);
        while (_pos != _buf) *_O_pos++ = *--_pos;
        return *this;
    }

    IO_Tp &operator<<(char ch) {
        *_O_pos++ = ch;
        return *this;
    }
} IO;
struct val{int id,v;bool operator<(const val&x)const{return v<x.v;}}x[N*6];
int cnt[N];
bool ok(int d){
	int num=0;
	memset(cnt,0,sizeof(cnt));
	for(int l=1,r=1;r<6*n;l++){
		while(r<6*n&&x[r].v-x[l].v<=d)num+=((cnt[x[r].id]++)==0),r++;
		if(num==n)return 1;
		num-=((--cnt[x[l].id])==0);
	}
	return 0;
}
int main(){
	for(int i=0;i<6;i++)IO>>a[i];
	IO>>n;
	for(int i=1;i<=n;i++){
		IO>>b[i];
		for(int j=0;j<6;j++)x[i+j*n].id=i,x[i+j*n].v=b[i]-a[j];
	}
	sort(x+1,x+6*n+1);
	int l=0,r=1000000000,ans=1000000000;
	while(l<=r){
		int mid=l+r>>1;
		if(ok(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：BFqwq (赞：3)

提供一种堆的解法。

显然对于每一个 $b_i$，其最终取值有六种。我们考虑一开始先将所有取值中最小的全部拿出来，放到一个小根堆中，并且维护其最大值。

令最大值为 $mx$，最小值为 $mn$，则目前的答案为 $ans=mx-mn$。

然后我们考虑把目前的所有数中最小的拿出来，让后找到对应 $b_i$ 中的其他取值中排名比它大 $1$ 的那个，然后重新放回堆中，更新答案。

显然，我们这种做法可以使得我们所选的数尽可能的集中，所以可以得到最优解。

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200],str[200];int tt;
inline void print(int x,char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=120005;
int f[7],a[maxn],n,pos[maxn],mx,res=1e9+7;
struct node{
	int v,id;
	friend bool operator <(node a,node b){
		return a.v>b.v;
	}
}tmp;
priority_queue<node> q;
signed main(){
	for(int i=1;i<=6;i++){
		f[i]=read();
	}
	sort(&f[1],&f[7]);
	reverse(&f[1],&f[7]);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		tmp.id=i;
		tmp.v=a[i]-f[1];
		pos[i]=1;
		q.push(tmp);
		mx=max(mx,tmp.v);
	}
	while(!q.empty()){
		tmp=q.top();
		q.pop();
		res=min(res,mx-tmp.v);
		int i=tmp.id;
		pos[i]++;
		if(pos[i]<=6) tmp.v=a[i]-f[pos[i]];
		else break;
		mx=max(mx,tmp.v);
		q.push(tmp);
	}
	print(res);
	return 0;
}
```


---

## 作者：dead_X (赞：3)

## 1 题意
有六根弦，每根弦的基础音高是 $a_i$ 。

如果你在第 $i$ 根弦的第 $j$ 个位置上弹奏，你能得到一个音高为 $a_i+j$ 的音。

你现在需要演奏所有音，每个音可以在任意一个弦的任意一个位置上弹奏。求所有位置中最大值减最小值的最小值。
## 2 思路
我们对于每个音求合法位置，并且记录**在一个位置上通过某种弦可以弹第 $x$ 个音符**。

然后从小到大排序位置，左右跑一遍双指针即可。

具体来说，我们维护一个队列，如果最左边的位置对应的音符已经出现两次，则出队。每次进队一个并不断出队，更新答案。
## 3 代码
```
#include<bits/stdc++.h>
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int a[13],b[100003],n,l=1,r=1,cnt=0;
pair<int,int> x[600003];
int f[100003];
signed main()
{
    for(int i=1; i<=6; i++) a[i]=read();
    n=read();
    for(int i=1; i<=n; i++) b[i]=read();
    for(int i=1; i<=6; i++) for(int j=1; j<=n; j++) x[++cnt]=make_pair(max(b[j]-a[i],1ll),j);
    long long ans=1000000000000ll;
    sort(x+1,x+cnt+1);
    int now=0;
    for(int l=1,r=1; r<=cnt; r++)
    {
        if(f[x[r].second]==0) ++now;
        ++f[x[r].second];
        while(f[x[l].second]>1) --f[x[l].second],++l;
        if(now==n) ans=min(ans,x[r].first-x[l].first);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：2)

首先，$6$ 这个奇怪的数是一个突破口，这告诉我们可以处理出所有差值。

现在我们就需要找到最短的区间 $[l,r]$，使得所有大小在 $[l,r]$ 内的差值，用 $b_1\sim b_n$ 算出的都存在。

这就是双指针了。给所有差值排序，然后枚举所有差值，双指针找出对应的最小 $r$，更新答案即可。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,b[10],mp[100010];
struct st{int x,id;}a[600010];
bool cmp(const st &x,const st &y){
    return x.x<y.x;
}
int main()
{
    for(int i=1;i<=6;i++)cin>>b[i];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        for(int j=1;j<=6;j++)
            a[++m]={x-b[j],i};
    }
    sort(a+1,a+6*n+1,cmp);
    int r=0,cnt=0,minn=1e9;
	for(int l=1;l<=6*n;l++)
	{
		while(cnt<n&&r<6*n)
		{
			r++;
			if(!mp[a[r].id])cnt++;
			mp[a[r].id]++;
		}
		if(cnt==n)
			minn=min(minn,a[r].x-a[l].x);
		mp[a[l].id]--;
		if(!mp[a[l].id])cnt--;
	}
	cout<<minn<<endl;
    return 0;
}
```

---

## 作者：A_Đark_Horcrux (赞：2)

看到这道题，想到 [P2085](https://www.luogu.com.cn/problem/P2085) 最小函数值

可以运用同样的思路,用一个小根堆存储每一个 $b_i - a_j$ 和当前 b 数组里的位置（也就是 i）：

```cpp
struct node
{
	int x,pos;//x代表值，pos代表是b数组中的位置
	bool operator > (const node &b) const//重载运算符
	{
		return x>b.x;
	}
};
priority_queue<node,vector<node>,greater<node> > q;//小根堆
```

再开一个 cnt 数组表示 b 数组的每一位是和 a 数组的哪一位相减（也就是处理了多少次）。

首先把 a 数组排序，使它具有单调性。然后把每一个 $b_i$ 减去最小的 $a_i$ 存入堆中，初始化 $cnt_i =1$，并记录 $b_i - a_j$ 的最大值，方便更新答案。

在操作过程中，每次取出堆顶，记录下答案，由于是小根堆，取出来的是最小值，故答案更新为记录的差的最大值减去堆顶取出的差值（最小值）。然后要把 $b_{pos}$ 减去下一个 $a_i$ 的值放进去，这时候就要用上 cnt 数组，我们让 $cnt_{pos}$ 加上一，则此时的 x 更新为 $b_{pos}-a_{cnt_{pos}}$，丢回到堆里面去并且更新差的最大值。

最后还有终止条件：若 b 数组的一个位置被更新了超过 6 次，说明它是 b 数组里最小的一个，并且已经减过最后一个 $a_i$ 了，而这个差值被放到了堆顶？这也就意味着之后再出现的差值不可能比它小，之后的操作只会更新最大值，答案不会比当前优，结束。

（大根堆+维护最小值或许也可以，我还没试过

```cpp
int main()
{
	for(i=1;i<=6;i++) a[i]=read();
	sort(a+1,a+7,cmp);//先给a排序
	n=read();
	for(i=1;i<=n;i++) cnt[i]=1;//初始化
	for(i=1;i<=n;i++)
	{
		b[i]=read();//输入a
		q.push(node{abs(b[i]-a[1]),i});//将最小的先插入堆
		maxx=max(maxx,b[i]-a[1]);//记录最大值
	}
	while(!q.empty())
	{
		node now=q.top(); q.pop();//先把对顶取出来
		ans=min(ans,maxx-now.x); cnt[now.k]++;//更新答案，并更新cnt数组
		if(cnt[now.k]>6) {printf("%d\n",ans); return 0;}//终止条件
		now.x=b[now.k]-a[cnt[now.k]]; q.push(now);//插入新的值
		maxx=max(maxx,b[now.k]-a[cnt[now.k]]);//更新maxx
	}//最后提一句，要先更新ans再更新maxx
	return 0;
}
```


---

## 作者：Zesty_Fox (赞：2)

~~毒瘤C题，考场卡我1个小时~~

前往博客，食用效果更佳：[点这里](https://www.cnblogs.com/acceptedzhs/p/13876630.html)

首先，这道题难点在哪里？**它的最大值与最小值都是浮动的**。

怎么办？**把最小/最大值固定！**

以把最小值固定为例，我们枚举每个音符，并枚举它使用哪条琴弦，将它此时的位置**强制**其作为最小值（设为$minx$）。

同时，我们令其他音符**不作为最小值**，即其他的音符的位置**不能**小于最小值。

接下来，我们只需计算每个音符的最小位置（但不小于最小值），在这些音符中取 $\max$ 即可。

直接的想法是枚举其他的所有音符，寻找满足 $b_i-a_j \ge minx$ 最大 $a_j$ （此时 $b_i-a_j$ 最小）。

很明显，这样做是 $O(n)$ 的。然而，我们要枚举 $6n$ 个最小值，时间复杂度为$O(n^2)$ （把常数项省掉了）…

略加思考，我们发现并不是所有的音符都要枚举一遍。我们把$a、b$数组分别从小到大排序，并把$a$数组去重（原因后面讲），那么**最悲惨的音符**~~（雾）~~ 肯定是**那些可以用 $a_{j-1}$ 的琴弦，但正好用不了 $a_j$ 的琴弦的音符**中**最大**的一个。当然，如果存在音符连 $a_1$ 都用不了，直接判定**当前最小值不合法**，并枚举下一个最小值。

举个例子：$a$数组为 $[1,3,5]$ （去重以后），$b$数组为 $[4,5,6,6,7]$，$minx$为$3$。

那么，$5、7$是最悲惨的音符，因为$5$是可以用琴弦$a_1$但用不了琴弦$a_2$（有$4、5$两个音符）中最大的音符，$7$是可以用琴弦$a_2$但用不了琴弦$a_3$中最大的音符。显然，最大的位置将在最悲惨的音符中产生。

由于我们对 $b$ 数组排过序，因此对每一条琴弦，直接二分查找最大的 $b_i$ ，使 $b_i-a_j < minx$ 即可。

于是，我们只要找到这些音符即可。这些音符最多不超过$6$个。时间复杂度 $O(n \log n)$ 。

最后说一句，为什么$a$要去重？因为我们要找可以用 $a_{j-1}$ 的琴弦但用不了 $a_j$ 的琴弦的音符，如果存在重复，即 $a_{j-1}=a_j$ ，则可能这个音符 $a_{j-1}$ 的琴弦、 $a_j$ 的琴弦都用不了，明显不符。

$Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
ll a[10],n,b[100010],pos[10],cnt;
ll ans=1e18;
int main(){
    for(int i=1;i<=6;i++) scanf("%lld",&a[i]);
    sort(a+1,a+7);cnt=unique(a+1,a+7)-a-1;//去重
    cin>>n;
    for(int j=1;j<=n;j++) scanf("%lld",&b[j]);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=cnt;j++){
            ll minx=b[i]-a[j],maxn=0,last=0; //枚举minx
            if(b[1]-a[1]<minx) goto fail;
            for(int k=2;k<=cnt;k++){
                last=lower_bound(b+last+1,b+n+1,minx+a[k])-b-1;//二分查找
                maxn=max(maxn,b[last]-a[k-1]);//更新最大位置
            }
            for(int k=cnt;k>=1;k--){
                if(b[n]-a[k]>=minx){
                    maxn=max(maxn,b[n]-a[k]); //最大的音符特殊处理一下
                    break;
                }
            }
            ans=min(ans,maxn-minx);//更新答案
            fail:;
        }
    }
    cout<<ans<<endl;
    return 0;
}

```


---

## 作者：xrk2006 (赞：1)

# 【题解】CF1413C Perform Easily 

写篇题解水水经验~顺便增加一下 RP~

比较套路和简单的一道绿题。

[博客园食用效果更佳](https://www.cnblogs.com/xrkforces/p/CF1413C.html)

## 题目链接

[Perform Easily - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/CF1413C)

## 题意概述

给你一个长度为 $6$ 的 $a$ 数组，和一个长度为 $n$ 的 $b$ 数组，要求将 $b$ 数组内的每一个数，减去 $a_1\sim a_6$ 中的一个，然后让处理后的数组极差（即最大值与最小值的差）最小。

## 数据范围

- $1\le n \le 1\times 10^6$
- $1 \le a_i,b_i \le 1\times 10^9$

## 思路分析

首先考虑处理后数组的最大和最小值，一定是对于所有的 $i(1 \le i \le n)$，$b_i$ 减去 $a_1 \sim a_6$ 之后所有数中的一个。

那么我们把对于每个 $i$，$b_i$ 减去 $a_1\sim a_6$ 的所有值扔到一个 `vector` 里。为了确定 `vector` 中的每一个数是哪个 $b_i$ 处理得来的，我们给 `vector` 中的每个元素都规定一个 $id$，如果这个数是由 $b_i$ 减去 $a_1$ 到 $a_6$ 中的某一个得来的，我们就让这个数的 $id=i$。

那么问题实际上就转化为：

> 有一个长度为 $6n$ 的数组，且每个元素都有一个 $id$，现在让你从这个数组里面选择一些数，要求：
>
> - 对于所有的 $i(1\le i \le n)$，要求选出来的数中至少有一个数的 $id=i$。
> - 选出来的数在所有合法的选择方案中，极差最小。

定义这个 `vector` 为 $p$。

因为要求的是极差最小，那实际上就是让我们确定选出来数的最大值和最小值。那么想到枚举最小值，那么我们只需要考虑当 $p_i$ 作为最小值时，谁能够成为最小的最大值。

由于题目要求的是极差，我们联想到可以将这个 `vector` 中的元素排序。

所以当 $p_i$ 作为最小值时，选的数一定是在 $p_i$ 右边，如果 $p_j(j>i)$ 作为最大值，那么下标为区间 $[i,j]$ 中的数都可以被选进去，但是我们并不关心选哪些数，只要确定最大值和最小值。也就是说如果区间 $(i,j)$ 中有多个数 $id$ 相同，那么这些数中任选一个都可以。所以对于所有 $1 \le k \le n$，只要区间 $[i,j]$ 中至少存在一个数的 $id=i$ 即可。

也就是说当 $p_i$ 为最小值时，$p_j$ 可以作为最大值当且仅当下标为区间 $[i,j]$ 中数的 $id$ 覆盖了 $1\sim n$。由此可知可以作为最大值的下标 $j$ 一定是从最后一个元素到前面某个点的连续一段区间（因为如果 $[i,k]$ 中数的 $id$ 覆盖了 $1\sim n$，由于 $[i,k+1]$ 包含了区间 $[i,k]$，所以 $[i,k+1]$ 中的数的 $id$ 也一定覆盖了 $1\sim n$），假设这个区间是 $[r,n]$，最小的最大值就是 $p_r$，那么我们从 $l$ 开始往后枚举，顺便记录一下当前的 $id$ 覆盖了 $1\sim n$ 中的多少个数，遇到第一个完全覆盖 $1\sim n$ 的下标就是 $r$。

到目前为止我们已经有了一个做法了：枚举 $p_i$ 作为选出来的数的最小值，然后从 $i$ 开始向后枚举最大值，顺便记录当前区间的 $id$ 覆盖了 $1\sim n$ 中得多少个数，然后遇到第一个完全覆盖的下标 $j$，则 $p_j$ 即为最小的最大值，此时的极差为 $p_j-pi$，那么最后最小的极差就是每个 $p_i$ 作为最小值时最小极差取 $\min$。

但是这样做复杂度是 $O(n^2)$ 级别的，无法接受，考虑优化。

我们发现枚举 $p_i$ 作为最小值，当 $i$ 逐渐增大时，对应最小的最大值下标 $j$ 也一定是单调不降的。这一点很好理解。因为当你 $i$ 变成 $i+1$ 时，也就是 $[i,j]$ 变成 $[i+1,j]$。假设 $p_i$ 的 $id$ 是 $t$，那么如果原先 $[i,j]$ 中 $id$ 为 $t$ 的元素个数大于 $1$，那么满足条件的 $j$ 不变；如果 $id$ 为 $t$ 的个数本来为 $1$，那么 $i+1$ 之后 $id$ 为 $t$ 的个数现在变为 $0$，所以新的 $j>$ 原先的 $j$。

有了单调不降这个特征，我们就可以愉快的使用双指针了，直接用双指针维护当前最小值和最大值的位置 $l,r$。顺便在指针移动的过程中维护当前区间覆盖的 $id$ 的个数即可。

时间复杂度 $O(6n)$。

## 代码实现

```cpp
//CF1413C
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#define pii pair<int,int>
#define mk make_pair
#define int long long
using namespace std;
const int maxn=1e6+10;
int b[maxn],a[10],cntnow[maxn];

vector<pii>p;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int cmp(pii a,pii b){return a.first<b.first;}

signed main()
{
	for(int i=1;i<=6;i++)a[i]=read();
	int n=read();
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
		for(int j=1;j<=6;j++)p.push_back(mk(b[i]-a[j],i));
	}
	sort(p.begin(),p.end(),cmp);
	int r=-1;
	int ans=1e18;
	int now=0;
	for(int l=0;l<p.size();l++)
	{
		while((r<(signed)p.size()-1)&&now<n)
		{
			r++;
			cntnow[p[r].second]++;
			if(cntnow[p[r].second]==1)now++;
		}
		if(now>=n)ans=min(ans,p[r].first-p[l].first);
		cntnow[p[l].second]--;
		if(cntnow[p[l].second]==0)now--;
	}
	cout<<ans<<'\n';
	return 0;
}
```



---

## 作者：AFOier (赞：1)

考虑枚举最小值，然后对于每个$b_i$，减去**能使减后的值仍大于最小值**的最大$a_i$，这么做的时间复杂度为$O(36n^2)$

我们发现枚举最小值后，并不需要遍历每个数，而只需要找到对于$k \in [1,6]$的
$$\max\{b_i-a_k\},minn+a_k\leq b_i<minn+a_{k+1}$$

用set维护即可$O(6 \log n)$找到最大值

总复杂度是$O(36n\log n)$

```
#include <bits/stdc++.h>
using namespace std;
int n, b[100011], a[7], minn, ans;
set <int> s;
int main() {
	for(int i = 1; i <= 6; i++) scanf("%d", &a[i]);
	scanf("%d", &n); minn = 2e9;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		minn = min(minn, b[i]);
		s.insert(b[i]);
	}
	sort(a+1, a+7); ans = 2e9;
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= 6; j++) {
		if(b[i] - a[j] > minn - a[1]) continue; //当前最小值不合法
		int Min = b[i] - a[j], Max = 0;
		for(int k = 2; k <= 6; k++) {
			set<int>::iterator it = s.lower_bound(Min+a[k]); 
			if(it == s.begin()) continue;
			it--;
			Max = max(Max, *it - a[k-1]);
		}
		set<int>::iterator it = s.end(); it--;
		Max = max(Max, *it - a[6]);
		ans = min(ans, Max - Min);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：NightmareAlita (赞：0)

## 简要题意

给定一个含有 $6$ 个元素的可重集 $a$，一个数 $n$ 和一个含有 $n$ 个数的可重集 $b$，现在要求 $b$ 中每个数和 $a$ 中任意一个数作差使得作差后得到的新的集合 $b$ 中最大的数和最小的数的差最小。

## 策略分析

首先考虑暴力，每个数最后的值都有 $6$ 种可能，所以总可能数有 $6^n$ 种，显然不行。题目中 $n$ 的大小为 $10^5$，所以我们期待一个 $O(n\log n)$ 的做法。我们发现，所有数也只有 $6$ 种可能，想要枚举答案不可能，但我们可以枚举结果。于是我们想到把 $b$ 中每个元素都和 $a$ 中所有元素作差，最后得到 $6n$ 个数放入一个新的数组 $cp$。因为我们要考虑最大和最小的差最小，所以我们需要使 $cp$ 数组中的值变得有序，于是我们对其进行排序。排序后为了查找的时候保证查找的区间内的数必须包含原来 $b$ 中每个数的至少一种差（显然其每个数都有 $6$ 种差），我们要在插入 $cp$ 前给每个数打好标记，标记它来自于哪个数。

预处理做完后，我们考虑如何查找答案。因为我们需要一个区间最大值，还需要一个区间最小值，所以我们想到了用双指针来进行查找。我们设左指针为 $lidx$，右指针为 $ridx$。$ridx$ 先走，一直走到与 $lidx$ 间包含了的数包含了原来 $b$ 中每个数的至少一个结果为止。现在开始移动左指针，每移动一次就 $ridx$ 与 $lidx$ 所指的两数之差更新答案。当两指针之间包含的数不能包含原来 $b$ 中每个数的至少一个结果时，就回到第一步重新开始移动 $ridx$，循环一轮即可得到答案。

枚举复杂度为 $O(n)$，排序复杂度为 $O(n\log n)$，最后搜索的复杂度为 $O(n)$，所以整个算法的时间复杂度为 $O(n\log n)$，于是我们做完了，下面是代码。

### 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

namespace SHAWN {
    const int N = 1e6 + 7, INF = 1e9;
    struct node { int val, id; }cp[N];
    int n, idx, ans = INF;
    int a[7], b[N], cnt[N];
    bool cmp(node x, node y) { return x.val < y.val; }
    int work()
    {
        for (int i = 1; i <= 6; ++i) { cin >> a[i]; }
        cin >> n;
        if (n == 1) { cout << "0\n"; return 0; }
        for (int i = 1; i <= n; ++i) {
            cin >> b[i];
            for (int j = 1; j <= 6; ++j) {
                cp[++idx] = {b[i] - a[j], i};
            }
            cnt[i] = 0;
        }// 加标记
        sort(cp + 1, cp + idx + 1, cmp);
        int lidx = 1, ridx = 0, ncnt = 0;
        // cnt数组和ncnt用来维护当前区间包含原来b数组中的数的结果的个数
        while (ridx < idx) {
            // 双指针搜索
            if (!cnt[cp[++ridx].id]) { ++ncnt; }
            ++cnt[cp[ridx].id];
            while (lidx < ridx && cp[ridx].val - cp[lidx].val >= ans) {
                if (cnt[cp[lidx].id] == 1) { --ncnt; }
                --cnt[cp[lidx].id];
                ++lidx;
            }
            // 移动左指针到可行方案处
            while (lidx < ridx && ncnt == n) {
                ans = min(ans, cp[ridx].val - cp[lidx].val);
                if (cnt[cp[lidx].id] == 1) { --ncnt; }
                --cnt[cp[lidx].id];
                ++lidx;
            } 
            // 移动左指针并不断更新答案
        }
        cout << ans << '\n';
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：gyh20 (赞：0)

被卡了好久好久。。。

很明显不能直接贪心，排序后 DP 感觉也不可做。最后莫名其妙想到了这种做法。

首先先定义结构体包含 $val,id$， $id$ 表示来源于哪一个 $b$，$val$ 存每一个 $b_i-a_i$。

那么一种合法的方案就是一个包含所有 $id$ 的子区间。

可以先用链表将所有 $id$ 相同的点串起来。

枚举初始点，计算当前所有 $id$ 中第一个点最大的一个（这样一定合法）。计算完后将自己链表指向的下一个加入，依次计算即可。

代码（比赛时傻了，用了个优先队列）：

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=1e9+7;
int t,n,m,a[500002],b[500002],ans,head[500002],cnt,num,nxt[600002],f[600002],fst[100002];
priority_queue<int>q,d;
inline int first(){
	while(!d.empty()&&q.top()==d.top())q.pop(),d.pop();
	return q.top();
}
struct edge{int to,next;}e[1000002];
inline void add(re int x,re int y){e[++cnt]=(edge){y,head[x]};head[x]=cnt;}
inline void pls(re int &x,re int y){(x+=y)>=M?x-=M:x;}
struct node{int id,val;bool operator <(const node x){return val<x.val;}}p[600002];
char s[500002];
signed main(){
	for(re int i=1;i<=6;++i)a[i]=read();ans=1e18;
	sort(a+1,a+6+1);
	n=read();
	for(re int i=1;i<=n;++i){
		b[i]=read();
		for(re int j=1;j<=6;++j)p[++num]=(node){i,b[i]-a[j]};
	}
	sort(p+1,p+num+1);
	for(re int j=1;j<=n;++j)nxt[j]=num+1;
	p[num+1].val=1e18;
	for(re int i=num;i;--i){
		f[i]=nxt[p[i].id];
		nxt[p[i].id]=fst[p[i].id]=i;
	}
	for(re int i=1;i<=n;++i)q.push(fst[i]);
	for(re int i=1;i<=num;++i){
		ans=min(ans,p[first()].val-p[i].val);
		q.push(f[i]);
	}
	printf("%lld",ans);
}
```


---

