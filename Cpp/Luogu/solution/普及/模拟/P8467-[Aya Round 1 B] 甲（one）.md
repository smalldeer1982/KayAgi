# [Aya Round 1 B] 甲（one）

## 题目描述

定义长度为 $5$ 的序列 $S$ 为「好的」，当且仅当存在长度为 $5$ 的排列 $P$，满足 $S_{P_1}-1=S_{P_2}=S_{P_3}+1$ 且 $S_{P_4}=S_{P_5}$。现有一长度为 $5$ 的整数序列 $a$，满足 $0\le a_i \le 9(1\le i \le 5)$。其中 $a_1 \sim a_4$ 给定。试判断是否存在 $a_5$ 满足 $a$ 为「好的」。

其中，长度为 $5$ 的排列 $P$，指的是一个长度为 $5$ 的数列，其中 $1,2,3,4,5$ 在这个数列中出现且只出现一次。

## 说明/提示

### 附加样例

- 样例 $2$ 见下发文件中的 $\textbf{\textit{one2.in/one2.ans}}$。该样例满足测试点 $2$ 的限制。
- 样例 $3$ 见下发文件中的 $\textbf{\textit{one3.in/one3.ans}}$。该样例满足测试点 $5$ 的限制。

### 样例解释

#### 样例 \#1

- 对于第 $1$ 组数据，可以令 $a_5=8$。此时存在 $P=\{4,1,2,5,3\}$，满足 $a_{P_1}-1=a_{P_2}=a_{P_3}+1$ 且 $a_{P_4}=a_{P_5}$。故输出 $1$。
- 对于第 $2$ 组数据，可以令 $a_5=4$。此时存在 $P=\{3,2,1,4,5\}$，满足 $a_{P_1}-1=a_{P_2}=a_{P_3}+1$ 且 $a_{P_4}=a_{P_5}$。故输出 $1$。
- 对于第 $3$ 组数据，不存在可以使 $a$ 为「好的」的 $a_5$。

$$
\begin{aligned}
\fcolorbox{black}{#fbb}{3\ \ 2\ \ 8\ \ 4} + \fcolorbox{black}{yellow}{8} &\Rightarrow \fcolorbox{black}{#fbb}{2\ \ 3\ \ 4} + \fcolorbox{black}{yellow}{8\ \ 8}\ {\color{green}\sqrt{}}\\
\fcolorbox{black}{#fbb}{1\ \ 2\ \ 3\ \ 4} + \fcolorbox{black}{yellow}{4} &\Rightarrow \fcolorbox{black}{#fbb}{1\ \ 2\ \ 3} + \fcolorbox{black}{yellow}{4\ \ 4}\ {\color{green}\sqrt{}}\\
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9} +   \begin{cases}
\fcolorbox{black}{yellow}{0}\\
\fcolorbox{black}{yellow}{1}\\
\cdots\\
\fcolorbox{black}{yellow}{9}
\end{cases}&\Rightarrow
{\color{red}\xcancel{\color{black}
\begin{cases}
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9\ \ 0}\\
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9\ \ 1}\\
\cdots\\
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9\ \ 9}
\end{cases}}}
\end{aligned}
$$

### 数据范围

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|} \hline
\textbf{\textsf{测试点}} & \bm{{T\le}} & \textbf{\textsf{特殊性质}} \cr\hline
1 & 100 & \textbf{A} \cr\hline
2 & 100 & \textbf{B} \cr\hline
3 & 100 & - \cr\hline
4 & 1000 & - \cr\hline
5 & 10^5 & - \cr\hline
\end{array}
$$

- 特殊性质 $\bf A$：$a_1=a_2=a_3=a_4$。
- 特殊性质 $\bf B$：$a_1,a_2,a_3,a_4$ 互不相等。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$0\le a_i \le 9$。

## 样例 #1

### 输入

```
5
3 2 8 4
1 2 3 4
1 9 4 9
1 0 0 1
0 0 4 2```

### 输出

```
1
1
0
0
1```

# 题解

## 作者：chen_zhe (赞：26)

# 幻想乡麻将游戏

## 解法

