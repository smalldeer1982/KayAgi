# A+B Problem

## 题目背景

**不熟悉算法竞赛的选手请看这里：**

算法竞赛中要求的输出格式中，**不能有多余的内容**，**这也包括了“请输入整数 $\bm a$ 和 $\bm b$” 这一类的提示用户输入信息的内容**。若包含了这些内容，将会被认为是 `Wrong Answer`，即洛谷上的 `WA`。在对比代码输出和标准输出时，系统将忽略每一行结尾的空格，以及最后一行之后多余的换行符。

若因此类问题出现本机似乎输出了正确的结果，但是实际提交结果为错误的现象，请勿认为是洛谷评测机出了问题，而是你的代码中可能存在多余的输出信息。用户可以参考在题目末尾提供的代码。

此外，**请善用进入 IDE 模式**，以避免不同平台的评测产生差异。

最后，请不要在对应的题目讨论区中发布自己的题解，请发布到题解区域中，否则将处以删除或禁言的处罚。若发现无法提交题解则表明本题题解数量过多，仍不应发布讨论。若您的做法确实与其他所有题解均不一样，请联系管理员添加题解。

## 题目描述

输入两个整数 $a, b$，输出它们的和（$|a|,|b| \le {10}^9$）。

注意

1. Pascal 使用 `integer` 会爆掉哦！
2. 有负数哦！
3. C/C++ 的 main 函数必须是 `int` 类型。程序正常结束时的返回值必须是 0。这不仅对洛谷其他题目有效，而且也是 NOIP/CSP/NOI 比赛的要求！

好吧，同志们，我们就从这一题开始，向着大牛的路进发。

> 任何一个伟大的思想，都有一个微不足道的开始。

## 说明/提示

**广告**

洛谷出品的算法教材，帮助您更简单的学习基础算法。[【官方网店绝赞热卖中！】>>>](https://item.taobao.com/item.htm?id=637730514783)

[![](https://cdn.luogu.com.cn/upload/image_hosting/njc7dlng.png)](https://item.taobao.com/item.htm?id=637730514783)

**本题各种语言的程序范例：**

C
```c
#include <stdio.h>

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d\n", a+b);
    return 0;
}
```
----------------

C++
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a,b;
    cin >> a >> b;
    cout << a+b << endl;
    return 0;
}
```
----------------

Pascal
```cpp
var a, b: longint;
begin
    readln(a,b);
    writeln(a+b);
end.
```
-----------------

Python 3

```python
s = input().split()
print(int(s[0]) + int(s[1]))
```
-----------------

Java
```java
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String args[]) throws Exception {
        Scanner cin=new Scanner(System.in);
        int a = cin.nextInt(), b = cin.nextInt();
        System.out.println(a+b);
    }
}
```
-----------------

JavaScript （Node.js）

```javascript
const fs = require('fs')
const data = fs.readFileSync('/dev/stdin')
const result = data.toString('ascii').trim().split(' ').map(x => parseInt(x)).reduce((a, b) => a + b, 0)
console.log(result)
process.exit() // 请注意必须在出口点处加入此行
```

-----------------

Ruby

```ruby
a, b = gets.split.map(&:to_i)
print a+b
```

-----------------

PHP

```php
<?php
$input = trim(file_get_contents("php://stdin"));
list($a, $b) = explode(' ', $input);
echo $a + $b;
```

-----------------

Rust

```rust
use std::io;

fn main(){
    let mut input=String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s=input.trim().split(' ');

    let a:i32=s.next().unwrap()
               .parse().unwrap();
    let b:i32=s.next().unwrap()
               .parse().unwrap();
    println!("{}",a+b);
}
```

-----------------

Go

```go
package main

import "fmt"

func main() {
    var a, b int
    fmt.Scanf("%d%d", &a, &b)
    fmt.Println(a+b)
}
```

-----------------

C# Mono

```cs
using System;

public class APlusB{
    private static void Main(){
        string[] input = Console.ReadLine().Split(' ');
        Console.WriteLine(int.Parse(input[0]) + int.Parse(input[1]));
    }
}
```

------------------

Kotlin

```kotlin
fun main(args: Array<String>) {
    val (a, b) = readLine()!!.split(' ').map(String::toInt)
    println(a + b)
}
```

------------------

Haskell

```haskell
main = do
    [a, b] <- (map read . words) `fmap` getLine
    print (a+b)
```

------------------

Lua

```lua
a = io.read('*n')
b = io.read('*n')
print(a + b)
```

------------------

OCaml

```ocaml
Scanf.scanf "%i %i\n" (fun a b -> print_int (a + b))
```

------------------

Julia

```julia
nums = map(x -> parse(Int, x), split(readline(), " "))
println(nums[1] + nums[2])
```

------------------

Scala

```scala
object Main extends App {
    println(scala.io.StdIn.readLine().split(" ").map(_.toInt).sum)
}
```

------------------

Perl

```perl
my $in = <STDIN>;
chomp $in;
$in = [split /[\s,]+/, $in];
my $c = $in->[0] + $in->[1];
print "$c\n";
```

## 样例 #1

### 输入

```
20 30
```

### 输出

```
50
```

# 题解

## 作者：lin_toto (赞：5181)

本题的恶搞题解到此为止。

为防止新人受到误导，不再接受新的此类题解。

以前的保留不会删除，但请不要再提交。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int a,b;
    cin >> a >> b;
    cout << a+b;
    return 0;
}
```

---

## 作者：fish_love_cat (赞：283)

2017 年的管理组：

> 本题的恶搞题解到此为止。
>
> 为防止新人受到误导，不再接受新的此类题解。
> 
> 以前的保留不会删除，但请不要再提交。

2025 年的管理组：

> 鼓励全新的大炮（核弹）打蚊子技术。

---

注意到是大炮打蚊子而不是其他什么的，合理推测大炮在本题中有着极其重要的地位。

观察大炮这个词语，注意到其首字母是 dp，而主题库内的算法标签恰好有动态规划 dp，这启示我们利用动态规划通过此题。

于是我们定义 $f_{i,j}$ 为 $i+j$ 的值，答案即为 $f_{a,b}$。

接下来考虑转移。

注意到 $f_{i,j}=f_{i,j-1}+1$，于是就可以照着转移了。

时间复杂度 $O(n^2)$。

但是数据范围太大了！我们需要优化这个柿子。

又注意到 $f_{i,j}=f_{i,0}+j$，于是这样我们就优化成了 $O(n)$。

可还是过不了，怎么办？

因为 $f_{i,0}>f_{i-1,0}$，具有单调性，可以使用二分来优化 dp。

考虑二分 $i$ 的值，找到后进行转移。

可是数组开不下，而且有负数呢！

我有一计，线性 dp 有点难做，那我们原创一种常数 dp 吧！

由于我~~贿赂了管理员窃取了数据~~进行了打表，得到结论 $f_{i,0}=i$，虽然我不会证，但是，很神奇吧！

管理员会不会要我补充对于重要结论的证明呢。

那么还是证明一下的好：

首先 $f_{i,j}=i+j$。

因为 $j=0$，于是 $f_{i,0}=i+0=i$。

所以 $f_{i,0}=i$！

那么我们只需要初始化一下，然后进行转移就可以了！

这个时候有人要问了，主播主播那你怎么开数组呢？

答案是红黑树！实现的 `map`。

于是我们就写完啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,int>mp;
int main(){
    int a,b;
    cin>>a>>b;
    mp[make_pair(a,0)]=a;
    mp[make_pair(a,b)]=mp[make_pair(a,0)]+b;
    cout<<mp[make_pair(a,b)];
    return 0;
}
```

总结，这是一道非常棒的常数 dp 练手题。

但是这个算法不在 CCF 的考纲上，应该是 CCF 太弱了还不会这么高级的算法，对吧。

不考实在太可惜了。

---

怎么评论区都在问证明这句话的意思：

> 所以 $f_{i,0}=i$！

所以解释一下吧。

观察式子，注意到是中文感叹号，这启示我们并非阶乘。

换 @[llamn](https://www.luogu.com.cn/user/1038651) 言之：

观察题解，注意到原文 `$f_{i,0}=i$！` 中感叹号没有在 $\LaTeX$ 公式中，启示我们感叹号的含义并非阶乘。

观察。注意。启示。

---

## 作者：洛谷视频题解 (赞：272)

![](bilibili:BV1ew411Z76w?page=1)

## 广告

洛谷出品教材《深入浅出程序设计竞赛 - 基础篇》，助力轻松入门算法！[【点击此处购买 >>】](https://item.taobao.com/item.htm?id=637730514783)

[![](https://cdn.luogu.com.cn/upload/image_hosting/v70qsqm4.png)](https://item.taobao.com/item.htm?id=637730514783)

---

## 作者：chen_zhe (赞：252)

# P1001 - A+B Problem

输入两个整数 $a,b$，输出它们的和（$|a|,|b|\leq 10^9$）。

注意

1. Pascal 使用 integer 会爆掉哦！
2. 有负数哦！
3. C/C++ 的 main 函数必须是 int 类型，而且最后要 return 0。这不仅对洛谷其他题目有效，而且也是 NOIP/NOI/CSP 比赛的要求！

好吧，同志们，我们就从这一题开始，向着大牛的路进发。

> 任何一个伟大的思想，都有一个微不足道的开始。

----

神题，做法多种多样。

首先，我们可以发现这题有个最简单的做法，就是读入 $a,b$，输出 $a+b$ 即可。代码如下：

```cpp
namespace solver1
{
	int a,b;
	
	inline void solve()
	{
		a=read(),b=read();
		cout << a+b << endl;
	}
}
```

虽然能 AC，但是洛谷上很多神题，因此我觉得这题不应该这么简单。

首先，这个题很明显可以不用加号，因此有如下做法（自欺欺人）：

```cpp
namespace solver2
{
	int a,b;
	
	inline void solve()
	{
		a=read(),b=read();
		cout << a-(-b) << endl;
	}
}
```

我们还可以考虑如何不用 `+,-` 两个符号完成这个题。考虑一下进行加法的本质是每一个位上的进位，而要产生进位，也就是两个对应位上都是 $1$ 才会产生进位。这个是可以通过 `a&b` 得到的。而如果我们进行 `a^b` 则可以得到两个位在不考虑其他位上的进位的时候的加法计算结果。因为 `0^1=1^0=1`，相当于没有进位的加 $1$，而 `1^1=0`，相当于 $1+1$ 产生进位，而 `0^0=0` 相当于两位都是 $0$，相加也是 $0$。因此我们可以使用异或以及与运算完成加法。具体请看代码。

``` cpp
namespace solver3
{
	int a,b;
	
	inline void solve()
	{
		a=read(),b=read();
		while (b!=0)
		{
			int _a=a^b;
			int _b=(a&b)<<1;
			a=_a;
			b=_b;
		}
		cout << a << endl;
	}
}
```

接下来有一些别的方法。

首先，如果我们有两个集合 $\{A\},\{B\}$，其中 $|A|=a,|B|=b$，我们把两个集合合并，得到集合的秩的大小，那么就可以很好地完成了。

反正我们也不知道我们集合里面是什么东西就干脆用并查集吧，不用开个 `set`。

```cpp
namespace solver4
{
	int a[5],fa[5],size[5];
	
	inline void Init()
	{
		for (int i=1;i<=2;i++)
		{
			fa[i]=i;
			size[i]=a[i];
		}
	}
	
	inline int Find(int x)
	{
		return fa[x]==x?x:fa[x]=Find(fa[x]);
	}
	
	inline void Merge(int x,int y)
	{
		int fx=Find(x),fy=Find(y);
		if (fx!=fy)
		{
			fa[fy]=fx;
			size[fx]+=size[fy];
		}
	}
	
	inline void solve()
	{
		a[1]=read(),a[2]=read();
		Init();
		Merge(1,2);
		cout << size[1] << endl;
	}
}
```

我们还可以考虑，如果目前有一张图，有 $3$ 个节点 $1 \to 2,2 \to 3$，那么令每条边的边权分别是 $a,b$，那么最后的答案就是这个图的最小生成树，当然最大生成树也是可以的。因为我只会 kruskal，所以代码如下：

```cpp
namespace solver5
{
	int a[5],fa[5];
	
	struct node
	{
		int u,v,w;
		bool operator < (const node &rhs) const
		{
			return w<rhs.w;
		}
	}edge[5];
	
	inline void Init()
	{
		for (int i=1;i<=2;i++)
			fa[i]=i;
	}
	
	inline int Find(int x)
	{
		return fa[x]==x?x:fa[x]=Find(fa[x]);
	}
	
	inline void Merge(int x,int y)
	{
		int fx=Find(x),fy=Find(y);
		if (fx!=fy)
			fa[fy]=fx;
	}
	
	inline void solve()
	{
		a[1]=read(),a[2]=read();
		Init();
		sort(a+1,a+3);
		edge[1]={1,2,a[1]};
		edge[2]={2,3,a[2]};
		int ans=0;
		for (int i=1;i<=2;i++)
		{
			auto e=edge[i];
			int u=edge[i].u,v=edge[i].v;
			int fu=Find(u),fv=Find(v);
			if (fu!=fv)
			{
				ans+=e.w;
				Merge(fu,fv);
			}
		}
		cout << ans << endl;
	}
}
```

当然，如果你真建立出这张图，那么我们甚至可以使用 dijkstra 跑从 $1 \to 3$ 的最短路径，也可以算出我们要求的答案。

```cpp
namespace solver6
{
	struct node
	{
		int to,dis;
		
		bool operator < (const node &rhs) const
		{
			return dis<rhs.dis;
		}
	};
	
	priority_queue <node> q;
	
	vector <node> G[5];
	
	int dis[5],vis[5];
	
	inline void Dijkstra()
	{
		memset(dis,0x7f,sizeof(dis));
		q.push({1,0});
		dis[1]=0;
		while (!q.empty())
		{
			node rhs=q.top();
			q.pop();
			int u=rhs.to;
			if (vis[u])
				continue;
			for (int i=0;i<G[u].size();i++)
			{
				rhs=G[u][i];
				int v=rhs.to,d=rhs.dis;
				if (dis[v]>dis[u]+d)
				{
					dis[v]=dis[u]+d;
					q.push({v,dis[v]});
				}
			}
		}
	}
	
	inline void solve()
	{
		int a=read(),b=read();
		G[1].push_back({2,a});
		G[2].push_back({3,b});
		Dijkstra();
		cout << dis[3] << endl;
	}
}
```

当然，有一些很奇妙的方法。我们考虑一下网络流解法。当然因为里面有负权，所以应该取绝对值然后判断要不要减回去。

第一种解法是最大流。两条边流量分别是 $a,b$，这样的确就可以得到 $a+b$。

```cpp
namespace solver7
{
	int head[50],tail[50],next[50],r[50],ecnt=1,s=1,t=4,d[50],cur[50],flow;

	inline void link(int u,int v,int w)
	{
		next[++ecnt]=head[u];
		head[u]=ecnt;
		tail[ecnt]=v;
		r[ecnt]=w;
		next[++ecnt]=head[v];
		head[v]=ecnt;
		tail[ecnt]=u;
		r[ecnt]=0;
	}
	
	inline bool BFS()
	{
		queue <int> q;
		q.push(t);
		memset(d,0,sizeof(d));
		d[t]=1;
		while (!q.empty())
		{
			int u=q.front();
			q.pop();
			for (int i=head[u];i;i=next[i])
			{
				int v=tail[i];
				if (d[v]==0 && r[i^1]>0)
				{
					d[v]=d[u]+1;
					q.push(v);
				}
			}
		}
		return d[s]>0;
	}
	
	inline int DFS(int u,int budget)
	{
		if (u==t)
			return budget;
		int res=0;
		for (int &e=cur[u];e;e=next[e])
		{
			int v=tail[e];
			if (d[v]+1==d[u] && r[e]>0)
			{
				int delta=DFS(v,min(r[e],budget));
				if (delta)
				{
					r[e]-=delta;
					r[e^1]+=delta;
					flow+=delta;
					budget-=delta;
					res+=delta;
				}
			}
		}
		return res;
	}
	
	inline int Dinic()
	{
		int ans=0;
		while (BFS())
		{
			for (int i=s;i<=t;i++)
				cur[i]=head[i];
			ans+=DFS(s,1145141919);
		}
		return ans;
	}
	
	inline void solve()
	{
		int f=0;
		int a=read(),b=read();
		if (a<0)
		{
			a=abs(a);
			f|=1;
		}
		if (b<0)
		{
			b=abs(b);
			f|=2;
		}
		link(1,2,a);
		link(1,3,b);
		link(2,4,1145141919);
		link(3,4,1145141919);
		int ans=Dinic();
		if (f&1)
			ans-=2*a;
		if (f&2)
			ans-=2*b;
		cout << ans << endl;
	}
}
```

第二种解法是费用流。我们考虑一条边的费用是 $a$，一条边的费用是 $b$，单位流量的费用为 $1$，则可以使用最小费用最大流解决，在这里我采用的是原始对偶 （primal-dual） 算法求费用流。好像写原始对偶是不用判负了（

```cpp
namespace solver8
{
	struct node
	{
		int to,dis;
		bool operator < (const node &rhs) const
		{
			return dis>rhs.dis;
		}
	};
	
	int d[10],preu[10],pree[10];
	
	bool inq[10];
	
	int e=1,w[10],r[10],first[10],next[10],cost=0,flow=0,tail[10],h[10];
	
	void link(int u,int v,int re,int weight)
	{
	    next[++e]=first[u];
	    first[u]=e;
	    tail[e]=v;
	    r[e]=re;
	    w[e]=weight;
	    next[++e]=first[v];
	    first[v]=e;
	    tail[e]=u;
	    r[e]=0;
	    w[e]=-weight;
	    
	}
	
	int s=1,t=3;
	
	bool vis[100050];
	
	inline void dijkstra()
	{
		for (int i=1;i<=5;i++)
		{
			vis[i]=0;
			d[i]=INT_MAX;
		}
		d[s]=0;
		priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
		q.empty();
		q.push(pair<int,int>(0,s));
		while (!q.empty())
		{
			pair <int,int> rhs=q.top();
			q.pop();
			int u=rhs.second;
			if (vis[u])
				continue;
			for (int i=first[u];i;i=next[i])
			{
				int v=tail[i];
				if (r[i]>0 && d[v]>d[u]+w[i]+h[u]-h[v])
				{
					d[v]=d[u]+w[i]+h[u]-h[v];
					preu[v]=u;
					pree[v]=i;
					q.push(pair<int,int>(d[v],v));
				}
			}
		}
	}
	
	inline void MinCostMaxFlow()
	{
		memset(h,0,sizeof(h));
		while (1)
		{
			dijkstra();
			if (d[t]==INT_MAX)
				break;
			else
			{
				for (int u=1;u<=3;u++)
					h[u]+=d[u];
				int delta=INT_MAX;
				for (int u=t;u!=s;u=preu[u])
				{
					int e=pree[u];
					delta=min(delta,r[e]);
				}
				flow+=delta;
				cost+=delta*h[t];
				for (int u=t;u!=s;u=preu[u])
				{
					int e=pree[u];
					r[e]-=delta;
					r[e^1]+=delta;
				}
			}
		}
	}
	
	inline void solve()
	{
		int a=read(),b=read();
		link(1,2,1,a);
		link(2,3,1,b);
		MinCostMaxFlow();
		cout << cost << endl;
	}
}
```

接下来我们考虑把它丢到序列上。

我们假设有一个数列 $\{A_n\}$，那么我们令 $A_1=a,A_2=b$。

我们把数列做个前缀和，再用 $S_2-S_0$ 的差分，就可以得到 $a+b$ 的大小。

```cpp
namespace solver9
{
	int a[5],S[5];
	
	inline void solve()
	{
		for (int i=1;i<=2;i++)
			a[i]=read();
		for (int i=1;i<=2;i++)
			S[i]=S[i-1]+a[i];
		cout << S[2]-S[0] << endl;
	}
}

```

当然如果只是读入 `a[i]` 的话显得不高级。我们考虑几个可以维护区间的数据结构。

首先是树状数组，单点修改，区间查询和：

```cpp
namespace solver10
{
	int f[10];
	
	inline int Lowbit(int x)
	{
		return x&-x;
	}
	
	inline void Change(int k,int x)
	{
		while (k<=5)
		{
			f[k]+=x;
			k+=Lowbit(k);
		}
	}
	
	inline int Query(int k)
	{
		int ans=0;
		while (k)
		{
			ans+=f[k];
			k-=Lowbit(k);
		}
		return ans;
	}
	
	inline void solve()
	{
		Change(1,read());
		Change(2,read());
		cout << Query(2) << endl;
	}
}
```

然后是线段树区间修改区间求和。

```cpp
namespace solver11
{
	struct SegTree
	{
		int l,r;
		long long val,tag;
	}t[50];
	
	inline void Push_Up(int id)
	{
		t[id].val=t[id<<1].val+t[id<<1|1].val;
	}
	
	inline void Push_Down(int id)
	{
		if (t[id].tag)
		{
			int mid=(t[id].l+t[id].r)>>1;
			t[id<<1].tag+=t[id].tag;
			t[id<<1|1].tag+=t[id].tag;
			t[id<<1].val+=(mid-t[id].l+1)*t[id].tag;
			t[id<<1|1].val+=(t[id].r-mid)*t[id].tag;
			t[id].tag=0;
		}
	}
	
