# Binary String Reconstruction

## 题目描述

For some binary string $ s $ (i.e. each character $ s_i $ is either '0' or '1'), all pairs of consecutive (adjacent) characters were written. In other words, all substrings of length $ 2 $ were written. For each pair (substring of length $ 2 $ ), the number of '1' (ones) in it was calculated.

You are given three numbers:

- $ n_0 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 0 $ ;
- $ n_1 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 1 $ ;
- $ n_2 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 2 $ .

For example, for the string $ s= $ "1110011110", the following substrings would be written: "11", "11", "10", "00", "01", "11", "11", "11", "10". Thus, $ n_0=1 $ , $ n_1=3 $ , $ n_2=5 $ .

Your task is to restore any suitable binary string $ s $ from the given values $ n_0, n_1, n_2 $ . It is guaranteed that at least one of the numbers $ n_0, n_1, n_2 $ is greater than $ 0 $ . Also, it is guaranteed that a solution exists.

## 样例 #1

### 输入

```
7
1 3 5
1 1 1
3 9 3
0 1 0
3 1 2
0 0 3
2 0 0```

### 输出

```
1110011110
0011
0110001100101011
10
0000111
1111
000```

# 题解

## 作者：45dinо (赞：5)

有一个更简洁的做法。

发现相邻两个和为 $0$ 时，两个数都是 $0$；和为 $1$ 时，两个数一个 $1$ 一个 $0$；和为 $2$ 时，两个数都是 $1$。

发现和为 $1$ 是最特殊的情况，所以利用它分类。
- $n_1=0$，由于保证答案存在，$n_0$ 和 $n_2$ 必然有一个为 $0$，直接构造即可。
- $n_1\neq 0$，先构造 $n_0+1$ 个 $0$，保证和为 $0$ 的数量达到，再构造 $n_2+1$ 个 $1$，保证和为 $2$ 的数量达到，此时已经有一组和为 $1$，对于剩下的 $n_1-1$ 个和为 $1$ 的组，只要按照 $0-1-0-1-0\dots$ 的顺序构造即可。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n1,n2,n3;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d %d",&n1,&n2,&n3);
		if(n2==0)
		{
			if(n1)
				for(int i=1;i<=n1+1;i++)
					cout<<0;
			else
				for(int i=1;i<=n3+1;i++)
					cout<<1;
			cout<<endl;
			continue;
		}
		for(int i=1;i<=n1+1;i++)
			cout<<0;
		for(int i=1;i<=n3+1;i++)
			cout<<1;
		n2--;
		for(int i=1;i<=n2;i++)
			if(i&1)
				cout<<0;
			else
				cout<<1;
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：bitset_iTM (赞：3)

## 思路  
拿到题目一看，这不就构造嘛~，看了其他大佬们的题解，发现没有使用搜索构造的。虽然搜索复杂度没有其他大佬好，但是通过这题还是没问题哒~  
（个人感觉搜索构造更好理解）  
定义一个 dfs 函数，包含以下参数：  
1. $step$ ：当前正在构造了第几步，当构造到 $x _ {0} + x _ {1} + x _ {2} + 1 + 1$ 时结束（注意要多加一个1，因为此时字符全里只有$x _ {0} + x _ {1} + x _ {2} + 1$ 个元素，满足结束的条件）
1. $a$ ：已经构造出 $a$ 个相邻和为 0 的字符对
1. $b$ ：已经构造出 $b$ 个相邻和为 1 的字符对
1. $c$ ：已经构造出 $c$ 个相邻和为 2 的字符对
1. $s$ ：表示目前已经构造出的字符串

