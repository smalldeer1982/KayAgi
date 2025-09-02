# [POI 2013] USU-Take-out

## 题目描述

Little Edna has received the take-out game as a present.

Take-out is a single player game, in which the player is given a sequence of $n$ adjacent blocks, numbered from $1$ to $n$.

Each block is either black or white, and there are $k$ times as many white    blocks as there are black ones.

The player's goal is to remove all the blocks by certain permissible moves.

A single move consists in removing exactly $k$ white blocks and a single    black block without changing the positions of other blocks.

The move is permissible if there is no "gap" (a space left by    a previously taken out block) between any two blocks being removed.

Help poor little Edna in finding any sequence of permissible moves that    remove all the blocks.

有n块砖，其中白色是黑色的k倍，求一个消除序列，满足以下条件：

每次消除k+1个砖，其中k块白色，1块黑色，并且这k+1块砖从开始到结束，中间不能路过已经消除过的砖

数据保证有解


## 说明/提示

有n块砖，其中白色是黑色的k倍，求一个消除序列，满足以下条件：

每次消除k+1个砖，其中k块白色，1块黑色，并且这k+1块砖从开始到结束，中间不能路过已经消除过的砖

数据保证有解


返回`TAT1`：同一个位置输出$2$次

返回`TAT2`：输出的$k+1$个位置不满足白色是黑色$k$倍

返回`TAT3`：未按照升序输出或者中间路过已经消除的砖

SPJ provided by @colazcy

## 样例 #1

### 输入

```
12 2
ccbcbbbbbbcb
```

### 输出

```
1 8 12
2 6 7
3 4 5
9 10 11
```

# 题解

## 作者：Taduro (赞：12)


## 题意：

​	有n块砖，其中白色是黑色的k倍，求一个消除序列，满足以下条件：每次消除k+1个砖，其中k块白色，1块黑色，并且这k+1块砖从开始到结束，中间不能路过已经消除过的砖。要求你输出方案，数据保证有解。


## 思路：

​	一开始的想法是分治，就是从中间随便掏出符合要求的一段，之后再去做两边的，倒序输出。但很快发现这个方法不行，首先是时间受不了，其次是在中间先取相当于把两边断开，破坏了很多可行的方法。

​	对于断开序列的问题可以这样解决：把每次找到的砖删掉，再重新跑一遍，直到删光。那就是一个                      $N^2$ 的枚举了，跟分治差不多快但至少正确。

​	手动模拟一下这个过程，发现我们做了很多无用功，比如循环要删除砖块前面那些砖块被循环了多次。而开一个栈可以很好的解决这个问题，当栈顶有$k+1$个元素并只有一个'c'是，将他们全部弹出储存到输出中即可。

## 代码：

```c++
#include<cstdio>
#include<iostream>
using namespace std;
char a[1000001];
int n,top,sum[1000001],stack[1000001];
int k,cnt,ans[1000001];
int main(){
	scanf("%d%d%s",&n,&k,a+1);
	for (int i=1; i<=n; i++){
		stack[++top]=i;
		sum[top]=sum[top-1]+(a[i]=='c');
		if (top>=k+1&&sum[top]-sum[top-k-1]==1){
			for (int j=top; j>=top-k; j--){
				ans[++cnt]=stack[j];
			}
			top=top-k-1;
		}
	}
	for (int i=n; i>=1; i--){
		printf("%d ",ans[i]);
		if (i%(k+1)==1) puts("");
	}
	return 0;
}
```

---

## 作者：xkcdjerry (赞：9)

