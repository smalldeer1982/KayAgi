# [ABC387E] Digit Sum Divisible 2

## 题目描述

对于正整数 $n$，定义其数位和为 $n$ 在十进制表示下各位数字之和。例如 $2025$ 的数位和是 $2 + 0 + 2 + 5 = 9$。  
当正整数 $n$ 能被其数位和整除时，称 $n$ 为**良整数**。例如 $2025$ 能被其数位和 $9$ 整除，因此是良整数。  
对于满足 $a$ 和 $a+1$ 均为良整数的正整数对 $(a, a+1)$，称其为**良整数双子**。例如 $(2024, 2025)$ 是良整数双子。

给定正整数 $N$，请找到一个满足 $N \leq a$ 且 $a + 1 \leq 2N$ 的良整数双子 $(a, a + 1)$。若不存在这样的双子，请报告这一事实。

## 说明/提示

### 约束条件

- $N$ 是满足 $1 \leq N < 10^{100000}$ 的整数

### 样例解释 1

$(8, 9)$ 是满足条件的良整数双子。其他符合条件的解包括 $(5, 6)$、$(6, 7)$、$(7, 8)$ 和 $(9, 10)$。

### 样例解释 2

不存在满足条件的良整数双子。

### 样例解释 3

$(2024, 2025)$ 是满足条件的良整数双子。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5```

### 输出

```
8```

## 样例 #2

### 输入

```
21```

### 输出

```
-1```

## 样例 #3

### 输入

```
1234```

### 输出

```
2024```

## 样例 #4

### 输入

```
1234567890123456789012345678901234567890```

### 输出

```
1548651852734633803438094164372911259190```

# 题解

## 作者：xxgirlxx (赞：14)

## 题外话
~~关注@[xxgirlxx](https://www.luogu.com.cn/user/1059074) 谢谢喵，关注@[xxboyxx](https://www.luogu.com.cn/user/473256) 谢谢喵~~

~~你怎么知道我赛时死调 D 题花了 80 分钟~~

~~你怎么知道我赛后 E 题和 F 题总用时等于 D 题用时~~

~~你怎么知道我认为的 CDEF 难度排序非常抽象（E 小于 F 小于 C 小于 D）~~
## 题目大意
给你一个数 $n$，请你在 $[n,n \times 2)$ 这个区间中找到一个整数 $x$，使得 $x$ 和 $x+1$ 能分别被它们的数位数字之和整除。
## 题目思路
先别管区间，先看什么样的 $x$ 才能使 $x$ 和 $x+1$ 能分别被它们的数位数字之和整除呢？这个时候需要用到一个小学（~~忘记是不是奥数了~~）的知识：$2,3,8,9$ 所能整除的数的特征。

首先我们要清楚我们所能控制的量一定是数位数字之和，因为 $n$ 的范围过大，不好控制（$n \le 10^{100000}$）。

然后我们会发现如果数位数字之和太大合理的情况就会非常少，所以我们就先看 $10$ 及以内的数，即 $1,2,3,4,5,6,7,8,9,10$，我们仔细判断一下就会发现实际上有可能出现合法情况的数位数字之和仅有 $2$ 和 $8$。原因是它们的下一个数字的数位数字之和一定是 $3$ 和 $9$，$3$ 和 $9$ 能整除的数的特征非常优秀，就是**数位数字之和**为 $3$ 和 $9$ 的倍数。也就是说，只要满足 $x$ 的数位数字之和是 $2$ 或 $8$ 且能被整除，下一个数字 $x+1$ 就一定是合法的。

然后我们就可以找到两种合理的构造方式：

第一种是最后一位为 $0$，其余位数之和为 $2$。

第二种是最后三位为 $0$，其余位数之和为 $8$。

然后我们再来考虑怎么将其放入到 $[n,n \times 2)$ 这个区间中。

注意到数位数字之和为 $2$ 只会有两种情况：分成两个 $1$ 或一个 $2$。注意到一个 $2$ 的局限性过大，仅有当第一位为 $1$ 时可以使用，所以考虑拆成两个 $1$，然后会发现这种构造方式一定可以使首位为 $6,7,8,9$ 的数拥有合法的数字，因为首位是 $6,7,8,9$，所以 $n$ 的两倍一定是首位为 $1$ 且第二位大于 $2$ 的，所以我们可以直接使用类似于 $10\cdots 010$ 的方式构造出正确的数字，但是注意特判一下仅有一位的情况，因为如果仅有一位，那么 $n\times 2$ 就只有两位，即使压到最小也放不下（因为最小的情况是 $110$）。

那首位为 $1,2,3,4,5$ 的数字怎么办呢？我们就考虑使用 $8$ 来求解，但是因为 $8$ 要求后三位都为 $0$，所以这种方法仅能对于 $\ge8000$ 的数字进行构造。但是因为首位 $\ge 6$ 的数都被 $2$ 的构造方法筛掉了，所以剩下的数中最小的是 $10000$，可以放下两位，所以我们考虑将 $8$ 拆开放置在前两位，为了 $\ge n$，我们先令第一位就是 $n$ 的第一位，然后就可以求出第二位的数字，然后判断一下 $n$ 的第二位数字，如果 $n$ 的第二位数字大于等于我们算出来的应填的数字，那么我们就将第一位数字加一，第二位数字减一。

有关将第一位数字加一，第二位数字减一的正确性证明如下：

因为如果我们刚好跟 $n$ 的第一位相同的情况下 $n$ 都比我们大，那么我们在第一位数字加一，第二位数字减一是一定能够保证处在 $[n,n \times 2)$ 这个区间中的，因为第一位数字比 $n$ 的第一位数字大 $1$，所以满足 $\ge n$，然后我们是加了 $90\cdots 0$，但是 $n\times 2$ 是加了一个 $n-1$，且只有在 $n-1$ 是 $9\cdots 9$ 的情况下会跟我们构造的数加的数的位数一样，其余情况都会比我们构造的数加的数要多一位。但不管什么情况，$n\times 2$ 加的数都比我们构造的数加的要多，且本身我们构造的数就比 $n$ 还要小，所以满足 $<n\times 2$。

最后所剩下的数都必定是 $<8000$ 的了，非常简单，直接在  $[n,n \times 2)$ 这个区间中暴力枚举判断即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,num,sum,cnt,res;
int main(){
	cin>>s;
	if(s[0]-'0'>5){
		if(s.size()>1)for(int i=0;i<=s.size();i++)cout<<((i==0||i==s.size()-1)?1:0);
		else cout<<s[0]-'0';
	}
	else if(s.size()>4||(s.size()==4&&s[0]-'0'>=8)){
		cout<<s[0]-'0'+(s[1]-'0'>=8-s[0]+'0'-1)<<8-s[0]+'0'-(s[1]-'0'>=8-s[0]+'0'-1);
		for(int i=2;i<s.size();i++)cout<<0;
	}
	else{
		for(int i=0;i<s.size();i++)n*=10,n+=s[i]-'0';
		for(int i=n;i<n*2;i++){
			num=i,sum=0,res=i+1,cnt=0;
			while(num)sum+=num%10,num/=10;
			while(res)cnt+=res%10,res/=10;
			if(i%sum==0&&(i+1)%cnt==0)cout<<i,exit(0);
		}
		cout<<-1;
	}
	return 0;
}
```

