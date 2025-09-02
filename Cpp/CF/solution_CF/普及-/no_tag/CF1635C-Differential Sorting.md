# Differential Sorting

## 题目描述

You are given an array $ a $ of $ n $ elements.

Your can perform the following operation no more than $ n $ times: Select three indices $ x,y,z $ $ (1 \leq x < y < z \leq n) $ and replace $ a_x $ with $ a_y - a_z $ . After the operation, $ |a_x| $ need to be less than $ 10^{18} $ .

Your goal is to make the resulting array non-decreasing. If there are multiple solutions, you can output any. If it is impossible to achieve, you should report it as well.

## 说明/提示

In the first example, the array becomes

 $ [-6,-4,2,-1,2] $ after the first operation,

 $ [-6,-4,-3,-1,2] $ after the second operation.

In the second example, it is impossible to make the array sorted after any sequence of operations.

In the third example, the array is already sorted, so we don't need to perform any operations.

## 样例 #1

### 输入

```
3
5
5 -4 2 -1 2
3
4 3 2
3
-3 -2 -1```

### 输出

```
2
1 2 3
3 4 5
-1
0```

# 题解

## 作者：yitian_ (赞：8)

## 题目分析

给定一个长度为 $n$ 的数组 $a$，可以执行不超过 $n$ 次操作，每次操作可以选择三个不同的索引 $x,y.z$，并 $a_x \gets a_y - a_z $。要求最终的数组按照非降序排列，并给出所构造的方案的操作次数，以及每次操作中你选择的三个整数 $x,y,z$。如果无解，输出 $-1$。

我们可以先判断是否已经是非降序排列，再判断是否无解，最后再处理一般情况。

## 思路

1. **检查数组是否已经是非降序排列：** 
   - 遍历数组，检查相邻元素是否满足非降序关系（即当前元素大于等于前一个元素）。
   - 如果有任何一对相邻元素不满足非降序关系，则将标志 $f$ 置为 $1$，表示数组不是非降序排列。

2. **处理最后两个元素的特殊情况：**
   - 如果最后两个元素不满足非降序关系（即倒数第二个元素大于最后一个元素），则无法通过操作将数组变为非降序，直接输出 $-1$。
   - 否则，如果最后两个元素满足非降序关系，但是差值大于倒数第二个元素的值，则同样无法通过操作将数组变为非降序，也直接输出 $-1$。

3. **处理一般情况：**
   - 如果以上两种情况都不满足，说明数组可以通过操作变为非降序。
   - 输出操作次数 $n-2$（因为最后两个元素已经满足非降序关系）。
   - 对于前 $n-2$ 个元素，每次操作选择位置 $i$、$n-1$、$n$，使得 $a_i = a_{n-1} - a_n$。

## C++ 代码实现

```c
#include<bits/stdc++.h>
using namespace std;

int a[200010]; // 定义一个全局数组 a，用于存储输入的数组元素

int main()
{
    int t;
    cin >> t; // 输入测试用例的数量
    while(t--) // 循环处理每个测试用例
	{
        int n,f=0; // n表示数组长度
        cin >> n; // 输入数组的长度
        a[0]=-1000000001;
        for(int i=1;i<=n;i++)
        {
        	cin >> a[i]; // 输入数组的元素值
			if(a[i]<a[i-1]) // 如果当前元素小于前一个元素，说明需要进行操作
			{
			    f=1; // 将 f 置为1
			}
        }
        if(f==0) // 如果 f 为 0，说明数组已经是非降序的，无需进行操作
		{
            cout << 0 << endl; // 输出操作次数为 0
            continue; // 继续处理下一个测试用例
        }
        if(a[n-1]>a[n]) // 如果倒数第二个元素大于最后一个元素，无法通过操作使得数组非降序
        {
        	cout << -1 << endl; // 输出 -1 表示无解
        }
        else if(a[n-1]-a[n]>a[n-1]) // 如果倒数第二个元素与最后一个元素之差大于倒数第二个元素，无法通过操作使得数组非降序
        {
        	cout << -1 << endl; // 输出 -1 表示无解
        }
        else // 否则，可以通过一定操作使得数组变为非降序
		{
            cout << n-2<< endl; // 输出操作次数为 n-2
            for(int i=1;i<=n-2;i++) // 输出具体的操作
            {
            	cout << i << " " << n - 1 << " " << n << endl; // 每次操作选择倒数第二个元素和最后一个元素
            }
        }
    }
    return 0;
}
```

---

## 作者：Cat_shao (赞：3)

