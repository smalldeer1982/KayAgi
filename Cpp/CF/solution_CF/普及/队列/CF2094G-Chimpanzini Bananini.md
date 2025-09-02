# Chimpanzini Bananini

## 题目描述

Chimpanzini Bananini 正站在一场重大战斗的边缘——这场战斗注定会带来终结。

对于任意长度为 $m$ 的数组 $b$，我们定义该数组的"炫酷值"为 $\sum_{i=1}^m b_i \cdot i = b_1 \cdot 1 + b_2 \cdot 2 + b_3 \cdot 3 + \ldots + b_m \cdot m$。

Chimpanzini Bananini 给你一个空数组。你可以对它进行三种类型的操作：

1. 对数组进行循环移位。即数组 $[a_1, a_2, \ldots, a_n]$ 变为 $[a_n, a_1, a_2, \ldots, a_{n-1}]$。
2. 反转整个数组。即数组 $[a_1, a_2, \ldots, a_n]$ 变为 $[a_n, a_{n-1}, \ldots, a_1]$。
3. 在数组末尾追加一个元素。即数组 $[a_1, a_2, \ldots, a_n]$ 在追加 $k$ 后变为 $[a_1, a_2, \ldots, a_n, k]$。

每次操作后，你需要计算当前数组的炫酷值。

注意所有操作都是持久化的。这意味着每个操作都会修改数组，后续操作都应基于前一次操作后的数组状态进行。

## 说明/提示

数组前六次操作后的状态：
- $[1]$
- $[1, 2]$
- $[1, 2, 3]$
- $[3, 1, 2]$
- $[3, 1, 2, 4]$
- $[4, 2, 1, 3]$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1
13
3 1
3 2
3 3
1
3 4
2
3 5
1
3 6
2
3 7
2
1```

### 输出

```
1
5
14
11
27
23
48
38
74
73
122
102
88```

# 题解

## 作者：枫原万叶 (赞：3)

# CF2094G Chimpanzini Bananini 题解

## 分析

体面大概意思是操作一个空数组，可以进行一下三种操作：

1. 最后一个元素移到最前面。
2. 数组元素顺序翻转。
3. 在数组末尾添加一个元素。

每次操作后输出所有元素乘以其下标的和，这个操作次数最多 $ 2 \times 10^5 $ 次。

那么我们来看一下每一个操作应该怎么做：

- 操作一：直接计算新元素的数值，即 $ k \times (当前长度 + 1) $。
- 操作二：反转后，原位置 $ i $ 变为 $ n + 1 - i $。总和变为 $ suma \times (n + 1) - sum $，其中这里的 $ suma $ 是元素总和。
- 操作三：将最后一个元素移到最前面，其他元素右移。总和变化就是 $ sum = sum + suma - x \times n $（这里的 $x$ 是被移动的元素的值）。

这里我们转换一个思路，对于反转我们其实不需要整个数组反转，而是调整操作一和操作三的添加或者移动位置就可以了。

这里进行了一个数学转换和标记，直接把每次操作的时间复杂度简化至 $ O(1) $。

## 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int q;
		scanf("%d", &q);
		deque<int> dq;
		int rev = 0;
		ll sum = 0, suma = 0;
		int n = 0;
		while (q--) {
			int s;
			scanf("%d", &s);
			if (s == 3) {
				int k;
				scanf("%d", &k);
				if (rev) {
					dq.push_front(k);
				} else {
					dq.push_back(k);
				}
				sum += k * (n + 1LL);
				suma += k;
				n++;
			} else if (s == 1) {
				int l;
				if (rev) {
					l = dq.front();
				} else {
					l = dq.back();
				}
				sum += suma - l * (ll)n;
				if (rev) {
					dq.push_back(dq.front());
					dq.pop_front();
				} else {
					dq.push_front(dq.back());
					dq.pop_back();
				}
			} else if (s == 2) {
				rev ^= 1;
				sum = (n + 1LL) * suma - sum;
			}
			printf("%lld\n", sum);
		}
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：2)

设当前答案为 $ans$。

考虑每次操作后答案会受到什么影响。

对于操作一，修改后答案即为 $a_n+\sum_{i=1}^{n-1} a_i\times (i+1)=ans-(n-1)\times a_n+\sum_{i=1}^{n-1}a_i$（这里的 $a$ 为修改前的序列）。

对于操作二，修改后答案即为 $\sum_{i=1}^n a_i\times (n-i+1)=(n+1)\times \sum_{i=1}^n a_i-ans$。

对于操作三，修改后答案即为 $ans+(n+1)\times x$。

可以发现，我们需要维护的是序列的长度、第一个元素和最后一个元素以及所有元素的和。可以考虑维护一个数组 $b$，用指针 $l,r$ 代表其第一个元素及最后一个元素，通过指针的移动来反映操作的影响。注意不要让数组下标出现负数。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 6e5 + 5;
int a[N], b[N];
 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n = 0, s = 0, ans = 0, fan = 0, l = 3e5 + 1, r = 3e5 + 0;
		int q;
		cin >> q;
		while (q--) {
			int op, x;
			cin >> op;
			if (op == 1) {
				if (!fan)
					ans = ans - (n - 1) * a[r] + s - a[r];
				else
					ans = ans - (n - 1) * a[l] + s - a[l];
				if (!fan)
					a[--l] = a[r], r--;
				else
					a[++r] = a[l], l++;
			} else if (op == 2) {
				ans = s * (n + 1) - ans;
				fan = 1 - fan;
			} else {
				cin >> x;
				++n;
				ans += n * x;
				s += x;
				if (!fan)
					a[++r] = x;
				else
					a[--l] = x;
			}
			cout << ans << "\n";
		}
	}
}
```cpp