	inline void Build(int id,int l,int r)
	{
		t[id].l=l;
		t[id].r=r;
		if (l==r)
			return;
		int mid=(l+r)>>1;
		Build(id<<1,l,mid);
		Build(id<<1|1,mid+1,r);
		Push_Up(id);
	}
	
	inline void Change(int id,int l,int r,int val)
	{
		if (l<=t[id].l && t[id].r<=r)
		{
			t[id].tag+=val;
			t[id].val+=val*(t[id].r-t[id].l+1);
			return;
		}
		Push_Down(id);
		int mid=(t[id].l+t[id].r)>>1;
		if (r<=mid)
			Change(id<<1,l,r,val);
		else if (l>mid)
			Change(id<<1|1,l,r,val);
		else
		{
			Change(id<<1,l,mid,val);
			Change(id<<1|1,mid+1,r,val);
		}
		Push_Up(id);
	}
	
	inline long long Query(int id,int l,int r)
	{
		if (l<=t[id].l && t[id].r<=r)
			return t[id].val;
		Push_Down(id);
		int mid=(t[id].l+t[id].r)>>1;
		if (r<=mid)
			return Query(id<<1,l,r);
		else if (l>mid)
			return Query(id<<1|1,l,r);
		else
			return Query(id<<1,l,mid)+Query(id<<1|1,mid+1,r);
	}
	
	inline void solve()
	{
		Build(1,1,2);
		Change(1,1,1,read());
		Change(1,2,2,read());
		cout << Query(1,1,2) << endl;
	}
}
```

那么平衡树也可以做。咕咕咕。

---

## 作者：ghj1222 (赞：127)

位运算cpp版的，注释已经加上了。

我认为计算机在执行的时候也是这样子的。

大意就是按照十进制竖式加法的方式来计算二进制的。先算出不进位的值(通过xor)，然后算出进位(通过and)，之后递归调用，两者加起来就行了

```cpp
#include <iostream>
using namespace std;
int plus(int a,int b)//这个是加法运算函数
{
    if(b==0)//如果b(进位)是0(没有进位了)，返回a的值
        return a;
    else
    {
        int xor,carry;
        xor=a^b;//xor是a和b不进位加法的值
        carry=(a&b)<<1;//carry是a和b进位的值(只有两个都是1才会产生进位，所以是与运算。左移一位是因为二进制加法和十进制加法竖式一样进位要加在左面一位里)
        return plus(xor,carry);//把不进位加法和进位的值的和就是结果
    }
}
int main()
{
    int a,b;
    cin >> a >> b;
    cout << plus(a,b) << endl;
    return 0;
}
``` 
正解
```cpp
#include <iostream>
using namespace std;
int main()
{
    int a,b;
    cin >> a >> b;
    cout << a+b << endl;
    return 0;
}
```
最短代码

```cpp
#include <cstdio>
int main(int a,int b)
{
    return (scanf("%d%d",&a,&b),printf("%d\n",a+b))&0;
}
```

---

## 作者：Nights_watcher (赞：107)

![](https://cdn.luogu.com.cn/upload/image_hosting/t575866y.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

该给我过题解了

[AC记录](https://www.luogu.com.cn/record/216939005)

这是一道特别困难的题目，难度应该有紫题。

我们可以发现，$a$ 和 $b$ 的数据范围特别大，居然超过了 `short`！我们只好拿出秘密武器：高精度。我们可以发现 $(a+b)^2=a^2+b^2+2ab$。所以可以使用高精度乘法算出来 $a^2,b^2,2ab$，再使用高精度开根算出绝对值 $a+b$。这时候我们就需要特判。若 $a$ 为正数且 $b$ 为正数，则 $a+b$ 为正数。若 $a$ 为负数且 $b$ 为负数，则 $a+b$ 为负数。若 $a$ 与 $b$ 一正一负，则要比较 $a$ 与 $b$ 的绝对值，用到高精度比较。

高精度开根难度为紫，高精度乘法难度为绿，高精度加法难度为橙，高精度比较难度为橙，为什么这题是红题！

上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string qf (string a)
{
	if (a[0] == '-') return a.substr (1 , a.size () - 1);
	return "-" + a;
}
string operator - (string a) {return qf (a);}
string gjc (string a , string b)
{
	if (a[0] == '-' && b[0] == '-') return gjc (- a , - b);
	else if (a[0] == '-') return - gjc (- a , b);
	else if (b[0] == '-') return - gjc (a , - b);
	int ans[a.size () + b.size ()] = {};
	reverse (a.begin () , a.end ());
	reverse (b.begin () , b.end ());
	for (int i = 0;i < a.size ();i ++)
		for (int j = 0;j < b.size ();j ++) ans[i + j] += (a[i] - '0') * (b[j] - '0');
	for (int i = 0;i < a.size () + b.size ();i ++)
		if (ans[i] > 9)
		{
			int x = ans[i] % 10 , y = ans[i] / 10;
			ans[i] = x;
			ans[i + 1] += y;
		}
	string ans2 = "";
	for (int i = 1;i <= a.size () + b.size ();i ++) ans2 += (char) (ans[i - 1] + '0');
	if (ans2[ans2.size () - 1] == '0') ans2 = ans2.substr (0 , ans2.size () - 1);
	reverse (ans2.begin () , ans2.end ());
	return ans2;
}
string max (string a , string b)
{
	if (a[0] == '-' && b[0] == '-')
	{
		if (- max (- a , - b) == a) return b;
		return a;
	}
	else if (a[0] == '-') return b;
	else if (b[0] == '-') return a;
	else if (a.size () > b.size ()) return a;
	else if (a.size () < b.size ()) return b;
	else
	{
		for (int i = 0;i < a.size ();i ++)
			if (a[i] > b[i]) return a;
			else if (a[i] < b[i]) return b;
		return a;
	}
}
string min (string a , string b)
{
	if (max (a , b) == a) return b;
	return a;
}
string gjj (string a , string b);
string cut (string a , string b)
{
	if (a[0] == '-' && b[0] == '-') return cut (- b , - a);
	else if (a[0] == '-') return - gjj (- a , b);
	else if (b[0] == '-') return gjj (b , - a);
	else if (max (a , b) != a) return - cut (b , a);
	reverse (a.begin () , a.end ());
	reverse (b.begin () , b.end ());
	string ans = "";
	for (int i = 1;i <= a.size () + 1;i ++) ans += "0";
	for (int i = 0;i < b.size ();i ++) ans[i] += a[i] - b[i];
	for (int i = b.size ();i < a.size ();i ++) ans[i] = a[i];
	for (int i = 0;i < ans.size ();i ++)
		if (ans[i] < '0')
		{
			ans[i] += 10;
			ans[i + 1] -= 1;
		}
	while (ans.size () > 1 && ans[ans.size () - 1] == '0') ans = ans.substr (0 , ans.size () - 1);
	reverse (ans.begin () , ans.end ());
	return ans;
}
string gjj (string a , string b)
{
	if (a[0] == '-' && b[0] == '-') return - gjc (- a , - b);
	else if (a[0] == '-') return cut (b , - a);
	else if (b[0] == '-') return cut (a , - b);
	if (a.size () < b.size ()) swap (a , b);
	reverse (a.begin () , a.end ());
	reverse (b.begin () , b.end ());
	string ans = "";
	for (int i = 1;i <= a.size () + 1;i ++) ans += "0";
	for (int i = 0;i < b.size ();i ++) ans[i] += a[i] - '0' + b[i] - '0';
	for (int i = b.size ();i < a.size ();i ++) ans[i] = a[i];
	for (int i = 0;i < ans.size ();i ++)
		if (ans[i] > '9')
		{
			ans[i] -= 10;
			ans[i + 1] += 1;
		}
	if (ans[ans.size () - 1] == '0') ans = ans.substr (0 , ans.size () - 1);
	reverse (ans.begin () , ans.end ());
	return ans;
}
string dev (string b , int a)
{
	if (a < 0 && b[0] == '-') return dev (- b , - a);
	else if (a < 0) return - dev (b , - a);
	else if (b[0] == '-') return - dev (- b , a);
	while (a % 10 == 0 && b[b.size () - 1] == '0')
    {
        a /= 10;
        b = b.substr (0 , b.size () - 1);
    }
	string ans = "";
	int yu = 0;
	for (int i = 0;i < b.size ();i ++)
	{
		yu = yu * 10 + b[i] - '0';
		ans += yu / a + '0';
		yu %= a;
	}
	while (ans.size () > 1 && ans[0] == '0') ans = ans.substr (1);
	return ans;
}
string operator / (string a , int b) {return dev (a , b);}
string operator * (string a , string b) {return gjc (a , b);}
string operator + (string a , string b) {return gjj (a , b);}
string operator - (string a , string b) {return cut (a , b);}
string sqrt (string s)
{
	if (s == "0") return "0";
	if (s == "1") return "1";
	string l = "1" , r = "1" , ans , dan = "1";
	for (int i = 1;i < s.size () / 2;i ++) l += "0";
	for (int i = 1;i <= s.size () / 2 + 1;i ++) r += "0";
	while (max (l , r) == r)
	{
		string mid = (l + r) / 2;
		if (max (mid * mid , s) == s)
		{
			ans = mid;
			l = gjj (mid , dan);
		}
		else r = mid - dan;
	}
	return ans;
}
signed main ()
{
	string a , b , c = "2";
	cin >> a >> b;
	if (a[0] == '-' && b[0] == '-')	cout << - sqrt (a * a + b * b + c * a * b);
	else if (a[0] == '-')
	{
		if (max (- a , b) == b) cout << sqrt (a * a + b * b + c * a * b);
		else cout << - sqrt (a * a + b * b + c * a * b);
	}
	else if (b[0] == '-')
	{
		if (max (- b , a) == a) cout << sqrt (a * a + b * b + c * a * b);
		else cout << - sqrt (a * a + b * b + c * a * b);
	}
	else cout << sqrt (a * a + b * b + c * a * b);
}
```

---

## 作者：Eason_cyx (赞：100)

在 C++ 中，我们可以用以下方法定义一个变量：

```cpp
int x;
```

其中，`int` 是变量类型名，这种变量可以存储 $-2^{31}\sim2^{31}-1$ 之间的整数。而 $x$ 就是你的变量名了。因为本题中 $-2\times10^9 \le a+b \le 2\times10^9$，满足这个存储条件，所以我们使用 `int` 就可以了。

我们可以用 `cin >> x;` 来读入一个变量 `x`。对于多个变量，在后面多加几个 `>>` 即可，例如 `cin >> a >> b;` 和 `cin >> qwq >> awa >> luogu >> esc;`。

至于输出，我们可以用 `cout << x;` 来输出一个变量 `x`，如果要输出多个，和 `cin` 同理。如果你想换行，可以使用 `endl`。如 `cout << Eason_cyx << endl;` 可以输出一个名为 `Eason_cyx` 的变量的值，并换行。

上面的 `cout` 和 `cin` 都在 `iostream` 头文件中，所以记得导入这个头文件！同时，由于一些命名空间的问题，你还需要使用 `using namespace std;` 才能使用这两个函数。关于命名空间可以自行搜索。

以上就是本题的讲解。下面是代码。

```cpp
#include <iostream> 
using namespace std;
int main() {
    int a,b;
    cin >> a >> b;
    cout << a+b << endl;
    return 0;
}
```

---

## 作者：Moya_Rao (赞：86)

今天想来带大家讲一个 P1001 的题解啦喵！

首先我们需要认识一个东西——它的名字叫做头文件喵！

头文件是什么喵？请看下面：
```
#include<bits/stdc++.h>
using namespace std;

int main(){
    
    return 0;
}
```

学习 OI 的萌新们呀喵，你们要明白，我们的代码需要写上这一段话才能够正常运行呢喵！

喵，当然第一行可以换成其他的，但我用的是万能的喵，不用写很多！是不是很轻松喵？

那么我们学习 OI 就得先把这段话背下来咯喵！

接着咱们来看题喵：题目会给你两个整数 $a$ 和 $b$ 然后要求你算 $a+b$ 是多少喵！

那我们就可以在代码里定义两个 `int` 类型的变量 $a$ 和 $b$ 来存储数值啦喵！至于 `int` 类型是什么？就是整数类型啦喵！当然，不是所有整数都能存的，太大的就放不进啦喵！

好的，那接下来就是算和了。也很简单吧喵，我们再定义一个变量 $c$，让 $c$ 的值为 $a+b$，最后把 $c$ 输出就好啦！

可是到底该怎么输入，又该怎么输出呢？很简单的，输入就是 `cin` 函数，输出就是 `cout` 函数！

这样就可以通过本题啦！

那么我在此放上本题的参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main(){
    cin>>a;
    cin>>b;
    c=a+b;
    cout<<c;
    return 0;
}
```

通过本题之后，可以尝试一下 [B2002](https://www.luogu.com.cn/problem/B2002) 哦！

希望各位能够开心快乐地学习 OI！我们下次再见咯！~~下次我还是去写蓝题题解吧~~

---

## 作者：headless_piston (赞：81)

大炮维护日志：修改了大炮的运行逻辑，特别优化了其在对蚊子实施打击时的使用体验。同时，同步更新了《大炮使用手册》，润色了一些句子，并增添了对大炮新功能的说明。
### 思路：
观察数据范围，发现答案竟然在 $[-2^{31},2^{31}-1]$ 范围内，为了防止溢出，我们考虑使用高精度算法，然而朴素的高精度算法时间复杂度为 $O(n)$，也许需要一定程度的优化。  
我们知道，FFT（快速傅里叶变换）可以高效地计算多项式卷积，因此被用来优化乘法的计算。借用这种算法，我们尝试对加法进行优化。具体思路借用了[这道题](https://www.luogu.com.cn/problem/P1919)。  
FFT 具有线性性质。这也是我们应用其优化运算的基础。具体地，对于两个序列 $a$ 和 $b$，有 $\operatorname{FFT}(a\times b)=\operatorname{FFT}(a)\times \operatorname{FFT}(b)$，同理，有 $\operatorname{FFT}(a+ b)=\operatorname{FFT}(a)+\operatorname{FFT}(b)$，考虑利用这个性质，对 $a$ 和 $b$ 进行 FFT，然后将结果相加，最后再对相加后的结果逆 FFT 即得答案。

### 常数优化：
高精度运算的一种简单且有效的优化方式就是压位，然而 FFT 在计算过程中涉及浮点运算，这会带来严重的精度问题，尤其是在使用压位高精的时候。所以我们只压两位。对于本题，$\dfrac{1}{2}$ 的常数已经足够了。
### 使用体验优化：
为了方便大炮的使用，我对其进行了封装，同时内附一份标准的 FFT 优化高精度乘法运算模板。
```cpp
#include<cmath>
#include<iostream>
#include<cstring>
//********一些辅助函数与FFT实现
const double PI=4*atan(1);
template<typename T>
void Swap(T &a,T &b){
	T c=a;
	a=b;
	b=c;
	return;
}
template<typename T>
T Max(const T &a,const T &b){
	return a<b?b:a;
}
typedef long long ll;
struct comp{
	double real,imag;
	comp operator+(const comp &x)const{
		return {real+x.real,imag+x.imag};
	}
	comp operator-(const comp &x)const{
		return {real-x.real,imag-x.imag};
	}
	comp operator*(const comp &x)const{
		return {real*x.real-imag*x.imag,real*x.imag+x.real*imag};
	}
	comp operator/(const unsigned &x)const{
		return {real/(double)x,imag/(double)x};
	}
};
void FFT(comp *f,unsigned n,int rev){
	for(unsigned i=1,j=n>>1,k;i<n-1;i++){//位逆序置换
		if(i<j)
			Swap(f[i],f[j]);
		k=n>>1;
		while(j>=k){
			j-=k;
			k>>=1;
		}
		j+=k;
	}
	for(unsigned l=2;l<=n;l<<=1){//蝶形运算
		double arg=2*PI*rev/l;
		comp wn={cos(arg),sin(arg)};
		for(unsigned i=0;i<n;i+=l){
			comp w={1,0};
			for(unsigned j=0;j<(l>>1);j++){
				comp f1=f[i+j];
				comp f2=f[i+j+(l>>1)];
				f[i+j]=f1+w*f2;
				f[i+j+(l>>1)]=f1-w*f2;
				w=w*wn;
			}
		}
	}
	if(!~rev)
		for(unsigned i=0;i<n;i++)
			f[i]=f[i]/n;
}
//********高精度整数类
#define BASE 100//因为FFT的精度问题严重，我们只压2位
template<const unsigned Size>
class bigint{
private:
	unsigned len;
	int num[Size];
	void init(){
		memset(num,0,sizeof(num));
		len=1;
	}
	bool abs_greater_equal(const bigint &a)const{
		if(len!=a.len)
			return len>a.len;
		for(int i=len;i;i--)
			if(num[i]!=a.num[i])
				return num[i]>a.num[i];
		return 1;
	}
public:
	bigint(){
		init();
	}
	void get_num(std::string s){
		init();
		int f=0;
		unsigned slen=s.length();
		if(s[0]=='-')
			num[0]=f=1;
		len=0;
		unsigned temp=0,w=1;
		for(int i=slen-1;i>=f;i--){
			temp+=(s[i]^48)*w;
			w=(w<<1)+(w<<3);
			if(w==BASE||i==f){
				num[++len]=(int)temp;
				temp=0;
				w=1;
			}
		}
		if(temp||len==0)
			num[++len]=temp;
	}
	bool operator<(const bigint &a)const{
		if(num[0]&&!a.num[0])
			return 1;
		if(!num[0]&&a.num[0])
			return 0;
		if(num[0]){
			if(len!=a.len)
				return len>a.len;
			for(int i=len;i;i--)
				if(num[i]!=a.num[i])
					return num[i]>a.num[i];
		}
		else{
			if(len!=a.len)
				return len<a.len;
			for(int i=len;i;i--)
				if(num[i]!=a.num[i])
					return num[i]<a.num[i];
		}
		return 0;
	}
	bigint operator+(const bigint &a)const{
		bigint res;
		if(len==1&&num[1]==0){
			res=a;
			return res;
		}
		if(a.len==1&&a.num[1]==0){
			res=*this;
			return res;
		}
		if(num[0]==a.num[0]){
			res.num[0]=num[0];
			unsigned len_sum=1;
			while(len_sum<len+a.len)
				len_sum<<=1;
			comp *fa=new comp[len_sum]();
			comp *fb=new comp[len_sum]();
			for(unsigned i=0;i<len;i++)
				fa[i]={(double)num[i+1],0};
			for(unsigned i=0;i<a.len;i++)
				fb[i]={(double)a.num[i+1],0};
			FFT(fa,len_sum,1);
			FFT(fb,len_sum,1);
			for(unsigned i=0;i<len_sum;i++)
				fa[i]=fa[i]+fb[i];
			FFT(fa,len_sum,-1);
			res.len=Max(len,a.len);
			ll temp=0;
			for(unsigned i=0;i<res.len;i++){
				ll val=(ll)round(fa[i].real)+temp;
				res.num[i+1]=(int)(val%BASE);
				temp=val/BASE;
			}
			if(temp)
				res.num[++res.len]=temp;
			while(res.len>1&&res.num[res.len]==0)
				res.len--;
			delete[] fa;
			delete[] fb;
		}
		else{
			if(abs_greater_equal(a)){
				res.num[0]=num[0];
				unsigned len_sum=1;
				while(len_sum<len+a.len)
					len_sum<<=1;
				comp *fa=new comp[len_sum]();
				comp *fb=new comp[len_sum]();
				for(unsigned i=0;i<len;i++)
					fa[i]={(double)num[i+1],0};
				for(unsigned i=0;i<a.len;i++)
					fb[i]={(double)a.num[i+1],0};
				FFT(fa,len_sum,1);
				FFT(fb,len_sum,1);
				for(unsigned i=0;i<len_sum;i++)
					fa[i]=fa[i]-fb[i];
				FFT(fa,len_sum,-1);
				res.len=Max(len,a.len);
				ll temp=0;
				for(unsigned i=0;i<res.len;i++){
					ll val=(ll)round(fa[i].real)+temp;
					if(val<0){
						val+=BASE;
						temp=-1;
					}
					else
						temp=0;//借位
					res.num[i+1]=(int)(val%BASE);
				}
				if(temp)
					res.num[++res.len]=temp;
				while(res.len>1&&res.num[res.len]==0)
					res.len--;
				delete[] fa;
				delete[] fb;
			}
			else{
				res.num[0]=a.num[0];
				unsigned len_sum=1;
				while(len_sum<len+a.len)
					len_sum<<=1;
				comp *fa=new comp[len_sum]();
				comp *fb=new comp[len_sum]();
				for(unsigned i=0;i<len;i++)
					fa[i]={(double)num[i+1],0};
				for(unsigned i=0;i<a.len;i++)
					fb[i]={(double)a.num[i+1],0};
				FFT(fa,len_sum,1);
				FFT(fb,len_sum,1);
				for(unsigned i=0;i<len_sum;i++)
					fa[i]=fb[i]-fa[i];
				FFT(fa,len_sum,-1);
				res.len=Max(len,a.len);
				ll temp=0;
				for(unsigned i=0;i<res.len;i++){
					ll val=(ll)round(fa[i].real)+temp;
					if(val<0){
						val+=BASE;
						temp=-1;
					}
					else
						temp=0;
					res.num[i+1]=(int)(val%BASE);
				}
				if(temp)
					res.num[++res.len]=temp;
				while(res.len>1&&res.num[res.len]==0)
					res.len--;
				delete[] fa;
				delete[] fb;
			}
			if(res.len==1&&res.num[1]==0)
				res.num[0]=0;
		}
		return res;
	}
	bigint operator*(const bigint &a)const{
		bigint res;
		if((len==1&&num[1]==0)||(a.len==1&&a.num[1]==0))
			return res;
		res.num[0]=num[0]^a.num[0];
		unsigned len_sum=1;
		while(len_sum<len+a.len)
			len_sum<<=1;
		comp *fa=new comp[len_sum]();
		comp *fb=new comp[len_sum]();
		for(unsigned i=0;i<len;i++)
			fa[i]={(double)num[i+1],0};
		for(unsigned i=0;i<a.len;i++)
			fb[i]={(double)a.num[i+1],0};
		FFT(fa,len_sum,1);
		FFT(fb,len_sum,1);
		for(unsigned i=0;i<len_sum;i++)
			fa[i]=fa[i]*fb[i];
		FFT(fa,len_sum,-1);
		res.len=len+a.len;
		ll temp=0;
		for(unsigned i=0;i<res.len;i++){
			ll val=(ll)(fa[i].real+0.5)+temp;
			res.num[i+1]=(int)(val%BASE);
			temp=val/BASE;
		}
		if(temp)
			res.num[++res.len]=temp;
		while(res.len>1&&res.num[res.len]==0)
			res.len--;
		delete[] fa;
		delete[] fb;
		return res;
	}
	void read(){
		init();
		std::string s;
		char ch=getchar();
		while(ch<'0'||ch>'9'){
			if(ch=='-')
				s.push_back('-');
			ch=getchar();
		}
		while(ch>='0'&&ch<='9'){
			s.push_back(ch);
			ch=getchar();
		}
		get_num(s);
	}
	void print(){
		if(num[0])
			putchar('-');
		bool leading_zero=1;
		for(int i=len;i;i--){
			if(leading_zero)
				printf("%d",num[i]);
			else
				printf("%02d",num[i]);
			leading_zero=0;
		}
		putchar('\n');
		return;
	}
};
//********程序主体
const int N=1<<10,M=100;
int n,m;
bigint<114514> a,b,c;
int main(){
	a.read();
	b.read();
	c=a+b;
	c.print();
	return 0;
}
```
### 写在结尾：
我们成功把 $O(1)$ 的朴素算法优化到了 $O(n)$，接着进一步将 $O(n)$ 的高精度算法优化到了 FFT 的 $O(n \log n)$，这体现了我们对 OI 知识的灵活迁移运用。希望大家能（~~可千万别~~）将这种思想运用到学习生活中。

---

## 作者：xxr___ (赞：37)

怎么不写矩阵乘法？

首先我们需要知道矩阵乘法，两个矩阵 $A$ 和 $B$ 相乘的结果是 $C$。

我们设 $A_{i,j}$ 表示 $A$ 矩阵的第 $i$ 行第 $j$ 个元素，$B_{i,j}$ 表示 $B$ 矩阵的第 $i$ 行第 $j$ 个元素，那么有公式 $C_{i,j}=\sum_k A_{i,k} \times B_{k,j}$。

好的，相信聪明的你已经学会了矩阵乘法，再来看看这个题，我们可以令 $A$ 矩阵是 $\begin{bmatrix} 1 & 1
\end{bmatrix}$ 令 $B$ 矩阵是 $\begin{bmatrix} a \\ b\end{bmatrix}$ 那么 $A\times B$ 的结果就是 $\begin{bmatrix} a + b & 0\\
0 & 0\end{bmatrix}$ 了。

代码：
```cpp
#include<iostream>