给定一个长度为 $n$ 的序列 $a$ ，可以进行 $n$ 次操作。每次操作可以选三个位置 $x, y, z \ (1 \le x < y < z \le n)$ ，将 $a_x$ 替换为 $a_y - a_z$ 。求出一系列操作使得操作过后 $a$ 单调递增。

首先排除掉几种好判断的情况：
- 给定 $a$ 单调递增，一次操作都不需要
- $a_{n - 1} > a_n$ ，无论怎么操作都没法使 $a$ 单调递增。

从 $n$ 往 1 扫，很容易找出一个位置 $i$ 使得 $a_i > a_{i + 1}$ 且 $[i + 1, n]$ 单调递增。记 $a_pos$ 为 $[i + 2, n]$ 中任意一个 $\ge 0$ 的。从 $i$ 到 1 扫，如果到了位置 $j$ 使得 $a_j > a_{j + 1}$ ，由于 $[j + 1, n]$ 之前已经单调递增，直接让 $a_j = a_{j + 1} - a_pos$ ，这次操作中的三个位置也就是 $j, j + 1, pos$ 。

```cpp
//
// Created by Cat-shao on 2022/2/20.
//

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;
typedef tuple<int, int, int> TII;

int n;
long long a[MAX_N];
vector<TII> op;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        if (a[n - 1] > a[n]) {
            cout << "-1\n";
            continue;
        }
        if (is_sorted(a + 1, a + n + 1)) {
            cout << "0\n";
            continue;
        }
        int i = n - 2;
        while (i >= 1 && a[i] <= a[i + 1]) {
            i --;
        }
        int pos = n;
        while (pos > i + 1) {
            if (a[pos] >= 0) {
                break;
            } else {
                pos--;
            }
        }
        if (pos == i + 1) {
            cout << "-1\n";
        } else {
            op.clear();
            for (; i >= 1; --i) {
                if (a[i] > a[i + 1]) {
                    a[i] = a[i + 1] - a[pos];
                    op.emplace_back(i, i + 1, pos);
                }
            }
            cout << op.size() << '\n';
            for (const auto j : op) {
                cout << get<0>(j) << ' ' << get<1>(j) << ' ' << get<2>(j) << '\n';
            }
        }
    }
    return 0;
}
```

---

## 作者：洛谷小灵 (赞：3)

### 声明

- 语言：Java
- Tips：又是一篇蒟蒻的题解...QAQ...

### 解析

**由 $x,y,z$ （$1\leq x \lt y \lt z \leq n$）这个条件可知：**

1. 一定存在 $a_n \ge a_{n-1}$ ，若不存在则此序列无解，因为无法找出满足条件的 3 个索引，因此无法处理这种关系。
2. 在满足上面的条件的前提下，若 $a_n \ge 0$ 则前面的所有数字都可以使用 $a_x = a_n - a_{n-1}$ 来修正（修正为同一个数值，题目没说严格递增，因此可行）。
3. 若 $a_n < 0$ 且此序列**非升序**，则此序列无解。
4. 若 $a_n < 0$ 且此序列**升序**，则此序列有解。

**证明：**若 $a_n < 0$ 且此序列**非升序**，则此序列无解。**（介于我只是个学渣，也不知道算不算证明，因此仅供参考哈）**

假设该序列为 $a_i \ge a_{i+1} \leq \dots \leq a_{n-1} \leq a_n$ ，存在 $a_i \ge a_{i+1}$ ，从右向左看，你需要修改 $a_i$ 或 $a_{i+1}$ 其中一个，使其满足 $a_i \leq a_{i+1}$ ，因为 $a_n < 0$ ，为了保证整个序列不降（即保证升序），所以整个序列都是负数。根据负数减负数的性质可知，当 $-a-(-b)$ ，$-b$ 的值越小，则结果越大，反之越小。假设修改 $a_{i+1}$ ，后面的值是越来越大，$a_x = a_y - a_z$ 最终的值必然越来越小。

### AC Code

```java
public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StreamTokenizer st = new StreamTokenizer(br);
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) throws Exception {
        int T = nextInt();
        while(T-- != 0) {
            int n = nextInt();
            int[] A = new int[n+1];
            for(int i = 1; i <= n; i++) A[i] = nextInt();
            if(A[n] < A[n-1]) {
                out.println(-1);
                continue;
            }
            if(A[n] < 0) {
                boolean flag = false;
                for(int i = 1; i < n; i++) {
                    if(A[i] > A[i+1]) {
                        flag = true;
                        break;
                    }
                }
                if(flag) out.println(-1);
                else out.println(0);
                continue;
            }
            out.println(n-2);
            for(int i = 1; i < n - 1; i++) {
                out.printf("%d %d %d\n", i, n-1, n);
            }
        }
        out.flush();
    }

    public static int nextInt() throws Exception {
        st.nextToken();
        return (int) st.nval;
    }

    public static String nextStr() throws Exception {
        st.nextToken();
        return st.sval;
    }
}
```

