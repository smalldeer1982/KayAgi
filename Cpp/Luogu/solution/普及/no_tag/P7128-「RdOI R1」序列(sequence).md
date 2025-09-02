# 「RdOI R1」序列(sequence)

## 题目描述

有一序列 $x$ ，长度为 $q$ ，序列中的每个数只出现一次。

即：序列 $x$ 是 $1$ 到 $q$ 的一个排列。

对于序列 $x$ 的操作只有一种：对于一个数 $x_i$ ，你可以使其与 $x_{2i}$ 或 $x_{2i+1}$ 交换位置(如果它们存在的话)。

现在请你使序列 $x$ 变为一个升序序列，并按顺序输出你进行的操作。

## 说明/提示

【样例说明】

样例#1说明：

交换 $2$ 和 $3$ ，序列变为：$2,1,3$。

再交换 $2$ 和 $1$ ，序列变为：$1,2,3$。

【数据范围】

对于 $40\%$ 的数据，$3 \le q \le 2^{10}$。

对于 $100\%$ 的数据，$3 \le q \le 2^{17}$，$1 \le x_i \le q$。

【提示】

- 使用 Special Judge。
- $q = 2 ^ p - 1(p \in \mathbb{N}^*)$  
- 最多进行 $2q\times\lceil\log_2 q\rceil$ 次操作。
- 样例的输出数据只是众多方案中的一种。
- 因为是 `special judge` ，因此不提供附加样例。

---

【文件读入读出】**（模拟，提交代码时不需使用）**

- 文件名：`sequence.cpp`
- 读入文件名：`sequence.in`
- 读出文件名：`sequence.out`


## 样例 #1

### 输入

```
3
3 1 2```

### 输出

```
1 3
1 2```

## 样例 #2

### 输入

```
7
1 3 2 7 6 4 5```

### 输出

```
2 4
1 2
1 3
3 7
2 5
1 2
1 3
3 6
1 2
2 5
1 3
1 2
2 4
1 2
1 3
1 2```

# 题解

## 作者：Thomas_Cat (赞：8)

赛后口胡题解：

Ps：可能受了验题影响因此可能代码像std就不放了（

---

对于该题，我们知道的条件是：

- 有一课二叉树，节点数为 $2^p-1$，其中 $x_i,x_{2i},x_{2i+1}$ 的关系很容易理解：父亲和左儿子右儿子。

- 从上面的到：在该二叉树中对于节点 $j$，可与 $2j,2j+1$交换位置，使其编号与值相等。

---

因此我们的处理方法如下：

- 找到 $x_i$

- 找到 $x_i,x_{x_i}$ 的 $LCA$

- 用儿子交换到 $x_{x_i}$

- 从 $x_q$ 处理至 $x_1$

口胡完毕（

---

## 作者：Alarm5854 (赞：5)

这道题目的做法比较简单。用一个数组记录一下 $x$ 出现的位置，然后，将 $x$ 从大到小枚举，如果说 $x$ 现在就在原来的位置，那么就不要动了；否则，那就把这个数先弄到第一个位置，然后根据这个数的二进制位一步一步的交换上去。记得改变其它数的位置，否则会出错。

这样做的交换次数最多为 $2q\log_2q$ 次，满足题目的要求。

```cpp
#include<cctype>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 131072;
int q, x[N], p[N], t[N];
int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
int main() {
	q = read();
	for (int i = 1; i <= q; ++i) p[x[i] = read()] = i;
	for (int i = q; i > 1; --i) {
		if (p[i] == i) continue;
		while (p[i] > 1) {
			printf("%d %d\n", p[i] / 2, p[i]);
			swap(x[p[i]], x[p[i] / 2]);
			swap(p[i], p[x[p[i]]]);//记得交换这个东西
		}
		int j = 0;
		for (int k = i; k > 1; k /= 2) t[++j] = k; t[++j] = 1;//用个数组存一下i不断除以二并向下取整时经过的路径，等一下倒序循环即可
		for (int k = j; k > 1; --k) {
			printf("%d %d\n", t[k], t[k - 1]);
			swap(x[t[k]], x[t[k - 1]]);
			swap(p[x[t[k]]], p[x[t[k - 1]]]);
		}
	}
	return 0;
}
```

---

## 作者：Xuanbo (赞：1)

## [P7128 「RdOI R1」序列(sequence)](https://www.luogu.com.cn/problem/P7128)
---


