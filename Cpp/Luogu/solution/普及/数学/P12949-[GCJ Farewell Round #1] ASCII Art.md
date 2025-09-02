# [GCJ Farewell Round #1] ASCII Art

## 题目描述

**Cody-Jamal** 听说了生成式人工智能创作艺术的事情。他对这种新的艺术创作方式感到兴奋，但同时也担心人类创作的艺术会被取代。他认为一个很好的折衷方案是利用计算机来创作人类无法完成的艺术作品。

由于 **Cody-Jamal** 刚刚开始接触计算机生成艺术，他决定从简单的开始。他想创建一个巨大的字符串，以双重重复的方式展示英文字母，以表现字母的普遍性和永恒性。

**Cody-Jamal** 编写了以下程序：

```
for i = 1 to 1e100:
    for letter = A to Z:
        print letter i times
```

这里 $1 \mathrm{e} 100$ 表示整数 $10^{100}$。例如：

* 当 $i=1$ 时，程序会输出 $\mathrm{ABCDEFGHIJKLMNOPQRSTUVWXYZ}$（26 个字母各出现 1 次）
* 当 $i=2$ 时，程序会输出 $\mathrm{AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ}$（26 个字母各出现 2 次）
* 当 $i=3$ 时，程序会输出 $\mathrm{AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ}$（26 个字母各出现 3 次）

显然，**Cody-Jamal** 的这个程序需要运行极其漫长的时间。你能在不实际运行程序的情况下，直接计算出程序输出的第 $\mathbf{N}$ 个字符是什么吗？

## 说明/提示

程序输出的字符序列开始部分为：
- $i=1$: A(1), B(2), C(3), D(4), E(5),..., Z(26)
- $i=2$: A(27-28), B(29-30), C(31-32),..., Z(78)
- ...

因此：
- 第 5 个字符是 E
- 第 31 个字符是 C（位于第二轮的 C 部分）

**数据范围**

- $1 \leq \mathbf{T} \leq 100$

**测试集 1（9 分，可见判定）**
- $1 \leq \mathbf{N} \leq 10^{6}$

**测试集 2（20 分，可见判定）**
- $1 \leq \mathbf{N} \leq 10^{12}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5
31```

### 输出

```
Case #1: E
Case #2: C```

# 题解

## 作者：4041nofoundGeoge (赞：2)

## 题目简述

CJ 运行了一个程序会一直往下生成字符：

ABCD $\cdots$ ZAABBCCDD $\cdots$ ZZAAABBB $\cdots$

即为每个字母输出 $i$ 遍。

## 思路

### 方法一

模拟，时间复杂度 $O(TN)$。~~想实现需要给 kkk 加钱买评测机。~~

### 方法二

我们要求 $N$ 是在字符输出几遍时出现的，于是不难发现：
$$
\sum^{k}_{i=1}26\times i \le N\le \sum^{k+1}_{i=1}26\times i\\
26\sum^{k}_{i=1}i\le N\le 26\sum^{k+1}_{i=1}i\\
\frac{26\times(1+k)\times k}{2}\le N\le \frac{26\times(1+k+1)\times {k+1}}{2}
$$

所以我们需要求 $k$ 小于 $N$ 最大值，即 $\dfrac{26\times(1+k)\times k}{2}\le N$。

~~很~~不难算出时间复杂度为 $O(T\sqrt{N})$。貌似还会有些超时。

### 方法三

考虑方法二的优化：倍增 $+$ 二分，压缩求 $k$ 的时间，时间复杂度为 $O(T\log N)$。

### 方法四

求出 $\dfrac{26\times(1+k)\times k}{2}\le N$ 的解集，然后用 $O(T)$ 的时间复杂度完成代码，但有丢失精度的风险。

## 代码

给出**方法三**的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        long long n;
        cin>>n;
        cout<<"Case #"<<q-t<<": ";
        long long i=0;
        long long right=1;
        long long last=right;
        while(26*right*(right-1)/2<n){
            last=right;
            right*=2;
        }
        long long left=last;
        while(left<=right){
            long long mid=(left+right)/2;
            long long total=26*mid*(mid+1)/2;
            if(total>=n) {
                i=mid;
                right=mid-1;
            } 
            else {
                left=mid+1;
            }
        }
            long long prev=26*(i-1)*i/2;
            long long now=(n-prev-1)/i;
            cout<<(char)('A'+now)<<"\n";
    }
    return 0;
}
```

---

## 作者：All_Wrong_Answer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12949)

## 思路：

看到题解区有找规律的和倍增结合二分的，那我太菜了就不得不拿出暴力做法了。

看数据范围发现 $T\le100$ 且 $n \le 10^{12}$，那直接 $O(Tn)$ 显然不可取，但是注意到第 $i$ 组的字母总数为 $26i$，这样显然比暴力模拟快很多，而且求得在某一组后显然能 $O(1)$ 确定答案，所以考虑不枚举 $n$，而枚举组数 $k$，则能满足 $\frac{k(26+26k)}{2} \le n$，当 $n$ 取最大值 $10^{12}$ 时且 $k$ 为整数时，解得 $k \le 277349$，那么我们的复杂度就变成了 $O(Tk)$，其中 $k\le277349$，极限下 $T \times k=27734900$，显然可以通过此题了。

然后实现稍微有一点点细节，可以看代码。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
const long long ma=1000000000000;
long long zh[300005];
int main(){
	zh[0]=0; 
	long long s=0,px;
	for(int i=1;i<=1145141919;i++){
		s+=i*26;
		zh[i]=s;
		if(s>ma){
			px=i;
			break;
		}
	}
	long long t,x;
	cin>>t;
	for(int i=1;i<=t;i++){
		
		cin>>x;
		x--;
		int u;
		for(int j=1;j<=px;j++){
			if(zh[j]>=x){
				u=j;
				break;
			}
		}
		cout<<"Case #"<<i<<": ";
		if(zh[u]==x) cout<<"A\n"; 
		else if(u==1) cout<<char(x+'A')<<endl;
		else cout<<char(((x-zh[u-1])/u)+'A')<<endl;
	}
	return 0; 
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

数学老师开心的笑啦！

我们设 $x$ 表示已经进行了 $x$ 轮，那么，可得不等式：$\frac{26(x+1)x}{2} \le n$。
化简得：$x^2+x-\frac{n}{13} \le 0$。

解出最大的整数 $x$（用公式法），再让 $n$ 减去之前 $x$ 轮所消耗的步数得到本轮的步数，再计算即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    int T, n, c = 0;
    cin >> T;
    while (T-- && cin >> n && printf("Case #%d: ", ++c)) {
        int t = n / 13, deta = 4 * t + 1;
        int x = (sqrt(deta) - 1) / 2;
        n -= 26 * (x + 1) * x / 2;
        if (n == 0) cout << 'Z' << '\n'; // 这里要特判一下
        else cout << char(ceil(1.0 * n / (x + 1)) + 'A' - 1) << '\n';
    }
    return 0;
}
```