struct Matrix{
	int g[2][2];
	Matrix (){
		for(int i = 0;i < 2; ++ i){
			for(int j = 0;j < 2; ++ j){
				g[i][j] = 0;
			}
		}
	}
};
inline Matrix operator * (const Matrix & x,const Matrix & y){
	Matrix z;
	for(int i = 0;i < 2; ++ i){
		for(int j = 0;j < 2; ++ j){
			for(int k = 0;k < 2; ++ k){
				z.g[i][j] += x.g[i][k] * y.g[k][j];
			}
		}
	}
	return z;
}
int main(){
	Matrix A,B;
	int a,b;
	std::cin >> a >> b;
	A.g[0][0] = 1;
	A.g[0][1] = 1;
	B.g[0][0] = a;
	B.g[1][0] = b;
	A = A * B;
	std::cout << A.g[0][0];
	return 0;
}
```

---

## 作者：Little_Cart (赞：35)

你好啊，欢迎进入编程的世界！接下来你要迎接的挑战是：进入编程世界的关键一招，$a+b$ 问题！

如果你通过了这个问题，那么你就彻底打开了通往新世界的大门！那让我们开始吧！

### C++

我想了一下，传统的 $a+b$ 还是太吃操作了，我们有没有什么更有趣的算法来解决呢，有的兄弟有的，我这边推荐二分，二分是一个很有用的算法，在红题到黑题你都能看到他的身影！

我们假设 $mid$ 为我们当前二分的值，$l,r$ 为我们目前已经锁定的左右边界。

每次二分开始的时候，我们将 $mid$ 设为 $l,r$ 的平均值，也就是 $\frac{l+r}{2}$，在本题因为没有小数，所以我们可以向下取整。

如果 $a+b<mid$，那么说明 $mid$ 大了，这个时候我们把右边界 $r$ 设为 $mid-1$ 就好了。

如果 $a+b>mid$，那么说明 $mid$ 小了，这个时候我们把左边界 $l$ 设为 $mid+1$ 就好了。

如果 $a+b=mid$，那么恭喜你，你找到了答案！这个时候我们输出这个 $mid$ 就可以了！

我们可以使用 `while` 循环来重复这个过程，直到我们找到答案。

由于过程中可能会爆 `int`，所以我们需要可以储存更大整数变量的类型：`long long`！

附上一份代码，如果想要真正踏入编程的世界，那么是不可以复制别人的代码提交的，需要你亲手打出来，体验编程之美！

```cpp
#include<iostream>
using namespace std;
long long a,b;
int main(){
	long long l=-2e9,r=2e9,mid;
	cin>>a>>b;
	while(l<=r){
		mid=(l+r)>>1;
		if(a+b==mid){
			cout<<mid;
			break;
		}
		else if(a+b<mid){
			r=mid-1;
		}
		else if(a+b>mid){
			l=mid+1;
		}
	}
	return 0;
}
```


如果你通过了这道题，那么恭喜你，你现在可以挑战所有带有二分标签的题目了，让我们继续加油吧！

### python

同时附上一篇 python 题解。

由于 python 中的 `input` 会读入一行的字符串，所以这里我们使用 `split` 来将这个字符串分割成两个正整数。

`split` 可以将一个字符串函数默认按照空格将字符串分割并返回一个列表。

在 `split` 结束之后，$s$ 列表中存储的是两个字符串，但是我们需要两个整型变量进行加减，所以需要使用 `int(s[0])`。

```python
s=input().split()
print(int(s[0])+int(s[1]))
```

---

## 作者：jijidawang (赞：35)

题目让我们求两个数的和，恰好 `add` 指令可以用来求两个数的和
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b;
	cin >> a >> b;
	__asm__ volatile
	(
		"mov %1, %%rax\n"
		"mov %2, %%rbx\n"
		"add %%rax, %%rbx\n"
		"mov %%rbx, %0\n"
		:"=r"(a) :"r"(a), "r"(b) :"%rax", "%rbx"
	);
	cout << a << endl;
	return 0;
}
```

---

## 作者：K8He (赞：35)

如果是 A*B Problem，我们可以轻松将其转化成多项式乘法问题。

此题容易注意到使用经典结论，先使用多项式 exp 一步将加法转换成乘法再使用多项式 ln 得到答案。

有一点细节 WA 了几发：

- 多项式 ln 会忽略常数项，所以应当先对 $a, b$ 乘 $10$。
- 乘 $10$ 以后是 $11$ 位数不是 $10$ 位数。
- 负数的情况可以先全都加上 $10^9$，最后对答案减去 $2\times 10^9$。

然后就可以愉快的通过了！

代码（可能有人问 `namespace POLY` 是什么吧，是史哦！）：

```cpp
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = a; i <= b; ++i)
#define for_(i, a, b) for (int i = a; i >= b; --i)
#define far(i, vec) for (auto i : vec)
#define bdmd int mid = (l + r) >> 1
typedef long double ldb;
typedef long long ll;
typedef double db;
typedef std::pair <int, int> pii;
typedef std::pair <ll, ll> pll;
const int N = 1e5 + 10, P = 998244353;
namespace IO {
	int rnt () {
		int x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
}
namespace POLY {
	const int N=3e5+10,P=998244353,g=3,invg=332748118;int rev[N],omega[2][N];
	std::mt19937 rnd (std::chrono::system_clock::now ().time_since_epoch ().count ());
	template<typename T1,typename T2>inline T1 add(T1 a,T2 b){return(a+=b)>=POLY::P?a-POLY::P:a;}template<typename T1,typename T2>inline void addi(T1&a,T2 b){(a+=b)>=POLY::P?a-=POLY::P:a;return;}template<typename T1,typename...Args>inline T1 add(T1 a,Args...b){return add(a,add(b...));}template<typename T1,typename...Args>inline void addi(T1&a,Args...b){addi(a,add(b...));return;}
	template<typename T1,typename T2>inline T1 sub(T1 a,T2 b){return(a-=b)<0?a+POLY::P:a;}template<typename T1,typename T2>inline void subi(T1&a,T2 b){(a-=b)<0?a+=POLY::P:a;return;}template<typename T1,typename...Args>inline T1 sub(T1 a,Args...b){return sub(a,add(b...));}template<typename T1,typename...Args>inline void subi(T1&a,Args...b){subi(a,add(b...));return;}
	template<typename T1,typename T2>inline T1 mul(T1 a,T2 b){return(1ll*a*b)%POLY::P;}template<typename T1,typename T2>inline void muli(T1&a,T2 b){a=mul(a,b);return;}template<typename T1,typename...Args>T1 inline mul(T1 a,Args...b){return mul(a,mul(b...));}template<typename T1,typename...Args>inline void muli(T1&a,Args...b){muli(a,mul(b...));return;}
	template<typename T1,typename T2>inline T1 FastPow(T1 a,T2 b){T1 ans=1;while(b){if(b&1)muli(ans,a);muli(a,a),b>>=1;}return ans;}template<typename T>inline T Inv(T a){return FastPow(a,POLY::P-2);}
	inline int PreWork(const int &n){int lim=1,l=0;while(lim<=n)lim<<=1,++l;_for(i,0,lim)rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));omega[0][0]=omega[1][0]=1;omega[0][1]=FastPow(g,(POLY::P-1)/lim);omega[1][1]=FastPow(invg,(POLY::P-1)/lim);_for(i,2,lim)omega[0][i]=mul(omega[0][i-1],omega[0][1]),omega[1][i]=mul(omega[1][i-1],omega[1][1]);return lim;}
	namespace Cipolla{int _i_;class Complex{public:int real,imag;Complex()=default;Complex(int _real,int _imag):real(_real),imag(_imag){}inline void operator*=(Complex b){int tmp1=add(mul(real,b.real),mul(imag,b.imag,_i_));int tmp2=add(mul(real,b.imag),mul(imag,b.real));real=tmp1,imag=tmp2;return;}};inline int FastPow(Complex a,int b){Complex ans(1,0);while(b){if(b&1)ans*=a;a*=a,b>>=1;}return ans.real;}inline int Cipolla(int n){if (!n)return 0;if (POLY::FastPow(n,(POLY::P-1)>>1)==POLY::P-1)return -1;int a;while(a){a=rnd()%POLY::P,_i_=sub(mul(a,a),n);if(POLY::FastPow(_i_,(POLY::P-1)>>1)==POLY::P-1)break;}return FastPow(Complex(a,1),(POLY::P+1)>>1);}};
	template<typename T = int> class Poly {
	private:std::vector<T>A;
	public:
		Poly()=default;Poly(int len){A.resize(len);return;}Poly(std::vector<T> _A):A(_A){}Poly(typename std::vector<T>::iterator bg,typename std::vector<T>::iterator ed){A.assign(bg,ed);return;}Poly(typename std::vector<T>::iterator bg,int len){A.assign(bg,bg+len);return;}
		inline T& operator[](const int& x){return A[x];}inline T operator[](const int& x)const{return A[x];}
		inline int deg()const{return A.size()-1;}inline int len()const{return A.size();}inline Poly Resize(int len){A.resize(len);return(*this);}
		inline typename std::vector<T>::iterator begin(){return A.begin();}inline typename std::vector<T>::iterator end(){return A.end();}inline T* data(){return A.data();}
		inline void Cover(typename std::vector<T>::iterator bg,typename std::vector<T>::iterator ed){A.assign(bg,ed);return;}inline void Cover(typename std::vector<T>::iterator bg,int len){A.assign(bg,bg+len);return;}
		inline Poly Slice(int n){return n<=0?Poly(0):(n<len()?Poly(begin(),begin()+n+1):Poly(*this).Resize(n+1));}inline void Clear(){std::vector<T>().swap(A);return;}
		inline void NTT(int lim,bool type){Resize(lim);_for(i,0,lim-1)if(i<rev[i])std::swap(A[i],A[rev[i]]);for(int mid=1,t=lim>>1;mid<lim;mid<<=1,t>>=1){for(int R=mid<<1,j=0;j<lim;j+=R){_for(k,0,mid-1){T x=A[j+k],y=mul(omega[type][t*k],A[j+mid+k]);A[j+k]=add(x,y),A[j+mid+k]=sub(x,y);}}}if(type==1){T inv_lim=FastPow(lim,POLY::P-2);_for(i,0,lim-1)A[i]=mul(A[i],inv_lim);}return;}
		friend inline Poly operator+(Poly F,Poly G){F.Resize(std::max(F.len(),G.len()));_for(i,0,G.deg())addi(F[i],G[i]);return F;}inline Poly&operator+=(Poly G){Resize(std::max(len(),G.len()));_for(i,0,G.deg())addi(A[i],G[i]);return(*this);}
		friend inline Poly operator+(Poly F,T x){addi(F[0],x);return F;}friend inline Poly operator+(T x,Poly F){addi(F[0],x);return F;}inline Poly&operator+=(T x){addi(A[0],x);return(*this);}
		friend inline Poly operator-(Poly F,Poly G){F.Resize(std::max(F.len(),G.len()));_for(i,0,G.deg())subi(F[i],G[i]);return F;}inline Poly&operator-=(Poly G){Resize(std::max(len(),G.len()));_for(i,0,G.deg())subi(A[i],G[i]);return(*this);}
		friend inline Poly operator-(Poly F,T x){subi(F[0],x);return F;}friend inline Poly operator-(T x,Poly F){subi(F[0],x);return F;}inline Poly&operator-=(T x){subi(A[0],x);return(*this);}
		friend inline Poly operator*(Poly F,Poly G){int lim=PreWork(F.deg()+G.deg());F.NTT(lim,0),G.NTT(lim,0);_for(i,0,lim-1)muli(F[i],G[i]);F.NTT(lim,1);return F;}inline Poly&operator*=(Poly G){int lim=PreWork(deg()+G.deg());NTT(lim,0),G.NTT(lim,0);_for(i,0,lim-1)muli(A[i],G[i]);NTT(lim,1);return(*this);}
		friend inline Poly operator*(Poly F,T x){_for(i,0,F.deg())muli(F[i],x);return F;}friend inline Poly operator*(T x,Poly F){_for(i,0,F.deg())muli(F[i],x);return F;}inline Poly&operator*=(T x){_for(i,0,deg())muli(A[i],x);return(*this);}
		friend inline Poly operator/(Poly F,T x){x=POLY::Inv(x);return F*x;}friend inline Poly operator/(T x,Poly F){x=POLY::Inv(x);return F*x;}inline Poly&operator/=(T x){x=POLY::Inv(x);(*this)*=x;return(*this);}
		friend inline Poly operator<<(Poly F,int x){F.Resize(F.len()+x),memmove(F.data()+x,F.data(),4*(F.len()-x)),memset(F.data(),0,4*x);return F;}inline Poly&operator<<=(int x){Resize(len()+x),memmove(data()+x,data(),4*(len()-x)),memset(data(),0,4*x);return(*this);}
		friend inline Poly operator>>(Poly F,int x){if(x>=F.len())F.Clear();else memmove(F.data(),F.data()+x,4*(F.len()-x)),F.Resize(F.len()-x);return F;}inline Poly& operator>>=(int x){return x>=len()?(Clear(),*this):(memmove(data(),data()+x,4*(len()-x)),Resize(len()-x),*this);}
		inline Poly Inv(){Poly G(1);if(A.empty())return G;G[0]=POLY::Inv(A[0]);Poly t[2];for(int l=2;l<(len()<<1);l<<=1){t[0].Cover(A.begin(),std::min(l,len()));t[1]=G,t[1].Resize(std::min(l,len()));int lim=PreWork(t[0].deg()+t[1].deg()+1);t[0].NTT(lim,0),t[1].NTT(lim,0),G.Resize(lim);_for(i,0,lim-1)G[i]=mul(sub(2,mul(t[0][i],t[1][i])),t[1][i]);G.NTT(lim,1),G.Resize(l);}G.Resize(len());return G;}
		inline Poly Sqrt(){Poly G(1);G[0]=Cipolla::Cipolla(A[0]),G[0]=std::min(G[0],POLY::P-G[0]);T inv2=POLY::Inv(2);Poly t[2];for(int l=2;l<(len()<<1);l<<=1){t[1].Cover(A.begin(),std::min(l,len()));G.Resize(l),t[0]=G.Inv()*t[1];_for(i,0,l-1)G[i]=mul(t[0][i]+G[i],inv2);}G.Resize(len());return G;}
		inline Poly Differential(){Poly G(len()-1);_for(i,0,deg()-1)G[i]=mul(A[i+1],i+1);return G;}inline void iDifferential(){_for(i,0,deg()-1)A[i]=mul(A[i+1],i+1);A.resize(len()-1);return;}
		inline Poly Integral(){Poly G(len());for_(i,deg(),1)G[i]=mul(A[i-1],POLY::Inv(i));return G;}inline void iIntegral(){A.resize(len());for_(i,deg(),1)A[i]=mul(A[i-1],POLY::Inv(i));A[0]=0;return;}
		inline Poly Ln(){Poly G=(Differential()*Inv()).Integral();G.Resize(len());return G;}
		inline Poly Exp(){Poly G(1),H;G[0]=1;T inv2=POLY::Inv(2);for(int l=2;l<(len()<<1);l<<=1)G.Resize(l),H.Cover(A.begin(),std::min(l,len())),H-=G.Ln(),++H[0],G*=H;G.Resize(len());return G;}
		inline Poly Power(int k){if(A[0]!=0)return((((*this)*FastPow(A[0],P-2)).Ln())*k).Exp()*FastPow(A[0],k);else _for(i,0,deg())if(A[i]!=0)return((*this)>>i).Power(k)<<(i*k);return Poly(len());}
		inline Poly Power(pii k){if(A[0]!=0)return((((*this)*FastPow(A[0],P-2)).Ln())*k.second).Exp()*FastPow(A[0],k.first);else _for(i,0,deg())if(A[i]!=0)return(1ll*i*k.first)>len()?Poly(len()):((*this)>>i).Power(k)<<(i*k.first);return Poly(len());};
	};
} using poly = POLY::Poly<int>;
namespace SOLVE {
	using namespace IO;
	ll a, b, ans;
	poly A, B, C;
	void In () {
		a = rnt (), b = rnt ();
		return;
	}
	void Solve () {
		a += 1000'000'000ll;
		b += 1000'000'000ll;
		a *= 10, b *= 10;
		A.Resize (11), B.Resize (11);
		_for (i, 0, 10) {
			A[i] = a % 10, a /= 10;
			B[i] = b % 10, b /= 10;
		}
		A = A.Exp (), B = B.Exp ();
		C = A * B;
		C = C.Ln ();
		ll t = 1;
		_for (i, 0, std::min (10, C.deg ()))
			ans = ans + t * C[i], t *= 10;
		ans /= 10;
		ans -= 2000'000'000ll;
		return;
	}
	void Out () {
		printf ("%lld\n", ans);
		return;
	}
}
int main () {
	SOLVE::In ();
	SOLVE::Solve ();
	SOLVE::Out ();
	return 0;
} /*

*/
```

---

## 作者：NOI_Winner (赞：32)

先上代码再解释：
```cpp
#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
```

我们逐行解释：
```cpp
#include <iostream>
```
这一行是预处理指令，用于包含头文件 `iostream`，后面的 `cin` 和 `cout` 都在该头文件中被定义。也就是说，要使用 `cin` 和 `cout` 必须加上这一行。
```cpp
using namespace std;
```
C++ 标准头文件的的所有定义都被包含在名称空间 `std` 中，本行用于导入名称空间中的所有内容。初学者不需要理解其具体含义，只需记住在每一个程序中都加上这一行就行了。
```cpp
int main()
```
这一行用于定义主函数 `main`，每一个程序都必须包含它，程序将从这里开始执行，它的内容需使用大括号包含。
```cpp
int a, b;
```
这一行定义两个 `int` 类型变量 `a` 和 `b`，`int` 是最常用的整数类型，通常占用四个字节大小，存储的数据范围为 $-2147483648$ 至 $2147483647$。`a` 与 `b` 就是 `int` 类型的两个变量。
```cpp
cin >> a >> b;
```
`cin` 语句用于输入，这里可以输入两个数并存入 `a` 和 `b`。还可以在后面继续拼接输入更多的数字，如 `cin >> a >> b >> c;`。
```cpp
cout << a + b << endl;
```
这一行用于输出答案。`a + b` 是一个表达式，使用 `cout` 可将它输出，输出 `endl` 可用于换行。同样 `cout` 也可以在后面拼接。
```cpp
return 0;
```
这一句用于结束程序并返回 $0$。初学者现在不必了解它具体作用，实际上这一句是可选的。

