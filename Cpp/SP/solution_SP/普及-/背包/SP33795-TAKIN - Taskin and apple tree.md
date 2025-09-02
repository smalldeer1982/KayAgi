# TAKIN - Taskin and apple tree

## 题目描述

# TAKIN - Taskin和苹果树


Taskin有一个苹果园，每天早上他都会去果园采摘苹果。他有一个篮子，可以携带**不超过 M个**苹果。Taskin将所摘的苹果放入篮子里，对于每一棵树，他要么将这棵树上的所有苹果摘完，要么跳过这棵树不摘。现在让你制定一个方案，使Taskin所摘的苹果数量最多。

## 说明/提示

T<=10,N<=20,M<=2*10^10,a[i]<=10^9

翻译提供者：right_cat

## 样例 #1

### 输入

```
2
5 6
2 1 2 7 8
5 10
1 2 4 4 6```

### 输出

```
5
10```

# 题解

## 作者：UnyieldingTrilobite (赞：12)

超水绿题建议降级。

首先，上来一看：背包！

诶呀这不是背包裸题吗！

一看 $m$ 的范围，心凉了大半截······

**明显的MLE**。

怎么处理？

仔细想一想！

既然 $a_i$ 的取值范围左右横跨如此之大，那必然有很多冗余状态！

动态规划冗余状态······想到了什么？

**记忆化搜索！**

嗯没错，就是他。

DP数组改成umap就好了呢。

**但进一步思考，umap意义大吗？**

还是数据范围落差的问题，**如果出题人想卡这种算法，完全可以精心构造一组数据（例如 $a_i=2^i$ ）使得每个状态只被遍历到一次，这时候umap就白费了，相当于暴搜。**

所以······只剩下一条路了——暴力枚举每棵树拿不拿苹果。

↑以上是我口胡的，从另一种思路切入正解。

事实上，一般人怎么像？

$T$ 和 $n$ 才 $10$ emm......

$\operatorname{O}(T\times2^n)$ 无脑暴力枚举完全可过——显然就是暴力。

所以说这题没有绿题难度。

然后代码就很好写辣······
C++版 ~~别想了另一个版本也是C++，但建议P党看下面一版（滑稽~~：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,a[21];
long long dfs(const long long&i,const long long&now){
	return now<=m?i==n+1?now:max(dfs(i+1,now),dfs(i+1,now+a[i])):0;
}
int main(){
	for(cin>>t;t;--t){//多组数据
		cin>>n>>m;
		for(long long i=1;i<=n;++i)cin>>a[i];
        	//输入
		cout<<dfs(1,0)<<endl;
        	//处理&输出
	}
    return 0;
}
```
dfs函数专门拎出来~~灵魂拷问~~：
```cpp
long long dfs(const long long&i,const long long&now){
//dfs(当前正在决策的树，已经摘的苹果)
return now<=m?//now不超过m吗？
i==n+1?//如果是，所有树都已经决策完了吗？
now//决策完了！保证了now不超过m！返回！
:max(dfs(i+1,now),dfs(i+1,now+a[i]))//决策，这棵树摘不摘呢？
:0;//now超过m了！啊哦，非法了！
}
```

注意由于可以一直不拿苹果，所以0可以改成任何一个非正数。

好了，正经题解结束了······

接着是高能：

思路清晰加强理解，可以采用[这个玩意](https://www.luogu.com.cn/blog/250637/)。

就是在代码开头加上[这些](https://www.luogu.com.cn/paste/yd432osb)然后语言选C++14就好了，你会感觉写代码像写【老虎叫】语作文。

非正经代码，非C/C++党的可以看这个（类似伪代码）：
```cpp
I have some long long integers called t,n as well as m;
I have one long long integer array called a[21];
I have one function called dfs(of one long long integer called i as well as another long long integer called nw){
    If the value of nw is greater than the value of m do{
        Return with the value of 0LL;
    }
    If the value of i equals the value of n plus 1 do{
        Return with the value of nw;
    }
    Return with the value of cpp::max(dfs(i plus 1,nw),dfs(i plus 1,nw plus a[i]));
}
Let us begin;
    Read in t;
    For each long long integer T within the range of(1LL,t) do{
        Read in n,then read in m;
        For each long long integer i within the range of(1LL,n) do{
            Read in a[i];
        }
        Print out the value of dfs(1,0);
        Print out '\n';
    }
