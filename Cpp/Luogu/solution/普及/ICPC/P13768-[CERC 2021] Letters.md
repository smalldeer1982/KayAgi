# [CERC 2021] Letters

## 题目描述

Martin 正在听一场关于线性代数的讲座。毋庸置疑，正在讲课的教授是整个宇宙中最无聊的人。黑板上写着一个 $N \times M$ 的矩阵。矩阵中的某些位置是字母（英文字母），而其他位置是空白。下面是一个 $6 \times 8$ 的矩阵示例：

$\begin{bmatrix} k & l & & n & d & i & \\ & & & & c \\  & & & & & i & h \\ j & & a \\ & c & b \\ & c & & & & e & f \end{bmatrix}.$

Martin 完全不知道这个矩阵代表什么。他太无聊了，已经有 30 分钟没有听讲了。不过，Martin 有着极其丰富的想象力。他想象这个矩阵突然受到了重力的影响，所有字母都会向下滑动，直到每个字母“到达底部”或“碰到它下方的字母”为止。在第一阶段，上面的矩阵会变成：

$\begin{bmatrix} \\ \\ \\ & & l & & & i \\ k & & c & a & & d & i & h \\ j & & c & b & n & c & e & f \end{bmatrix}.$

之后，重力改变了方向，现在把字母拉向左边。我们进入了第二阶段。同样，所有字母都会向左滑动，直到每个字母“到达左括号”或“碰到它左边的字母”为止。前面的矩阵变为：

$\begin{bmatrix} l & i \\ k & c & a & d & i & h \\ j & c & b & n & c & e & f \end{bmatrix}.$

Martin 在脑海中不断进行这个过程，直到这场无聊的讲座结束。当然，在每个阶段之后，也就是所有字母都到达各自位置后，重力可能会改变方向（方向有四种可能：左、右、上和下）。

### 任务

编写一个程序，根据重力方向变化的精确序列，确定所有字母在矩阵中的最终位置。

## 说明/提示

### 输入范围

- $1 \leq N, M \leq 100$
- $0 \leq K \leq 100$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 8 5
DLURD
k.l.ndi.
.....c..
......ih
j..a....
..cb....
..c...ef```

### 输出

```
........
........
........
......hf
..iadice
.lkcbnjc```

## 样例 #2

### 输入

```
3 3 0
a..
.b.
..x```

### 输出

```
a..
.b.
..x```

# 题解

## 作者：__CuSO4__ (赞：1)

[目前最优解+代码最短](https://www.luogu.com.cn/record/233123748)

一道简单的模拟题，按照题意分别处理每种重力的方向即可。

具体地：

1. 先找出每一行/列的所有非空的字符，按照顺序存到一个临时数组内。
2. 按照重力方向，临时数组中的字符依次放到这一行/列的不同端点，其他的字符设为 `.`。

每种情况虽然大体上代码相同，但是要注意的点还是比较多的，对于循环的顺序与边界要想清楚。

代码如下：

```cpp line-numbers
#include <iostream>
using namespace std;

int n,m,q;
char a[105],b[105],ch[105][105];

