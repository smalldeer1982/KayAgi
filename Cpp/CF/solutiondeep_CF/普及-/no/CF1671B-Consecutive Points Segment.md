# 题目信息

# Consecutive Points Segment

## 题目描述

You are given $ n $ points with integer coordinates on a coordinate axis $ OX $ . The coordinate of the $ i $ -th point is $ x_i $ . All points' coordinates are distinct and given in strictly increasing order.

For each point $ i $ , you can do the following operation no more than once: take this point and move it by $ 1 $ to the left or to the right (i..e., you can change its coordinate $ x_i $ to $ x_i - 1 $ or to $ x_i + 1 $ ). In other words, for each point, you choose (separately) its new coordinate. For the $ i $ -th point, it can be either $ x_i - 1 $ , $ x_i $ or $ x_i + 1 $ .

Your task is to determine if you can move some points as described above in such a way that the new set of points forms a consecutive segment of integers, i. e. for some integer $ l $ the coordinates of points should be equal to $ l, l + 1, \ldots, l + n - 1 $ .

Note that the resulting points should have distinct coordinates.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2
1 4
3
1 2 3
4
1 2 3 7
1
1000000
3
2 5 6```

### 输出

```
YES
YES
NO
YES
YES```

# AI分析结果

### 题目内容
# 连续点段

## 题目描述
给定 $n$ 个在坐标轴 $OX$ 上具有整数坐标的点。第 $i$ 个点的坐标为 $x_i$ 。所有点的坐标都互不相同，并且按严格递增顺序给出。

对于每个点 $i$ ，你最多可以进行一次以下操作：将这个点向左或向右移动 $1$（即，你可以将其坐标 $x_i$ 更改为 $x_i - 1$ 或 $x_i + 1$ ）。换句话说，对于每个点，你（分别地）选择它的新坐标。对于第 $i$ 个点，它可以是 $x_i - 1$ 、$x_i$ 或 $x_i + 1$ 。

你的任务是确定是否可以按照上述方式移动某些点，使得新的点集形成一个连续的整数段，即对于某个整数 $l$ ，点的坐标应该等于 $l, l + 1, \ldots, l + n - 1$ 。

注意，得到的点应该具有不同的坐标。

你必须回答 $t$ 个独立的测试用例。

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕判断给定的严格递增整数序列能否通过对每个数最多进行一次加1或减1操作，使其变为连续整数段展开。多数题解通过分析序列首末项差值与 $n$ 的关系得出结论，少数通过贪心策略逐步判断相邻元素差值能否调整为1。
1. **思路方面**：多数题解认为当且仅当 $a_n - a_1 \leq n + 1$ 时答案为能，否则为不能。部分题解从反面思考，考虑连续整数段经操作后能形成的序列特征；部分通过分析相邻元素差值情况，如差值为1、2、3、大于3时分别讨论能否调整为连续序列。
2. **算法要点**：核心在于找到一个简洁的判断条件。如通过分析连续整数段首末项差值为 $n - 1$ ，结合每个数可操作范围推出原序列首末项差值需满足 $a_n - a_1 \leq n + 1$ ；或贪心处理相邻元素差值，根据不同差值情况判断可行性。
3. **解决难点**：难点在于如何简洁准确地判断能否构成连续整数段。从首末项差值角度，需理解操作对首末项差值的影响范围；从贪心角度，要合理处理相邻元素不同差值情况，保证后续元素有足够操作空间。

### 所选的题解
- **作者：8atemak1r (赞：5)  星级：5星  关键亮点：直接给出简洁结论，从反向思考证明结论，代码简洁明了**
```cpp
#include<iostream>
using namespace std;
const int maxn = 200005;
int t, n, a[maxn];
int main() {
    ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> t;
    while(t --) {
        cin >> n;
        for(int i = 1; i <= n; ++ i) cin >> a[i];
        if(a[n] - a[1] <= n + 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```
核心实现思想：输入数据后，直接判断序列首项与末项的差值是否小于等于 $n + 1$ ，输出相应结果。

- **作者：Tx_Lcy (赞：1)  星级：4星  关键亮点：采用贪心策略，从前往后分析相邻元素差值，维护标记判断可行性**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[211100];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;cin>>t;
	while (t--){
		int n;cin>>n;
		int tag=0;//这是标记是否有解的
		for (int i=1;i<=n;i++) cin>>a[i];
		int f=1;//这是标记 1 到 i-1 是否不用修改的
		for (int i=2;i<=n;i++){
		    if (abs(a[i]-a[i-1])==2){
		    	if (!f) a[i]--;
		    	else f=0;
			}else if (abs(a[i]-a[i-1])==3){
				if (!f){tag=1;break;}
				else f=0,a[i]--;
			}else if (abs(a[i]-a[i-1])>3){tag=1;break;}
		}
	    if (tag) cout<<"NO\n";
	    else cout<<"YES\n";
	}
	return 0;
}
```
核心实现思想：通过循环遍历相邻元素，根据差值为2、3、大于3的不同情况，结合标记 $f$ 判断是否有解，$f$ 表示前面元素是否有过修改，若有则按特定规则处理当前元素，若处理过程中发现无解则标记 $tag$ 。

- **作者：幸存者 (赞：1)  星级：4星  关键亮点：从首末项差值出发，详细分析不同差值范围下如何通过操作得到连续整数段**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, minx = 1e6, maxx = 0;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            if (i == 1) minx = x;
            else if (i == n) maxx = x;
        }
        if (maxx - minx <= n + 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```
核心实现思想：输入数据时记录首项和末项，判断首末项差值是否小于等于 $n + 1$ ，若满足则输出“YES”，否则输出“NO”，并对满足条件时如何通过操作使序列连续进行了详细分析。

### 最优关键思路或技巧
从首末项差值角度分析，利用连续整数段首末项差值为 $n - 1$ 以及每个数可操作范围，得出原序列首末项差值需满足 $a_n - a_1 \leq n + 1$ 的简洁判断条件，这是一种高效的思维方式。

### 可拓展之处
同类型题可考察对其他序列通过有限操作进行变换的可行性判断，类似算法套路是从序列整体特征（如首末项、极差等）出发，结合操作规则推导判断条件。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过分析数据特征找到最优排序方式。
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：利用贪心思想解决数字序列的删除问题，与本题通过分析序列特征解决问题思路类似。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：同样是贪心算法应用，根据不同数据条件确定最优策略。 

---
处理用时：65.81秒