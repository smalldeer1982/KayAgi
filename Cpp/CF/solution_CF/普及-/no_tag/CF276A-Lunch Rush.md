# Lunch Rush

## 题目描述

$n$ 个餐馆，每个餐馆都有两个值 $f_i$，$t_i$，分别代表在该餐馆的快乐值和所要停留的时间，给出一个正整数 $k$，如果 $t_i>k$，则在该餐馆的快乐值为 $f_i-(t_i-k)$，否则，仍为 $f_i$，选择一个餐馆，使获得的快乐值最大。

## 说明/提示

$1\leq n \leq 10^4$，$1\leq k,f_i,t_i \leq 10^9$。

## 样例 #1

### 输入

```
2 5
3 3
4 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 6
5 8
3 6
2 3
2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 5
1 7
```

### 输出

```
-1
```

# 题解

## 作者：yydfj (赞：2)

**这是本蒟蒻第十五次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你两个正整数 $n$ 和 $k$，接下来 $n$ 行分别输入 $f$ 和 $t$，若 $t>k$，则将 $f-(t-k)$ 的值放进序列 $q$ 里，否则直接将 $f$ 的值放进序列 $q$ 里，问序列 $q$ 里最大的值是多少。

## 解法综述

输入和将值放进序列 $q$ 里的步骤直接模拟即可，关键在于序列 $q$ 中找其最大值的办法。

我们可以给序列 $q$ 从大到小进行排序，则序列 $q$ 中的第一个数就是其最大值，但如果我们将序列 $q$ 看成一个优先队列，则可以不用排序直接得出序列 $q$ 中的第一个数为其最大值。

## 代码描述
```cpp
#include<queue>
#include<cstdio>
using namespace std;
priority_queue<int> q;//直接定义的优先队列默认为从大到小排列
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    while(n--)
    {
        int f,t;
        scanf("%d%d",&f,&t);
        q.push(t>k?f-(t-k):f);
        //若t>k，则将f-(t-k)的值放进序列q里，否则直接将f的值放进序列q里
    }
    printf("%d",q.top());//得出序列q中的第一个数为其最大值
    return 0;
}
```

---

## 作者：33aaron (赞：2)

最近估值掉的有点快，写篇题解压压惊，安慰一下我受伤的心灵~。
## 题目大意
有 $n$ 家餐馆可供用餐，我们知道去第 $i$ 家餐馆用餐可以得到的乐趣指数 $f_i$ 和需要的用餐时间 $t_i$。输出去哪家餐馆可以得到的乐趣指数最大值。
- 如果 $t_i > k$，则获得的乐趣指数为 $f_i - (t_i - k)$。
- 否则，获得的乐趣指数为 $f_i$。
## 题目分析
其实就是非常简单的模拟，但是要注意当 $t_i > k$ 时乐趣指数有可能是负数，如果所有的 $t_i$ 都大于 $k$ 的话，最大值就是一个负数。所以这里记录答案（乐趣最大值）的那个变量初始值不能为 $0$。
## Solution
```Cpp
#include <iostream>
#define INF 0x3f3f3f3f
using namespace std;
int main() {
    int n, k, ans = -INF; //这里记录乐趣最大值的变量的初始值我用了-INF
    cin >> n >> k;
    while (n--) {
        int f, t;
        cin >> f >> t;
        if (t > k) ans = max(ans, f - (t - k));
        else ans = max(ans, f); 
    }
    cout << ans;
    return 0;
}
```

---

## 作者：newbie_QwQ (赞：1)

分析：这道题让我们求出 $n$ 个餐馆里的快乐值最大是多少，求快乐值的方法也已经在题目中给出，一步步模拟即可。真的太简单了，没啥好讲的。

------------
## AC 代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int i,n,k,f,t,m=-2000000000;//唯一一个坑点，最大值可以是一个很小的负数，初始值要设的小一点。
    cin>>n>>k;
    for(i=1;i<=n;i++)
    {
        cin>>f>>t;
        if(t>k) m=max(m,f-(t-k));//按题目中给出的模拟。
        else m=max(m,f);
    }
    cout<<m;
    return 0;//再见!
}
```

---

## 作者：程门立雪 (赞：1)

**题解：**

当我们发现 $n$ 只有 $10^4$ 时，就很容易可以想到，进行模拟就好了。

对于每一家餐厅进行判断，如果时间够，就得到 $f_i$ 的快乐值，如果时间不够，就得到 $f_i - (t_i - k)$ 的快乐值。因为可能为负数，所以初始答案要赋极小值。

```c
int n, k, ans = -0x3f3f3f3f; 
struct node{
	int t, f;
}a[10010];
int main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	n = read(), k = read();
	for(int i = 1; i <= n; i++) a[i].f = read(), a[i].t = read();
	for(int i = 1; i <= n; i++)
	{
		if(a[i].t > k) ans = max(ans, a[i].f - a[i].t + k);
		else ans = max(ans, a[i].f);
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：hanyuchen2019 (赞：0)

由于数据范围 $10^4$，可以直接模拟每个餐馆的快乐值，取最大值即可。

唯一的坑点是：由于 $f$ 可能为负数，初始值不能设为 $0$，要设成 `-INF` ，否则会在样例 $3$ 挂掉。（我把初始值设为 $-10^8$ 都挂在测试点 $9$ 上了）

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,k,ans=-2147483648;//设成一个极小值
	cin>>n>>k;
	for(int i=1,f,t;i<=n;i++)//枚举每个餐馆
	{
		cin>>f>>t;//不用开数组读人，可以直接处理
		ans=max(ans, t>k ? f-(t-k) : f );//三目运算符
		/*等价于：
		if(t>k)
			ans=max(ans,f-(t-k));
		else
			ans=max(ans,f);
		*/
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Rosmarinus (赞：0)

有 $n$ 家餐馆可供用餐，我们知道去第 $i$ 家餐馆用餐可以得到的乐趣指数 $f_i$ 和需要的用餐时间 $t_i$。输出去哪家餐馆可以得到的乐趣指数最大值。

- 如果 $t_i > k$，则获得的乐趣指数为 $f_i - (t_i - k)$；
- 否则，获得的乐趣指数为 $f_i$。

水题，每次按照更快乐的选就好。

唯一需要注意的是，$ans$ 初始值不能定位 $0$，需要定极小值。

## Code

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n, k, ans = -0x3f3f3f3f3f;
    cin >> n >> k;
    while (n --)
	{
        int f, t;
        cin >> f >> t;
        if (t > k) ans = max(ans, f - (t - k));
        else ans = max(ans, f); 
    }
    cout << ans << endl;
    return 0;
}
```

---

