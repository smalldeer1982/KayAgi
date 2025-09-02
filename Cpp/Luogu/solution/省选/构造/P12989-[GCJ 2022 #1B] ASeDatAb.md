# [GCJ 2022 #1B] ASeDatAb

## 题目描述

一个研究联盟花费三年时间寻找最佳数据库，但仍存在问题。该数据库以 8 位二进制字符串形式存储记录值。遗憾的是，他们实现记录值设置功能的方式存在缺陷。

数据库的每条记录都是一个 8 位二进制字符串，其位索引从左到右为 0 至 7。当收到将特定记录设置为新值 $V$ 的指令时，数据库并不会直接将其设为 $V$，而是执行以下操作：

1. 选择一个 0 到 7 之间的整数 $r$，并生成 $V$ 向右循环移动 $r$ 位后的值 $W$。即 $W$ 的第 $((i + r) \bmod 8)$ 位等于 $V$ 的第 $i$ 位。
2. 将记录的当前值 $X$ 更新为 $X$ 与 $W$ 的异或值（即新值的第 $i$ 位为 1 当且仅当 $X$ 和 $W$ 的第 $i$ 位不同）。
3. 最后向用户返回新值中 1 的位数。

幸运的是，无论初始值如何或数据库如何选择旋转值，总能通过不超过 300 次操作将记录值重置为全 0。请编写一个程序与数据库交互完成此任务。

### 交互协议

本题为交互题。

初始时，你的程序应读取一个整数 $\mathbf{T}$ 表示测试用例数量，随后处理 $\mathbf{T}$ 个测试用例。

每个测试用例开始时，数据库记录会被设为非 $00000000$ 的值。每个测试用例中，你的程序最多可进行 300 轮交互。

每轮交互流程：
1. 你输出一个 8 位二进制字符串作为操作值 $V$
2. 评测系统执行前述操作后，返回一个整数 $\mathbf{N_{i}}$ 表示更新后记录值中 1 的位数
   - 若 $\mathbf{N_{i}}=0$ 表示成功，应开始下一测试用例（或程序终止）
   - 若 $\mathbf{N_{i}}=-1$ 表示第 300 次操作仍未归零，测试失败（后续用例不再处理）
   - 若 $1 \leq \mathbf{N_{i}} \leq 8$ 可继续尝试

只有当所有测试用例均成功将记录值归零时，解答才被视为正确。

若检测到非法输出，评测系统将返回 -1 并终止。收到 -1 后需正常退出以避免资源错误判定。

## 说明/提示

可使用测试工具进行本地测试（需与代码并行运行）。工具说明详见其注释，注意该工具**并非**真实评测系统。

**数据范围**
- $1 \leq \mathbf{T} \leq 100$
- $-1 \leq \mathbf{N_{i}} \leq 8$

**测试集 1（25 分，可见判定）**
- 初始值为均匀随机生成的非全零 8 位二进制数
- 旋转值均为独立均匀随机选择

**测试集 2（15 分，可见判定）**
- 评测系统采用对抗策略（可动态调整初始值和旋转值）
- 保证初始值不为全零

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1

3

0```

### 输出

```

00110011

00011001```

# 题解

## 作者：liuzhenhao09 (赞：2)

很有意思的题目。

先考虑如果只有四位的话怎么去做，显然我们可以通过询问 $1000$ 来做到控制答案的奇偶性，不妨让结果（指目前 $1$ 的个数）为偶数，显然如果结果为 $0$ 或 $4$ 就已经做完了。

如果结果是 $2$ 的话，显然只有两种可能的情况，一种是两个 $1$ 是相邻的，例如 $1100$，要么就是两个 $1$ 分开，如 $1010$。

我们可以通过询问 $1010$ 来使第二种情况的结果变为 $0$ 或 $4$，同时如果目前是第一种情况，也不会改变什么。

而如果是第一种情况的话，询问 $1100$ 即可将其变为 $0$ 或 $4$ 或第二种情况，再问一遍 $1010$ 就做完了。 

回到原题，同样的，我们先将结果变为偶数。这个时候我们需要发现一个串 $10101010$。这个串的优势在于它只有两种变化的可能，信息量是很大的。不难发现再询问一个 $10101010$ 后即可算出目前的奇数位和偶数位各有几个 $1$。注意此时我们无法区分奇数位和偶数位。

我们肯定要去尽量使得奇数位和偶数位都分开用四位的方法去做。所以如果奇数位有奇数个 $1$（注意此时偶数位一定也有奇数个 $1$），直接询问 $11000000$ 即可使得奇数位和偶数位都有偶数个 $1$。

那么，类似地，比如对于奇数位来说，只有三种情况，全 $0$ 或全 $1$（这是同一种），两个 $1$ 相邻，两个 $1$ 分开。且询问 $10101010$ 的时候并不会改变情况。

如果奇数位和偶数位都是第一种情况，就做完了，非常容易将结果变成 $0$。

下文中，如果出现上一种情况，立刻终止判断。$(1)$ 代表第一种情况，$(2),(3)$ 同理。

首先，列举一下目前所有的情况：（奇偶位不区分）

$(1)+(2),(1)+(3),(2)+(2),(2)+(3),(3)+(3)$。

我们现在可以直接判断目前是哪种情况。

相当于一张图有六个点（还有一个是汇点），你也可以把汇点理解成 $(1)+(1)$，然后每个点有若干个策略，你需要给每个点定一个策略，每个策略是指向若干个点，最后你要让这张图变成一个 DAG，且每个点能到达终点。考虑倒着拓扑排序，即将目前状态归约到若干个已知可以到达汇点的点。（这段比较抽象）

如果目前是 $(3)+(3)$，则显然可以通过一步 $11001100$ 来完成。

如果目前是 $(1)+(3)$，我们问一步 $10001000$，可以归约到 $(3)+(3)$ 或者汇点 $(1)+(1)$。

如果目前是 $(2)+(2)$，我们参考之前四位的方法，问一步 $11110000$，可以归约到 $(1)+(1),(1)+(3),(3)+(3)$。

如果目前是 $(1)+(2)$，问一步 $10100000$，可以归约到 $(1)+(1),(1)+(3),(2)+(2)$。

如果目前是 $(2)+(3)$，现在只要没有自环就行，问一步 $11001100$，归约到 $(1)+(2)$。

然后就做完了，实现可能和这个不太一样，但是本质相同。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e18 + 7;
const int MOD = 998244353;
int qpow(int a,int b){
	int res = 1;
	for( ; b; b >>= 1){
		if(b & 1) res = (res * a) % MOD;
		a = (a * a) % MOD;
	}
	return res;
}
char buf[1<<21],*p1,*p2;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2) ? 0 : *p1++)
template <typename T>
inline void read(T& x){
    x = 0;
    int f = 1;
    char ch = gc();
    while(!isdigit(ch)){
        if(ch == '-') f = -1;
        ch = gc();
    }
    while(isdigit(ch)){
        x = (x << 1) + (x << 3) + ch - '0';
        ch = gc();
    }
    x *= f;
}
int T;
int pre = 0;
int query(string s){
	cout<<s<<endl;
	int x;
	cin>>x;
	pre = x;
	return x;
}
typedef pair<int,int> pii;
pii ask(){
	string t = "01010101";
	int x = pre;
	int y = query(t);
	if(!y) return {-1,-1};
	int z = 2 + (y - x) / 2;
	return {z,y - z};
}
bool check(pii oo){
	if(oo.first == -1 && oo.second == -1) return 1;
	if(oo.first == 0 && oo.second == 0) return 1;
	else if(oo.first == 4 && oo.second == 4){
		query("11111111");
		return 1;
	}
	else if(oo.first == 4 && oo.second == 0){
		query("10101010");
		pii res = ask();
		return check(res);
	}
	else if(oo.first == 0 && oo.second == 4){
		query("10101010");
		pii res = ask();
		return check(res);
	}
	return 0;
}
signed main(){
	cin>>T;
	while(T--){
		query("10000000");
		if(!pre) continue;
		if(pre & 1LL){
			query("10000000");
			if(!pre) continue;
		}
		pii res = ask();
		if(res.first & 1LL){
			query("11000000");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first + res.second == 6 || res.first + res.second == 2){
			query("10001000");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first == 2 && res.second == 2){
			query("11001100");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first + res.second == 2 || res.first + res.second == 6){
			query("10100000");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first == 2 && res.second == 2){
			query("11110000");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first == 2 && res.second == 2){
			query("11001100");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first + res.second == 2 || res.first + res.second == 6){
			query("10001000");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
		if(res.first == 2 && res.second == 2){
			query("11001100");
			if(!pre) continue;
		}
		res = ask();
		if(check(res)) continue;
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

神秘好题。讲一下官方题解做法。

我们希望有一个比较「万能」的输出序列 $P_3$，使得我们只要输出其一段前缀就可以将数归零。

长度为 $1$ 的时候，显然为 $P_0=\{\tt1\}$。

长度为 $2$ 的时候，考虑一下如何处理。

- 首先我们除去 $\tt 11$，即加入 $\tt 11$。
- 然后考虑 $\tt 10,01$ 要怎么办，那我们发现，上面的那个异或后仍然是 $\tt 10,01$。  
  如果我们这次加入 $\tt 10$，那么结果就会变成 $\tt 00$ 或 $\tt 11$。前面那个 $\tt 00$ 是我们想要的。
- 至于最后的那个 $\tt 11$，我们再加入一次 $11$ 不就好了吗？

故序列为 $P_1=\{\tt 11,10,11\}$。

考虑长度为 $4$，或者更大的 $2^k(k>1)$ 的时候要怎么办。

首先，如果存储的数的前 $2^{k-1}$ 和后 $2^{k-1}$ 位相同，那这是好的。由于循环移位对前后无影响，所以我们直接将 $P_{k-1}$ 的每个元素数位上复制一下即可。

那如果不是的话，我们可以先对前 $2^{k-1}$ 位异或一下 $P_{k-1}$ 的第一项，然后再做以上的事情，如果发现还是不行的话就继续异或 $P_{k-1}$ 的下一项，做以上操作，以此类推，最后总能让前 $2^{k-1}$ 位和后 $2^{k-1}$ 位相同，最后使得其变为 $2^k$ 个 $\tt 0$。

总操作次数是 $2^8-1=255<300$。

```cpp
#include<bits/stdc++.h>
#define N 105
#define ll long long
#define mod 
using namespace std;

vector<string>vec;

vector<string>gen(int dep)
{
    if(!dep) return {"1"};
    auto vec=gen(dep-1),v0=vec,v1=vec;
    for(auto &i:v0) i+=string(i.size(),'0');
    for(auto &i:v1) i+=i;
    vector<string>res=v1;
    for(auto &i:v0)
    {
        res.push_back(i);
        for(auto &j:v1) res.push_back(j);
    }
    return res;
}

void sol()
{
    for(auto i:vec)
    {
        cout<<i<<endl;
        int n;
        cin>>n;
        if(!n) return;
    }
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int t;
    cin>>t;
    vec=gen(3);
    while(t--) sol();
    return 0;
}
```

---

