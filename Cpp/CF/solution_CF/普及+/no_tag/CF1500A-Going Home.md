# Going Home

## 题目描述

It was the third month of remote learning, Nastya got sick of staying at dormitory, so she decided to return to her hometown. In order to make her trip more entertaining, one of Nastya's friend presented her an integer array $ a $ .

Several hours after starting her journey home Nastya remembered about the present. To entertain herself she decided to check, are there four different indices $ x, y, z, w $ such that $ a_x + a_y = a_z + a_w $ .

Her train has already arrived the destination, but she still hasn't found the answer. Can you help her unravel the mystery?

## 说明/提示

In the first example $ a_2 + a_3 = 1 + 5 = 2 + 4 = a_1 + a_6 $ . Note that there are other answer, for example, 2 3 4 6.

In the second example, we can't choose four indices. The answer 1 2 2 3 is wrong, because indices should be different, despite that $ a_1 + a_2 = 1 + 3 = 3 + 1 = a_2 + a_3 $

## 样例 #1

### 输入

```
6
2 1 5 2 7 4```

### 输出

```
YES
2 3 1 6```

## 样例 #2

### 输入

```
5
1 3 1 9 20```

### 输出

```
NO```

# 题解

## 作者：TonyYin (赞：11)

这题 cf 考场上好像就只有不到2000人A掉……

## 题意

给定 $n$ 个正整数 $a_1, a_2\cdots, a_n$，求出任意一组 $x\neq y\neq z\neq w$ 使得 $a_x+a_y=a_z+a_w$.

$n\leq 2\times 10^5, 1\leq a_i\leq 2.5\times 10^6$.

## 分析

首先考虑暴力，我们开一个 $2a_i\leq 5\times 10^6$ 大小的桶，记录已经找到的和，然后 $\mathcal{O}(n^2)$ 地暴力枚举，直到桶中有元素出现过 $\geq1$ 次，并且满足 $x, y, z, w$ 互不相同即可。

又考虑到这只是 `div2.` 的 `C` 题，在这个数据范围上的 $\mathcal{O}(n\log n)$ 做法经过尝试后都行不通。

赛后，我们才知道：非常不幸，这题是结论题。

**结论：上面的暴力做法的时间复杂度为：$\mathcal{O}(\min(n^2, n+C))$，$C$ 为 $a_i+a_j$ 的值域。**

## 证明

首先，如果我们找到了四组**两两不完全相同**的 $(x_i, y_i)$，使得：
$$
a_{x_1}+a_{y_1}=a_{x_2}+a_{y_2}=a_{x_3}+a_{y_3}=a_{x_4}+a_{y_4}
$$
那么就可以找到满足条件的 $x,y, z, w$ 了。

这个结论是非常自然的，简单分类讨论就可以证明。对四个数对中，有多少个 $a_x$ 相同进行讨论：

1. 如果有四个数对的 $a_{x_i}$ 相同，那么 $a_{y_1}=a_{y_2}=a_{y_3}=a_{y_4}$，所以 $y_1, y_2, y_3, y_4$ 是可行的解。
2. 如果有三个数对的 $a_{x_i}$ 相同，不妨设 $a_{x_4}$ 与另外三个数不同，那么 $(x_4, y_4), (x_1, y_1)$ 就是一组可行解。
3. 对于其他情况，显然能找到满足题意的 $x, y, z, w$.

因此，我们只需要用 $\mathcal{O}(n^2)$ 的暴力做法，**最差情况是：所输出的答案的 $sum$ 值出现四次。**

