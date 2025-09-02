# 题目信息

# Ice Sculptures

## 题目描述

The Berland University is preparing to celebrate the 256-th anniversary of its founding! A specially appointed Vice Rector for the celebration prepares to decorate the campus. In the center of the campus $ n $ ice sculptures were erected. The sculptures are arranged in a circle at equal distances from each other, so they form a regular $ n $ -gon. They are numbered in clockwise order with numbers from 1 to $ n $ .

The site of the University has already conducted a voting that estimated each sculpture's characteristic of $ t_{i} $ — the degree of the sculpture's attractiveness. The values of $ t_{i} $ can be positive, negative or zero.

When the university rector came to evaluate the work, he said that this might be not the perfect arrangement. He suggested to melt some of the sculptures so that:

- the remaining sculptures form a regular polygon (the number of vertices should be between 3 and $ n $ ),
- the sum of the $ t_{i} $ values of the remaining sculptures is maximized.

Help the Vice Rector to analyze the criticism — find the maximum value of $ t_{i} $ sum which can be obtained in this way. It is allowed not to melt any sculptures at all. The sculptures can not be moved.

## 说明/提示

In the first sample it is best to leave every second sculpture, that is, leave sculptures with attractivenesses: 2, 4, 5 и 3.

## 样例 #1

### 输入

```
8
1 2 -3 4 -5 5 2 3
```

### 输出

```
14
```

## 样例 #2

### 输入

```
6
1 -2 3 -4 5 -6
```

### 输出

```
9
```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
21
```

# AI分析结果

### 题目内容
# 冰雕

## 题目描述
伯兰大学正准备庆祝其建校256周年！一位特别任命的负责庆典的副校长准备装饰校园。在校园中心竖立了 $n$ 座冰雕。这些冰雕等距排列成一个圆圈，因此它们形成了一个正 $n$ 边形。它们按顺时针方向从1到 $n$ 编号。

该大学的网站已经进行了一次投票，评估了每座冰雕的 $t_{i}$ 特性——冰雕的吸引力程度。$t_{i}$ 的值可以是正数、负数或零。

当大学校长来评估这项工作时，他说这可能不是完美的布置。他建议融化一些冰雕，以便：
- 剩下的冰雕形成一个正多边形（顶点数应在3到 $n$ 之间），
- 剩下冰雕的 $t_{i}$ 值之和最大。

帮助副校长分析这个批评——找出通过这种方式可以获得的 $t_{i}$ 总和的最大值。也可以选择不融化任何冰雕。冰雕不能移动。

## 说明/提示
在第一个样例中，最好每隔一个留下一座冰雕，即留下吸引力为2、4、5和3的冰雕。

## 样例 #1
### 输入
```
8
1 2 -3 4 -5 5 2 3
```
### 输出
```
14
```

## 样例 #2
### 输入
```
6
1 -2 3 -4 5 -6
```
### 输出
```
9
```

## 样例 #3
### 输入
```
6
1 2 3 4 5 6
```
### 输出
```
21
```

### 算法分类
枚举

### 综合分析与结论
这些题解思路大致相同，均基于枚举法。由于要形成正多边形，其顶点数必为 $n$ 的因子且大于等于3 。各题解通过枚举 $n$ 的因子作为正多边形边长（顶点间距），再枚举起点，统计每种情况下顶点值之和，取最大值。不同点在于部分题解对特殊情况（如 $n$ 为质数或4）进行了特判，部分题解在代码实现上采用了不同方式（如快读、自定义函数等）以及对时间复杂度优化程度略有差异。

### 所选的题解
- **作者：cst_123 (4星)**
    - **关键亮点**：思路清晰，代码简洁，利用快读优化输入，在枚举因子时从2到 $n/3$ ，减少不必要枚举。
    - **重点代码**：
```cpp
long long read(){//快读
   long long x=0,sg=1;char cha=getchar();
   while(cha<'0'||cha>'9'){if(cha=='-')sg=-1;cha=getchar();}
   while(cha>='0'&&cha<='9'){x=x*10+cha-'0';cha=getchar();}
   return x*sg;
}
long long n,ans,sum;
long long a[20010];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		ans+=a[i];
       		//将全部统计
	}
	for(int i=2;i<=n/3;i++){
    		//枚举正 m 边形的边长
		if(!(n%i))
			for(int j=1;j<=i;j++){
            		//枚举起点
				sum=0;//清0
				for(int k=j;k<=n;k+=i)
					sum+=a[k];
                 			//统计该次的结果
				ans=max(ans,sum);//是最大值
			}
	}
	printf("%lld\n",ans);
	return 0;
}
```
核心实现思想：先通过快读输入数据并计算所有数总和作为初始答案，然后枚举可能的边长（$n$ 的因子且范围在2到 $n/3$ ），对每个边长枚举起点，计算该情况下顶点值之和并更新最大值。

- **作者：PR_CYJ (4星)**
    - **关键亮点**：代码简洁明了，逻辑清晰，直接按枚举因子、起点、求和取最大值的思路实现。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,maxx=0;//maxx要设为 0 
	cin>>n;
	int a[n+10]={};
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		maxx+=a[i];//求出距离为 1时的值，即所有数的和 
	for(int i=2;i<=n/3;i++)//枚举距离 
		if (n%i==0)//距离是 n的因数 
			for(int j=1;j<=i;j++)//枚举起点 
			{
				int s=0;
				for(int k=j;k<=n;k+=i)//求和 
					s+=a[k];
				maxx=max(maxx,s);//找出最大值 
			}
	cout<<maxx<<endl;
}
```
核心实现思想：先读入数据并计算所有数总和作为初始最大值，接着枚举可能的边长（$n$ 的因子且范围在2到 $n/3$ ），对每个边长枚举起点，计算该情况下顶点值之和并更新最大值。

