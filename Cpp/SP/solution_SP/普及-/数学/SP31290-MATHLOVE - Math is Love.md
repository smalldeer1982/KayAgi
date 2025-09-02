# MATHLOVE - Math is Love

# 题解

## 作者：FFTotoro (赞：5)

这里提供一种解方程的做法。

首先推式子：

$\because\sum\limits_{i=1}^ki=n,$

$\therefore\frac{k(k+1)}{2}=n,$

$\therefore k^2+k=2n,$

根据一元二次方程求根公式，有

$\therefore k=\frac{-1\pm\sqrt{1+8n}}{2}$。

注意，因为这里 $k$ 是整数，所以 $\sqrt{1+8n}$ 是整数是有答案的必要条件，即 $1+8n$ 必须是完全平方数。

所以代码就很好写了。放代码：

```cpp
#include<iostream>
#include<cmath>
#define int long long // 记得开 long long
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        int x; cin>>x;
        int a=sqrt(1+8*x);
        if(a*a==1+8*x)cout<<(a-1>>1)<<endl; // 如果有解那么答案就是 (a-1)/2
        else cout<<"NAI\n"; // 无解情况
    }
    return 0;
}
```

---

## 作者：　　　吾皇 (赞：3)

**输入格式**

第一行 一个正整数T(1<=T<=100000)，表示有T组数据

第2-T+1行 每行一个正整数Y(1<=Y<=$3*10^9$)

**输出格式**

对于每个Y，如果有正整数k满足$\sum_{i=1}^k =y$，则输出k的值，否则输出NAI（换行）

### 题目分析
将$\sum_{i=1}^k =y$转化为(1+k)$\times$k$\div$2=y

再搞一下，得$k^2$+k=2$\times$y

现在有至少2种方法：1.解出k的值 2.利用sqrt下取整算出小于2y的最小平方数校验是否符合

### 代码（这里用的是第二种）
```
#include<bits/stdc++.h>
using namespace std;
long long y,p;//注意这里p要开longlong 不然p*p会炸
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&y);
		p=floor(sqrt(y*2));//这里向下取整
		if(y*2==p*(p+1)) printf("%d\n",p);//如果p满足上述式子，输出p的值
		else puts("NAI");//否则输出NAI
	}
}
```
### 顺带附上第一种
$$p=(-1+sqrt(1+8*y))/2;$$ 
显然可以强行类型转换

### 介绍一种暴力作法
```
#include<bits/stdc++.h>
using namespace std;
map<long long,int>q;
int t;
long long y;
int main(){
	for(long long i=1;i*i+i<=6000000000;i++) q[(i*i+i)/2]=i;//将范围内所有满足条件的都存入map
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&y);
		if(q.count(y)) printf("%d\n",q[y]);如果y在map中出现过，则输出对应的答案
		else puts("NAI");否则输出NAI
	}
}
```


---

## 作者：foxgirl_ckt1009 (赞：1)

# 思路
根据题目描述，$Y$ 是从 $0$ 到 $n$ 的数字之和。因此，我们可以使用等差数列求和公式来计算 $Y$ 的值。等差数列求和公式是 $(n(n+1))\div2$ 。因此，我们可以使用以下方法来计算 $n$ 的值：
# 步骤
1. 计算 $(n(n+1))\div2$ 的值。
2. 如果该值等于 $Y$ ，则 $n$ 的值为 $(n+1)\div2$ 。
3. 如果该值小于 $Y$ ，则 $n$ 不存在。
4. 如果该值大于 $Y$ ，则 $n$ 的值为$(-1+\sqrt{(1+8Y)})\times2$。

```
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int y;
        cin >> y;
        int n = (-1 + sqrt(1 + 8LL * y)) / 2;
        if (n * (n + 1) / 2 == y) {
            cout << n << endl;
        } else {
            cout << "NAI" << endl;
        }
    }
    return 0;
}
```
代码已测试，请放心食用！

---

## 作者：251Sec (赞：1)

水题。

似乎有人用解方程的写法，但实际上这题直接暴力打表就是 $O(\sqrt{y}+T)$ 的。可以通过。

枚举所有 $k$，将对应的 $y$ 算出来，然后存进表中即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;
unordered_map<ll, int> a;
int main() {
    scanf("%d", &t);
    ll j = 1;
    for (int i = 2; j <= 3e9; j += i, i++) {
        a[j] = i - 1;
    }
    while (t--) {
        ll y;
        scanf("%lld", &y);
        if (a[y]) printf("%lld\n", a[y]);
        else puts("NAI");
    }
    return 0;
}