因为 $P$ 是一个长度为 $5$ 的排列，因此我们可以将这 $5!$ 种情况全部枚举出来后，再进行对 $a$ 的枚举，逐一加以判断即可。枚举全排列可以使用 `next_permutation` 函数。对于一组数据至多要枚举 $5! \times 10=1200$ 次，而 $T \leq 10^5$，自然可以承受。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int T,a[6];
int main()
{
    cin >> T;
    while (T--)
    {
        bool flag=false;
        for (int i=1;i<=4;i++)
            cin >> a[i];
        int P[]={1,2,3,4,5};
        do
        {
            for (int i=0;i<=9;i++)
            {
                a[5]=i;
                if (a[P[0]]-1==a[P[1]] && a[P[1]]==a[P[2]]+1 && a[P[3]]==a[P[4]])
                    flag=true;
            }
        }while (next_permutation(P,P+5));
        puts(flag?"1":"0");
    }
    return 0;
}
```

当然也可以分类讨论，从手速来说好像全排列快一点。

---

## 作者：落花月朦胧 (赞：7)

# 题意

给出一个有 4 个元素的序列，询问你是否可以增加一个数使这个序列使是 「好的」。

这里对于 「好的」 的定义是：

能找到一种排列方式使这 5 个元素的序列满足下面的条件：

不妨设这个序列为 $A$。

$A_1 + 1=A_2 = A_3 - 1$ 并且 $A_4 = A_5$。

# 题解

注意到 $\forall A_i \in [0, 9]$，这个范围已经很小了，我们可以暴力枚举 $0$ 到 $9$ 所有的数为 $A_5$，然后通过排序判断即可。

对于排序判断，显然只有三种情况：

+ $A_1+1=A_2=A_3-1, A_4=A_5$
+ $A_1=A_2, A_3+1=A_4=A_5-1$
+ $A_1+1=A_2,A_3=A_4,A_4+1=A_5$

依次判断即可。

我的代码下标是从 $0$ 开始的，所以与上面的公式有所不同，你也可以从 $1$ 开始。

```cpp
void solve() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::vector<int> A = {a, b, c, d};

    for (int i = 0; i <= 9; i++) {
        auto B = A;
        B.push_back(i);
        std::sort(B.begin(), B.end());
        if (B[0] + 1 == B[1] && B[1] + 1 == B[2] && B[3] == B[4] || (B[0] == B[1] && B[2] + 1 == B[3] && B[3] + 1 == B[4])) {
            std::cout << "1\n";
            return;
        }
        if (B[0] + 1 == B[1] && B[1] == B[2] && B[2] == B[3] && B[3] + 1 == B[4]) {
            std::cout << "1\n";
            return;
        }
    }
    std::cout << "0\n";
}
```

---

## 作者：云裳 (赞：5)

## 解法

由于数据范围小，加上条件特殊，可以分类讨论。


------------

设给出的序列中的数分别是 $a_1,a_2,a_3,a_4$。

如果这组数据存在一个合法的解，那么给出的数有两种情况，分别是：

1. 序列中存在任意三个数 $a,b,c$ 使得 $a+1=b=c-1$ 。这样的话令 $a_5$ 等于设下的数便可以了，一定有解。
2. 序列中有相等的两个数 $a,b$ 。这样的话只有剩下的两个数 $c,d$ 相差 $1$ 或 $2$ 才存在有解。如果$c,d$ 相差 $1$，可以令 $a_5$ 为 $\max(c,d)+1$。如果$c,d$ 相差 $2$，可以令 $a_5$ 为 $\max(c,d)-1$。

这样的话令再 $P$ 按照题目要求的进行排列，便可以得到一个合法的解了。  

------------

有了这样一种思路，代码实现方式便基本出来了。

1. 读入，并初始化 $flag$ 为 $0$，这个待会儿会用到。
1. 从小到大排序。
1. 判断输入的数中是否存在任意三个数 $a,b,c$ 使得 $a+1=b=c-1$ 。如果存在，令 $flag$ 为 $1$，并直接输出。
1. 双重循环判断序列中是否存在相等的两个数 $a,b$ ，存在的话将 $a,b$ 设为无穷大，并退出循环。
1. 判断 $flag$ 是否为 $0$，如果 $flag$ 为 $0$，则给出的数不符合我们刚才说的两种情况，输出 $0$ 。
1. 再次从小到大排序，由于我们将给出的数中两个存在的数设为了无穷大，所以现在在序列中的前面两个便是在上方条件中第二种的 $c,d$，判断这两个数是否相差 $1$ 或 $2$。

------------

### 代码

```cpp
// by chwu
#include <bits/stdc++.h>
#define maxn 1000010
#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int a[10];
        bool flag = 0;//flag 初始化为0 
        for (int i = 1; i <= 4; i++)
            cin >> a[i];
        sort(a + 1, a + 5);//排序 
        for (int i = 1; i <= 3; i++) {
            if (a[i] + 1 == a[i + 1] && a[i + 1] + 1 == a[i + 2]) {
			//判断是否存在任意三个数 a,b,c 使得 a+1=b=c-1  
                flag = 1;
                break;
            }
        }
        if (flag) {//存在必定有解 
            cout << "1\n";
            continue;
        }
        for (int i = 1; i <= 4; i++) {
            for (int j = i + 1; j <= 4; j++) {
            	//判断是否存在相等的两个数 a,b
                if (a[i] == a[j]) {
                    a[i] = INF, a[j] = INF;//设为无穷大 
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        sort(a + 1, a + 5);//排序 
        if (!flag) {//如果flag还是0，说明给出的数无解 
            cout << "0\n";
            continue;
        }
        if (a[2] - a[1] != 2 && a[2] - a[1] != 1) {//判断差是否不为1或2 
            cout << "0\n";//无解 
            continue;
        }
        cout << "1\n";
    }
    return 0;
}
```

---

## 作者：MujicaSaki (赞：5)

大佬代码都好短啊，我来写个长点儿的。

### 思路：

就是枚举 $1$ 到 $9$ 加进序列，然后排序一遍，判断是否存在有 $s_1 +1 = s_2 = s_3-1 $ && $s_4 = s_5$ 的序列。

然后有人就会直接从第一个数字枚举到最后一是否有第一种情况也就是 $s_1 +1 = s_2 = s_3-1 $ 然后**记录**起来再判断是否有**不属于**那记录的三个数字且相同的两个数字。这里有个问题就是数组要清空成以前的情况。

然后有人就写出了这样的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,c,a[15],x,y,z,b[15];
bool f,f1,f2;
string s;
int main()
{
	cin>>t;
    while(t--)
    {
        for(int i=1;i<5;i++) {cin>>a[i];b[i]=a[i];}//备份
        for(int i=0;i<=9;i++)//枚举0-9
        {
        	a[5]=i;
        	sort(a+1,a+6);//排序
        	for(int j=1;j<=5;j++)
        	{
        		if(a[j+1]==a[j]+1&&a[j+2]-1==a[j+1])
        		{
        			x=j;//记录
        			y=j+1;
        			z=j+2;
        			for(int k=1;k<=5;k++)
				    {
                        if(a[k]==a[k+1]&&k!=x&&k!=y&&k!=z&&k+1!=x&&k+1!=y&&k+1!=z)
                        {
                            f1=1;//如果有解
                            break;
                        }
				    }
				    if(f1==1) {cout<<1<<endl;f2=1;break;}
                }
			}
			for(int j=1;j<=5;j++) a[j]=0;
			for(int j=1;j<5;j++) a[j]=b[j];
			f=0;//清零
			f1=0;
			if(f2==1) break;
			if(i==9){cout<<0<<endl;break;}//如果都到9了还没有解
		}
		f2=0;
    }
}
```

然后就只得了 $40$ 分。

不妨看看这组数据：

```
11
8 7 6 7
7 9 8 8
7 6 5 6
9 8 7 8
7 6 8 7
1 2 3 2
7 6 6 5
2 0 1 1
2 1 1 0
7 6 7 8
0 2 1 1
```
应该全部输出 $1$，却上面的代码输出 $0$。

这组数据有什么规律呢？可以发现此组数据有上面的两个情况但是并不能一起用而且重复的是中间的量。

这样的话就比如第一个数据枚举到 $7$ 会变成 $6$ $7$ $7$ $7$ $8$。但是这样的话判断第一种情况就最多只能判断到 $6$ $7$ $7$。所以我们应该三个数分别枚举一遍。而且**不能相同**。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,c,a[15],x,y,z,b[15];
bool f,f1,f2;
int main()
{
	cin>>t;
    while(t--)
    {
        for(int i=1;i<5;i++) cin>>a[i];
        for(int i=1;i<5;i++) b[i]=a[i];
        for(int i=0;i<=9;i++)
        {
        	a[5]=i;
        	sort(a+1,a+6);
            for(int j=1;j<=5;j++)//三个变量枚举
            {  
                for(int k=j+1;k<=5;k++)//j+1防止重复
                {
                    for(int l=k+1;l<=5;l++)
                    {
                        if(a[k]==a[j]+1&&a[l]-1==a[k])
                        {
                            x=j;
                            y=k;
                            z=l;
                            for(int m=1;m<=5;m++)
                            {
                                if(a[m]==a[m+1]&&m!=x&&m!=y&&m!=z&&m+1!=x&&m+1!=y&&m+1!=z)
                                {
                                    f1=1;
                                    break;
                                }
                            }
                            if(f1==1&&f2!=1) {cout<<1<<endl;f2=1;break;}
                        }
                    }
                }
            }
			for(int j=1;j<=5;j++) a[j]=0;
			for(int j=1;j<5;j++) a[j]=b[j];
			f=0;
			f1=0;
			if(f2==1) break;
			if(i==9){cout<<0<<endl;break;}
		}
		f2=0;
    }
}
```


---

