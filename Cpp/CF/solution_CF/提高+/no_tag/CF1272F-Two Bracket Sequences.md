# Two Bracket Sequences

## 题目描述

给出两个括号串$s,t$（$s,t$ 不一定合法），它们仅由左括号`(`和右括号`)`组成

你需要构造一个字符串 $f$，使得 $s,t$ 都是 $f$ 的子串（不一定是连续子串），并满足：字符串 $f$ 合法且 $|f|$（$f$的长度）尽可能小

定义合法括号串：

- `()`是合法括号串  
- 若 $S$ 是合法括号串，则 $(S)$ 也是合法括号串
- 若 $A$ 和 $B$ 都是合法括号串，则 $AB$ 也是合法括号串

## 说明/提示

$|s|,|t| \le 200$。

感谢 @_Wolverine 提供的翻译

## 样例 #1

### 输入

```
(())(()
()))()
```

### 输出

```
(())()()
```

## 样例 #2

### 输入

```
)
((
```

### 输出

```
(())
```

## 样例 #3

### 输入

```
)
)))
```

### 输出

```
((()))
```

## 样例 #4

### 输入

```
())
(()(()(()(
```

### 输出

```
(()()()(()()))
```

# 题解

## 作者：yuzhechuan (赞：14)

### 题解：

设$g[i][j][k]$表示要使$S$串匹配到第$i$个括号，$T$串匹配到第$j$个括号，所得到的答案串里还有$k$个左括号未匹配所需要的最少括号

同时记录$f[i][j][k]=\{i',j',k'\}$表示$g[i][j][k]$是从$g[i'][j'][k']$转移来的

考虑转移：

假设我们现在要在状态$\{i,j,k\}$上添加个左括号转移到状态$\{ni,nj,nk\}$

因为是添加左括号，所以$nk=k+1$

如果$S_{i+1}$是左括号，那么$ni=i+1$（意思是匹配），否则就$ni=i$（意思是加个不存在的括号）

$T$串同理

相反的，如果现在要加个右括号，那$nk=k-1$（因为可以抵消一个左括号），其余与左括号的情况同理

另外，还要注意$nk$的上下边界，即$nk\in[0,len_S+len_T]$

代码中，考虑用bfs进行这个dp过程，从$\{0,0,0\}$一步加一个括号，由于bfs的性质，可以保证第一次到达某种状态时，解一定是最优的（即括号数最少）

这样我们就可以省略g数组了

最后考虑回溯统计答案

显然的，状态$\{len_S,len_T,0\}$是我们需要的答案状态，表示$S$和$T$串都匹配完了，且没有左括号剩余

我们就可以从这个答案状态出发，沿$f$数组回溯到$\{0,0,0\}$为止

假设现在状态时$\{i,j,k\}$，将要回溯到$\{i',j',k'\}$

如果$k>k'$，就说明现在这个状态是一个左括号

否则$k<k'$就说明这个状态是一个右括号

把相应括号加到答案串里逆序输出即可


---

代码中我写了个结构体，实际上也可以用c++11自带的多元组tuple

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=205;
int n,m;
char a[N],b[N];
string ans;

struct node{
	int i,j,k;
}f[N][N][N<<1];


void bfs(){
	queue<node> q;
	memset(f,-1,sizeof f); //一开始都没走过
	f[0][0][0]=(node){0,0,0}; //起始状态
	q.push((node){0,0,0});
	while(!q.empty()){
		node x=q.front();q.pop();
		int i=x.i,j=x.j,k=x.k,ni,nj,nk;
		ni=i+(a[i+1]=='('); //加个左括号，这样写可以精简代码的说~
		nj=j+(b[j+1]=='(');
		nk=k+1;
		if(nk<=n+m&&f[ni][nj][nk].i==-1){ //记忆化的思路，没走过才能走
			f[ni][nj][nk]=x;
			q.push((node){ni,nj,nk});
		}
		ni=i+(a[i+1]==')'); //加个右括号
		nj=j+(b[j+1]==')');
		nk=k-1;
		if(nk>=0&&f[ni][nj][nk].i==-1){
			f[ni][nj][nk]=x;
			q.push((node){ni,nj,nk});
		}
	}
}

signed main(){
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);m=strlen(b+1);
	bfs();
	int i=n,j=m,k=0;
	while(i||j||k){ //回溯
		node nxt=f[i][j][k];
		if(nxt.k<k) ans="("+ans;
		else ans=")"+ans;
		i=nxt.i;j=nxt.j;k=nxt.k;
	}
	cout<<ans;
}
```

---

