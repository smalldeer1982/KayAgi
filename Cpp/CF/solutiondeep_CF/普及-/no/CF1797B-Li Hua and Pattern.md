# 题目信息

# Li Hua and Pattern

## 题目描述

Li Hua has a pattern of size $ n\times n $ , each cell is either blue or red. He can perform exactly $ k $  operations. In each operation, he chooses a cell and changes its color from red to blue or from blue to red. Each cell can be chosen as many times as he wants. Is it possible to make the pattern, that matches its rotation by $ 180^{\circ} $ ?

Suppose you were Li Hua, please solve this problem.

## 说明/提示

In test case 1, you can't perform any operation. The pattern after rotation is on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/debd4989c6daceeecb5305f7cb7ec257866c6bf5.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/187295f499fcefe17d924d6eb93da50e9773c4d3.png)In test case 2, you can perform operations on $ (2,1),(3,2),(3,4) $ . The pattern after operations is in the middle and the pattern after rotation is on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/0c0aed7c9c5dddd78137bdc2f8654231a7026420.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/3b36bd2af8c0789e62f808d71f3af4107dad02c2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/3b36bd2af8c0789e62f808d71f3af4107dad02c2.png)

## 样例 #1

### 输入

```
3
4 0
1 1 1 1
0 0 0 1
1 0 1 0
1 1 1 1
4 3
1 0 1 1
1 0 0 0
0 1 0 1
1 1 0 1
5 4
0 0 0 0 0
0 1 1 1 1
0 1 0 0 0
1 1 1 1 1
0 0 0 0 0```

### 输出

```
NO
YES
YES```

# AI分析结果

### 题目内容
# 李华与图案

## 题目描述
李华有一个 $n\times n$ 的图案，每个单元格要么是蓝色要么是红色。他可以恰好执行 $k$ 次操作。在每次操作中，他选择一个单元格并将其颜色从红色变为蓝色或从蓝色变为红色。每个单元格可以根据需要被选择多次。是否有可能使图案在旋转 $180^{\circ}$ 后与原图案匹配？

假设你是李华，请解决这个问题。

## 说明/提示
在测试用例1中，你不能执行任何操作。旋转后的图案在右边。

![图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/debd4989c6daceeecb5305f7cb7ec257866c6bf5.png)
![图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/187295f499fcefe17d924d6eb93da50e9773c4d3.png)
在测试用例2中，你可以对 $(2,1)$、$(3,2)$、$(3,4)$ 执行操作。操作后的图案在中间，旋转后的图案在右边。

![图片3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/0c0aed7c9c5dddd78137bdc2f8654231a7026420.png)
![图片4](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/3b36bd2af8c0789e62f808d71f3af4107dad02c2.png)
![图片5](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/3b36bd2af8c0789e62f808d71f3af4107dad02c2.png)

## 样例 #1
### 输入
```
3
4 0
1 1 1 1
0 0 0 1
1 0 1 0
1 1 1 1
4 3
1 0 1 1
1 0 0 0
0 1 0 1
1 1 0 1
5 4
0 0 0 0 0
0 1 1 1 1
0 1 0 0 0
1 1 1 1 1
0 0 0 0 0
```
### 输出
```
NO
YES
YES
```

### 算法分类
数学

### 综合分析与结论
这些题解思路基本一致，核心都是通过比较原图案与其旋转180°后对应位置的颜色差异，计算出最少修改次数，再结合给定的操作次数k和图案边长n的奇偶性来判断是否能达成目标。
1. **思路**：遍历图案，对比每个单元格与其旋转180°后对应位置的颜色，若不同则记录。由于遍历全图会使每对不同的对应单元格被计算两次，所以记录的总数需除以2得到最少修改次数mink。然后比较mink与k的大小，若k小于mink则直接输出NO；若k大于等于mink，再根据n的奇偶性判断：n为奇数时一定能达成（因可通过修改中心格满足操作次数）；n为偶数时，需判断k - mink的奇偶性，若为偶数则能达成，否则不能。
2. **算法要点**：准确找出旋转180°后的对应位置，正确统计颜色不同的单元格对数并除以2，合理根据n和k - mink的奇偶性判断结果。
3. **解决难点**：理解并处理好操作次数与图案中心对称要求之间的关系，特别是在n为偶数时，剩余操作次数的奇偶性对结果的影响。

