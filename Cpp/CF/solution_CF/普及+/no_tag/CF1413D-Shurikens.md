# Shurikens

## 题目描述

Tenten runs a weapon shop for ninjas. Today she is willing to sell $ n $ shurikens which cost $ 1 $ , $ 2 $ , ..., $ n $ ryo (local currency). During a day, Tenten will place the shurikens onto the showcase, which is empty at the beginning of the day. Her job is fairly simple: sometimes Tenten places another shuriken (from the available shurikens) on the showcase, and sometimes a ninja comes in and buys a shuriken from the showcase. Since ninjas are thrifty, they always buy the cheapest shuriken from the showcase.

Tenten keeps a record for all events, and she ends up with a list of the following types of records:

- + means that she placed another shuriken on the showcase;
- - x means that the shuriken of price $ x $ was bought.

Today was a lucky day, and all shurikens were bought. Now Tenten wonders if her list is consistent, and what could be a possible order of placing the shurikens on the showcase. Help her to find this out!

## 说明/提示

In the first example Tenten first placed shurikens with prices $ 4 $ and $ 2 $ . After this a customer came in and bought the cheapest shuriken which costed $ 2 $ . Next, Tenten added a shuriken with price $ 3 $ on the showcase to the already placed $ 4 $ -ryo. Then a new customer bought this $ 3 $ -ryo shuriken. After this she added a $ 1 $ -ryo shuriken. Finally, the last two customers bought shurikens $ 1 $ and $ 4 $ , respectively. Note that the order $ [2, 4, 3, 1] $ is also valid.

In the second example the first customer bought a shuriken before anything was placed, which is clearly impossible.

In the third example Tenten put all her shurikens onto the showcase, after which a customer came in and bought a shuriken with price $ 2 $ . This is impossible since the shuriken was not the cheapest, we know that the $ 1 $ -ryo shuriken was also there.

## 样例 #1

### 输入

```
4
+
+
- 2
+
- 3
+
- 1
- 4```

### 输出

```
YES
4 2 3 1```

## 样例 #2

### 输入

```
1
- 1
+```

### 输出

```
NO```

## 样例 #3

### 输入

```
3
+
+
+
- 2
- 1
- 3```

### 输出

```
NO```

# 题解

## 作者：AFOier (赞：7)

~~翻译好评~~

我们倒序进行操作，维护一个栈

对于每个购买操作，我们把它压入栈中

对于每个放置操作，我们只需取出栈顶

如果当前压入栈中的数大于栈顶元素/弹栈时栈为空，则无解

考虑正确性：

栈中存储的是接下来要购买的物品价格（也即之前放置的物品），由于购买时一定买最便宜的，所以最便宜的最后加入一定是最优的

如果当前压入栈中的数大于栈顶元素，那么当前元素和栈顶元素都会在前面放入，不符合买最便宜的要求，无解

时间复杂度$O(n)$

```
#include <bits/stdc++.h>
using namespace std;
int n, sta[200011], cnt;
int s[200011], ans[200011];
char opt[200011];
int main() {
	scanf("%d", &n); n *= 2;
	for(int i = 1; i <= n; i++) {
		cin >> opt[i];
		if(opt[i] == '-') scanf("%d", &s[i]);
	}
	for(int i = n; i >= 1; i--) {
		if(opt[i] == '-') {
			if(cnt && s[i] > sta[cnt]) {
				cout << "NO" << endl;
				return 0;
			}
			sta[++cnt] = s[i];
		}
		else {
			if(!cnt) {
				cout << "NO" << endl;
				return 0;
			}
			ans[i] = sta[cnt--];
		}
	}
	cout << "YES" << endl;
	for(int i = 1; i <= n; i++) 
	if(opt[i] == '+') cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：Singercoder (赞：3)

掉分选手带着残念来补本题的三种做法...

# O(n)

对于每一次`- x`操作，我们发现它除了能去掉价格为x的手里剑，还有能给我们一个信息：剩余所有手里剑价格>x。

所以对于当前的`- x1`操作，我们只要找到一个还未匹配的`+`，使得这二者之间的所有`- x2`操作都满足x2<x1，即所有值都必须比x1小；那么我们只需要预处理一下第一个比x1大的前驱即可，用单调栈O(n)维护。

那么应该选择哪一个`+`呢？不难发现对于所有可以匹配的`+`，**在匹配过后，它们的限制都会上升至x1**，也就是说无论选择哪一个，对于后续操作的影响都相同。

选择最近的未匹配`+`即可，注意判断一下它是否在比x1大的前驱之后，如果不是则无解。

```cpp
#include<bits/stdc++.h>