祝大家在日后的学习中步步高升，勇攀 OI 之巅峰！！！

---

## 作者：cyc001 (赞：31)

### Solution

设这两个数为 $x$ 和 $y$。

如果 $x$ 和 $y$ 都是正数就可以这么做。

我们先把原数转成二进制形式，每一位分别是 $a_1 \dots a_n$ 和 $b_1 \dots b_n$。

写出 $a$ 和 $b$ 的 OGF $A(x)$ 和 $B(x)$。

随便带 $n$ 个 $x$，多点求值把 $A$ 和 $B$ 转成点值，把点值加起来，再插值插回去就得到了 $A(x)+B(x)$，处理二进制下进位的问题，最后转回十进制就可以了，但是其实可以直接计算 $\sum\limits_{i=0}^{+\infty} [x^n](A(x)+B(x))2^n$ 也可以。

另外由于插值和多点求值中涉及到的数不大，我们可以直接写模 $998244353$ 的 ntt 完全可以过。

复杂度 $O(\log V\log^2\log V)$。

涉及到负数类似地处理一下，比如说我们不一定转成严格的二进制，只要 $\sum a_i 2^i=x$ 就可以了，这样位权可以为负，负数的问题就解决啦 QwQ。

### Code

```cpp
#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
    unordered_map<lint,vector<lint>> uwn;
    unordered_map<lint,vector<int>> urev;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto wn(const auto h){
        if(uwn.contains(h)) return&uwn[h];
        const auto wx=qpow(omega,(MOD-1)/h);
        vector<lint> xwn(h);
        auto u=1ll;
        for(auto&x:xwn) x=u,(u*=wx)%=MOD;
        uwn[h]=xwn;
        return&uwn[h];
    }
    auto rev(const auto h){
        if(urev.contains(h)) return&urev[h];
        vector<int> xrev(h);
        cir(i,0,h) xrev[i]=(xrev[i>>1]>>1)|((h>>1)*(i&1));
        urev[h]=xrev;
        return&urev[h];
    }
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct.resize(n);
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    constexpr auto fact(const auto x) const{return fct[x];}
    constexpr auto ifact(const auto x) const{return ifct[x];}
} math;
class poly:public vector<lint>{
public:
    using vector<lint>::vector;
    auto change(poly&a,const auto n){
        auto rev=math.rev(n);
        cir(i,0,n) if(i<(*rev)[i]) std::swap(a[i],a[(*rev)[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const auto n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            auto wn=math.wn(h);
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*(*wn)[k-i]%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=a[k+midh]>MOD-1?MOD:0;
                    a[k]+=wk;
                    a[k]-=a[k]>MOD-1?MOD:0;
                }
            }
        }
        if(type==-1){
            const auto ivn=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=ivn)%=MOD;
        }
    }
public:
    auto sized(const auto n){
        auto res=*this;
        res.resize(n);
        return res;
    }
    auto shrink(){
        auto a=*this;
        while(a.size()>1&&(!a.back())) a.pop_back();
        return a;
    }
    auto transform(const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        resize(nlen);
        ntt<1>(*this,nlen);
    }
    auto shift(){
        auto a=*this;
        a.emplace(a.begin(),0);
        return a;
    }
    auto itransform(const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        resize(nlen);
        ntt<-1>(*this,nlen);
    }
    auto transform(){transform(size());}
    auto itransform(){itransform(size());}
    friend auto operator+(poly a,poly b){
        a.resize(max(a.size(),b.size()));
        cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
        return a;
    }
    friend auto operator-(poly a){
        for(auto&i:a) (i=MOD-i)%=MOD;
        return a;
    }
    friend auto operator-(poly a,poly b){
        return a+(-b);
    }
    friend auto operator*(poly a,auto b) requires is_integral_v<decltype(b)>{
        for(auto&i:a) (i*=b)%=MOD;
        return a;
    }
    friend auto operator*(poly a,poly b){
        const auto nlen=1<<(int)(ceil(log2(a.size()+b.size())));
        a.transform(nlen);b.transform(nlen);
        cir(i,0,nlen) (a[i]*=b[i])%=MOD;
        a.itransform();
        return a;
    }
    friend auto inv(poly a,const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        a.resize(nlen);
        auto f=poly{math.inv(a[0])};
        for(auto i=1;i<nlen;i<<=1){
            f=(f*2-(f*f).sized(i<<1)*(a.sized(i<<1))).sized(i<<1);
        }
        return f;
    }
    friend auto operator~(poly a){
        return inv(a,a.size());
    }
    friend auto int_dx(poly a){
        a.emplace(a.begin(),0);
        cir(i,0,(int)(a.size())) (a[i]*=math.inv(i))%=MOD;
        return a;
    }
    friend auto d_dx(poly a){
        cir(i,0,(int)(a.size())) (a[i]*=i)%=MOD;
        a.erase(a.begin());
        return a;
    }
    friend auto ln(poly a,auto req_len){
        return int_dx(d_dx(a)*inv(a,req_len));
    }
    friend auto ln(poly a){
        return ln(a,a.size());
    }
    friend auto exp(poly a,auto req_len){
        auto res=poly{1};
        a.resize(req_len);
        a.resize(1<<(int)(ceil(log2(a.size()))));
        const auto n=(int)(a.size());
        for(auto i=1;i<n;i<<=1){
            res=(res*(poly{1}-ln(res.sized(i<<1))+a).sized(i<<1)).sized(i<<1);
        }
        return res;
    }
    friend auto exp(poly a){
        return exp(a,a.size());
    }
    friend auto x_exp(const auto k,auto req_len){
        auto res=poly(req_len);
        res.resize(1<<(int)(ceil(log2(res.size()))));
        auto pwk=1ull;
        cir(i,0,(int)(res.size())){
            res[i]=pwk*math.ifact(i)%MOD;
            (pwk*=k)%=MOD;
        }
        return res;
    }
    friend auto pow(poly a,const auto x){
        return exp(ln(a)*x);
    }
    friend auto operator/(poly a,poly b){
        const auto n=(int)(a.size()),m=(int)(b.size());
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
        a.resize(max(n-m+1,1));
        b.resize(max(n-m+1,1));
        auto q=a*(~b);
        q.resize(max(n-m+1,1));
        reverse(q.begin(),q.end());
        return q;
    }
    friend auto operator%(poly a,poly b){
        return a-b*(a/b);
    }
    friend auto sqrt(poly a){
        return exp(ln(a)*math.inv(2));
    }
};
auto getvalues(poly a,const vector<lint> p){
    map<pair<int,int>,poly> cur;
    auto init=[&](auto __self,int l,int r){
        if(l==r) return cur[{l,r}]=poly{(MOD-p[l])%MOD,1};
        const auto mid=midpoint(l,r);
        return cur[{l,r}]=(__self(__self,l,mid)*__self(__self,mid+1,r)).shrink();
    };
    init(init,0,(int)(p.size())-1);
    vector<lint> res(p.size());
    auto divide=[&](auto __self,int l,int r,poly f){
        if(l==r) return res[l]=f[0],void();
        const auto mid=midpoint(l,r);
        __self(__self,l,mid,(f%cur[{l,mid}]).shrink());
        __self(__self,mid+1,r,(f%cur[{mid+1,r}]).shrink());
    };
    divide(divide,0,(int)(p.size())-1,a);
    return res;
}
auto lagrange(const vector<lint> x,const vector<lint> y){
    const auto n=(int)(x.size());
    auto init=[&](auto __self,int l,int r){
        if(l==r) return poly{(MOD-x[l])%MOD,1};
        const auto mid=midpoint(l,r);
        return (__self(__self,l,mid)*__self(__self,mid+1,r)).shrink();
    };
    const auto m=init(init,0,n-1);
    auto val=getvalues(d_dx(m),x);
    auto divide=[&](auto __self,int l,int r){
        if(l==r) return pair(poly{y[l]*math.inv(val[l])%MOD},poly{(MOD-x[l])%MOD,1});
        const auto mid=midpoint(l,r);
        const auto[lf,lw]=__self(__self,l,mid);
        const auto[rf,rw]=__self(__self,mid+1,r);
        return pair((lf*rw+rf*lw).shrink(),(lw*rw).shrink());
    };
    return divide(divide,0,n-1).first;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int a,b;cin>>a>>b;
    const auto sgna=(a<0?MOD-1:1);
    const auto sgnb=(b<0?MOD-1:1);
    a=abs(a);b=abs(b);
    poly A(32),B(32);
    cir(i,0,32) A[i]=(a&1),a>>=1;
    cir(i,0,32) B[i]=(b&1),b>>=1;
    A=A*sgna;
    B=B*sgnb;
    ranlux48 eng(random_device().operator()());
    set<lint> x;
    while(x.size()<32) x.emplace(uniform_int_distribution<lint>(0,MOD-1)(eng));
    const auto px=vector(x.begin(),x.end());
    auto va=getvalues(A,px);
    auto vb=getvalues(B,px);
    cir(i,0,(int)(va.size())) (va[i]+=vb[i])%=MOD;
    const auto c=lagrange(px,vector(va.begin(),va.end()));
    auto ans=0ll;
    cir(i,0,32){
        if(c[i]>MOD/2){
            ans+=(c[i]-MOD)*(1ll<<i);
        }else{
            ans+=c[i]*(1ll<<i);
        }
    }
    cout<<ans<<'\n';
    return 0;
}

```

---

## 作者：yr409892525 (赞：23)

## 题解：P1001 A+B Problem
首先我们需要知道三个性质。                 
1. $a+b=a\operatorname{xor} b+2\times (a\operatorname{and} b)$。
2. $a+0=a$。
3. $0+a=a$。

性质 $1$ 的证明：                       
对于 $a,b$ 在二进制下的每一位都有四种情况。
1. $a$ 在二进制下的第 $i$ 位为 $1$ 且 $b$ 在二进制下的第 $i$ 位为 $1$，则 $1\operatorname{xor} 1+2\times (1\operatorname{and} 1)=2$。
2. $a$ 在二进制下的第 $i$ 位为 $1$ 且 $b$ 在二进制下的第 $i$ 位为 $0$，则 $1\operatorname{xor} 0+2\times (1\operatorname{and} 0)=1$。
3. $a$ 在二进制下的第 $i$ 位为 $0$ 且 $b$ 在二进制下的第 $i$ 位为 $1$，则 $0\operatorname{xor} 1+2\times (0\operatorname{and} 1)=1$。
4. $a$ 在二进制下的第 $i$ 位为 $0$ 且 $b$ 在二进制下的第 $i$ 位为 $0$，则 $0\operatorname{xor} 0+2\times (0\operatorname{and} 0)=0$。

发现以上四种情况都成立。

很显然，性质 $2,3$ 成立。                             
有了这三条性质，我们就可以对 $a,b$ 一直进行变换，直到 $a=0$ 或 $b=0$ 为止。                                
代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int add(int a,int b){
	if(a==0) return b;
	if(b==0) return a;
	return add(a^b,2*(a&b));
}
int main(){
    int a,b;
	cin>>a>>b;
	cout<<add(a,b);
	return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：21)

闲着没事整篇题解。

先以正常的方法完成（即使用 `cin` 和 `cout` 和加法运算符）：


```cpp
#include <bits/stdc++.h>
#define int long long 

using namespace std;

int a,b;

signed main()
{
	cin>>a>>b;
	cout<<a+b<<endl;
    return 0;
}

```

顺便讲一下关于 `define` 的知识。说简介一点就是将 `define A B` 后代码中所有 `A` 都替换为 `B` 然后没了。例如 `#define int long long` 就是将代码中所有 `int` 换为 `long long` 类型，因为有时候数据较大会导致 `int` 存不下所以通常使用 `long long` 类型存储整数。注意打主函数是是 `int main()` 所以使用这句话时应将主函数改为 `signed main()` 就可以了。

然后注意 `return 0;` 是好习惯。


当然，为了使代码拥有更快的效率，我们可以格式化输入输出（也就是 `scanf` 和`printf` 实现）或是在原代码前面加上：


```cpp
ios_base::sync_with_stdio(0);
cin.tie(0);cout.tie(0);
```

补充：打回原因是**不够整活**，那我整点：

因为答案不超过 `int` 类型存储范围，来份二分枚举答案：


```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int a,b,ans;

bool check(int x)
{
	return x<(a+b);
}

signed main()
{
	cin>>a>>b;
	int l=INT_MIN,r=INT_MAX;
    while(l<r)
	{
		int mid=(l+r)>>1;
        if(mid==a+b)
        {
			ans=mid;
			break;
		}
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<ans<<endl;
    return 0;
}
```



为了尊重之前的整活题解，其实还有更多的方法，找到了一份文章：

[https://blog.csdn.net/2201_75605164/article/details/133951800](https://blog.csdn.net/2201_75605164/article/details/133951800)。

可以自行研究计算更加快速的方法。再见喵！

---

## 作者：niuzh (赞：20)

#### 前言

这不一眼树剖板子吗。

### 思路

显然，我们可以使用树链剖分，在一颗由两个点权分别为 $a$ 与 $b$ 的点构成的树上跑树剖。具体用线段树维护重链上点权的区间和，再用 lca 求两点唯一路径上点权之和。

### 代码

```cpp
/*
 * @FilePath: tmp.cpp
 * @Author: niu-zh
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
vector<int> tree[N];
int cnt,a[N];
struct node
{
	int tree[N<<2],lzy[N<<2];
	void pushup(int p)
	{
		tree[p]=tree[p<<1]+tree[p<<1|1];
	}
	void makelzy(int p,int l,int r,int x)
	{
		tree[p]+=(x*(r-l+1));
		lzy[p]+=x;
	}
	void pushdown(int p,int l,int r)
	{
		int mid=(l+r)>>1;
		makelzy(p<<1,l,mid,lzy[p]);
		makelzy(p<<1|1,mid+1,r,lzy[p]);
		lzy[p]=0;
	}
	void update(int p,int l,int r,int x,int y,int add)
	{
		if (x<=l&&r<=y)
		{
			makelzy(p,l,r,add);
			return;
		}
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if (mid>=x) update(p<<1,l,mid,x,y,add);
		if (mid<y) update(p<<1|1,mid+1,r,x,y,add);
		pushup(p);
	}
	int query(int p,int l,int r,int x,int y)
	{
		if (x<=l&&r<=y)
		{
			return tree[p];
		}
		pushdown(p,l,r);
		int mid=(l+r)>>1,ans=0;
		if (mid>=x) ans+=query(p<<1,l,mid,x,y);
		if (mid<y) ans+=query(p<<1|1,mid+1,r,x,y);
		return ans;
	}
} tr;
int fa[N],dep[N],sze[N],son[N],top[N],dfn[N],rnk[N];
void dfs1(int x)
{
	son[x]=-1;
	sze[x]=1;
	for (auto v:tree[x])
	{
		if (dep[v]) continue;
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v);
		sze[x]+=sze[v];
		if (son[x]==-1||sze[v]>sze[son[x]])
		{
			son[x]=v;
		}
	}
}
void dfs2(int x, int t)
{
	top[x]=t;
	cnt++;
	dfn[x]=cnt;
	if(a[x])
	{
		tr.update(1,1,2,dfn[x],dfn[x],a[x]);
	}
	rnk[cnt]=x;
	if (son[x]==-1)
	{
		return;
	}
	dfs2(son[x],t);
	for (auto v:tree[x])
	{
		if (v!=son[x]&&v!=fa[x])
		{
			dfs2(v,v);
		}
	}
}
int query(int u,int v)
{
	int ans=0;
	while (top[u]!=top[v])
	{
		if (dep[top[u]]<dep[top[v]])
		{
			swap(u,v);
		}
		ans+=tr.query(1,1,2,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if (dep[u]>dep[v])
	{
		swap(u,v);
	}
	ans+=tr.query(1,1,2,dfn[u],dfn[v]);
	return ans;
}
signed main()
{
	for (int i=1; i<=2; i++)
	{
		cin>>a[i];
	}
	tree[1].push_back(2);
	tree[2].push_back(1);
	dep[1]=1;
	dfs1(1);
	dfs2(1,1);
	cout<<query(1,2);
	return 0;
}
```

---

## 作者：langmouren (赞：19)

# A+B Problem

模拟退火练手题。

可以不断退火，使其接近 $a+b$，最后输出答案。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a,b,ans;
mt19937 Rand(time(0));
uniform_int_distribution<int>dist(-1e9,1e9);

void SA(int sum){
    double beginT=5000,endT=1e-6,k=0.9997;
    
    for(double T=beginT;T>endT;T*=k){
        int A=ans+dist(Rand)%2001-1000;
        A=max(-1000000000,min(1000000000,A));
        int B=sum-A,cur=A+B;
        
        if(abs(cur-sum)<abs(ans-sum)) ans=cur;
        else if(exp((abs(ans-sum)-abs(cur-sum))/T)>(double)Rand()/INT_MAX) ans=cur;
    }
}

int main(){
    cin>>a>>b;
    int sum=a+b;
    ans=dist(Rand);
    int cnt=10;
    while(cnt--) SA(sum);
    cout<<ans;
    return 0;
}
```

---

## 作者：船酱魔王 (赞：19)

## 题意转化

居然是加法问题，太难啦。

第一个数加第二个数的问题似乎需要可持久化历史查询的数据结构，不可做，考虑转化为两个数的较大值加两个数的较小值，每次找到最大值和最小值，然后求和即可。

最小值查询可以转化为相反数的最大值查询，然后符号取反计入答案。

因此题意被转化为，区间最大值查询问题，要求询问复杂度 $ O(1) $ 单次，预处理线性，空间线性，查询区间可以认为是随机的。

## 分析

因为预处理和空间要求，你无法直接使用 ST 表。

考虑分块解决题目，将序列分为 $ S $ 个数一段，每次查询是 $ \max\{\max_{i=l}^{\lfloor \frac{l}{S}\rfloor\times S+S-1}a_i,\max_{i=\lfloor\frac{l}{S}\rfloor+1}^{\lfloor\frac{r}{S}\rfloor-1}blomax_i,\max_{i=\lfloor \frac{r}{S}\rfloor\times S}^r \} $，若 $ l,r $ 所属同一块，则暴力即可，这样的询问不会很多不影响时间复杂度。（这里分块方法为 $ i $ 属于块 $ \lfloor \frac{i}{S} \rfloor $）。

显然 $ \max $ 运算的第一项和第三项可以在分块后线性预处理，第二项可以转化为一个在 $ blomax $ 数组（长度为 $ \frac{n}{S} $ 量级）上的 RMQ 问题。

因此，对于绝大多数询问，单次查询复杂度为 $ O(1) $，预处理复杂度为 $ O(\frac{n}{S} \log \frac{n}{S}) $，空间复杂度与预处理复杂度相同，因此当 $ S $ 近似取 $ \log n $ 时，预处理复杂度为线性。

而将两个数的原数值和相反数放入序列，查询原始数区间最大值和相反数区间最大值再反转后者符号即可完成本题，时间复杂度是 $ O(n) $ 预处理 $ O(1) $ 查询的，$ n,q $ 在本题取 $ 2 $，在 1s 的严格时间限制下能过。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define ui unsigned int
using namespace std;
const int N = 2e7 + 5;
const int S = 35;
int n, m;
unsigned int s;
ui a[N];
ui b[N];
ui c[N];
ui blo[N / S + 5];
ui sm[N / S + 5][35];
int ql[N], qr[N];
ui rmq(int x, int y) {
    int k = log2(y - x + 1);
    return max(sm[x][k], sm[y - (1 << k) + 1][k]);
}
int main() {
    n = 2, m = 2;
    int x;
    scanf("%d", &x);
    a[1] = 1e9 + x, a[3] = 1e9 - x;
    scanf("%d", &x);
    a[2] = 1e9 + x, a[4] = 1e9 - x;
    for(int i = 5; i <= n; i++) a[i] = a[i - 4];
    for(int i = 1; i <= n; i++) blo[(i - 1) / S] = max(blo[(i - 1) / S], a[i - 1]), sm[(i - 1) / S][0] = blo[(i - 1) / S];
    for(int i = 0; i < n; i++) {
        if(i % S == 0) b[i] = a[i];
        else b[i] = max(b[i - 1], a[i]);
    }
    for(int i = n - 1; i >= 0; i--) {
        if(i == n - 1 || i % S == S - 1) c[i] = a[i];
        else c[i] = max(c[i + 1], a[i]);
    }
    for(int i = 1; i <= 34; i++) {
        if((1 << i) - 1 > (n - 1) / S) break;
        for(int j = 0; j + (1 << i) - 1 <= (n - 1) / S; j++) sm[j][i] = max(sm[j][i - 1], sm[j + (1 << (i - 1))][i - 1]);
    }
    int sum_ans = 0;
    ql[1] = 1, qr[1] = 2, ql[2] = 3, qr[2] = 4;
    for(int qi = 1; qi <= m; qi++) {
        int l, r;
        l = ql[qi], r = qr[qi];
        if(l > r) swap(l, r);
        ui ans = 0;
        if(l / S + 1 < r / S) ans = rmq(l / S + 1, r / S - 1);
        if(l / S == r / S) {
            for(int i = l; i <= r; i++) ans = max(ans, a[i]);
        } else ans = max(ans, max(c[l], b[r]));
        if(qi % 2 == 1) sum_ans += ans - 1e9;
        else sum_ans -= ans - 1e9;
    }
    cout << sum_ans << endl;
    return 0;
}
```

---

## 作者：wwwidk1234 (赞：16)

## 题目

给定两个整数 $a,b$，求 $a$ 与 $b$ 的和。

## 思路

本题有多种解法，充分发挥一题多解的思维可以更好地提升 OI 能力。

### 思路 1

我们首先定义两个变量 $a,b$：`int a,b;`。在 C++ 中，`int` 为整形变量，可存放 $-2^{31} \sim 2^{31}-1$ 之间的整数。

接着使用 `cin>>a>>b;` 语句读入 $a$ 与 $b$ 的值。输入数据中 $a,b$ 之间用一个空格隔开，所以 `cin` 就会将第一个数赋值给 $a$，第二个数赋值给 $b$。

然后使用 `cout<<a+b;` 语句输出 $a$ 与 $b$ 的和。`cout` 的功能是输出变量、字符串、常数等值。如果你想在输出后加上一个换行，那么可以使用 `endl`，比如 `cout<<a<<endl<<b;`，这句话的意思就是将 $a,b$ 分别在两行中输出。

注意，`cin` 和 `cout` 功能都在 `iostream` 头文件中，如果想使用就必须将头文件导入。使用 `#include<iostream>` 语句即可将 `iostream` 导入。在更深入学习信息学编程之后将会用到更多的功能（比如 `queue` 等），如果想使用就必须将每个功能的头文件分别导入。如果不想记忆的话，可以使用 `#include<bits/stdc++.h>` 将所有头文件导入。同时，`cin` 和 `cout` 等也必须使用 `using namespace std;` 将命名空间引入。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b;
	cin>>a>>b;
	cout<<a+b;
	return 0;
}
```

### 思路 2

看到题目中的 $a,b$ 并求它们的和，可以联想到**区间求和问题**，用**树状数组**维护一个长度为 $2$ 的序列 $c$，首先对 $c_1$ 增加 $a$，然后对 $c_2$ 增加 $b$，接着使用 `query` 函数将 $c_1 \sim c_2$ 的和求出即为答案。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=5;
int a[N],c[N],n,Q;
inline int lowbit(int x)
{
	return x&-x;
}
inline void modify(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=v;
}
inline int query(int x)
{
	int s=0;
	for(int i=x;i;i-=lowbit(i)) s+=c[i];
	return s;
}
int main()
{
    n=2;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        modify(i,a[i]);
    }
    cout<<query(2);
    return 0;
}
```

