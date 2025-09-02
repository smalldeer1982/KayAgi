# [COI 2007] Patrik 音乐会的等待

## 题目描述

$n$ 个人正在排队进入一个音乐会。人们等得很无聊，于是他们开始转来转去，想在队伍里寻找自己的熟人。

队列中任意两个人 $a$ 和 $b$，如果他们是相邻或他们之间没有人比 $a$ 或 $b$ 高，那么他们是可以互相看得见的。

写一个程序计算出有多少对人可以互相看见。

## 说明/提示

#### 数据规模与约定
对于全部的测试点，保证 $1\le$ 每个人的高度 $< 2^{31}$，$1 \le n \le 5\times 10^5$。

## 样例 #1

### 输入

```
7 
2 
4 
1 
2 
2 
5 
1```

### 输出

```
10```

# 题解

## 作者：SuperJvRuo (赞：150)

## 搬运+翻译Croatian Olympiad in Informatics 2007官方题解

The large limit on N will make quadratic solutions time out.
 
$O(N^2)$枚举显然会TLE。
 
To start with, suppose the heights of all people are distinct. Imagine going through the line in order.
 
先假设每个人身高不同，脑补一下走过整个队列。
 
Observe any person A waiting in line. If, after person A, we encounter a taller person B, then person Asurely can't see anyone after person B.
 
观察队伍中的一个人A。如果我们他后面找到了一个比他不知道高到哪里去了的B，A就不能与B后面的人谈笑风生了。
 
Because of this, when going through the line, we can maintain a stack of "open subproblems", wherean open subproblem is a person already encountered in the line, but who still has a possibility of seeingsomeone whom we haven't yet encountered. It should be obvious that the subproblems on the stackare sorted in descending order of height (topmost subproblem = shortest person).
 
因此我们可以维护一个单调栈，记录我们已经找到过的高人，但他仍可能与没找到过的高人谈笑风生。显然栈上的高人们按高度的降序排列，栈顶的人最矮。
 
When we encounter a new person, that person can see everyone on the stack that is shorter, and alsotakes those people off the stack (closing their subproblems). If the stack isn't empty after this, theperson can also see the first person remaining on the stack. The person then enters the stack (there is apossibility that they will see someone later in line).
 
当我们找到一个新的高人时，他可以向栈里比他naive人的传授人生经验，并让他们出栈。如果出栈之后栈非空，他还可以与栈顶的高人谈笑风生。然后我们再另请这位高明进栈。
 
Even though the solution has two nested loops, the overall complexity is O(N), because every personenters and leaves the stack exactly once, and each iteration of the inner loop pops oneelement off thestack.
 
有人问了一个simple的问题：这样的解法不是有两层循环吗？然而它的总复杂度是$O(N)$，因为每个人的进栈与出栈都只有一次，内层的每次循环从栈中弹出一个高人。
 
To complete the solution, we need to consider the effect of persons equally tall. One way is to have thestack hold ordered pairs (height, number of people) and maintain it accordingly.
 
要A掉这道题我们还要考虑两个人身高相同的情况。我们可以在栈里存pair<身高，人数>并维护它。

官方标程：
```
/*
  Croatian Olympiad in Informatics 2007
  Task PATRIK
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

typedef long long llint;
typedef pair<int,int> par;

stack<par> S;

int main( void ) {
   int n;
   scanf( "%d", &n );

   llint ret = 0;
   for( int i = 0; i < n; ++i ) {
      int h;
      scanf( "%d", &h );
      
      par p( h, 1 );
      for( ; !S.empty() && S.top().first <= h; S.pop() ) {
         ret += S.top().second;
         if( S.top().first == h ) p.second += S.top().second;
      }

      if( !S.empty() ) ++ret;
      S.push( p );
   }
   
   cout << ret << endl;

   return 0;
}
```

---

## 作者：eternal风度 (赞：73)

# 单调栈+二分查找