That is all;
Thank you so much;
```
嗯，好了，全部结束了。

**Over.**

祝大家切题愉快！

文章前面一大段分析写的很累的，顺手留个赞呗~

---

## 作者：zhangyuhan (赞：3)

~~emm好久没刷暴力搜索了~~

这题原本可以当作$01$背包来做，但是$m≤2×10^{10}$。。。$gg$

观察数据范围：$n≤20$，考虑深搜。

根据题面的提示，我们知道有两种决策：

$1.$选择采摘当前的树

$2.$跳到下一棵树

其实这两个决策用代码实现都很简单。令$cur$为当前的树的下标，$v$为已经采摘的苹果数量，则：

第$1$种决策可以写为：

```cpp
dfs(cur+1,v+a[cur]);
```

第$2$种决策可以写为

```cpp
dfs(cur+1,v);
```

光这样打暴力是会$T$的，所以我们需要剪枝。

题面中说：可以携带不超过$M$个苹果，根据这一点我们可以剪枝：如果$v>m$就回溯。

代码实现也很简单：

```cpp
if(v>m)
    return ;
```

搜索的边界条件：那一定要把每棵树都遍历到，即$cur>n$(**注意！一定要大于！否则最后一棵树就无法遍历到！**)时，更新答案。

代码实现也很简单：

```cpp
if(cur>n){
    ans=max(ans,v);
    return ;
}
```

这样，完整的$dfs$函数就写出来了:

```cpp
void dfs(int cur,long long v){
    if(v>m)
        return ;
    if(cur>n){
        ans=max(ans,v);
        return ;
    }
    dfs(cur+1,v+a[cur]);
    dfs(cur+1,v);
}
```

最后说说做这道题的两大坑点：

$1.$ $ans$、$m$、$v$**这三个一定要开**$long$ $long$**！！！**

$2.$由于这是循环输入，所以在每次循环时，$ans$**一定要清零！！！**

最后送给大家完整的$AC$ $Code$

```cpp
#include<iostream>
using namespace std;

int t;

int n,a[10010];
long long m;

long long ans;

long long max(long long a,long long b){
    if(a>b)
        return a;
    return b;
}

void dfs(int cur,long long v){
    if(v>m)
        return ;
    if(cur>n){
        ans=max(ans,v);
        return ;
    }
    dfs(cur+1,v+a[cur]);
    dfs(cur+1,v);
}

int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        dfs(1,0);
        cout<<ans<<endl;
    }
    return 0;
}

```

---

## 作者：Fatalis_Lights (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/SP33795)

## Solution

这个题我一开始看题面的时候以为是个背包，没想到 $n$ 只有 $20$ 。那可以直接深搜啊。

时间复杂度 $\Theta(T\times 2^n)$ 。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100
using namespace std;
int n,m,a[N],t,ans;
//数字的数量，背包容量，物品重量，测试数据组数，答案。

void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
void read(int &x){
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}//快读模板不解释

inline void dfs(int depth, int tot){
	//搜索到了第几个，现在的总重。
	if(tot>m) return; //枚举时，如果超重了，直接结束，不更新答案。
	if(depth>n){ ans=max(ans,tot); return; } //如果到底了，就结束枚举，更新答案。
	dfs(depth+1,tot); //假如不选，那么重量不增加。
	dfs(depth+1,tot+a[depth]); //选，更新重量。
}

void init(){
	read(n); read(m);
	for(int i=1;i<=n;i++) read(a[i]);
}//读入

signed main(){
	read(t);
	while(t--){
		init(); ans=0; //多测要清空
		dfs(1,0);//开始枚举第一个，此时背包总重为零。
  		print(ans); puts(""); //输出需要换行。
	}
	return 0;
}
```


