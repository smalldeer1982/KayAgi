# [GCJ 2014 #1C] Part Elf

## 题目描述

Vida 说她是半精灵：她的祖先中至少有一个是精灵。但她不知道这个精灵是她的父母（1 代之前）、祖父母（2 代之前），还是更久远的祖先。帮她找找看吧！

成为半精灵的方式大致与你想象的一样。精灵、人类以及半精灵的孩子都是通过两个父母结合而诞生的。如果一位父母的精灵血统是 $\frac{A}{B}$，另一位是 $\frac{C}{D}$，那么他们的孩子的精灵血统将是 $\frac{(A/B + C/D)}{2}$。例如，如果一个精灵血统是 $\frac{0}{1}$ 的人与一个精灵血统是 $\frac{1}{2}$ 的人生了孩子，那么这个孩子的精灵血统将是 $\frac{1}{4}$。

Vida 确信一点：在 40 代之前，她有 $2^{40}$ 位不同的祖先，而且每一位的精灵血统都是 $\frac{1}{1}$ 或 $\frac{0}{1}$。

Vida 说她的精灵血统是 $\frac{P}{Q}$。请告诉她，若她的精灵血统真的是 $\frac{P}{Q}$，那么她家族中最少多少代之前可能出现过一位 $\frac{1}{1}$ 的纯精灵祖先。如果不可能拥有精确为 $\frac{P}{Q}$ 的精灵血统，请告诉她这是不可能的！


## 说明/提示

请注意，第五个样例数据并不满足 Small 数据集的限制。即使你未能正确解出它，也可能已经正确解决了 Small 数据集。

**样例解释**

在第一个样例中，Vida 可以拥有一位 $\frac{1}{1}$ 的父母和一位 $\frac{0}{1}$ 的父母。也就是说，她的家族中 1 代之前就可能有一位纯精灵祖先，因此答案是 $1$。

在第二个样例中，Vida 的父母可以是一个 $\frac{1}{1}$ 的精灵和一个 $\frac{1}{2}$ 的精灵。那么她的家族中也可以在 1 代之前出现纯精灵祖先，因此答案是 $1$。

在第三个样例中，Vida 的父母可以是一个 $\frac{0}{1}$ 的人类和一个 $\frac{1}{2}$ 的精灵。而这个 $\frac{1}{2}$ 的精灵父母可以是一个 $\frac{1}{1}$ 的精灵和一个 $\frac{0}{1}$ 的人类。那么家族中可能在 2 代之前出现纯精灵祖先，因此答案是 $2$。

在第四个样例中，如果你的 40 代祖先都只可能是 $\frac{0}{1}$ 或 $\frac{1}{1}$ 的精灵，那么精确拥有 $\frac{2}{23}$ 的精灵血统是不可能的。

**注意**

是的，Vida 的祖先非常之多。如果你觉得这个设定最不现实，请重新阅读有关精灵的部分。

## 限制条件

- $1 \leq T \leq 100$。

### Small 数据集（8 分）

- 时间限制：~~60~~ 3 秒。
- $1 \leq P < Q \leq 1000$。
- $P$ 与 $Q$ 互质，即 $\frac{P}{Q}$ 是最简分数。

### Large 数据集（12 分）

- 时间限制：~~120~~ 5 秒。
- $1 \leq P < Q \leq 10^{12}$。
- $P$ 与 $Q$ 不一定互质，即 $\frac{P}{Q}$ 不一定是最简分数。

翻译由 ChatGPT-4o 完成

## 样例 #1

### 输入

```
5
1/2
3/4
1/4
2/23
123/31488```

### 输出

```
Case #1: 1
Case #2: 1
Case #3: 2
Case #4: impossible
Case #5: 8```

# 题解

## 作者：F_L_Bird (赞：0)

# Solution P13253 —— Part Elf

## 一：题意

一个半精灵的精灵血统定义为他的双亲的精灵血统的平均数，给出一个半精灵的精灵血统，已知他 $40$ 代之前的祖先的血统都为 $0$ 和 $1$，求最少多少代之前在他的祖先中可能出现过一位血统为 $1$ 的纯精灵祖先，如果不可能出现所给的精灵血统，输出 "impossible"。

## 二：思路

