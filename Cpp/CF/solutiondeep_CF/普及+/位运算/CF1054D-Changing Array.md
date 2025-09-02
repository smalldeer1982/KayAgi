# 题目信息

# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0
```

### 输出

```
5```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4
```

### 输出

```
19```

# AI分析结果

### 题目内容
# 改变数组

## 题目描述
课间休息时，万尼亚来到教室，看到黑板上有一个由\(n\)个\(k\)位整数\(a_1, a_2, \ldots, a_n\)组成的数组。如果\(0 \leq x \leq 2^k - 1\)，则整数\(x\)被称为\(k\)位整数。

当然，万尼亚忍不住开始修改黑板上写的数字。为确保没人注意到，万尼亚只允许自己进行一种类型的修改：选择数组的一个索引\(i\)（\(1 \leq i \leq n\)），并将数字\(a_i\)替换为数字\(\overline{a_i}\)。对于一个\(k\)位整数\(x\)，我们将\(\overline{x}\)定义为这样一个\(k\)位整数，它的所有\(k\)位都与\(x\)的对应位不同。

万尼亚不喜欢数字\(0\)。因此，他喜欢这样的区间\([l, r]\)（\(1 \leq l \leq r \leq n\)），使得\(a_l \oplus a_{l + 1} \oplus \ldots \oplus a_r \neq 0\)，其中\(\oplus\)表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。确定通过上述零次或多次操作，万尼亚最多能得到多少个他喜欢的区间。

## 说明/提示
在第一个示例中，如果瓦夏不进行任何操作，他得到的数组有\(5\)个万尼亚喜欢的区间。如果他对\(i = 2\)进行操作，他得到数组\([1, 0, 0]\)，因为当\(k = 2\)时，\(\overline{3} = 0\)。这个数组有\(3\)个万尼亚喜欢的区间。同样，为了得到有\(5\)个万尼亚喜欢的区间的数组，他可以对\(i = 3\)和\(i = 2\)进行两次操作。然后他得到数组\([1, 0, 3]\)。可以证明他无法得到\(6\)个或更多他喜欢的区间。

在第二个示例中，为了得到\(19\)个万尼亚喜欢的区间，他可以对\(i = 3\)、\(i = 4\)、\(i = 5\)、\(i = 6\)进行\(4\)次操作，得到数组\([1, 4, 3, 0, 4, 3]\)。

## 样例 #1
### 输入
```
3 2
1 3 0
```
### 输出
```
5```

## 样例 #2
### 输入
```
6 3
1 4 4 7 3 4
```
### 输出
```
19```

### 综合分析与结论
这些题解的共同思路是正难则反，通过计算总区间数减去异或和为\(0\)的区间数来得到答案。算法要点在于利用异或前缀和将区间异或和转化为前缀和的异或，并且都意识到对数组元素的操作相当于对前缀和进行特定的异或操作。解决难点在于如何通过合理操作使异或和为\(0\)的区间数最少。

不同题解在具体实现上稍有差异，有的直接在计算前缀和过程中贪心选择使相同前缀和数量最少的路径；有的通过统计不同前缀和的出现次数，利用组合数公式计算相同前缀和产生的异或和为\(0\)的区间数。

### 所选的题解
#### 作者：灵茶山艾府 (5星)
- **关键亮点**：思路清晰，先通过前缀异或和将子数组异或和转化为前缀和中两个元素的异或值，进而将问题转化为让前缀和数组中的不同数对尽量多。提出正难则反思路，通过统计\(\min(s[i], s[i]\oplus (2^k - 1))\)的出现次数，利用组合数公式计算答案，代码实现简洁高效。
- **核心代码**：
```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, k, v, s int
	Fscan(in, &n, &k)
	ans := c2(n + 1)
	m := 1<<k - 1
	cnt := map[int]int{s: 1} // s[0]
	for ; n > 0; n-- {
		Fscan(in, &v)
		s ^= v
		cnt[min(s, s^m)]++
	}
	for _, c := range cnt {
		ans -= c2(c/2) + c2(c-c/2)
	}
	Print(ans)
}

func c2(n int) int64 { return int64(n) * int64(n-1) / 2 }
func min(a, b int) int { if a > b { return b }; return a }
```
核心实现思想：在读取数组元素过程中，实时计算前缀异或和\(s\)，并将\(\min(s, s\oplus m)\)的出现次数记录在`cnt`中，最后通过组合数公式计算并更新答案。

