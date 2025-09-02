# Library game

## 题目描述

Alessia and Bernardo are discovering the world of competitive programming through the books of their university library.

The library consists of $ m $ sections numbered from $ 1 $ to $ m $ . Each section contains only books dedicated to a particular subject and different sections correspond to different subjects. In order to prevent the students from wandering in the library, the university has established a system of passes. Each pass has a length $ y $ associated to it and allows access to an interval of $ y $ consecutive sections in the library. During a visit, the student must choose exactly one book from one of these sections and leave the library. Each pass can be used only once.

At the moment Alessia and Bernardo have $ n $ passes of lengths $ x_1, \, x_2, \, \dots, \, x_n $ . They have different opinions on the best way to improve: Alessia thinks that it is important to study many different topics, while Bernardo believes that it is important to study deeply at least one topic. So, Alessia wants to use the $ n $ passes to get $ n $ books on distinct topics, while Bernardo would like to get at least two books on the same topic.

They have reached the following agreement: for each of the following $ n $ days, Alessia will choose a pass of length $ y $ among those which are still available and an interval of $ y $ sections in the library, and Bernardo will go into the library and will take exactly one book from one of those sections.

Can Bernardo manage to get at least two books on the same subject, or will Alessia be able to avoid it?

You should decide whether you want to be Alessia or Bernardo, and you have to fulfill the goal of your chosen character. The judge will impersonate the other character. Note that, even if at some moment Bernardo has already taken two books on the same subject, the interaction should go on until the end of the $ n $ days.

## 说明/提示

In the first sample, it can be shown that Alessia can accomplish her goal. An example of interaction (after reading the input) follows:

$$ 
\begin{array}{|c|c|c|} 
\hline \textbf{Contestant} & \textbf{Judge} & \textbf{Explanation} \\
\hline \texttt{Alessia} & & \text{The program will act as Alessia} \\ 
\hline 3 \quad 11 & & \text{Choose $y = 3$ and $a = 11$} \\ 
\hline & 13 & \text{Judge selects $b = 13$} \\ 
\hline 10 \quad 2 & & \text{Choose $y = 10$ and $a = 2$} \\ 
\hline & 9 & \text{Judge selects $b = 9$} \\ 
\hline 7 \quad 1 & & \text{Choose $y = 7$ and $a = 1$} \\ 
\hline & 4 & \text{Judge selects $b = 4$} \\ 
\hline 2 \quad 10 & & \text{Choose $y = 2$ and $a = 10$} \\ 
\hline & 10 & \text{Judge selects $b = 10$} \\ 
\hline 3 \quad 6 & & \text{Choose $y = 3$ and $a = 6$} \\ 
\hline & 7 & \text{Judge selects $b = 7$} \\ 
\hline \end{array}
$$
The program of the contestant wins because all the books chosen by Bernardo pertain to different topics. The actions performed by the contestant and the judge in this example of interaction may be non-optimal.

In the **second sample**, it can be shown that Bernardo can manage to fulfil his goal. An example of interaction (after reading the input) follows: 

$$  \begin{array}{|c|c|c|} \hline \textbf{Contestant} & \textbf{Judge} & \textbf{Explanation} \\ \hline \texttt{Bernardo} & & \text{The program will act as Bernardo} \\ \hline & 4 \quad 1 & \text{Judge chooses $y = 4$ and $a = 1$} \\ \hline 4 & & \text{Select $b = 4$} \\ \hline & 1 \quad 10 & \text{Judge chooses $y = 1$ and $a = 10$} \\ \hline 10 & & \text{Select $b = 10$} \\ \hline & 6 \quad 3 & \text{Judge chooses $y = 6$ and $a = 3$} \\ \hline 4 & & \text{Select $b = 4$} \\ \hline & 4 \quad 5 & \text{Judge chooses $y = 4$ and $a = 5$} \\ \hline 8 & & \text{Select $b = 8$} \\ \hline \end{array}  $$

The program of the contestant wins because Bernardo has selected two books on topic number  $ 4$. The actions performed by the contestant and the judge in this example of interaction may be non-optimal.

## 样例 #1

### 输入

```
5 14
3 7 2 3 10```

### 输出