（小小声：这有黄？）

---

## 作者：Yi_chen123 (赞：1)

## 思路

一道有难度的数论题，我们可以将其分成两步去解答。

## 第一步：判断第 $N$ 个字符位于第几次循环中

解决这个任务，我们需要计算第 $i$ 次循环后一共出现了多少字符。\
我们根据题意可知，第 $i$ 次循环会出现 $26i$ 个字符，那么到第 $i$ 次循环结束，总共会有 $\sum_{k = 1}^{i} 26k$ 个字符出现。我们暂时记作 $f(i)$。\
根据求和运算符的性质，我们发现：

$$
\sum_{k = 1}^{i} 26k = 26 \sum_{i}^{k = 1}k
$$

再对其套用等差数列求和公式得：

$$
26 \sum_{i}^{k = 1}k = 26 \times \dfrac{i(i + 1)}{2}
$$

所以我们得到 $O(1)$ 时间复杂度求 $f(i)$ 的代码：

```cpp
inline int f(int x){
	return 26LL * x * (x + 1LL) / 2; 
} 
```

那么我们可以列出如下关于 $x$ 的不等式：

$$
f(x - 1) \le N \le f(x)
$$

暴力计算是 $O(\sqrt N)$ 的，由于 $T \le 100$，所以时限给的还是差了点意思。所以我们可以考虑继续优化求解时间。

