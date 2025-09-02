# Ehab and another another xor problem

## 题目描述

交互题，系统有两个整数 $(a,b)$，你每次可以询问一组整数 $(c,d)$，系统会回答：
- $1$ 如果 $a\oplus c>b\oplus d$
- $0$ 如果 $a\oplus c=b\oplus d$
- $-1$ 如果 $a\oplus c<b\oplus d$

其中操作 $a\oplus b$ 表示 $a$ 和 $b$ [按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

你需要在询问不超过 $62$ 次之后输出 $(a,b)$ 的值，保证 $0\le a, b < 2^{30}$。

## 样例 #1

### 输入

```
1
-1
0```

### 输出

```
? 2 1
? 1 2
? 2 0
! 3 1```

# 题解

## 作者：mrsrz (赞：6)

考虑从高到低确定$a,b$的二进制位，且确定一位所用的步数最多2次。

先花一次询问确定$a,b$的大小关系$f$。

设当前已经确定的$a$的二进制位组成$A$，$b$的二进制位组成$B$。

我们令$f$在任一时刻都表示$a\oplus A$和$b\oplus B$的大小关系（即不考虑已经确定的二进制位）。

对于第$i$位，我们先询问$c=A\oplus 2^i,d=B\oplus 2^i$。如果得到的大小关系等于$f$，则说明这两个二进制位相等，否则不等。

若相等，则询问$c=A\oplus 2^i,d=B$，若得到的大小关系为1，则说明两数都不含第$i$位；若为-1，则说明两数都含第$i$位。不可能为0。更新$A,B$即可。

由于这两个二进制位相同，所以更新$A,B$后，$f$的值不用改变。

若不相等，得到的大小关系为1，则$a$含有第$i$位，若为-1，则$b$含有第$i$位，不可能为0。更新$A,B$即可。

此时$f$的值就有可能改变，需要再花一步询问$c=A,d=B$，更新$f$的值。

这样总共步数为61步，没有超过限制。

## Code：
```cpp
#include<cstdio>
#include<cstdlib>
int A,B;
void ask(int x,int y){printf("? %d %d\n",x,y);fflush(stdout);}
void succ(int x,int y){printf("! %d %d\n",x,y);fflush(stdout);exit(0);}
int main(){
	ask(0,0);
	int cmp;
	scanf("%d",&cmp);
	for(int i=29;~i;--i){
		ask(1<<i|A,1<<i|B);
		int x;
		scanf("%d",&x);
		if(x==cmp){//same
			ask(1<<i|A,B);
			scanf("%d",&x);
			if(x==-1)A|=1<<i,B|=1<<i;
		}else{//different
			if(cmp==1)A|=1<<i;else B|=1<<i;
			ask(A,B);
			scanf("%d",&cmp);
		}
	}
	succ(A,B);
}
```

---

## 作者：EnofTaiPeople (赞：2)

这道题有些吓唬人：只能得到两个数字异或之后的大小比较结果，这也确实是一道 IO 交互猜数的好题，难度较大。

IO 交互猜数都有一个共同的特点：真相只有一个！通俗的讲，它们一般只有一个答案，并且代码实现较为基础，亦可称作“思维题”。

对于位运算的题目，他们大部分的通解就是逐位确定，此题限制了 62 次询问，即每一位只有两次询问机会，我们可以根据之前询问的结果得到从某一位开始的 $x,y$ 的比较结果。

先预处理 $2^i$，用一个 p2n 数组存，初始 $x=y=0$，对于每一个二进制位，如果 x 或 y 为 1，就让它们或上这一位，直到处理完第 0 位，$x,y$ 就是答案。

我们先进行依次询问 “？ 0 0”，得到 $x,y$ 的初始大小关系，用 npt 来记录，每处理完一位，就更新一次。

代码细节：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p2n[32],x,y,npt,i,o,oo,ooo;
int main(){
	ios_base::sync_with_stdio(false);
	for(i=0;i<=31;++i)p2n[i]=1<<i;
	cout<<"? 0 0"<<endl;cin>>npt;
	for(i=29;i>=0;--i)
		switch(npt){
		case 1:cout<<"? "<<x<<" "<<(y|p2n[i])<<endl;
		cin>>o;switch(o){
				case 1:x|=p2n[i];cout<<"? "<<x<<" "<<y<<endl;
				cin>>oo;if(oo==-1)y|=p2n[i];npt=1;break;
				case 0:x|=p2n[i];npt=0;break;
				case -1:cout<<"? "<<(x|p2n[i])<<" "<<(y|p2n[i])<<endl;
				cin>>oo;if(oo==-1)x|=p2n[i],npt=-1;break;
				default:break;
			}break;
		case 0:cout<<"? "<<x<<" "<<(y|p2n[i])<<endl;
		cin>>o;if(o==1)x|=p2n[i],y|=p2n[i];
		npt=0;break;
		case -1:cout<<"? "<<(x|p2n[i])<<" "<<y<<endl;
		cin>>o;switch(o){
				case 1:cout<<"? "<<(x|p2n[i])<<" "<<(y|p2n[i])<<endl;
				cin>>oo;if(oo==1)y|=p2n[i],npt=1;break;
				case 0:y|=p2n[i];npt=0;break;
				case -1:y|=p2n[i];cout<<"? "<<x<<" "<<y<<endl;
				cin>>oo;if(oo==1)x|=p2n[i];npt=-1;break;
				default:break;
			}break;
		default:break;
	}
	cout<<"! "<<x<<" "<<y<<endl;
	return 0;
}
```
因为分类太多了，在此不一一讨论。这里用到的原理主要是“高位高者高”，即如果在一个高位，$x$ 比 $y$ 高，那么不管后面有什么，$x$ 一定比 $y$ 高。

可以看一下我的其他交互题题解：

[CF1415E1](https://www.luogu.com.cn/blog/lwxde/solution-cf1451e1)

[CF1556D](https://www.luogu.com.cn/blog/lwxde/solution-cf1556d)

---

## 作者：_sunkuangzheng_ (赞：1)

为什么这是紫题啊（

**【题目大意】**（引用自题目翻译）


交互题，系统有两个整数 $(a,b)$，你每次可以询问一组整数 $(c,d)$，系统会回答：
- $1$ 如果 $a\oplus c>b\oplus d$
- $0$ 如果 $a\oplus c=b\oplus d$
- $-1$ 如果 $a\oplus c<b\oplus d$


你需要在询问不超过 $62$ 次之后输出 $(a,b)$ 的值，保证 $0\le a, b < 2^{30}$。

**【题目分析】**

$2^{30}$ 和 $62$ 很容易想到二进制或二分。但是题目给出的交互格式并不是很好二分，所以我们考虑二进制逐位确定。

在初始状态下，我们要先确定 $a,b$ 的大小关系。显然可以通过一组询问 $(0,0)$ 轻松问出。下面假设 $a \ge b$。

考虑有以下两个二进制数字：

$1110010$

$1100001$

在二进制下，显然两个数字的大小关系取决于第一个不同的数字。如果我们询问 $(2^i,2^i)$，找到第一个答案为 $0$ 的位置，则有这一位上 $a,b$ 不相等，且前面都相等。考虑如何判断相等的位置上到底是 $1$ 还是 $0$，这是简单的，我们只需要询问 $(2^i,0)$ 结合答案就可以确定这一位的数字。

我们考虑在找到了那一个不同的位置后怎么处理。为了消除前面不一样的位置对异或大小的影响，我们每次的询问要加上已经确定的位置的大小，即询问 $(2^i+a_{cur},2^i+b_{cur})$。如果当前位已经是 $-1$，那么说明这一位上 $a$ 是 $1$，$b$ 是 $0$，我们将 $a \gets a + 2^i$ 后继续判断。你发现，这是原问题的子问题！我们可以递归求解。

至此这道题就做完了，发现每一位上都会询问 $2$ 次，初始时会额外询问一次，最大询问次数是 $61$，可以解决问题。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,k,x,y;
int ask(int a,int b){cout << "? " << a << " " << b << endl,cin >> k;return k;}
void solve(int s,int &a,int &b){
    for(int i = s,p = ask(a,b);i >= 0;i --)
        if(ask(a+(1 << i),b+(1 << i)) == p) {if(ask(a+(1 << i),b) == -1) a += (1 << i),b += (1 << i);}
        else return (p == 1 ? a :b) += (1 << i),solve(i-1,a,b),void();
}
int main(){solve(29,a,b),cout << "! " << a << " " << b;}
```
 

---

## 作者：开始新的记忆 (赞：0)

题目：[https://www.luogu.org/problem/CF1088D](https://www.luogu.org/problem/CF1088D)

交互题，系统有两个整数(a,b)(a,b)，你每次可以询问一组整数(c,d)(c,d)，系统会回答：

1 如果a\oplus c>b\oplus da⊕c>b⊕d
0 如果a\oplus c=b\oplus da⊕c=b⊕d
-1 如果a\oplus c<b\oplus da⊕c<b⊕d
其中操作a\oplus ba⊕b表示aa和bb按位异或

你需要在询问不超过62次之后输出(a,b)(a,b)的值，保证0<=a, b<=2^30

大致思路：因为系统说查询最多62次，而a，b不超过2^30，可以知道这道题和二进制有关。于是我们可以在每个二进制位上都做两次询问然后判断ab分别有没有这一位。


```
#include<bits/stdc++.h>
using namespace std;
int a=0,b=0,flag;
int ask(int x,int y)
{
	cout<<"? "<<x<<' '<<y<<endl;
	int ans;
	cin>>ans;
	return ans;
}

int main()
{	cout.flush();
	flag=ask(0,0);
	for(int i=29;i>=0;i--)
	{
		int t=ask(a^(1<<i),b),tt=ask(a,b^(1<<i));
		if(t==tt) 
		{
			if(flag==1) 
				a^=(1<<i);
			else if(flag==-1) 
				b^=(1<<i);
			flag=t;
		}
		else if(t==-1) 
			a^=(1<<i),b^=(1<<i);
	}
	cout<<"! "<<a<<' '<<b<<endl;
	return 0;
}

```


---

