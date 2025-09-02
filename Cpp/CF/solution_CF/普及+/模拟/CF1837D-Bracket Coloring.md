# Bracket Coloring

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- the bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- the bracket sequences ")(", "(" and ")" are not.

A bracket sequence is called beautiful if one of the following conditions is satisfied:

- it is a regular bracket sequence;
- if the order of the characters in this sequence is reversed, it becomes a regular bracket sequence.

For example, the bracket sequences "()()", "(())", ")))(((", "))()((" are beautiful.

You are given a bracket sequence $ s $ . You have to color it in such a way that:

- every bracket is colored into one color;
- for every color, there is at least one bracket colored into that color;
- for every color, if you write down the sequence of brackets having that color in the order they appear, you will get a beautiful bracket sequence.

Color the given bracket sequence $ s $ into the minimum number of colors according to these constraints, or report that it is impossible.

## 样例 #1

### 输入

```
4
8
((())))(
4
(())
4
))((
3
(()```

### 输出

```
2
2 2 2 1 2 2 2 1
1
1 1 1 1
1
1 1 1 1
-1```

# 题解

## 作者：igAC (赞：12)

# $\text{Describe}$

[CFlink](https://codeforces.com/contest/1837/problem/D)

[洛谷 link](https://www.luogu.com.cn/problem/CF1837D)

# $\text{Solution}$

括号序列的套路：左括号记为 $+1$，右括号记为 $-1$，求前缀和。

有一个显然的结论：原序列左右括号个数相同是能否分为若干个合法括号序列的充要条件。

如果整个序列合法，那就全输出 $1$ 就行了。

否则，一定是分成两组。

记前缀和为 $sum$。

若 $sum_i<0$ 或 $sum_{i-1}<0$ 则分为第一组。

剩下的分到第二组，可以证明这样是对的。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,a[N],sum[N];
string s;
void solve(){
	n=read();cin>>s;
	for(int i=1;i<=n;++i) a[i]=(s[i-1]=='(')?1:-1;
	for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
	if(sum[n]){
		puts("-1");
		return;
	}
	bool flg1=false,flg2=false;
	for(int i=1;i<=n;++i){
		flg1|=(sum[i]<0);
		flg2|=(sum[i]>0);
	}
	if(!(flg1&flg2)){
		puts("1");
		for(int i=1;i<=n;++i) printf("1 ");
		puts("");
		return;
	}
	puts("2");
	for(int i=1;i<=n;++i) printf((sum[i]<0 || sum[i-1]<0)?"1 ":"2 ");
	puts("");
}
int main(){
	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：strcmp (赞：6)

**题目大意：** 给定一个长度为 $n$ 的括号序列，将这个括号用其**子序列**覆盖，使得每个子序列都满足：

- 任意前缀的左括号数量不少于右括号数量，或者任意前缀的右括号数量不少于左括号数量。前者我们称为**满足条件 $1$ 的子序列**，后者称为**满足条件 $2$ 的子序列。**

- 左括号数量与右括号数量相等。

求出任意一个方案，使得覆盖这个序列的子序列**数量最少**。

## Solution

首先，有无解的充要条件为总括号序列的左括号数量和右括号数量相等。充分性显然，必要性的话可以构造 $\frac{n}{2}$ 个单独的子序列，每个子序列为 `()`，这就是一个解。

注意到有一个显然的结论，就是**最少的子序列个数必然不会超过 $2$**。

考虑证明一下，设最少有 $k$ 个合法子序列才能将整个序列覆盖掉，很显然这些子序列要么只满足条件 $1$，要么只满足条件 $2$。

对于任意两个满足条件 $1$ 的序列，**我们可以直接将它们首尾接起来，而不影响其合法性。** 首先，二者本身左括号和右括号数量都是相等的，加起来也必然相等，即左括号数量与右括号数量相等。又因为任意前缀的左括号不少于右括号数量，前者从 $1$ 到相接处的条件都已经满足了，而 $1$ 到相接处的左括号数量与右括号数量相等，所以只用看相接处以后的合法性，根据后者的合法性，相接处以后的序列也是合法的。所以这个序列就是合法的，我们可以直接将两个小的合法子序列并成一个较大的合法的子序列。对于满足条件 $2$ 的序列，类似讨论即可，也可以证明首尾相接不影响其合法性。

此时我们发现将满足条件 $1$ 的子序列全部并在一起；满足条件 $2$ 的子序列全部并在一起，也就只剩下两个子序列了。

方便起见，默认 $s_0 = 0$，子序列 $a$ 满足条件 $1$。子序列 $b$ 满足条件 $2$。

对于这两个子序列，考虑如何分配。将左括号看作 $1$，右括号看作 $-1$，对整个括号序列做一遍前缀和，记为 $s_i$。

接下来我们可以选择直接开两个线性表无脑的做贪心，但第一篇题解（Orz）提出了一个合法而又简洁的选择方案是**如果 $s_i < 0$ 或者 $s_{i - 1} < 0$ 则将 $i$ 归入 $a$，否则归入 $b$。**

考虑这样做的合法性。我们发现它本质上是将括号序列分为了两类**偶回文串！**

什么意思呢？可以结合一个数据看：

```
input:
1
18
((()))())(()())(()

output:
2
1 1 1 1 1 1 1 1 2 2 1 1 1 1 2 2 1 1 
```

对 $a$ 和 $b$ 的交界点用 `|` 隔开，可以得到：

```
((()))()|)(|()()|)(|()
```

再拆一下，这次我们取 $s_i = 0$ 的点拆。

```
((()))|()|)(|()()|)(|()
```

我们发现放在 $a$ 里的都是形如 $\texttt{(((...)))}$ 的子串，$b$ 里的都是形如 $\texttt{)))...(((}$ 的子串。我们称前者为 $\text A$ 类子串，后者为 $\text B$ 类子串。

证明 $\text{A}$ 类串起来符合所有要求是极为显然的。而根据之前的结论，有 $k$ 个串同时满足条件 $1$，那么它们串起来也满足条件 $1$。$\text B$ 类子序列也同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/xyo4rtpq.png)

感性理解一下，任意左右括号数相等的括号序列，都可以由 $\text A$ 类串和 $\text B$ 类串拼接和插入得到。所以我们的策略是正确的。

这时候找出函数与 $0$ 轴的交点就行了，容易得到交点为满足 $s_{i - 1} = -1$ 且 $s_{i} = 0$ 的点和 $s_{i - 1} = 0$ 且 $s_{i} = -1$ 的点。分别归入两类子序列中即可。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 2e5 + 10;
char s[maxn]; ll sum[maxn];
int main(){
	int t, n; scanf("%d", &t);
	while(t--){
		scanf("%d", &n); scanf("%s", s + 1); 
		for (int i = 1; i <= n; i++)sum[i] += sum[i - 1] + (s[i] == '(' ? 1 : -1);
		if (sum[n] != 0)puts("-1");
		else{
			int o = 0, p = 0;
			for (int i = 1; i <= n; i++)o |= (sum[i] > 0), p |= (sum[i] < 0);
			if (o ^ p){
				puts("1");
				for (int i = 1; i <= n; i++)printf("1 ");
				puts("");
			}else{
				puts("2");
				for (int i = 1; i <= n; i++){
					if(sum[i] < 0 || sum[i - 1] < 0)printf("2 ");
					else printf("1 ");
				}
				puts("");
			} 
		}
		for (int i = 1; i <= n; i++)sum[i] = 0;
	}
	return 0;
}
```


---

## 作者：TheForsaking (赞：2)

若原序列左右括号个数不同则无解。  

若原序列已经是优美序列，则组数为１。  

考虑其他情况，设原序列长度为 $2n$，则左右括号的数量均为 $n$。若原序列前半部分左括号的数量为 $x$，则后半部分左括号数量为 $n-x$，右括号数量为 $x$，因此将前半部分的左括号和后半部分的右括号分为一组，前半部分的右括号和后半部分的左括号分为另一组即可构造出组数为 $2$ 的方案。  

附上代码  
```
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <stack>
#include <ctime>

using namespace std;

typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, pii> piii;
typedef pair<int, long long > pil;
typedef long long ll;
const int N = 200086, MOD = 1e9 + 7, INF = 0x3f3f3f3f, MID = 50000;
int n, m, a[N];
char s[N];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        scanf("%s", s + 1);
        bool up = 0, down = 0;
        for (int i = 1; i < n + 1; i++)
        {
            if (s[i] == '(') a[i] = a[i - 1] + 1;
            else a[i] = a[i - 1] - 1;
            if (a[i] > 0) up = 1;
            else if (a[i] < 0) down = 1;
        }
        if (a[n])
        {
            printf("-1\n");
            continue;
        }
        if (!up || !down)
        {
            printf("1\n");
            for (int i = 1; i < n + 1; i++) printf("%d ", 1);
            printf("\n");
            continue;
        }
        printf("2\n");
        for (int i = 1; i < n + 1; i++)
        {
            if (i <= n / 2)
            {
                if (s[i] == '(') printf("1 ");
                else printf("2 ");
            }
            else
            {
                if (s[i] == ')') printf("1 ");
                else printf("2 ");
            }
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 分析

对于某个子串的开头 $c$，如果 $c$ 是左括号，则这个子串的要求就是条件一；如果 $c$ 是右括号，则这个子串的要求就是条件二。不难想到，如果一个子串 $x$ 属于条件一，而后面是一个属于条件二的子串 $y$，再之后又是一个属于条件一的子串 $z$。则我们可以把 $x$ 和 $z$ 分为一组，因为这两组的任意前缀都是满足条件一的，反之同理。

我们可以统计两个前缀和，存左右括号出现的次数。枚举每一位，如果将这一个字符加进当前截取的子串，则需判断这一位对应的前缀和是否满足该子串属于的条件。不满足，则新开一个子串，记录这个子串的开头。最后将条件相同的输出一样的分组即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int t,n;
string s;
int s1[N],s2[N];
int w[N];
bool check(){
	if(s1[s.size()]!=s2[s.size()]){
		return 0;
	}
	int nowk=-1,l=1,now=1;
	for(int i=1;i<=s.size();i++){
		if(s1[i]-s1[l-1]==s2[i]-s2[l-1]){
			w[i]=nowk;
		}
		else{
			if(s1[i]-s1[l-1]>s2[i]-s2[l-1]){
				if(nowk!=1){
					nowk=1,l=i,w[i]=nowk;
				}
				else{
					w[i]=nowk;
				}
			}
			else{
				if(nowk!=2){
					nowk=2,l=i,w[i]=nowk;
				}
				else{
					w[i]=nowk;
				}			
			}
		}
	}
	return 1;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		memset(s2,0,sizeof(s2)),memset(s1,0,sizeof(s1));
		for(int i=0;i<s.size();i++){
			if(s[i]=='(') s1[i+1]++;
			else s2[i+1]++;
			s1[i+1]+=s1[i],s2[i+1]+=s2[i];
		}
		int ans=check();
		if(!ans){
			cout<<"-1\n";
		}
		else{
			int fl=0,k1=0,k2=0;
			for(int i=1;i<=s.size();i++){
				if(!k1&&w[i]==1) k1=1,fl++;
				if(!k2&&w[i]==2) k2=1,fl++;
			}
			cout<<fl<<"\n";
			for(int i=1;i<=s.size();i++){
				if(fl==2) cout<<w[i]<<" ";
				else cout<<1<<" ";
			}
			cout<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：1)

括号匹配板子题？建议评橙到黄。

------------

先考虑无解的情况。如果左右括号总个数不同，无论咋分都没用。

直接暴力跑出整个序列是否是优美的，如果是就都放 $1$ 组就行。

如果不是，考虑顶多分两组。

把所有不能和当前匹配的放 $2$ 组，由于此题不区分左右括号，$2$ 组一定也能匹配。

用两个栈分别存放无法直接匹配左括号和右括号，线性维护就行。

总体复杂度 $\operatorname{O}(T\times n)$。

------------

没啥难的吧。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,cntz,cntf[2],cnt[2],st[maxn][2],ans[maxn];
char s[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        scanf("%s",s+1);
        cntz=cntf[0]=cntf[1]=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='(')
                cntz++;
            if(cntz>=i-cntz)
                cntf[0]++;
            if(i-cntz>=cntz)
             	cntf[1]++;
        }
        if(cntz*2!=n){
            puts("-1 Sherry");
            continue;
        }
        if(cntf[0]==0||cntf[0]==n||cntf[1]==0||cntf[1]==n){
            puts("1 Sherry");
            for(int i=1;i<=n;i++)
                printf("1 ");
            puts("Sherry");
            continue;
        }
        puts("2 Sherry");
        memset(ans,0,sizeof(ans));
        cnt[0]=cnt[1]=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='('){
                if(cnt[1])
                    ans[i]=ans[st[cnt[1]--][1]]=2;
                else
                    st[++cnt[0]][0]=i;
            }
            else{
                if(cnt[0])
                    ans[i]=ans[st[cnt[0]--][0]]=1;
                else
                    st[++cnt[1]][1]=i;
            }
        }
        for(int i=1;i<=n;i++)
            printf("%d ",ans[i]);
        puts("Sherry");
    }
    return 0;
}
```


---

## 作者：hanjinghao (赞：1)

# 题意

如果一个括号序列符合以下两个条件中的一个，那么它是优美的：

1、序列的任意一个前缀中，左括号的个数不少于右括号的个数，且整个序列中，左括号的个数等于右括号的个数。

2、序列的任意一个前缀中，右括号的个数不少于左括号的个数，且整个序列中，左括号的个数等于右括号的个数。

给定一个括号序列，你需要把它分成若干组，使得每一组的括号构成的序列都是优美的。求最少需要分成多少组，并输出分组方案。如果无解，输出 $ -1 $。

# 思路

如果整个序列中，左括号的个数不等于右括号的个数，那么**一定无解**。

如果整个序列就是一个优美的序列，那么把所有的括号都分在同一组即可。

其余情况，一定是恰好分成两组。开两个栈 $ s_1 $ 和 $ s_2 $，分别存储左括号和右括号。从左往右扫描，对于左括号，如果此时 $ s_2 $ 非空，那么把这个左括号和 $ s_2 $ 栈顶的右括号都分在第二组，并把 $ s_2 $ 栈顶的右括号弹出栈；否则，把这个左括号加入 $ s_1 $。对于右括号，如果此时 $ s_1 $ 非空，那么把这个右括号和 $ s_1 $ 栈顶的左括号都分在第一组，并把 $ s_1 $ 栈顶的左括号弹出栈；否则，把这个右括号加入 $ s_2 $。

# 代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline void read(T &x)
{
	x = 0;
	bool flg = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= (c == '-');
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = (x % 10) | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline void writesp(T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline void writeln(T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5;
int T, n, col[N], Top1, Top2, sta1[N], sta2[N];
char s[N];

int main()
{
	read(T);
	while (T--)
	{
		read(n);
		scanf("%s", s + 1);
		int cnt = 0;
		for (int i = 1; i <= n; ++i)
			if (s[i] == '(') ++cnt;
			else --cnt;
		if (cnt)
		{
			puts("-1");
			continue;
		}
		cnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (s[i] == '(') ++cnt;
			else --cnt;
			if (cnt < 0) goto Fail1;
		}
		puts("1");
		for (int i = 1; i <= n; ++i)
			writesp(1);
		putchar(10);
		continue;
		Fail1:;
		cnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (s[i] == ')') ++cnt;
			else --cnt;
			if (cnt < 0) goto Fail2;
		}
		puts("1");
		for (int i = 1; i <= n; ++i)
			writesp(1);
		putchar(10);
		continue;
		Fail2:;
		puts("2");
		Top1 = Top2 = 0;
		for (int i = 1; i <= n; ++i)
			if (s[i] == '(')
			{
				if (Top2)
				{
					col[i] = col[sta2[Top2]] = 2;
					--Top2;
				}
				else sta1[++Top1] = i;
			}
			else
			{
				if (Top1)
				{
					col[i] = col[sta1[Top1]] = 1;
					--Top1;
				}
				else sta2[++Top2] = i;
			}
		for (int i = 1; i <= n; ++i)
			writesp(col[i]);
		putchar(10);
	}
	return 0;
}

```