观察样例，约分后发现满足条件的精灵血统的分母 $Q \in \{2^{k}\mid k \in \mathbb{Z}\}$，接下来我们尝试证明：

用数学语言表述，其意义为：

> 对于序列 $\{a_{n}\}$ 满足 $n \in \{2^{k}\mid k \in \mathbb{Z}\}, a_{i} \in \{ 0,1 \}$，其中 $i$ 满足 $ 1 \le i \le n$，序列的平均值$\dfrac{\sum_{i = 1}^{n} a_{i}}{n}$ 化简后其分母 $P \in \{2^{k}\mid k \in \mathbb{Z}\}$。

这样表述后正确性也就显而易见了（其第 $k$ 代祖先一共有 $2^{k}$ 位）。同理，上述命题的逆定理也很好证明：如果这个序列的平均值（也就是半精灵的精灵血统）形如 $\frac{n}{2^{k}}$，那么可以将序列还原为 $\underbrace{0,0\cdots0}_{2^{k} - n},\underbrace{1,1\cdots1}_{n}$ 的形态。

接着，我们考虑从这个序列入手获取答案。很明显，如果我们希望最后一个血统为 $1$ 的祖先尽可能地在下方，自然需要所有血统为 $1$ 的祖先尽可能地在一起以“保持血统纯正”。如果祖先有 $2^{k}$ 位，则在上方就会有 $k$ 代祖先，而每一代传递下来的血统为 $1$ 的祖先数量至少减少一半，则他们对答案做出的贡献为 $-\lfloor \log_{2}n \rfloor$（答案原本为 $k$ ，因为我们希望答案尽可能小，于是要减去 $\lfloor \log_{2}n \rfloor$）。

## 三：实现

对分母约分需要求最大公因数，这一步可以使用 std 中的 `__gcd()` 函数，也可以手写（手写并不困难，而且似乎有些比赛不能使用下划线开头的函数，因此我们选择手写）。取对数的函数可以使用 cmath 库中的 `log2()`。判断一个数是否为 $2$ 的正整数次幂，有很多种实现方法，这里我们选择最快的方法：如果 $n = \operatorname{lowbit}(n)$，则 $n \in \{2^{k}\mid k \in \mathbb{Z}\}$。

这道题就这样华丽的做完啦，时间复杂度 $\operatorname{O}(T\log_{2}n)$，瓶颈在于约分求最大公因数需要 $\operatorname{O}(\log_{2}n)$ 的时间复杂度。

代码如下喵 \~ 不要抄我喵 \~

```cpp
#include<iostream>
#include<cmath>
using namespace std;

long long a,b;

long long gcd(long long a,long long b){	//这里写了辗转相除法求最大公因数
	return (a % b == 0 ? b : gcd(b,a % b));
}

inline long long lowbit(long long x){	//lowbit函数用于判断一个数是否为2的正整数次幂
	return x & (-x);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	for(int i = 1;i <= t;i += 1)
	{
		char c;				//c作为占位符方便读入
		cin>>a>>c>>b;
		long long t = gcd(a,b);		//求出最大公因数后化简
		a /= t;
		b /= t;
		if(b != lowbit(b))		//如果化简后分母不是2的正整数次幂
		{
			cout<<"Case #"<<i<<": impossible\n";
		}
		else		//计算答案
		{
			cout<<"Case #"<<i<<": "<<int(log2(b)) - int(log2(a))<<'\n';
		}
	}
	return 0;
}
```

## 四：相关知识

> 取对数也可以手写预处理（预处理复杂度 $\operatorname{O}(w)$，查询 $\operatorname{O}(1)$，其中 $w$ 为值域），但是这题询问次数过少，预处理很明显不划算，所以我们不考虑，也不在此列出代码，感兴趣的同学可以自行查询。
>

