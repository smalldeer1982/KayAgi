# 题目信息

# 24 Game

## 题目描述

Little X used to play a card game called "24 Game", but recently he has found it too easy. So he invented a new game.

Initially you have a sequence of $ n $ integers: $ 1,2,...,n $ . In a single step, you can pick two of them, let's denote them $ a $ and $ b $ , erase them from the sequence, and append to the sequence either $ a+b $ , or $ a-b $ , or $ a×b $ .

After $ n-1 $ steps there is only one number left. Can you make this number equal to $ 24 $ ?

## 样例 #1

### 输入

```
1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
8
```

### 输出

```
YES
8 * 7 = 56
6 * 5 = 30
3 - 4 = -1
1 - 2 = -1
30 - -1 = 31
56 - 31 = 25
25 + -1 = 24
```

# AI分析结果

### 题目重写
# 24点游戏

## 题目描述
小X过去常玩一种叫做“24点游戏”的纸牌游戏，但最近他觉得这太简单了。于是他发明了一个新游戏。

最初，你有一个包含 \(n\) 个整数的序列：\(1,2,\cdots,n\) 。在每一步中，你可以选择其中两个数，设为 \(a\) 和 \(b\) ，将它们从序列中删除，并在序列中添加 \(a + b\)，或 \(a - b\)，或 \(a×b\) 。

经过 \(n - 1\) 步后，序列中只剩下一个数字。你能使这个数字等于 \(24\) 吗？

## 样例 #1
### 输入
```
1
```
### 输出
```
NO
```
## 样例 #2
### 输入
```
8
```
### 输出
```
YES
8 * 7 = 56
6 * 5 = 30
3 - 4 = -1
1 - 2 = -1
30 - -1 = 31
56 - 31 = 25
25 + -1 = 24
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分析规律来解决问题。所有题解都指出 \(n < 4\) 时无法得到 \(24\) ，而 \(n \geq 4\) 时可以通过特定运算组合得到 \(24\) ，并利用相邻数字相减得 \(1\) 或通过特定数字组合得 \(0\) 的方式，来维持最终结果为 \(24\) 。不同之处在于对于 \(n \geq 4\) 时具体凑 \(24\) 的方式以及处理剩余数字的细节略有差异。

### 所选的题解
- **作者：ftcly (赞：8) - 5星**
    - **关键亮点**：思路清晰，简洁明了地给出了不同 \(n\) 取值下凑 \(24\) 的具体运算步骤，代码实现直接。
    - **个人心得**：提到开始想用深搜，在乱算时发现有规律可找，还强调了输出要打空格。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;//输入 
    if(n<4)//4以下直接输出NO
    {
        cout<<"NO"<<endl;
        return 0;
    }
    else//其他n取值一定能过
    cout<<"YES"<<endl;
    if (n%2){		//偶数情况
    cout<<" 3 * 5 = 15"<<endl<<"2 * 4 = 8"<<endl<<"15 + 8 = 23"<<endl<<"23 + 1 = 24"<<endl;//先算出24
    for (int i=n;i>=6;i-=2) 
        cout<<i<<" - "<<i-1<<" = 1"<<endl<<"24 * 1 = 24"<<endl;//每次用第i个和第i-1个数维持24
    }
    else{		//奇数
    cout<<"1 + 2 = 3"<<endl<<"3 + 3 = 6"<<endl<<"4 * 6 = 24"<<endl;
    for (int i=n;i>=5;i-=2) 
        cout<<i<<" - "<<i-1<<" = 1"<<endl<<"24 * 1 = 24"<<endl;  //同上
    }
    return 0;
}   
```
- **作者：wmrqwq (赞：6) - 5星**
    - **关键亮点**：解题思路阐述详细，先简述题目，再清晰地证明 \(n \geq 4\) 时一定能构造出方案，并给出 \(1 \sim 4\) 和 \(1 \sim 5\) 凑 \(24\) 点的具体方法，代码逻辑清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long n;
int main()
{
	cin>>n;
	if(n<=3)//如果n小于4
	{
		cout<<"NO";//直接输出NO
		return 0;
	}
	else//如果n大于等于4
	{
		cout<<"YES"<<endl;//输出YES
		if(n%2)//如果n为奇数
		{
			cout<<"2 * 4 = 8"<<endl<<"3 * 5 = 15"<<endl<<"15 + 8 = 23"<<endl<<"23 + 1 = 24"<<endl;
			for(int i=n;i>5;i-=2)//将剩下的数依次相减
				cout<<i<<" - "<<i-1<<" = "<<"1"<<endl<<"24 * 1 = 24"<<endl;			
		}
		else//如果n为偶数
		{
			cout<<"1 * 2 = 2"<<endl<<"2 * 3 = 6"<<endl<<"4 * 6 = 24"<<endl;
			for(int i=n;i>4;i-=2)//将剩下的数依次相减
				cout<<i<<" - "<<i-1<<" = "<<"1"<<endl<<"24 * 1 = 24"<<endl;
		}
	}
	QwQ;
}
```
- **作者：lianchanghua (赞：3) - 4星**
    - **关键亮点**：先在纸上模拟找出规律，对奇数和偶数情况分别给出清晰的凑 \(24\) 步骤和代码实现，注释详细。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main(){
    int n;
    cin>>n;  
	if(n<4){//4以下无解 
		cout<<"NO";
		exit(0);
	}
    cout<<"YES"<<"\n";
    if(n%2){//判断奇偶
    	//奇数情况 
    	cout<<"5 * 4 = 20"<<"\n";
		cout<<"20 + 3 = 23"<<"\n";
		cout<<"23 + 2 = 25"<<"\n";
		cout<<"25 - 1 = 24"<<"\n";
		for(int i=n;i>=6;i-=2){
			cout<<i<<" - "<<i-1<<" = "<<"1"<<"\n";
			cout<<"24 * 1 = 24"<<"\n";
		}
	}
    else{
    	//偶数情况 
		cout<<"1 * 2 = 2"<<"\n";
		cout<<"2 * 3 = 6"<<"\n";
		cout<<"4 * 6 = 24"<<"\n";
		for(int i=n;i>=5;i-=2){
			cout<<i<<" - "<<i-1<<" = "<<"1"<<"\n";
			cout<<"24 * 1 = 24"<<"\n";
		}
    }
    return 0;
}
```
### 最优关键思路或技巧
通过对较小 \(n\) 值进行模拟运算，发现 \(n < 4\) 无法凑出 \(24\) ，而 \(n \geq 4\) 时，可以针对 \(n\) 的奇偶性分别找出固定的数字组合凑出 \(24\) ，再利用相邻数字相减得 \(1\) ，与已凑出的 \(24\) 相乘维持结果为 \(24\) 。这种通过找规律、分类讨论的思维方式是解决本题的关键。

### 可拓展之处
同类型题通常是给定一些数字和运算规则，要求得到特定结果，类似算法套路是先对小数据进行分析找规律，再根据规律对大数据进行处理。

### 推荐题目
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析和枚举解决连续自然数求和问题，与本题找规律解题思路类似。
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过对数据的分析和简单运算得出结果，考察数学思维和代码实现能力。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同套餐价格计算最优购买方案，涉及数学计算和逻辑判断。 

---
处理用时：58.65秒