#define ri register int 

#define inf 0x3f3f3f3f

using std::cin;

const int MAXN=2e5+10;

int n;
int a[MAXN],pre[MAXN];
int s[MAXN],top;
bool vis[MAXN];

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	char op;
	for(ri i=1;i<=n*2;++i)
	{
		cin>>op;
		if(op=='+')vis[i]=1;
		else scanf("%d",&a[i]);
	}
	
	a[0]=inf;
	s[++top]=0;
	for(ri i=1;i<=n*2;++i)if(!vis[i])
	{
		while(a[i]>a[s[top]])--top;
		pre[i]=s[top];
		s[++top]=i;
	}
	
	top=0;
	for(ri i=1;i<=n*2;++i)
	{
		if(vis[i])s[++top]=i;
		else
		{
			if(!top || s[top]<pre[i]){printf("NO");return 0;}
			else a[s[top--]]=a[i];
		}
	}
	
	printf("YES\n");
	for(ri i=1;i<=n*2;++i)if(vis[i])printf("%d ",a[i]);
	
	return 0;
}

```

# 逆向思路

由上个做法可知我们的匹配其实就是括号匹配。

那能不能先匹配，然后检查匹配的合法性呢？

比如:$((()())())$

~~像套娃一样是不是~~

我们发现对于每个匹配，它的外层匹配的值一定更大，所以从后往前遍历，用单调栈（~~没错还是它~~）或者堆来维护未匹配右括号的最小值，判断它与当前右括号之间的大小关系，若比当前右括号还小则无解。

应该是和官方题解一个思路的吧？~~所以不贴代码了~~。

# O(nlogn)

~~都有O(n)做法了为什么还要讲O(nlogn)的啊喂~~。

刚才那个算法成立的一个很重要的因素在于：对于每个`-x`，前面所有未匹配`+`都是等价的。

但如果你~~像我一样~~没能发现这一点，而认为一定要在可匹配`+`中选择最靠前的那一个，也可以在单调栈上进行一个小小的二分查找。

但如果这样，用所有`- x`操作去给栈内的`+`更新限制的复杂度会达到$O(n^2)$，所以我们考虑直接在栈内存储`- x`操作。

如果这样的话，我们就必须支持快速查询每个`-x`操作后面第一个未被匹配的`+`，这个如果暴力跳后继又会达到$O(n^2)$，我们考虑像并查集那样进行路径压缩。

~~考场上就在想这么复杂的题目都能做出来上分肯定稳了~~

```cpp
#include<bits/stdc++.h>

#define ri register int 
#define pii pair<int,int>

#define inf 0x3f3f3f3f

using std::cin;
using std::min;
using std::sort;
using std::pair;

const int MAXN=2e5+10;

int n,a[MAXN];
bool vis[MAXN];

int nxt[MAXN];
int get_nxt(int u){return nxt[u]==u?u:nxt[u]=get_nxt(nxt[u]);}

int h,t;
pii q[MAXN];

int main()
{
//	freopen("1.in","r",stdin);

	scanf("%d",&n);
	char op;
	for(ri i=1;i<=n*2;++i)
	{
		cin>>op;
		if(op=='+')vis[i]=1;
		else scanf("%d",&a[i]);
	}
	vis[n*2+1]=1;
	for(ri i=0;i<=n*2+1;++i)nxt[i]=i+!vis[i];
	
	q[h=t=n]=pii(inf,0);
	for(ri i=1,j,k;i<=n*2;++i)if(!vis[i])
	{
		j=lower_bound(q+h,q+t+1,pii(a[i],i))->second;
		k=get_nxt(j);
		
		if(k>i){printf("NO\n");return 0;}
		else
		{
			a[k]=a[i];
			nxt[k]=k+1;
		}
		
		while(a[i]>q[h].first)++h;
		q[--h]=pii(a[i],i);
	}
	
	printf("YES\n");
	for(ri i=1;i<=n*2;++i)if(vis[i])printf("%d ",a[i]);
	printf("\n");
	
	return 0;
}

