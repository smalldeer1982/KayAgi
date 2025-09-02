# 题目信息

# Max and Mex

## 题目描述

[题目链接](https://codeforces.com/problemset/problem/1496/B)

给出一个长度大小为 $n$ 的可重集合 $S$（集合内允许有），保证这 $n$ 个数互不相同且非负。

接下来，你需要将下面操作进行 $k$ 次：  
将 $\lceil \frac{a+b}{2}\rceil$ 加入集合（注意这里是**可重集**），其中 $a=\operatorname{mex}(S)$， $b=\max(S)$。

这里 $\operatorname{mex}(S)$ 表示集合 $S$ 中没有出现过的最小的非负整数，$\max(S)$ 表示 $S$ 中的最大整数。

求 $k$ 次操作后，集合 $S$ 中有多少个不同的数。

## 说明/提示

$1\le T \le 100$  
$1\le n \le 10^5$  
$0 \le a_i,k \le 10^9$  
$\sum n\le 10^5$

## 样例 #1

### 输入

```
5
4 1
0 1 3 4
3 1
0 1 4
3 0
0 1 4
3 2
0 1 2
3 2
1 2 3```

### 输出

```
4
4
3
5
3```

# AI分析结果

### 题目内容
# Max and Mex

## 题目描述

[题目链接](https://codeforces.com/problemset/problem/1496/B)

给出一个长度大小为 $n$ 的可重集合 $S$（集合内允许有重复元素），保证这 $n$ 个数互不相同且非负。

接下来，你需要将下面操作进行 $k$ 次：  
将 $\lceil \frac{a+b}{2}\rceil$ 加入集合（注意这里是**可重集**），其中 $a=\operatorname{mex}(S)$， $b=\max(S)$。

这里 $\operatorname{mex}(S)$ 表示集合 $S$ 中没有出现过的最小的非负整数，$\max(S)$ 表示 $S$ 中的最大整数。

求 $k$ 次操作后，集合 $S$ 中有多少个不同的数。

## 说明/提示

$1\le T \le 100$  
$1\le n \le 10^5$  
$0 \le a_i,k \le 10^9$  
$\sum n\le 10^5$

## 样例 #1

### 输入

```
5
4 1
0 1 3 4
3 1
0 1 4
3 0
0 1 4
3 2
0 1 2
3 2
1 2 3
```

### 输出

```
4
4
3
5
3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分类讨论来避免暴力模拟，利用 $mex$ 和 $max$ 的关系来确定操作后集合元素个数的变化规律。主要分为两种情况：
 - 当 $mex > max$ 时（实际就是集合包含了 $0$ 到 $max$ 的所有数字，$mex = max + 1$ ），每次操作加入的数为 $max + 1$ ，之后 $mex$ 和 $max$ 都会增加 $1$ ，所以 $k$ 次操作后集合不同元素个数为 $n + k$ 。
 - 当 $mex < max$ 时，每次操作加入的数 $p=\lceil \frac{mex + max}{2}\rceil$ 满足 $mex < p < max$ ，这意味着 $mex$ 和 $max$ 不会改变，此时只需判断 $p$ 在原集合中是否存在，存在则集合不同元素个数为 $n$ ，不存在则为 $n + 1$ 。同时，所有题解都注意到了 $k = 0$ 时需特判直接输出 $n$ 。

### 所选的题解
 - **洛璟 - 5星**
    - **关键亮点**：思路清晰，先指出暴力模拟会超时，然后详细分析两种情况并给出证明，代码实现简洁明了，还包含快读优化。
    - **个人心得**：经巨佬指正修改了时间复杂度的错误。
    - **核心代码**：
```cpp
int main()
{
    t = read();
    while (t--)
    {
        map<int, bool> fg;
        priority_queue<int> q;
        n = read();
        k = read();
        for (int i = 1;i <= n;++i)
        {
            a[i] = read();
            fg[a[i]] = 1;
            q.push(a[i]);
        }
        if (k == 0)
        {
            printf("%d\n", n);
            continue;
        }
        for (int i = 0;i <= n;++i)
        {
            if (fg[i] == 0)
            {
                me = i;
                break;
            }

        }
        if (me > q.top())
        {
            printf("%d\n", n + k);
        }
        else
        {
            int tmp = (me + q.top() + 1) / 2;
            if (fg[tmp] == 0)
            {
                printf("%d\n", n + 1);
            }
            else
            {
                printf("%d\n", n);
            }
        }
    }

    return 0;
}
```
核心实现思想：先读入数据并标记每个数是否存在，找到 $mex$ 。然后根据 $mex$ 和 $max$ 的关系判断属于哪种情况，进而输出结果。

 - **Silence_water - 4星**
    - **关键亮点**：分析部分逻辑清晰，对 $a$（即 $mex$ ）和 $b$（即 $max$ ）的大小关系进行分类讨论，代码实现使用 `multiset` ，较为直观。
    - **核心代码**：
```cpp
int main()
{
    scanf("%d",&T);
    while(T--)
    {
    	m.clear();
    	scanf("%d%d",&n,&k);
    	for(int i=1;i<=n;i++)
    	{
    		scanf("%d",&x);
    		m.insert(x);
		}
    	if(k==0)
    	{
    		printf("%d\n",n);
    		continue;
		}
		it=m.begin();
		int mex=-inf;
		if(*it>0)mex=0;// 无0就是0
		else
		{
			for(int i=1;i<n;i++)
			{
				st=it;it++;
				if(*st+1<*it){mex=i;break;}//找到mex
			}
			if(mex==-inf)mex=(*it)+1;//如果没找到，那么mex=max+1
		}
		it=m.end();
		it--;
		int mx=*it;
		if(mx+1==mex)
		{
			printf("%d\n",n+k);
			continue;
		}
		int ns=(int)ceil(0.5*(mex+mx));
		it=m.lower_bound(ns);
		if(*it!=ns)n++;//若不存在，ans=n+1
		printf("%d\n",n);
	}
    return 0;
}
```
核心实现思想：先读入数据插入 `multiset` ，然后根据集合元素情况找到 $mex$ 和 $max$ ，依据两者关系分类得出结果。

 - **cmll02 - 4星**
    - **关键亮点**：代码简洁，分类讨论清晰，先排序后找 $mex$ ，直接根据 $mex$ 和 $max$ 的关系得出答案。
    - **核心代码**：
```cpp
signed main()
{
    int T=read();
    while(T--)
    {
        int n=read(),k=read();
        for(int i=1;i<=n;i++)a[i]=read();
        std::sort(a+1,a+n+1);
        int mex=-1,max=a[n];a[0]=-1;
        for(int i=1;i<=n;i++)
        {
            if(a[i]-1>a[i-1])
            {
                mex=a[i-1]+1;
                break;
            }
        }
        if(mex==-1)
        {
            printf("%lld\n",k+max+1);
            continue;
        }
        if(max-1==mex)
        {
            printf("%lld\n",n);
        }
        else
        {
            if(k==0)printf("%lld\n",n);
            else
            {
                int aa=(max+mex-1)/2+1;
                for(int i=1;i<=n;i++)
                {
                    if(a[i]==aa)
                    {
                        printf("%lld\n",n);
                        goto ng;
                    }
                }
                printf("%lld\n",n+1);
            }
        }
        ng:;
    }
}
```
核心实现思想：先对输入数据排序，找到 $mex$ ，根据 $mex$ 与 $max$ 的关系，判断是否插入新元素，得出最终集合元素个数。

### 最优关键思路或技巧
通过对 $mex$ 和 $max$ 大小关系的分类讨论，避免了对 $k$ 次操作的暴力模拟，将时间复杂度从暴力的高复杂度降低到接近线性复杂度。利用数学推导得出不同情况下操作后集合元素个数的变化规律，从而快速求解。

### 可拓展之处
此类题目属于通过分析操作规律来避免暴力模拟的数学思维题。类似套路是对题目中的关键操作或定义进行深入分析，找到操作过程中的不变量或有规律的变化，从而简化问题。例如一些关于集合元素增减操作并统计最终状态的题目，都可以尝试通过分析操作对关键量（如本题的 $mex$ 和 $max$ ）的影响来解决。

### 相似知识点洛谷题目
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过对连续自然数求和公式的数学分析来解决问题，考察数学思维。
 - [P2669 金币](https://www.luogu.com.cn/problem/P2669)：需要分析金币获取规律，根据规律进行计算，与本题找操作规律类似。
 - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：利用斐波那契数列性质和数学推导来求解，同样是基于数学知识找规律解题。

### 个人心得摘录与总结
洛璟提到经他人指正修改了时间复杂度的错误，说明在解题过程中，对时间复杂度等细节的分析很重要，即使思路正确，复杂度分析错误也可能导致误解。这提醒我们在做题时要严谨对待复杂度分析，多与他人交流以发现潜在错误。 

---
处理用时：120.12秒