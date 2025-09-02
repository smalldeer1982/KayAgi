# Candies Distribution

## 题目描述

There are $ n $ children numbered from $ 1 $ to $ n $ in a kindergarten. Kindergarten teacher gave $ a_i $ ( $ 1 \leq a_i \leq n $ ) candies to the $ i $ -th child. Children were seated in a row in order from $ 1 $ to $ n $ from left to right and started eating candies.

While the $ i $ -th child was eating candies, he calculated two numbers $ l_i $ and $ r_i $ — the number of children seating to the left of him that got more candies than he and the number of children seating to the right of him that got more candies than he, respectively.

Formally, $ l_i $ is the number of indices $ j $ ( $ 1 \leq j < i $ ), such that $ a_i < a_j $ and $ r_i $ is the number of indices $ j $ ( $ i < j \leq n $ ), such that $ a_i < a_j $ .

Each child told to the kindergarten teacher the numbers $ l_i $ and $ r_i $ that he calculated. Unfortunately, she forgot how many candies she has given to each child. So, she asks you for help: given the arrays $ l $ and $ r $ determine whether she could have given the candies to the children such that all children correctly calculated their values $ l_i $ and $ r_i $ , or some of them have definitely made a mistake. If it was possible, find any way how she could have done it.

## 说明/提示

In the first example, if the teacher distributed $ 1 $ , $ 3 $ , $ 1 $ , $ 2 $ , $ 1 $ candies to $ 1 $ -st, $ 2 $ -nd, $ 3 $ -rd, $ 4 $ -th, $ 5 $ -th child, respectively, then all the values calculated by the children are correct. For example, the $ 5 $ -th child was given $ 1 $ candy, to the left of him $ 2 $ children were given $ 1 $ candy, $ 1 $ child was given $ 2 $ candies and $ 1 $ child — $ 3 $ candies, so there are $ 2 $ children to the left of him that were given more candies than him.

In the second example it is impossible to distribute the candies, because the $ 4 $ -th child made a mistake in calculating the value of $ r_4 $ , because there are no children to the right of him, so $ r_4 $ should be equal to $ 0 $ .

In the last example all children may have got the same number of candies, that's why all the numbers are $ 0 $ . Note that each child should receive at least one candy.

## 样例 #1

### 输入

```
5
0 0 1 1 2
2 0 1 0 0
```

### 输出

```
YES
1 3 1 2 1
```

## 样例 #2

### 输入

```
4
0 0 2 0
1 1 1 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
0 0 0
0 0 0
```

### 输出

```
YES
1 1 1
```

# 题解

## 作者：Karry5307 (赞：4)

### 题意

给两个长度为$n$的序列$l$和$r$，你需要求出一个序列$a$使得左侧比$a_i$大的有$l_i$个数，右侧比$a_i$大的有$r_i$个数。

判断序列$a$的存在性，如果存在输出一种可能的序列。

$\texttt{Data Range:}1\leq n\leq 10^3,0\leq l_i,r_i\leq n$

### 题解

构造好题。

考虑到$l_i=r_i=0$的位置为$a$中非严格最大值存在的位置，于是可以用类似于拓扑排序的思想来构造。

每一次把所有$l_i=r_i=0$的位置塞进一个队列中，考虑当前的队首，假设为$j$，那么就把所有小于$j$的并且没有赋值的位置的$r$减去$1$，所有大于$j$并且没有赋值的位置的$l$减去$1$即可。模拟一下就好了。

如果被塞进队列里面的点不足$n$个就无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
queue<ll>q;
ll cnt,cur,top,col;
ll l[MAXN],r[MAXN],res[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	cnt=cur=col=read();
	for(register int i=1;i<=cnt;i++)
	{
		l[i]=read();
	}
	for(register int i=1;i<=cnt;i++)
	{
		r[i]=read();
	}
	while(1)
	{
		for(register int i=1;i<=cnt;i++)
		{
			if(l[i]==0&&r[i]==0)
			{
				q.push(i);
			}
		}
		if(q.empty())
		{
			break;
		}
		cur-=q.size();
		while(!q.empty())
		{
			top=q.front(),q.pop(),l[top]=r[top]=-1,res[top]=col;
			for(register int i=top-1;i;i--)
			{
				r[i]--;
			}
			for(register int i=top+1;i<=cnt;i++)
			{
				l[i]--;
			}
		}
		col--;
	}
	if(cur)
	{
		return puts("NO"),0;
	}
	puts("YES");
	for(register int i=1;i<=cnt;i++)
	{
		printf("%d ",res[i]);
	}
}
```

---

## 作者：Isharmla (赞：2)

很好的思维题。

做这种题一般我们没有思路是很正常的，所以，我们需要找到一个突破口，如何找到这个突破口呢？可以手玩一下样例，看看有什么特殊性质。如果你是没有思路而看向题解的话，这边也可以按照这个方法再玩会样例。

我们可以从最大值入手，如果数据合法，一定存在一个充分条件 $l_x=r_x=0$，也就是这个数列有最大值。显然一个序列一定有最大值，如果最大值都没有，那么只有可能是不可能存在答案了。这样我们就可以判断错误了。然后，我们将这个数的贡献去除，也就是对于 $y \lt x$ 的，他的 $r_y$ 此时就减一，对于 $x \lt y$ 的，他的 $l_y$ 就减一。

这样做有什么用呢？既然他的贡献被去除了，我们就可以看为这点不存在了。我们将当前的最大值的贡献全部减去，这样一来，我们的问题再次转换长度为 $n-num_{max}$ 的数列，这里 $num_{max}$ 表示最大值的个数。让你判断是否合法，我们继续按照上面的方法解决这个子问题，直到最后长度变为 $1$ 即可。最后又倒回来，按照这个顺序从小到大赋值即可。

```cpp
// Problem: C. Candies Distribution
// Contest: Codeforces - Mail.Ru Cup 2018 Round 1
// URL: https://codeforces.com/contest/1054/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F(i,a,b) for(int i=a;i<=b;i++)
#define R(i,a,b) for(int i=a;i>=b;i--)
const int N=2e5+5;

