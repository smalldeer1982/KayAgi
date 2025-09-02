# 题目信息

# Ela Sorting Books

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737A/56ed0d2349bc5e2f6cd6bfba1e2e6140ddd296a6.png)Ela loves reading a lot, just like her new co-workers in DTL! On her first day after becoming an engineer in DTL, she is challenged by a co-worker to sort a heap of books into different compartments on the shelf. $ n $ books must be split into $ k $ compartments on the bookshelf ( $ n $ is divisible by $ k $ ). Each book is represented by a lowercase Latin letter from 'a' to 'y' inclusively, which is the beginning letter in the title of the book.

Ela must stack exactly $ \frac{n}{k} $ books in each compartment. After the books are stacked, for each compartment indexed from $ 1 $ to $ k $ , she takes the minimum excluded (MEX) letter of the multiset of letters formed by letters representing all books in that compartment, then combines the resulting letters into a string. The first letter of the resulting string is the MEX letter of the multiset of letters formed by the first compartment, the second letter of the resulting string is the MEX letter of the multiset of letters formed by the second compartment, ... and so on. Please note, under the constraint of this problem, MEX letter can always be determined for any multiset found in this problem because 'z' is not used.

What is the lexicographically greatest resulting string possible that Ela can create?

A string $ a $ is lexicographically greater than a string $ b $ if and only if one of the following holds:

- $ b $ is a prefix of $ a $ , but $ b \ne a $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears later in the alphabet than the corresponding letter in $ b $ .

The minimum excluded (MEX) letter of a multiset of letters is the letter that appears earliest in the alphabet and is not contained in the multiset. For example, if a multiset of letters contains $ 7 $ letters 'b', 'a', 'b', 'c', 'e', 'c', 'f' respectively, then the MEX letter of this compartment is 'd', because 'd' is not included in the multiset, and all letters comes before 'd' in the alphabet, namely 'a', 'b' and 'c', are included in the multiset.

## 说明/提示

In the first test case, the books can be divided into $ 3 $ compartments as below:

- the first compartment contains the books with indices $ 1, 2, 3, 7 $ : $ multiset_1 = \{ $ 'c', 'a', 'b', 'd' $ \} $ $ \rightarrow $ $ MEX(multiset_1) = $ 'e'
- the second compartment contains the books with indices $ 4, 5, 6, 9 $ : $ multiset_2 = \{ $ 'c', 'c', 'a', 'b' $ \} $ $ \rightarrow $ $ MEX(multiset_2) = $ 'd'
- the third compartment contains the remaining books $ 8, 10, 11, 12 $ : $ multiset_3 = \{ $ 'a', 'a', 'a', 'c' $ \} $ $ \rightarrow $ $ MEX(multiset_3) = $ 'b'

Therefore, the answer is 'edb'. It can be proven that there is no way that Ela can arrange the books so that it results in a lexicographically greater string.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737A/407eef03cdf4780f728db3b04f21cd023d792a00.png)

## 样例 #1

### 输入

```
5
12 3
cabccadabaac
12 6
cabccadabaac
12 12
cabccadabaac
25 1
abcdefghijklmnopqrstuvwxy
10 5
bcdxedbcfg```

### 输出

```
edb
ccbbba
bbbbbaaaaaaa
z
aaaaa```

# AI分析结果

### 题目内容
# Ela整理书籍

## 题目描述
Ela和她在DTL的新同事们一样，非常热爱阅读。在她成为DTL工程师的第一天，一位同事向她发起挑战，要求将一堆书分类摆放到书架的不同隔间里。需要将$n$本书分成书架上的$k$个隔间（$n$能被$k$整除）。每本书都用一个小写拉丁字母表示，范围从'a'到'y'，这个字母是书名的首字母。

Ela必须在每个隔间中恰好堆叠$\frac{n}{k}$本书。在书堆叠好后，对于从$1$到$k$编号的每个隔间，她要找出由该隔间中所有书所代表字母组成的多重集中的最小未出现字母（MEX），然后将得到的字母组合成一个字符串。结果字符串的第一个字母是第一个隔间所代表字母的多重集的MEX字母，第二个字母是第二个隔间所代表字母的多重集的MEX字母，依此类推。请注意，在本题的约束条件下，对于本题中出现的任何多重集，都总能确定MEX字母，因为不使用'z'。

Ela能创建的字典序最大的结果字符串是什么？

字符串$a$的字典序大于字符串$b$，当且仅当以下情况之一成立：
- $b$是$a$的前缀，但$b \neq a$；
- 在$a$和$b$第一个不同的位置上，字符串$a$的字母在字母表中出现的顺序比$b$中相应字母更靠后。

多重集的最小未出现字母（MEX）是指在字母表中出现最早且不在该多重集中的字母。例如，如果一个字母多重集分别包含7个字母'b'、'a'、'b'、'c'、'e'、'c'、'f'，那么这个隔间的MEX字母是'd'，因为'd'不在该多重集中，且在字母表中排在'd'之前的所有字母，即'a'、'b'和'c'，都包含在该多重集中。

## 说明/提示
在第一个测试用例中，书可以按如下方式分成3个隔间：
- 第一个隔间包含索引为1、2、3、7的书：$multiset_1 = \{ $ 'c', 'a', 'b', 'd' $ \} $  $\rightarrow$  $MEX(multiset_1) = $ 'e'
- 第二个隔间包含索引为4、5、6、9的书：$multiset_2 = \{ $ 'c', 'c', 'a', 'b' $ \} $  $\rightarrow$  $MEX(multiset_2) = $ 'd'
- 第三个隔间包含其余的书8、10、11、12：$multiset_3 = \{ $ 'a', 'a', 'a', 'c' $ \} $  $\rightarrow$  $MEX(multiset_3) = $ 'b'

