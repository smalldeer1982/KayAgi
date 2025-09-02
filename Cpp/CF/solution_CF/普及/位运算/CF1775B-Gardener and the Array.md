# Gardener and the Array

## 题目描述

The gardener Kazimir Kazimirovich has an array of $ n $ integers $ c_1, c_2, \dots, c_n $ .

He wants to check if there are two different subsequences $ a $ and $ b $ of the original array, for which $ f(a) = f(b) $ , where $ f(x) $ is the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of all of the numbers in the sequence $ x $ .

A sequence $ q $ is a subsequence of $ p $ if $ q $ can be obtained from $ p $ by deleting several (possibly none or all) elements.

Two subsequences are considered different if the sets of indexes of their elements in the original sequence are different, that is, the values of the elements are not considered when comparing the subsequences.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775B/01e7b88f6704ebb4d7f093f81e886f156c238509.png)

## 说明/提示

It can be proven that in the first test case there are no two different subsequences $ a $ and $ b $ for which $ f(a) = f(b) $ .

In the second test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by the element at position $ 1 $ , and the subsequence $ b $ formed by the elements at positions $ 1 $ and $ 2 $ .

In the third test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by elements at positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , and the subsequence $ b $ formed by elements at positions $ 2 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
2 1 5
2 2 4
2 2 3
2
2 1 2
1 2
4
3 1 2 4
2 2 4
4 1 2 5 6
2 2 5
5
3 3 1 2
3 2 5 3
5 7 2 3 1 4
5 1 2 6 3 5
3 2 6 3
2
1 1
1 2```

### 输出

```
No
Yes
Yes
Yes
No```

# 题解

## 作者：Endt (赞：5)

# Gardener and the Array-题解

### 题意

给定一个数组 $t$，判断是否有两个不同的子序列 $a$ 和 $b$，$f(a)=f(b)$。其中，$f(x)$ 是序列 $x$ 中所有数字的位或。

### 解法

尝试通过固定 $b$ 去找 $a$。显然，$b=t$ 时，$a$ 是最容易找到的，只需要删去一个数，判断位或值是否改变就可以了。（如果 $b\not =t$，可以让 $a,b$ 同时加上 $b$ 的补集，等号仍然成立。）

可以枚举删去的数。对于每个为 $1$ 的二进制位，如果其他数在这个数位上也存在 $1$，则有解；若所有数都不满足，无解。

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Pub  public
#define  rand  Rand
std::mt19937 rand(time(NULL));

using std::min;using std::max;

int T;
int n,k;
std::vector<int> p[100005];
int d[200005];
int main(){
    scanf("%d",&T);
    while(~--T){
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            p[i].clear();
            scanf("%d",&k);
            for(int j=1,x;j<=k;++j){
                scanf("%d",&x);
                p[i].emplace_back(x);
                ++d[x];
            }
        }
        bool f=1;
        for(int i=1;i<=n;++i){
            f=1;
            for(int j:p[i])if(d[j]==1)f=0;
            if(f)break;
        }
        if(f)printf("YES\n");
        else printf("NO\n");
        for(int i=1;i<=n;++i)for(int j:p[i])--d[j];
    }
    return 0;
}
```


---

## 作者：wwwwwza (赞：3)

**题目翻译：**  
题目描述：  
园丁卡齐米尔·卡齐米罗维奇有一个 $n$ 个整数 $c_1,c_2,\cdots,c_n$ 的数组。  
他想检查原始数组中是否有两个不同的子序列 $a$ 和 $b$，其中 $f(a)=f(b)$，其中，$f(x)$ 是序列 $x$ 中所有数字的位或。  
序列 $q$ 是 $p$ 的子序列，如果可以通过删除几个（可能没有或全部）元素从 $p$ 获得 $q$。  
如果原始序列中元素的索引集合不同，则认为两个子序列不同，即在比较子序列时不考虑元素的值。  

输入：  
每个测试包含多个测试用例。第一行包含测试用例数 $t(1\leq t\leq 10^{5})$。测试用例的描述如下。
每个测试用例的第一行包含一个整数 $n(1\leq n\leq 10^{5})$，数组 $c$ 的大小。   
在这个问题中对数组 $c$ 的描述是隐式给出的，以加快输入速度。  
测试用例的以下 $n$ 行中的第 $(i+1)$ 行以整数 $k_i(1\leq k_i\leq 10^{5})$ 开始，数字 $c_i$ 中的设置位数。接下来是 $k_i$ 个不同的整数 $ p_{i,1},p_{i,2},\cdots,p_{i,k_i}$ $(1\leq p_i \leq 2 \times 10^{5})$，数字 $c_i$ 设置为 $1$ 的位数。换句话说，$c_i=2^{p_{i,1}}+2^{p_{i,2}}+\cdots+2^{p_{i,k_i}}$。 
保证所有测试中 $k_i$ 的总和不超过 $10^{5}$。

