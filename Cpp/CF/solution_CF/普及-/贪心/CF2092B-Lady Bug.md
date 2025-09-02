# Lady Bug

## 题目描述

当 Dasha Purova 刚越过法国边境时，反派 Markaron 绑架了她并将她关押在其城堡下的监狱中。幸运的是，神奇的 Lady Bug 得知 Dasha 的消息后立即赶往 Markaron 的城堡营救她。然而，她需要破解一个复杂密码才能进入。

该密码由两个长度为 $n$ 的比特字符串 $a$ 和 $b$ 组成。Lady Bug 在一次操作中可以选择任意索引 $2 \leq i \leq n$ 并执行以下两种操作之一：

1. 交换($a_i$, $b_{i-1}$)（交换 $a_i$ 和 $b_{i-1}$ 的值），或  
2. 交换($b_i$, $a_{i-1}$)（交换 $b_i$ 和 $a_{i-1}$ 的值）。

Lady Bug 可以进行任意次数的操作。若她能使第一个字符串 $a$ 仅由 0 组成，则视为密码破解成功。请帮助她判断是否能成功营救 Dasha。

## 说明/提示

第一个测试用例中，字符串 $a$ 本身已全为 0。

第二个测试用例中，一种可能的操作序列为：

1. 交换$(a_2, b_{1})$  
  $$$\mathtt{0{\color{red}{1}}0001}$$$  
  $$$\mathtt{{\color{red}{0}}10111}$$$
2. 交换$(b_5, a_{4})$  
  $$$\mathtt{000{\color{red}{0}}01}$$$  
  $$$\mathtt{1101{\color{red}{1}}1}$$$
3. 交换$(a_4, b_{3})$  
  $$$\mathtt{000{\color{red}{1}}01}$$$  
  $$$\mathtt{11{\color{red}{0}}101}$$$
4. 交换$(a_5, b_{4})$  
  $$$\mathtt{00000{\color{red}{1}}}$$$  
  $$$\mathtt{1111{\color{red}{0}}1}$$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
000
000
6
010001
010111
5
10000
01010
2
11
00```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：枫原万叶 (赞：4)

# CF2092B Lady Bug 题解

## 分析

我们知道是一个元素可以与它斜对角的元素交换，如下图，一个元素是可以去到这样顺序中的任何一个位置的地方。

![](https://cdn.luogu.com.cn/upload/image_hosting/o955gbow.png)

然后题目又需要我们让第一个序列都为 0 ，那么就看一下 1 是否都可以到下面的序列，也就是判断红线上的数是否大于 $\frac{n}{2}$ ，蓝线上的数是否大于 $\frac{n}{2}$ (这里要向上取整，因为出现奇数)，由此就可以得到代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
int zh(int n){
	return (n%2==1)?(n/2)+1:n/2;
}
bool fun(){
	int n;
	int arr1[MAXN],arr2[MAXN];
	int cnt1=0,cnt2=0;
	scanf("%d",&n);
	string s1,s2;
	cin>>s1;
	cin>>s2;
	for(int i=1;i<=n;i++){
		arr1[i]=s1[i-1]-'0';
	}
	for(int i=1;i<=n;i++){
		arr2[i]=s2[i-1]-'0';
	}
	for(int i=1;i<=n;i+=2)
		swap(arr1[i],arr2[i]);
	for(int i=1;i<=n;i++)
		if(arr1[i]==1) cnt1++;
	for(int i=1;i<=n;i++)
		if(arr2[i]==1) cnt2++;
	if(cnt1>zh(n)){
		return false;
	}
	if(cnt2>n/2){
		return false;
	}
	return true;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		if(fun()==true){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：2)

### 题意
输入两个字符串，有操作：**交换当前字符与斜对角的字符**，询问是否存在方法使得第一个字符串全是 $0$。

### 思路
一道橙题，思路很好想。我们可以先把序列进行斜向交换，因为序列是交错的，所以新的序列是 $a_0,b_1,a_2,b_3,\dots,a_{n-1},b_n$。然后我们已知序列可以交换顺序，我们设字符串 $0$ 的个数为 $m$，所以当第一个字符串 $m$ 大于序列长度一半且第二个字符串 $m$ 大于长度一半时有解，否则无解。

注意：第一个 $m$ 大于长度向上取整，第二个 $m$ 向下取整。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define ll long long 

ll n;

std::string a,b;

int main()
{
	ll t;std::cin>>t;
	while(t--)
	{
		std::cin>>n>>a>>b;
		ll m1=0,m2=0;
		for(ll i=0;i<n;i++)
		{
			if(i%2==0)
			{
				if(a[i]=='0') m1++;
				if(b[i]=='0') m2++;
			}
			else
			{
				if(b[i]=='0') m1++;
				if(a[i]=='0') m2++;
			}
		}
		if(m1>=ceil((double)n/2)&&m2>=floor((double)n/2))
		{
			std::cout<<"yEs\n";
		}
		else
		{
			std::cout<<"nO\n";
		}
	}
	return 0;
}
```

