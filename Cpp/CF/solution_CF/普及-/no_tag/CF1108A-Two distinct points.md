# Two distinct points

## 题目描述

给定你数轴上的两条线段 $[l_1, r_1],[l_2, r_2]$（可能相交，重叠或重合）。你需要找到两个整数 $a,b$ 满足 $l_1 \leq a \leq r_1, l_2 \leq b \leq r_2$，且 $a\neq b$。你需要回答 $q$ 个询问，可能存在多种答案，输出任意一个即可。

## 样例 #1

### 输入

```
5
1 2 1 2
2 6 3 4
2 4 1 3
1 2 1 3
1 4 5 8
```

### 输出

```
2 1
3 4
3 2
1 2
3 7
```

# 题解

## 作者：Reywmp (赞：4)

捞一波题解。

------------

题目给了你2个区间，叫你找这个区间里的数。

我们从$l1 \le a \le r1$和$l2 \le b \le r2$中得知

>这是一个闭区间,所以a可以取l1,r1;b也可以取l2,r2.

那么又保证$l1<r1$且$l2<r2$得知

>$l1 \ne r1$,$l2 \ne r2$.

但是没有说到$l1 \ne l2$ $r1 \ne r2$

所以我们每次取$a=l1$,$b=r2$

因为$a \ne b$,所以我们特判l1是否等于r2,如果不等于,输出

如果等于就将b换成l2,因为$r2 \ne l2$所以此时$a \ne b$.

------------

核心代码如下：
```
while(t--)//注意多组数据
{
	int l1,r1,l2,r2;
	read(l1);read(r1);read(l2);read(r2);
	if(l1==r2)
		printf("%d %d\n",l1,l2);
	else
		printf("%d %d\n",l1,r2);
}
```

---

## 作者：kon_tori (赞：3)

拿到题目分析一下:
存在 ``q`` 组数据，每组数据有两个数 ``a`` 和 ``b`` ，其中 ``l1<=a<=r1`` ， ``l2<=b<=r2`` ，要求使 ``a!=b`` 且满足 ``l1<=a<=r1`` 且 ``l2<=b<=r2`` 的 ``a`` ， ``b`` 的值。

看到这里，我首先想到的是，如果 ``a`` 取 ``l1`` ， ``b`` 取 ``r2`` ，就可以最大限度的拉开 ``a`` ， ``b`` 之间的距离，从而使 ``a!=b`` ，然后自信满满的交了一份代码上去。

``code:``

```cpp
/* Author:light_chaser
   Online Judge:luogu */
  #include<bits/stdc++.h>
  using namespace std;
  int T;
  int l1,r1,l2,r2;
  
  inline int read(){
      register int s=0,w=1;
      register char ch=getchar();
      while(ch<'0'||ch>'9'){
          if(ch=='-')w=-1;
          ch=getchar();
      }
      while(ch>='0'&&ch<='9') 
      s=s*10+ch-'0',ch=getchar();
      return s*w;
  }//快读
  
  int main(){
      T=read();
      while(T--){
          l1=read(),r1=read();
          l2=read(),r2=read();
          cout<<l1<<" "<<r2<<"\n";
      }
      return 0;
  }  
```
结果是,``WA``在了``#2``点上。

仔细一想，忽略了当 ``l1=r2`` 的情况，此时会导致 ``a=b`` ，显然不行。考虑加上一组特判：当 ``l1=r2`` 时， ``a`` 取 ``l1`` ， ``b`` 取 ``l2`` ，结果 ``AC`` ， ``90ms`` 。

``code:``

```cpp
/* Author:light_chaser
   Online Judge:luogu */
  #include<bits/stdc++.h>
  using namespace std;
  int T;
  int l1,r1,l2,r2;
  
  inline int read(){
      register int s=0,w=1;
      register char ch=getchar();
      while(ch<'0'||ch>'9'){
          if(ch=='-')w=-1;
          ch=getchar();
      }
      while(ch>='0'&&ch<='9') 
      s=s*10+ch-'0',ch=getchar();
      return s*w;
  }
  
  int main(){
      T=read();
      while(T--){
          l1=read(),r1=read();
          l2=read(),r2=read();
          if(l1!=r2) cout<<l1<<" "<<r2<<"\n";
          else cout<<l1<<" "<<l2<<"\n";
      }
      return 0;
  }  
 
```

---

## 作者：FP·荷兰猪 (赞：1)

> 题意：给你两条线段，求出点a，b，是的它们分别属于这两条线段上且a!=b

分析与解：

题目中有说两条线段的长度都大于1，所以保证有解，不用再特判。

