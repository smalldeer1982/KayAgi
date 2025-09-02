# Not Quite Latin Square

## 题目描述

拉丁方阵是一个 $3 \times 3$ 的网格，由字母 $\texttt{A}$、$\texttt{B}$ 和 $\texttt{C}$ 组成，满足以下条件：

- 每一行中，字母 $\texttt{A}$、$\texttt{B}$ 和 $\texttt{C}$ 各出现一次；
- 每一列中，字母 $\texttt{A}$、$\texttt{B}$ 和 $\texttt{C}$ 各出现一次。

例如，下面是一个可能的拉丁方阵：
$$
\begin{bmatrix}
\texttt{A} & \texttt{B} & \texttt{C} \\
\texttt{C} & \texttt{A} & \texttt{B} \\
\texttt{B} & \texttt{C} & \texttt{A} \\
\end{bmatrix}
$$
现在，给你一个拉丁方阵，但其中有一个字母被问号 $\texttt{?}$ 替换了。请你找出被替换的字母。

## 说明/提示

三个测试用例的正确拉丁方阵如下所示：

$$
\begin{bmatrix}
\texttt{A} & \texttt{B} & \texttt{C} \\
\texttt{C} & \color{red}{\texttt{A}} & \texttt{B} \\
\texttt{B} & \texttt{C} & \texttt{A} \\
\end{bmatrix}
\quad
\begin{bmatrix}
\texttt{B} & \texttt{C} & \texttt{A} \\
\texttt{C} & \texttt{A} & \color{red}{\texttt{B}} \\
\texttt{A} & \texttt{B} & \texttt{C} \\
\end{bmatrix}
\quad
\begin{bmatrix}
\color{red}{\texttt{C}} & \texttt{A} & \texttt{B} \\
\texttt{B} & \texttt{C} & \texttt{A} \\
\texttt{A} & \texttt{B} & \texttt{C} \\
\end{bmatrix}
$$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
ABC
C?B
BCA
BCA
CA?
ABC
?AB
BCA
ABC```

### 输出

```
A
B
C```

# 题解

## 作者：DrAlfred (赞：1)

摘要：位运算，模拟

[传送门：https://www.luogu.com.cn/problem/CF1915B](https://www.luogu.com.cn/problem/CF1915B)

## 题意

Latin 矩阵是一个 $3 \times 3 $ 的，每一行、每一列都各有一个 $ \texttt{A} $，$ \texttt{B} $ 和 $ \texttt{C} $ 的矩阵。

$ t $ 组数据。每次输入一个残缺的 Latin 矩阵（缺失位置用 $\texttt{?}$ 表示），求缺失的位置是什么字母。

## 分析思路

利用异或的性质。两个相同的字符异或和为 $ 0 $；$ 0 $ 异或一个字符这个字符本身。

所以将 $ \texttt{A} $，$ \texttt{B} $ 和 $ \texttt{C} $ 异或起来，然后异或上 $ \texttt{?} $ 所处那一行或那一列剩下的两个字符，即可得答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline void solve(void) {
    char c[3][3];
    int x = 0, y = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> c[i][j];
            if (c[i][j] == '?') x = i, y = j;
        }
    }
    char A = 'A' ^ 'B' ^ 'C';
    for (int i = 0; i < 3; i++) {
        if (i != y) A ^= c[x][i];
    }
    cout << A << endl;
}
int main(int argc, char const *argv[]) {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Jasoncwx (赞：1)

[题目传送门！](/problem/CF1915B)
## 题目思路
我们只需要判断哪一行有问号，然后输出这一行没出现过的那个字母即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        for(int i=1;i<=3;i++){
            string s;cin>>s;
            if(s.find("?")!=std::string::npos){//这一行有问号
                if(s.find("A")==std::string::npos)cout<<"A";//没有A
                if(s.find("B")==std::string::npos)cout<<"B";//没有B
                if(s.find("C")==std::string::npos)cout<<"C";//没有C
                cout<<endl;
            }
        }
    }
}
```


---

## 作者：封禁用户 (赞：0)

# CF1915B

## 题意

给出一个 $3$ 行 $3$ 列的字符矩形，其中每行都有字符 `ABC` 各一个组成，现有一个字符未知，求出未知字符。

## 思路

就是说每个字符都应该出现 $3$ 次，所以我们只要找到出现两次的字符即可。