因此，答案是'edb'。可以证明，Ela没有其他方法排列这些书以得到字典序更大的字符串。

## 样例 #1
### 输入
```
5
12 3
cabccadabaac
12 6
cabccadabaac
12 12
cabccadabaac
25 1
abcdefghijklmnopqrstuvwxy
10 5
bcdxedbcfg
```
### 输出
```
edb
ccbbba
bbbbbaaaaaaa
z
aaaaa
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为统一，都基于贪心策略。要点在于为使每段中未出现的最小字母构成的序列字典序最大，需尽量让每段为从 'a' 开始的连续子串。通过记录每个字母的出现次数，遍历字母统计数组，每次从 'a' 开始找第一个出现次数为 0 的字母输出，若前 $\frac{n}{k}$ 个字母都出现了，则输出第 $\frac{n}{k} + 1$ 个字母。解决的难点在于理解如何通过合理分配字母，使得每段的 MEX 字母组合起来字典序最大，大家都意识到让字典序靠前的字母尽量连续出现是关键。

### 所选的题解
- **作者：with_no_signal (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，很好地体现了贪心的策略，利用双循环遍历实现核心逻辑，且代码结构紧凑。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
int cnt[31];
string str;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--)
	{
		memset(cnt,0,sizeof(cnt));
		cin>>n>>k>>str;
		for(int i=0; i<str.size(); i++)
		{
			cnt[str[i]-'a'+1]++;
		}
		for(int i=1; i<=k; i++)
		{
			bool flag=true;
			for(int j=1; j<=n/k; j++)
			{
				if(cnt[j]==0)
				{
					flag=false;
					cout<<(char)(j+'a'-1);
					break;
				}
				cnt[j]--;
			}
			if(flag)cout<<(char)(n/k+'a');
		}
		cout<<endl;
	}
	return 0;
}
```
    - **核心实现思想**：外层循环遍历 $k$ 个隔间，内层循环遍历每个隔间应有的 $\frac{n}{k}$ 个字母，在内层循环中找出现次数为 0 的字母输出，若未找到则输出第 $\frac{n}{k} + 1$ 个字母。

- **作者：linbaicheng2022 (4星)**
    - **关键亮点**：对思路的阐述较为详细，代码注释丰富，便于理解。先明确了每段 MEX 字母的范围，再按贪心思路实现。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210;
int n, k, sum[N];
string str;

int main () {
	int T;
	cin >> T;
	while (T --) {
		memset (sum, 0, sizeof sum); //数组记得清零
		cin >> n >> k >> str;

		for (int i = 0; i < n; i ++) //统计每个字符出现的次数
			sum[str[i] - 'a' + 1] ++;

		for (int i = 1; i <= k; i ++) {
			int ok = 0;
			for (int j = 1; j <= n / k; j ++) { //遍历 L 个字符
				if (sum[j] == 0) { //如果这个字符没有出现过，就输出
					ok = 1;
					cout << char (j + 'a' - 1);
					break;
				}
				
				sum[j] --; //遍历过这个字符了，将这个字符出现次数减一
			}

			if (ok == 0) //如果前面没有找到，就输出第 L + 1 个字符
				cout << char (n / k + 'a'); 
		}

		cout << endl;
	}
	return 0;
}
```
    - **核心实现思想**：与上一题解类似，通过双重循环，外层控制隔间数量，内层遍历每个隔间的字母，找出现次数为 0 的字母输出，若内层循环结束未找到则输出特定字母。

- **作者：zzy0618 (4星)**
    - **关键亮点**：在思路分析中明确提到贪心思想的应用，代码实现中使用桶记录字母出现次数，逻辑清晰，变量命名规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, k, len, i, j, x, N;
int mp[30];//桶 
string s;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);//读入加速 
	cin >> t;
	while (t--) {
		memset(mp, 0, sizeof(mp));//清空桶 
		cin >> n >> k >> s;
		len = s.size();
		N =n / k;//用 N 记录 n/k 较快 
		for (i = 0; i < len; i++)mp[s[i] - 'a' + 1]++;//记录 
		for (i = 1; i <= k; i++) {
			x = 1;
			for (j = 1; j <= N; j++) {//不断向上爬 
				if (mp[j] == 0) {//如果中途没有字符了 
					x = 0;
					putchar(j + 'a' - 1);
					break;
				}
				mp[j]--;
			}
			if (x)putchar(N + 'a');//输出 k+1 个字符 
		}
		putchar('\n');
	}
	return 0;
}
```
    - **核心实现思想**：利用桶数组 `mp` 记录字母出现次数，通过两层循环，外层循环处理 $k$ 个隔间，内层循环遍历每个隔间的字母，根据字母出现次数是否为 0 决定输出的字母。

### 最优关键思路或技巧
采用贪心策略，优先考虑字典序小的字母，让每段尽量从 'a' 开始连续，通过桶数组记录每个字母的出现次数，然后按顺序遍历查找出现次数为 0 的字母，这是解决本题的关键思路和技巧。

### 同类型题或类似算法套路拓展
此类题目通常围绕字符串的分割与特定规则下的最优解求解。类似套路是先明确目标（如本题字典序最大），然后分析如何通过合理分配元素（如字母）达到目标，利用数据结构（如桶数组）辅助统计，再通过循环遍历实现逻辑。

### 推荐洛谷题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：同样是贪心策略的应用，通过对数据的合理排序和贪心选择来解决问题。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：利用贪心思想，根据接水时间对队伍进行排序以得到最优解。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过比较不同购买方案的价格，采用贪心策略选择最省钱的购买方式。 

---
处理用时：82.32秒