```
-```

## 样例 #2

### 输入

```
4 10
4 1 6 4```

### 输出

```
-```

# 题解

## 作者：CYZZ (赞：7)

# [Library game](https://www.luogu.com.cn/problem/CF1776C)
膜拜 pb 大师 orz。
## 思路
先考虑 A 和 B 各自的最优策略。

- 对于 A，最优策略很简单，就是从左往右能放就放。此外，放更长的区间不会使答案更劣，所以我们可以把每个区间从长到短排序。
- 对于 B，B 希望卡到某一个时刻 A 放不进去。设 B 想让 A 放不进区间 $p$，则 B 的最优策略为每隔 $a_p$ 拿一个，也就是拿走 $a_p$ 的倍数，这样就可以确保区间 $p$ 放不进去。

最优策略确定了，考虑如何快速确定胜负情况，这取决于 B 选择的区间 $p$。通过手玩（抽屉原理可证）可以发现，如果满足 $\exists a_i > \lfloor \frac{m}{i} \rfloor$，则 B 必胜。如果没有，则 A 必胜。（注意这里的 $a$ 数组是排过序的）

交互时，对于 B，如果 A 选择的区间长度大于 $a_p$，输出包含在内的 $a_p$ 的倍数。否则随便选一个输出。

确定了胜负，剩下的直接按最优策略和交互库交互即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p,a[105],bk[5005];
bool cmp(int x,int y)
{
    return x>y;
}
void solve_A()
{
    printf("Alessia\n");
    fflush(stdout);
    memset(bk,0,sizeof bk);
    for(int i=1;i<=n;i++)
    {
        int l=1,x;
        for(int r=1;r<=m;r++)
        {
            if(bk[r])//被B拿走了
                l=r+1;
            else if(r-l+1==a[i])//能放进去
            {
                printf("%d %d\n",a[i],l);
                fflush(stdout);
                break;
            }
        }
        scanf("%d",&x);
        bk[x]=1;
    }
}
void solve_B()
{
    printf("Bernardo\n");
    fflush(stdout);
    for(int i=1;i<=n;i++)
    {
        int len,l;
        scanf("%d%d",&len,&l);
        if(a[p]<=len)
            printf("%d\n",(l+a[p]-1)/a[p]*a[p]);//求区间内a[p]的倍数
        else
            printf("%d\n",l);//随便输出一个
        fflush(stdout);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(a[i]>(m/i))//此时B必胜
        {
            p=i;
            break;
        }
    }
    if(!p)
        solve_A();
    else
        solve_B();
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：赵悦岑 (赞：3)

[访问博客获得更好的阅读体验](https://2745518585.github.io/post/CF1776C-solution/)

### 题意

有一个长度为 $m$ 的序列，以及大小为 $n$ 的可重集。两个人依次进行操作：先手在可重集中选择一个数 $L$，再在序列上选择一段长度为 $L$ 的区间，满足区间内的所有位置均未被标记，然后从可重集重删除 $L$；后手在先手上一次选择的区间中选择一个位置并进行标记。如果先手无法选择一个合法的区间则失败，把可重集删完则获胜，求最终谁会获胜，并与交互库模拟这个过程。

### 解法

先考虑先手如何操作。我们可以考虑一个贪心策略，把区间长度从大到小排序，每次尝试放置最长的区间，并找到可以放置的间隔最小的两个标记位置中间放置。

考虑后手。后手进行标记的最终目的是让对方有一个区间放不进去，我们可以枚举这个区间的长度 $x$，显然在 $x$ 的倍数位置标记是最优方案。如果当前先手选的区间包含了 $x$ 的整数倍位置，那么就标记这个位置，否则这个区间长度小于 $x$，任意放置。

我们可以发现能标记 $x$ 整数倍位置的个数就是已选择区间中长度大于 $x$ 的区间个数，而使得长度大于等于 $x$ 的区间无法放置至少需要标记 $\lfloor \frac{m}{x} \rfloor$ 个，所以只需要判断长度大于等于 $x$ 的区间个数即可。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,m,t,a[N];
bool h[N];
int solve()
{
    sort(a+1,a+m+1);
    for(int i=1;i<=m;++i)
    {
        if(n/a[i]<=m-i)
        {
            t=a[i];
            return 1;
        }
    }
    return 0;
}
pair<int,int> solve1(int p)
{
    h[p]=true;
    int x=0,y=1e9,z=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i])
        {
            if(z>=a[m]&&z<y) x=i-z,y=z;
            z=0;
        }
        else ++z;
    }
    if(z>=a[m]&&z<y-x+1) x=n-z+1,y=z;
    --m;
    return make_pair(x,x+a[m+1]-1);
}
int solve2(pair<int,int> z)
{
    --m;
    int x=z.first,y=z.second;
    if(y-x+1<t) return x;
    for(int i=x;i<=y;++i)
    {
        if(i%t==0) return i;
    }
    return x;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
    }
    if(solve()==0)
    {
        printf("Alessia\n");
        fflush(stdout);
        pair<int,int> z=solve1(0);
        printf("%d %d\n",z.second-z.first+1,z.first);
        fflush(stdout);
        while(m)
        {
            int x;
            scanf("%d",&x);
            pair<int,int> z=solve1(x);
            printf("%d %d\n",z.second-z.first+1,z.first);
            fflush(stdout);
        }
    }
    else
    {
        printf("Bernardo\n");
        fflush(stdout);
        while(m)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",solve2(make_pair(y,y+x-1)));
            fflush(stdout);
        }
    }
    return 0;
}
```





---

## 作者：EuphoricStar (赞：3)

orz p_b_p_b。

下文令 $a_i$ 为原题面中的 $x_i$。

拿到题目无从下手，不妨简化一下。

考虑 $n = 2$ 怎么做。不妨设 $a_1 \ge a_2$。发现若 $a_2 \le \left\lfloor\frac{m}{2}\right\rfloor$ 时 A 必胜，否则 B 必胜。

于是我们大胆猜测结论是将 $a$ 从大到小排序后，$\forall i \in [2, n], a_i \le \left\lfloor\frac{m}{i}\right\rfloor$ 时 A 必胜，否则 B 必胜。

证明是容易的。根据抽屉原理，第 $i$ 轮开始前不包含选过的元素的极长连续段长度的最大值最小是 $\left\lceil\frac{m - i + 1}{i}\right\rceil = \left\lfloor\frac{m}{i}\right\rfloor$。因此：

- 如果不满足 $\forall i \in [2, n], a_i \le \left\lfloor\frac{m}{i}\right\rfloor$，设 $p$ 为使得 $a_p > \left\lfloor\frac{m}{i}\right\rfloor$ 的位置，那么 A 选择长度 $\ge a_p$ 的区间时，Bob 一定可以在这个区间内找到 $[1, m]$ 的 $a_p$ 等分点（即 $a_p \mid x$ 的点），这样 A 选完 $[1, p]$ 的区间后，B 一定能获胜。
- 否则，第 $i$ 轮 A 随便选一个长度 $= a_i$ 的未被覆盖的区间即可。因为满足 $\forall i \in [2, n], a_i \le \left\lfloor\frac{m}{i}\right\rfloor$，所以第 $i$ 轮一定存在一个长度 $= a_i$ 的未被覆盖的区间。

交互就直接按上面模拟即可。

[code](https://codeforces.com/problemset/submission/1776/215152749)

---

## 作者：Wu_Qi_Tengteng (赞：1)

首先对于 $A$，它的最优策略一定是把区间从大到小排序，然后从左往右能放就放。
证明：
1. 首先合着放肯定不劣。假设我合在一起放最终导致被限制上了，那么即使我分开放了还是会被限制。
2. 从左往右放显然也是不劣的。因为这样可以让我们右边的区间尽可能大。即使我是从中间某一部分开始，如果最终按照我从左往右放的情况都被限制了，中间放的更会被限制。
3. 先放最大的显然不劣。因为到后面显然会越来越密集，我先放大的肯定不劣。如果我先放大的导致后面被限制了，那我先放小的后面更被限制。

对于 $B$ 的策略就没那么显然了。我们可以枚举这个区间 $p$，表示最终我们不想让 $p$ 这个区间放进去。$p$ 的长度为 $a_p$ 。如果我们不想让 $p$ 放进去，最优策略就是每隔 $a_p$ 个拿一个（因为 $A$ 会让你尽量隔开）。如果长度大于等于 $a_p$ 的区间的数量 $-1$ 大于等于 $\lfloor\frac{m}{a_p}\rfloor$，那么显然必胜，否则就限制不了 $a_p$。假设不满足这个条件仍然获胜了，那么只能是因为有一个更小的区间满足了条件。所以当区间中存在 $a_p$ 的倍数的时候我们就放，否则就随便放。

总的来说，判断一下哪个必胜，模拟对局就可以了。

时间复杂度 $\mathcal{O}(nm)$。
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1005,M=5005;
int n,m,a[N],nxt[M];
void solveA(){
	cout<<"Alessia"<<endl;
	nxt[0]=m+1;
	for(int i=1;i<=n;i++){
		int j=0;
		while(nxt[j]-j-1<a[i])j=nxt[j];
		cout<<a[i]<<" "<<j+1<<endl;
		int x;
		cin>>x;
		nxt[x]=nxt[j];
		nxt[j]=x;
	}
}
bool vis[N];
void solveB(int p){
	cout<<"Bernardo"<<endl;
	for(int i=1;i<=n;i++){
		int len,x;
		cin>>len>>x;
		bool fl=0;
		for(int j=x;j<=x+len-1;j++){
			if(vis[j]){
				cout<<j<<endl;
				fl=1;
				break;
			}
		}
		if(fl)continue;
		if(len>=p){
			int u=p*((x-1)/p+1);
			vis[u]=1;
			cout<<u<<endl; 
		}else{
			vis[x]=1;
			cout<<x<<endl;
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,[&](int x,int y){return x>y;});
	for(int i=n;i>0;i--){
		if(i-1>=m/a[i]){
			solveB(a[i]);
			return 0;
		}	
	}
	solveA();
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
不难的好玩题。

摘自 [交互、构造、博弈](https://www.luogu.com.cn/training/676672)。
## 思路分析
考虑什么时候策略最优。

对于 Alessia 来说，肯定是能放就放最优。

那不同大小的区间而言，肯定也是从大到小放优秀。

因为大的区间被取了之后可能还能塞下小的区间，而小的区间一定不能把大区间塞进去。

所以我们直接从大区间往小区间暴力塞就行了。

然后来考虑 Bernardo。

对于 Bernardo 肯定是考虑在某一步让一个长度为 $x$ 的区间塞不进去。

那么最优的策略肯定是每隔 $x$ 长度抽掉一本书，这样长度为 $x$ 的就塞不进去了。

但这个 $x$ 是 Bernardo 最开始钦定的，要是中途更换肯定会变得更劣，所以我们要做的就是尝试对于每一种 $x$ check 能不能卡掉。

我们发现，只有长度 $len\ge x$ 时，才必然会包含我们要卡掉的断点。

所以说设 $n$ 为满足 $len\ge x$ 的区间个数，当且仅当 $n\cdot x>m$ 时才能卡住。

剩下来就是构造策略的问题了。

对于 Bernardo 而言，能卡断点则卡断点，否则随意。

对于 Alessia 而言，从大区间到小区间，从前往后，能塞就塞。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=5e5+10,M=5e3+10,V=5e5,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,m,a[N],mp[N],s[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	// #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void solve()
{
	n=read(),m=read();for(int i=1;i<=n;i++) a[i]=read();sort(a+1,a+1+n);
	for(int i=n;i>=1;i--) if((n-i+1)*a[i]>m)
	{
		cout<<"Bernardo"<<endl;
		for(int j=1,x,y;j<=n;j++)
		{
			x=read(),y=read();
			if(x>=a[i]) cout<<(y+a[i]-1)/a[i]*a[i]<<endl;
			else cout<<y<<endl;
		}return;
	}cout<<"Alessia"<<endl;
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j+a[i]-1<=m;j++) if(s[j+a[i]-1]==s[j-1])
			{cout<<a[i]<<" "<<j<<endl;break;}
		mp[read()]=1;for(int j=1;j<=m;j++) s[j]=s[j-1]+mp[j];
	}
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

