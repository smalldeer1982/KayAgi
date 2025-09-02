# 「Cfz Round 3」Battle

## 题目描述

Alice 和 Bob 正在进行一个游戏，游戏的规则如下：

- Alice 初始时拥有一个整数 $n$，Bob 初始时拥有一个整数 $m$；
- 从 Alice 开始，两人轮流对**对方拥有的整数**进行操作：设对方此时拥有的整数为 $h$，使 $h$ 的值**减去** $h \bmod p$，其中 $\bmod$ 表示**取模**运算，$p$ 是给定的一个定值；
- 两人中率先使对方拥有的整数变为 $0$ 的人获得胜利，若在两人分别进行 $10^{10^{9961}}$ 次操作后仍无人获得胜利，则认为游戏平局。

你需要判断谁将会获得胜利，或报告游戏将会平局。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，Alice 在第一次操作中就会将 Bob 拥有的整数从 $2$ 变为 $2-(2\bmod 10)$ 即 $0$，所以 Alice 将会获得胜利。

对于第 $2$ 组数据，Alice 在第一次操作中会将 Bob 拥有的整数从 $11$ 变为 $11-(11\bmod 11)$ 即 $11$，而 Bob 在第一次操作中会将 Alice 拥有的整数从 $9$ 变为 $9-(9 \bmod 11)$ 即 $0$，所以 Bob 将会获得胜利。

对于第 $3$ 组数据，可以证明游戏将会平局。

#### 「数据范围」

对于所有数据，$1 \leq T \leq 5000$，$1 \leq n, m, p \leq 2\times 10^9$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
3
1 2 10
9 11 11
55 15 14```

### 输出

```
Alice
Bob
Lasting Battle```

# 题解

## 作者：ScaredQiu (赞：7)

### 数学

------------

一般地，对于任意 $n,p \in \mathbb{Z} ^+$ 有 $(n-n \bmod p) \bmod p=0$。

$n$ 减去 $n$ 除以 $p$ 的余数后必为 $p$ 的倍数，此后必定有 $n \bmod p =0$。

也就是说，**会使 $n$ 的值减小的操作只可能是对 $n$ 进行的第一次操作**。

同理，**会使 $m$ 的值减小的操作只可能是对 $m$ 进行的第一次操作**。

按顺序模拟两人的第一次操作，若一位玩家持有的数字变为 $0$ 则另一位玩家获胜。

如果一轮操作后游戏没有结束，由于 $n,m$ 的值不会再次改变，游戏永远无法结束。

单次询问时间复杂度 $O(1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mod;
void solution(){
	scanf("%d%d%d",&n,&m,&mod);
	m-=m%mod;
	if(m==0) return puts("Alice"),void();
	n-=n%mod;
	if(n==0) return puts("Bob"),void();
	puts("Lasting Battle");
}
int T;
int main(){
	scanf("%d",&T);
	while(T--) solution();
	return 0;
}
```

---

## 作者：__Tonycyt__ (赞：4)

### 思路

首先由于要进行 $10^{10^{9961}}$ 轮，所以不可能模拟。

考虑到 $h-h \bmod p$ 一定为 $p$ 的倍数，所以在进行一次操作之后两个人的数都不会变化了。

所以只需要模拟一轮，而且 $h-h\bmod p=0$ 当且仅当 $0\leq h<p$，所以直接判断 $h<p$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int x,y,p;
		cin>>x>>y>>p;
		if(y<p) cout<<"Alice\n";
		else if(x<p) cout<<"Bob\n";
		else cout<<"Lasting Battle\n";
	}
	return 0;
}

