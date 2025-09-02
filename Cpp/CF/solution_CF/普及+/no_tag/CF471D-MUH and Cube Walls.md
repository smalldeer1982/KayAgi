# MUH and Cube Walls

## 题目描述

Polar bears Menshykov and Uslada from the zoo of St. Petersburg and elephant Horace from the zoo of Kiev got hold of lots of wooden cubes somewhere. They started making cube towers by placing the cubes one on top of the other. They defined multiple towers standing in a line as a wall. A wall can consist of towers of different heights.

Horace was the first to finish making his wall. He called his wall an elephant. The wall consists of $ w $ towers. The bears also finished making their wall but they didn't give it a name. Their wall consists of $ n $ towers. Horace looked at the bears' tower and wondered: in how many parts of the wall can he "see an elephant"? He can "see an elephant" on a segment of $ w $ contiguous towers if the heights of the towers on the segment match as a sequence the heights of the towers in Horace's wall. In order to see as many elephants as possible, Horace can raise and lower his wall. He even can lower the wall below the ground level (see the pictures to the samples for clarification).

Your task is to count the number of segments where Horace can "see an elephant".

## 说明/提示

The picture to the left shows Horace's wall from the sample, the picture to the right shows the bears' wall. The segments where Horace can "see an elephant" are in gray.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471D/4bab2ce5008bc40c15cf28d8ffc04197c7f77d57.png)

## 样例 #1

### 输入

```
13 5
2 4 5 5 4 3 2 2 2 3 3 2 1
3 4 4 3 2
```

### 输出

```
2```

# 题解

## 作者：PanH (赞：14)

### 主要算法：差分、kmp
先处理出 $a$ 串和 $b$ 串的差分数组，题目要求的就是差分数组的子串匹配。用kmp解决。

#### 提醒：如果你的方法和我差不多，记得特判一下 $b$ 串长度为1的情况，直接输出  $n$ 即可。

code：
```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,a[N],b[N],c[N<<1],fail[N<<1],ans;
int main()
{
	cin>>n>>m;
	
	//特判
	if(m==1) 
	{
		cout<<n;
		return 0;
	}
	
	//差分 
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<n;i++)	a[i]-=a[i+1];
	for(int i=1;i<=m;i++)	cin>>b[i];
	for(int i=1;i<m;i++)	b[i]-=b[i+1];
	
	//kmp 
	b[m]=-100,n--;
	for(int i=m+1;i<=m+n;i++)	b[i]=a[i-m];
	for(int i=2,j=0;i<=n+m;i++)
	{
		while(j&&b[j+1]!=b[i])	j=fail[j];
		if(b[j+1]==b[i])	j++;
		fail[i]=j;
		if(j==m-1)	ans++;
	}
	
	
	cout<<ans;
	return 0;
}
```


---

## 作者：_Anchor (赞：6)

# 题意

[传送门](https://www.luogu.com.cn/problem/CF471D)

给两堵墙。问a墙中与b墙顶部形状相同的区间有多少个

# 分析

KMP+差分

根据样例解释，我们很容易就能发现：

这里所求的形状，实质上其实就是相邻两个墙的高度的差来确定的

只要差相等，那么形状不就相等了

所以我们考虑将原数组差分，然后这里问的是相等的区间，就是将两个差分数组进行匹配

那么直接KMP，匹配到了多少个答案就是多少，套板子即可

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
const int N=2e5+5,M=1e6+5,MOD=1e9+7;
int n,m,a[N],b[N],kmp[N<<1],ans;
int main(){
    read(n),read(m);
	if(m==1){write(n);return 0;}//注意特判
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<n;i++) a[i]-=a[i+1];
	for(int i=1;i<=m;i++) read(b[i]);
	for(int i=1;i<m;i++) b[i]-=b[i+1];
	b[m]=-100009,n--;//相当于隔离的作用
	for(int i=m+1;i<=m+n;i++) b[i]=a[i-m];//拼接两个字符串
	for(int i=2,j=0;i<=n+m;i++){
		while(j&&b[j+1]!=b[i]) j=kmp[j];
		if(b[j+1]==b[i]) j++;
		kmp[i]=j;
		if(j==m-1) ans++;
	}
	write(ans);
    return 0;
}

