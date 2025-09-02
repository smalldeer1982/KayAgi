# [BalticOI 2007] Sequence 序列问题

## 题目描述

对于一个给定的序列 $a _ 1, \cdots, a _ n$，我们对它进行一个操作 $\text{reduce}(i)$，该操作将数列中的元素 $a _ i$ 和 $a _ {i+1}$ 用一个元素 $\max(a _ i,a _ {i+1})$ 替代，这样得到一个比原来序列短的新序列。这一操作的代价是 $\max(a _ i,a _ {i+1})$。进行 $n-1$ 次该操作后，可以得到一个长度为 $1$ 的序列。

我们的任务是计算代价最小的 $\text{reduce}$ 操作步骤，将给定的序列变成长度为 $1$ 的序列。

## 说明/提示

### 数据规模与约定

- 对于 $30\%$ 的测试数据，$n\le 500$； 
- 对于 $50\%$ 的测试数据，$n \le 20000$；
- 对于 $100\%$ 的测试数据，$1 \le n \le 10^6$，$0 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
5```

# 题解

## 作者：顾淼_ (赞：44)

~~给没想通贪心的~~

先上超简洁代码
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
long long ans, a[1000100];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 1; i < n; i++){
        ans += max(a[i - 1], a[i]);
    }
    cout << ans;
}
```

刚做这道题的时候没看出来是贪心

~~蒟蒻啊蒟蒻~~


时隔这么久，跟机房小伙伴回顾这道题

终于（他）得到了一个比较满意的解释

~~我太菜了，解释老有漏洞~~

“把图呈上来！”~~假装画外音~~

-----=_=废话分割线------------


