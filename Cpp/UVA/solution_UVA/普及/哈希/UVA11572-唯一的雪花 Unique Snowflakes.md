# 唯一的雪花 Unique Snowflakes

## 题目描述

企业家 Emily 有一个很酷的主意：把雪花包起来卖。她发明了一台机器，这台机器可以捕捉飘落的雪花，并把它们一片一片打包进一个包裹里。一旦这个包裹满了，它就会被封上送去发售。

Emily 的公司的口号是“把独特打包起来”，为了实现这一诺言，一个包裹里不能有两片一样的雪花。不幸的是，这并不容易做到，因为实际上通过机器的雪花中有很多是相同的。Emily 想知道这样一个不包含两片一样的雪花的包裹最大能有多大，她可以在任何时候启动机器，但是一旦机器启动了，直到包裹被封上为止，所有通过机器的雪花都必须被打包进这个包裹里，当然，包裹可以在任何时候被封上。

## 样例 #1

### 输入

```
1
5
1
2
3
2
1```

### 输出

```
3```

# 题解

## 作者：逆流之时 (赞：30)

看到这题的题解码风都不怎么好，再交一份。  
没什么好讲的，就是STL的map模板题+滑动窗口，也可以用set。  
```cpp
#include<cstdio>
#include<map>
using namespace std;
map<int,int> snow;
int T,n,ans,last,a;
int main()
{
	for(scanf("%d",&T);T--;printf("%d\n",ans))
	{
		snow.clear();
		scanf("%d",&n);
		last=ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			if(snow[a]>last)last=snow[a];
			printf("%d\n",snow[a]);
			ans=max(ans,i-last);
			snow[a]=i;
		}
	}
	return 0;
}
```


---

## 作者：zhenliu (赞：12)