好，废话不多说，上代码~  
## code  
```cpp
#include <bits/stdc++.h>
using namespace std;

int a, b, c;
bool flag = 0;

void dfs(int step, int x, int y, int z, string s)
{
    if (flag) return ; //已经找到答案了，结束
    if (x > a || y > b || z > c) return ; //剪枝
    if (step == a + b + c + 2)
    {
        if (x != a || y != b || z != c) return ;
        //构造出的字符串不符合条件，return掉
        cout << s << endl;
        flag = 1; //已经找到答案，标记为1
        return ;
    }
    
    int f = s.back() - '0';
    if (f == 0) //当最后一个字符是0时
    {
        dfs(step + 1, x + 1, y, z, s + '0');
        //当前字符选择0，相邻两个字符的和为0，x + 1
        dfs(step + 1, x, y + 1, z, s + '1');
        //当前字符选择1，相邻两个字符的和为1，y + 1
    }
    
    else if (f == 1) //当最后一个字符是1时
    {
        dfs(step + 1, x, y + 1, z, s + '0');
        //当前字符选择0，相邻两个字符的和为1，y + 1
        dfs(step + 1, x, y, z + 1, s + '1');
        //当前字符选择1，相邻两个字符的和为2，z + 1
    }
    
    else //这说明目前是第一次构造，字符串里还没有元素
    {
        dfs(step + 1, x, y, z, "0");
        //选择0，目前字符串里只有1个字符，无法组成字符对
        dfs(step + 1, x, y, z, "1");
        //选择1，目前字符串里只有1个字符，无法组成字符对
    }
}

void solve()
{
    flag = 0; //初始化
    scanf("%d %d %d", &a, &b, &c);
    dfs(1, 0, 0, 0, "");
}

int main()
{
    int T;
    scanf("%d", &T);
    
    while (T--) //多组数据用函数，好习惯qwq
        solve();
    return 0; //完美地结束~！
}

```


---

## 作者：MIQILINSANXINGSHICHU (赞：2)

# 蒟蒻的题解
其实分情况讨论就好了

第一种情况,n0，n1为零.这种时候只需要输出n2加一个1就好了。
```
if((n0==0)&&(n1==0)&&(n2!=0)){
	for(int i=1;i<=n2+1;i++)
		cout<<"1";
		cout<<endl;
	}
```
第二种情况，只有n1为零。这种情况我们可以先输出n2，也就是n2加一个1，再输出n1,因为前面已经有了一个一，所以先输个0，再输出(n1-1)/2个10，这里可以在草稿纸上简单列几个数找下规律。
```
if((n0==0)&&(n1!=0)&&(n2!=0)){
	for(int i=1;i<=n2+1;i++)
		cout<<"1";
		if(n1%2==0){
			for(int i=1;i<=n1/2;i++)
			cout<<"01";
		}
		else{
			cout<<"0";
			for(int i=1;i<=(n1-1)/2;i++)
				cout<<"10";
		}
		cout<<endl;
}
```
第三种情况，只有n1不为零，也很简单，分两种情况，n1为奇数偶数，在草稿纸上列一下就好了。
```
if((n0==0)&&(n1!=0)&&(n2==0)){
	cout<<"1";
		if(n1%2==0){
			for(int i=1;i<=n1/2;i++)
			cout<<"01";
		}
		else{
			cout<<"0";
			for(int i=1;i<=(n1-1)/2;i++)
				cout<<"10";
		}
		cout<<endl;
}
```
第四种情况，只有n0不为零，输出n0+1个0就好了。
```
if((n0!=0)&&(n1==0)&&(n2==0)){
	for(int i=1;i<=n0+1;i++)
		cout<<"0";
	cout<<endl;
}
```
第五种情况，只有n2为零，先输出n0+1个0，再输出个一，之后也建议在草稿纸上列出几组数找一下规律。
```
if((n0!=0)&&(n1!=0)&&(n2==0)){
	for(int i=1;i<=n0+1;i++)
		cout<<"0";
	if(n1%2==0){
		for(int i=1;i<=n1/2;i++)
			cout<<"10";
	}
	else{
		cout<<"1";
		for(int i=1;i<=(n1-1)/2;i++)
				cout<<"01";
	}
	cout<<endl;
}
```
第六种情况，全部不为零，我也分了两种情况，n1的奇偶性，为奇数的话先把n0输出了，再考虑n1的情况，然后是n2.为偶数的时候先输出10，再输出n0个0，再输出1，再解决掉n1，最后考虑n2,具体还是建议草稿纸上写出来看下。
```
if((n0!=0)&&(n1!=0)&&(n2!=0)){
	if(n1%2==1){
		for(int i=1;i<=n0+1;i++)
			cout<<"0";
		for(int i=1;i<=(n1-1)/2;i++)
			cout<<"10";
		for(int i=1;i<=n2+1;i++)
			cout<<"1";
		cout<<endl;
	}
	else{
		cout<<"10";
		for(int i=1;i<=n0;i++)
			cout<<"0";
		cout<<"1";
		for(int i=1;i<=(n1-2)/2;i++)
			cout<<"01";
		for(int i=1;i<=n2;i++)
			cout<<"1";
		cout<<endl;
	}
}
```
就是这样了，多打草稿就好。