### 所选的题解
- **作者：qifan_maker (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，直接按核心思路实现，无冗余代码。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n,k;
		cin >> n >> k;
		int a[1100][1100];
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				cin >> a[i][j];
			}
		}
		int mink = 0;
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				if (a[i][j]!= a[n-i+1][n-j+1]){
					mink++;
				}
			}
		}
		mink /= 2;
		if (k < mink){
			cout << "NO" << endl;
		}
		else {
			if (n%2 == 0){
				if ((k-mink)%2 == 0){
					cout << "YES" << endl;
				}
				else {
					cout << "NO" << endl;
				}
			}
			else {
				cout << "YES" << endl;
			}
		}
	}
	return 0;
}
```
核心实现思想：先读入图案和操作次数，通过双重循环遍历图案计算最少修改次数mink，然后根据mink与k的关系及n的奇偶性输出结果。
- **作者：jiangchen1234 (4星)**
    - **关键亮点**：代码模块化，将输入和核心判断部分分开，提高了代码的可读性和可维护性。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2000;
long long t,n,k,a[maxn][maxn];
bool p;
string st;
void in(long long n) {//输入
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin>>a[i][j];
		}
	}
}
bool find(long long d) {//核心步骤
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(a[i][j]!= a[n - i + 1][n - j + 1]) {//判定
				ans++;
			}
		}
	}
	ans /= 2;//重复了两遍，要除2
	if (ans > d) return 0;//比标准多 返回false
	if(ans % 2 == d % 2 or n % 2 == 1) {
		return 1;
	} else {
		return 0;
	}
}
int main() {
	cin>>t;
	for(int i = 0; i < t; i++) {
		cin>>n>>k;
		in(n);
		if(find(k)) {
			cout<<"YES"<<endl;
		} else {
			cout<<"NO"<<endl;
		}
	}
```
核心实现思想：通过in函数读入图案，find函数计算最少修改次数并判断是否满足条件，main函数控制流程并输出结果。
- **作者：ylch (4星)**
    - **关键亮点**：在题解中详细解释了中心对称图形的概念和数组下标递推式，对理解题目有很大帮助，代码实现简洁且符合核心思路。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1100][1100];
int T,n,k;

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n >> k;
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				cin >> a[i][j];
		int ans = 0;
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				if (a[i][j]!= a[n-i+1][n-j+1])	ans++;
		ans /= 2;
		if (k < ans)
		{
			puts("NO");
		}
		else
		{
			if (n%2 == 0)
				puts((k-ans)%2==0? "YES" : "NO");
			if (n%2 == 1)
				puts("YES");
		}
	}
	return 0;
}
```
核心实现思想：读入数据后，通过双重循环统计颜色不同的单元格对数并计算最少修改次数，再根据与k的关系及n的奇偶性输出结果。

### 最优关键思路或技巧
1. **思维方式**：抓住中心对称图案的本质特征，即通过比较原图案与其旋转180°后对应位置的颜色来确定修改次数，这种利用图形对称性质的思维方式是解题关键。
2. **代码实现技巧**：合理利用循环遍历图案，注意计算修改次数时避免重复计算，以及根据n和k的关系进行清晰的条件判断。

### 同类型题或类似算法套路拓展
同类型题通常围绕图形的对称性质与操作次数限制展开，类似算法套路是先确定图形变换后的对应关系，计算满足条件的最少操作次数，再结合给定操作次数及其他条件（如奇偶性）判断可行性。

### 推荐洛谷题目
1. **P1080 [NOIP2012 提高组] 国王游戏**：涉及数学推理和贪心策略，通过分析数据间的数学关系来确定最优解，与本题通过分析图案对称的数学关系解题类似。
2. **P2671 [NOIP2015 提高组] 求和**：需要运用数学知识对题目条件进行推导和计算，与本题在利用数学方法解决问题上思路相似。
3. **P1147 连续自然数和**：通过数学分析找到满足条件的连续自然数序列，考验对数学关系的理解和运用，与本题分析图案对称关系解题思路有共通之处。 

---
处理用时：75.14秒