## AC Code
```
#include<bits/stdc++.h>
using namespace std;
int t;
char a[10][10];
int main() {
	cin>>t;
	while(t--){
		int f[4]={0};
		  for(int i=1;i<=3;i++)
            for(int i=1;i<=3;i++){
                char c;
				cin>>c;
                f[c-'A'+1]++;
            }
		for(int i=1;i<=3;i++){
			if(f[i]==2){
				cout<<char(i+'A'-1)<<endl;
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 思路
简单判断，首先在整个矩阵中找出一个问号，这个很好实现，然后在那一行找一下 ``A B C`` 哪个没有出现过就可以了，实现非常简单，多组数据记得初始化。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
 
int mp[10][10];
 
int main()
{
	int t;
	cin >> t;
	while(t--){
		memset(mp, 0, sizeof(mp));
		for(int i = 1; i <= 3; i++){
			for(int j = 1; j <= 3; j++){
				char a;
				cin >> a;
				if(a == 'A'){
					mp[i][j] = 1;
				} 
				else if(a == 'B'){
					mp[i][j] = 2;
				}
				else if(a == 'C'){
					mp[i][j] = 3;
				}
				else{
					mp[i][j] = -1;
				}
			}
		}
		for(int i = 1; i <= 3; i++){
			bool if_a = false, if_b = false, if_c = false;
			for(int j = 1; j <= 3; j++){
				if(mp[i][j] == -1){
					for(int k = 1; k <= 3; k++){
						if(mp[i][k] == 1){
							if_a = true;
						}
						else if(mp[i][k] == 2){
							if_b = true;
						}
						else if(mp[i][k] == 3){
							if_c = true;
						}
					}
					if(if_a && if_b){
						cout << "C" << endl;
					}
					else if(if_b && if_c){
						cout << "A" << endl;
					}
					else{
						cout << "B" << endl;
					}
				}
			}
		}
	} 
	return 0;
}
 
```


---

## 作者：gaojizhe05 (赞：0)

# 题目大意
给定一个 $3$ 行 $3$ 列的矩阵，每行每列都由 ```A B C```构成，每个字母都会出现且只会出现 $1$ 次。现在有一个字母未知，要求出它。
# 题目分析
因为矩阵每行每列都是由 ```A B C``` 构成，所以一个矩阵中每个字母都会出现 $3$ 次。

因此，我们可以统计每个字母出现的次数，**只出现了两次的那个字母就是被替换的字母**。
# 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
char c;//读入字母
int t,cnt[4];//cnt存每个字母出现的次数
int main(){
    cin>>t;//读入组数
    while(t--){
        for(int i=0;i<3;i++) cnt[i]=0;//cnt初始化
        for(int i=1;i<=3;i++)
            for(int i=1;i<=3;i++){
                cin>>c;//读入字母
                cnt[c-'A']++;//计数增加
            }
        for(int i=0;i<3;i++)
            if(cnt[i]==2){//只出现了两次的字母
                putchar('A'+i);
                cout<<endl;//输出
            }
    }
    return 0;
}
``````

---

## 作者：zhouzihang1 (赞：0)

# CF1915B Not Quite Latin Square 题解

###### ~~这是小型数独？~~

[洛谷链接](https://www.luogu.com.cn/problem/CF1915B)

[CF 链接](https://codeforces.com/problemset/problem/1915/B)

[MyBlog](https://www.luogu.com.cn/blog/827018/cf1915b-not-quite-latin-square-ti-xie)

## 思路

分析一下，每次输入一个 $3 \times 3$ 的字符数独，其中包含一个 `?`，问题是 `?` 代替的字符是 ```A B C``` 中的哪一个？

思路是很简单的，找出每一个数独中 `?` 的位置，记录下它所在的列（行也可以），然后遍历它所在的列的所有字符，找出 `?` 代替了哪一个字符。

对于如何找出 `?` 代替的字符，我们可以找出这一列里有哪些字符，就可以知道没有那个字符了。

## 核心代码

```cpp
string s[4];
bool flag[100];
void solve()
{
	memset(flag,0,sizeof(flag));
    //注意清空数组，不然会答案错误
	for(int i=1;i<=3;i++) cin>>s[i];
	int pos;
	for(int i=1;i<=3;i++)
		for(int j=0;j<3;j++)
			if(s[i][j]=='?') pos=j;
    //找出 '?' 所在的列。
	for(int i=1;i<=3;i++)
		flag[(int)s[i][pos]]=1;
    //flag 中将 ABC 的ASCll码赋值为 1 表示出现过
	for(int i='A';i<='C';i++)
		if(!flag[i]) cout<<(char)i<<endl;
    //如果没出现过就输出
}
```

---

## 作者：coderJerry (赞：0)

### 题目大意
$t$ 组数据，每次给出一个 $3\times3$ 的矩阵，其中一个字符是 ```?```。矩阵满足：每行每列有且仅有各 $1$ 个 ```A B C```，求出 ```?``` 代表的字符。
### 题目分析
~~毕竟是 div4，所以思路简单~~。因为矩阵每行有且仅有各 $1$ 个 ```A B C```，所以我们可以先找出 ```?``` 所在的这一行，接下来遍历一整行，```A B C``` 哪个没有就输出谁（可以用 ```bool``` 变量来记录）。
### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t,line;
	char a[4][4];
	bool fa,fb,fc;
	cin>>t;
	while(t--){
		fa=fb=fc=0; 
		for(int i=1;i<=3;i++){
			for(int j=1;j<=3;j++){
				cin>>a[i][j];
				if(a[i][j]=='?') line=i;
                                //找出“？”在哪一行
			}
		}
		for(int i=1;i<=3;i++){
			if(a[line][i]=='A') fa=1;
			if(a[line][i]=='B') fb=1;
			if(a[line][i]=='C') fc=1;
		} 
		if(!fa) cout<<"A\n";
		if(!fb) cout<<"B\n";
		if(!fc) cout<<"C\n";
	}
	return 0;
}
```


---