---

## 作者：Storm_Lightning (赞：1)

# CF1635C Differential Sorting 题解

## 题目大意

给定一个长度为 $n$ 的序列 $a[i]$，然后再进行不超过 $n$ 次操作，每次选三个数 $x,y,z$，然后执行 $a[x]=a[y]-a[z]$ 的操作。若有解，则输出操作次数和每次操作的 $x,y,z$ 即可。

## 思路分析

首先，我们可以对序列 $a$ 进行分类讨论。

- 如果序列 $a$ 是单调不减的，则输出 $0$ 即可。

- 若 $a$ 不是单调不减的，我们考虑若 $a[n-1]>a[n]$，则此时必定无解，因为这样的话 $a[n-1]$ 的值就无法更新了。还有一点就是，若 $a[n]<0$ 则无解，否则就可以将前面的数都修改为 $a[n-1]-a[n]$。

### 提示

- 本题多组数据。

- 要开 long long。

## 代码

```cpp
int n,t;
int a[200010];
signed main()
{
	cin>>t;
	while(t--)
	{
		int flag=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(i>1&&a[i]<a[i-1])
			{
				flag=1;
			}
		}
		if(flag==0)
		{
			cout<<0<<endl;
			continue;
		}
		if(a[n-1]>a[n]||a[n]<0)
		{
			cout<<-1<<endl;
			continue;
		}
		cout<<n-2<<endl;
		for(int i=1;i<=n-2;i++)
		{
			cout<<i<<' '<<n-1<<' '<<n<<endl;
		}
	}
	return 0;
}
```

克制自己，不要抄代码！

---

## 作者：清烛 (赞：1)

题意：给定一个序列 $a$，每次操作可以选择 $1\le x < y < z\le n$，然后 $a_x\leftarrow a_y - a_z$，构造一个方案使得整个序列不降。$n = 2\times 10^5$。

我们注意到，选择的三个下标一定要满足 $x<y<z$，所以发现第一个性质：**若 $a_{n-1}>a_n$，则无解**，因为我们没办法修正 $a_{n - 1}$。接下来，我们注意到，若 $a_n\ge0$，则我们可以将前面所有数字修正为 $a_{n-1} -a_n$。否则无解，除非序列一开始就不降。

证明：假设 $a_n<0$ 且序列初始不满足不降，并且我们用了 $m$ 步完成排序。假设我们最后一步操作是 $(x_m, y_m, z_m)$，不难发现为了保证不降，所有元素都是负值，故 $a_{z_m}$ 一定  $< 0$，但是 $a_{x_m} = a_{y_m} - a_{z_m}>a_{y_m}$，假设不成立。

```cpp
const int maxn = 2e5 + 5;
int a[maxn], n;

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        if (is_sorted(a + 1, a + n + 1)) {
            print(0);
            continue;
        }
        if (a[n - 1] > a[n] || a[n] < 0) {
            print(-1);
            continue;
        }
        print(n - 2);
        FOR(i, 1, n - 2) print(i, n - 1, n);
    }
    return output(), 0;
}
```

---

## 作者：_WF_ (赞：0)

## 题目分析
给定一个序列 $A$，每次操作**可以**选择 $1 \le x < y < z \le n$，让 $a_x = a_y - a_z$，构造一个方案使成为序列变为**不下降序列**（即满足 ${\forall}A_i \le A_{i+1}$）。

