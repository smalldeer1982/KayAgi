# 题目信息

# Magical Array

## 题目描述

Valery is very interested in magic. Magic attracts him so much that he sees it everywhere. He explains any strange and weird phenomenon through intervention of supernatural forces. But who would have thought that even in a regular array of numbers Valera manages to see something beautiful and magical.

Valera absolutely accidentally got a piece of ancient parchment on which an array of numbers was written. He immediately thought that the numbers in this array were not random. As a result of extensive research Valera worked out a wonderful property that a magical array should have: an array is defined as magic if its minimum and maximum coincide.

He decided to share this outstanding discovery with you, but he asks you for help in return. Despite the tremendous intelligence and wit, Valera counts very badly and so you will have to complete his work. All you have to do is count the number of magical subarrays of the original array of numbers, written on the parchment. Subarray is defined as non-empty sequence of consecutive elements.

## 说明/提示

Notes to sample tests:

Magical subarrays are shown with pairs of indices \[a;b\] of the beginning and the end.

In the first sample: \[1;1\], \[2;2\], \[3;3\], \[4;4\], \[2;3\].

In the second sample: \[1;1\], \[2;2\], \[3;3\], \[4;4\], \[5;5\], \[1;2\], \[2;3\], \[1;3\].

## 样例 #1

### 输入

```
4
2 1 1 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
-2 -2 -2 0 1
```

### 输出

```
8
```

# AI分析结果

### 题目内容中文重写
# 神奇数组

## 题目描述
瓦列里对魔法非常感兴趣。魔法对他的吸引力极大，以至于他在任何地方都能看到魔法。他用超自然力量的干预来解释任何奇怪和怪异的现象。但谁能想到，即使在一个普通的数字数组中，瓦列里也能看到一些美丽而神奇的东西。

瓦列里偶然得到了一张古老的羊皮纸，上面写着一个数字数组。他立刻认为这个数组中的数字不是随机的。经过大量的研究，瓦列里得出了一个神奇数组应具备的奇妙性质：如果一个数组的最小值和最大值相等，那么这个数组就被定义为神奇数组。

他决定与你分享这一杰出的发现，但作为回报，他向你寻求帮助。尽管瓦列里非常聪明和机智，但他的计算能力很差，所以你将不得不完成他的工作。你所要做的就是计算写在羊皮纸上的原始数字数组中神奇子数组的数量。子数组被定义为连续元素的非空序列。

## 说明/提示
样例测试的注释：
神奇子数组用起始和结束的索引对 `[a;b]` 表示。

在第一个样例中：`[1;1]`，`[2;2]`，`[3;3]`，`[4;4]`，`[2;3]`。

在第二个样例中：`[1;1]`，`[2;2]`，`[3;3]`，`[4;4]`，`[5;5]`，`[1;2]`，`[2;3]`，`[1;3]`。

## 样例 #1
### 输入
```
4
2 1 1 4
```
### 输出
```
5
```

## 样例 #2
### 输入
```
5
-2 -2 -2 0 1
```
### 输出
```
8
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是一致的，即先明确神奇数组的定义为数组中所有元素都相等，然后找出原数组中所有连续且元素相同的子数组，对于长度为 $n$ 的这样的子数组，其内部神奇子数组的数量为 $\frac{n(n + 1)}{2}$，最后将所有这样的子数组的神奇子数组数量累加起来得到最终结果。

各题解的算法要点主要是通过遍历数组，判断相邻元素是否相等来确定连续相同元素的子数组长度，再利用公式计算子数组数量。解决的难点在于正确处理数组的边界情况，即最后一段连续相同元素的子数组也需要计算其神奇子数组数量。

### 所选题解
- **zhangyuhao9（4星）**
  - **关键亮点**：思路清晰，代码注释详细，易于理解。
  - **个人心得**：无
- **diqiuyi（4星）**
  - **关键亮点**：对思路的阐述较为详细，包括对公式的证明，并且代码使用了快读优化。
  - **个人心得**：提到了 $nowl$ 初始值的处理技巧，省去了对第一次输入的特判。
- **xiaomuyun（4星）**
  - **关键亮点**：对代码实现的各个步骤分析详细，同时提醒了数据范围和输出格式的注意事项。
  - **个人心得**：提到自己犯了给 `ans` 开 `long long` 后，`printf` 忘记写 `%lld` 的错误。

### 重点代码
#### zhangyuhao9 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100001],ans=0;
int main(){
    long long n;
    cin>>n;    //输入第一行的数
    long long num=0;   //将计数初始化为0
    for(int i=1;i<=n;i++){
        cin>>a[i];       //将数组输入
        if(a[i]!=a[i-1]){   //如果相邻两数不相等
            ans=ans+num*(num+1)/2;    //更新答案
            num=1;
        }
        else{     //如果相邻两数相等
            num++;     //答案再加一
        }
    }
    ans=ans+num*(num+1)/2;      //最后统计总数
    cout<<ans;       //输出答案
    return 0;      //好习惯
}
```
**核心实现思想**：通过遍历数组，用 `num` 记录连续相同元素的个数，当相邻元素不同时，利用公式计算当前连续相同元素子数组的神奇子数组数量并累加到 `ans` 中，最后处理最后一段连续相同元素的子数组。

