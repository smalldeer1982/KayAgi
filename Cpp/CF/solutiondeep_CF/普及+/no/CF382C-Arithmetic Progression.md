# 题目信息

# Arithmetic Progression

## 题目描述

Everybody knows what an arithmetic progression is. Let us remind you just in case that an arithmetic progression is such sequence of numbers $ a_{1},a_{2},...,a_{n} $ of length $ n $ , that the following condition fulfills:

 $ a_{2}-a_{1}=a_{3}-a_{2}=a_{4}-a_{3}=...=a_{i+1}-a_{i}=...=a_{n}-a_{n-1}. $ For example, sequences \[1, 5\], \[10\], \[5, 4, 3\] are arithmetic progressions and sequences \[1, 3, 2\], \[1, 2, 4\] are not.

Alexander has $ n $ cards containing integers. Arthur wants to give Alexander exactly one more card with a number so that he could use the resulting $ n+1 $ cards to make an arithmetic progression (Alexander has to use all of his cards).

Arthur has already bought a card but he hasn't written a number on it. Help him, print all integers that you can write on a card so that the described condition fulfilled.

## 样例 #1

### 输入

```
3
4 1 7
```

### 输出

```
2
-2 10
```

## 样例 #2

### 输入

```
1
10
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
1 3 5 9
```

### 输出

```
1
7
```

## 样例 #4

### 输入

```
4
4 3 4 5
```

### 输出

```
0
```

## 样例 #5

### 输入

```
2
2 4
```

### 输出

```
3
0 3 6
```

# AI分析结果

### 题目内容
# 等差数列

## 题目描述
每个人都知道什么是等差数列。以防万一，我们还是提醒一下，等差数列是这样一个长度为 $n$ 的数列 $a_{1},a_{2},\cdots,a_{n}$，满足以下条件：

$a_{2}-a_{1}=a_{3}-a_{2}=a_{4}-a_{3}=\cdots=a_{i + 1}-a_{i}=\cdots=a_{n}-a_{n - 1}$。例如，序列 \[1, 5\]，\[10\]，\[5, 4, 3\] 是等差数列，而序列 \[1, 3, 2\]，\[1, 2, 4\] 不是。

亚历山大有 $n$ 张写有整数的卡片。亚瑟想再给亚历山大一张卡片，上面写一个数字，使得他能用这 $n + 1$ 张卡片组成一个等差数列（亚历山大必须使用所有卡片）。

亚瑟已经买了一张卡片，但还没有在上面写数字。帮他找出所有可以写在卡片上的整数，使得上述条件成立。

## 样例 #1
### 输入
```
3
4 1 7
```
### 输出
```
2
-2 10
```

## 样例 #2
### 输入
```
1
10
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
4
1 3 5 9
```
### 输出
```
1
7
```

## 样例 #4
### 输入
```
4
4 3 4 5
```
### 输出
```
0
```

## 样例 #5
### 输入
```
2
2 4
```
### 输出
```
3
0 3 6
```

### 算法分类
数学

### 综合分析与结论
这三道题解都采用分类讨论的方式解决问题，核心思路都是根据 $n$ 的不同取值情况分别处理，先对输入数据排序，再分析能否构成等差数列及可插入数字的位置和值。
 - **思路方面**：都围绕 $n = 1$、$n = 2$、$n \geq 3$ 三种情况展开。$n = 1$ 时，题解1认为无解输出 -1，题解2认为有无限个答案但按题意输出 -1 ，题解3认为新数任意取；$n = 2$ 时，都考虑了在两端插入数字的情况，同时根据两数差的奇偶性判断中间能否插入数字；$n \geq 3$ 时，均先排序，再通过分析相邻数差值来确定是否为等差数列以及可插入数字的位置和值。
 - **算法要点**：排序后处理相邻数的差值，通过计数或比较确定可能的公差，再根据公差判断能否插入数字构成等差数列。
 - **解决难点**：$n \geq 3$ 时，如何准确判断原序列是否为等差数列，以及若不是，找到合适的插入位置和数字。题解1通过统计不同差值出现次数确定公差；题解2用 `map` 存储差值及出现次数找众数确定公差；题解3通过两次假设不同的公差，检查序列是否符合条件来确定可插入数字。

