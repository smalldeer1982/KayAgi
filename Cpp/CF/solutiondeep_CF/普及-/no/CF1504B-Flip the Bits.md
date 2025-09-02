# 题目信息

# Flip the Bits

## 题目描述

There is a binary string $ a $ of length $ n $ . In one operation, you can select any prefix of $ a $ with an equal number of $ 0 $ and $ 1 $ symbols. Then all symbols in the prefix are inverted: each $ 0 $ becomes $ 1 $ and each $ 1 $ becomes $ 0 $ .

For example, suppose $ a=0111010000 $ .

- In the first operation, we can select the prefix of length $ 8 $ since it has four $ 0 $ 's and four $ 1 $ 's: $ [01110100]00\to [10001011]00 $ .
- In the second operation, we can select the prefix of length $ 2 $ since it has one $ 0 $ and one $ 1 $ : $ [10]00101100\to [01]00101100 $ .
- It is illegal to select the prefix of length $ 4 $ for the third operation, because it has three $ 0 $ 's and one $ 1 $ .

Can you transform the string $ a $ into the string $ b $ using some finite number of operations (possibly, none)?

## 说明/提示

The first test case is shown in the statement.

In the second test case, we transform $ a $ into $ b $ by using zero operations.

In the third test case, there is no legal operation, so it is impossible to transform $ a $ into $ b $ .

In the fourth test case, here is one such transformation:

- Select the length $ 2 $ prefix to get $ 100101010101 $ .
- Select the length $ 12 $ prefix to get $ 011010101010 $ .
- Select the length $ 8 $ prefix to get $ 100101011010 $ .
- Select the length $ 4 $ prefix to get $ 011001011010 $ .
- Select the length $ 6 $ prefix to get $ 100110011010 $ .

In the fifth test case, the only legal operation is to transform $ a $ into $ 111000 $ . From there, the only legal operation is to return to the string we started with, so we cannot transform $ a $ into $ b $ .

## 样例 #1

### 输入

```
5
10
0111010000
0100101100
4
0000
0000
3
001
000
12
010101010101
100110011010
6
000111
110100```

### 输出

```
YES
YES
NO
YES
NO```

# AI分析结果

### 题目内容
# 翻转位

## 题目描述
有一个长度为 $n$ 的二进制字符串 $a$ 。在一次操作中，你可以选择 $a$ 的任意一个前缀，该前缀中 $0$ 和 $1$ 的符号数量相等。然后将前缀中的所有符号取反：每个 $0$ 变为 $1$ ，每个 $1$ 变为 $0$ 。

例如，假设 $a = 0111010000$ 。
- 在第一次操作中，我们可以选择长度为 $8$ 的前缀，因为它有四个 $0$ 和四个 $1$ ：$[01110100]00 \to [10001011]00$ 。
- 在第二次操作中，我们可以选择长度为 $2$ 的前缀，因为它有一个 $0$ 和一个 $1$ ：$[10]00101100 \to [01]00101100$ 。
- 第三次操作选择长度为 $4$ 的前缀是不合法的，因为它有三个 $0$ 和一个 $1$ 。

你能否通过有限次操作（可能不需要操作）将字符串 $a$ 转换为字符串 $b$ ？

## 说明/提示
第一个测试用例在题目描述中已展示。

在第二个测试用例中，我们无需操作即可将 $a$ 转换为 $b$ 。

在第三个测试用例中，不存在合法操作，所以无法将 $a$ 转换为 $b$ 。

在第四个测试用例中，有一种这样的转换方式：
- 选择长度为 $2$ 的前缀得到 $100101010101$ 。
- 选择长度为 $12$ 的前缀得到 $011010101010$ 。
- 选择长度为 $8$ 的前缀得到 $100101011010$ 。
- 选择长度为 $4$ 的前缀得到 $011001011010$ 。
- 选择长度为 $6$ 的前缀得到 $100110011010$ 。

在第五个测试用例中，唯一合法的操作是将 $a$ 转换为 $111000$ 。从那里开始，唯一合法的操作是回到我们开始的字符串，所以我们无法将 $a$ 转换为 $b$ 。

## 样例 #1
### 输入
```
5
10
0111010000
0100101100
4
0000
0000
3
001
000
12
010101010101
100110011010
6
000111
110100
```
### 输出
```
YES
YES
NO
YES
NO
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路大多是从后往前遍历字符串，利用翻转操作的性质来判断能否从字符串 $a$ 转换为字符串 $b$ 。由于翻转操作的特殊性，即同一前缀翻转偶数次无意义，奇数次等价于一次，所以从后往前遍历可以避免前面操作对后面判断的影响。同时，通过预处理可翻转的前缀位置，结合当前字符与目标字符的比较，以及已有的翻转状态，来确定是否能完成转换。

不同题解在细节实现上有所差异，比如有的通过记录前缀和来判断前缀是否可翻转，有的通过记录操作奇偶性来模拟翻转效果等。但整体思路围绕从后往前贪心判断这一核心。

### 所选的题解
- **作者：_Anchor (5星)**
    - **关键亮点**：思路清晰，先分析出操作次数的奇偶性性质，再从后往前贪心遍历，通过记录当前点之后位置被选择次数的奇偶性，结合当前点与目标点的异同，判断当前点是否必选，最后通过判断必选位置是否为可选位置的子集来确定结果，时间复杂度 $O(n)$ 。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
#define ll long long
const int N=3e5+5,M=1e6+5,INF=1e9+7;
int n,m,q,T,t,Ans;
int a[N],b[N];
char str1[N],str2[N];
int main(){
	read(T);
	while(T--){
		read(n);int sum=0,now=0;bool flag=0;
		scanf("%s",str1+1),scanf("%s",str2+1);
		for(int i=1;i<=n;i++){
			a[i]=b[i]=0;
			sum+=(str1[i]=='1'?1:-1);
			if(sum==0) a[i]=true;
			if(str1[i]!=str2[i]) b[i]=true;
		}
		for(int i=n;i>=1;i--){
			if(b[i]^now){
				if(a[i]) now^=1;
				else flag=true;
			}
		}
		if(flag) puts("NO");
		else puts("YES");
	}
    return 0;
}
```
    - **核心思想**：先预处理出每个位置是否可选（$a$数组）以及当前位置与目标位置是否不同（$b$数组），从后往前遍历，根据当前位置与目标位置的异同以及之后位置被选次数的奇偶性（$now$）来判断当前位置是否必选，若必选位置不在可选位置内则标记不可行。
