# Ringed Genesis

## 题目背景

Enzyme runs through the Ringed Genesis，just like Rabbit runs through a Ring. 

## 题目描述

有一个长长的环，环由 $n$ 个格子首尾相接形成，依次编号 $0$ 至 $n-1$。

还有一种动物——兔子。兔子的步长为 $k$。若兔子当前在第 $i$ 个格子，那么下一秒它将跳到第 $(i+k)\bmod n$ 个格子。

现在有 $m$ 只兔子，第 $i$ 只兔子的初始格子为第 $p_i$ 个格子。随着时间的流逝，有些格子被兔子经过了，有些却一直没有被兔子经过。

你需要求出的是，有多少个格子永远不可能被兔子经过。

## 说明/提示

子任务 1（$10\%$）：$k=1$。

子任务 2（$20\%$）：$k|n$，也即 $\gcd(k,n)=k$。

子任务 3（$25\%$）：$1\leq n\leq 1000$，$1\leq m\leq 1000$。

子任务 4（$45\%$）：无特殊限制。

对于全部数据，$1 \leq n \leq 10^6$，$1 \leq m \leq 10^6$，$1 \leq k \leq n$。

## 样例 #1

### 输入

```
4 2 2
0 1
```

### 输出

```
0```

## 样例 #2

### 输入

```
4 2 2
0 2
```

### 输出

```
2```

# 题解

## 作者：dingcx (赞：64)

作为$2020$年的第$2$道比赛题，还是比较简单的。
## 思路
这题代码并不难写，重点在于思路。

先举几个例子。如果环长$8$，步长$2$，会出现这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/5wulzihg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现，当初始点是红点时，蓝色的$4$块永远跳不到，否则红色的$4$块永远跳不到。

如果环长$8$，步长$6$，会出现这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/0zbgabw9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

和上面效果是一样的。

再如果环长$8$，步长$4$，又会出现这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/fi674rr1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

出现了$4$种颜色。

综上，不难发现颜色的个数就是**环长和步长的最大公约数**。

只要一种颜色有一个格子上有兔子，那么所有这种颜色上**都能够跳到**。

答案就是**跳不到的颜色个数**乘以**每个颜色有多少格**。

这样，代码就呼之欲出了。
## 代码
~~相信没有多少人喜欢上面的一通分析吧~~，那么，你们喜欢的代码来了——
```cpp
#include<cstdio>
using namespace std;
const int MAXN=1e6+10;
bool s[MAXN];//s[i]表示有没有兔子在颜色i上
int gcd(int num1,int num2){//标准gcd求最大公约数
	if(num2==0) return num1;
	return gcd(num2,num1%num2);//辗转相除法
}
int main(){
	int n,m,d,a,ans=0;
	scanf("%d%d%d",&n,&m,&d);
	int gc=gcd(n,d);//求出颜色个数
	for(int i=1;i<=m;i++){
		scanf("%d",&a);
		s[a%gc]=1;//标记
	}
	for(int i=0;i<gc;i++)
		if(!s[i]) ans+=(n/gc);//跳不到就加上每个颜色的格数
	printf("%d",ans);
	return 0;//华丽结束
}
```
看我这么辛苦画了这么些个图，总得点个赞再走呀！

---

## 作者：TEoS (赞：7)

签到题，还是很一眼的


------------
**思路分析**

很容易想到暴力模拟。简单分析后可以发现，由于步长相同，当一只兔子走到已走过的格子上时，之后走的格子都会是一样的，可以用这个性质对暴力进行优化，这样每个格子最多只会走一次。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e6+100;
int n,m,k,ans;
bool pd[N];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		while(!pd[x])
		{
			pd[x]=1;
			x=(x+k)%n;
		}//模拟直到走到已走过的格子
	}
	for(int i=0;i<n;i++)
		ans+=!pd[i];//统计没走过的格子数
	printf("%d",ans);
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：6)

