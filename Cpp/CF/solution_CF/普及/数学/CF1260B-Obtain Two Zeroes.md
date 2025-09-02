# Obtain Two Zeroes

## 题目描述

You are given two integers $ a $ and $ b $ . You may perform any number of operations on them (possibly zero).

During each operation you should choose any positive integer $ x $ and set $ a := a - x $ , $ b := b - 2x $ or $ a := a - 2x $ , $ b := b - x $ . Note that you may choose different values of $ x $ in different operations.

Is it possible to make $ a $ and $ b $ equal to $ 0 $ simultaneously?

Your program should answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example two operations can be used to make both $ a $ and $ b $ equal to zero:

1. choose $ x = 4 $ and set $ a := a - x $ , $ b := b - 2x $ . Then $ a = 6 - 4 = 2 $ , $ b = 9 - 8 = 1 $ ;
2. choose $ x = 1 $ and set $ a := a - 2x $ , $ b := b - x $ . Then $ a = 2 - 2 = 0 $ , $ b = 1 - 1 = 0 $ .

## 样例 #1

### 输入

```
3
6 9
1 1
1 2
```

### 输出

```
YES
NO
YES
```

# 题解

## 作者：幻想繁星 (赞：4)

## CF1260B 题解
首先，我们把两种操作合并来看，都是一个数减 $x$，另一个数减 $2x$，即两个数一共减 $3x$，而 $x$ 又一定是整数，所以如果 $a$ 和 $b$ 的和不是 $3$ 的倍数，那永远也不可能操作成功。

------------

但仅仅是怎么简单吗？当然不会，比如 $1$ 和 $8$ 的和也是 $3$ 的倍数，但是很明显不可能操作成功，所以我们还要考虑 $a$、$b$ 最多每次拉开 $x$ 的差距，不妨把所有操作的 $x$ 看作 $1$，考虑极端情况一直执行一种相同的操作，即 $a$、$b$ 中的较大数每次比较小数多减 $1$，共可操作较小数次，也就是说较大数最多减较小数的 $2$ 倍。所以当较大数大于较小数的 $2$ 倍时，也永远不可能操作成功。

------------

总结：本题仅需判断 $a$ 和 $b$ 的和是否是 $3$ 的倍数并且 $a$、$b$ 中的较大数是否小于等于较小数的 $2$ 倍即可。


------------

代码如下：
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;//使用命名空间 
int main()//主函数 
{
	int n,a,b;//定义 
	cin>>n;//输入 
	for(;n--;)//循环n次 
	{
		cin>>a>>b;//输入 
		if(min(a,b)*2<max(a,b)||(a+b)%3) cout<<"NO"<<endl;//不符合条件（a+b为3的倍数以及较大数不大于较小数的两倍）输出NO（记得换行） 
		else cout<<"YES"<<endl;//符合条件输出YES并换行 
	}
    return 0;//结束 
}
```

---

## 作者：Rainbow_qwq (赞：3)

Codeforces Div.2 B题。~~我居然想了十多分钟~~

[CF1260B Obtain Two Zeroes](https://www.luogu.com.cn/problem/CF1260B)

# 思路

可以把题目看做这样：每次操作，可以把一个数$-1$，另一个数$-2$，最后要把两个数都变成$0$。

可以发现：每次操作总共都减去$3$。

所以如果$(a+b)\ \text{mod}\ 3\ne 0$那肯定不行。

还有，如果一直把较小数$-1$，较大数$-2$，这样较大数还是不能变为$0$，也不行。

也就是说$a\times 2<b$就不行。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
bool work()
{
	int a=read(),b=read();
	if(a>b)swap(a,b);
	if(a*2<b)return 0;
	return (a+b)%3==0;
}
signed main()
{
	int n=read();
	while(n--)
    	if(work())puts("YES");
        else puts("NO");
    return 0;
}
```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1260B) & [CF链接](http://codeforces.com/problemset/problem/1260/B)

## 思路分析：

不妨设 $a+b=c$，那么要使 $a=b=0$，那么 $3x$ 就要等于 $c$。

所以如果 $(a+b)\bmod 3 \ne 0 $，就无法使 $a=b=0$。

但这样还不行，因为每次把 $\max(a,b)$ 减去 $2x$，把 $\min(a,b)$ 减去 $x$，那么如果 $\min(a,b)<\max(a,b)/2$，那也是不满足条件的。

## 代码：

```cpp
#include<iostream>
using namespace std;
int T,a,b;
int main(){
	cin>>T;
	while(T--){
		cin>>a>>b;
		if((a+b)%3==0&&min(a,b)>=max(a,b)/2){//判断 
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：jasonshen_ (赞：0)

我们知道，有两次操作：

> $a=a-x,b=b-2\times x(x>0)$
>
> $a=a-2\times x,b=b-x(x>0)$

我们知道，每次 $a+b$ 总共都减了 $3x$ 。

所以，我们首先需要判断是否 $a+b$ 是 $3$ 的倍数就可以了。

于是，我们写出了一个简单的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		if((a+b)%3!=0)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}

```
但是，并没有正确，不然这也不是黄题了。

我们一定是少判断了什么，我们看下面这个样例：

如果 $a=1 b=10001$ 我们上面的代码会输出 ``YES ``。但是，我们知道，一定是不可以的。

所以，我们还需要判断一下 $min(a,b)\times 2$ 和 $max(a,b)$ 的大小就可以了，因为如果我们一直让最小数减小，最大数减大，所以如果是上面那种情况，一定是无法正确的。

那么这样的话，只需要写几个 ``if`` 就可以了。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&a,&b);
		if((a+b)%3!=0)printf("NO\n");
		else{
			if(min(a,b)*2<max(a,b))printf("NO\n");
			else printf("YES\n");
		}
	}
	return 0;
}
```


---

## 作者：LBYYSM_123 (赞：0)

### 题意
给你两个正整数 $a$ 和 $b$。你可以对他们两个进行 $2$ 种操作：

* $a=a-x,b=b-2x$
* $a=a-2x,b=b-x$
  

求是否有一种方式能使得 $a$ 和 $b$ 同时等于 $0$。
### 思路
从等式可知，在每一种操作中，正整数 $a$ 和 $b$ 都总共减去了 $3x$,要想他们同时等于 $0$，那么它们的和必须是 $3$ 的倍数。同时也能发现，$a$ 不能大于 $2 \times b$，$b$ 也不能大于 $2 \times a$。（否则即使一直进行操作，它们也不能化为 $0$）。即：
$$\begin{cases}
a+b\equiv0\pmod3\\
b\leq 2 \times a\\
a\leq 2 \times b\\
\end{cases}
$$ 
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
void work(int T){
	if(T==0) return;
	cin>>a>>b;
	((a+b)%3==0&a<=2*b&&b<=2*a)?(puts("YES")):(puts("NO"));
	work(T--);
}
int main(){
	int T;
	cin>>T;
	work(T);//个人以为递归比较优雅
	return 0;
} 
```


