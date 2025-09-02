# 「LCOI2022」 Cow Insertion

## 题目背景

Farmer John 迎来了新奶牛——Bessie。每个奶牛都会有一定的开心值，Farmer John 希望 Bessie 能更幸福的生活在这里。

## 题目描述

牛棚里原来有 $n$ 头奶牛，开心值的感染距离 $m$，并且 $a_i$ 表示原来牛棚中第 $i(1\le i\le n)$ 头牛的开心值。并且，Bessie 同样拥有一个开心值 $A$。

整个牛棚的开心值是 $\sum\limits_{i=1}^{n-m+1}\ \max\limits_{i\le j\le i+m-1}\ a_j$，Bessie 可以住在任意两头牛的中间或起始以及最后。Farmer John 想知道：Bessie 来这里之后，整个牛棚的开心值最大为多少。

## 说明/提示

【样例解释】
- 当 Bessie 在第一个位置时（$50,60,100,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,50}+\max\cases{60,100}+\max\cases{100,70}$，即 $60+100+100=260$。
- 当 Bessie 在第二个位置时（$60,50,100,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,50}+\max\cases{50,100}+\max\cases{100,70}$，即 $60+100+100=260$。
- 当 Bessie 在第三个位置时（$60,100,50,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,100}+\max\cases{100,50}+\max\cases{50,70}$，即 $100+100+70=270$。
- 当 Bessie 在第四个位置时（$60,100,70,50$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,100}+\max\cases{100,70}+\max\cases{70,50}$，即 $70+100+100=270$。

显然，整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{260,260,270,270}=270$。

【数据范围与约定】

|subtask|$n\le$|分值|
|:-:|:-:|:-:|
|$1$|$5\times10^2$|$10$|
|$2$|$5\times10^3$|$20$|
|$3$|$5\times10^6$|$70$|

对于 $100\%$ 的数据，$1\le m\le n$，$0\le a_i, A\le100$。

## 样例 #1

### 输入

```
3 2 50
60 100 70```

### 输出

```
270```

# 题解

## 作者：Suzt_ilymtics (赞：13)