如果第一条线段的左端点不等于第二条线段的右端点，则分别输出第一条线段的左端点不等于第二条线段的右端点；否则，输出第一条线段的右端点和第二条线段的左端点。
****
代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int x1,y1,x2,y2;
    for (int i=1;i<=n;i++)//注意有多组数据！
    {
    	cin>>x1>>y1>>x2>>y2;
    	if (x1!=y2) cout<<x1<<" "<<y2<<endl;//判断第一条线段的左端点是否等于第二条线段的右端点
    	else cout<<y1<<" "<<x2<<endl;
    }
    return 0;
}
```

---

## 作者：wxwoo (赞：1)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/03/13/solution-cf1108a/)

******

[原题目链接](https://www.luogu.org/problemnew/show/CF1108A)

我们可以取两条线段的中点，若重合就让第二条线段的中点+1

$Q:$中点+1后不在线段上怎么办？

$A:$由于C++整数除法自动省略小数，也就是向下取整，若线段长度大于1，那么中点+1后一定不会超出线段，若线段长度为1，即$l+1=r$，那么$\left\lfloor\dfrac{l+r}{2}\right\rfloor=l$，所以中点$+1=r$，也不会超出线段，所以中点+1后无论如何都在线段上，符合题意

代码如下

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
inline void read(int &x)//快读，写不写无所谓
{
	char ch;
	int f=1;
	x=0;
	do
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}while(!('0'<=ch&&ch<='9'));
	do
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}while('0'<=ch&&ch<='9');
	x*=f;
}

int main()
{
	int q;
	read(q);//读入q
	while(q--)//循环q次，可换成for(int i=1;i<=q;i++)
	{
		int l1,r1,l2,r2;
		read(l1);
		read(r1);
		read(l2);
		read(r2);//读入l1,r1,l2,r2
        int a=(l1+r1)/2;
        int b=(l2+r2)/2;//取两条线段的中点
		printf("%d %d\n",a,(a==b?b+1:b));//若相等，输出b+1，反之输出b
	}
	return 0;
}
```

---

## 作者：guoyicheng_gg (赞：0)

这道题的思路很简单，由于题中说了一定有解，我们可以先把l1输出，然后从l2开始遍历，一直遍历到了r2，遍历到不等于l1的且符合题意解的即可输出(其实就是暴力了)

代码
```cpp
#include <bits/stdc++.h> //万能头 
using namespace std; //命名空间 
int main() {
	int T;
	cin >> T; //多组数据
	while (T--) { //遍历多组数据 
		int l1, r1, l2, r2; //依照题意命名变量
		cin >> l1 >> r1 >> l2 >> r2; //输入四个数
		cout << l1 << " "; // 先输出l1, 因为此方程一定有解
		for (int i = l2; i <= r2; i++) { //遍历l2到r2 
			if (i != l1) { // 找到第一个不等于l1的点 //判断 
				cout << i << endl; //输出找到的值 
				break; //找到值, 直接跳出 
			}
		} 
	} 
	return 0; //好习惯要养成 
}
 
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $q$ 次询问，每次询问给定四个数 $l_1,r_1,l_2,r_2$。对于每次询问，找到两个数 $a,b$，使得 $l_1\leqslant a\leqslant r_1,l_2\leqslant b\leqslant r_2$ 且 $a\neq b$。

**数据范围：$1\leqslant q\leqslant 500,1\leqslant l_1,r_1,l_2,r_2\leqslant 10^9,l_1<r_1,l_2<r_2$。**
## Solution
我们看是否有 $l_1=l_2$，如果有的话那么 $a=l_1,b=r_2$，否则就可以 $a=l_1,b=l_2$。这方法很智障，但可以保证它是满足要求的。
## Code
```cpp
int n;

int main() {
	getint(n);
	while(n--) {
		int l1, r1, l2, r2;
		getint(l1), getint(r1), getint(l2), getint(r2);
		if(l1 == l2)	writeint(l1), putchar(' '), writeint(r2), putchar('\n');
		else	writeint(l1), putchar(' '), writeint(l2), putchar('\n');
	}
	return 0;
}
```

---

## 作者：Hiraeth (赞：0)

不明白现有题解里面为什么都说得那么复杂

这不是道水题吗。。。

寻找数对a,b分别属于两个不同的区间并且a,b不等

那么我们令a,b分别为左端点 如果a=b 那么我们令其中一个为右端点即可

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l1,l2,r1,r2,q;
long long p1,p2;
int main(){
	scanf("%lld",&q);
	for (int i=1;i<=q;i++) {
		scanf("%lld%lld%lld%lld",&l1,&r1,&l2,&r2);
		p1=l1;
		p2=l2;
		if (p1==p2) p2=r2;
		printf("%lld %lld\n",p1,p2); 
	}
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

第一个线段取左端点，第二个线段如果左端点与第一个线段相同就取左端点+1，否则取左端点
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};


int main(void)
{
    rg int n = fast_IO::read();
    while (n--)
    {
        rg int l = fast_IO::read(), r = fast_IO::read(), l2, r2;
        fast_IO::write(l); putchar(' ');
        l2 = fast_IO::read(), r2 = fast_IO::read();
        if (l2 == l)++l2;
        fast_IO::write(l2); putchar('\n');
    }
    return 0;
}

```

---

