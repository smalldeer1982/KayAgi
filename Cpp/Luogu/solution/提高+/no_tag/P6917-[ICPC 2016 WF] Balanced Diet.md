# [ICPC 2016 WF] Balanced Diet

## 题目描述

每天，Danny 都会从糖果店买一颗糖并吃掉它。糖果店中有 $m$ 种糖，编号为 $1 \dots m$ 。

Danny 知道均衡饮食很重要，他正在尝试在购买糖果时有一个均衡的饮食。因此他给每种糖 $i$ 分配了一个目标分数 $f_i (0 \le f_i \le 1, f_i$ 为一个实数 $) $, 。他希望他所吃的所有糖中，第 $i$ 种糖的数量占比大概为 $f_i$ 。

准确的说， 令 $s_ i$ 表示 Danny 已经吃掉的第 $i$ 种糖的数量,  $n = \sum _{i=1}^ m s_ i$, 我们认为一种吃糖的方法是均衡的仅当对于所有的 $i$，满足：

$$n f_ i - 1 < s_ i < n f_ i + 1$$

Danny 已经购买并吃掉了一些糖，并且他保证每个前缀的饮食都是均衡的。他想知道在保证每个前缀均衡饮食的条件下，他最多还能吃多少颗糖。

给定目标分数 $f_i$
和他已经吃过的糖果序列，请你确定在保证每个前缀均衡饮食的条件下，Danny 最多还能购买并吃掉多少颗糖果。

## 样例 #1

### 输入

```
6 5
2 1 6 3 5 3
1 2 5 3 5
```

### 输出

```
1

```

## 样例 #2

### 输入

```
6 4
2 1 6 3 5 3
1 2 5 3
```

### 输出

```
forever

```

# 题解

## 作者：kyEEcccccc (赞：4)

先忽略掉无穷解的判断，假设我们只需要不停地操作尽可能多的步骤。考虑一个贪心策略：对于一类糖果，存在某个时刻 $t_i$，到这个时刻如果还没有额外买一个这种糖果就会不合法了；当然也存在一个时刻 $s_i$，在此之前如果买了一个糖果就会不合法。那么我们每次取所有可以取的糖果里 $t_i$ 最小的那个糖果，如果发现没有能取的，或者有必须取的取不了，那就寄了。

现在考虑无穷解的问题。一个大胆的猜测是如果说进行到下一个 $A = \sum\limits_{i=1}^n a_i$ 的倍数轮次以后依然合法那就一定合法了。考虑这是为啥。我们发现当轮数是 $A$ 的倍数时候所有 $nf_i$ 都是整数，那么所有糖果都只有一种合法数值。如果这一次合法，上一次进行到 $A$ 的倍数也合法，那么可以无限模仿这一回合的方法进行下去。那么我们只需要模拟最多 $A$ 轮。

实现考虑使用一些堆和 `set`。

---

## 作者：XIxii (赞：2)

### 思路：

  满足下列贪心即可：
    $\frac{na_i}{sf} < s_i + 1$

  而我们需要求解的就是天数，即：
    $n < \frac{(s_i+1)sf}{a_i}$

  注意 $n$ 为整数，所以最终得到：
    $n < \lfloor \frac{(s_i+1)sf}{a_i} \rfloor +1$


### 代码：

```
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL m,k,tot;
LL a[100010],b[100010];
priority_queue<pair<LL,LL> >Q;
void init()
{
	cin>>m>>k;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        tot+=a[i];
    }
    for(int i=1;i<=k;i++)
    {
        long long t;
        cin>>t;
        b[t]++;
    }
    for(int i=1;i<=m;i++)
    {
        long long t=((b[i]+1)*tot+a[i]-1)/a[i];
        Q.push(make_pair(-t,i));
    }
}
void work()
{
	LL i=k+1;
	for(i;i<=k+tot;i++)
    {
		LL day=-Q.top().first,ind=Q.top().second;
		Q.pop();
		if(day<i)
        {
			i=day-1;
			break;
		}
		b[ind]++;
		day=((b[ind]+1)*tot+a[ind]-1)/a[ind];
		Q.push(make_pair(-day, ind));
	}
	if(i!=k+tot+1)
    {
        cout<<i-k<<endl;
    }
	else 
    {
        cout<<"forever\n";
    }
}
int main()
{
	init();
	work();
	return 0;
}

```

---

