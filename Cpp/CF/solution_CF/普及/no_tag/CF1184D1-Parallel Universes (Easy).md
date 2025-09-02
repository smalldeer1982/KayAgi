# Parallel Universes (Easy)

## 题目描述

Third Doctor 曾说平行宇宙之间的旅行“就像穿越旅行”。然而，他错认为存在着无限的平行宇宙，而事实上它们永远不会超过$250$个。

海蒂最近得到了一个多元宇宙观测器。她能看到所有的$N$个宇宙排成一排，它们之间不存在联系。 Doctor 在第$k$宇宙。

由于时空的种种原因，宇宙的数量永远不会超过$m$。

显然，多元宇宙变幻莫测，每次做出变化时，必将会有一个新的并行宇宙被创建，或者一个不存在的链接被破坏。

更具体地说，

- 当一个宇宙被创造时，它将在任何两个相邻的宇宙之间或在其中一个末端出现。

- 当一个连接断开时，它可以在任何两个相邻的宇宙之间被切断。在将多宇宙分割成两段之后，不包含 Doctor 的部分将在时空中陨落，不复存在。

海蒂突发奇想，模拟$t$个变化。每次变化时时，海蒂想知道多元宇宙的长度（即宇宙的数量）和 Doctor 的位置。

## 样例 #1

### 输入

```
5 2 10 4
0 1
1 1
0 4
1 2
```

### 输出

```
4 1
5 2
4 2
5 3
```

# 题解

## 作者：syhx (赞：2)

就是一道模拟题，大概就是 普及- 的难度。  
主要就是去对添加操作和删除操作进行分类讨论。  
以下进行讨论。

------------
### 分类讨论：添加操作
1. 当添加宇宙位置在博士位置的前面时，博士位置要后移。
2. 不管添加位置在哪里，宇宙总长度都要增加。

------------
### 分类讨论：删除操作
1. 当删除位置在博士位置的前面时，博士位置要前移 删除的宇宙数量 个。
2. 不然把宇宙长度删到只剩博士的位置。

------------
这是最后的代码。注释很详细，请放心食用。
```
#include<bits/stdc++.h>
using namespace std;
int now_long,d_where,max_space,T;
//now_long是宇宙的现在长度。
//d_where是博士现在在的位置。
//max_space是宇宙的最大数量。
//T是操作次数。
void solve(){
    int do_what,where;
	//do_what是操作，where是操作位置 
	cin>>do_what>>where;	
	if(do_what==1){
	//加入宇宙操作 
		if(where<=d_where){
		//如果加入位置在博士位置的前面 
			now_long++;		
			d_where++;
			//宇宙长度++，博士位置后移 
		}
		else now_long++;
		//不然只是宇宙长度++ 
		cout<<now_long<<" "<<d_where<<endl;
	}
	else{
	//删除宇宙操作 
		if(where<d_where){
		//如果删除位置在博士位置的前面 
			now_long-=where;
			d_where-=where;
			//宇宙数量--，博士位置前移 
		}
		else now_long=where;
		//不然删到只剩博士和他在的宇宙链 
		cout<<now_long<<" "<<d_where<<endl;
	}	
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//优化 
	cin>>now_long>>d_where>>max_space;
	cin>>T;
	while(T--) solve();
    //解决
    return 0;
}
//syhx-NaOH2009
```
@ syhx

---

## 作者：封禁用户 (赞：1)

## 思路

有两种情况：

1. $blog=1$

	 - 当 $x≤k$ : $Doctor$ 的位置和多元宇宙的总长度 $1$。
     
    - 当 $x>k$ : 多元宇宙的总长度加 $1$。

2. $blog=0$

    - $x≥k$ : 多元宇宙的总长变为 $x$。 
    
    - $x<k$ : $Doctor$ 的位置和多元宇宙的总长度 $x$。
    
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,m,t;
bool blog;
int x;

