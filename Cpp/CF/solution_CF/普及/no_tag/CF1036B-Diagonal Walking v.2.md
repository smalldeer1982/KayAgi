# Diagonal Walking v.2

## 题目描述

Mikhail walks on a Cartesian plane. He starts at the point $ (0, 0) $ , and in one move he can go to any of eight adjacent points. For example, if Mikhail is currently at the point $ (0, 0) $ , he can go to any of the following points in one move:

- $ (1, 0) $ ;
- $ (1, 1) $ ;
- $ (0, 1) $ ;
- $ (-1, 1) $ ;
- $ (-1, 0) $ ;
- $ (-1, -1) $ ;
- $ (0, -1) $ ;
- $ (1, -1) $ .

If Mikhail goes from the point $ (x1, y1) $ to the point $ (x2, y2) $ in one move, and $ x1 \ne x2 $ and $ y1 \ne y2 $ , then such a move is called a diagonal move.

Mikhail has $ q $ queries. For the $ i $ -th query Mikhail's target is to go to the point $ (n_i, m_i) $ from the point $ (0, 0) $ in exactly $ k_i $ moves. Among all possible movements he want to choose one with the maximum number of diagonal moves. Your task is to find the maximum number of diagonal moves or find that it is impossible to go from the point $ (0, 0) $ to the point $ (n_i, m_i) $ in $ k_i $ moves.

Note that Mikhail can visit any point any number of times (even the destination point!).

## 说明/提示

One of the possible answers to the first test case: $ (0, 0) \to (1, 0) \to (1, 1) \to (2, 2) $ .

One of the possible answers to the second test case: $ (0, 0) \to (0, 1) \to (1, 2) \to (0, 3) \to (1, 4) \to (2, 3) \to (3, 2) \to (4, 3) $ .

In the third test case Mikhail cannot reach the point $ (10, 1) $ in 9 moves.

## 样例 #1

### 输入

```
3
2 2 3
4 3 7
10 1 9
```

### 输出

```
1
6
-1
```

# 题解

## 作者：封禁用户 (赞：5)

# 0.前言
~~擅长写分支结构的我又来了~~。
考试的时候犯迷糊了，后来静下心来还是AC了。
这题我看大佬用的其他方法，那本蒟蒻来发一篇分支结构的题解！

# 1.思路
首先用一个 $flag$ 记录是否输出过（输出过是 $1$，没输出是 $0$ ）

