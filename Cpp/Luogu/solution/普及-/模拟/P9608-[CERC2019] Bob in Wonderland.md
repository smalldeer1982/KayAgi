# [CERC2019] Bob in Wonderland

## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Bob in Wonderland](https://contest.felk.cvut.cz/19cerc/solved/bob.pdf)」**

## 题目描述

众所周知，链条是由相连的环组成的。通常，所有环都具有相同的形状和大小。Bob 是一名铁匠学徒，他正在制作自己的第一条铱链。他遵循传统的链条制作通则。上面写着：
- 如果没有链条，制作一个环，它将成为你链条的一部分。
- 如果有一条链，制作一个环，并将其连接到你已有的链中的另一个环上。

Bob 做了第一个环。然后，每次他制作另一个环时，他都会将其连接到链条上的其他环上，就像通则告诉他的那样。

当他完成时，他意识到他创造的物体根本不像一条普通的链。为了把链条拉直，他反复地拎起可能是链条两端的两个链环，并试图把它们尽可能地拉开。但在不同的地方，还有更多的“链条”从拉直的部分垂下来。

很明显，Bob 的工作还没有完成，他决定把他制作的物体称为未完成的链条。经过更多的思考，Bob 得出了一个结论，他必须更谨慎地断开一些环，并将它们重新连接到未完成的链条的其余部分，以获得他想要制作的直链。在直链中，每个环最多连接两个其他环，并且直链不能在不断开链环的情况下分离成更多的部分。

Bob 现在更加小心了，将用简单的步骤取得进展。在一个步骤中，他将选择一个环 A，连接到未完成链中的另一个环 B。然后，他会断开 A，将其与 B 分开，并将 A 重新连接到未完成的链条中的另一个环 C。如果最初连接到 A 的环不是 B，Bob 将在整个步骤中保持它们连接着 A。

Bob 获得直链所需执行的最小步骤数是多少？

## 说明/提示

### 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/541l6nqd.png)

## 样例 #1

### 输入

```
5
4 3
1 2
4 5
3 2
```

### 输出

```
0```

## 样例 #2

### 输入

```
6
1 3
3 2
3 4
4 5
4 6```

### 输出

```
2```

## 样例 #3

### 输入

```
7
1 2
2 3
3 4
4 5
3 6
6 7```

### 输出

```
1```

# 题解

## 作者：Defy_HeavenS (赞：5)

## 题意
给你一个由若干个环相扣而成的链条，如果想让这个链条变成直链，至少要解开几个环。

直链是指每个环最多和其他两个环相扣的链，如：

![](https://cdn.luogu.com.cn/upload/image_hosting/ld9du45d.png)

## 思路
求这个链解开多少个环可以解成若干条直链，就是在求这个链有多少个环连了大于 $2$ 个其他环，只要把这些连接数量大于 $2$ 的解开就是若干条直链。

比如一个环和 $3$ 个环相扣，就要解开 $1$ 个。

![](https://cdn.luogu.com.cn/upload/image_hosting/2tvcq4gj.png)

### 那么怎么求有几个连接数量大于 $2$ 的环呢？

我们看题，**在直链中，每个环最多连接两个其他环**，那么把链想象成无向图就是每个顶点的度不能大于 $2$，如果大于 $2$ 就要断开其他的顶点。

还是上面那个例子，最大的环的度是 $3$，就要断开 $3-2$ 个环。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,v,s;
int d[300005];
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++){
		if(d[i]>2){
			s+=max(0,d[i]-2);
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：Amberhart (赞：4)

## 题意

Bob 在制作一条铱链，但完成后发现链条不是直的。他决定断开一些环并将其重新连接到链条的其余部分。问 Bob 获得直链的最小步骤数。

## 思路

看样例就能理解题目意思。

首先要把输入的信息存到 $d$ 数组里，如果有一个点链的链条多余 $2$ 个，那就不是直的。

那要断掉多少个链条呢？

看样例一，点 $1$ 分了 $1$ 个分支，用了 $0$ 步完成。 

看样例二，点 $3$ 分了 $2$ 个分支，点 $4$ 分了 $2$ 个分支，一共是 $4$ 个分支，用了 $2$ 步完成。

看样例三，点 $3$ 分了 $2$ 个分支，用了 $1$ 步完成。

总结一下，样例一是 $1-1=0$（特殊情况，本来就是直链）;

样例二是 $4-2=2$；

样例三是 $3-2=1$。

除了样例一的特殊情况，发现都是用分支数减 $2$。

在计算的时候就要求一个 $\max$，就是 $0$（特殊情况）和 $d[i]-2$ 求一个最大值来计算。


## 注意

输入要输入 $1$ 到 $n-1$ 行，具体看题目样例。

## 代码

代码没什么好解释的，都在思路里说过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,u,v,d[300010],c;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		d[u]++;d[v]++;//将链条链起来
	}
	for(int i=1;i<=n;i++){
		if(d[i]>2){
			c=c+max(0,d[i]-2);
		}
	}
	cout<<c;
	return 0;
}

```


---

## 作者：hjsxhst2022 (赞：3)

题目大意看上一篇题解，这里就不写了。
### 思路:
1. 读取环的数量 $n$。

2. 初始化列表 $d$，其中 $d[i]$ 表示环 $i$ 相邻的环的数量，初始值赋为 $0$。

3. 读取 $n-1$ 条边的信息，每次读取一条边，即两个整数 $u$ 和 $v$，表示连接了环 $u$ 和环 $v$。

4. 在读边的时候更新列表 $d$，将 $d[u]$ 和 $d[v]$ 加 $1$，表示环 $u$ 和环 $v$ 相邻的环数加 $1$。

5. 再次遍历所有的环，对于每个环 $i$，检查它相邻的环的数量 $d[i]$。如果 $d[i]$ 大于 $2$，表示该环连接了多余的边，$d[i]-2$ 就是需要断开的连接数量，将这个数量加到 $s$ 中。

6. 最后，输出 $s$，即将未完成的链条转化为直链所需的最少步骤数。

code:
```python
n=int(input())
d=[0]*(n + 1)
s=0
for i in range(1,n):
    u,v=map(int,input().split())
    d[u]+=1
    d[v]+=1
for i in range(1,n+1):
    if d[i]>2:
        s+=max(0,d[i]-2)
print(s)
```
[AC记录](https://www.luogu.com.cn/record/124238864)

~~蒟蒻的第 9 篇题解！~~

---

## 作者：hjqhs (赞：2)

切了一道黑再来看着黄题，感觉好简单，，，  
一个 $t$ 数组，表示第 $i$ 个环上共连了 $t_i$ 个别的环。对于任意一个环，想要满足是直链的充分必要条件明显是 $t_i \le 2$。所以读入时记录 $t_i$，然后如果 $t_i \ge 3$ 就让答案加上 $t_i-2$。然后这道题就做完了。
```cpp
#include<bits/stdc++.h>
// #define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=300005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9'){
    if(ch=='-')f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<3)+(x<<1)+(ch^48);
    ch=getchar();
  }
  return x*f;
}
int n,t[N],ans;
void solve(){
  cin>>n;
  for(int i=1;i<n;++i){
    int u,v;
    cin>>u>>v;
    ++t[u],++t[v];
  }
  for(int i=1;i<=n;++i){
    if(t[i]>2)ans+=t[i]-2;
  }
  cout<<ans;
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}
```

---

## 作者：FreedomKing (赞：2)

### 题目大意

给出一棵树，求有多少个节点连接的点数 $\ge 3$。

### 思路

直接统计每条边的两个点的连接数量，一次循环判断其是否 $\ge 3$ 即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(x,y) (x>y?x:y)
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k,ans;
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		a[u]++;
		a[v]++;
	}
	for(int i=1;i<=n;i++) ans+=max(0,a[i]-2);
	cout<<ans;
	return 0;
}
```