照例想推广博客：[eternal风度的博客](http://www.cnblogs.com/cjoierljl)

那么这一篇也同步发表于：[Patrik 音乐会的等待题解(单调栈+二分查找)](https://www.cnblogs.com/cjoierljl/p/9912127.html)

## 嘿嘿入正题

这个题不是很难，但是没有转过来还是难想的

可以先去做一下这个题：[洛谷P1901 发射站](https://www.luogu.org/problemnew/show/P1901)

**蒟蒻发现很多题解都是错的呀，复杂度比较玄学吧**

**那么介绍一种标准的$O(nlogn)$的方法**

### 单调栈
考虑对于一个人作为方案中右边那个人时我们算答案（为了不算重）

有哪些人我们看不到呢，无非是被它右边的人挡住了是吧

那么从左往右维护一个单调递减的单调栈，单调栈中的人不会出现被挡住的情（只有$i$看不到的情况后面会讲）

自己想一下这里很简单

### 二分查找
考虑肯定只有单调栈中的人会被$i$算入答案是吧

并且很容易发现一定是个连续的区间$[x,i-1]$（~~这不废话吗~~）

那么我们在单调栈中二分这个区间的左端点，显然左端点就是$i$左边第一个比$i$高的数

这不就是上面那个[发射站](https://www.luogu.org/problemnew/show/P1901)的题目了吗

计入答案的就是区间长度啦

### 代码极其简单。。。
```
#include<bits/stdc++.h>
#define il inline
#define rg register
#define ldb double
#define lst long long
#define rgt register int
#define N 500050
using namespace std;
const int Inf=1e9;
il int read()
{
	int s=0,m=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')m=1;ch=getchar();}
	while( isdigit(ch))s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}

int n,top;lst Ans;
int H[N],stk[N];

il void Calc(rgt x)
{
	rgt le=0,ri=top,mid,ret=0;
	while(le<=ri)
	{
		mid=(le+ri)>>1;
		if(H[stk[mid]]>x)ret=mid,le=mid+1;
		else ri=mid-1;
	}
	if(!ret)Ans+=top;
	else Ans+=top-ret+1;
}
int main()
{
	n=read();
	for(rgt i=1;i<=n;++i)H[i]=read();
	for(rgt i=1;i<=n;++i)
	{
		Calc(H[i]);
		while(top>0&&H[i]>H[stk[top]])--top;
		stk[++top]=i;
	}return printf("%lld\n",Ans),0;
}
```
# 如果对您有所帮助，将是我万分的荣幸

---

## 作者：越学越掂 (赞：26)

这道题可以使用单调栈解决。

首先，我们整理一下思路，对于队伍中的一个人来说，他可能看到自己前面的人，也可能看到自己后面的人，但是如果把前后两种情况都考虑的话，寻找一遍下来一定有很多重复，所以我们决定只考虑每个人的前或后一侧的情况，这里我们对每个人的前面的人讨论

如果一个人身后存在一个比他高的人，那么他将不会再被看见，因此，可以可根据身高维护一个单调栈，从左向右依次扫描，扫描到 A 时，我们希望栈里保存的是 A 之前，能够和 A 相互看到的人。具体实现时，栈中的元素是自下而上递减的，这就要求我们再加元素时保证栈顶元素大于等于加进的那个元素，可以用二分法求出栈中第一个大于等于输入的元素的值，并把这个元素以上的元素全部弹出，把输入的元素放进栈中。

写代码时一定要注意：

1.第一个元素单独输入，道理很显然

2.由于第一个元素是单独输入的，所以栈中是有一个元素的，初始时把top设为1

3.根据题意，身高相同的人并不会互相遮挡

```cpp
#include<iostream>
using namespace std;
long long st[10000000],n,top=1,ans,m;
int main()
{
    cin>>n;
    int a;
    cin>>st[1];//输入
    for(int i=2;i<=n;i++)
    {
        cin>>a;
        if(st[top]>a)
        {
            top++,ans++,st[top]=a;
        }
        else
        {
            int l=1,r=top;
            while(l<r)
            {
                m=(l+r)>>1;
                if(r==l+1)m=r;
                if(a>=st[m])r=m-1;
                else l=m;
            }
            ans+=top-l+1;
            while(top>0&&st[top]<a)top--;
            st[++top]=a;
        }
    }
    cout<<ans;//输出
}
```

---

## 作者：Mr_WA的大号 (赞：23)

### 单调栈万岁！

P1823方法：单调栈

难度★★★★

## 正文来了！

洛谷的这一题要用**单调栈**来完成。

单调栈是一个具有单调性的栈，要一直保持单调，遇到不单调的，要删除或覆盖。就像这一题，要保持上升的趋势。

**重点：连续的几个同样的数字要用一个数组来记录个数，栈中只存一个数字，不然会TLE。还要开long long,不然WA等着你！**

好了，课讲完了。上代码。

同志们一定要记得：

**棕名只用动动鼠标抄题解，不抄题解，拒绝棕名！**

```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
using namespace std;
long long n,s[500010],a[500010],top,sum,same[500010];
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	    scanf("%d",&a[i]);
	for(int i=1; i<=n; i++)
	{
		while(top>0&&a[i]>=a[s[top-1]])
		{
			if(a[i]==a[s[top-1]])
			    same[i]=same[s[top-1]]+1;
			sum++;
			sum+=same[s[top-1]];
			top--;
		}
		if(top>0)sum++;
		s[top++]=i;
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：multiverse_ (赞：15)

#### 单调栈

	n^2暴力可 A 6个点
	不用结构体或pair记录重复个数 T 3个点 
	考虑一个人如果遇到一个比他高的人，后面的人他就看不到了，于是到此为止，把他扔掉
	想法与单调栈极为相似，于是有：
    
  ```cpp
#include <bits/stdc++.h>
using namespace std;
struct info{
	int val,num;
};//val表示当前这个人的高度，num表示在这个人之前且他所能看到的有多少人和他一样高 
void read(int &x){
	int f=1,r=0;char ch;
	do ch=getchar();while(ch!='-'&&!isdigit(ch));
	if(ch=='-')f=-1,ch=getchar();
	do r=r*10+ch-48,ch=getchar(); while(isdigit(ch));
	x=f*r; 
}//快读 
stack<info> s; //单调栈 
int n; 
int main() {
	cin>>n;
	long long ans=0;
	for(int i=1;i<=n;i++){
		int h=0;
		read(h);//当前这个人A的高度 
		info p=(info){h,1};//高度为本身，最先开始和A一样高的人是一个（自己） 
		while(!s.empty()&&s.top().val<=h){
			//当栈顶元素小于A的时候，栈顶这个人被A挡住了，所以看不见后面了要被弹出去
			//而弹出等于A高度的人时要记录一下，也弹出
			//（因为如果不弹出，单调栈访问不到除栈顶元素以外的元素） 
			ans+=s.top().num;
			//答案加上栈顶元素的与之相同高度的元素个数（没有就加一） 
			if(s.top().val==h)p.num+=s.top().num;
			//如果该元素与A的高度相同,那么与A高度相同的人的个数（num）要加上该元素的个数 
			s.pop();
			//弹出栈顶元素 
		}
		if(!s.empty())ans++;
		//如果栈中还有元素，则头元素是第一个大于A的高度的人，也可以和A互相看到 
		s.push(p);
		//将A的信息压入栈中 
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：EarthGiao (赞：9)

## 【思路】
单调栈    
很有意思的一道题目     

### 【题目大意】
一个队列    
两个人中间只要没有比他俩其中一个高的就可以相互看见    
求能够相互看见的对数    

### 【理智分析】
这对点能够互相看见是基于两者之间没有比他们任何一者高的基础上的    
一个人能够看见最远的一个人就是两边第一个比他高的    
这很显然对吧？     
因为第一个比他高的之后的人就被他挡住了    
（贴合实际）    
然后如果这个人和一边第一个比他高的人    
中间的人不一定能够全部被这个人看见    

### 【举例】   
因为：   
1 1 4 5 1 4 1 9 1 9    
位置8上的那个9右边能看到最远的就是位置1上的1    
但是位置1到位置8之间所有的数   
他不是都能够彼此看见的    
比如位置5上的那个1   
就不能彼此看见    
因为中间有一个位置6上的4是比1高的   
所以彼此看不见    
看一下位置8上的9右边能够看到的数     
5 4 1    
很显然这是一个大向右递增的区间    
因为你看到了右边第一个之后    
看到的右边第二个不能够比右边第一个要低    
不然就是不能够被看见的    

### 【呼之欲出】   
是不是很显然了？    
这不就是单调栈吗！？    

### 【最终思路】    
上面的过程完全就是在单调栈的过程对吧    
如果栈里面的栈顶元素比手上这个元素要小    
那栈顶元素左边能够看到的最后一个元素就是手上这个了   
再也看不到别的了     
这就是1对可以互相看见     
弹出就好了    
然后手上这个继续和栈顶去比较   

### 【注意】
两个一样高的人是可以相互看见的    
1 1 1 1 1     
这串数字里面    
第一个1是可以和最后一个1相互看见的    
千万不要忽略哦    

然后就是怎么处理上面这种情况了    
一开始我想的是暴力从栈里面取出来    
计数有多少个    
计完数之后再放回栈    
这样就超时了两个点    
这两个点我下载了一个点的测试数据看来一下    
500000个一样的10   
不超时才怪……    
所以 可以在栈中存一个结构体    
记录这个人的高度和人数    
也就是和她一样高的并且在栈中位置是紧挨着的    
遇到和她一样的情况只需要将其弹出    
然后在弹入一个v(计数多少个人) + 1的就好了      
## 【完整代码】
### 【80分暴力出栈代码】
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
const int Max = 500005;
int a[Max];
stack<int>s;
int main()
{
	int n;
	cin >> n;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i];
	int js = 0;
	for(register int i = 1;i <= n;++ i)
	{
		int jj = 0;
		while(!s.empty() && a[i] >= s.top())
		{
			if(a[i] == s.top())
			{
				while(!s.empty() && s.top() == a[i])
					s.pop(),jj ++,js ++;
			}
			else
			{
				s.pop();
				js ++;
			}
		}
		if(!s.empty())
			js ++;
		while(jj --)
			s.push(a[i]);
		s.push(a[i]);
	}
	cout << js << endl;
	return 0;
}
```
### 【AC代码】
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
#define int long long
using namespace std;
const int Max = 500005;
struct node
{
	int h;
	int v;
}a[Max];
stack<node>s;
signed main()
{
//	freopen("music.in","r",stdin);
	int n;
	cin >> n;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i].h,a[i].v = 1;
	int ans = 0;
	for(register int i = 1;i <= n;++ i)
	{
		while(!s.empty() && a[i].h > s.top().h)
		{
			ans += s.top().v;
			s.pop();
		}
		if(!s.empty() && a[i].h == s.top().h)
		{
			node qwq = s.top();
			ans += s.top().v;
			s.pop();
			if(!s.empty())
				ans ++;
			s.push((node){qwq.h,qwq.v + 1});
		}
		else
		{
			if(!s.empty())
				ans ++;
			s.push(a[i]);
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：于丰林 (赞：9)

**说句实话，这道题真的挺坑的，首先，我们先来说一下大体的思路。**

**这道题其实就是给出一个队伍，要找出所有能相互看见的一对（两个人之间没有比两个人任意一个人高的人），那么我们该怎么做呢？**

**
我们来想一下，由于题中让我们找的是对数，为了避免找重了，我们只能看一个方向（如果你偏要看两个方向再除以二也没有人拦你。。。），但是从左往右看显然前面元素会受到后面的影响，为了保证正序判断，这里应该从右往左看。
**

**我们任意取一位人，那么这个人所能看到最远的人就是它前面第一个比他高的人，并且如果这个人高于他左边的人P，那么显然他右边的人一定看不到P。
**

**根据这两条性质，我们很容易想到一种数据结构：栈。又因为每个人入栈时栈中元素一定是单调不递增的，所以该栈具有单调性，因此我们引入一个新的概念：单调栈。**

**归概来说，每当我们放入一个元素，我们只需要执行两个操作：**

**1.查找第一个比他高的人，统计看到的人数**

**2.弹出会被他遮到（小于他）的元素**

**第一条我们可以用二分法查找，而第二条直接线性搜索即可。**

**最后，附上本题代码：**

```cpp
#include<cstdio>
using namespace std;
int n,top;
long long Ans;
int a[500050],stk[500050];
void dfs(int x)
{
    int le=0,ri=top,mid,ret=0;
    while(le<=ri)
    {
        mid=(le+ri)>>1;
        if(a[stk[mid]]>x)ret=mid,le=mid+1;
        else ri=mid-1;
    }
    if(!ret)Ans+=top;
    else Ans+=top-ret+1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; ++i)scanf("%d",&a[i]);
    for(int i=1; i<=n; ++i)
    {
        dfs(a[i]);
        while(top>0&&a[i]>a[stk[top]])--top;
        stk[++top]=i;
    }
    printf("%lld",Ans);
    return 0;
}
```

## **你以为这就完事了？**
**并没有**！

**在课上有人提到了一种简便做法（错的，但可以改对）**

简便做法：不进行二分查找，认为弹出元素的数量加一就是能看到的人数

乍一看好像是对的：例如 9 8 7 3 2中插入一个6，那么弹出3，2看到了7，3，2，确实是弹出元素数量加一，但是忽略了相等的情况（题中没说不能相等（坑））。

　　例如：9，8，7，2中插入一个2，那么显然不会弹出任何元素，但是看到的是两个哇！因此加入特判一。。。
  
　　再例如：φ 中插入任何元素，那么显然答案是0，但是按照上述做法求得答案1！因此加入特判二。。。
  
　　还有很多就不一一列举了，总之，如果一道题加了这么多特判，代码长度一定会大大增加，这里还是提供一种加了补丁后的代码：
  
　　这里用到了两个栈，一个存数，另一个存个数。
  
```cpp
#include <cstdio>
#include <stack>
using namespace std;
stack <long long> stk,num;
int n;
long long ans;
int main()
{
    scanf("%d",&n);
    long long tmp;
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld",&tmp);
        while (!stk.empty() && stk.top() < tmp)
        {
            stk.pop();
            ans += num.top();
            num.pop();
        }
        if (stk.empty())
        {
            stk.push(tmp);
            num.push(1);
        }
        else
        {
            if (tmp != stk.top())
            {
                ans += 1;
                stk.push(tmp);
                num.push(1);
            }
            else if (stk.size() == 1)
            {
                ans += num.top();
                int u = num.top();
                num.pop();
                num.push(u + 1);
            }
            else
            {
                ans += num.top();
                int u = num.top();
                num.pop();
                ans += 1;
                num.push(u + 1);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：LlLlCc (赞：9)

这题是很经典的单调栈啊。

数据是500000，nlogn也能过（好像另一篇题解就是nlogn的），其实数据还能再加强点，这样就只能o(n)的单调栈过了。（亲测时间为nlogn的1/5）

------------
进入正题

## 题目大意：

  求出组合A,B，（**A，B直接不存在严格大于A或B**）有多少组。
  
------------
## 1.暴力：
  好的方法都是建立在暴力的基础上的，只有想通了暴力才有可能得出正解。暴力还是比较好想的，N方枚举每个人，看看他们之间有没有比他们大的就好了。
  
## 2.单调栈 （O（n））

  举个例子：1 2 3
  
  看看这个例子，发现当枚举i（1）时，只有后面（2）有比他大的，再后面（3）的他就看不到了。这就让我们想到了单调栈，**只要一个元素出栈了，那么接下来就没他什么事了**（这也是单调栈时间复杂度O(n)的原因，因为每个元素只会入栈一次，出栈一次）。
  
  具体单调栈的操作，另一个题解已经讲的很清楚了，我就来讲讲怎么把那层多余的二分查找（logn）给去掉.
  
  因为单调栈是保持单调的，越靠近栈顶的值越小，所有为了保持单调性每枚举到的值就往下压，对比和栈顶那个大，如果大于栈顶，top（栈的高度）减1。当不能再往下压时，如果栈内还有元素，说明这两个人是可以看到的（中间不存在大于他们的元素了），ans++。
  
  这里有个优化，当该元素等于栈顶元素时，就把栈顶元素的积累次数+1，不用再站一位了。
  
  还有一个坑点，这题要开**long long**
  
  具体看代码体会吧：
  
  ```
#include<bits/stdc++.h>
#define ll long long
#define maxn 10000005
using namespace std;
ll n,a[maxn],top,x,ans;
struct lc{
	ll x,tot;
}Q[maxn];
inline ll read(){
	ll ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++){
		while (top&&a[i]>a[Q[top].x]) ans+=Q[top].tot,top--;
		if (a[i]==a[Q[top].x]){
			ans+=Q[top].tot;Q[top].tot++;
			if (top>1) ans++;
		    continue;
		}
		if (top) ans++;
		Q[++top].x=i,Q[top].tot=1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：liubai (赞：8)

## 改个一个小时，终于将这个题给A了
### 话不多少 直接分析题目  
 _队列中任意两个人A和B，如果他们是相邻或他们之间没有人比A或B高，那么他们是可以互相看得见的。_ 
### 看到这里可以想到单调队列维护一个单调递减的序列+二分搜寻第一个比这个人高的位置
### 另外 此题只要让这个人向左看就可以得出所有结果（不要往左右同时看 不然很麻烦）
#### 下面看代码说话
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
int a[510000];
int q[510000];
long long top;
long long ans,l,r;//ans要开long long 否则会WA
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d",a+i);
	}
	top=1;//top为单调队列的长度
	q[1]=a[1];//第一个加入队列
	q[0]=1231233;//注意 左端点设置一个较大的数 保证队列的位置为1,2,3...
   //从2往后搜 因为第一个人不会看到任何人
	for(int i=2; i<=n; i++) {
		l=0;
		r=top;
      //二分队列
		while(l<=r) {
			int mid=(l+r)>>1;
			if(q[mid]<=a[i])//高度相等时也可以看到
		        r=mid-1;
                      else l=mid+1;
		}
      //二分后的l表示这个人的高度应该排在第几位，r表示第一个比这个人高的位置
              if(r==0)//前面的单调队列最高的人都没有比这个人高时
			ans+=top;//这个人可以看到前面所有人
		else//有比他高的时候
			ans+=(top-r+1);//
         这个r人可以看到比他高的第一个人但不能看到更高的人
		while(q[top]<a[i])//入队条件 把比他矮的都剔除掉
			top--;
		q[++top]=a[i];//最后会减到比他大或等于的位置 top++后在入队
	}
	printf("%lld\n",ans);
	return 0;
}
```
### 希望对各位~~dalao~~有所帮助

---

## 作者：RPChe_ (赞：4)

看了题解，发现大佬们大多用了单调栈+pair维护或单调栈+二分查找的方式，但是，此题可以用
## 两个单调栈
来求解。

------------

首先，读完题，我们发现此题要找一个人左右两边第一个比他大的数，那么自然想到单调栈。第一次我只维护了一个单调栈，结果样例都过不了。考虑到题目说的是的左右两边，我就又加了一个单调栈。

对于每一个单调栈，分别从数据的左右两边开始处理，对应计算的分别是每一个人可以看到他左边的几个人的和他可以看到他右边的几个人，期间维护其单调递增。因为每一个单位会被第一个比他高的那个人挡住视线，所以每当有一个人被从栈里弹出，他就会被当前这个人挡住视线，也就是看不到后面的人了。如果有人被从栈里弹出，就把答案累加1。

然而我们还是过不了样例。这是因为我们没有计算高度相同的情况。但是我们又不能弹出与当前这个人高度相同的人，因为他并不会被当前这个人遮挡，那怎么办呢？这时候，我们只需要累加答案就可以了，因为高度相同的不会相互遮挡，而需要累加的则是之前跟这个人高度相同的人的总数。这样就可以AC此题了。

因为元素不会重复入栈，所以时间复杂度为O(n)。

需要注意的是为了避免重复累加，累加操作只在一个栈中执行一次。

最后，抬上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<stack>//个人喜欢STL
using namespace std;

inline long long read() {
	long long f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-f;ch=getchar();}
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}

inline void write(long long x) {
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

long long n,h[500005],ans,c[500005];

void left_maxx() {
	stack<int> s;
	for(int i=1;i<=n;i++) {
		while(!s.empty()&&h[s.top()]<h[i]) s.pop(),ans++;
		if(!s.empty()&&h[s.top()]==h[i]) c[i]+=c[s.top()]+1,ans+=c[i];//为了避免回溯查找，浪费时间，可以直接记一下数，累加的时候把上一个人累加的数算上，再加1就行。
		s.push(i);
	}
}

void right_maxx() {
	stack<int> s;
	for(int i=n;i>=1;i--) {
		while(!s.empty()&&h[s.top()]<h[i]) s.pop(),ans++;
		s.push(i);
	}
}

int main() {
	n=read();
	for(int i=1;i<=n;i++) h[i]=read();
	left_maxx();
	right_maxx();
	write(ans);
	return 0;
}
```


---

## 作者：functionendless (赞：3)

我并没有用单调栈，但思想跟单调栈近似

维护nxt[i]表示i之后最近的一个大于等于h[i]的人

那么对于点i，只要不停地向后找它的nxt直到h[nxt[j]]>h[i]就可以了

具体实现见代码（还是有些细节要注意的）

```cpp
#include<cstdio>
#include<cstring>
#define N 500010
using namespace std;
int a[N],nxt[N],n,ans=0;
int main()
{
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    for(i=1;i<n;i++) nxt[i]=i+1; nxt[n]=0;
    for(i=n;i>=1;i--)
    {
        for(j=nxt[i];j;j=nxt[j])
        {
            if(a[j]<a[i]) ans++; 
            else break;
        }
        nxt[i]=j;
        while(a[j]==a[i]) {ans++; j=nxt[j];}//由于相等的也满足条件，但因为维护nxt的性质所以在这处理
        if(j) ans++;//第一个大于的也可以(自己脑补一下就知道了)
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：q17770027225 (赞：2)

蒟蒻又来~~水~~题解了。

这道题单调栈的具体做法可以参考楼上，由于加了三个~~毒瘤~~数据，这道题ac后面三个点的核心操作就是对重复元素的处理，~~本来想卡常过~~，重复元素不能随便删，但是如果出现大量的重复元素，每次都去遍历一遍的话就会非常浪费时间，因此可以搞一个二维的单调栈，一维存高度，二维存数量，就可以愉快地删重复元素了,用数组版的单调栈方便查看栈中元素及调试。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
ll n,x,a[maxn],h[maxn],ans=0;
ll q1[2][maxn];
int f1=1,r1=0;
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}

int main()
{
	//ios::sync_with_stdio(false);
	n=read();
	for(int i=1;i<=n;i++) h[i]=read();
	q1[0][++r1]=h[1],q1[1][r1]=1;
	for(int i=2;i<=n;i++)
	{
		int t=1;
		while(r1>0&&q1[0][r1]<=h[i]) 
		{
			if(q1[0][r1]==h[i]) t+=q1[1][r1];
			ans+=q1[1][r1];r1--;
		}
		if(r1>0) ans++;
		q1[0][++r1]=h[i];q1[1][r1]=t;
	}
	printf("%lld\n",ans);
} 

```
后面三个点大概是20ms左右，可见重复元素之多，数据之毒瘤（逃）


---

## 作者：傅思维666 (赞：1)

## 题解：

首先看到这题，一个绝对暴力的思路是一一枚举所有组合，然后对于每一个组合，判断一下这俩人是不是可以互相看见。然后累加ans。

肯定是T了，别想了。

但是我们可以通过刚刚的暴力思路进行画图模拟来得出一些更深刻的结论：显然地，如果从某一个人开始向右查找，碰到一群比他矮的，那么这些比他矮的和他自己就是合法的对。但是如果突然碰到一个比他高的，那即使后面还有若干的人比他矮，那也GG，因为这个高的阻挡住了所有的视线。

恍然发现要维护一个具有单调性的队列。于是我们考虑单调队列/单调栈，这道题用单调队列是不行的，因为单调队列是一个先进先出的数据结构，显然和本题题意不符。所以我们用单调栈再考虑一下：我们从队列的第一个人开始，维护一个单调递减的栈，当一个新的元素入栈的时候，显然，他可以看到当前在栈中所有比他矮的人，那就开始按单调栈的操作逐一弹栈，然后一直更新答案。这道题的思路就出来了。

如此写完，WA。

原因有两个：

第一个，如果碰到和其身高相等的咋办？

新开一个变量来记录有几个（包括自己）相等的。同时累计答案，最后再把所有相等的压回去即可。

第二个，注意，如果比他矮的和相等的都弹掉之后，栈还不为空，那么还要加上1.为什么呢？因为如果这个人是比他高的第一个人，那么他俩还是可以互相看到的，而这个人后面的就不行了。

开写，TLE三个点（超级数据）

为啥子会T呢？

这三个数据之所以区别于其他的数据，就是因为特殊构造了很多相等的人。按照我们刚才的思路，统计完了再一一压回去，实在是太慢！所以我们考虑在弹栈的时候累计，最后一起压回去。具体是，开一个二元组，第一维统计身高，第二维统计这个身高的人数，这样在每次弹栈的时候就可以搞很多个人，在某种程度上（可能只针对这3组故意构造的数据）优化了时间。



代码：

```cpp
#include<stack>
#include<cstdio>
using namespace std;
typedef pair<int,int>par;
typedef long long ll;
ll ans;
int n;
stack<par>s;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		int x;
		scanf("%d",&x);
		par p=make_pair(x,1);
		while (!s.empty()&&x>=s.top().first)
		{
			if (s.top().first==x)
                p.second+=s.top().second;
			ans+=s.top().second;
			s.pop();
		}
		if (!s.empty())
            ans++;
		s.push(p);
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P1823)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;就是一道单调栈的题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们只考虑一个人作为一对人的右边那个的情况。从左到右扫描这些人，并且维护一个单调递减的栈。当扫描到第$i$个人的时候，我们把单调栈中所有比他矮的人都弹掉；根据单调栈的性质，我们知道这些人和第$i$个人都可以互相看到，所以我们弹几次答案就加几次。当栈顶的人比他高的时候，我们就把当前的人塞到栈里面。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们还用一个$cnt$数组来维护栈里的每一个位置上身高相同的人的数量。如果栈顶的人和第$i$个人一样高，根据题意，栈里跟$i$一样高的人都可以看到$i$；另外，这一排身高相同的人后面的那位（是一个人）也可以看到$i$。然后$cnt$的对应位置需要增加。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;按此模拟即可。
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const int MAXN = 500005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

int sta[MAXN], top;
int h[MAXN], cnt[MAXN];
int N;

int main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ ) read( h[i] );
	LL res = 0;
	top = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		while( top && h[sta[top]] < h[i] )
			res += cnt[top], cnt[top] = 0, top --;
		if( h[sta[top]] == h[i] )
		{
			res += cnt[top];
			if( top - 1 ) res ++;
			cnt[top] ++;
		}
		else
		{
			if( top ) res ++;
			sta[++top] = i, cnt[top] = 1;
		}
	}
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Thaumaturge (赞：1)

都是单调栈，都是单调栈！就没有人想到用堆这种傻傻的数据结构去做吗？？？qwq

可能思想和单调栈相近吧。。。反正我不知道单调栈是什么东西

具体实现方法：小根堆 + 链表

### （ Warning：以下内容将会把“数”,“身高”,“人”混为一谈，前自行理解）

对于两个人：他们可以看到彼此，当且仅当中间的人没有比他们高的人。这也就是说，我们从这个人开始往右，往左寻找，如果有比他大的，说明它们之间一定能看到，组数+1

也就是说，我们可以依次枚举每个人，如果他左边有人比他高，组数+1，如果右边有人比他高，组数+1，及时退出即可

但是，这显然不够，这样就变O(n^2)了，这并不是我们想要的。也就是说，对于一个数，我们需要快速检测它的右边或左边是否有比它大的数！

这很好办！我们可以用一个链表和一个小根堆来解决它：由于我们从小的数开始取，因此我们之前检索过的数，都比当前检索的数小，所以检索完一个数后，我们就把他从链表中删去即可，如果他左边或右边没有数了，组数就不再+1，这个实现，思路都应该较为简单，不再赘述。

没问题，但是这样就连样例也过不了

这是因为：我们没有考虑到两个数相等的情况，如：

4 2 1 2 5

我们会分别检索a[2]，a[3]，而组数+4而不是+5。其实a[2],a[5]可以看到彼此，但我们并没有把它们统计起来，因为我们默认2的左边或右边至多有一个人可以看到他，如果这样，数列中就不会有相等的数了

其实这个问题也很容易就能解决：两个身高相等的人能看到彼此，说明他们在目前的链表中是相邻的，如果不相邻，就意味这他们中间有比他们高的人，所以才看不到。

这就好了，每次我们取数时，在取最小的数的前提下，把相邻的数全部取完即可，若取了n个，容易知道，产生组数就是(n-1) * n/2 。当然，如果这些数的左边不为空，说明这些人的左边一定有比他们高的，这样又会产生n组能够互相看到的人了，右边也是一样的

这样就可以写了：

```cpp
#include <bits/stdc++.h>//我不喜欢压行

using namespace std;

priority_queue < pair < int , int >  > q;
int n[550000],i,j,m,xx,hc;
long long ans;
int beginn;

struct list{
	int l,r;
}a[550000];

int main(){
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&n[i]);
		q.push(make_pair(-n[i],-i));//这里把下标取反，就能保证身高一样时，下标是从小到大开始取的，对于链表，就能保证他是从左到右取而非从右到左取
		a[i].l=i-1;//链表初始化
		a[i].r=i+1;
	}
	while(!q.empty())
	{
		xx=-q.top().second;

		q.pop();
		a[a[xx].r].l=a[xx].l;//删数
		a[a[xx].l].r=a[xx].r;//删数

		if(n[xx]==n[a[xx].r])//一次性取完所有相同的数
		{
			beginn=xx;
			hc=0;
			while(n[xx]==n[a[xx].r]&&(!q.empty()))
			{
				hc++;
				ans+=hc;//原来取了n个数，每多取1个，就会新产生n个组数，同时n++;
				xx=-q.top().second;
				q.pop();

				a[a[xx].r].l=a[xx].l;//删数
				a[a[xx].l].r=a[xx].r;//删数
			}
			if(a[beginn].l!=0)//如果左边有比他们高的，加上
			ans+=hc+1;
			if(a[xx].r!=m+1)//如果右边有比他们高的，加上
			ans+=hc+1;
			continue;
		}

		if(a[xx].l!=0)//左边有比他高的，加上
		ans++;
		if(a[xx].r!=m+1)//右边有比他高的，加上
		ans++;
	}
	printf("%lld",ans);
	return 0;
}
```

管理员大大给过qwq

---

## 作者：兴安黑熊 (赞：1)

本题考虑单调队列，涉及重复的元素处理，使用一个结构体就行，也有人用pair也行。
定义结构体
struct sa
{
    int v;//存值
    int di;//存重复度
}vis[N];
    
    考虑下面5个数字：
    
          

------------
   输入的值     3   2   2   2   5
    
   重复度数     0   0   1   2   0
   
   入栈计数     0   1   1   1   0   
   
   出栈计数    1    1   2   3   0
   
   
   答案：    10
   
------------

   算法策略：
   
   (1)新来的元素大于和等于队首值，则队首元素要出栈，出栈的时候要加1；
   
   (2)入栈的时候，如果栈里不为空的话（还有元素，构成一个有序对），也要加1；
   
   (3) 出栈时，结果还要加上出栈元素的重复度。
   
  (4) 在纸上好好画画，就懂了！
  
  (5) 本题卡int,所以要long long
  
  
  下面见代码：
  
  ```cpp
#include<cstdio>
#include<algorithm>
#include <stack>
using namespace std;
const int N=5e5+5;
struct sa
{
    int v;
    int di;//重复度
}vis[N];
stack<sa>dis;
int n;

int main()
{int tmp,du=0;
long long ans=0;
scanf("%d",&n);
scanf("%d",&tmp);
dis.push({tmp,0});
for(int i=2;i<=n;i++)
{    du=0;
    scanf("%d",&tmp);
    while(!dis.empty()&&tmp>=dis.top().v)
    {
        if (tmp==dis.top().v)
          du=dis.top().di+1;

        ans+=1;
        ans+=dis.top().di;
        dis.pop();

    }
    if (!dis.empty())
        ans++;
    dis.push({tmp,du});

}
  printf("%lld\n",ans);



    return 0;
}

```
  
  
  
  
  
   
   
    

---

## 作者：小黑AWM (赞：1)

## **STL Upper_bound Lower_bound大法好！**
### 回到本题，由于要一对人能够互相看见，必须保证两者之间没有一个高的人阻挡了其中的一个人才能够相互看见，加上是一条队伍，所以我们可以考虑单调栈，保证栈中单调递减，那么就可以轻易判断有几对人可以相互看见（只要看栈顶是不是小于等于他不就行了，还有第一个比他高的也可以看见）。

想到这里，暗笑，那不是处理起来很简单，一个一个点人头好了。

然而~~毒瘤的管理员~~加强了这题的数据(还删了重题4333)。所以当一条队伍每个人的身高都相等的时候，一个一个点的朴素算法会被卡成O(n*n)，我们的目的是在单调栈中找到第一个比他高的，并且维护单调栈的性质，那么考虑二分找到第一个比他高的，再二分第一个比他小的，这样就成功的把复杂度控制在了O(nlgn)还是能过的。

然而本蒟蒻真的是太菜了……导致写不好二分的边界处理😭

拿起我们伟大的武器upper_bound 和 lower_bound(虽然经常被卡，但是做题的时候用O2优化一下问题不算很大)

```
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
long long n,stack[500500],s,top,height;
int main(){
    cin>>n;
    cin>>height;
    stack[++top]=height;
    for(int i=1;i<n;i++){
        cin>>height;
        if(height<stack[top])s++,stack[++top]=height;
        else{
            int pos=lower_bound(stack+1, stack+1+top, height,greater<int>())-stack;//最终放弃手写二分,最后减去头指针的话返回值就不是迭代器而是两个迭代器的地址的差值,也就是数组下标,这样找到了第一个小于/等于他的在栈中的数,所以第一个比他大的数应该就是这个数再往前一个
            if(pos>1)//由于当在栈底时前面没有了,所以不用往前
                pos--;
            s+=top-pos+1;//top到pos的人这个新来的都可以看到
            top=upper_bound(stack+1, stack+1+top, height, greater<int>())-stack;//找到第一个比他矮的人,把比他矮的人都挡住了所以直接就可以出栈
            stack[top]=height;
        }
    }
    cout<<s;
    return 0;
}

```

---

## 作者：iodwad (赞：1)

单调栈。

题目意思是指两个人中间没有一个人比某一个人高就能互相看见（语文不好要人命

所以如果一个人之后出现了一个比他还高的，他就不可能再与后面的某个人互相看见。

所以维护一个单调栈，栈内高度单调不上升，每次可以先与栈内所有小于等于当前高度的人互相看见，如果弹出操作完成后栈非空，还可以与栈顶互相看见。

但是有重复元素，所以栈内存个 `pair`

```cpp
#include <iostream>
#include <cstdio>
#include <stack>

typedef long long LL;
#define int LL

const int MAXN = 500000;

int n, ans, Top;
int a[MAXN | 1];
std::stack < std::pair < int, int > > sta;

inline int read() {
	register int x = 0;
	register char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) {
		/*
		while(Top > 0 && a[sta[Top]] < a[i]) --Top, ans += 1LL;
		if(Top) ans += 1LL;
		sta[++Top] = i;
		*/
		std::pair < int, int > nowP = std::make_pair(a[i], 1);
		while(!sta.empty() && sta.top().first <= a[i]) {
			std::pair < int, int > tmp = sta.top();
			sta.pop();
			if(tmp.first == a[i]) nowP.second += tmp.second;
			ans += tmp.second;
		}
		if(!sta.empty()) ++ans;
		sta.push(nowP);
	}
	printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：fighter_OI (赞：1)

提高二题难度。思维性较高。

#solution1：模拟，爆搜

对于每个左右端点，判断开区间内的最大值是否小于等于左右端点。

时间复杂度：O（n^3）

```cpp
uses math;
var s,i,j,n,tot,x:longint; a:array[0..500000] of longint;
function cz(l,r:longint):longint;
var i:longint;
begin
 cz:=a[l];
 for i:=l+1 to r do
     cz:=max(cz,a[i]);
end;
begin
 read(n);
 tot:=0; s:=0;
 for i:=1 to n do read(a[i]);
 s:=0;
 for i:=1 to n-1 do
     for j:=i+1 to n do
         begin
          if i+1=j then begin inc(s); continue; end;
          if cz(i+1,j-1)<=min(a[i],a[j]) then inc(s);
         end;
 write(s);
end .
```
30分……

solution2：模拟，线段树

由于要求区间最大值，线段树上

（蒟蒻不会线段树……）

solution3：单调栈

维护一个不升的序列，具体细节自己理解

```cpp
uses math;
var s,i,j,n,tot,x,k:longint; a:array[0..500000] of longint;
begin
 read(n);
 tot:=0; s:=0; 
 for i:=1 to n do
  begin
   read(x);
   k:=tot;
   while (k>0)and(a[k]<=x) do begin inc(s); dec(k); end;
   if k>0 then inc(s);
   while (tot>0)and(a[tot]<x) do dec(tot); 
   inc(tot); a[tot]:=x;
  end;
 write(s);
end .
```

---

## 作者：不存在之人 (赞：0)

考虑$A$怎么看到左边的人:
1. $A$一定能互相看到左边第一个比他高的人。 
2. $A$可以看到左边单调递减区间的人。

这个东西维护一个单调递减的单调栈就好了。

然后对于相同高度的，我们可以缩点分类讨论一下记录块中的$size$。

只有$A$这个块中最左边的人能向左一览无余单调递减区间。而遇到比他高的人$A$整块都会看到。

如果碰到高度相同的人，显然两两都能看到，然后最后合并$size$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>par;
typedef pair<par,ll>pii;
const ll INF=2e18;
const int MAXN=8e5+5;
#define mp make_pair
par a[MAXN];
pii sta[MAXN];
ll cnt=0,n,top=0,ans=0,recalc=0;
int main()
{
    scanf("%lld",&n);
    recalc=n-1;
    for(int i=1;i<=n;i++)
	{
        ll tmp;
        scanf("%lld",&tmp);
        if(tmp!=a[cnt].first) a[++cnt]=mp(tmp,1);
        else a[cnt].second++;
    }
    for(int i=1;i<=cnt;i++)
	if(a[i].second>2) recalc+=(a[i].second-1)*(a[i].second-2)/2;
    for(int i=1;i<=cnt;i++)
	{
        int flag=0;
        while(top&&sta[top].first.first<=a[i].first)
		{
            if(sta[top].first.first==a[i].first)
			{
                ans+=sta[top].first.second*a[i].second;
                flag=sta[top].first.second;top--;
                break;  
            }
            ans+=sta[top].first.second;
            if(i>1&&i-1==sta[top].second) ans--;
            top--;  
        }
        if(top) ans+=a[i].second;
        if(top&&sta[top].second==i-1) ans--;
        if(flag) a[i].second+=flag;
        sta[++top]=mp(a[i],i);
    }
    printf("%lld\n",ans+recalc);
    return 0;
}
```

---

## 作者：FFFFFFFHHHHHHH (赞：0)

注意等于的情况即可  数据改了增加一个数量维度防止最后三个点超时	
```cpp
#include<bits/stdc++.h>
using namespace std;
//input by bxd
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define repp(i,a,b) for(int i=(a);i>=(b);--i)
#define RI(n) scanf("%d",&(n))
#define RII(n,m) scanf("%d%d",&n,&m)
#define RIII(n,m,k) scanf("%d%d%d",&n,&m,&k)
#define RS(s) scanf("%s",s);
#define ll long long
#define pb push_back
#define REP(i,N)  for(int i=0;i<(N);i++)
#define CLR(A,v)  memset(A,v,sizeof A)
//////////////////////////////////
#define inf 0x3f3f3f3
const int N=1000000;
int sta[N];
struct node
{
    int cnt,v;
};
int main()
{
    stack<node>sta;
    ll ans=0;
    int n;
    RI(n);
    int pos=0;
    while(n--)
    {
        int x;
        RI(x);
        int t=1;

        while(sta.size()&&sta.top().v<=x)
        {
            if(sta.top().v==x)t+=sta.top().cnt;
            ans+=sta.top().cnt;
            sta.pop();
        }
        if(sta.size())ans++;
      
        sta.push(node{t,x});
    }
    cout<<ans;
    return 0;
}

```


---

## 作者：LlLlCc (赞：0)

这题是很经典的单调栈啊。

数据是500000，nlogn也能过（好像前面的题解都是nlogn的），其实数据还能再加强点，这样就只能o(n)的单调栈过了。（亲测时间为nlogn的1/5）

------------
进入正题

## 题目大意：

  求出组合A,B，（**A，B直接不存在严格大于A或B**）有多少组。
  
------------
## 1.暴力：
  好的方法都是建立在暴力的基础上的，只有想通了暴力才有可能得出正解。暴力还是比较好想的，N方枚举每个人，看看他们之间有没有比他们大的就好了。
  
## 2.单调栈 （O（n））

  举个例子：1 2 3
  
  看看这个例子，发现当枚举i（1）时，只有后面（2）有比他大的，再后面（3）的他就看不到了。这就让我们想到了单调栈，**只要一个元素出栈了，那么接下来就没他什么事了**（这也是单调栈时间复杂度O(n)的原因，因为每个元素只会入栈一次，出栈一次）。
  
  具体单调栈的操作，其他的题解已经讲的很清楚了，我就来讲讲怎么把那层多余的二分查找（logn）给去掉.
  
  因为单调栈是保持单调的，越靠近栈顶的值越小，所有为了保持单调性每枚举到的值就往下压，对比和栈顶那个大，如果大于栈顶，top（栈的高度）减1。当不能再往下压时，如果栈内还有元素，说明这两个人是可以看到的（中间不存在大于他们的元素了），ans++。
  
  这里有个优化，当该元素等于栈顶元素时，就把栈顶元素的积累次数+1，不用再站一位了。
  
  还有一个坑点，这题要开**long long**
  
  具体看代码体会吧：
  
  ```
#include<bits/stdc++.h>
#define ll long long
#define maxn 10000005
using namespace std;
ll n,a[maxn],top,x,ans;
struct lc{
	ll x,tot;
}Q[maxn];
inline ll read(){
	ll ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++){
		while (top&&a[i]>a[Q[top].x]) ans+=Q[top].tot,top--;
		if (a[i]==a[Q[top].x]){
			ans+=Q[top].tot;Q[top].tot++;
			if (top>1) ans++;
		    continue;
		}
		if (top) ans++;
		Q[++top].x=i,Q[top].tot=1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