首先，看到这题暴力应该很好想，就是按照题目的描述，给到达的点做标记，然后在统计即可。可是这会超时。
代码如下
```cpp
//O3??
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
char buf[100010], *p1, *p2;
//#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++
template<class item>
inline item read() {
    item res = 0;
    bool negative = 0;
    char ch = getchar();
    while (!isdigit(ch)) negative |= ch == '-', ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return negative ? -res : res;
}
template<class item>
inline item read(item & t) {
    t = read<item>();
    return t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t), read(args...);
}
//bool find(int i, int x) {
//	return binary_search(a[i].begin(), a[i].end(), x);
//}
//bool check(int x) {
//	int ans = 0;
//	for (register int i = 1; i <= n; ++i)
//		ans += find(i, x);
//	return ans == p;
//}
int n, m, k, c[1000010];
int main() {
	read(n, m, k);
	if (k == 1) {
		puts("0");
		return 0;
	}
	for (register int i = 1; i <= m; ++i) {
		int val1, val2;
		val2 = read(val1);
		do {
			c[val1] = 1;
			val1 = (val1 + k) % n;
		} while (val1 != val2);
	}
	int ans = 0;
	for (register int i = 0; i < n; ++i)
		ans += !c[i];
	cout << ans;
}
```
然后我们可以通过骗分
```cpp
//O3??
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
char buf[100010], *p1, *p2;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++
template<class item>
inline item read() {
    item res = 0;
    bool negative = 0;
    char ch = getchar();
    while (!isdigit(ch)) negative |= ch == '-', ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return negative ? -res : res;
}
template<class item>
inline item read(item & t) {
    t = read<item>();
    return t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t), read(args...);
}
int n, m, p, ans[N], f[10 * N];
//bool find(int i, int x) {
//	return binary_search(a[i].begin(), a[i].end(), x);
//}
//bool check(int x) {
//	int ans = 0;
//	for (register int i = 1; i <= n; ++i)
//		ans += find(i, x);
//	return ans == p;
//}
int main() {
	puts("0");
}
```
得到发现，输出零的几个点都是超时的数据点。
于是可以特判$m$的大小，如果太大直接输出零
还可以加一个剪枝，如果访问到以前走过的点就直接结束(~~不过加了好像还慢了~~)
```cpp
//O3??
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
char buf[100010], *p1, *p2;
//#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++
template<class item>
inline item read() {
    item res = 0;
    bool negative = 0;
    char ch = getchar();
    while (!isdigit(ch)) negative |= ch == '-', ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return negative ? -res : res;
}
template<class item>
inline item read(item & t) {
    t = read<item>();
    return t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t), read(args...);
}
//bool find(int i, int x) {
//	return binary_search(a[i].begin(), a[i].end(), x);
//}
//bool check(int x) {
//	int ans = 0;
//	for (register int i = 1; i <= n; ++i)
//		ans += find(i, x);
//	return ans == p;
//}
int n, m, k, c[1000010];
int main() {
	read(n, m, k);
	if (k == 1) {
		puts("0");
		return 0;
	}
	if (m >= 50000) {
		puts("0");
		return 0;
	}
	for (register int i = 1; i <= m; ++i) {
		int val1, val2;
		val2 = read(val1);
		do {
			c[val1] = 1;
			val1 = (val1 + k) % n;
		} while (val1 != val2);
	}
	int ans = 0;
	for (register int i = 0; i < n; ++i)
		ans += !c[i];
	cout << ans;
}
```
所以就这样差不多了，还在最优解的[第一页](https://www.luogu.com.cn/record/list?pid=P5887&orderBy=1&status=&language=3&page=1)


---

## 作者：厨神 (赞：3)

土槽一下赛后视频讲解，第一个同学讲的太快了啊。

这个题主要是考察标记，就是兔子什么时候停止跳呢，就是跳到他跳过的位置后，所以这个题复杂度就是格子的大小。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1000010
int n,m,k,t,a[N],ans;
int main(){
	cin >> n >> m >> k;
	for(int i=0;i<m;i++){
		cin >> t;
		if(a[t]) continue;
		while(1){
			if(a[t]==1) break;
			a[t]=1;
			t+=k;
			t%=n;
		}
	}
	for(int i=0;i<n;i++){
		if(a[i]==0) ans++;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：低調 (赞：3)

~~一看题目，又没有样例（吐血）~~

仔细看完一遍题目和特殊数据后，第一下想到的是裴蜀定理 ~~（不要问我裴蜀定理是什么）~~。

很明显在一个长度为定值的区间，每只兔子能且仅能跳到一个格子上，区间的长度便是$gcd(n,k)$~~（见“裴蜀定理”）~~，这样我们只需要计算出在同一段区间有几个格子没有任何一只兔子跳到过，可以以$[1,gcd(n,k)]$来计算每一个区间中无法跳到的格子，最后乘以这样的区间总数$\dfrac{n}{gcd(n,k)}$。

接下来上代码 ~~（在比赛中速度蛮快的，只有13$ms$，比赛后加了快读反而更慢）~~：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read() {//快读
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-')ch=getchar();
	if(ch=='-')ch=getchar(),f=-1;
	while(isdigit(ch))x=(x*10)+(ch^48),ch=getchar();
	return x*f;
}
long long a[1000001],k,p,n,m,i,tot;
int main() {
	n=read(),m=read(),k=read();
	k=__gcd(k,n);//先进行预处理，算出最小区间的长度，方便后面查找，可以理解为减小步子大小
	if(k==1) {//特判，此时任意一只兔子可以跳完全部的格子
		cout<<0;//不能跳到的格子个数为0
		return 0;
	}
	for(i=1; i<=m; i++) {
		p=read();
		a[p%k+1]++;//在一个区间内进行改变，若不为0说明可以跳到
	}
	for(i=1; i<=k; i++) {
		if(a[i]==0)tot++;//区间中不能跳到的格子个数++
	}
	cout<<tot*n/k;//每一个区间不能跳到的个数*区间个数
	return 0;
}
```

---

## 作者：过往梦魇之殇 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P5887)

做法：无 ~~（暴力+优化）~~   

**思路简述：**

容易想到一个格子只能最多走一遍，重复到达则接下来经过的格子都是之前走过的
（因为步长不变，显然）

而后我们可以考虑暴力，扫每一个兔子经过的格子，虽然做法看起来是$O(mn)$，但是加了剪“枝”便可以水过了...

**代码展示：**

```cpp
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<complex>
#include<climits>
#define re register
#define in inline
#define ll long long
#define pi acos(-1.0)
#define inf 2147483640
using namespace std;
in int read()
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
in void write(int X)
{
    if(X<0)putchar('-'),X=-X;
    if(X>=10)write(X/10);
    putchar(X%10+'0');
}
int n,m,k,cnt;
bool vis[1000010];
void sign(int x){
	while(!vis[x]){
		vis[x]=1;
		x=(x+k)%n;
	}
}
int main()
{
	n=read();
	m=read();
	k=read();
	for(re int i=1;i<=m;++i){
		int p;
		p=read();
		sign(p);
	}
	for(re int i=0;i<n;++i){
		if(!vis[i]){
			++cnt;
		}
	}
	write(cnt);
    return 0;
}
```
然后就愉快地$AC$辣！！！

> $Thanks$ $For$ $Watching!$

---

## 作者：PDY08 (赞：1)

#### 这道题一看就想用模拟解决，直接上代码吧（解释都写在代码里）
```
#include<iostream>
using namespace std;
int n,m,k,i,a[1000001],b,c,s;//数组a用来记录踩到的次数，c表示踩到的地方
int main(){
	cin>>n>>m>>k;
	for(i=1;i<=m;i++){
		cin>>b;
		c=b;
		while(a[c]<2){//当没有第二只兔子踩这里
			a[c]++;//标记已经踩过
			c+=k;//跳到下一个地方
			c%=n;//以防超出范围
		}
	}
	for(i=0;i<=n-1;i++){//检查每一个格子踩了几次
		if(a[i]==0){//没被踩过
			s++;
		}
	}
	cout<<s;
} 
```
### 在判断踩没踩过时，既可以使用整型标记，又可以使用布尔型（bool）判断。

---

## 作者：flysong (赞：1)

这是我的第一篇题解。

[博客内食用更佳a](https://flysong.blog.luogu.org/solution-p5887)

我来发 ~~(歪)~~ 题解了。

看到楼上一堆巨佬的什么$gcd()$和裴蜀定理，我只想说一句：

这题如果加点优化暴力能过。

首先先特判$k$，当$k=1$时，直接输出$0$(显而易见,当步长等于$1$时，兔子能走遍所有的格)。

接下来对于输入，我们进行一点优化——

快读了解一下？

下面贴快读代码:
```cpp
inline int read()
{
	char ch=getchar();
	int f=1,num=0;

	while(!isalnum(ch))
	{
		if(ch=='-')
		{
			f=-1;
			break;
		}
		ch=getchar();
	}
	while(isalnum(ch))
	{
		num=num*10+(ch-'0');
		ch=getchar();
	}
	return num*f;
}
```
接下来在读入时把兔子所在格进行标记并将结果$-1$(结果初始设为总格数)。

然后就是程序主体。我们进行循环来找到走过的格子。每找到一个,就将结果$-1$。注意千万不要在找到已经走过的格子后再将结果$-1$,结束条件为任意一只兔子回到起点。

最后输出结果。


$Code$
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	char ch=getchar();
	int f=1,num=0;

	while(!isalnum(ch))
	{
		if(ch=='-')
		{
			f=-1;
			break;
		}
		ch=getchar();
	}
	while(isalnum(ch))
	{
		num=num*10+(ch-'0');
		ch=getchar();
	}
	return num*f;
}

int rabbit[1000000]={};
bool way[1000000]={};
int s=0;

int main(int argc, char const *argv[])
{
	int n=read(),m=read(),k=read();
	int sum=n;
	if(k==1)
	{
		printf("0");
		return 0;
	}
	for(int i=0;i<m;i++)
	{
		rabbit[i]=read();
		if(!way[rabbit[i]])
		{
			sum--;
		}
		way[rabbit[i]]=true;
	}
	s=rabbit[0];
	do
	{
		for(int i=0;i<m;i++)
		{
			rabbit[i]+=k;
			rabbit[i]%=n; 
			if(!way[rabbit[i]])
			{
				sum--;
			}
			way[rabbit[i]]=true;
			if(sum==0)
			{
				cout<<sum;
				return 0;
			}
		}
	}
	while(s!=rabbit[0]);
	cout<<sum;
	return 0;
}
```
这就是AC代码。


---

## 作者：友利奈緒 (赞：1)

管他那么多，先模拟一遍再说啦！

思路很简单，弄一个bool数组为true，当跳到某个格子就将那个格子标为false

如果跳到false的格子里就说明会和前面一样循环，就跳出循环

最后枚举为true的个数

直接上代码
```cpp
#include<bits/stdc++.h>
#define int long long//这个纯属个人写代码习惯，不要在意
using namespace std;
bool a[1000006];
signed main()//这是因为main函数只能int，而我int又变成了long long
{
	int n,m,k;
	cin>>n>>m>>k;
	int x;
	for(int i=0;i<n;i++)
	a[i]=true;
	for(int i=1;i<=m;i++)
	{
		cin>>x;
		int now=x;//now表示现在所在的格子
		while(a[now]==true)
		{
			a[now]=false;
			now=(now+k)%n;
		
		}
	}
	int cnt=0;//cnt表示没到过的格子数量
	for(int i=0;i<n;i++)
	{
		if(a[i]==true) cnt++;
	}
	cout<<cnt;
	return 0;
}
```


---

## 作者：DreamFox (赞：0)

本题思路：

暴力模拟，把每个兔子所在的格子枚举到回到原来位置

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,sum=0,c;
bool a[1000000],b[1000000];
int gcd(int a,int b)
{
    if(a%b==0)return b;
    else return gcd(b,a%b);
}
int main()
{
	cin>>n>>m>>k;
	if(k==1)cout<<"0\n",exit(0);
	for(int i=0;i<m;i++)
	{
		cin>>c;
		int ak=c;
		a[c]=1;
		c=(c+k)%n;
		a[c]=1;
		while(c!=ak)
		{
			c=(c+k)%n;
			a[c]=1;
		}
	}
	for(int i=0;i<n;i++)
	if(a[i]==0)++sum;
	cout<<sum<<endl;
	return 0;
}
```
~~这就A了？~~

没有，这只得了55分

如何优化呢？

我们可以发现，当某个格子对$gcd(n,k)$取模的结果与另外一个格子对$gcd(n,k)$取模的数相等，那么它们每次循环出现的数是一样的。

所以我们就可以凭借这一点，利用一个数组记录模数，如果模数已经出现过，那么就$continue$

$AC$ $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,sum=0,c;
bool a[1000000],b[1000000];
int gcd(int a,int b)
{
    if(a%b==0)return b;
    else return gcd(b,a%b);
}
int main()
{
	cin>>n>>m>>k;
	int ac=gcd(n,k);
	if(k==1)cout<<"0\n",exit(0);
	for(int i=0;i<m;i++)
	{
		cin>>c;
		if(b[c%ac]==1)continue;
		b[c%ac]=1;
		int ak=c;
		a[c]=1;
		c=(c+k)%n;
		a[c]=1;
		while(c!=ak)
		{
			c=(c+k)%n;
			a[c]=1;
		}
	}
	for(int i=0;i<n;i++)
	if(a[i]==0)++sum;
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：nxt_permutation (赞：0)

这道题分为2种情况：
- 1.当n与k的最大公约数是1，即他们互质时，所有格子都会被走到，此时输出0；
- 2.当n与k的最大公约数不是1时，设为now，兔子的出发点为 _pi_ 则兔子能走到所有模now同余于 _pi_ 的点。

- 点有没有遍历过直接用个bool数组存储即可

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int p[1000001];
bool vis[1000001];//是否遍历过
int gcd(int a,int b)//辗转相除法
{
	if(a%b==0) return b;
	else return gcd(b,a%b);
}
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	int now=gcd(n,k);
	for(int i=0;i<m;i++) scanf("%d",&p[i]);
	if(now==1) cout<<0<<endl;
	else
	{
		int ans=n;
		for(int i=0;i<m;i++)
		{
			if(!vis[p[i]%now])
			{
				ans-=n/now;
				vis[p[i]%now]=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：李若谷 (赞：0)

比赛的时候我竟然想了好久，我太弱了

简单的数学

n环，k步的一个兔子可以到n/gcd(n,k)个地方

由于每一个兔子一次都跳k步，所以如果一个兔子能跳到另一个兔子的起点，那么这两个兔子的路径回重复。所以只要判断每个兔子的路径是否重复，如果不重复就+n/gcd(n,k)。

代码：
```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
int p[1000001];
bool f[1000001];
int gcd(int a,int b)
{
    while(b){
        int t = b;
        b = a%b;
        a = t;
    }
    return a;
} 
int read()
{
    char ch;
    int ans = 0;
    ch = getchar();
    while(ch>='0'&&ch<='9')
    {
        ans = ans*10 + ch-'0';
        ch = getchar();
    }
    return ans;
}
int main()
{
	int n,m,k;
	n=read(),m=read(),k=read();
	for(int i=0;i<m;i++)
		p[i]=read();
	int ans = 0;
	int z = gcd(k,n);
	for(int i=0;i<m;i++)
	{
		if(!f[p[i]%z])
			ans+=n/z;
		f[p[i]%z] = 1;

	}
	if(ans>n)
		ans = n;
	printf("%d\n",n-ans);
	// if(n%k==0)
	// 	cout<<n-n/k<<endl;
	// else
	// 	cout<<n<<endl;
	return 0;
}
```

---

## 作者：gyh20 (赞：0)

在一个长度为$n$的环上，一次走$k$步能到达的点就是只走一圈每一步走$gcd(k,n)$步所到达的位置。

于是可以得出方法。

令$k$为$gcd(k,n)$。

对于每一个$p[i]$，令$v[p[i]\% k]$为1。

最后检查$1$~$n$的每一个数，如果!$v[i\% k]$则将答案$+1$。

代码如下：

```cpp
#include<cstdio>
using namespace std;
#define re register
const int Mxdt=500;
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read()
{
	int res=0;char ch=gc();
	while(ch<'0'||ch>'9')ch=gc();
	while(ch>='0'&&ch<='9')res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return res;
}
int n,m,a[1000002],p,b,ans;
bool v[1000002];
inline int gcd(re int x,re int y){
	return y?gcd(y,x%y):x;
}
int main(){
	n=read();
	m=read(); 
	p=read();
	p=gcd(p,n);
	for(re int i=1;i<=m;++i)v[read()%p]=1;
	for(re int i=1;i<=n;++i)if(!v[i%p])++ans;
	printf("%d",ans);
}
```


---

## 作者：　　　吾皇 (赞：0)

~~面向数据编程~~

### 分析 

- 当 $k=1$ 时，显然每个格子都能跳到，则输出 $0$。
- 当 $\gcd(k,n)=k$ 时，当兔子跳完全程时后面全都是重复的，所以如果 $i$ 可以跳到，那么 $i+k$ 也可以跳到。反之亦然。因此只要统计 $0$ 到 $k-1$  中有多少格子能跳到，再乘以 $\frac{n}{k}$ 即可。
- 当 $n \le 10^3$，$m \le 10^3$ 时，暴力即可。
- 其他条件下，答案必然为 $0$。

简要证明：

$∵$ $\gcd(k,n) \ne k$

$∴$ 对于 $i$ （$1 \le i \le n$），$i \times k$ 必然是 $0,\cdots,n-1$ 中的一个且不重复。

$∴$ 只要存在兔子必定能跳完。即答案为 $0$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,p[1000001],a,ans,t[1000001];
bool x[1000001];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(k==1) return printf("0"),0;//任务1 当k为1时
	for(int i=1;i<=m;i++) 	scanf("%d",&p[i]);
	if(__gcd(k,n)==k){//任务2 按如上处理
		for(int i=1;i<=m;i++) t[(p[i]%k)]=1;//将所有格子按模k处理为0到k-1的
		for(int i=0;i<k;i++) if(!t[i]) ans++;//如果否，计数器加一
		return printf("%d",ans*(n/k)),0;//由于0到k-1的情况与k到2k-1..nk到(n+1)k-1完全相同，所以只要乘n/k即可
	}
	if(n<=1000&&m<=1000){//任务3 直接暴力
		for(int i=1;i<=m;i++){
			a=p[i],x[a]=true;
			while(1){
				a=(a+k)%n,x[a]=true;//将当前兔子位置标为true
				if(a==p[i]) break;//暴力到回到原点
			}
		}
		for(int i=0;i<n;i++) if(!x[i]) ans++;//判断是否能跳到
		return printf("%d",ans),0;
	}
	printf("0");//其他条件 直接输出
}
```


---

## 作者：Light_Cone (赞：0)

（大概是~~去世的~~NOIP.PJ T1难度


------------


由题意可知，兔子爬过的格子是一个环，**移动方式是（当前位置+k）%n**。

由此可见每一只兔子的移动方式都是同样的，所以**当一只兔子跳到一个曾经跳过的位置，便意味着接下来的位置也都被之前跳跃过了**。
。
所以我们可以~~口胡~~发现，当移动到的位置被经过时，就不需往下进行下去了。

在这里，我们用一个bool数组进行标记是否走过该位置，设定一个总数ans=n,每走过一个没有经过的格子，ans--，最后的结果自然便是不可能走过的格子数。

# Code：
```cpp
#include <cstdio>
int n,m,k,ans;
bool v[1000010];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	ans=n;
	for(int i=1;i<=m;i++)
	{
		int a;
		scanf("%d",&a);
		while(!v[a])
		{
			v[a]=1;
			ans--;
			a=(a+k)%n;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
~~口胡完成！~~

---

## 作者：老咸鱼了 (赞：0)

一道模拟题，注意一下????如果是已经被跳过的地方，那么就可以直接不用再跳，用一个vis数组保存哪些地方是已经被跳过的，最后一个O（n）扫一遍还有哪些点没被跳过。
整体时间复杂度O(n)

注意下数据范围是1e5，数组开大点
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool vis[1555555];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int t;
		scanf("%d",&t);
		while(!vis[t])//把这个兔子能到的所有的点都走一遍，如果被走过就不用走了
		{
			vis[t]=true;
			t=(t+k)%n;
		}
	}
	int ans=0;
	for(int i=0;i<n;i++)
	if(!vis[i])ans++;
	printf("%d",ans);
	return 0;
}
```


---