```

---

## 作者：wxzzzz (赞：3)

### 思路

前置：[KMP](https://www.cnblogs.com/wangxuzhou-blog/p/character-string.html)（博客阅读）

这题实在是太简单了，就讲讲 KMP 吧。

KMP 是一种字符串单模匹配算法，复杂度 $O(n+k)$ 。

KMP 这个名字的由来：它是三个人：D.E · Knuth 、J.H · Morris 和 V.R · Pratt 同时发现的。

暴力匹配算法在每个字符失配后都回溯到了 $i+1$ 的位置，显然这会浪费很多时间。

KMP 认为，如果在某个起点 $i$ 到 $j$ 这一段匹配过一遍，就不需要再匹配一遍了。
因此，它要在每次失配后知道模式串至少要往前移几位才有可能匹配成功。
显然，移动的位数即是失配点之前模式串的最长相同前后缀的长度。

[图片演示](https://img2023.cnblogs.com/blog/3071615/202307/3071615-20230719222404938-351766415.png)（原创图）

这样，问题就转换成了求模式串的最长相同前后缀。

[动态演示](https://img-blog.csdnimg.cn/20210209085824857.gif)

- 如果用万能头就不能用 $next$ 做数组名。

预处理：维护 $next$ 数组，$next_i$ 表示在模式串 $1$ 到 $i$ 的字符中前后缀相同的最大长度。

预处理的过程就相当于 KMP 自己匹配自己，利用之前求出的部分 $next$ 数组递推。

[动态演示](https://img2023.cnblogs.com/blog/3071615/202307/3071615-20230719223126169-703616441.gif)

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, nxt[1000005];
char p[1000005], s[1000005];
int main() {
    cin >> n, scanf("%s", p + 1);
    cin >> m, scanf("%s", s + 1);

    for (int i = 2, j = 0; i <= n; i++) {
        while (j && p[i] != p[j + 1]) {
            j = nxt[j];
        }
        if (p[i] == p[j + 1]) {
            j++;
        }
        nxt[i] = j;
    }

    for (int i = 1, j = 0; i <= m; i++) {
        while (j && s[i] != p[j + 1]) {
            j = nxt[j];
        }
        if (s[i] == p[j + 1]) {
            j++;
        }
        if (j == n) {
            cout << i - n + 1 << ' ', j = nxt[j];
        }   //模式串在主串中匹配成功的位置
    }

    return 0;
}
```