int main()
{
	cin>>n>>k>>m>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>blog>>x;	
		if(blog==1)
		{
			if(x<=k)
			{
				n++;		
				k++;
			}
			else
			{
				n++;
			}
		}
		else
		{
			if(x<k)
			{
				n=n-x;
				k=k-x;
			}
			else
			{
				n=x;
			}
		}	
		cout<<n<<" "<<k<<endl;
	}	
    return 0;
}
```

---

## 作者：jubaoyi2011 (赞：0)

## 思路

我们先设每行的两个数分别为 $i_1$ 和 $i_2$，这时 $i_1$  就只有两种情况：
1.  $i_1 = 1$，而此时 $i_2$ 又分为两种情况：

当 $i_2 \le k$ 时，博士的位置和多元宇宙的长度加 $1$

当 $i_2 > k$ 时，多元宇宙的长度加 $1$。

2.   $i_1 = 0$，而此时 $i_2$ 也分为两种情况：

当 $i_2 \ge k$ 时，多元宇宙的长度变为 $i_2$。

当 $i_2 < k$ 时，博士的位置和多元宇宙的长度变为 $i_2$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,m,t,i1,i2;

int main(){
    cin>>n>>k>>m>>t;
    while(t--){
    	cin>>i1>>i2;	
    	if(i1==1){
    	    if(i2<=k){
        		n++;		
        		k++;
    	    }
    	    else{
        		n++;
    	    }
    	}
    	else{
    	    if(i2<k){
              n=n-i2;
          		k=k-i2;
          }
    	    else{
          		n=i2;
    	    }
    	}	
    	cout<<n<<" "<<k<<endl;
    }	
}
```

---

## 作者：liangkairui (赞：0)

# [Parallel Universes (Easy)](https://www.luogu.com.cn/problem/CF1184D1) 题解
## 浅谈一下
题目翻译~~貌似~~反了。

这是一道需要~~简单~~想一下的模拟~~水~~题。

顺着题解味就过来了。
## 思路
添加宇宙：如果插入的宇宙在 Third Doctor 前时，他就要往后移。无论宇宙插在哪里，总长度都要增加。

连接断开：如果 Third Doctor 在断开的位置后面，就要减去断开的宇宙的位置。否则 Third Doctor 的位置不变。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k,m,t;
	scanf("%d%d%d%d",&n,&k,&m,&t);
	while(t--){
		int opt,i;
		scanf("%d%d",&opt,&i);
		if(opt==1){		//插入宇宙（题目翻译弄反了） 
			if(i<=k)k++;
			n++;
		}
		else{
			if(i<k){
				n-=i;
				k-=i;
			}
			else n=i;
		}
		printf("%d %d\n",n,k);
	}
	return 0;
}
```

---

## 作者：DecemberFox (赞：0)

# CF1184D1 题解

## 题目分析

本题大致意思是通过模拟一条链，在每一次删除和插入操作后输出链的长度和 Third Doctor 的位置。

## 解法分析

对于本题，由于题目并不关心每一个宇宙的内容，只关心整体长度和 Third Doctor 的位置。因此可以通过简单的模拟求解。

- 对于添加操作：

	首先不论 Third Doctor 在何处，整体长度一定增加 $1$。

	然后对 Third Doctor 的位置进行分类讨论，若他在新增宇宙的后面，那么他的位置将会后移，否则他的位置不会发生变化。

- 对于移除操作：

	首先对 Third Doctor 的位置进行分类讨论，若他他在断开链的前面，他的位置不会发生变化，否则他的位置将要减去断开链的位置。

	其次，链的长度也需要相应减少。

有了上面的讨论，代码就很好写了。

```cpp
#include<iostream>
#include<cstdio>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int n(1);
		now=0;
