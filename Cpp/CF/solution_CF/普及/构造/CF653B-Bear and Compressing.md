# Bear and Compressing

## 题目描述

题目大意：

长度为n的字符串(字符串中只有abcdef共6种字母)，有q种压缩方式，可以将字符串的前两个字符压成1个字符，求凭借这q种压缩方式，有几种长度为n的字符串最终能被压缩成字符'a'.

## 说明/提示

在第一个样例中，符合条件的长度为3的字符串有4中，“abb”，“cab”，“cca”，“eea”

“abb” —> “ab” —> “a”

“cab” —> “ab” —> “a”

“cca” —> “ca” —> “a”

“eea” —> “ca” —> “a”

感谢@李东晓 提供的翻译

## 样例 #1

### 输入

```
3 5
ab a
cc c
ca a
ee c
ff d
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 8
af e
dc d
cc f
bc b
da b
eb a
bb b
ff c
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 2
bb a
ba a
```

### 输出

```
0
```

# 题解

## 作者：QWQ_123 (赞：0)

发现 $n$ 很小只有 $6$，但是一开始的两个一定是 $m$ 中的两个，所以 $n$ 就相当于只有 $4$ 个，直接暴力枚举每一位填什么应该也能过。

但是有一个优化就是每次选择可以与当前字符构成 $m$ 中的一个的字符。

比如当前字符是 $\texttt{c}$ 然后 $m$ 个字符集中有 $\texttt{cd}$ 那么这这一位的下一位就可以填 $\texttt{d}$，然后当前字符变成 $\texttt{cd}$ 对应的字符。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
string s[40];
char change[30][30];
vector<char> c[30][30];
int ans = 0;

void dfs(char la, int id) {
	// cout << la << ' ' << id << endl;
	if (id > n) {
		if (la == 'a') ++ans;
		return ;
	}

	for (int i = 0; i < 26; ++i)
		if (change[la - 'a'][i]) {
			dfs(change[la - 'a'][i], id + 1);
		}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		string a, b;
		cin >> a >> b;
		s[i] = a;
		change[a[0] - 'a'][a[1] - 'a'] = b[0];
	}

	for (int i = 1; i <= m; ++i) {
		dfs(change[s[i][0] - 'a'][s[i][1] - 'a'], 3);
	}

	printf("%d\n", ans);

	return 0;
}
```

---

## 作者：_Anchor (赞：0)

# Solution

比较显而易见，我们可以把每个字符串看成一个结点，然后根据首字母向其它新的字符串代表的结点连边，然后根据 $n$ 长度的限制弄出来一个 $DAG$ 。

最后统计一下每个点可以到达的最底层的点的数量就可以了，注意为什么是统计数量而不是在每次有出边的时候直接 $+1$ ：

因为某一个状态可能由两种不同的状态来到达，但是最后算也只能算一种，如果直接根据边数来加 $1$ 的话会算重。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=1e5+5,M=1e6+5,MOD=1e9+7;
int n,m,k;
int head[N],nex[M],to[M],idx,cnt=6,tot[N];
ll ans;
string op,op1;
unordered_map<string,int> q,q1;
unordered_map<int,string> iq;
inline void add(int u,int v){
    nex[++idx]=head[u];
    to[idx]=v;
    head[u]=idx;
    return ;
}
void dfs(string x,int len){
    if(len==n+1) return ;
    if(!q1.count(x)&&len==n){q1[x]=++cnt;ans++;}
    int now=x[0]-'a'+1;
    for(int i=head[now];i;i=nex[i]){
        int y=to[i];
        string yy=iq[y];
        x.erase(0,1);
        x=yy+x;
        dfs(x,len+1);
    }
    return ;
}
int main(){
    read(n),read(k);
    for(int i=1;i<=k;i++){
        cin>>op>>op1;
        if(!q.count(op)) q[op]=++cnt,iq[cnt]=op;
        add(op1[0]-'a'+1,q[op]);
    }
    dfs("a",1);
    write(ans);
    return 0;
}
```

---