所有 $sum$ 的可能值只有 $5\times 10^6$ 种，根据抽屉原理，程序复杂度不超过 $2\times 10^7$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10, MAXC = 2e6 + 5e5 + 10;
int n;
int x[MAXC << 1], y[MAXC << 1];
int a[MAXN], cnt[MAXC << 1];
bool have_ans;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(cnt[a[i] + a[j]]) {
				if(x[a[i] + a[j]] != i && y[a[i] + a[j]] != i 
                && x[a[i] + a[j]] != j && y[a[i] + a[j]] != j) {
					cout << "YES" << endl << i << " " << j << " " << x[a[i] + a[j]] << " " << y[a[i] + a[j]] << endl;
					return 0;
				}
			} else {
				cnt[a[i] + a[j]]++;
				x[a[i] + a[j]] = i; y[a[i] + a[j]] = j;
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
```

---

## 作者：Blunt_Feeling (赞：9)

## CF1500A Going Home 题解

庆祝 $\texttt{Codeforces}$ 第 1.5k 场比赛！

这是一道挺玄学的题目，比赛时想了半个小时，打了 15 分钟，出人意料地 AC 了。

为什么说它玄学？主要是它的数据范围太大了。作为一道在茫茫数海中找 $4$ 个数的题目，根据这四个数要满足的条件：$a+b=c+d$，不难想到把数的和进行哈希。我们可以 $O(n^2)$ 遍历所有数，把两两数之和 Hash 到一个`map`中，这之后一旦找到另外的两个数，满足这另外两个数的和已经在`map`中出现过，就直接输出。但是我们的 $n$ 有 $2\times 10^5$，而时限只有 $2$ 秒，这肯定是跑不完的。所以比赛时，我在代码中加入了一个统计查找次数的变量`times`，一旦`times`超过某一个人为设定的较大的值，即认为找不到解，输出 NO。

比赛结束后，仔细一想，其实这个判断是没有必要的。可以给出分析：

因为每个数 $a_i$ 都是小于等于 $2.5\times 10^6$ 的，所以其两两相加产生的不同的和最多不会超过 $5\times 10^6$。而我 $i$ 和 $j$ 遍历到的数字对会有 $4\times 10^{10}$ 个，根据鸽巢原理（又名“鸽笼原理”“抽屉原理”），定会有很多个值是重复的。在实际遍历的过程中，虽然遍历不到 $4\times 10^{10}$ 对，但是 $2$ 秒钟内几千万对还是有的。所以在可遍历的范围内，一定能得出是否有解。

另外，`STL`中`map`的速度是 $\log$ 级别的，可能会比较慢，所以用数组代替`map`进行哈希。

### Code

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
const int maxn=200050;
int n;
struct ee{
	int b,p;
}a[maxn];
struct Node{ //哈希用的桶
	int a,b;
}mp[5200000];
bool cmp(ee x,ee y) {
	return x.b<y.b;
}
int main()
{
	n=read();
	For(i,1,n) a[i].b=read(),a[i].p=i;
	sort(a+1,a+n+1,cmp);
	For(i,1,n-1)
	{
		For(j,i+1,n)
		{
			int s=a[i].b+a[j].b;
			if(mp[s].a&&mp[s].a!=i&&mp[s].a!=j&&mp[s].b!=i&&mp[s].b!=j)
			{ //不能重复使用数字
				printf("YES\n%d %d %d %d\n",a[mp[s].a].p,a[mp[s].b].p,a[i].p,a[j].p);
				return 0;
			}
			else mp[s].a=i,mp[s].b=j;
		}
	}
	puts("NO"); //只有遍历完还没有找到解时才输出NO
	return 0;
}
```
感谢管理员对本题解的指正！

---

## 作者：Schwarzkopf_Henkal (赞：4)

发现这是个神秘结论/乱搞题。

首先考虑，如果找到了四组**不完全相同**的二元组 $(x_i,y_i)$ 使得他们在 $a$ 序列上对应的值的和相等则一定存在至少一个符合条件的四元组即答案。证明：

当对于四个**无序**二元组都存在 $x_i$ 使得 $x_1=x_2=x_3=x_4$ 时，一定有 $a_{y_1}=a_{y_2}=a_{y_3}=a_{y_4}$，但 $y_1,y_2,y_3,y_4$ 各不相同，于是 $(y1,y2,y3,y4)$ 合法。

剩下的情况，一定存在一对完全不相同的二元组。

这样做的话，根据鸽巢原理我们能够在 $\text O(\min(n^2,C))$ 的时间复杂度内得到答案。

```cpp
#include<bits/stdc++.h>
#include <utility>
using namespace std;
int n,a[200005];
vector<pair<int,int> >c[5000005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int cur=a[i]+a[j];
            for(int k=0;k<c[cur].size();k++)
                if(c[cur][k].first!=i&&c[cur][k].first!=j&&c[cur][k].second!=i&&c[cur][k].second!=j){
                    cout<<"YES\n"<<i<<" "<<j<<" "<<c[cur][k].first<<" "<<c[cur][k].second<<'\n';
                    return 0;
                }
            c[cur].push_back(make_pair(i,j));
            if(c[cur].size()>=4){
                for(int k=1;k<=3;k++){
                    if(c[cur][k].first!=c[cur][0].first&&c[cur][k].second!=c[cur][0].first)
                        goto Karkov;
                    if(c[cur][k].first!=c[cur][0].first)
                        swap(c[cur][k].first,c[cur][k].second);
                }
                cout<<"YES\n"<<c[cur][0].second<<" "<<c[cur][1].second<<" "<<c[cur][2].second<<" "<<c[cur][3].second;
                return 0;
                Karkov:;
                swap(c[cur][0].first,c[cur][0].second);
                for(int k=1;k<=3;k++){
                    if(c[cur][k].first!=c[cur][0].first&&c[cur][k].second!=c[cur][0].first)
                        goto Karfka;
                    if(c[cur][k].first!=c[cur][0].first)
                        swap(c[cur][k].first,c[cur][k].second);
                }
                cout<<"YES\n"<<c[cur][0].second<<" "<<c[cur][1].second<<" "<<c[cur][2].second<<" "<<c[cur][3].second;
                return 0;
                Karfka:;
            }
        }
    }
    cout<<"NO";
}/*
竟然是个乱搞/结论题？？？

*/
```

goto 是好文明！！！！

---

## 作者：tommymio (赞：3)

暴力枚举就可以了（我比赛时弄了 $\text{1h}$ 双指针做法直接豹毙

具体来说就是枚举所有对 $x,y$，如果发现一对可以就退出循环。

下面让我们证明一下这种做法的正确性，它的时间复杂度是 $O(\min(n^2,n+C)$ 的，而不是 $O(n^2)$，其中 $C$ 是值域。因为一个 $a_x+a_y$ 在 $x$ 相同时最多只能计入 $3$ 个 $y$，因为计入更多 $y$，$y$ 就能够通过两两配对找到一组解。而根据广义鸽巢原理，在 $\frac{n(n-1)}{2}\geq C$ 时存在一个权值，至少存在 $\lfloor\frac{n(n-1)}{2C}\rfloor\geq 1$ 组 $a_x+a_y$。于是证毕。

```cpp
#include<cstdio>
#include<utility>
int a[200005];
std::pair<int,int> res[5000005];  
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	int n=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<=n;++i) {
		for(register int j=i+1;j<=n;++j) {
			int sum=a[i]+a[j];
			if(res[sum].first==0||res[sum].second==0) {
				res[sum].first=i; res[sum].second=j;
			}
			else if(res[sum].first!=i&&res[sum].second!=j&&res[sum].first!=j&&res[sum].second!=i) {
				printf("YES\n");
				printf("%d %d %d %d\n",res[sum].first,res[sum].second,i,j);
				return 0;
			}
		}
	} 
	printf("NO\n");
	return 0;
}
```

---

## 作者：dalao_see_me (赞：2)

## 题目大意
~~这题题意这么明显就不需要了吧~~ 在 $1$ 到 $n$ 中找出四个不相等的整数 $x,y,z,w$，使得 $a_x+a_y=a_z+a_w$。
## 做法
显然我们有一个 $n^4$ 的暴力，每次枚举 $x,y,z,w$ 计算和就可以了。

我们考虑对其进行优化。

看一下数据范围：$a_i\le2.5\times10^6$，可以得到$2a_i\le5\times10^6$。是不是可以开个桶维护一下已经找到的和呢？

这样我们就把暴力优化到了 $n^2$。理论上还是会T，但是它最多会跑 $5\times10^6$。

为什么呢？

显然桶的大小开 $5\times10^6$ 就够了。那么，根据抽屉原理（即鸽巢原理），如果跑的次数比 $5\times10^6$ 多了，一定会有一个抽屉使用了两次。使用了两次就代表了有解。

所以时间是 $min(n^2,n+C)$，$C$是值域。

那为什么时间要在 $C$ 的基础上加上 $n$ 呢？

是因为要等到次数跑到了 $C$ 以后，第二重循环 $j$ 变量还要跑到 $n$。

## Code time
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=5e6+6;
int n,cnt;
int a[N];
struct Node{//桶
	int flag,x,y;
}b[M];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++){
			int s=a[i]+a[j];
			if(!b[s].flag){//当桶中没有s这个值的时候
				b[s].x=i;
				b[s].y=j;
				b[s].flag=1;
			}
			else if(i!=b[s].x&&i!=b[s].y&&j!=b[s].x&&j!=b[s].y)return printf("YES\n%d %d %d %d",i,j,b[s].x,b[s].y),0;//当桶中出现了s且上一次出现的i j和现在的i j不相同时，输出并结束程序
		}
	return puts("NO"),0;
}
```


---

## 作者：snnu_lgw (赞：1)

### Description

在一个$array$ $a$ 中是否存在四个不同的下标$x,y,z,w$，使得$a_x+a_y=a_z+a_w$

### Solution

不妨设$sum=a[i]+a[j],1\le i,j \le n,i \ne j$，对于一个长度为$n$的$array$ $a$，从中可以选出$\frac {n*(n-1)}2$个$sum$，当然里面可能有相同的

观察数据范围可以看出，$n$最大值为$2e5$，$a[i]$最大值为$2.5e6$，则$sum \in [2,5000000]$

如果  $\frac {n*(n-1)}2 >5000000$，那么必然存在至少两个相同的$sum$

因此可以直接枚举$\frac {n*(n-1)}2$这么多个$sum$，如果出现相同的，则直接输出即可，时间复杂度为$O(min(n^2,n+c))$~~（详见Editorial）~~因为最多枚举到$5e6$个就会终止，所以其实一定不会超时

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e6+10;

struct Node{
	int x,y;
}p[maxn];

int n, a[200000+10];

int main()
{	
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n-1;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			int sum = a[i] + a[j];
			if(p[sum].x==0 || p[sum].y==0)
			{
				p[sum].x = i;
				p[sum].y = j;
			}
			else
			{
				if(p[sum].x!=i && p[sum].y!=i && p[sum].x!=j && p[sum].y!=j)
				{
					printf("YES\n");
					printf("%d %d %d %d",p[sum].x,p[sum].y,i,j);
					return 0;
				}
			}
		}
	}
	cout<<"NO";
	return 0;
}

```