## 前言
- 这道题跟[逛画展](https://www.luogu.com.cn/problem/P1638)很像，一样可以用双指针来做。不过前者的限制是要求每个种类包含一个，而此题要求不能包含相同种类，所以只用改一下更新答案的条件就好啦。
- 你问双指针是什么？：[尺取法（双指针）洛谷日报](https://www.luogu.com.cn/blog/Nero-Yuzurizaki/chi-qu-fa-xiao-jie)
## 思路
- 设置 $l$,$r$ 两个指针，可以知道，如果答案合法，那么 $r+1-l$ 永远是优于 $r-l$ 的
- 所以，当答案合法时（没有重复的种类），更新答案，并将 $r$ 右移。当答案不合法时，将 $l$ 不断右移，去重，直到答案合法。
## 代码
```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
int n,t,cnt[1000005],a[1000005];
int main(){
	scanf("%d",&t);
	while(t--){
		int l=1,r=1,repeat=0,maxans=-0x3f3f3f3f;//repeat表示有重复的雪花种类个数 
		memset(cnt,0,sizeof(cnt));
		scanf("%d",&n);
		for(RI i=1;i<=n;i++)scanf("%d",&a[i]);
		cnt[a[1]]=1;
		while(l<=r&&r<=n){
		//一点废话：为什么r>n就退出呢？会不会出现r>n了后，l右移还能更新答案的情况呢？
		//因为r>n肯定是前一个合法方案把r++变过来的。相当于l=x，r=n的时候肯定有一个合法解。所以后面l右移了就不会有更大的合法解了 
 			if(repeat==0){//没有重复的雪花，更新答案,并将r往右移找更大的答案 
				maxans=max(maxans,r-l+1);
				r++;
				if(++cnt[a[r]]>1)repeat++;
			}
			else{
				if(--cnt[a[l]]==1)repeat--;//有重复的雪花，将l往右移去重 
				l++;
			}
		}
		printf("%d\n",maxans);
	}
	return 0;
}
```



------------
Thanks for Watching


---

## 作者：Froggy (赞：6)

### 双向队列(deque)实现单调队列

**注:deque是两头都可以插入和删除的队列**

deque里存的是数互不相同的,并且以$a_{i-1}$结尾的最长序列

考虑加入$a_{i}$ :

如果deque里目前没有$a_{i}$,直接加到末尾即可

如果有,一直弹出deque最前面的元素直到deque里没有$a_{i}$,然后加到末尾

可以用map记录deque中的元素

最终的$ans$即为在这个过程中deque的size的最大值

---

代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
#include<map>
using namespace std;
#define N 1111111
inline int read(){//输入很大,尽量用快读
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
deque<int> q;
map<int,int> mp;
int T,n,a[N],ans;
int main(){
	T=read();
	while(T--){
		mp.clear();//多组数据,别忘了清空!
		q.clear();
		ans=0;
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		int now=1;
		for(int i=1;i<=n;i++){
			while(mp[a[i]]){//一直弹出deque最前面的数,直到mp[a[i]]=0
				mp[q.front()]=0;
				q.pop_front();
			}
			q.push_back(a[i]);
			mp[a[i]]=1;
			ans=max(ans,(int)q.size());//记得每次都要取最大值
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

显然,时间复杂度为$O(Tnlogn)$

[*Froggy's blog,呱!*](https://www.luogu.org/blog/1445353309froggy/)

欢迎来踩!



---

## 作者：rainygame (赞：5)

**题解区唯一一个最坏时间复杂度 $\Theta(n)$ 的题解！**

首先，思路当然是双指针。有两个指针 $l,r$，对于每个 $l \in[1,n]$，都枚举 $r$ 所能达到的最远距离。这里当然不是从头开始枚举，而是从上一次 $r$ 开始枚举（因为当 $l$ 增加时，$r$ 一定不减，所以不用从头开始枚举）。$l$ 和 $r$ 都最多只会走 $1$ 次 $[1,n]$，所以时间复杂度为 $\Theta(n)$。

但是如何枚举最远距离呢？我们显然可以做一个标记，如果 $[l,r]$ 之间有 $a_i$，就标记一下 $a_i$。当 $r$ 枚举到被标记的 $a_r$ 的时候，就说明不能再走下去了。

标记题解区要么用 `map`、`set`，要么用哈希，这无疑使得时间复杂度大大增加。这里其实可以直接使用布尔数组标记 ~~（妹说就是无限空间）~~，但是这需要用 $10^9 \div 1024^2 \approx 954$ MB，在部分题目中可能不能通过。

所以在这里推荐一个 STL：`bitset`，它也是一个布尔数组，不过它每一位都只占 $1$ 比特位而不是 $1$ 字节，这使得我们的大小还得除以 $8$，标记数组所占空间瞬间优化到了 $120$ MB 左右。关于 `bitset` 的更多信息，可以看看[ OI-Wiki 的说明](https://oi-wiki.org/lang/csl/bitset/)。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000000

int t, n, l, r, ans;
int a[MAXN];
bitset<1000000001> vis;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> t;
    while (t--){
    	cin >> n;
    	for (int i(0); i<n; ++i) cin >> a[i];
    	
	    l = r = ans = 0;
    	while (l < n){
//    		cout << r << '\n';
    		while (r < n && !vis[a[r]]) vis[a[r++]] = 1;
//			cout << l << ' ' << r << '\n';
    		ans = max(ans, r-l);
    		vis[a[l++]] = 0;
		}
		cout << ans << '\n';
	} 

    return 0;
}
```


---

## 作者：L_Bennett (赞：4)

# 思路：
开一个数组pos,pos[ x ] 表示x出现的位置， 这个数组初始化为-1。

用一个变量start来记录当前枚举序列的起点，初始为0
然后枚举这个序列，依次记录每个数的位置，假设当前枚举到i， 在记录这个位置之前，先检查当前这个数的位置pos[arr[i]]是否大于等于start，如果大于，说明这个数已经在[start, i-1]中已经出现过了，记下这个满足条件的子序列长度。然后枚举下一个子序列： start = pos[i] + 1.  这个算法总复杂度为O(n)
# 上代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long int64;
const int INF = 0x3f3f3f3f;
const int MAXN = 1000010;
int arr[MAXN];
int pos[MAXN];
int main()
{
    //ios::sync_with_stdio(false);
    int nCase, m, n;
    scanf("%d", &nCase);
    while(nCase--)
    {
        scanf("%d", &n);
        int cnt=0;
        for(int i=0; i<n; ++i)
            scanf("%d", &arr[i]);
        memset(pos, -1, sizeof(pos));
        int start = 0;
        int maxx = 0;
        arr[n] = arr[n-1];
        for(int i=0; i<=n; ++i)
        {
            if(pos[arr[i]] >= start)
            {
                int tmp = i - start;
                maxx = max(tmp, maxx);
                start = pos[arr[i]]+1;
                pos[arr[i]] = i;
            }
            else
            {
                pos[arr[i]] = i;
            }
        }
        printf("%d\n", maxx);
    }
    return 0;
}
```

---

## 作者：WaltVBAlston (赞：3)

前言：


这份代码 RE 了 7 次， WA 了两次，在兔神~~和 UVA 评测机~~的不懈努力下调出了 6+ 个 bug ，于 2021 年 7 月 19 日凌晨 1:54 最终 AC 。


总结：srO 兔神nb Orz。


------------


题目翻译：


有 **T** 组测试数据，每组测试数据中有 **N** 个可能重复的数字，求最长连续不重复片段。~~（这个名字是我编的）~~


思路：


本题输入的数字可能很大，无法直接使用数组进行存储。这个时候我们就需要一个叫做 **map** 的东西。关于它的详细用法可以自行 Baidu First Search ，在此就不赘述了。


简单来说，你可以把它当成是一个可以开非常大下标的数组。


存储完数据之后，我们就可以开始跑核心程序了:（我采用的是一边存储一边处理，代码会相对短一些）


**m** 是一个 **map** 变量，判定当前数字是否出现在当前的连续不重复片段中。如果这个数字之前没有出现，我们就把它加到当前的连续不重复片段当中。


如果出现了，我们就要找到上一次出现是什么时候，将其从我们的不重复片段中去除。值得注意的是，因为要求的是 **连续** 不重复片段，所以上一次出现的数字之前的数字也必须全部去除。 **cnt**  实时存储当前连续不重复片段的长度。



```
if(m[a[i]]==0){
	m[a[i]]++;
	cnt++;
}
else{
	while(m[a[i]]!=0){
		m[a[l]]--;
		cnt--;
		l++;
	}
	m[a[i]]++;
	cnt++;
}
```

正因为上一次出现的数字之前的数字也必须全部去除，所以当前状态不一定是最优解，所以我们需要实时判定 **cnt** 的最长长度，用 **ans** 来保存。


```
ans=max(ans,cnt);
```

进行完上述操作之后，我们就可以将最长长度——即 **ans** 输出了！

```
cout<<ans<<endl;//注意需要endl
```



必须说一嘴，各位大佬的讲解也非常清楚，但是码风可能对某些 OIer 不太友好（比如我），~~喜欢这种码风的大佬们且看且珍惜~~。

代码中有注释：

```
#include<map>
#include<iostream>
#include<cstring>
using namespace std;
int t,ans=0,n,a[10000005];
map <int,int> m;//声明map变量 
int l=1;//注意l初始化不为0 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int cnt=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(m[a[i]]==0){//这个数字没有出现在当前的连续不重复片段中 
				m[a[i]]++;
				cnt++;
			}
			else{
				while(m[a[i]]!=0){//这个数字出现在当前的连续不重复片段中 
					m[a[l]]--;
					cnt--;
					l++;
				}
				m[a[i]]++;
				cnt++;//注意，当前数字被加入了，所以要将长度cnt+1 
			}
			ans=max(ans,cnt);
		}
		cout<<ans<<endl;//注意需要endl
		memset(a,0,sizeof(a));
		m.clear();
		ans=0;
		l=1;
      		//一定要记得初始化
	}
	return 0;
} 
```
如果有不懂的或者 hack 代码，欢迎私信或者评论。

（孩子凌晨写的代码，差点猝死 bushi ，求过）

---

## 作者：zhengrunzhe (赞：3)

stl固然nb 但毕竟还是常数大的log

这里提供一个离散化的 虽然也是log但常数比较小

显然$Two-Pointers$(尺取法)

设$f(l,r)$表示[l,r]中数的种数

则有单调性：$f(l,r+1)>=f(l,r)$

那我们就可以大力双指针

右指针往右跳到不重复的最远位置

更新答案

然后左指针往右跳一位

左右指针都只跳了n次

所以查询的复杂度是$O(n)$

然而前面离散化花费了$O(n log n)$

所以总复杂度$O(n log n)$

```cpp
#include<cstdio>
#include<algorithm>
using std::sort;
using std::unique;
using std::lower_bound;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
const int N=1e6+10;
int n,col[N],color[N],cnt[N],ans;
inline const void add(int x){cnt[col[x]]++;}
inline const void del(int x){cnt[col[x]]--;}
int main()
{
	int t;read(t);
	while (t--)
	{
		read(n);
		for (int i=1;i<=n;i++)read(col[i]),color[i]=col[i];
		sort(color+1,color+n+1);int tot=unique(color+1,color+n+1)-color-1;
		for (int i=1;i<=n;i++)col[i]=lower_bound(color+1,color+tot+1,col[i])-color;
		int l=1,r=0;ans=0;
		for (int i=0;i<=tot;i++)cnt[i]=0;
		while (r<=n)
		{
			while (cnt[col[r+1]]<1&&r<=n)add(++r);
			ans=max(ans,r>n?r-l:r-l+1);
			del(l++);
		}
		writeln(ans);
	}
	return 0;
}
```

---

## 作者：_lfxxx_ (赞：3)

### 题意：
找最长的**无重复数**的**子段**。
### 思路：
双指针。

定义两个指针 $l$ 和 $r$。

显然，如果 $[l,r]$ 是合法的，且如果 $a_{r+1}$ 没有出现过， 那么 $[l,r+1]$ 显然要好一些。

所以我们可以从位置 $1$ 开始，看 $a_{r+1}$ 是否在 $[l,r]$ 出现过。出现过就用 $r$ 向外拓展，否则就把 $l$ 指针指向 $a_{r+1}$ 在 $[l,r]$ 中出现的位置加 $1$（因为不能有重，所以要再加 $1$）。

如果暴力查找 $a_{r+1}$ 在 $[l,r]$ 中的位置最坏是 $O(n^2)$ 的，所以需要优化。

这里用 hash 可以做到单次查找 $O(1)$，总复杂度 $O(n)$。
### 代码：
~~有些懒~~代码中用 `unordered_map` 实现 hash。
```cpp
read(T);
while(T--){
	unordered_map<int,int>m;
	read(n);
	ans=0;
	l=1;
	for(int i=1;i<=n;++i){
		read(x);
		if(m[x])
			l=max(l,m[x]+1);
		m[x]=i;
		ans=max(ans,i-l+1);
	}
	write(ans,"\n");
}
return 0;
```


---

## 作者：Rrann (赞：2)

### 前言：

蒟蒻写一篇详细一点的题解。

第一次写题解希望能过。

### 题意：

求给定的整个数列中不包含相同元素的最长区间。

### 分析：

1. 使用双指针（尺取法），$l=1$，$r=0$。

   但为什么两个指针不一样，$r=0$ 的原因是进入 `while` 会加 $1$，表示第一个数，如果一开始  $r=1$，就不正确。 

   $l \le n,r<n$,$r<n$ 原因也和上面大同小异，防止超出。

   这是小细节啦。

2. 还有就是扩大缩小区间的正确性：

   感性理解一下，如果  $[l,r]$ 区间能行，$[l+1,r]$ 也一定能行，因为都是从前面转移过来的啊，前面已经判断过了，这就保证了我们改变 $l$ 指针的正确性。

   改变 $l$ 指针的同时照应了题面，可以在任意时刻启动机器。

更具体的看代码。

### Code：

```c++
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
	while (isdigit(ch)) {x=x*10+ch-48; ch=getchar();}
	return x*f;
}

#define max MAX
inline ll MAX(ll a,ll b){return a>b?a:b;}
#define min MIN
inline ll MIN(ll a,ll b){return a<b?a:b;}

// I want to call it " Ruler_get ". 

const ll nore=1000010;
map < ll , bool > vis;
ll a[nore],n,ans;

int main()
{
	short int T=read();
	while(T--)
	{
		n=read();
		for(register ll i=1;i<=n;i++)
			a[i]=read();
		vis.clear();//多组数据记得清空 
		ll l=1,r=0,ans=-0x3f3f3f3f;
		while(l<=n)
		{
			while(r<n)//这里r是<n 不是<=n  
			{
				r++;
				if(vis[a[r]])
				{
					r--;
					break;
				}
				vis[a[r]]=1;
			}
			ans=max(ans,r-l+1);
			vis[a[l]]=0;
			l++;//可以在任何时候启动机器  
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：1)

## 题意

翻译成人话：求一个序列的最长连续无重复数字的子序列长度。

## 思路

考虑暴力做法，双重循环枚举子序列，光是 $O(N^2)$ 的时间就过不去，所以考虑优化。

考虑使用滑动窗口，紫书上说：

定义 $last_i$ 表示 $a_i$ 上一次出现在哪个位置，如果在之前没有出现，则 $last_i$ 等于 $-1$。

然后求 $last_i$ 的过程可以利用 ```set``` 或者 ```map``` 来辅助完成。当滑动窗口时，判有没有重复的数字就只需要 $O(1)$ 的复杂度了。

然后按照滑动窗口的模板写就可以啦！注意记得 ```set``` 或 ```map``` 要清空。

## 代码

码风丑陋，注意观看：

```cpp
#include<bits/stdc++.h>

using namespace std;

int t, n, a[1000005], last[1000005];

unordered_map<int, int> vis;   //一个好像是利用 hash 表实现的 map，会快一点。

void Solve(){
  cin >> t;
  while(t--){
    cin >> n;
    for(int i = 1; i <= n; i++){
      cin >> a[i];
    }
    for(int i = 1; i <= n; i++){    //求出 last[i]
      if(!vis[a[i]]){    //如果之前没有出现过
        last[i] = -1;
      }
      else{
        last[i] = vis[a[i]];    //vis[a[i]] 表示 a[i] 上一次的位置
      }
      vis[a[i]] = i;    //更新
    }
    int l = 1, r = 1, maxi = -1e9;
    while(r <= n){     //滑动窗口模板
      while(r <= n && l > last[r]){     //利用 last[i] 判断
        r++;
      }
      maxi = max(maxi, r - l);    //维护最长长度
      l++;
    }
    cout << maxi << endl;
    vis.clear();    //清空
  }
}

int main(){
  Solve();
  return 0;
}
```

---

## 作者：冰糖鸽子 (赞：1)

**题意：**

> 求一个序列中最长的没有重复元素的子串的长度

----

首先可以想到枚举区间并验证，但很明显复杂度过高。考虑仅枚举左端点 $l$ ，右端点 $r$ 随着 $l$ 的增加而增加。

简单证一下为什么 $l$ 移动的过程中 $r$ 不会后退（感性理解）：

- 若 $[l,r]$ 内没有重复的元素，则 $[l+1,r]$ 中更不会有重复的元素，因为仅是删去了一个数。

- 为了让长度最长，$r$ 显然不会后退（后退了则一定会回来，还浪费时间）

至于判断是否没有重复元素可以用 STL 中强大的 $\operatorname{map}$ 实现

而这种用两个指针一直右移的算法，就叫做 **尺取法（也叫做双指针法等）**

代码（多测记得清空）：

```cpp

// Problem: UVA11572 唯一的雪花 Unique Snowflakes
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/UVA11572
// Memory Limit: 0 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define M 1000005
int T,n,a[M],ans;
map<int,int>snow;
void done(int m)
{
	snow.clear();
	int l=1,r;
	ans=r=0;
	while(l<=m)
	{
		while(r<m)
		{
			r++;
			if(snow[a[r]])
			{
				r--;
				break;
			}
			snow[a[r]]=1;
		}
		// cout<<l<<' '<<r<<endl;
		snow[a[l]]=0;
		ans=max(ans,r-l+1);
		l++;r=max(r,l-1);
	}
}
int main()
{
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
		}
		done(n);
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：ljw2005 (赞：1)

假设序列元素从0开始编号，所求连续子序列的左端点为L，右端点为R。首先考虑起
点L=0的情况。可以从R=0开始不断增加R，相当于把所求序列的右端点往右延伸。当无法延
伸（即A[R+1]在子序列A[L～R]中出现过）时，只需增大L，并且继续延伸R。既然当前
的A[L～R]是可行解，L增大之后必然还是可行解，所以不必减少R，继续增大即可。
不难发现这个算法是正确的，不过真正有意思的是算法的时间复杂度。暂时先不考
虑“判断是否可以延伸”这个部分，每次要么把R加1，要么把L加1，而L和R最多从0增加到n-
1，所以指针增加的次数是O(n)的。
最后考虑“判断是否可以延伸”这个部分。比较容易想到的方法是用一个STL的set，保
存A[L～R]中元素的集合，当R增大时判断A[R+1]是否在set中出现，而R加1时把A[R+1]插入到
set中，L+1时把A[L]从set中删除。因为set的插入删除和查找都是O(logn)的，所以这个算法的
时间复杂度为O(nlogn)。代码如下：
``` cpp
#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
const int maxn = 1000000 + 5;
int A[maxn];
int main( ) {
	int T, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) 		scanf("%d", &A[i]);
		set<int> s;
		int L = 0, R = 0, ans = 0;
		while(R < n) {
			while(R < n && !s.count(A[R])) 					s.insert(A[R++]);
			ans = max(ans, R - L);
			s.erase(A[L++]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```
另一个方法是用一个map求出last[i]，即下标i的“上一个相同元素的下标”。例如，输入
序列为3 2 4 1 3 2 3，当前区间是[1,3]（即元素2, 4, 1），是否可以延伸呢？下一个数是
A[5]=3，它的“上一个相同位置”是下标0（A[0]=3），不在区间中，因此可以延伸。map的所
有操作都是O(logn)的，但后面所有操作的时间复杂度均为O(1)，总时间复杂度也
是O(nlogn)。代码如下：
``` cpp
#include<cstdio>
#include<map>
using namespace std;
const int maxn = 1000000 + 5;
int A[maxn], last[maxn];
map<int, int> cur;
int main( ) {
	int T, n;
	scanf("%d", &T);
	while(T——) {
		scanf("%d", &n);
		cur.clear( );
		for(int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			if(!cur.count(A[i])) last[i] = -1;
			else last[i] = cur[A[i]];
			cur[A[i]] = i;
		}
		int L = 0, R = 0, ans = 0;
		while(R < n) {
			while(R < n && last[R] < L) R++;
			ans = max(ans, R - L);
			L++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