---

## 作者：b6e0_ (赞：2)

打完CF又来写题解啦~求兹磁qwq（第一次AK CF比赛）

[CF题面传送门](https://codeforces.com/contest/1352/problem/F) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1352F) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1352F)

构造题。稍微分一些情况。

如果$n1=0$，那么比较好办。这种情况下$n0$和$n2$中只可能有一个不为$0$：$n0$不为$0$时输出$n0+1$个$0$，$n2$不为$0$时输出$n2+1$个$1$。

如果$n1$不为$0$，就会稍微有点麻烦。用$s$表示答案字符串。首先$s=$"$1$"。做$n1$次，每次如果$s$的末尾是$1$则添加$0$，是$0$则添加$1$。然后做$n0$次，每次将$s$开头的$1$换成$10$。最后做$n2$次，每次在开头添加一个$1$。用样例模拟一下就能懂。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n0,n1,n2,i;
	string s;
	cin>>t;
	while(t--)
	{
		cin>>n0>>n1>>n2;
		if(n1)//判断n1是否为0
		{
			s="1";
			for(i=0;i<n1;i++)
				if(s[s.size()-1]=='0')
					s+="1";
				else
					s+="0";
			for(i=0;i<n0;i++)
				s="10"+s.substr(1,s.size()-1);//将s开头的1换成10
			for(i=0;i<n2;i++)
				s="1"+s;
			cout<<s<<endl;
		}
		else
			if(n0)
			{
				while(n0--)
					cout<<0;
				cout<<"0\n";//最后要多输出一个0
			}
			else
			{
				while(n2--)
					cout<<1;
				cout<<"1\n";//最后要多输出一个1
			}
	}
	return 0;
}
```
时间复杂度为$O((n0+n1+n2)^2)$。

---

## 作者：registerGen (赞：2)

小清新构造题。

[更好的阅读体验](https://registergen.github.io/post/solution-cf1352f/)

# Solution

给一个我的构造方法吧，比较简洁。

- 若 $n_0=0$ 且 $n_1=0$，则输出 $n_2+1$ 个 $\texttt{1}$ 即可。

- 若 $n_2=0$ 且 $n_1=0$，则输出 $n_0+1$ 个 $\texttt{0}$ 即可。

- 否则，我们先来 $n_0+1$ 个 $\texttt{0}$，再来 $n_2+1$ 个 $\texttt{1}$，最后 $n_1-1$ 个 $\texttt{01}$ 相间即可。

# Code

```cpp
#include<bits/stdc++.h>

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n0,n1,n2;
		scanf("%d%d%d",&n0,&n1,&n2);
		std::string ans="";
		if(n0==0&&n1==0)
		{
			for(int i=1;i<=n2+1;i++)ans+="1";
			goto OUTPUT;
		}
		if(n1==0&&n2==0)
		{
			for(int i=1;i<=n0+1;i++)ans+="0";
			goto OUTPUT;
		}
		if(n1>=1)
		{
			for(int i=1;i<=n0+1;i++)ans+="0";
			for(int i=1;i<=n2+1;i++)ans+="1";
			for(int i=1;i<=n1-1;i++)
			{
				if(i%2==1)ans+="0";
				else ans+="1";
			}
			goto OUTPUT;
		}