#### 作者：花里心爱 (4星)
- **关键亮点**：同样采用正难则反思路，代码实现简单易懂。在计算前缀和过程中，每次比较当前前缀和取反前后出现次数的大小，贪心选择出现次数少的作为当前前缀和，从而减少异或和为\(0\)的区间数。
- **核心代码**：
```cpp
#include <cstdio>
#include <cctype>
#include <map>
#define ll long long
inline int read() {
    int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
    while(isdigit(ch)){d=d*10+ch-48;ch=getchar();}return d;
}

int n, k, a, mx;
int pre, nowa, nowb;
ll ans;
std::map<int, int> mp;

int main() {
    n = read(), k = read();
    mx = (1<<k)-1; // 为了方便进行取反操作这里记录一下后k为均为1的值
    mp[0] = 1;
    for(int i = 1; i <= n; ++i) {
        a = read();
        nowa = pre^a;
        nowb = nowa^mx;
        if(mp[nowa] < mp[nowb]) {
            ans += (mp[nowa]++); // 取最小的前缀和
            pre = nowa;
        }
        else {
            ans += (mp[nowb]++);
            pre = nowb;
        }
    }
    printf("%lld", ((ll)n*(n+1))/2 - ans); // 用总数减去最小的区间异或和为0的区间数
    return 0;
}
```
核心实现思想：在遍历数组时，计算当前元素加入后的前缀和`nowa`及其取反后的`nowb`，比较二者在`map`中出现次数，选择次数少的更新前缀和`pre`并累加其出现次数到`ans`，最后用总区间数减去`ans`得到答案。

#### 作者：crashed (4星)
- **关键亮点**：分析过程详细，从理论上推导证明了贪心选择的正确性，即通过均值不等式说明应选择出现次数较少的前缀和，使得相同前缀和产生的异或和为\(0\)的区间数最少。
- **核心代码**：
```cpp
#include <map>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXN = 2e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

map<int, int> mp;

int N, K;

int main()
{
	mp[0] = 1;
	read( N ), read( K );
	LL res = 0;
	int upper = ( 1 << K ) - 1, pXor = 0, fir, sec; 
	for( int i = 1, a ; i <= N ; i ++ )
	{
		read( a );
		fir = pXor ^ a, sec = pXor ^ a ^ upper;
		if( mp[fir] < mp[sec] ) res += mp[pXor = fir] ++;
		else res += mp[pXor = sec] ++;
	}
	write( 1ll * N * ( N + 1 ) / 2 - res ), putchar( '\n' );
	return 0;
}
```
核心实现思想：与花里心爱题解类似，在遍历数组时，计算当前前缀和`fir`及其取反后的`sec`，根据`map`中二者出现次数的比较结果，选择较小次数的更新前缀和`pXor`并累加其出现次数到`res`，最后用总区间数减去`res`得到答案。

### 最优关键思路或技巧
1. **正难则反思维**：直接求异或和不为\(0\)的区间较难，转化为求异或和为\(0\)的区间数，用总区间数相减得到答案。
2. **异或前缀和应用**：将区间异或和问题转化为前缀和的异或，简化问题求解。
3. **贪心策略**：通过合理选择前缀和（如选择出现次数少的前缀和），使得异或和为\(0\)的区间数最少，从而间接最大化异或和不为\(0\)的区间数。

### 可拓展之处
同类型题或类似算法套路：此类题目通常围绕位运算（特别是异或）和区间问题展开。常见套路包括利用前缀和（这里是异或前缀和）处理区间信息，以及在面对复杂限制条件时采用正难则反的思路。类似题目可能会改变操作类型、数据范围或者限制条件，但核心思路可能类似。

### 推荐题目
1. **P1514 引水入城**：涉及区间覆盖和贪心策略，与本题在利用策略优化结果上有相似之处。
2. **P1080 [NOIP2012 提高组] 国王游戏**：同样是贪心策略的应用，通过分析数据特点找到最优贪心方案，和本题思路有相通之处。
3. **P2058 [NOIP2016 提高组] 海港**：运用前缀和思想处理区间内的元素统计问题，与本题利用异或前缀和处理区间异或和问题类似。

### 个人心得摘录与总结
部分作者提到“正难则反”思路在本题中的重要性，即当直接求解问题困难时，考虑从反面入手。还有作者提到在实现过程中对边界情况的注意，如初始前缀和为\(0\)的情况需要特殊处理，这提醒在解决此类问题时要全面考虑各种边界条件，避免遗漏。 

---
处理用时：66.03秒