---

## 作者：yzy041616 (赞：0)

[题目传送门](/problem/CF1260B)

## Part.1 题目

有 $n$ 组数据，每组数据给你两个数 $a$ 和 $b$，然后每个操作可以选一个**正整数** $x$，然后分别将 $a,b$ 减掉 $2x,x$，或者分别将 $a,b$ 减掉 $x,2x$。问你能不能经过有限步操作将 $a$ 和 $b$ 都变成 $0$。

## Part.2 思路

如果可以，那么这些操作里面“分别将 $a,b$ 减掉 $2x,x$”的这一类可以合并成一步：分别将 $a,b$ 减掉 $2X,X$，其中 $X$ 为所有的 $x$ 之和。

同样，“分别将 $a,b$ 减掉 $x,2x$”的这一类也可以合并成一步：分别将 $a,b$ 减掉 $Y,2Y$，其中 $Y$ 为所有的 $x$ 之和。

条件里的“$x$ 是正整数”这一条就转化成了“$X,Y$ 都是自然数”。（因为某一类的操作可以不做，所以等于 $0$ 也是可以的）

现在可以开始判断了。首先，如果要使 $a,b$ 都为 $0$，那么一定有 $a=2X+Y$ 和 $b=2Y+X$。我们把 $X,Y$ 当作未知数解一下，得到 $X=\dfrac{2a-b}{3},Y=\dfrac{2b-a}{3}$。所以 $\dfrac{2a-b}{3}$ 和 $\dfrac{2b-a}{3}$ 都得是自然数。

要想 $\dfrac{2a-b}{3}$ 和 $\dfrac{2b-a}{3}$ 都是自然数，我们需要：

+ $2a-b\equiv0\pmod 3$
+ $2b-a\equiv0\pmod 3$
+ $2a-b\geq0,2b-a\geq0$

由于 $2a-b\equiv2a-b-(3a-3b)\equiv2b-a\pmod3$，我们只需要 $2a-b\equiv0\pmod3$ 就行了。又因为 $(2a-b)+(a+b)=3a\equiv0\pmod3$，所以我们只需判断 $a+b\equiv0\pmod3$。

综上，要想 $a,b$ 都等于 $0$，有三个条件：

+ $a+b\equiv0\pmod3$
+ $2a\geq b$
+ $2b\geq a$

## Part.3 代码

```cpp
#include<iostream>
using namespace std;
int main(){
	int n;cin>>n;
	while(n--){//我在这里用了反向判断的方式，避免一行过长。
		int a,b;cin>>a>>b;
		if((a+b)%3){cout<<"NO\n";continue;}
		if(a>b+b||b>a+a)cout<<"NO\n";
		else cout<<"YES\n";
	}
}
```

---

## 作者：ivyjiao (赞：0)

## 题意：

给你两个正整数 $a,b$。你可以对他们两个进行 $2$ 种操作：

1. $a=a-x,b=b-2 \times x(x>0)$
2. $a=a-2 \times x,b=b-x(x>0)$

可以看出，两种操作，$a$ 和 $b$ 最终都共减去 $3x$，所以只需要判断 $a+b$ 是否为 $3$ 的倍数即可。

当然，$a$ 不能大于 $2 \times b$，否则即使全部执行 $2$ 操作，$a$ 也减不完。$b$ 也不能大于 $2 \times a$，否则即使全部执行 $1$ 操作，$b$ 也减不完。

代码：

```cpp
#include<iostream>
using namespace std;
int t,a,b;
int main(){
    cin>>t;
    while(t--){
        cin>>a>>b;
        if((a+b)%3==0&&a<=2*b&&b<=2*a) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
```


---