提示：要想将原序列变为 $1$ 到 $n$ 的有序序列，可以优先考虑从大到小恢复，因为已完成恢复的最后的数不会影响到之后的操作。

由题可以看出，$i$ 位置与 $2i$ 或 $2i+1$ 位置的联系可以看为一棵根节点为 $1$ 的二叉树。所谓从当前位置到目标位置就是求两点间的树上路径。~~本来考虑建图的~~

求树上的路径可以想到求两点间的 LCA，用 `dep` 数组保存当前位置在树上的深度，先将两点跳到同一深度，再同步上跳直到相遇，记录上跳的过程，就是交换的操作。
### 定义
- `pos[N]`：数字 $w_i$ 在数列中的位置。
- `dep[N]`：当前位置 $i$ 在二叉树中的深度。
```cpp
#include<bits/stdc++.h>
#define Xuanbo return 0
#define int long long
using namespace std;
const int N=1e6;
int n;
int w[N];
int pos[N],dep[N];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>w[i];
        pos[w[i]]=i;
        dep[i]=dep[i>>1]+1;
    }
    for(int i=n;i>=1;i--){//i代表的是数字i本身
        vector<int> X,Y;
        int x=pos[i];//原位(位置)
        int y=i;//应位(数字)
        Y.push_back(y);
        X.push_back(x);
        while(dep[x]!=dep[y]){
            y>>=1;
            Y.push_back(y);
        }
        while(x!=y){
            x>>=1;
            y>>=1;
            X.push_back(x);
            Y.push_back(y);
        }
        for(int j=1;j<X.size();j++){
            int a=X[j],b=X[j-1];
            swap(w[a],w[b]);
            swap(pos[w[a]],pos[w[b]]);
            cout<<a<<" "<<b<<'\n';
        }
        for(int j=Y.size()-1;j>=1;j--){
            int a=Y[j],b=Y[j-1];
            swap(w[a],w[b]);
            swap(pos[w[a]],pos[w[b]]);
            cout<<a<<" "<<b<<'\n';
        }
    }
    Xuanbo;
}
```
~~蒟蒻的第一篇题解求通过QWQ~~

---

## 作者：hlb44 (赞：1)

[$题目传送门$](https://www.luogu.com.cn/problem/P7128)
## 题目知识点
对于序列 $x$ 的操作只有一种：对于一个数 $x_i$，你可以使其与 $x_{i+1}$ 或 $x_{2i+1}$ 交换位置(如果它们存在的话)。

读了这一段话，你应该想到什么？

二叉树！

那么对于一颗二叉树，${x_i,x_{i+1},x_{2i+1}}$ 分别对应的是：父亲、左儿子、右儿子，这时你要问为什么？

不妨来看这个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/m4fnp5ib.png)
在上图中，这是一个高度是 $ 4 $ 的满二叉树。

请看到图中的根节点：红色 $ 1 $。

它的左儿子是绿色 $2$，右儿子是蓝色 $ 3 $，$ 1 $ 和 $ 2 $ 的关系是 $ 1 × 2 = 2 $，$1$ 和 $3$ 的关系是 $ 1 × 2 + 1 = 3 $；

还不明显？

那就再看图中蓝色 $ 3 $ 的左儿子：灰 $ 6 $。

它的左儿子是粉色 $ 12 $，右儿子是紫色 $ 13 $，$ 6 $ 和 $ 12 $ 的关系是 $ 6×2=12 $，$ 6 $ 和 $ 13 $ 的关系是 $ 6×2+1=13 $。

那么你如果在任意观察一个有左儿子和右儿子点，你能发现一个规律：

假设父亲的编号为 $ x $，则左儿子编号为 $ 2x $，右儿子的编号为 $ 2x+1 $。

## 题目解析
那我们就可以按这样的方式来计算：

1.  找到 $ x_i$。

2.  找到 $ x $ 和 $ x_{x_i} $ 的 $\operatorname{Lca}$。

3.  用这个点的儿子交换到 $ x_{x_i}$。