OUTPUT:
		puts(ans.c_str());
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：1)

## 题解 CF1352F 【Binary String Reconstruction】

### 题意

+ 给出 $a,b,c$，求构造一个 01 序列，对于每个长度为 $2$ 的子串，和为 $0$ 的有 $a$ 个，和为 $1$ 的有 $b$ 个，和为 $2$ 的有 $c$ 个；
+ 多组数据，$a,b,c\le100$。

### 做法

似乎思路其他题解都不同？

如果 $a$ 不为 $0$，输出 $a+1$ 个 $0$。

如果 $c$ 不为 $0$，输出 $c+1$ 个 $1$。

如果 $b$ 不为 $0$：  
+ 如果 $ac$ 不为 $0$，$b\Leftarrow b-1$，因为前面已经有一组了；
+ 如果 $a,c$ 都为 $0$，$b\Leftarrow b+1$，因为还要有一个数垫在前面；
+ 如果前面字符串最后一位是 $1$，按 $01010\dots$ 的顺序输出 $b$ 位；
+ 否则按 $10101\dots$ 的顺序输出 $b$ 位。

### 代码

根据上面讲的做了一些细节上的处理，总体思路一样。

```cpp
#include <cstdio>

using namespace std;

void run() {
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if (a) {
		for (int i = 0; i <= a; ++i) {
			printf("0");
		}
	}
	if (c) {
		for (int i = 0; i <= c; ++i) {
			printf("1");
		}
	}
	if (b) {
		if (a && c) {
			--b;
		}
		if (c) {
			for (int i = 0; i < b; ++i) {
				printf("%d", i & 1);
			}
		}
		else if (a) {
			for (int i = 1; i <= b; ++i) {
				printf("%d", i & 1);
			}
		}
		else {
			for (int i = 0; i <= b; ++i) {
				printf("%d", i & 1);
			}
		}
	}
	printf("\n");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：
- 很容易想到 $1+1=2$ 和 $0+0=0$ 这两种方案比较的普通，可以直接把 $0$ 或 $1$ 放在一堆，但如果要组成的和为 $1$，那只能是两个不同的数相加的来。所以我们可以现构造一个 $0$ 和 $1$ 相互交错的字符串，在将所有要用的 $n0$ 个 $0$ 全部放到构造字符串的最后一个 $1$ 后面， $n0$ 个 $0$ 全部放到构造字符串的最后一个 $0$ 后面。但要最后判断 $n1$ 是否等于 $0$，如是要特殊处理。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n0,n1,n2;
		cin>>n0>>n1>>n2;
		int sum=n1+1;
		if(n1==0)
		{
			sum=0;
		}
		for(int i=0;i<sum;i++)
		{
			if(i+2>=sum)
			{
				if(i%2==0)
				{
					for(int j=0;j<=n2;j++)
					{
						cout<<1;
					}
					n2=0;
				}
				else
				{
					for(int j=0;j<=n0;j++)
					{
						cout<<0;
					}
					n0=0;
				}
			}
			else
			{
				if(i%2==0)
				{
					cout<<1;
				}
				else
				{
					cout<<0;
				}
			}
		}
		if(n2!=0)
		{
			for(int j=0;j<=n2;j++)
			{
				cout<<1;
			}
		}
		if(n0!=0)
		{
			for(int j=0;j<=n0;j++)
			{
				cout<<0;
			}
		}
		cout<<endl;
	}
}
```


---

## 作者：zxh923 (赞：0)

# CF1352F Binary String Reconstruction 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1352F)

### 思路

首先有 $0+0=0,0+1=1+0=1,1+1=2$，于是我们可以得到 $1$ 是比较特殊的一种情况，接下来进行分类。

+ 没有和为 $1$ 的子串

所以序列中 $0$ 和 $1$ 一定不同时出现，否则必有和为 $1$ 的一段，所以此时序列只可能为全 $0$ 或全 $1$。

+ 有和为 $1$ 的子串

考虑先把 $0$ 凑够，于是先输出 $n_0+1$ 个 $0$，接下来开始输出 $1$，记住这时已经有一个子串和为 $1$。