---

## 作者：Walrus (赞：7)

人类智慧题。

---

首先小学奥数告诉我们：

> 一个数当且仅当能被 $3$ 整除时各个数位和是 $3$ 的倍数。

> 一个数当且仅当能被 $4$ 整除时最后两位数字构成的数能被 $4$ 整除。

当然 $2$ 和 $5$ 的也比较显然（看末位即可）。

我们要充分发扬人类智慧，这个题字符串长度 $N\leq 10^5$，**首先考虑贪心**。因为上述结论中**对数字中间的 $0$** 是不会为这个数能被 $2,3,4,5$ 整除造成任何贡献的，即我们只需要考虑**第一位和后两位填什么即可**。

这类大数据范围题先打表，大概结论是这样的：

以下几种数是合法的。

- 形如 $1\times 10^k+10$。
- 形如 $2 \times 10^k$。
- 形如 $3 \times 10^k+32$。
- 形如 $4 \times 10^k+40$。
- 形如 $8\times 10^k$。

你发现对于这几种情况是覆盖了所有区间的（因为答案可以在 $N\sim2 \times N$ 之间任意构造），所以直接判断数位于哪个区间就可以了。

注意，你会发现样例中有无解的情况出现，这是因为 $N$ 过小导致中间无法补 $0$ 而对于第 $1,3,4$ 条结论可能是矛盾的，于是考虑**当 $N$ 较小的时候暴力，反之套结论即可。**

---

## 作者：chaqjs (赞：4)

# [AtCoder Beginner Contest 387 E - Digit Sum Divisible 2](https://atcoder.jp/contests/abc387/tasks/abc387_e)题解

## 题目描述

正整数 $n$ 的位数和定义为 $n$ 写成十进制时的位数和。例如，$2025$ 的位数和是 $2 + 0 + 2 + 5 = 9$。  

如果一个正整数 $n$ 能被它的数位和整除，那么这个正整数 $n$ 就叫做**好整数**。例如，$2025$ 是一个好整数，因为它能被其数位和 $9$ 整除。
  
如果 $a$ 和 $a+1$ 都是好整数，那么一对正整数 $(a, a+1)$ 称为**孪生好整数**。例如，$(2024, 2025)$ 就是一对孪生好整数。

给你一个正整数 $N$。请找出一对孪生好整数 $(a, a + 1)$，使得 $N \leq a$ 和 $a + 1 \leq 2N$。如果不存在这样的一对，输出 $-1$。

## 思路

对于小数据，我们进行暴力。而对于大数据，我们只需要构造一个有规律的、比较特殊的数。

首先我们知道：

- 一个数能被 $8$ 整除当且仅当它的后三位能被 $8$ 整除。
  
- 一个数能被 $9$ 整除当且仅当它的数位之和能被 $9$ 整除。
  

由此， 我们进行构造。

令一个好整数 $a$ 的数位之和为 $8$，且个位不为 $9$。

根据上面的两个性质和好整数的定义，我们可以确定：

$a$ 为 $8$ 的倍数，$a+1$ 为 $9$ 的倍数且是一个好整数。

即 $(a,a+1)$ 是一对孪生好整数。

归纳一下，使 $(a,a+1)$ 是一对孪生好整数的条件有：

- $a$ 的是 $8$ 的倍数。
  
- $a$ 的数位之和是 $8$。
  
- $n \le a < 2n$。
  

那么，什么样的 $a$ 既是特殊的又满足上面的条件呢？仔细思考，我们发现当 $a$ 的后三位全部是 $0$ 时，既特殊又满足条件。

接下来我们开始分类讨论。

先考虑特殊情况。若 $n$ 除了第一位之外全是 $0$，即 $n = \overline{x00\dots00}$。显然，在构造 $a$ 时，我们可以让 $a$ 的第一位仍为 $x$，第二位为 $8-x$。代码写为 `cout << x << 8 - x, zero_out(len - 2);`。其中 `zero_out` 是输出多少个 $0$。当然，这是建立在 $x \ne 9$ 的基础上的。而当 $x=9$ 时，我们可以让 $a = \overline{1700\dots00}$。代码为 `cout << 17, zero_out(len - 1);`。