* 特殊：关于无解的情况，不难看出当 $a_{n-1} > a_n$ 无解，因为 $a_{n-1}$ 无法被修改。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,cnt=0;
int a[200010];
int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		a[0]=INT_MIN;//初始最小值
		for(int i=1;i<=n;i++){
			cin >> a[i];
			if(a[i]<a[i-1])cnt=1;//对是否初始是不下降子序列
		}
		if(cnt==0){
			cout << 0 << endl;
			continue;
		}
		if(a[n-1]>a[n])
			cout << -1 << endl; 
		else if(a[n-1]-a[n]>a[n-1])
			cout << -1 << endl;//判无解
		else{
			cout << n-2<< endl; 
			for(int i=1;i<=n-2;i++) 
			cout << i << " " << n - 1 << " " << n << endl;
		}
	}
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF1635C](https://www.luogu.com.cn/problem/CF1635C) || [CodeForces 1635 C](https://codeforces.com/contest/1635/problem/C)

### 简要题意
给出一个由 $n$ 个元素组成的数组 $a$，你可以执行以下操作不超过 $n$ 次：
  * 选择三个元素 $a_x,a_y,a_z(1 \leq x , y , z \leq n)$，并将 $a_x$ 替换为 $a_y - a_z$。操作完成后，$|a_x|$ 必须小于 $10^{18}$。

请判断是否可以使操作后的数组不递减排列，如果有则输出任意一种方案，否则输出 $-1$。

### 思路
如果 $a_{n-1} \gt a_n$，那么最后两个元素永远都无法改为不递减的，答案就是 $-1$。

如果 $a_n \geq 0$，则必有一种解决方案：对每个 $1\le i\le n−2$ 执行操作 $(i,n−1,n)$。

例如序列 $\{4,2,1,3\}$ 可以进行以下操作：

* $\{4,2,1,3\}\Rightarrow \{-2,2,1,3\}\Rightarrow\{-2,-2,1,3\}$

否则，只有当且仅当初始数组已经为不递减排序时，才有解 $0$。

[记录](https://codeforces.com/contest/1635/submission/283863043)

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005];
int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (a[n - 2] > a[n - 1]) cout << -1 << endl; //最后两项无法交换，无解
        else
        {
            if (a[n - 1] < 0)
            {
                if (is_sorted(a, a + n)) cout << 0 << endl; //除非已经排序，否则无解
                else cout << -1 << endl;
            }
            else
            {
                cout << n - 2 << endl; //一共进行n-2次操作
                for (int i = 1; i <= n - 2; ++i) cout << i << ' ' << n - 1 << ' ' << n << endl;
            }
        }
    }
    return 0;
}
```

---

## 作者：ZYXzyx1006 (赞：0)

## 题目分析
你的目标是使得最终的数组按照非降序排列。请给出你所构造的方案的操作次数，并给出每次操作中你选择的三个整数
观察题面，显然有“构造”二字，那么就是构造题，存在规律和多解。
## 仔细分析题意 
非降序排列就说明元素与元素可以相等，那么可以将所有数字改成同一个数满足需求。保持不下降就意味着应尽量减少靠后元素的改变，防止影响已经改好的数要再次改变。那么想到保持数组末两位元素不变，将前面的元素赋值为末两位之差。
此外需要注意，若数组本身就是非降序的，输出 0。若倒数第二位大于最后一位，样例无解。若最后一位小于 0，则无解，分两类讨论。如果倒数第二位大于最后一位和最后一位大于倒数第二位。仔细思考。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[214514];
int t;
int main()
{
    cin>>t;
    for(int i=1; i<=t; i++) 
	{   
	    bool f=0;
        int n; 
        cin>>n;
        for(int i1=1;i1<=n;i1++)
        {
        	cin>>a[i1];
			if(a[i1]<a[i1+1]) 
			    f=1; //是否已经单调上升（>=） 
        }
        if(f==0) //说明数组已经是非降序的，无需进行操作
		{
            cout<<0<<endl;
            continue;
        }
        if(a[n-1]>a[n]||a[n]<0) 
        	cout<<-1<<endl; //无解
        else //可以通过(n-2)次操作达成目标 
		{
            cout<<n-2<<endl;
            for(int j=1;j<=n-2;j++)
            	cout<<j<<" "<<n-1<<" "<<n<<endl; 
        }
    }
}
```
#### 第一次写题解，写的不好还请见谅QWQ

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1635C)

# 题意：
给你一个长度为 $n$ 的数组，你每次可以选择三个位置 $x$，$y$，$z$ 并且 $x \lt y \lt z$。然后将 $a_x$ 换成 $a_y - a_z$。你要在 $n$ 步之内将这个数组变成非降序，问最终的数组长成什么样。

# 思路：