在本题中，要求的是两段墙墙的顶部相同，换句话说就是两段墙中每相邻两堵墙高度差相等，也就是差分相等，直接在原数组上差分跑 KMP 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, ans, a[200005], b[200005], nxt[200005];
int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= m; i++)
        cin >> b[i];

    for (int i = 1; i < n; i++)
        a[i] = a[i + 1] - a[i];

    for (int i = 1; i < m; i++)
        b[i] = b[i + 1] - b[i];

    for (int i = 2, j = 0; i <= m; i++) {
        while (j && b[i] != b[j + 1])
            j = nxt[j];

        if (b[i] == b[j + 1])
            j++;

        nxt[i] = j;
    }

    for (int i = 1, j = 0; i <= n; i++) {
        while (j && a[i] != b[j + 1])
            j = nxt[j];

        if (a[i] == b[j + 1])
            j++;

        if (j == m - 1)
            ans++, j = nxt[j];
    }

    cout << ans;
    return 0;
}
```

---

## 作者：DennyQi (赞：3)

这是个字符串匹配的问题，然而在这里匹配被定义为`所有字符的差`都相同。

我们来分析一下这样匹配有什么特殊的性质。我们发现，他们两两相邻的差是一样的。于是我们可以预处理出两个串的差分数组，然后直接去匹配差分数组就可以了。用KMP算法$O(n)$完成就可以了。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 200010;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int mul(const int& a, const int& b){ return 1ll*a*b%P; }
inline int add(const int& a, const int& b){ return (a+b>=P)?a+b-P:a+b; }
inline int sub(const int& a, const int& b){ return (a-b<0)?a-b+P:a-b; }
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,m,ans,tmp[N],a[N],b[N],nxt[N];
inline void get_next(){
	for(int i = 2, j; i <= m; ++i){
		j = nxt[i-1];
		while(b[i-1] != b[j] && j) j = nxt[j];
		nxt[i] = j+1;
	}
}
inline void KMP(){
	for(int i = 1, j = 1; i <= n-1;){
		if(a[i] == b[j]){
			++i, ++j;
			if(j >= m){
				++ans;
				j = nxt[j];
			}
		}
		else{
			j = nxt[j];
			if(!j) ++i, ++j;
		}
	}
}
int main(){
	// freopen("file.in","r",stdin);
	n = read(), m = read();
	if(m == 1){
		printf("%d\n",n);
		return 0;
	}
	for(int i = 1; i <= n; ++i) tmp[i] = read();
	for(int i = 1; i < n; ++i) a[i] = tmp[i] - tmp[i+1];
	for(int i = 1; i <= m; ++i) tmp[i] = read();
	for(int i = 1; i < m; ++i) b[i] = tmp[i] - tmp[i+1];
	get_next();
	KMP();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：EDqwq (赞：2)

首先，我们通过读题可以发现，这个墙可以随意伸缩，也就是集体加，集体减。

那么，有什么东西是不变的吗？显然有：差。

只要两两之间的差一样，那么我们就可以通过伸缩去把他匹配上。

所以首先，我们需要两两做差，把总共 $n - 1$ 个差存起来。

然后，我们需要找到一个能算出一个串在另一个串中出现的次数的算法，显然 KMP 满足我们的要求。

最后有一个特判，当 $m = 1$ 时，直接输出 $n$ 即可，否则我们就会拿一个空数组去做 KMP 。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m;
int s1[1000010],s2[1000010];
int nxt[1000010];
int ans;

void getnxt(){
	int p = 0;
	for(int i = 2;i <= m - 1;i ++){
		while(p && s2[i] != s2[p + 1])p = nxt[p];
		if(s2[p + 1] == s2[i])p ++;
		nxt[i] = p;
	}
}

void KMP(){
	int p = 0;
	for(int i = 1;i <= n - 1;i ++){
		while(p && s2[p + 1] != s1[i])p = nxt[p];
		if(s2[p + 1] == s1[i])p ++;
		if(p == m - 1){
			ans ++;
			p = nxt[p];
		}
	}
}

signed main(){
	cin>>n>>m;
	if(m == 1){
		cout<<n;
		return 0;
	}
	for(int i = 1;i <= n;i ++)s1[i] = read();
	for(int i = 1;i <= m;i ++)s2[i] = read();
	for(int i = 1;i <= n;i ++)s1[i] -= s1[i + 1];
	for(int i = 1;i <= m;i ++)s2[i] -= s2[i + 1];
	getnxt();
	KMP();
	cout<<ans;
	return 0;
}
```

---

## 作者：Nephren_Sakura (赞：1)

