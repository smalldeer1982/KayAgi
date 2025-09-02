# Guess the Cycle Size

## 题目描述

This is an interactive problem.

I want to play a game with you...

We hid from you a cyclic graph of $ n $ vertices ( $ 3 \le n \le 10^{18} $ ). A cyclic graph is an undirected graph of $ n $ vertices that form one cycle. Each vertex belongs to the cycle, i.e. the length of the cycle (the number of edges in it) is exactly $ n $ . The order of the vertices in the cycle is arbitrary.

You can make queries in the following way:

- "? a b" where $ 1 \le a, b \le 10^{18} $ and $ a \neq b $ . In response to the query, the interactor outputs on a separate line the length of random of two paths from vertex $ a $ to vertex $ b $ , or -1 if $ \max(a, b) > n $ . The interactor chooses one of the two paths with equal probability. The length of the path —is the number of edges in it.

You win if you guess the number of vertices in the hidden graph (number $ n $ ) by making no more than $ 50 $ queries.

Note that the interactor is implemented in such a way that for any ordered pair $ (a, b) $ , it always returns the same value for query "? a b", no matter how many such queries. Note that the "? b a" query may be answered differently by the interactor.

The vertices in the graph are randomly placed, and their positions are fixed in advance.

Hacks are forbidden in this problem. The number of tests the jury has is $ 50 $ .

## 说明/提示

In the first example, the graph could look like this

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1729E/9ade550fb3e264ef1dadca91be3accfdcc0d9e04.png)The lengths of the simple paths between all pairs of vertices in this case are $ 1 $ or $ 2 $ .

- The first query finds out that one of the simple paths from vertex $ 1 $ to vertex $ 2 $ has a length of $ 1 $ .
- With the second query, we find out that one of the simple paths from vertex $ 1 $ to vertex $ 3 $ has length $ 2 $ .
- In the third query, we find out that vertex $ 4 $ is not in the graph. Consequently, the size of the graph is $ 3 $ .

## 样例 #1

### 输入

```
1

2

-1```

### 输出

```
? 1 2

? 1 3

? 1 4

! 3```

# 题解

## 作者：Mashiroqwq (赞：7)

~~希望大家不要像我一样只看大意而忽略掉一些细节，所以我就免费给大家提供一个加强版做法。~~

**注意询问 $(a,b)$ 和 $(b,a)$ 不是一样的。**

# 原题

也就是询问 $(a,b)$ 和询问 $(b,a)$ 不是一样的。

考虑到如果我们询问 $(a,b)$ 和 $(b,a)$ 得到的结果不一样，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/mlp9a8l3.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

如果我们得到了 $(1,3)$ 的结果是 $2$，但是 $(3,1)$ 的结果是 $3$，那么这两条路径相当于围成了一个环，所以答案是 $2+3=5$。

所以我们只需要枚举一个点 $k$，如果 $(1,k)$ 和 $(k,1)$ 结果不同就直接输出答案，否则就继续枚举，同时注意一下询问答案等于 $-1$ 的情况即可。

当然这样是不能保证 $100\%$ 概率能求解出答案的，不过出错的概率不会大于 $\dfrac{1}{2^{24}}$，所以可以放心使用。

```cpp
for(int i=2;i<=26;++i){
	int a=ask(1,i);
	if(a==-1){
		cout << "! " << i-1 << endl;
		return 0;
	}
	int b=ask(i,1);
	if(a!=b){
		cout << "! " << a+b << endl;
		return 0;
	}
}
```

# 加强版

也就是询问 $(a,b)$ 和 $(b,a)$ 一定会返回相同的结果。

我们记 $a=ans(1,2)$，考虑枚举一个点 $k$，询问 $(1,k)$ 以及 $(2,k)$。

我们假定 $1,2,k$ 在环上的关系如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nmzrmv11.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

也就是说 $1,2$ 之间距离为 $a$，$2,k$ 之间距离为 $c$，$1,k$ 之间距离为 $b$，其中 $a,b,c \geq 1$，且有 $n=a+b+c$。

那么询问 $(2,k)$ 的结果一定是 $c$ 或 $a+b$ 两者之一，询问 $(1,k)$ 的结果一定是 $b$ 或 $a+c$ 两者之一。

我们记 $A=a,B=ans(1,k),C=(2,k)$。