若 $n$ 只是一个普通的数呢？我们发现只需要考虑它的前两位即可，我们设为 $x$ 和 $y$。当 $x=9$ 时，与上面的一样。`cout << 17, zero_out(len - 1);`。当 $x=8$ 时，`cout << 107, zero_out(len - 2);`。当 $x \ne 1$ 时，`cout << x + 1 << 8 - x - 1, zero_out(len - 2);`。当 $x=1$ 且 $y \ge 5$ 时，`cout << x + 1 << 8 - x - 1, zero_out(len - 2);`。若以上条件都不成立，`cout << 17 , zero_out(len - 2);`。

至此，我们已经全部分类讨论完了，这是完整代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 1e5 + 5;

string n;// 由于 n 非常大，我们只能用字符串读入 

// 数据小时判断是否为好整数 
bool is_good(int x){
	int sum = 0, p = x;
	while (p) sum += p % 10, p /= 10;
	return x % sum == 0;
}

// 输出 0 
void zero_out(int num){
	for (int i = 1; i <= num; i++) cout << 0;
}

int main(){
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;
	
	int len = n.size();
	
	// 小数据暴力 
	if (len <= 6){
		int now_n = 0;
		for (int i = 0; i < len; i++)
			now_n = now_n * 10 + n[i] - '0';
		for (int i = now_n; i < 2 * now_n; i++){
			if (is_good(i) && is_good(i + 1)){
				cout << i;
				return 0;
			}
		}
		cout << -1;
		return 0;
	}
	
	/*                        ________
	考虑 n 的特殊情况，即 n = x00...00 */ 
	bool zero = 0;
	for (int i = len - 1; i >= 0; i--)
		if (n[i] == '0'){
			zero = 1;
			break;
		}
	
	// 分类讨论 
	if (!zero){
		int x = n[0] - '0';
		if (x != 9)
			cout << x << 8 - x, zero_out(len - 2);
		else
			cout << 17, zero_out(len - 1);
	}
	else {
		int x = n[0] - '0';
		int y = n[1] - '0';
		if (x == 9)
			cout << 17, zero_out(len - 1);
		else if (x == 8)
			cout << 107, zero_out(len - 2);
		else if (x != 1 || (x == 1 && y >= 5))
			cout << x + 1 << 8 - x - 1, zero_out(len - 2);
		else
			cout << 17, zero_out(len - 2);
	}

	return 0;
}

```

---

## 作者：Dream_poetry (赞：2)

### 题意：
设 $f(x)$ 表示 $x$ 各个数位之和，请输出一种在 $n$ 到 $2n$ 之间满足 $x$ 能被 $f(x)$  整除且 $x+1$ 能被 $f(x+1)$ 整除的方案。

你只需要输出 $x$ 即可，且满足 $n \le x < 2n$。

### 思路：

考虑暴力，可以发现在 $10^6$ 之内轻松跑过。

然后我们经过仔细思考之后决定构造。

首先一个小学结论：若一个数各个数位之和是 $9$ 的倍数，则这个数可以被 $9$ 整除。

我们不考虑复杂情况，仅考虑各个数位之和恰好为 $9$ 的情况。

我们再考虑若一个数是 $8$ 的倍数它所要满足的显然条件。

显然最好想的就是这个数是 $1000$ 的倍数。

那为了美观，我们不妨构造这样一种情况：

让 $x$ 最高位和千位数目之和为 $8$，其余数位都为 $0$。

此时 $x+1$ 恰好也满足我们所要的条件。

直接输出 $x$ 即可。

不过请注意 $x$ 最高位的选择，我们应该分类讨论 $n$ 最高位为 $1,8,9$ 和其他值的情况。

若 $n$ 最高值为 $8$ 或 $9$ 时，为了保证构造出我们上述需要的 $x$，又因为此时必然会出现进位，我们不妨构造 ```1000……0007000``` 这种情况，也能符合条件，不过一定注意进位。

若 $n$ 最高值为 $1$ 时，可能会出现 ```1000……0001``` 这种情况，若还使用原构造，则会导致所求 $x$ 大于 $2n$，不可取。

不过我们发现如果此时 $n$ 在千位以上还存在其他非零数，我们原构造依然成立，所以再次进行分类讨论。

如果还是无法使用原构造，我们直接启用备用构造 ```11000……00024```，显然此时依然是对的。

再来思考一下无解的情况，如果 $n$ 的位数高于 $4$，显然可以通过上述构造找出答案，所以无解情况必然被拘束在了一个较小范围内，直接暴力来跑出检验即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
int len;
int n;

inline int check(int x){
	int w=x;
	int cnt=0;
	while (w){
		cnt+=w%10;
		w/=10;
	}
	return x%cnt==0;
}
inline void solve(){
	for (int i=0;i<len;i++){
		n=n*10+(int)(s[i]-'0');	
	}
	for (int i=n;i<2*n;i++){
		if (check(i) && check(i+1)){
			cout<<i;
			return;
		}
	}
	cout<<"-1";
	return;
}

signed main(){
	cin>>s;
	len=s.size();
	if (len<=7){
		solve();
		return 0;
	}
	if (s[0]=='1'){
		int op=0;
		for (int i=1;i<len-4;i++){
			if (s[i]!='0'){
				op=1;
				break;
			}
		}
		if (!op){
			cout<<11;
			for (int i=1;i<len-3;i++){
				cout<<0;
			}
			cout<<24;
			return 0;	
		}
		
	}
	int flag=0;
	for (int i=1;i<len;i++){
		if (s[i]!='0'){
			flag=1;
			break;
		}
	}
	int b=(int)(s[0]-'0')+flag;
	if (b>=9){
		cout<<"10";
		b=1;		
	}
	else{
		cout<<b;	
	} 
	for (int i=1;i<len-4;i++){
		cout<<'0';
	}
	cout<<8-b<<"000";
	return 0;
}
```

