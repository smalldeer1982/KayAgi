# Upscaling

## 题目描述

给你一个整数 $n$，输出一个 $2n \times 2n$ 的棋盘，由 $2 \times 2$ 的 `#` 与 $2 \times 2$ 的 `.` 构成，最左上角的单元格为 $2 \times 2$ 的 `#` 构成。

## 样例 #1

### 输入

```
4
1
2
3
4```

### 输出

```
##
##
##..
##..
..##
..##
##..##
##..##
..##..
..##..
##..##
##..##
##..##..
##..##..
..##..##
..##..##
##..##..
##..##..
..##..##
..##..##```

# 题解

## 作者：ljk8886 (赞：3)

## 题目大意

有 $t$ 组数据，每组数据包含一个 $n$。要求输出如题面中的 $2n \times 2n$ 的方阵。

## 题目分析

因为 $2n \times 2n$ 的方阵处理起来比较复杂，所以我们可以将其简化成 $n \times n$ 的方阵，每个点就相当于一个 $2 \times 2$ 的方阵。观察一下，我们可以发现它是两个字符交替排列，也就相当于告诉我们：

- 若当前行数为奇数，那么奇数列是 `#`，偶数列是 `.`。

- 若当前行数为奇数，那么奇数列是 `.`，偶数列是 `#`。

现在回归到问题，由于是 $2n$ 行，那么就是要判断当前行数加一再除以二是否为奇数或偶数了，这里要不要加一取决于你的第一行是 $0$ 还是 $1$。下面给到代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n;
int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i = 1; i <= 2 * n; i++) //有2*n行 
		{
			int x = (i + 1) / 2; // 我是从1开始的，所以要加1 
			if (x & 1) 
			{
				for (int j = 1; j <= 2 * n; j++) //有2*n列 
				{
					x = (j + 1) / 2;
					if (x & 1) cout << "#"; //如果x是奇数，就输出# 
					else cout << "."; //如果x是偶数，就输出. 
				}
			}
			else //同上 
			{
				for (int j = 1; j <= 2 * n; j++)
				{
					x = (j + 1) / 2;
					if (x & 1) cout << ".";
					else cout << "#";
				}
			}
			cout << endl; //要换行 
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

## Description

给定正整数 $n$，输出如图所示的矩阵。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1950B/883bc02f0b7d07cb0bca7d12d6264453443bc86b.png)

## Solution

我们把整个矩阵的每两行划为一块来讨论，即整个矩阵一共分为 $n$ 行。首先，可以看到从上往下数的每个**奇数行**的行首为 `#`，每个**偶数行**的行首为 `.`。然后在每一行中，两个 `#` 和两个 `.` 交替出现，每行一共 $2n$ 个字符。