---

## 作者：cjx_AK (赞：2)

题意：

给你两个字符串，可以把字符与斜对角的字符交换，问是否存在一种方法，使得第一个字符串全是 0。 

思路：

由于一个字符不能移到相邻的格子里去，不妨假设两个种类，第一种的代表元素是下标为 $1$ 的字符，第二种则是下标为 $2$。

第一种字符串能放下 $\lceil{\frac{n}{2}}\rceil$ 个 1，第二种则可放下 $\lfloor{\frac{n}{2}}\rfloor$ 个 1。

统计后进行判断即可。

code：

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
int T;
int n;
ll a[2000005];
string s;
signed main(){
	cin>>T;
	while(T--){
		int cnt=0;
		int cnt2=0;
		cin>>n;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='1'){
				if(i%2==0){
					cnt++;
				}else{
					cnt2++;
				}
			}
		}
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='1'){
				if(i%2==0)cnt2++;
				else cnt++;
			}
		}
		if(cnt>s.size()/2||cnt2>s.size()/2+s.size()%2){
			puts("NO");
		}else{
			puts("YES");
		}
	}
}
```

---

## 作者：abort (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF2092B)
# 题目分析
Lady Bug 每次操作可选择索引 $2 \leq i \leq n$，执行两种操作之一，即交换 $(a_i, b_{i-1})$ 或交换 $(b_i, a_{i-1})$，操作次数任意。
# 题解

从题面我们可以看出，$s_1$ 的奇数位不管怎么挪还是奇数位，偶数位不管怎么挪还是偶数位；$s_2$ 的偶数位不管怎么挪都是奇数位，奇数位不管怎么挪都是偶数位。所以，我们可以看出，我们只需要统计奇偶位置 $0$ 的个数就可以了。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

char s1[200010], s2[200010];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cin >> (s1 + 1) >> (s2 + 1);
        int cnt_ou = 0, cnt_ji = 0;
        for (int i = 1; i <= n; i++)
        {
            if (s1[i] == '0')
            {
                if (i % 2 == 1) cnt_ji++;
                else cnt_ou++;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (s2[i] == '0')
            {
                if (i % 2 == 1) cnt_ou++;
                else cnt_ji++;
            }
        }
        if (cnt_ou >= n / 2 && cnt_ji >= n - n / 2)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}

---

## 作者：yulinOvO (赞：1)

### 题意：
每个输入数据输入两个字符串，可以交换当前字符与斜对角的字符，请问可不可以任意操作后使得第一个字符串全是 $0$。

### 思路：
这样的操作实际上在 $a_i$ 的数可以通过 2 次操作到 $a_{i-2}$，$a_{i+2}$，再次重复可以到 $a_{i-4}$，$a_{i+4}$。当然也可以到 $b_{i-1}$，$b_{i+1}$，即每个对角线上的字符可以任意重新排列，只要保持它们原有的奇偶位置属性不变。

### Code:
```cpp
#include <iostream>
using namespace std;
int T,n,c,d;
string s;
int main()
{
    cin>>T;
    while(T--&&cin>>n>>s)
    {
        c=d=0;
        for(int i=0;i<s.size();i++) if(s[i]=='1') i%2?d++:c++;
        cin>>s;
        for(int i=0;i<s.size();i++) if(s[i]=='1') i%2?c++:d++;
        cout<<(c<=n/2&&d<=(n+1)/2?"YES\n":"NO\n");
    }
}
```

---

## 作者：potata111 (赞：1)

## [_CF2092B_](https://www.luogu.com.cn/problem/CF2092B) Lady Bug

### 题目大意

给你两个字符串 $Str1$ 和 $Str2$，都长 $n$，且由且仅由 $0$ 或 $1$ 组成。  
对于这两个字符串，你可以这样**交换**：
$$
  swap(Str1_i, Str2_{i-1}),\ i \in (1, n];
$$
$$
  swap(Str1_i, Str2_{i+1}),\ i \in [1, n);
$$

~~这种符号语言太抽象了……~~  
也即：将 $Str1_i$ 与其对角线上的某个 $Str2_j$ 交换 $(\ j = i \pm 1$ 且 $i, j \in [1, n]\ )$。

交换规则如上：那么**能否经过若干次交换**，使得 $Str1$ 全为 $0$。

---

### 输入

首先是数据组数 $t\ (t ≤ 10^4)$。每组数据由三行组成：  

第一行为 $Str1$ 与 $Str2$ 的**长度** $n\ (n ≤ 2\ \times 10^5)$；  
第二、三行分别为一个字符串：$Str1$ 与 $Str2$。

### 输出

每组数据的输出独占一行。

如果可以通过交换使得 $Str1$ 全为 $0$，输出 **Yes**。  
若不能，则输出 **No**。



---

### 解析

观察题意，可以发现交换的**次数没有上限**。  
所以我们的交换其实没有题中所述的那么自由。

确切地，所有元素的交换都**集中**在两条路径上，且两条路径上的元素对交换操作都具有**封闭性**。

即无论怎么交换某个元素，它都**只能**在某条路径上移动（如下）：

![](https://cdn.luogu.com.cn/upload/image_hosting/yo680i63.png)

并且不难想到：对于任一字符与它所在路径上的目标点，必然存在一种交换方式，使其在有限的步骤内使其到达目标点。即**_在一条路径上，点的排列是任意的_**。

答案呼之欲出：**分别考虑**两条路径。  
如果两条路径上 $0$ 的**个数都足够**，则输出 **Yes**，否则输出 **No**。


---

### 代码

细节把控好就可以 Accepted 咯。


```cpp
#include<iostream>
#include<string>