**无解情况：** 
然后就是一个 $n \times m$ 的坐标系，最少应该走 $\max(n,m)$ 步，下面我来证明一下：
当 $n>m$ 时：
‪![](https://t1.picb.cc/uploads/2021/08/19/wWwtpv.png)
其中路径为粗的蓝色的线，长边为 $n$ ，短边为 $m$。最少步数为 $n$ 步。同样道理，当 $m>n$ 时，最少步数为 $m$ 步。以无论怎样，最少步数一定是 $\max(n,m)$，作者觉得到这还是很好理解的。

言归正传，所以当给出的步数 $k$ 小于最小步数 $\max(n,m)$ 时，无解，输出 $-1$。（输出完后 $flag=1$）

**其余情况：** 
当 $\max(n,m)-\min(n,m)$ 为 $2$ 的倍数时，简单试一下就会发现最多可以斜着走 $k-1$ 步。再用上图来看就应该是，小长方形的宽的举例若为 $2$ 的倍数，就需要不走斜着的路，需要绕路走两步，故要减 $1$。

当 $\min(n,m)-k$ 为 $2$ 的倍数时，trytry就发现可以斜着走 $k-2$ 步，不为则走 $k$ 步。这也可以结合上图，找到大长方形的宽，和刚才解释一样，即绕路或不绕路。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,k;
int main(){
    scanf("%lld",&t);
    while(t--){
    	bool flag=0;
        scanf("%lld%lld%lld",&n,&m,&k);
        if(k<max(n,m)&&flag==0){
        	cout<<"-1\n";
        	flag=1;
        }
        if((max(n,m)-min(n,m))%2&&flag==0){
        	cout<<k-1<<"\n";
        	flag=1;
        }
        else if(flag==0){
            if((min(n,m)-k)%2) cout<<k-2<<"\n";
            else cout<<k<<"\n";
			flag=1;
        }
    }
}
```


---

## 作者：Light_Pursuer (赞：1)

# [Diagonal Walking v.2 - 洛谷](https://www.luogu.com.cn/problem/CF1036B) 1600

## Solution

分类讨论。

首先思考什么时候答案无解，答案无解当且仅当 $k<\max(n,m)$ 时。

接着进行分类讨论有解的情况。

画一个图可以知道，当 $\max(n,m)-\min(n,m)$ 为奇数时，答案只需要输出 $k-1$ 即可。

当 $\max(n,m)-\min(n,m)$ 为偶数时，接着分类讨论。如果 $\min(n,m)-k$ 时奇数，输出 $k-2$ 就可以了，否则就输出 $k$。

时间复杂度 $O(T)$。

code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int ret=0,f=1;char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') 
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*f;
}
int n,m,k;
signed main()
{
	int t;t=read();
    while(t--)
	{
    	n=read(),m=read(),k=read();
        if(k<max(n,m))
		{
        	cout<<"-1"<<endl;
        	continue;
        }
        if((max(n,m)-min(n,m))%2)
		{
        	cout<<k-1<<endl;
        	continue;
        }
        else
		{
            if((min(n,m)-k)%2) 
			{
				cout<<k-2<<"\n";	
			}
            else 
			{
				cout<<k<<"\n";
			}
        }
    }
    return 0;
}
```

---

## 作者：Alloverzyt (赞：1)

[更好的阅读体验](https://www.cnblogs.com/alloverzyt/p/17513087.html)

~~(管理员辛苦了，我谢谢你们)~~

# 题目大意

很明显，这道题就是求 $k$ 步之内到达点 $(a,b)$，然后尽量走对角线，求能走对角线的最大值。

# 做题思路

首先明白一个事实，即一个对角线可以通过增加一步而抵达点不变，如图：
[![pCrr7tJ.png](https://s1.ax1x.com/2023/07/03/pCrr7tJ.png)](https://imgse.com/i/pCrr7tJ)

我们可以这样思考这道题，在到达目的地以后，剩余步数如果为双数，则在对角线来回走，最后会到目的地。但如果剩余步数为单数，我们通过上图转化最后依旧到达目的地。

现在考虑什么时候输出 $-1$，即为走完 $k$ 步后仍无法到达目的地，考虑从原点到达目的地需要的最小步数即为 $\max(a,b)$。

所以排除掉无法到达的情况，我们分类讨论：
1. 设 $a$ 和 $b$ 中，$a$ 为较大的一个数，如果 `(a-b)%2==0`，那么走对角线我们会先到达 $b$ 的限定高度，考虑优化走到 $a$ 的路线，以 $(5,3)$ 为例，走到 $3$ 的限定高度后，如果剩余路线为双数，考虑上下跳走,答案 $k$：
[![pCrrTk4.png](https://s1.ax1x.com/2023/07/03/pCrrTk4.png)](https://imgse.com/i/pCrrTk4)

2. 依旧设 $a$ 为较大的一数，如果 `(a-b)%2==1`，那么我们只好消耗一格走平路以到达目的地，答案 $k-1$，以 $(5,2)$ 为例：
[![pCrrI7F.png](https://s1.ax1x.com/2023/07/03/pCrrI7F.png)](https://imgse.com/i/pCrrI7F)

最后，我们只需要判断一下剩余的步数能不能全部在对角线上反复横跳。如果不行，则贡献为 $-2$（开头讲了）。

线上 AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,k;
int main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld%lld",&n,&m,&k);
        if(k<max(n,m)){
        	printf("-1\n");
        	continue; 
        }
        if((max(n,m)-min(n,m))%2==1) k--;
        else if((k-max(n,m))%2==1) k-=2;
        printf("%lld\n",k);
    }
	return 0;
}
```
-------------------------------
在此补充一个我有点迷糊的点，即为什么判断 `if((max(n,m)-min(n,m))%2==1)` 后，不用再次判断剩余的 $k$ 是否为为双数，上图，
[![pCrr50U.png](https://s1.ax1x.com/2023/07/03/pCrr50U.png)](https://imgse.com/i/pCrr50U)

满足 `if((max(n,m)-min(n,m))%2==1)` 意味着我们到达目的地之前至少走了一个平路，此时若 $k$ 为单数，直接将多的一个平路改为对角线加平路（还是最开始将的三角转换），如上图。

---

## 作者：BeyondStars (赞：1)

其实这个策略好像比较难想，可能是因为我太笨了吧。策略是走到m,n中较小的那个数所在的那一行或列。然后判断剩下的步数与当前点到m目标点的距离(水平距离或者竖直距离)是不是偶数，如果是的话，那么接下来的所有步数都可以斜着走。如果**剩余步数**是奇数的话，应该在原点的时候就水平与竖直都走一步。这样就可以使剩余步数是偶数了，然后把(1,1)当做原点来计算就行了。如果剩余距离是奇数，那么就应该在原点的时候就水平**或**竖直走一次。至于这个的正确性，其实可以自己画个图简单看一下，有一定的贪心的思想在里面，就是尽量走斜步。同时还有一个很重要的思想：转化为子问题的思想。
代码:
```cpp
#include <iostream>
using namespace std;
inline unsigned long long max(unsigned long long a,unsigned long long b){return a>b?a:b;}
inline unsigned long long min(unsigned long long a,unsigned long long b){return a<b?a:b;}
int main() {
    int q;
    unsigned long long n,m,k;
    cin>>q;
    while(q--){
        cin>>n>>m>>k;
        if(max(m,n)>k){cout<<-1<<endl;continue;}
        unsigned long long ans = 0;
        if((max(m,n)-min(m,n)&1)==0&&(k-min(m,n))&1==1){//如果到达min(m,n)所在的行或列以后，到目标点的距离是个奇数，说明在一开始的时候就要向(1,1)移动
            n-=1;
            m-=1;
            k-=2;
        }
        ans = min(m,n);//移动到min(m,n)
        k -= min(m,n);//剩余步数
        unsigned long long  dis = max(m,n)-min(m,n);//看看距离
        if(dis&1){//如果距离是个奇数,那么应该一开始就向左或者右移动一下,然后斜着走
            k--;
            ans+=k;
        }else{//如果距离是个偶数，剩下的直接全部斜着走
            ans+=k;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
安利一波本蒟蒻的博客[点我，点我](http://denghaoyu.leanote.com/)，欢迎各位大佬~~调教~~指教


---

## 作者：Hutao__ (赞：0)

## 思路

分类讨论。

先讨论无解的情况，仅当 $k < \max( n ,m )$ 时无解，明显这种情况肯定走不到终点。

通过画图我们得知，当 $\max(n,m) - \min(n,m)$ 为奇时答案为 $k-1$，因为当走到 $(n,m-1)$ 或 $(n-1,m)$ 时，要正常走一步才行。

再讨论 $\max(n,m)-\min(n,m) $ 为偶数时，若 $\min(n,m) -k $ 为奇时，输出 $k-2$，否则输出 $k$。

## 代码


```cpp
//lgRMJ坏了不保证此代码能通过本题
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,k;
		cin>>n>>m>>k;
		if(k<max(n,m)){
			cout<<-1<<'\n';
			continue;
		}
		if((max(n,m)-min(n,m))%2==1){
			cout<<k-1<<'\n';
		}
		else {
			if(abs(min(n,m)-k)/*结果可能为负*/%2==1)cout<<k-2<<'\n';
			else cout<<k<<'\n';
		}
	}
}
```

---

## 作者：jiangjiangQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1036B)
### 前置知识点
从 $ (0,0) $ 出发到 $ (x,y) $ ，最短路长度为 $ \max(n,m) $。
那么这就可以判断什么时候无解了，即 $k$ 小于 $ \max(n,m) $。输出```-1```。

### 进一步解决有解情况
设 $px$ 为 $ \max(n,m) $，$py$ 为 $ \min(n,m) $。
可得一下三种情况。

1. $px$ 与 $py$ 的差值模 $2$ 余 $1$，$ans=k-1$。
2. $k$ 与 $px$ 的差值模 $2$ 余 $1$，$ans=k-2$。
3. $px$ 与 $py$ 的差值为 $2$ 的倍数，则有 $ans=k$。

证明：

1. 
![](https://cdn.luogu.com.cn/upload/image_hosting/iolgtodv.png)
可以发现如果想要 $3$ 次到达 $(2,3)$ 最多走 $2$ 个斜步。然后平移一格。
具体还可以枚举相同情况去验证。

2.
![](https://cdn.luogu.com.cn/upload/image_hosting/czf6towq.png)
由于从 $(0,0)$ 直接到 $(2,2)$ 最短路径长度为 $2$。可是 $k=3$，那么这就需要把一个斜步变成两个平移了。

3. 
![](https://cdn.luogu.com.cn/upload/image_hosting/dklisgiy.png)
当出现这种情况，一种是可以直接斜步到且符合步数要求。
再比如图中想 $6$ 步去到 $(2,4)$，当已经用了 $4$ 个斜步，这时已经到达目标坐标了。可还有 $2$ 步怎么办呢？那就用两个相反方向的斜步相抵消。还是在终点。所以综上所述第三种差值为 $2$ 的倍数，直接就是 $k$ 了。

### 代码实现
还是比较简短的。
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define dy; ios::sync_with_stdio(false),cin.tie(),cout.tie();
#define int long long
#define re register
#define For(i,l,r) for(re int i=l;i<=r;i++)
const int N=3e5+5;
inline void read(int &x){
	   x=0;int f=1;
	   char c=getchar();
	   while(!isdigit(c)){
			if(c=='-') f=-1;
			c=getchar();
	   }while(isdigit(c)){
			x=x*10+c-'0';
			c=getchar();
	   }x*=f;
}
inline void write(int x){
	   if(x<0){x=-x;putchar('-');}
	   if(x>9) write(x/10);
	   putchar(x%10+'0');
}int T,x,y,k;
signed main(){
	dy;cin>>T;
	while(T--){
		cin>>x>>y>>k;
		if(k<max(x,y)) cout<<-1<<endl;
		else{
			int px=max(x,y),py=min(x,y);
			if((px-py)%2==1) cout<<k-1<<endl;
			else if((k-px)%2==1) cout<<k-2<<endl;
			else cout<<k<<endl; 
		}
	}
	return 0;
}
```
$\color{red}\texttt{请勿抄袭} $。


---