在具体代码实现中，先循环每一（两行），再循环每一列就可以。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
using namespace std;
int n;
il void solve()
{
	cin>>n;
	char flag='#'; //当前该输出的字符 
	for(int i=1;i<=n;++i) //循环块 
	{
		for(int line=1;line<=2;++line) //一块有相同的2行 
		{
			flag=(i&1 ? '#' : '.'); //根据行数的奇偶性判断flag 
			for(int j=1;j<=n;++j) //循环列 
			{
				putchar(flag),putchar(flag); //输出2次 
				flag=(flag=='.' ? '#' : '.'); //交替
			}
			putchar('\n'); //一行输完之后换行
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：MhxMa (赞：1)

[更好的阅读体验](https://blog.mhxma.tech/2024/04/03/tijie-CF1950B/)

题目要求根据给定的整数 $n$，输出一个 $2n \times 2n$ 的棋盘，其中每个 $2 \times 2 $的小方块交替使用  `#` 和 `.` 构成。

模拟即可，用一个 `flag` 表示当前应该使用 `#` 还是 `.`，使用两层循环来生成棋盘，每次循环是，先根据 `flag` 的值输出当前行的两个方块，然后翻转 `flag` 的值，以便下一行使用相反的符号。  

每输出完一行，根据 $n$ 的奇偶性来更新 `flag` 的值，使得下一行的开头与当前行的结尾相反即可，时间复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        bool flag = true;

        for (int i = 0; i < 2 * n; i += 2) {
            for (int j = 0; j < 2 * n; j += 2) {
                if (flag)
                    cout << "##";
                else
                    cout << "..";
                flag = !flag;
            }
            cout << endl;
            
            if (n % 2)
                flag = !flag;
                
            for (int j = 0; j < 2 * n; j += 2) {
                if (flag)
                    cout << "##";
                else
                    cout << "..";
                flag = !flag;
            }
            cout << endl;

            if (n % 2 == 0)
                flag = !flag;
        }
    }
    return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# CF1950B Upscaling 题解

建议评红。

考察知识点：你的细心和耐心。

### 翻译

你需要输出一个 $2n\times 2n$ 的方阵。这个方阵是由 $n\times n$ 个小方阵组成的，它们可能是如下的两种情况：

1. 

```
##
##
```

2.

```
..
..
```

你需要保证这两种方阵交替输出且左上角的方阵是第一种。

### 解析

按照题意模拟输出即可。

注意每次输出是第一种还是第二种即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
void solve(bool x){
	for(int i=1;i<=n;i++){
		if(x==1){ //先输出第一种
			if(i%2==1){
				cout<<"##";
			}
			else{
				cout<<"..";
			}
		}
		else{ //先输出第二种
			if(i%2==1){
				cout<<"..";
			}
			else{
				cout<<"##";
			}
		}
	} 
	cout<<"\n";
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=2;j++){
				solve(i&1);
			}
		} 
	}
return 0;
}
```

---

## 作者：louliu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1950B)

### 分析

我们先来看看样例图片：

![样例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1950B/883bc02f0b7d07cb0bca7d12d6264453443bc86b.png)

我们就会发现每四个格子为一组，那我们将纵坐标与横坐标都除以二，那是不是就更好做了呢？

当然我们还能发现一个规律（改变后）：

1. 纵坐标为偶数，且横坐标为偶数，输出 $#$。

1. 纵坐标为奇数，且横坐标为偶数，输出点。

1. 纵坐标为偶数，且横坐标为奇数，输出点。

1. 纵坐标为奇数，且横坐标为奇数，输出 $#$。

##### 点指 $.$!

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>b;
		for(int j=0;j<b*2;j++){
			for(int k=0;k<b*2;k++){
				if((j/2)%2==0){
					if((k/2)%2==0){//我们要维持改变后的值，所以要两两为一组，否则就是n*n的图
						cout<<"#";
					}
					else cout<<".";
				}
				else{
					if((k/2)%2==1){
						cout<<"#";
					}
					else cout<<".";
				}
			}	
			cout<<"\n";		
		}
	}
	return 0;
}


```

建议升橙！

---

## 作者：nyC20 (赞：0)

# 思路
首先我们需要明确一点，如果 $i$ 是一个奇数，且 $1 \le i \le n$，那么第 $i$ 行和第 $i+1$ 行一样，第 $i$ 列和第 $i+1$ 列一样，所以我们可以把每一个 $2 \times 2$ 的小方格看成一个点来进行循环，输出时输出两遍就行了。然后我们判断这个点的行和列的奇偶，可以分为以下四种情况：

- 奇行奇列，这个点是 `#`。
- 奇行偶列，这个点是 `.`。
- 偶行奇列，这个点是 `.`。
- 偶行偶列，这个点是 `#`。

然后输出即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
void print(){
	for(int i=1;i<=n;i++){//行 
		for(int j=1;j<=2;j++){//两遍
			if(i&1){
				for(int k=1;k<=n;k++){
					if(k&1)printf("##");//奇行奇列 
					else printf("..");//奇行偶列 
				}
			}
			else {
				for(int k=1;k<=n;k++){
					if(k&1)printf("..");//偶行奇列 
					else printf("##");//偶行偶列 
				}
			}
			printf("\n");
		}
	}
}
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		print();
	}
	return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
共 $t$ 组数据。

每组数据给定 $n$，输出一个由 $2\times 2$ 的 `#` 和 $2\times 2$ 的 `.` 交错构成的棋盘，保证棋盘左上角为 `#`。
# 思路
不妨先将 $2\times 2$ 的小格子看作 $1\times1$ 的小格子。

