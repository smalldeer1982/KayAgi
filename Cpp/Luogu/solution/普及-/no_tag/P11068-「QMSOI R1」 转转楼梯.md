# 「QMSOI R1」 转转楼梯

## 题目背景

题目描述就是最好的题目背景（）。

## 题目描述

同学们每天都要做操，而做操会经过转转楼梯。

转转楼梯有 $n+1$ 阶楼梯，对于第 $i(1\le i\le n+1)$ 阶转转楼梯，其有一个转转值 $a_i$ 且 $a_i\in\{0,1\}$，特别的，$a_{n+1}=0$。

对于一阶转转楼梯，如果其下一阶楼梯的转转值与之相同（即 $a_{i+1}=a_i$）那么我们可以直接走下去，耗费一秒。否则我们需要耗费一秒转一圈以改变目前这阶楼梯的转转值为 $1-a_i$。然后再耗费一秒走下去。

我们需要做 $k$ 天课间操。每天要从第 $1$ 阶楼梯走到第 $n+1$ 阶楼梯。

请求出这 $k$ 天同学们经过转转楼梯的总时间。

## 说明/提示

### 样例解释
第一天数列 $a=\{0,1,0\}$，走三步，转两圈，时间为 $5$。

第二天数列 $a=\{1,0,0\}$，走三步，转一圈，时间为 $4$。

### 数据范围

**本题使用 subtask 进行捆绑测试**，每个 subtask 的具体分值如下：
| 子任务 | 值域 | 分值 |
| :----------: | :----------: | :----------: |
| $0$ | $1\le n,k\le 2\times 10^3$ | $30$ |
| $1$ | $1\le n,k\le 2\times 10^6$ | $70$ |

对于所有数据，满足 $1\le n,k\le2\times10^6$，$a_i\in\{0,1\}$。

## 样例 #1

### 输入

```
3 2
0 1 0```

### 输出

```
9```

# 题解

## 作者：focus_aurora (赞：5)

## 思路
分类讨论的数学题。

我们选择当前位置是一的情况进行讨论。

我们发现一个性质，下一轮前 $n$ 个转转楼梯的状态是上一轮第二个到第 $n+1$ 的状态，且若干次后，转转楼梯一定会全部变成零。

所以，分如下情况讨论。

当前位置的左边是一且右边是零的时候，此时只需要转动一次。总共转动 $i$ 次。

当前位置左右两边都是零的时候，此时需要转动两次。总共需要转动 $2\times i-1$ 次。

当前位置左边为零右边为一的时候，此时需要转动 $i-1$ 次。

然而我们只执行了 $k$ 轮。

所以所有的的答案记录都要让 $k$ 和 $i$ 取最小值进行操作。

最后，别忘赋初值。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//一定开long long！！！！！ 
using namespace std;
int a[2000005];
signed main(){
	int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}//输入 
	int ans=0;//答案记录变量 
	a[0]=1;//赋初值 
	for(int i=1;i<=n;i++){
		if(a[i]){
			if(a[i-1]&&!a[i+1]){//第一种情况 
				ans+=min(m,i);//和轮数取最小值 
			}
			if(!a[i-1]&&!a[i+1]){//第二种情况 
				int s=min(m,i);
				if(s==i){
					ans+=2*(s-1)+1;
				}
				else{
					ans+=2*s;
				}
			}
			if(!a[i-1]&&a[i+1]){//第三种情况 
				int s=min(m,i);
				if(s==i){
					ans+=s-1;
				}
				else{
					ans+=s;
				}
			}
		}
	}
	cout<<ans+m*n;//输出结果 
	return 0;
}
```

---

## 作者：wbqhasvcf (赞：4)

形式化题意：做一天操相当于把原本的 $01$ 串每一个数向左移动了一位，即 $a_{1}$ 溢出，$a_{n}$ 填充为 $0$（因为 $a_{n+1}=0$）。抓住问题的本质我们就好办了，根据题意对于 $1\le i\le n$，如果 $a_{i}$ 与 $a_{i+1}$ 不相等，那么额外增加 $1$ 秒转一圈，也就是说我们需要找出初始的 $01$ 串中有多少对 $a_{i}$ 与 $a_{i+1}$ 不相等，并将下标 $i$ 与 $k$ 比大小，较小者为这对不相等的数额外增加的秒数。这样 $01$ 串的长度 $n$ 与经过的天数 $k$ 相乘，再加上额外增加的秒数，即为同学们经过转转楼梯的总时间。于是时间复杂度为 $O(n)$ 的简短代码便倾囊而出：
```cpp
#include<iostream>
using namespace std;

