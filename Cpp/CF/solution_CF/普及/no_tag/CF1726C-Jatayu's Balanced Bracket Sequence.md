# Jatayu's Balanced Bracket Sequence

## 题目描述

### 题目大意

对于一个长度为 $2n$ 的**合法**的括号串 $s$，按照如下方法构造一张无向图：

- 括号序列的所有位置都是无向图中的一个点。

- 对于该序列的任意位置 $l$，它能向另一个位置 $r$ 连边当且仅当满足子串 $s[l, \; \dots , \; r]$ 也是一个**合法**括号串。

求这张无向图的连通块个数。

## 样例 #1

### 输入

```
4
1
()
3
()(())
3
((()))
4
(())(())```

### 输出

```
1
2
3
3```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

同学暴力做的，也能过。。。

但是这一题是结论题：

`((` 的数量就是答案。

说明一下：

对于一对括号 `(...)` 他的出场方式（左括号左边那个）有两种：

- `)(...)` 左边有个右括号，他也有个匹配的左括号 `(...)(...)`。依次记为 $(i,j),(k,l)$。
	左边那一对有他自己的连通块。而 $(i,l)$ 是合法的括号串，所以 $(i,j)$ 和 $(k,l)$ 就连在一起了，变成一个连通块。
- `((...)` 没人跟他玩，计入答案。

## code

```cpp
#include<stdio.h>
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,ans;
struct __readt__{inline __readt__(){read(t);}}_readt___;
main()
{
	read(n);ans=0;
	for(int i=0,a='(',b;i<n<<1;++i,a=b)
	{
		for(;b=nc(),(b^'(')&&(b^')'););
		if(a=='('&&b=='(')++ans;
	}
	printf("%d\n",ans);
	if(--t)main();
}
```

---

## 作者：Hovery (赞：4)

## Problem

[Jatayu's Balanced Bracket Sequence](https://www.luogu.com.cn/problem/CF1726C)

## Sol

对于这个问题我们考虑两个点什么时候会连边。

```
(((()))),()()(())
```

像上面这种，第一个点和最后一个点都会有连边。

我们不妨把一对括号用区间去描述。

对于 ```(()())``` 这样的括号，把它转化成下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/2krpm7fi.png)

像下面两个线段，其实它们的端点是属于一个连通块里的。

至于为什么，就把这个线段变成其对应的括号序列看一下就知道了。

我们先把这样的线段求出，然后按左端点排个序。

对于一个线段分两种情况。

- $1.$ 前面有一个线段的右端点与它的左端点相邻

  对于这种情况，把当前线段与前面的线段合并，并且这种情况不会产生一个新的连通块。

- $2.$ 前面没有线段的右端点与它的左端点相邻

  对于这种情况，就说明它产生了一个新的连通块。
  
上面的东西可以用堆去维护。

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pb push_back
using namespace std;

void read(int &x)
{
    char ch;
    int w = x = 0;
    ch = getchar();
    for (;!isdigit(ch);ch = getchar())
    w ^= (ch == 45);
    for (;isdigit(ch);ch = getchar())
    x = x * 10 + (ch ^ 48);
    x = w ? -x : x;
}

int n, now, a[200010], cnt;

struct rec{
    int l, r;
}b[200010];

set<int>s;

char st[200010];

void solve()
{
    cin >> n;
    n *= 2;
    now = 0;
    cin >> st + 1;
    cnt = 0;
    for (int i = 1;i <= n;i++)
    {
        if (st[i] == '(')
        {
            a[++now] = i;
        }
        else {
            b[++cnt].l = a[now--];
            b[cnt].r = i;
        }
    }
    s.clear();
    sort(b + 1, b + cnt + 1, [](rec x, rec y)
    {
        return x.l < y.l;
    });
    int sum = 0;
    for (int i = 1;i <= cnt;i++)
    {
        if (s.empty())
        {
            sum++;
            s.insert(b[i].r);
            continue;
        }
        if (*s.lower_bound(b[i].l - 1) == b[i].l - 1)
        {
            s.erase(s.lower_bound(b[i].l - 1));
            s.insert(b[i].r);
        }
        else {
            sum++;
            s.insert(b[i].r);
        }
    }
    cout << sum << endl;
}