```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/SP31290)   
一元二次方程裸题。      
首先，$\sum\limits^k_{i=1}i$ 就等于 $\frac{(1+k)k}{2}$。   
再拆一下括号：$\frac{k^2+k}{2}$。   
将其转换为一元二次方程：$\frac{1}{2}k^2+\frac{1}{2}k-y=0$。     
下一步，我们要去掉 $\frac{1}{2}$，如果加上，计算会变麻烦。        
我们可以提取公除数。    
所以，就有 $\frac{k^2+k}{2}-y=0$，这里的除以 $2$ 可以直接移动到 $-y$ 的部分，变成 $-2y$。   
最后的方程为：$k^2+k-2y=0$。    
我们回顾一下一元二次方程的求根公式：    
$\frac{-b\pm \sqrt{\color{red}{b^2-4ac}}}{2a}$    
其中，红色部分我们接下来用 $d$ 代替。    
这道题的 $y$ 肯定为一个正数，所以这个方程不存在无解的情况。    
那 ```NAI``` 的情况如果判断呢？   
最后的输出要求是一个**正整数**，所以我们只需要判断 $d$ 是不是一个完全平方数就可以。    
对于本题中的 $d$，我们可以简化一下。   
$b^2-4ac$ 带入数据为 $1^2-4\times1\times(-2y)$，即 $1-4\times1\times(-2y)$，我们拆开括号：$1-4\times1\times(-2)\times y$，把乘法的结果算出来：$1-(-8y)$。   
所以，$d$ 其实就等于 $1-(-8y)$。  
本题要输出正数根，所以 $\pm$ 就应该变成 $+$。   
要开 long long。    
CODE：   
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int t;
long long y,d,sq;
int main(void){
	cin>>t;
	while(t--){
		cin>>y;
		d=1-(-8*y);//算出b^2-4ac
		sq=sqrt(d);//平方根，向下取整
		if(sq*sq==d){//如果相乘还等于原来的结果，就是完全平方数
			cout<<(sq-1)/2;//输出正数根
		}else{
			cout<<"NAI";
		}
		cout<<endl;
	}
} 
```


---

## 作者：Steve_xh (赞：0)

# 题面