> 判断一个数是否为 $2$ 的正整数次幂，可以使用很多种方法：
>
> 第一：暴力枚举指数进行判断，时间复杂度 $\operatorname{O}(\log_{2}w)$，其中 $w$ 为值的大小。
>
> 第二：预处理出所有的 $2^{k}$，在需要时二分查找，预处理时间复杂度 $\operatorname{O}(\log_{2}w)$，查询 $\operatorname{O}(\log_{2}(\log_{2} w))$。
>
> 第三：注意到 $2^{k}$ 转换成二进制为 $(1\underbrace{00\cdots0}_{k})_{2}$，使用 $\rm{lowbit}$ 函数处理出数的最后一个为 $1$ 的二进制位，如果 $n = \operatorname{lowbit}(n)$，则 $n \in \{2^{k}\mid k \in \mathbb{Z}\}$（关于 $\rm{lowbit}$ 函数，可以查询 [OI Wiki](https://oi-wiki.org/ds/fenwick/#%E7%AE%A1%E8%BE%96%E5%8C%BA%E9%97%B4)）。

>最大公因数的实现有很多种方式，这里采用欧几里得算法（也就是辗转相除法），更多有关于最大公因数的实现也可以查询 [OI Wiki](https://oi-wiki.org/math/number-theory/gcd/)。

>CCF 目前已经开放了下划线开头的库函数或宏的使用，但是我个人还是不是很喜欢（感觉不好看，怪怪的）。

---

感谢观看喵 \~ 谢谢支持喵 \~

---

## 作者：IkillDream (赞：0)

# P13253 题解

## 思路

我们可以先将每次操作在分母上乘以 $2$。因为，合法的血统的分母必须是 $2$ 的幂次方（即 $Q$ 必须是 $2$ 的幂次方，比如 $2,4,8,\ldots,2^{40}$）。如果 $Q$ 不是 $2$ 的幂次方，否则直接返回 ```impossible```，满足了以上条件，我们看 $\frac{P}{Q}$不是最简分数，接着也要先将其约分，然后检查分母是否是 $2$ 的幂次方，最后我们只需要找到最小的 $k$ 就好了。

## [AC points](https://www.luogu.com.cn/record/225288278)

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int kkk01=1;kkk01<=t;kkk01++){
        long long p,q;
        char c;
        cin>>p>>c>>q;
        long long g=__gcd(p,q);
        p/=g;
        q/=g;
        long long qq=q;
        int kkk02=0;
        while(qq%2==0)qq/=2,kkk02++;
        if(qq!=1){
            cout<<"Case #"<<kkk01<<": impossible"<<endl;
            continue;
        }
        int ans=-1;
        for(int k=1;k<=40;k++)
            if(p*(1LL<<k)>=q){
                ans=k;
                break;
            }
        if(ans!=-1)cout<<"Case #"<<kkk01<<": "<<ans<<endl;
        else cout<<"Case #"<<kkk01<<": impossible"<<endl;
    }
    return 0;
}
```

## 后记

题解制作不容易如果决的我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

---

## 作者：4041nofoundGeoge (赞：0)

## 思路

不难发现精灵 $\frac{C}{D}$ 和 $\frac{1}{1}$ 的孩子是 $\frac{D+C}{2D}$，和 $\frac{0}{1}$ 的孩子是 $\frac{C}{2D}$。于是得到在 $\frac{C}{D}$ **最简情况下** $D$ 一定是 $2$ 的 $n$ 次幂，然后就可以写题目了。

### 细节

1. 记得开 long long。
2. 要约分！！
3. $\log D\le 40$。
4. 题目要求最小辈分的祖先，所以我们每一次我们将 $D\leftarrow D\div 2$，若 $D<C$，我们就找到最先的祖先了。
5. 不难发现若 $D=2^x,x∈\mathbb{Z}$，$D\&(D-1)$ 应等于 $0$。
6. 时间复杂度 $O(T\log d)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool pwo(long long p){
    return (p&(p-1))==0;
}
int main(){
    int t;
    cin>>t;
    int qp=t;
    while(t--){
        long long p,q;
        char f;
        cin>>p>>f>>q;
        long long div=__gcd(p,q);
        p/=div,q/=div;
        cout<<"Case #"<<qp-t<<": ";
        int flag=1;
        if(!pwo(q)||q>((1LL)<<40)){
            cout<<"impossible\n";
            continue;
        }
        while(true){
            if(q/2<=p){
                cout<<flag<<endl;
                break;
            }
            flag++;
            q/=2;
        }
    }
    return 0;
}
```

别急着走，若你高中数学学的好，不难发现答案是 $\lfloor \log D\rfloor-\lfloor \log C\rfloor$ 且 $(D,C)=1$。时间复杂度 $O(T)$。

---