输出：
对于每组输入，如果存在 $f(a)=f(b)$ 的两个不同子序列，则打印“是”，否则打印“否”。    
您可以在任何情况下输出答案（上限或下限）。例如，字符串 “yEs”,“yEs”,“yEs” 和 “yEs”将被识别为肯定响应。

说明/提示：
可以证明，在第一个测试用例中，没有两个不同的子序列 $a$ 和 $b$，其中 $f(a)=f(b)$。   
在第二个测试案例中，可能的答案之一是以下子序列：由位置 $1$ 处的元素形成的子序列 $a$，以及由位置 $1$ 和 $2$ 处的元素构成的子序列 $b$。  
在第三个测试案例中，可能的答案之一是以下子序列：由位置 $1,2,3$ 和 $4$ 处的元素形成的子序列 $a$，以及由位置 $2,3,4$ 处的元件形成的子顺序 $b$。


**思路：**
这约等于一个包含问题，定义集合 $a$ 包含全部 $c_i$，定义集合 $b$ 包含除了 $c_k$ 之外的全部 $c_i$，如果集合 $a$ 包含集合 $b$，则有解。  
首先用一个桶存储所有的 $p_{i,j}$，再枚举每一个 $c_i$，看看 $c_{i,j}$ 在桶里的个数是否都大于二（因为有一个是自己提供的），如果都大于二，表示有解。

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int t,n,k,p[N],vis[N];
signed main(){
	scanf("%d",&t);
	while(t--){
		int cnt=0;
		scanf("%d",&n);//输入 
		for(int i=1;i<=n;i++){
			scanf("%d",&k);
			for(int j=1;j<=k;j++){
				scanf("%d",&p[++cnt]);//将二维数组压成一维 
				vis[p[cnt]]++;
			}
			p[++cnt]=-1;
		}
		bool flag=0,ok=0;
		for(int i=1;i<=cnt;i++){//枚举桶 
			if(p[i]==-1){
				if(!flag){
					ok=1;
					break;
				}
				flag=0;
			}else{
				if(vis[p[i]]<2)flag=1;
			}
		}
		for(int i=1;i<=cnt;i++){//重置 
			if(p[i]!=-1){
				vis[p[i]]=0;
			}
		}
		if(ok)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

```

---

## 作者：xu222ux (赞：2)

# [CF1775B](https://www.luogu.com.cn/problem/CF1775B)

## 简化版题意

给定一个有 $n$ 个整数的数组 $c$。判断是否有两个不同的子序列 $a$ 和 $b$，满足 $\operatorname{f(a)}=\operatorname{f(b)}$。其中，$\operatorname{f(x)}$ 是序列 $x$ 中所有数字的按位或运算的结果。

### 思路

看见此题我本是没思路的，但后来发现题目良心的给了样例解释，让我找到了规律。

我发现，如果可以满足题意，那么就一定有一组解是 $n$ 个数都选和选 $n-1$ 个数。为什么呢，因为或运算的特殊性质。

所以只需要从 $n$ 个数中取出一个是结果不变就行了。

#### 怎么取？

会发现取出什么样的数才会对最终结果有影响，没错，就是他某位是一且其他数的这一位都不是一。


## code
```cpp

#include<bits/stdc++.h>
using namespace std;
int n;
int k[200005];
vector<int>v[200005];
int r[200005];
int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            v[i].clear();
            scanf("%d",&k[i]);
            for(int j=1;j<=k[i];j++){
                int a;scanf("%d",&a);
                r[a]++;
                v[i].emplace_back(a);
            }
        }
        string out="No";
        for(int i=1;i<=n;i++){
            bool flag=true;
            for(auto z:v[i]){
                if(r[z]==1){
                    flag=false;
                    break;
                }
            }
            if(flag){
                out="";
                printf("Yes");
                break;
            }
        }
        cout<<out<<endl;
        for(int i=1;i<=n;i++)
            for(auto z:v[i])
                r[z]--;
    }
    return 0;
}