这时你可能有不知道 $\operatorname{Lca}$ 了，给你一篇[博客](https://blog.csdn.net/lxt_Lucia/article/details/81354890)，自己去看吧。

为了维护公共秩序~不想写~，只提供部分代码：

```cpp
if (p[i]==i){
	continue;
}
while (p[i]>1) {
	cout<<p[i]/2<<" "<<p[i]<<"\n";
	swap(x[p[i]],x[p[i]/2]);
	swap(p[i],p[x[p[i]]]);
}
int j=0;
for (int k=i;k>1; k/=2){
	t[++j]=k;
}
t[++j]=1;
for (int k=j;k>1;--k) {
	cout<<t[k]<<" "<<t[k-1]<<"\n";
	swap(x[t[k]],x[t[k-1]]);
	swap(p[x[t[k]]],p[x[t[k-1]]]);
}

---

## 作者：_WHX985_ (赞：1)

## 思路
题目标签也没有给任何的提示，但只要你读题仔细就能发现 $2x$ 和 $2x+1$ 仿佛在那里见过，你没有想错，在一棵二叉树上，一个节点编号为 $x$ 的节点的左孩子编号为 $2x$ 右孩子编号为 $2x+1$，当然这是在有的情况下。如果不理解大家就来看个图。圆圈中写的是节点的编号。
![](https://cdn.luogu.com.cn/upload/image_hosting/dbsur026.png)
这样的话，思路就有了。建立一个 $vis$ 数组记录一下 
$x$ 出现的位置，然后直接从后往前枚举 $x$，当 $x$ 就在 $x$ 号位时 $x$ 就不需要动了，因为此时的 $x$ 已经排好了，但如果没拍好，切记不要盲目交换，而是将 $x$ 移动到第一个再交换。
## 部分参考代码
C++ 部分参考代码，有注释。

```cpp
for(int i=flag;i>=2;i--){
	if(df[i]!=i){//x没有排好 
		while(df[i]>1){//所处的位置大于1 
			cout<<df[i]/2<<' '<<df[i]<<'\n';//交换i号位和i/2号位 
			swap(x[df[i]],x[df[i]/2]);//标记 
			swap(df[i],df[x[df[i]]]);
		}
		int high=0;//栈顶 
		for(int j=i;j>=2;j/=2){//压入栈 
			t[++high]=j;
			t[++high]=1;
		}
		for(int j=high;j>=2;j--){
			cout<<t[j]<<' '<<t[j-1]<<'\n';//交换 
			swap(x[t[j]],x[t[j-1]]);
			swap(df[x[t[j]]],df[x[t[j-1]]]);
		}
	}
}
```

---

## 作者：SilverLi (赞：1)

[序列 の 传送门](https://www.luogu.com.cn/problem/P7128)

看到题目。

> 对于一个数 $x_i$，你可以使其与 $x_{2i}$ 或 $x_{2i+1}$ 交换位置。

$2i$ 和 $2i+1$ 想到什么？

对，就是**二叉树**，所以可以找到他们两个的 LCA，再交换。

但是，应该交换哪两个数，于是可以考虑用 $pos_j$ 储存 $x_i=j$ 的 $i$ 的值。

例如，$x_1=2$，那么 $pos_2=1$。

因为是交换 $x_i$ 和 $x_{2i}$ 或 $x_{2i+1}$，所以采用倒叙枚举。

如果 $pos_{x_i}$ 不等于 $i$，那么先求出 $pos_{x_i}$ 和 $i$ 的 LCA，再将 $x_{LCA}$ 向下一个数一个数地交换到 $x_i$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1<<18;
int n,a[N],p[N];
inline int LCA(int u,int v) {
	while(u!=v)
		if(u>v)	u>>=1;
		else	v>>=1;
	return u;
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;++i) {cin>>a[i];p[a[i]]=i;}
	for(int i=n;i;--i)
		if(p[i]!=i) {
			int lca=LCA(p[i],i);
			int now=lca,P=p[i];
			if(lca!=p[i])
				while(now!=P) {
					cout<<(P>>1)<<' '<<P<<endl;
					swap(a[P],a[P>>1]);
					p[a[P]]=P,p[a[P>>1]]=P>>1;
					P>>=1;
				}
			P=i;
			stack<int> s;
			while(now<P)	s.push(P),P>>=1;
			while(!s.empty()) {
				int nxt=s.top();
				cout<<now<<' '<<nxt<<endl;
				swap(a[now],a[nxt]);
				p[a[now]]=now,p[a[nxt]]=nxt;
				now=nxt;
				s.pop();
			}
		}
	return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7128)
# 题意
输入一个 $q$ 的排列 $x$，然后进行若干次以下操作使 $x$ 变为升序序列并输出操作数及具体操作：
> 对于一个数 $x_i$，可以让它与 $x_{2i}$ 或 $x_{2i+1}$ 交换位置。（如果它们都存在）。
# 思路
用一个数组记录 $x$ 出现的位置，然后枚举 $x$，如果 $x_i$ 就在目标位置就不要动，否则就想把它放到第一个位置，然后再一步一步交换到目标位置。其中记得改变其他数的位置。

为了维护社区秩序（实际上是懒），代码就不放了，求关~

---

## 作者：wuhan1234 (赞：0)

## 1.编程思路。

根据题意，序列 $X$ 是 $1$ 到 $q$ 的一个排列。要使序列  $X$ 变为一个升序序列，就是要通过交换操作使得序列 $X$ 中的任意一个数 $X_i=i$。

根据给出的交换规则可以发现，用序列 $X$ 的 $q$ 个数据作为结点值，可以构成一棵有 $q$ 个结点的完全二叉树，序列 $X$ 中的数据交换操作只能发生在其对应完全二叉树的父结点和左子结点（或右子结点）之间。

设 $pos_i$ 表示数字 $i$ 在序列 $X$ 中的位置。例如，$X_4=7$，则 $pos_7=4$。

采用逆序循环的方式将数字 $q$ 至 $1$ 均通过交换使其放置在其应该放置的位置。对于任意一个数 $i(1\le i\le q)$，要使 $X_i=i$，可以采用如下操作：

1）若数字 $i$ 的位置 $pos_i$ 的值就是 $i$，则数字 $i$ 已经放置在正确位置，无需交换处理；直接进行下次循环，处理数字 $i-1$；

2）找到编号为 $pos_i$ 的结点（数字 $i$ 当前所在的位置）和编号为 $i$ 的结点（数字 $i$ 应该交换到的位置）的最近公共祖先的编号 $k$；

3）先将位于 $pos_i$ 位置的数字 $i$ 依次向上交换到最近公共祖先 $k$ 处（若 $pos_i=k$，则无需移动），再将位于公共祖先 $k$ 处的数字 $i$ 向下依次交换到编号为 $i$ 的结点处。

## 2.源程序。
```c
#include <stdio.h>
int common(int a,int b)  // 寻找结点a和b的最近公共祖先
{   // 每次让编号大的结点向根结点走一步，直到两个结点到了同一个点
    while (a != b)
    {
        if (a > b) a /= 2;
        else       b /= 2;
    }
    return a;
}
int x[150005],pos[150005];
void change1(int a,int b)   // 将从二叉树中编号为b的结点向上依次换到编号为a的祖先结点处
{
     int t;
     while (b!=a)
     {
         printf("%d %d\n",b/2,b);
         t=x[b];  x[b]=x[b/2];  x[b/2]=t;
         pos[x[b]]=b;
         pos[x[b/2]]=b/2;
         b=b/2;
     }
}
void change2(int a,int b)   // 将从二叉树中编号为a的结点向下依次换到编号为b的结点处
{
     int cnt=0;
     int p[20];
     while (b!=a)
     {
         p[cnt++]=b;
         b/=2;
     }
     int cur=a,next,t;
     while (cnt--)
     {
         next=p[cnt];
         printf("%d %d\n",cur,next);
         t=x[cur];  x[cur]=x[next];  x[next]=t;
         pos[x[cur]]=cur;
         pos[x[next]]=next;
         cur=next;
     }
}
int main()
{
	int n;
	scanf("%d",&n);
	int i;
	for (i=1;i<=n;i++)
    {
        scanf("%d",&x[i]);
        pos[x[i]]=i;
    }
    for (i = n; i >= 1; i--)     // 从最后一个位置到第1个位置进行处理，将每个位置放置正确的数
    {
        if (pos[i]==i) continue;  // 当前数正好在其正确位置
        int p,k;
        p=pos[i];           // 确定数字i所在的位置p，然后交换位置p和位置i的数
        k=common(p,i);      // 找到p和i的最近公共祖先k
        if (k!=p)
        {
            change1(k,p);  // 先将位于p位置的数字i向上换到最近公共祖先k处
        }
        change2(k,i);      // 再将位于k处的数字i向下换到位置i处
    }
	return 0;
}

```


---

