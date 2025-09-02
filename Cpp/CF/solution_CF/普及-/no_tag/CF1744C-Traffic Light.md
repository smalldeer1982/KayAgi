# Traffic Light

## 题目描述

You find yourself on an unusual crossroad with a weird traffic light. That traffic light has three possible colors: red (r), yellow (y), green (g). It is known that the traffic light repeats its colors every $ n $ seconds and at the $ i $ -th second the color $ s_i $ is on.

That way, the order of the colors is described by a string. For example, if $ s= $ "rggry", then the traffic light works as the following: red-green-green-red-yellow-red-green-green-red-yellow- ... and so on.

More formally, you are given a string $ s_1, s_2, \ldots, s_n $ of length $ n $ . At the first second the color $ s_1 $ is on, at the second — $ s_2 $ , ..., at the $ n $ -th second the color $ s_n $ is on, at the $ n + 1 $ -st second the color $ s_1 $ is on and so on.

You need to cross the road and that can only be done when the green color is on.

You know which color is on the traffic light at the moment, but you don't know the current moment of time. You need to find the minimum amount of time in which you are guaranteed to cross the road.

You can assume that you cross the road immediately.

For example, with $ s= $ "rggry" and the current color r there are two options: either the green color will be on after $ 1 $ second, or after $ 3 $ . That way, the answer is equal to $ 3 $ — that is the number of seconds that we are guaranteed to cross the road, if the current color is r.

## 说明/提示

The first test case is explained in the statement.

In the second test case the green color is on so you can cross the road immediately.

In the third test case, if the red color was on at the second second, then we would wait for the green color for one second, and if the red light was on at the first second, then we would wait for the green light for two seconds.

In the fourth test case the longest we would wait for the green color is if we wait for it starting from the fifth second.

## 样例 #1

### 输入

```
6
5 r
rggry
1 g
g
3 r
rrg
5 y
yrrgy
7 r
rgrgyrg
9 y
rrrgyyygy```

### 输出

```
3
0
2
4
1
4```

# 题解

## 作者：沉石鱼惊旋 (赞：3)

### 题目翻译

问当前字符后的第一个 $\tt{g}$ 与它的距离最大是多少。

当前字符可能有很多个。

### 题目思路

我们把目前找到的当前字符的位置记录下来，找到最早的，记录一下时间差，取个最大。

但显然我们不能对每一个去找，必须几个打包一找。

我用 `queue` 模拟题意，详情见代码。

由于当前的可能要到下一个循环才能看见 $\tt{g}$，所以要循环两次。

时间复杂度 $\mathcal O(n)$。

### 题目代码

```
#include<bits/stdc++.h>
using namespace std;
int t,n,z;
char c[200020];
char tmp;
queue<int>q;
int ans=INT_MIN;
void solve()
{
	ans=INT_MIN;
	while(!q.empty())
	{
		q.pop();
	}
	scanf("%d %c%s",&n,&tmp,c+1);
	for(int i=1;i<=n+n;i++)
	{
		z=i;
		if(z>n)
		{
			z-=n;
		}
		if(i<=n&&c[z]==tmp)
		{
			q.push(z);
		}
		if(c[z]=='g'&&!q.empty())//找到g并且有当前字符
		{
			ans=max(ans,i-q.front());//取一个最大的时间差
			while(!q.empty())
			{
				q.pop();
			}
		}
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		solve();
	}
	return 0;
}
/*
6
5 r
rggry
1 g
g
3 r
rrg
5 y
yrrgy
7 r
rgrgyrg
9 y
rrrgyyygy
*/
```

---

## 作者：Allanljx (赞：2)

## 思路
首先要破环为列。然后从后往前循环下标 $i$，用 $a$ 数组记录从 $i$ 往后（包括 $i$）的第一个 `g` 出现的位置，然后取 $\max\limits_{i=1\sim n} a_i-i$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q;
char ch;
char a[400005];
int qz[400005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>ch;
		cin>>(a+1);
		int l=strlen(a+1);
		for(int i=1;i<=l;i++) a[i+l]=a[i];
		for(int i=2*l;i>=1;i--)
		{
			if(a[i]=='g') qz[i]=i;
			else qz[i]=qz[i+1];
		}
		int maxn=0;
		for(int i=1;i<=l;i++)
		{
			if(a[i]!=ch) continue;
			maxn=max(maxn,qz[i]-i);
		}
		cout<<maxn<<endl;
	}
}
```

---

## 作者：haokee (赞：1)

## 题目大意

给定一个循环节 $s$，求给定的字符距离它右边最近的 $\texttt{g}$ 的距离，求最大值。

## 思路

贪心，我们可以先思考没有循环。我们首先从前往后慢慢扫描，如果字符符合要求，我们就记录下这个字符的位置。这里我们只用记录**最小值**。

如果我们遇到了字符 $\texttt{g}$，那么直接记录答案，并且分节，因为这里是求最近的字符 $\texttt{g}$。

现在考虑循环。我们知道，相同的循环节如果我们直接记录，那么可能会存在跨过循环节的现象。但是我们知道，如果一个循环节里面有 $\texttt{g}$，那么不会存在两个循环节都找不到答案的情况；如果没有 $\texttt{g}$，则无解。我们只需将字符串拷贝一遍即可。

## 判断贪心正确性

对于每一个给定的字符，它的右边只有一个答案。而如果没有分节，最小值肯定是最优的，没有必要把所有给定字符的位置全部记录下来，因为它距离右边的第一个 $\texttt{g}$ 肯定是最远的，因此这个贪心算法是完全正确的。

## 代码

```cpp
#include <iostream>
#include <cstring>  // 使用string类进行操纵，可以更好地连接字符串
using namespace std;