long long n,ans;
int k;
bool a[2000005];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
    ans=n*k;//光是ans开long long还不够，还得保证n与k其中一个是长整型，否则n乘k会溢出
	for(int i=1;i<=n;i++)
	    if(a[i]!=a[i+1])
	        ans+=min(i,k);//额外增加的秒数
	cout<<ans;
	return 0;
}
```

---

## 作者：DGFLSzfd (赞：2)

## 通用思路
在做这种看上去没有固定套路的题目时（通常为竞赛的第一题或第二题），我们可以用一套**万能的流程来分析并解决**。

1. 简化题目  
有些题目为了增加难度，通常使用奇怪的或委婉的描述，我们则需要简化它们。以此题为例，要修改 $a_{i}$ 为 $1-a_{i}$ 且 $a_{i} \in\{0,1\}$ 不就是 $0$ 变成 $1$，$1$ 变成 $0$ 吗？

2. 模拟观察  
我们可以打一个暴力来观察不同数据在运行时的变化。

3. 寻找规律  
要论证一个思路的正确性和严谨性是非常耗时的一件事，有时我们无需证明一个思路的正确性，只需按照规律进行猜想。

4. 尝试修改  
通常我们很难一次想到周全，我们可以多次猜测错误之处，修改并提交，毕竟 IOI 赛制。
## 本题思路
按照上述的通用思路过一遍后，这题的做法是显而易见的。

因为每次 $a_{i}$ 的值都会变为 $a_{i+1}$，可以想象这是一个长度固定为 $n$ 的队列，每轮操作就相当于扔掉队头，在队尾加入一个 $0$。

不难发现每轮 $ans$ 就会加上 $n$ 和队列中 $a_{i+1}\ne a _{i}$ 的个数。

那么如何快速统计当前队列中 $a_{i+1}\ne a _{i}$ 的个数呢？  
当然是后缀和了！后缀和统计了以原数据第 $i$ 个数为队头的包括它在内的 $a_{i+1}\ne a _{i}$ 的个数。

## 代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int s[2000010],su[2000010];
long long ans=0;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(int i=n;i>=1;i--)
	{
		su[i]=su[i+1];
		if(s[i]!=s[i+1])
			su[i]++;
	}
	for(int i=1;i<=k;i++)
	{
		ans+=su[i];
		ans+=n;
	}cout<<ans;
} 
```

---

## 作者：_xdd_ (赞：1)

好像跟别的题解撞代码了，不管了先写出来。

首先答案初始化为 $n\times k$，这是正常走的时间，接下来我们求转圈的时间，即有多少 $a_i\ne a_{i+1}$，接下来考虑楼梯的变换。

每天走完楼梯，楼梯都会向左位移一位，原来的 $a_1$ 溢出，$a_n$ 变为 $0$，所以 $k$ 天下来，$a_i$ 会被踩中 $\min(i,k)$ 次，答案也要加上 $\min(i,k)$。

至于为什么是 $\min(i,k)$，刚才说了楼梯会向左位移，而 $a_1$ 会溢出，如果 $i<k$ 则 $a_i$ 会在第 $k$ 天结束前溢出，所以最多只能踩中 $i$ 次，否则踩中 $k$ 次。