string s,t;

inline int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') f*=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0') {
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
//突破口：最大的数
int n,x = 0,ans[N],a[N],b[N];
bool vis[N];
void Clear(int x) {
	for(int i=1; i<x; i++) b[i]--;
	for(int i=x+1; i<=n; i++) a[i]--;
}
signed main() {
	n=read();
	x=n;
	F(i,1,n) a[i]=read();
	F(i,1,n) b[i]=read();
	queue<int> Q;
	F(i,1,n) {
		bool falg=false;
		F(j,1,n) {
			if(vis[j]) continue;
			if(a[j]==b[j]&&a[j]==0) Q.push(j),falg=true;

		}
		if(falg==true) {
			while(!Q.empty()) {
				Clear(Q.front());
				ans[Q.front()]=x; 
				vis[Q.front()]=1;
				Q.pop();
			}
		}
		x--;
	}
	F(i,1,n) if(ans[i]==0){cout<<"NO";return 0;}
	cout<<"YES"<<endl;
	F(i,1,n) cout<<ans[i]<<" ";
	return 0;
}
```



---

## 作者：cqbztz2 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1054C)

# 题目大意

给 n 个孩子分发糖果，每个孩子知道自己左边比自己糖果数多的人的个数，也知道自己右边比自己糖果数多的人的个数，要求你找出一种满足的分配方案。

# 思路

对于每个人，他的 $ l[i]+r[i] $ 越小，说明他的糖果数越多；反之，他的 $ l[i]+r[i] $ 越大，说明他的糖果数越少。

所以我们就让 $ v[i]=n-l[i]-r[i] $ ，然后检查第 i 个人的左右两边是不是满足 $ l[i] $ 和 $ r[i] $ 的条件，只要有一个人不满足，就是 NO 。

# 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  struct node{
      int l,r,v;
  }a[1005];
  int n;
  int main(){
      cin>>n;
      for(int i=1;i<=n;i++){
          cin>>a[i].l;
      }

      for(int i=1;i<=n;i++){
          cin>>a[i].r;
      }

      for(int i=1;i<=n;i++){
          a[i].v=n-a[i].l-a[i].r;
      }
      for(int i=1;i<=n;++i){
          for(int j=1;j<i;j++){
              if(a[j].v>a[i].v){
                  a[i].l--;
              }
          }     
          for(int j=i+1;j<=n;j++){
              if(a[j].v>a[i].v){
                  a[i].r--;
              }
          }     
          if(a[i].l!=0||a[i].r!=0){
              cout<<"NO";
              return 0;
          }  
      }
      cout<<"YES"<<endl;
      for(int i=1;i<=n;++i){
          cout<<a[i].v<<" ";
      }
      return 0;
  }
```


---

## 作者：lizulong (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1054C)

## 思路

一眼构造题。

如果和我一样刚开是没什么思路的话，直接看样例找规律。

```
in:

5
0 0 1 1 2
2 0 1 0 0

out:

YES
1 3 1 2 1
```

不难发现，左右两边如果同时没有比自己大的，即  $l_i=r_i=0$ 时，就是该数列中最大的一个已知数。

有了一个已知数且最大，就能更新 $l_i$ 与 $r_i$ 如此循环下去就能求出来。

但这样不仅时间复杂度高，代码也不是很好写。

回过头来看样例，又发现如果把 $l_i$ 与 $r_i$ 加起来，最终的数列不就是其和的排行。

```
0+2=2
0+0=0
1+1=2
1+0=1
2+0=2

和为
2 0 2 1 2

排行
1 3 1 2 1
```

这样似乎不就直接解决了？

但还忘了考虑 ```NO``` 的情况，可以用我们一开始的思路，一个个去更新，当场上没有 $l_i=r_i=0$ 时，直接输出 ```NO```。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int s=0,w=1;
	char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
    while(ch>='0'&&ch<='9') s=s*10+ch-48,ch=getchar();
    return s*w;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
int l[1005],r[1005],a[1005];
struct node{
	int NO_;//原顺序 
	int number;//排行 
	int he;//和 
}x[1005];
bool cmp(node qaq,node qwq){
	return qaq.he > qwq.he ;
}
signed main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) l[i]=read();
	for(int i=1;i<=n;i++) r[i]=read();
	for(int i=1;i<=n;i++) x[i].he=l[i]+r[i],x[i].NO_=i;
	sort(x+1,x+1+n,cmp);
	x[1].number=1;
	for(int i=2,same=x[1].he;i<=n;i++) (x[i].he!=same) ?(x[i].number=x[i-1].number+1,same=x[i].he):(x[i].number =x[i-1].number); 
	for(int i=1;i<=n;i++)	a[x[i].NO_]=x[i].number;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<i;j++) if(a[j]>a[i]) l[i]--;
		for(int j=i+1;j<=n;j++) if(a[j]>a[i]) r[i]--;
		if(l[i]!=0||r[i]!=0) {cout<<"NO\n";return 0;}
	} 
	cout<<"YES\n";
	for(int i=1;i<=n;i++) write(a[i]),putchar(' ');
	putchar('\n'); 
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/127552403)

---