int t, n, ind = 1e9, ans = -1;
// 细节*1：ind需要记录最小值，ans可能存在0的情况，保险
char c;
string s;

int main() {
    for (cin >> t; t; --t) {
        cin >> n >> c >> s;
        s += s  /*调用string重载运算符拷贝字符串*/ , 
        ans = -1, ind = 1e9;  // 细节*2：多组数据记得清空！
        for (int i = 0; i < s.size(); ++i) {  //遍历每个字符
            if (s[i] == c) {  // 如果是开头
                ind = min(ind, i);  // 记录最优值
            } 
            if (s[i] == 'g') {  // 细节*3：有可能给定字符就是g，不可写成else if
                ans = max(ans, i - ind);  // 记录答案
                ind = 1e9;  // 细节*4：此时已经分节了，ind需要重新计算
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：litachloveyou (赞：1)

题目要求给定的字符 $c$ 到字符 $g$  的最远距离，并且字符串是有周期的。

那么，我们可以把这个字符串复制一段，将它的长度变为 $2\times n$，将每一个字符 $g$ 的位置都存进一个数组中。

这时，我们再重新遍历原来的 $n$ 长度，当碰到要求的字符 $c$ 时，使用二分查找，快速查找离他最近的 $g$，再更新一下最大值的答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
	int n;
	char q;
	cin >> n >> q;
	string s;
	cin >> s;
	s = " " + s + s;
	vector<int>pos;
	for (int i = 1; i <= n * 2; i++)
	{
		if (s[i] == 'g')pos.push_back(i);
	}
	int ans = -1;
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == q)
		{
			int k = lower_bound(pos.begin(), pos.end(), i) - pos.begin();
			ans = max(ans, pos[k] - i);
		}
	}
	printf("%d\n", ans);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：guanyf (赞：0)

### 题意
- 给定长度为 $N$ 的循环字符串 $s$，求每个字符 $c$ 的后面最近的 `g` 的距离的最大值。

- $1 \le N \le 2 \times 10^5$

### 分析、思路
遇到这类环相关的问题，我们可以**破环为链**，具体方式是在 $s$ 后再接一个 $s$。这样就可以把原先字符前的字符移到字符后去处理了。

对于每个 `g`，我们可以把它的位置记录在队列中，对于每个字符 $c$ 来说，最近的 `g` 就是队列的首元素。如果当前字符就是 `g`，则弹出首元素。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, n, ans, cnt;
vector<int> v;  // vector 模拟queue
char c;
string s;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    cin >> n >> c >> s, s = ' ' + s + s, ans = 0, cnt = 0;
    v.clear();
    for (int i = 1; i < s.size(); i++) {
      if (s[i] == 'g') {
        v.push_back(i);
      }
    }
    for (int i = 1; i <= n; i++) {
      if (s[i] == c) {
        ans = max(ans, v[cnt] - i);
      }
      cnt += (s[i] == 'g');
    }
    cout << ans << '\n';
  }

  return 0;
}
```


---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/CF1744C)

## Solution
字符串模拟题。

首先，这个“循环节”很难处理，不妨复制字符串 $s$ 到原来的 $s$ 之后，达到循环的效果。

令 $p$ 为 $c$ 在 $s$ 中的第 $i$ 个字符位置，随后 $O(n)$ 遍历找到最近的 $\texttt{g}$，对于每个 $i - p$ 取最大值即可。

## Code

```cpp
// 2023/5/26 Accept__

#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 7;

long long t, n, ans, p = -1;
char c;
string s;

