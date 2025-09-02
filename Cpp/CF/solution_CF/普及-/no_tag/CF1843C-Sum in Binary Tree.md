# Sum in Binary Tree

## 题目描述

Vanya really likes math. One day when he was solving another math problem, he came up with an interesting tree. This tree is built as follows.

Initially, the tree has only one vertex with the number $ 1 $ — the root of the tree. Then, Vanya adds two children to it, assigning them consecutive numbers — $ 2 $ and $ 3 $ , respectively. After that, he will add children to the vertices in increasing order of their numbers, starting from $ 2 $ , assigning their children the minimum unused indices. As a result, Vanya will have an infinite tree with the root in the vertex $ 1 $ , where each vertex will have exactly two children, and the vertex numbers will be arranged sequentially by layers.

 ![](https://espresso.codeforces.com/3fe851b2505ce276dabd4a63ad7472346f98f9a8.png) Part of Vanya's tree.Vanya wondered what the sum of the vertex numbers on the path from the vertex with number $ 1 $ to the vertex with number $ n $ in such a tree is equal to. Since Vanya doesn't like counting, he asked you to help him find this sum.

## 说明/提示

In the first test case of example on the path from the root to the vertex $ 3 $ there are two vertices $ 1 $ and $ 3 $ , their sum equals $ 4 $ .

In the second test case of example on the path from the root to the vertex with number $ 10 $ there are vertices $ 1 $ , $ 2 $ , $ 5 $ , $ 10 $ , sum of their numbers equals $ 1+2+5+10 = 18 $ .

## 样例 #1

### 输入

```
6
3
10
37
1
10000000000000000
15```

### 输出

```
4
18
71
1
19999999999999980
26```

# 题解

## 作者：_O_v_O_ (赞：3)

### 简要题意：

给定一棵根结点为 $1$ 完全二叉树，编号为 $x$ 的节点的左儿子编号为 $x \times 2$，右儿子编号为 $x \times 2 + 1$。从编号为 $1$ 的结点到编号 $n$ 的结点的路径上的结点编号之和等于多少？

------------
### 思路：

其实不用二叉树来存储，直接从编号为 $n$ 的结点往上遍历即可，编号为 $x$ 的结点的父亲结点的编号就是 $x \div 2$。

------------
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //因数据原因，要开long long
int t;
signed main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int ans=0;   //开始往上遍历，ans代表路径上的结点编号和。
		while(n>=1){   //遍历到根节点后暂停。
			ans+=n;
			n/=2;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/113159203)

---

## 作者：Dream__Sky (赞：2)

题意简述：

在一棵完全二叉树上，从编号为 $1$ 的顶点到编号为 $n$ 的顶点的路径上的顶点编号之和等于多少。

分析：

如图![](https://cdn.luogu.com.cn/upload/image_hosting/8gdypxu3.png)

我们可以选择一个点来模拟。

例如 $n=13$，那么每一个顶点上的数是：$13 --> 6 --> 3 --> 1$。

我们发现每一项都是前一项除以二（向下取整）。

有了这个规律，代码就好写了：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n; 
signed main()
{
	cin>>T;//T组数据
	while(T--)
	{
		cin>>n;
		int sum=0;
		while(n)
		{
			sum+=n;
			n/=2;
		}//模拟除以二的过程，直到到了根节点，即n=1
		cout<<sum<<endl;
	}
	return 0;
}
 
```



---

## 作者：ran_qwq (赞：0)

给你一棵完全二叉树，$i$ 号节点的父亲为 $\lfloor\dfrac{i}{2}\rfloor$。求根节点 $1$ 走到 $n$ 的节点经过节点的编号和。

---
简单题。每次从 $n$ 往上跳到 $\lfloor\dfrac{n}{2}\rfloor$，求和即可。

```cpp
void solve()
{
	int n=read(),ans=0;
	while(n) ans+=n,n>>=1;write(ans,"\n");
}
```

---

## 作者：rainygame (赞：0)

~~感觉应该把它和 B 互换。~~

顶多评橙。

这道题的意思是给出一个有 $n$ 个结点的完全二叉树，求 $n$ 到 $1$ 的结点编号之和。

那么我们可以直接枚举呀，一个结点 $v$ 的父节点编号为 $\lfloor \frac{v}{2}\rfloor$。

设：

$$
f(x)=\begin{cases}
1,&x=1\\
x+f(\lfloor \frac{x}{2}\rfloor),&x > 1
\end{cases}
$$

答案即为 $f(n)$。

**记得开 `long long`!**

---

