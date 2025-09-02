# Payment Without Change

## 题目描述

你身上有 $a$ 个 $n$ 元的硬币和 $b$ 个 $1$ 元的硬币。请问能不能在不找零的情况下购买 $s$ 元的物品。

## 样例 #1

### 输入

```
4
1 2 3 4
1 2 3 6
5 2 6 27
3 3 5 18
```

### 输出

```
YES
NO
NO
YES
```

# 题解

## 作者：傅思维666 (赞：4)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11796097.html)

#### 题目大意：

你现在有$a$块面值为$n$的钱币和$b$块面值为$1$的钱币。现在给你一个目标价格$S$，问你是否能够用手中的钱币凑出来想要的价格。

#### 解析：

简单的模拟。可以发现，因为有一块钱的凑数，所以只要我们凑出来的$n$面值的钱的总价值比$S$小，而且小的那部分可以用一块钱的补齐（即数量足够），那么就显然可以凑出合法的钱数。

那我们如何知道比$S$小的$n$面值的钱有多少呢？

除法啊。$\lfloor s/n\rfloor$。

注意，这里还需要和$a$比一下大小，因为有可能$\lfloor s/n\rfloor>a$，这种情况是不合法的。

最后判一下这个东西加上$b$能不能比$S$大，大的话就合法，否则就非法。

至于输出，还是建议大家放标准输出$YES$和$NO$。养成好习惯。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T;
int a,b,n,s;
int main() 
{
    scanf("%d",&T);
    while(T--) 
    {
        scanf("%d%d%d%d",&a,&b,&n,&s);
        int num=s/n;
        num=min(num,a);
        if(num*n+b>=s) 
        {
            printf("YES\n");
            continue;
        }
        else 
        {
            printf("NO\n");
            continue;
        }
    }
    return 0;
}
```



---

## 作者：andyli (赞：2)

分两种情况分析：  
1. $a'$枚价值为$n$的硬币与$b'$枚1元硬币($b'<n$)  
	若$a'\leq a$且$b'\leq b$，则满足题意。  
    
2. $a'$枚价值为$n$的硬币与$b'$枚1元硬币($a'>a$)  
	若$b' \leq b$，则满足题意。

主要代码如下：  
```cpp
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int a, b, n, S;
        io.read(a, b, n, S);
        if (S / n <= a) // #1
            writeln((S % n) <= b ? "YES" : "NO");
        else  // #2
            writeln((S - n * a) <= b ? "YES" : "NO");
    }
    return 0;
}

```

---

## 作者：王炸拆开打 (赞：1)

原本想闲暇之余刷一个，结果这个题代码太短了，忍不住分享一下

# 核心思想：模拟

### ~~重要思想：多买点东西~~

思路（解法）见代码


代码如下：

```cpp
#include<iostream>//不要掉以轻心 
#include<cstdio>
using namespace std;
int n,s,a,b;
int main(){
	int q;
	scanf("%d",&q);
	for(int e=1;e<=q;e++){
		scanf("%d%d%d%d",&a,&b,&n,&s);
		int minn=min(s/n,a);//可能钱不够，取一个小的 
		if((s-minn*n)<=b) printf("YES\n");//剩下的1元够不够 
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：oimaster (赞：0)

显然我们要尽可能使用面值 $n$ 的硬币，然后不够的用面值为 $1$ 的硬币凑。

那么，我们就需要 $\lfloor\frac{s}{n}\rfloor$ 个面值 $n$ 的硬币，不过因为一共就 $a$ 张，所以用面值 $n$ 最多可以撑 $\min(\lfloor\frac{s}{n}\rfloor,a)\cdot n$ 块钱。

那么接下来所有的钱拿 $1$ 来凑即可。代码很好写。

```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,n,s;
		cin>>a>>b>>n>>s;
		if(min(s/n,a)*n+b>=s)
			cout<<"YES";
		else
			cout<<"NO";
		cout<<endl;
	}
}
```

---

## 作者：TEoS (赞：0)

OI生涯打的第一场CF比赛，写篇题解纪念一下吧


本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/11797694.html)。

------------
可以想到先尽量用面值为1的硬币来凑，然后再用面值为n的硬币来补足。先算出用上所有面值为1的硬币还差多少钱，然后判断用面值为n的硬币够不够补足就可以了。计算需要面值为n的硬币的数量的时候，注意是否需要加1的判断。还有一个需要注意的点，有可能用面值为1的硬币就够了，即$b>=s$，有可能会出现没有特判这个情况导致 Wrong answer on test 2 的情况。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll t,a,b,n,s;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>n>>s;
		if(((s-b)%n==0 && a>=(s-b)/n)||((s-b)%n!=0 && a>=(s-b)/n+1 && ((s-b)/n+1)*n<=s)|| b>=s)//分别判断能整除，不能整除和直接凑够的情况
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```


---