```


---

## 作者：BFSDFS123 (赞：2)

我们定义一个数是“必要的”，当且仅当如果我们不选择该数的话，其它所有数的或值不等于所有数的或值。

此处判定一个数是否为“必要的”，关键在于他的二进制为 $1$ 的位上是否有一个位置在所有数中只出现了一次。

结论是如果所有数都是“必要的”，则无解，否则**一定**有解。

证明也很简单：

如果所有数都是“必要的”，那很容易发现，我们去掉任何一个数，答案都不相同，故我们也无法找到两个或值相同的子序列，一定无解。

如果有一个数不是“必要的”，则一个可行的构造方式为：整个序列和整个序列去掉这个数。

因为这个数不是“必要的”，所以去掉与不去掉答案都不会变。

故得证。

代码：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
#define ull unsigned long long
#define ll long long
using namespace std;
//#define int long long
map<int,int> mp;
vector<int> vc[100010];
void work()
{
    mp.clear();
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        vc[i].clear();
        for(int j=1;j<=k;j++)
        {
            int p;
            scanf("%d",&p);
            vc[i].push_back(p);
            mp[p]++;
        }
    }
    
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        bool flag=true;;
        for(auto j:vc[i])
        {
            if(mp[j]==1)
            {
                flag=false;
            }
        }
        ans|=flag;
    }
    if(ans)
    {
        puts("YES");
    }else{
        puts("NO");
    } 
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        work();
    }
    return 0;
}

```

---

## 作者：ran_qwq (赞：1)

这题数据较大，暴力完全过不去。

统计每一个数字出现的次数，对于每一个 $c_i$，判断所有 $p_{i,k_i}$ 是否只出现过一次。如果所有 $c_i$ 都有一个 $p_{i,k_i}$ 只出现过一次，那么对于任意一个子序列它的数字集合都是不同的，输出 $\texttt{No}$，否则输出 $\texttt{Yes}$。注意清空时不要用 memset，应该清空所有用过的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,INF=1e9,Mod=998244353;
//省略快读快写
int T,n,cnt,a[N],b[N];
vector<int> v[N];
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),cnt=0;
		for(int i=1;i<=n;i++)
			v[i].clear();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			for(int j=1;j<=a[i];j++)
			{
				int x=read();
				b[x]++,v[i].push_back(x);
			}
		}
		int f=0;
		for(int i=1;i<=n&&!f;i++)
		{
			int flag=1;
			for(int j=0;j<a[i]&&flag;j++)
				if(b[v[i][j]]==1)
					flag=0;
			if(flag)
				puts("Yes"),f=1;
		}
		if(!f)
			puts("No");
		for(int i=1;i<=n;i++)
			for(int j=0;j<a[i];j++)
				b[v[i][j]]=0;
	}
}

```


---

## 作者：OJ_killer (赞：0)

~~位运算大法好 && STL大法好~~

## 前置知识：

STL、位运算。

+ 思路

先统计所有二进制位数出现的次数，然后再看每个数，如果这个数里的 $k$ 个二进制位数的计数都大于等于 $2$，则要么能用其他数凑出与这个数相等的数。要么这个数的二进制位数时期其他能凑出来的位数的集合的子集。

 + 代码
 
```cpp
#include<bits/stdc++.h>
using namespace std;

int T;

int main(){
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        map<int, int> mp;
        vector<vector<int> > a(n); 
        for(int i = 0; i < n; i++){
            int cnt;
            cin >> cnt;
            a[i].resize(cnt);
            for(int j = 0; j < cnt; j++)
                cin >> a[i][j], mp[a[i][j]]++;
        }
        bool f = 0;
        for(int i = 0; i < n; i++){ //遍历
            for(auto x : a[i])
				mp[x]--;
            bool flag = 1;
            for(auto x : a[i])
               flag &= (mp[x] > 0);
            if (flag){
                f = 1;
                break; //不满足跳出
            }
            for(auto x : a[i])
				mp[x]++;
        }
        if (f)
        	cout << "Yes" << "\n";
        else
        	cout << "No" << "\n";
    }
	return 0;
}

---

## 作者：daiarineko (赞：0)

# 题解【CF1775B Gardener and the Array】

## 0. 题目描述

给你一个数列 $a$，请你找出它的两个不同子**序列** $x,y$，使得这两个子序列的按位或和相同。**多组数据**。

输入格式：每一行先给出 $k_i$，再给出若干个 $p_j$，代表 $a_i$ 二进制下的第 $p_j$ 位为 $1$。具体见样例。**保证一行内的 $p$ 不会有重复。**

按位或和：数列 $s$ 的按位或和为 $s_1 \operatorname{or} s_2 \operatorname{or}\dots  \operatorname{or} s_{|s|}$，其中 $\operatorname{or}$ 为按位或运算。

## 1. 思路

这个输入格式使得数的二进制表示中 $1$ 很少，但是数本身很大。

实际上，这个“子序列”就是用来吓人的。可以证明，如果有解，一定有一个解满足 $x = a$。

