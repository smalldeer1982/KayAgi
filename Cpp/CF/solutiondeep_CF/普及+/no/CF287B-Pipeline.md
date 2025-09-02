# 题目信息

# Pipeline

## 题目描述

Vova, the Ultimate Thule new shaman, wants to build a pipeline. As there are exactly $ n $ houses in Ultimate Thule, Vova wants the city to have exactly $ n $ pipes, each such pipe should be connected to the water supply. A pipe can be connected to the water supply if there's water flowing out of it. Initially Vova has only one pipe with flowing water. Besides, Vova has several splitters.

A splitter is a construction that consists of one input (it can be connected to a water pipe) and $ x $ output pipes. When a splitter is connected to a water pipe, water flows from each output pipe. You can assume that the output pipes are ordinary pipes. For example, you can connect water supply to such pipe if there's water flowing out from it. At most one splitter can be connected to any water pipe.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF287B/d347ad4c15760876dd4efdb4df653ce9dd1bfe47.png)The figure shows a $ 4 $ -output splitterVova has one splitter of each kind: with $ 2 $ , $ 3 $ , $ 4 $ , ..., $ k $ outputs. Help Vova use the minimum number of splitters to build the required pipeline or otherwise state that it's impossible.

Vova needs the pipeline to have exactly $ n $ pipes with flowing out water. Note that some of those pipes can be the output pipes of the splitters.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
8 4
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 管道

## 题目描述
沃瓦，终极图勒的新萨满，想要建造一条管道。由于终极图勒恰好有 $n$ 座房屋，沃瓦希望城市恰好有 $n$ 根水管，每根这样的水管都应连接到水源。如果有水流从一根水管流出，那么这根水管就可以连接到水源。最初，沃瓦只有一根有水流的水管。此外，沃瓦还有几个分流器。

一个分流器是一种构造，它由一个输入口（可以连接到一根水管）和 $x$ 个输出水管组成。当一个分流器连接到一根有水的水管时，水会从每个输出水管流出。你可以假设输出水管是普通水管。例如，如果有水流从这样的水管流出，你就可以将水源连接到它。任何一根水管最多只能连接一个分流器。

![4 - 输出分流器](https://cdn.luogu.com.cn/upload/vjudge_pic/CF287B/d347ad4c15760876dd4efdb4df653ce9dd1bfe47.png)
图中展示了一个有4个输出口的分流器。沃瓦有各种类型的分流器各一个：分别有 $2$、$3$、$4$、$\cdots$、$k$ 个输出口。帮助沃瓦用最少数量的分流器建造所需的管道，否则说明这是不可能的。

沃瓦需要管道恰好有 $n$ 根有水流流出的水管。注意，其中一些水管可以是分流器的输出水管。

## 样例 #1
### 输入
```
4 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5 5
```
### 输出
```
1
```

## 样例 #3
### 输入
```
8 4
```
### 输出
```
-1
```

### 算法分类
二分

### 综合分析与结论
所有题解都基于二分法求解本题，核心思路是利用答案的单调性，通过二分枚举分流器的数量，并结合贪心策略在 $O(1)$ 时间复杂度内判断该数量的分流器能否满足使 $n$ 个客户通水的要求。不同题解在细节处理和表述上略有差异，例如对边界条件的特判方式、公式推导和代码实现的风格等。

### 所选的题解
- **作者：_lxy_ (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，详细注释了关键步骤和公式含义，对二分的每一步处理都有清晰解释，还特别提醒注意数据类型范围。
    - **重点代码**：
```cpp
int check(ll mid)
{
    ll x=(2*k-(mid-1))*mid/2-mid+1; 
    return x>=n;
}
int main()
{
    scanf("%lld%lld",&n,&k);
    if(n==1) 
    {
        printf("0\n");
        return 0;
    }
    ans=-1;
    ll l=1,r=k-1;
    while(l<=r) 
    {
        ll mid=(l+r)/2;
        int flag=check(mid);
        if(flag) 
        {
            ans=mid; 
            r=mid-1; 
        }
        else l=mid+1; 
    }
    printf("%lld\n",ans);
    return 0;
}
```
    - **核心实现思想**：`check` 函数计算使用 `mid` 个分流器时能产生的水管数，与 `n` 比较。主函数中二分枚举分流器数量，根据 `check` 结果调整范围，找到满足条件的最小分流器数量，特判了 `n == 1` 的情况。
- **作者：AKPC (4星)**
    - **关键亮点**：对题意简化清晰，详细阐述了思路，包括二分的原因、`check` 函数的贪心策略及公式推导，还提到了对无解情况的特判。
    - **重点代码**：
```cpp
signed main(){
	cin>>n>>k,l=0,r=k-1;
	if (k*(k-1)/2<--n){
		cout<<-1;
		return 0;
	}
	while (l<r){
		int mid=(l+r)/2;
		if ((k-1+k-mid)*mid/2>=n) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```
    - **核心实现思想**：先特判无解情况，二分循环中根据 `check` 函数判断当前二分的分流器数量能否满足要求，调整二分范围，最终输出结果。
- **作者：静谧幽蓝 (4星)**
    - **关键亮点**：提供了两种解法，二分法思路清晰，对边界条件判断详细；爆算等式法从数学角度直接求解，有详细的公式推导过程。
    - **二分法重点代码**：
```cpp
bool check(int x)
{
    int temp=((m-1)+(m-x))*(x)/2;
    return temp>=n;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    if(n>m*(m-1)/2+1)
    {
        cout<<"-1\n";
        return 0;
    }
    n--;
    int l=0,r=m;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    cout<<l<<'\n';
    return 0;
}
```
    - **核心实现思想**：`check` 函数计算使用 `x` 个水管时增加的接口数与 `n` 比较。主函数先特判无解情况，二分枚举水管数量，根据 `check` 结果调整范围得到答案。
    - **爆算等式法重点代码**：
```cpp
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    if(n>m*(m-1)/2.00+9.00/8.00)
    {
        cout<<"-1\n";
        return 0;
    }
    long double root1=(-(2*m-1.00)-sqrtl((2*m-1)*(2*m-1)+8*(1-n)))/(-2.00);
    long double root2=(-(2*m-1.00)+sqrtl((2*m-1)*(2*m-1)+8*(1-n)))/(-2.00);
    cout<<(long long)(ceill(min(root1,root2)))<<'\n';
    return 0;
}
```
    - **核心实现思想**：根据题意列出二次方程，计算判别式判断有无解，利用求根公式求出根，取较小根上取整输出。

### 最优关键思路或技巧
利用二分法结合贪心策略求解。由于能通水的客户数随分流器数量增加而增加，具有单调性，适合二分。在判断二分的分流器数量是否满足条件时，贪心选择编号大的分流器，通过等差数列求和公式在 $O(1)$ 时间复杂度内计算出增加的水流数，从而高效解决问题。

### 可拓展之处
同类型题常利用二分查找的单调性特点，结合具体问题的贪心策略求解。类似套路如在资源分配、最值求解等问题中，若答案具有单调性，可考虑二分枚举答案，再用贪心或其他高效方法判断该答案是否可行。

### 洛谷相似题目
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分枚举答案，判断能否满足一定条件，与本题二分思路类似。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：利用二分答案结合贪心判断，确定满足条件的最小分段值。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样基于二分答案和贪心策略解决问题。 

---
处理用时：77.45秒