首先非降序的情况直接输出，然后对于最后两个位置，一定要是非降序的，接下来我们对于前面的 $n - 2$ 个数，只需要等于 $a_{n-1} - a_n$ 即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int t,n,a[N];
signed main(){
    cin>>t;
    while(t--){
        int f=0;
        cin>>n;
        a[0]=-1e9-1;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            f|=a[i]<a[i-1];
        }
        if(!f){
            cout<<0<<endl;
            continue;
        }
        if(a[n-1]>a[n]){
            cout<<-1<<endl;
        }else if(a[n-1]-a[n]>a[n-1]){
            cout<<-1<<endl;
        }else{
            cout<<n-2<<endl;
            for(int i=1;i<n-1;i++){
                cout<<i<<" "<<n-1<<" "<<n<<endl;
            }
        }
    }
    return 0;
}
```
完结撒花~

---

## 作者：xiaokang_suancai (赞：0)

# CF1635C 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1635C)
## 题目大意
给定长为 $n$ 的数组 $a$，最多执行 $n$ 次操作，每次操作可以选择三个下标 $x,y,z$，使得 $a_x=a_y-a_z$。如果无解则输出 $-1$。
## 思路分析
首先是不需要执行任何操作的情况。显然，当 $a$ 不是单调递减的时候，不需要操作，输出 $0$ 即可。\
其次是无解的情况。不难发现，如果 $a_{n-1} > a_n$ 或者 $a_{n-1}-a_n > a_{n-1}$，我们不可能在规定次数内将数组变为非降序。\
最后是一般情况。通过推理易证，只要在一般情况下的数组都恰好需要 $n-2$ 次操作。我们只要在每一次循环中都使 $a_i=a_{n-1}-a_n$ 就一定能将数组变为非降序。\
一道不错的思维题。
## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		a[0]=-0x3fffffff; // 这里是为了防止在判定非降序时数组边界的随机数导致误判
		bool flag=true;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]<a[i-1])
			{
				flag=false; // 如果判定到有降序就直接跳过
				break;
			}
		}
		if(flag)
		{
			cout<<0<<endl;
			continue;
		} // 在非降序的情况下直接输出 0 
		if(a[n-1]>a[n])
		{
			cout<<-1<<endl;
			continue;
		}
		if(a[n-1]-a[n]>a[n-1])
		{
			cout<<-1<<endl;
			continue;
		} // 判断无解的情况，上面已经讲了 
		else
		{
			cout<<n-2<<endl;
			for(int i=1;i<=n-2;i++)
				cout<<i<<" "<<n-1<<" "<<n<<endl;
		} // 套用推导出来的公式
	}
	return 0;
}
```

---

## 作者：Tulip_ (赞：0)

### 题意

给定一个长度为 $n$ 的数组 $a$。你可以执行**不超过 $n$ 次操作**，每次操作中，你可以选择**三个整数 $x,y,z$**，需要保证 $1\leqslant x<y<z\leqslant n$ 且操作之后 $\left|a_x\right|<10^{18}$，然后将 $a_x$ 替换为 $a_y-a_z$。

你的目标是使得**最终的数组按照非降序排列**。请给出你所构造的方案的操作次数，并给出每次操作中你选择的三个整数 $x,y,z$；或者判断根本不可能通过执行不超过 $n$ 次操作达到目标，此时输出 `-1`。

### 思路

我们需要**三个分类讨论**：

1. 一开始就判断**数组按照非降序排列**，如果满足就输出 `0`。

这个就是边输入边判断，一发现不满足就标记。

2. 思考 `1`：哪些不满足需输出 `-1`

我们思考后会发现 $a_n$ 与 $a_{n-1}$ 的关系跟输出 `-1`。

**$a_{n-1}$ 大于 $a_{n}$ 或者是 $a_{n-1}-a_{n}$ 大于 $a_{n-1}$**，则无法通过操作将数组变为非降序，直接输出 `−1`。

3. 思考 `2`：哪种方案可以最简单的打出来，有那种固定的更改方案吗。

这个可能有点难，那看这个。

通过思考，我发现只要满足，且有更改方案的个数都为 $n-2$。

对于每一次的更改，我们**可以将 $a_{i}$ 替换为 $a_{n}$ 与 $a_{n-1}$ 相减**，这样我们就不用一个一个判断，只需要**直接输出 $a_i,a_n-1,a_n$。**

### 注意

- 边输入边判断时，我们要**记得加上 $i>1$**，这是因为输入第一个时，可能会将标记数标记，使得输出了 `-1`。

- 数组**记得不要卡的刚刚好**，建议设为 $2 \times 10^5 +5$ 不然会 `RE` 的！

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Max=2e5+5;
int t,n,a[Max]; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
    	cin>>n;  
		int o=0;
    	for(int i=1;i<=n;i++){
    		cin>>a[i];
    		if(i>1&&a[i]<a[i-1])  o=1; 
		}
    	if(o==0){
    		cout<<0<<endl;
    		continue;
		}else if(a[n-1]>a[n]||a[n-1]-a[n]>a[n-1]){
			cout<<-1<<endl;
			continue;
		}else{
			cout<<n-2<<endl;
			for(int i=1;i<=n-2;i++){
				cout<<i<<" "<<n-1<<" "<<n<<endl;
			}
		}
	}
	return 0;
}
```

讲到这应该明白了吧，快去去试一试！

---