用变量 $res$ 存储当前格子的状态，令其初值为 $1$（用 $1$ 代指 `#`，$0$ 代指 `.`）。

分类讨论奇数和偶数。

$n$ 为奇数时，若将一行行的格子排成一行不难发现 `#` 和 `.` 是交替出现的，所以只需要每次输出一个格子后让 $res$ 异或 $1$，然后每输出 $n$ 个格子换行即可。

$n$ 为偶数时，若按上述方法将棋盘压成一行会发现 `#` 和 `.` 依然交替不过每过 $n$ 格后会停止交替一次。于是可先按奇数方案输出，不过每次换行时不使 $res$ 的值改变即可。

最后，将上述思路改为对于每行格子输出两行相同格子，然后每次输出两个相同字符即可。
# 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const char s[2]={'.','#'};

int t,n;

inline void solve(){
    
    int res=1;

    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        for(int k=1;k<=2;k++){
            for(int j=1;j<=n;j++){
        
                printf("%c%c",s[res],s[res]);
                res^=1;
            }
            puts("");
            if(n&1)res^=1;
        }
        res^=1;
    }
}

main(){

    scanf("%d",&t);

    while(t--)
        solve();

    return 0;
}
```

---

## 作者：_dbq_ (赞：0)

## 前言
没读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF1950B)先读题。

## 题目大意
有 $T$ 组数据，每组数据给定一个 $n$，要求给出符合要求的 $2n*2n$ 的矩阵。

## 思路
通过观察可以发现，整个图形是用 $n*n$ 个大小为 $2*2$ 的矩阵组成的。矩阵有两种形式，分别为全是 ```#``` 和全是 ```.```的。当一个位置的行列坐标同奇偶时，这个位置放全是 ```#``` 的矩阵，否则就放全是 ```.``` 的矩阵。

## 代码
```cpp
#include<iostream>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
inline int read(){//快读
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    #ifdef dbq
    freopen("CF1950B.in","r",stdin);
    freopen("CF1950B.out","w",stdout);
    #endif
    int T=read();//T组数据
    while(T--)
    {
    	cint n=read();//读入n
    	for(int i=1;i<=n;i++)//放n行2*2的矩阵
    		for(int k=1;k<=2;k++)//每个矩阵的第一行和第二行一样
    		{
    			for(int j=1;j<=n;j++)//放n列2*2的矩阵
	    			if(i%2==j%2) cout<<"##";//同奇偶就放“#”
	    			else cout<<"..";//否则放“.”
	    		cout<<endl;//换行
    		}	
	}
    return 0;
}
```

---

## 作者：xd244 (赞：0)

一道简单模拟题，建议评橙。

从 $1$ 循环到 $n$，每次输出相同的两行，将两个一行中相同的字符看做一个，所以原问题就化成了输出 $n\times n$ 的矩阵，每一个 $\text{行数}+\text{列数}$ 的值为偶数时，输出两个 ```#```，否则输出 ```.```。

所以代码极简：
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int c=1;c<=n;c++){
            for(int _c=1;_c<=n;_c++){
                if((_c+c)%2==0)cout<<"##";
                else cout<<"..";
            }cout<<"\n";
            for(int _c=1;_c<=n;_c++){
                if((_c+c)%2==0)cout<<"##";
                else cout<<"..";
            }cout<<"\n";
        }
    }
}

