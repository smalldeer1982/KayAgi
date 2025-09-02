# Discounts

## 题目描述

输入n个整数($a_1...a_n$)和 $m$ 个整数( $q_1...q_m$ )。求在去掉第 $q_i$ 大的数字后，$n-1$ 个整数的和。

## 说明/提示

样例中，输入3，去掉数组中第3大的整数7，剩下的数字和为27；输入4，去掉数组中第4大的数字4，和为30。

## 样例 #1

### 输入

```
7
7 1 3 1 4 10 8
2
3 4
```

### 输出

```
27
30
```

# 题解

## 作者：kon_tori (赞：3)

### 题意
有$\texttt{n}$个数($\texttt{a1}$，$\texttt{a2}$，$\texttt{a3}$……$\texttt{an}$)，
对它们的和执行$\texttt{m}$次操作：每次从中减去第$\texttt{h}$大的数，输出每次处理的结果。

### 思路
先求这$\texttt{n}$个数的和，然后使用$\texttt{sort}$对这些数进行升序排序，最后执行这$\texttt{m}$次操作。

**注意：不开$\texttt{long long}$见祖宗；数组大小一定要开够。**

### 代码实现
$\texttt{code:}$
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  #define ll long long//本题数据较大，一定要开long long，不然在#3就wa了 
  using namespace std;
  ll n;
  ll a[300001];//根据数据范围开数组
  ll m;
  ll h;
  ll sum1=0;//n个数的和
  
  template<typename T>void read(register T& a){
      T x=0,f=1; 
      register char c=getchar();
      while(!isdigit(c)){
          if(c=='-')f=-1; 
          c=getchar();
      }
      while(isdigit(c))
      x=(x<<1)+(x<<3)+c-'0',c = getchar();
      a = x*f;
  }//快读
  
  int main(){
      read(n);
      for(ll i=1; i<=n; i++){
          read(a[i]);
          sum1+=a[i];
      }//读入，求和
      sort(a+1,a+n+1);//排序
      read(m);
      while(m--)/*执行m次操作*/{
          read(h);
          cout<<sum1-a[n-h+1]<<"\n";//每次减去第h大的数
      }
      return 0;
  }
```

### 后记&闲话
~~蒟蒻在你谷更新后的第一篇题解~~

**管理员们辛苦了！**

~~期末考试rp++！~~

蒟蒻的第$\texttt{10}$篇题解，望通过。

---

## 作者：zplqwq (赞：1)

**题目思路**：

我们可以先预处理出所有数的和，记录在变量 $ret$ 里，然后再将数组正序排序，最后在输出时输出 $ans-a_{n-ret+1}$ 即可。最后记得开 `long long`。

代码：

```cpp
      for(int i=1; i<=n; i++)
      {
          cin>>a[i];
          ret+=a[i];
      }
      sort(a+1,a+n+1);
      cin>>m;
      while(m--)
      {
          cin>>q;
          cout<<ret-a[n-q+1]<<endl;
      }
```

---

## 作者：wuwenjiong (赞：0)

## 题意：
给出 $n$ 个整数，在依次读入 $m$ 个数，分别是 $x_1,x_2...x_m$ ，对于每个数，输出这 $n$ 个数之和与第 $x_i$ 大的数的差。
## 思路：
因为输入的 $n$ 个数并不保证升序或降序，所以还要排序一遍。这里就可以用到快排。使用快排时，需要用万能头文件或者下面这个头文件：
~~~
#include<algorithm>
~~~
另外考虑到是第 $x_i$ 大，建议降序排，但快排默认是升序排，所以就要加上它：
```cpp
bool cmp(int x,int y){
	return x>y;
}
```
接下来就好办了，输入 $n$ 个数时，记录下它们的和，然后将数组排序一下，按照题意输出即可。

完整代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long s,x;
int a[300005];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	int n,m,i,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];
	}
	sort(a+1,a+n+1,cmp);
	cin>>m;
	while(m--){
		cin>>k;
		cout<<s-a[k]<<endl;
	}
	return 0;
}
```
谢谢！！！

---

## 作者：Da_un (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1132B)
题目大意都应该能懂，下面直接讲思路。

按照题目说的顺序写代码即可，先输入 $n$ 个整数，用一个累加器 ```sum``` 累加 $n$ 个整数，然后将这 $n$ 个整数从大到小排序后再输入 $m$ 个整数，对于每次输入的数 $q$，用累加器减去数 $q$ 作为下标所对应的数并输出即可。

要注意的是：

- 看数据范围，累加器用 ```int``` 的话会爆空间，所以必须开 ```long long```  才可通过此题。

- 为了方便，输入 $n$ 个整数时，从下标 $1$ 开始，这样进行完排序后，$a[q]$ 所对应的数即为第 $q$ 大的数。~~这样看着舒服一点~~

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[300005];
int n,m,q;
long long sum;
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	scanf("%d",&m);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m;i++){
		scanf("%d",&q);
		printf("%lld\n",sum-a[q]);
	}
	return 0;
}
```
完结撒花~~

---

## 作者：atarashiTLE (赞：0)

~~最水B题，没有之一~~

### 思路：
排序后直接将累计的和减去$q_i$。

**不开`longlong`见祖宗！**

----
### 实现以及说明：
先放代码。
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,q,a[300010],tmp,ans;
signed main(){
   cin>>n;
   for(int i=0;i<n;i++)
      cin>>a[i],ans+=a[i];//累加和
   sort(a,a+n);//正序排序
   cin>>q;
   for(int i=0;i<q;i++){
      cin>>tmp;
      cout<<ans-a[n-tmp]<<endl;//①
   }
   return 0;
}
```
①：因为是正序排序，所以将`a`数组反着用，这样就不用麻烦去写`cmp`函数

---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$。有 $q$ 次询问，每次询问给定一个数 $x$。对于每次询问，求出数组中去掉一个第 $x$ 大的数字后数组内剩余的数字的总和。

**数据范围：$2\leqslant n\leqslant 3\times 10^5,1\leqslant a_i\leqslant 10^9,1\leqslant m<n,2\leqslant q_i\leqslant n$。**
## Solution
预处理出所有数的总和，直接排序之后每次询问就可以直接输出总和减去第 $x$ 大的数后的值了，就是我们要求的剩余的数字的总和。
## Code
```cpp
int n, a[300007], q;
ll sum;

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	getint(n);
	_for(i, 1, n) {getint(a[i]); sum += a[i];}
	sort(a + 1, a + n + 1, cmp);
	getint(q);
	while(q--) {
		int x;
		getint(x);
		ll ans = sum - a[x];
		writell(ans), putchar('\n');
	}
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

从小到大排序，对于每个$q$输出$sum-a_{n-q+1}$
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 3e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N];

int main(void)
{
    rg ll ans = 0;
    rg int n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)ans += (a[i] = fast_IO::read());
    sort(a + 1, a + n + 1);
    rg int m = fast_IO::read();
    for (rg int i = 1; i <= m; ++i)
    {
        rg int x = fast_IO::read();
        fast_IO::write(ans - a[n - x + 1]); putchar('\n');
    }
    return 0;
}
```


---