#### diqiuyi 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return f?x:-x;
}
int ans,nowl,a,b,n;
//a是新加入的数，b是上一个数，nowl是目前区间的长度
int main(){
	n=read();
	while(n--){
		a=read();
		if(a==b)
			nowl++;
		else{
			ans=ans+(nowl*nowl+nowl)/2;
			nowl=1;
			b=a;
		}
	}
	ans=ans+(nowl*nowl+nowl)/2;
	printf("%d\n",ans);
	return 0;
}
```
**核心实现思想**：使用快读读取输入，用 `nowl` 记录当前连续相同元素的区间长度，当新加入的元素与上一个元素不同时，计算当前区间的神奇子数组数量并累加到 `ans` 中，最后处理最后一个区间。

#### xiaomuyun 的代码
```cpp
#include<cstdio>

using namespace std;

long long n,f[100001],a[100001],ans=0;

int main(){
	scanf("%d",&n);
	for(long long i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]==a[i-1]) f[i]=f[i-1]+1;//计数器+1
		else {
			f[i]=1;
			ans+=(1+f[i-1])*f[i-1]/2;//否则做连续的数的和的运算
		}
	}
	ans+=(1+f[n])*f[n]/2;//第n项的特殊运算
	printf("%lld\n",ans);//是%lld！！！
	return 0;
}
```
**核心实现思想**：用数组 `f` 记录连续相同元素的个数，当相邻元素不同时，利用公式计算当前连续相同元素子数组的神奇子数组数量并累加到 `ans` 中，最后处理最后一个元素所在的子数组，同时注意输出格式。

### 最优关键思路或技巧
- **数学公式的运用**：利用 $\frac{n(n + 1)}{2}$ 这个公式快速计算长度为 $n$ 的连续相同元素子数组中神奇子数组的数量。
- **边界处理**：在遍历完数组后，要记得处理最后一段连续相同元素的子数组，避免遗漏。

### 可拓展之处
同类型题目可能会在数组元素的性质、子数组的定义等方面进行变化，例如可能会要求找出满足特定条件（如元素和为某个值）的连续子数组数量，或者在二维数组中找出满足条件的子矩阵数量等。解题的关键还是要找出规律，利用合适的数学公式进行计算。

### 推荐题目
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：涉及组合数学的思想，通过计算不同选择的组合数来求解问题。
- [P1734 最大约数和](https://www.luogu.com.cn/problem/P1734)：需要运用数学知识，找出数的约数并计算最大约数和。
- [P2670 扫雷游戏](https://www.luogu.com.cn/problem/P2670)：需要对矩阵进行遍历和判断，与本题的数组遍历思想有相似之处。

### 个人心得总结
- **xiaomuyun**：在给 `ans` 开 `long long` 后，`printf` 时要记得使用 `%lld` 输出格式，否则可能会导致结果错误。
- **diqiuyi**：在处理初始值时，可以巧妙利用输入的特性，省去对第一次输入的特判，使代码更简洁。

---
处理用时：54.39秒