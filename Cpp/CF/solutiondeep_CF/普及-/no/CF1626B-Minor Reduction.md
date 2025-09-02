# 题目信息

# Minor Reduction

## 题目描述

You are given a decimal representation of an integer $ x $ without leading zeros.

You have to perform the following reduction on it exactly once: take two neighboring digits in $ x $ and replace them with their sum without leading zeros (if the sum is $ 0 $ , it's represented as a single $ 0 $ ).

For example, if $ x = 10057 $ , the possible reductions are:

- choose the first and the second digits $ 1 $ and $ 0 $ , replace them with $ 1+0=1 $ ; the result is $ 1057 $ ;
- choose the second and the third digits $ 0 $ and $ 0 $ , replace them with $ 0+0=0 $ ; the result is also $ 1057 $ ;
- choose the third and the fourth digits $ 0 $ and $ 5 $ , replace them with $ 0+5=5 $ ; the result is still $ 1057 $ ;
- choose the fourth and the fifth digits $ 5 $ and $ 7 $ , replace them with $ 5+7=12 $ ; the result is $ 10012 $ .

What's the largest number that can be obtained?

## 说明/提示

The first testcase of the example is already explained in the statement.

In the second testcase, there is only one possible reduction: the first and the second digits.

## 样例 #1

### 输入

```
2
10057
90```

### 输出

```
10012
9```

# AI分析结果

### 题目内容
# 小数化简

## 题目描述
给定一个无前导零的整数 $x$ 的十进制表示。

你必须对其恰好执行一次以下化简操作：选取 $x$ 中相邻的两个数字，并用它们的和（无 前导零，若和为 $0$ ，则表示为单个 $0$ ）替换这两个数字。

例如，若 $x = 10057$ ，可能的化简操作如下：
- 选择第一个和第二个数字 $1$ 和 $0$ ，将它们替换为 $1 + 0 = 1$ ；结果为 $1057$ ；
- 选择第二个和第三个数字 $0$ 和 $0$ ，将它们替换为 $0 + 0 = 0$ ；结果同样为 $1057$ ；
- 选择第三个和第四个数字 $0$ 和 $5$ ，将它们替换为 $0 + 5 = 5$ ；结果仍为 $1057$ ；
- 选择第四个和第五个数字 $5$ 和 $7$ ，将它们替换为 $5 + 7 = 12$ ；结果为 $10012$ 。

问能得到的最大数字是多少？

## 说明/提示
示例中的第一个测试用例在题目描述中已解释。

在第二个测试用例中，只有一种可能的化简操作：对第一个和第二个数字进行操作。

## 样例 #1
### 输入
```
2
10057
90
```
### 输出
```
10012
9
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略。首先证明操作后的数一定小于原来的数，然后分情况讨论：当存在相邻两数之和大于9时，为使结果最大，应选择最靠近个位的这样一对数进行操作，因为这样对原数减小的影响最小；当不存在相邻两数之和大于9时，应操作前两位，以保证最高位最大。各题解在代码实现上略有不同，如遍历方向、存储方式等，但整体思路一致。

### 所选的题解
- **作者：gzlinzy (5星)**
    - **关键亮点**：思路清晰，先证明操作后数变小，再详细分析两种情况，得出贪心策略，代码简洁明了。
    - **重点代码核心实现思想**：通过遍历字符串，判断相邻字符代表数字之和是否大于9，记录满足条件的位置，最后按规则输出结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,f,lena;
string a;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>a;
		lena=a.length();
		for(int i=0;i<lena-1;i++)
			if(a[i]+a[i+1]-2*'0'>9)f=i;
		for(int i=0;i<f;i++)cout<<a[i];
		cout<<a[f]+a[f+1]-2*'0';
		for(int i=f+2;i<lena;i++)cout<<a[i];
		cout<<endl;
		f=0;
	}
}
```
- **作者：哈士奇憨憨 (4星)**
    - **关键亮点**：简洁阐述题目大意和思路，代码逻辑清晰，易于理解。
    - **重点代码核心实现思想**：同样遍历字符串判断相邻数字和是否进位，记录位置，按规则输出新数。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	cin >> t;
	while(t--){
		cin >> s;
		int j = 0;
		for(int i = 0; i < s.size() - 1; i++){
			if(s[i] - '0' + s[i + 1] - '0' >= 10){//判断是否进位
				j = i;//记录相加位置
			}
		}
		for(int i = 0; i < j; i++){
			cout << s[i];
		}
		cout << s[j] - '0' + s[j + 1] - '0';//相加的两个数做特殊处理
		for(int i = j + 2; i < s.size(); i++){
			cout << s[i];
		}
		cout << endl;	
	}
 } 
```
- **作者：Argon_Cube (4星)**
    - **关键亮点**：对解题思路阐述详细，从结果位数变化和权重角度分析，得出贪心选择策略。
    - **重点代码核心实现思想**：从后向前遍历字符串找相邻数字和大于9的位置，若找到则修改字符串，否则操作前两位并输出。
```cpp
#include <iostream>
#include <string>
#include <array>

using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		string tmp;
		bool flag=false;
		cin>>tmp;
		int len=tmp.size()-1;
		for(int i=len;~i;i--)
			if(tmp[i]+tmp[i+1]-2*'0'>9)
			{
				int temp=tmp[i]+tmp[i+1]-2*'0';
				tmp[i]=temp/10+'0',tmp[i+1]=temp%10+'0',flag=true;
				break;
			}
		if(flag)
		{
			cout<<tmp<<'\n';
			continue;
		}
		cout<<(char)(tmp[0]+tmp[1]-'0');
		for(int i=2;i<=len;i++)
			cout<<tmp[i];
		cout<<'\n';
	}
	return 0;
}
```

### 最优关键思路或技巧
贪心策略的运用，根据相邻数字和与9的大小关系，分别从数的权重较小和较大处进行操作，以获取最大结果。在代码实现上，利用字符串存储整数，方便对各个数位进行操作。

### 拓展
同类型题通常围绕数字的操作与优化，如对数字的拆分、合并、重新排列等，通过贪心策略寻找最优解。类似算法套路是先分析不同操作对结果的影响，再根据影响确定贪心选择方向。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) 

---
处理用时：39.01秒