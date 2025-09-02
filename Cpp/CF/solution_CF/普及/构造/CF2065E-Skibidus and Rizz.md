# Skibidus and Rizz

## 题目描述

情人节将至，Skibidus 拼命需要一种方法来吸引他的暗恋对象！幸运的是，他找到了正解：制造完美的二进制字符串！

给定一个二进制字符串$^{\text{∗}} $ $t$，令 $x$ 表示 $t$ 中 $\texttt{0}$ 的个数，$y$ 表示 $t$ 中 $\texttt{1}$ 的个数。我们定义字符串的平衡值为 $\max(x-y,\, y-x)$。

Skibidus 给你三个整数 $n$，$m$ 和 $k$。他希望你构造一个长度为 $n+m$ 的二进制字符串 $s$，其中恰好包含 $n$ 个 $\texttt{0}$ 和 $m$ 个 $\texttt{1}$，并且要求其所有子串$^{\text{†}} $的平衡值的最大值恰好为 $k$。如果不存在满足条件的字符串，请输出 -1。

$ ^{\text{∗}} $ 二进制字符串指仅由字符 $\texttt{0}$ 和 $\texttt{1}$ 组成的字符串。

$ ^{\text{†}} $ 字符串 $a$ 是字符串 $b$ 的子串，意味着 $a$ 可以通过删除 $b$ 开头和结尾的若干（可能为 0 或全部）字符得到。

## 说明/提示

在第一个测试用例中，我们必须构造一个字符串 $s$，包含 1 个 $\texttt{0}$ 和 2 个 $\texttt{1}$，且所有子串中的最大平衡值为 $1$。一个可能的满足条件的字符串是 $\texttt{101}$，原因如下：

- 考虑由索引 $[1,1]$ 界定的子串：平衡值为 $\max(0-1,\, 1-0) = 1$。
- 考虑由索引 $[1,2]$ 界定的子串：平衡值为 $\max(1-1,\, 1-1) = 0$。
- 考虑由索引 $[1,3]$ 界定的子串：平衡值为 $\max(1-2,\, 2-1) = 1$。
- 考虑由索引 $[2,2]$ 界定的子串：平衡值为 $\max(1-0,\, 0-1) = 1$。
- 考虑由索引 $[2,3]$ 界定的子串：平衡值为 $\max(1-1,\, 1-1) = 0$。
- 考虑由索引 $[3,3]$ 界定的子串：平衡值为 $\max(0-1,\, 1-0) = 1$。

在所有可能的子串中，最大的平衡值为 $1$。

在第二个测试用例中，具有最大平衡值的子串为 $\texttt{0100}$，其平衡值为 $\max(3-1,\, 1-3) = 2$。

## 样例 #1

### 输入

```
6
1 2 1
4 3 2
2 4 3
8 3 2
5 0 4
5 0 5```

### 输出

```
101
0100101
011011
-1
-1
00000```

# 题解

## 作者：_hi_ (赞：4)

## 题面

要求构造一个长度为 $n+m$ 的 01 串，其中 0 有 $n$ 个，1 有 $m$ 个，且它的所有子串中，0 与 1 的差最大的恰好为 $k$。

## 思路

无解 $-1$ 的情况有两种，即为 $n<k$ 且 $m<k$，或者 $\max(n,m)-\min(n,m)>k$ 都很好理解。

能发现，形如 
```cpp
1010...101011...1100...001010...1010
```
 这样的串，左右两侧的 01 交替串对中间并没有贡献。

所以，可以先把 $n$ 个 1 和 $m$ 个 0 先连续放在左右两侧，接着，从两侧开始隔一位交换一对 0 和 1，直到中间的连续 1 和 0 有一个等于 $k$。

即 
```cpp
000..00111..11
```
变为
```cpp
01000..0011..11101
```
再变为
```cpp
010101...00..0011..11..010101
```


还有一些细节稍微处理一下就 A 啦！