这里再输出 $n_2+1$ 个 $1$，接下来还剩 $n_1-1$ 个和为 $1$ 的子串，交错输出 $0,1$ 即可。

### 代码

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 8005
using namespace std;
int t,n3,n1,n2;
signed main(){
	cin>>t;
	while(t--){
		cin>>n1>>n2>>n3;
		if(!n2){
			if(n1)for(int i=1;i<=n1+1;i++)cout<<"0";
			else for(int i=1;i<=n3+1;i++)cout<<"1";
			cout<<'\n';
		}
		else{
			for(int i=1;i<=n1+1;i++)cout<<"0";
			for(int i=1;i<=n3+1;i++)cout<<"1";
			for(int i=1;i<n2;i++){
				if(i&1)cout<<"0";
				else cout<<"1";
			}
			cout<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路

可以通过观察发现一个性质，对于除了最后一个字母，每个字母都会堆答案产生一的贡献，也就是不会发生构造两段连续的 $0$ 的情况，$1$ 也是同理的。

那么我们就可以暴力构造了，因为这里是可能等于零的，那么就先把等于零的全给特判掉，然后对于剩下的先构造 $n0,n2$，然后构造 $n1-1$ 个 $01$ 相间的就好了。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i++)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using i64 = long long;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        int n0, n1, n2;
        cin >> n0 >> n1 >> n2;
        if (n0 == 0 && n1 == 0) {
            rep(i, 1, n2 + 1) {
                cout << 1;
            }
            cout << "\n";
            continue;
        }
        if (n1 == 0 && n2 == 0) {
            rep(i, 1, n0 + 1) {
                cout << 0;
            }
            cout << "\n";
            continue;
        }
        if (n1 >= 1) {
            rep(i, 1, n0 + 1) {
                cout << 0;
            }
            rep(i, 1, n2 + 1) {
                cout << 1;
            }
            bool flag = 0;
            rep(i, 1, n1 - 1) {
                cout << flag;
                flag ^= 1;
            }
            cout << "\n";
            continue;
        }
    }
    return 0;
}
```

---

## 作者：TheOnlyMan (赞：0)

```cpp
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n0,n1,n2;
		cin>>n0>>n1>>n2;//奇怪的构造，先做00，再做01，最后做11
		string ans="";//将答案存起来再一次性输出会快不少
		if(n0){
			if(n1%2==0&&n1)ans+='1',n1--;//在01串存在时若是为奇数则先往最前面加个1，因为01串必须以1结尾，不然会使第2个多1。 
			ans+='0';//先放个0，再根据00串个数放0
		}
		for(int i=1;i<=n0;i++){
			ans+='0';
		}
		if(n1){
			if(n0){//因为前面处理过01串的奇偶性，01串此时一定为奇数
				for(int i=1;i<=n1;i++){
					ans+=(ans.back()=='0'?'1':'0');
				}
          	//01串结尾一定为1
			}
			else{//00串不存在，则处理奇偶性放置0，1顺序，使结尾为1
				if(n1%2==0)ans+='1';
				else ans+='0';
				for(int i=1;i<=n1;i++){
					ans+=(ans.back()=='0'?'1':'0');
				}
			}
		}
		if(n2){
			int num=!ans.length()？n2+1:n2;//判断1个数
			for(int i=1;i<=num;i++){
				ans+='1';
			}
		}
		cout<<ans<<"\n";//最后输出即可	
	}
	return 0; 
}
```
```


---

## 作者：do_while_true (赞：0)

输出 $n_0+1$ 个 $0$ （凑齐 $n_0$ 个 $00$），$n_2+1$ 个 $1$ （凑齐 $n_2$ 个 $11$），然后这两段中间出现了一个$01$ ，所以在最后输出长度为 $n_2-1$ 的 $010101...$ 或 $101010...$ 即可。具体输出那种取决于前面是 $1$ 还是 $0$。

[$\mathcal{Code}$](https://codeforces.com/contest/1352/submission/79568495)

---