[题目传送门](https://www.luogu.com.cn/problem/SP31290)

**题目大意：**

给定 $T$ 个数，每次判断这个数是不是等于 $1+2+3+...+k$。是的话输出 $k$，不是的话输出 $\verb!NAI!$。

# 思路

~~（话说我第一次看到这个奇怪的求和符号还不知道是什么意思）~~

这道题纯枚举会超时，因为只有 $1s$，不过提前将所有可能的数算出来再判断也是可以的。这里介绍一种很多人都在用也很好用的方法。

根据等差数列求和公式可得：
$$1+2+3+...+k=\frac{(1+k)k}{2}$$
设给出的数 $n$ 是有解的，则：
$$n=(k+k^2)\div2$$
$$2n=k+k^2$$
$$k^2+k-2n=0$$
我们便可以转换并利用一元二次方程求根公式：
$$1k^2+1k+(-2)n=0$$
$$k=\frac{-1\pm\sqrt{1-4\times1\times(-2)n}}{2\times1}$$
但是 $k$ 肯定不能是负数的，所以：
$$k=\frac{\sqrt{8n+1}-1}{2}$$
再根据一元二次方程的无解条件，判断 $\sqrt{8n+1}$ 是否为整数就能判断无解的情况啦。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,y;
signed main(){
    ios::sync_with_stdio(false);//只有一秒，需要加上
    cin>>t;
    while(t--){
        cin>>y;
        double tmp=sqrt(8*y+1);//判断条件
        if(tmp==(int)tmp)//如果是整数
            cout<<((int)(tmp-1)>>1)<<"\n";//刚刚算出来的式子就是答案
        else//无解
            cout<<"NAI\n";
    }
    return 0;
}
```

---

## 作者：_xEr_ (赞：0)

## 先看题目

给定整数 $n$，问是否存在 $k$ 满足 $\large\sum_{i=1}^ki =n$。若有，输出 $k$，否则输出 ```NAI```。

共有 $t$ 次操作。

## 再想思路

先简化题目。  

$\large\sum_{i=1}^ki$ 即为 $\large\frac{(k+1)\times k}{2}$，等差数列求和嘛。之后我们便可以可以枚举 $k$，从而构造合法 $n$。

但那样空间显然受不了，怎么办？优化吗？  
不，我们可以用 `unordered_map`。

`unordered_map` 可以看作系统哈希。看名字就可以看出是无序版 `map`，他大部分操作自然和 `map` 也是一样的。

但 $k$ 枚举到什么时候是头呢？手算吗？  
不，我们可以 `if((k+1)*k/2>3*1e9)break;`。

这两种方法无疑是很适合分秒必争的赛场的。不要太多计算和思考，节省了一部分时间。程序效果、用时也与思考得到的结果一样。

## THE CODE
```cpp
#include<iostream>
#include<unordered_map>
using namespace std;
unordered_map<long long,int>a;
int main(){
	int t,y;
	cin>>t;
	for(long long k=1;k<=1e9;k++){
		if((k+1)*k/2>3*1e9)break;
		a[(k+1)*k/2]=k;
	}
	while(t--){
		cin>>y;
		if(a[y])cout<<a[y]<<endl;
		else puts("NAI");
	}
} 
```

---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP31290)

去博客食用，效果更加。

### [思路]

从题目描述可以看出，$Y$ 为 $0+1+2+\ldots+n$。所以我们可以使用等差数列求和公式 $\frac{n\times(n+1)}{2}$ 算出 $Y$。最后，我们可以使用这些方法算出 $n$ 的值：

- 算出 $\frac{n\times(n+1)}{2}$ 的值。

- 判断 $\frac{n\times(n+1)}{2} = Y$，$n$ 的值为 $\frac{n+1}{2}$。

- 判断 $\frac{n\times(n+1)}{2} < Y$，$n$ 不存在。

- 判断 $\frac{n\times(n+1)}{2} > Y$，$n$ 的值为 $2(-1+\sqrt{1+8Y})$。

### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<ctime>
#include<string>
#include<cstring>
#include<vector> 
using namespace std;
int t,n,y; 
int main()
{
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
        scanf("%d",&y);
        n=(sqrt(y*8+1)-1)/2;
        if((n*n+n)/2!=y)
            printf("NAI\n");
        if((n*n+n)/2==y)
            printf("%d\n",n);
    }
    return 0;
}
```

---

## 作者：End_of_time (赞：0)

[SP31290 MATHLOVE - Math is Love 题目传送门](https://www.luogu.com.cn/problem/SP31290)

看到题解里面各位大佬写的基本都是解方程的方法，作为一个数学不好的蒟蒻，我来提供一种简单易懂的方法。

首先我们要回忆一下自然数列的求和公式：

$$ {\large \sum_{i=1}^{n} i =\frac{n\times (n+1)}{2}} $$

那么，我们要做的就是，对于每一个数 $y$，我们需要找到一个 $n$，使得 

$$ {\large \frac{n\times (n+1)}{2} = y} $$

首先，我们把左边式子里的常数项乘到右边去，得：

$$ {\large {n\times (n+1)} = 2y} $$

然后，对两边进行同时开方，得：

$$ {\large \sqrt{n\times (n+1)} = \sqrt{2y}} $$

$ \because n \times (n + 1) = n^2 + n $

且 $n^2 \le n^2+n \le n^2+2n+1$

即 $ n^2 \le n \times (n+1) \le (n+1)^2 $

$ \therefore n \le \sqrt{n \times (n+1)} \le n + 1$

$ \therefore n \le \sqrt{2y} \le n + 1$

所以，我们只需要要对于每一个 $y$，先将其乘以 2，再开方并下取整，判断一下这个数符不符合条件，输出即可。

代码如下：
```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
int T, n;
inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	} while(c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c - '0');
		c = getchar();
	} return x * f;
} 
inline void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
} 
signed main() {
	T = read();
	while(T --) {
		n = read();
		n *= 2;
		int t = floor(sqrt(n));
		if(t * (t + 1) == n) write(t), puts("");
  		// 这里判断一下，因为有可能不能正好符合条件。
		else puts("NAI");
	} return 0;
} 
```

---

## 作者：Unnamed114514 (赞：0)

设答案为 $x$，由题意得：

$\sum\limits_{i=1}^xi=\dfrac{x(x+1)}{2}=n$

化简得 $x^2+x-2n=0$。

原方程 $a=1,b=1,c=-2n$。

利用求根公式：

$x=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}=\dfrac{-1\pm\sqrt{1+8n}}{2}$。

由于 $x$ 为整数，且 $\dfrac{1}{2},-1$ 均为整数，所以 $\sqrt{1+8n}$ 为整数；反之，则无整数解，输出 `NAI`。

因为 $x$ 为整数，而 $-1-\sqrt{1+8n}<-1<0$，所以显然分母应为 $-1+\sqrt{1+8n}$。

设 $p=\lfloor\sqrt{1+8n}\rfloor$，当 $p^2\ne1+8n$ 时，无整数解，输出 `NAI`；否则，输出 $\dfrac{p-1}{2}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		int p=sqrt(1+8*n);
		if(p*p==1+8*n)
			cout<<(p-1)/2<<endl;
		else
			puts("NAI");
	}
	return 0;
}
```

---

## 作者：Prolystic (赞：0)

## [原题目](https://www.luogu.com.cn/problem/SP31290)

不难发现原题目中要求达成的关系可以列为一个方程。按步骤将未知数 $k$ 解出来，步骤如下：

$\sum_{i = 1}^{k} i = y$

$\frac{(1+k)k}{2} = y$

$(1+k)k = 2y$

$k^2+k-2y = 0$

套求根公式：

$k = \frac{-1\pm \sqrt{1-4\times 1\times(-2y)}}{2\times 1}$

$k = \frac{-1\pm \sqrt{1+8y}}{2}$ 

因无复数参与运算情况下，$-1$ 减去任何数都应为负数，而负数的 $k$ 不符合本题题意，所以

$k = \frac{-1+\sqrt{1+8y}}{2}$

只需判断 $1+8y$ 是否为完全平方数即可。

时间复杂度 $O(T)$，可以很轻松地通过。

```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
int T;
int main()
{
    scanf("%d",&T);
    for(int i = 1;i<=T;i++)
    {
        long long Y;
        scanf("%lld",&Y);
        long long delta = sqrt(1+8*Y);
        if(delta*delta==1+8*Y)
        {
            printf("%lld\n",(delta-1)/2);
        }
        else
        {
            printf("NAI\n");
        }
    }
    return 0;
}