题目传送门：[link](https://www.luogu.com.cn/problem/CF471D)。

首先我们要读懂题。

这边给出一个简要题意：

给定两个序列 $a,b$，其中 $|a| < |b|$，求 $a$ 中有多少个长度与 $b$ 相同的子段 $a_i \dots a_{i+|b|-1}$ 满足 $a_i-b_1 = a_{i+1}-b_2 = \dots = a_{i+|b|-1}-b_{|b|}$。

首先，我们对于相邻两项移项，就变成了：

$a_{i+1}-a_i=b_2-b_1,a_{i+2}-a_{i+1}=b_3-b_2,\dots,a_{i+|b|-1}-a_{i+|b|-2}=b_{|b|}-b_{|b|-1}$。

那么我们可以对于两个序列求出差分数组 $diff$ 和 $DIFF$。

那么原题意转化为：

对于序列 $diff$，序列 $DIFF$ 在其中出现了多少次。

这种题目一般有两个想法，哈希和 KMP。

但是这题卡哈希，所以我用了 KMP。

如果 KMP 不熟悉可以去看 P3375。

那么这题就做完了。

最后注意一个特判，当 $m=1$ 时直接输出 $n$，不然你会拿一个空数组做 KMP 导致 WA。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1000005],diff[1000005],A[1000005],DIFF[1000005],nxt[1000005],ans=0;
void getnext(int s[]){
	int i=0,j=-1;
	nxt[0]=-1;
	while(i<m){
		if(j==-1||s[i]==s[j])
			i++,j++,nxt[i]=j;
		else
			j=nxt[j];
	}
	return;
}
void kmp(int s1[],int s2[]){
	getnext(s2);
	int i,j;
	i=j=0;
	while(i<n){
		if(j==m-1&&s1[i]==s2[j])
			ans++,j=nxt[j];
		else if(j==-1||s1[i]==s2[j])
			i++,j++;
		else
			j=nxt[j];
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	if(m==1){
		cout<<n;
		return 0;
	}
	for(int i=1; i<=n; i++)
		cin>>a[i];
	for(int i=0; i<n-1; i++)
		diff[i]=a[i+2]-a[i+1];
	for(int i=1; i<=m; i++)
		cin>>A[i];
	for(int i=0; i<m-1; i++)
		DIFF[i]=A[i+2]-A[i+1];
	n--;
	m--;
	kmp(diff,DIFF);
	cout<<ans;
	return 0;
}
```

[CF AC 记录](https://codeforces.com/contest/471/submission/212938586)。

---

## 作者：FanYongchen (赞：1)

题目中要求 $a$ 墙中与 $b$ 墙顶部形状相同的区间。

形状相同，就是高低起伏相同，自然就能想到差分了。

所以求出 $a$ 与 $b$ 的差分数组，然后直接跑 KMP 就行了。

当然差分数组的第一位是不用比较的，因为只要形状相同就行了。

但是这道题中不能直接用字符串去存每个数的值，因为数值可能会超过 $9$，那我们直接用数组保存就行了。

这里匹配的思路源自 [OI wiki](https://oi-wiki.org/string/kmp/#knuth-morris-pratt)。

代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;
#define ms(x,y) memset(x,y,sizeof(x))
#define mc(x,y) memcpy(x,y,sizeof(x))
#define ll long long
const int M=500005;
int n,m;
int a[M],b[M];
int c1[M],c2[M];//c1为a的差分数组，c2为b的差分数组
int Next[M];
int s[M],l=0;//用数组保存
int main()
{
    clock_t t1=clock();
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//==================================
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],c1[i]=a[i]-a[i-1];
    for(int i=1;i<=m;i++) cin>>b[i],c2[i]=b[i]-b[i-1];
    for(int i=2;i<=m;i++) s[l++]=(c2[i]+'0');//第一位不用比较，所以i初始值为2
    s[l++]=-1;//-1为分隔符
    for(int i=2;i<=n;i++) s[l++]=(c1[i]+'0');//同上
    int i=0,j=-1;
    Next[0]=-1;
    while(i<l)//裸的KMP
    {
        if(j==-1||s[i]==s[j]) i++,j++,Next[i]=j;
        else j=Next[j];
    }
    int ans=0;
    for(int i=1;i<=l;i++) ans+=(Next[i]==m-1);
    //注意这里要m-1，因为差分数组的第一位不用匹配
    //然后因为有一个分隔符-1，所以i直接从1开始也是没关系的
    cout<<ans;
//==================================

    cerr<<"Time used:"<<clock()-t1<<"ms"<<"\n";
    return 0;
} 
```

---

## 作者：ethan0328 (赞：1)

## 思路

显然，当 $b$ 数组整体加或减一个数后等于 $a$ 数组的一部分是满足形状相同。

所以我们把 $a$ 和 $b$ 两个数组差分，并从第二位开始 kmp。

要注意，特判 $b$ 的长度为 $1$ 时，直接输出 $n$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,ans,s1[N],s2[N],p[N];
void pre()
{
	p[2]=1;
	int j=1;
	for(int i=3;i<=m;i++)
	{
		while(j>1&&s2[j+1]!=s2[i])
		{
			j=p[j];
		}
		if(s2[j+1]==s2[i])
		{
			j++;
		}
		p[i]=j;
	}
}
void kmp()
{
	int j=1;
	for(int i=2;i<=n;i++)
	{
		while(j>1&&s2[j+1]!=s1[i])
		{
			j=p[j];
		}
		if(s2[j+1]==s1[i])
		{
			j++;
		}
		if(j==m)
		{
			ans++;
			j=p[j];
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s1[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>s2[i]; 
	}
	if(m==1)
	{
		cout<<n;
		return 0;
	}
	for(int i=n;i>1;i--)
	{
		s1[i]-=s1[i-1];
	}
	for(int i=m;i>1;i--)
	{
		s2[i]-=s2[i-1];
	}
	pre();
	kmp();
	cout<<ans;
}
```


---

## 作者：xiezheyuan (赞：0)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/cf417d.html)

## 简要题意

[题目传送门](https://codeforces.com/problemset/problem/471/D)

平面上有两堵墙 $a,b$。长度分别为 $n,w$。求 $a$ 墙顶端有多少个区间与 $b$ 墙顶端一样。

$1\le n,w \le 2 \times 10^5,1 \leq a_i,b_i \leq 10^9$

## 代码

先用一下样例的图进行分析：

![image](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471D/4bab2ce5008bc40c15cf28d8ffc04197c7f77d57.png)

可以发现，顶端的形状取决于从 $i$ 到 $i+1$ 上升或下降了多少格，而不取决于每一个地方的具体高度。自然想到差分数组。

我们求出 $a,b$ 两堵墙的差分数组后，就可以 $b$ 为模式串在 $a$ 上跑 KMP 了。

注意这个做法有一个缺陷，就是在 $w=1$ 的时候答案是 $n$，我们会输出 $n-1$。这是因为差分数组比原数组少一个元素导致的。我们特判一下即可。

时间复杂度 $O(n+w)$。

## 代码

这里给出的是传统实现，看不懂题解的拼接两个数组的写法。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,m;
int A[1000005],B[1000005];
int fail[1000005];

signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>A[i];
    for(int i=1;i<=m;i++) cin>>B[i];
    for(int i=1;i<n;i++) A[i]-=A[i+1];
    for(int i=1;i<m;i++) B[i]-=B[i+1];
    n--;m--;
    for(int i=2,j=0;i<=m;i++){
        while(j&&B[i]!=B[j+1]) j=fail[j];
        if(B[j+1]==B[i]) j++;
        fail[i]=j;
    }
    int ans=0;
    for(int i=1,j=0;i<=n;i++){
        while(j&&B[j+1]!=A[i]) j=fail[j];
        if(A[i]==B[j+1]) j++;
        if(j==m){ans++;j=fail[j];}
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Kreedy_Ke (赞：0)

## [题目翻译](https://www.luogu.com.cn/paste/zr8cicqu)

注意题目中的一段话：

>为了尽可能多地看到大象，Horace 可以升高和降低他的墙。他甚至可以把墙降到地面以下。

这就已经在暗示这题的标准做法了。因为可以对一段区间进行整体加减操作就意味着每一个“塔”的高度不再重要了，重要的是相邻“塔”之间的相对高度。所以这个题目就从匹配形状转换到了匹配相对高度。相对高度怎么记录？用差分数组。怎么匹配子串？用 KMP。

不过还有一点需要注意，记录 $b$ 墙相对高度的差分数组在匹配时，第一位是不用匹配的，因为高度可以随意变换。所以，当 $b$ 墙长度为 1 时，就已经不需要匹配了，直接输出 $a$ 墙长度就行。

剩下的就是 KMP 和差分的板子了，这题可以作为 KMP 的入门题。

代码如下：

```
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define LL long long
using namespace std;
const int N=2e5+9;
int n,m;
LL a[N],b[N],c[N],d[N],nxt[N];
void get_next() //把求 next 数组的过程改成整型数组就行了
{
    for ( int i=2,j=0 ; i<=m ; nxt[i++]=j )
	{
        while ( j && d[i]!=d[j+1] ) j=nxt[j];
		if ( d[i]==d[j+1] ) j++;
	}
}
LL Find() //KMP 模板
{
    LL cnt=0;
    for ( int i=0,j=1 ; j<=n ; j++ )
    {
        while ( i && c[j]!=d[i+1] ) i=nxt[i];
		if ( c[j]==d[i+1] ) i++;
        if ( i==m ) cnt++;
    }
    return cnt;
}
int main()
{
	scanf("%d %d",&n,&m);
	for ( int i=1 ; i<=n ; i++ ) scanf("%lld",&a[i]);
	for ( int i=1 ; i<=m ; i++ ) scanf("%lld",&b[i]);
	if ( m==1 ) { printf("%d\n",n); return 0; } //特判 m 为 1 时的情况
	for ( int i=2 ; i<=n ; i++ ) c[i-1]=a[i]-a[i-1]; //建立差分数组
	for ( int i=2 ; i<=m ; i++ ) d[i-1]=b[i]-b[i-1]; //顺便除去 b 的第一位
	c[n--]=-1e16; d[m--]=-1e15; //别忘了结尾
	get_next();
	printf("%lld\n",Find());
	return 0;
}
```

---

## 作者：Steven__Chen (赞：0)

对于一个字符串S，我们定义“匹配”为两个字符串的每个字符都相等

类似的，对于一个抽象的序列，我们定义“匹配”为两个序列满足一些性质，记为 $S(s_1, s_2) = 1$，另外定义一个四元函数 $P$

若要使用KMP算法，$S$ 函数需要满足一些性质，如下：

性质一（传递性）：

若 $S(s_1,s_2) =1$ 且 $S(s_2, s_3) = 1$，则有 $S(s_1, s_3) = 1$

性质二：

若 $S(s_1,s_2) =1$ 且 $S(s_3, s_4) = 1$ 且 $P(s_1,s_2,s_3,s_4) = 1$ ，则有 $S(s1+s3, s2+s4) = 1$

例题：[CF471D](https://www.luogu.com.cn/problem/CF471D)

这道题有差分做法，但博主太蒻没有想到。

在这题里，对于两个长度为 $n$ 的序列 $a$ 和 $b$，当存在一个常数 $k$，对于任意一个 $i(1\le i\le n)$ ，都满足 $b_i - a_i = k$ 时，
$S(a, b) = 1$

对于满足 $S(a, b) = 1$ 且 $S(c, d) = 1$ 的四个序列 $a, b, c, d$，
当存在一个常数 $k$，满足 $a$ 和 $b$，$c$ 和 $d$ 中元素值的差都为 $k$ 时，$P(a,b,c,d)=1$，所以也有 $S(a+c, b+d)=1$ 。

贴上代码：

```cpp
#include <cstdio>
using namespace std;
int n, w, a[300000], b[300000], f[300000], minus, ans;
int main()
{
       scanf("%d%d", &n, &w);
       for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
       for (int i = 1; i <= w; i++) scanf("%d", &b[i]);
       f[0] = 0;
       for (int i = 0; i < w; i++)
       {
            int j = f[i];
            while (j && b[i + 1] - b[j + 1] != b[i] - b[j]) j = f[j];
            if (b[i + 1] - b[j + 1] == b[i] - b[j]) f[i + 1] = j + 1;
            else f[i + 1] = 1;
            f[1] = 0;
       }
       int j = 0;
       for (int i = 1; i <= n; i++)
       {
            while (j && a[i] - b[j + 1] != a[i - 1] - b[j]) j = f[j];
            if (a[i] - b[j + 1] == a[i - 1] - b[j]) j++;
            else j = 1;
            if (j == w) ans++, j = f[j];
       }
       printf("%d", ans);
       return 0;
}
```



---

## 作者：daiarineko (赞：0)

# 题解 - CF471D MUH and Cube Walls

## Link - 链接

[Luogu RMJ CF471D](https://www.luogu.com.cn/problem/CF471D)  
[CF 471D](http://codeforces.com/problemset/problem/471/D)

## Description - 题目简述

给定两堵墙（具体见图），问 $a$ 墙中与 $b$ 墙顶部**形状**相同的区间有多少个；两个区间可以重叠。

```plain
抽象图：
        Wall a        Wall b
    2455432223321     34432
  5   XX
  4  XXXX              XX
  3  XXXXX   XX       XXXX
  2 XXXXXXXXXXXX      XXXXX
  1 XXXXXXXXXXXXX     XXXXX

        Match
    -45543-------
    --------23321
  5   XX
  4  XXXX
  3  XXXXX   XX
  2 -XXXXX--XXXX
  1 --------XXXXX
(-1)        XXXXX
```

## Solution - 题解

注意到，题面中说的是形状相同，这意味着匹配时重要的是相对高度。

那么什么能用来刻画相对高度呢？差分！

因此，我们转而观察差分数组。

```plain
 A   2  4  5  5  4  3  2  2  2  3  3  2  1
 B      3  4  4  3  2        3  4  4  3  2
 A' +2 +2 +1 +0 -1 -1 -1 +0 +0 +1 +0 -1 -1
 B'1   +3 +1 +0 -1 -1
 B'2                        +3 +1 +0 -1 -1
```

诶，发生了一个奇怪的事情：第一列匹配不上！

这其实是正常的。毕竟这相当于什么呢，这相当于我们钦定第零列高度为 $0$ 了。

想要避免这个问题，也很简单，只要把第一列去掉，就可以啦！这相当于第零列的高度被我们忽略掉了，自然不影响答案。

当然，去掉第一列的时候，$a,b$ 数组都要去掉。（否则 CF 上会被 Hack）

```plain
 A   2  4  5  5  4  3  2  2  2  3  3  2  1
 B      3  4  4  3  2        3  4  4  3  2
 A' -- +2 +1 +0 -1 -1 -1 +0 +0 +1 +0 -1 -1
 B'1   -- +1 +0 -1 -1
 B'2                        -- +1 +0 -1 -1
```

接下来就是匹配啦！有了以上的铺垫，匹配就变成了单模式串单母串匹配模板。于是 KMP 可过。

KMP 部分建议参考 KMP 模板题题解。

本题主要考验的是能够想到差分这个 Trick 的思维能力。

### 示例代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 204800;
inline namespace kmp
{
    int tl, t[maxn];
    int fail[maxn];
    void construct()
    {
        int i = 0, j = -1;
        fail[0] = -1;
        for (; i < tl;)
        {
            if (j == -1 || t[i] == t[j])
                fail[++i] = ++j;
            else
                j = fail[j];
        }
    }
    int query(int sl, int s[])
    {
        int ans = 0, i = -1, j = -1;
        for (; i < sl && j < tl;)
        {
            if (j == -1 || s[i] == t[j])
                ++i, ++j;
            else
                j = fail[j];
            if (j == tl)
                j = fail[j], ++ans;
        }
        return ans;
    }
}
int s[maxn], sl;
int main()
{
    scanf("%d%d", &sl, &tl);
    for (int i = 0; i < sl; ++i)
    {
        scanf("%d", &s[i]);
        if (i)
            s[i - 1] = s[i] - s[i - 1];
    }
    --sl;
    for (int i = 0; i < tl; ++i)
    {
        scanf("%d", &t[i]);
        if (i)
            t[i - 1] = t[i] - t[i - 1];
    }
    --tl;
    if (!tl)
    {
        printf("%d\n", sl + 1); // 见下
        return 0;
    }
    construct();
    printf("%d\n", query(sl, s));
    return 0;
}
```

## Hack - 坑点

1. 由于删去了一项，当 $w=1$ 时，显然会锅掉。这时候需要特判；经过简单的画图就能判断此时答案 $=n$。
2. 区间可重叠，因此匹配成功后 `j` 跳 `fail` 而不是从头开始。


---

## 作者：SunsetSamsara (赞：0)

## 前置知识
差分与 KMP 算法
## 分析
其实所谓的“形状相同”就相当于**相对位置相同**，而相对位置相同又可以转换成**差分数组相同**

所以这题直接在两个差分数组合并起来的数组上运行 KMP 获取 next 数组时判断一下当前是否已经匹配完 $b$ 墙，如果匹配完则加上一。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[200001],b[200001];
int nxt[400001];
int ans;
int main(){
	scanf("%d%d",&n,&m);
	if(m==1){
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1;i<=n;++i)a[i-1]-=a[i];//差分 
	for(int i=1;i<=m;++i)scanf("%d",b+i);
	for(int i=1;i<=m;++i)b[i-1]-=b[i];//差分 
	b[m]=-0x7f7f7f7f;//注意，这里为了不能被匹配到所以得设置一个边界值 
	for(int i=m+1;i<m+n;++i)b[i]=a[i-m];
	for(int i=2,j=0;i<m+n;++i){
		while(j&&b[j+1]!=b[i])j=nxt[j];
		if(b[j+1]==b[i])++j;
		nxt[i]=j;
		if(j==m-1)++ans;//匹配完成b串后答案加1 
	}
	printf("%d\n",ans);
}
```

---

## 作者：Cylete (赞：0)

差分转化一下其实就是[P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)

注意特判$m == 0$，此时答案为$n$

```cpp
int T, n, m, k, ans;

int a[N], b[N], fail[N];

inline void solve() {
//	into();
	read(n); read(m);
	if(m == 1) {
		writeln(n);
		return;
	}
	for(R int i = 1; i <= n; i++) read(a[i]);
	for(R int i = 1; i < n; i++) a[i] -= a[i + 1];
	for(R int i = 1; i <= m; i++) read(b[i]);
	for(R int i = 1; i < m; i++) b[i] -= b[i + 1];
    //差分
	for(R int i = 2, j = 0; i < m; i++) {
		while(j && b[j + 1] != b[i]) j = fail[j];
		if(b[j + 1] == b[i]) j++;
		fail[i] = j;
	}
	for(R int i = 1, j = 0; i < n; i++) {
		while(j && b[j + 1] != a[i]) j = fail[j];
		if(b[j + 1] == a[i]) j++;
		if(j == m - 1) ans++, j = fail[j];
	}
	writeln(ans);
}
```

---

## 作者：AKPC (赞：0)

### 思路
题目要我们求出 $a$ 中与 $b$ 高低起伏相同的区间，可以将相邻两位相减成为一个差分数组，然后用这个差分数组跑 KMP 搜索符合条件的区间即可。

当然注意特判，如果 $w=1$ 的话显然有 $n$ 个区间形状相同。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,tip,ans,a[1000005],b[1000005],nxt[1000005];
signed main(){
    cin>>n>>m;
    if (m==1) {cout<<n;return 0;}
    for (int i=1;i<=n;i++) cin>>a[i];n--;
    for (int i=1;i<=n;i++) a[i]-=a[i+1];
    for (int i=1;i<=m;i++) cin>>b[i];m--;
    for (int i=1;i<=m;i++) b[i]-=b[i+1];
    for (int i=2;i<=m;i++){
        while (tip&&b[i]!=b[tip+1]) tip=nxt[tip];
        if (b[i]==b[tip+1]) tip++;
        nxt[i]=tip;
    }
    tip=0;
    for (int i=1;i<=n;i++){
        while (tip&&a[i]!=b[tip+1]) tip=nxt[tip];
        if (a[i]==b[tip+1]) tip++;
        if (tip==m) ans++,tip=nxt[tip];
    }
    cout<<ans;
    return 0;
}
```


---