### 思路 3

考虑使用最短路算法。首先考虑一个三个结点三个边的有向图，如下所示（其中 $1$ 到 $3$ 的边权为一个很大的数，比 $a+b$ 的值大）：

![](https://cdn.luogu.com.cn/upload/image_hosting/yi0duauf.png)

最短路径就是 $1 \to 2 \to 3$，所以求 $a+b$ 的值就等同于求 $1$ 到 $3$ 的最短路径。因为只有三个结点，所以考虑 Floyd 算法。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr ll inf=1.2e18;
constexpr ll N=7;
ll g[N][N];
int main()
{
    memset(g,0x3f,sizeof g);
    int n=3;
	cin>>g[1][2];
	cin>>g[2][3];
	g[1][3]=inf;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	cout<<g[1][3];
	return 0;
}
```

### 思路 4

**二项式定理**：对于任意自然数 $n$ 以及实数 $a,b$，均有：

$(a + b)^n = \sum_{k=0}^n C_n^k \cdot a^{n-k} b^k$

题目可转化为求 $(a+b) \bmod p$ 的值，其中 $p=1218000211019$ 为质数。所以我们可以考虑使用二项式定理求解该题目。

其中 $C_n^k$ 为组合数，计算公式如下（$x ^{\prime}$ 表示 $x$ 在模 $p$ 意义下的逆元，根据费马小定理可以计算出 $x ^{\prime}=x^{p-2}$）：

$$
\begin{aligned}
C_n^k \bmod p &= \dfrac{n!}{k!(n-k)!} \bmod p \\
 &= n! \cdot k!^{\prime} \cdot (n-k)!^{\prime} \bmod p
\end{aligned}
$$

首先初始化一下阶乘和阶乘的逆元（`f[i]` 表示 $i$ 的阶乘，`invf[i]` 表示 $i!$ 的逆元，`ksm(a,b)` 的功能是计算 $a^b \bmod p$ 的值）：

```cpp
f[0]=invf[0]=1;
for(int i=1;i<10;i++) f[i]=f[i-1]*i%mod;
for(int i=1;i<10;i++) invf[i]=invf[i-1]*ksm(i,mod-2)%mod;
```

然后套二项式定理公式：

```cpp
ll ans=0;
for(int k=0;k<=1;k++) ans=(ans+C(n,k)*ksm(a,n-k)*ksm(b,k))%mod;
```

最后输出 `ans` 即可。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=10;
constexpr ll mod=1218000211019;
ll a,b,f[N],invf[N];
inline ll ksm(ll a,ll b)
{
    ll s=1;
    while(b)
    {
        if(b&1) s=s*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return s;
}
inline ll C(ll a,ll b)
{
    if(a<b) return 0;
    return f[a]*invf[b]%mod*invf[a-b]%mod;
}
int main()
{
    cin>>a>>b;
    int n=1;
    f[0]=invf[0]=1;
    for(int i=1;i<10;i++) f[i]=f[i-1]*i%mod;
    for(int i=1;i<10;i++) invf[i]=invf[i-1]*ksm(i,mod-2)%mod;
    ll ans=0;
    for(int k=0;k<=1;k++) ans=(ans+C(n,k)*ksm(a,n-k)*ksm(b,k))%mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：XZhuRen (赞：16)

诈骗题。

首先发现这个问题让我们求两个正整数向加，不取模，记 $f(a,b)=a+b$。

我们手打 $f(a,b)$ 在 $a,b\le 1000$ 的部分。发现 $f(a,b)$ 在 $a,b\le 1000$ 的时候恰好等于 `(a^b)+((a&b)<<1)`。

由于问题没有多组数据，考虑直接输出这个结果提交。

发现可以通过，时间复杂度 $\mathcal{O}(1)$。

# 笑点解析：

运算使用了加法。

---

## 作者：aaalys (赞：15)

## 思路

前置芝士：FHQ Treap 维护的文艺平衡树。

在数学中我们学过，$a+b$ 符合交换律，所以可以使用一种数据结构~~快速~~将 $a$ 和 $b$ 的值交换。

这可以用 FHQ Treap 维护的文艺平衡树来完成，只需在平衡树里存个和就行。

## 代码

```cpp
#include <bits/stdc++.h>
#define set(x) node &now = tr[x]
#define ls now.lc
#define rs now.rc
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int N = 10;
int tot, root;
int a[N];
struct node{
    int lc, rc, pri, sz;
    int val, lzrev, sum;
}tr[N];
int newNode(int k){
    set(++tot);
    now.sz = 1;
    now.pri = rand();
    now.val = k;
    now.sum = k;
    return tot;
}
void pushup(int u){
    set(u);
    now.sz = tr[ls].sz + tr[rs].sz + 1;
    now.sum = tr[ls].sum + tr[rs].sum + now.val;
}
void reverse(int u){
    if (!u)return;
    set(u);
    swap(ls, rs);
    now.lzrev ^= 1;
}
void pushdown(int u){
    set(u);
    if (now.lzrev){
        reverse(ls);
        reverse(rs);
        now.lzrev = 0;
    }
}
pii split(int u, int x){
    if (!u)return {0, 0};
    pushdown(u);
    set(u);
    if (x == tr[ls].sz + 1){
        int k = rs;
        rs = 0;
        pushup(u);
        return {u, k};
    }
    if (x > tr[ls].sz){
        pii t = split(rs, x - tr[ls].sz - 1);
        rs = t.first;
        pushup(u);
        return {u, t.second};
    }
    pii t = split(ls, x);
    ls = t.second;
    pushup(u);
    return {t.first, u};
}
int merge(int u, int v){
    if (!u || !v)return u | v;
    if (tr[u].pri > tr[v].pri){
        pushdown(u);
        set(u);
        rs = merge(rs, v);
        pushup(u);
        return u;
    }
    pushdown(v);
    set(v);
    ls = merge(u, ls);
    pushup(v);
    return v;
}
void insert(int k){
    root = merge(root, newNode(k));
}
void update(int l, int r){
    pii x = split(root, r);
    pii y = split(x.first, l - 1);
    reverse(y.second);
    root = merge(merge(y.first, y.second), x.second);
}
int query(int l, int r){
    pii x = split(root, r);
    pii y = split(x.first, l - 1);
    int ans = tr[y.second].sum;
    root = merge(merge(y.first, y.second), x.second);
    return ans;
}
int main(){
    int a, b;
    cin >> a >> b;
    insert(a);//插入两个数
    insert(b);
    update(1, 2);//交换
    cout << query(1, 2);//求和
    return 0;
}
```

---

## 作者：Aurelia_Veil (赞：15)

# 题解：P1001 A+B Problem

## 正文：

我们一眼可以看出，这是要我们求出一个大小为 $114 \times 514$ 的矩阵的和，于是可以使用二维树状数组快速求出答案。
记住这是一个模板题！

### 我们来讲解一些二维树状数组的写法：

#### 1. 创建树状数组：

直接创建一个大小为 $114 \times 514$ 的二维树状数组，但是最大我设为的 $2^{12} \times 2^{12}$ 的大小。

重要代码：

```cpp
const int N=1<<12;
long long tree[N][N][7];
```

#### 2. 填充二维线段树：

我们在输入时填充二维线段树，但是因为这是构造题，所以可以随机输出咩。

重要代码：

```cpp
for(int i=3;i<=n;i++){//从 3 开始咩
    for(int j=3;j<=m;j++){
        add(i,j,rand());
    }
}
```

```cpp
void add(int x,int y,long long z){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=m;j+=lowbit(j)){
            tree[i][j][1]+=z;
            tree[i][j][2]+=z*x;
            tree[i][j][3]+=z*y;
            tree[i][j][4]+=z*x*y;
        }
    }
}
```

#### 3. 如何区间求和：

我们需要使用位运算求出这个数的所有子集，使用 $sum$ 变量统计最终结果。

重要代码：

```cpp
long long sum(int x,int y){
    long long sum=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            sum+=(x+1)*(y+1)*tree[i][j][1]-(y+1)*tree[i][j][2]-(x+1)*tree[i][j][3]+tree[i][j][4];
        }
    }
    return sum;
}
```

#### 4. 输入格式：

为了保证输入格式符合题目，我们要修改输入代码。

重要代码：

```cpp
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    n=114;
    m=514;
    n++;
    m++;
    for(int i=3;i<=n;i++){
        for(int j=3;j<=m;j++){
            add(i,j,rand());
        }
    }
    int k,t=3;
    while(t){
        if(t==3){
            k=1;
        }else if(t==2){
            k=1;
        }else{
            k=2;
        }
        if(k==1){
            int ax,ay,bx,by,z;
            if(t==3){
                ax=1;
                ay=1;
                bx=1;
                by=1;
                z=a;
            }else{
                ax=2;
                ay=1;
                bx=2;
                by=1;
                z=b;
            }
            ax++;
            ay++;
            bx++;
            by++;
            add(bx,by,z);
            add(bx,ay-1,-z);
            add(ax-1,by,-z);
            add(ax-1,ay-1,z);
        }else{
            int ax=1e9/1e9,ay=2e7/2e7-2+2,bx=1*2+0,by=-1+2;
            printf("%lld\n",sum(bx,by)-sum(bx,ay-1)-sum(ax-1,by)+sum(ax-1,ay-1));
        }
        t--;
    }
    return 0;
}
```

---

### 最终代码

代码如下咩：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1<<12;
long long tree[N][N][7];
int n,m;
int lowbit(int x){
    return x&(-x);
}
void add(int x,int y,long long z){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=m;j+=lowbit(j)){
            tree[i][j][1]+=z;
            tree[i][j][2]+=z*x;
            tree[i][j][3]+=z*y;
            tree[i][j][4]+=z*x*y;
        }
    }
}
long long sum(int x,int y){
    long long sum=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            sum+=(x+1)*(y+1)*tree[i][j][1]-(y+1)*tree[i][j][2]-(x+1)*tree[i][j][3]+tree[i][j][4];
        }
    }
    return sum;
}
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    n=114;
    m=514;
    n++;
    m++;
    int k,t=3;
    while(t){
        if(t==3){
            k=1;
        }else if(t==2){
            k=1;
        }else{
            k=2;
        }
        if(k==1){
            int ax,ay,bx,by,z;
            if(t==3){
                ax=1;
                ay=1;
                bx=1;
                by=1;
                z=a;
            }else{
                ax=2;
                ay=1;
                bx=2;
                by=1;
                z=b;
            }
            ax++;
            ay++;
            bx++;
            by++;
            add(bx,by,z);
            add(bx,ay-1,-z);
            add(ax-1,by,-z);
            add(ax-1,ay-1,z);
        }else{
            int ax=1e9/1e9,ay=2e7/2e7-2+2,bx=1*2+0,by=-1+2;
            printf("%lld\n",sum(bx,by)-sum(bx,ay-1)-sum(ax-1,by)+sum(ax-1,ay-1));
        }
        t--;
    }
    return 0;
}
```

## 正解的语法讲解：

### 1.

```cpp
#include<iostream>
```

这个指头文件，是一条预处理指令，其中包含一下组件：

- `std::istream` 类：指输入流。

- `std::ostream` 类：指输出流

- `std::cin` 对象：这是 `std::istream` 类中的其中一个对象，表示标准输入流，通常为键盘输入。

- `std::cout` 对象：这是 `std::ostream` 类中的其中一个对象，表示标准输出流，通常为屏幕输出。

---

### 2.

```cpp
using namespace std;
```

这个为标准命名空间，这段代码是要将 `std` 作为标准命名，`std` 为 C++ 标准库的命名空间。

---

### 3.

```cpp
int main(){

    return 0;
}
```

这个是主函数，表示程序刚开始要运行的函数。

---

所以代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b;//定义两个变量 a 和 b 
    cin>>a>>b;//输入并赋值 a 和 b 
    cout<<a+b;//输出 a + b 的和 
    return 0;
}
```

---

## 作者：lfxxx_ (赞：14)

题解里怎么可以没有我们的主席树呢！

考虑将 $A$ 和 $B$ 转化成一个长度为 $2$ 的序列。

然后对这个序列维护可持久化线段树。

最后就是一个区间和查询就可以了！

```cpp
#include<bits/stdc++.h>
#define I using
#define love namespace
#define KukCair std
I love KukCair;//不要管这句-----------
const int N=1e5+5;
int root[N],a[N],tot;
int tr[N<<5],ls[N<<5],rs[N<<5],tag[N<<5];
void pushup(int p){tr[p]=tr[ls[p]]+tr[rs[p]];}
int build(int pl,int pr)
{
	int p=++tot;
	if(pl==pr)
	{
		tr[p]=a[pl];
		return p;
	}
	int mid=(pl+pr)>>1;
	ls[p]=build(pl,mid);
	rs[p]=build(mid+1,pr);
	pushup(p);
	return p;
}
void addtag(int p,int pl,int pr,int d)
{
	tag[p]+=d;
	tr[p]+=(pr-pl+1)*d;
}
void pushdown(int p,int pl,int pr)
{
	int mid=(pl+pr)>>1;
	if(tag[p])
	{
		addtag(ls[p],pl,mid,tag[p]);
		addtag(rs[p],mid+1,pr,tag[p]);
		tag[p]=0;
	}
}
int update(int p,int pl,int pr,int L,int R,int d)
{
	++tot;
	tr[tot]=tr[p];
	ls[tot]=ls[p];
	rs[tot]=rs[p];
	tag[tot]=tag[p];
	p=tot;
	if(L<=pl&&pr<=R)
	{
		addtag(p,pl,pr,d);
		return p; 
	}
	int mid=(pl+pr)>>1;
	pushdown(p,pl,pr);
	if(L<=mid)ls[p]=update(ls[p],pl,mid,L,R,d);
	if(mid<R)rs[p]=update(rs[p],mid+1,pr,L,R,d);
	pushup(p);
	return p;
}
int query(int p,int pl,int pr,int L,int R)
{
	if(R<pl||pr<L)
		return 0;
	if(L<=pl&&pr<=R)
		return tr[p];
	int mid=(pl+pr)>>1;
	pushdown(p,pl,pr);
	return query(ls[p],pl,mid,L,R)+query(rs[p],mid+1,pr,L,R);	
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n=2;
	root[0]=build(1,n);
	int x,y;
	cin>>x>>y;
	root[1]=update(root[0],1,n,1,1,x);
	root[2]=update(root[1],1,n,2,2,y);
	cout<<query(root[2],1,n,1,2);
	return 0;
}
```

---

## 作者：GoldenSTEVE7 (赞：13)

## 写在前面的话
注意，如果你是新手，首先就是养成习惯：

1. 基础代码模板一定要记牢。
2. 一定要记得打**分号**。

## 本题代码


```cpp
#include <iostream>
using namespace std;

int main() {
    int a,b;       //定义变量 a, b
    cin >> a >> b; //输入 a, b
    cout << a+b;   //输出 a+b 
    return 0;      //不要忘记这一行，建议再打初始代码时，提前写好
}
```

-----
接下来的不是新手可以不用看了

整活时间到！
-----

$$
a+b = (a+b) \times 1
$$

众所周知

$$
\lim_{x\rightarrow0} \frac{\sin x}{x} = 1
$$

代入得

$$
a+b = 
\lim_{x\rightarrow0} \frac{\sin x}{x} \times (a+b)
$$

$\sin$ 我们可以用泰勒级数实现

我们把 $x$ 取小亿点点，精度可能是过得去的。

代码如下：
```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
double Sin(double x) {
    double ret = x, a = x, p = x * x, cur = 1; 

    for (int i = 1; i <= 100; i++) { 
        cur *= (2 * i) * (2 * i + 1); a *= p / cur;
        if (i % 2 == 0) ret += a;
        else  ret -= a;
    }
    return ret;
}
int main() {
	int a, b; cin >> a >> b;
	double x = 0.00000001;
	double q = Sin(x) / x;
	int ans = int(ceil(q*a+q*b));
	if(ans < -1) ans--;
	cout << ans;
	return 0;
}
```

---

## 作者：LEWISAK (赞：12)

**本篇题解并非本题的正规做法。**

题解区还没有ISAP求最大流的方法？蒟蒻来一发！

注意到我们可以考虑将求解二数相加转化为求最大流问题，建出下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jt3k8ix5.png)

然后进行增广路求解，由于 $1\to t$ 和 $2 \to t$ 的流量都是无限的，所以最后最大流就是 $s \to 1$ 与 $s \to 2$ 的流量和，也就是 $a+b$。

最后，实现上，由于 ISAP 无法处理负数，所以将 $a$ 和 $b$ 都加 $10^9$ 即可。 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace kong{bool st;}
namespace zhu{
int tot=1,head[1001000],lead[1001000],dep[1001000],gap[1001000],n,s,t,jia=1e9;
queue<int> q;
struct{
	int nxt,to,w;
}e[2002000];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
	e[++tot]={head[v],u,0};
	head[v]=tot;
	return;
}
void bfs(){
	q.push(t);
	dep[t]=1;
	gap[1]++;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dep[v]){
				dep[v]=dep[x]+1;
				q.push(v);
				gap[dep[v]]++;
			}
		}
	}
}
int dfs(int x,int flow){
	if(x==t||flow==0) return flow;
	int rest=flow;
	for(int i=lead[x];i&&rest;i=e[i].nxt){
		lead[x]=i;
		int v=e[i].to,w=e[i].w;
		if(dep[x]==dep[v]+1&&w>0){
			int t=dfs(v,min(rest,w));
			rest-=t;
			e[i].w-=t;
			e[i^1].w+=t;
		}
	}
	if(rest){
		gap[dep[x]]--;
		if(!gap[dep[x]]){
			dep[s]=n+1;
		}
		dep[x]++;
		gap[dep[x]]++;
	}
	return flow-rest;
}
int ISAP(){
	int ans=0;
	bfs();
	while(dep[s]<=n){
		for(int i=1;i<=n;i++){
			lead[i]=head[i];
		}
		ans+=dfs(s,1e18);
	}
	return ans;
}
string main(){
	int a,b;
	cin>>a>>b;
	a+=jia;b+=jia;
	s=3,t=4;
	add(s,1,a);add(s,2,b);
	add(1,t,a);add(2,t,b);
	n=4;
	cout<<ISAP()-jia*2<<'\n';
	return "调了好久……";
}
}
namespace kong{bool ed;double kj(){return (&st-&ed)/1048576.0;}}
signed main(){
	cerr<<zhu::main()<<'\n'<<kong::kj();
	return 0;
}
```

---

## 作者：dulinfan2023 (赞：12)

数论好题！！

先说结论：$a+b=a$ $\texttt{and}$ $b + a $ $\texttt{or}$ $b$

原因：使用二进制加法。

对于 $a,b$ 均为 $1$ 的位，在 $a$ $\texttt{and}$ $b$ 和 $a$ $\texttt{or}$ $b$ 中被算了刚好 $2$ 次。