---

## 作者：gavinliu266 (赞：2)

# 思路
记一个数 $x$ 数位之和为 $f(x)$。

首先，我们需要知道这些内容。

- 能被 $3$ 整除的数的特点：通过证明 $x \equiv f(x) \pmod{3}$，得到 $3 \mid x \Leftrightarrow 3 \mid f(x)$。
  
  证明：设 $x = \overline{x_{n}x_{n-1} \cdots x_0}=x_n10^n+x_{n-1}10^{n-1}+ \cdots +x_010^0$。因为 $10^m \equiv 1 \pmod{3}(m \in \mathbf{N})$，所以 $x \equiv x_n+x_{n-1}+ \cdots +x_0\pmod{3} \equiv f(x)\pmod{3}$。证毕。

- 同理，能被 $9$ 整除的数的特点：$9 \mid x \Leftrightarrow 9 \mid f(x)$。

- $1000$ 是 $8$ 的倍数，自然也是 $4$ 的倍数。

下面思路：

1. 先写一个打表程序，对于 $N < 1000$ 时直接查表。为什么？这个等所有构造结束后再解释。

2. 接下来，设 $k=\lfloor \lg N \rfloor$，这里，因为 $N < 1000$ 已经处理过了，所以 $k \ge 3$。如果 $N = 10^k$，则构造 $a=10^k+11$，此时 $3 \mid a$，$4 \mid (a+1)$。

3. 如果 $10^k < N < 2 \times 10^k$，则构造 $a=2 \times 10^k$，此时 $2 \mid a$，$3 \mid (a+1)$。

4. 如果 $2 \times 10^k \le N < 3 \times 10^k$，则构造 $a=3 \times 10^k +320$，此时 $8 \mid a$，$9 \mid (a+1)$。

5. 如果 $3 \times 10^k \le N < 4 \times 10^k$，则构造 $a=4 \times 10^k +40$，此时也是 $8 \mid a$，$9 \mid (a+1)$。

6. 如果 $4 \times 10^k \le N < 6 \times 10^k$，则构造 $a=6 \times 10^k +200$，此时也是 $8 \mid a$，$9 \mid (a+1)$。

7. 剩下来的情况，类比情况 2，构造 $a=10^{k+1}+11$，此时 $3 \mid a$，$4 \mid (a+1)$。

这就是整个思路了。你会发现它构造的 $a$ 后面加的数不超过 $1000$，所以把小于 $1000$ 的数单独处理是非常有用的。另外，我们为所有大于等于 $1000$ 的构造了一组解，所以当 $N \ge 1000$ 时一定有解。

怎么构造出来的？自然是先打表找规律，再证明啊。

时间复杂度：$O(\log N)$。

# 代码实现
打表代码。

为了节省篇幅，略微压行。
```cpp
#include <bits/stdc++.h>
int get_sum(int n) { int ret = 0; while(n) { ret += n % 10, n /= 10; }  return ret; }
bool bk[100005];
int main() {
    for(int i = 1; i <= 100000; ++i) if(i % get_sum(i) == 0) bk[i] = 1;
    for(int i = 1; i < 100000; ++i) if(bk[i] && bk[i + 1]) printf("%d, ", i);
}
```