[AC code](https://codeforces.com/contest/2065/submission/305536953)

---

## 作者：thedyingkai (赞：4)

### 思路
由题意，平衡值为 $|n_0-n_1|$，如果在 $n$ 和 $m$ 的条件下不可能达到平衡值，则输出 $-1$。

由于题目要求的是全部子串的最大平衡值等于 $k$，而生成子串的方法仅仅是去除两端的数字，所以代码可以构造为三部分，一段全部为 $0$，一段 $0$ 和 $1$ 交替出现，一段全部为 $1$。

题目要求 $k$，我们就先把 $n$ 和 $m$ 中最大者对应的数字 $x$ 拼接 $k$ 次，此时平衡值已经达到了题目要求，如果再接着拼接，平衡值就会超出要求，所以只能拼接 $1-x$。

但是继续拼接 $1-x$ 的话，不能保证 $\operatorname{n(1-x)}-\operatorname{n(x)}$ 一定不大于 $k$（注：$\operatorname{n(x)}$ 代表数字 $x$ 的个数），所以交替输出，这样保证平衡值不会超出要求，最后把剩下的用 $1-x$ 补足长度即可，由于事先比较，不会影响到最大平衡值。
### 最后输出三个循环范围的来源：
- $i<k$：先拿更多的那个（设为 $x$）凑够要求的平衡值。
- $i<n-k$：避免错误，两者交替出现，直到 $x$ 全部输出，以便于后面输出 $1-x$。
- $i<m-n+k$：最后剩下的用 $1-x$ 补足长度。
### AC code
```cpp
#include "iostream"
#include "algorithm"
using namespace std;
int t,n,m,k;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m>>k;
        bool flag=0;
        if(n<m){
            swap(n,m);
            flag=1;
        }
        if(k>n||k<n-m){
            cout<<"-1\n";
            continue;
        }
        for(int i=0;i<k;i++) cout<<(0^flag);
        for(int i=0;i<n-k;i++) cout<<(1^flag)<<(0^flag);
        for(int i=0;i<m-n+k;i++) cout<<(1^flag);
        cout<<'\n';
    }
}
```

---

## 作者：restart_to_revive (赞：1)

# CF2065E 题解
## Explanation
给定 $n$，$m$，$k$，求长度为 $n+m$ 的 $01$ 串使得其任意子串 $0$ 和 $1$ 的个数差距最大值为 $k$。如果没有，输出 $-1$。
## Analyze
首先我们可以发现 $k$ 个的情况显然是 $k$ 个 $1$ 或者 $k$ 个 $0$ 构成，为了使其满足规定，就要使剩下的 $0$ 和 $1$ 交替排布。

明显，无解的情况有两种：第一种是 $0$ 和 $1$ 均不足 $k$ 个，而第二种是再交替排布后剩下的 $0$ 或 $1$ 超过了 $k$ 个。

## Coding
由上方分析可以轻松写出。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int x,y,n; 
string s;
string h;
int main(){
	cin>>t;
	for(int i=0;i<t;i++){
		s=h;
		cin>>x>>y>>n;
		if(n==0){
			cout<<-1<<'\n';
			continue;
		}
		bool flag=false;
		if(x>y){
			if(x<n){
				cout<<-1<<'\n';
				continue;
			}
			for(int i=0;i<n;i++){
				s=s+'0';
				x--;	
			}
		}
		else{
			flag=true;
			if(y<n){
				cout<<-1<<'\n';
				continue;
			}
			for(int i=0;i<n;i++){
				s=s+'1';
				y--;
			}
		}
		if(x==0 and y==0){
			cout<<s<<'\n';
			continue;
		}
		for(int i=0;x!=0 and y!=0;i++){
			if(flag==true){
				s=s+'0';
				s=s+'1';
				x--;
				y--;
			}
			else{
				s=s+'1';
				s=s+'0';
				x--;
				y--;
			}
		}
		if(flag==true and x==0 and y!=0){
			cout<<-1<<'\n';
			continue;
		}
		if(flag==false and y==0 and x!=0){
			cout<<-1<<'\n';
			continue;
		}
		if(flag==true and x==0 and y==0){
			cout<<s<<'\n';
			continue;
		}
		if(flag==false and y==0 and x==0){
			cout<<s<<'\n';
			continue;
		}
		for(int i=0;i<max(x,y);i++){
			if(x>0) s=s+'0';
			else s=s+'1';
		}
		cout<<s<<'\n';
		s=h;
	}
	return 0;
}
```
但是交上去后却 [TLE](https://codeforces.com/contest/2065/submission/305305223)
到飞起。

但是复杂度为 $O(n+m)$ 正确。

考虑优化常数。
## Optimize
由于字符串操作常数较大，故直接预处理是否可行。
```cpp
	if(n==0){
		cout<<-1<<'\n';
		continue;
	}
	if(max(x,y)<n){
		cout<<-1<<'\n';
		continue;
	}
	bool flag=false;
	if(x>y){
		if(x<n){
			cout<<-1<<'\n';//case 1
			continue;
		}
		x-=n;
	}
	else{
		flag=true;
		if(y<n){
			cout<<-1<<'\n';//case 1
			continue;
		}
		y-=n;
	}
	int k=min(x,y);
	if(x>y) x-=y,y=0;
	else y-=x,x=0;
	if(flag==true and x==0 and y!=0){
		cout<<-1<<'\n';//case 2
		continue;
	}
	if(flag==false and y==0 and x!=0){
		cout<<-1<<'\n';//case 2
		continue;
	}
```
然后直接每位输出 $0$ 或者 $1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int x,y,n; 
string s;
string h;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int i=0;i<t;i++){
		s=h;
		cin>>x>>y>>n; 
		if(n==0){
			cout<<-1<<'\n';
			continue;
		}
		if(max(x,y)<n){
			cout<<-1<<'\n';
			continue;
		}
		bool flag=false;
		if(x>y){
			if(x<n){
				cout<<-1<<'\n';
				continue;
			}
			x-=n;
		}
		else{
			flag=true;
			if(y<n){
				cout<<-1<<'\n';
				continue;
			}
			y-=n;
		}
		int k=min(x,y);
		if(x>y) x-=y,y=0;
		else y-=x,x=0;
		if(flag==true and x==0 and y!=0){
			cout<<-1<<'\n';
			continue;
		}
		if(flag==false and y==0 and x!=0){
			cout<<-1<<'\n';
			continue;
		}
		if(flag==false){
			for(int i=0;i<n;i++){
				cout<<0;
			}
		}
		else{
			for(int i=0;i<n;i++){
				cout<<1;
			}
		}
		for(int i=0;i<k;i++){
			if(flag==true){
				cout<<"01";
			}
			else{
				cout<<10;
			}
		}
		if(flag==true and x==0 and y==0){
			cout<<'\n';
			continue;
		}
		if(flag==false and y==0 and x==0){
			cout<<'\n';
			continue;
		}
		bool flag2=(x>0);
		if(flag2==true){
			for(int i=0;i<x;i++){
				cout<<0;
			}
		}
		else{
			for(int i=0;i<y;i++){
				cout<<1;
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

## Tips
**一定在每组操作后清空字符串！！！**

[AC submission](https://codeforces.com/contest/2065/submission/305350683)

---

## 作者：EternalLabyrinth (赞：1)

### 题意：

给定 $n$ 个 $0$，$m$ 个 $1$，使用这些字符拼成一个长度为 $n+m$ 的二进制串。记一个字符串 $s$ 中 $1$ 和 $0$ 相差的个数为 $P(s)$。再给定一个 $k$，要使得拼成的这个字符串中的任意一个非空子串的 $s$ 的 $P(s)\leq k$，且存在一个 $s$ 使得 $P(s)=k$。

请构造出一种方案使得其成立或报告无解。

### 做法：

首先如果 $k>\max\{n,m\}$，则无解。

我们不妨设 $n>m$。先在前面放 $k$ 个 $0$，现在 $n$ 消耗掉了 $k$，若 $n-k$ 还是大于 $m$，那就无解了。后面接着放 $10$ 串，这样保证平衡，最后面全放 $1$ 即可。

$n\leq m$ 是对称的，于是我们就做完了。

---

## 作者：ztd___ (赞：1)

我在 CF2065 中的过题顺序：A，C1，E，D。是的你没有看错，我没有过掉 B，所以我认为该题比 B，C2，D 都简单，而 B 比 A，C1，D，E 都难。

考虑最简单的构造方案：显然对于一个字符串 $S$，如果里面全是 $0$ 或 $1$，那么 $S$ 的平衡值就是 $S$ 的长度。

所以构造方案非常显然，先输出 $k$ 个 $0$ 或 $1$，然后剩下的按 $10$ 或 $01$ 交替输出，最后再输出剩下的就可以了。这样由前面的 $k$ 个字符组成的子串的平衡值一定是 $k$。后面的 $0$ 和 $1$ 互相抵消，平衡值必然不会超过 $k$。

考虑判无解。如果 $k > \max(n,m)$，显然一开始的 $k$ 个 $0$ 或 $1$ 是不够用的，无解。其次如果 $k < \lvert n - m \rvert$，那么整个字符串的平衡值会比 $k$ 还大，无解。

代码也是非常简单。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m, k;
		cin >> n >> m >> k;
		if (abs(n - m) > k || (k > n && k > m)) {
			cout << "-1\n";
		} else {
			if (n > m) {
				n -= k;
				for (int i = 0;i < k;i++) cout << "0";
				for (int i = 1;i <= min(n, m);i++) cout << "10";
				if (n < m) {
					for (int i = 1;i <= m - n;i++) cout << "1";
				} else if (m < n) {
					for (int i = 1;i <= n - m;i++) cout << "0";
				}
			} else {
				m -= k;
				for (int i = 0;i < k;i++) cout << "1";
				for (int i = 1;i <= min(n, m);i++) cout << "01";
				if (n < m) {
					for (int i = 1;i <= m - n;i++) cout << "1";
				} else if (m < n) {
					for (int i = 1;i <= n - m;i++) cout << "0";
				}
			}
			cout << "\n";
		}
	}
	return 0;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV1eiNhe7EZ9?t=1064)

---

## 作者：fish_love_cat (赞：0)

简要题意：要求构造一个包含 $n$ 个 $\texttt{0}$ 和 $m$ 个 $\texttt{1}$ 的 $\texttt{01}$ 字符串使得其任意子串 $\texttt{0}$ 与 $\texttt{1}$ 数量之差的最大值恰为 $k$。

我们假设 $n\ge m$。

显然当 $k<n-m$ 或者 $k>n$ 时无解。

剩下的情况保证 $n-k\le m$。

我们可以先构造一个长度为 $k$ 全是 $\texttt{0}$ 的字符串，这样可以将 $n$ 减少 $k$。

我们将 $\texttt{10}$ 交替输出直至 $n$ 被消耗完，这样操作显然不会令结果变大。

之所以是 $n$ 先消耗完是因为我们保证了 $n-k\le m$。

然后我们再将剩余的 $m$ 个 $\texttt{1}$ 输出。

此时剩余的 $\texttt{1}$ 数量即为最初始的 $m-(n-k)=m+k-n$。

因为 $n\ge m$，所以 $m-n\le0$，也就是 $m-n+k\le k$。

那么构造是合法的。

$m<n$ 的情况是同理的。

做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    int swp=0;
    if(n<m)swap(n,m),swp=1;
    if(n-m>k){
        puts("-1");
        return;
    }
    if(k>n){
        puts("-1");
        return;
    }
    for(int i=1;i<=k;i++)
    cout<<(0^swp);
    n-=k;
    for(int i=1;i<=n;i++)
    cout<<(1^swp)<<(0^swp);
    m-=n;
    for(int i=1;i<=m;i++)
    cout<<(1^swp);
    cout<<'\n';
}
int main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# CF2065E 题解

## 思路

如果 $|n-m|>k$，显然对于任意一种结果，都有一个长度为 $n+m$ 的子串，使得二者之差 $>k$。

如果 $n<k$ 且 $m<k$，显然二者之差永远无法达到 $k$，无解。

要使差正好为 $k$，那么不能出现连续 $k+1$ 及以上长度的相同字符，如果长度小于等于 $k-1$ 可能无法保证合法，所以，只需要每 $k$ 个换一次字符，就可以保证无论怎么取结果都会小于等于 $k$，如果 $n>m$，则先填 $0$，否则先填 $1$。

比如，$n=10,m=9,k=4$，则可以构造出这样一个解：`0000111100001111001`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=400005;

int T,n,m,k;

int main() {
    read(T);
    while (T--) {
        read(n),read(m),read(k);
        if (abs(n-m)>k || (n<k && m<k)) {
            puts("-1");
            continue;
        }
        if (n>m) {
            while (n || m) {
                _rep(i,1,k) {
                    if (!n) break;
                    write(0);
                    n--;
                }
                _rep(i,1,k) {
                    if (!m) break;
                    write(1);
                    m--;
                }
            }
        } else {
            while (n || m) {
                _rep(i,1,k) {
                    if (!m) break;
                    write(1);
                    m--;
                }
                _rep(i,1,k) {
                    if (!n) break;
                    write(0);
                    n--;
                }
            }
        }
        putchar(10);
    }
    return 0;
}
```

---

## 作者：jzjr (赞：0)

## 前置知识

* 构造

## 翻译

现在定义一个 $01$ 字符串 $s$ 的平衡值为：

设 $s$ 有 $a$ 个 $0$，$b$ 个 $1$，那么值为 $|a-b|$。

现在给你 $n$ 个 $0$，$m$ 个 $1$。问你是否存在一种构造方式使得构成的字符串的所有字串的最大平衡值为 $k$。

## 思路

由于要平衡，考虑如下构造方法。

- $n>m$

前 $k$ 个为 $0$，后面尽量为 $k$ 个 $1$，接下来尽可能 $01$ 排列。

- $n\leq m$

前 $k$ 个为 $1$，后面尽量为 $k$ 个 $0$，接下来尽可能 $10$ 排列。

可以发现这样既满足前 $k$ 个字符构成的子串平衡值为 $k$，也满足后面的字串基本平衡。

但注意：

当 $k>n$ 且 $k>m$ 时，不存在。

当 $k<|n-m|$ 时，不存在。

## 实现

按照思路模拟即可。

### AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,k;
inline void solve(){
	cin>>n>>m>>k;
	int x=n-m;
	if(x<0)x=-x;
	if(x>k||(k>n&&k>m)){
		cout<<"-1\n";
		return ;
	}
	else {
		if(n>m){
			for(int i=1;i<=k;i++)cout<<'0',n--;
			for(int i=1;i<=k&&m;i++,m--)cout<<'1';
			while(n&&m)n--,m--,cout<<"01";
			while(n)cout<<'0',n--;
		}
		else {
			for(int i=1;i<=k;i++)cout<<'1',m--;
			for(int i=1;i<=k&&n;i++,n--)cout<<'0';
			while(n&&m)n--,m--,cout<<"10";
			while(m)cout<<'1',m--;
		}
		cout<<"\n";
	}
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
} 
```

---