```

---

## 作者：dead_X (赞：3)

## 1 前言
遇到这种信息不对称的题倒着跑是经典Trick吧

但是你们为什么都正着搜啊
## 2 思路
离线操作并维护一个堆，倒着往回搜。

* 如果是 $-$

这个时候应该是堆中加入了一个更小的数。我们直接判断堆顶和加入的数的大小关系然后插入或者直接输出 ``NO`` 。

* 如果是 $+$ 

这意味着我们可以随便拿出一个数，所以我们要分析拿哪个数更优。

注意到上面的操作需要堆顶尽量大，于是一个非常自然的想法就是取走堆顶。

**坑点：如果没有数可取也是非法的。**
## 3 代码
[R.I.P(大家可以看看为什么WA了)](https://codeforces.ml/contest/1434/submission/96663694)
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
char ch[200003][4];
int a[200003];
int ans[100003];
signed main()
{
    int n=read();
    for(int i=1; i<=2*n; i++)
    {
        scanf("%s",ch[i]);
        if(ch[i][0]=='-') a[i]=read();
    }
    stack<int> s;
    int cnt=0;
    for(int i=1; i<=2*n; i++)
    {
        if(ch[i][0]=='+') 
        {
            s.push(++cnt);
        }
        else
        {
            if(s.empty()) puts("NO"),exit(0);//loveti
            int x=s.top();
            if(ans[x]>a[i]) puts("NO"),exit(0);
            ans[x]=a[i],s.pop();
            if(!s.empty())ans[s.top()]=max(ans[s.top()],a[i]);
        }
    }
    puts("YES");
    for(int i=1; i<=n; i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：AlanSP (赞：2)

~~第一次fst/kk~~

考虑维护一个栈，栈内加入的是下标，并未赋值。

把购买操作看成弹栈，并把栈顶代表的下标赋成当前的 $x$。

每次弹栈时，维护一个标记，表示当前栈内元素曾经的最小值。

由于只会在弹栈中考虑判定大小，所以加在栈顶就好了。

不合法有两种情况：

- 当前栈为空。

- 栈顶标记 > 当前元素，说明栈内有比最小值还小的元素。

之后模拟就好了，复杂度 $O(n)$，也不需要离线和倒推。

**更新标记时一定要和原本的标记取max！！！**
---

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+9;
int n,stk[N],top,num,ans[N],tag[N],cnt;
char op[3];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++)
	{
		scanf("%s",op+1);
		if(op[1]=='+') stk[++top]=++cnt;
		else
		{
			int x;
			scanf("%d",&x);
			if(!top||x<=tag[stk[top]]) return puts("NO"),0;
			ans[stk[top--]]=x;
			tag[stk[top]]=max(tag[stk[top]],max(tag[stk[top+1]],x));
		}
	}
	if(top) return puts("NO"),0;
	puts("YES");
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：NightmareAlita (赞：1)

## 简要题意

给定一个 $n$ 和 $2n$ 个操作，第一种操作 "+" 表示从 $1$ ~ $n$ 中选择一个数插入序列，第二种操作 " - $x$" 表示从当前序列中删除 $x$ 且 $x$ 为当前序列里的最小值，根据给出的操作来推断将数插入序列的合法顺序。

## 策略分析

### 不合法情况

不合法的情况有两种。第一种是当在连续取出的两个值中，后取出的值比前取出的值小，因为每次必须取出序列里最小的值，所以这种情况显然是不符合要求的。第二种情况是取出的操作数比放入的操作数多，这样显然也是不合法的。

### 如何处理合法情况

我们看到这种有进有出的结构能够想到什么，怎么才能反转操作呢？我们很自然地想到可以用栈来实现。我们倒着进行操作，遇到取数操作就把取出来的数压入栈 $s$，遇到插入操作就把 $s$ 栈顶元素弹出来塞进另一个栈 $ans$ 里，最后把 $ans$ 里的元素依次弹出就是答案所要的序列了。按照刚刚讨论过的不合法情况，当 $s$ 中入栈元素比栈顶元素大则不合法，如果需要弹出时栈 $s$ 为空则不合法。

### 正确性证明

因为每次都要取序列中的最小值，所以后出来的元素一定是更大的，我们就默认它插入得更早。而倒序插入的时候保证了小的元素一定后进栈，所以也不会出现弹出一个数时它还没插入的情况。当 $s$ 入栈元素大于栈顶元素，就相当于操作时取出的值不是最小值；而当弹栈时栈空了，就说明插入的数量少于取出的数量，刚好就对应上了上面分析的不合法情况。由此就可以判断出其正确性。

## 实现

```cpp
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