---

## 作者：___new2zy___ (赞：2)

## 题解 SP33795 【TAKIN - Taskin and apple tree】

题目传送门:

https://www.luogu.org/problemnew/show/SP33795

=================================================

不得不说，这题还是很水的= =

~~虽然说我蒻到连这题都写不出来= =~~

直接看代码吧~


    #include<iostream>
    #include<cstdio>
    #include<cmath>
    #include<algorithm>
    #include<queue>
    #include<cstring>
    using namespace std;
    typedef long long ll;
    const int inf=1e9+7;
    inline ll read()//快读,有需要的童鞋可以了解一下 
    {
        ll p=0,f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
        while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
        return 1ll*f*p;}
    const ll maxn=22;
    ll n,m,ans,sumv,A[maxn];
    //A数组记录每件物品的价值(苹果树上的苹果数)
    //sumv表示当前的获得的最多苹果数 
    inline ll max_(ll a,ll b)//自己的max函数 
    {return a>b?a:b;}
    void dfs(int k)
    //对于第k件物品进行dfs 
    {
	    if(sumv>m);
	    //剪枝:如果当前的苹果数超过篮子容积直接返回 
	    else if(k>n)ans=max_(ans,sumv);
	    //如果已经尝试选择完所有苹果树,对答案取max 
	    else//其他情况尝试选择和不选择 
	       {
	   		sumv+=A[k];
	   		//方案一:选择第k个苹果树
	   		dfs(k+1);
	   		//回溯:方案2:不选第k个苹果树 
	   		sumv-=A[k];
	   		dfs(k+1);
	       }
	    return ;
    }
    int main()
    {
	    int T=read();
	    while(T--)
	          {
	      	  n=read(),m=read(),ans=-inf;
	      	  for(int i=1;i<=n;i++)A[i]=read();
	      	  dfs(1);//从第一棵苹果树开始枚举 
	      	  printf("%lld\n",ans);
		      }
	    return 0;
    }
    
    
好啦，有人可能对于dfs感觉不爽~~（其实我也是这么想的）~~

至于一些神奇的做法，本人也是想了很多：

比如说本人尝试用一些做法= =~~（堆排序和dp）~~发现都WA
了

如果有dalao使用了别的方法通过了此题，请发到题解里

感谢阅读~~

最后推广一下我的博客：

https://www.luogu.org/blog/new2zy/

拜拜~~~



---

## 作者：chengni (赞：2)

数据非常恶心，m太大导致背包放不下，但是n很小，直接深搜加剪枝即可。

简单的深搜。
```cpp
#include<bits/stdc++.h>

using namespace std;

inline long long read(){
	char ch=getchar();long long x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}

long long a[1000];

long long ans=0;
long long n,m;

void dfs(long long x,long long v){//枚举拿或者不拿，并且剪枝
	if(v>m) return;
	if(v>ans) ans=v;
	if(x==n+1) return ;
	dfs(x+1,v);
	dfs(x+1,v+a[x]);
	
}

int main(){
	long long t=read();
	while(t--){
		ans=0;//记得每次改一下ans的初始值。
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		dfs(1,0);//直接深搜即可
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：Jerry_heng (赞：0)

看到很多大佬都在用DFS，我就放一个用位运算做的吧。

对于每一棵树，要么取要么不取，所以就想到了用一个二进制数表示状态。

共有 $2^n$ 种取法，就用 $0-2^n - 1$ 这些数表示。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int a[21];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int ans=0,n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<(1<<n);i++){//不用考虑0
			int s=0;
			for(int j=1;j<=n;j++)s+=a[j]*((i>>(j-1))%2);//取第j位
			if(s<=m)ans=max(ans,s);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