#define isdigit(c) ((c)>='0'&&(c)<='9')
		while(!isdigit(c)){if(c=='-') n=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
#undef isdigit
		now*=n;
		read(next...);
	}
	template<typename nowtype>
	void write(nowtype num,char end='\n')
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
	template<typename nowtype,typename ...nexttype>
	void write(nowtype num,char end,nexttype ...next)
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
		write(next...);
	}
}
using namespace io;
//以上是快读快写
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	void solve()
	{
		int n,k,m,t,op,i;
		read(n,k,m,t);
		while(t--)
		{
			read(op,i);
			switch(op)
			{
			case 0:
				if(k>i)
				{
					k-=i;
					n-=i;
				}
				else n=i;
				break;
			case 1:
				if(k>=i) ++k;
				++n;
				break;
			}
			write(n,' ',k);
		}
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

## 作者：_Starlit__Sky_ (赞：0)

# 洛谷 CF1184D1 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1184D1)

## 题目算法

模拟

## 题目思路

对于 $t$ 次输入，有两种不同的操作类型，对于每种操作类型，我们需要输出宇宙的总长 $n$ 和 `Doctor` 的位置 $k$：

### 类型 $1$（在第 $i$ 位添加宇宙）

#### 宇宙的总长 $n$
- 因为添加了 $1$ 个宇宙，所以宇宙的总长 $n$ 将增加 $1$。（~~这不是废话吗~~）

#### `Doctor` 的位置 $k$
对于 $k$，有两种情况。

- 当添加的位置 $i$ 比 `Doctor` 的位置 $k$ 小（即添加的宇宙在 `Doctor` 的前面）时，`Doctor` 的位置 $k$ 将增加 $1$。

- 当添加的位置 $i$ 比 `Doctor` 的位置 $k$ 大（即添加的宇宙在 `Doctor` 的后面）时，`Doctor` 的位置 $k$ 不变。

### 类型 $2$（断开第 $i$ 位链接）

#### 宇宙的总长 $n$
因为没有 `Doctor` 的一部分将被删除，所以宇宙长度 $n$ 需要减去没有 `Doctor` 的一部分宇宙的长度

对于没有 `Doctor` 的一部分宇宙的长度，有 $2$ 种情况。
- 当 $i$ 比 `Doctor` 的位置 $k$ 小（即前 $i$ 个宇宙是第一部分，第 $i+1$ 至第 $n$ 个宇宙是第二部分，`Doctor` 在第二部分）时，由于前 $i$ 个宇宙是没有 `Doctor` 的一部分宇宙，它的长度是 $i$，所以宇宙的长度 $n$ 将减少 $i$。
- 当 $i$ 比 `Doctor` 的位置 $k$ 大（即前 $i$ 个宇宙是第一部分，第 $i+1$ 至第 $n$ 个宇宙是第二部分，`Doctor` 在第一部分）时，由于第 $i+1$ 至第 $n$ 个宇宙是没有 `Doctor` 的一部分宇宙，它的长度是 $n-(i+1)+1$，所以宇宙的长度 $n$ 将减少 $n-(i+1)+1$。

#### `Doctor` 的位置 $k$
对于 $k$，有 $2$ 种情况。
- 当 $i$ 比 `Doctor` 的位置 $k$ 小（即前 $i$ 个宇宙是第一部分，第 $i+1$ 至第 $n$ 个宇宙是第二部分，`Doctor` 在第二部分）时，由于前 $i$ 个宇宙的消失，所以第二部分的宇宙中的位置将整体往前移动 $i$，即 $k$ 要减少 $i$。
- 当 $i$ 比 `Doctor` 的位置 $k$ 大（即前 $i$ 个宇宙是第一部分，第 $i+1$ 至第 $n$ 个宇宙是第二部分，`Doctor` 在第一部分）时，由于消失的宇宙在 `Doctor` 的后方，所以 `Doctor` 的位置 $k$ 无需变化。

## 代码
本人提交已 AC。放心食用。

```python
n,k,m,t = map(int,input().split()) # 输入 n,k,m,t
for _ in range(t): # t 组输入
    op,i = map(int,input().split())
    if op == 1: # 第一个数为 0
        n += 1 # 宇宙数量始终增加
        if i <= k: k += 1 # 若添加宇宙的位置在博士前面则博士的位置增加
    if op == 0: # 第一个数为 1
        if i < k: # 如果断开的位置在博士前面
            k -= i # 博士的位置往前移动 i 个
            n -= i # 宇宙数量减少 i 个
        else: # 如果断开的位置在博士后面
            n -= n-(i+1)+1 # 宇宙数量减少 n-(i+1)+1 个
    print(n,k)
```

~~点个赞再走吧~~ $awa$

---

## 作者：valen071 (赞：0)

[YUANTI传送门](https://www.luogu.com.cn/problem/CF1184D1)

# 思路：
暴力模拟当然可以，但是显然太麻烦。
提供一种更好的思路：
先输入一个 A 然后一个 B ；

1. A 为 TRUE
增加一个宇宙，再按照 B 和 K 的关系讨论；

2. A 为 FALSE
减少宇宙，在讨论；

[AC!!!!](https://www.luogu.com.cn/record/146689024)

代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k,m,N,p;
signed main(){
	cin >> n >> k >> m >> N;
	for(int i=1;i<=N;i++){
		int a,b;
		cin >> a >> b;
		if(a==0){//a=0,看b<k or b>=k;
			if(b<k){
				n=n-b;
				k=k-b;
			}
			else n=b;
		}
		else {//a=1,看b<=k or b>k;
			if(b<=k){
				n++;
				k++;
			}
			else n++;
		}	
		cout << n << " " << k << endl;
	}	
    return 0;
}
```


---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1184D1)

# 思路

一道模拟题，进行分类讨论。

- 如果 $op$ 为 $1$ ，则增加宇宙，判断是否在 Doctor 前面加。若是，位置和长度增加，反之只有长度增加。

- 如果 $op$ 为 $0$ ，操作为切割，判断是否在 Doctor 前面切。若是，位置和长度减少 $i$ ，反之长度为 $i$ 。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,T,op,x;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k>>m>>T;
    while(T--){
    	cin>>op>>x;
    	if(op){
    		if(x<=k) n++,k++;
    		else n++;
		}
    	else{
    		if(x<k) n-=x,k-=x;
    		else n=x;
		}
		cout<<n<<" "<<k<<"\n";
	}
    return 0;
}
```


---

## 作者：WaterSky (赞：0)

这一道[题目](https://www.luogu.com.cn/problem/solution/CF1184D1)比较简单。

- 如果需要执行的步骤为增加宇宙，那么就要判断是否在 Doctor 前面增加，如果是，那么 Doctor 的位置和长度增加 $1$，否则就只有长度增加 $1$。
- 如果执行为切割，那么就同样要判断，是否是在 Doctor 前面切割，如果是，那么位置和长度都减少 $i$，否则长度变为 $i$。

```
#include<bits/stdc++.h>
using namespace std;
long long n,k,m,t,x,y;
int main()
{
	cin>>n>>k>>m>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>y>>x;	
		if(y==1)
		if(x<=k) n++,k++;
		else n++;
		else
		if(x<k) n=n-x,k=k-x;
      else n=x;
		cout<<n<<" "<<k<<endl;
	}	
    return 0;
}

```

---

## 作者：MithrilSword_XIV (赞：0)

## 思路

判断加入宇宙的地方和删除连接的地方 $i$ 与 Doctor 所在的位置 $k$。

如果 $b$ 为 $1$：

- $i \le k$，将 Doctor 的位置与宇宙的长度都加 $1$。
- $i > k$，将宇宙的长度加 $1$。

否则：

- $i < k$，删除后面的部分，将 Doctor 的位置与宇宙的长度都减 $i$。
- $i \ge k$，删除前面的部分，将宇宙的长度变为 $i$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,t,b,id;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>m>>t;
	for(int i=1;i<=t;i++){
		cin>>b>>id;
		if(b){
			if(id<=k){
				k++,n++;
			}else{
				n++;
			}
		}else if(!b){
			if(id<k){
				k-=id,n-=id;
			}else{
				n=id;
			}
		}
		cout<<n<<' '<<k<<'\n';
	}
	return 0;
}

```


---

## 作者：N_z_ (赞：0)

## 前言
为什么翻译出来和原文的输入的意义反了啊。

这边给一个正确的输入格式
若第一个数为 $1$ ，意为在位置 $i(1\leq i\leq l+1)$ 插入一个宇宙，其中 $l$ 表示多重宇宙的当前长度。

若第一个数为 $0$ ，表示第 $i(1\leq i\leq l-1)$ 个链接断开了，其中 $l$ 表示多元宇宙的当前长度。
## 思路
模拟。

对于
* $op=1$
	* $i≤k$ 博士位置和总长都加 $1$ 。
   * $i>k$ 总长加 $1$ 。
* $op=0$
	* $i<k$ 总长和博士位置都减 $i$ 。
   * $i≥k$ 总长变为 $i$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k,m,t;
    cin>>n>>k>>m>>t;
    while(t--)
    {
        int op,i;
        cin>>op>>i;
        if(op==1){
            n++;
            if(i<=k)k++;
            cout<<n<<' '<<k<<endl;
        }
        else{
            if(i<k)n-=i,k-=i;
            else n=i;
            cout<<n<<' '<<k<<endl;
        }
    }
}
```

---

## 作者：Tobiichi_Origami (赞：0)

**希望洛谷重新翻译一下本题，输入样例和题目翻译整反了。**


**思路**

本题让我们模拟 $t$ 次，输出对应每次操作的 $n$ 和 $k$ 的值。

如果 $b$ 为 $1$，在位置 $i$ 插入一个宇宙，宇宙的总数量也就多了一个，所以 $n+1$，并且，如果在 $\texttt{doctor}$ 的前面插入了一个宇宙，则 $\texttt{doctor}$ 的位置也多了一个，所以 $k+1$。

如果 $b$ 为 $0$，在位置 $i$ 选择 $doctor$ 不在的宇宙区间彻底删除掉，如果在 $doctor$ 的前面的区间被删除了的话，则 $doctor$ 的位置和宇宙的总数量也就减少了 $i$，所以 $k-=i$ 并且 $n-=i$，但如果在 $doctor$ 的后面怎么办呢，这时 $doctor$ 的位置并不改变，改变的是宇宙的数量，宇宙也就只剩 $i$ 个，所以 $n=i$。

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k,m,t,i;
    bool b;
    cin>>n>>k>>m>>t;
    for(int k=1;k<=t;k++)
    {
        cin>>b>>i;
        if(b)
        {
            n++;
            if(i<=k) k++;
            cout<<n<<" "<<k<<endl;
        }
        else 
        {
            if(i<k) n-=i,k-=i;
            else n=i;
            cout<<n<<" "<<k<<endl;
        }
    }
    return 0;
}
```


---