对于 $a,b$ 有 $1$ 位是 $1$ 的位，在 $a$ $\texttt{or}$ $b$ 中被算了刚好 $1$ 次。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b;
signed main(){
	cin>>a>>b;
	cout<<(a&b)+(a|b);
}

```

---

## 作者：huangboning (赞：11)

考虑用位运算实现加法。

容易发现，异或就相当于对每一位进行不进位的加法。

那么如何处理进位？只有两数都为 1 才会产生进位，于是想到与运算，记得左移一位，表示乘二。

```cpp
#include<bits/stdc++.h>
using namespace std;
int add(int a,int b){
    while(b!=0){
        int sum=a^b;//不进位的加法
        int carry=(a&b)<<1;//进位
        a=sum;
        b=carry;
    }
    return a;
}
int a,b;
int main()
{
	ios::sync_with_stdio(0);
	cin>>a>>b;
	cout<<add(a,b);
	return 0;
 } 
```

---

## 作者：许多 (赞：10)

看到题意，我们不难想到先建一棵树，用树剖来解这个题。

我们可以建一个两个节点的树，显然这样结构的树是唯一且确定的。然后对两个节点的权值进行修改，最后求出这条链上的权值和。剩下的就是模板了

让我们直接看到代码：
```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define LL long long
#define N 100001
using namespace std;
LL n,m,r;
LL a[N],father[N],dep[N],siz[N],son[N],top[N],seg[N],rev[N];
vector<LL>bian[N];
void dfs1(LL now,LL fa){
	father[now]=fa;
	dep[now]=dep[fa]+1;
	siz[now]=1;
	for(int i=0;i<bian[now].size();i++){
		if(bian[now][i]!=fa){
			dfs1(bian[now][i],now);
			siz[now]+=siz[bian[now][i]];
			if(siz[bian[now][i]]>siz[son[now]])son[now]=bian[now][i];
		}
	}
	return;
}
void dfs2(LL now,LL Top){
	top[now]=Top;
	seg[now]=++seg[0];
	rev[seg[0]]=now;
	if(son[now])dfs2(son[now],Top);
	for(int i=0;i<bian[now].size();i++)
		if(bian[now][i]!=father[now]&&bian[now][i]!=son[now])
			dfs2(bian[now][i],bian[now][i]);
	return ;
}
LL sum[N<<2],add[N<<2],qwe=0;
void build(LL l,LL r,LL now){
	if(l==r){
		sum[now]=a[rev[l]];
		return ;
	}
	LL mid=(l+r)>>1;
	build(l,mid,now<<1);
	build(mid+1,r,now<<1|1);
	sum[now]=sum[now<<1]+sum[now<<1|1];
	return;
}
void Add(LL l,LL r,LL now,LL v){
	add[now]+=v;
	sum[now]+=(r-l+1)*v;
	return;
}
void pushdown(LL l,LL r,LL now){
	LL mid=(l+r)>>1;
	if(add[now]==0)return;
	Add(l,mid,now<<1,add[now]);
	Add(mid+1,r,now<<1|1,add[now]);
	add[now]=0;
	return;
}
void modify(LL l,LL r,LL x,LL y,LL now,LL v){
	if(l>=x&&r<=y)return Add(l,r,now,v);
	LL mid=(l+r)>>1;
	pushdown(l,r,now);
	if(x<=mid)modify(l,mid,x,y,now<<1,v);
	if(y>mid) modify(mid+1,r,x,y,now<<1|1,v);
	sum[now]=sum[now<<1]+sum[now<<1|1];
	return ;
}
LL query(LL l,LL r,LL x,LL y,LL now){
	if(l>=x&&r<=y)return sum[now];
	int mid=(l+r)>>1,Max=0;
	pushdown(l,r,now);
	if(x<=mid)Max+=query(l,mid,x,y,now<<1);
	if(y>mid) Max+=query(mid+1,r,x,y,now<<1|1);
	return Max;
}
int main(){
	n=2;
	bian[1].push_back(2);bian[2].push_back(1);
	dfs1(1,1);
	dfs2(1,1);
	build(1,n,1);
	for(int i=1;i<=3;i++){
		if(i==1){
			int x=1,y=1,z;
            cin>>z;
			while(top[x]!=top[y]){
				if(dep[top[x]]<dep[top[y]])swap(x,y);
				modify(1,n,seg[top[x]],seg[x],1,z);
				x=father[top[x]];
			}
			if(dep[x]>dep[y])swap(x,y);
			modify(1,n,seg[x],seg[y],1,z);
		}
		else if(i==2){
			int x=2,z;
            cin>>z;
			modify(1,n,seg[x],seg[x]+siz[x]-1,1,z);
		}
		else if(i==3){
            int x=1,y=2;
			LL Max=0;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]])swap(x,y);
				Max+=query(1,n,seg[top[x]],seg[x],1);
				x=father[top[x]];
			}
			if(dep[x]>dep[y])swap(x,y);
			Max+=query(1,n,seg[x],seg[y],1);
			printf("%lld\n",Max);
		}
		else if(i==4){
			int x;
			scanf("%d",&x);
			printf("%lld\n",query(1,n,seg[x],seg[x]+siz[x]-1,1));
		}
	}
	return 0;
}
```

看起来也是非常简单呢。让我们一起，向大牛前进！

---

## 作者：_luogu_huowenshuo_ (赞：9)

## 思路
使用递归来求和，递归函数的第一个参数代表进位，第二个模拟加法，如果 $a$ 等于 $0$，则代表没有进位，直接返回 $b$。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int add(int a,int b)
{
	if(!a)return b;
	return add((a&b)<<1,a^b);
}
signed main()
{
	int a,b;cin>>a>>b;
	cout<<add(a,b);
 	return 0;
}

```

---

## 作者：TemplateClass (赞：9)

简单题，不知道大家为什么做得那么麻烦。

引用一句忘了在哪里看到的话：遇到不明二元关系就建图。加法似乎没有什么特别好的性质，所以我们建两个结点 $u$ 和 $v$，然后令 $u$ 的权值为 $a$，$v$ 的权值为 $b$，接着让它们之间建一条双向边，不难发现这个图是一个强连通图。

然后这就是缩点板子题了，我们跑一个 Tarjan 然后拓扑排序时 dp 一下即可，时间复杂度 $O(1)$，吊打大多数带 $\log$ 甚至是根号的题解。

注意输入的数可能是负数，所以 dp 时不能直接取 `std::max` 而是要相加。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<set>
#include<cassert>

constexpr int N = 2 + 5;

int a, b, n = 2, w[N]; std::vector<int> G[N], nG[N];
int dfn[N], low[N], blg[N], tot = 0;
std::stack<int> st; bool in_st[N], pred[N];
int scct = 0, wsum[N]; std::vector<int> scc[N];
std::set<int> added[N]; int in[N], dp[N];

void tarjan(int u) {
	dfn[u] = low[u] = ++tot;
	st.push(u); in_st[u] = true;
	for(const auto& v : G[u]) {
		if(!dfn[v]) {
			tarjan(v); low[u] = std::min(low[u], low[v]);
		} else {
			if(in_st[v]) low[u] = std::min(low[u], low[v]);
		}
	}
	if(dfn[u] == low[u]) {
		std::vector<int> vec; vec.push_back(u);
		while(st.top() != u) {
			blg[st.top()] = scct + 1;
			vec.push_back(st.top());
			wsum[scct + 1] += w[st.top()];
			in_st[st.top()] = false; st.pop(); 
		}
		wsum[scct + 1] += w[u];
		in_st[u] = false; st.pop();
		blg[u] = scct + 1; scc[++scct] = vec;
	}
}

inline int topo() {
	std::queue<int> q; int ret = 0;
	for(int u = 1; u <= scct; ++u) {
		if(!in[u]) {
			q.push(u); dp[u] = wsum[u];
		}
	}
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(const auto& v : nG[u]) {
			dp[v] = dp[u] + wsum[v];
			ret += dp[v]; if(!(--in[v])) q.push(v);
		}
	}
	return ret;
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> w[1] >> w[2]; G[1].push_back(2);
	for(int u = 1; u <= n; ++u) {
		if(!dfn[u]) tarjan(u);
	}
	for(int u = 1; u <= n; ++u) {
		for(const auto& v : G[u]) {
			int bu = blg[u], bv = blg[v];
			if(bu == bv || added[bu].count(bv)) continue;
			added[bu].insert(bv); nG[bu].push_back(bv); ++in[bv];
		}
	}
	// std::cerr << wsum[1] << "\n";
	std::cout << topo() << "\n";
	
	return 0;
}
```

---

## 作者：llamn (赞：9)

我们发现题目给了我们一些数，要求我们进行求和。同时，当我们逐个输入每一个数字时，原来的数就要乘 $10$ 并加上新数。

这意味着我们需要维护一个支持单点乘法、单点加法、区间求和的数据结构，当然是线段树啦！

```cpp
#include <bits/stdc++.h> 
#define _eggy_ using 
#define _party_ namespace
_eggy_ _party_ std;

#define cint const int&
template <unsigned char ce>
struct dzpd
{
	struct dzpd <ce-1> ls,rs;
	int l,r,sum;
	void bd(cint bl, cint br)
	{
		l = bl, r = br;
		if (bl == br)
		{
			sum = 0;
			return;
		}ls.bd(bl,(bl+br)>>1);
		rs.bd(((bl+br)>>1)+1,br);
		sum = ls.sum + rs.sum;
	}
	void add(cint t1, cint v)
	{
		if (l == r)
		{
			sum += v;
			return;
		}
		if (t1 <= ls.r) ls.add(t1,v);
		else rs.add(t1,v);
		sum = ls.sum + rs.sum;
	}
	void mul(cint t1, cint v)
	{
		if (l == r)
		{
			sum *= v;
			return;
		}
		if (t1 <= ls.r) ls.mul(t1,v);
		else rs.mul(t1,v);
		sum = ls.sum + rs.sum;
	}
	int getsum(cint t1, cint t2)
	{
		if (t1 <= l && r <= t2) return sum;
		if (t2 <= ls.r) return ls.getsum(t1,t2);
		if (t1 >= rs.l) return rs.getsum(t1,t2);
		return ls.getsum(t1,t2) + rs.getsum(t1,t2);
	}
};

template <>
struct dzpd <0>
{
	int l,r,sum;
	void bd(cint bl, cint br) {l = bl, r = br, sum = 0;}
	void add(cint t1, cint v) {sum += v;}
	void mul(cint t1, cint v) {sum *= v;}
	int getsum(cint t1, cint t2) {return sum;}
};
struct dzpd <10> t;

char c;
int i;
bool f;
int main()
{
	i = 1, f = 1;
	t.bd(1,2);
	while (scanf("%c",&c) != -1)
	{
		if (c == ' ' || c == '\n' || c == '\r')
		{
			i++, f = 1;
			continue;
		}
		if (c == '-')
		{
			f = 0;
			continue;
		}
		t.mul(i,10);
		if (f) t.add(i,c - '0');
		else t.add(i,'0' - c);
	}cout << t.getsum(1,2);
    return 0;
}

```

---

## 作者：CQBZ_ZJYjoe (赞：8)

# 本篇题解前置知识：splay

## 思路分析

知周所众，平衡树是一个可以高效维护区间问题的数据结构。看到此题，我们可以将其转化为两个元素的区间，对区间求和，显然，可以使用平衡树解决。

## 代码实现


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,tot;
struct Node
{
    Node *ls,*rs,*fa;
    int val,siz,idx,sum;
}tr[100010],*rt,*NIL,*cnt;
void update(Node *x)
{
    if (x==NIL)
        return ;
    x->siz=x->ls->siz+x->rs->siz+1;
    x->sum=x->ls->sum+x->rs->sum+x->val;
}//更新节点
bool getson(Node *x)
{
    return x==x->fa->rs;
}//左右儿子
void rotate(Node *x)
{
    Node *fa=x->fa,*gfa=fa->fa;
    if (!getson(x))
    {
        if (!getson(fa))
            gfa->ls=x;
        else 
            gfa->rs=x;
        x->fa=gfa;
        fa->ls=x->rs;
        x->rs->fa=fa;
        x->rs=fa;
        fa->fa=x;
    }
    else 
    {
        if (!getson(fa))
            gfa->ls=x;
        else 
            gfa->rs=x;
        x->fa=gfa;
        fa->rs=x->ls;
        x->ls->fa=fa;
        x->ls=fa;
        fa->fa=x;
    }
    update(fa);
    update(x);
}//旋转
void splay(Node *x,Node *y)
{
    while (x->fa!=y)
    {
        Node *fa=x->fa,*gfa=fa->fa;
        if (gfa!=y)
        {
            if (getson(x)==getson(fa))
                rotate(fa);
            else 
                rotate(x);
        }
        rotate(x);
    }
    if (y==NIL)
        rt=x;
    update(x);
}//splay操作
Node *newnode(int x)
{
    Node *p=++cnt;
    p->val=p->sum=x;
    p->siz=1;
    p->fa=p->ls=p->rs=NIL;
    p->idx=++tot;
    return p;
}
void ins(Node *&u,int x,Node *fa)
{
    if (u==NIL)
    {
        u=newnode(x);
        u->fa=fa;
        splay(u,NIL);
        return ;
    }
    if (u->val>=x)
        ins(u->ls,x,u);
    else 
        ins(u->rs,x,u);
    update(u);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    NIL=&tr[0];
    NIL->val=0x7f7f7f7f;
    NIL->siz=0;
    NIL->fa=NIL->ls=NIL->rs=NIL;
    cnt=NIL;
    rt=NIL;
    ins(rt,0x7f7f7f7f,NIL);
    ins(rt,-0x7f7f7f7f,NIL);//初始化+哨兵节点

    int a,b;
    cin>>a>>b;

    ins(rt,a,NIL);
    ins(rt,b,NIL);//插入

    cout<<rt->sum;
    return 0;
}
```


## 提醒

注意指针不要越界！！！

---

## 作者：longyitongxue (赞：8)

Update on 2025/5/10：出了点小问题

[Question's door](https://www.luogu.com.cn/problem/P1001)
# 大炮思路
学了高精度，回来做普通的低级 $a+b$ 了！

不过这道题，考虑到负数情况，所以，我们需要附上高精减的代码。

如果 $a$ 和 $b$ 都为负数，那么输出一个负号，后面接着 $\left|a\right|+\left|b\right|$。

如果 $a,b$ 其中一个为负数，如果 $a$ 是负数，输出 $b-a$，反之输出 $a-b$。

剩余情况直接 $a+b$ 即可。

首先，范围只有 $10^9$ 之大，所以我们数组最多最多也就开个 $9$ 的大小。不过保险起见，开大一点也不是不可以。

其次，我们按照竖式的方法，对齐个位（幸好没小数点）（如下）

$$
\begin{align}
&&10000154&\\
+&&02551441&\\
&&\overline{\quad\quad12551595}&
\end{align}
$$
$$
\begin{align}
&&114514&\\
-&&111111&\\
&&\overline{\quad\quad003403}&
\end{align}
$$

先处理加减法，然后，如果有进位或退位，后面再处理。接着不能有前导零，有就删，最后反着输出结果（因为对齐了个位需要倒着对齐，到最后还得翻转过来）。

# [整活代码](https://www.luogu.com.cn/record/216601942)
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string add(string x,string y){
	string ans;
	int a[15]={},b[15]={},c[15]={};
	int jw,lena=x.size(),lenb=y.size(),lenc;
	for(int i=1;i<=lena;i++){
		a[i]=x[lena-i]-'0';
	}
	for(int i=1;i<=lenb;i++){
		b[i]=y[lenb-i]-'0';
	}
	lenc=max(lena,lenb);
	for(int i=1;i<=lenc;i++){
		c[i]=a[i]+b[i];
	}
	for(int i=1;i<=lenc;i++){
		c[i+1]+=(c[i]/10);
		c[i]%=10;
	}
	if(c[lenc+1]!=0)lenc++;
	while(c[lenc]==0&&lenc>1)lenc--; 
	for(int i=lenc;i>=1;i--){
		ans+=char(c[i]+'0');
	}
	return ans;
}
string sub(string x,string y){
	string ans;
    if(x.size()<y.size()||(x.size()==y.size()&&x<y)){
		swap(x,y);
		ans="-";
	}
	int a[15]={},b[15]={},c[15]={};
	int lena=x.size(),lenb=y.size(),lenc;
	for(int i=1;i<=lena;i++){
		a[i]=x[lena-i]-'0';
	}
	for(int i=1;i<=lenb;i++){
		b[i]=y[lenb-i]-'0';
	}
	lenc=max(lena,lenb);
	for(int i=1;i<=lenc;i++){
		if(a[i]<b[i]){
			a[i]+=10;
			a[i+1]--;
		}
		c[i]=a[i]-b[i];
	}
	while(c[lenc]==0&&lenc>1)lenc--;
	for(int i=lenc;i>=1;i--){
		ans+=char(c[i]+'0');
	}
	return ans;
}
int main(){
    string a,b;
    cin>>a>>b;
    if(a[0]=='-'&&b[0]=='-'){
        cout<<'-'<<add(a.substr(1),b.substr(1));
    }else if(a[0]=='-'||b[0]=='-'){
        if(a[0]=='-'){
            cout<<sub(b,a.substr(1));
        }else{
            cout<<sub(a,b.substr(1));
        }
    }else{
        cout<<add(a,b);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：8)

啊，这里面竟然没有模拟退火的题解。

我们使用模拟退火，如果答案接近 $A+B$ 的值，就接受这个值，否则一定概率接受。

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 SA_rand(time(0));
int a,b;
double ans=1e308,t,dt=0.995,SA_clk=-1;
double cal(double aa){
	return abs(a+b-aa);
}
void SA(){
	double Ans=ans;
	t=1e12;
	while(t>1e-18){
		double ANS=Ans+(((long long)SA_rand()<<1)-UINT_MAX)*t;
		if(cal(ANS)<cal(ans)){
			ans=ANS,Ans=ANS;
		}else if(exp((cal(ans)-cal(ANS))/t)*UINT_MAX>SA_rand())Ans=ANS;
		t*=dt;
	}
	if(SA_clk<0)SA_clk=(double)clock()/CLOCKS_PER_SEC;
}
void sol(){
	ans=0;
	SA();
	while((double)clock()/CLOCKS_PER_SEC<0.95-SA_clk)SA();
}
int main(){
	cin>>a>>b;
    sol();
	printf("%.0f",ans);
} 
```

---

## 作者：_yang_yi_bo_ (赞：7)

题解区有网络流，主席树，splay，连莫队题解都没有，是不是瞧不起莫队啊？

很显然知道区间 $[l,r]$ 的和，也可以很快求出区间 $[l,r],[l-1,r],[l+1,r],[l,r-1],[l,r+1]$ 的和。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k, d;
int a[2000005], p[2000005];
int ans[2000005];
struct kkk {
  int l, r, i;
  bool operator<(const kkk& x) const {
    if (x.i != i) return i < x.i;
    if (i & 1) return r < x.r;
    return r > x.r;
  }
} e[2000005];
signed main() {
  n = 114514, m = 114514;
  d = n / round(pow(m, 0.5));
  for (int i = 1; i <= 2; i++) cin >> a[i];
  for (int i = 3; i <= n; i++) a[i] = 114514;
  for (int i = 1; i <= m; i++) {
    e[i].l = 1, e[i].r = i;
    p[i] = i, e[i].i = e[i].l / d;
  }
  sort(p + 1, p + m + 1, [](int x, int y) { return e[x] < e[y]; });
  for (int i = 1, l = 1, r = 0; i <= m; i++) {
    while (l > e[p[i]].l) {
      l--;
      ans[0] += a[l];
    }
    while (r < e[p[i]].r) {
      r++;
      ans[0] += a[r];
    }
    while (l < e[p[i]].l) {
      ans[0] -= a[l];
      l++;
    }
    while (r > e[p[i]].r) {
      ans[0] -= a[r];
      r--;
    }
    ans[p[i]] = ans[0];
  }
  cout << ans[2] << "\n";
  return 0;
}
```

---

## 作者：__CJY__ (赞：7)

## 思路
直接输出就不说了……
### 前缀和
可以用前缀和，设 $s$ 为前缀和数组，$t$ 为输入的数：$s_i=s_{i-1}+t$，最后输出 $s_2$ 即可。
### 位运算
我们可以使用 $a \oplus b$ 得到不考虑进位的加法结果，用 `(a&b)<<1` 得到所有需要进位的位置，将不考虑进位的结果和进位值相加，直到 $b=0$ 为止。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;cin>>a>>b;
	cout<<a+b;
}
```
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[5],t;
int main(){
	for(int i=1;i<=2;i++) cin>>t,s[i]=s[i-1]+t;
	cout<<s[2];
}
```
```cpp
#include<bits/stdc++.h>
using namespace std;
int add(int a,int b){
	if(!b) return a;
	return add(a^b,(a&b)<<1);
}
int main(){
	int a,b;cin>>a>>b;
	cout<<add(a,b);
}
```

---

## 作者：sto__Liyhzh__orz (赞：7)

[传送门](https://www.luogu.com.cn/problem/P1001)

本题解使用矩阵快速幂。

### 题意：

给定函数 $f(x)=\begin{cases} a & x =1 \\ b & x = 2 \\ f(x-1)+f(x-2)& x \ge 3 \end{cases}$

求 $f(3)$。

我可以发现这就是一个非常简单的广义斐波那契数列。

现在来计算初始矩阵：

$$f(n)=1\times f(n-1)+1\times f(n-2)$$

$$f(n-1)=1\times f(n-1)+0\times f(n-2)$$

所以初始矩阵值为：

$$\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$$

递推式为：

$$\begin{bmatrix} f_{i + 1} \\ f_i \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} \times \begin{bmatrix} f_i \\ f_{i - 1} \end{bmatrix}$$

然后就可以愉快的写代码啦！

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lowbit(x) ((x)&-(x))
#define small priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>
using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void ll_cmax(ll &a,ll b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(int &a,int b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}
bool minuscule(char ch){return ch>='a' && ch<='z';}
bool number(char ch){return ch>='0' && ch<='9';}

const int MAXN=5;
ll n,mod,a1,a2,p,q;

namespace Matrix
{
	struct matrix{ll m[MAXN][MAXN];};
	int N=2;
	
	matrix operator *(matrix& a,matrix& b)
	{
		matrix c;
		memset(c.m,0,sizeof(c.m));
		for(int i=1;i<=N;i++) for(int j=1;j<=N;j++)
		for(int k=1;k<=N;k++)
		{
			c.m[i][j]=(c.m[i][j]+a.m[i][k]*b.m[k][j]);
		}
		return c;
	}
	
	matrix matrix_pow(matrix a,ll k)
	{
		matrix ans;
		memset(ans.m,0,sizeof(ans.m));
		ans.m[1][1]=a2,ans.m[1][2]=a1;
		while(k)
		{
			if(k&1) ans=ans*a;
			k>>=1;
			a=a*a;
		}
		return ans;
	}
} 

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	// cin>>p>>q>>a1>>a2>>n>>mod;
    cin>>a1>>a2;
    p=1,q=1;n=3;
	if(n==1) return cout<<a1<<endl,0;
	if(n==2) return cout<<a2<<endl,0;
	Matrix::matrix ans;
	ans.m[1][1]=p,ans.m[1][2]=1,ans.m[2][1]=q;
	ans=Matrix::matrix_pow(ans,n-2);
	cout<<ans.m[1][1]<<endl;
	return 0;
}
```

---

## 作者：__CrossBow_EXE__ (赞：7)

# 前言

考虑把题目转化为图上问题：相当于三个节点（记作 $1,2,3$），连一条从 $1$ 至 $2$，权值为 $a$ 的边；以及一条从 $2$ 至 $3$，权值为 $b$ 的边。答案就是从 $1$ 到 $3$ 的最短路。

我们发现边的数量和点的数量很少，考虑 Floyd。时间复杂度为 $O(n^3)$，时间还是卡得很死的。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
int a,b;
int G[5005][5005];//邻接矩阵存图
signed main(int argc,char *argv[]){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(NULL);
	cin.tie(0),cout.tie(0);
	cin>>a>>b;
	//初始化为极大值 
	for(int i=1;i<=5000;i++){
		for(int j=1;j<=5000;j++){
			G[i][j]=2147483647;
		} 
	}
	G[1][2]=a;//建边 
	G[2][3]=b;
	//Floyd
	for(int k=1;k<=3;k++){
		for(int i=1;i<=3;i++){
			for(int j=1;j<=3;j++){
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);//松弛 
			}
		}
	}
	cout<<G[1][3]<<endl;//直接输出最短路 
	return 0;
}
/*
---INFORMATIONS---
TIME:2025/5/10 14:10:44
PROBLEM:P1001
CODE BY __CrossBow_EXE__ Luogu uid967841
*/
```

---

## 作者：Red_Dawn (赞：7)

一看到加法即可想到公差为 $1$ 等差数列求和。

设 $a$ 为末项，则：
$$(1 + a) \times (a \div 2) = 1+2+3+...+a$$

那么 $a + b$ 为末项为：
$$(1 + (a+b)) \times ((a+b) \div 2)$$

求 $a + b$ 用
$$(1 + (a+b)) \times ((a+b) \div 2)-(1 + (a+b-1)) \times ((a+b-1) \div 2)$$

即可。

# code：
```
#include <bits/stdc++.h>
using namespace std;
double a, b; // int会错

double f(double s) {
	return (1 + s) * (s / 2);
}

int main() {
	cin >> a >> b;
	cout << int(f(f(a + b) - f((f(f(a + b) - f(a + b - 1)) - f(a + b - 1)) - 1)) - f(a + b - 1)); // 理论上来说这里叠多少层都可以
	return 0;
}
```

---

## 作者：LEWISAK (赞：6)

注意到可以将问题简化为在这样一颗树上（1 号点点权为 0）：

![](https://cdn.luogu.com.cn/upload/image_hosting/l48hba9z.png)

求 $2\to 3$ 上的点点权和，也就是 $2\to lca$ 上的点点权和加 $3\to lca$ 上的点点权和。

读过[这篇论文](https://www.luogu.com.cn/article/doc6k1mz)后我们可以学到一种 $O(\log^2n)$ 的求 lca 方法，稍加变通即可实现。

（此题数据较水，代码可能有误）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500500],b[500500];
int num,r,dep[500500],siz[500500],w[500500],son[500500],fa[500500],n,m,tot,head[500500],id[500500],top[500500],dis[500500],in[500500],out[500500],p[500500],cnt,outt;
struct tudouwoshinidefensininengrangwochidiaonimama{
	int to,nxt;
}e[1000500];
struct zxpshizxchexpdejiehetisuoyiwodezxcchixp{
	int l,r,min,mx;
}tree[2000500];
inline void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return;
}
inline void dfs1(int x,int f){
	in[x]=++cnt;
	p[x]=cnt;
	fa[x]=f;
	siz[x]=1;
	dep[x]=dep[f]+1;
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dis[v]=dis[x]+a[v];
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]){
			son[x]=v;
		}
	}
	out[x]=cnt;
	return;
}
inline void dfs2(int x,int topp){
	top[x]=topp;
	id[x]=++num;
	b[num]=a[x];
	if(!son[x]){
		return;
	}
	dfs2(son[x],topp);
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[x]||v==son[x]){
			continue;
		}
		dfs2(v,v);
	}
	return;
}
#define ls (id<<1)
#define rs (id<<1|1)
#define mid (tree[id].l+tree[id].r)/2
#define up\
	tree[id].min=min(tree[ls].min,tree[rs].min);\
	if(tree[id].min==tree[ls].min) tree[id].mx=tree[ls].mx;\
	else if(tree[id].min==tree[rs].min) tree[id].mx=tree[rs].mx;