---

## 作者：Umbrella_Leaf (赞：1)

十分简单的一道题。

> 给出一列数 $a$ ，求是否存在 $x,y,z,w$ 使得 $a_x+a_y=a_z+a_w$ ，并且输出方案。

首先我们 $O(n^4)$ 的暴力肯定是没问题的对吧。

然后我们也可以想出 $O(n^3+C)$ 的做法，具体就是拿个桶记录一下每个数然后暴力枚举三个找剩下一个，这里 $C$ 是值域 $2.5\times 10^6$ 。

按照桶的思路可以想出 $O(n^2)$ 的做法，即枚举 $x$ 和 $y$ ，记一下他们的和是否出现过然后判一判重复就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int n;
pair<int,int> box[5000005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(box[a[i]+a[j]].first){
				if(box[a[i]+a[j]].first!=i&&box[a[i]+a[j]].second!=j&&box[a[i]+a[j]].second!=i){
					puts("YES");
					printf("%d %d %d %d\n",box[a[i]+a[j]].first,box[a[i]+a[j]].second,i,j);
					return 0;
				}
			}else box[a[i]+a[j]]=make_pair(i,j);
	puts("NO");
	return 0;
}
```
这个代码是可以过的，但是为什么呢？

首先我们大致估计一个范围 $n\le 5000$，那么肯定是可以暴力的。

然后 $n\ge 5000$ 的情况呢我们就用抽屉原理，这里 $a_x+a_y$ 的和至少 $\dfrac{5000\times 4999}{2}$ 个，显然肯定有重复，那么就存在答案了。

但是这个分析没有考虑相同数的情况，这里我们想一下，一个 $a_x$ 最多带三个 $a_y$ 对不对，因为有四个的话就可以两两配对有答案了。

现在重复数的情况复杂度也有保证了，两种情况合并一下总复杂度应该是 $O(\min(n^2,n+C))$。

显然可过。

---

## 作者：清烛 (赞：0)

[My Blog](https://imyangty.com/oi/1327)

## 题意
给定 $\lbrace a_n\rbrace$，满足 $4\le n\le 2\times10^5$ 并且 $\forall i\in[1,n],1\le a_i\le 2.5\times10^6$，求四个不同的下标 $x,y,z,w$ 使得 $a_x + a_y = a_z + a_w$。

有解则打印解，无解输出 $\texttt{NO}$

## 题解
注意到我们的和 $a_i + a_j\le 5\times 10^6$，这个是解决问题的关键。

所以我们直接大力枚举 $S = a_i + a_j$，记录一下加出来的这个 $S$，如果同样的 $S$ 出现了第二次则直接输出答案就好。根据鸽巢原理，我们如果枚举的次数超过了值域，那么就肯定不存在解。

实际上提交了会发现这个上界根本就跑不满，最大的一个点约 40ms，很快。

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 2e5 + 5, maxs = 5e6 + 5;

struct node
{
    int id, val;
    bool operator<(const node &b) const
    {
        if (val == b.val) return id < b.id;
        else return val < b.val;
    }
} a[maxn], ans[maxs];

int n;

int main()
{
    n = read();
    FOR(i, 1, n) a[i].val = read(), a[i].id = i;
    std::sort(a + 1, a + n + 1);
    int cnt = 0;
    FOR(i, 1, n)
        FOR(j, i + 1, n)
        {
            int s = a[i].val + a[j].val;
            if (ans[s].id + ans[s].val && ans[s].id != a[i].id && ans[s].id != a[j].id && ans[s].val != a[i].id && ans[s].val != a[j].id)
            {
                printf("YES\n%d %d %d %d", a[i].id, a[j].id, ans[s].id, ans[s].val);
                return 0;
            }
            else if (!ans[s].id)
                ans[s].id = a[i].id, ans[s].val = a[j].id, ++cnt;
            if (cnt >= 5e6)
            {
                puts("NO");
                return 0;
            }
        }
    puts("NO");
    return 0;
}
```

---

## 作者：houpingze (赞：0)

~~知识点：乱搞~~

我们就开个结构体类型的桶，然后枚举两个数的和，每次都丢进桶里（下标也要），然后如果桶里已经有数字了，就代表这几个可以组成 $a_i+a_j=a_k+a_l$ 了，直接输出即可

注意！ $i,j,k,l$ 互不相同！

这样理论是$O(n^2)$的，但实际完全跑不满，故可以通过。

---

