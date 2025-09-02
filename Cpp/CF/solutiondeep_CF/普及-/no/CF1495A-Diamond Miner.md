# 题目信息

# Diamond Miner

## 题目描述

[题目链接](https://codeforces.com/problemset/problem/1495/A)

在一个平面直角坐标系上，有 $n$ 个矮人与 $n$ 个钻石。保证所有矮人都在 $y$ 轴上，所有钻石都在 $x$ 轴上，且没有东西在原点

现在，每个矮人都需要去捡一个钻石。假设矮人和钻石的坐标分别为 $(x,y),(u,v)$，那么这个矮人去捡这个钻石所花费的体力就是 $\sqrt{(x-u)^2+(y-v)^2}$（也就是两点间的距离）

求一个钻石的分配方案，使得所有矮人花费的总体力最少，并输出这个最小值

## 说明/提示

$1 \le T \le 10$  
$1\le n \le 10^5,\sum n\le 10^5$  
$|x|,|y|\le 10^8$

## 样例 #1

### 输入

```
3
2
0 1
1 0
0 -1
-2 0
4
1 0
3 0
-5 0
6 0
0 3
0 1
0 2
0 4
5
3 0
0 4
0 -3
4 0
2 0
1 0
-3 0
0 -10
0 -2
0 -10```

### 输出

```
3.650281539872885
18.061819283610362
32.052255376143336```

# AI分析结果

### 题目内容
# 钻石矿工

## 题目描述
[题目链接](https://codeforces.com/problemset/problem/1495/A)

在一个平面直角坐标系上，有 $n$ 个矮人与 $n$ 个钻石。保证所有矮人都在 $y$ 轴上，所有钻石都在 $x$ 轴上，且没有东西在原点。

现在，每个矮人都需要去捡一个钻石。假设矮人和钻石的坐标分别为 $(x,y),(u,v)$，那么这个矮人去捡这个钻石所花费的体力就是 $\sqrt{(x - u)^2 + (y - v)^2}$（也就是两点间的距离）。

求一个钻石的分配方案，使得所有矮人花费的总体力最少，并输出这个最小值。

## 说明/提示
$1 \le T \le 10$  
$1\le n \le 10^5,\sum n\le 10^5$  
$|x|,|y|\le 10^8$

## 样例 #1
### 输入
```
3
2
0 1
1 0
0 -1
-2 0
4
1 0
3 0
-5 0
6 0
0 3
0 1
0 2
0 4
5
3 0
0 4
0 -3
4 0
2 0
1 0
-3 0
0 -10
0 -2
0 -10
```
### 输出
```
3.650281539872885
18.061819283610362
32.052255376143336
```

### 算法分类
贪心

### 综合分析与结论
所有题解均采用贪心策略，核心思路是证明不交叉连线（即坐标绝对值小的与小的连，大的与大的连）为最优方案。各题解通过不同方式证明此结论，如利用三角形两边之和大于第三边的性质、和一定时差小积大的原理、对平方后式子作差比较等。之后将坐标轴上的点按坐标绝对值排序，对应配对计算距离和。各题解的不同点主要在于证明过程的详细程度、代码实现细节（如输入方式、排序方式、精度处理等）。

### 所选的题解
- **作者：TonyYin (赞：16)  星级：5星  关键亮点**：通过配图清晰展示分析过程，利用三角形三边关系严谨证明不交叉连线最优，代码简洁明了。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 10;
int T;
double a[MAXN], b[MAXN];
signed main() {
    cin >> T;
    while(T--) {
        int n, cnt1 = 0, cnt2 = 0; cin >> n;
        for(int i = 1; i <= 2 * n; i++) {
            int x, y; scanf("%lld%lld", &x, &y);
            if(x == 0) {
                if(y < 0) y *= -1;
                a[++cnt1] = y;
            }
            if(y == 0) {
                if(x < 0) x *= -1;
                b[++cnt2] = x;
            }
        }
        sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
        double ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += sqrt(a[i] * a[i] + b[i] * b[i]);
        }
        printf("%.11lf\n", ans);
    }
    return 0;
}
```
核心代码实现思想：读入坐标，将 $y$ 轴上的点取 $y$ 坐标绝对值存于数组 $a$，$x$ 轴上的点取 $x$ 坐标绝对值存于数组 $b$，对两数组排序后，对应元素计算距离累加得到答案。

- **作者：血色黄昏 (赞：3)  星级：4星  关键亮点**：给出贪心思路及详细证明过程，通过具体不等式推导证明贪心策略正确性，代码有对精度问题的讨论。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, t, k, a[100010], b[100010];//定义数组
bool cmp(int a, int b)//按绝对值排序
{
	return abs(a) < abs(b);
}
int main()
{
	cin>>t;
	while(t --)//多测
	{
		long double ans = 0;//答案
		int cnt1 = 0, cnt2 = 0;//两个数组记录到那里了
		cin>>n;
		for(int i = 1;i <= n;i ++)
		{
			int x, y;
			cin>>x>>y;
			if(x == 0)a[++ cnt1] = y;//分坐标轴读入
			else b[++ cnt2] = x;
			cin>>x>>y;
			if(x == 0)a[++ cnt1] = y;//同上
			else b[++ cnt2] = x;
		}
		sort(a + 1, a + n + 1, cmp);//排序
		sort(b + 1, b + n + 1, cmp);
		for(int i = 1;i <= n;i ++)
		{
			ans += sqrt(1.0 * (long double)(a[i] * a[i]) + 1.0 * (long double)(b[i] * b[i]));//每次加最近两个的相对距离
		}
    	cout<<setiosflags(ios::fixed)<<setprecision(30);//输出精度开到1e-30
    	cout<<ans<<endl;//输出
	}
    return 0;
}
```
核心代码实现思想：读入坐标分别存入对应数组，自定义按绝对值排序函数对数组排序，对应元素计算距离累加，最后按高精度输出答案。

- **作者：Silence_water (赞：2)  星级：4星  关键亮点**：通过配图直观展示两种连线方式，对比得出不交叉连线更优，代码简洁且有精度和类型转换的提醒。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int T,n,k,a[M],b[M];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
    	scanf("%d",&n);
    	int a0=0,b0=0;
    	for(int i=1;i<=2*n;i++)
    	{
    		int x,y;
    		scanf("%d%d",&x,&y);
    		if(y==0)a[++a0]=abs(x);
    		else b[++b0]=abs(y);
		}
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		double ans=0.0;
		for(int i=1;i<=n;i++)
			ans+=sqrt((long long)a[i]*a[i]+(long long)b[i]*b[i]);
		printf("%.11lf\n",ans);
	}
    return 0;
}
```
核心代码实现思想：读入坐标取绝对值存入不同数组，排序后对应元素计算距离累加，按指定精度输出答案。

### 最优关键思路或技巧
利用贪心思想，通过数学证明（如三角形三边关系、和一定时差小积大等）得出不交叉连线为最优方案，再通过排序实现坐标的配对计算。在代码实现中，注意坐标的处理（取绝对值）以及精度问题。

### 可拓展思路
此类问题可拓展到其他几何图形上的点配对求距离和最小问题，或在限制条件更多的情况下探讨最优配对策略。类似算法套路是遇到求最值的配对问题，先尝试从简单情况入手，通过数学方法证明贪心策略的正确性。

### 推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)
- [P2949 [USACO09OPEN]Work Scheduling G](https://www.luogu.com.cn/problem/P2949)

### 个人心得摘录
血色黄昏提到“十年 OI 一场空，强转 ll 见祖宗”，强调了在处理大数据范围时类型转换的重要性，否则可能因数据类型问题导致结果出错（如输出 nan）。 

---
处理用时：74.57秒