### 所选的题解
 - **作者：丧黑福造 (5星)**
    - **关键亮点**：思路清晰，对每种情况的分析细致全面，代码实现简洁明了，对特殊情况（如序列只有3个数时公差的选取）处理得当。
    - **重点代码核心实现思想**：先读入数据排序，根据 $n$ 的值分类讨论。$n = 1$ 直接输出 -1；$n = 2$ 判断两数间能否插入数字并输出结果；$n \geq 3$ 时，统计不同相邻数差值出现次数确定公差，再判断能否插入数字及输出结果。
```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
int a[100005];
main(){
    int cnt, n, d, ans, td, td1, c1, c2;
    scanf("%d", &n);
		for (register int i = 1; i <= n; i++) scanf("%d", &a[i]);
        sort (a + 1, a + n + 1);
        d = a[2] - a[1];
        if (n == 1)	puts ("-1");
        else if (a[1] == a[n] && n >= 2)/*常数列*/ printf("1\n%d\n", a[1]);
        else if (n == 2) {
			if ((a[1] + a[2]) % 2)/*判断两数之间是否也可以插入*/  printf("2\n%d %d\n", a[1] - d, a[2] + d);
			else printf("3\n%d %d %d\n", a[1] - d, (a[1] + a[2]) / 2,  a[2] + d);
        }
        else {
			c2 = c1 = 1;
			td1 = a[3]-a[2];
			if (td1!= d) {
				for (register int i = 4; i <= n; i ++){
					int td = a[i] - a[i-1];
					if (td == td1) c2++;
					else c1++;
					if (c1 >= 2 || c2 >= 2) break;//出现次数>=2的差即为整个序列的公差
				}
			}
            if (c2 >= c1 && n >= 3 && d > td1)/*最终确定公差*/ d = td1;
            cnt = 0;
            for (register int i = 2; i <= n; i++) {
			td = a[i] - a[i-1];
			if (d!= td) {
				cnt++;
				if ((a[i-1]+a[i]) % 2 || a[i-1]+2*d!= a[i]) {
					cnt++;
					break;
                }
            	else ans = a[i-1] + d;
			}
		}
		if (!cnt) printf("2\n%d %d\n", a[1]-d, a[n]+d);//本身已经是等差数列了 
		else if (cnt == 1) printf("1\n%d\n", ans); 
		else puts ("0");//无解 
	}
    return 0;
}
```
 - **作者：kimi0705 (4星)**
    - **关键亮点**：采用函数封装检查序列是否为等差数列，代码结构清晰，分类讨论逻辑明确，对每种情况的处理步骤详细。
    - **重点代码核心实现思想**：读入数据排序后，按 $n$ 的值分类。$n = 1$ 输出 -1；$n$ 个数相等输出一种情况；$n = 2$ 根据两数差奇偶性输出结果；$n \geq 3$ 先检查是否为等差数列，是则两端可插入，不是则两次假设公差判断能否插入并输出结果。
