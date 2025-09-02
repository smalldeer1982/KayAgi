# Perfect Team

## 题目描述

您可能已经知道标准的ICPC团队正好由三名成员组成。然而，完美的团队有更多的限制。学生可以有一些专业：编码或数学家。她/他可以没有专业化，但不能同时拥有两者。

因此，如果团队至少包括一名编码员，至少有一名数学家，并且由三名成员组成，那么团队就被认为是完美的。

你是一所非常大的大学的教练，你知道你的学生的$c$ 是编码员，$m$ 是数学家，$x$ 没有专业。

您可以分配给他们的最佳完整团队的最大数量是多少？

请注意，有些学生可能没有团队，每个学生都可以成为一个团队的一员。

您还被要求回答$q$ 个独立查询。

## 样例 #1

### 输入

```
6
1 1 1
3 6 0
0 0 0
0 1 1
10 1 10
4 4 1
```

### 输出

```
1
3
0
0
1
3
```

# 题解

## 作者：Alex_Wei (赞：4)

#### 题意概述

你有 $a$ 个 $A$，$b$ 个 $B$，$c$ 个 $C$

每个团队共有 $3$ 人，且必须要有一个 $A$ 和一个 $B$

问最多能组成多少团队

---

贪心即可

首先肯定是**能用多少 $C$ 就用多少 $C$**

剩余的 $A$ 和 $B$ 分情况讨论

- 当 $A\ge 2B$ 时，尽量多地用 $2A+1B$ 的组合

- 当 $B\ge 2A$ 时，尽量多地用 $2B+1A$ 的组合

- 否则剩下的团队数为 $\large\lfloor\frac{A+B}{3}\rfloor$

---

具体细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll q,c,m,x;
int main()
{
	cin>>q;
	for(int i=0;i<q;i++){
		cin>>c>>m>>x;//A,B,C
		int ans=min(c,min(m,x));//贪心，能用多少 C 就用多少
		c-=ans,m-=ans;//减掉
		if(c*2<=m)cout<<ans+c<<endl;//第一种情况 
		else if(m*2<=c)cout<<ans+m<<endl;//第二种情况
		else cout<<ans+(c+m)/3<<endl;//第三种情况
	}
    return 0;
}

```

求赞qwq


---

## 作者：弦巻こころ (赞：2)

还算一道比较简单的思路题吧.代码也很简单

~~这是我见过最简单的div2C了~~

首先,我们可以肯定的是,我们最多就只能有$min(c,m)$个最佳团队.最多的时候就是 $2* min(c,m)<= max(c,m)+x $的时候.如果$2* min(c,m)< max(c,m)+x$ 就直接输出 三者之和 /3 即可.

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c;
		cout<<min(min(a,b),(a+b+c)/3)<<endl;//取个min就完事了
	}
}
```


---

## 作者：lyhqwq (赞：1)

### 思路

一个完美团队的形式可能有以下几种

1. 一个编码员，一个数学家，一个没有专业的人。
1. 两个编码员，一个数学家或一个编码员，两个数学家。

分类讨论

- 当 $\min(c,m)\leq x$ 时，我们选择形式1.，所以答案为 $min(c,m)$
- 当 $\min(c,m)>x$ 时，我们选择一部分形式1.当形式1.用完之后再用形式2.，此时答案为 $(c+m+x) \div 3$

综上，答案为 $\min(\min(c,m),(c+m+x)\div3)$

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long q,c,m,x;
int main(){
    scanf("%lld",&q);
    while(q--){
        scanf("%lld%lld%lld",&c,&m,&x);
        printf("%lld\n",min(min(c,m),(c+m+x)/3));
    }
}