inline void build(int l,int r,int id){
//	cout<<l<<' '<<r<<'\n';
	tree[id].l=l;tree[id].r=r;
	if(l==r){
		tree[id].mx=p[l];
		tree[id].min=dep[l];
		return;
	}
	build(l,mid,ls);
	build(mid+1,r,rs);
	up;
	return;
}
inline int sum(int l,int r,int id){
	if(tree[id].l>=l&&tree[id].r<=r){
		return tree[id].min;
	}
	int ans=1e18;
	if(l<=mid){
		int t=sum(l,r,ls);
		if(t<ans){
			ans=t;
			outt=tree[ls].mx;
		}
	}
	if(r>mid){
		int t=sum(l,r,rs);
		if(t<ans){
			ans=t;
			outt=tree[rs].mx;
		}
	}
	return ans;
}
signed main(){
//	cin.tie(0);cout.tie(0);
//	ios::sync_with_stdio(0);
	int aa,b;
	cin>>aa>>b;
	a[2]=aa;a[3]=b;
	add(1,2);add(1,3);
	dfs1(1,0);
	dfs2(1,1);
	build(in[1],out[1],1);
	sum(in[1],out[1],1);
	cout<<dis[2]+dis[3]-2*dis[outt];
}
```

---

## 作者：W_C_B_H (赞：6)

Update 2025.05.10：建议看看我的小号 @Wesley_Lin 给这道题写的[题解](https://www.luogu.com.cn/article/lcfloli5)，小作坊下料更猛。

你将看到一种使用 SPFA 求 $n$ 个整数之和的算法。

我们可以建立一张有向图，其中包含 $n+1$ 个节点（编号为 $0\sim n$）和 $n$ 条边，第 $i$ 条（$1\le i\le n$）边从节点 $i-1$ 指向节点 $i$，边权为 $a_i$。注意到此时节点 $0$ 到节点 $n$ 的最短路径长度即为 $\sum_{i=1}^na_i$，也就是所有 $a_i$ 的和。

这种情况下，我们只需令 $n=2$，将输入的两个数记作 $a_1,a_2$，按照上面的方法建立有向图，并使用 SPFA 算法求出最短路径长度并输出即可。

Code：

```cpp
// 该程序可以使用 SPFA 求出 n 个数的和 
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define pii pair<int,int>
#define prq priority_queue
#define fi first
#define se second
#define ctn continue
const int llinf=0x3f3f3f3f3f3f3f3f;
#define N 1000005
int n,a[N],dis[N];
vector<pii>e[N];	// 邻接表存边, first 表示到达的点, second 表示边权 
queue<int>q;
signed main()
{
	dis[0]=0;	// 初始化, 将起点的最短路长度设为 0 
	n=2;	// 本题中只有两个数 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dis[i]=llinf;	// 初始化最短路长度 
		e[i-1].pb({i,a[i]});	// 建边 
	}
	// SPFA
	q.push(0);
	while(!q.empty())
	{
		int u=q.front(), d=dis[u];
		q.pop();
		for(pii i:e[u])
		{
			int v=i.fi, w=i.se;
			if(dis[v]>d+w)
			{
				dis[v]=d+w;
				q.push(v);
			}
		}
	}
	cout<<dis[n];
	return 0;
}
```

---

## 作者：liuzhongrui (赞：6)

## 思路：

动态树板题，这里使用比较强的 SATT 解决。

设两个节点，一个点权为 $A$，一个点权为 $B$，则路径权值和即为 $A+B$。

## 代码:

```c++
#include <iostream>
#define ls(x) T[x][0]
#define rs(x) T[x][1]
#define ms(x) T[x][2]
using namespace std;
const int MAXN = 300005;
int T[MAXN][3], s[MAXN][2], tot, v[MAXN], r[MAXN], top, st[MAXN], f[MAXN];
int nnd() {
	if (top) {
		top--;
		return st[top + 1];
	}
	return ++tot;
}
bool isr(int x) {
	return rs(f[x]) != x && ls(f[x]) != x;
}
bool dir(int x) {
	return rs(f[x]) == x;
}
void psu(int x, int ty) {
	if (ty) {
		s[x][1] = s[ls(x)][1] + s[rs(x)][1] + s[ms(x)][1];
		return;
	}
	s[x][0] = s[ls(x)][0] + v[x] + s[rs(x)][0];
	s[x][1] = s[ls(x)][1] + s[ms(x)][1] + s[rs(x)][1] + v[x];
}
void psr(int x) {
	if (!x) return;
	r[x] ^= 1;
	swap(ls(x), rs(x));
}
void psd(int x, int ty) {
	if (ty) return;
	if (r[x]) {
		psr(ls(x));
		psr(rs(x));
		r[x] = 0;
	}
}
void upd(int x, int ty) {
	if (!isr(x)) upd(f[x], ty);
	psd(x, ty);
}
void stf(int x, int fa, int ty) {
	if (x) f[x] = fa;
	T[fa][ty] = x;
}
void rtt(int x, int ty) {
	int y = f[x], z = f[y], d = dir(x), w = T[x][d ^ 1];
	if (z) T[z][ms(z) == y ? 2 : dir(y)] = x;
	T[x][d ^ 1] = y;
	T[y][d] = w;
	if (w) f[w] = y;
	f[y] = x;
	f[x] = z;
	psu(y, ty);
	psu(x, ty);
}
void spy(int x, int ty, int gl = 0) {
	upd(x, ty);
	for (int y; y = f[x], (!isr(x)) && y != gl; rtt(x, ty)) {
		if (f[y] != gl && (!isr(y))) rtt(dir(x) ^ dir(y) ? x : y, ty);
	}
}
void cle(int x) {
	ls(x) = ms(x) = rs(x) = s[x][0] = s[x][1] = r[x] = v[x] = 0;
	st[++top] = x;
}
void del(int x) {
	stf(ms(x), f[x], 1);
	if (ls(x)) {
		int p = ls(x);
		psd(p, 1);
		while (rs(p)) p = rs(p), psd(p, 1);
		spy(p, 1, x);
		stf(rs(x), p, 1);
		stf(p, f[x], 2);
		psu(p, 1);
		psu(f[x], 0);
	} else
		stf(rs(x), f[x], 2);
	cle(x);
}
void spl(int x) {
	spy(x, 1);
	int y = f[x];
	spy(y, 0);
	psd(x, 1);
	if (rs(y)) {
		swap(f[ms(x)], f[rs(y)]);
		swap(ms(x), rs(y));
		psu(x, 1);
	} else
		del(x);
	psu(rs(y), 0);
	psu(y, 0);
}
void acs(int x) {
	spy(x, 0);
	int ys = x;
	if (rs(x)) {
		int y = nnd();
		stf(ms(x), y, 0);
		stf(rs(x), y, 2);
		rs(x) = 0;
		stf(y, x, 2);
		psu(y, 1);
		psu(x, 0);
	}
	while (f[x]) {
		spl(f[x]);
		x = f[x];
	}
	spy(ys, 0);
}
int fdr(int x) {
	acs(x);
	psd(x, 0);
	while (ls(x)) x = ls(x), psd(x, 0);
	spy(x, 0);
	return x;
}
void mkr(int x) {
	acs(x);
	psr(x);
}
void epo(int x, int y) {
	mkr(x);
	acs(y);
}
void lnk(int x, int y) {
	if (fdr(x) == fdr(y)) return;
	acs(x);
	mkr(y);
	stf(y, x, 1);
	psu(x, 0);
	psu(y, 0);
}
void cu(int x, int y) {
	epo(x, y);
	if (ls(y) != x || rs(x)) return;
	f[x] = ls(y) = 0;
	psu(y, 0);
}
int main() {
	tot = 2;
	cin >> v[1] >> v[2];
	psu(1, 0);
	psu(2, 0);
	lnk(1, 2);
	epo(1, 2);
	cout << s[2][0];
	return 0;
}


```

---

## 作者：Vct14 (赞：6)

题意：给定一个 $3$ 个点的图，其中连接点 $1,2$ 的边的边权为 $a$，连接点 $2,3$ 的边的边权为 $b$，连接点 $1,3$ 的边的边权为 $2^{31}-1$，求该图的最小生成树。

最小生成树（最小代价生成树）是指一个有 $n$ 个结点的连通图的有着所有 $n$ 个点、最少边和最小代价的子图。

Kruskal 算法（克鲁斯卡尔算法）是一种用来查找最小生成树的贪心算法，适用于稀疏图。核心知识点为并查集。

设边数为 $E$，则它的时间复杂度为 $O(E \log E)$。

### 怎样存边

我们可以使用一个结构体，存下一条边连接的两个点及距离。

### 怎样判断是否连通

这里需要运用并查集，最开始时，每一个点都为一个连通分量。若节点 $u$ 和节点 $v$ 间有一条边，则把节点 $u$ 所在的集合与节点 $v$ 所在的集合合并。

最终只剩下 $1$ 个连通分量时，则此图连通。

当然，因为使一个 $n$ 个点的图连通的最少边数（最小生成树边数）为 $n-1$（如图 $1-1$），所以也可以在已经取了 $n-1$ 条边时结束。

![](https://cdn.luogu.com.cn/upload/image_hosting/gx78dqx5.png)

如图，当点数为 $6$，边数为 $5$ 时，可以连通。

### 怎样选边

既然有 $m$ 条边，但我们只需要选择 $n-1$ 条边，那么如何选择呢？

因为每条边有不同的长度，而题目要求求最短的长度，所以我们可以将所有边按长度从小到大排序。

然后，我们可以依次遍历每一条边：

若这两个点不在同一个集合内（不连通），则可以选择这一条边。我们让总长度加上这一条边的距离，边的数量加 $1$，再将两个点所在的集合合并。

当有边数 $p=n-1$ 时，我们可以直接输出距离，并使用 `return 0` 结束程序。

给一组数据帮助理解：[Link](https://www.luogu.com.cn/paste/8zf5z1xm)。

由此可以建出下图。（右边为排序后的结果）

![](https://cdn.luogu.com.cn/upload/image_hosting/he5rdzte.png)

---



使用 Kruskal 算法解决即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5002,M=2e5+2;
int fa[N];

struct Edg{
	int x,y,z;
}edge[M];

void add(int u,int v,int w,int i){
	edge[i].x=u;
	edge[i].y=v;
	edge[i].z=w;
}

bool cmp(Edg a,Edg b){
	return a.z<b.z;
}

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

int main(){
	int n=3,m=2;
	for(int i=1; i<=n; i++) fa[i]=i;
    int a,b;cin>>a>>b;
	add(1,2,a,1);add(2,3,b,2);add(1,3,2147483647,3);
	int sum=0,s=0;
	sort(edge+1,edge+m+1,cmp);
	for(int i=1; i<=m; i++){
		int x=edge[i].x,y=edge[i].y,z=edge[i].z;
		if(find(x)==find(y)) continue;
		fa[find(x)]=y;
		sum+=z;s++;
		if(s==n-1){
			cout<<sum;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：呼吸之野 (赞：6)

本题需要维护单点加，查询单点求和。

我们考虑用线段树维护，对 $a$ 建树，然后单点加上 $b$，最后查询区间和即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
struct segtree{
	int l,r;
	ll lazy,sum;
}tree[10];
ll n,m,a[10];
inline int lchild(int id){
	return id<<1;
}
inline int rchild(int id){
	return id<<1|1;
}
void pushdown(int id){
	if(tree[id].lazy){
		tree[lchild(id)].sum += tree[id].lazy*(tree[lchild(id)].r-tree[lchild(id)].l+1);
		tree[rchild(id)].sum += tree[id].lazy*(tree[rchild(id)].r-tree[rchild(id)].l+1);
		tree[lchild(id)].lazy += tree[id].lazy;
		tree[rchild(id)].lazy += tree[id].lazy;  
		tree[id].lazy = 0;
	}
	return ;
}
void pushup(int id){
	tree[id].sum = tree[lchild(id)].sum + tree[rchild(id)].sum;
	return ;
}
void build(int id,int lnow,int rnow){
	tree[id].l = lnow; tree[id].r = rnow;
	if(lnow == rnow){
		tree[id].sum = a[lnow];
		return ;
	}
	int mid = (lnow+rnow)>>1;
	build(lchild(id),lnow,mid);
	build(rchild(id),mid+1,rnow);
	pushup(id);
	return ;
}
ll query(int l,int r,int id){
	if(tree[id].l >= l && tree[id].r <= r) return tree[id].sum;
	pushdown(id);
	int mid = (tree[id].l+tree[id].r)>>1;
	ll sum = 0;
	if(l <= mid) sum += query(l,r,lchild(id));
	if(r >= mid+1) sum += query(l,r,rchild(id));
	return sum;
}
void update(int l,int r,int id,int k){
	if(tree[id].l >= l && tree[id].r <= r){
		tree[id].lazy += k;
		tree[id].sum += (tree[id].r-tree[id].l+1)*k;
		return ;
	}
	pushdown(id);
	int mid = (tree[id].l+tree[id].r)>>1;
	if(l <= mid) update(l,r,lchild(id),k);
	if(r >= mid+1) update(l,r,rchild(id),k);
	pushup(id);
	return ;
}
signed main(){
	cin>>a[1]>>m;
	build(1,1,1);
	update(1,1,1,m);
	cout<<query(1,1,1);
	return 0;
} 
```

---

## 作者：DHT666 (赞：6)

## 题意
给定 $a$ 和 $b$，求 $a+b$ 的值。

## 思路
这道题用回滚莫队做。