---

## 作者：Tomwsc (赞：1)

# CF2094G Chimpanzini Bananini 题解

## 思路

考虑在 $O(1)$ 的时间复杂度内完成每一次操作。同时，因为涉及翻转操作，所以考虑使用双端队列，因为该数据结构可以维护两边操作。此时，操作 $2$ 便变成了换成双端队列的另外一端操作。

设此时数组的答案为 $ans$，数组的个数为 $sz$，数组中数的和为 $num$。

- 对于操作 $1$，容易得到 $ans\leftarrow ans - \text{此时的最后一个元素}\times sz + num$。然后把此时的最后一个元素放进此时的队首，再执行 ```pop``` 操作即可。
- 对于操作 $2$，我们发现每个元素的位置变成了 $n - i +1$，所以 $ans=\sum_{i=1}^{sz}(n-i+1)\times a_i$，对比原答案：$ans=\sum_{i=1}^{sz}i\times a_i$。可以发现 $ans\leftarrow (sz+1)\times num-ans$。
- 对于操作 $3$，只需把新的数 $k$ 放进队列里，然后 $num\leftarrow num+k$，$sz\leftarrow sz+1$，$ans\leftarrow ans+k\times sz$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
#define regint register int
#define pb push_back
#define mp make_pair
#define PII pair<int , int>
using namespace std;
const int MAXN = 2e5 + 10;
int t , q;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> q;
		deque<int>Q;
		int num = 0 , ans = 0 , sz = 0;
		bool flag = false;
		while(q --) {
			int opt , k;
			cin >> opt;
			if(opt == 1) {
				if(flag) {
					Q.push_back(Q.front());
					ans = ans - Q.front() * sz + num;
					Q.pop_front();
				} else {
					Q.push_front(Q.back());
					ans = ans - Q.back() * sz + num;
					Q.pop_back();					
				}
			} else if(opt == 2) {
				ans = (sz + 1) * num - ans;
				flag ^= true;
			} else {
				cin >> k;
				if(!flag) {
					Q.push_back(k);
					sz ++;
					num += k;
					ans += k * sz;
				} else {
					Q.push_front(k);
					sz ++;
					num += k;
					ans += k * sz;
				}
			}
			cout << ans << '\n';
		}
	}
	return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意

给定一个数组 $a$，有三类操作：翻转、循环移位和在末尾插入。每次操作后求 $\sum_{i=0}^n a_i\cdot i$。

### 思路