```cpp
#include <bits/stdc++.h>
using namespace std;
bool check ( vector <int> a ) {
	int c  = a[1] - a[0];
	for ( int i = 2; i < a.size(); i++ ) if ( a[i] - a[i - 1]!= c ) return 0;
	return 1;
}
int main() {
	int n;
	cin >> n;
	vector <int> Arr ( n );
	for ( int &i : Arr ) cin >> i;
	sort ( Arr.begin(), Arr.end() );
	if ( n == 1 ) cout << -1;
	else if ( Arr[0] == Arr[n - 1] ) cout << 1 << ' ' << Arr[0];
	else if ( n == 2 ) {
		if ( ( Arr[1] - Arr[0] ) & 1 ) { // 差是奇数，不能在中间插入
			cout << 2 << '\n';
			cout << Arr[0] - ( Arr[1] - Arr[0] ) << ' ' << Arr[1] + ( Arr[1] - Arr[0] ) << '\n';
		} else {
			cout << 3 << '\n';
			cout << Arr[0] - ( Arr[1] - Arr[0] ) << ' ' << ( Arr[1] - Arr[0] ) / 2 + Arr[0] << ' ' << Arr[1] + ( Arr[1] - Arr[0] ) << '\n';
		}
	} else {
		if ( check ( Arr ) ) {
			int c = Arr[1] - Arr[0];
			cout << 2 << '\n';
			cout << Arr[0] - c << ' ' << Arr[n - 1] + c;
		} else {
			// 假设 0-1 是公差
			int c = Arr[1] - Arr[0];
			int cnt = 0, id;
			for ( int i = 1; i < Arr.size(); i++ ) if ( Arr[i] - Arr[i - 1]!= c ) cnt++, id = i - 1;
			if ( cnt == 1 ) {
				if ( Arr[id + 1] - Arr[id] == 2 * c ) {
					cout << 1 << '\n';
					cout << ( Arr[id + 1] - Arr[id] ) / 2 + Arr[id];
					return 0;
				}
			}
			// 假设 1-2 是公差
			c = Arr[2] - Arr[1];
			cnt = 0;
			for ( int i = 1; i < Arr.size(); i++ ) if ( Arr[i] - Arr[i - 1]!= c ) cnt++, id = i - 1;
			if ( cnt == 1 ) {
				if ( Arr[id + 1] - Arr[id] == 2 * c ) {
					cout << 1 << '\n';
					cout << ( Arr[id + 1] - Arr[id] ) / 2 + Arr[id];
					return 0;
				} else {
					cout << 0;
					return 0;
				}
			}
			cout << 0;
			return 0;
		}
	}
}
```
 - **作者：AKPC (4星)**
    - **关键亮点**：利用 `map` 统计差值出现次数确定众数作为公差，思路独特，对各种情况判断全面，代码逻辑清晰。
    - **重点代码核心实现思想**：读入数据排序后，$n = 1$ 输出 -1；$n = 2$ 按两数差情况输出；$n \geq 3$ 统计相邻数差值，用 `map` 找众数作为公差，根据众数出现情况及不同差值与公差关系判断能否插入并输出结果。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100001],f[100001],t[5],maxn,id=-1,sum,idx=-1,tip;
unordered_map<int,int>mp;
signed main(){
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	if (n==1) {cout<<-1;return 0;}
	sort(a+1,a+n+1);
	if (n==2){
		if (a[2]-a[1]==0) cout<<1<<'\n'<<a[1];
		else if ((a[2]-a[1])%2==0) cout<<3<<'\n'<<a[1]*2-a[2]<<' '<<(a[2]+a[1])/2<<' '<<a[2]*2-a[1];
		else cout<<2<<'\n'<<a[1]*2-a[2]<<' '<<a[2]*2-a[1];
		return 0;
	}
	for (int i=1;i<n;i++){
		f[i]=a[i+1]-a[i];
		if (!mp[f[i]]++) t[++tip]=f[i];
		if (maxn<mp[f[i]]&&mp[f[i]]>=2) maxn=mp[f[i]],id=f[i];
		if (tip>=3) {cout<<0;return 0;}
	}
	if (id==-1){
		if (f[1]==2*f[2]) cout<<1<<'\n'<<f[2]+a[1];
		else if (f[2]==2*f[1]) cout<<1<<'\n'<<f[1]+a[2];
		else cout<<0;
		return 0;
	}
	for (int i=1;i<n;i++){
		if (f[i]==id) continue;
		if (f[i]!=id*2) {cout<<0;return 0;}
		sum++,idx=i;
	}
	if (tip==1){
		if (id==0) cout<<1<<'\n'<<a[1];
		else cout<<2<<'\n'<<a[1]-f[1]<<' '<<a[n]+f[1];
	}
	else if (sum<=1) cout<<1<<'\n'<<a[idx]+id;
	else cout<<0;
	return 0;
}
```

### 最优关键思路或技巧
分类讨论结合排序后分析相邻数差值是解决本题的关键。通过对 $n$ 不同取值情况分别处理，利用排序使问题简化，再根据差值确定公差及可插入数字，这种方法清晰明了，易于实现。

### 可拓展之处
同类型题可涉及等比数列相关判断与数字插入问题，或在更多限制条件下判断数列能否构成特定数列。类似算法套路是对序列先排序，再通过分析相邻元素关系（如差值、比值等）来解决问题。

### 洛谷相似题目
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析数据间关系解决问题，与本题分析相邻数差值思路类似。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举和判断等式是否成立来解决，与本题分类讨论确定可插入数字思路有相似处。
 - [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：根据条件不断迭代计算，和本题根据不同情况分别处理有相似思维方式。 

---
处理用时：145.06秒