注意到回滚莫队的板题：[历史研究](https://www.luogu.com.cn/problem/AT_joisc2014_c)，于是考虑套模板。

历史研究这道题是让你求一段区间的数和数出现次数乘积的最大值，所以这道题就是求长度为 $1$ 的区间，$a+b$ 出现的次数和 $a+b$ 的乘积，容易想到让 $a+b$ 出现一次即可，这样的答案就是 $1 \times (a+b) = a+b$，也就解决了这个问题。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long ll;

const ll N = 2;

struct node {
	ll l, r, id;
} b[N], c[N];

ll n, m, idx;
ll a[N], d[N];
ll cq[N], te[N];
ll id[N], st[N], ed[N], bsiz;
ll res = -2e9, w[N];
ll o[N], p[N];
ll f[N], idy;

// 莫队排序
bool cmp(node x, node y) {
	if(id[x.l] == id[y.l]) return x.r < y.r;
	return id[x.l] < id[y.l];
}

// 加入一个点
void add(ll x, ll type) {
	x = cq[x];
	if(type == 0) {
		p[x]++;
		res = res < te[x] * p[x] ? te[x] * p[x] : res;
	} else {
		if(idy == 0) f[++idy] = res;
		f[++idy] = x;
		p[x]++;
		res = res < te[x] * p[x] ? te[x] * p[x] : res;
	}
}

int main() {
	ll A, B;
	scanf("%lld%lld", &A, &B);
	
	n = 1, m = 1; // 数列长度和询问次数
	a[1] = A + B; // 数列
	c[1].l = c[1].r = 1; // 区间范围
	c[1].id = 1; // 询问编号
	
	// 下为历史研究代码
	
	// 离散化
	d[1] = a[1];
	sort(d + 1, d + 1 + n);
	
	for(int i = 1; i <= n; i++) {
		cq[i] = lower_bound(d + 1, d + 1 + n, a[i]) - d;
		te[cq[i]] = a[i];
	}
	
	// 分块
	bsiz = sqrt(n);
	for(ll i = 1; i <= n; i++) {
		id[i] = (i - 1) / bsiz + 1;
	}
	for(ll i = 1, j = 1; j <= n; i++, j += bsiz) {
		st[i] = j;
		ed[i] = min(j + bsiz - 1, n);
	}
	
	// 回滚莫队
	for(ll i = 1; i <= m; i++) {
		if(id[c[i].l] == id[c[i].r]) {
			ll q = -2e9;
			for(ll j = c[i].l; j <= c[i].r; j++) {
				o[cq[j]]++;
				q = max(q, o[cq[j]] * a[j]);
			}
			w[c[i].id] = q;
			for(ll j = c[i].l; j <= c[i].r; j++) o[cq[j]] = 0;
		} else b[++idx] = c[i];
	}
	
	sort(b + 1, b + 1 + idx, cmp);
	
	ll l = 0, r = 0, tl = 0;
	for(ll i = 1; i <= idx; i++) {
		if(i == 1 || id[b[i].l] != id[b[i - 1].l]) {
			for(int j = 1; j <= n; j++) p[j] = 0;
			res = -2e9;
			l = r = ed[id[b[i].l]] + 1;
			tl = l;
			add(l, 0);
		}
		while(r < b[i].r) add(++r, 0);
		while(l > b[i].l) add(--l, 1);
		w[b[i].id] = res;
		if(idy) {
			for(int i = 2; i <= idy; i++) {
				p[f[i]]--;
			}
			res = f[1];
			idy = 0, l = tl;
		}
	}
	
	for(ll i = 1; i <= m; i++) {
		printf("%lld\n", w[i]);
	}
	
	return 0;
}
```

---

## 作者：_smart_stupid_ (赞：6)

如果不感兴趣，可以直接提交这一行代码：

```python
print(sum((map(int,input().split())))
```

接下来使用线段树算法解决这个问题。

将问题建模为区间加，区间查询，那么本题简化为：先在区间 $[1,1]$ 每个数字加上一个数，再在区间 $[2,2]$ 每个数字加上一个数，并查询区间 $[1,2]$ 的和。

但是我们发现这样是不够简化的，所以还要加上区间乘法。

我们将操作看作：区间 $[1,2]$ 全部加上 $1$，然后区间 $[1,1]$ 乘上一个数，区间 $[2,2]$ 乘上一个数，最后输出答案。

但是我们发现逆元没有出现，那么继续简化为题为区间 $[1,100000]$ 区间加上 $1$，然后区间 $[1,50000]$ 乘上一个数，区间 $[50001,100000]$ 乘上一个数，最后输出区间 $[1,100000]$ 的和除以 $50000$ 在模 $10000000000037$ 意义下的答案。

而这个时候我们知道上面那一坨数是一个质数，由 NotDeep 小定理可得在模 $p$ 意义下除以 $x$ 等于乘上 $x^{p - 2}$。

要注意要开 `__int128`。

## AC Code：

```cpp
#include <iostream>
#include <queue>
using namespace std;
__int128 n, q, mod = 10000000000037;
struct node{
	__int128 l, r, sum, tag_p, tag_m;
};
node t[800100];
void update(int p) {
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
	t[p].sum %= mod;
}
void push_tag(__int128 p) {
	t[p * 2].sum = (t[p * 2].sum * t[p].tag_m + t[p].tag_p * (t[p * 2].r - t[p * 2].l + 1)) % mod;
	t[p * 2 + 1].sum = (t[p * 2 + 1].sum * t[p].tag_m + t[p].tag_p * (t[p * 2 + 1].r - t[p * 2 + 1].l + 1)) % mod;
	t[p * 2].tag_m = (t[p * 2].tag_m * t[p].tag_m) % mod;
	t[p * 2 + 1].tag_m = (t[p * 2 + 1].tag_m * t[p].tag_m) % mod;
	t[p * 2].tag_p = (t[p * 2].tag_p * t[p].tag_m + t[p].tag_p) % mod;
	t[p * 2 + 1].tag_p = (t[p * 2 + 1].tag_p * t[p].tag_m + t[p].tag_p) % mod;
	t[p].tag_p = 0;
	t[p].tag_m = 1;
}

void make_tree(__int128 l, __int128 r, __int128 p) {
	t[p].l = l;
	t[p].r = r;
	t[p].tag_p = 0, t[p].tag_m = 1;
	if (l < r) {
		make_tree(l, (l + r) / 2, p * 2);
		make_tree((l + r) / 2 + 1, r, p * 2 + 1);
	}
}
void add(__int128 l, __int128 r, __int128 p, __int128 x) {
	if (l > t[p].r || r < t[p].l) return;
	push_tag(p);
	if (l <= t[p].l && t[p].r <= r) {
		t[p].tag_p += x;
		t[p].tag_p %= mod;
		t[p].sum = (t[p].sum + t[p].tag_p * (t[p].r - t[p].l + 1) % mod) % mod;
		return;
	}
	add(l, r, p * 2, x);
	add(l, r, p * 2 + 1, x);
	update(p);
}
void mul(__int128 l, __int128 r, __int128 p, __int128 x) {
	if (l > t[p].r || r < t[p].l) return;
	push_tag(p);
	if (l <= t[p].l && t[p].r <= r) {
		t[p].tag_p *= x;
		t[p].tag_p %= mod;
		t[p].tag_m *= x;
		t[p].tag_m %= mod;
		t[p].sum = (t[p].sum * t[p].tag_m) % mod;
		return;
	}
	mul(l, r, p * 2, x);
	mul(l, r, p * 2 + 1, x);
	update(p);
}
__int128 get(__int128 l, __int128 r, __int128 p) {
	if (l > t[p].r || r < t[p].l) return 0;
	push_tag(p);
	if (l <= t[p].l && t[p].r <= r) {
		return t[p].sum;
	}
	return (get(l, r, p * 2) + get(l, r, p * 2 + 1)) % mod;
}
__int128 fpow(__int128 a, long long b) {
	__int128 ans = 1;
	while (b) {
		if (b & 1) ans = (ans * a) % mod;
		a = a * a % mod, b >>= 1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	long long a, b;
	cin >> a >> b;
	int n = 100000;
	make_tree(1, n, 1);
	add(1, n, 1, 1);
	mul(1, n / 2, 1, a);
	mul(n / 2 + 1, n, 1, b);
	__int128 ans = get(1, 100000, 1);
	ans *= fpow(n / 2, mod - 2);
	ans %= mod;
	cout << (long long)ans << '\n';
	return 0;
}
```

---

## 作者：Dream_poetry (赞：6)

### 思路：

首先这是一篇非正常题解。

我们将两个数视作并联电路两个支路上允许通过的最大电流。

我们的目标视为干路电流最大可能值。

我们惊喜地发现，这不是网络流裸题吗？

详见：[P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376)。

于是我们就快乐的通过了此题。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
struct node{
	int nex,to;
	int val;
}e[5000005];
int he[1000005];
int tot=1;
int now[1000005];
int s,t;
const int inf=1e12;

inline void add(int x,int y,int w){
	e[++tot].nex=he[x];
	e[tot].to=y;
	e[tot].val=w;
	he[x]=tot;
}
int dis[5000005];
inline int bfs(){
	for (int i=1;i<=2;i++){
		dis[i]=inf;
	}
	queue<int>q;
	q.push(s);
	dis[s]=0;
	now[s]=he[s];
	while (q.size()){
		int x=q.front();
		q.pop();
		for (int i=he[x];i;i=e[i].nex){
			int v=e[i].to;
			int w=e[i].val;
			if (w && dis[v]==inf){
				q.push(v);
				dis[v]=dis[x]+1;
				now[v]=he[v];
				if (v==t){
					return 1;
				}
			}
		}
	}
	return 0;
}

inline int dfs(int x,int sum){
	if (x==t){
		return sum; 
	}
	int res=0;
	for (int i=now[x];i && sum;i=e[i].nex){
		now[x]=i;
		int v=e[i].to;
		int w=e[i].val;
		if (w && dis[v]==dis[x]+1){
			int k=dfs(v,min(sum,w));
			if (k==0){
				dis[v]=inf;
			} 
			e[i].val-=k;
			e[i^1].val+=k;
			sum-=k;
			res+=k; 
		}
	}
	return res;
}
int ans;

signed main(){
	int a,b;
	cin>>a>>b;
	s=1;
	t=2;
	add(s,t,a);
	add(t,s,0);
	add(s,t,b);
	add(t,s,0);
	while (bfs()){
		ans+=dfs(s,inf);
	}
	cout<<ans;
	
	return 0;
}
```

---

## 作者：aaa1145141919810 (赞：6)

看见楼上楼下各路神仙对轰，小蒟蒻认为自己还是太弱了，不会什么太高深的算法，所以写个二维前缀和吧（主要是会的都被写完了）

我们来观察下面这张图：

![并不好看的图](https://cdn.luogu.com.cn/upload/image_hosting/bpbsid4s.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

通过输入数据构造如上的矩形，我们需要的答案就是红框部分矩形的值的和。这就是二维前缀和的[模板题](https://www.bilibili.com/video/BV1GJ411x7h7/)了。话不多说，上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 5;
LL a, b, sum[N][N], t[N][N];

inline LL read()
{
	LL w = 0, t = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')t = -1;ch = getchar();}
	while('0' <= ch && ch <= '9')w = w*10+(ch&15),ch = getchar();
	return w*t;
}

int main()
{
	a = read(), b = read();
	for(int i = 1; i <= 2; i++)
		for(int j = 1; j <= 2; j++)
		{
			if(i == 1)t[i][j] = a;
			else t[i][j] = b;
			sum[i][j] = sum[i-1][j]+sum[i][j-1] - sum[i-1][j-1] + t[i][j];
		}
	printf("%lld\n", sum[2][2]-sum[2][1]);
	
	return 0;
}
```

---

## 作者：zhoujunchen (赞：6)

方法一：

直接模拟，输入两个变量，输出他们的和。




```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int a,b;
    cin >> a >> b;
    cout << a+b;
    return 0;
}
```


方法二：

线段树，将两个数视为一个长度为 $2$ 的区间，进行区间修改操作。




```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls x<<1
#define rs x<<1|1
int n,m,a[100005],tree[400005],tag[400005];
void build(int x,int l,int r){
	if(l==r)return tree[x]=a[l],void();
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	tree[x]=tree[ls]+tree[rs];
}
void addtag(int x,int l,int r,int k){
	tag[x]+=k,tree[x]+=k*(r-l+1);
}
void push_down(int x,int l,int r){
	if(tag[x]){
		int mid=l+r>>1;
		addtag(ls,l,mid,tag[x]),addtag(rs,mid+1,r,tag[x]);
		tag[x]=0;
	}
}
void update(int x,int l,int r,int L,int R,int d){
	if(L<=l&&r<=R)return addtag(x,l,r,d),void();
	int mid=l+r>>1;
	push_down(x,l,r);
	if(L<=mid)update(ls,l,mid,L,R,d);
	if(mid<R)update(rs,mid+1,r,L,R,d);
	tree[x]=tree[ls]+tree[rs];
}
int query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return tree[x];
	int mid=l+r>>1,res=0;
	push_down(x,l,r);
	if(L<=mid)res+=query(ls,l,mid,L,R);
	if(mid<R)res+=query(rs,mid+1,r,L,R);
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	n=2;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	cout<<query(1,1,n,1,2);
	return 0;
}
```

[更多解法。](https://www.acwing.com/solution/content/69403/)

---

## 作者：justalearner (赞：5)

线性规划好题。

题目要求我们算 $A+B$，可以构造一个线性规划问题：
$$
\operatorname{maximize} x_1+x_2\\
s.t.
\left\{
\begin{aligned}
x_1\le A\\
x_2\le B
\end{aligned}
\right.
$$

答案即为 $A+B$。

当然这道题 $A$ 和 $B$ 可以是负的。所以可以给 $A$ 和 $B$ 分别加上一个 $1\times 10^9$，最后答案减去 $2\times 10^9$ 即可。

线性规划具体实现方式参见 [OI-wiki](https://oi-wiki.org/math/simplex/)。

参考代码：
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=25;
const double eps=1e-8,INF=1e15;
inline int read(){
	char c=getchar();int x=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0'; c=getchar();}
	return x*f;
}
int n,m,type;
double a[N][N],ans[N];
int id[N<<1];
int q[N];
void Pivot(int l,int e){
	swap(id[n+l],id[e]);
	double t=a[l][e]; a[l][e]=1;
	for(int j=0;j<=n;j++) a[l][j]/=t;
	for(int i=0;i<=m;i++) if(i!=l && abs(a[i][e])>eps){
		t=a[i][e]; a[i][e]=0;
		for(int j=0;j<=n;j++) a[i][j]-=a[l][j]*t;
	}
}
bool init(){
	while(true){
		int e=0,l=0;
		for(int i=1;i<=m;i++) if(a[i][0]<-eps && (!l||(rand()&1))) l=i;
		if(!l) break;
		for(int j=1;j<=n;j++) if(a[l][j]<-eps && (!e||(rand()&1))) e=j;
		if(!e) {puts("Infeasible");return false;}
		Pivot(l,e);
	}
	return true;
}
bool simplex(){
	while(true){
		int l=0,e=0; double mn=INF;
		for(int j=1;j<=n;j++)
			if(a[0][j]>eps) {e=j;break;}
		if(!e) break;
		for(int i=1;i<=m;i++) if(a[i][e]>eps && a[i][0]/a[i][e]<mn)
			mn=a[i][0]/a[i][e],l=i;
		if(!l) {puts("Unbounded");return false;}
		Pivot(l,e);
	}
	return true;
}
int main(){
	srand(317);
	n=2,m=2;
	int A=read()+1E9,B=read()+1E9;
	a[0][1]=1,a[0][2]=1;
	a[1][0]=A,a[1][1]=1,a[1][2]=0;
	a[2][0]=B,a[2][1]=0,a[2][2]=1;
	for(int i=1;i<=n;i++) id[i]=i;
	if(init() && simplex()){
		printf("%.0lf\n",-a[0][0]-2E9);
	}
	else exit(-1);
}
```

---

## 作者：OIer6666 (赞：5)

提示：本题解不是正常写法，萌新勿看！

正解：
```cpp
#include<iostream>
using namespace std;
int main(){
    int a,b;cin>>a>>b;
    cout<<a+b<<"\n";
    return 0;
}
```
---
## ~~正式~~整活内容

不多废话，上代码。

1. 高精度树状数组变式

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 2e5 + 5;
int C[MAXN], m;
unsigned t;
string a, b;
int lowbit(int k) {
	return k & -k;
}
void add(int x, int k) {
	while (x <= 1145) {
		C[x] += k;
		x += lowbit(x);
	}
}
int solve(int a, int b) {
	--a;
	int suma, sumb;
	suma = sumb = 0;
	while (a) {
		suma += C[a];
		a -= lowbit(a);
	}
	while (b) {
		sumb += C[b];
		b -= lowbit(b);
	}
	return sumb - suma;
}
struct node {
	int x, y;
	bool operator < (node b) {
		if (x == b.x)
			return y < b.y;
		return x < b.x;
	}
} s[MAXN];
string VERY_EASY_PLUS(string a, string b) {
	string ans;
	for (int i = 0; i < a.size(); i++) {
		add(i + 1, a[i] - '0');
		if (solve(i + 1, i + 1) >= 10) {
			add(i + 2, 1);
			add(i + 1, -10);
		}
	}
	for (int i = 0; i < b.size(); i++) {
		add(i + 1, b[i] - '0');
		if (solve(i + 1, i + 1) >= 10) {
			add(i + 2, 1);
			add(i + 1, -10);
		}
	}//求和
	bool can = 0;
	for (int i = max(a.size(), b.size()) + 1; i; i--) {
		if (can || solve(i, i))
			ans.push_back(solve(i, i) + '0'), can = 1;
	}//转换
	return ans;
}
int CHANGE(string chen_zhe) {
	unsigned manba = (24, 0);
	for (auto i : chen_zhe) {
		manba = manba * 10 + i - '0';
	}
	return (int)manba;//转换
}
int main() {
	ios::sync_with_stdio(false);
	cin >> t;
	while (t) {
		a.push_back(t % 10 + '0');
		t /= 10;
	}
	cin >> t;
	while (t) {
		b.push_back(t % 10 + '0');
		t /= 10;
	}
	cout << CHANGE(VERY_EASY_PLUS(a, b));
	return 0;
}
```

2. 最短路变式

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<utility>
#include<cstring>
using namespace std;
#define N 100005
struct BI {
	int to, ne, v;
};
int h[N] = {0}, cnt;
BI e[2 * N];
void add(int a, int b, int v) {
	e[++cnt] = {b, h[a], v};
	h[a] = cnt;
}
struct CMP_pii {
	bool operator()(const pair<int, unsigned> &n1, const pair<int, unsigned> &n2)const {
		if (n1.second == n2.second)
			return n1.first < n2.first;
		return n1.second < n2.second;
	}
};
unsigned dis[N];
void unDijkstra(int st) {
	memset(dis, 0xff, sizeof(dis));
	priority_queue<pair<int, unsigned>, vector<pair<int, unsigned> >, CMP_pii > pq;
	pq.push(make_pair(st, 0));
	while (pq.size()) {
		if (pq.top().second > dis[pq.top().first]) {
			pq.pop();
			continue;
		}
		pair<int, unsigned> top = pq.top();
		pq.pop();
		dis[top.first] = top.second;
		for (int i = h[top.first]; i; i = e[i].ne) {
			dis[e[i].to] = top.second * 10 + e[i].v, pq.push(make_pair(e[i].to, top.second * 10 + e[i].v));
		}
	}
}
int main() {
	unsigned a, b;
	cin >> a >> b;
	unsigned m = 0;
	for (int i = 1; i <= 11; i++) {
		unsigned t = a % 10 + b % 10 + m;
		m = t / 10;
		t %= 10;
		add(i + 1, i, t);
		a /= 10;
		b /= 10;
	}
	unDijkstra(11);
	cout << (int)dis[1];
	return 0;
}
```

---

## 作者：Gold14526 (赞：4)

注意到这道题需要把 $a$ 和 $b$ 加起来，这需要在 $a$ 和 $b$ 之间建立起联系，也就是一个 Link 的操作，故可以想到使用 Link-Cut Tree 维护。

Link-Cut Tree 目前还是 $10$ 级算法，甚至没有下放到 noi 考点，我认为这题是红题多少有点恶评了。

代码：

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int x=0,zf=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')zf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x*zf;
}
void print(cint x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cint x,const char ch)
{
	if(x<0)
	{
		putchar('-');
		print(-x);
		putchar(ch);
		return;
	}
	print(x);
	putchar(ch);
}
cint N=2;
int n;
int val[N+1];
namespace LCT{
	int f[N+1];
	struct noe{
		int son[2],sum;
		bool tag;
	}t[N+1];
	inline bool notroot(cint x)
	{
		return (t[f[x]].son[0]==x||t[f[x]].son[1]==x);
	}
	inline void rev(cint x)
	{
		swap(t[x].son[0],t[x].son[1]);
		t[x].tag^=1;
	}
	void push_up(cint p)
	{
		t[p].sum=t[t[p].son[0]].sum+t[t[p].son[1]].sum+val[p];
	}
	void push_down(cint p)
	{
		if(!t[p].tag)return;
		t[p].tag=0;
		rev(t[p].son[0]);
		rev(t[p].son[1]);
	}
	void rotate(cint x)
	{
		cint y=f[x],z=f[y],p=(t[y].son[1]==x),q=(t[z].son[1]==y),w=t[x].son[!p];
		if(notroot(y))
		{
			t[z].son[q]=x;
		}
		t[x].son[!p]=y;
		t[y].son[p]=w;
		if(w)
		{
			f[w]=y;
		}
		f[y]=x;
		f[x]=z;
		push_up(y);
	}
	void rotate2(cint x)
	{
		cint y=f[x],z=f[y];
		if(notroot(y))
		{
			rotate((t[y].son[0]==x)^(t[z].son[0]==y)?x:y);
		}
		rotate(x);
	}
	void push_all(cint x)
	{
		if(notroot(x))push_all(f[x]);
		push_down(x);
	}
	void splay(cint x)
	{
		push_all(x);
		while(notroot(x))
		{
			rotate2(x);
		}
		push_up(x);
	}
	void access(int x)
	{
		for(int y=0;x;y=x,x=f[x])
		{
			splay(x);
			t[x].son[1]=y;
			push_up(x);
		}
	}
	void make_root(cint x)
	{
		access(x);
		splay(x);
		rev(x);
	}
	int find_root(int x)
	{
		access(x);
		splay(x);
		while(t[x].son[0])
		{
			push_down(x);
			x=t[x].son[0];
		}
		splay(x);
		return x;
	}
	void split(cint x,cint y)
	{
		make_root(x);
		access(y);
		splay(y);
	}
	bool link(cint x,cint y)
	{
		make_root(x);
		if(find_root(y)==x)return 0;
		f[x]=y;
		return 1;
	}
}
using namespace LCT;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=2;
	val[1]=read();
	val[2]=read();
	link(1,2);
	split(1,2);
	princh(t[2].sum,'\n');
	return 0;
}

```

---