```


---

## 作者：Dream_weavers (赞：1)

~~来水一波 python 的题解~~

[题目传送门](https://www.luogu.com.cn/problem/CF1221C)

## 题意

有 $c$ 个编码员、$m$ 个数学家和 $x$ 个没有专业的学生。每个团队至少要有 $1$ 个编码员和 $1$ 个数学家，并且每个团队要有 $3$ 人，求**最多**能组成多少个团队？

## 思路

每个团队要满足两个条件：

- 至少要有 $1$ 个编码员和 $1$ 个数学家

- 每个团队要有 $3$ 人

让团队最多，就要尽可能利用编码员（$c$）和数学家（$m$），团队数量就是 $\min(c,m)$。但是没有专业的学生人数（$x$）可能达不到，还要从总人数看，这个情况下数量就是 $\left\lfloor\dfrac{c+m+x}{3}\right\rfloor$。

所以综合这两个条件，团队数量就是 $\min(\min(c,m),\left\lfloor\dfrac{c+m+x}{3}\right\rfloor)$。

## 代码

```python
t=int(input())
for i in range(t):
    list=input().split()
    c=int(list[0])
    m=int(list[1])
    x=int(list[2])
    print(min(min(c,m),(c+m+x)//3))
    

```


---

## 作者：lrmlrm_ (赞：1)

# 题意

有 $ q $ 次询问 , 每次有 $ 3 $ 个数 , 分别表示编码员 , 数学家和没有任何专业的学生的数量 , 已知每个团队至少要 $ 1 $ 个编码员和 $ 1 $ 个数学家 , 问最多可以组成多少个团队 ？

$ s $ 表示编码员个数 ， $ m $ 表示数学家个数 ， $ x $ 表示$ 3 $ 个数 , $ x $ 没有任何专业的学生的数量  。

$ \left( 1 \leq q \leq 10^4 , 0 \leq c,m,x \right) $

# 思路 

首先 ， 不难想到团队最多只能有有 $ \min \left( s , m \right) $  个团队 ， 也就是在 $ x + \max ( c, m ) > 2 \times \min ( c, m ) $ 的情况下 。 如果 $ x + \max( c, m ) \leq 2 \times \min ( c , m ) $ , 就要输出 $ \left( s + m + x \right) /3 $ 。

# 代码

```cpp
#include<cstdio>
#include<iostream>
int q,c,m,x;
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%d%d%d",&c,&m,&x);
		printf("%d\n",std::min(std::min(c,m),(c+m+x)/3));
	}
	return 0;
}
```
[](P1934)

---

## 作者：shAdomOvO (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/CF1221C)
#### 这题还是很水的，我这里就讲解一下让大家跟好的理解
## 正文
由题可知，给出三种学员，编码猿，数学家，没有专业。每个团队三个人，必须有编码猿和数学家。所以可以看出，团队数量的最大值就是编码猿or数学家的最小值，但是必须总人数足够才行；如果总人数少于编码猿or数学家的最小值，那么编码猿和数学家的数量是一定足够的，那么最大值就是三种人数之和除以3。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long c,m,x,q,a,b;
int main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>c>>m>>x;
		a=min(c,m);//对应着第一种情况
		b=(c+m+x)/3;//第二种
		cout<<min(a,b)<<endl;
        	//如果b>a，那么总人数是大于编码猿or数学家的最小值乘以三的。
          //故用两个min就可以解决问题
	}
}
```

---

## 作者：封禁用户 (赞：0)

# 题意（重点部分）

如果团队至少包括一名编码员，至少有一名数学家，并且由三名成员组成，那么团队就被认为是完美的。

你是一所非常大的大学的教练，你知道你的学生的 $c$ 是编码员，$m$ 是数学家，$x$ 没有专业。

您可以分配给他们的最佳完整团队的最大数量是多少？

请注意，有些学生可能没有团队，每个学生都可以成为一个团队的一员。

您还被要求回答 $q$ 个独立查询。

# 思路

其实这道题有两种情况：

情况一：团队最多只有 $min(s,m)$ 个团队，$a$ 等于  $min(s,m)$。

情况二：如果 $2 \times$ $min(c,m)$ 小于 $max(c,m)+x$，$b$ 等于 $(c+m+x)\div3$。

最后输出 $a$ 和 $b$ 两个数的较小值

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,z;
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++) 
	{
		cin>>x>>y>>z;
		long long a=min(x,y),b=(x+y+z)/3;
		cout<<min(a,b)<<endl; 
	}	
	return 0;
} 
```

---

## 作者：zbk233 (赞：0)

## 解题思路

一道思维题，在想通了过程之后就很简单了。

这道题的样例中提供了解题需要的两种情况，我们先来看第一种情况：

```10 1 10```

因为数学家比编码员少，所以最多组成数学家的数量，也就是一个团队，反之，编码员比数学家少的情况也是这样的。

对于第一种情况，能组成的团队数 $ans1$ 就为 $\min(c,m)$。

我们再来看第二种情况：

```4 4 1```

这时的 $ans1$ 为 $4$，但是总人数只有 $9$ 人，明显无法组成 $4$ 个团队，那么对于这种情况的 $ans2$ 就为 $(c+m+x)/3$。

最后，只需要输出 $\min(ans1,ans2)$ 即可。

## 参考代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,c,m,x;
	cin>>n;
	while(n--){
		cin>>c>>m>>x;
		cout<<min(c,min(m,(c+m+c)/x))<<'\n';
	}
	return 0;
}
```


---