int main(){
    cin>>n>>m>>q;
    for (int i=1;i<=q;i++) cin>>a[i];
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) cin>>ch[i][j];
    for (int i=1;i<=q;i++){
        if (a[i]=='L'){
            for (int j=1,p=0;j<=n;j++,p=0){
                for (int k=1;k<=m;k++) if (ch[j][k]!='.') b[++p]=ch[j][k];
                for (int k=1;k<=m;k++) ch[j][k]=(k<=p?b[k]:'.');
            }
        }
        if (a[i]=='R'){
            for (int j=1,p=m;j<=n;j++,p=m){
                for (int k=m;k>=1;k--) if (ch[j][k]!='.') b[p--]=ch[j][k];
                for (int k=m;k>=1;k--) ch[j][k]=(k>p?b[k]:'.');
            }
        }
        if (a[i]=='U'){
            for (int k=1,p=0;k<=m;k++,p=0){
                for (int j=1;j<=n;j++) if (ch[j][k]!='.') b[++p]=ch[j][k];
                for (int j=1;j<=n;j++) ch[j][k]=(j<=p?b[j]:'.');
            }
        }
        if (a[i]=='D'){
            for (int k=1,p=n;k<=m;k++,p=n){
                for (int j=n;j>=1;j--) if (ch[j][k]!='.') b[p--]=ch[j][k];
                for (int j=n;j>=1;j--) ch[j][k]=(j>p?b[j]:'.');
            }
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++) cout<<ch[i][j];
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：zyr2011 (赞：1)

### 题目解法
模拟题，~~这时限真的要开那么高吗？~~，对于左移，我们直接遍历一遍各行，如果左边**不是 ```.``` 而是字母**的话，我们直接加入一个字符串 $ans$ 中，然后用将这一行的**前面**的字符替换为 $ans$ 内的字符，直到 $ans$ 内所有字符都在这一行中，剩下的地方用 ```.``` 来填补。右移也是一样的，只不过更新时**要换一个方向**。对于上升和下降，我们遍历与更新的**是列不是行**，其余细节也大致相同，这里也就~~懒得写~~不详细展开了。  
记得对 $k = 0$ 的情况特判。
### 满分代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
const int N=100+10;
string a[N];
int n,m,k;
inline void solve(char op){
	if(op=='L'){
		for(re int i=0;i<n;++i){
			string ans;
			for(re int j=0;j<m;++j){
				if(a[i][j]!='.'){
					ans+=a[i][j];//是字母，加进ans 
				}
			}
			string d(m,'.');
			for(re int j=0;j<ans.size();++j){
				d[j]=ans[j];//更新 
			}
			a[i]=d;
		}
	} 
	else if(op=='R'){
		for(re int i=0;i<n;++i){
			string ans;
			for(re int j=0;j<m;++j){
				if(a[i][j]!='.'){
					ans+=a[i][j];
				}
			}
			string d(m,'.');
			int sum=m-ans.size();
			for(re int j=0;j<ans.size();++j){
				d[sum+j]=ans[j];//记得换一个方向！！ 
			}
			a[i]=d;
		}
	} 
	else if(op=='U'){
		for(re int i=0;i<m;++i){
			string ans;
			for(re int j=0;j<n;++j){
				if(a[j][i]!='.'){
					ans+=a[j][i];
				}
			}
			for(re int j=0;j<n;++j){
				if(j<ans.size()){
					a[j][i]=ans[j];
				}
				else{
					a[j][i]='.';
				}
			}
		}
	}
	else if(op=='D'){
		for(re int i=0;i<m;++i){
			string ans;
			for(re int j=0;j<n;++j){
				if(a[j][i]!='.'){
					ans+=a[j][i];
				}
			}
			int sum=n-ans.size();
			for(re int j=0;j<n;++j){
				if(j>=sum){
					a[j][i]=ans[j-sum];//换一个方向 
				}
				else{
					a[j][i]='.';
				}
			}
		}
	}//别忘了上升和下降遍历的是列！ 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	if(k==0){
		for(re int i=0;i<n;++i){
			cin>>a[i];
		}
		for(re int i=0;i<n;++i){
			cout<<a[i]<<"\n";
		}
		return 0;
	}//k=0的特判 
	string s;cin>>s;
	for(re int i=0;i<n;++i){
		cin>>a[i];
	}
	for(re int i=0;i<s.size();++i){
		solve(s[i]);
	}//根据操作序列移动 
	for(re int i=0;i<n;++i){
		cout<<a[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：liuyuantao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13768)

观察到数据范围不大，所以我们考虑模拟。

考虑字符所对应的操作。  
* $\texttt{L,R}$：对于 $\texttt{L}$，每一行最左侧的字母将会触边，位于行首，其它字母将会位于其左侧的字母右侧。所以我们枚举行号 $i$，对于行中位于第 $j$ 位的字母，将其移动到最靠左的非空位置。显然这可以用一个变量维护。$\texttt{R}$ 反过来即可。
* $\texttt{U,D}$：对于 $\texttt{U}$，每一列最上方的字母将会触顶，位于列首，其它字母将会位于其上方的字母下方。所以我们枚举列号 $i$，对于列中位于第 $j$ 位的字母，将其移动到最靠上的非空位置。$\texttt{D}$ 反过来即可。

总时间复杂度 $O(nmk)$。  

[本题一血](https://www.luogu.com.cn/record/232000035)
```cpp line-numbers
#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define PII pair<LL,LL>

const int N=1e2+5;
LL mod=1e9+7;

LL inf=0x7fffffffff;
LL T,n,m,ans,cnt;
char ch[N][N],cg[N][N];
string s;

inline LL read(){
	char cg=getchar();
	LL x=0;
	while(cg<'0'||cg>'9')cg=getchar();
	while(cg>='0'&&cg<='9'){
		x*=10;
		x+=cg-'0';
		cg=getchar();
	}
	return x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>T;
	if(T>0)cin>>s;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>cg[i][j];
		}
	}
	for(int t=0;t<T;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				ch[i][j]=cg[i][j];
			    cg[i][j]='.';
			}
		}
		switch(s[t]){
			case 'L':{
				for(int i=1;i<=n;i++){
					cnt=0;
					for(int j=1;j<=m;j++){
						if(ch[i][j]!='.'){
							cg[i][++cnt]=ch[i][j];
						}
					}
				}
				break;
			}
			case 'R':{
				for(int i=1;i<=n;i++){
					cnt=m+1;
					for(int j=m;j>=1;j--){
						if(ch[i][j]!='.'){
							cg[i][--cnt]=ch[i][j];
						}
					}
				}
				break;
			}
			case 'U':{
				for(int i=1;i<=m;i++){
					cnt=0;
					for(int j=1;j<=n;j++){
						if(ch[j][i]!='.'){
							cg[++cnt][i]=ch[j][i];
						}
					}
				}
				break;
			}
			case 'D':{
				for(int i=1;i<=m;i++){
					cnt=n+1;
					for(int j=n;j>=1;j--){
						if(ch[j][i]!='.'){
							cg[--cnt][i]=ch[j][i];
						}
					}
				}
				break;
			}
		}
    }
	for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
		    cout<<cg[i][j];
		}
		cout<<'\n';
	}
		
	return 0;
}
```

---

## 作者：HuangYuBo096 (赞：0)

[AC Record](https://www.luogu.com.cn/record/232571032)

这是蒟蒻的第一篇题解，望管理过审qwq

### 题目大意

给定一个 $N \times M$ 的字符矩阵，有 $K$ 次操作。每次操作要求将矩阵内的所有字符堆到特定的一边。

输入 $N,M,K$ ，操作字符串（在我的代码中记为 $o$ ，包含 L, R, U 和 D四种字符）和字符矩阵，求出 $K$ 次操作后的矩阵。

### 题目思路

先看数据范围。

+ $0 \leq N,M \leq 100$ ；
+ $K \leq 100$ ；
+ 时间限制为 $2.00 s$ 。
  
数据范围比较小，考虑模拟解决。

每次操作时，写4个 `if` ，判断为操作 L, R, U 还是 D 。

每一个 `if` 中：
+ 枚举每一个格子；
+ 如果这个格子没有字母（即为 `.` ），就跳过；
+ 如果这个格子有字母（不为 `.` ），就把这个字符往操作规定的方向推，推到不能再推（下一个格子超出边界，或有字母）为止。

::::warning[注意]
这种做法应该保证当前被操作字符的前面所有字符（如果有）都被推到对应的位置上，所以应当对循环顺序做一些调整，以保证先枚举到需要优先操作的字符。
::::

最后，输出答案即可。

### AC Code

::::info[一些关于代码的要点]
+ 当 $K = 0$ 时，我们不需要读入 $o$ ,需要进行特判；
+ 注意题目的输入与输出中没有空格。
::::

```c++ line-numbers
#include<bits/stdc++.h>
using namespace std;
char arr[110][110];
long long n,m,k;
string o;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>k;
    if(k!=0){
        cin>>o;
    }
    for(long long i=1;i<=n;i++){
        string s;
        cin>>s;
        for(long long j=1;j<=m;j++){
            arr[i][j]=s[j-1];
        }
    }
    for(long long c=0;c<k;c++){
        char op=o[c];
        if(op=='L'){
            for(long long i=1;i<=n;i++){
                for(long long j=1;j<=m;j++){
                    if(arr[i][j]=='.')continue;
                    for(long long pos=j;pos>1;pos--){
                        if(arr[i][pos-1]=='.'){
                            arr[i][pos-1]=arr[i][pos];
                            arr[i][pos]='.';
                        }else{
                            break;
                        }
                    }
                }
            }
        } 
        else if(op=='R'){
            for(long long i=1;i<=n;i++){
                for(long long j=m;j>=1;j--){
                    if(arr[i][j]=='.')continue;
                    for(long long pos=j;pos<m;pos++){
                        if(arr[i][pos+1]=='.'){
                            arr[i][pos+1]=arr[i][pos];
                            arr[i][pos]='.';
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        else if(op=='U'){
            for(long long j=1;j<=m;j++){
                for(long long i=1;i<=n;i++){
                    if(arr[i][j]=='.') continue;
                    for(long long pos=i;pos>1;pos--){
                        if(arr[pos-1][j]=='.'){
                            arr[pos-1][j]=arr[pos][j];
                            arr[pos][j]='.';
                        }else{
                            break;
                        }
                    }
                }
            }
        }
        else{
            for(long long j=1;j<=m;j++){
                for(long long i=n;i>=1;i--){
                    if(arr[i][j]=='.')continue;
                    for(long long pos=i;pos<n;pos++){
                        if(arr[pos+1][j]=='.'){
                            arr[pos+1][j]=arr[pos][j];
                            arr[pos][j]='.';
                        }else{
                            break;
                        }
                    }
                }
            }
        }
    }
    for(long long i=1;i<=n;i++){
        for(long long j=1;j<=m;j++){
            cout<<arr[i][j];
        }
        cout<<endl;
    }
    return 0;
}
```

谢谢大家！

---

## 作者：lizongrui000 (赞：0)

### 题目分析
输入一个长度 $k$ 的字符串，再输入一个 $n \times m$ 的字符矩阵，根据字符串的每个字母进行操作：当字母表示为向左时，让矩阵中的所有字母向左滑动，碰到边框或其他字母停下。向右、上、下时同理。
### 代码思路
按题目描述输入，注意 $k=0$ 时就不输入字符串。
```cpp
int n,m,k;
cin>>n>>m>>k;
string s;
if(k) cin>>s;
char a[105][105];
for(int i=1;i<=n;++i)
{
    for(int j=1;j<=m;++j)
    {
        cin>>a[i][j];
    }
}
for(int l=0;l<s.size();++l)
{
    //省略部分代码，在下面会写
}
```
然后写循环来判断字符串中的每个字母。当向左滑动时，因为最左边一列不会移动，因此从 $j=2$ 开始枚举每个字符，$i$ 正常。如果这个字符从最左边开始到 $j-1$ 中有空的位置，就将该字符移动到空的位置，原位置变为空，之后直接结束循环。
```cpp
if(s[l]=='L')
    for(int i=1;i<=n;++i)
        for(int j=2;j<=m;++j)
            if(a[i][j]!='.')
                for(int L=1;L<j;++L)
                    if(a[i][L]=='.'){
                        a[i][L]=a[i][j];
                        a[i][j]='.';
                        break;
                    }
```
接下来判断向右移动，$j=m-1$ 开始枚举，这个字符从最右边开始判断，直到 $j+1$，之后便和向左滑动同理。
```cpp
if(s[l]=='R')
    for(int i=1;i<=n;++i)
        for(int j=m-1;j>=1;--j)
            if(a[i][j]!='.')
                for(int r=m;r>j;--r)
                    if(a[i][r]=='.')
                    {
                        a[i][r]=a[i][j];
                        a[i][j]='.';
                        break;
                    }
```
向上判断则是从 $i=2$ 开始，$j$ 正常，从这一列最上面开始，直到 $i+1$，之后也同理。
```cpp
if(s[l]=='U')
    for(int i=2;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(a[i][j]!='.')
                for(int u=1;u<i;++u)
                    if(a[u][j]=='.')
                    {
                        a[u][j]=a[i][j];
                        a[i][j]='.';
                        break;
                    }
```
之后是向下判断。从 $i=n-1$ 开始，从这一列最下面开始判断，直到 $i-1$，之后同理。
```cpp
if(s[l]=='D')
    for(int i=n-1;i>=1;--i)
        for(int j=1;j<=m;++j)
            if(a[i][j]!='.')
                for(int d=n;d>i;--d)
                    if(a[d][j]=='.')
                    {
                        a[d][j]=a[i][j];
                        a[i][j]='.';
                        break;
                    }
```
最后输出即可。
```cpp
for(int i=1;i<=n;++i)
{
    for(int j=1;j<=m;++j)
        cout<<a[i][j];
    cout<<endl;
}
```

---