```

---

## 作者：CaiZi (赞：2)

## P10029「Cfz Round 3」Battle 题解
#### [题目链接](https://www.luogu.com.cn/problem/P10029)
### 题意理解
有两个数 $n,m$。轮流使 $m\gets m-m \bmod p$，再使 $n\gets n-n \bmod p$。谁的数先变为 $0$ 谁就失败。进行超过 $10^{10^{9961}}$ 回合后平局。$T$ 组数据，$1\le T\le5000$，$1\le n,m,p\le 2\times10^9$。
### 题目分析
本题解与其余题解略有不同，本题解使用暴力模拟法，可以通过本题（毕竟这题是道红题）。

$10^{10^{9961}}$ 这个数字显然无论怎么操作都是达不到的，因此可以无视。真正平局的条件是：当不断进行游戏均无法改变 $n,m$ 时，游戏平局。即 $n\bmod p=0$ 且 $m\bmod p=0$ 时，游戏平局。
### 代码展示
实际复杂度是 $O(T)$ 的。因为在进行一次循环后，$m,n$ 必然为 $p$ 的倍数，所以只会进行一次循环。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,p;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n>>m>>p;
		while(true){//模拟
			m-=m%p;
			if(m==0){
				cout<<"Alice\n";
				break;
			}
			n-=n%p;
			if(n==0){
				cout<<"Bob\n";
				break;
			}
			if(n%p==0&&m%p==0){//当两人都无法减少对方数字时平局
				cout<<"Lasting Battle\n";
				break;
			}
		}
	}
	return 0;
}
```
#### [提交记录](https://www.luogu.com.cn/record/141598505)

---

## 作者：_fallen_leaves_ (赞：1)

#### [P10029](https://www.luogu.com.cn/problem/P10029)

## 思路：
先求出两人需要多少次才能把别人的数变成 $0$，这个数只要做操作完数没有改变，就一定不能把他变成 $0$，求出两数，再来做比较，如果两数都不可以，就输出 Lasting Battle，如果第一个数如果小于第二个数，就是 Alice 胜，否则输出 Bob 胜。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n,m,p,x,sum=0,ans=0; 
		cin>>n>>m>>p;
		while(1)
		{
			x=m;
			if(m==0) break;//如果变成0，直接退出循环 
			m-=m%p;//减少m%p 
			sum++;
			if(x==m)
			{
				sum=LONG_LONG_MAX;//如果不行，就赋值一个很大的数 
				break;
			}
		}//求第二个数经历多少次能到0 
		while(1)
		{
			x=n;
			if(n==0) break;//如果变成0，直接退出循环 
			n-=n%p;//减少n%p
			ans++;
			if(x==n)
			{
				ans=LONG_LONG_MAX;//如果不行，就赋值一个很大的数 
				break;
			}
		}//求第一个数经历多少次能到0 
		if(sum==LONG_LONG_MAX&&ans==LONG_LONG_MAX)	cout<<"Lasting Battle\n";
		else if(sum<=ans) cout<<"Alice\n";
		else cout<<"Bob\n";//多组数据需要输出换行 
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

注意到第一次操作后，$h$ 会变为 $p$ 的倍数，随后 $h\bmod p$ 会变为 $0$，即 $h$ 的值不会再改变。那么如果双方不能在一回合内将对方的数变为 $0$，则为平局。

又当 $h=h\bmod p$（即 $h<p$）时一次操作即可变为 $0$，则判断一下即可。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
    cin>>T;
    while(T--){
    	int n,m,p;
        cin>>n>>m>>p;
        if(m<p) puts("Alice");
        else{
        	if(n<p) puts("Bob");
            else puts("Lasting Battle");
		}
	}
	return 0;
}
```

---

## 作者：York佑佑 (赞：0)

## 分析
设此时的整数为 $h$。不难发现，如果 $h \ge p$，则第一轮操作后 $h$ 将会变成 $p$ 的倍数，此时 $h \bmod p = 0$，$h$ 经过无数次操作之后依然不变。如果 $h < p$，则 $h = h \bmod p$，第一轮操作后 $h$ 将变成 $0$。

将刚才的结论带入 Alice 和 Bob。Alice 初始时拥有一个整数 $n$，Bob 初始时拥有一个整数 $m$。

- 当 $n \ge p$ 且 $m \ge p$ 时，两人的数一轮操作后 $h$ 将会变成 $p$ 的倍数，经过无数次操作之后依然不变。此时平局。

- 当 $n < p $ 且 $m \ge p$ 时，Bob 的数 $m$ 经过第一轮操作后会变成 $p$ 的倍数，Alice 的数 $m$ 经过第一轮操作后会变成 $0$，此时 Bob 胜。

- 当 $m < p$ 时，Bob 的数 $m$ 经过第一轮操作后会变成 $0$，此时 Alice 胜。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, p;
int main(){
	cin >> T;
	while (T--){
		cin >> n >> m >> p;
		if (n >= p && m >= p)	cout << "Lasting Battle\n";
		else	cout<<(m>=p?"Bob\n":"Alice\n");
	}
	return 0;
}
```


---