乍一看可能要高级数据结构维护，但其实所有操作都可以 $O(1)$ 完成。

我们维护一个当前状态的答案 $ans$ 和所有数组元素之和 $sum$，每次操作时如下更新即可：

- 操作一，$ans\leftarrow \sum_{i=0}^{n-1}a_i-(n-1)\cdot a_n=ans+sum-a_n\cdot n$；
- 操作二，$ans\leftarrow n\cdot \sum_{i=0}^{n}a_i-ans=sum\cdot (n+1)-ans$；
- 操作三，$ans\leftarrow ans+(n+1)\cdot k;\ sum\leftarrow sum+k$。

当然这是对答案的维护。对于数组本身的维护，显然不能直接使用数组暴力修改，考虑使用队列。而由于有翻转操作的存在，队列两端都可以增添元素，因此我们可以请出 STL 的好工具，双端队列 deque。

deque 支持从头部和尾部增添或者删除元素，维护一个 bool 值表示当前处于正方向还是反方向，每次采用该方向的方式维护双端队列即可。

### 程序如下

```cpp
#include<cstdio>
#include<cstring>
#include<deque>
using namespace std;
int T,m;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&m);
		deque<int>q;
		bool inv=false;
		long long ans=0,sum=0;
		int n=0;
		while(m--){
			int op,x;
			scanf("%d",&op);
			if(op==1){
				int k;
				if(inv){
					k=q.front();
					q.pop_front();
					q.push_back(k);
				}
				else{
					k=q.back();
					q.pop_back();
					q.push_front(k);
				}
				ans=ans+sum-1ll*n*k;
			}
			else if(op==2){
				inv=!inv;
				ans=1ll*(n+1)*sum-ans;
			}
			else{
				scanf("%d",&x);
				if(inv)q.push_front(x);
				else q.push_back(x);
				ans+=1ll*++n*x;
				sum+=x;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

### THE END

![](https://cdn.luogu.com.cn/upload/image_hosting/snmmfntc.png)

---

## 作者：AK_400 (赞：0)

我们直接维护两个数组，$a$ 记录不翻转的，$b$ 记录翻转的，$ansa$ 为 $a$ 的权值，$ansb$ 为 $b$ 的权值,$sum$ 为已插入数的和，$sz$ 为已插入数的数量。

为了防止出现负数下标，又因为所有操作只对开头结尾有用，所以使用两个双端队列。

对于操作一，将 $a$ 的结尾删除（记为 $x$），在开头插入，并将其他元素的贡献加一，也就是 $ansa\gets ansa+sum-x\times sz$。

对 $b$ 是同理的，将 $b$ 的开头删除（记为 $x$），在结尾插入，并将其他元素的贡献减一，也就是 $ansa\gets ansa-sum+x\times sz$。

对于操作二，交换 $a$，$b$ 以及交换 $ansa$，$ansb$ 即可，注意 deque 的 swap 是 $O(1)$ 的。

对于操作三，将 $x$ 插到 $a$ 的结尾，并加上贡献，即 $ansa\gets ansa+x\times sz$。将 $x$ 插到 $b$ 的开头，将所有元素的贡献加一，即 $ansb\gets ansb+sum$。

答案就是 $ansa$。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int q;
deque<int>a,r;
int ansa,ansr,sum,sz;
void op1(){
    int x=a.back();
    ansr-=sum;
    ansa+=sum;
    ansr+=x*sz;
    ansa-=x*sz;
    a.pop_back();
    a.push_front(x);
    r.pop_front();
    r.push_back(x);
}
void op2(){
    a.swap(r);
    swap(ansa,ansr);
}
void op3(int x){
    ansr+=sum;
    r.push_front(x);
    a.push_back(x);
    sum+=x;
    sz++;
    ansa+=x*sz;
    ansr+=x;
}
void slv(){
    a.clear();
    r.clear();
    sum=sz=ansa=ansr=0;
    read(q);
    while(q--){
        int op;
        read(op);
        if(op==1)op1();
        else if(op==2)op2();
        else{
            int x;
            read(x);
            op3(x);
        }
        cout<<ansa<<endl;
    }
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