inline long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        cin >> n >> c >> s, s += s, s = " " + s, n *= 2;
        for (int i = 1, j; i <= n; i++) {
            if (c == 'g') {
                break;
            }
            j = i, (s[j] == c && p == -1) && (p = j);
            if (s[j] == 'g' && p != -1) {
                ans = max(ans, j - p), p = -1;
                if (i > n) {
                    break;
                }
            }
        }
        cout << ans << '\n', ans = 0, p = -1;
    }
    
    return 0;
}
```


---

## 作者：loser_seele (赞：0)

VP 的时候想到的一个又臭又长的暴力做法。

首先对于每个给定字符，不难发现答案只会有两种情况：一种是存在某个绿灯在它后面，那么从这个字符直接到绿灯显然是最优。第二种情况是后面没有绿灯，那么由于周期所以从头开始找，那么开头第一个绿灯与其的距离即为答案。

发现将所有绿灯的下标丢入一个数组里之后，对于每个给定字符实际上只需要求下标的后继，如果后继不存在则选取从头部开始的第一个后继即可。

后继可以用平衡树维护查询，所以得到了一个 $ \mathcal{O}(n\log{n}) $ 的解法，可以通过。注意清空不能直接 memset，否则会超时。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node 
{
	int lc,rc,key,pri,cnt,sze;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].key
	#define p(x) t[x].pri
	#define c(x) t[x].cnt
	#define s(x) t[x].sze
}
t[500020];
int rt,pool;
const int INF=-2147483647;
inline int read() 
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') 
    {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') 
    {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline void upt(const int &k) 
{
	s(k)=s(lc(k))+s(rc(k))+c(k);
}
inline void Zig(int &k) 
{
	int y=lc(k);
	lc(k)=rc(y);
	rc(y)=k;
	s(y)=s(k);
	upt(k);
	k=y;
}
inline void Zag(int &k) 
{
	int y=rc(k);
	rc(k)=lc(y);
	lc(y)=k;
	s(y)=s(k);
	upt(k);
	k=y;
}
inline void inserter(int &k,const int &key) 
{
	if(!k) 
    {
		k=++pool;
		v(k)=key;
		p(k)=rand();
		c(k)=s(k)=1;
		lc(k)=rc(k)=0;
		return;
	} 
    else
	++s(k);
	if(v(k)==key)
	++c(k); 
    else if(key<v(k))
    {
		inserter(lc(k),key);
		if(p(lc(k))<p(k))
		Zig(k);
	} 
    else 
    {
		inserter(rc(k),key);
		if(p(rc(k))<p(k))
		Zag(k);
	}
	return;
}
inline void Delete(int &k,const int &key) 
{
	if(v(k)==key) 
    {
		if(c(k)>1)
		--c(k),--s(k); 
        else if(!lc(k)||!rc(k))
		k=lc(k)+rc(k); 
        else if(p(lc(k))<p(rc(k)))
		Zig(k),Delete(k,key); 
        else
		Zag(k),Delete(k,key);
		return;
	}
	--s(k);
	if(key<v(k))
	Delete(lc(k),key); 
    else
	Delete(rc(k),key);
	return;
}
inline int QueryPre(const int &key) 
{
	int x=rt,res=-INF;
	while(x) 
    {
		if(v(x)<key)
		res=v(x),x=rc(x); 
        else
		x=lc(x);
	}
	return res;
}
inline int QuerySuf(const int &key) 
{
	int x=rt,res=INF;
	while(x) 
    {
		if(v(x)>key)
		res=v(x),x=lc(x); 
        else
		x=rc(x);
	}
	return res;
}
inline int QueryKth(int k) 
{
	int x=rt;
	while(x) 
    {
		if(s(lc(x))<k&&s(lc(x))+c(x)>=k)
		return v(x);
		if(s(lc(x))>=k)
		x=lc(x); else
		k-=s(lc(x))+c(x),x=rc(x);
	}
	return 0;
}
inline int QueryRank(const int &key) 
{
	int x=rt,res=0;
	while(x) 
    {
		if(key==v(x))
		return res+s(lc(x))+1;
		if(key<v(x))
		x=lc(x); 
        else
		res+=s(lc(x))+c(x),x=rc(x);
	}
	return res;
}
int a[2000020];
unordered_map<int,int>vis;
int dis(int a,int b) 
{
	return abs(a-b);
}
int main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		int n;
		cin>>n;
		char now;
		string s;
		cin>>now>>s;
		vis.clear();
		for (int i=1;i<=pool;i++)
		lc(i)=rc(i)=v(i)=p(i)=c(i)=s(i)=0;
		rt=pool=0;
		int qq=0;
		for (int i=1;i<=n;i++)
		if(s[i-1]=='g')
		inserter(rt,i),qq++;
		vector<int>pos;
		int ans=0;
		for (int i=0;i<s.size();i++)
		if(s[i]==now)
		pos.push_back(i+1);
		if(now=='g') 
        {
			cout<<0<<'\n';
			continue;
		}
		for (int i=0;i<pos.size();i++) 
        {
			int pre=pos[i];
			int suf=QuerySuf(pos[i]-1);
			if(suf<0)
			suf=2e9,pre=QuerySuf(0);
			//cout<<pre<<' '<<suf<<' '<<pos[i]<<'\n';
			int ans1=n-dis(pre,pos[i]),ans2=dis(suf,pos[i]);
			ans=max(ans,min(ans1,ans2));
		}
		cout<<ans<<'\n';
	}
}
```


