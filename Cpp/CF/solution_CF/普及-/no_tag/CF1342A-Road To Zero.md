# Road To Zero

## 题目描述

You are given two integers $ x $ and $ y $ . You can perform two types of operations:

1. Pay $ a $ dollars and increase or decrease any of these integers by $ 1 $ . For example, if $ x = 0 $ and $ y = 7 $ there are four possible outcomes after this operation: 
  - $ x = 0 $ , $ y = 6 $ ;
  - $ x = 0 $ , $ y = 8 $ ;
  - $ x = -1 $ , $ y = 7 $ ;
  - $ x = 1 $ , $ y = 7 $ .
2. Pay $ b $ dollars and increase or decrease both integers by $ 1 $ . For example, if $ x = 0 $ and $ y = 7 $ there are two possible outcomes after this operation: 
  - $ x =             -1 $ , $ y = 6 $ ;
  - $ x = 1 $ , $ y = 8 $ .

Your goal is to make both given integers equal zero simultaneously, i.e. $ x = y = 0 $ . There are no other requirements. In particular, it is possible to move from $ x=1 $ , $ y=0 $ to $ x=y=0 $ .

Calculate the minimum amount of dollars you have to spend on it.

## 说明/提示

In the first test case you can perform the following sequence of operations: first, second, first. This way you spend $ 391 + 555       + 391 = 1337 $ dollars.

In the second test case both integers are equal to zero initially, so you dont' have to spend money.

## 样例 #1

### 输入

```
2
1 3
391 555
0 0
9 4```

### 输出

```
1337
0```

# 题解

## 作者：SpeedStar (赞：3)

### 算法分析
对于这个问题只需考虑以下两种情况：
1. 如果$a+a\leqslant b$，我们必须执行$x+y$次第一个操作，所以答案是$(x+y)*a$；
2. 如果$a+a>b$，我们必须执行$min(x,y)$次第二个操作和$|x-y|$次第一个操作，所以答案是$min(x,y)*b+|x-y|*a$。

### C++代码
```cpp
#include <iostream>
#define int long long

using namespace std;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while (t--) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		if (a + a <= b) cout << (x + y) * a << '\n';
		else cout << min(x, y) * b + abs(x - y) * a << '\n';
	}
	
	return 0;
}
```

PS：必须开$long\ long$

---

## 作者：do_while_false (赞：1)

【大体思路】

我们为方便思考，要确保 $x<y$ ，所以如果 $x>y$ 时，就 ```swap``` 一下即可。

当 $x<y$ 时，我们显然有两个最优的操作。

- 将两个数同时用 $b$ 代价向下削直到 $x$ 变为 $0$ 。然后再用 $a$ 代价削 $y-x$ 次，操作的代价是 $b\times x+a\times (y-x)$

- 全都单独削，代价 $a\times x+a\times y$

将这两个代价算出来，最小值即为答案。

复杂度 $O(1)$

【代码】

~~这么简单就不写代码了，~~ 不会写的可以看看别的大大的代码哦、

---

## 作者：添哥 (赞：0)

## 十年OI一场空，不开 $long long$ 见祖宗！
我因为没开 $long long$ 所以被卡了/kk（人傻常数大）

$x$ ， $y$ ， $a$ ， $b$ 的上限都是$10^9$ ， $int$ 勉强存的下，但是要把它们乘起来的话就会炸（警示后人）

除此以外此题还是挺简单的（怎么CF的题都是恶评……）。
## 好了，扯淡完毕，下面正式讲思路
我们知道，花 $b$ 的代价珂以一次让 $x$ 和 $y$ 都减 $1$ ，但是如果 $b>2a$ 的话这种方案肯定不划算，直接输出 $(x+y)*a$ 就好。

否则的话我们就取较小的那个与 $b$ 的积，再加上较大的那个与较小的那个差和 $a$ 的积就好了

**另外,注意换行**

## AC代码
```
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)//最近稀饭上了while输入法
    {
        long long x,y,a,b;//开long long
        cin>>x>>y>>a>>b;
        if(b>a*2)//特判
        {
            cout<<(x+y)*a<<endl;
        }
        else
        {
            if(x>y)
            {
            	cout<<y*b+(x-y)*a<<endl;
			}
			else
            {
            	cout<<x*b+(y-x)*a<<endl;
			}
        }
    }
    return 0;
}
```
## ~~打字很累~~，求通过，求点赞