```

---

## 作者：infinities (赞：0)

[Blog](https://www.luogu.org/blog/209547/)

题意：给定t和t组数据，问每组数据中的n是否是1~x(x可以是任意数)的和

这是一道好题，用来练习简单数论和二分查找都是不错的，现在讲一下二分的思路(数论的思路我怕是不会qwq)：

1. 首先，我们套一下公式，知道了$1+2+3+....+x=x(x+1)/2$

2. 所以，我们先把n乘以二，这样只要寻找有没有一个整数x和x+1相乘等于n就可以了

3. 然后就轮到用二分的时候了，套板子就好，没什么好说的，只是不要用递归来算，可能会炸空间，用while循环模拟递归比较好

4. 核心代码：
```cpp
long long erfen(long long l,long long r,long long key){
    long long left=l,right=r;
    t=(l+r)/2;
    while(t*(t+1)!=key){
        t=(left+right)/2;
        if(t==p)return 0;
        if(t*(t+1)<key)left=t;else
        if(t*(t+1)>key)right=t;
        p=t;
    }
    return t;
}
```

5. 还有一点很重要，因为$x(x+1)=2*n$，所以我们把二分查找里的$r$设成$sqrt(n*2)$左右就行了，但是这个“左右”不能太小，我第一次设成$sqrt(n*2*20)$，WA掉了，一度绝望，后来改成$sqrt(n*2*2000)$就轻松AC了

6. 注意，$n\le10^9*3$，不开long long见祖宗

code:
```cpp
#include<bits/stdc++.h>//无奈图（万能头）文件 
long long t,p;//不开long long见祖宗 
long long erfen(long long l,long long r,long long key){
    long long left=l,right=r;
    t=(l+r)/2;
    while(t*(t+1)!=key){
        t=(left+right)/2;
        if(t==p)return 0;//如果陷入死循环（n不符合题意）返回 
        if(t*(t+1)<key)left=t;else
        if(t*(t+1)>key)right=t;
        p=t;
    }
    return t;
}//基本上二分板子，剩下的没什么讲的 
using namespace std;
int main(){
    ios::sync_with_stdio(0);//cin,cout快读 
    long long t,n,l=1,r,u;
    cin>>t;
    while(t--){//多组数据 
        cin>>n;
        n*=2;//要乘以二 
        r=sqrt(n*2000);//... 
        u=erfen(l,r,n);
        if(u)cout<<u<<"\n";else
        cout<<"NAI\n";//如果不符合题意，输出“NAI” 
    }
    //return 0;
}
```


---