---

## 作者：qianyuzhe (赞：2)

## 题意简述

给定一条链条上相邻环的编号，定义一个步骤如下：选择一个环 $A$，连接到未完成链中的另一个环 $B$。然后断开 $A$ 与 $B$ 的连接，并将 $A$ 重新连接到未完成的链条中的另一个环 $C$。求最少几个步骤后链条变为直链。

## 题目分析

由于要使步骤最少，因此我们可以用贪心求解。

考虑设置数组 $c$ 记录某环连接的环的数量，如果 $c_i>2$ 则说明环 $i$ 连接了超过 $2$ 个环，此时将 $c_i$ 设为 $2$，并将答案加一。

时间复杂度 $O(n)$，空间复杂度 $O(n)$，可以在输入时就进行判断，动态更新 $c$ 数组，~~优化亿点常数~~。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,r,c[300005];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	while(cin>>x>>y){
		if(++c[x]>2){//更新第一环
			c[x]--;
			r++;
		}
		if(++c[y]>2){//更新第二环
			c[y]--;
			r++;
		}
	}
	cout<<r;//输出步骤数
}
```

---

## 作者：2011FYCCCTA (赞：1)

[原题](https://www.luogu.com.cn/problem/P9608)

---
### 思路
很明显，一个环最多与 $2$ 个环相连，若多余 $2$ 个就把多出的删除，最终输出删除的个数即可。可以把每个环看成一个点，就相当于先求出每个点的度数再得出所有度数大于 $2$ 的点减 $2$ 的差的和。

---

## 作者：Miyamizu_Mitsuha (赞：1)

很好想，如果想要一条直链，那明显的一个环最多只能连两个环（左边一个右边一个），超过两个我们就需要把它断开，直到剩两个。开一个桶记录一下每一个环的连接数量，然后判断就好了。复杂度 $O(n)$。

```
#include <bits/stdc++.h>
using namespace std;

int main(){
     int n,ans=0;
     int cnt[300005]={0};
     cin>>n;
     for(int i=1;i<n;i++)
     {
	 	int u,v;
	 	cin>>u>>v;
	 	cnt[u]++;
	 	cnt[v]++;
     }
     for(int i=1;i<=n;i++)
	 	if(cnt[i]>2)
	    	ans+=(cnt[i]-2);
     cout<<ans;
     return 0;
}

```


---

## 作者：smydahaoren (赞：0)

### 题目大意

题目中给定 $n$ 个链，然后在输入两个之间有联系的链，然而 $1$ 个链最多和 $2$ 个产生联系，也就是说，多余的链要解掉。输出解掉多余链的个数。



------------
### 思路分析

[![pPcwL80.png](https://s1.ax1x.com/2023/09/10/pPcwL80.png)](https://imgse.com/i/pPcwL80)

第一张图中，$3$ 个链，每个链都只和另外两个链构成联系，所以不用解掉多余的链。

而在第二张图中，有一个链与别的链总共三个联系，那就需要去掉一个联系。

那么，要解决这道题，只需要把 $n$ 个链，每个链所有的联系数统计出来，最后判断一下是否有超过 $2$ 个的联系。



------------
### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,u,v,ans;
int d[1000009];
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++){
		if(d[i]>2){
			ans+=(d[i]-2);
		}
	}
	cout<<ans;
	return 0;
}

```


---