AC 代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[100005];
int n;
int db[105] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 80, 110, 111, 132, 152, 200, 209, 224, 399, 407, 440, 480, 510, 511, 512, 629, 644, 735, 800, 803, 935, 999, 1010, 1011, 1014, 1015, 1016, 1100};
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    if(n <= 3) {  // case 1
        int num = 0;
        for(int i = 1; i <= n; ++i) num = num * 10 + s[i] - '0';
        for(int i = 1; i <= 100; ++i)
            if(db[i] >= num) {
                if(db[i] >= num * 2) printf("-1\n");
                else printf("%d\n", db[i]);
                return 0;
            }
    }
    if(s[1] == '1') {
        bool fl = false;
        for(int i = 2; i <= n; ++i)
            if(s[i] != '0') {
                fl = true;
                break;
            }
        if(!fl) {  // case 2
            putchar('1');
            for(int i = 2; i <= n - 2; ++i) putchar('0');
            putchar('1'), putchar('1');
        } else {  // case 3
            putchar('2');
            for(int i = 1; i < n; ++i) putchar('0');
        }
        return 0;
    }
    if(s[1] == '2') {  // case 4
        putchar('3');
        for(int i = 1; i <= n - 4; ++i) putchar('0');
        printf("320");
    } else if(s[1] == '3') {  // case 5
        putchar('4');
        for(int i = 1; i <= n - 3; ++i) putchar('0');
        printf("40");
    } else if(s[1] == '4' || s[1] == '5') {  // case 6
        putchar('6');
        for(int i = 1; i <= n - 4; ++i) putchar('0');
        printf("200");
    } else {  // case 7
        putchar('1');
        for(int i = 2; i <= n - 1; ++i) putchar('0');
        putchar('1'), putchar('1');
    }
}
```

---

## 作者：_smart_stupid_ (赞：1)

这应该是一篇小学生都看得懂的题解。

当 $n$ 为一位数时，$n$ 本身就是一个合法的答案。接下来讨论 $n$ 为两位数的情况。

接下来为了方便讨论，将 $x$ 表示为 $n$ 的位数，$y$ 表示为 $n$ 最高位上的数字。即 $y \times 10^{x-1} \le n$ 且 $x$ 最大的同时让 $y$ 尽量大。

两位数答案只有 $20$ 和 $80$ 满足条件。

## 当 $y$ 为 $1$ 时

发现：$2 \times 10^{x-1}$ 是一个合法的好整数，$2 \times 10^{x-1} + 1$ 也是一个合法的好整数（各位数的和为 $3$，一定为 $3$ 的倍数）。

此时，满足 $n > 10^{x-1}$ 的 $n$（乘 $2$ 后大于 $2 \times 10^{x-1}$）可以使用上述方法得到构造。

对于 $n = 10 ^ {x-1}$，可以将原来构造最高位的 $2$ 减去一，挪到其他一个为 $0$ 的位置，当 $x \ge 3$ 时，可以使用这种构造，否则，无解（没有大于等于 $10$ 且小于等于 $19$ 的两位数答案）

## 当 $y$ 为 $2$ 时

当 $x = 2$ 时，只有 $n = 20$ 才有答案，为 $20$，否则，无解。

当 $x = 3$ 时，$399$ 为一个满足所有 $n$ 的特殊解。

当 $x \ge 4$ 时，$3 \times 10^{x-1} + 33$ 为好整数，减去一后，位数之和为 $8$，由于为 $4$ 位数，后三位为 $032$，满足 $8$ 的倍数的特征。

## 当 $y$ 为 $3$ 时

当 $x = 2$ 时，无合法解。

当 $x \ge 3$ 时，$44 \times 10^{n-2}$ 一定为好整数。其数位和为 $8$，后三位为 $440$，$400$，$000$，都符合 $8$ 的倍数的特征。加一后，各位数的和为 $9$。

## 当 $y$ 为 $4$ 时

对于 $n > 4 \times 10^{x-1}$，$8 \times 10^{x-1}$ 为一个合法答案（本身是 $8$ 的倍数，加一后变为 $9$ 的倍数）

否则，直接套用 $y = 3$ 时的构造。

## 当 $y \in {5,6,7}$ 时

可以直接套用 $y = 4$ 的构造得到答案。

## 当 $y \in {8,9}$ 时

可以从 $y = 1$ 的构造得到灵感，$11 \times 10 ^ {n - 1}$ 一定满足答案。由于 $x \ge 2$，上述构造一定至少为三位数，满足条件。

讨论完所有的情况，只有 $2$ 位数存在无解情况，其他情况都可以给出对应构造。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
string n;
int l;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	l = n.length();
	if (l == 1) {
		cout << n << '\n';
		return 0;
	}
	if (n[0] == '1') {
		bool flag = 0;
		for (int i = 1; i < l; i++) flag |= n[i] > '0';
		if (flag) { // 大于10..000
			cout << "2";
			for (int i = 1; i < l; i++) cout << '0';
			cout << '\n';
			return 0;
		}
		if (l > 2) { // 等于10..000
			cout << "11";
			for (int i = 1; i + 1 < l; i++) cout << '0'; //110, 111
			cout << '\n';
			return 0;
		}
	}
	if (n[0] == '2') {
		if (l > 3) {
			// 3032, 3033
			cout << "3";
			for (int i = 1; i + 2 < l; i++) cout << '0';
			cout << "32\n";
			return 0;
		}
		else if (l == 3) {
			cout << "399\n";
			return 0;
		}
		else if (n == "20") {
			cout << "20\n";
			return 0;
		}
	}
	if (n[0] == '3') {
		if (l > 2) {
			cout << "44";
			for (int i = 1; i + 1 < l; i++) cout << '0';
			return 0;
		}
	}
	if (n[0] == '4') {
		bool flag = 0;
		for (int i = 1; i < l; i++) flag |= (n[i] != '0');
		if (flag) { // 大于40..000
			cout << "8";
			for (int i = 1; i < l; i++) cout << '0';
			cout << '\n';
			return 0;
		}
		// 等于40..000
		if (l > 2) {
			cout << "44";
			for (int i = 1; i + 1 < l; i++) cout << '0';
			return 0;
		}
	}
	if (n[0] == '5' || n[0] == '6' || n[0] == '7') {
		cout << "8";
		for (int i = 1; i < l; i++) cout << '0';
		cout << '\n';
		return 0;
	}
	if (n[0] == '8' || n[0] == '9') {
		cout << "11";
		for (int i = 1; i < l; i++) cout << "0";
		cout << "\n";
		return 0;
	}
	cout << "-1\n";
	return 0;
}
```

---

## 作者：Ybll_ (赞：1)

# 题意：
给你一个 $n$，找出任意一个满足以下条件的数 $a$：

1. $a$ 的各位之和为 $a$ 的因数；
2. $a+1$ 的各位之和为 $a+1$ 的因数；
3. $n\le a<a+1<2n$。