- **作者：LKY928261 (4星)**
    - **关键亮点**：对时间复杂度进行优化，采用成对枚举因子方式将枚举因子复杂度从 $O(n)$ 优化到 $O(\sqrt n)$ ，且代码结构清晰，通过自定义函数简化逻辑。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>

#define ll long long//祖传开ll（虽然本题可以不开）

using namespace std;

ll n,s,t,a[20005],i,j;

void work(ll x,ll y){//枚举以x为间隔，y为编号最小的点的多边形的点权和
	ll t=0,i;
	for(i=y;i<n;i+=x)t+=a[i];
	s=max(s,t);
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=0;i<n;i++){cin>>a[i];s+=a[i];}//读入+初始化最值
	if(n%2==0&&n!=4)work(2,0),work(2,1);//判断n能被2整除的情况
	for(i=3;i*i<=n;i++)if(n%i==0){//枚举n的因子
		for(j=0;j<i;j++)work(i,j);
		for(j=0;j<n/i;j++)work(n/i,j);
	}
	cout<<s<<"\n";
}
```
核心实现思想：读入数据并初始化最大值，对 $n$ 为偶数且不为4的情况单独处理，然后枚举 $n$ 的因子（优化为 $O(\sqrt n)$ 复杂度），对每个因子及其对应的另一个因子分别枚举起点，通过自定义函数计算并更新最大值。

### 最优关键思路或技巧
1. **枚举因子优化**：在枚举 $n$ 的因子时，将范围控制在 $[3, n/3]$ ，减少不必要的枚举情况，降低时间复杂度。如部分题解通过判断 $n\%i == 0$ 来确定因子，并从2开始枚举到 $n/3$ 。更进一步，像LKY928261的题解采用成对枚举因子方式，将枚举因子的时间复杂度从 $O(n)$ 优化到 $O(\sqrt n)$ 。
2. **合理初始化**：先计算所有数的和作为初始最大值，考虑了不删除任何冰雕的情况，减少后续判断分支。

### 拓展思路
此类题目属于基于几何性质（正多边形顶点等距）的枚举问题。类似题目通常会给定一些具有特定规律的元素排列，要求根据某种规则选取元素使得某个目标函数最优。解题套路一般是先分析题目中的规则所蕴含的数学关系（如本题正多边形顶点数与总点数的整除关系），然后利用这些关系确定枚举的范围和方式，通过枚举所有可能情况找到最优解。

### 洛谷相似题目推荐
1. **P1111 修复公路**：通过枚举时间来判断能否连通所有点，涉及到图的连通性与枚举思想。
2. **P1306 斐波那契公约数**：需要枚举斐波那契数列的项数来寻找最大公约数，考查数论与枚举。
3. **P1463 [POI2002][HAOI2007]反素数**：通过枚举约数个数等条件来寻找反素数，综合了数论和枚举算法。 

---
处理用时：90.29秒