我们可以先将答案进行倍增，求出答案大致的左、右区间：

```cpp
int l = 1LL, r = 2LL; //l 为左区间，r 为右区间
while(f(r - 1) < n) l = r, r <<= 1; //循环将左右区间乘上 2，直到 f(r - 1) >= n
```

此时不难证明 $f(l) \le N \le f(r)$。可是我们不能保证 $r - l = 1$，因此我们需要对左右区间进行二分答案。

```cpp
int cnt = 0; //cnt 为 x 的唯一整数解
while(l <= r){
    int mid = (l + r) >> 1;
    if(f(mid) >= n) r = mid - 1, cnt = mid;
    else l = mid + 1; 
} 
```

二分结束后，原方程的唯一整数解就是 $x = cnt$，而且单次求解的时间复杂度只有 $O(\log n)$！至此第一步画上了圆满的句号。

### 第二步：求出第 $N$ 个字符的具体内容

艰难~~渡劫~~之后，问题就迎刃而解了。\
我们不难发现，第 $cnt$ 次循环是从第 $start = f(cnt) + 1$ 个字符开始的，而这个循环在运行到字符总数为 $N$ 时，这一层循环只输出了 $N - start$ 个字符。如果我们假设 $\tt A$ 是 $0$ 号字母，那么第 $N$ 个字符就是 $\lfloor \dfrac{n - start}{cnt} \rfloor$ 号字母！

代码实现如下：

```cpp
int start = f(cnt - 1) + 1; //此层循环起始下标
int ans = (n - start) / cnt;
cout << static_cast<char> (ans + 'A') << endl;
```

## 代码

```cpp
#include<bits/stdc++.h>
#define test(a) cout << #a << " = " << a << endl
#define int long long 
using namespace std;

inline int f(int x){
	return 26LL * x * (x + 1LL) / 2; 
} 
signed main(){
	int T; cin >> T;
    int Q = T;
	while(T--){
        cout << "Case #" << Q - T << ": "; //这里不知道为什么要这样子进行测试编号输出，如果用单纯的记数器好像是过不了的
		int n; cin >> n; 
		int l = 1LL, r = 2LL, cnt = 0;
		while(f(r - 1) < n) l = r, r <<= 1;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(f(mid) >= n) r = mid - 1, cnt = mid;
			else l = mid + 1; 
		} 
		int start = f(cnt - 1) + 1;
        int ans = (n - start) / cnt;
        cout << static_cast<char> (ans + 'A') << endl;
	} 
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12949)

# 题目分析

可以看成一道找规律题目。

设由一个 $i$ 生成的完整字符串为一组。不难发现，前 $k$ 组的字符总数为 $13k(k+1)$。证明：

字符总数等于
$$26(1+2+ \dots +k)$$
$$=\frac{1}{2}k(k+1) \times 26$$
$$=13k(k+1)$$

因此首先确定大范围，即第 $n$ 个字符在哪一组。设在第 $x$ 组，则
$$x=\lfloor \frac{1}{2}(-1+\sqrt{1+\frac{4n}{13}})\rfloor+1$$

其实就是解不等式：
$$13x(x+1) \le n$$

的解集再加 $1$。

注意精度，建议使用 ```double```，注意特判 $n$ 正好为一组末尾的情况。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		double n,k0;
		cin>>n;
		k0=(-1+sqrt(1+4*n/13))/2;
		long long k=floor(k0);
		long long last=n-13*(k+1)*k;
		if(last==0){
			cout<<"Z"<<endl;
			continue;
		}
		long long h=ceil((double)last/(double)(k+1));
		cout<<(char)('A'+h-1)<<endl; 
	}
	return 0;
}
```

---