signed main()
{
    IOS;
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
```

---

## 作者：xihegudiiakioi (赞：1)

## **解题思路**
这道题其实并没那么难主要的地方在于理解题意~

出现的括号序列有这两种情况：

1. `((()))` 这样子的序列一共有 $3$ 个连通块
2. `()(()())` 这样子的序列有 $3$ 个连通块

我们可以看出，当 `)` 后面有 `(` 时原来的两个连通块就会变成一个，因此我们只需要判断有多少个 `)(` 就行了让累加变量先等于 $n$ ，遇到之后减 $1$ 就行了。

## **AC代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,len,sum;
string s;
int main(){
	cin >> n;
	sum = n;
	for(int i = 1;i <= n;i++){
		cin >> len >> s;
		sum = len;
		len *= 2;
		bool t = true;
		for(int j = 1;j < len;j++){//判断有多少个 ")("
			if(s[j] == '('){
				if(!t){
					sum--;
				}
				t = true;
			}else{
				t = false;
			}
		}
		cout << sum << endl;
	}
	
	return 0;
} 
```

---

## 作者：Shunpower (赞：1)

## 前言
 
 本来是练贪心，然后一发 DP 就过去了，，，
 
 使用“记忆化”搜索实现的 DP。似乎题解里面没有。
 
## 思路
 
 让我们考虑 DP。$dp_{l,r}$ 表示 $[l,r]$ 可以造出来的连通块个数，那么显然 我们应该分类讨论。
 
- $l+1=r$，此时显然答案为 $1$。
- 当 $[l,r]$ 的字符串形如 `(A)`，其中 $A$ 是一个匹配括号串，那么答案为 $dp_{l+1,r-1}+1$，因为最外层的两个括号会单独成为一个连通块。
- 当 $[l,r]$ 的字符串形如 `ABC...Z`，其中 $A,B,C,\cdots ,Z$ 都是匹配括号串，那么答案就为把这些字符串的 $dp$ 值全部加起来，再减去这些字符串的个数，最后加个 $1$。因为原来每个字符串的最外层都会合并在一起，所以才要在减去个数之后加上 $1$。

于是这个题就做完了，使用记忆化搜索实现 DP，因为拓扑序比较麻烦。容易发现不需要记忆化，因为每个匹配括号串只会走一次。甚至连 DP 数组也不需要了，这样就不会爆空间了。

容易发现我们要走的匹配括号串的数量只有长度级别（可能大一点点？），所以可以过。

## 代码

```
//Author:Zealous_YH / Cream_H
//Hai Bian & Xiao Bao
//Hey Left
//Just enjoy the loneliness
//Open a personal party always stay
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define ull unsigned long long
#define bk break
#define ctn continue
#define inf INT_MAX
#define uinf INT_MIN
#define prq priority_queue
#define vr vector
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define efor(i,x) for(int i=head[x];i;i=edge[i].nex)
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define S setiosflags(ios::fixed)<<setprecision(2)
#define pdd pair<ld,ld>
#define pss pair<string,string>
using namespace std;
const int N=2e5+10;
int maxn=uinf,minn=inf;
int tnt,tot;
int T;
int n;
string s;
int p[N];
stack <int> br;
int dfs(int l,int r){
	if(l+1==r){
		return 1;
	}
	if(p[l]==r){
		int ans=dfs(l+1,r-1)+1;
		return ans;
	}
	else{
		int ans=0;
		for(int i=l;i<=r;i=p[i]+1){
			ans+=dfs(i,p[i])-1;
		}
		return ans+1;
	}
}
void solve(){
	cin>>n>>s;
	n<<=1;
	s='@'+s;
	fr1(i,1,n){
		if(s[i]=='('){
			br.push(i);
		}
		else{
			p[br.top()]=i;
			br.pop();
		}
	}
	cout<<dfs(1,n)<<endl;
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//YHX 2004.08.16
//Everything For Ji.
//Everything For Lin.
//Everything For Hao.
//Everything For You.
```

---

## 作者：E1_de5truct0r (赞：1)

提供一种简洁易懂的做法。

容易发现，如果形如 `((()))` 这种形态，每多一层连通块数量就加一。但是有一种特殊情况，即 `()()` 这种，理论上会产生两个连通块但是实际上只有一个。

那么我们不妨考虑在每一个左括号加入的时候，都加上 $1$ 的贡献，而在出现右括号的时候，减去那些多余的贡献。

因此我们只需要维护：

>对于每一个右括号，在直到不合法之前，匹配的左括号数量。即，对于 `()()()()` 的最后一个右括号，应该算出来 $4$。

那么我们每次就把答案减去 这个值减一 即可。

然后考虑怎么维护这个值。显然，我们可以模拟栈的操作，每次进入一个左括号就深度加一，否则深度减一。

容易发现，每次左括号压栈的时候，这一深度的贡献会加一；而每次右括号弹到一个深度的时候，所有大于它的深度的贡献将会归零。

于是直接模拟即可，代码还是非常好写的。

复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>

// 省略巨长的缺省源。

using namespace std;

const int MAXN=200005;

char s[MAXN];
int pre[MAXN],cur[MAXN];

void solve(){
	int n; cin>>n>>(s+1);
	
	for(int i=1;i<=(n<<1);i++) pre[i]=0; // 清空数组
	
	int j=0,ans=0;
	for(int i=1;i<=(n<<1);i++){
		if(s[i]=='(') pre[++j]++,ans++; // 如果是左括号就加贡献
		else ans=ans-pre[j],pre[j]=0; // 否则减贡献
	}
	cout<<ans+1<<endl; // 输出
}

int main(){

	int T; cin>>T;
	while(T--) solve();

	return flush(),0;
}

```

---

## 作者：yegengghost (赞：0)

前排大佬的题解太优秀了。

我考虑了并查集。

还现翻了些与 ```class``` 有关的知识……

既然考虑有几个联通块，我们就要看他们之间的公共祖先是否一样。若一样就将答案减一（因为是两两比较是否在一个连通块上）。


```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=114514;
const int mod=1;
int ksm(int x,int k)
{
	int ans=1,base=x;
	while(k)
	{
		if(k&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod; k>>=1;
	}
	return ans;
}
int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
class node
{
public:
	vector<int>p;//维护一个并查集
	int n;
	node(int _n):n(_n)
	{
		p.resize(n);
		iota(p.begin(),p.end(),0);//批量递增
	}
	inline int get(int x)
	{
		return (x==p[x]?x:(p[x]=get(p[x])));//路径压缩
	}//并查集操作
	inline bool unite(int x,int y)
	{
		x=get(x);
		y=get(y);
		if(x!=y)
		{
			p[x]=y;
			return 1;
		}
		return 0;
	}//找公共祖先以统计联通块
};
signed main()
{
	int t;
	t=read();
	while(t--)
	{
		int n;
		n=read();
		n*=2;
		string s;
		cin>>s;
		vector<vector<int> >a(2*n+5);
		int m=n+1;
		a[m].push_back(0);
		int ans=n;
		node d(n);
		for(int i=0;i<n;i++)
		{
			if(s[i]=='(')
				m++;
			else
				m--;//看括号们是否都有“另一半”
			int l=(!a[m-1].size()?-1:a[m-1].back());
			for(int j=(int)a[m].size()-1;j>=0&&j>=(int)a[m].size()-2;j--)
			{
				if(a[m][j]<l)
					break;
				if(d.unite(a[m][j],i))
					ans--;//发现在一个连通块就把答案减一
			}
			a[m].push_back(i);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Zigh_Wang (赞：0)

推荐[博客](https://blog.csdn.net/YunYuanWang/article/details/126758112?spm=1001.2014.3001.5501)内食用哦

# 题面

> ### 题目大意
> 
> 对于一个长度为 $2n$ 的**合法**的括号串 $s$，按照如下方法构造一张无向图：
> 
> - 括号序列的所有位置都是无向图中的一个点。
> 
> - 对于该序列的任意位置 $l$，它能向另一个位置 $r$ 连边当且仅当满足子串 $s[l, \; \dots , \; r]$ 也是一个**合法**括号串。
> 
> 求这张无向图的连通块个数。
> 
> ### 输入格式
> 
> 第一行包含一个整数 $T \; (1 \leqslant T \leqslant 10^5)$  表示测试样例组数。
> 
> 对于每组测试样例，第一行包含一个整数 $n \; (1 \leqslant n \leqslant 10^5)$ 表示序列长度为 $2n$。
> 
> 接下来的一行包含一个长度为 $2n$ 的合法括号串。
> 
> ### 输出格式
> 
> 对于每组测试样例，包含一个整数表示该串构造的无向图的连通块数。
> 
> $Translated \; by \; Zigh$

# 分析
一看到括号序列，我们第一反应一定是用栈来维护，那么这和这道题有什么关系呢？

首先我们观察下面这个括号串：
![在这里插入图片描述](https://img-blog.csdnimg.cn/db2abac3c75e4ea5ac703298726cfd58.png)
所有的 $top = k$ 的左括号只会向 $top = k - 1$ 的右括号连边，并且他们之间不能存在任何一个 $top < k - 1$ 的右括号，否则他们会被隔断， 如下图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/a0ac4884d079492e96d13db5f83a96c7.png)
上图中的那条蓝色边就不应该存在，因为他们之间有一个 $0$ 阻隔。

也就是说，我们把右括号的 $top$ 单独拎出来看，我们会发现**连续**的一段**相等**的会形成一个连通块 ( 形如 AAAAAA )，或者一段连续相等的中间夹着一些比他大的会形成一个连通块 ( 形如 AAABBBAA 其中 A < B)。通过观察我们可以发现，接下来将会形成一个新的连通块有且仅当 $top_i > top_{i + 1}$。那我们只需要数出这样的对数即可，最后别忘了加上最外面一层的 $1$。

![在这里插入图片描述](https://img-blog.csdnimg.cn/680ed7dc8019466d99505f91062fb56e.png)
# 代码
```cpp
//省略快读和头文件
int T;
int n;
char str[MAXN];
int a[MAXN], cnt = 0;
int tp = 0;
int ans = 0;

int main()
{
	T = inpt();
//	scanf("%d", &T);
	while(T--) {
		ans = 0;
		tp = 0;
		cnt = 0;
		
		n = inpt();
		scanf("%s", str + 1);
		for(int i = 1; i <= 2 * n; i++) {
			if(str[i] == '(') {
				tp++;
			}else {
				tp--;
				a[++cnt] = tp;
			}
		}
		for(int i = 1; i < cnt; i++) {
			if(a[i] > a[i + 1])
				ans++;
		}
		
		printf("%d\n", ans + 1);
	}

 	return 0;
}
```
# 提醒

最后一点提醒，文件名不要直接粘贴题目名字哦，不然调试两行泪哦~

猜猜，那个题面里的 $Zigh$ 是谁呢Qwq

---