---

## 作者：__AFO__ (赞：0)

## 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1837D)

这道题考察利用字符串的使用，如果左右括号的数量不相同，直接输出 $-1$ ，这道题其实最多只有两个括号，一个是正括号，另一个是反括号，因为题中要求的括号不一定要连续，只要左右括号数量相等就一定可以成立，而题中只有两种类型的括号，那染色就变得简单了，注意不要被样例得迷惑了，样例一也可以写为 $2 2 2 2 2 2 1 1$ 这样题目就变得简单了，只需特判是不是只有一种类型的括号即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long l,r,n,q,c[1000010],o,u;
stack<long long> p;//栈储存括号下标 
int main(){
    scanf("%lld",&q);
    while(q--){
    	o=0;
    	u=0;
    	l=0;
    	r=0;
    	while(!p.empty()){//每组样例初始化栈 
    		p.pop();
		}
    	scanf("%lld",&n);
    	cin>>s;
    	for(long long i=0;i<n;i++){
    		if(p.empty()){//如果栈是空的，直接添加下标 
    		   p.push(i);
			}
    		else{
    			if(s[p.top()]!=s[i]&&s[i]==')'){//如果栈顶括号和新括号可以组成一对正括号 
    				c[i]=1;//将颜色都染成1 
    				c[p.top()]=1;
    				o++;//说明存在正括号 
    				p.pop();
				}else if(s[p.top()]!=s[i]&&s[i]=='('){//如果栈顶括号和新括号可以组成一对反括号 
					c[i]=2;//将颜色都染成2 
					c[p.top()]=2;
					p.pop();
					u++;//说明存在反括号 
				}else{
					p.push(i);//否则加入栈 
				}
			}
    		if(s[i]=='(') l++;//统计左右括号数量 
    		else r++;
		}
		if(l!=r){//如果数量不等 
			printf("-1\n");//输出-1 
			continue;
		}
		if(u>0&&o>0) printf("2\n"),o=0;//两种括号都存在，输出2 
		else if((u==0&&o>0)||(o==0&&u>0)) printf("1\n"),o=1;//只有一种括号，输出1 
		for(long long i=0;i<n;i++){
			if(o==1) printf("1 ");//如果只有一种括号，全部输出1 
			else printf("%lld ",c[i]);//否则输出颜色编号 
		}
		printf("\n");
	}

	return 0;
}
```

END

---

## 作者：lovely_hyzhuo (赞：0)

## 1.题意

首先我们的优美括号序列就是正序是合法的括号序列或者倒序是合法的括号序列。

现在我们要将整个序列染色，使得每种颜色按原顺序写下都是完美的。

## 2.题目分析

显然整个序列左右括号数量必须一样，否则输出无解。

对于所有的合法的原括号序列的不重叠的子序列，可以拼在一起，这样一定是优美的，染成同色。

对于剩下的括号，大概像先右括号再左括号拼成一个的，染成同色。

所以我们可以用两个栈来模拟。

第一个栈放左括号的下标。如果有右括号来了直接弹出，标记为第一种颜色。

第二个栈放右括号的下标。如果有左括号来了直接弹出，标记为第二种颜色。

最后如果只用一种颜色可以涂完，特判一下就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000010];
int b[1000010];
void solve()
{
	stack<int>st1,st2;
	int n;
	cin>>n;
	cin>>a;
	int cntz=0,cnty=0;
	for(int i=0;i<n;i++)
	{
		if(a[i]==')')
			cnty++;
		else
			cntz++;
	}
	if(cntz!=cnty)
	{
		cout<<"-1\n";
		return;
	}
	int flag1=0,flag2=0;
	for(int i=0;i<n;i++)
	{
		if(a[i]==')')
		{
			if(st1.size()==0)
				st2.push(i);
			else
				b[st1.top()]=1,b[i]=1,st1.pop();
		}
		else
		{
			if(st2.size()==0)
				st1.push(i);
			else
				b[st2.top()]=2,b[i]=2,st2.pop();
		}
	}
	for(int i=0;i<n;i++)
	{
		if(b[i]==1)
			flag1=1;
		else
			flag2=1;
	}
	cout<<flag1+flag2<<endl;
	for(int i=0;i<n;i++)
	{
		if(flag1==0&&b[i]==2)
			b[i]--;
	}
	for(int i=0;i<n;i++)
		cout<<b[i]<<" ";
	cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：___nyLittleT___ (赞：0)

# 思路
用前缀和数组记录括号的情况：  
- `( ->`$\ 1$  
- `) ->`$\ -1$  
检查每一个位置，按题目要求输出即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define check(s) (s=='('?1:-1)
using namespace std;
int t,n;
char s;
int sum[200005];
int main() {
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--) {
		bool f1=false,f2=false;
		cin>>n;
		for(int i=1; i<=n; i++) {
			cin>>s;
			sum[i]=sum[i-1]+check(s);
		}
		if(sum[n]) {
			printf("-1\n");
			continue;
		}
		for(int i=1; i<=n; i++) {
			f1|=(sum[i]<0);
			f2|=(sum[i]>0);
		}
		if(f1&&f2) {
			printf("2\n");
			for(int i=1; i<=n; i++) {
				if(sum[i]<0||sum[i-1]<0) printf("1 ");
				else printf("2 ");
			}
			printf("\n");
		} else {
			printf("1\n");
			for(int i=1; i<=n; i++) printf("1 ");
			printf("\n");
		}
	}
	return 0;
}
```

---