---

## 作者：zajasi (赞：0)

感觉自己的思路很清新，来发一篇。
## 题意
规定一个字符 $c$，对于循环字符串 $a$ 中的每一个字符 $c$，找到右边的离它最近的一个 $g$，求这个距离最大是多少。
## 样例解释
```
5 r
rggry
```
第 $1$ 号位置上的 $r$，到离它最近的 $g$（$2$ 号位置）距离是 $1$。

第 $4$ 号位置上的 $r$，到离它最近的 $g$（$7$ 号位置）距离是 $3$。

所以最大距离就是 $3$。
## 解题思路
明显的，我们发现一个字符离它右边最近的 $g$ 要么是在原本字符串上，要么是在原来字符串复制一遍放在后面的字符串上。所以首先，我们 **按序** 排列当前字符串和复制一遍后的字符串上所有 $g$ 的位置。然后对于每一个目标字符，只需要在记录的位置上做二分查找即 `lower_bound` 就可以了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
char c;
string a;
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){ 
        cin>>n>>c>>a;
        a='+'+a;//从 1 开始下标，因为不习惯 0
        vector<int> v;
        for(int i=1;i<a.size();i++){
            if(a[i]=='g')v.push_back(i);
        }//记录当前字符串中 g 的所有位置
        for(int i=1;i<a.size();i++){
            if(a[i]=='g')v.push_back(i+n);
        }//记录复制后的字符串中 g 的所有位置
 //       for(int i=0;i<v.size();i++)cout<<v[i]<<" ";cout<<"\n";
        int z=LLONG_MIN;
        for(int i=1;i<a.size();i++){
            if(a[i]==c){
                int l=lower_bound(v.begin(),v.end(),i)-v.begin();//找到离目标字符最近的 g 的位置
                z=max(z,v[l]-i);//计算距离与目前答案求最大值
//                cout<<l<<" "<<i<<" "<<v[l]<<" "<<v[l]-i<<"\n";
            }
        }
        cout<<z<<"\n";//直接输出
    }
    return 0;
}
```

---

## 作者：xuluhai (赞：0)

### 思路
因为可能出现循环的情况，也就是从 $s_{n-1}$ 走到 $s_{1}$ 的情况，所以我们需要把字符串再复制一份，然后我们只要碰到出发时的灯就开始计时；碰到绿灯就停止计时，最后比较一下那个时间最长就可以了。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
char c;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>c;
		bool flag=false;//flag表示现在在不在走路 
		int cnt=0,ans=0xc0c0c0c0;//初始化为极小值 
		cin>>s;
		s=s+s;//考虑可能出现从s[n-1]走到s[1]的情况 
		for(int i=0;i<=n*2-1;i++){
			if(s[i]==c && !flag){//如果这个字符是出发的字符，且现在不在走路状态 
				flag=true;
			}
			if(s[i]=='g'){ 
				flag=false;
				ans=max(ans,cnt);//因为为了保证此时一定能等到绿灯要取max 
				cnt=0;
			}
			if(flag) cnt++;
		}
		cout<<ans<<endl;
	}


	return 0;
}
```


---

## 作者：XiaoQuQu (赞：0)

考虑预处理出在每一个时间 $i$ 的时候，等到绿灯的最小时间 $ans_i$。

显然，对于所有 $s_i=\texttt g$，$ans_i=0$。否则，记 $ans_i=\inf$。那么有 $ans_i=\min(ans_i,ans_{i+1}+1)$。注意特判 $i=n$ 的情况。

```cpp
// Problem: C. Traffic Light
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

const int MAXN = 2e5 + 5;
char s[MAXN], ch[5], t;
int ans[MAXN];
int n;

void work() {
    cin >> n >> ch;
    t = ch[0];
    cin >> s + 1;
    int x = 0;
    int fr = 0;
    for (int i = n; i >= 1; --i) if (s[i] == 'g') {fr = i; break;}
    for (int i = fr; i >= 1; --i) {
    	ans[i] = ans[i + 1] + 1;
    	if (s[i] == 'g') ans[i] = 0;
    }
    if (s[n] == 'g') ans[n] = 0;
    else ans[n] = ans[1] + 1;
    for (int i = n - 1; i > fr; --i) {
    	ans[i] = ans[i + 1] + 1;
    	if (s[i] == 'g') ans[i] = 0;
    }
    int anss = 0;
    for (int i = 1; i <= n; ++i) {
    	if (s[i] == t) anss = max(anss, ans[i]);
    }
    cout << anss << endl;
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        work();
    }
    return 0;
}
```



---

