# 题目信息

# Maximum Strength

## 题目描述

Fedya is playing a new game called "The Legend of Link", in which one of the character's abilities is to combine two materials into one weapon. Each material has its own strength, which can be represented by a positive integer $ x $ . The strength of the resulting weapon is determined as the sum of the absolute differences of the digits in the decimal representation of the integers at each position.

Formally, let the first material have strength $ X = \overline{x_{1}x_{2} \ldots x_{n}} $ , and the second material have strength $ Y = \overline{y_{1}y_{2} \ldots y_{n}} $ . Then the strength of the weapon is calculated as $ |x_{1} - y_{1}| + |x_{2} - y_{2}| + \ldots + |x_{n} - y_{n}| $ . If the integers have different lengths, then the shorter integer is padded with leading zeros.

Fedya has an unlimited supply of materials with all possible strengths from $ L $ to $ R $ , inclusive. Help him find the maximum possible strength of the weapon he can obtain.

An integer $ C = \overline{c_{1}c_{2} \ldots c_{k}} $ is defined as an integer obtained by sequentially writing the digits $ c_1, c_2, \ldots, c_k $ from left to right, i.e. $ 10^{k-1} \cdot c_1 + 10^{k-2} \cdot c_2 + \ldots + c_k $ .

## 说明/提示

In the first test case, the weapon made from materials with strengths $ 53 $ and $ 57 $ will have the maximum possible strength: $ |5 - 5| + |3 - 7| = 4 $ .

In the second test case, the maximum strength is achieved with materials with strengths $ 190 $ and $ 209 $ : $ |1 - 2| + |9 - 0| + |0 - 9| = 19 $ .

In the fourth test case, there is only one valid strength, so the answer is $ 0 $ .

In the sixth test case, the maximum strength is achieved with materials with strengths $ 1909 $ and $ 90 $ : $ |1 - 0| + |9 - 0| + |0 - 9| + |9 - 0| = 28 $ . Note that the shorter integer was padded with leading zeros.

## 样例 #1

### 输入

```
6
53 57
179 239
13 37
132228 132228
54943329752812629795 55157581939688863366
88 1914```

### 输出

```
4
19
11
0
163
28```

# AI分析结果

### 题目内容（已翻译）
# 最大强度

## 题目描述
费迪亚正在玩一款名为《林克传奇》的新游戏，在游戏中，角色的一项能力是将两种材料合成一件武器。每种材料都有自己的强度，可用正整数 $x$ 表示。合成武器的强度由两种材料十进制表示中每一位数字差的绝对值之和决定。

形式上，设第一种材料的强度为 $X = \overline{x_{1}x_{2} \ldots x_{n}}$，第二种材料的强度为 $Y = \overline{y_{1}y_{2} \ldots y_{n}}$。那么武器的强度计算为 $ |x_{1} - y_{1}| + |x_{2} - y_{2}| + \ldots + |x_{n} - y_{n}| $。如果两个整数的长度不同，则在较短的整数前面补零。

费迪亚拥有从 $L$ 到 $R$（包括 $L$ 和 $R$）的所有可能强度的材料，且数量无限。请帮助他找出他能获得的武器的最大可能强度。

整数 $C = \overline{c_{1}c_{2} \ldots c_{k}}$ 定义为按从左到右的顺序依次写出数字 $c_1, c_2, \ldots, c_k$ 得到的整数，即 $ 10^{k - 1} \cdot c_1 + 10^{k - 2} \cdot c_2 + \ldots + c_k $。

## 说明/提示
在第一个测试用例中，由强度为 $53$ 和 $57$ 的材料制成的武器将具有最大可能强度：$ |5 - 5| + |3 - 7| = 4 $。

在第二个测试用例中，强度为 $190$ 和 $209$ 的材料能达到最大强度：$ |1 - 2| + |9 - 0| + |0 - 9| = 19 $。

在第四个测试用例中，只有一种有效的强度，所以答案是 $0$。

在第六个测试用例中，强度为 $1909$ 和 $90$ 的材料能达到最大强度：$ |1 - 0| + |9 - 0| + |0 - 9| + |9 - 0| = 28 $。请注意，较短的整数前面补了零。