![](https://cdn.luogu.com.cn/upload/pic/39455.png)


事实上每个数最多只可能被有效加两次（~~想一想，为什么~~）

合并一次后被另一个数合并，或者两边的数都比他小（如图a3）

而看每一边的情况

当一边的数都比a[i]小，最终一定会使a[i]被加一次，如果如图中a3，一侧有a1比a3大，显然在加上a1前会先和a3合并使得结果更优

另一边同理



---

## 作者：zhy137036 (赞：18)

这道题需要先用分治的思路找规律，找到规律这道题就特别简单了。
我们先来看一个例子：

![](https://cdn.luogu.com.cn/upload/pic/66728.png )

## 思路
很明显，要把n个数合并成一个数，需要合并n-1次

我们要让代价尽可能的小，
最大的第5个数就应该尽可能少的和别的数合并。

由于第5个数不可避免的要和左右两边的数各合并一次，所以第5个数至少被计算2次，那我们就让它只合并两次。

要让它只合并两次，就要先合并左边的4个数，再合并右边的3个数，最后和第5个数合并。

接下来我们分治地合并左右两个子区间，下面举出几个数的例子，大家找找规律：

作为左边4个数中最大的数，第2个数也要被计算2次，但第8个数因为右边没有数了，就只用计算1次，而第4个数是夹在第2个数和第5个数之间这个区间最大的数，它只用在和第3个数合并时计算1次，而最小的第6个数合并时不会被计算。

找到规律了吗，规律就是**一个数被计算的次数就是它两边紧挨着的比它小的数的个数**，看看是不是这样。

找到了这个规律，一个蓝题就变成了一个红题了。

### 2019/10/5 update

感谢@[暮光闪闪](https://www.luogu.org/user/19811)提醒：

如果相邻两数相等，仍然必须选出一个较大的数，比如选择左边为较大的数。如果判断时一个数右边的数等于该数于那么该数应计算，而它的左边等于时就不应计算。

## 代码：
```cpp
#include<iostream>
using namespace std;
long long a[1000005];//每个数的值
int main(void)
{
    long long n,ans=0;//n表示数的数量，ans是代价
    cin>>n;//输入数的个数
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];//整个程序大部分时间都花在这步上了qwq
    }
    for(int i=1;i<=n;i++)//枚举每个数
    {
        if(i>1&&a[i-1]<a[i])//如果左边小于它
        {
            ans+=a[i];
        }
        if(i<n&&a[i+1]<=a[i])//如果右边小于等于它
        {
            ans+=a[i];
        }
    }
    cout<<ans<<endl;//输出
    return 0;
}
```

---

## 作者：Yukhoi (赞：7)

### 模拟即可

~~为广大跟我一样看不懂那篇线段树题解的蒟蒻们献上简明代码福音~~

## O(n)思路如下：

首先我们知道，不管如何操作，每次操作必然会减少一个数，最后一次操作所需价值必然是所有数据中最大的那个数，那么既然无论如何都会有这个结果，从头到尾扫一遍，将前后较大的数与答案累加（代码实现如下）
```cpp
for(int i=1; i<=n; ++i) {
	if(a[i]>a[i-1]&&i!=1) ans+=a[i];
	if(a[i]>=a[i+1]&&i!=n) ans+=a[i];
    //前一个if不用等号是为了避免重复，自己想想就知道是怎么回事了
}
```
然后，再在这核心代码前后，加上各种头文件、读优、输优等~~看起来牛逼用起来舒适便捷的~~模板和数据读入的循环、main函数的格式~~（白痴都知道）~~即可。

完整代码如下：
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cctype>
#define ll long long
using namespace std;

ll n,a[1000005],ans;

inline ll read() {
	ll X=0,w=0;
	char ch=0;
	while(!isdigit(ch))
		w|=ch=='-',ch=getchar();
	while(isdigit(ch))
		X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
	return w?-X:X;
}

inline void write(ll x) {
	ll num=0;
	char ch[20];
	if (!x) ch[++num]='0';
	while(x) ch[++num]=(x%10)+48,x/=10;
	while(num) putchar(ch[num--]);
	puts("");
}
//各种看起来牛逼用起来舒适便捷的（划掉）模板

int main() {
	n=read();
	for(int i=1; i<=n; ++i)
		a[i]=read();
	for(int i=1; i<=n; ++i) {
		if(a[i]>a[i-1]&&i!=1) ans+=a[i];
		if(a[i]>=a[i+1]&&i!=n) ans+=a[i];
	}
    //核心循环
	write(ans);
	return 0;
}
```

---

## 作者：Wyxrg (赞：6)

**Solution:**

对于每个很大的数，基于贪心，我们显然要让它合并次数尽可能少，以保证最终总代价最小。

如图：

![](https://s2.ax1x.com/2019/12/14/QWPaUH.png)
考虑中间那个最大的 $maxn$，很显然，将其与其它的合并代价显然更大，所以，我们不可能先用 $maxn$ 去和其它的合并。

但是，由于最终目标长度为1，所以无论如何，$maxn$ 终将被合并，可以先考虑将比它小的全部合并，最后再与它合并，以减少它参与合并的次数。

不难想到，可以先将 $maxn$ 左边全部合并，再将其右边全部合并，最后，再让左右两部分与它合并，这样可以保证比先合并 $maxn$ 与其它的更优。

然后，该问题就被分成两个小问题，合并左边与右边。

注意到，如果一个数左边比它小，那么总有一天，总有一年会向它合并过来，也就是说，它不可避免的向左对答案产生一次贡献，右边一样同理。

若一个数左边比它大，那么它肯定会在某个时刻并上去，那么对答案产生贡献的是它左边的数，右边同理。

总之，一个数的左邻比它小，它会产生一次贡献，右舍比它小，就会再产生一次贡献，累计答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,hxt[10001000];
long long ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&hxt[i]);
	for(int i=2;i<=n;i++) ans+=max(hxt[i],hxt[i-1]);
	printf("%lld",ans); 
	return 0;
} 
```

---

## 作者：NightStriker (赞：5)

看到这道题，首先想到是区间 dp，$f_{l,r}$ 代表操作 $l\sim r$ 的代价。

$$\large f_{l,r}=\left\{\begin{matrix} 
  a_l+f_{l+1,r}\ [x=l] \\  
  a_r+f_{l,r-1}\ [x=r] \\
  2a_x+f_{l,x-1}+f_{x+1,r}\ \ \ \text{else}
\end{matrix}\right. $$

其中 $x$ 代表该区间内极值的位置。

但我们发现 $l,r$ 的范围过大，无法开 $10^5\times 10^5$ 的数组。

使用 dfs 即可解决这个问题。

但是时间复杂度不允许，因为需要重复查询区间内最大值。

查询区间内最大值？RMQ！

使用 $\mathcal{O}(n\log_2 n)$ 的 [ST 表](https://oiwiki.com/ds/sparse-table/)。

其中求解答案的 `work` 函数需要开 long long。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1000001],f[1000001][21];
//f 数组表示 [i,i+2^j) 内的最大值
int RMQ(int x,int y){
	int len = y-x+1;
	int k = log2(len);
	if(a[f[x][k]]<a[f[y-(1<<k)+1][k]]) return f[y-(1<<k)+1][k];
	else return f[x][k];
}
long long work(int i,int j){
	if(i>=j) return 0;
	int p = RMQ(i,j);
	if(p==i) return a[i]+work(i+1,j);
	else if(p==j) return a[j]+work(i,j-1);
	else return a[p]*2+work(i,p-1)+work(p+1,j);
}
signed main() {
	cin>>n;
	for(int i = 1;i<=n;i++) {
		cin>>a[i];
		f[i][0] = i;
	}
	for(int k = 1;1<<k<=n;k++){
		for(int i = 1;i<=n-(1<<k)+1;i++){
			f[i][k] = f[i][k-1];	
			if(a[f[i][k]]<a[f[i+(1<<k-1)][k-1]]) f[i][k] = f[i+(1<<k-1)][k-1];
		} 
	}
	cout<<work(1,n)<<endl;
	return 0;
}
```

---

## 作者：redegg (赞：5)

应该是贪心吧，写了三次（全TLE一次，全WA一次，全AC一次），思路是每次合并最小的，这样的话减少数的数量不变但代价变小（我傻到第一次去写dp...）。

由于给的数很大，我维护了一个线段树，记得数组是开long long。

代码意思是，每次在一个区间中找到最大的数，然后以这个数为分界线，分成两个新的区间，然后去同样去处理新的区间，到底后返回过程中算代价。这样返回过程就是一个贪心过程。

（ps：题解被hack掉一次，已经更改，请多多指教，建议观看上面大佬题解）

（我为什么又交了个线段树题解？）

```
#include <bits/stdc++.h>
using namespace std;
int n;
struct ha
{
    long long maxn;
    int v;
    bool operator <(const  ha &aa)const
    {
        return maxn<aa.maxn;
    }
}t[6000000];

long long a[2000000];

void build(int l,int r,int id)
{
    if(l==r)
    {
        t[id].maxn=a[l];
        t[id].v=l;
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,id*2);
    build(mid+1,r,id*2+1);
    t[id]=max(t[id*2],t[id*2+1]);
}

ha cck(int l,int r,int z,int y,int id)
{
    if(l==z&&r==y)
    {
        return t[id];
    }
    int mid=(l+r)/2;
    if(mid>=y)return cck(l,mid,z,y,id*2);
    else if(mid<z)return cck(mid+1,r,z,y,id*2+1);
    else
    {
        return max(cck(l,mid,z,mid,id*2),cck(mid+1,r,mid+1,y,id*2+1));
    }
}

long long dfs(int l,int r)
{
    if(l>r)return 0;
    if(l==r)return 0;
    cck(1,n,l,r,1);
    long long ans=0;
    ha ll=cck(1,n,l,r,1);
    if(ll.v-1>=l)
    {
        ans+=dfs(l,ll.v-1)+ll.maxn;
    }
    if(ll.v+1<=r)
    {
        ans+=dfs(ll.v+1,r)+ll.maxn;
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,n,1);
    printf("%lld\n",dfs(1,n));
}


```

---

## 作者：未见堇开 (赞：3)

我们对可能的序列进行分类讨论（设$len$为序列长度）：

#### 1.单调序列
显然，对于序列中的元素合并整个序列的最小代价为
$\sum _{i=2}^{len}a_{i}$（递增）
$\sum _{i=1}^{len-1}a_{i}$（递减）
#### 2.有一个波峰的序列
同样显然，从波峰两侧向波峰合并是最优方案。

设波峰是$t$号元素，则最小代价为$\sum _{i=2}^{t}(a_{i})+\sum _{i=t}^{len-1}(a_{i})=a_{t}+\sum _{2}^{len-1}a_{i}$
#### 3.有两个波峰的序列
易证先合并低波峰再合并高波峰的代价最小。

维护一个单调栈，将出栈序列合并后与入栈元素合并，同时计算代价。
#### 4.任意序列
其实就是将两个波峰的情况扩展到多个波峰，同情况3。

~~明显把题目复杂化了~~

代码：
```cpp
#include<cstdio>
#define reg register
#define MAXN 1000001
using namespace std;

typedef long long ll;

int q[MAXN];
int n,ptr_q=0;
ll ans=0;

inline int qin()//快读
{
	reg int ans=0,m=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			m=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ans=ans*10+(ch-'0');
		ch=getchar();
	}
	return(ans*m);
}

int main()
{
	n=qin();
	for(reg int i=1;i<=n;i++)
	{
		reg int tmp=++ptr_q;
		q[ptr_q]=qin();
		while(q[tmp]>q[ptr_q-1]&&ptr_q>1)
			ptr_q--;
		if(ptr_q!=tmp)
		{
			for(reg int i=ptr_q;i<tmp-1;i++)
				ans+=q[i];
			ans+=q[tmp],q[ptr_q]=q[tmp];
			q[tmp]=0;
		}
	}
	for(reg int i=1;i<ptr_q;i++)
		ans+=q[i];
	printf("%lld",ans);
	return(0);
}
```
------------
其实这道题与[[NOIP2013]积木大赛/[NOIP]2018铺设道路](https://www.luogu.org/problemnew/show/P1969)是一类题，解法也很类似。~~所以本题难度可能不到蓝题~~

---

## 作者：木木！ (赞：2)

emmmm贪心$\Theta(n)$代码已经有很多人发了，那就发个$\Theta(nlogn)$贪心25分非正解吧QwQ

思路是每次找到现有数列中最小的合并代价，合并了。正确性显然。

合并的时候将较小的数字删除，再插入一个新生成的数对，用链表维护邻接情况。易证每次循环都会导致一个数被删除，所以队列中最多有$2n$个数，总复杂度$\Theta(nlogn)$（可以结合代码理解）

然而……在全RE、1WA 3TLE之后，终于卡在了1AC 3TLE，然后开-o2也救不了了……

（说好的$\Theta(nlogn)$过得了$10^6$呢）

结论：STL = Sometimes TLE Library

一开始想的是$\Theta(n^3)$的动规算法（似乎满足四边形不等式……应该可以降维到$\Theta(n^2)$？），反正稳挂。

思路是用$dp[i][j]$表示合并$[i,j]$这一段的最小代价，可得$dp[i][j]=min\{i\leq k< j,dp[i][k]+dp[k+1][j]\}+max\{i\leq k\leq j,v_k\}$，初始条件$dp[i][i] = 0$

预计得分30分，实际得分25分（数据范围是假的，说是对于$30%$的数据满足$1<n\leq 300$，但是总共才4个点）

最后放上$\Theta(TLE)$贪心代码

```cpp
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

#define int long long

int nxt[1000005];
int pre[1000005];
int val[1000005];
int del[1000005];

struct pr
{
	int x;
	int y;
};

class cmp
{
public:
	bool operator()(pr a,pr b)
	{
		return max(val[a.x],val[a.y]) > max(val[b.x],val[b.y]);
	}
};


signed main()
{
	int n;
	scanf("%lld",&n);
	for(int i=1; i<=n; ++i)
	{
		scanf("%lld",val+i);
	}
	
	nxt[1] = 2;
	for(int i=2; i<n; ++i)
	{
		nxt[i] = i+1;
		pre[i] = i-1;
	}
	pre[n] = n-1;
	
	priority_queue<pr,vector<pr>,cmp> pq;
	for(int i=1; i<n; ++i)
	{
		pr p;
		p.x = i;
		p.y = i+1;
		pq.push(p);
	}
	
	int ans = 0;
	while(!pq.empty())
	{
		pr th = pq.top();
		pq.pop();
		
		if(val[th.x]>val[th.y])
		{
			swap(th.x,th.y);
		}
		if(del[th.x] || del[th.y])
		{
			continue;
		}
		
		del[th.x] = 1;
		ans += val[th.y];
		
		if(pre[th.y] == th.x)
		{
			pre[th.y] = pre[pre[th.y]];
			nxt[pre[th.y]] = th.y;
			if(pre[th.y])
			{
				pr p;
				p.x = pre[th.y];
				p.y = th.y;
				pq.push(p);
			}
		}
		else
		{
			nxt[th.y] = nxt[nxt[th.y]];
			pre[nxt[th.y]] = th.y;
			if(nxt[th.y])
			{
				pr p;
				p.x = nxt[th.y];
				p.y = th.y;
				pq.push(p);
			}
		}
	}
	
	printf("%lld",ans);
}
```

---

## 作者：nofind (赞：2)

题意:https://www.luogu.org/problem/P4393

代码短,但是思维高的题

先推荐一篇博客(就是看这篇博客才懂得)：
https://www.cnblogs.com/DarkValkyrie/p/11258015.html

既然与最大值有关,不妨这么考虑：

一个区间的最大值x至少会被计入答案两次(位置1/n的只会计入一次),因此如果有一种方案使得每个最大值仅会被计入答案一次,那么这种方案就是最优方案,显然这是可以办到的,对于[1,n]的最大值x,我们优先合并[1,x-1]和[x+1,n],最后再合并x即可(这是分治的思想),因此从1到n O(N)扫一遍,ans+=max(a[i],a[i+1])

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1000010;
int n,ans;
int a[maxn];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<n;i++)ans+=max(a[i],a[i+1]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：青丘杨哲 (赞：1)

统一规定，两个元素合并后采用二元素编号中较小的一个作为新的编号。

假设$5$个元素$a_1,...,a_5$，其中$a_3$是所有数中最大的，那么我们需要使$a_3$尽量少地被使用。

显然$a_3$至少要被使用$2$次，因为左边和右边的数都比它小，但是我们可以避免额外使用$a_3$——让$(a_1,a_2)$和$(a_4,a_5)$先合并，再让二元素与$a_3$合并。代价为：$\max(a_1,a_2)+\max(a_4,a_5)+2a_3$。

在局部的小区间内同理：设$f_{l,r}$为区间$[l,r]$成功合并的最小代价，如果$\max\limits_{i=l}^r a_i=a_j$，则要付出的代价为$2a_j+f_{l,j-1}+f_{j+1,r}$。如此进行$DP$，这样就可以得到一个$O(n \log n)$的算法。

考虑一下如何优化该算法。在递归的过程中，只有能够作为区间最大值的数会被计算到，而无法作为哪怕是最小的区间之最大值的数并不会被计算在内——这个“最小的区间”，显然指相邻的$2$个数。而无论一个数有多大，它最多只会被计算到$2$次。这样我们推出一个极其简单的计算方法：$ans=\sum\limits_{i=1}^{n-1}\max(a_i,a_{i+1})$。

下证这个计算方法和$DP$的方程是完全一致的。它们的共同性质：

（$1$）一个数最多会被计算到$2$次；

（$2$）递归边界都是最小的区间$[i,i+1]$；

（$3$）无法作为区间最大值的数，没有资格被计算到答案内。

现在唯一存在的隐患是：如今的计算方法出现了只被计算$1$次的数，这是哪里来的？$DP$方法里面数有三类：大区间最大值，即在一个区间内它的左右两边都有数，它被计算$2$次；小区间最大值，即递归到最小的区间$[a_i,a_{i+1}]$之时，它们临时被充当为最大值使用；无资格值，即不是任何区间的最大值。

显然被计算$1$次的数就是小区间最大值。这样我们算法的正确性被证明完毕了。

参考程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=(1e6+5);
int N; LL a[MAXN],ans;
int rd1(){
	int x=0; char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
	return x;
}
LL rd2(){
	LL x=0; char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
	return x;
}
int main(){
	N=rd1();
	for (int i=1;i<=N;i++) a[i]=rd2();
	for (int i=1;i<=N-1;i++)
		ans+=max(a[i],a[i+1]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Cat_cc (赞：1)

 这是我见过的比较水的一道蓝题了，看到题解的大佬有人用什么贪心和队列，但是根本不需要，反正最后长度为1，最后一次操作所需价值必然是最大的那个数，那么既然无论如何都会有最大的，就从头到尾扫一遍，将较大的数与答案累加输入的时候一起处理就好了。

ac代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,now,last,ans;
int main()
{
    cin>>n>>last;
    for(n--;n--;){
    cin>>now;
    ans+=max(last,now);
    last=now;
    }
    cout<<ans;
}
```


---

## 作者：小黑AWM (赞：1)

> 这题很简单，基本的线性贪心我们这里就不再赘述了。不过我们可以通过这题，想到另外一题的做法[【P5462】X龙珠](https://www.luogu.org/problem/P5462)

显然的，我们可以将一个长度为 $n$ 的序列分为 $n-1$ 个二元组，记二元组 $i$ 中的最大值是 $P(i)$ ，每次取出所有二元组 $P(i)$ 最小的那个，把二元组里那个较小的数从序列里删掉，这样子我们其实从二元组集合中删掉了两个元素，又添加了一个元素。

由于一共操作 $n-1$ 次，每次我们从堆中删除一个元素的复杂度是 $O(logn)$ 的，所以复杂度是严格的 $O(nlogn)$ 。

然后用与X龙珠类似的双向链表+堆模拟就可以写出这个做法。

```cpp
/*
 * Author: xiaohei_AWM
 * Date: 7.24
 * Mutto: Face to the weakness, expect for the strength.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<utility>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
using namespace std;
#define reg register
#define endfile fclose(stdin);fclose(stdout);
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
namespace IO{
    char buf[1<<15],*S,*T;
    inline char gc(){
        if (S==T){
            T=(S=buf)+fread(buf,1,1<<15,stdin);
            if (S==T)return EOF;
        }
        return *S++;
    }
    inline int read(){
        reg int x;reg bool f;reg char c;
        for(f=0;(c=gc())<'0'||c>'9';f=c=='-');
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^'0'));
        return f?-x:x;
    }
    inline ll readll(){
        reg ll x;reg bool f;reg char c;
        for(f=0;(c=gc())<'0'||c>'9';f=c=='-');
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^'0'));
        return f?-x:x;
    }
}
using namespace IO;
const int maxn = 1e6 + 10;
struct Pair{
    int first, second;
    int fid, sid;
    int maxv(){
        return max(first, second);
    }
    int mid(){
        if(first > second) return sid;
        else return fid;
    }
    bool operator<(const Pair &v)const{
        return max(first, second) > max(v.first, v.second);
    }
};
struct Node{
    int num, id, pre, nxt;
} table[maxn];
int n, func[maxn], vi[maxn];
ll ans;
priority_queue<Pair> Q;
int main(){
    n = read();
    for(int i = 1; i <= n; i++){
        table[i].num = read(), table[i].id = i;
        table[i].pre = i-1, table[i].nxt = i+1;
    }
    Pair temp, temp1;
    for(int i = 1; i <= n-1; i++){
        temp.first = table[i].num;
        temp.fid = i;
        temp.second = table[table[i].nxt].num;
        temp.sid = i+1;
        Q.push(temp);
    }
    while(n > 1){
        do{
            temp = Q.top();
            Q.pop();
        }while(vi[temp.fid] || vi[temp.sid]);
        n -= 1;
        vi[temp.mid()] = 1;
        ans = ans + temp.maxv();
        table[table[temp.mid()].pre].nxt = table[temp.mid()].nxt;
        table[table[temp.mid()].nxt].pre = table[temp.mid()].pre;
        temp1.first = table[table[temp.mid()].pre].num,
        temp1.second = table[table[temp.mid()].nxt].num;
        temp1.fid = table[temp.mid()].pre;
        temp1.sid = table[temp.mid()].nxt;
        if(temp1.first != 0 && temp1.second != 0)
            Q.push(temp1);
    }
    cout << ans << endl;
    return 0;
}
```

没错我就是直接用我过了X龙珠的程序改的。

但是 priority_queue 套了一个比较大的 structure 所以常数不是很优秀，但是用 O2 可以过。读者可以自行采用手写堆优化，或者把函数换成变量之类的。

---

## 作者：nju_zdd (赞：0)

# 比较简单的一道题目
#### 说白了题目的意思就是：对于任意的a[i - 1]和a[i]
## **拣小的往ans里加**


那么这题就变得异常简单（小声bb）.

$\color{red}\text{附AC代码：}$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans, a[1000100];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
        ans += max(a[i - 1], a[i]);
    cout << ans;
}
```
$\color{blue}\text{好了就是这样，祝大家切蓝题愉快！}$

---