[同步发表在我的博客](https://www.cnblogs.com/Silymtics/p/solution-P8102.html)

[题目传送ww](https://www.luogu.com.cn/problem/P8102)

看到这个牛棚的开心值的计算方法，显然要用单调队列去处理，这样的话，对于一个已知的牛棚，我们可以在 $\mathcal O(n)$ 的时间内计算出整个牛棚的开心值。

我们考虑枚举能插的每一个位置。

借助单调队列模拟这个过程的话可以做到 $\mathcal O(n^2)$，期望得分 $30$。

考虑优化，发现在放 $i$ 位置和 $i+1$ 位置的时候很多位置的贡献是不会变化的，那我们只考虑变化了的。

我们考虑在第 $x$ 和第 $x+1$ 个牛之间插入一个牛。

以 $n = 6, m = 3, x = 3$ 为例。

插之前： `######` ；插之后：`###x###`。

`#` 从左到右编号 $1 \sim 6$。

我们发现 $[2,4], [3,5]$ 的贡献变成了 $[2,x], [3,4], [x, 5]$ 这三个区间。

后面这三个区间的贡献可以表示成原序列中三个长度为 $2$ 的区间和插入的 $x$ 去 $\max$ 求和贡献。

我们可以用单调队列两次分别预处理出每个长度为 $m$ 的区间的贡献和每个长度为 $m-1$ 的区间的贡献。 

然后，我们从前到后枚举插入的位置 $x$ （序列中第 $x$ 个元素的后面）的时候，发现这些有贡献的区间的范围是不断右移的，根据 $x,m$ 就可以确定出这个范围，然后用类似双指针的写法更新即可。

因为所有预处理包括后面的枚举插入位置都是 $\mathcal O(n)$ 的，所以总复杂度为 $\mathcal O(n)$，期望得分 $100$。

更多细节看代码吧。

```cpp
/*
Work by: Suzt_ilymtics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 5e6+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

int n, m, A;
int res = 0, Ans = 0, ans = 0;
int a[MAXN];
int b[MAXN], c[MAXN];
int q[MAXN], head = 1, tail = 0;

int read() {
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
    return f ? -s : s;
}

signed main()
{
    n = read(), m = read(), A = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i < m; ++i) {
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
    }
    for(int i = m; i <= n; ++i) {
        while(head <= tail && q[head] < i - m + 1) head ++;
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
        b[i - m + 1] = a[q[head]];
    }
    head = 1, tail = 0;
    int p = m - 1;
    for(int i = 1; i < p; ++i) {
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
    }
    for(int i = p; i <= n; ++i) {
        while(head <= tail && q[head] < i - p + 1) head ++;
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
        c[i - p + 1] = a[q[head]];
    }
    for(int i = 1; i <= n - p + 1; ++i) {
        c[i] = max(c[i], A);
    }
    for(int i = 1; i <= n - m + 1; ++i) ans += b[i];
    // 短区间长度为 m-1，个数为 m
    // 长区间长度为 m，个数为 m - 1
    // 若，插 i, i + 1 之间，所涉短区间为 [i - m + 2, i + 1]，所涉长区间为 [i - m + 2, i] 
    for(int i = 0; i <= n; ++i) {
        res -= b[i], res += c[i + 1];
        if(i - m + 1 >= 1) res += b[i - m + 1] - c[i - m + 1];
        Ans = max(Ans, ans + res);
    }
    printf("%lld\n", Ans);
    return 0;
}
```



---

## 作者：little_cindy (赞：6)

官方题解来了，求管理员给过qwq。
## 思路
### $\mathbf{\mathsf{10}}$ 分

这 $10$ 分你要是没拿到就基本可以退役了（

第一层循环：枚举插入位置，并求最大值

第二层循环：枚举起点位置，并求和

第三层循环：枚举当前点，并求最大值

伪代码：

```cpp
for 插入点ins
    插入(ins)
    for 起点i
        for 当前点j
            cnt=max(a[i])
        tot+cnt
	ans=max(tot)
```

我们先考虑插入函数是不是浪费时间。

答案是否定的——你里面的两重循环更慢，而插入函数不影响整体时间复杂度，顶多加一个常数。

分析完以后，就可以开始写函数了。

函数很简单，只要暴力“移动” $ins$ 后面的值就行了

插入函数：
```cpp
void insert(int x){
	b[x]=A;
	for(int i=1;i<=n;i++){
		if(i>=x){
			b[i+1]=a[i];
		}
		else{
			b[i]=a[i];
		}
	}
}
```

函数时间复杂度：$Θ(n)$。

伪代码直接改成真代码就好了，随便写写就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,A,a[5000005],b[5000005],ans=0;
void insert(int x){
	b[x]=A;
	for(int i=1;i<=n;i++){
		if(i>=x){
			b[i+1]=a[i];
		}
		else{
			b[i]=a[i];
		}
	}
}
int main() {
	cin>>n>>m>>A;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int ins=1;ins<=n;ins++){
		int tot=0,cnt=0;
		insert(ins);
		n++;
		for(int i=1;i<=n-m+1;i++){
			cnt=0;
			for(int j=i;j<=i+m-1;j++){
				cnt=max(b[j],cnt);
			}
			tot+=cnt;
		}
		n--;
		ans=max(ans,tot);
	}
	cout<<ans;
	return 0;
}
```

时间复杂度：$Θ(n^3)$。

说句闲话，其实 subtask$2$ 可以过一个点，但是是捆绑数据。

### $\mathbf{\mathsf{30}}$ 分

这个方法本来是可以得满分的，但是被我改了数据范围（光速逃

枚举插入点，每次滑动窗口就好了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5000000 + 5;
int n, m, A, Apos;
int a[MAXN];
deque<int> q;
int dat(int i) {
	if (i < Apos)
		return a[i];
	if (i > Apos)
		return a[i - 1];
	return A;
}
int main() {
	cin >> n >> m >> A;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	n++;
	int ans = 0;
	for (Apos = 1; Apos <= n - m + 1; Apos++) {
		while (!q.empty())
			q.pop_back();
		int now = 0;
		for (int i = 1, j = 1; i <= n - m + 1; i++) {
			while (j - i + 1 <= m) {
				while (!q.empty() && dat(q.back()) <= dat(j))
					q.pop_back();
				q.push_back(j++);
			}
			while (!q.empty() && q.front() < i)
				q.pop_front();
			now += dat(q.front());
		}
		ans = max(ans, now);
	}
	cout << ans << endl;
	return 0;
}
```

### $\mathbf{\mathsf{100}}$ 分

简单思考一下，可以得出一个结论——对于每次修改 $A$ 只会影响到插入位置的前 $m-1$ 个区间，没必要全部依次修改。

首先，如果 $m=1$，那么只需要统计和即可。

我们定义 $7$ 个数组：
- $f_i=\sum\limits^{i+m-1}_{j=i}a_j$
- $g_i=\sum\limits^{i+m-2}_{j=i}a_j$
- $sumf_i=\sum\limits^{i}_{j=1}f_j$（$f_i$ 的前缀和）
- $sumF_i=\sum\limits^{i}_{j=1}\begin{cases}f_j(f_j>A)\\0(f_j\le A)\end{cases}$（$f_i$ 中大于 $A$ 的前缀和）
- $sumg_i=\sum\limits^{i}_{j=1}g_j$（$g_i$ 的前缀和）
- $sumG_i=\sum\limits^{i}_{j=1}\begin{cases}g_j(g_j>A)\\0(g_j\le A)\end{cases}$（$g_i$ 中大于 $A$ 的前缀和）
- $cntg_i=\sum\limits^{i}_{j=1}g_j<A$（$g_i$ 中小于 $A$ 的个数）

在定义一个数 $base$ 插入 $A$ 之前的答案。

首先做两次优先队列预处理完成上述的几个数组。

接下来，我们只需要处理包含 $A$ 的几个区间。

如果把 $A$ 放在第 $i$ 个位置之后：

因为我们已经处理好了不加入 $A$ 时所有的和，所以我们只需要知道加入 $A$ 后的增量。

上面已经提到，我们只需要处理包含 $A$ 的区间。这样的区间一共有 $m$ 个——以 $A$ 开始的一个的和不以 $A$ 开始的 $m-1$ 个。

以 $A$ 开始的区间最值便很显然是 $A$ 和后面的 $m-1$ 个数的最大值取一个最大值，这后面的 $m-1$ 个数的最大值我们已经处理出来了，即 $g$ 数组。所以这部分的答案 $now$ 是 $\max\{
A,
g_{i+1}
\}$。

影响了那些区间呢？

简单推一下，影响的第一个区间的编号 $l$ 为 $\max
\{
1,
i-m+2
\}$，影响最后一个区间的编号 $r$ 为 $i$。

这样，我们就可以的出插入后的答案之和 $nxt$ 为 $A\times(cntg_r-cntg_{l-1})+sumG_r-sumG_{l-1}$。

但是，我们要求的是**增量**。所以，我们还要减去原来的和。由于以 $A$ 开始的区间是新生儿，所以不需要减。而前 $m-1$ 个区间不同，我们还要减去它原来的和 $pre=sumf_r-sumf_{l-1}$。


所以这部分的增量便是：
$$
now+nxt-pre
$$

那所有怎么统计呢?

很简单，用一个变量 $ans$ 取个情况的最大值即可。

到了这里，你以为完了？

不不不，还没完。

上面统计的只是把 $A$ 放在第 $i$ 个位置**之后**的情况，把 $A$ 放在第 $1$ 个位置之后也是可行的一种答案。所以应当先把 $ans$ 初始化为 $\max\begin{cases}A\\g_1\end{cases}$。

最后输出 $ans$，你就可以过了。

## code
```cpp
#include <bits/stdc++.h>
template <typename T> inline void read(T& x);
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg);
template <typename T>inline void write(T x);
template <typename T,typename ...Arg> inline void write(T x,Arg ...arg);
using namespace std;
const int MAXN = 5000000 + 5;
int n, m, A;
int a[MAXN];
int base = 0;   //插入A之前的和
int f[MAXN];    // f[i]: max(a[i] ~ a[i+m-1])
int g[MAXN];    // g[i]: max(a[i] ~ a[i+(m-1)-1])
int sumf[MAXN]; // f[i]的前缀和
int sumF[MAXN]; // f[i]中大于A的前缀和
int sumg[MAXN]; // g[i]的前缀和
int sumG[MAXN]; // g[i]中大于A的前缀和
int cntg[MAXN]; // g[i]中小于等于A的元素数量的前缀和
deque<int> qf, qg;
int main() {
	read(n,m,A);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	if (m == 1) {
		int ans = A;
		for (int i = 1; i <= n; i++)
			ans += a[i];
		write(ans);
		puts("");
		return 0;
	}
	//计算 f, sumf, sumF, base
	sumf[0] = sumF[0] = 0;
	for (int i = 1, j = 1; i <= n - m + 1; i++) {
		while (j - i + 1 <= m) {
			while (!qf.empty() && a[qf.back()] <= a[j])
				qf.pop_back();
			qf.push_back(j++);
		}
		while (!qf.empty() && qf.front() < i)
			qf.pop_front();
		f[i] = a[qf.front()];
		base += f[i];
		sumf[i] = sumf[i - 1] + f[i];
		sumF[i] = sumF[i - 1] + (f[i] > A ? f[i] : 0);
	}
	//计算 g,sumg,sumG
	sumg[0] = sumG[0] = cntg[0] = 0;
	for (int i = 1, j = 1; i <= n - (m - 1) + 1; i++) {
		while (j - i + 1 <= (m - 1)) {
			while (!qg.empty() && a[qg.back()] <= a[j])
				qg.pop_back();
			qg.push_back(j++);
		}
		while (!qg.empty() && qg.front() < i)
			qg.pop_front();
		g[i] = a[qg.front()];
		sumg[i] = sumg[i - 1] + g[i];
		sumG[i] = sumG[i - 1] + (g[i] > A ? g[i] : 0);
		cntg[i] = cntg[i - 1] + (g[i] <= A);
	}
	//计算插入 A 后的最大增量
	int ans = max(g[1], A); //放在第一个位置时的增量
	for (int i = 1; i <= n - m + 1; i++) {
		int now = max(g[i + 1], A); // A 开始往后的区间最值
		//插在i后面时，会影响前m-1个元素
		int l = max(1, i - (m - 1) + 1);
		int r = i;
		int pre = sumf[r] - sumf[l - 1]; //插入A之前的这些元素的最值答案之和
		int nxt = (cntg[r] - cntg[l - 1]) * A +
		          (sumG[r] - sumG[l - 1]); //插入A之后的这些元素的最值答案之和
		now += nxt - pre;
		ans = max(ans, now);
		// cout << i << ":" << l << "~" << r << " " << pre << " " << nxt << endl;
	}
	write(base+ans);
	puts("");
	return 0;
}
template <typename T> inline void read(T& x) {
	x=0;
	T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x=x*f;
	return;
}
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>inline void write(T x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x<10) {
		putchar(x+'0');
	} else {
		write(x/10);
		putchar(x%10+'0');
	}
}
template <typename T,typename ...Arg> inline void write(T x,Arg ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}
```

---

## 作者：lalaouye (赞：4)

本题一眼单调队列，但得知做法不是难点。

我们先把单调队列模板打完，定义 $b_i$ 为 $[i,i+m-1]$ 中的最大值，接下来考虑放 $A$。

### 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/kbztfiio.png)

如上图（字母的值为它是第几个字母），$A$ 可以放在 $0 \sim 8$ 的位置，假设 $m=3$，在查询过程中，若我们将 $A$ 放在 $4$ 的位置，本身我们以 $d$ 为起点的 $b_d=\max(a_d,a_e,a_f)$，而现在变成了 $\max(a_d,A,a_e)$，可以发现与 $a_f$ 无关了，也就是说，假设我们放在位置 $i$,那么起点为 $i-m+2 \sim i-1$ 的区间的最后一个值都会被 $A$ 从区间挤出去。

### 实现

故我们再进行第二次单调队列，定义 $c_i$ 为 $[i,i+m-2]$ 中的最大值（区间长度减一），因为 $A$ 不管在哪都是固定的，所以我们将每个 $c_i=\max(c_i,A)$，意思是当 $A$ 加入这一段内的最大值 。在枚举 $A$ 的位置 $i$ 时，我们将本次总量较原始开心值的变动设为 $ret$，那么我们将 $ret$ 初始化为 $c_{i+1}$，意思是以 $i$ 为起点的区间最大值，接着我们将收到 $A$ 影响的区间最大值减去，加上新的区间最大值，而其它的地方都是跟原始的一样所以不用管，剩下的交给前缀和，故式子为：

$ret=c_{i+1}-\sum\limits_{j=i-m+2}^i{b_j-c_j}$

$maxn=\max(maxn,ret)$

初始开心值为 $sum$

最后输出$sum+maxn$ 就好啦。 

### 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=5e6+5;
int n,m,A,tail,head=1,maxn,sum;
int q1[N],a[N],b[N],c[N],q2[N],s1[N],s2[N];
inline int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
int main(){
	n=rd(),m=rd(),A=rd();
	for(int i=1;i<=n;i++)a[i]=rd();
	for(int i=1;i<=n;i++){
		while(tail>=head&&i-q1[head]>=m)head++;
		while(tail>=head&&a[q1[tail]]<=a[i])tail--;
		q1[++tail]=i;
		if(i>=m)
		sum+=a[q1[head]],b[i-m+1]=a[q1[head]];
	}
	m--;
	tail=0,head=1;
	for(int i=1;i<=n;i++){
		while(tail>=head&&i-q2[head]>=m)head++;
		while(tail>=head&&a[q2[tail]]<=a[i])tail--;
		q2[++tail]=i;
		if(i>=m)
		c[i-m+1]=a[q2[head]];
	}
	for(int i=1;i<=n-m+1;i++)c[i]=max(c[i],A);
	for(int i=1;i<=n;i++)s2[i]=s2[i-1]+c[i];
	m++;
	for(int i=1;i<=n;i++)s1[i]=s1[i-1]+b[i];
	for(int i=0;i<=n;i++){
		int ret=c[i+1];
		ret-=s1[i];ret+=s1[max(0,i-m+1)];
		ret+=(s2[i]-s2[max(0,i-m+1)]);
		maxn=max(maxn,ret);
	}
	cout<<sum+maxn<<endl;
	return 0;
} 
```


---

## 作者：Proxima_Centauri (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/P8102)
# 题意
简化：有 $n$ 个数和一个长度 $m$，要从其中某个位置插入一个数 $A$，最大化所有长度为 $m$ 区间的最大值之和。
# 分析
蒟蒻看到这个题，一眼想到 ST 表，但是一看空间：**开不下**！（模拟赛好多同学因此挂分

那么还有什么算法可以求**固定长度区间的最大值**？——**单调队列**！

我们可以使用单调队列求出以下两个数组：
1. $f[i]$ 代表以 $i$ 为结尾的长度为 $m - 1$ 的区间中的最大值
2. 类似地，$g[i]$ 代表以 $i$ 为结尾的长度为 $m$ 的区间中的最大值

求出这两个数组意义何在？

注意到在数组的第 $i$ 个数前面插入一个数，对数组**最开始一部分和最后一部分的价值没有影响**。这里面就用到了 $g$ 数组，来存储不变的那部分。

与此同时，也有插入位置**前后一部分**的区域，将会**受到插入操作的影响**。对于这部分，我们记录 $f$ 数组。

对于在第 $i$ 个数前插入的情况，从 $i - 1$ 到 $i + m - 2$ 的 $f$ 数组是会受到影响的。属于**其中的下标在插入之后，都会形成新的区间**，而这些是跟 $A$ 有关系的。

那么我们对 $f$ 和 $g$ 数组执行如下操作：
```
for (int i = m + 1; i <= n; i++) g[i] += g[i - 1];
for (int i = m; i <= n; i++)
	f[i] = max(A, f[i]) + f[i - 1];
```
其中枚举起点是 $m$，因为在 $m - 1$ 之前的 $f$ 数组是没有意义的。记录前缀和是为了后面方便求解区间和。

最后在**预处理出两个数组**之后，计算答案只需要枚举插入的位置即可。

具体地，我们设插入**最后能影响到的位置**为 $i$，那么我们有如下推导（可以举个例子或者画个图帮助理解）：
1. 由假设容易知道以 $i + 1$ 为结尾，长度为 $m - 1$ 的串就**不受影响**了，那么从**该位置到 $n$ 位置**答案都可以使用 $g$ 数组的区间和表示
2. 可以由上面**对两数组的意义的分析**推出：插入的位置是在第 $i - m + 2$ 个元素以前。那么从**第 $i - m + 1$ 个元素及以前的答案也不受影响**，都要计算进去，使用 $g$ 数组的区间和计算
3. 那么从**第 $i - m + 1$ 到第 $i$ 位**都是会受影响的，**使用 $f$ 数组的区间和**（事先已经和 $A$ 取过最大值了）来表示

代码实现上当然还要注意**数组是否越界**的问题：
```
long long ans = 0;
for (int i = 0; i <= n; i++) 
	ans = max(ans, g[max(i - m + 1, 0)] + g[n] - g[i] + f[i] - f[max(i - m, 0)]);
```
大体的思路就是这样，注意对 $m = 1$ 的情况特判即可。
# AC code
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
long long f[5000010], a[5000010], g[5000010];
int q[5000010], st = 1, ed;
int main()
{
//	freopen("insert.in", "r", stdin);
//	freopen("insert.out", "w", stdout);
	int n, m;
	long long A;
	scanf("%d%d%lld", &n, &m, &A);
	long long sum = A;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		sum += a[i];
		if (st <= ed && i - q[st] >= m - 1) st++;
		while (st <= ed && a[q[ed]] < a[i]) ed--;
		q[++ed] = i;
		if (i >= m - 1) f[i] = a[q[st]];
	} // 单调队列求 f 数组
	if (m == 1)
	{
		printf("%lld\n", sum);
		return 0;
	} // 特判
	st = 1, ed = 0;
	for (int i = 1; i <= n; i++)
	{
		if (st <= ed && i - q[st] >= m) st++;
		while (st <= ed && a[q[ed]] < a[i]) ed--;
		q[++ed] = i;
		if (i >= m) g[i] = a[q[st]];
	} // 清空队列，不另外开新数组，节省空间
	for (int i = m + 1; i <= n; i++) g[i] += g[i - 1];
	for (int i = m; i <= n; i++)
		f[i] = max(A, f[i]) + f[i - 1];
	long long ans = 0;
	for (int i = 0; i <= n; i++) 
		ans = max(ans, g[max(i - m + 1, 0)] + g[n] - g[i] + f[i] - f[max(i - m, 0)]);
	printf("%lld\n", ans);
	return 0;
}
```
完结撒花！
# 总结
思维题，不难想到单调队列，关键在于想到用两次单调队列求出 $f$ 和 $g$ 数组，然后进行计算（这里真的很易错，我考场就挂在这里了）。

---

## 作者：Think (赞：2)

### 不得不说这是道单调队列的好题
## 1. 思路
首先看数据范围 ：  
$n \in [\ 1 ,5\times10^6\ ]$ 。   
这就注定了我们不可以用暴力插入再进行单调队列算法 。  
注意到插入队列的 **John 影响范围有限** 。  
所以我们可以由此入手 。  
## 2. 解法  
假设我们有序列：$1\ 2\ 3\ 4\ 5\ 6\ 7$ 。  
感染范围 $len$ 为 $3$ 。  
插入的位点为 $4$ 和 $5$ 之间 。  
则序列就变为了 $1\ 2\ 3\ 4\ x\ 5\ 6\ 7$ 。   
我们发现影响到的区间有 $[3,x]\ [4,5]\ [x,6]$ 。  
可以看作 $\textbf{len-1=2}$ 的区间插入 $x$ 后得到 。 

所以我们可以 **预处理** 两条:  
- $pre1$ 代表 长度为 $len$ 区间内元素的最大值的 **前缀和** 。  
- $pre2$ 代表 长度为 $len-1$ 区间内元素的最大值的 **前缀和** 。  

而在求 $pre2$ 的时候可以 **与 John 的值作比较** 选出较大值 。  

插入的位点为 $4$ 和 $5$ 之间时，答案为：     
$max\{1,2,3\}+max\{2,3,4\}+max\{3,4,x\}$   
$+max\{4,x,5\}+max\{x,5,6\}+max\{5,6,7\}$ 。

即： $pre1[4]+(\ pre2[6]-pre2 [4-1]\ )+(\ pre1[7]-pre1[6]\ )$ 。  
插入 $i$ 和 $i+1$ 之间时 ，令:  
- $l=i$ 。
- $r=i+len-1$ 。  

进而得出通项： 
- $pre1[l]+(\ pre2[r]-pre2[l-1]\ )+(\ pre1[n]-pre1[r]\ )$ 。  

写的时候注意判断 $l$ 和 $r$ **是否越界** 即可 。
## 3. Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e6+5;
int n,len,A;
int a[maxn];
int pre1[maxn],pre2[maxn];
struct Node{
	int val;
	int id;
}q[maxn];
void solve1(){//手写单调队列 
	memset(q,0,sizeof(q));
	int head=1,tail=0;
	for(int i=1;i<=n;i++){
		while(head<=tail&&a[i]>=q[tail].val) tail--;
		q[++tail].val=a[i];
		q[tail].id=i;
		while(q[head].id<=i-len)head++;
		if(i>=len) pre1[i]=pre1[i-1]+q[head].val;
	}
}
void solve2(){//手写单调队列 
	memset(q,0,sizeof(q));
	int head=1,tail=0;
	for(int i=1;i<=n;i++){
		while(head<=tail&&a[i]>=q[tail].val) tail--;
		q[++tail].val=a[i];
		q[tail].id=i;
		while(q[head].id<=i-len+1)head++;
		if(i>=len-1) pre2[i]=pre2[i-1]+max(q[head].val,A);//与 John 的值作比较选出较大值
	}
}
int influ(int i){
	int l=i,r=i+len-1;
	if(l<1) l=1;
	if(r>n) r=n;//判断越界 
	return pre1[l]+(pre2[r]-pre2[l-1])+(pre1[n]-pre1[r]);//通项 
}
int main(){
	scanf("%d%d%d",&n,&len,&A);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	solve1();solve2();
	int ans=-1;
	for(int i=0;i<=n;i++) ans=max(ans,influ(i));//枚举插入点 
	printf("%d",ans);
	return 0;
}
```
最后~~吐槽一下~~，这道题仅仅将 John 插入头尾就可以得到 $90$ pts

---

## 作者：lalaji2010 (赞：0)

# [P8102 「LCOI2022」 Cow Insertion](https://www.luogu.com.cn/problem/P8102)

## 分析

单调队列好题。

对于一个静态区间，我们是容易使用单调队列维护区间最大值的。所以我们首先可以尝试枚举插入点，都跑一遍单调队列，这样就有了一个 $O(n^2)$ 的做法。

然后呢，你会发现：对于将牛插入 $i$ 和 $i+1$ 之间，以及将牛插入 $i+1$ 和 $i+2$ 之间两种情况，更多的区间最大值是没有变化的。进而我们想方设法求出来哪些量变化和不变化的规律进而优化时间复杂度。

来看一组例子。

$n=6,m=3,A=6$，序列为：$1\ 1\ 4\ 5\ 1\ 4$。



当我们将 $A$ 插入第 $3$ 个元素和第 $4$ 个元素之间，原序列变为：$1\ 1\ 4\ 6\ 5\ 1\ 4$。这时答案应为 $\max\{1,1,4\}+\max\{1,4,A\}+\max\{4,A,5\}+\max\{A,5,1\}+\max\{5,1,4\}$，我们发现，答案由一部分长度为 $m$ 的区间最大值和一部分长度为 $m-1$ 的区间和 $A$ 取最大值构成。

推广一下，你会发现不论 $A$ 插在哪里，答案的构成都是如此。

我们将原序列中区间 $[i,i-m+1]$ 的最大值记为 $maxx1_i$，保证 $i \geq m$，将原序列中区间 $[i,i-m+2]$ 的最大值记为 $maxx2_i$，保证 $i \geq m-1$。

假设将 $A$ 插在第 $k$ 个元素与 $k+1$ 个元素之间，则有答案为：

$$\sum_{i=1}^{k}maxx1_i+ \sum_{i=k}^{k+m-1} maxx2_i+\sum_{i=k+m}^{n}maxx1_i$$

设 $sum1_x=\sum_{i=1}^{x}maxx1_i$，$sum2_x= \sum_{i=1}^{x}maxx2_i$，则上式等价于：

$$sum1_k+sum2_{k+m-1}-sum2_{k-1}+sum1_n-sum1_{k+m-1}$$

处理一下 $k-1$ 和 $k+m-1$ 的边界情况就好啦。

当然，还要考虑 $m=1$ 的特殊情况，我们难以直接用单调队列维护 $sum1$ 和 $sum2$，于是特判一下，这时答案是所有元素和加 $A$。

## AC code
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
using namespace std;
const int N=5e6+5;
int n,m,A;
int a[N],q[N];
long long sum1[N],sum2[N];
long long res=0;
int main(){
	cin>>n>>m>>A;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(m==1){
		res=A;
		for(int i=1;i<=n;i++){
			res+=a[i];
		}
		cout<<res<<"\n";
		return 0;
	}
	int h=1,t=0;
	for(int i=1;i<=n;i++){
		while(h<=t&&a[i]>=a[q[t]]) t--;
		q[++t]=i;
		while(q[h]<=i-m) h++;
		if(i>=m) sum1[i]=sum1[i-1]+a[q[h]];
	}
	h=1,t=0;
	for(int i=1;i<=n;i++){
		while(h<=t&&a[i]>=a[q[t]]) t--;
		q[++t]=i;
		while(q[h]<=i-m+1) h++;
		if(i>=m-1) sum2[i]=sum2[i-1]+max(a[q[h]],A);
	}
	for(int i=0;i<=n;i++){
		int l=i,r=i+m-1;
		res=max(res,sum1[l]+(sum2[r]-sum2[max(l-1,0)])+(sum1[n]-sum1[min(n,r)]));
	}
	printf("%d",res);
	return 0;
}
```

---

## 作者：SnowFlavour (赞：0)

## 前情提要

这题挺好。

学校模拟赛老师选了这道题，结果没想起来单调队列，就写了个 ST 表，经过极限卡常，获得成就，MLE！

## 我会暴力！

这个做法非常直接，题目让干什么你就干什么就行了呗。我们考虑枚举每一个位置，用暴力方法（或者用链表，区别不大）插入那个值就可以了。然后我们暴力扫描所有区间求和。总复杂度 $O(n^2m)$，啥也过不了。（但是场上可以对拍）

## 我会单调队列！

我们会发现，在不加入那只新奶牛的时候，这个题目就是一个经典的单调队列模板。具体参见 [OIWiki](https://oi-wiki.org/ds/monotonous-queue/) 的内容。

但是问题是我们不能只用一个单调队列，原因是我们一但插入新的东西，这个算法就需要重算，那么整个复杂度就立刻变成平方级别。那怎么办呢？

## 我会画图！

这个时候，硬推是不行了，我们考虑研究样例。

当我们插入一个元素的时候，思考我们都改变了哪些，也就是对答案有多少贡献。

来看看图：

![](https://s21.ax1x.com/2024/10/06/pA82OVs.png)

上方的图是原区间，下方的图是修改后的区间。

不难发现，插入操作其实是“撕裂”了原来的区间，然后加上了一些新的区间。

在图中，我将被撕裂的原区间用红色表示，新产生的区间用蓝色在下方表示。可以发现，如果我们在 $i$ 元素和 $i-1$ 元素间插入一个数，被撕裂的区间就是**同时**跨过这两个元素的长度为 $m$ 的区间。更形式化地，就是区间 $[i-m+1,i]$ 到 $[i-1,i+m-2]$ 的所有区间。

新增的区间就是所有跨过这两个元素中**任意一个**的长度为 $m-1$ 的区间（因为插入以后就会增加一个长度）。更形式化地，就是区间 $[i-m+1,i-1]$ 到 $[i,i+m-2]$ 的所有区间。

那么我们就有了思路：先找出来在原序列上的答案，然后枚举每一个可以添加的位置，减去所有被撕裂的区间的最大值，加上所有生成的区间的最大值，就是这个位置的答案。

撕裂的区间最大值可以用单调队列来求，生成的区间也可以。我们只要再搞一个单调队列，维护所有长度为 $m-1$ 的区间最大值就搞定了。最后，我们对这个值和 $A$ 取最大值就可以解决了。

这样一来，时间复杂度就降到了 $O(nm)$。怎么能继续优化呢？

## 我会尺取法！

好吧，其实这并不是一个严格意义上的尺取法，不过思想是一致的——只修改变化的量。

我们考虑，当从一个位置，转移到下一个位置的时候，答案发生了怎样的变化：

![](https://s21.ax1x.com/2024/10/06/pA8R1Zd.png)

当 $A$ 右移一格的时候，总共会产生四种变化：

1. 之前被撕裂的区间复原。（绿色）
2. 撕裂新的区间。（红色）
3. 之前生成的区间消失。（紫色）
4. 生成新的区间。（蓝色）

也就是说，我们在从前面一个位置转移到当前位置的时候，我们需要且仅仅需要进行上面四种操作。这四个操作也很简单，和刚才的做法几乎一样，这里就不展开说了。

最终，我们就有了一个成熟的算法：

1. 暴力找出当 $A$ 加在第一个位置时的状态。
2. 向下一个状态转移，只进行四次计算。
3. 得到最终答案。

这么着，整个复杂度就直接回归到 $O(n)$ 了，这也是理论最优复杂度（因为还有输入复杂度摆在那呢）。

## 我会敲键盘！

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<deque>
#include<cstdio>
#define int long long
#define max(X,Y) ((X)>(Y)?(X):(Y))
using namespace std;
const int N=5e6+10;
int a[N],cnt[N],f[N],g[N];
int n,m,A,ans;
void fi(){
    freopen("insert.in","r",stdin);
    freopen("insert.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

inline void init(){
    deque<int>q,em;
    for(int i=1;i<=m;i++){
        while(!q.empty()&&a[q.back()]<=a[i])q.pop_back();
        q.push_back(i);
    }
    f[1]=a[q.front()];
    for(int i=m+1;i<=n;i++){
        while(!q.empty()&&a[q.back()]<=a[i])q.pop_back();
        q.push_back(i);
        while(!q.empty()&&i-q.front()>=m)q.pop_front();
        f[i-m+1]=a[q.front()];
    }
    q=em;
    for(int i=1;i<=m-1;i++){
        while(!q.empty()&&a[q.back()]<=a[i])q.pop_back();
        q.push_back(i);
    }
    g[1]=a[q.front()];
    for(int i=m;i<=n;i++){
        while(!q.empty()&&a[q.back()]<=a[i])q.pop_back();
        q.push_back(i);
        while(!q.empty()&&i-q.front()>=m-1)q.pop_front();
        g[i-m+2]=a[q.front()];
    }
}
inline int ask(int x,int y){
    if(y-x==m-1)return f[x];
    else return g[x];
}

signed main(){
    // fi();
    cin>>n>>m>>A;
    for(int i=1;i<=n;i++)cin>>a[i];
    init();
    // cout<<g[3]<<endl;
    for(int i=1;i+m-1<=n;i++){
        int mx=ask(i,i+m-1);
        ans+=mx;
    }
    int maxa=max(ans+max(A,ask(1,m-1)),ans+max(A,ask(n-m+2,n)));
    
    for(int i=1;i<=m&&i+m-2<=n;i++){
        ans+=max(ask(i,i+m-2),A);
    }
    for(int i=1;i<m&&i+m-1<=n;i++){
        ans-=ask(i,i+m-1);
        // cout<<ans<<endl;
    }
    // cout<<ans<<endl;
    maxa=max(ans,maxa);
    for(int i=m;i<=n-m+1;i++){
        ans+=ask(i-m+1,i);
        // cout<<i<<" "<<ans<<endl;
        ans-=max(ask(i-m+1,i-1),A);
        // cout<<i<<" "<<ans<<endl;
        ans-=ask(i,i+m-1);
        // cout<<i<<" "<<ans<<endl;
        ans+=max(ask(i+1,i+m-1),A);
        // cout<<i<<" "<<ans<<endl;
        maxa=max(maxa,ans);
        // cout<<i<<" "<<ans<<endl;
    }

    cout<<maxa<<endl;
}
```

---

## 作者：_Fatalis_ (赞：0)

~~听着《打上花火》，不知不觉推出了式子~~

初碰此题，看见 $n \le 5 \times 10^6$，感觉 $n \lg n$ 能过啊  
（$5\times 10^6 \times \lg5\times10^6 \approx 5\times10^6 \times 22.2534 \approx 1.1126 \times 10^8$）

心想可能得卡个常数了（~~事实后来我是大常数选手~~）

---

看到题面立马想到插入 $A$ 的影响是有限的，大概是向左向右 $m$ 个数。

整个题目都在求 $\max_x^y$，干脆将所有 $\max$ 得到的数单独算出来。想到算定长最值，可以用 [滑动窗口](/problem/P1886) $O(n)$ 解决，所以将值设出来：
$$
s_i = \max _ {j = i} ^ {i + m - 1} a_j \ (1 \le i \le n - m + 1)
$$
那么未插入 $A$ 的答案即为：
$$
ans_1 = \sum _ {i = 1} ^ {n - m + 1} s_i
$$
现在考虑插入 $A$ 之后答案将会变成什么。

如果将 $A$ 插入到 $a_k$ 后面，序列长这个样子：
$$
\cdots, a_k, A, a_k +1, \cdots
$$
那么左端没有覆盖到 $A$ 的地方是不会受 $A$ 的影响的。

有**右边界** $i + m - 1 = k$（$s_i$ 的右端点刚好与 $a_k$ 重合）

所以**右边界**为 $i = k - m + 1$。

所以左端未受影响的答案为
$$
ans_2 = \sum _ {i = 1} ^ {k - m + 1} s_i
$$
同理，

右端**左边界** $i = k + 1$，

则右端未受影响的答案为
$$
ans_3 = \sum _ {i = k + 1} ^ {n - m + 1} s_i
$$
现在需要处理中间受影响的部分。

观察到覆盖 $A$ 的地方有个共同点，就是他们对答案的贡献为原长度为 $m - 1$ 的贡献与 $A$ 取 $\max$。

将长度为 $m - 1$ 的 $\max$ 结果列出来：
$$
u_i = \max _ {j = i} ^ {i + m - 2} a_j \  (1 \le i \le n - m + 2)
$$
 $u_i$ 与 $s_i$ 相似。

那么，$a_i, \cdots, a_k, A, a_{k + 1}, \cdots, a_{i + m - 2}$ 的最终贡献为
$$
\max\{A, u_i\}
$$
左边界为 $i + m - 2 = k$（刚好 $A$ 踩到原来 $k + 1$ 的位置）

所以 $i = k - m + 2$。

右边界同理，$i = k + 1$。

所以贡献为：
$$
ans_4 = \sum _ {i = k - m + 2} ^ {k + 1} \max\{A, u _ i\}
$$
 所以加入 $A$ 的最终答案为：
$$
ans' = ans _ 2 + ans _ 4 + ans _3
$$
即
$$
ans' = \sum _ {i = 1} ^ {k - m + 1} s_i + \sum _ {i = k - m + 2} ^ {k + 1} \max\{A, u _ i\} + \sum _ {i = k + 1} ^ {n - m + 1} s_i
$$
此时可以直接通过求出 $s$ 即 $u$（需要先进行 $\max$ 操作）的前缀和，$O(n) \times O(1)$ 枚举求解 $ans'$。

但是，式子有点乱。

将 $ans' - ans$，得到加入 $A$ 的贡献：
$$
ans'' = ans' - ans = \sum _ {i = k - m + 2} ^ {k + 1} \max\{A, u _ i\} - \sum _ {i = k - m + 2} ^ {k} s _ i
$$
于是可以得到一个用 `std::vector` 实现的超大常数 code：

```cpp
#include <cstdio>
#include <vector>
#include <deque>

// monotony_queue 即 单调队列
std::deque<std::pair<int, int> > dq;
int push_back(int id, int x, int m) {
    while (!dq.empty() && dq.back().second <= x) dq.pop_back();
    dq.push_back({id, x});
    while (!dq.empty() && dq.front().first <= id - m) dq.pop_front();
    return dq.front().second;
}
std::vector<int> monotony_queue(std::vector<int> v, int m) {
    // init
    dq.clear();
    std::vector<int> ans;

    // main
    for (int i = 0; i < m - 1; i++) push_back(i, v[i], m);
    for (int i = m - 1; i < v.size(); i++) {
        ans.push_back(push_back(i, v[i], m));
    }
    return ans;
}

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int main() {
    static std::vector<int> v, s, u;
    int n, m, A, x;

    // input
    scanf("%d%d%d", &n, &m, &A);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        v.push_back(x);
    }

    // init s, u
    s = monotony_queue(v, m);
    u = monotony_queue(v, m - 1);

    u[0] = max(u[0], A);
    for (int i = 1; i < u.size(); i++) {
        u[i] = max(u[i], A);
        u[i] += u[i - 1];
    }
    u.insert(u.begin(), 0);

    for (int i = 1; i < s.size(); i++) {
        s[i] += s[i - 1];
    }
    s.insert(s.begin(), 0);

    int maxn = -998244353; // ans''
    for (int k = 1; k <= n; k++) { // 这里记得算全 k，否则会 WA
        int l = max(0, k - m + 1);
        int r = min(n - m + 1, k);
        maxn = max(maxn, u[r + 1] - u[l] - s[r] + s[l]);
    }
    maxn += *s.rbegin(); // Don't forget add ans
    printf("%d\n", maxn); // ans'
    return 0;
}
```



---