## 样例 #1
### 输入
```
6
53 57
179 239
13 37
132228 132228
54943329752812629795 55157581939688863366
88 1914
```
### 输出
```
4
19
11
0
163
28
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法。由于数据范围较大，超过了 `unsigned long long` 范围，所以都采用字符串来处理输入。主要思路是先将两个数的长度补齐，然后从最高位开始比较，若某一位不同，则该位的差加上后面位数乘 $9$ 就是最大强度，因为后面的位可以取 $0$ 和 $9$ 使差值最大。若所有位都相同，则最大强度为 $0$。

### 所选题解
- **作者：LukeLuke (赞：6)，4星**
  - **关键亮点**：思路清晰，代码简洁，对贪心策略的解释详细，通过反转字符串方便补零和处理相同前缀。
  - **核心代码**：
```c++
#include <bits/stdc++.h>
using namespace std;
 
const int N = 110;
char l[N], r[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
    	scanf("%s%s", l, r);
        int n = strlen(l), m = strlen(r);
        reverse(l, l + n);
        reverse(r, r + m);
        for (int i = n; i < m; i++) l[n++] = '0';
        while (n && l[n - 1] == r[m - 1]) --n, --m;
        if (!n) puts("0");
        else printf("%d\n", (n - 1) * 9 + abs(l[n - 1] - r[n - 1]));
    }
    return 0;
} 
```
  - **核心实现思想**：先反转字符串，方便在较短字符串后面补零。然后去掉相同的高位，若去掉后没有剩余位，则输出 $0$，否则计算最高位的差加上后面位数乘 $9$ 作为结果。

- **作者：Mr_Biantainne (赞：4)，4星**
  - **关键亮点**：对贪心策略的要点解释清晰，代码使用 `string` 类型，更符合现代 C++ 风格。
  - **核心代码**：
```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll t;
string a, b;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> a >> b;
        reverse(a.begin(), a.end()), reverse(b.begin(), b.end()); //反转，方便添加0
        while (a.size() < b.size()) a.push_back('0'); //如果第一个数字位数少就加0
        while (a.size() > b.size()) b.push_back('0'); //如果第二个数字位数少就加0
        ll p = a.size() - 1;
        while (p >= 0 && a[p] == b[p]) p--; //去掉相同的高位
        if (p == -1) cout << 0 << endl; //什么都没有，两个数字完全一样，答案只能为0
        else cout << abs(a[p] - b[p]) + p * 9 << endl; //下一位计算上下限，然后后面随便取
    }
}
```
  - **核心实现思想**：反转字符串后补零，去掉相同的高位，若所有位都相同则输出 $0$，否则计算最高位的差加上后面位数乘 $9$ 作为结果。

- **作者：fantastic_dream (赞：2)，4星**
  - **关键亮点**：对贪心思路的推理过程有一定阐述，考虑了位数不同时的分类讨论。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
string a,b;
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>a>>b;
		int len1=a.size(),len2=b.size(),ans=0,cnt;
		if(len1!=len2){
			if(len1>len2)	swap(a,b),swap(len1,len2);//别忘了交换 len1,len2! 
			for(int i=0;i<len2-1;i++){
				ans+=9;
			}
			ans+=b[0]-'0';
			cout<<ans<<'\n';
			continue;
		}
		cnt=len1;
		for(int i=0;i<len1;i++){
			if(a[i]!=b[i]){
				ans+=abs(b[i]-a[i]);
				cnt=i+1;
				break;
			}	
		}
		ans+=9*(len1-cnt);
		cout<<ans<<'\n';
	}
	return 0;
}
```
  - **核心实现思想**：若位数不同，较短数后面补零，结果为后面位数乘 $9$ 加上较长数最高位的值；若位数相同，找到第一个不同的位，计算该位的差加上后面位数乘 $9$ 作为结果。

### 最优关键思路或技巧
- **使用字符串处理大整数**：由于数据范围超过了 `unsigned long long`，使用字符串存储和处理输入，避免了整数溢出问题。
- **贪心策略**：找到第一个不同的位，后面的位取 $0$ 和 $9$ 使差值最大，从而得到最大强度。

### 拓展思路
同类型题可能会改变材料合成武器的规则，或者增加更多的限制条件，但核心思路可能还是贪心策略。类似的算法套路可以应用在其他需要在一定范围内寻找最优解的问题中，通过分析问题的特点，找到局部最优的选择，从而得到全局最优解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略合并果子，使总代价最小。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：使用贪心算法安排排队顺序，使平均等待时间最短。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：利用贪心策略选择最多的线段进行覆盖。

### 个人心得摘录与总结
- **fantastic_dream**：提到在交换两个数时，记得交换两数的长度，避免出现错误，提醒在处理字符串和长度相关操作时要细心。 

---
处理用时：56.51秒