- $B=b, C=c$，显然这种情况下 $A+B+C$ 就是答案，对于 $A+B+C$ 检查即可。
- $B=b, C=a+b$，这种情况下确定不了答案。
- $B=a+c,C=c$，这种情况下确定不了答案。
- $B=a+c,C=a+b$，这种情况下 $A+B+C-2 \times A=B+C-A$ 就是答案。

那么我们在枚举点 $k$ 的过程中，询问 $(1,k),(2,k),(1,A+B+C+1),(1,B+C-A+1)$ 即可，显然可以确定答案的概率为 $\dfrac{1}{2}$，每次消耗四次询问。

还有一种情况就是 $k$ 在 $1,2$ 之间长度为 $a$ 的路径上，这种情况与上述情况及其相似故不再说明。

那么我们可以从 $3$ 到 $14$ 枚举 $k$ 执行操作即可，操作次数上限为 $49$，出错概率最大为 $\dfrac{1}{2^{12}}$，足以通过本题。

```cpp
inline void F(){
	fflush(stdout);
	return ;
}

inline ll ask(int x, int y){
	if(y>1e18) return -1;	
	cout << "? " << x << ' ' << y << endl;
	ll res;F();
	cin >> res;
	return res;
}

signed main(){
	int c=ask(1,2);
	ll ans=1e18+2;
	for(int i=3;i<=14;++i){
		int a=ask(1,i);
		if(a==-1){
			cout << "! " << i-1 << endl;
			return 0;
		}
		int b=ask(2,i);
		int u=min(min(a,b),c);
		int o=ask(1,a+b+c-2*u+1);
		if(o==-1) ans=min(ans,a+b+c-2*u);
		o=ask(1,a+b+c+1);
		if(o==-1) ans=min(ans,a+b+c);
	}
	cout << "! " << ans;F();
	return 0;
}
```

---

## 作者：FFTotoro (赞：2)

Div.3 出交互题了，好感动。

因为询问次数限制为 50 次，所以我们需要利用图的一些性质。

对于两个点 $a,b$，连接他们的路径有且仅有两条，它们互相包围成了这个环。

因为交互库会从两条路径中随机选择一条，这样，我们对于点 $a,b$ 问两次，如果两次询问的回答不一样，就说明反馈的两次值是 $a$ 到 $b$ 的两条路径。这两条路径围成了这个环，所以环的长度就是两次回答的和。

我们设 $a=1$，$b$ 从 $2$ 枚举到 $26$（每个点问 $2$ 次，$25$ 个点刚好问 $50$ 次），一直询问下去，如果两次结果不等就输出并结束程序。

注意特判输出 $-1$ 的情况。

可以证明，这种算法出锅的概率几乎为 $0$。如果你还是不放心，可以在循环结束后（如果能结束）加一句 `while(1)`，将 WA 变成 TLE。因为 CF 对 TLE 的程序会**重测 3 遍**，所以在其他随机化算法出锅概率比较大的交互题中，这种方法十分好用。

放代码：

```cpp
#include<iostream>
#define int long long
using namespace std;
main(){
    ios::sync_with_stdio(false);
    for(int i=2;i<=26;i++){
        cout<<"? 1 "<<i<<endl;
        cout<<flush;
        int x; cin>>x;
        if(x==-1){
            cout<<"! "<<i-1<<endl;
            cout<<flush;
            return 0;
        }
        cout<<"? "<<i<<" 1"<<endl;
        cout<<flush;
        int y; cin>>y;
        if(x!=y){
            cout<<"! "<<x+y<<endl;
            cout<<flush;
            return 0;
        }
    }
    while(1);
}
```

---

## 作者：hereiszd (赞：2)

# 题意简述
给定一个节点数为 $n$ 的环，每次询问两点之间的路径，如果超出范围则会回答  $-1$。

现在请在最多可以进行 $50$ 次询问，请求出这个环的点数。

注意两点显然会有两条路径，但是会随机确定一条为两点的路径，换句话说，多次询问同两个点的答案总是一定的（坑点）。

# 题目分析
注意到 $n \le 10^{18}$ 二分显然会超出询问次数。

我们再来考虑这么一个问题：如果回答的两点路径一定是最短路径的话，我们询问 $(a,b)$ 与我们询问 $(b,a)$ 的答案总会相同。

可是回答不一定为最短路径，并且如果我们知道了两点的两条路径，答案便已知。

