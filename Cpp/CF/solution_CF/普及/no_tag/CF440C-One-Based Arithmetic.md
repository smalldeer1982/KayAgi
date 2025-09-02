# One-Based Arithmetic

## 题目描述

Prof. Vasechkin wants to represent positive integer $ n $ as a sum of addends, where each addends is an integer number containing only 1s. For example, he can represent 121 as 121=111+11+–1. Help him to find the least number of digits 1 in such sum.

## 样例 #1

### 输入

```
121
```

### 输出

```
6
```

# 题解

## 作者：__Shine__ (赞：9)

## 题目大意
给定一个 $n$，需要把 $n$ 用若干个用 $1$ 组成的数通过加和减表示出来，求最少需要用的 $1$ 的个数。

例：$121=111+11-1$

所以用了 $6$ 个 $1$ $(n \leq 10^{15})$。

## 具体思路
这道题表面看上去挺难（因为 $n \leq 10^{15}$)，但仔细思考就会发现，**在 $10^{15}$ 内，仅包含 $1$、$11$、$111$、$1111$ 等 $15$ 个数**。

所以我们可以想到**深搜**！由于这题的性质，每次搜肯定能得到一个解，然后之后搜的时候**如果 $1$ 的数量大于这个解，就可以跳出**，怒剪了一大波枝。（最优性剪枝）

也就是从最高位开始，慢慢**把位数削成 $0$**。因为把第 $i$ 位消除成 $0$ 后，可以选择数保证**这一位不会再变回 $1$**，我们可以一位一位削下去。

深搜只有两种方向，例如第 $i$ 位是 $x$，
1. 第一种方向是就是**搞 $x$ 个 $1$ 把它削了**；

2. 另一种是**搞一堆 $1$ 把它加上去，然后搞一个比前面那个位数多一位的 $1$ 把它再削掉**。

这两种都有可能，而其他的方法都不如这两种。

所以哐哐哐就是搜啦！
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int ans,len;
ll one[17]={0,1,11,111,1111,11111,111111,1111111,11111111,111111111,1111111111,11111111111,111111111111,1111111111111,11111111111111,111111111111111,1111111111111111};
void dfs(ll x,int sum)
{
    int a,b;
    if(sum>=ans) 
		return;//如果1的数量大于这个解，就可以跳出
    if(x==0)//搜索到边界 
    {
        ans=sum;
        return;
    }
    if(x<0) 
		x=-x;
	//从最高位开始，慢慢把位数削成0
    ll y=x;
    int t=0;
    while(y) 
    {
    	t++;
		y/=10;
	}
    ll reta=x;
	ll retb=one[t+1]-x;
    ll h=pow(10,t-1);
    int sa=0,sb=t+1;
    while(reta>=h) 
		reta-=one[t],sa+=t;
    while(retb>=h) 
		retb-=one[t],sb+=t;
	//两种方向，一种加，一种减 
    dfs(reta,sum+sa);
    dfs(retb,sum+sb);
    return;
}

int main()
{
    ll x;
    while(scanf("%lld",&x)!=EOF)//如果没有输入完毕，就继续输入
    {
        ans=1e9;//将ans初始化为极大值 
        dfs(x,0);//开始搜索
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Forever丶CIL (赞：4)

题目： One-Based Arithmetic

codeforce的题，挺有意思的

题目链接：http://codeforces.com/problemset/problem/440/C

题目大意是：给你一个n，你需要把n用若干个1组成数通过加加减减表示出来，求最少用的1的个数。
例：121=111+11-1 用了6个1。
![](https://cdn.luogu.com.cn/upload/pic/14091.png)


------------

第一看n的范围，觉得爆搜没戏，肯定是数学题，但是仔细想想，没问题的，因为对于小于1e15的数中，仅由1组成的数很少：

1

11

111

1111 

11111 

111111 

1111111

11111111

111111111

1111111111

11111111111

111111111111

1111111111111 

11111111111111

111111111111111

只有这十五个，所以枚举就好了，那么我们要想枚举方法了。

首先考虑，对于一个数假设它有x位，那么我们一定是用小于等于x位的1去加，或者上来加个x+1位的1，再用小于等于x位的1去减，所以我们可以上来就枚举最高位数的1，再一点点降低枚举的位数，我们对于一个i位的1，我们可以选择加它，也可以选择减它，所以我们每次要进行两个决策，递归求解，最后传递回来需要的最少位数的1。但是其实很不好写，至少我是这么觉得的，反正我写了好久，脑子都成浆糊了，估计是我比较笨。

具体写的思路是：
我们枚举i位的1，去一点点凑成x，刚开始在递归函数里存x和x的位数+1（后面用dig代替），表示我们现在要用dig位的1去拼x，如果我们现在要加dig位的1，那么我们可以一次性加满，像这样：55->11×5或者是64=11×5+...，一次性把dig位的1一直加到不能加为止，然后再用dig-1位的1去填补剩下的。那么如果是减法，我们可以用dig位的1减去x，然后剩下的那个数不就是我们需要再一点点加回来的那个么，这样我们就把减法变成了加法，例：999=1111-111-1，当我们枚举4位的1时，我们选择减法，就成了我们要用3位一下的1去拼1111-999了，后面如果再遇到减法，一样的道理去转化。


------------

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
ll A[20];
ll n;
inline ll read()//读入优化
{
    ll fl=1ll,rt=0ll; char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') fl=-1ll; ch=getchar(); }
    while(ch>='0'&&ch<='9'){ rt=rt*10ll+ch-'0'; ch=getchar(); }
    return fl*rt;
}
int Get_n(ll x)//获得n的数字位数，好像可以在读优中完成哎
{
    int ret=0ll;
    while(x!=0)
    {
        x/=10;
        ret++;
    }
    return ret;
}
ll dfs(ll x,ll dig)//现在我们要消除的数为x，我们用位数为dig的1来消除
{
    ll use=x/A[dig]; x=x%A[dig];//一次性吧dig位的1都加上
    if(x==0) return dig*use;
    //dig+dfs(A[dig]-x,dig-1)用来计算多加一点再去减的情况
    //dfs(x,dig-1)用来计算继续加的情况
    else return dig*use+min(dig+dfs(A[dig]-x,dig-1),dfs(x,dig-1));
}
int main()
{
	//打出上面列举的1111...的那个表
    for(int i=1;i<=17;i++) A[i]=A[i-1]*10ll+1ll;
    n=read();
    int Q=Get_n(n);
    printf("%I64d\n",dfs(n,Q+2ll));
    return 0;
}
```

---