[更差的阅读体验](https://www.luogu.com.cn/blog/spinning-xkcdjerry/solution-p3551#)

一道好题，刚开始正着想死活想不出来，最后想到正难则反，考虑最后一段一定是连续的（否则一定不合法），而假如最后一段被删除了倒数第二段也是连续的，所以结构应该类似一棵树，以样例为例，也可以这么划分：  
```
10 11 12 
1 8 9 
2 6 7 
3 4 5 
```
对应的是：
```
[c[c[bcb]bb]bb][bcb]
```
联系如何构造树的结构和删除后前后需要连接上可以想到使用栈来维护，每次将一个字符压入栈中，如果最后 $k+1$ 个中恰好有一个 `c`，那么弹出这 $k+1$ 个（对应在原串中删除）并且记录弹出了哪些位置。由于连续段是**最后一个**选的却是最先被扫处来的，所以弹出的顺序应该倒过来。  

正确性证明：  
假如有解，那么这么构造能够找到这个解的一个合法最后一步，而去除最后一步以及其相关的字母之后会变成一个一模一样而且规模更小的问题，可以对其使用相同的论证直到问题规模降为 $0$。所以显然保证正确性。

时间复杂度：  
每个字母共 $n$ 个会恰好被插入 $1$ 次，弹出 $1$ 次，总时间为 $O(n)$。  
且每弹出 $k$ 个点会花 $O(k)$ 的时间重新计算 `c` 的数目，由于保证有解会恰好弹出 $\frac{n}{k+1}$ 次，总时间为 $O(k \times \frac{n}{k+1})=O(n)$。  
所以整个程序的复杂度为 $O(n)$。

上代码（为截至 2021 年 12 月 20 日的最优解）：
```c++
#include <cstdio>
#define N 1000010
int n,k;
int f[N],g[N];
char s[N];
//top：栈顶
//black：最近k+1个中有几个c
//kk：一维数组模拟二维数组的辅助变量
int top,black,kk;
int main()
{
    scanf("%d%d%s",&n,&k,s+1);
    for(int i=1;i<=n;i++)
    {
        f[++top]=i;
        //维护最近k+1个中的c数目
        black+=(s[i]=='c');
        if(top>k+1) black-=(s[f[top-k-1]]=='c');
        //处理匹配
        if(top>k&&black==1)
        {
            //弹出k个并记录
            for(int j=0;j<=k;j++) g[kk+j]=f[top-j];
            kk+=k+1;
            top-=k+1;
            //重新维护c的数目
            black=0;
            for(int j=0;j<top&&j<=k;j++) black+=(s[f[top-j]]=='c');
        }
    }

    for(int i=kk-k-1;i>=0;i-=k+1)
    {
        //记得输出编号的时候反向
        for(int j=k;j>=0;j--) printf("%d ",g[i+j]);
        putchar('\n');
    }
}
```

[评测记录](https://www.luogu.com.cn/record/65476596)

注意点：
* 题目只保证 $k<n$，所以不能开 $k \times k$ 的矩阵，本人是使用了一个一维数组来模拟二维矩阵，实际上也可以动态分配 $ \frac{n}{k+1} \times k$ 的矩阵但是会[慢一些](https://www.luogu.com.cn/record/65471914)
* 由于栈是按字符串顺序压入的所以从顶向下弹出的时候会反向，由于题目要求升序输出输出的时候还需要再反向一遍

说句闲话，看到这段代码跑的时间我感觉数据范围开到 $10^7$ 甚至 $1.5 \times 10^7$ 都行，还是出题人太仁慈了（雾）

---

## 作者：kczno1 (赞：8)

逆向思考。

最后选择的一定是一段连续的区间，

否则中间就是已经选择过的。

之后删掉这段区间，就可以递归处理。

同时，可以发现，只要满足白色是黑色的k倍，就一定有解。

只要证明可以选择一段连续的区间即可，因为之后是递归的。

如果不存在，则每个黑色相邻的白色都<k，那么白色总数就<k\*黑色，矛盾。

```cpp
#include<bits/stdc++.h>

#define N 1000100
char ch[N];
int s[N],pre[N];
bool qb[N<<1],*b=qb+N;int now;
int st[N],top;

int main()
{
    freopen("1.in","r",stdin);
    int n,k,i,j,x;scanf("%d%d",&n,&k);
    scanf("%s",ch+1);
    b[0]=1;
    for (i=1;i<=n;++i)
    {
        s[i]=(now+=(ch[i]=='b')?-1:k);
        if(b[now]) 
        {
            for(x=i,j=1;j<=k+1;++j,x=pre[x]) b[s[st[++top]=x]]=0; 
            pre[i+1]=x;
        }
        else pre[i+1]=i;
        b[now]=1;
    }
    while (top) 
    {
        for (i=1;i<=k+1;++i) printf("%d ",st[top--]);
        printf("\n");
    }
}
```

---

## 作者：DYYqwq (赞：5)

这东西。。好难想。。

本来以为是类似于区间 dp 的东西，推式子推半天，结果题解告诉我是正难则反？！！

考虑对于把序列左右断开的做法：把符合条件的直接删去，一点一点删，直到没有了。

好消息：虽然很慢，但是是正确的。

坏消息：$O(n^2)$ 也太慢了！

考虑哪里做了些唐事。

我们找到目标方块之前搜索了太多块了！

考虑用栈维护。不断将字符压入栈，如果最后 $k+1$ 有且只有一个  `c`，那么把这些东西删掉（弹出）。

每个字母只有一次出栈入栈机会。而且算 `c` 数量的时间也是 $O(n)$ 的。因此总时间复杂度为 $O(n)$。

其实还是很简单嘛，下次不要做不出来了噢 qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n , k , c[1000010] , q[1000010] , ans[1000010] , tp , cnt;
int main()
{
	scanf("%d%d" , &n , &k);
	cin >> s;
	s = '_' + s;
	for(int i = 1 ; i <= n ; i ++)
	{
		q[++ tp] = i;
		c[tp] = c[tp - 1] + (s[i] == 'c');
		if(c[tp] - c[tp - k - 1] == 1 && tp >= k + 1)
		{
			for(int j = tp ; j > tp - k - 1 ; j --) ans[++ cnt] = q[j];
			tp -= (k + 1);
		}
	}
	int ans_num = 0;
	for(int i = cnt ; i >= 1 ; i --)
	{
		printf("%d " , ans[i]);
		if(++ ans_num == 3) puts("") , ans_num = 0;
	}
	return 0;
}
```

---

## 作者：Acerkaio (赞：5)

有 n 块砖，其中白色是黑色的 $k$ 倍，求一个消除序列，满足以下条件：

每次消除 $k+1$ 个砖，其中 $k$ 块白色，$1$ 块黑色，并且这 $k+1$ 块砖从开始到结束，中间不能路过已经消除过的砖。

### 解析：

倒退法！

先找连续且只包含一个黑色块的序列，因为在最后时刻只能选择连续的序列。

如样例：
```
c  c  b  c  b  b  b  b  b  b  c  b
1  2  3  4  5  6  7  8  9  10 11 12
```
那么在第一个连续且只包含一个黑色块的序列 $[3,5]$ 可以存起来，并把它从原序列删去可得新序列：
```
c  c  b  b  b  b  b  c  b
1  2  6  7  8  9  10 11 12
```
如同原来做法删去 2 6 7。

发现了什么——我们通过倒退法跨过正顺序做法的最后要删除的序列，且满足每次消除 $k+1$ 个砖，其中 $k$ 块白色，$1$ 块黑色，并且这 $k+1$ 块砖从开始到结束，中间不能路过已经消除过的砖。

以上为皆思路，要实现它，可以用到栈：我们将一直将数入栈，如果发现栈内有比 $k+1$ 多的数且满足这 $k+1$ 个数只有一块黑色块，那么出栈并存起（倒叙，至于为什么，因为后面要全部倒叙输出），一直到数字全入完栈且出完栈（数据保证有解）。

最后要倒叙输出，至于为什么，因为我们通过倒叙法作出，所得第一个序列其实是最后序列（所以题目其实根本不用按照升序输出，且可能只有这一种输出方式）。

# CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10101010];
int sum[10101010],q[10101010],ans[10101010];
int n,k;
int main()
{
	cin>>n>>k;
	cin>>s+1;
	int tot=0,num=0;
	for(int i=1;i<=n;i++)
	{
		tot++;
		q[tot]=i;
		if(s[i]=='c')
		{
			sum[tot]=sum[tot-1]+1;
		}
		else
		{
			sum[tot]=sum[tot-1];
		}
		if(sum[tot]-sum[tot-k-1]==1&&tot>=k+1)
		{
			for(int j=tot;j>tot-k-1;j--)
			{
				ans[++num]=q[j];
			}
			tot=tot-k-1;
		}
	}
	int js=0;
	for(int j=num;j>=1;j--)
	{
		++js;
		cout<<ans[j]<<" ";	
		if(js==3)
		{
			cout<<'\n';
			js=0;	
		}
	}
	return 0;
}
```


---

## 作者：Priori_Incantatem (赞：4)

[题目链接](https://www.luogu.com.cn/problem/P3551)

虽说是道绿题，但个人感觉思路不太好想

首先，我们假设可以路过已消除的砖块，并考虑用栈维护  
我们将元素（砖块）按顺序压入栈，每当压入一个元素，就检查栈顶 $k+1$ 个元素中是否恰好有一块黑色的砖。如果满足此条件，那么就将这 $k+1$ 块消掉。

把这个方案画成图就是这个样子

![image.png](https://img-blog.csdnimg.cn/img_convert/3fe93a5884f29473332fc299132e6692.png)

可以发现，这些不同颜色的弧是互相包含的，并且可以证明不会两弧交叉  
那么，我们把上面方案的操作顺序倒过来，满足先做**没有被包含**的操作。这样就不会经过已经被消除的块了。

这里感性理解一下为什么两弧不会交叉  
![image.png](https://img-blog.csdnimg.cn/img_convert/107a970ef6e059315abf8457dcd7adec.png)
显然，在进行红色操作时，$\text{B}$ 块肯定比 $\text{A}$ 块优先选，所以一定不会出现交叉的情况

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int Maxn=1000000+10;
vector <int> g[Maxn];
int a[Maxn],c[Maxn];
int sum[Maxn];
char s[Maxn];
int n,k,cnt,tot;
inline int lowbit(int x)
{
	return x&(-x);
}
void modify(int x,int k)
{
	while(x<=n)
	{
		sum[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x)
{
	int ret=0;
	while(x)
	{
		ret+=sum[x];
		x-=lowbit(x);
	}
	return ret;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	for(int i=1;i<=n;++i)
	if(s[i]=='c')a[i]=1;
	else a[i]=0;
	for(int i=1;i<=n;++i)
	{
		c[++cnt]=i;
		if(s[i]=='c')modify(cnt,1);
		if(cnt>k && query(cnt)-query(cnt-k-1)==1)
		{
			++tot;
			for(int j=1;j<=k+1;++j)
			{
				if(s[c[cnt]]=='c')
				modify(cnt,-1);
				g[tot].push_back(c[cnt--]);
			}
		}
	}
	for(int i=tot;i;--i)
	{
		for(int j=g[i].size()-1;j>=0;--j)
		printf("%d ",g[i][j]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：nofind (赞：3)

题意：https://www.luogu.org/problemnew/show/P3551

输出是每次去掉的块的编号

正着想DP实在不好想,因为考虑的太多。

逆向思维:最后取出的一定是一个连续的区间,把这个区间去掉后,倒数第二个取出的也是一个连续区间(最后一个区间的两端点合并后)

```
如样例：c c b c b b b b b b  c  b
        1 2 3 4 5 6 7 8 9 10 11 12
```

最后取出3 4 5 
```

问题就变成了:	c c b b b b b  c  b
       		1 2 6 7 8 9 10 11 12
```

现在取出的是:2 6 7

以此类推

于是开一个栈从前往后扫,等到栈顶top到top—k-1满足1黑k白时就弹栈取出,最后倒着输出即可

code(借鉴了网上的:https://www.cnblogs.com/zhoushuyu/p/9745613.html):

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int n,k,top,cnt;
int s[maxn],ans[maxn],sum[maxn];
char str[maxn];
inline int read()
{
	char c=getchar();int res=0,f=1;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') res=res*10+c-'0',c=getchar();
	return res*f;
}
int main()
{
	n=read(),k=read()+1;scanf("%s",str+1);
	for(int i=1;i<=n;i++)
	{
		s[++top]=i;sum[top]=sum[top-1]+(str[i]=='c');//num->black
		if(top>=k&&sum[top]-sum[top-k]==1)
		{
			for(int j=top-k;j<top;top--) ans[++cnt]=s[top];
		}
	}
	for(int i=n;i;i--) printf("%d%c",ans[i],i%k==1?'\n':' ');
	return 0;
}
```



---

## 作者：Anaxagoras (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P3551)

Update:2022.02.16 修改了一些错误

第一次过 P 开头的题解 QAQ

### 0x00 所需知识

1. 栈

1. 前缀和（只是略微涉及一点点）

### 0x01 思路

我们可以把字符一个一个压入栈，如果栈顶 $k+1$ 个刚好满足其中有 $k$ 块白色，$1$ 块黑色那么我们就储存答案并弹出它们。每个字符被压入、弹出各 $1$ 次，那么这就是一个 $\Theta(n)$ 的算法。

但是我们如果依次去检验栈顶元素就会变为一个 $\Theta(nk)$ 的算法，会 T 掉。那我们就可以用一个前缀和数组存下从栈底到栈顶一共多少块黑色，如果
`sum[i]-sum[i-k-1]==1`，即从`i`到`i-k`之间如果只有 $1$ 块黑色，剩下的 $k$ 块就都是白色，那么时间复杂度就从 $\Theta(k)$ 降成 $\Theta(1)$。

### 0x02 AC Code 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,top,rk;//top 为指向储存字符下标栈顶的指针，rk 为指向储存答案栈顶的指针
int s[1000005],sum[1000005],ans[1000005];//s 是储存字符下标的栈，sum 是前缀和数组，ans 是储存答案的栈
string st;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>st;
	for(int i=1;i<=n;i++)
	{
		s[++top]=i;
		if(st[i-1]=='c')//题目下标是从 1 开始的，但是 STL string 是默认从 0 开始的，所以要减 1
		{
			sum[top]=sum[top-1]+1;
		}
		else
		{
			sum[top]=sum[top-1];
		}
		if(top>=k+1&&sum[top]-sum[top-k-1]==1)//top>=k+1 是为了防止数组下溢
		{
			for(int j=top;j>=top-k;j--)
			{
				ans[++rk]=s[j];//储存答案
			}
			top=top-k-1;//出栈
		}
	}
	for(int i=rk;i>=1;i--)
	{
		cout<<ans[i]<<' ';
		if(i%(k+1)==1)
		{
			cout<<'\n';
		}
	}
	return 0;
}
```

这里再提供一种 STL 写法

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int>s;
stack<int>ans;
int n,k,len;
int sum[1000005];
string st;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>st;
	for(int i=1;i<=n;i++)
	{
		s.push(i);
		if(st[i-1]=='c')
		{
			sum[s.size()]=sum[s.size()-1]+1;
		}
		else
		{
			sum[s.size()]=sum[s.size()-1];
		}
		if(s.size()>=k+1&&sum[s.size()]-sum[s.size()-k-1]==1)
		{
			len=s.size();
			for(int j=len;j>=len-k;j--)
			{
				ans.push(s.top());
				s.pop();
			}
		}
	}
	len=ans.size();
	for(int i=len;i>=1;i--)
	{
		cout<<ans.top()<<' ';
		ans.pop();
		if(i%(k+1)==1)
		{
			cout<<'\n';
		}
	}
	return 0;
}
```

End

---

## 作者：SunburstFan (赞：1)

### P3551 [POI2013] USU-Take-out

#### 题目大意

有 $n$ 块砖，其中白色是黑色的 $k$ 倍，求一个消除序列，满足以下条件：

每次消除 $k+1$ 个砖，其中 $k$ 块白色，$1$ 块黑色，并且这 $k+1$ 块砖从开始到结束，中间不能路过已经消除过的砖。

#### 解题思路

这个问题看似很棘手：怎样保证中间不能路过已经消除过的砖块？

可以手模一下样例，就会发现，一个比较优的策略是先将取两边的砖块，最后取中间的砖块，但是这样很难实现。

这时候可以考虑反向思考，如果是按照这样的策略，那么最后一组序列就会是**在中间的一段连续区间**，根据这个突破口，我们不难得到以下做法：

维护一个栈，当栈顶有连续的一段区间中恰好满足白色 $1$ 个，黑色 $k$ 个的条件，就将这 $k+1$ 个元素弹出，依此类推，只要栈顶有连续 $k+1$ 个元素满足要求就弹出，最终将弹出的元素倒序输出就是正确方案。

判断满足要求可以将白色砖块赋值为 $1$，黑色砖块赋值为 $0$，再用前缀和维护。

```cpp
for(int i=1;i<=n;i++){
    stk.push(i);

    int top=stk.size();
    sum[top]=sum[top-1]+(s[i-1]=='c'); 

    if(stk.size()<k+1)continue;
    if(sum[top]-sum[top-k-1]==1){
        int j=0;
        while(j<=k){
            output.push_back(stk.top());
            j++,stk.pop();
        }
        //stk.pop_k(k+1);
    }
}

for(int i=output.size()-1;i>=0;i--){
    cout<<output[i]<<" ";
    if(i%(k+1)==0)cout<<"\n";
}
```

---

## 作者：zzyiqa (赞：1)

[原题戳这里](https://www.luogu.com.cn/problem/P3551)

# 题目大意：

有 $n$ 块砖，其中白色是黑色的 $k$ 倍，求一个消除序列，满足以下条件：

每次消除 $k+1$ 个砖，其中 $k$ 块白色，$1$ 块黑色，并且这 $k+1$ 块砖从开始到结束，中间不能路过已经消除过的砖。

数据保证有解。

# 前置知识：

~~只需要知道**栈**的基本用法。~~

# 思路：

这道题正着想不好想，那么考虑正难则反。很明显，对于最后消除的一组，他们一定是待在一起的。考虑接下来的，显然，再次消除的一组也是待在一起的（因为不待在一起就中间一定会有一个砖块隔着，又因为一定有解，所以它后来一定会被消除，那么就不符合消除的条件了）。这里以样例为例。（这里我用的我跑出来的样例，手玩一下也是正确的）。

```cpp
10 11 12
1 8 9
2 6 7
3 4 5
```

最后一组消除后很明显倒数第二组是待在一起的，随即倒数第三组也待在了一起，这样就保证了中间不会出现要被消除的。

推到这里，不难想到用栈维护。并且再维护一个数组表示当前栈里的黑色的数量的数组，如果满足 $k+1$ 个连续板砖中，只有一个黑色板砖，那么很明显，这一组可以消除。

# AC Code


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e6+5;
ll n,k,sum[N],a[N],top,cnt,ans[N];
string s;
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>k>>s;
	s=" "+s;
	for(ll i=1;i<=n;i++){
		a[++top]=i;//加入栈 
		sum[top]=sum[top-1]+(s[i]=='c');//统计栈内的关于黑色砖块的数量前缀和 
		if(top>=k+1 && sum[top]-sum[top-k-1]==1){//满足黑色砖块的数量为 1 
			for(ll j=top;j>=top-k;j--) ans[++cnt]=a[j];//将当前可行的方案加入 
			top=top-(k+1);//弹出 k-1 个 
		}
	}
	for(ll i=n;i>=1;i--){
		cout<<ans[i]<<" ";//输出 
		if(i%(k+1)==1) cout<<"\n";//每 k+1 个就完成消除了一组 
	}
	return 0;
}

```

---

## 作者：_shine_ (赞：0)

在最后一次消除操作时，所消除的显然是一个连续的区间（因为其他的砖块均被消除，但又不能跨过这些消除的砖块），显然可以使用栈来维护，原因如下：其他的虽然有可能并不是一个区间（即可能会跳着跳着选择），但其极左、极右断点所形成的区间显然是均未被消除的。

而使用栈来维护只需每次取出栈顶 $k+1$ 个扫一下，满足 $1$ 黑 $k$ 白即可。

注意方案需要倒序输出。
#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,k;int st[maxn],idx;
int sum[maxn],ans[maxn],ans_idx;
char s[maxn];
signed main(){
	cin >> n >> k;scanf("%s",s+1);
	for(int i=1;i<=n;++i){
		st[++idx]=i;
		sum[idx]=sum[idx-1]+(s[i]=='c');
//		cout << sum[idx] << " " << sum[idx-k-1] << " " << i << endl;
		if(idx>=k+1 && sum[idx]-sum[idx-k-1]==1){
			for(int j=idx;j>=idx-k;--j)ans[++ans_idx]=st[j];
			idx=idx-k-1;
		}
	}
//	puts("hi"); 
	for(int i=n;i>=1;--i){
		cout << ans[i] << " ";
		if(i%(k+1)==1)cout << endl; 
	}
	return 0;
} 
```

---

## 作者：zzzyyyyhhhhh (赞：0)

## 题意

给定一个 01 串，每次操作消除 $k$ 个 1 和 1 个 0 ,每次操作的涉及的最左和最右的字符中间不得有消除过的串，求消除方案。

## 分析

可以认为有两个约束条件。

1. 不得经过消除过的串。
2. 每次消 $k$ 个 1 和 1 个 0。

对于第二个条件，只要找出 $k$ 个 1 和 1 个 0 即可，难点在于第一个条件。



首先考虑划分成几个区间，从两边消到中间。



这时就会出现一个问题，每次的 $k$ 个 1 有多个位置可选，如果选择不当，下次消除 $k$ 个之后也有可能消不到一个 0。

比如这样 $(k=2)$。

> $\texttt{bbbbccccbbbbcbb}$

选择前两个，会发现两端没有 c 可选。

> $\texttt{xxbbccccbbbbcbb}$

也可能出现这种情况 $(k=2)$。

> $\texttt{bbbccbbccbbb}$

需要划分成两段。

> $\texttt{bbbccb | bccbbb}$

**所以考虑将这个过程反过来**  从中间往两边消，最后逆序输出答案，这样就避免了 1 条件的限制。



很明显，每次 $O(n)$ 找可消除的串再拼接要 TLE 了，于是考虑遍历一遍，对于每个位置 $i$ 考虑包括 $i$ 的前 $k+1$ 个未消除的字符能否消除。因为一定有解，所以这种方法可以消除完整个序列。



用一个栈维护 $i$ 前面未消除的字符，同时记录每个未消除字符前有多少 0 和 1，$i$ 前面的 0 1 数量直接从上一个字符转移，如果能消除则  pop $k+1$ 个元素。

> $\texttt{bbbccbbcb}$

> $\texttt{bbb}$

> $\texttt{bbbc -> bxxx}$

> $\texttt{bxxxcb}$

> $\texttt{bxxxcbb -> bxxxxxx}$

> $\texttt{bxxxxxxcb->xxxxxxxxx}$



## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+100;
struct node//未消除的砖结构体。
{
	bool cc;//是否为黑砖。
	int b,c;//此砖前k+1个未消除的砖白砖和黑砖数量。
	int pos;//位置。
};
deque<node> s;//deque代替栈。
int n,c,b;
vector<int> ans[N];//记录答案。
int cnt;//消除次数
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>b;
	c=1;
	s.push_back({0,0,0,0});//加空元素，避免栈空re。
	for(int i=1;i<=n;i++)
	{
		char c1;
		cin>>c1;
		if(c1=='b')
		{
			s.push_back({1,s.back().b+1,s.back().c,i});//此砖白。
		}
		else
		{
			s.push_back({0,s.back().b,s.back().c+1,i});//此砖黑。
		}
		if((int)s.size()>c+b+1)
		{
			if(s[(int)s.size()-c-b-1].cc)s.back().b--;//白砖或黑砖数减 这k+1块砖前面一个砖的颜色。
			else s.back().c--;
		}
		if((int)s.size()>c+b)
		{
			if((int)s.back().c==c&&(int)s.back().b==b)//这k+1块砖是否符合要求，如果是统计答案并pop。
			{
				cnt++;
				int t=s.size();
				for(int i=t-c-b;i<t;i++)
				{
					ans[cnt].push_back(s.back().pos);
					s.pop_back();
				}
			}
		}
	}
		for(int i=cnt;i>=1;i--)//倒序输出每次操作。
		{
			stable_sort(ans[i].begin(),ans[i].end());//每次操作内正序输出。
			for(int j=0;j<(int)ans[i].size();j++)
			{
				cout<<ans[i][j]<<' ';
			}
			cout<<'\n';
		}

	return 0;
}


```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑一个正难则反，最后一次一定是连续的 $k+1$ 个数。

然后前面的每次不一定连续，可以使用栈。

用一个栈维护当前没移走的，一旦凑够 $k$ 个白和 $1$ 个黑就弹走，放到答案里记录。

等弹完之后把答案倒着输出一遍。

时间复杂度 $O(nk)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
using namespace std;
int n,k;
string s;
stack<pair<char,int> >st;
vector<pair<char,int> >tmp;
vector<vector<pair<char,int> > >ans;
bool cmp(pair<char,int>a,pair<char,int>b){
    return a.second<b.second;
}
int main(){
    cin>>n>>k>>s;
    for(int i=0,b,c;i<s.size();i++){
        st.push({s[i],i+1});//压栈
        if(k+1<=st.size()){
            b=c=0;
            tmp.clear();
            for(int j=1;j<=k+1;j++){
                if(st.top().first=='b')
                    b++;
                else if(st.top().first=='c')
                    c++;
                tmp.push_back(st.top()),st.pop();//暴力判断
            }
            if(b==k&&c==1)
                ans.push_back(tmp);//可以就压栈
            else while(tmp.size())
                st.push(tmp[tmp.size()-1]),tmp.pop_back();//否则推回去
        }
    }
    for(int i=n/(k+1)-1;i>=0;i--){//倒着输出
        sort(ALL(ans[i]),cmp);//记得排序
        for(int j=0;j<=k;j++)
            cout<<ans[i][j].second<<" \n"[j==k];
    }/*
    for(vector<vector<pair<char,int> > >::reverse_iterator it=ans.rbegin();it!=ans.rend();it++){
        vector<pair<char,int> >k=*it;
        for(auto p:k)
            cout<<p.second<<' ';
        cout<<'\n';
    }*/
    return 0;
}
```

然后就 $90$ 分，原因是时间复杂度过高，$O(nk)\to n=10^6,k=10^6-1 \to nk=10^{12}$。

## 优化

加上前缀和，记录当前栈内前 $x$ 个元素中是黑色的数量。

**注意：不要先全前缀和出来，因为弹栈会改变之前算的前缀和**。

## 代码

```cpp
#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
using namespace std;
int n,k,sum[1000001];
string s;
stack<pair<char,int> >st;
vector<pair<char,int> >tmp;
vector<vector<pair<char,int> > >ans;
bool cmp(pair<char,int>a,pair<char,int>b){
    return a.second<b.second;
}
int main(){
    cin>>n>>k>>s;
    s=' '+s;
    for(int i=1;i<=n;i++){
        st.push({s[i],i});
        sum[st.size()]=sum[st.size()-1]+(s[i]=='c');//注意这里前缀和不用i，要覆盖掉弹出的
        if(st.size()>=k+1&&sum[st.size()]-sum[st.size()-k-1]==1){
            for(int j=1;j<=k+1;j++)
                tmp.push_back(st.top()),st.pop();
            ans.push_back(tmp),
            tmp.clear();
            
        }
    }//i-k~i
    //sum[i]-sum[i-k-1]
    //sum[i+1]-sum[i-k]
    for(int i=n/(k+1)-1;i>=0;i--){
        sort(ALL(ans[i]),cmp);
        for(int j=0;j<=k;j++)
            cout<<ans[i][j].second<<" \n"[j==k];
    }/*
    for(vector<vector<pair<char,int> > >::reverse_iterator it=ans.rbegin();it!=ans.rend();it++){
        vector<pair<char,int> >k=*it;
        for(auto p:k)
            cout<<p.second<<' ';
        cout<<'\n';
    }*/
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑这样一个做法：

从前往后将每一块砖推入栈顶，如果栈顶连续 $k+1$ 个元素有 $k$ 个白色，$1$ 个黑色，就把这些捆绑作为一组。最后逆序输出这些组。

显然这是正确的，因为这不会导致经过消除过的砖。

考虑使用平衡树维护，开两个平衡树，分别维护黑色和白色的栈，每次相当于问黑色的第 $k$ 大的与白色第二大的相对关系即可。

为了容易实现，考虑用 `pb_ds` 维护即可。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int N = 1e6 + 5;

vector<vector<int>> v;

int n, k;
string s;

tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> s1, s2;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == 'c') s2.insert(i);
		else s1.insert(i);
		if (s2.size() && s1.size() >= k)
		{
			if (s2.size() >= 2 && *s1.find_by_order(k - 1) < *s2.find_by_order(1)) continue;
			vector<int> g;
			int ggg = *s2.find_by_order(0);
			g.emplace_back(ggg);
			s2.erase(ggg);
			int c = k;
			vector<int> kk; 
			while (c--)
			{
				g.emplace_back(*s1.find_by_order(0));
				kk.emplace_back(*s1.find_by_order(0));
				s1.erase(s1.find_by_order(0));
			}
			sort(g.begin(), g.end());
			v.emplace_back(g);
		}
	}
	reverse(v.begin(), v.end());
	for (auto &i : v)
	{
		for (auto &j : i) cout << j << " ";
		cout << "\n";
	}
	return 0;
}

```


---