既然如此，$y$ 一定是在 $a$ 中移除一个数。因为如果移除两个数有解，移除一个数一定也有解。

首先，有暴力做法：枚举移除的是哪个数，再判断按位或和是否相等。这肯定会 TLE。

考虑如何优化。我们存储每一位在整个数组里出现的个数 $vis_i$。这样移除一个数 $a_i$ 后，按位或和不变的**充要条件**即为：对于所有的 $1\leq j\leq k_i$，$vis_{p_{i,j}} > 1$。换句话说，移除这个数，这些位仍然存在。

这样的话，预处理所有数的按位或和，复杂度为 $O(\sum k)$；枚举移除的是哪个数，复杂度仍然为 $O(\sum k)$，可以通过。

## 2. 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 200005;
int t, n;
vector<int> c[maxn];
int vis[maxn];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            int k;
            cin >> k;
            c[i].clear();
            while (k--)
            {
                int p;
                cin >> p;
                c[i].emplace_back(p); // 存储 p 数组
            }
        }
        bool flag = false;
        for (int i = 1; i <= n; ++i)
            for (auto j : c[i])
                ++vis[j]; // 预处理所有位的出现次数
        for (int i = 1; i <= n; ++i)
        {
            bool flag2 = true;
            for (auto j : c[i])
                if (vis[j] < 2)
                {
                    flag2 = false;
                    break; // 若有任何一位不满足上述条件，不能通过移除当前数得到解
                }
            if (flag2)
            { // 若所有位都满足条件，则有解
                flag = true;
                break;
            }
        }
        for (int i = 1; i <= n; ++i)
            for (auto j : c[i])
                --vis[j]; // 记得多测清空！
        if (flag)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    cout.flush();
    return 0;
}
```

## 3. 附注

遇到询问是否有解的题，我们可以先在不改变解的存在性的情况下简化问题。例如这题就可以从“选择两个子序列”简化为“删除一个数”，大幅提升了求解速度，同时也更容易得到问题的答案。

当然，这样的 trick 也可以用在构造题中。例如本场的 A 题，就可以将字符串分成多个类型，具体见 A 题题解（题解区很多这类做法）。


---

## 作者：Mine_King (赞：0)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/17042849.html)

# B. Gardener and the Array

## Problem

[CF1775B Gardener and the Array](https://codeforces.com/contest/1775/problem/B)

**题目大意：**

给你一个序列，你要判断能否找到两个不同的子序列使得他们或起来相等。但序列中数的大小为 $2^{2 \times 10^5}$。题目会给出每个数二进制下哪些位为 $1$，保证输入量不超过 $10^5$。

## Solution

首先容易想到一个结论：若题目有解则一定存在一种方案使得其中一个子序列是全串。

可以通过调整法证明这个结论：考虑任意一个合法解 $A,B$，设 $|A| \ge |B|$，考虑所有不在 $A$ 中的数，若将其加入 $A$ 后或和不变则直接加入，否则其一定也不在 $B$ 中，将其同时加入两个子序列即可。

然后容易想到另一个结论：若题目有解则一定存在一种方案使得其中一个子序列是全串且另一个子序列是全串扣掉某个数。

因为全串的或和一定大于等于任意一个子串的或和，所以当存在一个合法解使得其中一个子序列是全串的情况下，往另一个串里添数一定合法，一直添加直到只剩一个数即可。

故这题做法呼之欲出：求全串或和，枚举不在另一个子串内的数，计算是否合法。

具体实现时可以用一个数组 $b_i$ 表示全串中二进制下第 $i$ 位为 $1$ 的数的个数。判断是否合法只要枚举这个数为 $1$ 的位，判断这一位的 $b$ 是否 $> 1$ 即可。

## Code

```cpp
// Think twice, code once.
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T,n,b[200005];
vector<int> c[100005];

int check(int x) {
	int flag=1;
	for (int i:c[x])
		if (!--b[i]) flag=0;
	for (int i:c[x]) b[i]++;
	return flag;
}

int main() {
	scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		for (int i=1;i<=n;i++) {
			int len;
			scanf("%d",&len);
			c[i].resize(len);
			for (int j=0;j<len;j++)
				scanf("%d",&c[i][j]),b[c[i][j]]++;
		}
		for (int i=1;i<=n;i++)
			if (check(i)) {
				puts("Yes");
				goto NXT;
			}
		puts("No");
		NXT:;
		for (int i=1;i<=n;i++) {
			for (int j:c[i]) b[j]--;
			vector<int> ().swap(c[i]);
		}
	}
	return 0;
}
```

---