你只需要输出任意一个满足条件的正整数。
# 思路：
一道构造题，如果 $n$ 比较小，那就暴力，否则~~考虑乱搞~~我们先找出能被各位之和是 $8$ 的数，然后在后面疯狂加 $0$，就可以得到 $8$ 的倍数，此时再给这个数 $+1$，就得到了一个 $9$ 的倍数。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f(string s)
{
	int x=0;
	for(int i=0;i<s.size();i++)
	{
		x=x*10+s[i]-'0';
	}
	return x;
}
int sum(int x)
{
	int n=0;
	do
	{
		n+=x%10;
	}
	while(x/=10);
	return n;
}
signed main()
{
	string s;
	cin>>s;
	if(s.size()<9)
	{
		int n=f(s);
		for(int i=n;i<2*n;i++)
		{
			if(i%sum(i)==0&&(i+1)%sum(1+i)==0)
			{
				cout<<i;
				return 0;
			}
		}
		cout<<-1;
		return 0; 
	}
	int x=(s[0]-'0')*10+s[1]-'0';
	if(x<17)cout<<17;
	else if(x<26)cout<<26;
	else if(x<35)cout<<35;
	else if(x<44)cout<<44;
	else if(x<53)cout<<53;
	else if(x<62)cout<<62;
	else if(x<71)cout<<71;
	else cout<<107;
	for(int i=2;i<s.size();i++)
	{
		cout<<0;
	}
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

可以尝试通过构造解决此题。

考虑到一个数能被 $9$ 整除是各个数位上和为 $9$ 的倍数，一个数整除 $8$ 只需要末三位均为 $0$ 即可。因此大致的方向就是去构造 $x,8 - x,0,0,\cdots,0,0,0$ 的一个数来满足条件。  
**【为什么选择 $8$：相较于 $4$，$8$ 的拆分比较多，因此更容易满足条件。】**

再来考虑 $[N,2N]$ 这个范围的限制。设 $N$ 的最高位 $p$，则：

- 当 $p \ge 7$ 时，构造 $107\underbrace{00\cdots000}_{n-2}$ 总能符合条件。

- 当 $2 \le p \le 7$ 以及 $17,18,19$ 开头的数，构造 $p + 1,7 - p,\underbrace{0,0,\cdots,0,0,0}_{n - 2}$ 总能符合条件。

- $p=1$ 的其余情况，构造 $17\underbrace{00\cdots000}_{n-2}$ 总能符合条件。

- 当然，$N$ 较小的时候难以构造出上述条件，直接跑暴力即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n;char s[MAX]; 
int calc (int x)
{
	int res = 0;
	while (x) res += x % 10,x /= 10;
	return res;
}
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	scanf ("%s",s + 1);n = strlen (s + 1);
	if (n <= 6)
	{
		int num = 0;
		for (int i = 1;i <= n;++i) num = num * 10 + s[i] - '0';
		for (int i = num;i < 2 * num;++i)
			if (i % calc (i) == 0 && (i + 1) % calc (i + 1) == 0) {printf ("%d\n",i);return 0;} 
		puts ("-1"); 
		return 0;
	}
	if (s[1] >= '7')
	{
		printf ("107");
		for (int i = 1;i <= n - 2;++i) printf ("0");
		puts ("");
	}
	else if (s[1] >= '2' || (s[1] == '1' && s[2] >= '7'))
	{
		int dig = s[1] - '0' + 1;
		printf ("%d%d",dig,8 - dig);
		for (int i = 1;i <= n - 2;++i) printf ("0");
		puts ("");
	}
	else 
	{
		printf ("17");
		for (int i = 1;i <= n - 2;++i) printf ("0");
		puts ("");
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：sjh0626 (赞：1)

## 题意概括
正整数 $n$ 的位数和定义为 $n$ 写成十进制时的位数和。例如，$2025$ 的位数和是 $2 + 0 + 2 + 5 = 9$。  
如果一个正整数 $n$ 能被它的数位和整除，那么这个正整数 $n$ 就叫做好整数。例如，$2025$ 是一个好整数，因为它能被其数位和 $9$ 整除。  

如果 $a$ 和 $a+1$ 都是好整数，那么一对正整数 $(a, a+1)$ 就叫做孪生好整数。例如，$(2024, 2025)$ 就是孪生好整数。

给你一个正整数 $N$。找出一对孪生好整数 $(a, a + 1)$，使得 $N \leq a$ 和 $a + 1 \leq 2 \times N$，如果不存在这样的一对，请输出 `-1`。
## 思路分析
经典的分类讨论。

首先 $N \le 100000$ 就不用说了，直接暴力。

接下来我们要知道一个事实，我们为了让 $N$ 和 $N+1$ 都是好整数，就得使 $N$ 的数位和为 $8$，$N+1$ 的数位和为 $9$。

$8 = 1+7 = 2+6 = 3+5 = 4+4 = 5+3 = 6+2 = 7+1 = 8+0 = 1+0+7$。
我们可以根据 $N$ 的前两位来判断答案的前两位，但是，有一个很特殊，如果 $N$ 的前两位 $\le 80$ 时，我们就只能选择 $107$。

总结：还是建议看代码理解。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
using namespace std;
class FastIO{
	public:
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	FastIO &operator>>(int &x){
		x=read();
		return *this;
	}
};
FastIO qin;
bool good(int x){
	int sum=0;
	int y=x;
	while(y){
		sum+=y%10,y/=10;
	}
	return x%sum==0;
}
string s,ans;
int x;
int main(){
	cin>>s;
	if(s.size()<=6){
		x=stoi(s);
		for(int i=x;i<2*x;i++){
			if(good(i)&&good(i+1)){
				cout<<i;
				sjh0626s code;
			}
		}
		cout<<-1;
		sjh0626s code;
	}
	x=(s[0]-'0')*10+s[1]-'0';//前两位
	if(x<=16)ans="17";
	else if(x<=25)ans="26";
	else if(x<=34)ans="35";
	else if(x<=43)ans="44";
	else if(x<=52)ans="53"; 
	else if(x<=61)ans="62";
	else if(x<=70)ans="71";
	else if(x<=79)ans="80";
	else ans="107";
	cout<<ans;
	for(int i=1;i<=s.size()-2;i++){
		cout<<"0";
	}
	sjh0626s code;
}
```

---

## 作者：zsq9 (赞：1)

[AC 记录](https://www.luogu.com.cn/record/197831321)

## 题目大意

如果正整数 $n$ 可被其数字和整除，则称其为**好整数**。

如果 $a$ 和 $a+1$ 都是好整数，则称一对正整数 $(a, a+1)$ 为**孪生好整数**。

找出一对孪生好整数 $(a, a + 1)$，使得 $N \leq a$ 和 $a + 1 \leq 2N$。如果不存在这样的配对，则报告该事实。

## 思路

我们先打表如图黄色的是孪生好整数，红色的是好整数，
![](https://cdn.luogu.com.cn/upload/image_hosting/g3cji53n.png)

可以发现规律首先数字和为 **$9$ 或 $3$** 的定为好整数，末尾有 **三个 $0$** 的也定为好整数，这下就好做了，首先 $10^6$ 以下就直接暴力不管它，但是在 $10^6$ 以上就定有孪生好整数，因为末尾有 **三个 $0$** 的也定为好整数，所以直接再看它是 $2 \sim 3$ 还是 $8 \sim 9$ 组成孪生好整数，按照规律来打就行了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string n;
int sum(int x){
	int ans=0;
	while(x){
		ans+=x%10;
		x/=10;
	}
	return ans;
}
int main(){
	cin>>n;
	if(n.size()<=6){
		long long N=0;
		for(int i=0;i<n.size();i++)	N=10*N+n[i]-48;
		for(int i=N;i<2*N;i++)
			if(i%sum(i)==0&&(i+1)%sum(i+1)==0)
			{
				cout<<i;
				return 0;
			}
		cout<<-1;
		return 0;
	}
	if(n[0]=='1'){
		long long t=1;
		for(int i=1;i<n.size();i++)
			if(n[i]!='0')
			{
				t=0;
				break;
			}
		if(t){
			cout<<11;
			for(int i=0;i<n.size()-2;i++)	cout<<0;
			return 0;
		}
	}
	if(n[0]<='1'){
		cout<<2;
		for(int i=1;i<=n.size()-1;i++)	cout<<0;
	}
	else if(n[0]=='2'&&n[1]<'6'){
		cout<<26;
		for(int i=1;i<=n.size()-2;i++)	cout<<0;
	}
	else if(n[0]<'4'||(n[0]=='4'&&n[1]<'4')){
		cout<<44;
		for(int i=1;i<=n.size()-2;i++)	cout<<0;
	}
	else if(n[0]<'8'){
		cout<<8;
		for(int i=1;i<=n.size()-1;i++)	cout<<0;
	}
	else{
		cout<<11;
		for(int i=1;i<=n.size()-1;i++)	cout<<0;
	}
	return 0;
}

```

---

## 作者：HasNoName (赞：0)

### 思路
感觉是一道比较巧的构造题。

因为一个数如果它的后三位都为 $0$ 则它可以被 $8$ 整除。

而如果一个数的各位数字之和的可以被 $9$ 整除，则这个数可以被 $9$ 整除。

考虑当一个数字的位数小于等于 $6$ 时，暴力枚举，一个数字的位数大于 $6$ 时，枚举其前三位，如果一个数的前三位个位数字之和为 $8$ 的倍数，则它加一一定是 $9$ 的倍数，合法。

因为一个三位数它的首位 $k$ 小于等于 $7$ 则可以构造出它的最高位加一，个位为 $8-k$，十位为 $0$。如果 $k\ge 8$ 则可以构造十位为 $16-k$，个位为 $0$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int get(int x)//各位数字之和
{
  int sum=0;
  while(x)
  {
    sum+=x%10;
    x/=10;
  }
  return sum;
}
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin>>s;
  if(s.size()<=5)
  {
    int n=0;
    for(int i=0;i<s.size();i++)
      n=n*10+s[i]-'0';
    for(int i=n;i<2*n;i++)
      if(i%get(i)==0&&(i+1)%get(i+1)==0)
      {
        cout<<i<<'\n';
        return 0;
      }
    cout<<"-1\n";
    return 0;
  }
  int n=(s[0]-'0')*10+s[1]-'0';
  for(int i=n+1;i<2*n;i++)
  {
    if(get(i)==8)
    {
      cout<<i;
      for(int i=1;i<=s.size()-2;i++)
        cout<<0;
      cout<<'\n';
      return 0;
    }
  }
  return 0;
}
```

---

## 作者：player_1_Z (赞：0)

### 先来理解题目
[atcoder 原题](https://atcoder.jp/contests/abc387/tasks/abc387_e)

### 思路
我们发现直接暴力会超时，同时发现如果一个数的各位之和为 $8$，那么只需要末三位为 $0$ 就可以了，而且可以保证这个数符合题目要求。但是需要这个数大于五位，所以如果 $n$ 小于 $10^7$ 就直接暴力找，否则运用上述规律。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int c(int x){//判断是否符合要求 
	int sx=0,y=x;
	while(y){
		sx+=y%10;
		y/=10;
	}
	return (x%sx==0)?1:0;
}
int main(){
	cin>>s;
	int l=s.size();
	if(l<7){//数据够小，可以直接暴力 
		for(int i=0;i<l;i++) n=n*10+(s[i]-'0');
		for(int i=n;i<2*n;i++){
			if(c(i)&&c(i+1)){
				cout<<i;//找到了 
				return 0;
			}
		}
		cout<<-1;exit(0);//没有 
	}
	int n=(s[0]-'0')*10+(s[1]-'0');//依照样例推出的方法 
	if(n<=16) cout<<17;
	else if(n<=25) cout<<26;
	else if(n<=34) cout<<35;
	else if(n<=43) cout<<44;
	else if(n<=52) cout<<53;
	else if(n<=61) cout<<62;
	else cout<<107;
	for(int i=3;i<=l;i++) cout<<0;
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

这样一道 E，居然只值 $2097$，还没 ABC358F 难？

我居然赛时切掉了这道而不是比它简单的 F，匪夷所思。

## Solution AT_abc387_e

### Idea

直接暴力枚举是不行的，我们需要找规律。

我们先把前 $10000$ 的表打出来。

打表程序很好写，按照题意模拟即可。

打完表，我们会发现：$20$、$200$、$2000$ 都是能够符合要求并输出为答案的数。

原因为何？注意到 $2\times 10^x$（其中 $x$ 为正整数）的数位和为 $2$，显然是 $2\times 10^x$ 的因数，所以 $2\times 10^x$ 是好数；$2\times 10^x+1$ 的数位和为 $3$，因为数位和为 $3$ 的数一定有因数 $3$，所以 $2\times 10^x+1$ 是好数。

接着再发挥一下注意力：$80$、$800$、$8000$ 都是可以输出为答案的数。

原因为何？注意到 $8\times 10^x$（其中 $x$ 为正整数）的数位和为 $8$，显然是 $8\times 10^x$ 的因数，所以 $8\times 10^x$ 是好数；$8\times 10^x+1$ 的数位和为 $9$，因为数位和为 $9$ 的数一定有因数 $9$，所以 $8\times 10^x+1$ 是好数。

那么我们看到现在我们已经有两类可以输出为答案的数，它们分别是：$2\times 10^x$ 和 $8\times 10^x$（其中 $x$ 为正整数）。

我们考虑 $2\times 10^x$ 和 $8\times 10^x$（其中 $x$ 为正整数）作为答案时，$n$（题目中输入的数）可以为多少。

对于 $2\times 10^x$，显然有 $2n>2\times 10^x$ 且 $n\le 2\times 10^x$，则 $n\in (1\times 10^x,2\times 10^x]$。

对于 $8\times 10^x$ 同理有 $n\in (4\times 10^x,8\times 10^x]$。

但是这样只能覆盖少量区间，我们还需要对于其他区间进行覆盖。

打到 $100000$，发现 $440$、$4400$、$44000$ 都是符合条件的数。

证明：$44\times 10^x$（其中 $x$ 为正整数）数位和为 $8$，但是 $44$ 不是 $8$ 的倍数而只是 $4$ 的倍数。但是 $10$ 中含有一个因子 $2$，所以 $44\times 10^x$ 就是 $8$ 的倍数；$44\times 10^x+1$ 数位和为 $9$，数位和是 $9$ 的数可以被 $9$ 整除，所以 $44\times 10^x+1$ 是好数。所以 $44\times 10^x$ 可以作为答案输出。对于这个答案，$n$ 的范围是 $(22\times 10^x,44\times 10^x]$。

发现 $110$、$1100$、$11000$ 都是符合要求的数，证明类似：$11\times 10^x$ 为好数，因为数位和为 $2$，而 $11\times 10^x+1$ 数位和为 $3$，可以被 $3$ 整除。对于这个数，$n$ 的范围是 $(5.5\times 10^x,11\times 10^x]$。

现在我们还有前两位为 $20$ 的数，为 $21$ 的数，以及 $2.2\times 10^x$ 没有覆盖。注意到 $3320$、$33200$ 都是符合条件的数，原因是 $332\times 10^x$（$x$ 为正整数）数位和为 $8$，$332$ 是 $4$ 的倍数，再乘 $10$ 显然就是 $8$ 的倍数了。至于 $332\times 10^x+1$，数位和为 $9$，与先前证明类似。对于这个数，$n$ 的范围为 $(166\times 10^x,332\times 10^x]$。

整理一下，设 $n$ 的前两位为 $t$，总位数为 $x$，为了降低代码难度，我们按照以下格式输出：

- $x\le 3$：暴力枚举，然后输出。
- $t=10$：输出 $1.1\times 10^{x-1}$。
- $t\in [11,19]$：输出 $2\times 10^{x-1}$。
- $t\in [20,30]$：输出 $3.32\times 10^{x-1}$。
- $t\in [30,43]$：输出 $4.4\times 10^{x-1}$。
- $t\in [44,79]$：输出 $8\times 10^{x-1}$。
- $t\in [80,99]$：输出 $1.1\times 10^x$。

然后就做完了。

### Code

```
#include <bits/stdc++.h>
using namespace std;
string s;
int n;
int ans[55] = {0,1,
               2,
               3,
               4,
               5,
               6,
               7,
               8,
               9,
               20,
               80,
               110,
               111,
               132,
               152,
               200,
               209,
               224,
               399,
               407,
               440,
               480,
               510,
               511,
               512,
               629,
               644,
               735,
               800,
               803
               ,935, 999};
int main()
{
    cin >> s;
    n = s.length();
    if(n<=3){
        int x=0;
        for(int i=0;i<n;i++){
            x=x*10+(s[i]-'0');
        }
        for(int i=x;i<2*x;i++){
            for(int j=1;j<=36;j++){
                if(i==ans[j]){
                    printf("%d",i);
                    return 0;
                }
            }
        }
        printf("-1");
        return 0;
    }
    bool f=1;
    for(int i=1;i<n;i++){
        if(s[i]!='0'){
            f=0;
            break;
        }
    }
    if(s[0]=='1'&&f){
        s[1]='1';
        cout<<s;
        return 0;
    }
    int x=(s[0]-'0')*10+(s[1]-'0');
    if(10<=x&&x<=19){
        printf("20");
        for(int i=1;i<=n-2;i++)printf("0");
        return 0;
    }
    if(20<=x&&x<=30){
        printf("332");
        for(int i=1;i<=n-3;i++)printf("0");
        return 0;
    }
    if(30<=x&&x<=43){
        printf("44");
        for(int i=1;i<=n-2;i++)printf("0");
        return 0;
    }
    if(44<=x&&x<=79){
        printf("80");
        for(int i=1;i<=n-2;i++)printf("0");
        return 0;
    }
    if(80<=x){
        printf("110");
        for(int i=1;i<=n-2;i++)printf("0");
        return 0;
    }
}
```

---

