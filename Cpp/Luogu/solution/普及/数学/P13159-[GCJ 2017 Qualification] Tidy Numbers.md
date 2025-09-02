# [GCJ 2017 Qualification] Tidy Numbers

## 题目描述

Tatiana 喜欢保持整洁。她的玩具按照从小到大的顺序排列，她的铅笔按照从短到长的顺序排列，她的电脑按照从旧到新的顺序排列。一天，在练习数数的时候，她注意到有些整数在十进制下书写且没有前导零时，其各位数字是非递减排列的。例如 8、123、555 和 224488 就是这样的数。她决定把这些数称为“tidy”数。不满足这个性质的数，比如 20、321、495 和 999990，就不是 tidy 数。

她刚刚从 1 开始按升序数到了 $N$。她数到的最后一个 tidy 数是多少？

## 说明/提示

**样例解释**

注意，最后一个样例不会出现在 Small 数据集里。

**限制条件**

- $1 \leq T \leq 100$。

**Small 数据集（5 分，测试集 1 - 可见）**

- $1 \leq N \leq 1000$。

**Large 数据集（10 分，测试集 2 - 隐藏）**

- $1 \leq N \leq 10^{18}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
132
1000
7
111111111111111110```

### 输出

```
Case #1: 129
Case #2: 999
Case #3: 7
Case #4: 99999999999999999```

# 题解

## 作者：chinazhanghaoxun (赞：4)

# P13159 Tidy Numbers - Solution

## Problem Statement

给定一个数 $N$，你要将它改为小于等于原数，且各位数字不递减的最大数。

## Analysis

首先分情况讨论，若原数满足条件，则不必修改。否则，分析满足性质的数字。

设初次不符合规则的位置为 $x$，即 $N_x>N_{x+1}$，先将 $N_x\gets N_x-1$，也就是**相当于退一位**，这样才能满足小于原数。

再考虑后面的位数，由于已经满足 $N_x-1<N_x$，因此后面的数字不会决定两数的大小关系，**全部设为 $9$ 一定是最优的**。

这样，就粗略地证明了贪心的正确性，可以实现。

## Approach

使用字符串存储 $N$，字符串为 $S$。遍历找到 $x$，$S_x\gets S_x-1$，再将后面的 $S_i\gets9$，其中 $i\in(x,n]$。由于每次更新后**可能仍然不合条件**，所以要**循环此操作**，直到全串符合为止。

最后还要注意**去掉前导零**，使用 `while(s[i]=='0') i++` 就可以实现。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;

void solve(){
	for(int i=1;i<s.size();i++){
        if(s[i-1]>s[i]){ //找x 
            s[i-1]--;
            for(int j=i;j<s.size();j++)
            	s[j]='9';
            solve();
        }
	}
}

void print(){
    int i=0;
    while(s[i]=='0') //去除前导零 
        i++;
    for(i;i<s.size();i++)
        cout<<s[i];
    cout<<endl;
}

int main(){
    int T;
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>s;
		solve(); 
        printf("Case #%d: ",t);
        print(); //输出答案，处理前导零 
    } 
    return 0;
}
```

---

## 作者：koukou (赞：1)

看了一圈好像都只有这种贪心方法。

我们可以从前往后枚举，如果这一位比下一位大，即不满足 tidy 数的要求，则将其减一，后面全部填 $9$。\
为什么填 $9$ 可行呢？首先，全部填 $9$ 一定是非递减排列的，而且由于当前这个数减了一，所以后面无论填什么都一定小于原数，而在所有情况里，全部填 $9$ 必然最优。\
证明了这个贪心方法的正确性，接着给出代码：
```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 20 + 1;
int T, l;
string n;
void work()
{
	l = n.size();
	for(int i = 0; i + 1 < l; i++)
	{
		if(n[i] > n[i + 1])
		{
			n[i]--;//减一
			for(int j = i + 1; j < l; j++) n[j] = '9';//填9
			work();//继续检查
		}
	}
	return;
}
signed main() 
{
	cin >> T;
	for(int id = 1; id <= T; id++)
	{
		cin >> n;
		work();
		int i = 0;
		while(i < l && n[i] == '0') i++;//这里很重要！要记得去掉前导零！
		cout << "Case #" << id << ": ";
		for(; i < l; i++) cout << n[i];
		cout << "\n";
	}
    return 0;
}
```

---

## 作者：yongqian123 (赞：1)

:::info[形式化题意]{open}
求最大的不超过 $N$ 的从最高位到最低位的数字是非降序的数。
:::

## 题目分析
贪心。

令 $N$ 是一个字符串。

以下的 $N$ 都被当作字符串处理。

当 $N_i>N_{i+1}$ 时，必须使得 $N_i\le N_{i+1}$。$(0\le i<|N|-1)$

$\because$ 新的 $N\le$ 原来的 $N$，  
又 $\because$ 必须使得 $N_i\le N_{i+1}(0\le i<|N|-1)$，  
$\therefore$ 新的 $N_i\le$ 原来的 $N_i$ 且 $N_{i+1}$ 要尽量大 $(0\le i<|N|-1)$。  
$\therefore$ 新的 $N_i=$ 原来的 $N_i-1$，$N_{i+1}=9(0\le i<|N|-1)$。  
又 $\because$ 新的 $N_i$ 可能会影响 $N_{i-1}(1\le i<|N|-1)$，  
$\therefore$ 逆序处理 $N$。  
$\because N$ 是字符串，  
$\therefore$ 需要用高精度。  
$\because$ 我们想要争取不 TLE，  
$\therefore$ 记录所有处理过的 $N_{i+1}=9$ 的 $i_{\min}$ 为 $f$，最后统一输出。

:::info[核心代码]
```cpp lines=5,8
cin >> N;
f = N.size() - 1, k = 0;
for (ll i = f; i >= 1; i--) if (N[i - 1] > N[i]){
	f = i, N[i--] = '9', N[i]--;
	while (N[i] < '0' && i >= 0) N[i--] = '9', N[i]--;
	i++;
}while (N[k] == '0' && k <= f) k++;
cout << N.substr(k, f + 1 - k) << string(N.size() - 1 - f, '9') << '\n';
```
:::

---

## 作者：封禁用户 (赞：0)

[P13159 [GCJ 2017 Qualification] Tidy Numbers](https://www.luogu.com.cn/problem/P13159)

我们需要找到不超过给定数字 $N$ 的最大“Tidy”数。Tidy 数的定义是其各位数字从左到右是非递减的。例如 $123$、$555$ 都是 Tidy 数，而 $321$、$110$ 不是。我们不难发现，Tidy 数的特征是：数字的每一位都不大于下一位。所以我们的策略就是：当发现某位大于下一位时，将该位减 $1$，后面所有位置为 $9$，然后递归检查。

---

AC code 如下：
```cpp
#include <iostream>
#include <string>
using namespace std;

bool isTidy(long long n) {
    string s = to_string(n);
    for (int i = 0; i < s.size() - 1; ++i)
        if (s[i] > s[i + 1]) return false;
    return true;
}

long long f(long long n) {
    if (isTidy(n)) return n;
    string s = to_string(n);
    for (int i = 0; i < s.size() - 1; ++i) {
        if (s[i] > s[i + 1]) {
            s[i]--;
            for (int j = i + 1; j < s.size(); ++j)
                s[j] = '9';
            return f(stoll(s));
        }
    }
    return n;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        long long n; cin >> n;
        cout << "Case #" << t << ": " << f(n) << endl;
    }
}
```
主要考察了贪心算法。

---