namespace SHAWN {
    stack<int> s;
    stack<int> ans;
    vector<int> opt;// 记录操作
    int n;
    int work()
    {
        cin >> n;
        for (int i = 1; i <= 2 * n; ++i) {
            char op; int x;
            cin >> op;
            if (op == '+') { opt.emplace_back(0); }
            else if(op == '-') { cin >> x; opt.emplace_back(x); }
        }
        for (int i = opt.size() - 1; i >= 0; --i) {
            // 倒着复现操作
            if (!opt[i]) {
                if (s.empty()) { cout << "NO\n"; return 0; }
                // 插入的数量少于取出的数量
                else { ans.push(s.top()); s.pop(); }
            }
            else {
                if (s.size() && opt[i] > s.top()) { cout << "NO\n"; return 0; }
                // 操作时取出的值不是最小值
                else { s.push(opt[i]); }
            }
        }
        cout << "YES\n"; 
        while (!ans.empty()) { cout << ans.top() << ' '; ans.pop(); }
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

## 作者：tommymio (赞：1)

这题事实上就是叫我们把每个 $+$ 和 $-$ 配对，并且不能出现非法的情况，求给出 **任意一种** 方案。

观察一下，只有两种情况是非法的：

- 卖出的手里剑并不是当前最便宜的，即存在比卖出的 $x$ 更小的数
- 卖出的比摆放的多，即 $-$ 数大于 $+$ 数

第二种情况是非常好判断的。现在来解决第一种情况。出现第一种情况，一定是把比卖出的 $x$ 更小的数和 $x$ 摆放在了一起。也就是说比 $x$ 更小的数在 $x$ 被卖出前就被摆放了。为了不存在这种情况，我们将当前 $x$ 与大于当前 $x$ 的第一个数之后的能匹配的 $+$ 匹配。

这个过程使用一个单调栈维护第一个大于 $x$ 的位置，和一个 $set$ 维护这个位置后第一个 $+$ 即可，时间复杂度为 $O(n\log n)$。

代码就不贴了，非常好实现。



---

## 作者：BFqwq (赞：1)

对于每一个数，其合法的位置是在自己上一个比它大的数卖出之后（否则上一个比它大的数必然非法）。

于是一个很显然的贪心是，当我们处理到某一个 `-` 时，如果有多个 `+` 可以对应，则取最前面的一定是最优的。注意此处的可以对应该是在合法的前提下的。

因为对于一个数，它与上一个比它大的数之间还有若干个数，这中间的 `+` 它都是可以占用的。但对于比它小的某个数，这中间的部分 `+` 是不能占用的，因而选在越前面越好。

这样就有一种自然的想法：用一个单调栈维护它之前最近的比它大的数的位置，然后用一个 set 维护所有 `+` 的位置。每个数的对应位置就是它前面比它大的最近的数之后的第一个 `+`。

如果无法匹配，则输出 `NO`。

```cpp
#include <bits/stdc++.h>
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
set<int> s;
set<int>::iterator it;
int a[maxn<<1],st[maxn],top,ans[maxn<<1],n;
signed main(){
	n=read();
	for(int i=1;i<=n*2;i++){
		char c=getchar();
		while(c!='+'&&c!='-'){
			c=getchar();
		}
		if(c=='+'){
			s.insert(i);
		}
		else{
			if(s.empty()){
				puts("NO");
				return 0;
			}
			a[i]=read();
			while(top&&a[st[top]]<a[i]){
				top--;
			}
			it=s.lower_bound(st[top]);
			if(it==s.end()){
				puts("NO");
				return 0;
			}
			ans[*it]=a[i];
			st[++top]=i;
			s.erase(it);
		}
	}
	puts("YES");
	for(int i=1;i<=n*2;i++){
		if(ans[i]) print(ans[i],' ');
	}
	return 0;
}
```


---

## 作者：lyhqwq (赞：0)

# Solution

水题。

倒着做，把加数变为删数，删数变为加数，维护一个优先队列，如果当前要加入的数大于已经加入的数的最小值，那么就无解，因为每次买走的一定是最便宜的一个，在最小值一定是最先被删除，即最后被加入的。若合法，则记录答案。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
struct node{
    char op;
    int x;
}a[N];
int n,x;
int ans[N];
priority_queue<int,vector<int>,greater<int> > q;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++){
        scanf(" %c",&a[i].op);
        if(a[i].op=='-') scanf("%d",&a[i].x);
    }
    x=n;
    for(int i=2*n;i>=1;i--){
        if(a[i].op=='+'){
            if(q.empty()) return puts("NO"),0;
            ans[x--]=q.top();
            q.pop();
        }
        else{
            if(!q.empty()&&q.top()<a[i].x) return puts("NO"),0;
            q.push(a[i].x);
        }
    }
    puts("YES");
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}

```

---