using namespace std;

int q;
int n;
string tar, tmp;

void solve()
{
	cin >> n;
	cin >> tar >> tmp;
	tar = ' ' + tar;
	tmp = ' ' + tmp;
	
	int cnt1 = 0, cnt2 = 0;
	
	for (int i = 1; i <= n; i++)
	{
		int target = (tar[i] == '1');
		int temp = (tmp[i] == '1');
		
		if (i & 1)
			cnt1 += target,
			cnt2 += temp;
		else
			cnt1 += temp,
			cnt2 += target;
	}
	
	int div = n / 2;
	if (n & 1)
		cout << ((cnt1 > div || cnt2 > n - div) ? ("No") : ("Yes"));
	else
		cout << ((cnt1 > div || cnt2 > div) ? ("No") : ("Yes"));
	cout << '\n';
}

int main()
{
	cin >> q;
	
	while (q--)
		solve();
		
	return 0;
}
```

---

## 作者：K_J_M (赞：1)

# CF2092B Lady Bug

## 题目描述

当 Dasha Purova 刚越过法国边境时，反派 Markaron 绑架了她并将她关押在其城堡下的监狱中。幸运的是，神奇的 Lady Bug 得知 Dasha 的消息后立即赶往 Markaron 的城堡营救她。然而，她需要破解一个复杂密码才能进入。

该密码由两个长度为 $n$ 的比特字符串 $a$ 和 $b$ 组成。Lady Bug 在一次操作中可以选择任意索引 $2 \leq i \leq n$ 并执行以下两种操作之一：

1. 交换 $(a_i$, $b_{i-1})$。
2. 交换 $(b_i$, $a_{i-1})$。

Lady Bug 可以进行任意次数的操作。若她能使第一个字符串 $a$ 仅由 $0$ 组成，则视为密码破解成功。请帮助她判断是否能成功营救 Dasha。
## Solution
将这两个操作翻译一下就是可以走蛇形路径上的数随意交换。即 $a$ 第一个和 $b$ 第二个和 $a$ 第三个等等可以随便交换。$b$ 第一个和 $a$ 第二个和 $b$ 第三个等等可以随便交换。容易知道我们可以将其中一条路径上的所有 $0$ 交换到 $a$ 数组上面。那么我们只需要统计每一条路径上 $0$ 的个数能否覆盖所需地方即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int t,n;
string a,b;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>a>>b;
        a=" "+a,b=" "+b;
        int cnt=0,k=0;
        for(int i=1;i<=n;++i){
            if(i%2==0){
                cnt+=(b[i]=='0');
            }else{
                cnt+=(a[i]=='0');
                ++k;
            }
        }
        if(cnt<k){
            puts("NO");
        }else{
            cnt=0,k=0;
            for(int i=1;i<=n;++i){
                if(i%2==0){
                    cnt+=(a[i]=='0');
                    ++k;
                }else{
                    cnt+=(b[i]=='0');
                }
            }
            if(cnt<k){
                puts("NO");
            }else{
                puts("YES");
            }
        }
    }
    return 0;
}
```