所以我们不妨询问 $25$ 组，从 $2$ 开始，每组分别询问 $(1,i)$ 和 $(i,1)$，如果两次回答不一样，设两个答案分别为 $x,y$,则点数为 $x+y$。

如果中间出现了 $-1$ 答案直接就是询问的那个点减一。

这个方法当然又可能出错，不过我们可以分析一下，设错误的概率 $p$，则 $p= \frac{1}{2^{25}}$，这个题又有 $50$ 的数据点，总的错误概率就是 $p^{50}$，基本上就是 $0$ 了。

# 代码

注意数据范围，显然需要开 ```long long```，赛时白交了一发。



```cpp
/*
	Author:zd
	Status:WA on pretest 2
*/

#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
#define int long long
int ask(int a,int b);
signed main(){
	for(int i=2;i<=26;i++){
		int fr=ask(1,i);
		int to=ask(i,1);
		if(fr==-1){
			cout<<"! "<<i-1<<endl;
			return 0;
		}
		if(to!=fr){
			cout<<"! "<<fr+to<<endl;
			return 0;
		}
	}
	return 0;
}
int ask(int a,int b){
	int l;
	cout<<"? "<<a<<' '<<b<<endl;
	cin>>l;
	return l;
}

 
```


---

## 作者：lrqlrq250 (赞：1)

~~CF 珍稀动物之交互题~~

## 解题思路
第一眼看上去是很简单的二分，直接疯狂询问 $\texttt{? 1 mid}$ 就可以在 $O(\log n)$ 的复杂度里找到答案。

理想很丰满，现实很骨感。

$\log 10^{18}$ 刚好是 $59$ 多一点，但是询问次数只有 $50$……

所以只能老老实实想正解了。

我们发现一个很神奇的东西：$\texttt{? a b}$ 和 $\texttt{? b a}$ 的值是可能不同的！

也就是说，如果我们询问了一个 $\texttt{? a b}$，然后又问了一个 $\texttt{? b a}$，并且我们发现两次的返回值（不妨设为 $dis1$ 和 $dis2$）是不一样的，就说明环上一定有 $dis1 + dis2$ 个点（分别从两侧覆盖一段弧，一定覆盖了整个环）。而能令两次返回值不同的概率有足足 $50%$！

所以我们可以做 $25$ 轮上面这种操作，每一轮先问一次 $\texttt{? 1 a}$，然后再问一次 $\texttt{? a 1}$。如果两次不同就可以输出答案了。

可以发现这样的方式可以做到只有 $\dfrac{1}{2^{25}}$ 的几率每次都让两个值相同，小到可以忽略不计……

记得如果第一次询问就直接返回 $-1$ 的话，就可以直接确定答案了。

## AC Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;


int main(){
	ll d1, d2;
	for (int i=2; i<=25; i++){
		printf("? 1 %d\n", i);
		fflush(stdout);
		scanf("%lld", &d1);
		if (d1 == -1){printf("! %lld\n", i - 1); break;}
		printf("? %d 1\n", i);
		fflush(stdout);
		scanf("%lld", &d2);
		if (d1 != d2){printf("! %lld\n", d1 + d2); break;}
	}
	return 0;
}