---

## 作者：Into_qwq (赞：0)

因为要使得$x$和$y$最终都变成0，所以有两种操作：

1.将$x$，$y$分别进行进行$x$次a操作和$y$次a操作，此时总花费为$a\times (x+y)$

2.将x，y进行$min(x,y)$次b操作，再进行 $\left|x-y\right|$ 次a操作，总花费为$b\times min(x,y)+a\times\left|x-y\right|$


解释：第一个很明显了，第二个就是把其中一个离0较小的数变成0

如果把较大数变成0，则进行了$max(x,y)$次b操作,显然$max(x,y)\leqslant min(x,y)$

然后都要进行$\left|x-y\right|$次a操作



------------


当$x<y$时，第二种花费为$x\times b + (x-y)\times a$

两种花费的差为$\left|2y\times a-y\times b\right|$

把 $y$ 提出来，得费用为$y\times\left|1\times a- b \right|$

当$x<y$不成立时，同理

设$2\times a-b$为$w$

所以就可以得到

当$w<0$时选择第一种

当$w=0$时，两种操作一样

当$w>0$是，选择第二种

代码就不放了

**完结撒花**

---

## 作者：lingfunny (赞：0)

## 题目分析
首先看数据范围:
$$0\le x,y,\le10^9$$
$$1\le a,b\le10^9$$
最坏情况下，花费应该是
$$\max(|x|,|y|)\times\max(a,b)$$
显然爆```int```，肯定是要用```long long```了。

接下来，试想一下，要什么情况下将$x,y$同时$+1$或$-1$比较赚呢？自然要满足一下两个条件：
- $x,y$ 同号（即同是正数或同是负数）因为如果异号的话，岂不是拆东墙补西墙？
- $2\times a\le b$ 这是当然的，因为如果$2\times a> b$，就不如直接变成两次$+1$或者两次$-1$。

所以当$x,y$同号的时候，可以让$x,y$ 时$+1$或者$-1$直到其中某个数等于$0$。其实就是一个简单的贪心。

其他情况下，自然是让$x,y$ 单独$+1$或者$-1$比较划算，也是唯一可行的方案。

所以接下来，就可以愉快的分类了。还没有看懂的话可以看代码~
## 上代码

```cpp
#include <cstdio>

int t;
long long x,y,a,b;
long long cost;

inline int read();
inline int swap(long long &x,long long &y){long long tmp=x;x=y;y=tmp;}
inline long long abs(long long x){return x<0?-x:x;}

int main(){
	t=read();
	while(t--){
		cost=0;
		x=read();y=read();a=read();b=read();
		if(a*2<b)b=a*2;							//如果a*2<b，就可以把b的花费变成两次a的花费
		if(x<=0 && y<=0 || x>=0 && y>=0){		//如果同号
			x=abs(x);y=abs(y);					//如果是负数，可以当做两个正数处理
			if(x>y)swap(x,y);					//让x<=y，比较好处理
			y-=x,cost=b*x;						//同时-1，直到x=0，这时候y=y-x，花费就是b*x
			cost += a*y;						//最后将剩余的y用a操作-1
		} else {								//如果异号，自然不能用b操作，避免拆东墙补西墙
			x=abs(x);y=abs(y);					//x要做abs(x)次a操作，y要做abs(y)次a操作
			cost = x+y;
			cost *= a;							//计算结果
		}
		printf("%lld\n",cost);
	}
    return 0;
}

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
```

---

## 作者：do_while_true (赞：0)

方便判断，假定 $x<y$。有两种方式可能为最优的:

1. 全用 1 操作，花费 $a*x+a*y$
1. 用 2 操作把 $y$ 清零，再用 1 操作把 $x$ 清零，花费 $b*x+a*(y-x)$

对着两个取 $\min$ 输出即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,x,y,a,b;
long long ans1,ans2;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>x>>y>>a>>b;
		if(x>y) swap(x,y);
		ans1=1ll*a*x+1ll*a*y;
		ans2=1ll*b*x+1ll*a*(y-x);
		printf("%lld\n",min(ans1,ans2));
	}
	return 0;
}
```


---