- **作者：听取MLE声一片 (4星)**
    - **关键亮点**：指出变换不改变 $01$ 的数量，通过预处理出每一个可以变换的点，从后往前处理，利用一个数累加记录变换次数，避免每次变换全部更改，综合复杂度为 $O(N)$ 。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a[300001],b[300001],c[300001];
int n,t;
int main()
{
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			char x;
			cin>>x;
			a[i]=x-'0';
		}
		for(int i=1;i<=n;i++){
			char x;
			cin>>x;
			b[i]=x-'0';
		}
		int s1=0,s2=0;
		for(int i=1;i<=n;i++){
			c[i]=0;
			if(a[i]==0)
				s1++;
			if(a[i]==1)
				s2++;
			if(s1==s2)
				c[i]=1;
		}
		int pd=1,sum=0;
		for(int i=n;i>=1;i--){
			if(!pd)
				break;
			a[i]=(a[i]+sum)%2;
			if(c[i]==0){
				if(a[i]!=b[i]){
					pd=0;
					cout<<"NO\n";
				}
				continue;
			}
			else{
				if(a[i]!=b[i])
					sum++;
			}
		}
		if(pd)
			cout<<"YES\n";
	}
	return 0;
}
```
    - **核心思想**：先统计每个位置前 $0$ 和 $1$ 的数量，标记出可变换的位置（$c$数组），从后往前遍历，根据之前的变换次数（$sum$）更新当前字符，若当前位置不可变换且与目标字符不同则输出 `NO` ，否则根据情况更新变换次数。
- **作者：nalemy (4星)**
    - **关键亮点**：通过求前缀和判断前缀是否可翻转，定义 $flg_i$ 表示当前前缀是否被翻转（结果意义上），从后往前枚举，根据当前字符与目标字符的关系以及 $flg_i$ 的状态来决定是否翻转，同时检查翻转条件，逻辑清晰。
    - **核心代码**：
```C++
#include<iostream>
#define N 300000
using namespace std;

int pa[N]; // 前缀和
int main() {
    string a, b; bool flg;
    int t, n; cin >> t;
    while (t--) {
        cin >> n >> a >> b, pa[0] = a[0] == '1', flg = false;
        for (int i=1; i<n; i++) // 求前缀和
            pa[i] = pa[i-1] + a[i] - '0';
        for (int i=n-1; i>=0; i--) { // 倒序遍历
            // 不用再翻转了
            if (a[i] - '0' ^ b[i] - '0' == flg) continue; // 直接走
            // 需要翻转，但是不满足条件
            if (pa[i] * 2!= i + 1) goto DIE; // 直接死
            // 没死，那么大胆翻转
            flg =!flg;
        }
        cout << "YES\n"; continue; // 没死，说明可行，输出完直接走
        DIE: cout << "NO\n"; // 竟然死了，不可行
    }
    return 0;
}
```
    - **核心思想**：先求出前缀和（$pa$数组），从后往前遍历，若当前字符与目标字符的异或结果与 $flg$ 相同则无需操作，否则检查当前前缀是否可翻转，若可翻转则更新 $flg$ 。

### 最优关键思路或技巧
从后往前贪心遍历的方式，结合翻转操作的奇偶性性质以及对可翻转前缀的预处理判断，能高效解决此类问题。这种思路避免了从前往后遍历可能出现的复杂情况，简化了判断逻辑。

### 拓展思路
同类型题目通常围绕特定规则的字符串变换展开，类似算法套路是抓住操作的本质特点（如本题中翻转操作的奇偶性等价、只能操作前缀等），从便于分析的方向（如本题从后往前）进行遍历判断。

### 推荐题目
- [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)：涉及对字符串的合法匹配判断，与本题对字符串按特定规则操作判断有相似之处。
- [P2044 自然数的拆分问题](https://www.luogu.com.cn/problem/P2044)：同样是对序列进行特定规则的变换与判断，可锻炼对规则的理解和应用能力。
- [P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略解决问题，与本题从后往前贪心判断的思路类似。

### 个人心得摘录
作者LiveZoom提到赛时和赛后调试很久才通过本题，最初使用树状数组写法时间复杂度为 $O(n\log n)$ ，后来发现可以 $O(n)$ 实现且代码更简洁。这表明在解题时不仅要关注能否实现，还需思考优化方式，同时调试过程也是对题目和算法理解不断加深的过程。 

---
处理用时：145.62秒