```

PS：由于洛谷 RMJ 正在维护，Codeforces 上的 AC 记录在[这里](https://codeforces.com/contest/1729/submission/175331206)

---

## 作者：zhicheng (赞：1)

~~随机算法真是个好东西~~

### 思路

因为题目说每次选择圈上的两条路径的概率相同，都是 $0.5$，所以我们考虑以下策略：

每次询问两次，$(1,i)$ 和 $(i,1)$。这个 $i$ 从 $2$ 开始每次增加 $1$。如果返回 $-1$，那么就表示已经越界，由于我们是依次询问的，所以 $i-1$ 就一定是最大的标号，也就是总点数。如果返回的是两个相同的数，我们无法确认到底是同一种路径还是两种路径。而当返回两个不同的数时，就可以确认这是两个不同路径，所以将两个返回值加起来就是总边数，也就等于点数。因为我们一共有 $50$ 次询问，我们可以进行上述操作 $25$ 次，每次返回值都一样的概率就是 $\dfrac{1}{2^{25}}$，足够小了。而因为有 $50$ 个测试点，完全正确的概率是 $\left(\dfrac{2^{25}-1}{2^{25}}\right)^{50}$，大约为 $0.9999985$，足够大。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long p,q;
	for(int i=2;;i++){
		printf("? 1 %d\n",i);  //两次询问
		fflush(stdout);
		scanf("%lld",&p);
		if(p==-1){  //越界
			printf("! %d",i-1);
			fflush(stdout);
			return 0;
		}
		printf("? %d 1\n",i);
		fflush(stdout);
		scanf("%lld",&q);
		if(p!=q){  //得出答案
			printf("! %d",p+q);
			fflush(stdout);
			return 0;
		}
	}
}
```
~~代码在赛时评测的时候有一个点跑了18次询问，撞大运了。~~
![](https://cdn.luogu.com.cn/upload/image_hosting/bf0oeytq.png)

---

## 作者：free_fall (赞：0)

# 题目大意
有一个隐藏的 $n$ 边形，可以用 $?$ $a$ $b$ 的形式提问，随机给出 $a$ 到 $b$ 经过的边数，如果 $a$ 或 $b$ 超过了 $n$ 返回 $-1$，要求询问不超过 $50$ 次，用 $!$ $n$ 的形式输出答案。
# 思路
因为 $a$ 或 $b$ 超过 $n$ 时会返回 $-1$，所以可以把 $a$ 确定为 $1$，然后二分 $b$，就可以得到答案。但是看一眼数据范围，最多询问次数超过 $50$ 次，直接凉凉。

其实这道题目正解简单到难以想象，从 $a$ 到 $b$ 只有两种可能性，一种顺时针走，一种逆时针走，所以只需询问 $?$ $a$ $b$ 和 $?$ $b$ $a$，如果不同则将结果相加即为答案。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int i=1;i<=25;i++){
		long long a,b;
		cout<<"?"<<" "<<i<<" "<<i+1<<endl;
		cin>>a;
		cout<<"?"<<" "<<i+1<<" "<<i<<endl;
		cin>>b;
		if(a!=b){
			cout<<"!"<<" "<<a+b;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：cheng_qi (赞：0)

~~大聪明交互题~~

### Solution

我们从 $2$ 开始枚举到 $26$，每次询问并保存 $1 \to i$ 和 $i \to 1$ 的路径长度，记为 $x$ 和 $y$，注意到每次返回的是环上两条路径的某一条路径长，当 $x \not = y$ 时，说明走的是两条不同的路径，即把整个环遍历了一遍，故得出答案为 $x+y$。若交互库返回 $-1$，说明 $i>n$。若返回 $x=y$，说明两次走的是同一条路径，则再次询问。

### 正确性证明

我们可以进行 $25$ 次上述操作，每次失败的概率为 $\frac 1 2$，$25$ 次操作都失败的概率仅为 $\frac 1 {2^{25}} \approx 3 \times 10^{-8}$，可以忽略不计。

### Code
稍微有点压行。   
交互记得 `flush`。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	for (int i = 2; i <= 26; ++i) {
		cout << "? " << 1 << " " << i << endl;
		long long x;
		cin >> x;
		cout << "? " << i << " " << 1 << endl;
		long long y;
		cin >> y;
		if (x == -1) {cout << "! " << i - 1 << endl; return 0;}
		if (x != y) {cout << "! " << x + y << endl; return 0;}
	}
	return 0;
}
```

---

## 作者：_LighT_ (赞：0)

题目传送门：[CF1729E](https://www.luogu.com.cn/problem/CF1729E)

## 思路

~~纯纯诈骗题~~

容易想到，每次询问 `? a b` 会等概率的返回劣弧长或优弧长，两者之和即为 $n$. 但由于完全相同的询问只会给出完全相同的回答，我们不妨相应地询问 `? b a`，如若给出的一对长度不同，就为答案。

最多能询问 $25$ 组，依照此方法通过的概率 $P=1-\dfrac{1}{2^{25}}$，足够理想。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int T=25;
	ll v=2,len1,len2;
	while(T--){
		cout<<"? 1 "<<v<<'\n';cout.flush();cin>>len1;
		cout<<"? "<<v<<" 1\n";cout.flush();cin>>len2;
		if(len1==-1||len2==-1){
			cout<<"! "<<v-1;
			return 0;
		}//特判节点数不足的情况
		if(len1!=len2){
			cout<<"! "<<len1+len2;
			return 0;
		}
		else ++v;
	}
	return 0;
}
```


---

