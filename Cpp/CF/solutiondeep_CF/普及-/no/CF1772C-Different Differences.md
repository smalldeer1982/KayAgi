# 题目信息

# Different Differences

## 题目描述

An array $ a $ consisting of $ k $ integers is strictly increasing if $ a_1 < a_2 < \dots < a_k $ . For example, the arrays $ [1, 3, 5] $ , $ [1, 2, 3, 4] $ , $ [3, 5, 6] $ are strictly increasing; the arrays $ [2, 2] $ , $ [3, 7, 5] $ , $ [7, 4, 3] $ , $ [1, 2, 2, 3] $ are not.

For a strictly increasing array $ a $ of $ k $ elements, let's denote the characteristic as the number of different elements in the array $ [a_2 - a_1, a_3 - a_2, \dots, a_k - a_{k-1}] $ . For example, the characteristic of the array $ [1, 3, 4, 7, 8] $ is $ 3 $ since the array $ [2, 1, 3, 1] $ contains $ 3 $ different elements: $ 2 $ , $ 1 $ and $ 3 $ .

You are given two integers $ k $ and $ n $ ( $ k \le n $ ). Construct an increasing array of $ k $ integers from $ 1 $ to $ n $ with maximum possible characteristic.

## 样例 #1

### 输入

```
7
5 9
4 12
3 3
3 4
4 4
4 6
8 11```

### 输出

```
1 3 4 7 8
2 4 7 12
1 2 3
1 3 4
1 2 3 4
2 4 5 6
1 2 3 5 6 7 8 11```

# AI分析结果

### 题目内容
# 不同的差值

## 题目描述
一个由 $k$ 个整数组成的数组 $a$ 是严格递增的，如果 $a_1 < a_2 < \dots < a_k$ 。例如，数组 $[1, 3, 5]$ ，$[1, 2, 3, 4]$ ，$[3, 5, 6]$ 是严格递增的；数组 $[2, 2]$ ，$[3, 7, 5]$ ，$[7, 4, 3]$ ，$[1, 2, 2, 3]$ 则不是。

对于一个由 $k$ 个元素组成的严格递增数组 $a$ ，我们将其特征定义为数组 $[a_2 - a_1, a_3 - a_2, \dots, a_k - a_{k - 1}]$ 中不同元素的数量。例如，数组 $[1, 3, 4, 7, 8]$ 的特征是 $3$ ，因为数组 $[2, 1, 3, 1]$ 包含 $3$ 个不同的元素：$2$ ，$1$ 和 $3$ 。

给定两个整数 $k$ 和 $n$ （$k \le n$ ）。构造一个从 $1$ 到 $n$ 的长度为 $k$ 的递增数组，使其具有最大可能的特征。

## 样例 #1
### 输入
```
7
5 9
4 12
3 3
3 4
4 4
4 6
8 11
```
### 输出
```
1 3 4 7 8
2 4 7 12
1 2 3
1 3 4
1 2 3 4
2 4 5 6
1 2 3 5 6 7 8 11
```
### 算法分类
贪心

### 题解综合分析与结论
所有题解都采用贪心策略，核心思路是让相邻元素的差值尽量不同，理想情况下差值序列为 $[1, 2, 3, \cdots]$ 。难点在于构造过程中要保证数组元素不超过 $n$ ，且数组长度为 $k$ 。不同题解在处理超出 $n$ 限制的方式上有所差异，但本质都是在保证特征数尽量大的前提下，调整后续元素的生成方式。

### 所选的题解
- **作者：a2lyaXNhbWUgbWFyaXNh (5星)**
    - **关键亮点**：思路清晰简洁，通过数学公式直接计算出每个位置应取的值，代码实现高效且简洁。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int t,k,n;
	cin>>t;
	while(t--){
		cin>>k>>n;
		for(int i=1;i<=k;++i)
			cout<<min(1+i*(i-1)/2,n-k+i)<<" ";
		cout<<'\n';
	}
	return 0;
}
```
    - **核心实现思想**：对于数列的第 $i$ 项，通过 $\min(i\times\frac{1}{2}(i - 1), n - k + i)$ 计算，既保证了差值尽量不同，又避免超出 $n$ 的限制。
- **作者：CR7_houyetong (4星)**
    - **关键亮点**：对贪心思路的阐述详细，包括差值序列选择的原因以及处理超出 $n$ 限制的具体方法，代码有详细注释。
    - **个人心得**：鸣谢他人指出不妥之处，表明在解题过程中通过交流不断完善思路。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,i,j,k,cnt1,cnt2,a[10010];
signed main(){
	cin>>t;
	while (t--){
		cin>>k>>n;
		memset(a,0,sizeof(a));
		a[1]=1;
		cnt1=2;
		for (i=0;i<k;i++){
			if (n-a[cnt1-1]>k-2){
				a[cnt1]=a[cnt1-1]+cnt1-1;
				cnt1++;
			} 
			else{
				cnt2=a[cnt1-1]+1;
				for (j=cnt1;j<=k;j++){
					a[j]=cnt2;
					cnt2++;
				}
			}
		}
		for (i=1;i<=k;i++)
		  cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```
    - **核心实现思想**：先按差值递增构造数组，当发现剩余可增加的数不足以按原规律构造到长度 $k$ 时，从当前位置起让后续元素依次递增 $1$ 。
- **作者：ImNot6Dora (4星)**
    - **关键亮点**：代码简洁，通过巧妙的条件判断，直接在循环中处理不同情况，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int k,n;
		int ans=1;
		int cnt=0;
		cin>>k>>n;
		for(int i=1;i<=k;i++){
			if(n-ans-cnt>=k-i)ans+=cnt++;
			else ans++;
			cout<<ans<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```
    - **核心实现思想**：用 $ans$ 表示前一个数字，$cnt$ 表示差值，通过判断 $n - ans - cnt$ 与 $k - i$ 的大小关系，决定是继续按差值递增还是每次只增加 $1$ 。

### 最优关键思路或技巧
采用贪心策略，优先让相邻元素差值不同以最大化特征数。在处理 $n$ 的限制时，通过数学计算（如 $a2lyaXNhbWUgbWFyaXNh$ 的题解）或条件判断（如其他部分题解），在保证数组长度的同时，尽量维持差值的多样性。

### 拓展
此类题目属于构造类贪心问题，常见套路是先确定理想的构造模式，再根据题目限制条件进行调整。类似题目通常需要在满足一定约束条件下，构造出最优的序列或结构。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

---
处理用时：48.07秒