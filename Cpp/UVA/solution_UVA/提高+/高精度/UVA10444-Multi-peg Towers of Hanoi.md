# Multi-peg Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1385

[PDF](https://uva.onlinejudge.org/external/104/p10444.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/b08ae043c16349a4e020bb344c82bd8559661c15.png)

## 样例 #1

### 输入

```
3 4
4 4
10 4
10 5
0 0```

### 输出

```
Case 1: 5
Case 2: 9
Case 3: 49
Case 4: 31```

# 题解

## 作者：newbiechd (赞：3)

[Blog](https://www.cnblogs.com/cj-chd)  
早期作品，不喜轻喷。  
这是一道小水题 但是我做了很久 因为我比较菜
下面是正文
### 这是一道DP题
#### 我们主要解决两个问题：
#### 1.转移方程	2.高精度（下面有版子）


1. 这里要求的是n盘p塔的hanoi问题。  
   如果有不知道汉诺塔的同学请转（我也不知道转哪里，自己看看书吧）  
   如果有不知道DP的同学（也没有关系，这道题本质上和递推差不多）  
   首先由3塔的hanoi，我们先尝试求解4塔问题：  
   设有n个盘和4个塔A、B、C、D；  
   先在4塔模式下从A塔移动i个盘子到B塔；  
   再在3塔模式下从A塔把剩下的n-i个盘子移动到D塔；  
   最后在4塔模式下把B塔的i个盘子移动到D塔；  
   这种移法可以保证满足hanoi的移动规则：小盘在上，而步数最少；

   由此可以推广：  
   设有n个盘和p个塔；  
   先在p塔模式下从A塔移动i个盘子到B塔；  
   再在p-1塔模式下从A塔把剩下的n-i个盘子移动到D塔；  
   最后在p塔模式下把B塔的i个盘子移动到D塔；  
   与之前的方法非常类似！
   
   现在我们可以写出状态转移方程：
   $f[n][p]=min{f[i][p]+f[n-i][p-1]}$
2. 至于高精度，如果有同学没有板子可以找CSDN[重载高精度的模版](https://blog.csdn.net/scanew/article/details/12841373)这篇帖子中的最后一段代码作为参考（但最好结合书本把代码写简洁一些）

本人最近才了解卡常这种奇妙的操作，所以在代码里应用了一些卡常  
其实并没有太大必要，但毕竟卡卡更健康嘛 呵呵
#### 终于上代码了：
```
#include<bits/stdc++.h>
#define R register//register 卡常神器 
using namespace std;
struct bignum{
	int n[110],l;
	bignum(){memset(n,0,sizeof(n)),l=1;}
	inline void read(){//inline 也常用于卡常 
		char ch=getchar(),s[5010];
		while(ch<48||ch>=58) ch=getchar();
		while(ch>=48&&ch<58) s[++l]=ch,ch=getchar();
		for(R int i=1;i<=l;++i) n[i]=s[l+1-i]^48;//多用 ++i，比 i++快了不少 
	}
	inline void print(){
		for(R int i=l;i>0;--i) putchar(n[i]+48);
	}
	inline int operator <(bignum y){
		bignum x=*this;
		if(x.l!=y.l) return x.l<y.l;
		for(R int i=x.l;i>0;--i)
			if(x.n[i]!=y.n[i]) return x.n[i]<y.n[i];
		return 0;
	}
	inline bignum operator +(bignum y){
		bignum t,x=*this;	R int i;
		for(i=1;i<=x.l||i<=y.l;++i){
			t.n[i]+=x.n[i]+y.n[i];
			if(t.n[i]>9) t.n[i]-=10,++t.n[i+1];
		}
		t.l= t.n[i]==1? i:i-1;
		return t;
	}
	inline bignum operator *(bignum y){
		bignum t,x=*this;
		t.l=x.l+y.l-1;
		for(R int i=1;i<=x.l;++i)
			for(R int j=1;j<=y.l;++j){
				t.n[i+j-1]+=x.n[i]*y.n[j];
				while(t.n[i+j-1]>9)
					t.n[i+j-1]-=10,++t.n[i+j];
			}
		if(t.n[t.l+1]) ++t.l;
		return t;
	}
}f[201][21],minN,one,two;//关于one、two：只是因为懒得打高精乘低精 
//高精的版子，这里用的是重载，会比函数快一些 
int k=0,n,p;
int readint(){
	int f=0;	char ch=getchar();
	while(ch<48||ch>=58) ch=getchar();
	while(ch>=48&&ch<58) f=(f<<3)+(f<<1)+(ch^48),ch=getchar();
	return f;
}//快读 
int main()
{
	one.n[1]=1,two.n[1]=2;//高精的1和2 
	for(int j=3;j<=20;++j) f[1][j]=one;//初始化只有一个盘的情况 
	for(int i=1;i<=200;++i) f[i][3]=f[i-1][3]*two+one;//初始化普通三塔的情况 
	for(int j=4;j<=20;++j)
		for(int i=2;i<=200;++i)
		{
			minN.l=100,minN.n[100]=1;
			for(int t=1;t<i;++t)
			{
				bignum tmp=f[t][j]*two+f[i-t][j-1];
				if(tmp<minN) minN=tmp;
			}
			f[i][j]=minN;
		}//DP的过程 
	//这里是把答案先预处理出来 
	n=readint(),p=readint();
	while(n||p)
	{
		printf("Case %d: ",++k);
		f[n][p].print(),putchar('\n');
		n=readint(),p=readint();
	}//询问、输出 
	return 0;
}
```
嗯 就是这样。  
PS：敲完这篇题解之后，总感觉还有些地方不够完善  
	有不对的地方敬请谅解！

---

## 作者：hovny (赞：1)

## [题面](https://www.luogu.org/problemnew/show/UVA10444)

求$p(3< p \le 20)$根杆子，$n(0\le n \le200)$个圆盘的最优解（规则和普通汉诺塔一样）

## 思路：

**递推**、**DP**

题目里其实也给出了一个的递推式，设$f[k][i]$表示$k$根杆子，$i$个圆盘的状态

> $f[k][i]=min\{2*f[k][j]+f[k-1][i-j]\},1\le j < i$

表示的意思是：

> 先把$j$个圆盘在$k$根杆子的情况下转移，再将剩下的$i-j$个圆盘在$k-1$根杆子的情况下转移

这样读懂了之后代码就很好写了

不过要注意的是：

**$ n\le 200 $**，在这种情况下，$ll$都爆了……，所以还是老实写个高精吧

Code：

```cpp
#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
#define ll long long
#define N 200
using namespace std;
struct node{
	int a[110],l;
	node operator+ (const node x) const{//其实重载个加法就非常方便了
		int L=max(l,x.l);node y;//L表示长度
		y.a[1]=0;
		for(int i=1;i<=L;i++) {
			y.a[i]+=a[i]+x.a[i];
			y.a[i+1]=y.a[i]/10;
			y.a[i]%=10;
		}
		if(y.a[L+1]) ++L;y.l=L;
		return y; 
	} 
}f[25][N+7],init;//init是一个单位的数，也就是1
int n,p,t;
inline node Min(register node a,register node b) {//比较大小
	if(a.l!=b.l) return (a.l<b.l)?a:b;
	register int t=a.l;
	while(a.a[t]==b.a[t]&&t) --t;
	return (a.a[t]<b.a[t])?a:b;
}
inline void Init() {//预处理一下
	int i,j,k;init.a[1]=1,init.l=1;f[3][1]=init;
	for(i=2;i<=N;i++) f[3][i]=(f[3][i-1]+f[3][i-1])+init;
	for(k=4;k<=20;k++) {
		f[k][1]=init;
		for(i=2;i<=N;i++) {
			f[k][i].l=INF;
			for(j=1;j<i;j++)
				f[k][i]=Min(f[k][i],(f[k][j]+f[k][j])+f[k-1][i-j]);
		}
	}
}
inline void Print(register int n,register int p) {
	int i;
	printf("Case %d: ",++t);
	if(!f[p][n].l) {puts("0");return;}
	for(i=f[p][n].l;i;i--)
		printf("%d",f[p][n].a[i]);
	puts("");
}
int main() {
	Init();
	while(~scanf("%d%d",&n,&p)&&p!=0) Print(n,p);//输出就好了
	return 0;
}
```



---

## 作者：0x00AC3375 (赞：0)

### 1. 题意
有一个包含 $n(n\le 200)$ 个圆盘以及 $p(p\le25)$ 个柱子的汉诺塔，输入 $n,p$ 的值，请求出至少需要多少次移动才能将全部圆盘从一个柱子移动到另一个柱子。

### 2. 汉诺塔初步
对于一个汉诺塔而言，移动圆盘需要遵循下面的规则：
- 每次只能移动 $1$ 个圆盘；
- 移动过程中，不允许将小盘放在大盘的下面。

### 3. 过程分析

对于一个包含 $n$ 个圆盘 $p$ 个柱子的汉诺塔，若暂时忽略最下方的圆盘，则求解问题的过程为：
1. 先将**最小的** $t$ 个圆盘转移到另一个柱子（这个柱子**被小盘占用了**，便不能再把其他的**较大的盘**放在上面）；
2. 将 $n-t$ 个圆盘利用其余的 $p-1$ 个柱子按照规则移动到另一个柱子上；
3. 重复步骤 1，将 $t$ 个圆盘利用全部 $p$ 个柱子，叠上去。

在上述过程中，求解 $t$ 和 $n-t$ 个圆盘的汉诺塔可以继续按照类似的过程向下递归。选择不同的 $t$ 值，总共的步数也不同，从中取能够使步数最小化的 $t$ 即为最优解。

设二元函数 $f(i,j)$ 表示有 $i$ 个盘和 $j$ 个柱子的情况，按照上述过程，可以得到转移方程

$$ f(i,j)=\min\limits_{1\le t<i}{\{2f(t,j)+f(i-t,j-1)\}}$$

按照上述方程，我们首先从最基础（也是最特殊）的情况入手：
- 对于一个只有 $3$ 个柱子的汉诺塔，如果有 $n$ 个圆盘，容易证明至少需要 $2^n-1$ 次移动，也即 

$${\forall} n\ge 0,f(n,3)=2^n-1$$

- 对于只有 $1$ 个圆盘的汉诺塔，不论有多少个柱子，均只需要 $1$ 次移动；

- 最重要的一点，盘的数量可以是零，因此需要特判！这时答案始终是零，也即

$${\forall} k\ge 3,f(1,k)=1,f(0,k)=0$$

这就是递归操作（动态规划）的初始条件。

### 4. 代码实现
如果有 $200$ 个盘子且只有 $3$ 个柱子，则需要移动 $2^{200}-1$ 次，即便是 `__int128` 类型也容不下，这里考虑使用 Java 的 BigInteger 存储数值，$O(n^3)$ 时间复杂度求出所有的答案，针对每一组数据用 $O(1)$ 的复杂度进行查询即可。

```java
import java.util.*;
import java.math.*;
public class Main
{
    public static BigInteger[][] f = new BigInteger[212][25];
    public static void main(String[] args)
    {
        for(int i=1;i<=210;i+=1) f[i][3]=BigInteger.valueOf(2).pow(i).subtract(new BigInteger("1"));
        for(int i=3;i<=23;i+=1) {
            f[1][i] = BigInteger.valueOf(1);
            f[0][i] = BigInteger.valueOf(0);
        }
        for(int j=4;j<=23;j+=1)
        {
            for(int i=2;i<=210;i+=1)
            {
                f[i][j]=BigInteger.valueOf(2).pow(210);
                for(int t=1;t<i;t+=1)
                {
                    BigInteger tmp = f[t][j].multiply(BigInteger.valueOf(2)).add(f[i-t][j-1]);
                    if(tmp.compareTo(f[i][j])<0) f[i][j]=tmp;
                }
            }
        }
        Scanner cin = new Scanner(System.in);
        for(int i=1;;i+=1)
        {
            int n = cin.nextInt(), p=cin.nextInt();
            if(n==0 && p==0) return;
            System.out.println("Case " + i + ": " + f[n][p]);
        }
    }
}
```

### 5. Extra
很多人一听到高精度第一想法就是 Python，但是笔者个人不推荐使用 Python 处理涉及到二维或多维数组的问题。虽然 Python 可以利用嵌套的 list 模拟多维数组，但这往往容易引起莫名其妙的 bug。

---