记得开 `long long`。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define maxn 2000000+5
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int n,k;
int ans,a[maxn];
signed main(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    ans=n*k;
    for(int i=1;i<=n;i++){
        if(a[i]!=a[i+1]){
            ans+=min(i,k);
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：songhongying (赞：1)

## 题目大意：
转转楼梯有 $n+1$ 阶楼梯，对于第 $i$ 阶转转楼梯，其有一个转转值 $a_i$，对于一阶转转楼梯，如果其下一阶楼梯的转转值与之相同（即 $a_{i+1}=a_i$）那么我们可以直接走下去，耗费一秒。否则我们需要耗费一秒转一圈以改变目前这阶楼梯的转转值为 $1-a_i$，然后再耗费一秒走下去。

## 解题思路：
首先，要明白耗费一秒转一圈以改变目前这阶楼梯的转转值为 $1-a_i$ 就是如果 $a_i$ 为 $1$，就变为 $0$，否则变为 $1$。

然后，我们可以手算一下样例，得出每天走完楼梯后，相当于将转转楼梯的所有台阶向左移一位，即删除 $a_1$，将 $a_{n+1}$ 等于零。

最后，还需累加上当前台阶需要转几次。

这样，我们就得出一个不会超时的代码啦。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
int n,k,a[10000005],t;
signed main(){
    
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
	    cin>>a[i];
	}
	t=n*k;//总共需要走的楼梯数量
	for(int i=1;i<=n;i++)
	{
	    if(a[i]!=a[i+1])  t+=min(i,k);//累加次数
	}
	cout<<t;
	
	return 0;//完美结束
}
```

---

## 作者：MingRi_Doctor (赞：0)

## 题目大意：
转转楼梯有 $n+1$ 阶楼梯，对于一阶转转楼梯，如果其下一阶楼梯的转转值与之相同，那么我们可以直接走下去，耗费一秒。否则我们需要耗费一秒将目前这阶楼梯的转转值设为 $1-a_i$。然后再耗费一秒走下去。

## 思路：
这是一道非常简单的规律题，设 $n=3$，数列 $a=\{0,1,0\}$，那么结果如下：

第一天：$a=\{0,1,0\}$

第二天：$a=\{1,0,0\}$

第三天：$a=\{0,0,1\}$

第四天：$a=\{0,1,0\}$

我们可以从这个样例找到规律：将第 $i$ 天数列 $a$ 的第 $1$ 位移到最后一位就是第 $i+1$ 天的序列 $a$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,sum,a[2000005];
int k;//要开int才能用min函数
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	} 
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[i+1])//如果与下一阶楼梯的转转值不同
			sum+=min(i,k);//加上转i或k圈的秒数
	}
	cout<<sum+n*k;//输出转圈的秒数加上走k次n阶楼梯的秒数
	return 0;
} 
```

---

## 作者：qW__Wp (赞：0)

将答案分为两部分：走的时间和转圈时间。

对于走的时间，总贡献显然为 $n \times k$。

对于转圈时间，手玩几组样例之后可以发现：每一天都会把整个序列往左移一位，并在末尾补 $0$。严谨地说，对于所有的 $1 \le i < n$，使 $a_i \gets a_{i+1}$，并使 $a_n=0$。

于是考虑对于每一个 $a_i=1$，计算其贡献：

+ 若 $a_{i+1}=0$，则总贡献加上 $\min(i,k)$。

+ 若 $i > 1$，且 $a_{i-1}=0$，则总贡献加上$\min(i-1,k)$。

Code:

```
#include <bits/stdc++.h>
#define int long long // 记得开 long long
#define INF 0x3fffffff
#define INFF 1e18
#define endl '\n'
#define lson id << 1
#define rson id << 1 | 1
#define LL long long
#define ULL unsigned long long

using namespace std;

const int N = 2e6 + 5;

int a[N];

signed main() {
	int n, k; cin >> n >> k;
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	int ans = k * n;
	for (int i = 1; i <= n; i ++) {
		if (a[i]) {
			if (i > 1 && !a[i - 1]) ans += min(i - 1, k);
			if (!a[i + 1]) ans += min(i, k);
		}
	}
	cout << ans;
	return 0;
}
```

难度：中位橙。

---

## 作者：OrzSceamyn (赞：0)

## P11068 「QMSOI R1」 转转楼梯 题解

签到题。

先写个暴力，观察每次的转转值数组，你会发现每次都是删去 $a_1$ 将其他的向左移一位并在最后补 $0$。

所以可以求一个后缀和，定义 $sum_i$ 表示初始 $a_i$ 到 $a_n$ 有多少个相邻不同的值。

那么最后答案显然就是 $n\times k + \sum_{i=1}^{k}{sum_i}$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
const int maxn=2e6+7;
int sum[maxn],a[maxn];
int n,k;
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		if(a[i]!=a[i+1])sum[i]=sum[i+1]+1;
		else sum[i]=sum[i+1];
	}
	int ans=0;
	for(int i=1;i<=k;i++){
		ans+=n;
		ans+=sum[i];
	}
	cout<<ans<<'\n';
	
}

int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(T--){
		solve();
	}
	return 0;
}

```

---