---

## 作者：mc_xiexie (赞：1)

### 解法

根据题意我们可以将两个序列变一下，因为只能斜着交换，则得出新序列 $a_0,b_1,\ldots,b_{n-1},a_n$ 和 $b_0,a_1,\ldots,a_{n-1},b_n$。

在这两个新序列的数可以随意排列，所以只要第一个新序列中的 $0$ 大于 $ \left\lceil \dfrac{n}{2}\right\rceil $ 个并且第二个新序列中的 $0$ 大于 $ \left\lfloor \dfrac{n}{2}\right\rfloor $ 个就成立。

### 代码


```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string a,b;
		cin>>a>>b;
		int sum1=0,sum2=0;
		for(int i=0;i<n;i++){
			if(i%2==0){
				if(a[i]=='0'){
					sum1++;
				}
				if(b[i]=='0'){
					sum2++;
				} 
			}
			else{
				if(a[i]=='0'){
					sum2++;
				}
				if(b[i]=='0'){
					sum1++;
				} 
			}
		}
		if(sum1>=ceil((double)n/2) && sum2>=floor((double)n/2)){
			cout<<"Yes\n";
		}
		else{
			cout<<"No\n";
		}
	}
} 
```

[AC记录](https://codeforces.com/contest/2092/submission/313317053)

---

## 作者：zhangli828 (赞：0)

## 题目大意
给定两个字符串 $a,b$ 你可以把 $a_i,b_{i-1}$ 或者 $a_{i-1},b_i$ 交换，问最后 $a$ 能否全为 $0$。
## 题目思路
要做这道题我们可以发现一个有趣的事，一个在 $a_i$ 的数可以到 $a_{i-2},a_{i+2}$ 等地方去，也可以到 $b_{i-1},b_{i+1}$ 等地方去，所以我们发现一个字符可以在任意一个满足以上条件的地方。所以我们可以进一步得知每一个对角线的地方形成的链可以把其字符按任意方式排列。
## 题目解法
所以我们根据以上思路可以把两条对角线形成的链的 $0$ 的个数求出来，再看是否能填满 $a$ 即可。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
const int kMaxN = 2e5 + 10;
 
int t, n, cnt1, cnt2;
char c;
 
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; cnt1 = cnt2 = 0) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> c, (c == '0') && ((i % 2) ? (cnt1++) : (cnt2++));  // 统计数量
    }
    for (int i = 1; i <= n; i++) {
      cin >> c, (c == '0') && ((i % 2) ? (cnt2++) : (cnt1++));  // 统计数量
    }
    cout << (cnt2 >= n / 2 && cnt1 >= (n + 1) / 2 ? "YES\n" : "NO\n");  // 判断是否能够填满 a
  }
  return 0;
}
```

---

## 作者：LVFUyang1 (赞：0)

题意：给你两个 $\texttt{01}$ 串，每次可以交换 $a[i],b[i-1]$ 或 $a[i],b[i+1]$。求能不能使得第一个串全是 $0$。


显然，第一个串的奇数位置和第二个串的偶数位置是联通的，偶数位置和第二个串的奇数位置是联通的。这两个联通块里$1$的数量不能超过其一半。


那这题就非常简单了。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
char a[N],b[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		int cnt=0,cnt1=0;
		for(int i=1;i<=n;i++){
			if(i%2==0){
				if(a[i]=='1')
					cnt1++;
				if(b[i]=='1')
					cnt++;
			}
			if(i%2!=0){
				if(a[i]=='1')
					cnt++;
				if(b[i]=='1')
					cnt1++;
			}
		}
		if(cnt>n/2||cnt1>(n+1)/2)
			cout<<"No"<<'\n';
		else
			cout<<"Yes"<<'\n';
	}
	return 0;
}



```

---