```

---

## 作者：2021zjhs005 (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1950B)。

看了图片，就应该知道题意了，也就是让我们以 $2\times 2$ 的方格由 # 和 $\texttt{.}$ 相互交错排列，到了行末就换行：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1950B/883bc02f0b7d07cb0bca7d12d6264453443bc86b.png)

明显，我们可以两行并作一行看，两列并作一列看。

设行为 $line$，列为 $col$。

- $line$ 为奇数。
  - $col$ 为奇数，则这个方格由 # 组成。
  - $col$ 为偶数，则这个方格由 $\texttt{.}$ 组成。
 - $line$ 为偶数。
   - $col$ 为奇数，则这个方格由 $\texttt{.}$ 组成。
   - $col$ 为偶数，则这个方格由 # 组成。
   
明显，输出的时候不能两行一起输出，所以可以把行看作 $\lfloor \frac{i+1}{2}\rfloor$，其中 $i$ 为一行一行看的行。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int T,n;

inline void solve(){
  n=read();
  rep(i,1,n << 1){
    rep(j,1,n){
      int now = (i >> 1) + (i & 1);//等价于 (i+1)/2。
      /* 分情况讨论。*/
      if(now & 1){
         if(j & 1) pr("##");
         else pr("..");
      }
      else{
        if(j & 1) pr("..");
        else pr("##");
      }
    }
  pr("\n");
  }
}
signed main(){
  T=read();
  while(T--) solve();
}
```

---

## 作者：ny_Dacong (赞：0)

`#` 格子出现的位置：奇数行的奇数列 或者 偶数行的偶数列。否则为 `.` 格子。

然后将每个格子扩展为 $2 \times 2$ 的样子。变化前的格子 $(i,j)$ 会扩展到变化后的 $(i \times 2-1,j \times 2-1),(i \times 2-1,j \times 2),(i \times 2,j \times 2-1),(i \times 2,j \times 2)$ 这四个格子上。

接下来依次输出即可。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
bool Map[50][50];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        memset(Map,0,sizeof(Map));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i&1){
                    if(j&1){
                        Map[i*2][j*2] = 1;
                        Map[i*2][j*2-1] = 1;
                        Map[i*2-1][j*2] = 1;
                        Map[i*2-1][j*2-1] = 1;
                    }
                }else{
                    if((j&1) == 0){
                        Map[i*2][j*2] = 1;
                        Map[i*2][j*2-1] = 1;
                        Map[i*2-1][j*2] = 1;
                        Map[i*2-1][j*2-1] = 1;
                    }
                }
            }
        }
        for(int i = 1; i <= n*2; i++){
            for(int j = 1; j <= n*2; j++){
                if(Map[i][j]){
                    printf("#");
                }else{
                    printf(".");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
```

---

## 作者：Harrylzh (赞：0)

观察发现答案就是一些内部颜色相同的 $2 \times 2$ 方格黑白交替出现，一共有 $n \times n$ 个这样的方格。遍历每一个小方格，看它所属的 $2 \times 2$ 方格在几行几列，再根据奇偶性来判断黑白即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		long long n;
		scanf("%lld",&n);
		for(long long i=0;i<n*2;i++)
		{
			for(long long j=0;j<n*2;j++)
			{
				if((i/2+j/2)%2==0)
				{
					printf("#");
				}
				else printf(".");
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：hmzclimc (赞：0)

## 思路
模拟。

设答案为 $ans$，同时观察题目描述中的图片，不难发现：

- 当 $\lfloor i \div 2 \rfloor \bmod 2 =1,\lfloor j \div 2 \rfloor \bmod 2 =1$ 时，$ans(i,j) = \texttt{\#}$。
- 当 $\lfloor i \div 2 \rfloor \bmod 2 =1,\lfloor j \div 2 \rfloor \bmod 2 =0$ 时，$ans(i,j) = \texttt{.}$。
- 当 $\lfloor i \div 2 \rfloor \bmod 2 =0,\lfloor j \div 2 \rfloor \bmod 2 =1$ 时，$ans(i,j) = \texttt{.}$。
- 当 $\lfloor i \div 2 \rfloor \bmod 2 =0,\lfloor j \div 2 \rfloor \bmod 2 =0$ 时，$ans(i,j) = \texttt{\#}$。

判断一下输出即可。

## 主要代码

```cpp
void solve(){
    int n=read();
    for(int i=0;i<2*n;i++){ // 代码已经在上面解释过了
        for(int j=0;j<2*n;j++){
            if((i/2)%2==1){
                if((j/2)%2==1){
                    print("#");
                }else{
                    print(".");
                }
            }else{
                if((j/2)%2==1){
                    print(".");
                }else{
                    print("#");
                }
            }
        }
        puts("");
    }
}
```

感谢阅读，有问题请指出，谢谢。

---

